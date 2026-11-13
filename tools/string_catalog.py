#!/usr/bin/env python3
"""Catalogue every Japanese string in the ROM as JSON, with room for an English translation.

The output is what a translator edits: one entry per string, keyed by its ROM offset, holding the
original EUC-JP text, the English text, and how many bytes the string may occupy in place. `dump`
merges into an existing file, so re-running it never loses work already typed into `en`.

usage: string_catalog.py dump [--rom baseroms/jp/baserom.z64] [--json text/strings.json]
       string_catalog.py selftest
"""

import argparse
import json
import struct
import sys
from pathlib import Path

RESIDENT_ROM_START = 0x1000
RESIDENT_ROM_END = 0x80C00
MAX_STRING = 0x80
MIN_JAPANESE = 2


def euc_jp_length(data, i):
    """Bytes of one EUC-JP character at data[i], or 0 when it is not valid text."""
    b = data[i]
    if b == 0x0A or b == 0x0D:
        return 1
    if 0x20 <= b < 0x7F:
        return 1
    if 0xA1 <= b <= 0xFE and i + 1 < len(data) and 0xA1 <= data[i + 1] <= 0xFE:
        return 2
    if b == 0x8E and i + 1 < len(data) and 0xA1 <= data[i + 1] <= 0xDF:   # half-width kana
        return 2
    return 0


def read_string(rom, i):
    """The NUL-terminated string at rom[i], or None if it does not look like Japanese text."""
    text = []
    japanese = 0
    j = i
    while j < len(rom) and len(text) < MAX_STRING:
        b = rom[j]
        if b == 0:
            break
        n = euc_jp_length(rom, j)
        if n == 0:
            return None
        if n == 2:
            japanese += 1
        text.append(rom[j:j + n])
        j += n
    if rom[j] != 0 or japanese < MIN_JAPANESE:
        return None
    try:
        decoded = b''.join(text).decode('euc_jp')
    except UnicodeDecodeError:
        return None
    if any(ord(c) < 0x20 and c not in '\n' for c in decoded):
        return None
    return decoded, j


def scan(rom):
    """{offset: (text, room)} for every Japanese string outside the compressed assets."""
    found = {}
    i = 0
    while i < len(rom):
        if 0xA1 <= rom[i] <= 0xFE:
            got = read_string(rom, i)
            if got and likely_text(got[0]):
                text, end = got
                found[i] = (text, end - i)
                i = end + 1
                continue
        i += 1
    return found


def likely_text(text):
    """Whether a run of high bytes reads as game text rather than coincidental data.

    Code and binary data contain plenty of bytes in the EUC-JP range; real strings are mostly kana,
    digits and Japanese punctuation, so require 70% of the characters to be in that set.
    """
    interpunct = '\u3000\u30fc\u3001\u3002\u300c\u300d\u300e\u300f\uff01\uff1f\uff0e'
    good = 0
    for c in text:
        if '\u3041' <= c <= '\u30ff' or c in interpunct or c in ' \n' or c.isdigit():
            good += 1
    return good >= 0.7 * len(text) and len(text) >= 3


def region(offset):
    if RESIDENT_ROM_START <= offset < RESIDENT_ROM_END:
        return 'resident'
    return 'rom'


def dump(rom_path, json_path):
    rom = Path(rom_path).read_bytes()
    existing = {}
    if Path(json_path).exists():
        existing = json.loads(Path(json_path).read_text(encoding='utf-8'))
    strings = scan(rom)
    out = {}
    kept = 0
    for offset, (text, room) in sorted(strings.items()):
        key = '0x%06X' % offset
        old = existing.get(key, {})
        entry = {
            'jp': text,
            'en': old.get('en', ''),
            'room': room,
            'region': region(offset),
        }
        if old.get('en'):
            kept += 1
        out[key] = entry
    Path(json_path).parent.mkdir(parents=True, exist_ok=True)
    Path(json_path).write_text(json.dumps(out, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    print('%d strings -> %s (%d translations kept)' % (len(out), json_path, kept))


def fill(json_path, dictionary_path):
    """Fills empty `en` fields from a jp->en dictionary, leaving hand-written lines alone."""
    strings = json.loads(Path(json_path).read_text(encoding='utf-8'))
    dictionary = json.loads(Path(dictionary_path).read_text(encoding='utf-8'))
    added = 0
    for entry in strings.values():
        if entry['en'] or entry['jp'] not in dictionary:
            continue
        text = dictionary[entry['jp']]
        if len(text.encode('ascii', 'replace')) + 1 > entry['room']:
            continue                       # would not fit: leave it for a shorter wording
        entry['en'] = text
        added += 1
    Path(json_path).write_text(json.dumps(strings, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    print('%d strings filled from %s (%d remain empty)'
          % (added, dictionary_path, sum(1 for e in strings.values() if not e['en'])))


def selftest():
    # "バトル" + NUL: 2-byte EUC-JP kana, must be found as one string of 6 bytes plus terminator.
    rom = bytearray(0x100)
    text = 'バトル'.encode('euc_jp')
    rom[0x40:0x40 + len(text)] = text
    got = scan(bytes(rom))
    assert got.get(0x40) == ('バトル', len(text)), got
    assert not likely_text('淳潘衣7'), 'binary noise was accepted'
    # ASCII-only and stray high bytes must not be reported.
    rom2 = bytearray(0x100)
    rom2[0x20:0x25] = b'hello'
    rom2[0x60] = 0xFE
    rom2[0x61] = 0x00
    assert scan(bytes(rom2)) == {}, scan(bytes(rom2))
    # A translation must be shown its room, so an over-long string is caught before it is applied.
    assert got[0x40][1] == 6
    print('selftest ok')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('command', choices=['dump', 'fill', 'selftest'])
    ap.add_argument('--rom', default='baseroms/jp/baserom.z64')
    ap.add_argument('--json', default='text/strings.json')
    ap.add_argument('--dictionary', default='text/dictionary.json')
    args = ap.parse_args()
    if args.command == 'selftest':
        selftest()
        return
    if args.command == 'fill':
        fill(args.json, args.dictionary)
        return
    dump(args.rom, args.json)


if __name__ == '__main__':
    main()
