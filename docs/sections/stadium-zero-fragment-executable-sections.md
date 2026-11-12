# Stadium Zero per-fragment executable sections

This is an evidence-labeled section map for all 259 restored fragment images in the Japanese-only original Pokémon Stadium. It distinguishes CPU instructions supported by relocation/control-flow evidence, inferred contiguous text envelopes, and unclassified payload; it is not a completed function inventory or a matching-ROM build.

## Input and baseline

- **Repository baseline:** private `bike-noonwood/pokestadium0`, `master`, scaffold commit `55dba795d7ac465734a928a5251788044aba49f3`. This records the initial analysis snapshot; see repository history for publication and [the refinement report](refined/flow-and-gap-validation.md) for subsequent results.
- **Attribution:** Team Hippodrome original. The decompilation follows pret conventions; pret is not involved with the recompilation.
- **Input:** Japan-only original Stadium, 16 MiB, SHA256 `ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`. An independent known-good dump checksum remains unestablished.
- **Storage baseline:** `docs/mappings/resident-fragments.json` establishes 27 raw and 232 compressed images. Every compressed image is decoded with its wrapper restoration patches applied, and each restored-image hash must equal the prior manifest.
- **Coordinates:** section offsets refer to the restored fragment image, not offsets into the compressed ROM stream. Add the image's link base to obtain link-time addresses; this is not necessarily its allocated runtime address.

## Results

The generated `fragment-sections.json` and `fragment-sections.csv` report:

- **187 images with CPU-code evidence:** the 26 initial raw images, eight later resource-oriented images with executable prefixes, and 153 images with seven-instruction entry stubs.
- **72 images without CPU-code evidence:** indices 26–29, 35–37, 41–42, and 43–105. Their payload remains unclassified rather than being blindly marked executable or conclusively declared all data.
- **849,076 instruction bytes:** words reached from accepted seeds, including delay slots. This is not a count of functions or exhaustive recovered code.
- **925,560 candidate text-envelope bytes:** the sum of contiguous candidate prefixes. The additional 76,484 bytes contain valid instruction-shaped gaps or zero fill, not independently established executable words.
- **13 images with unresolved indirect control transfers:** the report field `unresolved_indirect_jumps` includes both indirect calls (`jalr`) and non-return indirect jumps. These are not yet resolved jump tables or callback inventories.
- **Zero rejected seeded paths:** the accepted seed traversal did not encounter malformed instructions or invalid delay slots. This does not mean every possible execution path has been recovered.

All 153 images at indices 106–258 have the same executable offset span `[0x20,0x3C)`. Their link base is `0x8FF00000`, so that span is `[0x8FF00020,0x8FF0003C)` at link time. Their instructions contain image-specific pointers and must not be treated as byte-identical functions or one shared runtime image.

## Candidate text envelopes

These are end-exclusive, restored-image offsets. All start at `0x20`; full instruction-evidence spans and candidate gaps are recorded separately in the JSON. Envelope boundaries are inferred, not original ELF section records.

| Image index | ROM storage start | Link base | Candidate text end |
|---|---|---|---|
| 0 | 0x00080C00 | 0x81100000 | 0x1C4E8 |
| 1 | 0x0015B1A0 | 0x81000000 | 0x2298 |
| 2 | 0x0015E220 | 0x81200000 | 0xD1C |
| 3 | 0x0015F390 | 0x81500000 | 0x538 |
| 4 | 0x0015F8F0 | 0x81300000 | 0x364 |
| 5 | 0x0015FCE0 | 0x82300000 | 0x27F4 |
| 6 | 0x00162BE0 | 0x88400000 | 0x2D68 |
| 7 | 0x00166580 | 0x82000000 | 0x8F50 |
| 8 | 0x001720F0 | 0x88100000 | 0x2D6C |
| 9 | 0x00175570 | 0x82400000 | 0x400 |
| 10 | 0x0017BE70 | 0x81700000 | 0x1AF4 |
| 11 | 0x0017E340 | 0x81800000 | 0x758 |
| 12 | 0x0017ED00 | 0x82100000 | 0x88DD0 |
| 13 | 0x00232510 | 0x82200000 | 0x2C20 |
| 14 | 0x00235D70 | 0x88000000 | 0x1FC4 |
| 15 | 0x00238BD0 | 0x89000000 | 0xA580 |
| 16 | 0x00252E10 | 0x89100000 | 0xA7E4 |
| 17 | 0x00261F00 | 0x8A000000 | 0x5F0 |
| 18 | 0x00262620 | 0x8A100000 | 0x57D0 |
| 19 | 0x00293410 | 0x8A200000 | 0x32FC |
| 20 | 0x002B1360 | 0x8E000000 | 0x78 |
| 21 | 0x002B13F0 | 0x8E100000 | 0x7C |
| 22 | 0x002B1480 | 0x8E200000 | 0x7C |
| 23 | 0x002B1510 | 0x8E300000 | 0x78 |
| 24 | 0x002B15A0 | 0x8E400000 | 0x78 |
| 25 | 0x002B16A0 | 0x81600000 | 0x8AC |
| 30 | 0x00326700 | 0x8F100000 | 0x250 |
| 31 | 0x003553C0 | 0x8F200000 | 0x540 |
| 32 | 0x0035C390 | 0x8F500000 | 0x408 |
| 33 | 0x0035E790 | 0x8F600000 | 0x7B0 |
| 34 | 0x00369F50 | 0x8EB00000 | 0x404 |
| 38 | 0x0038A540 | 0x8F400000 | 0xCC |
| 39 | 0x003C5200 | 0x8E800000 | 0x134 |
| 40 | 0x003CE090 | 0x8E900000 | 0x134 |
| 106–258 | See CSV per image | 0x8FF00000 | 0x3C |

For image 0, the resulting link-time instruction envelope ends at `0x8111C4E8`, corresponding to raw ROM offset `0x0009D0E8`. Two zero words follow, then non-instruction payload begins at image offset `0x1C4F0`. The zero words are labeled separately, not counted as executable instructions.

## Rules and inspected corrections

- **Header targets are conditional seeds:** the standard header J is present on data-oriented images too. The mapper requires body instruction relocations, or a negative-stack-adjustment entry shape for the small no-body-relocation wrappers; it does not accept arbitrary valid-looking header targets.
- **Instruction relocation sites:** types 4, 5 and 6 inside the payload supply seeds. Type 2 pointer targets are recorded but not independently traversed.
- **Delay slots:** relocation sites in a delay slot are seeded through the preceding control-transfer instruction. They must not create fallthrough past an unconditional jump or return.
- **Direct flow:** local J/JAL and branch destinations are traversed. Call return continuations are traversed; non-return indirect jumps stop exploration. `jr ra` is a terminal return.
- **Inspected image-0 tail:** handlers at offsets `0x1C43C`, `0x1C460`, `0x1C468`, and `0x1C494` contain no later relocation sites. Their disassembly is retained in `evidence/section-boundary-disassembly.txt`, and they are explicit, input-specific seeds.
- **Candidate envelope checks:** every gap word inside a proposed prefix decodes as a non-trap CPU instruction or zero. No type-2 relocation storage sites lie inside any proposed prefix. These are supporting checks, not proof that every gap is executed.
- **Payload remainder:** unknown words stay `unclassified_payload`. The map does not infer `.data`, `.rodata`, textures, display lists, BSS, or function boundaries from instruction appearance alone.

`sections` partitions each decoded stored image exactly into header, instruction evidence, candidate words/zero fill, unclassified payload, and relocation-table/storage tail. No words are lost or duplicated. Header instructions are not included in the payload CPU-instruction count.

## Reproduction and verification

Run from the repo root after installing `requirements-mapping.txt` into `.venv`. PowerShell examples:

```powershell
& ./.venv/bin/python tools/map_fragment_sections.py baseroms/jp/baserom.z64
& ./.venv/bin/python tools/test_fragment_sections.py
& ./.venv/bin/python tools/test_map_rom.py
```

The section mapper has eight passing tests: five synthetic regressions and three input-backed checks covering all 259 restored images. The earlier storage mapper's six tests also pass. A second section-map generation produced identical JSON and CSV hashes:

- **JSON SHA256:** `d6fc35e111d6251e3c0747b7350b24b7a4ec9826fc6652db9a8d01abe34da4ae`.
- **CSV SHA256:** `a07daa6796162a2f6f3595069ed0f96eb1dcd3e744936de97dcd99d72244628b`.

The evidence log retains test output, generation output, hashes, and selected raw disassembly. No ROM, decompressed image binary, or extracted retail resource is included in this deliverable.

## Sanity check and next gate

This establishes reproducible evidence spans and candidate executable prefixes, not exhaustive executable-section recovery. Unresolved indirect transfers, unseeded leaf functions, possible code beyond the observed prefixes, and the exact code-versus-padding classification of valid-looking gaps still need verification before broad `/src` pragma generation. The stack-prologue rule is a heuristic and is covered by the known input inventory rather than a universal fragment-format guarantee.

Neither a production compiler identification nor a rebuilt-ROM byte-identity gate has passed. No Stadium 1/2 library match claim has been made. This report was prepared before GitHub publication; repository history records the publication commit.
