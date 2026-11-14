/* Declarations for src/audio_manager.c. */
#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "global.h"

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/33FE0.c
 * src/3D140.c
 * src/3D140_2.c
 */

typedef struct AMDMABuffer {
    /* 0x00 */ ALLink node;
    /* 0x08 */ u32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ char* ptr;
} AMDMABuffer;

typedef struct AMDMAState {
    /* 0x00 */ u8 initialized;
    /* 0x04 */ AMDMABuffer* firstUsed;
    /* 0x08 */ AMDMABuffer* firstFree;
} AMDMAState;

typedef struct unk_D_80078548 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} unk_D_80078548;

typedef struct amConfig {
    /* 0x00 */ u32 outputRate;
    /* 0x04 */ u32 framesPerField;
    /* 0x08 */ u32 maxACMDSize;
} amConfig; // size = 0xC

extern s32 mus_active_fade_handle;

extern f32 mus_fade_start_volume;

extern u8 mus_fade_target_volume;

extern f32 mus_fade_step_rate;

extern u8 mus_sound_effect_blocked;

// audio_manager.c
void amCreateAudioMgr(ALSynConfig* c, amConfig* amc, u32 num_dma_buffers, s32 arg3, s32 arg4);
void __clearAudioDMA(void);
void Cry_PlayFromPokedex(s32);
s32 Cry_IsPlaying(void);
s32 Audio_SetEnabled(s32);

// functions defined in assembly
OSTask* Audio_CreateFrameTask(OSTask*);
void AudioFrameUpdate(s32 arg0);

#endif // AUDIO_MANAGER_H
