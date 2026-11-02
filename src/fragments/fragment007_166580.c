/* Stadium Zero fragment007_166580. */

#include "global.h"
#include "m2c_macros.h"

void func_82000020(s32* values, s32 first, s32 count) {
    s32 end = first + count;

    for (; first < end; first++) {
        values[first] = -1;
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

#ifdef NON_MATCHING
/* TODO: decompile func_82000140; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82000140.s")
#endif

Entry82000058* func_820001B8(Entry82000058* entries, s32* outCount) {
    Entry82000058* selected = NULL;
    s32 count = 0;
    s32 i;

    entries += 6;
    for (i = 0; i < 6; i++) {
        entries--;
        if (entries->unk_00 != 0) {
            selected = entries;
            count++;
        }
    }
    *outCount = count;
    return selected;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82000258; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82000258.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_820003D4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820003D4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8200053C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_8200053C.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_82000900; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82000900.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_820009A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820009A4.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_82001340; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82001340.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_82001708; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82001708.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82001810; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82001810.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82001BB4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82001BB4.s")
#endif

typedef struct Color82001CCC {
    u8 c[4];
} Color82001CCC;
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color82001CCC);

void func_82001C00(s32 x, s32 y, Color82001CCC color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x88, 0x64, color);
}

void func_82001C60(s32 x, s32 y, Color82001CCC color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x + 0x88, y, 0x18C, 0x64, color);
}

void func_82001CCC(s32 arg0, s32 arg1, Color82001CCC arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x214, 1, arg2);
    func_80029028(arg0, arg1 + 0x63, 0x214, 1, arg2);
}

#ifdef NON_MATCHING
/* TODO: decompile func_82001D64; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82001D64.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_820023E8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820023E8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82002528; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82002528.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82002668; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82002668.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82002778; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82002778.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_82002D5C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82002D5C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82002EE4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82002EE4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82002FF8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82002FF8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82003118; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82003118.s")
#endif

extern Color82001CCC D_82008F5C;
extern Color82001CCC D_82008F58;
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

M2C_UNK func_8002E3F0(s32);                         /* extern */

void func_82003688(s32 arg0) {
    func_8002E3F0(arg0 + 0x2F8);
}

#ifdef NON_MATCHING
/* TODO: decompile func_820036A8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820036A8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_820037D0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820037D0.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_82004B0C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82004B0C.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_8200569C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_8200569C.s")
#endif

extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;
s32 func_80025BD8(void);
void func_80027FF8(void*, s32);
s32 func_80002D98(s32);
void func_82004B0C(s32);
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
