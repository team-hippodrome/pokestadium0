/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/ekans_game/ekans_game.c, src/fragments/free_battle_rules/free_battle_rules.c, src/fragments/gallery_backgrounds/gallery_backgrounds_2A1B50.c, src/fragments/gallery_camera/gallery_camera_14EC80.c, src/fragments/gallery_camera/gallery_camera_150AC0.c, src/fragments/gallery_debugger/gallery_debugger.c, src/fragments/gallery_enlarge/gallery_enlarge.c, src/fragments/gym_leader_castle/gym_leader_castle.c, src/fragments/jigglypuff_doodle/jigglypuff_doodle.c. */

#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "pokemon_types.h"
#include "battle.h"
#include "asset_archive.h"

typedef struct unk_D_84002D18 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} unk_D_84002D18;
typedef struct unk_D_84002D28 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
} unk_D_84002D28;
typedef struct unk_D_84002BE8 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ u8* unk_0C;
} unk_D_84002BE8;
extern s32 pad_D_84002D10;
extern s32 pad_D_84002D1C;



extern u8 D_50002A0[];
extern u8 D_50003F0[];
extern u8 D_5000BA0[];
extern u8 D_5000C90[];
extern u8 D_50011D0[];
extern u8 D_5001680[];
extern u8 D_50017E8[];

typedef struct unk_D_839006B0 {
    /* 0x00 */ BattleMon unk_00;
    /* 0x54 */ char unk54[0x38];
} unk_D_839006B0;
typedef struct unk_D_83902700 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk04[0x70];
} unk_D_83902700;


extern char** sUiText;
extern char** sTrainerNameText;
extern GymLeaderCastleTrainer sCurrentNodeTrainers[4];
extern BinArchive* sTrainerDataArchive;
extern BinArchive* sPortraitArchive;
extern BinArchive* sBackgroundArchive;
extern u8* sGymLeaderCastleTexture;
extern u8* sEliteFourTexture;
extern s16 sCurrentHoverNodeIndex;
#define CHAMPION 11
#define ELITE_4 10
#define ELITE_4_TO_GLC 9
#define GLC_TO_ELITE_4 8
#define GIOVANNI 7
extern CastleMapNode sCastleMapNodes[];
extern s16 sSelectedMapNode;
extern s16 sCursorMoveTimer;
extern s16 sRoomDescriptionHeight;
extern s16 sEliteFourTransition;

#include "math.h"
typedef struct unk_D_86301730 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ DisplayObject unk_004;
    /* 0x16C */ Vec3f unk_16C;
    /* 0x178 */ s8 unk_178;
    /* 0x179 */ s8 unk_179;
    /* 0x17A */ s8 unk_17A;
    /* 0x17B */ s8 unk_17B;
    /* 0x17C */ u16 unk_17C;
    /* 0x17E */ char pad17E[6];
} unk_D_86301730;

#include "m2c_macros.h"

void func_82183BA8(void);
void func_82183D9C(void);
void func_82183DA4(void);
void func_82183DAC(void);
void func_82183DB4(void);
void func_82183DBC(void);
void func_82183DC4(void);
void func_82183E1C(void);
void func_821853EC(void);
void func_821853F4(void);
void func_821853FC(void);
void func_82185404(void);

extern s32 D_821CF2B0;
extern u32 D_821CF2B4;
/**
 * The COM AI's own random source: an LCG (x * 0x41C64E6D + 0x3039) mixed with a
 * 17-bit shift register, reduced to 0..99. Seeded by BattleAi_SelectTeam.
 * Stadium 1 has the same generator in its audio code, which is where the old
 * name came from.
 */
s32 BattleAi_RandomPercent(void) {
    D_821CF2B0 = (D_821CF2B0 * 0x41C64E6D) + 0x3039;

    if (D_821CF2B4 & 1) {
        D_821CF2B4 ^= 0x11020;
    }

    D_821CF2B4 >>= 1;

    return (u8)((D_821CF2B0 ^ D_821CF2B4) % 100);
}

s32 func_80053A80();                                /* extern */

/**
 * Advances BattleAi_RandomPercent 0..31 times, using bits 4..8 of func_80053A80.
 */
void BattleAi_StirRandom(void) {
    u32 var_s0;

    var_s0 = (u32) (func_80053A80() & 0x1F0) >> 4;
    if (var_s0 != 0) {
        do {
            BattleAi_RandomPercent();
            var_s0 -= 1;
        } while (var_s0 != 0);
    }
}

/**
 * Empty.
 */
void func_82183BA8(void) {
}

f32 func_80055340(f32);                             /* extern */

/**
 * Gen 1 stat formula without DVs: ((sqrt(statExp) / 4 + base * 2) * level) / 100 + 5.
 * The callers pass statExp 0xFFFF (maximum stat experience).
 */
s32 BattleAi_CalcStat(s32 arg0, s32 arg1, s32 arg2) {
    return ((s32) ((((s32) func_80055340((f32) arg1) / 4) + (arg0 * 2)) * arg2) / 100) + 5;
}

/**
 * Max HP from base HP and level: BattleAi_CalcStat(base, 0xFFFF, level) + level + 5.
 */
s32 BattleAi_CalcMaxHp(s32 arg0, s32 arg1) {
    return BattleAi_CalcStat(arg0, 0xFFFF, arg1) + arg1 + 5;
}

/**
 * Attack from base stat and level (max stat experience).
 */
s32 BattleAi_CalcAttack(s32 arg0, s32 arg1) {
    return BattleAi_CalcStat(arg0, 0xFFFF, arg1);
}

/**
 * Defense from base stat and level (max stat experience).
 */
s32 BattleAi_CalcDefense(s32 arg0, s32 arg1) {
    return BattleAi_CalcStat(arg0, 0xFFFF, arg1);
}

/**
 * Speed from base stat and level (max stat experience).
 */
s32 BattleAi_CalcSpeed(s32 arg0, s32 arg1) {
    return BattleAi_CalcStat(arg0, 0xFFFF, arg1);
}

/**
 * Special from base stat and level (max stat experience).
 */
s32 BattleAi_CalcSpecial(s32 arg0, s32 arg1) {
    return BattleAi_CalcStat(arg0, 0xFFFF, arg1);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Current HP as a percentage of max HP (battler bytes 0x18 / 0x34), at least 1
 * while the Pokemon has any HP left, 0 when fainted.
 */
s32 BattleAi_GetHpPercent(s8 *arg0)
{
  s32 var_v1;
  u16 temp_v0;
  temp_v0 = *((u16 *) (((s8 *) arg0) + 0x18));
  if (!temp_v0)
  {
    return 0;
  }
  var_v1 = ((s32) (temp_v0 * 0x64)) / ((s32) (*((u16 *) (((s8 *) arg0) + 0x34))));
  if (var_v1 == 0)
  {
    var_v1 = 1;
  }
  return var_v1;
}

/**
 * Counts the battlers on a side whose HP is not zero. The side's first word is the
 * party, whose info byte at offset 2 is the number of Pokemon in play.
 * Matching note: the loop is a do/while over a byte pointer with the end address
 * `arg0 + n * 0x90` recomputed in its condition, as in the ROM.
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_CountUnfainted(u8 *arg0) {
    s32 count;
    u8 *p;
    s32 n;

    count = 0;
    p = arg0;
    n = M2C_FIELD(*(void **)arg0, u8 *, 2);
    if (n > 0) {
        do {
            if (M2C_FIELD(p, u16 *, 0x1C) != 0) {
                count++;
            }
            p += 0x90;
        } while (p < arg0 + n * 0x90);
    }
    return count;
}

/**
 * Empty.
 */
void func_82183D9C(void) {
}

/**
 * Empty.
 */
void func_82183DA4(void) {
}

/**
 * Empty.
 */
void func_82183DAC(void) {
}

/**
 * Empty.
 */
void func_82183DB4(void) {
}

/**
 * Empty.
 */
void func_82183DBC(void) {
}

/**
 * Empty.
 */
void func_82183DC4(void) {
}

/**
 * Adds a random 0..15 * 400 to a battler's team-pick score (word at offset 4).
 * Seen in play (2026-11-13) (Free Battle, COM team selection): called from BattleAi_PickNextPokemon
 * for some candidates (the 40% roll), with the candidate battler as the argument.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
void BattleAi_AddRandomPickScore(s8* arg0) {
    BattleAi_StirRandom();
    M2C_FIELD(arg0, s32*, 4) += (BattleAi_RandomPercent() & 0xF) * 400;
}

/**
 * Empty.
 */
void func_82183E1C(void) {
}

extern BattleSlotZ* D_821CF298;

/**
 * Returns 1 if an unfainted Pokemon of the given species is in the opponent's
 * team (D_821CF298), otherwise 0.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_OpponentHasSpecies(s32 arg0) {
    s32 i;

    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].hp != 0) && (arg0 == D_821CF298[i].species)) {
            return 1;
        }
    }
    return 0;
}

/**
 * Counts opponent Pokemon that are Water or Flying type.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_CountOpponentWaterOrFlying(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].type1 == TYPE_WATER) || (D_821CF298[i].type2 == TYPE_WATER) || (D_821CF298[i].type1 == TYPE_FLYING) || (D_821CF298[i].type2 == TYPE_FLYING)) {
            count++;
        }
    }
    return count;
}

/**
 * Counts opponent Pokemon that are Ground type.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_CountOpponentGround(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].type1 == TYPE_GROUND) || (D_821CF298[i].type2 == TYPE_GROUND)) {
            count++;
        }
    }
    return count;
}

/**
 * Counts opponent Pokemon that are Fighting type.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_CountOpponentFighting(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].type1 == TYPE_FIGHTING) || (D_821CF298[i].type2 == TYPE_FIGHTING)) {
            count++;
        }
    }
    return count;
}

/**
 * Returns 1 if the opponent brought a level 55 Tauros.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_OpponentHasLevel55Tauros(void) {
    s32 i;

    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].species == TAUROS) && (D_821CF298[i].level == 55)) {
            return 1;
        }
    }
    return 0;
}

/**
 * Counts opponent Pokemon that are Electric or Poison type.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_CountOpponentElectricOrPoison(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].type1 == TYPE_ELECTRIC) || (D_821CF298[i].type2 == TYPE_ELECTRIC) || (D_821CF298[i].type1 == TYPE_POISON) || (D_821CF298[i].type2 == TYPE_POISON)) {
            count++;
        }
    }
    return count;
}

/**
 * Counts opponent Pokemon that are Rock or Water type.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_CountOpponentRockOrWater(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].type1 == TYPE_ROCK) || (D_821CF298[i].type2 == TYPE_ROCK) || (D_821CF298[i].type1 == TYPE_WATER) || (D_821CF298[i].type2 == TYPE_WATER)) {
            count++;
        }
    }
    return count;
}

/**
 * Counts opponent Pokemon that are Electric type.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_CountOpponentElectric(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].type1 == TYPE_ELECTRIC) || (D_821CF298[i].type2 == TYPE_ELECTRIC)) {
            count++;
        }
    }
    return count;
}

extern BattleSlotZ* D_821CF294;
s32 BattleAi_NoVenusaurChanseyJynxPicked(s32);

/**
 * Hand-written team-selection preferences. The COM trainer is identified by the
 * id word of its roster (0x6974, 0x95EC, ...); for some trainers a species gets a
 * bonus when the opponent brought a species it counters (for example Gengar when
 * the opponent has Tauros). Every pick except Ditto also gets +50000 unless the
 * side's mode byte (0x368) is set. arg1 is the pick round (0 = lead).
 * Seen in play (2026-11-13) (Free Battle against the むしとり roster, COM team selection): called from
 * BattleAi_PickNextPokemon for each candidate with round 0. That roster's trainer id matched none
 * of the hand-written cases, so none of the opponent checks it calls ran.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
void BattleAi_AddTrainerPickScore(u8* arg0, s32 arg1) {
    s32 score = 0;
    s32 id = D_821CF294->roster->unk_018;

    switch (arg0[0x17]) {
        case GENGAR:
            if ((id == 0x6974) && BattleAi_OpponentHasSpecies(TAUROS)) {
                score = 30000;
            }
            break;
        case ALAKAZAM:
            if ((id == 0x6974) && BattleAi_OpponentHasSpecies(GENGAR)) {
                score = 10000;
            }
            if (id == 0x3C5E) {
                score = 1000;
            }
            if (id == 0xBBBD) {
                score = 5000;
            }
            if (id == 0x95EC) {
                if (BattleAi_OpponentHasSpecies(GENGAR)) {
                    score = 5000;
                }
                if (BattleAi_OpponentHasSpecies(CHANSEY) || BattleAi_OpponentHasSpecies(EXEGGUTOR) || BattleAi_OpponentHasSpecies(JYNX)) {
                    break;
                }
                score += 5000;
            }
            break;
        case DITTO:
            if (((u8*)D_821CF294)[0x368] != 0) {
                score = 1000;
            }
            break;
        case JYNX:
            if (id == 0x6974) {
                score = 10000;
            }
            if (id == 0x6299) {
                score = BattleAi_NoVenusaurChanseyJynxPicked(arg1);
            }
            break;
        case JOLTEON:
            if (id == 0x6974) {
                score = 10000;
            }
            if ((id == 0xC0FC) && (BattleAi_OpponentHasSpecies(LAPRAS) || BattleAi_OpponentHasSpecies(DEWGONG) || BattleAi_OpponentHasSpecies(CLOYSTER))) {
                score = 10000;
            }
            if ((id == 0x6299) && (BattleAi_CountOpponentWaterOrFlying() >= 2)) {
                score = 10000;
            }
            if (id == 0x3C5E) {
                score = 10000;
            }
            if (id == 0x813A) {
                if (BattleAi_OpponentHasSpecies(EXEGGUTOR) || BattleAi_OpponentHasSpecies(SNORLAX)) {
                    break;
                }
                score = 10000;
            }
            if (((id == 0x77CB) || (id == 0xBBBD) || (id == 0x940F)) && BattleAi_CountOpponentWaterOrFlying()) {
                score = 5000;
            }
            if ((id == 0xD870) && !BattleAi_CountOpponentGround()) {
                score = 10000;
            }
            if ((id == 0x940F) && BattleAi_OpponentHasSpecies(EXEGGUTOR)) {
                score += 5000;
            }
            if (id == 0x95EC) {
                if (BattleAi_OpponentHasSpecies(STARMIE) || BattleAi_OpponentHasSpecies(ZAPDOS) || BattleAi_OpponentHasSpecies(GYARADOS)) {
                    score = 5000;
                }
                if (BattleAi_OpponentHasSpecies(CHANSEY) || BattleAi_OpponentHasSpecies(EXEGGUTOR) || BattleAi_CountOpponentGround()) {
                    break;
                }
                score += 5000;
            }
            break;
        case STARMIE:
            if (id == 0x6974) {
                score = 10000;
            }
            if (id == 0xCD7E) {
                score = 10000;
            }
            if ((id == 0xC0FC) && BattleAi_CountOpponentGround()) {
                score = 5000;
            }
            if (id == 0x3C5E) {
                score = 5000;
            }
            if (id == 0x95EC) {
                score = 5000;
                if (BattleAi_OpponentHasSpecies(GENGAR) || BattleAi_OpponentHasSpecies(DRAGONITE)) {
                    score = 10000;
                }
                if (BattleAi_OpponentHasSpecies(JYNX)) {
                    break;
                }
                score += 5000;
            }
            if ((id == 0x813A) && (BattleAi_OpponentHasSpecies(EXEGGUTOR) || BattleAi_OpponentHasSpecies(SNORLAX))) {
                score = 10000;
            }
            break;
        case TAUROS:
            if (id == 0x4FC7) {
                score = 5000;
            }
            if ((id == 0x6299) && !BattleAi_CountOpponentFighting()) {
                score = 10000;
            }
            if (id == 0x813A) {
                if (BattleAi_OpponentHasSpecies(EXEGGUTOR) || BattleAi_OpponentHasSpecies(SNORLAX)) {
                    break;
                }
                score = 10000;
            }
            if ((id == 0xBBBD) || (id == 0xD870) || (id == 0x940F)) {
                score = 10000;
            }
            if (id == 0x95EC) {
                if (BattleAi_OpponentHasSpecies(JYNX) || BattleAi_OpponentHasSpecies(CHANSEY) || BattleAi_OpponentHasSpecies(DUGTRIO) || BattleAi_OpponentHasSpecies(GENGAR) ||
                    BattleAi_OpponentHasSpecies(DRAGONITE)) {
                    score = 5000;
                }
                if (BattleAi_OpponentHasSpecies(LAPRAS) || BattleAi_OpponentHasSpecies(ARTICUNO)) {
                    break;
                }
                score += 5000;
            }
            break;
        case ELECTRODE:
            if (id == 0x4FC7) {
                score = 10000;
            }
            break;
        case KANGASKHAN:
            if ((id == 0x4FC7) && BattleAi_OpponentHasSpecies(ARTICUNO)) {
                score = 5000;
            }
            break;
        case EXEGGUTOR:
            if (((u8*)D_821CF294)[0x368] != 0) {
                score = 1000;
                break;
            }
            if ((id == 0xC0FC) && BattleAi_CountOpponentGround()) {
                score = 5000;
            }
            if ((id == 0xD870) && BattleAi_OpponentHasLevel55Tauros()) {
                score = 10000;
            }
            if (id == 0x95EC) {
                if (BattleAi_OpponentHasSpecies(JOLTEON) || BattleAi_OpponentHasSpecies(ALAKAZAM)) {
                    score = 5000;
                }
                if (BattleAi_OpponentHasSpecies(JYNX)) {
                    break;
                }
                score += 5000;
            }
            break;
        case LAPRAS:
            if (id == 0x813A) {
                if (BattleAi_OpponentHasSpecies(EXEGGUTOR) || BattleAi_OpponentHasSpecies(SNORLAX)) {
                    break;
                }
                score = 10000;
            }
            if (id == 0xBBBD) {
                score = 1000;
            }
            if ((id == 0x95EC) && (BattleAi_OpponentHasSpecies(ARTICUNO) || BattleAi_OpponentHasSpecies(TAUROS) || BattleAi_OpponentHasSpecies(CLOYSTER) ||
                                   BattleAi_OpponentHasSpecies(DEWGONG) || BattleAi_OpponentHasSpecies(LAPRAS) || BattleAi_OpponentHasSpecies(EXEGGUTOR) ||
                                   BattleAi_OpponentHasSpecies(STARMIE) || BattleAi_OpponentHasSpecies(DRAGONITE))) {
                score = 5000;
            }
            break;
        case DUGTRIO:
            if (BattleAi_CountOpponentElectricOrPoison()) {
                score = 5000;
            }
            break;
        case GOLEM:
        case ARTICUNO:
            if ((id == 0x813A) && (BattleAi_OpponentHasSpecies(EXEGGUTOR) || BattleAi_OpponentHasSpecies(SNORLAX))) {
                score = 10000;
            }
            break;
        case VENUSAUR:
            if ((id == 0x6299) && BattleAi_NoVenusaurChanseyJynxPicked(arg1) && (BattleAi_CountOpponentRockOrWater() >= 2)) {
                score = 10000;
            }
            break;
        case CHANSEY:
            if ((id == 0x6299) && BattleAi_NoVenusaurChanseyJynxPicked(arg1) && !BattleAi_CountOpponentFighting()) {
                score = 10000;
            }
            break;
        case GYARADOS:
            if ((id == 0x6299) && (BattleAi_CountOpponentElectric() < 2)) {
                score = 10000;
            }
            break;
        case PINSIR:
            if (((u8*)D_821CF294)[0x368] != 0) {
                score = 1000;
            }
            break;
    }
    if ((((u8*)D_821CF294)[0x368] == 0) && (arg0[0x17] != DITTO)) {
        score += 50000;
    }
    M2C_FIELD(arg0, s32*, 4) += score;
}

/**
 * Strided byte search: returns the first byte equal to arg3 in a table of arg2
 * bytes read every arg1 bytes, or NULL.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
u8* BattleAi_FindByte(u8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8* p;

    for (p = arg0; arg2 != 0; p += arg1) {
        arg2 -= arg1;
        if (arg3 == *p) {
            return p;
        }
    }
    return NULL;
}

extern Move82184ADC D_8006B190[];
extern u8 D_8218AC50[];
/**
 * Damage multiplier of a move from attacker arg0 to defender arg1, in percent:
 * 150 for same-type attack bonus, then each matching type-chart row
 * (D_8218AC50: attacking type, defending type, multiplier * 10) is applied.
 * Status moves (power 0) return 100.
 * Seen in play (2026-11-13) (Free Battle, COM team selection): called from
 * BattleAi_AddMatchupPickScore and returned 100 for neutral matchups.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAi_GetTypeMultiplier(s8* arg0, s8* arg1, s32 move) {
    s32 mult = 100;
    u8 def_type1;
    u8 def_type2;
    s32 type;
    u8* chart;

    if (move != 0) {
        def_type1 = M2C_FIELD(arg1, u8*, 0x28);
        def_type2 = M2C_FIELD(arg1, u8*, 0x29);
        if (D_8006B190[move - 1].power != 0) {
            type = D_8006B190[move - 1].type;
            if (type == M2C_FIELD(arg0, u8*, 0x28) || type == M2C_FIELD(arg0, u8*, 0x29)) {
                mult = 150;
            }
            for (chart = D_8218AC50; chart[0] != 0xFF; chart += 3) {
                if (chart[0] == type && (chart[1] == def_type1 || chart[1] == def_type2)) {
                    mult = chart[2] * mult / 10;
                }
            }
        }
    }
    return mult;
}

/**
 * Returns the move if the battler knows it, has PP left for it and it is not the
 * disabled move (byte 0x63); otherwise 0.
 * Seen in play (2026-11-12): during a COM decision it returned each move it was asked about
 * (0x0B, 0x42, 0x68, 0x75) for COM's Pinsir, whose AI record holds exactly those four moves
 * with 30, 25, 15 and 10 PP.
 */
s32 BattleAi_CanUseMove(s8 *arg0, s32 arg1) {
    s32 i;
    u8 *p = (u8 *)arg0;

    if (arg1 != 0) {
        for (i = 0; i < 4; i++) {
            if (p[0x2B + i] == 0) {
                return 0;
            }
            if ((arg1 == p[0x2B + i]) && (p[0x3E + i] & 0x3F) && (arg1 != p[0x63])) {
                return arg1;
            }
        }
    }
    return 0;
}

/**
 * Returns Recover, Softboiled or Rest if the battler can use one, otherwise 0.
 * Seen in play (2026-11-12): returned 0x69 (Recover) for COM's Gengar after Recover was put in
 * its move slot 3, and 0 for 1P's Nidoqueen, which has no healing move.
 */
u8 BattleAi_FindUsableHealingMove(u8 *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            return 0;
        }
        switch (arg0[0x2B + i]) {
            case RECOVER:
            case SOFTBOILED:
            case REST:
                if (BattleAi_CanUseMove((s8*)arg0, arg0[0x2B + i]) != 0) {
                    return arg0[0x2B + i];
                }
                break;
        }
    }
    return 0;
}

/**
 * Returns 1 if either of the battler's types is arg1.
 */
s32 BattleAi_HasType(s8 *arg0, s32 arg1) {
    if ((arg1 == M2C_FIELD(arg0, u8 *, 0x28)) || (arg1 == M2C_FIELD(arg0, u8 *, 0x29))) {
        return 1;
    }
    return 0;
}

