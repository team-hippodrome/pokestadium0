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

extern u8 D_8219A4F4;
extern u8* D_8218B2B8[];
void BattleScene_InitializeBattlePresentation(CameraNode*);
void BattleScene_UpdateParticipantsInView(CameraNode*);
void Battle_ResetModelToIdleAnim(ActivePokemon*);

/**
 * Selects the next B-roll camera shot from the shot list for D_8219A4F4 (wrapping at 0xFF)
 * and starts it; list 5 jumps straight to phase step 24.
 * @unverified Name guessed from the code.
 */
void BattleCamera_StartNextBRollShot(CameraNode* camera) {
    if (D_8219A4F4 == 5) {
        sBattleScene.scene->phaseStep = 24;
        BattleScene_InitializeBattlePresentation(camera);
        return;
    }
    if (D_8218B2B8[D_8219A4F4][sBattleScene.scene->bRollShotIndex] == 0xFF) {
        sBattleScene.scene->bRollShotIndex = 0;
    }
    sBattleScene.scene->phaseStep = D_8218B2B8[D_8219A4F4][sBattleScene.scene->bRollShotIndex];
    sBattleScene.scene->bRollShotIndex++;
    Battle_ResetModelToIdleAnim(sActivePokemon[0]);
    Battle_ResetModelToIdleAnim(sActivePokemon[1]);
    BattleScene_ResetCameraFrameCounter();
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_BRollCameraSetupArenaOrbit(camera);
            break;
        case 2:
            BattleScene_BRollCameraSetupRotatingArenaOverview(camera);
            break;
        case 4:
            BattleScene_BRollShotFrontHigh(camera);
            break;
        case 6:
            BattleScene_BRollShotRandomPokemon0(camera);
            break;
        case 8:
            BattleScene_BRollShotRandomPokemon1(camera);
            break;
        case 10:
            BattleScene_BRollShotFrontLow(camera);
            break;
        case 12:
            BattleScene_BRollShotAimPokemon0(camera);
            break;
        case 14:
            BattleScene_BRollShotAimPokemon1(camera);
            break;
        case 16:
            BattleScene_BRollShotWideFovRotatedX(camera);
            break;
        case 18:
            BattleScene_BRollShotWideFovRotatedX(camera);
            break;
        case 20:
            BattleScene_BRollShotFrontWide(camera);
            break;
        case 22:
            BattleScene_BRollShotFrontClose(camera);
            break;
    }
    BattleScene_UpdateParticipantsInView(camera);
}
