/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_313250.c, src/fragments/battle_engine/battle_engine_361050.c, src/fragments/battle_engine/battle_engine_move_animation.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "math.h"
#include "jpeg_stream.h"
#include "gb_data.h"
extern unk_D_843C5568 gBattleAI_ActivePokemon[2];
extern s32 pad_D_843C60A0;
extern u16 D_82199F50;
extern u16 D_82199F52;
extern u16 D_82199F54;
extern u16 D_82199F56;
extern u16 D_82199F58;
extern u8 D_82199F32;
extern unk_D_843C6148 D_8219A494;
#include "fragments/fragment012_17ED00/battle_engine_361050_types.h"

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "model_animation_events.h"
#include "model_renderer.h"
#include "pokemon_stats.h"
#include "text_system.h"
#include "gb_save.h"
#include "audio_commands.h"
#include "jpeg_stream.h"
#include "audio_fade.h"
#include "audio_stored_fade.h"
#include "audio_loop_point.h"
#include "cry.h"
#include "matrix.h"
#include "memory.h"
#include "moves.h"
#include "pokemon.h"
#include "status.h"
extern PokemonBattleCues sSide1BattleCues;
extern PokemonBattleCues sSide2BattleCues;
extern SpeciesModelTransform sSide1PresentationTransform;
extern SpeciesModelTransform sSide2PresentationTransform;
extern ActivePokemon* sActivePokemon[2];
extern ActivePokemon* sSide1ActivePokemon;
extern ActivePokemon* sSide2ActivePokemon;
extern MovePresentationCue* sCurrentAnimation;
extern ModelDimensions sPokemonModelDimensions[2];
extern SwayLayoutConfig sDefaultSwayLayout;
extern BattleSceneStateTickSlot sBattleSceneStateTickSlots[7];
extern s32 sBattleSceneStateTickSlotIndex;
extern PokemonBattleCues* sSideBattleCues[];
extern SpeciesModelTransform* sSidePresentationTransform[];
extern TagTeamPartners* sPlayerTagTeam[];
extern u8 sPokemonWithAlternateSleepIdle[];
extern u8 sPokemonWithAlternateSleepHitReactions[];
extern u8 sPokemonWithNewHmInYellow[];
extern u8 sCharizardLearnsFlyInYellow[];
extern u8 sButterfreeLearnsFlashInYellow[];
extern u8 sVenonatLearnsFlashInYellow[];
extern u8 sVenomothLearnsFlashInYellow[];
extern u8 sDiglettLearnsCutInYellow[];
extern u8 sDugtrioLearnsCutInYellow[];
extern u8 sKabutopsLearnsCutInYellow[];
extern u8 sMewtwoLearnsNothingNewInYellow[];
extern u8 sMewLearnsNothingNewInYellow[];
extern u8* sPokemonYellowHmAdditions[];
extern u8 sAerodactyl;
extern u8 sFearow;
extern u8 sFarfetchD;
extern u8 sDoduoEvoLine[];
extern char** sBattleMessagesTable;
extern char** sPokemonNameTable;
extern char** sMoveNameTable;
extern char** sStatusConditionNameTable;
extern char** sBattleControllerDisconnectedMessage;
#define PARTNER_PIKACHU_CUE_BANK 152
#define DIGLETT_OB1 (DIGLETT - 1)
#define DUGTRIO_OB1 (DUGTRIO - 1)
#define ELECTRODE_OB1 (ELECTRODE - 1)
#define SQUIRTLE_OB1 (SQUIRTLE - 1)
#define WARTORTLE_OB1 (WARTORTLE - 1)
#define BLASTOISE_OB1 (BLASTOISE - 1)
#define CLOYSTER_OB1  (CLOYSTER - 1)

#include "fragments/battle_engine/battle_engine.h"
#include "geo_node.h"
#include "model_animation.h"
#include "text_system.h"
#include "audio_commands.h"
#include "matrix.h"
#include "memory.h"
#include "util.h"
#include "m2c_macros.h"

u16 BattleAi_ApplyMoveEffectDamageOverride(BattleMonRuntime* arg0, BattleMonRuntime* arg1);
void BattleAi_ClampDamageRatio(void);
void BattleAi_PrepareDamageCalcState(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2);
s32 BattleScene_FindU16InByteArray(u16 lookup_value, u8* array, s32 array_length);
void BattleScene_IntroInitNop(void);

u16 BattleAi_ApplyMoveEffectDamageOverride(BattleMonRuntime* arg0, BattleMonRuntime* arg1) {
    s32 var_v0;

    switch (D_8219A494.unk_01) {
        case 38:
            break;

        case 40:
            D_82199F50 = arg0->displayHp / 2;
            if (D_82199F50 == 0) {
                D_82199F50 = 1;
            }
            break;

        case 41:
            switch (D_8219A494.unk_00) {
                case 0x45:
                case 0x65:
                    var_v0 = arg0->unk_26;
                    break;

                case 0x31:
                    var_v0 = 0x14;
                    break;

                case 0x52:
                    var_v0 = 0x28;
                    break;

                default:
                    var_v0 = arg0->unk_26;
                    var_v0 = (var_v0 >> 1) + (var_v0 >> 2);
            }

            D_82199F50 = var_v0;
            break;

        default:
            if (D_8219A494.unk_02 == 0) {
                return D_82199F50;
            }
            break;
    }

    return D_82199F50;
}

void BattleAi_ClampDamageRatio(void) {
    if (D_82199F50 >= 2) {
        D_82199F50 = (D_82199F50 * 0xFF) / 255;
    }
}

extern u8 D_8219A497;
typedef struct TypeMatchupZ {
    /* 0x00 */ u8 attackType;
    /* 0x01 */ u8 defendType;
    /* 0x02 */ u8 multiplier;
} TypeMatchupZ; // size = 0x3
extern TypeMatchupZ D_8218AC50[];

/**
 * Damage-estimate version of Battle_ApplyTypeEffectAndSTAB for any attacker and
 * defender (battle Pokemon records), working on D_82199F50.
 * @unverified Name and comment guessed from the code.
 */
void BattleCalc_ApplyTypeEffectAndStab(u8* attacker, u8* defender) {
    TypeMatchupZ* entry;
    u8 attType1 = attacker[0x1C];
    u8 attType2 = attacker[0x1D];
    u8 defType1 = defender[0x1C];
    u8 defType2 = defender[0x1D];
    u8 moveType = D_8219A497;

    if ((moveType == attType1) || (moveType == attType2)) {
        D_82199F50 += D_82199F50 >> 1;
    }
    for (entry = D_8218AC50; entry->attackType != 0xFF; entry++) {
        if ((entry->attackType == moveType) && ((entry->defendType == defType1) || (entry->defendType == defType2))) {
            D_82199F50 = (D_82199F50 * entry->multiplier) / 10;
        }
    }
}

void BattleAi_PrepareDamageCalcState(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2) {
    MoveData* temp_v0 = &gMoveData[arg2 - 1];

    D_8219A494.unk_00 = temp_v0->moveId;
    D_8219A494.unk_01 = temp_v0->effect;
    D_8219A494.unk_02 = temp_v0->power;
    D_8219A494.unk_03 = temp_v0->type;
    D_8219A494.unk_04 = temp_v0->accuracy;
    D_8219A494.unk_05 = temp_v0->pp;

    D_82199F50 = 0;
    D_82199F52 = D_8219A494.unk_02;
    if (D_82199F52) {
        if (D_8219A494.unk_03 < 0x14) {
            D_82199F56 = arg1->modifiedDefense;
            if (arg1->uniqueStatusFlags & 4) {
                D_82199F56 *= 2;
            }

            if (D_82199F32 != 0) {
                D_82199F56 = arg1->unmodifiedDefense;
                D_82199F54 = arg0->unmodifiedAttack;
            } else {
                D_82199F54 = arg0->modifiedAttack;
            }
        } else {
            D_82199F56 = arg1->modifiedSpecial;
            if (arg1->uniqueStatusFlags & 2) {
                D_82199F56 *= 2;
            }

            if (D_82199F32 != 0) {
                D_82199F56 = arg1->unmodifiedSpecial;
                D_82199F54 = arg0->unmodifiedSpecial;
            } else {
                D_82199F54 = arg0->modifiedSpecial;
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

        D_82199F58 = arg0->unk_26;
        if (D_82199F32 != 0) {
            D_82199F58 *= 2;
        }
    }
}

/**
 * Gen 1 base damage ((level * 2 / 5 + 2) * power * attack / defense) / 50 + 2,
 * capped at 997, added to D_82199F50.
 * @unverified Name and comment guessed from the code.
 */
void BattleCalc_AddBaseDamage(UNUSED u8* arg0, UNUSED u8* arg1) {
    u8 tmp = D_8219A494.unk_01;

    if (tmp == 7) {
        D_82199F56 >>= 1;
        if (D_82199F56 == 0) {
            D_82199F56 = 1;
        }
    }

    if (D_82199F56 == 0) {
        D_82199F56 = 1;
    }

    D_82199F50 += (((((D_82199F58 * 2) / 5) + 2) * D_82199F52 * D_82199F54) / D_82199F56) / 50;

    if (D_82199F50 >= 0x3E5) {
        D_82199F50 = 0x3E4;
    }

    D_82199F50 += 2;
}

extern u8 D_82199F32;
extern u8 D_82199F33;
void func_8210E9C0(u8*, u8*);
void func_8210EAC4();
void func_8210EC0C(u8*, u8*, u8);
void BattleCalc_AddBaseDamage(u8*, u8*);

/**
 * Runs the sequence func_8210EC0C, BattleCalc_AddBaseDamage, BattleCalc_ApplyTypeEffectAndStab,
 * func_8210EAC4 and func_8210E9C0 for the attacker/defender pair
 * (arg0, arg1). The flag D_82199F32 is saved into D_82199F33 and cleared
 * for the first four steps, and restored before the last one. arg2 is only
 * handed on to func_8210EC0C.
 * @unverified Name guessed from the code; comment kept.
 */
void BattleCalc_EstimateDamage(u8* arg0, u8* arg1, u8 arg2) {
    D_82199F33 = D_82199F32;
    D_82199F32 = 0;
    func_8210EC0C(arg0, arg1, arg2);
    BattleCalc_AddBaseDamage(arg0, arg1);
    BattleCalc_ApplyTypeEffectAndStab(arg0, arg1);
    func_8210EAC4();
    D_82199F32 = D_82199F33;
    func_8210E9C0(arg0, arg1);
}

/**
 * Returns the index of `lookup_value` in `array`, or -1 if absent.
 */
s32 BattleScene_FindU16InByteArray(u16 lookup_value, u8* array, s32 array_length) {
    s32 lookup_result = 0;

    while (array_length--) {
        if (lookup_value == *array) {
            return lookup_result;
        }
        array++;
        lookup_result++;
    }

    return -1;
}

typedef struct S0LearnRuntime {
    /* 0x00 */ char unk00[0x1F];
    /* 0x1F */ u8 moves[4];
    /* 0x23 */ char unk23[0x3];
    /* 0x26 */ u8 unk_26;
} S0LearnRuntime;
typedef struct S0LearnMon {
    /* 0x000 */ char unk000[0x7C6];
    /* 0x7C6 */ S0LearnRuntime runtime;
    /* 0x7ED */ char unk7ED[0x851 - 0x7ED];
    /* 0x851 */ u8 moveSlotIllegality[4];
} S0LearnMon;
typedef struct S0Learnset {
    /* 0x00 */ u8 unk_00[10];
    /* 0x0A */ u8 unk_0A[10];
} S0Learnset; // size = 0x14
extern S0Learnset D_8218CA60[];
extern S0Learnset D_8218D62C[];
extern u8 D_8218AD9C[];
extern u8* D_8218ADC8[];
u8 Move_GetIdFromTableIndex(s32);
/**
 * Clears a move slot's illegal flag when the species can have that move (start
 * moves, level-up moves or TM/HM).
 * @unverified Name and comment guessed from the code.
 */
void Battle_MarkLegalMovesForSpecies(S0LearnMon* pokemon, u16 pokemon_id) {
    s32 move_index;
    s32 i;
    s32 lookup;
    s32 tm_index;
    u8 tm_hm_flag;
    SpeciesData* species_data;
    S0LearnRuntime* pokemon_runtime;

    pokemon_runtime = &pokemon->runtime;

    for (move_index = 0; move_index < 4; move_index++) {
        if (pokemon_runtime->moves[move_index] != 0) {
            species_data = &gSpeciesData[pokemon_id];

            for (i = 0; i < ARRAY_COUNT(species_data->startingMoves); i++) {
                if ((species_data->startingMoves[i] != 0) && (species_data->startingMoves[i] == pokemon_runtime->moves[move_index])) {
                    pokemon->moveSlotIllegality[move_index] = 0;
                }
            }

            for (i = 0; i < 10; i++) {
                if ((D_8218CA60[pokemon_id].unk_00[i] != 0) && (pokemon_runtime->unk_26 >= D_8218CA60[pokemon_id].unk_00[i]) &&
                    (D_8218CA60[pokemon_id].unk_0A[i] == pokemon_runtime->moves[move_index])) {
                    pokemon->moveSlotIllegality[move_index] = 0;
                }
            }

            for (i = 0; i < 10; i++) {
                if ((D_8218D62C[pokemon_id].unk_00[i] != 0) && (pokemon_runtime->unk_26 >= D_8218D62C[pokemon_id].unk_00[i]) &&
                    (D_8218D62C[pokemon_id].unk_0A[i] == pokemon_runtime->moves[move_index])) {
                    pokemon->moveSlotIllegality[move_index] = 0;
                }
            }

            for (i = 0; i < 64; i++) {
                lookup = BattleScene_FindU16InByteArray(pokemon_id + 1, D_8218AD9C, 8);
                if (lookup >= 0) {
                    tm_index = i / 8;
                    if (tm_index == D_8218ADC8[lookup][0]) {
                        tm_hm_flag = species_data->tmHmLearnset[tm_index] | D_8218ADC8[lookup][1];
                    } else {
                        tm_hm_flag = species_data->tmHmLearnset[tm_index];
                    }
                } else {
                    tm_hm_flag = species_data->tmHmLearnset[i / 8];
                }

                if (((tm_hm_flag >> (i % 8)) & 1) && (Move_GetIdFromTableIndex(i) == pokemon_runtime->moves[move_index])) {
                    pokemon->moveSlotIllegality[move_index] = 0;
                }
            }
        } else {
            pokemon->moveSlotIllegality[move_index] = 0;
        }
    }
}

extern u8 D_8218C930[][2];

/**
 * Marks all four moves illegal, then clears the flags for moves the species or
 * its pre-evolutions (D_8218C930) can learn.
 * @unverified Name and comment guessed from the code.
 */
void Battle_CheckMovesetLegality(s8* arg0) {
    s32 pad; // FAKE: stack padding
    s8* state = arg0 + 0x7C6;

    M2C_FIELD(arg0, s8*, 0x851) = 1;
    M2C_FIELD(arg0, s8*, 0x852) = 1;
    M2C_FIELD(arg0, s8*, 0x853) = 1;
    M2C_FIELD(arg0, s8*, 0x854) = 1;
    Battle_MarkLegalMovesForSpecies(arg0, M2C_FIELD(state, u8*, 0xB) - 1);
    if (D_8218C930[M2C_FIELD(state, u8*, 0xB) - 1][0] != 0) {
        Battle_MarkLegalMovesForSpecies(arg0, D_8218C930[M2C_FIELD(state, u8*, 0xB) - 1][0] - 1);
    }
    if (D_8218C930[M2C_FIELD(state, u8*, 0xB) - 1][1] != 0) {
        Battle_MarkLegalMovesForSpecies(arg0, D_8218C930[M2C_FIELD(state, u8*, 0xB) - 1][1] - 1);
    }
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_8210F2F4(s8 *arg0)
{
  int new_var2; // FAKE: permuter temp
  u16 *new_var; // FAKE: permuter temp
  ;
  new_var = ((s8 *) arg0) + 0x7D2;
  new_var2 = ((*((s32 *) (((s8 *) arg0) + 0x860))) + ((*((s32 *) (((s8 *) arg0) + 0x794))) * 0x50)) + ((0, 0x1C));  // FAKE
  *((u16 *) (((s8 *) new_var2) + 2)) = (u16) (*((u16 *) new_var)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
 if (1) { }  // karodo
}

extern ActivePokemon* D_8219A540;
void func_80043860(s32);

/**
 * Steps the party Pokemon's HP one point toward the battle display HP. Returns 1
 * once they are equal.
 * @unverified Name and comment guessed from the code.
 */
s32 Battle_StepPartyHpToDisplay(ActivePokemon* arg0) {
    BattleMonRuntime* rt = &arg0->state.runtime;
    BattleMon* mon = &arg0->teamRoster->pokemonPicked[arg0->state.rosterIndex];

    if (mon->hp == rt->displayHp) {
        return 1;
    }
    mon->hp = Math_StepToS32(mon->hp, rt->displayHp, 1, 1);
    if (mon->hp == rt->displayHp) {
        if (arg0->displayObject.objectType == 0x98) {
            return 1;
        }
        func_80043860(BattleScene_GetParticipantSideIndex(D_8219A540));
        return 1;
    }
    return 0;
}

void BattleScene_IntroInitNop(void) {
}

extern u8 D_82199F7C;
extern f64 D_DBL_82195770;
extern f64 D_DBL_82195778;
u32 func_80053A80(void);
u8 func_8210F3F0(void)
{
  return (D_82199F7C += (u8) ((u32) ((((f32) ((s32) ((u16) (func_80053A80() / 5577)))) / D_DBL_82195770) * D_DBL_82195778))) ^ 0; // FAKE: no-op ^ 0
}
