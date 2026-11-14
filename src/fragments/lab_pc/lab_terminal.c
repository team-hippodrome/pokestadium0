/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "lab_pc.h"
#include "asset_archive.h"
#include "font.h"
#include "graphics_textures.h"
#include "input.h"
#include "memory_main.h"
extern s32 pad_D_8831A4DC[8];
#include "m2c_macros.h"
void ScrollList_SetItems(s8*, s32, s8*);
void func_8900020C(void);
s32 LabItem_ComputeRemainingCapacity(s32 arg0, ByteMatrix* arg1);
s32 LabItem_ComputeMaxTransferQuantity(s32 arg0, ByteMatrix* arg1);
s32 LabItem_FindOrAllocateGamePakBoxSlot(LabItemSaveSlot* arg0, s32 arg1, char* arg2);
void LabItem_LoadGamePakBoxSlots(LabItemSaveSlot* arg0);
void LabItem_ReadDeckEntries(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3);
void func_800275E4(s32, s32);
void ScrollList_SetCursorKeepOffset(s32*, s32);
void func_800275E4(s32, s32);
int func_800274E0();
void ScrollList_SetCursorKeepOffset(s32*, s32);
extern M2C_UNK D_8900A5B8;
void Window_SetRect(s8*, s32, s32, s32, s32);
void Window_InitLabeled(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);
extern Color_RGBA8 D_8900A5C0;
extern char D_89018460[];
extern char D_89018468[];
extern s32 D_800603C0;
M2C_UNK func_8001A944(s32, s32, ...);
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Window_DrawLabeled(s8*, s32);
extern u8 D_8007356C[];
extern u8 D_800734A8[];
extern Gfx D_80060270[];
extern Color_RGBA8 D_8900A5C4;
extern Color_RGBA8 D_8900A5C8;
extern Color_RGBA8 D_8900A5CC;
s32 func_8002B390(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;
extern Color_RGBA8 D_8900A5BC;
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_8001AA60(s32, s32, s32);
void Font_SetColorForFlags(s32);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
void TextBox_Draw(s8*);
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern Color_RGBA8 D_80073520;
extern u8 D_04002130[];
extern u8 D_04002238[];
extern u8 D_04002340[];
extern u8 D_04002448[];
extern char D_89018470[];
extern s32 D_800603C0;
extern M2C_UNK D_89018474;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
extern Color_RGBA8 D_8900A5D4[];
extern u8 D_800734A8[];
void Window_SetRect(s8*, s32, s32, s32, s32);
void Menu_Init(s8*, s32, s32, s32, s32, s32);
M2C_UNK func_80027804();
s32 Menu_UpdateCursorSkipDisabled(void*);
extern Gfx D_80060270[];
extern Color_RGBA8 D_8900A5E0;
extern Color_RGBA8 D_8900A5E8;
extern Color_RGBA8 D_8900A5EC[];
extern char D_8901848C[];
char* func_8001FDC8(u8, char*);
s32 func_80031C24(u8);
s32 func_80031CC8(u8);
void Font_SetColorForFlags(s32);
void ScrollList_Init(s8*, s32, s8*, s32, void*, s32, s32);
void LabItem_DrawItemCountRow();
void func_8002F9D8(void *, s32, s32, s32, s32);
void ScrollList_DrawInlineItems(void *, s32, s32, s32, s32);
void Ui_DrawNumberZeroPadded(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void *, s32, s32);
extern Gfx D_80073450[];
extern u8 D_04011AB8[];
s32 ScrollList_UpdateCursor(void*);
s32 func_80030230(void*);
extern PrimEnvColor D_8900A608;
extern PrimEnvColor D_8900A610;
extern u8* D_89017A80[];
extern u8 D_89017A98[];
extern s32 D_89019114;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);
void Font_SetColorForFlags(s32);
s32 func_8002BC44(s32);
M2C_UNK func_8001A944(s32, s32, ...);
extern u8 D_800734A8[];
M2C_UNK func_8001A944(s32, s32, ...);
extern u8 D_800734A8[];
extern s32 D_8900A650[];
extern char* D_8900A660[];
extern char* D_8900A66C[];
extern s8* D_8900A678[];
s32 func_80031BC0(u8, char *);
typedef struct LabItemGridZ {
    /* 0x00 */ u8* data;
    /* 0x04 */ s32 pad04[2];
    /* 0x0C */ s32 stride;
} LabItemGridZ;
typedef struct LabItemCursorZ {
    /* 0x00 */ LabItemGridZ* grid;
    /* 0x04 */ s32 pad04;
    /* 0x08 */ s32 selected;
} LabItemCursorZ;
#define CURSOR(p) ((LabItemCursorZ*)((p) + 0x1E4))
void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);
void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);
extern Color_RGBA8 D_8900A698;
extern u8 D_8900A69C[];
extern char D_89018660[];
extern char D_8901866C[];
void Ui_DrawImageInStrips(void*, s32, s32);
void Font_SetColorForFlags(s32);
extern Color_RGBA8 D_8900A6AC;
extern Color_RGBA8 D_8900A6B0;
extern char D_89018678[];
void LabItem_DrawTrainerInfo();
void Window_SetRect(s8*, s32, s32, s32, s32);
void Menu_Init(s8*, s32, s32, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Window_DrawFrame(void*);
void Menu_DrawInlineItems(void*, s32, s32, s32, s32);
extern u8 D_8007356C[];
extern u8 D_89018688[];
s32 Menu_UpdateCursor(void*);
void func_8002B018(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern u8 D_8900A580[];
extern u8 D_8900A584[];
extern u8 D_8900A5A0[];
extern u8 D_8900A5A4[];
extern u8 D_8900A5A8[];
extern u8 D_8900A5AC[];
extern Color_RGBA8 D_8900A6B4;
extern Color_RGBA8 D_8900A6B8;
extern u8 D_8900BFC0[];
extern u8 D_89010368[];
extern u8 D_890110F0[];
extern PrimEnvColor D_8900A6BC;
extern PrimEnvColor D_8900A6C4;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern u8 D_89017A98[];
extern char D_890186C0[];
extern char D_890186CC[];
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void Font_SetColorForFlags(s32);
extern s32 D_8900A6CC[];
extern s8 *D_8900A6D8[];
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
extern u8 D_800735C4[];
void func_8002B054(s8*, s32);
void Window_DrawFrame(void*);
s32 func_8002B2B0(void *);
s32 LabItem_UpdateItemList(void *, u32);
void BgStage_DrawFrame(void);


extern s32 D_89019108;
extern s32 D_89019118;
extern u8 D_8901911C[];
void func_80022118(s32);
void func_80022188(s32);
s32 func_8002207C(s32);
void func_8002D7D4(s32);
void func_800243B8(void);
void func_800245E0(s32, s32);
void LabItem_DrawScreen(LabItemScreen*);
/**
 * Writes the changed item lists back to the save and flushes it.
 * Seen in play (2026-11-13) ran on レポートしてやめる (ないようが へんこうされています) after moving items in せいとん >
 * どうぐをいどうする.
 */
void LabItem_SaveChanges(LabItemScreen* arg0) {
    s32 locked = 0;
    s32 flush = 0;

    if ((arg0->dirty[0] != 0) || (arg0->dirty[1] != 0)) {
        locked = 1;
    }
    if (locked) {
        func_80022118(D_89019108);
    }
    if (arg0->dirty[0] != 0) {
        LabItem_WriteDeckBack(0x23, D_89019108, 0, &arg0->itemTables[0], 0, NULL, -1);
    }
    if (arg0->dirty[1] != 0) {
        LabItem_WriteDeckBack(0x22, D_89019108, 0, &arg0->itemTables[1], 0, NULL, -1);
    }
    if (arg0->gamePakSlot != -1) {
        if (arg0->saveSlots[arg0->gamePakSlot].present != 0) {
            if (arg0->dirty[2] != 0) {
                flush = 1;
                if (arg0->itemTables[2].count == 0) {
                    func_800245E0(0x12, arg0->gamePakSlot);
                } else {
                    LabItem_WriteDeckBack(0x12, 0, arg0->gamePakSlot, &arg0->itemTables[2], 0, NULL, -1);
                }
            }
        } else if (arg0->itemTables[2].count > 0) {
            flush = 1;
            LabItem_WriteDeckBack(0x12, 0, arg0->gamePakSlot, &arg0->itemTables[2], 0, (char*)D_8901911C, D_89019118);
        }
    }
    if (locked) {
        if (func_8002207C(D_89019108) == 0) {
            func_8002D7D4(D_89019108);
            LabItem_DrawScreen(arg0);
        }
        func_80022188(D_89019108);
    }
    if (flush) {
        func_800243B8();
    }
}

/**
 * Returns 1 when any of the three item lists changed.
 * Seen in play (2026-11-13) ran once when B left the item sort screen after nothing had been moved;
 * the screen closed without asking to save.
 */
s32 LabItem_HasUnsavedChanges(LabItemScreen* arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (arg0->dirty[i] != 0) {
            return 1;
        }
    }

    return 0;
}

void SavePrompt_Init(s8*, s32, s32);
void LabItem_InitConfirmWindow(LabItemConfirmWindow*, s32, s32, s8*, s8*);
s32 SavePrompt_Update(s8*);
void Save_DrawReportingWindow(s8*);
s32 LabItem_UpdateConfirmWindow(LabItemConfirmWindow*);
void LabItem_InitDeleteDataWindow(LabItemDeleteDataWindow*, s32, s32, LabItemSaveSlot*);
s32 LabItem_UpdateDeleteDataCursor(LabItemDeleteDataWindow*);
void func_89002E58(LabItemSaveDataWindow*, s32, s32, LabItemSaveSlot*, ByteMatrix*);
s32 func_8900352C(LabItemSaveDataWindow*);
void func_890022D0(LabItemOrganizeWindow*);
s32 LabItem_UpdateOrganizeWindow(LabItemOrganizeWindow*);
extern s8 D_8901871C[];
extern s8 D_89018728[];
extern s8 D_89018760[];
extern s8 D_8901876C[];

/**
 * Runs the item organizer's state machine for one frame.
 * Seen in play (2026-11-12): ran どうぐのせいり.
 */
s32 LabItem_UpdateScreen(LabItemScreen* arg0) {
    s32 ret = 0;
    s32 res;

    switch (arg0->state) {
        case 1:
            res = LabItem_UpdateOrganizeWindow(&arg0->organizeWindow);
            if (res == -1) {
                if (LabItem_HasUnsavedChanges(arg0) != 0) {
                    arg0->state = 2;
                    SavePrompt_Init(arg0->savePrompt, 0xCA, 0xAD);
                } else {
                    ret = 1;
                }
            } else if (res > 0) {
                switch (res) {
                    case 1:
                        arg0->state = 3;
                        LabItem_InitConfirmWindow(&arg0->confirmWindow, 0xBA, 0xAE, D_8901871C, D_89018728);
                        arg0->confirmWindow.choice.cursor = 1;
                        break;
                }
            }
            break;
        case 2:
            res = SavePrompt_Update(arg0->savePrompt);
            if (res == -1) {
                arg0->state = 1;
            } else if (res > 0) {
                ret = 1;
                switch (res) {
                    case 2:
                        break;
                    case 1:
                        Save_DrawReportingWindow(arg0->savePrompt);
                        LabItem_SaveChanges(arg0);
                        break;
                }
            }
            break;
        case 3:
            res = LabItem_UpdateConfirmWindow(&arg0->confirmWindow);
            if (res == -1) {
                arg0->state = 1;
            } else if (res == 1) {
                LabItem_InitDeleteDataWindow(&arg0->deleteDataWindow, 0x2B, 0x5C, arg0->saveSlots);
                arg0->state = 4;
            }
            break;
        case 4:
            res = LabItem_UpdateDeleteDataCursor(&arg0->deleteDataWindow);
            if (res == -1) {
                arg0->state = 1;
                arg0->itemTables[2].count = 0;
            } else if (res == 1) {
                LabItem_ReadDeckEntries(0x12, 0, arg0->deleteDataWindow.menu.cursor, &arg0->itemTables[2]);
                func_89002E58(&arg0->saveDataWindow, 0xD6, 0x45, &arg0->saveSlots[arg0->deleteDataWindow.menu.cursor], &arg0->itemTables[2]);
                arg0->state = 5;
            }
            break;
        case 5:
            res = func_8900352C(&arg0->saveDataWindow);
            if (res == -1) {
                arg0->state = 4;
            } else if (res == 1) {
                arg0->state = 6;
                LabItem_InitConfirmWindow(&arg0->confirmWindow, 0xBA, 0xAE, D_89018760, D_8901876C);
                arg0->confirmWindow.choice.cursor = 1;
            }
            break;
        case 6:
            res = LabItem_UpdateConfirmWindow(&arg0->confirmWindow);
            if (res == -1) {
                arg0->state = 5;
            } else if (res == 1) {
                arg0->gamePakSlot = arg0->deleteDataWindow.menu.cursor;
                arg0->saveSlots[arg0->gamePakSlot].present = 0;
                arg0->itemTables[2].count = 0;
                func_890022D0(&arg0->organizeWindow);
                arg0->state = 1;
            }
            break;
    }
    return ret;
}

extern Color_RGBA8 D_8900A6E8;
extern Color_RGBA8 D_80073520;
void func_8002A354(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);
/**
 * Draws one terminal menu row with its highlight or frame.
 * Seen in play (2026-11-12): rows ポケモンを いどうする / どうぐを いどうする / ボックスを いどうする.
 */
void LabTerminal_DrawMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 temp_v0 = *arg5;

    if (arg4 & 8) {
        func_8002A354(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x1A, D_8900A6E8);
    } else if (arg4 & 2) {
        Ui_DrawRoundedFrame(arg0 + 2, arg1 + 2, temp_v0 - 4, 0x1C, D_80073520);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

M2C_UNK func_80027804();
/**
 * Sets up a terminal menu window with its rows and title.
 * Seen in play (2026-11-12) in せいとん: ran on entry as the せいとん menu window appeared.
 */
void LabTerminal_InitMenuWindow(LabTerminalMenuWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, char* arg5, s32 arg6, char* arg7, s32 arg8, char* arg9) {

    Window_SetRect((s8*)&arg0->window, arg1, arg2, arg3, arg4);
    arg0->window.state = 0;
    arg0->window.animTimer = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = arg9;
    func_80027804(&arg0->items, arg5, arg6, arg6);
    Menu_Init((s8*)&arg0->menu, (s32)&arg0->items, (s32)arg0->itemFlags, (s32)LabTerminal_DrawMenuRow, arg3 - 0xC, 0x20);
    arg0->descriptions = (char**)arg7;
    arg0->descriptionLines = arg8;
}

extern Color_RGBA8 D_8900A6FC;
extern Color_RGBA8 D_8900A700;
/**
 * Draws a terminal menu window.
 * Seen in play (2026-11-12): the せいとん menu with its description.
 */
void LabTerminal_DrawMenuWindow(LabTerminalMenuWindow* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 sp38;
    s32 h;

    if (func_8002AE6C() == 0) {
        h = (arg0->menu.items->count << 5) + 8;
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + h + 5, arg0->window.frame.width, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, h, *(Color_RGBA8*)&D_8900A5BC);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + h + 0xC, arg0->window.frame.width - 0xC, arg0->descriptionLines * 0x1C, D_8900A6FC, D_8900A700);
        sp38 = arg0->window.frame.width - 0xC;
        Menu_DrawItems(&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 0xA, 0xFFEF, (s32)&sp38);
        Font_BeginTranslucentTextRendering();
        func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(arg0->window.frame.x + 0xE, arg0->window.frame.y + h + 0x10, arg0->descriptions[arg0->menu.cursor]);
        Font_EndTexturedTextRendering();
    }
}

/**
 * Handles input on a terminal menu window while it is open.
 * Seen in play (2026-11-12): moved over the せいとん menu.
 */
s32 LabTerminal_UpdateMenuWindow(LabTerminalMenuWindow* arg0) {
    s32 ret = 0;
    s32 temp_v0;

    switch (arg0->window.state) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (Menu_UpdateCursor(&arg0->menu) == 0) {
        temp_v0 = func_8002BC14(D_800603C0);
        if (temp_v0 == -1) {
            ret = -1;
        } else if (temp_v0 == 1) {
            ret = arg0->menu.cursor + 1;
        }
    }
    return ret;
}

extern char D_8900A704[];
extern char D_8900A710[];
extern char D_890188F4[];
void LabTerminal_InitMenuWindow(LabTerminalMenuWindow*, s32, s32, s32, s32, char*, s32, char*, s32, char*);

/**
 * Calls LabTerminal_InitMenuWindow with its own first argument passed straight through
 * followed by 0x30, 0x5C, 0x170, 0xCE, D_8900A704, 3, D_8900A710, 3 and
 * D_890188F4. What LabTerminal_InitMenuWindow does (it is still assembly) and what the
 * arguments mean are not established.
 * Seen in play (2026-11-12) in せいとん: set up the first menu: ポケモンを いどうする, どうぐを いどうする, ボックスを いどうする.
 */
void LabTerminal_InitMainMenu(LabTerminalMenuWindow* arg0) {
    LabTerminal_InitMenuWindow(arg0, 0x30, 0x5C, 0x170, 0xCE, D_8900A704, 3, D_8900A710, 3, D_890188F4);
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
void LabTerminal_DrawMenuWindow(LabTerminalMenuWindow*);
extern M2C_UNK D_89018900;
extern s32 D_89019108;
extern M2C_UNK D_89019110;

/**
 * Draws the GB save summary bar and the background.
 * Seen in play (2026-11-12): the せいとん screen with the 1P サトシ IDNo/12345 bar.
 */
void LabTerminal_DrawMainScreen(LabTerminalMenuWindow* arg0) {
    M2C_UNK *var_a1;

    BgStage_DrawFrame();
    if (D_89019108 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_89019110;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_89018900, D_89019108);
    LabItem_DrawBackground();
    LabTerminal_DrawMenuWindow(arg0);
}

/**
 * Wrapper around LabTerminal_UpdateMenuWindow(arg0): -1 calls func_8003F6AC(3) and returns -1;
 * a positive result calls func_8003F6AC(2) and returns the word at arg0 + 0x34
 * plus 1; any other result returns 0. (Same pattern as FreeBattle_UpdateBattleModeWindow.)
 * Seen in play (2026-11-12): returned the せいとん menu pick.
 */
s32 LabTerminal_UpdateMainMenu(LabTerminalMenuWindow* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = LabTerminal_UpdateMenuWindow(arg0);
    if (tmp == -1) {
        func_8003F6AC(3);
        result = -1;
    } else if (tmp > 0) {
        func_8003F6AC(2);
        result = arg0->menu.cursor + 1;
    }
    return result;
}

extern M2C_UNK D_89019110;
extern LabTerminalMenuWindow D_89028950;
extern s32 D_890289D4;
s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);

/**
 * Stores the result of func_80025BD8() in D_89019108. If it is not -1, passes it with
 * &D_89019110 to func_80027FF8. Then calls LabTerminal_InitMainMenu(&D_89028950) and sets
 * D_890289D4 to 1. (The value is re-read from D_89019108 after the store, which is
 * what the retail register allocation needs.) What the value means is not established.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void LabTerminal_InitScreen(void) {
    D_89019108 = func_80025BD8();
    if (D_89019108 != -1) {
        func_80027FF8(&D_89019110, D_89019108);
    }
    LabTerminal_InitMainMenu(&D_89028950);
    D_890289D4 = 1;
}

typedef struct Col8900429C { u8 r, g, b, a; } Col8900429C;
extern s32 D_8900A71C;
extern s32 D_8900A720;
/*
 * Second name for D_8900A71C. The fade-out store in this function family
 * (also func_8200579C, func_8900429C, LabPCList_UpdateFade, func_8A101B30) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_8900A71C_2;
extern M2C_UNK D_8901890C;
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(Col8900429C*, Col8900429C, f32);
s32 func_8900429C(s32 arg0) {
    Col8900429C sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_8900A71C;
    if (n >= 8) {
        D_8900A720 = 1;
    }
    if (D_8900A720 != 0) {
        n--;
        D_8900A71C_2 = n;
    }
    BgStage_DrawFrame();
    if (D_89019108 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_89019110;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_8901890C, D_89019108);
    n = D_8900A71C;
    func_8002C8D8(&sp2C, *(Col8900429C*)&D_8900A5B8, n / (f64)8.0f);
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_8900A720 == 0) {
        n = D_8900A71C;
        n++;
        D_8900A71C = n;
    }
    return 0;
}

void Cont_StartReadInputs(void);                            /* extern */
void Cont_ReadInputs(void);                            /* extern */
void func_89003650(LabItemScreen*);
void LabItem_DrawScreen(LabItemScreen*);
M2C_UNK PcSort_Init(M2C_UNK *, M2C_UNK *);        /* extern */
M2C_UNK PcSort_Free(M2C_UNK *);                   /* extern */
M2C_UNK PcSort_DrawScreen(M2C_UNK *);                   /* extern */
s32 PcSort_UpdateScreen(M2C_UNK *);                       /* extern */
M2C_UNK PcBox_Init(M2C_UNK *);                   /* extern */
M2C_UNK PcBox_Free(M2C_UNK *);                   /* extern */
M2C_UNK PcBox_DrawScreen(M2C_UNK *);                   /* extern */
s32 PcBox_UpdateScreen(M2C_UNK *);                       /* extern */
extern M2C_UNK D_89018918;
extern LabItemScreen D_89019128;
extern M2C_UNK D_89019B98;
extern M2C_UNK D_89021428;
extern LabTerminalMenuWindow D_89028950;
extern s32 D_890289D4;

/**
 * One frame of the lab terminal.
 * Seen in play (2026-11-12): ran every frame of せいとん.
 */
s32 LabTerminal_RunFrame(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    sp1C = 0;
    Cont_StartReadInputs();
    Cont_ReadInputs();
    switch (D_890289D4) {                           /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        LabTerminal_DrawMainScreen(&D_89028950);
        temp_v0 = LabTerminal_UpdateMainMenu(&D_89028950);
        if (temp_v0 == -1) {
            sp1C = 1;
        } else if (temp_v0 > 0) {
            D_890289D4 = temp_v0 + 1;
            switch (D_890289D4) {                   /* switch 2; irregular */
            case 2:                                 /* switch 2 */
                PcSort_Init(&D_89019B98, &D_89018918);
                break;
            case 3:                                 /* switch 2 */
                func_89003650(&D_89019128);
                break;
            case 4:                                 /* switch 2 */
                PcBox_Init(&D_89021428);
                break;
            }
        }
        break;
    case 3:                                         /* switch 1 */
        LabItem_DrawScreen(&D_89019128);
        if (LabItem_UpdateScreen(&D_89019128) != 0) {
            D_890289D4 = 1;
        }
        break;
    case 2:                                         /* switch 1 */
        PcSort_DrawScreen(&D_89019B98);
        if (PcSort_UpdateScreen(&D_89019B98) != 0) {
            D_890289D4 = 1;
            PcSort_Free(&D_89019B98);
        }
        break;
    case 4:                                         /* switch 1 */
        PcBox_DrawScreen(&D_89021428);
        if (PcBox_UpdateScreen(&D_89021428) != 0) {
            D_890289D4 = 1;
            PcBox_Free(&D_89021428);
        }
        break;
    }
    return sp1C;
}

extern FontContext* D_86A06200;
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_04000000[];
extern u8 D_00400F70[];
extern u8 D_004076E0[];
extern u8 D_88000000[];
extern u8 D_00235D70[];
extern u8 D_00238BD0[];
void LabTerminal_InitScreen(void);
s32 func_8900429C(s32);

/**
 * LabTerminal_Init
 *
 * Fragment entry point.  It follows the same template as the Pokedex entry
 * function Pokedex_Init, and neither argument is used.  The steps are:
 *
 *   1. main_pool_push_state('TERM') saves the main pool state under that tag;
 *      the matching main_pool_pop_state('TERM') is near the end.
 *   2. Font_Init(0x3C, 0) is called (Font_Init in symbol_addrs.txt).
 *   3. Two assets are loaded with Asset_LoadToSegment: the ROM range
 *      D_002E0BE0..D_002E2B90 into segment 1 and D_00400F70..D_004076E0 into
 *      segment 4.  The segment number is bits 24-27 of the address of
 *      D_01000000 / D_04000000.
 *   4. LabTerminal_InitScreen() and StageLoader_UpdateSegments() are called.
 *   5. BgStage_RunUntilCondition is run three times, with timer values 8, 0
 *      and 8: the first and third with callback func_8900429C, the second
 *      with LabTerminal_RunFrame.  What those callbacks do is not established
 *      (func_8900429C is still assembly).
 *   6. StageLoader_WaitForRetrace() and main_pool_pop_state('TERM').
 *   7. Fragment_QueueCall queues a call to the fragment whose id comes from
 *      the address D_88000000 (bits 20-27, minus 0x10), with the ROM range
 *      D_00235D70..D_00238BD0.
 *
 * Returns 0x8040.
 * Seen in play (2026-11-12) in せいとん: ran when せいとん was entered from the main menu.
 */
s32 LabTerminal_Init(s32 arg0, s32 arg1) {
    main_pool_push_state('TERM');
    Font_Init(0x3C, 0);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);
    LabTerminal_InitScreen();
    StageLoader_UpdateSegments();
    BgStage_RunUntilCondition(8, func_8900429C);
    BgStage_RunUntilCondition(0, LabTerminal_RunFrame);
    BgStage_RunUntilCondition(8, func_8900429C);
    StageLoader_WaitForRetrace();
    main_pool_pop_state('TERM');
    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
