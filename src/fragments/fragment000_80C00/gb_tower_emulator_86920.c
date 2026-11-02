/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_emulator/gb_tower_emulator_86920.c. */

#include "global.h"
typedef struct unk_func_81206FA0 {
  /* 0x00 */ s32 unk_00;
  /* 0x04 */ s32 unk_04;
  /* 0x08 */ s32 unk_08;
  /* 0x0C */ s32 unk_0C;
} unk_func_81206FA0;
typedef struct unk_D_812346E0 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} unk_D_812346E0;
typedef struct unk_D_81231450 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_81231450;
typedef struct unk_D_81234650 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_81234650;
typedef struct unk_D_81234690 {
    /* 0x00 */ u8  pad0[2];
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 pad0E[0x2A];
} unk_D_81234690;
extern unk_D_81234690 D_811858B8;
extern volatile s32 D_811858F0;
extern s32 D_811858F8;
extern s32 D_811858FC;
extern s16* D_811859B8[3];
extern s16 D_811859C4[3];
extern u32 D_811859CC;
extern volatile s32 D_811859D4;

#include "m2c_macros.h"

u32 GbApu_AllocZeroed(unk_func_81206FA0* arg0, s32 arg1);
s32 GbApu_Alloc(unk_func_81206FA0* arg0, s32 arg1);
void GbApu_InitAllocator(unk_func_81206FA0* arg0, s32 arg1, s32 arg2);

#ifdef NON_MATCHING
/* TODO: decompile func_811095E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811095E0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81109678; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81109678.s")
#endif

M2C_UNK func_81112E00(M2C_UNK *);                   /* extern */
extern s8 D_81184668;
extern s16 D_811858CC;
void func_81109764(s32 arg0)
{
  s32 new_var2;
  s8 *new_var;
  s32 var_s1;
  var_s1 = 0;
  if (D_811858CC > 0)
  {
    new_var = &D_81184668;
    new_var = new_var;
    new_var2 = arg0;
    do
    {
      if (((((u32) (*((u32 *) (((s8 *) new_var) + 0)))) >> 0x1F) != 0) && (new_var2 == (*((u8 *) (((s8 *) new_var) + 4)))))
      {
        func_81112E00(new_var);
      }
      var_s1 += 1;
      new_var += 0x15C;
    }
    while (var_s1 < D_811858CC);
  }
}

u32 GbApu_AllocZeroed(unk_func_81206FA0* arg0, s32 arg1) {
  s32 temp_v0;
  u32 temp_a2;
  u32 var_a1;
  temp_v0 = ALIGN16(arg1);
  temp_a2 = arg0->unk_04;
  if ((arg0->unk_00 + arg0->unk_08) >= (temp_a2 + temp_v0)) {
      arg0->unk_04 += temp_v0;
      var_a1 = temp_a2;
      while (var_a1 < arg0->unk_04) {
          *((u8*)var_a1++) = 0;
      }
  } else {
      return 0;
  }
  arg0->unk_0C++;
  return temp_a2;
}

s32 GbApu_Alloc(unk_func_81206FA0* arg0, s32 arg1) {
  s32 temp_a2;
  u32 temp_v0;

  temp_v0 = ALIGN16(arg1);
  temp_a2 = arg0->unk_04;
  if ((arg0->unk_00 + arg0->unk_08) >= (arg0->unk_04 + temp_v0)) {
      arg0->unk_04 = temp_v0 + temp_a2;
  } else {
      return 0;
  }
  arg0->unk_0C++;
  return temp_a2;
}

void GbApu_InitAllocator(unk_func_81206FA0* arg0, s32 arg1, s32 arg2) {
  arg0->unk_00 = ALIGN16(arg1);
  arg0->unk_04 = ALIGN16(arg1);
  arg0->unk_08 = (s32) (arg2 - (arg1 & 0xF));
  arg0->unk_0C = 0;
}

void func_811098E8(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 4);
}

/*
 * func_811098FC
 *
 * Resets a small record: the words at +0x00 and +0x10 are cleared, the words
 * at +0x08 and +0x14 are set to the value at +0x04, the word at +0x20 is set
 * to (+0x0C) + (+0x04), and the halfwords at +0x1E and +0x2A are set to -1.
 * It reads like the set-up of a cursor over a buffer (start at +0x04, length
 * at +0x0C, end stored at +0x20), but the role of the record is not
 * established from the code alone, so the fields are left unnamed.
 *
 * The sum is written with the fields in this order, and read from memory
 * rather than through a local, because IDO orders the two operands of the
 * addu differently otherwise.
 */
void func_811098FC(s32* arg0) {
    arg0[4] = 0;
    arg0[0] = 0;
    arg0[8] = arg0[3] + arg0[1];
    ((s16*)arg0)[0xF] = -1;
    ((s16*)arg0)[0x15] = -1;
    arg0[2] = arg0[1];
    arg0[5] = arg0[1];
}

void func_8110992C(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110993C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110993C.s")
#endif

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184290;
extern M2C_UNK D_811842C0;
extern M2C_UNK D_811842F0;

void func_8110999C(s8 *arg0) {
    M2C_FIELD(&D_81184290, s32 *, 4) = (s32) M2C_FIELD(&D_81184290, s32 *, 0);
    func_811098C0(&D_811842C0, func_81109868(&D_81184290, M2C_FIELD(arg0, s32 *, 0)), M2C_FIELD(arg0, s32 *, 0));
    func_811098C0(&D_811842F0, func_81109868(&D_81184290, M2C_FIELD(arg0, s32 *, 0xC)), M2C_FIELD(arg0, s32 *, 0xC));
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_811842F0;
extern M2C_UNK D_81184300;
extern M2C_UNK D_81184310;

void func_81109A18(s8 *arg0) {
    M2C_FIELD(&D_811842F0, s32 *, 4) = (s32) M2C_FIELD(&D_811842F0, s32 *, 0);
    func_811098C0(&D_81184300, func_81109868(&D_811842F0, M2C_FIELD(arg0, s32 *, 0)), M2C_FIELD(arg0, s32 *, 0));
    func_811098C0(&D_81184310, func_81109868(&D_811842F0, M2C_FIELD(arg0, s32 *, 4)), M2C_FIELD(arg0, s32 *, 4));
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184300;
extern M2C_UNK D_81184320;
extern M2C_UNK D_81184324;
extern M2C_UNK D_81184380;
extern M2C_UNK D_81184384;
extern M2C_UNK D_811843E0;
extern M2C_UNK D_811843E4;

void func_81109A94(s8 *arg0) {
    M2C_FIELD(&D_81184300, s32 *, 4) = (s32) M2C_FIELD(&D_81184300, s32 *, 0);
    func_811098C0(&D_81184324, func_81109868(&D_81184300, M2C_FIELD(arg0, s32 *, 0)), M2C_FIELD(arg0, s32 *, 0));
    func_811098C0(&D_81184384, func_81109868(&D_81184300, M2C_FIELD(arg0, s32 *, 4)), M2C_FIELD(arg0, s32 *, 4));
    func_811098C0(&D_811843E4, func_81109868(&D_81184300, M2C_FIELD(arg0, s32 *, 8)), M2C_FIELD(arg0, s32 *, 8));
    func_811098E8(&D_81184320);
    func_811098E8(&D_81184380);
    func_811098E8(&D_811843E0);
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184310;
extern M2C_UNK D_81184340;
extern M2C_UNK D_81184344;
extern M2C_UNK D_811843A0;
extern M2C_UNK D_811843A4;
extern M2C_UNK D_81184400;
extern M2C_UNK D_81184404;

void func_81109B50(s8 *arg0) {
    M2C_FIELD(&D_81184310, s32 *, 4) = (s32) M2C_FIELD(&D_81184310, s32 *, 0);
    func_811098C0(&D_81184344, func_81109868(&D_81184310, M2C_FIELD(arg0, s32 *, 0)), M2C_FIELD(arg0, s32 *, 0));
    func_811098C0(&D_811843A4, func_81109868(&D_81184310, M2C_FIELD(arg0, s32 *, 4)), M2C_FIELD(arg0, s32 *, 4));
    func_811098C0(&D_81184404, func_81109868(&D_81184310, M2C_FIELD(arg0, s32 *, 8)), M2C_FIELD(arg0, s32 *, 8));
    func_811098FC(&D_81184340);
    func_811098FC(&D_811843A0);
    func_811098FC(&D_81184400);
}

#ifdef NON_MATCHING
/* TODO: decompile func_81109C0C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81109C0C.s")
#endif

/*
 * func_8110A310
 *
 * Calls func_8110B880(arg0, arg2) and returns its result if that is
 * non-zero.  Otherwise returns 0 if arg1 is 3, and
 * func_8110A368(arg0, arg1, arg2) for any other arg1.
 */
s32 func_8110A368(s32 arg0, s32 arg1, s32 arg2);
s32 func_8110B880(s32 arg0, s32 arg1);

s32 func_8110A310(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = func_8110B880(arg0, arg2);

    if (result != 0) {
        return result;
    }
    if (arg1 == 3) {
        return 0;
    }
    return func_8110A368(arg0, arg1, arg2);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110A368; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110A368.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110A474; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110A474.s")
#endif

void func_8110A848(s16* values) {
    s32 i;

    for (i = 0; i < 8;) {
        values[i + 1] = 0;
        values[i + 2] = 0;
        values[i + 3] = 0;
        i += 4;
        values[i - 4] = 0;
    }
}

extern s16 D_811371D8[];
void func_8110A878(s16* values, s32 index) {
    s32 i;

    for (i = 0; i < 8; i++) {
        values[i] = D_811371D8[index * 8 + i];
    }
}

extern s16 D_811373C8[];
void func_8110A8CC(s16* values, s32 index) {
    s32 i;
    s16* source = &D_811373C8[index * 8 - 8];

    for (i = 0; i < 8; i++) {
        values[i] = source[i];
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110A924; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110A924.s")
#endif

typedef struct Voice8110AA50 {
    /* 0x000 */ char unk000[0xC];
    /* 0x00C */ u16 unk_0C;
    /* 0x00E */ char unk00E[0x14A];
} Voice8110AA50; // size = 0x158
extern Voice8110AA50 D_81184110[];
extern s8 D_8118427B;
void func_8110AA50(void) {
    s32 n;
    s32 i;
    s32 j;

    if (*(s16*)&D_811858B8 == 2) {
        n = 2;
    } else {
        n = 1;
    }
    for (i = 0; i < D_8118427B; i++) {
        for (j = 0; j < n; j++) {
            D_81184110[i].unk_0C -= D_81184110[i].unk_0C / 3;
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110AC14; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110AC14.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110AC8C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110AC8C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110AFF0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110AFF0.s")
#endif

typedef struct unk_D_81184450 {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ char unk4[0x4];
    /* 0x8 */ s16 unk_8;
    /* 0xA */ s16 unk_A;
} unk_D_81184450; // size = 0xC

typedef struct unk_D_81184440 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ unk_D_81184450 unk_10[1];
} unk_D_81184440;

extern unk_D_81184440 D_81184440;
s32 func_8110B880(s32 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < D_81184440.unk_0C; i++) {
        if (arg0 == D_81184440.unk_10[i].unk_8 && arg1 == D_81184440.unk_10[i].unk_A) {
            return D_81184440.unk_10[i].unk_0;
        }
    }

    return 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110B8D8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110B8D8.s")
#endif

s8* func_8110BA8C(s32);
s32 func_8110B958(s32 arg0, s32 arg1, s32 arg2, s8 arg3) {
    s8* p = func_8110BA8C(arg0);

    if (p != NULL) {
        M2C_FIELD(p, u8*, 2) = arg1;
        M2C_FIELD(p, s32*, 0xC) = arg2;
        M2C_FIELD(p, s8*, 1) = arg3;
        return M2C_FIELD(p, s32*, 8);
    }
    return 0;
}

s8* func_8110BF28(s32 arg0);
s32 func_8110B9A8(s32 arg0, s32 arg1, s32 arg2, s8 arg3) {
    s8* p = func_8110BF28(arg0);

    if (p != NULL) {
        M2C_FIELD(p, u8*, 2) = arg1;
        M2C_FIELD(p, s32*, 0xC) = arg2;
        M2C_FIELD(p, s8*, 1) = arg3;
        return M2C_FIELD(p, s32*, 8);
    }
    return 0;
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184300;
extern M2C_UNK D_81184310;
extern M2C_UNK D_811845D0;
extern s32 D_811845D8;
extern s32 D_811845F4;
extern M2C_UNK D_811845F8;
extern s32 D_81184600;
extern s32 D_8118461C;

void func_8110B9F8(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_81109868(&D_81184300, arg0);
    if (temp_v0 == 0) {
        D_811845D8 = 0;
    } else {
        func_811098C0(&D_811845D0, temp_v0, arg0);
    }
    temp_v0_2 = func_81109868(&D_81184310, arg1);
    if (temp_v0_2 == 0) {
        D_81184600 = 0;
    } else {
        func_811098C0(&D_811845F8, temp_v0_2, arg1);
    }
    D_811845F4 = 0;
    D_8118461C = 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110BA8C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110BA8C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110BD20; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110BD20.s")
#endif

typedef struct GbRemap8110BEE4 {
    u8 pad00;
    s8 kind;
    u8 pad02[6];
    s32 oldAddress;
    s32 newAddress;
} GbRemap8110BEE4;
typedef struct GbReference8110BEE4 {
    unsigned char high : 4;
    unsigned char kind : 2;
    unsigned char low : 2;
    u8 pad01[3];
    s32 address;
} GbReference8110BEE4;
void func_8110BEE4(GbRemap8110BEE4* source, GbReference8110BEE4* reference) {
    if (reference != NULL && reference->address == source->oldAddress) {
        reference->address = source->newAddress;
        reference->kind = source->kind;
    }
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
s8 *func_8110BF28(s32 arg0)
{
  s32 temp_v0_2;
  s8 *temp_v0;
  s32 *new_var;
  new_var = (s32 *) (&D_811845F4);
  temp_v0_2 = func_81109868(&(*((s8 *) (&D_811845D0))), arg0);
  if (temp_v0_2 == 0)
  {
    return 0;
  }
  temp_v0 = (((*new_var) * 0x14) + 0x10) + (&(*((s8 *) (&D_811845D0))));
  *((s8 *) (((s8 *) temp_v0) + 0)) = 1;
  *((s32 *) (((s8 *) temp_v0) + 8)) = temp_v0_2;
  *((s32 *) (((s8 *) temp_v0) + 0x10)) = arg0;
  *new_var += 1;
  return temp_v0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110BFB0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110BFB0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110C1C0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110C1C0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110C2D8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110C2D8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110C618; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110C618.s")
#endif

extern s8 D_81184655;

s32 func_8110CA2C(s32 arg0) {
    if (arg0 == 0xFF) {
        return 1;
    }
    if (((u8*)&D_81184655)[arg0] >= 2) {
        return 1;
    }
    return 0;
}

extern s8 D_81184656;

s32 func_8110CA68(s32 arg0) {
    if (arg0 == 0xFF) {
        return 1;
    }
    if (((u8*)&D_81184656)[arg0] >= 2) {
        return 1;
    }
    return 0;
}

extern s8 D_81184654;

s32 func_8110CAA4(s32 arg0) {
    if (arg0 == 0xFF) {
        return 1;
    }
    if (((u8*)&D_81184654)[arg0] >= 2) {
        return 1;
    }
    return 0;
}

extern s8 D_81184655;
void func_8110CAE0(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    if (arg0 != 0xFF) {
        temp_v0 = arg0 + &D_81184655;
        if (*temp_v0 != 5) {
            *temp_v0 = arg1;
        }
    }
}

extern s8 D_81184656;
void func_8110CB10(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    if (arg0 != 0xFF) {
        temp_v0 = arg0 + &D_81184656;
        if (*temp_v0 != 5) {
            *temp_v0 = arg1;
        }
    }
}

extern s8 D_81184654;
void func_8110CB40(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    if (arg0 != 0xFF) {
        temp_v0 = arg0 + &D_81184654;
        if (*temp_v0 != 5) {
            *temp_v0 = arg1;
        }
    }
}

void func_8110CB70(s8 *arg0, s32 arg1, unsigned short arg2)
{
  s32 var_v0;
  s8 *var_a2;
  *((s16 *) (((s8 *) arg0) + 2)) = arg2;
  *((s32 *) (((s8 *) arg0) + 4)) = arg1;
  var_v0 = 0;
  if ((*((s16 *) (((s8 *) arg0) + 0))) > 0)
  {
 var_a2 = arg0; do { var_v0 += 1; if (((*((s32 *) (((s8 *) var_a2) + 0x14))) != 0) && ((*((s8 *) (((s8 *) var_a2) + 0x18))) == 2)) {
        *((s32 *) (((s8 *) var_a2) + 0x10)) = (s32) ((*((s32 *) (((s8 *) var_a2) + 0x10))) + arg1);
      }
      var_a2 += 0x10;
 } while (var_v0 < (*((s16 *) (((s8 *) arg0) + 0)))); }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110CBD0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110CBD0.s")
#endif

extern u16 D_811858AC;
s32 func_8110D7B0(M2C_UNK, s32);
void func_8110CBD0(s32, void*);
void func_8110D3D4(s32);
void func_8110CC94(s32 arg0, s32 arg1) {
    s32 sp18[2];

    if (arg0 < D_811858AC) {
        arg0 = func_8110D7B0(0, arg0);
        if (arg1 & 2) {
            func_8110CBD0(arg0, sp18);
        }
        if (arg1 & 1) {
            func_8110D3D4(arg0);
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110CD0C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110CD0C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110CDF0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110CDF0.s")
#endif

M2C_UNK func_8004CFB0(s32, M2C_UNK, M2C_UNK);       /* extern */
s32 func_8110D7B0(M2C_UNK, s32);                    /* extern */
s32 func_8110DCC0(M2C_UNK, s32, s32, s32, s32);     /* extern */

void func_8110CEC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_8110DCC0(2, func_8110D7B0(2, arg0), arg1, arg2, arg3) == 0) {
        func_8004CFB0(arg3, 0, 0);
    }
}

extern u8* D_811858A8;
void func_8110CF24(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 off;
    s32 count;

    off = ((u16*)D_811858A8)[func_8110D7B0(0, arg0)];
    count = *(off + D_811858A8);
    off++;
    while (count > 0) {
        func_8110DCC0(1, func_8110D7B0(1, D_811858A8[off++]), arg1, arg2, arg3);
        count--;
    }
}

u8* func_8110CFEC(s32 index, s32* outCount) {
    s32 offset = ((u16*)D_811858A8)[func_8110D7B0(0, index)];

    *outCount = D_811858A8[offset++];
    if (*outCount == 0) {
        return NULL;
    }
    return D_811858A8 + offset;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110D054; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110D054.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110D110; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110D110.s")
#endif

typedef struct Slot8110D214 {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ char unk004[0x158];
} Slot8110D214; // size = 0x15C
extern Slot8110D214 D_81184740[];

s32 func_8110D278(s32, s32, s32);
s32 func_8110D1B8(s32 arg0, s32 arg1, s32 arg2) {
    if (D_811859D4 != 0) {
        return 0;
    }
    D_81184740[arg0].unk_000 = 0;
    return func_8110D278(arg0, arg1, arg2);
}

s32 func_8110D278(s32, s32, s32);
s32 func_8110D214(s32 arg0, s32 arg1, s32 arg2) {
    if (D_811859D4 != 0) {
        return 0;
    }
    D_81184740[arg0].unk_000 = arg2;
    return func_8110D278(arg0, arg1, 0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110D278; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110D278.s")
#endif

s32 func_8110D7B0(s32, s32);
s32 func_8110D5BC(s32, s32, s32*);
void func_8110D3D4(s32 arg0) {
    s32 index;
    s32 output;

    index = func_8110D7B0(0, arg0);
    func_8110D5BC(0, index, &output);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110D408; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110D408.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110D4E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110D4E0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110D5BC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110D5BC.s")
#endif

u8* func_8110D840(s32);
s32 func_8110D7B0(s32 arg0, s32 arg1) {
    s32* entry = (s32*)(func_8110D840(arg0) + arg1 * 16);

    if (entry[5] == 0) {
        arg1 = entry[4];
    }
    return arg1;
}

s32 func_8110A310(s32, M2C_UNK, s32);               /* extern */

s32 func_8110D7EC(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = func_8110B880(arg0, arg1);
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = func_8110A310(arg0, 2, arg1);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

extern u8* D_8118589C;
extern u8* D_811858A0;
extern u8* D_811858A4;
u8* func_8110D840(s32 index) {
    u8* result;

    switch (index) {
    case 0:
        result = D_8118589C;
        break;
    case 1:
        result = D_811858A0;
        break;
    case 2:
        result = D_811858A4;
        break;
    default:
        result = NULL;
        break;
    }
    return result;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110D884; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110D884.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110DA68; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110DA68.s")
#endif

void func_8110DB8C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {

}

#ifdef NON_MATCHING
/* TODO: decompile func_8110DBA0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110DBA0.s")
#endif
