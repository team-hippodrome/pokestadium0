/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "m2c_macros.h"

extern f32 D_FLT_8218935C[][4];
extern Vec3f D_8218B630;
extern Vec3f D_8218B63C;
void func_821224F4(CameraNode*);
void func_82121D78(CameraNode*, f32, f32);
void func_8212187C(s32);
void BattleCamera_CaptureModelOrbit(ActivePokemon*, CameraNode*);
extern f32 D_FLT_82196040;
void BattleCamera_CaptureModelOrbit(ActivePokemon*, CameraNode*);
void BattleScene_BRollShotFrontClose(CameraNode*);
extern const f64 D_DBL_821960A0;
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void BattleScene_EaseCameraTargetFromSavedEye(CameraNode*, ActivePokemon*);
s32 func_821217DC(M2C_UNK);
extern f32 D_FLT_82189358[][4];
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
void BattleScene_SelectNextBRollCameraShot(CameraNode*);
s32 func_821217DC(M2C_UNK);
void func_82122628(s32, Vec3f, s32, s32, f32, f32);
extern f32 D_FLT_821960A8;
void BattleScene_EaseCameraTargetToParticipant(CameraNode*, ActivePokemon*);
void func_8212188C(void);
extern u8* D_800603C0;

void func_82120A34(CameraNode*);
void func_82120A90(CameraNode*);
void BattleCamera_StartNextBRollShot(CameraNode*);
/**
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Rental_TeamSlotsUpdate(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 1:
            func_82120A34(arg0);
            break;
        case 3:
            func_82120A90(arg0);
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
        case 25:
            BattleScene_BRollStepOrbitUntilEnd(arg0);
            break;
        case 27:
            BattleScene_BRollWait440Frames((s32)arg0);
            break;
        case 29:
            BattleScene_BRollWaitForButtonToExit(arg0);
            break;
        case 50:
            BattleCamera_StartNextBRollShot(arg0);
            break;
    }
}
