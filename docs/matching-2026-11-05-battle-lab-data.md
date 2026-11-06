# Battle and laboratory data integration — 2026-11-05

This batch builds **6 previously held owners / 4,264 text bytes** from matching
C in the complete ROM. It resumes verified source/data layouts for three
unchanged groups: battle_engine_3055E0, battle_engine_309ED0, and fragment019's
lab_pc_icons. No new algorithm recovery is claimed.

| Owner | Text bytes |
| --- | ---: |
| `func_821243DC` | 360 |
| `func_82124CD0` | 432 |
| `func_8212A328` | 380 |
| `func_8212A850` | 1216 |
| `func_8212AD10` | 1360 |
| `func_8A201394` | 516 |

The prior continuation through PR #42 was merged externally into master at
`1b44419887d20982250f7803f2b9060fa5dde683`. Its tree exactly equals the
verified #42 tree `f0fa3879d809a58cedafa1c81680d933a480a395`. This PR targets
that master revision and requires no open PR dependency. The inspected #37
head `822a12ad2195465136009951dc52c9d66da081ee` leaves all six owners in asm.

Each affected primary source was byte-compared with the saved reconciliation's
master basis before the verified split/data layouts were reused. Shared
headers and four additional C units separate independent read-only pools.
Source and section registries preserve section bounds and zero-only alignment
trimming. These fixed-layout splits do not establish original translation-unit
boundaries. No extracted retail data or assembly is copied into source.

Two ledger C-name entries are corrected to their existing definitions:
`func_82123D4C` and `func_82124194`. The prior ledger listed semantic aliases
whose imported declarations have different signatures; the actual existing
camera helper definitions already use these address-based names. Their C
names/signatures are retained, and the unrelated imported alias declarations
and global symbol bindings are left alone. The new shared header retains the
correct floating-point argument type of func_8000EEBC. No previously built C
owner reverts to assembly; current master/SDK changes outside these groups are
preserved. The two remaining held groups have newer edits and are excluded
until they can be reconciled separately.

Verified totals: **4,713 / 5,444 C owners (86.6%)**, **867,376 C text bytes
(66.5%)**, and **731 remaining assembly owners**. Recorded held C falls from
**8 to 2 owners**. Full source matching remains incomplete.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,505 functions in 428 files**, with zero failures; all
**65 tests pass**. The direct function total is unchanged because held C was
already checked. The ledger, generated coverage, and receipt were refreshed
from this passing build.

No inline assembly, instruction words, code blobs, or comparison exceptions
are added. Private ROMs, extracted assembly/assets, compiler binaries, and
toolchains remain local. No PR is merged by this run.
