# Camera-relative point helper — 2026-11-05

This batch replaces **one assembly owner / 172 text bytes** with genuine C:
`func_8213831C` in `particle_math_261F90.c`. It obtains the scene camera,
normalizes the direction from its eye to its target, and writes a point at
the caller's requested distance along that direction. It reuses the existing
`CameraNode` layout and vector helpers, including the by-value vector ABI.
The existing camera getter returns a 32-bit address, cast to `CameraNode*`.

This PR depends on #45 and targets its branch. The owner remains assembly in
open PR #37, inspected at `1743216d241303b4e7147c6dbc84e8d93c432541`.
The adjacent orientation helper `func_82138244` is already covered by #37 and
is excluded from this batch. Existing C implementations remain unchanged.
No compiler override, data placement, inline assembly, raw instruction words,
code blobs, or comparison exception is added.

Verified totals: **4,722 / 5,444 C owners (86.7%)**, **869,504 C text bytes
(66.7%)**, **722 assembly owners remaining**, and **zero recorded held C**.
Full source matching remains incomplete; hourly matching continues.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,512 functions in 430 files**, with zero failures; all
**65 tests pass**. The ledger, generated coverage, and production receipt
are refreshed from the passing full-ROM build. No C owner regresses to assembly.

Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local. No PR is merged by this run.
