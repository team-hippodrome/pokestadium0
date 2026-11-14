/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "audio_commands.h"
#include "geo_node.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK func_80019B28(s32, u8, u8, u8, s32);
M2C_UNK func_800419F8();
M2C_UNK func_82106220();
M2C_UNK func_821079E8(M2C_UNK);
M2C_UNK func_82108C0C(s32);
M2C_UNK func_82121D78(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_821224F4();
M2C_UNK func_82124A40();
extern M2C_UNK D_8218B630;
extern f32 D_FLT_82189354[][4];
extern s32 D_82199DE0;
extern s32 D_82199DE4;
extern s32 D_8219A520;
// FAKE: sBattleScene.scene under a second symbol at the same address; func_82128510
// mixes it with sBattleScene, which is needed to match (IDO does not see the two alias).
extern BattleScene* D_8219A5A0;
extern u8 D_82199F31;
f32 BattleScene_GetParticipantHeight(s32);
s32 Battle_StepPartyHpToDisplay(s32);
s32 func_80041374(s32, u32);
s32 func_82124810(void*, void*);
u16 func_82107CA0(ActivePokemon* active_pokemon);
void BattleMessage_ShowForSide(s32, s32);
void BattleScene_CameraShotTargetHighThunk(void*, void*);
void func_8000EEBC(s8*, s8*, f32, s32, s32);
void func_80041940(s32, s32, s32, s32);
void func_8210C1A8(f32*, f32, f32);
void func_8211EE8C(void);
void func_8212188C(void);
void func_82124830(void*, void*);
void func_82124874(void*, void*);

extern s32 D_8219A570;
extern s32 D_8219A574;

/**
 * Sets the camera preset to 1 and ends the target's effect mode (func_82108C0C).
 */
void func_82124E80(void) {
    sBattleScene.scene->cameraPresetId = 1;
    func_82108C0C(sActingPokemon);
}

/**
 * Sets the camera preset to 3 and ends the effect mode of both the target and the user.
 */
void func_82124EB4(void) {
    sBattleScene.scene->cameraPresetId = 3;
    func_82108C0C(sActingPokemon);
    func_82108C0C(sOtherPokemon);
}

/**
 * Empty.
 */
void func_82124EF4(void) {
}

/**
 * Called once both actions are committed: sets the acting side from Battle_DetermineMoveOrder
 * (skipping a side with no move), records the order for the COM AI, enters phase 0 and resolves
 * the first action with Battle_ResolveMonAction. Ran in play from Battle_ChooseActions on a Struggle turn and
 * on the second turn of Razor Wind and Fly.
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran once both
 * actions were committed, just before the presentation entered phase 2.
 */
void Battle_StartTurn(void) {
    s32 sp24;
    ActivePokemonState* temp_s0;
    ActivePokemonState* temp_s1;
    BattleMonRuntime* ptr;

    temp_s0 = &sActivePokemon[0]->state;
    temp_s1 = &sActivePokemon[1]->state;
    BattleScene_SetCameraSubstate(1, 1);

    sp24 = sBattleScene.scene->actingSide;
    sBattleScene.scene->actingSide = Battle_DetermineMoveOrder(sActivePokemon[0], sActivePokemon[1]);

    ptr = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;
    if (ptr->usedMove == 0xFF) {
        sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
    }

    if (sActivePokemon[0]->teamRoster->isHuman & 2) {
        if (sBattleScene.scene->actingSide == 0) {
            BattleAi_RecordUsedMove(temp_s0->rosterIndex, temp_s1->rosterIndex, 0);
        } else {
            BattleAi_RecordUsedMove(temp_s0->rosterIndex, temp_s1->rosterIndex, 1);
        }
    } else if (sActivePokemon[1]->teamRoster->isHuman & 2) {
        if (sBattleScene.scene->actingSide == 1) {
            BattleAi_RecordUsedMove(temp_s1->rosterIndex, temp_s0->rosterIndex, 0);
        } else {
            BattleAi_RecordUsedMove(temp_s1->rosterIndex, temp_s0->rosterIndex, 1);
        }
    }

    sBattleScene.scene->sideCurrentlySwitching = sBattleScene.scene->actingSide;
    sBattleScene.scene->phase = 0;
    temp_s0->infoBoxBlinkTimer = 0;
    temp_s1->infoBoxBlinkTimer = 0;
    if (sBattleScene.scene->mode == 5) {
        sBattleScene.scene->unk_44 = 6;
    } else {
        sBattleScene.scene->unk_44 = 2;
    }
    Battle_ResolveMonAction();
    sBattleScene.scene->actingSide = sp24;
}

void BattleAi_RecordUsedMove(s32, s32, s32);
/**
 * When the acting side's action is a switch (0x0F) or a send-out (0x10), records it for the COM
 * AI and enters phase 11 or 18. Returns 1 if it did.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle and a Pound
 * turn.
 * @unverified Name and comment from the code.
 */
s32 BattleScene_TryStartSwitchAction(void) {
    ActivePokemonState* sp24;
    ActivePokemonState* sp20;
    ActivePokemonState* sp1C;

    sp24 = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    sp20 = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    sp1C = &sActivePokemon[!sBattleScene.scene->actingSide]->state;
    func_821079E8(0x1FFE);
    if ((sp24->faintState == 0xF) || (sp24->faintState == 0x10)) {
        if (*M2C_FIELD(sActivePokemon[sBattleScene.scene->actingSide], u8**, 0x860) & 2) {
            BattleAi_RecordUsedMove(sp20->rosterIndex, sp1C->rosterIndex, 2);
        }
        Battle_ClearRuntimeFlags(sActivePokemon[sBattleScene.scene->actingSide], 0x3800);
        sBattleScene.scene->phaseStep = 0;
        sBattleScene.scene->stepFrameTimer = 0;
        if (sp24->faintState == 0x10) {
            sBattleScene.scene->phase = 0x12;
        } else {
            sBattleScene.scene->phase = 0xB;
        }
        return 1;
    }
    return 0;
}

/**
 * Starts the switch-in for any side whose action is a switch (actions 0xF and 0x10),
 * human sides first, then restores the acting side.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleScene_InitializeSwitchActions(void) {
    s32 sp2C;
    ActivePokemonState* sp28;
    ActivePokemonState* sp24;

    sp28 = &sActivePokemon[0]->state;
    sp24 = &sActivePokemon[1]->state;
    BattleScene_SetCameraSubstate(1, 1);

    sp2C = sBattleScene.scene->actingSide;

    if ((sp28->faintState == 0xF) || (sp28->faintState == 0x10)) {
        if (sActivePokemon[0]->teamRoster->isHuman & 2) {
            BattleAi_RecordUsedMove(sp28->rosterIndex, sp24->rosterIndex, 2);
        }
        sBattleScene.scene->actingSide = 0;
        sBattleScene.scene->sideCurrentlySwitching = 0;
        sBattleScene.scene->phase = 0;
        sBattleScene.scene->unk_44 = 2;
        BeginBattleForEntity(sActivePokemon[0]);
        sBattleScene.scene->actingSide = sp2C;
    } else {
        if (sActivePokemon[0]->teamRoster->isHuman & 2) {
            BattleAi_RecordUsedMove(sp24->rosterIndex, sp28->rosterIndex, 2);
        }
        sBattleScene.scene->actingSide = 1;
        sBattleScene.scene->sideCurrentlySwitching = 1;
        sBattleScene.scene->phase = 0;
        sBattleScene.scene->unk_44 = 2;
        BeginBattleForEntity(sActivePokemon[1]);
        sBattleScene.scene->actingSide = sp2C;
    }
}

extern s32 D_82199DE0;
M2C_UNK func_800419F8();
void func_82121D8C(s32, s32, s8 *);
/**
 * Calls func_800419F8 on both Pokemon's records and clears their +0x10 fields, then calls
 * func_82121D8C(1, flag, side 1's record) with flag 0 in scene modes 4, 9 and 10, when
 * either side's state byte is 16 or when scene+0x2E is 2, and 1 otherwise. Sets scene+0x44
 * from the scene mode (5 for mode 6, 9 for mode 10, else 1) and advances the phase step.
 */
void func_82125384(void) {
    s8* a;
    s8* b;
    s32 st;

    a = M2C_FIELD(&D_82199DE0, s8 **, 0) + 0x78C;
    b = M2C_FIELD(&D_82199DE0, s8 **, 4) + 0x78C;
    func_800419F8(1, a, b);
    M2C_FIELD(a, s32 *, 0x10) = 0;
    M2C_FIELD(b, s32 *, 0x10) = 0;
    st = sBattleScene.scene->mode;
    if ((st == 4) || (st == 9) || (st == 0xA)) {
        func_82121D8C(1, 0, b);
    } else if ((M2C_FIELD(a, u8 *, 0x2E) == 0x10) || (M2C_FIELD(b, u8 *, 0x2E) == 0x10) || (sBattleScene.scene->transitionStyle == 2)) {
        func_82121D8C(1, 0, b);
    } else {
        func_82121D8C(1, 1, b);
    }
    st = sBattleScene.scene->mode;
    if (st == 6) {
        sBattleScene.scene->unk_44 = 5;
    } else if (st == 0xA) {
        sBattleScene.scene->unk_44 = 9;
    } else {
        sBattleScene.scene->unk_44 = 1;
    }
    sBattleScene.scene->phaseStep++;
}

void func_82133868(ActivePokemonState*);

// Stadium 1 counterpart: Battle_ActSecondAttacker (no phase/arg handling here).
/**
 * Called when the first action's presentation ends: flips the acting side, resolves that side's
 * action (a switch through BeginBattleForEntity, the scripted action in mode 10, otherwise
 * Battle_ResolveMonAction) and marks the second pass. BattleScene_CompleteActionPhase then enters
 * phase 3. In play phase 3 always followed phase 2 or 7 this way.
 * Seen in play (2026-11-12): in a turn where 1P's Poison Sting went first, it ran when that
 * action's presentation ended, before COM's Pinsir acted.
 */
void BattleScene_StartSecondAction(void) {
    ActivePokemonState* temp_a3;

    sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
    temp_a3 = &sActivePokemon[sBattleScene.scene->actingSide]->state;

    if ((temp_a3->faintState == 0xF) || (temp_a3->faintState == 0x10)) {
        BeginBattleForEntity(sActivePokemon[sBattleScene.scene->actingSide]);
    } else if (sBattleScene.scene->mode == 0xA) {
        func_82133868(temp_a3);
    } else {
        Battle_ResolveMonAction();
    }

    sBattleScene.scene->actionPass = 1;
    sBattleScene.scene->unk_90.z = 0.0f;
}

/**
 * Clears the scene's phase substep.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name guessed from the code.
 */
void BattleScene_ClearPhaseFlag(void) {
    sBattleScene.scene->phaseSubstep = 0;
}

/**
 * Sets the scene's phase substep to 1.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name guessed from the code.
 */
void BattleScene_SetPhaseFlag(void) {
    sBattleScene.scene->phaseSubstep = 1;
}

/**
 * Switches the battle scene to phase arg1 at step 0.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_SetPhase(UNUSED CameraNode* arg0, s32 arg1) {
    sBattleScene.scene->phase = arg1;
    sBattleScene.scene->phaseStep = 0;
}

/**
 * Sets the camera clip mask 0x1FFE and copies the camera's field of view (+0x2C) into
 * scene+0x60.
 */
void func_821255B4(s8 *arg0) {
    func_821079E8(0x1FFE);
    sBattleScene.scene->verticalFieldOfView = (f32) M2C_FIELD(arg0, f32 *, 0x2C);
}

/**
 * Sets the camera clip mask 0x1FFE and the field of view to 30, on the camera and in
 * scene+0x60.
 */
void func_821255EC(s8 *arg0) {
    func_821079E8(0x1FFE);
    M2C_FIELD(arg0, f32 *, 0x2C) = 30.0f;
    sBattleScene.scene->verticalFieldOfView = 30.0f;
}

/**
 * Ends the acting side's action: clears its rock-throwing flag, stored sounds and model
 * reload step. After the first action, goes to the second mover's phase (3) unless either
 * side has no move (0xFF) and the other side's state byte is not 15 or 16, in which case it
 * goes to the end-of-turn phase (4). After the second action, always goes to phase 4.
 */
void func_8212562C(void) {
    BattleMonRuntime* runtime;
    BattleMonRuntime* other_runtime;
    ActivePokemonState* other_state;
    s32 other;

    if (sBattleScene.scene->actionPass == 0) {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->actingSide]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        runtime = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;
        other = sBattleScene.scene->actingSide == 0;
        other_runtime = &sActivePokemon[other]->state.runtime;
        other_state = &sActivePokemon[other]->state;
        if ((runtime->usedMove == 0xFF) || (other_runtime->usedMove == 0xFF)) {
            if ((other_state->faintState != 0xF) && (other_state->faintState != 0x10)) {
                sBattleScene.scene->phaseStep = 0;
                sBattleScene.scene->stepFrameTimer = 0;
                sBattleScene.scene->phase = 4;
                return;
            }
        }
        BattleScene_StartSecondAction();
        sBattleScene.scene->phaseStep = 0;
        sBattleScene.scene->stepFrameTimer = 0;
        sBattleScene.scene->phase = 3;
    } else {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->actingSide]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        sBattleScene.scene->phaseStep = 0;
        sBattleScene.scene->stepFrameTimer = 0;
        sBattleScene.scene->phase = 4;
    }
}

/**
 * If the target is seeded or badly poisoned and has used no move (0xFF), ends the action
 * and moves on to the second mover's phase (3). Returns 1 if it did.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (12 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleScene_HandleFaintStatusCompletion(void) {
    s8* temp_v0 = (s8*)sOtherPokemon + 0x7C6;

    if (((M2C_FIELD(temp_v0, u8*, 0x4D) & 0x80) || (M2C_FIELD(temp_v0, u8*, 0x15) & 0x18)) && (M2C_FIELD(temp_v0, u8*, 0x5A) == 0xFF)) {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->actingSide]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        BattleScene_StartSecondAction();
        sBattleScene.scene->phaseStep = 0;
        sBattleScene.scene->stepFrameTimer = 0;
        sBattleScene.scene->phase = 3;
        return 1;
    }
    return 0;
}

/**
 * Ends the current action: after the first mover's action, goes on to the second mover
 * (phase 3) unless the target has no move; otherwise goes to the end-of-turn phase (4).
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (162 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_CompleteActionPhase(void) {
    if ((sBattleScene.scene->actionPass == 0) && ((sOtherPokemon)->state.runtime.usedMove != 0xFF)) {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->actingSide]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        BattleScene_StartSecondAction();
        sBattleScene.scene->phaseStep = 0;
        sBattleScene.scene->stepFrameTimer = 0;
        sBattleScene.scene->phase = 3;
    } else if (BattleScene_HandleFaintStatusCompletion() == 0) {
        BattleAnim_ClearRockThrowingMoveFlag(sActivePokemon[sBattleScene.scene->actingSide]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        sBattleScene.scene->phaseStep = 0;
        sBattleScene.scene->stepFrameTimer = 0;
        sBattleScene.scene->phase = 4;
    }
}

/**
 * Switches to phase arg0, clearing the substep, frame timers, move effect kind and Rage
 * follow-up. Returns 1.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (75 of the moves).
 * @unverified Name guessed from the code.
 */
s32 BattleScene_TransitionToPhaseFull(s32 arg0) {
    BattleScene_ClearPhaseFlag();
    BattleScene_ResetCameraFrameCounter();
    sBattleScene.scene->moveEffectKind = 0;
    sBattleScene.scene->rageFollowupPhase = 0;
    sBattleScene.scene->phaseStep = 0;
    sBattleScene.scene->stepFrameTimer = 0;
    sBattleScene.scene->phase = arg0;
    return 1;
}

/**
 * Like BattleScene_TransitionToPhaseFull but keeps the move effect kind.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name guessed from the code.
 */
s32 BattleScene_TransitionToPhase(s32 arg0) {
    BattleScene_ClearPhaseFlag();
    BattleScene_ResetCameraFrameCounter();
    sBattleScene.scene->rageFollowupPhase = 0;
    sBattleScene.scene->phaseStep = 0;
    sBattleScene.scene->stepFrameTimer = 0;
    sBattleScene.scene->phase = arg0;
    return 1;
}

/**
 * Once both HP bars have finished moving, goes to the faint phase (5) for a side that
 * fainted, or on to the next step if neither did.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_ResolveDisplayedHpCompletion(CameraNode* arg0) {
    if ((D_8219A560 == 1) && (D_8219A564 == 1)) {
        BattleScene_ResetCameraFrameCounter();
        func_8211EE8C();
        BattleScene_ClearPhaseFlag();
        if (func_82107CA0(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
            BattleScene_SetPhase(arg0, 5);
            sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
        } else if (func_82107CA0(sActivePokemon[!sBattleScene.scene->actingSide]) == 0) {
            BattleScene_SetPhase(arg0, 5);
        } else {
            func_82125838();
        }
    }
}

/**
 * Updates the HP displays and goes to the faint phase for the acting Pokémon if it has 0
 * HP, or the next step if the other Pokémon fainted or neither did.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (162 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_UpdateDisplayedHpAndTransition(CameraNode* arg0) {
    BattleMonRuntime* sp1C = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;

    func_82125570();
    func_8212188C();
    func_8211EE8C();
    func_82106220(sOtherPokemon);

    if (Battle_GetActiveMonHp(sActivePokemon[sBattleScene.scene->actingSide]) == 0) {
        sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
        func_82125594(arg0, 5);
    } else if (Battle_GetActiveMonHp(sActivePokemon[!sBattleScene.scene->actingSide]) == 0) {
        func_821259E8(arg0);
    } else if (sBattleScene.scene->rageFollowupPhase == 0xA) {
        func_82125990(0xA);
    } else if (sBattleScene.scene->moveEffectKind == 9) {
        func_82125930(9);
    } else if ((sp1C->statusCondition & 0x18) || (sp1C->volatileStatusFlags & 0x80)) {
        func_82125930(6);
    } else {
        func_821259E8(arg0);
    }
}

/**
 * Steps both parties' displayed HP toward their real HP, storing whether each is done in
 * D_8219A560/D_8219A564, then runs the HP bar step func_82125AC8.
 */
void func_82125C34(s32 arg0) {
    D_8219A560 = Battle_StepPartyHpToDisplay(D_82199DE0);
    D_8219A564 = Battle_StepPartyHpToDisplay(D_82199DE4);
    func_82125AC8(arg0);
}

/**
 * Once both parties' displayed HP has caught up, sets camera preset 1 and runs the HP bar
 * step func_82125AC8.
 */
void func_82125C80(s32 arg0) {
    if ((D_8219A560 == 1) && (D_8219A564 == 1)) {
        sBattleScene.scene->cameraPresetId = 1;
        func_82125AC8(arg0);
    }
}

/**
 * Enters the effect phase for moves whose presentation replaces the attack animation
 * (moveEffectKind 7, 12-15, 17, 21, 25, 27-31), via BattleScene_TransitionToPhaseFull. Returns 1
 * if it did.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle and a Pound
 * turn.
 * @unverified Name and comment from the code; kind 7 to phase 7 seen in play with Double Team.
 */
s32 BattleScene_TryEnterEffectPhaseBeforeLaunch(void) {
    s32 temp_v0;

    temp_v0 = sBattleScene.scene->moveEffectKind;
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

/**
 * Enters the effect phase that follows the launch: the miss (8, also when Battle_MoveMissed
 * flagged it), status (22), confusion self-hit (20), Disable (32), stat lowering (26), crash (16)
 * and 23. Returns 1 if it did.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle and a Pound
 * turn.
 * @unverified Name and comment from the code; the miss path seen in play.
 */
s32 BattleScene_TryEnterEffectPhaseBeforeImpact(void) {
    s32 temp_v0;

    temp_v0 = sBattleScene.scene->moveEffectKind;
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

/**
 * If the acting Pokémon is seeded or poisoned/burned (status 0x18) and used no move,
 * switches to the residual damage phase (35) and returns 1.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleScene_PrepareResidualStatusPresentation(void) {
    s32 idx = sBattleScene.scene->actingSide;
    BattleMonRuntime* temp_v1_2 = &sActivePokemon[idx]->state.runtime;

    if (((temp_v1_2->volatileStatusFlags & 0x80) || (temp_v1_2->statusCondition & 0x18)) && (temp_v1_2->usedMove == 0xFF)) {
        return BattleScene_TransitionToPhaseFull(0x23);
    }
    return 0;
}

/**
 * Points sActingPokemon at the acting Pokémon and sOtherPokemon at the other one, and clears
 * the camera preset.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_UpdateActiveOwnerPointers(void) {
    s32 idx;

    sActingPokemon = sActivePokemon[sBattleScene.scene->actingSide];
    idx = sBattleScene.scene->actingSide == 0;
    sOtherPokemon = sActivePokemon[idx];
    sBattleScene.scene->cameraPresetId = 0;
}

/**
 * Phase 0 of BattleScene_UpdatePhase: sets up the scene for a new turn, then the turn moves on to phase 1.
 */
void BattleScene_InitTurnPresentation(s32 arg0) {
    s8 *sp34;
    s8 *sp30;

    sp34 = sActingPokemon;
    sp30 = sOtherPokemon;
    func_800419F8(0);
    func_82121D78(arg0, 0x41A00000, 0x457A0000);
    func_82124A40();
    sBattleScene.scene->stepFrameTimer = 0;
    sBattleScene.scene->rotationX = 0;
    sBattleScene.scene->rotationY = 0;
    sBattleScene.scene->distance = (f32) D_FLT_821962A4;
    sBattleScene.scene->actionPass = 0;
    func_821224F4();
    func_82125570();
    if ((M2C_FIELD(sp34, f32 *, 0x28) > 100.0f) && (M2C_FIELD(sp30, f32 *, 0x28) > 100.0f)) {
        func_821218AC(arg0, M2C_FIELD(&D_8218B630, s32 *, 0), M2C_FIELD(&D_8218B630, f32 *, 4) + 200.0f, M2C_FIELD(&D_8218B630, s32 *, 8), sBattleScene.scene->distance, (s32) sBattleScene.scene->rotationX, (s32) sBattleScene.scene->rotationY);
    } else {
        func_821218AC(arg0, M2C_FIELD(&D_8218B630, s32 *, 0), M2C_FIELD(&D_8218B630, f32 *, 4), M2C_FIELD(&D_8218B630, s32 *, 8), sBattleScene.scene->distance, (s32) sBattleScene.scene->rotationX, (s32) sBattleScene.scene->rotationY);
    }
    func_82108C0C(D_82199DE0);
    func_82108C0C(D_82199DE4);
    sBattleScene.scene->phaseStep = (s32) (sBattleScene.scene->phaseStep + 1);
}

/**
 * Plays one of four target-camera shots for a faint: 3 at the faint start, a random 0 to 2 during
 * the collapse (BattleScene_FaintStepStart, BattleScene_FaintStepCollapse).
 * Player sweep: reached only by Self-Destruct and Explosion.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleCamera_PlayFaintShot(void* arg0, void* arg1, s32 arg2) {
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
        default:
            func_82124874(arg1, arg0);
            break;
    }
}

/**
 * Called by BattleScene_FaintStepStart. Returns 1 (after clearing flags 0x60C) when state flag
 * 0x200 is set, so the faint uses row 17. Otherwise clears the Fly/Dig flags (0x4008) and puts
 * the model back on the ground, clears sleep, restores full alpha, and returns 0 (row 0).
 * Player sweep: reached only by Self-Destruct and Explosion.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
s32 BattleScene_ResetFaintingMonState(ActivePokemon* active_pokemon) {
    UNUSED s32 pad; // FAKE: stack padding
    BattleMon* party_pokemon = &active_pokemon->teamRoster->pokemonPicked[active_pokemon->state.rosterIndex];
    ActivePokemonState* state = &active_pokemon->state;

    if (state->flags & 0x200) {
        Battle_ClearRuntimeFlags(active_pokemon, 0x60C);
        return 1;
    }
    if (state->flags & 0x80) {
        func_82136708(2, active_pokemon);
        Battle_ClearRuntimeFlags(active_pokemon, 0x80);
    }
    if (state->flags & 0x4008) {
        active_pokemon->displayObject.alpha = 0xFF;
        func_82136708(4, active_pokemon);
        active_pokemon->displayObject.position.y = D_FLT_82189354[active_pokemon->displayObject.objectType][0];
        active_pokemon->displayObject.node.renderFlags &= ~2;
        active_pokemon->displayObject.node.renderFlags |= 0x20;
        active_pokemon->displayObject.node.flags |= 1;
        Battle_ClearRuntimeFlags(active_pokemon, 0x4608);
    }
    if (party_pokemon->statusCondition & 7) {
        party_pokemon->statusCondition = 0;
        func_8210568C(active_pokemon, 0xB8, 1);
        func_82136708(3, active_pokemon);
        Battle_ClearRuntimeFlags(active_pokemon, 1);
    }
    state->alpha = 0xFF;
    func_80019B28((s32)active_pokemon, 0xFF, 0xFF, 0xFF, state->alpha);
    return 0;
}

/**
 * Faint, step 0: sets up the faint presentation (a frame or two before the message).
 * Seen in play (Pinsir fainting to Poison Sting); Stadium 1 used these steps for a send-out.
 */
void BattleScene_FaintStepStart(CameraNode* arg0) {
    if (func_82124A50(sActivePokemon[!sBattleScene.scene->actingSide]) == 0) {
        Battle_ClearRuntimeFlags(sActivePokemon[!sBattleScene.scene->actingSide], 0x3800);
        BattleCamera_PlayFaintShot(sActivePokemon[!sBattleScene.scene->actingSide], arg0, 3);
        Audio_FadeAndClearStoredSounds();
        BattleAnim_CleanupEffects(2);
        BattleScene_ResetCameraFrameCounter();
        Battle_ClearMessageCursor();
        BattleCamera_CaptureModelOrbit(sActivePokemon[!sBattleScene.scene->actingSide], arg0);
        if (BattleScene_ResetFaintingMonState(sActivePokemon[!sBattleScene.scene->actingSide]) != 0) {
            BattleScene_EnterStateRow(sActivePokemon[!sBattleScene.scene->actingSide], 0x11);
            sBattleScene.scene->phaseStep = 0xA;
        } else {
            BattleScene_EnterStateRow(sActivePokemon[!sBattleScene.scene->actingSide], 0);
            sBattleScene.scene->phaseStep += 1;
        }
    }
}

extern u8* D_82189180[];
s32 BattleAnim_IsAssetLoadBusy(ActivePokemon* arg0);
void func_821235E0(CameraNode*, ActivePokemon*);
void func_8211EE8C(void);
void ActivePokemon_SetStateFlags(ActivePokemon*, s32);
u16 func_8210C020(s32); // BattleAnim_RandomRange
/**
 * Faint, step 1: 「…は たおれた！」 and the fainting animation with sparkles (about 60 frames in play).
 * Seen in play (Pinsir fainting to Poison Sting); Stadium 1 used these steps for a send-out.
 */
void BattleScene_FaintStepCollapse(CameraNode* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    ActivePokemonState* state = &sActivePokemon[!sBattleScene.scene->actingSide]->state;
    u8* rec = D_82189180[!sBattleScene.scene->actingSide] + 0x72D;
    u16 sel;

    if (BattleAnim_IsAssetLoadBusy((s8*)sActivePokemon[!sBattleScene.scene->actingSide]) == 0) {
        if (sBattleScene.scene->stepFrameTimer == 0x1D) {
            for (;;) {
                sel = func_8210C020(4);
                if (sel != 3) {
                    break;
                }
            }
            BattleCamera_PlayFaintShot(sActivePokemon[!sBattleScene.scene->actingSide], arg0, sel);
        }
        if (func_82121820(0x1E) != 0) {
            func_821235E0(arg0, sActivePokemon[!sBattleScene.scene->actingSide]);
        }
        if ((rec[4] >> 1) == (sActivePokemon[!sBattleScene.scene->actingSide]->displayObject.transformAnim.frameFixed >> 16)) {
            func_8211EE8C();
            BattleMessage_ShowForSide(D_8219A520 + 0x448 + (!sBattleScene.scene->actingSide << 6), !sBattleScene.scene->actingSide);
        }
        if (rec[0xA] == (sActivePokemon[!sBattleScene.scene->actingSide]->displayObject.transformAnim.frameFixed >> 16) + 3) {
            func_8211EE8C();
            if (state->faintState != 0x12) {
                BattleMessage_ShowForSide(D_8219A520 + 0x1C8, !sBattleScene.scene->actingSide);
            }
            sActivePokemon[!sBattleScene.scene->actingSide]->displayObject.node.renderFlags &= ~0x20;
            ActivePokemon_SetStateFlags(sActivePokemon[!sBattleScene.scene->actingSide], 0x100);
            func_8212188C();
            sBattleScene.scene->phaseStep++;
        }
        func_821229AC(arg0, sActivePokemon[!sBattleScene.scene->actingSide]);
    }
}

/**
 * Faint, step 2: the fainted Pokemon turns into a ball of light and disappears.
 * Seen in play (Pinsir fainting to Poison Sting); Stadium 1 used these steps for a send-out.
 */
void BattleScene_FaintStepVanish(CameraNode* arg0) {
    func_821229AC(arg0, sActivePokemon[!sBattleScene.scene->actingSide]);
    if (BattleScene_AdvanceCameraFrameCounter(0x19) != 0) {
        func_8211EE8C();
        Audio_FadeAndClearStoredSounds();
        sBattleScene.scene->phaseStep++;
    }
}

/**
 * Faint, step 3: waits 5 camera frames, then marks the Pokemon fainted (state 0x10).
 * Seen in play (Pinsir fainting to Poison Sting); Stadium 1 used these steps for a send-out.
 */
void BattleScene_FaintStepFinishVanish(CameraNode* arg0) {
    ActivePokemonState* temp_s0 = &sActivePokemon[!sBattleScene.scene->actingSide]->state;

    func_821229AC(arg0, sActivePokemon[!sBattleScene.scene->actingSide]);

    if (BattleScene_AdvanceCameraFrameCounter(5) != 0) {
        BattleAnim_CleanupEffects(1);
        func_80041374(3, 0);

        if (temp_s0->faintState != 0x12) {
            temp_s0->faintState = 0x10;
        }

        if (temp_s0->faintState == 0x12) {
            temp_s0->faintState = 0x13;
        }

        sBattleScene.scene->phaseStep++;
    }
}

/**
 * Faint, step 4: refreshes the HUD, then goes to the end of the turn (phase 4), to the other side's faint (phase 5) or sets the winner when that side has nothing left.
 * Seen in play (Pinsir fainting to Poison Sting); Stadium 1 used these steps for a send-out.
 */
void BattleScene_FaintStepEnd(UNUSED CameraNode* arg0) {
    ActivePokemonState* other;
    ActivePokemonState* self;
    s32 side;
    BattleMon* mon;

    side = sBattleScene.scene->actingSide == 0;
    other = &sActivePokemon[side]->state;
    self = &sActivePokemon[sBattleScene.scene->actingSide]->state;
    mon = &sActivePokemon[side]->teamRoster->pokemonPicked[sActivePokemon[side]->state.rosterIndex];

    if (func_821217DC(2) != 0) {
        side = sBattleScene.scene->actingSide;
        func_80041940(side == 0, 0, mon->maxHp, side);
        func_8212188C();
        func_82125570();
        func_8211EE8C();
        sBattleScene.scene->phaseStep++;
        if (other->faintState == 0x10) {
            sBattleScene.scene->stepFrameTimer = 0;
            sBattleScene.scene->phaseStep = 0;
            if (self->faintState == 0x11) {
                sBattleScene.scene->phase = 5;
                side = sBattleScene.scene->actingSide == 0;
                sBattleScene.scene->actingSide = side;
            } else if (self->faintState == 0x12) {
                sBattleScene.scene->phase = 5;
                side = sBattleScene.scene->actingSide == 0;
                sBattleScene.scene->actingSide = side;
            } else {
                sBattleScene.scene->phase = 4;
            }
        } else if (self->faintState == 0x12) {
            sBattleScene.scene->stepFrameTimer = 0;
            sBattleScene.scene->phaseStep = 0;
            sBattleScene.scene->phase = 5;
            side = sBattleScene.scene->actingSide == 0;
            sBattleScene.scene->actingSide = side;
        } else {
            sBattleScene.scene->winner = sBattleScene.scene->actingSide + 1;
            func_80043A10();
        }
        Audio_FadeAndClearStoredSounds();
    }
}

/**
 * Empty camera step.
 */
void func_82126A1C(UNUSED CameraNode* arg0) {
}

/**
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleScene_AdvanceSendOutFollowupCamera(CameraNode* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    ActivePokemonState* state = &sActivePokemon[!sBattleScene.scene->actingSide]->state;
    u8* rec = D_82189180[!sBattleScene.scene->actingSide] + 0x79B;
    u16 sel;

    if (BattleAnim_IsAssetLoadBusy((s8*)sActivePokemon[!sBattleScene.scene->actingSide]) == 0) {
        if (sBattleScene.scene->stepFrameTimer == 0x1D) {
            for (;;) {
                sel = func_8210C020(4);
                if (sel != 3) {
                    break;
                }
            }
            BattleCamera_PlayFaintShot(sActivePokemon[!sBattleScene.scene->actingSide], arg0, sel);
        }
        if (func_82121820(0x1E) != 0) {
            func_821235E0(arg0, sActivePokemon[!sBattleScene.scene->actingSide]);
        }
        if ((rec[4] >> 1) == (sActivePokemon[!sBattleScene.scene->actingSide]->displayObject.transformAnim.frameFixed >> 16)) {
            func_8211EE8C();
            BattleMessage_ShowForSide(D_8219A520 + 0x448 + (!sBattleScene.scene->actingSide << 6), !sBattleScene.scene->actingSide);
        }
        if (rec[0xA] == (sActivePokemon[!sBattleScene.scene->actingSide]->displayObject.transformAnim.frameFixed >> 16) + 1) {
            func_8211EE8C();
            if (state->faintState != 0x12) {
                BattleMessage_ShowForSide(D_8219A520 + 0x1C8, !sBattleScene.scene->actingSide);
            }
            sActivePokemon[!sBattleScene.scene->actingSide]->displayObject.node.renderFlags &= ~0x20;
            ActivePokemon_SetStateFlags(sActivePokemon[!sBattleScene.scene->actingSide], 0x100);
            func_8212188C();
            BattleCamera_CaptureModelOrbit(sActivePokemon[!sBattleScene.scene->actingSide], arg0);
            sBattleScene.scene->phaseStep = 2;
        }
    }
}

/**
 * Phase 5: a Pokemon faints (seen in play: ひんし shown during this phase, then phase 4). The step helpers it calls still carry Stadium 1 send-out names, which may be wrong.
 */
void BattleScene_PhaseFaint(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_FaintStepStart(arg0);
            break;

        case 1:
            BattleScene_FaintStepCollapse(arg0);
            break;

        case 2:
            BattleScene_FaintStepVanish(arg0);
            break;

        case 3:
            BattleScene_FaintStepFinishVanish(arg0);
            break;

        case 4:
            BattleScene_FaintStepEnd(arg0);
            break;

        case 5:
            func_82126A1C(arg0);
            break;

        case 10:
            BattleScene_AdvanceSendOutFollowupCamera(arg0);
            break;
    }
}

/**
 * Last step of the faint sequence in phase 34: after 2 frames, updates the fainted side's
 * HUD, clears the camera and message state and advances. If the other side's state byte is
 * 16 the battle continues at phase 4; otherwise the acting side wins (winner = side + 1).
 */
void func_82126D20(UNUSED CameraNode* arg0) {
    ActivePokemonState* state;
    UNUSED s32 pad[2]; // FAKE: stack padding
    BattleMon* mon;
    s32 side;

    side = sBattleScene.scene->actingSide == 0;
    state = &sActivePokemon[side]->state;
    mon = &sActivePokemon[side]->teamRoster->pokemonPicked[sActivePokemon[side]->state.rosterIndex];

    if (func_821217DC(2) != 0) {
        side = sBattleScene.scene->actingSide;
        func_80041940(side == 0, 0, mon->maxHp, side);
        func_8212188C();
        func_82125570();
        func_8211EE8C();
        sBattleScene.scene->phaseStep++;
        if (state->faintState == 0x10) {
            sBattleScene.scene->stepFrameTimer = 0;
            sBattleScene.scene->phaseStep = 0;
            sBattleScene.scene->phase = 4;
        } else {
            sBattleScene.scene->winner = sBattleScene.scene->actingSide + 1;
            func_80043A10();
        }
        Audio_FadeAndClearStoredSounds();
    }
}

/**
 * Phase 34, a faint that can end the battle: steps 0-3 are the faint collapse and vanish,
 * step 4 is func_82126D20, and the later steps run the send-out follow-up camera.
 */
void func_82126E34(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
        case 0:
            BattleScene_FaintStepStart(arg0);
            break;

        case 1:
            BattleScene_FaintStepCollapse(arg0);
            break;

        case 2:
            BattleScene_FaintStepVanish(arg0);
            break;

        case 3:
            BattleScene_FaintStepFinishVanish(arg0);
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

/**
 * Camera step: keeps the field of view, clears camera and message state, zeroes the zoom and
 * advances the phase step after 10 frames, placing the eye from the stored distance and
 * angles.
 */
void func_82126EE0(CameraNode* arg0) {
    func_821255B4((s8*)arg0);
    func_82124A40();
    func_8211EE8C();
    func_821224F4();
    sBattleScene.scene->orbitDistance = 0.0f;
    if (func_821217DC(0xA) != 0) {
        sBattleScene.scene->phaseStep++;
    }
    func_8000EEBC((s8*)arg0 + 0xB4, (s8*)arg0 + 0xA8, sBattleScene.scene->distance, sBattleScene.scene->rotationX, sBattleScene.scene->rotationY);
}

f32 func_8000F23C(f32, f32, f32, f32);
void func_8210C104(s16*, s16, s16);
/**
 * Camera step that pulls back to an overview: in scene mode 10 it eases the zoom to 120,
 * the pitch to 0xE38, the distance to 250 and the field of view to 80, then moves on with
 * func_82125594(2). Otherwise it does the same toward 350 once both models are above height
 * 100.
 */
void func_82126F70(CameraNode* arg0) {
    s8* sp34 = (s8*)sActingPokemon;
    s8* sp30 = (s8*)sOtherPokemon;

    if (sBattleScene.scene->mode == 0xA) {
        sBattleScene.scene->unk_90.z = func_8000F23C(sBattleScene.scene->unk_90.z, 0.05f, 0.03f, 0.03f);
        func_8210C1A8(&sBattleScene.scene->orbitDistance, 120.0f, sBattleScene.scene->unk_90.z);
        func_8210C104(&sBattleScene.scene->rotationX, 0xE38, sBattleScene.scene->orbitDistance);
        func_8210C1A8(&sBattleScene.scene->distance, 250.0f, 0.055f);
        func_8210C1A8(&arg0->perspective.verticalFieldOfView, 80.0f, 0.03f);
        func_8000EEBC((s8*)arg0 + 0xB4, (s8*)arg0 + 0xA8, sBattleScene.scene->distance, sBattleScene.scene->rotationX, sBattleScene.scene->rotationY);
        if (sBattleScene.scene->rotationX == 0xE38) {
            func_82125594(arg0, 2);
        }
    } else {
        func_821079E8(0x2E36);
        if ((M2C_FIELD(sp34, f32*, 0x28) > 100.0f) && (M2C_FIELD(sp30, f32*, 0x28) > 100.0f)) {
            sBattleScene.scene->unk_90.z = func_8000F23C(sBattleScene.scene->unk_90.z, 0.1f, 0.1f, 0.1f);
            func_8210C1A8(&sBattleScene.scene->orbitDistance, 120.0f, sBattleScene.scene->unk_90.z);
            func_8210C104(&sBattleScene.scene->rotationX, 0xE38, sBattleScene.scene->orbitDistance);
            func_8210C1A8(&sBattleScene.scene->distance, 350.0f, 0.2f);
            func_8210C1A8(&arg0->perspective.verticalFieldOfView, 80.0f, 0.02f);
        } else {
            sBattleScene.scene->unk_90.z = func_8000F23C(sBattleScene.scene->unk_90.z, 0.2f, 0.1f, 0.1f);
            func_8210C1A8(&sBattleScene.scene->orbitDistance, 120.0f, sBattleScene.scene->unk_90.z);
            func_8210C104(&sBattleScene.scene->rotationX, 0xE38, sBattleScene.scene->orbitDistance);
            func_8210C1A8(&sBattleScene.scene->distance, 250.0f, 0.2f);
            func_8210C1A8(&arg0->perspective.verticalFieldOfView, 80.0f, 0.02f);
        }
        func_8000EEBC((s8*)arg0 + 0xB4, (s8*)arg0 + 0xA8, sBattleScene.scene->distance, sBattleScene.scene->rotationX, sBattleScene.scene->rotationY);
        if (sBattleScene.scene->rotationX == 0xE38) {
            func_82125594(arg0, 2);
        }
    }
}

/**
 * Phase 1: the command phase, while the menus are open. In play, every turn passes through it.
 */
void BattleScene_PhaseCommand(CameraNode* arg0) {
    switch (sBattleScene.scene->phaseStep) {
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

/**
 * Starts the Pokémon's info box blinking (infoBoxBlinkTimer = 0x800).
 */
void func_821272C0(ActivePokemon* arg0) {
    arg0->state.infoBoxBlinkTimer = 0x800;
}

void ModelAnim_SetFrame(DisplayObject* display_object, s16 animation_timer);
/**
 * Rounds the model's animation frame to the next multiple of its frame count, counted back
 * from arg1. Skipped when model flag 2 or 0x4000 is set.
 */
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
s16 BattleScene_GetParticipantFacingAngle(ActivePokemon* arg0);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);
/**
 * Move intro camera variant 0: once the user's model is ready, sets camera preset 3, frames
 * the user's default anchor from the front at distance 150 and a size-scaled eye distance,
 * then steps the shot until it hands over.
 */
void func_82127354(CameraNode* arg0) {
    s32 i;
    f32 sp58;
    f32 step;
    BattleScene* scene = sBattleScene.scene;

    switch (scene->phaseSubstep) {
        case 0:
            if (func_82124A50(sActingPokemon) == 0) {
                func_82124EB4();
                func_82108C0C(sActingPokemon);
                func_82108C0C(sOtherPokemon);
                func_8213B31C(2);
                sBattleScene.scene->unk_1B = 0;
                func_821272C0((s8*)sActingPokemon);
                func_821255EC((s8*)arg0);
                BattleAnim_GetOwnerDefaultAnchorPosition(sActingPokemon, &sBattleScene.scene->anchorPosition);
                func_82134FD0(sActingPokemon);
                step = func_82121750(sActingPokemon, 3.5f, 300.0f);
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0, 0, sBattleScene.scene->orbitDistance = 150.0f, 0.0); // FAKE: store inside the call
                sBattleScene.scene->anchorPosition.x = arg0->view.targetPosition.x;
                sBattleScene.scene->anchorPosition.z = arg0->view.targetPosition.z;
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->anchorPosition, 0, (sActingPokemon)->displayObject.rotation.y, sBattleScene.scene->distance = step, 0.0); // FAKE: store inside the call
                func_82102010(sActingPokemon);
                func_82125580();
                func_821224F4();
                BattleMessage_ShowForSide(D_8219A520 + 0x188, sBattleScene.scene->actingSide);
                i = 0;
                step = 0.3f;
                sp58 = sBattleScene.scene->orbitDistance;
                for (;;) {
                    sBattleScene.scene->unk_84.z = func_8000F23C(sBattleScene.scene->unk_90.z, 0.7f, step, step);
                    func_8210C1A8(&sp58, 0.0f, sBattleScene.scene->unk_84.z);
                    if (sp58 <= 0.05f) {
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)sActingPokemon, i += 5); // FAKE: i += 5
                func_821224F4();
            }
            break;
        case 1:
            scene->cameraPresetId = 4;
            BattleAnim_GetOwnerDefaultAnchorPosition(sActingPokemon, &sBattleScene.scene->anchorPosition);
            if (func_82101FD4(sActingPokemon) != 0) {
                func_82121750(sActingPokemon, 3.5f, 300.0f);
                step = 0.3f;
                sBattleScene.scene->unk_84.z = func_8000F23C(sBattleScene.scene->unk_90.z, 0.7f, step, step);
                func_8210C1A8(&sBattleScene.scene->orbitDistance, 0.0f, sBattleScene.scene->unk_84.z);
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0, 0, sBattleScene.scene->orbitDistance, 0.0);
                sBattleScene.scene->anchorPosition.x = arg0->view.targetPosition.x;
                sBattleScene.scene->anchorPosition.z = arg0->view.targetPosition.z;
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->anchorPosition, 0, (sActingPokemon)->displayObject.rotation.y, sBattleScene.scene->distance, 0.0);
                if (sBattleScene.scene->orbitDistance <= 0.05f) {
                    BattleMessage_ShowForSide(D_8219A520 + 0x388, sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep++;
                    func_82125570();
                }
            }
            break;
    }
}

/**
 * Move intro camera variant 1: frames the user from its facing angle at distance 150 with
 * the eye 600 away (at least 25 high), then steps the shot until it hands over.
 */
void func_82127724(CameraNode* arg0) {
    s32 i;
    f32 dist;
    f32 step;
    s16 rate;

    BattleAnim_GetOwnerDefaultAnchorPosition(sActingPokemon, &sBattleScene.scene->anchorPosition);
    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            if (func_82124A50(sActingPokemon) == 0) {
                func_8213B31C(2);
                sBattleScene.scene->unk_1B = 0;
                func_821272C0((s8*)sActingPokemon);
                func_821255EC((s8*)arg0);
                func_82124EB4();
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0, (sActingPokemon)->facingDirection << 0xE, sBattleScene.scene->orbitDistance = 150.0f, 0.0); // FAKE: store inside the call
                BattleScene_SetCameraEyeAndStoreAnglesFromAt(arg0, 0, (sActingPokemon)->facingDirection * 0x16C, 600.0f, 0.0f);
                if (arg0->view.eyePosition.y <= 25.0f) {
                    arg0->view.eyePosition.y = 25.0f;
                }
                func_82134FD0(sActingPokemon);
                func_82102010(sActingPokemon);
                func_82125580();
                func_821224F4();
                BattleMessage_ShowForSide(D_8219A520 + 0x188, sBattleScene.scene->actingSide);
                i = 0;
                sBattleScene.scene->unk_84.x = 50.0f;
                step = 0.3f;
                for (;;) {
                    dist = func_82121750(sActingPokemon, 3.5f, 300.0f);
                    func_8210C1A8(&sBattleScene.scene->unk_84.x, 8.0f, step);
                    rate = (sBattleScene.scene->rotationY - (sActingPokemon)->facingDirection * 0x38E0) / (s16)sBattleScene.scene->unk_84.x;
                    if (rate < 0) {
                        rate *= -1;
                    }
                    if (rate < 30) {
                        rate = 30;
                    }
                    if (BattleAnim_StepToS16(&sBattleScene.scene->rotationY, (sActingPokemon)->facingDirection * 0x38E0, rate) != 0) {
                        func_8210C1A8(&sBattleScene.scene->unk_84.z, step, 0.02f);
                        func_8210C1A8(&sBattleScene.scene->orbitDistance, 0.0f, sBattleScene.scene->unk_84.z);
                    } else {
                        func_8210C1A8(&sBattleScene.scene->unk_84.y, 0.5f, 0.03f);
                        func_8210C1A8(&sBattleScene.scene->distance, dist, sBattleScene.scene->unk_84.y);
                    }
                    BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0, (sActingPokemon)->facingDirection << 0xE, sBattleScene.scene->orbitDistance, 0.0);
                    BattleScene_SetCameraEyeFromAt(arg0, 0, sBattleScene.scene->rotationY, sBattleScene.scene->distance, 0.0f);
                    if (sBattleScene.scene->distance < dist + 5.0f) {
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)sActingPokemon, i += 5); // FAKE: i += 5
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0, (sActingPokemon)->facingDirection << 0xE, sBattleScene.scene->orbitDistance = 150.0f, 0.0); // FAKE: store inside the call
                BattleScene_SetCameraEyeAndStoreAnglesFromAt(arg0, 0, (sActingPokemon)->facingDirection * 0x16C, 600.0f, 0.0f);
                if (arg0->view.eyePosition.y <= 25.0f) {
                    arg0->view.eyePosition.y = 25.0f;
                }
                func_821224F4();
                sBattleScene.scene->unk_84.x = 50.0f;
            }
            break;
        case 1:
            if (func_82101FD4(sActingPokemon) != 0) {
                step = 0.3f;
                dist = func_82121750(sActingPokemon, 3.5f, 300.0f);
                func_8210C1A8(&sBattleScene.scene->unk_84.x, 8.0f, step);
                rate = (sBattleScene.scene->rotationY - (sActingPokemon)->facingDirection * 0x38E0) / (s16)sBattleScene.scene->unk_84.x;
                if (rate < 0) {
                    rate *= -1;
                }
                if (rate < 30) {
                    rate = 30;
                }
                if (BattleAnim_StepToS16(&sBattleScene.scene->rotationY, (sActingPokemon)->facingDirection * 0x38E0, rate) != 0) {
                    func_8210C1A8(&sBattleScene.scene->unk_84.z, step, 0.02f);
                    func_8210C1A8(&sBattleScene.scene->orbitDistance, 0.0f, sBattleScene.scene->unk_84.z);
                } else {
                    func_8210C1A8(&sBattleScene.scene->unk_84.y, 0.5f, 0.03f);
                    func_8210C1A8(&sBattleScene.scene->distance, dist, sBattleScene.scene->unk_84.y);
                }
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0, (sActingPokemon)->facingDirection << 0xE, sBattleScene.scene->orbitDistance, 0.0);
                BattleScene_SetCameraEyeFromAt(arg0, 0, sBattleScene.scene->rotationY, sBattleScene.scene->distance, 0.0f);
                if (sBattleScene.scene->distance < dist + 5.0f) {
                    BattleMessage_ShowForSide(D_8219A520 + 0x388, sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep++;
                    func_82125570();
                }
                if (arg0->view.eyePosition.y <= 25.0f) {
                    arg0->view.eyePosition.y = 25.0f;
                }
            }
            break;
    }
}

extern f32 D_FLT_8218935C[][4];
f32 func_82121750(ActivePokemon*, f32, f32);
s16 BattleScene_GetParticipantFacingAngle(ActivePokemon* arg0);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);
/**
 * Move intro camera variant 2: frames the user from the front, aimed 2.5 times its height
 * above the anchor, shows the move message and steps the shot.
 */
void func_82127DFC(CameraNode* arg0) {
    s32 i;
    f32 sp68;
    f32 step;

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            if (func_82124A50(sActingPokemon) == 0) {
                func_82124EB4();
                func_82108C0C(sActingPokemon);
                func_82108C0C(sOtherPokemon);
                func_8213B31C(2);
                sBattleScene.scene->unk_1B = 0;
                func_821272C0((s8*)sActingPokemon);
                func_821255EC((s8*)arg0);
                BattleAnim_GetOwnerDefaultAnchorPosition(sActingPokemon, &sBattleScene.scene->anchorPosition);
                step = func_82121750(sActingPokemon, 3.5f, 250.0f);
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(sActingPokemon), 0.0f, BattleScene_GetParticipantHeight(sActingPokemon) * 2.5f);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(sActingPokemon), step, 0.0f);
                BattleMessage_ShowForSide(D_8219A520 + 0x188, sBattleScene.scene->actingSide);
                func_82134FD0(sActingPokemon);
                func_82102010(sActingPokemon);
                func_82125580();
                func_821224F4();
                i = 0;
                step = 0.1f;
                sp68 = arg0->view.targetPosition.y;
                while (TRUE) {
                    sBattleScene.scene->unk_84.z = func_8000F23C(sBattleScene.scene->unk_84.z, 0.2f, step, step);
                    func_8210C1A8(&sp68, sBattleScene.scene->anchorPosition.y + D_FLT_8218935C[(sActingPokemon)->displayObject.objectType - 1][3], sBattleScene.scene->unk_84.z);
                    if (sp68 <= (sBattleScene.scene->anchorPosition.y + step) + D_FLT_8218935C[(sActingPokemon)->displayObject.objectType - 1][3]) {
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)sActingPokemon, i += 5); // FAKE: i += 5
                func_821224F4();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            if (func_82101FD4(sActingPokemon) != 0) {
                step = 0.1f;
                sBattleScene.scene->unk_84.z = func_8000F23C(sBattleScene.scene->unk_84.z, 0.2f, step, step);
                func_8210C1A8(&arg0->view.targetPosition.y, sBattleScene.scene->anchorPosition.y + D_FLT_8218935C[(sActingPokemon)->displayObject.objectType - 1][3], sBattleScene.scene->unk_84.z);
                if (arg0->view.targetPosition.y <= (sBattleScene.scene->anchorPosition.y + step) + D_FLT_8218935C[(sActingPokemon)->displayObject.objectType - 1][3]) {
                    BattleMessage_ShowForSide(D_8219A520 + 0x388, sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep++;
                    func_82125570();
                }
            }
            break;
    }
}

extern f32 D_FLT_8218935C[][4];
f32 func_82121750(ActivePokemon*, f32, f32);
s16 BattleScene_GetParticipantFacingAngle(ActivePokemon* arg0);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);
/**
 * Move intro camera variant 3: like variant 2 but aimed 1.5 times the user's height below
 * the anchor.
 */
void func_8212817C(CameraNode* arg0) {
    s32 i;
    f32 sp68;
    f32 step;

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            if (func_82124A50(sActingPokemon) == 0) {
                func_82124EB4();
                func_82108C0C(sActingPokemon);
                func_82108C0C(sOtherPokemon);
                func_8213B31C(2);
                sBattleScene.scene->unk_1B = 0;
                func_821272C0((s8*)sActingPokemon);
                func_821255EC((s8*)arg0);
                BattleAnim_GetOwnerDefaultAnchorPosition(sActingPokemon, &sBattleScene.scene->anchorPosition);
                step = func_82121750(sActingPokemon, 3.5f, 250.0f);
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(sActingPokemon), 0.0f, -BattleScene_GetParticipantHeight(sActingPokemon) * 1.5f);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(sActingPokemon), step, 0.0f);
                BattleMessage_ShowForSide(D_8219A520 + 0x188, sBattleScene.scene->actingSide);
                func_82102010(sActingPokemon);
                func_82125580();
                func_821224F4();
                func_82134FD0(sActingPokemon);
                i = 0;
                step = 0.1f;
                sp68 = arg0->view.targetPosition.y;
                while (TRUE) {
                    sBattleScene.scene->unk_84.z = func_8000F23C(sBattleScene.scene->unk_84.z, 0.2f, step, step);
                    func_8210C1A8(&sp68, sBattleScene.scene->anchorPosition.y + D_FLT_8218935C[(sActingPokemon)->displayObject.objectType - 1][3], sBattleScene.scene->unk_84.z);
                    if ((sBattleScene.scene->anchorPosition.y - step) + D_FLT_8218935C[(sActingPokemon)->displayObject.objectType - 1][3] <= sp68) {
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)sActingPokemon, i += 5); // FAKE: i += 5
                func_821224F4();
            }
            break;
        case 1:
            sBattleScene.scene->cameraPresetId = 4;
            if ((func_82124A50(sActingPokemon) == 0) && (func_82101FD4(sActingPokemon) != 0)) {
                step = 0.1f;
                sBattleScene.scene->unk_84.z = func_8000F23C(sBattleScene.scene->unk_84.z, 0.2f, step, step);
                func_8210C1A8(&arg0->view.targetPosition.y, sBattleScene.scene->anchorPosition.y + D_FLT_8218935C[(sActingPokemon)->displayObject.objectType - 1][3], sBattleScene.scene->unk_84.z);
                if (D_FLT_8218935C[(sActingPokemon)->displayObject.objectType - 1][3] + (sBattleScene.scene->anchorPosition.y - step) <= arg0->view.targetPosition.y) {
                    BattleMessage_ShowForSide(D_8219A520 + 0x388, sBattleScene.scene->actingSide);
                    sBattleScene.scene->phaseStep++;
                    func_82125570();
                }
            }
            break;
    }
}

f32 func_82121750(ActivePokemon*, f32, f32);
s16 BattleScene_GetParticipantFacingAngle(ActivePokemon* arg0);
void func_82134FD0(ActivePokemon*);
void func_82102010(ActivePokemon*);
s32 func_82101FD4(ActivePokemon*);
/**
 * Move intro camera variant 4: frames the user from the front, aimed two heights below the
 * anchor with the eye 150 lower, shows the move message and steps the shot.
 */
void func_82128510(CameraNode* arg0) {
    f32 sp44;
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp3A;
    BattleScene* scene = D_8219A5A0;

    switch (scene->phaseSubstep) {
        case 0:
            if (func_82124A50(sActingPokemon) == 0) {
                func_82124EB4();
                func_82108C0C(sActingPokemon);
                func_82108C0C(sOtherPokemon);
                func_8213B31C(2);
                D_8219A5A0->unk_1B = 0;
                func_821272C0((s8*)sActingPokemon);
                func_821255EC((s8*)arg0);
                BattleAnim_GetOwnerDefaultAnchorPosition(sActingPokemon, &sBattleScene.scene->anchorPosition);
                sp44 = func_82121750(sActingPokemon, 3.5f, 300.0f);
                sp3A = BattleScene_GetParticipantFacingAngle(sActingPokemon);
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0, sp3A, 0.0f, 2.0f * -BattleScene_GetParticipantHeight(sActingPokemon));
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->anchorPosition, 0, BattleScene_GetParticipantFacingAngle(sActingPokemon), sp44, -150.0f);
                BattleMessage_ShowForSide(D_8219A520 + 0x188, sBattleScene.scene->actingSide);
                func_82134FD0(sActingPokemon);
                func_82102010(sActingPokemon);
                func_82125580();
                func_821224F4();
            }
            break;
        case 1:
            scene->cameraPresetId = 4;
            if (func_82101FD4(sActingPokemon) != 0) {
                func_8210C1A8(&D_8219A5A0->unk_84.z, 0.4f, 0.01f);
                func_8210C1A8(&arg0->view.targetPosition.y, D_8219A5A0->anchorPosition.y, D_8219A5A0->unk_84.z);
                if ((D_8219A5A0->anchorPosition.y - 1.0f) <= arg0->view.targetPosition.y) {
                    BattleMessage_ShowForSide(D_8219A520 + 0x388, D_8219A5A0->actingSide);
                    D_8219A5A0->phaseStep++;
                    func_82125570();
                }
            }
            break;
    }
}

/**
 * Move intro camera variant 5: picks one of variants 0-3 at random on substep 0 and runs it.
 */
void func_82128780(CameraNode* arg0) {
    if (sBattleScene.scene->phaseSubstep == 0) {
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
 * Camera step for sActingPokemon, switched on scene field 0x3C. Case 0 dry-runs
 * the camera swing to count its frames (passed on to func_821272CC) and then
 * resets the camera; case 1 runs the swing for real and advances scene field
 * 0x20 once it settles.
 */
void func_82128848(CameraNode* arg0) {
    s32 pad; // FAKE
    s32 i;

    switch (sBattleScene.scene->phaseSubstep) {
        case 0:
            if (func_82124A50(sActingPokemon) == 0) {
                func_82124EB4();
                func_82108C0C(sActingPokemon);
                func_82108C0C(sOtherPokemon);
                func_8213B31C(2);
                sBattleScene.scene->unk_1B = 0;
                func_821272C0((s8*)sActingPokemon);
                func_821255EC((s8*)arg0);
                func_82134FD0(sActingPokemon);
                sBattleScene.scene->verticalFieldOfView = arg0->perspective.verticalFieldOfView;
                arg0->perspective.verticalFieldOfView = 100.0f;
                BattleAnim_GetOwnerDefaultAnchorPosition(sActingPokemon, &sBattleScene.scene->anchorPosition);
                sBattleScene.scene->orbitDistance = func_82121750(sActingPokemon, 4.0f, 300.0f);
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0,
                                                  BattleScene_GetParticipantFacingAngle(sActingPokemon), 0.0f, 0.0);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->anchorPosition,
                                                     sBattleScene.scene->unk_6E = -0x1554,
                                                     BattleScene_GetParticipantFacingAngle(sActingPokemon),
                                                     sBattleScene.scene->orbitDistance, 0.0);
                BattleMessage_ShowForSide(D_8219A520 + 0x188, sBattleScene.scene->actingSide);
                func_82102010(sActingPokemon);
                func_82125580();
                func_821224F4();

                // Dry-run the camera move to count how many frames it takes.
                i = 0;
                for (;;) {
                    BattleAnim_StepToS16(&sBattleScene.scene->unk_6E, 0x149E, 0x2D);
                    BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->anchorPosition,
                                                         sBattleScene.scene->unk_6E,
                                                         BattleScene_GetParticipantFacingAngle(sActingPokemon),
                                                         sBattleScene.scene->orbitDistance, 0.0);
                    func_8210C1A8(&arg0->perspective.verticalFieldOfView, sBattleScene.scene->verticalFieldOfView, 0.08f);
                    if (arg0->perspective.verticalFieldOfView < sBattleScene.scene->verticalFieldOfView + 1.0f) {
                        arg0->perspective.verticalFieldOfView = sBattleScene.scene->verticalFieldOfView;
                        break;
                    }
                    i++;
                }
                func_821272CC((DisplayObject*)sActingPokemon, i += 5); // FAKE: i is dead afterwards

                // Then reset the camera to its starting state.
                sBattleScene.scene->verticalFieldOfView = arg0->perspective.verticalFieldOfView;
                arg0->perspective.verticalFieldOfView = 100.0f;
                BattleAnim_GetOwnerDefaultAnchorPosition(sActingPokemon, &sBattleScene.scene->anchorPosition);
                sBattleScene.scene->orbitDistance = func_82121750(sActingPokemon, 4.0f, 300.0f);
                BattleScene_SetCameraAtFromAnchor(sActingPokemon, arg0, sBattleScene.scene->anchorPosition, 0,
                                                  BattleScene_GetParticipantFacingAngle(sActingPokemon), 0.0f, 0.0);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->anchorPosition,
                                                     sBattleScene.scene->unk_6E = -0x1554,
                                                     BattleScene_GetParticipantFacingAngle(sActingPokemon),
                                                     sBattleScene.scene->orbitDistance, 0.0);
                func_821224F4();
            }
            break;

        case 1:
            if (func_82101FD4(sActingPokemon) != 0) {
                sBattleScene.scene->cameraPresetId = 4;
                BattleAnim_StepToS16(&sBattleScene.scene->unk_6E, 0x149E, 0x2D);
                BattleScene_SetCameraEyeFromPosition(arg0, sBattleScene.scene->anchorPosition,
                                                     sBattleScene.scene->unk_6E,
                                                     BattleScene_GetParticipantFacingAngle(sActingPokemon),
                                                     sBattleScene.scene->orbitDistance, 0.0);
                func_8210C1A8(&arg0->perspective.verticalFieldOfView, sBattleScene.scene->verticalFieldOfView, 0.08f);
                if (arg0->perspective.verticalFieldOfView < sBattleScene.scene->verticalFieldOfView + 1.0f) {
                    BattleMessage_ShowForSide(D_8219A520 + 0x388, sBattleScene.scene->actingSide);
                    arg0->perspective.verticalFieldOfView = sBattleScene.scene->verticalFieldOfView;
                    sBattleScene.scene->phaseStep++;
                    func_82125570();
                }
            }
            break;
    }

    if (!arg0) {} // FAKE
}
