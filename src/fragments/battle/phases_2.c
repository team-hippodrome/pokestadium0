/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "audio_commands.h"
#include "geo_node.h"
#include "matrix.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK ActivePokemon_SetModelTransform(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK func_8211EE8C();
M2C_UNK func_82125384();
M2C_UNK func_821365B0(M2C_UNK, s8 *, s8 *, M2C_UNK, s32);
extern ActivePokemon* D_8219A540;
extern M2C_UNK D_82199DE0;
extern Vec3f D_8218B630;
extern s32 D_8219A520;
extern s32 D_8219A544;
extern s8 *D_8219A5A0;
s32 ActivePokemon_GetNickname(ActivePokemon*);
s32 BattleMessage_Format(s32, s32, s32, ...);
s32 Battle_StepPartyHpToDisplay(ActivePokemon*);
s32 func_8001101C(s8 *, M2C_UNK *);
s32 func_82101FD4(s32);
s32 func_82107CA0(ActivePokemon*);
void BattleCamera_PlayShot(s32, s32, s32);
void BattleMessage_ShowForSide(s32, s32);
void BattleScene_InitTurnPresentation(CameraNode* arg0);
void func_80041914(u8, u8);
void func_82104C68(ActivePokemon*, s32);
void func_82106354(ActivePokemon*);
void func_82106374(ActivePokemon*);
void func_82107408(ActivePokemon*);
void func_82108C0C(ActivePokemon*);
void func_82124874(void*, void*);
void func_82124A40(void);
void func_82135098(ActivePokemon*);

/**
 * Phase 35. Same residual damage presentation as BattleScene_PhaseResidualDamageAfterMove for a Pokemon that
 * has no move this turn (usedMove high nibble 0xF); entered by BattleScene_PrepareResidualStatusPresentation.
 * Seen in play (2026-11-13) (unattended all-Metronome Free Battle with randomized teams, battle 2
 * turn 16): ran twice. Teams carried random sleep, poison, burn, freeze and paralysis; the exact
 * status was not logged.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleScene_PhaseResidualDamageWithoutMove(CameraNode* arg0) {
    u8* sp2C = (u8*)sActivePokemon[sBattleScene.scene->actingSide] + 0x7C6;
    u8* sp28 = (u8*)sActivePokemon[!sBattleScene.scene->actingSide] + 0x7C6;
    ActivePokemon* cur = sActivePokemon[sBattleScene.scene->actingSide];

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_82135098((ActivePokemon*)D_8219A544);
            func_82106374((ActivePokemon*)D_8219A544);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            func_82106354(cur);
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
                    BattleMessage_ShowForSide(D_8219A520 + 0x288, sBattleScene.scene->actingSide);
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


/**
 * Phase 33. Shows residual damage on the acting Pokemon only (the other HP bar is treated as settled). If
 * it reaches 0 HP, flips the acting side and enters BattleScene_PhaseFaintAfterResidualDamage; otherwise
 * continues with BattleScene_CleanupActionAndAdvance.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void BattleScene_PhaseResidualDamageFaintCheck(CameraNode* arg0) {
    u8* sp1C = (u8*)sActivePokemon[sBattleScene.scene->actingSide] + 0x7C6;
    u8* sp18 = (u8*)sActivePokemon[!sBattleScene.scene->actingSide] + 0x7C6;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_82135098((ActivePokemon*)D_8219A544);
            func_82106374((ActivePokemon*)D_8219A544);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            func_82108C0C((ActivePokemon*)D_8219A544);
            Audio_FadeAndClearStoredSounds();
            BattleAnim_CleanupEffects(1);
            func_82124874(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            func_82104C68(sActivePokemon[sBattleScene.scene->actingSide], 0xD);
            BattleMessage_ShowForSide(D_8219A520 + 0x248, sBattleScene.scene->actingSide);
            M2C_FIELD(sp1C, u16*, 0xC) = M2C_FIELD(sp1C, u16*, 0xE);
            M2C_FIELD(sp18, u16*, 0xC) = M2C_FIELD(sp18, u16*, 0xE);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 2:
            func_82124874(arg0, sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A560 = Battle_StepPartyHpToDisplay(sActivePokemon[sBattleScene.scene->actingSide]);
            D_8219A564 = 1;

            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                if (func_82107CA0(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
                    func_82125570();
                    BattleScene_SetPhase(arg0, 0x22);
                    sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
                } else {
                    func_8212562C();
                }
            }
            break;
    }
}

/**
 * When the Pokemon is frozen (status 0x20), stops its category-1 particles and sets render
 * flag 0x20.
 */
void func_82130D48(ActivePokemon* active_pokemon) {
    BattleMon* party_pokemon = &active_pokemon->teamRoster->pokemonPicked[active_pokemon->thumbnail.shownRosterIndex];

    if (party_pokemon->statusCondition & 0x20) {
        BattleAnim_StopOwnerCategoryParticles(1, active_pokemon);
        active_pokemon->displayObject.node.renderFlags |= 0x20;
    }
}


/**
 * Phase 11: the acting side withdraws its Pokemon for a switch (action 0x0F, through
 * BattleScene_TryStartSwitchAction). Ran in play when 1P switched from the Pokemon menu.
 */
void BattleScene_PhaseWithdraw(CameraNode* arg0) {
    u8* sp2C = (u8*)sActivePokemon[sBattleScene.scene->actingSide] + 0x78C;
    ActivePokemon* temp_s0 = sActivePokemon[sBattleScene.scene->actingSide];

    if (sBattleScene.scene->actingSide) {}  // karodo

    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_821255EC(arg0);
            BattleCamera_PlayShot((s32)temp_s0, (s32)arg0, 2);
            BattleScene_ResetCameraFrameCounter();
            BattleMessage_ShowForSide(D_8219A520 + 0x1C8, sBattleScene.scene->actingSide);
            sBattleScene.scene->phaseStep++;
            break;

        case 1:
            BattleScene_ApproachCameraZoom(arg0, temp_s0);
            func_82104C68(temp_s0, 2);
            func_82130D48(temp_s0);
            sBattleScene.scene->phaseStep++;
            break;

        case 2:
            BattleScene_ApproachCameraZoom(arg0, temp_s0);
            if (sBattleScene.scene->stepFrameTimer == 0x23) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x69) != 0) {
                Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)arg0 + 0xB4), temp_s0->facingDirection * -150.0f, 0.0, 0.0f);
                if (sBattleScene.scene && sBattleScene.scene) {}  // FAKE
                Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)arg0 + 0xA8), temp_s0->facingDirection * -50.0f, 5.0f, 0.0f);
                BattleScene_SetParticipantModelTransform(temp_s0, 2, 0);
                BattleAnim_QueueEffectList3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 3:
            if (temp_s0->pokeBall.position.y == 2.5f) {
                temp_s0->pokeBall.node.renderFlags |= 0x20;
            }
            if (ModelAnim_IsAnimationDone((DisplayObject*)((u8*)temp_s0 + 0x624)) == 1) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 4:
            temp_s0->pokeBall.node.flags &= ~1;
            *M2C_FIELD(temp_s0, u8**, 0x85C) |= 0x80;
            sBattleScene.scene->phaseStep++;
            break;

        case 5:
            if (*M2C_FIELD(temp_s0, u8**, 0x85C) & 0x10) {
                *M2C_FIELD(temp_s0, u8**, 0x85C) &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                func_82107408(temp_s0);
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                Audio_PlayCommand(2, 0, 0);
                BattleScene_RebindParticipantTeamMember(temp_s0, sp2C[0x2D]);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 6:
            func_82104C68(temp_s0, 0x12);
            BattleCamera_PlayShot((s32)temp_s0, (s32)arg0, 3);
            BattleCamera_CaptureModelOrbit(temp_s0, arg0);
            BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
            BattleScene_ResetCameraFrameCounter();
            sBattleScene.scene->phaseStep++;
            break;

        case 7:
            func_82122A7C(arg0, temp_s0);
            if (sBattleScene.scene->stepFrameTimer == 0x1E) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_IsRowWaitCompleteWithEventCount(temp_s0, 0x64) != 0) {
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(2);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)temp_s0 + 0x30), 1.0f, 1.0f, 1.0f);
                func_8212562C();
                M2C_FIELD(sp2C, u16*, 0x36) &= ~0x3800;
            }
            break;
    }
}


/**
 * Phase 18: sends out the replacement after a faint (seen in play, on the turn after the faint).
 */
void BattleScene_PhaseSendOutAfterFaint(CameraNode* arg0) {
    ActivePokemonState* sp3C = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    ActivePokemonState* sp38 = &sActivePokemon[!sBattleScene.scene->actingSide]->state;
    ActivePokemon* temp_s0 = sActivePokemon[sBattleScene.scene->actingSide];
    BattleMonRuntime* sp2C = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;

    sBattleScene.scene->cameraPresetId = 4;

    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_821255EC(arg0);
            Vec3f_SetComponentsDuplicate(&arg0->view.targetPosition, temp_s0->facingDirection * -150.0f, 0.0, 0.0f);
            Vec3f_SetComponentsDuplicate(&arg0->view.eyePosition, temp_s0->facingDirection * -50.0f, 5.0f, 0.0f);
            Vec3f_SetComponentsDuplicate(&temp_s0->displayObject.position, temp_s0->facingDirection * -150.0f, 25.0f, 0.0f);
            BattleScene_ResetCameraFrameCounter();
            Battle_ClearMessageCursor();
            BattleMessage_ShowForSide(D_8219A520 + 0x88, sBattleScene.scene->actingSide);
            BattleAnim_LoadModeResourceList(temp_s0->sessionTeams, 3);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 1:
            if (BattleAnim_TryRegisterAssetTables(temp_s0) != 0) {
                temp_s0->sessionTeams->displayModel = sp2C->species;
                temp_s0->sessionTeams->displayMon = &temp_s0->teamRoster->pokemonPicked[temp_s0->state.rosterIndex];
                BattleScene_SetParticipantModelTransform(temp_s0, 2, 0);
                BattleAnim_QueueEffectList3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 2:
            if (temp_s0->pokeBall.position.y == 2.5f) {
                temp_s0->pokeBall.node.renderFlags |= 0x20;
            }

            if (ModelAnim_IsAnimationDone(&temp_s0->pokeBall) == 1) {
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 3:
            temp_s0->pokeBall.node.flags &= ~1;
            temp_s0->sessionTeams->modelFlags |= 0x80;
            sBattleScene.scene->phaseStep += 1;
            break;

        case 4:
            if (temp_s0->sessionTeams->modelFlags & 0x10) {
                temp_s0->sessionTeams->modelFlags &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                BattleThumbnail_TickOwnerCameraFraming(temp_s0);
                Audio_PlayCommand(2, 0, 0);
                temp_s0->thumbnail.shownRosterIndex = sp3C->rosterIndex;
                temp_s0->thumbnail.shownTeamMemberIndex = sp3C->teamMemberIndex;
                BattleScene_RebindParticipantTeamMember(temp_s0, sp3C->menuTeamMemberIndex);
                BattleScene_ResetCameraFrameCounter();
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                BattleScene_EnterStateRow(temp_s0, 0x12);
                BattleCamera_PlayShot((s32)temp_s0, (s32)arg0, 3);
                BattleCamera_CaptureModelOrbit(temp_s0, arg0);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 5:
            BattleCamera_PlayShot((s32)temp_s0, (s32)arg0, 3);
            BattleCamera_CaptureModelOrbit(temp_s0, arg0);
            sBattleScene.scene->phaseStep += 1;
            break;

        case 6:
            func_82122A7C(arg0, temp_s0);
            if (BattleScene_AdvanceCameraFrameCounter(0x15) != 0) {
                Battle_ClearMessageCursor();
                BattleAnim_ResetFreezeStatusAndRestoreAnimation(temp_s0);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 7:
            func_82122A7C(arg0, temp_s0);
            if (BattleScene_IsRowWaitCompleteWithEventCount(temp_s0, 0x32) != 0) {
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(2);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                Vec3f_SetComponentsDuplicate(&temp_s0->displayObject.scale, 1.0f, 1.0f, 1.0f);
                if (sp38->faintState != 0x10) {
                    sBattleScene.scene->actionPass = 3;
                }
                sBattleScene.scene->transitionStyle = 2;
                func_8212562C();
                sp3C->flags &= 0xC7FF;
            }
            break;
    }
}

/**
 * Runs the per-frame battle presentation phase selected by scene->phase and phaseStep. Move-specific phases
 * (7, 12-15, 17, 25, 27-31, 38) are entered through BattleScene_PhaseDispatchMoveEffect.
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it was running the
 * presentation from the frame after Battle_StartTurn (phase 0, then 2).
 */
void BattleScene_UpdatePhase(CameraNode* arg0) {
    func_82125FD0();
    switch (sBattleScene.scene->phase) {
    case 0:
        BattleScene_InitTurnPresentation(arg0);
        BattleScene_SetPhase(arg0, 1);
        /* fallthrough */
    case 1:
        BattleScene_PhaseCommand(arg0);
        break;
    case 2:
        BattleScene_PhaseFirstAction(arg0);
        break;
    case 3:
        BattleScene_PhaseSecondAction(arg0);
        break;
    case 4:
        BattleScene_PhaseEndTurn((s32)arg0);
        break;
    case 7:
        BattleScene_PhaseSelfEffect(arg0);
        break;
    case 30:
        BattleScene_PhaseExplosion(arg0);
        break;
    case 29:
        BattleScene_PhaseHaze(arg0);
        break;
    case 28:
        BattleScene_PhaseMoveFailedMessage(arg0);
        break;
    case 25:
        BattleScene_PhaseSubstitute(arg0);
        break;
    case 21:
        BattleScene_PhaseHeal(arg0);
        break;
    case 27:
        BattleScene_PhaseBide(arg0);
        break;
    case 12:
        BattleScene_PhaseFlyUp(arg0);
        break;
    case 13:
        BattleScene_PhaseDigUnder(arg0);
        break;
    case 14:
        BattleScene_PhaseChargeUp(arg0);
        break;
    case 15:
        BattleScene_PhaseTransform(arg0);
        break;
    case 17:
        BattleScene_PhaseCannotMove(arg0);
        break;
    case 31:
        BattleScene_PhaseFullParalysis(arg0);
        break;
    case 20:
        BattleScene_PhaseConfusionSelfHit(arg0);
        break;
    case 8:
        BattleScene_PhaseMoveMissed(arg0);
        break;
    case 22:
        BattleScene_PhaseInflictStatus(arg0);
        break;
    case 32:
        BattleScene_PhaseDisable(arg0);
        break;
    case 23:
        func_8212F9FC(arg0);
        break;
    case 10:
        func_82130494(arg0);
        break;
    case 6:
        BattleScene_PhaseResidualDamageAfterMove(arg0);
        break;
    case 33:
        BattleScene_PhaseResidualDamageFaintCheck(arg0);
        break;
    case 35:
        BattleScene_PhaseResidualDamageWithoutMove(arg0);
        break;
    case 9:
        BattleScene_PhaseRecoilDamage(arg0);
        break;
    case 16:
        BattleScene_PhaseCrashDamage(arg0);
        break;
    case 11:
        BattleScene_PhaseWithdraw(arg0);
        break;
    case 18:
        BattleScene_PhaseSendOutAfterFaint(arg0);
        break;
    case 26:
        BattleScene_PhaseLowerStat(arg0);
        break;
    case 5:
        BattleScene_PhaseFaint(arg0);
        break;
    case 34:
        func_82126E34(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-13) with scene mode forced to 4 at scene start, func_82134374 called this
 * directly (not through BattleScene_UpdateIntroSequence's case 0): it set rotationX to 0x3C6E and
 * rotationY to 0, and the next frame's update was already at step 1.
 */
void BattleScene_IntroStepInitOverheadCamera(CameraNode* arg0) {
    BattleScene_ResetCameraFrameCounter();
    BattleScene_SetCameraAtFromPosition(arg0, D_8218B630, 0, 0, 0.0f, 0.0f);
    BattleScene_SetCameraEyeAndStoreAngles(arg0, D_8218B630, 0x3C6E, sBattleScene.scene->rotationY = 0, sBattleScene.scene->orbitDistance = D_FLT_82196668, 0.0f);
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    sBattleScene.scene->stageScale = D_FLT_8219666C;
    Battle_SetStageScale(sBattleScene.scene->stageScale);
    Audio_PlayCommand(4, 0, 0);
    func_80041914(sActivePokemon[0]->teamRoster->numberOfPokemonBrought, sActivePokemon[1]->teamRoster->numberOfPokemonBrought);
    BattleAnim_LoadModeResourceList(sActivePokemon[0]->sessionTeams, 3);
    sBattleScene.scene->phaseStep += 1;
}

/**
 * Seen in play (2026-11-13) with scene mode forced to 4 it ran on the two frames after the overhead
 * camera was set up, then the step moved to 2.
 */
void BattleScene_IntroStepWaitForAssets(s32 arg0) {
    if (func_82101FD4(D_82199DE0) != 0) {
        sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
    }
}

s32 func_80041374(s32, u32);
/**
 * Seen in play (2026-11-13) with scene mode forced to 4 the screen showed the arena from directly
 * above, small and rotating; rotationY fell by 0x16C per call (0 to -21476 over about 60 calls)
 * until the step moved to 3 (BattleScene_OpeningStepThrowSide1).
 */
void BattleScene_IntroStepSpinOverheadCamera(CameraNode* arg0) {
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    BattleAnim_ApproachF(&sBattleScene.scene->orbitDistance, 10000.0f, 0.025f);
    BattleScene_SetCameraAtFromPosition(arg0, D_8218B630, 0, 0, 0.0f, 0.0f);
    BattleScene_SetCameraEyeAndStoreAngles(arg0, D_8218B630, 0x3C6E, sBattleScene.scene->rotationY -= 0x16C, sBattleScene.scene->orbitDistance, 0.0f);
    BattleAnim_ApproachF(&sBattleScene.scene->stageScale, 1.0f, 0.06f);
    Battle_SetStageScale(sBattleScene.scene->stageScale);
    if (sBattleScene.scene->stepFrameTimer == 0x3C) {
        func_80041374(4, 0x3C);
    }
    if (func_821217DC(0x50) != 0) {
        Audio_PlayCommand(1, 0xFE, 0);
        Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)arg0 + 0xB4), 0.0f, 75.0f, 0.0f);
        Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)arg0 + 0xA8), -1.79f, 0.075f, 155.2f);
        ActivePokemon_SetModelTransform((s8*)sActivePokemon[0], 1, 0);
        func_821365B0(8, (s8*)sActivePokemon[0], (s8*)sActivePokemon[0], 0xFF, 0xFF);
        Battle_SetStageScale(1.0f);
        sBattleScene.scene->phaseStep += 1;
        sBattleScene.scene->verticalFieldOfView = M2C_FIELD(arg0, f32*, 0x2C);
        M2C_FIELD(arg0, f32*, 0x2C) = 40.0f;
    }
}

/**
 * Battle opening, step 4: once side 0's throw has finished, starts side 1's Poke Ball throw
 * (model transform 1, effect list 10).
 * Seen in play: a Poke Ball with a sparkle trail rises from the trainer box.
 */
void BattleScene_OpeningStepThrowSide1(s32 arg0) {
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), f32 *, 0x64C) == 0.0f) {
        Audio_PlayCommand(1, 1, 0);
        ActivePokemon_SetModelTransform(M2C_FIELD(&D_82199DE0, s8 **, 4), 1, 0);
        func_821365B0(0xA, M2C_FIELD(&D_82199DE0, s8 **, 4), M2C_FIELD(&D_82199DE0, s8 **, 4), 0xFF, 0xFF);
        sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
    }
}

void func_8212254C(s8*, void*, Vec3f, s32, s32, f32, f32);
void func_82122628(void*, Vec3f, s32, s32, f32, f32);
/**
 * Battle opening, step 5: once side 1's throw has finished, frames side 0 and starts its Poke
 * Ball landing (model transform 2, effect list 11).
 * Seen in play: the camera then shows the field with the landing ball's shadow.
 */
void BattleScene_OpeningStepLandSide0Ball(void* arg0) {
    Vec3f sp34;

    sp34.y = 0.0f;
    sp34.z = 0.0f;
    sp34.x = -150.0f;
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), f32 *, 0x64C) == 0) {
        if (sBattleScene.scene->mode == 4) {
            M2C_FIELD(arg0, f32 *, 0x2C) = sBattleScene.scene->verticalFieldOfView;
        }
        func_8212254C(M2C_FIELD(&D_82199DE0, s8 **, 0), arg0, sp34, 0, 0, 0.0f, 0.0f);
        ActivePokemon_SetModelTransform(M2C_FIELD(&D_82199DE0, s8 **, 0), 2, 0);
        func_821365B0(0xB, M2C_FIELD(&D_82199DE0, s8 **, 0), M2C_FIELD(&D_82199DE0, s8 **, 0), 0xFF, 0xFF);
        func_82122628(arg0, sp34, sBattleScene.scene->rotationX = 0x71C, 0x4000, sBattleScene.scene->orbitDistance = 250.0f, 0.0f);
        sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
    }
}

/**
 * Intro camera step: clears node flag 1 on both models, zooms toward distance 60
 * and turns the camera angle to 0 around (-150, 0, 0). Once the angle is at least 46 and
 * side 0's model scale is 2.5, plays sound command 2 and advances the phase step.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleScene_IntroPanCamera(CameraNode* arg0) {
    Vec3f sp2C;

    sp2C.y = 0.0f;
    sp2C.z = 0.0f;
    sp2C.x = -150.0f;
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    BattleAnim_ApproachF(&sBattleScene.scene->orbitDistance, 60.000004f, 0.1f);
    BattleAnim_StepToS16(&sBattleScene.scene->rotationX, 0, 0x1E);
    BattleScene_SetCameraEyeFromPosition(arg0, sp2C, sBattleScene.scene->rotationX, 0x4000, sBattleScene.scene->orbitDistance, 0.0f);

    if ((sBattleScene.scene->rotationX >= 0x2E) && (sActivePokemon[0]->pokeBall.position.y == 2.5f)) {
        Audio_PlayCommand(2, 0, 0);
        sActivePokemon[0]->pokeBall.node.renderFlags |= 0x20;
        sBattleScene.scene->phaseStep += 1;
    }
}

/**
 * Battle opening, step 7: waits for side 0's Poke Ball animation to end.
 * Seen in play: ends with the white flash of side 0's ball opening.
 */
void BattleScene_OpeningStepWaitSide0Ball(s32 arg0) {
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (func_8001101C(M2C_FIELD(&D_82199DE0, s8 **, 0) + 0x624, &D_82199DE0) == 1) {
        sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
    }
}

/**
 * Battle start: sends out side 0's Pokemon with ゆけっ！%s (Go! %s).
 * Seen in play (2026-11-12): at the start of a COM free battle it first ran as 1P's Poké Ball
 * burst open, before COM's send-out.
 */
void BattleScene_SendOutSide0(CameraNode* arg0) {
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    func_821365B0(3, (s8*)sActivePokemon[0], (s8*)sActivePokemon[0], 0xFF, 0xFF);
    BattleMessage_Format(D_8219A520 + 0x448, 0, (s32)D_82196650, ActivePokemon_GetNickname(sActivePokemon[0]));
    func_8211EE8C();
    BattleMessage_ShowForSide(D_8219A520 + 0x448, 0);
    sActivePokemon[0]->displayObject.node.flags |= 1;
    sActivePokemon[0]->pokeBall.node.flags &= ~1;
    BattleCamera_PlayShot((s32)sActivePokemon[0], (s32)arg0, 3);
    BattleCamera_CaptureModelOrbit(sActivePokemon[0], arg0);
    func_82104C68(sActivePokemon[0], 0x10);
    sBattleScene.scene->substepFrameCounter = 0;
    sBattleScene.scene->phaseStep++;
}

/**
 * Battle opening, step 9: holds the camera on side 0's Pokemon after BattleScene_SendOutSide0
 * until its send-out row finishes.
 * Seen in play: holds on the flash with 「ゆけっ！イワイワ」 (1P's lead).
 */
void BattleScene_OpeningStepWaitSide0SendOut(CameraNode* arg0) {
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    func_82122A7C(arg0, sActivePokemon[0]);
    sBattleScene.scene->substepFrameCounter++;
    if (sBattleScene.scene->substepFrameCounter == 0x28) {
        func_8211EE8C();
    }
    if (func_821057D4(sActivePokemon[0], 0x3C) != 0) {
        sBattleScene.scene->phaseStep++;
    }
}

/**
 * Battle start: sends out side 1's Pokemon with ゆけっ！%s (Go! %s).
 * Seen in play (2026-11-12): at the start of the same battle it first ran right after 1P's Onix
 * had come out, for COM's send-out.
 */
void BattleScene_SendOutSide1(CameraNode* arg0) {
    Audio_PlayCommand(2, 0, 0);
    BattleAnim_QueueEffectList3(3, sActivePokemon[1], sActivePokemon[1], 0xFF, 0xFF);
    BattleMessage_Format(D_8219A520 + 0x488, 0, (s32)D_8219665C, ActivePokemon_GetNickname(sActivePokemon[1]));
    func_8211EE8C();
    BattleMessage_ShowForSide(D_8219A520 + 0x488, 1);
    BattleScene_ResetCameraFrameCounter();
    sActivePokemon[1]->displayObject.node.flags |= 1;
    BattleCamera_PlayShot((s32)sActivePokemon[1], (s32)arg0, 3);
    BattleCamera_CaptureModelOrbit(sActivePokemon[1], arg0);
    func_82104C68(sActivePokemon[1], 0x10);
    sBattleScene.scene->phaseStep++;
    sBattleScene.scene->substepFrameCounter = 0;
}

/**
 * Battle opening, step 11: holds the camera on side 1's Pokemon after BattleScene_SendOutSide1,
 * then ends the opening.
 * Seen in play: holds on the flash with 「ゆけっ！ニドのすけ」 (the COM's lead), then the command menu
 * opens.
 */
void BattleScene_OpeningStepWaitSide1SendOut(CameraNode* arg0) {
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    func_82122A7C(arg0, sActivePokemon[1]);
    sBattleScene.scene->substepFrameCounter++;
    if (sBattleScene.scene->substepFrameCounter == 0x28) {
        Battle_ClearMessageCursor();
    }
    if (BattleScene_IsRowWaitCompleteWithEventCount(sActivePokemon[1], 0x3C) != 0) {
        Battle_ClearMessageCursor();
        func_82125384();
    }
}
