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
s32 Particle_Field50_SetXZFromField7C_09BB4();
s32 Pokemon_GetTypeIndex(s32, s32);
s32 func_8001FA30(u8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void func_8001A384(s32, s32);
void func_8001A944(s32, s32, const char*, ...);
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
extern s8* D_8A21DA50;
extern Color_RGBA8 D_8A203304;
extern Entry80066AD8 D_80066AD8[];
extern Gfx D_80060270[];
extern s32 D_8A21DA40;
extern s32 D_8A21DE08;
extern M2C_UNK D_8A21DE10;
extern M2C_UNK D_8A21DA80;

/**
 * Draws the status condition name in its color (the fainted entry when HP is 0).
 * Seen in play (2026-11-12): ふつう (no status) on the party rows and on the summary page.
 */
void MonSummary_DrawStatusCondition(s32 arg0, s32 arg1, BattleMon* arg2) {
    Entry80066AA0* e;

    if (arg2->hp == 0) {
        e = &D_80066AA8;
    } else {
        e = &D_80066AA0[func_8001FA30(arg2->statusCondition)];
    }
    Gfx_SetEnvColor(e->r, e->g, e->b, 0xFF);
    Font_Printf(arg0, arg1, e->str);
}

/**
 * Draws HP:, L%d and %3d/%3d.
 * Seen in play (2026-11-12): HP: and L5 19/ 19 on the party rows.
 */
void PartyScreen_DrawHpLevel(s32 arg0, s32 arg1, BattleMon* arg2, s32 arg3) {
    BattleHud_DrawHpBarTexture(arg0 + 0x16D, arg1 + 9, 0x94, arg2->hp, arg2->maxHp);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg3);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0x4C, arg1 + 0xD, arg2->nickname);
    Gfx_SetEnvColor(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    Font_SetActive(4, 0);
    Font_Printf(arg0 + 0x13B, arg1 + 6, D_8A21D850);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x11B, arg1 + 0x19, D_8A21D854, arg2->level);
    Font_Printf(arg0 + 0x175, arg1 + 0x19, D_8A21D858, arg2->hp, arg2->maxHp);
    MonSummary_DrawStatusCondition(arg0 + 0xD4, arg1 + 0x19, arg2);
    Font_EndTexturedTextRendering();
}

/** Draws an RGBA16 texture at a position. */
void UI_DrawTextureRgba16(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(arg0, arg1, 0x28, 0x28, ((PokeIconRenderer*)D_8A21DA50)->slots[arg2].image->img_p, 0x28, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

extern Color_RGBA8 D_8A203304;
extern Color_RGBA8 D_8A203348;
extern Color_RGBA8 D_80073520;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
/**
 * Draws a Pokemon list row with its HP and level; highlights it for the selection flags.
 * Seen in play (2026-11-12): one row per party Pokemon (icon, nickname, status, level, HP bar).
 */
void PartyScreen_DrawListRow(s32 arg0, s32 arg1, BattleMon *arg2, s32 arg3, s32 arg4, s32 *arg5) {
    s32 pad[3]; // FAKE: stack padding
    s32 kind = *arg5;
    Color_RGBA8 *color;

    if (arg4 & 0x18) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0x20F, 0x2D, D_8A203304);
    }
    PartyScreen_DrawHpLevel(arg0, arg1, arg2, arg4);
    if (arg4 & 0x12) {
        if (kind == 2) {
            color = &D_8A203348;
        } else {
            color = &D_80073520;
        }
        Ui_DrawRoundedFrame(arg0 + 2, arg1 + 2, 0x211, 0x2F, *color);
    }
}

/**
 * Sets up the Pokemon list window (545x360) and its menu of PartyScreen_DrawListRow rows.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void PartyScreen_InitList(PartyListWindow* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Window_SetRect((s8*)arg0, arg1, arg2, 0x221, 0x168);
    arg0->window.animTimer = 0;
    arg0->window.title = NULL;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x1001;
    Menu_Init((s8*)&arg0->menu, arg3, (s8*)arg0->itemFlags, (M2C_UNK *)PartyScreen_DrawListRow, 0x215, 0x33);
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
 * Draws the Pokemon list window: divider, footer bar and the rows.
 * Seen in play (2026-11-12): the party list window with the footer 「ポケモンを えらんで ください」.
 */
void PartyScreen_DrawList(PartyListWindow* arg0, s32 arg1) {
    s32 flags = 0xFFED;
    s32 i;
    s32 x;
    s32 y;

    if ((arg0->window.state != 2) && (Particle_Field50_SetXZFromField7C_09BB4() == 0)) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x137, arg0->window.frame.width, &D_8007356C);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + 0x13E, arg0->window.frame.width - 0xC, 0x24, D_8A203350, D_8A203354);
        func_8001AB6C();
        func_8001A384(0x10, 0);
        func_8001A944(arg0->window.frame.x + 0x36, arg0->window.frame.y + 0x144, (arg1 == 2) ? D_8A20335C : D_8A203358);
        func_8001ABBC();

        x = arg0->window.frame.x + 6;
        y = arg0->window.frame.y + 6;
        for (i = 0; i < 6; i++) {
            gSPDisplayList(gDisplayListHead++, D_80060270);
            func_80029028(x, y + 1, arg0->menu.cellWidth, arg0->menu.cellHeight, D_8A203304);
            func_80029028(x, y, arg0->menu.cellWidth, 1, D_8A20334C);
            func_80029028(x, (y + arg0->menu.cellHeight) - 1, arg0->menu.cellWidth, 1, D_8A20334C);
            y += arg0->menu.cellHeight;
        }

        switch (arg1) {
            case 0:
            case 2:
                flags = 0xFFEF;
                break;
            case 1:
                flags = 0xFFFD;
                break;
        }
        Menu_DrawItems((s8*)&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 6, flags, (s32)&arg1);
    }

    if ((arg0->window.state == 1) || (arg0->window.state == 2)) {
        func_800189C0(D_8A21DA50, 0);
        BgStage_DrawFrame();
        x = arg0->window.frame.x + 6;
        y = arg0->window.frame.y + 6;
        for (i = 0; i < arg0->menu.items->count; i++) {
            if (((arg1 == 1) && (i == arg0->menu.cursor)) ||
                ((arg1 == 2) && (arg0->menu.itemFlags[i] & 8))) {
                Ui_FillRectHighlighted(x + 0x14, y + 5, 0x28, 0x28, D_8A203304);
            } else {
                gSPDisplayList(gDisplayListHead++, D_80060270);
                func_80029028(x + 0x14, y + 5, 0x28, 0x28, D_8A203304);
            }
            UI_DrawTextureRgba16(x + 0x14, y + 5, i);
            y += arg0->menu.cellHeight;
        }
    }
}

/**
 * Draws one menu row label with the selection highlight.
 * Seen in play (2026-11-12): one row of that menu.
 */
void PartyScreen_DrawActionMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xA2, 0x1E, D_8A203304);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, arg1 + 6, arg2);
    Font_EndTexturedTextRendering();
}

extern u8 D_8A203364[];
s32 BattleMon_CountMoves(u8* arg0);
void func_80027804(s8*, void*, s32, s32);
/**
 * Sets up the small menu window (180x132).
 * Seen in play (2026-11-12): opens when a party Pokemon is picked: つよさをみる / ならびかえ / やめる.
 */
void PartyScreen_InitActionMenu(PartyActionMenuWindow* arg0, s32 arg1, s32 arg2, u8* arg3)
{
  s32* new_var; // FAKE: permuter temp
  s8 *sp2C;
  Window_SetRect((s8*)arg0, arg1, arg2, 0xB4, 0x84);
  arg0->window.animTimer = 0;
  new_var = &arg0->window.state;
  arg0->window.title = NULL;
  *new_var = 0;
  arg0->window.frame.style = 0;
  arg0->window.frame.color = D_8A203304;
  sp2C = (s8*)&arg0->items;
  func_80027804(sp2C, D_8A203364, 3, 3);
  Menu_Init((s8*)&arg0->menu, sp2C, (s8*)arg0->itemFlags, (M2C_UNK *) PartyScreen_DrawActionMenuRow, 0xA8, 0x24);
  if ((!arg0) && (!arg0))
  {
  }
  arg0->menu.options |= 0x10000;
  if (((arg3[0] > 0) && (arg3[0] < 0x98)) && (BattleMon_CountMoves(arg3) != 0))
  {
    return;
  }
  *arg0->menu.itemFlags |= 1;
}

/**
 * Draws the menu window's items.
 * Seen in play (2026-11-12): draws the つよさをみる / ならびかえ / やめる menu.
 */
void PartyScreen_DrawActionMenu(PartyActionMenuWindow* arg0) {
    if (Particle_Field50_SetXZFromField7C_09BB4() == 0) {
        Menu_DrawItems((s8*)&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 0xC, 0xFEF, 0);
    }
}

extern s8 *D_800603C0;
M2C_UNK func_8003F6AC(M2C_UNK);
s32 Menu_UpdateCursor(s8*);
s32 func_8002BC14(s32);
/**
 * Menu-list input handler (same pattern as FreeBattle_UpdatePopupMenu / LabTerminal_UpdateMenuWindow). Does nothing and
 * returns 0 while Menu_UpdateCursor(arg0 + 0x2C) is non-zero. Otherwise reads the input result
 * from func_8002BC14(D_800603C0): -1 returns -1; 1 looks at the entry for the cursor index
 * stored at arg0 + 0x34 in the halfword table pointed to by arg0 + 0x30 -- if bit 0 of that
 * entry is clear it returns index + 1, if set it plays sound effect func_8003F6AC(8) and
 * returns 0; any other result returns 0. (What the table bit means -- likely "disabled"
 * -- is inferred from the sound call only.)
 * Seen in play (2026-11-12): moves the cursor over つよさをみる / ならびかえ / やめる and returns the pick.
 */
s32 PartyScreen_UpdateActionMenu(PartyActionMenuWindow* arg0) {
    s32 sp1C = 0;
    s32 dir;
    s32 idx;

    if (Menu_UpdateCursor((s8*)&arg0->menu) == 0) {
        dir = func_8002BC14((s32)D_800603C0);
        if (dir == -1) {
            sp1C = -1;
        } else if (dir == 1) {
            idx = arg0->menu.cursor;
            if (!(arg0->menu.itemFlags[idx] & 1)) {
                sp1C = idx + 1;
            } else {
                func_8003F6AC(8);
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
 * Seen in play (2026-11-12): こうげき/ぼうぎょ/すばやさ/とくしゅ with the save's stat values.
 */
void MonSummary_DrawStats(s32 arg0, s32 arg1, BattleMon* arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0xF4, 0x86, D_8A203304);
    func_8001AB6C();
    func_8001A384(0x10, 0);
    func_8001AA9C(0xFF, 0xC8, 0xC8, 0xFF);
    func_8001A944(arg0 + 0xE, arg1 + 7, D_8A21D8BC);
    func_8001A944(arg0 + 0xE, arg1 + 0x27, D_8A21D8C8);
    func_8001A944(arg0 + 0xE, arg1 + 0x47, D_8A21D8D4);
    func_8001A944(arg0 + 0xE, arg1 + 0x67, D_8A21D8E0);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    func_8001A944(arg0 + 0x9E, arg1 + 7, D_8A21D8EC, arg2->attack);
    func_8001A944(arg0 + 0x9E, arg1 + 0x27, D_8A21D8F0, arg2->defense);
    func_8001A944(arg0 + 0x9E, arg1 + 0x47, D_8A21D8F4, arg2->speed);
    func_8001A944(arg0 + 0x9E, arg1 + 0x67, D_8A21D8F8, arg2->special);
    func_8001ABBC();
}

extern char D_8A21D8FC[];
extern char D_8A21D904[];
extern char D_8A21D908[];
extern char D_8A21D90C[];
extern char D_8A21D914[];
/**
 * Draws No.%03d, L%d, HP %3d/%3d and じょうたい/ (status).
 * Seen in play (2026-11-12): No.004, ヒノコ L5, HP 18/ 18, じょうたい/ ふつう.
 */
void MonSummary_DrawHeader(s32 arg0, s32 arg1, BattleMon* arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x122, 0x90, D_8A203304);
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    Font_EnableTwoCycleTexturing();
    func_8001A384(0x10, 0);
    Gfx_SetPrimColor(0x5A, 0x6B, 0xFF, 0xFF);
    func_8001A944(arg0 + 0x25, arg1 + 0x1E, arg2->nickname);
    Font_DisableTwoCycleTexturing();
    func_8001A384(8, 0);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    func_8001A944(arg0 + 9, arg1 + 6, D_8A21D8FC, arg2->species.id);
    func_8001A944(arg0 + 0xC9, arg1 + 0x21, D_8A21D904, arg2->level);
    func_8001A944(arg0 + 0x45, arg1 + 0x44, D_8A21D908);
    func_8001A944(arg0 + 0x8D, arg1 + 0x58, D_8A21D90C, arg2->hp, arg2->maxHp);
    func_8001AA9C(0xFF, 0xC7, 0xC7, 0xFF);
    func_8001A944(arg0 + 0x23, arg1 + 0x74, D_8A21D914);
    MonSummary_DrawStatusCondition(arg0 + 0xAF, arg1 + 0x74, arg2);
    func_8001ABBC();
    BattleHud_DrawHpBarTexture(arg0 + 0x85, arg1 + 0x48, 0x94, arg2->hp, arg2->maxHp);
}

/**
 * Draws the name of the species' type 1 or 2 in its type color; nothing for a missing type 2.
 * Seen in play (2026-11-12): ほのお for Charmander; くさ and どく for Bulbasaur.
 */
void MonSummary_DrawTypeName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Color82000BC4 c;
    s32 idx = Pokemon_GetTypeIndex(arg3, arg4);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(arg2, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(arg0, arg1, D_80066AD8[idx].str);
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
s32 func_8A20219C(s32, s32);
/**
 * Draws Type 1/2, ID No., おやのなまえ (OT name), けいけんち (Exp) and the Exp to the next level.
 * Seen in play (2026-11-12): タイプ1/2, ID No./ 12345, おやのなまえ/ サトシ, けいけんち/ 135 and あと 44で L6.
 */
void MonSummary_DrawTrainerInfo(s32 arg0, s32 arg1, s32 arg2) {
    s32 next_level;
    s32 to_next;

    if (((BattleMon*)arg2)->level == 100) {
        next_level = 100;
    } else {
        next_level = ((BattleMon*)arg2)->level + 1;
    }
    to_next = func_8A20219C(((BattleMon*)arg2)->species.id, next_level) - ((BattleMon*)arg2)->exp;
    Ui_FillRectPrimEnvColor(arg0, arg1, 0x122, 0xC8, D_8A203370, D_8A203374);
    func_8001AB6C();
    func_8001A384(8, 0);
    func_8001AA9C(0xFF, 0xDA, 0xC7, 0xFF);
    func_8001A944(arg0 + 0x37, arg1 + 0xC, D_8A21D920);
    if (Pokemon_GetTypeIndex(arg2, 1) != -1) {
        func_8001A944(arg0 + 0x37, arg1 + 0x28, D_8A21D92C);
    }
    func_8001AA9C(0xFF, 0xFF, 0xC7, 0xFF);
    func_8001A944(arg0 + 0xF, arg1 + 0x4C, D_8A21D938);
    func_8001AA9C(0xED, 0xFF, 0xC7, 0xFF);
    func_8001A944(arg0 + 0xF, arg1 + 0x68, D_8A21D940);
    func_8001AA9C(0xDA, 0xFF, 0xC7, 0xFF);
    func_8001A944(arg0 + 0xF, arg1 + 0x8C, D_8A21D950);
    func_8001AA9C(0xC7, 0xFF, 0xDA, 0xFF);
    func_8001A944(arg0 + 0xF, arg1 + 0xA8, D_8A21D95C);
    func_8001A944(arg0 + 0xA5, arg1 + 0xA8, D_8A21D964);
    func_8001A944(arg0 + 0xC3, arg1 + 0xA8, D_8A21D968);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    func_8001A944(arg0 + 0xAF, arg1 + 0x4C, D_8A21D96C, ((BattleMon*)arg2)->otId);
    func_8001A944(arg0 + 0xAF, arg1 + 0x68, (char*)arg2 + 0x40);
    func_8001A944(arg0 + 0x87, arg1 + 0x8C, D_8A21D974, ((BattleMon*)arg2)->exp);
    func_8001A944(arg0 + 0x40, arg1 + 0xA8, D_8A21D978, to_next);
    func_8001A944(arg0 + 0xD7, arg1 + 0xA8, D_8A21D97C, next_level);
    func_8001ABBC();
    MonSummary_DrawTypeName(arg0 + 0xAF, arg1 + 0xC, 8, arg2, 0);
    MonSummary_DrawTypeName(arg0 + 0xAF, arg1 + 0x28, 8, arg2, 1);
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
void func_8A2010C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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

    Ui_FillRectPrimEnvColor(arg0, arg1, 0x21C, 0x86, D_8A203378, D_8A20337C);
    count = BattleMon_CountMoves((u8*)arg2);
    for (i = 0; i < count; i++) {
        hl = 0;
        if (arg3 == i) {
            Ui_DrawRoundedFrame(D_8A203384[i].boxX + arg0, D_8A203384[i].boxY + arg1, 0xD0, 0x30, D_80073520);
            hl = 2;
        }
        Ui_DrawImageInStrips(D_8A203384[i].icon, D_8A203384[i].iconX + arg0, D_8A203384[i].iconY + arg1);
        move = BattleMon_GetMoveIndex((u8*)arg2, i);
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
        x = D_8A203384[i].nameX + arg0;
        if (D_8A203384[i].center) {
            x = x - (func_800566BC(str) >> 1) * 0x14 + 0x8C;
        }
        func_8001A944(x, D_8A203384[i].nameY + arg1, str);
        func_8001ABBC();
        if (move != -2) {
            cur = ((u8*)arg2)[i + 0x20];
            step = gMoveData[move].pp / 5;
            if (step >= 7) {
                step = 7;
            }
            max = gMoveData[move].pp + step * (cur >> 6);
            func_8001AB6C();
            func_8001A384(4, 0);
            Font_SetColorForFlags(hl);
            func_8001A944(D_8A203384[i].ppX + arg0, D_8A203384[i].ppY + arg1, D_8A21D990, cur & 0x3F, max);
            func_8001ABBC();
        }
    }
}


/**
 * Draws the species name banner.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void MonSummary_DrawSpeciesName(s32 arg0, s32 arg1, BattleMon* arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x122, 0x4E, D_8A203304);
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8001ABE8();
    func_8001A384(0x10, 0);
    func_8001AAE4(0x5A, 0x6B, 0xFF, 0xFF);
    func_8001A944(arg0 + 0x25, arg1 + 0x1E, *(char**)D_80064C44[arg2->species.id]);
    func_8001AC3C();
    func_8001A384(8, 0);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    func_8001A944(arg0 + 9, arg1 + 6, "No.%03d", arg2->species.id);
    func_8001A944(arg0 + 0xC9, arg1 + 0x21, "L%d", arg2->level);
    func_8001A384(4, 0);
    func_8001A944(arg0 + 9, arg1 + 0x3C, "タイプ"); // "Type"
    func_8001A944(arg0 + 0x4F, arg1 + 0x3C, "1/");
    if (Pokemon_GetTypeIndex((s32)arg2, 1) != -1) {
        func_8001A944(arg0 + 0xB9, arg1 + 0x3C, "2/");
    }
    MonSummary_DrawTypeName(arg0 + 0x6F, arg1 + 0x3C, 4, (s32)arg2, 0);
    MonSummary_DrawTypeName(arg0 + 0xD9, arg1 + 0x3C, 4, (s32)arg2, 1);
    func_8001ABBC();
}
