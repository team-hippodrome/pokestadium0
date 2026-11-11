"""Original SDK provenance and native assembler alias accounting."""
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from production import (ROOT, ULTRALIB_ASM_FLAGS, sdk_assembly_source,
                        link_symbols, normalize_sdk_symbols, headers_digest)
from check_functions import native_function_symbols, native_owner_span, compare


class SDKAssemblyTests(unittest.TestCase):
    def wrapper(self, text, source='lib/ultralib/src/os/example.s'):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            assembly = root / source
            assembly.parent.mkdir(parents=True)
            assembly.write_text('.text\n')
            wrapper = root / 'src/example.c'
            wrapper.parent.mkdir(parents=True, exist_ok=True)
            wrapper.write_text(text)
            with patch('production.ROOT', root):
                return sdk_assembly_source('src/example.c', {'assembly_source': source})

    def test_original_source_is_selected_by_include(self):
        source = 'lib/ultralib/src/os/example.s'
        self.assertEqual(self.wrapper('/* Original SDK */\n#include "' + source + '"\n'), source)

    def test_extra_code_cannot_receive_original_sdk_credit(self):
        with self.assertRaisesRegex(ValueError, 'include only'):
            self.wrapper('#include "lib/ultralib/src/os/example.s"\nint extra(void) { return 0; }')

    def test_non_sdk_source_cannot_receive_original_sdk_credit(self):
        with self.assertRaisesRegex(ValueError, 'invalid original SDK'):
            self.wrapper('#include "src/example.s"', 'src/example.s')

    def test_entry_alias_does_not_duplicate_a_sized_function(self):
        functions = {'alias': (0, 0), 'body': (0, 12), 'second': (16, 8)}
        self.assertEqual(native_function_symbols(functions),
                         {'body': (0, 12), 'second': (16, 8)})

    def test_unsized_entry_without_a_body_remains_subject_to_comparison(self):
        functions = {'unknown': (0, 0), 'body': (4, 12)}
        self.assertEqual(native_function_symbols(functions), functions)

    def test_local_sdk_assembly_headers_are_part_of_the_receipt_digest(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            header = root / 'lib/ultralib/src/os/exceptasm.h'
            header.parent.mkdir(parents=True)
            header.write_text('#define MQ_FULLQUEUE 4\n')
            with patch('production.ROOT', root):
                original = headers_digest()
                header.write_text('#define MQ_FULLQUEUE 8\n')
                self.assertNotEqual(headers_digest(), original)

    def test_internal_sdk_entry_compares_its_complete_instruction_interval(self):
        owners = {(None, 0x80000100): ('outer', [0x03E00008, 0, 13, 0x03E00008], ())}
        region = native_owner_span(None, 0x80000108, 8, owners)
        self.assertEqual(region[0], 'outer')
        functions = {'internal': (0, 8)}
        original = struct.pack('>2I', 13, 0x03E00008)
        self.assertIsNone(compare(original, functions, {}, 'internal', 0x80000108,
                                  region[1], {}))
        changed = struct.pack('>2I', 0, 0x03E00008)
        self.assertEqual(compare(changed, functions, {}, 'internal', 0x80000108,
                                 region[1], {}), 'word 0')

    def test_sdk_entries_cannot_escape_their_owner_or_use_an_unknown_extent(self):
        owners = {(None, 0x80000100): ('first', [1, 2], ()),
                  (None, 0x80000108): ('second', [3, 4], ())}
        for address, size in ((0x80000104, 8), (0x80000100, 0),
                              (0x80000100, 3), (0x80000101, 4), (0x80000200, 4)):
            with self.subTest(address=address, size=size):
                self.assertIsNone(native_owner_span(None, address, size, owners))
        self.assertIsNone(native_owner_span(0, 0x80000100, 8, owners))

    def test_only_referenced_undefined_symbols_need_addresses(self):
        assembler = shutil.which('mips-linux-gnu-as')
        if not assembler:
            self.skipTest('MIPS assembler unavailable')
        with tempfile.TemporaryDirectory() as directory:
            source, obj = Path(directory) / 'input.s', Path(directory) / 'output.o'
            source.write_text('.text\n.globl unused\n.globl body\nbody:\n'
                              'lui $t0, %hi(required)\n'
                              'addiu $t0, $t0, %lo(required)\n')
            subprocess.run([assembler, '-32', '-EB', '-o', str(obj), str(source)],
                           check=True, capture_output=True)
            defined, missing = link_symbols([obj])
            self.assertIn('body', defined)
            self.assertEqual(missing, {'required'})

    def test_native_sdk_metadata_links_without_changing_text_or_references(self):
        compiler = ROOT / 'tools/ido5.3/cc'
        linker = shutil.which('mips-linux-gnu-ld')
        if not compiler.exists() or not linker:
            self.skipTest('native SDK assembler or MIPS linker unavailable')
        from elftools.elf.elffile import ELFFile
        from elftools.elf.relocation import RelocationSection

        def contents(path):
            with path.open('rb') as handle:
                elf = ELFFile(handle)
                references = []
                for section in elf.iter_sections():
                    if isinstance(section, RelocationSection):
                        symbols = elf.get_section(section['sh_link'])
                        references.extend((section.name, entry['r_offset'],
                                           entry['r_info_type'],
                                           symbols.get_symbol(entry['r_info_sym']).name)
                                          for entry in section.iter_relocations())
                return elf.get_section_by_name('.text').data(), references

        with tempfile.TemporaryDirectory() as directory:
            obj, linked = Path(directory) / 'native.o', Path(directory) / 'linked.o'
            subprocess.run([str(compiler), *ULTRALIB_ASM_FLAGS, '-O1', '-mips2',
                            '-o', str(obj), 'lib/ultralib/src/os/probetlb.s'],
                           cwd=ROOT, check=True, capture_output=True)
            before = contents(obj)
            normalize_sdk_symbols(obj)
            self.assertEqual(contents(obj), before)
            subprocess.run([linker, '-r', '-o', str(linked), str(obj)],
                           check=True, capture_output=True)
            self.assertEqual(contents(linked)[0], before[0])


if __name__ == '__main__':
    unittest.main()
