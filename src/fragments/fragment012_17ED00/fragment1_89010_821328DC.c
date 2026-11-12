/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragment1_89010.h"

void func_821328DC(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_821324D8(arg0);

        case 1:
            func_821325E8((s32)arg0);
            break;

        case 2:
            func_82132628(arg0);
            break;

        case 3:
            func_821326E4(arg0);
            break;

        case 4:
            func_82131C64(arg0);
            break;

        case 5:
            func_82131D24(arg0);
            break;

        case 6:
            func_82131EC4(arg0);
            break;

        case 7:
            func_8213201C(arg0);
            break;

        case 8:
            BattleScene_SendOutSide0(arg0);
            break;

        case 9:
            func_821321A4(arg0);
            break;

        case 10:
            BattleScene_SendOutSide1(arg0);
            break;

        case 11:
            func_8213233C(arg0);
            break;

        case 12:
            func_821323D0((s32)arg0);
            break;
    }
}
