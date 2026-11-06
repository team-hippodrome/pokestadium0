# Paired laboratory menu input handlers — 2026-11-05

This batch replaces **two assembly owners / 264 text bytes** with genuine C:
`func_890013F8` in `lab_pc_list_1CEA00.c` and `func_89004FE4` in
`lab_pc_list_1D7B40.c`, each 132 bytes.

Both handlers take a menu pointer and flags. Bit `0x200` selects between two
existing navigation helpers. When navigation returns zero, they read the
controller action: cancel calls the existing feedback helper with ID 3 and
returns -1; confirm returns 1; otherwise they return zero. The recovered C
passes the menu pointer to the navigation helpers, whose implementations read
it from `$a0`. The old draft had omitted this argument. A result initialized
to zero before the mode branch preserves the retail spill and return flow.

This PR depends on #46 and targets its branch. Both owners remain assembly in
open PR #37, inspected at `1743216d241303b4e7147c6dbc84e8d93c432541`.
Existing C implementations remain unchanged. No compiler override, source
registry or data placement change, inline assembly, raw instruction words,
code blobs, or comparison exception is added.

Verified totals: **4,724 / 5,444 C owners (86.8%)**, **869,768 C text bytes
(66.7%)**, **720 assembly owners remaining**, and **zero recorded held C**.
Full source matching remains incomplete; hourly matching continues.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,514 functions in 430 files**, with zero failures; all
**65 tests pass**. The ledger, generated coverage, and production receipt
are refreshed from the passing full-ROM build. No C owner regresses to assembly.

Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local. No PR is merged by this run.
