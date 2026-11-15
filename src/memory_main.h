/* Declarations for src/memory_main.c. */
#ifndef MEMORY_MAIN_H
#define MEMORY_MAIN_H

#include "global.h"
#include <ultra64.h>
#include <macros.h>

#include "memory.h"

// memory_main.c
// memory_main.c
void MainPool_Init(void *start, void *end);
void *MainPool_AllocFromPool(u32 size, u32 side);
u32 MainPool_Free(void *addr, u32 runBlockFunc);
void *MainPool_AllocWithFunc(u32 size, s32 side, s32 arg, AllocateFunc func);
void *MainPool_Alloc(u32 size, s32 side);
void MainPool_TryFree(s32 arg0);
void *MainPool_Realloc(void *addr, size_t size);
s32 MainPool_GetAvailable(void);
u32 MainPool_PushState(u32 arg);
u32 MainPool_PopState(u32 arg);
void *MainPool_Search(uintptr_t addr, s32 *argPtr);
void MainPool_SetFunc(void *block, s32 arg, AllocateFunc func);
size_t MainPool_GetBlockDist(MainPoolBlock *block);
MainPool*MainPool_GetPool(void);

#endif // MEMORY_MAIN_H
