/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/crash_screen.c. */

#include "global.h"
#include "string.h"
#include <PR/os_internal_thread.h>
#include "stdarg.h"
#include "crash_screen.h"
#include "controller.h"
#include "memmap.h"
#include "stdarg.h"
extern CrashScreen gCrashScreen;
extern u8 gCrashScreenCharToGlyph[128];
extern u32 gCrashScreenFont[];
extern const char* gFaultCauses[18];
extern const char* gFPCSRFaultCauses[6];
extern u16 gCrashScreenUnlockInputs[];

void CrashScreen_DrawRect(s32 x, s32 y, s32 width, s32 height);
void CrashScreen_DrawGlyph(s32 x, s32 y, s32 glyph);
char* CrashScreen_CopyToBuf(char* buffer, const char* data, size_t size);
void CrashScreen_Printf(s32 x, s32 y, const char* fmt, ...);
void CrashScreen_Sleep(s32 ms);
void CrashScreen_PrintFpr(s32 x, s32 y, s32 regNum, void* addr);
void CrashScreen_PrintFpcsr(u32 fpcsr);
OSThread* CrashScreen_GetFaultedThread(void);
void CrashScreen_SetDrawInfo(u16* frameBufPtr, u16 width, u16 height);
void CrashScreen_Init(void);
void CrashScreen_PrintfWithBg(s16 x, s16 y, const char* fmt, ...);

void CrashScreen_ThreadEntry(UNUSED void* unused);

/** Fills a rectangle on the crash screen framebuffer. */
void CrashScreen_DrawRect(s32 x, s32 y, s32 width, s32 height) {
    u16* ptr;
    s32 i;
    s32 j;

    if (gCrashScreen.width == (0x140 * 2)) {
        x <<= 1;
        y <<= 1;
        width <<= 1;
        height <<= 1;
    }

    ptr = gCrashScreen.frameBuf + gCrashScreen.width * y + x;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            *ptr = ((*ptr & 0xE738) >> 2) | 1;
            ptr++;
        }

        ptr += gCrashScreen.width - width;
    }
}

/** Draws one font glyph on the crash screen. */
void CrashScreen_DrawGlyph(s32 x, s32 y, s32 glyph) {
    s32 shift = ((glyph % 5) * 6);
    const u32* data = &gCrashScreenFont[glyph / 5 * 7];
    s32 i;
    s32 j;

    if (gCrashScreen.width == SCREEN_WIDTH) {
        u16* ptr = gCrashScreen.frameBuf + (gCrashScreen.width) * y + x;

        for (i = 0; i < 7; i++) {
            u32 bit = 0x80000000U >> shift;
            u32 row_mask = *data++;

            for (j = 0; j < 6; j++) {
                *ptr++ = (bit & row_mask) ? 0xFFFF : 1;
                bit >>= 1;
            }

            ptr += gCrashScreen.width - 6;
        }
    } else if (gCrashScreen.width == (SCREEN_WIDTH * 2)) {
        u16* ptr = gCrashScreen.frameBuf + (y * 0x500) + (x * 2);

        for (i = 0; i < 7; i++) {
            u32 bit = 0x80000000U >> shift;
            u32 row_mask = *data++;

            for (j = 0; j < 6; j++) {
                u16 temp = (bit & row_mask) ? 0xFFFF : 1;

                ptr[0] = temp;
                ptr[1] = temp;
                ptr[(SCREEN_WIDTH * 2)] = temp;
                ptr[(SCREEN_WIDTH * 2) + 1] = temp;
                ptr += 2;
                bit >>= 1;
            }

            ptr += (0x9E8 / 2);
        }
    }
}

/** Copies bytes into a buffer and returns the pointer past them. */
char* CrashScreen_CopyToBuf(char* buffer, const char* data, size_t size) {
    return (char*)memcpy(buffer, data, size) + size;
}

/** Prints formatted text on the crash screen. */
void CrashScreen_Printf(s32 x, s32 y, const char* fmt, ...) {
    signed char* ptr;
    u32 glyph;
    s32 size;
    signed char buf[0x100];

    va_list args;
    va_start(args, fmt);

    size = _Printf(CrashScreen_CopyToBuf, (char*)buf, fmt, args);

    if (size > 0) {
        ptr = buf;

        while (size > 0) {

            glyph = gCrashScreenCharToGlyph[*ptr & 0x7f];

            if (glyph != 0xff) {
                CrashScreen_DrawGlyph(x, y, glyph);
            }

            size--;

            ptr++;
            x += 6;
        }
    }

    va_end(args);
}

/** Busy-waits for a number of milliseconds. */
void CrashScreen_Sleep(s32 ms) {
    u64 cycles = OS_USEC_TO_CYCLES(ms * 1000LL); // why not just do OS_NSEC_TO_CYCLES and not multiply by 1000LL?

    osSetTime(0);
    while (osGetTime() < cycles) {}
}

/** Prints a floating-point register on the crash screen. */
void CrashScreen_PrintFpr(s32 x, s32 y, s32 reg_num, void* addr) {
    u32 bits;
    s32 exponent;

    bits = *(u32*)addr;
    exponent = ((bits & 0x7f800000U) >> 0x17) - 0x7f;
    if ((exponent >= -0x7e && exponent <= 0x7f) || bits == 0) {
        CrashScreen_Printf(x, y, "F%02d:%+.3e", reg_num, *(f32*)addr);
    } else {
        CrashScreen_Printf(x, y, "F%02d:---------", reg_num);
    }
}

/**
 * Prints the floating-point control and status register and its flags on the
 * crash screen.
 */
void CrashScreen_PrintFpcsr(u32 fpcsr) {
    s32 i;
    u32 bit = 1 << 17;

    CrashScreen_Printf(30, 155, "FPCSR:%08XH", fpcsr);

    for (i = 0; i < 6; i++) {
        if (fpcsr & bit) {
            CrashScreen_Printf(132, 155, "(%s)", gFPCSRFaultCauses[i]);
            break;
        }
        bit >>= 1;
    }
}

/** Draws the crash screen for a faulted thread. */
void CrashScreen_Draw(OSThread* faulted_thread) {
    s16 cause_index;
    __OSThreadContext* ctx;
    u32 ret;

    ctx = &faulted_thread->context;
    cause_index = ((faulted_thread->context.cause >> 2) & 0x1F);

    if (cause_index == 23) {
        cause_index = 16;
    }

    if (cause_index == 31) {
        cause_index = 17;
    }

    osWritebackDCacheAll();

    CrashScreen_DrawRect(25, 20, 270, 25);
    CrashScreen_Printf(30, 25, "THREAD:%d  (%s)", faulted_thread->id, gFaultCauses[cause_index]);
    CrashScreen_Printf(30, 35, "PC:%08XH   SR:%08XH   VA:%08XH", ctx->pc, ctx->sr, ctx->badvaddr);

    CrashScreen_Sleep(2000);

    osViBlack(0);
    osViRepeatLine(0);
    osViSwapBuffer(gCrashScreen.frameBuf);

    CrashScreen_DrawRect(25, 45, 270, 185);

    CrashScreen_Printf(30, 50, "AT:%08XH   V0:%08XH   V1:%08XH", (u32)ctx->at, (u32)ctx->v0, (u32)ctx->v1);
    CrashScreen_Printf(30, 60, "A0:%08XH   A1:%08XH   A2:%08XH", (u32)ctx->a0, (u32)ctx->a1, (u32)ctx->a2);
    CrashScreen_Printf(30, 70, "A3:%08XH   T0:%08XH   T1:%08XH", (u32)ctx->a3, (u32)ctx->t0, (u32)ctx->t1);
    CrashScreen_Printf(30, 80, "T2:%08XH   T3:%08XH   T4:%08XH", (u32)ctx->t2, (u32)ctx->t3, (u32)ctx->t4);
    CrashScreen_Printf(30, 90, "T5:%08XH   T6:%08XH   T7:%08XH", (u32)ctx->t5, (u32)ctx->t6, (u32)ctx->t7);
    CrashScreen_Printf(30, 100, "S0:%08XH   S1:%08XH   S2:%08XH", (u32)ctx->s0, (u32)ctx->s1, (u32)ctx->s2);
    CrashScreen_Printf(30, 110, "S3:%08XH   S4:%08XH   S5:%08XH", (u32)ctx->s3, (u32)ctx->s4, (u32)ctx->s5);
    CrashScreen_Printf(30, 120, "S6:%08XH   S7:%08XH   T8:%08XH", (u32)ctx->s6, (u32)ctx->s7, (u32)ctx->t8);
    CrashScreen_Printf(30, 130, "T9:%08XH   GP:%08XH   SP:%08XH", (u32)ctx->t9, (u32)ctx->gp, (u32)ctx->sp);
    CrashScreen_Printf(30, 140, "S8:%08XH   RA:%08XH", (u32)ctx->s8, (u32)ctx->ra);

    CrashScreen_PrintFpcsr(ctx->fpcsr);

    CrashScreen_PrintFpr(30, 170, 0, &ctx->fp0.f.f_even);
    CrashScreen_PrintFpr(120, 170, 2, &ctx->fp2.f.f_even);
    CrashScreen_PrintFpr(210, 170, 4, &ctx->fp4.f.f_even);
    CrashScreen_PrintFpr(30, 180, 6, &ctx->fp6.f.f_even);
    CrashScreen_PrintFpr(120, 180, 8, &ctx->fp8.f.f_even);
    CrashScreen_PrintFpr(210, 180, 10, &ctx->fp10.f.f_even);
    CrashScreen_PrintFpr(30, 190, 12, &ctx->fp12.f.f_even);
    CrashScreen_PrintFpr(120, 190, 14, &ctx->fp14.f.f_even);
    CrashScreen_PrintFpr(210, 190, 16, &ctx->fp16.f.f_even);
    CrashScreen_PrintFpr(30, 200, 18, &ctx->fp18.f.f_even);
    CrashScreen_PrintFpr(120, 200, 20, &ctx->fp20.f.f_even);
    CrashScreen_PrintFpr(210, 200, 22, &ctx->fp22.f.f_even);
    CrashScreen_PrintFpr(30, 210, 24, &ctx->fp24.f.f_even);
    CrashScreen_PrintFpr(120, 210, 26, &ctx->fp26.f.f_even);
    CrashScreen_PrintFpr(210, 210, 28, &ctx->fp28.f.f_even);
    CrashScreen_PrintFpr(30, 220, 30, &ctx->fp30.f.f_even);

    ret = Memmap_GetLoadedFragmentVaddr(ctx->pc);
    if (ret != 0) {
        CrashScreen_Printf(120, 220, "F-PC:%08XH", ret - 0x20);
    }

    ret = Memmap_GetLoadedFragmentVaddr((u32)ctx->ra);
    if (ret != 0) {
        CrashScreen_Printf(210, 220, "F-RA:%08XH", ret - 0x20);
    }

}

/** Returns the thread that faulted. */
OSThread* CrashScreen_GetFaultedThread(void) {
    OSThread* thread = __osGetActiveQueue();

    while (thread->priority != -1) {
        if (thread->priority > 0 && thread->priority < 0x7F && (thread->flags & 3)) {
            return thread;
        }

        thread = thread->tlnext;
    }

    return NULL;
}

/*
 * CrashScreen_ThreadEntry  (owner func_80007F74)
 *
 * Entry point of the crash-handler thread.  It asks the OS to deliver CPU
 * breakpoint events (as message 1) and CPU fault events (as message 2) to
 * the crash screen's message queue, then sleeps on that queue.  Each time a
 * message arrives it looks for a thread that has faulted; once one is
 * found it stops that thread, waits until player 1 has entered the
 * 10-press unlock button sequence (CrashScreen_WaitForButtonCombo),
 * draws the crash screen (CrashScreen_Draw), and then spins forever.
 */
void CrashScreen_ThreadEntry(UNUSED void* unused) {
    OSMesg mesg;
    OSThread* faulted_thread;

    osSetEventMesg(OS_EVENT_CPU_BREAK, &gCrashScreen.queue, (OSMesg)1);
    osSetEventMesg(OS_EVENT_FAULT, &gCrashScreen.queue, (OSMesg)2);

    do {
        /* Block until the OS reports a break or a fault... */
        osRecvMesg(&gCrashScreen.queue, &mesg, 1);
        /* ...then see whether some thread really has faulted. */
        faulted_thread = CrashScreen_GetFaultedThread();
    } while (faulted_thread == NULL);

    osStopThread(faulted_thread);
    CrashScreen_WaitForButtonCombo();
    CrashScreen_Draw(faulted_thread);

    /* Nothing more to do; keep this thread alive on the crash screen. */
    while (TRUE) {}
}

/** Sets the framebuffer pointer and size used by the crash screen. */
void CrashScreen_SetDrawInfo(u16* frame_buf_ptr, u16 width, u16 height) {
    gCrashScreen.frameBuf = (u16*)((uintptr_t)frame_buf_ptr | 0xA0000000);
    gCrashScreen.width = width;
    gCrashScreen.height = height;
}

/** Initializes the crash screen's framebuffer. */
void CrashScreen_Init(void) {
    gCrashScreen.frameBuf = (u16*)(uintptr_t)((osMemSize | 0xA0000000) - ((SCREEN_WIDTH * SCREEN_HEIGHT) * 2));
    gCrashScreen.width = SCREEN_WIDTH;
    gCrashScreen.height = 16;
    osCreateMesgQueue(&gCrashScreen.queue, &gCrashScreen.mesg, 1);
    osCreateThread(&gCrashScreen.thread, 2, CrashScreen_ThreadEntry, NULL,
                   gCrashScreen.stack + sizeof(gCrashScreen.stack), 128);
    osStartThread(&gCrashScreen.thread);
}

/** Prints formatted text on the crash screen over a background. */
void CrashScreen_PrintfWithBg(s16 x, s16 y, const char* fmt, ...) {
    signed char* ptr;
    u32 glyph;
    s32 size;
    signed char buf[0x100];
    va_list args;

    va_start(args, fmt);

    size = _Printf(CrashScreen_CopyToBuf, (char*)buf, fmt, args);

    if (size > 0) {
        CrashScreen_DrawRect(x - 6, y - 6, (size + 2) * 6, 19);
        ptr = buf;

        while (size > 0) {
            glyph = gCrashScreenCharToGlyph[*ptr & 0x7F];

            if (glyph != 0xFF) {
                CrashScreen_DrawGlyph(x, y, glyph);
            }

            ptr++;
            size--;
            x += 6;
        }
    }

    va_end(args);
}
