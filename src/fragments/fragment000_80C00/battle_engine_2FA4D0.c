/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/audio_sound_state.c, src/fragments/battle_engine/battle_engine_2FA4D0.c, src/fragments/battle_engine/battle_engine_317E70.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "status_icons.h"
#include "game_state.h"
#include "text_system.h"
#include "3D140.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"

#include "audio_sound_state.h"
#include "libnumus/player.h"
#include "audio_stream.h"
#include "3D140.h"
#include "audio_commands.h"

#include "fragments/battle_engine/battle_engine.h"
#include "geo_render.h"
#include "model_renderer.h"
#include "matrix.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"

#include "m2c_macros.h"

void func_8110FC30(void);
void func_8110FC38(void);
void func_8110FC40(void);
void func_8110FE90(void);
s32 Audio_CountCategorySounds(s32 arg0);
void BattleAnim_ClearEffectStateFlag(void);
void BattleAnim_EffectStartNop(void);
void BattleAnim_DisableEffectSpawningAlias(void);

void BattleAnim_DisableEffectSpawning(void);

void func_8110FC30(void) {
}

void func_8110FC38(void) {
}

void func_8110FC40(void) {
}

M2C_UNK func_800567E0(M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
extern s8 D_811861DA;
extern s8 D_811861DB;
extern s8 D_811861DC;
extern M2C_UNK D_811861E0;
extern M2C_UNK D_811861E8;
extern M2C_UNK *D_81186200;
extern M2C_UNK D_81186208;
extern M2C_UNK D_81186218;
extern M2C_UNK *D_81186230;
extern M2C_UNK D_81186234;
extern M2C_UNK D_81186238;
extern M2C_UNK *D_81186250;

void func_8110FC48(void) {
    D_811861DA = 0;
    D_811861DB = 0;
    D_811861DC = 0;
    D_81186200 = &D_811861E8;
    D_81186230 = &D_81186218;
    D_81186250 = &D_81186238;
    func_800567E0(D_81186200, &D_811861E0, 1);
    func_800567E0(D_81186230, &D_81186208, 4);
    func_800567E0(D_81186250, &D_81186234, 1);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110FCF0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110FCF0.s")
#endif

/*
 * func_8110FD48
 *
 * Calls func_8110FCF0(arg0, &value) where `value` is a local copy of the
 * second argument, so the callee receives it by pointer.  Siblings
 * func_8110FD90 / func_8110FDC0 do the same after shifting an s8 / s16
 * left by 24 / 16 bits; this one passes the word through unchanged.
 *
 * arg0 is declared s32 because the one known caller of the twin function
 * func_8110FD6C passes the constant 0xF9000000 there, so it is a plain
 * word and not necessarily an object pointer.  The cast below only
 * satisfies the DisplayObject* prototype of func_8110FCF0 used by the
 * siblings and produces no code.
 *
 * func_8110FD6C compiles to identical machine code (the original source
 * probably differed in a type that cannot be recovered from the assembly).
 */
void func_8110FCF0(DisplayObject* arg0, s32* arg1);
void func_8110FD48(s32 arg0, s32 arg1) {
    func_8110FCF0((DisplayObject*)arg0, &arg1);
}

/*
 * func_8110FD6C
 *
 * Passes arg0 and the address of a stack copy of arg1 on to func_8110FCF0.
 * This is the function the project's symbol list also knows as
 * func_8121036C_jp(s32 cmd, s32 arg1); callers pass a 32-bit command word
 * such as 0xF9000000 or 0xF1000000 as the first argument, which is why arg0
 * is an s32 here.  The cast only satisfies the DisplayObject* prototype of
 * func_8110FCF0 used by the sibling functions and produces no code.
 *
 * It is a machine-code twin of func_8110FD48; the two cannot be told apart
 * from the assembly.  The address-style name is kept because the other C
 * functions in this file (e.g. func_8110FD90) also use address names.
 */
void func_8110FCF0(DisplayObject* arg0, s32* arg1);
void func_8110FD6C(s32 arg0, s32 arg1) {
    func_8110FCF0((DisplayObject*)arg0, &arg1);
}

void func_8110FCF0(DisplayObject* arg0, s32* arg1);
void func_8110FD90(DisplayObject* arg0, s8 arg1) {
    s32 sp1C = arg1 << 24;

    func_8110FCF0(arg0, &sp1C);
}

void func_8110FDC0(DisplayObject* arg0, s16 arg1) {
    s32 sp1C = arg1 << 16;

    func_8110FCF0(arg0, &sp1C);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110FDF0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110FDF0.s")
#endif

void func_8110FE74(void) {
    (*(u8 *)&D_811861DB) = (*(u8 *)&D_811861DA);
    (*(s8 *)&D_811861DC) = 0;
}

void func_8110FE90(void) {
}

s32 func_8004D1C0(M2C_UNK *, u32 *, M2C_UNK);       /* extern */
extern M2C_UNK D_811855D8;

u32 func_8110FE98(s32 *arg0) {
    u32 sp1C;

    if (func_8004D1C0(&D_811855D8, &sp1C, 0) == -1) {
        *arg0 = 0;
        return 0U;
    }
    *arg0 = sp1C & 0xFFFFFF;
    return sp1C >> 0x18;
}

s32 Audio_CountCategorySounds(s32 arg0) {
    return Audio_CountActiveSoundsByCategory(arg0);
}

extern u8 D_81184658;

/*
 * func_8110FF1C
 *
 * Calls func_8004D1C0 once with the queue pointer in D_81186250, the address
 * of a local word and a third argument of 0 (see func_8110FF74). Returns 0 if
 * that call returns -1; otherwise returns 1 when the word it stored equals
 * D_81184658 and 0 when it does not. The caller-visible meaning of the
 * comparison is not established here.
 * Matching note: the unused leading `pad` local moves `sp18` to the ROM's
 * stack offset (sp+0x18); the two returns are written as separate
 * `return 0` / `return 1` paths because that is the form that compiles to the
 * ROM's branch layout.
 */
s32 func_8110FF1C(void) {
    UNUSED s32 pad;
    u32 sp18;

    if (func_8004D1C0(D_81186250, &sp18, 0) == -1) {
        return 0;
    }
    if (sp18 != D_81184658) {
        return 0;
    }
    return 1;
}

/*
 * func_8110FF74
 *
 * Calls func_8004D1C0 with the queue pointer in D_81186250, the address of a
 * local word and a third argument of 0, repeatedly until it returns -1. The
 * received word is never read, so the loop only discards what the call hands
 * back. (dp_intro.c declares func_8004D1C0 as taking an OSMesgQueue*, and the
 * other callers pass 1 as the third argument; what 0 and -1 mean to the
 * callee is not established here.)
 * Matching note: the -1 is kept in a local assigned inside the loop body.
 * With a literal -1 in the condition the compiler hands out the saved
 * registers in a different order. Declaring `neg` before `sp28` puts `sp28`
 * at the ROM's stack offset (sp+0x28).
 */
void func_8110FF74(void) {
    s32 neg;
    u32 sp28;

    do {
        neg = -1;
    } while (func_8004D1C0(D_81186250, &sp28, 0) != neg);
}

extern u8* D_86B0E5E8;
extern GraphNode* D_86B0E5D0;
void func_8110FF74(void);
void func_8110FD6C(s32, s32);
s32 func_8110FDF0(void);
extern volatile u8 D_81184657;
extern u8 D_81184658;
s32 func_8110FFC8(s32 arg0) {
    s32 v;
    u32 sp18;

    func_8110FF74();
    v = D_81184657;
    if (v != 0) {
        func_8110FE74();
        if (arg0 == D_81184658) {
            return 0;
        }
        if (v >= 3) {
            return 0;
        }
        func_8004D1C0(D_81186250, &sp18, 1);
    }
    func_8110FF74();
    func_8110FD6C(0xF9000000, arg0);
    return func_8110FDF0();
}

extern volatile s32 D_811859D4;

/**
 * Sets the volatile flag D_811859D4 to 1, calls func_8110FFC8(0), then
 * clears the volatile byte D_81184657.
 */
void func_81110060(void) {
    D_811859D4 = 1;
    func_8110FFC8(0);
    D_81184657 = 0;
}

typedef struct unk_D_81184668 {
    /* 0x000 */ u32 unk_000_31 : 1;
    /* 0x000 */ u32 unk_000_0 : 31;
    /* 0x004 */ char unk004[0x30];
    /* 0x034 */ s8* unk_034[(0x15C - 0x34) / 4];
} unk_D_81184668; // size = 0x15C

extern unk_D_81184668 D_81184668[];

s8 func_8111009C(s32 arg0, s32 arg1, s32 arg2) {
    unk_D_81184668* ch = &D_81184668[arg0];
    s8* p;

    if (ch->unk_000_31) {
        p = ch->unk_034[arg1];
        return (p + arg2)[0xC4];
    }
    return -1;
}

extern s8 D_811847BC;
s8 func_811100F8(s32 arg0, s32 arg1) {
    return *(&D_811847BC + ((arg0 * 0x15C) + arg1));
}

M2C_UNK func_811098C0(M2C_UNK *, s32, M2C_UNK);     /* extern */
extern M2C_UNK D_811842A0;

void func_81110128(s32 arg0, M2C_UNK arg1) {
    func_811098C0(&D_811842A0, arg0, arg1);
}

void BattleAnim_ClearEffectStateFlag(void) {
    D_811842A0 = 0;
}

void BattleAnim_EffectStartNop(void) {
}

void BattleAnim_DisableEffectSpawningAlias(void) {
    BattleAnim_DisableEffectSpawning();
}
