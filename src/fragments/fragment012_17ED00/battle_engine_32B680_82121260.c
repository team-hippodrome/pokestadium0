/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "matrix.h"
#include "math_util.h"
#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "matrix.h"
#include "m2c_macros.h"
void func_8211F580(void);
void BattleScene_IntroCameraRollStepNoFov(CameraNode* arg0);
void BattleScene_SelectNextIntroCameraShot(CameraNode* arg0);
extern f32 D_FLT_8218935C[][4];
extern Vec3f D_8218B630;
extern Vec3f D_8218B63C;
void func_821224F4(CameraNode*);
void func_82121D78(CameraNode*, f32, f32);
void func_8212187C(s32);
void func_821351F8(CameraNode*, ActivePokemon*);
s32 func_8211F644(ActivePokemon*, CameraNode*);
void func_82104C68(ActivePokemon*, s32);
f32 BattleScene_GetParticipantHeight(ActivePokemon*);
void func_8212239C(ActivePokemon*, CameraNode*);
extern f32 D_FLT_82196040;
void func_8212239C(ActivePokemon*, CameraNode*);
void func_8212054C(CameraNode*);
extern const f64 D_DBL_821960A0;
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextIntroCameraShot(CameraNode*);
void BattleScene_SelectNextIntroCameraShot(CameraNode*);
void func_82122FD8(CameraNode*, ActivePokemon*);
s32 func_821217DC(M2C_UNK);
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextIntroCameraShot(CameraNode*);
void BattleScene_SelectNextIntroCameraShot(CameraNode*);
s32 func_82135734(CameraNode*, ActivePokemon*);
s32 func_821217DC(M2C_UNK);
void func_82122628(s32, Vec3f, s32, s32, f32, f32);
extern f32 D_FLT_821960A8;
f32 func_82121750(ActivePokemon*, f32, f32);
void func_82122A7C(CameraNode*, ActivePokemon*);
s32 func_82135734(CameraNode*, ActivePokemon*);
void func_8212188C(void);
extern s8 *D_8219A5A0;
extern u8* D_800603C0;
void Audio_FadeCategoriesAndStreams(s32 arg0);

void Battle_ChooseActionsForMode(void);
void BattleMenu_ResetTimeout(void);

/**
 * Per-frame update while unk_1C is 1 (b-roll camera mode): runs the action selection phase and
 * dispatches to the update function of the current b-roll shot (odd cameraCounter values).
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleScene_UpdateBRollCameraSequence(CameraNode* arg0) {
    if (sBattleScene.scene->mode == 1) {
        if ((sBattleScene.scene->transitionStep == 0) && (sActivePokemon[0]->thumbnail.camera->viewport.x == 0x17) &&
            (sActivePokemon[1]->thumbnail.camera->viewport.x == 0x103)) {
            Battle_ChooseActionsForMode();
        } else {
            BattleMenu_ResetTimeout();
        }
    }
    if (sBattleScene.scene->mode == 5) {
        Battle_ChooseActionsForMode();
    }
    switch (sBattleScene.scene->phaseStep) {
        case 1:
            func_82120A34(arg0);
            break;
        case 3:
            func_82120A90(arg0);
            break;
        case 5:
            func_82120AC8(arg0);
            break;
        case 7:
            func_82120BB8(arg0);
            break;
        case 9:
            func_82120BB8(arg0);
            break;
        case 11:
            func_82120C44(arg0);
            break;
        case 13:
            func_82120D94(arg0);
            break;
        case 15:
            func_82120D94(arg0);
            break;
        case 17:
            func_82120E70(arg0);
            break;
        case 19:
            func_82120E70(arg0);
            break;
        case 21:
            func_82120FB0(arg0);
            break;
        case 23:
            BattleScene_IntroCameraPresetHoldStep(arg0);
            break;
        case 50:
            BattleScene_SelectNextIntroCameraShot(arg0);
            break;
    }
}
