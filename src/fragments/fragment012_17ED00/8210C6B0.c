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

#ifdef NON_MATCHING
/* TODO: decompile func_8210C778; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210C778.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_8210C8A0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210C8A0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8210CA24; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210CA24.s")
#endif

void func_82134D60(void);
void func_8210CA24(s8*);
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
M2C_UNK func_8211F274();

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
    UNUSED s32 pad;

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

M2C_UNK func_8211F274();
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

#ifdef NON_MATCHING
/* TODO: decompile func_8210CDEC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210CDEC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8210CEE8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210CEE8.s")
#endif

s32 func_82107F88(s32);                             /* extern */
M2C_UNK func_8211F274();                            /* extern */
M2C_UNK func_8211F288(s32, s32, s32);               /* extern */
extern s32 D_8218C700;

void func_8210CFE4(s32 arg0) {
    func_8211F274();
    func_8211F288(arg0, D_8218C700, func_82107F88(arg0));
}

#ifdef NON_MATCHING
/* TODO: decompile func_8210D020; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210D020.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8210D1B0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210D1B0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8210D378; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210D378.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8210D4B4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210D4B4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8210D6BC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210D6BC.s")
#endif

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
    UNUSED s32 pad;
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

#ifdef NON_MATCHING
/* TODO: decompile func_8210DA30; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210DA30.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8210DAEC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210DAEC.s")
#endif

void BattleScene_CompleteCpuForcedAction(ActivePokemon* arg0, UNUSED ActivePokemon* arg1) {
    ActivePokemonState* ptr = &arg0->state;

    BattleScene_ApplyForcedActionDelay(arg0);
    ptr->unk_2A = 1;
    ptr->unk_04 = 1;
    ptr->unk_0C = ptr->unk_14;
    ptr->unk_10 = 3;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8210DCE4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210DCE4.s")
#endif

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
  s8 **new_var;
  s8 *temp_a1;
  int pad;
  temp_a1 = (s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x9CC)));
  temp_v1 = *((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x9CC));
  *((u8 *) (temp_a1 + 1)) = (u8) ((*((u8 *) (((s8 *) temp_v1) + 1))) | 1);
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x865)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x865))) | 1);
  new_var = (s8 **) (((s8 *) (&D_82199DE0)) + 4);
  ;
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x9CC)))) + 1)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x9CC)))) + 1))) | 1);
  *((u8 *) (((s8 *) (*new_var)) + 0x865)) = (u8) ((*((u8 *) (((s8 *) (*new_var)) + 0x865))) | 1);
}

extern s8 D_82199DE0;
void func_8210E36C(void)
{
  s8 *temp_a1;
  s8 *temp_v1;
  ;
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x9CC)))) + 1)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x9CC)))) + 1))) & 0xFFFE);
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x865)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 0)))) + 0x865))) & 0xFFFE);
  ;
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x9CC)))) + 1)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x9CC)))) + 1))) & 0xFFFE);
  *((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x865)) = (u8) ((*((u8 *) (((s8 *) (*((s8 **) (((s8 *) (&D_82199DE0)) + 4)))) + 0x865))) & 0xFFFE);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8210E3C0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210E3C0.s")
#endif

void func_8210E3C0(ActivePokemon*, ActivePokemon*);
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

#ifdef NON_MATCHING
/* TODO: decompile func_8210E504; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210E504.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_8210E790; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210E790.s")
#endif

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
