/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_31D9F0.h"

void func_82116D20(void) {
}

void func_82116D28(void) {
}

void BattleHud_DrawLevelNumber(s32 arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad[2];
    s8* var_s2;
    s8 sp58[2];
    UNUSED s32 pad2[2];
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
    UNUSED s32 pad[2];
    s8 sp70[7];
    UNUSED s32 pad2;
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

void func_82116FF4(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4) {
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

void func_821170D0(s16 arg0, s16 arg1, s32 arg2, s32 arg3, u16 arg4, s32 arg5) {
    UNUSED s32 pad;
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
        BattleHud_DrawSpeciesNameLabel(arg2, arg3, arg4, &arg1->unk_008, var_t0);
    } else {
        BattleHud_DrawSpeciesNameLabelBlink(arg2, arg3, arg4, &arg1->unk_008, arg5, var_t0);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821172F0.s")

s32 BattleHud_DrawBorderTile(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4) {
    UNUSED s32 pad[4];
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
