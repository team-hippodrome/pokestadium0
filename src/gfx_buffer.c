/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gfx_buffer.c. */

#include "global.h"
#include "gfx_buffer.h"
typedef struct DisplayListBuffers {
    /* 0x00 */ u32* buffers[2];  // @unverified: 'DYN0'/'DYN1' allocations in Gfx_InitDisplayListBuffers
    /* 0x08 */ u32 allocEnd;     // @unverified: Gfx_AllocDisplayList takes space down from here toward gDisplayListHead
    /* 0x0C */ s32 bufferSize;   // @unverified: buffer_size argument of Gfx_InitDisplayListBuffers
    /* 0x10 */ s16 current;      // @unverified: toggled by Gfx_SwapDisplayListBuffer, indexes buffers[]
} DisplayListBuffers; // size = 0x14
extern Gfx* gDisplayListHead;
extern DisplayListBuffers D_800AA158;
void Gfx_SwapDisplayListBuffer(void);

void Gfx_InitDisplayListBuffers(u32 buffer_size, s32 pool_side);
void Gfx_FreeDisplayListBuffers(void);
void Gfx_SwapDisplayListBuffer(void);
void Gfx_GetDisplayListRange(Gfx** arg0, Gfx** arg1);
void* Gfx_AllocDisplayList(s32 size);
s32 Gfx_GetDisplayListRemaining(void);

/** Allocates the two display list buffers. */
void Gfx_InitDisplayListBuffers(u32 buffer_size, s32 pool_side) {
    D_800AA158.current = 0;
    D_800AA158.bufferSize = buffer_size;
    D_800AA158.buffers[0] = main_pool_alloc_with_func(buffer_size, pool_side, 'DYN0', NULL);
    D_800AA158.buffers[1] = main_pool_alloc_with_func(buffer_size, pool_side, 'DYN1', NULL);
    Gfx_SwapDisplayListBuffer();
}

/** Frees the display list buffers. */
void Gfx_FreeDisplayListBuffers(void) {
    main_pool_try_free(D_800AA158.buffers[1]);
    main_pool_try_free(D_800AA158.buffers[0]);
}

/** Switches to the other display list buffer. */
void Gfx_SwapDisplayListBuffer(void) {
    s32* temp_v0 = (s32*)&D_800AA158;

    D_800AA158.current ^= 1;
    temp_v0 += D_800AA158.current;

    D_800AA158.allocEnd = *temp_v0 + D_800AA158.bufferSize;
    gDisplayListHead = *temp_v0;
}

/** Returns the start and current end of the display list buffer. */
void Gfx_GetDisplayListRange(Gfx** arg0, Gfx** arg1) {
    s32* ptr = (s32*)&D_800AA158;
    *arg1 = (Gfx*)((uintptr_t)gDisplayListHead - ptr[D_800AA158.current]);
    *arg0 = (Gfx*)(ptr[D_800AA158.current]);
}

/** Allocates space from the end of the display list buffer. */
void* Gfx_AllocDisplayList(s32 size) {
    u32 temp_v0;
    u32 ret;

    size = ALIGN8(size);
    temp_v0 = (D_800AA158.allocEnd - size);
    ret = NULL;
    if (temp_v0 >= (uintptr_t)gDisplayListHead) {
        D_800AA158.allocEnd = temp_v0;
        ret = temp_v0;
    }
    return ret;
}

/** Returns how many bytes of the display list buffer remain. */
s32 Gfx_GetDisplayListRemaining(void) {
    return D_800AA158.allocEnd - (uintptr_t)gDisplayListHead;
}
