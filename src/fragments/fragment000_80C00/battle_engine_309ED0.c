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

/** Four consecutive words, copied as a unit. */
typedef struct Words4_8110E71C {
    s32 w[4];
} Words4_8110E71C;

/** Entry returned by func_8110E6B0: four words, the first of which starts with a flag byte. */
typedef struct Entry8110E71C {
    /* 0x00 */ u8 flags;
    /* 0x01 */ u8 unk_01[3];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} Entry8110E71C;

/** Object that receives a copy of the entry; only the used fields are named. */
typedef struct Owner8110E71C {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 keyA;
    /* 0x02 */ u8 keyB;
    /* 0x03 */ u8 unk_03[9];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 unk_10[0xC];
    /* 0x1C */ Words4_8110E71C copy;
} Owner8110E71C;

/**
 * Looks up the entry for (keyA, keyB) with func_8110E6B0. If one exists, its
 * 16 bytes are copied into arg0->copy, the entry's second word is
 * overwritten with arg0->unk_0C, and bits 2 and 3 of its first byte are
 * cleared.
 */
void func_8110E71C(Owner8110E71C* arg0) {
    Entry8110E71C* entry;

    entry = (Entry8110E71C*)func_8110E6B0(arg0->keyA, arg0->keyB);
    if (entry != NULL) {
        arg0->copy = *(Words4_8110E71C*)entry;
        entry->unk_04 = arg0->unk_0C;
        entry->flags &= 0xFFF3;
    }
}

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

typedef struct Item8110F4D0 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 key;
} Item8110F4D0;

/**
 * Appends `arg0` to the list `list` unless an entry with the same `key` (offset 0x4)
 * is already present among the first `count` entries.
 *
 * @param arg0  Item to add.
 * @param count Number of entries currently in `list`.
 * @param list  Array of item pointers; must have room for `count + 1` entries.
 * @return The new entry count (count + 1 if added, otherwise unchanged).
 */
s32 func_8110F4D0(Item8110F4D0* arg0, s32 count, Item8110F4D0** list) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (arg0->key == list[i]->key) {
            break;
        }
    }
    if (i == count) {
        list[count] = arg0;
        count++;
    }
    return count;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110F518; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110F518.s")
#endif

/* First word of a record, split into bit ranges (big-endian, most significant
 * bit first). The field names only say which bits they are; what they mean is
 * not established. */
typedef struct {
    u32 bits31_28 : 4;
    u32 bits27_26 : 2;
    u32 bit25 : 1;
    u32 bit24 : 1;
    u32 low24 : 24;
} PackedWordRec;

extern PackedWordRec *D_81184978[];
extern s32 D_81185578;

/*
 * func_8110F64C
 *
 * Takes a pointer to a pointer to a record whose first word is read as the
 * bit ranges above. When the low 24 bits, bit 25 and bits 27..26 are all
 * non-zero, the record pointer is appended to the pointer array D_81184978
 * and the count D_81185578 is incremented. There is no bounds check on the
 * count. The caller (func_8110F6A4) is still assembly, so what the array and
 * the count are used for is not established from this function alone.
 * Matching note: the bit-field reads are what produce the ROM's shift
 * sequence; the equivalent masks and shifts on a plain word differ in
 * temporary register numbering.
 */
void func_8110F64C(PackedWordRec **arg0) {
    PackedWordRec *rec;

    rec = *arg0;
    if (rec->low24 && rec->bit25 && rec->bits27_26) {
        D_81184978[D_81185578] = rec;
        D_81185578 += 1;
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
