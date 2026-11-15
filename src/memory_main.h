/* Declarations for src/memory_main.c. */
#ifndef MEMORY_MAIN_H
#define MEMORY_MAIN_H

#include "global.h"
#include <ultra64.h>
#include <macros.h>

#include "memory.h"

// memory_main.c
// memory_main.c
void main_pool_init(void *start, void *end);
void *main_pool_alloc_from_pool(u32 size, u32 side);
u32 main_pool_free(void *addr, u32 runBlockFunc);
void *main_pool_alloc_with_func(u32 size, s32 side, s32 arg, AllocateFunc func);
void *main_pool_alloc(u32 size, s32 side);
void main_pool_try_free(s32 arg0);
void *main_pool_realloc(void *addr, size_t size);
s32 main_pool_get_available(void);
u32 main_pool_push_state(u32 arg);
u32 main_pool_pop_state(u32 arg);
void *main_pool_search(uintptr_t addr, s32 *argPtr);
void main_pool_set_func(void *block, s32 arg, AllocateFunc func);
size_t main_pool_get_block_dist(MainPoolBlock *block);
MainPool*main_pool_get_pool(void);

#endif // MEMORY_MAIN_H
