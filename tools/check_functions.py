#!/usr/bin/env python3
"""Compile C and original SDK assembly functions and compare them with the ROM.

Each source file is compiled with IDO and -DNON_MATCHING, which leaves only
the C function definitions (GLOBAL_ASM owners drop out). Original SDK assembly
wrappers instead use ultralib's native IDO assembler recipe. Every function in
the object is matched to its pragma-inventory owner by address and compared
word for word. Relocated fields are checked by solving for symbol addresses:

* names in linker_scripts/jp/symbol_addrs.txt and address-style names
  (func_XXXXXXXX, D_XXXXXXXX, ...) must resolve to that address;
* every reference to one symbol inside a function must agree;
* section-relative references (string/float literals, jump tables, statics
  local to a function) only need to agree within the function, because the
  .rodata/.bss layout of a whole file is not verified until the ROM links.

This is a per-function check, not a ROM rebuild: position-dependent code
(alignment padding inside a function) can differ once files link for real.

Usage: tools/check_functions.py [--cc-dir tools] [src files...]  (IDO from tools/ido<version>/cc)
"""
import argparse
import io
import json
from multiprocessing import Pool
from pathlib import Path
import re
import struct
import subprocess
import sys
import tempfile

from elftools.elf.elffile import ELFFile

from map_fragment_sections import load_image
from map_rom import EXPECTED_SHA256
from production import (ULTRALIB_FLAGS, ULTRALIB_ASM_FLAGS, sdk_assembly_source,
                        normalize_sdk_symbols)

ROOT = Path(__file__).resolve().parents[1]
ADDR_NAME = re.compile(r"^(?:func|D|D_FLT|D_DBL|jtbl|B|sub|RO|L)_([0-9A-Fa-f]{8})(?:_\d+)?$")
CFLAGS = ["-c", "-G", "0", "-non_shared", "-Xcpluscomm", "-nostdinc", "-Wab,-r4300_mul",
          "-EB", "-w", "-D_MIPS_SZLONG=32", "-DNDEBUG", "-D_FINALROM", "-DN_MICRO",
          "-DF3DEX_GBI_2", "-DBUILD_VERSION=VERSION_I_P", "-DLANGUAGE_C", "-D_LANGUAGE_C",
          "-DVERSION_JP=1", "-DNON_MATCHING"]
INCLUDES = ["include", "src", ".", "lib/ultralib/include", "lib/ultralib/include/PR",
            "lib/ultralib/include/ido"]


def load_symbols():
    symbols = {}
    for line in (ROOT / "linker_scripts/jp/symbol_addrs.txt").read_text().splitlines():
        match = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", line)
        if match:
            symbols[match.group(1)] = int(match.group(2), 16)
    return symbols


TAIL_WORDS = 16


def load_owner_words(rom):
    """(image_index, link address) -> owner words, from the inventory and ROM.

    Decompressing every fragment is slow, so the result is cached in build/.
    """
    import hashlib
    import pickle
    text = (ROOT / "docs/pragma-inventory.json").read_bytes()
    key = hashlib.sha256(text + hashlib.sha256(rom).digest() + b"tail-v1").hexdigest()
    cache = ROOT / "build/check_functions_owners.pickle"
    if cache.exists():
        stored_key, owners = pickle.loads(cache.read_bytes())
        if stored_key == key:
            return owners
    owners = read_owner_words(rom)
    cache.parent.mkdir(parents=True, exist_ok=True)
    cache.write_bytes(pickle.dumps((key, owners)))
    return owners


def read_owner_words(rom):
    inventory = json.loads((ROOT / "docs/pragma-inventory.json").read_text())
    mapping = json.loads((ROOT / "docs/mappings/resident-fragments.json").read_text())
    images = {}
    owners = {}
    starts = {}
    for row in inventory["owners"]:
        starts.setdefault(row["image_index"], []).append(int(row["start"], 0))
    for index in starts:
        starts[index].sort()
    for row in inventory["owners"]:
        index = row["image_index"]
        start, stop = int(row["start"], 0), int(row["end"], 0)
        if index is None:
            blob = rom
        else:
            if index not in images:
                images[index] = load_image(rom, mapping["fragments"][index])
            blob = images[index]
        raw = blob[start:stop]
        words = list(struct.unpack(">%dI" % (len(raw) // 4), raw))
        # The unowned words that follow the owner, up to the next owner. The
        # owner ranges stop at the last reachable instruction, so a function
        # that ends in an endless loop leaves its dead epilogue here.
        later = [s for s in starts[index] if s >= stop]
        gap = blob[stop:min(later[0] if later else len(blob), stop + TAIL_WORDS * 4)]
        tail = list(struct.unpack(">%dI" % (len(gap) // 4), gap[:len(gap) // 4 * 4]))
        owners[(index, int(row["link_start"], 0))] = (row["name"], words, tail)
    return owners


def parse_object(data):
    elf = ELFFile(io.BytesIO(data))
    sections = list(elf.iter_sections())
    text_index = [i for i, s in enumerate(sections) if s.name == ".text"]
    if not text_index:
        return b"", {}, {}
    text_index = text_index[0]
    symtab = elf.get_section_by_name(".symtab")
    functions = {}
    for sym in symtab.iter_symbols():
        if sym["st_shndx"] == text_index and sym["st_info"]["type"] == "STT_FUNC":
            functions[sym.name] = (sym["st_value"], sym["st_size"])
    relocations = {}
    rel = elf.get_section_by_name(".rel.text")
    if rel:
        for entry in rel.iter_relocations():
            sym = symtab.get_symbol(entry["r_info_sym"])
            name = sym.name
            if sym["st_info"]["type"] == "STT_SECTION" or not name:
                name = "@" + sections[sym["st_shndx"]].name
            relocations[entry["r_offset"]] = (entry["r_info_type"], name)
    return sections[text_index].data(), functions, relocations


def sext16(value):
    return value - 0x10000 if value & 0x8000 else value


def compare(text, functions, relocations, name, vram, expected, symbols, learned=None, tail=()):
    """Return None on a match, else a short reason.

    With learned (a dict), a name with no known address is bound to the
    address the ROM implies and recorded there instead of failing.

    A function may run past its owner only into tail, the unowned ROM words
    after it, and only with words equal to those (a dead epilogue after an
    endless loop, with no relocations).
    """
    offset, size = functions[name]
    count = size // 4
    if count > len(expected):
        extra = struct.unpack(">%dI" % (count - len(expected)),
                              text[offset + 4 * len(expected):offset + size])
        if (list(extra) != list(tail[:len(extra)])
                or any(offset + 4 * i in relocations for i in range(len(expected), count))):
            return "size %d words, owner has %d" % (count, len(expected))
        count = len(expected)
        size = 4 * count
    if any(expected[count:]):
        return "size %d words, owner has %d" % (count, len(expected))
    words = struct.unpack(">%dI" % count, text[offset:offset + size])
    by_offset = {value[0]: key for key, value in functions.items()}
    bound = {}

    def bind(sym, address):
        address &= 0xFFFFFFFF
        match = ADDR_NAME.match(sym)
        if match and int(match.group(1), 16) != address:
            return False
        if not sym.startswith("@") and not match and sym not in symbols and sym not in functions:
            if learned is None or learned.setdefault(sym, address) != address:
                return False
        if sym in symbols and symbols[sym] != address:
            if learned is None or learned.setdefault("!" + sym, address) != address:
                return False
            return True
        if bound.setdefault(sym, address) != address:
            return False
        return True

    for i, (got, want) in enumerate(zip(words, expected)):
        reloc = relocations.get(offset + 4 * i)
        if reloc is None:
            if got != want:
                return "word %d" % i
            continue
        kind, sym = reloc
        if kind == 4:  # R_MIPS_26
            if (got ^ want) & 0xFC000000:
                return "opcode %d" % i
            target = ((vram + 4 * i) & 0xF0000000) | ((want & 0x3FFFFFF) << 2)
            addend = (got & 0x3FFFFFF) << 2
            if sym == "@.text" and addend in by_offset:
                sym, addend = by_offset[addend], 0
            if not bind(sym, target - addend):
                return "call target %d (%s); ROM implies 0x%08X" % (i, sym, target - addend)
        elif kind == 5:  # R_MIPS_HI16, checked through its LO16 users
            if (got ^ want) & 0xFFFF0000:
                return "opcode %d" % i
        elif kind == 6:  # R_MIPS_LO16: pair with the HI16 that loaded its base
            if (got ^ want) & 0xFFFF0000:
                return "opcode %d" % i
            base = (got >> 21) & 0x1F
            hi = None
            for k in range(i - 1, -1, -1):
                prior = relocations.get(offset + 4 * k)
                if prior and prior[0] == 5 and prior[1] == sym and ((words[k] >> 16) & 0x1F) == base:
                    hi = k
                    break
            if hi is None:
                return "unpaired %%lo %d" % i
            addend = ((words[hi] & 0xFFFF) << 16) + sext16(got & 0xFFFF)
            target = ((expected[hi] & 0xFFFF) << 16) + sext16(want & 0xFFFF)
            if not bind(sym, target - addend):
                return "address %d (%s); ROM implies 0x%08X" % (i, sym, (target - addend) & 0xFFFFFFFF)
        else:
            return "relocation type %d" % kind
    return None


_SEGMENTS = None


def segment_of(path):
    """Image index (None for the resident image) of the owners a source file builds.

    File names no longer encode the fragment, so this reads it from
    docs/function-matches.csv (owner per source) and the pragma inventory
    (image per owner). Every owner of one file must lie in one image.
    """
    global _SEGMENTS
    if _SEGMENTS is None:
        import csv
        inventory = json.loads((ROOT / "docs/pragma-inventory.json").read_text())
        image = {row["name"]: row["image_index"] for row in inventory["owners"]}
        found = {}
        with (ROOT / "docs/function-matches.csv").open() as handle:
            for row in csv.DictReader(handle):
                found.setdefault(row["source"], set()).add(image[row["owner"]])
        _SEGMENTS = {}
        for source, images in found.items():
            if len(images) != 1:
                raise ValueError(f"{source} has owners in several images: {sorted(map(str, images))}")
            _SEGMENTS[source] = images.pop()
    return _SEGMENTS.get(path)


def compile_source(path, cc_dir, overrides):
    flags = overrides.get(path, {})
    cc = Path(cc_dir) / ("ido" + flags.get("ido", "7.1")) / "cc"
    with tempfile.TemporaryDirectory() as tmp:
        native = flags.get("profile") == "ultralib-asm"
        if native:
            sdk_assembly_source(path, flags)
        source = Path(tmp) / (Path(path).stem + '.s' if native else Path(path).name)
        source.write_bytes((ROOT / path).read_text(encoding="utf-8").encode("euc-jp", "replace"))
        obj = Path(tmp) / "out.o"
        if native:
            base = ULTRALIB_ASM_FLAGS
        elif flags.get("profile") == "ultralib":
            # An unmodified lib/ultralib source, included by path from the repository root.
            base = [*ULTRALIB_FLAGS, "-EB", "-DNON_MATCHING"]
        else:
            base = [*CFLAGS, *("-I" + str(ROOT / i) for i in INCLUDES)]
        command = [str(cc), *base, flags.get("opt", "-O2"), flags.get("mips", "-mips2"),
                   *flags.get("extra", []), "-I" + str(ROOT / Path(path).parent),
                   "-o", str(obj), str(source)]
        result = subprocess.run(command, capture_output=True, text=True, errors="replace",
                                cwd=ROOT)
        if result.returncode != 0 or not obj.exists():
            return None, result.stdout + result.stderr
        if native:
            normalize_sdk_symbols(obj)
        return obj.read_bytes(), ""


def native_function_symbols(functions):
    """Ignore zero-size SDK entry aliases only when a sized entry shares the offset."""
    sized = {offset for offset, size in functions.values() if size}
    return {name: value for name, value in functions.items()
            if value[1] or value[0] not in sized}


def native_owner_span(segment, address, size, owners):
    """Find the exact SDK function interval within a conservative inventory owner.

    Exception assembly has several real function entries in one inventory owner.
    Every entry still compares against its own complete ROM instruction interval;
    crossing an owner boundary or an unknown/empty extent is rejected.
    """
    if address is None or size <= 0 or size % 4:
        return None
    for (owner_segment, start), (name, words, tail) in owners.items():
        if owner_segment != segment or not start <= address < start + 4 * len(words):
            continue
        offset = address - start
        if offset % 4 or offset + size > 4 * len(words):
            return None
        return name, words[offset // 4:(offset + size) // 4], ()
    return None


def check_file(job):
    path, cc_dir, overrides, symbols, owners, learn = job
    data, error = compile_source(path, cc_dir, overrides)
    if data is None:
        return path, [("<compile>", error.strip()[-500:])], 0
    text, functions, relocations = parse_object(data)
    native = overrides.get(path, {}).get("profile") == "ultralib-asm"
    if native:
        functions = native_function_symbols(functions)
    segment = segment_of(path)
    failures = []
    checked = 0
    learned = {} if learn else None
    for name in functions:
        match = ADDR_NAME.match(name)
        address = symbols.get(name, int(match.group(1), 16) if match else None)
        owner = (native_owner_span(segment, address, functions[name][1], owners)
                 if native else owners.get((segment, address)))
        if owner is None:
            failures.append((name, "no assembly owner at this address"))
            continue
        reason = compare(text, functions, relocations, name, address, owner[1], symbols, learned,
                         owner[2])
        checked += 1
        if reason:
            failures.append((name, reason))
    for name, address in sorted((learned or {}).items()):
        if name.startswith("!"):
            failures.append((name[1:], "conflicting symbol; ROM implies 0x%08X" % address))
        else:
            failures.append((name, "unknown symbol; ROM implies 0x%08X" % address))
    return path, failures, checked


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("sources", nargs="*")
    parser.add_argument("--rom", default=str(ROOT / "baseroms/jp/baserom.z64"))
    parser.add_argument("--cc-dir", default=str(ROOT / "tools"))
    parser.add_argument("-j", type=int, default=None)
    parser.add_argument("--learn", action="store_true",
                        help="report addresses the ROM implies for unknown symbols")
    args = parser.parse_args()
    rom = Path(args.rom).read_bytes()
    import hashlib
    if hashlib.sha256(rom).hexdigest() != EXPECTED_SHA256:
        sys.exit("wrong input ROM")
    owners = load_owner_words(rom)
    symbols = load_symbols()
    overrides = json.loads((ROOT / "tools/cflags_overrides.json").read_text())
    sources = args.sources or sorted(set(
        str(p.relative_to(ROOT)) for p in (ROOT / "src").rglob("*.c")
        if has_c_functions(p)) | {
            path for path, flags in overrides.items()
            if flags.get('profile') == 'ultralib-asm'})
    jobs = [(s, args.cc_dir, overrides, symbols, owners, args.learn) for s in sources]
    total = 0
    bad = 0
    with Pool(args.j) as pool:
        for path, failures, checked in pool.imap_unordered(check_file, jobs):
            total += checked
            for name, reason in failures:
                bad += 1
                print("%s: %s: %s" % (path, name, reason))
    print("%d functions checked in %d files, %d failures" % (total, len(sources), bad))
    sys.exit(1 if bad else 0)


def has_c_functions(path):
    text = path.read_text(encoding="utf-8")
    return bool(re.search(r"^[A-Za-z_][^;#\n]*\)\s*\{\s*$", text, re.M))


if __name__ == "__main__":
    main()
