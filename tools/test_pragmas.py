#!/usr/bin/env python3
"""Check pragma ownership, conditional structure, scoped bytes and C syntax."""
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys
import unittest

from generate_pragmas import conditional, LISTING_WORD
from map_fragment_sections import load_image

ROOT = Path(__file__).resolve().parents[1]
PRAGMA = re.compile(r'#pragma GLOBAL_ASM\("([^"]+)"\)')


class TemplateTests(unittest.TestCase):
    def test_reference_conditional_direction(self):
        text = conditional("func_80000460", "asm/jp/nonmatchings/1060/func_80000460.s")
        self.assertTrue(text.startswith("#ifdef NON_MATCHING\n"))
        self.assertIn("#else\n#pragma GLOBAL_ASM", text)
        self.assertTrue(text.endswith("#endif\n"))
        self.assertNotIn("void func_", text)


class InventoryTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.inventory = json.loads((ROOT / "docs/pragma-inventory.json").read_text())

    def test_every_owner_has_one_source(self):
        """Each owner has one C, original SDK assembly, or GLOBAL_ASM source."""
        import csv
        pragmas = []
        for path in sorted((ROOT / "src").rglob("*.c")):
            source = path.read_text(encoding="utf-8")
            found = PRAGMA.findall(source)
            self.assertEqual(source.count("#pragma GLOBAL_ASM"), len(found), path)
            pragmas.extend(found)
        self.assertEqual(len(pragmas), len(set(pragmas)))
        by_assembly = {row["assembly"]: row["name"] for row in self.inventory["owners"]}
        for path in pragmas:
            self.assertIn(path, by_assembly)
        with (ROOT / "docs/function-matches.csv").open() as handle:
            rows = list(csv.DictReader(handle))
        c_owners = {row["owner"] for row in rows if row["build"] == "c"}
        asm_owners = {by_assembly[path] for path in pragmas}
        sdk_rows = [row for row in rows if row['status'] == 'ultralib-asm']
        sdk_owners = {row['owner'] for row in sdk_rows}
        from production import sdk_assembly_source
        overrides = json.loads((ROOT / 'tools/cflags_overrides.json').read_text())
        for row in sdk_rows:
            self.assertEqual(row['build'], 'asm')
            flags = overrides[row['source']]
            self.assertEqual(flags['profile'], 'ultralib-asm')
            original = sdk_assembly_source(row['source'], flags)
            self.assertEqual(row['origin'], 'libultra:' + original[len('lib/ultralib/'):])
            self.assertIn(row['c_name'], (ROOT / original).read_text())
        self.assertFalse(c_owners & asm_owners)
        self.assertFalse(sdk_owners & (c_owners | asm_owners))
        # Matching C that still needs its file's data stays behind NON_MATCHING.
        held = {row["owner"] for row in rows if row["status"] in ("s1", "m2c", "hand") and row["build"] != "c"}
        self.assertLessEqual(held, asm_owners)
        self.assertEqual(c_owners | asm_owners | sdk_owners,
                         {row["name"] for row in self.inventory["owners"]})
        for row in rows:
            if row["status"] in ("s1", "m2c", "hand"):
                self.assertIn(row["c_name"], (ROOT / row["source"]).read_text(encoding="utf-8"))

    def test_global_symbol_names_are_unique(self):
        names = []
        for row in self.inventory["owners"]:
            names.extend([row["name"], *row["aliases"]])
        self.assertEqual(len(names), len(set(names)))

    def test_no_owners_for_resource_only_images(self):
        sections = json.loads((ROOT / "docs/sections/refined/fragment-sections.json").read_text())
        allowed = {row["image_index"] for row in sections["images"] if row["text_envelope"]}
        present = {row["image_index"] for row in self.inventory["owners"]
                   if row["image_index"] is not None}
        self.assertEqual(present, allowed)
        self.assertEqual(len(present), 187)

    def test_unresolved_transfers_do_not_block_owners(self):
        with (ROOT / "docs/sections/refined/runtime-watchlist.csv").open() as source:
            import csv
            sites = list(csv.DictReader(source))
        self.assertEqual(len(sites), 71)
        for site in sites:
            index, offset = int(site["image_index"]), int(site["offset"], 0)
            owners = [row for row in self.inventory["owners"]
                      if row["image_index"] == index
                      and int(row["start"], 0) <= offset < int(row["end"], 0)]
            self.assertEqual(len(owners), 1, site)

    def test_c_functions_match_private_input(self):
        rom_path = ROOT / "baseroms/jp/baserom.z64"
        if not rom_path.exists():
            self.skipTest("private input ROM unavailable")
        if not (ROOT / "tools/ido7.1/cc").exists():
            self.skipTest("IDO unavailable; run make setup")
        result = subprocess.run([sys.executable, str(ROOT / "tools/check_functions.py")],
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout[-2000:] + result.stderr[-2000:])

    def test_owner_ranges_and_listing_bytes_match_private_input(self):
        rom_path = ROOT / "baseroms/jp/baserom.z64"
        if not rom_path.exists():
            self.skipTest("private input ROM unavailable")
        rom = rom_path.read_bytes()
        mapping = json.loads((ROOT / "docs/mappings/resident-fragments.json").read_text())
        sections = json.loads((ROOT / "docs/sections/refined/fragment-sections.json").read_text())
        images = {}
        for row in self.inventory["owners"]:
            start, stop = int(row["start"], 0), int(row["end"], 0)
            index = row["image_index"]
            if index is None:
                self.assertGreaterEqual(start, 0x1060)
                self.assertLessEqual(stop, 0x5D8C0)
                raw = rom[start:stop]
                for excluded in self.inventory["excluded_ranges"]:
                    if excluded["image"] == "resident":
                        self.assertFalse(start < int(excluded["end"], 0)
                                         and stop > int(excluded["start"], 0))
            else:
                if index not in images:
                    images[index] = load_image(rom, mapping["fragments"][index])
                self.assertGreaterEqual(start, 0x20)
                self.assertLessEqual(stop, int(sections["images"][index]["text_envelope"][1], 0))
                raw = images[index][start:stop]
            self.assertEqual(hashlib.sha256(raw).hexdigest(), row["input_sha256"])
            data = (ROOT / row["assembly"]).read_bytes()
            self.assertEqual(hashlib.sha256(data).hexdigest(), row["assembly_sha256"])
            listed = b"".join(int(value, 16).to_bytes(4, "big")
                              for value in LISTING_WORD.findall(data.decode()))
            self.assertEqual(listed, raw)


if __name__ == "__main__":
    unittest.main(verbosity=2)
