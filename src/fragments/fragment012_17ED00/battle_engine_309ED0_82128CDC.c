/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_309ED0.h"

extern s32 D_8219A570;
extern s32 D_8219A574;
void BattleAi_RecordUsedMove(s32, s32, s32);
extern s32 D_82199DE0;
M2C_UNK func_800419F8();
void func_82121D8C(s32, s32, s8 *);
void func_82133868(ActivePokemonState*);
f32 func_8000F23C(f32, f32, f32, f32);
void func_8210C104(s16*, s16, s16);
void ModelAnim_SetFrame(DisplayObject* display_object, s16 animation_timer);
f32 func_82121750(ActivePokemon*, f32, f32);
s16 func_82107CC4(ActivePokemon*);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);

s32 func_82125F54(void);
void func_82105FCC(s32);

void func_82128CDC(CameraNode* arg0, s32 arg1) {
    s8* sp1C = (s8*)D_8219A544 + 0x78C;

    func_821079E8(0x1FFE);
    func_82106374((s32)sActivePokemon[0]);
    func_82106374((s32)sActivePokemon[1]);
    if ((func_821250D4() == 0) && (func_82125F54() == 0)) {
        func_82105FCC(D_8219A544);
        if (sBattleScene.scene->moveEffectKind == 0xC) {
            arg1 = 0;
        }
        if (M2C_FIELD(sp1C, u16*, 0x36) & 0x400) {
            arg1 = 6;
        }
        switch (arg1) {
            case 0:
                func_82127354(arg0);
                break;
            case 1:
                func_82127724(arg0);
                break;
            case 2:
                func_82127DFC(arg0);
                break;
            case 3:
                func_8212817C(arg0);
                break;
            case 4:
                func_82128510(arg0);
                break;
            case 5:
                func_82128780(arg0);
                break;
            case 6:
                func_82128848(arg0);
                break;
            default:
                func_82127354(arg0);
                break;
        }
    }
}

void func_82128E34(s32 arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            func_82125580();
            break;
        case 1:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x14) != 0) {
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212188C();
                if (sBattleScene.scene->moveEffectKind == 0x14) {
                    func_82104C68(sActivePokemon[sBattleScene.scene->actingSide], 0x16);
                } else {
                    func_82104C68(sActivePokemon[sBattleScene.scene->actingSide], 3);
                }
                sBattleScene.scene->phaseStep++;
                func_82125570();
            }
            break;
    }
}

void func_82128F2C(CameraNode* arg0, s32 arg1) {
    BattleScene* scene;
    u8 temp_v1;
    int off;

    scene = sBattleScene.scene;
    temp_v1 = M2C_FIELD(sBattleScene.scene, u8*, 0x1B);
    off = 0x389;
    if ((temp_v1 != 0xA) && (M2C_FIELD(D_8219A520, s8*, off) != 0)) {
        M2C_FIELD(scene, u8*, 0x1B) = temp_v1 + 1;
        return;
    }
    func_82124A40();
    if (1) {  // karodo
    }
    D_8219A574 = D_8219A570 = sMultihitCount;
    if (func_82125CC8() == 0) {
        func_82128E34((s32)arg0);
    }
}

void func_82128FBC(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_SetPhaseFlag();
                BattleCamera_PlayShot((ActivePokemon*)D_8219A544, arg0, 0);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                BattleScene_ResetCameraSubstepCounter();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, (ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraSubstepCounter(0xF) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x32) != 0) {
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            break;
    }
}

void func_821290CC(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_SetPhaseFlag();
                BattleCamera_PlayShot((ActivePokemon*)D_8219A544, arg0, 1);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraSubstepCounter();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, (ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraSubstepCounter(0xF) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x32) != 0) {
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            break;
    }
}

void func_821291E4(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_SetPhaseFlag();
                BattleCamera_PlayShot((ActivePokemon*)D_8219A544, arg0, 2);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraSubstepCounter();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, (ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraSubstepCounter(0xF) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x32) != 0) {
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            break;
    }
}

void func_821292FC(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_SetPhaseFlag();
                BattleCamera_PlayShot((ActivePokemon*)D_8219A544, arg0, 3);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraSubstepCounter();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, (ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraSubstepCounter(0xF) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x32) != 0) {
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            break;
    }
}

void func_82129414(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (func_821217DC(0x14) != 0) {
                func_821255B4((s8*)arg0);
                func_82125580();
                BattleCamera_PlayShot((ActivePokemon*)D_8219A544, arg0, 4);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                func_8211EE8C();
                func_8212189C();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, (ActivePokemon*)D_8219A544);
            if (func_82121798(0xF) != 0) {
                func_8211EE8C();
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x32) != 0) {
                func_8211EE8C();
                func_8212188C();
                func_82125570();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            func_8210C1A8(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            break;
    }
}

void func_8212954C(CameraNode* arg0) {
    if (sBattleScene.scene->phaseSubstep == 0) {
        D_8219A568 = BattleAnim_RandomRange(3);
        if (D_8219A568 >= 4) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
        case 0:
            func_82128FBC(arg0);
            break;
        case 1:
            func_821290CC(arg0);
            break;
        case 2:
            func_821291E4(arg0);
            break;
        default:
            func_82128FBC(arg0);
            break;
    }
}

void func_8212960C(CameraNode* arg0) {
    if (sBattleScene.scene->phaseSubstep == 0) {
        D_8219A568 = BattleAnim_RandomRange(4);
        if (D_8219A568 >= 5) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
        case 0:
            func_82128FBC(arg0);
            break;
        case 1:
            func_821290CC(arg0);
            break;
        case 2:
            func_821291E4(arg0);
            break;
        case 3:
            func_821292FC(arg0);
            break;
        default:
            func_82128FBC(arg0);
            break;
    }
}

void func_821296E4(CameraNode* arg0) {
    if (sBattleScene.scene->phaseSubstep == 0) {
        D_8219A568 = BattleAnim_RandomRange(4);
        if (D_8219A568 >= 5) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
        case 0:
            func_82128FBC(arg0);
            break;
        case 1:
            func_821290CC(arg0);
            break;
        case 2:
            func_821291E4(arg0);
            break;
        case 3:
            func_82129414(arg0);
            break;
        default:
            func_82128FBC(arg0);
            break;
    }
}

extern s32 D_8219A56C;
void func_821297BC(CameraNode* arg0) {
    switch (M2C_FIELD(D_8219A5A0, s32*, 0x3C)) {
        case 0:
            M2C_FIELD(D_8219A5A0, s32*, 0x50) = 4;
            func_821255B4((s8*)arg0);
            BattleCamera_PlayShot((ActivePokemon*)D_8219A544, arg0, D_8219A570);
            BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
            func_82125580();
            break;
        case 1:
            M2C_FIELD(D_8219A5A0, s32*, 0x50) = 4;
            func_821228B0(arg0, (ActivePokemon*)D_8219A544);
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x32) != 0) {
                func_821255B4((s8*)arg0);
                func_8211EE8C();
                BattleCamera_PlayShot((ActivePokemon*)D_8219A544, arg0, D_8219A570 - 1);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                if (--D_8219A570 < 0 || D_82199F31 != 0) {
                    func_82125580();
                    do {  // FAKE
                        D_8219A570 = D_8219A56C;
                        M2C_FIELD(D_8219A5A0, s32*, 0x3C)++;
                    } while (0);
                } else {
                    func_82104C68(((ActivePokemon**)&D_82199DE0)[M2C_FIELD(D_8219A5A0, u16*, 0x2C)], 0x13);
                    Audio_FadeAndClearStoredSounds();
                    func_8213B31C(1);
                    M2C_FIELD(D_8219A5A0, s32*, 0x3C) = 1;
                }
            }
            break;
        case 2:
            M2C_FIELD(D_8219A5A0, s32*, 0x50) = 4;
            func_821228B0(arg0, (ActivePokemon*)D_8219A544);
            if (func_821217DC(0x28) != 0) {
                M2C_FIELD(D_8219A5A0, s32*, 0x50) = 0;
                func_8212188C();
                func_82125570();
                M2C_FIELD(D_8219A5A0, s32*, 0x48) = 0;
                Audio_FadeAndClearStoredSounds();
                M2C_FIELD(D_8219A5A0, s32*, 0x20)++;
            }
            break;
    }
}

void func_821299B0(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                sBattleScene.scene->cameraPresetId = 4;
                BattleScene_SetPhaseFlag();
                Battle_ClearMessageCursor();
                BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                BattleCamera_PlayShot((ActivePokemon*)D_8219A544, arg0, 3);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                BattleScene_ResetCameraSubstepCounter();
                func_821366B0(7, (ActivePokemon*)D_8219A544);
            }
            break;
        case 1:
            func_821228B0(arg0, (ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraSubstepCounter(0x28) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                sBattleScene.scene->cameraPresetId = 0;
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                sBattleScene.scene->phaseStep += 1;
            }
            break;
    }
}

extern s32 D_8219A568;

void func_82129AE8(CameraNode* arg0, s32 arg1) {
    s32 temp = M2C_FIELD(D_8219A5A0, s32*, 0x48);

    if (temp == 0x18) {
        arg1 = 0xA;
    } else if (temp == 0x14) {
        arg1 = 0xB;
    } else if ((arg1 != 5) && (arg1 != 6) && (arg1 != 7)) {
        D_8219A568 = arg1;
    }
    switch (arg1) {
        case 0:
            func_82128FBC(arg0);
            break;
        case 1:
            func_821290CC(arg0);
            break;
        case 2:
            func_821291E4(arg0);
            break;
        case 3:
            func_821292FC(arg0);
            break;
        case 4:
            func_82129414(arg0);
            break;
        case 5:
            func_8212954C(arg0);
            break;
        case 6:
            func_8212960C(arg0);
            break;
        case 7:
            func_821296E4(arg0);
            break;
        case 10:
            func_821297BC(arg0);
            break;
        case 11:
            func_821299B0(arg0);
            break;
        default:
            func_82128FBC(arg0);
            break;
    }
}

void BattleScene_ActionSetupAnimationVariantB(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 2;
            BattleAnim_CleanupEffects(1);
            BattleScene_ClearCameraOffsetVectors();
            BattleScene_SetPhaseFlag();
            func_82124284((s32)arg0, D_8219A540, 0.0f);
            break;

        case 1:
            func_821243DC((s32)arg0, D_8219A540, 0.0f);
            if (sBattleScene.scene->unk_74 <= 1.0f) {
                BattleScene_CleanupParticipantEffectMode((ActivePokemon*)D_8219A544);
                sBattleScene.scene->phaseStep++;
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
            }
            break;
    }
}

void func_82129D10(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            BattleScene_ClearCameraOffsetVectors();
            BattleScene_SetPhaseFlag();
            func_82124284((s32)arg0, D_8219A540, BattleScene_GetParticipantHeight(D_8219A540) * 2.0f);
            break;
        case 1:
            if (BattleAnim_IsSessionBusy((ActivePokemon*)D_8219A540) == 0) {
                func_821243DC((s32)arg0, D_8219A540, BattleScene_GetParticipantHeight(D_8219A540) * 2.0f);
                if (sBattleScene.scene->unk_74 <= 1.0f) {
                    BattleScene_CleanupParticipantEffectMode((ActivePokemon*)D_8219A544);
                    sBattleScene.scene->phaseStep++;
                    BattleScene_ClearPhaseFlag();
                    BattleScene_ResetCameraFrameCounter();
                }
            }
            break;
    }
}

void func_82129E30(s32 arg0) {
    s32 temp_v0;

    M2C_FIELD(D_8219A5A0, s32 *, 0x50) = 2;
    temp_v0 = M2C_FIELD(D_8219A5A0, s32 *, 0x3C);
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8213B31C(1);
        func_821224F4();
        func_82125580();
        func_82124284(arg0, D_8219A540, -BattleScene_GetParticipantHeight(D_8219A540) * D_FLT_821963A0);
        return;
    case 1:
        func_821243DC(arg0, D_8219A540, -BattleScene_GetParticipantHeight(D_8219A540) * D_FLT_821963A4);
        if (M2C_FIELD(D_8219A5A0, f32 *, 0x74) <= 1.0f) {
            func_82106374(D_8219A544);
            func_82125570();
            func_8212188C();
            M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
        }
        return;
    }
}

void func_82129F5C(CameraNode* arg0) {
    s32 temp_v0;

    M2C_FIELD(D_8219A5A0, s32 *, 0x50) = 2;
    temp_v0 = M2C_FIELD(D_8219A5A0, s32 *, 0x3C);
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8213B31C(1);
        func_821224F4();
        func_82125580();
        func_82124544((s32)arg0, D_8219A540, 8.0f, 6.0f, 2.5f, 6.0f, 0);
        return;
    case 1:
        func_82124664((s32)arg0, D_8219A540, 0);
        if (M2C_FIELD(D_8219A5A0, f32 *, 0x74) < (M2C_FIELD(D_8219A5A0, f32 *, 0x5C) + D_FLT_821963A8)) {
            func_82106374(D_8219A544);
            M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
            func_82125570();
            func_8212188C();
        }
        return;
    }
}

void func_8212A074(s32 arg0) {
    s32 temp_v0;

    M2C_FIELD(D_8219A5A0, s32 *, 0x50) = 2;
    temp_v0 = M2C_FIELD(D_8219A5A0, s32 *, 0x3C);
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8213B31C(1);
        func_821224F4();
        func_82125580();
        func_82124544(arg0, D_8219A540, 10.0f, 12.0f, 3.5f, 6.0f, 0x11C6);
        return;
    case 1:
        func_82124664(arg0, D_8219A540, 0x11C6);
        if (M2C_FIELD(D_8219A5A0, f32 *, 0x74) <= (M2C_FIELD(D_8219A5A0, f32 *, 0x5C) + 1.0f)) {
            func_82106374(D_8219A544);
            M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
            func_82125570();
            func_8212188C();
        }
        return;
    }
}

void func_8212A190(CameraNode* arg0) {
    if (sBattleScene.scene->phaseSubstep == 0) {
        D_8219A568 = BattleAnim_RandomRange(3);
        if (D_8219A568 >= 4) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
        case 0:
            func_82129C1C(arg0);
            break;
        case 1:
            func_82129D10(arg0);
            break;
        case 2:
            func_82129E30((s32)arg0);
            break;
        default:
            func_82129C1C(arg0);
            break;
    }
}

void func_8212A250(CameraNode* arg0) {
    if (sBattleScene.scene->phaseSubstep == 0) {
        D_8219A568 = BattleAnim_RandomRange(4);
        if (D_8219A568 >= 5) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
        case 0:
            func_82129C1C(arg0);
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
        default:
            func_82129C1C(arg0);
            break;
    }
}
