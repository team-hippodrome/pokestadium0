# Style-guide pass (per-chunk style agents)

Hub branch: `claude/project-thread-obmv3z`, stacked on the naming hub (#85). Each agent
owns one chunk of files (table below), works on its own branch made from the hub, and opens
one PR into the hub branch. The hub merges them one at a time and keeps the ROM
byte-identical on every merge.

The rules are `CONTRIBUTING.md`. This page only says how to apply them here.

## Setup
- ROM: copy the project upload `0d8923aa-…` to `baseroms/jp/baserom.z64` (gitignored),
  `apt-get install binutils-mips-linux-gnu`, then `make init`.
- `.venv/bin/pip install libclang==18.1.1` for `tools/style_check.py` and `tools/snake_locals.py`.
- Gate before every push: `make rom` gives sha1 `8bc8d2ff…` (sha256 `ed9f7cd7…`), and `make test` passes.

## What to fix
Start from `.venv/bin/python tools/style_check.py -v <your paths>`. It finds the shapes a
regex or libclang can see. Then read every function in the chunk, because most of the work
is not machine-findable:

1. **Docs.** Every function has a `/** */` comment that says what it does, written from the
   code. Keep every `@unverified` tag, every "Seen in play" note and every play note. Fix a
   comment that the code contradicts, and say so in the PR.
2. **Numbers.** Hex for addresses, offsets, masks, flags, packed colors and binary angles.
   Decimal for counts, loop bounds, lengths, timers, frame counts, HP/damage/coordinates and
   indices. Do not flip a literal that is acceptable either way (powers of two and one less).
   A literal's base never changes codegen; `make rom` still decides.
3. **Colors.** A `// #RRGGBB` comment next to every literal color.
4. **Japanese text.** An English translation comment on or above every Japanese string.
   Official names from `docs/glossary.md`.
5. **Fakes.** `tools/fake_audit.py --unmarked` and reading. Mark decomp slop `// FAKE`;
   karodo may keep `// karodo`. Never relabel slop as karodo. Do not rewrite code to remove a
   fake in this pass; that is separate work.
6. **Names.** Functions `Domain_Purpose`, at most 50 characters; shorten longer ones with
   `tools/rename_symbol.py` (keep the meaning, keep the tag). Locals and arguments
   snake_case (`tools/snake_locals.py` already ran; finish the rest by hand). Globals
   `gName` (resident) / `sName` (fragment-local) or `D_XXXXXXXX`. Structs TitleCase.
   Otherwise do not rename for taste: the naming hub owns names.
7. **Terminology.** "GB Player", never "GB Tower" (except Stadium 1 paths). "Nintendo Cup",
   never "Poke Cup". "Poké Ball" is two words (`PokeBall`, `POKE_BALL`). "COM" for computer
   trainers. `rotationX/Y/Z` instead of yaw/pitch/roll for rotations (B-roll, dice rolls and
   audio pitch are fine). "boom" for Explosion + Self-Destruct as a group. "brought" vs
   "picked" Pokémon. Valid / legal / eligible as defined in the guide. American spelling.
   Zero has 40 battle species and no minigames.
8. **Bugs and cross references.** `//!bug` on original-game bugs the code makes evident;
   `//@path` when a comment points at another file.

## Do not
- Reformat or re-indent code: IDO is whitespace-sensitive. No clang-format.
- Change what any code does, loosen a match checker, add per-function compiler flags, or touch
  `tools/cflags_overrides.json`.
- Drop `@unverified`. Delete `oldnotes`. Add long `.md` files.
- Commit a ROM or anything built from one.

## Shared headers and conflicts
Edit a shared header's comments and fields only in the chunk that owns it (table). Renames
that reach other chunks go through `tools/rename_symbol.py` / `tools/rename_field.py` and
must be listed in the PR body as `OLD -> NEW` so the hub can replay them. Commit `docs/` with
every rename. Rebase on the hub when it moves; no merge commits.

## PR
One PR into `claude/project-thread-obmv3z`, titled `Style: <chunk>`. Body: what changed by
category with counts, `tools/style_check.py` totals before and after for the chunk, the
rename list, and anything left on purpose with the reason.

## Chunks
| # | Chunk | Paths | Owns header |
|---|---|---|---|
| 1 | Battle animations | `src/fragments/battle/anim_*.c` | |
| 2 | Battle particles and trails | `src/fragments/battle/` particle*, *trail*, *ribbon*, *grid*, radial_*, model_transforms*, move_animation.c, auxiliary_effect.c, strip_wipe.c, thick_line.c, gradient_rect.c | |
| 3 | Battle engine and scene | every other file in `src/fragments/battle/` | `battle.h` |
| 4 | Fragment 000 audio and GB emulator | `src/fragments/audio_and_gb_emulator/` | its header |
| 5 | Resident audio and GB | `src/audio_*`, `src/gb_*` | those headers |
| 6 | Resident other | every other non-vendored `src/*.c/h`, `include/` | those headers |
| 7 | Lab and Pokédex | `lab_pokemon_list`, `lab_pc`, `pokedex`, `party_summary`, `pokedex_menu` | their headers |
| 8 | Menus and small fragments | every other directory under `src/fragments/` | their headers |
