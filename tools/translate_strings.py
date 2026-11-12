#!/usr/bin/env python3
"""String inventory and English in-place translation for the resident image.

Strings are the `extern char D_800xxxxx[]` symbols the sources name, stored NUL-terminated in the
resident image, which maps to ROM as rom = vram - 0x7FFFF400 (tools/map_rom.py). Text is EUC-JP, and
the font loop (func_8001A944) draws single-byte ASCII directly, so a translation is plain ASCII
padded with NULs inside the original string's extent.

usage: translate_strings.py dump  [--rom baseroms/jp/baserom.z64] [--out text/strings_ja.json]
       translate_strings.py apply --translations text/strings_en.json
                                   [--rom baseroms/jp/baserom.z64] [--out build/baserom_en.z64]
       translate_strings.py selftest
"""

import argparse
import json
import re
import sys
from pathlib import Path

RESIDENT_VRAM_BIAS = 0x7FFFF400  # rom = vram - bias
RESIDENT_VRAM_END = 0x80080000
MAX_STRING = 0x100

SYMBOL_RE = re.compile(r"extern\s+(?:char|u8|s8)\s+(D_8[0-9A-Fa-f]{7})\[\]")


def scan_symbols(root: Path) -> dict:
    """Every resident D_8xxxxxxx byte-array symbol the sources declare, as {name: vram}."""
    found = {}
    for path in sorted(root.glob("src/**/*.c")) + sorted(root.glob("src/**/*.h")) + sorted(root.glob("include/*.h")):
        for name in SYMBOL_RE.findall(path.read_text(errors="ignore")):
            vram = int(name[2:], 16)
            if 0x80000000 <= vram < RESIDENT_VRAM_END:
                found[name] = vram
    return found


def decode_string(data: bytes):
    """The text at the start of data, or None when the bytes are not ASCII/EUC-JP text."""
    end = data.find(b"\x00", 0, MAX_STRING)
    if end <= 0:
        return None
    raw = data[:end]
    if max(raw) >= 0x80:
        try:
            text = raw.decode("euc-jp")
        except UnicodeDecodeError:
            return None
    else:
        text = raw.decode("ascii")
    if any(ord(c) < 0x20 and c != "\n" for c in text) or "\x7f" in text:
        return None
    return text


def dump(rom: bytes, symbols: dict) -> dict:
    strings = {}
    for name, vram in sorted(symbols.items(), key=lambda kv: kv[1]):
        off = vram - RESIDENT_VRAM_BIAS
        if off < 0 or off >= len(rom):
            continue
        text = decode_string(rom[off : off + MAX_STRING])
        if text is not None:
            strings[name] = {"vram": hex(vram), "text": text}
    return strings


def apply(rom: bytearray, strings: dict, translations: dict) -> list:
    """Writes translations in place; returns the names that did not fit."""
    overflow = []
    for name, text in translations.items():
        if name not in strings:
            raise SystemExit("%s: not in the inventory" % name)
        current = strings[name]
        if text == current["text"]:
            continue
        try:
            raw = text.encode("ascii")
        except UnicodeEncodeError:
            raise SystemExit("%s: %r is not ASCII (the glyph map covers 0x21-0x7E)" % (name, text))
        off = int(current["vram"], 16) - RESIDENT_VRAM_BIAS
        room = rom.find(b"\x00", off) - off
        if len(raw) > room:
            overflow.append((name, len(raw), room))
            continue
        rom[off : off + room] = raw + b"\x00" * (room - len(raw))
    return overflow


def selftest():
    rom = bytearray(0x2000)
    symbols = {"D_80000400": 0x80000400, "D_80000480": 0x80000480, "D_80000500": 0x80000500}
    rom[0x1000:0x1000 + 6] = "テスト".encode("euc-jp")
    rom[0x1080:0x1080 + 5] = b"ABCDE"
    rom[0x1100:0x1100 + 5] = b"\xff\xfe\x00"
    strings = dump(bytes(rom), symbols)
    assert strings["D_80000400"]["text"] == "テスト", strings
    assert strings["D_80000480"]["text"] == "ABCDE", strings
    assert "D_80000500" not in strings, "binary data was taken for text"

    overflow = apply(rom, strings, {"D_80000400": "TEST", "D_80000480": "AB"})
    assert overflow == [], overflow
    again = dump(bytes(rom), symbols)
    assert again["D_80000400"]["text"] == "TEST", again
    assert again["D_80000480"]["text"] == "AB", again
    assert rom[0x1006] == 0, "the pad after a shorter translation is not NUL"

    overflow = apply(rom, again, {"D_80000400": "TOO LONG FOR THE SLOT"})
    assert overflow == [("D_80000400", 21, 4)], overflow  # the slot is now "TEST" + NUL pad
    print("selftest ok")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("command", choices=["dump", "apply", "selftest"])
    ap.add_argument("--rom", default="baseroms/jp/baserom.z64")
    ap.add_argument("--out")
    ap.add_argument("--translations")
    args = ap.parse_args()
    root = Path(__file__).absolute().parent.parent

    if args.command == "selftest":
        selftest()
        return

    rom = Path(args.rom).read_bytes()
    strings = dump(rom, scan_symbols(root))
    if args.command == "dump":
        out = Path(args.out or root / "text/strings_ja.json")
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps(strings, ensure_ascii=False, indent=1, sort_keys=True) + "\n")
        print("%d strings -> %s" % (len(strings), out))
        return

    translations = json.loads(Path(args.translations).read_text())
    rom = bytearray(rom)
    overflow = apply(rom, strings, translations)
    for name, size, room in overflow:
        print("%s: %d bytes in a %d-byte slot" % (name, size, room), file=sys.stderr)
    out = Path(args.out or root / "build/baserom_en.z64")
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_bytes(rom)
    print("%d translations applied, %d overflow -> %s" % (len(translations) - len(overflow), len(overflow), out))
    sys.exit(1 if overflow else 0)


if __name__ == "__main__":
    main()
