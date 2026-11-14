/* Object boundary at 0x82005D90 (16-byte text alignment). */
/* Stadium Zero fragment007_166580. */

#include "global.h"
#include "m2c_macros.h"

#include "free_battle_setup.h"
s32 func_80020AFC(s32, s32, s32, s32);
s32 func_80020CE4(void*, s32, s32);
void func_80020C60(s32);
void func_800207F8(u8*);
extern u8 D_80065D00[];

s32 FreeBattle_ReadTeam(s32 arg0, s32 arg1, s32 arg2, Entry82000058* entry);

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 Pokemon_GetTypeIndex(s32, s32);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001ABBC(void);
void Font_SetLineHeight(s32 arg0);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A944(s32, s32, const char*, ...);

typedef struct Entry8006A9D4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry8006A9D4; // size = 0xC
extern Entry8006A9D4 D_8006A9D4[];
extern u8 D_800734A8[];
extern char D_82009B90[];
u32 func_800566BC(const char*);

void FreeBattle_DrawMoveName(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void FreeBattle_DrawTypeName(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_8002B390(s32);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);

s32 FreeBattle_UpdateRentalConfirmChoice(s8* arg0);

typedef struct Color82001CCC {
    u8 c[4];
} Color82001CCC;
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color82001CCC);
void FreeBattle_DrawRowBorders(s32 arg0, s32 arg1, Color82001CCC arg2);

M2C_UNK FreeBattle_EnterEntryScreenState();                            /* extern */

void FreeBattle_SetEntryScreenState(s8 *arg0, s32 arg1, s32 arg2);

extern Color82001CCC D_82008F5C;
extern Color82001CCC D_82008F58;
void FreeBattle_DrawTeamWindowPanels(s8* arg0);

void FreeBattle_DrawRentalTeamPanels(s8* arg0);

M2C_UNK GridMenu_UpdateCursor();                            /* extern */
extern char D_800735C4[];

void func_82003688(s32 arg0);

void FreeBattle_ClearSideRoster(s8 *arg0);

M2C_UNK FreeBattle_BuildBattleRosters(s8 *, s8 *, s8 *, s32, s32, s32); /* extern */

void FreeBattle_CommitEntries(s8 *arg0);

extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;
s32 func_80025BD8(void);
void func_80027FF8(void*, s32);
s32 func_80002D98(s32);
void FreeBattle_InitBattleModeScreen(s32);
void func_8200573C(void);

void Cont_StartReadInputs(void);                            /* extern */
void Cont_ReadInputs(void);                            /* extern */
M2C_UNK FreeBattle_DrawScreen(s32);                         /* extern */
M2C_UNK FreeBattle_UpdateScreen(s32);                         /* extern */
extern s32 D_8200AD28;

void FreeBattle_RunFrame(s32 arg0);

M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK FreeBattle_DrawScreen(s32);                         /* extern */
extern M2C_UNK D_82009E18;
extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;

s32 FreeBattle_DrawScreenWithSummary(s32 arg0);

M2C_UNK func_80002DC0(s32);                         /* extern */
extern s32 D_8200AD28;

void func_82005958(void);

extern s32 D_8200AD08[8];
extern s32 D_8200AC40;
extern s32 D_820090DC[8];
s32 func_800044AC(s32, s32);

void func_8200597C(void);

s32 Font_Init(s32 load_size, s32 side);
s8 *PokeIcon_AllocFramebuffers(s32 arg0);
u16* func_80018F2C(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80017FDC(s32, s32, s32, s32);
s32 func_80004154(u8*, u8*, s32, s32);
void PokeIcon_OpenModelArchives(void);
void func_800040B4(s32, u8*, u8*);
void func_80003EB8(s32, u8*, u8*, s32);
s32 func_80001B10(u8*);
void FreeBattle_RestoreMenuState(s32);
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
M2C_UNK func_820059EC(void);

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
s32 func_82005CCC(s32 arg0, M2C_UNK arg1);

extern Color_RGBA8 D_82009100;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void Window_DrawLabeled(s8*, s32);
extern u8 D_8007356C;
void Font_SetColorForFlags(s32);

/**
 * Draws one menu row label with the selection highlight.
 * Seen in play: draws each row of the 「たいせんルールせんたく」 list.
 */
void FreeBattle_DrawMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 temp_v0 = *arg5;

    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x1A, D_82009100);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

/*
 * FreeBattle_InitMenuWindow
 *
 * Sets the window rect, style 0x801 and title arg9, points the item list at the arg6 strings
 * in arg5, sets up the menu (FreeBattle_DrawMenuRow rows of width arg3 - 0xC, 32 pixels
 * apart) and stores the description table arg7 and its line count arg8.
 *
 * Same shape as FreeBattle_InitBattleModeWindow. As there, &arg0->itemList is written out
 * twice rather than cached in a local, which moves the compiler's stack spill and changes
 * the frame size.
 */
void Window_SetRect(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK func_80027804(void*, s32, s32, s32);         /* extern */
M2C_UNK Menu_Init(void*, void*, void*, void (*)(s32, s32, char *, s32, s32, s32 *), s32, s32); /* extern */
/**
 * Sets up a titled menu window with item and description tables.
 * Seen in play: A on フリーバトル opens 「たいせんルールせんたく」 (フリーバトル, L 1～30 バトル, L50～55 バトル) and runs this.
 */
void FreeBattle_InitMenuWindow(MenuWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, char** arg7, s32 arg8, char* arg9) {
    Window_SetRect(&arg0->window, arg1, arg2, arg3, arg4);
    arg0->window.state = 0;
    arg0->window.animTimer = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = arg9;
    func_80027804(&arg0->itemList, arg5, arg6, arg6);
    Menu_Init(&arg0->menu, &arg0->itemList, arg0->itemFlags, FreeBattle_DrawMenuRow, arg3 - 0xC, 0x20);
    arg0->menu.options = (s32) (arg0->menu.options | 0x10000);
    arg0->descriptions = arg7;
    arg0->descriptionLines = arg8;
}

s32 func_8002AE6C();
void Menu_DrawItems(void*, s32, s32, s32, s8 *);
extern Color_RGBA8 D_82009104;
extern Color_RGBA8 D_82009108;

/**
 * Draws the window while func_8002AE6C() is zero: the list panel (rows * 32 + 8 high), the
 * description box (descriptionLines * 0x1C high), the menu rows via Menu_DrawItems (flags
 * arg1 | 0xFFED, row width passed by pointer in sp38) and descriptions[menu.cursor] in the
 * color from D_800734A8.
 * What the constants mean is not established. `pad` places sp38 at sp+0x38 as in the ROM.
 * Seen in play: draws the 「たいせんルールせんたく」 list window with its description box.
 */
void FreeBattle_DrawMenuWindow(MenuWindow* arg0, s32 arg1) {
    s32 pad; // FAKE: stack padding
    s32 sp38;
    s32 temp_s1;

    if (func_8002AE6C() == 0) {
        temp_s1 = (arg0->menu.items->count << 5) + 8;
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + temp_s1 + 5, arg0->window.frame.width, &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, temp_s1, *(Color82001CCC*)&D_82009100);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + temp_s1 + 0xC, arg0->window.frame.width - 0xC, arg0->descriptionLines * 0x1C, D_82009104, D_82009108);
        sp38 = arg0->window.frame.width - 0xC;
        Menu_DrawItems(&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 0xA, arg1 | 0xFFED, (s8*)&sp38);
        func_8001AB6C();
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        func_8001A384(8, 0);
        Font_SetLineHeight(0x1C);
        func_8001A944(arg0->window.frame.x + 0xE, arg0->window.frame.y + temp_s1 + 0x10, arg0->descriptions[arg0->menu.cursor]);
        func_8001ABBC();
    }
}

extern s32 D_800603C0;

/**
 * FreeBattle_UpdateMenuWindow
 *
 * Returns 0 immediately unless the word at arg0 + 0x28 is 1 or 2. Otherwise,
 * if Menu_UpdateCursor(arg0 + 0x2C, arg0) returns 0, it reads func_8002BC14(D_800603C0):
 * -1 calls func_8003F6AC(3) and returns -1; 1 calls func_8003F6AC(2) and
 * returns the word at arg0 + 0x34 plus 1; any other value returns 0.
 * (FreeBattle_UpdatePopupMenu is the same pattern without the mode check.)
 * Seen in play: runs while the 「たいせんルールせんたく」 list is open.
 */
s32 FreeBattle_UpdateMenuWindow(MenuWindow* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = arg0->window.state;
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (Menu_UpdateCursor(&arg0->menu, arg0) == 0) {
        tmp = func_8002BC14(D_800603C0);
        if (tmp == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (tmp == 1) {
            func_8003F6AC(2);
            result = arg0->menu.cursor + 1;
        }
    }
    return result;
}

/**
 * Draws one popup menu row with the selection highlight.
 * Seen in play: draws each numbered row of the ルールをみる rules list.
 */
void FreeBattle_DrawPopupRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, MenuWindow* arg5) {
    if (arg4 & 0x18) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, arg5->window.frame.width - 0x12, 0x1E, arg5->window.frame.color);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, arg1 + 6, arg2);
    Font_EndTexturedTextRendering();
}

typedef struct List820061F0 {
    /* 0x00 */ char **items;
    /* 0x04 */ s8 count;
    /* 0x08 */ s32 unk8;
} List820061F0;
/**
 * Sets up a popup menu sized to its widest string.
 * Seen in play: ルールをみる opens the rules list (「1) 6ぴきの ポケモンを エントリー」 … 「5) エントリーできるポケモン 33しゅるい」) as
 * this popup.
 */
void FreeBattle_InitPopupMenu(MenuWindow* arg0, s32 arg1, s32 arg2, List820061F0 *arg3, s8 *arg4, Color_RGBA8 arg5) {
    s32 i;
    s32 w;
    s32 max = 0;
    s32 h;

    for (i = 0; i < arg3->count; i++) {
        w = func_800566BC(arg3->items[i]) >> 1;
        if (max < w) {
            max = w;
        }
    }
    func_80027804(&arg0->itemList, (s32)arg3->items, arg3->count, arg3->count);
    h = max * 0x18 + 0x18;
    Menu_Init(&arg0->menu, &arg0->itemList, arg4, (void (*)(s32, s32, char *, s32, s32, s32 *))FreeBattle_DrawPopupRow, h, 0x24);
    arg0->menu.options |= 0x10000;
    Window_SetRect(&arg0->window, arg1, arg2, h + 0xC, arg3->count * 0x24 + 0x18);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x800;
    arg0->window.title = arg3->unk8;
    arg0->window.frame.color = arg5;
}

s32 func_8002AE6C();                                /* extern */
void Menu_DrawItems(void*, s32, s32, s32, s8 *);  /* extern */
// FAKE: permuter output (the new_var temp and the no-op test).
/**
 * Draws a popup menu's items.
 * Seen in play: draws the ルールをみる rules list window.
 */
void FreeBattle_DrawPopupMenu(MenuWindow* arg0, s32 arg1)
{
  Menu *new_var; // FAKE: permuter temp
  if (func_8002AE6C() == 0)
  {
    if (arg0 && arg0)
    {
    }
    Menu_DrawItems(new_var = &arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 0xC, arg1 | 0xFFED, (s8*)arg0);
  }
}

s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;
/**
 * Moves a popup menu's cursor. Returns -1 on cancel, the 1-based row on confirm.
 * Seen in play: runs while the rules list is open; D-Down moves the highlight down the rules.
 */
s32 FreeBattle_UpdatePopupMenu(MenuWindow* arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (Menu_UpdateCursor(&arg0->menu) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = arg0->menu.cursor + 1;
        }
    }
    return sp1C;
}

extern u8 D_800734A8[];
/**
 * Draws one opponent choice in 「あいてをせんたく」 (2P, 3P, 4P, COM): highlight box when selected (flag
 * 0x10), dimmed when unavailable (flag 1).
 * Seen in play: with one controller, 2P to 4P were dimmed and COM was boxed.
 */
void FreeBattle_DrawOpponentOption(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    Color_RGBA8 c;

    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0x46, 0x16, D_82009100);
    }
    Font_BeginTranslucentTextRendering();
    c = ((Color_RGBA8*)&D_800734A8)[(arg4 & 2) ? 0 : 1];
    if (arg4 & 1) {
        c.a = 0x4C;
    }
    Gfx_SetEnvColor(c.r, c.g, c.b, c.a);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

typedef struct Offset82006508 {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
} Offset82006508;

extern u8 D_8200911C[];
extern u8 D_8200912C[];
extern u8 D_8200913C[];
extern Color_RGBA8 D_8200914C;
extern Color_RGBA8 D_82009150;
extern Color_RGBA8 D_82009154;
extern Color_RGBA8 D_82009158;
extern Offset82006508 D_8200915C[];
void Ui_DrawImageInStrips(void*, s32, s32);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

/**
 * Draws the four controller ports, marking the connected and active ones.
 * Seen in play: draws the controller pictures in 「あいてをせんたく」.
 */
void FreeBattle_DrawControllerPanel(s32 x, s32 y, s32 present, s32 active, s32 markA, s32 markB) {
    s32 i;

    Ui_FillRectPrimEnvColor(x, y, 0x186, 0x8D, D_8200914C, D_82009150);
    Ui_DrawImageInStrips(D_8200911C, x + 0x88, y + 5);
    for (i = 0; i != 4; i++) {
        if ((present >> i) & 1) {
            if ((active >> i) & 1) {
                Ui_DrawImageInStrips(D_8200912C, D_8200915C[i].x + x, D_8200915C[i].y + y);
            } else {
                Ui_DrawImageInStrips(D_8200913C, D_8200915C[i].x + x, D_8200915C[i].y + y + 0xC);
            }
        }
        if ((markA >> i) & 1) {
            Ui_DrawRoundedFrame(D_8200915C[i].x + x, D_8200915C[i].y + y, 0x3A, 0x43, D_82009154);
        }
        if ((markB >> i) & 1) {
            Ui_DrawRoundedFrame(D_8200915C[i].x + x, D_8200915C[i].y + y, 0x3A, 0x43, D_82009158);
        }
    }
}

void FreeBattle_DrawOpponentOption(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4);
void Window_SetRect(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK Menu_SkipDisabledForward(s8 *, s32);                   /* extern */
extern M2C_UNK D_8200917C;
extern M2C_UNK D_82009F70;

/**
 * FreeBattle_InitOpponentSelect
 *
 * Initializes the FreeBattleOpponentWindow arg0: calls
 * Window_SetRect(&arg0->window, arg1, arg2, 0x192, 0x10F), style 0x801, title D_82009F70; the
 * four options D_8200917C go into itemList and the menu (FreeBattle_DrawOpponentOption rows).
 * controllerMask = arg3. With mask = ~arg3 (OR 0xE when arg4 == 1), each of the bits 2, 4 and 8
 * set in mask disables option 0, 1 or 2. Stores arg5 at unk_70 and moves the cursor to an
 * enabled option (Menu_SkipDisabledForward).
 *
 * Same family as FreeBattle_InitBattleModeWindow and FreeBattle_InitMenuWindow. What the object, the bits
 * and the values mean is not established. Matching notes: the sub-object
 * addresses are held in the locals sp2C and sp28 (the ROM spills them), and
 * the unused leading `pad` local places those spill slots at sp+0x2C and
 * sp+0x28.
 * Seen in play: たいせんする opens 「あいてをせんたく」 (1P VS, 2P 3P 4P COM) and runs this.
 */
void FreeBattle_InitOpponentSelect(FreeBattleOpponentWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad; // FAKE: stack padding
    s8 *sp2C;
    s8 *sp28;
    s32 var_v1;

    Window_SetRect(&arg0->window, arg1, arg2, 0x192, 0x10F);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = (char*)&D_82009F70;
    sp2C = (s8*)&arg0->itemList;
    func_80027804(sp2C, (s32)&D_8200917C, 4, 4);
    sp28 = (s8*)&arg0->menu;
    Menu_Init(sp28, sp2C, arg0->itemFlags, (void (*)(s32, s32, char *, s32, s32, s32 *))FreeBattle_DrawOpponentOption, 0x4C, 0x1C);
    arg0->menu.options = (s32) (arg0->menu.options | 0x10000);
    arg0->controllerMask = arg3;
    var_v1 = ~arg3;
    if (arg4 == 1) {
        var_v1 |= 0xE;
    }
    if (var_v1 & 2) {
        arg0->menu.itemFlags[0] |= 1;
    }
    if (var_v1 & 4) {
        arg0->menu.itemFlags[1] |= 1;
    }
    if (var_v1 & 8) {
        arg0->menu.itemFlags[2] |= 1;
    }
    arg0->unk_70 = arg5;
    Menu_SkipDisabledForward(sp28, arg3);
}

void Ui_DrawImageInStrips(void*, s32, s32);
void FreeBattle_DrawControllerPanel(s32, s32, s32, s32, s32, s32);
extern u8 D_8200910C[];
extern char D_82009F84[];

/**
 * Draws the window while func_8002AE6C() is zero: a frame via Ui_DrawTexturedDivider (at y + 0x92),
 * a filled bar via func_80029028 (color D_82009100, height 0x70), the picture D_8200910C via
 * Ui_DrawImageInStrips, the text D_82009F84 in the color from D_800734A8, the menu via
 * Menu_DrawItems, and finally FreeBattle_DrawControllerPanel with controllerMask, unk_70, 1 and a
 * value chosen from menu.cursor (0 -> 2, 1 -> 4, 2 -> 8, otherwise 0).
 * What the constants mean is not established.
 * Matching note: Ui_DrawTexturedDivider and Menu_DrawItems must be declared void; their
 * (unused) return value would otherwise shift the compiler's register choices.
 * Seen in play: draws 「あいてをせんたく」 with the N64 and controller pictures and 1P VS COM.
 */
void FreeBattle_DrawOpponentSelect(FreeBattleOpponentWindow* arg0) {
    s32 sp2C;

    sp2C = 0;
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x92, arg0->window.frame.width, &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x99, arg0->window.frame.width - 0xC, 0x70, *(Color82001CCC*)&D_82009100);
        Ui_DrawImageInStrips(D_8200910C, arg0->window.frame.x + 0xA9, arg0->window.frame.y + 0xC1);
        func_8001AB6C();
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        func_8001A384(8, 0);
        func_8001A944(arg0->window.frame.x + 0x36, arg0->window.frame.y + 0xC3, D_82009F84);
        func_8001ABBC();
        Menu_DrawItems(&arg0->menu, arg0->window.frame.x + 0x110, arg0->window.frame.y + 0x99, 0xFEF, 0);
        switch (arg0->menu.cursor) {
            case 0:
                sp2C = 2;
                break;
            case 1:
                sp2C = 4;
                break;
            case 2:
                sp2C = 8;
                break;
        }
        FreeBattle_DrawControllerPanel(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->controllerMask, arg0->unk_70, 1, sp2C);
    }
}

/**
 * Variant of FreeBattle_UpdateBattleModeWindow whose sub-object is at arg0 + 0x38. Returns 0
 * immediately unless the word at arg0 + 0x28 is 1 or 2. Otherwise, if
 * Menu_UpdateCursorSkipDisabled(arg0 + 0x38, arg0) returns 0, it reads
 * func_8002BC14(D_800603C0): -1 calls func_8003F6AC(3) and returns -1; 1 calls
 * func_8003F6AC(2), returns 1 and maps the word at arg0 + 0x40 (0..3) to the
 * value 2..5 stored in the word at arg0 + 0x64. Any other value returns 0.
 * Seen in play: runs while 「あいてをせんたく」 is open.
 */
s32 FreeBattle_UpdateOpponentSelect(FreeBattleOpponentWindow* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = arg0->window.state;
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (Menu_UpdateCursorSkipDisabled(&arg0->menu, arg0) == 0) {
        tmp = func_8002BC14(D_800603C0);
        if (tmp == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (tmp == 1) {
            func_8003F6AC(2);
            result = 1;
            switch (arg0->menu.cursor) {
                case 0:
                    arg0->choice = 2;
                    break;
                case 1:
                    arg0->choice = 3;
                    break;
                case 2:
                    arg0->choice = 4;
                    break;
                case 3:
                    arg0->choice = 5;
                    break;
            }
        }
    }
    return result;
}

void func_82006AC0(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    Color_RGBA8 c;

    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0x6E, 0x16, D_82009100);
    }
    Font_BeginTranslucentTextRendering();
    c = ((Color_RGBA8*)&D_800734A8)[(arg4 & 2) ? 0 : 1];
    if (arg4 & 1) {
        c.a = 0x4C;
    }
    Gfx_SetEnvColor(c.r, c.g, c.b, c.a);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}


/*
 * func_82006BB8
 *
 * Reads the word at arg0 + 0xBC, inverts it, and for each of bits 1, 2 and 3
 * of the inverted value (masks 2, 4 and 8) sets bit 0 in three of the six
 * halfwords of the array that arg0 + 0x70 points to:
 *   bit 1 -> halfwords 0, 3, 4
 *   bit 2 -> halfwords 1, 3, 5
 *   bit 3 -> halfwords 2, 4, 5
 * What the flags word and the halfwords mean is not established here; the
 * bank pointer is re-read from arg0 for every update because the compiler is
 * not told the stores cannot change it.
 */
void func_82006BB8(FreeBattleTeamOpponentWindow* arg0) {
    s32 inv;

    inv = ~arg0->controllerMask;
    if (inv & 2) {
        arg0->opponentMenu.itemFlags[0] |= 1;
        arg0->opponentMenu.itemFlags[3] |= 1;
        arg0->opponentMenu.itemFlags[4] |= 1;
    }
    if (inv & 4) {
        arg0->opponentMenu.itemFlags[1] |= 1;
        arg0->opponentMenu.itemFlags[3] |= 1;
        arg0->opponentMenu.itemFlags[5] |= 1;
    }
    if (inv & 8) {
        arg0->opponentMenu.itemFlags[2] |= 1;
        arg0->opponentMenu.itemFlags[4] |= 1;
        arg0->opponentMenu.itemFlags[5] |= 1;
    }
}

extern M2C_UNK D_82009190;
extern M2C_UNK D_820091A0;
extern M2C_UNK D_82009FCC;

/*
 * func_82006C74
 *
 * Initializes the object arg0 (layout not established): the same shape as
 * FreeBattle_InitOpponentSelect, but the embedded window starts at arg0 + 4 (Window_SetRect with
 * 0x192 x 0x163), the words at 0x28 and 0x2C are cleared, the word at 0x18 is set to
 * 0x801 and the pointer at 0x24 to &D_82009FCC. Calls func_80027804 on the
 * sub-objects at arg0 + 0x30 (&D_82009190, 4, 4) and arg0 + 0x3C (&D_820091A0, 7, 7),
 * and Menu_Init on (0x48, 0x30, 0x90) and (0x6C, 0x3C, 0x98), both with the
 * callback func_82006AC0, 0x74 and 0x1C; sets bit 0x10000 in the words at 0x68 and
 * 0x8C and stores arg3 at 0xBC.
 *
 * Then, with mask = ~arg3 (OR 0xE when arg4 == 2): for each of the bits 2, 4 and 8 that
 * is set in mask, sets bit 0 of the halfword at offset 2, 4 or 6 of the record
 * pointed to by the word at arg0 + 0x4C. Finally calls func_82006BB8(arg0), stores
 * 1 at offset 0 and arg5 at 0xC4.
 *
 * What the object, the bits and the values mean is not established. Matching
 * notes: the sub-object addresses are held in the locals sp2C and sp28 (the ROM
 * spills them), the unused leading `pad` places the spill slots, and arg5 is stored
 * before the constant 1 so that its load comes first.
 */
void func_82006C74(FreeBattleTeamOpponentWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad; // FAKE: stack padding
    void *sp2C;
    void *sp28;
    s32 var_v1;

    Window_SetRect(&arg0->window, arg1, arg2, 0x192, 0x163);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = &D_82009FCC;
    sp2C = &arg0->sideItemList;
    func_80027804(sp2C, (s32)&D_82009190, 4, 4);
    sp28 = &arg0->sideMenu;
    Menu_Init(sp28, sp2C, &arg0->sideItemFlags, (void (*)(s32, s32, char *, s32, s32, s32 *))func_82006AC0, 0x74, 0x1C);
    sp2C = &arg0->opponentItemList;
    arg0->sideMenu.options = (s32) (arg0->sideMenu.options | 0x10000);
    func_80027804(sp2C, (s32)&D_820091A0, 7, 7);
    Menu_Init(&arg0->opponentMenu, sp2C, &arg0->opponentItemFlags, (void (*)(s32, s32, char *, s32, s32, s32 *))func_82006AC0, 0x74, 0x1C);
    arg0->opponentMenu.options = (s32) (arg0->opponentMenu.options | 0x10000);
    arg0->controllerMask = arg3;
    var_v1 = ~arg3;
    if (arg4 == 2) {
        var_v1 |= 0xE;
    }
    if (var_v1 & 2) {
        arg0->sideMenu.itemFlags[1] |= 1;
    }
    if (var_v1 & 4) {
        arg0->sideMenu.itemFlags[2] |= 1;
    }
    if (var_v1 & 8) {
        arg0->sideMenu.itemFlags[3] |= 1;
    }
    func_82006BB8(arg0);
    arg0->unk_C4 = arg5;
    arg0->focus = 1;
}


void func_82006DF8(FreeBattleTeamOpponentWindow* arg0) {
    s32 maskB = 0xFED, maskA = 0xFED;
    s32 pad[1]; // FAKE: stack padding
    s32 markA = 0;
    s32 markB = 0;

    if (func_8002AE6C(&arg0->window) == 0) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x92, arg0->window.frame.width, &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x99, arg0->window.frame.width - 0xC, 0xC4, *(Color82001CCC*)&D_82009100);
        Ui_DrawImageInStrips(D_8200910C, arg0->window.frame.x + 0xA9, arg0->window.frame.y + 0xF9);
        if (arg0->focus != 0) {
            if (arg0->focus == 1) {
                maskB = 0xFEF;
            }
        } else {
            maskB = 0xFFD;
            maskA = 0xFEF;
        }
        Menu_DrawItems(&arg0->sideMenu, arg0->window.frame.x + 0x22, arg0->window.frame.y + 0xD1, maskB, NULL);
        Menu_DrawItems(&arg0->opponentMenu, arg0->window.frame.x + 0xFC, arg0->window.frame.y + 0x99, maskA, NULL);
        switch ((u32)arg0->sideMenu.cursor) {
            case 0:
                markA = 1;
                break;
            case 1:
                markA = 3;
                break;
            case 2:
                markA = 5;
                break;
            case 3:
                markA = 9;
                break;
        }
        if (arg0->focus == 0) {
            switch ((u32)arg0->opponentMenu.cursor) {
                case 0:
                    markB = 2;
                    break;
                case 1:
                    markB = 4;
                    break;
                case 2:
                    markB = 8;
                    break;
                case 3:
                    markB = 6;
                    break;
                case 4:
                    markB = 0xA;
                    break;
                case 5:
                    markB = 0xC;
                    break;
            }
        }
        FreeBattle_DrawControllerPanel(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->controllerMask, arg0->unk_C4, markA, markB);
    }
}

void Menu_ClearItemFlags(u8*, void*);
// The seven result cases were one macro in the original: IDO only schedules
// these three stores the way the ROM does when they share a source line.
#define SET_PAIR_82007030(owner, first, second, count) \
    (owner)->players[2] = (first); (owner)->players[3] = (second); (owner)->playerCount += (count)

s32 func_82007030(FreeBattleTeamOpponentWindow* arg0) {
    s32 result = 0;
    u32 res;

    if (((u32)arg0->window.state != 1) && ((u32)arg0->window.state != 2)) { // the ROM compares these unsigned
        return 0;
    }
    switch (arg0->focus) {
        case 1:
            if (Menu_UpdateCursorSkipDisabled((u8*)&arg0->sideMenu, arg0) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    result = -1;
                } else if (res == 1) {
                    func_8003F6AC(2);
                    arg0->focus = 0;
                    switch ((u32)arg0->sideMenu.cursor) {
                        case 0:
                            arg0->players[0] = 1;
                            arg0->players[1] = 0;
                            arg0->playerCount = 1;
                            break;
                        case 1:
                            arg0->players[0] = 1;
                            arg0->players[1] = 2;
                            arg0->playerCount = 2;
                            arg0->opponentMenu.itemFlags[0] |= 1;
                            arg0->opponentMenu.itemFlags[3] |= 1;
                            arg0->opponentMenu.itemFlags[4] |= 1;
                            arg0->opponentMenu.itemFlags[6] |= 1;
                            break;
                        case 2:
                            arg0->players[0] = 1;
                            arg0->players[1] = 3;
                            arg0->playerCount = 2;
                            arg0->opponentMenu.itemFlags[1] |= 1;
                            arg0->opponentMenu.itemFlags[3] |= 1;
                            arg0->opponentMenu.itemFlags[5] |= 1;
                            arg0->opponentMenu.itemFlags[6] |= 1;
                            break;
                        case 3:
                            arg0->players[0] = 1;
                            arg0->players[1] = 4;
                            arg0->playerCount = 2;
                            arg0->opponentMenu.itemFlags[2] |= 1;
                            arg0->opponentMenu.itemFlags[4] |= 1;
                            arg0->opponentMenu.itemFlags[5] |= 1;
                            arg0->opponentMenu.itemFlags[6] |= 1;
                            break;
                    }
                    arg0->opponentMenu.cursor = 0;
                    Menu_SkipDisabledForward((s8*)&arg0->opponentMenu, (s32)arg0);
                }
            }
            break;
        case 0:
        if (Menu_UpdateCursorSkipDisabled((u8*)&arg0->opponentMenu, arg0) == 0) {
            res = func_8002BC14(D_800603C0);
            if (res == -1) {
                func_8003F6AC(3);
                arg0->focus = 1;
                Menu_ClearItemFlags((u8*)&arg0->opponentMenu, arg0);
                func_82006BB8(arg0);
            } else if (res == 1) {
                func_8003F6AC(2);
                switch ((u32)arg0->opponentMenu.cursor) {
                    case 0:
                        SET_PAIR_82007030(arg0, 2, 0, 1);
                        break;
                    case 1:
                        SET_PAIR_82007030(arg0, 3, 0, 1);
                        break;
                    case 2:
                        SET_PAIR_82007030(arg0, 4, 0, 1);
                        break;
                    case 3:
                        SET_PAIR_82007030(arg0, 2, 3, 2);
                        break;
                    case 4:
                        SET_PAIR_82007030(arg0, 2, 4, 2);
                        break;
                    case 5:
                        SET_PAIR_82007030(arg0, 3, 4, 2);
                        break;
                    case 6:
                        SET_PAIR_82007030(arg0, 5, 0, 1);
                        break;
                }
                result = 1;
            }
        }
            break;
    }
    return result;
}

typedef struct Box82007398 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} Box82007398;

/**
 * Draws one card of the 「バトルモード」 window: the stadium picture and its label (フリーバトル or トーナメント),
 * with a highlight box when flag 0x10 marks it selected.
 * Seen in play: runs every frame on that window; the yellow box follows D-Left/D-Right.
 */
void FreeBattle_DrawBattleModeCard(s32 arg0, s32 arg1, s32* arg2, s32 arg3, s32 arg4) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    Box82007398 sp24;

    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xB2, 0xC2, D_82009100);
    }
    sp24.unk_08 = sp24.unk_04 = sp24.unk_00 = 0x98;
    sp24.unk_0C = arg2[2];
    Ui_DrawImageInStrips((void*)&sp24, arg0 + 0x10, arg1 + 8);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0x16, arg1 + 0xAA, (char*)arg2[0]);
    Font_EndTexturedTextRendering();
}

/*
 * FreeBattle_InitBattleModeWindow
 *
 * Initializes the FreeBattleModeWindow arg0: calls
 * Window_SetRect(arg0, arg1, arg2, 0x190, 0x12E), clears the words at 0x24
 * and 0x28, sets the word at 0x14 to 0x801 and the word at 0x20 to arg4.
 * Calls func_80027410 on the sub-object at arg0 + 0x54 with (arg3, 0xC, 2, 2),
 * then GridMenu_Init on the sub-objects at 0x2C, 0x54 and 0x64 with
 * FreeBattle_DrawBattleModeCard as a callback and the values 2, 0xB8 and 0xC8. Finally sets
 * bit 0x10000 in the word at 0x4C and stores arg3 at 0x68.
 *
 * What the object is and what the constants mean is not established. The
 * address arg0 + 0x54 is written out twice instead of being kept in a local:
 * a local moves the compiler's spill of it from sp+0x34 to sp+0x30.
 */
void Window_SetRect(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK func_80027410(s8 *, s32, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK GridMenu_Init(s8 *, s8 *, s8 *, M2C_UNK *, s32, s32, s32); /* extern */

/**
 * Sets up the バトルモード (battle mode) window.
 * Seen in play: runs when B backs out of the rule list to the バトルモード window.
 */
void FreeBattle_InitBattleModeWindow(FreeBattleModeWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Window_SetRect(arg0, arg1, arg2, 0x190, 0x12E);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = arg4;
    func_80027410(&arg0->items, arg3, 0xC, 2, 2);
    GridMenu_Init(&arg0->menu, &arg0->items, &arg0->itemFlags, (M2C_UNK*)FreeBattle_DrawBattleModeCard, 2, 0xB8, 0xC8);
    arg0->menu.options = (s32)(arg0->menu.options | 0x10000);
    arg0->modes = arg3;
}


extern Color_RGBA8 D_820091BC;
extern Color_RGBA8 D_820091C0;
M2C_UNK GridMenu_DrawInlineItems(s8*, s32, s32, s32, s32);

/**
 * Draws the FreeBattleModeWindow arg0 (window.frame.x at +0, y at +4, width at +8)
 * while func_8002AE6C() is zero: a box via Ui_DrawTexturedFrameDecal (D_800735C4), the frame via
 * Ui_DrawTexturedDivider, a filled bar via func_80029028 (color D_82009100, height 0xDC), a second
 * panel via Ui_FillRectPrimEnvColor (colors D_820091BC / D_820091C0), the sub-object at +0x2C via
 * GridMenu_DrawInlineItems, and the text pointer stored at index [+0x34] of the table of 12-byte
 * records pointed to by the word at +0x68 (the pointer is the second word of a record),
 * printed in the color from D_800734A8 via func_8001A944.
 * What the constants mean is not established.
 * Matching note: Ui_DrawTexturedDivider must be declared void (see FreeBattle_DrawOpponentSelect).
 * Seen in play: draws the 「バトルモード」 window (フリーバトル / トーナメント pictures and the description below)
 * every frame.
 */
void FreeBattle_DrawBattleModeWindow(FreeBattleModeWindow* arg0) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0xE, arg0->window.frame.y + 0xE, 0x174, 0xCC, D_800735C4);
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0xE1, arg0->window.frame.width, &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, 0xDC, *(Color82001CCC*)&D_82009100);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + 0xE8, arg0->window.frame.width - 0xC, 0x40, D_820091BC, D_820091C0);
        GridMenu_DrawInlineItems(&arg0->menu, arg0->window.frame.x + 0x10, arg0->window.frame.y + 0x10, 0xFFEF, 0);
        func_8001AB6C();
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        func_8001A384(8, 0);
        Font_SetLineHeight(0x1C);
        func_8001A944(arg0->window.frame.x + 0x14, arg0->window.frame.y + 0xEC, ((FreeBattleModeEntry*)arg0->modes)[arg0->menu.cursor].text);
        func_8001ABBC();
    }
}

extern s32 D_800603C0;

/**
 * FreeBattle_UpdateBattleModeWindow
 *
 * Returns 0 immediately unless the word at arg0 + 0x28 is 1 or 2. Otherwise,
 * if GridMenu_UpdateCursor(arg0 + 0x2C, arg0) returns 0, it reads func_8002BC14(D_800603C0):
 * -1 calls func_8003F6AC(3) and returns -1; 1 calls func_8003F6AC(2) and
 * returns the word at arg0 + 0x34 plus 1; any other value returns 0.
 * (FreeBattle_UpdatePopupMenu is the same pattern without the mode check.)
 * Seen in play: runs while the バトルモード window is up; D-Right moves the highlight to トーナメント and
 * changes the description.
 */
s32 FreeBattle_UpdateBattleModeWindow(FreeBattleModeWindow* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = arg0->window.state;
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (GridMenu_UpdateCursor(&arg0->menu, arg0) == 0) {
        tmp = func_8002BC14(D_800603C0);
        if (tmp == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (tmp == 1) {
            func_8003F6AC(2);
            result = arg0->menu.cursor + 1;
        }
    }
    return result;
}

typedef struct {
    /* 0x00 */ char* text;
    /* 0x04 */ u8* icon;
} IconPanel;

extern Gfx D_80060290[];
extern Gfx D_80060398[];
void func_80027F8C(s32);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);

/**
 * Draws one row of 「カップせんたく」: highlight box when selected (flag 0x10), a cleared-cup icon at the
 * right when flag 0x100 is set, and the cup name dimmed when locked.
 * Seen in play: draws モンスターボールカップ (boxed) and the greyed スーパーボール, ハイパーボール and マスターボールカップ.
 * Seen in play (2026-11-13) drew the rows of 「カップせんたく」 for the L1～30 tournament (モンスターボールカップ, then
 * the greyed スーパー, ハイパー and マスターボール cups).
 */
void FreeBattle_DrawCupRow(s32 arg0, s32 arg1, IconPanel* arg2, s32 arg3, s32 arg4) {
    UNUSED s32 pad[5]; // FAKE: stack padding
    s32 sp28;

    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0x14A, 0x1E, D_82009100);
    }
    if (arg4 & 0x100) {
        gSPDisplayList(gDisplayListHead++, D_80060290);
        func_8001B884(arg0 + 0x12C, arg1 + 6, 0x18, 0x18, arg2->icon, 0x18, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
    sp28 = arg1 + 6;
    Font_BeginTranslucentTextRendering();
    func_80027F8C(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, sp28, arg2->text);
    Font_EndTexturedTextRendering();
}

extern u8 D_8200A040[];
extern u8 D_820091C4[];
/**
 * Sets up the カップせんたく (choose cup) window with up to four cups.
 * Seen in play: トーナメントにでる opens 「カップせんたく」 (モンスターボールカップ, スーパーボールカップ, ハイパーボールカップ, マスターボールカップ) and
 * runs this.
 */
void FreeBattle_InitCupSelect(FreeBattleCupWindow* arg0, s32 arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 n;
    s32 i;

    if (arg3 >= 4) {
        n = 4;
    } else {
        n = arg3 + 1;
    }
    Window_SetRect(arg0, arg1, arg2, 0x15C, 0xA8);
    arg0->window.animTimer = 0;
    arg0->window.title = NULL;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x800;
    arg0->window.frame.color = D_82009100;
    arg0->window.title = D_8200A040;
    func_80027410(&arg0->items, (s32)D_820091C4, 8, 4, 4);
    Menu_Init(&arg0->menu, &arg0->items, &arg0->itemFlags, (void (*)(s32, s32, char*, s32, s32, s32*))FreeBattle_DrawCupRow, 0x150, 0x24);
    arg0->menu.options |= 0x10000;
    arg0->menu.cursor = n - 1;
    for (i = 0; i < arg3; i++) {
        arg0->menu.itemFlags[i] |= 0x100;
    }
    for (i = n; i < 4; i++) {
        arg0->menu.itemFlags[i] |= 1;
    }
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawInlineItems(s8 *, s32, s32, s32, s32);  /* extern */

/**
 * Draws the choose cup window.
 * Seen in play: draws the 「カップせんたく」 window; only モンスターボールカップ is open on a new save.
 */
void FreeBattle_DrawCupSelect(FreeBattleCupWindow* arg0, s32 arg1) {
    if (func_8002AE6C() == 0) {
        Menu_DrawInlineItems(&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 0xC, arg1 | 0xFFED, 0);
    }
}

/**
 * Variant of FreeBattle_UpdateBattleModeWindow with an extra check. Returns 0 immediately unless the
 * word at arg0 + 0x28 is 1 or 2. Otherwise, if Menu_UpdateCursorSkipDisabled(arg0 + 0x2C, arg0)
 * returns 0, it reads func_8002BC14(D_800603C0): -1 calls func_8003F6AC(3) and
 * returns -1; 1 looks at bit 0 of the u16 at index arg0->unk_34 of the array
 * pointed to by the word at arg0 + 0x30. If that bit is clear it calls
 * func_8003F6AC(2) and returns unk_34 + 1; if it is set it calls
 * func_8003F6AC(8) and returns 0. Any other value returns 0.
 * Seen in play: runs while 「カップせんたく」 is open.
 */
s32 FreeBattle_UpdateCupSelect(FreeBattleCupWindow* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = arg0->window.state;
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (Menu_UpdateCursorSkipDisabled((u8*)&arg0->menu, arg0) == 0) {
        tmp = func_8002BC14(D_800603C0);
        if (tmp == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (tmp == 1) {
            if (!(arg0->menu.itemFlags[arg0->menu.cursor] & 1)) {
                func_8003F6AC(2);
                result = arg0->menu.cursor + 1;
            } else {
                func_8003F6AC(8);
            }
        }
    }
    return result;
}

typedef struct Cfg82007C30 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Cfg82007C30; // size = 0xC
extern Color_RGBA8 D_820091E4[2];
extern Cfg82007C30 D_820091EC[2];

/**
 * Initializes the object arg0 (size and layout not established) and fills in a
 * per-entry table. Stores arg4 and arg5 in the second word of the two entries of
 * the 12-byte table D_820091EC, selects entry 1 when arg3 == 2 (otherwise entry 0),
 * calls Window_SetRect(arg0, arg1, arg2, 0x235, 0x174), clears the words at 0x20, 0x24
 * and 0x28 and sets the word at 0x14 to 0x801. Copies the selected entry's first word to
 * 0x20 and builds the sub-object at arg0 + 0xCC with func_80027410 from the entry's
 * second and third words (stride 0x50, width 0x50). Calls func_80018168(arg6), stores
 * arg6 at 0xDC and then, for each of the 0xD4 entries (stride 0x50 starting at the
 * pointer stored at 0xCC), calls func_80018234 with the entry's first byte and an
 * RGBA5551 value packed from the color D_820091E4[i & 1] (the top five bits of red, green
 * and blue go to bits 15-11, 10-6 and 5-1, and bit 0 is set).
 * What the object is and what the constants mean is not established.
 */
void func_82007C30(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s8* arg6) {
    Cfg82007C30* cfg;
    u8* entry;
    s32 sel;
    s32 i;
    s32 size;
    Color_RGBA8 color;

    if (arg3 == 2) {
        sel = 1;
    } else {
        sel = 0;
    }
    D_820091EC[0].unk4 = arg4;
    D_820091EC[1].unk4 = arg5;
    Window_SetRect(arg0, arg1, arg2, 0x235, 0x174);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x801;
    cfg = &D_820091EC[sel];
    M2C_FIELD(arg0, s32*, 0x20) = cfg->unk0;
    size = cfg->unk8;
    func_80027410(arg0 + 0xCC, cfg->unk4, 0x50, size, size);
    func_80018168(arg6);
    entry = M2C_FIELD(arg0, u8**, 0xCC);
    M2C_FIELD(arg0, s8**, 0xDC) = arg6;
    for (i = 0; i < M2C_FIELD(arg0, s32*, 0xD4); i++) {
        color = D_820091E4[i & 1];
        func_80018234(M2C_FIELD(arg0, unk_func_8001A024**, 0xDC), i, *entry,
                      ((color.r << 8) & 0xF800) | ((color.g * 8) & 0x7C0) | ((color.b >> 2) & 0x3E) | 1);
        entry += 0x50;
    }
}

extern Color82001CCC D_82009204[];
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void func_800189C0(s32, s32);
void BgStage_DrawFrame(void);
s32 PokeIcon_GetImage(s8 *arg0, s32 arg1);

void func_82007D94(s8* arg0, s32 arg1) {
    s32 i;
    s32 x;
    s32 y;
    s32 x0 = M2C_FIELD(arg0, s32*, 0) + 6;
    s32 y0 = M2C_FIELD(arg0, s32*, 4) + 6;
    s8* entry;

    if (func_8002AE6C() == 0) {
        for (i = 0; i < 42; i++) {
            gSPDisplayList(gDisplayListHead++, D_80060270);
            func_80029028((i % 7) * 0x4F + x0, (i / 7) * 0x3C + y0, 0x4F, 0x3C, D_82009204[i & 1]);
        }
        func_800189C0(M2C_FIELD(arg0, s32*, 0xDC), 0);
        BgStage_DrawFrame();
        entry = M2C_FIELD(arg0, s8**, 0xCC);
        for (i = 0; i < M2C_FIELD(arg0, s32*, 0xD4); i++) {
            func_8001AB6C();
            func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
            func_8001A384(4, -1);
            x = (i % 7) * 0x4F + x0;
            y = (i / 7) * 0x3C + y0;
            func_8001A944(x + 2, y + 0x2A, entry + 0x30);
            func_8001ABBC();
            gSPDisplayList(gDisplayListHead++, D_80073408);
            func_8001B884(x + 0x26, y + 2, 0x28, 0x28, PokeIcon_GetImage(M2C_FIELD(arg0, s32*, 0xDC), i), 0x28, 0x200000);
            gSPDisplayList(gDisplayListHead++, D_80073438);
            entry += 0x50;
        }
    }
}

extern s32 D_800603C0;

/*
 * func_82008044
 *
 * Returns 0 immediately unless the word at arg0 + 0x28 is 1 or 2. Otherwise
 * reads func_8002BC14(D_800603C0): -1 or 1 calls func_8003F6AC(3) and returns
 * -1; any other value returns 0.
 */
s32 func_82008044(void* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = M2C_FIELD(arg0, s32*, 0x28);
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    tmp = func_8002BC14(D_800603C0);
    if ((tmp == -1) || (tmp == 1)) {
        func_8003F6AC(3);
        result = -1;
    }
    return result;
}

void Window_SetRect(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern Color_RGBA8 D_8200920C;
extern Color_RGBA8 D_82009210;
extern u8 D_8200A0A0[];
/**
 * Sets up the ちゅうい！！ (warning) window for duplicate species.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void FreeBattle_InitDuplicateWarning(FreeBattleDuplicateWarning* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Window_SetRect(arg0, arg1, arg2, 0x148, 0x68);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x2806;
    arg0->window.frame.color = D_8200920C;
    arg0->window.frame.color2 = D_82009210;
    arg0->window.title = D_8200A0A0;
    arg0->value = arg3;
}

void func_8001AB6C(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A384(s32, s32);
void Font_SetLineHeight(s32 arg0);
void func_8001A944(s32, s32, const char*, ...);
void func_8001ABBC(void);
extern u8 D_800734A8[];
extern char D_8200A0B0[];

/**
 * Draws おなじポケモンが %dたいいます (there are %d of the same Pokemon).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void FreeBattle_DrawDuplicateWarning(FreeBattleDuplicateWarning* arg0) {
    if (func_8002AE6C() == 0) {
        func_8001AB6C();
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        func_8001A384(8, 0);
        Font_SetLineHeight(0x1C);
        func_8001A944(arg0->window.frame.x + 0xE, arg0->window.frame.y + 0xE, D_8200A0B0, arg0->value);
        func_8001ABBC();
    }
}

void Window_InitLabeled(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);
extern Color_RGBA8 D_82009218;
extern char D_8200A104[];
extern char D_8200A114[];
extern char D_8200A11C[];

/**
 * Initializes the FreeBattleShortageWarning arg0; the same
 * setup as FreeBattle_InitLevelSumWarning with different strings (D_8200A104, D_8200A114 and
 * D_8200A11C) and color (D_82009218), and one more argument. Calls
 * Window_SetRect(arg0, arg1, arg2, 0x134, 0x92), clears the words at 0x24 and
 * 0x28, sets the word at 0x14 to 0x2801 and the pointer at 0x20 to D_8200A104.
 * Calls Window_InitLabeled on the sub-objects at arg0 + 0x2C and arg0 + 0x68, sets
 * the words at 0x58, 0x60, 0xAC and 0xA8 to 0xA, 0xC, 2 and 0, stores
 * D_800603C0 and then arg3 in the word at 0xA4 (calling func_8000B2F4 with
 * each), and finally stores arg3 at 0xB4 and arg4 at 0xB0.
 * What the object is and what the constants mean is not established.
 * Seen in play (2026-11-13) in the L1～30 tournament (モンスターボールカップ) entry, A on the GB party of three
 * opened 「ちゅうい!! つかえるポケモンが 6たい たりません」 with はい/いいえ, and this ran once as it appeared.
 */
void FreeBattle_InitShortageWarning(FreeBattleShortageWarning* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Window_SetRect(arg0, arg1, arg2, 0x134, 0x92);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x2801;
    arg0->window.title = D_8200A104;
    Window_InitLabeled(&arg0->yesButton, arg0->window.frame.x + 0x2E, arg0->window.frame.y + 0x6E, 0x48, D_82009218, D_8200A114);
    arg0->yesButton.labelX = 0xA;
    arg0->yesButton.unk_34 = 0xC;
    Window_InitLabeled(&arg0->noButton, arg0->window.frame.x + 0xBE, arg0->window.frame.y + 0x6E, 0x48, D_82009218, D_8200A11C);
    arg0->choice.count = 2;
    arg0->choice.cursor = 0;
    arg0->choice.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->choice.controller = arg3;
    func_8000B2F4(arg3);
    arg0->controller = arg3;
    arg0->count = arg4;
}

extern Color_RGBA8 D_8200921C;
extern Color_RGBA8 D_82009220;
extern char D_8200A124[];

/**
 * Draws the FreeBattleShortageWarning arg0: the same drawing code as
 * FreeBattle_DrawLevelSumWarning with different colors (D_8200921C / D_82009220) and text
 * (D_8200A124), which is printed with the word at +0xB0 passed twice as extra
 * arguments to func_8001A944. See FreeBattle_DrawLevelSumWarning for the sequence of calls; the
 * selection index at +0xA8 again decides which of the two sub-objects (+0x2C,
 * +0x68) gets 2 from Window_DrawLabeled and which gets 0.
 * What the constants mean is not established.
 * Seen in play (2026-11-13) drew the 「ちゅうい!! つかえるポケモンが 6たい たりません」 warning on the tournament entry
 * screen every frame while it was up.
 */
void FreeBattle_DrawShortageWarning(FreeBattleShortageWarning* arg0) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x61, arg0->window.frame.width, &D_8007356C);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + 6, 0x128, 0x5C, D_8200921C, D_82009220);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x68, arg0->window.frame.width - 0xC, 0x24, *(Color82001CCC*)&D_82009100);
        func_8001AB6C();
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        func_8001A384(8, 0);
        Font_SetLineHeight(0x1C);
        func_8001A944(arg0->window.frame.x + 0xE, arg0->window.frame.y + 0xE, D_8200A124, arg0->count, arg0->count);
        func_8001ABBC();
        Window_DrawLabeled(&arg0->yesButton, (arg0->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&arg0->noButton, (arg0->choice.cursor == 1) ? 2 : 0);
    }
}

s32 func_8002B390(s32);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);

/**
 * Handles the too few usable Pokemon warning.
 * Seen in play (2026-11-13) ran every frame while the tournament entry screen's 「つかえるポケモンが 6たい
 * たりません」 warning waited for はい/いいえ.
 */
s32 FreeBattle_UpdateShortageWarning(FreeBattleShortageWarning* arg0) {
    s32 ret = 0;
    s32 temp_v0;

    if (func_8002B390(&arg0->choice) == 0) {
        temp_v0 = func_8002BC14(arg0->controller);
        if (temp_v0 == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (temp_v0 == 1) {
            switch (arg0->choice.cursor) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    func_8003F6AC(3);
                    ret = -1;
                    break;
            }
        }
    }
    return ret;
}

extern Color_RGBA8 D_82009228;
extern char D_8200A178[];
extern char D_8200A188[];
extern char D_8200A190[];
void Window_InitLabeled(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);

/**
 * Initializes the FreeBattleLevelSumWarning arg0: calls
 * Window_SetRect(arg0, arg1, arg2, 0x134, 0x92), clears the words at 0x24 and
 * 0x28, sets the word at 0x14 to 0x2801 and the pointer at 0x20 to
 * D_8200A178. Calls Window_InitLabeled twice, on the sub-objects at arg0 + 0x2C
 * (string D_8200A188) and arg0 + 0x68 (string D_8200A190), both with width
 * 0x48 and color D_82009228 and positions derived from the words at 0 and 4.
 * Then sets the words at 0x58, 0x60, 0xAC and 0xA8 to 0xA, 0xC, 2 and 0, and
 * stores D_800603C0 and then arg3 in the word at 0xA4, calling func_8000B2F4
 * with each value in turn. Finally stores arg3 at 0xB0.
 * What the object is and what the constants mean is not established.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void FreeBattle_InitLevelSumWarning(FreeBattleLevelSumWarning* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Window_SetRect(arg0, arg1, arg2, 0x134, 0x92);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x2801;
    arg0->window.title = D_8200A178;
    Window_InitLabeled(&arg0->yesButton, arg0->window.frame.x + 0x2E, arg0->window.frame.y + 0x6E, 0x48, D_82009228, D_8200A188);
    arg0->yesButton.labelX = 0xA;
    arg0->yesButton.unk_34 = 0xC;
    Window_InitLabeled(&arg0->noButton, arg0->window.frame.x + 0xBE, arg0->window.frame.y + 0x6E, 0x48, D_82009228, D_8200A190);
    arg0->choice.count = 2;
    arg0->choice.cursor = 0;
    arg0->choice.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->choice.controller = arg3;
    func_8000B2F4(arg3);
    arg0->controller = arg3;
}

extern Color_RGBA8 D_8200922C;
extern Color_RGBA8 D_82009230;
extern char D_8200A198[];

/**
 * Draws the FreeBattleLevelSumWarning arg0 ( the same kind of object that
 * FreeBattle_InitLevelSumWarning / FreeBattle_InitRentalConfirm initialize: x at +0, y at +4, width at +8, a
 * selection index at +0xA8 and two sub-objects at +0x2C and +0x68). Does nothing
 * while func_8002AE6C() is non-zero. Otherwise it draws the frame with
 * Ui_DrawTexturedDivider and Ui_FillRectPrimEnvColor, emits D_80060270 and fills a bar with
 * func_80029028 (color D_82009100), then prints the string D_8200A198 with the
 * font color from D_800734A8 via func_8001A944, and finally calls Window_DrawLabeled
 * on the two sub-objects with 2 for the one whose index (0 for +0x2C, 1 for +0x68)
 * equals the selection at +0xA8 and 0 for the other.
 * What the constants mean is not established.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void FreeBattle_DrawLevelSumWarning(FreeBattleLevelSumWarning* arg0) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x61, arg0->window.frame.width, &D_8007356C);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + 6, 0x128, 0x5C, D_8200922C, D_82009230);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x68, arg0->window.frame.width - 0xC, 0x24, *(Color82001CCC*)&D_82009100);
        func_8001AB6C();
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        func_8001A384(8, 0);
        Font_SetLineHeight(0x1C);
        func_8001A944(arg0->window.frame.x + 0xE, arg0->window.frame.y + 0xE, D_8200A198);
        func_8001ABBC();
        Window_DrawLabeled(&arg0->yesButton, (arg0->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&arg0->noButton, (arg0->choice.cursor == 1) ? 2 : 0);
    }
}

s32 func_8002B390(s32);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);

/**
 * Handles the level sum warning.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 FreeBattle_UpdateLevelSumWarning(FreeBattleLevelSumWarning* arg0) {
    s32 ret = 0;
    s32 temp_v0;

    if (func_8002B390(&arg0->choice) == 0) {
        temp_v0 = func_8002BC14(arg0->controller);
        if (temp_v0 == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (temp_v0 == 1) {
            switch (arg0->choice.cursor) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    func_8003F6AC(3);
                    ret = -1;
                    break;
            }
        }
    }
    return ret;
}

extern Color_RGBA8 D_82009234;
extern char D_8200A1EC[];
extern char D_8200A1F4[];
extern char D_8200A1FC[];

/**
 * Initializes the FreeBattleRentalConfirm arg0; a sibling of
 * FreeBattle_InitConfirmWindow. Calls Window_SetRect(arg0, arg1, arg2, 0x18C, 0x66), clears the words at
 * 0x20, 0x24 and 0x28 and sets the word at 0x14 to 0x1001. Calls Window_InitLabeled three times,
 * on the sub-objects at arg0 + 0x2C (string D_8200A1EC), + 0x68 (D_8200A1F4) and + 0xA4
 * (D_8200A1FC, width 0x5C; the other two use width 0x48), all with color D_82009234 and
 * positions derived from the words at 0 and 4; the words at 0x58 and 0x60 are set to 0xA
 * and 0xC between the first two calls. Then clears the word at 0xE4, stores arg3 at 0xEC
 * and 3 (arg3 != 0) or 2 (arg3 == 0) at 0xE8, and stores D_800603C0 and then arg4 in the
 * word at 0xE0 (calling func_8000B2F4 with each).
 * What the object is and what the constants mean is not established.
 * Seen in play: A on a team opens 「このデータでエントリーします。 はい いいえ」 and runs this.
 */
void FreeBattle_InitRentalConfirm(FreeBattleRentalConfirm* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Window_SetRect(arg0, arg1, arg2, 0x18C, 0x66);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x1001;
    Window_InitLabeled(&arg0->buttons[0], arg0->window.frame.x + 0x76, arg0->window.frame.y + 0x42, 0x48, D_82009234, D_8200A1EC);
    arg0->buttons[0].labelX = 0xA;
    arg0->buttons[0].unk_34 = 0xC;
    Window_InitLabeled(&arg0->buttons[1], arg0->window.frame.x + 0xC6, arg0->window.frame.y + 0x42, 0x48, D_82009234, D_8200A1F4);
    Window_InitLabeled(&arg0->buttons[2], arg0->window.frame.x + 0x122, arg0->window.frame.y + 0x42, 0x5C, D_82009234, D_8200A1FC);
    arg0->choice.cursor = 0;
    arg0->hasThirdButton = arg3;
    if (arg3 != 0) {
        arg0->choice.count = 3;
    } else {
        arg0->choice.count = 2;
    }
    arg0->choice.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->choice.controller = arg4;
    func_8000B2F4(arg4);
}

extern Color_RGBA8 D_82009238;
extern Color_RGBA8 D_8200923C;
extern char D_8200A208[];

/**
 * Draws the FreeBattleRentalConfirm arg0: a variant of FreeBattle_DrawLevelSumWarning /
 * FreeBattle_DrawShortageWarning with a shorter frame (height 0x30) and colors D_82009238 /
 * D_8200923C, text D_8200A208 in a larger font size (0x10), and a selection index
 * at +0xE4 (rather than +0xA8) that decides which of the sub-objects at +0x2C, +0x68
 * and, only when the word at +0xEC is non-zero, +0xA4 is passed 2 by Window_DrawLabeled
 * (index 0, 1 or 2 respectively); the others get 0.
 * What the constants mean is not established.
 * Seen in play: draws 「このデータでエントリーします。」 with はい / いいえ.
 */
void FreeBattle_DrawEntryConfirm(FreeBattleRentalConfirm* arg0) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x35, arg0->window.frame.width, &D_8007356C);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, 0x30, D_82009238, D_8200923C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x3C, arg0->window.frame.width - 0xC, 0x24, *(Color82001CCC*)&D_82009100);
        func_8001AB6C();
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        func_8001A384(0x10, 0);
        func_8001A944(arg0->window.frame.x + 0x12, arg0->window.frame.y + 0x12, D_8200A208);
        func_8001ABBC();
        Window_DrawLabeled(&arg0->buttons[0], (arg0->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&arg0->buttons[1], (arg0->choice.cursor == 1) ? 2 : 0);
        if (arg0->hasThirdButton != 0) {
            Window_DrawLabeled(&arg0->buttons[2], (arg0->choice.cursor == 2) ? 2 : 0);
        }
    }
}

s32 func_8002B390(s32);                             /* extern */
s32 func_8002BC14(s32);                             /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */

/**
 * Handles the rental confirm window.
 * Seen in play: runs while 「このデータでエントリーします。」 is open; はい enters the team.
 */
s32 FreeBattle_UpdateRentalConfirm(FreeBattleRentalConfirm* arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;

    var_s0 = 0;
    if (func_8002B390(&arg0->choice) == 0) {
        temp_v0 = func_8002BC14(arg0->choice.controller);
        if (temp_v0 == -1) {
            func_8003F6AC(3);
            var_s0 = -1;
        } else if (temp_v0 == 1) {
            temp_v0_2 = arg0->choice.cursor;
            switch (temp_v0_2) {                    /* irregular */
            case 0:
                var_s0 = 1;
                break;
            case 2:
                var_s0 = 2;
                break;
            case 1:
                var_s0 = -1;
                func_8003F6AC(3);
                break;
            }
        }
    }
    return var_s0;
}
