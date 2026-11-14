/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "font.h"
#include "graphics_textures.h"
#include "input.h"
#include "memmap.h"
#include "pokemon_lab_support.h"
#include "ui_graphics.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK Ui_DrawPrimColorRect(s32, s32, s32, s32, s32, s32, s32, s32);
M2C_UNK func_8001A944(s32, s32, s8*);
M2C_UNK func_8001AA9C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8001AB6C();
extern unk_D_84385790 D_80066AA0[];
u32 func_8001FA30(s32);
u32 func_800566BC(s8*);
void func_8001A384(M2C_UNK, M2C_UNK);
void func_8001ABBC(void);

/**
 * Draws a move's PP as "current/max" text left to right from (arg0, arg1). Returns the x
 * position after it.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
s32 BattleHud_DrawMovePpTextLTR(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s8 sp70[7];
    s32 i;
    u8** temp_s2;
    u8* var_v1;

    temp_s2 = Memmap_GetSegmentVaddr(D_300B870);
    sprintf(sp70, "%3d/%3d", arg2 & 0x3F, arg3);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    for (i = 0; i < 7; i++) {
        s32 c = sp70[i];

        switch (c) {
            case ' ':
                var_v1 = NULL;
                break;

            case '/':
                var_v1 = temp_s2[10];
                break;

            default:
                if ((c >= 0x30) && (c < 0x3A)) {
                    var_v1 = temp_s2[c - '0'];
                } else {
                    var_v1 = NULL;
                }
                break;
        }

        if (var_v1 != NULL) {
            func_8001B884(arg0, arg1, 8, 6, var_v1, 8, 0);
            arg0 += 8;
        }
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    return arg0;
}


/**
 * Draws a move's PP as "current/max" text right to left, ending at (arg0, arg1). Returns
 * the x position before it.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
s32 BattleHud_DrawMovePpTextRTL(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s8 sp70[7];
    s32 i;
    u8** temp_s2;
    u8* var_v1;

    temp_s2 = Memmap_GetSegmentVaddr(D_300B870);
    sprintf(sp70, "%3d/%3d", arg2 & 0x3F, arg3);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    for (i = 7; i > 0; i--) {
        s32 c = sp70[i];

        switch (c) {
            case ' ':
                var_v1 = NULL;
                break;

            case '/':
                var_v1 = temp_s2[10];
                break;

            default:
                if ((c >= 0x30) && (c < 0x3A)) {
                    var_v1 = temp_s2[c - '0'];
                } else {
                    var_v1 = NULL;
                }
                break;
        }

        if (var_v1 != NULL) {
            func_8001B884(arg0, arg1, 8, 6, var_v1, 8, 0);
            arg0 -= 8;
        }
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    return arg0;
}


typedef struct Entry8006A9D4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ char* name;
    /* 0x08 */ s32 unk_08;
} Entry8006A9D4; // size = 0xC
extern Entry8006A9D4 D_8006A9D4[];
extern u8* D_8218AF70[];
extern Gfx D_800602C8[];
extern Gfx D_80060398[];
extern char D_82195A14[];
extern char D_82195A20[];
extern char D_82195A2C[];
extern char D_82195A38[];
typedef struct MovePpInit {
    s32 pp[4];
} MovePpInit;
/**
 * Draws the move panel with names and PP. Moves not revealed yet show ？？？？？.
 */
void BattleMenu_DrawMovePanel(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 i;
    MovePpInit move_pp = { 0, 0, 0, 0 };
    u8 max_pp[4];
    BattleMon* party;
    BattleMonRuntime* runtime;

    party = &arg0->side->teamMember[arg0->thumbnail.shownTeamMemberIndex]->pokemonPicked[arg0->thumbnail.shownRosterIndex];
    runtime = &arg0->state.runtime;

    func_82116CF4(arg1 + 1, arg2 + 1, 0xC7, 0x38, &D_8218B008 + arg3 * 3, &D_8218B014 + arg3 * 3);
    if (arg1) {} // FAKE
    gSPDisplayList(gDisplayListHead++, D_800602C8);
    BattleHud_DrawBorderTile(arg1, arg2 - 1, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 5, 8, 8, D_030095C0);
    for (i = 1; i < 7; i++) {
        BattleHud_DrawBorderTile(arg1, arg2 + i * 8, 8, 8, D_030095C0);
    }
    BattleHud_DrawBorderTile(arg1, arg2 + 0x33, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0xC0, arg2 - 1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0xC0, arg2 + 5, 8, 8, D_03009740);
    for (i = 1; i < 7; i++) {
        BattleHud_DrawBorderTile(arg1 + 0xC0, arg2 + i * 8, 8, 8, D_03009740);
    }
    BattleHud_DrawBorderTile(arg1 + 0xC0, arg2 + 0x33, 8, 8, D_030097C0);
    for (i = 1; i < 24; i++) {
        BattleHud_DrawBorderTile(arg1 + i * 8, arg2 - 1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + i * 8, arg2 + 0x33, 8, 8, D_030098C0);
    }
    gSPDisplayList(gDisplayListHead++, D_80060398);

    for (i = 0; i < 4; i++) {
        if (runtime->uniqueStatusFlags & 8) {
            max_pp[i] = gMoveData[runtime->moves[i] - 1].pp / 5;
            if (max_pp[i] >= 8) {
                max_pp[i] = 7;
            }
            max_pp[i] = gMoveData[runtime->moves[i] - 1].pp + (((runtime->pp[i] & 0xC0) >> 6) * max_pp[i]);
        } else {
            max_pp[i] = gMoveData[party->moves[i] - 1].pp / 5;
            if (max_pp[i] >= 8) {
                max_pp[i] = 7;
            }
            max_pp[i] = gMoveData[party->moves[i] - 1].pp + (((party->pp[i] & 0xC0) >> 6) * max_pp[i]);
        }
    }

    if (runtime->uniqueStatusFlags & 8) {
        if (runtime->moves[0] && (runtime->moves[0] < 0xA6)) {
            move_pp.pp[0] = BattleHud_DrawMovePpTextRTL(arg1 + 0x52, arg2 + 0xF, runtime->pp[0], max_pp[0]);
        }
        if (runtime->moves[1] && (runtime->moves[1] < 0xA6)) {
            move_pp.pp[1] = BattleHud_DrawMovePpTextLTR(arg1 + 0x7C, arg2 + 0x1C, runtime->pp[1], max_pp[1]);
        }
        if (runtime->moves[2] && (runtime->moves[2] < 0xA6)) {
            move_pp.pp[2] = BattleHud_DrawMovePpTextLTR(arg1 + 0x70, arg2 + 0x30, runtime->pp[2], max_pp[2]);
        }
        if (runtime->moves[3] && (runtime->moves[3] < 0xA6)) {
            move_pp.pp[3] = BattleHud_DrawMovePpTextRTL(arg1 + 0x44, arg2 + 0x23, runtime->pp[3], max_pp[3]);
        }
    } else {
        if (party->moves[0] && (party->moves[0] < 0xA6)) {
            move_pp.pp[0] = BattleHud_DrawMovePpTextRTL(arg1 + 0x52, arg2 + 0xF, party->pp[0], max_pp[0]);
        }
        if (party->moves[1] && (party->moves[1] < 0xA6)) {
            move_pp.pp[1] = BattleHud_DrawMovePpTextLTR(arg1 + 0x7C, arg2 + 0x1C, party->pp[1], max_pp[1]);
        }
        if (party->moves[2] && (party->moves[2] < 0xA6)) {
            move_pp.pp[2] = BattleHud_DrawMovePpTextLTR(arg1 + 0x70, arg2 + 0x30, party->pp[2], max_pp[2]);
        }
        if (party->moves[3] && (party->moves[3] < 0xA6)) {
            move_pp.pp[3] = BattleHud_DrawMovePpTextRTL(arg1 + 0x44, arg2 + 0x23, party->pp[3], max_pp[3]);
        }
    }

    gSPDisplayList(gDisplayListHead++, D_80060308);

    Gfx_DrawTextureRgba16Ia8(arg1 + 0x5D, arg2 + 6, 0x10, 0xE, D_030078C0, D_03007A80, 0x10, 0x100000);
    Gfx_DrawTextureRgba16Ia8(arg1 + 0x6C, arg2 + 0x16, 0x10, 0xE, D_030070E0, D_030072A0, 0x10, 0x100000);
    Gfx_DrawTextureRgba16Ia8(arg1 + 0x5D, arg2 + 0x26, 0x10, 0xE, D_03007380, D_03007540, 0x10, 0x100000);
    Gfx_DrawTextureRgba16Ia8(arg1 + 0x4E, arg2 + 0x16, 0x10, 0xE, D_3007620, D_030077E0, 0x10, 0x100000);

    gSPDisplayList(gDisplayListHead++, D_80060398);
    gSPDisplayList(gDisplayListHead++, D_800602C8);

    if (runtime->uniqueStatusFlags & 8) {
        if (runtime->moves[0] && (runtime->moves[0] < 0xA6)) {
            func_8001B884(move_pp.pp[0] - 0x19, arg2 + 0xE, 0x20, 9, D_8218AF70[gMoveData[runtime->moves[0] - 1].type], 0x20, 0);
        }
        if (runtime->moves[1] && (runtime->moves[1] < 0xA6)) {
            func_8001B884(move_pp.pp[1], arg2 + 0x1B, 0x20, 9, D_8218AF70[gMoveData[runtime->moves[1] - 1].type], 0x20, 0);
        }
        if (runtime->moves[2] && (runtime->moves[2] < 0xA6)) {
            func_8001B884(move_pp.pp[2], arg2 + 0x2F, 0x20, 9, D_8218AF70[gMoveData[runtime->moves[2] - 1].type], 0x20, 0);
        }
        if (runtime->moves[3] && (runtime->moves[3] < 0xA6)) {
            func_8001B884(move_pp.pp[3] - 0x18, arg2 + 0x22, 0x20, 9, D_8218AF70[gMoveData[runtime->moves[3] - 1].type], 0x20, 0);
        }
    } else {
        if (runtime->moves[0] && (runtime->moves[0] < 0xA6)) {
            func_8001B884(move_pp.pp[0] - 0x19, arg2 + 0xE, 0x20, 9, D_8218AF70[gMoveData[runtime->moves[0] - 1].type], 0x20, 0);
        }
        if (runtime->moves[1] && (runtime->moves[1] < 0xA6)) {
            func_8001B884(move_pp.pp[1], arg2 + 0x1B, 0x20, 9, D_8218AF70[gMoveData[runtime->moves[1] - 1].type], 0x20, 0);
        }
        if (runtime->moves[2] && (runtime->moves[2] < 0xA6)) {
            func_8001B884(move_pp.pp[2], arg2 + 0x2F, 0x20, 9, D_8218AF70[gMoveData[runtime->moves[2] - 1].type], 0x20, 0);
        }
        if (runtime->moves[3] && (runtime->moves[3] < 0xA6)) {
            func_8001B884(move_pp.pp[3] - 0x18, arg2 + 0x22, 0x20, 9, D_8218AF70[gMoveData[runtime->moves[3] - 1].type], 0x20, 0);
        }
    }

    gSPDisplayList(gDisplayListHead++, D_80060398);

    func_8001AB6C();
    func_8001A384(1, 0);

    if (runtime->uniqueStatusFlags & 8) {
        if (runtime->moves[0] && (runtime->moves[0] < 0xA6)) { BattleHud_DrawTextCentered(arg1 + 0x5A, arg2 + 4, D_8006A9D4[runtime->moves[0] - 1].name); }
        if (runtime->moves[1] && (runtime->moves[1] < 0xA6)) {
            func_8001A944(arg1 + 0x7C, arg2 + 0x11, D_8006A9D4[runtime->moves[1] - 1].name);
        }
        if (runtime->moves[2] && (runtime->moves[2] < 0xA6)) {
            func_8001A944(arg1 + 0x6E, arg2 + 0x25, D_8006A9D4[runtime->moves[2] - 1].name);
        }
        if (runtime->moves[3] && (runtime->moves[3] < 0xA6)) {
            BattleHud_DrawTextCentered(arg1 + 0x4C, arg2 + 0x18, D_8006A9D4[runtime->moves[3] - 1].name);
        }
    } else {
        if (runtime->moves[0] && (runtime->moves[0] < 0xA6)) { BattleHud_DrawTextCentered(arg1 + 0x5A, arg2 + 4, D_8006A9D4[runtime->moves[0] - 1].name); }
        if (runtime->moves[1] && (runtime->moves[1] < 0xA6)) {
            func_8001A944(arg1 + 0x7C, arg2 + 0x11, D_8006A9D4[runtime->moves[1] - 1].name);
        }
        if (runtime->moves[2] && (runtime->moves[2] < 0xA6)) {
            func_8001A944(arg1 + 0x6E, arg2 + 0x25, D_8006A9D4[runtime->moves[2] - 1].name);
        }
        if (runtime->moves[3] && (runtime->moves[3] < 0xA6)) {
            BattleHud_DrawTextCentered(arg1 + 0x4C, arg2 + 0x18, D_8006A9D4[runtime->moves[3] - 1].name);
        }
    }

    if (runtime->moves[0] >= 0xA6) {
        BattleHud_DrawTextCentered(arg1 + 0x5A, arg2 + 4, D_82195A14);
    }
    if (runtime->moves[1] >= 0xA6) {
        func_8001A944(arg1 + 0x7C, arg2 + 0x11, D_82195A20);
    }
    if (runtime->moves[2] >= 0xA6) {
        func_8001A944(arg1 + 0x6E, arg2 + 0x25, D_82195A2C);
    }
    if (runtime->moves[3] >= 0xA6) {
        BattleHud_DrawTextCentered(arg1 + 0x4C, arg2 + 0x18, D_82195A38);
    }

    func_8001ABBC();
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 0xCD, 0x3E, 0);
}

extern u8 D_0300A500[];
extern u8 D_0300A7A0[];
extern char D_82195A44[];
extern char D_82195A58[];
extern char D_82195A60[];
/**
 * Draws こうさんしますか? (Surrender?) with いいえ (No) and はい (Yes), tinted for the trainer slot.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void BattleMenu_DrawSurrenderPrompt(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 pad; // FAKE
    s32 idx;
    s32 n;

    if (Trainer_GetSlots()[arg2].isHuman & 2) {
        idx = 4;
    } else {
        idx = arg2;
    }
    func_82116CF4(arg0 + 1, arg1 + 1, 0xC6, 0x28, idx * 3 + &D_8218B008, idx * 3 + &D_8218B014);
    func_8001AB6C();
    func_8001A384(2, 0);
    func_8001A944(arg0 + 0x2E, arg1 + 6, D_82195A44);
    func_8001A944(arg0 + 0x38, arg1 + 0x18, D_82195A58);
    func_8001A944(arg0 + 0x81, arg1 + 0x18, D_82195A60);
    func_8001ABBC();
    gSPDisplayList(gDisplayListHead++, D_80060308);
    Gfx_DrawTextureRgba16Ia8(arg0 + 0x21, arg1 + 0x17, 0x18, 0xE, D_0300A500, D_0300A7A0, 0x18, 0x100000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg0, arg1, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg0, arg1 + 6, 8, 8, D_030095C0);
    for (n = 8; n < 0x28; n += 8) {
        BattleHud_DrawBorderTile(arg0, arg1 + n, 8, 8, D_030095C0);
        BattleHud_DrawBorderTile(arg0 + 0xBE, arg1 + n, 8, 8, D_03009740);
    }
    BattleHud_DrawBorderTile(arg0, arg1 + 0x22, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg0 + 0xBE, arg1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg0 + 0xBE, arg1 + 6, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg0 + 0xBE, arg1 + 0x22, 8, 8, D_030097C0);
    for (n = 8; n < 0xC0; n += 8) {
        BattleHud_DrawBorderTile(arg0 + n, arg1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg0 + n, arg1 + 0x22, 8, 8, D_030098C0);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    BattleHud_DrawTranslucentShadowRect(arg0 - 3, arg1 - 2, 0xCC, 0x2D, 0);
}

/**
 * Draws text arg2 at (arg0, arg1) in font 1.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleHud_DrawPlainText(s16 arg0, s16 arg1, char* arg2) {
    Font_BeginTranslucentTextRendering();
    Font_SetActive(1, 0);
    Font_Printf(arg0, arg1, arg2);
    Font_EndTexturedTextRendering();
}

/**
 * Draws one row of the switch panel: level, HP bar, HP fraction and the button icon for the slot
 * (C-Up, C-Left, B, C-Right, C-Down, A for slots 0-5). Ran in play while the Pokemon menu was
 * open.
 */
void BattleMenu_DrawSwitchPanelEntry(TeamRoster* arg0, BattleMon* arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_t0;

    BattleHud_DrawLevelNumber(arg2 + 3, arg3 + 4, arg1->level);
    Widget_DrawMeterBar(arg2 + 0x1E, arg3 + 0xE, arg1->hp, arg1->maxHp);
    BattleHud_DrawHpFractionText(arg2 + 0x26, arg3 + 0x14, arg1->hp, arg1->maxHp);

    gSPDisplayList(gDisplayListHead++, D_80060308);

    if (arg4 == 0) {
        Gfx_DrawTextureRgba16Ia8(arg2 + 8, arg3 + 0xD, 0x10, 0xE, D_030078C0, D_03007A80, 0x10, 0x100000);
    }
    if (arg4 == 1) {
        Gfx_DrawTextureRgba16Ia8(arg2 + 8, arg3 + 0xD, 0x10, 0xE, D_3007620, D_030077E0, 0x10, 0x100000);
    }
    if (arg4 == 2) {
        Gfx_DrawTextureRgba16Ia8(arg2 + 8, arg3 + 0xD, 0x10, 0xC, D_0300A080, D_0300A200, 0x10, 0x100000);
    }
    if (arg4 == 3) {
        Gfx_DrawTextureRgba16Ia8(arg2 + 8, arg3 + 0xD, 0x10, 0xE, D_030070E0, D_030072A0, 0x10, 0x100000);
    }
    if (arg4 == 4) {
        Gfx_DrawTextureRgba16Ia8(arg2 + 8, arg3 + 0xD, 0x10, 0xE, D_03007380, D_03007540, 0x10, 0x100000);
    }
    if (arg4 == 5) {
        Gfx_DrawTextureRgba16Ia8(arg2 + 8, arg3 + 0xD, 0x10, 0xC, D_03009E40, D_03009FC0, 0x10, 0x100000);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    Font_BeginTranslucentTextRendering();
    Font_SetActive(1, 0);
    Font_Printf(arg2 + 0x18, arg3 + 2, arg1->nickname);
    Font_EndTexturedTextRendering();

    if (arg0->pokemonPicked[arg4].hp == 0) {
        var_t0 = 1;
    } else {
        var_t0 = LabPC_StatusToIconIndex(arg0->pokemonPicked[arg4].statusCondition);
    }

    if (var_t0 != 0) {
        gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
        Gfx_DrawTextureRgba16(arg2 + 0x49, arg3 + 2, 0x18, 0xB, D_8218AFDC[var_t0], 0x18, 0);
        gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    }
}

/**
 * Draws a Pokemon's HUD details at (arg2, arg3): level, HP bar and HP fraction, a gender or
 * marker icon chosen by arg4, and a status icon when it has one.
 */
void func_8211B208(TeamRoster* arg0, BattleMon* arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_t0;

    BattleHud_DrawLevelNumber(arg2 + 3, arg3 + 4, arg1->level);
    Widget_DrawMeterBar(arg2 + 0x1E, arg3 + 0xE, arg1->hp, arg1->maxHp);
    BattleHud_DrawHpFractionText(arg2 + 0x26, arg3 + 0x14, arg1->hp, arg1->maxHp);

    gSPDisplayList(gDisplayListHead++, D_80060308);

    if (arg4 == 0) {
        Gfx_DrawTextureRgba16Ia8(arg2 + 8, arg3 + 0xD, 0x10, 0xE, D_030078C0, D_03007A80, 0x10, 0x100000);
    }
    if (arg4 == 1) {
        Gfx_DrawTextureRgba16Ia8(arg2 + 8, arg3 + 0xD, 0x10, 0xE, D_030070E0, D_030072A0, 0x10, 0x100000);
    }
    if (arg4 == 2) {
        Gfx_DrawTextureRgba16Ia8(arg2 + 8, arg3 + 0xD, 0x10, 0xE, D_03007380, D_03007540, 0x10, 0x100000);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    Font_BeginTranslucentTextRendering();
    Font_SetActive(1, 0);
    Font_Printf(arg2 + 0x18, arg3 + 2, arg1->nickname);
    Font_EndTexturedTextRendering();

    if (arg0->pokemonPicked[arg4].hp == 0) {
        var_t0 = 1;
    } else {
        var_t0 = LabPC_StatusToIconIndex(arg0->pokemonPicked[arg4].statusCondition);
    }

    if (var_t0 != 0) {
        gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
        Gfx_DrawTextureRgba16(arg2 + 0x49, arg3 + 2, 0x18, 0xB, D_8218AFDC[var_t0], 0x18, 0);
        gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    }
}

extern u8 D_8218B02C[];
extern u8 D_8218B044[];
extern u8 D_8218B05C[];
extern u8 D_8218B074[];
extern u8 D_8218B038[];
extern u8 D_8218B050[];
extern u8 D_8218B068[];
extern u8 D_8218B080[];
extern u8* D_8218AFF8[];
/**
 * Draws a three-Pokemon roster panel at (arg1, arg2) for team arg0: each member's details
 * and name, then a drop shadow around the panel.
 */
void func_8211B484(TeamRoster* arg0, s16 arg1, s16 arg2, s32 arg3) {
    UNUSED s32 pad; // FAKE
    s8* sp88[] = {D_8218B02C, D_8218B044, D_8218B05C, D_8218B074};
    s8* sp78[] = {D_8218B038, D_8218B050, D_8218B068, D_8218B080};
    UNUSED s32 pad2[4]; // FAKE
    BattleMon* mon0 = &arg0->pokemonPicked[0];
    BattleMon* mon1 = &arg0->pokemonPicked[1];
    BattleMon* mon2 = &arg0->pokemonPicked[2];
    s32 i;
    s32 icon; // status icon index, computed but never used here

    if (mon0->hp == 0) {
        icon = 1;
    } else {
        icon = func_8001FA30(mon0->statusCondition);
    }
    if (mon1->hp == 0) {
        icon = 1;
    } else {
        icon = func_8001FA30(mon1->statusCondition);
    }
    if (mon2->hp == 0) {
        icon = 1;
    } else {
        icon = func_8001FA30(mon2->statusCondition);
    }
    func_82116CF4(arg1 + 1, arg2 + 1, 0x63, 0xF, sp88[arg3], sp78[arg3]);
    func_82116CF4(arg1 + 1, arg2 + 0x10, 0x63, 0x1D, sp88[arg3] + 3, sp78[arg3] + 3);
    func_82116CF4(arg1 + 1, arg2 + 0x2D, 0x63, 0x1D, sp88[arg3] + 6, sp78[arg3] + 6);
    func_82116CF4(arg1 + 1, arg2 + 0x4A, 0x63, 0x1D, sp88[arg3] + 9, sp78[arg3] + 9);
    BattleHud_DrawPlainText(arg1 + 0x2C, arg2 + 3, arg0->trainerName);
    func_8211B208(arg0, mon0, arg1 + 1, arg2 + 0x10, 0);
    func_8211B208(arg0, mon1, arg1 + 1, arg2 + 0x2D, 1);
    func_8211B208(arg0, mon2, arg1 + 1, arg2 + 0x4A, 2);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    func_8001B884(arg1 + 1, arg2, 0x18, 0x10, D_8218AFF8[arg3], 0x18, 0);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1, arg2 - 1, 8, 8, D_030096C0);
    for (i = 7; i < 0x62; i += 7) {
        BattleHud_DrawBorderTile(arg1, arg2 + i, 8, 8, D_030095C0);
        BattleHud_DrawBorderTile(arg1 + 0x5D, arg2 + i, 8, 8, D_03009740);
    }

    BattleHud_DrawBorderTile(arg1, arg2 + 0x60, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0x5D, arg2 - 1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0x5D, arg2 + 0x60, 8, 8, D_030097C0);
    for (i = 7; i < 0x62; i += 7) {
        BattleHud_DrawBorderTile(arg1 + i, arg2 - 1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + i, arg2 + 0x60, 8, 8, D_030098C0);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 0x69, 0x6A, 0);
}

typedef struct Colors8211B900 {
    s8* p[4];
} Colors8211B900;
Colors8211B900 D_8218B104 = { { (s8*)D_8218B02C, (s8*)D_8218B044, (s8*)D_8218B05C, (s8*)D_8218B074 } };
Colors8211B900 D_8218B114 = { { (s8*)D_8218B038, (s8*)D_8218B050, (s8*)D_8218B068, (s8*)D_8218B080 } };
extern u8* D_8218AFF8[];
extern Gfx D_800602C8[];
extern Gfx D_80060398[];

/**
 * Draws the Pokemon (switch) menu panel: the trainer name and one row per Pokemon brought,
 * through BattleMenu_DrawSwitchPanelEntry. Ran in play every frame while 1P's Pokemon menu (B)
 * was open.
 */
void BattleMenu_DrawSwitchPanel(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3) {
    UNUSED s32 pad[3]; // FAKE
    Colors8211B900 a = D_8218B104;
    Colors8211B900 b = D_8218B114;
    TeamRoster* roster = arg0->side->teamMember[arg0->thumbnail.shownTeamMemberIndex];
    BattleMon* m0 = &arg0->teamRoster->pokemonPicked[0];
    BattleMon* m1 = &arg0->teamRoster->pokemonPicked[1];
    BattleMon* m2 = &arg0->teamRoster->pokemonPicked[2];
    BattleMon* m3 = &arg0->teamRoster->pokemonPicked[3];
    BattleMon* m4 = &arg0->teamRoster->pokemonPicked[4];
    BattleMon* m5 = &arg0->teamRoster->pokemonPicked[5];
    UNUSED s32 pad2[5]; // FAKE
    s32 icon; // status icon index, computed but never used here
    s32 n;

    if (m0->hp == 0) {
        icon = 1;
    } else {
        icon = func_8001FA30(m0->statusCondition);
    }
    if (m1->hp == 0) {
        icon = 1;
    } else {
        icon = func_8001FA30(m1->statusCondition);
    }
    if (m2->hp == 0) {
        icon = 1;
    } else {
        icon = func_8001FA30(m2->statusCondition);
    }
    if (m3->hp == 0) {
        icon = 1;
    } else {
        icon = func_8001FA30(m3->statusCondition);
    }
    if (m4->hp == 0) {
        icon = 1;
    } else {
        icon = func_8001FA30(m4->statusCondition);
    }
    if (m5->hp == 0) {
        icon = 1;
    } else {
        icon = func_8001FA30(m5->statusCondition);
    }
    func_82116CF4(arg1 + 1, arg2 + 1, 0xC8, 0xF, a.p[arg3], b.p[arg3]);
    func_82116CF4(arg1 + 1, arg2 + 0x10, 0xC8, 0x1D, a.p[arg3] + 3, b.p[arg3] + 3);
    func_82116CF4(arg1 + 1, arg2 + 0x2D, 0xC8, 0x1D, a.p[arg3] + 6, b.p[arg3] + 6);
    func_82116CF4(arg1 + 1, arg2 + 0x4A, 0xC8, 0x1D, a.p[arg3] + 9, b.p[arg3] + 9);
    BattleHud_DrawPlainText(arg1 + 0x2C, arg2 + 3, roster->trainerName);
    gSPDisplayList(gDisplayListHead++, D_800602C8);
    Gfx_DrawTextureRgba16(arg1 + 1, arg2, 0x18, 0x10, D_8218AFF8[arg3], 0x18, 0);
    gSPDisplayList(gDisplayListHead++, D_80060398);
    if (roster->numberOfPokemonBrought > 0) {
        BattleMenu_DrawSwitchPanelEntry(roster, m0, arg1 + 1, arg2 + 0x10, 0);
    }
    if (roster->numberOfPokemonBrought >= 2) {
        BattleMenu_DrawSwitchPanelEntry(roster, m1, arg1 + 1, arg2 + 0x2D, 1);
    }
    if (roster->numberOfPokemonBrought >= 3) {
        BattleMenu_DrawSwitchPanelEntry(roster, m2, arg1 + 1, arg2 + 0x4A, 2);
    }
    if (roster->numberOfPokemonBrought >= 4) {
        BattleMenu_DrawSwitchPanelEntry(roster, m3, arg1 + 0x66, arg2 + 0x10, 3);
    }
    if (roster->numberOfPokemonBrought >= 5) {
        BattleMenu_DrawSwitchPanelEntry(roster, m4, arg1 + 0x66, arg2 + 0x2D, 4);
    }
    if (roster->numberOfPokemonBrought >= 6) {
        BattleMenu_DrawSwitchPanelEntry(roster, m5, arg1 + 0x66, arg2 + 0x4A, 5);
    }
    gSPDisplayList(gDisplayListHead++, D_800602C8);
    BattleHud_DrawBorderTile(arg1, arg2 - 1, 8, 8, D_030096C0);
    for (n = 1; n < 14; n++) {
        BattleHud_DrawBorderTile(arg1, arg2 + n * 7, 8, 8, D_030095C0);
        BattleHud_DrawBorderTile(arg1 + 0xC2, arg2 + n * 7, 8, 8, D_03009740);
    }
    BattleHud_DrawBorderTile(arg1, arg2 + 0x60, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0xC2, arg2 - 1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0xC2, arg2 + 0x60, 8, 8, D_030097C0);
    for (n = 1; n < 28; n++) {
        BattleHud_DrawBorderTile(arg1 + n * 7, arg2 - 1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + n * 7, arg2 + 0x60, 8, 8, D_030098C0);
    }
    gSPDisplayList(gDisplayListHead++, D_80060398);
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 0xCE, 0x6A, 0);
}

extern s8 D_8218B020;
/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle and a Pound
 * turn.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleHud_DrawCompactMonStatusBox(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3) {
    BattleMon* mon;
    u32 status;
    u8* color;
    s32 n;
    ActivePokemonState* state;
    u16 val;

    state = &arg0->state;
    mon = &arg0->side->teamMember[arg0->thumbnail.shownTeamMemberIndex]->pokemonPicked[arg0->thumbnail.shownRosterIndex];
    if (mon->hp == 0) {
        status = 1;
    } else {
        status = func_8001FA30(mon->statusCondition);
    }
    if (state->infoBoxBlinkTimer < 0xFF00) {
        state->infoBoxBlinkTimer -= 0x30;
    }
    val = state->infoBoxBlinkTimer;
    if ((val >> 8) & 1) {
        color = (u8*)(&D_8218B008 + arg3 * 3);
    } else {
        color = (u8*)(&D_8218B020 + arg3 * 3);
    }
    BattleHud_DrawMonInfoBox(arg0, mon, &D_80066AA0[status], arg1 + 1, arg2 + 1, 0x46, 0x28, color[0], color[1], color[2], 0xB2);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1, arg2, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x22, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0x40, arg2, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0x40, arg2 + 0x22, 8, 8, D_030097C0);
    for (n = 8; n < 0x40; n += 8) {
        BattleHud_DrawBorderTile(arg1 + n, arg2, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + n, arg2 + 0x22, 8, 8, D_030098C0);
    }
    for (n = 8; n < 0x28; n += 8) {
        BattleHud_DrawBorderTile(arg1, arg2 + n, 8, 8, D_030095C0);
        BattleHud_DrawBorderTile(arg1 + 0x40, arg2 + n, 8, 8, D_03009740);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 0x4C, 0x2D, 0);
}

void Font_SetLineHeight(s32 arg0);
void Battle_DrawGradientRectWrapper(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void BattleHud_DrawTranslucentShadowRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/**
 * Draws the battle message box at (x, y) with the revealed part of the text, in the color of the
 * given side.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name from its caller.
 */
void BattleMessage_DrawBox(s32 arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 i;
    s32 n;

    Battle_DrawGradientRectWrapper(arg1 + 1, arg2 + 1, 0xEE, 0x24, (Color_RGB8*)(&D_8218B008 + arg0 * 3), (Color_RGB8*)(&D_8218B014 + arg0 * 3));
    func_8001AB6C();
    func_8001A384(2, 0);
    Font_SetLineHeight(0x10);
    func_8001A944(arg1 + 0xA, arg2 + 5, arg3);
    func_8001ABBC();
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1, arg2, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x1E, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0xE8, arg2, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0xE8, arg2 + 0x1E, 8, 8, D_030097C0);
    for (n = 8; n < 0xE8; n += 8) {
        BattleHud_DrawBorderTile(arg1 + n, arg2, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + n, arg2 + 0x1E, 8, 8, D_030098C0);
    }
    for (n = 8; n < 0x20; n += 8) {
        BattleHud_DrawBorderTile(arg1, arg2 + n, 8, 8, D_030095C0);
        BattleHud_DrawBorderTile(arg1 + 0xE8, arg2 + n, 8, 8, D_03009740);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 1, 0xF4, 0x29, 0);
}

/**
 * Draws a side's caption box with the revealed part of the caption text.
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name from its caller.
 */
void BattleHud_DrawCaptionBox(s32 arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 n;

    Battle_DrawGradientRectWrapper(arg1 + 1, arg2 + 1, 0xC8, 0x24, (Color_RGB8*)(&D_8218B008 + arg0 * 3), (Color_RGB8*)(&D_8218B014 + arg0 * 3));
    func_8001AB6C();
    func_8001A384(2, 0);
    Font_SetLineHeight(0x10);
    func_8001A944(arg1 + 0xA, arg2 + 5, arg3);
    func_8001ABBC();
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1, arg2, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x1E, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0xC2, arg2, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0xC2, arg2 + 0x1E, 8, 8, D_030097C0);
    for (n = 8; n < 0xC8; n += 8) {
        BattleHud_DrawBorderTile(arg1 + n, arg2, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + n, arg2 + 0x1E, 8, 8, D_030098C0);
    }
    for (n = 8; n < 0x20; n += 8) {
        BattleHud_DrawBorderTile(arg1, arg2 + n, 8, 8, D_030095C0);
        BattleHud_DrawBorderTile(arg1 + 0xC2, arg2 + n, 8, 8, D_03009740);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 1, 0xCD, 0x28, 0);
}

extern u8 D_0300A500[];
extern u8 D_0300A7A0[];
extern char D_82195A68[];
extern char D_82195A7C[];
extern char D_82195A84[];
/**
 * Draws the こうさんしますか? (Surrender?) prompt with the No/Yes cursor at state.unk_2F.
 */
void BattleMenu_DrawSurrenderPromptWithCursor(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 pad[2]; // FAKE
    s32 n;

    Battle_DrawGradientRectWrapper(arg1 + 1, arg2 + 1, 0xC8, 0x24, (Color_RGB8*)(&D_8218B008 + arg3 * 3), (Color_RGB8*)(&D_8218B014 + arg3 * 3));
    func_8001AB6C();
    func_8001A384(2, 0);
    func_8001A944(arg1 + 0x28, arg2 + 5, D_82195A68);
    func_8001A944(arg1 + 0x32, arg2 + 0x14, D_82195A7C);
    func_8001A944(arg1 + 0x7A, arg2 + 0x14, D_82195A84);
    func_8001ABBC();
    gSPDisplayList(gDisplayListHead++, D_80060308);
    Gfx_DrawTextureRgba16Ia8(arg1 + arg0->state.surrenderCursor * 0x49 + 0x1B, arg2 + 0x14, 0x18, 0xE, D_0300A500, D_0300A7A0, 0x18, 0x100000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1, arg2, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x1E, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0xC2, arg2, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0xC2, arg2 + 0x1E, 8, 8, D_030097C0);
    for (n = 8; n < 0xC8; n += 8) {
        BattleHud_DrawBorderTile(arg1 + n, arg2, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + n, arg2 + 0x1E, 8, 8, D_030098C0);
    }
    for (n = 8; n < 0x20; n += 8) {
        BattleHud_DrawBorderTile(arg1, arg2 + n, 8, 8, D_030095C0);
        BattleHud_DrawBorderTile(arg1 + 0xC2, arg2 + n, 8, 8, D_03009740);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 1, 0xCD, 0x28, 0);
}

extern u8 D_8219A4F1;
u8 func_8000F1FC(u8, s32, s32, s32);
/**
 * Draws the acting Pokemon's nickname centered near the bottom of the screen, fading it in
 * by 5 a frame.
 */
void func_8211C9FC(void) {
    u32 len;
    s8* name;
    ActivePokemonState* state = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    BattleMon* bm = &sActivePokemon[sBattleScene.scene->actingSide]->side->teamMember[0]->pokemonPicked[state->rosterIndex];

    D_8219A4F1 = func_8000F1FC(D_8219A4F1, 0xFF, 5, 5);
    func_8001AB6C();
    func_8001ABE8();
    func_8001AA9C(0xFF, 0xFF, 0xFF, D_8219A4F1);
    func_8001AAE4(0xFF, 0xFF, 0xF, D_8219A4F1);
    name = (s8*)bm + 0x30;
    len = func_800566BC((s32)name) >> 1;
    func_8001A384(4, 0);
    func_8001A944(0x9A - len * 6, 0xBE, (s32)name);
    func_8001AC3C();
    func_8001ABBC();
}

extern Gfx D_800602C8[];
extern Gfx D_80060398[];
extern u8 D_03003EC0[];
extern u8 D_03006C40[];

/**
 * Draws a 104-pixel wide RGBA32 image line by line from y = 23, starting at D_03003EC0.
 */
void func_8211CB0C(void) {
    s32 i;
    u8* tex;

    gSPDisplayList(gDisplayListHead++, D_800602C8);
    // Keep on one line: IDO schedules the setup differently otherwise.
    tex = D_03003EC0; i = 0x17; do {
        Gfx_DrawTextureRgba32(0x1E, i, 0x68, 1, tex, 0x68, 0);
        tex += 0x1A0;
        i++;
    } while (tex != D_03006C40);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

extern s8 D_8219A4A0[];
extern s8 D_8219A4C8[];
/**
 * Splits str at its first space: the first word goes to D_8219A4A0 and the rest to
 * D_8219A4C8. Returns 1 if there was a space, 0 otherwise.
 */
s32 func_8211CBCC(s8* str) {
    s8 i = 0;
    s8 j = 0;

    do {
        D_8219A4A0[i] = str[i];
        i++;
        D_8219A4A0[i] = 0;
        if (str[i] == ' ') {
            goto found;
        }
    } while (str[i] != 0);
    return 0;
found:
    i++;
    do {
        D_8219A4C8[j] = str[i];
        i++;
        j++;
        D_8219A4C8[j] = 0;
    } while (str[i] != 0);
    return 1;
}

u8 D_8218B124[] = { 0xFF, 0xFF, 0xFF, 0x00, 0x6E, 0xFF, 0xFF, 0xFF, 0xFF, 0x64, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x64, 0x00, 0x00, 0x64, 0xFF, 0x00, 0x00, 0xFF };

typedef struct TextLine8211CC8C {
    /* 0x00 */ s8* str;
    /* 0x04 */ u8 color;
    /* 0x05 */ char unk05[3];
} TextLine8211CC8C; // size = 0x8
typedef struct Rgb8211CC8C {
    u8 r, g, b;
} Rgb8211CC8C;
extern TextLine8211CC8C D_82189D8C[];
extern u8 D_8219A4F0[];
extern char D_82195A8C[];
extern char D_82195A94[];
extern char D_82195A9C[];
s32 func_8000A4E8(s8*, char*);

/**
 * Draws the battle text box at its stored position, fading it in (or out) by 10 a frame and
 * drawing its lines.
 */
void func_8211CC8C(void) {
    UNUSED s32 pad[4]; // FAKE
    s16 x = *(s16*)&D_8219A4F0[0x16]; // FAKE: the text box is read as raw bytes; a struct pointer gets folded
    s16 y = *(s16*)&D_8219A4F0[0x18]; // FAKE
    s32 n = 0;
    s32 i = 0;
    Rgb8211CC8C* c;
    s32 ty;
    s32 len;

    if (D_8219A4F0[3] == 0xFF) {
        return;
    }
    if (D_8219A4F0[0] & 8) {
        D_8219A4F0[2] = func_8000F1FC(D_8219A4F0[2], 0xFF, 0xA, 0xA);
    } else {
        D_8219A4F0[2] = func_8000F1FC(D_8219A4F0[2], 0, 0xA, 0xA);
    }
    for (;;) {
        if (D_8219A4F0[3] == 0) {
            break;
        }
        if (func_8000A4E8(D_82189D8C[i].str, D_82195A8C) == 0) {
            n++;
            i++;
            if (n == D_8219A4F0[3]) {
                break;
            }
        }
        i++;
    }
    n = 0;
    for (;;) {
        if (func_8000A4E8(D_82189D8C[i + n].str, D_82195A94) == 0) {
            break;
        }
        n++;
    }
    if (y == 0xB4) {
        if (n >= 7) {
            y = y - n * 0xB - (n / 2) * 0xF + 0x43;
        } else {
            y = y - (n / 2) * 0xF - 0xA;
        }
    } else if (n >= 7) {
        y = y + n * 0xB - (n / 2) * 0xF - 0x43;
    } else {
        y = y - (n / 2) * 0xF + 0xA;
    }
    n = 0;
    for (;;) {
        if (func_8000A4E8(D_82189D8C[i].str, D_82195A9C) == 0) {
            break;
        }
        ty = y + n * 0xF;
        func_8001AB6C();
        func_8001ABE8();
        // FAKE: base first, then += index, so D_8218B124 is allocated before the 3 multiplier
        c = (Rgb8211CC8C*)D_8218B124;
        c += D_82189D8C[i].color << 1;
        func_8001AA9C(c->r, c->g, c->b, D_8219A4F0[2]);
        c = (Rgb8211CC8C*)D_8218B124;
        c += (D_82189D8C[i].color << 1) + 1;
        func_8001AAE4(c->r, c->g, c->b, D_8219A4F0[2]);
        if ((func_8211CBCC(D_82189D8C[i].str) == 0) || (D_82189D8C[i].color == 1)) {
            len = func_800566BC(D_82189D8C[i].str) >> 1;
            func_8001A384(2, -1);
            func_8001A944(x - len * 6 - 6, ty, D_82189D8C[i].str);
        } else {
            len = func_800566BC(D_8219A4A0) >> 1;
            func_8001A384(2, -1);
            func_8001A944(x - len * 0xC - 0xC, ty, D_8219A4A0);
            func_8001A384(2, -1);
            func_8001A944(x - 6, ty, D_8219A4C8);
        }
        func_8001AC3C();
        func_8001ABBC();
        i++;
        n++;
    }
}

extern u8 D_8219A4F0[];
extern u8 D_03003540[];
extern u8 D_03001DA0[];
/**
 * Fades the text box frame in or out by 5 a frame (flag 0x80), and when flag 0x40 is set
 * draws it with the env color as a translucent textured box.
 */
void func_8211D06C(void) {
    s32 i;
    u8* tex;

    if (D_8219A4F0[0] & 0x80) {
        D_8219A4F0[1] = func_8000F1FC(D_8219A4F0[1], 0xFF, 5, 5);
    } else {
        D_8219A4F0[1] = func_8000F1FC(D_8219A4F0[1], 0, 5, 5);
    }
    if (D_8219A4F0[0] & 0x40) {
        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0);
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
        gDPSetEnvColor(gDisplayListHead++, 0xFF, 0xFF, 0xFF, D_8219A4F0[1]);
        for (i = 0, tex = D_03003540; i != 0x10; i++, tex += 0x98) {
            func_8001BCB4(0x54, i + 0x70, 0x98, 1, tex, 0x98, 0);
        }
        gDPPipeSync(gDisplayListHead++);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
        gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    } else {
        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0);
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
        gDPSetEnvColor(gDisplayListHead++, 0xFF, 0xFF, 0xFF, D_8219A4F0[1]);
        for (i = 0, tex = D_03001DA0; i != 42; i++, tex += 0x90) {
            func_8001BCB4(0x58, i + 0x63, 0x90, 1, tex, 0x90, 0);
        }
        gDPPipeSync(gDisplayListHead++);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
        gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    }
}

/**
 * Draws the strip wipe if it is on.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_DrawStripWipeIfActive(void) {
    if (BattleScene_GetStripWipeState() != 0) {
        BattleScene_DrawStripWipe();
    }
}

extern char D_82195AA4[];
extern char D_82195AB0[];
extern char D_82195AC0[];
extern char D_82195AC8[];
extern char D_82195AD4[];
extern char D_82195AE0[];
extern char D_82195AEC[];
extern char D_82195AF4[];
s32 D_8218B13C[] = { (s32)D_82195AA4, (s32)D_82195AB0, (s32)D_82195AC0, (s32)D_82195AC8, (s32)D_82195AD4, (s32)D_82195AE0, (s32)D_82195AEC, (s32)D_82195AF4 };
extern u8 D_8219A730;
extern u8 D_8219A731;
extern s8 D_8219A732;
extern u8 D_0300A500[];
extern u8 D_0300A7A0[];
extern Gfx D_80060398[];
/**
 * Draws a list panel at (arg0, arg1): a translucent black box, the entries from D_8218B13C
 * (dimmed when D_8219A730 is set) and the cursor next to entry D_8219A732.
 */
void func_8211D3D8(s16 arg0, s16 arg1) {
    Ui_DrawPrimColorRect(arg0, arg1, 0x64, 0x7D, 0, 0, 0, 0x3C);
    func_8001AB6C();
    if (D_8219A730 == 0) {
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0x78);
    }
    func_8001A384(1, 0);
    func_8001A944(arg0 + 0x18, arg1 + 4, D_8218B13C[0]);
    func_8001A944(arg0 + 0x18, arg1 + 0x10, D_8218B13C[1]);
    func_8001A944(arg0 + 0x18, arg1 + 0x1C, D_8218B13C[2]);
    func_8001A944(arg0 + 0x18, arg1 + 0x28, D_8218B13C[3]);
    func_8001A944(arg0 + 0x18, arg1 + 0x34, D_8218B13C[4]);
    func_8001A944(arg0 + 0x18, arg1 + 0x40, D_8218B13C[5]);
    func_8001A944(arg0 + 0x18, arg1 + 0x4C, D_8218B13C[6]);
    func_8001A944(arg0 + 0x18, arg1 + 0x58, D_8218B13C[7]);
    func_8001AA9C(0xFF, 0xFF, 0, 0xFF);
    func_8001A944(arg0 + 0x18, arg1 + 0x69, D_8218B13C[D_8219A731]);
    func_8001ABBC();
    gSPDisplayList(gDisplayListHead++, D_80060308);
    Gfx_DrawTextureRgba16Ia8(arg0 + 2, arg1 + D_8219A732 * 0xC + 3, 0x18, 0xE, D_0300A500, D_0300A7A0, 0x18, 0x100000);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

s32 func_800564D4(char*, const char*, ...);
extern s32 D_82199DE0;
extern char D_82195B00[];
extern char D_82195B0C[];
extern char D_82195B18[];
extern char D_82195B24[];
extern char D_82195B30[];
extern char D_82195B3C[];
extern char D_82195B4C[];
extern char D_82195B50[];
extern char D_82195B58[];
extern char D_82195B60[];
extern char D_82195B64[];
extern char D_82195B68[];
/**
 * Debug overlay: camera distance, X/Y offset, X/Y angle and animation frame.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void BattleDebug_DrawCameraParams(s16 arg0, s16 arg1) {
    char buf[16];

    Ui_DrawPrimColorRect(arg0, arg1, 0x82, 0x50, 0, 0, 0, 0x3C);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg0 + 3, arg1 + 4, (s32)D_82195B00);
    func_8001A944(arg0 + 3, arg1 + 0x10, (s32)D_82195B0C);
    func_8001A944(arg0 + 3, arg1 + 0x1C, (s32)D_82195B18);
    func_8001A944(arg0 + 3, arg1 + 0x28, (s32)D_82195B24);
    func_8001A944(arg0 + 3, arg1 + 0x34, (s32)D_82195B30);
    func_8001A944(arg0 + 3, arg1 + 0x40, (s32)D_82195B3C);
    func_8001ABBC();
    func_800564D4(buf, D_82195B4C, M2C_FIELD(D_82199DE0, f32*, 0x9F0));
    func_82116480(buf, arg0 + 0x46, arg1 + 6);
    func_800564D4(buf, D_82195B50, M2C_FIELD(D_82199DE0, f32*, 0x9FC));
    func_82116480(buf, arg0 + 0x46, arg1 + 0x12);
    func_800564D4(buf, D_82195B58, M2C_FIELD(D_82199DE0, f32*, 0x9F8));
    func_82116480(buf, arg0 + 0x46, arg1 + 0x1E);
    func_800564D4(buf, D_82195B60, M2C_FIELD(D_82199DE0, s16*, 0x9EC));
    func_82116480(buf, arg0 + 0x46, arg1 + 0x2A);
    func_800564D4(buf, D_82195B64, M2C_FIELD(D_82199DE0, s16*, 0x9EE));
    func_82116480(buf, arg0 + 0x46, arg1 + 0x36);
    func_800564D4(buf, D_82195B68, M2C_FIELD(D_82199DE0, s32*, 0x9E8));
    func_82116480(buf, arg0 + 0x4B, arg1 + 0x42);
}

extern char D_82195B6C[];
extern char D_82195B74[];
extern char D_82195B80[];
extern char D_82195B8C[];
extern char D_82195B98[];
extern char D_82195BA4[];
extern char D_82195BB4[];
extern char D_82195BC4[];
extern char D_82195BD4[];
s32 D_8218B15C[] = { (s32)D_82195B6C, (s32)D_82195B74, (s32)D_82195B80, (s32)D_82195B8C, (s32)D_82195B98, (s32)D_82195BA4, (s32)D_82195BB4, (s32)D_82195BC4, (s32)D_82195BD4 };

/**
 * Debug overlay: カメラ (Camera) label.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void BattleDebug_DrawCameraLabel(s16 arg0, s16 arg1) {
    Ui_DrawPrimColorRect(arg0, arg1, 0x6E, 0x1E, 0, 0, 0, 0x3C);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg0 + 3, arg1 + 4, (s32)&D_82195BE4);
    func_8001A944(arg0 + 0x23, arg1 + 0x10, D_8218B15C[D_8219A5A4]);
    func_8001ABBC();
}

typedef struct Entry8006A9CC {
    /* 0x0 */ char* name;
    /* 0x4 */ char unk04[0x8];
} Entry8006A9CC; // size = 0xC
extern Entry8006A9CC D_8006A9CC[];

extern s32 D_8219A764;
extern s32 D_8219A760;
extern s32 D_8219A740;
extern s32 D_8219A744;
extern u8 D_8219A748;
extern u8 D_8219A749;
extern u8 D_8219A74A;
extern u8 D_8219A74B;
extern char D_82195D40[];
extern char D_82195D48[];
extern char D_82195D50[];
extern char D_82195D5C[];
extern char D_82195D68[];
extern char D_82195D70[];
extern char D_82195D7C[];
extern char D_82195D88[];
extern char D_82195D90[];
extern char D_82195D9C[];
extern char D_82195DA8[];
extern char D_82195DAC[];
extern char D_82195BEC[], D_82195BF8[], D_82195C04[], D_82195C10[];
extern char D_82195C1C[], D_82195C24[], D_82195C30[], D_82195C38[], D_82195C40[], D_82195C4C[];
extern char D_82195C58[], D_82195C60[], D_82195C68[], D_82195C70[], D_82195C78[], D_82195C84[], D_82195C90[], D_82195C9C[];
extern char D_82195CA8[], D_82195CB0[], D_82195CB8[], D_82195CC0[], D_82195CC8[], D_82195CD8[], D_82195CE4[], D_82195CF0[];
extern char D_82195CFC[], D_82195D04[], D_82195D0C[], D_82195D14[], D_82195D1C[], D_82195D28[], D_82195D34[];

/**
 * Debug overlay: ステップ1 (Step 1) option lists, MODE, and しぬ/しなない (faint / don't faint).
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void BattleDebug_DrawStepMenu(s16 arg0, s16 arg1) {
    char buf[16];
    char* labels[] = { D_82195BEC, D_82195BF8, D_82195C04, D_82195C10 };
    char* names0[] = { D_82195C1C, D_82195C24, D_82195C30, D_82195C38, D_82195C40, D_82195C4C };
    char* names1[] = { D_82195C58, D_82195C60, D_82195C68, D_82195C70, D_82195C78, D_82195C84, D_82195C90, D_82195C9C };
    char* names2[] = { D_82195CA8, D_82195CB0, D_82195CB8, D_82195CC0, D_82195CC8, D_82195CD8, D_82195CE4, D_82195CF0 };
    char* names3[] = { D_82195CFC, D_82195D04, D_82195D0C, D_82195D14, D_82195D1C, D_82195D28, D_82195D34 };

    Ui_DrawPrimColorRect(arg0, arg1, 0x78, 0x82, 0, 0, 0, 0x3C);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg0 + 3, arg1 + 2, (s32)D_82195D40);
    if (D_8219A764 == 0) {
        func_8001A944(arg0 + 0x3C, arg1 + 2, (s32)D_82195D48);
    } else {
        func_8001A944(arg0 + 0x3C, arg1 + 2, (s32)D_82195D50);
    }
    func_8001A944(arg0 + 0x3C, arg1 + 0x10, *(s32*)((&D_82199DE0)[D_8219A760] + 0x860) + 8);
    func_8001A944(arg0 + 3, arg1 + 0x10, (s32)D_82195D5C);
    func_8001A944(arg0 + 3, arg1 + 0x1C, (s32)D_82195D68);
    if (D_8219A740 == 0xA6) {
        func_8001A944(arg0 + 0x23, arg1 + 0x1C, (s32)D_82195D70);
    } else {
        func_8001A944(arg0 + 0x23, arg1 + 0x1C, (s32)D_8006A9CC[D_8219A740].name);
    }
    func_8001A944(arg0 + 3, arg1 + 0x28, (s32)D_82195D7C);
    func_8001A944(arg0 + 3, arg1 + 0x34, (s32)D_82195D88);
    if (D_8219A744 == 0xA6) {
        func_8001A944(arg0 + 0x23, arg1 + 0x34, (s32)D_82195D90);
    } else {
        func_8001A944(arg0 + 0x23, arg1 + 0x34, (s32)D_8006A9CC[D_8219A744].name);
    }
    func_8001A944(arg0 + 3, arg1 + 0x40, (s32)D_82195D9C);
    func_8001A944(arg0 + 3, arg1 + 0x4C, (s32)labels[0]);
    func_8001A944(arg0 + 0x3C, arg1 + 0x4C, (s32)names0[D_8219A748]);
    func_8001A944(arg0 + 3, arg1 + 0x58, (s32)labels[1]);
    func_8001A944(arg0 + 0x3C, arg1 + 0x58, (s32)names1[D_8219A749]);
    func_8001A944(arg0 + 3, arg1 + 0x64, (s32)labels[2]);
    func_8001A944(arg0 + 0x3C, arg1 + 0x64, (s32)names2[D_8219A74A]);
    func_8001A944(arg0 + 3, arg1 + 0x70, (s32)labels[3]);
    func_8001A944(arg0 + 0x3C, arg1 + 0x70, (s32)names3[D_8219A74B]);
    func_8001ABBC();
    func_800564D4(buf, D_82195DA8, D_8219A740);
    func_82116480(buf, arg0 + 0x3C, arg1 + 0x28);
    func_800564D4(buf, D_82195DAC, D_8219A744);
    func_82116480(buf, arg0 + 0x3C, arg1 + 0x40);
}

extern s32 D_8219A740;
extern s32 D_8219A74C;
extern s32 D_8219A750;
extern s32 D_8218B218[];
extern s32 D_8218B204[];
extern char D_82195E04[];
extern char D_82195E10[];
extern char D_82195E20[];
extern char D_82195E28[];
extern char D_82195E3C[];
extern char D_82195E50[];
extern char D_82195E54[];
extern char D_82195E6C[];
extern char D_82195E7C[];
extern char D_82195E84[];
extern char D_82195E90[];
extern char D_82195E94[];
extern char D_82195E98[];
extern char D_82195E9C[];
extern char D_82195EA0[];
extern char D_82195EA4[];
extern s32 D_8219A75C;
extern s32 D_8219A768;
/**
 * Debug overlay for move effects: move name and number, turn, effect 1/2 start, end frame and current frame.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void BattleDebug_DrawMoveEffectViewer(s16 arg0, s16 arg1) {
    char buf[16];
    s32 val;
    UNUSED s32 pad[1]; // FAKE: stack padding

    val = M2C_FIELD(D_82199DE0, s32*, 0x620);
    Ui_DrawPrimColorRect(arg0, arg1, 0xAA, 0x70, 0, 0, 0, 0x3C);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg0 + 3, arg1 + 4, (s32)D_82195E04);
    func_8001A944(arg0 + 0x64, arg1 + 4, (s32)D_8006A9CC[D_8219A740].name);
    func_8001A944(arg0 + 3, arg1 + 0x10, (s32)D_82195E10);
    func_8001A944(arg0 + 3, arg1 + 0x1C, (s32)D_82195E20);
    if (D_8219A75C == 3) {
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0x3C);
        func_8001A944(arg0 + 0x64, arg1 + 0x1C, D_8218B218[D_8219A75C]);
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        func_8001A944(arg0 + 0x64, arg1 + 0x1C, D_8218B218[D_8219A75C]);
    }
    func_8001A944(arg0 + 3, arg1 + 0x28, (s32)D_82195E28);
    func_8001A944(arg0 + 3, arg1 + 0x34, (s32)D_82195E3C);
    if (D_8219A750 == 0) {
        func_8001A944(arg0 + 0x69, arg1 + 0x34, (s32)D_82195E50);
    }
    func_8001A944(arg0 + 3, arg1 + 0x40, (s32)D_82195E54);
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8001A944(arg0 + 3, arg1 + 0x4C, (s32)D_82195E6C);
    func_8001A944(arg0 + 3, arg1 + 0x58, (s32)D_82195E7C);
    func_8001A944(arg0 + 0x64, arg1 + 0x58, D_8218B204[D_8219A5A4]);
    func_8001A944(arg0 + 3, arg1 + 0x64, (s32)D_82195E84);
    func_8001ABBC();
    func_800564D4(buf, D_82195E90, D_8219A740);
    func_82116480(buf, arg0 + 0x64, arg1 + 0x12);
    func_800564D4(buf, D_82195E94, val);
    func_82116480(buf, arg0 + 0x64, arg1 + 0x4E);
    func_800564D4(buf, D_82195E98, D_8219A74C);
    func_82116480(buf, arg0 + 0x6E, arg1 + 0x2A);
    if (D_8219A750 != 0) {
        func_800564D4(buf, D_82195E9C, D_8219A750);
        func_82116480(buf, arg0 + 0x6E, arg1 + 0x36);
    }
    func_800564D4(buf, D_82195EA0, D_8219A768);
    func_82116480(buf, arg0 + 0x6E, arg1 + 0x42);
    func_800564D4(buf, D_82195EA4, M2C_FIELD(M2C_FIELD(D_82199DE0, void**, 0x44), u16*, 0xA));
    func_82116480(buf, arg0 + 0x64, arg1 + 0x66);
}

extern s32 D_8218B228[];
extern char D_82195EF0[];
extern char D_82195EFC[];
extern char D_82195F0C[];
extern char D_82195F20[];
extern char D_82195F34[];
extern char D_82195F38[];
extern char D_82195F48[];
extern char D_82195F50[];
extern char D_82195F5C[];
extern char D_82195F60[];
extern char D_82195F64[];
extern char D_82195F68[];
extern char D_82195F6C[];
/**
 * Debug overlay for move effects with the camera: move name and number, effect 1/2 start, current frame, camera and frame.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void BattleDebug_DrawMoveCameraViewer(s16 arg0, s16 arg1) {
    char buf[16];
    s32 val;
    UNUSED s32 pad[1]; // FAKE: stack padding

    val = M2C_FIELD(D_82199DE0, s32*, 0x620);
    Ui_DrawPrimColorRect(arg0, arg1, 0xAA, 0x5A, 0, 0, 0, 0x3C);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg0 + 3, arg1 + 4, (s32)D_82195EF0);
    func_8001A944(arg0 + 0x69, arg1 + 4, (s32)D_8006A9CC[D_8219A740].name);
    func_8001A944(arg0 + 3, arg1 + 0x10, (s32)D_82195EFC);
    func_8001A944(arg0 + 3, arg1 + 0x1C, (s32)D_82195F0C);
    func_8001A944(arg0 + 3, arg1 + 0x28, (s32)D_82195F20);
    if (D_8219A750 == 0) {
        func_8001A944(arg0 + 0x69, arg1 + 0x28, (s32)D_82195F34);
    }
    func_8001A944(arg0 + 3, arg1 + 0x34, (s32)D_82195F38);
    func_8001A944(arg0 + 3, arg1 + 0x40, (s32)D_82195F48);
    func_8001A944(arg0 + 0x69, arg1 + 0x40, D_8218B228[D_8219A5A4]);
    func_8001A944(arg0 + 3, arg1 + 0x4C, (s32)D_82195F50);
    func_8001ABBC();
    func_800564D4(buf, D_82195F5C, D_8219A740);
    func_82116480(buf, arg0 + 0x69, arg1 + 0x12);
    func_800564D4(buf, D_82195F60, val);
    func_82116480(buf, arg0 + 0x69, arg1 + 0x36);
    if (D_8219A750 != 0) {
        func_800564D4(buf, D_82195F64, D_8219A750);
        func_82116480(buf, arg0 + 0x69, arg1 + 0x2A);
    }
    func_800564D4(buf, D_82195F68, D_8219A74C);
    func_82116480(buf, arg0 + 0x69, arg1 + 0x1E);
    func_800564D4(buf, D_82195F6C, M2C_FIELD(M2C_FIELD(D_82199DE0, void**, 0x44), u16*, 0xA));
    func_82116480(buf, arg0 + 0x64, arg1 + 0x4E);
}

extern s32 D_8219A74C;
extern s32 D_8219A754;
extern char D_82195F70[];
extern char D_82195F84[];
extern char D_82195F98[];
extern char D_82195FA8[];
extern char D_82195FB4[];
extern char D_82195FB8[];
extern char D_82195FBC[];
extern char D_82195FC0[];
/**
 * Debug overlay: effect start, sound start, current frame and frame.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void BattleDebug_DrawEffectSoundTiming(s16 arg0, s16 arg1) {
    char buf[16];
    UNUSED s32 pad[1]; // FAKE: stack padding
    s32 val = M2C_FIELD(D_82199DE0, s32*, 0x620);

    Ui_DrawPrimColorRect(arg0, arg1, 0xAA, 0x36, 0, 0, 0, 0x3C);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg0 + 3, arg1 + 4, (s32)D_82195F70);
    func_8001A944(arg0 + 3, arg1 + 0x10, (s32)D_82195F84);
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8001A944(arg0 + 3, arg1 + 0x1C, (s32)D_82195F98);
    func_8001A944(arg0 + 3, arg1 + 0x28, (s32)D_82195FA8);
    func_8001ABBC();
    func_800564D4(buf, D_82195FB4, val);
    func_82116480(buf, arg0 + 0x64, arg1 + 0x1E);
    func_800564D4(buf, D_82195FB8, D_8219A74C);
    func_82116480(buf, arg0 + 0x64, arg1 + 6);
    func_800564D4(buf, D_82195FBC, D_8219A754);
    func_82116480(buf, arg0 + 0x64, arg1 + 0x12);
    func_800564D4(buf, D_82195FC0, M2C_FIELD(M2C_FIELD(D_82199DE0, void**, 0x44), u16*, 0xA));
    func_82116480(buf, arg0 + 0x64, arg1 + 0x2A);
}

extern char D_82195FC4[];
extern char D_82195FD0[];
extern char D_82195FD8[];
extern char D_82195FE4[];
extern char D_82195FF0[];
extern s32 D_8219A760;
/**
 * Debug overlay: Pokemon, Poke Ball, number and player.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void BattleDebug_DrawPokeBallViewer(s16 arg0, s16 arg1) {
    char buf[16];
    u8* mon = (u8*)(((s32*)&D_82199DE0)[D_8219A760] + 0x7C6);

    Ui_DrawPrimColorRect(arg0, arg1, 0x78, 0x3C, 0, 0, 0, 0x3C);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg0 + 3, arg1 + 4, (s32)D_82195FC4);
    if (mon[0xB] >= 0x98) {
        func_8001A944(arg0 + 0x3C, arg1 + 4, (s32)D_82195FD0);
    } else {
        func_8001A944(arg0 + 0x3C, arg1 + 4, *(s32*)D_80064C44[mon[0xB]]);
    }
    func_8001A944(arg0 + 3, arg1 + 0x10, (s32)D_82195FD8);
    func_8001A944(arg0 + 3, arg1 + 0x1C, (s32)D_82195FE4);
    func_8001A944(arg0 + 0x3C, arg1 + 0x1C, M2C_FIELD(((s32*)&D_82199DE0)[D_8219A760], s32*, 0x860) + 8);
    func_8001ABBC();
    func_800564D4(buf, D_82195FF0, mon[0xB]);
    func_82116480(buf, arg0 + 0x3C, arg1 + 0x12);
}

extern s8* D_8219A5A0;
extern char D_82195FF4[];
extern char D_82195FF8[];
/**
 * Draws a small translucent panel at (arg0, arg1) with two formatted values from the
 * scene's +0xCC object (its fields 0x34 and 0x38).
 */
void func_8211E794(s16 arg0, s16 arg1) {
    char buf[16];

    Ui_DrawPrimColorRect(arg0, arg1, 0x50, 0x1E, 0, 0, 0, 0x3C);
    func_800564D4(buf, D_82195FF4, sBattleScene.scene->camera->perspective.nearPlane);
    func_82116480(buf, arg0 + 3, arg1 + 2);
    func_800564D4(buf, D_82195FF8, sBattleScene.scene->camera->perspective.farPlane);
    func_82116480(buf, arg0 + 3, arg1 + 0x10);
}
