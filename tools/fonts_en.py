#!/usr/bin/env python3
"""Stadium 1's English font for a Stadium Zero ROM: the data half of the English build.

Zero's font archive (ROM 0x2B2C80, six PERS-SZP files) holds square Japanese glyphs, 257 cells per
set, with one advance for every glyph: its Latin letters are full-width. Stadium 1's sets have the
same cell geometry (16x10, 16x12, 16x16, 24x20, 24x24, 32x32) and proportional Latin glyphs, each
set starting with a 0x90-byte advance table.

An English set is Stadium 1's advance table and 145 Latin glyphs, then Zero's own cells 145..256
(lower-case full-width letters, hiragana, part of the katakana), the layout both games share up to
glyph 68 (symbols, digits, capitals):

    [Latin advances, 0x90 bytes] [Latin 0..144] [Zero 145..256]

Zero's katakana starts at cell 69, inside the Latin glyphs, so its cells 69..144 move to the 76
cells English text never draws (katakana_cell): Stadium 1's accented letters other than the e
acute, Zero's full-width lower case (drawn with the Latin letters instead) and the unused last
cell. A set keeps Zero's 257 cells that way; any more ran the big sets out of memory on the
order-select screen.

The code half is C built with -DENGLISH: func_8001A118 registers the cells past the table and keeps
the set's own advance, and func_80019F70 maps ASCII through D_8006081F with each glyph's advance,
katakana to its moved cells, full-width lower case to the Latin letters, and everything else
the retail way with the set's own advance. tools/production.py calls this for `--english`.

usage: fonts_en.py selftest
       fonts_en.py names --us STADIUM1.z64   (the name pass: English names wider than the Japanese)
"""

import argparse
import json
import struct
from pathlib import Path

ZERO_FONTS = 0x2B2C80            # the BinArchive func_8001A194 opens
ZERO_FONTS_END = 0x2E0BE0
ZERO_ASCII_MAP = 0x8006081F - 0x7FFFF400  # D_8006081F, indexed by the character code
US_FONTS = 0x3BA190              # fonts_ROM_START in the Stadium 1 decompilation
US_ASCII_MAP = 0x8DE80           # 128-byte table whose A-Z and a-z entries increase
MAP_BYTES = 0x80
ADVANCES = 0x90
GLYPHS = 0x91
ZERO_CELLS = 257
KATAKANA = range(69, GLYPHS)     # Zero's katakana cells that the Latin glyphs cover
E_ACUTE = 118                    # the one accented Latin glyph the ASCII map draws (`@`)
CELLS = [(0x10, 0x0A), (0x10, 0x0C), (0x10, 0x10), (0x18, 0x14), (0x18, 0x18), (0x20, 0x20)]


def archive_files(rom, offset):
    total, count = struct.unpack_from('>4I', rom, offset)[2:]
    if count != len(CELLS):
        raise SystemExit('%#x: archive has %d files, expected %d' % (offset, count, len(CELLS)))
    return total, [struct.unpack_from('>4I', rom, offset + 0x10 + i * 0x10)[:2] for i in range(count)]


def set_data(rom, offset, size):
    """One font file (PERS-SZP), decompressed."""
    import crunch64
    blob = rom[offset:offset + size]
    return crunch64.yay0.decompress(blob[struct.unpack_from('>I', blob, 8)[0]:])


def map_is_latin(table):
    """Whether table[c] is a glyph index in the Latin range for A-Z and a-z, increasing."""
    upper, lower = table[0x41:0x5B], table[0x61:0x7B]
    return (all(upper[i] < upper[i + 1] for i in range(25))
            and all(lower[i] < lower[i + 1] for i in range(25))
            and max(upper) < GLYPHS and max(lower) < GLYPHS)


def latin_map(us):
    """Stadium 1's glyph numbers for printable ASCII (0x21..0x7F), for D_8006081F."""
    table = us[US_ASCII_MAP:US_ASCII_MAP + MAP_BYTES]
    if not map_is_latin(table):
        raise SystemExit('no ASCII glyph map at %#x in that dump: is it the Stadium 1 US ROM?' % US_ASCII_MAP)
    # Entries below 0x21 are the game's text macros (0x09/0x0D/0x11/0x15 -> glyph 6, 0x19 -> 1,
    # ...), which Stadium 1's table zeroes; a name that uses one would then draw glyph 0 forever.
    return table[0x21:]


def katakana_cell(cell):
    """Where Zero's katakana cell 69..144 is in an English set: Font_GetKatakanaGlyph in
    src/model_renderer.c. Cells 95..117 and 119..144 (accented Latin), 149..174 (full-width lower
    case) and 256 (unused)."""
    i = cell - KATAKANA[0]
    if i < 23:
        return 95 + i
    if i < 49:
        return 96 + i
    if i < 75:
        return 100 + i
    return 256


def english_set(zero, latin, cell):
    """One English font file, uncompressed: Stadium 1's table and glyphs, Zero's cells 145..256,
    and Zero's katakana cells that the Latin glyphs cover moved to katakana_cell."""
    out = bytearray(latin[:ADVANCES + GLYPHS * cell] + zero[GLYPHS * cell:])
    for k in KATAKANA:
        at = ADVANCES + katakana_cell(k) * cell
        out[at:at + cell] = zero[k * cell:(k + 1) * cell]
    return bytes(out)


def english_archive(archive, us):
    """Zero's font archive (its ROM bytes) with every set rebuilt by english_set."""
    import crunch64
    _, zfiles = archive_files(archive, 0)
    _, ufiles = archive_files(us, US_FONTS)
    blobs = []
    for index, ((zoff, zsize), (uoff, usize)) in enumerate(zip(zfiles, ufiles)):
        width, height = CELLS[index]
        zero = set_data(archive, zoff, zsize)
        latin = set_data(us, US_FONTS + uoff, usize)
        if len(zero) != ZERO_CELLS * width * height or len(latin) < ADVANCES + GLYPHS * width * height:
            raise SystemExit('font set %d does not have the expected cells' % index)
        out = english_set(zero, latin, width * height)
        blobs.append(b'PERS-SZP' + struct.pack('>4I', 0x18, len(out), len(out), 0) + crunch64.yay0.compress(out))
    header, body = bytearray(0x10 + 0x10 * len(blobs)), bytearray()
    for index, blob in enumerate(blobs):
        struct.pack_into('>2I', header, 0x10 + 0x10 * index, len(header) + len(body), len(blob))
        body += blob + bytes(-len(blob) % 16)
    struct.pack_into('>4I', header, 0, 0, 0, len(header) + len(body), len(blobs))
    return bytes(header + body)


def put(rom, at, offset, data):
    """Writes data where the retail ROM bytes offset.. are in this build; they must still be a run."""
    start = at(offset)
    if at(offset + len(data) - 1) != start + len(data) - 1:
        raise SystemExit('retail ROM %#x..%#x is no longer contiguous' % (offset, offset + len(data)))
    rom[start:start + len(data)] = data


def english(rom, us, at):
    """Points Zero's ASCII map at the Latin glyphs. at(retail ROM offset) is where it is now."""
    put(rom, at, ZERO_ASCII_MAP + 0x21, latin_map(us))


# The name tables in text/strings.json (resident ROM offsets, first..last entry). A box that holds
# the longest Japanese name of a table holds every English name that is no wider than that.
NAME_TABLES = (("species", 0x07A680, 0x07B358), ("moves", 0x07B460, 0x07BD04), ("items", 0x07BD40, 0x07C280))


def text_width(text, table, advances, own):
    """Pixels `text` takes: each ASCII glyph's own advance, the set's for the rest (func_80019F70)."""
    return sum(advances[table[ord(c)]] if c.isascii() else own for c in text.replace('é', '@'))


def names(us_path, json_path):
    """Lists, per font set, the English names wider than the longest Japanese name of their table."""
    us = Path(us_path).read_bytes()
    table = bytes(0x21) + latin_map(us)
    strings = json.loads(Path(json_path).read_text(encoding="utf-8"))
    _, ufiles = archive_files(us, US_FONTS)
    for index, (uoff, usize) in enumerate(ufiles):
        advances = set_data(us, US_FONTS + uoff, usize)[:ADVANCES]
        own = CELLS[index][1]   # the advance of a Japanese glyph (func_8001A194): the cell height
        for name, first, last in NAME_TABLES:
            entries = [e for key, e in strings.items() if first <= int(key, 16) <= last and e["en"]]
            room = max(len(e["jp"]) for e in entries) * own
            wide = sorted({(text_width(e["en"], table, advances, own), e["en"]) for e in entries
                           if text_width(e["en"], table, advances, own) > room}, reverse=True)
            print("set %d (%dpx) %s: %d of %d wider than %dpx%s" % (
                index, own, name, len(wide), len(entries), room,
                "".join("\n    %3d %s" % pair for pair in wide)))


def selftest():
    assert text_width("ab♀", bytes(range(0x80)), bytes([3] * 0x80), 10) == 16
    table = bytearray(MAP_BYTES)
    for i in range(26):
        table[0x41 + i] = 26 + i
        table[0x61 + i] = 69 + i
    assert map_is_latin(table)
    broken = bytearray(table)
    broken[0x50] = 0
    assert not map_is_latin(broken), 'a broken map was accepted'
    # One-byte cells: each of Zero's holds its own number (mod 256), every Latin one 'L'.
    zero = bytes(i & 0xFF for i in range(ZERO_CELLS))
    latin = bytes(ADVANCES) + b'L' * GLYPHS
    cells = english_set(zero, latin, 1)[ADVANCES:]
    moved = [katakana_cell(k) for k in KATAKANA]
    assert len(cells) == ZERO_CELLS and len(set(moved)) == len(KATAKANA) and E_ACUTE not in moved, moved
    assert all(cells[katakana_cell(k)] == k for k in KATAKANA), 'katakana cells'
    # Everything else: Latin below 95 and the e acute, Zero's katakana tail 145..148 and hiragana.
    assert all(cells[i] == (ord('L') if i < GLYPHS else i) for i in range(ZERO_CELLS)
               if i not in moved), 'set layout'
    assert not set(moved) & (set(range(95)) | set(range(145, 149)) | set(range(175, 256))), moved
    rom = bytearray(0x40)
    put(rom, lambda offset: offset + 0x10, 0x8, b'abcd')
    assert rom[0x18:0x1C] == b'abcd', rom
    try:
        put(rom, lambda offset: offset + (0x10 if offset < 0xA else 0x20), 0x8, b'abcd')
    except SystemExit:
        pass
    else:
        raise AssertionError('a split run was written')
    print('selftest ok')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('command', choices=['selftest', 'names'])
    ap.add_argument('--us', help='Stadium 1 US ROM')
    ap.add_argument('--json', default='text/strings.json')
    args = ap.parse_args()
    if args.command == 'names':
        return names(args.us, args.json)
    selftest()


if __name__ == '__main__':
    main()
