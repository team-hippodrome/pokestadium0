/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "audio_commands.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK func_8211EE8C();
M2C_UNK BattleScene_BeginCameraReturnTransition();
extern f32 D_FLT_82189354[][4];
extern u8* D_82189180[];
s32 Battle_StepPartyHpToDisplay(ActivePokemon*);
s32 func_82107A5C(ActivePokemon*);
s32 func_82107CA0(ActivePokemon*);
s32 func_8210C020(M2C_UNK, s32);
s32 BattleScene_FrameParticipantFromAboveThunk(void*, void*);
void ActivePokemon_SetStateFlags(ActivePokemon*, s32);
void Audio_PlayMoveSound(s32, s32, s32);
void BattleCamera_PlayShot(s32, s32, s32);
void BattleMessage_ShowForSide(s32, s32);
void BattleScene_CameraShotTargetHighThunk(void*, void*);
void BattleScene_ReactionCritical(CameraNode*, void*);
void BattleScene_ReactionNormal(CameraNode*, void*);
void BattleAnim_SwapToSubstituteModel(ActivePokemon*);
void func_82104C68(ActivePokemon*, s32);
void BattleScene_ResidualPhaseNop(ActivePokemon*);
void func_82106374(ActivePokemon*);
void func_82107408(ActivePokemon*);
void func_82108C0C(ActivePokemon*);
void func_821224F4();
void BattleScene_EaseCameraToFrontView(CameraNode*, ActivePokemon*, f32);
void BattleScene_FrameParticipantFromBelowClamped(void*, void*);
void BattleScene_FrameParticipantFrontAltThunk(void*, void*);
void func_82124A40(void);
void func_82125AC8(CameraNode*);
void BattleScene_StepPartyHpAndUpdateHpBar(CameraNode*);
void BattleScene_UpdateHpBarWhenHpSettled(CameraNode*);
void BattleScene_SetReactionFlagFromByte1(s32);
void BattleScene_FinishReactionWhenHpSettled(CameraNode*, s32*, s32*);
void BattleCamera_StoreShotIndex(void*);
void BattleCamera_PlayReactionFraming(ActivePokemon*, CameraNode*, void*);
void BattleSound_UpdateSideHp(ActivePokemon*);

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

/**
 * Empty render hook.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_RenderNop1(void) {
}

/**
 * Empty render hook.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_RenderNop2(void) {
}


/**
 * Step 4 reaction after the last hit of a multi-hit move, when the hit count message shows
 * (hitReactionKind 1, set in ProcessBattleTurn).
 * In the per-move sweep (moves 1-33) only Double Slap, Comet Punch and Double Kick ran it.
 */
void BattleScene_ReactionMultiHitEnd(CameraNode* arg0, void* arg1) {
    BattleMonRuntime* sp24 = &(sActingPokemon)->state.runtime;
    MovePresentationCue* temp_v1 = (sp24->usedMove - 1) + (MovePresentationCue*)D_82189180[func_82107A5C(sOtherPokemon)];
    volatile s32 sp1C;

    if (sOtherPokemon->displayObject.objectType == 0x98) {
        sp1C = 0xF;
    } else if (temp_v1->frameCounter == 0xFF) {
        sp1C = M2C_FIELD((sActingPokemon)->displayObject.transformAnim.data, u16*, 0xA) - temp_v1->currentFrame;
    } else {
        sp1C = temp_v1->frameCounter - temp_v1->currentFrame;
    }

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            BattleCamera_StoreShotIndex(arg1);
            func_82124A40();
            func_82121EB0(sOtherPokemon);
            func_82104C68(sActingPokemon, 4);
            BattleCamera_PlayReactionFraming(sOtherPokemon, arg0, (void*)D_8219A570);
            D_8219A570--;
            if (D_8219A570 < 0) {
                BattleScene_UseCameraPreset1AndIdleUser();
                BattleSound_UpdateSideHp(sOtherPokemon);
                BattleCamera_PlayReactionFraming(sOtherPokemon, arg0, (void*)D_8219A570);
                BattleCamera_CaptureModelOrbit(sOtherPokemon, arg0);
                BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
                ActivePokemon_CommitPendingStatus(sOtherPokemon);
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseSubstep = 2;
                D_8219A578 = 0;
                BattleScene_SetReactionFlagFromByte1((s32)gBattleMessageQueues->messageBuffers[3]);
                if (gBattleMessageQueues->messageBuffers[3][1] != 0) {
                    D_8219A578 = 1;
                }
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], sBattleScene.scene->actingSide);
                func_821061A8(sOtherPokemon);
            } else {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(sp1C) != 0) {
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                sBattleScene.scene->phaseSubstep = 0;
            }
            break;

        case 2:
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[10], sBattleScene.scene->actingSide);
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
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (D_8219A578 == 0) {
                BattleScene_SetReactionFlagFromByte1((s32)gBattleMessageQueues->messageBuffers[0]);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_SetReactionFlagFromByte1((s32)gBattleMessageQueues->messageBuffers[0]);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 5:
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (D_8219A578 == 0) {
                BattleScene_ResetCameraSubstepCounter();
                BattleScene_SetReactionFlagFromByte1((s32)gBattleMessageQueues->messageBuffers[6]);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[6], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                BattleScene_SetReactionFlagFromByte1((s32)gBattleMessageQueues->messageBuffers[6]);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[6], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 6:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (sp24->hp != 0) {
                if (func_82105C8C(sOtherPokemon, 0xF) != 0) {
                    sBattleScene.scene->phaseSubstep++;
                }
                if (BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) {
                    sBattleScene.scene->phaseSubstep = 8;
                }
            } else if ((BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) && (BattleScene_AdvanceCameraFrameCounterUntil(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseSubstep = 9;
            }
            break;

        case 7:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) {
                sBattleScene.scene->phaseSubstep = 9;
            }
            break;

        case 8:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (func_82105C8C(sOtherPokemon, 0xF) != 0) {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 9:
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (gBattleMessageQueues->messageBuffers[13][1] == 0) {
                sBattleScene.scene->phaseSubstep = 0xB;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[13], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 10:
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->phaseSubstep++;
                Battle_ClearMessageCursor();
            }
            break;

        case 11:
            if (BattleScene_ReloadModelForFlag1000(sOtherPokemon) == 0) {
                D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
                D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
                BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
                BattleScene_FinishReactionWhenHpSettled(arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}


/**
 * Step 4 reaction when the hit also lowered a stat or confused the target (hitReactionKind 3, set
 * by Battle_Effect_LowerStat and Battle_Effect_ConfuseChance).
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name from BattleScene_ActionStepReaction's dispatch.
 */
void BattleScene_ReactionSideEffect(CameraNode* arg0, void* arg1) {

    BattleMonRuntime* sp1C = &(sOtherPokemon)->state.runtime;

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            BattleSound_UpdateSideHp(sOtherPokemon);
            BattleCamera_StoreShotIndex(arg1);
            func_82124A40();
            BattleScene_ResetCameraFrameCounter();
            ActivePokemon_CommitPendingStatus(sOtherPokemon);
            BattleScene_SetReactionFlagFromByte1((s32)gBattleMessageQueues->messageBuffers[3]);
            BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], sBattleScene.scene->actingSide);
            BattleCamera_PlayReactionFraming(sOtherPokemon, arg0, arg1);
            BattleCamera_CaptureModelOrbit(sOtherPokemon, arg0);
            func_82104C68(sActingPokemon, 0xB);
            sBattleScene.scene->phaseSubstep++;
            break;

        case 1:
            BattleScene_UseCameraPreset1AndIdleUser();
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 2:
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[6], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 3:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (sp1C->hp != 0) {
                if (func_82105C8C(sOtherPokemon, 0xF) != 0) {
                    sBattleScene.scene->phaseSubstep++;
                }
                if (BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) {
                    sBattleScene.scene->phaseSubstep = 5;
                }
            } else if ((BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) && (BattleScene_AdvanceCameraFrameCounterUntil(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseSubstep = 6;
            }
            break;

        case 4:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_FrameReactingParticipant(arg0, sOtherPokemon) != 0) {
                sBattleScene.scene->phaseSubstep = 6;
            }
            break;

        case 5:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (func_82105C8C(sOtherPokemon, 0xF) != 0) {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 6:
            if (gBattleMessageQueues->messageBuffers[13][1] == 0) {
                sBattleScene.scene->phaseSubstep = 8;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
                D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[13], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 7:
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->phaseSubstep++;
                Battle_ClearMessageCursor();
            }
            break;

        case 8:
            if (BattleScene_ReloadModelForFlag1000(sOtherPokemon) == 0) {
                D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
                D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
                BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
                BattleScene_FinishReactionWhenHpSettled(arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}


/**
 * Step 4 of an action phase: commits the target's pending status and runs the target reaction for
 * hitReactionKind (0 normal, 1 last hit of a multi-hit move, 2 critical hit or OHKO, 3 side
 * effect).
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran at phase 2,
 * step 4, with hitReactionKind 0, and called BattleScene_ReactionNormal.
 */
void BattleScene_ActionStepReaction(CameraNode* arg0, void* arg1) {
    s32 other;

    BattleScene_ResetCameraFovTo30(arg0);
    sBattleScene.scene->cameraPresetId = 2;
    other = sBattleScene.scene->actingSide == 0;
    ActivePokemon_CommitPendingStatus(sActivePokemon[other]);
    if (sBattleScene.scene->hitReactionKind == 3) {
        BattleScene_ReactionSideEffect(arg0, arg1);
    } else if (sBattleScene.scene->hitReactionKind == 1) {
        BattleScene_ReactionMultiHitEnd(arg0, arg1);
    } else if (sBattleScene.scene->hitReactionKind == 2) {
        BattleScene_ReactionCritical(arg0, arg1);
    } else {
        BattleScene_ReactionNormal(arg0, arg1);
    }
}


/**
 * Phase 2: the first action of the turn. Steps 0-4 run the move's presentation script (user
 * intro, hit count, launch, travel, target reaction) from the per-move table at D_80073D84, and
 * may hand over to an effect phase such as 7 or 8. In play, 1P's Thunderbolt ran here when 1P
 * moved first; when COM moved first this phase handed straight over to 7 for its Double Team.
 */
void BattleScene_PhaseFirstAction(CameraNode* arg0) {
    s32 n = 10;
    BattleMonRuntime* sp = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;

    if (sBattleScene.scene->mode == n) {
        switch (sBattleScene.scene->phaseStep) {
            case 0:
                BattleScene_ActionStepIntro(arg0, D_8218B2F4[D_8219A4F4][0]);
                break;
            case 1:
                BattleScene_ActionStepSetHitCount(arg0, 0);
                break;
            case 2:
                BattleScene_ActionStepUseMove(arg0, D_8218B2F4[D_8219A4F4][1]);
                break;
            case 3:
                BattleScene_ActionStepTravel(arg0, D_8218B2F4[D_8219A4F4][2]);
                break;
            case 4:
                BattleScene_ActionStepReaction(arg0, (void*)D_8218B2F4[D_8219A4F4][3]);
                break;
        }
    } else {
        switch (sBattleScene.scene->phaseStep) {
            case 0:
                BattleScene_ActionStepIntro(arg0, *(u16*)(D_80073D84 + 2 + sp->usedMove * n));
                break;
            case 1:
                BattleScene_ActionStepSetHitCount(arg0, 0);
                break;
            case 2:
                BattleScene_ActionStepUseMove(arg0, *(u16*)(D_80073D84 + 4 + sp->usedMove * n));
                break;
            case 3:
                BattleScene_ActionStepTravel(arg0, *(u16*)(D_80073D84 + 6 + sp->usedMove * n));
                break;
            case 4:
                BattleScene_ActionStepReaction(arg0, (void*)*(u16*)(D_80073D84 + 8 + sp->usedMove * n));
                break;
        }
    }
}


/**
 * Phase 3: the second action of the turn, with the same steps as BattleScene_PhaseFirstAction.
 * In play, 1P's Thunderbolt ran here when COM moved first.
 */
void BattleScene_PhaseSecondAction(CameraNode* arg0) {
    s32 n = 10;
    BattleMonRuntime* sp = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;

    if (sBattleScene.scene->mode == n) {
        switch (sBattleScene.scene->phaseStep) {
            case 0:
                BattleScene_ActionStepIntro(arg0, D_8218B320[D_8219A4F4][0]);
                break;
            case 1:
                BattleScene_ActionStepSetHitCount(arg0, 0);
                break;
            case 2:
                BattleScene_ActionStepUseMove(arg0, D_8218B320[D_8219A4F4][1]);
                break;
            case 3:
                BattleScene_ActionStepTravel(arg0, D_8218B320[D_8219A4F4][2]);
                break;
            case 4:
                BattleScene_ActionStepReaction(arg0, (void*)D_8218B320[D_8219A4F4][3]);
                break;
        }
    } else {
        switch (sBattleScene.scene->phaseStep) {
            case 0:
                BattleScene_ActionStepIntro(arg0, *(u16*)(D_80073D84 + 2 + sp->usedMove * n));
                break;
            case 1:
                BattleScene_ActionStepSetHitCount(arg0, 0);
                break;
            case 2:
                BattleScene_ActionStepUseMove(arg0, *(u16*)(D_80073D84 + 4 + sp->usedMove * n));
                break;
            case 3:
                BattleScene_ActionStepTravel(arg0, *(u16*)(D_80073D84 + 6 + sp->usedMove * n));
                break;
            case 4:
                BattleScene_ActionStepReaction(arg0, (void*)*(u16*)(D_80073D84 + 8 + sp->usedMove * n));
                break;
        }
    }
}


/**
 * Plays one of the user's camera shots 0-2, picked at random (the pick is kept in D_8219A568).
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayRandomUserShot3(s32 camera)
{
  s32 temp_v0;
  s32 var_v1;
 temp_v0 = func_8210C020(3, camera); D_8219A568 = temp_v0; var_v1 = temp_v0; if (temp_v0 >= 4) { D_8219A568 = 0; var_v1 = 0; } switch (var_v1) { case 0: // FAKE: no-op ^ 0
      BattleCamera_PlayShot(sActingPokemon, camera, 0);
      return;

    case 1:
      BattleCamera_PlayShot(sActingPokemon, camera, 1);
      return;

    case 2:
      BattleCamera_PlayShot(sActingPokemon, camera, 2);
      return;

    default:
      BattleCamera_PlayShot(sActingPokemon, camera, 0);
      return;

  }

}

/**
 * Plays one of the user's camera shots 0-3, picked at random (the pick is kept in D_8219A568).
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayRandomUserShot4(s32 camera)
{
  s32 temp_v0;
  s32 var_v1;
 temp_v0 = func_8210C020(4, camera); D_8219A568 = temp_v0;
  var_v1 = temp_v0;
  if (temp_v0 >= 5)
  {
    D_8219A568 = 0;
    var_v1 = 0;
  }
  switch (var_v1)
  {
    case 0:
      BattleCamera_PlayShot(sActingPokemon, camera, 0);
      return;

    case 1:
      BattleCamera_PlayShot(sActingPokemon, camera, 1);
      return;

    case 2:
      BattleCamera_PlayShot(sActingPokemon, camera, 2);
      return;

    case 3:
      BattleCamera_PlayShot(sActingPokemon, camera, 3);
      return;

    default:
      BattleCamera_PlayShot(sActingPokemon, camera, 0);
      return;

  }

}

/**
 * Plays one of the user's camera shots 0, 1, 2 or 4, picked at random (the pick is kept in
 * D_8219A568).
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayRandomUserShotWith4(s32 camera)
{
  s32 temp_v0;
  s32 var_v1;
  temp_v0 = func_8210C020(4, camera); D_8219A568 = temp_v0; var_v1 = temp_v0; // IDO: these statements must share one source line
  if (temp_v0 >= 5)
  {
    D_8219A568 = 0;
    var_v1 = 0;
  }
  switch (var_v1)
  {
    case 0:
      BattleCamera_PlayShot(sActingPokemon, camera, 0);
      return;

    case 1:
      BattleCamera_PlayShot(sActingPokemon, camera, 1);
      return;

    case 2:
      BattleCamera_PlayShot(sActingPokemon, camera, 2);
      return;

    case 3:
      BattleCamera_PlayShot(sActingPokemon, camera, 4);
      return;

    default:
      BattleCamera_PlayShot(sActingPokemon, camera, 0);
      return;

  }

}


/**
 * Plays BattleCamera_PlayShot variant 0-4 on the acting Pokemon.
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name from the code.
 */
void BattleCamera_PlayUserShot(s32 arg0, s32 arg1) {
    switch (arg1) {
        case 0:
            BattleCamera_PlayShot(sActingPokemon, arg0, 0);
            break;
        case 1:
            BattleCamera_PlayShot(sActingPokemon, arg0, 1);
            break;
        case 2:
            BattleCamera_PlayShot(sActingPokemon, arg0, 2);
            break;
        case 3:
            BattleCamera_PlayShot(sActingPokemon, arg0, 3);
            break;
        case 4:
            BattleCamera_PlayShot(sActingPokemon, arg0, 4);
            break;
        default:
            BattleCamera_PlayShot(sActingPokemon, arg0, 0);
            break;
    }
}


/**
 * Plays one of four camera shots on the target (variant 0-3, from the move table or random).
 * Phase 8 uses it with a random variant for the dodge.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle.
 * @unverified Name from the code.
 */
void BattleCamera_PlayTargetShot(ActivePokemon* arg0, CameraNode* arg1, s32 arg2) {
    switch (arg2) {
        case 0:
            BattleScene_CameraShotTargetHighThunk(arg1, arg0);
            break;
        case 1:
            BattleScene_FrameParticipantFromAboveThunk(arg1, arg0);
            break;
        case 2:
            BattleScene_FrameParticipantFromBelowClamped(arg1, arg0);
            break;
        case 3:
            BattleScene_FrameParticipantFrontAltThunk(arg1, arg0);
            break;
        default:
            BattleScene_FrameParticipantFrontAltThunk(arg1, arg0);
            break;
    }
}

/**
 * Plays the user's camera shot for its move from the move table D_80073D90 (field 2). Shots
 * 5, 6 and 7 use their own setups, and shot 4 also sets scene+0x54.
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayMoveUserShot(s32 camera) {
    BattleMonRuntime* runtime;

    runtime = &(sActingPokemon)->state.runtime;
    sBattleScene.scene->easeFovAfterUserShot = 0;
    if (D_80073D90[runtime->usedMove - 1].userCameraShot == 5) {
        BattleCamera_PlayRandomUserShot3(camera);
    } else if (D_80073D90[runtime->usedMove - 1].userCameraShot == 6) {
        BattleCamera_PlayRandomUserShot4(camera);
    } else if (D_80073D90[runtime->usedMove - 1].userCameraShot == 7) {
        BattleCamera_PlayRandomUserShotWith4(camera);
    } else if (D_80073D90[runtime->usedMove - 1].userCameraShot == 4) {
        sBattleScene.scene->easeFovAfterUserShot = 1;
        BattleCamera_PlayUserShot(camera, D_80073D90[runtime->usedMove - 1].userCameraShot);
    } else {
        BattleCamera_PlayUserShot(camera, D_80073D90[runtime->usedMove - 1].userCameraShot);
    }
}

/**
 * Phase 7: presentation for moves that act on the user (moveEffectKind 7, set by
 * Battle_Effect_StatUp, Focus Energy, Mist, Reflect/Light Screen, Conversion, Mimic and Splash).
 * Shows the used-move message, then the effect message. In play COM's Double Team ran here
 * whether it moved first or second.
 */
void BattleScene_PhaseSelfEffect(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 5) != 0) {
                BattleScene_SaveCameraFovAndClipMask(arg0);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                BattleCamera_PlayMoveUserShot((s32)arg0);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                func_82104C68(sActingPokemon, 3);
                ActivePokemon_CommitPendingStatus(sActingPokemon);
                BattleScene_PhaseStepNop(sActingPokemon);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            BattleScene_EaseCameraTargetUnlessTransformed(arg0, sActingPokemon);
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            BattleScene_EaseCameraTargetUnlessTransformed(arg0, sActingPokemon);
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            if (sBattleScene.scene->stepFrameTimer == 0x37) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_IsMoveAnimationDone(sActingPokemon, 0x3C) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            BattleScene_EaseCameraTargetUnlessTransformed(arg0, sActingPokemon);
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (sOtherPokemon->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            BattleScene_UpdateHpBarWhenHpSettled(arg0);
            break;
    }
}


/**
 * Phase 30 (moveEffectKind 0x1E, set by BattleEffect_Explosion): Self-Destruct and Explosion.
 * In the per-move sweep only Self-Destruct and Explosion entered phase 30 (then 5, the faint).
 */
void BattleScene_PhaseExplosion(CameraNode* arg0) {
    BattleMonRuntime* sp1C = &(sOtherPokemon)->state.runtime;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 5) != 0) {
                BattleSound_UpdateSideHp(sActingPokemon);
                BattleSound_UpdateSideHp(sOtherPokemon);
                BattleScene_SaveCameraFovAndClipMask(arg0);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                BattleCamera_PlayMoveUserShot((s32)arg0);
                func_82104C68(sActingPokemon, 3);
                ActivePokemon_CommitPendingStatus(sActingPokemon);
                BattleScene_PhaseStepNop(sActingPokemon);
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
                Audio_FadeAndClearStoredSounds();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], !sBattleScene.scene->actingSide);
                BattleCamera_PlayTargetShot(sOtherPokemon, arg0, BattleAnim_RandomRange(2));
                BattleCamera_CaptureModelOrbit(sOtherPokemon, arg0);
                func_82104C68(sActingPokemon, 4);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            BattleScene_EaseCameraTargetToParticipant(arg0, sOtherPokemon);
            if (sBattleScene.scene->stepFrameTimer == 0x28) {
                Battle_ClearMessageCursor();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], !sBattleScene.scene->actingSide);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x50) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            BattleScene_EaseCameraTargetToParticipant(arg0, sOtherPokemon);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((D_8219A564 == 1) && (D_8219A560 == 1)) {
                if (sp1C->hp != 0) {
                    BattleAnim_CleanupEffects(1);
                    BattleSound_UpdateSideHp(sActingPokemon);
                    Audio_FadeAndClearStoredSounds();
                    BattleCamera_PlayShot(sActingPokemon, (s32)arg0, 3);
                    sBattleScene.scene->phaseStep++;
                } else {
                    BattleSound_UpdateSideHp(sOtherPokemon);
                    if (sOtherPokemon->state.runtime.usedMove == 0xFF) {
                        sBattleScene.scene->actionPass = 3;
                    }
                    BattleScene_ResetCameraFrameCounter();
                    func_82124A40();
                    BattleScene_SetPhase(arg0, 5);
                }
            }
            break;

        case 4:
            BattleScene_EaseCameraTargetToParticipant(arg0, sOtherPokemon);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (sOtherPokemon->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            func_82124A40();
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}


/**
 * Phase 28 (moveEffectKind 0x1C): the user's move does nothing and only messages show. Set when
 * the user flinched, when Recover or Rest fails at full HP and when Mirror Move has nothing to
 * copy.
 * In the per-move sweep Recover, Soft-Boiled and Rest at full HP and Mirror Move with nothing to
 * copy entered phase 28.
 */
void BattleScene_PhaseMoveFailedMessage(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_SaveCameraFovAndClipMask(arg0);
            BattleCamera_PlayShot(sActingPokemon, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0xA) != 0) {
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            BattleCamera_PlayShot(sActingPokemon, arg0, 3);
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 0x1E) != 0) {
                ActivePokemon_CommitPendingStatus(sActingPokemon);
                BattleScene_PhaseStepNop(sActingPokemon);
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
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
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (sOtherPokemon->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            BattleScene_UpdateHpBarWhenHpSettled(arg0);
            break;
    }
}


/**
 * Phase 21 (moveEffectKind 0x15, set by Battle_Effect_Heal): Recover, Soft-Boiled and Rest.
 * Not reached in the sweep: 1P's Nidoqueen was at full HP, so heal moves failed to phase 28
 * instead.
 * Seen in play (2026-11-12): Recover with Nidoqueen at 20/69 HP ran this phase, and the HUD then
 * showed 54/69 (half its max HP restored).
 */
void BattleScene_PhaseHeal(CameraNode* arg0) {

    ActivePokemonState* sp24 = &(sActingPokemon)->state;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 0x1E) != 0) {
                BattleSound_UpdateSideHp(sActingPokemon);
                BattleScene_SaveCameraFovAndClipMask(arg0);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                BattleCamera_PlayMoveUserShot((s32)arg0);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                BattleScene_ResetCameraFrameCounter();
                func_82104C68(sActingPokemon, 3);
                ActivePokemon_CommitPendingStatus(sActingPokemon);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            BattleScene_EaseCameraTargetUnlessTransformed(arg0, sActingPokemon);
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            if (BattleScene_IsMoveAnimationDone(sActingPokemon, 0x64) != 0) {
                sBattleScene.scene->phaseStep = 4;
            }
            if (BattleScene_IsCameraFrameCounterAtLeast(0x1E) != 0) {
                Battle_ClearMessageCursor();
                if (sp24->flags & 1) {
                    BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep++;
                } else {
                    BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep = 3;
                }
            }
            break;

        case 2:
            BattleScene_EaseCameraTargetUnlessTransformed(arg0, sActingPokemon);
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            if (BattleScene_IsMoveAnimationDone(sActingPokemon, 0x64) != 0) {
                sBattleScene.scene->phaseStep = 4;
            }
            if (BattleScene_IsCameraFrameCounterAtLeast(0x3C) != 0) {
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            BattleScene_EaseCameraTargetUnlessTransformed(arg0, sActingPokemon);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_IsMoveAnimationDone(sActingPokemon, 0x64) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 4:
            BattleScene_EaseCameraTargetUnlessTransformed(arg0, sActingPokemon);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (sOtherPokemon->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            func_82124A40();
            BattleScene_UpdateHpBarWhenHpSettled(arg0);
            break;
    }
}


/**
 * Phase 15 (moveEffectKind 0x0F, set by Battle_Effect_Transform).
 * In the per-move sweep only Transform entered phase 15.
 */
void BattleScene_PhaseTransform(CameraNode* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    BattleMonRuntime* sp30 = &(sActingPokemon)->state.runtime;
    BattleMonRuntime* sp2C = &(sOtherPokemon)->state.runtime;
    ActivePokemonState* sp28 = &(sActingPokemon)->state;
    ActivePokemonState* sp24 = &(sOtherPokemon)->state;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_821217DC(0x14) != 0) {
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                BattleCamera_PlayMoveUserShot((s32)arg0);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (func_821217DC(0x19) != 0) {
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], sBattleScene.scene->actingSide);
                func_821233EC(arg0, sActingPokemon);
                if (sp30->volatileStatusFlags & 0x10) {
                    if (sp2C->uniqueStatusFlags & 8) {
                        sp28->model = (sActingPokemon)->side->displayModel = sp24->transformSpecies;
                    } else if (sOtherPokemon->side->displayModel == 0x98) {
                        sp28->model = (sActingPokemon)->side->displayModel = sp2C->species;
                    } else {
                        sp28->model = (sActingPokemon)->side->displayModel = sOtherPokemon->side->displayModel;
                    }
                } else if (sp2C->uniqueStatusFlags & 8) {
                    (sActingPokemon)->side->displayModel = sp24->transformSpecies;
                } else if (sOtherPokemon->side->displayModel == 0x98) {
                    (sActingPokemon)->side->displayModel = sp2C->species;
                } else {
                    (sActingPokemon)->side->displayModel = sOtherPokemon->side->displayModel;
                }
                *M2C_FIELD(sActingPokemon, u8**, 0x85C) |= 0x80;
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (*M2C_FIELD(sActingPokemon, u8**, 0x85C) & 0x10) {
                *M2C_FIELD(sActingPokemon, u8**, 0x85C) &= ~0x90;
                func_8210881C(sActingPokemon);
                func_82107408(sActingPokemon);
                func_82101B54(sActingPokemon, sp30->usedMove);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            Audio_PlayMoveSound(sp30->usedMove, (sActingPokemon)->displayObject.objectType, 0);
            func_82104C68(sActingPokemon, 0x12);
            func_821233EC(arg0, sActingPokemon);
            sBattleScene.scene->phaseStep++;
            break;

        case 4:
            M2C_FIELD(sActingPokemon, u8**, 0x9CC)[1] |= 1;
            (sActingPokemon)->thumbnail.displayObject.node.flags |= 1;
            func_82107160(sActingPokemon);
            func_821233EC(arg0, sActingPokemon);
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 0x32) != 0) {
                func_82124A40();
                BattleScene_StepPartyHpAndUpdateHpBar(arg0);
            }
            break;
    }
}


/**
 * Phase 25 (moveEffectKind 0x19, set by Battle_Effect_Substitute).
 */
void BattleScene_PhaseSubstitute(CameraNode* arg0) {
    BattleMonRuntime* sp1C = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;
    ActivePokemonState* sp18 = &sActivePokemon[sBattleScene.scene->actingSide]->state;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleSound_UpdateSideHp(sActingPokemon);
                BattleScene_SaveCameraFovAndClipMask(arg0);
                BattleAnim_PlayMoveEffectScript(sActingPokemon, sp1C->usedMove);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                BattleCamera_PlayMoveUserShot((s32)arg0);
                if (sp18->flags & 0x800) {
                    BattleAnim_SwapToSubstituteModel((s8*)sActingPokemon);
                }
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            if (sp18->flags & 0x800) {
                BattleScene_ResetOwnerModelIfLoaded(sActingPokemon);
            }
            if (BattleAnim_IsModelBusy(sActingPokemon) == 0) {
                Battle_ClearRuntimeFlags(sActingPokemon, 0x800);
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 2:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            BattleScene_RecenterCameraOnOwner(arg0, sActingPokemon);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x46) != 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 3:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            BattleScene_RecenterCameraOnOwner(arg0, sActingPokemon);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (sOtherPokemon->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetAnimationStep();
            BattleScene_UpdateHpBarWhenHpSettled(arg0);
            break;
    }
}

void Announcer_CommentOnSideMessage(s32);

/**
 * Phase 27 (moveEffectKind 0x1B): Bide, when it starts and while it stores energy.
 * In the per-move sweep only Bide entered phase 27.
 */
void BattleScene_PhaseBide(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 0x1E) != 0) {
                BattleScene_SaveCameraFovAndClipMask(arg0);
                Announcer_CommentOnSideMessage(0x2E);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                BattleCamera_PlayMoveUserShot((s32)arg0);
                ActivePokemon_CommitPendingStatus(sActingPokemon);
                BattleScene_PhaseStepNop(sActingPokemon);
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x32) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (sOtherPokemon->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            BattleScene_UpdateHpBarWhenHpSettled(arg0);
            break;
    }
}

void BattleAnim_StartCueEventTrack(ActivePokemon*, s32, s32);

// Returns int with no return statement (most likely an old-style definition with
// no return type). BattleScene_PhaseHaze only matches when this call is seen as
// returning a value: it keeps $v0 away from the scene pointer there.
/**
 * Plays a Pokemon's pending model reactions from its state flags: 2 (reaction 1), 1 (resets
 * its roster byte 5, sets event track 0xB8, reaction 3) and the acting Pokemon's 0x80
 * (reaction 2), clearing each flag, then commits its pending status.
 * @unverified Name guessed from the code.
 */
s32 BattleScene_HazeClearStatusEffects(ActivePokemon* active_pokemon) {
    ActivePokemonState* state = &active_pokemon->state;
    BattleMon* sp28 = &active_pokemon->teamRoster->pokemonPicked[active_pokemon->state.rosterIndex];

    if (active_pokemon->state.flags & 2) {
        func_82136708(1, active_pokemon);
        active_pokemon->displayObject.node.renderFlags |= 0x20;
        Battle_ClearRuntimeFlags(active_pokemon, 2);
    }
    if (state->flags & 1) {
        M2C_FIELD(sp28, s8*, 5) = 0;
        BattleAnim_StartCueEventTrack(active_pokemon, 0xB8, 1);
        func_82136708(3, active_pokemon);
        Battle_ClearRuntimeFlags(active_pokemon, 1);
    }
    if (state->flags & 0x80) {
        func_82136708(2, sActivePokemon[sBattleScene.scene->actingSide]);
        Battle_ClearRuntimeFlags(sActivePokemon[sBattleScene.scene->actingSide], 0x80);
    }
    ActivePokemon_CommitPendingStatus(active_pokemon);
}

void func_82104C68(ActivePokemon*, s32);
s32 BattleScene_IsModelAnimationDone(ActivePokemon*, s32);
void BattleScene_PhaseStepNop(ActivePokemon*);
/**
 * Phase 29: presents Haze (seen in play).
 */
void BattleScene_PhaseHaze(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 5) != 0) {
                BattleCamera_PlayMoveUserShot((s32)arg0);
                BattleScene_SaveCameraFovAndClipMask(arg0);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                func_82104C68(sActingPokemon, 3);
                ActivePokemon_CommitPendingStatus(sActingPokemon);
                BattleScene_PhaseStepNop(sActingPokemon);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            if (sBattleScene.scene->stepFrameTimer == 0x37) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_IsMoveAnimationDone(sActingPokemon, 0x3C) != 0) {
                BattleScene_HazeClearStatusEffects(sOtherPokemon);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (sOtherPokemon->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            BattleScene_UpdateHpBarWhenHpSettled(arg0);
            break;
    }
}

/**
 * Phase 12 (moveEffectKind 0x0C, set by Battle_Effect_Charge for Fly): the first turn of Fly.
 * In the per-move sweep Fly (19) went 2 -> 12.
 */
void BattleScene_PhaseFlyUp(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 0x1E) != 0) {
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                BattleScene_ResetCameraFrameCounter();
                func_821224F4();
                func_82125570();
                Battle_ClearMessageCursor();
                func_82104C68(sActingPokemon, 8);
                sBattleScene.scene->easeRates.y = 0.5f;
                BattleAnim_Vec3fCopy(&sBattleScene.scene->savedCameraAt, &arg0->view.targetPosition);
                BattleAnim_Vec3fCopy(&sBattleScene.scene->savedCameraEye, &arg0->view.eyePosition);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            BattleAnim_ApproachF(&sBattleScene.scene->easeRates.y, 0.0f, 0.06f);
            BattleScene_EaseCameraToFrontView(arg0, sActingPokemon, sBattleScene.scene->easeRates.y);
            if ((sActingPokemon)->displayObject.position.y - D_FLT_82189354[(sActingPokemon)->displayObject.objectType][0] >= 800.0f) {
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            ActivePokemon_SetStateFlags(sActingPokemon, 0x200);
            BattleAnim_Vec3fCopy(&arg0->view.targetPosition, &sBattleScene.scene->savedCameraAt);
            BattleAnim_Vec3fCopy(&arg0->view.eyePosition, &sBattleScene.scene->savedCameraEye);
            sBattleScene.scene->phaseStep++;
            break;

        case 3:
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (func_82121820(0x28) != 0)) {
                ActivePokemon_SetStateFlags(sActivePokemon[sBattleScene.scene->actingSide], 4);
                func_8213C4B8();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetAnimationStep();
                BattleScene_StepPartyHpAndUpdateHpBar(arg0);
            }
            break;
    }
}

void BattleScene_EaseCameraTargetHeight(CameraNode*, ActivePokemon*);
f32 BattleScene_GetParticipantHeight(ActivePokemon*);
/**
 * Phase 13 (moveEffectKind 0x0D, set by Battle_Effect_Charge for Dig): the first turn of Dig.
 * In the per-move sweep only Dig entered phase 13.
 */
void BattleScene_PhaseDigUnder(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 0x1E) != 0) {
                BattleScene_SaveCameraFovAndClipMask(arg0);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                Battle_ClearMessageCursor();
                func_82104C68(sActingPokemon, 8);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if ((sActingPokemon)->modelTransformTimer == 2) {
                BattleScene_EaseCameraTargetHeight(arg0, sActingPokemon);
            }

            if (((sActingPokemon)->displayObject.objectType != 0x32) && ((sActingPokemon)->displayObject.objectType != 0x33)) {
                if ((BattleAnim_IsAssetLoadBusy(sActingPokemon) == 0) && ((sActingPokemon)->displayObject.position.y <= (-BattleScene_GetParticipantHeight(sActingPokemon) * 2.5))) {
                    BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], sBattleScene.scene->actingSide);
                    ActivePokemon_SetStateFlags(sActingPokemon, 0x4000);
                    (sActingPokemon)->displayObject.node.renderFlags &= 0xFFDF;
                    sBattleScene.scene->phaseStep++;
                }
            } else if (BattleScene_IsModelAnimationDone(sActingPokemon, 0x1E) != 0) {
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[3], sBattleScene.scene->actingSide);
                ActivePokemon_SetStateFlags(sActingPokemon, 0x4000);
                (sActingPokemon)->displayObject.node.renderFlags &= 0xFFDF;
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            BattleScene_EaseCameraTargetHeight(arg0, sActingPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            BattleScene_EaseCameraTargetHeight(arg0, sActingPokemon);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            func_82124A40();
            BattleScene_UpdateHpBarWhenHpSettled(arg0);
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
 * Phase 14 (moveEffectKind 0x0E, set by Battle_Effect_Charge): the first turn of Razor Wind,
 * Solar Beam, Skull Bash and Sky Attack.
 * In the per-move sweep Razor Wind (13) went 2 -> 14.
 */
void BattleScene_PhaseChargeUp(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleCamera_PlayShot(sActingPokemon, (s32)arg0, 3);
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 0x1E) != 0) {
                BattleScene_SaveCameraFovAndClipMask(arg0);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                func_8212188C();
                func_8212189C();
                func_82104C68(sActingPokemon, 8);
                ActivePokemon_CommitPendingStatus(sActingPokemon);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (func_82121798(0x28) != 0) {
                func_8211EE8C();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_IsMoveKeyedRowWaitComplete(sActingPokemon, 0x1E) != 0) {
                func_82124A40();
                BattleScene_UpdateHpBarWhenHpSettled(arg0);
            }
            break;
    }
}

/**
 * Phase 17 (moveEffectKind 0x11, set by Battle_CheckMonCanAct): the user can't act because it is
 * asleep or frozen, the target holds it with a trapping move, it must recharge, or its move is
 * disabled.
 * In play COM's Pinsir, held by Bind, spent its turn in phase 17 (row 9).
 */
void BattleScene_PhaseCannotMove(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleScene_SaveCameraFovAndClipMask(arg0);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                BattleCamera_PlayMoveUserShot((s32)arg0);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                ActivePokemon_CommitPendingStatus(sActingPokemon);
                func_82104C68(sActingPokemon, 9);
                sBattleScene.scene->phaseStep++;
                ActivePokemon_CommitPendingStatus(sActingPokemon);
            }
            break;

        case 1:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&arg0->perspective.verticalFieldOfView, 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            func_82124A40();
            BattleScene_UpdateHpBarWhenHpSettled(arg0);
            break;
    }
}

/**
 * Brings a Pokemon back to its normal height after an air or underground move: with flag
 * 0x200 it only restores the height; with 0x4008 it also makes the model opaque and visible
 * again and plays reaction 4.
 * @unverified Name guessed from the code.
 */
void BattleScene_ReturnToGroundHeight(ActivePokemon* active_pokemon) {
    u8* ptr = (u8*)active_pokemon + 0x78C;

    if (M2C_FIELD(ptr, u16*, 0x36) & 0x200) {
        active_pokemon->displayObject.position.y = D_FLT_82189354[active_pokemon->displayObject.objectType][0];
        Battle_ClearRuntimeFlags(active_pokemon, 0x608);
    } else if (M2C_FIELD(ptr, u16*, 0x36) & 0x4008) {
        active_pokemon->displayObject.alpha = 0xFF;
        func_82136708(4, active_pokemon);
        active_pokemon->displayObject.position.y = D_FLT_82189354[active_pokemon->displayObject.objectType][0];
        active_pokemon->displayObject.node.renderFlags &= ~0x2;
        active_pokemon->displayObject.node.renderFlags |= 0x20;
        active_pokemon->displayObject.node.flags |= 1;
        Battle_ClearRuntimeFlags(active_pokemon, 0x4608);
    }
}


/**
 * Phase 20: a confused Pokemon hurts itself (seen in play: 75 to 63 HP). Shows the message, enters state row 15, and steps the HP down.
 */
void BattleScene_PhaseConfusionSelfHit(CameraNode* arg0) {
    BattleScene_ResetCameraFovTo30(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98(sActingPokemon) == 0) {
                BattleScene_ReturnToGroundHeight(sActingPokemon);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            BattleScene_ResetAnimationStep();
            BattleScene_EnterStateRow(sActingPokemon, 0xF);
            BattleCamera_PlayTargetShot(sActingPokemon, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
            BattleScene_SetDamageShakeAmplitude(sActingPokemon);
            BattleAnim_QueueEffectList(8, sActingPokemon);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 2:
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            BattleScene_FrameReactingParticipant(arg0, sActingPokemon);
            if (BattleScene_IsModelAnimationDone(sActingPokemon, 0x32) != 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 3:
            if (BattleScene_ReloadModelForFlag1000(sActingPokemon) == 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 4:
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_FrameReactingParticipant(arg0, sActingPokemon) != 0) {
                BattleScene_ResetAnimationStep();
                BattleScene_StepPartyHpAndUpdateHpBar(arg0);
            }
            break;
    }
}


/**
 * Phase 31: からだが しびれて うごけない (is fully paralyzed), seen in play.
 */
void BattleScene_PhaseFullParalysis(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_SaveCameraFovAndClipMask(arg0);
            BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[1], sBattleScene.scene->actingSide);
            BattleScene_ReturnToGroundHeight(sActingPokemon);
            BattleCamera_PlayShot(sActingPokemon, arg0, 3);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            BattleCamera_PlayShot(sActingPokemon, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                ActivePokemon_CommitPendingStatus(sActingPokemon);
                BattleScene_EnterStateRow(sActingPokemon, 9);
                sBattleScene.scene->phaseStep += 1;
                ActivePokemon_CommitPendingStatus(sActingPokemon);
            }
            break;

        case 2:
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 3:
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            BattleScene_ResetAnimationStep();
            BattleScene_UpdateHpBarWhenHpSettled(arg0);
            break;
    }
}

/**
 * Picks one of three target camera framings at random for Pokemon arg0 and runs it.
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayRandomTargetFraming3(ActivePokemon* active_pokemon, CameraNode* camera) {
    D_8219A568 = BattleAnim_RandomRange(3);
    if (D_8219A568 >= 4) {
        D_8219A568 = 0;
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
 * Picks one of four or five target framings (func_8210C020(4)) for Pokemon arg0 and runs it.
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayRandomTargetFraming4(ActivePokemon* active_pokemon, CameraNode* camera) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_8210C020(4, (s32)camera); D_8219A568 = temp_v0;
    var_v1 = temp_v0;
    if (temp_v0 >= 5) {
        D_8219A568 = 0;
        var_v1 = 0;
    }
    switch (var_v1) {
        case 0:
            BattleScene_CameraShotTargetHighThunk(camera, active_pokemon);
            return;
        case 1:
            BattleScene_FrameParticipantFromAboveThunk(camera, active_pokemon);
            return;
        case 2:
            BattleScene_FrameParticipantFromBelowClamped(camera, active_pokemon);
            return;
        case 3:
            BattleScene_FrameParticipantFrontAltThunk(camera, active_pokemon);
            return;
        default:
            BattleScene_FrameParticipantFrontAltThunk(camera, active_pokemon);
            return;
    }
}

/**
 * Plays the target camera shot for the move the other side used, from field 6 of the move
 * table D_80073D90 (4 and 6 pick a random framing, 5 reuses the last one).
 * @unverified Name guessed from the code.
 */
void BattleCamera_PlayMoveTargetShot(CameraNode* camera) {
    s32 other = sBattleScene.scene->actingSide == 0;
    ActivePokemon* opp = sActivePokemon[other];
    BattleMonRuntime* runtime = &opp->state.runtime;

    if (D_80073D90[runtime->usedMove - 1].targetCameraShot == 5) {
        BattleCamera_PlayTargetShot(opp, camera, D_8219A568);
    } else if (D_80073D90[runtime->usedMove - 1].targetCameraShot == 4) {
        BattleCamera_PlayRandomTargetFraming3(opp, camera);
    } else if (D_80073D90[runtime->usedMove - 1].targetCameraShot == 6) {
        BattleCamera_PlayRandomTargetFraming4(opp, camera);
    } else {
        BattleCamera_PlayTargetShot(opp, camera, D_80073D90[runtime->usedMove - 1].targetCameraShot);
    }
}

/**
 * Phase 4: ends the turn and returns to phase 0.
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran at phase 4
 * after both actions, and the battle went back to the command menu.
 */
void BattleScene_PhaseEndTurn(s32 arg0) {
    s32 temp_v0;

    temp_v0 = sBattleScene.scene->phaseStep;
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8211EE8C();
        BattleScene_BeginCameraReturnTransition();
        /* fallthrough */
    case 1:
        return;
    }
}


/**
 * Phase 16 (moveEffectKind 0x10, set by Battle_PrintMoveFailureText): Jump Kick and Hi Jump Kick
 * missed and the user takes crash damage.
 * In play a forced Jump Kick miss went 2 -> 16, showed 「いきおい あまって ニドニドは じめんに ぶつかった！」 and took
 * Nidoqueen from 69 to 68 HP.
 */
void BattleScene_PhaseCrashDamage(CameraNode* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 side = sBattleScene.scene->actingSide;
    u8* sp1C = D_82189180[side] + 0x738;

    BattleScene_ResetCameraFovTo30(arg0);
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_ResetAnimationStep();
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            if (func_82124B30(sActingPokemon) == 0) {
                BattleSound_UpdateSideHp(sActingPokemon);
                sBattleScene.scene->cameraPresetId = 1;
                func_82108C0C(sActingPokemon);
                func_8213B31C(1);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
                BattleCamera_PlayTargetShot(sActingPokemon, arg0, 3);
                BattleCamera_CaptureModelOrbit(sActingPokemon, arg0);
                func_82121EB0(sActingPokemon);
                BattleScene_ResetAnimationStep();
                ModelAnim_SetAnimation((DisplayObject*)sActingPokemon, *sp1C);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            sBattleScene.scene->cameraPresetId = 1;
            BattleCamera_PlayTargetShot(sActingPokemon, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                Battle_ClearMessageCursor();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[6], sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            sBattleScene.scene->cameraPresetId = 1;
            BattleCamera_PlayTargetShot(sActingPokemon, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 4:
            sBattleScene.scene->cameraPresetId = 1;
            if (BattleScene_ReloadModelForFlag1000(sActingPokemon) == 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 5:
            sBattleScene.scene->cameraPresetId = 1;
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            BattleCamera_PlayTargetShot(sActingPokemon, arg0, 3);
            if ((D_8219A560 != 0) && (D_8219A564 != 0)) {
                BattleScene_ResetAnimationStep();
                BattleScene_StepPartyHpAndUpdateHpBar(arg0);
            }
            break;
    }
}


/**
 * Phase 8: the move missed. The target dodges to a random side (row 12 on the user) and the
 * miss message shows. Entered from step 3 when Battle_MoveMissed ran or moveEffectKind is 8.
 * In play a forced miss (Battle_Random = 255) ran 2 -> 8 and showed
 * 「しかし ニドニドの こうげきは はずれた！」.
 */
void BattleScene_PhaseMoveMissed(CameraNode* arg0) {
    ActivePokemonState* sp1C = &sOtherPokemon->state;

    BattleScene_ResetCameraFovTo30(arg0);
    sBattleScene.scene->cameraPresetId = 2;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            if (sp1C->flags & 0x200) {
                BattleCamera_PlayTargetShot(sOtherPokemon, arg0, D_8219A568 = 2);
            } else {
                BattleCamera_PlayTargetShot(sOtherPokemon, arg0, D_8219A568 = BattleAnim_RandomRange(2));
            }
            BattleScene_EnterStateRow(sActingPokemon, 0xC);
            BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            sBattleScene.scene->phaseStep += 1;
            func_8210626C(sOtherPokemon);
            break;

        case 1:
            BattleScene_UseCameraPreset1AndIdleUser();
            if (func_821217DC(0x32) != 0) {
                BattleScene_CleanupParticipantEffectMode(sActingPokemon);
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                func_8211EE8C();
                BattleScene_ResetAnimationStep();
                BattleScene_StepPartyHpAndUpdateHpBar(arg0);
            }
            break;
    }
}

/**
 * Phase 22 (moveEffectKind 0x16): a status move hits the target. Set by Battle_Effect_Sleep,
 * Battle_Effect_Poison, Battle_Effect_Paralyze and Battle_Effect_Confuse. Seen in play for
 * Confuse Ray.
 */
void BattleScene_PhaseInflictStatus(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    BattleScene_ResetCameraFovTo30(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            BattleCamera_PlayMoveTargetShot(arg0);
            BattleCamera_CaptureModelOrbit(sOtherPokemon, arg0);
            BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_EnterStateRow(sActingPokemon, 0xE);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            if (sBattleScene.scene->stepFrameTimer == 0x1E) {
                ActivePokemon_CommitPendingStatus(sOtherPokemon);
            }
            if (func_821217DC(0x50) != 0) {
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                func_8211EE8C();
                BattleScene_ResetAnimationStep();
                BattleScene_StepPartyHpAndUpdateHpBar(arg0);
            }
            break;
    }
}

/**
 * Phase 26 (moveEffectKind 0x1A, set by Battle_Effect_LowerStat): a move that lowers the target's
 * stat.
 * In the per-move sweep (moves 1-33) only Sand Attack ran it.
 */
void BattleScene_PhaseLowerStat(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    BattleScene_ResetCameraFovTo30(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            BattleScene_ResetAnimationStep();
            BattleScene_ResetCameraFrameCounter();
            ActivePokemon_CommitPendingStatus(sOtherPokemon);
            BattleCamera_PlayMoveTargetShot(arg0);
            BattleCamera_CaptureModelOrbit(sOtherPokemon, arg0);
            BattleScene_EnterStateRow(sActingPokemon, 0xB);
            BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[6], sBattleScene.scene->actingSide);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            BattleScene_FrameReactingParticipant(arg0, sOtherPokemon);
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x6E) != 0) {
                sBattleScene.scene->phaseStep += 1;
                func_8211EE8C();
                BattleScene_ResetCameraFrameCounter();
            }
            break;

        case 2:
            if (BattleScene_ReloadModelForFlag1000(sOtherPokemon) == 0) {
                BattleScene_UseCameraPreset1AndIdleUser();
                D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
                D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
                BattleScene_EaseCameraTargetToParticipant(arg0, sOtherPokemon);
                BattleScene_ResetAnimationStep();
                func_82125AC8(arg0);
            }
            break;
    }
}

/**
 * Phase 32 (moveEffectKind 0x20, set by Battle_Effect_Disable).
 * In the per-move sweep only Disable entered phase 32.
 */
void BattleScene_PhaseDisable(CameraNode* arg0) {
    BattleMonRuntime* runtime = &(sActingPokemon)->state.runtime;

    sBattleScene.scene->cameraPresetId = 2;
    BattleScene_ResetCameraFovTo30(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            BattleCamera_PlayTargetShot(sOtherPokemon, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            BattleAnim_QueueMoveEffectEnd(runtime->usedMove, sActingPokemon, sOtherPokemon, BattleScene_GetHitCueDefaultAnchor(sOtherPokemon), BattleScene_GetHitCueAlternateAnchor(sOtherPokemon));
            BattleScene_SetParticipantModelTransform(sOtherPokemon, 0x10, 0);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            BattleScene_UseCameraPreset1AndIdleUser();
            if (func_821217DC(0x50) != 0) {
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                func_8211EE8C();
                BattleScene_ResetAnimationStep();
                BattleScene_StepPartyHpAndUpdateHpBar(arg0);
            }
            break;
    }
}

/**
 * Camera and HP sequence for a hit on the target: shows the target's shot and the move
 * message, steps the target's displayed HP, then switches to the user's shot and steps
 * both sides' HP until they catch up and the user's animation ends, then runs the HP bar
 * step.
 * @unverified Name guessed from the code.
 */
void BattleScene_PhaseDrainHp(CameraNode* camera) {
    BattleScene_ResetCameraFovTo30(camera);
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleSound_UpdateSideHp(sActingPokemon);
            BattleSound_UpdateSideHp(sOtherPokemon);
            func_8213B31C(1);
            sBattleScene.scene->cameraPresetId = 2;
            func_82104C68(sActingPokemon, 4);
            BattleCamera_PlayTargetShot(sOtherPokemon, camera, D_8219A568 = BattleAnim_RandomRange(4));
            BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[0], sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            func_82121EB0(sOtherPokemon);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            sBattleScene.scene->cameraPresetId = 2;
            D_8219A564 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            if (sBattleScene.scene->stepFrameTimer == 0x3C) {
                Battle_ClearMessageCursor();
            }
            if ((D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounter(0x96) != 0)) {
                BattleCamera_PlayTargetShot(sActingPokemon, camera, D_8219A568 = BattleAnim_RandomRange(4));
                Audio_FadeAndClearStoredSounds();
                func_8213B31C(1);
                func_821365E8(4, sActingPokemon);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if (BattleScene_AdvanceCameraFrameCounter(0x5A) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            D_8219A560 = Battle_StepPartyHpToDisplay(sOtherPokemon);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActingPokemon);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (BattleScene_IsModelAnimationDone(sActingPokemon, 0x1E) != 0)) {
                func_82125570();
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                BattleScene_UseCameraPreset1AndIdleUser();
                func_82125AC8(camera);
            }
            break;
    }
}


/**
 * Phase 6. Poison/burn-style residual damage after a move: BattleScene_UpdateDisplayedHpAndTransition enters it
 * when the acting Pokemon has unk_15 bits 0x18 or unk_4D bit 0x80 set. Plays effect list 5 or 6 (unk_15 bits)
 * and effect list 10 (unk_4D bit 0x80), then flips the acting side and enters BattleScene_PhaseConfusionSelfHit if the
 * acting Pokemon reaches 0 HP.
 */
void BattleScene_PhaseResidualDamageAfterMove(CameraNode* arg0) {
    BattleMonRuntime* sp2C = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;
    BattleMonRuntime* sp28 = &sActivePokemon[!sBattleScene.scene->actingSide]->state.runtime;
    ActivePokemon* sp24 = sActivePokemon[sBattleScene.scene->actingSide];

    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_FrameParticipantFrontWide(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            func_82124A40();
            BattleSound_UpdateSideHp(sActingPokemon);
            func_82106374(sActingPokemon);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            BattleScene_ResidualPhaseNop(sp24);
            if (BattleScene_ReloadModelForFlag2000(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                func_82108C0C(sActingPokemon);
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                BattleScene_FrameParticipantFrontWide(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
                func_82104C68(sActivePokemon[sBattleScene.scene->actingSide], 0xD);
                if (sp2C->statusCondition & 0x18) {
                    BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[7], sBattleScene.scene->actingSide);
                    sp2C->hp = sp2C->hpAfterPoisonBurn;
                    sp28->hp = sp28->hpAfterPoisonBurn;
                    if (sp2C->statusCondition & 0x10) {
                        BattleAnim_QueueEffectList(6, sActingPokemon);
                    } else {
                        BattleAnim_QueueEffectList(5, sActingPokemon);
                    }
                    sBattleScene.scene->phaseStep++;
                } else {
                    BattleSound_UpdateSideHp(sOtherPokemon);
                    BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[8], sBattleScene.scene->actingSide);
                    Audio_PlayCommand(0x22, 0, 0);
                    sp2C->hp = sp2C->hpAfterLeechSeed;
                    sp28->hp = sp28->hpAfterLeechSeed;
                    BattleAnim_QueueEffectList(0xA, sActingPokemon);
                    sBattleScene.scene->phaseStep = 3;
                }
            }
            break;

        case 2:
            BattleScene_FrameParticipantFrontWide(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                if (func_82107CA0(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                    func_82125570();
                    BattleScene_SetPhase(arg0, 5);
                    sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
                } else if (sp2C->volatileStatusFlags & 0x80) {
                    BattleSound_UpdateSideHp(sOtherPokemon);
                    Audio_PlayCommand(0x22, 0, 0);
                    BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[8], sBattleScene.scene->actingSide);
                    sp2C->hp = sp2C->hpAfterLeechSeed;
                    sp28->hp = sp28->hpAfterLeechSeed;
                    BattleAnim_QueueEffectList(0xA, sActingPokemon);
                    sBattleScene.scene->phaseStep++;
                } else {
                    sBattleScene.scene->phaseStep = 4;
                }
            }
            break;

        case 3:
            BattleScene_FrameParticipantFrontWide(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0) && (D_8219A560 == 1) && (D_8219A564 == 1)) {
                sBattleScene.scene->phaseStep++;
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
            }
            break;

        case 4:
            if (BattleScene_ReloadModelForFlag1000(sOtherPokemon) == 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 5:
            func_82124A40();
            BattleScene_FrameParticipantFrontWide(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}


void func_82106374(ActivePokemon*);
s32 BattleScene_ReloadModelForFlag2000(ActivePokemon*);
void func_82108C0C(ActivePokemon*);
void BattleAnim_QueueEffectList(u8 arg0, s32 arg1);
void func_821237B0(CameraNode*, ActivePokemon*);
void BattleScene_EaseCameraToRecoilFraming(CameraNode*, ActivePokemon*);
void func_82134EBC(ActivePokemon*, s32);
s32 BattleScene_ReloadModelForFlag1000(ActivePokemon*);
/**
 * Phase 9 (moveEffectKind 9). The acting Pokemon takes damage from its own move: plays effect list 9, the
 * hit cue animation and the damage shake, then commits pendingHp to hp.
 * In the per-move sweep exactly Take Down, Double-Edge, Submission and Struggle entered phase 9.
 */
void BattleScene_PhaseRecoilDamage(CameraNode* arg0) {
    BattleMonRuntime* self = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;
    BattleMonRuntime* other = &sActivePokemon[!sBattleScene.scene->actingSide]->state.runtime;

    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleSound_UpdateSideHp(sActingPokemon);
            func_82106374(sActingPokemon);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            if (BattleScene_ReloadModelForFlag2000(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                func_82108C0C(sActingPokemon);
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                BattleAnim_QueueEffectList(9, sActingPokemon);
                BattleScene_ResetCameraFrameCounter();
                func_821237B0(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[14], sBattleScene.scene->actingSide);
                self->hp = self->pendingHp;
                other->hp = other->pendingHp;
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            BattleScene_EaseCameraToRecoilFraming(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0xF) != 0) {
                func_82134EBC(sActingPokemon, 0x1F);
                func_82121EB0(sActingPokemon);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            if (BattleScene_ReloadModelForFlag1000(sOtherPokemon) == 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 4:
            BattleScene_ResetAnimationStep();
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            BattleScene_EaseCameraToRecoilFraming(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (func_82121820(0x3C) != 0)) {
                func_82125AC8(arg0);
            }
            break;
    }
}

/**
 * Battle phase 10. Step 0 waits until the acting Pokemon's check passes, then clears
 * effects, shows a message for the other side, queues effect list 6 and plays sound
 * command 0x23. Step 1 waits 55 frames and shows a second message, then falls through to
 * step 2, which waits 60 frames and ends the phase.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name guessed from the code.
 */
void BattleScene_Phase10(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_CleanupParticipantEffectMode(sActingPokemon);
            BattleScene_ResidualPhaseNop(sActivePokemon[sBattleScene.scene->actingSide]);
            if (BattleScene_ReloadModelForFlag2000(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                func_82108C0C(sActingPokemon);
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[11], !sBattleScene.scene->actingSide);
                BattleAnim_QueueEffectList6(3, sOtherPokemon);
                Audio_PlayCommand(0x23, 0, 0);
                BattleScene_FrameParticipantFrontWide(arg0, sOtherPokemon);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(0x37) != 0) {
                func_8211EE8C();
                BattleMessage_ShowForSide((s32)gBattleMessageQueues->messageBuffers[9], !sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            /* fallthrough */
        case 2:
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                func_8211EE8C();
                func_82125AC8(arg0);
            }
            break;
    }
}
