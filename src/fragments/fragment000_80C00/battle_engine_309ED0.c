/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_309ED0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "model_renderer.h"
#include "audio_commands.h"
#include "3D140.h"
#include "audio_fade.h"
#include "audio_loop_point.h"
#include "cry.h"
#include "matrix.h"
extern s32 pad_D_84390210[4];
extern s32 sMultihitCount;
extern s32 sMultihitCountdown;

#include "m2c_macros.h"

void func_8110DC90(void);
void func_8110DC98(void);
s32 BattleScene_EndStatusAnimationsAndCommit(ActivePokemon* arg0);
void func_8110E714(void);

void func_8110DC90(void) {
}

void func_8110DC98(void) {
}

void func_8110D5BC(Particle* arg0, s32 arg1, s32* arg2);

void func_8110DCA0(Particle* arg0, s32 arg1) {
    s32 sp1C;

    func_8110D5BC(arg0, arg1, &sp1C);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110DCC0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110DCC0.s")
#endif

s32 BattleScene_EndStatusAnimationsAndCommit(ActivePokemon* arg0) {
    BattleAnim_ClearFreezeStatusAnimation(arg0);
    BattleAnim_EndSleepStatusAnimation(arg0);
    Battle_ApplyAnimStateEffects(arg0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110DF80; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110DF80.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110E500; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110E500.s")
#endif

s32* func_81110CA8(s32, s32);
s32* func_81110D6C(s32, s32);
s32 func_8110E6B0(s32 arg0, s32 arg1) {
    s32* p;
    s32 v;

    if (arg1 < 0x80) {
        p = func_81110CA8(arg0, arg1);
        if (p == NULL) {
            return 0;
        }
        v = p[4];
    } else {
        p = func_81110D6C(arg0, arg1 - 0x80);
        if (p == NULL) {
            return 0;
        }
        v = p[1];
    }
    return v;
}

void func_8110E714(void) {
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110E71C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110E71C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110E784; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110E784.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110E910; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110E910.s")
#endif

void func_8110E994(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {

}

#ifdef NON_MATCHING
/* TODO: decompile func_8110E9A8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110E9A8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110EABC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110EABC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110EB40; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110EB40.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110ED98; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110ED98.s")
#endif

void func_8110EE28(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {

}

#ifdef NON_MATCHING
/* TODO: decompile func_8110EE3C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110EE3C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110EF7C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110EF7C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110F310; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110F310.s")
#endif

typedef struct GbItem8110F4D0 {
    u32 flags;
    s32 key;
} GbItem8110F4D0;
s32 func_8110F4D0(GbItem8110F4D0* item, s32 count, GbItem8110F4D0** items) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (item->key == items[i]->key) {
            break;
        }
    }
    if (i == count) {
        items[count++] = item;
    }
    return count;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110F518; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110F518.s")
#endif

typedef struct GbCollected8110F64C {
    u32 high : 4;
    u32 kind : 2;
    u32 enabled : 1;
    u32 unused : 1;
    u32 address : 24;
} GbCollected8110F64C;
extern GbCollected8110F64C* D_81184978[];
extern s32 D_81185578;
void func_8110F64C(GbCollected8110F64C** arg0) {
    GbCollected8110F64C* item = *arg0;

    if (item->address && item->enabled && item->kind) {
        D_81184978[D_81185578++] = item;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110F6A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110F6A4.s")
#endif

typedef struct Entry81184450 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ char unk4[0x4];
    /* 0x8 */ s16 unk_8;
    /* 0xA */ s16 unk_A;
} Entry81184450; // size = 0xC
typedef struct Table81184440 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ Entry81184450 unk_10[1];
} Table81184440;
extern Table81184440 D_81184440;
extern s32 D_8118444C;
typedef struct Entry811858B0 {
    /* 0x00 */ u8 unk_00[2];
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ char unk04[8];
} Entry811858B0; // size = 0xC
extern Entry811858B0* D_811858B0;
typedef struct Entry8110D840 {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char unk09[7];
} Entry8110D840; // size = 0x10
typedef struct Table8110D840 {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ Entry8110D840 entries[1];
} Table8110D840;
Table8110D840* func_8110D840(s32);
s32 func_8110D7B0(s32, s32);
void func_8110F6A4(s32, s32, s32*);
void func_8110FAF4(void) {
    Table8110D840* base = func_8110D840(2);
    s32 i;
    s32 idx;
    s32 buf[8];
    s32 id;

    for (i = 0; i < D_8118444C; i++) {
        if (D_81184440.unk_10[i].unk_8 == 1) {
            id = func_8110D7B0(1, D_81184440.unk_10[i].unk_A);
            buf[0] = D_811858B0[id].unk_02;
            buf[0] = func_8110D7B0(2, buf[0]);
            buf[1] = D_811858B0[id].unk_03;
            buf[1] = func_8110D7B0(2, buf[1]);
            buf[4] = base->entries[buf[0]].unk_08;
            idx = buf[1];
            buf[5] = base->entries[idx].unk_08;
            func_8110F6A4(id, 0, buf);
        }
    }
}
