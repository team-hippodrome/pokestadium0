/* Declarations for src/dp_intro.c. */
#ifndef DP_INTRO_H
#define DP_INTRO_H

#include "global.h"

struct GfxImage;

// A frame request for the display worker (Display_QueueFramebufferRequest), filled by StageLoader_BeginFrame.
typedef struct DisplayFrame {
    /* 0x00 */ u8 retracesPerFrame; // @unverified: StageContext.retracesPerFrame; DisplayWorker_ProcessFrame waits this many retraces
    /* 0x01 */ u8 hiRes; // @unverified: StageContext.zoom; row of the VI mode table D_8005F664 (0 low resolution, 1 high)
    /* 0x02 */ u8 antiAlias; // @unverified: StageContext.antiAlias; column of the VI mode table D_8005F664 (1 anti-aliased)
    /* 0x03 */ u8 renderTargetIndex; // @unverified: StageContext.renderTargetIndex; a request for the shown target is not rendered
    /* 0x04 */ Gfx* dlist; // @unverified: start of the display list, the task's data_ptr
    /* 0x08 */ Gfx* dlistSize; // @unverified: size in bytes of the display list (Gfx_GetDisplayListRange), the task's data_size
    /* 0x0C */ struct GfxImage* framebuffer; // @unverified: passed to osViSwapBuffer when the frame is shown
} DisplayFrame; // size = 0x10

#include "scheduler.h"

// The display worker thread (D_800870D0): renders a requested frame and shows the one before.
typedef struct DisplayWorker {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ u8 stack[0x800]; // @unverified: osCreateThread stack top in the display init
    /* 0x9B0 */ struct GfxImage* lineImage; // @unverified: one 640-pixel line image (Display_ClearFramebufferLine); also the top of stack
    /* 0x9B4 */ OSMesg frameMesgBuf; // @unverified: buffer of the frame request queue
    /* 0x9B8 */ OSMesg doneMesgBuf; // @unverified: buffer of the frame done queue
    /* 0x9BC */ OSMesgQueue frameQueue; // @unverified: gets DisplayFrame requests (Display_QueueFramebufferRequest)
    /* 0x9D4 */ OSMesgQueue doneQueue; // @unverified: the worker sends 'DONE' after each request (Display_WaitForCompletion)
    /* 0x9EC */ SchedClient client; // @unverified: retrace client registered in DisplayWorker_ThreadMain
    /* 0xA18 */ SchedTask task; // @unverified: the graphics task (DisplayTask_Initialize, DisplayTask_Submit)
    /* 0xA80 */ s16 nmiClearStep; // @unverified: func_80001558 clears 16 lines of the shown framebuffer per step after a pre-NMI, 15 steps
    /* 0xA82 */ u8 isWaitingForRequest; // @unverified: 1 while DisplayWorker_ThreadMain blocks on frameQueue
    /* 0xA83 */ u8 padA83;
    /* 0xA84 */ DisplayFrame requestFrame; // @unverified: the latest request (func_800012AC), rendered next
    /* 0xA94 */ DisplayFrame renderFrame; // @unverified: rendered last frame, shown in this one
    /* 0xAA4 */ DisplayFrame shownFrame; // @unverified: on screen now
} DisplayWorker; // size = 0xAB4

extern DisplayWorker D_800870D0;

// dp_intro.c
void DisplayTask_Initialize(SchedTask* arg0);
void DisplayTask_Submit(SchedTask* arg0, DisplayFrame* arg1, s32 arg2);
void DisplayWorker_ProcessFrame(void);
void DisplayWorker_ThreadMain(UNUSED void* arg);
void DisplayWorker_Initialize(void);
void Display_ClearFramebufferLine(u16 color);
u16 Display_GetFramebufferClearColor(void);
void Display_WaitForCompletion(void);
void Display_QueueFramebufferRequest(void* arg0);
void Display_WaitForFrames(s32 arg0);
void Display_SetBufferConfig(DisplayFrame* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);
void Display_ApplyPendingVideoMode(void);
s32 Display_IsFrameReady(void);
u32 Audio_GetSpecialSequenceState(void);
u8 Cont_GetControllerBits(void);

#endif // DP_INTRO_H
