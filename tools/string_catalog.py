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
import re
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
    if j >= len(rom) or rom[j] != 0 or japanese < MIN_JAPANESE:
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
        # A string starts at a Japanese character, or at ASCII (a leading space, mostly) when that
        # is word-aligned after a NUL and the Japanese follows at once.
        if 0xA1 <= rom[i] <= 0xFE or (i % 4 == 0 and i and rom[i - 1] == 0 and 0x20 <= rom[i] < 0x7F
                                      and i + 1 < len(rom) and 0xA1 <= rom[i + 1] <= 0xFE):
            got = read_string(rom, i)
            # Two characters (はい, あり, なし) only count word-aligned: unaligned pairs are noise.
            if got and likely_text(got[0]) and (len(got[0]) >= 3 or i % 4 == 0):
                text, end = got
                # Room is the NUL plus, for a string that starts word-aligned, the zero bytes up
                # to the next word: the alignment padding before whatever follows it.
                room = end + 1
                if i % 4 == 0:
                    while room % 4 and room < len(rom) and rom[room] == 0:
                        room += 1
                found[i] = (text, room - i)
                i = end + 1
                continue
        i += 1
    return found


def likely_text(text):
    """Whether a run of high bytes reads as game text rather than coincidental data.

    Code and binary data contain plenty of bytes in the EUC-JP range; real strings are mostly kana,
    digits, full-width forms and Japanese punctuation, so require 70% of the characters to be in
    that set. A two-character string must be all kana. printf conversions (ゆけっ！%s) do not count
    either way.
    """
    text = re.sub(r'%[-0-9.]*[a-zA-Z]', '', text)
    interpunct = '\u3000\u30fc\u3001\u3002\u300c\u300d\u300e\u300f\uff01\uff1f\uff0e'
    good = 0
    for c in text:
        if ('\u3041' <= c <= '\u30ff' or '\uff01' <= c <= '\uff5e' or c in interpunct or c in ' \n'
                or c.isdigit()):
            good += 1
    if len(text) == 2:
        return all('\u3041' <= c <= '\u30ff' for c in text)
    return good >= 0.7 * len(text) and len(text) >= 3


# ROM ranges whose strings stay Japanese, with the reason dump writes into their entries.
KEEP_JP = [(0x175570, 0x17BE70, 'fragment009 team records: the game builds nicknames and trainer '
                                'names from these fields as 2-byte Japanese, so ASCII draws garbage'),
           (0x4006C0, 0x4006E0, 'preset Pokemon record (nickname, trainer): the COM team names are '
                                'built from it as 2-byte Japanese; "Stadium" here drew as "S k" and '
                                'leaked "ium" into the COM nicknames')]


# ROM ranges that read as Japanese and are not text: a fill pattern (いいいいいいぅ) and sample data.
NOT_TEXT = [(0x72ADC0, 0x72ADD4), (0xE30148, 0xE30150)]


def keep_jp(offset):
    return next((reason for start, end, reason in KEEP_JP if start <= offset < end), None)


def region(offset):
    if RESIDENT_ROM_START <= offset < RESIDENT_ROM_END:
        return 'resident'
    return 'rom'


def dump(rom_path, json_path):
    rom = Path(rom_path).read_bytes()
    existing = {}
    if Path(json_path).exists():
        existing = json.loads(Path(json_path).read_text(encoding='utf-8'))
    strings = {offset: found for offset, found in scan(rom).items()
               if not any(start <= offset < end for start, end in NOT_TEXT)}
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
        if keep_jp(offset):
            entry['en'], entry['keep_jp'] = '', keep_jp(offset)
        if entry['en']:
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
        if entry['en'] or entry.get('keep_jp') or entry['jp'] not in dictionary:
            continue
        text = dictionary[entry['jp']]
        if len(text.encode('ascii', 'replace')) + 1 > entry['room']:
            continue                       # would not fit: leave it for a shorter wording
        entry['en'] = text
        added += 1
    Path(json_path).write_text(json.dumps(strings, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    print('%d strings filled from %s (%d remain empty)'
          % (added, dictionary_path, sum(1 for e in strings.values() if not e['en'])))


def merge(json_path, auto_dir):
    """Absorbs the {jp: en} files written by the translation batches into the catalogue.

    A translation is applied to every catalogue entry with that Japanese text, but only where it
    fits: `room` is what the original string occupies, terminator and alignment padding included.
    Resident strings are the exception: the English build moves a longer one to the end of the
    resident data (tools/production.py).
    """
    strings = json.loads(Path(json_path).read_text(encoding='utf-8'))
    pairs, conflicts = {}, 0
    for path in sorted(Path(auto_dir).glob('*_en.json')):
        for jp, en in json.loads(path.read_text(encoding='utf-8')).items():
            if not en:
                continue
            if pairs.get(jp, en) != en:
                conflicts += 1
                continue
            pairs[jp] = en
    filled = overflow = 0
    for entry in strings.values():
        if entry['en'] or entry.get('keep_jp') or entry['jp'] not in pairs:
            continue
        text = pairs[entry['jp']]
        if len(text.encode('ascii', 'replace')) + 1 > entry['room'] and entry['region'] != 'resident':
            overflow += 1
            continue
        entry['en'] = text
        filled += 1
    Path(json_path).write_text(json.dumps(strings, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')
    print('%d batch pairs (%d conflicting texts skipped), %d entries filled, %d would not fit, '
          '%d still untranslated' % (len(pairs), conflicts, filled, overflow,
                                     sum(1 for e in strings.values() if not e['en'])))


def selftest():
    # "バトル" + NUL: 6 bytes of 2-byte EUC-JP kana and a terminator, word-aligned, so its room
    # runs to the next word: 8 bytes.
    rom = bytearray(0x100)
    text = 'バトル'.encode('euc_jp')
    rom[0x40:0x40 + len(text)] = text
    got = scan(bytes(rom))
    assert got.get(0x40) == ('バトル', 8), got
    # An unaligned string gets only its terminator, even with zeros after it.
    rom[0x81:0x81 + len(text)] = text
    assert scan(bytes(rom)).get(0x81) == ('バトル', 7), scan(bytes(rom))
    assert not likely_text('淳潘衣7'), 'binary noise was accepted'
    assert likely_text('ゆけっ！%s') and not likely_text('は%s'), 'printf conversions'
    # Two kana count as a string only when word-aligned.
    rom[0xA0:0xA4] = rom[0xC1:0xC5] = 'はい'.encode('euc_jp')
    got = scan(bytes(rom))
    assert got.get(0xA0) == ('はい', 8) and 0xC1 not in got, got
    # ASCII-only and stray high bytes must not be reported.
    rom2 = bytearray(0x100)
    rom2[0x20:0x25] = b'hello'
    rom2[0x60] = 0xFE
    rom2[0x61] = 0x00
    assert scan(bytes(rom2)) == {}, scan(bytes(rom2))
    print('selftest ok')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('command', choices=['dump', 'fill', 'merge', 'selftest'])
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
    if args.command == 'merge':
        merge(args.json, 'text/auto')
        return
    dump(args.rom, args.json)


if __name__ == '__main__':
    main()
