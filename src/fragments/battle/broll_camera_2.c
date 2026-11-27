/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "m2c_macros.h"
void BattleScene_BRollStepNop(void);
void BattleScene_BRollCameraUpdateRotatingArenaOverview(CameraNode* arg0);
void BattleScene_SelectNextBRollCameraShot(CameraNode* arg0);
extern f32 D_FLT_8218935C[][4];
extern Vec3f D_8218B630;
extern Vec3f D_8218B63C;
void func_821224F4(CameraNode*);
void func_82121D78(CameraNode*, f32, f32);
void func_8212187C(s32);
void BattleCamera_StartSpeciesPath(CameraNode*, ActivePokemon*);
s32 BattleScene_SkipUnavailableBRollShot(ActivePokemon*, CameraNode*);
void BattleScene_EnterStateRow(ActivePokemon*, s32);
f32 BattleScene_GetParticipantHeight(ActivePokemon*);
void BattleCamera_CaptureModelOrbit(ActivePokemon*, CameraNode*);
extern f32 D_FLT_82196040;
void BattleCamera_CaptureModelOrbit(ActivePokemon*, CameraNode*);
void BattleScene_BRollShotFrontClose(CameraNode*);
extern const f64 D_DBL_821960A0;
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void BattleScene_EaseCameraTargetFromSavedEye(CameraNode*, ActivePokemon*);
s32 BattleScene_AdvanceCameraFrameCounter(M2C_UNK);
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
s32 BattleCamera_StepPath(CameraNode*, ActivePokemon*);
s32 BattleScene_AdvanceCameraFrameCounter(M2C_UNK);
void func_82122628(s32, Vec3f, s32, s32, f32, f32);
extern f32 D_FLT_821960A8;
f32 BattleScene_ScaleCameraDistance(ActivePokemon*, f32, f32);
void BattleScene_EaseCameraTargetToParticipant(CameraNode*, ActivePokemon*);
s32 BattleCamera_StepPath(CameraNode*, ActivePokemon*);
void BattleScene_ResetCameraFrameCounter(void);
extern u8* D_800603C0;
void Audio_FadeCategoriesAndStreams(s32 arg0);

void Battle_ChooseActionsForMode(void);
void BattleMenu_ResetCommandTimer(void);

/**
 * Per-frame update while unk_1C is 1 (b-roll camera mode): runs the action selection phase and
 * dispatches to the update function of the current b-roll shot (odd cameraCounter values).
 */
void BattleScene_UpdateBRollCameraSequence(CameraNode* arg0) {
    if (sBattleScene.scene->mode == 1) {
        if ((sBattleScene.scene->transitionStep == 0) && (sActivePokemon[0]->thumbnail.camera->viewport.x == 0x17) &&
            (sActivePokemon[1]->thumbnail.camera->viewport.x == 0x103)) {
            Battle_ChooseActionsForMode();
        } else {
            BattleMenu_ResetCommandTimer();
        }
    }
    if (sBattleScene.scene->mode == 5) {
        Battle_ChooseActionsForMode();
    }
    switch (sBattleScene.scene->phaseStep) {
        case 1:
            BattleScene_BRollCameraUpdateArenaOrbit(arg0);
            break;
        case 3:
            BattleScene_BRollCameraUpdateRotatingArenaOverview(arg0);
            break;
        case 5:
            BattleScene_BRollTiltUpToHead(arg0);
            break;
        case 7:
            BattleScene_BRollHoldFollow60Frames(arg0);
            break;
        case 9:
            BattleScene_BRollHoldFollow60Frames(arg0);
            break;
        case 11:
            BattleScene_BRollTiltUpHigh(arg0);
            break;
        case 13:
            BattleScene_BRollHoldOrbit(arg0);
            break;
        case 15:
            BattleScene_BRollHoldOrbit(arg0);
            break;
        case 17:
            BattleScene_BRollRaiseRotationXRestoreFov(arg0);
            break;
        case 19:
            BattleScene_BRollRaiseRotationXRestoreFov(arg0);
            break;
        case 21:
            BattleScene_BRollDollyIn(arg0);
            break;
        case 23:
            BattleScene_BRollCameraUpdatePresetHold(arg0);
            break;
        case 50:
            BattleScene_SelectNextBRollCameraShot(arg0);
            break;
    }
}
