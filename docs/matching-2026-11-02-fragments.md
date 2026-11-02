# Remaining held fragment data — 2026-11-02

This batch adds **3 owners / 1,428 text bytes** built from C beyond PR #19:

| Owner | Compiled C name | Text bytes |
| --- | --- | ---: |
| `func_811177E8` | `func_811177E8` | 788 |
| `func_88400A1C` | `Trade_DrawSaveSeqMessageBackdrop` | 124 |
| `func_8A201394` | `func_8A201394` | 516 |

Verified coverage is **4,415 / 5,444 owners (81.1%)**, covering
**807,236 text bytes (61.9%)**. **1,029 assembly owners remain.** No recorded
matching C is now held behind `NON_MATCHING` for data placement.

The GB Tower initializer and trade-menu backdrop now have their local-array
storage placed separately from later functions. The laboratory icon function's
jump table stays with the preceding contiguous literal data. Shared local
headers retain each group's types and declarations; these build splits do not
claim recovered original translation-unit boundaries.

Full image comparison recovered Zero's backdrop gradient colors: RGB
`(0, 0, 50)` and `(0, 0, 200)`, replacing the donor's brown values. Constants and
tables are emitted from C; no extracted instruction words or comparison bypass
are introduced.

Validation: `make rom` with comparison enabled passes all **260 images** and
the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,218 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #19](https://github.com/team-hippodrome/pokestadium0/pull/19).
Private ROMs, extraction, compiler binaries, and toolchains remain local.
Full source matching remains incomplete.
