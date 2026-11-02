# UI record scans and list setup — 2026-11-02

This batch adds **4 owners / 564 text bytes** built from genuine matching C
beyond PR #32 in fragments 007 and 008.

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_820001B8` | Count marked records and return the first marked record | 160 |
| `func_88102600` | Set up a 16-entry record/list view using mode 1 | 136 |
| `func_88102688` | Set up a 16-entry record/list view using mode 2 | 136 |
| `func_88102710` | Set up a four-entry record/list view using mode 0 | 132 |

The scan reuses the existing `Entry82000058` view and its `0x54`-byte stride.
It starts one past six records and steps backward before each read. Every
nonzero marker contributes to the output count; the returned pointer is the
lowest-index marked record, or NULL if none is marked. A simple fixed-count
loop lets IDO produce the retail unrolled scan.

The setup routines preserve the original 32-bit address parameter and form
typed metadata pointers at `0x2698` and `0x26A8`. They initialize the record
block at `0x458` with stride `0x220`, initialize the pointer table at `0x2658`,
populate it through the existing helper, and configure the view at `0x88` with
its original coordinates and mode. Keeping the address parameter as a word
retains IDO's `0x30`-byte stack frame; changing it to a pointer adds unused
stack space. Pointer conversions at the helper calls are explicit.

No inline assembly, instruction words, code blobs, or comparison exceptions
were introduced. The marker-fill, draw-callback, and selected-row candidates
still differ and remain private; they are excluded from this batch.

Verified totals: **4,467 / 5,444 C owners (82.1%)**, **813,680 text bytes
(62.4%)**, and **977 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,270 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #32](https://github.com/team-hippodrome/pokestadium0/pull/32)
and targets its branch. Private ROMs, extracted assembly/assets, compiler
binaries, and toolchains remain local.
