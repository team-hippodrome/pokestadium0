#ifndef ZERO_BATTLE_ENGINE_31D9F0_H
#define ZERO_BATTLE_ENGINE_31D9F0_H

/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_2FA4D0.c, src/fragments/battle_engine/battle_engine_31D9F0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_renderer.h"

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

void BattleHud_DrawLevelNumber(s32 arg0, s32 arg1, s32 arg2);

void BattleHud_DrawHpFractionText(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, s8*);              /* extern */
M2C_UNK func_8001AA9C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
void func_8001ABBC(void);
u32 func_800566BC(s8*);                            /* extern */
M2C_UNK func_82116CF4(s32, s32, M2C_UNK, M2C_UNK, s8 *, s8 *); /* extern */
extern s8 D_8218B008;
extern s8 D_8218B014;
void BattleHud_DrawSpeciesNameLabel(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4);

extern s8 D_8219597C;
void BattleHud_DrawSpeciesNameLabelBlink(s16 arg0, s16 arg1, s32 arg2, s32 arg3, u16 arg4, s32 arg5);

void BattleHud_DrawSpeciesNameLabelAuto(ActivePokemon* arg0, TeamRoster* arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s32 arg6);

extern f32 D_FLT_82199EB0;
void func_82116480(s8* arg0, s16 arg1, s16 arg2);
void func_82117610(s16 x, s16 y);

extern f32 D_FLT_82199EB4;
void func_8211778C(s16 x, s16 y);

void BattleHud_DrawPartyBallRow(ActivePokemon* arg0, s16 arg1, s16 arg2);

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
void BattleHud_DrawMonStatusBoxPlayer(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);

void BattleHud_DrawMonStatusBoxOpponent(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);

M2C_UNK func_8001A944(s32, s32, s8*);              /* extern */
u32 func_800566BC(s8*);                            /* extern */

void func_82119994(s32 arg0, s32 arg1, s32 arg2);

s32 BattleHud_DrawMovePpTextLTR(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 BattleHud_DrawMovePpTextRTL(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

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
void func_8211AEA4(TeamRoster* arg0, BattleMon* arg1, s32 arg2, s32 arg3, s32 arg4);

/*
 * BattleDebug_DrawCameraLabel
 *
 * Calls Ui_DrawPrimColorRect(arg0, arg1, 0x6E, 0x1E, 0, 0, 0, 0x3C), then
 * func_8001AB6C() and func_8001A384(1, 0), then func_8001A944 twice: with
 * (arg0 + 3, arg1 + 4, &D_82195BE4) and with (arg0 + 0x23, arg1 + 0x10,
 * D_8218B15C[D_8219A5A4]), and finally func_8001ABBC().  D_8219A5A4 selects
 * an entry of the word-sized table D_8218B15C, which is passed on as the
 * third argument.  The calls look like a begin / draw / end sequence
 * positioned relative to (arg0, arg1), but that is an inference.
 *
 * The roles of the func_8001A... helpers are not established here.
 */
M2C_UNK Ui_DrawPrimColorRect(s32, s32, s32, s32, s32, s32, s32, s32);
extern M2C_UNK D_82195BE4;
extern s32 D_8218B15C[];
extern s32 D_8219A5A4;

void BattleDebug_DrawCameraLabel(s16 arg0, s16 arg1);

#endif
