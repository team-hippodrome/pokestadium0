/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_3438B0.h"

extern s32 D_8219A520;
extern ActivePokemon* D_8219A540;
extern s32 D_8219A544;
extern s32 D_8219A560;
extern s32 D_8219A564;
extern s32 D_8219A570;
extern s32 D_8219A578;
extern u8* D_82189180[];
extern u8* D_8218B2F4[];
extern u8 D_8219A4F4;
extern u8 D_80073D84[];
extern u8* D_8218B320[];
extern s32 D_8219A568;
extern MoveAnimInfoZ D_80073D90[];
extern f32 D_FLT_82189354[][4];
extern s8 *D_8219A5A0;

void BattleAnim_RenderNop1(void) {
}

void BattleAnim_RenderNop2(void) {
}


void func_8212B270(CameraNode* arg0, void* arg1) {
    u8* sp24 = (u8*)D_8219A544 + 0x7C6;
    Cue8212B270* temp_v1 = (sp24[0x5A] - 1) + (Cue8212B270*)D_82189180[func_82107A5C(D_8219A540)];
    volatile s32 sp1C;

    if (M2C_FIELD(D_8219A540, s16*, 0x1A) == 0x98) {
        sp1C = 0xF;
    } else if (temp_v1->unk_0A == 0xFF) {
        sp1C = M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x44), u16*, 0xA) - temp_v1->unk_06;
    } else {
        sp1C = temp_v1->unk_0A - temp_v1->unk_06;
    }

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            func_8212A554(arg1);
            func_82124A40();
            func_82121EB0(D_8219A540);
            func_82104C68((ActivePokemon*)D_8219A544, 4);
            func_8212A768(D_8219A540, arg0, (void*)D_8219A570);
            D_8219A570--;
            if (D_8219A570 < 0) {
                func_82124E80();
                func_82135098(D_8219A540);
                func_8212A768(D_8219A540, arg0, (void*)D_8219A570);
                func_8212239C(D_8219A540, arg0);
                func_82122DFC(arg0, D_8219A540);
                func_82110B44(D_8219A540);
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseSubstep = 2;
                D_8219A578 = 0;
                func_8212A4A4(D_8219A520 + 0x148);
                if (M2C_FIELD(D_8219A520, s8*, 0x149) != 0) {
                    D_8219A578 = 1;
                }
                func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                func_821061A8(D_8219A540);
            } else {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(sp1C) != 0) {
                func_80040738();
                BattleAnim_CleanupEffects(1);
                sBattleScene.scene->phaseSubstep = 0;
            }
            break;

        case 2:
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
                func_8211F034(D_8219A520 + 0x308, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 3:
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 4:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (D_8219A578 == 0) {
                func_8212A4A4(D_8219A520 + 0x88);
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                func_8212A4A4(D_8219A520 + 0x88);
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 5:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (D_8219A578 == 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8212A4A4(D_8219A520 + 0x208);
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8212A4A4(D_8219A520 + 0x208);
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 6:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sp24, u16*, 0xC) != 0) {
                if (func_82105C8C(D_8219A540, 0xF) != 0) {
                    sBattleScene.scene->phaseSubstep++;
                }
                if (func_82122DFC(arg0, D_8219A540) != 0) {
                    sBattleScene.scene->phaseSubstep = 8;
                }
            } else if ((func_82122DFC(arg0, D_8219A540) != 0) && (BattleScene_AdvanceCameraFrameCounterUntil(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseSubstep = 9;
            }
            break;

        case 7:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (func_82122DFC(arg0, D_8219A540) != 0) {
                sBattleScene.scene->phaseSubstep = 9;
            }
            break;

        case 8:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (func_82105C8C(D_8219A540, 0xF) != 0) {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 9:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (M2C_FIELD(D_8219A520, s8*, 0x3C9) == 0) {
                sBattleScene.scene->phaseSubstep = 0xB;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x3C8, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 10:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->phaseSubstep++;
                Battle_ClearMessageCursor();
            }
            break;

        case 11:
            if (func_82124BF8(D_8219A540) == 0) {
                D_8219A560 = func_8210F31C(D_8219A540);
                D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
                func_82122DFC(arg0, D_8219A540);
                func_8212A4CC(arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}


void func_8212BA28(CameraNode* arg0, void* arg1) {

    u8* sp1C = (u8*)D_8219A540 + 0x7C6;

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            func_82135098(D_8219A540);
            func_8212A554(arg1);
            func_82124A40();
            BattleScene_ResetCameraFrameCounter();
            func_82110B44(D_8219A540);
            func_8212A4A4(D_8219A520 + 0x148);
            func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
            func_8212A768(D_8219A540, arg0, arg1);
            func_8212239C(D_8219A540, arg0);
            func_82104C68((ActivePokemon*)D_8219A544, 0xB);
            sBattleScene.scene->phaseSubstep++;
            break;

        case 1:
            func_82124E80();
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 2:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 3:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sp1C, u16*, 0xC) != 0) {
                if (func_82105C8C(D_8219A540, 0xF) != 0) {
                    sBattleScene.scene->phaseSubstep++;
                }
                if (func_82122DFC(arg0, D_8219A540) != 0) {
                    sBattleScene.scene->phaseSubstep = 5;
                }
            } else if ((func_82122DFC(arg0, D_8219A540) != 0) && (BattleScene_AdvanceCameraFrameCounterUntil(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseSubstep = 6;
            }
            break;

        case 4:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (func_82122DFC(arg0, D_8219A540) != 0) {
                sBattleScene.scene->phaseSubstep = 6;
            }
            break;

        case 5:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (func_82105C8C(D_8219A540, 0xF) != 0) {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 6:
            if (M2C_FIELD(D_8219A520, s8*, 0x3C9) == 0) {
                sBattleScene.scene->phaseSubstep = 8;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                D_8219A560 = func_8210F31C(D_8219A540);
                D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x3C8, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 7:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->phaseSubstep++;
                Battle_ClearMessageCursor();
            }
            break;

        case 8:
            if (func_82124BF8(D_8219A540) == 0) {
                D_8219A560 = func_8210F31C(D_8219A540);
                D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
                func_82122DFC(arg0, D_8219A540);
                func_8212A4CC(arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}


void func_8212BF28(CameraNode* arg0, void* arg1) {
    s32 other;

    func_821255EC(arg0);
    sBattleScene.scene->cameraPresetId = 2;
    other = sBattleScene.scene->actingSide == 0;
    func_82110B44(sActivePokemon[other]);
    if (sBattleScene.scene->hitReactionKind == 3) {
        func_8212BA28(arg0, arg1);
    } else if (sBattleScene.scene->hitReactionKind == 1) {
        func_8212B270(arg0, arg1);
    } else if (sBattleScene.scene->hitReactionKind == 2) {
        func_8212AD10(arg0, arg1);
    } else {
        func_8212A850(arg0, arg1);
    }
}


void func_8212BFF0(CameraNode* arg0) {
    s32 n = 10;
    u8* sp = (u8*)sActivePokemon[sBattleScene.scene->actingSide] + 0x7C6;

    if (sBattleScene.scene->mode == n) {
        switch (sBattleScene.scene->phaseStep) {
            case 0:
                func_82128CDC(arg0, D_8218B2F4[D_8219A4F4][0]);
                break;
            case 1:
                func_82128F2C(arg0, 0);
                break;
            case 2:
                func_82129AE8(arg0, D_8218B2F4[D_8219A4F4][1]);
                break;
            case 3:
                func_8212A328(arg0, D_8218B2F4[D_8219A4F4][2]);
                break;
            case 4:
                func_8212BF28(arg0, (void*)D_8218B2F4[D_8219A4F4][3]);
                break;
        }
    } else {
        switch (sBattleScene.scene->phaseStep) {
            case 0:
                func_82128CDC(arg0, *(u16*)(D_80073D84 + 2 + sp[0x5A] * n));
                break;
            case 1:
                func_82128F2C(arg0, 0);
                break;
            case 2:
                func_82129AE8(arg0, *(u16*)(D_80073D84 + 4 + sp[0x5A] * n));
                break;
            case 3:
                func_8212A328(arg0, *(u16*)(D_80073D84 + 6 + sp[0x5A] * n));
                break;
            case 4:
                func_8212BF28(arg0, (void*)*(u16*)(D_80073D84 + 8 + sp[0x5A] * n));
                break;
        }
    }
}


void func_8212C1C4(CameraNode* arg0) {
    s32 n = 10;
    u8* sp = (u8*)sActivePokemon[sBattleScene.scene->actingSide] + 0x7C6;

    if (sBattleScene.scene->mode == n) {
        switch (sBattleScene.scene->phaseStep) {
            case 0:
                func_82128CDC(arg0, D_8218B320[D_8219A4F4][0]);
                break;
            case 1:
                func_82128F2C(arg0, 0);
                break;
            case 2:
                func_82129AE8(arg0, D_8218B320[D_8219A4F4][1]);
                break;
            case 3:
                func_8212A328(arg0, D_8218B320[D_8219A4F4][2]);
                break;
            case 4:
                func_8212BF28(arg0, (void*)D_8218B320[D_8219A4F4][3]);
                break;
        }
    } else {
        switch (sBattleScene.scene->phaseStep) {
            case 0:
                func_82128CDC(arg0, *(u16*)(D_80073D84 + 2 + sp[0x5A] * n));
                break;
            case 1:
                func_82128F2C(arg0, 0);
                break;
            case 2:
                func_82129AE8(arg0, *(u16*)(D_80073D84 + 4 + sp[0x5A] * n));
                break;
            case 3:
                func_8212A328(arg0, *(u16*)(D_80073D84 + 6 + sp[0x5A] * n));
                break;
            case 4:
                func_8212BF28(arg0, (void*)*(u16*)(D_80073D84 + 8 + sp[0x5A] * n));
                break;
        }
    }
}


void func_8212C398(s32 arg0)
{
  s32 temp_v0;
  s32 var_v1;
 temp_v0 = func_8210C020(3, arg0); D_8219A568 = temp_v0; var_v1 = temp_v0; if (temp_v0 >= 4) { D_8219A568 = 0 ^ 0; var_v1 = 0; } switch (var_v1) { case 0: // FAKE: no-op ^ 0
      func_82124984(D_8219A544, arg0, 0);
      return;

    case 1:
      func_82124984(D_8219A544, arg0, 1);
      return;

    case 2:
      func_82124984(D_8219A544, arg0, 2);
      return;

    default:
      func_82124984(D_8219A544, arg0, 0);
      return;

  }

}

void func_8212C454(s32 arg0)
{
  s32 temp_v0;
  s32 var_v1;
 temp_v0 = func_8210C020(4, arg0); D_8219A568 = temp_v0;
  var_v1 = temp_v0;
  if (temp_v0 >= 5)
  {
    D_8219A568 = 0;
    var_v1 = 0;
  }
  switch (var_v1)
  {
    case 0:
      func_82124984(D_8219A544, arg0, 0);
      return;

    case 1:
      func_82124984(D_8219A544, arg0, 1);
      return;

    case 2:
      func_82124984(D_8219A544, arg0, 2);
      return;

    case 3:
      func_82124984(D_8219A544, arg0, 3);
      return;

    default:
      func_82124984(D_8219A544, arg0, 0);
      return;

  }

}

void func_8212C530(s32 arg0)
{
  s32 temp_v0;
  s32 var_v1;
 do { temp_v0 = func_8210C020(4, arg0); D_8219A568 = temp_v0; var_v1 = temp_v0 & 0xFFFFFFFFFFFFFFFF; } while (0);  // FAKE
  if (temp_v0 >= 5)
  {
    D_8219A568 = 0;
    var_v1 = 0;
  }
  switch (var_v1)
  {
    case 0:
      func_82124984(D_8219A544, arg0, 0);
      return;

    case 1:
      func_82124984(D_8219A544, arg0, 1);
      return;

    case 2:
      func_82124984(D_8219A544, arg0, 2);
      return;

    case 3:
      func_82124984(D_8219A544, arg0, 4);
      return;

    default:
      func_82124984(D_8219A544, arg0, 0);
      return;

  }

}


void func_8212C60C(s32 arg0, s32 arg1) {
    switch (arg1) {
        case 0:
            func_82124984(D_8219A544, arg0, 0);
            break;
        case 1:
            func_82124984(D_8219A544, arg0, 1);
            break;
        case 2:
            func_82124984(D_8219A544, arg0, 2);
            break;
        case 3:
            func_82124984(D_8219A544, arg0, 3);
            break;
        case 4:
            func_82124984(D_8219A544, arg0, 4);
            break;
        default:
            func_82124984(D_8219A544, arg0, 0);
            break;
    }
}


void func_8212C6E8(ActivePokemon* arg0, CameraNode* arg1, s32 arg2) {
    switch (arg2) {
        case 0:
            BattleScene_CameraShotTargetHighThunk(arg1, arg0);
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

void func_8212C78C(s32 arg0) {
    BattleMonRuntime* runtime;

    runtime = &((ActivePokemon*)D_8219A544)->state.runtime;
    M2C_FIELD(sBattleScene.scene, s32*, 0x54) = 0;
    if (D_80073D90[runtime->usedMove - 1].unk_02 == 5) {
        func_8212C398(arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_02 == 6) {
        func_8212C454(arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_02 == 7) {
        func_8212C530(arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_02 == 4) {
        M2C_FIELD(sBattleScene.scene, s32*, 0x54) = 1;
        func_8212C60C(arg0, D_80073D90[runtime->usedMove - 1].unk_02);
    } else {
        func_8212C60C(arg0, D_80073D90[runtime->usedMove - 1].unk_02);
    }
}

void func_8212C874(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 5) != 0) {
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                func_8212239C((ActivePokemon*)D_8219A544, arg0);
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (sBattleScene.scene->stepFrameTimer == 0x37) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x3C) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}


/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleScene_Phase30(CameraNode* arg0) {
    u8* sp1C = (u8*)D_8219A540 + 0x7C6;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 5) != 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                func_82135098(D_8219A540);
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (sBattleScene.scene->stepFrameTimer == 0x46) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x6E) != 0) {
                BattleAnim_CleanupEffects(1);
                func_80040738();
                func_8211F034(D_8219A520 + 0x148, !sBattleScene.scene->actingSide);
                func_8212C6E8(D_8219A540, arg0, BattleAnim_RandomRange(2));
                func_8212239C(D_8219A540, arg0);
                func_82104C68((ActivePokemon*)D_8219A544, 4);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            func_82122A7C(arg0, D_8219A540);
            if (sBattleScene.scene->stepFrameTimer == 0x28) {
                Battle_ClearMessageCursor();
                func_8211F034(D_8219A520 + 0x88, !sBattleScene.scene->actingSide);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x50) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            func_82122A7C(arg0, D_8219A540);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((D_8219A564 == 1) && (D_8219A560 == 1)) {
                if (M2C_FIELD(sp1C, u16*, 0xC) != 0) {
                    BattleAnim_CleanupEffects(1);
                    func_82135098((ActivePokemon*)D_8219A544);
                    func_80040738();
                    func_82124984(D_8219A544, (s32)arg0, 3);
                    sBattleScene.scene->phaseStep++;
                } else {
                    func_82135098(D_8219A540);
                    if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                        sBattleScene.scene->actionPass = 3;
                    }
                    BattleScene_ResetCameraFrameCounter();
                    func_82124A40();
                    BattleScene_SetPhase(arg0, 5);
                }
            }
            break;

        case 4:
            func_82122A7C(arg0, D_8219A540);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            func_82124A40();
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}


void func_8212CF90(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_821255B4(arg0);
            func_82124984(D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0xA) != 0) {
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            func_82124984(D_8219A544, arg0, 3);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 2:
            if (sBattleScene.scene->stepFrameTimer == 0x37) {
                func_8211EE8C();
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 3:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}


void func_8212D194(CameraNode* arg0) {

    u8* sp24 = (u8*)D_8219A544 + 0x78C;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                func_8212239C((ActivePokemon*)D_8219A544, arg0);
                BattleScene_ResetCameraFrameCounter();
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                func_82110B44((ActivePokemon*)D_8219A544);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x64) != 0) {
                sBattleScene.scene->phaseStep = 4;
            }
            if (BattleScene_IsCameraFrameCounterAtLeast(0x1E) != 0) {
                Battle_ClearMessageCursor();
                if (M2C_FIELD(sp24, u16*, 0x36) & 1) {
                    func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep++;
                } else {
                    func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep = 3;
                }
            }
            break;

        case 2:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x64) != 0) {
                sBattleScene.scene->phaseStep = 4;
            }
            if (BattleScene_IsCameraFrameCounterAtLeast(0x3C) != 0) {
                func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x64) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 4:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            func_82124A40();
            func_82125C80(arg0);
            break;
    }
}


void func_8212D504(CameraNode* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    u8* sp30 = (u8*)D_8219A544 + 0x7C6;
    u8* sp2C = (u8*)D_8219A540 + 0x7C6;
    u8* sp28 = (u8*)D_8219A544 + 0x78C;
    u8* sp24 = (u8*)D_8219A540 + 0x78C;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_821217DC(0x14) != 0) {
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (func_821217DC(0x19) != 0) {
                func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                func_821233EC(arg0, (ActivePokemon*)D_8219A544);
                if (sp30[0x4D] & 0x10) {
                    if (sp2C[0x4E] & 8) {
                        M2C_FIELD(sp28, s16*, 0xC0) = M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = M2C_FIELD(sp24, s16*, 0xC2);
                    } else if (M2C_FIELD(M2C_FIELD(D_8219A540, u8**, 0x85C), s16*, 2) == 0x98) {
                        M2C_FIELD(sp28, s16*, 0xC0) = M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = sp2C[0xB];
                    } else {
                        M2C_FIELD(sp28, s16*, 0xC0) = M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = M2C_FIELD(M2C_FIELD(D_8219A540, u8**, 0x85C), s16*, 2);
                    }
                } else if (sp2C[0x4E] & 8) {
                    M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = M2C_FIELD(sp24, s16*, 0xC2);
                } else if (M2C_FIELD(M2C_FIELD(D_8219A540, u8**, 0x85C), s16*, 2) == 0x98) {
                    M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = sp2C[0xB];
                } else {
                    M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = M2C_FIELD(M2C_FIELD(D_8219A540, u8**, 0x85C), s16*, 2);
                }
                *M2C_FIELD(D_8219A544, u8**, 0x85C) |= 0x80;
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (*M2C_FIELD(D_8219A544, u8**, 0x85C) & 0x10) {
                *M2C_FIELD(D_8219A544, u8**, 0x85C) &= ~0x90;
                func_8210881C((ActivePokemon*)D_8219A544);
                func_82107408((ActivePokemon*)D_8219A544);
                func_82101B54((ActivePokemon*)D_8219A544, sp30[0x5A]);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            func_8003FE58(sp30[0x5A], M2C_FIELD(D_8219A544, s16*, 0x1A), 0);
            func_82104C68((ActivePokemon*)D_8219A544, 0x12);
            func_821233EC(arg0, (ActivePokemon*)D_8219A544);
            sBattleScene.scene->phaseStep++;
            break;

        case 4:
            M2C_FIELD(D_8219A544, u8**, 0x9CC)[1] |= 1;
            M2C_FIELD(D_8219A544, u8*, 0x865) |= 1;
            func_82107160((ActivePokemon*)D_8219A544);
            func_821233EC(arg0, (ActivePokemon*)D_8219A544);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x32) != 0) {
                func_82124A40();
                func_82125C34(arg0);
            }
            break;
    }
}


void func_8212D820(CameraNode* arg0) {
    BattleMonRuntime* sp1C = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;
    ActivePokemonState* sp18 = &sActivePokemon[sBattleScene.scene->actingSide]->state;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                func_821255B4(arg0);
                BattleAnim_PlayMoveEffectScript((ActivePokemon*)D_8219A544, sp1C->usedMove);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                if (sp18->flags & 0x800) {
                    func_821020FC((s8*)D_8219A544);
                }
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (sp18->flags & 0x800) {
                BattleScene_ResetOwnerModelIfLoaded((ActivePokemon*)D_8219A544);
            }
            if (BattleAnim_IsSessionBusy((ActivePokemon*)D_8219A544) == 0) {
                Battle_ClearRuntimeFlags((ActivePokemon*)D_8219A544, 0x800);
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 2:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            BattleScene_RecenterCameraOnOwner(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x46) != 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 3:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            BattleScene_RecenterCameraOnOwner(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

void func_80042A6C(s32);

/**
 * Camera state machine (sibling of func_8212C874). Sets scene->unk_50 = 4 and switches on
 * scene->unk_20:
 * 0: once func_82105724(D_8219A544, 0x1E) succeeds, runs the shared camera setup
 * (func_821255B4, func_8212C78C, func_8211F034, ...), plays sound 0x2E, resets the
 * camera frame counter and advances to state 1.
 * 1: while scene->unk_54 == 1, eases the camera field at +0x2C towards 60.0f; when the frame
 * counter reaches 0x32, clears the message cursor and advances to state 2.
 * 2: same easing, caches func_8210F31C for both active Pokemon in D_8219A560/D_8219A564,
 * sets scene->unk_34 = 3 if byte 0x820 of D_8219A540 is 0xFF, resets the frame counter
 * and animation step and finishes through func_82125C80.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleScene_Phase38(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_821255B4(arg0);
                func_80042A6C(0x2E);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x32) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

void func_8210568C(ActivePokemon*, s32, s32);

// Returns int with no return statement (most likely an old-style definition with
// no return type). func_8212DE30 only matches when this call is seen as
// returning a value: it keeps $v0 away from the scene pointer there.
s32 func_8212DD14(ActivePokemon* arg0) {
    ActivePokemonState* state = &arg0->state;
    BattleMon* sp28 = &arg0->teamRoster->pokemonPicked[arg0->state.rosterIndex];

    if (arg0->state.flags & 2) {
        func_82136708(1, arg0);
        M2C_FIELD(arg0, u8*, 2) |= 0x20;
        func_82105E4C(arg0, 2);
    }
    if (state->flags & 1) {
        M2C_FIELD(sp28, s8*, 5) = 0;
        func_8210568C(arg0, 0xB8, 1);
        func_82136708(3, arg0);
        func_82105E4C(arg0, 1);
    }
    if (state->flags & 0x80) {
        func_82136708(2, sActivePokemon[sBattleScene.scene->actingSide]);
        func_82105E4C(sActivePokemon[sBattleScene.scene->actingSide], 0x80);
    }
    func_82110B44(arg0);
}

void func_82104C68(ActivePokemon*, s32);
s32 func_82105724(ActivePokemon*, s32);
void func_82105E64(ActivePokemon*);
void func_8212DE30(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 5) != 0) {
                func_8212C78C((s32)arg0);
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (sBattleScene.scene->stepFrameTimer == 0x37) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x3C) != 0) {
                func_8212DD14(D_8219A540);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

void func_8212E0B0(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                BattleScene_ResetCameraFrameCounter();
                func_821224F4();
                func_82125570();
                Battle_ClearMessageCursor();
                func_82104C68((ActivePokemon*)D_8219A544, 8);
                M2C_FIELD(sBattleScene.scene, f32*, 0x88) = 0.5f;
                BattleAnim_Vec3fCopy(&sBattleScene.scene->unk_B8, &arg0->view.targetPosition);
                BattleAnim_Vec3fCopy(&sBattleScene.scene->unk_C4, &arg0->view.eyePosition);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            BattleAnim_ApproachF(&M2C_FIELD(sBattleScene.scene, f32*, 0x88), 0.0f, 0.06f);
            func_8212311C(arg0, (ActivePokemon*)D_8219A544, M2C_FIELD(sBattleScene.scene, f32*, 0x88));
            if (((ActivePokemon*)D_8219A544)->displayObject.position.y - D_FLT_82189354[M2C_FIELD(D_8219A544, s16*, 0x1A)][0] >= 800.0f) {
                func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            func_82105E38((ActivePokemon*)D_8219A544, 0x200);
            BattleAnim_Vec3fCopy(&arg0->view.targetPosition, &sBattleScene.scene->unk_B8);
            BattleAnim_Vec3fCopy(&arg0->view.eyePosition, &sBattleScene.scene->unk_C4);
            sBattleScene.scene->phaseStep++;
            break;

        case 3:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (func_82121820(0x28) != 0)) {
                func_82105E38(sActivePokemon[sBattleScene.scene->actingSide], 4);
                func_8213C4B8();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}

void func_82123314(CameraNode*, ActivePokemon*);
f32 func_82107EC8(ActivePokemon*);
/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleScene_Phase13(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                func_8212239C((ActivePokemon*)D_8219A544, arg0);
                Battle_ClearMessageCursor();
                func_82104C68((ActivePokemon*)D_8219A544, 8);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (((ActivePokemon*)D_8219A544)->modelTransformTimer == 2) {
                func_82123314(arg0, (ActivePokemon*)D_8219A544);
            }

            if ((((ActivePokemon*)D_8219A544)->displayObject.objectType != 0x32) && (((ActivePokemon*)D_8219A544)->displayObject.objectType != 0x33)) {
                if ((BattleAnim_IsAssetLoadBusy((ActivePokemon*)D_8219A544) == 0) && (((ActivePokemon*)D_8219A544)->displayObject.position.y <= (-func_82107EC8((ActivePokemon*)D_8219A544) * 2.5))) {
                    func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                    func_82105E38((ActivePokemon*)D_8219A544, 0x4000);
                    ((ActivePokemon*)D_8219A544)->displayObject.node.renderFlags &= 0xFFDF;
                    sBattleScene.scene->phaseStep++;
                }
            } else if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                func_82105E38((ActivePokemon*)D_8219A544, 0x4000);
                ((ActivePokemon*)D_8219A544)->displayObject.node.renderFlags &= 0xFFDF;
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            func_82123314(arg0, (ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            func_82123314(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            func_82124A40();
            func_82125C80(arg0);
            break;
    }
}

extern s32 D_84390220;
extern ActivePokemon* D_84390204;
extern s32 D_84390224;
s32 func_82121798(s32);
void func_8212188C(void);
void func_8212189C(void);
s32 BattleScene_IsMoveKeyedRowWaitComplete(ActivePokemon*, s32);
void func_82124A40(void);
/**
 * BattleScene_Phase14: two-step camera/animation state for a battle move effect.
 * Sets the scene's unk_50 to 4, then switches on the scene state counter
 * (unk_20):
 * 0: calls func_82124984 for the active Pokemon (D_8219A544) and waits on
 * func_82105724(.., 0x1E), a "move cue reached" check that falls back to
 * a 0x1E-frame wait when the Pokemon is frozen, asleep, airborne or
 * underground.  Once it reports true the effect is set up
 * (func_821255B4, func_8211F034, func_8212188C/func_8212189C,
 * func_82104C68 with 8, func_82110B44) and the state counter advances.
 * 1: calls func_8211EE8C when func_82121798(0x28) fires, refreshes
 * D_8219A560/D_8219A564 from the two entries of sActivePokemon (the
 * indices unk_2C and !unk_2C), and when BattleScene_IsMoveKeyedRowWaitComplete(.., 0x1E) -- the
 * same kind of cue check -- reports true calls func_82124A40 and
 * func_82125C80.
 * Same shape as func_8212C874 and func_8212E7B0.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleScene_Phase14(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_82124984(D_8219A544, (s32)arg0, 3);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212188C();
                func_8212189C();
                func_82104C68((ActivePokemon*)D_8219A544, 8);
                func_82110B44((ActivePokemon*)D_8219A544);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (func_82121798(0x28) != 0) {
                func_8211EE8C();
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_IsMoveKeyedRowWaitComplete((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_82124A40();
                func_82125C80(arg0);
            }
            break;
    }
}

void func_8212E7B0(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82104C68((ActivePokemon*)D_8219A544, 9);
                sBattleScene.scene->phaseStep++;
                func_82110B44((ActivePokemon*)D_8219A544);
            }
            break;

        case 1:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            func_82124A40();
            func_82125C80(arg0);
            break;
    }
}

void func_8212E9C8(ActivePokemon* arg0) {
    u8* ptr = (u8*)arg0 + 0x78C;

    if (M2C_FIELD(ptr, u16*, 0x36) & 0x200) {
        arg0->displayObject.position.y = D_FLT_82189354[M2C_FIELD(arg0, s16*, 0x1A)][0];
        func_82105E4C(arg0, 0x608);
    } else if (M2C_FIELD(ptr, u16*, 0x36) & 0x4008) {
        arg0->displayObject.lodFraction = 0xFF;
        func_82136708(4, arg0);
        arg0->displayObject.position.y = D_FLT_82189354[M2C_FIELD(arg0, s16*, 0x1A)][0];
        arg0->displayObject.node.renderFlags &= ~0x2;
        arg0->displayObject.node.renderFlags |= 0x20;
        arg0->displayObject.node.flags |= 1;
        func_82105E4C(arg0, 0x4608);
    }
}


void BattleScene_PhaseFaint(CameraNode* arg0) {
    func_821255EC(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98((ActivePokemon*)D_8219A544) == 0) {
                func_8212E9C8((ActivePokemon*)D_8219A544);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            BattleScene_ResetAnimationStep();
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xF);
            func_8212C6E8((ActivePokemon*)D_8219A544, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            func_8212239C((ActivePokemon*)D_8219A544, arg0);
            BattleScene_SetDamageShakeAmplitude((ActivePokemon*)D_8219A544);
            func_821366B0(8, (ActivePokemon*)D_8219A544);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 2:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            func_82122DFC(arg0, (ActivePokemon*)D_8219A544);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x32) != 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 3:
            if (func_82124BF8((ActivePokemon*)D_8219A544) == 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 4:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (func_82122DFC(arg0, (ActivePokemon*)D_8219A544) != 0) {
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}


void func_8212ECC8(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_821255B4(arg0);
            func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
            func_8212E9C8((ActivePokemon*)D_8219A544);
            func_82124984(D_8219A544, arg0, 3);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            func_82124984(D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                func_82110B44((ActivePokemon*)D_8219A544);
                BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 9);
                sBattleScene.scene->phaseStep += 1;
                func_82110B44((ActivePokemon*)D_8219A544);
            }
            break;

        case 2:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 3:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

void func_8212EEC0(ActivePokemon* arg0, CameraNode* arg1) {
    D_8219A568 = BattleAnim_RandomRange(3);
    if (D_8219A568 >= 4) {
        D_8219A568 = 0;
    }
    switch (D_8219A568) {
        case 0:
            BattleScene_CameraShotTargetHighThunk(arg1, arg0);
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

void func_8212EF74(ActivePokemon* arg0, CameraNode* arg1) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_8210C020(4, (s32)arg1); D_8219A568 = temp_v0;
    var_v1 = temp_v0;
    if (temp_v0 >= 5) {
        D_8219A568 = 0;
        var_v1 = 0;
    }
    switch (var_v1) {
        case 0:
            BattleScene_CameraShotTargetHighThunk(arg1, arg0);
            return;
        case 1:
            func_82124810(arg1, arg0);
            return;
        case 2:
            func_82124830(arg1, arg0);
            return;
        case 3:
            func_82124874(arg1, arg0);
            return;
        default:
            func_82124874(arg1, arg0);
            return;
    }
}

void func_8212F044(CameraNode* arg0) {
    s32 other = sBattleScene.scene->actingSide == 0;
    ActivePokemon* opp = sActivePokemon[other];
    BattleMonRuntime* runtime = &opp->state.runtime;

    if (D_80073D90[runtime->usedMove - 1].unk_06 == 5) {
        func_8212C6E8(opp, arg0, D_8219A568);
    } else if (D_80073D90[runtime->usedMove - 1].unk_06 == 4) {
        func_8212EEC0(opp, arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_06 == 6) {
        func_8212EF74(opp, arg0);
    } else {
        func_8212C6E8(opp, arg0, D_80073D90[runtime->usedMove - 1].unk_06);
    }
}

void func_8212F118(s32 arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_8219A5A0, s32 *, 0x20);
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8211EE8C();
        func_82125384();
        /* fallthrough */
    case 1:
        return;
    }
}


void func_8212F16C(CameraNode* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 side = sBattleScene.scene->actingSide;
    u8* sp1C = D_82189180[side] + 0x738;

    func_821255EC(arg0);
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_ResetAnimationStep();
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            if (func_82124B30((ActivePokemon*)D_8219A544) == 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                sBattleScene.scene->cameraPresetId = 1;
                func_82108C0C((ActivePokemon*)D_8219A544);
                func_8213B31C(1);
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                func_8212C6E8((ActivePokemon*)D_8219A544, arg0, 3);
                func_8212239C((ActivePokemon*)D_8219A544, arg0);
                func_82121EB0((ActivePokemon*)D_8219A544);
                BattleScene_ResetAnimationStep();
                ModelAnim_SetAnimation((DisplayObject*)D_8219A544, *sp1C);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            sBattleScene.scene->cameraPresetId = 1;
            func_8212C6E8((ActivePokemon*)D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                Battle_ClearMessageCursor();
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            sBattleScene.scene->cameraPresetId = 1;
            func_8212C6E8((ActivePokemon*)D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 4:
            sBattleScene.scene->cameraPresetId = 1;
            if (func_82124BF8((ActivePokemon*)D_8219A544) == 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 5:
            sBattleScene.scene->cameraPresetId = 1;
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            func_8212C6E8((ActivePokemon*)D_8219A544, arg0, 3);
            if ((D_8219A560 != 0) && (D_8219A564 != 0)) {
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}


void BattleScene_PhaseMoveFailedMessage(CameraNode* arg0) {
    ActivePokemonState* sp1C = &D_8219A540->state;

    func_821255EC(arg0);
    sBattleScene.scene->cameraPresetId = 2;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            if (sp1C->flags & 0x200) {
                func_8212C6E8(D_8219A540, arg0, D_8219A568 = 2);
            } else {
                func_8212C6E8(D_8219A540, arg0, D_8219A568 = BattleAnim_RandomRange(2));
            }
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xC);
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            sBattleScene.scene->phaseStep += 1;
            func_8210626C(D_8219A540);
            break;

        case 1:
            func_82124E80();
            if (func_821217DC(0x32) != 0) {
                BattleScene_CleanupParticipantEffectMode((ActivePokemon*)D_8219A544);
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                func_8211EE8C();
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}

void func_8212F5B4(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    func_821255EC(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            func_8212F044(arg0);
            func_8212239C(D_8219A540, arg0);
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xE);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            func_82122DFC(arg0, D_8219A540);
            if (sBattleScene.scene->stepFrameTimer == 0x1E) {
                func_82110B44(D_8219A540);
            }
            if (func_821217DC(0x50) != 0) {
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                func_8211EE8C();
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}

void func_8212F6E4(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    func_821255EC(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            BattleScene_ResetAnimationStep();
            BattleScene_ResetCameraFrameCounter();
            func_82110B44(D_8219A540);
            func_8212F044(arg0);
            func_8212239C(D_8219A540, arg0);
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xB);
            func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            func_82122DFC(arg0, D_8219A540);
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x6E) != 0) {
                sBattleScene.scene->phaseStep += 1;
                func_8211EE8C();
                BattleScene_ResetCameraFrameCounter();
            }
            break;

        case 2:
            if (func_82124BF8(D_8219A540) == 0) {
                func_82124E80();
                D_8219A560 = func_8210F31C(D_8219A540);
                D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
                func_82122A7C(arg0, D_8219A540);
                BattleScene_ResetAnimationStep();
                func_82125AC8(arg0);
            }
            break;
    }
}

void func_8212F894(CameraNode* arg0) {
    BattleMonRuntime* runtime = &((ActivePokemon*)D_8219A544)->state.runtime;

    sBattleScene.scene->cameraPresetId = 2;
    func_821255EC(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            func_8212C6E8(D_8219A540, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            BattleAnim_QueueMoveEffectEnd(runtime->usedMove, (ActivePokemon*)D_8219A544, D_8219A540, BattleScene_GetHitCueDefaultAnchor(D_8219A540), func_82107B54(D_8219A540));
            BattleScene_SetParticipantModelTransform(D_8219A540, 0x10, 0);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            func_82124E80();
            if (func_821217DC(0x50) != 0) {
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                func_8211EE8C();
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}

void func_8212F9FC(CameraNode* arg0) {
    func_821255EC(arg0);
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_82135098((ActivePokemon*)D_8219A544);
            func_82135098(D_8219A540);
            func_8213B31C(1);
            sBattleScene.scene->cameraPresetId = 2;
            func_82104C68((ActivePokemon*)D_8219A544, 4);
            func_8212C6E8(D_8219A540, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            func_82121EB0(D_8219A540);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            sBattleScene.scene->cameraPresetId = 2;
            D_8219A564 = func_8210F31C(D_8219A540);
            if (sBattleScene.scene->stepFrameTimer == 0x3C) {
                Battle_ClearMessageCursor();
            }
            if ((D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounter(0x96) != 0)) {
                func_8212C6E8((ActivePokemon*)D_8219A544, arg0, D_8219A568 = BattleAnim_RandomRange(4));
                func_80040738();
                func_8213B31C(1);
                func_821365E8(4, (ActivePokemon*)D_8219A544);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x5A) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0)) {
                func_82125570();
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                func_82124E80();
                func_82125AC8(arg0);
            }
            break;
    }
}


/**
 * Phase 6. Poison/burn-style residual damage after a move: BattleScene_UpdateDisplayedHpAndTransition enters it
 * when the acting Pokemon has unk_15 bits 0x18 or unk_4D bit 0x80 set. Plays effect list 5 or 6 (unk_15 bits)
 * and effect list 10 (unk_4D bit 0x80), then flips the acting side and enters BattleScene_PhaseFaint if the
 * acting Pokemon reaches 0 HP.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleScene_PhaseResidualDamageAfterMove(CameraNode* arg0) {
    u8* sp2C = (u8*)sActivePokemon[sBattleScene.scene->actingSide] + 0x7C6;
    u8* sp28 = (u8*)sActivePokemon[!sBattleScene.scene->actingSide] + 0x7C6;
    ActivePokemon* sp24 = sActivePokemon[sBattleScene.scene->actingSide];

    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            func_82124A40();
            func_82135098((ActivePokemon*)D_8219A544);
            func_82106374((ActivePokemon*)D_8219A544);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            func_82106354(sp24);
            if (func_82124A50(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                func_82108C0C((ActivePokemon*)D_8219A544);
                func_80040738();
                BattleAnim_CleanupEffects(1);
                func_82124894(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
                func_82104C68(sActivePokemon[sBattleScene.scene->actingSide], 0xD);
                if (sp2C[0x15] & 0x18) {
                    func_8211F034(D_8219A520 + 0x248, sBattleScene.scene->actingSide);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0xE);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0xE);
                    if (sp2C[0x15] & 0x10) {
                        func_821366B0(6, (ActivePokemon*)D_8219A544);
                    } else {
                        func_821366B0(5, (ActivePokemon*)D_8219A544);
                    }
                    sBattleScene.scene->phaseStep++;
                } else {
                    func_82135098(D_8219A540);
                    func_8211F034(D_8219A520 + 0x288, sBattleScene.scene->actingSide);
                    func_800407B0(0x22, 0, 0);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    func_821366B0(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->phaseStep = 3;
                }
            }
            break;

        case 2:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                if (func_82107CA0(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                    func_82125570();
                    BattleScene_SetPhase(arg0, 5);
                    sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
                } else if (sp2C[0x4D] & 0x80) {
                    func_82135098(D_8219A540);
                    func_800407B0(0x22, 0, 0);
                    func_8211F034(D_8219A520 + 0x288, sBattleScene.scene->actingSide);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    func_821366B0(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->phaseStep++;
                } else {
                    sBattleScene.scene->phaseStep = 4;
                }
            }
            break;

        case 3:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0) && (D_8219A560 == 1) && (D_8219A564 == 1)) {
                sBattleScene.scene->phaseStep++;
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
            }
            break;

        case 4:
            if (func_82124BF8(D_8219A540) == 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 5:
            func_82124A40();
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}


void func_82106374(ActivePokemon*);
s32 func_82124A50(ActivePokemon*);
void func_82108C0C(ActivePokemon*);
void func_821366B0(s32, ActivePokemon*);
void func_821237B0(CameraNode*, ActivePokemon*);
void func_82123684(CameraNode*, ActivePokemon*);
void func_82134EBC(ActivePokemon*, s32);
s32 func_82124BF8(ActivePokemon*);
/**
 * Phase 9 (moveEffectKind 9). The acting Pokemon takes damage from its own move: plays effect list 9, the
 * hit cue animation, and the damage shake while displayHp moves toward unk_12, then updates HP.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleScene_PhaseRecoilDamage(CameraNode* arg0) {
    BattleMonRuntime* self = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;
    BattleMonRuntime* other = &sActivePokemon[!sBattleScene.scene->actingSide]->state.runtime;

    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_82135098((ActivePokemon*)D_8219A544);
            func_82106374((ActivePokemon*)D_8219A544);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            if (func_82124A50(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                func_82108C0C((ActivePokemon*)D_8219A544);
                func_80040738();
                BattleAnim_CleanupEffects(1);
                func_821366B0(9, (ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                func_821237B0(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
                func_8211F034(D_8219A520 + 0x408, sBattleScene.scene->actingSide);
                self->displayHp = self->currentHp;
                other->displayHp = other->currentHp;
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            func_82123684(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0xF) != 0) {
                func_82134EBC((ActivePokemon*)D_8219A544, 0x1F);
                func_82121EB0((ActivePokemon*)D_8219A544);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            if (func_82124BF8(D_8219A540) == 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 4:
            BattleScene_ResetAnimationStep();
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->actingSide]);
            func_82123684(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (func_82121820(0x3C) != 0)) {
                func_82125AC8(arg0);
            }
            break;
    }
}

void BattleScene_Phase10(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_CleanupParticipantEffectMode((ActivePokemon*)D_8219A544);
            func_82106354(sActivePokemon[sBattleScene.scene->actingSide]);
            if (func_82124A50(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                func_82108C0C((ActivePokemon*)D_8219A544);
                func_80040738();
                BattleAnim_CleanupEffects(1);
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x348, !sBattleScene.scene->actingSide);
                BattleAnim_QueueEffectList6(3, D_8219A540);
                Audio_PlayCommand(0x23, 0, 0);
                func_82124894(arg0, D_8219A540);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(0x37) != 0) {
                func_8211EE8C();
                func_8211F034(D_8219A520 + 0x2C8, !sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }

        case 2:
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                func_8211EE8C();
                func_82125AC8(arg0);
            }
            break;
    }
}
