# Fragment000 resource lists and shutdown — 2026-11-02

This batch adds **3 owners / 220 text bytes** built from genuine matching C
beyond PR #29 in the imported `battle_engine_309ED0.c` and
`battle_engine_2FA4D0.c` units.

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_8110F4D0` | Append a resource pointer only when no existing key matches | 72 |
| `func_8110F64C` | Collect a reference when its packed address and flags qualify | 88 |
| `func_81110060` | Set the busy flag, call the shutdown helper, and clear the active byte | 60 |

The list helper uses a partial two-word record view and a normal indexed loop.
It preserves the original count on a duplicate and advances the count only
when appending. Correct pointer indexing removes the extra scaling in the
initial candidate and lets IDO hoist the key load out of the loop.

The collector exposes the packed word with unsigned bitfields: a low 24-bit
address, an enable flag at bit 25, and a two-bit kind at bits 27:26. It appends
the original pointer only when all three tests pass, preserving the other
bits and the existing global count update. These partial views do not claim
the full original record layouts.

The shutdown wrapper declares the existing shared busy word `volatile`,
consistent with the other translation unit that accesses it. This reproduces
the retail addressing and store order. It calls `func_8110FFC8(0)` before
clearing the already-volatile active byte.

No inline assembly, instruction words, code blobs, or comparison exceptions
were introduced. Allocator, load-status, queue-drain, and byte-decoder probes
still differ and remain private. The temporary allocator-field declaration
used by a probe was restored before validation and is excluded from this batch.

Verified totals: **4,456 / 5,444 C owners (81.9%)**, **812,468 text bytes
(62.3%)**, and **988 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,259 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #29](https://github.com/team-hippodrome/pokestadium0/pull/29)
and targets its branch. Private ROMs, extracted assembly/assets, compiler
binaries, and toolchains remain local.
