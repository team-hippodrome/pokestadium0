/* Declarations for src/memory.c. */
#ifndef MEMORY_H
#define MEMORY_H

#include "global.h"
#include <ultra64.h>
#include <macros.h>

struct MainPoolBlock;

typedef void (*AllocateFunc)(struct MainPoolBlock*, u32);

typedef struct MainPoolBlock {
    /* 0x00 */ struct MainPoolBlock *prev;
    /* 0x04 */ struct MainPoolBlock *next;
    /* 0x08 */ AllocateFunc func;
    /* 0x0C */ s32 arg; // passed into func as the 2nd argument.
} MainPoolBlock; // size = 0x10

// structs for the main pool.
typedef struct MainPoolState {
    /* 0x00 */ s32 freeSpace;
    /* 0x04 */ MainPoolBlock *listHeadL;
    /* 0x08 */ MainPoolBlock *listHeadR;
    /* 0x0C */ struct MainPoolState *prev;
} MainPoolState;

typedef struct MainPool {
    /* 0x00 */ OSMesg msgs[1];
    /* 0x04 */ OSMesgQueue queue;
    /* 0x1C */ size_t available;
    /* 0x20 */ MainPoolBlock *start;
    /* 0x24 */ MainPoolBlock *end;
    /* 0x28 */ MainPoolBlock *listHeadL;
    /* 0x2C */ MainPoolBlock *listHeadR;
    /* 0x30 */ struct MainPoolState *mainState;
} MainPool;

// structs used for the smaller pools allocated from the global pool.
typedef struct MemoryBlock {
    /* 0x00 */ struct MemoryBlock *next;
    /* 0x04 */ u32 size;
} MemoryBlock;

typedef struct MemoryPool {
    /* 0x00 */ OSMesg msgs[1];
    /* 0x04 */ OSMesgQueue queue;
    /* 0x1C */ size_t available;
    /* 0x20 */ struct MemoryBlock *firstBlock;
    /* 0x24 */ struct MemoryBlock freeList;
} MemoryPool;

// memory.c
// memory.c
MemoryPool *mem_pool_try_init(u32 size, s32 side);
MainPool* mem_pool_init(MainPool* pool, s32 size);
void *mem_pool_alloc(MemoryPool* node, s32 size);
void mem_pool_free(MemoryPool* pool, void* addr);

#endif // MEMORY_H
