# First matching pass

This page records the historical first pass. Current verified totals are in
[COVERAGE.md](../COVERAGE.md); the latest continuation is recorded in
[matching-2026-11-02-lab.md](matching-2026-11-02-lab.md).

This pass put C into the tree for every function that matched without hand
work, from two sources:

1. **The Stadium 1 decomp** ([team-hippodrome/pokestadium](https://github.com/team-hippodrome/pokestadium),
   the Japanese Stadium 2). Stadium Zero is built with the same IDO 7.1 `-O2 -mips2`
   flags, and most of its resident code is Stadium 1's files in the same order.
2. **m2c's first output** (`--target mips-ido-c --valid-syntax`), compiled unchanged.

| | Functions |
| --- | ---: |
| Assembly owners (first-pass inventory) | 5,444 |
| Matched by m2c's first output, compiled alone | 1,577 |
| Matched by a Stadium 1 or ultralib function, compiled in its own TU | 2,191 |
| Either of the two | 3,014 |
| Now C in `src/` and passing `tools/check_functions.py` | 2,804 (2,004 Stadium 1, 800 m2c) |
| **Built as C by the full-ROM `make rom`** | **2,919** (incl. 151 from unmodified ultralib) |
| Identified as libultra (ultralib 2.0I, IDO 5.3), kept as `GLOBAL_ASM` | 173 |

The first three rows count functions that compiled to the ROM bytes in isolation.
Some did not survive the move into shared Stadium Zero files. The usual
reasons were an m2c declaration that conflicts with a header prototype, a Stadium 1
name that maps to two Stadium Zero addresses, or alignment padding inside a
function that depends on its offset in the object. Those functions stay as `GLOBAL_ASM`.

## How Stadium 1 counterparts were found

* Every Stadium 1 source file was compiled for both `VERSION_US` and `VERSION_JP`,
  and ultralib was built for 2.0I. Each function was then fingerprinted by
  its instruction words, with relocated fields masked.
* Fingerprint hits were confirmed with the same address-solving comparison that
  `tools/check_functions.py` uses. Stadium 1 file-static data has no symbols in
  IDO objects. To name it, each Stadium 1 file was recompiled with a probe function
  that takes the address of every static variable, which recovers the
  (section, offset) → name mapping.
* When several Stadium 1 functions compile identically, the choice is
  made greedily, longest function first. A candidate is accepted only if all of its
  symbol bindings agree with the names already assigned. Ties go to the Stadium 1
  file of the neighbouring functions.

## Source layout

Resident code that used to be `src/1060.c` is now split at Stadium 1 file
boundaries: `src/rsp.c`, `src/dma.c`, and so on. Fragments with Stadium 1
counterparts became directories, such as `src/fragments/fragment012_17ED00/`. Runs
with no counterpart are named by ROM offset (resident) or link address (fragments).
These are working groupings, not recovered translation units. A split also happens
where the ROM has 16-byte alignment padding, which marks the end of an object's `.text`.

Ported files keep the Stadium 1 preamble: includes, macros and types. Stadium 1
data definitions become `extern` declarations, and their Stadium Zero
addresses are in `linker_scripts/jp/symbol_addrs.txt`. Stadium 1 names whose
spelling encodes a Stadium 1 address (`D_80083C1C`, `func_800338B0`) were renamed
to the Stadium Zero address. Unbound address-style declarations were dropped from
the copied headers. Headers come from Stadium 1 (`include/`, `src/**/*.h`), and
`lib/ultralib` is vendored as in Stadium 1.

`docs/function-matches.csv` lists every owner: where it lives, its C name, and
whether it is a Stadium 1 port (with the source file), m2c output, libultra, or asm.

## Verifying

```sh
make init                                    # Python packages, IDO 5.3 and 7.1, extraction
make rom                                     # full-ROM build of src/, compared with the base ROM
.venv/bin/python tools/check_functions.py    # 2804 functions checked in 388 files, 0 failures
```

`check_functions.py` compiles each source with `-DNON_MATCHING`, which leaves only
the C functions. Each object function is compared with its owner's ROM words. All
non-relocated words must be identical. Relocated fields must resolve to the
address in `symbol_addrs.txt` or to the address in the symbol's name, and must be
consistent within the function. Per-file compiler overrides (IDO 5.3 for libleo and
the JPEG code, `-signed` for `hal_libc.c`) are in `tools/cflags_overrides.json`.

`check_functions.py` is a quick per-function check. `make rom` is the real gate: it
builds every `src/` file whole through asm-processor and links it at its ROM
address (see [production-build.md](production-build.md)). Of the 2,804 matching
functions, most are built as C there; 89 of those needed their file's
data placed at its ROM address (`config/jp/sections.json`). The rest reference
literals, jump tables or statics in files whose remaining `GLOBAL_ASM` functions
own data in between, so they stay behind `#ifdef NON_MATCHING` with the
`GLOBAL_ASM` in the `#else`.
One more function (`func_8004F8B4` in `src/libultra/audio/reverb.c`) came from
the single-function m2c candidates.

Building whole files exposed one missed object boundary: `fragment007_166580.c`
is now split at 0x82008C40, where the ROM pads to 16 bytes after a C function.
