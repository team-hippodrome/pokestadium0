# Audio driver (fragment000)

Zero's audio code at 0x81107390-0x811155BF is Nintendo's sequenced-audio driver, the one whose
original function names are `Nas_*`/`Nap_*` (the OoT decomp keeps them in "original name:"
comments). The same driver ships in SM64 (EU and Shindou) and in OoT and MM. Zero's copy sits
between SM64 Shindou and OoT. The comments used to call it "Zelda-style"; it is the same driver
library, not something modeled on Zelda.

[audio-driver-oot-map.tsv](audio-driver-oot-map.tsv) lists every function with its OoT counterpart,
original name, SM64 Shindou name where it helps, a confidence and the evidence.

## How the mapping was made

- Function order. Zero's functions follow OoT's `synthesis.c`, `heap.c`, `load.c`, `thread.c`,
  `os.c`, `playback.c`, `effects.c` and `seqplayer.c` in order. Where OoT added functions, Zero
  skips them and the order picks up again.
- Call graph. For each function, the driver functions it calls (`jal` targets in the built ELF)
  were compared with the calls in the OoT body. 151 of 204 match exactly. The rest differ only
  where OoT added features (external pool, synthetic waves, sound effects, Haas effect), split or
  inlined a helper, or wraps libultra (`Audio_InvalDCache`). Those count as `high`. Five functions
  whose differences are not explained this simply are `medium`. Functions with no counterpart are
  `none`.
- Bodies. Strong fingerprints include AudioHeap_ComputeFilterCoefficients (the 262159.0f seeds and
  the out/tmp bug of OoT func_800DF1D8), AudioPlayback_NoteSetResamplingRate (the 2.0f split, the
  1.99998f and 3.99996f clamps and the 32768.0f scale) and AudioEffects_UpdateAdsr (the envelope
  commands, the 128-update sustain countdown and the 0.00001f cutoff).

## Differences that matter

- Reverbs are indexed, as in Shindou: `AudioSynth_LoadRingBufferPart(cmd, ..., reverbIndex)`.
- Zero downsamples a reverb only when `downsampleRate >= 3` (`slti 3` at 0x811073C4). OoT uses
  `>= 2`, and Zero has no second ring buffer, filter or comb filter.
- There are two sample-cache allocators (temporary and persistent), as in Shindou. OoT merged them.
- AudioLoad_AsyncLoadSeqFonts (Shindou `func_sh_802f3158`) has no OoT counterpart.
- 0x811155A0 onward is Zero's own layer that queues audio thread commands (OoT `AUDIOCMD_OP_*`
  numbering: 0xF1 mute, 0xF2 unmute, 0x06 channel IO, 0x08 channel mute, 0x82 init sequence
  player, 0xF8 stop commands). 0x81115818 onward is the GB APU emulator and is not part of the driver.

Names follow OoT, using the file prefixes this repo already had (`AudioPlayback_`, `AudioEffects_`,
which are MM's), and MM's name where OoT leaves a function unnamed.
