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
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 pad0E[0x14 - 0x0E];
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 pad16[0x1C - 0x16];
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ u8 pad20[0x38 - 0x20];
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

extern u8 D_81184654[1];
extern u8 D_81184655[1];
extern u8 D_81184656[1];

void func_811095E0(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_81184655[i] != 5) {
            D_81184655[i] = 0;
        }
    }
    for (i = 0; i < 1; i++) {
        if (D_81184654[i] != 5) {
            D_81184654[i] = 0;
        }
    }
    for (i = 0; i < 1; i++) {
        if (D_81184656[i] != 5) {
            D_81184656[i] = 0;
        }
    }
}

/* One 0xCC-byte record; only the fields func_81109678 touches are named. */
typedef struct Rec81109678Flags {
    /* 0x0 */ u8 bit7 : 1;
    /* 0x0 */ u8 bit6 : 1;
    /* 0x0 */ u8 rest : 6;
} Rec81109678Flags;

typedef struct Rec81109678 {
    /* 0x00 */ u8 pad00[0x30];
    /* 0x30 */ u8 unk_30;
    /* 0x31 */ u8 pad31[2];
    /* 0x33 */ u8 unk_33;
    /* 0x34 */ u8 unk_34;
    /* 0x35 */ u8 pad35[0x44 - 0x35];
    /* 0x44 */ Rec81109678Flags* unk_44;
    /* 0x48 */ u8 pad48[0x5C - 0x48];
    /* 0x5C */ u8 unk_5C;
    /* 0x5D */ u8 unk_5D;
    /* 0x5E */ u8 pad5E[0x6C - 0x5E];
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ u8 pad70[0xB4 - 0x70];
    /* 0xB4 */ u32 enabled : 1;
    /* 0xB4 */ u32 restB4 : 31;
    /* 0xB8 */ u8 padB8[0xCC - 0xB8];
} Rec81109678; // size = 0xCC

s32 func_8111073C(Rec81109678*);
s32 func_811114BC(Rec81109678*);
s32 func_81112EAC(s8*, Rec81109678*);
extern Rec81109678* D_81184664;
extern s8 D_81184938;
extern s32 D_811858E8;

/*
 * func_81109678
 *
 * Walks the D_811858E8 records of the array at D_81184664 (0xCC bytes each,
 * the array pointer is re-read on every iteration). For each record whose
 * byte at 0x33 equals arg0: if the bytes at 0x34 and 0x30 are 0 and non-zero
 * respectively, it clears bit 7 and then sets bit 6 of the byte that the
 * pointer at 0x44 points to. In every matching record it then calls
 * func_8111073C(rec), func_811114BC(rec) and func_81112EAC(&D_81184938, rec).
 * Records whose byte at 0x33 differs are skipped. What the record and the
 * flag bits mean is not established from this function.
 *
 * Matching notes: the two single-bit writes are declared as bit-fields; the
 * bit-field form gives the retail `andi 0xFF7F` / `ori 0x40` read-modify-write
 * sequences and register numbering (a plain `&= 0xFF7F; |= 0x40` on a byte
 * was one temporary register off). Indexing the array with the loop counter,
 * instead of a separate byte offset, gives the retail loop setup order.
 */
void func_81109678(s32 arg0) {
    s32 i;
    Rec81109678* p;

    for (i = 0; i < D_811858E8; i++) {
        p = &D_81184664[i];
        if (arg0 == p->unk_33) {
            if ((p->unk_34 == 0) && (p->unk_30 != 0)) {
                p->unk_44->bit7 = 0;
                p->unk_44->bit6 = 1;
            }
            func_8111073C(p);
            func_811114BC(p);
            func_81112EAC(&D_81184938, p);
        }
    }
}

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

M2C_UNK func_811098C0(M2C_UNK *, s32, s32);
extern M2C_UNK D_81184290;
extern M2C_UNK D_811842B0;
extern u8 D_81186270[];
extern s32 D_811526FC;
extern s32 D_811842A0;

/**
 * Runs func_811098C0 twice: first on D_811842B0 with the buffer D_81186270 and
 * length arg0, then on D_81184290 with the remainder of the buffer (starting
 * at arg0 and D_811526FC - arg0 long). Finally clears D_811842A0. What
 * func_811098C0 does with its arguments is not established.
 */
void func_8110993C(s32 arg0) {
    func_811098C0(&D_811842B0, (s32)D_81186270, arg0);
    func_811098C0(&D_81184290, (s32)(D_81186270 + arg0), D_811526FC - arg0);
    D_811842A0 = 0;
}

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

typedef struct CacheEntry81109C0C {
    /* 0x00 */ u8* ramAddr;
    /* 0x04 */ u32 size;
    /* 0x08 */ s16 tableType;
    /* 0x0A */ s16 id;
} CacheEntry81109C0C; // size = 0xC

typedef struct Pool81109C0C {
    /* 0x00 */ u8* startRamAddr;
    /* 0x04 */ u8* curRamAddr;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 numEntries;
} Pool81109C0C; // size = 0x10

typedef struct PersistentCache81109C0C {
    /* 0x00 */ s32 numEntries;
    /* 0x04 */ Pool81109C0C pool;
    /* 0x14 */ CacheEntry81109C0C entries[1];
} PersistentCache81109C0C; // size = 0x20

typedef struct TemporaryCache81109C0C {
    /* 0x00 */ s32 nextSide;
    /* 0x04 */ Pool81109C0C pool;
    /* 0x14 */ CacheEntry81109C0C entries[2];
} TemporaryCache81109C0C; // size = 0x2C

typedef struct Cache81109C0C {
    /* 0x00 */ PersistentCache81109C0C persistent;
    /* 0x20 */ TemporaryCache81109C0C temporary;
} Cache81109C0C;

typedef struct SeqPlayer81109C0C {
    /* 0x000 */ u32 enabled : 1;
    /* 0x000 */ u32 rest0 : 31;
    /* 0x004 */ u8 seqId;
    /* 0x005 */ u8 pad5[0x15C - 0x5];
} SeqPlayer81109C0C; // size = 0x15C

extern u8 D_81184654[1];
extern u8 D_81184655[1];
extern u8 D_81184656[1];
void func_8110CAE0(s32, s32);

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

typedef struct Entry8110A368 { s32 val; char pad4[6]; s16 key; } Entry8110A368;
typedef struct Tbl8110A368 { u32 count; char pad4[0x10]; Entry8110A368 entries[1]; } Tbl8110A368;
s32 func_8110A368(s32 arg0, s32 arg1, s32 arg2) {
    Tbl8110A368* sub;
    Tbl8110A368* tbl;
    u32 i;
    switch (arg0) {
    case 0:
        tbl = (Tbl8110A368*)&D_81184320;
        break;
    case 1:
        tbl = (Tbl8110A368*)&D_81184380;
        break;
    case 2:
        tbl = (Tbl8110A368*)&D_811843E0;
        break;
    }
    sub = (Tbl8110A368*)((u8*)tbl + 0x20);
    if (arg1 == 0) {
        if (arg2 == sub->entries[0].key) {
            sub->count = 1;
            return sub->entries[0].val;
        }
        if (arg2 == sub->entries[1].key) {
            sub->count = 0;
            return sub->entries[1].val;
        }
        return 0;
    }
    sub = tbl;
    for (i = 0; i < sub->count; i++) {
        if (arg2 == tbl->entries[i].key) {
            return tbl->entries[i].val;
        }
    }
    if (arg1 == 2) {
        return func_8110A310(arg0, 0, arg2);
    }
    return 0;
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
/**
 * Unused in the code seen so far. Fills out[0..15] from two recurrences in p
 * and q seeded with 262159.0f; as in the Ocarina of Time version
 * (func_800DDF80) the first loop writes to out instead of tmp, so the second
 * loop copies partly uninitialised values.
 */
void func_8110A474(f32 p, f32 q, u16* out) {
    s32 i;
    f32 tmp[16];

    tmp[0] = (f32)(q * 262159.0f);
    tmp[8] = (f32)(p * 262159.0f);
    tmp[1] = (f32)((q * p) * 262159.0f);
    tmp[9] = (f32)(((p * p) + q) * 262159.0f);

    for (i = 2; i < 8; i++) {
        out[i] = q * tmp[i - 2] + p * tmp[i - 1];
        out[8 + i] = q * tmp[6 + i] + p * tmp[7 + i];
    }

    for (i = 0; i < 16; i++) {
        out[i] = tmp[i];
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110A474.s")
#endif

/*
 * func_8110A848
 *
 * Sets the eight s16 values at arg0 to zero (the loop is unrolled by four in
 * the retail code).
 */
void func_8110A848(s16* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        arg0[i] = 0;
    }
}

extern s16 D_811371D8[];

/*
 * func_8110A878
 *
 * Copies eight s16 values into arg0 from entry arg1 of the table at
 * D_811371D8 (entries are 8 s16 = 16 bytes long; the loop is unrolled by four
 * in the retail code).
 */
void func_8110A878(s16* arg0, s32 arg1) {
    s16* src;
    s32 i;

    src = &D_811371D8[arg1 * 8];
    for (i = 0; i < 8; i++) {
        arg0[i] = src[i];
    }
}

extern s16 D_811373C8[];

/*
 * func_8110A8CC
 *
 * Copies eight s16 values into arg0 from the table at D_811373C8. The entry is
 * numbered from 1: entry arg1 starts at D_811373C8 + (arg1 - 1) * 16 bytes
 * (8 s16 per entry; the loop is unrolled by four in the retail code).
 */
void func_8110A8CC(s16* arg0, s32 arg1) {
    s16* src;
    s32 i;

    src = &D_811373C8[arg1 * 8 - 8];
    for (i = 0; i < 8; i++) {
        arg0[i] = src[i];
    }
}

void func_8110A924(s16* arg0, s32 arg1, s32 arg2) {
    s32 i;

    if ((arg1 == 0) && (arg2 == 0)) {
        func_8110A878(arg0, 0);
    } else if (arg2 == 0) {
        func_8110A878(arg0, arg1);
    } else if (arg1 == 0) {
        func_8110A8CC(arg0, arg2);
    } else {
        for (i = 0; i < 8; i++) {
            arg0[i] = (D_811371D8[arg2 * 8 + i] + D_811373C8[arg2 * 8 + i]) / 2;
        }
    }
}

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

extern s16 D_811858C2;

void func_8110AC14(void) {
    s32 idx = D_811858FC;
    s32 i;

    D_811859C4[idx] = D_811858C2;
    for (i = 0; i < 0x7E0; i++) {
        D_811859B8[idx][i] = 0;
    }
}

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
    /* 0x4 */ s32 unk_4;
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

s32 func_8110B8D8(s32 x, s32 y, s32 size) {
    UNUSED s32 pad;
    s32 index = D_81184440.unk_0C;

    D_81184440.unk_10[index].unk_0 = func_81109868((M2C_UNK*)&D_81184440, size);
    if (D_81184440.unk_10[index].unk_0 == 0) {
        return 0;
    }
    D_81184440.unk_10[index].unk_8 = x;
    D_81184440.unk_10[index].unk_A = y;
    D_81184440.unk_10[index].unk_4 = size;
    // No return here; the original falls off the end with the allocation still in v0.
}

struct SampleCacheEntry8110BA8C* func_8110BA8C(u32);
s32 func_8110B958(s32 arg0, s32 arg1, s32 arg2, s8 arg3) {
    s8* p = (s8*)func_8110BA8C(arg0);

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
typedef struct SampleCacheEntry8110BA8C {
    /* 0x00 */ s8 inUse;
    /* 0x01 */ s8 origMedium;
    /* 0x02 */ s8 sampleBankId;
    /* 0x04 */ s32 sampleAddr;
    /* 0x08 */ u8* allocatedAddr;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u32 size;
} SampleCacheEntry8110BA8C; // size = 0x14

typedef struct SampleCache8110BA8C {
    /* 0x00 */ u8* startRamAddr;
    /* 0x04 */ u8* curRamAddr;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 numAllocatedEntries;
    /* 0x10 */ SampleCacheEntry8110BA8C entries[1];
    /* 0x24 */ s32 numEntries;
} SampleCache8110BA8C;

typedef struct PreloadSample8110BA8C {
    /* 0x00 */ u32 unk_bits : 8;
    /* 0x00 */ u32 size : 24;
} PreloadSample8110BA8C;

typedef struct Preload8110BA8C {
    /* 0x00 */ u32 endAndMediumKey;
    /* 0x04 */ PreloadSample8110BA8C* sample;
    /* 0x08 */ u8* ramAddr;
    /* 0x0C */ u32 encodedInfo;
    /* 0x10 */ s32 isFree;
} Preload8110BA8C; // size = 0x14

extern SampleCache8110BA8C D_811845F8;
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
        func_811098C0((M2C_UNK*)&D_811845F8, temp_v0_2, arg1);
    }
    D_811845F4 = 0;
    D_8118461C = 0;
}

extern Preload8110BA8C D_81184B78[];
extern s32 D_8118557C;
void func_8110BD20(SampleCacheEntry8110BA8C*);

SampleCacheEntry8110BA8C* func_8110BA8C(u32 size) {
    u8* allocAfter;
    u8* allocBefore;
    void* mem;
    s32 index;
    s32 i;
    SampleCacheEntry8110BA8C* entry;
    Preload8110BA8C* preload;
    SampleCache8110BA8C* cache;
    u8* startRamAddr;
    u8* endRamAddr;

    cache = &D_811845F8;
    allocBefore = cache->curRamAddr;
    mem = (void*)func_81109868((M2C_UNK*)cache, size);
    if (mem == NULL) {
        u8* old = cache->curRamAddr;

        cache->curRamAddr = cache->startRamAddr;
        mem = (void*)func_81109868((M2C_UNK*)cache, size);
        if (mem == NULL) {
            cache->curRamAddr = old;
            return NULL;
        }
        allocBefore = cache->startRamAddr;
    }

    allocAfter = cache->curRamAddr;

    index = -1;
    for (i = 0; i < D_8118557C; i++) {
        preload = &D_81184B78[i];
        if (preload->isFree == 0) {
            startRamAddr = preload->ramAddr;
            endRamAddr = preload->ramAddr + preload->sample->size - 1;

            if (endRamAddr < allocBefore && startRamAddr < allocBefore) {
                continue;
            }
            if (endRamAddr >= allocAfter && startRamAddr >= allocAfter) {
                continue;
            }

            preload->isFree = 1;
        }
    }

    for (i = 0; i < cache->numEntries; i++) {
        if (!cache->entries[i].inUse) {
            continue;
        }

        startRamAddr = cache->entries[i].allocatedAddr;
        endRamAddr = startRamAddr + cache->entries[i].size - 1;

        if (endRamAddr < allocBefore && startRamAddr < allocBefore) {
            continue;
        }
        if (endRamAddr >= allocAfter && startRamAddr >= allocAfter) {
            continue;
        }

        func_8110BD20(&cache->entries[i]);
        if (index == -1) {
            index = i;
        }
    }

    if (index == -1) {
        index = cache->numEntries++;
    }

    entry = &cache->entries[index];
    entry->inUse = 1;
    entry->allocatedAddr = mem;
    entry->size = size;

    return entry;
}

/* One-byte flags field; only the 2-bit value at bits 2-3 is touched by func_8110BEE4. */
typedef struct {
    u8 pad0 : 4;
    u8 field : 2;
    u8 pad1 : 2;
} Flags2Bit;

typedef struct Entry8110D4E0 { u8 unk00; u8 unk01; u8 unk02; u8 unk03; u8** instruments; u8** drums; } Entry8110D4E0;
extern Entry8110D4E0* D_811858B0;
extern u8* D_811858A0;
s32 func_8110CA2C(s32 arg0);
u8* func_81110CA8(s32, s32);
u8* func_81110D6C(s32, s32);

void func_8110BEE4(u8* arg0, Flags2Bit* arg1);

void func_8110BD20(SampleCacheEntry8110BA8C* entry) {
    u8* inst;
    s32 numFonts;
    s32 fontId;
    s32 sampleBankId1;
    s32 sampleBankId2;
    s32 instId;
    u8* drum;
    s32 drumId;

    numFonts = *(s16*)D_811858A0;
    for (fontId = 0; fontId < numFonts; fontId++) {
        sampleBankId1 = D_811858B0[fontId].unk02;
        sampleBankId2 = D_811858B0[fontId].unk03;
        if (((sampleBankId1 != 0xFF) && (entry->sampleBankId == sampleBankId1)) ||
            ((sampleBankId2 != 0xFF) && (entry->sampleBankId == sampleBankId2)) || entry->sampleBankId == 0) {
            if (func_8110A310(1, 2, fontId) != 0) {
                if (func_8110CA2C(fontId) != 0) {
                    for (instId = 0; instId < D_811858B0[fontId].unk00; instId++) {
                        inst = func_81110CA8(fontId, instId);
                        if (inst != NULL) {
                            if (inst[1] != 0) {
                                func_8110BEE4((u8*)entry, M2C_FIELD(inst, Flags2Bit**, 8));
                            }
                            if (inst[2] != 0x7F) {
                                if (1) {
                                    func_8110BEE4((u8*)entry, M2C_FIELD(inst, Flags2Bit**, 0x18));
                                }
                            }
                            func_8110BEE4((u8*)entry, M2C_FIELD(inst, Flags2Bit**, 0x10));
                        }
                    }
                    for (drumId = 0; drumId < D_811858B0[fontId].unk01; drumId++) {
                        drum = func_81110D6C(fontId, drumId);
                        if (drum != NULL) {
                            func_8110BEE4((u8*)entry, M2C_FIELD(drum, Flags2Bit**, 4));
                        }
                    }
                }
            }
        }
    }
}

/*
 * func_8110BEE4
 *
 * If arg1 is non-NULL and the word at arg0 + 0x08 equals the word at
 * arg1 + 0x04, copies the word at arg0 + 0x0C into arg1 + 0x04 and stores the
 * low two bits of the signed byte at arg0 + 0x01 into bits 2-3 of the byte at
 * arg1 + 0x00 (a bit-field write: the retail code masks with 0xFFF3 / 0x0C).
 */
void func_8110BEE4(u8* arg0, Flags2Bit* arg1) {
    if ((arg1 != NULL) && (M2C_FIELD(arg0, s32*, 8) == M2C_FIELD(arg1, s32*, 4))) {
        M2C_FIELD(arg1, s32*, 4) = M2C_FIELD(arg0, s32*, 0xC);
        arg1->field = M2C_FIELD(arg0, s8*, 1);
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


void func_8110BFB0(void) {
    UNUSED s32 pad2[1];
    s32 j;
    s32 count;
    UNUSED s32 pad[5];
    s32 a;
    s32 b;
    s8* slot;
    s32 k;
    s32 m;
    s32 i;
    u8* p;
    s32 off;

    count = *(s16*)D_811858A0;
    for (i = 0; i < count; i++) {
        a = D_811858B0[i].unk02;
        b = D_811858B0[i].unk03;
        if ((a != 0xFF) || (b != 0xFFU)) {
            off = 0x12;
            if ((func_8110A310(1, 3, i) != 0) && (func_8110CA2C(i) != 0)) {
                slot = (s8*)&D_811845D0;
                for (j = 0; j < D_811845F4; j++, slot += 0x14) {
                    if ((a != slot[off]) && (b != slot[0x12]) && (slot[0x12] != 0)) {
                        break;
                    }
                    {
                        for (k = 0; k < D_811858B0[i].unk00; k++) {
                            p = func_81110CA8(i, k);
                            if (p != NULL) {
                                if (p[1] != 0) {
                                    func_8110BEE4(slot + 0x10, M2C_FIELD(p, Flags2Bit**, 8));
                                }
                                if (p[2] != 0x7F) {
                                    func_8110BEE4(slot + 0x10, M2C_FIELD(p, Flags2Bit**, 0x18));
                                }
                                func_8110BEE4(slot + 0x10, M2C_FIELD(p, Flags2Bit**, 0x10));
                            }
                        }
                        for (m = 0; m < D_811858B0[i].unk01; m++) {
                            p = func_81110D6C(i, m);
                            if (p != NULL) {
                                func_8110BEE4(slot + 0x10, M2C_FIELD(p, Flags2Bit**, 4));
                            }
                        }
                    }
                }
            }
        }
    }
}

typedef struct Timer8110C1C0 {
    /* 0x00 */ u8* ramAddr;
    /* 0x04 */ u32 devAddr;
    /* 0x08 */ u16 sizeUnused;
    /* 0x0A */ u16 size;
    /* 0x0C */ u8 unused;
    /* 0x0D */ u8 slot;
    /* 0x0E */ u8 count;
} Timer8110C1C0; // size = 0x10
extern Timer8110C1C0* D_81185688;
extern u32 D_8118568C;
extern u32 D_81185690;
extern s32 D_81185694;
extern u8 D_81185698[];
extern u8 D_81185798[];
extern u8 D_8118589A;
extern u8 D_8118589B;
void func_8110C1C0(void) {
    u32 i;
    Timer8110C1C0* t;
    for (i = 0; i < D_81185690; i++) {
        t = &D_81185688[i];
        if (t->count != 0) {
            if (--t->count == 0) {
                t->slot = D_8118589A;
                D_81185698[D_8118589A++] = i;
            }
        }
    }
    for (i = D_81185690; i < D_8118568C; i++) {
        t = &D_81185688[i];
        if (t->count != 0) {
            if (--t->count == 0) {
                t->slot = D_8118589B;
                D_81185798[D_8118589B++] = i;
            }
        }
    }
    D_81185694 = 0;
}

extern u8 D_81185898;
extern u8 D_81185899;
extern u8 D_81185638[];
extern u32 D_811858F4;
extern u8 D_81185618[];
extern s8 D_81137ACC[];
s32 func_8110DBA0();

void* func_8110C2D8(u32 devAddr, u32 size, s32 arg2, u8* dmaIndexRef, s32 medium) {
    UNUSED s32 pad1;
    Timer8110C1C0* dma;
    s32 hasDma = FALSE;
    u32 dmaDevAddr;
    UNUSED u32 pad2;
    u32 dmaIndex;
    u32 transfer;
    s32 bufferPos;
    u32 i;

    if (arg2 != 0 || *dmaIndexRef >= D_81185690) {
        for (i = D_81185690; i < D_8118568C; i++) {
            dma = &D_81185688[i];
            bufferPos = devAddr - dma->devAddr;
            if (0 <= bufferPos && (u32)bufferPos <= (dma->size - size)) {
                if (dma->count == 0 && D_81185899 != D_8118589B) {
                    if (dma->slot != D_81185899) {
                        D_81185798[dma->slot] = D_81185798[D_81185899];
                        D_81185688[D_81185798[D_81185899]].slot = dma->slot;
                    }
                    D_81185899++;
                }
                dma->count = 32;
                *dmaIndexRef = (u8)i;
                return (dma->ramAddr + devAddr) - dma->devAddr;
            }
        }

        if (D_81185899 != D_8118589B && arg2 != 0) {
            dmaIndex = D_81185798[D_81185899];
            D_81185899++;
            dma = D_81185688 + dmaIndex;
            hasDma = TRUE;
        }
    } else {
        dma = D_81185688 + *dmaIndexRef;
        bufferPos = devAddr - dma->devAddr;
        if (0 <= bufferPos && (u32)bufferPos <= dma->size - size) {
            if (dma->count == 0) {
                if (dma->slot != D_81185898) {
                    D_81185698[dma->slot] = D_81185698[D_81185898];
                    D_81185688[D_81185698[D_81185898]].slot = dma->slot;
                }
                D_81185898++;
            }
            dma->count = 2;
            return (dma->ramAddr + devAddr) - dma->devAddr;
        }
    }

    if (!hasDma) {
        if (D_81185898 == D_8118589A) {
            return NULL;
        }
        dmaIndex = D_81185698[D_81185898++];
        dma = D_81185688 + dmaIndex;
        hasDma = TRUE;
    }

    transfer = dma->size;
    dmaDevAddr = devAddr & ~0xF;
    dma->count = 3;
    dma->devAddr = dmaDevAddr;
    dma->sizeUnused = transfer;
    func_8110DBA0(&D_81185638[D_811858F4++ * 0x18], 0, 0, dmaDevAddr, dma->ramAddr, transfer, D_81185618, medium, D_81137ACC);
    *dmaIndexRef = dmaIndex;
    return (devAddr - dmaDevAddr) + dma->ramAddr;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110C618; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110C618.s")
#endif

extern u8 D_81184655[1];

s32 func_8110CA2C(s32 arg0) {
    if (arg0 == 0xFF) {
        return 1;
    }
    if (((u8*)&D_81184655)[arg0] >= 2) {
        return 1;
    }
    return 0;
}

extern u8 D_81184656[1];

s32 func_8110CA68(s32 arg0) {
    if (arg0 == 0xFF) {
        return 1;
    }
    if (((u8*)&D_81184656)[arg0] >= 2) {
        return 1;
    }
    return 0;
}

extern u8 D_81184654[1];

s32 func_8110CAA4(s32 arg0) {
    if (arg0 == 0xFF) {
        return 1;
    }
    if (((u8*)&D_81184654)[arg0] >= 2) {
        return 1;
    }
    return 0;
}

extern u8 D_81184655[1];
void func_8110CAE0(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    if (arg0 != 0xFF) {
        temp_v0 = arg0 + &D_81184655;
        if (*temp_v0 != 5) {
            *temp_v0 = arg1;
        }
    }
}

extern u8 D_81184656[1];
void func_8110CB10(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    if (arg0 != 0xFF) {
        temp_v0 = arg0 + &D_81184656;
        if (*temp_v0 != 5) {
            *temp_v0 = arg1;
        }
    }
}

extern u8 D_81184654[1];
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

extern u8* D_811858A8;
extern u16 D_811858AC;
s32 func_8110D7B0(M2C_UNK, s32);
s32 func_8110D4E0(s32);

s32 func_8110CBD0(s32 arg0, s32* arg1) {
    s32 off;
    s32 count;
    u8 id;
    s32 ret;

    if (arg0 >= D_811858AC) {
        return 0;
    }
    off = ((u16*)D_811858A8)[func_8110D7B0(0, arg0)];
    id = 0xFF;
    count = *(off + D_811858A8);
    off++;
    while (count > 0) {
        id = D_811858A8[off++];
        ret = func_8110D4E0(id);
        count--;
    }
    *arg1 = id;
    return ret;
}

extern u16 D_811858AC;
s32 func_8110D7B0(M2C_UNK, s32);
s32 func_8110CBD0(s32, s32*);
s32 func_8110D3D4(s32);
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

typedef struct Stream8110CD0C {
    /* 0x00 */ u32 unk00_0 : 4;
    /* 0x00 */ u32 mode : 2;
    /* 0x00 */ u32 unk00_6 : 1;
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 addr : 24;
    /* 0x04 */ s32 unk04;
} Stream8110CD0C;
void func_8110DB8C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3);
void func_8110DA68(s32, s32, u32, s32);
extern u8* D_811858A4;
s32 func_8110CD0C(Stream8110CD0C* arg0, s32 arg1) {
    s32 ret;

    if (arg0->enabled == 1) {
        if (arg0->mode != 0) {
            ret = func_8110B9A8(arg0->addr, arg1, arg0->unk04, arg0->mode);
            if (ret == 0) {
                return -1;
            }
            if (arg0->mode == 1) {
                func_8110DB8C(arg0->unk04, ret, arg0->addr, *(s16*)(D_811858A4 + 2));
            } else {
                func_8110DA68(arg0->unk04, ret, arg0->addr, arg0->mode);
            }
            arg0->mode = 0;
            arg0->unk04 = ret;
        }
    }
}

u8* func_81110CA8(s32, s32);
u8* func_81110D6C(s32, s32);
s32 func_8110CDF0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p;

    if (arg1 < 0x7F) {
        p = func_81110CA8(arg0, arg1);
        if (p == NULL) {
            return -1;
        }
        if (p[1] != 0) {
            func_8110CD0C(M2C_FIELD(p, Stream8110CD0C **, 8), arg0);
        }
        func_8110CD0C(M2C_FIELD(p, Stream8110CD0C **, 0x10), arg0);
        if (p[2] != 0x7F) {
            func_8110CD0C(M2C_FIELD(p, Stream8110CD0C **, 0x18), arg0);
        }
    } else if (arg1 == 0x7F) {
        p = func_81110D6C(arg0, arg2);
        if (p == NULL) {
            return -1;
        }
        func_8110CD0C(M2C_FIELD(p, Stream8110CD0C **, 4), arg0);
        return 0;
    }
}

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

u8* func_8110CFEC(s32 arg0, s32* arg1) {
    s32 off;

    off = ((u16*)D_811858A8)[func_8110D7B0(0, arg0)];
    *arg1 = *(off + D_811858A8);
    off++;
    if (*arg1 == 0) {
        return NULL;
    }
    return D_811858A8 + off;
}

void func_8110D110(s32 arg0);

void func_8110D054(s32 arg0) {
    s32 off;
    s32 count;
    s32 id;

    off = ((u16*)D_811858A8)[func_8110D7B0(0, arg0)];
    count = *(off + D_811858A8);
    off++;
    while (count > 0) {
        count--;
        id = func_8110D7B0(1, D_811858A8[off++]);
        if (func_8110B880(1, id) == 0) {
            func_8110D110(id);
            func_8110CAE0(id, 0);
        }
    }
}

extern s16 D_811843BE;
extern s16 D_811843CA;
void func_8110D110(s32 arg0) {
    Tbl8110A368* tbl2;
    s32 none;
    Tbl8110A368* tbl = (Tbl8110A368*)&D_81184380;
    u32 i;

    none = -1;
    if (arg0 == ((Tbl8110A368*)((u8*)tbl + 0x20))->entries[0].key) {
        D_811843BE = none;
    } else if (arg0 == D_811843CA) {
        D_811843CA = none;
    }
    tbl2 = tbl;
    for (i = 0; i < tbl2->count; i++) {
        if (arg0 == tbl2->entries[i].key) {
            tbl2->entries[i].key = none;
        }
    }
    func_81109678(arg0);
}

typedef struct Slot8110D214 {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ char unk004[0x158];
} Slot8110D214; // size = 0x15C
extern Slot8110D214 D_81184740[];
s32 func_8110D278(s32, s32, s32);

/**
 * Clears the first word of slot arg0 in the D_81184740 array (stride 0x15C) and
 * returns func_8110D278(arg0, arg1, arg2); returns 0 without touching anything if
 * D_811859D4 is nonzero. arg1 and arg2 are passed through unchanged. Sibling of
 * func_8110D214, which stores its arg2 instead of 0 and passes 0 as the last argument.
 * What the slot and the flag mean is not established.
 */
s32 func_8110D1B8(s32 arg0, s32 arg1, s32 arg2) {
    if (D_811859D4 != 0) {
        return 0;
    }
    D_81184740[arg0].unk_000 = 0;
    return func_8110D278(arg0, arg1, arg2);
}

s32 func_8110D214(s32 arg0, s32 arg1, s32 arg2) {
    if (D_811859D4 != 0) {
        return 0;
    }
    D_81184740[arg0].unk_000 = arg2;
    return func_8110D278(arg0, arg1, 0);
}

typedef struct Flags8110D278 {
    u8 b80 : 1;
    u8 b40 : 1;
    u8 rest : 6;
} Flags8110D278;
s32 func_8110D3D4(s32);
void func_811152A4(s32);
void func_81115254(s8*);
s32 func_8110D278(s32 arg0, s32 arg1, s32 arg2) {
    s8* slot;
    u8 id;
    s32 count;
    s32 off;
    s32 r;
    s32 i;

    if (arg1 >= D_811858AC) {
        return 0;
    }
    slot = &D_81184668 + arg0 * 0x15C;
    arg1 = func_8110D7B0(0, arg1);
    func_81112E00(slot);
    id = 0xFF;
    /* do-while(0) block (likely a macro in the original) is required for the register choice */
    do {
        off = ((u16*)D_811858A8)[arg1];
        count = *(off + D_811858A8);
        off++;
    } while (0);
    while (count > 0) {
        id = D_811858A8[off++];
        func_8110D4E0(id);
        count--;
    }
    r = func_8110D3D4(arg1);
    func_811152A4(arg0);
    M2C_FIELD(slot, s8*, 4) = arg1;
    M2C_FIELD(slot, u8*, 5) = id;
    ((Flags8110D278*)slot)->b80 = 1;
    M2C_FIELD(slot, s32*, 0x18) = r;
    M2C_FIELD(slot, s32*, 0x74) = r;
    M2C_FIELD(slot, s8*, 0x8C) = 0;
    M2C_FIELD(slot, s16*, 0x10) = 0;
    ((Flags8110D278*)slot)->b40 = 0;
    func_81115254(slot);
    for (i = 0; i < 16; i++) {
    }
}

s32 func_8110D5BC(s32 tableType, s32 id, s32* didAllocate);

s32 func_8110D3D4(s32 arg0) {
    s32 idx;
    s32 sp18;

    idx = func_8110D7B0(0, arg0);
    func_8110D5BC(0, idx, &sp18);
}

u8* func_8110D840(s32);
s32 func_8110D7EC(s32, s32);
#define ENTRY ((u8*)&((s32(*)[4])table)[arg0])
s32 func_8110D408(s32 arg0, s32* arg1) {
    s32 ret;
    u8* table = func_8110D840(2);
    s32 state;
    s32 sp28;

    arg0 = func_8110D7B0(2, arg0);
    if ((ret = func_8110D7EC(2, arg0)) != 0) {
        func_8110CB40(arg0, 2);
        *arg1 = 0;
        return ret;
    }
    state = (s8)ENTRY[0x19];
    if (state == 4) {
        *arg1 = (s8)ENTRY[0x18];
        return *(s32*)(ENTRY + 0x10);
    }
    if ((ret = func_8110D5BC(2, arg0, &sp28)) != 0) {
        *arg1 = 0;
        return ret;
    }
    *arg1 = (s8)ENTRY[0x18];
    return *(s32*)(ENTRY + 0x10);
}
#undef ENTRY

s32 func_8110D408(s32, s32*);
void func_8110EF7C(s32, s32, s32*, s32);
s32 func_8110D4E0(s32 arg0) {
    s32 ret;
    s32 a;
    s32 b;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp20[4];

    arg0 = func_8110D7B0(1, arg0);
    a = D_811858B0[arg0].unk02;
    b = D_811858B0[arg0].unk03;
    sp20[0] = a;
    sp20[1] = b;
    if (a != 0xFF) {
        sp20[2] = func_8110D408(a, &sp30);
    } else {
        sp20[2] = 0;
    }
    if (b != 0xFF) {
        sp20[3] = func_8110D408(b, &sp34);
    } else {
        sp20[3] = 0;
    }
    ret = func_8110D5BC(1, arg0, &sp38);
    if (ret == 0) {
        return 0;
    }
    if (sp38 == 1) {
        func_8110EF7C(arg0, ret, sp20, 0);
    }
    return ret;
}

typedef struct AudioTableEntry8110D5BC {
    /* 0x00 */ u32 romAddr;
    /* 0x04 */ u32 size;
    /* 0x08 */ s8 medium;
    /* 0x09 */ s8 cachePolicy;
    /* 0x0A */ s16 shortData1;
    /* 0x0C */ s16 shortData2;
    /* 0x0E */ s16 shortData3;
} AudioTableEntry8110D5BC; // size = 0x10

typedef struct AudioTable8110D5BC {
    /* 0x00 */ s16 numEntries;
    /* 0x02 */ s16 unkMediumParam;
    /* 0x04 */ u32 romAddr;
    /* 0x08 */ char pad[0x8];
    /* 0x10 */ AudioTableEntry8110D5BC entries[1];
} AudioTable8110D5BC;

s32 func_81109C0C(s32, s32, s32, s32);

/**
 * Loads entry id of audio table tableType (0 sequences, 1 sound fonts, 2 sample
 * banks) synchronously and returns its RAM address, or 0 if no memory could be
 * allocated. *didAllocate says whether new memory was used (0 when the entry
 * was already cached). The table's load status is updated. Same structure as
 * AudioLoad_SyncLoad in the Ocarina of Time audio library.
 */
s32 func_8110D5BC(s32 tableType, s32 id, s32* didAllocate) {
    u32 size;
    AudioTable8110D5BC* table;
    s32 ramAddr;
    u32 medium;
    s32 status;
    u32 romAddr;
    s32 cachePolicy;
    UNUSED s32 pad;

    ramAddr = func_8110D7EC(tableType, id);
    if (ramAddr != 0) {
        *didAllocate = 0;
        status = 2;
    } else {
        table = (AudioTable8110D5BC*)func_8110D840(tableType);
        size = table->entries[id].size;
        size = ALIGN16(size);
        medium = table->entries[id].medium;
        cachePolicy = table->entries[id].cachePolicy;
        romAddr = table->entries[id].romAddr;
        switch (cachePolicy) {
            case 0:
                ramAddr = func_8110B8D8(tableType, id, size);
                if (ramAddr == 0) {
                    return ramAddr;
                }
                break;
            case 1:
                ramAddr = func_81109C0C(tableType, size, 1, id);
                if (ramAddr == 0) {
                    return ramAddr;
                }
                break;
            case 2:
                ramAddr = func_81109C0C(tableType, size, 0, id);
                if (ramAddr == 0) {
                    return ramAddr;
                }
                break;
            case 3:
            case 4:
                ramAddr = func_81109C0C(tableType, size, 2, id);
                if (ramAddr == 0) {
                    return ramAddr;
                }
                break;
        }

        *didAllocate = 1;
        if (medium == 1) {
            func_8110DB8C(romAddr, ramAddr, size, table->unkMediumParam);
        } else {
            func_8110DA68(romAddr, ramAddr, size, medium);
        }

        status = cachePolicy == 0 ? 5 : 2;
    }

    switch (tableType) {
        case 0:
            func_8110CB10(id, status);
            break;
        case 1:
            func_8110CAE0(id, status);
            break;
        case 2:
            func_8110CB40(id, status);
            break;
    }

    return ramAddr;
}

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

/*
 * func_8110D840
 *
 * Returns the pointer stored in D_8118589C, D_811858A0 or D_811858A4 for
 * arg0 = 0, 1 or 2, and NULL for any other value (the caller treats the result
 * as a byte pointer to a table indexed in 16-byte steps). What the three
 * tables are is not established.
 * Matching note: the result is built in a local and returned once; separate
 * `return` statements in each case give a different register choice.
 */
u8* func_8110D840(s32 arg0) {
    u8* ret;
    ret = NULL;
    switch (arg0) {
    case 0:
        ret = D_8118589C;
        break;
    case 1:
        ret = D_811858A0;
        break;
    case 2:
        ret = D_811858A4;
        break;
    }
    return ret;
}

void func_8110EE3C(void* sampleP, u32 fontDataAddr, void* relocInfo);

/**
 * Relocates a sound font loaded at fontData: the drum and instrument pointer
 * lists, each drum's and instrument's samples and envelope, and records the
 * font's drum and instrument lists in D_811858B0. Same structure as
 * AudioLoad_RelocateFont in the Ocarina of Time audio library.
 */
void func_8110D884(s32 fontId, u32 fontData, void* relocInfo) {
    u32 reloc2;
    u32 reloc;
    s32 i;
    u8* drum;
    u32* ptrs = (u32*)fontData;
    s32 numDrums = D_811858B0[fontId].unk01;
    u8* inst;
    s32 numInstruments = D_811858B0[fontId].unk00;

    reloc2 = ptrs[0];
    if ((reloc2 != 0) && (numDrums != 0)) {
        ptrs[0] = reloc2 + fontData;
        for (i = 0; i < numDrums; i++) {
            reloc = ((u32*)ptrs[0])[i];
            if (reloc != 0) {
                reloc += fontData;
                ((u32*)ptrs[0])[i] = reloc;
                drum = (u8*)reloc;
                if (drum[2] == 0) {
                    func_8110EE3C(drum + 4, fontData, relocInfo);
                    reloc = *(u32*)(drum + 0xC);
                    drum[2] = 1;
                    *(u32*)(drum + 0xC) = reloc + fontData;
                }
            }
        }
    }

    if (numInstruments >= 0x80) {
        numInstruments = 0x7F;
    }

    for (i = 1; i <= numInstruments; i++) {
        if (ptrs[i] != 0) {
            ptrs[i] += fontData;
            inst = (u8*)ptrs[i];
            if (inst[0] == 0) {
                if (inst[1] != 0) {
                    func_8110EE3C(inst + 8, fontData, relocInfo);
                }
                func_8110EE3C(inst + 0x10, fontData, relocInfo);
                if (inst[2] != 0x7F) {
                    func_8110EE3C(inst + 0x18, fontData, relocInfo);
                }
                reloc = *(u32*)(inst + 4);
                inst[0] = 1;
                *(u32*)(inst + 4) = reloc + fontData;
            }
        }
    }

    D_811858B0[fontId].drums = (u8**)ptrs[0];
    D_811858B0[fontId].instruments = (u8**)(ptrs + 1);
}

extern s8 D_81137C1C[];
extern s8 D_81137C28[];
extern u8 D_81185650[];
extern u8 D_81185670[];
void func_80056730(s32, u32);
void func_8004D1C0(void*, s32, s32);
s32 func_8110DBA0();
void func_8110DA68(s32 arg0, s32 arg1, u32 arg2, s32 arg3) {

    arg2 = (arg2 + 0xF) & ~0xF;
    func_80056730(arg1, arg2);
    while (TRUE) {
        if (arg2 < 0x400) {
            break;
        }
        func_8110DBA0(D_81185670, 1, 0, arg0, arg1, 0x400, D_81185650, arg3, D_81137C1C);
        func_8004D1C0(D_81185650, 0, 1);
        arg2 -= 0x400;
        arg0 += 0x400;
        arg1 += 0x400;
    }
    if (arg2 != 0) {
        func_8110DBA0(D_81185670, 1, 0, arg0, arg1, arg2, D_81185650, arg3, D_81137C28);
        func_8004D1C0(D_81185650, 0, 1);
    }
}

void func_8110DB8C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {

}

typedef struct IoMesg8110DBA0 {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 pri;
    /* 0x03 */ u8 status;
    /* 0x04 */ void* retQueue;
    /* 0x08 */ void* dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
} IoMesg8110DBA0;
s32 func_800593D0(void);
s32 func_80051E60(void);
void func_80056530(s32, IoMesg8110DBA0*, s32);
s32 func_8110DBA0(IoMesg8110DBA0* mb, s32 pri, s32 direction, u32 devAddr, void* dramAddr, u32 size, void* mq, s32 kind) {
    s32 handle;

    if ((u32)D_811859D4 > 16) {
        return -1;
    }
    switch (kind) {
        case 2:
            handle = func_800593D0();
            break;
        case 3:
            handle = func_80051E60();
            break;
        default:
            return 0;
    }
    if (size & 0xF) {
        size = (size + 0xF) & ~0xF;
    }
    mb->pri = pri;
    mb->retQueue = mq;
    mb->dramAddr = dramAddr;
    mb->devAddr = devAddr;
    mb->size = size;
    M2C_FIELD(handle, s32*, 0x14) = 2;
    func_80056530(handle, mb, direction);
    return 0;
}
