/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "battle.h"
#include "memory_main.h"
#include "math.h"
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

void BattleScene_MemoryUnusedNop(void);

extern s32 D_8219A760;
void BattleScene_SetCameraClipMaskBothSides(s32);

/**
 * Camera frame on the Pokemon of side D_8219A760: aims at its default anchor from the
 * front, at a distance scaled by its size, then advances the phase step.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name guessed from the code.
 */
void BattleScene_FinalPresentationFrameActiveOwner(CameraNode* arg0) {
    f32 sp3C;

    BattleScene_SetCameraClipMaskBothSides(0x1FFE);
    BattleScene_SetCameraClipPlanes(arg0, 20.0f, 4000.0f);
    BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[D_8219A760], &sBattleScene.scene->anchorPosition);
    sp3C = BattleScene_ScaleCameraDistance(sActivePokemon[D_8219A760], 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(sActivePokemon[D_8219A760], arg0, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(sActivePokemon[D_8219A760]),
                  0.0f, 0.0f);
    BattleScene_SetCameraEyeFromAt(arg0, 0, BattleScene_GetParticipantFacingAngle(sActivePokemon[D_8219A760]), sp3C, 0.0f);

    if (sActivePokemon[0]) {}  // karodo
    sBattleScene.scene->phaseStep += 1;
    if (D_8219A760) {}  // karodo
}

/**
 * Empty.
 * @unverified Name guessed from the code.
 */
void BattleScene_MemoryUnusedNop(void) {
}

void BattleScene_SelectNextBRollCameraShot(CameraNode* arg0);
void BattleCamera_StartNextBRollShot(CameraNode* arg0);
void BattleScene_InitTurnPresentation(s32 arg0);
void BattleScene_SetPhase(CameraNode* arg0, s32 arg1);
void BattleScene_OpeningStepInitCamera(CameraNode* arg0);
void BattleScene_IntroStepInitOverheadCamera(CameraNode* arg0);
void SceneMode7_StepInit(s32 arg0);
void SceneMode11_StepInit(CameraNode* arg0);
/**
 * Starts the battle scene: clears the winner, sets the field of view to 30 and runs the
 * opening step for the scene mode (mode 0 frames the active Pokemon, modes 1 and 5 start
 * the B-roll), then stores the camera.
 * @unverified Name guessed from the code.
 */
void BattleScene_StartPresentationForMode(CameraNode* arg0, UNUSED s32 arg1, UNUSED s32 arg2) {
    sBattleScene.scene->winner = 0;
    sBattleScene.scene->verticalFieldOfView = 30.0f;
    switch (sBattleScene.scene->mode) {
        case 0:
            BattleScene_FinalPresentationFrameActiveOwner(arg0);
            break;
        case 1:
        case 5:
            BattleScene_SelectNextBRollCameraShot(arg0);
            break;
        case 9:
            BattleCamera_StartNextBRollShot(arg0);
            break;
        case 2:
        case 6:
        case 10:
            BattleScene_InitTurnPresentation((s32)arg0);
            BattleScene_SetPhase(arg0, 1);
            break;
        case 3:
            BattleScene_InitTurnPresentation((s32)arg0);
            BattleScene_SetPhase(arg0, 5);
            break;
        case 8:
            BattleScene_OpeningStepInitCamera(arg0);
            break;
        case 4:
            BattleScene_IntroStepInitOverheadCamera(arg0);
            break;
        case 7:
            SceneMode7_StepInit((s32)arg0);
            break;
        case 11:
            SceneMode11_StepInit(arg0);
            break;
    }
    sBattleScene.scene->camera = arg0;
}

/**
 * Allocates the battle scene from the main pool and zeroes it.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleScene_AllocateMemory(void) {
    sBattleScene.scene = MainPool_Alloc(sizeof(BattleScene), 0);
    bzero(sBattleScene.scene, sizeof(BattleScene));
}
