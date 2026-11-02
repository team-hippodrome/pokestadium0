# UI panels and ranges — 2026-11-02

This batch adds **7 owners / 648 text bytes** built from genuine matching C
beyond PR #30 in fragments 007 and 008.

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_82000020` | Fill an indexed range with -1 | 56 |
| `func_82001C00` | Draw the left 136-by-100 panel | 96 |
| `func_82001C60` | Draw the right 396-by-100 panel | 108 |
| `func_88100BA4` | Initialize a window, its colors, state words, and caller value | 128 |
| `func_88100CD0` | Draw the left 136-by-100 panel in fragment 008 | 96 |
| `func_88100D30` | Draw the right 396-by-100 panel in fragment 008 | 108 |
| `func_88101D7C` | Fill an indexed range with -1 in fragment 008 | 56 |

The drawing wrappers use the existing display-list macro and pass their
four-byte color structs by value. The existing color declarations move before
their first use without changing their representation. Each wrapper retains
the original setup display list, dimensions, and right-panel x offset.

The two range helpers use a normal indexed loop from `first` to
`first + count`. This retains the original empty-range behavior and lets IDO
reproduce the retail pointer induction and branch delay slot.

The window initializer forwards x/y to the existing five-argument constructor,
using width `0x170` and height `0x68`. A partial window view exposes the fields
at `0x14` through `0x2C`; it preserves the three zero stores, flags `0x1006`,
and final caller-value store. The adjacent color presets are referenced as a
two-element external array, preserving the original unaligned aggregate loads
and stores. No new color values or extracted data are defined.

No inline assembly, instruction words, code blobs, or comparison exceptions
were introduced. Nearby callback and selected-row candidates still differ;
they remain private and are not counted as matches.

Verified totals: **4,463 / 5,444 C owners (82.0%)**, **813,116 text bytes
(62.4%)**, and **981 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,266 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #30](https://github.com/team-hippodrome/pokestadium0/pull/30)
and targets its branch. Private ROMs, extracted assembly/assets, compiler
binaries, and toolchains remain local.
