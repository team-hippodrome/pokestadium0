# Menu cursor input — 2026-11-02

This batch adds **1 owner / 220 text bytes** built from genuine matching C
beyond PR #27: `func_8002DC04` in `src/2E480.c`.

The routine returns zero for an empty menu without polling input. Otherwise,
it reads the repeated D-pad value through the existing zero-argument input
API, uses the low 16 bits, and wraps down/up movement at the item-count bounds.
It calls the existing one-argument sound API only when the cursor changes,
then returns the input value. A one-item menu therefore leaves the cursor in
place and does not play the navigation sound.

Initialize the result to zero before the empty-menu check. This expresses the
early return and reproduces IDO's retail register allocation and spill slots.
The previous candidates passed a cursor value to the input routine and extra
arguments to the sound routine; this implementation uses their actual typed
interfaces. It retains the existing partial menu layout.

No inline assembly, instruction words, code blobs, or comparison exceptions
were introduced. Disabled-row navigation, cursor repair, grid/scroll cursor,
and related candidates still differ and remain private; they are excluded
from this batch and its coverage.

Verified totals: **4,445 / 5,444 C owners (81.6%)**, **811,644 text bytes
(62.3%)**, and **999 remaining assembly owners**. Full source matching remains
incomplete. No recorded matching C is held for data placement.

Validation: `make rom` with comparison enabled passes all **260 linked images**
and the complete **16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,248 functions in 426 files**, with zero failures.
All **65 tests pass**. The ledger, coverage, and production receipt describe
this passing build.

Depends on the verified source from [PR #27](https://github.com/team-hippodrome/pokestadium0/pull/27),
now merged into `codex/stadium-zero-20261101-sdk-optimized`. This batch targets
that branch; its tree equals the verified #27 tree. `master` still contains
the earlier source through #18.
Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local.
