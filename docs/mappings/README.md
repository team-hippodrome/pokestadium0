# Stadium Zero resident and fragment mappings

This mapping pass uses the supplied Japanese Stadium Zero ROM, not a linear
disassembly of its whole contents. `resident-fragments.json` is the full
machine-readable evidence inventory; `fragment-mappings.csv` contains one row
per fragment image. These files contain metadata, not a ROM or extracted assets.

Prepared on 2026-10-10 against local repository baseline
`55dba795d7ac465734a928a5251788044aba49f3`. This is the analysis baseline;
publication history is recorded by the repository commits.

## Input and scope

- Input size: `0x1000000` bytes.
- MD5: `c46e087d966a35095df96799b0b4ffae`.
- SHA-1: `8bc8d2ff7df25b26bd0c353d2adfe83e4e3a7a87`.
- SHA-256: `ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
- Header: big-endian magic `80 37 12 40`, title `POKEMON STADIUM`, cartridge
  bytes `CPSJ`, revision byte `00`, header PC `0x80100400`.
- Provenance: user-supplied Project Files ROM, hydrated from its LFS object.
  The SHA-256 matches that object. An independent known-good dump database
  checksum has NOT been established.

All findings below come from the inspected ROM bytes and the cited ROM offsets.
The script is deliberately restricted to this exact SHA-256. No other region,
revision, compiler, or game has been verified by these findings.

## Resident image

| Component | ROM range, end exclusive | Runtime/link address | Evidence |
|---|---|---|---|
| Header | `0x0..0x40` | Not executable | Header bytes |
| IPL3 | `0x40..0xB70` | Initially `0xA4000040` | Inspected boot instructions; later copy to `0x80000000` |
| Boot tail | `0xB70..0x1000` | Not treated as CPU text | Includes font bytes loaded by `0x80001868` from ROM `0xB70..0xC70`; full tail not subdivided |
| Resident entry | `0x1000..0x1060` | `0x80000400..0x80000460` | Entry instructions at ROM `0x1000` |
| Resident CPU-text envelope after entry | `0x1060..0x5D8C0` | `0x80000460..0x8005CCC0` | Last CPU routine ends at ROM `0x5D8C0`; RSP task builder uses `0x8005CCC0` as its microcode boot pointer |
| Resident microcode and data | `0x5D8C0..0x80C00` | `0x8005CCC0..0x80080000` | RSP task construction and first fragment header; internal section boundaries pending |
| Resident BSS | No ROM bytes | `0x80080000..0x80105360` | Entry clears `0x85360` bytes from `0x80080000` |

The resident mapping is
`vram = 0x80000400 + (rom_offset - 0x1000)`.
This formula stops at the logical resident image end, `0x80C00`; it must NOT
be applied across the rest of the ROM.

The header PC is not the executed resident entry address. IPL3 reads that PC and
subtracts `0x100000` at ROM `0x4D0..0x4E0` when programming PI DRAM destination,
and again at `0x560..0x570` when constructing the entry address. Thus the observed
`0x80100400` header PC maps to `0x80000400`. IPL3 copies its later boot routine
from `0xA40004C0..0xA4000768` to RAM `0x80000000` at ROM `0x458..0x4BC`.

The boot transfer itself is larger than the logical resident image. ROM
`0x50C..0x518` programs PI length `0x100003`, meaning `0x100004` transferred
bytes, from ROM `0x1000` through `0x101004` exclusive. Some fragment bytes are
therefore initially copied as well; that does not make them resident CPU text.

The RSP boundary has independent caller evidence: resident function
`0x80003308`, ROM `0x3F08..0x3FB8`, constructs a task with boot pointer
`0x8005CCC0`, boot size `0xD0`, microcode pointer `0x8005ED80`, microcode size
`0x1000`, data pointer `0x8007FFA0`, and data size `0x800`. This prevents RSP
instructions and data from becoming accidental CPU-function pragmas. The
CPU-text envelope is not a recovered list of original translation units or
proof that every detected function boundary within it is correct.

## Fragment loader and format

These are descriptive roles inferred from inspected instructions, not recovered
original function names:

- `0x800040B4`, ROM `0x4CB4..0x4D08`: loads a ROM interval through
  `0x80003A24`, then invokes the fragment-loading/relocation path.
- `0x800044AC`, ROM `0x50AC..0x51BC`: archive-member loader checks `FRAG` and
  `MENT` at header offsets `+8` and `+0xC`, then invokes `0x8000401C`.
- `0x8000401C`, ROM `0x4C1C..0x4CB4`: obtains allocation size, attaches fragment
  metadata, uses header RAM size at `+0x1C` to resize storage, and invokes
  relocation at `0x80001C50`.
- `0x80001C50`, ROM `0x2850..0x2AB0`: reads relocation offset `+0x14`, RAM
  size `+0x1C`, registers the loaded image, processes relocation types
  `2`, `4`, `5`, and `6`, then clears the relocation/BSS tail and writes back cache.
  The earlier broad split incorrectly truncated this routine at `0x80001D6C`;
  the evidence here uses raw ROM decoding through its actual return.
- `0x80001EE0`, ROM `0x2AE0..0x2B44`: resolves addresses in
  `0x81000000..0x90000000` using an eight-byte-per-slot mapping table at
  `0x800A8D20`. Slot is `((address & 0x0FF00000) >> 20) - 0x10`,
  and the intra-image offset is `address & 0xFFFFF`.
- `0x80025B60`, ROM `0x26760..0x267A0`: receives a loaded image pointer,
  calls it through `jalr`, and releases it afterward.

| Offset | Meaning established for this ROM |
|---|---|
| `+0x00` | Jump instruction to the link-time entry, not necessarily offset `0x20` |
| `+0x04` | NOP delay slot |
| `+0x08..+0x0F` | `FRAGMENT` signature |
| `+0x10` | `0x20` in every mapped image; payload starts here, not necessarily the entry |
| `+0x14` | Relocation table offset relative to image start |
| `+0x18` | Stored/decoded image size, structurally corroborated across all images |
| `+0x1C` | Required RAM size; can be smaller than stored size because relocations are discarded |

The link base is derived from the entry jump's one-megabyte slot. It is a
relocatable link-time namespace, NOT an assertion that the game loads the image
at that fixed RAM address. Actual placement depends on the allocator and mapping
table. No emulator runtime capture was performed.

## Compressed storage

The game loader explicitly supports `PERS-SZP` and `PRESJPEG` containers in
`0x80003A24`. For `PERS-SZP`, `0x800036A0`, ROM `0x42A0..0x4374`,
uses payload offset `+8`, decoded size `+0xC`, allocated size `+0x10`,
and restoration-patch count `+0x14`. Each patch at `+0x18` onward is
`(word_value, decoded_offset)`. It invokes `0x800093E0` on the Yay0 payload,
restores these words, and clears any allocated tail.

The scanner independently decodes Yay0 mask, link and literal streams,
records their exact consumed extent, and compares every decoded result with
`crunch64.yay0.decompress`. Compressed fragment validation is performed AFTER
the wrapper restoration patches, matching the inspected load path.

`rom_consumed_end` is the byte after the final byte consumed by a raw image or
compressed stream. It is not automatically the archive member's padded end.
Archive directory ownership and member padding are not yet fully mapped.

## Results and checks

- 27 raw fragment images and 232 compressed fragment images, totaling 259.
- 44 unique link-time slots; 216 images reuse `0x8FF00000`.
- 790 Yay0 blocks decoded with two agreeing implementations; no decode errors.
- 90,161 relocation records checked for supported type, aligned in-payload
  offset and table bounds; jump and HI16 records also checked against J/JAL and
  LUI opcodes respectively.
- 88 compressed-wrapper restoration patches applied with bounds checks.
- Entry jump targets fall within each image's pre-relocation payload.
- Fragment storage ranges are non-overlapping.
- All 259 raw `FRAGMENT` signature hits are accounted for: 27 are raw images,
  and 232 are literal bytes inside identified compressed streams.
- The mapping-only splat run produced 489 bins covering the entire 16 MiB ROM.
  Every bin was compared with its original input interval and the concatenated
  SHA-256 agrees. This is extraction partition identity, not a ROM build.
- Six focused tests pass: literal Yay0 decoding, overlapping backreferences,
  bad-backreference rejection, bad-fragment-header rejection, manifest extents,
  and byte-exact reproduction of the input from the mapping-only bins.
- Regenerated JSON, CSV and YAML hashes were unchanged on a second scanner run.
- Slot and ROM offsets are preserved independently; image count is NOT function
  count, and reusable slots are NOT globally unique loaded addresses.

The first raw fragment is ROM `0x80C00..0xDA9B0`, link slot `0x81100000`,
entry `0x81100020`, relocation offset `0x54B20`, stored size `0x59DB0`,
and RAM size `0x8C970`. A resident caller gives further corroboration for two
other raw images: `0x80025F3C`, ROM `0x26B3C..0x26BDC`, loads ROM
`0x15F390..0x15F8F0` for slot `0x81500000` and ROM
`0x17ED00..0x232510` for slot `0x82100000`. Those intervals exactly agree
with their headers.

## Reproduction and next gate

From the repository root, using the privately supplied ROM:

```powershell
.\.venv\Scripts\python.exe tools/map_rom.py baseroms/jp/baserom.z64 --output-dir docs/mappings --mapping-yaml yamls/jp/mapping.yaml
.\.venv\Scripts\python.exe -m splat split yamls/jp/mapping.yaml
.\.venv\Scripts\python.exe tools/test_map_rom.py -v
```

The tested sandbox invocation uses `.venv/bin/python` instead. Tested packages:
Python `3.14`, rabbitizer `1.16.2`, spimdisasm `1.42.4`, splat64 `0.50.1`;
see `requirements-mapping.txt` for the isolated mapping dependencies.
No claim of production compiler suitability follows from this Python-tool run.

The scanner and the independent decoder use `crunch64 0.6.2` as the comparison
oracle, after separate stream traversal. `n64img 0.3.3` and `pygfxd 1.0.5` are
pinned because the tested splat import requires them even for an opaque-bin split.

`yamls/jp/mapping.yaml` partitions the whole ROM into opaque bins, preserving
the mapped boundaries without declaring mixed fragment payloads to be code.
It is an extraction/storage oracle, not the production build YAML.

Before regenerating `/src`, establish each fragment's executable ranges and
text/data/rodata split, then disassemble with its own link-time namespace.
Library-overlap comparisons, original compiler confirmation, recovered
translation-unit boundaries and rebuilt-ROM byte identity remain unrun.

The rejected linear split and its generated `src/main.c` are kept only in
ignored `.analysis/broad-extraction/` scratch. They are not accepted source.
This report was prepared before GitHub publication. See repository history for
the publication commit, and [the refined flow report](../sections/refined/flow-and-gap-validation.md)
for the subsequent executable-section and indirect-transfer analysis.
