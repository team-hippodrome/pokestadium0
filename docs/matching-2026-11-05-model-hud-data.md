# Battle-model and HUD data integration — 2026-11-05

This batch builds **17 additional owners / 6,856 text bytes** from matching C
in the complete ROM, beyond PR #40. It resumes the previously verified source
and data layouts for model transforms, battle HUD drawing, participant effects,
and a battle-scene helper. No new algorithm recovery is claimed.

| Owner | Text bytes | Previous state |
| --- | ---: | --- |
| `func_82117610` | 380 | Held C |
| `func_8211778C` | 380 | Held C |
| `func_82117908` | 1224 | Held C |
| `func_821199E4` | 356 | Held C |
| `func_82119B48` | 356 | Held C |
| `func_82154050` | 464 | Held C |
| `func_82154310` | 372 | Held C |
| `func_821094C0` | 244 | Unrecorded held C |
| `func_821095B4` | 432 | Held C |
| `func_82109824` | 424 | Held C |
| `func_82109AF4` | 404 | Held C |
| `func_8210B5C8` | 456 | Held C |
| `func_8210B7E4` | 64 | Unrecorded held C |
| `func_8210B824` | 468 | Held C |
| `func_8210BA64` | 196 | Restored verified C |
| `func_8210BB88` | 360 | Held C |
| `func_821328DC` | 276 | Held C |

Fourteen owners were recorded held matches. Two more, `func_821094C0` and
`func_8210B7E4`, already had matching C under NON_MATCHING but were still marked
asm in the ledger; their metadata and production selection are now corrected.
`func_8210BA64` is restored from the previously verified continuation. All
seventeen remain assembly in the inspected open #37 head
`822a12ad2195465136009951dc52c9d66da081ee`.

The four source groups are battle_engine_31D9F0, battle_engine_32B680_3,
battle_engine_move_model_transforms, and fragment1_89010. Their current primary
sources were byte-compared with the saved reconciliation's master basis before
reusing the verified layouts. Shared declaration headers and six additional C
units separate independent read-only pools and existing C-defined writable
tables. Source/section registries retain section bounds and zero-only alignment
trimming. These fixed-layout splits do not establish original translation-unit
boundaries. No extracted retail data or assembly is copied into source.

The ledger keeps existing C names and origins, restores the three missing C
entries, and assigns owners to the units that build them. No previously built
C owner reverts to assembly. Current master/SDK and prior #38/#39/#40 changes
are retained. No inline assembly, instruction words, code blobs, or comparison
exceptions are added.

Verified totals: **4,707 / 5,444 C owners (86.5%)**, **863,112 C text bytes
(66.2%)**, and **737 remaining assembly owners**. Recorded held matching C
falls **22 to 8 owners**. Full source matching remains incomplete.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,505 functions in 424 files**, with zero failures; all
**65 tests pass**. The direct total rises by one because the held C, including
the two unrecorded entries, was already checked. A comparison of definitions
in the affected units confirms that no checked function was removed and only
func_8210BA64 was added to the individual checks. The ledger, generated
coverage, and receipt were refreshed from this passing build.

Depends on [PR #40](https://github.com/team-hippodrome/pokestadium0/pull/40)
and targets its branch. Private ROMs, extracted assembly/assets, compiler
binaries, and toolchains remain local. No PR is merged by this run.
