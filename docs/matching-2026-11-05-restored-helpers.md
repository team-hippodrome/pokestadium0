# Restored verified C helpers — 2026-11-05

This batch restores **6 verified C owners / 1,044 text bytes** that remained
assembly on the current continuation and in open PR #37. It resumes bodies
from the previously verified reconciliation snapshot, with fresh verification
in the current source units. No new algorithm recovery is claimed.

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_8810105C` | Draw the paired panels at a caller-supplied height | 208 |
| `func_82108090` | Initialize three participant secondary models | 320 |
| `func_82108A94` | Select the idle animation when the active animation finishes | 376 |
| `func_89100380` | Initialize the known laboratory state fields | 36 |
| `func_8910713C` | Translate display-index ranges using the original thresholds | 52 |
| `func_89107170` | Translate the corresponding index ranges | 52 |

Only the six function bodies and required supporting declarations are inserted.
The panel helper references an external two-color palette and passes the
existing color struct by value; no palette data is added. The state initializer
uses a partial field layout with the established byte offsets, keeping the
paired byte stores on one source line for IDO scheduling. The battle helpers
reuse existing model/cue types and preserve the three-model loop, side marker,
model-facing values, cue lookup order, and idle/flying/sleep selection.

The two integer translations retain their exact signed comparisons and
arithmetic. The source units' existing C implementations and surrounding work
are preserved. No source-group overwrite, registry change, inline assembly,
instruction words, code blobs, or comparison exceptions are introduced.

All six are assembly in the inspected #37 head
`1743216d241303b4e7147c6dbc84e8d93c432541`. Other saved matches already covered
by #37 are excluded. This PR depends on #44 and targets its branch.

Verified totals: **4,721 / 5,444 C owners (86.7%)**, **869,332 C text bytes
(66.7%)**, **723 assembly owners remaining**, and **zero recorded held C**.
Full source matching remains incomplete; hourly matching continues.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,511 functions in 430 files**, with zero failures; all
**65 tests pass**. The ledger, generated coverage, and production receipt were
refreshed from this passing build. No previously built C owner reverts to asm.

Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local. No PR is merged by this run.
