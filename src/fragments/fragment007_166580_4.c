/* Fixed-layout split (from func_82002980); original translation-unit boundaries remain unconfirmed. */

#include "global.h"
#include "m2c_macros.h"

typedef struct {
    /* 0x00 */ s32 flag;
    /* 0x04 */ char unk04[0x50];
} Slot54;
typedef struct Mon82000258 {
    /* 0x00 */ char unk00[0x28];
    /* 0x28 */ u8 level;
    /* 0x29 */ char unk29[0x2B];
} Mon82000258; // size = 0x54
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
typedef struct Color82001CCC {
    u8 c[4];
} Color82001CCC;
typedef struct {
    /* 0x00 */ Slot54** slots;
    /* 0x04 */ u16* flags;
} SlotFlags;

M2C_UNK func_8002E3F0();
void func_82004518(s8*, s32, s32);
extern s32 D_8200AC58[];
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001ABBC(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A944(s32, s32, const char*, ...);
extern M2C_UNK D_800734A8;
void func_8002D900(FlagOwner*);
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color82001CCC);
extern Color82001CCC D_82008F5C;
extern Color82001CCC D_82008F58;

extern s32 D_82009C50;
extern s32 D_82009C6C;
extern s32 D_82009C84;
void func_82008524(s8* arg0, s32 arg1, s32 arg2, s32 arg3);
void func_82008870(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_80031B88(FlagOwner*);

void func_82002980(arg0)
    s8* arg0;
{
    s8* panel = NULL;
    s32 color;

    switch (M2C_FIELD(arg0, s32*, 4)) {
        case 1:
            if (!(M2C_FIELD(arg0, s32*, 0x788) & 2) && M2C_FIELD(arg0, s32*, 0x734) != 0) {
                func_82000020(D_8200AC58, (M2C_FIELD(arg0, s32*, 0x48) * 6) % 24, 6);
                M2C_FIELD(arg0, s32*, 0x734) = 0;
            }
            panel = arg0 + 0x14;
            break;
        case 2:
            panel = arg0 + 0x320;
            break;
        case 5:
            if (!(M2C_FIELD(arg0, s32*, 0x788) & 2)) {
                func_82008524(arg0 + 0x428, 0xA6, 0x105, M2C_FIELD(arg0, s32*, 0x744));
            }
            panel = arg0 + 0x428;
            break;
        case 4:
            panel = arg0 + 0x370;
            break;
        case 8:
            if (!(M2C_FIELD(arg0, s32*, 0x788) & 2)) {
                if (((Slot54*)(arg0 + 0xE4))[M2C_FIELD(arg0, s32*, 0x300)].flag != 0) {
                    color = -1;
                } else {
                    color = ((Slot54*)(arg0 + 0xE4))[M2C_FIELD(arg0, s32*, 0x300)].unk04[0];
                }
                func_82001340((FlagOwner*)(arg0 + 0x6E4), (Slot54*)(arg0 + 0xE4), color);
                func_80031B88((FlagOwner*)(arg0 + 0x6E4));
            }
            panel = arg0 + 0x14;
            break;
        case 6:
            func_8002D900((FlagOwner*)(arg0 + 0x6E4));
            panel = arg0 + 0x14;
            break;
        case 3:
            func_820009A4(arg0 + 0x5CC, 0x69, 0x7D, (s32)((Slot54*)(arg0 + 0xE4))[M2C_FIELD(arg0, s32*, 0x300)].unk04, (s32)&D_82009C50, M2C_FIELD(arg0, s32*, 0x744));
            panel = arg0 + 0x5CC;
            break;
        case 7:
            func_820009A4(arg0 + 0x5CC, 0x69, 0x7D, (s32)((Slot54*)(arg0 + 0xE4))[M2C_FIELD(arg0, s32*, 0x300)].unk04, (s32)&D_82009C6C, M2C_FIELD(arg0, s32*, 0x744));
            panel = arg0 + 0x5CC;
            break;
        case 9:
            func_820009A4(arg0 + 0x5CC, 0x69, 0x7D, M2C_FIELD(arg0, s32*, 0x6EC) * 0x50 + *M2C_FIELD(arg0, s32**, 0x6E4), (s32)&D_82009C84, M2C_FIELD(arg0, s32*, 0x744));
            panel = arg0 + 0x5CC;
            break;
        case 10:
            func_82008870(arg0 + 0x4DC, 0x7A, 0x10B, M2C_FIELD(arg0, s32*, 0x740) != 0, M2C_FIELD(arg0, s32*, 0x744));
            panel = arg0 + 0x4DC;
            break;
        case 12:
            panel = arg0 + 0x74C;
            break;
    }
    M2C_FIELD(arg0, s8**, 0xC) = panel;
}


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

void func_800306E0(s8*, s32);
extern u8 D_800AAF50[];
typedef struct List82002C3C {
    u8** items;
    s32 unk4;
    s32 count;
} List82002C3C;

void func_82002C3C(s8* arg0) {
    s32 sel = M2C_FIELD(arg0, s32*, 0x48);
    s32 mode = M2C_FIELD(arg0, s32*, 0x738);
    s32 i;
    s32 count;
    u8** list;
    List82002C3C* obj;

    if (mode != 5) {
        obj = M2C_FIELD(arg0, List82002C3C**, 0x40);
        count = obj->count;
        list = obj->items;
        for (i = 0; i < count && (*list)[0] == 0 && (*list)[1] == 0x20; i++, list++) {
            if (mode - 1 == (*list)[2]) {
                sel = i;
                break;
            }
        }
    }
    func_800306E0(arg0 + 0x40, sel);
    mode = M2C_FIELD(arg0, s32*, 0x738);
    if (mode == 5) {
        M2C_FIELD(arg0, u8**, 0x744) = D_800AAF50;
    } else {
        M2C_FIELD(arg0, u8**, 0x744) = D_800AAF50 + (mode - 1) * 0x24;
    }
    M2C_FIELD(arg0, s32*, 0x734) = 0;
    M2C_FIELD(arg0, u8**, 0x58) = M2C_FIELD(arg0, u8**, 0x744);
    M2C_FIELD(arg0, u8**, 0x6FC) = M2C_FIELD(arg0, u8**, 0x744);
    func_82002BF8(arg0, 1, 0);
}

extern s32 D_8200AC50;
extern s32 D_8200ACFC;
extern s32 D_8200AD00;
extern s32 D_8200AC58[];
extern M2C_UNK D_82009C98;
void func_82001810();
extern M2C_UNK func_820020EC;
void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK func_8002EC24(s8*, s32, s8*, M2C_UNK, M2C_UNK*, s32, s32);
M2C_UNK func_80030894(s8*, s8*, s8*, M2C_UNK, s32, M2C_UNK*, s32, s32);
M2C_UNK func_80027410(s8*, s32, M2C_UNK, M2C_UNK, s32);
void func_80018168(s8* arg0);
void func_82002C3C(s8*);

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

s32 func_8002AE6C(s8*);
void func_800189C0(s32, s32);
void func_800069CC(void);
void func_8002F3C4(s8*, s32, s32, s32, s32);
void func_8200288C(s8*, s32);
void func_8200813C(s8*);
void func_820082EC(s8*);
void func_82008640(s8*);
void func_820089D4(s8*);
void func_82000C5C(s8*);
void func_8002D024(s8*);
extern s32 D_8200AC50;
void func_8200339C(s8* arg0) {
    if (func_8002AE6C(arg0 + 0x14) != 0) {
        return;
    }
    func_82002FF8(arg0);
    switch (M2C_FIELD(arg0, s32*, 4)) {
        case 1:
            func_800189C0(D_8200AC50, 0);
            func_800069CC();
            func_8002F3C4(arg0 + 0x40, M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x16, 0xFFF, M2C_FIELD(arg0, s32*, 0x73C));
            break;
        case 2:
            func_800189C0(D_8200AC50, 0);
            func_800069CC();
            func_8200288C(arg0, 1);
            func_82003234(arg0);
            func_8200813C(arg0 + 0x320);
            break;
        case 6:
        case 8:
            func_800189C0(D_8200AC50, 0);
            func_800069CC();
            func_8200288C(arg0, (M2C_FIELD(arg0, s32*, 4) == 6) ? 1 : 2);
            func_82003118(arg0, (M2C_FIELD(arg0, s32*, 4) == 6) ? 0 : 1);
            func_820032E8(arg0);
            break;
        case 10:
            func_800189C0(D_8200AC50, 0);
            func_800069CC();
            func_8200288C(arg0, 0);
            func_82003234(arg0);
            func_820089D4(arg0 + 0x4DC);
            break;
        case 4:
            func_800189C0(D_8200AC50, 0);
            func_800069CC();
            func_8200288C(arg0, 0);
            func_82003234(arg0);
            func_820082EC(arg0 + 0x370);
            break;
        case 5:
            func_800189C0(D_8200AC50, 0);
            func_800069CC();
            func_8200288C(arg0, 0);
            func_82003234(arg0);
            func_82008640(arg0 + 0x428);
            break;
        case 7:
        case 9:
            func_8200288C(arg0, 2);
            func_82003118(arg0, (M2C_FIELD(arg0, s32*, 4) == 7) ? 0 : 2);
            func_820032E8(arg0);
            func_82000C5C(arg0 + 0x5CC);
            break;
        case 3:
            func_8200288C(arg0, 2);
            func_82003234(arg0);
            func_82000C5C(arg0 + 0x5CC);
            break;
        case 11:
            func_800189C0(D_8200AC50, 0);
            func_800069CC();
            func_8200288C(arg0, 0);
            func_82003234(arg0);
            break;
        case 12:
            func_800189C0(D_8200AC50, 0);
            func_800069CC();
            func_8002F3C4(arg0 + 0x40, M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x16, 0xFFF, M2C_FIELD(arg0, s32*, 0x73C));
            func_8002D024(arg0 + 0x74C);
            break;
    }
}

s32 func_82003688(s32 arg0) {
    return func_8002E3F0(arg0 + 0x2F8);
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
s32 func_82000258(Mon82000258*);

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

typedef struct Str82009D28 { char s[7]; } Str82009D28;
typedef struct Str82009D40 { char s[11]; } Str82009D40;
typedef struct Mon82004020 { s32 data[0x14]; } Mon82004020;
typedef struct Entry82004020 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Mon82004020 mon;
} Entry82004020; // size = 0x54
typedef struct Src82004020 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char name[0x10];
    /* 0x18 */ s32 count;
    /* 0x1C */ Entry82004020 entries[1];
} Src82004020;
extern u8 D_800AAF74[];
extern char D_82009D28[];
extern char D_82009D40[];
char* func_8000A460(char*, const char*);
void func_80058410(void*, void*, s32, s32);
void func_82004020(u8* arg0, u8* arg1, s32 arg2, Src82004020* arg3) {
    s32 i;
    s32 n;
    char* name;

    if (arg2 == 5) {
        arg0[0] = 2;
        arg0[1] = 1;
        M2C_FIELD(arg0, u8**, 4) = D_800AAF74;
        name = (char*)(arg0 + 8);
        *(Str82009D28*)name = *(Str82009D28*)D_82009D28;
        M2C_FIELD(arg0, s32*, 0x18) = 0;
    } else {
        arg0[0] = 1;
        arg0[1] = arg2 - 1;
        M2C_FIELD(arg0, u8**, 4) = D_800AAF50 + (arg2 - 1) * 0x24;
        name = (char*)(arg0 + 8);
        if (arg3->unk_01 == 0x20 && arg2 == arg3->unk_02 + 1) {
            func_8000A460(name, arg3->name);
            M2C_FIELD(arg0, s32*, 0x18) = arg3->unk_04;
        } else {
            M2C_FIELD(arg0, s32*, 0x18) = 0;
            func_8000A460(name, ((char**)&D_820090C0)[arg2]);
        }
    }
    for (i = 0, n = 0; i < arg3->count; i++) {
        if (arg3->entries[i].unk_00 == 0) {
            ((Mon82004020*)(arg0 + 0x1C))[n++] = arg3->entries[i].mon;
        }
    }
    arg0[2] = n;
    M2C_FIELD(arg0, u8**, 0x1FC) = arg1;
    M2C_FIELD(arg1, s16*, 0) = 0;
    arg1[2] = arg0[2];
    func_80058410(arg0 + 0x1C, arg1 + 0x28, 0x1E0, n);
    *(Str82009D40*)(arg1 + 4) = *(Str82009D40*)D_82009D40;
    func_8000A460((char*)(arg1 + 0x14), name);
}

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

extern s8* D_8200ACF8;
void func_800257F0(u8);

void func_82004268(s32* arg0, s32* arg1, Src82004020** arg2, s32 arg3, s32 arg4, s32 arg5) {
    Src82004020* src;

    D_8200ACF8[0] = arg3;
    D_8200ACF8[1] = arg4;
    if (D_8200ACF8[0] == 2) {
        D_8200ACF8[2] = arg5;
    }
    if ((D_8200ACF8[0] == 1) || (D_8200ACF8[0] == 2)) {
        if (arg0[0] > 0) {
            src = arg2[arg0[0] - 1];
            if (src->unk_01 == 0x20) {
                M2C_FIELD(D_8200ACF8, u8*, 0x1094) = src->unk_02;
            } else {
                M2C_FIELD(D_8200ACF8, s8*, 0x1094) = -1;
            }
            func_800257F0(M2C_FIELD(D_8200ACF8, u8*, 0x1094));
        }
    }
    M2C_FIELD(D_8200ACF8, u32*, 0x108C) = -1;
    M2C_FIELD(D_8200ACF8, u32*, 0x1090) = -1;
    func_82004240(D_8200ACF8 + 0x1034);
    func_82004240(D_8200ACF8 + 0x105C);
    D_8200ACF8[4] = 0;
    D_8200ACF8[0x208] = 0;
    D_8200ACF8[0x40C] = 0;
    D_8200ACF8[0x610] = 0;
    if (arg0[0] > 0) {
        func_82004020(D_8200ACF8 + 4, D_8200ACF8 + 0x814, arg0[0], arg2[arg0[0] - 1]);
        M2C_FIELD(D_8200ACF8, s8**, 0x103C + M2C_FIELD(D_8200ACF8, u8*, 0x1035) * 4) = D_8200ACF8 + 4;
        M2C_FIELD(D_8200ACF8, u8*, 0x1035)++;
    }
    if (arg0[1] > 0) {
        func_82004020(D_8200ACF8 + 0x208, D_8200ACF8 + 0xA1C, arg0[1], arg2[arg0[1] - 1]);
        M2C_FIELD(D_8200ACF8, s8**, 0x103C + M2C_FIELD(D_8200ACF8, u8*, 0x1035) * 4) = D_8200ACF8 + 0x208;
        M2C_FIELD(D_8200ACF8, u8*, 0x1035)++;
    }
    if (arg1[0] > 0) {
        func_82004020(D_8200ACF8 + 0x40C, D_8200ACF8 + 0xC24, arg1[0], arg2[arg1[0] - 1]);
        M2C_FIELD(D_8200ACF8, s8**, 0x1064 + M2C_FIELD(D_8200ACF8, u8*, 0x105D) * 4) = D_8200ACF8 + 0x40C;
        M2C_FIELD(D_8200ACF8, u8*, 0x105D)++;
    }
    if (arg1[1] > 0) {
        func_82004020(D_8200ACF8 + 0x610, D_8200ACF8 + 0xE2C, arg1[1], arg2[arg1[1] - 1]);
        M2C_FIELD(D_8200ACF8, s8**, 0x1064 + M2C_FIELD(D_8200ACF8, u8*, 0x105D) * 4) = D_8200ACF8 + 0x610;
        M2C_FIELD(D_8200ACF8, u8*, 0x105D)++;
    }
}

void func_82004268(s32*, s32*, Src82004020**, s32, s32, s32);

void func_820044D0(s8 *arg0) {
    func_82004268((s32*)(arg0 + 0x4358), (s32*)(arg0 + 0x4360), (Src82004020**)(arg0 + 0x4340), M2C_FIELD(arg0, s32 *, 0x4370), M2C_FIELD(arg0, s32 *, 0x4374), M2C_FIELD(arg0, s32 *, 0x501C));
}
