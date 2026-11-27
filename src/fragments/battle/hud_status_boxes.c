/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "font.h"
#include "graphics_textures.h"
#include "input.h"
#include "ui_graphics.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
M2C_UNK func_8001AB6C();
extern StatusLabel D_80066AA0[];
u32 LabPC_StatusToIconIndex(s32);
u32 func_800566BC(s8*);
void Font_SetActive(M2C_UNK, M2C_UNK);
void Font_EndTexturedTextRendering(void);

/* Zero uses different segmented addresses for the three party-ball textures. */
extern u8 D_03006C40[];
extern u8 D_03006CA0[];
extern u8 D_03006D00[];

/**
 * Draws the "TIME" label and the battle time (minutes, seconds, hundredths) at (x, y).
 * @unverified Name guessed from the code.
 */
void BattleHud_DrawBattleTime(s16 x, s16 y) {
    UNUSED s32 pad; // FAKE: stack padding
    s8 buf[12];
    f32 time = D_FLT_82199EB0 / 30.0f;
    UNUSED s32 pad2[3]; // FAKE: stack padding

    Font_BeginTranslucentTextRendering();
    Font_SetActive(1, 0);
    Font_Printf(x + 3, y + 3, "TIME");
    Font_EndTexturedTextRendering();
    sprintf(buf, "%02d", (s32)(time / 60.0f));
    BattleHud_DrawSmallDigits(buf, x + 50, y + 5);
    sprintf(buf, "%02d", (s32)time % 60);
    BattleHud_DrawSmallDigits(buf, x + 70, y + 5);
    sprintf(buf, "%02d", (s32)(time * 100.0) % 100);
    BattleHud_DrawSmallDigits(buf, x + 90, y + 5);
}


/**
 * Draws the "TOTAL TIME" label and the total time (minutes, seconds, hundredths) at (x, y).
 * @unverified Name guessed from the code.
 */
void BattleHud_DrawTotalTime(s16 x, s16 y) {
    UNUSED s32 pad; // FAKE: stack padding
    s8 buf[12];
    f32 time = D_FLT_82199EB4 / 30.0f;
    UNUSED s32 pad2[3]; // FAKE: stack padding

    Font_BeginTranslucentTextRendering();
    Font_SetActive(1, 0);
    Font_Printf(x + 3, y + 3, "TOTAL TIME");
    Font_EndTexturedTextRendering();
    sprintf(buf, "%02d", (s32)(time / 60.0f));
    BattleHud_DrawSmallDigits(buf, x + 110, y + 5);
    sprintf(buf, "%02d", (s32)time % 60);
    BattleHud_DrawSmallDigits(buf, x + 130, y + 5);
    sprintf(buf, "%02d", (s32)(time * 100.0) % 100);
    BattleHud_DrawSmallDigits(buf, x + 150, y + 5);
}


/**
 * Draws the row of party balls under a status box: one icon per Pokemon brought, chosen by
 * fainted, has a status condition or healthy. Draws both trainers' rows in tag battles.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleHud_DrawPartyBallRow(ActivePokemon* arg0, s16 arg1, s16 arg2) {
    u8* sp74[] = { D_03006C40, D_03006CA0, D_03006D00 };
    UNUSED s32 pad; // FAKE: stack padding
    s32 i;
    s32 j;
    s32 var_v0_2;

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    if (arg0 == sActivePokemon[0]) {
        if (arg0->side->tagTeamSize == 1) {
            for (i = 0; i < arg0->side->teamMember[0]->numberOfPokemonBrought; i++) {
                if (arg0->side->teamMember[0]->pokemonPicked[i].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->side->teamMember[0]->pokemonPicked[i].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 + i * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }
        } else {
            for (i = 0; i < arg0->side->teamMember[0]->numberOfPokemonBrought; i++) {
                if (arg0->side->teamMember[0]->pokemonPicked[i].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->side->teamMember[0]->pokemonPicked[i].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 + i * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }

            for (j = 0; j < arg0->side->teamMember[1]->numberOfPokemonBrought; j++) {
                if (arg0->side->teamMember[1]->pokemonPicked[j].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->side->teamMember[1]->pokemonPicked[j].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 + i * 7 + j * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }
        }
    }

    if (arg0 == sActivePokemon[1]) {
        if (arg0->side->tagTeamSize == 1) {
            for (i = 0; i < arg0->side->teamMember[0]->numberOfPokemonBrought; i++) {
                if (arg0->side->teamMember[0]->pokemonPicked[i].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->side->teamMember[0]->pokemonPicked[i].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 - i * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }
        } else {
            for (i = 0; i < arg0->side->teamMember[0]->numberOfPokemonBrought; i++) {
                if (arg0->side->teamMember[0]->pokemonPicked[i].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->side->teamMember[0]->pokemonPicked[i].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 - i * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }

            for (j = 0; j < arg0->side->teamMember[1]->numberOfPokemonBrought; j++) {
                if (arg0->side->teamMember[1]->pokemonPicked[j].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->side->teamMember[1]->pokemonPicked[j].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 - i * 7 - j * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }
        }
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}


/**
 * Draws side 0's status box: the info box tinted with the controller color, the trainer name
 * label, the border tiles, the drop shadows and the party ball row below.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleHud_DrawMonStatusBoxPlayer(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    TeamRoster* sp80;
    BattleMon* sp7C;
    Color_RGB8* temp_v0_2;
    u32 var_v1;

    sp80 = arg0->side->teamMember[arg0->thumbnail.shownTeamMemberIndex];
    sp7C = &arg0->side->teamMember[arg0->thumbnail.shownTeamMemberIndex]->pokemonPicked[arg0->thumbnail.shownRosterIndex];

    if (sp7C->hp == 0) {
        var_v1 = 1;
    } else {
        var_v1 = LabPC_StatusToIconIndex(sp7C->statusCondition);
    }

    temp_v0_2 = &((Color_RGB8*)&D_8218B008)[sp80->controllerPort];
    BattleHud_DrawMonInfoBox(arg0, sp7C, &D_80066AA0[var_v1], arg1 + 1, arg2 + 18, 70, 40, temp_v0_2->r, temp_v0_2->g,
                  temp_v0_2->b, 0xB2);
    BattleHud_DrawTrainerNameLabelAuto(arg0, sp80, arg1 + 1, arg2 + 1, sp80->controllerPort, arg3, arg4);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    BattleHud_DrawBorderTile(arg1, arg2, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0xF, 8, 8, D_03009440);
    BattleHud_DrawBorderTile(arg1, arg2 + 54, 8, 8, D_03009440);
    BattleHud_DrawBorderTile(arg1 + 65, arg2, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 65, arg2 + 15, 8, 8, D_030094C0);
    BattleHud_DrawBorderTile(arg1 + 65, arg2 + 51, 8, 8, D_030097C0);
    BattleHud_DrawBorderTile(arg1 + 8, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x10, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 24, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x20, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 40, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 48, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 56, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 57, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 18, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 16, arg2 + 18, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 24, arg2 + 18, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 32, arg2 + 18, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 40, arg2 + 18, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 48, arg2 + 18, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 56, arg2 + 18, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 57, arg2 + 18, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 51, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 16, arg2 + 51, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 24, arg2 + 51, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 32, arg2 + 51, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 40, arg2 + 51, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 48, arg2 + 51, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 56, arg2 + 51, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 57, arg2 + 51, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 8, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 21, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 29, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 37, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 45, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 46, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 65, arg2 + 8, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 65, arg2 + 21, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 65, arg2 + 29, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 65, arg2 + 37, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 65, arg2 + 45, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 65, arg2 + 47, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1, arg2 + 61, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 69, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 77, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 85, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 33, arg2 + 58, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 33, arg2 + 61, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 33, arg2 + 69, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 33, arg2 + 77, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 33, arg2 + 85, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 33, arg2 + 89, 8, 8, D_030097C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 89, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 4, arg2 + 89, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 12, arg2 + 89, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 20, arg2 + 89, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 28, arg2 + 89, 8, 8, D_030098C0);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    BattleHud_DrawTranslucentShadowRect(arg1 - 3, arg2 - 2, 78, 63, 0);
    BattleHud_DrawTranslucentShadowRect(arg1 - 3, arg2 + 58, 45, 41, 0);
    BattleHud_DrawPartyBallRow(arg0, arg1, arg2 + 0x62);
}

/**
 * Draws side 1's status box: the same parts as BattleHud_DrawMonStatusBoxPlayer, laid out
 * with the name label below the box and the party ball row above it.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (165 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleHud_DrawMonStatusBoxOpponent(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    TeamRoster* sp80;
    BattleMon* sp7C;
    Color_RGB8* temp_v0;
    u32 var_v1;

    sp80 = arg0->side->teamMember[arg0->thumbnail.shownTeamMemberIndex];
    sp7C = &arg0->side->teamMember[arg0->thumbnail.shownTeamMemberIndex]->pokemonPicked[arg0->thumbnail.shownRosterIndex];

    if (sp7C->hp == 0) {
        var_v1 = 1;
    } else {
        var_v1 = LabPC_StatusToIconIndex(sp7C->statusCondition);
    }

    temp_v0 = &((Color_RGB8*)&D_8218B008)[sp80->controllerPort];
    BattleHud_DrawMonInfoBox(arg0, sp7C, &D_80066AA0[var_v1], arg1, arg2 + 40, 70, 40, temp_v0->r, temp_v0->g, temp_v0->b,
                  0xB2);
    BattleHud_DrawTrainerNameLabelAuto(arg0, sp80, arg1, arg2 + 0x50, sp80->controllerPort, arg3, arg4);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    BattleHud_DrawBorderTile(arg1, arg2 + 76, 8, 8, D_03009440);
    BattleHud_DrawBorderTile(arg1, arg2 + 91, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1, arg2 + 39, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 36, 8, 8, D_030094C0);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 76, 8, 8, D_030094C0);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 91, 8, 8, D_030097C0);
    BattleHud_DrawBorderTile(arg1 + 7, arg2 + 39, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 39, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 16, arg2 + 39, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 24, arg2 + 39, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 32, arg2 + 39, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 40, arg2 + 39, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 48, arg2 + 39, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 56, arg2 + 39, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 7, arg2 + 79, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 79, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 16, arg2 + 79, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 24, arg2 + 79, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 32, arg2 + 79, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 40, arg2 + 79, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 48, arg2 + 79, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 56, arg2 + 79, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 7, arg2 + 91, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 91, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 16, arg2 + 91, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 24, arg2 + 91, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 32, arg2 + 91, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 40, arg2 + 91, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 48, arg2 + 91, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 56, arg2 + 91, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 44, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 52, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 60, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 68, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 82, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 83, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 44, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 52, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 60, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 68, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 82, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 83, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 30, arg2, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 8, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x10, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 24, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x20, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 30, arg2 + 8, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 30, arg2 + 16, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 30, arg2 + 24, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 30, arg2 + 31, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 0x20, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 40, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 48, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 55, arg2, 8, 8, D_03009940);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    BattleHud_DrawTranslucentShadowRect(arg1 + 27, arg2 - 2, 47, 42, 0);
    BattleHud_DrawTranslucentShadowRect(arg1 - 4, arg2 + 38, 77, 61, 0);
    BattleHud_DrawPartyBallRow(arg0, arg1 + 0x41, arg2 - 7);
}

extern u8 D_0300A2C0[];
extern u8 D_0300A440[];
extern char D_821959C4[];
extern char D_821959D0[];
extern char D_821959DC[];
/**
 * Draws the battle command menu: たたかう (Fight), ポケモン (Pokemon), にげる (Run).
 */
void BattleMenu_DrawCommandMenu(s32 arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 i;
    s32 pad; // FAKE

    Battle_DrawGradientRectWrapper(arg1 + 1, arg2 + 1, 0xC6, 0x10, arg3 * 3 + &D_8218B008, arg3 * 3 + &D_8218B014);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 - 1, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 4, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 11, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 193, arg2 - 1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 193, arg2 + 4, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 193, arg2 + 11, 8, 8, D_030097C0);
    for (i = 7; i != 0xC4; i += 7) {
        BattleHud_DrawBorderTile(arg1 + i, arg2 - 1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + i, arg2 + 11, 8, 8, D_030098C0);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    gSPDisplayList(gDisplayListHead++, D_80060308);
    Gfx_DrawTextureRgba16Ia8(arg1 + 7, arg2 + 3, 16, 12, D_03009E40, D_03009FC0, 16, 0x100000);
    Gfx_DrawTextureRgba16Ia8(arg1 + 70, arg2 + 3, 16, 12, D_0300A080, D_0300A200, 16, 0x100000);
    Gfx_DrawTextureRgba16Ia8(arg1 + 134, arg2 + 3, 16, 12, D_0300A2C0, D_0300A440, 16, 0x100000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    func_8001AB6C();
    Font_SetActive(1, 0);
    Font_Printf(arg1 + 22, arg2 + 4, D_821959C4);
    Font_Printf(arg1 + 86, arg2 + 4, D_821959D0);
    Font_Printf(arg1 + 150, arg2 + 4, D_821959DC);
    Font_EndTexturedTextRendering();
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 204, 22, 0);
}

extern u8 D_03009C00[];
extern u8 D_03009D80[];
extern u8 D_030099C0[];
extern u8 D_03009B40[];
extern char D_821959E4[];
extern char D_821959EC[];
/**
 * Draws the wide button bar with もどる (Back) and かくにん (Confirm).
 */
void BattleMenu_DrawBackConfirmBar(s32 arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 i;
    s32 pad; // FAKE

    Battle_DrawGradientRectWrapper(arg1 + 1, arg2 + 1, 0x7D, 0x10, arg3 * 3 + &D_8218B008, arg3 * 3 + &D_8218B014);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 - 1, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 4, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 11, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 119, arg2 - 1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 119, arg2 + 4, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 119, arg2 + 11, 8, 8, D_030097C0);
    for (i = 7; i != 0x77; i += 7) {
        BattleHud_DrawBorderTile(arg1 + i, arg2 - 1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + i, arg2 + 11, 8, 8, D_030098C0);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    gSPDisplayList(gDisplayListHead++, D_80060308);
    Gfx_DrawTextureRgba16Ia8(arg1 + 7, arg2 + 3, 16, 12, D_030099C0, D_03009B40, 16, 0x100000);
    Gfx_DrawTextureRgba16Ia8(arg1 + 64, arg2 + 3, 16, 12, D_03009C00, D_03009D80, 16, 0x100000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    func_8001AB6C();
    Font_SetActive(1, 0);
    Font_Printf(arg1 + 24, arg2 + 4, D_821959E4);
    Font_Printf(arg1 + 81, arg2 + 4, D_821959EC);
    Font_EndTexturedTextRendering();
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 131, 22, 0);
}

extern u8 D_03009C00[];
extern u8 D_03009D80[];
extern char D_821959F8[];
/**
 * Draws the small かくにん (Confirm) button.
 * Seen in play (2026-11-12): first ran on the frame before the R かくにん button appeared beside
 * COM's panel while COM picked a replacement for its fainted Pinsir (カイのすけ).
 */
void BattleMenu_DrawConfirmButton(s32 arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 i;
    s32 pad; // FAKE

    Battle_DrawGradientRectWrapper(arg1 + 1, arg2 + 1, 0x47, 0x10, arg3 * 3 + &D_8218B008, arg3 * 3 + &D_8218B014);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 - 1, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 4, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 11, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 - 1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 4, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 63, arg2 + 11, 8, 8, D_030097C0);
    for (i = 7; i != 0x3F; i += 7) {
        BattleHud_DrawBorderTile(arg1 + i, arg2 - 1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + i, arg2 + 11, 8, 8, D_030098C0);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    gSPDisplayList(gDisplayListHead++, D_80060308);
    Gfx_DrawTextureRgba16Ia8(arg1 + 7, arg2 + 3, 16, 12, D_03009C00, D_03009D80, 16, 0x100000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    func_8001AB6C();
    Font_SetActive(1, 0);
    Font_Printf(arg1 + 24, arg2 + 4, D_821959F8);
    Font_EndTexturedTextRendering();
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 74, 22, 0);
}

/**
 * Draws a string centered on x, assuming 10 pixels per two-byte character.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name from the code.
 */
void BattleHud_DrawTextCentered(s32 arg0, s32 arg1, s32 arg2) {
    Font_Printf(arg0 - ((func_800566BC(arg2) >> 1) * 0xA), arg1, arg2);
}
