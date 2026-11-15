/* Declarations for src/crash_screen.c. */
#ifndef CRASH_SCREEN_H
#define CRASH_SCREEN_H

#include "global.h"

typedef struct {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ char stack[0x800];
    /* 0x9B0 */ OSMesgQueue queue;
    /* 0x9C8 */ OSMesg mesg;
    /* 0x9CC */ u16* frameBuf;
    /* 0x9D0 */ u16 width;
    /* 0x9D2 */ u16 height;
} CrashScreen; // size = 0x9D4

extern CrashScreen gCrashScreen;

extern u8 gCrashScreenCharToGlyph[128];

extern u32 gCrashScreenFont[];

extern const char* gFaultCauses[18];

extern const char* gFPCSRFaultCauses[6];

extern u16 gCrashScreenUnlockInputs[];

// crash_screen.c
void CrashScreen_Sleep(s32 ms);
void CrashScreen_DrawRect(s32 x, s32 y, s32 width, s32 height);
void CrashScreen_DrawGlyph(s32 x, s32 y, s32 glyph);
char *CrashScreen_CopyToBuf(char *buffer, const char *data, size_t size);
void CrashScreen_Printf(s32 x, s32 y, const char *fmt, ...);
void CrashScreen_PrintFpr(s32 x, s32 y, s32 regNum, void *addr);
void CrashScreen_PrintFpcsr(u32 fpcsr);
void CrashScreen_Draw(OSThread* faultedThread);
OSThread* CrashScreen_GetFaultedThread(void);
void CrashScreen_ThreadEntry(void* unused);
void CrashScreen_SetDrawInfo(u16* frameBufPtr, u16 width, u16 height);
void CrashScreen_Init(void);
void CrashScreen_PrintfWithBg(s16 x, s16 y, const char* fmt, ...);

#endif // CRASH_SCREEN_H
