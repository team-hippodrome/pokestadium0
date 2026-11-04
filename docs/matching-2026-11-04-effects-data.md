# Battle-effect and terrain data integration — 2026-11-04

This batch builds **12 previously held owners / 13,416 text bytes** from
matching C in the complete ROM, beyond PR #39. The bodies already passed
individual checks; the new progress is verified full-ROM integration of their
read-only and writable data. No new algorithm recovery is claimed.

| Owner | Text bytes |
| --- | ---: |
| `func_821640A0` | 248 |
| `func_82164198` | 2360 |
| `func_82164B9C` | 264 |
| `func_821659FC` | 460 |
| `func_82165E30` | 232 |
| `func_82170D28` | 476 |
| `func_82171088` | 1792 |
| `func_821720B4` | 956 |
| `func_82172470` | 648 |
| `func_821726F8` | 984 |
| `func_82172AD0` | 1644 |
| `func_82173418` | 3352 |

The functions cover effect callbacks, ribbon-mesh spawning/drawing, terrain
bounds and height/slope sampling, wave updates, and terrain rendering. Their
three source groups are battle_engine_339CA0, battle_engine_343BA0_8, and
battle_engine_347330. Each current primary source was byte-compared against
the saved reconciliation's master basis before the previously verified split
and data placement were reused. These groups are unchanged by newer master
and open #37; all twelve owners remain held in the inspected #37 head
`eb43f4a1d5a5d2418b40fd4f4ea8113840fb4f37`.

Shared headers retain declarations while six additional C units separate
independent literal/jump-table pools and existing C-defined writable tables.
Source/section registries place each unit's data, including bounded sections
where only zero alignment trimming is permitted. The full-ROM comparison
checks the resulting data and code at their established addresses. These are
fixed-layout splits, not claims about original translation-unit boundaries.
No extracted retail data or assembly is copied into source.

The ledger retains existing C names and match origins while assigning owners
to their actual source units. Current master/SDK changes, #38's texture helpers,
and #39's camera data placement are preserved. No inline assembly, instruction
words, code blobs, or comparison exceptions are added.

Verified totals: **4,690 / 5,444 C owners (86.1%)**, **856,256 C text bytes
(65.7%)**, and **754 remaining assembly owners**. Held matching C falls from
**34 to 22 owners**. Full source matching remains incomplete.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,504 functions in 418 files**, with zero failures.
The function total is unchanged because held C was already checked; the six
new units increase the file total. All **65 tests pass**. The ledger, generated
coverage, and production receipt were refreshed from this passing build.

Depends on [PR #39](https://github.com/team-hippodrome/pokestadium0/pull/39)
and targets its branch. Private ROMs, extracted assembly/assets, compiler
binaries, and toolchains remain local. No PR is merged by this run.
