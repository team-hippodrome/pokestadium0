#!/usr/bin/env python3
"""Write English text from text/strings.json into a built ROM, in place.

`text/strings.json` is produced by `tools/string_catalog.py dump` (jp text, room, region) and filled
either by `string_catalog.py fill` (a jp->en dictionary) or by hand. Only string runs the scanner
found are touched, so every write lands on an uncompressed, already-catalogued string; the English
text is NUL-padded inside the bytes the Japanese text occupied, which the font loop reads as a
terminator. tools/production.py calls this for `--english`.

usage: translate_strings.py selftest
"""

import argparse

from fonts_en import put


def encode(text):
    """English text as the game's bytes: ASCII, with `@` for é (Stadium 1's map draws it so), and
    EUC-JP for what only the Japanese cells have (the ♀ and ♂ of Nidoran)."""
    return text.replace("é", "@").encode("euc_jp", "replace")


def apply(rom, strings, at=lambda offset: offset):
    """Patches every translated string in place; returns (written, overflow, skipped).

    Entries are keyed by retail ROM offset; at(offset) is where that byte is in this build.
    """
    written = overflow = skipped = 0
    for key, entry in strings.items():
        text = entry.get("en")
        if not text:
            skipped += 1
            continue
        raw = encode(text)
        if len(raw) + 1 > entry["room"]:
            overflow += 1
            continue
        put(rom, at, int(key, 16), raw + bytes(entry["room"] - len(raw)))
        written += 1
    return written, overflow, skipped


def selftest():
    rom = bytearray(0x100)
    rom[0x40:0x48] = "バトル".encode("euc_jp") + b"\x00\x00"      # 6 bytes of text, room 8
    strings = {
        "0x000040": {"jp": "バトル", "en": "Battle", "room": 8},
        "0x000050": {"jp": "とてもながい", "en": "far too long to fit", "room": 6},
        "0x000060": {"jp": "はい", "en": "", "room": 8},
    }
    written, overflow, skipped = apply(rom, strings)
    assert (written, overflow, skipped) == (1, 1, 1), (written, overflow, skipped)
    assert rom[0x40:0x48] == b"Battle\x00\x00", rom[0x40:0x48]
    assert encode("POKéMON") == b"POK@MON" and encode("Nidoran♀") == b"Nidoran\xa1\xea"
    assert rom[0x50:0x58] == b"\x00" * 8, "an over-long string was written"
    moved = bytearray(0x100)
    apply(moved, strings, lambda offset: offset + 0x20)
    assert moved[0x60:0x68] == b"Battle\x00\x00", "the string did not follow the layout"
    print("selftest ok")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("command", choices=["selftest"])
    ap.parse_args()
    selftest()


if __name__ == "__main__":
    main()
