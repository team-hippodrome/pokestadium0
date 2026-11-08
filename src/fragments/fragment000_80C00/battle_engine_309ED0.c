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

typedef struct SampleHeader8110E500 {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 unk_00 : 2;
    /* 0x00 */ u32 size : 24;
    /* 0x04 */ s32 devAddr;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} SampleHeader8110E500; // size = 0x10

typedef struct SampleLoad8110E500 {
    /* 0x00 */ s8 medium;
    /* 0x01 */ u8 arg0;
    /* 0x02 */ u8 arg1;
    /* 0x04 */ s32 devAddr;
    /* 0x08 */ s32 ramAddr;
    /* 0x0C */ s32 curRamAddr;
    /* 0x10 */ s32 state;
    /* 0x14 */ s32 size;
    /* 0x18 */ s8* status;
    /* 0x1C */ SampleHeader8110E500 header;
    /* 0x2C */ u8 unk_2C[0x34];
} SampleLoad8110E500; // size = 0x60

typedef struct SampleLoads8110E500 {
    /* 0x00 */ s32 index;
    /* 0x04 */ SampleLoad8110E500 slots[2];
} SampleLoads8110E500;

extern SampleLoads8110E500 D_81180610;
s32 func_8110B958(s32, s32, s32, s8);
s32 func_8110E6B0(s32 arg0, s32 arg1);

s32 func_8110E500(s32 arg0, u8 arg1, s8* status) {
    SampleHeader8110E500* header = (SampleHeader8110E500*)func_8110E6B0(arg0, arg1);
    SampleLoad8110E500* load;

    if (header == NULL) {
        *status = 0;
        return -1;
    }
    if (header->medium == 0) {
        *status = 2;
        return 0;
    }
    load = &D_81180610.slots[D_81180610.index];
    if (load->state == 3) {
        load->state = 0;
    }
    load->header = *header;
    load->status = status;
    load->ramAddr = func_8110B958(header->size, arg0, header->devAddr, header->medium);
    if (load->ramAddr == 0) {
        if ((header->medium == 1) || (header->codec == 2)) {
            *status = 0;
            return -1;
        }
        *status = 3;
        return -1;
    }
    load->state = 1;
    load->size = ALIGN16(header->size);
    load->curRamAddr = load->ramAddr;
    load->devAddr = header->devAddr;
    load->medium = header->medium;
    load->arg0 = arg0;
    load->arg1 = arg1;
    D_81180610.index ^= 1;
    return 0;
}

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

extern u8 D_81137E3C[];
void func_8110DBA0(s8*, s32, s32, s32, s32, s32, OSMesgQueue*, s32, u8*);

void func_8110E910(s8* arg0, s32 arg1) {
    osInvalDCache((void*)M2C_FIELD(arg0, s32*, 8), arg1);
    osCreateMesgQueue((OSMesgQueue*)(arg0 + 0x2C), (OSMesg*)(arg0 + 0x44), 1);
    func_8110DBA0(arg0 + 0x48, 0, 0, M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 8), arg1, (OSMesgQueue*)(arg0 + 0x2C), *(u8*)arg0, D_81137E3C);
}

void func_8110E994(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {

}

#ifdef NON_MATCHING
/* TODO: decompile func_8110E9A8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110E9A8.s")
#endif

typedef struct Entry8110EABC {
    /* 0x00 */ s8 active;
    /* 0x01 */ char unk01[0x53];
} Entry8110EABC; // size = 0x54
extern volatile s32 D_811859D4;
extern Entry8110EABC D_81185580[1];
void func_8110EB40(Entry8110EABC*, s32);
void func_8110EABC(s32 arg0) {
    s32 i;

    if (D_811859D4 != 1U) {
        for (i = 0; i < 1; i++) {
            if (D_81185580[i].active == 1) {
                func_8110EB40(&D_81185580[i], arg0);
            }
        }
    }
}

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

#ifdef NON_MATCHING
/* TODO: decompile func_8110EE3C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110EE3C.s")
#endif

typedef struct RelocInfo8110EF7C {
    /* 0x00 */ s32 sampleBankId1;
    /* 0x04 */ s32 sampleBankId2;
    /* 0x08 */ s32 baseAddr1;
    /* 0x0C */ s32 baseAddr2;
    /* 0x10 */ u32 medium1;
    /* 0x14 */ u32 medium2;
} RelocInfo8110EF7C;

typedef struct Sample8110EF7C {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 unk_bit26 : 1;
    /* 0x00 */ u32 isRelocated : 1;
    /* 0x00 */ u32 size : 24;
    /* 0x04 */ s32 sampleAddr;
} Sample8110EF7C;

typedef struct Preload8110EF7C {
    /* 0x00 */ u32 endAndMediumKey;
    /* 0x04 */ Sample8110EF7C* sample;
    /* 0x08 */ s32 ramAddr;
    /* 0x0C */ u32 encodedInfo;
    /* 0x10 */ s32 isFree;
} Preload8110EF7C; // size = 0x14

extern s32 D_811806D8;
extern Preload8110EF7C D_81184B78[];
extern s32 D_8118557C;
extern OSMesgQueue D_811855F8;
extern u8* D_811858A4;
void func_8110D884(s32, s32, RelocInfo8110EF7C*);
void func_8110DB8C(s32, s32, u32, s16);
void func_8110DA68(s32, s32, u32, s32);
void func_8110E9A8(s32, s32, u32, s32, s32, OSMesgQueue*, u32);
s32 func_8110B9A8(s32, s32, s32, s8);


void func_8110EF7C(s32 fontId, s32 fontData, RelocInfo8110EF7C* relocInfo, s32 async) {
    UNUSED s32 pad[2];
    s32 sampleRamAddr;
    Sample8110EF7C* sample;
    s32 size;
    s32 nChunks;
    s32 preloadInProgress;
    s32 i;

    preloadInProgress = 0;
    if (D_8118557C != 0) {
        preloadInProgress = 1;
    } else {
        D_811806D8 = 0;
    }

    D_81185578 = 0;
    func_8110D884(fontId, fontData, relocInfo);

    size = 0;
    for (i = 0; i < D_81185578; i++) {
        size += ALIGN16(((Sample8110EF7C*)D_81184978[i])->size);
    }

    for (i = 0; i < D_81185578; i++) {
        if (D_8118557C == 0x78) {
            break;
        }

        sample = (Sample8110EF7C*)D_81184978[i];
        switch (async) {
            case 0:
                if (sample->medium == relocInfo->medium1) {
                    // Assigning size here keeps it live, which the ROM's register allocation needs.
                    sampleRamAddr = func_8110B9A8(size = sample->size, relocInfo->sampleBankId1, sample->sampleAddr, sample->medium);
                } else if (sample->medium == relocInfo->medium2) {
                    sampleRamAddr = func_8110B9A8(sample->size, relocInfo->sampleBankId2, sample->sampleAddr, sample->medium);
                }
                break;

            case 1:
                if (sample->medium == relocInfo->medium1) {
                    sampleRamAddr = func_8110B958(sample->size, relocInfo->sampleBankId1, sample->sampleAddr, sample->medium);
                } else if (sample->medium == relocInfo->medium2) {
                    sampleRamAddr = func_8110B958(sample->size, relocInfo->sampleBankId2, sample->sampleAddr, sample->medium);
                }
                break;
        }

        if (sampleRamAddr == 0) {
            continue;
        }

        switch (async) {
            case 0:
                if (sample->medium == 1) {
                    func_8110DB8C(sample->sampleAddr, sampleRamAddr, sample->size, *(s16*)(D_811858A4 + 2));
                    sample->sampleAddr = sampleRamAddr;
                    sample->medium = 0;
                } else {
                    func_8110DA68(sample->sampleAddr, sampleRamAddr, sample->size, sample->medium);
                    sample->sampleAddr = sampleRamAddr;
                    sample->medium = 0;
                }
                break;

            case 1:
                D_81184B78[D_8118557C].sample = sample;
                D_81184B78[D_8118557C].ramAddr = sampleRamAddr;
                D_81184B78[D_8118557C].encodedInfo = (D_8118557C << 24) | 0xFFFFFF;
                D_81184B78[D_8118557C].isFree = 0;
                D_81184B78[D_8118557C].endAndMediumKey = sample->sampleAddr + sample->size + sample->medium;
                D_8118557C++;
                break;
        }
    }
    D_81185578 = 0;

    if ((D_8118557C != 0) && !preloadInProgress) {
        sample = D_81184B78[D_8118557C - 1].sample;
        nChunks = (sample->size >> 12) + 1;
        func_8110E9A8(sample->sampleAddr, D_81184B78[D_8118557C - 1].ramAddr, sample->size, sample->medium, nChunks, &D_811855F8, D_81184B78[D_8118557C - 1].encodedInfo);
    }
}

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

typedef struct Entry811858B0 {
    /* 0x00 */ u8 unk_00[2];
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ char unk04[8];
} Entry811858B0; // size = 0xC
extern Entry811858B0* D_811858B0;

s32 func_8110F518(s32 arg0, Item8110F4D0** arg1) {
    s32 count = 0;
    s32 i;
    s32 n1 = D_811858B0[arg0].unk_00[1];
    s32 n0 = D_811858B0[arg0].unk_00[0];
    s32* p;
    u8* q;

    for (i = 0; i < n1; i++) {
        p = func_81110D6C(arg0, i);
        if (p != 0) {
            // do-while(0) wrapper only changes register allocation; needed to match
            do {
                count = func_8110F4D0((Item8110F4D0*)p[1], count, arg1);
            } while (0);
        }
    }
    for (i = 0; i < n0; i++) {
        q = (u8*)func_81110CA8(arg0, i);
        if (q != 0) {
            if (q[1] != 0) {
                count = func_8110F4D0(*(Item8110F4D0**)(q + 8), count, arg1);
            }
            if (q[2] != 0x7F) {
                count = func_8110F4D0(*(Item8110F4D0**)(q + 0x18), count, arg1);
            }
            count = func_8110F4D0(*(Item8110F4D0**)(q + 0x10), count, arg1);
        }
    }
    return count;
}


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
void func_8110F6A4(s32, s32, RelocInfo8110EF7C*);
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
