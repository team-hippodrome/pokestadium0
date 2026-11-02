/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_2FA4D0.c, src/fragments/battle_engine/battle_engine_31D9F0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_renderer.h"

#include "fragments/battle_engine/battle_engine.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "status_icons.h"
#include "game_state.h"
#include "text_system.h"
#include "3D140.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"

#include "m2c_macros.h"

void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);

void func_82116D20(void);
void func_82116D28(void);
s32 BattleHud_DrawBorderTile(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4);
void ParticleEffect_InitNoop(void);
void BattleHud_DrawPlainText(s16 arg0, s16 arg1, char* arg2);
void BattleScene_DrawStripWipeIfActive(void);

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

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, s32);               /* extern */
M2C_UNK func_8001AA9C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
u32 func_800566BC(s32);                             /* extern */
M2C_UNK func_82116CF4(s16, s16, M2C_UNK, M2C_UNK, s8 *, s8 *); /* extern */
extern s8 D_8218B008;
extern s8 D_8218B014;
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

extern s8 D_8219597C;
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

#ifdef NON_MATCHING
/* TODO: decompile func_821172F0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821172F0.s")
#endif

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

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
extern f32 D_FLT_82199EB0;
void func_82116480(s8* arg0, s16 arg1, s16 arg2);
void func_82117610(s16 x, s16 y) {
    UNUSED s32 pad;
    s8 buf[12];
    f32 time = D_FLT_82199EB0 / 30.0f;
    UNUSED s32 pad2[3];

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
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82117610.s")
#endif

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
extern f32 D_FLT_82199EB4;
void func_8211778C(s16 x, s16 y) {
    UNUSED s32 pad;
    s8 buf[12];
    f32 time = D_FLT_82199EB4 / 30.0f;
    UNUSED s32 pad2[3];

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
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211778C.s")
#endif

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void BattleHud_DrawPartyBallRow(ActivePokemon* arg0, s16 arg1, s16 arg2) {
    u8* sp74[] = { D_3006170, D_30061D0, D_3006230 };
    UNUSED s32 pad;
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
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82117908.s")
#endif

extern Color_RGB8 D_84385860[];
extern unk_D_84385790 D_84385790[];
u32 func_8001FA30(s32);
extern unk_D_84385790 D_80066AA0[];
void func_821172F0(ActivePokemon* arg0, BattleMon* arg1, unk_D_84385790* arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
extern u8 D_030096C0[];
extern u8 D_03009440[];
extern u8 D_03009840[];
extern u8 D_030094C0[];
extern u8 D_030097C0[];
extern u8 D_03009940[];
extern u8 D_030098C0[];
extern u8 D_030095C0[];
extern u8 D_03009740[];
extern u8 D_03009640[];
void BattleHud_DrawMonStatusBoxPlayer(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4) {
    UNUSED s32 pad[2];
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
    func_821172F0(arg0, sp7C, &D_80066AA0[var_v1], arg1 + 1, arg2 + 0x12, 0x46, 0x28, temp_v0_2->r, temp_v0_2->g,
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

extern Color_RGB8 D_84385860[];
extern unk_D_84385790 D_84385790[];
extern u8 D_03009440[];
extern u8 D_03009640[];
void BattleHud_DrawMonStatusBoxOpponent(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4) {
    UNUSED s32 pad[2];
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
    func_821172F0(arg0, sp7C, &D_80066AA0[var_v1], arg1, arg2 + 0x28, 0x46, 0x28, temp_v0->r, temp_v0->g, temp_v0->b,
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

#ifdef NON_MATCHING
/* TODO: decompile func_82118FD8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82118FD8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82119364; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82119364.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821196A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821196A4.s")
#endif

M2C_UNK func_8001A944(s32, s32, s32);               /* extern */
u32 func_800566BC(s32);                             /* extern */

void func_82119994(s32 arg0, s32 arg1, s32 arg2) {
    func_8001A944(arg0 - ((func_800566BC(arg2) >> 1) * 0xA), arg1, arg2);
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
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
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821199E4.s")
#endif

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
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
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82119B48.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82119CAC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82119CAC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211AAC4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211AAC4.s")
#endif

void BattleHud_DrawPlainText(s16 arg0, s16 arg1, char* arg2) {
    Font_BeginTranslucentTextRendering();
    Font_SetActive(1, 0);
    Font_Printf(arg0, arg1, arg2);
    Font_EndTexturedTextRendering();
}

extern u8 D_030078C0[];
extern u8 D_03007A80[];
extern u8 D_030077E0[];
extern u8 D_0300A080[];
extern u8 D_0300A200[];
extern u8 D_030070E0[];
extern u8 D_030072A0[];
extern u8 D_03007380[];
extern u8 D_03007540[];
extern u8 D_03009E40[];
extern u8 D_03009FC0[];
extern Gfx D_80060308[];
extern u8* D_8218AFDC[];
void Widget_DrawMeterBar(s32, s32, s32, s32);
s32 LabPC_StatusToIconIndex(s32);
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

/**
 * Draws one party-slot HUD row for the current Pokemon (compare func_8211AEA4, which handles
 * six slot icons): level number, HP meter bar and HP fraction text, then the slot icon chosen
 * by arg4 (0..2 only in this variant), the name text, and the status-condition icon when the
 * party member has HP left and a non-zero LabPC_StatusToIconIndex (a fainted member forces
 * icon 1). arg0 is the team roster, arg1 the displayed BattleMon, (arg2, arg3) the row origin.
 */
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

#ifdef NON_MATCHING
/* TODO: decompile func_8211B484; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211B484.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211B900; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211B900.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211BEA8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211BEA8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211C1B8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211C1B8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211C43C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211C43C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211C6C0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211C6C0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211C9FC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211C9FC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211CB0C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211CB0C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211CBCC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211CBCC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211CC8C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211CC8C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211D06C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211D06C.s")
#endif

void BattleScene_DrawStripWipeIfActive(void) {
    if (BattleScene_GetStripWipeState() != 0) {
        BattleScene_DrawStripWipe();
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8211D3D8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211D3D8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211D5F4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211D5F4.s")
#endif

/*
 * func_8211D874
 *
 * Calls func_8001AC7C(arg0, arg1, 0x6E, 0x1E, 0, 0, 0, 0x3C), then
 * func_8001AB6C() and func_8001A384(1, 0), then func_8001A944 twice: with
 * (arg0 + 3, arg1 + 4, &D_82195BE4) and with (arg0 + 0x23, arg1 + 0x10,
 * D_8218B15C[D_8219A5A4]), and finally func_8001ABBC().  D_8219A5A4 selects
 * an entry of the word-sized table D_8218B15C, which is passed on as the
 * third argument.  The calls look like a begin / draw / end sequence
 * positioned relative to (arg0, arg1), but that is an inference.
 *
 * The roles of the func_8001A... helpers are not established here.
 */
M2C_UNK func_8001AC7C(s16, s16, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
extern M2C_UNK D_82195BE4;
extern s32 D_8218B15C[];
extern s32 D_8219A5A4;

void func_8211D874(s16 arg0, s16 arg1) {
    func_8001AC7C(arg0, arg1, 0x6E, 0x1E, 0, 0, 0, 0x3C);
    func_8001AB6C();
    func_8001A384(1, 0);
    func_8001A944(arg0 + 3, arg1 + 4, (s32)&D_82195BE4);
    func_8001A944(arg0 + 0x23, arg1 + 0x10, D_8218B15C[D_8219A5A4]);
    func_8001ABBC();
}

#ifdef NON_MATCHING
/* TODO: decompile func_8211D920; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211D920.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211DDC0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211DDC0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211E164; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211E164.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211E414; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211E414.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211E5F4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211E5F4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8211E794; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8211E794.s")
#endif
