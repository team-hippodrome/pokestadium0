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

## Workstream 1: English font — done

Zero's font archive (ROM `0x2B2C80..0x2E0BE0`) holds six PERS-SZP files, one per set, each 257 glyph
cells: 144 Latin slots, the two-cycle gradient glyph and 112 kana glyphs. The cells are 16x10, 16x12,
16x16, 24x20, 24x24, 32x32 — the **same geometry Stadium 1 uses** (`fonts_ROM_START` `0x3BA190` in
that game's dump), so its archive drops into the same slot. Its Japanese glyphs are square and every
glyph in a set advances by one value (10, 12, 16, 20, 24, 32 px), which is why Zero's Latin letters
are full-width. Stadium 1's set files instead start with a **0x90-byte advance table** followed by
0x91 Latin glyphs, so each glyph advances by its own width (space 4, `A` 7, `i` 3 in the 16x10 set).

The English build is `make en` (see "English build on the shiftable layout" below): Stadium 1's set
payloads go into Zero's archive slots and its Latin glyph numbers into `D_8006081F`
(`tools/fonts_en.py`), and two functions are C under `#ifdef ENGLISH`: `func_8001A118` registers
`file + 0x90` as the set's glyphs, and `func_80019F70` maps printable ASCII through the Latin map and
copies the glyph's advance from the table into the set's advance byte, which both glyph drawers read
right after the call. Every other code takes the retail path. Until 2026-11-13 these were binary
patches at the functions' retail size, because the build could not move code yet.

Known limits: kana has no glyph in the Latin sheets, so an untranslated Japanese string draws blank
cells with the space advance (the intended signal for what is left to translate); the two-cycle
gradient glyph sits at a cell index the Latin sheets do not have, and nothing in Zero enables
two-cycle text; `é` is not in the map, so "POKéMON" is written "POKeMON".

## Workstream 2: announcer subtitles — done (2026-11-13)

Done together with workstream 3; see `docs/subtitles.md`. Zero's announcer turned out to be sound
effects from one bank, not a stream, so the plan below changed: the hook is the effect start in
`func_80043DD0`, the lines were written down from the bank, and the state lives in new
`.data` of `src/stage_loader.c`. Original plan:

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

## Workstream 3: movie and animation subtitles — done (2026-11-13)

The spoken scene lines (tournament and Free Battle openings, badge calls, the champion) are
effects of the same announcer bank, queued when the battle music starts, so workstream 2's hook
and table cover them; see `docs/subtitles.md`. No other voice source was found: the bank's other
players are `Audio_PlayCommand` case 0x50 (hooked too) and `func_80041834` (never called), and
Zero has no streamed audio (`src/audio_stream.h` declares Stadium 1's `AudioStream_*`, which
nothing defines). Original plan:

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

## IPL3 boot checksum (2026-11-12)

IPL3 verifies a CRC over the **first megabyte** of the ROM (0x1000..0x101000) against the header
words at 0x10/0x14 and halts on a mismatch. A halt is a black screen with no exception, so every
patch below 0x101000 looked like "the game hangs".

Evidence: a one-byte change in the font sheet (0x2B2D00, above 1 MB) boots; a one-word commutative
operand swap in the loader (0x1AD44, below 1 MB) hangs.

Zero is CIC-NUS-6103; its seed is 0xA3886759 and the final mix is `(a3^t2)+t3`, `(s0^a2)+t4`.
`tools/fonts_en.py` ports Project64's `CalculateRomCrc` (`rom_crc`, `detect_seed`, `fix_checksum`),
re-stamps the header after patching, and the checker refuses a ROM whose stamp is stale.

## Font archive tail (2026-11-12)

Zero's font archive spans 0x2B2C80..0x2E0BE0 (0x2DF60 bytes, six PERS-SZP files). Stadium 1's
archive is only 0x10FA0 bytes, so the first patch cleared the remaining 0x1CFC0 bytes —
116,287 of which are nonzero. Those are Zero's own glyph sheets for the big sets (glyph data
for 24x20/24x24/32x32 starts at 0x2BE3D0), and clearing them broke any screen that loads
those sets. The archive header defines every file's extent, so clearing the tail is not
needed: `full` now leaves it alone and only the archive's own bytes change.

## Per-glyph advances, and why the archive header must not change (2026-11-12)

Stadium 1 stores a 0x90-byte advance table at the start of every font file, so its 145 glyphs are
proportional while Zero's 257 are monospace (one advance per set). `func_8001A118` is patched to
register `file + 0x90` as the glyph base, and `func_80019F70` copies the glyph's advance out of that
table into the set's first byte (`advance`), which `func_8001A3E4` already reads per character.
Verified against the built ROM: `A` advances 7/7/10/12/14/18 in sets 0..5, space 4/4/6/7/8/10.

The font context block is never cleared (`main_pool_alloc_with_func` does not zero), so a slot the
screen did not load holds stale data. The mapper therefore range-checks the slot (`sltiu 6`), exits
when `font_context` is null, and skips the read when a slot's glyph base is null.

### The archive header stays retail

Replacing Zero's whole archive with Stadium 1's (its own header, 145 glyphs per set, total
0x10FA0) froze the screen behind the Battle menu: the panel never appeared, only the background and
the `IDNo.` stamp. Zero's UI code indexes those sheets, so the archive is now patched *in place*:

* Zero's header (file offsets, compressed sizes, total 0x2DF60) stays byte-identical to retail, and
  every set keeps its 257 glyphs' worth of slot;
* each slot receives Stadium 1's PERS-SZP payload (its own advance table + 145 glyphs), zero-padded
  to the slot size, which is safe because the PERS header carries the real extents.

Only bytes 0x2B2CFE..0x2E0BD3 -- the payloads -- differ, plus the map table, the two functions and
the header CRC.

### Sets must decompress to Zero's size (2026-11-12)

Stadium 1's sets hold 145 glyphs, Zero's 257, and Zero's UI indexes glyphs up to 256. A set
that decompresses smaller than Zero's makes those reads leave the pool block, which is an address
error mid-frame: the picture freezes while the audio thread keeps playing. Each English set is
therefore padded to Zero's exact decompressed length with blank cells (0xF0, the value of Zero's
own empty glyph) and recompressed; the payload still fits its slot with room to spare (set 5:
#67AD in a #F3F0 slot).

### Stale set slots (2026-11-12)

Screens load subsets of the six sets: GB Tower uses mask 0x18, the ones behind てもち/バトル use
0x3C, so slots the screen did not load keep whatever the pool block held before. Retail's mapper
reads nothing and survives that; the advance lookup dereferenced the stale glyph base and faulted.
The mapper now requires the base to be inside `sMemPool` (0x800A94A0, start+0x100 <= base < end)
before touching the advance table, so an unloaded slot can only cost a monospace character.

### What the save state showed (2026-11-12)

The frozen state (gopher64, RDRAM stored word- and byte-reversed at state offset 0x1E555) shows the
font context the failing screens build with mask 0x3C:

```
entry0 adv= 5 h= 0 w=48 ptr=0x06003058   <- never loaded
entry1 adv= 5 h= 0 w=48 ptr=0x060030a0   <- never loaded
entry2 adv=16 h=16 w=16 ptr=0x801a13d0   <- set 2
entry3 adv=20 h=20 w=24 ptr=0x801831e0   <- set 3
entry4 adv=24 h=24 w=24 ptr=0x8015ef90   <- set 4
entry5 adv= 5 h= 0 w=49 ptr=0x0600312c   <- never loaded
```

So the failing screens do call `Font_SetActive` with masks they never loaded, and those slots hold
stale pool bytes. `text-0x90` on 0x06003058 is outside RDRAM: address error, picture stops, audio
thread keeps playing. The mapper now refuses any glyph base outside 0x80001000..0x803F0000. Note the
earlier attempt read `sMemPool.start` at offset 0; in this build the pool struct keeps its queue
first and start/end sit at 0x20/0x24, so that check returned start=0 and accepted the bad pointer.

## Strings: catalogue, dictionary, apply (2026-11-12)

`tools/string_catalog.py dump` scans the ROM for NUL-terminated EUC-JP runs and keeps the ones that
read as text (70% kana/digits/Japanese punctuation, at least three characters): 2722 strings today,
1081 of them in the resident image. Each entry is keyed by ROM offset and carries `jp`, `en`,
`room` (bytes the original occupied) and `region`. Re-running `dump` merges, so nothing typed into
`en` is lost.

`text/dictionary.json` holds jp->en pairs. It is seeded from Stadium 1's `species_names.json`
(151 official names) plus menu, battle and trainer vocabulary. `string_catalog.py fill` copies any
matching entry into `en` when the English fits in `room`; 581 strings are filled at the moment, the
rest are Pokédex flavour text and names waiting for review.

`tools/translate_strings.py` writes the translations into the built ROM in place (ASCII plus NUL
padding inside `room`); the build re-stamps the IPL3 checksum afterwards, since the resident image
sits below the first megabyte. Only uncompressed, catalogued runs are ever written.

Full English build (since 2026-11-13; see the last section):

```
.venv/bin/python tools/string_catalog.py dump      # merge any new jp strings
.venv/bin/python tools/string_catalog.py fill      # dictionary -> en, where it fits
make en EN_FONT_ROM=~/pokestadium-complete/baseroms/us/baserom.z64   # -> build/pokestadium0-en.z64
```

## Bulk translation (2026-11-12)

1657 distinct untranslated strings were split into ten batches (`text/auto/batchNN_jp.json`), each
translated against the brief in `text/auto/README-translate.md` (Stadium 1 localisation style,
official names from `text/dictionary.json`, ASCII only, `len(en)+1 <= room`, line breaks and line
widths preserved). `string_catalog.py merge` absorbs the `*_en.json` results into
`text/strings.json` for every entry with that Japanese text, but only where the English fits.

Result: 2583 of 2722 strings translated, 139 still Japanese (garbage entries and leftovers), and
138 that do not fit their original slot — official names like `Weepinbell` in a slot sized for four
kana. Those need relocation (write the English elsewhere and patch the reference), which is the same
mechanism workstream 4 needs for attack and Pokédex names.

## Room counts the terminator and the padding (2026-11-13)

`room` used to be the Japanese text's byte length without its NUL, and the fit check
`len(en) + 1 <= room` then also reserved a NUL, so every string lost a byte plus its alignment
padding. String literals start word-aligned, so `dump` now counts the NUL and, for a word-aligned
string, the zero bytes up to the next word. All 41 resident strings among the old overflow are
reached through pointers, and the fragment009 ones are 16-byte record fields, so the padding is
theirs to use.

Result: 132 of the 138 overflowing translations fit, giving 2715 of 2722 strings translated. Of
the 7 left, one is a scanner false positive (`いいいいいいぅ` at 0x72ADC3) and six are move and item
names that need more than their 12 bytes: Rolling Kick, Poison Powder, Sleep Powder, Defense Curl,
Focus Energy, Paralyze Heal.

## Kana stays visible (2026-11-12)

Stadium 1's sets hold 145 glyphs, Zero's 257. The English payload keeps Stadium 1's 0x90-byte
advance table and 145 glyphs, then carries **Zero's own cells 145..256**, so untranslated Japanese
(species names, nicknames, Game Pak names) still draws. `func_80019F70` handles printable ASCII and
tail-calls a copy of the retail mapper kept in the free tail of the font archive for everything
else, so kana and the text macros keep retail behaviour exactly.

Correction (2026-11-13): only hiragana lands in the kept cells (`D_8005E47F[c] + 0xAF`). Katakana
maps to `D_8005E37F[c] + 0x45`, from glyph 69 up, which is inside Stadium 1's Latin range, so a
katakana nickname draws as accented Latin letters (`イワイワ` shows as `mïmï` on the rental entry
screen). Fixed the same day; see "Katakana and team records" below.

## Katakana and team records (2026-11-13)

Zero's retail mapper reaches every one of its cells 0..144 from Japanese text: row-1 symbols
(0..68), full-width digits (16..25) and capitals (26..51), which Stadium 1's Latin glyphs share,
and katakana (69..148), which they do not. Three layouts were tried:

* All 257 of Zero's cells kept and the 83 Latin glyphs ASCII uses appended: correct everywhere,
  but each set grows by a third, and the order-select screen (sets 2..5, about 190 KB more) ran
  out of memory: `GfxImage_Allocate` returned NULL and `GfxImage_Initialize` stored through it.
* What ships: Stadium 1's 145 glyphs, Zero's cells 145..256, and in the three small sets (16x10,
  16x12, 16x16; 12 to 20 KB each) a copy of Zero's cells 69..144 from cell 257.
  `func_80019F70` sends katakana there in those sets and to the hiragana of the same sound
  (`c - 0x100`, one JIS row up) in the big ones. Every non-ASCII glyph now takes the set's own
  advance, which `func_8001A118` keeps in the set entry's spare byte; before, a kana after a Latin
  letter took that letter's width.
* The archive is rebuilt with its own header (`fonts_en.english_archive`) and is a ROM segment of
  its own, so the larger sets move what follows; its ROM range symbols follow it.

The garbled COM nicknames (`パルn k`, `ium umT`) and trainer name (`S k`) were not the font. The
preset Pokemon record at ROM 0x4006CA holds a nickname and a trainer name (`ポケスタ`) as packed
Japanese fields, and the catalogue had translated them ("Venusaur", "Stadium"). The code that
builds the COM team's names from these fields copies them as 2-byte characters, so the ASCII came
out split and leaked into the nicknames. Those fields, and fragment009's team records, which have
the same layout, are now `KEEP_JP` ranges in `tools/string_catalog.py`: `dump` marks their entries
`keep_jp` and `fill`/`merge` leave them alone. Checked in Project64: the entry, order-select and
battle screens show `イワイワ`, `パルパル`, `スピスピ`, `ガール`, and the battle HUD `ニドニド`.

## English build on the shiftable layout (2026-11-13)

`make en` (`production.py build --compare 0 --english <Stadium 1 US ROM>`) replaces the patch
pipeline. It compiles with `-DENGLISH`, so the two font functions are C, then writes the font
payloads, the Latin map and `text/strings.json` into the ROM it just laid out, each retail offset
translated through the piece it now sits in. Nothing assumes the retail layout any more, so code and
data may grow. The screens checked (title, main menu, entry, order select) are pixel-identical to
the old patched ROM.

A resident translation longer than its `room` no longer has to be cut: the build puts it after the
resident data under a new label and resolves the retail address to that label, so every pointer and
`%hi/%lo` that named the old string names the new one. The build refuses a string that nothing
refers to by its start address (an array inside a struct cannot move this way). `merge` therefore
fills resident entries whatever their length. This moved the last six: Rolling Kick, Poison Powder,
Sleep Powder, Defense Curl, Focus Energy and Paralyze Heal, each reached through one table pointer.
Fragment strings still have to fit.

## Second pass (2026-11-14)

**Font layout.** Every set, big ones included, is now Stadium 1's 0x90 advances, its Latin cells
0..144 and Zero's cells 145..256: 257 cells, the retail count, so no screen needs more memory.
Zero's katakana cells 69..144 are drawn into cells the English text never uses
(`fonts_en.katakana_cell`, mirrored by `Font_GetKatakanaGlyph` in `src/model_renderer.c`): the
accented Latin cells 95..117 and 119..144, and the full-width lower-case cells 149..174, whose
characters (0x2361..0x237A) `func_80019F70` now draws with the ASCII letters. Katakana therefore
draws as katakana in every set; the hiragana fallback and the copies past cell 256 are gone.
Checked on the hi-res entry and order-select screens and in battle.

**é.** Cell 118 keeps Stadium 1's é and `@` maps to it. `translate_strings.encode` writes `é` as
`@` and everything else non-ASCII as EUC-JP, so `Nidoran♀` keeps its sign. The catalogue spells
Pokémon, POKéMON, Pokédex and Poké Ball/Doll/Mart with it; the Zero studio accepts é.

**Two-character strings.** `string_catalog.scan` takes two kana when they start word-aligned
(`はい`, `いいえ`, `あり`, `なし`); unaligned pairs are noise. `NOT_TEXT` drops two ranges that
read as Japanese and are not (the `いいいいいいぅ` fill at 0x72ADC0, sample data at 0xE30148).

**printf strings.** `likely_text` ignored `%s`/`%d` when counting, so `ゆけっ！%s`, `は%sした！`,
`なまえ/%s` and `ボックス%d` failed the 70% test and stayed Japanese. Conversions are now stripped
before counting; "Go! %s" was seen in battle.

**Compressed fragments hold no text.** Every Yay0 block was decompressed and scanned: the only
Japanese is the block at ROM 0x3FFD78, rental and team records of the `keep_jp` kind. Nothing to
catalogue there.

**The main-menu box is proportional.** Its drawer (`Font_Printf` -> `func_8001A3E4`) reads the
set's advance after `func_80019F70`. It looks monospaced because Stadium 1's 20-pixel set has
wide advances (11..12 for most letters, 7 for i and l). No code change.

**Name pass.** `tools/fonts_en.py names --us <Stadium 1 ROM>` measures every species, move and
item name of Stadium 1's own tables (not `text/strings.json`) in each set against the widest the retail game could draw there (its longest
Japanese name times the set's advance). Wider than that, per set: 10px species 54, moves 27; 12px
species 12 (Kangaskhan and Charmander 70 against 60; Farfetch'd, Hitmonchan, Flycatcher,
Electabuzz, Charmeleon, Exeggutor, Exeggcute, Wigglytuff, Victreebel, Triple Bird), moves 0; 16px
species 34, moves 5; 20px species 10, moves 3; 24px species 10; 32px species 2 (Charmander,
Kangaskhan); items none. Three of those moves are spelled shorter in the catalogue, as on the
Game Boy (THUNDERPUNCH, THUNDERSHOCK, PoisonPowder). The bound is the retail text, not the box, so each listed name still
needs a look on its screen.
