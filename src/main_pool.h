/* Declarations for src/main_pool.c. */
#ifndef MAIN_POOL_H
#define MAIN_POOL_H

#include "global.h"
#include <ultra64.h>
#include <macros.h>

// main_pool.c
void *MainPool_AllocState(u32 size, s32 side);

#endif // MAIN_POOL_H
