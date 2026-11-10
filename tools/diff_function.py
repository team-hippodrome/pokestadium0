#!/usr/bin/env python3
"""Show a compiled C function next to its retail owner, instruction by instruction.

Usage: tools/diff_function.py src/file.c NAME [--all]

NAME is the C function name. The file is compiled the way
tools/check_functions.py compiles it (-DNON_MATCHING), so held C is included.
Relocated fields are shown as their relocation; '*' marks differing words.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import struct
import sys

import rabbitizer

import check_functions as cf

ROOT = cf.ROOT


def disasm(word, vram):
    return rabbitizer.Instruction(word, vram).disassemble()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('source')
    parser.add_argument('name')
    parser.add_argument('--all', action='store_true', help='print matching lines too')
    args = parser.parse_args()
    rom = (ROOT / 'baseroms/jp/baserom.z64').read_bytes()
    if hashlib.sha256(rom).hexdigest() != cf.EXPECTED_SHA256:
        sys.exit('wrong input ROM')
    owners = cf.load_owner_words(rom)
    symbols = cf.load_symbols()
    overrides = json.loads((ROOT / 'tools/cflags_overrides.json').read_text())
    data, error = cf.compile_source(args.source, str(ROOT / 'tools'), overrides)
    if data is None:
        sys.exit(error)
    text, functions, relocations = cf.parse_object(data)
    if args.name not in functions:
        sys.exit('no function %s in the object' % args.name)
    match = cf.ADDR_NAME.match(args.name)
    address = symbols.get(args.name, int(match.group(1), 16) if match else None)
    owner = owners.get((cf.segment_of(args.source), address))
    if owner is None:
        sys.exit('no owner at the address of %s' % args.name)
    offset, size = functions[args.name]
    got = struct.unpack('>%dI' % (size // 4), text[offset:offset + size])
    want = owner[1]
    reason = cf.compare(text, functions, relocations, args.name, address, want, symbols, {}, owner[2])
    print('%s: %d words, owner %s has %d; %s' % (args.name, len(got), owner[0], len(want),
                                                  'MATCH' if reason is None else reason))
    for i in range(max(len(got), len(want))):
        vram = address + 4 * i
        g = got[i] if i < len(got) else None
        w = want[i] if i < len(want) else None
        reloc = relocations.get(offset + 4 * i)
        if g is not None and w is not None:
            if reloc:
                mask = 0xFC000000 if reloc[0] == 4 else 0xFFFF0000
                same = (g & mask) == (w & mask)
            else:
                same = g == w
        else:
            same = False
        if same and not args.all:
            continue
        left = disasm(g, vram) if g is not None else ''
        if reloc:
            left += '  [%s]' % reloc[1]
        right = disasm(w, vram) if w is not None else ''
        print('%s %4d %-48s %s' % (' ' if same else '*', i, left[:48], right))


if __name__ == '__main__':
    main()
