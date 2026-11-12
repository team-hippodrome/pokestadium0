#ifndef ZERO_FRAGMENT1_89010_H
#define ZERO_FRAGMENT1_89010_H

/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/1/fragment1_89010.c, src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "global.h"

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math.h"
#include "math_util.h"
extern u8* sBattleAnimAssetPointers[256];
extern s16 sBattleAnimResourceList[0x10];
extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];
extern s16 D_8219CAC0;
extern s16 D_8219CAC2;
extern Mtx D_8219CAC8;
extern s16 D_8219CB08;
extern s16 D_8219CB0A;
extern s16 D_8219CB0C;
extern s16 D_8219CB0E;
extern s16 D_8219CB10;
extern s16 D_8219CB12;
extern s16 D_8219CB14;
extern s16 D_8219CB16;
extern s16 D_8219CB18;
extern s16 D_8219CB1A;
extern const char D_821978C8[];

#include "m2c_macros.h"

void BattleScene_OpeningStepNop(UNUSED s32 arg0);
void BattleAnim_NoopUpdateHook(void);

void func_82131880(CameraNode* arg0);
void func_821319FC(CameraNode* arg0);
void func_82131A3C(CameraNode* arg0);
void BattleScene_OpeningStepThrowSide1(CameraNode* arg0);
void BattleScene_OpeningStepLandSide0Ball(CameraNode* arg0);
void func_82131EC4(CameraNode* arg0);
void BattleScene_OpeningStepWaitSide0Ball(CameraNode* arg0);
void BattleScene_SendOutSide0(CameraNode* arg0);
void BattleScene_OpeningStepWaitSide0SendOut(CameraNode* arg0);
void BattleScene_SendOutSide1(CameraNode* arg0);
void BattleScene_OpeningStepWaitSide1SendOut(CameraNode* arg0);

void BattleScene_UpdateIntroSequence(CameraNode* arg0);

s32 func_82101FD4(s32);                             /* extern */
extern s32 D_82199DE0;
extern s8 *D_8219A5A0;

void BattleScene_OpeningStepWaitForAssets(s32 arg0);

void BattleScene_OpeningStepInitCamera(CameraNode* arg0);
void BattleScene_OpeningStepOrbitCamera(CameraNode* arg0);
void BattleScene_OpeningStepLowerCameraAndThrowSide0(CameraNode* arg0);

void BattleScene_RunOpeningSendOut(CameraNode* arg0);

#endif
