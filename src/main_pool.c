/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/memory.c. */

#include "global.h"
#include "main_pool.h"
#include "memory_main.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void MainPool_FinalizeAllocation(struct MemoryBlock* block);
void MainPool_ResetState(struct MainPoolState* state);
void MainPool_ResetStateToOffset(struct MainPoolState* state, s32 size);
void* MainPool_AllocAligned(struct MainPoolState* state, s32 arg1, s32 arg2);
void* MainPool_InitState(struct MainPoolState* block, s32 size);

void* MainPool_AllocState(u32 size, s32 side);
void MainPool_FinalizeAllocation(struct MemoryBlock* block);
void* MainPool_InitState(struct MainPoolState* block, s32 size);
void* MainPool_AllocAligned(struct MainPoolState* state, s32 arg1, s32 arg2);
void MainPool_ResetStateToOffset(struct MainPoolState* state, s32 size);
void MainPool_ResetState(struct MainPoolState* state);

/** Allocates a main pool state from one side of the pool. */
void* MainPool_AllocState(u32 size, s32 side) {
    MainPoolBlock* block;
    void* ptr = NULL;

    size = ALIGN4(size);
    ptr = 0;
    block = main_pool_alloc(size, side);
    if (block != NULL) {
        ptr = MainPool_InitState(block, size);
    }
    return ptr;
}

/** Finalizes a block allocation, aligning its size. */
void MainPool_FinalizeAllocation(struct MemoryBlock* block) {
    s32 size = ALIGN16(block->size + 0x10);

    main_pool_realloc(block, size);
    block->next = (void*)(size - 0x10);
}

/** Initializes a main pool state over a block of memory. */
void* MainPool_InitState(struct MainPoolState* block, s32 size) {
    void* temp_v1 = (void*)((u8*)block + 0x10);

    block->listHeadL = 0;
    block->freeSpace = ((size & ~3) - 0x10); // this doesnt match an ALIGN4 macro or whatnot
    block->listHeadR = temp_v1;
    block->prev = temp_v1;
    return block;
}

/** Allocates aligned memory from a pool state. */
void* MainPool_AllocAligned(struct MainPoolState* state, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_a3;
    s32 var_v0;
    s32 ret = 0;

    if (arg2 > 0) {
        var_v0 = (((s32)state->prev + (s32)arg2) - 1) & ~(arg2 - 1);
    } else {
        var_v0 = state->prev;
    }
    temp_a2 = (var_v0 - (s32)state->prev) + arg1;
    if (temp_a2 > 0) {
        temp_a3 = (s32)state->listHeadL + temp_a2;
        if ((s32)state->freeSpace >= temp_a3) {
            ret = var_v0;
            state->prev = (s32)((s32)state->prev + temp_a2);
            state->listHeadL = temp_a3;
        }
    }
    return ret;
}

/** Resets a pool state, keeping the first part of its allocations. */
void MainPool_ResetStateToOffset(struct MainPoolState* state, s32 size) {
    if ((s32)state->freeSpace >= size) {
        state->listHeadL = size;
        state->prev = (void*)((s32)state->listHeadR + size);
    }
}

/** Frees every allocation of a pool state. */
void MainPool_ResetState(struct MainPoolState* state) {
    void* mem = (u8*)((u32)state + sizeof(struct MainPoolState));

    state->listHeadL = 0;
    state->listHeadR = mem;
    state->prev = mem;
}
