/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "matrix.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void func_8210C1A8(f32*, f32, f32);
void func_8212254C(s32, s32, Vec3f, s32, s32, f32, f32);
void func_82123D4C(CameraNode* arg0, ActivePokemon* arg1);

/**
 * Steps an impact framing started by func_82124284: eases the zoom toward 0 (speed
 * ramping up to 2.8) and keeps the eye 5 times the Pokemon's size (at least 400) away
 * offset by arg2, at least 15 high.
 */
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


/**
 * Starts an orbit framing on the Pokemon: zoom arg2 times its size (at least 50 * arg3),
 * target distance arg4 times its size (at least 50 * arg5), eye at pitch arg6 from its
 * facing.
 */
void func_82124544(CameraNode* arg0, ActivePokemon* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sBattleScene.scene->unk_D0);
    sBattleScene.scene->unk_74 = BattleScene_ScaleCameraDistance(arg1, arg2, 50.0f * arg3);
    sBattleScene.scene->distance = BattleScene_ScaleCameraDistance(arg1, arg4, 50.0f * arg5);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromAt(arg0, arg6, BattleScene_GetParticipantFacingAngle(arg1), sBattleScene.scene->unk_74, 0.0f);
}

/**
 * Steps the orbit framing of func_82124544: eases the zoom toward the target distance (speed
 * ramping up to 2.5) at pitch arg2.
 */
void func_82124664(s32 arg0, s32 arg1, s16 arg2) {
    f32 temp = 0.35f;

    M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = func_8000F23C(M2C_FIELD(sBattleScene.scene, f32*, 0x98), 2.5f, temp, temp);
    func_8210C1A8(&sBattleScene.scene->unk_74, sBattleScene.scene->distance, M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
    func_8212254C(arg1, arg0, sBattleScene.scene->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    func_82122684(arg0, arg2, BattleScene_GetParticipantFacingAngle(arg1), sBattleScene.scene->unk_74, 0.0f);
}

/**
 * Forwards both arguments to BattleScene_SetCameraPresetClose; camera shot table entry.
 * Seen in play (2026-11-13) ran for the same 44 moves as BattleScene_SetCameraPresetClose
 * (DoubleSlap showed the close side shot).
 */
void BattleScene_SetCameraPresetCloseThunk(CameraNode* arg0, ActivePokemon* arg1) {
    BattleScene_SetCameraPresetClose(arg0, arg1);
}

/**
 * Forwards both arguments to BattleScene_SetCameraPresetHighClose; camera shot table entry.
 * Seen in play (2026-11-13) ran for the same 36 moves as BattleScene_SetCameraPresetHighClose
 * (Karate Chop showed the high close-up). Was BattleScene_SetCameraFollowPresetNearThunk.
 */
void BattleScene_SetCameraPresetHighCloseThunk(CameraNode* arg0, ActivePokemon* arg1) {
    BattleScene_SetCameraPresetHighClose(arg0, arg1);
}

/**
 * Forwards both arguments to BattleScene_SetCameraPresetLowClose; camera shot table entry.
 * Seen in play (2026-11-13) ran for the same 31 moves as BattleScene_SetCameraPresetLowClose
 * (Swords Dance showed the low close-up).
 */
void BattleScene_SetCameraPresetLowCloseThunk(CameraNode* arg0, ActivePokemon* arg1) {
    BattleScene_SetCameraPresetLowClose(arg0, arg1);
}

/**
 * Forwards both arguments to BattleScene_CameraShotTargetClose; camera shot table entry.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
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
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
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

/**
 * Updates the mini effect particles.
 */
void func_82124874(void) {
    MiniFx_UpdateParticles();
}

/**
 * Frames the Pokemon from the front of its facing at 3.5 times its size (at least 300).
 */
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
/**
 * Runs camera shot `arg2` (0-4, default 0) for Pokemon `arg0` on camera `arg1`.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening, a switch
 * in battle and a Pound turn.
 * @unverified Name and comment guessed from the code.
 */
void BattleCamera_PlayShot(void* arg0, void* arg1, s32 arg2) {
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
