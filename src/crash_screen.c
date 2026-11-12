/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/crash_screen.c. */

#include "global.h"
#include "string.h"
#include <PR/os_internal_thread.h>
#include "stdarg.h"
#include "crash_screen.h"
#include "memmap.h"
#include "controller.h"
#include "stdarg.h"
extern CrashScreen gCrashScreen;
extern u8 gCrashScreenCharToGlyph[128];
extern u32 gCrashScreenFont[];
extern const char* gFaultCauses[18];
extern const char* gFPCSRFaultCauses[6];
extern u16 gCrashScreenUnlockInputs[];

void crash_screen_draw_rect(s32 x, s32 y, s32 width, s32 height);
void crash_screen_draw_glyph(s32 x, s32 y, s32 glyph);
char* crash_screen_copy_to_buf(char* buffer, const char* data, size_t size);
void crash_screen_printf(s32 x, s32 y, const char* fmt, ...);
void crash_screen_sleep(s32 ms);
void crash_screen_print_fpr(s32 x, s32 y, s32 regNum, void* addr);
void crash_screen_print_fpcsr(u32 fpcsr);
OSThread* crash_screen_get_faulted_thread(void);
void crash_screen_set_draw_info(u16* frameBufPtr, u16 width, u16 height);
void crash_screen_init(void);
void crash_screen_printf_with_bg(s16 x, s16 y, const char* fmt, ...);

void crash_screen_thread_entry(UNUSED void* unused);

void crash_screen_draw_rect(s32 x, s32 y, s32 width, s32 height) {
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

void crash_screen_draw_glyph(s32 x, s32 y, s32 glyph) {
    s32 shift = ((glyph % 5) * 6);
    const u32* data = &gCrashScreenFont[glyph / 5 * 7];
    s32 i;
    s32 j;

    if (gCrashScreen.width == SCREEN_WIDTH) {
        u16* ptr = gCrashScreen.frameBuf + (gCrashScreen.width) * y + x;

        for (i = 0; i < 7; i++) {
            u32 bit = 0x80000000U >> shift;
            u32 rowMask = *data++;

            for (j = 0; j < 6; j++) {
                *ptr++ = (bit & rowMask) ? 0xFFFF : 1;
                bit >>= 1;
            }

            ptr += gCrashScreen.width - 6;
        }
    } else if (gCrashScreen.width == (SCREEN_WIDTH * 2)) {
        u16* ptr = gCrashScreen.frameBuf + (y * 0x500) + (x * 2);

        for (i = 0; i < 7; i++) {
            u32 bit = 0x80000000U >> shift;
            u32 rowMask = *data++;

            for (j = 0; j < 6; j++) {
                u16 temp = (bit & rowMask) ? 0xFFFF : 1;

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

char* crash_screen_copy_to_buf(char* buffer, const char* data, size_t size) {
    return (char*)memcpy(buffer, data, size) + size;
}

void crash_screen_printf(s32 x, s32 y, const char* fmt, ...) {
    signed char* ptr;
    u32 glyph;
    s32 size;
    signed char buf[0x100];

    va_list args;
    va_start(args, fmt);

    size = _Printf(crash_screen_copy_to_buf, (char*)buf, fmt, args);

    if (size > 0) {
        ptr = buf;

        while (size > 0) {

            glyph = gCrashScreenCharToGlyph[*ptr & 0x7f];

            if (glyph != 0xff) {
                crash_screen_draw_glyph(x, y, glyph);
            }

            size--;

            ptr++;
            x += 6;
        }
    }

    va_end(args);
}

void crash_screen_sleep(s32 ms) {
    u64 cycles = OS_USEC_TO_CYCLES(ms * 1000LL); // why not just do OS_NSEC_TO_CYCLES and not multiply by 1000LL?

    osSetTime(0);
    while (osGetTime() < cycles) {}
}

void crash_screen_print_fpr(s32 x, s32 y, s32 reg_num, void* addr) {
    u32 bits;
    s32 exponent;

    bits = *(u32*)addr;
    exponent = ((bits & 0x7f800000U) >> 0x17) - 0x7f;
    if ((exponent >= -0x7e && exponent <= 0x7f) || bits == 0) {
        crash_screen_printf(x, y, "F%02d:%+.3e", reg_num, *(f32*)addr);
    } else {
        crash_screen_printf(x, y, "F%02d:---------", reg_num);
    }
}

void crash_screen_print_fpcsr(u32 fpcsr) {
    s32 i;
    u32 bit = 1 << 17;

    crash_screen_printf(30, 155, "FPCSR:%08XH", fpcsr);

    for (i = 0; i < 6; i++) {
        if (fpcsr & bit) {
            crash_screen_printf(132, 155, "(%s)", gFPCSRFaultCauses[i]);
            break;
        }
        bit >>= 1;
    }
}

void crash_screen_draw(OSThread* faulted_thread) {
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

    crash_screen_draw_rect(25, 20, 270, 25);
    crash_screen_printf(30, 25, "THREAD:%d  (%s)", faulted_thread->id, gFaultCauses[cause_index]);
    crash_screen_printf(30, 35, "PC:%08XH   SR:%08XH   VA:%08XH", ctx->pc, ctx->sr, ctx->badvaddr);

    crash_screen_sleep(2000);

    osViBlack(0);
    osViRepeatLine(0);
    osViSwapBuffer(gCrashScreen.frameBuf);

    crash_screen_draw_rect(25, 45, 270, 185);

    crash_screen_printf(30, 50, "AT:%08XH   V0:%08XH   V1:%08XH", (u32)ctx->at, (u32)ctx->v0, (u32)ctx->v1);
    crash_screen_printf(30, 60, "A0:%08XH   A1:%08XH   A2:%08XH", (u32)ctx->a0, (u32)ctx->a1, (u32)ctx->a2);
    crash_screen_printf(30, 70, "A3:%08XH   T0:%08XH   T1:%08XH", (u32)ctx->a3, (u32)ctx->t0, (u32)ctx->t1);
    crash_screen_printf(30, 80, "T2:%08XH   T3:%08XH   T4:%08XH", (u32)ctx->t2, (u32)ctx->t3, (u32)ctx->t4);
    crash_screen_printf(30, 90, "T5:%08XH   T6:%08XH   T7:%08XH", (u32)ctx->t5, (u32)ctx->t6, (u32)ctx->t7);
    crash_screen_printf(30, 100, "S0:%08XH   S1:%08XH   S2:%08XH", (u32)ctx->s0, (u32)ctx->s1, (u32)ctx->s2);
    crash_screen_printf(30, 110, "S3:%08XH   S4:%08XH   S5:%08XH", (u32)ctx->s3, (u32)ctx->s4, (u32)ctx->s5);
    crash_screen_printf(30, 120, "S6:%08XH   S7:%08XH   T8:%08XH", (u32)ctx->s6, (u32)ctx->s7, (u32)ctx->t8);
    crash_screen_printf(30, 130, "T9:%08XH   GP:%08XH   SP:%08XH", (u32)ctx->t9, (u32)ctx->gp, (u32)ctx->sp);
    crash_screen_printf(30, 140, "S8:%08XH   RA:%08XH", (u32)ctx->s8, (u32)ctx->ra);

    crash_screen_print_fpcsr(ctx->fpcsr);

    crash_screen_print_fpr(30, 170, 0, &ctx->fp0.f.f_even);
    crash_screen_print_fpr(120, 170, 2, &ctx->fp2.f.f_even);
    crash_screen_print_fpr(210, 170, 4, &ctx->fp4.f.f_even);
    crash_screen_print_fpr(30, 180, 6, &ctx->fp6.f.f_even);
    crash_screen_print_fpr(120, 180, 8, &ctx->fp8.f.f_even);
    crash_screen_print_fpr(210, 180, 10, &ctx->fp10.f.f_even);
    crash_screen_print_fpr(30, 190, 12, &ctx->fp12.f.f_even);
    crash_screen_print_fpr(120, 190, 14, &ctx->fp14.f.f_even);
    crash_screen_print_fpr(210, 190, 16, &ctx->fp16.f.f_even);
    crash_screen_print_fpr(30, 200, 18, &ctx->fp18.f.f_even);
    crash_screen_print_fpr(120, 200, 20, &ctx->fp20.f.f_even);
    crash_screen_print_fpr(210, 200, 22, &ctx->fp22.f.f_even);
    crash_screen_print_fpr(30, 210, 24, &ctx->fp24.f.f_even);
    crash_screen_print_fpr(120, 210, 26, &ctx->fp26.f.f_even);
    crash_screen_print_fpr(210, 210, 28, &ctx->fp28.f.f_even);
    crash_screen_print_fpr(30, 220, 30, &ctx->fp30.f.f_even);

    ret = Memmap_GetLoadedFragmentVaddr(ctx->pc);
    if (ret != 0) {
        crash_screen_printf(120, 220, "F-PC:%08XH", ret - 0x20);
    }

    ret = Memmap_GetLoadedFragmentVaddr((u32)ctx->ra);
    if (ret != 0) {
        crash_screen_printf(210, 220, "F-RA:%08XH", ret - 0x20);
    }

}

OSThread* crash_screen_get_faulted_thread(void) {
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
 * crash_screen_thread_entry  (owner func_80007F74)
 *
 * Entry point of the crash-handler thread.  It asks the OS to deliver CPU
 * breakpoint events (as message 1) and CPU fault events (as message 2) to
 * the crash screen's message queue, then sleeps on that queue.  Each time a
 * message arrives it looks for a thread that has faulted; once one is
 * found it stops that thread, waits until player 1 has entered the
 * 10-press unlock button sequence (crash_screen_wait_for_button_combo),
 * draws the crash screen (crash_screen_draw), and then spins forever.
 */
void crash_screen_thread_entry(UNUSED void* unused) {
    OSMesg mesg;
    OSThread* faulted_thread;

    osSetEventMesg(OS_EVENT_CPU_BREAK, &gCrashScreen.queue, (OSMesg)1);
    osSetEventMesg(OS_EVENT_FAULT, &gCrashScreen.queue, (OSMesg)2);

    do {
        /* Block until the OS reports a break or a fault... */
        osRecvMesg(&gCrashScreen.queue, &mesg, 1);
        /* ...then see whether some thread really has faulted. */
        faulted_thread = crash_screen_get_faulted_thread();
    } while (faulted_thread == NULL);

    osStopThread(faulted_thread);
    crash_screen_wait_for_button_combo();
    crash_screen_draw(faulted_thread);

    /* Nothing more to do; keep this thread alive on the crash screen. */
    while (TRUE) {}
}

void crash_screen_set_draw_info(u16* frame_buf_ptr, u16 width, u16 height) {
    gCrashScreen.frameBuf = (u16*)((uintptr_t)frame_buf_ptr | 0xA0000000);
    gCrashScreen.width = width;
    gCrashScreen.height = height;
}

void crash_screen_init(void) {
    gCrashScreen.frameBuf = (u16*)(uintptr_t)((osMemSize | 0xA0000000) - ((SCREEN_WIDTH * SCREEN_HEIGHT) * 2));
    gCrashScreen.width = SCREEN_WIDTH;
    gCrashScreen.height = 16;
    osCreateMesgQueue(&gCrashScreen.queue, &gCrashScreen.mesg, 1);
    osCreateThread(&gCrashScreen.thread, 2, crash_screen_thread_entry, NULL,
                   gCrashScreen.stack + sizeof(gCrashScreen.stack), 128);
    osStartThread(&gCrashScreen.thread);
}

void crash_screen_printf_with_bg(s16 x, s16 y, const char* fmt, ...) {
    signed char* ptr;
    u32 glyph;
    s32 size;
    signed char buf[0x100];
    va_list args;

    va_start(args, fmt);

    size = _Printf(crash_screen_copy_to_buf, (char*)buf, fmt, args);

    if (size > 0) {
        crash_screen_draw_rect(x - 6, y - 6, (size + 2) * 6, 19);
        ptr = buf;

        while (size > 0) {
            glyph = gCrashScreenCharToGlyph[*ptr & 0x7F];

            if (glyph != 0xFF) {
                crash_screen_draw_glyph(x, y, glyph);
            }

            ptr++;
            size--;
            x += 6;
        }
    }

    va_end(args);
}
