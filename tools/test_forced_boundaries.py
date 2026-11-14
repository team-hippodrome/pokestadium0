#!/usr/bin/env python3
"""Check the declared owner boundaries in generate_pragmas.FORCED_BOUNDARIES.

Stub tables are declared, never inferred from byte patterns: an undeclared
`j target; nop` (a tail jump, or adjacent wrappers) keeps the ordinary owner
rules, and a declared table is read only inside its range and inside .text.
"""
import json
from pathlib import Path
import struct
import unittest

from generate_pragmas import (FORCED_BOUNDARIES, forced_boundaries, make_section,
                              merge_owners, stub_table_targets)
from map_fragment_sections import load_image

ROOT = Path(__file__).resolve().parents[1]
BASE = 0x81000000
NOP = 0x00000000
JR_RA = 0x03E00008


def j(offset):
    return (2 << 26) | (((BASE + offset) >> 2) & 0x3FFFFFF)


def jal(offset):
    return (3 << 26) | (((BASE + offset) >> 2) & 0x3FFFFFF)


def li_v0(value):
    return 0x24020000 | value


def image(words):
    return b"".join(struct.pack(">I", word) for word in words)


def leaf(value):
    """A 16-byte leaf function: li v0, value; jr ra; nop; padding nop."""
    return [li_v0(value), JR_RA, NOP, NOP]


def owners(data, declaration=None, entries=()):
    table, forced = forced_boundaries(declaration, data, BASE, 0, len(data))
    section = make_section(data, 0, len(data), BASE, "test", entries=[0, *entries],
                           forced_entries=forced)
    return [(members[0].vromStart, members[-1].vromEnd)
            for members in merge_owners(section, data, BASE, [], table)]


class SyntheticTests(unittest.TestCase):
    def test_table_owner_grouping(self):
        """A declared table is one owner and each local target starts its own."""
        data = image([j(0x20), NOP, j(0x30), NOP, j(0x40), NOP, NOP, NOP,
                      *leaf(1), *leaf(2), *leaf(3)])
        self.assertEqual(stub_table_targets(data, 0, 0x18, 0, len(data)),
                         [0x01000020, 0x01000030, 0x01000040])
        self.assertEqual(owners(data, {"stub_table": (0, 0x18)}),
                         [(0, 0x20), (0x20, 0x30), (0x30, 0x40), (0x40, 0x50)])
        # Undeclared, the same bytes keep the ordinary rule: jumps to targets
        # nobody calls share one conservative owner.
        self.assertEqual(owners(data), [(0, 0x50)])

    def test_single_tail_jump_is_not_a_table(self):
        """A lone `j; nop` is an ordinary tail jump unless declared."""
        # 0x00 jumps into the middle of 0x10, which nothing calls.
        data = image([j(0x14), NOP, NOP, NOP,
                      li_v0(2), li_v0(3), JR_RA, NOP])
        self.assertEqual(owners(data, entries=[0x10]), [(0, 0x20)])
        # A tail jump to a called function stays a separate owner.
        data = image([j(0x10), NOP, NOP, NOP, *leaf(2),
                      jal(0x10), NOP, JR_RA, NOP])
        self.assertEqual(owners(data, entries=[0x20]),
                         [(0, 0x10), (0x10, 0x20), (0x20, 0x30)])

    def test_adjacent_wrappers_are_not_grouped(self):
        """Two adjacent called `j; nop` wrappers stay two owners when undeclared."""
        data = image([j(0x20), NOP, j(0x30), NOP, NOP, NOP, NOP, NOP,
                      *leaf(1), *leaf(2),
                      jal(0x0), NOP, jal(0x8), NOP,
                      jal(0x20), NOP, jal(0x30), NOP,
                      JR_RA, NOP, NOP, NOP])
        self.assertEqual(owners(data, entries=[0x8, 0x40]),
                         [(0, 0x8), (0x8, 0x20), (0x20, 0x30), (0x30, 0x40), (0x40, 0x70)])

    def test_scan_is_bounded(self):
        """Only the declared slots inside .text are read; bad slots are errors."""
        data = image([j(0x20), NOP, j(0x30), NOP, j(0x40), NOP, NOP, NOP, *leaf(1)])
        # The third slot is a stub too, but it is outside the declared range.
        self.assertEqual(len(stub_table_targets(data, 0, 0x10, 0, len(data))), 2)
        with self.assertRaises(ValueError):  # runs past the .text envelope
            stub_table_targets(data, 0, 0x18, 0, 0x10)
        with self.assertRaises(ValueError):  # slot 0x18 is padding, not a stub
            stub_table_targets(data, 0, 0x20, 0, len(data))
        with self.assertRaises(ValueError):  # half a slot
            stub_table_targets(data, 0, 0x14, 0, len(data))
        with self.assertRaises(ValueError):  # forced entry outside .text
            forced_boundaries({"entries": (0x30,)}, data, BASE, 0, 0x30)


class RealTableTests(unittest.TestCase):
    """Fragment 001, the model callback library."""

    @classmethod
    def setUpClass(cls):
        inventory = json.loads((ROOT / "docs/pragma-inventory.json").read_text())
        cls.owners = sorted((int(row["start"], 0), int(row["end"], 0), row["name"])
                            for row in inventory["owners"] if row["image_index"] == 1)

    def test_only_fragment_001_is_declared(self):
        self.assertEqual(sorted(FORCED_BOUNDARIES), [1])

    def test_table_is_one_owner(self):
        self.assertEqual(self.owners[0], (0x20, 0x170, "func_81000020"))

    def test_table_targets_start_owners(self):
        rom_path = ROOT / "baseroms/jp/baserom.z64"
        if not rom_path.exists():
            self.skipTest("private input ROM unavailable")
        mapping = json.loads((ROOT / "docs/mappings/resident-fragments.json").read_text())
        sections = json.loads((ROOT / "docs/sections/refined/fragment-sections.json").read_text())
        metadata = mapping["fragments"][1]
        start, stop = [int(value, 0) for value in sections["images"][1]["text_envelope"]]
        data = load_image(rom_path.read_bytes(), metadata)
        targets = stub_table_targets(data, 0x20, 0x168, start, stop)
        self.assertEqual(len(targets), 41)
        # The slot after the table is padding, so the declared end is exact.
        self.assertEqual(struct.unpack_from(">II", data, 0x168), (0, 0))
        table, entries = forced_boundaries(FORCED_BOUNDARIES[1], data, BASE, start, stop)
        local = {target - 0x01000000 for target in targets if target < 0x02000000}
        owner_starts = {owner_start for owner_start, _, _ in self.owners}
        self.assertTrue(local)
        self.assertLessEqual(local, owner_starts)
        self.assertLessEqual({0x60C, 0x65C}, owner_starts)
        self.assertEqual(set(entries), local | {0x60C, 0x65C})


if __name__ == "__main__":
    unittest.main()
