# Function naming pass (per-fragment player agents)

Hub branch: `claude/project-thread-ttcreu`, stacked on #78. Each agent works on one
fragment (or the resident code outside fragments) and opens its PR into the hub branch.
The hub merges them one at a time and keeps `make rom` byte-identical on every merge.

## Rules
- Official English names; JP→EN lookups in `docs/glossary.md`.
- Stadium 1 is a reference only. Verify every name against Zero's code or play.
- Zero has only 40 battle species (`docs/stadium-zero-battle-roster.md`). No minigames.
- The audio driver is Nintendo's N64 sound driver; use the OoT names from #78.
- Mark fakes `// FAKE`. Never loosen a match checker. No per-function compiler flags.
- Never commit a ROM or anything derived from one.
- A name not seen in play keeps `@unverified`. Remove the tag only when the game showed it,
  and say how in the PR (breakpoint hit, stub test, RAM poke).
- Replace stale "not reached in play" notes when a function is reached.
- Commit `docs/` with every rename (`tools/rename_symbol.py` edits `docs/function-matches.csv`
  and `linker_scripts/jp/symbol_addrs.txt`).
- Before the PR: `make rom` (sha256 `ed9f7cd7…`) and `make test` pass.

## Known gaps from the 2026-11-13 blind test
- The VS scene's reveal helpers (trainer-card rotation etc.) are unnamed.
- Some "not reached" notes are stale.
- Dead Stadium 1 names remain in `battle_prep.h`.

## Emulator use
Run one emulator per agent at a time, and stagger play checks: build first, then play.
If savestate loads time out or frames stall, stop and report it to the hub instead of
retrying; the hub will ask other agents to idle.
