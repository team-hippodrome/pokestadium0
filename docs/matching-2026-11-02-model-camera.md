# Model and camera interpolation — 2026-11-02

This batch replaces **4 uncovered assembly owners / 936 text bytes** with
matching C beyond PR #23:

| Owner | Source group | Text bytes |
| --- | --- | ---: |
| `func_8212239C` | Camera anchor setup | 188 |
| `func_82135458` | Conditional camera target interpolation | 308 |
| `func_82135BE4` | Camera target approach | 244 |
| `func_8210BA64` | Surf model update | 196 |

The camera routines use a partial typed view of the model's angle and distance
fields at offsets `0x30`, `0x32`, and `0x38`. Keeping their pointer lifetimes and
local declaration order intact reproduces the original addressing, spills, and
stack layout. Unused local storage retains the observed frame layout. Species
model data is indexed as four-float rows, avoiding double scaling of byte offsets.
The anchor setup retains the retail floating-point operand order.

The Surf update samples the terrain before looking up the model's resting height.
Its rotation conversion uses a signed 16-bit angle before multiplication by 182;
the final halfword store lets IDO remove the redundant extension instructions.
The completion path restores height before clearing rotation. Zero uses a
200-frame limit and adds five units to the water height while the animation runs.

The corresponding public Stadium 1 sources helped recover the control flow:
[battle camera](https://github.com/team-hippodrome/pokestadium/blob/master/src/fragments/battle_engine/battle_engine_camera.c)
(blob `7a76272588e15b04ebd5a6e0398ffd9339f06ff2`) and
[model transforms](https://github.com/team-hippodrome/pokestadium/blob/master/src/fragments/battle_engine/battle_engine_move_model_transforms.c)
(blob `108aa146b2d92ce04733689b88848585e802ef4e`). The implementations retain
Zero's verified behavior and layout. No instruction words, inline assembly,
retail code blobs, or comparison exceptions were introduced.

Verified totals: **4,429 / 5,444 C owners (81.4%)**, **809,432 text bytes
(62.1%)**, and **1,015 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,232 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #23](https://github.com/team-hippodrome/pokestadium0/pull/23).
Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local.
