/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_3438B0.h"

/**
 * Phase 35. Same residual damage presentation as BattleScene_PhaseResidualDamageAfterMove for a Pokemon that
 * has no move this turn (usedMove high nibble 0xF); entered by BattleScene_PrepareResidualStatusPresentation.
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
                        func_821366B0(6, (ActivePokemon*)D_8219A544);
                    } else {
                        func_821366B0(5, (ActivePokemon*)D_8219A544);
                    }
                    sBattleScene.scene->phaseStep++;
                } else {
                    BattleMessage_ShowForSide(D_8219A520 + 0x288, sBattleScene.scene->actingSide);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    func_821366B0(0xA, (ActivePokemon*)D_8219A544);
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
                    func_800407B0(0x22, 0, 0);
                    BattleMessage_ShowForSide(D_8219A520 + 0x288, sBattleScene.scene->actingSide);
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

void func_82130D48(ActivePokemon* active_pokemon) {
    BattleMon* party_pokemon = &active_pokemon->teamRoster->pokemonPicked[M2C_FIELD(active_pokemon, s32*, 0x9D0)];

    if (party_pokemon->statusCondition & 0x20) {
        BattleAnim_StopOwnerCategoryParticles(1, active_pokemon);
        active_pokemon->displayObject.node.renderFlags |= 0x20;
    }
}


/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleScene_PhaseWithdrawFainted(CameraNode* arg0) {
    u8* sp2C = (u8*)sActivePokemon[sBattleScene.scene->actingSide] + 0x78C;
    ActivePokemon* temp_s0 = sActivePokemon[sBattleScene.scene->actingSide];

    if (sBattleScene.scene->actingSide) {}  // karodo

    sBattleScene.scene->cameraPresetId = 4;
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            func_821255EC(arg0);
            func_82124984((s32)temp_s0, (s32)arg0, 2);
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
            if (M2C_FIELD(temp_s0, f32*, 0x64C) == 2.5f) {
                M2C_FIELD(temp_s0, u8*, 0x626) |= 0x20;
            }
            if (ModelAnim_IsAnimationDone((DisplayObject*)((u8*)temp_s0 + 0x624)) == 1) {
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 4:
            M2C_FIELD(temp_s0, u8*, 0x625) &= ~1;
            *M2C_FIELD(temp_s0, u8**, 0x85C) |= 0x80;
            sBattleScene.scene->phaseStep++;
            break;

        case 5:
            if (*M2C_FIELD(temp_s0, u8**, 0x85C) & 0x10) {
                *M2C_FIELD(temp_s0, u8**, 0x85C) &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                func_82107408(temp_s0);
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                func_800407B0(2, 0, 0);
                BattleScene_RebindParticipantTeamMember(temp_s0, sp2C[0x2D]);
                sBattleScene.scene->phaseStep++;
            }
            break;

        case 6:
            func_82104C68(temp_s0, 0x12);
            func_82124984((s32)temp_s0, (s32)arg0, 3);
            func_8212239C(temp_s0, arg0);
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


void func_821311A0(CameraNode* arg0) {
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
                temp_s0->sessionTeams->displayModel = sp2C->id;
                temp_s0->sessionTeams->unk_04 = (TeamRoster*)&temp_s0->teamRoster->pokemonPicked[temp_s0->state.rosterIndex];
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
            temp_s0->sessionTeams->uniqueStatusFlags |= 0x80;
            sBattleScene.scene->phaseStep += 1;
            break;

        case 4:
            if (temp_s0->sessionTeams->uniqueStatusFlags & 0x10) {
                temp_s0->sessionTeams->uniqueStatusFlags &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                BattleThumbnail_TickOwnerCameraFraming(temp_s0);
                Audio_PlayCommand(2, 0, 0);
                M2C_FIELD(temp_s0, s32*, 0x9D0) = sp3C->rosterIndex;
                M2C_FIELD(temp_s0, s32*, 0x9D4) = sp3C->teamMemberIndex;
                BattleScene_RebindParticipantTeamMember(temp_s0, sp3C->replacementState);
                BattleScene_ResetCameraFrameCounter();
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                BattleScene_EnterStateRow(temp_s0, 0x12);
                func_82124984((s32)temp_s0, (s32)arg0, 3);
                func_8212239C(temp_s0, arg0);
                sBattleScene.scene->phaseStep += 1;
            }
            break;

        case 5:
            func_82124984((s32)temp_s0, (s32)arg0, 3);
            func_8212239C(temp_s0, arg0);
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
                if (sp38->unk_2D != 0x10) {
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
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleScene_UpdatePhase(CameraNode* arg0) {
    func_82125FD0();
    switch (sBattleScene.scene->phase) {
    case 0:
        func_8212601C(arg0);
        BattleScene_SetPhase(arg0, 1);
        /* fallthrough */
    case 1:
        func_82127250(arg0);
        break;
    case 2:
        func_8212BFF0(arg0);
        break;
    case 3:
        func_8212C1C4(arg0);
        break;
    case 4:
        func_8212F118((s32)arg0);
        break;
    case 7:
        func_8212C874(arg0);
        break;
    case 30:
        BattleScene_Phase30(arg0);
        break;
    case 29:
        func_8212DE30(arg0);
        break;
    case 28:
        func_8212CF90(arg0);
        break;
    case 25:
        func_8212D820(arg0);
        break;
    case 21:
        func_8212D194(arg0);
        break;
    case 27:
        BattleScene_Phase38(arg0);
        break;
    case 12:
        func_8212E0B0(arg0);
        break;
    case 13:
        BattleScene_Phase13(arg0);
        break;
    case 14:
        BattleScene_Phase14(arg0);
        break;
    case 15:
        func_8212D504(arg0);
        break;
    case 17:
        func_8212E7B0(arg0);
        break;
    case 31:
        func_8212ECC8(arg0);
        break;
    case 20:
        func_8212EA84(arg0);
        break;
    case 8:
        func_8212F440(arg0);
        break;
    case 22:
        func_8212F5B4(arg0);
        break;
    case 32:
        func_8212F894(arg0);
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
        func_8212F16C(arg0);
        break;
    case 11:
        BattleScene_PhaseWithdrawFainted(arg0);
        break;
    case 18:
        func_821311A0(arg0);
        break;
    case 26:
        func_8212F6E4(arg0);
        break;
    case 5:
        func_82126C74(arg0);
        break;
    case 34:
        func_82126E34(arg0);
        break;
    }
}

void func_82131880(CameraNode* arg0) {
    BattleScene_ResetCameraFrameCounter();
    BattleScene_SetCameraAtFromPosition(arg0, D_8218B630, 0, 0, 0.0f, 0.0f);
    BattleScene_SetCameraEyeAndStoreAngles(arg0, D_8218B630, 0x3C6E, M2C_FIELD(sBattleScene.scene, s16*, 0x5A) = 0, sBattleScene.scene->unk_74 = D_FLT_82196668, 0.0f);
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    M2C_FIELD(sBattleScene.scene, f32*, 0x64) = D_FLT_8219666C;
    Battle_SetStageScale(M2C_FIELD(sBattleScene.scene, f32*, 0x64));
    Audio_PlayCommand(4, 0, 0);
    func_80041914(sActivePokemon[0]->teamRoster->numberOfPokemonBrought, sActivePokemon[1]->teamRoster->numberOfPokemonBrought);
    BattleAnim_LoadModeResourceList(sActivePokemon[0]->sessionTeams, 3);
    sBattleScene.scene->phaseStep += 1;
}

void func_821319FC(s32 arg0) {
    if (func_82101FD4(D_82199DE0) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

s32 func_80041374(s32, u32);
void func_82131A3C(CameraNode* arg0) {
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    BattleAnim_ApproachF(&sBattleScene.scene->unk_74, 10000.0f, 0.025f);
    BattleScene_SetCameraAtFromPosition(arg0, D_8218B630, 0, 0, 0.0f, 0.0f);
    BattleScene_SetCameraEyeAndStoreAngles(arg0, D_8218B630, 0x3C6E, M2C_FIELD(sBattleScene.scene, s16*, 0x5A) -= 0x16C, sBattleScene.scene->unk_74, 0.0f);
    BattleAnim_ApproachF(&M2C_FIELD(sBattleScene.scene, f32*, 0x64), 1.0f, 0.06f);
    Battle_SetStageScale(M2C_FIELD(sBattleScene.scene, f32*, 0x64));
    if (sBattleScene.scene->stepFrameTimer == 0x3C) {
        func_80041374(4, 0x3C);
    }
    if (func_821217DC(0x50) != 0) {
        func_800407B0(1, 0xFE, 0);
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

void func_82131C64(s32 arg0) {
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), f32 *, 0x64C) == 0.0f) {
        func_800407B0(1, 1, 0);
        ActivePokemon_SetModelTransform(M2C_FIELD(&D_82199DE0, s8 **, 4), 1, 0);
        func_821365B0(0xA, M2C_FIELD(&D_82199DE0, s8 **, 4), M2C_FIELD(&D_82199DE0, s8 **, 4), 0xFF, 0xFF);
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

void func_8212254C(s8*, void*, Vec3f, s32, s32, f32, f32);
void func_82122628(void*, Vec3f, s32, s32, f32, f32);
void func_82131D24(void* arg0) {
    Vec3f sp34;

    sp34.y = 0.0f;
    sp34.z = 0.0f;
    sp34.x = -150.0f;
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), f32 *, 0x64C) == 0) {
        if (M2C_FIELD(D_8219A5A0, s32 *, 0x1C) == 4) {
            M2C_FIELD(arg0, f32 *, 0x2C) = M2C_FIELD(D_8219A5A0, f32 *, 0x60);
        }
        func_8212254C(M2C_FIELD(&D_82199DE0, s8 **, 0), arg0, sp34, 0, 0, 0.0f, 0.0f);
        ActivePokemon_SetModelTransform(M2C_FIELD(&D_82199DE0, s8 **, 0), 2, 0);
        func_821365B0(0xB, M2C_FIELD(&D_82199DE0, s8 **, 0), M2C_FIELD(&D_82199DE0, s8 **, 0), 0xFF, 0xFF);
        func_82122628(arg0, sp34, M2C_FIELD(D_8219A5A0, s16 *, 0x58) = 0x71C, 0x4000, M2C_FIELD(D_8219A5A0, f32 *, 0x74) = 250.0f, 0.0f);
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

void BattleScene_IntroPanCamera(CameraNode* arg0) {
    Vec3f sp2C;

    sp2C.y = 0.0f;
    sp2C.z = 0.0f;
    sp2C.x = -150.0f;
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    BattleAnim_ApproachF(&sBattleScene.scene->unk_74, 60.000004f, 0.1f);
    BattleAnim_StepToS16(&sBattleScene.scene->rotationY, 0, 0x1E);
    BattleScene_SetCameraEyeFromPosition(arg0, sp2C, sBattleScene.scene->rotationY, 0x4000, sBattleScene.scene->unk_74, 0.0f);

    if ((sBattleScene.scene->rotationY >= 0x2E) && (M2C_FIELD(sActivePokemon[0], f32*, 0x64C) == 2.5f)) {
        Audio_PlayCommand(2, 0, 0);
        M2C_FIELD(sActivePokemon[0], u8*, 0x626) |= 0x20;
        sBattleScene.scene->phaseStep += 1;
    }
}

void func_8213201C(s32 arg0) {
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (func_8001101C(M2C_FIELD(&D_82199DE0, s8 **, 0) + 0x624, &D_82199DE0) == 1) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

/**
 * Battle start: sends out side 0's Pokemon with ゆけっ！%s (Go! %s).
 * @unverified Name and comment guessed from the code.
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
    func_82124984((s32)sActivePokemon[0], (s32)arg0, 3);
    func_8212239C(sActivePokemon[0], arg0);
    func_82104C68(sActivePokemon[0], 0x10);
    sBattleScene.scene->substepFrameCounter = 0;
    sBattleScene.scene->phaseStep++;
}

void func_821321A4(CameraNode* arg0) {
    M2C_FIELD(sActivePokemon[1], u8*, 1) &= ~1;
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
 * @unverified Name and comment guessed from the code.
 */
void BattleScene_SendOutSide1(CameraNode* arg0) {
    func_800407B0(2, 0, 0);
    BattleAnim_QueueEffectList3(3, sActivePokemon[1], sActivePokemon[1], 0xFF, 0xFF);
    BattleMessage_Format(D_8219A520 + 0x488, 0, (s32)D_8219665C, ActivePokemon_GetNickname(sActivePokemon[1]));
    func_8211EE8C();
    BattleMessage_ShowForSide(D_8219A520 + 0x488, 1);
    BattleScene_ResetCameraFrameCounter();
    M2C_FIELD(sActivePokemon[1], u8*, 0x1) |= 1;
    func_82124984((s32)sActivePokemon[1], (s32)arg0, 3);
    func_8212239C(sActivePokemon[1], arg0);
    func_82104C68(sActivePokemon[1], 0x10);
    sBattleScene.scene->phaseStep++;
    sBattleScene.scene->substepFrameCounter = 0;
}

void func_8213233C(CameraNode* arg0) {
    M2C_FIELD(sActivePokemon[0], u8*, 1) &= ~1;
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
