/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_359F90.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gb_data.h"
#include "text_system.h"
#include "matrix.h"
#include "moves.h"
#include "fragments/fragment012_17ED00/battle_engine_313D60_types.h"
extern u8 sBattleMoveFailed;
extern u8 sBattleCritFlag;
extern u8 D_82199F4E;
extern u16 sBattleDamage;
extern s32 pad_D_843C4DD0;
extern s32 pad_D_843C4DD4;
extern s32 pad_D_843C4DD8;
extern s32 pad_D_843C4DDC;
extern s32 pad_D_843C4DE0;
extern s32 pad_D_843C4DE4;
extern s32 pad_D_843C4DE8;
extern s32 sTypeEffectiveness;
extern s32 pad_D_843C4DF0[21];
extern u8 sConfused;
extern u8 sStatCanBeChangedFurther;
extern s32 pad_D_843C4E48[252];
extern BattleMonRuntime* sBattleUser;
extern BattleMonRuntime* sBattleTarget;
extern BattleMonRuntime D_8219A3C8[2];
extern StatStageMultiplier gStatStageMultipliers[];
extern u8 sTypeEffects[];
extern u8 sHighCritMoves[];
#define PRINTF(x) ((void)(x))

#include "m2c_macros.h"

s32 ActivePokemon_GetNickname(ActivePokemon*);

void BattleMessage_Format(s32, s32, s32, ...);
extern s32 D_8219A520;

void ComputeAllPokemonStats(BattleMon* arg0);
void func_82110FB0(void);
void func_82110FB8(void);
void Battle_LoadMoveCache(void);
s32 Battle_Effect_Metronome(void);
void Battle_ApplyPoisonOrBurnDamage(void);
void func_82111870(void);

u8 Battle_Random(void);
void ComputePokemonStat(s32 arg0, BattleMon* arg1);
void Battle_RefundSelectedMovePp(void);

/**
 * Invoke the stored-stat calculator for selectors 0 through 4, preserving its original range.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ComputeAllPokemonStats(BattleMon* arg0) {
    ComputePokemonStat(0, arg0);
    ComputePokemonStat(1, arg0);
    ComputePokemonStat(2, arg0);
    ComputePokemonStat(3, arg0);
    ComputePokemonStat(4, arg0);
}

extern u16 D_82199F54;
extern u16 D_82199F58;
extern u16 D_82199F56;
extern u16 D_82199F52;
extern u16 D_843C4DCC;
/**
 * Select damage power, offensive/defensive stats and level, including screens and critical hits.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle and a Pound
 * turn.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void InitBattleParameters(void) {
    sBattleDamage = 0;
    D_82199F52 = sBattleUser->moveCache.power;
    if (D_82199F52) {
        if (sBattleUser->moveCache.type < 0x14) {
            D_82199F56 = sBattleTarget->modifiedDefense;
            if (sBattleTarget->uniqueStatusFlags & 4) {
                D_82199F56 *= 2;
            }

            if (sBattleCritFlag != 0) {
                D_82199F56 = sBattleTarget->unmodifiedDefense;
                D_82199F54 = sBattleUser->unmodifiedAttack;
            } else {
                D_82199F54 = sBattleUser->modifiedAttack;
            }
        } else {
            D_82199F56 = sBattleTarget->modifiedSpecial;
            if (sBattleTarget->uniqueStatusFlags & 2) {
                D_82199F56 *= 2;
            }

            if (sBattleCritFlag != 0) {
                D_82199F56 = sBattleTarget->unmodifiedSpecial;
                D_82199F54 = sBattleUser->unmodifiedSpecial;
            } else {
                D_82199F54 = sBattleUser->modifiedSpecial;
            }
        }

        if (D_82199F54 & 0xFF00) {
            if (D_82199F56 & 0xFF00) {
                D_82199F54 >>= 2;
                D_82199F56 >>= 2;
                if (D_82199F54 == 0) {
                    D_82199F54 = 1;
                }
            }
        }

        D_82199F58 = sBattleUser->unk_26;
        if (sBattleCritFlag != 0) {
            D_82199F58 *= 2;
        }
    }
}

extern u16 D_82199F52;
extern u16 D_82199F56;
extern u16 D_82199F58;
extern u16 D_82199F54;
extern u16 D_82199F58;
/**
 * Calculate base damage, halving defense for boom moves and delegating OHKO success.
 * Seen in play (2026-11-12): for Nidorino's Poison Sting (level 20, Attack 43, power 15) against
 * Pinsir (Defense 62) it set sBattleDamage to 4, which is the Gen 1 base damage
 * ((20*2/5+2)*15*43/62)/50+2.
 */
s32 Battle_CalcDamage(void) {
    s32 temp_v0 = sBattleUser->moveCache.effect;

    if (temp_v0 == 7) {
        D_82199F56 >>= 1;
        if (D_82199F56 == 0) {
            D_82199F56 = 1;
        }
    }

    if ((temp_v0 != 0x1D) && (temp_v0 != 0x1E)) {
        if (temp_v0 == 0x26) {
            return Battle_CheckMoveSuccess();
        }

        if (D_82199F52 == 0) {
            return 0;
        }
    }

    sBattleDamage += (((((D_82199F58 * 2) / 5) + 2) * D_82199F52 * D_82199F54) / D_82199F56) / 50;
    if (sBattleDamage > 0x3E4) {
        sBattleDamage = 0x3E4;
    }
    sBattleDamage += 2;

    return 1;
}

extern s32 D_8218C7B0;
extern s32 D_8218C7B4;
void ActivePokemon_SetStateFlags(ActivePokemon*, s32);
/**
 * Subtract damage from Substitute or target HP and update the associated continuation state.
 * Seen in play (2026-11-12): took Pinsir from 75 to 65 HP with sBattleDamage 10.
 */
void Battle_ApplyDamage(void) {
    BattleMonRuntime* target = sBattleTarget;

    if (target->volatileStatusFlags & 0x10) {
        if (sBattleScene.scene->moveEffectKind == 0x14) {
            BattleMessage_Format(D_8219A520 + 0x208, 0x2B, D_8218C7B0, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
            if (sBattleTarget->substituteHp < sBattleDamage) {
                sBattleTarget->volatileStatusFlags &= 0xFFEF;
                BattleMessage_Format(D_8219A520 + 0x208, 0x2C, D_8218C7B4, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
                sBattleUser->moveCache.effect = 0;
                ActivePokemon_SetStateFlags(sActivePokemon[sBattleScene.scene->actingSide], 0x1000);
            } else {
                sBattleTarget->substituteHp -= sBattleDamage;
            }
        } else {
            BattleMessage_Format(D_8219A520 + 0x208, 0x2B, D_8218C7B0, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
            if (sBattleTarget->substituteHp < sBattleDamage) {
                sBattleTarget->volatileStatusFlags &= 0xFFEF;
                BattleMessage_Format(D_8219A520 + 0x208, 0x2C, D_8218C7B4, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
                sBattleUser->moveCache.effect = 0;
                ActivePokemon_SetStateFlags(sActivePokemon[!sBattleScene.scene->actingSide], 0x1000);
            } else {
                sBattleTarget->substituteHp -= sBattleDamage;
            }
        }
    } else {
        if (sBattleDamage < target->hp) {
            target->hp -= sBattleDamage;
        } else {
            sBattleDamage = target->hp;
            target->hp = 0;
        }
    }
}

extern u8 D_8218ABF0[];
extern u8 D_8218ABF4[];
extern u8 D_8218ABFC[];
extern u8 D_8218AC04[];
extern s32 D_8218C754;
extern s32 D_8218C758;
extern s32 D_8218C75C;
extern s32 D_8218C760;
extern s32 D_8218C764;
s32 func_8210FA2C(s32, u8*, s32);
s32 ActivePokemon_GetMoveName(ActivePokemon*);

/**
 * Queues the "<nickname> used <move>" message, picking one of the five Gen 1 endings by move set;
 * Metronome and Mirror Move use a second message slot.
 */
void BattleMessage_PrintUsedMove(void) {
    BattleMonRuntime* runtime = &sActivePokemon[sBattleScene.scene->actingSide]->state.runtime;
    s32 type;

    runtime->lastMove = sBattleUser->moveCache.lastMove;
    if (func_8210FA2C(runtime->moveCache.lastMove, D_8218ABF0, 2) != 0) {
        type = 0;
    } else if (func_8210FA2C(runtime->moveCache.lastMove, D_8218ABF4, 5) != 0) {
        type = 1;
    } else if (func_8210FA2C(runtime->moveCache.lastMove, D_8218ABFC, 5) != 0) {
        type = 2;
    } else if (func_8210FA2C(runtime->moveCache.lastMove, D_8218AC04, 0x2E) != 0) {
        type = 3;
    } else {
        type = 4;
    }
    if (sBattleUser->moveCache.lastMove == 0x76 || sBattleUser->moveCache.lastMove == 0x77) {
        switch (type) {
            case 0:
                BattleMessage_Format(D_8219A520 + 0x388, 0x14, D_8218C754, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
            case 1:
                BattleMessage_Format(D_8219A520 + 0x388, 0x15, D_8218C758, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
            case 2:
                BattleMessage_Format(D_8219A520 + 0x388, 0x16, D_8218C75C, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
            case 3:
                BattleMessage_Format(D_8219A520 + 0x388, 0x17, D_8218C760, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
            case 4:
                BattleMessage_Format(D_8219A520 + 0x388, 0x18, D_8218C764, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
        }
    } else {
        switch (type) {
            case 0:
                BattleMessage_Format(D_8219A520 + 0xC8, 0x14, D_8218C754, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
            case 1:
                BattleMessage_Format(D_8219A520 + 0xC8, 0x15, D_8218C758, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
            case 2:
                BattleMessage_Format(D_8219A520 + 0xC8, 0x16, D_8218C75C, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
            case 3:
                BattleMessage_Format(D_8219A520 + 0xC8, 0x17, D_8218C760, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
            case 4:
                BattleMessage_Format(D_8219A520 + 0xC8, 0x18, D_8218C764, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]),
                              ActivePokemon_GetMoveName(sActivePokemon[sBattleScene.scene->actingSide]));
                break;
        }
    }
}

/**
 * Spend PP unless the active continuation suppresses it; update stored PP outside Transform.
 * Seen in play (2026-11-12): 1P's Poison Sting went from 35 to 34 PP across this call.
 */
void Battle_DecrementPP(s32 arg0) {
    BattleMonRuntime* temp_v0;
    ActivePokemonState* temp_a1;
    BattleMon* temp_a2;

    temp_v0 = &sActivePokemon[arg0]->state.runtime;
    temp_a1 = &sActivePokemon[arg0]->state;
    temp_a2 = &sActivePokemon[arg0]->teamRoster->pokemonPicked[temp_a1->rosterIndex];

    if ((temp_v0->usedMove != 0xA5) && !(temp_v0->immobilizedReason & 7) && !(temp_v0->volatileStatusFlags & 0x40)) {
        temp_v0->pp[temp_a1->selectedMoveIndex]--;
        if (!(temp_v0->uniqueStatusFlags & 8)) {
            temp_a2->pp[temp_a1->selectedMoveIndex] -= 1;
        }
    }
}

extern s8 *D_8219A3C0;
extern s8 *D_8219A3C4;
extern u8 D_8218AC34[][2];
/**
 * Gen 1 CalcHitChance: scales the move's accuracy by the user's accuracy stage and the target's
 * evasion stage, clamped to 1-255.
 */
void Battle_CalcHitChance(void) {

    s32 idx = ((u8*)D_8219A3C0)[0x60];
    s32 i;
    s32 v;

    i = ((u8*)D_8219A3C4)[0x61];
    i = 14 - i;
    v = ((u8*)D_8219A3C0)[0x48] * D_8218AC34[idx - 1][0] / D_8218AC34[idx - 1][1];
    if (v == 0) {
        v = 1;
    }
    v = v * D_8218AC34[i - 1][0] / D_8218AC34[i - 1][1];
    if (v == 0) {
        v = 1;
    }
    if (v >= 0x100) {
        v = 0xFF;
    }
    ((u8*)D_8219A3C0)[0x48] = v;
}

extern s8 D_82199F31;
extern s16 D_82199F50;
extern s8 *D_8219A3C0;
extern s8 *D_8219A3C4;
extern s8 *D_8219A5A0;

/**
 * Marks the move as missed: clears the damage, sets the missed flag and clears the user's
 * thrashing bit (0x20 of byte 0x4C).
 */
void Battle_MoveMissed(void) {
    s32 temp_v0;

    D_82199F50 = 0;
    temp_v0 = M2C_FIELD(D_8219A5A0, s32 *, 0x1C);
    if ((temp_v0 == 5) || (temp_v0 == 9) || (temp_v0 == 6) || (temp_v0 == 0xA)) {
        if (M2C_FIELD(D_8219A3C4, u8 *, 0x4C) & 0x40) {
            D_82199F31 = 1;
        } else {
            D_82199F31 = 0;
        }
    } else {
        D_82199F31 = 1;
    }
    M2C_FIELD(D_8219A3C0, u8 *, 0x4C) = (u8) (M2C_FIELD(D_8219A3C0, u8 *, 0x4C) & 0xFFDF);
}

void Battle_MoveMissed(void);
u8 Battle_Random(void);
/**
 * Gen 1 MoveHitTest: Dream Eater on a target that isn't asleep, Swift, moves into Fly or Dig,
 * Substitute, Mist and the accuracy roll each end in Battle_MoveMissed.
 */
void Battle_MoveHitTest(void) {
    s8* p = D_8219A3C0;
    u8 effect = M2C_FIELD(p, u8*, 0x45);

    if ((effect == 8) && !(M2C_FIELD(D_8219A3C4, u8*, 0x15) & 7)) {
        Battle_MoveMissed();
        return;
    }
    if (M2C_FIELD(D_8219A3C4, u8*, 0x4D) & 0x10) {
        if (effect == 0x11) {
            return;
        }
        if ((effect == 3) || (effect == 8)) {
            Battle_MoveMissed();
            return;
        }
    }
    if (M2C_FIELD(D_8219A3C4, u8*, 0x4C) & 0x40) {
        Battle_MoveMissed();
        return;
    }
    if ((((effect >= 0x12) && (effect < 0x1A)) || ((effect >= 0x3A) && (effect < 0x42))) && (M2C_FIELD(D_8219A3C4, u8*, 0x4D) & 2)) {
        Battle_MoveMissed();
        return;
    }
    if (M2C_FIELD(p, u8*, 0x4D) & 1) {
        return;
    }
    Battle_CalcHitChance();
    if (Battle_Random() >= M2C_FIELD(D_8219A3C0, u8*, 0x48)) {
        Battle_MoveMissed();
    }
}

/**
 * Copies the runtime's pending status condition into the party Pokemon.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle and a Pound
 * turn.
 * @unverified Name and comment guessed from the code.
 */
void ActivePokemon_CommitPendingStatus(ActivePokemon* arg0) {
    BattleMon* ptr = &arg0->teamRoster->pokemonPicked[arg0->state.rosterIndex];

    ptr->statusCondition = arg0->state.runtime.pendingStatusCondition;
}

/**
 * Quarter modified Speed when paralyzed, retaining a minimum of one.
 * Seen in play (2026-11-12): after 1P's Thunder Wave paralysed COM's Pinsir (status byte 0x40),
 * it cut Pinsir's modified Speed from 50 to 12; an earlier call with status 0 left it at 50.
 */
void ApplyParalysisSpeedCut(ActivePokemon* arg0) {
    BattleMonRuntime* temp_v0 = &arg0->state.runtime;

    if (arg0->state.runtime.pendingStatusCondition & 0x40) {
        temp_v0->speed >>= 2;
        if (temp_v0->speed == 0) {
            temp_v0->speed = 1;
        }
    }
}

/**
 * Halve modified Attack when burned, retaining a minimum of one.
 * Seen in play (2026-11-12): with COM's Pinsir burned (status byte 0x10) it cut Pinsir's modified
 * Attack from 71 to 35.
 */
void ApplyBurnAttackCut(ActivePokemon* arg0) {
    BattleMonRuntime* temp_v0 = &arg0->state.runtime;

    if (arg0->state.runtime.pendingStatusCondition & 0x10) {
        temp_v0->modifiedAttack >>= 1;
        if (temp_v0->modifiedAttack == 0) {
            temp_v0->modifiedAttack = 1;
        }
    }
}

void Battle_CheckMovesetLegality(ActivePokemon*);
void func_80041940(s32, s32, s32);

/**
 * Populate runtime species, HP, types, moves, stats and neutral stages from the selected roster.
 * Seen in play (2026-11-12): filled Onix's runtime state on the switch-in; the HUD then showed
 * イワワ L20 ふつう 49/ 49.
 */
void Battle_InitPokemonRuntimeState(ActivePokemon* arg0) {
    ActivePokemonState* sp28;
    BattleMonRuntime* sp24;
    BattleMon* sp34;
    s32 i;
    s32 j;

    sp28 = &arg0->state;
    sp24 = &arg0->state.runtime;
    sp34 = &arg0->sessionTeams->teamMember[sp28->replacementState]->pokemonPicked[sp28->rosterIndex];

    sp24->unk_14 = sp28->rosterIndex;
    sp24->id = sp34->species.id;
    sp24->hp = sp34->hp;
    sp24->pendingStatusCondition = sp34->statusCondition;
    sp24->roster[6] = sp34->type1;
    sp24->roster[7] = sp34->type2;
    sp24->roster[8] = sp34->unk_08;

    sp24->moves[0] = sp34->moves[0];
    sp24->moves[1] = sp34->moves[1];
    sp24->moves[2] = sp34->moves[2];
    sp24->moves[3] = sp34->moves[3];
    sp24->unk_24 = sp34->unk_1E;

    sp24->pp[0] = sp34->pp[0];
    sp24->pp[1] = sp34->pp[1];
    sp24->pp[2] = sp34->pp[2];
    sp24->pp[3] = sp34->pp[3];

    if ((sp34->moves[0] == 0) || (sp34->moves[0] >= 0xA6)) {
        sp24->pp[0] = 0;
    }

    if ((sp34->moves[1] == 0) || (sp34->moves[1] >= 0xA6)) {
        sp24->pp[1] = 0;
    }

    if ((sp34->moves[2] == 0) || (sp34->moves[2] >= 0xA6)) {
        sp24->pp[2] = 0;
    }

    if ((sp34->moves[3] == 0) || (sp34->moves[3] >= 0xA6)) {
        sp24->pp[3] = 0;
    }

    for (i = 0; i < 4; i++) {
        if (sp34->moves[i] == 0) {
            for (j = i; j < 4; j++) {
                sp24->pp[j] = 0;
                sp24->moves[j] = sp34->moves[j] = 0;
            }
            break;
        }
    }

    sp24->unk_26 = sp34->level;
    sp24->maxHp = sp34->maxHp;
    sp24->modifiedAttack = sp34->attack;
    sp24->modifiedDefense = sp34->defense;
    sp24->speed = sp34->speed;
    sp24->modifiedSpecial = sp34->special;

    ApplyParalysisSpeedCut(arg0);
    ApplyBurnAttackCut(arg0);

    sp24->unk_36 = gBaseStats[sp24->id].baseHP;
    sp24->unmodifiedAttack = sp34->attack;
    sp24->unmodifiedDefense = sp34->defense;
    sp24->unmodifiedSpeed = sp34->speed;
    sp24->unmodifiedSpecial = sp34->special;

    // clang-format off
    for (i = 0; i < 8; i++) { sp24->unk_5C[i] = 7; }
    // clang-format on

    Battle_CheckMovesetLegality(arg0);
    func_80041940(BattleScene_GetParticipantSideIndex(arg0), sp34->hp, sp34->maxHp);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s32 func_82110EAC(s8 *arg0)
{
  int new_var; // FAKE: permuter temp
  if ((*((u16 *) (((s8 *) ((*((s32 *) (((s8 *) arg0) + 0x860))) + ((*((s32 *) (((s8 *) arg0) + 0x7A4))) * 0x50))) + (new_var = -0x32)))) != 0) // FAKE: decomp slop, raw pointer casts stand in for struct fields
  {
    return 1;
  }
  return 0;
}

extern u8 D_82199F6A;
void func_82110EE4(void) {
    if (D_82199F6A & 1) {
        D_8219A3C8[0].modifiedAttack += D_8219A3C8[0].modifiedAttack >> 3;
        if (D_8219A3C8[0].modifiedAttack >= 0x3E8) {
            D_8219A3C8[0].modifiedAttack = 0x3E7;
        }
    }
    if (D_82199F6A & 2) {
        D_8219A3C8[0].modifiedDefense += D_8219A3C8[0].modifiedDefense >> 3;
        if (D_8219A3C8[0].modifiedDefense >= 0x3E8) {
            D_8219A3C8[0].modifiedDefense = 0x3E7;
        }
    }
    if (D_82199F6A & 4) {
        D_8219A3C8[0].speed += D_8219A3C8[0].speed >> 3;
        if (D_8219A3C8[0].speed >= 0x3E8) {
            D_8219A3C8[0].speed = 0x3E7;
        }
    }
    if (D_82199F6A & 8) {
        D_8219A3C8[0].modifiedSpecial += D_8219A3C8[0].modifiedSpecial >> 3;
        if (D_8219A3C8[0].modifiedSpecial >= 0x3E8) {
            D_8219A3C8[0].modifiedSpecial = 0x3E7;
        }
    }
}

void func_82110FB0(void) {
}

void func_82110FB8(void) {
}

/**
 * Load all six cached move-data bytes for usedMove; no animation is executed here.
 * Seen in play (2026-11-12): for 1P's Poison Sting it filled the cache with 28 02 0F 03 FF 23:
 * move 40, effect 2 (may poison), power 15, type 3 (Poison), accuracy 255, 35 PP.
 */
void Battle_LoadMoveCache(void) {
    sBattleUser->moveCache.lastMove = gMoveData[sBattleUser->usedMove - 1].moveId;
    sBattleUser->moveCache.effect = gMoveData[sBattleUser->usedMove - 1].effect;
    sBattleUser->moveCache.power = gMoveData[sBattleUser->usedMove - 1].power;
    sBattleUser->moveCache.type = gMoveData[sBattleUser->usedMove - 1].type;
    sBattleUser->moveCache.accuracy = gMoveData[sBattleUser->usedMove - 1].accuracy;
    sBattleUser->moveCache.pp = gMoveData[sBattleUser->usedMove - 1].pp;
}

extern s32 D_8218C780;
/**
 * Gen 1 HandleBuildingRage: when the target is using Rage and its Attack stage isn't maxed,
 * queues the rage message and raises its Attack through BattleEffect_ApplyStatBoost.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a Pound turn.
 * @unverified Name and comment from the code (matches the Gen 1 engine).
 */
void Battle_HandleBuildingRage(void) {
    BattleMonRuntime* sp1C;

    if ((sBattleTarget->volatileStatusFlags & 0x40) && ((sBattleTarget->unk_5C[0]) != 0xD)) {
        sp1C = sBattleUser;

        sBattleUser = sBattleTarget;
        sBattleUser->moveCache.lastMove = 0;
        sBattleUser->moveCache.effect = 10;

        BattleMessage_Format(D_8219A520 + 0x348, 0x1F, D_8218C780, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
        BattleEffect_ApplyStatBoost();

        sBattleUser->moveCache.lastMove = RAGE;
        sBattleUser->moveCache.effect = 0;

        sBattleUser = sp1C;
    }
}

extern u8 D_843C4DB3;
extern u8 D_82199F3F;

extern s32 D_8218C7A8;
extern s32 D_8218C7AC;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
/**
 * Gen 1 DisplayEffectiveness: queues the super effective message when the type multiplier is
 * above 10, or the not very effective message when it is below 10.
 * In play Ember on Pinsir (Fire on Bug) showed 「こうかは ばつぐんだ！」.
 */
void Battle_DisplayEffectiveness(void) {
    sTypeEffectiveness = D_82199F3F & 0x7F;
    if (sTypeEffectiveness >= 0xB) {
        BattleMessage_Format(D_8219A520 + 0x88, 0x29, D_8218C7A8);
    } else if (sTypeEffectiveness < 0xA) {
        BattleMessage_Format(D_8219A520 + 0x88, 0x2A, D_8218C7AC);
    }
}

extern s32 D_8218C778;
extern s32 D_8218C77C;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
/**
 * Gen 1 PrintCriticalOHKOText: queues the critical hit (sBattleCritFlag 1) or one-hit KO (2)
 * message, sets hitReactionKind 2 and stores the flag on the target.
 * In play, with sBattleCritFlag set to 1 on entry, Ember showed 「きゅうしょに あたった！」.
 */
void Battle_PrintCriticalOHKOText(void) {
    BattleMonRuntime* sp1C = &sActivePokemon[!sBattleScene.scene->actingSide]->state.runtime;

    switch (sBattleCritFlag) {
        case 1:
            BattleMessage_Format(D_8219A520 + 0x148, 0x1D, D_8218C778);
            sBattleScene.scene->hitReactionKind = 2;
            break;
        case 2:
            BattleMessage_Format(D_8219A520 + 0x148, 0x1E, D_8218C77C);
            sBattleScene.scene->hitReactionKind = 2;
            break;
    }
    sp1C->unk_5B = sBattleCritFlag;
    sBattleCritFlag = 0;
}

/**
 * Gen 1 ApplyAttackToEnemyPokemon: sets the fixed damage of OHKO moves, Super Fang (half the
 * target's HP), Seismic Toss and Night Shade (user level), Sonic Boom (20), Dragon Rage (40) and
 * Psywave (random 1 to 1.5x level), then applies the damage. Moves with no power and no special
 * damage do nothing.
 * In play Sonic Boom took Pinsir from 75 to 55 HP, the fixed 20.
 */
void Battle_ApplyAttackToTarget(void) {
    s32 n;

    switch (((u8*)D_8219A3C0)[0x45]) {
        case 0x26:
            break;
        case 0x28:
            D_82199F50 = M2C_FIELD(D_8219A3C4, u16*, 0xC) / 2;
            if ((u16)D_82199F50 == 0) {
                D_82199F50 = 1;
            }
            break;
        case 0x29:
            switch (((u8*)D_8219A3C0)[0x44]) {
                case 0x45:
                case 0x65:
                    n = ((u8*)D_8219A3C0)[0x26];
                    break;
                case 0x31:
                    n = 0x14;
                    break;
                case 0x52:
                    n = 0x28;
                    break;
                default:
                    {
                        s32 r;
                        n = ((u8*)D_8219A3C0)[0x26];
                        n = (n >> 1) + n;
                        do {
                            do {
                                r = Battle_Random();
                            } while (r == 0);
                        } while (r >= n);
                        n = r;
                    }
                    break;
            }
            D_82199F50 = n;
            break;
        default:
            if (((u8*)D_8219A3C0)[0x46] == 0) {
                return;
            }
            break;
    }
    if ((u16)D_82199F50 != 0) {
        Battle_ApplyDamage();
    }
}

extern u8 D_82199F3F;
extern s32 D_8218C768;
extern s32 D_8218C76C;
extern s32 D_8218C770;
extern s32 D_8218C774;
/**
 * Gen 1 PrintMoveFailureText: queues the doesn't affect / missed / failed message for a move that
 * failed. A Jump Kick or Hi Jump Kick miss (effect 0x2D) then deals the user crash damage
 * (moveEffectKind 0x10): sBattleDamage / 8, at least 1. sBattleDamage is 0 when this runs, so the
 * crash is always 1 HP, as on the Game Boy carts.
 * In play a forced Jump Kick miss ran it: 「しかし ニドニドの こうげきは はずれた！」 then the crash text.
 * Seen in play (2026-11-13) (Metronome pinned to Hi Jump Kick; Zero has no Hitmonlee, so Metronome
 * is the only legal way to use it): a forced miss showed 「しかし イワイワの こうげきは はずれた！」
 * then 「いきおい あまって イワイワは じめんに ぶつかった！」, Onix 49 → 48 HP. Against a target typed
 * Ghost/Poison it showed 「カイのすけには こうかが ないみたいだ」 and the same crash, 49 → 48 HP.
 * sBattleDamage read 0 at entry both times.
 */
void Battle_PrintMoveFailureText(void) {
    BattleMonRuntime* sp1C;

    if (D_82199F3F & 0x7F) {
        if (sBattleCritFlag == 0xFF) {
            BattleMessage_Format(D_8219A520 + 0x88, 0x19, D_8218C768, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
        } else {
            BattleMessage_Format(D_8219A520 + 0x88, 0x1A, D_8218C76C, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
        }
    } else {
        BattleMessage_Format(D_8219A520 + 0x88, 0x1B, D_8218C770, ActivePokemon_GetNickname(sActivePokemon[!sBattleScene.scene->actingSide]));
    }

    sBattleCritFlag = 0;

    if (sBattleUser->moveCache.effect == 0x2D) {
        sBattleScene.scene->moveEffectKind = 0x10;
        sBattleDamage >>= 3;
        if (sBattleDamage == 0) {
            sBattleDamage++;
        }

        BattleMessage_Format(D_8219A520 + 0x208, 0x1C, D_8218C774, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));

        sp1C = sBattleUser;
        sBattleUser = sBattleTarget;
        sBattleTarget = sp1C;
        sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
        Battle_ApplyDamage();
        sBattleScene.scene->actingSide = !sBattleScene.scene->actingSide;
        sBattleTarget = sBattleUser;
        sBattleUser = sp1C;
    }
}

/**
 * Gives back one PP of the selected move, on both the battle copy (sBattleUser) and the roster
 * copy. Metronome calls it so that only the move it pulls costs PP. Was misnamed
 * Battle_IncrementMoveUsage.
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Named from the code; the sweep saw it run for Metronome but did not read the PP.
 */
void Battle_RefundSelectedMovePp(void) {
    ActivePokemonState* state;
    BattleMon* mon;

    mon = &sActivePokemon[sBattleScene.scene->actingSide]->teamRoster->pokemonPicked[sActivePokemon[sBattleScene.scene->actingSide]->state.rosterIndex];
    state = &sActivePokemon[sBattleScene.scene->actingSide]->state;

    sBattleUser->pp[state->selectedMoveIndex]++;
    mon->pp[state->selectedMoveIndex]++;
}

/**
 * Refund the selected slot's PP, choose a non-Metronome move and load its cache.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Metronome.
 */
s32 Battle_Effect_Metronome(void) {
    s32 move_pulled;

    Battle_RefundSelectedMovePp();
    do {
        do {
            move_pulled = Battle_Random();
        } while (move_pulled == 0 || move_pulled >= 0xA5);
    } while (move_pulled == METRONOME);
    sBattleUser->usedMove = move_pulled;
    Battle_LoadMoveCache();
    return 1;
}

/**
 * Stage poison/burn HP loss, scaling it by the Toxic counter when active.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fire Punch, Poison Sting, Twineedle, Flamethrower, Poison Powder, Toxic, Smog, Fire Blast.
 */
void Battle_ApplyPoisonOrBurnDamage(void) {
    u16 var_a0;

    if (sBattleUser->pendingHp != 0xFFFF) {
        sBattleUser->hpAfterPoisonBurn = sBattleUser->pendingHp;
    } else {
        sBattleUser->hpAfterPoisonBurn = sBattleUser->hp;
    }

    var_a0 = (sBattleUser->maxHp >> 4) & 0xFFFF;
    if (var_a0 == 0) {
        var_a0++;
    }

    if (sBattleUser->uniqueStatusFlags & 1) {
        sBattleUser->toxicCounter++;
        var_a0 *= sBattleUser->toxicCounter;
    }

    if (sBattleUser->hpAfterPoisonBurn < var_a0) {
        sBattleUser->hpAfterPoisonBurn = 0;
    } else {
        sBattleUser->hpAfterPoisonBurn -= var_a0;
    }

    sBattleUser->unk_10 = sBattleUser->hpAfterPoisonBurn;
}

/**
 * Stage Leech Seed HP transfer, including the Toxic-counter multiplier and healing cap.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Leech Seed.
 */
void Battle_ApplyLeechSeedDamage(void) {
    s32 amount;
    s32 v;

    if (!(sBattleUser->pendingStatusCondition & 0x18)) {
        v = sBattleUser->pendingHp;
        if (v != 0xFFFF) {
            sBattleUser->unk_10 = v;
        } else {
            sBattleUser->unk_10 = sBattleUser->hp;
        }
    }
    v = (sBattleUser->maxHp >> 4) & 0xFFFF;
    amount = v;
    if (v == 0) {
        v = v + 1;
        amount = v & 0xFFFF;
    }
    if (sBattleUser->uniqueStatusFlags & 1) {
        sBattleUser->toxicCounter += 1;
        v = (u32)amount * sBattleUser->toxicCounter;
        amount = v & 0xFFFF;
    }
    v = sBattleUser->unk_10;
    if (v < amount) {
        sBattleUser->unk_10 = 0;
        amount = sBattleUser->unk_10;
    } else {
        sBattleUser->unk_10 = v - amount;
    }
    sBattleTarget->unk_10 = sBattleTarget->hp;
    sBattleTarget->unk_10 = sBattleTarget->unk_10 + amount;
    v = sBattleTarget->maxHp;
    if (v < sBattleTarget->unk_10) {
        sBattleTarget->unk_10 = v;
    }
}

void func_82111870(void) {
}

extern s32 D_8218C704;
extern s32 D_8218C708;
extern s32 D_8218C70C;

// Matches the ROM, but uses rodata data that is not placed in this file yet.
void Battle_ApplyLeechSeedDamage(void);
void func_82111870(void);

/**
 * Queue and stage poison/burn and Leech Seed effects after the action.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in a switch in battle and a Pound
 * turn.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Battle_ApplyResidualEffects(void) {
    if (sBattleTarget->hp == 0) {
        return 0;
    }

    if (sBattleUser->pendingStatusCondition & 0x18) {
        if (sBattleUser->pendingStatusCondition & 8) {
            BattleMessage_Format(D_8219A520 + 0x248, 0, D_8218C704, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
        } else {
            BattleMessage_Format(D_8219A520 + 0x248, 1, D_8218C708, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
        }
        Battle_ApplyPoisonOrBurnDamage();
        sBattleTarget->hpAfterPoisonBurn = sBattleTarget->hp;
    }

    if (sBattleUser->volatileStatusFlags & 0x80) {
        Battle_ApplyLeechSeedDamage();
        func_82111870();
        BattleMessage_Format(D_8219A520 + 0x288, 2, D_8218C70C, ActivePokemon_GetNickname(sActivePokemon[sBattleScene.scene->actingSide]));
    }

    if (sBattleUser->hp != 0) {
        return 0;
    }
    return 1;
}
