# Four-byte record copy — 2026-11-02

This batch adds **1 owner / 140 text bytes** built from genuine matching C
beyond PR #25: `func_821867A8` in `ekans_game_3.c`.

The helper writes exactly four bytes. It copies each nonzero source byte and
advances the source pointer; once it reaches a zero byte, it leaves that
pointer in place and pads the rest of the destination with zeroes. Both
record-conversion callers ignore its return, and their declarations now use
its recovered `void` signature. An integer temporary preserves the byte
promotion and IDO register allocation seen in the retail function.

No inline assembly, instruction words, code blobs, or comparison exceptions
were introduced. Nearby move-check candidates still differ and remain private;
they are excluded from this batch and its coverage.

Verified totals: **4,439 / 5,444 C owners (81.5%)**, **810,540 text bytes
(62.2%)**, and **1,005 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,242 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #25](https://github.com/team-hippodrome/pokestadium0/pull/25).
Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local.
