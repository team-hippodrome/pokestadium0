# Battle model helpers — 2026-11-02

This batch adds **7 owners / 1,120 text bytes** built from genuine matching C
beyond PR #22. All **55 owners** in `battle_engine_helper.c` are now built from C;
the seventh addition is the related height-reset helper in
`battle_engine_move_animation.c`.

| Owner | Compiled C name | Text bytes |
| --- | --- | ---: |
| `func_82107B88` | `BattleAnim_GetSpeciesBaseScale` | 60 |
| `func_82107BC4` | `func_82107BC4` | 48 |
| `func_82107BFC` | `func_82107BFC` | 136 |
| `func_82107EC8` | `func_82107EC8` | 80 |
| `func_82108090` | `BattleScene_InitializeParticipantSecondaryModels` | 320 |
| `func_82108A94` | `Battle_ReturnToIdleAnimIfFinished` | 376 |
| `func_82106144` | `func_82106144` | 100 |

The model-size and height tables use four-float rows. Correct typed indexing
avoids scaling their byte offsets twice. An integer factor of `2` reproduces the
retail floating-point multiply; `2.0f` makes IDO replace it with an addition.
The vector helper retains the one-based species row index and the original X
scale used for its Z result.

The secondary-model routines follow the corresponding
[Stadium 1 helper source](https://github.com/team-hippodrome/pokestadium/blob/master/src/fragments/battle_engine/battle_engine_helper.c)
(read as blob `1772a516d8a28e2019cb898d152f6c331f6a58f8`), adapted for Zero's
three afterimages, effect slots, alternate sleep species, and Ditto animation
range. The state pointer's declaration and initialization preserve its lifetime
across calls. Local declaration order preserves the secondary initializer's
stack layout. Existing source units, image placement, and compiler settings
remain in use; no instruction words, inline assembly, or comparison bypasses
were added.

Verified totals: **4,425 / 5,444 C owners (81.3%)**, **808,496 text bytes
(62.0%)**, and **1,019 remaining assembly owners**. Full source matching is
incomplete; no recorded matching C remains held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,228 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #22](https://github.com/team-hippodrome/pokestadium0/pull/22).
Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local.
