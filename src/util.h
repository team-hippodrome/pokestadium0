/* Declarations for src/util.c. */
#ifndef UTIL_H
#define UTIL_H

#include "global.h"

extern u32 gExpansionRAMStart;

// util.c
uintptr_t Util_ConvertAddrToVirtAddr(uintptr_t addr);
void Util_Memcpy(u32* dest, u32* src, int size);
void* Util_Malloc(s32 size);
void Util_Free(void* ptr);
void Util_DrawRect(Gfx** dlist, s32 ulx, s32 lrx, u16 color);
void Util_Memclear(u64* dest, u32 size);
s32 Util_CheckStubMemArea(u64* ptr); // unused

#endif // UTIL_H
