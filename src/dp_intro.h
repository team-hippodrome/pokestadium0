/* Declarations for src/dp_intro.c. */
#ifndef DP_INTRO_H
#define DP_INTRO_H

#include "global.h"

struct GfxImage;

typedef struct UnkArray4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ struct GfxImage* unk_0C;
} UnkArray4; // size = 0x10

#include "scheduler.h"

// dp_intro.c
void DisplayTask_Initialize(UnkStruct80001380* arg0);
void DisplayTask_Submit(UnkStruct80001380* arg0, struct UnkArray4* arg1, s32 arg2);
void DisplayWorker_ProcessFrame(void);
void DisplayWorker_ThreadMain(UNUSED void* arg);
void DisplayWorker_Initialize(void);
void Display_ClearFramebufferLine(u16 color);
u16 Display_GetFramebufferClearColor(void);
void Display_WaitForCompletion(void);
void Display_QueueFramebufferRequest(void* arg0);
void Display_WaitForFrames(s32 arg0);
void Display_SetBufferConfig(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);
void Display_ApplyPendingVideoMode(void);
s32 Display_IsFrameReady(void);
u32 Audio_GetSpecialSequenceState(void);
u8 Cont_GetControllerBits(void);

#endif // DP_INTRO_H
