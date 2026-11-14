/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "party_summary.h"
#include "audio_commands.h"
#include "display_object_textures.h"
#include "font.h"
#include "fragments/cartridge_check/cartridge_check.h"
#include "fragments/main_menu/main_menu.h"
#include "fragments/unidentified_001/unidentified_001.h"
#include "gb_save.h"
#include "geo_render.h"
#include "input.h"
#include "memory_main.h"
#include "pokemon_stats.h"
#include "ui_graphics.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK Ui_DrawTexturedDivider(s32, s32, s32, M2C_UNK *);
M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32);
M2C_UNK func_80019008(s32, s32, M2C_UNK);
M2C_UNK func_8001B5F0();
M2C_UNK func_80029864(s32, s32, s32, M2C_UNK *);
extern M2C_UNK D_800734A8;
extern s8 *D_800603C0;
extern s8 D_8007356C;
s32 Window_DrawAnimatedFrame();
s32 func_80020CE4(s32, s32, s32);
u8* func_800196F8(s32);
void func_8001A384(s32, s32);
void func_8001A944(s32, s32, const char*, ...);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001AB6C(void);
void func_8001ABBC(void);
void func_80022118(s32);
void func_80022188(s32);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_8002D7D4(s32);

extern s32 D_8A21DE08;
extern M2C_UNK D_8A21DE10;

s32 Display_IsFrameReady(void);
s32 func_80002BA4(void*, s32);
s32 func_80017304(s32, BinArchive*, s32, void*, s32);
s32 func_8001FA8C(s32);
s32 BattleMon_CountMoves(u8* arg0);
s32 BattleMon_GetMoveIndexChecked();
typedef struct Move8A201D3C { u8 unk00; u8 unk01; u8 power; u8 type; u8 unk04; u8 unk05; } Move8A201D3C;
extern Move8A201D3C D_8006B190[];
extern BinArchive* sMoveBackdropArchive;
extern void* D_8A21DA58;
extern void* sMoveBackdropPools[4];
extern s32 sMoveBackdrops[];

/**
 * Draws a 282x130 YUV image at (x, y) as 16x16 tiles (the last column and row are cut
 * to 10 and 2 pixels): the move-type picture behind the move description.
 * Seen in play (2026-11-14): a yellow lightning picture behind でんきショック's text and a grey one
 * behind なきごえ's. Stubbed, C-Right left the old picture under the new text.
 */
void MonSummary_DrawMoveBackdrop(s32 x, s32 y, u8* image) {
    s32 j;
    s32 i;
    s32 w;
    s32 h;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, 0x0F0A4000, 0);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombine(gDisplayListHead++, 0x17FE2F, 0x77FCF87C);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_CONV);
    gDPSetConvert(gDisplayListHead++, G_CV_K0, G_CV_K1, G_CV_K2, G_CV_K3, G_CV_K4, G_CV_K5);
    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 0x90; i += 0x10) {
        h = 0x82 - i;
        if (h > 0x10) {
            h = 0x10;
        }
        for (j = 0; j < 0x120; j += 0x10) {
            w = 0x11A - j;
            if (w > 0x10) {
                w = 0x10;
            }
            left = (x + j) << 2;
            top = (y + i) << 2;
            right = (x + j + w) << 2;
            bottom = (y + i + h) << 2;
            gDPLoadTextureBlockYuv(gDisplayListHead++, image, G_IM_FMT_YUV, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, left, top, right, bottom, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            image += 0x200;
        }
    }

    gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
}

void MonSummary_DrawMoveBackdrop(s32, s32, u8*);
s32 func_8001FA8C(s32);
extern Color_RGBA8 D_8A203424;
extern char D_8A21D9B4[];
extern char D_8A21D9BC[];
extern char D_8A21D9C8[];
extern char D_8A21D9D4[];
extern char D_8A21D9D8[];
extern char D_8A21D9DC[];
typedef struct Entry8006A9DC { char* str; s32 unk4; s32 unk8; } Entry8006A9DC;
extern Entry8006A9DC D_8006A9DC[];
/**
 * Draws the selected move's タイプ/, いりょく/ (power; --- below 2), めいちゅう/ (accuracy %)
 * and description over its backdrop.
 * Declared s32 with no return statement: only then does IDO stop reading the
 * move id from v0 after the -2 check.
 * Seen in play (2026-11-14): タイプ/でんき いりょく/ 40 めいちゅう/100% for でんきショック and
 * タイプ/ノーマル いりょく/--- for なきごえ.
 */
s32 MonSummary_DrawMoveInfo(s32 x, s32 y, s32 mon, s32 slot)
{
    s32 move;
    MonSummary_DrawMoveBackdrop(x + 4, y + 2, (u8*)sMoveBackdrops[slot]);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x122, 2, D_8A203424);
    func_80029028(x, y + 2, 4, 0x82, D_8A203424);
    func_80029028(x + 0x11E, y + 2, 4, 0x82, D_8A203424);
    move = BattleMon_GetMoveIndexChecked(mon, slot);
    if (move != (-2)) {
        s32 type_id;
        Entry80066AD8 *type;
        s32 pp;
        type_id = func_8001FA8C(D_8006B190[move].type);
        type = &D_80066AD8[type_id];
        pp = ((((D_8006B190[move].unk04 * 100) / 255) + 2) / 5) * 5;
        func_8001AB6C();
        func_8001A384(4, 0);
        func_8001AA9C(0xFF, 0xC8, 0xC8, 0xFF);
        func_8001A944(x + 9, y + 4, D_8A21D9B4);
        func_8001A944(x + 0x99, y + 4, D_8A21D9BC);
        func_8001A944(x + 9, y + 0x17, D_8A21D9C8);
        func_8001AA9C(type->color.r, type->color.g, type->color.b, type->color.a);
        func_8001A944(x + 0x49, y + 4, type->str);
        func_8001AA9C(*((u8 *) (((s8 *) (&D_800734A8)) + 0)), *((u8 *) (((s8 *) (&D_800734A8)) + 1)), *((u8 *) (((s8 *) (&D_800734A8)) + 2)), *((u8 *) (((s8 *) (&D_800734A8)) + 3)));
        Font_SetLineHeight(0x14);
        if (D_8006B190[move].power >= 2)
        {
            func_8001A944(x + 0xE9, y + 4, D_8A21D9D4, D_8006B190[move].power);
        }
        else
        {
            func_8001A944(x + 0xE9, y + 4, D_8A21D9D8, D_8006B190[move].power);
        }
        func_8001A944(x + 0x69, y + 0x17, D_8A21D9DC, pp);
        func_8001A384(4, -1);
        Font_SetLineHeight(0x18);
        func_8001A944(x + 9, y + 0x3A, D_8006A9DC[move].str);
        func_8001ABBC();
    }
}

/**
 * Draws the rendered 3D model preview texture, 8 rows at a time.
 * Seen in play (2026-11-14): the turning Pikachu model on the left of both summary pages.
 */
void MonSummary_DrawModelPreview(s32 x, s32 y, s32 mon) {
    u8* tex;
    s32 i;
    s32 n;

    tex = func_800196F8(sPartyModelPreview);
    BgStage_DrawFrame();
    gSPDisplayList(gDisplayListHead++, D_80060290);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    for (i = 0; i < 0xD2; i += n) {
        if ((0xD2 - i) < 8) {
            n = 0xD2 - i;
        } else {
            n = 8;
        }
        func_8001B884(x, y + i, 0xF4, n, tex, 0x100, 0x200000);
        tex += n << 9;
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}


/**
 * Sets up the summary window (552x362) for `mon` and loads one move-type backdrop per move.
 * Seen in play (2026-11-14): ran when つよさをみる was picked.
 */
void MonSummary_InitPageWindow(MonSummaryWindow* window, s32 x, s32 y, s32 mon) {
    s32 unused; // FAKE: stack padding
    s32 count;
    s32 i;
    s32 handle;
    s32 move;

    Window_SetRect((s8*)window, x, y, 0x228, 0x16A);
    window->window.state = 0;
    window->window.title = 0;
    window->window.animTimer = 0;
    window->window.frame.style = 0x1001;
    window->modelLoaded = 0;
    window->mon = mon;
    count = BattleMon_CountMoves((u8*)mon);
    while (Display_IsFrameReady() == 0) {
    }
    for (i = 0; i < count; i++) {
        handle = func_80002BA4(sMoveBackdropPools[i], 0x14800);
        move = BattleMon_GetMoveIndexChecked(mon, i);
        sMoveBackdrops[i] = func_80017304(handle, sMoveBackdropArchive, func_8001FA8C((move == -2) ? 0 : D_8006B190[move].type), D_8A21DA58, 0x3000);
    }
}

/**
 * Draws a summary page: page 0 is the stats page (header, stats, trainer info), page 1 the
 * moves page (header, move list, move info). Both show the 3D model.
 * Seen in play (2026-11-14): page 0 after つよさをみる, page 1 after A on it.
 */
void MonSummary_DrawPage(MonSummaryWindow* window, s32 page)
{
  s32 temp_v0;
  if (((window->window.state) != 2) && (Window_DrawAnimatedFrame() == 0))
  {
    if (page == 0)
    {
      func_80029864((window->window.frame.x) + 0xF9, window->window.frame.y, window->window.frame.height, &D_8007356C);
      Ui_DrawTexturedDivider(window->window.frame.x, (window->window.frame.y) + 0xD7, 0x100, &D_8007356C);
      Ui_DrawTexturedDivider((window->window.frame.x) + 0xFA, (window->window.frame.y) + 0x95, 0x12E, &D_8007356C);
      MonSummary_DrawStats((window->window.frame.x) + 6, (window->window.frame.y) + 0xDE, window->mon);
      MonSummary_DrawHeader((window->window.frame.x) + 0x100, (window->window.frame.y) + 6, window->mon);
      MonSummary_DrawTrainerInfo((window->window.frame.x) + 0x100, (window->window.frame.y) + 0x9C, window->mon);
    }
    else
    {
      Ui_DrawTexturedDivider(window->window.frame.x, (window->window.frame.y) + 0xD7, window->window.frame.width, &D_8007356C);
      func_80029864((window->window.frame.x) + 0xF9, window->window.frame.y, 0xDE, &D_8007356C);
      MonSummary_DrawMovesHeader((window->window.frame.x) + 0x100, (window->window.frame.y) + 6, window->mon);
      MonSummary_DrawMoveList((window->window.frame.x) + 6, (window->window.frame.y) + 0xDE, window->mon, window->moveSlot);
      MonSummary_DrawMoveInfo((window->window.frame.x) + 0x100, (window->window.frame.y) + 0x54, window->mon, window->moveSlot);
    }
  }
  temp_v0 = window->window.state;
  if (((temp_v0 ^ 0) == 1) || (temp_v0 == 2)) // FAKE: no-op ^ 0
  {
    if ((window->modelLoaded) == 0)
    {
      window->modelLoaded = 1;
      func_80019008(sPartyModelPreview, window->mon, 0x108D);
    }
    MonSummary_DrawModelPreview(0x32, 0x5A, window->mon);
  }
}

/**
 * Moves page input: C-Up, C-Right, C-Down, C-Left pick move slot 0-3. An empty slot buzzes
 * (sound 8); otherwise the slot becomes window->moveSlot and the page redraws. Returns 1 when a C
 * button was pressed. Seen in play (2026-11-14): C-Right picked なきごえ, C-Left でんこうせっか.
 */
s32 MonSummary_UpdateMoveCursor(MonSummaryWindow* window) {
    s32 var_s0;
    u16 temp_v0;

    var_s0 = -1;
    if (func_80022B40() != 0) {
        temp_v0 = ((Controller*)D_800603C0)->buttonPressed;
        if (temp_v0 & 8) {
            var_s0 = 0;
        } else if (temp_v0 & 1) {
            var_s0 = 1;
        } else if (temp_v0 & 4) {
            var_s0 = 2;
        } else if (temp_v0 & 2) {
            var_s0 = 3;
        }
        if (var_s0 >= 0) {
            if (BattleMon_GetMoveIndexChecked(window->mon, var_s0, window) == -1) {
                func_8003F6AC(8);
            } else {
                func_8003F6AC(2);
                window->moveSlot = var_s0;
                if (window->window.state <= 0) {
                    window->window.animTimer = (s32) window->window.animTimer;
                } else {
                    window->window.animTimer = 4;
                }
            }
        }
    }
    return var_s0 >= 0;
}

/**
 * Draws the tinted screen background.
 * Seen in play (2026-11-14): the てもち screen background.
 */
void PartyScreen_DrawBackground(void) {
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, D_8A203300.r, D_8A203300.g, (s32)D_8A203300.b);
}

/**
 * Returns the experience points needed to reach `level` for the species' growth rate.
 * Seen in play (2026-11-14): Pikachu at 1728 Exp showed あと 469で L13 (2197 = 13^3).
 */
s32 MonSummary_GetExpForLevel(s32 species, s32 level) {
    s32 sp4;

    switch (gBaseStats[species].growthRate) {
        case 0:
            sp4 = level * level * level;
            break;

        case 1:
            sp4 = (((level * level * level * 3) / 4) + (level * 0xA * level)) - 0x1E;
            break;

        case 2:
            sp4 = (((level * level * level * 3) / 4) + (level * 0x14 * level)) - 0x1E;
            break;

        case 3:
            sp4 = ((((level * level * level * 6) / 5) - (level * 0xF * level)) + (level * 0x64)) - 0x8C;
            break;

        case 4:
            sp4 = (level * level * level * 4) / 5;
            break;

        case 5:
            sp4 = (level * level * level * 5) / 4;
            break;
    }
    return sp4;
}

/**
 * Reads the Game Boy party from the Transfer Pak into the BattleMon table; sets its count.
 * Seen in play (2026-11-14): ran once as the てもち screen opened and filled the 3 Pokémon of the save.
 */
void PartyScreen_ReadParty(ByteMatrix* table) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp1C = (s32)table->rows;
    temp_v0 = func_80020AFC(0x20, sPartyGbPort, 0, 0);
    sp18 = temp_v0;
    table->count = func_80020CE4(sp1C, table->capacity, temp_v0);
    func_80020C60(sp18);
}

/**
 * Writes the reordered party back to the Game Boy save (レポートしてやめる), then redraws `screen`.
 * Seen in play (2026-11-14): after swapping ハナ and カコ, the pak .sav's species list changed from
 * 99 B0 54 to B0 99 54.
 */
void PartyScreen_WriteParty(s32* monList, s32 screen) {
    s32* sp2C;
    s32 i;
    s32 temp_s3;

    sp2C = (s32*)monList[0];
    func_80022118(sPartyGbPort);
    temp_s3 = func_80020AFC(0x20, sPartyGbPort, 0, 1);

    for (i = 0; i < monList[2]; i++) {
        func_80020DF0(sp2C[i], 1, temp_s3);
    }

    func_80020C60(temp_s3);
    if (func_8002207C(sPartyGbPort) == 0) {
        func_8002D7D4(sPartyGbPort);
        PartyScreen_Draw((M2C_UNK*)screen);
    }
    func_80022188(sPartyGbPort);
}

void func_80027410(s8 *, s8 *, s32, s32, s32);
void func_80027804(s8 *, s8 *, s32, s32);
/**
 * Starts the てもち screen at state 1: reads the party, builds the list and the icons.
 * Seen in play (2026-11-14): ran once as the screen opened.
 */
void PartyScreen_SetupList(PartyScreen* screen) {
    s32 i;

    screen->state = 1;
    screen->activeWindow = &screen->listWindow.window;
    screen->dirty = 0;
    for (i = 0; i < 6; i++) {
        screen->monPointers[i] = &screen->mons[i];
    }
    func_80027410((s8*)&screen->monTable, (s8*)screen->mons, 0x50, 6, 0);
    PartyScreen_ReadParty((s8*)&screen->monTable);
    func_80027804((s8*)&screen->monList, (s8*)screen->monPointers, 6, screen->monTable.count);
    for (i = 0; i < screen->monTable.count; i++) {
        func_8001833C((PokeIconRenderer*)sPartyIconList, i, (BattleMon*)(screen->monTable.rows + i * 0x50),
                      GPACK_RGBA5551(D_8A203304.r, D_8A203304.g, D_8A203304.b, 1));
    }
    PartyScreen_InitList(&screen->listWindow, 0x2F, 0x4D, (s32)&screen->monList);
}

s32 Window_UpdateAnimation(Window* arg0);
void SavePrompt_Draw(s8*);
void PartyScreen_DrawList(PartyListWindow*, s32);
#define CTX ((PartyScreen*)screen)
/**
 * Draws the てもち screen for its current state (1 list, 2 action menu, 3 reorder, 4 stats page,
 * 5 moves page, 6 save prompt). Seen in play (2026-11-14): every frame of the screen.
 */
void PartyScreen_Draw(void* screen) {
    BgStage_DrawFrame();
    switch (CTX->state) {
        case 1:
            if (Window_UpdateAnimation(&CTX->listWindow) != 0) {
                PartyScreen_DrawBackground();
            }
            PartyScreen_DrawList(&CTX->listWindow, 0);
            break;
        case 2:
            if ((CTX->nextState == 4) || (CTX->nextState == 7)) {
                PartyScreen_DrawBackground();
                Window_UpdateAnimation(&CTX->listWindow);
                Window_UpdateAnimation(&CTX->actionMenu);
                PartyScreen_DrawList(&CTX->listWindow, 1);
            } else if (Window_UpdateAnimation(&CTX->actionMenu) != 0) {
                CTX->listWindow.window.animTimer = (CTX->listWindow.window.state <= 0) ? CTX->listWindow.window.animTimer : 4;
                Window_UpdateAnimation(&CTX->listWindow);
                PartyScreen_DrawList(&CTX->listWindow, 1);
                CTX->listWindow.window.animTimer = (CTX->listWindow.window.state <= 0) ? CTX->listWindow.window.animTimer : 4;
            } else {
                Window_UpdateAnimation(&CTX->listWindow);
                PartyScreen_DrawList(&CTX->listWindow, 1);
            }
            PartyScreen_DrawActionMenu(&CTX->actionMenu);
            break;
        case 3:
            if (Window_UpdateAnimation(&CTX->listWindow) != 0) {
                PartyScreen_DrawBackground();
            }
            PartyScreen_DrawList(&CTX->listWindow, 2);
            break;
        case 4:
            if (Window_UpdateAnimation(&CTX->summaryWindow) != 0) {
                PartyScreen_DrawBackground();
            }
            MonSummary_DrawPage(&CTX->summaryWindow, 0);
            break;
        case 5:
            if (Window_UpdateAnimation(&CTX->summaryWindow) != 0) {
                PartyScreen_DrawBackground();
            }
            MonSummary_DrawPage(&CTX->summaryWindow, 1);
            break;
        case 6:
            if (CTX->nextState == 7) {
                PartyScreen_DrawBackground();
                Window_UpdateAnimation(&CTX->listWindow);
                Window_UpdateAnimation(&CTX->savePrompt);
                PartyScreen_DrawList(&CTX->listWindow, 0);
            } else if (Window_UpdateAnimation(&CTX->savePrompt) != 0) {
                CTX->listWindow.window.animTimer = (CTX->listWindow.window.state <= 0) ? CTX->listWindow.window.animTimer : 4;
                Window_UpdateAnimation(&CTX->listWindow);
                PartyScreen_DrawList(&CTX->listWindow, 0);
                CTX->listWindow.window.animTimer = (CTX->listWindow.window.state <= 0) ? CTX->listWindow.window.animTimer : 4;
            } else {
                Window_UpdateAnimation(&CTX->listWindow);
                PartyScreen_DrawList(&CTX->listWindow, 0);
            }
            SavePrompt_Draw(&CTX->savePrompt);
            break;
    }
}
#undef CTX

/**
 * Starts closing the active window; when it has closed, PartyScreen_Update switches to
 * `nextState` and `nextWindow`. Seen in play (2026-11-14): on つよさをみる, ならびかえ and on leaving.
 */
void PartyScreen_CloseWindow(PartyScreen* screen, s32 nextState, s32 nextWindow) {
    screen->activeWindow->animTimer = 7;
    screen->nextState = nextState;
    screen->nextWindow = (Window*)nextWindow;
}

s32 Menu_UpdateCursor(s8*);
s32 func_8002BC14(s32);
void SavePrompt_Init(s8*, s32, s32);
void Menu_ClearItemFlags(s8*);
s32 SavePrompt_Update(s8*);
void Save_DrawReportingWindow(s8*);
s32 PartyScreen_UpdateActionMenu(PartyActionMenuWindow*);
void PartyScreen_InitActionMenu(PartyActionMenuWindow* window, s32 x, s32 y, u8* mon);
void PartyScreen_WriteParty(s32* monList, s32 screen);
/**
 * Runs the てもち screen's state machine for one frame. Returns 1 when the screen is done.
 * Seen in play (2026-11-14): list, action menu, stats page, moves page, ならびかえ and the save prompt
 * 「ないようが へんこうされています」.
 */
M2C_UNK PartyScreen_Update(PartyScreen* ctx) {
    s32 ret = 0;
    PartyScreen* arg0 = ctx; // FAKE: the copy takes a stack slot; needed to match
    s32 res;

    if (arg0->activeWindow->state == 4) {
        arg0->state = arg0->nextState;
        if (arg0->state == 7) {
            ret = 1;
        } else {
            arg0->nextState = 0;
            arg0->activeWindow = arg0->nextWindow;
        }
        return ret;
    }
    if ((arg0->activeWindow->state != 1) && (arg0->activeWindow->state != 2)) {
        return 0;
    }

    switch (arg0->state) {
        case 1:
            if (Menu_UpdateCursor(&arg0->listWindow.menu) != 0) {
                arg0->listWindow.window.animTimer = (arg0->listWindow.window.state <= 0) ? arg0->listWindow.window.animTimer : 4;
            } else {
                res = func_8002BC14((s32)D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    if (arg0->dirty != 0) {
                        SavePrompt_Init(&arg0->savePrompt, 0xCA, 0xAD);
                        arg0->state = 6;
                        arg0->activeWindow = &arg0->savePrompt;
                    } else {
                        PartyScreen_CloseWindow(arg0, 7, 0);
                    }
                } else if (res == 1) {
                    func_8003F6AC(2);
                    PartyScreen_InitActionMenu(&arg0->actionMenu, 0x194, 0x123, (u8*)arg0->monPointers[arg0->listWindow.menu.cursor]);
                    arg0->state = 2;
                    arg0->activeWindow = &arg0->actionMenu;
                }
            }
            break;
        case 2:
            res = PartyScreen_UpdateActionMenu(&arg0->actionMenu);
            if (res == -1) {
                func_8003F6AC(3);
                PartyScreen_CloseWindow(arg0, 1, (s32)&arg0->listWindow);
            } else if (res > 0) {
                switch (res) {
                    case 1:
                        func_8003F6AC(2);
                        PartyScreen_CloseWindow(arg0, 4, (s32)&arg0->summaryWindow);
                        arg0->summaryWindow.moveSlot = 0;
                        arg0->listWindow.window.animTimer = 7;
                        MonSummary_InitPageWindow(&arg0->summaryWindow, 0x2C, 0x54, arg0->monPointers[arg0->listWindow.menu.cursor]);
                        break;
                    case 2:
                        func_8003F6AC(2);
                        PartyScreen_CloseWindow(arg0, 3, (s32)&arg0->listWindow);
                        arg0->listWindow.menu.itemFlags[arg0->listWindow.menu.cursor] |= 8;
                        arg0->swapIndex = arg0->listWindow.menu.cursor;
                        break;
                    case 3:
                        func_8003F6AC(3);
                        if (arg0->dirty != 0) {
                            SavePrompt_Init(&arg0->savePrompt, 0xD4, 0xAD);
                            PartyScreen_CloseWindow(arg0, 6, (s32)&arg0->savePrompt);
                        } else {
                            PartyScreen_CloseWindow(arg0, 7, 0);
                            arg0->listWindow.window.animTimer = 7;
                        }
                        break;
                }
            }
            break;
        case 3:
            if (Menu_UpdateCursor(&arg0->listWindow.menu) != 0) {
                arg0->listWindow.window.animTimer = (arg0->listWindow.window.state <= 0) ? arg0->listWindow.window.animTimer : 4;
            } else {
                res = func_8002BC14((s32)D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    arg0->state = 1;
                    arg0->activeWindow = &arg0->listWindow;
                    arg0->listWindow.window.animTimer = (arg0->listWindow.window.state <= 0) ? arg0->listWindow.window.animTimer : 4;
                    Menu_ClearItemFlags(&arg0->listWindow.menu);
                } else if (res == 1) {
                    func_8003F6AC(0x18);
                    res = arg0->monPointers[arg0->swapIndex];
                    arg0->monPointers[arg0->swapIndex] = arg0->monPointers[arg0->listWindow.menu.cursor];
                    arg0->monPointers[arg0->listWindow.menu.cursor] = res;
                    func_8001833C((PokeIconRenderer*)sPartyIconList, arg0->swapIndex, (BattleMon*)arg0->monPointers[arg0->swapIndex], 0);
                    func_8001833C((PokeIconRenderer*)sPartyIconList, arg0->listWindow.menu.cursor, (BattleMon*)arg0->monPointers[arg0->listWindow.menu.cursor], 0);
                    arg0->dirty = 1;
                    arg0->state = 1;
                    arg0->activeWindow = &arg0->listWindow;
                    arg0->listWindow.window.animTimer = (arg0->listWindow.window.state <= 0) ? arg0->listWindow.window.animTimer : 4;
                    Menu_ClearItemFlags(&arg0->listWindow.menu);
                }
            }
            break;
        case 4:
            res = func_8002BC14((s32)D_800603C0);
            if (res == -1) {
                func_8003F6AC(3);
                PartyScreen_CloseWindow(arg0, 1, (s32)&arg0->listWindow);
                arg0->listWindow.window.animTimer = 0;
            } else if (res == 1) {
                func_8003F6AC(2);
                arg0->state = 5;
                arg0->summaryWindow.window.animTimer = (arg0->summaryWindow.window.state <= 0) ? arg0->summaryWindow.window.animTimer : 4;
            }
            break;
        case 5:
            if (MonSummary_UpdateMoveCursor(&arg0->summaryWindow) == 0) {
                res = func_8002BC14((s32)D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    arg0->state = 4;
                    arg0->summaryWindow.window.animTimer = (arg0->summaryWindow.window.state <= 0) ? arg0->summaryWindow.window.animTimer : 4;
                } else if (res == 1) {
                    func_8003F6AC(2);
                    PartyScreen_CloseWindow(arg0, 1, (s32)&arg0->listWindow);
                    arg0->listWindow.window.animTimer = 0;
                }
            }
            break;
        case 6:
            res = SavePrompt_Update(&arg0->savePrompt);
            if (res == -1) {
                PartyScreen_CloseWindow(arg0, 1, (s32)&arg0->listWindow);
            } else if (res > 0) {
                switch (res) {
                    case 1:
                        Save_DrawReportingWindow(&arg0->savePrompt);
                        PartyScreen_WriteParty((s32*)(&arg0->monList), (s32)arg0);
                        PartyScreen_CloseWindow(arg0, 7, 0);
                        arg0->listWindow.window.animTimer = 7;
                        break;
                    case 2:
                        PartyScreen_CloseWindow(arg0, 7, 0);
                        arg0->listWindow.window.animTimer = 7;
                        break;
                }
            }
            break;
        case 7:
            ret = 1;
            break;
    }
    return ret;
}

/**
 * Finds the active Game Boy pak, builds its summary for the top bar and sets up the screen.
 * Seen in play (2026-11-14): ran first after the entry point.
 */
void PartyScreen_Load(void) {
    sPartyGbPort = func_80025BD8();
    D_8A21DE08 = sPartyGbPort;
    if (D_8A21DE08 != -1) {
        func_80027FF8(&D_8A21DE10, D_8A21DE08);
    }
    PartyScreen_SetupList(&sPartyScreen);
}

typedef struct ColF50 { u8 r, g, b, a; } ColF50;
extern s32 D_8A203428;
extern s32 D_8A20342C;
/*
 * Second name for D_8A203428. The fade-out store in this function family
 * (also func_8200579C, LabTerminal_UpdateFade, LabPCList_UpdateFade, func_8A101B30) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_8A203428_2;
extern M2C_UNK D_8A21D9E4;
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(ColF50*, ColF50, f32);
/**
 * Fade frame for BgStage_RunUntilCondition: steps the background tint counter up to 8, then
 * back down, and draws the pak summary bar on top.
 * Seen in play (2026-11-14): ran as the てもち screen opened and as it closed.
 */
s32 PartyScreen_FadeFrame(u8 unused) {
    ColF50 sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_8A203428;
    if (n >= 8) {
        D_8A20342C = 1;
    }
    if (D_8A20342C != 0) {
        n--;
        D_8A203428_2 = n;
    }
    BgStage_DrawFrame();
    if (D_8A21DE08 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8A21DE10;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_8A21D9E4, D_8A21DE08);
    n = D_8A203428;
    func_8002C8D8(&sp2C, *(ColF50*)&D_8A203300, n / (f64)8.0f);
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_8A20342C == 0) {
        n = D_8A203428;
        n++;
        D_8A203428 = n;
    }
    return 0;
}

/**
 * One frame: reads the controllers, then draws and updates the てもち screen.
 * Seen in play (2026-11-14): every frame of the てもち (party) screen, reached from the main menu with a
 * crafted Pocket Monsters Green save.
 */
void PartyScreen_RunFrame(s32 unused) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    func_8001B5F0();
    func_800158C0();
    PartyScreen_Draw(&sPartyScreen);
    PartyScreen_Update(&sPartyScreen);
}

/**
 * Fragment entry for the てもち (party) screen: pushes the 'VIEW' pool state, loads the font,
 * the move-type backdrop archive, the model preview and the icon list, runs the screen with a fade
 * in and out, then queues the main menu fragment.
 * Seen in play (2026-11-14): ran on はい at the main menu's てもち prompt.
 */
s32 PartyScreen_Init(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {
    s32 i;

    main_pool_push_state('VIEW');
    Font_Init(0x1C, 0);
    sMoveBackdropArchive = BinArchive_Open(D_003DCB60, D_003F53C0, 1, 1);
    D_8A21DA48 = (ModelLoadContext*)PokeIcon_AllocFramebuffers(1);
    sPartyModelPreview = (s32)PokeIcon_CreateModelPreview(D_8A21DA48, 0x100, 0xD2, 0, 0, 0xF4, 0xD2, D_8A203438);
    sPartyIconList = (s8*)PokeIcon_CreateRenderList(D_8A21DA48, 6, 0x28, 0x28);
    PokeIcon_OpenModelArchives();

    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);

    D_8A21DA58 = main_pool_alloc(0x3000, 0);
    for (i = 0; i < 4; i++) {
        sMoveBackdropPools[i] = main_pool_alloc(0x14800, 0);
    }

    PartyScreen_Load();
    StageLoader_UpdateSegments();
    BgStage_RunUntilCondition(8, PartyScreen_FadeFrame);
    BgStage_RunUntilCondition(0, (s32 (*)(u8))PartyScreen_RunFrame);
    BgStage_RunUntilCondition(8, PartyScreen_FadeFrame);
    StageLoader_WaitForRetrace();
    Font_Free();
    main_pool_pop_state('VIEW');
    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
