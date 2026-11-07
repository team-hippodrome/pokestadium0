/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_31D9F0.h"

s32 BattleHud_DrawMovePpTextLTR(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[2];
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


s32 BattleHud_DrawMovePpTextRTL(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[2];
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


#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82119CAC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211AAC4.s")

void BattleHud_DrawPlainText(s16 arg0, s16 arg1, char* arg2) {
    Font_BeginTranslucentTextRendering();
    Font_SetActive(1, 0);
    Font_Printf(arg0, arg1, arg2);
    Font_EndTexturedTextRendering();
}

void func_8211AEA4(TeamRoster* arg0, BattleMon* arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_t0;

    BattleHud_DrawLevelNumber(arg2 + 3, arg3 + 4, arg1->unk_24);
    Widget_DrawMeterBar(arg2 + 0x1E, arg3 + 0xE, arg1->hp, arg1->unk_26);
    BattleHud_DrawHpFractionText(arg2 + 0x26, arg3 + 0x14, arg1->hp, arg1->unk_26);

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
    Font_Printf(arg2 + 0x18, arg3 + 2, arg1->unk_30);
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

void func_8211B208(TeamRoster* arg0, BattleMon* arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_t0;

    BattleHud_DrawLevelNumber(arg2 + 3, arg3 + 4, arg1->unk_24);
    Widget_DrawMeterBar(arg2 + 0x1E, arg3 + 0xE, arg1->hp, arg1->unk_26);
    BattleHud_DrawHpFractionText(arg2 + 0x26, arg3 + 0x14, arg1->hp, arg1->unk_26);

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
    Font_Printf(arg2 + 0x18, arg3 + 2, arg1->unk_30);
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211B484.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211B900.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211BEA8.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211C1B8.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211C43C.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211C6C0.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211C9FC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211CB0C.s")

extern s8 D_8219A4A0[];
extern s8 D_8219A4C8[];
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211CC8C.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211D06C.s")

void BattleScene_DrawStripWipeIfActive(void) {
    if (BattleScene_GetStripWipeState() != 0) {
        BattleScene_DrawStripWipe();
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211D3D8.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211D5F4.s")

void func_8211D874(s16 arg0, s16 arg1) {
    func_8001AC7C(arg0, arg1, 0x6E, 0x1E, 0, 0, 0, 0x3C);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg0 + 3, arg1 + 4, (s32)&D_82195BE4);
    func_8001A944(arg0 + 0x23, arg1 + 0x10, D_8218B15C[D_8219A5A4]);
    func_8001ABBC();
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211D920.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211DDC0.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211E164.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211E414.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211E5F4.s")

s32 func_800564D4(char*, const char*, ...);
extern s8* D_8219A5A0;
extern char D_82195FF4[];
extern char D_82195FF8[];
void func_8211E794(s16 arg0, s16 arg1) {
    char buf[16];

    func_8001AC7C(arg0, arg1, 0x50, 0x1E, 0, 0, 0, 0x3C);
    func_800564D4(buf, D_82195FF4, M2C_FIELD(M2C_FIELD(D_8219A5A0, s8**, 0xCC), f32*, 0x34));
    func_82116480(buf, arg0 + 3, arg1 + 2);
    func_800564D4(buf, D_82195FF8, M2C_FIELD(M2C_FIELD(D_8219A5A0, s8**, 0xCC), f32*, 0x38));
    func_82116480(buf, arg0 + 3, arg1 + 0x10);
}
