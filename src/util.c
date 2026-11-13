/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/util.c. */

#include "global.h"
#include "memmap.h"
#include "memory.h"
#include "util.h"
extern u32 gExpansionRAMStart;
extern MainPool** gMainPool;
void Dma_InitializeCompletionQueue(void);
s32 StageContext_IsHighResolution(void);

#include "m2c_macros.h"

uintptr_t Util_ConvertAddrToVirtAddr(uintptr_t addr);
void Util_Memcpy(u32* dest, u32* src, int size);
void* Util_Malloc(s32 size);
void Util_Free(void* ptr);
void Util_DrawRect(Gfx** dlist, s32 ulx, s32 lrx, u16 color);

/**
 * Convert any valid address to its virtual (KSEG0) counterpart.
 */
uintptr_t Util_ConvertAddrToVirtAddr(uintptr_t addr) {
    uintptr_t retaddr = NULL; // any invalid cases are treated as NULL return.

    // convert physical (in installed memory range) to virtual.
    if (addr < osMemSize) {
        retaddr = addr | 0x80000000;
        // convert segmented to virtual.
    } else if (addr < 0x10000000U) {
        retaddr = Memmap_GetSegmentVaddr(addr);
        // convert a fragment pre-relocated address to a post-relocated virtual address.
    } else if ((addr >= 0x81000000U) &&
               (addr < 0x90000000U)) { // is the address in fragment space? convert it to its post-relocated address.
        retaddr = Memmap_GetFragmentVaddr(addr);
        // pass-through addresses that are already virtual (in installed memory range)
    } else if ((addr >= 0x80000000U) && (addr < (uintptr_t)(osMemSize + 0x80000000U))) {
        retaddr = addr;
    }

    return retaddr;
}

/**
 * Copy memory from one address to the other.
 */
void Util_Memcpy(u32* dest, u32* src, int size) {
    while (size-- > 0) {
        *(dest++) = *(src++);
    }
}

M2C_UNK func_800020C0(M2C_UNK *, M2C_UNK);          /* extern */
s32 func_80002840(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_80003670();                            /* extern */
extern s32 D_800A94E0;
extern M2C_UNK D_80105360;

void func_80002D58(void) {
    func_800020C0(&D_80105360, 0x80400000);
    func_80003670();
    D_800A94E0 = func_80002840(0x10000, 0);
}

/**
 * Allocate memory from the main pool.
 */
void* Util_Malloc(s32 size) {
    return mem_pool_alloc(gMainPool, size);
}

/**
 * Free a pointer being used in the main pool.
 */
void Util_Free(void* ptr) {
    mem_pool_free(gMainPool, ptr);
}

/**
 * Draws a profiler rectangle with given coordinates. Solely used by the next function
 * which facilitates the tacked on memory profiler.
 */
void Util_DrawRect(Gfx** dlist, s32 ulx, s32 lrx, u16 color) {
    s32 uly = 15;
    s32 lry = 17;
    Gfx* gfx = *dlist;

    if (StageContext_IsHighResolution() != 0) {
        ulx <<= 1;
        lrx <<= 1;
        uly <<= 1;
        lry <<= 1;
    }

    gDPPipeSync(gfx++);
    gDPSetFillColor(gfx++, color << 16 | color);
    gDPFillRectangle(gfx++, ulx, uly, lrx, lry);
    *dlist = gfx;
}

void func_80002EC8(Gfx** dlist) {
    MainPool* pool = main_pool_get_pool();
    UNUSED s32 pad; // FAKE: stack padding
    s32 available = main_pool_get_available();

    if (available >= 0) {
        s32 baseX = 30;
        s32 startX = ((u32)(K0_TO_PHYS(pool->start)) >> 15) + baseX;
        s32 headLX = ((u32)(K0_TO_PHYS(pool->listHeadL)) >> 15) + baseX;
        s32 headRX = ((u32)(K0_TO_PHYS(pool->listHeadR)) >> 15) + baseX;
        s32 endX = ((u32)(K0_TO_PHYS(pool->end)) >> 15) + baseX;

        Util_DrawRect(dlist, baseX, startX, GPACK_RGBA5551(248, 120, 40, 1)); // #F87828
        Util_DrawRect(dlist, startX, headLX, GPACK_RGBA5551(248, 248, 40, 1)); // #F8F828
        Util_DrawRect(dlist, headLX, headRX, GPACK_RGBA5551(40, 80, 248, 1)); // #2850F8
        Util_DrawRect(dlist, headRX, endX, GPACK_RGBA5551(248, 248, 40, 1)); // #F8F828
        HAL_Printf(baseX, 20, "MEM: +%XH (+%dK)", available, available / 1024);
    } else {
        s32 baseX = 30;
        s32 startX = ((u32)(K0_TO_PHYS(pool->start)) >> 15) + baseX;
        s32 headLX = ((u32)(K0_TO_PHYS(pool->listHeadL)) >> 15) + baseX;
        s32 headRX = ((u32)(K0_TO_PHYS(pool->listHeadR)) >> 15) + baseX;
        s32 endX = ((u32)(K0_TO_PHYS(pool->end)) >> 15) + baseX;

        Util_DrawRect(dlist, baseX, startX, GPACK_RGBA5551(248, 120, 40, 1)); // #F87828
        Util_DrawRect(dlist, startX, headRX, GPACK_RGBA5551(248, 248, 40, 1)); // #F8F828
        Util_DrawRect(dlist, headRX, headLX, GPACK_RGBA5551(248, 40, 40, 1)); // #F82828
        Util_DrawRect(dlist, headLX, endX, GPACK_RGBA5551(248, 248, 40, 1)); // #F8F828
        HAL_Printf(baseX, 20, "MEM: -%XH (-%dK)", -available, -available / 1024);
    }
}

/**
 * Clear memory address area.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Util_Memclear(u64* dest, u32 size) {
    while (size-- > 0) {
        *(dest++) = 0x1234567812345678;
    }
}

/**
 * Unused function for checking some 64-bit range (possibly some display list?) for values
 * cooresponding to 0x8040000080400000. This could have been for some memory test however
 * the code for such a test is not present in this ROM, so we can only guess this function's
 * intended usage.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Util_CheckStubMemArea(u64* ptr) {
    s32 ret = 0;

    while (*(ptr++) == 0x1234567812345678) {
        ret++;
    }
    return ret * sizeof(*ptr);
}
