# English translation: to do

Open work for the English build (`make en`). Plans and history are in `docs/translation.md` and
`docs/subtitles.md`; tick an item off here when it lands and record the details there.

## To fix

- [x] **Katakana draws as Latin letters** (2026-11-13). The small font sets carry a copy of Zero's
      katakana cells; the big ones draw the same sound in hiragana. Details in `docs/translation.md`.
- [x] **Garbled COM nicknames and trainer name** (2026-11-13): `パルn k`, `ium umT`, `S k` came from
      translated team-record fields (`ポケスタ` -> "Stadium" in the preset record at ROM 0x4006D5).
      Those fields, and fragment009's team records, now stay Japanese (`KEEP_JP` in
      `tools/string_catalog.py`).
- [ ] **Team records in English.** Trainer classes and names, nicknames in fragment009 and the preset
      record (702 catalogue entries marked `keep_jp`) stay Japanese because the code that builds
      names from them assumes 2-byte characters. Find that code (it writes the COM nicknames, the
      first two characters doubled) and make it handle ASCII, then drop the `KEEP_JP` ranges.
- [x] **Katakana in the big font sets** (2026-11-14): katakana now lives in unused cells of every
      set, no extra memory. "Second pass" in `docs/translation.md`.
- [x] **Two-character strings** (2026-11-14): catalogued when word-aligned (`はい`, `なし`).
- [x] **Some text ignores per-glyph advances** (2026-11-14): not a bug. The main-menu box is
      proportional; Stadium 1's 20-pixel set just has wide advances.
- [x] **Strings with `%s`/`%d` were not catalogued** (2026-11-14): `ゆけっ！%s` and three others.
- [ ] Still empty in the catalogue: 0x260C4C `のＰＰ`, 0x260EA4 `から`, 0x400DA4 `オさ` (sentence
      fragments; they need their readers looked at first).
- [ ] **The catalogue cannot tell text from text-like data.** A record field that holds Japanese
      can be translated and break the code reading it, as with the team records above. Each
      `rom`-region entry outside plain message tables should be checked against its reader.
- [x] **Text in compressed fragments** (2026-11-14): there is none. The only Japanese in a Yay0
      block is the team records at ROM 0x3FFD78, which belong to the item above.
- [ ] **Fragment strings cannot move.** Only resident strings longer than their room are relocated.
      None are waiting today.
- [x] **Garbage catalogue entry** at ROM 0x72ADC3 (2026-11-14): `NOT_TEXT` in the catalogue tool.
- [x] `é` (2026-11-14): written as `@`, drawn from Stadium 1's cell 118.

## To be verified

- [ ] The six moved move/item names (Rolling Kick, Poison Powder, Sleep Powder, Defense Curl,
      Focus Energy, Paralyze Heal) on screen: the ROM pointers are checked, the screens are not.

- [ ] Subtitle lines marked review in `text/subtitles.json` (the Zero studio's "to review"
      filter): the badge calls (`0x01`..`0x08`, their shared tail phrase is not worked out yet),
      `0x0D`, `0x10`, `0x18`, `0x1A`, `0x23`, `0x35`, `0x38`, `0x53`, `0x59`, `0x66`; `0x47` has no
      line.
- [ ] Battle sound effects (BTLSFX): sort the 77 `unknown` effects into voice and sfx in the Zero
      studio, confirm the round-number calls (`0x10`..`0x15`), and find "Good luck" (lead: system
      effect `0x17`, which plays battle sample 40).
- [ ] System sounds (SYSSFX table, 76 effects, all `unknown`): sort them in the studio's System
      tab; most are menu sounds, a few play the battle voice samples.
- [ ] Badge calls and the tournament openings on screen: only the Free Battle opening and two
      battle lines have been seen.

## To do

- [x] Movie and scene subtitles (workstream 3), 2026-11-13: same hook as the announcer.
- [x] Announcer subtitles (workstream 2), 2026-11-13: `docs/subtitles.md`.
- [x] Battle voice calls (BTLSFX) through the same system, and the Zero studio to edit
      `text/subtitles.json` with the audio, 2026-11-13.
- [x] Subtitle box (2026-11-14): placed as in pokestadium-complete (bottom at y 176), clear of the
      battle's boxes. Screens without a font context still show none.
- [x] Subtitle toggle (2026-11-14): Options > Subtitles, mask 4 of the options byte, on by default.
- [x] Name pass, the list (2026-11-14): `tools/fonts_en.py names`, results in
      `docs/translation.md`.
- [ ] Name pass, the screens: the bound used is the retail text's width, not the box's. Look at
      the listed names where they draw (Kangaskhan and Charmander first) and shorten or squeeze.
- [ ] Release artifact: a BPS patch against the retail dump (`tools/make_bps.py` from
      pokestadium-complete).

## Housekeeping

- Project64 picks settings by header CRC, so every rebuilt ROM needs an RDB entry copied from
  retail's `[665E8259-D098BD1D-C:4A]` (`Save Type=Sram`, `RDRAM Size=8`), or it hangs on black.
- The `E:` stash `On translation-en: shiftable build` is superseded by the merged branch.
