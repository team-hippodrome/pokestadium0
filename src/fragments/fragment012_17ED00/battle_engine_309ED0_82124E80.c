/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_309ED0.h"

extern s32 D_8219A570;
extern s32 D_8219A574;

void func_82124E80(void) {
    M2C_FIELD(D_8219A5A0, s32 *, 0x50) = 1;
    func_82108C0C(D_8219A544);
}

void func_82124EB4(void) {
    M2C_FIELD(D_8219A5A0, s32 *, 0x50) = 3;
    func_82108C0C(D_8219A544);
    func_82108C0C(D_8219A540);
}

void func_82124EF4(void) {
}

void func_82124EFC(void) {
    s32 sp24;
    ActivePokemonState* temp_s0;
    ActivePokemonState* temp_s1;
    BattleMonRuntime* ptr;

    temp_s0 = &sActivePokemon[0]->state;
    temp_s1 = &sActivePokemon[1]->state;
    BattleScene_SetCameraSubstate(1, 1);

    sp24 = sBattleScene.scene->unk_2C;
    sBattleScene.scene->unk_2C = Battle_DetermineMoveOrder(sActivePokemon[0], sActivePokemon[1]);

    ptr = &sActivePokemon[sBattleScene.scene->unk_2C]->state.runtime;
    if (M2C_FIELD(ptr, u8*, 0x5A) == 0xFF) {
        sBattleScene.scene->unk_2C = !sBattleScene.scene->unk_2C;
    }

    if (sActivePokemon[0]->teamRoster->unk_000 & 2) {
        if (sBattleScene.scene->unk_2C == 0) {
            BattleAI_RecordUsedMove(temp_s0->rosterIndex, temp_s1->rosterIndex, 0);
        } else {
            BattleAI_RecordUsedMove(temp_s0->rosterIndex, temp_s1->rosterIndex, 1);
        }
    } else if (sActivePokemon[1]->teamRoster->unk_000 & 2) {
        if (sBattleScene.scene->unk_2C == 1) {
            BattleAI_RecordUsedMove(temp_s1->rosterIndex, temp_s0->rosterIndex, 0);
        } else {
            BattleAI_RecordUsedMove(temp_s1->rosterIndex, temp_s0->rosterIndex, 1);
        }
    }

    sBattleScene.scene->unk_2A = sBattleScene.scene->unk_2C;
    sBattleScene.scene->unk_38 = 0;
    temp_s0->unk_30 = 0;
    temp_s1->unk_30 = 0;
    if (sBattleScene.scene->unk_1C == 5) {
        sBattleScene.scene->unk_44 = 6;
    } else {
        sBattleScene.scene->unk_44 = 2;
    }
    Battle_ResolveMonAction();
    sBattleScene.scene->unk_2C = sp24;
}

void func_82188B8C(s32, s32, s32);
s32 func_821250D4(void) {
    s8* sp24;
    s8* sp20;
    s8* sp1C;

    sp24 = (s8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x78C;
    sp20 = (s8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x78C;
    sp1C = (s8*)sActivePokemon[!sBattleScene.scene->unk_2C] + 0x78C;
    func_821079E8(0x1FFE);
    if ((M2C_FIELD(sp24, u8*, 0x2E) == 0xF) || (M2C_FIELD(sp24, u8*, 0x2E) == 0x10)) {
        if (*M2C_FIELD(sActivePokemon[sBattleScene.scene->unk_2C], u8**, 0x860) & 2) {
            func_82188B8C(M2C_FIELD(sp20, s32*, 8), M2C_FIELD(sp1C, s32*, 8), 2);
        }
        func_82105E4C(sActivePokemon[sBattleScene.scene->unk_2C], 0x3800);
        sBattleScene.scene->unk_20 = 0;
        M2C_FIELD(sBattleScene.scene, s32*, 0x14) = 0;
        if (M2C_FIELD(sp24, u8*, 0x2E) == 0x10) {
            M2C_FIELD(sBattleScene.scene, s32*, 0x38) = 0x12;
        } else {
            M2C_FIELD(sBattleScene.scene, s32*, 0x38) = 0xB;
        }
        return 1;
    }
    return 0;
}

void BattleScene_InitializeSwitchActions(void) {
    s32 sp2C;
    ActivePokemonState* sp28;
    ActivePokemonState* sp24;

    sp28 = &sActivePokemon[0]->state;
    sp24 = &sActivePokemon[1]->state;
    BattleScene_SetCameraSubstate(1, 1);

    sp2C = sBattleScene.scene->unk_2C;

    if ((sp28->unk_2D == 0xF) || (sp28->unk_2D == 0x10)) {
        if (sActivePokemon[0]->teamRoster->unk_000 & 2) {
            BattleAI_RecordUsedMove(sp28->rosterIndex, sp24->rosterIndex, 2);
        }
        sBattleScene.scene->unk_2C = 0;
        sBattleScene.scene->unk_2A = 0;
        sBattleScene.scene->unk_38 = 0;
        sBattleScene.scene->unk_44 = 2;
        BeginBattleForEntity(sActivePokemon[0]);
        sBattleScene.scene->unk_2C = sp2C;
    } else {
        if (sActivePokemon[0]->teamRoster->unk_000 & 2) {
            BattleAI_RecordUsedMove(sp24->rosterIndex, sp28->rosterIndex, 2);
        }
        sBattleScene.scene->unk_2C = 1;
        sBattleScene.scene->unk_2A = 1;
        sBattleScene.scene->unk_38 = 0;
        sBattleScene.scene->unk_44 = 2;
        BeginBattleForEntity(sActivePokemon[1]);
        sBattleScene.scene->unk_2C = sp2C;
    }
}

extern s32 D_82199DE0;
M2C_UNK func_800419F8();
void func_82121D8C(s32, s32, s8 *);
void func_82125384(void) {
    s8* a;
    s8* b;
    s32 st;

    a = M2C_FIELD(&D_82199DE0, s8 **, 0) + 0x78C;
    b = M2C_FIELD(&D_82199DE0, s8 **, 4) + 0x78C;
    func_800419F8(1, a, b);
    M2C_FIELD(a, s32 *, 0x10) = 0;
    M2C_FIELD(b, s32 *, 0x10) = 0;
    st = M2C_FIELD(D_8219A5A0, s32 *, 0x1C);
    if ((st == 4) || (st == 9) || (st == 0xA)) {
        func_82121D8C(1, 0, b);
    } else if ((M2C_FIELD(a, u8 *, 0x2E) == 0x10) || (M2C_FIELD(b, u8 *, 0x2E) == 0x10) || (M2C_FIELD(D_8219A5A0, u16 *, 0x2E) == 2)) {
        func_82121D8C(1, 0, b);
    } else {
        func_82121D8C(1, 1, b);
    }
    st = M2C_FIELD(D_8219A5A0, s32 *, 0x1C);
    if (st == 6) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x44) = 5;
    } else if (st == 0xA) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x44) = 9;
    } else {
        M2C_FIELD(D_8219A5A0, s32 *, 0x44) = 1;
    }
    M2C_FIELD(D_8219A5A0, s32 *, 0x20)++;
}

void func_82133868(ActivePokemonState*);

// Stadium 1 counterpart: Battle_ActSecondAttacker (no phase/arg handling here).
void func_821254B0(void) {
    ActivePokemonState* temp_a3;

    sBattleScene.scene->unk_2C = !sBattleScene.scene->unk_2C;
    temp_a3 = &sActivePokemon[sBattleScene.scene->unk_2C]->state;

    if ((temp_a3->unk_2D == 0xF) || (temp_a3->unk_2D == 0x10)) {
        BeginBattleForEntity(sActivePokemon[sBattleScene.scene->unk_2C]);
    } else if (sBattleScene.scene->unk_1C == 0xA) {
        func_82133868(temp_a3);
    } else {
        Battle_ResolveMonAction();
    }

    sBattleScene.scene->unk_34 = 1;
    sBattleScene.scene->unk_A0.z = 0.0f;
}

void BattleScene_ClearPhaseFlag(void) {
    sBattleScene.scene->unk_3C = 0;
}

void BattleScene_SetPhaseFlag(void) {
    sBattleScene.scene->unk_3C = 1;
}

void BattleScene_SetPhase(UNUSED CameraNode* arg0, s32 arg1) {
    sBattleScene.scene->unk_38 = arg1;
    sBattleScene.scene->unk_20 = 0;
}

void func_821255B4(s8 *arg0) {
    func_821079E8(0x1FFE);
    M2C_FIELD(D_8219A5A0, f32 *, 0x60) = (f32) M2C_FIELD(arg0, f32 *, 0x2C);
}

void func_821255EC(s8 *arg0) {
    func_821079E8(0x1FFE);
    M2C_FIELD(arg0, f32 *, 0x2C) = 30.0f;
    M2C_FIELD(D_8219A5A0, f32 *, 0x60) = 30.0f;
}

void func_8212562C(void) {
    BattleMonRuntime* runtime;
    BattleMonRuntime* other_runtime;
    ActivePokemonState* other_state;
    s32 other;

    if (sBattleScene.scene->unk_34 == 0) {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->unk_2C]);
        func_80040738();
        BattleScene_ResetAnimationStep();
        runtime = &sActivePokemon[sBattleScene.scene->unk_2C]->state.runtime;
        other = sBattleScene.scene->unk_2C == 0;
        other_runtime = &sActivePokemon[other]->state.runtime;
        other_state = &sActivePokemon[other]->state;
        if ((runtime->usedMove == 0xFF) || (other_runtime->usedMove == 0xFF)) {
            if ((other_state->unk_2D != 0xF) && (other_state->unk_2D != 0x10)) {
                sBattleScene.scene->unk_20 = 0;
                sBattleScene.scene->unk_14 = 0;
                sBattleScene.scene->unk_38 = 4;
                return;
            }
        }
        func_821254B0();
        sBattleScene.scene->unk_20 = 0;
        sBattleScene.scene->unk_14 = 0;
        sBattleScene.scene->unk_38 = 3;
    } else {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->unk_2C]);
        func_80040738();
        BattleScene_ResetAnimationStep();
        sBattleScene.scene->unk_20 = 0;
        sBattleScene.scene->unk_14 = 0;
        sBattleScene.scene->unk_38 = 4;
    }
}

s32 BattleScene_HandleFaintStatusCompletion(void) {
    s8* temp_v0 = (s8*)D_8219A540 + 0x7C6;

    if (((M2C_FIELD(temp_v0, u8*, 0x4D) & 0x80) || (M2C_FIELD(temp_v0, u8*, 0x15) & 0x18)) && (M2C_FIELD(temp_v0, u8*, 0x5A) == 0xFF)) {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->unk_2C]);
        func_80040738();
        BattleScene_ResetAnimationStep();
        func_821254B0();
        sBattleScene.scene->unk_20 = 0;
        sBattleScene.scene->unk_14 = 0;
        M2C_FIELD(sBattleScene.scene, s32*, 0x38) = 3;
        return 1;
    }
    return 0;
}

void BattleScene_CompleteActionPhase(void) {
    if ((sBattleScene.scene->unk_34 == 0) && (M2C_FIELD(D_8219A540, u8*, 0x820) != 0xFF)) {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->unk_2C]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        func_821254B0();
        sBattleScene.scene->unk_20 = 0;
        sBattleScene.scene->unk_14 = 0;
        sBattleScene.scene->unk_38 = 3;
    } else if (BattleScene_HandleFaintStatusCompletion() == 0) {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->unk_2C]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        sBattleScene.scene->unk_20 = 0;
        sBattleScene.scene->unk_14 = 0;
        sBattleScene.scene->unk_38 = 4;
    }
}

s32 BattleScene_TransitionToPhaseFull(s32 arg0) {
    BattleScene_ClearPhaseFlag();
    BattleScene_ResetCameraFrameCounter();
    sBattleScene.scene->unk_48 = 0;
    sBattleScene.scene->unk_4C = 0;
    sBattleScene.scene->unk_20 = 0;
    sBattleScene.scene->unk_14 = 0;
    sBattleScene.scene->unk_38 = arg0;
    return 1;
}

s32 BattleScene_TransitionToPhase(s32 arg0) {
    BattleScene_ClearPhaseFlag();
    BattleScene_ResetCameraFrameCounter();
    sBattleScene.scene->unk_4C = 0;
    sBattleScene.scene->unk_20 = 0;
    sBattleScene.scene->unk_14 = 0;
    sBattleScene.scene->unk_38 = arg0;
    return 1;
}

void BattleScene_ResolveDisplayedHpCompletion(CameraNode* arg0) {
    if ((D_8219A560 == 1) && (D_8219A564 == 1)) {
        BattleScene_ResetCameraFrameCounter();
        func_8211EE8C();
        BattleScene_ClearPhaseFlag();
        if (func_82107CA0(sActivePokemon[sBattleScene.scene->unk_2C]) == 0) {
            BattleScene_SetPhase(arg0, 5);
            sBattleScene.scene->unk_2C = !sBattleScene.scene->unk_2C;
        } else if (func_82107CA0(sActivePokemon[!sBattleScene.scene->unk_2C]) == 0) {
            BattleScene_SetPhase(arg0, 5);
        } else {
            func_82125838();
        }
    }
}

void BattleScene_UpdateDisplayedHpAndTransition(CameraNode* arg0) {
    u8* sp1C = (u8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x7C6;

    func_82125570();
    func_8212188C();
    func_8211EE8C();
    func_82106220(D_8219A540);

    if (Battle_GetActiveMonHp(sActivePokemon[sBattleScene.scene->unk_2C]) == 0) {
        sBattleScene.scene->unk_2C = !sBattleScene.scene->unk_2C;
        func_82125594(arg0, 5);
    } else if (Battle_GetActiveMonHp(sActivePokemon[!sBattleScene.scene->unk_2C]) == 0) {
        func_821259E8(arg0);
    } else if (sBattleScene.scene->unk_4C == 0xA) {
        func_82125990(0xA);
    } else if (sBattleScene.scene->unk_48 == 9) {
        func_82125930(9);
    } else if ((sp1C[0x15] & 0x18) || (sp1C[0x4D] & 0x80)) {
        func_82125930(6);
    } else {
        func_821259E8(arg0);
    }
}

void func_82125C34(s32 arg0) {
    D_8219A560 = func_8210F31C(D_82199DE0);
    D_8219A564 = func_8210F31C(D_82199DE4);
    func_82125AC8(arg0);
}

void func_82125C80(s32 arg0) {
    if ((D_8219A560 == 1) && (D_8219A564 == 1)) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x50) = 1;
        func_82125AC8(arg0);
    }
}

s32 func_82125CC8(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_8219A5A0, s32 *, 0x48);
    if (temp_v0 == 7) {
        return func_82125930(7);
    }
    if (temp_v0 == 0x1E) {
        return func_82125930(0x1E);
    }
    if (temp_v0 == 0x1C) {
        return func_82125930(0x1C);
    }
    if (temp_v0 == 0x15) {
        return func_82125930(0x15);
    }
    if (temp_v0 == 0xF) {
        return func_82125930(0xF);
    }
    if (temp_v0 == 0x19) {
        return func_82125930(0x19);
    }
    if (temp_v0 == 0x1B) {
        return func_82125930(0x1B);
    }
    if (temp_v0 == 0x1D) {
        return func_82125930(0x1D);
    }
    if (temp_v0 == 0xC) {
        return func_82125930(0xC);
    }
    if (temp_v0 == 0xD) {
        return func_82125930(0xD);
    }
    if (temp_v0 == 0xE) {
        return func_82125930(0xE);
    }
    if (temp_v0 == 0x11) {
        return func_82125930(0x11);
    }
    if (temp_v0 == 0x1F) {
        return func_82125930(0x1F);
    }
    return 0;
}

s32 func_82125E5C(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_8219A5A0, s32 *, 0x48);
    if (temp_v0 == 0x16) {
        return func_82125930(0x16);
    }
    if (temp_v0 == 0x20) {
        return func_82125930(0x20);
    }
    if (temp_v0 == 0x1A) {
        return func_82125930(0x1A);
    }
    if (temp_v0 == 0x17) {
        return func_82125930(0x17);
    }
    if (temp_v0 == 0x14) {
        return func_82125930(0x14);
    }
    if (temp_v0 == 0x10) {
        return func_82125930(0x10);
    }
    if ((D_82199F31 != 0) || (temp_v0 == 8)) {
        return func_82125930(8);
    }
    return 0;
}

s32 BattleScene_PrepareResidualStatusPresentation(void) {
    s32 idx = sBattleScene.scene->unk_2C;
    BattleMonRuntime* temp_v1_2 = &sActivePokemon[idx]->state.runtime;

    if (((temp_v1_2->unk_4D & 0x80) || (temp_v1_2->unk_15 & 0x18)) && (temp_v1_2->usedMove == 0xFF)) {
        return BattleScene_TransitionToPhaseFull(0x23);
    }
    return 0;
}

void BattleScene_UpdateActiveOwnerPointers(void) {
    s32 idx;

    D_8219A544 = sActivePokemon[sBattleScene.scene->unk_2C];
    idx = sBattleScene.scene->unk_2C == 0;
    D_8219A540 = sActivePokemon[idx];
    sBattleScene.scene->unk_50 = 0;
}

void func_8212601C(s32 arg0) {
    s8 *sp34;
    s8 *sp30;

    sp34 = D_8219A544;
    sp30 = D_8219A540;
    func_800419F8(0);
    func_82121D78(arg0, 0x41A00000, 0x457A0000);
    func_82124A40();
    M2C_FIELD(D_8219A5A0, s32 *, 0x14) = 0;
    M2C_FIELD(D_8219A5A0, s16 *, 0x58) = 0;
    M2C_FIELD(D_8219A5A0, s16 *, 0x5A) = 0;
    M2C_FIELD(D_8219A5A0, f32 *, 0x5C) = (f32) D_FLT_821962A4;
    M2C_FIELD(D_8219A5A0, s32 *, 0x34) = 0;
    func_821224F4();
    func_82125570();
    if ((M2C_FIELD(sp34, f32 *, 0x28) > 100.0f) && (M2C_FIELD(sp30, f32 *, 0x28) > 100.0f)) {
        func_821218AC(arg0, M2C_FIELD(&D_8218B630, s32 *, 0), M2C_FIELD(&D_8218B630, f32 *, 4) + 200.0f, M2C_FIELD(&D_8218B630, s32 *, 8), M2C_FIELD(D_8219A5A0, f32 *, 0x5C), (s32) M2C_FIELD(D_8219A5A0, s16 *, 0x58), (s32) M2C_FIELD(D_8219A5A0, s16 *, 0x5A));
    } else {
        func_821218AC(arg0, M2C_FIELD(&D_8218B630, s32 *, 0), M2C_FIELD(&D_8218B630, f32 *, 4), M2C_FIELD(&D_8218B630, s32 *, 8), M2C_FIELD(D_8219A5A0, f32 *, 0x5C), (s32) M2C_FIELD(D_8219A5A0, s16 *, 0x58), (s32) M2C_FIELD(D_8219A5A0, s16 *, 0x5A));
    }
    func_82108C0C(D_82199DE0);
    func_82108C0C(D_82199DE4);
    M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
}

void func_821261A0(void* arg0, void* arg1, s32 arg2) {
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
        default:
            func_82124874(arg1, arg0);
            break;
    }
}

s32 func_82126220(ActivePokemon* active_pokemon) {
    UNUSED s32 pad; // FAKE: stack padding
    BattleMon* party_pokemon = &active_pokemon->teamRoster->pokemonPicked[active_pokemon->state.rosterIndex];
    ActivePokemonState* state = &active_pokemon->state;

    if (state->flags & 0x200) {
        func_82105E4C(active_pokemon, 0x60C);
        return 1;
    }
    if (state->flags & 0x80) {
        func_82136708(2, active_pokemon);
        func_82105E4C(active_pokemon, 0x80);
    }
    if (state->flags & 0x4008) {
        active_pokemon->displayObject.lodFraction = 0xFF;
        func_82136708(4, active_pokemon);
        active_pokemon->displayObject.position.y = D_FLT_82189354[active_pokemon->displayObject.objectType][0];
        active_pokemon->displayObject.node.renderFlags &= ~2;
        active_pokemon->displayObject.node.renderFlags |= 0x20;
        active_pokemon->displayObject.node.flags |= 1;
        func_82105E4C(active_pokemon, 0x4608);
    }
    if (party_pokemon->statusCondition & 7) {
        party_pokemon->statusCondition = 0;
        func_8210568C(active_pokemon, 0xB8, 1);
        func_82136708(3, active_pokemon);
        func_82105E4C(active_pokemon, 1);
    }
    state->alpha = 0xFF;
    func_80019B28((s32)active_pokemon, 0xFF, 0xFF, 0xFF, state->alpha);
    return 0;
}

void func_82126380(CameraNode* arg0) {
    if (func_82124A50(sActivePokemon[!sBattleScene.scene->unk_2C]) == 0) {
        Battle_ClearRuntimeFlags(sActivePokemon[!sBattleScene.scene->unk_2C], 0x3800);
        func_821261A0(sActivePokemon[!sBattleScene.scene->unk_2C], arg0, 3);
        func_80040738();
        BattleAnim_CleanupEffects(2);
        BattleScene_ResetCameraFrameCounter();
        Battle_ClearMessageCursor();
        func_8212239C(sActivePokemon[!sBattleScene.scene->unk_2C], arg0);
        if (func_82126220(sActivePokemon[!sBattleScene.scene->unk_2C]) != 0) {
            BattleScene_EnterStateRow(sActivePokemon[!sBattleScene.scene->unk_2C], 0x11);
            sBattleScene.scene->unk_20 = 0xA;
        } else {
            BattleScene_EnterStateRow(sActivePokemon[!sBattleScene.scene->unk_2C], 0);
            sBattleScene.scene->unk_20 += 1;
        }
    }
}

extern u8* D_82189180[];
s32 func_82101F84(s8*);
void func_821235E0(CameraNode*, ActivePokemon*);
void func_8211EE8C(void);
void func_82105E38(ActivePokemon*, s32);
u16 func_8210C020(s32); // BattleAnim_RandomRange
void func_821264E4(CameraNode* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    ActivePokemonState* state = &sActivePokemon[!sBattleScene.scene->unk_2C]->state;
    u8* rec = D_82189180[!sBattleScene.scene->unk_2C] + 0x72D;
    u16 sel;

    if (func_82101F84((s8*)sActivePokemon[!sBattleScene.scene->unk_2C]) == 0) {
        if (sBattleScene.scene->unk_14 == 0x1D) {
            for (;;) {
                sel = func_8210C020(4);
                if (sel != 3) {
                    break;
                }
            }
            func_821261A0(sActivePokemon[!sBattleScene.scene->unk_2C], arg0, sel);
        }
        if (func_82121820(0x1E) != 0) {
            func_821235E0(arg0, sActivePokemon[!sBattleScene.scene->unk_2C]);
        }
        if ((rec[4] >> 1) == (sActivePokemon[!sBattleScene.scene->unk_2C]->displayObject.transformAnim.frameFixed >> 16)) {
            func_8211EE8C();
            func_8211F034(D_8219A520 + 0x448 + (!sBattleScene.scene->unk_2C << 6), !sBattleScene.scene->unk_2C);
        }
        if (rec[0xA] == (sActivePokemon[!sBattleScene.scene->unk_2C]->displayObject.transformAnim.frameFixed >> 16) + 3) {
            func_8211EE8C();
            if (state->unk_2D != 0x12) {
                func_8211F034(D_8219A520 + 0x1C8, !sBattleScene.scene->unk_2C);
            }
            sActivePokemon[!sBattleScene.scene->unk_2C]->displayObject.node.renderFlags &= ~0x20;
            func_82105E38(sActivePokemon[!sBattleScene.scene->unk_2C], 0x100);
            func_8212188C();
            sBattleScene.scene->unk_20++;
        }
        func_821229AC(arg0, sActivePokemon[!sBattleScene.scene->unk_2C]);
    }
}

void BattleScene_AdvanceSendOutCameraClose(CameraNode* arg0) {
    func_821229AC(arg0, sActivePokemon[!sBattleScene.scene->unk_2C]);
    if (BattleScene_AdvanceCameraFrameCounter(0x19) != 0) {
        func_8211EE8C();
        func_80040738();
        sBattleScene.scene->unk_20++;
    }
}

void BattleScene_FinishSendOutCameraClose(CameraNode* arg0) {
    ActivePokemonState* temp_s0 = &sActivePokemon[!sBattleScene.scene->unk_2C]->state;

    func_821229AC(arg0, sActivePokemon[!sBattleScene.scene->unk_2C]);

    if (BattleScene_AdvanceCameraFrameCounter(5) != 0) {
        BattleAnim_CleanupEffects(1);
        func_80041374(3, 0);

        if (temp_s0->unk_2D != 0x12) {
            temp_s0->unk_2D = 0x10;
        }

        if (temp_s0->unk_2D == 0x12) {
            temp_s0->unk_2D = 0x13;
        }

        sBattleScene.scene->unk_20++;
    }
}

void func_8212684C(UNUSED CameraNode* arg0) {
    ActivePokemonState* other;
    ActivePokemonState* self;
    s32 side;
    BattleMon* mon;

    side = sBattleScene.scene->unk_2C == 0;
    other = &sActivePokemon[side]->state;
    self = &sActivePokemon[sBattleScene.scene->unk_2C]->state;
    mon = &sActivePokemon[side]->teamRoster->pokemonPicked[sActivePokemon[side]->state.rosterIndex];

    if (func_821217DC(2) != 0) {
        side = sBattleScene.scene->unk_2C;
        func_80041940(side == 0, 0, mon->unk_26, side);
        func_8212188C();
        func_82125570();
        func_8211EE8C();
        sBattleScene.scene->unk_20++;
        if (other->unk_2D == 0x10) {
            sBattleScene.scene->unk_14 = 0;
            sBattleScene.scene->unk_20 = 0;
            if (self->unk_2D == 0x11) {
                sBattleScene.scene->unk_38 = 5;
                side = sBattleScene.scene->unk_2C == 0;
                sBattleScene.scene->unk_2C = side;
            } else if (self->unk_2D == 0x12) {
                sBattleScene.scene->unk_38 = 5;
                side = sBattleScene.scene->unk_2C == 0;
                sBattleScene.scene->unk_2C = side;
            } else {
                sBattleScene.scene->unk_38 = 4;
            }
        } else if (self->unk_2D == 0x12) {
            sBattleScene.scene->unk_14 = 0;
            sBattleScene.scene->unk_20 = 0;
            sBattleScene.scene->unk_38 = 5;
            side = sBattleScene.scene->unk_2C == 0;
            sBattleScene.scene->unk_2C = side;
        } else {
            sBattleScene.scene->unk_40 = sBattleScene.scene->unk_2C + 1;
            func_80043A10();
        }
        func_80040738();
    }
}

void func_82126A1C(UNUSED CameraNode* arg0) {
}

void func_82126A24(CameraNode* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    ActivePokemonState* state = &sActivePokemon[!sBattleScene.scene->unk_2C]->state;
    u8* rec = D_82189180[!sBattleScene.scene->unk_2C] + 0x79B;
    u16 sel;

    if (func_82101F84((s8*)sActivePokemon[!sBattleScene.scene->unk_2C]) == 0) {
        if (sBattleScene.scene->unk_14 == 0x1D) {
            for (;;) {
                sel = func_8210C020(4);
                if (sel != 3) {
                    break;
                }
            }
            func_821261A0(sActivePokemon[!sBattleScene.scene->unk_2C], arg0, sel);
        }
        if (func_82121820(0x1E) != 0) {
            func_821235E0(arg0, sActivePokemon[!sBattleScene.scene->unk_2C]);
        }
        if ((rec[4] >> 1) == (sActivePokemon[!sBattleScene.scene->unk_2C]->displayObject.transformAnim.frameFixed >> 16)) {
            func_8211EE8C();
            func_8211F034(D_8219A520 + 0x448 + (!sBattleScene.scene->unk_2C << 6), !sBattleScene.scene->unk_2C);
        }
        if (rec[0xA] == (sActivePokemon[!sBattleScene.scene->unk_2C]->displayObject.transformAnim.frameFixed >> 16) + 1) {
            func_8211EE8C();
            if (state->unk_2D != 0x12) {
                func_8211F034(D_8219A520 + 0x1C8, !sBattleScene.scene->unk_2C);
            }
            sActivePokemon[!sBattleScene.scene->unk_2C]->displayObject.node.renderFlags &= ~0x20;
            func_82105E38(sActivePokemon[!sBattleScene.scene->unk_2C], 0x100);
            func_8212188C();
            func_8212239C(sActivePokemon[!sBattleScene.scene->unk_2C], arg0);
            sBattleScene.scene->unk_20 = 2;
        }
    }
}

void BattleScene_PhaseSendOutAfterFaint(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            BattleScene_AdvanceSendOutPreparation(arg0);
            break;

        case 1:
            BattleScene_AdvanceSendOutCamera(arg0);
            break;

        case 2:
            BattleScene_AdvanceSendOutCameraClose(arg0);
            break;

        case 3:
            BattleScene_FinishSendOutCameraClose(arg0);
            break;

        case 4:
            BattleScene_CompleteSendOutFollowup(arg0);
            break;

        case 5:
            func_82126A1C(arg0);
            break;

        case 10:
            BattleScene_AdvanceSendOutFollowupCamera(arg0);
            break;
    }
}

void func_82126D20(UNUSED CameraNode* arg0) {
    ActivePokemonState* state;
    UNUSED s32 pad[2]; // FAKE: stack padding
    BattleMon* mon;
    s32 side;

    side = sBattleScene.scene->unk_2C == 0;
    state = &sActivePokemon[side]->state;
    mon = &sActivePokemon[side]->teamRoster->pokemonPicked[sActivePokemon[side]->state.rosterIndex];

    if (func_821217DC(2) != 0) {
        side = sBattleScene.scene->unk_2C;
        func_80041940(side == 0, 0, mon->unk_26, side);
        func_8212188C();
        func_82125570();
        func_8211EE8C();
        sBattleScene.scene->unk_20++;
        if (state->unk_2D == 0x10) {
            sBattleScene.scene->unk_14 = 0;
            sBattleScene.scene->unk_20 = 0;
            sBattleScene.scene->unk_38 = 4;
        } else {
            sBattleScene.scene->unk_40 = sBattleScene.scene->unk_2C + 1;
            func_80043A10();
        }
        func_80040738();
    }
}

void func_82126E34(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            BattleScene_AdvanceSendOutPreparation(arg0);
            break;

        case 1:
            BattleScene_AdvanceSendOutCamera(arg0);
            break;

        case 2:
            BattleScene_AdvanceSendOutCameraClose(arg0);
            break;

        case 3:
            BattleScene_FinishSendOutCameraClose(arg0);
            break;

        case 4:
            func_82126D20(arg0);
            break;

        case 5:
            func_82126A1C(arg0);
            break;

        case 10:
            BattleScene_AdvanceSendOutFollowupCamera(arg0);
            break;
    }
}

void func_82126EE0(CameraNode* arg0) {
    func_821255B4((s8*)arg0);
    func_82124A40();
    func_8211EE8C();
    func_821224F4();
    M2C_FIELD(D_8219A5A0, f32*, 0x74) = 0.0f;
    if (func_821217DC(0xA) != 0) {
        M2C_FIELD(D_8219A5A0, s32*, 0x20)++;
    }
    func_8000EEBC((s8*)arg0 + 0xB4, (s8*)arg0 + 0xA8, M2C_FIELD(D_8219A5A0, f32*, 0x5C), M2C_FIELD(D_8219A5A0, s16*, 0x58), M2C_FIELD(D_8219A5A0, s16*, 0x5A));
}

f32 func_8000F23C(f32, f32, f32, f32);
void func_8210C104(s16*, s16, s16);
void func_82126F70(CameraNode* arg0) {
    s8* sp34 = (s8*)D_8219A544;
    s8* sp30 = (s8*)D_8219A540;

    if (M2C_FIELD(D_8219A5A0, s32*, 0x1C) == 0xA) {
        M2C_FIELD(D_8219A5A0, f32*, 0x98) = func_8000F23C(M2C_FIELD(D_8219A5A0, f32*, 0x98), 0.05f, 0.03f, 0.03f);
        func_8210C1A8(&M2C_FIELD(D_8219A5A0, f32*, 0x74), 120.0f, M2C_FIELD(D_8219A5A0, f32*, 0x98));
        func_8210C104(&M2C_FIELD(D_8219A5A0, s16*, 0x58), 0xE38, M2C_FIELD(D_8219A5A0, f32*, 0x74));
        func_8210C1A8(&M2C_FIELD(D_8219A5A0, f32*, 0x5C), 250.0f, 0.055f);
        func_8210C1A8(&M2C_FIELD(arg0, f32*, 0x2C), 80.0f, 0.03f);
        func_8000EEBC((s8*)arg0 + 0xB4, (s8*)arg0 + 0xA8, M2C_FIELD(D_8219A5A0, f32*, 0x5C), M2C_FIELD(D_8219A5A0, s16*, 0x58), M2C_FIELD(D_8219A5A0, s16*, 0x5A));
        if (M2C_FIELD(D_8219A5A0, s16*, 0x58) == 0xE38) {
            func_82125594(arg0, 2);
        }
    } else {
        func_821079E8(0x2E36);
        if ((M2C_FIELD(sp34, f32*, 0x28) > 100.0f) && (M2C_FIELD(sp30, f32*, 0x28) > 100.0f)) {
            M2C_FIELD(D_8219A5A0, f32*, 0x98) = func_8000F23C(M2C_FIELD(D_8219A5A0, f32*, 0x98), 0.1f, 0.1f, 0.1f);
            func_8210C1A8(&M2C_FIELD(D_8219A5A0, f32*, 0x74), 120.0f, M2C_FIELD(D_8219A5A0, f32*, 0x98));
            func_8210C104(&M2C_FIELD(D_8219A5A0, s16*, 0x58), 0xE38, M2C_FIELD(D_8219A5A0, f32*, 0x74));
            func_8210C1A8(&M2C_FIELD(D_8219A5A0, f32*, 0x5C), 350.0f, 0.2f);
            func_8210C1A8(&M2C_FIELD(arg0, f32*, 0x2C), 80.0f, 0.02f);
        } else {
            M2C_FIELD(D_8219A5A0, f32*, 0x98) = func_8000F23C(M2C_FIELD(D_8219A5A0, f32*, 0x98), 0.2f, 0.1f, 0.1f);
            func_8210C1A8(&M2C_FIELD(D_8219A5A0, f32*, 0x74), 120.0f, M2C_FIELD(D_8219A5A0, f32*, 0x98));
            func_8210C104(&M2C_FIELD(D_8219A5A0, s16*, 0x58), 0xE38, M2C_FIELD(D_8219A5A0, f32*, 0x74));
            func_8210C1A8(&M2C_FIELD(D_8219A5A0, f32*, 0x5C), 250.0f, 0.2f);
            func_8210C1A8(&M2C_FIELD(arg0, f32*, 0x2C), 80.0f, 0.02f);
        }
        func_8000EEBC((s8*)arg0 + 0xB4, (s8*)arg0 + 0xA8, M2C_FIELD(D_8219A5A0, f32*, 0x5C), M2C_FIELD(D_8219A5A0, s16*, 0x58), M2C_FIELD(D_8219A5A0, s16*, 0x5A));
        if (M2C_FIELD(D_8219A5A0, s16*, 0x58) == 0xE38) {
            func_82125594(arg0, 2);
        }
    }
}

void BattleScene_Phase2(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_82126EE0(arg0);
            break;

        case 1:
            func_82126F70(arg0);
            break;

        case 2:
            func_82125594(arg0, 2);
            break;
    }
}

void func_821272C0(s8 *arg0) {
    M2C_FIELD(arg0, s16 *, 0x7BE) = 0x800;
}

void ModelAnim_SetFrame(DisplayObject* display_object, s16 animation_timer);
void func_821272CC(DisplayObject* arg0, s32 arg1) {
    s32 frames = M2C_FIELD(M2C_FIELD(arg0, s8**, 0x44), u16*, 0xA);

    if (M2C_FIELD(arg0, u16*, 0x7C2) & 2) {
        return;
    }
    /* Read through a second type so the halfword is loaded again, as in the original. */
    if ((u16)M2C_FIELD(arg0, s16*, 0x7C2) & 0x4000) {
        return;
    }
    ModelAnim_SetFrame(arg0, (arg1 / frames + 1) * frames - arg1);
}

f32 func_82121750(ActivePokemon*, f32, f32);
s16 func_82107CC4(ActivePokemon*);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);
void func_82127354(CameraNode* arg0) {
    s32 i;
    f32 sp58;
    f32 step;
    s8* scene = (s8*)sBattleScene.scene;

    switch (M2C_FIELD(scene, s32*, 0x3C)) {
        case 0:
            if (func_82124A50((ActivePokemon*)D_8219A544) == 0) {
                func_82124EB4();
                func_82108C0C(D_8219A544);
                func_82108C0C(D_8219A540);
                func_8213B31C(2);
                M2C_FIELD(sBattleScene.scene, s8*, 0x1B) = 0;
                func_821272C0((s8*)D_8219A544);
                func_821255EC((s8*)arg0);
                BattleAnim_GetOwnerDefaultAnchorPosition((ActivePokemon*)D_8219A544, &sBattleScene.scene->unk_D0);
                func_82134FD0((ActivePokemon*)D_8219A544);
                step = func_82121750((ActivePokemon*)D_8219A544, 3.5f, 300.0f);
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0, 0, M2C_FIELD(sBattleScene.scene, f32*, 0x74) = 150.0f, 0.0); // FAKE: store inside the call
                M2C_FIELD(sBattleScene.scene, f32*, 0xC0) = M2C_FIELD(arg0, f32*, 0xB4);
                M2C_FIELD(sBattleScene.scene, f32*, 0xC8) = M2C_FIELD(arg0, f32*, 0xBC);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, M2C_FIELD(D_8219A544, s16*, 0x20), M2C_FIELD(sBattleScene.scene, f32*, 0x5C) = step, 0.0); // FAKE: store inside the call
                func_82102010((ActivePokemon*)D_8219A544);
                func_82125580();
                func_821224F4();
                func_8211F034(D_8219A520 + 0x188, sBattleScene.scene->unk_2C);
                i = 0;
                step = 0.3f;
                sp58 = M2C_FIELD(sBattleScene.scene, f32*, 0x74);
                for (;;) {
                    M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = func_8000F23C(M2C_FIELD(sBattleScene.scene, f32*, 0x98), 0.7f, step, step);
                    func_8210C1A8(&sp58, 0.0f, M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
                    if (sp58 <= 0.05f) {
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)D_8219A544, i += 5); // FAKE: i += 5
                func_821224F4();
            }
            break;
        case 1:
            M2C_FIELD(scene, s32*, 0x50) = 4;
            BattleAnim_GetOwnerDefaultAnchorPosition((ActivePokemon*)D_8219A544, &sBattleScene.scene->unk_D0);
            if (func_82101FD4((ActivePokemon*)D_8219A544) != 0) {
                func_82121750((ActivePokemon*)D_8219A544, 3.5f, 300.0f);
                step = 0.3f;
                M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = func_8000F23C(M2C_FIELD(sBattleScene.scene, f32*, 0x98), 0.7f, step, step);
                func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0f, M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0, 0, M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0);
                M2C_FIELD(sBattleScene.scene, f32*, 0xC0) = M2C_FIELD(arg0, f32*, 0xB4);
                M2C_FIELD(sBattleScene.scene, f32*, 0xC8) = M2C_FIELD(arg0, f32*, 0xBC);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, M2C_FIELD(D_8219A544, s16*, 0x20), M2C_FIELD(sBattleScene.scene, f32*, 0x5C), 0.0);
                if (M2C_FIELD(sBattleScene.scene, f32*, 0x74) <= 0.05f) {
                    func_8211F034(D_8219A520 + 0x388, M2C_FIELD(sBattleScene.scene, u16*, 0x2C));
                    M2C_FIELD(sBattleScene.scene, s32*, 0x20)++;
                    func_82125570();
                }
            }
            break;
    }
}

void func_82127724(CameraNode* arg0) {
    s32 i;
    f32 dist;
    f32 step;
    s16 rate;

    BattleAnim_GetOwnerDefaultAnchorPosition((ActivePokemon*)D_8219A544, &sBattleScene.scene->unk_D0);
    switch (M2C_FIELD(sBattleScene.scene, s32*, 0x3C)) {
        case 0:
            if (func_82124A50((ActivePokemon*)D_8219A544) == 0) {
                func_8213B31C(2);
                M2C_FIELD(sBattleScene.scene, s8*, 0x1B) = 0;
                func_821272C0((s8*)D_8219A544);
                func_821255EC((s8*)arg0);
                func_82124EB4();
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0, M2C_FIELD(D_8219A544, s32*, 0x60C) << 0xE, M2C_FIELD(sBattleScene.scene, f32*, 0x74) = 150.0f, 0.0); // FAKE: store inside the call
                BattleScene_SetCameraEyeAndStoreAnglesFromAt(arg0, 0, M2C_FIELD(D_8219A544, s32*, 0x60C) * 0x16C, 600.0f, 0.0f);
                if (M2C_FIELD(arg0, f32*, 0xAC) <= 25.0f) {
                    M2C_FIELD(arg0, f32*, 0xAC) = 25.0f;
                }
                func_82134FD0((ActivePokemon*)D_8219A544);
                func_82102010((ActivePokemon*)D_8219A544);
                func_82125580();
                func_821224F4();
                func_8211F034(D_8219A520 + 0x188, sBattleScene.scene->unk_2C);
                i = 0;
                M2C_FIELD(sBattleScene.scene, f32*, 0x84) = 50.0f;
                step = 0.3f;
                for (;;) {
                    dist = func_82121750((ActivePokemon*)D_8219A544, 3.5f, 300.0f);
                    func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x84), 8.0f, step);
                    rate = (M2C_FIELD(sBattleScene.scene, s16*, 0x5A) - M2C_FIELD(D_8219A544, s32*, 0x60C) * 0x38E0) / (s16)M2C_FIELD(sBattleScene.scene, f32*, 0x84);
                    if (rate < 0) {
                        rate *= -1;
                    }
                    if (rate < 30) {
                        rate = 30;
                    }
                    if (BattleAnim_StepToS16(&M2C_FIELD(sBattleScene.scene, s16*, 0x5A), M2C_FIELD(D_8219A544, s32*, 0x60C) * 0x38E0, rate) != 0) {
                        func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x8C), step, 0.02f);
                        func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0f, M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
                    } else {
                        func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x88), 0.5f, 0.03f);
                        func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x5C), dist, M2C_FIELD(sBattleScene.scene, f32*, 0x88));
                    }
                    BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0, M2C_FIELD(D_8219A544, s32*, 0x60C) << 0xE, M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0);
                    BattleScene_SetCameraEyeFromAt(arg0, 0, M2C_FIELD(sBattleScene.scene, s16*, 0x5A), M2C_FIELD(sBattleScene.scene, f32*, 0x5C), 0.0f);
                    if (M2C_FIELD(sBattleScene.scene, f32*, 0x5C) < dist + 5.0f) {
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)D_8219A544, i += 5); // FAKE: i += 5
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0, M2C_FIELD(D_8219A544, s32*, 0x60C) << 0xE, M2C_FIELD(sBattleScene.scene, f32*, 0x74) = 150.0f, 0.0); // FAKE: store inside the call
                BattleScene_SetCameraEyeAndStoreAnglesFromAt(arg0, 0, M2C_FIELD(D_8219A544, s32*, 0x60C) * 0x16C, 600.0f, 0.0f);
                if (M2C_FIELD(arg0, f32*, 0xAC) <= 25.0f) {
                    M2C_FIELD(arg0, f32*, 0xAC) = 25.0f;
                }
                func_821224F4();
                M2C_FIELD(sBattleScene.scene, f32*, 0x84) = 50.0f;
            }
            break;
        case 1:
            if (func_82101FD4((ActivePokemon*)D_8219A544) != 0) {
                step = 0.3f;
                dist = func_82121750((ActivePokemon*)D_8219A544, 3.5f, 300.0f);
                func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x84), 8.0f, step);
                rate = (M2C_FIELD(sBattleScene.scene, s16*, 0x5A) - M2C_FIELD(D_8219A544, s32*, 0x60C) * 0x38E0) / (s16)M2C_FIELD(sBattleScene.scene, f32*, 0x84);
                if (rate < 0) {
                    rate *= -1;
                }
                if (rate < 30) {
                    rate = 30;
                }
                if (BattleAnim_StepToS16(&M2C_FIELD(sBattleScene.scene, s16*, 0x5A), M2C_FIELD(D_8219A544, s32*, 0x60C) * 0x38E0, rate) != 0) {
                    func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x8C), step, 0.02f);
                    func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0f, M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
                } else {
                    func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x88), 0.5f, 0.03f);
                    func_8210C1A8(&M2C_FIELD(sBattleScene.scene, f32*, 0x5C), dist, M2C_FIELD(sBattleScene.scene, f32*, 0x88));
                }
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0, M2C_FIELD(D_8219A544, s32*, 0x60C) << 0xE, M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0);
                BattleScene_SetCameraEyeFromAt(arg0, 0, M2C_FIELD(sBattleScene.scene, s16*, 0x5A), M2C_FIELD(sBattleScene.scene, f32*, 0x5C), 0.0f);
                if (M2C_FIELD(sBattleScene.scene, f32*, 0x5C) < dist + 5.0f) {
                    func_8211F034(D_8219A520 + 0x388, M2C_FIELD(sBattleScene.scene, u16*, 0x2C));
                    M2C_FIELD(sBattleScene.scene, s32*, 0x20)++;
                    func_82125570();
                }
                if (M2C_FIELD(arg0, f32*, 0xAC) <= 25.0f) {
                    M2C_FIELD(arg0, f32*, 0xAC) = 25.0f;
                }
            }
            break;
    }
}

extern f32 D_FLT_8218935C[][4];
f32 func_82121750(ActivePokemon*, f32, f32);
s16 func_82107CC4(ActivePokemon*);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);
void func_82127DFC(CameraNode* arg0) {
    s32 i;
    f32 sp68;
    f32 step;

    switch (M2C_FIELD(sBattleScene.scene, s32*, 0x3C)) {
        case 0:
            if (func_82124A50((ActivePokemon*)D_8219A544) == 0) {
                func_82124EB4();
                func_82108C0C(D_8219A544);
                func_82108C0C(D_8219A540);
                func_8213B31C(2);
                M2C_FIELD(sBattleScene.scene, s8*, 0x1B) = 0;
                func_821272C0((s8*)D_8219A544);
                func_821255EC((s8*)arg0);
                BattleAnim_GetOwnerDefaultAnchorPosition((ActivePokemon*)D_8219A544, &sBattleScene.scene->unk_D0);
                step = func_82121750((ActivePokemon*)D_8219A544, 3.5f, 250.0f);
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0, func_82107CC4((ActivePokemon*)D_8219A544), 0.0f, func_82107EC8((ActivePokemon*)D_8219A544) * 2.5f);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, func_82107CC4((ActivePokemon*)D_8219A544), step, 0.0f);
                func_8211F034(D_8219A520 + 0x188, sBattleScene.scene->unk_2C);
                func_82134FD0((ActivePokemon*)D_8219A544);
                func_82102010((ActivePokemon*)D_8219A544);
                func_82125580();
                func_821224F4();
                i = 0;
                step = 0.1f;
                sp68 = M2C_FIELD(arg0, f32*, 0xB8);
                while (TRUE) {
                    M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = func_8000F23C(M2C_FIELD(sBattleScene.scene, f32*, 0x8C), 0.2f, step, step);
                    func_8210C1A8(&sp68, M2C_FIELD(sBattleScene.scene, f32*, 0xC4) + D_FLT_8218935C[((ActivePokemon*)D_8219A544)->displayObject.objectType - 1][3], M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
                    if (sp68 <= (M2C_FIELD(sBattleScene.scene, f32*, 0xC4) + step) + D_FLT_8218935C[((ActivePokemon*)D_8219A544)->displayObject.objectType - 1][3]) {
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)D_8219A544, i += 5); // FAKE: i += 5
                func_821224F4();
            }
            break;
        case 1:
            M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 4;
            if (func_82101FD4((ActivePokemon*)D_8219A544) != 0) {
                step = 0.1f;
                M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = func_8000F23C(M2C_FIELD(sBattleScene.scene, f32*, 0x8C), 0.2f, step, step);
                func_8210C1A8(&M2C_FIELD(arg0, f32*, 0xB8), M2C_FIELD(sBattleScene.scene, f32*, 0xC4) + D_FLT_8218935C[((ActivePokemon*)D_8219A544)->displayObject.objectType - 1][3], M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
                if (M2C_FIELD(arg0, f32*, 0xB8) <= (M2C_FIELD(sBattleScene.scene, f32*, 0xC4) + step) + D_FLT_8218935C[((ActivePokemon*)D_8219A544)->displayObject.objectType - 1][3]) {
                    func_8211F034(D_8219A520 + 0x388, M2C_FIELD(sBattleScene.scene, u16*, 0x2C));
                    M2C_FIELD(sBattleScene.scene, s32*, 0x20)++;
                    func_82125570();
                }
            }
            break;
    }
}

extern f32 D_FLT_8218935C[][4];
f32 func_82121750(ActivePokemon*, f32, f32);
s16 func_82107CC4(ActivePokemon*);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);
void func_8212817C(CameraNode* arg0) {
    s32 i;
    f32 sp68;
    f32 step;

    switch (M2C_FIELD(sBattleScene.scene, s32*, 0x3C)) {
        case 0:
            if (func_82124A50((ActivePokemon*)D_8219A544) == 0) {
                func_82124EB4();
                func_82108C0C(D_8219A544);
                func_82108C0C(D_8219A540);
                func_8213B31C(2);
                M2C_FIELD(sBattleScene.scene, s8*, 0x1B) = 0;
                func_821272C0((s8*)D_8219A544);
                func_821255EC((s8*)arg0);
                BattleAnim_GetOwnerDefaultAnchorPosition((ActivePokemon*)D_8219A544, &sBattleScene.scene->unk_D0);
                step = func_82121750((ActivePokemon*)D_8219A544, 3.5f, 250.0f);
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0, func_82107CC4((ActivePokemon*)D_8219A544), 0.0f, -func_82107EC8((ActivePokemon*)D_8219A544) * 1.5f);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, func_82107CC4((ActivePokemon*)D_8219A544), step, 0.0f);
                func_8211F034(D_8219A520 + 0x188, sBattleScene.scene->unk_2C);
                func_82102010((ActivePokemon*)D_8219A544);
                func_82125580();
                func_821224F4();
                func_82134FD0((ActivePokemon*)D_8219A544);
                i = 0;
                step = 0.1f;
                sp68 = M2C_FIELD(arg0, f32*, 0xB8);
                while (TRUE) {
                    M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = func_8000F23C(M2C_FIELD(sBattleScene.scene, f32*, 0x8C), 0.2f, step, step);
                    func_8210C1A8(&sp68, M2C_FIELD(sBattleScene.scene, f32*, 0xC4) + D_FLT_8218935C[((ActivePokemon*)D_8219A544)->displayObject.objectType - 1][3], M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
                    if ((M2C_FIELD(sBattleScene.scene, f32*, 0xC4) - step) + D_FLT_8218935C[((ActivePokemon*)D_8219A544)->displayObject.objectType - 1][3] <= sp68) {
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)D_8219A544, i += 5); // FAKE: i += 5
                func_821224F4();
            }
            break;
        case 1:
            M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 4;
            if ((func_82124A50((ActivePokemon*)D_8219A544) == 0) && (func_82101FD4((ActivePokemon*)D_8219A544) != 0)) {
                step = 0.1f;
                M2C_FIELD(sBattleScene.scene, f32*, 0x8C) = func_8000F23C(M2C_FIELD(sBattleScene.scene, f32*, 0x8C), 0.2f, step, step);
                func_8210C1A8(&M2C_FIELD(arg0, f32*, 0xB8), M2C_FIELD(sBattleScene.scene, f32*, 0xC4) + D_FLT_8218935C[((ActivePokemon*)D_8219A544)->displayObject.objectType - 1][3], M2C_FIELD(sBattleScene.scene, f32*, 0x8C));
                if (D_FLT_8218935C[((ActivePokemon*)D_8219A544)->displayObject.objectType - 1][3] + (M2C_FIELD(sBattleScene.scene, f32*, 0xC4) - step) <= M2C_FIELD(arg0, f32*, 0xB8)) {
                    func_8211F034(D_8219A520 + 0x388, M2C_FIELD(sBattleScene.scene, u16*, 0x2C));
                    M2C_FIELD(sBattleScene.scene, s32*, 0x20)++;
                    func_82125570();
                }
            }
            break;
    }
}

f32 func_82121750(ActivePokemon*, f32, f32);
s16 func_82107CC4(ActivePokemon*);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);
void func_82128510(CameraNode* arg0) {
    f32 sp44;
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp3A;
    s8* scene = D_8219A5A0;

    switch (M2C_FIELD(scene, s32*, 0x3C)) {
        case 0:
            if (func_82124A50((ActivePokemon*)D_8219A544) == 0) {
                func_82124EB4();
                func_82108C0C(D_8219A544);
                func_82108C0C(D_8219A540);
                func_8213B31C(2);
                M2C_FIELD(D_8219A5A0, s8*, 0x1B) = 0;
                func_821272C0((s8*)D_8219A544);
                func_821255EC((s8*)arg0);
                BattleAnim_GetOwnerDefaultAnchorPosition((ActivePokemon*)D_8219A544, &sBattleScene.scene->unk_D0);
                sp44 = func_82121750((ActivePokemon*)D_8219A544, 3.5f, 300.0f);
                sp3A = func_82107CC4((ActivePokemon*)D_8219A544);
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0, sp3A, 0.0f, 2.0f * -func_82107EC8((ActivePokemon*)D_8219A544));
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0, 0, func_82107CC4((ActivePokemon*)D_8219A544), sp44, -150.0f);
                func_8211F034(D_8219A520 + 0x188, sBattleScene.scene->unk_2C);
                func_82134FD0((ActivePokemon*)D_8219A544);
                func_82102010((ActivePokemon*)D_8219A544);
                func_82125580();
                func_821224F4();
            }
            break;
        case 1:
            M2C_FIELD(scene, s32*, 0x50) = 4;
            if (func_82101FD4((ActivePokemon*)D_8219A544) != 0) {
                func_8210C1A8(&M2C_FIELD(D_8219A5A0, f32*, 0x8C), 0.4f, 0.01f);
                func_8210C1A8(&M2C_FIELD(arg0, f32*, 0xB8), M2C_FIELD(D_8219A5A0, f32*, 0xC4), M2C_FIELD(D_8219A5A0, f32*, 0x8C));
                if ((M2C_FIELD(D_8219A5A0, f32*, 0xC4) - 1.0f) <= M2C_FIELD(arg0, f32*, 0xB8)) {
                    func_8211F034(D_8219A520 + 0x388, M2C_FIELD(D_8219A5A0, u16*, 0x2C));
                    M2C_FIELD(D_8219A5A0, s32*, 0x20)++;
                    func_82125570();
                }
            }
            break;
    }
}

void func_82128780(CameraNode* arg0) {
    if (sBattleScene.scene->unk_3C == 0) {
        D_8219A568 = BattleAnim_RandomRange(4);
        if (D_8219A568 >= 4) {
            D_8219A568 = 0;
        }
    }
    switch (D_8219A568) {
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
    }
}

/**
 * Camera step for D_8219A544, switched on scene field 0x3C. Case 0 dry-runs
 * the camera swing to count its frames (passed on to func_821272CC) and then
 * resets the camera; case 1 runs the swing for real and advances scene field
 * 0x20 once it settles.
 */
void func_82128848(CameraNode* arg0) {
    s32 pad; // FAKE
    s32 i;

    switch (M2C_FIELD(sBattleScene.scene, s32*, 0x3C)) {
        case 0:
            if (func_82124A50((ActivePokemon*)D_8219A544) == 0) {
                func_82124EB4();
                func_82108C0C(D_8219A544);
                func_82108C0C(D_8219A540);
                func_8213B31C(2);
                M2C_FIELD(sBattleScene.scene, s8*, 0x1B) = 0;
                func_821272C0((s8*)D_8219A544);
                func_821255EC((s8*)arg0);
                func_82134FD0((ActivePokemon*)D_8219A544);
                M2C_FIELD(sBattleScene.scene, f32*, 0x60) = M2C_FIELD(arg0, f32*, 0x2C);
                M2C_FIELD(arg0, f32*, 0x2C) = 100.0f;
                BattleAnim_GetOwnerDefaultAnchorPosition((ActivePokemon*)D_8219A544, &sBattleScene.scene->unk_D0);
                M2C_FIELD(sBattleScene.scene, f32*, 0x74) = func_82121750((ActivePokemon*)D_8219A544, 4.0f, 300.0f);
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0,
                                                  func_82107CC4((ActivePokemon*)D_8219A544), 0.0f, 0.0);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0,
                                                     M2C_FIELD(sBattleScene.scene, s16*, 0x6E) = -0x1554,
                                                     func_82107CC4((ActivePokemon*)D_8219A544),
                                                     M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0);
                func_8211F034(D_8219A520 + 0x188, sBattleScene.scene->unk_2C);
                func_82102010((ActivePokemon*)D_8219A544);
                func_82125580();
                func_821224F4();

                // Dry-run the camera move to count how many frames it takes.
                i = 0;
                for (;;) {
                    BattleAnim_StepToS16(&M2C_FIELD(sBattleScene.scene, s16*, 0x6E), 0x149E, 0x2D);
                    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0,
                                                         M2C_FIELD(sBattleScene.scene, s16*, 0x6E),
                                                         func_82107CC4((ActivePokemon*)D_8219A544),
                                                         M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0);
                    func_8210C1A8(&M2C_FIELD(arg0, f32*, 0x2C), M2C_FIELD(sBattleScene.scene, f32*, 0x60), 0.08f);
                    if (M2C_FIELD(arg0, f32*, 0x2C) < M2C_FIELD(sBattleScene.scene, f32*, 0x60) + 1.0f) {
                        M2C_FIELD(arg0, f32*, 0x2C) = M2C_FIELD(sBattleScene.scene, f32*, 0x60);
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)D_8219A544, i += 5); // FAKE: i is dead afterwards

                // Then reset the camera to its starting state.
                M2C_FIELD(sBattleScene.scene, f32*, 0x60) = M2C_FIELD(arg0, f32*, 0x2C);
                M2C_FIELD(arg0, f32*, 0x2C) = 100.0f;
                BattleAnim_GetOwnerDefaultAnchorPosition((ActivePokemon*)D_8219A544, &sBattleScene.scene->unk_D0);
                M2C_FIELD(sBattleScene.scene, f32*, 0x74) = func_82121750((ActivePokemon*)D_8219A544, 4.0f, 300.0f);
                BattleScene_SetCameraAtFromAnchor((ActivePokemon*)D_8219A544, arg0, sBattleScene.scene->unk_D0, 0,
                                                  func_82107CC4((ActivePokemon*)D_8219A544), 0.0f, 0.0);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0,
                                                     M2C_FIELD(sBattleScene.scene, s16*, 0x6E) = -0x1554,
                                                     func_82107CC4((ActivePokemon*)D_8219A544),
                                                     M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0);
                func_821224F4();
            }
            break;

        case 1:
            if (func_82101FD4((ActivePokemon*)D_8219A544) != 0) {
                M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 4;
                BattleAnim_StepToS16(&M2C_FIELD(sBattleScene.scene, s16*, 0x6E), 0x149E, 0x2D);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->unk_D0,
                                                     M2C_FIELD(sBattleScene.scene, s16*, 0x6E),
                                                     func_82107CC4((ActivePokemon*)D_8219A544),
                                                     M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0);
                func_8210C1A8(&M2C_FIELD(arg0, f32*, 0x2C), M2C_FIELD(sBattleScene.scene, f32*, 0x60), 0.08f);
                if (M2C_FIELD(arg0, f32*, 0x2C) < M2C_FIELD(sBattleScene.scene, f32*, 0x60) + 1.0f) {
                    func_8211F034(D_8219A520 + 0x388, M2C_FIELD(sBattleScene.scene, u16*, 0x2C));
                    M2C_FIELD(arg0, f32*, 0x2C) = M2C_FIELD(sBattleScene.scene, f32*, 0x60);
                    M2C_FIELD(sBattleScene.scene, s32*, 0x20)++;
                    func_82125570();
                }
            }
            break;
    }

    if (!arg0) {} // FAKE
}
