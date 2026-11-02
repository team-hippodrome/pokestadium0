# Battle roster scans — 2026-11-02

This batch adds **9 owners / 968 text bytes** built from genuine matching C
beyond PR #24. The routines are located in the imported `ekans_game_3.c` source
unit and operate on battle roster records and move availability.

| Owner | Scan | Text bytes |
| --- | --- | ---: |
| `func_82183D50` | Count rows with a nonzero 16-bit value at `0x1C` | 76 |
| `func_82183E24` | Find a nonzero row matching the byte at `0x1B` | 100 |
| `func_82183E88` | Count type IDs 21 or 2 | 124 |
| `func_82183F04` | Count type ID 4 | 104 |
| `func_82183F6C` | Count type ID 1 | 104 |
| `func_8218403C` | Count type IDs 23 or 3 | 124 |
| `func_821840B8` | Count type IDs 5 or 21 | 124 |
| `func_82184134` | Count type ID 23 | 104 |
| `func_821851B4` | Check a move's availability, then use the fallback helper | 108 |

The existing `BattleSlotZ` partial layout is declared before its first use.
The fields at `0x1C`, `0x2C`, and `0x2D` are exposed while preserving its
`0x90`-byte size and existing members. Normal indexed loops let IDO generate
the retail induction variables and pointer increments; applying a byte stride
to a typed pointer would scale it twice. The type counters retain the original
condition order and count each matching row once.

The move helper scans at most four entries, stops at the first zero entry,
and accepts the requested move only when its availability byte is nonzero.
Otherwise it calls `func_82185108` using the verified two-argument signature.
No inline assembly, instruction words, code blobs, or comparison exceptions
were introduced.

Verified totals: **4,438 / 5,444 C owners (81.5%)**, **810,400 text bytes
(62.2%)**, and **1,006 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,241 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on [PR #24](https://github.com/team-hippodrome/pokestadium0/pull/24).
Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local.
