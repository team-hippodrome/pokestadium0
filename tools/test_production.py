"""Storage and assembler regression tests using synthetic, redistributable bytes."""
from pathlib import Path
import shutil
import struct
import tempfile
import unittest
import json

from m2c_easiest import function_bytes
from production import MACROS, canonical_assembly, encode_image, run, storage_template, trim_text
from production import ROOT, SECTION_REGISTRY, SOURCE_REGISTRY, source_files, trim_file_text
from production import ASSETS, fix_checksum


def wrapped(override=None):
    # One literal A, a seven-byte overlapping backreference, literals BCD.
    yay0 = b'Yay0' + struct.pack('>3I', 11, 20, 22)
    yay0 += struct.pack('>IH', 0xB8000000, 0x5000) + b'ABCD'
    patch = b'' if override is None else override + struct.pack('>I', 4)
    header = b'PERS-SZP' + struct.pack('>4I', 24 + len(patch), 11, 0, int(override is not None))
    return header + patch + yay0


class StorageTests(unittest.TestCase):
    def test_reconstructs_literals_and_overlapping_backreferences(self):
        original = wrapped()
        template, placeholders = storage_template(original)
        self.assertEqual(template[-4:], bytes(4))
        self.assertEqual(encode_image(b'AAAAAAAABCD', template, placeholders), original)

    def test_literals_come_from_the_rebuilt_image(self):
        template, placeholders = storage_template(wrapped())
        changed = encode_image(b'ZZZZZZZZEFG', template, placeholders)
        self.assertEqual(changed[-4:], b'ZEFG')

    def test_incompatible_change_fails_instead_of_copying_original_code(self):
        template, placeholders = storage_template(wrapped())
        with self.assertRaisesRegex(ValueError, 'backreference'):
            encode_image(b'ABAAAAAABCD', template, placeholders)

    def test_restoration_words_come_from_the_rebuilt_image(self):
        original = wrapped(b'WXYZ')
        template, placeholders = storage_template(original)
        self.assertEqual(template[24:28], bytes(4))
        self.assertEqual(encode_image(b'AAAAWXYZBCD', template, placeholders), original)
        changed = encode_image(b'AAAA1234BCD', template, placeholders)
        self.assertEqual(changed[24:28], b'1234')

    def test_fixed_extent_is_enforced(self):
        template, placeholders = storage_template(wrapped())
        with self.assertRaisesRegex(ValueError, 'changed size'):
            encode_image(b'AAAA', template, placeholders)


class ExtractedAssetsTests(unittest.TestCase):
    @unittest.skipUnless((ASSETS / 'manifest.json').exists(), 'private extraction unavailable')
    def test_every_owner_is_erased_from_opaque_image_assets(self):
        manifest = json.loads((ASSETS / 'manifest.json').read_text())
        count = 0
        for group in manifest['groups']:
            image = (ASSETS / (group['name'] + '.bin')).read_bytes()
            for owner in group['owners']:
                start, end = int(owner['start'], 0), int(owner['end'], 0)
                self.assertEqual(image[start:end], bytes(owner['size']), owner['name'])
                count += 1
        self.assertEqual(count, 5444)


@unittest.skipUnless(shutil.which('mips-linux-gnu-as'), 'MIPS GNU assembler unavailable')
class AssemblerTests(unittest.TestCase):
    def check_words(self, instructions):
        lines = []
        expected = bytearray()
        for index, (word, instruction) in enumerate(instructions):
            lines.append(f'/* {index * 4:06X} {0x80000000 + index * 4:08X} {word:08X} */ {instruction}')
            expected.extend(word.to_bytes(4, 'big'))
        source = MACROS + '.text\nglabel fixture\n' + canonical_assembly('\n'.join(lines)) + 'endlabel fixture\n'
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / 'fixture.s'
            obj = path.with_suffix('.o')
            path.write_text(source)
            run(['mips-linux-gnu-as', '-march=vr4300', '-32', '-G0', path, '-o', obj])
            self.assertEqual(function_bytes(obj, 'fixture'), bytes(expected))

    def test_move_alias_preserves_or_versus_addu(self):
        self.check_words([(0x00401021, 'move $v0, $v0'), (0x00401025, 'move $v0, $v0')])

    def test_edited_operands_are_not_replaced_by_stale_listing_registers(self):
        text = '/* 000000 80000000 00401021 */ move $v0, $a0\n'
        self.assertIn('addu $v0, $a0, $zero', canonical_assembly(text))
        text = '/* 000004 80000004 40026000 */ mfc0 $a0, Cause\n'
        self.assertIn('mfc0 $a0, $13', canonical_assembly(text))

    def test_control_register_names_and_64_bit_transfers(self):
        self.check_words([(0x40026000, 'mfc0 $v0, Status'),
                          (0x4442F800, 'cfc1 $v0, $FpcCsr'),
                          (0x44222000, 'dmfc1 $v0, $f4'),
                          (0xDDEFF8C0, 'ld $t7, -0x740($t7)'),
                          (0xFF480110, 'sd $t0, 0x110($k0)')])

    def test_division_does_not_expand_to_trap_macro(self):
        self.check_words([(0x0085001A, 'div $a0, $a1'), (0x0085001B, 'divu $a0, $a1')])

    def test_live_zero_instructions_cannot_be_trimmed_as_alignment(self):
        with tempfile.TemporaryDirectory() as temporary:
            source = Path(temporary) / 'fixture.s'
            obj = source.with_suffix('.o')
            source.write_text(MACROS + '.text\nglabel fixture\nnop\nnop\nendlabel fixture\n')
            run(['mips-linux-gnu-as', '-march=vr4300', '-32', '-G0', source, '-o', obj])
            with self.assertRaisesRegex(ValueError, 'symbol size differs'):
                trim_text(obj, 'fixture', 4)
            trim_text(obj, 'fixture', 8)
            self.assertEqual(function_bytes(obj, 'fixture'), bytes(8))


if __name__ == '__main__':
    unittest.main()


@unittest.skipUnless((ROOT / 'baseroms/jp/baserom.z64').exists(), 'private ROM unavailable')
class ChecksumTests(unittest.TestCase):
    def test_restamping_the_retail_rom_reproduces_its_header(self):
        rom = bytearray((ROOT / 'baseroms/jp/baserom.z64').read_bytes())
        header = rom[0x10:0x18]
        rom[0x10:0x18] = bytes(8)
        fix_checksum(rom)
        self.assertEqual(rom[0x10:0x18], header)


class SourceRegistryTests(unittest.TestCase):
    def test_every_source_file_is_registered(self):
        registered = json.loads(SOURCE_REGISTRY.read_text())
        files = source_files(registered)
        self.assertEqual(sorted(registered), sorted({path for path, _ in files.values()}))
        on_disk = {str(p.relative_to(ROOT)) for p in (ROOT / 'src').rglob('*.c')
                   if not p.name.endswith('.inc.c')}
        self.assertEqual(set(registered), on_disk)

    def test_placed_sections_belong_to_registered_files(self):
        registered = set(json.loads(SOURCE_REGISTRY.read_text()))
        for path, sections in json.loads(SECTION_REGISTRY.read_text()).items():
            self.assertIn(path, registered)
            self.assertLessEqual(set(sections), {'.rodata', '.data', '.bss'}, path)
            for place in sections.values():
                address = place['address'] if isinstance(place, dict) else place
                self.assertRegex(address, r'^0x[0-9A-F]{8}$')

    @unittest.skipUnless(shutil.which('mips-linux-gnu-as'), 'MIPS GNU assembler unavailable')
    def test_file_text_trims_only_zero_alignment(self):
        with tempfile.TemporaryDirectory() as temporary:
            source = Path(temporary) / 'fixture.s'
            obj = source.with_suffix('.o')
            source.write_text(MACROS + '.text\nglabel fixture\njr $ra\nnop\n.word 0, 0\n')
            run(['mips-linux-gnu-as', '-march=vr4300', '-32', '-G0', source, '-o', obj])
            self.assertEqual(trim_file_text(obj, 8), 8)
            # A span longer than the object keeps the object size; the image
            # comparison checks the remaining (erased) owner bytes.
            self.assertEqual(trim_file_text(obj, 0x20), 8)
            source.write_text(MACROS + '.text\nglabel fixture\njr $ra\nnop\nnop\naddiu $v0, $v0, 1\n')
            run(['mips-linux-gnu-as', '-march=vr4300', '-32', '-G0', source, '-o', obj])
            with self.assertRaisesRegex(ValueError, 'owners span'):
                trim_file_text(obj, 8)
