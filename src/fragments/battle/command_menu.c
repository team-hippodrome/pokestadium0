/* Stadium Zero fragment012_17ED00. */

#include "global.h"
#include "battle.h"
#include "m2c_macros.h"

extern f32 D_82199EB0;
extern s32 D_82199EB8;

extern f32 D_FLT_82199EB0;

/**
 * Counts the command phase's frame timer (D_FLT_82199EB0) up to 150; returns 1
 * once it is there. Runs every frame while the sides pick their actions. The
 * COM's choice is timed off it: the AI runs at frame 1 (60 for a replacement
 * after a faint), the COM box shows its pick from frame 30, and the pick is
 * final at frame 90 (or 10 once the player has picked). Nothing times out.
 */
s32 BattleMenu_TickCommandTimer(void) {
    if (D_FLT_82199EB0 >= 150.0f) {
        return 1;
    }
    D_FLT_82199EB0 += 1.0f;
    return 0;
}

extern f32 D_FLT_82199EB0;

/**
 * Resets the command phase's frame timer, once both actions are committed.
 */
void BattleMenu_ResetCommandTimer(void) {
    D_FLT_82199EB0 = 0.0f;
}

/**
 * While the Pokemon's command state (+0x79C) is 3, adds 0x38E to its action timer and
 * returns 1; otherwise returns 0.
 */
s32 func_8210C708(s8 *arg0) {
    s8 *temp_v1;

    temp_v1 = arg0 + 0x78C;
    if (M2C_FIELD(arg0, s32 *, 0x79C) == 3) {
        M2C_FIELD(temp_v1, u16 *, 0x1E) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x1E) + 0x38E);
        return 1;
    }
    return 0;
}

/**
 * Takes the trainer index at 0x7B8 as the commanding trainer (0x7B9) and uses that
 * trainer's controller port for this Pokémon.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleScene_SelectActiveController(ActivePokemon* arg0) {
    ActivePokemonState* ptr = &arg0->state;

    arg0->state.menuTeamMemberIndex = arg0->state.prevMenuTeamMemberIndex;
    ptr->controller = &gControllers[arg0->sessionTeams->teamMember[arg0->state.menuTeamMemberIndex]->controllerPort];
}

s32 func_82107A5C(void);
void func_8210C738(ActivePokemon* arg0, ActivePokemonState* arg1, Controller* arg2);
M2C_UNK func_82134D80();
extern s8 D_82199DE0;

/**
 * While the command menu option is 3, waits for L on the Pokemon's controller (unless the
 * other side's state byte is 16): then runs func_8210C738 for command 2, resets the option
 * and returns 0. Until then adds 0x38E to the action timer and returns 1.
 */
s32 func_8210C778(ActivePokemon* arg0) {
    ActivePokemonState* state = &arg0->state;
    ActivePokemonState* other = &((ActivePokemon**)&D_82199DE0)[func_82107A5C() == 0]->state;
    Controller* controller = state->controller;
    s32 pad; // FAKE: stack padding

    if (state->selectedCommandOption == 3) {
        if ((controller->buttonPressed & 0x20) && (other->faintState != 0x10)) {
            if (state->selectedCommand == 2) {
                func_8210C738(arg0, other, controller);
            }
            state->selectedCommandOption = 0;
            func_82134D80();
            return 0;
        }
        state->actionDelayTimer += 0x38E;
        return 1;
    }
    return 0;
}

/**
 * Stores the chosen move slot as the selected move and, unless selection is
 * locked, sets the move to use; handles slot 4 (no move chosen) separately.
 */
void BattleMenu_CommitMoveSelection(ActivePokemon* arg0) {
    BattleMonRuntime* temp_v1 = &arg0->state.runtime;
    ActivePokemonState* temp_v0 = &arg0->state;

    if (arg0->state.moveIndex != 4) {
        temp_v0->selectedMoveIndex = temp_v0->moveIndex;
        if (temp_v0->moveSelectionLocked == 0) {
            temp_v1->usedMove = temp_v1->moves[temp_v0->selectedMoveIndex];
        }
    } else {
        if (temp_v1->immobilizedReason & 0x20) {
            temp_v0->selectedMoveIndex = temp_v0->moveIndex;
        } else {
            temp_v0->moveIndex = 0;
            temp_v0->selectedMoveIndex = 0;
            temp_v1->usedMove = 0xA5;
        }
    }
}

void func_8211F274();
s32 ActivePokemon_GetNickname(s32);
M2C_UNK ActivePokemon_ShowCaption();
extern s32 D_8218C6F0;
/**
 * Fight menu check for a Pokemon with no usable PP: shows 「…は だすことの
 * できる わざが ない」 ("has no moves it can use"), then A confirms Struggle
 * (move slot 4) and L goes back. Returns 1 while this applies.
 */
s32 BattleMenu_HandleNoUsableMoves(arg0) ActivePokemon *arg0;
{
  s32 i;
  s32 temp_a1;
  s32 var_v1;
  ActivePokemonState *temp_v0;
  BattleMonRuntime *temp_a0;
  Controller *cont;
  temp_a0 = &arg0->state.runtime;
  cont = arg0->state.controller;
  var_v1 = 0;
  if (temp_a0->disabledMoveState != 0)
  {
    temp_a1 = temp_a0->disabledMoveState >> 4;
    for (i = 0; i < 4; i++)
    {
      if (temp_a1 != i)
      {
        var_v1 |= temp_a0->pp[i] & 0x3F;
      }
    }

  }
  else
  {
 do { for (i = 0; i < 4; i++) { var_v1 |= temp_a0->pp[i] & 0x3F; } } while (0);
  }
  if (var_v1 == 0)
  {
    temp_v0 = &arg0->state;
    if ((*((s32 *) (((s8 *) arg0) + 0xA04))) == 0)
    {
      if (temp_v0->selectedCommandOption == 0)
      {
        temp_v0->selectedCommandOption = 1;
      }
      func_8211F274(arg0);
      ActivePokemon_ShowCaption(arg0, D_8218C6F0, ActivePokemon_GetNickname((s32) arg0));
    }
    else
      if (cont->buttonPressed & 0x20)
    {
      func_8211F274(arg0);
      arg0->state.selectedCommandOption = 0;
      BattleAnim_PlaySoundEffect3();
    }
    else
      if (cont->buttonPressed & 0x8000)
    {
      func_8211F274(arg0);
      temp_v0->actionDelayTimer = 0;
      temp_v0->selectedCommandOption = 3;
      temp_v0->moveIndex = 4;
    }
    return 1;
  }
  return 0;
}

void func_8211F274();
M2C_UNK ActivePokemon_ShowCaption();
extern s32 D_8218C6F4;
extern s32 D_8218C6F8;

typedef struct BattleMoveCheck8210CA24 {
    /* 0x000 */ char unk000[0x7A0];
    /* 0x7A0 */ s32 slot;
    /* 0x7A4 */ char unk7A4[0x7F8 - 0x7A4];
    /* 0x7F8 */ u8 moveFlags[1];
} BattleMoveCheck8210CA24;

/**
 * Checks the chosen move slot: shows a message and returns 1 if it has no PP or
 * is disabled, otherwise confirms it.
 * Seen in play (2026-11-12): with Poison Sting's PP set to 0, choosing it (C-Up) made this return
 * 1 and the game showed わざの のこりポイントが ない！ (No PP left for this move!) instead of starting the
 * turn.
 */
s32 BattleMenu_TryConfirmMove(s8* arg0) {
    u8 flags;
    s8* state;

    if (!(((BattleMoveCheck8210CA24*)arg0)->moveFlags[((BattleMoveCheck8210CA24*)arg0)->slot] & 0x3F)) {
        func_8211F274(arg0);
        ActivePokemon_ShowCaption(arg0, D_8218C6F4);
        return 1;
    }
    flags = M2C_FIELD(arg0, u8*, 0x818);
    state = arg0 + 0x78C;
    if ((flags & 0xF) && ((flags >> 4) == M2C_FIELD(state, s32*, 0x14))) {
        func_8211F274(arg0);
        ActivePokemon_ShowCaption(arg0, D_8218C6F8);
        return 1;
    }
    M2C_FIELD(state, s16*, 0x1E) = 0;
    M2C_FIELD(state, s32*, 0x10) = 3;
    M2C_FIELD(state, s8*, 0x1C) = 0;
    return 0;
}

void func_82134D60(void);
s32 BattleMenu_TryConfirmMove(s8*);
/**
 * Maps the C buttons to the four move slots and tries to confirm the pressed one.
 */
void BattleMenu_HandleMoveButtons(s8* arg0) {
    s32 buttons;
    s8* ctrl;

    ctrl = M2C_FIELD(arg0, s8**, 0x858);
    buttons = M2C_FIELD(ctrl, u16*, 8);

    if ((buttons & 8) && (M2C_FIELD(arg0, u8*, 0x7E5) != 0) && (M2C_FIELD(arg0, u8*, 0x7E5) < 0xA6)) {
        func_82134D60();
        M2C_FIELD(arg0, s32*, 0x7A0) = 0;
        BattleMenu_TryConfirmMove(arg0);
    } else if ((buttons & 1) && (M2C_FIELD(arg0, u8*, 0x7E6) != 0) && (M2C_FIELD(arg0, u8*, 0x7E6) < 0xA6)) {
        func_82134D60();
        M2C_FIELD(arg0, s32*, 0x7A0) = 1;
        BattleMenu_TryConfirmMove(arg0);
    } else if ((buttons & 4) && (M2C_FIELD(arg0, u8*, 0x7E7) != 0) && (M2C_FIELD(arg0, u8*, 0x7E7) < 0xA6)) {
        func_82134D60();
        M2C_FIELD(arg0, s32*, 0x7A0) = 2;
        BattleMenu_TryConfirmMove(arg0);
    } else if ((buttons & 2) && (M2C_FIELD(arg0, u8*, 0x7E8) != 0) && (M2C_FIELD(arg0, u8*, 0x7E8) < 0xA6)) {
        func_82134D60();
        M2C_FIELD(arg0, s32*, 0x7A0) = 3;
        BattleMenu_TryConfirmMove(arg0);
    }
}

s32 BattleMenu_HandleNoUsableMoves();                                /* extern */
void func_82134D40(s8 *);
M2C_UNK func_82134D80(s8 *);                        /* extern */
void func_8211F274();

/**
 * Fight menu, every frame: L goes back to the command menu, holding R shows the
 * move list (sub[0x1C]), and the C buttons go to BattleMenu_HandleMoveButtons.
 * Callers reach the same address as BattleScene_HandlePlayerMoveSelection
 * (Stadium 1's name); merging the two names changes the prototype in
 * battle.h, so both stay for now.
 *
 * Does nothing unless the word at arg0 + 0x790 is 1 and BattleMenu_HandleNoUsableMoves()
 * returns 0. Then, with `rec` = the pointer at arg0 + 0x858 and `sub` =
 * arg0 + 0x78C:
 *  - if the word at arg0 + 0xA04 is non-zero: calls func_8211F274(arg0) when
 *    any of the bits 0xE03F is set in the halfword at rec + 8;
 *  - otherwise clears sub[0x20]; if sub[0x10] is 0 it sets it to 1 and
 *    returns; else if bit 0x20 of rec + 8 is set and bit 0x10 of the halfword
 *    at rec + 6 is clear, it clears sub[0x10], calls func_82134D80(arg0) and
 *    returns; else it clears the byte sub[0x1C], and, when bit 0x10 of rec + 6
 *    is set, calls func_82134D40(arg0) if bit 0x10 of rec + 8 is also set and
 *    sets the byte sub[0x1C] to 1; finally it calls BattleMenu_HandleMoveButtons(arg0).
 *
 * What the fields and the callees mean is not established (rec[6] and rec[8]
 * look like button/state bit masks but that is a guess from the masks only).
 * Matching notes: func_82134D40 must be declared `void` (the result is unused;
 * an `M2C_UNK` return changes register allocation), and the unused `pad` local,
 * declared after `temp_v1`, moves the spill slot of `temp_v0` to sp+0x18.
 */
void BattleMenu_UpdateMoveMenu(s8 *arg0) {
    void *temp_v0;
    void *temp_v1;
    UNUSED s32 pad; // FAKE: stack padding

    temp_v1 = M2C_FIELD(arg0, void **, 0x858);
    if ((M2C_FIELD(arg0, s32 *, 0x790) == 1) && (BattleMenu_HandleNoUsableMoves() == 0)) {
        temp_v0 = arg0 + 0x78C;
        if (M2C_FIELD(arg0, s32 *, 0xA04) != 0) {
            if (M2C_FIELD(temp_v1, u16 *, 8) & 0xE03F) {
                func_8211F274(arg0);
            }
        } else {
            M2C_FIELD(temp_v0, s32 *, 0x20) = 0;
            if (M2C_FIELD(temp_v0, s32 *, 0x10) == 0) {
                M2C_FIELD(temp_v0, s32 *, 0x10) = 1;
                return;
            }
            if ((M2C_FIELD(temp_v1, u16 *, 8) & 0x20) && !(M2C_FIELD(temp_v1, u16 *, 6) & 0x10)) {
                M2C_FIELD(temp_v0, s32 *, 0x10) = 0;
                func_82134D80(arg0);
                return;
            }
            M2C_FIELD(temp_v0, s8 *, 0x1C) = 0;
            if (M2C_FIELD(temp_v1, u16 *, 6) & 0x10) {
                if (M2C_FIELD(temp_v1, u16 *, 8) & 0x10) {
                    func_82134D40(arg0);
                }
                M2C_FIELD(temp_v0, s8 *, 0x1C) = 1;
            }
            BattleMenu_HandleMoveButtons(arg0);
        }
    }
}

s32 func_8210CCDC(s8 *arg0, M2C_UNK arg1)
{
  *((s8 *) (((s8 *) arg0) + 0x7B6)) = 1;
  if (1)
  {
    *((s8 *) (((s8 *) arg0) + 0x7B6)) = 1;
    BattleMenu_UpdateMoveMenu(arg0);
    *((s8 *) (((s8 *) arg0) + 0x7B6)) = 1;
  }
  return 0;
}

/**
 * Locks in a forced repeat of the Pokémon's current move (for example a multi-turn move)
 * after the usual delay.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_ConfirmForcedMoveRepeat(ActivePokemon* arg0) {
    ActivePokemonState* ptr = &arg0->state;

    BattleScene_ApplyForcedActionDelay(arg0);
    ptr->moveSelectionLocked = 1;
    ptr->selectedCommandOption = 3;
    ptr->selectedMoveIndex = ptr->moveIndex;
}

/**
 * Commits a chosen switch: the picked party slot (state.actionChosen) becomes
 * state.rosterIndex. The switch counterpart of BattleMenu_CommitMoveSelection.
 */
void BattleMenu_CommitSwitchSelection(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x794) = (s32) M2C_FIELD(arg0, s32 *, 0x7A4);
    if (M2C_FIELD(arg0, u8 *, 0x7BA) != 0x10) {
        M2C_FIELD(arg0, u8 *, 0x7BA) = 0xFU;
    }
}

void func_8211F274();
M2C_UNK ActivePokemon_ShowCaption();
extern s32 D_8218C6FC;

/**
 * Returns 1 if the chosen party member has HP left; otherwise plays the error sound,
 * shows a caption and returns 0.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
s32 BattleScene_ValidateSelectedPartyMember(ActivePokemon* arg0) {
    if (arg0->sessionTeams->teamMember[arg0->state.menuTeamMemberIndex]->pokemonPicked[arg0->state.actionChosen].hp != 0) {
        return 1;
    }

    func_8211F274(arg0);
    ActivePokemon_ShowCaption(arg0, D_8218C6FC);
    return 0;
}

void ActivePokemon_SetController(ActivePokemon*, u8*);
/**
 * Tag team: when either teammate's controller presses B, that teammate's
 * controller takes over this Pokemon's menu.
 * Seen in play (2026-11-13) in a Free Battle switch (1P switched to its second Pokémon) it ran when
 * B opened the Pokémon menu.
 * @unverified Name and comment guessed from the code.
 */
void BattleMenu_TakeControlOnBPress(ActivePokemon* arg0, u8* arg1, u8* arg2, s32 arg3) {
    ActivePokemonState* state = &arg0->state;
    u16 mask;
    s32 m; // FAKE

    m = 0x4000;
    if (arg0->sessionTeams->teamMember[0]->numberOfPokemonBrought == 3) {
        mask = m;
    } else {
        mask = 0x4000;
    }
    if (arg3 == 1) {
        if (*(u16*)(arg1 + 8) & mask) {
            state->prevMenuTeamMemberIndex = state->menuTeamMemberIndex;
            state->menuTeamMemberIndex = 0;
            ActivePokemon_SetController(arg0, arg1);
        } else if (*(u16*)(arg2 + 8) & mask) {
            state->prevMenuTeamMemberIndex = state->menuTeamMemberIndex;
            state->menuTeamMemberIndex = 0;
            ActivePokemon_SetController(arg0, arg2);
        }
    } else {
        if (*(u16*)(arg1 + 8) & mask) {
            state->prevMenuTeamMemberIndex = state->menuTeamMemberIndex;
            state->menuTeamMemberIndex = 0;
            ActivePokemon_SetController(arg0, arg1);
        } else if (*(u16*)(arg2 + 8) & mask) {
            state->prevMenuTeamMemberIndex = state->menuTeamMemberIndex;
            state->menuTeamMemberIndex = 1;
            ActivePokemon_SetController(arg0, arg2);
        }
    }
}

void ActivePokemon_SetController(ActivePokemon*, u8*);
/**
 * Tag team: like BattleMenu_TakeControlOnBPress, but for the C buttons (the mask
 * depends on how many Pokemon were brought).
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name and comment guessed from the code.
 */
void BattleMenu_TakeControlOnCButtonPress(ActivePokemon* arg0, u8* arg1, u8* arg2, s32 arg3) {
    ActivePokemonState* state = &arg0->state;
    u16 mask;

    if (arg0->sessionTeams->teamMember[0]->numberOfPokemonBrought == 3) {
        mask = 0xD;
    } else {
        mask = 0xC00F;
    }
    if (arg3 == 1) {
        if (*(u16*)(arg1 + 8) & mask) {
            state->prevMenuTeamMemberIndex = state->menuTeamMemberIndex;
            state->menuTeamMemberIndex = 0;
            ActivePokemon_SetController(arg0, arg1);
        } else if (*(u16*)(arg2 + 8) & mask) {
            state->prevMenuTeamMemberIndex = state->menuTeamMemberIndex;
            state->menuTeamMemberIndex = 0;
            ActivePokemon_SetController(arg0, arg2);
        }
    } else {
        if (*(u16*)(arg1 + 8) & mask) {
            state->prevMenuTeamMemberIndex = state->menuTeamMemberIndex;
            state->menuTeamMemberIndex = 0;
            ActivePokemon_SetController(arg0, arg1);
        } else if (*(u16*)(arg2 + 8) & mask) {
            state->prevMenuTeamMemberIndex = state->menuTeamMemberIndex;
            state->menuTeamMemberIndex = 1;
            ActivePokemon_SetController(arg0, arg2);
        }
    }
}

s32 ActivePokemon_GetNickname(s32);                             /* extern */
void func_8211F274();                            /* extern */
M2C_UNK ActivePokemon_ShowCaption(s32, s32, s32);               /* extern */
extern s32 D_8218C700;

/**
 * Clears the caption state and shows caption D_8218C700 with the Pokemon's nickname.
 */
void func_8210CFE4(s32 arg0) {
    func_8211F274();
    ActivePokemon_ShowCaption(arg0, D_8218C700, ActivePokemon_GetNickname(arg0));
}

void func_82134D60(void);

/**
 * Pokemon (switch) menu buttons: sets state.actionChosen to the party slot of
 * the pressed button and confirms the switch. With six Pokemon: C-Up 0,
 * C-Left 1, B 2, C-Right 3, C-Down 4, A 5 (the on-screen list uses the same
 * layout); with three: C-Up 0, C-Right 1, C-Down 2. Pressing the active
 * Pokemon's own button shows a message instead.
 */
void BattleMenu_HandleSwitchButtons(ActivePokemon* arg0, s8* arg1) {
    u8* team = *(u8**)(arg0->state.menuTeamMemberIndex * 4 + M2C_FIELD(arg0, s8**, 0x85C) + 8);
    ActivePokemonState* state = &arg0->state;

    if (team[2] == 3) {
        if (M2C_FIELD(arg1, u16*, 8) & 8) {
            arg0->state.actionChosen = 0;
        } else if (M2C_FIELD(arg1, u16*, 8) & 1) {
            arg0->state.actionChosen = 1;
        } else if (M2C_FIELD(arg1, u16*, 8) & 4) {
            arg0->state.actionChosen = 2;
        } else {
            return;
        }
    } else {
        if (M2C_FIELD(arg1, u16*, 8) & 8) {
            arg0->state.actionChosen = 0;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 2) {
            arg0->state.actionChosen = 1;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 0x4000) {
            arg0->state.actionChosen = 2;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 1) {
            arg0->state.actionChosen = 3;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 4) {
            arg0->state.actionChosen = 4;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 0x8000) {
            arg0->state.actionChosen = 5;
        }
    }
    if (M2C_FIELD(arg1, u16*, 8) & 0xC00F) {
        if ((state->rosterIndex == state->actionChosen) && (state->teamMemberIndex == state->menuTeamMemberIndex)) {
            if (func_8210CD7C(arg0) != 0) {
                func_8210CFE4((s32)arg0);
            }
        } else if (state->actionChosen <= (u32)(team[2] - 1)) {
            if (func_8210CD7C(arg0) != 0) {
                func_82134D60();
                state->showingCommandOptions = 0;
                state->actionDelayTimer = 0;
                state->selectedCommandOption = 3;
            }
        }
    }
}

/**
 * Pokemon (switch) menu, every frame: L goes back to the command menu, holding
 * R shows the party list, and the other buttons go to
 * BattleMenu_HandleSwitchButtons. Stadium 0 counterpart of Stadium 1's
 * BattleScene_HandlePlayerPartySelection, with the two controller pointers
 * kept in locals instead of globals.
 */
void BattleMenu_UpdateSwitchMenu(ActivePokemon* arg0) {
    ActivePokemonState* sp18 = &arg0->state;
    s32 idx;
    Controller* c1;
    Controller* c2;

    if (arg0->sessionTeams->tagTeamSize == 1) {
        c1 = &gControllers[arg0->sessionTeams->teamMember[0]->controllerPort];
        c2 = &gControllers[arg0->sessionTeams->teamMember[0]->controllerPort];
    } else {
        c1 = &gControllers[arg0->sessionTeams->teamMember[sp18->menuTeamMemberIndex]->controllerPort];
        idx = sp18->menuTeamMemberIndex == 0;
        c2 = &gControllers[arg0->sessionTeams->teamMember[idx]->controllerPort];
    }

    if (arg0->captionState.active != 0) {
        if (sp18->controller->buttonPressed & 0xE03F) {
            func_8211F274(arg0);
        }
    } else if (sp18->selectedCommandOption == 0) {
        sp18->selectedCommandOption = 2;
    } else if ((c1->buttonPressed & 0x20) && (sp18->faintState != 0x10) &&
               !(c1->buttonDown & 0x10) && !(c2->buttonDown & 0x10)) {
        BattleScene_SelectActiveController(arg0);
        BattleAnim_PlaySoundEffect3();
        sp18->selectedCommandOption = 0;
    } else {
        sp18->showingCommandOptions = 0;
        if ((c1->buttonDown & 0x10) || (c2->buttonDown & 0x10)) {
            if ((c1->buttonPressed & 0x10) || (c2->buttonPressed & 0x10)) {
                BattleAnim_PlaySoundEffect1();
            }
            sp18->showingCommandOptions = 1;
        }
        BattleMenu_HandleSwitchButtons(arg0, (s8*)sp18->controller);
    }
}

extern u8 D_800AAF50[];
void BattleMenu_UpdateSwitchMenu(ActivePokemon* active_pokemon);
void BattleMenu_TakeControlOnCButtonPress(ActivePokemon*, u8*, u8*, s32);
/**
 * When the player's Pokemon has fainted (state 0x10 at +0x2E), runs the forced
 * Pokemon menu (no L to go back) for its replacement and returns 1; returns 0
 * otherwise, so the normal command menu runs.
 */
s32 BattleScene_HandlePlayerFaintedSwitch(ActivePokemon* arg0, ActivePokemon* arg1) {
    u8* c1;
    u8* c2;
    s8* team;
    ActivePokemonState* state = &arg0->state;
    ActivePokemonState* other = &arg1->state;

    if (arg0->sessionTeams->tagTeamSize == 1) {
        c1 = c2 = &D_800AAF50[M2C_FIELD(arg0->sessionTeams->teamMember[0], u8*, 1) * 0x24];
    } else {
        team = M2C_FIELD(arg0, s8**, 0x85C);
        c1 = &D_800AAF50[M2C_FIELD(M2C_FIELD(team, s8**, 8), u8*, 1) * 0x24];
        c2 = &D_800AAF50[M2C_FIELD(M2C_FIELD(team, s8**, 0xC), u8*, 1) * 0x24];
    }
    if ((state->faintState == 0x10) && (other->faintState == 0x10)) {
        if (state->selectedCommandOption == 3) {
            func_8210C708((s8*)arg0);
            return 1;
        }
        state->selectedCommand = 2;
        state->selectedCommandOption = 2;
        BattleMenu_UpdateSwitchMenu(arg0);
        return 1;
    }
    if (state->faintState == 0x10) {
        state->selectedCommand = 2;
        state->selectedCommandOption = 2;
        other->selectedCommandOption = 3;
        other->selectedCommand = 1;
        BattleMenu_TakeControlOnCButtonPress(arg0, c1, c2, arg0->sessionTeams->tagTeamSize);
        BattleMenu_UpdateSwitchMenu(arg0);
        return 1;
    }
    return 0;
}

/*
 * Stadium 0 counterpart of Stadium 1's BattleScene_ForfeitPrompt, with the two
 * controller pointers kept in locals instead of globals.
 */
/**
 * Surrender prompt (こうさんしますか？ いいえ はい, opened with Start): the D-pad moves the cursor and A on はい
 * makes the other side the winner, A on いいえ closes it. Closes when the other side has the prompt
 * open. Ran in play when 1P pressed Start.
 */
void BattleMenu_UpdateSurrenderPrompt(ActivePokemon* arg0) {
    ActivePokemonState* sp18 = &arg0->state;
    ActivePokemonState* temp_a0 = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->state;
    Controller* c1;
    Controller* c2;

    if (arg0->sessionTeams->tagTeamSize == 1) {
        c1 = &gControllers[arg0->sessionTeams->teamMember[0]->controllerPort];
        c2 = &gControllers[arg0->sessionTeams->teamMember[0]->controllerPort];
    } else {
        c1 = &gControllers[arg0->sessionTeams->teamMember[0]->controllerPort];
        c2 = &gControllers[arg0->sessionTeams->teamMember[1]->controllerPort];
    }

    if (temp_a0->selectedCommandOption == 4) {
        sp18->selectedCommandOption = 0;
        sp18->selectedCommand = 0;
        return;
    }

    if (sp18->selectedCommandOption != 4) {
        sp18->surrenderCursor = 0;
    }

    sp18->selectedCommandOption = 4;

    if ((c1->buttonPressed & 0x200) || (c2->buttonPressed & 0x200)) {
        sp18->surrenderCursor = 0;
        Audio_PlaySoundEffectById(1);
    }

    if ((c1->buttonPressed & 0x100) || (c2->buttonPressed & 0x100)) {
        sp18->surrenderCursor = 1;
        Audio_PlaySoundEffectById(1);
    }

    if ((sp18->surrenderCursor == 1) && ((c1->buttonPressed & 0x8000) || (c2->buttonPressed & 0x8000))) {
        Audio_PlaySoundEffectById(2);
        sBattleScene.scene->winner = (BattleScene_GetParticipantSideIndex(arg0) == 0) + 1;
    } else if ((sp18->surrenderCursor == 0) && ((c1->buttonPressed & 0x8000) || (c2->buttonPressed & 0x8000))) {
        sp18->selectedCommandOption = 0;
        sp18->selectedCommand = 0;
        Audio_PlaySoundEffectById(3);
    }
}

extern u8 D_800AAF50[];
void BattleMenu_TakeControlOnBPress(ActivePokemon*, u8*, u8*, s32);
void func_82134D60(void);

/**
 * Reads the buttons of the Pokemon's controller(s) (both trainers in a tag battle) into its
 * command state: A sets 1, B sets 2 and lets the partner take control, Start sets 3. A, B
 * or Start (when the other side isn't in state 4) also calls func_82134D60.
 */
void func_8210D6BC(ActivePokemon* arg0) {
    s8* state = (s8*)arg0 + 0x78C;
    s8* other = (s8*)sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0] + 0x78C;
    u8* c1;
    u8* c2;
    s8* team;
    s32 buttons;

    if (M2C_FIELD(state, s32*, 0x10) != 0) {
        return;
    }
    if (arg0->sessionTeams->tagTeamSize == 1U) {
        c1 = c2 = &D_800AAF50[M2C_FIELD(arg0->sessionTeams->teamMember[0], u8*, 1) * 0x24];
    } else {
        team = M2C_FIELD(arg0, s8**, 0x85C);
        c1 = &D_800AAF50[M2C_FIELD(M2C_FIELD(team, s8**, 8), u8*, 1) * 0x24];
        c2 = &D_800AAF50[M2C_FIELD(M2C_FIELD(team, s8**, 0xC), u8*, 1) * 0x24];
    }
    if (M2C_FIELD(M2C_FIELD(state, s8**, 0xCC), u16*, 8) & 0x8000) {
        M2C_FIELD(state, s32*, 4) = 1;
    } else {
        buttons = M2C_FIELD(c2, u16*, 8) | M2C_FIELD(c1, u16*, 8);
        if (buttons & 0x4000) {
            M2C_FIELD(state, s32*, 4) = 2;
            BattleMenu_TakeControlOnBPress(arg0, c1, c2, arg0->sessionTeams->tagTeamSize);
        } else if (buttons & 0x1000) {
            M2C_FIELD(state, s32*, 4) = 3;
        } else {
            M2C_FIELD(state, s32*, 4) = 0;
        }
    }
    buttons = M2C_FIELD(c2, u16*, 8) | M2C_FIELD(c1, u16*, 8);
    if ((buttons & 0x8000) || (buttons & 0x4000) || ((buttons & 0x1000) && (M2C_FIELD(other, s32*, 0x10) != 4))) {
        func_82134D60();
    }
}

s32 func_8210C778(ActivePokemon*);

void func_8210D6BC(ActivePokemon* active_pokemon);
void BattleMenu_UpdateSwitchMenu(ActivePokemon* active_pokemon);
void BattleMenu_UpdateSurrenderPrompt(ActivePokemon* active_pokemon);
/**
 * Reads the player's command menu input for this turn. Returns 1 once an action has been
 * chosen.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (164 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleScene_HandlePlayerActionInput(ActivePokemon* arg0) {
    ActivePokemonState* opponent_state = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->state;

    if (opponent_state->faintState == 0x10) {
        if (func_8210C708(arg0) != 0) {
            return 1;
        }
    } else if (func_8210C778(arg0) != 0) {
        return 1;
    }

    func_8210D6BC(arg0);

    switch (arg0->state.selectedCommand) {
        case 2:
            BattleMenu_UpdateSwitchMenu(arg0);
            return 1;

        case 3:
            BattleMenu_UpdateSurrenderPrompt(arg0);
            return 1;

        case 1:
            break;
    }
    return 0;
}

/**
 * Collects the human player's action for the turn: handles a fainted switch, otherwise
 * reads the command menu unless the Pokémon is locked into a move, in which case the
 * repeat is confirmed.
 */
void BattleScene_CollectPlayerAction(ActivePokemon* arg0, ActivePokemon* arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    BattleMonRuntime* sp20 = &arg0->state.runtime;
    BattleMonRuntime* sp1C = &arg1->state.runtime;

    if (BattleScene_HandlePlayerFaintedSwitch(arg0, arg1) == 0) {
        if (!(sp20->volatileStatusFlags & 0x60)) {
            sp20->immobilizedReason &= ~8;
            sp1C->immobilizedReason &= ~8;
            if (!(sp20->immobilizedReason & 0x12)) {
                if (BattleScene_HandlePlayerActionInput(arg0) == 0) {
                    if (!(sp20->pendingStatusCondition & 0x27)) {
                        if (!(sp20->immobilizedReason & 0x21)) {
                            if (sp1C->immobilizedReason & 0x20) {
                                BattleScene_HandlePlayerMoveSelectionLocked(arg0, arg0->state.controller);
                                sp20->usedMove = 0xFF;
                            } else {
                                BattleScene_HandlePlayerMoveSelection(arg0);
                            }
                        } else {
                            BattleScene_HandlePlayerMoveSelectionLocked(arg0, arg0->state.controller);
                        }
                    } else {
                        BattleScene_HandlePlayerMoveSelectionLocked(arg0, arg0->state.controller);
                    }
                }
            } else {
                BattleScene_ConfirmForcedMoveRepeat(arg0);
            }
        } else {
            BattleScene_ConfirmForcedMoveRepeat(arg0);
        }
    }
}

/**
 * Returns 1 when none of the Pokemon's non-disabled moves has PP left, so it
 * must use Struggle (move slot 4); 0 otherwise.
 */
s32 BattleMenu_MustStruggle(ActivePokemon* arg0) {
    u8* mon = (u8*)arg0 + 0x7C6;
    s32 pp = 0;
    s32 disabled;

    if (arg0->state.runtime.disabledMoveState != 0) {
        disabled = mon[0x52] >> 4;
        if (disabled != 0) {
            pp = mon[0x32] & 0x3F;
        }
        if (disabled != 1) {
            pp |= mon[0x33] & 0x3F;
        }
        if (disabled != 2) {
            pp |= mon[0x34] & 0x3F;
        }
        if (disabled != 3) {
            pp |= mon[0x35] & 0x3F;
        }
    } else {
        pp = mon[0x32] & 0x3F;
        pp |= mon[0x33] & 0x3F;
        pp |= mon[0x34] & 0x3F;
        pp |= mon[0x35] & 0x3F;
    }
    if (pp == 0) {
        return 1;
    }
    return 0;
}

s32 BattleAi_ChooseTurnAction(s32, s32, s32, s32, s8*);
/**
 * When the COM's Pokemon has fainted, asks the AI for a replacement at frame 60
 * of the command timer (BattleAi_ChooseTurnAction returns 4 + party slot) and
 * returns 1; returns 0 otherwise. Seen in game: after Pinsir fainted the AI
 * returned 9 and Gengar (party slot 5) came out.
 */
s32 BattleScene_HandleCpuFaintedSwitch(ActivePokemon* arg0, ActivePokemon* arg1) {
    ActivePokemonState* state = &arg0->state;
    ActivePokemonState* other = &arg1->state;
    s32 pad[2]; // FAKE

    if ((state->faintState == 0x10) && (other->faintState == 0x10)) {
        if (state->selectedCommandOption == 3) {
            func_8210C708((s8*)arg0);
            return 1;
        }
        state->selectedCommand = 2;
        state->selectedCommandOption = 2;
        if (D_FLT_82199EB0 == 60.0f) {
            func_82134D60();
            D_82199EB8 = BattleAi_ChooseTurnAction((s32)&arg0->state.runtime, (s32)&arg1->state.runtime, state->rosterIndex, other->rosterIndex, M2C_FIELD(arg1, s8**, 0x860));
            state->showingCommandOptions = 0;
            state->actionChosen = D_82199EB8 - 4;
            state->actionDelayTimer = 0;
            state->selectedCommandOption = 3;
            state->selectedCommand = 2;
        }
        return 1;
    }
    if (state->faintState == 0x10) {
        state->selectedCommand = 2;
        state->selectedCommandOption = 2;
        other->selectedCommandOption = 3;
        other->selectedCommand = 1;
        if (D_FLT_82199EB0 == 60.0f) {
            func_82134D60();
            D_82199EB8 = BattleAi_ChooseTurnAction((s32)&arg0->state.runtime, (s32)&arg1->state.runtime, state->rosterIndex, other->rosterIndex, M2C_FIELD(arg1, s8**, 0x860));
            state->showingCommandOptions = 0;
            state->actionChosen = D_82199EB8 - 4;
            state->actionDelayTimer = 0;
            state->selectedCommandOption = 3;
            state->selectedCommand = 2;
        }
        return 1;
    }
    return 0;
}

/**
 * Locks in a COM Pokémon's forced repeat of its current move after the usual delay.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleScene_CompleteCpuForcedAction(ActivePokemon* arg0, UNUSED ActivePokemon* arg1) {
    ActivePokemonState* ptr = &arg0->state;

    BattleScene_ApplyForcedActionDelay(arg0);
    ptr->moveSelectionLocked = 1;
    ptr->selectedCommand = 1;
    ptr->selectedMoveIndex = ptr->moveIndex;
    ptr->selectedCommandOption = 3;
}

/**
 * The COM cannot pick a move this turn (asleep or frozen, recharging or locked
 * in, or held by the opponent's trapping move): after the usual 30/90-frame
 * delays it confirms Fight with the current move slot. Seen in game with the
 * COM asleep.
 */
void BattleScene_AutoConfirmCpuMove(ActivePokemon* arg0, ActivePokemon* arg1) {
    ActivePokemonState* sp20 = &arg1->state;
    ActivePokemonState* sp1C = &arg0->state;

    BattleScene_ApplyForcedActionDelay(arg0);
    sp1C->moveSelectionLocked = 1;

    if ((D_82199EB0 == 30.0f) && (D_82199EB8 < 4)) {
        BattleAnim_PlaySoundEffect2();
    }

    if ((D_82199EB8 < 4) && (D_82199EB0 >= 30.0f)) {
        sp1C->selectedCommandOption = 1;
        sp1C->selectedCommand = 1;
    }

    if (((D_82199EB0 >= 90.0f) || ((sp20->selectedCommandOption == 3) && (D_82199EB0 >= 10.0f))) && (D_82199EB8 < 4)) {
        BattleAnim_PlaySoundEffect2();
        sp1C->selectedCommand = 1;
        sp1C->selectedCommandOption = 3;
        sp1C->selectedMoveIndex = sp1C->moveIndex;
    }
}

s32 BattleMenu_MustStruggle(ActivePokemon* arg0);
/**
 * Applies the COM's chosen move (a slot under 4) on its thinking timer: at frame 30 it
 * opens Fight with a sound, and at frame 90 (or 10 once the player has locked in) it picks
 * the move, or Struggle when no move has PP.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (5 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_ApplyCpuChoice(ActivePokemon* arg0, ActivePokemon* arg1) {
    ActivePokemonState* sp18;
    ActivePokemonState* sp14;
    s32 var_v0;

    sp18 = &arg0->state;
    sp14 = &arg1->state;

    if ((D_82199EB0 == 30.0f) && (D_82199EB8 < 4)) {
        BattleAnim_PlaySoundEffect2();
    }

    if (D_82199EB8 < 4) {
        if (D_82199EB0 >= 30.0f) {
            sp18->selectedCommandOption = 1;
            sp18->selectedCommand = 1;
        }
    }

    if ((D_82199EB0 >= 90.0f) || ((sp14->selectedCommandOption == 3) && (D_82199EB0 >= 10.0f))) {
        if (D_82199EB8 < 4) {
            BattleAnim_PlaySoundEffect2();
            sp18->selectedCommand = 1;
            sp18->selectedCommandOption = 3;
            if (BattleMenu_MustStruggle(arg0) != 0) {
                sp18->moveIndex = 4;
                sp18->selectedMoveIndex = 4;
            } else {
                var_v0 = D_82199EB8;
                sp18->moveIndex = var_v0;
                sp18->selectedMoveIndex = var_v0;
            }
        }
    }
}

/**
 * Applies the COM's choice once its thinking delay is over when the choice is a switch
 * (4 or more). Returns 1 if it applied one.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (11 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleScene_ApplyCpuSwitchChoice(ActivePokemon* arg0, ActivePokemon* arg1) {
    ActivePokemonState* sp1C = &arg0->state;
    ActivePokemonState* sp18 = &arg1->state;

    if ((D_82199EB0 == 30.0f) && (D_82199EB8 >= 4)) {
        BattleAnim_PlaySoundEffect2();
    }

    if (D_82199EB0 >= 30.0f) {
        if (D_82199EB8 >= 4) {
            sp1C->selectedCommandOption = 2;
            sp1C->selectedCommand = 2;
        }
    }

    if ((D_82199EB0 >= 90.0f) || ((sp18->selectedCommandOption == 3) && (D_82199EB0 >= 10.0f))) {
        if (D_82199EB8 >= 4) {
            BattleAnim_PlaySoundEffect2();
            sp1C->showingCommandOptions = 0;
            sp1C->actionChosen = D_82199EB8 - 4;
            sp1C->actionDelayTimer = 0;
            sp1C->selectedCommandOption = 3;
            sp1C->selectedCommand = 2;
        }
    }

    if (D_82199EB8 >= 4) {
        return 1;
    }
    return 0;
}

extern f32 D_84390120;
extern s32 D_8439013C;
extern s32 D_84390138;
extern s32 D_82199EBC;
s32 BattleAi_ChooseTurnAction(s32, s32, s32, s32, s8*);
/**
 * On the first frame of the COM's thinking delay, runs the COM AI once to pick its turn
 * action.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (11 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleScene_TriggerCpuChoice(s32 arg0, s32 arg1, s8* arg2, s8* arg3, ActivePokemon* arg4) {
    if (D_FLT_82199EB0 == 1.0f) {
        if (D_82199EBC == 0) {
            D_82199EBC = 1;
            D_82199EB8 = BattleAi_ChooseTurnAction(arg0, arg1, M2C_FIELD(arg2, s32*, 8), M2C_FIELD(arg3, s32*, 8), M2C_FIELD(arg4, s8**, 0x860));
        }
    }
}

extern f32 D_82199EB0;
extern s32 D_82199EBC;
/**
 * Collects the COM's action for the turn: handles a fainted switch, otherwise runs the COM
 * AI and applies its move or switch, or confirms a forced repeat.
 */
s32 BattleScene_CollectCpuAction(ActivePokemon* arg0, ActivePokemon* arg1) {
    BattleMonRuntime* sp34 = &arg0->state.runtime;
    BattleMonRuntime* sp30 = &arg1->state.runtime;
    ActivePokemonState* sp2C = &arg0->state;
    ActivePokemonState* sp28 = &arg1->state;

    if (BattleScene_HandleCpuFaintedSwitch(arg0, arg1) != 0) {
        return 0;
    }

    if (!(sp34->volatileStatusFlags & 0x60)) {
        sp34->immobilizedReason &= ~8;
        sp30->immobilizedReason &= ~8;

        if (!(sp34->immobilizedReason & 0x12)) {
            if (BattleScene_ApplyForcedActionDelay(arg0) != 0) {
                return 0;
            }

            if (D_82199EB0 == 0.0f) {
                D_82199EBC = 0;
                return 0;
            }

            BattleScene_TriggerCpuChoice(sp34, sp30, sp2C, sp28, arg1);

            if (BattleScene_ApplyCpuSwitchChoice(arg0, arg1) != 0) {
                return 0;
            }

            if (!(sp34->pendingStatusCondition & 0x27)) {
                if (!(sp34->immobilizedReason & 0x21)) {
                    if (sp30->immobilizedReason & 0x20) {
                        BattleScene_AutoConfirmCpuMove(arg0, arg1);
                        sp34->usedMove = 0xFF;
                    } else if (BattleScene_ApplyForcedActionDelay(arg0) != 0) {
                        return 0;
                    } else {
                        if (D_82199EB0 == 0.0f) {
                            D_82199EBC = 0;
                            return 0;
                        }
                        BattleScene_TriggerCpuChoice(sp34, sp30, sp2C, sp28, arg1);
                        BattleScene_ApplyCpuChoice(arg0, arg1);
                    }
                } else {
                    BattleScene_AutoConfirmCpuMove(arg0, arg1);
                }
            } else {
                BattleScene_AutoConfirmCpuMove(arg0, arg1);
            }
        } else {
            BattleScene_CompleteCpuForcedAction(arg0, arg1);
        }
    } else {
        BattleScene_CompleteCpuForcedAction(arg0, arg1);
    }

    return 0;
}

extern s8 D_82199DE0;
void func_8210E318(void)
{
  s8 *temp_v1;
  s8 **new_var; // FAKE: permuter temp
  s8 *temp_a1;
  int pad;
  temp_a1 = (s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x9CC))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  temp_v1 = *((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x9CC)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (temp_a1 + 1)) = (u8) ((*((u8 *) (((s8 *) temp_v1) + 1))) | 1); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x865)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x865))) | 1); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  new_var = (s8 **) (((s8 *) (&D_82199DE0)) + 4);
  ;
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x9CC)))) + 1)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x9CC)))) + 1))) | 1); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) (*new_var)) + 0x865)) = (u8) ((*((u8 *) (((s8 *) (*new_var)) + 0x865))) | 1); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

extern s8 D_82199DE0;
void func_8210E36C(void)
{
  s8 *temp_a1;
  s8 *temp_v1;
  ;
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x9CC)))) + 1)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x9CC)))) + 1))) & 0xFFFE); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x865)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x865))) & 0xFFFE); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  ;
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x9CC)))) + 1)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x9CC)))) + 1))) & 0xFFFE); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x865)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x865))) & 0xFFFE); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

typedef struct DemoInput8210E3C0 {
    /* 0x0 */ u16 frames;
    /* 0x2 */ u16 pressed;
    /* 0x4 */ u16 down;
} DemoInput8210E3C0;
extern DemoInput8210E3C0 D_8218ABB8[];
extern Controller D_82199EC8[];
extern s32 D_82199F10[];
extern s32 D_82199F18[];
/**
 * Feeds the scripted controller input for the current side (D_8218ABB8: frames,
 * pressed, held), as used by the demo battles.
 * Seen in play (2026-11-13) (title-screen demo battle, left idle after boot: Lapras vs Zapdos, then
 * Ditto and Jynx): ran for both sides on the demo's first turn, returning 0 for side 0 and 1 for
 * side 1. It did not run in the 165-move or Metronome Free Battle sweeps.
 */
void BattleDemo_PlayScriptedInput() {
    s32 i = func_82107A5C();
    Controller* c = &D_82199EC8[i];

    c->buttonPressed = 0;
    if (D_82199F18[i] == 0) {
        if ((D_82199F18[i] = D_8218ABB8[D_82199F10[i]].frames) != 0) {
            c->buttonPressed = D_8218ABB8[D_82199F10[i]].pressed;
            c->buttonDown = D_8218ABB8[D_82199F10[i]++].down;
        }
    }
    if (D_82199F18[i] > 0) {
        D_82199F18[i]--;
    }
}

void BattleDemo_PlayScriptedInput();
/**
 * Runs the scripted input, then locks move selection when a volatile or trapping
 * state forces the move.
 * Seen in play (2026-11-13) (title-screen demo battle, left idle after boot): ran for both sides on
 * the demo's first turn, each time just before BattleDemo_PlayScriptedInput. It did not run in
 * 165-move or Metronome Free Battles.
 * @unverified Name and comment guessed from the code.
 */
void Battle_PrepareTurnInput(ActivePokemon* arg0, ActivePokemon* arg1) {
    BattleMonRuntime* temp_v0 = &arg0->state.runtime;
    BattleMonRuntime* temp_v1 = &arg1->state.runtime;

    BattleDemo_PlayScriptedInput(arg0, arg1);
    if (!(temp_v0->volatileStatusFlags & 0x60)) {
        temp_v0->immobilizedReason &= ~8;
        temp_v1->immobilizedReason &= ~8;
        if (temp_v0->immobilizedReason & 0x12) {
            arg0->state.moveSelectionLocked = 1;
        }
    } else {
        arg0->state.moveSelectionLocked = 1;
    }
}

extern s32 D_82199F20;
extern u8 D_82199DFC[];
extern u8 D_82199E0C[];
extern s32 D_82199F10[2];
extern s32 D_82199F18[2];
void Battle_StartTurn(void);
extern Controller D_82199EC8[];
/*
 * Stadium 0 counterpart of Stadium 1's BattleScene_TickAttractModeInput
 * (debug/attract-mode buttons on controller D_82199EC8).
 */
void func_8210E504(void) {
    ActivePokemonState* sp24 = &sActivePokemon[0]->state;
    ActivePokemonState* sp20 = &sActivePokemon[1]->state;
    BattleMonRuntime* sp1C = &sActivePokemon[0]->state.runtime;
    BattleMonRuntime* sp18 = &sActivePokemon[1]->state.runtime;
    Controller* cont = &D_82199EC8[0];
    s32 move;
    s32 three = 3; // FAKE

    Battle_PrepareTurnInput(sActivePokemon[0], sActivePokemon[1]);
    Battle_PrepareTurnInput(sActivePokemon[1], sActivePokemon[0]);

    if (cont->buttonPressed & 0x20) {
        func_8210E318();
        BattleThumbnail_TriggerOwnerModelAnimation(sActivePokemon[0]);
        BattleThumbnail_TriggerOwnerModelAnimation(sActivePokemon[1]);
    }

    if (cont->buttonPressed & 0x10) {
        func_8210E36C();
    }

    if (cont->buttonPressed & 0x1000) {
        sp24->selectedCommand = 0;
        sp20->selectedCommand = 0;
        do {
            move = BattleAnim_RandomRange(4);
        } while ((move == D_82199F20) || (move >= 4));
        D_82199F20 = move;

        if (sp24->moveSelectionLocked == 0) {
            sp1C->usedMove = D_82199DFC[D_82199F20];
        }
        sp24->selectedCommandOption = three;

        if (sp20->moveSelectionLocked == 0) {
            sp18->usedMove = D_82199E0C[D_82199F20];
        }
        sp20->selectedCommandOption = three;

        if ((sp24->selectedCommandOption == three) && (sp20->selectedCommandOption == three)) {
            Battle_StartTurn();
        }
    }

    if (cont->buttonPressed & 0x2000) {
        D_82199F10[0] = 0;
        D_82199F18[0] = 0;
        D_82199F10[1] = 0;
        D_82199F18[1] = 0;
    }

    if (cont->buttonPressed & 0x8000) {
        sBattleScene.scene->winner = three;
    }
}

/**
 * Battle_InitParticipantRuntime
 *
 * Calls Battle_InitPokemonRuntimeState(arg0).  The two extra arguments are
 * accepted but not used; the retail code stores them to the stack, which is
 * why the signature declares them.
 * Seen in play (2026-11-13) ran during the opening of a COM Free Battle, before the first command
 * menu.
 * @unverified Name guessed from the code; comment kept.
 */
void Battle_InitParticipantRuntime(ActivePokemon* arg0, s32 arg1, s32 arg2) {
    Battle_InitPokemonRuntimeState(arg0);
}

/*
 * Battle_InitBothParticipants
 *
 * Resets the battle-scene state for both sides:
 *   - runs Battle_InitParticipantRuntime on the active-Pokemon pointers stored at D_82199DE0
 *     and D_82199DE4, passing (0, 1) for the first and (1, 0) for the second
 *     (Battle_InitParticipantRuntime ignores those two arguments);
 *   - calls func_8210F688(0, 1) and func_8210F688(1, 0);
 *   - clears the first two words of D_82199F10 and of D_82199F18;
 *   - clears bytes +0 and +4 of D_8219A4F0, sets byte +3 to 0xFF, and clears
 *     the halfwords at +0x1A, +0x1C, +0x1E and +0x20.
 * The meaning of func_8210F688's arguments and of the cleared fields is not
 * established from this function alone.
 *
 * D_82199DE0 is declared as s8 elsewhere in this file, so the pointer it holds
 * is read through a cast.
 */
extern ActivePokemon* D_82199DE4;
extern s32 D_82199F10[];
extern s32 D_82199F18[];
extern s16 D_8219A4F0[];
void func_8210F688(s32 arg0, s32 arg1);

/**
 * Initializes both participants and resets the demo input scripts and turn state.
 * Seen in play (2026-11-13) ran during the opening of a COM Free Battle, before the first command
 * menu.
 * @unverified Name and comment guessed from the code.
 */
void Battle_InitBothParticipants(void) {
    Battle_InitParticipantRuntime(*(ActivePokemon**)&D_82199DE0, 0, 1);
    Battle_InitParticipantRuntime(D_82199DE4, 1, 0);
    func_8210F688(0, 1);
    func_8210F688(1, 0);
    D_82199F10[0] = 0;
    D_82199F18[0] = 0;
    D_82199F10[1] = 0;
    D_82199F18[1] = 0;
    ((u8*)D_8219A4F0)[0] = 0;
    ((u8*)D_8219A4F0)[4] = 0;
    ((u8*)D_8219A4F0)[3] = 0xFF;
    D_8219A4F0[0xE] = 0;
    D_8219A4F0[0xD] = 0;
    D_8219A4F0[0xF] = 0;
    D_8219A4F0[0x10] = 0;
}

void func_8210E118(ActivePokemon*, ActivePokemon*);
void func_8210D90C(ActivePokemon*, ActivePokemon*);
void func_82125224(void);
void Battle_StartTurn(void);
extern u16 D_82199F24;
extern u16 D_82199F50;

/**
 * Gets both sides' actions for the turn: the COM AI for a COM side (party flag
 * bit 1), the player's command input otherwise.
 */
void Battle_ChooseActions(void) {
    ActivePokemonState* state0 = &sActivePokemon[0]->state;
    ActivePokemonState* state1 = &sActivePokemon[1]->state;

    if (*M2C_FIELD(sActivePokemon[0], u8**, 0x860) & 2) {
        D_82199F24 = D_82199F50;
        func_8210E118(sActivePokemon[0], sActivePokemon[1]);
        D_82199F50 = D_82199F24;
    } else {
        func_8210D90C(sActivePokemon[0], sActivePokemon[1]);
    }
    if (*M2C_FIELD(sActivePokemon[1], u8**, 0x860) & 2) {
        D_82199F24 = D_82199F50;
        func_8210E118(sActivePokemon[1], sActivePokemon[0]);
        D_82199F50 = D_82199F24;
    } else {
        func_8210D90C(sActivePokemon[1], sActivePokemon[0]);
    }
    if ((state0->selectedCommandOption == 3) && (state1->selectedCommandOption == 3)) {
        if (state0->selectedCommand == 2) {
            BattleMenu_CommitSwitchSelection((s8*)sActivePokemon[0]);
        } else {
            BattleMenu_CommitMoveSelection(sActivePokemon[0]);
        }
        if (state1->selectedCommand == 2) {
            BattleMenu_CommitSwitchSelection((s8*)sActivePokemon[1]);
        } else {
            BattleMenu_CommitMoveSelection(sActivePokemon[1]);
        }
        if ((state0->selectedCommand == 2) || (state1->selectedCommand == 2)) {
            func_82125224();
            return;
        }
        Battle_StartTurn();
    }
}

void func_8210E504(void);
void Battle_ChooseActions(void);

/**
 * Clears unlocked move selections, then picks the action-choice routine for the
 * battle mode.
 */
void Battle_ChooseActionsForMode(void) {
    ActivePokemonState* state0 = &sActivePokemon[0]->state;
    ActivePokemonState* state1 = &sActivePokemon[1]->state;

    if (state0->moveSelectionLocked != 1) {
        state0->moveSelectionLocked = 0;
    }
    if (state1->moveSelectionLocked != 1) {
        state1->moveSelectionLocked = 0;
    }
    switch (sBattleScene.scene->mode) {
        case 1:
            Battle_ChooseActions();
            break;
        case 5:
            func_8210E504();
            break;
    }
    BattleMenu_TickCommandTimer();
}
