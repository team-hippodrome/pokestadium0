/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gfx_buffer.c. */

#include "global.h"
#include "gfx_buffer.h"
typedef struct UnkStruct800A7428 {
    u32* unk0;
    u32* unk4;
    u32 unk8;
    s32 unkC;
    s16 unk10;
} UnkStruct800A7428;
extern Gfx* gDisplayListHead;
extern UnkStruct800A7428 D_800AA158;
void Gfx_SwapDisplayListBuffer(void);

void Gfx_InitDisplayListBuffers(u32 buffer_size, s32 pool_side);
void Gfx_FreeDisplayListBuffers(void);
void Gfx_SwapDisplayListBuffer(void);
void Gfx_GetDisplayListRange(Gfx** arg0, Gfx** arg1);
void* Gfx_AllocDisplayList(s32 size);
s32 Gfx_GetDisplayListRemaining(void);

/** Allocates the two display list buffers. */
void Gfx_InitDisplayListBuffers(u32 buffer_size, s32 pool_side) {
    D_800AA158.unk10 = 0;
    D_800AA158.unkC = buffer_size;
    D_800AA158.unk0 = main_pool_alloc_with_func(buffer_size, pool_side, 'DYN0', NULL);
    D_800AA158.unk4 = main_pool_alloc_with_func(buffer_size, pool_side, 'DYN1', NULL);
    Gfx_SwapDisplayListBuffer();
}

/** Frees the display list buffers. */
void Gfx_FreeDisplayListBuffers(void) {
    main_pool_try_free(D_800AA158.unk4);
    main_pool_try_free(D_800AA158.unk0);
}

/** Switches to the other display list buffer. */
void Gfx_SwapDisplayListBuffer(void) {
    s32* temp_v0 = (s32*)&D_800AA158;

    D_800AA158.unk10 ^= 1;
    temp_v0 += D_800AA158.unk10;

    D_800AA158.unk8 = *temp_v0 + D_800AA158.unkC;
    gDisplayListHead = *temp_v0;
}

/** Returns the start and current end of the display list buffer. */
void Gfx_GetDisplayListRange(Gfx** arg0, Gfx** arg1) {
    s32* ptr = (s32*)&D_800AA158;
    *arg1 = (Gfx*)((uintptr_t)gDisplayListHead - ptr[D_800AA158.unk10]);
    *arg0 = (Gfx*)(ptr[D_800AA158.unk10]);
}

/** Allocates space from the end of the display list buffer. */
void* Gfx_AllocDisplayList(s32 size) {
    u32 temp_v0;
    u32 ret;

    size = ALIGN8(size);
    temp_v0 = (D_800AA158.unk8 - size);
    ret = NULL;
    if (temp_v0 >= (uintptr_t)gDisplayListHead) {
        D_800AA158.unk8 = temp_v0;
        ret = temp_v0;
    }
    return ret;
}

/** Returns how many bytes of the display list buffer remain. */
s32 Gfx_GetDisplayListRemaining(void) {
    return D_800AA158.unk8 - (uintptr_t)gDisplayListHead;
}
