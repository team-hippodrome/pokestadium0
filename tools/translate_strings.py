#!/usr/bin/env python3
"""Write English text from text/strings.json into a built ROM, in place.

`text/strings.json` is produced by `tools/string_catalog.py dump` (jp text, room, region) and filled
either by `string_catalog.py fill` (a jp->en dictionary) or by hand. Only string runs the scanner
found are touched, so every write lands on an uncompressed, already-catalogued string; the English
text is NUL-padded inside the bytes the Japanese text occupied, which the font loop reads as a
terminator. Changes below 1 MB break the IPL3 header checksum, so it is re-stamped afterwards.

usage: translate_strings.py apply --rom build/pokestadium0-full.z64 [--json text/strings.json]
                                  [--out build/pokestadium0-en.z64]
       translate_strings.py selftest
"""

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fonts_en  # noqa: E402  (the IPL3 checksum port lives there)


def apply(rom, strings):
    """Patches every translated string in place; returns (written, overflow, skipped)."""
    written = overflow = skipped = 0
    for key, entry in strings.items():
        text = entry.get("en")
        if not text:
            skipped += 1
            continue
        raw = text.encode("ascii", "replace")
        if len(raw) + 1 > entry["room"]:
            overflow += 1
            continue
        offset = int(key, 16)
        rom[offset:offset + entry["room"]] = raw + bytes(entry["room"] - len(raw))
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
    assert rom[0x50:0x58] == b"\x00" * 8, "an over-long string was written"
    print("selftest ok")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("command", choices=["apply", "selftest"])
    ap.add_argument("--rom", default="build/pokestadium0-full.z64")
    ap.add_argument("--json", default="text/strings.json")
    ap.add_argument("--out", default="build/pokestadium0-en.z64")
    args = ap.parse_args()
    if args.command == "selftest":
        selftest()
        return
    rom = bytearray(Path(args.rom).read_bytes())
    strings = json.loads(Path(args.json).read_text(encoding="utf-8"))
    seed = fonts_en.detect_seed(rom)
    written, overflow, skipped = apply(rom, strings)
    fonts_en.fix_checksum(rom, seed)
    Path(args.out).write_bytes(rom)
    print("%d strings translated, %d did not fit, %d untranslated -> %s"
          % (written, overflow, skipped, args.out))


if __name__ == "__main__":
    main()
