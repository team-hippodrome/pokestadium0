#!/usr/bin/env python3
"""Put Stadium 1's English font into a Stadium Zero ROM, and teach the font code to use it.

Zero's font archive (ROM 0x2B2C80, six PERS-SZP files) holds square Japanese glyphs, 257 cells per
set, with one advance for every glyph: its Latin letters are full-width. Stadium 1's archive has the
same cell geometry (16x10, 16x12, 16x16, 24x20, 24x24, 32x32) but starts each set file with a
0x90-byte advance table, then 0x91 Latin glyphs, so it fits Zero's slot without relocation.

Two functions are rewritten in place at exactly their retail size. The build pins each source file's
span, not its functions, so a recompiled file whose functions change size would shift the rest of the
file and break the calls other files make by address:

  func_8001A118 (font set registration)  stores file + 0x90 as the set's glyph base.
  func_80019F70 (glyph code mapping)  maps printable ASCII through D_8006081F, maps every other code
      to glyph 0, and copies the glyph's advance out of the table into the set's advance field, which
      the two glyph drawers already read once per character.

usage: fonts_en.py patch --rom build/pokestadium0-jp.z64 --us <us baserom.z64> [--out PATH]
       fonts_en.py check --rom build/pokestadium0-en.z64 --us <us baserom.z64>
       fonts_en.py selftest
"""

import argparse
import struct
import sys
from pathlib import Path

ZERO_FONTS = 0x2B2C80            # the BinArchive range func_8001A194 opens
ZERO_FONTS_END = 0x2E0BE0
ZERO_ASCII_MAP = 0x8006081F - 0x7FFFF400  # D_8006081F, read by func_80019F70
US_FONTS = 0x3BA190              # fonts_ROM_START in the Stadium 1 decompilation
US_ASCII_MAP = 0x8DE80           # 128-byte table whose A-Z and a-z entries increase
MAP_BYTES = 0x80
ADVANCES = 0x90
RDRAM_START = 0x80001000        # the font sheets are decompressed anywhere inside RDRAM
RDRAM_END = 0x803F0000
GLYPHS = 0x91
# Which stages touch which part; the narrow ones exist to bisect a screen-level fault.
INPLACE_STAGES = {'full', 'noremap'}          # the real patch: English payloads in Zero's own slots
ARCHIVE_STAGES = {'archive', 'data', 'data-keep', 'keep-map', 'keep-loader'}  # bisect: whole-archive swap
MAP_TABLE_STAGES = {'full', 'noremap', 'data', 'map', 'data-keep', 'keep-map'}
MAP_FUNC_STAGES = {'full', 'data', 'map', 'code', 'keep-map'}
LOADER_STAGES = {'full', 'noremap', 'code', 'loader', 'loader0', 'keep-loader'}
CELLS = [(0x10, 0x0A), (0x10, 0x0C), (0x10, 0x10), (0x18, 0x14), (0x18, 0x18), (0x20, 0x20)]

ROM_BIAS = 0x7FFFF400            # rom = vram - ROM_BIAS for the resident image
MAP_FUNC = 0x80019F70            # glyph code mapping, 0x120 bytes
LOAD_FUNC = 0x8001A118           # font set registration, 0x7C bytes

ZERO, AT, V0, V1, A0, A1, A2, A3 = 0, 1, 2, 3, 4, 5, 6, 7
T0, T1, T2, T3, T4, T5, T6, T7 = 8, 9, 10, 11, 12, 13, 14, 15
T8, T9, SP, RA = 24, 25, 29, 31


# --- instruction encoding (only the forms the patches use) -------------------------------------
def lui(rt, imm):
    return 0x3C000000 | (rt << 16) | (imm & 0xFFFF)


def addiu(rt, rs, imm):
    return 0x24000000 | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


def addu(rd, rs, rt):
    return (rs << 21) | (rt << 16) | (rd << 11) | 0x21


def sll(rd, rt, sa):
    return (rt << 16) | (rd << 11) | (sa << 6)


def sltiu(rt, rs, imm):
    return 0x2C000000 | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


def lw(rt, off, rs):
    return 0x8C000000 | (rs << 21) | (rt << 16) | (off & 0xFFFF)


def lbu(rt, off, rs):
    return 0x90000000 | (rs << 21) | (rt << 16) | (off & 0xFFFF)


def andi(rt, rs, imm):
    return 0x30000000 | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


def sw(rt, off, rs):
    return 0xAC000000 | (rs << 21) | (rt << 16) | (off & 0xFFFF)


def sb(rt, off, rs):
    return 0xA0000000 | (rs << 21) | (rt << 16) | (off & 0xFFFF)


def sltu(rd, rs, rt):
    return (rs << 21) | (rt << 16) | (rd << 11) | 0x2B


def beq(rs, rt, words):
    return 0x10000000 | (rs << 21) | (rt << 16) | (words & 0xFFFF)


def bne(rs, rt, words):
    return 0x14000000 | (rs << 21) | (rt << 16) | (words & 0xFFFF)


def jr(rs):
    return (rs << 21) | 0x08


NOP = 0


def hi(address):
    return ((address + 0x8000) >> 16) & 0xFFFF


def lo(address):
    return address & 0xFFFF


# --- the two patched functions ----------------------------------------------------------------
def words_at(rom, vram, count):
    return list(struct.unpack_from('>%dI' % count, rom, vram - ROM_BIAS))


def font_context_address(rom):
    """Address of the font_context global, taken from func_8001A118's own lui/addiu pair."""
    w = words_at(rom, LOAD_FUNC, 8)
    if (w[6] >> 26) != 0x0F or (w[7] >> 26) != 0x09:
        raise SystemExit('func_8001A118 does not load font_context first: unexpected build')
    low = struct.unpack('>h', struct.pack('>H', w[7] & 0xFFFF))[0]
    return ((w[6] & 0xFFFF) << 16) + low


def font_load_words(rom, shift=ADVANCES):
    """func_8001A118 with the glyph base moved `shift` bytes past the file start."""
    r = words_at(rom, LOAD_FUNC, 0x7C // 4)
    if (r[9] >> 26) != 0x23 or (r[9] & 0xFFFF) != 0x28:
        raise SystemExit('the arg4 spill in func_8001A118 moved: unexpected build')
    if (r[12] >> 26) != 0x2B:
        raise SystemExit('the set pointer store in func_8001A118 moved: unexpected build')
    out = r[0:12] + [addiu(T6, T6, shift), r[12]]              # set->tex = file + shift
    out += [r[14], sb(T9, 0, T8), r[18], sb(T2, 1, T8), r[22], sb(T5, 2, T8)]
    out += [r[25], r[26], r[27], r[28], r[29], r[30]]
    return out + [NOP] * (len(r) - len(out))


def english_payload(us, index, target_len):
    """One English font file, sized to decompress to exactly Zero's own set (target_len bytes).

    Zero's UI indexes glyphs up to 256, and its sets hold 257 cells; Stadium 1's hold 145. A set
    that decompresses smaller than Zero's makes those reads land outside the pool block - an address
    error mid-frame, which looks like a hang with the music still playing. So the English glyphs are
    followed by blank cells (0xF0, the value of Zero's own empty glyph) up to Zero's count.
    """
    import crunch64

    _, ufiles = archive_files(us, US_FONTS)
    off, size = ufiles[index]
    blob = us[US_FONTS + off:US_FONTS + off + size]
    data = crunch64.yay0.decompress(blob[struct.unpack_from('>I', blob, 8)[0]:])
    width, height = CELLS[index]
    cells = (len(data) - ADVANCES) // (width * height)
    out = data + b'\xF0' * (target_len - len(data))
    if len(out) != target_len:
        raise SystemExit('set %d is larger than Zero\'s (%#x > %#x)' % (index, len(data), target_len))
    body = crunch64.yay0.compress(out)
    return b'PERS-SZP' + struct.pack('>4I', 0x18, len(out), len(out), 0) + body, cells


def zero_set_len(rom, offset, size):
    """Decompressed length of one of Zero's own font files."""
    import crunch64
    blob = rom[offset:offset + size]
    return len(crunch64.yay0.decompress(blob[struct.unpack_from('>I', blob, 8)[0]:]))


def font_map_words(rom, ctx=None):
    """func_80019F70: printable ASCII through the Latin map, and that glyph's advance into the set.

    The advance table sits 0x90 bytes before the glyph base, inside each English font file. The font
    context block is never cleared, so a slot the screen did not load can hold stale data: the slot
    is range-checked and a null glyph base is skipped before anything is dereferenced.
    """
    ctx = font_context_address(rom) if ctx is None else ctx
    ascii_block = [
        lui(T2, hi(0x8006081F)),             # ret = map[c]
        addiu(T2, T2, lo(0x8006081F)),
        addu(T2, T2, A0),
        lbu(V0, 0, T2),
    ]
    store = [
        lui(T3, hi(ctx)),                    # font_context
        addiu(T3, T3, lo(ctx)),
        lw(T3, 0, T3),
        beq(T3, ZERO, 0),                    # no font context yet: skip the advance update
        NOP,
        lbu(T4, 0x38, T3),                   # the active set slot
        sltiu(AT, T4, 6),                    # outside the six registered sets: skip
        beq(AT, ZERO, 0),
        NOP,
        sll(T6, T4, 3),
        addu(T6, T3, T6),                    # &entries[slot]
        lw(T5, 0x4, T6),                     # entry->file is the glyph base
        lui(AT, hi(RDRAM_START)),            # the glyph base must be inside RDRAM, or the read below
        addiu(AT, AT, lo(RDRAM_START)),      # faults: unloaded slots hold values like 0x06003058
        sltu(AT, T5, AT),
        bne(AT, ZERO, 0),
        NOP,
        lui(AT, hi(RDRAM_END)),
        sltu(AT, T5, AT),
        beq(AT, ZERO, 0),
        NOP,
        addiu(T5, T5, -ADVANCES),            # its advance table sits 0x90 bytes before it
        addu(T5, T5, V0),
        lbu(T5, 0, T5),
        sb(T5, 0, T6),                       # entry->advance = table[glyph]
    ]
    tail = [jr(RA), NOP]
    head = [
        andi(A0, A0, 0xFFFF),                # the caller's u16 character code
        addu(V0, ZERO, ZERO),                # everything but printable ASCII is glyph 0
        sltiu(AT, A0, 0x7F),
        beq(AT, ZERO, 0),                    # >= 0x7F: store
        NOP,
        sltiu(AT, A0, 0x21),
        bne(AT, ZERO, 0),                    # < 0x21: store
        NOP,
    ]
    base = len(head) + len(ascii_block)
    head[3] = beq(AT, ZERO, base - 3 - 1)
    head[6] = bne(AT, ZERO, base - 6 - 1)
    tail_index = len(store)
    for index in (3, 7, 15, 19):
        assert (store[index] >> 26) in (0x04, 0x05), 'branch site %d moved' % index
        store[index] = (store[index] & ~0xFFFF) | ((tail_index - index - 1) & 0xFFFF)
    words = head + ascii_block + store + tail
    retail = words_at(rom, MAP_FUNC, 0x120 // 4)
    assert len(words) <= len(retail), 'map function outgrew its retail span'
    return words + [NOP] * (len(retail) - len(words))



# --- patch and check ---------------------------------------------------------------------------
def archive_files(rom, offset):
    total, count = struct.unpack_from('>4I', rom, offset)[2:]
    if count != len(CELLS):
        raise SystemExit('%#x: archive has %d files, expected %d' % (offset, count, len(CELLS)))
    return total, [struct.unpack_from('>4I', rom, offset + 0x10 + i * 0x10)[:2] for i in range(count)]


def map_is_latin(table):
    """Whether table[c] is a glyph index in the Latin range for A-Z and a-z, increasing."""
    upper, lower = table[0x41:0x5B], table[0x61:0x7B]
    return (all(upper[i] < upper[i + 1] for i in range(25))
            and all(lower[i] < lower[i + 1] for i in range(25))
            and max(upper) < GLYPHS and max(lower) < GLYPHS)


CIC_SEEDS = {'6101': 0xF8CA4DDC, '6102': 0xF8CA4DDC, '6103': 0xA3886759,
             '6105': 0xDF26F436, '6106': 0x1FEA617A}
CRC_LENGTH = 0x100000  # IPL3 checksums only the first megabyte of the ROM
M32 = 0xFFFFFFFF


def rom_crc(rom, seed):
    """IPL3's ROM checksum, ported from Project64's CN64Rom::CalculateRomCrc."""
    a3 = t2 = t3 = s0 = a2 = t4 = seed
    for t0 in range(0, CRC_LENGTH, 4):
        v0 = struct.unpack_from('>I', rom, 0x1000 + t0)[0]
        v1 = (a3 + v0) & M32
        if v1 < a3:
            t2 = (t2 + 1) & M32
        sa = v0 & 0x1F
        a0 = ((v0 << sa) | (v0 >> ((0x20 - sa) & 0x1F))) & M32
        a3 = v1
        t3 ^= v0
        s0 = (s0 + a0) & M32
        a2 = (a3 ^ v0 ^ a2) & M32 if a2 < v0 else (a2 ^ a0)
        t4 = ((v0 ^ s0) + t4) & M32
    if seed == CIC_SEEDS['6103']:
        return ((a3 ^ t2) + t3) & M32, ((s0 ^ a2) + t4) & M32
    if seed == CIC_SEEDS['6106']:
        return ((a3 * t2) + t3) & M32, ((s0 * a2) + t4) & M32
    return (a3 ^ t2 ^ t3) & M32, (s0 ^ a2 ^ t4) & M32


def detect_seed(rom):
    """The CIC seed of an untouched build, found by matching its header checksum."""
    stored = struct.unpack_from('>2I', rom, 0x10)
    seed = next((s for s in set(CIC_SEEDS.values()) if rom_crc(rom, s) == stored), None)
    if seed is None:
        raise SystemExit('unrecognised CIC: header checksum matches no known seed')
    return seed


def fix_checksum(rom, seed):
    """Rewrite 0x10/0x14 so IPL3's boot checksum accepts the patched ROM.

    Anything below 0x101000 changes the checksum; IPL3 halts on a mismatch, which is a black
    screen and no fault - so every patched ROM must be re-stamped.
    """
    computed = rom_crc(rom, seed)
    struct.pack_into('>2I', rom, 0x10, *computed)
    return computed


def patch(rom, us, stage='full'):
    """stage: full = archive + map + loader patch, data = archive + map, map = map only,
    archive = archive only. The narrower stages exist to bisect a boot fault."""
    """Returns rom with Stadium 1's font archive and map, and both function patches."""
    total, _ = archive_files(us, US_FONTS)
    current, _ = archive_files(rom, ZERO_FONTS)
    inplace = stage in INPLACE_STAGES
    if current == total and not inplace:
        raise SystemExit("the font slot already holds Stadium 1's archive: already patched?")
    if current != ZERO_FONTS_END - ZERO_FONTS:
        raise SystemExit('font slot (%#x bytes) is not this build\'s archive' % current)
    if total > ZERO_FONTS_END - ZERO_FONTS:
        raise SystemExit("Stadium 1's archive (%#x) does not fit Zero's slot (%#x)"
                         % (total, ZERO_FONTS_END - ZERO_FONTS))
    table = us[US_ASCII_MAP:US_ASCII_MAP + MAP_BYTES]
    if not map_is_latin(table):
        raise SystemExit('no ASCII glyph map at %#x in that dump' % US_ASCII_MAP)

    seed = detect_seed(rom)
    out = bytearray(rom)
    if stage in INPLACE_STAGES:
        # Write Stadium 1's payloads into Zero's own slots: the archive header (and so every file
        # offset, size and glyph count the UI code indexes) stays byte-identical to retail.
        _, zfiles = archive_files(rom, ZERO_FONTS)
        for index, (zoff, zsize) in enumerate(zfiles):
            payload, _ = english_payload(us, index, zero_set_len(rom, ZERO_FONTS + zoff, zsize))
            if len(payload) > zsize:
                raise SystemExit('English set %d does not fit Zero slot %#x (%#x)'
                                 % (index, zsize, len(payload)))
            out[ZERO_FONTS + zoff:ZERO_FONTS + zoff + zsize] = payload + bytes(zsize - len(payload))
    elif stage in ARCHIVE_STAGES:
        out[ZERO_FONTS:ZERO_FONTS + total] = us[US_FONTS:US_FONTS + total]
    if stage in ('data', 'archive'):
        # Bisect-only: clearing Zero's stale glyph data is not required (the archive header
        # defines every file's extent) and it is 0x1CFC0 bytes of real ROM, so 'full' keeps it.
        out[ZERO_FONTS + total:ZERO_FONTS_END] = bytes(ZERO_FONTS_END - ZERO_FONTS - total)
    if stage in MAP_TABLE_STAGES:
        out[ZERO_ASCII_MAP:ZERO_ASCII_MAP + MAP_BYTES] = table
    patches = []
    if stage in MAP_FUNC_STAGES:
        patches.append((MAP_FUNC, font_map_words(rom)))
    if stage == 'micro':
        # One commutative operand swap inside the retail loader: proves a code patch lands where the
        # CPU reads it, with no behavioural change at all.
        retail_words = words_at(rom, LOAD_FUNC, 0x7C // 4)
        assert (retail_words[11] & 0x3F) == 0x21, 'operand add expected'
        swap = (retail_words[11] & ~((0x1F << 21) | (0x1F << 16))) | (3 << 21) | (15 << 16)
        patches.append((LOAD_FUNC, retail_words[:11] + [swap] + retail_words[12:]))
    if stage in LOADER_STAGES:
        patches.insert(0, (LOAD_FUNC, font_load_words(rom, 0 if stage == 'loader0' else ADVANCES)))
    for vram, words in patches:
        struct.pack_into('>%dI' % len(words), out, vram - ROM_BIAS, *words)
    fix_checksum(out, seed)
    check(bytes(out), us, rom, stage, seed)
    return bytes(out)


def check(rom, us, retail, stage='full', seed=None):
    """Raises unless rom carries the English archive, its map and both function patches.

    retail is the unpatched build, the source of the instruction words the patches reuse.
    """
    total, files = archive_files(rom, ZERO_FONTS)
    if stage in INPLACE_STAGES:
        zfiles = archive_files(retail, ZERO_FONTS)[1]
        for index, (zoff, zsize) in enumerate(zfiles):
            payload, _ = english_payload(us, index, zero_set_len(retail, ZERO_FONTS + zoff, zsize))
            if rom[ZERO_FONTS + zoff:ZERO_FONTS + zoff + zsize] != payload + bytes(zsize - len(payload)):
                raise SystemExit('font payload %#x is not the English set' % zoff)
        if rom[ZERO_FONTS:ZERO_FONTS + 0x70] != retail[ZERO_FONTS:ZERO_FONTS + 0x70]:
            raise SystemExit("the font archive header changed")
    elif stage in ARCHIVE_STAGES:
        if rom[ZERO_FONTS:ZERO_FONTS + total] != us[US_FONTS:US_FONTS + total]:
            raise SystemExit("font archive differs from Stadium 1's")
    if stage in ('data', 'archive'):
        if rom[ZERO_FONTS + total:ZERO_FONTS_END].count(0) != ZERO_FONTS_END - ZERO_FONTS - total:
            raise SystemExit('font slot tail is not cleared')
    if stage in MAP_TABLE_STAGES:
        if rom[ZERO_ASCII_MAP:ZERO_ASCII_MAP + MAP_BYTES] != us[US_ASCII_MAP:US_ASCII_MAP + MAP_BYTES]:
            raise SystemExit("ASCII glyph map differs from Stadium 1's")
    if stage == 'micro':
        rw = words_at(retail, LOAD_FUNC, 0x7C // 4)
        expected_loader = rw[:11] + [(rw[11] & ~((0x1F << 21) | (0x1F << 16))) | (3 << 21) | (15 << 16)] + rw[12:]
    else:
        expected_loader = (font_load_words(retail, 0 if stage == 'loader0' else ADVANCES)
                           if stage in LOADER_STAGES
                           else words_at(retail, LOAD_FUNC, 0x7C // 4))
    if words_at(rom, LOAD_FUNC, 0x7C // 4) != expected_loader:
        raise SystemExit('the font loader patch is not in place')
    if rom_crc(rom, seed or detect_seed(retail)) != struct.unpack_from('>2I', rom, 0x10):
        raise SystemExit('header checksum does not match the patched ROM: IPL3 would hang')
    print('%s: font archive %#x bytes, glyph map %s, loader %s'
          % (stage, total, 'patched' if stage in MAP_FUNC_STAGES else 'retail',
             'patched' if stage in LOADER_STAGES else 'retail'))


def _retail_stub(rom):
    """A ROM image whose func_8001A118 words are the retail ones, for the self-test."""
    rom = bytearray(rom)
    w = [addiu(SP, SP, -0x18), 0xAFBF0014, 0xAFA5001C, 0xAFA60020, 0x0C000000, 0xAFA70024,
         lui(A0, 0x800B), addiu(A0, A0, -0x2E00), lw(T7, 0, A0), lw(T6, 0x28, SP), sll(V1, V0, 3),
         addu(T8, T7, V1), sw(T6, 4, T8), lw(T0, 0, A0), lw(T9, 0x1C, SP), addu(T1, T0, V1),
         sb(T9, 0, T1), lw(T3, 0, A0), lw(T2, 0x20, SP), addu(T4, T3, V1), sb(T2, 1, T4),
         lw(T7, 0, A0), lw(T5, 0x24, SP), addu(T6, T7, V1), sb(T5, 2, T6), lw(T8, 0, A0),
         sb(V0, 0x38, T8), 0x8FBF0014, addiu(SP, SP, 0x18), 0x03E00008, 0]
    struct.pack_into('>31I', rom, LOAD_FUNC - ROM_BIAS, *w)
    return rom


# --- interpreter used by the self-test ---------------------------------------------------------
def run_map_function(rom, code, ctx, set_base, tex, table, char, slot=0):
    """Runs the emitted mapper; returns (glyph, the advance it wrote to entry[slot]).

    table is the 0x90-byte advance table that sits 0x90 bytes before tex in every English font file.
    """
    mem = {ctx: struct.pack('>I', set_base),                # font_context
           set_base + 0x38: bytes([slot])}                  # unk_50 = the active slot
    if tex:
        mem[set_base + slot * 8 + 4] = struct.pack('>I', tex)
        for i, byte in enumerate(table):
            mem[tex - ADVANCES + i] = bytes([byte])
    regs = [0] * 32
    regs[A0] = char
    pc, steps = 0, 0

    def read(addr, size):
        if addr in mem:
            return mem[addr]
        if ZERO_ASCII_MAP <= addr - ROM_BIAS < ZERO_ASCII_MAP + MAP_BYTES:
            return rom[addr - ROM_BIAS:][:size]
        if set_base <= addr < set_base + 0x40:                # untouched entry slots read as zero
            return bytes(size)
        raise AssertionError('read of unmapped %#x' % addr)

    while steps < 200:
        steps += 1
        w = struct.unpack_from('>I', code, pc)[0]
        op, rs, rt, rd = w >> 26, (w >> 21) & 0x1F, (w >> 16) & 0x1F, (w >> 11) & 0x1F
        imm = struct.unpack('>h', struct.pack('>H', w & 0xFFFF))[0]
        pc += 4
        if w == 0:
            continue
        if op == 0x0F:
            regs[rt] = (w & 0xFFFF) << 16
        elif op == 0x09:
            regs[rt] = (regs[rs] + imm) & 0xFFFFFFFF
        elif op == 0x0C:
            regs[rt] = regs[rs] & (w & 0xFFFF)
        elif op == 0x0B:
            regs[rt] = 1 if regs[rs] < (w & 0xFFFF) else 0
        elif op == 0x04:
            pc += imm * 4 if regs[rs] == regs[rt] else 0
        elif op == 0x05:
            pc += imm * 4 if regs[rs] != regs[rt] else 0
        elif op == 0x23:
            regs[rt] = struct.unpack('>I', read(regs[rs] + imm, 4))[0]
        elif op == 0x24:
            regs[rt] = read(regs[rs] + imm, 1)[0]
        elif op == 0x28:
            mem[regs[rs] + imm] = bytes([regs[rt] & 0xFF])
        elif op == 0x00:
            fn = w & 0x3F
            if fn == 0x21:
                regs[rd] = (regs[rs] + regs[rt]) & 0xFFFFFFFF
            elif fn == 0x00:
                regs[rd] = (regs[rt] << ((w >> 6) & 0x1F)) & 0xFFFFFFFF
            elif fn == 0x2B:
                regs[rd] = 1 if regs[rs] < regs[rt] else 0
            elif fn == 0x08:
                return regs[V0], mem.get(set_base + slot * 8, b'\x00')[0]
            else:
                raise AssertionError('unhandled funct %#x' % fn)
        else:
            raise AssertionError('unhandled opcode %#x' % op)
    raise AssertionError('the mapping function did not return')


def run_load_function(rom, code, ctx, sp, index, args, file_ptr):
    """Interprets the patched font-set registration; returns the set's 8 bytes and unk_50."""
    mem = {ctx: struct.pack('>I', 0x80100000), sp + 0x10: struct.pack('>I', file_ptr)}
    regs = [0] * 32
    regs[SP] = sp
    regs[A1], regs[A2], regs[A3] = args
    pc = 0
    for _ in range(300):
        w = struct.unpack_from('>I', code, pc)[0]
        op, rs, rt, rd = w >> 26, (w >> 21) & 0x1F, (w >> 16) & 0x1F, (w >> 11) & 0x1F
        imm = struct.unpack('>h', struct.pack('>H', w & 0xFFFF))[0]
        pc += 4
        if w == 0:
            continue
        if op == 0x03:                                   # jal: only func_8001A0A4, which picks the slot
            regs[V0] = index
        elif op == 0x0F:
            regs[rt] = (w & 0xFFFF) << 16
        elif op == 0x09:
            regs[rt] = (regs[rs] + imm) & 0xFFFFFFFF
        elif op == 0x23:
            raw = mem.get(regs[rs] + imm)
            assert raw is not None, 'read of unmapped %#x' % (regs[rs] + imm)
            regs[rt] = struct.unpack('>I', raw)[0]
        elif op == 0x28:                                 # sb
            mem[regs[rs] + imm] = bytes([regs[rt] & 0xFF])
        elif op == 0x2B:                                 # sw
            mem[regs[rs] + imm] = struct.pack('>I', regs[rt] & 0xFFFFFFFF)
        elif op == 0x00:
            fn = w & 0x3F
            if fn == 0x21:
                regs[rd] = (regs[rs] + regs[rt]) & 0xFFFFFFFF
            elif fn == 0x00:
                regs[rd] = (regs[rt] << ((w >> 6) & 0x1F)) & 0xFFFFFFFF
            elif fn == 0x08:
                set_ptr = 0x80100000 + index * 8
                set_bytes = (mem.get(set_ptr, b'\x00')[0], mem.get(set_ptr + 1, b'\x00')[0],
                             mem.get(set_ptr + 2, b'\x00')[0],
                             struct.unpack('>I', mem.get(set_ptr + 4, b'\x00' * 4))[0])
                return set_bytes, mem.get(0x80100000 + 0x38, b'\x00')[0]
            else:
                raise AssertionError('unhandled funct %#x' % fn)
        else:
            raise AssertionError('unhandled opcode %#x' % op)
    raise AssertionError('the loader did not return')


def selftest():
    table = bytearray(MAP_BYTES)
    for i in range(26):
        table[0x41 + i] = 26 + i
        table[0x61 + i] = 69 + i
    assert map_is_latin(table)
    broken = bytearray(table)
    broken[0x50] = 0
    assert not map_is_latin(broken), 'a broken map was accepted'

    advance = bytearray(ADVANCES)
    advance[0], advance[26], advance[77] = 4, 7, 3          # space, A, i
    rom = bytearray(ZERO_FONTS_END)
    rom[ZERO_ASCII_MAP:ZERO_ASCII_MAP + MAP_BYTES] = table
    words = font_map_words(rom, ctx=0x8006d200)
    code = struct.pack('>%dI' % len(words), *words)
    cases = ((0x41, 0, 0x80200000, (26, 7)), (0x69, 0, 0x80200000, (77, 3)),
             (0x20, 0, 0x80200000, (0, 4)), (0x2421, 0, 0x80200000, (0, 4)),
             (0x41, 0, 0, (26, 0)),                          # set not loaded: no read, no write
             (0x41, 0, 0x06003058, (26, 0)),                 # stale slot, the value the save state holds
             (0x41, 0, 0x80500000, (26, 0)),                 # above RDRAM
             (0x41, 9, 0x80200000, (26, 0)))                 # slot out of range: untouched
    for char, slot, tex, expected in cases:
        got = run_map_function(rom, code, 0x8006d200, 0x80100000, tex, advance, char, slot)
        assert got == expected, (hex(char), slot, hex(tex), got, expected)
    # The loader patch, interpreted: set 2 gets file+0x90, its three size bytes, and slot 2.
    rom2 = bytearray(0x2E0000)
    code2 = struct.pack('>%dI' % 31, *font_load_words(_retail_stub(rom2)))
    set_bytes, slot = run_load_function(rom2, code2, 0x800AD200, 0x800FF000, 2, (10, 10, 16), 0x80400000)
    assert set_bytes == (10, 10, 16, 0x80400090), set_bytes      # advance, height, width, glyph base
    assert slot == 2, slot
    print('selftest ok')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('command', choices=['patch', 'check', 'selftest'])
    ap.add_argument('--rom', default='build/pokestadium0-jp.z64')
    ap.add_argument('--us', help='Stadium 1 US baserom.z64, the source of the English font')
    ap.add_argument('--out')
    ap.add_argument('--stage', choices=['full', 'noremap', 'inplace', 'data', 'data-keep', 'keep-map', 'keep-loader', 'code', 'map', 'archive', 'loader', 'loader0', 'micro'], default='full',
                    help='full: archive + map + loader; data: archive + map; code: map + loader; '
                         'map/archive: one of them (bisecting a boot fault)')
    ap.add_argument('--base', default='build/pokestadium0-jp.z64',
                    help='the unpatched build, checked against the patch')
    args = ap.parse_args()
    if args.command == 'selftest':
        selftest()
        return
    if not args.us:
        raise SystemExit('--us is required: the English glyphs come from the Stadium 1 dump')
    rom, us = Path(args.rom).read_bytes(), Path(args.us).read_bytes()
    if args.command == 'patch':
        out = Path(args.out or 'build/pokestadium0-en.z64')
        out.write_bytes(patch(rom, us, args.stage))
        print('patched %s' % out)
    else:
        check(rom, us, Path(args.base).read_bytes())


if __name__ == '__main__':
    main()
