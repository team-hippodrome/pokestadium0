/* Fixed-layout split (from FreeBattle_EnterEntryScreenState); original translation-unit boundaries remain unconfirmed. */

#include "global.h"
#include "m2c_macros.h"

typedef struct {
    /* 0x00 */ s32 flag;
    /* 0x04 */ char unk04[0x50];
} Slot54;
#include "fragments/fragment007_166580_types_2.h"
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

M2C_UNK GridMenu_UpdateCursor();
void FreeBattle_SetScreenState(s8*, s32, s32);
extern s32 D_8200AC58[];
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001ABBC(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A944(s32, s32, const char*, ...);
extern M2C_UNK D_800734A8;
void Menu_ClearItemFlags(FlagOwner*);
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color82001CCC);
extern Color82001CCC D_82008F5C;
extern Color82001CCC D_82008F58;

extern s32 D_82009C50;
extern s32 D_82009C6C;
extern s32 D_82009C84;
void FreeBattle_InitLevelSumWarning(s8* arg0, s32 arg1, s32 arg2, s32 arg3);
void FreeBattle_InitRentalConfirm(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ScrollGrid_SyncCursor(FlagOwner*);

/**
 * Enters an entry screen state and picks its panel: 1 the team list, 2, 4, 5 the level-sum
 * warning, 8 a team's Pokemon grid.
 * Seen in play: runs when 「エントリーポケモンのせんたく」 opens in state 1 (the team list).
 * @unverified States other than 1 not seen.
 */
void FreeBattle_EnterEntryScreenState(arg0)
    s8* arg0;
{
    s8* panel = NULL;
    s32 color;

    switch (M2C_FIELD(arg0, s32*, 4)) {
        case 1:
            if (!(M2C_FIELD(arg0, s32*, 0x788) & 2) && M2C_FIELD(arg0, s32*, 0x734) != 0) {
                FreeBattle_ClearIndices(D_8200AC58, (M2C_FIELD(arg0, s32*, 0x48) * 6) % 24, 6);
                M2C_FIELD(arg0, s32*, 0x734) = 0;
            }
            panel = arg0 + 0x14;
            break;
        case 2:
            panel = arg0 + 0x320;
            break;
        case 5:
            if (!(M2C_FIELD(arg0, s32*, 0x788) & 2)) {
                FreeBattle_InitLevelSumWarning(arg0 + 0x428, 0xA6, 0x105, M2C_FIELD(arg0, s32*, 0x744));
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
                FreeBattle_MarkPickedRentals((FlagOwner*)(arg0 + 0x6E4), (Slot54*)(arg0 + 0xE4), color);
                ScrollGrid_SyncCursor((FlagOwner*)(arg0 + 0x6E4));
            }
            panel = arg0 + 0x14;
            break;
        case 6:
            Menu_ClearItemFlags((FlagOwner*)(arg0 + 0x6E4));
            panel = arg0 + 0x14;
            break;
        case 3:
            FreeBattle_InitConfirmWindow(arg0 + 0x5CC, 0x69, 0x7D, (s32)((Slot54*)(arg0 + 0xE4))[M2C_FIELD(arg0, s32*, 0x300)].unk04, (s32)&D_82009C50, M2C_FIELD(arg0, s32*, 0x744));
            panel = arg0 + 0x5CC;
            break;
        case 7:
            FreeBattle_InitConfirmWindow(arg0 + 0x5CC, 0x69, 0x7D, (s32)((Slot54*)(arg0 + 0xE4))[M2C_FIELD(arg0, s32*, 0x300)].unk04, (s32)&D_82009C6C, M2C_FIELD(arg0, s32*, 0x744));
            panel = arg0 + 0x5CC;
            break;
        case 9:
            FreeBattle_InitConfirmWindow(arg0 + 0x5CC, 0x69, 0x7D, M2C_FIELD(arg0, s32*, 0x6EC) * 0x50 + *M2C_FIELD(arg0, s32**, 0x6E4), (s32)&D_82009C84, M2C_FIELD(arg0, s32*, 0x744));
            panel = arg0 + 0x5CC;
            break;
        case 10:
            FreeBattle_InitRentalConfirm(arg0 + 0x4DC, 0x7A, 0x10B, M2C_FIELD(arg0, s32*, 0x740) != 0, M2C_FIELD(arg0, s32*, 0x744));
            panel = arg0 + 0x4DC;
            break;
        case 12:
            panel = arg0 + 0x74C;
            break;
    }
    M2C_FIELD(arg0, s8**, 0xC) = panel;
}


/**
 * Sets the entry screen's state (and flags); without flag 1 it switches at once through
 * FreeBattle_EnterEntryScreenState, otherwise it defers the switch.
 * Seen in play: runs when 「エントリーポケモンのせんたく」 opens.
 * Seen in play (2026-11-13) ran when the エントリーポケモンのせんたく screen opened and when its rows were
 * picked.
 */
void FreeBattle_SetEntryScreenState(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x788) = arg2;
    if (arg2 & 1) {
        M2C_FIELD(M2C_FIELD(arg0, s8 **, 0xC), s32 *, 0x24) = 7;
        M2C_FIELD(arg0, s32 *, 8) = arg1;
        return;
    }
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    FreeBattle_EnterEntryScreenState();
}

void ScrollList_SetCursor(s8*, s32);
extern u8 D_800AAF50[];
typedef struct List82002C3C {
    u8** items;
    s32 unk4;
    s32 count;
} List82002C3C;

/**
 * Puts the entry list cursor on the row for the current entry mode, picks that mode's pick buffer
 * (D_800AAF50) and enters entry state 1.
 * Seen in play: runs when 「エントリーポケモンのせんたく」 opens.
 * @unverified Name from the code.
 */
void FreeBattle_InitEntryListCursor(s8* arg0) {
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
    ScrollList_SetCursor(arg0 + 0x40, sel);
    mode = M2C_FIELD(arg0, s32*, 0x738);
    if (mode == 5) {
        M2C_FIELD(arg0, u8**, 0x744) = D_800AAF50;
    } else {
        M2C_FIELD(arg0, u8**, 0x744) = D_800AAF50 + (mode - 1) * 0x24;
    }
    M2C_FIELD(arg0, s32*, 0x734) = 0;
    M2C_FIELD(arg0, u8**, 0x58) = M2C_FIELD(arg0, u8**, 0x744);
    M2C_FIELD(arg0, u8**, 0x6FC) = M2C_FIELD(arg0, u8**, 0x744);
    FreeBattle_SetEntryScreenState(arg0, 1, 0);
}

extern s32 D_8200AC50;
extern s32 D_8200ACFC;
extern s32 D_8200AD00;
extern s32 D_8200AC58[];
extern M2C_UNK D_82009C98;
void FreeBattle_DrawMonCell();
extern M2C_UNK FreeBattle_DrawTeamRow;
void Window_SetRect(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK ScrollList_Init(s8*, s32, s8*, M2C_UNK, M2C_UNK*, s32, s32);
M2C_UNK ScrollGrid_Init(s8*, s8*, s8*, M2C_UNK, s32, M2C_UNK*, s32, s32);
M2C_UNK func_80027410(s8*, s32, M2C_UNK, M2C_UNK, s32);
void func_80018168(s8* arg0);
void FreeBattle_InitEntryListCursor(s8*);

/**
 * Initializes the slot-menu object at arg0 (the layout other functions in this file
 * access as SlotMenu):
 *   - sets up the base window at +0x14 via Window_SetRect (arg1, arg2, size 0x220 x 0x158),
 *   - zeroes +0x00/+0x38/+0x3C, stores 0x801 at +0x28, &D_82009C98 at +0x34 and arg3 at +0xC4,
 *   - creates the sub-object at +0x40/+0x84 with ScrollList_Init (passing &FreeBattle_DrawTeamRow),
 *   - sets bit 0x10000 at +0x60,
 *   - fills the first 0x28 words of D_8200AC58 with -1,
 *   - stores 1 at +0x738, arg4 at +0x73C and the mode arg5 at +0x740, and calls FreeBattle_InitEntryListCursor,
 *   - when arg5 != 0, builds the record view at +0x684 (source D_8200ACFC if arg5 == 1,
 *     otherwise D_8200AD00, with different dimensions), links it through ScrollGrid_Init
 *     at +0x6E4/+0x694 (passing &FreeBattle_DrawMonCell) and sets bit 0x10000 at +0x704,
 *   - finally calls func_80018168 on D_8200AC50.
 * The meaning of arg1..arg5 beyond what is stored above is not established.
 * Seen in play: runs as 「エントリーポケモンのせんたく 1Pせんたくちゅう」 opens.
 */
void FreeBattle_InitEntrySelect(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s8* var_s1;

    Window_SetRect(arg0 + 0x14, arg1, arg2, 0x220, 0x158);
    M2C_FIELD(arg0, s32*, 0x38) = 0;
    M2C_FIELD(arg0, s32*, 0x3C) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0x801;
    M2C_FIELD(arg0, M2C_UNK**, 0x34) = &D_82009C98;
    M2C_FIELD(arg0, s32*, 0xC4) = arg3;
    ScrollList_Init(arg0 + 0x40, arg3, arg0 + 0x84, 3, &FreeBattle_DrawTeamRow, 0x214, 0x64);
    M2C_FIELD(arg0, s32*, 0x60) = M2C_FIELD(arg0, s32*, 0x60) | 0x10000;
    M2C_FIELD(arg0, s32*, 0) = 0;
    FreeBattle_ClearIndices(D_8200AC58, 0, 0x28);
    M2C_FIELD(arg0, s32*, 0x738) = 1;
    M2C_FIELD(arg0, s32*, 0x73C) = arg4;
    M2C_FIELD(arg0, s32*, 0x740) = arg5;
    FreeBattle_InitEntryListCursor(arg0);
    if (arg5 != 0) {
        if (arg5 == 1) {
            var_s1 = arg0 + 0x684;
            func_80027410(var_s1, D_8200ACFC, 0x50, 0x28, 0x28);
        } else {
            var_s1 = arg0 + 0x684;
            func_80027410(var_s1, D_8200AD00, 0x50, 0x21, 0x21);
        }
        ScrollGrid_Init(arg0 + 0x6E4, var_s1, arg0 + 0x694, 4, 3, &FreeBattle_DrawMonCell, 0x84, 0x32);
        M2C_FIELD(arg0, s32*, 0x704) = M2C_FIELD(arg0, s32*, 0x704) | 0x10000;
    }
    func_80018168((s8*)D_8200AC50);
}

extern Gfx D_80073450[];
extern u8 D_05000008[];
extern char D_82009CC8[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void Ui_DrawPrimColorRect(s32, s32, s32, s32, s32, s32, s32, s32);

/**
 * Emits the display list D_80073450 and the DECALRGBA combiner, then calls
 * func_8001B884 at (arg0, arg1) with D_05000008 as its texture argument (arg2
 * is passed straight through as the third argument), calls Ui_DrawPrimColorRect with
 * (arg0 + 0xE, arg1, 0x84, 0x14, ...) and then
 * prints the string D_82009CC8 at (arg0 + 0x10, arg1 + 2) in the color
 * stored at D_800734A8 using font 4.
 * What this draws is not yet established.
 * Seen in play: draws the 「レンタルポケモン」 title bar of the rental grid.
 */
void FreeBattle_DrawRentalTitle(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001B884(arg0, arg1, arg2, 0x14, D_05000008, 8, 0);
    Ui_DrawPrimColorRect(arg0 + 0xE, arg1, 0x84, 0x14, 0, 0, 0, 0xFF);
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
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, char*);

/**
 * Draws a labeled box using the menu object arg0 (layout not established; it
 * reads the words at 0x14, 0x18 and the mode index at 0x738). Calls
 * Ui_DrawTexturedFrameDecal at (word 0x14 + 0x127, word 0x18 - 0x12) with size 0xA6 by 0x14
 * and D_800735C4, emits D_80060270 and fills a 0xA2 by 0x10 rectangle at
 * (+0x129, -0x10) with the color D_82009098[mode - 1]. Then prints the string
 * D_82009CF0 at (+0x12A, -0x10) in the color D_800734A8, font 4, passing
 * D_820090A8[mode] as the extra argument.
 * Seen in play: draws 「1Pせんたくちゅう」 next to the entry screen title.
 */
void FreeBattle_DrawChoosingLabel(s8* arg0) {
    Ui_DrawTexturedFrameDecal(M2C_FIELD(arg0, s32*, 0x14) + 0x127, M2C_FIELD(arg0, s32*, 0x18) - 0x12, 0xA6, 0x14, D_800735C4);
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
void ScrollGrid_DrawItems(void*, s32, s32, s32, TableArgs*);

/**
 * Draws using the menu object arg0 (layout not established; it reads the words
 * at 0x14, 0x18 and 0x1C as position/size values): calls FreeBattle_DrawRentalTitle at
 * (+6, +0x88) with the third argument being word 0x1C minus 0xC, emits the
 * display list D_80060270 and fills a 2 by 0xB6 rectangle with color D_820090C0
 * at (+6, +0x9C). Then builds a TableArgs {D_8200AC58, 0x18, 0x10, 0} and calls
 * ScrollGrid_DrawItems on the sub-object at arg0 + 0x6E4 at (+8, +0xAC) with a mode
 * word of 0xFED, or 0xFEF when arg1 is 1, or 0xFFD when arg1 is 2.
 * What the mode word's bits mean is not yet established.
 * Seen in play: draws the 「レンタルポケモン」 window holding the L50 rental grid (フシギバナ, リザードン, カメックス, …).
 */
void FreeBattle_DrawRentalTitleWindow(s8* arg0, s32 arg1) {
    s32 sp44;
    TableArgs sp34;

    sp44 = 0xFED;
    FreeBattle_DrawRentalTitle(M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x88, M2C_FIELD(arg0, s32*, 0x1C) - 0xC);
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
    ScrollGrid_DrawItems(arg0 + 0x6E4, M2C_FIELD(arg0, s32*, 0x14) + 8, M2C_FIELD(arg0, s32*, 0x18) + 0xAC, sp44, &sp34);
}

/**
 * Draws the two textured panels behind the picked team's window (left the trainer column, right
 * the Pokemon).
 * Seen in play: runs while 「このデータでエントリーします。」 is shown over the picked team.
 * @unverified Which panel is which not checked.
 */
void FreeBattle_DrawTeamWindowPanels(s8* arg0) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x6A, 0x88, 0xE8, D_82008F5C);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 0x8E, M2C_FIELD(arg0, s32*, 0x18) + 0x6A, 0x18C, 0xE8, D_82008F58);
}

/**
 * Draws the two short textured panels of the team being built above the rental grid (the 「なまえ 1P」
 * row).
 * Seen in play: runs while the L50～55 rental grid is open.
 */
void FreeBattle_DrawRentalTeamPanels(s8* arg0) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x6A, 0x88, 0x1E, D_82008F5C);
    func_80029028(M2C_FIELD(arg0, s32*, 0x14) + 0x8E, M2C_FIELD(arg0, s32*, 0x18) + 0x6A, 0x18C, 0x1E, D_82008F58);
}

s32 func_8002AE6C(s8*);
void func_800189C0(s32, s32);
void BgStage_DrawFrame(void);
void ScrollList_DrawItems(s8*, s32, s32, s32, s32);
void FreeBattle_DrawRentalListWindow(s8*, s32);
void FreeBattle_DrawDuplicateWarning(s8*);
void FreeBattle_DrawShortageWarning(s8*);
void FreeBattle_DrawLevelSumWarning(s8*);
void FreeBattle_DrawEntryConfirm(s8*);
void FreeBattle_DrawMonStatusWindow(s8*);
void TextBox_Draw(s8*);
extern s32 D_8200AC50;
/**
 * Draws the rental selection screen for its current state (choosing label, list, entry confirm, status window).
 * Seen in play: runs every frame on 「エントリーポケモンのせんたく」 (Free Battle's team list).
 */
void FreeBattle_DrawRentalScreen(s8* arg0) {
    if (func_8002AE6C(arg0 + 0x14) != 0) {
        return;
    }
    FreeBattle_DrawChoosingLabel(arg0);
    switch (M2C_FIELD(arg0, s32*, 4)) {
        case 1:
            func_800189C0(D_8200AC50, 0);
            BgStage_DrawFrame();
            ScrollList_DrawItems(arg0 + 0x40, M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x16, 0xFFF, M2C_FIELD(arg0, s32*, 0x73C));
            break;
        case 2:
            func_800189C0(D_8200AC50, 0);
            BgStage_DrawFrame();
            FreeBattle_DrawRentalListWindow(arg0, 1);
            FreeBattle_DrawTeamWindowPanels(arg0);
            FreeBattle_DrawDuplicateWarning(arg0 + 0x320);
            break;
        case 6:
        case 8:
            func_800189C0(D_8200AC50, 0);
            BgStage_DrawFrame();
            FreeBattle_DrawRentalListWindow(arg0, (M2C_FIELD(arg0, s32*, 4) == 6) ? 1 : 2);
            FreeBattle_DrawRentalTitleWindow(arg0, (M2C_FIELD(arg0, s32*, 4) == 6) ? 0 : 1);
            FreeBattle_DrawRentalTeamPanels(arg0);
            break;
        case 10:
            func_800189C0(D_8200AC50, 0);
            BgStage_DrawFrame();
            FreeBattle_DrawRentalListWindow(arg0, 0);
            FreeBattle_DrawTeamWindowPanels(arg0);
            FreeBattle_DrawEntryConfirm(arg0 + 0x4DC);
            break;
        case 4:
            func_800189C0(D_8200AC50, 0);
            BgStage_DrawFrame();
            FreeBattle_DrawRentalListWindow(arg0, 0);
            FreeBattle_DrawTeamWindowPanels(arg0);
            FreeBattle_DrawShortageWarning(arg0 + 0x370);
            break;
        case 5:
            func_800189C0(D_8200AC50, 0);
            BgStage_DrawFrame();
            FreeBattle_DrawRentalListWindow(arg0, 0);
            FreeBattle_DrawTeamWindowPanels(arg0);
            FreeBattle_DrawLevelSumWarning(arg0 + 0x428);
            break;
        case 7:
        case 9:
            FreeBattle_DrawRentalListWindow(arg0, 2);
            FreeBattle_DrawRentalTitleWindow(arg0, (M2C_FIELD(arg0, s32*, 4) == 7) ? 0 : 2);
            FreeBattle_DrawRentalTeamPanels(arg0);
            FreeBattle_DrawMonStatusWindow(arg0 + 0x5CC);
            break;
        case 3:
            FreeBattle_DrawRentalListWindow(arg0, 2);
            FreeBattle_DrawTeamWindowPanels(arg0);
            FreeBattle_DrawMonStatusWindow(arg0 + 0x5CC);
            break;
        case 11:
            func_800189C0(D_8200AC50, 0);
            BgStage_DrawFrame();
            FreeBattle_DrawRentalListWindow(arg0, 0);
            FreeBattle_DrawTeamWindowPanels(arg0);
            break;
        case 12:
            func_800189C0(D_8200AC50, 0);
            BgStage_DrawFrame();
            ScrollList_DrawItems(arg0 + 0x40, M2C_FIELD(arg0, s32*, 0x14) + 6, M2C_FIELD(arg0, s32*, 0x18) + 0x16, 0xFFF, M2C_FIELD(arg0, s32*, 0x73C));
            TextBox_Draw(arg0 + 0x74C);
            break;
    }
}

s32 func_82003688(s32 arg0) {
    return GridMenu_UpdateCursor(arg0 + 0x2F8);
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

void FreeBattle_InitDuplicateWarning(s8*, s32, s32, s32);
void FreeBattle_InitShortageWarning(s8*, s32, s32, s32, s32);
s32 FreeBattle_CountDuplicateSpecies(void*, s32*);
s32 FreeBattle_AllTriosOverLevelLimit(Mon82000258*);

/**
 * Decides the next state of the six-slot menu. Clears `picked`, then, if `mode`
 * is non-zero, inspects the slots in this order and returns the first result
 * that applies:
 *   1. FreeBattle_CountDuplicateSpecies reports a positive count: call FreeBattle_InitDuplicateWarning on the struct at +0x320,
 *      store the reported slot index in `cur`, call FreeBattle_DisableUnpickedRows on +0x2F8,
 *      return 2.
 *   2. FreeBattle_FindFlaggedSlot finds a flagged slot: set `picked`, store its index in
 *      `cur`, then return 8 if bit 0 of unk_784 is set, otherwise call
 *      FreeBattle_InitShortageWarning on the struct at +0x370 and return 4.
 *   3. `mode` is 1 and FreeBattle_AllTriosOverLevelLimit is non-zero: return 6 if bit 1 of unk_784
 *      is set, otherwise 5.
 * Otherwise (including when `mode` is 0) returns 0xA.
 * What the individual return values mean is not established from this function.
 * Seen in play: runs when A picks a team on the entry screen.
 */
s32 FreeBattle_CheckEntryRules(SlotMenu* arg0) {
    Slot54* found;
    s32 sp38;
    s32 sp34;
    s32 ret;

    arg0->picked = 0;
    if (arg0->mode == 0) {
        ret = 0xA;
    } else {

        sp38 = FreeBattle_CountDuplicateSpecies(arg0->slots, &sp34);
        if (sp38 > 0) {
            FreeBattle_InitDuplicateWarning((s8*)arg0 + 0x320, 0x9C, 0x105, sp38);
            arg0->cur = sp34;
            FreeBattle_DisableUnpickedRows((SlotFlags*)((s8*)arg0 + 0x2F8));
            ret = 2;
        } else {
            found = FreeBattle_FindFlaggedSlot(arg0->slots, &sp38);
            if (found != NULL) {
                arg0->picked = 1;
                arg0->cur = found - arg0->slots;
                if (arg0->unk_784 & 1) {
                    ret = 8;
                } else {
                    FreeBattle_InitShortageWarning((s8*)arg0 + 0x370, 0xA6, 0x105, arg0->unk_744, sp38);
                    ret = 4;
                }
            } else if ((arg0->mode == 1) && (FreeBattle_AllTriosOverLevelLimit(arg0->slots) != 0)) {
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
 * Puts the rental Pokemon under the cursor into the team's current slot and marks the team
 * changed.
 * Seen in play: はい on 「レンタルしますか？」 adds the Pokemon (フシギバナ L50) to the 「なまえ 1P」 row.
 */
void FreeBattle_RentSelectedMon(SlotMenu* arg0) {
    arg0->unk_734 = 1;
    arg0->unk_784 |= 1;
    *(Words80*)arg0->slots[arg0->cur].unk04 = (*arg0->records)[arg0->recordIndex];
    arg0->slots[arg0->cur].flag = 0;
    arg0->unk_2FC[arg0->cur] = 0;
    D_8200AC58[(arg0->unk_48 * 6 + arg0->cur) % 24] = -1;
}

typedef struct Blk820038B0 {
    s32 w[0x85];
} Blk820038B0;
extern u8 D_82009D04[];
void FreeBattle_DrawSlotCell();

/**
 * Runs the entry Pokemon list: pick, rental, confirm and warnings.
 * Seen in play: runs while 1P picks a team on 「エントリーポケモンのせんたく」.
 */
s32 FreeBattle_UpdateEntrySelect(s8 *arg0)
{
  s32 ret = 0;
  s32 next;
  u8 *rec;
  if ((*((s32 *) (((s8 *) arg0) + 8))) != 0)
  {
    next = *((s32 *) (((s8 *) (*((s8 **) (((s8 *) arg0) + 0xC)))) + 0x28)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    if (next == 4)
    {
      if ((arg0 && arg0) && arg0) // FAKE: keeps arg0 in a0 for the state read above
      {
      }
      *((s32 *) (((s8 *) arg0) + 4)) = *((s32 *) (((s8 *) arg0) + 8)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      if ((*((s32 *) (((s8 *) arg0) + 8))) == 0xD)
      {
        ret = 1;
      }
      else
      {
        FreeBattle_EnterEntryScreenState(arg0);
        *((s32 *) (((s8 *) arg0) + 8)) = 0;
      }
      return ret;
    }
    if ((next != 1) && (next != 2))
    {
      return 0;
    }
  }
  switch (*((s32 *) (((s8 *) arg0) + 4)))
  {
    case 1:
      if (ScrollList_UpdateCursor(arg0 + 0x40) == 0)
    {
      next = func_8002BC14(*((s32 *) (((s8 *) arg0) + 0x744)));
      if (next == (-1))
      {
        func_8003F6AC(3);
        ret = -1;
      }
      else
        if (next == 1)
      {
        s32 sp40;
        rec = (*(*((u8 ****) (((s8 *) arg0) + 0xC4))))[*((s32 *) (((s8 *) arg0) + 0x48))]; // FAKE: decomp slop, raw pointer casts stand in for struct fields
        if (((*((s32 *) (((s8 *) arg0) + 0x740))) == 0) && ((FreeBattle_FindFlaggedSlot(rec + 0x1C, &sp40), sp40 == 6)))
        {
          func_8003F6AC(8);
          TextBox_Init(arg0 + 0x74C, D_82009D04, 1, 2, 9);
          FreeBattle_SetEntryScreenState(arg0, 0xC, 0);
        }
        else
        {
          func_8003F6AC(2);
          *((s32 *) (((s8 *) arg0) + 0x784)) = 0;
          if (rec[0] & 2)
          {
            FreeBattle_InitNamedTeam(arg0 + 0xC8, *((s32 *) (((s8 *) arg0) + 0x738)));
            *((s32 *) (((s8 *) arg0) + 0x784)) |= 1;
          }
          else
          {
            *((Blk820038B0 *) (arg0 + 0xC8)) = *((Blk820038B0 *) rec);
          }
          func_80027410(arg0 + 0x2DC, (s32) (arg0 + 0xE4), 0x54, 6, 6);
          GridMenu_Init(arg0 + 0x2F8, arg0 + 0x2DC, arg0 + 0x2EC, FreeBattle_DrawSlotCell, 3, 0x84, 0x32);
          *((s32 *) (((s8 *) arg0) + 0x6EC)) = 0;
          *((s32 *) (((s8 *) arg0) + 0x318)) |= 0x10000;
          FreeBattle_MarkIneligibleSlots(arg0 + 0x2F8);
          FreeBattle_SetEntryScreenState(arg0, FreeBattle_CheckEntryRules(arg0), 0);
          *((s32 *) (((s8 *) arg0) + 0x310)) = *((s32 *) (((s8 *) arg0) + 0x744)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
          func_8000B2F4(*((s32 *) (((s8 *) arg0) + 0x744)));
        }
      }
    }
      break;

    case 2:
      if (func_82003688(arg0) == 0)
    {
      next = func_8002BC14(*((s32 *) (((s8 *) arg0) + 0x744)));
      if (next == (-1))
      {
        func_8003F6AC(3);
        FreeBattle_SetEntryScreenState(arg0, 1, 1);
      }
      else
        if (next == 1)
      {
        if (((Slot54 *) (arg0 + 0xE4))[*((s32 *) (((s8 *) arg0) + 0x300))].flag & 0x40) // FAKE: decomp slop, raw pointer casts stand in for struct fields
        {
          func_8003F6AC(2);
          FreeBattle_SetEntryScreenState(arg0, 3, 0);
        }
        else
        {
          func_8003F6AC(8);
        }
      }
    }
      break;

    case 3:
      next = FreeBattle_UpdateRentalConfirmChoice(arg0 + 0x5CC);
      if (next == (-1))
    {
      FreeBattle_SetEntryScreenState(arg0, 2, 3);
    }
    else
      if (next == 1)
    {
      func_8003F6AC(2);
      FreeBattle_EnableUnpickedRows(arg0 + 0x2F8);
      func_82001708(arg0 + 0xE4, *((s32 *) (((s8 *) arg0) + 0x300)));
      func_82002528(arg0 + 0x2F8);
      FreeBattle_SetEntryScreenState(arg0, FreeBattle_CheckEntryRules(arg0), 1);
    }
      break;

    case 4:
      next = FreeBattle_UpdateShortageWarning(arg0 + 0x370);
      if (next == (-1))
    {
      FreeBattle_SetEntryScreenState(arg0, 1, 1);
    }
    else
      if (next == 1)
    {
      func_8003F6AC(2);
      FreeBattle_SetEntryScreenState(arg0, 8, 1);
    }
      break;

    case 5:
      next = FreeBattle_UpdateLevelSumWarning(arg0 + 0x428);
      if (next == (-1))
    {
      FreeBattle_SetEntryScreenState(arg0, 1, 1);
    }
    else
      if (next == 1)
    {
      if (arg0)
      {
      }
      *((s32 *) (((s8 *) arg0) + 0x784)) |= 2;
      FreeBattle_SetEntryScreenState(arg0, 6, 1);
    }
      break;

    case 6:
      if (func_82003688(arg0) == 0)
    {
      next = func_8002BC14(*((s32 *) (((s8 *) arg0) + 0x744)));
      if (next == (-1))
      {
        func_8003F6AC(3);
        if ((*((s32 *) (((s8 *) arg0) + 0x784))) & 2)
        {
          FreeBattle_SetEntryScreenState(arg0, 1, 0);
        }
        else
        {
          FreeBattle_SetEntryScreenState(arg0, 0xA, 0);
        }
      }
      else
        if (next == 1)
      {
        func_8003F6AC(2);
        if (((Slot54 *) (arg0 + 0xE4))[*((s32 *) (((s8 *) arg0) + 0x300))].flag & 1) // FAKE: decomp slop, raw pointer casts stand in for struct fields
        {
          FreeBattle_SetEntryScreenState(arg0, 8, 0);
        }
        else
        {
          FreeBattle_SetEntryScreenState(arg0, 7, 0);
        }
      }
    }
      break;

    case 8:
      if (ScrollGrid_UpdateCursor(arg0 + 0x6E4) == 0)
    {
      next = func_8002BC14(*((s32 *) (((s8 *) arg0) + 0x744)));
      if (next == (-1))
      {
        func_8003F6AC(3);
        if ((*((s32 *) (((s8 *) arg0) + 0x748))) != 0)
        {
          FreeBattle_SetEntryScreenState(arg0, 1, 0);
        }
        else
        {
          FreeBattle_SetEntryScreenState(arg0, 6, 0);
        }
      }
      else
        if (next == 1)
      {
        if (!((*((u16 **) (((s8 *) arg0) + 0x6E8)))[*((s32 *) (((s8 *) arg0) + 0x6EC))] & 1)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
        {
          func_8003F6AC(2);
          FreeBattle_SetEntryScreenState(arg0, 9, 0);
        }
        else
        {
          func_8003F6AC(8);
        }
      }
    }
      break;

    case 7:
      next = FreeBattle_UpdateRentalConfirmChoice(arg0 + 0x5CC);
      if (next == (-1))
    {
      FreeBattle_SetEntryScreenState(arg0, 6, 3);
    }
    else
      if (next == 1)
    {
      func_8003F6AC(2);
      FreeBattle_SetEntryScreenState(arg0, 8, 1);
    }
      break;

    case 9:
      next = FreeBattle_UpdateRentalConfirmChoice(arg0 + 0x5CC);
      if (next == (-1))
    {
      FreeBattle_SetEntryScreenState(arg0, 8, 3);
    }
    else
      if (next == 1)
    {
      func_8003F6AC(0x22);
      FreeBattle_RentSelectedMon(arg0);
      FreeBattle_SetEntryScreenState(arg0, FreeBattle_CheckEntryRules(arg0), 1);
    }
      break;

    case 10:
      next = FreeBattle_UpdateRentalConfirm(arg0 + 0x4DC);
      if (next == (-1))
    {
      FreeBattle_SetEntryScreenState(arg0, 1, 1);
    }
    else
      if (next == 2)
    {
      func_8003F6AC(2);
      *((s32 *) (((s8 *) arg0) + 0x300)) = 0;
      *((s32 *) (((s8 *) arg0) + 0x6EC)) = 0;
      FreeBattle_SetEntryScreenState(arg0, 6, 1);
    }
    else
      if (next == 1)
    {
      func_8003F6AC(0x20);
      FreeBattle_SetEntryScreenState(arg0, 0xB, 1);
    }
      break;

    case 11:
      ret = 1;
      break;

    case 12:
      if ((*((u16 *) (((s8 *) (*((u16 **) (((s8 *) arg0) + 0x744)))) + 8))) & 0xC000) // FAKE: decomp slop, raw pointer casts stand in for struct fields
    {
      func_8003F6AC(2);
      FreeBattle_SetEntryScreenState(arg0, 1, 1);
    }
      break;

  }

  return ret;
}

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
/**
 * Copies a picked team into a battle roster: its name (the preset or saved name), source buffer
 * and its non-empty Pokemon, then builds the display copy.
 * Seen in play: runs on 「エントリーけってい」.
 * @unverified Name from the code.
 */
void FreeBattle_CopyTeamToRoster(u8* arg0, u8* arg1, s32 arg2, Src82004020* arg3) {
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

/**
 * Zeroes one side's roster header in D_8200ACF8.
 * Seen in play: runs on 「エントリーけってい」.
 */
void FreeBattle_ClearSideRoster(s8 *arg0) {
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
void Session_LoadPortSnapshot(u8);

/**
 * Builds the battle rosters in D_8200ACF8 for each side's picked teams
 * (FreeBattle_CopyTeamToRoster), clears both side headers first and, in modes 1 and 2, loads the
 * picked port's session snapshot.
 * Seen in play: runs on 「エントリーけってい」.
 * @unverified Layout from the code.
 */
void FreeBattle_BuildBattleRosters(s32* arg0, s32* arg1, Src82004020** arg2, s32 arg3, s32 arg4, s32 arg5) {
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
            Session_LoadPortSnapshot(M2C_FIELD(D_8200ACF8, u8*, 0x1094));
        }
    }
    M2C_FIELD(D_8200ACF8, u32*, 0x108C) = -1;
    M2C_FIELD(D_8200ACF8, u32*, 0x1090) = -1;
    FreeBattle_ClearSideRoster(D_8200ACF8 + 0x1034);
    FreeBattle_ClearSideRoster(D_8200ACF8 + 0x105C);
    D_8200ACF8[4] = 0;
    D_8200ACF8[0x208] = 0;
    D_8200ACF8[0x40C] = 0;
    D_8200ACF8[0x610] = 0;
    if (arg0[0] > 0) {
        FreeBattle_CopyTeamToRoster(D_8200ACF8 + 4, D_8200ACF8 + 0x814, arg0[0], arg2[arg0[0] - 1]);
        M2C_FIELD(D_8200ACF8, s8**, 0x103C + M2C_FIELD(D_8200ACF8, u8*, 0x1035) * 4) = D_8200ACF8 + 4;
        M2C_FIELD(D_8200ACF8, u8*, 0x1035)++;
    }
    if (arg0[1] > 0) {
        FreeBattle_CopyTeamToRoster(D_8200ACF8 + 0x208, D_8200ACF8 + 0xA1C, arg0[1], arg2[arg0[1] - 1]);
        M2C_FIELD(D_8200ACF8, s8**, 0x103C + M2C_FIELD(D_8200ACF8, u8*, 0x1035) * 4) = D_8200ACF8 + 0x208;
        M2C_FIELD(D_8200ACF8, u8*, 0x1035)++;
    }
    if (arg1[0] > 0) {
        FreeBattle_CopyTeamToRoster(D_8200ACF8 + 0x40C, D_8200ACF8 + 0xC24, arg1[0], arg2[arg1[0] - 1]);
        M2C_FIELD(D_8200ACF8, s8**, 0x1064 + M2C_FIELD(D_8200ACF8, u8*, 0x105D) * 4) = D_8200ACF8 + 0x40C;
        M2C_FIELD(D_8200ACF8, u8*, 0x105D)++;
    }
    if (arg1[1] > 0) {
        FreeBattle_CopyTeamToRoster(D_8200ACF8 + 0x610, D_8200ACF8 + 0xE2C, arg1[1], arg2[arg1[1] - 1]);
        M2C_FIELD(D_8200ACF8, s8**, 0x1064 + M2C_FIELD(D_8200ACF8, u8*, 0x105D) * 4) = D_8200ACF8 + 0x610;
        M2C_FIELD(D_8200ACF8, u8*, 0x105D)++;
    }
}

void FreeBattle_BuildBattleRosters(s32*, s32*, Src82004020**, s32, s32, s32);

/**
 * Commits both sides' picked teams to the battle (FreeBattle_BuildBattleRosters with the entry
 * screen's state).
 * Seen in play: runs when はい confirms the COM's team and 「エントリーけってい」 appears.
 */
void FreeBattle_CommitEntries(s8 *arg0) {
    FreeBattle_BuildBattleRosters((s32*)(arg0 + 0x4358), (s32*)(arg0 + 0x4360), (Src82004020**)(arg0 + 0x4340), M2C_FIELD(arg0, s32 *, 0x4370), M2C_FIELD(arg0, s32 *, 0x4374), M2C_FIELD(arg0, s32 *, 0x501C));
}
