/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "audio_commands.h"
#include "geo_node.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK func_800419F8();
M2C_UNK func_82106374(s32);
M2C_UNK func_821079E8(M2C_UNK);
M2C_UNK func_8212189C();
M2C_UNK func_821224F4();
M2C_UNK func_82124284(s32, s32, f32);
M2C_UNK func_821243DC(s32, s32, f32);
M2C_UNK func_82124544(s32, s32, f32, f32, f32, f32, s32);
M2C_UNK func_82124664(s32, s32, M2C_UNK);
M2C_UNK func_82124A40();
extern s32 D_82199DE0;
extern s32 D_8219A520;
extern u8 D_82199F31;
f32 BattleScene_GetParticipantHeight(s32);
void BattleCamera_PlayShot(ActivePokemon* arg0, CameraNode* arg1, s32 arg2);
void BattleMessage_ShowForSide(s32, s32);
void func_82104C68(ActivePokemon*, s32);
void func_8210C1A8(f32*, f32, f32);
void func_8211EE8C(void);
void func_8212188C(void);

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
s16 BattleScene_GetParticipantFacingAngle(ActivePokemon* arg0);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);

s32 func_82125F54(void);
void func_82105FCC(s32);

/**
 * Step 0 of an action phase (2 or 3). Starts a switch instead when the action is one
 * (BattleScene_TryStartSwitchAction), otherwise runs the user's intro camera variant from the
 * per-move table at D_80073D84 (every move uses variant 5 outside mode 10).
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran at phase 2,
 * step 0, and called BattleScene_TryStartSwitchAction.
 */
void BattleScene_ActionStepIntro(CameraNode* arg0, s32 arg1) {
    s8* sp1C = (s8*)sActingPokemon + 0x78C;

    func_821079E8(0x1FFE);
    func_82106374((s32)sActivePokemon[0]);
    func_82106374((s32)sActivePokemon[1]);
    if ((BattleScene_TryStartSwitchAction() == 0) && (func_82125F54() == 0)) {
        func_82105FCC(sActingPokemon);
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

/**
 * Hit-count step of a move: on substep 1, once the user's animation is done (or 20 frames
 * in a frozen/asleep/airborne state), shows the move message and starts the user's model
 * reaction 0x16 (when moveEffectKind is 0x14) or 3, then advances the phase step.
 */
void func_82128E34(s32 arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            func_82125580();
            break;
        case 1:
            if (func_82105724(sActingPokemon, 0x14) != 0) {
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

/**
 * Step 1 of an action phase: copies sMultihitCount into the hit counters, then enters the effect
 * phase for moves that skip the attack animation (BattleScene_TryEnterEffectPhaseBeforeLaunch).
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran at phase 2,
 * step 1.
 */
void BattleScene_ActionStepSetHitCount(CameraNode* arg0, s32 arg1) {
    BattleScene* scene;
    u8 temp_v1;
    int off;

    scene = sBattleScene.scene;
    temp_v1 = sBattleScene.scene->unk_1B;
    off = 0x389;
    if ((temp_v1 != 0xA) && (M2C_FIELD(D_8219A520, s8*, off) != 0)) {
        scene->unk_1B = temp_v1 + 1;
        return;
    }
    func_82124A40();
    if (1) {  // karodo
    }
    D_8219A574 = D_8219A570 = sMultihitCount;
    if (BattleScene_TryEnterEffectPhaseBeforeLaunch() == 0) {
        func_82128E34((s32)arg0);
    }
}

/**
 * Move-use camera shot 0: after 20 frames plays the user's camera shot 0 and captures its
 * orbit, then follows the user until its move animation finishes (or 50 frames in a
 * frozen/asleep state), clearing the message cursor along the way.
 */
void func_82128FBC(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_SetPhaseFlag();
                BattleCamera_PlayShot(sActingPokemon, arg0, 0);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                BattleScene_ResetCameraSubstepCounter();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, sActingPokemon);
            if (BattleScene_AdvanceCameraSubstepCounter(0xF) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8(sActingPokemon, 0x32) != 0) {
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            break;
    }
}

/**
 * Move-use camera shot 1: same as func_82128FBC with camera shot 1.
 */
void func_821290CC(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_SetPhaseFlag();
                BattleCamera_PlayShot(sActingPokemon, arg0, 1);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraSubstepCounter();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, sActingPokemon);
            if (BattleScene_AdvanceCameraSubstepCounter(0xF) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8(sActingPokemon, 0x32) != 0) {
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            break;
    }
}

/**
 * Move-use camera shot 2: same as func_82128FBC with camera shot 2.
 */
void func_821291E4(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_SetPhaseFlag();
                BattleCamera_PlayShot(sActingPokemon, arg0, 2);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraSubstepCounter();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, sActingPokemon);
            if (BattleScene_AdvanceCameraSubstepCounter(0xF) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8(sActingPokemon, 0x32) != 0) {
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            break;
    }
}

/**
 * Move-use camera shot 3: same as func_82128FBC with camera shot 3.
 */
void func_821292FC(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_SetPhaseFlag();
                BattleCamera_PlayShot(sActingPokemon, arg0, 3);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraSubstepCounter();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, sActingPokemon);
            if (BattleScene_AdvanceCameraSubstepCounter(0xF) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8(sActingPokemon, 0x32) != 0) {
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            break;
    }
}

/**
 * Move-use camera shot 4: same pattern as func_82128FBC with camera shot 4, and eases the
 * field of view to 60 while it plays.
 */
void func_82129414(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            if (func_821217DC(0x14) != 0) {
                func_821255B4((s8*)arg0);
                func_82125580();
                BattleCamera_PlayShot(sActingPokemon, arg0, 4);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                func_8211EE8C();
                func_8212189C();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, sActingPokemon);
            if (func_82121798(0xF) != 0) {
                func_8211EE8C();
            }
            if (func_821058E8(sActingPokemon, 0x32) != 0) {
                func_8211EE8C();
                func_8212188C();
                func_82125570();
                sBattleScene.scene->cameraPresetId = 0;
                sBattleScene.scene->phaseStep++;
            }
            func_8210C1A8(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            break;
    }
}

/**
 * Move-use camera variant 5: picks shot 0, 1 or 2 at random on substep 0 and runs it.
 */
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

/**
 * Move-use camera variant 6: picks shot 0-3 at random on substep 0 and runs it.
 */
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

/**
 * Move-use camera variant 7: picks shot 0, 1, 2 or 4 at random on substep 0 and runs it.
 */
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
/**
 * Use-move step variant 10 (BattleScene_ActionStepUseMove): the multi-hit loop. Each hit replays
 * the camera shot, enters the repeat-hit row (0x13) on the target and counts D_8219A570 down; it
 * stops early when the target faints (D_82199F31).
 * Player sweep: reached only by the ten multi-hit moves (Double Slap, Comet Punch, Double Kick,
 * Fury Attack, Twineedle, Pin Missile, Spike Cannon, Barrage, Fury Swipes, Bonemerang).
 */
void BattleScene_UseMoveStepMultiHit(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 4;
            func_821255B4((s8*)arg0);
            BattleCamera_PlayShot(sActingPokemon, arg0, D_8219A570);
            BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
            func_82125580();
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, sActingPokemon);
            if (func_821058E8(sActingPokemon, 0x32) != 0) {
                func_821255B4((s8*)arg0);
                func_8211EE8C();
                BattleCamera_PlayShot(sActingPokemon, arg0, D_8219A570 - 1);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                if (--D_8219A570 < 0 || D_82199F31 != 0) {
                    func_82125580();
                    do {  // FAKE
                        D_8219A570 = D_8219A56C;
                        sBattleScene.scene->phaseSubstep++;
                    } while (0);
                } else {
                    func_82104C68(((ActivePokemon**)&D_82199DE0)[sBattleScene.scene->actingSide], 0x13);
                    Audio_FadeAndClearStoredSounds();
                    func_8213B31C(1);
                    sBattleScene.scene->phaseSubstep = 1;
                }
            }
            break;
        case 2:
            sBattleScene.scene->cameraPresetId = 4;
            func_821228B0(arg0, sActingPokemon);
            if (func_821217DC(0x28) != 0) {
                sBattleScene.scene->cameraPresetId = 0;
                func_8212188C();
                func_82125570();
                sBattleScene.scene->moveEffectKind = 0;
                Audio_FadeAndClearStoredSounds();
                sBattleScene.scene->phaseStep++;
            }
            break;
    }
}

/**
 * Use-move step variant 11 (BattleScene_ActionStepUseMove), the confusion self-hit: shows message
 * +0x148 for the acting side, plays camera shot 3 and queues effect list 7 on the actor, then
 * waits for its cue.
 * Seen in play: with the COM's Pinsir (カイのすけ) confused, it showed 「わけも わからず じぶんを こうげきした！」 with
 * the red ?! marks over its head. It also ran in the sweeps after Supersonic, Confuse Ray and
 * Psybeam's confusion side effect.
 */
void BattleScene_UseMoveStepConfusionSelfHit(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                sBattleScene.scene->cameraPresetId = 4;
                BattleScene_SetPhaseFlag();
                Battle_ClearMessageCursor();
                BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                BattleCamera_PlayShot(sActingPokemon, arg0, 3);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                BattleScene_ResetCameraSubstepCounter();
                BattleAnim_QueueEffectList(7, sActingPokemon);
            }
            break;
        case 1:
            func_821228B0(arg0, sActingPokemon);
            if (BattleScene_AdvanceCameraSubstepCounter(0x28) != 0) {
                Battle_ClearMessageCursor();
            }
            if (func_82105724(sActingPokemon, 0x1E) != 0) {
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

/**
 * Step 2 of an action phase: runs the move-use camera variant (table column 2 of D_80073D84; 10
 * for multi-hit moves, 11 for the confusion self-hit).
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran at phase 2,
 * step 2, as the move-use shot began.
 */
void BattleScene_ActionStepUseMove(CameraNode* arg0, s32 arg1) {
    s32 temp = sBattleScene.scene->moveEffectKind;

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
            BattleScene_UseMoveStepMultiHit(arg0);
            break;
        case 11:
            BattleScene_UseMoveStepConfusionSelfHit(arg0);
            break;
        default:
            func_82128FBC(arg0);
            break;
    }
}

/**
 * Camera step for an action: on substep 0 clears old effects and offsets and aims the camera
 * at the acting Pokemon; on substep 1 tracks it until the camera settles, then ends the
 * target's effect mode and advances the phase step.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (24 of the moves).
 * @unverified Name guessed from the code.
 */
void BattleScene_ActionSetupAnimationVariantB(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            sBattleScene.scene->cameraPresetId = 2;
            BattleAnim_CleanupEffects(1);
            BattleScene_ClearCameraOffsetVectors();
            BattleScene_SetPhaseFlag();
            func_82124284((s32)arg0, sOtherPokemon, 0.0f);
            break;

        case 1:
            func_821243DC((s32)arg0, sOtherPokemon, 0.0f);
            if (sBattleScene.scene->orbitDistance <= 1.0f) {
                BattleScene_CleanupParticipantEffectMode(sActingPokemon);
                sBattleScene.scene->phaseStep++;
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
            }
            break;
    }
}

/**
 * Impact camera variant 1: clears old effects and offsets and aims at the target two
 * heights above it; once the target's effect session is idle, tracks it until the camera
 * settles, ends the user's effect mode and advances the phase step.
 */
void func_82129D10(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            BattleScene_ClearCameraOffsetVectors();
            BattleScene_SetPhaseFlag();
            func_82124284((s32)arg0, sOtherPokemon, BattleScene_GetParticipantHeight(sOtherPokemon) * 2.0f);
            break;
        case 1:
            if (BattleAnim_IsSessionBusy(sOtherPokemon) == 0) {
                func_821243DC((s32)arg0, sOtherPokemon, BattleScene_GetParticipantHeight(sOtherPokemon) * 2.0f);
                if (sBattleScene.scene->orbitDistance <= 1.0f) {
                    BattleScene_CleanupParticipantEffectMode(sActingPokemon);
                    sBattleScene.scene->phaseStep++;
                    BattleScene_ClearPhaseFlag();
                    BattleScene_ResetCameraFrameCounter();
                }
            }
            break;
    }
}

/**
 * Impact camera variant 2: like variant 1 but aimed below the target (by D_FLT_821963A0
 * heights) with camera preset 2.
 */
void func_82129E30(s32 arg0) {
    s32 temp_v0;

    sBattleScene.scene->cameraPresetId = 2;
    temp_v0 = sBattleScene.scene->phaseSubstep;
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8213B31C(1);
        func_821224F4();
        func_82125580();
        func_82124284(arg0, sOtherPokemon, -BattleScene_GetParticipantHeight(sOtherPokemon) * D_FLT_821963A0);
        return;
    case 1:
        func_821243DC(arg0, sOtherPokemon, -BattleScene_GetParticipantHeight(sOtherPokemon) * D_FLT_821963A4);
        if (sBattleScene.scene->orbitDistance <= 1.0f) {
            func_82106374(sActingPokemon);
            func_82125570();
            func_8212188C();
            sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
        }
        return;
    }
}

/**
 * Impact camera variant 3: orbits the target (func_82124544 with 8, 6, 2.5, 6 and angle 0)
 * until the zoom is close to the stored distance, then advances the phase step.
 */
void func_82129F5C(CameraNode* arg0) {
    s32 temp_v0;

    sBattleScene.scene->cameraPresetId = 2;
    temp_v0 = sBattleScene.scene->phaseSubstep;
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8213B31C(1);
        func_821224F4();
        func_82125580();
        func_82124544((s32)arg0, sOtherPokemon, 8.0f, 6.0f, 2.5f, 6.0f, 0);
        return;
    case 1:
        func_82124664((s32)arg0, sOtherPokemon, 0);
        if (sBattleScene.scene->orbitDistance < (sBattleScene.scene->distance + D_FLT_821963A8)) {
            func_82106374(sActingPokemon);
            sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
            func_82125570();
            func_8212188C();
        }
        return;
    }
}

/**
 * Impact camera variant 4: orbit like variant 3 with wider settings (10, 12, 3.5, 6) at
 * angle 0x11C6.
 */
void func_8212A074(s32 arg0) {
    s32 temp_v0;

    sBattleScene.scene->cameraPresetId = 2;
    temp_v0 = sBattleScene.scene->phaseSubstep;
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8213B31C(1);
        func_821224F4();
        func_82125580();
        func_82124544(arg0, sOtherPokemon, 10.0f, 12.0f, 3.5f, 6.0f, 0x11C6);
        return;
    case 1:
        func_82124664(arg0, sOtherPokemon, 0x11C6);
        if (sBattleScene.scene->orbitDistance <= (sBattleScene.scene->distance + 1.0f)) {
            func_82106374(sActingPokemon);
            sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
            func_82125570();
            func_8212188C();
        }
        return;
    }
}

/**
 * Impact camera variant 5: picks variant 0, 1 or 2 at random on substep 0 and runs it.
 */
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

/**
 * Impact camera variant 7: picks variant 0-3 at random on substep 0 and runs it.
 */
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
