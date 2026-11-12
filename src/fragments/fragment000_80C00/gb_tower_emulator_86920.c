/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_emulator/gb_tower_emulator_86920.c. */

#include "global.h"
#include "fragments/fragment000_80C00/gb_tower_emulator_86920_types.h"
typedef struct unk_D_81234690 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 pad16[0x18 - 0x16];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ u8 pad28[0x38 - 0x28];
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
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_81109764(s32 arg0)
{
  s32 new_var2; // FAKE: permuter temp
  s8 *new_var; // FAKE: permuter temp
  s32 var_s1;
  var_s1 = 0;
  if (D_811858CC > 0)
  {
    new_var = &D_81184668;
    new_var = new_var; // FAKE: self-assignment
    new_var2 = arg0;
    do
    {
      if (((((u32) (*((u32 *) (((s8 *) new_var) + 0)))) >> 0x1F) != 0) && (new_var2 == (*((u8 *) (((s8 *) new_var) + 4))))) // FAKE: decomp slop, raw pointer casts stand in for struct fields
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



typedef struct PersistentCache81109C0C {
    /* 0x00 */ u32 numEntries;
    /* 0x04 */ Pool81109C0C pool;
    /* 0x14 */ CacheEntry81109C0C entries[1];
} PersistentCache81109C0C; // size = 0x20

typedef struct TemporaryCache81109C0C {
    /* 0x00 */ u32 nextSide;
    /* 0x04 */ Pool81109C0C pool;
    /* 0x14 */ CacheEntry81109C0C entries[2];
} TemporaryCache81109C0C; // size = 0x2C

typedef struct Cache81109C0C {
    /* 0x00 */ PersistentCache81109C0C persistent;
    /* 0x20 */ TemporaryCache81109C0C temporary;
} Cache81109C0C;


extern u8 D_81184654[1];
extern u8 D_81184655[1];
extern u8 D_81184656[1];
void func_8110CAE0(s32, s32);

void* func_81109C0C(s32 tableType, s32 size, s32 cache, s32 id) {
    Cache81109C0C* loadedCache;
    TemporaryCache81109C0C* tCache;
    Pool81109C0C* tempPool;
    void* persistentAddr;
    void* tempAddr;
    u8 loadStatusEntry0;
    u8 loadStatusEntry1;
    s32 i;
    u8* loadStatus;

    switch (tableType) {
        case 0:
            loadedCache = (Cache81109C0C*)&D_81184320;
            loadStatus = D_81184656;
            break;
        case 1:
            loadedCache = (Cache81109C0C*)&D_81184380;
            loadStatus = D_81184655;
            break;
        case 2:
            loadedCache = (Cache81109C0C*)&D_811843E0;
            loadStatus = D_81184654;
            break;
    }

    if (cache == 0) {
        tCache = &loadedCache->temporary;
        tempPool = &tCache->pool;

        if (tCache->entries[0].id == -1) {
            loadStatusEntry0 = 0;
        } else {
            loadStatusEntry0 = loadStatus[tCache->entries[0].id];
        }

        if (tCache->entries[1].id == -1) {
            loadStatusEntry1 = 0;
        } else {
            loadStatusEntry1 = loadStatus[tCache->entries[1].id];
        }

        if (tableType == 1) {
            if (loadStatusEntry0 == 4) {
                for (i = 0; i < D_811858E8; i++) {
                    if (D_81184664[i].unk_33 == tCache->entries[0].id && D_81184664[i].enabled) {
                        break;
                    }
                }

                if (i == D_811858E8) {
                    func_8110CAE0(tCache->entries[0].id, 3);
                    loadStatusEntry0 = 3;
                }
            }

            if (loadStatusEntry1 == 4) {
                for (i = 0; i < D_811858E8; i++) {
                    if (D_81184664[i].unk_33 == tCache->entries[1].id && D_81184664[i].enabled) {
                        break;
                    }
                }

                if (i == D_811858E8) {
                    func_8110CAE0(tCache->entries[1].id, 3);
                    loadStatusEntry1 = 3;
                }
            }
        }

        if (loadStatusEntry0 == 0) {
            tCache->nextSide = 0;
        } else if (loadStatusEntry1 == 0) {
            tCache->nextSide = 1;
        } else if (loadStatusEntry0 == 3 && loadStatusEntry1 == 3) {
            // Use the opposite side from last time.
        } else if (loadStatusEntry0 == 3) {
            tCache->nextSide = 0;
        } else if (loadStatusEntry1 == 3) {
            tCache->nextSide = 1;
        } else {
            if (tableType == 0) {
                if (loadStatusEntry0 == 2) {
                    for (i = 0; i < D_811858CC; i++) {
                        if (((SeqPlayer81109C0C*)&D_81184668)[i].enabled && ((SeqPlayer81109C0C*)&D_81184668)[i].seqId == tCache->entries[0].id) {
                            break;
                        }
                    }
                    if (i == D_811858CC) {
                        tCache->nextSide = 0;
                        goto done;
                    }
                }
                if (loadStatusEntry1 == 2) {
                    for (i = 0; i < D_811858CC; i++) {
                        if (((SeqPlayer81109C0C*)&D_81184668)[i].enabled && ((SeqPlayer81109C0C*)&D_81184668)[i].seqId == tCache->entries[1].id) {
                            break;
                        }
                    }
                    if (i == D_811858CC) {
                        tCache->nextSide = 1;
                        goto done;
                    }
                }
            } else if (tableType == 1) {
                if (loadStatusEntry0 == 2) {
                    for (i = 0; i < D_811858E8; i++) {
                        if (D_81184664[i].unk_33 == tCache->entries[0].id && D_81184664[i].enabled) {
                            break;
                        }
                    }
                    if (i == D_811858E8) {
                        tCache->nextSide = 0;
                        goto done;
                    }
                }
                if (loadStatusEntry1 == 2) {
                    for (i = 0; i < D_811858E8; i++) {
                        if (D_81184664[i].unk_33 == tCache->entries[1].id && D_81184664[i].enabled) {
                            break;
                        }
                    }
                    if (i == D_811858E8) {
                        tCache->nextSide = 1;
                        goto done;
                    }
                }
            }

            if (tCache->nextSide == 0) {
                if (loadStatusEntry0 == 1) {
                    if (loadStatusEntry1 == 1) {
                        goto fail;
                    }
                    tCache->nextSide = 1;
                }
            } else {
                if (loadStatusEntry1 == 1) {
                    if (loadStatusEntry0 == 1) {
                        goto fail;
                    }
                    tCache->nextSide = 0;
                }
            }

            if (0) {
            fail:
                return NULL;
            }
        }

    done:
        if (tCache->entries[tCache->nextSide].id != -1) {
            loadStatus[tCache->entries[tCache->nextSide].id] = 0;
            if (tableType == 1) {
                func_81109678(tCache->entries[tCache->nextSide].id);
            }
        }

        switch (tCache->nextSide) {
            case 0:
                tCache->entries[0].ramAddr = tempPool->startRamAddr;
                tCache->entries[0].id = id;
                tCache->entries[0].size = size;
                tempPool->curRamAddr = tempPool->startRamAddr + size;

                if (tCache->entries[1].id != -1 && tCache->entries[1].ramAddr < tempPool->curRamAddr) {
                    loadStatus[tCache->entries[1].id] = 0;
                    switch (tableType) {
                        case 0:
                            func_81109764(tCache->entries[1].id);
                            break;
                        case 1:
                            func_81109678(tCache->entries[1].id);
                            break;
                    }
                    tCache->entries[1].id = -1;
                    tCache->entries[1].ramAddr = tempPool->startRamAddr + tempPool->size;
                }
                tempAddr = tCache->entries[0].ramAddr;
                break;

            case 1:
                tCache->entries[1].ramAddr = (u8*)((u32)(tempPool->startRamAddr + tempPool->size - size) & ~0xF);
                tCache->entries[1].id = id;
                tCache->entries[1].size = size;
                if (tCache->entries[0].id != -1 && tCache->entries[1].ramAddr < tempPool->curRamAddr) {
                    loadStatus[tCache->entries[0].id] = 0;
                    switch (tableType) {
                        case 0:
                            func_81109764(tCache->entries[0].id);
                            break;
                        case 1:
                            func_81109678(tCache->entries[0].id);
                            break;
                    }
                    tCache->entries[0].id = -1;
                    tempPool->curRamAddr = tempPool->startRamAddr;
                }
                tempAddr = tCache->entries[1].ramAddr;
                break;

            default:
                return NULL;
        }

        tCache->nextSide ^= 1;
        return tempAddr;
    }

    persistentAddr = (void*)func_81109868((M2C_UNK*)&loadedCache->persistent.pool, size);
    loadedCache->persistent.entries[loadedCache->persistent.numEntries].ramAddr = persistentAddr;

    if (persistentAddr == NULL) {
        switch (cache) {
            case 2:
                return func_81109C0C(tableType, size, 0, id);
            case 0:
            case 1:
                return NULL;
        }
    }

    loadedCache->persistent.entries[loadedCache->persistent.numEntries].id = id;
    loadedCache->persistent.entries[loadedCache->persistent.numEntries].size = size;
    return loadedCache->persistent.entries[loadedCache->persistent.numEntries++].ramAddr;
}

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

extern volatile u8 D_81184657;
extern s32 D_8118465C;
void func_8110AFF0(void);
void func_8110BFB0(void);

s32 func_8110AC8C(void) {
    s32 i;
    s32 j;
    s32 sp24;

    if (D_811858B8.unk_00 == 2) {
        sp24 = 2;
    } else {
        sp24 = 1;
    }

    switch (D_81184657) {
        case 5:
            for (i = 0; i < D_811858B8.unk_14; i++) {
                func_81112E00(&D_81184668 + i * 0x15C);
            }
            D_8118465C = 4 / sp24;
            D_81184657--;
            break;
        case 4:
            if (D_8118465C != 0) {
                D_8118465C--;
                func_8110AA50();
            } else {
                for (i = 0; i < D_811858E8; i++) {
                    if (D_81184664[i].enabled && D_81184664[i].unk_5D != 0) {
                        D_81184664[i].unk_6C = D_811858B8.unk_1C;
                        D_81184664[i].unk_5C |= 0x10;
                    }
                }
                D_8118465C = 16 / sp24;
                D_81184657--;
            }
            break;
        case 3:
            if (D_8118465C != 0) {
                D_8118465C--;
                func_8110AA50();
            } else {
                D_8118465C = 4 / sp24;
                D_81184657--;
            }
            break;
        case 2:
            func_8110AC14();
            if (!D_8118465C && !D_8118465C && !D_8118465C) {} // FAKE: empty test found by a fake search; only changes register use
            if (D_8118465C != 0) {
                D_8118465C--;
            } else {
                D_81184657--;
                func_8110BFB0();
            }
            if (!D_811858B8.unk_00) {} // FAKE: empty test found by the permuter; keeps &D_811858B8 in a saved register
            break;
        case 1:
            func_8110AFF0();
            D_81184657 = 0;
            for (i = 0; i < 3; i++) {
                D_811859C4[i] = D_811858B8.unk_08;
                for (j = 0; j < 0x7E0; j++) {
                    D_811859B8[i][j] = 0;
                }
            }
            break;
    }

    if (D_81184657 < 3) {
        return 0;
    }
    return 1;
}








typedef struct SplitAFF0 {
    /* 0x00 */ s32 a;
    /* 0x04 */ s32 b;
    /* 0x08 */ s32 c;
} SplitAFF0;

extern AudioSpecAFF0 D_811526C4[];
extern s16 D_811526F8;
extern u16 D_81184278;
extern s16 D_8118427C;
extern void* D_81184288;
extern s32 D_81184298;
extern SessionSplitAFF0 D_81184620;
extern SplitAFF0 D_81184630;
extern SplitAFF0 D_81184638;
extern SplitAFF0 D_81184648;
extern u8 D_81184658;
extern s32 D_811858E4;
extern s16 D_811858EC;
extern void* D_81185900[2];
extern s32 D_811859B4;
extern f32 D_811859B0;
extern u32 D_8118568C;
extern s32 D_8118557C;
// func_8110B9F8 is defined as void in the next file, but this file calls it as
// if it returned a value (as with an implicit declaration); the call only
// matches that way.
s32 func_8110B9F8(s32, s32);
void func_8110C618(s32);
void func_811152A4(s32);
s32 func_80058100(s32);
void func_8005C0A0(void);
void func_8110FAF4(void);
void func_81111130(void);
void func_81111AF4(void);
void func_8111539C(s32);
void func_81115480(void);


#define EXTERNAL_POOL_AFF0 (*(PoolAFF0*)&D_811842A0)
#define REVERBS_AFF0 ((SynthesisReverbAFF0*)D_81184110)

void func_8110AFF0(void) {
    UNUSED s32 pad[5]; // FAKE: stack pad of unknown origin; only reserves frame space
    s32 persistentMem;
    s32 temporaryMem;
    s32 totalMem;
    s32 wantMisc;
    s32 j;
    s32 i;
    ReverbSettingsAFF0* settings;
    SynthesisReverbAFF0* reverb;
    AudioSpecAFF0* spec = &D_811526C4[D_81184658];

    D_8118568C = 0;
    D_811858B8.unk_02 = spec->frequency;
    D_811858B8.unk_04 = func_80058100(D_811858B8.unk_02);
    D_811858B8.unk_06 = ((D_811858B8.unk_02 / D_811859B4) + 0xF) & 0xFFF0;
    D_811858B8.unk_0A = D_811858B8.unk_06 - 0x10;
    D_811858B8.unk_08 = D_811858B8.unk_06 + 0x10;
    D_811858B8.unk_0C = ((D_811858B8.unk_06 + 0x10) / 0xD0) + 1;
    D_811858B8.unk_0E = (D_811858B8.unk_06 / D_811858B8.unk_0C) & ~7;
    D_811858B8.unk_10 = D_811858B8.unk_0E + 8;
    D_811858B8.unk_12 = D_811858B8.unk_0E - 8;
    D_811858B8.unk_18 = 32000.0f / (s32)D_811858B8.unk_02;
    D_811858B8.unk_20 = (1.0f / 256.0f) / D_811858B8.unk_0C;
    D_811858B8.unk_24 = D_811858B8.unk_0C / 4.0f;
    D_811858B8.unk_1C = 1.0f / D_811858B8.unk_0C;
    D_811858E8 = spec->numNotes;
    D_811858B8.unk_14 = spec->numSequencePlayers;
    if (D_811858B8.unk_14 >= 2) {
        D_811858B8.unk_14 = 1;
    }
    D_81184278 = spec->unk_0C;
    D_811858EC = (u32)(D_811858B8.unk_0C * 2880000.0f / D_811526F8 / D_811859B0);
    D_811858B8.unk_00 = spec->unk_04;
    D_811858B8.unk_06 *= D_811858B8.unk_00;
    D_811858B8.unk_08 *= D_811858B8.unk_00;
    D_811858B8.unk_0A *= D_811858B8.unk_00;
    D_811858B8.unk_0C *= D_811858B8.unk_00;
    if (D_811858B8.unk_00 >= 2) {
        D_811858B8.unk_08 -= 0x10;
    }
    D_811858E4 = D_811858E8 * 0x14 * D_811858B8.unk_0C + spec->numReverbs * 0x20 + 0x1E0;
    persistentMem = spec->persistentSeqMem + spec->persistentFontMem + spec->persistentSampleMem + spec->persistentSampleCacheSize + 0x10;
    temporaryMem = spec->temporarySeqMem + spec->temporaryFontMem + spec->temporarySampleMem + spec->temporarySampleCacheSize + 0x10;
    totalMem = persistentMem + temporaryMem;
    wantMisc = D_81184298 - totalMem - 0x100;
    D_81184620.miscPoolSize = wantMisc;
    D_81184620.cachePoolSize = totalMem;
    func_8110999C((s8*)&D_81184620);
    D_81184630.a = persistentMem;
    D_81184630.b = temporaryMem;
    func_81109A18((s8*)&D_81184630);
    D_81184638.a = spec->persistentSeqMem;
    D_81184638.b = spec->persistentFontMem;
    D_81184638.c = spec->persistentSampleMem;
    func_81109A94((s8*)&D_81184638);
    D_81184648.a = spec->temporarySeqMem;
    D_81184648.b = spec->temporaryFontMem;
    D_81184648.c = spec->temporarySampleMem;
    func_81109B50((s8*)&D_81184648);
    func_8110B9F8(spec->persistentSampleCacheSize, spec->temporarySampleCacheSize);
    if (EXTERNAL_POOL_AFF0.start != NULL) {
        EXTERNAL_POOL_AFF0.cur = EXTERNAL_POOL_AFF0.start;
    }
    func_811095E0();
    D_81184664 = (Rec81109678*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, D_811858E8 * 0xCC);
    func_81111AF4();
    func_81111130();
    D_81184288 = (void*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, D_811858B8.unk_0C * D_811858E8 * 0x18);
    for (i = 0; i != 2; i++) {
        D_81185900[i] = (void*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, D_811858E4 * 8);
    }
    for (i = 0; i < 1; i++) {
        reverb = &REVERBS_AFF0[i];
        reverb->useReverb = 0;
    }
    D_8118427B = spec->numReverbs;
    for (i = 0; i < D_8118427B; i++) {
        reverb = &REVERBS_AFF0[i];
        settings = &spec->reverbSettings[i];

        reverb->downsampleRate = settings->downsampleRate;
        reverb->windowSize = settings->windowSize * 64;
        reverb->windowSize /= reverb->downsampleRate;
        reverb->decayRatio = settings->decayRatio;
        reverb->unk_0A = settings->unk_4;
        reverb->unk_10 = settings->unk_6;
        reverb->unk_12 = settings->unk_8;
        reverb->unk_05 = settings->unk_A;
        reverb->unk_08 = settings->unk_C;
        reverb->useReverb = 8;
        reverb->leftRingBuf = (s16*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, reverb->windowSize * 2);
        reverb->rightRingBuf = (s16*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, reverb->windowSize * 2);
        reverb->nextRingBufPos = 0;
        reverb->unk_18 = 0;
        reverb->curFrame = 0;
        reverb->bufSizePerChan = reverb->windowSize;
        reverb->framesToIgnore = 2;
        reverb->resampleFlags = 1;
        reverb->soundSample = &reverb->sample;
        reverb->sample.loop = &reverb->loop;
        reverb->soundTuning = 1.0f;
        reverb->sample.codec = 3;
        reverb->sample.medium = 0;
        reverb->sample.size = reverb->windowSize * 2;
        reverb->sample.sampleAddr = reverb->leftRingBuf;
        reverb->loop.start = 0;
        reverb->loop.count = 1;
        reverb->loop.end = reverb->windowSize;
        if (reverb->downsampleRate != 1) {
            reverb->unk_0E = 0x8000 / reverb->downsampleRate;
            reverb->unk_28 = (void*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, 0x20);
            reverb->unk_2C = (void*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, 0x20);
            reverb->unk_30 = (void*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, 0x20);
            reverb->unk_34 = (void*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, 0x20);
            for (j = 0; j < D_811858B8.unk_0C; j++) {
                s16* mem = (s16*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, 0x340);

                reverb->items[0][j].toDownsampleLeft = mem;
                reverb->items[0][j].toDownsampleRight = mem + 0xD0;
                mem = (s16*)GbApu_AllocZeroed((unk_func_81206FA0*)&D_811842C0, 0x340);
                reverb->items[1][j].toDownsampleLeft = mem;
                reverb->items[1][j].toDownsampleRight = mem + 0xD0;
            }
        }
        if (settings->lowPassFilterCutoffLeft != 0) {
            reverb->filterLeftState = (s16*)GbApu_Alloc((unk_func_81206FA0*)&D_811842C0, 0x20);
            reverb->filterLeft = (s16*)GbApu_Alloc((unk_func_81206FA0*)&D_811842C0, 0x10);
            func_8110A878(reverb->filterLeft, settings->lowPassFilterCutoffLeft);
        } else {
            reverb->filterLeft = NULL;
        }
        if (settings->lowPassFilterCutoffRight != 0) {
            reverb->filterRightState = (s16*)GbApu_Alloc((unk_func_81206FA0*)&D_811842C0, 0x20);
            reverb->filterRight = (s16*)GbApu_Alloc((unk_func_81206FA0*)&D_811842C0, 0x10);
            func_8110A878(reverb->filterRight, settings->lowPassFilterCutoffRight);
        } else {
            reverb->filterRight = NULL;
        }
    }
    func_81115480();
    for (j = 0; j < D_811858B8.unk_14; j++) {
        func_8111539C(j);
        func_811152A4(j);
    }
    func_8110C618(D_811858E8);
    D_8118557C = 0;
    D_8118427C = 0x1000;
    func_8110FAF4();
    func_8005C0A0();
}
