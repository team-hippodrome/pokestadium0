# Pokédex list input — 2026-11-05

This batch replaces **one assembly owner / 152 text bytes** with genuine C:
`func_8A100588` in `fragment018_262620/pokedex_214920.c`.

The handler passes the list at state offset `0x2C` to the existing navigation
helper. When navigation returns zero, it reads the controller's pressed-button
halfword. Bit `0x0001` plays feedback ID 2, resets the grid selection to zero,
and toggles the view-mode word at `0x1B0`. The cancel and confirm bits return
-1 and 1 respectively; otherwise it preserves the navigation result.

A full-word scratch value holds the promoted button bits and then the view
mode during the toggle path. This reproduces the retail register allocation
and stack frame. The existing controller-address declaration is moved before
its first new use; the original helper signatures and surrounding C remain
unchanged.

This PR depends on #48 and targets its branch. The owner remains assembly in
open PR #37, inspected at `1743216d241303b4e7147c6dbc84e8d93c432541`.
No compiler override, source registry or data placement change, inline assembly,
raw instruction words, code blobs, or comparison exception is added.

Verified totals: **4,727 / 5,444 C owners (86.8%)**, **870,196 C text bytes
(66.8%)**, **717 assembly owners remaining**, and **zero recorded held C**.
Full source matching remains incomplete; hourly matching continues.

Validation: `make rom COMPARE=1` passes all **260 linked images** and the full
**16,777,216-byte ROM**, SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`.
Direct checks pass **4,517 functions in 430 files**, with zero failures; all
**65 tests pass**. The ledger, generated coverage, and production receipt
are refreshed from the passing full-ROM build. No C owner regresses to assembly.

Private ROMs, extracted assembly/assets, compiler binaries, and toolchains
remain local. No PR is merged by this run.
