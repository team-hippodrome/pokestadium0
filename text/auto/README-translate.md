# Translation brief

Each `batchNN_jp.json` is a list of `{jp, room, count}`. Produce `batchNN_en.json`: a JSON object
mapping each `jp` string to its English translation.

Rules:

- Style: the English localisation of **Pokémon Stadium (N64, 1999)**. Official terminology, official
  Pokémon/move/trainer-class names, plain sentence case for dialogue, ALL CAPS only where the
  Japanese is a label or the original Stadium build shouts (mode names, PA/announcer lines).
- Use the official English names in `../dictionary.json` when a string is one of those names.
- ASCII only. The game's glyph map covers 0x20-0x7E.
- `len(en) + 1 <= room` bytes. `room` is the size of the original Japanese string; English is
  shorter per character, so this is usually easy, but check.
- Keep `\n` where the Japanese has it, and keep every line no longer than the Japanese line it
  replaces (text boxes are narrow). Re-wrap if needed.
- Pokédex entries: translate the meaning, keep the three-line shape.
- Trainer and nickname strings (personal names like `サトシ`, `どろスター`) are transliterated names in
  capitals: `ASH`, `DOROSTAR`. Nicknames invented by players stay kana in game, so only translate
  what is in the batch.
- If a string is data rather than language (garbage that slipped into the catalogue), map it to an
  empty string `""` and say so in your summary.

Write the file, then report: how many strings, how many left `""`, and any string you were unsure of.
