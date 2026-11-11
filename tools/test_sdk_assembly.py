"""Original SDK provenance and native assembler alias accounting."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from production import (ROOT, ULTRALIB_ASM_FLAGS, sdk_assembly_source,
                        link_symbols, normalize_sdk_symbols)
from check_functions import native_function_symbols


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
