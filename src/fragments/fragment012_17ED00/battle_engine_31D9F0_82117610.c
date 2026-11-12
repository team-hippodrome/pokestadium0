/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_31D9F0.h"

/* Zero uses different segmented addresses for the three party-ball textures. */
extern u8 D_03006C40[];
extern u8 D_03006CA0[];
extern u8 D_03006D00[];

void func_82117610(s16 x, s16 y) {
    UNUSED s32 pad; // FAKE: stack padding
    s8 buf[12];
    f32 time = D_FLT_82199EB0 / 30.0f;
    UNUSED s32 pad2[3]; // FAKE: stack padding

    Font_BeginTranslucentTextRendering();
    Font_SetActive(1, 0);
    Font_Printf(x + 3, y + 3, "TIME");
    Font_EndTexturedTextRendering();
    sprintf(buf, "%02d", (s32)(time / 60.0f));
    func_82116480(buf, x + 0x32, y + 5);
    sprintf(buf, "%02d", (s32)time % 60);
    func_82116480(buf, x + 0x46, y + 5);
    sprintf(buf, "%02d", (s32)(time * 100.0) % 100);
    func_82116480(buf, x + 0x5A, y + 5);
}


void func_8211778C(s16 x, s16 y) {
    UNUSED s32 pad; // FAKE: stack padding
    s8 buf[12];
    f32 time = D_FLT_82199EB4 / 30.0f;
    UNUSED s32 pad2[3]; // FAKE: stack padding

    Font_BeginTranslucentTextRendering();
    Font_SetActive(1, 0);
    Font_Printf(x + 3, y + 3, "TOTAL TIME");
    Font_EndTexturedTextRendering();
    sprintf(buf, "%02d", (s32)(time / 60.0f));
    func_82116480(buf, x + 0x6E, y + 5);
    sprintf(buf, "%02d", (s32)time % 60);
    func_82116480(buf, x + 0x82, y + 5);
    sprintf(buf, "%02d", (s32)(time * 100.0) % 100);
    func_82116480(buf, x + 0x96, y + 5);
}


void BattleHud_DrawPartyBallRow(ActivePokemon* arg0, s16 arg1, s16 arg2) {
    u8* sp74[] = { D_03006C40, D_03006CA0, D_03006D00 };
    UNUSED s32 pad; // FAKE: stack padding
    s32 i;
    s32 j;
    s32 var_v0_2;

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    if (arg0 == sActivePokemon[0]) {
        if (arg0->sessionTeams->tagTeamSize == 1) {
            for (i = 0; i < arg0->sessionTeams->teamMember[0]->numberOfPokemonBrought; i++) {
                if (arg0->sessionTeams->teamMember[0]->pokemonPicked[i].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->sessionTeams->teamMember[0]->pokemonPicked[i].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 + i * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }
        } else {
            for (i = 0; i < arg0->sessionTeams->teamMember[0]->numberOfPokemonBrought; i++) {
                if (arg0->sessionTeams->teamMember[0]->pokemonPicked[i].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->sessionTeams->teamMember[0]->pokemonPicked[i].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 + i * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }

            for (j = 0; j < arg0->sessionTeams->teamMember[1]->numberOfPokemonBrought; j++) {
                if (arg0->sessionTeams->teamMember[1]->pokemonPicked[j].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->sessionTeams->teamMember[1]->pokemonPicked[j].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 + i * 7 + j * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }
        }
    }

    if (arg0 == sActivePokemon[1]) {
        if (arg0->sessionTeams->tagTeamSize == 1) {
            for (i = 0; i < arg0->sessionTeams->teamMember[0]->numberOfPokemonBrought; i++) {
                if (arg0->sessionTeams->teamMember[0]->pokemonPicked[i].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->sessionTeams->teamMember[0]->pokemonPicked[i].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 - i * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }
        } else {
            for (i = 0; i < arg0->sessionTeams->teamMember[0]->numberOfPokemonBrought; i++) {
                if (arg0->sessionTeams->teamMember[0]->pokemonPicked[i].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->sessionTeams->teamMember[0]->pokemonPicked[i].statusCondition != 0) {
                    var_v0_2 = 1;
                } else {
                    var_v0_2 = 0;
                }
                Gfx_DrawTextureRgba16(arg1 - i * 7, arg2, 8, 6, sp74[var_v0_2], 8, 0);
            }

            for (j = 0; j < arg0->sessionTeams->teamMember[1]->numberOfPokemonBrought; j++) {
                if (arg0->sessionTeams->teamMember[1]->pokemonPicked[j].hp == 0) {
                    var_v0_2 = 2;
                } else if (arg0->sessionTeams->teamMember[1]->pokemonPicked[j].statusCondition != 0) {
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


void BattleHud_DrawMonStatusBoxPlayer(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    TeamRoster* sp80;
    BattleMon* sp7C;
    Color_RGB8* temp_v0_2;
    u32 var_v1;

    sp80 = arg0->sessionTeams->teamMember[M2C_FIELD(arg0, s32*, 0x9D4)];
    sp7C = &arg0->sessionTeams->teamMember[M2C_FIELD(arg0, s32*, 0x9D4)]->pokemonPicked[M2C_FIELD(arg0, s32*, 0x9D0)];

    if (sp7C->hp == 0) {
        var_v1 = 1;
    } else {
        var_v1 = func_8001FA30(sp7C->statusCondition);
    }

    temp_v0_2 = &((Color_RGB8*)&D_8218B008)[sp80->controllerPort];
    BattleHud_DrawMonInfoBox(arg0, sp7C, &D_80066AA0[var_v1], arg1 + 1, arg2 + 0x12, 0x46, 0x28, temp_v0_2->r, temp_v0_2->g,
                  temp_v0_2->b, 0xB2);
    BattleHud_DrawSpeciesNameLabelAuto(arg0, sp80, arg1 + 1, arg2 + 1, sp80->controllerPort, arg3, arg4);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    BattleHud_DrawBorderTile(arg1, arg2, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0xF, 8, 8, D_03009440);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x36, 8, 8, D_03009440);
    BattleHud_DrawBorderTile(arg1 + 0x41, arg2, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0x41, arg2 + 0xF, 8, 8, D_030094C0);
    BattleHud_DrawBorderTile(arg1 + 0x41, arg2 + 0x33, 8, 8, D_030097C0);
    BattleHud_DrawBorderTile(arg1 + 8, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x10, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x18, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x20, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x28, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x30, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x38, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x39, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 0x12, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x10, arg2 + 0x12, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x18, arg2 + 0x12, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x20, arg2 + 0x12, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x28, arg2 + 0x12, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x30, arg2 + 0x12, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x38, arg2 + 0x12, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x39, arg2 + 0x12, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 0x33, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x10, arg2 + 0x33, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x18, arg2 + 0x33, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x20, arg2 + 0x33, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x28, arg2 + 0x33, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x30, arg2 + 0x33, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x38, arg2 + 0x33, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x39, arg2 + 0x33, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 8, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x15, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x1D, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x25, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x2D, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x2E, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 0x41, arg2 + 8, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x41, arg2 + 0x15, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x41, arg2 + 0x1D, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x41, arg2 + 0x25, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x41, arg2 + 0x2D, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x41, arg2 + 0x2F, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x3D, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x45, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x4D, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x55, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 0x21, arg2 + 0x3A, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x21, arg2 + 0x3D, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x21, arg2 + 0x45, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x21, arg2 + 0x4D, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x21, arg2 + 0x55, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x21, arg2 + 0x59, 8, 8, D_030097C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x59, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 4, arg2 + 0x59, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0xC, arg2 + 0x59, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x14, arg2 + 0x59, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x1C, arg2 + 0x59, 8, 8, D_030098C0);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    BattleHud_DrawTranslucentShadowRect(arg1 - 3, arg2 - 2, 0x4E, 0x3F, 0);
    BattleHud_DrawTranslucentShadowRect(arg1 - 3, arg2 + 0x3A, 0x2D, 0x29, 0);
    BattleHud_DrawPartyBallRow(arg0, arg1, arg2 + 0x62);
}

void BattleHud_DrawMonStatusBoxOpponent(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    TeamRoster* sp80;
    BattleMon* sp7C;
    Color_RGB8* temp_v0;
    u32 var_v1;

    sp80 = arg0->sessionTeams->teamMember[M2C_FIELD(arg0, s32*, 0x9D4)];
    sp7C = &arg0->sessionTeams->teamMember[M2C_FIELD(arg0, s32*, 0x9D4)]->pokemonPicked[M2C_FIELD(arg0, s32*, 0x9D0)];

    if (sp7C->hp == 0) {
        var_v1 = 1;
    } else {
        var_v1 = func_8001FA30(sp7C->statusCondition);
    }

    temp_v0 = &((Color_RGB8*)&D_8218B008)[sp80->controllerPort];
    BattleHud_DrawMonInfoBox(arg0, sp7C, &D_80066AA0[var_v1], arg1, arg2 + 0x28, 0x46, 0x28, temp_v0->r, temp_v0->g, temp_v0->b,
                  0xB2);
    BattleHud_DrawSpeciesNameLabelAuto(arg0, sp80, arg1, arg2 + 0x50, sp80->controllerPort, arg3, arg4);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    BattleHud_DrawBorderTile(arg1, arg2 + 0x4C, 8, 8, D_03009440);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x5B, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x27, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x24, 8, 8, D_030094C0);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x4C, 8, 8, D_030094C0);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x5B, 8, 8, D_030097C0);
    BattleHud_DrawBorderTile(arg1 + 7, arg2 + 0x27, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 0x27, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x10, arg2 + 0x27, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x18, arg2 + 0x27, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x20, arg2 + 0x27, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x28, arg2 + 0x27, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x30, arg2 + 0x27, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x38, arg2 + 0x27, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 7, arg2 + 0x4F, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 0x4F, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x10, arg2 + 0x4F, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x18, arg2 + 0x4F, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x20, arg2 + 0x4F, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x28, arg2 + 0x4F, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x30, arg2 + 0x4F, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x38, arg2 + 0x4F, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 7, arg2 + 0x5B, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 8, arg2 + 0x5B, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x10, arg2 + 0x5B, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x18, arg2 + 0x5B, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x20, arg2 + 0x5B, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x28, arg2 + 0x5B, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x30, arg2 + 0x5B, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1 + 0x38, arg2 + 0x5B, 8, 8, D_030098C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x2C, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x34, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x3C, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x44, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x52, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1, arg2 + 0x53, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x2C, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x34, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x3C, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x44, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x52, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x53, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0x1E, arg2, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 8, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x10, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x18, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0x20, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x1E, arg2 + 8, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 0x1E, arg2 + 0x10, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 0x1E, arg2 + 0x18, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 0x1E, arg2 + 0x1F, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 + 0x20, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x28, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x30, arg2, 8, 8, D_03009940);
    BattleHud_DrawBorderTile(arg1 + 0x37, arg2, 8, 8, D_03009940);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    BattleHud_DrawTranslucentShadowRect(arg1 + 0x1B, arg2 - 2, 0x2F, 0x2A, 0);
    BattleHud_DrawTranslucentShadowRect(arg1 - 4, arg2 + 0x26, 0x4D, 0x3D, 0);
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

    func_82116CF4(arg1 + 1, arg2 + 1, 0xC6, 0x10, arg3 * 3 + &D_8218B008, arg3 * 3 + &D_8218B014);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 - 1, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 4, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 0xB, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0xC1, arg2 - 1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0xC1, arg2 + 4, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0xC1, arg2 + 0xB, 8, 8, D_030097C0);
    for (i = 7; i != 0xC4; i += 7) {
        BattleHud_DrawBorderTile(arg1 + i, arg2 - 1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + i, arg2 + 0xB, 8, 8, D_030098C0);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    gSPDisplayList(gDisplayListHead++, D_80060308);
    Gfx_DrawTextureRgba16Ia8(arg1 + 7, arg2 + 3, 0x10, 0xC, D_03009E40, D_03009FC0, 0x10, 0x100000);
    Gfx_DrawTextureRgba16Ia8(arg1 + 0x46, arg2 + 3, 0x10, 0xC, D_0300A080, D_0300A200, 0x10, 0x100000);
    Gfx_DrawTextureRgba16Ia8(arg1 + 0x86, arg2 + 3, 0x10, 0xC, D_0300A2C0, D_0300A440, 0x10, 0x100000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg1 + 0x16, arg2 + 4, D_821959C4);
    func_8001A944(arg1 + 0x56, arg2 + 4, D_821959D0);
    func_8001A944(arg1 + 0x96, arg2 + 4, D_821959DC);
    func_8001ABBC();
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 0xCC, 0x16, 0);
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

    func_82116CF4(arg1 + 1, arg2 + 1, 0x7D, 0x10, arg3 * 3 + &D_8218B008, arg3 * 3 + &D_8218B014);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 - 1, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 4, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 0xB, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0x77, arg2 - 1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0x77, arg2 + 4, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x77, arg2 + 0xB, 8, 8, D_030097C0);
    for (i = 7; i != 0x77; i += 7) {
        BattleHud_DrawBorderTile(arg1 + i, arg2 - 1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + i, arg2 + 0xB, 8, 8, D_030098C0);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    gSPDisplayList(gDisplayListHead++, D_80060308);
    Gfx_DrawTextureRgba16Ia8(arg1 + 7, arg2 + 3, 0x10, 0xC, D_030099C0, D_03009B40, 0x10, 0x100000);
    Gfx_DrawTextureRgba16Ia8(arg1 + 0x40, arg2 + 3, 0x10, 0xC, D_03009C00, D_03009D80, 0x10, 0x100000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg1 + 0x18, arg2 + 4, D_821959E4);
    func_8001A944(arg1 + 0x51, arg2 + 4, D_821959EC);
    func_8001ABBC();
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 0x83, 0x16, 0);
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

    func_82116CF4(arg1 + 1, arg2 + 1, 0x47, 0x10, arg3 * 3 + &D_8218B008, arg3 * 3 + &D_8218B014);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 - 1, 8, 8, D_030096C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 4, 8, 8, D_030095C0);
    BattleHud_DrawBorderTile(arg1 - 1, arg2 + 0xB, 8, 8, D_03009640);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 - 1, 8, 8, D_03009840);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 4, 8, 8, D_03009740);
    BattleHud_DrawBorderTile(arg1 + 0x3F, arg2 + 0xB, 8, 8, D_030097C0);
    for (i = 7; i != 0x3F; i += 7) {
        BattleHud_DrawBorderTile(arg1 + i, arg2 - 1, 8, 8, D_03009940);
        BattleHud_DrawBorderTile(arg1 + i, arg2 + 0xB, 8, 8, D_030098C0);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    gSPDisplayList(gDisplayListHead++, D_80060308);
    Gfx_DrawTextureRgba16Ia8(arg1 + 7, arg2 + 3, 0x10, 0xC, D_03009C00, D_03009D80, 0x10, 0x100000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg1 + 0x18, arg2 + 4, D_821959F8);
    func_8001ABBC();
    BattleHud_DrawTranslucentShadowRect(arg1 - 2, arg2 - 2, 0x4A, 0x16, 0);
}

/**
 * Draws a string centred on x, assuming 10 pixels per two-byte character.
 * @unverified Name from the code.
 */
void BattleHud_DrawTextCentered(s32 arg0, s32 arg1, s32 arg2) {
    func_8001A944(arg0 - ((func_800566BC(arg2) >> 1) * 0xA), arg1, arg2);
}
