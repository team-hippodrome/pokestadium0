# Laboratory list entry flags — 2026-11-05

This batch replaces **two assembly owners / 276 text bytes** with genuine C in
`fragment016_252E10/lab_pc_list_1D7B40.c`:

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_8910548C` | Set or clear bit 3 across the list's entry flags | 120 |
| `func_891059FC` | Rebuild entry flags from the current records | 156 |

The bit updater captures the initial list metadata, selects 8 or zero from the
requested mode, and checks that the list is nonempty before initializing the
byte offset. It clears bit 3 and reloads the flag pointer before applying the
selected value. The rebuild routine clears each flag halfword, calls the
existing record flag helper, reloads the flag pointer, and combines the result.
It advances records by `0x24` and flag offsets by two bytes. Both loops reread
the list count for their continuation checks. Initializing the record address
in its declaration preserves the retail saved-register allocation.

This PR depends on #47 and targets its branch. Both owners remain assembly in
open PR #37, inspected at `1743216d241303b4e7147c6dbc84e8d93c432541`.
Existing C implementations remain unchanged. No compiler override, source
registry or data placement change, inline assembly, raw instruction words,
code blobs, or comparison exception is added.

Verified totals: **4,726 / 5,444 C owners (86.8%)**, **870,044 C text bytes
(66.7%)**, **718 assembly owners remaining**, and **zero recorded held C**.
Full source matching remains incomplete; hourly matching continues.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,516 functions in 430 files**, with zero failures; all
**65 tests pass**. The ledger, generated coverage, and production receipt
are refreshed from the passing full-ROM build. No C owner regresses to assembly.

Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local. No PR is merged by this run.
