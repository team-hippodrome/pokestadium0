/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_309ED0.h"

void func_8212A328(CameraNode* arg0, s32 arg1) {
    UNUSED s32 pad;
    BattleMonRuntime* runtime = &((ActivePokemon*)D_8219A540)->state.runtime;

    if (BattleScene_AdvanceOwnerAnimation98((ActivePokemon*)D_8219A540) != 0) {
        return;
    }
    func_82106144(D_8219A544);
    if (6 == D_80073D90[runtime->usedMove - 1].unk_04) {
        arg1 = D_8219A568;
    }
    if ((arg1 != 5) && (arg1 != 6) && (arg1 != 7)) {
        D_8219A568 = arg1;
    }
    if (func_82125E5C() != 0) {
        return;
    }
    func_821255EC(arg0);
    switch (arg1) {
        case 0:
            BattleScene_ActionSetupAnimationVariantB(arg0);
            break;
        case 1:
            func_82129D10(arg0);
            break;
        case 2:
            func_82129E30((s32)arg0);
            break;
        case 3:
            func_82129F5C(arg0);
            break;
        case 4:
            func_8212A074((s32)arg0);
            break;
        case 5:
            func_8212A190(arg0);
            break;
        case 7:
            func_8212A250(arg0);
            break;
        default:
            BattleScene_ActionSetupAnimationVariantB(arg0);
            break;
    }
}


void func_8212A4A4(s8 *arg0) {
    D_8219A578 = 0;
    if (M2C_FIELD(arg0, s8 *, 1) != 0) {
        D_8219A578 = 1;
    }
}

void func_8212A4CC(s32 arg0, s32 *arg1, s32 *arg2) {
    if ((*arg1 == 1) && (*arg2 == 1) && (func_82121820(0x1E) != 0)) {
        func_82108C0C(D_8219A544);
        M2C_FIELD(D_8219A5A0, s8 *, 0x1A) = 0;
        func_8212188C();
        func_8212189C();
        func_8211EE8C();
        func_82125570();
        func_82124A40();
        func_82125AC8(arg0);
    }
}

void func_8212A554(s32 arg0) {
    s32 temp_v0;

    if (arg0 == 4) {
        temp_v0 = func_8210C020(3);
        D_8219A568 = temp_v0;
        if (temp_v0 >= 4) {
            D_8219A568 = 0;
        }
    } else if (arg0 != 5) {
        D_8219A568 = arg0;
    }
}

void func_8212A5AC(ActivePokemon* arg0, CameraNode* arg1) {
    if (sBattleScene.scene->unk_3C == 0) {
        D_8219A568 = BattleAnim_RandomRange(3);
        if (D_8219A568 >= 3) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
        case 0:
            func_821247F0(arg1, arg0);
            break;
        case 1:
            func_82124810(arg1, arg0);
            break;
        case 2:
            func_82124830(arg1, arg0);
            break;
        default:
            func_82124874(arg1, arg0);
            break;
    }
}

void func_8212A67C(ActivePokemon* arg0, CameraNode* arg1) {
    if (sBattleScene.scene->unk_3C == 0) {
        D_8219A568 = BattleAnim_RandomRange(4);
        if (D_8219A568 >= 4) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
        case 0:
            func_821247F0(arg1, arg0);
            break;
        case 1:
            func_82124810(arg1, arg0);
            break;
        case 2:
            func_82124830(arg1, arg0);
            break;
        case 3:
            func_82124874(arg1, arg0);
            break;
        default:
            func_82124874(arg1, arg0);
            break;
    }
}

void func_8212A768(ActivePokemon* arg0, CameraNode* arg1, s32 arg2) {
    if (arg2 == 4) {
        func_8212A5AC(arg0, arg1);
    } else if (arg2 == 6) {
        func_8212A67C(arg0, arg1);
    } else {
        if (arg2 == 5) {
            arg2 = D_8219A568;
        }
        switch (arg2) {
            case 0:
                func_821247F0(arg1, arg0);
                break;
            case 1:
                func_82124810(arg1, arg0);
                break;
            case 2:
                func_82124830(arg1, arg0);
                break;
            case 3:
                func_82124874(arg1, arg0);
                break;
            default:
                func_82124874(arg1, arg0);
                break;
        }
    }
}


void func_8212A850(CameraNode* arg0, s32 arg1) {
    BattleMonRuntime* sp1C = &((ActivePokemon*)D_8219A540)->state.runtime;

    switch (sBattleScene.scene->unk_3C) {
        case 0:
            func_8212A554(arg1);
            func_82124A40();
            BattleScene_ResetCameraFrameCounter();
            func_82125580();
            BattleScene_SetDamageShakeAmplitude((ActivePokemon*)D_8219A540);
            func_8212A4A4((s8*)(D_8219A520 + 0x208));
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 4);
            func_8212A768((ActivePokemon*)D_8219A540, arg0, arg1);
            func_8212239C((ActivePokemon*)D_8219A540, arg0);
            func_82110B44((ActivePokemon*)D_8219A540);
            func_82135098((ActivePokemon*)D_8219A540);
            func_821061A8((ActivePokemon*)D_8219A540);
            break;

        case 1:
            func_82124E80();
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            func_82122DFC(arg0, (ActivePokemon*)D_8219A540);
            if (D_8219A578 == 0) {
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->unk_3C++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 2:
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            if (sp1C->unk_0C != 0) {
                if (BattleScene_IsRowAnimWaitComplete((ActivePokemon*)D_8219A540, 0xF) != 0) {
                    sBattleScene.scene->unk_3C++;
                }
                if (func_82122DFC(arg0, (ActivePokemon*)D_8219A540) != 0) {
                    sBattleScene.scene->unk_3C = 4;
                }
            } else if ((func_82122DFC(arg0, (ActivePokemon*)D_8219A540) != 0) && (func_82121820(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->unk_3C = 5;
            }
            break;

        case 3:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            if (func_82122DFC(arg0, (ActivePokemon*)D_8219A540) != 0) {
                sBattleScene.scene->unk_3C = 5;
            }
            break;

        case 4:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            func_82122DFC(arg0, (ActivePokemon*)D_8219A540);
            if (BattleScene_IsRowAnimWaitComplete((ActivePokemon*)D_8219A540, 0xF) != 0) {
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 5:
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            if (*(s8*)(D_8219A520 + 0x3C9) == 0) {
                sBattleScene.scene->unk_3C = 7;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x3C8, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 6:
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->unk_3C++;
                Battle_ClearMessageCursor();
            }
            break;

        case 7:
            if (func_82124BF8((ActivePokemon*)D_8219A540) == 0) {
                D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
                D_8219A564 = func_8210F31C(D_8219A544);
                func_82122DFC(arg0, (ActivePokemon*)D_8219A540);
                func_8212A4CC((s32)arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}


void func_8212AD10(CameraNode* arg0, s32 arg1) {
    BattleMonRuntime* sp1C = &((ActivePokemon*)D_8219A540)->state.runtime;

    switch (sBattleScene.scene->unk_3C) {
        case 0:
            func_8212A554(arg1);
            func_82124A40();
            BattleScene_ResetCameraFrameCounter();
            func_82125580();
            BattleScene_SetDamageShakeAmplitude((ActivePokemon*)D_8219A540);
            func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->unk_2C);
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 4);
            func_8212A768((ActivePokemon*)D_8219A540, arg0, arg1);
            func_8212239C((ActivePokemon*)D_8219A540, arg0);
            func_82110B44((ActivePokemon*)D_8219A540);
            func_821061A8((ActivePokemon*)D_8219A540);
            func_82135098((ActivePokemon*)D_8219A540);
            break;

        case 1:
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            func_82122DFC(arg0, (ActivePokemon*)D_8219A540);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                func_82124E80();
                func_8212A4A4((s8*)(D_8219A520 + 0x88));
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 2:
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            func_82122DFC(arg0, (ActivePokemon*)D_8219A540);
            if (D_8219A578 == 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 3:
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            if (sp1C->unk_0C != 0) {
                if (BattleScene_IsRowAnimWaitComplete((ActivePokemon*)D_8219A540, 0xF) != 0) {
                    sBattleScene.scene->unk_3C++;
                }
                if (func_82122DFC(arg0, (ActivePokemon*)D_8219A540) != 0) {
                    sBattleScene.scene->unk_3C = 5;
                }
            } else if ((func_82122DFC(arg0, (ActivePokemon*)D_8219A540) != 0) && (func_82121820(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->unk_3C = 6;
            }
            break;

        case 4:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            if (func_82122DFC(arg0, (ActivePokemon*)D_8219A540) != 0) {
                sBattleScene.scene->unk_3C = 6;
            }
            break;

        case 5:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            func_82122DFC(arg0, (ActivePokemon*)D_8219A540);
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            if (BattleScene_IsRowAnimWaitComplete((ActivePokemon*)D_8219A540, 0xF) != 0) {
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 6:
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            if (*(s8*)(D_8219A520 + 0x3C9) == 0) {
                sBattleScene.scene->unk_3C = 8;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x3C8, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 7:
            D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
            D_8219A564 = func_8210F31C(D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->unk_3C++;
                Battle_ClearMessageCursor();
            }
            break;

        case 8:
            if (func_82124BF8((ActivePokemon*)D_8219A540) == 0) {
                D_8219A560 = func_8210F31C((s32)(ActivePokemon*)D_8219A540);
                D_8219A564 = func_8210F31C(D_8219A544);
                func_82122DFC(arg0, (ActivePokemon*)D_8219A540);
                func_8212A4CC((s32)arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}
