/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/audio_commands.c, src/audio_data.c. */

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
typedef struct unk_D_80077970 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
} unk_D_80077970;
extern u8 pad_D_800FC694[4];
extern unk_D_800FC6CC* D_800B41E4;
extern u8* D_800B41E8;
extern unk_D_800FC6D4* D_800FD688;
extern s16* D_800B41EC;
extern u32* gAudioRegions;
extern s32 pad_D_800FC70C;
extern s32 pad_D_800FC710;
extern u8 pad_D_800FC718[0x80];
#define AUDIO_HEAP_SIZE 300000
extern s32 pad_D_80077C80;

#include "audio_data.h"
#include "libnumus/player.h"
#include "rom_device.h"
#include "audio_cache.h"
#include "audio_category_fade.h"
#include "audio_commands.h"

#include "m2c_macros.h"

void Audio_RelocateOffsets(u32* arg0, u32 arg1, s32 arg2);
void Audio_CreateFrameTaskWrapper(void* arg0);
void Audio_ClearWaveDataLoaded(void);

void Audio_RelocateOffsets(u32* arg0, u32 arg1, s32 arg2) {
    u32 i;

    for (i = 0; i < arg2; i++, arg0++) {
        *arg0 += arg1;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003E1F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003E1F8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8003EECC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003EECC.s")
#endif

extern s32 D_800FD608;
extern u8 D_8007752C;
s32 func_80037AC4(s32, s32);
void func_800419F8(s32);

s32 func_8003F654(s32 arg0) {
    s32 ret;

    if (arg0 == 0) {
        arg0 = 1;
    }
    ret = func_80037AC4(D_800FD608, arg0);

    if (D_8007752C == 0) {
        func_800419F8(0);
    }
    return ret;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003F6AC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003F6AC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8003F96C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003F96C.s")
#endif

void func_8003FE58(s32, s32, s32);

void func_8003FE34(s32 arg0, s32 arg1) {
    func_8003FE58(arg0, 1, arg1);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003FE58; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003FE58.s")
#endif

void Audio_CreateFrameTaskWrapper(void* arg0) {
    Audio_CreateFrameTask(arg0);
}

M2C_UNK func_80037AC4(s32, M2C_UNK);                /* extern */
extern u8 D_80077524;
extern s32 D_800FD64C;
extern s32 D_800FD650;

void func_80040738(void) {
    if (D_80077524 != 0) {
        func_80037AC4(D_800FD64C, 0x32);
        func_80037AC4(D_800FD650, 0x32);
    } else {
        func_80037AC4(D_800FD64C, 0x5A);
        func_80037AC4(D_800FD650, 0x5A);
    }
    D_800FD64C = 0;
    D_800FD650 = 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_800407B0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800407B0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80041374; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80041374.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_80041940; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80041940.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_800419F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800419F8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80042508; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80042508.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80042A6C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80042A6C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80042FF8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80042FF8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80043860; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80043860.s")
#endif

/*
 * func_80043A10
 *
 * Chooses between two settings depending on D_80077540 and D_800FD6B4 and
 * sets the flag byte D_80077530.
 *
 *   - If D_80077540 == 8 and the byte D_800FD6B4 is at least 2:
 *     func_80043CE8(0x18, 0.0f, 0x80) and D_80077530 = 1; nothing else.
 *   - In every other case: func_80043CE8(0x1E, 0.0f, 0x80), D_80077530 = 0,
 *     then func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1).
 *
 * The second argument of func_80043CE8 is a float: with a float parameter
 * the compiler loads the constant into $a1 with `li`, which is what the ROM
 * does (an integer 0 would use `move $a1, $zero`).  What func_80043CE8
 * (still assembly) and func_8003834C do with these values is not
 * established here.
 */
void func_80043CE8(s32, f32, s32);
extern s8 D_80077530;
extern u8 D_80077540;
extern s32 D_800B4188;
extern s32 D_800B41A4;

void func_80043A10(void) {
    if (D_80077540 == 8) {
        if (*(u8*)&D_800FD6B4 >= 2) {
            func_80043CE8(0x18, 0.0f, 0x80);
            D_80077530 = 1;
            return;
        }
        func_80043CE8(0x1E, 0.0f, 0x80);
        D_80077530 = 0;
        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
        return;
    }
    func_80043CE8(0x1E, 0.0f, 0x80);
    D_80077530 = 0;
    func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
}

#ifdef NON_MATCHING
/* TODO: decompile func_80043B00; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80043B00.s")
#endif

/** One pending entry in the 10-slot ring buffer D_800FD6C0. */
typedef struct QueuedEntry80043CE8 {
    /* 0x0 */ s32 id;
    /* 0x4 */ f32 value;
    /* 0x8 */ u32 level;
} QueuedEntry80043CE8;

extern u8 D_80077528;
extern u8 D_8007753C;
extern u32 D_80077558;
extern u32 D_8007758C;
extern QueuedEntry80043CE8 D_800FD6C0[];
s32 func_8004D300(s32);

/**
 * Appends (arg0, arg1, arg2 + 0x70) to the 10-entry ring buffer D_800FD6C0,
 * with the level clamped to 0xFF.
 *
 * Does nothing unless D_80077528 == 0, D_80077538 != 0 and D_8007753C == 0,
 * and also does nothing when D_80077558 (the number of queued entries) is
 * already 2 or more. D_8007758C is the write index and wraps modulo 10. The
 * update runs with the interrupt mask raised by func_8004D300 (libultra's
 * osSetIntMask) and restored afterwards.
 */
void func_80043CE8(s32 arg0, f32 arg1, s32 arg2) {
    s32 prevMask;
    QueuedEntry80043CE8* entry;
    u32 level;
    u32 idx;
    u32 count;

    if ((D_80077528 == 0) && (D_80077538 != 0) && (D_8007753C == 0)) {
        prevMask = func_8004D300(1);
        count = D_80077558;
        if (count < 2) {
            idx = D_8007758C;
            entry = &D_800FD6C0[idx];
            level = arg2 + 0x70;
            entry->level = level;
            entry->id = arg0;
            entry->value = arg1;
            if (level >= 0x100) {
                entry->level = 0xFF;
            }
            D_8007758C = idx + 1;
            D_80077558 = count + 1;
            D_8007758C %= 10;
        }
        func_8004D300(prevMask);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_80043DD0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80043DD0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80044158; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80044158.s")
#endif

void Audio_ClearWaveDataLoaded(void) {
    D_80075C30 &= ~0x80000000;
}
