#!/usr/bin/env python3
"""Relocatable C/assembly ROM build, with separately retained opaque assets.

No original owner bytes survive in the extracted image assets. Every owner
comes from a compiler or assembler object placed by the image linker script.
"""
import argparse
import bisect
from collections import Counter
import csv
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess
import sys

from map_fragment_sections import load_image
from map_rom import EXPECTED_SHA256, trace_yay0
from m2c_easiest import FLAGS, TYPES

ROOT = Path(__file__).resolve().parents[1]
ASSETS = ROOT / 'assets/production'
BUILD = ROOT / 'build/production'
SOURCE_REGISTRY = ROOT / 'config/jp/sources.json'
# src/ file -> {section: link address} for object data placed at its ROM address.
SECTION_REGISTRY = ROOT / 'config/jp/sections.json'
# src/ file -> {section: retail size}; written by a matching build, read by the others.
SIZE_REGISTRY = ROOT / 'config/jp/section_sizes.json'
# The one fragment that other fragments reach through relocations (checked against retail).
SHARED_SLOT = 0x82100000
# Names that carry their own retail address.
ADDRESS = re.compile(r'(?:func_|D_(?:(?:FLT|DBL|STR)_)?|jtbl_|T_|\.L)([0-9A-F]{8})(?:_\d+)?')
SOURCE_FLAGS = ['-c', '-G', '0', '-non_shared', '-Xcpluscomm', '-nostdinc', '-Wab,-r4300_mul',
                '-w', '-D_MIPS_SZLONG=32', '-DNDEBUG', '-D_FINALROM', '-DN_MICRO', '-DF3DEX_GBI_2',
                '-DBUILD_VERSION=VERSION_I_P', '-DLANGUAGE_C', '-D_LANGUAGE_C', '-DVERSION_JP=1',
                '-Iinclude', '-Isrc', '-I.', '-Ilib/ultralib/include', '-Ilib/ultralib/include/PR',
                '-Ilib/ultralib/include/ido']
# Files with "profile": "ultralib" include an unmodified lib/ultralib source and
# build it with ultralib's own IDO flags for 2.0I libultra_rom (not 2.0I_P: seteventmesg,
# sethwinterrupt and cartrominit only match the 2.0I code).
ULTRALIB_FLAGS = ['-c', '-Wab,-r4300_mul', '-G', '0', '-nostdinc', '-Xcpluscomm', '-w',
                  '-D_MIPS_SZLONG=32', '-DF3DEX_GBI', '-DBUILD_VERSION=6',
                  '-DBUILD_VERSION_STRING="2.0I"', '-non_shared', '-DNDEBUG', '-D_FINALROM',
                  '-I.', '-Ilib/ultralib/include', '-Ilib/ultralib/include/ido',
                  '-Ilib/ultralib/include/PR']
ULTRALIB_ASM_FLAGS = ['-c', '-Wab,-r4300_mul', '-G', '0', '-nostdinc',
                      '-woff', '516,649,838,712', '-D_MIPS_SZLONG=32',
                      '-DF3DEX_GBI', '-DBUILD_VERSION=6', '-non_shared',
                      '-DNDEBUG', '-D_FINALROM', '-I.',
                      '-Ilib/ultralib/include', '-Ilib/ultralib/include/PR']
PRAGMA = re.compile(r'(#pragma\s+GLOBAL_ASM\(\s*")([^"]+)("\s*\))')
LISTING = re.compile(r'/\*\s+[0-9A-F]+\s+([0-9A-F]+)\s+([0-9A-F]{8})\s*\*/\s*(.*)')
# Address operands the generated listings left as numbers: "vram word" -> (operand, symbol).
# The relocation check of a matching build fails for any that are missing here.
LISTING_FIXES = {'8111C17C 3C088112': ('(0x81120000 >> 16)', '%hi(T_8111BC18)'),
                 '8111C190 2508BC18': ('-0x43E8', '%lo(T_8111BC18)')}
MACROS = '''.set noreorder
.set noat
.set gp=64
.macro nonmatching name, size
.endm
.macro glabel name
.globl \\name
.type \\name, @function
\\name:
.endm
.macro alabel name
.globl \\name
\\name:
.endm
.macro endlabel name
.size \\name, . - \\name
.endm
'''


def sha(data):
    return hashlib.sha256(data).hexdigest()


def run(argv):
    result = subprocess.run([str(x) for x in argv], cwd=ROOT, capture_output=True)
    if result.returncode:
        raise RuntimeError(' '.join(map(str, argv)) + '\n' + result.stderr.decode() + result.stdout.decode())
    return result.stdout


def tokens(packed):
    """Yield literal positions and backreferences in a validated Yay0 stream."""
    size, links, literals = struct.unpack_from('>3I', packed, 4)
    mask_cursor, mask, remaining, output = 16, 0, 0, 0
    while output < size:
        if not remaining:
            mask = struct.unpack_from('>I', packed, mask_cursor)[0]
            mask_cursor += 4
            remaining = 32
        if mask & 0x80000000:
            yield output, literals, 1, 0
            literals += 1
            output += 1
        else:
            value = struct.unpack_from('>H', packed, links)[0]
            links += 2
            length = value >> 12
            distance = (value & 4095) + 1
            if not length:
                length = packed[literals] + 18
                literals += 1
            else:
                length += 2
            yield output, None, length, distance
            output += length
        remaining -= 1
        mask = (mask << 1) & 0xFFFFFFFF


def storage_template(stored):
    """Retain compression topology, erase every encoded image literal/override."""
    offset, size, _, count = struct.unpack_from('>4I', stored, 8)
    decoded, _ = trace_yay0(stored[offset:])
    if len(decoded) != size:
        raise ValueError('wrapper decoded length differs')
    template = bytearray(stored)
    placeholders = []
    for index in range(count):
        position = struct.unpack_from('>I', stored, 28 + index * 8)[0]
        placeholders.append([position, decoded[position:position + 4].hex()])
        template[24 + index * 8:28 + index * 8] = bytes(4)
    for _, literal, _, _ in tokens(stored[offset:]):
        if literal is not None:
            template[offset + literal] = 0
    return bytes(template), placeholders


def encode_image(image, template, placeholders):
    """Re-emit literals from rebuilt bytes using the original compression plan.

    A changed backreference must fail, rather than silently retaining old code.
    This preserves retail storage identity without guessing a compressor lineage.
    """
    result = bytearray(template)
    offset, size, _, count = struct.unpack_from('>4I', result, 8)
    if len(image) != size:
        raise ValueError('fixed-layout decoded image changed size')
    decoded = bytearray(image)
    if len(placeholders) != count:
        raise ValueError('restoration count differs')
    for index, (position, original) in enumerate(placeholders):
        if struct.unpack_from('>I', result, 28 + index * 8)[0] != position:
            raise ValueError('restoration position differs')
        result[24 + index * 8:28 + index * 8] = decoded[position:position + 4]
        decoded[position:position + 4] = bytes.fromhex(original)
    for output, literal, length, distance in tokens(template[offset:]):
        if literal is not None:
            result[offset + literal] = decoded[output]
        else:
            if distance > output or output + length > len(decoded):
                raise ValueError('invalid retained compression plan')
            for index in range(length):
                if decoded[output + index] != decoded[output + index - distance]:
                    raise ValueError('changed image cannot use retained Yay0 backreference')
    restored, _ = trace_yay0(result[offset:])
    restored = bytearray(restored)
    for index, (position, _) in enumerate(placeholders):
        restored[position:position + 4] = result[24 + index * 8:28 + index * 8]
    if restored != image:
        raise ValueError('encoded image does not restore to linked image')
    return bytes(result)


def extract():
    rom = (ROOT / 'baseroms/jp/baserom.z64').read_bytes()
    if sha(rom) != EXPECTED_SHA256:
        raise ValueError('wrong input ROM')
    mapping = json.loads((ROOT / 'docs/mappings/resident-fragments.json').read_text())
    inventory = json.loads((ROOT / 'docs/pragma-inventory.json').read_text())
    ASSETS.mkdir(parents=True, exist_ok=True)
    groups = []
    specifications = [('resident', None, 0, 0x80C00, 0x7FFFF400, rom[:0x80C00], None)]
    for index, meta in enumerate(mapping['fragments']):
        specifications.append((f'fragment{index:03}', index, int(meta['rom_start'], 0),
                               int(meta['rom_consumed_end'], 0), int(meta['link_base'], 0),
                               load_image(rom, meta), meta))
    for name, index, start, end, base, image, meta in specifications:
        owners = [r for r in inventory['owners'] if r['image_index'] == index]
        image_assets = bytearray(image)
        cursor = 0
        for row in sorted(owners, key=lambda r: int(r['start'], 0)):
            begin, stop = int(row['start'], 0), int(row['end'], 0)
            if begin < cursor or sha(image[begin:stop]) != row['input_sha256']:
                raise ValueError('owner overlap or input mismatch')
            image_assets[begin:stop] = bytes(stop - begin)
            cursor = stop
        (ASSETS / f'{name}.bin').write_bytes(image_assets)
        group = dict(name=name, image_index=index, rom_start=start, rom_end=end,
                     base=base, size=len(image), expected_sha256=sha(image),
                     asset_sha256=sha(image_assets), owners=owners,
                     storage='raw' if meta is None else meta['storage'])
        if group['storage'] != 'raw':
            template, placeholders = storage_template(rom[start:end])
            (ASSETS / f'{name}.storage').write_bytes(template)
            group.update(placeholders=placeholders, template_sha256=sha(template))
        groups.append(group)
    gaps = []
    cursor = 0
    for group in groups:
        if group['rom_start'] > cursor:
            name = f'opaque_{cursor:X}.bin'
            data = rom[cursor:group['rom_start']]
            (ASSETS / name).write_bytes(data)
            gaps.append(dict(start=cursor, end=group['rom_start'], asset=name, sha256=sha(data)))
        if group['rom_start'] < cursor:
            raise ValueError('ROM storage overlap')
        cursor = group['rom_end']
    if cursor < len(rom):
        name = f'opaque_{cursor:X}.bin'
        data = rom[cursor:]
        (ASSETS / name).write_bytes(data)
        gaps.append(dict(start=cursor, end=len(rom), asset=name, sha256=sha(data)))
    manifest = dict(input_sha256=EXPECTED_SHA256, size=len(rom), groups=groups, gaps=gaps)
    (ASSETS / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    print(f'Extracted {len(groups)} images; erased {len(inventory["owners"])} code-owner ranges from opaque assets', flush=True)


def canonical_assembly(text):
    """Disambiguate assembler aliases; never substitute raw instruction words."""
    lines = []
    controls = dict(Index=0, Random=1, EntryLo0=2, EntryLo1=3, Context=4,
                    PageMask=5, Wired=6, BadVaddr=8, Count=9, EntryHi=10,
                    Compare=11, Status=12, Cause=13, EPC=14, PRId=15,
                    Config=16, LLAddr=17, WatchLo=18, WatchHi=19,
                    XContext=20, ParityError=26, CacheErr=27, TagLo=28,
                    TagHi=29, ErrorEPC=30, FpcCsr=31, FpcIrr=0)
    for line in text.splitlines():
        match = LISTING.search(line)
        if match:
            if match[1] + ' ' + match[2] in LISTING_FIXES:
                line = line.replace(*LISTING_FIXES[match[1] + ' ' + match[2]])
                match = LISTING.search(line)
            value = int(match[2], 16)
            mnemonic = match[3].split()[0]
            instruction = match[3].split('/*', 1)[0].strip()
            operands = instruction.split(None, 1)
            operands = [part.strip() for part in operands[1].split(',')] if len(operands) > 1 else []
            replacement = None
            if mnemonic == 'move':
                if value & 63 not in (33, 37) or len(operands) != 2:
                    raise ValueError('unsupported move alias')
                opcode = 'or' if value & 63 == 37 else 'addu'
                dest, source = operands
                sources = f'$zero, {source}' if (value >> 21) & 31 == 0 else f'{source}, $zero'
                replacement = f'{opcode} {dest}, {sources}'
            elif mnemonic in ('div', 'divu') and value >> 26 == 0 and len(operands) == 2:
                replacement = f'{mnemonic} $0, {operands[0]}, {operands[1]}'
            elif mnemonic in ('cfc1', 'ctc1', 'mfc0', 'mtc0', 'dmfc0', 'dmtc0'):
                if len(operands) == 2 and operands[1].lstrip('$') in controls:
                    replacement = f'{mnemonic} {operands[0]}, ${controls[operands[1].lstrip("$")]}'
            if replacement:
                line = line[:match.start(3)] + replacement
            if mnemonic in ('dmfc1', 'dmtc1'):
                lines.extend(['.set fp=64', line, '.set fp=32'])
                continue
        lines.append(line)
    return '\n'.join(lines) + '\n'


def trim_text(obj, name, size):
    """Remove assembler alignment padding after a lone C function, keeping relocations."""
    data = bytearray(obj.read_bytes())
    if data[:6] != b'\x7fELF\x01\x02':
        raise ValueError('expected big-endian ELF32')
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    positions = [header[6] + i * header[11] for i in range(header[12])]
    sections = [struct.unpack_from('>IIIIIIIIII', data, p) for p in positions]
    table = sections[header[13]]
    strings = data[table[4]:table[4] + table[5]]
    found = False
    for section in sections:
        if section[1] != 2:
            continue
        names_section = sections[section[6]]
        names = data[names_section[4]:names_section[4] + names_section[5]]
        for offset in range(section[4], section[4] + section[5], section[9]):
            index, value, symbol_size, info, _, _ = struct.unpack_from('>IIIBBH', data, offset)
            if names[index:].split(b'\0', 1)[0].decode() == name and info & 15 == 2:
                if value != 0 or symbol_size != size:
                    raise ValueError('C function symbol size differs: ' + name)
                found = True
    if not found:
        raise ValueError('C function symbol missing: ' + name)
    for position, section in zip(positions, sections):
        section_name = strings[section[0]:].split(b'\0', 1)[0]
        if section_name == b'.text':
            if section[5] < size or any(data[section[4] + size:section[4] + section[5]]):
                raise ValueError('C function is oversized or has nonzero trailing content: ' + name)
            struct.pack_into('>I', data, position + 20, size)
            struct.pack_into('>I', data, position + 32, 4)
            obj.write_bytes(data)
            return
    raise ValueError('no C text section')


def trim_file_text(obj, size, after=b'', strict=True):
    """Trim IDO's trailing .text alignment of a source file to its owner span.

    The last owner of a file can carry more trailing padding than the object
    emits; that remainder comes from the erased (zero) owner bytes and is
    checked by the image comparison like everything else.

    after holds the image bytes that follow the span. Owner ranges stop at the
    last reachable instruction, so a file whose last function ends in an
    endless loop carries that function's dead epilogue past the span; those
    bytes may be trimmed too when they equal the image bytes, which the gap
    after the span then supplies.
    """
    return trim_section(obj, '.text', size, after, strict)


def trim_section(obj, name, size, after=b'', strict=True):
    """Shorten a section to at most size bytes.

    Only zero bytes, or bytes equal to after (the image bytes past size), may be removed.
    A section holding more than that is an error when strict, and is otherwise left whole.
    """
    data = bytearray(obj.read_bytes())
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    positions = [header[6] + i * header[11] for i in range(header[12])]
    sections = [struct.unpack_from('>IIIIIIIIII', data, p) for p in positions]
    table = sections[header[13]]
    strings = data[table[4]:table[4] + table[5]]
    for position, section in zip(positions, sections):
        if strings[section[0]:].split(b'\0', 1)[0] == name.encode():
            extra = bytes(data[section[4] + size:section[4] + section[5]])
            if section[1] != 8 and any(extra) and extra != bytes(after[:len(extra)]):
                if strict:
                    raise ValueError(f'{obj.name}: {name} is 0x{section[5]:X} bytes, owners span 0x{size:X}')
                return section[5]
            size = min(size, section[5])
            struct.pack_into('>I', data, position + 20, size)
            struct.pack_into('>I', data, position + 32, 4)
            obj.write_bytes(data)
            return size
    raise ValueError(f'no {name} section in {obj.name}')


def sdk_assembly_source(path, flags):
    """Validate an include-only wrapper for an original ultralib assembly file."""
    source = flags.get('assembly_source', '')
    if (not source.startswith('lib/ultralib/src/') or Path(source).suffix != '.s'
            or '..' in Path(source).parts or not (ROOT / source).is_file()):
        raise ValueError('invalid original SDK assembly source: ' + source)
    wrapper = re.sub(r'/\*.*?\*/|//[^\n]*', '',
                     (ROOT / path).read_text(), flags=re.S).strip()
    if wrapper != '#include "' + source + '"':
        raise ValueError('SDK assembly wrapper must include only ' + source)
    return source


def normalize_sdk_symbols(obj):
    """Put IDO assembler ELF symbols in standard local/global order.

    Only symbol-table metadata and relocation symbol indices change. The
    original assembled instructions, data, offsets, and addends are retained.
    """
    data = bytearray(obj.read_bytes())
    if data[:6] != b'\x7fELF\x01\x02':
        raise ValueError('expected big-endian ELF32 SDK object')
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    positions = [header[6] + i * header[11] for i in range(header[12])]
    sections = [struct.unpack_from('>IIIIIIIIII', data, p) for p in positions]
    for index, table in enumerate(sections):
        if table[1] != 2:  # SHT_SYMTAB
            continue
        if table[9] != 16 or table[5] % 16:
            raise ValueError('invalid SDK symbol-table entry size')
        entries = [bytes(data[p:p + 16])
                   for p in range(table[4], table[4] + table[5], 16)]
        locals_ = [i for i, entry in enumerate(entries) if entry[12] >> 4 == 0]
        globals_ = [i for i, entry in enumerate(entries) if entry[12] >> 4 != 0]
        order = locals_ + globals_
        remap = {old: new for new, old in enumerate(order)}
        data[table[4]:table[4] + table[5]] = b''.join(entries[i] for i in order)
        struct.pack_into('>I', data, positions[index] + 28, len(locals_))
        for position, section in zip(positions, sections):
            if section[6] != index:
                continue
            if section[1] in (4, 9):  # SHT_RELA / SHT_REL
                step = 12 if section[1] == 4 else 8
                for offset in range(section[4], section[4] + section[5], step):
                    info = struct.unpack_from('>I', data, offset + 4)[0]
                    struct.pack_into('>I', data, offset + 4,
                                     (remap[info >> 8] << 8) | (info & 255))
            elif section[1] == 17:  # SHT_GROUP signature symbol
                struct.pack_into('>I', data, position + 28, remap[section[7]])
    obj.write_bytes(data)


def compile_source_file(path, directory, compilers, prefix):
    """Compile a whole registered file with its C or original SDK assembly recipe.

    GLOBAL_ASM owners use the same normalized listings as assembly owners.
    """
    overrides = json.loads((ROOT / 'tools/cflags_overrides.json').read_text())
    flags = overrides.get(path, {})
    stem = path[len('src/'):-2].replace('/', '__')
    obj = directory / (stem + '.o')
    if flags.get('profile') == 'ultralib-asm':
        sdk_assembly_source(path, flags)
        unit = directory / (stem + '.s')
        unit.write_text((ROOT / path).read_text())
        run([compilers[flags.get('ido', '5.3')], *ULTRALIB_ASM_FLAGS,
             flags.get('opt', '-O1'), flags.get('mips', '-mips2'),
             *flags.get('extra', []), '-o', obj, unit])
        normalize_sdk_symbols(obj)
        return obj
    canon = BUILD / 'listings'

    def canonical(match):
        listing = canon / match[2]
        if not listing.exists():
            listing.parent.mkdir(parents=True, exist_ok=True)
            listing.write_text(canonical_assembly((ROOT / match[2]).read_text()))
        return match[1] + str(listing.relative_to(ROOT)) + match[3]

    unit = directory / (stem + '.c')
    unit.write_text(PRAGMA.sub(canonical, (ROOT / path).read_text(encoding='utf-8')), encoding='utf-8')
    if flags.get('profile') == 'ultralib':
        # No GLOBAL_ASM (and -O3, which asm-processor does not take): plain IDO.
        run([compilers[flags.get('ido', '7.1')], *ULTRALIB_FLAGS, flags.get('opt', '-O2'),
             flags.get('mips', '-mips2'), *flags.get('extra', []), '-o', obj, unit])
        return obj
    run([sys.executable, 'tools/asm-processor/build.py', '--asm-prelude', 'tools/asm_prelude.inc',
         '--input-enc', 'utf-8', '--output-enc', 'euc-jp', compilers[flags.get('ido', '7.1')], '--',
         prefix + 'as', '-march=vr4300', '-32', '-G0', '-EB', '--',
         *(ULTRALIB_FLAGS if flags.get('profile') == 'ultralib' else SOURCE_FLAGS),
         flags.get('opt', '-O2'), flags.get('mips', '-mips2'), *flags.get('extra', []),
         '-I' + str(Path(path).parent), '-o', obj, unit])
    return obj


def object_sections(obj):
    """Section name -> (size, type) of an ELF32 big-endian object."""
    data = obj.read_bytes()
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    positions = [header[6] + i * header[11] for i in range(header[12])]
    sections = [struct.unpack_from('>IIIIIIIIII', data, p) for p in positions]
    table = sections[header[13]]
    strings = data[table[4]:table[4] + table[5]]
    return {strings[s[0]:].split(b'\0', 1)[0].decode(): (s[5], s[1]) for s in sections}


def link_symbols(objects):
    """Resolve actual allocated-section references, not unused symbol-table entries.

    IDO's native assembler retains undefined numeric-label names with no
    relocations. They require no linker address and do not represent code.
    """
    from elftools.elf.elffile import ELFFile
    from elftools.elf.relocation import RelocationSection
    defined, referenced = set(), set()
    for obj in objects:
        with obj.open('rb') as handle:
            elf = ELFFile(handle)
            table = elf.get_section_by_name('.symtab')
            if table is not None:
                defined.update(symbol.name for symbol in table.iter_symbols()
                               if symbol['st_shndx'] != 'SHN_UNDEF'
                               and symbol['st_info']['bind'] in ('STB_GLOBAL', 'STB_WEAK'))
            for section in elf.iter_sections():
                if not isinstance(section, RelocationSection):
                    continue
                target = elf.get_section(section['sh_info'])
                if not target['sh_flags'] & 2:  # SHF_ALLOC; other sections are discarded.
                    continue
                symbols = elf.get_section(section['sh_link'])
                for relocation in section.iter_relocations():
                    symbol = symbols.get_symbol(relocation['r_info_sym'])
                    if symbol['st_shndx'] == 'SHN_UNDEF':
                        referenced.add(symbol.name)
    return defined, referenced - defined


def read_elf(data):
    """(section names, section headers, [(symbol, value, section name)]) of a big-endian ELF32."""
    header = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    raw = [struct.unpack_from('>10I', data, header[6] + i * header[11]) for i in range(header[12])]

    def text(table, index):
        start = raw[table][4] + index
        return data[start:data.index(b'\0', start)].decode()
    names = [text(header[13], section[0]) for section in raw]
    symbols = []
    for section in raw:
        if section[1] == 2:  # SHT_SYMTAB
            for position in range(section[4], section[4] + section[5], 16):
                name, value, _, _, _, index = struct.unpack_from('>IIIBBH', data, position)
                symbols.append((text(section[6], name), value,
                                names[index] if 0 < index < len(raw) else None))
    return names, raw, symbols


def fix_checksum(rom):
    """Restamp the header checksum (0x10) that the CIC 6103 boot code checks.

    It covers the first megabyte after the boot code; a mismatch halts on a black screen.
    Ported from Project64's CN64Rom::CalculateRomCrc.
    """
    a3 = t2 = t3 = s0 = a2 = t4 = 0xA3886759  # the 6103 seed
    for v0 in struct.unpack_from('>262144I', rom, 0x1000):
        v1 = (a3 + v0) & 0xFFFFFFFF
        if v1 < a3:
            t2 = (t2 + 1) & 0xFFFFFFFF
        sa = v0 & 0x1F
        a0 = ((v0 << sa) | (v0 >> ((0x20 - sa) & 0x1F))) & 0xFFFFFFFF
        a3 = v1
        t3 ^= v0
        s0 = (s0 + a0) & 0xFFFFFFFF
        a2 = (a3 ^ v0 ^ a2) & 0xFFFFFFFF if a2 < v0 else (a2 ^ a0)
        t4 = ((v0 ^ s0) + t4) & 0xFFFFFFFF
    struct.pack_into('>2I', rom, 0x10, ((a3 ^ t2) + t3) & 0xFFFFFFFF, ((s0 ^ a2) + t4) & 0xFFFFFFFF)


def in_fragment_space(address):
    """Memmap_GetFragmentVaddr only translates this range."""
    return 0x81000000 <= address < 0x90000000


class Image:
    """One independently linked image: the resident code or a fragment.

    Nothing is pinned to its retail address. Each piece (an owner, a placed
    object section or a run of asset bytes) follows the previous one, keeping
    its retail alignment, so a piece that grows moves everything after it.
    Every reference to a retail address is a symbol that the linker script
    binds to the piece holding that address; pointers inside asset bytes are
    emitted as such symbols too. A fragment's relocation table is rebuilt from
    the relocations the linker applied.
    """
    # The resident entry sets up BSS, the stack and the first call with raw
    # instructions that no owner covers; these are its address operands.
    ENTRY = {0x1000: 'lui $t0, %hi(T_80080000)', 0x1008: 'addiu $t0, $t0, %lo(T_80080000)',
             0x1024: 'lui $t2, %hi(T_80000550)', 0x1028: 'lui $sp, %hi(T_80080400)',
             0x102C: 'addiu $t2, $t2, %lo(T_80000550)', 0x1034: 'addiu $sp, $sp, %lo(T_80080400)'}
    RESIDENT_DATA = 0x60280  # ROM offset of the first resident data symbol, after the RSP microcode
    RESIDENT_BSS = 0x85360   # cleared by the entry code; the size is an immediate there

    def __init__(self, group, selected, cc, prefix, compare, files, compilers, symbols, placements,
                 sizes, names, resident_addresses, shift=0, directory=None):
        self.group, self.name, self.base = group, group['name'], group['base']
        self.prefix, self.compare, self.symbols, self.shift = prefix, compare, symbols, shift
        self.directory = directory or BUILD / self.name
        self.directory.mkdir(parents=True, exist_ok=True)
        self.asset = (ASSETS / (self.name + '.bin')).read_bytes()
        self.fragment = group['image_index'] is not None
        if self.fragment:
            self.content, _, self.ram = struct.unpack_from('>3I', self.asset, 0x14)
            count = struct.unpack_from('>I', self.asset, self.content)[0]
            self.table = struct.unpack_from(f'>{count}I', self.asset, self.content + 4)
            self.span = max(self.ram, group['size'])
        else:
            self.content, self.table = group['size'], ()
            self.span = self.content + self.RESIDENT_BSS
        self.pointers = self.find_pointers(resident_addresses)
        self.offsets = sorted(self.pointers)
        self.used = set()
        self.sizes = {}    # src file -> {section: size}, the retail sizes when this build matches
        self.text = None   # the linker script of the last link
        self.parts = None  # piece index -> linked address
        self.prepare(selected, cc, files, compilers, placements, sizes, names)

    def word(self, offset):
        return struct.unpack_from('>I', self.asset, offset)[0]

    def find_pointers(self, resident_addresses):
        """Image offset -> assembly for each address held in the asset bytes."""
        pointers = {}
        if self.fragment:
            # The retail relocation table says exactly which words are addresses.
            for entry in self.table:
                kind, offset = entry >> 24 & 0x7F, entry & 0xFFFFFF
                word = self.word(offset)
                if kind == 2:
                    pointers[offset] = f'.4byte T_{word:08X}'
                elif kind == 4 and word >> 26 in (2, 3):
                    target = (word & 0x3FFFFFF) << 2 | 0x80000000
                    pointers[offset] = f'{"j" if word >> 26 == 2 else "jal"} T_{target:08X}'
            # The loader leaves resident addresses alone, so the table does not list them.
            # Nor does it list geo layout set-callback commands (0x08000000, callback, argument)
            # aiming at another fragment's slot: the geo code converts those when it runs.
            for offset in range(0x20, self.content, 4):
                word = self.word(offset)
                if word in resident_addresses or (
                        self.word(offset - 4) == 0x08000000 and in_fragment_space(word)
                        and word & 0xFFF00000 != self.base):
                    pointers.setdefault(offset, f'.4byte T_{word:08X}')
            return pointers
        pointers.update(self.ENTRY)
        # The resident image has no relocation table, so any aligned data word that is a
        # resident address counts as a pointer. Words in fragment slots are not taken: retail
        # has none that point inside a fragment, only slot bases (which never move) and
        # lookalikes such as 0x81000531, a slot id and a count.
        low, high = self.base + 0x1000, self.base + self.span
        for offset in range(self.RESIDENT_DATA, self.content, 4):
            word = self.word(offset)
            if low <= word <= high:
                pointers[offset] = f'.4byte T_{word:08X}'
        return pointers

    def prepare(self, selected, cc, files, compilers, placements, sizes, names):
        """Compile and assemble everything, and list the pieces in retail order."""
        group, name, directory = self.group, self.name, self.directory
        assembly = [MACROS]
        pieces = []  # (retail image offset, retail size, object, section)
        c_objects = []
        self.counts = counts = Counter()
        cursor = 0
        current = None
        objects_by_file = {}
        occupied = []
        self.nobits = []
        for path in sorted({path for path, _ in files.values()} & {
                files[row['name']][0] for row in group['owners'] if row['name'] in files}):
            objects_by_file[path] = compile_source_file(path, directory, compilers, self.prefix)
            found = object_sections(objects_by_file[path])
            for section, place in placements.get(path, {}).items():
                if section not in found:
                    raise ValueError(f'{path} has no {section} to place')
                size, kind = found[section]
                if isinstance(place, dict):
                    # IDO pads a section to 16 bytes; where the next object's data
                    # starts inside that padding, the registry gives the real size.
                    retail = int(place['size'], 0)
                    retail = min(retail, trim_section(objects_by_file[path], section, retail,
                                                      strict=self.compare))
                    place = place['address']
                else:
                    retail = size if self.compare else sizes.get(path, {}).get(section, size)
                self.sizes.setdefault(path, {})[section] = retail
                address = int(place, 0)
                offset = address - group['base']
                if kind == 8:  # SHT_NOBITS: addresses only, no image bytes
                    self.nobits.append((address, retail, objects_by_file[path].name, section))
                elif not 0 <= offset <= offset + retail <= self.content:
                    raise ValueError(f'{path} {section} lies outside {name}')
                elif retail:
                    occupied.append((offset, retail, objects_by_file[path].name, section))
        occupied.sort()
        for (a, size_a, *_), (b, *_) in zip(occupied, occupied[1:]):
            if a + size_a > b:
                raise ValueError(f'placed data sections overlap in {name}')

        def gap(begin, end):
            # Placed object data takes precedence over the extracted asset bytes.
            for offset, size, obj, section in occupied:
                if begin < offset + size and offset < end:
                    if offset < begin or offset + size > end:
                        raise ValueError(f'{obj} {section} straddles an owner in {name}')
                    gap(begin, offset)
                    pieces.append((offset, size, obj, section))
                    begin = offset + size
            if end > begin:
                section = f'.gap_{begin:X}'
                assembly.append(f'.section {section}, "a", @progbits')
                position = begin
                first = bisect.bisect_left(self.offsets, begin)
                for offset in self.offsets[first:bisect.bisect_right(self.offsets, end - 4)]:
                    if offset > position:
                        assembly.append(f'.incbin "assets/production/{name}.bin", {position}, {offset - position}')
                    assembly.append(self.pointers[offset])
                    self.used.add(offset)
                    position = offset + 4
                if end > position:
                    assembly.append(f'.incbin "assets/production/{name}.bin", {position}, {end - position}')
                assembly.append('')
                pieces.append((begin, end - begin, 'assembly.o', section))
        spans = {}
        for row in group['owners']:
            if row['name'] in files:
                path, _ = files[row['name']]
                begin, end = spans.get(path, (int(row['start'], 0), int(row['end'], 0)))
                spans[path] = (min(begin, int(row['start'], 0)), max(end, int(row['end'], 0)))
        for row in sorted(group['owners'], key=lambda r: int(r['start'], 0)):
            begin, end = int(row['start'], 0), int(row['end'], 0)
            if begin < cursor:
                if files.get(row['name'], (None,))[0] != current:
                    raise ValueError(f'{row["name"]} lies inside the span of {current}')
                counts['c' if files[row['name']][1] else 'asm'] += 1
                continue
            gap(cursor, begin)
            if row['name'] in files:
                current = files[row['name']][0]
                span_begin, span_end = spans[current]
                obj = objects_by_file[current]
                size = min(trim_file_text(obj, span_end - span_begin, self.asset[span_end:span_end + 64],
                                          strict=self.compare), span_end - span_begin)
                c_objects.append(obj)
                pieces.append((begin, size, obj.name, '.text'))
                gap(begin + size, span_end)
                counts['c' if files[row['name']][1] else 'asm'] += 1
                cursor = span_end
                continue
            if row['name'] in selected:
                candidate = ROOT / selected[row['name']]['candidate']
                unit = directory / (row['name'] + '.c')
                unit.write_bytes(TYPES.encode() + candidate.read_bytes())
                obj = directory / (row['name'] + '.o')
                run([cc, *FLAGS, '-I.', unit, '-o', obj])
                trim_text(obj, row['name'], row['size'])
                c_objects.append(obj)
                pieces.append((begin, end - begin, obj.name, '.text'))
                counts['c'] += 1
            else:
                section = '.text_' + row['name']
                assembly.append(f'.section {section}, "ax", @progbits\n')
                listing = ROOT / row['assembly']
                assembly.append(canonical_assembly(listing.read_text()))
                pieces.append((begin, end - begin, 'assembly.o', section))
                counts['asm'] += 1
            cursor = end
        gap(cursor, self.content)
        if not self.fragment and self.ENTRY.keys() - self.used:
            raise ValueError('resident entry code is no longer asset bytes')
        source = directory / 'assembly.s'
        source.write_text('\n'.join(assembly))
        assembly_obj = directory / 'assembly.o'
        run([self.prefix + 'as', '-march=vr4300', '-32', '-G0', source, '-o', assembly_obj])
        self.objects = [assembly_obj, *c_objects]
        self.undefined = sorted(link_symbols(self.objects)[1])
        self.pieces = pieces
        self.begins = [piece[0] for piece in pieces]
        # Per piece, (retail offset, object offset) of each symbol whose retail address is
        # known, so an address inside an object that changed size can still be found.
        self.anchors = []
        defined = {}
        for obj in c_objects:
            _, _, symbols = read_elf(obj.read_bytes())
            sections = object_sections(obj)
            for symbol, value, section in symbols:
                defined.setdefault((obj.name, section), []).append((symbol, value))
            for section, (size, _) in sections.items():
                defined[obj.name, section, 'size'] = size
        for begin, size, obj, section in pieces:
            anchors = {0: 0}
            low = self.base + begin
            for symbol, value in defined.get((obj, section), ()):
                match = ADDRESS.fullmatch(symbol)
                known = {int(match[1], 16)} if match else names.get(symbol, set())
                known = [address for address in known if low <= address < low + size]
                if len(known) == 1:
                    anchors.setdefault(known[0] - low, value)
            anchors = sorted(anchors.items()) + [(size, defined.get((obj, section, 'size'), size))]
            if self.compare and any(old != new for old, new in anchors):
                raise ValueError(f'{name}: {obj} {section} defines a symbol away from its retail address')
            self.anchors.append(anchors)

    def locate(self, address):
        """(piece index, offset in the piece) of a retail address; index None is BSS."""
        offset = address - self.base
        if offset >= self.content:
            return None, offset - self.content
        index = bisect.bisect_right(self.begins, offset) - 1
        offset -= self.begins[index]
        anchors = self.anchors[index]
        at = bisect.bisect_right(anchors, (offset, float('inf'))) - 1
        (old, new), (next_old, next_new) = anchors[at], anchors[min(at + 1, len(anchors) - 1)]
        if offset != old and next_old - old != next_new - new:
            raise ValueError(f'{self.name}: 0x{address:08X} lies inside code or data of '
                             f'{self.pieces[index][2]} that changed size; define a symbol there '
                             'or place the referencing data in config/jp/sections.json')
        return index, new + offset - old

    def expression(self, address):
        index, offset = self.locate(address)
        return f'__bss + 0x{offset:X}' if index is None else f'ADDR(.part_{index}) + 0x{offset:X}'

    def address(self, address):
        """Where a retail address ended up in the last link; itself before any link."""
        if self.parts is None:
            return address
        index, offset = self.locate(address)
        return (self.bss if index is None else self.parts[index]) + offset

    def script(self, resolve):
        """Linker script text; resolve(image, retail address) gives a symbol's value."""
        name, directory = self.name, self.directory
        linker = ['PHDRS { prefix PT_LOAD FLAGS(4); body PT_LOAD FLAGS(7); }', 'SECTIONS {']
        for index, (begin, size, obj, section) in enumerate(self.pieces):
            output = f'.part_{index}'
            # --shift pads some pieces, to prove that nothing depends on a retail address.
            pad = self.shift if index % 64 == 1 else 0
            where = f'ALIGN(. + {pad} - {begin % 16}, 16) + {begin % 16}' if index else f'0x{self.base:X}'
            linker.append(f'{output} {where} : AT(ADDR({output}) - 0x{self.base:X}) SUBALIGN(4) '
                          f'{{ "{directory / obj}"({section}) }} :{"body" if index else "prefix"}')
            if self.compare:
                linker.append(f'ASSERT(SIZEOF({output}) == {size}, "size differs: {name} {section}")')
        linker.append('__bss = ALIGN(16);')
        for index, (address, size, obj, section) in enumerate(self.nobits):
            output = f'.nobits_{index}'
            # Zeroed variables inside the stored bytes only name them: INFO emits nothing,
            # and the bytes keep coming from the asset.
            kind, segment = ('INFO', 'NONE') if address - self.base < self.content else ('NOLOAD', 'body')
            linker.append(f'{output} {self.expression(address)} ({kind}) : SUBALIGN(4) '
                          f'{{ "{directory / obj}"({section}) }} :{segment}')
            linker.append(f'ASSERT(SIZEOF({output}) {"==" if self.compare else "<="} {size}, '
                          f'"BSS size differs: {name} {obj} {section}")')
        linker.append('/DISCARD/ : { *(*) }\n}')
        for symbol in self.undefined:
            if symbol in self.symbols:
                address = self.symbols[symbol]
            else:
                match = ADDRESS.fullmatch(symbol)
                if not match:
                    raise ValueError('unresolved symbol has no established address: ' + symbol)
                address = int(match[1], 16)
            linker.append(f'PROVIDE({symbol} = {resolve(self, address)});')
        return '\n'.join(linker) + '\n'

    def link(self, text):
        """Link with the given script; leaves the image bytes and their stored form."""
        group, name, directory = self.group, self.name, self.directory
        self.text = text
        script = directory / 'link.ld'
        script.write_text(text)
        elf = directory / (name + '.elf')
        # ll.c and llcvt.c are -mips3 objects, as in ultralib.
        run([self.prefix + 'ld', '--no-warn-mismatch', '--emit-relocs', '-T', script,
             '-Map', directory / 'link.map', '-o', elf, *self.objects])
        output = directory / (name + '.bin')
        run([self.prefix + 'objcopy', '-O', 'binary', elf, output])
        data = elf.read_bytes()
        names, raw, symbols = read_elf(data)
        self.parts = {int(section[6:]): header[3] for section, header in zip(names, raw)
                      if section.startswith('.part_')}
        self.bss = next(value for symbol, value, _ in symbols if symbol == '__bss')
        # (type, image offset, symbol value) of every relocation the linker applied, in the
        # order the objects list them: a HI16 comes before the LO16s that complete it.
        self.relocations = []
        for header in raw:
            if header[1] == 9 and names[header[7]].startswith('.part_'):  # SHT_REL
                for position in range(header[4], header[4] + header[5], 8):
                    offset, info = struct.unpack_from('>II', data, position)
                    if info & 255 in (2, 4, 5, 6):
                        self.relocations.append((info & 255, offset - self.base, symbols[info >> 8][1]))
        image = bytearray(output.read_bytes())
        image += bytes(-len(image) % 16)
        if self.fragment:
            image = self.add_relocations(image)
        self.image = bytes(image)
        if self.compare and len(image) != group['size']:
            raise ValueError('linked image size differs: ' + name)
        exact = sha(image) == group['expected_sha256']
        if self.compare and not exact:
            raise ValueError('linked image bytes differ: ' + name)
        if group['storage'] == 'raw':
            self.stored = self.image
        elif exact:
            self.stored = encode_image(image, (ASSETS / f'{name}.storage').read_bytes(), group['placeholders'])
        else:
            import crunch64
            # No restoration patches: they only undo a quirk of the retail compressor.
            self.stored = (b'PERS-SZP' + struct.pack('>4I', 0x18, len(image), max(len(image), self.ram_size), 0)
                           + crunch64.yay0.compress(self.image))

    def add_relocations(self, content):
        """Append the relocation table to the linked bytes and complete the header."""
        relocations = []  # what the loader must apply
        for kind, offset, target in self.relocations:
            foreign = (target & 0xFFF00000) != self.base
            # Another fragment's address is a plain number that code hands to
            # Memmap_GetFragmentVaddr itself (or masks for the slot number), except in
            # SHARED_SLOT, whose image the retail tables do relocate references to.
            if in_fragment_space(target) and (not foreign or target & 0xFFF00000 == SHARED_SLOT):
                relocations.append(kind << 24 | foreign << 31 | offset)
        self.ram_size = self.ram + len(content) - self.content

        def finish(table):
            image = content + table + bytes(-len(table) % 16)
            struct.pack_into('>3I', image, 0x14, len(content), len(image), self.ram_size)
            return image
        if self.compare or self.shift:
            # Every retail relocation that does anything must have been found again.
            # Follows Memmap_RelocateFragment: a LO16 completes the last HI16 of its register.
            expected, upper = set(), {}
            for entry in self.table:
                kind = entry >> 24 & 0x7F
                offset = self.address(self.base + (entry & 0xFFFFFF)) - self.base
                word = struct.unpack_from('>I', content, offset)[0]
                if kind == 5:
                    upper[word >> 16 & 31] = (offset, word)
                elif kind == 6:
                    high, value = upper[word >> 21 & 31]
                    if in_fragment_space(((value << 16) + (word & 0xFFFF) - (word & 0x8000) * 2) & 0xFFFFFFFF):
                        expected.update(((5, high), (6, offset)))
                elif in_fragment_space(word if kind == 2 else (word & 0x3FFFFFF) << 2 | 0x80000000):
                    expected.add((kind, offset))
            found = {(entry >> 24 & 0x7F, entry & 0xFFFFFF) for entry in relocations}
            if found != expected:
                sample = sorted(found ^ expected)[:8]
                raise ValueError(f'{self.name}: {len(found ^ expected)} relocations differ from retail: '
                                 + ', '.join(f'{kind}@0x{offset:X}' for kind, offset in sample))
        if len(content) == self.content:
            # Unchanged images keep the retail table, whose order and flags are not derivable.
            image = finish(bytearray(self.asset[self.content:]))
            if sha(image) == self.group['expected_sha256']:
                return image
        return finish(bytearray(struct.pack(f'>{len(relocations) + 1}I', len(relocations), *relocations)))


def check_shift(images, moved):
    """--shift self-test: each image is the retail one with every address moved along.

    Pieces only moved, so outside the relocated words the bytes must be the retail
    bytes, and each relocated word must hold where its retail value went.
    """
    rom = (ROOT / 'baseroms/jp/baserom.z64').read_bytes()
    mapping = json.loads((ROOT / 'docs/mappings/resident-fragments.json').read_text())
    for image in images:
        index = image.group['image_index']
        old = bytearray(rom[:image.content] if index is None else load_image(rom, mapping['fragments'][index]))
        new = bytearray(image.image)
        starts = [image.parts[piece] - image.base for piece in range(len(image.pieces))]

        def retail(offset):
            piece = bisect.bisect_right(starts, offset) - 1
            return image.begins[piece] + offset - starts[piece]
        upper = {}  # register -> its last HI16, as the loader pairs them
        for kind, offset, _ in image.relocations:
            pair = [struct.unpack_from('>I', data, at)[0] for data, at in ((new, offset), (old, retail(offset)))]
            if kind == 5:
                upper[pair[0] >> 16 & 31] = pair
                continue
            if kind == 4:
                pair = [(word & 0x3FFFFFF) << 2 | 0x80000000 for word in pair]
            elif kind == 6:
                pair = [((high << 16) + (low & 0xFFFF) - (low & 0x8000) * 2) & 0xFFFFFFFF
                        for high, low in zip(upper[pair[0] >> 21 & 31], pair)]
            if pair[0] != moved(image, pair[1]):
                raise ValueError(f'{image.name}+0x{retail(offset):X}: 0x{pair[1]:08X} became 0x{pair[0]:08X}, '
                                 f'not 0x{moved(image, pair[1]):08X}')
        for kind, offset, _ in image.relocations:
            new[offset:offset + 4] = old[retail(offset):retail(offset) + 4] = bytes(4)
        for (begin, size, obj, section), start in zip(image.pieces, starts):
            skip = 0x20 if image.fragment and not begin else 0  # the header holds the new sizes
            if new[start + skip:start + size] != old[begin + skip:begin + size]:
                raise ValueError(f'{image.name}: {obj} {section} changed besides its relocations')
    print(f'shift check: {sum(len(image.relocations) for image in images)} addresses in '
          f'{len(images)} images moved consistently', flush=True)


def headers_digest():
    """One digest over every header and included C fragment the src/ build can read."""
    digest = hashlib.sha256()
    for directory in ('include', 'src', 'lib/ultralib/include', 'lib/ultralib/src'):
        for path in sorted((ROOT / directory).rglob('*')):
            if path.is_file() and (path.suffix == '.h' or path.name.endswith('.inc.c')):
                digest.update(str(path.relative_to(ROOT)).encode() + b'\0' + path.read_bytes())
    return digest.hexdigest()


def source_files(paths):
    """Owner name -> (src file, owner is C) for the whole-file source registry."""
    if len(set(paths)) != len(paths):
        raise ValueError('duplicate source file in registry')
    wanted = set(paths)
    files = {}
    with (ROOT / 'docs/function-matches.csv').open() as handle:
        for row in csv.DictReader(handle):
            if row['source'] in wanted:
                files[row['owner']] = (row['source'], row['build'] == 'c')
    missing = wanted - {path for path, _ in files.values()}
    if missing:
        raise ValueError('source registry names files with no owners: ' + ', '.join(sorted(missing)))
    return files


def build(cc, prefix, compare, jobs, asm_only, compilers, shift=0):
    manifest = json.loads((ASSETS / 'manifest.json').read_text())
    BUILD.mkdir(parents=True, exist_ok=True)
    receipt_path = BUILD / 'receipt.json'
    receipt_path.write_text(json.dumps(dict(status='incomplete', full_rom_identical=False)) + '\n')
    selected = {}
    if not asm_only:
        rows = json.loads((ROOT / 'config/jp/matching.json').read_text())
        for row in rows:
            if row['name'] in selected:
                raise ValueError('duplicate C owner: ' + row['name'])
            selected[row['name']] = row
        known = {row['name'] for group in manifest['groups'] for row in group['owners']}
        if selected.keys() - known:
            raise ValueError('matching registry contains unknown owners')
    files = source_files(json.loads(SOURCE_REGISTRY.read_text()) if not asm_only else [])
    placements = json.loads(SECTION_REGISTRY.read_text()) if not asm_only else {}
    if placements.keys() - {path for path, _ in files.values()}:
        raise ValueError('section registry names files that are not built')
    for name in files.keys() & selected.keys():
        del selected[name]
    symbols = {}
    for line in (ROOT / 'linker_scripts/jp/symbol_addrs.txt').read_text().splitlines():
        match = re.match(r'\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', line)
        if match:
            symbols[match[1]] = int(match[2], 16)
    # Symbol name -> retail addresses, to find where an object defines a retail address.
    names = {}
    for name, address in symbols.items():
        names.setdefault(name, set()).add(address)
    with (ROOT / 'docs/function-matches.csv').open() as handle:
        for row in csv.DictReader(handle):
            for name in (row['owner'], row['c_name']):
                names.setdefault(name, set()).add(int(row['vram'], 0))
    sizes = json.loads(SIZE_REGISTRY.read_text()) if SIZE_REGISTRY.exists() else {}
    resident_group = manifest['groups'][0]
    # Addresses of resident things that fragment data may point at.
    resident_addresses = {resident_group['base'] + int(row['start'], 0) for row in resident_group['owners']}
    resident_addresses.update(address for address in symbols.values() if 0x80000400 <= address < 0x80105360)
    for path in [*(ROOT / 'asm').rglob('*.s'), *(ROOT / 'src').rglob('*.[ch]')]:
        resident_addresses.update(int(address, 16) for address in
                                  re.findall(r'\bD_(80[01][0-9A-F]{5})\b', path.read_text(errors='replace')))
    # Link slot -> image extent, for the slots that only one fragment uses.
    slots = Counter(group['base'] for group in manifest['groups'])
    unique = {}
    for group in manifest['groups'][1:]:
        if slots[group['base']] == 1:
            with (ASSETS / (group['name'] + '.bin')).open('rb') as handle:
                unique[group['base']] = max(group['size'], struct.unpack('>I', handle.read(0x20)[0x1C:])[0])
    counts = Counter()
    if not compare and not shift and '-DSHIFTABLE' not in SOURCE_FLAGS:
        # Code that holds a ROM offset as a number takes it from a symbol instead. That costs
        # instructions, so the --shift self-test, which keeps the retail code, leaves it out.
        SOURCE_FLAGS.append('-DSHIFTABLE')
    with ThreadPoolExecutor(max_workers=jobs) as pool:
        images = list(pool.map(lambda group: Image(
            group, selected, cc, prefix, compare, files, compilers, symbols, placements, sizes, names,
            resident_addresses, shift), manifest['groups']))
        resident = images[0]
        by_slot = {image.base: image for image in images[1:] if image.base in unique}
        # ROM segments in order: (retail start, image or None, opaque bytes or None).
        segments = [(image.group['rom_start'], image, None) for image in images]
        for gap in manifest['gaps']:
            data = (ASSETS / gap['asset']).read_bytes()
            if sha(data) != gap['sha256']:
                raise ValueError('opaque asset changed: ' + gap['asset'])
            segments.append((gap['start'], None, data))
        segments.sort(key=lambda segment: segment[0])
        old_starts = [segment[0] for segment in segments]
        new_starts = list(old_starts)

        def rom(address):
            """Where a retail ROM address is now; everything moves with its segment."""
            index = bisect.bisect_right(old_starts, address) - 1
            return new_starts[index] + address - old_starts[index]

        def owner(image, address):
            """The image that a retail address seen in the given image belongs to."""
            if resident.base + 0x1000 <= address <= resident.base + resident.span:
                return resident
            if in_fragment_space(address):
                target = image if address & 0xFFF00000 == image.base else by_slot.get(address & 0xFFF00000)
                if target is not None and address - target.base <= target.span:
                    return target

        def moved(image, address):
            """Where a retail RAM or ROM address seen in the given image is now."""
            target = owner(image, address)
            if target is not None:
                return target.address(address)
            return rom(address) if resident.content <= address < manifest['size'] else address

        def resolve(image, address):
            # The linker places an image's own addresses; the rest come from the last links.
            if owner(image, address) is image:
                return image.expression(address)
            return f'0x{moved(image, address):08X}'

        # An image's symbols depend on where the other images and the ROM contents ended
        # up, which depends on every image's size: relink until nothing changes.
        for _ in range(10):
            scripts = [image.script(resolve) for image in images]
            stale = [(image, text) for image, text in zip(images, scripts) if text != image.text]
            if not stale:
                break
            for index, _ in enumerate(pool.map(lambda pair: pair[0].link(pair[1]), stale), 1):
                if index % 25 == 0:
                    print(f'{index}/{len(stale)} images linked', flush=True)
            cursor = 0
            for index, (start, image, data) in enumerate(segments):
                # Stay at the retail offset while there is room; otherwise keep its alignment.
                new_starts[index] = start if cursor <= start else cursor + (start - cursor) % 16
                cursor = new_starts[index] + len(image.stored if image else data)
        else:
            raise ValueError('image addresses did not settle')
    if shift:
        check_shift(images, moved)
    output = bytearray()
    stored = {}
    for start, (_, image, data) in zip(new_starts, segments):
        output += bytes(start - len(output))
        output += image.stored if image else data
        if image:
            counts.update(image.counts)
            stored[image.group['rom_start']] = len(image.stored)
    # Archive directories hold member offsets and sizes; fragments 43 and up live in the last two.
    for archive in (0x2B2C80, 0x2F5940, 0x3FEBD0, 0x4A8000, 0x500000):
        base = rom(archive)
        total, count = struct.unpack_from('>2I', output, base + 8)
        struct.pack_into('>I', output, base + 8, rom(archive + total) - base)
        for entry in range(base + 16, base + 16 + 16 * count, 16):
            offset, size = struct.unpack_from('>2I', output, entry)
            member = archive + offset
            if member in stored:
                size = stored[member] + -stored[member] % 16
            struct.pack_into('>2I', output, entry, rom(member) - base, size)
    if len(output) > manifest['size'] and not output[manifest['size']:].strip(b'\xFF'):
        del output[manifest['size']:]  # the retail ROM ends in 0xFF filler
    output += b'\xFF' * (-len(output) % 0x100000)
    exact = sha(output) == EXPECTED_SHA256
    if compare and not exact:
        raise ValueError('full ROM differs')
    if not exact:
        fix_checksum(output)
    if compare and not asm_only:
        # Retail sizes of the placed sections, for builds whose objects no longer have them.
        text = json.dumps({path: image.sizes[path] for image in images for path in sorted(image.sizes)},
                          indent=2, sort_keys=True) + '\n'
        if not SIZE_REGISTRY.exists() or SIZE_REGISTRY.read_text() != text:
            SIZE_REGISTRY.write_text(text)
    target = ROOT / 'build/pokestadium0-jp.z64'
    target.write_bytes(output)
    overrides = json.loads((ROOT / 'tools/cflags_overrides.json').read_text())
    native = {path: sdk_assembly_source(path, overrides[path])
              for path, _ in files.values()
              if overrides.get(path, {}).get('profile') == 'ultralib-asm'}
    if any(is_c for path, is_c in files.values() if path in native):
        raise ValueError('original SDK assembly cannot be counted as C')
    native_versions = {overrides[path].get('ido', '5.3') for path in native}
    receipt = dict(status='PASS' if exact and compare else 'BUILT',
                   input_sha256=manifest['input_sha256'], output_sha256=sha(output),
                   full_rom_identical=exact, compare=compare, c_owners=counts['c'],
                   asm_owners=counts['asm'], linked_images=len(manifest['groups']),
                   sdk_asm_owners=sum(path in native for path, _ in files.values()),
                   original_assembly_sources_sha256={source: sha((ROOT / source).read_bytes())
                                                     for source in sorted(set(native.values()))},
                   sdk_assembler_tools_sha256={version: {
                       name: sha((Path(compilers[version]).parent / name).read_bytes())
                       for name in ('cc', 'acpp', 'as0', 'as1')}
                       for version in sorted(native_versions)},
                   compiler_sha256=sha(Path(cc).read_bytes()) if counts['c'] else None,
                   source_compilers_sha256={version: sha(Path(path).read_bytes())
                                            for version, path in compilers.items()} if files else None,
                   source_files=sorted({path for path, _ in files.values()}),
                   source_registry_sha256=sha(SOURCE_REGISTRY.read_bytes()),
                   section_registry_sha256=sha(SECTION_REGISTRY.read_bytes()),
                   headers_sha256=headers_digest(),
                   matching_registry_sha256=sha((ROOT / 'config/jp/matching.json').read_bytes()),
                   build_tools_sha256={name: sha((ROOT / name).read_bytes()) for name in
                                       ('tools/production.py', 'tools/m2c_easiest.py',
                                        'tools/asm_prelude.inc', 'tools/cflags_overrides.json',
                                        'tools/asm-processor/asm_processor.py',
                                        'tools/asm-processor/build.py',
                                        'docs/function-matches.csv',
                                        'linker_scripts/jp/symbol_addrs.txt')},
                   binutils={tool: run([prefix + tool, '--version']).decode().splitlines()[0]
                             for tool in ('as', 'ld', 'objcopy')},
                   c_sources_sha256={row['candidate']: sha((ROOT / row['candidate']).read_bytes())
                                     for row in selected.values()} |
                                    {path: sha((ROOT / path).read_bytes())
                                     for path in sorted({path for path, _ in files.values()})})
    receipt_path.write_text(json.dumps(receipt, indent=2) + '\n')
    print(json.dumps({key: value for key, value in receipt.items() if key != 'c_sources_sha256'}, indent=2), flush=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=['extract', 'build'])
    parser.add_argument('--cc', default='tools/ido5.3/cc')
    parser.add_argument('--cc71', default='tools/ido7.1/cc', help='IDO 7.1 for src/ files')
    parser.add_argument('--prefix', default='mips-linux-gnu-')
    parser.add_argument('--compare', type=int, choices=[0, 1], default=1)
    parser.add_argument('--jobs', type=int, default=4)
    parser.add_argument('--asm-only', action='store_true')
    parser.add_argument('--shift', type=lambda value: int(value, 0), default=0,
                        help='self-test: pad pieces of every image by this many bytes (a multiple of 16)')
    args = parser.parse_args()
    if args.command == 'extract':
        extract()
    else:
        compilers = {'5.3': str(Path(args.cc).resolve()), '7.1': str(Path(args.cc71).resolve())}
        build(compilers['5.3'], args.prefix, bool(args.compare) and not args.shift, args.jobs,
              args.asm_only, compilers, args.shift)


if __name__ == '__main__':
    main()
