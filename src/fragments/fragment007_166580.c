/* Stadium Zero fragment007_166580. */

#include "global.h"
#include "m2c_macros.h"

/* Unprototyped on purpose: different callers in this file pass one or two arguments. */
s32 func_8002DC04();
M2C_UNK func_8002E3F0();
s32 func_8002DCE0();
void func_82004518(s32, s32, s32);

/*
 * func_82000020
 *
 * Stores -1 into arg2 consecutive words of the s32 array arg0, starting at
 * index arg1 (indices arg1 .. arg1 + arg2 - 1). Does nothing when
 * arg1 + arg2 <= arg1, i.e. when arg2 is not positive. The compare is signed.
 * What the -1 entries mean is not established from this function.
 */
void func_82000020(s32* arg0, s32 arg1, s32 arg2) {
    s32 end;

    end = arg1 + arg2;
    for (; arg1 < end; arg1++) {
        arg0[arg1] = -1;
    }
}

typedef struct Entry82000058 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x50];
} Entry82000058; // size = 0x54
s32 func_80020AFC(s32, s32, s32, s32);
s32 func_80020CE4(void*, s32, s32);
void func_80020C60(s32);
void func_800207F8(u8*);
extern u8 D_80065D00[];

s32 func_82000058(s32 arg0, s32 arg1, s32 arg2, Entry82000058* entry) {
    s32 handle = func_80020AFC(arg0, arg1, arg2, 0);
    s32 i;
    u8* row;
    s32 idx;

    for (i = 0; i < 6; i++, entry++) {
        if (func_80020CE4(entry->unk_04, 1, handle) == 0) {
            break;
        }
        if ((entry->unk_04[0] > 0) && (entry->unk_04[0] < 0x98)) {
            func_800207F8(entry->unk_04);
            idx = entry->unk_04[0] - 1;
            row = &D_80065D00[idx * 0x17];
            entry->unk_04[6] = row[6];
            entry->unk_04[7] = row[7];
            entry->unk_00 = 0;
        }
    }
    func_80020C60(handle);
    return i;
}

/* One of six 0x54-byte slots; only the leading in-use flag word is known. */
typedef struct {
    /* 0x00 */ s32 flag;
    /* 0x04 */ char unk04[0x50];
} Slot54;

/*
 * func_82000140
 *
 * Sets the first word (flag) to 1 in each of the slots arg1 .. 5 of an array
 * of six 0x54-byte slots starting at arg0 (nothing happens when arg1 >= 6).
 * The retail code unrolls the loop by four.
 */
void func_82000140(Slot54* arg0, s32 arg1) {
    s32 i;

    arg0 += arg1;
    for (i = arg1; i < 6; i++) {
        arg0->flag = 1;
        arg0++;
    }
}

/*
 * func_820001B8
 *
 * Scans the six 0x54-byte slots starting at arg0 from slot 5 down to slot 0.
 * Stores in *arg1 how many have a non-zero first word (flag) and returns the
 * lowest-numbered such slot, or NULL when none is set.
 */
Slot54* func_820001B8(Slot54* arg0, s32* arg1) {
    Slot54* found = NULL;
    s32 count = 0;

    arg0 += 5;

    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    *arg1 = count;
    return found;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82000258; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82000258.s")
#endif

typedef struct {
    /* 0x000 */ u8 type;
    /* 0x001 */ u8 unk_01;
    /* 0x002 */ u8 unk_02;
    /* 0x003 */ u8 unk_03;
    /* 0x004 */ char unk04[0x210];
} Record214;

typedef struct {
    /* 0x00 */ Record214* records;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 count;
} RecordList;

/* Header (0x1C bytes) followed by six 0x54-byte slots (see Slot54). */
typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk08[0x10];
    /* 0x18 */ s32 slotCount;
    /* 0x1C */ Slot54 slots[6];
} SlotList;

#ifdef NON_MATCHING
/* TODO: decompile func_820003D4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820003D4.s")
#endif

/*
 * func_8200053C
 *
 * Appends an empty record to a list of 0x214-byte records: initialises the
 * header of the record at index `count` (type byte = 2, the next three bytes
 * = 0), then sets `count` to the index of the following record, computed as a
 * pointer difference from the start of the list.
 */
void func_8200053C(RecordList* arg0) {
    Record214* rec;

    rec = &arg0->records[arg0->count];
    rec->type = 2;
    rec->unk_01 = 0;
    rec->unk_02 = 0;
    rec->unk_03 = 0;
    rec++;
    arg0->count = rec - arg0->records;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82000594; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82000594.s")
#endif

/*
 * func_820008C8
 *
 * Builds a table of pointers into a block of equally sized records.
 * arg1 holds the address of the first record at +0x00 and the record count
 * at +0x08.  arg0 holds the address of the pointer table at +0x00; entry i
 * is set to (first record + i * 0x214), so each record is 0x214 bytes.
 * The count is then copied to arg0 + 0x08.  What the records are is not
 * known from the code alone.
 *
 * func_881025C8 is the same routine with a record size of 0x220.
 */
void func_820008C8(s32* arg0, s32* arg1) {
    s32 value = arg1[0];
    s32* out = (s32*)arg0[0];
    s32 i = 0;

    if (arg1[2] > 0) {
        do {
            *out = value;
            i += 1;
            value += 0x214;
            out += 1;
        } while (i < arg1[2]);
    }
    arg0[2] = arg1[2];
}

char* HAL_Strcpy(char*, char*);
extern s32 D_82008F84;

/*
 * func_82000900
 *
 * Initialises a slot-list object: sets its four header bytes to 1, 0, 0, 0
 * and the word at +0x04 to 0; copies the string D_82008F84[arg1] (a table of string
 * pointers) into the buffer at +0x08 with HAL_Strcpy; clears the flag word of all six slots and then
 * sets them all with func_82000140(slots, 0) (so the explicit clear is
 * overwritten); finally stores slotCount = 6.
 */
void func_82000900(SlotList* arg0, s32 arg1) {
    s32 i;

    arg0->unk_00 = 1;
    arg0->unk_01 = 0;
    arg0->unk_02 = 0;
    arg0->unk_03 = 0;
    arg0->unk_04 = 0;
    HAL_Strcpy(arg0->unk08, ((char**)&D_82008F84)[arg1]);
    for (i = 0; i < 6; i++) {
        arg0->slots[i].flag = 0;
    }
    func_82000140(arg0->slots, 0);
    arg0->slotCount = 6;
}

extern s32 D_800603C0;
void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern Color_RGBA8 D_8200902C;
extern char D_82009B80[];
extern char D_82009B88[];
extern s32 D_8200AC4C;
void func_8002AE94(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);

/**
 * Initialises the object arg0 (size and layout not established); a sibling of
 * func_82008524. Calls func_8002A8C4(arg0, arg1, arg2, 0x1AE, 0x124), clears the
 * words at 0x20, 0x24 and 0x28 and sets the word at 0x14 to 0x1001. Calls
 * func_8002AE94 twice, on the sub-objects at arg0 + 0x2C (string D_82009B80)
 * and arg0 + 0x68 (string D_82009B88), both with width 0x48 and colour
 * D_8200902C and positions derived from the words at 0 and 4. Then sets the
 * words at 0x58, 0x60, 0xAC and 0xA8 to 0xA, 0xC, 2 and 0, stores D_800603C0
 * and then arg5 in the word at 0xA4 (calling func_8000B2F4 with each), stores
 * arg4 at 0xB4 and arg3 at 0xB0, and clears D_8200AC4C.
 * What the object is and what the constants mean is not established.
 */
void func_820009A4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_8002A8C4(arg0, arg1, arg2, 0x1AE, 0x124);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x1001;
    func_8002AE94(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 0x10A, M2C_FIELD(arg0, s32*, 4) + 0x100, 0x48, D_8200902C, D_82009B80);
    M2C_FIELD(arg0, s32*, 0x58) = 0xA;
    M2C_FIELD(arg0, s32*, 0x60) = 0xC;
    func_8002AE94(arg0 + 0x68, M2C_FIELD(arg0, s32*, 0) + 0x15A, M2C_FIELD(arg0, s32*, 4) + 0x100, 0x48, D_8200902C, D_82009B88);
    M2C_FIELD(arg0, s32*, 0xAC) = 2;
    M2C_FIELD(arg0, s32*, 0xA8) = 0;
    M2C_FIELD(arg0, s32*, 0xA4) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32*, 0xA4) = arg5;
    func_8000B2F4(arg5);
    M2C_FIELD(arg0, s32*, 0xB4) = arg4;
    M2C_FIELD(arg0, s32*, 0xB0) = arg3;
    D_8200AC4C = 0;
}

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 func_8002D498(s32, s32);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001ABBC(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A944(s32, s32, const char*, ...);

typedef struct Entry8006A9D4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry8006A9D4; // size = 0xC
extern Entry8006A9D4 D_8006A9D4[];
extern M2C_UNK D_800734A8;
extern char D_82009B90[];
u32 func_800566BC(const char*);

void func_82000AC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Entry8006A9D4* entry;
    const char* str;
    Color82000BC4* c;

    func_8001A384(8, 0);
    if (arg2 == -2) {
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        str = D_82009B90;
    } else {
        entry = &D_8006A9D4[arg2];
        c = &D_80066AD8[entry->type].color;
        func_8001AA9C(c->r, c->g, c->b, c->a);
        str = entry->name;
    }
    if (arg3 != 0) {
        arg0 = arg0 - (func_800566BC(str) >> 1) * 20 + 0x8C;
    }
    func_8001A944(arg0, arg1, str);
}


void func_82000BC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Color82000BC4 c;
    s32 idx = func_8002D498(arg2, arg3);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(8, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(arg0, arg1, D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_82000C5C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82000C5C.s")
#endif

s32 func_8002B390(s32);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);

s32 func_820012B4(s8* arg0) {
    s32 ret = 0;
    s32 temp_v0;

    if (func_8002B390(arg0 + 0xA4) == 0) {
        temp_v0 = func_8002BC14(M2C_FIELD(arg0, s32*, 0xA4));
        if (temp_v0 == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (temp_v0 == 1) {
            switch (M2C_FIELD(arg0, s32*, 0xA8)) {
                case 1:
                    func_8003F6AC(3);
                    ret = -1;
                    break;
                default:
                    ret = 1;
                    break;
            }
        }
    }
    return ret;
}

typedef struct {
    /* 0x00 */ u8 id;
    /* 0x01 */ char unk01[0x4F];
} Record50;

typedef struct {
    /* 0x00 */ Record50* records;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 count;
} RecordTable;

typedef struct {
    /* 0x00 */ RecordTable* table;
    /* 0x04 */ u16* flags;
} FlagOwner;

void func_8002D900(FlagOwner*);

/**
 * For each of the six Slot54 entries in arg1 whose `flag` is zero and whose first
 * payload byte (offset 4) differs from arg2, scans the owner's record table; every
 * record whose id byte equals that payload byte gets bits 0x101 set in the
 * owner's parallel `flags` array (indexed by record number).
 * The meaning of the ids/flags is not yet known; names are structural only.
 */
void func_82001340(FlagOwner* arg0, Slot54* arg1, s32 arg2) {
    Record50* records;
    Record50* rec;
    s32 i;
    s32 count;
    s32 slot;
    Slot54* p;

    records = arg0->table->records;
    func_8002D900(arg0);
    slot = 0;
    p = arg1;
    for (; slot != 0x1F8; slot += 0x54, p++) {
        if ((p->flag == 0) && (arg2 != M2C_FIELD(p, u8*, 4))) {
            i = 0;
            rec = records;
            count = arg0->table->count;
            if (count > 0) {
                do {
                    if (rec->id == M2C_FIELD(p, u8*, 4)) {
                        arg0->flags[i] |= 0x101;
                        count = arg0->table->count;
                    }
                    i++;
                    rec++;
                } while (i < count);
            }
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8200140C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_8200140C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82001558; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82001558.s")
#endif

/**
 * Walks the six Slot54 entries at arg0. For each entry whose flag word has
 * bit 0x40 set, clears that bit, and then sets bit 0x10 unless the entry's
 * index equals arg1 (so only the entry arg1 is left without 0x10).
 * The meaning of the flag bits is not yet established.
 */
void func_82001708(Slot54* arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (!(arg0[i].flag & 0x40)) {
        } else {
            arg0[i].flag &= ~0x40;
            if (i != arg1) {
                arg0[i].flag |= 0x10;
            }
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_82001810; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82001810.s")
#endif

typedef struct Color82001CCC {
    u8 c[4];
} Color82001CCC;
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color82001CCC);
extern Color82001CCC D_82008F5C;
extern Color82001CCC D_82008F58;

#ifdef NON_MATCHING
/* TODO: decompile func_82001BB4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82001BB4.s")
#endif

/*
 * func_82001C00
 *
 * Emits the display list D_80060270, then fills a 0x88 by 0x64 rectangle at
 * (arg0, arg1) with the colour in arg2 using func_80029028
 * (Trade_DrawSolidFillRect).
 */
void func_82001C00(s32 arg0, s32 arg1, Color82001CCC arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x88, 0x64, arg2);
}

/*
 * func_82001C60
 *
 * Emits the display list D_80060270, then fills a 0x18C by 0x64 rectangle at
 * (arg0 + 0x88, arg1) with the colour in arg2 using func_80029028
 * (Trade_DrawSolidFillRect).
 */
void func_82001C60(s32 arg0, s32 arg1, Color82001CCC arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0 + 0x88, arg1, 0x18C, 0x64, arg2);
}

void func_82001CCC(s32 arg0, s32 arg1, Color82001CCC arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x214, 1, arg2);
    func_80029028(arg0, arg1 + 0x63, 0x214, 1, arg2);
}

extern char D_82009C08[];
void func_8001AAE4(u8, u8, u8, u8);
void func_8001AB2C(s32);
void func_8001ABE8(void);
void func_8001AC3C(void);

/*
 * func_82001D64
 *
 * Draws a filled rectangle with func_82001C60 using the colour D_82008F58,
 * then switches the font to translucent, two-cycle text rendering (white
 * environment colour, font set mask 0x20, func_8001AB2C(0x2A), prim colour
 * 255/100/255/255) and prints the string D_82009C08 at
 * (arg0 + 0xAE, arg1 + 0xE) before ending text rendering. arg2 is not used.
 */
void func_82001D64(s32 arg0, s32 arg1, s32 arg2) {
    func_82001C60(arg0, arg1, D_82008F58);
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8001A384(0x20, 0);
    func_8001AB2C(0x2A);
    func_8001ABE8();
    func_8001AAE4(0xFF, 0x64, 0xFF, 0xFF);
    func_8001A944(arg0 + 0xAE, arg1 + 0xE, D_82009C08);
    func_8001AC3C();
    func_8001ABBC();
}

#ifdef NON_MATCHING
/* TODO: decompile func_82001E20; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82001E20.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_820020EC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820020EC.s")
#endif

typedef struct {
    /* 0x00 */ Slot54** slots;
    /* 0x04 */ u16* flags;
} SlotFlags;

/**
 * For each of the six Slot54 entries reached through `*arg0->slots`, sets bit
 * 0x200 in the matching u16 of `arg0->flags` when the entry's flag word has bit 0
 * clear and at least one of the bits 0x26 set.
 * The meaning of the bits is not yet established.
 */
void func_820023E8(SlotFlags* arg0) {
    Slot54* slots;
    s32 i;

    slots = *arg0->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flag & 1) && (slots[i].flag & 0x26)) {
            arg0->flags[i] |= 0x200;
        }
    }
}

/**
 * For each of the six Slot54 entries reached through `*arg0->slots`, sets bit
 * 0x800 in the matching u16 of `arg0->flags` when the entry's flag word has bit 0
 * clear and at least one of the bits 0x10 set.
 * The meaning of the bits is not yet established.
 */
void func_82002528(SlotFlags* arg0) {
    Slot54* slots;
    s32 i;

    slots = *arg0->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flag & 1) && (slots[i].flag & 0x10)) {
            arg0->flags[i] |= 0x800;
        }
    }
}

/**
 * For each of the six Slot54 entries reached through `*arg0->slots`, sets bit 0
 * of the matching u16 in `arg0->flags` when the entry's flag word does not have
 * bit 0x40 set. The meaning of the bits is not yet established.
 */
void func_82002668(SlotFlags* arg0) {
    Slot54* slots;
    s32 i;

    slots = *arg0->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flag & 0x40)) {
            arg0->flags[i] |= 1;
        }
    }
}

/**
 * Counterpart of func_82002668: for each of the six Slot54 entries reached
 * through `*arg0->slots`, clears bit 0 of the matching u16 in `arg0->flags`
 * when the entry's flag word does not have bit 0x40 set.
 * The meaning of the bits is not yet established.
 */
void func_82002778(SlotFlags* arg0) {
    Slot54* slots;
    s32 i;

    slots = *arg0->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flag & 0x40)) {
            arg0->flags[i] &= ~1;
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8200288C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_8200288C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82002980; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82002980.s")
#endif

M2C_UNK func_82002980();                            /* extern */

void func_82002BF8(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x788) = arg2;
    if (arg2 & 1) {
        M2C_FIELD(M2C_FIELD(arg0, s8 **, 0xC), s32 *, 0x24) = 7;
        M2C_FIELD(arg0, s32 *, 8) = arg1;
        return;
    }
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    func_82002980();
}

#ifdef NON_MATCHING
/* TODO: decompile func_82002C3C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82002C3C.s")
#endif

extern s32 D_8200AC50;
extern s32 D_8200ACFC;
extern s32 D_8200AD00;
extern s32 D_8200AC58[];
extern M2C_UNK D_82009C98;
extern M2C_UNK func_82001810;
extern M2C_UNK func_820020EC;
void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK func_8002EC24(s8*, s32, s8*, M2C_UNK, M2C_UNK*, s32, s32);
M2C_UNK func_80030894(s8*, s8*, s8*, M2C_UNK, s32, M2C_UNK*, s32, s32);
M2C_UNK func_80027410(s8*, s32, M2C_UNK, M2C_UNK, s32);
void func_80018168(s8* arg0);
M2C_UNK func_82002C3C(s8*);

/**
 * Initializes the slot-menu object at arg0 (the layout other functions in this file
 * access as SlotMenu):
 *   - sets up the base window at +0x14 via func_8002A8C4 (arg1, arg2, size 0x220 x 0x158),
 *   - zeroes +0x00/+0x38/+0x3C, stores 0x801 at +0x28, &D_82009C98 at +0x34 and arg3 at +0xC4,
 *   - creates the sub-object at +0x40/+0x84 with func_8002EC24 (passing &func_820020EC),
 *   - sets bit 0x10000 at +0x60,
 *   - fills the first 0x28 words of D_8200AC58 with -1,
 *   - stores 1 at +0x738, arg4 at +0x73C and the mode arg5 at +0x740, and calls func_82002C3C,
 *   - when arg5 != 0, builds the record view at +0x684 (source D_8200ACFC if arg5 == 1,
 *     otherwise D_8200AD00, with different dimensions), links it through func_80030894
 *     at +0x6E4/+0x694 (passing &func_82001810) and sets bit 0x10000 at +0x704,
 *   - finally calls func_80018168 on D_8200AC50.
 * The meaning of arg1..arg5 beyond what is stored above is not established.
 */
void func_82002D5C(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s8* var_s1;

    func_8002A8C4(arg0 + 0x14, arg1, arg2, 0x220, 0x158);
    M2C_FIELD(arg0, s32*, 0x38) = 0;
    M2C_FIELD(arg0, s32*, 0x3C) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0x801;
    M2C_FIELD(arg0, M2C_UNK**, 0x34) = &D_82009C98;
    M2C_FIELD(arg0, s32*, 0xC4) = arg3;
    func_8002EC24(arg0 + 0x40, arg3, arg0 + 0x84, 3, &func_820020EC, 0x214, 0x64);
    M2C_FIELD(arg0, s32*, 0x60) = M2C_FIELD(arg0, s32*, 0x60) | 0x10000;
    M2C_FIELD(arg0, s32*, 0) = 0;
    func_82000020(D_8200AC58, 0, 0x28);
    M2C_FIELD(arg0, s32*, 0x738) = 1;
    M2C_FIELD(arg0, s32*, 0x73C) = arg4;
    M2C_FIELD(arg0, s32*, 0x740) = arg5;
    func_82002C3C(arg0);
    if (arg5 != 0) {
        if (arg5 == 1) {
            var_s1 = arg0 + 0x684;
            func_80027410(var_s1, D_8200ACFC, 0x50, 0x28, 0x28);
        } else {
            var_s1 = arg0 + 0x684;
            func_80027410(var_s1, D_8200AD00, 0x50, 0x21, 0x21);
        }
        func_80030894(arg0 + 0x6E4, var_s1, arg0 + 0x694, 4, 3, &func_82001810, 0x84, 0x32);
        M2C_FIELD(arg0, s32*, 0x704) = M2C_FIELD(arg0, s32*, 0x704) | 0x10000;
    }
    func_80018168((s8*)D_8200AC50);
}

extern Gfx D_80073450[];
extern u8 D_05000008[];
extern char D_82009CC8[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_8001AC7C(s32, s32, s32, s32, s32, s32, s32, s32);

/**
 * Emits the display list D_80073450 and the DECALRGBA combiner, then calls
 * func_8001B884 at (arg0, arg1) with D_05000008 as its texture argument (arg2
 * is passed straight through as the third argument), calls func_8001AC7C with
 * (arg0 + 0xE, arg1, 0x84, 0x14, ...) and then
 * prints the string D_82009CC8 at (arg0 + 0x10, arg1 + 2) in the colour
 * stored at D_800734A8 using font 4.
 * What this draws is not yet established.
 */
void func_82002EE4(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001B884(arg0, arg1, arg2, 0x14, D_05000008, 8, 0);
    func_8001AC7C(arg0 + 0xE, arg1, 0x84, 0x14, 0, 0, 0, 0xFF);
    func_8001AB6C();
    func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    func_8001A384(4, 0);
    func_8001A944(arg0 + 0x10, arg1 + 2, D_82009CC8);
    func_8001ABBC();
}

extern char D_800735C4[];
extern Color82001CCC D_82009098[];
extern s32 D_820090A8[];
extern char D_82009CF0[];
void func_800295E8(s32, s32, s32, s32, char*);

/**
 * Draws a labelled box using the menu object arg0 (layout not established; it
 * reads the words at 0x14, 0x18 and the mode index at 0x738). Calls
 * func_800295E8 at (word 0x14 + 0x127, word 0x18 - 0x12) with size 0xA6 by 0x14
 * and D_800735C4, emits D_80060270 and fills a 0xA2 by 0x10 rectangle at
 * (+0x129, -0x10) with the colour D_82009098[mode - 1]. Then prints the string
 * D_82009CF0 at (+0x12A, -0x10) in the colour D_800734A8, font 4, passing
 * D_820090A8[mode] as the extra argument.
 */
void func_82002FF8(s8* arg0) {
    func_800295E8(M2C_FIELD(arg0, s32*, 0x14) + 0x127, M2C_FIELD(arg0, s32*, 0x18) - 0x12, 0xA6, 0x14, D_800735C4);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 0x129, M2C_FIELD(arg0, s32*, 0x18) - 0x10, 0xA2, 0x10, D_82009098[M2C_FIELD(arg0, s32*, 0x738) - 1]);
    func_8001AB6C();
    func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    func_8001A384(4, 0);
    func_8001A944(M2C_FIELD(arg0, s32*, 0x14) + 0x12A, M2C_FIELD(arg0, s32*, 0x18) - 0x10, D_82009CF0, D_820090A8[M2C_FIELD(arg0, s32*, 0x738)]);
    func_8001ABBC();
}

typedef struct {
    /* 0x00 */ s32* table;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} TableArgs;

extern Color82001CCC D_820090C0;
extern s32 D_8200AC58[];
void func_800310D8(void*, s32, s32, s32, TableArgs*);

/**
 * Draws using the menu object arg0 (layout not established; it reads the words
 * at 0x14, 0x18 and 0x1C as position/size values): calls func_82002EE4 at
 * (+6, +0x88) with the third argument being word 0x1C minus 0xC, emits the
 * display list D_80060270 and fills a 2 by 0xB6 rectangle with colour D_820090C0
 * at (+6, +0x9C). Then builds a TableArgs {D_8200AC58, 0x18, 0x10, 0} and calls
 * func_800310D8 on the sub-object at arg0 + 0x6E4 at (+8, +0xAC) with a mode
 * word of 0xFED, or 0xFEF when arg1 is 1, or 0xFFD when arg1 is 2.
 * What the mode word's bits mean is not yet established.
 */
void func_82003118(s8* arg0, s32 arg1) {
    s32 sp44;
    TableArgs sp34;

    sp44 = 0xFED;
    func_82002EE4(M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x88, M2C_FIELD(arg0, s32*, 0x1C) - 0xC);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x9C, 2, 0xB6, D_820090C0);
    sp34.table = D_8200AC58;
    sp34.unk_04 = 0x18;
    sp34.unk_08 = 0x10;
    sp34.unk_0C = 0;
    switch (arg1) {
        case 1:
            sp44 = 0xFEF;
            break;
        case 2:
            sp44 = 0xFFD;
            break;
    }
    func_800310D8(arg0 + 0x6E4, M2C_FIELD(arg0, s32*, 0x14) + 8, M2C_FIELD(arg0, s32*, 0x18) + 0xAC, sp44, &sp34);
}

void func_82003234(s8* arg0) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x6A, 0x88, 0xE8, D_82008F5C);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 0x8E, M2C_FIELD(arg0, s32*, 0x18) + 0x6A, 0x18C, 0xE8, D_82008F58);
}

void func_820032E8(s8* arg0) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x6A, 0x88, 0x1E, D_82008F5C);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 0x8E, M2C_FIELD(arg0, s32*, 0x18) + 0x6A, 0x18C, 0x1E, D_82008F58);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8200339C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_8200339C.s")
#endif

void func_82003688(s32 arg0) {
    func_8002E3F0(arg0 + 0x2F8);
}

typedef struct { s32 w[20]; } Words80;

typedef struct {
    /* 0x000 */ char unk000[0x48];
    /* 0x048 */ s32 unk_48;
    /* 0x04C */ char unk04C[0x98];
    /* 0x0E4 */ Slot54 slots[6];
    /* 0x2DC */ char unk2DC[0x20];
    /* 0x2FC */ s16* unk_2FC;
    /* 0x300 */ s32 cur;
    /* 0x304 */ char unk304[0x3E0];
    /* 0x6E4 */ Words80** records;
    /* 0x6E8 */ char unk6E8[4];
    /* 0x6EC */ s32 recordIndex;
    /* 0x6F0 */ char unk6F0[0x44];
    /* 0x734 */ s32 unk_734;
    /* 0x738 */ char unk738[8];
    /* 0x740 */ s32 mode;
    /* 0x744 */ s32 unk_744;
    /* 0x748 */ s32 picked;
    /* 0x74C */ char unk74C[0x38];
    /* 0x784 */ s32 unk_784;
} SlotMenu;

void func_820080B8(s8*, s32, s32, s32);
void func_820081C8(s8*, s32, s32, s32, s32);
s32 func_82001558(void*, s32*);
s32 func_82000258(void*);

/**
 * Decides the next state of the six-slot menu. Clears `picked`, then, if `mode`
 * is non-zero, inspects the slots in this order and returns the first result
 * that applies:
 *   1. func_82001558 reports a positive count: call func_820080B8 on the struct at +0x320,
 *      store the reported slot index in `cur`, call func_82002668 on +0x2F8,
 *      return 2.
 *   2. func_820001B8 finds a flagged slot: set `picked`, store its index in
 *      `cur`, then return 8 if bit 0 of unk_784 is set, otherwise call
 *      func_820081C8 on the struct at +0x370 and return 4.
 *   3. `mode` is 1 and func_82000258 is non-zero: return 6 if bit 1 of unk_784
 *      is set, otherwise 5.
 * Otherwise (including when `mode` is 0) returns 0xA.
 * What the individual return values mean is not established from this function.
 */
s32 func_820036A8(SlotMenu* arg0) {
    Slot54* found;
    s32 sp38;
    s32 sp34;
    s32 ret;

    arg0->picked = 0;
    if (arg0->mode == 0) {
        ret = 0xA;
    } else {

        sp38 = func_82001558(arg0->slots, &sp34);
        if (sp38 > 0) {
            func_820080B8((s8*)arg0 + 0x320, 0x9C, 0x105, sp38);
            arg0->cur = sp34;
            func_82002668((SlotFlags*)((s8*)arg0 + 0x2F8));
            ret = 2;
        } else {
            found = func_820001B8(arg0->slots, &sp38);
            if (found != NULL) {
                arg0->picked = 1;
                arg0->cur = found - arg0->slots;
                if (arg0->unk_784 & 1) {
                    ret = 8;
                } else {
                    func_820081C8((s8*)arg0 + 0x370, 0xA6, 0x105, arg0->unk_744, sp38);
                    ret = 4;
                }
            } else if ((arg0->mode == 1) && (func_82000258(arg0->slots) != 0)) {
                if (arg0->unk_784 & 2) {
                    ret = 6;
                } else {
                    ret = 5;
                }
            } else {
                ret = 0xA;
            }
        }
    }
    return ret;
}


extern s32 D_8200AC58[];

/**
 * Copies the 0x50-byte record `*records[recordIndex]` into the payload of the
 * Slot54 selected by `cur`, clears that slot's `flag`, clears the s16 at
 * unk_2FC[cur], and sets D_8200AC58[(unk_48 * 6 + cur) % 24] to -1.
 * Also sets unk_734 to 1 and ORs bit 0 into unk_784.
 * The meaning of these fields is not yet established; names are structural only.
 */
void func_820037D0(SlotMenu* arg0) {
    arg0->unk_734 = 1;
    arg0->unk_784 |= 1;
    *(Words80*)arg0->slots[arg0->cur].unk04 = (*arg0->records)[arg0->recordIndex];
    arg0->slots[arg0->cur].flag = 0;
    arg0->unk_2FC[arg0->cur] = 0;
    D_8200AC58[(arg0->unk_48 * 6 + arg0->cur) % 24] = -1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_820038B0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820038B0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82004020; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82004020.s")
#endif

void func_82004240(s8 *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 1) = 0;
    M2C_FIELD(arg0, s16 *, 2) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82004268; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82004268.s")
#endif

M2C_UNK func_82004268(s8 *, s8 *, s8 *, s32, s32, s32); /* extern */

void func_820044D0(s8 *arg0) {
    func_82004268(arg0 + 0x4358, arg0 + 0x4360, arg0 + 0x4340, M2C_FIELD(arg0, s32 *, 0x4370), M2C_FIELD(arg0, s32 *, 0x4374), M2C_FIELD(arg0, s32 *, 0x501C));
}

#ifdef NON_MATCHING
/* TODO: decompile func_82004518; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82004518.s")
#endif

u8 func_80022B4C(s32);
u8 func_8000B2E8(void);

/*
 * func_82004B0C
 *
 * Recomputes two masks in the object at arg0 and then calls
 * func_82004518(arg0, 1, 0). Word +0x5018 gets bit i set for each i in 0..3
 * where func_80022B4C(i) returns 0. Word +0x5010 is set to func_8000B2E8()
 * and word +0x5014 to the number of bits among bits 0..3 of that value that
 * are set.
 */
void func_82004B0C(s32 arg0) {
    s32 i;

    M2C_FIELD(arg0, s32*, 0x5018) = 0;
    for (i = 0; i < 4; i++) {
        if (func_80022B4C(i) == 0) {
            M2C_FIELD(arg0, s32*, 0x5018) |= 1 << i;
        }
    }
    M2C_FIELD(arg0, s32*, 0x5010) = func_8000B2E8();
    M2C_FIELD(arg0, s32*, 0x5014) = 0;
    for (i = 0; i < 4; i++) {
        if ((M2C_FIELD(arg0, s32*, 0x5010) >> i) & 1) {
            M2C_FIELD(arg0, s32*, 0x5014) += 1;
        }
    }
    func_82004518(arg0, 1, 0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_82004BC0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82004BC0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82004CE0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82004CE0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82004E9C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82004E9C.s")
#endif

/*
 * func_8200569C
 *
 * Writes two words in the structure `arg0` points to, derived from the
 * bytes D_800AE8F0[0] and D_800AE8F0[1] of the session context, and then
 * calls func_82004518(arg0, 2, 0) or func_82004518(arg0, 3, 0).
 *
 *   D_800AE8F0[0] == 0:
 *     arg0->0x43AC = 0
 *     arg0->0x4418 = 0 if D_800AE8F0[1] == 0, else 1 if it is 2, else 2
 *     func_82004518(arg0, 2, 0)
 *   otherwise:
 *     arg0->0x43AC = 1
 *     arg0->0x4418 = 0 if D_800AE8F0[0] == 2, else 1
 *     func_82004518(arg0, 3, 0)
 *
 * func_82004518 is still assembly, so what the 2 / 3 select is not
 * established.  The first argument of every call is `arg0` itself; the ROM
 * never writes $a0 before the call, so it is the caller's argument passed
 * through.
 */
extern s8 D_800AE8F0;

void func_8200569C(s32 arg0) {
    s32 var_v0;

    if (D_800AE8F0 == 0) {
        M2C_FIELD((void*)arg0, s32 *, 0x43AC) = 0;
        if (((s8*)&D_800AE8F0)[1] == 0) {
            M2C_FIELD((void*)arg0, s32 *, 0x4418) = 0;
        } else {
            if (((s8*)&D_800AE8F0)[1] == 2) {
                var_v0 = 1;
            } else {
                var_v0 = 2;
            }
            M2C_FIELD((void*)arg0, s32 *, 0x4418) = var_v0;
        }
        func_82004518(arg0, 2, 0);
        return;
    }
    M2C_FIELD((void*)arg0, s32 *, 0x43AC) = 1;
    if (D_800AE8F0 == 2) {
        M2C_FIELD((void*)arg0, s32 *, 0x4418) = 0;
    } else {
        M2C_FIELD((void*)arg0, s32 *, 0x4418) = 1;
    }
    func_82004518(arg0, 3, 0);
}

extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;
s32 func_80025BD8(void);
void func_80027FF8(void*, s32);
s32 func_80002D98(s32);
void func_8200573C(void) {
    D_8200AD2C = func_80025BD8();
    if (D_8200AD2C != -1) {
        func_80027FF8(&D_8200AD30, D_8200AD2C);
    }
    D_8200AD28 = func_80002D98(0x5020);
    func_82004B0C(D_8200AD28);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8200579C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_8200579C.s")
#endif

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_82004CE0(s32);                         /* extern */
M2C_UNK func_82004E9C(s32);                         /* extern */
extern s32 D_8200AD28;

void func_820058BC(s32 arg0) {
    func_8000B1FC();
    func_8000B220();
    func_82004CE0(D_8200AD28);
    func_82004E9C(D_8200AD28);
}

M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK func_82004CE0(s32);                         /* extern */
extern M2C_UNK D_82009E18;
extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;

s32 func_820058FC(s32 arg0) {
    M2C_UNK *var_a1;

    func_82004CE0(D_8200AD28);
    if (D_8200AD2C == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8200AD30;
    }
    func_80028060(0, var_a1, &D_82009E18, D_8200AD2C);
    return 0;
}

M2C_UNK func_80002DC0(s32);                         /* extern */
extern s32 D_8200AD28;

void func_82005958(void) {
    func_80002DC0(D_8200AD28);
}

extern s32 D_8200AD08[8];
extern s32 D_8200AC40;
extern s32 D_820090DC[8];
s32 func_800044AC(s32, s32);

void func_8200597C(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_8200AD08[i] = func_800044AC(D_8200AC40, D_820090DC[i]);
    }
}

void func_8001A194(s32, s32);
s32 func_80017860(s32);
u16* func_80018F2C(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80017FDC(s32, s32, s32, s32);
s32 func_80004154(u8*, u8*, s32, s32);
void func_80017934(void);
void func_800040B4(s32, u8*, u8*);
void func_80003EB8(s32, u8*, u8*, s32);
s32 func_80001B10(u8*);
void func_8200569C(s32);
void func_80005B98(s32);
void func_80006828(s32, void*);
void func_8000A7B0(s32);
void func_80006998(s32);
void func_8000A7FC(s32);
void func_80006724(void);
void func_8000675C(void);
s32 func_8200579C(s32);
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_0A000000[];
extern u8 D_0A000C80[];
extern u8 D_0A0016D0[];
extern u8 D_003FFD60[];
extern u8 D_00400F70[];
extern u8 D_04000000[];
extern u8 D_004076E0[];
extern u8 D_05000000[];
extern u8 D_004199E0[];
extern u8 D_0042C4A0[];
extern u8 D_002F5940[];
extern u8 D_003139C0[];
extern s32 D_8200AC44;
extern u16* D_8200AC48;
extern s32 D_8200AC4C;
extern s32 D_8200AC50;
extern s32 D_8200ACFC;
extern s32 D_8200AD00;
extern s32 D_8200AD04;
extern s32 D_8200AD28;
extern s8 D_800AE8F0;
extern s32 D_82008F84;
M2C_UNK func_820059EC(void) {
    func_8001A194(0x3C, 0);
    D_8200AC44 = func_80017860(1);
    D_8200AC48 = func_80018F2C(D_8200AC44, 0x80, 0x78, 0, 0, 0x78, 0x78, 0);
    *D_8200AC48 &= ~2;
    *D_8200AC48 &= ~4;
    D_8200AC4C = 0;
    D_8200AC50 = func_80017FDC(D_8200AC44, 0x28, 0x28, 0x28);
    D_8200AC40 = func_80004154(D_002F5940, D_003139C0, 1, 1);
    func_80017934();

    func_800040B4(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    func_80003EB8(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    func_80003EB8(((u32)D_0A000000 & 0x0F000000) >> 0x18, D_003FFD60, D_00400F70, 0);
    func_80003EB8(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);
    func_80003EB8(((u32)D_05000000 & 0x0F000000) >> 0x18, D_004199E0, D_0042C4A0, 0);

    D_8200ACFC = func_80001B10(D_0A000000);
    D_8200AD00 = func_80001B10(D_0A000C80);
    D_8200AD04 = func_80001B10(D_0A0016D0);
    func_8200597C();
    func_8200573C();
    func_8000675C();

    if (M2C_FIELD(&D_800AE8F0, u16*, 0x1096) & 0x100) {
        M2C_FIELD(&D_800AE8F0, u16*, 0x1096) &= ~0x100;
        func_8200569C(D_8200AD28);
        func_80005B98(0xF);
        func_80006828(0x11, func_820058FC);
        func_8000A7B0(9);
    } else {
        func_80006828(8, func_8200579C);
    }
    func_80006828(0, func_820058BC);

    if (D_82008F84 == 0x8050) {
        func_80006998(0xFFFF);
        func_80005B98(0xF);
        func_80006828(0x11, func_820058FC);
        func_8000A7FC(0xF);
    } else {
        func_80006828(8, func_8200579C);
    }
    func_80006724();
    func_82005958();
}

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32); /* extern */
M2C_UNK func_820059EC();                            /* extern */
M2C_UNK func_82008F14();                            /* extern */
extern s8 D_00235D70;
extern s8 D_00238BD0;
extern s8 D_800AE8F0;
extern s32 D_82008F84;
extern M2C_UNK *D_8200ACF8;
extern s8 D_88000000;
s32 func_82005CCC(s32 arg0, M2C_UNK arg1)
{
  s32 temp_v1;
  func_8000256C(0x4D454E54);
  D_8200ACF8 = &D_800AE8F0;
  if (arg0 == 1)
  {
    func_82008F14();
  }
  else
  {
    func_820059EC();
  }
  func_80002620(0x4D454E54);
  temp_v1 = D_82008F84;
  if (temp_v1 == 0x8040)
  {
    func_80025BA0((((u32) (((s32) (&D_88000000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
  }
  return D_82008F84;
}
