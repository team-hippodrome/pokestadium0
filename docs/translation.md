# English translation of Stadium Zero: work plan

Scope: an English release of Pocket Monsters Stadium (1998), built from this repository, covering
the English font, announcer subtitles, subtitles for the movie and demo animation scenes, English
Pokémon/move names, and a JSON-driven string translation system.

Status: **planning and tooling only.** The build needs `baseroms/jp/baserom.z64` (SHA-256
`ed9f7cd7da795467c1e2b08ed1f878ff5aed906eae9ffe252074aef7a6703d8b`, 16 MiB), which is not on this
machine. Every step below that touches text or font bytes is blocked on that dump; the code paths
and the tooling are not.

## What the engine already gives us

Read from the decompilation, not assumed:

- **Text encoding is EUC-JP.** `func_8001A944` (`src/graphics_textures_2.c`) splits a glyph at
  every byte `>= 0x80`: the lead byte takes the next byte, and the pair is drawn as
  `code & 0x7F7F`, which is the JIS X 0208 code. Both bytes carry the EUC `+0x80` offset, so the
  games' strings are EUC-JP, and **single-byte ASCII passes through the same loop unchanged**.
- **The glyph map accepts ASCII today.** `func_80019F70` (`src/model_renderer.c`) maps
  `0x21 <= c < 0x7F` through a ROM table (`D_8006081F`), JIS rows 1/3/4/5 through other tables,
  and `0x2574` (ー) directly. So a translated ASCII string renders without touching the font code —
  it renders in the *Japanese* font's Latin glyphs, which is the reason for workstream 1 rather
  than a hard blocker on it.
- **Font sets**: `func_8001A194` opens the font archive at ROM `0x2B2C80..0x2E0BE0` and loads up to
  six sets by mask bit, with cell sizes 32x32, 24x24, 20x20, 16x16, 12x12, 10x10
  (`func_8001A118(mask, size_a, size_b, size_c, file)`). Advance is **one value per set**
  (`func_8001A3E4` returns `x + set->advance`), i.e. the Japanese build is monospace.
  Stadium 1 (US, `~/pokestadium-complete`) has the same six slots at 32x32, 24x24, 24x20, 16x16,
  16x12, 16x10 with a **per-glyph advance table** (`Font_GetGlyphAdvance`) and wide Latin cells.
- **Frame hooks that a subtitle port needs exist here too**: `StageLoader_SetupFrame`
  (`src/stage_loader.c:207`) is the end-of-frame hook `Subtitles_Draw` is called from in the
  Stadium 1 fork, and `Audio_UpdateBattleAudioFrame` is called from `src/3D140.c:614`, which is
  where `Subtitles_OnClip` fires there.
- **Strings live at fixed VRAM addresses in the resident image** as `extern char D_8007B7D0[]`
  style symbols, e.g. the free-battle menu labels in `src/game_state.c:395-406`. Resident VRAM maps
  to ROM as `rom = vram - 0x7FFFF400` (`tools/map_rom.py:310`, `tools/place_sections.py:55`), so
  every one of those strings is addressable and rewritable in place.

## Workstream 1: English font

Zero's font archive is a Japanese glyph sheet: square cells, monospace advance, ASCII mapped into
the sheet's Latin slots. Stadium 1's is a Latin sheet: wide cells, per-glyph advance.

1. Dump both archives (Zero `0x2B2C80`, Stadium 1 `fonts_ROM_START` at US `0x3BA190` in
   `~/pokestadium-complete/include/sections.h`) with the existing BinArchive reader.
2. Compare the six sets: glyph count, cell geometry, ASCII map (`D_8006081F` vs the US map in
   `gUiRestoreTextureDL`), advance tables.
3. Decide per set, not globally. The sets actually loaded per stage decide the work: `Font_Init`'s
   mask argument at each call site is the audit (`grep -rn "Font_Init(" src`), e.g. the lab uses
   `0x1C`, the fatal error screen `6`.
4. Two forms, cheapest first:
   - **Repack** (the fallback): write the US Latin glyph bitmaps into Zero's existing square cells,
     centered, and keep monospace advance. No code change; looks like a fixed-pitch Latin font.
   - **Port** (the target): adopt the US per-glyph advance table and the US cell geometry for the
     sets that are Latin-only in practice. This is a source change to `Font_Init`/`Font_DrawChar`
     (`src/graphics_textures_2.c`), and the US code in `~/pokestadium-complete/src/graphics_textures.c`
     is the reference implementation of both the advance table and the 4-bit packing.
5. Keep the Japanese sheet reachable. Untranslated strings must keep drawing until the last one is
   translated; the Stadium 1 fork solved the mirror-image problem (kana in a Latin build) with a
   second archive and a glyph base (`FONT_KANA_GLYPH_BASE`, `Font_MapJisGlyph`,
   `tools/extract_font_kana.py`). Reuse that shape in reverse rather than inventing a new one.
6. `é` is the known gap: Zero's map covers `0x21..0x7E` only, so "POKéMON" cannot be spelled. Either
   extend the map with the US `0xA0..0xFF` table (`D_8006F608` in the fork) or spell it "POKeMON".

Verification: a headless render of every glyph in the sheet to a PNG sheet per set (the fork's
`tools/png_rgba16.py` and `tools/font_i4.py` already convert font data), plus an in-game screenshot
of one menu per stage.

## Workstream 2: announcer subtitles

Direct port of `Subtitles_OnClip` / `Subtitles_Draw` / `Subtitles_Clear` from
`~/pokestadium-complete/src/text_system.c`, which is 90 lines and already debounced for a 320x240
stage.

1. Find Zero's announcer clip start inside `Audio_UpdateBattleAudioFrame` (`src/3D140.c`); the clip
   index is the trace point.
2. Add the subtitle state to the padding area of Zero's save/BSS block, and an options bit if the
   options screen has a free bit (the fork uses `MENU_OPTIONS_SUBTITLES 0x40`). If Zero has no
   options screen, ship it always-on and skip the toggle.
3. Call `Subtitles_Draw` at the end of `StageLoader_SetupFrame`.
4. Text: one line per clip index, injected as a data override (workstream 5's machinery). Clip
   numbering is Zero's own; it is not the Stadium 1 table.

Verification: every clip id in the pak resolves to a non-empty line, and the line count matches the
pak's; then a stage-by-stage listen-and-read pass.

## Workstream 3: movie and animation subtitles

The intro/demo scenes (`src/fragments/demo_scenes/`, `src/dp_intro.c`) play voice without any text
layer, and several cues fire outside battles ("GOOD LUCK!" before a battle).

1. Inventory the scenes: which fragment starts which clip, and what draws during it. The dialogue
   scenes that already draw Japanese lines carry their own timing; the ones that draw nothing need
   a cue table of their own.
2. Model it as one table: `{scene, clip id, start tenths, hold, text}`, the fork's multi-page
   subtitle format (`SUBTITLE_PAGE 0x7F` + start time) fits this without a schema change.
3. Reuse workstream 2's draw path; only the trigger differs (scene start instead of battle audio
   frame).

Verification: a per-scene checklist with clip id, text and on-screen duration; no line may be
shorter than one second on screen.

## Workstream 4: English Pokémon and move names

1. Locate the name tables: species names are a pointer/string table in the resident image
   (`Text_CopySpeciesName`, `src/gb_data.c:182`, reads `D_80064C44[species]`), move and item names
   follow the same shape. Dump them with workstream 5's tool.
2. Length budget: a kana name is 10 bytes of EUC-JP for five characters; "Bulbasaur" is 9 bytes and
   "Victreebel" 10. Most fit in place; the ones that do not need relocation (a longer string moves
   into free `.rodata` and the pointer/table entry is repointed).
3. Battle HUD labels are drawn into fixed boxes (`BattleHud_DrawSpeciesNameLabel*`,
   `src/fragments/fragment012_17ED00/`), so measure with `Font_MeasureTextExtent` and list every
   name that overflows its box.
4. Names come from `docs/glossary.md` (already the repo's JP→EN reference, with RBY spellings where
   they differ).

Verification: all 151 species + 165 moves + items resolve, no name overflows its HUD box, and the
GB-side names (`Text_TranscodeName`) keep working — they are a separate 6-byte encoding.

## Workstream 5: string translation system

Same shape as the Stadium 1 fork's `text/` + `tools/patch_textdata.py`, adapted to Zero's layout:
Zero has no single textdata archive of 42 tables; the strings sit in the resident image at fixed
addresses.

1. `tools/translate_strings.py dump` scans the C sources for `extern char D_8XXXXXXX[]` symbols,
   maps VRAM to ROM, decodes NUL-terminated EUC-JP, and writes `text/strings_ja.json` keyed by
   symbol. Strings that do not decode are data, not text, and are dropped.
2. `tools/translate_strings.py apply` reads `text/strings_en.json`, encodes ASCII, and writes each
   translation in place with NUL padding, reporting every string that does not fit (those become
   the relocation list).
3. Fragment-local strings (`D_812xxxxx` and up, inside fragment images) are out of scope for the
   first pass: `yamls/jp/mapping.yaml` has no per-fragment `link_base` yet (its own header calls the
   per-fragment text/data boundaries pending), so the tool reports them as unmapped instead of
   guessing. The fragment images' ROM offsets are in the yaml segments and their text starts are in
   `linker_scripts/jp/symbol_addrs.txt`; wiring that map is a step of its own, and until it lands
   most of the game's text is missing from the inventory.
4. The release artifact is a BPS patch against the retail dump, as the decomp's own convention.
   `tools/make_bps.py` from `~/pokestadium-complete` is stdlib and can be copied in.

Verification: dump → apply → dump returns the translations; `cmp` shows changes only inside
declared string extents; the rebuilt ROM boots and a scripted menu pass shows no Japanese in the
translated tables.

## Order and effort

1. String tool + inventory (no ROM needed to write, 1 session; needs the dump to run).
2. String translation pass (the bulk of the content, iterative).
3. Font dump comparison, then the repack or the advance-table port.
4. Announcer subtitles (port + table).
5. Scene subtitles (inventory + table).
6. Names (data pass, then HUD overflow pass).

Steps 1-2 give a readable English build with the Japanese font's Latin glyphs; nothing else is
blocked behind the font work.

## Risks

- **Layout overflow.** Japanese is 2 bytes per character in a fixed box; English is 1 byte per
  character at a different advance. Every fixed-position string needs a measured check or it
  clips, and the measure depends on the font work settling first.
- **No proportional text until the font port lands.** Counting characters does not predict width
  while the build is monospace.
- **The glyph map, not the sheet, decides coverage.** Extending the font without extending
  `func_80019F70` (or its tables) produces blank glyphs.
- **The announcer pak is per-region.** Zero's clip ids and count are not Stadium 1's, so the fork's
  `text/announcer.json` is a format reference only, never content.
