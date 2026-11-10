/* Stadium Zero resident code. */
/* Split from audio_commands.c: the code after the jump tables of func_800407B0. */

#include "audio_commands.h"
#include "audio_commands_category2.h"
#include "audio_commands.h"
#include "3D140.h"
#include "libnumus/player.h"
#include "rom_device.h"
#include "audio_channel.h"
#include "audio_cache.h"
#include "cry.h"
#include "audio_fade.h"
#include "m2c_macros.h"

#ifdef NON_MATCHING
/* TODO: decompile func_800414B0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800414B0.s")
#endif

M2C_UNK func_8003834C(s32, s32, s32, M2C_UNK, s32, s32, s32); /* extern */
extern s32 D_800B418C;
extern s32 D_800B41A8;

void func_80041834(s32 arg0) {
    func_8003834C(D_800B418C, D_800B41A8, arg0, 0x80, 0x80, 0, -1);
}

/*
 * func_8004187C
 *
 * Bounds-checked lookup into the array of two words at D_800FD698.
 * Returns the entry for index 0 or 1, and -1 for any other index
 * (the index is treated as unsigned, so negative values also give -1).
 * What the table entries mean is not known.
 */
extern s32 D_800FD698[];
s32 func_8004187C(u32 arg0) {
    if (arg0 >= 2U) {
        return -1;
    }
    return D_800FD698[arg0];
}

/*
 * func_800418A4
 *
 * Same shape as func_8004187C but reading the array of two words at
 * D_800FD6A8: index 0 or 1 returns the entry, anything else returns -1.
 */
extern s32 D_800FD6A8[];
s32 func_800418A4(u32 arg0) {
    if (arg0 >= 2U) {
        return -1;
    }
    return D_800FD6A8[arg0];
}

extern M2C_UNK D_800FD6B4;

s32 func_800418CC(u32 arg0) {
    if (arg0 >= 2) {
        return -1;
    }
    return ((u8*)&D_800FD6B4)[arg0];
}

extern u8 D_80077538;

void func_800418F0(s32 arg0) {
    if (arg0 != 0) {
        D_80077538 = 1;
        return;
    }
    D_80077538 = 0;
}

extern M2C_UNK D_800FD6B2;
extern M2C_UNK D_800FD6B4;

void func_80041914(s32 arg0, s32 arg1) {
    s8 temp_v0;
    s8 temp_v1;

    temp_v0 = arg0 * 2;
    temp_v1 = arg1 * 2;
    M2C_FIELD(&D_800FD6B2, s8 *, 0) = temp_v0;
    M2C_FIELD(&D_800FD6B4, s8 *, 0) = temp_v0;
    M2C_FIELD(&D_800FD6B2, s8 *, 1) = temp_v1;
    M2C_FIELD(&D_800FD6B4, s8 *, 1) = temp_v1;
}

extern s32 D_800FD6A0[];
extern u8 D_800FD6B0[];
extern u8 D_800FD6B6[];
extern u8 D_80077560;
void func_80041940(u32 arg0, s32 arg1, s32 arg2) {
    s32* cur;
    s32* prev;
    s32* next;

    if (arg0 < 2) {
        prev = &D_800FD6A0[arg0];
        cur = &D_800FD698[arg0];
        next = &D_800FD6A8[arg0];
        *prev = *cur;
        *cur = arg1;
        *next = arg2;
        if (arg1 == 0) {
            if (*prev == *next) {
                D_80077560 = 1;
            } else {
                D_80077560 = 0;
            }
            if (((u8*)&D_800FD6B4)[arg0] != 0) {
                ((u8*)&D_800FD6B4)[arg0]--;
            }
            D_800FD6B6[arg0]++;
            D_800FD6B0[arg0] = 1;
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_800419F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800419F8.s")
#endif
