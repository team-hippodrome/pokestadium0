# Battle-camera data integration — 2026-11-04

This batch builds **13 previously held owners / 12,104 text bytes** from
matching C in the complete ROM, beyond PR #38. These bodies already passed
individual checks; the new verified progress is their integration with placed
read-only data. No new algorithm recovery is claimed.

| Owner | Text bytes |
| --- | ---: |
| `func_8212B270` | 1976 |
| `func_8212BA28` | 1280 |
| `func_8212BFF0` | 468 |
| `func_8212C1C4` | 468 |
| `func_8212C60C` | 220 |
| `func_8212CB58` | 1080 |
| `func_8212D194` | 880 |
| `func_8212D504` | 796 |
| `func_8212EA84` | 580 |
| `func_8212F16C` | 724 |
| `func_8212FC98` | 1364 |
| `func_82130628` | 1256 |
| `func_82130DAC` | 1012 |

The battle_engine_3438B0 group uses the source split and data placement already
verified on the integration line through #34 and in the saved reconciliation
snapshot. Its source on current master was checked against that snapshot's
master basis before reuse. The newer master/SDK configuration and all other
source groups are retained. The inspected open #37 head leaves all 13 owners
held, so this batch does not duplicate its accepted owner work.

A shared header holds declarations, and the later functions starting at
`0x82130628` have a separate source unit. This fixed-layout split preserves the
independent literal/jump-table pools; it is not a claim about original
translation-unit boundaries. The first unit's read-only section is placed at
`0x82196410` with size `0x138`; the later unit's section starts at `0x8219655C`.
The production builder checks section placement and allows only zero alignment
trimming. Constants and jump tables are emitted by the C compiler. No extracted
retail data or assembly is added to source.

The owner ledger retains existing match origins and assigns each owner to the
unit that builds it. All 13 now build from C in the full-ROM receipt. The
other functions moved into the later unit retain their owner identities.
No inline assembly, instruction words, code blobs, or comparison exceptions
are introduced.

Verified totals: **4,678 / 5,444 C owners (85.9%)**, **842,840 C text bytes
(64.7%)**, and **766 remaining assembly owners**. Held matching C falls from
**47 to 34 owners**. Full source matching remains incomplete.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,504 functions in 412 files**, with zero failures.
The function total is unchanged because held C was already checked; the new
source unit increases the file total. All **65 tests pass**. The ledger,
coverage, and production receipt were refreshed from this passing build.

Depends on [PR #38](https://github.com/team-hippodrome/pokestadium0/pull/38)
and targets its branch. Private ROMs, extracted assembly/assets, compiler
binaries, and toolchains remain local. No PR is merged by this run.
