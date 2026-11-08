/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_3438B0.h"

void func_82130628(CameraNode* arg0) {
    u8* sp2C = (u8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x7C6;
    u8* sp28 = (u8*)sActivePokemon[!sBattleScene.scene->unk_2C] + 0x7C6;
    ActivePokemon* cur = sActivePokemon[sBattleScene.scene->unk_2C];

    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_82135098((ActivePokemon*)D_8219A544);
            func_82106374((ActivePokemon*)D_8219A544);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->unk_20++;
            break;

        case 1:
            func_82106354(cur);
            if (func_82124A50(sActivePokemon[sBattleScene.scene->unk_2C]) == 0) {
                func_82108C0C((ActivePokemon*)D_8219A544);
                func_80040738();
                BattleAnim_CleanupEffects(1);
                func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
                func_82104C68(sActivePokemon[sBattleScene.scene->unk_2C], 0xD);
                if (sp2C[0x15] & 0x18) {
                    func_8211F034(D_8219A520 + 0x248, sBattleScene.scene->unk_2C);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0xE);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0xE);
                    if (sp2C[0x15] & 0x10) {
                        func_821366B0(6, (ActivePokemon*)D_8219A544);
                    } else {
                        func_821366B0(5, (ActivePokemon*)D_8219A544);
                    }
                    sBattleScene.scene->unk_20++;
                } else {
                    func_8211F034(D_8219A520 + 0x288, sBattleScene.scene->unk_2C);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    func_821366B0(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->unk_20 = 3;
                }
            }
            break;

        case 2:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                if (func_82107CA0(sActivePokemon[sBattleScene.scene->unk_2C]) == 0) {
                    func_82125570();
                    BattleScene_SetPhase(arg0, 5);
                    sBattleScene.scene->unk_2C = !sBattleScene.scene->unk_2C;
                } else if (sp2C[0x4D] & 0x80) {
                    func_800407B0(0x22, 0, 0);
                    func_8211F034(D_8219A520 + 0x288, sBattleScene.scene->unk_2C);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    func_821366B0(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->unk_20++;
                } else {
                    sBattleScene.scene->unk_20 = 4;
                }
            }
            break;

        case 3:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if ((BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0) && (D_8219A560 == 1) && (D_8219A564 == 1)) {
                sBattleScene.scene->unk_20++;
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
            }
            break;

        case 4:
            if (func_82124BF8(D_8219A540) == 0) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 5:
            func_82124A40();
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}


#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82130B10.s")

void func_82130D48(ActivePokemon* active_pokemon) {
    BattleMon* party_pokemon = &active_pokemon->teamRoster->pokemonPicked[M2C_FIELD(active_pokemon, s32*, 0x9D0)];

    if (M2C_FIELD(party_pokemon, u8*, 5) & 0x20) {
        BattleAnim_StopOwnerCategoryParticles(1, active_pokemon);
        active_pokemon->displayObject.node.renderFlags |= 0x20;
    }
}


void func_82130DAC(CameraNode* arg0) {
    u8* sp2C = (u8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x78C;
    ActivePokemon* temp_s0 = sActivePokemon[sBattleScene.scene->unk_2C];

    if (sBattleScene.scene->unk_2C) {}

    M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 4;
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_821255EC(arg0);
            func_82124984((s32)temp_s0, (s32)arg0, 2);
            BattleScene_ResetCameraFrameCounter();
            func_8211F034(D_8219A520 + 0x1C8, sBattleScene.scene->unk_2C);
            sBattleScene.scene->unk_20++;
            break;

        case 1:
            BattleScene_ApproachCameraZoom(arg0, temp_s0);
            func_82104C68(temp_s0, 2);
            func_82130D48(temp_s0);
            sBattleScene.scene->unk_20++;
            break;

        case 2:
            BattleScene_ApproachCameraZoom(arg0, temp_s0);
            if (sBattleScene.scene->unk_14 == 0x23) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x69) != 0) {
                Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)arg0 + 0xB4), M2C_FIELD(temp_s0, s32*, 0x60C) * -150.0f, 0.0, 0.0f);
                if (sBattleScene.scene && sBattleScene.scene) {}
                Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)arg0 + 0xA8), M2C_FIELD(temp_s0, s32*, 0x60C) * -50.0f, 5.0f, 0.0f);
                BattleScene_SetParticipantModelTransform(temp_s0, 2, 0);
                BattleAnim_QueueEffectList3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 3:
            if (M2C_FIELD(temp_s0, f32*, 0x64C) == 2.5f) {
                M2C_FIELD(temp_s0, u8*, 0x626) |= 0x20;
            }
            if (ModelAnim_IsAnimationDone((DisplayObject*)((u8*)temp_s0 + 0x624)) == 1) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 4:
            M2C_FIELD(temp_s0, u8*, 0x625) &= ~1;
            *M2C_FIELD(temp_s0, u8**, 0x85C) |= 0x80;
            sBattleScene.scene->unk_20++;
            break;

        case 5:
            if (*M2C_FIELD(temp_s0, u8**, 0x85C) & 0x10) {
                *M2C_FIELD(temp_s0, u8**, 0x85C) &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                func_82107408(temp_s0);
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                func_800407B0(2, 0, 0);
                BattleScene_RebindParticipantTeamMember(temp_s0, sp2C[0x2D]);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 6:
            func_82104C68(temp_s0, 0x12);
            func_82124984((s32)temp_s0, (s32)arg0, 3);
            func_8212239C(temp_s0, arg0);
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
            BattleScene_ResetCameraFrameCounter();
            sBattleScene.scene->unk_20++;
            break;

        case 7:
            func_82122A7C(arg0, temp_s0);
            if (sBattleScene.scene->unk_14 == 0x1E) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_IsRowWaitCompleteWithEventCount(temp_s0, 0x64) != 0) {
                func_80040738();
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
    ActivePokemonState* sp3C = &sActivePokemon[sBattleScene.scene->unk_2C]->state;
    ActivePokemonState* sp38 = &sActivePokemon[!sBattleScene.scene->unk_2C]->state;
    ActivePokemon* temp_s0 = sActivePokemon[sBattleScene.scene->unk_2C];
    BattleMonRuntime* sp2C = &sActivePokemon[sBattleScene.scene->unk_2C]->state.runtime;

    sBattleScene.scene->unk_50 = 4;

    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_821255EC(arg0);
            Vec3f_SetComponentsDuplicate(&arg0->view.targetPosition, temp_s0->facingDirection * -150.0f, 0.0, 0.0f);
            Vec3f_SetComponentsDuplicate(&arg0->view.eyePosition, temp_s0->facingDirection * -50.0f, 5.0f, 0.0f);
            Vec3f_SetComponentsDuplicate(&temp_s0->displayObject.position, temp_s0->facingDirection * -150.0f, 25.0f, 0.0f);
            BattleScene_ResetCameraFrameCounter();
            Battle_ClearMessageCursor();
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
            BattleAnim_LoadModeResourceList(temp_s0->sessionTeams, 3);
            sBattleScene.scene->unk_20 += 1;
            break;

        case 1:
            if (BattleAnim_TryRegisterAssetTables(temp_s0) != 0) {
                temp_s0->sessionTeams->displayModel = sp2C->id;
                temp_s0->sessionTeams->unk_04 = (TeamRoster*)&temp_s0->teamRoster->pokemonPicked[temp_s0->state.rosterIndex];
                BattleScene_SetParticipantModelTransform(temp_s0, 2, 0);
                BattleAnim_QueueEffectList3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 2:
            if (temp_s0->pokeBall.position.y == 2.5f) {
                temp_s0->pokeBall.node.renderFlags |= 0x20;
            }

            if (ModelAnim_IsAnimationDone(&temp_s0->pokeBall) == 1) {
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 3:
            temp_s0->pokeBall.node.flags &= ~1;
            temp_s0->sessionTeams->uniqueStatusFlags |= 0x80;
            sBattleScene.scene->unk_20 += 1;
            break;

        case 4:
            if (temp_s0->sessionTeams->uniqueStatusFlags & 0x10) {
                temp_s0->sessionTeams->uniqueStatusFlags &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                BattleThumbnail_TickOwnerCameraFraming(temp_s0);
                Audio_PlayCommand(2, 0, 0);
                M2C_FIELD(temp_s0, s32*, 0x9D0) = sp3C->rosterIndex;
                M2C_FIELD(temp_s0, s32*, 0x9D4) = sp3C->teamMemberIndex;
                BattleScene_RebindParticipantTeamMember(temp_s0, sp3C->unk_2D_zero);
                BattleScene_ResetCameraFrameCounter();
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                BattleScene_EnterStateRow(temp_s0, 0x12);
                func_82124984((s32)temp_s0, (s32)arg0, 3);
                func_8212239C(temp_s0, arg0);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 5:
            func_82124984((s32)temp_s0, (s32)arg0, 3);
            func_8212239C(temp_s0, arg0);
            sBattleScene.scene->unk_20 += 1;
            break;

        case 6:
            func_82122A7C(arg0, temp_s0);
            if (BattleScene_AdvanceCameraFrameCounter(0x15) != 0) {
                Battle_ClearMessageCursor();
                BattleAnim_ResetFreezeStatusAndRestoreAnimation(temp_s0);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 7:
            func_82122A7C(arg0, temp_s0);
            if (BattleScene_IsRowWaitCompleteWithEventCount(temp_s0, 0x32) != 0) {
                func_80040738();
                BattleAnim_CleanupEffects(2);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                Vec3f_SetComponentsDuplicate(&temp_s0->displayObject.scale, 1.0f, 1.0f, 1.0f);
                if (sp38->unk_2D != 0x10) {
                    sBattleScene.scene->unk_34 = 3;
                }
                sBattleScene.scene->unk_2E = 2;
                func_8212562C();
                sp3C->flags &= 0xC7FF;
            }
            break;
    }
}

void BattleScene_UpdatePhase(CameraNode* arg0) {
    func_82125FD0();
    switch (sBattleScene.scene->unk_38) {
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
        func_8212CB58(arg0);
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
        func_8212DB28(arg0);
        break;
    case 12:
        func_8212E0B0(arg0);
        break;
    case 13:
        func_8212E350(arg0);
        break;
    case 14:
        func_8212E634(arg0);
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
        func_8212FC98(arg0);
        break;
    case 33:
        func_82130B10(arg0);
        break;
    case 35:
        func_82130628(arg0);
        break;
    case 9:
        func_821301EC(arg0);
        break;
    case 16:
        func_8212F16C(arg0);
        break;
    case 11:
        func_82130DAC(arg0);
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
    func_80041914(M2C_FIELD(sActivePokemon[0]->teamRoster, u8*, 2), M2C_FIELD(sActivePokemon[1]->teamRoster, u8*, 2));
    BattleAnim_LoadModeResourceList(sActivePokemon[0]->sessionTeams, 3);
    sBattleScene.scene->unk_20 += 1;
}

void func_821319FC(s32 arg0) {
    if (func_82101FD4(D_82199DE0) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82131A3C.s")

void func_82131C64(s32 arg0) {
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), f32 *, 0x64C) == 0.0f) {
        func_800407B0(1, 1, 0);
        func_82108A88(M2C_FIELD(&D_82199DE0, s8 **, 4), 1, 0);
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
        func_82108A88(M2C_FIELD(&D_82199DE0, s8 **, 0), 2, 0);
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
    BattleAnim_ApproachF(&M2C_FIELD(sBattleScene.scene, f32*, 0x74), 60.000004f, 0.1f);
    BattleAnim_StepToS16(&M2C_FIELD(sBattleScene.scene, s16*, 0x58), 0, 0x1E);
    BattleScene_SetCameraEyeFromPosition(arg0, sp2C, M2C_FIELD(sBattleScene.scene, s16*, 0x58), 0x4000, M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0f);

    if ((M2C_FIELD(sBattleScene.scene, s16*, 0x58) >= 0x2E) && (M2C_FIELD(sActivePokemon[0], f32*, 0x64C) == 2.5f)) {
        Audio_PlayCommand(2, 0, 0);
        M2C_FIELD(sActivePokemon[0], u8*, 0x626) |= 0x20;
        sBattleScene.scene->unk_20 += 1;
    }
}

void func_8213201C(s32 arg0) {
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (func_8001101C(M2C_FIELD(&D_82199DE0, s8 **, 0) + 0x624, &D_82199DE0) == 1) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

void func_82132088(CameraNode* arg0) {
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    func_821365B0(3, (s8*)sActivePokemon[0], (s8*)sActivePokemon[0], 0xFF, 0xFF);
    func_8211EF74(D_8219A520 + 0x448, 0, (s32)D_82196650, func_82107F88(sActivePokemon[0]));
    func_8211EE8C();
    func_8211F034(D_8219A520 + 0x448, 0);
    sActivePokemon[0]->displayObject.node.flags |= 1;
    sActivePokemon[0]->pokeBall.node.flags &= ~1;
    func_82124984((s32)sActivePokemon[0], (s32)arg0, 3);
    func_8212239C(sActivePokemon[0], arg0);
    func_82104C68(sActivePokemon[0], 0x10);
    sBattleScene.scene->unk_10 = 0;
    sBattleScene.scene->unk_20++;
}

void func_821321A4(CameraNode* arg0) {
    M2C_FIELD(sActivePokemon[1], u8*, 1) &= ~1;
    func_82122A7C(arg0, sActivePokemon[0]);
    sBattleScene.scene->unk_10++;
    if (sBattleScene.scene->unk_10 == 0x28) {
        func_8211EE8C();
    }
    if (func_821057D4(sActivePokemon[0], 0x3C) != 0) {
        sBattleScene.scene->unk_20++;
    }
}

void func_82132238(CameraNode* arg0) {
    func_800407B0(2, 0, 0);
    BattleAnim_QueueEffectList3(3, sActivePokemon[1], sActivePokemon[1], 0xFF, 0xFF);
    func_8211EF74(D_8219A520 + 0x488, 0, (s32)D_8219665C, func_82107F88(sActivePokemon[1]));
    func_8211EE8C();
    func_8211F034(D_8219A520 + 0x488, 1);
    BattleScene_ResetCameraFrameCounter();
    M2C_FIELD(sActivePokemon[1], u8*, 0x1) |= 1;
    func_82124984((s32)sActivePokemon[1], (s32)arg0, 3);
    func_8212239C(sActivePokemon[1], arg0);
    func_82104C68(sActivePokemon[1], 0x10);
    sBattleScene.scene->unk_20++;
    sBattleScene.scene->unk_10 = 0;
}

void func_8213233C(CameraNode* arg0) {
    M2C_FIELD(sActivePokemon[0], u8*, 1) &= ~1;
    func_82122A7C(arg0, sActivePokemon[1]);
    sBattleScene.scene->unk_10++;
    if (sBattleScene.scene->unk_10 == 0x28) {
        Battle_ClearMessageCursor();
    }
    if (BattleScene_IsRowWaitCompleteWithEventCount(sActivePokemon[1], 0x3C) != 0) {
        Battle_ClearMessageCursor();
        func_82125384();
    }
}
