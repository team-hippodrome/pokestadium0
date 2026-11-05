# Particle texture helpers — 2026-11-04

This batch adds **7 owners / 1,532 text bytes** built from genuine matching C
on master `26913080f6fcde0587a6022e9dd60eafe4241a92`, after merged PR #36.
The seven owners remain assembly in that revision and in the inspected head of
open PR #37 (`eb43f4a1d5a5d2418b40fd4f4ea8113840fb4f37`). No open PR
dependency is required.

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_82168FAC` | Load a 256-entry texture lookup table | 172 |
| `func_82169B14` | Configure clamped 16-bit load/render tiles for block loading | 220 |
| `func_82169BF0` | Configure clamped 16-bit tiles for tile loading | 220 |
| `func_82169CCC` | Configure clamped 32-bit load/render tiles for block loading | 220 |
| `func_82169DA8` | Configure clamped 32-bit tiles for tile loading | 220 |
| `func_82169E84` | Transfer a 16-bit texture block with the SDK DXT calculation | 240 |
| `func_82169FF8` | Transfer a 32-bit texture block with the SDK DXT calculation | 240 |

These functions use SDK display-list macros. They preserve synchronization
order, load/render tile selection, clamp modes, dimensions, palette loading,
and the 32-bit tile's banked row stride. Block transfers retain the SDK's
load-size clamp and DXT calculation. The original drafts incorrectly advanced
a `Gfx*` by eight elements; the SDK macros advance by one eight-byte command
and reproduce the original instruction scheduling.

The render-state and rectangular tile-transfer helpers are already covered by
#36, so their implementations are preserved. No duplicate match is counted.
No raw instruction words, inline assembly, code blobs, or comparison exceptions
are added. Private ROMs, extracted assembly/assets, compiler binaries, and
toolchains remain local.

Verified totals: **4,665 / 5,444 C owners (85.7%)**, **830,736 C text bytes
(63.7%)**, and **779 assembly owners remaining**. Of the remaining owners,
**47 have matching C held behind NON_MATCHING** for data placement on this
branch. Full source matching remains incomplete.

Validation: comparison-enabled `make rom COMPARE=1` passes all **260 linked
images** and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,504 functions in 411 files**, with zero failures.
All **65 tests pass**. The ledger, generated coverage, and committed receipt
were refreshed from this passing build.

The older integration branch through #34 contains previously verified source
splits and data placement. Its separate reconciliation snapshot remains local
for later integration with newer master work; it is not included or counted
as new progress in this batch. No PR is merged by this run.
