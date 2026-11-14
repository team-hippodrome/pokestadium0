/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK func_82108C0C(s32);
M2C_UNK func_8212189C();
M2C_UNK func_82124A40();
M2C_UNK func_82125AC8(s32);
s32 Battle_StepPartyHpToDisplay(s32);
s32 BattleScene_FrameParticipantFromAboveThunk(void*, void*);
void BattleMessage_ShowForSide(s32, s32);
void BattleScene_CameraShotTargetHighThunk(void*, void*);
void BattleScene_RestoreUserAfterTravel(s32);
void func_8211EE8C(void);
void func_8212188C(void);
void BattleScene_FrameParticipantFromBelowClamped(void*, void*);
void BattleScene_FrameParticipantFrontAltThunk(void*, void*);
void BattleSound_UpdateSideHp(ActivePokemon*);

/**
 * Step 3 of an action phase: waits for the user's animation, enters the miss or status phase when
 * one is pending (BattleScene_TryEnterEffectPhaseBeforeImpact), otherwise runs the travel camera
 * variant (table column 3 of D_80073D84).
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran at phase 2,
 * step 3.
 */
void BattleScene_ActionStepTravel(CameraNode* arg0, s32 arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    BattleMonRuntime* runtime = &(sOtherPokemon)->state.runtime;

    if (BattleScene_AdvanceOwnerAnimation98(sOtherPokemon) != 0) {
        return;
    }
    BattleScene_RestoreUserAfterTravel(sActingPokemon);
    if (6 == D_80073D90[runtime->usedMove - 1].travelCameraShot) {
        arg1 = D_8219A568;
    }
    if ((arg1 != 5) && (arg1 != 6) && (arg1 != 7)) {
        D_8219A568 = arg1;
    }
    if (BattleScene_TryEnterEffectPhaseBeforeImpact() != 0) {
        return;
    }
    BattleScene_ResetCameraFovTo30(arg0);
    switch (arg1) {
        case 0:
            BattleScene_ActionSetupAnimationVariantB(arg0);
            break;
        case 1:
            BattleScene_ImpactCameraAbove(arg0);
            break;
        case 2:
            BattleScene_ImpactCameraBelow((s32)arg0);
            break;
        case 3:
            BattleScene_ImpactCameraOrbit(arg0);
            break;
        case 4:
            BattleScene_ImpactCameraWideOrbit((s32)arg0);
            break;
        case 5:
            BattleScene_ImpactCameraRandom3(arg0);
            break;
        case 7:
            BattleScene_ImpactCameraRandom4(arg0);
            break;
        default:
            BattleScene_ActionSetupAnimationVariantB(arg0);
            break;
    }
}


/**
 * Sets D_8219A578 to whether byte 1 of arg0 is nonzero.
 * @unverified Name guessed from the code.
 */
void BattleScene_SetReactionFlagFromByte1(s8 *arg0) {
    D_8219A578 = 0;
    if (M2C_FIELD(arg0, s8 *, 1) != 0) {
        D_8219A578 = 1;
    }
}

/**
 * When both HP displays have caught up (*arg1 and *arg2 are 1) and 30 frames have passed,
 * ends the user's effect mode, clears the camera and message state and runs the HP bar step.
 * @unverified Name guessed from the code.
 */
void BattleScene_FinishReactionWhenHpSettled(s32 step, s32 *user_hp_done, s32 *target_hp_done) {
    if ((*user_hp_done == 1) && (*target_hp_done == 1) && (func_82121820(0x1E) != 0)) {
        func_82108C0C(sActingPokemon);
        sBattleScene.scene->hitReactionKind = 0;
        func_8212188C();
        func_8212189C();
        func_8211EE8C();
        func_82125570();
        func_82124A40();
        func_82125AC8(step);
    }
}

s32 func_8210C020(s32);
/**
 * Stores the camera shot index: 4 picks one at random (func_8210C020(3)), 5 keeps the last
 * one, any other value is stored as is.
 * @unverified Name guessed from the code.
 */
void BattleCamera_StoreShotIndex(s32 shot) {
    s32 temp_v0;

    if (shot == 4) {
        temp_v0 = func_8210C020(3);
        D_8219A568 = temp_v0;
        if (temp_v0 >= 4) {
            D_8219A568 = 0;
        }
    } else if (shot != 5) {
        D_8219A568 = shot;
    }
}

/**
 * Target framing chooser: picks one of three framings at random on substep 0 and runs it.
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayRandomReactionFraming3(ActivePokemon* active_pokemon, CameraNode* camera) {
    if (sBattleScene.scene->phaseSubstep == 0) {
        D_8219A568 = BattleAnim_RandomRange(3);
        if (D_8219A568 >= 3) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
        case 0:
            BattleScene_CameraShotTargetHighThunk(camera, active_pokemon);
            break;
        case 1:
            BattleScene_FrameParticipantFromAboveThunk(camera, active_pokemon);
            break;
        case 2:
            BattleScene_FrameParticipantFromBelowClamped(camera, active_pokemon);
            break;
        default:
            BattleScene_FrameParticipantFrontAltThunk(camera, active_pokemon);
            break;
    }
}

/**
 * Target framing chooser: picks one of four framings at random on substep 0 and runs it.
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayRandomReactionFraming4(ActivePokemon* active_pokemon, CameraNode* camera) {
    if (sBattleScene.scene->phaseSubstep == 0) {
        D_8219A568 = BattleAnim_RandomRange(4);
        if (D_8219A568 >= 4) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
        case 0:
            BattleScene_CameraShotTargetHighThunk(camera, active_pokemon);
            break;
        case 1:
            BattleScene_FrameParticipantFromAboveThunk(camera, active_pokemon);
            break;
        case 2:
            BattleScene_FrameParticipantFromBelowClamped(camera, active_pokemon);
            break;
        case 3:
            BattleScene_FrameParticipantFrontAltThunk(camera, active_pokemon);
            break;
        default:
            BattleScene_FrameParticipantFrontAltThunk(camera, active_pokemon);
            break;
    }
}

/**
 * Runs target framing arg2: 4 and 6 choose at random (3 or 4 choices), 5 reuses the last
 * one, 0-3 run that framing.
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayReactionFraming(ActivePokemon* active_pokemon, CameraNode* camera, s32 arg2) {
    if (arg2 == 4) {
        BattleCamera_PlayRandomReactionFraming3(active_pokemon, camera);
    } else if (arg2 == 6) {
        BattleCamera_PlayRandomReactionFraming4(active_pokemon, camera);
    } else {
        if (arg2 == 5) {
            arg2 = D_8219A568;
        }
        switch (arg2) {
            case 0:
                BattleScene_CameraShotTargetHighThunk(camera, active_pokemon);
                break;
            case 1:
                BattleScene_FrameParticipantFromAboveThunk(camera, active_pokemon);
                break;
            case 2:
                BattleScene_FrameParticipantFromBelowClamped(camera, active_pokemon);
                break;
            case 3:
                BattleScene_FrameParticipantFrontAltThunk(camera, active_pokemon);
                break;
            default:
                BattleScene_FrameParticipantFrontAltThunk(camera, active_pokemon);
                break;
        }
    }
}


/**
 * Step 4 reaction for an ordinary hit (hitReactionKind 0). Ran in play for every damaging move
 * that hit.
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran from step 4
 * with hitReactionKind 0 for the ordinary hit on Pinsir.
 */
void BattleScene_ReactionNormal(CameraNode* arg0, s32 arg1) {
    BattleMonRuntime* sp1C = &(sOtherPokemon)->state.runtime;

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            BattleCamera_StoreShotIndex(arg1);
            func_82124A40();
            BattleScene_ResetCameraFrameCounter();
            func_82125580();
            BattleScene_SetDamageShakeAmplitude(sOtherPokemon);
            BattleScene_SetReactionFlagFromByte1((s8*)((s32)gBattleMessageQueues->messageBuffers[6]));
            BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
            BattleScene_EnterStateRow(sActingPokemon, 4);
            BattleCamera_PlayReactionFraming(sOtherPokemon, arg0, arg1);
            BattleCamera_CaptureModelOrbit(sOtherPokemon, arg0);
            ActivePokemon_CommitPendingStatus(sOtherPokemon);
            BattleSound_UpdateSideHp(sOtherPokemon);
            func_821061A8(sOtherPokemon);
            break;

        case 1:
            BattleScene_UseCameraPreset1AndIdleUser();
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (D_8219A578 == 0) {
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->phaseSubstep++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[6], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 2:
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (sp1C->hp != 0) {
                if (BattleScene_IsRowAnimWaitComplete(sOtherPokemon, 0xF) != 0) {
                    sBattleScene.scene->phaseSubstep++;
                }
                if (BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) {
                    sBattleScene.scene->phaseSubstep = 4;
                }
            } else if ((BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) && (func_82121820(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseSubstep = 5;
            }
            break;

        case 3:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) {
                sBattleScene.scene->phaseSubstep = 5;
            }
            break;

        case 4:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (BattleScene_IsRowAnimWaitComplete(sOtherPokemon, 0xF) != 0) {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 5:
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (*(s8*)((s32)&gBattleMessageQueues->messageBuffers[13][1]) == 0) {
                sBattleScene.scene->phaseSubstep = 7;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[13], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 6:
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->phaseSubstep++;
                Battle_ClearMessageCursor();
            }
            break;

        case 7:
            if (BattleScene_ReloadModelForFlag1000(sOtherPokemon) == 0) {
                D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
                D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
                BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
                BattleScene_FinishReactionWhenHpSettled((s32)arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}


/**
 * Step 4 reaction for a critical hit or one-hit KO (hitReactionKind 2, set by
 * Battle_PrintCriticalOHKOText).
 * In the per-move sweep (moves 1-33) only Karate Chop and Slash ran it, the two high critical-hit
 * moves.
 */
void BattleScene_ReactionCritical(CameraNode* arg0, s32 arg1) {
    BattleMonRuntime* sp1C = &(sOtherPokemon)->state.runtime;

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            BattleCamera_StoreShotIndex(arg1);
            func_82124A40();
            BattleScene_ResetCameraFrameCounter();
            func_82125580();
            BattleScene_SetDamageShakeAmplitude(sOtherPokemon);
            BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], sBattleScene.scene->actingSide);
            BattleScene_EnterStateRow(sActingPokemon, 4);
            BattleCamera_PlayReactionFraming(sOtherPokemon, arg0, arg1);
            BattleCamera_CaptureModelOrbit(sOtherPokemon, arg0);
            ActivePokemon_CommitPendingStatus(sOtherPokemon);
            func_821061A8(sOtherPokemon);
            BattleSound_UpdateSideHp(sOtherPokemon);
            break;

        case 1:
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_UseCameraPreset1AndIdleUser();
                BattleScene_SetReactionFlagFromByte1((s8*)((s32)gBattleMessageQueues->messageBuffers[0]));
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 2:
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (D_8219A578 == 0) {
                BattleScene_ResetCameraSubstepCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[6], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[6], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 3:
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (sp1C->hp != 0) {
                if (BattleScene_IsRowAnimWaitComplete(sOtherPokemon, 0xF) != 0) {
                    sBattleScene.scene->phaseSubstep++;
                }
                if (BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) {
                    sBattleScene.scene->phaseSubstep = 5;
                }
            } else if ((BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) && (func_82121820(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseSubstep = 6;
            }
            break;

        case 4:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) {
                sBattleScene.scene->phaseSubstep = 6;
            }
            break;

        case 5:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_IsRowAnimWaitComplete(sOtherPokemon, 0xF) != 0) {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 6:
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (*(s8*)((s32)&gBattleMessageQueues->messageBuffers[13][1]) == 0) {
                sBattleScene.scene->phaseSubstep = 8;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[13], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 7:
            D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->phaseSubstep++;
                Battle_ClearMessageCursor();
            }
            break;

        case 8:
            if (BattleScene_ReloadModelForFlag1000(sOtherPokemon) == 0) {
                D_8219A560 = Battle_StepPartyHpToDisplay((s32)sOtherPokemon);
                D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
                BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
                BattleScene_FinishReactionWhenHpSettled((s32)arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}
