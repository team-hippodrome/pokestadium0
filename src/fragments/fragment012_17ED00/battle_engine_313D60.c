/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_313D60.c, src/fragments/battle_engine/battle_engine_359F90.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "geo_node.h"
#include "model_animation.h"
#include "text_system.h"
#include "audio_commands.h"
#include "matrix.h"
#include "memory.h"
#include "util.h"
extern unk_D_84390240 sBattleScene;
extern s32 pad_D_84390280;
extern s32 pad_D_84390290[4];

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

void func_8210F4E0(void);
s32 IsByteInArray(u8 lookup, u8* array, s32 array_length);
void func_8210FA74(void);
void Battle_SetActiveMoveFromSlotIndex(void);
s32 Battle_CheckMoveSuccess(void);
void ComputePokemonStat(s32 arg0, BattleMon* arg1);

void func_8210F4E0(void) {
}

extern s32 D_8219A520;
s32 BattleMessage_Format(s32, s32, s32, ...);
s32 ActivePokemon_GetNickname(ActivePokemon*);
extern s32 D_8218C788;
extern s32 D_8218C78C;
extern s32 D_8218C790;
extern s32 D_8218C794;
/**
 * Save the target's current HP and queue an HP-band message for the acting participant.
 * Seen in play (2026-11-13) in a Free Battle switch (1P switched to its second Pokémon) it ran when
 * C-Left picked the Pokémon to switch in.
 * Seen in play (2026-11-13) it also ran when COM sent out its next Pokémon (ゆけっ！ゲンのすけ) after its
 * first one fainted.
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void ShowDamageMessage(s32 attacker, s32 defender) {
    ActivePokemon** atk = &sActivePokemon[attacker];
    ActivePokemonState* state = &(*atk)->state;
    BattleMonRuntime* runtime = &sActivePokemon[defender]->state.runtime;
    s32 pct;

    if (runtime->hp == 0) {
        BattleMessage_Format(D_8219A520 + 0x88, 0x21, D_8218C788, ActivePokemon_GetNickname(*atk));
        return;
    }
    state->unk_28 = runtime->hp;
    pct = (runtime->hp * 0x19) / (runtime->maxHp >> 2);
    if (pct >= 0x46) {
        BattleMessage_Format(D_8219A520 + 0x88, 0x21, D_8218C788, ActivePokemon_GetNickname(*atk));
    } else if (pct >= 0x28) {
        BattleMessage_Format(D_8219A520 + 0x88, 0x22, D_8218C78C, ActivePokemon_GetNickname(*atk));
    } else if (pct >= 0xA) {
        BattleMessage_Format(D_8219A520 + 0x88, 0x23, D_8218C790, ActivePokemon_GetNickname(*atk));
    } else {
        BattleMessage_Format(D_8219A520 + 0x88, 0x24, D_8218C794, ActivePokemon_GetNickname(*atk));
    }
}

extern u8 D_82199F3F;
extern u8 D_82199F30;
/**
 * Clear the incoming participant's temporary effects and the opponent's trapping lock.
 * Seen in play (2026-11-12): ran on the same switch-in.
 */
void Battle_ResetTransientRuntimeState(s32 arg0, s32 arg1) {
    BattleMonRuntime* sp1C = &sActivePokemon[arg0]->state.runtime;
    BattleMonRuntime* sp18 = &sActivePokemon[arg1]->state.runtime;

    ShowDamageMessage(arg0, arg1);
    D_82199F4E = 0;
    D_82199F3F = 0;
    sp1C->moveCache.lastMove = 0;
    sp1C->lastMove = 0;
    sp18->lastMove = 0;
    sp1C->unk_4A = 0;
    sp1C->unk_4B = 0;
    sp1C->immobilizedReason = 0;
    sp1C->volatileStatusFlags = 0;
    sp1C->uniqueStatusFlags = 0;
    sp1C->disabledMoveState = 0;
    sp1C->disabledMove = 0;
    sp1C->scaleResize = 0;
    sp18->immobilizedReason &= ~0x20;
    D_82199F30 = 1;
}

s32 BattleMessage_Format(s32, s32, s32, ...);
extern s32 D_8219A520;
extern s32 D_8218C798;
extern s32 D_8218C79C;
extern s32 D_8218C7A0;
extern s32 D_8218C7A4;
extern char D_8219544C[];
/**
 * Formats the comment on the hit that just landed from the share of the target's max HP lost
 * (unk_28, the HP before the hit, minus hp, as a percentage): message 0x25 for 0%, 0x26 under 30%,
 * 0x27 under 70% and 0x28 for 70% or more. Adds message 0 when state.unk_2D is 0x10.
 * Was misnamed Battle_ResetEntityState.
 * @unverified Named from the code; not checked in play.
 */
void Battle_FormatDamageComment(ActivePokemon* active_pokemon) {
    ActivePokemonState* sp1C = &sActivePokemon[0]->state;
    ActivePokemonState* sp18 = &sActivePokemon[1]->state;
    BattleMonRuntime* temp_a1 = &sActivePokemon[0]->state.runtime;
    BattleMonRuntime* temp_a2 = &sActivePokemon[1]->state.runtime;
    s32 var_v0;

    if (active_pokemon == sActivePokemon[0]) {
        var_v0 = ((sp1C->unk_28 - temp_a2->hp) * 0x19) / (temp_a2->maxHp >> 2);
    } else {
        var_v0 = ((sp18->unk_28 - temp_a1->hp) * 0x19) / (temp_a1->maxHp >> 2);
    }

    if (var_v0 == 0) {
        BattleMessage_Format(D_8219A520 + 0x1C8, 0x25, D_8218C798);
    } else if (var_v0 < 0x1E) {
        BattleMessage_Format(D_8219A520 + 0x1C8, 0x26, D_8218C79C);
    } else if (var_v0 < 0x46) {
        BattleMessage_Format(D_8219A520 + 0x1C8, 0x27, D_8218C7A0);
    } else {
        BattleMessage_Format(D_8219A520 + 0x1C8, 0x28, D_8218C7A4);
    }

    if (active_pokemon->state.unk_2D == 0x10) {
        BattleMessage_Format(D_8219A520 + 0x1C8, 0, (s32)D_8219544C);
    }
}

u8 Battle_Random(void);                                /* extern */
extern u16 D_82199F50;

/**
 * Gen 1 RandomizeDamage: when the damage is at least 2, multiplies it by a random 217-255 and
 * divides by 255.
 */
void Battle_RandomizeDamage(void) {
    s32 temp_v0;

    if ((s32) D_82199F50 >= 2) {
        do {
            temp_v0 = Battle_Random();
        } while (temp_v0 < 0xD9);
        D_82199F50 = (u16) ((s32) (D_82199F50 * temp_v0) / 255);
    }
}

/**
 * Return which participant acts first using Quick Attack, Counter, Speed and a random tie break.
 * Seen in play (2026-11-12): returned 1 (COM first) with Pinsir at Speed 50 against Nidorino, and
 * Pinsir moved first; with Pinsir's Speed set to 1 it returned 0 and 1P moved first.
 */
u16 Battle_DetermineMoveOrder(ActivePokemon* pokemon, ActivePokemon* other_pokemon) {
    BattleMonRuntime* runtime = &pokemon->state.runtime;
    BattleMonRuntime* other_runtime = &other_pokemon->state.runtime;

    if (runtime->usedMove == QUICK_ATTACK) {
        if (other_runtime->usedMove != QUICK_ATTACK) {
            return 0;
        }
    } else if (other_runtime->usedMove == QUICK_ATTACK) {
        return 1;
    }

    if (runtime->usedMove == COUNTER) {
        if (other_runtime->usedMove != COUNTER) {
            return 1;
        }
    } else if (other_runtime->usedMove == COUNTER) {
        return 0;
    }

    if (other_runtime->speed < runtime->speed) {
        return 0;
    }

    if (runtime->speed < other_runtime->speed) {
        return 1;
    }

    if (Battle_Random() < 0x80) {
        return 0;
    }
    return 1;
}

/**
 * Test membership in a byte array of the supplied length.
 * Seen in play (2026-11-12): returned 0 for 0x28 (Poison Sting) in the two-byte list 0E 4A and in
 * the five-byte list 60 69 75 78 85.
 */
s32 IsByteInArray(u8 lookup, u8* array, s32 array_length) {
    while (array_length--) {
        if (lookup == *array) {
            return 1;
        }
        array++;
    }

    return 0;
}

void func_8210FA74(void) {
}

/**
 * Select a move in the first scratch runtime using the current scratch move-slot index.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Battle_SetActiveMoveFromSlotIndex(void) {
    D_8219A3C8[0].usedMove = D_8219A3C8[0].moves[D_82199F4E];
}

/**
 * Execute the cached effect and report whether it left the move-failed flag clear.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Guillotine, Horn Drill, Fissure.
 */
s32 Battle_CheckMoveSuccess(void) {
    BattleEffect_ExecuteMoveEffect();

    if (sBattleMoveFailed == 1) {
        return 0;
    }
    return 1;
}

/**
 * Calculate the requested stored stat from the selected base-stat/experience entries and DVs.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ComputePokemonStat(s32 arg0, BattleMon* arg1) {
    u16 i;
    u16 spC;
    u16 spA;
    u16 tmp;
    u16 sp6;
    u16 temp_a0;

    switch (arg0) {
        case 1:
            spA = gSpeciesData[arg1->level].baseHitPoints;
            spC = arg1->unk_14;
            break;

        case 2:
            spA = gSpeciesData[arg1->level].baseAttack;
            spC = arg1->unk_16;
            break;

        case 3:
            spA = gSpeciesData[arg1->level].baseDefense;
            spC = arg1->unk_18;
            break;

        case 4:
            spA = gSpeciesData[arg1->level].baseSpeed;
            spC = arg1->unk_1A;
            break;

        case 5:
            spA = gSpeciesData[arg1->level].baseSpecial;
            spC = arg1->unk_1C;
            break;
    }

    for (i = 1; i < 255; i++) {
        if (SQ(i) >= spC) {
            break;
        }
    }

    tmp = D_8219A3C8[0].unk_24;

    switch (arg0) {
        case 1:
            sp6 = ((tmp & 0x1000) >> 9) | ((tmp & 0x100) >> 6) | ((tmp & 0x10) >> 3) | (tmp & 1);
            break;

        case 2:
            sp6 = (tmp >> 0xC) & 0xF;
            break;

        case 3:
            sp6 = (tmp >> 8) & 0xF;
            break;

        case 4:
            sp6 = (tmp >> 4) & 0xF;
            break;

        case 5:
            sp6 = tmp & 0xF;
            break;
    }

    temp_a0 = ((((spA + sp6) * 2) + (i >> 2)) * arg1->level) / 100;
    if (arg0 == 1) {
        temp_a0 += arg1->level + 0xA;
    } else {
        temp_a0 += 5;
    }

    if (temp_a0 >= 0x3E8) {
        temp_a0 = 0x3E7;
    }

    switch (arg0) {
        case 1:
            arg1->maxHp = temp_a0;
            break;

        case 2:
            arg1->attack = temp_a0;
            break;

        case 3:
            arg1->defense = temp_a0;
            break;

        case 4:
            arg1->speed = temp_a0;
            break;

        case 5:
            arg1->special = temp_a0;
            break;
    }
}
