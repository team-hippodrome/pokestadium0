/* Declarations for src/gfx_buffer.c. */
#ifndef GFX_BUFFER_H
#define GFX_BUFFER_H

#include "global.h"

// gfx_buffer.c
void Gfx_InitDisplayListBuffers(u32 buffer_size, s32 pool_side);
void Gfx_FreeDisplayListBuffers(void);
void Gfx_SwapDisplayListBuffer(void);
void Gfx_GetDisplayListRange(Gfx** arg0, Gfx** arg1);
void* Gfx_AllocDisplayList(s32 size);
s32 Gfx_GetDisplayListRemaining(void);

#endif // GFX_BUFFER_H
