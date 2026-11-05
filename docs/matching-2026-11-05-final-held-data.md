# Final recorded held-C data integration — 2026-11-05

This batch builds the last **2 recorded held owners / 912 text bytes** from
matching C in the full ROM, beyond PR #43. It completes the recorded held-C
integration work, not full source matching. **729 assembly owners remain.**

| Owner | Behavior | Text bytes |
| --- | --- | ---: |
| `func_811177E8` | Existing GB-audio sample renderer | 788 |
| `func_88400A1C` | Existing save-sequence message backdrop drawing | 124 |

Both source groups had newer matching work after the saved verified data
layouts. Reusing the old whole files would have lost six C conversions. This
batch instead transplants the current bodies of func_81112650, func_81112E00,
func_81113E84, func_81113EF4, func_884022AC, and func_884025E4 into the verified
split layout. A body comparison confirms all six are verbatim identical to
#43. Their current byte-sized flag bitfields and helper declarations are
retained. The shared func_884022AC prototype now agrees with its void definition.
No previously built C owner reverts to assembly.

Shared headers and two additional C units separate the independent data pools.
The GB-audio tail's data starts at `0x811526A4` with size `0xC`; the trade
backdrop unit's data starts at `0x88402F8C` with size `0x8`, and the later trade
unit's data starts at `0x88402FB4` with size `0xC`. The registries retain the
existing first GB unit's read-only/writable placement and enforce section bounds
and zero-only alignment trimming. These fixed-layout splits do not establish
original translation-unit boundaries. No extracted retail data or assembly is
copied into source; no new algorithm recovery is claimed.

The inspected #37 head `1743216d241303b4e7147c6dbc84e8d93c432541` leaves both
owners held. This PR depends on #43 and preserves its current master/SDK and
source/data changes. Existing owner names and match origins are retained.

Verified totals: **4,715 / 5,444 C owners (86.6%)**, **868,288 C text bytes
(66.6%)**, **729 assembly owners remaining**, and **zero recorded held C**.
Full source matching remains incomplete, so hourly matching continues.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,505 functions in 430 files**, with zero failures; all
**65 tests pass**. The direct function total is unchanged because held C was
already checked. The ledger, generated coverage, and production receipt were
refreshed from this passing build.

No inline assembly, instruction words, code blobs, or comparison exceptions
are added. Private ROMs, extracted assembly/assets, compiler binaries, and
toolchains remain local. No PR is merged by this run.
