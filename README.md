# AI Disclosure

This repo is almost entirely vibe-coded. The reasons we think this is acceptable are:
- The AI assisted repo at [team-hippodrome/pokestadium](https://github.com/team-hippodrome/pokestadium) serves as a great base line for Stadium 0 as almost all functionality in zero is also in stadium 1
- Stadium 0 is a small game (only 16 mb)
- The md5 hash of the rom serves as a fail-safe

# Pokémon Stadium Zero (JP)

A matching decompilation of the Japanese-only original Pokémon Stadium (ポケモンスタジアム), by **Team Hippodrome**. The project follows pret's layout conventions; pret is not involved.

`make rom` builds the complete 16 MiB ROM byte-for-byte from `src/`. Source files are compiled with IDO through asm-processor (with unmodified `lib/ultralib` C and original SDK assembly wrappers built directly with IDO 5.3); the resident image and all 259 fragments link at their original addresses, and the fragments' original storage is rebuilt.

- **100% of compilable code owners (5,413 of 5,413; 1,270,568 text bytes) are built from C**, including **215** owners from unmodified `lib/ultralib` 2.0I sources.
- Of the **31** handwritten assembly owners ([docs/handwritten-asm.csv](docs/handwritten-asm.csv)), **25** (4,672 bytes) are built from original `lib/ultralib` SDK assembly and **6** remain as extracted assembly (low-level cop0/TLB/cache routines, the fragment jump-stub table, and the handwritten Game Boy emulator CPU interpreter). Across the complete 5,444-owner inventory, **5,438 / 5,444 (99.9%)** are built from C or original SDK source, with **0** ordinary or `libultra` owners remaining in extracted assembly.
- The per-owner ledger is [docs/function-matches.csv](docs/function-matches.csv); current verified counts and code bytes are in [COVERAGE.md](COVERAGE.md).
- Registered source files place recovered `.rodata`, `.data`, and runtime `.bss` at their established addresses. Other data, microcode, and non-code ranges still come from the extracted ROM.
- **Shiftable builds** are supported for modification (`make rom COMPARE=0`; verified with `make shift-test`).

Code matching is complete; semantic annotation, documentation, and investigation of original function boundaries, translation units, and compiler settings remain ongoing.

## Build

Provide your own Japanese ROM as `baseroms/jp/baserom.z64`:

```text
SHA-256 ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b
```

Install Python 3, GNU make, and GNU MIPS binutils, then run:

```sh
make init
make rom
make test
```

`make init` installs pinned Python dependencies and verified official IDO 5.3 and 7.1 binaries into the ignored `tools/ido5.3/` and `tools/ido7.1/`, then extracts local assets and assembly. `make rom` compares by default and produces `build/pokestadium0-jp.z64`. Use `make rom COMPARE=0` for a shiftable ROM build when modifying code or data, and `make shift-test` to verify relocation. See [production build details and constraints](docs/production-build.md) for setup, verification, and development.

`tools/check_functions.py` is a faster per-function check of the C in `src/` against the ROM, without linking.

Do not commit ROMs or extracted retail assets.

## Naming and Contributing

The game's text is Japanese, but annotations use official English names (フーディン → Alakazam, モンスターボール → Poké Ball, だいもんじ → Fire Blast). Look names up in the [Gen 1 Japanese → English glossary](docs/glossary.md).

See [CONTRIBUTING.md](CONTRIBUTING.md) for PR guidelines, the style guide, and clangd editor setup.

## Progress and evidence

- [Coverage](COVERAGE.md): verified owner counts and code bytes built from C and original SDK assembly.
- [Per-owner match ledger](docs/function-matches.csv): status and build source for all 5,444 inventory owners.
- [Handwritten assembly list](docs/handwritten-asm.csv): the 31 handwritten assembly owners (25 original SDK assembly, 6 extracted assembly).
- [Production receipt](docs/production-build-receipt.json): complete-ROM identity for the verified build.
- [Matching history](docs/matching.md): Stadium 1 ports, m2c output, hand-matched C, and the final [original SDK assembly continuations](docs/matching-2026-11-11-sdk-native.md) (`docs/matching-*.md`).
- [Resident and fragment mappings](docs/mappings/README.md): storage and restoration.
- [Executable sections and flow](docs/sections/refined/flow-and-gap-validation.md): conservative code discovery, indirect sites, and unresolved boundaries.
- [Runtime capture watchlist](docs/sections/refined/runtime-watchlist.csv): unresolved-site registers and link-time addresses, not assumed runtime PCs.
- [Pragma scaffold](docs/pragma-bootstrap.md): 5,444-owner inventory and production registry background.
- [Stadium 1/2 library overlap](docs/library-overlap/README.md): scoped exact-byte and address-masked comparisons with pinned donor revisions.

# Contacts
Join the [Team Hippodrome](https://discord.gg/8EvuQxbxu8) discord server.

Part of the [R.A.I.D. (Retro AI Development)](https://discord.gg/eCvnsvrjnY) community.
