# Subtitles for Stadium Zero

English subtitles for everything the announcer says: the tournament and Free Battle openings
before a battle, the badge calls, and the battle play-by-play. They are part of `make en`
(`-DENGLISH`); the retail build is unchanged.

## How Zero's announcer works

Unlike Stadium 1, which streams its announcer from a GSM pak, Zero plays it as ordinary sound
effects from one MUS bank, `JIKKYOU.WBK` (実況, play-by-play): 143 ADPCM samples in ROM
0xCED900..0xE74F3C and an effect table of 111 entries (`0x00`..`0x6E`). Each effect is a short
command stream that plays one to four samples in a row, so a line is often a shared phrase
(`ここで`, `おっと`, `さあ`) followed by its own sentence.

* `func_80043CE8(id, 0.0f, level)` queues effect `id` (a ring of 10, at most two pending).
  Battle code queues play-by-play; `Audio_StartMusicTrack` (`func_8003EECC`) queues the openings
  (`0x09`..`0x17`) when the battle music starts.
* `func_80043DD0` (Stadium 1's `Audio_UpdateBattleAudioFrame`) starts the next queued effect with
  `func_800383DC(bank, effects, id, ...)` once `func_80037B7C(handle)` says the previous one ended.
* `Audio_PlayCommand` (`func_800407B0`) case 0x50 plays effect `D_80077540` directly. Which
  effects that covers is not established; the badge calls (`0x01`..`0x08`) are the candidates.

A second bank, `BTLSFX.WBK` (88 effects, 47 samples, ROM 0xC836E0..0xCE8145), holds the battle
sound effects and the English voice calls ("Get ready!", the round numbers, "Semifinal!", "Come
again!"), played by `Audio_PlayCommand` with `func_8003834C(D_800B4188, D_800B41A4, id, ...)`.

An effect table is not tied to one sample bank. `func_8003F6AC`, the system-sound player, plays
SYSSFX effect `0x17` with the battle samples (`func_8003834C(D_800B4188, D_800B41A0, 0x17, ...)`),
and an effect started by another effect (`startfx`, `func_800370AC`) inherits its sample bank. So
the system table (`D_800B41A0`, 76 effects) can speak too. The other banks, MVOICE (cries),
TRCSFX and SPCSFX (move sounds), hold no speech.

Every sound effect, whatever started it, ends in `func_8003815C(bank, effects, channel, id, ...)`
in `src/libnumus/player.c`, which assigns the sound its handle. In the English build it calls
`Subtitles_OnSound(effects, id, handle)`, and the effect table (`D_800B41A8` announcer,
`D_800B41A4` battle, `D_800B41A0` system) says which line table to use.

## What the build adds

* `src/libnumus/player.c` (`#ifdef ENGLISH`): the hook above, once the handle is assigned.
* `src/stage_loader.c` (`#ifdef ENGLISH`): `Subtitles_OnSound` looks the effect up and, if it has
  a line, records it and the sound handle; a sound without one (a hit, a menu blip) leaves the
  subtitle alone. `Subtitles_Draw`, called from `StageLoader_SetupFrame` after the stage's queued
  text, draws the line while `func_80037B7C(handle)` reports the sound playing and 45 frames after,
  on a translucent box in the lower left (x 8, width 216, bottom at y 176, lines one pixel
  apart, as in pokestadium-complete; doubled on 640x480 stages), with the smallest font set the
  screen has loaded. That puts it above the battle's message and send-out boxes.
* The Options screen (fragment006) has a **Subtitles** row, On/Off: mask 4 of the options byte
  (`func_80025214`, save data + 0x7A43), set for off, so an old save has them on. The save data is
  only in memory on the menus (`D_800AE8E0` is NULL in a battle), so `Subtitles_Draw` keeps the
  last value it saw. The row's strings make fragment006's `.rodata` an `APPENDED` section too.
* `text/subtitles.json`: the lines, per bank and effect id: `kind` (`voice`, `sfx`, `unknown`,
  `none`), `jp`, `en`, `review`, `note`. Only `voice` entries with English get a subtitle.
* `tools/subtitles.py` (run by `make en`) writes `src/subtitles_en.h` from it: one table per bank,
  the Japanese as comments, `REVIEW` where it is a guess. It refuses a line wider than 34
  characters, the box's width.
* `tools/production.py` `APPENDED`: `stage_loader.c`'s `.data` and `.rodata` exist only in the
  English build and have no retail address, so a non-matching build places them after the
  resident data.

Checked in Project64: the Free Battle opening (`0x11`) shows over the stadium intro through the
`func_8003815C` hook, and "They're staring each other down." (`0x2E`) and "No orders from the
trainer!" (`0x31`) while the battle waits for orders (through an earlier hook in `func_80043DD0`).

## Editing the lines: the Zero studio

`pokestadium-research/stadium-assets` has a Zero studio (`studios/zero`, at `/zero/` of
`py serve.py`). Its extractor renders every effect of the three tables with the asset site's
Numus renderer (the game's own pitch and timing), with the sample bank the game pairs it with and
mixed with the effects it starts, into one clip each; the page lists them per table with a play
button, a download link, the clip length (or "loop"), and the fields of `text/subtitles.json`,
which **Save** writes in place (from this machine only; `$ZERO_SUBTITLES` overrides the path).
Then `make en`.

```
cd pokestadium-research/stadium-assets
(cd studios/zero && py -I tools/extract.py)   # once; build.sh does it too
py serve.py                                   # http://127.0.0.1:8764/zero/
node studios/zero/qa/smoke.mjs                # optional check of the page
```

## Where the lines come from

The ROM holds no text of the voice. The bank was read from RAM after boot (the expanded
`N64 PtrTablesV2` image at `D_800B418C` and the effect table at `D_800B41A8`, both decompressed by
the game), the samples decoded with pokestadium-complete's `tools/audio/numus_audio.py`, each
effect's samples joined in order, and the result written down by ear (the bank plays at about
12 kHz). The Japanese and the translation are in `text/subtitles.json`; for example `0x11` is
`ここ地下コロシアムで`, "here in the underground Colosseum". The battle bank's entries start as
`unknown` and are sorted by ear in the studio.

The effect stream format, as far as it was needed: `81 n` (or `81 80 n`) selects sample `n`,
`30 len` plays it, `60 len` waits, `b0 n` also starts effect `n`, `90`..`af` take one byte, `84`
takes seven, `80` ends.

## Open

* The battle bank: 77 of its 88 effects are still `unknown` (`0x00` is empty). Ten are entered as voice (round numbers `0x10`..`0x15` marked review, `0x16` Semifinal, `0x25` Get ready,
  `0x28` Come again, `0x29` Bye); "Good luck" has not been found yet. The best lead is system
  effect `0x17` (battle sample 40, also in battle `0x17`, `0x3A`, `0x43`, `0x44`), which is still
  unidentified; the system table is all `unknown` for now.
* System effect `0x0F` plays through a bank loaded at run time (`D_800FD690`), so its clip uses the
  system samples and may not sound like the game.
* The `REVIEW` lines: the badge calls share a tail phrase not yet worked out, and a few
  battle lines (`0x1A`, `0x23`, `0x35`, `0x38`, `0x53`, `0x59`, `0x66`) are best guesses. `0x47`
  has no line at all.
* A screen without a font context shows no subtitle. The openings and battles have one.
* `é` in a line is written as `@`, the byte the English glyph map draws as é.
