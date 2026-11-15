/* Object boundary at 0x82005D90 (16-byte text alignment). */
/* Stadium Zero fragment007_166580. */

#include "global.h"
#include "m2c_macros.h"

#include "free_battle_setup.h"
s32 Deck_Open(s32, s32, s32, s32);
s32 Deck_ReadEntries(void*, s32, s32);
void Deck_CloseAndFlush(s32);
void Pokemon_PrepareBattleMon(u8*);
extern u8 D_80065D00[];

s32 FreeBattle_ReadTeam(s32 arg0, s32 arg1, s32 arg2, TeamMonSlot* entry);

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 Pokemon_GetTypeIndex(s32, s32);
void Font_BeginTranslucentTextRendering(void);
void Font_SetActive(s32, s32);
void Font_EndTexturedTextRendering(void);
void Font_SetLineHeight(s32 arg0);
void Gfx_SetEnvColor(u8, u8, u8, u8);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);

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

s32 Ui_HandleHorizontalSelectionInput(s32);
s32 Ui_GetSelectionDirection(s32);
M2C_UNK Audio_PlaySystemSound(M2C_UNK);

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

void FreeBattle_UpdateTeamSlotCursor(s32 arg0);


M2C_UNK FreeBattle_BuildBattleRosters(s8 *, s8 *, s8 *, s32, s32, s32); /* extern */

void FreeBattle_CommitEntries(s8 *arg0);

extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;
s32 GbSave_GetActivePort(void);
void func_80027FF8(void*, s32);
s32 Util_Malloc(s32);
void FreeBattle_InitBattleModeScreen(s32);
void FreeBattle_CreateScreen(void);

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

M2C_UNK Util_Free(s32);                         /* extern */
extern s32 D_8200AD28;

void FreeBattle_FreeScreen(void);

extern s32 D_8200AD08[8];
extern s32 D_8200AC40;
extern s32 D_820090DC[8];
s32 BinArchive_GetFile(s32, s32);

void FreeBattle_LoadArchiveFiles(void);

s32 Font_Init(s32 load_size, s32 side);
s8 *PokeIcon_AllocFramebuffers(s32 arg0);
u16* func_80018F2C(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80017FDC(s32, s32, s32, s32);
s32 BinArchive_Open(u8*, u8*, s32, s32);
void PokeIcon_OpenModelArchives(void);
void Fragment_Load(s32, u8*, u8*);
void Asset_LoadToSegment(s32, u8*, u8*, s32);
s32 Memmap_GetSegmentVaddr(u8*);
void FreeBattle_RestoreMenuState(s32);
s32 StageFade_Start(s32);
void func_80006828(s32, void*);
void Audio_PlayMusicIfChanged(s32);
void func_80006998(s32);
void Audio_StopMusic(s32);
void StageLoader_WaitForRetrace(void);
void StageLoader_UpdateSegments(void);
s32 FreeBattle_UpdateFade(s32);
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
extern s32 D_82008F84;
M2C_UNK FreeBattle_RunSetupScreen(void);

M2C_UNK MainPool_PushState(M2C_UNK);                     /* extern */
M2C_UNK MainPool_PopState(M2C_UNK);                     /* extern */
M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32); /* extern */
M2C_UNK FreeBattle_RunSetupScreen();                            /* extern */
M2C_UNK FreeBattle_SetupGbCartVersus();                            /* extern */
extern s8 D_00235D70;
extern s8 D_00238BD0;
extern s32 D_82008F84;
extern s8 D_88000000;
/**
 * Entry point of the battle setup fragment: pushes the 'MENT' pool state, runs the setup screen
 * (or, when `mode` is 1, FreeBattle_SetupGbCartVersus), pops the state and, when the screen was
 * left with B (0x8040), queues the main menu. Returns 0x8040 (back to the main menu) or 0x8050
 * (start the battle).
 * Seen in play (2026-11-14): ran with `mode` 0 when はい was picked on the main menu's バトル
 * prompt. Both callers (main_menu.c, main_menu_entry.c) pass 0, so the `mode` 1 branch is not
 * reachable in retail.
 */
s32 FreeBattle_Main(s32 arg0, M2C_UNK arg1);

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
void FreeBattle_DrawMenuRow(s32 x, s32 y, char* text, s32 index, s32 flags, s32* row_width) {
    s32 temp_v0 = *row_width;

    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, temp_v0 - 6, 26, D_82009100);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 8, y + 4, text);
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
void FreeBattle_InitMenuWindow(MenuWindow* window, s32 x, s32 y, s32 width, s32 height, s32 items, s32 item_count, char** descriptions, s32 description_lines, char* title) {
    Window_SetRect(&window->window, x, y, width, height);
    window->window.state = 0;
    window->window.animTimer = 0;
    window->window.frame.style = 0x801;
    window->window.title = title;
    func_80027804(&window->itemList, items, item_count, item_count);
    Menu_Init(&window->menu, &window->itemList, window->itemFlags, FreeBattle_DrawMenuRow, width - 12, 0x20);
    window->menu.options = (s32) (window->menu.options | 0x10000);
    window->descriptions = descriptions;
    window->descriptionLines = description_lines;
}

s32 func_8002AE6C();
void Menu_DrawItems(void*, s32, s32, s32, s8 *);
extern Color_RGBA8 D_82009104;
extern Color_RGBA8 D_82009108;

/**
 * Draws the window while func_8002AE6C() is zero: the list panel (rows * 32 + 8 high), the
 * description box (descriptionLines * 0x1C high), the menu rows via Menu_DrawItems (flags
 * flags | 0xFFED, row width passed by pointer in sp38) and descriptions[menu.cursor] in the
 * color from D_800734A8.
 * What the constants mean is not established. `pad` places sp38 at sp+0x38 as in the ROM.
 * Seen in play: draws the 「たいせんルールせんたく」 list window with its description box.
 */
void FreeBattle_DrawMenuWindow(MenuWindow* window, s32 flags) {
    s32 pad; // FAKE: stack padding
    s32 sp38;
    s32 temp_s1;

    if (func_8002AE6C() == 0) {
        temp_s1 = (window->menu.items->count << 5) + 8;
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + temp_s1 + 5, window->window.frame.width, &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(window->window.frame.x + 6, window->window.frame.y + 6, window->window.frame.width - 12, temp_s1, *(Color82001CCC*)&D_82009100);
        Ui_FillRectPrimEnvColor(window->window.frame.x + 6, window->window.frame.y + temp_s1 + 12, window->window.frame.width - 12, window->descriptionLines * 28, D_82009104, D_82009108);
        sp38 = window->window.frame.width - 12;
        Menu_DrawItems(&window->menu, window->window.frame.x + 6, window->window.frame.y + 10, flags | 0xFFED, (s8*)&sp38);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(28);
        Font_Printf(window->window.frame.x + 14, window->window.frame.y + temp_s1 + 0x10, window->descriptions[window->menu.cursor]);
        Font_EndTexturedTextRendering();
    }
}

extern s32 D_800603C0;

/**
 * FreeBattle_UpdateMenuWindow
 *
 * Returns 0 immediately unless the word at window + 0x28 is 1 or 2. Otherwise,
 * if Menu_UpdateCursor(window + 0x2C, window) returns 0, it reads Ui_GetSelectionDirection(D_800603C0):
 * -1 calls Audio_PlaySystemSound(3) and returns -1; 1 calls Audio_PlaySystemSound(2) and
 * returns the word at window + 0x34 plus 1; any other value returns 0.
 * (FreeBattle_UpdatePopupMenu is the same pattern without the mode check.)
 * Seen in play: runs while the 「たいせんルールせんたく」 list is open.
 */
s32 FreeBattle_UpdateMenuWindow(MenuWindow* window) {
    s32 result = 0;
    s32 tmp;

    tmp = window->window.state;
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (Menu_UpdateCursor(&window->menu, window) == 0) {
        tmp = Ui_GetSelectionDirection(D_800603C0);
        if (tmp == -1) {
            Audio_PlaySystemSound(3);
            result = -1;
        } else if (tmp == 1) {
            Audio_PlaySystemSound(2);
            result = window->menu.cursor + 1;
        }
    }
    return result;
}

/**
 * Draws one popup menu row with the selection highlight.
 * Seen in play: draws each numbered row of the ルールをみる rules list.
 */
void FreeBattle_DrawPopupRow(s32 x, s32 y, char* text, s32 index, s32 flags, MenuWindow* window) {
    if (flags & 0x18) {
        Ui_FillRectHighlighted(x + 3, y + 3, window->window.frame.width - 18, 30, window->window.frame.color);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 12, y + 6, text);
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
void FreeBattle_InitPopupMenu(MenuWindow* window, s32 x, s32 y, List820061F0 *items, s8 *item_flags, Color_RGBA8 color) {
    s32 i;
    s32 w;
    s32 max = 0;
    s32 h;

    for (i = 0; i < items->count; i++) {
        w = func_800566BC(items->items[i]) >> 1;
        if (max < w) {
            max = w;
        }
    }
    func_80027804(&window->itemList, (s32)items->items, items->count, items->count);
    h = max * 24 + 24;
    Menu_Init(&window->menu, &window->itemList, item_flags, (void (*)(s32, s32, char *, s32, s32, s32 *))FreeBattle_DrawPopupRow, h, 36);
    window->menu.options |= 0x10000;
    Window_SetRect(&window->window, x, y, h + 12, items->count * 36 + 24);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 0x800;
    window->window.title = items->unk8;
    window->window.frame.color = color;
}

s32 func_8002AE6C();                                /* extern */
void Menu_DrawItems(void*, s32, s32, s32, s8 *);  /* extern */
// FAKE: permuter output (the new_var temp and the no-op test).
/**
 * Draws a popup menu's items.
 * Seen in play: draws the ルールをみる rules list window.
 */
void FreeBattle_DrawPopupMenu(MenuWindow* window, s32 flags)
{
  Menu *new_var; // FAKE: permuter temp
  if (func_8002AE6C() == 0)
  {
    if (window && window)
    {
    }
    Menu_DrawItems(new_var = &window->menu, window->window.frame.x + 6, window->window.frame.y + 12, flags | 0xFFED, (s8*)window); // FAKE: permuter temp
  }
}

s32 Ui_GetSelectionDirection(s32);
M2C_UNK Audio_PlaySystemSound(M2C_UNK);
extern s32 D_800603C0;
/**
 * Moves a popup menu's cursor. Returns -1 on cancel, the 1-based row on confirm.
 * Seen in play: runs while the rules list is open; D-Down moves the highlight down the rules.
 */
s32 FreeBattle_UpdatePopupMenu(MenuWindow* window) {
    s32 sp1C = 0;
    s32 dir;

    if (Menu_UpdateCursor(&window->menu) == 0) {
        dir = Ui_GetSelectionDirection(D_800603C0);
        if (dir == -1) {
            Audio_PlaySystemSound(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = window->menu.cursor + 1;
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
void FreeBattle_DrawOpponentOption(s32 x, s32 y, char* text, s32 index, s32 flags) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    Color_RGBA8 c;

    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 70, 22, D_82009100);
    }
    Font_BeginTranslucentTextRendering();
    c = ((Color_RGBA8*)&D_800734A8)[(flags & 2) ? 0 : 1];
    if (flags & 1) {
        c.a = 0x4C;
    }
    Gfx_SetEnvColor(c.r, c.g, c.b, c.a);
    Font_SetActive(8, 0);
    Font_Printf(x + 8, y + 4, text);
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
void FreeBattle_DrawControllerPanel(s32 x, s32 y, s32 present, s32 active, s32 mark_a, s32 mark_b) {
    s32 i;

    Ui_FillRectPrimEnvColor(x, y, 390, 141, D_8200914C, D_82009150);
    Ui_DrawImageInStrips(D_8200911C, x + 136, y + 5);
    for (i = 0; i != 4; i++) {
        if ((present >> i) & 1) {
            if ((active >> i) & 1) {
                Ui_DrawImageInStrips(D_8200912C, D_8200915C[i].x + x, D_8200915C[i].y + y);
            } else {
                Ui_DrawImageInStrips(D_8200913C, D_8200915C[i].x + x, D_8200915C[i].y + y + 12);
            }
        }
        if ((mark_a >> i) & 1) {
            Ui_DrawRoundedFrame(D_8200915C[i].x + x, D_8200915C[i].y + y, 58, 67, D_82009154);
        }
        if ((mark_b >> i) & 1) {
            Ui_DrawRoundedFrame(D_8200915C[i].x + x, D_8200915C[i].y + y, 58, 67, D_82009158);
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
 * Initializes the FreeBattleOpponentWindow window: calls
 * Window_SetRect(&window->window, x, y, 402, 271), style 0x801, title D_82009F70; the
 * four options D_8200917C go into itemList and the menu (FreeBattle_DrawOpponentOption rows).
 * controllerMask = controllerMask. With mask = ~controllerMask (OR 0xE when controllerCount == 1), each of the bits 2, 4 and 8
 * set in mask disables option 0, 1 or 2. Stores gbSaveReadyMask at unk_70 and moves the cursor to an
 * enabled option (Menu_SkipDisabledForward).
 *
 * Same family as FreeBattle_InitBattleModeWindow and FreeBattle_InitMenuWindow. What the object, the bits
 * and the values mean is not established. Matching notes: the sub-object
 * addresses are held in the locals sp2C and sp28 (the ROM spills them), and
 * the unused leading `pad` local places those spill slots at sp+0x2C and
 * sp+0x28.
 * Seen in play: たいせんする opens 「あいてをせんたく」 (1P VS, 2P 3P 4P COM) and runs this.
 */
void FreeBattle_InitOpponentSelect(FreeBattleOpponentWindow* window, s32 x, s32 y, s32 controller_mask, s32 controller_count, s32 gb_save_ready_mask) {
    s32 pad; // FAKE: stack padding
    s8 *sp2C;
    s8 *sp28;
    s32 var_v1;

    Window_SetRect(&window->window, x, y, 402, 271);
    window->window.animTimer = 0;
    window->window.state = 0;
    window->window.frame.style = 0x801;
    window->window.title = (char*)&D_82009F70;
    sp2C = (s8*)&window->itemList;
    func_80027804(sp2C, (s32)&D_8200917C, 4, 4);
    sp28 = (s8*)&window->menu;
    Menu_Init(sp28, sp2C, window->itemFlags, (void (*)(s32, s32, char *, s32, s32, s32 *))FreeBattle_DrawOpponentOption, 76, 28);
    window->menu.options = (s32) (window->menu.options | 0x10000);
    window->controllerMask = controller_mask;
    var_v1 = ~controller_mask;
    if (controller_count == 1) {
        var_v1 |= 0xE;
    }
    if (var_v1 & 2) {
        window->menu.itemFlags[0] |= 1;
    }
    if (var_v1 & 4) {
        window->menu.itemFlags[1] |= 1;
    }
    if (var_v1 & 8) {
        window->menu.itemFlags[2] |= 1;
    }
    window->unk_70 = gb_save_ready_mask;
    Menu_SkipDisabledForward(sp28, controller_mask);
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
void FreeBattle_DrawOpponentSelect(FreeBattleOpponentWindow* window) {
    s32 sp2C;

    sp2C = 0;
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + 146, window->window.frame.width, &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(window->window.frame.x + 6, window->window.frame.y + 153, window->window.frame.width - 12, 112, *(Color82001CCC*)&D_82009100);
        Ui_DrawImageInStrips(D_8200910C, window->window.frame.x + 169, window->window.frame.y + 193);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_Printf(window->window.frame.x + 54, window->window.frame.y + 195, D_82009F84);
        Font_EndTexturedTextRendering();
        Menu_DrawItems(&window->menu, window->window.frame.x + 272, window->window.frame.y + 153, 0xFEF, 0);
        switch (window->menu.cursor) {
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
        FreeBattle_DrawControllerPanel(window->window.frame.x + 6, window->window.frame.y + 6, window->controllerMask, window->unk_70, 1, sp2C);
    }
}

/**
 * Variant of FreeBattle_UpdateBattleModeWindow whose sub-object is at window + 0x38. Returns 0
 * immediately unless the word at window + 0x28 is 1 or 2. Otherwise, if
 * Menu_UpdateCursorSkipDisabled(window + 0x38, window) returns 0, it reads
 * Ui_GetSelectionDirection(D_800603C0): -1 calls Audio_PlaySystemSound(3) and returns -1; 1 calls
 * Audio_PlaySystemSound(2), returns 1 and maps the word at window + 0x40 (0..3) to the
 * value 2..5 stored in the word at window + 0x64. Any other value returns 0.
 * Seen in play: runs while 「あいてをせんたく」 is open.
 */
s32 FreeBattle_UpdateOpponentSelect(FreeBattleOpponentWindow* window) {
    s32 result = 0;
    s32 tmp;

    tmp = window->window.state;
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (Menu_UpdateCursorSkipDisabled(&window->menu, window) == 0) {
        tmp = Ui_GetSelectionDirection(D_800603C0);
        if (tmp == -1) {
            Audio_PlaySystemSound(3);
            result = -1;
        } else if (tmp == 1) {
            Audio_PlaySystemSound(2);
            result = 1;
            switch (window->menu.cursor) {
                case 0:
                    window->choice = 2;
                    break;
                case 1:
                    window->choice = 3;
                    break;
                case 2:
                    window->choice = 4;
                    break;
                case 3:
                    window->choice = 5;
                    break;
            }
        }
    }
    return result;
}

/**
 * Menu row callback of the tag opponent window: prints one option, highlighted when `flags`
 * has 0x10 and translucent when it has 1 (disabled).
 * Not reached in play: the tag opponent window is never opened (see
 * FreeBattle_InitTagOpponentSelect).
 * @unverified Name from the code.
 */
void FreeBattle_DrawTagOpponentOption(s32 x, s32 y, char* text, s32 index, s32 flags) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    Color_RGBA8 c;

    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 110, 22, D_82009100);
    }
    Font_BeginTranslucentTextRendering();
    c = ((Color_RGBA8*)&D_800734A8)[(flags & 2) ? 0 : 1];
    if (flags & 1) {
        c.a = 0x4C;
    }
    Gfx_SetEnvColor(c.r, c.g, c.b, c.a);
    Font_SetActive(8, 0);
    Font_Printf(x + 8, y + 4, text);
    Font_EndTexturedTextRendering();
}


/**
 * Disables (bit 0) the opponent options of the tag opponent window that need a controller that is
 * not plugged in: no 2P disables 2P, 2P&3P and 2P&4P; no 3P disables 3P, 2P&3P and 3P&4P; no 4P
 * disables 4P, 2P&4P and 3P&4P.
 * The bank pointer is re-read from `window` for every update because the compiler is not told the
 * stores cannot change it.
 * Not reached in play: the tag opponent window is never opened (see
 * FreeBattle_InitTagOpponentSelect).
 * @unverified Name from the code.
 */
void FreeBattle_DisableAbsentTagOpponents(FreeBattleTeamOpponentWindow* window) {
    s32 inv;

    inv = ~window->controllerMask;
    if (inv & 2) {
        window->opponentMenu.itemFlags[0] |= 1;
        window->opponentMenu.itemFlags[3] |= 1;
        window->opponentMenu.itemFlags[4] |= 1;
    }
    if (inv & 4) {
        window->opponentMenu.itemFlags[1] |= 1;
        window->opponentMenu.itemFlags[3] |= 1;
        window->opponentMenu.itemFlags[5] |= 1;
    }
    if (inv & 8) {
        window->opponentMenu.itemFlags[2] |= 1;
        window->opponentMenu.itemFlags[4] |= 1;
        window->opponentMenu.itemFlags[5] |= 1;
    }
}

extern M2C_UNK D_82009190;
extern M2C_UNK D_820091A0;
extern M2C_UNK D_82009FCC;

/**
 * Sets up the tag opponent window, a version of 「あいてをせんたく」 for two-player teams: a side
 * menu (1P, 1P&2P, 1P&3P, 1P&4P; D_82009190) and an opponent menu (2P, 3P, 4P, 2P&3P, 2P&4P,
 * 3P&4P, COM; D_820091A0), both drawn by FreeBattle_DrawTagOpponentOption. Options that need an
 * absent controller (`controllerMask`) are disabled, all partner options when `controllerCount`
 * is 2.
 * Matching notes: the sub-object addresses are held in the locals sp2C and sp28 (the ROM spills
 * them), the unused leading `pad` places the spill slots, and gbSaveReadyMask is stored before the constant 1
 * so that its load comes first.
 * Not reached in play: nothing calls it. FreeBattleScreen keeps room for the window at 0x45C8 and
 * FreeBattle_DrawScreen draws it in state 6, but FreeBattle_SetScreenState never opens state 6;
 * Free Battle only offers 1P against one opponent.
 * @unverified Name from the code.
 */
void FreeBattle_InitTagOpponentSelect(FreeBattleTeamOpponentWindow* window, s32 x, s32 y, s32 controller_mask, s32 controller_count, s32 gb_save_ready_mask) {
    s32 pad; // FAKE: stack padding
    void *sp2C;
    void *sp28;
    s32 var_v1;

    Window_SetRect(&window->window, x, y, 402, 355);
    window->window.animTimer = 0;
    window->window.state = 0;
    window->window.frame.style = 0x801;
    window->window.title = &D_82009FCC;
    sp2C = &window->sideItemList;
    func_80027804(sp2C, (s32)&D_82009190, 4, 4);
    sp28 = &window->sideMenu;
    Menu_Init(sp28, sp2C, &window->sideItemFlags, (void (*)(s32, s32, char *, s32, s32, s32 *))FreeBattle_DrawTagOpponentOption, 116, 28);
    sp2C = &window->opponentItemList;
    window->sideMenu.options = (s32) (window->sideMenu.options | 0x10000);
    func_80027804(sp2C, (s32)&D_820091A0, 7, 7);
    Menu_Init(&window->opponentMenu, sp2C, &window->opponentItemFlags, (void (*)(s32, s32, char *, s32, s32, s32 *))FreeBattle_DrawTagOpponentOption, 116, 28);
    window->opponentMenu.options = (s32) (window->opponentMenu.options | 0x10000);
    window->controllerMask = controller_mask;
    var_v1 = ~controller_mask;
    if (controller_count == 2) {
        var_v1 |= 0xE;
    }
    if (var_v1 & 2) {
        window->sideMenu.itemFlags[1] |= 1;
    }
    if (var_v1 & 4) {
        window->sideMenu.itemFlags[2] |= 1;
    }
    if (var_v1 & 8) {
        window->sideMenu.itemFlags[3] |= 1;
    }
    FreeBattle_DisableAbsentTagOpponents(window);
    window->unk_C4 = gb_save_ready_mask;
    window->focus = 1;
}


/**
 * Draws the tag opponent window: the side menu, the opponent menu and the controller panel with
 * the picked players marked.
 * Not reached in play: FreeBattle_DrawScreen draws it for screen state 6, which
 * FreeBattle_SetScreenState never sets.
 * @unverified Name from the code.
 */
void FreeBattle_DrawTagOpponentSelect(FreeBattleTeamOpponentWindow* window) {
    s32 mask_b = 0xFED, mask_a = 0xFED;
    s32 pad[1]; // FAKE: stack padding
    s32 mark_a = 0;
    s32 mark_b = 0;

    if (func_8002AE6C(&window->window) == 0) {
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + 146, window->window.frame.width, &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(window->window.frame.x + 6, window->window.frame.y + 153, window->window.frame.width - 12, 196, *(Color82001CCC*)&D_82009100);
        Ui_DrawImageInStrips(D_8200910C, window->window.frame.x + 169, window->window.frame.y + 249);
        if (window->focus != 0) {
            if (window->focus == 1) {
                mask_b = 0xFEF;
            }
        } else {
            mask_b = 0xFFD;
            mask_a = 0xFEF;
        }
        Menu_DrawItems(&window->sideMenu, window->window.frame.x + 34, window->window.frame.y + 209, mask_b, NULL);
        Menu_DrawItems(&window->opponentMenu, window->window.frame.x + 252, window->window.frame.y + 153, mask_a, NULL);
        switch ((u32)window->sideMenu.cursor) {
            case 0:
                mark_a = 1;
                break;
            case 1:
                mark_a = 3;
                break;
            case 2:
                mark_a = 5;
                break;
            case 3:
                mark_a = 9;
                break;
        }
        if (window->focus == 0) {
            switch ((u32)window->opponentMenu.cursor) {
                case 0:
                    mark_b = 2;
                    break;
                case 1:
                    mark_b = 4;
                    break;
                case 2:
                    mark_b = 8;
                    break;
                case 3:
                    mark_b = 6;
                    break;
                case 4:
                    mark_b = 0xA;
                    break;
                case 5:
                    mark_b = 0xC;
                    break;
            }
        }
        FreeBattle_DrawControllerPanel(window->window.frame.x + 6, window->window.frame.y + 6, window->controllerMask, window->unk_C4, mark_a, mark_b);
    }
}

void Menu_ClearItemFlags(u8*, void*);
// The seven result cases were one macro in the original: IDO only schedules
// these three stores the way the ROM does when they share a source line.
#define SET_PAIR_82007030(owner, first, second, count) \
    (owner)->players[2] = (first); (owner)->players[3] = (second); (owner)->playerCount += (count)

/**
 * Input of the tag opponent window: A on the side menu fills players[0..1] and moves to the
 * opponent menu, A there fills players[2..3]; returns 1 when both sides are picked, -1 on B.
 * Not reached in play: nothing calls it (no screen state updates the tag opponent window).
 * @unverified Name from the code.
 */
s32 FreeBattle_UpdateTagOpponentSelect(FreeBattleTeamOpponentWindow* window) {
    s32 result = 0;
    u32 res;

    if (((u32)window->window.state != 1) && ((u32)window->window.state != 2)) { // the ROM compares these unsigned
        return 0;
    }
    switch (window->focus) {
        case 1:
            if (Menu_UpdateCursorSkipDisabled((u8*)&window->sideMenu, window) == 0) {
                res = Ui_GetSelectionDirection(D_800603C0);
                if (res == -1) {
                    Audio_PlaySystemSound(3);
                    result = -1;
                } else if (res == 1) {
                    Audio_PlaySystemSound(2);
                    window->focus = 0;
                    switch ((u32)window->sideMenu.cursor) {
                        case 0:
                            window->players[0] = 1;
                            window->players[1] = 0;
                            window->playerCount = 1;
                            break;
                        case 1:
                            window->players[0] = 1;
                            window->players[1] = 2;
                            window->playerCount = 2;
                            window->opponentMenu.itemFlags[0] |= 1;
                            window->opponentMenu.itemFlags[3] |= 1;
                            window->opponentMenu.itemFlags[4] |= 1;
                            window->opponentMenu.itemFlags[6] |= 1;
                            break;
                        case 2:
                            window->players[0] = 1;
                            window->players[1] = 3;
                            window->playerCount = 2;
                            window->opponentMenu.itemFlags[1] |= 1;
                            window->opponentMenu.itemFlags[3] |= 1;
                            window->opponentMenu.itemFlags[5] |= 1;
                            window->opponentMenu.itemFlags[6] |= 1;
                            break;
                        case 3:
                            window->players[0] = 1;
                            window->players[1] = 4;
                            window->playerCount = 2;
                            window->opponentMenu.itemFlags[2] |= 1;
                            window->opponentMenu.itemFlags[4] |= 1;
                            window->opponentMenu.itemFlags[5] |= 1;
                            window->opponentMenu.itemFlags[6] |= 1;
                            break;
                    }
                    window->opponentMenu.cursor = 0;
                    Menu_SkipDisabledForward((s8*)&window->opponentMenu, (s32)window);
                }
            }
            break;
        case 0:
        if (Menu_UpdateCursorSkipDisabled((u8*)&window->opponentMenu, window) == 0) {
            res = Ui_GetSelectionDirection(D_800603C0);
            if (res == -1) {
                Audio_PlaySystemSound(3);
                window->focus = 1;
                Menu_ClearItemFlags((u8*)&window->opponentMenu, window);
                FreeBattle_DisableAbsentTagOpponents(window);
            } else if (res == 1) {
                Audio_PlaySystemSound(2);
                switch ((u32)window->opponentMenu.cursor) {
                    case 0:
                        SET_PAIR_82007030(window, 2, 0, 1);
                        break;
                    case 1:
                        SET_PAIR_82007030(window, 3, 0, 1);
                        break;
                    case 2:
                        SET_PAIR_82007030(window, 4, 0, 1);
                        break;
                    case 3:
                        SET_PAIR_82007030(window, 2, 3, 2);
                        break;
                    case 4:
                        SET_PAIR_82007030(window, 2, 4, 2);
                        break;
                    case 5:
                        SET_PAIR_82007030(window, 3, 4, 2);
                        break;
                    case 6:
                        SET_PAIR_82007030(window, 5, 0, 1);
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
void FreeBattle_DrawBattleModeCard(s32 x, s32 y, s32* mode, s32 index, s32 flags) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    Box82007398 sp24;

    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 178, 194, D_82009100);
    }
    sp24.unk_08 = sp24.unk_04 = sp24.unk_00 = 0x98;
    sp24.unk_0C = mode[2];
    Ui_DrawImageInStrips((void*)&sp24, x + 0x10, y + 8);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 22, y + 170, (char*)mode[0]);
    Font_EndTexturedTextRendering();
}

/*
 * FreeBattle_InitBattleModeWindow
 *
 * Initializes the FreeBattleModeWindow arg0: calls
 * Window_SetRect(arg0, arg1, arg2, 400, 302), clears the words at 0x24
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
void FreeBattle_InitBattleModeWindow(FreeBattleModeWindow* window, s32 x, s32 y, s32 modes, s32 title) {
    Window_SetRect(window, x, y, 400, 302);
    window->window.animTimer = 0;
    window->window.state = 0;
    window->window.frame.style = 0x801;
    window->window.title = title;
    func_80027410(&window->items, modes, 0xC, 2, 2);
    GridMenu_Init(&window->menu, &window->items, &window->itemFlags, (M2C_UNK*)FreeBattle_DrawBattleModeCard, 2, 184, 200);
    window->menu.options = (s32)(window->menu.options | 0x10000);
    window->modes = modes;
}


extern Color_RGBA8 D_820091BC;
extern Color_RGBA8 D_820091C0;
M2C_UNK GridMenu_DrawInlineItems(s8*, s32, s32, s32, s32);

/**
 * Draws the FreeBattleModeWindow window (window.frame.x at +0, y at +4, width at +8)
 * while func_8002AE6C() is zero: a box via Ui_DrawTexturedFrameDecal (D_800735C4), the frame via
 * Ui_DrawTexturedDivider, a filled bar via func_80029028 (color D_82009100, height 0xDC), a second
 * panel via Ui_FillRectPrimEnvColor (colors D_820091BC / D_820091C0), the sub-object at +0x2C via
 * GridMenu_DrawInlineItems, and the text pointer stored at index [+0x34] of the table of 12-byte
 * records pointed to by the word at +0x68 (the pointer is the second word of a record),
 * printed in the color from D_800734A8 via Font_Printf.
 * What the constants mean is not established.
 * Matching note: Ui_DrawTexturedDivider must be declared void (see FreeBattle_DrawOpponentSelect).
 * Seen in play: draws the 「バトルモード」 window (フリーバトル / トーナメント pictures and the description below)
 * every frame.
 */
void FreeBattle_DrawBattleModeWindow(FreeBattleModeWindow* window) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedFrameDecal(window->window.frame.x + 14, window->window.frame.y + 14, 372, 204, D_800735C4);
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + 225, window->window.frame.width, &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(window->window.frame.x + 6, window->window.frame.y + 6, window->window.frame.width - 12, 220, *(Color82001CCC*)&D_82009100);
        Ui_FillRectPrimEnvColor(window->window.frame.x + 6, window->window.frame.y + 232, window->window.frame.width - 12, 0x40, D_820091BC, D_820091C0);
        GridMenu_DrawInlineItems(&window->menu, window->window.frame.x + 0x10, window->window.frame.y + 0x10, 0xFFEF, 0);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(28);
        Font_Printf(window->window.frame.x + 20, window->window.frame.y + 236, ((FreeBattleModeEntry*)window->modes)[window->menu.cursor].text);
        Font_EndTexturedTextRendering();
    }
}

extern s32 D_800603C0;

/**
 * FreeBattle_UpdateBattleModeWindow
 *
 * Returns 0 immediately unless the word at window + 0x28 is 1 or 2. Otherwise,
 * if GridMenu_UpdateCursor(window + 0x2C, window) returns 0, it reads Ui_GetSelectionDirection(D_800603C0):
 * -1 calls Audio_PlaySystemSound(3) and returns -1; 1 calls Audio_PlaySystemSound(2) and
 * returns the word at window + 0x34 plus 1; any other value returns 0.
 * (FreeBattle_UpdatePopupMenu is the same pattern without the mode check.)
 * Seen in play: runs while the バトルモード window is up; D-Right moves the highlight to トーナメント and
 * changes the description.
 */
s32 FreeBattle_UpdateBattleModeWindow(FreeBattleModeWindow* window) {
    s32 result = 0;
    s32 tmp;

    tmp = window->window.state;
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (GridMenu_UpdateCursor(&window->menu, window) == 0) {
        tmp = Ui_GetSelectionDirection(D_800603C0);
        if (tmp == -1) {
            Audio_PlaySystemSound(3);
            result = -1;
        } else if (tmp == 1) {
            Audio_PlaySystemSound(2);
            result = window->menu.cursor + 1;
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
void Ui_SetTextColorForFlags(s32);
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);

/**
 * Draws one row of 「カップせんたく」: highlight box when selected (flag 0x10), a cleared-cup icon at the
 * right when flag 0x100 is set, and the cup name dimmed when locked.
 * Seen in play: draws モンスターボールカップ (boxed) and the grayed スーパーボール, ハイパーボール and マスターボールカップ.
 * Seen in play (2026-11-13) drew the rows of 「カップせんたく」 for the L1～30 tournament (モンスターボールカップ, then
 * the grayed スーパー, ハイパー and マスターボール cups).
 */
void FreeBattle_DrawCupRow(s32 x, s32 y, IconPanel* cup, s32 index, s32 flags) {
    UNUSED s32 pad[5]; // FAKE: stack padding
    s32 sp28;

    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 330, 30, D_82009100);
    }
    if (flags & 0x100) {
        gSPDisplayList(gDisplayListHead++, D_80060290);
        Gfx_DrawTextureRgba16(x + 300, y + 6, 24, 24, cup->icon, 24, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
    sp28 = y + 6;
    Font_BeginTranslucentTextRendering();
    Ui_SetTextColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 12, sp28, cup->text);
    Font_EndTexturedTextRendering();
}

extern u8 D_8200A040[];
extern u8 D_820091C4[];
/**
 * Sets up the カップせんたく (choose cup) window with up to four cups.
 * Seen in play: トーナメントにでる opens 「カップせんたく」 (モンスターボールカップ, スーパーボールカップ, ハイパーボールカップ, マスターボールカップ) and
 * runs this.
 */
void FreeBattle_InitCupSelect(FreeBattleCupWindow* window, s32 x, s32 y, s32 cups_cleared) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 n;
    s32 i;

    if (cups_cleared >= 4) {
        n = 4;
    } else {
        n = cups_cleared + 1;
    }
    Window_SetRect(window, x, y, 348, 168);
    window->window.animTimer = 0;
    window->window.title = NULL;
    window->window.state = 0;
    window->window.frame.style = 0x800;
    window->window.frame.color = D_82009100;
    window->window.title = D_8200A040;
    func_80027410(&window->items, (s32)D_820091C4, 8, 4, 4);
    Menu_Init(&window->menu, &window->items, &window->itemFlags, (void (*)(s32, s32, char*, s32, s32, s32*))FreeBattle_DrawCupRow, 336, 36);
    window->menu.options |= 0x10000;
    window->menu.cursor = n - 1;
    for (i = 0; i < cups_cleared; i++) {
        window->menu.itemFlags[i] |= 0x100;
    }
    for (i = n; i < 4; i++) {
        window->menu.itemFlags[i] |= 1;
    }
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawInlineItems(s8 *, s32, s32, s32, s32);  /* extern */

/**
 * Draws the choose cup window.
 * Seen in play: draws the 「カップせんたく」 window; only モンスターボールカップ is open on a new save.
 */
void FreeBattle_DrawCupSelect(FreeBattleCupWindow* window, s32 flags) {
    if (func_8002AE6C() == 0) {
        Menu_DrawInlineItems(&window->menu, window->window.frame.x + 6, window->window.frame.y + 0xC, flags | 0xFFED, 0);
    }
}

/**
 * Variant of FreeBattle_UpdateBattleModeWindow with an extra check. Returns 0 immediately unless the
 * word at window + 0x28 is 1 or 2. Otherwise, if Menu_UpdateCursorSkipDisabled(window + 0x2C, window)
 * returns 0, it reads Ui_GetSelectionDirection(D_800603C0): -1 calls Audio_PlaySystemSound(3) and
 * returns -1; 1 looks at bit 0 of the u16 at index window->unk_34 of the array
 * pointed to by the word at window + 0x30. If that bit is clear it calls
 * Audio_PlaySystemSound(2) and returns unk_34 + 1; if it is set it calls
 * Audio_PlaySystemSound(8) and returns 0. Any other value returns 0.
 * Seen in play: runs while 「カップせんたく」 is open.
 */
s32 FreeBattle_UpdateCupSelect(FreeBattleCupWindow* window) {
    s32 result = 0;
    s32 tmp;

    tmp = window->window.state;
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (Menu_UpdateCursorSkipDisabled((u8*)&window->menu, window) == 0) {
        tmp = Ui_GetSelectionDirection(D_800603C0);
        if (tmp == -1) {
            Audio_PlaySystemSound(3);
            result = -1;
        } else if (tmp == 1) {
            if (!(window->menu.itemFlags[window->menu.cursor] & 1)) {
                Audio_PlaySystemSound(2);
                result = window->menu.cursor + 1;
            } else {
                Audio_PlaySystemSound(8);
            }
        }
    }
    return result;
}

extern Color_RGBA8 D_820091E4[2];
extern FreeBattleMonGridConfig D_820091EC[2];

/**
 * Sets up the 7x6 grid of the Pokémon a rule allows, 「たいせんでつかえるポケモンは４０ぴき」 (40 Pokémon
 * can battle) or 「…３３びき」 for L1-30: picks config 1 (`ruleCategory` 2, L1-30, list `l130Mons`)
 * or config 0 (`allMons`), sets the window's title and rows, and registers each Pokémon's icon in
 * `icons` with a checkered cell color from D_820091E4.
 * Seen in play (2026-11-14): ran with ruleCategory 0 when 4) エントリーできるポケモン ４０しゅるい was
 * picked on the フリーバトル rules (40 Pokémon shown) and with 2 on the L1-30 rules (33 shown).
 */
void FreeBattle_InitUsableMonGrid(FreeBattleMonGridWindow* window, s32 x, s32 y, s32 rule_category, s32 all_mons, s32 l130_mons, s8* icons) {
    FreeBattleMonGridConfig* cfg;
    u8* entry;
    s32 sel;
    s32 i;
    s32 size;
    Color_RGBA8 color;

    if (rule_category == 2) {
        sel = 1;
    } else {
        sel = 0;
    }
    D_820091EC[0].mons = all_mons;
    D_820091EC[1].mons = l130_mons;
    Window_SetRect(window, x, y, 565, 372);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 0x801;
    cfg = &D_820091EC[sel];
    window->window.title = cfg->title;
    size = cfg->count;
    func_80027410(&window->mons, cfg->mons, sizeof(BattleMon), size, size);
    PokeIcon_ResetSlots(icons);
    entry = window->mons.rows;
    window->icons = icons;
    for (i = 0; i < window->mons.count; i++) {
        color = D_820091E4[i & 1];
        PokeIcon_SetSpeciesSlot(window->icons, i, *entry,
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

/**
 * Draws the usable Pokémon grid: 42 checkered cells, then each Pokémon's name and icon.
 * Seen in play (2026-11-14): drew the 40 (Free Battle) and 33 (L1-30) Pokémon grids.
 */
void FreeBattle_DrawUsableMonGrid(FreeBattleMonGridWindow* window, s32 flags) {
    s32 i;
    s32 x;
    s32 y;
    s32 x0 = window->window.frame.x + 6;
    s32 y0 = window->window.frame.y + 6;
    s8* entry;

    if (func_8002AE6C() == 0) {
        for (i = 0; i < 42; i++) {
            gSPDisplayList(gDisplayListHead++, D_80060270);
            func_80029028((i % 7) * 79 + x0, (i / 7) * 60 + y0, 79, 60, D_82009204[i & 1]);
        }
        func_800189C0(window->icons, 0);
        BgStage_DrawFrame();
        entry = window->mons.rows;
        for (i = 0; i < window->mons.count; i++) {
            Font_BeginTranslucentTextRendering();
            Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
            Font_SetActive(4, -1);
            x = (i % 7) * 79 + x0;
            y = (i / 7) * 60 + y0;
            Font_Printf(x + 2, y + 42, entry + 0x30);
            Font_EndTexturedTextRendering();
            gSPDisplayList(gDisplayListHead++, D_80073408);
            Gfx_DrawTextureRgba16(x + 38, y + 2, 40, 40, PokeIcon_GetImage(window->icons, i), 40, 0x200000);
            gSPDisplayList(gDisplayListHead++, D_80073438);
            entry += 0x50;
        }
    }
}

extern s32 D_800603C0;

/**
 * Input of the usable Pokémon grid: A or B closes it (returns -1); otherwise 0.
 * Seen in play (2026-11-14): ran while the grid was shown; B went back to the rules list.
 */
s32 FreeBattle_UpdateUsableMonGrid(FreeBattleMonGridWindow* window) {
    s32 result = 0;
    s32 tmp;

    tmp = window->window.state;
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    tmp = Ui_GetSelectionDirection(D_800603C0);
    if ((tmp == -1) || (tmp == 1)) {
        Audio_PlaySystemSound(3);
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
 * Seen in play (2026-11-14): opened 「ちゅうい！！ おなじポケモンが ２たいいます」 when a rental team in
 * L1～30 Battle held two スピアー (one poked in RAM).
 */
void FreeBattle_InitDuplicateWarning(FreeBattleDuplicateWarning* window, s32 x, s32 y, s32 duplicates) {
    Window_SetRect(window, x, y, 328, 104);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 0x2806;
    window->window.frame.color = D_8200920C;
    window->window.frame.color2 = D_82009210;
    window->window.title = D_8200A0A0;
    window->value = duplicates;
}

void Font_BeginTranslucentTextRendering(void);
void Gfx_SetEnvColor(u8, u8, u8, u8);
void Font_SetActive(s32, s32);
void Font_SetLineHeight(s32 arg0);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void Font_EndTexturedTextRendering(void);
extern u8 D_800734A8[];
extern char D_8200A0B0[];

/**
 * Draws おなじポケモンが %dたいいます (there are %d of the same Pokemon).
 * Seen in play (2026-11-14): drew 「おなじポケモンが ２たいいます しゅつじょうするポケモンを １たい
 * えらんでください」 (two of the same Pokémon; pick one to send out).
 */
void FreeBattle_DrawDuplicateWarning(FreeBattleDuplicateWarning* window) {
    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(28);
        Font_Printf(window->window.frame.x + 14, window->window.frame.y + 14, D_8200A0B0, window->value);
        Font_EndTexturedTextRendering();
    }
}

void Window_InitLabeled(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);
extern Color_RGBA8 D_82009218;
extern char D_8200A104[];
extern char D_8200A114[];
extern char D_8200A11C[];

/**
 * Initializes the FreeBattleShortageWarning window; the same
 * setup as FreeBattle_InitLevelSumWarning with different strings (D_8200A104, D_8200A114 and
 * D_8200A11C) and color (D_82009218), and one more argument. Calls
 * Window_SetRect(window, x, y, 308, 146), clears the words at 0x24 and
 * 0x28, sets the word at 0x14 to 0x2801 and the pointer at 0x20 to D_8200A104.
 * Calls Window_InitLabeled on the sub-objects at window + 0x2C and window + 0x68, sets
 * the words at 0x58, 0x60, 0xAC and 0xA8 to 0xA, 0xC, 2 and 0, stores
 * D_800603C0 and then controller in the word at 0xA4 (calling func_8000B2F4 with
 * each), and finally stores controller at 0xB4 and count at 0xB0.
 * What the object is and what the constants mean is not established.
 * Seen in play (2026-11-13) in the L1～30 tournament (モンスターボールカップ) entry, A on the GB party of three
 * opened 「ちゅうい!! つかえるポケモンが 6たい たりません」 with はい/いいえ, and this ran once as it appeared.
 */
void FreeBattle_InitShortageWarning(FreeBattleShortageWarning* window, s32 x, s32 y, s32 controller, s32 count) {
    Window_SetRect(window, x, y, 308, 146);
    window->window.animTimer = 0;
    window->window.state = 0;
    window->window.frame.style = 0x2801;
    window->window.title = D_8200A104;
    Window_InitLabeled(&window->yesButton, window->window.frame.x + 46, window->window.frame.y + 110, 72, D_82009218, D_8200A114);
    window->yesButton.labelX = 10;
    window->yesButton.unk_34 = 12;
    Window_InitLabeled(&window->noButton, window->window.frame.x + 190, window->window.frame.y + 110, 72, D_82009218, D_8200A11C);
    window->choice.count = 2;
    window->choice.cursor = 0;
    window->choice.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    window->choice.controller = controller;
    func_8000B2F4(controller);
    window->controller = controller;
    window->count = count;
}

extern Color_RGBA8 D_8200921C;
extern Color_RGBA8 D_82009220;
extern char D_8200A124[];

/**
 * Draws the FreeBattleShortageWarning window: the same drawing code as
 * FreeBattle_DrawLevelSumWarning with different colors (D_8200921C / D_82009220) and text
 * (D_8200A124), which is printed with the word at +0xB0 passed twice as extra
 * arguments to Font_Printf. See FreeBattle_DrawLevelSumWarning for the sequence of calls; the
 * selection index at +0xA8 again decides which of the two sub-objects (+0x2C,
 * +0x68) gets 2 from Window_DrawLabeled and which gets 0.
 * What the constants mean is not established.
 * Seen in play (2026-11-13) drew the 「ちゅうい!! つかえるポケモンが 6たい たりません」 warning on the tournament entry
 * screen every frame while it was up.
 */
void FreeBattle_DrawShortageWarning(FreeBattleShortageWarning* window) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + 97, window->window.frame.width, &D_8007356C);
        Ui_FillRectPrimEnvColor(window->window.frame.x + 6, window->window.frame.y + 6, 296, 92, D_8200921C, D_82009220);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(window->window.frame.x + 6, window->window.frame.y + 104, window->window.frame.width - 12, 36, *(Color82001CCC*)&D_82009100);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(28);
        Font_Printf(window->window.frame.x + 14, window->window.frame.y + 14, D_8200A124, window->count, window->count);
        Font_EndTexturedTextRendering();
        Window_DrawLabeled(&window->yesButton, (window->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&window->noButton, (window->choice.cursor == 1) ? 2 : 0);
    }
}

s32 Ui_HandleHorizontalSelectionInput(s32);
s32 Ui_GetSelectionDirection(s32);
M2C_UNK Audio_PlaySystemSound(M2C_UNK);

/**
 * Handles the too few usable Pokemon warning.
 * Seen in play (2026-11-13) ran every frame while the tournament entry screen's 「つかえるポケモンが 6たい
 * たりません」 warning waited for はい/いいえ.
 */
s32 FreeBattle_UpdateShortageWarning(FreeBattleShortageWarning* window) {
    s32 ret = 0;
    s32 temp_v0;

    if (Ui_HandleHorizontalSelectionInput(&window->choice) == 0) {
        temp_v0 = Ui_GetSelectionDirection(window->controller);
        if (temp_v0 == -1) {
            Audio_PlaySystemSound(3);
            ret = -1;
        } else if (temp_v0 == 1) {
            switch (window->choice.cursor) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    Audio_PlaySystemSound(3);
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
 * Initializes the FreeBattleLevelSumWarning window: calls
 * Window_SetRect(window, x, y, 308, 146), clears the words at 0x24 and
 * 0x28, sets the word at 0x14 to 0x2801 and the pointer at 0x20 to
 * D_8200A178. Calls Window_InitLabeled twice, on the sub-objects at window + 0x2C
 * (string D_8200A188) and window + 0x68 (string D_8200A190), both with width
 * 0x48 and color D_82009228 and positions derived from the words at 0 and 4.
 * Then sets the words at 0x58, 0x60, 0xAC and 0xA8 to 0xA, 0xC, 2 and 0, and
 * stores D_800603C0 and then controller in the word at 0xA4, calling func_8000B2F4
 * with each value in turn. Finally stores controller at 0xB0.
 * What the object is and what the constants mean is not established.
 * Seen in play (2026-11-14): opened the 155 level-sum warning in L50～55 Battle (はい / いいえ under
 * 「レンタルポケモンからえらぶ？」).
 */
void FreeBattle_InitLevelSumWarning(FreeBattleLevelSumWarning* window, s32 x, s32 y, s32 controller) {
    Window_SetRect(window, x, y, 308, 146);
    window->window.animTimer = 0;
    window->window.state = 0;
    window->window.frame.style = 0x2801;
    window->window.title = D_8200A178;
    Window_InitLabeled(&window->yesButton, window->window.frame.x + 46, window->window.frame.y + 110, 72, D_82009228, D_8200A188);
    window->yesButton.labelX = 10;
    window->yesButton.unk_34 = 12;
    Window_InitLabeled(&window->noButton, window->window.frame.x + 190, window->window.frame.y + 110, 72, D_82009228, D_8200A190);
    window->choice.count = 2;
    window->choice.cursor = 0;
    window->choice.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    window->choice.controller = controller;
    func_8000B2F4(controller);
    window->controller = controller;
}

extern Color_RGBA8 D_8200922C;
extern Color_RGBA8 D_82009230;
extern char D_8200A198[];

/**
 * Draws the FreeBattleLevelSumWarning window ( the same kind of object that
 * FreeBattle_InitLevelSumWarning / FreeBattle_InitRentalConfirm initialize: x at +0, y at +4, width at +8, a
 * selection index at +0xA8 and two sub-objects at +0x2C and +0x68). Does nothing
 * while func_8002AE6C() is non-zero. Otherwise it draws the frame with
 * Ui_DrawTexturedDivider and Ui_FillRectPrimEnvColor, emits D_80060270 and fills a bar with
 * func_80029028 (color D_82009100), then prints the string D_8200A198 with the
 * font color from D_800734A8 via Font_Printf, and finally calls Window_DrawLabeled
 * on the two sub-objects with 2 for the one whose index (0 for +0x2C, 1 for +0x68)
 * equals the selection at +0xA8 and 0 for the other.
 * What the constants mean is not established.
 * Seen in play (2026-11-14): drew the 155 level-sum warning with its はい / いいえ buttons.
 */
void FreeBattle_DrawLevelSumWarning(FreeBattleLevelSumWarning* window) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + 97, window->window.frame.width, &D_8007356C);
        Ui_FillRectPrimEnvColor(window->window.frame.x + 6, window->window.frame.y + 6, 296, 92, D_8200922C, D_82009230);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(window->window.frame.x + 6, window->window.frame.y + 104, window->window.frame.width - 12, 36, *(Color82001CCC*)&D_82009100);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(28);
        Font_Printf(window->window.frame.x + 14, window->window.frame.y + 14, D_8200A198);
        Font_EndTexturedTextRendering();
        Window_DrawLabeled(&window->yesButton, (window->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&window->noButton, (window->choice.cursor == 1) ? 2 : 0);
    }
}

s32 Ui_HandleHorizontalSelectionInput(s32);
s32 Ui_GetSelectionDirection(s32);
M2C_UNK Audio_PlaySystemSound(M2C_UNK);

/**
 * Handles the level sum warning.
 * Seen in play (2026-11-14): ran while the 155 level-sum warning was open.
 */
s32 FreeBattle_UpdateLevelSumWarning(FreeBattleLevelSumWarning* window) {
    s32 ret = 0;
    s32 temp_v0;

    if (Ui_HandleHorizontalSelectionInput(&window->choice) == 0) {
        temp_v0 = Ui_GetSelectionDirection(window->controller);
        if (temp_v0 == -1) {
            Audio_PlaySystemSound(3);
            ret = -1;
        } else if (temp_v0 == 1) {
            switch (window->choice.cursor) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    Audio_PlaySystemSound(3);
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
 * Initializes the FreeBattleRentalConfirm window; a sibling of
 * FreeBattle_InitConfirmWindow. Calls Window_SetRect(window, x, y, 396, 102), clears the words at
 * 0x20, 0x24 and 0x28 and sets the word at 0x14 to 0x1001. Calls Window_InitLabeled three times,
 * on the sub-objects at window + 0x2C (string D_8200A1EC), + 0x68 (D_8200A1F4) and + 0xA4
 * (D_8200A1FC, width 0x5C; the other two use width 0x48), all with color D_82009234 and
 * positions derived from the words at 0 and 4; the words at 0x58 and 0x60 are set to 0xA
 * and 0xC between the first two calls. Then clears the word at 0xE4, stores hasThirdButton at 0xEC
 * and 3 (hasThirdButton != 0) or 2 (hasThirdButton == 0) at 0xE8, and stores D_800603C0 and then controller in the
 * word at 0xE0 (calling func_8000B2F4 with each).
 * What the object is and what the constants mean is not established.
 * Seen in play: A on a team opens 「このデータでエントリーします。 はい いいえ」 and runs this.
 */
void FreeBattle_InitRentalConfirm(FreeBattleRentalConfirm* window, s32 x, s32 y, s32 has_third_button, s32 controller) {
    Window_SetRect(window, x, y, 396, 102);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 0x1001;
    Window_InitLabeled(&window->buttons[0], window->window.frame.x + 118, window->window.frame.y + 66, 72, D_82009234, D_8200A1EC);
    window->buttons[0].labelX = 0xA;
    window->buttons[0].unk_34 = 0xC;
    Window_InitLabeled(&window->buttons[1], window->window.frame.x + 198, window->window.frame.y + 66, 72, D_82009234, D_8200A1F4);
    Window_InitLabeled(&window->buttons[2], window->window.frame.x + 290, window->window.frame.y + 66, 92, D_82009234, D_8200A1FC);
    window->choice.cursor = 0;
    window->hasThirdButton = has_third_button;
    if (has_third_button != 0) {
        window->choice.count = 3;
    } else {
        window->choice.count = 2;
    }
    window->choice.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    window->choice.controller = controller;
    func_8000B2F4(controller);
}

extern Color_RGBA8 D_82009238;
extern Color_RGBA8 D_8200923C;
extern char D_8200A208[];

/**
 * Draws the FreeBattleRentalConfirm window: a variant of FreeBattle_DrawLevelSumWarning /
 * FreeBattle_DrawShortageWarning with a shorter frame (height 0x30) and colors D_82009238 /
 * D_8200923C, text D_8200A208 in a larger font size (0x10), and a selection index
 * at +0xE4 (rather than +0xA8) that decides which of the sub-objects at +0x2C, +0x68
 * and, only when the word at +0xEC is non-zero, +0xA4 is passed 2 by Window_DrawLabeled
 * (index 0, 1 or 2 respectively); the others get 0.
 * What the constants mean is not established.
 * Seen in play: draws 「このデータでエントリーします。」 with はい / いいえ.
 */
void FreeBattle_DrawEntryConfirm(FreeBattleRentalConfirm* window) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + 53, window->window.frame.width, &D_8007356C);
        Ui_FillRectPrimEnvColor(window->window.frame.x + 6, window->window.frame.y + 6, window->window.frame.width - 12, 48, D_82009238, D_8200923C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(window->window.frame.x + 6, window->window.frame.y + 60, window->window.frame.width - 12, 36, *(Color82001CCC*)&D_82009100);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(0x10, 0);
        Font_Printf(window->window.frame.x + 18, window->window.frame.y + 18, D_8200A208);
        Font_EndTexturedTextRendering();
        Window_DrawLabeled(&window->buttons[0], (window->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&window->buttons[1], (window->choice.cursor == 1) ? 2 : 0);
        if (window->hasThirdButton != 0) {
            Window_DrawLabeled(&window->buttons[2], (window->choice.cursor == 2) ? 2 : 0);
        }
    }
}

s32 Ui_HandleHorizontalSelectionInput(s32);                             /* extern */
s32 Ui_GetSelectionDirection(s32);                             /* extern */
M2C_UNK Audio_PlaySystemSound(M2C_UNK);                     /* extern */

/**
 * Handles the rental confirm window.
 * Seen in play: runs while 「このデータでエントリーします。」 is open; はい enters the team.
 */
s32 FreeBattle_UpdateRentalConfirm(FreeBattleRentalConfirm* window) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;

    var_s0 = 0;
    if (Ui_HandleHorizontalSelectionInput(&window->choice) == 0) {
        temp_v0 = Ui_GetSelectionDirection(window->choice.controller);
        if (temp_v0 == -1) {
            Audio_PlaySystemSound(3);
            var_s0 = -1;
        } else if (temp_v0 == 1) {
            temp_v0_2 = window->choice.cursor;
            switch (temp_v0_2) {                    /* irregular */
            case 0:
                var_s0 = 1;
                break;
            case 2:
                var_s0 = 2;
                break;
            case 1:
                var_s0 = -1;
                Audio_PlaySystemSound(3);
                break;
            }
        }
    }
    return var_s0;
}
