/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_3055E0.h"

void func_821243DC(CameraNode* arg0, ActivePokemon* arg1, f32 arg2) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = Math_StepToF(M2C_FIELD(sBattleScene.scene, f32*, 0x98), 2.8f, 0.45f, 0.45f);
    BattleAnim_ApproachF(&sBattleScene.scene->unk_74, 0.0f, M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
    D_8219A530 = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, arg1->facingDirection << 14, sBattleScene.scene->unk_74, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, arg1->facingDirection * 0x1555, D_8219A530, arg2);
    if (M2C_FIELD(arg0, f32*, 0xAC) <= 15.0f) {
        M2C_FIELD(arg0, f32*, 0xAC) = 15.0f;
    }
}


void func_82124544(CameraNode* arg0, ActivePokemon* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0));
    M2C_FIELD(sBattleScene.scene, f32*, 0x74) = BattleScene_ScaleCameraDistance(arg1, arg2, 50.0f * arg3);
    M2C_FIELD(sBattleScene.scene, f32*, 0x5C) = BattleScene_ScaleCameraDistance(arg1, arg4, 50.0f * arg5);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, M2C_FIELD(sBattleScene.scene, Vec3f*, 0xC0), 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromAt(arg0, arg6, BattleScene_GetParticipantFacingAngle(arg1), M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0f);
}

void func_82124664(s32 arg0, s32 arg1, s16 arg2) {
    f32 temp = 0.35f;

    M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = func_8000F23C(M2C_FIELD(sBattleScene.scene, f32*, 0x98), 2.5f, temp, temp);
    func_8210C1A8(&sBattleScene.scene->unk_74, sBattleScene.scene->distance, M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
    func_8212254C(arg1, arg0, sBattleScene.scene->unk_D0, 0, func_82107CC4(arg1), 0.0f, 0.0f);
    func_82122684(arg0, arg2, func_82107CC4(arg1), sBattleScene.scene->unk_74, 0.0f);
}

/**
 * Forwards both arguments to BattleScene_SetCameraPresetClose; camera shot table entry.
 * @unverified Name describes the forwarding only.
 */
void BattleScene_SetCameraPresetCloseThunk(CameraNode* arg0, ActivePokemon* arg1) {
    BattleScene_SetCameraPresetClose(arg0, arg1);
}

/**
 * Forwards both arguments to BattleScene_SetCameraFollowPresetNear; camera shot table entry.
 * @unverified Name describes the forwarding only.
 */
void BattleScene_SetCameraFollowPresetNearThunk(CameraNode* arg0, ActivePokemon* arg1) {
    BattleScene_SetCameraFollowPresetNear(arg0, arg1);
}

/**
 * Forwards both arguments to BattleScene_SetCameraPresetLowClose; camera shot table entry.
 * @unverified Name describes the forwarding only.
 */
void BattleScene_SetCameraPresetLowCloseThunk(CameraNode* arg0, ActivePokemon* arg1) {
    BattleScene_SetCameraPresetLowClose(arg0, arg1);
}

/**
 * Forwards both arguments to BattleScene_CameraShotTargetClose; camera shot table entry.
 * @unverified Name describes the forwarding only.
 */
void BattleScene_CameraShotTargetCloseThunk(CameraNode* arg0, ActivePokemon* arg1) {
    BattleScene_CameraShotTargetClose(arg0, arg1);
}

/**
 * Forwards both arguments to func_82123D4C.
 */
void func_821247D0(CameraNode* arg0, ActivePokemon* arg1) {
    func_82123D4C(arg0, arg1);
}

/**
 * Forwards both arguments to BattleScene_CameraShotTargetHigh; camera shot table entry.
 * @unverified Name describes the forwarding only.
 */
void BattleScene_CameraShotTargetHighThunk(CameraNode* arg0, ActivePokemon* arg1) {
    BattleScene_CameraShotTargetHigh(arg0, arg1);
}

/**
 * Forwards both arguments to func_82123F44.
 */
void func_82124810(CameraNode* arg0, ActivePokemon* arg1) {
    func_82123F44(arg0, arg1);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_82124830(s8 *arg0, ActivePokemon* arg1)
{
  if (arg0)
  {
  }
  func_82124054((CameraNode*)arg0, arg1);
  if ((*((f32 *) (((s8 *) arg0) + 0xB8))) <= 20.0f)
  {
    *((f32 *) (((s8 *) arg0) + 0xB8)) = 20.0f;
  }
}

void func_82124874(void) {
    MiniFx_UpdateParticles();
}

void func_82124894(CameraNode* arg0, ActivePokemon* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
}

void func_82124750();
void func_82124770();
void func_82124790();
void func_821247B0();
void func_821247D0();
void func_82124984(void* arg0, void* arg1, s32 arg2) {
    switch (arg2) {
        case 0:
            func_82124750(arg1, arg0);
            break;
        case 1:
            func_82124770(arg1, arg0);
            break;
        case 2:
            func_82124790(arg1, arg0);
            break;
        case 3:
            func_821247B0(arg1, arg0);
            break;
        case 4:
            func_821247D0(arg1, arg0);
            break;
        default:
            func_82124750(arg1, arg0);
            break;
    }
}
