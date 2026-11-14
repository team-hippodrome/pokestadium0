/* Stadium Zero fragment016_252E10. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_list/lab_pc_list_1D7B40.c, src/fragments/lab_pc_list/lab_pc_list_1E46B0.c. */

#include "lab_pokemon_list.h"
#include "lab_item.h"
#include "pokemon_stats.h"
#include "save_data.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void LabPCList_ConsumeUsedTmItem(unk_func_8830867C_04C_030_02C_000*);
extern Gfx D_8910D028[];

#include "m2c_macros.h"
extern u8 D_8910D7D0[];
typedef struct unk_func_88309614 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
} unk_func_88309614;
typedef struct unk_func_88313894 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ unk_func_8830867C_02C_0CC_000_000* unk_0C;
    /* 0x10 */ char unk10[0xC];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ unk_func_88313894_020 unk_20;
    /* 0x40 */ unk_func_88313894_020 unk_40;
} unk_func_88313894;

void LabPCList_ReadDeckCategory(unk_func_8830867C_02C_154* arg0);
void LabPCList_WriteDeckCategory(unk_func_8830867C_02C_154* arg0);
s32 LabPCList_IsTmItemId(s32* arg0);
s32 LabPCList_IsHmItemId(s32* arg0);
s32 LabPCList_IsSpecialTmItemId(s32* arg0);
s32 LabPCList_CompareTmHmEntries(unk_func_88200FA0_030_038* arg0, unk_func_88200FA0_030_038* arg1);
s32 LabPCList_CanLearnMoveByLevelUp(s32 arg0, s32 arg1);
void LabPCList_ConsumeUsedTmItem(unk_func_8830867C_04C_030_02C_000* arg0);

typedef struct unk_func_89109990_010 {
    /* 0x00 */ void* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ char unk_14[0xC];
} unk_func_89109990_010; // size = 0x20

typedef struct unk_func_89109990 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk08[0x8];
    /* 0x10 */ unk_func_89109990_010* unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
} unk_func_89109990;

void func_80027804(void*, u8**, s32, s32);
void func_89109990(unk_func_89109990* arg0, u8** arg1, u8* arg2, s32 arg3) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    unk_func_89109990_010* var_s1 = arg0->unk_10;
    s32 var_t0 = 0;
    s32 i;
    s32 j;

    switch (arg0->unk_04) {
        case 0x11:
        case 0x13:
            break;
        case 0x20:
            var_t0 = 1;
            break;
        case 0x21:
            break;
    }

    arg0->unk_18 = arg0->unk_14;
    for (i = 0; i < arg0->unk_18; i++) {
        var_s1[i].unk_00 = arg0;
        var_s1[i].unk_04 = i;
        var_s1[i].unk_08 = 1;
        var_s1[i].unk_0C = var_t0;
        var_s1[i].unk_10 = 0;
        // The loop has to stay on one line: IDO orders the unrolled stores by source line.
        for (j = 0; j < arg3; j++) { arg1[j] = &arg2[j * 0x58]; }
        func_80027804(var_s1[i].unk_14, arg1, arg3, 0);
        arg1 += arg3;
        arg2 += arg3 * 0x58;
    }
}

typedef struct LabPCDeckNode89109B60 {
    /* 0x00 */ void* owner;
    /* 0x04 */ s32 index;
    /* 0x08 */ u8 entry[1];
} LabPCDeckNode89109B60;
typedef struct LabPCDeck89109B60 {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ LabPCDeckNode89109B60** nodes;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 count;
} LabPCDeck89109B60; // size = 0x20
typedef struct LabPCBox89109B60 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ LabPCDeck89109B60* decks;
    /* 0x14 */ char unk14[0x4];
    /* 0x18 */ s32 deckCount;
    /* 0x1C */ char unk1C[0x8];
} LabPCBox89109B60; // size = 0x24
typedef struct LabPCBoxList89109B60 {
    /* 0x00 */ LabPCBox89109B60* boxes;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 count;
} LabPCBoxList89109B60;

/* Stadium 1's LabPCList_LoadAllBoxes, without its box-count check and NULL deck check. */
void func_89109B60(LabPCBoxList89109B60* arg0) {
    s32 i;
    s32 j;
    s32 n;
    DeckHandle* handle;
    LabPCDeck89109B60* deck;
    LabPCDeckNode89109B60** node;
    LabPCBox89109B60* box;

    box = arg0->boxes;
    for (i = 0; i < arg0->count; i++, box++) {
        deck = box->decks;
        for (j = 0; j < box->deckCount; j++, deck++) {
            node = deck->nodes;
            handle = Deck_Open(box->unk_04, box->unk_08, j, 0);
            n = 0;
            while (TRUE) {
                if (Deck_ReadEntries(&(*node)->entry, 1, handle) == 0) {
                    break;
                }
                (*node)->owner = deck;
                (*node)->index = n;
                node++;
                n++;
            }
            Deck_CloseAndFlush(handle);
            deck->count = n;
        }
    }
}

typedef struct LabPCListSlotZero {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s32* unk_14;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 unk_1C;
} LabPCListSlotZero; // size = 0x20

typedef struct LabPCListBoxZero {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ LabPCListSlotZero* unk_10;
    /* 0x14 */ char unk14[0x4];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ char unk1C[0x8];
} LabPCListBoxZero; // size = 0x24

/** Flattens the list's nested entries into one list. */
void LabPCList_FlattenEntries(unk_func_88200FA0_030_038* arg0, unk_func_8830867C_02C_144* arg1) {
    s32 i;
    s32 j;
    s32 x;
    s32* var_v0;
    LabPCListSlotZero* var_v1;
    s32* var_t0;
    LabPCListBoxZero* var_a2;

    var_v0 = (s32*)arg0->unk_00;
    var_a2 = (LabPCListBoxZero*)arg1->unk_00;

    for (i = 0; i < arg1->unk_08; i++, var_a2++) {
        var_v1 = var_a2->unk_10;

        for (j = 0; j < var_a2->unk_18; j++, var_v1++) {
            if (var_v1->unk_0C != 0) {
                var_t0 = var_v1->unk_14;

                for (x = 0; x < var_v1->unk_1C; x++, var_t0++, var_v0++) {
                    *var_v0 = *var_t0;
                }
            }
        }
    }

    arg0->unk_08 = var_v0 - (s32*)arg0->unk_00;
}

typedef struct LabPCDeck89109D14 {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ s32 dirty;
    /* 0x14 */ LabPCDeckNode89109B60** nodes;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 count;
} LabPCDeck89109D14; // size = 0x20
void func_80023268(s32 arg0, s32 arg1, s32 arg2);

/* Stadium 1's LabPCList_SaveAllBoxes, with every deck flushed the same way. */
void func_89109D14(LabPCBoxList89109B60* arg0) {
    s32 i;
    s32 j;
    s32 x;
    DeckHandle* handle;
    LabPCDeck89109D14* deck;
    LabPCDeckNode89109B60** node;
    LabPCBox89109B60* box;

    box = arg0->boxes;
    for (i = 0; i < arg0->count; i++, box++) {
        deck = (LabPCDeck89109D14*)box->decks;
        for (j = 0; j < box->deckCount; j++, deck++) {
            if (deck->dirty != 0) {
                node = deck->nodes;
                handle = Deck_Open(box->unk_04, box->unk_08, j, 1);
                for (x = 0; x < deck->count; x++, node++) {
                    Deck_WriteEntries((*node)->entry, 1, handle);
                    if ((box->unk_04 == 0x20) || (box->unk_04 == 0x21)) {
                        func_80023268(box->unk_08, (*node)->entry[0], 3);
                    }
                }
                Deck_CloseAndFlush(handle);
            }
            if (1) {} // karodo: also in Stadium 1's version
        }
    }
}

s32 func_80025BD8(void);
void func_80027410(void*, void*, s32, s32, s32);
void func_80027FF8(void*, s32);
s32 func_800246A8(s32, s32);
s32 Deck_GetSaveEntryTrainerId(s32, s32);
s32 Deck_GetSaveEntryName(s32 arg0, s32 arg1, u8* arg2);
s32 func_80024ADC(s32, s32);
s32 func_8000A4E8(char*, char*);
void func_89109E5C(unk_func_8830867C_02C_154* arg0, void* arg1, void* arg2, void* arg3) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 temp_s1;
    char sp54[4];
    GbSavePortSummary sp48;
    char sp38[16];
    s32 i;

    arg0->unk_00 = 0x23;
    arg0->unk_01 = func_80025BD8();
    arg0->unk_02 = 0;
    arg0->unk_04 = 1;
    func_80027410(&arg0[0].unk_0C, arg1, 2, 0x14, 0);

    arg0[1].unk_00 = 0x22;
    arg0[1].unk_01 = arg0->unk_01;
    arg0[1].unk_02 = 0;
    arg0[1].unk_04 = 1;
    func_80027410(&arg0[1].unk_0C, arg2, 2, 0x32, 0);

    arg0[2].unk_00 = 0x12;
    arg0[2].unk_01 = 0;
    func_80027410(&arg0[2].unk_0C, arg3, 2, 0x64, 0);

    func_80027FF8(&sp48, arg0->unk_01);

    for (i = 0; i < 4; i++) {
        if ((func_800246A8(0x12, i) != 0) && (func_80024ADC(0x12, i) > 0)) {
            temp_s1 = Deck_GetSaveEntryTrainerId(0x12, i);
            Deck_GetSaveEntryName(0x12, i, sp38);
            if ((sp48.trainerId == temp_s1) && (func_8000A4E8(sp54, sp38) == 0)) {
                break;
            }
        }
    }

    if (i < 4) {
        arg0[2].unk_02 = i;
        arg0[2].unk_04 = 1;
    } else {
        arg0[2].unk_04 = 0;
    }
}

/** Reads a deck category into the list. */
void LabPCList_ReadDeckCategory(unk_func_8830867C_02C_154* arg0) {
    DeckHandle* sp24;

    sp24 = Deck_Open(arg0->unk_00, arg0->unk_01, arg0->unk_02, 0);
    arg0->unk_14 = Deck_ReadEntries(arg0->unk_0C, arg0->unk_10, sp24);
    Deck_CloseAndFlush(sp24);
    arg0->unk_08 = 0;
}

/** Writes the list back to a deck category. */
void LabPCList_WriteDeckCategory(unk_func_8830867C_02C_154* arg0) {
    DeckHandle* sp24 = Deck_Open(arg0->unk_00, arg0->unk_01, arg0->unk_02, 1);

    Deck_WriteEntries(arg0->unk_0C, arg0->unk_14, sp24);
    Deck_CloseAndFlush(sp24);
    arg0->unk_08 = 0;
}

/** Returns whether an item ID is a TM; converts the ID to the TM index. */
s32 LabPCList_IsTmItemId(s32* arg0) {
    if ((*arg0 >= 0xC9) && (*arg0 < 0xFB)) {
        *arg0 -= 0x65;
        return 1;
    }
    if ((*arg0 >= 0xC4) && (*arg0 < 0xC9)) {
        *arg0 += 4;
        return 1;
    }
    return 0;
}

/** Returns whether an item ID is an HM. */
s32 LabPCList_IsHmItemId(s32* arg0) {
    static u8 D_8831A250[] = { 0x23, 0x24, 0x25, 0x26, 0x27, 0x28 };

    s32 i;

    for (i = 0; i < 6; i++) {
        if (*arg0 == D_8831A250[i]) {
            *arg0 = i;
            return 1;
        }
    }

    return 0;
}

/** Returns whether an item ID is the special TM. */
s32 LabPCList_IsSpecialTmItemId(s32* arg0) {
    static u8 D_8831A258[] = { 0x4F };

    s32 i;

    for (i = 0; i < 1; i++) {
        if (*arg0 == D_8831A258[i]) {
            *arg0 = i + 0x32;
            return 1;
        }
    }

    return 0;
}

/** List comparison for TM and HM entries. */
s32 LabPCList_CompareTmHmEntries(unk_func_88200FA0_030_038* arg0, unk_func_88200FA0_030_038* arg1) {
    return (arg0->unk_08 - arg1->unk_08 != 0) ? arg0->unk_08 - arg1->unk_08 : (s32)arg0[1].unk_00 - (s32)arg1[1].unk_00;
}

typedef struct TmEntry8910A21C {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ unk_func_8830867C_02C_154* unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} TmEntry8910A21C; // size = 0x14
void func_8910A21C(unk_func_88200FA0_030_038* arg0, TmEntry8910A21C* arg1, unk_func_8830867C_02C_154* arg2, s32 arg3) {
    unk_func_88205880_00D0** var_s6;
    unk_func_8830867C_02C_154* var_s4;
    s32 i;
    TmEntry8910A21C* var_s1;
    s32 j;
    s32 sp50;
    s32 var_s0;
    s32 var_v0;
    u8* var_s2;

    var_s6 = arg0->unk_00;
    var_s4 = arg2;
    var_s1 = arg1;

    for (i = 0; i < arg3; i++, var_s4++) {
        if (var_s4->unk_04 != 0) {
            var_s2 = var_s4->unk_0C;

            for (j = 0; j < var_s4->unk_14; j++, var_s2 += 2) {
                var_s0 = 0;
                sp50 = *var_s2;
                if (LabPCList_IsTmItemId(&sp50) != 0) {
                    var_s0 = 1;
                } else if (LabPCList_IsHmItemId(&sp50) != 0) {
                    var_s0 = 1;
                } else if (LabPCList_IsSpecialTmItemId(&sp50) != 0) {
                    var_s0 = 1;
                }

                if (var_s0 != 0) {
                    var_s1->unk_00 = var_s2;
                    var_s1->unk_04 = var_s4;
                    var_s1->unk_08 = sp50;

                    if (var_s4->unk_00 == 0x23) {
                        var_s1->unk_0C = 0;
                    } else {
                        if (var_s4->unk_00 == 0x22) {
                            var_v0 = 1;
                        } else {
                            var_v0 = 2;
                        }
                        var_s1->unk_0C = var_v0;
                    }
                    *var_s6 = (unk_func_88205880_00D0*)var_s1;

                    var_s1++;
                    var_s6++;
                }
            }
        }
    }

    arg0->unk_08 = var_s1 - arg1;
    PointerList_Sort(arg0, LabPCList_CompareTmHmEntries);
}

/** Returns whether a species learns a move by level up. */
s32 LabPCList_CanLearnMoveByLevelUp(s32 arg0, s32 arg1) {
    static SpeciesData D_8831757C[] = {
        { 0x06, 0x4E, 0x54, 0x4E, 0x64, 0x55, 0x14, 0x02, 0x2D, 0xD1, {0x0A, 0x2D, 0x34, 0x2B}, 0x03, {0xB5, 0x43, 0x4F, 0xCE, 0xE3, 0x08, 0x2E}, 0x00 },
        { 0x0C, 0x3C, 0x2D, 0x32, 0x46, 0x50, 0x07, 0x02, 0x2D, 0xA0, {0x5D, 0x00, 0x00, 0x00}, 0x00, {0x2A, 0x43, 0x38, 0xF0, 0x43, 0x28, 0x42}, 0x00 },
        { 0x30, 0x3C, 0x37, 0x32, 0x2D, 0x28, 0x07, 0x03, 0xBE, 0x4B, {0x21, 0x32, 0x00, 0x00}, 0x00, {0x20, 0x03, 0x38, 0xD0, 0x03, 0x28, 0x42}, 0x00 },
        { 0x31, 0x46, 0x41, 0x3C, 0x5A, 0x5A, 0x07, 0x03, 0x4B, 0x8A, {0x21, 0x32, 0x4D, 0x8D}, 0x00, {0x2A, 0x43, 0x38, 0xF0, 0x43, 0x28, 0x42}, 0x00 },
        { 0x32, 0x0A, 0x37, 0x19, 0x5F, 0x2D, 0x04, 0x04, 0xFF, 0x51, {0x0A, 0x00, 0x00, 0x00}, 0x00, {0xA0, 0x03, 0x08, 0xCE, 0x02, 0x88, 0x06}, 0x00 },
        { 0x33, 0x23, 0x50, 0x32, 0x78, 0x46, 0x04, 0x04, 0x32, 0x99, {0x0A, 0x2D, 0x5B, 0x00}, 0x00, {0xA0, 0x43, 0x08, 0xCE, 0x02, 0x88, 0x06}, 0x00 },
        { 0x8D, 0x3C, 0x73, 0x69, 0x50, 0x46, 0x05, 0x15, 0x2D, 0xC9, {0x0A, 0x6A, 0x47, 0x00}, 0x00, {0xB6, 0x7F, 0x0D, 0xC0, 0x83, 0x08, 0x16}, 0x00 },
        { 0x96, 0x6A, 0x6E, 0x5A, 0x82, 0x9A, 0x18, 0x18, 0x03, 0xDC, {0x5D, 0x32, 0x81, 0x5E}, 0x05, {0xB1, 0x7F, 0xAF, 0xF1, 0xAF, 0x38, 0x63}, 0x00 },
        { 0x97, 0x64, 0x64, 0x64, 0x64, 0x64, 0x18, 0x18, 0x2D, 0x40, {0x01, 0x00, 0x00, 0x00}, 0x03, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F}, 0x00 },
    };

    SpeciesData* var_v1;
    s32 i;

    var_v1 = &gSpeciesData[arg0 - 1];

    if (GbSave_GetPortGame(GbSave_GetActivePort()) == 7) {
        for (i = 0; i < 9; i++) {
            if (arg0 == D_8831757C[i].speciesId) {
                var_v1 = &D_8831757C[i];
            }
        }
    }
    return ((var_v1->tmHmLearnset[arg1 / 8] >> (arg1 % 8)) & 1) != 0;
}

s32 func_80020974(s32);
s32 BattleMon_CountMoves(u8* arg0);
s32 BattleMon_GetMoveIndex(s32, s32);

void func_8910A4C8(s8* arg0, u8* arg1) {
    s32 i;
    s32 j;
    s32 n;
    s32 n2;
    s32 k;
    s32 move;
    s8** base;
    s8* e;
    u8* p;

    base = M2C_FIELD(arg0, s8***, 0);
    for (i = 0; i < M2C_FIELD(arg0, s32*, 8); i++) {
        M2C_FIELD(base[i], s32*, 0x10) = 0;
        e = base[i];
        if (M2C_FIELD(e, s32*, 8) >= 100) {
            if (**(u8**)e >= 0xC9) {
                move = **(u8**)e - 0xC9;
            } else {
                move = **(u8**)e - 0x92;
            }
            n = BattleMon_CountMoves(arg1);
            for (j = 0; j < n; j++) {
                if (func_80020974(move) == arg1[j + 9]) {
                    break;
                }
            }
            if (j < n) {
                M2C_FIELD(base[i], s32*, 0x10) |= 8;
            }
            if (LabPCList_CanLearnMoveByLevelUp(arg1[0], move) == 0) {
                M2C_FIELD(base[i], s32*, 0x10) |= 0x10;
            }
        } else if (M2C_FIELD(e, s32*, 8) >= 50) {
            n2 = BattleMon_CountMoves(arg1);
            for (j = 0; j < n2; j++) {
                if ((BattleMon_GetMoveIndex((s32)arg1, j) != -2) && ((arg1 + j)[0x20] < 0xC0)) {
                    break;
                }
            }
            if (j >= n2) {
                M2C_FIELD(base[i], s32*, 0x10) |= 4;
            }
        } else {
            switch (**(u8**)e) {
                case 35:
                    if (M2C_FIELD(arg1, u16*, 0x14) >= 0x6400) {
                        M2C_FIELD(e, s32*, 0x10) |= 1;
                    }
                    break;
                case 36:
                    if (M2C_FIELD(arg1, u16*, 0x16) >= 0x6400) {
                        M2C_FIELD(e, s32*, 0x10) |= 1;
                    }
                    break;
                case 37:
                    if (M2C_FIELD(arg1, u16*, 0x18) >= 0x6400) {
                        M2C_FIELD(e, s32*, 0x10) |= 1;
                    }
                    break;
                case 38:
                    if (M2C_FIELD(arg1, u16*, 0x1A) >= 0x6400) {
                        M2C_FIELD(e, s32*, 0x10) |= 1;
                    }
                    break;
                case 39:
                    if (M2C_FIELD(arg1, u16*, 0x1C) >= 0x6400) {
                        M2C_FIELD(e, s32*, 0x10) |= 1;
                    }
                    break;
                case 40:
                    if (arg1[0x24] >= 100) {
                        M2C_FIELD(e, s32*, 0x10) |= 2;
                    }
                    break;
            }
        }
    }
}

/** Consumes a TM item after use. */
void LabPCList_ConsumeUsedTmItem(unk_func_8830867C_04C_030_02C_000* arg0) {
    if ((LabItem_IsQuantitylessItemForOperation(arg0->unk_00[0]->unk_00) != 0) || (arg0->unk_00[0]->unk_01 < 2)) {
        s32 tmp = arg0->unk_00[1]->unk_0C.unk_00;

        WordList_Remove(&arg0->unk_00[1]->unk_0C, ((s32)arg0->unk_00[0] - tmp) >> 1);
    } else {
        arg0->unk_00[0]->unk_01--;
    }
    arg0->unk_00[1]->unk_08 = 1;
}
