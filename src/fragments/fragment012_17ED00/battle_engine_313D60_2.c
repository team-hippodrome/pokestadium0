/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_313D60.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "geo_node.h"
#include "model_animation.h"
#include "text_system.h"
#include "audio_commands.h"
#include "matrix.h"
#include "memory.h"
#include "util.h"
extern unk_D_84390240 sBattleScene;
extern s32 pad_D_84390280;
extern s32 pad_D_84390290[4];

void BattleScene_UpdateCameraDefaultModeNoop(UNUSED CameraNode* arg0);
void BattleScene_UpdateCameraOwner0FramingModeNoop(UNUSED CameraNode* arg0);
void BattleScene_AvoidDegenerateCameraLookAt(CameraNode* arg0);
void BattleScene_TickCameraSubstate(CameraNode* arg0);
s32 BattleScene_Dispatch(s32 arg0, CameraNode* arg1);

void BattleScene_RunFinalPresentation(CameraNode* arg0, UNUSED ActivePokemon* arg1, UNUSED ActivePokemon* arg2);
void BattleScene_AllocateMemory(void);
void BattleScene_TickCameraSubstateDefault(CameraNode* arg0);
void BattleScene_TickCameraSubstateStripWipe(CameraNode* arg0);
void BattleScene_Update(CameraNode* arg0);

void BattleScene_UpdateCameraDefaultModeNoop(UNUSED CameraNode* arg0) {
}

void BattleScene_UpdateCameraOwner0FramingModeNoop(UNUSED CameraNode* arg0) {
}

void BattleScene_AvoidDegenerateCameraLookAt(CameraNode* arg0) {
    if (BattleAnim_Distance2D(arg0->view.targetPosition.x, arg0->view.targetPosition.z, arg0->view.eyePosition.x, arg0->view.eyePosition.z) < 0.0001f) {
        arg0->view.targetPosition.z += 0.001f;
    }
}

void func_82105E6C(void);
void func_82124A40(void);
void func_82106374(ActivePokemon*);
void func_821054A8(ActivePokemon*);

void BattleScene_TickCameraSubstateDefault(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_30) {
        case 0:
            sBattleScene.scene->unk_18 = 0;
            break;

        case 1:
            if (sBattleScene.scene->unk_44 == 2) {
                BattleThumbnail_ClearBothOwnerIdleFlags();
            }
            sBattleScene.scene->unk_30++;
            break;

        case 2:
            if (sActivePokemon[0]->thumbnail.camera->viewport.x == -0x48) {
                sBattleScene.scene->unk_30++;
            }
            break;

        case 3:
            GeoCamera_SetBackgroundTexture(arg0, 0x12C, 0xA, 2, Util_ConvertAddrToVirtAddr((u32)D_1000000));
            GeoCamera_SetBackground(arg0, 5, 0xA, 0, 0, 0);
            sBattleScene.scene->unk_18 = 0;
            sBattleScene.scene->unk_30 += 1;

        case 4:
            if (arg0->overlay.stepIndex == 0xA) {
                func_82105E6C();
                func_82106374(sActivePokemon[0]);
                func_82106374(sActivePokemon[1]);
                sBattleScene.scene->unk_30 += 1;
                sBattleScene.scene->unk_18 = 1;
            }
            break;

        case 5:
            if (BattleScene_AdvanceBothOwnerAnimations() == 0) {
                if ((sBattleScene.scene->unk_44 == 1) || (sBattleScene.scene->unk_44 == 5) || (sBattleScene.scene->unk_44 == 9)) {
                    BattleAnim_CleanupEffects(2);
                }
                func_821054A8(sActivePokemon[0]);
                func_821054A8(sActivePokemon[1]);
                sBattleScene.scene->unk_18 = 2;
                GeoCamera_SetBackgroundTexture(arg0, 0xA, 0x12C, 2, Util_ConvertAddrToVirtAddr((u32)D_1000000));
                GeoCamera_SetBackground(arg0, 4, 0xA, 0, 0, 0);
                arg0->perspective.verticalFieldOfView = 30.0f;
                sBattleScene.scene->unk_60 = 30.0f;
                sBattleScene.scene->unk_30 += 1;
            }
            break;

        case 6:
            func_82124A40();
            arg0->perspective.verticalFieldOfView = 30.0f;
            sBattleScene.scene->unk_60 = 30.0f;
            sBattleScene.scene->unk_18 = 0;
            if (arg0->overlay.stepIndex == 0xA) {
                sBattleScene.scene->unk_30 = 0;
                if (sBattleScene.scene->unk_44 == 1) {
                    BattleThumbnail_SetBothOwnerIdleFlags();
                }
            }
            break;
    }
}

void BattleScene_TickCameraSubstateStripWipe(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_30) {
        case 0:
            sBattleScene.scene->unk_18 = 0;
            break;

        case 1:
            if (sBattleScene.scene->unk_44 == 2) {
                BattleThumbnail_ClearBothOwnerIdleFlags();
            }
            sBattleScene.scene->unk_30++;
            break;

        case 2:
            if (sActivePokemon[0]->thumbnail.camera->viewport.x == -0x48) {
                sBattleScene.scene->unk_30++;
            }
            break;

        case 3:
            BattleScene_SetStripWipeState(3, 0x1E);
            BattleScene_UpdateStripWipe();
            sBattleScene.scene->unk_18 = 0;
            sBattleScene.scene->unk_30 += 1;

        case 4:
            BattleScene_UpdateStripWipe();
            if (BattleScene_GetStripWipeState() == 1) {
                func_82105E6C();
                BattleScene_CleanupParticipantEffectMode(sActivePokemon[0]);
                BattleScene_CleanupParticipantEffectMode(sActivePokemon[1]);
                sBattleScene.scene->unk_30 += 1;
                sBattleScene.scene->unk_18 = 1;
            }
            break;

        case 5:
            sBattleScene.scene->unk_18 = 1;
            sBattleScene.scene->unk_30 += 1;
            break;

        case 6:
            sBattleScene.scene->unk_18 = 1;
            sBattleScene.scene->unk_30 += 1;
            break;

        case 7:
            sBattleScene.scene->unk_18 = 1;
            sBattleScene.scene->unk_30 += 1;
            break;

        case 8:
            if (BattleScene_AdvanceBothOwnerAnimations() == 0) {
                if ((sBattleScene.scene->unk_44 == 1) || (sBattleScene.scene->unk_44 == 5) || (sBattleScene.scene->unk_44 == 9)) {
                    BattleAnim_CleanupEffects(2);
                }
                func_821054A8(sActivePokemon[0]);
                func_821054A8(sActivePokemon[1]);
                sBattleScene.scene->unk_18 = 2;
                BattleScene_SetStripWipeState(2, 0x1E);
                BattleScene_UpdateStripWipe();
                arg0->perspective.verticalFieldOfView = 30.0f;
                sBattleScene.scene->unk_60 = 30.0f;
                sBattleScene.scene->unk_30 += 1;
            }
            break;

        case 9:
            func_82124A40();
            arg0->perspective.verticalFieldOfView = 30.0f;
            sBattleScene.scene->unk_60 = 30.0f;
            sBattleScene.scene->unk_18 = 0;
            BattleScene_UpdateStripWipe();
            if (BattleScene_GetStripWipeState() == 0) {
                sBattleScene.scene->unk_30 = 0;
                if (sBattleScene.scene->unk_44 == 1) {
                    BattleThumbnail_SetBothOwnerIdleFlags();
                }
            }
            break;
    }
}

void BattleScene_TickCameraSubstate(CameraNode* arg0) {
    if (sBattleScene.scene->unk_2E == 0) {
        BattleScene_TickCameraSubstateDefault(arg0);
    } else {
        BattleScene_TickCameraSubstateStripWipe(arg0);
    }
}

void func_82121DAC(void);
void func_821328DC(CameraNode*);
void Rental_TeamSlotsUpdate(CameraNode*);
void func_82132D60(CameraNode*);
void func_821336EC(CameraNode*);
void func_82121C3C(CameraNode*);
void func_82133B6C(void);
void func_821065B4(ActivePokemon*);
void func_82122458(CameraNode*);
void func_82122374(CameraNode*);
extern ActivePokemon* sSide1ActivePokemon;
extern ActivePokemon* sSide2ActivePokemon;
void BattleScene_Update(CameraNode* arg0) {
    BattleScene_TickCameraSubstate(arg0);
    func_82121DAC();

    switch (sBattleScene.scene->unk_1C) {
        case 0:
            BattleScene_UpdateCameraDefaultModeNoop(arg0);
            break;
        case 1:
            BattleScene_UpdateBRollCameraSequence(arg0);
            break;
        case 2:
            BattleScene_UpdatePhase(arg0);
            break;
        case 3:
            BattleScene_UpdateCameraOwner0FramingModeNoop(arg0);
            break;
        case 4:
            BattleScene_UpdateIntroSequence(arg0);
            break;
        case 8:
            func_821328DC(arg0);
            break;
        case 5:
            BattleScene_UpdateBRollCameraSequence(arg0);
            break;
        case 6:
            BattleScene_UpdatePhase(arg0);
            break;
        case 9:
            Rental_TeamSlotsUpdate(arg0);
            break;
        case 10:
            BattleScene_UpdatePhase(arg0);
            break;
        case 7:
            func_82132D60(arg0);
            break;
        case 11:
            func_821336EC(arg0);
            break;
    }

    if ((sBattleScene.scene->unk_1C != 4) && (sBattleScene.scene->unk_1C != 8)) {
        func_82121C3C(arg0);
    }
    if ((sBattleScene.scene->unk_1C == 9) || (sBattleScene.scene->unk_1C == 10)) {
        func_82133B6C();
    }
    BattleScene_TickStateCallbacks();
    func_821065B4(sSide1ActivePokemon);
    func_821065B4(sSide2ActivePokemon);
    func_82122458(arg0);
    BattleScene_ApplyCameraShake(arg0);
    func_82122374(arg0);
    BattleScene_CameraHelperNop(arg0);
    BattleScene_AvoidDegenerateCameraLookAt(arg0);
}

s32 BattleScene_Dispatch(s32 arg0, CameraNode* arg1) {
    switch (arg0) {
        case 0:
            BattleScene_AllocateMemory();
            break;

        case 1:
        case 2:
            BattleScene_Update(arg1);
            break;

        case 3:
            BattleScene_RunFinalPresentation(arg1, sActivePokemon[0], sActivePokemon[1]);
            break;
    }
    return sBattleScene.scene->unk_40;
}
