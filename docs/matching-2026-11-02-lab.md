# Laboratory state and index helpers — 2026-11-02

This batch replaces three uncovered assembly owners with genuine matching C:

| Owner | Compiled C name | Text bytes |
| --- | --- | ---: |
| `func_89100380` | `func_89100380` | 36 |
| `func_8910713C` | `Move_NormalizeDisplayIndex` | 52 |
| `func_89107170` | `func_89107170` | 52 |

The initializer uses a partial typed view of five state fields at offsets
`0x9828`, `0x9829`, `0x982C`, `0x9918`, and `0x9B04`. Typed member accesses
reproduce the original large-offset addressing. Its two byte assignments share
a source line so IDO schedules the stores in their original order. The field
names and padding describe the observed layout without claiming a recovered
complete structure.

The two index helpers use nested conditional expressions. Expressing the outer
condition as an early return changes the register allocation; the nested form
reproduces the original control flow and register moves. No inline assembly,
instruction words, or extracted code blobs are used.

Adds **3 owners / 140 text bytes** beyond PR #20, raising verified coverage to
**4,418 / 5,444 owners (81.2%)** and **807,376 text bytes (61.9%)**.
**1,026 assembly owners remain**; full source matching remains incomplete.

Validation: `make rom` with comparison enabled passes all **260 images** and
the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,221 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and build receipt describe this
passing build.

Depends on [PR #20](https://github.com/team-hippodrome/pokestadium0/pull/20).
Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local.
