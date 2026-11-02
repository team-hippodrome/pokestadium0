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
typedef struct unk_func_8437F068_sp28 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} unk_func_8437F068_sp28;
typedef struct unk_func_8437F85C_sp74 {
    /* 0x00 */ s32 unk_00[6];
} unk_func_8437F85C_sp74;

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

u16 BattleAI_ApplyMoveEffectDamageOverride(BattleMonRuntime* arg0, BattleMonRuntime* arg1);
void BattleAI_ClampDamageRatio(void);
void BattleAI_PrepareDamageCalcState(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2);
s32 BattleScene_FindU16InByteArray(u16 lookup_value, u8* array, s32 array_length);
void BattleScene_IntroInitNop(void);

u16 BattleAI_ApplyMoveEffectDamageOverride(BattleMonRuntime* arg0, BattleMonRuntime* arg1) {
    s32 var_v0;

    switch (D_8219A494.unk_01) {
        case 38:
            break;

        case 40:
            D_82199F50 = arg0->unk_0C / 2;
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

void BattleAI_ClampDamageRatio(void) {
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

void func_8210EB28(u8* attacker, u8* defender) {
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

void BattleAI_PrepareDamageCalcState(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2) {
    MoveData* temp_v0 = &gMoveData[arg2 - 1];

    D_8219A494.unk_00 = temp_v0->unk_00;
    D_8219A494.unk_01 = temp_v0->unk_01;
    D_8219A494.unk_02 = temp_v0->unk_02;
    D_8219A494.unk_03 = temp_v0->unk_03;
    D_8219A494.unk_04 = temp_v0->unk_04;
    D_8219A494.unk_05 = temp_v0->unk_05;

    D_82199F50 = 0;
    D_82199F52 = D_8219A494.unk_02;
    if (D_82199F52) {
        if (D_8219A494.unk_03 < 0x14) {
            D_82199F56 = arg1->unk_2C;
            if (arg1->unk_4E & 4) {
                D_82199F56 *= 2;
            }

            if (D_82199F32 != 0) {
                D_82199F56 = arg1->unk_3A;
                D_82199F54 = arg0->unk_38;
            } else {
                D_82199F54 = arg0->unk_2A;
            }
        } else {
            D_82199F56 = arg1->unk_30;
            if (arg1->unk_4E & 2) {
                D_82199F56 *= 2;
            }

            if (D_82199F32 != 0) {
                D_82199F56 = arg1->unk_3E;
                D_82199F54 = arg0->unk_3E;
            } else {
                D_82199F54 = arg0->unk_30;
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

#ifdef NON_MATCHING
/* TODO: decompile func_8210EDBC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210EDBC.s")
#endif

extern u8 D_82199F32;
extern u8 D_82199F33;
void func_8210E9C0(u8*, u8*);
void func_8210EAC4();
void func_8210EC0C(u8*, u8*, u8);
void func_8210EDBC(u8*, u8*);

/**
 * Runs the sequence func_8210EC0C, func_8210EDBC, func_8210EB28,
 * func_8210EAC4 and func_8210E9C0 for the attacker/defender pair
 * (arg0, arg1). The flag D_82199F32 is saved into D_82199F33 and cleared
 * for the first four steps, and restored before the last one. arg2 is only
 * handed on to func_8210EC0C.
 */
void func_8210EED8(u8* arg0, u8* arg1, u8 arg2) {
    D_82199F33 = D_82199F32;
    D_82199F32 = 0;
    func_8210EC0C(arg0, arg1, arg2);
    func_8210EDBC(arg0, arg1);
    func_8210EB28(arg0, arg1);
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

#ifdef NON_MATCHING
/* TODO: decompile func_8210EFAC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210EFAC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8210F24C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210F24C.s")
#endif

void func_8210F2F4(s8 *arg0)
{
  int new_var2;
  u16 *new_var;
  ;
  new_var = ((s8 *) arg0) + 0x7D2;
  new_var2 = ((*((s32 *) (((s8 *) arg0) + 0x860))) + ((*((s32 *) (((s8 *) arg0) + 0x794))) * 0x50)) + ((0, 0x1C));
  *((u16 *) (((s8 *) new_var2) + 2)) = (u16) (*((u16 *) new_var));
 if (1) { }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8210F31C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210F31C.s")
#endif

void BattleScene_IntroInitNop(void) {
}

#ifdef NON_MATCHING
/* TODO: decompile func_8210F3F0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8210F3F0.s")
#endif
