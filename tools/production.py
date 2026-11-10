#!/usr/bin/env python3
"""Fixed-layout C/assembly ROM build, with separately retained opaque assets.

No original owner bytes survive in the extracted image assets. Every owner
comes from a compiler or assembler object placed by the image linker script.
"""
import argparse
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
PRAGMA = re.compile(r'(#pragma\s+GLOBAL_ASM\(\s*")([^"]+)("\s*\))')
LISTING = re.compile(r'/\*\s+[0-9A-F]+\s+([0-9A-F]+)\s+([0-9A-F]{8})\s*\*/\s*(.*)')
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


def trim_file_text(obj, size, after=b''):
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
    return trim_section(obj, '.text', size, after)


def trim_section(obj, name, size, after=b''):
    """Shorten a section to at most size bytes.

    Only zero bytes, or bytes equal to after (the image bytes past size), may be removed.
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
                raise ValueError(f'{obj.name}: {name} is 0x{section[5]:X} bytes, owners span 0x{size:X}')
            size = min(size, section[5])
            struct.pack_into('>I', data, position + 20, size)
            struct.pack_into('>I', data, position + 32, 4)
            obj.write_bytes(data)
            return size
    raise ValueError(f'no {name} section in {obj.name}')


def compile_source_file(path, directory, compilers, prefix):
    """Compile a whole src/ file through asm-processor.

    GLOBAL_ASM owners use the same normalized listings as assembly owners.
    """
    overrides = json.loads((ROOT / 'tools/cflags_overrides.json').read_text())
    flags = overrides.get(path, {})
    stem = path[len('src/'):-2].replace('/', '__')
    canon = BUILD / 'canonical'

    def canonical(match):
        listing = canon / match[2]
        if not listing.exists():
            listing.parent.mkdir(parents=True, exist_ok=True)
            listing.write_text(canonical_assembly((ROOT / match[2]).read_text()))
        return match[1] + str(listing.relative_to(ROOT)) + match[3]

    unit = directory / (stem + '.c')
    unit.write_text(PRAGMA.sub(canonical, (ROOT / path).read_text(encoding='utf-8')), encoding='utf-8')
    obj = directory / (stem + '.o')
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


def bss_output_section(output, address, obj, section, base, image_size):
    """Bind runtime BSS without reserving its overlapping stored-image bytes.

    Some fragments reuse their relocation storage as scratch after loading.
    An INFO section keeps the BSS symbol addresses but emits no image bytes
    or load segment; the stored bytes retain their independently checked owner.
    """
    inside = base <= address < base + image_size
    kind, segment = ('INFO', 'NONE') if inside else ('NOLOAD', 'body')
    return f'{output} 0x{address:X} ({kind}) : SUBALIGN(4) {{ "{obj}"({section}) }} :{segment}'


def build_group(group, selected, cc, prefix, compare, files=None, compilers=None, symbols=None,
                directory=None, placements=None):
    name = group['name']
    directory = directory or BUILD / name
    directory.mkdir(parents=True, exist_ok=True)
    assembly = [MACROS]
    sections = []
    c_objects = []
    counts = Counter()
    cursor = 0
    current = None
    files = files or {}
    placements = placements or {}

    def image_bytes(offset, count=64):
        # Extracted image bytes from offset, for trim_file_text.
        image = ROOT / 'assets/production' / (name + '.bin')
        with open(image, 'rb') as h:
            h.seek(offset)
            return h.read(count)
    objects_by_file = {}
    occupied = []
    nobits = []
    for path in sorted({path for path, _ in files.values()} & {
            files[row['name']][0] for row in group['owners'] if row['name'] in files}):
        objects_by_file[path] = compile_source_file(path, directory, compilers, prefix)
        found = object_sections(objects_by_file[path])
        for section, place in placements.get(path, {}).items():
            if section not in found:
                raise ValueError(f'{path} has no {section} to place')
            size, kind = found[section]
            if isinstance(place, dict):
                # IDO pads a section to 16 bytes; where the next object's data
                # starts inside that padding, the registry gives the real size.
                size = trim_section(objects_by_file[path], section, int(place['size'], 0))
                place = place['address']
            address = int(place, 0)
            offset = address - group['base']
            if kind == 8:  # SHT_NOBITS: addresses only, no image bytes
                nobits.append((address, size, objects_by_file[path].name, section))
            elif not 0 <= offset <= offset + size <= group['size']:
                raise ValueError(f'{path} {section} lies outside {name}')
            else:
                occupied.append((offset, size, objects_by_file[path].name, section))
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
                sections.append((offset, size, obj, section))
                begin = offset + size
        if end > begin:
            section = f'.gap_{begin:X}'
            assembly.append(f'.section {section}, "a", @progbits\n.incbin "assets/production/{name}.bin", {begin}, {end - begin}\n')
            sections.append((begin, end - begin, 'assembly.o', section))
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
            size = trim_file_text(obj, span_end - span_begin, image_bytes(span_end))
            c_objects.append(obj)
            sections.append((begin, size, obj.name, '.text'))
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
            sections.append((begin, end - begin, obj.name, '.text'))
            counts['c'] += 1
        else:
            section = '.text_' + row['name']
            assembly.append(f'.section {section}, "ax", @progbits\n')
            listing = ROOT / row['assembly']
            assembly.append(canonical_assembly(listing.read_text()))
            sections.append((begin, end - begin, 'assembly.o', section))
            counts['asm'] += 1
        cursor = end
    gap(cursor, group['size'])
    source = directory / 'assembly.s'
    source.write_text('\n'.join(assembly))
    assembly_obj = directory / 'assembly.o'
    run([prefix + 'as', '-march=vr4300', '-32', '-G0', source, '-o', assembly_obj])
    objects = [assembly_obj, *c_objects]
    undefined, defined = set(), set()
    for line in run([prefix + 'nm', *objects]).decode().splitlines():
        parts = line.split()
        if len(parts) == 2 and parts[0] == 'U':
            undefined.add(parts[1])
        elif len(parts) == 3:
            defined.add(parts[2])
    undefined -= defined
    linker = ['PHDRS { prefix PT_LOAD FLAGS(4); body PT_LOAD FLAGS(7); }', 'SECTIONS {']
    for index, (begin, size, obj, section) in enumerate(sections):
        output = f'.part_{index}'
        segment = 'prefix' if index == 0 else 'body'
        linker.append(f'{output} 0x{group["base"] + begin:X} : AT({begin}) SUBALIGN(4) {{ "{directory / obj}"({section}) }} :{segment}')
        linker.append(f'ASSERT(SIZEOF({output}) == {size}, "size differs: {name} {section}")')
    for index, (address, size, obj, section) in enumerate(nobits):
        output = f'.nobits_{index}'
        linker.append(bss_output_section(output, address, directory / obj, section,
                                         group['base'], group['size']))
        linker.append(f'ASSERT(SIZEOF({output}) == {size}, "size differs: {name} {obj} {section}")')
    linker.append('/DISCARD/ : { *(*) }\n}')
    for symbol in sorted(undefined):
        if symbols and symbol in symbols:
            linker.append(f'PROVIDE({symbol} = 0x{symbols[symbol]:08X});')
            continue
        match = re.fullmatch(r'(?:func_|D_(?:(?:FLT|DBL|STR)_)?|jtbl_|T_|\.L)([0-9A-F]{8})(?:_\d+)?', symbol)
        if not match:
            raise ValueError('unresolved symbol has no established address: ' + symbol)
        linker.append(f'PROVIDE({symbol} = 0x{match[1]});')
    script = directory / 'link.ld'
    script.write_text('\n'.join(linker) + '\n')
    elf = directory / (name + '.elf')
    # ll.c and llcvt.c are -mips3 objects, as in ultralib.
    run([prefix + 'ld', '--no-warn-mismatch', '-T', script, '-Map', directory / 'link.map', '-o', elf, *objects])
    output = directory / (name + '.bin')
    run([prefix + 'objcopy', '-O', 'binary', elf, output])
    image = output.read_bytes()
    if len(image) != group['size']:
        raise ValueError('linked image size differs: ' + name)
    if compare and sha(image) != group['expected_sha256']:
        raise ValueError('linked image bytes differ: ' + name)
    if group['storage'] != 'raw':
        image = encode_image(image, (ASSETS / f'{name}.storage').read_bytes(), group['placeholders'])
    return group, image, counts


def headers_digest():
    """One digest over every header and included C fragment the src/ build can read."""
    digest = hashlib.sha256()
    for directory in ('include', 'src', 'lib/ultralib/include'):
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


def build(cc, prefix, compare, jobs, asm_only, compilers):
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
    output = bytearray(manifest['size'])
    for gap in manifest['gaps']:
        data = (ASSETS / gap['asset']).read_bytes()
        if sha(data) != gap['sha256']:
            raise ValueError('opaque asset changed: ' + gap['asset'])
        output[gap['start']:gap['end']] = data
    counts = Counter()
    def task(group):
        return build_group(group, selected, cc, prefix, compare, files, compilers, symbols,
                           placements=placements)
    with ThreadPoolExecutor(max_workers=jobs) as pool:
        for index, (group, image, totals) in enumerate(pool.map(task, manifest['groups']), 1):
            if len(image) != group['rom_end'] - group['rom_start']:
                raise ValueError('stored image changed size')
            output[group['rom_start']:group['rom_end']] = image
            counts.update(totals)
            if index % 25 == 0:
                print(f'{index}/{len(manifest["groups"])} images linked', flush=True)
    exact = sha(output) == EXPECTED_SHA256
    if compare and not exact:
        raise ValueError('full ROM differs')
    target = ROOT / 'build/pokestadium0-jp.z64'
    target.write_bytes(output)
    receipt = dict(status='PASS' if exact and compare else 'BUILT',
                   input_sha256=manifest['input_sha256'], output_sha256=sha(output),
                   full_rom_identical=exact, compare=compare, c_owners=counts['c'],
                   asm_owners=counts['asm'], linked_images=len(manifest['groups']),
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
    args = parser.parse_args()
    if args.command == 'extract':
        extract()
    else:
        compilers = {'5.3': str(Path(args.cc).resolve()), '7.1': str(Path(args.cc71).resolve())}
        build(compilers['5.3'], args.prefix, bool(args.compare), args.jobs, args.asm_only, compilers)


if __name__ == '__main__':
    main()
