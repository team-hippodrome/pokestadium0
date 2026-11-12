/* Stadium Zero fragment012_17ED00. */

#include "global.h"
#include "fragments/battle_engine/battle_engine.h"
#include "m2c_macros.h"

extern f32 D_82199EB0;
extern s32 D_82199EB8;

extern f32 D_FLT_82199EB0;

s32 func_8210C6B0(void) {
    if (D_FLT_82199EB0 >= 150.0f) {
        return 1;
    }
    D_FLT_82199EB0 += 1.0f;
    return 0;
}

extern f32 D_FLT_82199EB0;

void func_8210C6F8(void) {
    D_FLT_82199EB0 = 0.0f;
}

s32 func_8210C708(s8 *arg0) {
    s8 *temp_v1;

    temp_v1 = arg0 + 0x78C;
    if (M2C_FIELD(arg0, s32 *, 0x79C) == 3) {
        M2C_FIELD(temp_v1, u16 *, 0x1E) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x1E) + 0x38E);
        return 1;
    }
    return 0;
}

void BattleScene_SelectActiveController(ActivePokemon* arg0) {
    ActivePokemonState* ptr = &arg0->state;

    M2C_FIELD(arg0, u8*, 0x7B9) = M2C_FIELD(arg0, u8*, 0x7B8);
    ptr->controller = &gControllers[arg0->sessionTeams->teamMember[M2C_FIELD(arg0, u8*, 0x7B9)]->controllerPort];
}

s32 func_82107A5C(void);
void func_8210C738(ActivePokemon* arg0, ActivePokemonState* arg1, Controller* arg2);
M2C_UNK func_82134D80();
extern s8 D_82199DE0;

s32 func_8210C778(ActivePokemon* arg0) {
    ActivePokemonState* state = &arg0->state;
    ActivePokemonState* other = &((ActivePokemon**)&D_82199DE0)[func_82107A5C() == 0]->state;
    Controller* controller = state->controller;
    s32 pad; // FAKE: stack padding

    if (state->unk_10 == 3) {
        if ((M2C_FIELD(controller, u16*, 8) & 0x20) && (other->unk_2D != 0x10)) {
            if (state->unk_04 == 2) {
                func_8210C738(arg0, other, controller);
            }
            state->unk_10 = 0;
            func_82134D80();
            return 0;
        }
        state->unk_1E += 0x38E;
        return 1;
    }
    return 0;
}

void func_8210C82C(ActivePokemon* arg0) {
    BattleMonRuntime* temp_v1 = &arg0->state.runtime;
    ActivePokemonState* temp_v0 = &arg0->state;

    if (arg0->state.unk_14 != 4) {
        temp_v0->unk_0C = temp_v0->unk_14;
        if (temp_v0->unk_2A == 0) {
            temp_v1->usedMove = temp_v1->moves[temp_v0->unk_0C];
        }
    } else {
        if (temp_v1->unk_4C & 0x20) {
            temp_v0->unk_0C = temp_v0->unk_14;
        } else {
            temp_v0->unk_14 = 0;
            temp_v0->unk_0C = 0;
            temp_v1->usedMove = 0xA5;
        }
    }
}

void func_8211F274();
s32 func_82107F88(s32);
M2C_UNK func_8211F288();
extern s32 D_8218C6F0;
s32 func_8210C8A0(arg0) ActivePokemon *arg0;
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
  if (temp_a0->unk_52 != 0)
  {
    temp_a1 = temp_a0->unk_52 >> 4;
    for (i = 0; i < 4; i++)
    {
      if (temp_a1 != i)
      {
        var_v1 |= temp_a0->unk_32[i] & 0x3F;
      }
    }

  }
  else
  {
 do { for (i = 0; i < 4; i++) { var_v1 |= temp_a0->unk_32[i] & 0x3F; } } while (0);
  }
  if (var_v1 == 0)
  {
    temp_v0 = &arg0->state;
    if ((*((s32 *) (((s8 *) arg0) + 0xA04))) == 0)
    {
      if (temp_v0->unk_10 == 0)
      {
        temp_v0->unk_10 = 1;
      }
      func_8211F274(arg0);
      func_8211F288(arg0, D_8218C6F0, func_82107F88((s32) arg0));
    }
    else
      if (cont->buttonPressed & 0x20)
    {
      func_8211F274(arg0);
      arg0->state.unk_10 = 0;
      BattleAnim_PlaySoundEffect3();
    }
    else
      if (cont->buttonPressed & 0x8000)
    {
      func_8211F274(arg0);
      temp_v0->unk_1E = 0;
      temp_v0->unk_10 = 3;
      temp_v0->unk_14 = 4;
    }
    return 1;
  }
  return 0;
}

void func_8211F274();
M2C_UNK func_8211F288();
extern s32 D_8218C6F4;
extern s32 D_8218C6F8;

typedef struct BattleMoveCheck8210CA24 {
    /* 0x000 */ char unk000[0x7A0];
    /* 0x7A0 */ s32 slot;
    /* 0x7A4 */ char unk7A4[0x7F8 - 0x7A4];
    /* 0x7F8 */ u8 moveFlags[1];
} BattleMoveCheck8210CA24;

s32 func_8210CA24(s8* arg0) {
    u8 flags;
    s8* state;

    if (!(((BattleMoveCheck8210CA24*)arg0)->moveFlags[((BattleMoveCheck8210CA24*)arg0)->slot] & 0x3F)) {
        func_8211F274(arg0);
        func_8211F288(arg0, D_8218C6F4);
        return 1;
    }
    flags = M2C_FIELD(arg0, u8*, 0x818);
    state = arg0 + 0x78C;
    if ((flags & 0xF) && ((flags >> 4) == M2C_FIELD(state, s32*, 0x14))) {
        func_8211F274(arg0);
        func_8211F288(arg0, D_8218C6F8);
        return 1;
    }
    M2C_FIELD(state, s16*, 0x1E) = 0;
    M2C_FIELD(state, s32*, 0x10) = 3;
    M2C_FIELD(state, s8*, 0x1C) = 0;
    return 0;
}

void func_82134D60(void);
s32 func_8210CA24(s8*);
void func_8210CACC(s8* arg0) {
    s32 buttons;
    s8* ctrl;

    ctrl = M2C_FIELD(arg0, s8**, 0x858);
    buttons = M2C_FIELD(ctrl, u16*, 8);

    if ((buttons & 8) && (M2C_FIELD(arg0, u8*, 0x7E5) != 0) && (M2C_FIELD(arg0, u8*, 0x7E5) < 0xA6)) {
        func_82134D60();
        M2C_FIELD(arg0, s32*, 0x7A0) = 0;
        func_8210CA24(arg0);
    } else if ((buttons & 1) && (M2C_FIELD(arg0, u8*, 0x7E6) != 0) && (M2C_FIELD(arg0, u8*, 0x7E6) < 0xA6)) {
        func_82134D60();
        M2C_FIELD(arg0, s32*, 0x7A0) = 1;
        func_8210CA24(arg0);
    } else if ((buttons & 4) && (M2C_FIELD(arg0, u8*, 0x7E7) != 0) && (M2C_FIELD(arg0, u8*, 0x7E7) < 0xA6)) {
        func_82134D60();
        M2C_FIELD(arg0, s32*, 0x7A0) = 2;
        func_8210CA24(arg0);
    } else if ((buttons & 2) && (M2C_FIELD(arg0, u8*, 0x7E8) != 0) && (M2C_FIELD(arg0, u8*, 0x7E8) < 0xA6)) {
        func_82134D60();
        M2C_FIELD(arg0, s32*, 0x7A0) = 3;
        func_8210CA24(arg0);
    }
}

s32 func_8210C8A0();                                /* extern */
void func_82134D40(s8 *);
M2C_UNK func_82134D80(s8 *);                        /* extern */
void func_8211F274();

/*
 * func_8210CBD4
 *
 * Does nothing unless the word at arg0 + 0x790 is 1 and func_8210C8A0()
 * returns 0. Then, with `rec` = the pointer at arg0 + 0x858 and `sub` =
 * arg0 + 0x78C:
 *  - if the word at arg0 + 0xA04 is non-zero: calls func_8211F274(arg0) when
 *    any of the bits 0xE03F is set in the halfword at rec + 8;
 *  - otherwise clears sub[0x20]; if sub[0x10] is 0 it sets it to 1 and
 *    returns; else if bit 0x20 of rec + 8 is set and bit 0x10 of the halfword
 *    at rec + 6 is clear, it clears sub[0x10], calls func_82134D80(arg0) and
 *    returns; else it clears the byte sub[0x1C], and, when bit 0x10 of rec + 6
 *    is set, calls func_82134D40(arg0) if bit 0x10 of rec + 8 is also set and
 *    sets the byte sub[0x1C] to 1; finally it calls func_8210CACC(arg0).
 *
 * What the fields and the callees mean is not established (rec[6] and rec[8]
 * look like button/state bit masks but that is a guess from the masks only).
 * Matching notes: func_82134D40 must be declared `void` (the result is unused;
 * an `M2C_UNK` return changes register allocation), and the unused `pad` local,
 * declared after `temp_v1`, moves the spill slot of `temp_v0` to sp+0x18.
 */
void func_8210CBD4(s8 *arg0) {
    void *temp_v0;
    void *temp_v1;
    UNUSED s32 pad; // FAKE: stack padding

    temp_v1 = M2C_FIELD(arg0, void **, 0x858);
    if ((M2C_FIELD(arg0, s32 *, 0x790) == 1) && (func_8210C8A0() == 0)) {
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
            func_8210CACC(arg0);
        }
    }
}

s32 func_8210CCDC(s8 *arg0, M2C_UNK arg1)
{
  *((s8 *) (((s8 *) arg0) + 0x7B6)) = 1;
  if (1)
  {
    *((s8 *) (((s8 *) arg0) + 0x7B6)) = 1;
    func_8210CBD4(arg0);
    *((s8 *) (((s8 *) arg0) + 0x7B6)) = 1;
  }
  return 0;
}

void BattleScene_ConfirmForcedMoveRepeat(ActivePokemon* arg0) {
    ActivePokemonState* ptr = &arg0->state;

    BattleScene_ApplyForcedActionDelay(arg0);
    ptr->unk_2A = 1;
    ptr->unk_10 = 3;
    ptr->unk_0C = ptr->unk_14;
}

void func_8210CD58(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x794) = (s32) M2C_FIELD(arg0, s32 *, 0x7A4);
    if (M2C_FIELD(arg0, u8 *, 0x7BA) != 0x10) {
        M2C_FIELD(arg0, u8 *, 0x7BA) = 0xFU;
    }
}

void func_8211F274();
M2C_UNK func_8211F288();
extern s32 D_8218C6FC;

s32 BattleScene_ValidateSelectedPartyMember(ActivePokemon* arg0) {
    if (arg0->sessionTeams->teamMember[M2C_FIELD(arg0, u8*, 0x7B9)]->pokemonPicked[arg0->state.unk_18].hp != 0) {
        return 1;
    }

    func_8211F274(arg0);
    func_8211F288(arg0, D_8218C6FC);
    return 0;
}

void func_82108DE8(ActivePokemon*, u8*);
void func_8210CDEC(ActivePokemon* arg0, u8* arg1, u8* arg2, s32 arg3) {
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
            state->ownerTeamMemberIndex = state->unk_2D_zero;
            state->unk_2D_zero = 0;
            func_82108DE8(arg0, arg1);
        } else if (*(u16*)(arg2 + 8) & mask) {
            state->ownerTeamMemberIndex = state->unk_2D_zero;
            state->unk_2D_zero = 0;
            func_82108DE8(arg0, arg2);
        }
    } else {
        if (*(u16*)(arg1 + 8) & mask) {
            state->ownerTeamMemberIndex = state->unk_2D_zero;
            state->unk_2D_zero = 0;
            func_82108DE8(arg0, arg1);
        } else if (*(u16*)(arg2 + 8) & mask) {
            state->ownerTeamMemberIndex = state->unk_2D_zero;
            state->unk_2D_zero = 1;
            func_82108DE8(arg0, arg2);
        }
    }
}

void func_82108DE8(ActivePokemon*, u8*);
void func_8210CEE8(ActivePokemon* arg0, u8* arg1, u8* arg2, s32 arg3) {
    ActivePokemonState* state = &arg0->state;
    u16 mask;

    if (arg0->sessionTeams->teamMember[0]->numberOfPokemonBrought == 3) {
        mask = 0xD;
    } else {
        mask = 0xC00F;
    }
    if (arg3 == 1) {
        if (*(u16*)(arg1 + 8) & mask) {
            state->ownerTeamMemberIndex = state->unk_2D_zero;
            state->unk_2D_zero = 0;
            func_82108DE8(arg0, arg1);
        } else if (*(u16*)(arg2 + 8) & mask) {
            state->ownerTeamMemberIndex = state->unk_2D_zero;
            state->unk_2D_zero = 0;
            func_82108DE8(arg0, arg2);
        }
    } else {
        if (*(u16*)(arg1 + 8) & mask) {
            state->ownerTeamMemberIndex = state->unk_2D_zero;
            state->unk_2D_zero = 0;
            func_82108DE8(arg0, arg1);
        } else if (*(u16*)(arg2 + 8) & mask) {
            state->ownerTeamMemberIndex = state->unk_2D_zero;
            state->unk_2D_zero = 1;
            func_82108DE8(arg0, arg2);
        }
    }
}

s32 func_82107F88(s32);                             /* extern */
void func_8211F274();                            /* extern */
M2C_UNK func_8211F288(s32, s32, s32);               /* extern */
extern s32 D_8218C700;

void func_8210CFE4(s32 arg0) {
    func_8211F274();
    func_8211F288(arg0, D_8218C700, func_82107F88(arg0));
}

void func_82134D60(void);

void func_8210D020(ActivePokemon* arg0, s8* arg1) {
    u8* team = *(u8**)(M2C_FIELD(arg0, u8*, 0x7B9) * 4 + M2C_FIELD(arg0, s8**, 0x85C) + 8);
    ActivePokemonState* state = &arg0->state;

    if (team[2] == 3) {
        if (M2C_FIELD(arg1, u16*, 8) & 8) {
            arg0->state.unk_18 = 0;
        } else if (M2C_FIELD(arg1, u16*, 8) & 1) {
            arg0->state.unk_18 = 1;
        } else if (M2C_FIELD(arg1, u16*, 8) & 4) {
            arg0->state.unk_18 = 2;
        } else {
            return;
        }
    } else {
        if (M2C_FIELD(arg1, u16*, 8) & 8) {
            arg0->state.unk_18 = 0;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 2) {
            arg0->state.unk_18 = 1;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 0x4000) {
            arg0->state.unk_18 = 2;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 1) {
            arg0->state.unk_18 = 3;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 4) {
            arg0->state.unk_18 = 4;
        }
        if (M2C_FIELD(arg1, u16*, 8) & 0x8000) {
            arg0->state.unk_18 = 5;
        }
    }
    if (M2C_FIELD(arg1, u16*, 8) & 0xC00F) {
        if ((state->rosterIndex == state->unk_18) && (state->teamMemberIndex == state->unk_2D_zero)) {
            if (func_8210CD7C(arg0) != 0) {
                func_8210CFE4((s32)arg0);
            }
        } else if (state->unk_18 <= (u32)(team[2] - 1)) {
            if (func_8210CD7C(arg0) != 0) {
                func_82134D60();
                state->unk_1C = 0;
                state->unk_1E = 0;
                state->unk_10 = 3;
            }
        }
    }
}

/*
 * Stadium 0 counterpart of Stadium 1's BattleScene_HandlePlayerPartySelection,
 * with the two controller pointers kept in locals instead of globals.
 */
void func_8210D1B0(ActivePokemon* arg0) {
    ActivePokemonState* sp18 = &arg0->state;
    s32 idx;
    Controller* c1;
    Controller* c2;

    if (arg0->sessionTeams->tagTeamSize == 1) {
        c1 = &gControllers[arg0->sessionTeams->teamMember[0]->controllerPort];
        c2 = &gControllers[arg0->sessionTeams->teamMember[0]->controllerPort];
    } else {
        c1 = &gControllers[arg0->sessionTeams->teamMember[sp18->unk_2D_zero]->controllerPort];
        idx = sp18->unk_2D_zero == 0;
        c2 = &gControllers[arg0->sessionTeams->teamMember[idx]->controllerPort];
    }

    if (M2C_FIELD(arg0, s32*, 0xA04) != 0) {
        if (sp18->controller->buttonPressed & 0xE03F) {
            func_8211F274(arg0);
        }
    } else if (sp18->unk_10 == 0) {
        sp18->unk_10 = 2;
    } else if ((c1->buttonPressed & 0x20) && (sp18->unk_2D != 0x10) &&
               !(c1->buttonDown & 0x10) && !(c2->buttonDown & 0x10)) {
        BattleScene_SelectActiveController(arg0);
        BattleAnim_PlaySoundEffect3();
        sp18->unk_10 = 0;
    } else {
        sp18->unk_1C = 0;
        if ((c1->buttonDown & 0x10) || (c2->buttonDown & 0x10)) {
            if ((c1->buttonPressed & 0x10) || (c2->buttonPressed & 0x10)) {
                BattleAnim_PlaySoundEffect1();
            }
            sp18->unk_1C = 1;
        }
        func_8210D020(arg0, (s8*)sp18->controller);
    }
}

extern u8 D_800AAF50[];
void func_8210D1B0(ActivePokemon* active_pokemon);
void func_8210CEE8(ActivePokemon*, u8*, u8*, s32);
/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 BattleScene_HandlePlayerForcedActionState(ActivePokemon* arg0, ActivePokemon* arg1) {
    u8* c1;
    u8* c2;
    s8* team;
    ActivePokemonState* state = &arg0->state;
    ActivePokemonState* other = &arg1->state;

    if (M2C_FIELD(M2C_FIELD(arg0, s8**, 0x85C), u8*, 1) == 1) {
        c1 = c2 = &D_800AAF50[M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x85C), s8**, 8), u8*, 1) * 0x24];
    } else {
        team = M2C_FIELD(arg0, s8**, 0x85C);
        c1 = &D_800AAF50[M2C_FIELD(M2C_FIELD(team, s8**, 8), u8*, 1) * 0x24];
        c2 = &D_800AAF50[M2C_FIELD(M2C_FIELD(team, s8**, 0xC), u8*, 1) * 0x24];
    }
    if ((state->unk_2D == 0x10) && (other->unk_2D == 0x10)) {
        if (state->unk_10 == 3) {
            func_8210C708((s8*)arg0);
            return 1;
        }
        state->unk_04 = 2;
        state->unk_10 = 2;
        func_8210D1B0(arg0);
        return 1;
    }
    if (state->unk_2D == 0x10) {
        state->unk_04 = 2;
        state->unk_10 = 2;
        other->unk_10 = 3;
        other->unk_04 = 1;
        func_8210CEE8(arg0, c1, c2, M2C_FIELD(M2C_FIELD(arg0, s8**, 0x85C), u8*, 1));
        func_8210D1B0(arg0);
        return 1;
    }
    return 0;
}

/*
 * Stadium 0 counterpart of Stadium 1's BattleScene_ForfeitPrompt, with the two
 * controller pointers kept in locals instead of globals.
 */
void func_8210D4B4(ActivePokemon* arg0) {
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

    if (temp_a0->unk_10 == 4) {
        sp18->unk_10 = 0;
        sp18->unk_04 = 0;
        return;
    }

    if (sp18->unk_10 != 4) {
        sp18->unk_2F = 0;
    }

    sp18->unk_10 = 4;

    if ((c1->buttonPressed & 0x200) || (c2->buttonPressed & 0x200)) {
        sp18->unk_2F = 0;
        Audio_PlaySoundEffectById(1);
    }

    if ((c1->buttonPressed & 0x100) || (c2->buttonPressed & 0x100)) {
        sp18->unk_2F = 1;
        Audio_PlaySoundEffectById(1);
    }

    if ((sp18->unk_2F == 1) && ((c1->buttonPressed & 0x8000) || (c2->buttonPressed & 0x8000))) {
        Audio_PlaySoundEffectById(2);
        sBattleScene.scene->unk_40 = (BattleScene_GetParticipantSideIndex(arg0) == 0) + 1;
    } else if ((sp18->unk_2F == 0) && ((c1->buttonPressed & 0x8000) || (c2->buttonPressed & 0x8000))) {
        sp18->unk_10 = 0;
        sp18->unk_04 = 0;
        Audio_PlaySoundEffectById(3);
    }
}

extern u8 D_800AAF50[];
void func_8210CDEC(ActivePokemon*, u8*, u8*, s32);
void func_82134D60(void);

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
    if (M2C_FIELD(M2C_FIELD(arg0, s8**, 0x85C), u8*, 1) == 1U) {
        c1 = c2 = &D_800AAF50[M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x85C), s8**, 8), u8*, 1) * 0x24];
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
            func_8210CDEC(arg0, c1, c2, M2C_FIELD(M2C_FIELD(arg0, s8**, 0x85C), u8*, 1));
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
void func_8210D1B0(ActivePokemon* active_pokemon);
void func_8210D4B4(ActivePokemon* active_pokemon);
s32 BattleScene_HandlePlayerActionInput(ActivePokemon* arg0) {
    ActivePokemonState* opponent_state = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->state;

    if (M2C_FIELD(opponent_state, u8*, 0x2E) == 0x10) {
        if (func_8210C708(arg0) != 0) {
            return 1;
        }
    } else if (func_8210C778(arg0) != 0) {
        return 1;
    }

    func_8210D6BC(arg0);

    switch (arg0->state.unk_04) {
        case 2:
            func_8210D1B0(arg0);
            return 1;

        case 3:
            func_8210D4B4(arg0);
            return 1;

        case 1:
            break;
    }
    return 0;
}

void BattleScene_CollectPlayerAction(ActivePokemon* arg0, ActivePokemon* arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    BattleMonRuntime* sp20 = &arg0->state.runtime;
    BattleMonRuntime* sp1C = &arg1->state.runtime;

    if (BattleScene_HandlePlayerForcedActionState(arg0, arg1) == 0) {
        if (!(sp20->unk_4D & 0x60)) {
            sp20->unk_4C &= ~8;
            sp1C->unk_4C &= ~8;
            if (!(sp20->unk_4C & 0x12)) {
                if (BattleScene_HandlePlayerActionInput(arg0) == 0) {
                    if (!(sp20->unk_15 & 0x27)) {
                        if (!(sp20->unk_4C & 0x21)) {
                            if (sp1C->unk_4C & 0x20) {
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

s32 func_8210DA30(ActivePokemon* arg0) {
    u8* mon = (u8*)arg0 + 0x7C6;
    s32 pp = 0;
    s32 disabled;

    if (M2C_FIELD(arg0, u8*, 0x818) != 0) {
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

s32 func_82188770(s32, s32, s32, s32, s8*);
/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 BattleScene_WaitForCpuChoice(ActivePokemon* arg0, ActivePokemon* arg1) {
    ActivePokemonState* state = &arg0->state;
    ActivePokemonState* other = &arg1->state;
    s32 pad[2]; // FAKE

    if ((state->unk_2D == 0x10) && (other->unk_2D == 0x10)) {
        if (state->unk_10 == 3) {
            func_8210C708((s8*)arg0);
            return 1;
        }
        state->unk_04 = 2;
        state->unk_10 = 2;
        if (D_FLT_82199EB0 == 60.0f) {
            func_82134D60();
            D_82199EB8 = func_82188770((s32)&arg0->state.runtime, (s32)&arg1->state.runtime, state->rosterIndex, other->rosterIndex, M2C_FIELD(arg1, s8**, 0x860));
            state->unk_1C = 0;
            state->unk_18 = D_82199EB8 - 4;
            state->unk_1E = 0;
            state->unk_10 = 3;
            state->unk_04 = 2;
        }
        return 1;
    }
    if (state->unk_2D == 0x10) {
        state->unk_04 = 2;
        state->unk_10 = 2;
        other->unk_10 = 3;
        other->unk_04 = 1;
        if (D_FLT_82199EB0 == 60.0f) {
            func_82134D60();
            D_82199EB8 = func_82188770((s32)&arg0->state.runtime, (s32)&arg1->state.runtime, state->rosterIndex, other->rosterIndex, M2C_FIELD(arg1, s8**, 0x860));
            state->unk_1C = 0;
            state->unk_18 = D_82199EB8 - 4;
            state->unk_1E = 0;
            state->unk_10 = 3;
            state->unk_04 = 2;
        }
        return 1;
    }
    return 0;
}

void BattleScene_CompleteCpuForcedAction(ActivePokemon* arg0, UNUSED ActivePokemon* arg1) {
    ActivePokemonState* ptr = &arg0->state;

    BattleScene_ApplyForcedActionDelay(arg0);
    ptr->unk_2A = 1;
    ptr->unk_04 = 1;
    ptr->unk_0C = ptr->unk_14;
    ptr->unk_10 = 3;
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleScene_CompleteCpuMoveAction(ActivePokemon* arg0, ActivePokemon* arg1) {
    ActivePokemonState* sp20 = &arg1->state;
    ActivePokemonState* sp1C = &arg0->state;

    BattleScene_ApplyForcedActionDelay(arg0);
    sp1C->unk_2A = 1;

    if ((D_82199EB0 == 30.0f) && (D_82199EB8 < 4)) {
        BattleAnim_PlaySoundEffect2();
    }

    if ((D_82199EB8 < 4) && (D_82199EB0 >= 30.0f)) {
        sp1C->unk_10 = 1;
        sp1C->unk_04 = 1;
    }

    if (((D_82199EB0 >= 90.0f) || ((sp20->unk_10 == 3) && (D_82199EB0 >= 10.0f))) && (D_82199EB8 < 4)) {
        BattleAnim_PlaySoundEffect2();
        sp1C->unk_04 = 1;
        sp1C->unk_10 = 3;
        sp1C->unk_0C = sp1C->unk_14;
    }
}

s32 func_8210DA30(ActivePokemon* arg0);
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
            sp18->unk_10 = 1;
            sp18->unk_04 = 1;
        }
    }

    if ((D_82199EB0 >= 90.0f) || ((sp14->unk_10 == 3) && (D_82199EB0 >= 10.0f))) {
        if (D_82199EB8 < 4) {
            BattleAnim_PlaySoundEffect2();
            sp18->unk_04 = 1;
            sp18->unk_10 = 3;
            if (func_8210DA30(arg0) != 0) {
                sp18->unk_14 = 4;
                sp18->unk_0C = 4;
            } else {
                var_v0 = D_82199EB8;
                sp18->unk_14 = var_v0;
                sp18->unk_0C = var_v0;
            }
        }
    }
}

s32 BattleScene_ApplyCpuSwitchChoice(ActivePokemon* arg0, ActivePokemon* arg1) {
    ActivePokemonState* sp1C = &arg0->state;
    ActivePokemonState* sp18 = &arg1->state;

    if ((D_82199EB0 == 30.0f) && (D_82199EB8 >= 4)) {
        BattleAnim_PlaySoundEffect2();
    }

    if (D_82199EB0 >= 30.0f) {
        if (D_82199EB8 >= 4) {
            sp1C->unk_10 = 2;
            sp1C->unk_04 = 2;
        }
    }

    if ((D_82199EB0 >= 90.0f) || ((sp18->unk_10 == 3) && (D_82199EB0 >= 10.0f))) {
        if (D_82199EB8 >= 4) {
            BattleAnim_PlaySoundEffect2();
            sp1C->unk_1C = 0;
            sp1C->unk_18 = D_82199EB8 - 4;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
            sp1C->unk_04 = 2;
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
s32 func_82188770(s32, s32, s32, s32, s8*);
void BattleScene_TriggerCpuChoice(s32 arg0, s32 arg1, s8* arg2, s8* arg3, ActivePokemon* arg4) {
    if (D_FLT_82199EB0 == 1.0f) {
        if (D_82199EBC == 0) {
            D_82199EBC = 1;
            D_82199EB8 = func_82188770(arg0, arg1, M2C_FIELD(arg2, s32*, 8), M2C_FIELD(arg3, s32*, 8), M2C_FIELD(arg4, s8**, 0x860));
        }
    }
}

extern f32 D_82199EB0;
extern s32 D_82199EBC;
s32 BattleScene_CollectCpuAction(ActivePokemon* arg0, ActivePokemon* arg1) {
    BattleMonRuntime* sp34 = &arg0->state.runtime;
    BattleMonRuntime* sp30 = &arg1->state.runtime;
    ActivePokemonState* sp2C = &arg0->state;
    ActivePokemonState* sp28 = &arg1->state;

    if (BattleScene_WaitForCpuChoice(arg0, arg1) != 0) {
        return 0;
    }

    if (!(sp34->unk_4D & 0x60)) {
        sp34->unk_4C &= ~8;
        sp30->unk_4C &= ~8;

        if (!(sp34->unk_4C & 0x12)) {
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

            if (!(sp34->unk_15 & 0x27)) {
                if (!(sp34->unk_4C & 0x21)) {
                    if (sp30->unk_4C & 0x20) {
                        BattleScene_CompleteCpuMoveAction(arg0, arg1);
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
                    BattleScene_CompleteCpuMoveAction(arg0, arg1);
                }
            } else {
                BattleScene_CompleteCpuMoveAction(arg0, arg1);
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
void func_8210E3C0() {
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

void func_8210E3C0();
void func_8210E484(ActivePokemon* arg0, ActivePokemon* arg1) {
    BattleMonRuntime* temp_v0 = &arg0->state.runtime;
    BattleMonRuntime* temp_v1 = &arg1->state.runtime;

    func_8210E3C0(arg0, arg1);
    if (!(temp_v0->unk_4D & 0x60)) {
        temp_v0->unk_4C &= ~8;
        temp_v1->unk_4C &= ~8;
        if (temp_v0->unk_4C & 0x12) {
            arg0->state.unk_2A = 1;
        }
    } else {
        arg0->state.unk_2A = 1;
    }
}

extern s32 D_82199F20;
extern u8 D_82199DFC[];
extern u8 D_82199E0C[];
extern s32 D_82199F10[2];
extern s32 D_82199F18[2];
void func_82124EFC(void);
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

    func_8210E484(sActivePokemon[0], sActivePokemon[1]);
    func_8210E484(sActivePokemon[1], sActivePokemon[0]);

    if (cont->buttonPressed & 0x20) {
        func_8210E318();
        BattleThumbnail_TriggerOwnerModelAnimation(sActivePokemon[0]);
        BattleThumbnail_TriggerOwnerModelAnimation(sActivePokemon[1]);
    }

    if (cont->buttonPressed & 0x10) {
        func_8210E36C();
    }

    if (cont->buttonPressed & 0x1000) {
        sp24->unk_04 = 0;
        sp20->unk_04 = 0;
        do {
            move = BattleAnim_RandomRange(4);
        } while ((move == D_82199F20) || (move >= 4));
        D_82199F20 = move;

        if (sp24->unk_2A == 0) {
            sp1C->usedMove = D_82199DFC[D_82199F20];
        }
        sp24->unk_10 = three;

        if (sp20->unk_2A == 0) {
            sp18->usedMove = D_82199E0C[D_82199F20];
        }
        sp20->unk_10 = three;

        if ((sp24->unk_10 == three) && (sp20->unk_10 == three)) {
            func_82124EFC();
        }
    }

    if (cont->buttonPressed & 0x2000) {
        D_82199F10[0] = 0;
        D_82199F18[0] = 0;
        D_82199F10[1] = 0;
        D_82199F18[1] = 0;
    }

    if (cont->buttonPressed & 0x8000) {
        sBattleScene.scene->unk_40 = three;
    }
}

/*
 * func_8210E6D0
 *
 * Calls Battle_InitPokemonRuntimeState(arg0).  The two extra arguments are
 * accepted but not used; the retail code stores them to the stack, which is
 * why the signature declares them.
 */
void func_8210E6D0(ActivePokemon* arg0, s32 arg1, s32 arg2) {
    Battle_InitPokemonRuntimeState(arg0);
}

/*
 * func_8210E6F4
 *
 * Resets the battle-scene state for both sides:
 *   - runs func_8210E6D0 on the active-Pokemon pointers stored at D_82199DE0
 *     and D_82199DE4, passing (0, 1) for the first and (1, 0) for the second
 *     (func_8210E6D0 ignores those two arguments);
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

void func_8210E6F4(void) {
    func_8210E6D0(*(ActivePokemon**)&D_82199DE0, 0, 1);
    func_8210E6D0(D_82199DE4, 1, 0);
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
void func_82124EFC(void);
extern u16 D_82199F24;
extern u16 D_82199F50;

void func_8210E790(void) {
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
    if ((state0->unk_10 == 3) && (state1->unk_10 == 3)) {
        if (state0->unk_04 == 2) {
            func_8210CD58((s8*)sActivePokemon[0]);
        } else {
            func_8210C82C(sActivePokemon[0]);
        }
        if (state1->unk_04 == 2) {
            func_8210CD58((s8*)sActivePokemon[1]);
        } else {
            func_8210C82C(sActivePokemon[1]);
        }
        if ((state0->unk_04 == 2) || (state1->unk_04 == 2)) {
            func_82125224();
            return;
        }
        func_82124EFC();
    }
}

void func_8210E504(void);
void func_8210E790(void);

void func_8210E924(void) {
    ActivePokemonState* state0 = &sActivePokemon[0]->state;
    ActivePokemonState* state1 = &sActivePokemon[1]->state;

    if (state0->unk_2A != 1) {
        state0->unk_2A = 0;
    }
    if (state1->unk_2A != 1) {
        state1->unk_2A = 0;
    }
    switch (sBattleScene.scene->unk_1C) {
        case 1:
            func_8210E790();
            break;
        case 5:
            func_8210E504();
            break;
    }
    func_8210C6B0();
}
