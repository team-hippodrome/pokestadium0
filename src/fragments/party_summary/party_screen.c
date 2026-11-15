/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "party_summary.h"
#include "audio_commands.h"
#include "font.h"
#include "gb_save.h"
#include "graphics_textures.h"
#include "input.h"
#include "ui_graphics.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK Menu_DrawItems(s8 *, s32, s32, M2C_UNK, s32);
M2C_UNK Menu_Init(s8 *, s32, s8 *, M2C_UNK *, s32, s32);
M2C_UNK Ui_DrawTexturedDivider(s32, s32, s32, M2C_UNK *);
extern Entry80066AA0 D_80066AA0[];
extern M2C_UNK D_800734A8;
extern s8 *D_800603C0;
extern s8 D_8007356C;
s32 Window_DrawAnimatedFrame();
s32 Pokemon_GetTypeIndex(s32, s32);
s32 func_8001FA30(u8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void func_8001A384(s32, s32);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001AAE4(s32, s32, s32, s32);
void func_8001AB6C(void);
void func_8001ABBC(void);
void func_8001ABE8(void);
void func_8001AC3C(void);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);

extern Entry80066AA0 D_80066AA0[];
extern Entry80066AA0 D_80066AA8;
extern M2C_UNK D_800734A8;
extern char D_8A21D850[];
extern char D_8A21D854[];
extern char D_8A21D858[];
extern s8* sPartyIconList;
extern Color_RGBA8 D_8A203304;
extern Entry80066AD8 D_80066AD8[];
extern Gfx D_80060270[];
extern s32 sPartyGbPort;
extern s32 D_8A21DE08;
extern M2C_UNK D_8A21DE10;
extern M2C_UNK sPartyScreen;

/**
 * Draws the status condition name in its color, or ひんし (fainted) when HP is 0.
 * Seen in play (2026-11-14): どく in purple for a poisoned Bulbasaur, ひんし for a Charmander at 0 HP,
 * ふつう (no status) for the rest, on the party rows and the つよさをみる page.
 */
void MonSummary_DrawStatusCondition(s32 x, s32 y, BattleMon* mon) {
    Entry80066AA0* e;

    if (mon->hp == 0) {
        e = &D_80066AA8;
    } else {
        e = &D_80066AA0[func_8001FA30(mon->statusCondition)];
    }
    Gfx_SetEnvColor(e->r, e->g, e->b, 0xFF);
    Font_Printf(x, y, e->str);
}

/**
 * Draws one party row's text: nickname, HP:, the HP bar, L%d, %3d/%3d and the status.
 * Seen in play (2026-11-14): ハナ どく L8 25/ 25 on the first てもち row.
 */
void PartyScreen_DrawRowText(s32 x, s32 y, BattleMon* mon, s32 flags) {
    BattleHud_DrawHpBarTexture(x + 0x16D, y + 9, 0x94, mon->hp, mon->maxHp);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 0x4C, y + 0xD, mon->nickname);
    Gfx_SetEnvColor(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    Font_SetActive(4, 0);
    Font_Printf(x + 0x13B, y + 6, D_8A21D850);
    Font_SetActive(8, 0);
    Font_Printf(x + 0x11B, y + 0x19, D_8A21D854, mon->level);
    Font_Printf(x + 0x175, y + 0x19, D_8A21D858, mon->hp, mon->maxHp);
    MonSummary_DrawStatusCondition(x + 0xD4, y + 0x19, mon);
    Font_EndTexturedTextRendering();
}

/**
 * Draws the party Pokémon icon in `slot` of the icon render list (40x40 RGBA16).
 * Seen in play (2026-11-14): ran for the icons left of each てもち row.
 */
void PartyScreen_DrawIcon(s32 x, s32 y, s32 slot) {
    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(x, y, 0x28, 0x28, ((PokeIconRenderer*)sPartyIconList)->slots[slot].image->img_p, 0x28, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

extern Color_RGBA8 D_8A203304;
extern Color_RGBA8 D_8A203348;
extern Color_RGBA8 D_80073520;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
/**
 * Menu row callback for the てもち list: the row highlight, PartyScreen_DrawRowText and the
 * cursor frame. `*modePtr` is PartyScreen_DrawList's mode; mode 2 (reordering) frames the cursor in
 * another color. Seen in play (2026-11-14): one call per party Pokémon.
 */
void PartyScreen_DrawListRow(s32 x, s32 y, BattleMon *mon, s32 index, s32 flags, s32 *mode_ptr) {
    s32 pad[3]; // FAKE: stack padding
    s32 kind = *mode_ptr;
    Color_RGBA8 *color;

    if (flags & 0x18) {
        Ui_FillRectHighlighted(x + 3, y + 3, 0x20F, 0x2D, D_8A203304);
    }
    PartyScreen_DrawRowText(x, y, mon, flags);
    if (flags & 0x12) {
        if (kind == 2) {
            color = &D_8A203348;
        } else {
            color = &D_80073520;
        }
        Ui_DrawRoundedFrame(x + 2, y + 2, 0x211, 0x2F, *color);
    }
}

/**
 * Sets up the てもち list window (545x360) and its menu of PartyScreen_DrawListRow rows over `monList`.
 * Seen in play (2026-11-14): ran once from PartyScreen_SetupList when the てもち screen opened.
 */
void PartyScreen_InitList(PartyListWindow* window, s32 x, s32 y, s32 mon_list) {
    Window_SetRect((s8*)window, x, y, 0x221, 0x168);
    window->window.animTimer = 0;
    window->window.title = NULL;
    window->window.state = 0;
    window->window.frame.style = 0x1001;
    Menu_Init((s8*)&window->menu, mon_list, (s8*)window->itemFlags, (M2C_UNK *)PartyScreen_DrawListRow, 0x215, 0x33);
}

extern s8 D_8007356C;
extern Color_RGBA8 D_8A20334C;
extern Color_RGBA8 D_8A203350;
extern Color_RGBA8 D_8A203354;
extern char* D_8A203358;
extern char* D_8A20335C;
void Ui_FillRectPrimEnvColor(s32 x, s32 y, s32 w, s32 h, Color_RGBA8 prim, Color_RGBA8 env);
void func_800189C0(s8*, s32);
void BgStage_DrawFrame(void);
/**
 * Draws the てもち list window: footer bar, row backgrounds, the rows and the icons. `mode` is
 * 0 for the list, 1 while the action menu is open and 2 while picking the second Pokémon of ならびかえ
 * (footer text and highlights change). Seen in play (2026-11-14): the list with
 * 「ポケモンを えらんで ください」.
 */
void PartyScreen_DrawList(PartyListWindow* window, s32 mode) {
    s32 flags = 0xFFED;
    s32 i;
    s32 x;
    s32 y;

    if ((window->window.state != 2) && (Window_DrawAnimatedFrame() == 0)) {
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + 0x137, window->window.frame.width, &D_8007356C);
        Ui_FillRectPrimEnvColor(window->window.frame.x + 6, window->window.frame.y + 0x13E, window->window.frame.width - 0xC, 0x24, D_8A203350, D_8A203354);
        func_8001AB6C();
        func_8001A384(0x10, 0);
        Font_Printf(window->window.frame.x + 0x36, window->window.frame.y + 0x144, (mode == 2) ? D_8A20335C : D_8A203358);
        func_8001ABBC();

        x = window->window.frame.x + 6;
        y = window->window.frame.y + 6;
        for (i = 0; i < 6; i++) {
            gSPDisplayList(gDisplayListHead++, D_80060270);
            func_80029028(x, y + 1, window->menu.cellWidth, window->menu.cellHeight, D_8A203304);
            func_80029028(x, y, window->menu.cellWidth, 1, D_8A20334C);
            func_80029028(x, (y + window->menu.cellHeight) - 1, window->menu.cellWidth, 1, D_8A20334C);
            y += window->menu.cellHeight;
        }

        switch (mode) {
            case 0:
            case 2:
                flags = 0xFFEF;
                break;
            case 1:
                flags = 0xFFFD;
                break;
        }
        Menu_DrawItems((s8*)&window->menu, window->window.frame.x + 6, window->window.frame.y + 6, flags, (s32)&mode);
    }

    if ((window->window.state == 1) || (window->window.state == 2)) {
        func_800189C0(sPartyIconList, 0);
        BgStage_DrawFrame();
        x = window->window.frame.x + 6;
        y = window->window.frame.y + 6;
        for (i = 0; i < window->menu.items->count; i++) {
            if (((mode == 1) && (i == window->menu.cursor)) ||
                ((mode == 2) && (window->menu.itemFlags[i] & 8))) {
                Ui_FillRectHighlighted(x + 0x14, y + 5, 0x28, 0x28, D_8A203304);
            } else {
                gSPDisplayList(gDisplayListHead++, D_80060270);
                func_80029028(x + 0x14, y + 5, 0x28, 0x28, D_8A203304);
            }
            PartyScreen_DrawIcon(x + 0x14, y + 5, i);
            y += window->menu.cellHeight;
        }
    }
}

/**
 * Menu row callback for the action menu: one label with the selection highlight.
 * Seen in play (2026-11-14): drew つよさをみる / ならびかえ / やめる.
 */
void PartyScreen_DrawActionMenuRow(s32 x, s32 y, char* label, s32 index, s32 flags) {
    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 0xA2, 0x1E, D_8A203304);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 0xC, y + 6, label);
    Font_EndTexturedTextRendering();
}

extern u8 D_8A203364[];
s32 BattleMon_CountMoves(u8* arg0);
void func_80027804(s8*, void*, s32, s32);
/**
 * Sets up the action menu window (180x132) for `mon`: つよさをみる / ならびかえ / やめる.
 * つよさをみる is disabled (item flag bit 0) for an invalid species or a Pokémon with no moves.
 * Seen in play (2026-11-14): opened by A on a party Pokémon. With Pikachu's moves poked to 0 in RAM,
 * A on つよさをみる did nothing and the screen stayed in state 2.
 */
void PartyScreen_InitActionMenu(PartyActionMenuWindow* window, s32 x, s32 y, u8* mon)
{
  s32* new_var; // FAKE: permuter temp
  s8 *sp2C;
  Window_SetRect((s8*)window, x, y, 0xB4, 0x84);
  window->window.animTimer = 0;
  new_var = &window->window.state;
  window->window.title = NULL;
  *new_var = 0;
  window->window.frame.style = 0;
  window->window.frame.color = D_8A203304;
  sp2C = (s8*)&window->items;
  func_80027804(sp2C, D_8A203364, 3, 3);
  Menu_Init((s8*)&window->menu, sp2C, (s8*)window->itemFlags, (M2C_UNK *) PartyScreen_DrawActionMenuRow, 0xA8, 0x24);
  if ((!window) && (!window))
  {
  }
  window->menu.options |= 0x10000;
  if (((mon[0] > 0) && (mon[0] < 0x98)) && (BattleMon_CountMoves(mon) != 0))
  {
    return;
  }
  *window->menu.itemFlags |= 1;
}

/**
 * Draws the action menu window's items.
 * Seen in play (2026-11-14): drew the つよさをみる / ならびかえ / やめる menu.
 */
void PartyScreen_DrawActionMenu(PartyActionMenuWindow* window) {
    if (Window_DrawAnimatedFrame() == 0) {
        Menu_DrawItems((s8*)&window->menu, window->window.frame.x + 6, window->window.frame.y + 0xC, 0xFEF, 0);
    }
}

extern s8 *D_800603C0;
M2C_UNK Audio_PlaySystemSound(M2C_UNK);
s32 Menu_UpdateCursor(s8*);
s32 func_8002BC14(s32);
/**
 * Action menu input: moves the cursor and returns the picked row + 1, -1 for B, else 0.
 * A disabled row (item flag bit 0) plays sound 8 and returns 0.
 * Seen in play (2026-11-14): returned the pick for つよさをみる and ならびかえ.
 */
s32 PartyScreen_UpdateActionMenu(PartyActionMenuWindow* window) {
    s32 sp1C = 0;
    s32 dir;
    s32 idx;

    if (Menu_UpdateCursor((s8*)&window->menu) == 0) {
        dir = func_8002BC14((s32)D_800603C0);
        if (dir == -1) {
            sp1C = -1;
        } else if (dir == 1) {
            idx = window->menu.cursor;
            if (!(window->menu.itemFlags[idx] & 1)) {
                sp1C = idx + 1;
            } else {
                Audio_PlaySystemSound(8);
            }
        }
    }
    return sp1C;
}

extern char D_8A21D8BC[];
extern char D_8A21D8C8[];
extern char D_8A21D8D4[];
extern char D_8A21D8E0[];
extern char D_8A21D8EC[];
extern char D_8A21D8F0[];
extern char D_8A21D8F4[];
extern char D_8A21D8F8[];
/**
 * Draws Attack, Defense, Speed and Special.
 * Seen in play (2026-11-14): こうげき 19, ぼうぎょ 12, すばやさ 25, とくしゅ 16 for the save's Pikachu.
 */
void MonSummary_DrawStats(s32 x, s32 y, BattleMon* mon) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0xF4, 0x86, D_8A203304);
    func_8001AB6C();
    func_8001A384(0x10, 0);
    func_8001AA9C(0xFF, 0xC8, 0xC8, 0xFF);
    Font_Printf(x + 0xE, y + 7, D_8A21D8BC);
    Font_Printf(x + 0xE, y + 0x27, D_8A21D8C8);
    Font_Printf(x + 0xE, y + 0x47, D_8A21D8D4);
    Font_Printf(x + 0xE, y + 0x67, D_8A21D8E0);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    Font_Printf(x + 0x9E, y + 7, D_8A21D8EC, mon->attack);
    Font_Printf(x + 0x9E, y + 0x27, D_8A21D8F0, mon->defense);
    Font_Printf(x + 0x9E, y + 0x47, D_8A21D8F4, mon->speed);
    Font_Printf(x + 0x9E, y + 0x67, D_8A21D8F8, mon->special);
    func_8001ABBC();
}

extern char D_8A21D8FC[];
extern char D_8A21D904[];
extern char D_8A21D908[];
extern char D_8A21D90C[];
extern char D_8A21D914[];
/**
 * Draws the つよさをみる page header: No.%03d, nickname, L%d, HP %3d/%3d with its bar and じょうたい/.
 * Seen in play (2026-11-14): No.025 ナシ L12, HP 30/ 30, じょうたい/ ふつう.
 */
void MonSummary_DrawHeader(s32 x, s32 y, BattleMon* mon) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x122, 0x90, D_8A203304);
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    Font_EnableTwoCycleTexturing();
    func_8001A384(0x10, 0);
    Gfx_SetPrimColor(0x5A, 0x6B, 0xFF, 0xFF);
    Font_Printf(x + 0x25, y + 0x1E, mon->nickname);
    Font_DisableTwoCycleTexturing();
    func_8001A384(8, 0);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    Font_Printf(x + 9, y + 6, D_8A21D8FC, mon->species.id);
    Font_Printf(x + 0xC9, y + 0x21, D_8A21D904, mon->level);
    Font_Printf(x + 0x45, y + 0x44, D_8A21D908);
    Font_Printf(x + 0x8D, y + 0x58, D_8A21D90C, mon->hp, mon->maxHp);
    func_8001AA9C(0xFF, 0xC7, 0xC7, 0xFF);
    Font_Printf(x + 0x23, y + 0x74, D_8A21D914);
    MonSummary_DrawStatusCondition(x + 0xAF, y + 0x74, mon);
    func_8001ABBC();
    BattleHud_DrawHpBarTexture(x + 0x85, y + 0x48, 0x94, mon->hp, mon->maxHp);
}

/**
 * Draws the name of the species' type 1 or 2 (`typeSlot`) in its type color at `fontSize`;
 * nothing for a missing type 2. Seen in play (2026-11-14): でんき for Pikachu on both pages.
 */
void MonSummary_DrawTypeName(s32 x, s32 y, s32 font_size, s32 mon, s32 type_slot) {
    Color82000BC4 c;
    s32 idx = Pokemon_GetTypeIndex(mon, type_slot);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(font_size, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        Font_Printf(x, y, D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

extern Color_RGBA8 D_8A203370;
extern Color_RGBA8 D_8A203374;
extern char D_8A21D920[];
extern char D_8A21D92C[];
extern char D_8A21D938[];
extern char D_8A21D940[];
extern char D_8A21D950[];
extern char D_8A21D95C[];
extern char D_8A21D964[];
extern char D_8A21D968[];
extern char D_8A21D96C[];
extern char D_8A21D974[];
extern char D_8A21D978[];
extern char D_8A21D97C[];
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
s32 MonSummary_GetExpForLevel(s32, s32);
/**
 * Draws タイプ1/2, ID No., おやのなまえ (OT name), けいけんち (Exp) and the Exp to the next level.
 * Seen in play (2026-11-14): タイプ1/ でんき, ID No./ 12345, おやのなまえ/ サトシ, けいけんち/ 1728 and
 * あと 469で L13 for the save's Pikachu.
 */
void MonSummary_DrawTrainerInfo(s32 x, s32 y, s32 mon) {
    s32 next_level;
    s32 to_next;

    if (((BattleMon*)mon)->level == 100) {
        next_level = 100;
    } else {
        next_level = ((BattleMon*)mon)->level + 1;
    }
    to_next = MonSummary_GetExpForLevel(((BattleMon*)mon)->species.id, next_level) - ((BattleMon*)mon)->exp;
    Ui_FillRectPrimEnvColor(x, y, 0x122, 0xC8, D_8A203370, D_8A203374);
    func_8001AB6C();
    func_8001A384(8, 0);
    func_8001AA9C(0xFF, 0xDA, 0xC7, 0xFF);
    Font_Printf(x + 0x37, y + 0xC, D_8A21D920);
    if (Pokemon_GetTypeIndex(mon, 1) != -1) {
        Font_Printf(x + 0x37, y + 0x28, D_8A21D92C);
    }
    func_8001AA9C(0xFF, 0xFF, 0xC7, 0xFF);
    Font_Printf(x + 0xF, y + 0x4C, D_8A21D938);
    func_8001AA9C(0xED, 0xFF, 0xC7, 0xFF);
    Font_Printf(x + 0xF, y + 0x68, D_8A21D940);
    func_8001AA9C(0xDA, 0xFF, 0xC7, 0xFF);
    Font_Printf(x + 0xF, y + 0x8C, D_8A21D950);
    func_8001AA9C(0xC7, 0xFF, 0xDA, 0xFF);
    Font_Printf(x + 0xF, y + 0xA8, D_8A21D95C);
    Font_Printf(x + 0xA5, y + 0xA8, D_8A21D964);
    Font_Printf(x + 0xC3, y + 0xA8, D_8A21D968);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    Font_Printf(x + 0xAF, y + 0x4C, D_8A21D96C, ((BattleMon*)mon)->otId);
    Font_Printf(x + 0xAF, y + 0x68, (char*)mon + 0x40);
    Font_Printf(x + 0x87, y + 0x8C, D_8A21D974, ((BattleMon*)mon)->exp);
    Font_Printf(x + 0x40, y + 0xA8, D_8A21D978, to_next);
    Font_Printf(x + 0xD7, y + 0xA8, D_8A21D97C, next_level);
    func_8001ABBC();
    MonSummary_DrawTypeName(x + 0xAF, y + 0xC, 8, mon, 0);
    MonSummary_DrawTypeName(x + 0xAF, y + 0x28, 8, mon, 1);
}

typedef struct Entry8006A9D4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry8006A9D4; // size = 0xC
extern Entry8006A9D4 D_8006A9D4[];
typedef struct Entry8A203384 {
    /* 0x00 */ s32 boxX;
    /* 0x04 */ s32 boxY;
    /* 0x08 */ s32 nameX;
    /* 0x0C */ s32 nameY;
    /* 0x10 */ s32 center;
    /* 0x14 */ s32 ppX;
    /* 0x18 */ s32 ppY;
    /* 0x1C */ s32 iconX;
    /* 0x20 */ s32 iconY;
    /* 0x24 */ s32 icon;
} Entry8A203384; // size = 0x28
extern Entry8A203384 D_8A203384[];
extern Color_RGBA8 D_8A203378;
extern Color_RGBA8 D_8A20337C;
extern char D_8A21D980[];
extern char D_8A21D990[];
void Ui_DrawImageInStrips(s32, s32, s32);

s32 BattleMon_GetMoveIndex(u8*, s32);
u32 func_800566BC(const char*);
/**
 * Draws the moves page's move list: each move name in its type color with PP cur/max,
 * laid out by the C button that picks it, and a frame on `selectedSlot`. Max PP adds
 * min(pp / 5, 7) per PP Up (top 2 bits of the PP byte).
 * Seen in play (2026-11-14): でんきショック 30/48 (3 PP Ups), なきごえ 40/47 (1 PP Up),
 * でんこうせっか 30/30, でんじは 20/20; C-Right moved the frame to なきごえ.
 */
void MonSummary_DrawMoveList(s32 baseX, s32 baseY, s32 mon, s32 selected_slot) {
    s32 pad; // FAKE
    s32 count;
    s32 pad2; // FAKE
    Color82000BC4 c;
    const char* str;
    s32 hl;
    s32 move;
    s32 x;
    s32 i;
    s32 step;
    s32 cur;
    s32 max;

    Ui_FillRectPrimEnvColor(baseX, baseY, 0x21C, 0x86, D_8A203378, D_8A20337C);
    count = BattleMon_CountMoves((u8*)mon);
    for (i = 0; i < count; i++) {
        hl = 0;
        if (selected_slot == i) {
            Ui_DrawRoundedFrame(D_8A203384[i].boxX + baseX, D_8A203384[i].boxY + baseY, 0xD0, 0x30, D_80073520);
            hl = 2;
        }
        Ui_DrawImageInStrips(D_8A203384[i].icon, D_8A203384[i].iconX + baseX, D_8A203384[i].iconY + baseY);
        move = BattleMon_GetMoveIndex((u8*)mon, i);
        func_8001AB6C();
        if (move == -2) {
            str = D_8A21D980;
            func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
        } else {
            c = D_80066AD8[D_8006A9D4[move].type].color;
            func_8001AA9C(c.r, c.g, c.b, c.a);
            str = D_8006A9D4[move].name;
        }
        func_8001A384(8, 0);
        x = D_8A203384[i].nameX + baseX;
        if (D_8A203384[i].center) {
            x = x - (func_800566BC(str) >> 1) * 0x14 + 0x8C;
        }
        Font_Printf(x, D_8A203384[i].nameY + baseY, str);
        func_8001ABBC();
        if (move != -2) {
            cur = ((u8*)mon)[i + 0x20];
            step = gMoveData[move].pp / 5;
            if (step >= 7) {
                step = 7;
            }
            max = gMoveData[move].pp + step * (cur >> 6);
            func_8001AB6C();
            func_8001A384(4, 0);
            Font_SetColorForFlags(hl);
            Font_Printf(D_8A203384[i].ppX + baseX, D_8A203384[i].ppY + baseY, D_8A21D990, cur & 0x3F, max);
            func_8001ABBC();
        }
    }
}


/**
 * Draws the moves page header: No.%03d, species name, L%d and タイプ 1/2.
 * Seen in play (2026-11-14): No.025 ピカチュウ L12 タイプ 1/でんき after A on the つよさをみる page.
 */
void MonSummary_DrawMovesHeader(s32 x, s32 y, BattleMon* mon) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x122, 0x4E, D_8A203304);
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8001ABE8();
    func_8001A384(0x10, 0);
    func_8001AAE4(0x5A, 0x6B, 0xFF, 0xFF);
    Font_Printf(x + 0x25, y + 0x1E, *(char**)D_80064C44[mon->species.id]);
    func_8001AC3C();
    func_8001A384(8, 0);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    Font_Printf(x + 9, y + 6, "No.%03d", mon->species.id);
    Font_Printf(x + 0xC9, y + 0x21, "L%d", mon->level);
    func_8001A384(4, 0);
    Font_Printf(x + 9, y + 0x3C, "タイプ"); // "Type"
    Font_Printf(x + 0x4F, y + 0x3C, "1/");
    if (Pokemon_GetTypeIndex((s32)mon, 1) != -1) {
        Font_Printf(x + 0xB9, y + 0x3C, "2/");
    }
    MonSummary_DrawTypeName(x + 0x6F, y + 0x3C, 4, (s32)mon, 0);
    MonSummary_DrawTypeName(x + 0xD9, y + 0x3C, 4, (s32)mon, 1);
    func_8001ABBC();
}
