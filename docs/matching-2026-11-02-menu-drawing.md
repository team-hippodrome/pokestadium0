# Menu setup and drawing — 2026-11-02

This batch adds **5 owners / 884 text bytes** built from genuine matching C
beyond PR #26 in `src/2E480.c`.

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_8002D880` | Initialize a vertical menu and select the repeat controller | 88 |
| `func_8002D948` | Draw the inset cursor rectangle for a vertical menu | 112 |
| `func_8002D9B8` | Draw rows from a list of item pointers | 288 |
| `func_8002DAD8` | Draw rows from contiguous items using the stored item size | 300 |
| `func_8002DECC` | Initialize the grid menu, including its column count | 96 |

The existing partial menu declarations move before their first use. They now
expose the controller at `0x18` and repeat mask at `0x1C` without changing the
`0x28`-byte layout. The initializers use the existing controller and input APIs,
clear the per-item flags through their setup helper, and set the vertical D-pad
repeat mask to `0xC00`.

The draw loops preserve the original item-count snapshot, two-byte flag stride,
selected-row flag bits, callback arguments, and row spacing. The pointer-list
variant advances by one pointer; the contiguous variant multiplies the index
by the stored item size. After drawing, they re-read the live item count before
optionally drawing the cursor rectangle. The rectangle's four-byte color is
passed as `Color_RGBA8` by value, preserving the retail unaligned aggregate
loads and stores. Its geometry initializers stay on one source line to retain
IDO's instruction scheduling.

No inline assembly, instruction words, code blobs, or comparison exceptions
were introduced. Navigation and grid-cursor candidates still differ and remain
private; they are excluded from this batch and its coverage.

Verified totals: **4,444 / 5,444 C owners (81.6%)**, **811,424 text bytes
(62.2%)**, and **1,000 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,247 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #26](https://github.com/team-hippodrome/pokestadium0/pull/26).
Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local.
