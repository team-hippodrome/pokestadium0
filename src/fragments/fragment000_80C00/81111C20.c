/* Stadium Zero fragment000_80C00. */

#include "global.h"
#include "m2c_macros.h"

#ifdef NON_MATCHING
/* TODO: decompile func_81111C20; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81111C20.s")
#endif

typedef struct Voice81111DC8 {
    /* 0x00 */ u32 active : 1;
} Voice81111DC8;
typedef struct Track81111DC8 {
    /* 0x00 */ u32 unk00_0 : 5;
    /* 0x00 */ u32 dirty : 1;
    /* 0x00 */ u32 unk00_6 : 2;
    /* 0x01 */ u32 state : 8;
    /* 0x02 */ char unk02[0x12 - 0x2];
    /* 0x12 */ u16 timer;
    /* 0x14 */ char unk14[0x1C - 0x14];
    /* 0x1C */ f32 level;
    /* 0x20 */ f32 levelStep;
    /* 0x24 */ char unk24[0x2C - 0x24];
    /* 0x2C */ f32 scale;
    /* 0x30 */ f32 out;
    /* 0x34 */ Voice81111DC8* voices[16];
} Track81111DC8;
void func_81111C20(Voice81111DC8 *, u32);
void func_81112E00(Track81111DC8 *);
void func_81111DC8(Track81111DC8 *arg0) {
    s32 i;

    if (arg0->timer != 0) {
        arg0->level += arg0->levelStep;
        arg0->dirty = 1;
        if (arg0->level > 1.0f) {
            arg0->level = 1.0f;
        }
        if (arg0->level < 0.0f) {
            arg0->level = 0.0f;
        }
        if ((--arg0->timer == 0) && (arg0->state == 2)) {
            func_81112E00(arg0);
            return;
        }
    }
    if (arg0->dirty) {
        arg0->out = arg0->level * arg0->scale;
    }
    for (i = 0; i < 16; i++) {
        if (arg0->voices[i]->active == 1) {
            func_81111C20(arg0->voices[i], arg0->dirty);
        }
    }
    arg0->dirty = 0;
}

extern f32 D_FLT_81136178[];

f32 func_81111F0C(arg0)
    s8* arg0;
{
    u32 idx;
    f32 ret;

    M2C_FIELD(arg0, f32*, 4) += M2C_FIELD(arg0, f32*, 8);
    idx = M2C_FIELD(arg0, f32*, 4);
    if (idx >= 0x80) {
        idx = 0x7F;
    }
    ret = (M2C_FIELD(arg0, f32*, 0xC) * (D_FLT_81136178[idx] - 1.0f)) + 1.0f;
    return ret;
}

typedef struct {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ u32 phase;
    /* 0x08 */ s16* table;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ f32 step;
} PhaseTableCursor;

/*
 * func_81111FE0
 *
 * Advances the cursor's phase by its step (truncated to an integer) and
 * returns the table entry selected by phase bits 10-15 (a 64-entry table of
 * s16), shifted right by 8 so only the entry's upper byte remains
 * (sign-extended).
 */
s16 func_81111FE0(PhaseTableCursor* arg0) {
    s32 index;

    arg0->phase += (s32)arg0->step;
    index = (arg0->phase >> 10) & 0x3F;
    return (s16)(arg0->table[index] >> 8);
}

#ifdef NON_MATCHING
/* TODO: decompile func_81112024; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81112024.s")
#endif

f32 func_81111F0C(); // The caller passes a second argument the callee ignores.
f32 func_81112024(s8 *, s8 *);                  /* extern */

void func_8111220C(s8 *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x80) != 0) {
        M2C_FIELD(arg0, f32 *, 0x38) = func_81111F0C(arg0 + 0x80, arg0);
    }
    if ((M2C_FIELD(arg0, u8 *, 0xA4) != 0) && (M2C_FIELD(arg0, s32 *, 0x44) != -1)) {
        M2C_FIELD(arg0, f32 *, 0x3C) = func_81112024(arg0 + 0x90, arg0);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_81112278; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81112278.s")
#endif

void func_8111235C(s8 *arg0, s32 arg1, M2C_UNK arg2) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 1) = 0;
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    M2C_FIELD(arg0, f32 *, 8) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x14) = 0.0f;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81112380; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81112380.s")
#endif
