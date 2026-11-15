/* Declarations for src/gb_audio_render.c. */
#ifndef GB_AUDIO_RENDER_H
#define GB_AUDIO_RENDER_H

#include "global.h"

// gb_audio_render.c
void GbAudio_GenerateSamples(s16*, s32, u32, f32);
void GbAudio_QueueRegisterWrite(u16, u8, u16);
u8 GbAudio_GetRegisterValue(u16);
void func_80044BA8(u32, u8, u32);

#endif // GB_AUDIO_RENDER_H
