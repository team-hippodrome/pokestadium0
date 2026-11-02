/* Stadium Zero fragment000_80C00. */

#include "global.h"
#include "m2c_macros.h"

#ifdef NON_MATCHING
/* TODO: decompile func_81111C20; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81111C20.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81111DC8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81111DC8.s")
#endif

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
