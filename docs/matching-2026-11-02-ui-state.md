# UI rendering and screen initialization — 2026-11-02

This batch adds **5 owners / 884 text bytes** built from genuine matching C
beyond PR #33 in fragments 007 and 008.

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_82001D64` | Draw a preset panel and its title with the original font settings | 188 |
| `func_8810105C` | Draw the two panels with a caller-supplied height | 208 |
| `func_8810137C` | Draw the icon panel and restore its display-list setup | 252 |
| `func_88102794` | Capture the active port, build its summary, and initialize screen state | 160 |
| `func_881029E0` | Allocate and initialize the screen, then retain the icon setup call | 76 |

The drawing routines use existing display-list macros, texture drawing, and
font interfaces. They pass color structs by value and preserve palette order,
panel dimensions, icon coordinates, and display-list restoration. The titled
panel uses its fixed preset color; the incoming third callback parameter is
retained in the signature. The title is referenced as an external string,
without publishing extracted text.

The initializer uses the existing active-port and summary helpers. It saves
the port globally, skips summary setup for port -1, initializes the screen's
child at byte offset four, and clears the state word. The two three-color
palettes and opaque buffers have explicit external declarations. Correcting
`arg0 + 4` on a word pointer to `arg0 + 1` removes the initial candidate's extra
pointer scaling.

The allocator requests `0x26B4` bytes through the existing one-argument API,
stores the result in the existing global handle, and passes that stored handle
to initialization. Using the saved globals at these call sites preserves the
retail addressing and helper order. No new palette, texture, or text data is
defined.

No inline assembly, instruction words, code blobs, or comparison exceptions
were introduced. Other state, callback, and drawing candidates still differ
and remain private; they are excluded from this batch.

Verified totals: **4,472 / 5,444 C owners (82.1%)**, **814,564 text bytes
(62.5%)**, and **972 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,275 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #33](https://github.com/team-hippodrome/pokestadium0/pull/33)
and targets its branch. Private ROMs, extracted assembly/assets, compiler
binaries, and toolchains remain local.
