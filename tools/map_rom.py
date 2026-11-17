#!/usr/bin/env python3
"""Inspect Stadium Zero headers without treating asset bytes as executable code."""
import argparse
import csv
from collections import Counter
import hashlib
import json
import struct
from pathlib import Path

import rabbitizer
import crunch64

EXPECTED_SHA256 = "ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b"


def inspect_fragment(data):
    """Validate a decoded image using the fields consumed by the ROM loader."""
    words = struct.unpack_from(">8I", data)
    if words[0] >> 26 != 2 or words[1] or data[8:16] != b"FRAGMENT":
        raise ValueError("invalid fragment signature or entry jump")
    entry = 0x80000000 | ((words[0] & 0x3FFFFFF) << 2)
    base = entry & 0xFFF00000
    begin, reloc, rom_size, ram_size = words[4:]
    if not (begin == 0x20 and begin <= reloc < rom_size <= len(data)):
        raise ValueError("invalid fragment extent")
    if not (0x81000000 <= base < 0x90000000 and base + begin <= entry < base + reloc):
        raise ValueError("entry is not within the pre-relocation payload")
    if ram_size < reloc:
        raise ValueError("RAM size smaller than retained payload")
    count = struct.unpack_from(">I", data, reloc)[0]
    if reloc + 4 + count * 4 > rom_size:
        raise ValueError("relocation table overrun")
    kinds = Counter()
    for index in range(count):
        value = struct.unpack_from(">I", data, reloc + 4 + index * 4)[0]
        kind, offset = (value >> 24) & 0x7F, value & 0xFFFFFF
        if kind not in (2, 4, 5, 6) or offset % 4 or not (offset + 4 <= reloc):
            raise ValueError(f"bad relocation {value:#x}")
        kinds[kind] += 1
        instruction = struct.unpack_from(">I", data, offset)[0]
        if kind == 4 and instruction >> 26 not in (2, 3):
            raise ValueError("R_MIPS_26 does not point to a jump")
        if kind == 5 and instruction >> 26 != 15:
            raise ValueError("R_MIPS_HI16 does not point to LUI")
    return {
        "link_base": f"0x{base:08X}",
        "fragment_slot": (base - 0x81000000) >> 20,
        "entry_link_vram": f"0x{entry:08X}",
        "entry_offset": f"0x{entry-base:X}",
        "payload_offset": f"0x{begin:X}",
        "reloc_offset": f"0x{reloc:X}",
        "image_size": f"0x{rom_size:X}",
        "ram_size": f"0x{ram_size:X}",
        "relocation_count": count,
        "relocation_kinds": dict(sorted(kinds.items())),
        "validation": "header, extent, entry, relocation bounds/types and J/LUI opcodes",
        "text_data_boundary": "not established",
        "runtime_base": "dynamic; assigned by loader",
    }


def trace_yay0(data):
    """Decode and return exact consumed extent, checked against crunch64."""
    size, links, literals = struct.unpack_from(">3I", data, 4)
    mask_cursor = 16
    masks = 0
    remaining = 0
    output = bytearray()
    while len(output) < size:
        if remaining == 0:
            masks = struct.unpack_from(">I", data, mask_cursor)[0]
            mask_cursor += 4
            remaining = 32
        if masks & 0x80000000:
            output.append(data[literals])
            literals += 1
        else:
            link = struct.unpack_from(">H", data, links)[0]
            links += 2
            length = link >> 12
            distance = (link & 0xFFF) + 1
            if length == 0:
                length = data[literals] + 18
                literals += 1
            else:
                length += 2
            if distance > len(output) or len(output) + length > size:
                raise ValueError("invalid backreference")
            for _ in range(length):
                output.append(output[-distance])
        masks = (masks << 1) & 0xFFFFFFFF
        remaining -= 1
    decoded = bytes(output)
    if decoded != crunch64.yay0.decompress(data):
        raise ValueError("independent decoder disagrees with crunch64")
    return decoded, max(mask_cursor, links, literals)


BANK_MAGIC = b"N64 PtrTablesV2\x00"
WAVE_MAGIC = b"N64 WaveTables \x00"
# Data regions identified from their consumers: (start, end exclusive, label, evidence).
CURATED_REGIONS = [
    (0xDA9B0, 0x15A9B0, "gb_waveform_tables",
     "32 x 0x4000 8-bit waveform tables; fragment 0x81100000 DMAs exactly this interval at 0x81100930"),
    (0x15A9B0, 0x15B1A0, "gb_audio_bank_seq",
     "ADPCM book and sequence bytes; 0x8110E1F0..0x8110E220 pass 0x15AE60, 0x15A9B0, 0x15AA60 to 0x8110CB70"),
    (0x2B1630, 0x2B16A0, "cpu_stub_2B1630",
     "0x70-byte MIPS routine outside any FRAGMENT; no static ROM reference found"),
    (0x434C00, 0x480CEC, "battle_species_records",
     "151 per-species records of 0x7F4 bytes (0x80C for #25); offsets in resident u32 table 0x80073B30, "
     "read 0x814 bytes at a time by 0x82102188"),
    (0x480CEC, 0x4857D0, "f32_table_480CEC",
     "big-endian f32 records after the species records; consumer not yet found"),
    (0xFB4690, 0xFE647C, "cry_data_FB4690",
     "u32 0x97 then, at +0x10, 151 x {u16 base cry, u8 pitch, u8 length} in National Dex order "
     "(values equal the Game Boy Red/Green cry table), +0x270 onward per-cry channel data; consumer not yet traced"),
]


def find_archives(data):
    """Top-level member archives: u32 ?, 0, total, count, then count x {offset, size, 0, 0}."""
    found, offset = [], 0
    while offset + 0x20 <= len(data):
        total, count = struct.unpack_from(">2I", data, offset + 8)
        table_end = 0x10 + count * 0x10
        valid = (data[offset + 4:offset + 8] == bytes(4) and 0 < count < 0x2000
                 and table_end <= total <= len(data) - offset and total > 0x40)
        for index in range(count if valid else 0):
            member, size, zero1, zero2 = struct.unpack_from(">4I", data, offset + 0x10 + index * 0x10)
            if (zero1 or zero2 or member + size > total or (size and member < table_end)
                    or (index == 0 and member != table_end)):
                valid = False
                break
        if valid:
            found.append((offset, total, count, table_end))
            offset += (total + 15) & ~15
        else:
            offset += 16
    return found


def asset_regions(data, report):
    """Label non-fragment storage. Regions overlapping a fragment image or an
    earlier (outer) region are dropped, so the result never conflicts with the
    fragment map. A wave table runs from its "N64 WaveTables" header to the next
    mapped boundary, minus trailing 0xFF fill."""
    taken = [(int(f["rom_start"], 0), int(f["rom_consumed_end"], 0)) for f in report["fragments"]]
    wrappers = {}
    cursor = data.find(b"PERS-SZP")
    while cursor >= 0:
        wrappers[cursor + struct.unpack_from(">I", data, cursor + 8)[0]] = cursor
        cursor = data.find(b"PERS-SZP", cursor + 8)
    # bank magic + ".WBK" name appear as literal bytes inside each bank's Yay0 stream
    banks = []
    cursor = data.find(BANK_MAGIC)
    while cursor >= 0:
        name = data[cursor + 0x10:cursor + 0x30].split(b"\0")[0].split(b".")[0].decode("ascii", "replace")
        banks.append((cursor, name or f"{cursor:X}"))
        cursor = data.find(BANK_MAGIC, cursor + 16)
    candidates = list(CURATED_REGIONS)
    for offset, total, count, table_end in find_archives(data):
        if any(offset < end and start < offset + total for start, end in taken):
            candidates.append((offset, offset + table_end, f"archive_{offset:X}_dir",
                               f"directory of a {count}-member archive; fragment members mapped separately"))
        else:
            candidates.append((offset, offset + total, f"archive_{offset:X}",
                               f"{count}-member archive without fragment members"))
    for block in report["yay0_blocks"]:
        if "rom_end" not in block or "fragment_words" in block:
            continue
        start, end = int(block["rom_start"], 0), int(block["rom_end"], 0)
        if start in wrappers:
            candidates.append((wrappers[start], end, f"szp_{wrappers[start]:X}",
                               f"PERS-SZP data, decoded size 0x{block['decoded_size']:X}"))
        elif crunch64.yay0.decompress(data[start:end])[:16] == BANK_MAGIC:
            name = next(n for o, n in banks if o > start)
            candidates.append((start, end, f"audio_{name}_bank_yay0",
                               f"Yay0 copy of the {name} pointer tables, the copy the game loads"))
        else:
            candidates.append((start, end, f"yay0_{start:X}",
                               f"Yay0 data, decoded size 0x{block['decoded_size']:X}"))
    cursor = data.find(b"PRESJPEG")
    while cursor >= 0:
        jpeg = cursor + struct.unpack_from(">I", data, cursor + 8)[0]
        eoi = data.find(b"\xFF\xD9", jpeg)
        if data[jpeg:jpeg + 2] == b"\xFF\xD8" and eoi > 0:
            candidates.append((cursor, eoi + 2, f"jpeg_{cursor:X}", "PRESJPEG background, baseline JPEG"))
        cursor = data.find(b"PRESJPEG", cursor + 8)
    for offset, name in banks:
        waves = data.find(WAVE_MAGIC, offset, offset + 0x40000)
        candidates.append((waves, None, f"audio_{name}_wavetables", "N64 WaveTables header and ADPCM sample data"))
    regions = []
    for start, end, label, evidence in sorted(candidates, key=lambda c: (c[0], -(c[1] or len(data)))):
        if not any(start < e and s < (end or start + 1) for s, e in taken):
            regions.append([start, end, label, evidence])
            taken.append((start, end or start + 1))
    regions.sort()
    for region in regions:
        if region[1] is None:
            end = min([s for s, _ in taken if s > region[0]] + [len(data)])
            while end > region[0] + 1 and data[end - 1] == 0xFF:
                end -= 1
            region[1] = end
    return [tuple(region) for region in regions]


def mapping_yaml(report, regions=(), data=None):
    """Generate an opaque-byte split: mapped images are not all declared code."""
    ranges = [
        (0, 0x40, "header"),
        (0x40, 0xB70, "ipl3"),
        (0xB70, 0x1000, "boot_tail"),
        (0x1000, 0x1060, "resident_entry"),
        (0x1060, 0x5D8C0, "resident_cpu_text"),
        (0x5D8C0, 0x80C00, "resident_ucode_and_data"),
    ]
    for index, fragment in enumerate(report["fragments"]):
        start = int(fragment["rom_start"], 0)
        end = int(fragment["rom_consumed_end"], 0)
        label = f"fragment_image_{index:03d}_{start:X}"
        ranges.append((start, end, label))
    ranges.extend((start, end, label) for start, end, label, _ in regions)
    ranges.sort()

    def gap(start, end):
        fill = set(data[start:end]) if data is not None else None
        return "pad" if fill and fill <= {0, 0xFF} else "opaque"
    lines = [
        "# Generated by tools/map_rom.py. Mapping-only, NOT a build configuration.",
        "# Every range is opaque bin; per-fragment text/data boundaries remain pending.",
        "# Non-fragment labels come from asset_regions() (docs/mappings/asset-regions.csv);",
        "# pad_ ranges hold only 0x00 and/or 0xFF bytes.",
        "name: Pokemon Stadium Zero (Japan), storage mapping",
        f"sha1: {report['sha1']}",
        "options:",
        "  basename: pokestadium0-mapping",
        "  platform: n64",
        "  base_path: ../..",
        "  target_path: baseroms/jp/baserom.z64",
        "  asset_path: assets/mapping",
        "  ld_script_path: build/mapping/pokestadium0.ld",
        "  ld_symbol_header_path: build/mapping/ld_symbols.h",
        "  create_asm_dependencies: false",
        "segments:",
    ]
    cursor = 0
    for start, end, label in ranges:
        if start < cursor:
            raise ValueError("overlapping mapping-only intervals")
        if start > cursor:
            lines.append(f"  - [0x{cursor:X}, bin, {gap(cursor, start)}_{cursor:X}]")
        lines.append(f"  - [0x{start:X}, bin, {label}]")
        cursor = end
    if cursor < report["size"]:
        lines.append(f"  - [0x{cursor:X}, bin, {gap(cursor, report['size'])}_{cursor:X}]")
    lines.append(f"  - [0x{report['size']:X}]")
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("rom", type=Path)
    parser.add_argument("--disasm", nargs=3, metavar=("START", "END", "VRAM"))
    parser.add_argument("--headers", action="store_true")
    parser.add_argument("--output-dir", type=Path)
    parser.add_argument("--mapping-yaml", type=Path)
    args = parser.parse_args()
    data = args.rom.read_bytes()
    if hashlib.sha256(data).hexdigest() != EXPECTED_SHA256:
        raise ValueError("input differs from the inspected Stadium Zero ROM")
    if args.disasm:
        start, end, vram = (int(value, 0) for value in args.disasm)
        for offset in range(start, end, 4):
            word = struct.unpack_from(">I", data, offset)[0]
            instruction = rabbitizer.Instruction(word, vram + offset - start)
            print(f"{offset:08X} {vram + offset - start:08X} {word:08X}  {instruction.disassemble()}")
        return
    headers = []
    position = 0
    while True:
        position = data.find(b"FRAGMENT", position)
        if position < 0:
            break
        start = position - 8
        words = struct.unpack_from(">8I", data, start)
        entry = 0x80000000 | ((words[0] & 0x3FFFFFF) << 2)
        base = entry & 0xFFF00000
        structurally_valid = (
            start % 16 == 0 and words[0] >> 26 == 2 and words[1] == 0
            and words[4] == 0x20 and 0x81000000 <= base < 0x90000000
            and 0x20 <= words[5] < words[6]
            and start + words[6] <= len(data)
        )
        record = {
            "rom_start": f"0x{start:08X}",
            "words": [f"0x{word:08X}" for word in words],
            "structurally_valid": structurally_valid,
        }
        if structurally_valid:
            count = struct.unpack_from(">I", data, start + words[5])[0]
            records_end = start + words[5] + 4 + count * 4
            relocations = []
            if records_end <= start + words[6]:
                relocations = list(struct.unpack_from(
                    f">{count}I", data, start + words[5] + 4))
            errors = []
            if records_end > start + words[6]:
                errors.append("relocation table overruns ROM size")
            for relocation in relocations:
                offset = relocation & 0xFFFFFF
                kind = (relocation >> 24) & 0x7F
                if kind not in (2, 4, 5, 6):
                    errors.append(f"unsupported relocation kind {kind}")
                if offset % 4 or offset >= words[5]:
                    errors.append(f"bad relocation offset {offset:#x}")
            record.update({
                "link_base": f"0x{base:08X}",
                "entry_vram": f"0x{entry:08X}",
                "entry_offset": f"0x{entry-base:X}",
                "reloc_offset": f"0x{words[5]:X}",
                "rom_end": f"0x{start+words[6]:08X}",
                "rom_size": f"0x{words[6]:X}",
                "ram_size": f"0x{words[7]:X}",
                "relocation_count": count,
                "relocation_errors": sorted(set(errors)),
            })
        headers.append(record)
        position += 8
    compressed = []
    fragments = []
    wrappers = {}
    wrapper_cursor = 0
    while True:
        wrapper_cursor = data.find(b"PERS-SZP", wrapper_cursor)
        if wrapper_cursor < 0:
            break
        payload_offset, decoded_size, ram_size, patch_count = struct.unpack_from(
            ">4I", data, wrapper_cursor + 8)
        if payload_offset == 24 + patch_count * 8:
            wrappers[wrapper_cursor + payload_offset] = {
                "start": wrapper_cursor, "decoded_size": decoded_size,
                "ram_size": ram_size, "patch_count": patch_count,
            }
        wrapper_cursor += 8
    position = 0
    while True:
        position = data.find(b"Yay0", position)
        if position < 0:
            break
        offset = position
        position += 4
        size, links, literals = struct.unpack_from(">3I", data, offset + 4)
        if not (0 < size <= 0x1000000 and 16 <= links <= literals
                and offset + literals < len(data)):
            continue
        try:
            decoded, consumed = trace_yay0(data[offset:])
        except Exception as error:
            compressed.append({"rom_start": f"0x{offset:X}", "error": str(error)})
            continue
        record = {
            "rom_start": f"0x{offset:08X}", "rom_end": f"0x{offset+consumed:08X}",
            "decoded_size": len(decoded),
        }
        if decoded[8:16] == b"FRAGMENT":
            wrapper = wrappers.get(offset)
            if wrapper is None:
                raise ValueError(f"fragment at {offset:#x} has no PERS-SZP owner")
            if len(decoded) != wrapper["decoded_size"]:
                raise ValueError("PERS-SZP decoded size disagreement")
            restored = bytearray(decoded)
            for patch_index in range(wrapper["patch_count"]):
                value, patch_offset = struct.unpack_from(
                    ">2I", data, wrapper["start"] + 24 + patch_index * 8)
                if patch_offset % 4 or patch_offset + 4 > len(restored):
                    raise ValueError("PERS-SZP patch overrun")
                struct.pack_into(">I", restored, patch_offset, value)
            info = inspect_fragment(restored)
            info.update({
                "storage": "PERS-SZP/Yay0",
                "rom_start": f"0x{wrapper['start']:08X}",
                "compressed_payload_start": f"0x{offset:08X}",
                "rom_consumed_end": f"0x{offset+consumed:08X}",
                "wrapper_patch_count": wrapper["patch_count"],
                "decoded_sha256": hashlib.sha256(restored).hexdigest(),
            })
            fragments.append(info)
            words = struct.unpack_from(">8I", restored)
            record["fragment_words"] = [f"0x{word:08X}" for word in words]
        compressed.append(record)
    for header in headers:
        start = int(header["rom_start"], 0)
        owners = [
            block["rom_start"] for block in compressed
            if "rom_end" in block and int(block["rom_start"], 0)
            <= start < int(block["rom_end"], 0)
        ]
        if owners:
            header["inside_yay0"] = owners
        if header["structurally_valid"] and not owners:
            size = int(header["rom_size"], 0)
            info = inspect_fragment(data[start:start+size])
            info.update({
                "storage": "raw",
                "rom_start": f"0x{start:08X}",
                "rom_consumed_end": f"0x{start+size:08X}",
                "decoded_sha256": hashlib.sha256(data[start:start+size]).hexdigest(),
            })
            fragments.append(info)
    fragments.sort(key=lambda fragment: int(fragment["rom_start"], 0))
    for left, right in zip(fragments, fragments[1:]):
        if int(left["rom_consumed_end"], 0) > int(right["rom_start"], 0):
            raise ValueError("fragment storage ranges overlap")
    report = {
        "size": len(data),
        "md5": hashlib.md5(data).hexdigest(),
        "sha1": hashlib.sha1(data).hexdigest(),
        "sha256": hashlib.sha256(data).hexdigest(),
        "header_hex": data[:64].hex(),
        "fragment_header_candidates": headers,
        "yay0_blocks": compressed,
        "resident": {
            "rom_start": "0x1000", "rom_end": "0x80C00",
            "link_start": "0x80000400", "link_end": "0x80080000",
            "rom_to_vram": "0x80000400 + (rom_offset - 0x1000)",
            "cpu_text_rom_end": "0x5D8C0",
            "cpu_text_vram_end": "0x8005CCC0",
            "cpu_text_end_basis": "RSP task builder 0x80003308 uses 0x8005CCC0 as microcode boot",
            "bss_start": "0x80080000", "bss_end": "0x80105360",
            "bss_size": "0x85360",
            "header_pc": "0x80100400",
            "boot_pc_adjustment": "-0x100000, inspected IPL3 at ROM 0x4D0 and 0x570",
            "boot_dma_range": "[0x1000, 0x101004); larger than logical resident image",
            "ucode_and_data": "[0x5D8C0, 0x80C00), internal boundaries pending",
        },
        "fragments": fragments,
        "summary": {
            "raw_fragments": sum(f["storage"] == "raw" for f in fragments),
            "compressed_fragments": sum(f["storage"] != "raw" for f in fragments),
            "fragment_images": len(fragments),
            "unique_link_bases": len({f["link_base"] for f in fragments}),
            "slot_image_counts": dict(Counter(f["link_base"] for f in fragments)),
            "yay0_blocks_checked_against_crunch64": len(compressed),
            "yay0_decode_errors": sum("error" in block for block in compressed),
            "relocation_records_checked": sum(f["relocation_count"] for f in fragments),
            "wrapper_patches_applied": sum(f.get("wrapper_patch_count", 0) for f in fragments),
        },
    }
    regions = asset_regions(data, report)
    if args.mapping_yaml:
        args.mapping_yaml.parent.mkdir(parents=True, exist_ok=True)
        args.mapping_yaml.write_text(mapping_yaml(report, regions, data), encoding="utf-8")
    serialized = json.dumps(report, indent=2) + "\n"
    if args.output_dir:
        args.output_dir.mkdir(parents=True, exist_ok=True)
        (args.output_dir / "resident-fragments.json").write_text(serialized, encoding="utf-8")
        fields = ["storage", "rom_start", "rom_consumed_end", "link_base",
                  "fragment_slot", "entry_link_vram", "entry_offset", "reloc_offset",
                  "image_size", "ram_size", "relocation_count", "wrapper_patch_count",
                  "decoded_sha256"]
        with (args.output_dir / "fragment-mappings.csv").open("w", newline="", encoding="utf-8") as output:
            writer = csv.DictWriter(output, fields, extrasaction="ignore")
            writer.writeheader()
            writer.writerows(fragments)
        with (args.output_dir / "asset-regions.csv").open("w", newline="", encoding="utf-8") as output:
            writer = csv.writer(output)
            writer.writerow(["rom_start", "rom_end", "label", "evidence"])
            writer.writerows((f"0x{s:08X}", f"0x{e:08X}", label, why) for s, e, label, why in regions)
        print(json.dumps(report["summary"], indent=2))
    else:
        print(serialized, end="")


if __name__ == "__main__":
    main()
