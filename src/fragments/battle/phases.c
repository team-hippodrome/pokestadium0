/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "audio_commands.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK func_8211EE8C();
M2C_UNK func_82125384();
extern ActivePokemon* D_8219A540;
extern f32 D_FLT_82189354[][4];
extern s32 D_8219A520;
extern s32 D_8219A544;
extern s8 *D_8219A5A0;
extern u8* D_82189180[];
s32 Battle_StepPartyHpToDisplay(ActivePokemon*);
s32 func_82107A5C(ActivePokemon*);
s32 func_82107CA0(ActivePokemon*);
s32 func_8210C020(M2C_UNK, s32);
s32 func_82124810(void*, void*);
void ActivePokemon_SetStateFlags(ActivePokemon*, s32);
void Audio_PlayMoveSound(s32, s32, s32);
void BattleCamera_PlayShot(s32, s32, s32);
void BattleMessage_ShowForSide(s32, s32);
void BattleScene_CameraShotTargetHighThunk(void*, void*);
void BattleScene_ReactionCritical(CameraNode*, void*);
void BattleScene_ReactionNormal(CameraNode*, void*);
void func_821020FC(s8*);
void func_82104C68(ActivePokemon*, s32);
void func_82106354(ActivePokemon*);
void func_82106374(ActivePokemon*);
void func_82107408(ActivePokemon*);
void func_82108C0C(ActivePokemon*);
void func_821224F4();
void func_8212311C(CameraNode*, ActivePokemon*, f32);
void func_82124830(void*, void*);
void func_82124874(void*, void*);
void func_82124A40(void);
void func_82125AC8(CameraNode*);
void func_82125C34(CameraNode*);
void func_82125C80(CameraNode*);
void func_8212A4A4(s32);
void func_8212A4CC(CameraNode*, s32*, s32*);
void func_8212A554(void*);
void func_8212A768(ActivePokemon*, CameraNode*, void*);
void func_82135098(ActivePokemon*);

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
    u8* sp24 = (u8*)D_8219A544 + 0x7C6;
    Cue8212B270* temp_v1 = (sp24[0x5A] - 1) + (Cue8212B270*)D_82189180[func_82107A5C(D_8219A540)];
    volatile s32 sp1C;

    if (D_8219A540->displayObject.objectType == 0x98) {
        sp1C = 0xF;
    } else if (temp_v1->unk_0A == 0xFF) {
        sp1C = M2C_FIELD(((ActivePokemon*)D_8219A544)->displayObject.transformAnim.data, u16*, 0xA) - temp_v1->unk_06;
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
                BattleCamera_CaptureModelOrbit(D_8219A540, arg0);
                func_82122DFC(arg0, D_8219A540);
                ActivePokemon_CommitPendingStatus(D_8219A540);
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseSubstep = 2;
                D_8219A578 = 0;
                func_8212A4A4(D_8219A520 + 0x148);
                if (M2C_FIELD(D_8219A520, s8*, 0x149) != 0) {
                    D_8219A578 = 1;
                }
                BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                func_821061A8(D_8219A540);
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
                BattleMessage_ShowForSide(D_8219A520 + 0x308, sBattleScene.scene->actingSide);
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
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (D_8219A578 == 0) {
                func_8212A4A4(D_8219A520 + 0x88);
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                func_8212A4A4(D_8219A520 + 0x88);
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 5:
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (D_8219A578 == 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8212A4A4(D_8219A520 + 0x208);
                BattleMessage_ShowForSide(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8212A4A4(D_8219A520 + 0x208);
                BattleMessage_ShowForSide(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 6:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
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
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            if (func_82122DFC(arg0, D_8219A540) != 0) {
                sBattleScene.scene->phaseSubstep = 9;
            }
            break;

        case 8:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (func_82105C8C(D_8219A540, 0xF) != 0) {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 9:
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            if (M2C_FIELD(D_8219A520, s8*, 0x3C9) == 0) {
                sBattleScene.scene->phaseSubstep = 0xB;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide(D_8219A520 + 0x3C8, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 10:
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->phaseSubstep++;
                Battle_ClearMessageCursor();
            }
            break;

        case 11:
            if (func_82124BF8(D_8219A540) == 0) {
                D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
                D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
                func_82122DFC(arg0, D_8219A540);
                func_8212A4CC(arg0, &D_8219A560, &D_8219A564);
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

    u8* sp1C = (u8*)D_8219A540 + 0x7C6;

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            func_82135098(D_8219A540);
            func_8212A554(arg1);
            func_82124A40();
            BattleScene_ResetCameraFrameCounter();
            ActivePokemon_CommitPendingStatus(D_8219A540);
            func_8212A4A4(D_8219A520 + 0x148);
            BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
            func_8212A768(D_8219A540, arg0, arg1);
            BattleCamera_CaptureModelOrbit(D_8219A540, arg0);
            func_82104C68((ActivePokemon*)D_8219A544, 0xB);
            sBattleScene.scene->phaseSubstep++;
            break;

        case 1:
            func_82124E80();
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 2:
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                BattleMessage_ShowForSide(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 3:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
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
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            if (func_82122DFC(arg0, D_8219A540) != 0) {
                sBattleScene.scene->phaseSubstep = 6;
            }
            break;

        case 5:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (func_82105C8C(D_8219A540, 0xF) != 0) {
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 6:
            if (M2C_FIELD(D_8219A520, s8*, 0x3C9) == 0) {
                sBattleScene.scene->phaseSubstep = 8;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
                D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide(D_8219A520 + 0x3C8, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseSubstep++;
            }
            break;

        case 7:
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->phaseSubstep++;
                Battle_ClearMessageCursor();
            }
            break;

        case 8:
            if (func_82124BF8(D_8219A540) == 0) {
                D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
                D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
                func_82122DFC(arg0, D_8219A540);
                func_8212A4CC(arg0, &D_8219A560, &D_8219A564);
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

    func_821255EC(arg0);
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
    u8* sp = (u8*)sActivePokemon[sBattleScene.scene->actingSide] + 0x7C6;

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
                BattleScene_ActionStepIntro(arg0, *(u16*)(D_80073D84 + 2 + sp[0x5A] * n));
                break;
            case 1:
                BattleScene_ActionStepSetHitCount(arg0, 0);
                break;
            case 2:
                BattleScene_ActionStepUseMove(arg0, *(u16*)(D_80073D84 + 4 + sp[0x5A] * n));
                break;
            case 3:
                BattleScene_ActionStepTravel(arg0, *(u16*)(D_80073D84 + 6 + sp[0x5A] * n));
                break;
            case 4:
                BattleScene_ActionStepReaction(arg0, (void*)*(u16*)(D_80073D84 + 8 + sp[0x5A] * n));
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
    u8* sp = (u8*)sActivePokemon[sBattleScene.scene->actingSide] + 0x7C6;

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
                BattleScene_ActionStepIntro(arg0, *(u16*)(D_80073D84 + 2 + sp[0x5A] * n));
                break;
            case 1:
                BattleScene_ActionStepSetHitCount(arg0, 0);
                break;
            case 2:
                BattleScene_ActionStepUseMove(arg0, *(u16*)(D_80073D84 + 4 + sp[0x5A] * n));
                break;
            case 3:
                BattleScene_ActionStepTravel(arg0, *(u16*)(D_80073D84 + 6 + sp[0x5A] * n));
                break;
            case 4:
                BattleScene_ActionStepReaction(arg0, (void*)*(u16*)(D_80073D84 + 8 + sp[0x5A] * n));
                break;
        }
    }
}


void func_8212C398(s32 arg0)
{
  s32 temp_v0;
  s32 var_v1;
 temp_v0 = func_8210C020(3, arg0); D_8219A568 = temp_v0; var_v1 = temp_v0; if (temp_v0 >= 4) { D_8219A568 = 0 ^ 0; var_v1 = 0; } switch (var_v1) { case 0: // FAKE: no-op ^ 0
      BattleCamera_PlayShot(D_8219A544, arg0, 0);
      return;

    case 1:
      BattleCamera_PlayShot(D_8219A544, arg0, 1);
      return;

    case 2:
      BattleCamera_PlayShot(D_8219A544, arg0, 2);
      return;

    default:
      BattleCamera_PlayShot(D_8219A544, arg0, 0);
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
      BattleCamera_PlayShot(D_8219A544, arg0, 0);
      return;

    case 1:
      BattleCamera_PlayShot(D_8219A544, arg0, 1);
      return;

    case 2:
      BattleCamera_PlayShot(D_8219A544, arg0, 2);
      return;

    case 3:
      BattleCamera_PlayShot(D_8219A544, arg0, 3);
      return;

    default:
      BattleCamera_PlayShot(D_8219A544, arg0, 0);
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
      BattleCamera_PlayShot(D_8219A544, arg0, 0);
      return;

    case 1:
      BattleCamera_PlayShot(D_8219A544, arg0, 1);
      return;

    case 2:
      BattleCamera_PlayShot(D_8219A544, arg0, 2);
      return;

    case 3:
      BattleCamera_PlayShot(D_8219A544, arg0, 4);
      return;

    default:
      BattleCamera_PlayShot(D_8219A544, arg0, 0);
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
            BattleCamera_PlayShot(D_8219A544, arg0, 0);
            break;
        case 1:
            BattleCamera_PlayShot(D_8219A544, arg0, 1);
            break;
        case 2:
            BattleCamera_PlayShot(D_8219A544, arg0, 2);
            break;
        case 3:
            BattleCamera_PlayShot(D_8219A544, arg0, 3);
            break;
        case 4:
            BattleCamera_PlayShot(D_8219A544, arg0, 4);
            break;
        default:
            BattleCamera_PlayShot(D_8219A544, arg0, 0);
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

/**
 * Plays the user's camera shot for its move from the move table D_80073D90 (field 2). Shots
 * 5, 6 and 7 use their own setups, and shot 4 also sets scene+0x54.
 */
void func_8212C78C(s32 arg0) {
    BattleMonRuntime* runtime;

    runtime = &((ActivePokemon*)D_8219A544)->state.runtime;
    sBattleScene.scene->easeFovAfterUserShot = 0;
    if (D_80073D90[runtime->usedMove - 1].unk_02 == 5) {
        func_8212C398(arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_02 == 6) {
        func_8212C454(arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_02 == 7) {
        func_8212C530(arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_02 == 4) {
        sBattleScene.scene->easeFovAfterUserShot = 1;
        BattleCamera_PlayUserShot(arg0, D_80073D90[runtime->usedMove - 1].unk_02);
    } else {
        BattleCamera_PlayUserShot(arg0, D_80073D90[runtime->usedMove - 1].unk_02);
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
            if (func_82105724((ActivePokemon*)D_8219A544, 5) != 0) {
                func_821255B4(arg0);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
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
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (D_8219A540->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}


/**
 * Phase 30 (moveEffectKind 0x1E, set by BattleEffect_Explosion): Self-Destruct and Explosion.
 * In the per-move sweep only Self-Destruct and Explosion entered phase 30 (then 5, the faint).
 */
void BattleScene_PhaseExplosion(CameraNode* arg0) {
    u8* sp1C = (u8*)D_8219A540 + 0x7C6;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 5) != 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                func_82135098(D_8219A540);
                func_821255B4(arg0);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
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
                Audio_FadeAndClearStoredSounds();
                BattleMessage_ShowForSide(D_8219A520 + 0x148, !sBattleScene.scene->actingSide);
                BattleCamera_PlayTargetShot(D_8219A540, arg0, BattleAnim_RandomRange(2));
                BattleCamera_CaptureModelOrbit(D_8219A540, arg0);
                func_82104C68((ActivePokemon*)D_8219A544, 4);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            func_82122A7C(arg0, D_8219A540);
            if (sBattleScene.scene->stepFrameTimer == 0x28) {
                Battle_ClearMessageCursor();
                BattleMessage_ShowForSide(D_8219A520 + 0x88, !sBattleScene.scene->actingSide);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x50) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            func_82122A7C(arg0, D_8219A540);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((D_8219A564 == 1) && (D_8219A560 == 1)) {
                if (M2C_FIELD(sp1C, u16*, 0xC) != 0) {
                    BattleAnim_CleanupEffects(1);
                    func_82135098((ActivePokemon*)D_8219A544);
                    Audio_FadeAndClearStoredSounds();
                    BattleCamera_PlayShot(D_8219A544, (s32)arg0, 3);
                    sBattleScene.scene->phaseStep++;
                } else {
                    func_82135098(D_8219A540);
                    if (D_8219A540->state.runtime.usedMove == 0xFF) {
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
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (D_8219A540->state.runtime.usedMove == 0xFF) {
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
            func_821255B4(arg0);
            BattleCamera_PlayShot(D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0xA) != 0) {
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            BattleCamera_PlayShot(D_8219A544, arg0, 3);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
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
            if (D_8219A540->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
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

    u8* sp24 = (u8*)D_8219A544 + 0x78C;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                func_821255B4(arg0);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                BattleScene_ResetCameraFrameCounter();
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x64) != 0) {
                sBattleScene.scene->phaseStep = 4;
            }
            if (BattleScene_IsCameraFrameCounterAtLeast(0x1E) != 0) {
                Battle_ClearMessageCursor();
                if (M2C_FIELD(sp24, u16*, 0x36) & 1) {
                    BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep++;
                } else {
                    BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep = 3;
                }
            }
            break;

        case 2:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x64) != 0) {
                sBattleScene.scene->phaseStep = 4;
            }
            if (BattleScene_IsCameraFrameCounterAtLeast(0x3C) != 0) {
                BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x64) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 4:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (D_8219A540->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            func_82124A40();
            func_82125C80(arg0);
            break;
    }
}


/**
 * Phase 15 (moveEffectKind 0x0F, set by Battle_Effect_Transform).
 * In the per-move sweep only Transform entered phase 15.
 */
void BattleScene_PhaseTransform(CameraNode* arg0) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    u8* sp30 = (u8*)D_8219A544 + 0x7C6;
    u8* sp2C = (u8*)D_8219A540 + 0x7C6;
    u8* sp28 = (u8*)D_8219A544 + 0x78C;
    u8* sp24 = (u8*)D_8219A540 + 0x78C;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_821217DC(0x14) != 0) {
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (func_821217DC(0x19) != 0) {
                BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                func_821233EC(arg0, (ActivePokemon*)D_8219A544);
                if (sp30[0x4D] & 0x10) {
                    if (sp2C[0x4E] & 8) {
                        M2C_FIELD(sp28, s16*, 0xC0) = ((ActivePokemon*)D_8219A544)->sessionTeams->displayModel = M2C_FIELD(sp24, s16*, 0xC2);
                    } else if (D_8219A540->sessionTeams->displayModel == 0x98) {
                        M2C_FIELD(sp28, s16*, 0xC0) = ((ActivePokemon*)D_8219A544)->sessionTeams->displayModel = sp2C[0xB];
                    } else {
                        M2C_FIELD(sp28, s16*, 0xC0) = ((ActivePokemon*)D_8219A544)->sessionTeams->displayModel = D_8219A540->sessionTeams->displayModel;
                    }
                } else if (sp2C[0x4E] & 8) {
                    ((ActivePokemon*)D_8219A544)->sessionTeams->displayModel = M2C_FIELD(sp24, s16*, 0xC2);
                } else if (D_8219A540->sessionTeams->displayModel == 0x98) {
                    ((ActivePokemon*)D_8219A544)->sessionTeams->displayModel = sp2C[0xB];
                } else {
                    ((ActivePokemon*)D_8219A544)->sessionTeams->displayModel = D_8219A540->sessionTeams->displayModel;
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
            Audio_PlayMoveSound(sp30[0x5A], ((ActivePokemon*)D_8219A544)->displayObject.objectType, 0);
            func_82104C68((ActivePokemon*)D_8219A544, 0x12);
            func_821233EC(arg0, (ActivePokemon*)D_8219A544);
            sBattleScene.scene->phaseStep++;
            break;

        case 4:
            M2C_FIELD(D_8219A544, u8**, 0x9CC)[1] |= 1;
            ((ActivePokemon*)D_8219A544)->thumbnail.displayObject.node.flags |= 1;
            func_82107160((ActivePokemon*)D_8219A544);
            func_821233EC(arg0, (ActivePokemon*)D_8219A544);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x32) != 0) {
                func_82124A40();
                func_82125C34(arg0);
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
                func_82135098((ActivePokemon*)D_8219A544);
                func_821255B4(arg0);
                BattleAnim_PlayMoveEffectScript((ActivePokemon*)D_8219A544, sp1C->usedMove);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                if (sp18->flags & 0x800) {
                    func_821020FC((s8*)D_8219A544);
                }
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (sp18->flags & 0x800) {
                BattleScene_ResetOwnerModelIfLoaded((ActivePokemon*)D_8219A544);
            }
            if (BattleAnim_IsSessionBusy((ActivePokemon*)D_8219A544) == 0) {
                Battle_ClearRuntimeFlags((ActivePokemon*)D_8219A544, 0x800);
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 2:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            BattleScene_RecenterCameraOnOwner(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x46) != 0) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 3:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            BattleScene_RecenterCameraOnOwner(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (D_8219A540->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

void func_80042A6C(s32);

/**
 * Phase 27 (moveEffectKind 0x1B): Bide, when it starts and while it stores energy.
 * In the per-move sweep only Bide entered phase 27.
 */
void BattleScene_PhaseBide(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_821255B4(arg0);
                func_80042A6C(0x2E);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x32) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (D_8219A540->state.runtime.usedMove == 0xFF) {
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
// no return type). BattleScene_PhaseHaze only matches when this call is seen as
// returning a value: it keeps $v0 away from the scene pointer there.
/**
 * Plays a Pokemon's pending model reactions from its state flags: 2 (reaction 1), 1 (resets
 * its roster byte 5, sets event track 0xB8, reaction 3) and the acting Pokemon's 0x80
 * (reaction 2), clearing each flag, then commits its pending status.
 */
s32 func_8212DD14(ActivePokemon* arg0) {
    ActivePokemonState* state = &arg0->state;
    BattleMon* sp28 = &arg0->teamRoster->pokemonPicked[arg0->state.rosterIndex];

    if (arg0->state.flags & 2) {
        func_82136708(1, arg0);
        arg0->displayObject.node.renderFlags |= 0x20;
        Battle_ClearRuntimeFlags(arg0, 2);
    }
    if (state->flags & 1) {
        M2C_FIELD(sp28, s8*, 5) = 0;
        func_8210568C(arg0, 0xB8, 1);
        func_82136708(3, arg0);
        Battle_ClearRuntimeFlags(arg0, 1);
    }
    if (state->flags & 0x80) {
        func_82136708(2, sActivePokemon[sBattleScene.scene->actingSide]);
        Battle_ClearRuntimeFlags(sActivePokemon[sBattleScene.scene->actingSide], 0x80);
    }
    ActivePokemon_CommitPendingStatus(arg0);
}

void func_82104C68(ActivePokemon*, s32);
s32 func_82105724(ActivePokemon*, s32);
void func_82105E64(ActivePokemon*);
/**
 * Phase 29: presents Haze (seen in play).
 */
void BattleScene_PhaseHaze(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 5) != 0) {
                func_8212C78C((s32)arg0);
                func_821255B4(arg0);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
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
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (D_8219A540->state.runtime.usedMove == 0xFF) {
                sBattleScene.scene->actionPass = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
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
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                BattleScene_ResetCameraFrameCounter();
                func_821224F4();
                func_82125570();
                Battle_ClearMessageCursor();
                func_82104C68((ActivePokemon*)D_8219A544, 8);
                sBattleScene.scene->unk_84.y = 0.5f;
                BattleAnim_Vec3fCopy(&sBattleScene.scene->savedCameraAt, &arg0->view.targetPosition);
                BattleAnim_Vec3fCopy(&sBattleScene.scene->savedCameraEye, &arg0->view.eyePosition);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            BattleAnim_ApproachF(&sBattleScene.scene->unk_84.y, 0.0f, 0.06f);
            func_8212311C(arg0, (ActivePokemon*)D_8219A544, sBattleScene.scene->unk_84.y);
            if (((ActivePokemon*)D_8219A544)->displayObject.position.y - D_FLT_82189354[((ActivePokemon*)D_8219A544)->displayObject.objectType][0] >= 800.0f) {
                BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            ActivePokemon_SetStateFlags((ActivePokemon*)D_8219A544, 0x200);
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
                func_82125C34(arg0);
            }
            break;
    }
}

void func_82123314(CameraNode*, ActivePokemon*);
f32 BattleScene_GetParticipantHeight(ActivePokemon*);
/**
 * Phase 13 (moveEffectKind 0x0D, set by Battle_Effect_Charge for Dig): the first turn of Dig.
 * In the per-move sweep only Dig entered phase 13.
 */
void BattleScene_PhaseDigUnder(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_821255B4(arg0);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
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
                if ((BattleAnim_IsAssetLoadBusy((ActivePokemon*)D_8219A544) == 0) && (((ActivePokemon*)D_8219A544)->displayObject.position.y <= (-BattleScene_GetParticipantHeight((ActivePokemon*)D_8219A544) * 2.5))) {
                    BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                    ActivePokemon_SetStateFlags((ActivePokemon*)D_8219A544, 0x4000);
                    ((ActivePokemon*)D_8219A544)->displayObject.node.renderFlags &= 0xFFDF;
                    sBattleScene.scene->phaseStep++;
                }
            } else if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                BattleMessage_ShowForSide(D_8219A520 + 0x148, sBattleScene.scene->actingSide);
                ActivePokemon_SetStateFlags((ActivePokemon*)D_8219A544, 0x4000);
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
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
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
 * Phase 14 (moveEffectKind 0x0E, set by Battle_Effect_Charge): the first turn of Razor Wind,
 * Solar Beam, Skull Bash and Sky Attack.
 * In the per-move sweep Razor Wind (13) went 2 -> 14.
 */
void BattleScene_PhaseChargeUp(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleCamera_PlayShot(D_8219A544, (s32)arg0, 3);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_821255B4(arg0);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212188C();
                func_8212189C();
                func_82104C68((ActivePokemon*)D_8219A544, 8);
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 1:
            if (func_82121798(0x28) != 0) {
                func_8211EE8C();
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_IsMoveKeyedRowWaitComplete((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_82124A40();
                func_82125C80(arg0);
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
                func_821255B4(arg0);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                func_8212C78C((s32)arg0);
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
                func_82104C68((ActivePokemon*)D_8219A544, 9);
                sBattleScene.scene->phaseStep++;
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
            }
            break;

        case 1:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            if (sBattleScene.scene->easeFovAfterUserShot == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            func_82124A40();
            func_82125C80(arg0);
            break;
    }
}

/**
 * Brings a Pokemon back to its normal height after an air or underground move: with flag
 * 0x200 it only restores the height; with 0x4008 it also makes the model opaque and visible
 * again and plays reaction 4.
 */
void func_8212E9C8(ActivePokemon* arg0) {
    u8* ptr = (u8*)arg0 + 0x78C;

    if (M2C_FIELD(ptr, u16*, 0x36) & 0x200) {
        arg0->displayObject.position.y = D_FLT_82189354[arg0->displayObject.objectType][0];
        Battle_ClearRuntimeFlags(arg0, 0x608);
    } else if (M2C_FIELD(ptr, u16*, 0x36) & 0x4008) {
        arg0->displayObject.lodFraction = 0xFF;
        func_82136708(4, arg0);
        arg0->displayObject.position.y = D_FLT_82189354[arg0->displayObject.objectType][0];
        arg0->displayObject.node.renderFlags &= ~0x2;
        arg0->displayObject.node.renderFlags |= 0x20;
        arg0->displayObject.node.flags |= 1;
        Battle_ClearRuntimeFlags(arg0, 0x4608);
    }
}


/**
 * Phase 20: a confused Pokemon hurts itself (seen in play: 75 to 63 HP). Shows the message, enters state row 15, and steps the HP down.
 */
void BattleScene_PhaseConfusionSelfHit(CameraNode* arg0) {
    func_821255EC(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98((ActivePokemon*)D_8219A544) == 0) {
                func_8212E9C8((ActivePokemon*)D_8219A544);
                BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            BattleScene_ResetAnimationStep();
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xF);
            BattleCamera_PlayTargetShot((ActivePokemon*)D_8219A544, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
            BattleScene_SetDamageShakeAmplitude((ActivePokemon*)D_8219A544);
            BattleAnim_QueueEffectList(8, (ActivePokemon*)D_8219A544);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 2:
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
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
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if (func_82122DFC(arg0, (ActivePokemon*)D_8219A544) != 0) {
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
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
            func_821255B4(arg0);
            BattleMessage_ShowForSide(D_8219A520 + 0xC8, sBattleScene.scene->actingSide);
            func_8212E9C8((ActivePokemon*)D_8219A544);
            BattleCamera_PlayShot(D_8219A544, arg0, 3);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            BattleCamera_PlayShot(D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
                BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 9);
                sBattleScene.scene->phaseStep += 1;
                ActivePokemon_CommitPendingStatus((ActivePokemon*)D_8219A544);
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
            func_82125C80(arg0);
            break;
    }
}

/**
 * Picks one of three target camera framings at random for Pokemon arg0 and runs it.
 */
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

/**
 * Picks one of four or five target framings (func_8210C020(4)) for Pokemon arg0 and runs it.
 */
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

/**
 * Plays the target camera shot for the move the other side used, from field 6 of the move
 * table D_80073D90 (4 and 6 pick a random framing, 5 reuses the last one).
 */
void func_8212F044(CameraNode* arg0) {
    s32 other = sBattleScene.scene->actingSide == 0;
    ActivePokemon* opp = sActivePokemon[other];
    BattleMonRuntime* runtime = &opp->state.runtime;

    if (D_80073D90[runtime->usedMove - 1].unk_06 == 5) {
        BattleCamera_PlayTargetShot(opp, arg0, D_8219A568);
    } else if (D_80073D90[runtime->usedMove - 1].unk_06 == 4) {
        func_8212EEC0(opp, arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_06 == 6) {
        func_8212EF74(opp, arg0);
    } else {
        BattleCamera_PlayTargetShot(opp, arg0, D_80073D90[runtime->usedMove - 1].unk_06);
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
        func_82125384();
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
                BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
                BattleCamera_PlayTargetShot((ActivePokemon*)D_8219A544, arg0, 3);
                BattleCamera_CaptureModelOrbit((ActivePokemon*)D_8219A544, arg0);
                func_82121EB0((ActivePokemon*)D_8219A544);
                BattleScene_ResetAnimationStep();
                ModelAnim_SetAnimation((DisplayObject*)D_8219A544, *sp1C);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            sBattleScene.scene->cameraPresetId = 1;
            BattleCamera_PlayTargetShot((ActivePokemon*)D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                Battle_ClearMessageCursor();
                BattleMessage_ShowForSide(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            sBattleScene.scene->cameraPresetId = 1;
            BattleCamera_PlayTargetShot((ActivePokemon*)D_8219A544, arg0, 3);
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
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            BattleCamera_PlayTargetShot((ActivePokemon*)D_8219A544, arg0, 3);
            if ((D_8219A560 != 0) && (D_8219A564 != 0)) {
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
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
    ActivePokemonState* sp1C = &D_8219A540->state;

    func_821255EC(arg0);
    sBattleScene.scene->cameraPresetId = 2;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            if (sp1C->flags & 0x200) {
                BattleCamera_PlayTargetShot(D_8219A540, arg0, D_8219A568 = 2);
            } else {
                BattleCamera_PlayTargetShot(D_8219A540, arg0, D_8219A568 = BattleAnim_RandomRange(2));
            }
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xC);
            BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
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

/**
 * Phase 22 (moveEffectKind 0x16): a status move hits the target. Set by Battle_Effect_Sleep,
 * Battle_Effect_Poison, Battle_Effect_Paralyze and Battle_Effect_Confuse. Seen in play for
 * Confuse Ray.
 */
void BattleScene_PhaseInflictStatus(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    func_821255EC(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            func_8212F044(arg0);
            BattleCamera_CaptureModelOrbit(D_8219A540, arg0);
            BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xE);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            func_82122DFC(arg0, D_8219A540);
            if (sBattleScene.scene->stepFrameTimer == 0x1E) {
                ActivePokemon_CommitPendingStatus(D_8219A540);
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

/**
 * Phase 26 (moveEffectKind 0x1A, set by Battle_Effect_LowerStat): a move that lowers the target's
 * stat.
 * In the per-move sweep (moves 1-33) only Sand Attack ran it.
 */
void BattleScene_PhaseLowerStat(CameraNode* arg0) {
    sBattleScene.scene->cameraPresetId = 2;
    func_821255EC(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            BattleScene_ResetAnimationStep();
            BattleScene_ResetCameraFrameCounter();
            ActivePokemon_CommitPendingStatus(D_8219A540);
            func_8212F044(arg0);
            BattleCamera_CaptureModelOrbit(D_8219A540, arg0);
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xB);
            BattleMessage_ShowForSide(D_8219A520 + 0x208, sBattleScene.scene->actingSide);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            func_82122DFC(arg0, D_8219A540);
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x6E) != 0) {
                sBattleScene.scene->phaseStep += 1;
                func_8211EE8C();
                BattleScene_ResetCameraFrameCounter();
            }
            break;

        case 2:
            if (func_82124BF8(D_8219A540) == 0) {
                func_82124E80();
                D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
                D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
                func_82122A7C(arg0, D_8219A540);
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
    BattleMonRuntime* runtime = &((ActivePokemon*)D_8219A544)->state.runtime;

    sBattleScene.scene->cameraPresetId = 2;
    func_821255EC(arg0);

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleAnim_CleanupEffects(1);
            BattleCamera_PlayTargetShot(D_8219A540, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
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

/**
 * Camera and HP sequence for a hit on the target: shows the target's shot and the move
 * message, steps the target's displayed HP, then switches to the user's shot and steps
 * both sides' HP until they catch up and the user's animation ends, then runs the HP bar
 * step.
 */
void func_8212F9FC(CameraNode* arg0) {
    func_821255EC(arg0);
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_82135098((ActivePokemon*)D_8219A544);
            func_82135098(D_8219A540);
            func_8213B31C(1);
            sBattleScene.scene->cameraPresetId = 2;
            func_82104C68((ActivePokemon*)D_8219A544, 4);
            BattleCamera_PlayTargetShot(D_8219A540, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            func_82121EB0(D_8219A540);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            sBattleScene.scene->cameraPresetId = 2;
            D_8219A564 = Battle_StepPartyHpToDisplay(D_8219A540);
            if (sBattleScene.scene->stepFrameTimer == 0x3C) {
                Battle_ClearMessageCursor();
            }
            if ((D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounter(0x96) != 0)) {
                BattleCamera_PlayTargetShot((ActivePokemon*)D_8219A544, arg0, D_8219A568 = BattleAnim_RandomRange(4));
                Audio_FadeAndClearStoredSounds();
                func_8213B31C(1);
                func_821365E8(4, (ActivePokemon*)D_8219A544);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 2:
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x5A) != 0) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            D_8219A560 = Battle_StepPartyHpToDisplay(D_8219A540);
            D_8219A564 = Battle_StepPartyHpToDisplay((ActivePokemon*)D_8219A544);
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
 * and effect list 10 (unk_4D bit 0x80), then flips the acting side and enters BattleScene_PhaseConfusionSelfHit if the
 * acting Pokemon reaches 0 HP.
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
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                func_82124894(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
                func_82104C68(sActivePokemon[sBattleScene.scene->actingSide], 0xD);
                if (sp2C[0x15] & 0x18) {
                    BattleMessage_ShowForSide(D_8219A520 + 0x248, sBattleScene.scene->actingSide);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0xE);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0xE);
                    if (sp2C[0x15] & 0x10) {
                        BattleAnim_QueueEffectList(6, (ActivePokemon*)D_8219A544);
                    } else {
                        BattleAnim_QueueEffectList(5, (ActivePokemon*)D_8219A544);
                    }
                    sBattleScene.scene->phaseStep++;
                } else {
                    func_82135098(D_8219A540);
                    BattleMessage_ShowForSide(D_8219A520 + 0x288, sBattleScene.scene->actingSide);
                    Audio_PlayCommand(0x22, 0, 0);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    BattleAnim_QueueEffectList(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->phaseStep = 3;
                }
            }
            break;

        case 2:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                if (func_82107CA0(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                    func_82125570();
                    BattleScene_SetPhase(arg0, 5);
                    sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
                } else if (sp2C[0x4D] & 0x80) {
                    func_82135098(D_8219A540);
                    Audio_PlayCommand(0x22, 0, 0);
                    BattleMessage_ShowForSide(D_8219A520 + 0x288, sBattleScene.scene->actingSide);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    BattleAnim_QueueEffectList(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->phaseStep++;
                } else {
                    sBattleScene.scene->phaseStep = 4;
                }
            }
            break;

        case 3:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
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
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}


void func_82106374(ActivePokemon*);
s32 func_82124A50(ActivePokemon*);
void func_82108C0C(ActivePokemon*);
void BattleAnim_QueueEffectList(u8 arg0, s32 arg1);
void func_821237B0(CameraNode*, ActivePokemon*);
void func_82123684(CameraNode*, ActivePokemon*);
void func_82134EBC(ActivePokemon*, s32);
s32 func_82124BF8(ActivePokemon*);
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
            func_82135098((ActivePokemon*)D_8219A544);
            func_82106374((ActivePokemon*)D_8219A544);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            if (func_82124A50(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                func_82108C0C((ActivePokemon*)D_8219A544);
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                BattleAnim_QueueEffectList(9, (ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                func_821237B0(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
                BattleMessage_ShowForSide(D_8219A520 + 0x408, sBattleScene.scene->actingSide);
                self->hp = self->pendingHp;
                other->hp = other->pendingHp;
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
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = Battle_StepPartyHpToDisplay(sActivePokemon[!sBattleScene.scene->actingSide]);
            func_82123684(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
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
            BattleScene_CleanupParticipantEffectMode((ActivePokemon*)D_8219A544);
            func_82106354(sActivePokemon[sBattleScene.scene->actingSide]);
            if (func_82124A50(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                func_82108C0C((ActivePokemon*)D_8219A544);
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                BattleScene_ResetCameraFrameCounter();
                BattleMessage_ShowForSide(D_8219A520 + 0x348, !sBattleScene.scene->actingSide);
                BattleAnim_QueueEffectList6(3, D_8219A540);
                Audio_PlayCommand(0x23, 0, 0);
                func_82124894(arg0, D_8219A540);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(0x37) != 0) {
                func_8211EE8C();
                BattleMessage_ShowForSide(D_8219A520 + 0x2C8, !sBattleScene.scene->actingSide);
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
