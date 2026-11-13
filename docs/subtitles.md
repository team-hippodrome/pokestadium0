# Subtitles for Stadium Zero

Port of the announcer-subtitle feature from `~/pokestadium-complete` (`src/text_system.c`,
`Subtitles_OnClip` / `Subtitles_Draw` / `Subtitles_Clear`) to Zero, plus translated lines for the
movies and the 3D cutscenes that only have Japanese voice and glyphs.

## How Stadium 1 does it

* `Subtitles_OnClip(clip)` runs on the audio thread the moment an announcer stream starts
  (`Audio_UpdateBattleAudioFrame`, `src/3D140_2.c:2293`): it records `osGetCount()` as the start
  time, the clip number, and `SUBTITLE_HOLD_FRAMES` (45) so short clips can still be read.
* `Subtitles_Draw()` runs at the end of every frame from `StageLoader_SetupFrame`
  (`src/stage_loader.c:365`), just before `gDPFullSync`. It bails when no clip is active, counts the
  hold down while `AudioStream_IsPlaying(1) == 0`, checks the Options toggle, then draws a
  translucent box (8, y, 216 wide, above the battle message box at y 179) with the smallest loaded
  font set and white text.
* Text is announcer table `TEXT_ANNOUNCER_TABLE`, string `clip - 1`. A line can hold page markers
  `0x7F <tenths>`: `Subtitles_GetWindow` shows the last window whose start time has passed, keeping
  a long line in step with the voice.
* `Subtitles_Clear()` runs when the stage ends, because the text archive belongs to the stage.

## Where it goes in Zero

| what | address | notes |
|------|---------|-------|
| `StageLoader_SetupFrame` | `0x80005F50` | same shape as Stadium 1's; ends `jal func_8000515C` (`Gfx_AllocDisplayList`) at `0x80006230` |
| draw hook | word at `0x80006230` | replace that `jal` with `jal <subtitles code>`; the delay slot (`sw $t0,0($v0)`) stays, and the new code calls `func_8000515C` itself before returning to `0x80006238` |
| `Audio_UpdateBattleAudioFrame` | `0x80043DD0` | unmatched asm; this is where `AudioStream_Start(1, seq, 0x7E, 0)` is issued, so the clip-start hook goes here |
| audio stream API | `src/audio_stream.h` | `AudioStream_Start`, `AudioStream_IsPlaying` are already matched and callable |

Free space for new code and tables: the tail of the font archive. `full` leaves
`0x2B42C3..`-ish payload ends, and slot 0 holds `0x97D` free bytes after its payload; slot 5 has
about `0x1F000`. The retail glyph mapper copy already lives at `ZERO_FONTS_END - 0x200`
(`0xB02E09E0`).

## Why binary patches, not C

`tools/production.py` pins each source file's `.text` span. A C function that grows pushes the rest
of its file down while every `jal`/`%hi-%lo` in other files keeps the old address, which produces a
ROM that passes the byte-identical check and then misbehaves. Everything here is therefore an
in-place code patch plus new code placed in free ROM (`0xB0xxxxxx`, executable in place), exactly
like `tools/fonts_en.py` does for the glyph mapper.

## Open items

1. Find the `AudioStream_Start` call site inside `0x80043DD0` and the register that holds the clip
   number — that is the only argument the hook needs. Progress: `func_80043CE8` is the wrapper
   (`jal func_8004D300` with `$a0 = 1`, the stream channel, and three spilled arguments, i.e.
   `AudioStream_Start(chan, seq, ...)`). `Audio_UpdateBattleAudioFrame` calls it twice
   (`0x80043F10`, `0x80043F68`), which is the same shape as Stadium 1's
   `AudioStream_Start(1, seq, 0x7E, 0); Subtitles_OnClip(clip);`. Hooking the wrapper covers every
   announcer start — battles, movies and cutscenes — so the next step is to identify which spilt
   argument is the clip and where the clip queue lives.
2. Runtime state: the clip number, its start time and the hold counter (3 words of RAM). Zero has no
   `gHackBss` equivalent yet; candidates are an unused field of the stage context, or the tail of the
   main pool. If Zero already keeps "current announcer clip" in a global, the state becomes
   stateless and only the hold counter is needed.
3. Options toggle: Stadium 1 has a `SUBTITLES` row in Options backed by `Save_GetSubtitles`. Zero's
   Options screen has no such row, so v1 draws whenever the option word's spare bit is set, and
   defaults to on.
4. Line data: `text/announcer.json` maps clip number to the Japanese line and its English
   translation; the page markers have to be re-timed against the English reading speed.
5. The movies and 3D cutscenes use the same stream API, so the same hook covers them once the clip
   ranges are known.
