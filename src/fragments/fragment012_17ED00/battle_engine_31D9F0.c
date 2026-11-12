/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_31D9F0.h"

void func_82116D20(void) {
}

void func_82116D28(void) {
}

void BattleHud_DrawLevelNumber(s32 arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s8* var_s2;
    s8 sp58[2];
    UNUSED s32 pad2[2]; // FAKE: stack padding
    u8** temp_s4;

    var_s2 = &sp58;
    temp_s4 = Memmap_GetSegmentVaddr(D_300B870);
    sprintf(sp58, "%d", arg2);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    if (arg2 >= 0x64) {
        arg0 -= 2;
        Gfx_DrawTextureRgba16(arg0, arg1, 8, 6, temp_s4[sp58[0] - '0'], 8, 0);
        arg0 += 8;
        var_s2 = &sp58[1];
    } else {
        Gfx_DrawTextureRgba16(arg0, arg1, 4, 6, temp_s4[11], 4, 0);
        arg0 += 5;
    }

    while (*var_s2 != 0) {
        Gfx_DrawTextureRgba16(arg0, arg1, 8, 6, temp_s4[*var_s2 - '0'], 8, 0);
        arg0 += 8;
        var_s2++;
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

void BattleHud_DrawHpFractionText(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s8 sp70[7];
    UNUSED s32 pad2; // FAKE: stack padding
    u8** temp_s2;
    u8* var_v0;
    s32 i;

    temp_s2 = Memmap_GetSegmentVaddr(D_300B870);
    sprintf(sp70, "%3d/%3d", arg2, arg3);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    for (i = 0; i < sizeof(sp70); i++) {
        switch (sp70[i]) {
            case ' ':
                var_v0 = NULL;
                break;

            case '/':
                var_v0 = temp_s2[10];
                break;

            default:
                var_v0 = temp_s2[sp70[i] - '0'];
                break;
        }

        if (var_v0 != NULL) {
            func_8001B884(arg0, arg1, 8, 6, var_v0, 8, 0);
        }

        arg0 += 8;
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

void BattleHud_DrawSpeciesNameLabel(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 sp24;
    s32 temp_v0;

    temp_v0 = arg2 * 3;
    func_82116CF4(arg0, arg1, 0x46, 0x11, temp_v0 + &D_8218B008, temp_v0 + &D_8218B014);
    func_8001AB6C();
    if (arg4 != 0) {
        func_8001AA9C(0xFF, 0x64, 0xFF, 0xFF);
    }
    sp24 = func_800566BC(arg3) >> 1;
    func_8001A384(2, 0);
    func_8001A944((arg0 - (sp24 * 5)) + 0x1E, arg1 + 2, arg3);
    func_8001ABBC();
}

void BattleHud_DrawSpeciesNameLabelBlink(s16 arg0, s16 arg1, s32 arg2, s32 arg3, u16 arg4, s32 arg5) {
    UNUSED s32 pad; // FAKE: stack padding
    s16 wave;
    s16 alpha;
    u32 half;
    s32 temp_v0;

    wave = gCosineTable[arg4 >> 4] * 255.0f;
    alpha = wave;
    if (wave < 0) {
        alpha = -wave;
    }
    temp_v0 = arg2 * 3;
    func_82116CF4(arg0, arg1, 0x46, 0x11, temp_v0 + &D_8218B008, temp_v0 + &D_8218B014);
    func_8001AB6C();
    func_8001A384(2, 0);
    if (arg5 != 0) {
        func_8001AA9C(0xFF, 0x64, 0xFF, (s8)alpha);
    } else {
        func_8001AA9C(0xFF, 0xFF, 0xFF, (s8)alpha);
    }
    half = func_800566BC(arg3) >> 1;
    if (wave > 0) {
        func_8001A944(arg0 + 0xE, arg1 + 2, (s32)&D_8219597C);
    } else {
        func_8001A944((arg0 - (half * 5)) + 0x1E, arg1 + 2, arg3);
    }
    func_8001ABBC();
}

void BattleHud_DrawSpeciesNameLabelAuto(ActivePokemon* arg0, TeamRoster* arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s32 arg6) {
    ActivePokemonState* ptr = &arg0->state;
    s32 var_t0 = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (ptr->moveSlotIllegality[i] == 1) {
            var_t0 = 1;
        }
    }

    if (arg6 == 0) {
        BattleHud_DrawSpeciesNameLabel(arg2, arg3, arg4, &arg1->trainerName, var_t0);
    } else {
        BattleHud_DrawSpeciesNameLabelBlink(arg2, arg3, arg4, &arg1->trainerName, arg5, var_t0);
    }
}

/**
 * Draws a Pokemon's info box: background (clipped at the left edge), level, HP bar, HP fraction,
 * the nickname centered on top and the status text in its color. Called every frame from
 * BattleHud_DrawMonStatusBoxPlayer.
 * @unverified Name from the code.
 */
void BattleHud_DrawMonInfoBox(ActivePokemon* arg0, BattleMon* arg1, unk_D_84385790* arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    u32 half;

    if (arg3 < 0) {
        if (arg5 + arg3 < 0) {
            Ui_DrawPrimColorRect(0, arg4, 0, arg6, arg7, arg8, arg9, argA);
        } else {
            Ui_DrawPrimColorRect(0, arg4, arg5 + arg3, arg6, arg7, arg8, arg9, argA);
        }
    } else {
        Ui_DrawPrimColorRect(arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA);
    }
    BattleHud_DrawLevelNumber(arg3 + 3, arg4 + 0x10, arg1->level);
    Widget_DrawMeterBar(arg3 + 2, arg4 + 0x19, arg1->hp, arg1->maxHp);
    BattleHud_DrawHpFractionText(arg3 + 0xC, arg4 + 0x1F, arg1->hp, arg1->maxHp);
    func_8001AB6C();
    func_8001A384(2, 0);
    half = func_800566BC((s32)arg1->nickname) >> 1;
    func_8001A944((arg3 - (half * 5)) + 0x1D, arg4 + 2, arg1->nickname);
    func_8001A384(1, 0);
    func_8001AA9C(arg2->unk_04.r, arg2->unk_04.g, arg2->unk_04.b, 0xFF);
    func_8001A944(arg3 + 0x1F, arg4 + 0xE, arg2->unk_00);
    func_8001ABBC();
}

s32 BattleHud_DrawBorderTile(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4) {
    UNUSED s32 pad[4]; // FAKE: stack padding
    s32 sp2C;
    s32 sp28;

    if (arg2 < 9) {
        sp2C = 0x400;
    } else {
        sp2C = 0;
    }

    // clang-format off
    if (arg3 < 9) { sp28 = 0x400; } else { sp28 = 0; }
    // clang-format on

    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRect(arg0, arg1, (arg0 + arg2) - 1, (arg1 + arg3) - 1, sp2C, sp28, 0);
}

void ParticleEffect_InitNoop(void) {
}
