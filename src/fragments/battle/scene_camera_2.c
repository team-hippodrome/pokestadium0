/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "matrix.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void func_8210C1A8(f32*, f32, f32);
void func_8212254C(s32, s32, Vec3f, s32, s32, f32, f32);
void BattleScene_FrameParticipantFront(CameraNode* arg0, ActivePokemon* arg1);

/**
 * Steps an impact framing started by BattleScene_FrameParticipantImpact: eases the zoom toward 0 (speed
 * ramping up to 2.8) and keeps the eye 5 times the Pokemon's size (at least 400) away
 * offset by arg2, at least 15 high.
 * @unverified Name guessed from the code.
 */
void BattleScene_StepImpactFraming(CameraNode* camera, ActivePokemon* active_pokemon, f32 eye_height) {
    BattleAnim_GetOwnerDefaultAnchorPosition(active_pokemon, &sBattleScene.scene->anchorPosition);
    sBattleScene.scene->easeRates.z = Math_StepToF(sBattleScene.scene->easeRampRates.z, 2.8f, 0.45f, 0.45f);
    BattleAnim_ApproachF(&sBattleScene.scene->orbitDistance, 0.0f, sBattleScene.scene->easeRates.z);
    D_8219A530 = BattleScene_ScaleCameraDistance(active_pokemon, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(active_pokemon, camera, sBattleScene.scene->anchorPosition, 0, active_pokemon->facingDirection << 14, sBattleScene.scene->orbitDistance, 0.0f);
    BattleScene_SetCameraEyeFromPosition(camera, sBattleScene.scene->anchorPosition, 0, active_pokemon->facingDirection * 0x1555, D_8219A530, eye_height);
    if (M2C_FIELD(camera, f32*, 0xAC) <= 15.0f) {
        M2C_FIELD(camera, f32*, 0xAC) = 15.0f;
    }
}


/**
 * Starts an orbit framing on the Pokemon: zoom arg2 times its size (at least 50 * arg3),
 * target distance arg4 times its size (at least 50 * arg5), eye at pitch arg6 from its
 * facing.
 * @unverified Name guessed from the code.
 */
void BattleScene_StartOrbitFraming(CameraNode* camera, ActivePokemon* active_pokemon, f32 zoom_scale, f32 zoom_min, f32 distance_scale, f32 distance_min, s16 pitch) {
    BattleAnim_GetOwnerDefaultAnchorPosition(active_pokemon, &sBattleScene.scene->anchorPosition);
    sBattleScene.scene->orbitDistance = BattleScene_ScaleCameraDistance(active_pokemon, zoom_scale, 50.0f * zoom_min);
    sBattleScene.scene->distance = BattleScene_ScaleCameraDistance(active_pokemon, distance_scale, 50.0f * distance_min);
    BattleScene_SetCameraAtFromAnchor(active_pokemon, camera, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(active_pokemon), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromAt(camera, pitch, BattleScene_GetParticipantFacingAngle(active_pokemon), sBattleScene.scene->orbitDistance, 0.0f);
}

/**
 * Steps the orbit framing of BattleScene_StartOrbitFraming: eases the zoom toward the target distance (speed
 * ramping up to 2.5) at pitch arg2.
 * @unverified Name guessed from the code.
 */
void BattleScene_StepOrbitFraming(s32 camera, s32 active_pokemon, s16 pitch) {
    f32 temp = 0.35f;

    sBattleScene.scene->easeRates.z = func_8000F23C(sBattleScene.scene->easeRampRates.z, 2.5f, temp, temp);
    func_8210C1A8(&sBattleScene.scene->orbitDistance, sBattleScene.scene->distance, sBattleScene.scene->easeRates.z);
    func_8212254C(active_pokemon, camera, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(active_pokemon), 0.0f, 0.0f);
    func_82122684(camera, pitch, BattleScene_GetParticipantFacingAngle(active_pokemon), sBattleScene.scene->orbitDistance, 0.0f);
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
 * Forwards both arguments to BattleScene_FrameParticipantFront.
 * @unverified Name guessed from the code.
 */
void BattleScene_FrameParticipantFrontThunk(CameraNode* camera, ActivePokemon* active_pokemon) {
    BattleScene_FrameParticipantFront(camera, active_pokemon);
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
 * Forwards both arguments to BattleScene_FrameParticipantFromAbove.
 * @unverified Name guessed from the code.
 */
void BattleScene_FrameParticipantFromAboveThunk(CameraNode* camera, ActivePokemon* active_pokemon) {
    BattleScene_FrameParticipantFromAbove(camera, active_pokemon);
}

/**
 * Frames the Pokemon from below (BattleScene_FrameParticipantFromBelow) and keeps the camera's 0xB8
 * value at least 20.
 * @unverified Name guessed from the code.
 */
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void BattleScene_FrameParticipantFromBelowClamped(s8 *arg0, ActivePokemon* active_pokemon)
{
  if (arg0)
  {
  }
  BattleScene_FrameParticipantFromBelow((CameraNode*)arg0, active_pokemon);
  if ((*((f32 *) (((s8 *) arg0) + 0xB8))) <= 20.0f)
  {
    *((f32 *) (((s8 *) arg0) + 0xB8)) = 20.0f;
  }
}

/**
 * Frames the Pokemon from the front (BattleScene_FrameParticipantFrontAlt).
 * @unverified Name guessed from the code.
 */
void BattleScene_FrameParticipantFrontAltThunk(CameraNode* camera, ActivePokemon* active_pokemon) {
    BattleScene_FrameParticipantFrontAlt(camera, active_pokemon);
}

/**
 * Frames the Pokemon from the front of its facing at 3.5 times its size (at least 300).
 * @unverified Name guessed from the code.
 */
void BattleScene_FrameParticipantFrontWide(CameraNode* camera, ActivePokemon* active_pokemon) {
    BattleAnim_GetOwnerDefaultAnchorPosition(active_pokemon, &sBattleScene.scene->anchorPosition);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(active_pokemon, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(active_pokemon, camera, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(active_pokemon), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(camera, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(active_pokemon), gCameraDistTarget, 0.0f);
}

void func_82124750();
void func_82124770();
void func_82124790();
void func_821247B0();
void BattleScene_FrameParticipantFrontThunk();
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
            BattleScene_FrameParticipantFrontThunk(arg1, arg0);
            break;
        default:
            func_82124750(arg1, arg0);
            break;
    }
}
