/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/audio_loop_point.c, src/controller.c, src/dp_intro.c. */

#include "global.h"
#include <PR/os_internal_reg.h>
#include "dp_intro.h"
#include "asset_archive.h"
#include "crash_screen.h"
#include "game_state.h"
#include "profiler.h"
#include "stage_loader.h"
extern u64 F3DEX2_data_bin[];
extern s32 D_800733F0;
extern u64 D_80087B88[0x100 / sizeof(u64)];
extern u64 D_80087C88[0x408 / sizeof(u64)];
extern u64 D_80088090[0xC08 / sizeof(u64)];
extern u64 D_80088C98[0x20000 / sizeof(u64)];
void Display_ClearFramebufferLine(u16 color);
void Display_SetBufferConfig(DisplayFrame* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);

#include "libnumus/player.h"

#include "global.h"
extern Controller* gPlayer1Controller;
extern Controller* gPlayer2Controller;
extern Controller* gPlayer3Controller;
extern Controller* gPlayer4Controller;
extern Controller gControllers[4];
extern OSMesgQueue gSIEventMesgQueue;
extern u8 gControllerBits;
extern u8 gEepromProbe;
extern OSContStatus gControllerStatuses[4];
extern OSContPad gControllerPads[4];
extern OSMesg gSIEventMesgBuf[1];
extern OSMesg gEepromMesgBuf[1];
extern OSMesgQueue gEepromMesgQueue;

#include "m2c_macros.h"

void DisplayTask_Initialize(SchedTask* arg0);
void DisplayTask_Submit(SchedTask* arg0, DisplayFrame* arg1, s32 arg2);
u16 Display_GetFramebufferClearColor(void);
void Display_WaitForCompletion(void);
void Display_QueueFramebufferRequest(void* arg0);
void Display_WaitForFrames(s32 arg0);
void Display_SetBufferConfig(DisplayFrame* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);
u32 Audio_GetSpecialSequenceState(void);
u8 Cont_GetControllerBits(void);

/** Initializes a graphics task. */
void DisplayTask_Initialize(SchedTask* arg0) {
    arg0->task.t.type = M_GFXTASK;
    arg0->task.t.flags = 0;
    arg0->task.t.ucode_boot = D_80087B88;
    arg0->task.t.ucode_boot_size = 0x100;
    arg0->task.t.ucode = _binary_assets_us_F3DEX2_bin_start;
    arg0->task.t.ucode_data = F3DEX2_data_bin;
    arg0->task.t.ucode_size = 0x1000;
    arg0->task.t.ucode_data_size = 0x800;
    arg0->task.t.dram_stack = (void*)ALIGN16((uintptr_t)D_80087C88);
    arg0->task.t.dram_stack_size = 0x400;
    arg0->task.t.yield_data_ptr = (void*)ALIGN16((uintptr_t)D_80088090);
    arg0->task.t.yield_data_size = 0xC00;
    arg0->task.t.output_buff = (D_80088C98);
    arg0->task.t.output_buff_size = (D_80088C98 + (0x20000 / sizeof(u64)));
    osCreateMesgQueue(&arg0->queue, &arg0->mesg, 1);
}

/** Fills in a graphics task from a display list buffer and submits it. */
void DisplayTask_Submit(SchedTask* arg0, DisplayFrame* arg1, s32 arg2) {
    arg0->task.t.data_ptr = (void*)(uintptr_t)arg1->dlist;
    arg0->task.t.data_size = (u32)arg1->dlistSize;
    Sched_SubmitTask(arg0, arg2);
}

extern u8 D_8005F664[][2];
extern OSViMode D_80077F40[];
/**
 * Selects the VI mode from the D_8005F664 table (indices arg0, arg1) and turns on
 * dither filter and divot, gamma off.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening.
 * @unverified Name and comment guessed from the code.
 */
M2C_UNK DpIntro_SetViMode(s8 arg0, s8 arg1) {
    osViSetMode(&D_80077F40[D_8005F664[arg0][arg1]]);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
    osViSetSpecialFeatures(OS_VI_DIVOT_ON);
}

void func_800012AC(DisplayFrame* arg0) {
    if (arg0 == NULL) {
        D_800870D0.requestFrame.dlist = 0;
        D_800870D0.requestFrame.dlistSize = 0;
        D_800870D0.requestFrame.framebuffer = 0;
        D_800870D0.requestFrame.hiRes = D_800870D0.renderFrame.hiRes;
        D_800870D0.requestFrame.antiAlias = D_800870D0.renderFrame.antiAlias;
        D_800870D0.requestFrame.retracesPerFrame = D_800870D0.renderFrame.retracesPerFrame;
        return;
    }
    D_800870D0.requestFrame.hiRes = arg0->hiRes;
    D_800870D0.requestFrame.antiAlias = arg0->antiAlias;
    D_800870D0.requestFrame.retracesPerFrame = arg0->retracesPerFrame;
    D_800870D0.requestFrame.dlist = arg0->dlist;
    D_800870D0.requestFrame.dlistSize = arg0->dlistSize;
    D_800870D0.requestFrame.framebuffer = arg0->framebuffer;
    D_800870D0.requestFrame.renderTargetIndex = arg0->renderTargetIndex;
}

void func_8000460C(void*);
void func_80004920(void*);
void func_8000494C(void*);
M2C_UNK DpIntro_SetViMode(s8, s8);

/**
 * Processes one frame in the display worker: builds and submits its graphics
 * task.
 */
void DisplayWorker_ProcessFrame(void) {
    s32 i;
    s32 sp20 = 0;

    if (D_800870D0.renderFrame.dlist != 0) {
        func_8000460C(&D_800870D0.task);
    }

    if ((D_800870D0.requestFrame.dlist != 0) && (D_800870D0.shownFrame.framebuffer != D_800870D0.requestFrame.framebuffer) && (D_800870D0.shownFrame.renderTargetIndex != D_800870D0.requestFrame.renderTargetIndex)) {
        DisplayTask_Submit(&D_800870D0.task, &D_800870D0.requestFrame, 1);
        sp20 = 1;
    }

    for (i = 1; i < D_800870D0.shownFrame.retracesPerFrame; i++) {
        func_80004920(&D_800870D0.client);
    }

    while (D_800870D0.client.queue.validCount > 0) {
        func_8000494C(&D_800870D0.client);
    }

    if (D_800870D0.renderFrame.framebuffer != NULL) {
        osViSwapBuffer(D_800870D0.renderFrame.framebuffer->img_p);
        osViRepeatLine(0);
        if ((D_800870D0.renderFrame.hiRes != D_800870D0.shownFrame.hiRes) || (D_800870D0.renderFrame.antiAlias != D_800870D0.shownFrame.antiAlias)) {
            DpIntro_SetViMode((s8)D_800870D0.renderFrame.hiRes, (s8)D_800870D0.renderFrame.antiAlias);
        }
        osViBlack(0U);
        crash_screen_set_draw_info((u16*)D_800870D0.renderFrame.framebuffer->img_p, D_800870D0.renderFrame.framebuffer->width, 0x10);
    } else {
        osViRepeatLine(1);
        osViSwapBuffer(D_800870D0.lineImage->img_p);
        if ((D_800870D0.renderFrame.hiRes != D_800870D0.shownFrame.hiRes) || (D_800870D0.renderFrame.antiAlias != D_800870D0.shownFrame.antiAlias)) {
            DpIntro_SetViMode((s8)D_800870D0.renderFrame.hiRes, (s8)D_800870D0.renderFrame.antiAlias);
        }
    }

    if ((sp20 == 0) && (D_800870D0.requestFrame.dlist != 0)) {
        DisplayTask_Submit(&D_800870D0.task, &D_800870D0.requestFrame, 0);
    }

    D_800870D0.shownFrame = D_800870D0.renderFrame;
    D_800870D0.renderFrame = D_800870D0.requestFrame;
    profiler_log_thread5_time(THREAD5_END);
    func_80004920(&D_800870D0.client);
}

void func_80001558(void) {
    s32 width;
    s32 i;
    s32 j;
    u64* p;

    if (D_800870D0.nmiClearStep < 15) {
        if (D_800870D0.shownFrame.hiRes == 0) {
            width = 80;
        } else {
            width = 320;
        }
        if (D_800870D0.shownFrame.framebuffer != NULL) {
            p = (u64*)D_800870D0.shownFrame.framebuffer->img_p;
            p += width * D_800870D0.nmiClearStep;
            // clang-format off
            for (i = 0; i < 16; i++) { for (j = 0; j < width; j++) { *(p++) = 0; } p += width * 14; }
            // clang-format on
        } else {
            func_80052DC0(1, width);
        }
        D_800870D0.nmiClearStep++;
        func_8005C0A0();
    }
    func_80004920(&D_800870D0.client);
    while (D_800870D0.client.queue.validCount > 0) {
        func_8000494C(&D_800870D0.client);
    }
    func_80004920(&D_800870D0.client);
}

void func_800594D0(u32);
void func_80001A30(void*, u8, u8, u8, u8, s32, s32, s32);
void func_80004EA8(SchedClient*);
void func_80001140(void*);
void func_800081E0(s32);
s32 func_8004D1C0(OSMesgQueue*, OSMesg*, s32);
s32 func_8004CFB0(OSMesgQueue*, OSMesg, s32);
void func_800012AC(DisplayFrame* arg0);
void func_80001328(void);
void func_80001558(void);

/**
 * Seen in play (2026-11-13) ran at boot (console reset, then N64 logo, opening, title and main
 * menu).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void DisplayWorker_ThreadMain(UNUSED void* arg0) {
    OSMesg msg;

    func_800594D0(0x01000F00);
    func_80001A30(&D_800870D0.shownFrame, 0, 1, 2, 0xFF, 0, 0, 0);
    func_80001A30(&D_800870D0.renderFrame, 0, 1, 2, 0xFF, 0, 0, 0);
    func_800567E0(&D_800870D0.client.queue, D_800870D0.client.mesgBuf, 4);
    func_80004EA8(&D_800870D0.client);
    func_80001140(&D_800870D0.task);
    while (1) {
        if (D_800A9710.preNmiFrames > 0) {
            func_80001558();
            continue;
        }
        func_800081E0(0);
        D_800870D0.isWaitingForRequest = 1;
        func_8004D1C0(&D_800870D0.frameQueue, &msg, 1);
        D_800870D0.isWaitingForRequest = 0;
        func_800081E0(1);
        func_800081E0(2);
        func_800012AC(msg);
        func_80001328();
        func_8004CFB0(&D_800870D0.doneQueue, (OSMesg)0x444F4E45, 0);
    }
}

void DisplayWorker_ThreadMain(void*);

/** Creates the display worker thread. */
void DisplayWorker_Initialize(void) {
    osCreateThread(&D_800870D0.thread, 5, DisplayWorker_ThreadMain, NULL, D_800870D0.stack + sizeof(D_800870D0.stack), 0x28);
    osStartThread(&D_800870D0.thread);
    osCreateMesgQueue(&D_800870D0.frameQueue, &D_800870D0.frameMesgBuf, 1);
    osCreateMesgQueue(&D_800870D0.doneQueue, &D_800870D0.doneMesgBuf, 1);
    D_800870D0.nmiClearStep = 0;
    D_800870D0.isWaitingForRequest = 0;
    D_800870D0.lineImage = (struct unk_D_80068BB0*)GfxImage_Allocate(0, IMAGE_SIZE_BITS_16b, 0x280, 1, MEMORY_POOL_RIGHT);
    Display_ClearFramebufferLine(1);
    Dma_WriteChunks(&D_80087B88, 0xB0000B70, 0xB0000C70, 0);
}

/*
 * Display_ClearFramebufferLine (func_80001948)
 *
 * Writes `color` into 640 consecutive 16-bit entries starting at the image
 * pointer of the image object stored at D_800870D0.lineImage (the one-line,
 * 0x280-wide image allocated in the intro setup function just above). The
 * Stadium 1 version of this function ends with an osWritebackDCache call;
 * the ROM's code for this address has no such call, so none is written.
 * Matching note: the count is a signed local decremented in the loop
 * condition (`width-- > 0`), the form used by the Stadium 1 source.
 */
void Display_ClearFramebufferLine(u16 color) {
    s32 width = 640;
    u16* buf = (u16*)D_800870D0.lineImage->img_p;

    while (width-- > 0) {
        *(buf)++ = color;
    }
}

/** Returns the color the framebuffer is cleared to. */
u16 Display_GetFramebufferClearColor(void) {
    u16* ptr = (u16*)D_800870D0.lineImage->img_p;
    return *ptr;
}

/** Blocks until the queued frame has finished. */
void Display_WaitForCompletion(void) {
    osRecvMesg(&D_800870D0.doneQueue, NULL, 1);
}

/** Queues a frame request for the display worker. */
void Display_QueueFramebufferRequest(void* arg0) {
    osSendMesg(&D_800870D0.frameQueue, arg0, 0);
}

/** Waits for the given number of frames. */
void Display_WaitForFrames(s32 arg0) {
    while (arg0-- > 0) {
        Display_QueueFramebufferRequest(0);
        Display_WaitForCompletion();
    }
}

/** Sets the configuration of a display buffer entry. */
void Display_SetBufferConfig(DisplayFrame* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7) {
    arg0->hiRes = arg1;
    arg0->antiAlias = arg2;
    arg0->retracesPerFrame = arg3;
    arg0->renderTargetIndex = arg4;
    arg0->dlist = (Gfx*)arg5;
    arg0->dlistSize = (Gfx*)arg6;
    arg0->framebuffer = (struct unk_D_80068BB0*)(uintptr_t)arg7;
}

/** Returns the state of the special audio sequence. */
u32 Audio_GetSpecialSequenceState(void) {
    return D_80087B80;
}

M2C_UNK DpIntro_SetViMode(s8, s8);                      /* extern */

/**
 * Seen in play (2026-11-13) ran when quitting the GB player (C-Up menu, Quit game, Yes) back to the
 * main menu.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Display_ApplyPendingVideoMode(void) {
    DpIntro_SetViMode((s8)D_800870D0.shownFrame.hiRes, (s8)D_800870D0.shownFrame.antiAlias);
}


/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the Pokédex, the party screen,
 * the Lab list, Lab sort, registration, the Lab PC and Free Battle setup.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Display_IsFrameReady(void) {
    s32 var_v1;

    var_v1 = 1;
    if (D_800870D0.renderFrame.dlist != 0) {
        var_v1 = D_800870D0.task.queue.validCount > 0;
    }
    return var_v1;
}

/*
 * Retrieve the current controller bits.
 */
u8 Cont_GetControllerBits(void) {
    return gControllerBits;
}
