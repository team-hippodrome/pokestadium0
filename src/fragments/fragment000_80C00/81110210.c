/* Stadium Zero fragment000_80C00. */

#include "global.h"
#include "fragments/particle_math/particle_math.h"
#include "m2c_macros.h"
void func_81110E3C(Particle*, s32);

#ifdef NON_MATCHING
/* TODO: decompile func_81110210; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81110210.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811105DC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811105DC.s")
#endif

typedef struct Copy18 {
    s32 w[6];
} Copy18;
typedef struct Inner0694 {
    char pad00[0x80];
    s32 unk_80;
} Inner0694;
typedef struct Def0694 {
    char pad00[0x18];
    u8 unk_18;
    s32 unk_1C;
    char pad20[0x54 - 0x20];
    Inner0694* unk_54;
} Def0694;
typedef struct Obj0694 {
    char pad00[0x34];
    u8 unk_34;
    char pad35;
    char unk_36[0x44 - 0x36];
    Def0694* unk_44;
    char pad48[0x5C - 0x48];
    u8 unk_5C;
    u8 unk_5D;
    char pad5E[0xB4 - 0x5E];
    Copy18 unk_B4;
} Obj0694;
extern Copy18 D_811369C0;
void func_8111235C(u8*, s32, char*);

void func_81110694(Obj0694* arg0) {
    Def0694* def = arg0->unk_44;

    if (def->unk_18 == 0) {
        func_8111235C(&arg0->unk_5C, def->unk_54->unk_80, arg0->unk_36);
    } else {
        func_8111235C(&arg0->unk_5C, def->unk_1C, arg0->unk_36);
    }
    arg0->unk_34 = 0;
    arg0->unk_5D = 1;
    arg0->unk_B4 = D_811369C0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8111073C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8111073C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81110798; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81110798.s")
#endif

u8* func_81110C6C(u8* arg0, s32 arg1) {
    u8* ret;

    if (arg1 < arg0[1]) {
        ret = arg0 + 8;
    } else if (arg0[2] >= arg1) {
        ret = arg0 + 0x10;
    } else {
        ret = arg0 + 0x18;
    }
    return ret;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81110CA8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81110CA8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81110D6C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81110D6C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81110E3C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81110E3C.s")
#endif

void func_81111090(Particle* arg0) {
    func_81110E3C(arg0, 6);
}

void func_811110B0(Particle* arg0) {
    func_81110E3C(arg0, 7);
}

void func_811110D0(s8 *arg0) {
    M2C_FIELD(arg0, s8 **, 0) = arg0;
    M2C_FIELD(arg0, s8 **, 4) = arg0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

/*
 * func_811110E0
 *
 * Calls func_811110D0 on four 16-byte blocks at arg0 + 0x00, 0x10, 0x20 and
 * 0x30.  func_811110D0 stores the block's own address in its first two words
 * and clears the third, giving an empty circular list head {next, prev,
 * count, owner}: func_8111147C and func_81112EAC, which insert into such a
 * list, link through the first two words, increment the third and copy the
 * fourth into the inserted node.  Afterwards arg0 itself is stored in the
 * fourth word (offset 0xC) of each block.
 */
void func_811110E0(s8 *arg0) {
    func_811110D0(arg0);
    func_811110D0(arg0 + 0x10);
    func_811110D0(arg0 + 0x20);
    func_811110D0(arg0 + 0x30);
    M2C_FIELD(arg0, s8 **, 0xC) = arg0;
    M2C_FIELD(arg0, s8 **, 0x1C) = arg0;
    M2C_FIELD(arg0, s8 **, 0x2C) = arg0;
    M2C_FIELD(arg0, s8 **, 0x3C) = arg0;
}

/* Same 0xCC-byte record array as func_81109678 (gb_tower_emulator_86920.c); only the fields used here are named. */
typedef struct Rec81111130 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 pad04[4];
    /* 0x08 */ struct Rec81111130* unk_08;
    /* 0x0C */ u8 pad0C[0xCC - 0xC];
} Rec81111130; // size = 0xCC

s32 func_81112EAC(s8*, Rec81111130*);
extern Rec81111130* D_81184664;
extern s8 D_81184938;
extern s32 D_811858E8;

/*
 * func_81111130
 *
 * Calls func_811110E0(&D_81184938), then for each of the D_811858E8 records of
 * the array at D_81184664 (0xCC bytes each, indexed directly each time):
 * stores the record's own address at offset 8, clears the word at offset 0,
 * and calls func_81112EAC(&D_81184938, record). func_81109678, which walks the
 * same array, passes the same list argument to the same function. What the
 * records are is not established from this function.
 */
void func_81111130(void) {
    s32 i;

    func_811110E0(&D_81184938);
    for (i = 0; i < D_811858E8; i++) {
        D_81184664[i].unk_08 = &D_81184664[i];
        D_81184664[i].unk_00 = 0;
        func_81112EAC(&D_81184938, &D_81184664[i]);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_811111E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811111E0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81111340; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81111340.s")
#endif

void func_8111147C(M2C_UNK *arg0, M2C_UNK *arg1) {
    if (M2C_FIELD(arg1, M2C_UNK **, 0) == NULL) {
        M2C_FIELD(arg1, M2C_UNK **, 0) = arg0;
        M2C_FIELD(arg1, M2C_UNK **, 4) = (M2C_UNK *) M2C_FIELD(arg0, M2C_UNK **, 4);
        *M2C_FIELD(arg0, M2C_UNK **, 4) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = arg1;
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + 1);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    }
}

void func_811114BC(s8 *arg0) {
    s8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s8 ***, 4) = (s8 **) M2C_FIELD(arg0, s8 ***, 4);
        *M2C_FIELD(arg0, s8 ***, 4) = M2C_FIELD(arg0, s8 **, 0);
        M2C_FIELD(arg0, s8 **, 0) = NULL;
    }
}

s8 *func_811114E8(s8 *arg0, s32 arg1) {
    s8 *temp_a0;
    s8 *var_v0;
    s8 *var_v1;

    var_v0 = M2C_FIELD(arg0, s8 **, 4);
    if (var_v0 == arg0) {
        return NULL;
    }
    var_v1 = var_v0;
    if (var_v0 != arg0) {
        do {
            if ((s32) M2C_FIELD(M2C_FIELD(var_v1, s8 **, 8), u8 *, 0x30) >= (s32) M2C_FIELD(M2C_FIELD(var_v0, s8 **, 8), u8 *, 0x30)) {
                var_v1 = var_v0;
            }
            var_v0 = M2C_FIELD(var_v0, s8 **, 4);
        } while (var_v0 != arg0);
    }
    if (var_v1 == NULL) {
        return NULL;
    }
    temp_a0 = M2C_FIELD(var_v1, s8 **, 8);
    if ((s32) M2C_FIELD(temp_a0, u8 *, 0x30) >= arg1) {
        return NULL;
    }
    return temp_a0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81111568; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81111568.s")
#endif


void func_81111688(s8 *arg0, s32 arg1) {
    func_811110B0(M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
}

extern f32 D_FLT_811858D4;
void func_811116BC(s8 *arg0, s8 *arg1)
{
  *((s8 **) (((s8 *) arg0) + 0x48)) = arg1;
  *((u8 *) (((s8 *) arg0) + 0x30)) = (u8) (*((u8 *) (((s8 *) (*((s8 **) (((s8 *) arg1) + 0x54)))) + 5)));
  *((f32 *) (((s8 *) arg0) + 0x6C)) = (f32) D_FLT_811858D4;
  *((u8 *) (((s8 *) arg0) + 0x5C)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x5C))) | 0x10);
}

/*
 * func_811116E8
 *
 * Moves one entry from the list headed at arg0 to the list headed at
 * arg0 + 0x30.  The list heads are 16-byte blocks laid out as
 * {next, prev, count, owner}, as set up by func_811110D0 and func_811110E0.
 *
 *   1. func_81112EEC(arg0) unlinks the first node of the list at arg0 and
 *      returns the word stored at offset 8 of that node (0 if the list is
 *      empty).  That value is the entry used below and the return value.
 *   2. If it is not 0, func_81111568(entry, arg1) is called on it, and
 *      func_8111147C then appends the entry to the list at arg0 + 0x30
 *      (it does nothing if the entry's first word is already non-zero).
 *
 * Returns the entry, or 0 if there was none.  What func_81111568 does with
 * arg1 is not established (it is still assembly).
 */
s32 func_81112EEC(s8 *);
M2C_UNK func_81111568(s32, s32);                    /* extern */

s32 func_811116E8(s8 *arg0, s32 arg1) {
    s32 ret;

    ret = func_81112EEC(arg0);
    if (ret != 0) {
        func_81111568(ret, arg1);
        func_8111147C((M2C_UNK *) (arg0 + 0x30), (M2C_UNK *) ret);
    }
    return ret;
}

/*
 * func_81111734
 *
 * Like func_811116E8, but it takes the entry from the list headed at
 * arg0 + 0x10, initialises it with func_811116BC(entry, arg1), and inserts
 * it at the front of the list headed at arg0 + 0x20 with func_81112EAC.
 * List heads are {next, prev, count, owner} blocks (see func_811110D0).
 *
 * func_81112EEC unlinks the first node of the list at arg0 + 0x10 and
 * returns the word at offset 8 of that node, or 0 if the list is empty.
 * Returns that entry, or 0 if there was none; nothing else happens then.
 */
s32 func_81112EEC(s8 *);

s32 func_81111734(s8 *arg0, s8 *arg1) {
    s32 ret;

    ret = func_81112EEC(arg0 + 0x10);
    if (ret != 0) {
        func_811116BC((s8 *) ret, arg1);
        func_81112EAC(arg0 + 0x20, (s8 *) ret);
    }
    return ret;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81111784; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81111784.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8111187C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8111187C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81111AF4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81111AF4.s")
#endif
