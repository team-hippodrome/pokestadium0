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

typedef struct StereoFlags811105DC {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 pad : 7;
    /* 0x1 */ u8 wide : 1;
} StereoFlags811105DC;

void func_811105DC(s8* arg0, f32 arg1) {
    StereoFlags811105DC* flags = (StereoFlags811105DC*)(arg0 + 0xB4);
    f32 pan;

    if (arg1 < 2.0f) {
        flags->wide = 0;
        if (1.99998f < arg1) {
            pan = 1.99998f;
        } else {
            pan = arg1;
        }
    } else {
        flags->wide = 1;
        if (3.99996f < arg1) {
            pan = 1.99998f;
        } else {
            pan = arg1 * 0.5f;
        }
    }
    M2C_FIELD(arg0, s16*, 0xC0) = pan * 32768.0f;
}

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

typedef struct Flags8111073C {
    /* 0x0 */ u32 b80 : 1;
    /* 0x0 */ u32 b40 : 1;
    /* 0x0 */ u32 b20 : 1;
    /* 0x0 */ u32 rest : 29;
} Flags8111073C;

#define FLAGS ((Flags8111073C*)(arg0 + 0xB4))
void func_8111073C(s8* arg0) {
    if (FLAGS->b40 == 1) {
        FLAGS->b40 = 0;
    }
    M2C_FIELD(arg0, u8*, 0x30) = 0;
    M2C_FIELD(arg0, u8*, 0x34) = 0;
    FLAGS->b80 = 0;
    if (arg0 && arg0 && arg0) {}
    M2C_FIELD(arg0, s32*, 0x44) = -1;
    M2C_FIELD(arg0, s32*, 0x40) = -1;
    FLAGS->b20 = 0;
    M2C_FIELD(arg0, u8*, 0x5D) = 0;
    M2C_FIELD(arg0, f32*, 0x70) = 0.0f;
}
#undef FLAGS

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

typedef struct ParticleBank81110CA8 {
    /* 0x0 */ u8 count;
    /* 0x1 */ u8 count2;
    /* 0x4 */ u8** entries;
    /* 0x8 */ u8** entries2;
} ParticleBank81110CA8; // size = 0xC

s32 func_8110CA2C(s32 arg0);
extern ParticleBank81110CA8* D_811858B0;
extern s32 D_811859D0;

u8* func_81110CA8(s32 arg0, s32 arg1) {
    ParticleBank81110CA8* bank;
    u8* ret;

    if (func_8110CA2C(arg0) == 0) {
        D_811859D0 = arg0 + 0x10000000;
        return NULL;
    }
    bank = (ParticleBank81110CA8*)((u8*)D_811858B0 + arg0 * sizeof(ParticleBank81110CA8));
    if (arg1 >= bank->count) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x03000000;
        return NULL;
    }
    ret = bank->entries[arg1];
    if (ret == NULL) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x01000000;
        return ret;
    }
    return ret;
}

u8* func_81110D6C(s32 arg0, s32 arg1) {
    ParticleBank81110CA8* bank;
    u8* ret;

    if (func_8110CA2C(arg0) == 0) {
        D_811859D0 = arg0 + 0x10000000;
        return NULL;
    }
    bank = (ParticleBank81110CA8*)((u8*)D_811858B0 + arg0 * sizeof(ParticleBank81110CA8));
    if (arg1 >= bank->count2) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x04000000;
        return NULL;
    }
    if ((u32)bank->entries2 < 0x80000000) {
        return NULL;
    }
    ret = bank->entries2[arg1];
    if (ret == NULL) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x05000000;
    }
    return ret;
}

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

extern s8 D_81184948;
extern s8 D_81184958;
extern s8 D_81184968;
void func_811111E0(void);
s32 func_81112EEC(s8 *);
void func_81111340(s8* arg0, s32 arg1) {
    s32 pad[3]; /* places src/dst at sp+0x48/0x44 and the frame at 0x58 as in the ROM */
    s8* src;
    s8* dst;
    s32 n;
    s32 pass;
    s32 r;

    func_811111E0();
    for (pass = 0, n = 0; n < arg1; pass++) {
        if (pass == 4) {
            return;
        }
        switch (pass) {
            case 0:
                src = &D_81184938;
                dst = arg0;
                break;
            case 1:
                src = &D_81184948;
                dst = arg0 + 0x10;
                break;
            case 2:
                src = &D_81184958;
                dst = arg0 + 0x20;
                break;
            case 3:
                src = &D_81184968;
                dst = arg0 + 0x30;
                break;
        }
        while (n < arg1) {
            r = func_81112EEC(src);
            if (r == 0) {
                break;
            }
            func_81112EAC(dst, (Rec81111130*)r);
            n++;
        }
    }
}

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

typedef struct Flags81111568 {
    /* 0x0 */ u32 pad0 : 6;
    /* 0x0 */ u32 flag : 1;
    /* 0x0 */ u32 pad0b : 1;
    /* 0x1 */ u8 mode : 3;
    /* 0x1 */ u8 pad1 : 2;
    /* 0x1 */ u8 range : 2;
    /* 0x1 */ u8 pad1b : 1;
    /* 0x2 */ char pad2[0xE];
    /* 0x10 */ s32 unk10;
} Flags81111568;
typedef struct Src81111568 {
    /* 0x0 */ u32 pad : 5;
    /* 0x0 */ u32 flag : 1;
    /* 0x0 */ u32 rest : 26;
} Src81111568;
typedef struct Bit81111568 { u8 pad : 5; u8 b : 1; u8 rest : 2; } Bit81111568;
void func_81111568(s8* arg0, s8* arg1) {
    Flags81111568* flags;
    s32 v;

    M2C_FIELD(arg0, s32*, 0x40) = -1;
    M2C_FIELD(arg0, s8**, 0x44) = arg1;
    M2C_FIELD(arg0, u8*, 0x30) = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x54), u8*, 5);
    ((Bit81111568*)arg1)->b = 1;
    M2C_FIELD(arg1, u8*, 3) = 3;
    M2C_FIELD(arg1, s8**, 0x48) = arg0;
    M2C_FIELD(M2C_FIELD(arg1, s8**, 0x54), s8**, 0x40) = arg0;
    M2C_FIELD(M2C_FIELD(arg1, s8**, 0x54), s8**, 0x44) = arg1;
    M2C_FIELD(arg1, f32*, 0x34) = 0.0f;
    func_81110694((Obj0694*)arg0);
    v = M2C_FIELD(arg1, u8*, 2);
    flags = (Flags81111568*)(arg0 + 0xB4);
    if (v == 0xFF) {
        v = M2C_FIELD(M2C_FIELD(arg1, s8**, 0x54), s16*, 0x22);
    }
    flags->unk10 = M2C_FIELD(arg1, s32*, 0x50);
    if (v >= 0x80 && v < 0xC0) {
        flags->range = 1;
    } else {
        flags->range = 0;
    }
    M2C_FIELD(arg0, u8*, 0x33) = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x54), u8*, 7);
    flags->flag = M2C_FIELD(arg1, Src81111568**, 0x54)->flag;
    flags->mode = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x54), u8*, 8) & 3;
}


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
void func_81111568(s8*, s8*);

s32 func_811116E8(s8 *arg0, s32 arg1) {
    s32 ret;

    ret = func_81112EEC(arg0);
    if (ret != 0) {
        func_81111568((s8*)ret, (s8*)arg1);
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

s8 *func_81111784(s8 *arg0, s8 *arg1)
{
  s8 *a;
  s8 *b;
  s32 prioA;
  s32 prioB;
  prioA = (prioB = 0x10);
  a = func_811114E8(arg0 + 0x20, *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5)));
  if (a != 0)
  {
    prioA = *((u8 *) (((s8 *) a) + 0x30));
  }
  b = func_811114E8(arg0 + 0x30, *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5)));
  if (b != 0)
  {
    prioB = *((u8 *) (((s8 *) b) + 0x30));
  }
  if ((a == 0) && (b == 0))
  {
    return 0;
  }
  if (prioB < (prioA ^ 0))
  {
    func_811114BC(b);
    func_81111688(b, (s32) arg1);
    func_81112EAC(arg0 + 0x20, (Rec81111130 *) b);
    *((u8 *) (((s8 *) b) + 0x30)) = *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5));
    return b;
  }
  *((s8 **) (((s8 *) a) + 0x48)) = arg1;
  *((u8 *) (((s8 *) a) + 0x30)) = *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5));
  return a;
}

s8* func_8111187C(s8* arg0) {
    s8* voice;
    s32 flags = M2C_FIELD(arg0, u8**, 0x54)[2];

    if (flags & 1) {
        voice = M2C_FIELD(arg0, s8**, 0x48);
        if ((voice != NULL) && (arg0 == M2C_FIELD(voice, s8**, 0x40)) && (M2C_FIELD(voice, s32*, 0x48) == -1)) {
            func_811116BC(voice, arg0);
            func_811114BC(voice);
            func_81112EAC(M2C_FIELD(voice, s8**, 0xC) + 0x20, (Rec81111130*)voice);
            return voice;
        }
    }
    if (flags & 2) {
        if (((voice = (s8*)func_811116E8(M2C_FIELD(arg0, s8**, 0x54) + 0x84, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = func_81111784(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL)) {
            return voice;
        }
    } else if (flags & 4) {
        if (((voice = (s8*)func_811116E8(M2C_FIELD(arg0, s8**, 0x54) + 0x84, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_811116E8(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x54), s8**, 0x4C) + 0x98, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x54), s8**, 0x4C) + 0x98, arg0)) != NULL) ||
            ((voice = func_81111784(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = func_81111784(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x54), s8**, 0x4C) + 0x98, arg0)) != NULL)) {
            return voice;
        }
    } else if (flags & 8) {
        if (((voice = (s8*)func_811116E8(&D_81184938, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(&D_81184938, arg0)) != NULL) ||
            ((voice = func_81111784(&D_81184938, arg0)) != NULL)) {
            return voice;
        }
    } else {
        if (((voice = (s8*)func_811116E8(M2C_FIELD(arg0, s8**, 0x54) + 0x84, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_811116E8(&D_81184938, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(&D_81184938, arg0)) != NULL) ||
            ((voice = func_81111784(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = func_81111784(&D_81184938, arg0)) != NULL)) {
            return voice;
        }
    }
    arg0[3] = 0;
    return NULL;
}

typedef struct Rec81111AF4 {
    /* 0x00 */ char pad00[0x1C];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ char pad20[0x10];
    /* 0x30 */ s8 unk_30;
    /* 0x31 */ s8 unk_31;
    /* 0x32 */ char pad32[2];
    /* 0x34 */ s8 unk_34;
    /* 0x35 */ char pad35;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ char pad38[8];
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ char pad4C[8];
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ char pad58[4];
    /* 0x5C */ s8 unk_5C;
    /* 0x5D */ s8 unk_5D;
    /* 0x5E */ char pad5E[0x84 - 0x5E];
    /* 0x84 */ f32 unk_84;
    /* 0x88 */ f32 unk_88;
    /* 0x8C */ char pad8C[0xA4 - 0x8C];
    /* 0xA4 */ s8 unk_A4;
    /* 0xA5 */ char padA5[0xB4 - 0xA5];
    /* 0xB4 */ Copy18 unk_B4;
    /* 0xCC */
} Rec81111AF4; // size = 0xCC
extern Copy18 D_811369A8;
extern s8 D_811842C0;
s32 func_81109868(s8 *, s32);
void func_81111AF4(void) {
    s32 i;
    Rec81111AF4* rec;

    for (i = 0; i < D_811858E8; i++) {
        rec = (Rec81111AF4*)&D_81184664[i];
        rec->unk_B4 = D_811369A8;
        rec->unk_30 = 0;
        rec->unk_34 = 0;
        rec->unk_44 = -1;
        rec->unk_48 = -1;
        rec->unk_40 = -1;
        rec->unk_31 = 0;
        rec->unk_54 = 0.0f;
        rec->unk_36 = 0;
        rec->unk_5D = 0;
        rec->unk_5C = 0;
        rec->unk_A4 = 0;
        rec->unk_84 = 0.0f;
        rec->unk_88 = 0.0f;
        rec->unk_1C = func_81109868(&D_811842C0, 0x80);
    }
}
