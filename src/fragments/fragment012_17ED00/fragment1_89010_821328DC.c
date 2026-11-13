/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragment1_89010.h"

/**
 * Battle opening phase: steps through the intro camera shots and both send-outs.
 * Seen in play (2026-11-13) in a COM Free Battle (scene mode 8) it ran every frame of the opening,
 * dispatching BattleScene_OpeningStepInitCamera, then WaitForAssets, OrbitCamera,
 * LowerCameraAndThrowSide0 and ThrowSide1 in order.
 */
void BattleScene_RunOpeningSendOut(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_OpeningStepInitCamera(arg0);

        case 1:
            BattleScene_OpeningStepWaitForAssets((s32)arg0);
            break;

        case 2:
            BattleScene_OpeningStepOrbitCamera(arg0);
            break;

        case 3:
            BattleScene_OpeningStepLowerCameraAndThrowSide0(arg0);
            break;

        case 4:
            BattleScene_OpeningStepThrowSide1(arg0);
            break;

        case 5:
            BattleScene_OpeningStepLandSide0Ball(arg0);
            break;

        case 6:
            func_82131EC4(arg0);
            break;

        case 7:
            BattleScene_OpeningStepWaitSide0Ball(arg0);
            break;

        case 8:
            BattleScene_SendOutSide0(arg0);
            break;

        case 9:
            BattleScene_OpeningStepWaitSide0SendOut(arg0);
            break;

        case 10:
            BattleScene_SendOutSide1(arg0);
            break;

        case 11:
            BattleScene_OpeningStepWaitSide1SendOut(arg0);
            break;

        case 12:
            BattleScene_OpeningStepNop((s32)arg0);
            break;
    }
}
