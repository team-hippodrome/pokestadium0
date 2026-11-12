/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/ekans_game/ekans_game.c, src/fragments/free_battle_rules/free_battle_rules.c, src/fragments/gallery_backgrounds/gallery_backgrounds_2A1B50.c, src/fragments/gallery_camera/gallery_camera_14EC80.c, src/fragments/gallery_camera/gallery_camera_150AC0.c, src/fragments/gallery_debugger/gallery_debugger.c, src/fragments/gallery_enlarge/gallery_enlarge.c, src/fragments/gym_leader_castle/gym_leader_castle.c, src/fragments/jigglypuff_doodle/jigglypuff_doodle.c. */

#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "pokemon_types.h"
#include "fragments/particle_math/particle_math.h"
#include "jpeg_stream.h"
#include "controller.h"
#include "geo_render.h"
#include "model_animation.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sound_state.h"
#include "audio_sfx.h"
#include "audio_channel.h"
#include "audio_loop_point.h"
#include "audio_commands_category2.h"
#include "audio_category_fade.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "fragments/widget_toolkit/widget_toolkit.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"
#include "stage_loader.h"
#include "geo_layout.h"

#include "fragments/free_battle_rules/free_battle_rules.h"
#include "graphics_textures.h"
#include "input.h"
#include "ui_graphics.h"
#include "pokemon_stats.h"
#include "game_state.h"
#include "session.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "DDC0.h"
#include "matrix.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
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

#include "fragments/gallery_backgrounds/gallery_backgrounds.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "gb_data.h"
#include "save_data.h"
#include "gfx_rect.h"
#include "controller_ram.h"
#include "memory.h"

#include "fragments/gallery_camera/gallery_camera.h"
#include "matrix.h"
#include "stage_loader.h"

#include "fragments/gallery_camera/gallery_camera.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "text_system.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
extern u8 D_50002A0[];
extern u8 D_50003F0[];
extern u8 D_5000BA0[];
extern u8 D_5000C90[];
extern u8 D_50011D0[];
extern u8 D_5001680[];
extern u8 D_50017E8[];

#include "fragments/gallery_debugger/gallery_debugger.h"
#include "graphics_textures.h"
#include "input.h"
#include "save_data.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
typedef struct unk_D_839006B0 {
    /* 0x00 */ BattleMon unk_00;
    /* 0x54 */ char unk54[0x38];
} unk_D_839006B0;
typedef struct unk_D_83902700 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk04[0x70];
} unk_D_83902700;

#include "fragments/gallery_enlarge/gallery_enlarge.h"
#include "display_object_textures.h"
#include "graphics_textures.h"
#include "input.h"
#include "gallery.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "gfx_buffer.h"
#include "controller.h"
#include "fragments/gallery_backgrounds/gallery_backgrounds.h"
#include "memory.h"
#include "stage_loader.h"

#include "fragments/gym_leader_castle/gym_leader_castle.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "save_data.h"
#include "game_state.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "audio_commands_category2.h"
#include "DDC0.h"
#include "memory.h"
#include "stage_loader.h"
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
#include "geo_render.h"
#include "model_animation_events.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "ui_graphics.h"
#include "gallery.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "fragments/widget_toolkit/widget_toolkit.h"
#include "memory.h"
#include "stage_loader.h"
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
 * 17-bit shift register, reduced to 0..99. Seeded by BattleAI_SelectTeam.
 * Stadium 1 has the same generator in its audio code, which is where the old
 * name came from.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_RandomPercent(void) {
    D_821CF2B0 = (D_821CF2B0 * 0x41C64E6D) + 0x3039;

    if (D_821CF2B4 & 1) {
        D_821CF2B4 ^= 0x11020;
    }

    D_821CF2B4 >>= 1;

    return (u8)((D_821CF2B0 ^ D_821CF2B4) % 100);
}

s32 func_80053A80();                                /* extern */

/**
 * Advances BattleAI_RandomPercent 0..31 times, using bits 4..8 of func_80053A80.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
void BattleAI_StirRandom(void) {
    u32 var_s0;

    var_s0 = (u32) (func_80053A80() & 0x1F0) >> 4;
    if (var_s0 != 0) {
        do {
            BattleAI_RandomPercent();
            var_s0 -= 1;
        } while (var_s0 != 0);
    }
}

void func_82183BA8(void) {
}

f32 func_80055340(f32);                             /* extern */

/**
 * Gen 1 stat formula without DVs: ((sqrt(statExp) / 4 + base * 2) * level) / 100 + 5.
 * The callers pass statExp 0xFFFF (maximum stat experience).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CalcStat(s32 arg0, s32 arg1, s32 arg2) {
    return ((s32) ((((s32) func_80055340((f32) arg1) / 4) + (arg0 * 2)) * arg2) / 100) + 5;
}

/**
 * Max HP from base HP and level: BattleAI_CalcStat(base, 0xFFFF, level) + level + 5.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CalcMaxHp(s32 arg0, s32 arg1) {
    return BattleAI_CalcStat(arg0, 0xFFFF, arg1) + arg1 + 5;
}

/**
 * Attack from base stat and level (max stat experience).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CalcAttack(s32 arg0, s32 arg1) {
    return BattleAI_CalcStat(arg0, 0xFFFF, arg1);
}

/**
 * Defense from base stat and level (max stat experience).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CalcDefense(s32 arg0, s32 arg1) {
    return BattleAI_CalcStat(arg0, 0xFFFF, arg1);
}

/**
 * Speed from base stat and level (max stat experience).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CalcSpeed(s32 arg0, s32 arg1) {
    return BattleAI_CalcStat(arg0, 0xFFFF, arg1);
}

/**
 * Special from base stat and level (max stat experience).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CalcSpecial(s32 arg0, s32 arg1) {
    return BattleAI_CalcStat(arg0, 0xFFFF, arg1);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Current HP as a percentage of max HP (battler bytes 0x18 / 0x34), at least 1
 * while the Pokemon has any HP left, 0 when fainted.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_GetHpPercent(s8 *arg0)
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
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CountUnfainted(u8 *arg0) {
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

void func_82183D9C(void) {
}

void func_82183DA4(void) {
}

void func_82183DAC(void) {
}

void func_82183DB4(void) {
}

void func_82183DBC(void) {
}

void func_82183DC4(void) {
}

/**
 * Adds a random 0..15 * 400 to a battler's team-pick score (word at offset 4).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
void BattleAI_AddRandomPickScore(s8* arg0) {
    BattleAI_StirRandom();
    M2C_FIELD(arg0, s32*, 4) += (BattleAI_RandomPercent() & 0xF) * 400;
}

void func_82183E1C(void) {
}

/*
 * BattleSlotZ is a 0x90-byte view of the AI's side model (D_821CF618 /
 * D_821CF998) shifted by four bytes: each side is a party pointer followed by
 * six 0x90-byte battler records, and D_821CF29C / D_821CF2A0 point at a
 * record (slot + 4). In record terms the battle Pokemon (BattleMonRuntime,
 * 0x64 bytes) starts at +0xC; see docs/annotation/com-ai.md.
 */
typedef struct BattleSlotZ {
    /* 0x00 */ TeamRoster* roster;
    /* 0x04 */ u8 pad04[4];
    /* 0x08 */ s32 pickScore;
    /* 0x0C */ u8 pad0C[0xF];
    /* 0x1B */ u8 species;
    /* 0x1C */ u16 hp;
    /* 0x1E */ u8 pad1E[0xE];
    /* 0x2C */ u8 type1;
    /* 0x2D */ u8 type2;
    /* 0x2E */ u8 pad2E[8];
    /* 0x36 */ u8 level;
    /* 0x37 */ u8 pad37[0x48];
    /* 0x7F */ u8 unk_7F;
    /* 0x80 */ u8 pad80[0x10];
} BattleSlotZ; // size = 0x90
extern BattleSlotZ* D_821CF298;

/**
 * Returns 1 if an unfainted Pokemon of the given species is in the opponent's
 * team (D_821CF298), otherwise 0.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_OpponentHasSpecies(s32 arg0) {
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
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CountOpponentWaterOrFlying(void) {
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
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CountOpponentGround(void) {
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
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CountOpponentFighting(void) {
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
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_OpponentHasLevel55Tauros(void) {
    s32 i;

    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].species == TAUROS) && (D_821CF298[i].level == 0x37)) {
            return 1;
        }
    }
    return 0;
}

/**
 * Counts opponent Pokemon that are Electric or Poison type.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CountOpponentElectricOrPoison(void) {
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
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CountOpponentRockOrWater(void) {
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
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CountOpponentElectric(void) {
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
s32 BattleAI_NoVenusaurChanseyJynxPicked(s32);

/**
 * Hand-written team-selection preferences. The COM trainer is identified by the
 * id word of its roster (0x6974, 0x95EC, ...); for some trainers a species gets a
 * bonus when the opponent brought a species it counters (for example Gengar when
 * the opponent has Tauros). Every pick except Ditto also gets +50000 unless the
 * side's mode byte (0x368) is set. arg1 is the pick round (0 = lead).
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
void BattleAI_AddTrainerPickScore(u8* arg0, s32 arg1) {
    s32 score = 0;
    s32 id = D_821CF294->roster->unk_018;

    switch (arg0[0x17]) {
        case GENGAR:
            if ((id == 0x6974) && BattleAI_OpponentHasSpecies(TAUROS)) {
                score = 0x7530;
            }
            break;
        case ALAKAZAM:
            if ((id == 0x6974) && BattleAI_OpponentHasSpecies(GENGAR)) {
                score = 0x2710;
            }
            if (id == 0x3C5E) {
                score = 0x3E8;
            }
            if (id == 0xBBBD) {
                score = 0x1388;
            }
            if (id == 0x95EC) {
                if (BattleAI_OpponentHasSpecies(GENGAR)) {
                    score = 0x1388;
                }
                if (BattleAI_OpponentHasSpecies(CHANSEY) || BattleAI_OpponentHasSpecies(EXEGGUTOR) || BattleAI_OpponentHasSpecies(JYNX)) {
                    break;
                }
                score += 0x1388;
            }
            break;
        case DITTO:
            if (((u8*)D_821CF294)[0x368] != 0) {
                score = 0x3E8;
            }
            break;
        case JYNX:
            if (id == 0x6974) {
                score = 0x2710;
            }
            if (id == 0x6299) {
                score = BattleAI_NoVenusaurChanseyJynxPicked(arg1);
            }
            break;
        case JOLTEON:
            if (id == 0x6974) {
                score = 0x2710;
            }
            if ((id == 0xC0FC) && (BattleAI_OpponentHasSpecies(LAPRAS) || BattleAI_OpponentHasSpecies(DEWGONG) || BattleAI_OpponentHasSpecies(CLOYSTER))) {
                score = 0x2710;
            }
            if ((id == 0x6299) && (BattleAI_CountOpponentWaterOrFlying() >= 2)) {
                score = 0x2710;
            }
            if (id == 0x3C5E) {
                score = 0x2710;
            }
            if (id == 0x813A) {
                if (BattleAI_OpponentHasSpecies(EXEGGUTOR) || BattleAI_OpponentHasSpecies(SNORLAX)) {
                    break;
                }
                score = 0x2710;
            }
            if (((id == 0x77CB) || (id == 0xBBBD) || (id == 0x940F)) && BattleAI_CountOpponentWaterOrFlying()) {
                score = 0x1388;
            }
            if ((id == 0xD870) && !BattleAI_CountOpponentGround()) {
                score = 0x2710;
            }
            if ((id == 0x940F) && BattleAI_OpponentHasSpecies(EXEGGUTOR)) {
                score += 0x1388;
            }
            if (id == 0x95EC) {
                if (BattleAI_OpponentHasSpecies(STARMIE) || BattleAI_OpponentHasSpecies(ZAPDOS) || BattleAI_OpponentHasSpecies(GYARADOS)) {
                    score = 0x1388;
                }
                if (BattleAI_OpponentHasSpecies(CHANSEY) || BattleAI_OpponentHasSpecies(EXEGGUTOR) || BattleAI_CountOpponentGround()) {
                    break;
                }
                score += 0x1388;
            }
            break;
        case STARMIE:
            if (id == 0x6974) {
                score = 0x2710;
            }
            if (id == 0xCD7E) {
                score = 0x2710;
            }
            if ((id == 0xC0FC) && BattleAI_CountOpponentGround()) {
                score = 0x1388;
            }
            if (id == 0x3C5E) {
                score = 0x1388;
            }
            if (id == 0x95EC) {
                score = 0x1388;
                if (BattleAI_OpponentHasSpecies(GENGAR) || BattleAI_OpponentHasSpecies(DRAGONITE)) {
                    score = 0x2710;
                }
                if (BattleAI_OpponentHasSpecies(JYNX)) {
                    break;
                }
                score += 0x1388;
            }
            if ((id == 0x813A) && (BattleAI_OpponentHasSpecies(EXEGGUTOR) || BattleAI_OpponentHasSpecies(SNORLAX))) {
                score = 0x2710;
            }
            break;
        case TAUROS:
            if (id == 0x4FC7) {
                score = 0x1388;
            }
            if ((id == 0x6299) && !BattleAI_CountOpponentFighting()) {
                score = 0x2710;
            }
            if (id == 0x813A) {
                if (BattleAI_OpponentHasSpecies(EXEGGUTOR) || BattleAI_OpponentHasSpecies(SNORLAX)) {
                    break;
                }
                score = 0x2710;
            }
            if ((id == 0xBBBD) || (id == 0xD870) || (id == 0x940F)) {
                score = 0x2710;
            }
            if (id == 0x95EC) {
                if (BattleAI_OpponentHasSpecies(JYNX) || BattleAI_OpponentHasSpecies(CHANSEY) || BattleAI_OpponentHasSpecies(DUGTRIO) || BattleAI_OpponentHasSpecies(GENGAR) ||
                    BattleAI_OpponentHasSpecies(DRAGONITE)) {
                    score = 0x1388;
                }
                if (BattleAI_OpponentHasSpecies(LAPRAS) || BattleAI_OpponentHasSpecies(ARTICUNO)) {
                    break;
                }
                score += 0x1388;
            }
            break;
        case ELECTRODE:
            if (id == 0x4FC7) {
                score = 0x2710;
            }
            break;
        case KANGASKHAN:
            if ((id == 0x4FC7) && BattleAI_OpponentHasSpecies(ARTICUNO)) {
                score = 0x1388;
            }
            break;
        case EXEGGUTOR:
            if (((u8*)D_821CF294)[0x368] != 0) {
                score = 0x3E8;
                break;
            }
            if ((id == 0xC0FC) && BattleAI_CountOpponentGround()) {
                score = 0x1388;
            }
            if ((id == 0xD870) && BattleAI_OpponentHasLevel55Tauros()) {
                score = 0x2710;
            }
            if (id == 0x95EC) {
                if (BattleAI_OpponentHasSpecies(JOLTEON) || BattleAI_OpponentHasSpecies(ALAKAZAM)) {
                    score = 0x1388;
                }
                if (BattleAI_OpponentHasSpecies(JYNX)) {
                    break;
                }
                score += 0x1388;
            }
            break;
        case LAPRAS:
            if (id == 0x813A) {
                if (BattleAI_OpponentHasSpecies(EXEGGUTOR) || BattleAI_OpponentHasSpecies(SNORLAX)) {
                    break;
                }
                score = 0x2710;
            }
            if (id == 0xBBBD) {
                score = 0x3E8;
            }
            if ((id == 0x95EC) && (BattleAI_OpponentHasSpecies(ARTICUNO) || BattleAI_OpponentHasSpecies(TAUROS) || BattleAI_OpponentHasSpecies(CLOYSTER) ||
                                   BattleAI_OpponentHasSpecies(DEWGONG) || BattleAI_OpponentHasSpecies(LAPRAS) || BattleAI_OpponentHasSpecies(EXEGGUTOR) ||
                                   BattleAI_OpponentHasSpecies(STARMIE) || BattleAI_OpponentHasSpecies(DRAGONITE))) {
                score = 0x1388;
            }
            break;
        case DUGTRIO:
            if (BattleAI_CountOpponentElectricOrPoison()) {
                score = 0x1388;
            }
            break;
        case GOLEM:
        case ARTICUNO:
            if ((id == 0x813A) && (BattleAI_OpponentHasSpecies(EXEGGUTOR) || BattleAI_OpponentHasSpecies(SNORLAX))) {
                score = 0x2710;
            }
            break;
        case VENUSAUR:
            if ((id == 0x6299) && BattleAI_NoVenusaurChanseyJynxPicked(arg1) && (BattleAI_CountOpponentRockOrWater() >= 2)) {
                score = 0x2710;
            }
            break;
        case CHANSEY:
            if ((id == 0x6299) && BattleAI_NoVenusaurChanseyJynxPicked(arg1) && !BattleAI_CountOpponentFighting()) {
                score = 0x2710;
            }
            break;
        case GYARADOS:
            if ((id == 0x6299) && (BattleAI_CountOpponentElectric() < 2)) {
                score = 0x2710;
            }
            break;
        case PINSIR:
            if (((u8*)D_821CF294)[0x368] != 0) {
                score = 0x3E8;
            }
            break;
    }
    if ((((u8*)D_821CF294)[0x368] == 0) && (arg0[0x17] != DITTO)) {
        score += 0xC350;
    }
    M2C_FIELD(arg0, s32*, 4) += score;
}

/**
 * Strided byte search: returns the first byte equal to arg3 in a table of arg2
 * bytes read every arg1 bytes, or NULL.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
u8* BattleAI_FindByte(u8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8* p;

    for (p = arg0; arg2 != 0; p += arg1) {
        arg2 -= arg1;
        if (arg3 == *p) {
            return p;
        }
    }
    return NULL;
}

#include "fragments/fragment012_17ED00/battle_engine_com_ai_2_types.h"
extern Move82184ADC D_8006B190[];
extern u8 D_8218AC50[];
/**
 * Damage multiplier of a move from attacker arg0 to defender arg1, in percent:
 * 150 for same-type attack bonus, then each matching type-chart row
 * (D_8218AC50: attacking type, defending type, multiplier * 10) is applied.
 * Status moves (power 0) return 100.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_GetTypeMultiplier(s8* arg0, s8* arg1, s32 move) {
    s32 mult = 100;
    u8 defType1;
    u8 defType2;
    s32 type;
    u8* chart;

    if (move != 0) {
        defType1 = M2C_FIELD(arg1, u8*, 0x28);
        defType2 = M2C_FIELD(arg1, u8*, 0x29);
        if (D_8006B190[move - 1].power != 0) {
            type = D_8006B190[move - 1].type;
            if (type == M2C_FIELD(arg0, u8*, 0x28) || type == M2C_FIELD(arg0, u8*, 0x29)) {
                mult = 150;
            }
            for (chart = D_8218AC50; chart[0] != 0xFF; chart += 3) {
                if (chart[0] == type && (chart[1] == defType1 || chart[1] == defType2)) {
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
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_CanUseMove(s8 *arg0, s32 arg1) {
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
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
u8 BattleAI_FindUsableHealingMove(u8 *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            return 0;
        }
        switch (arg0[0x2B + i]) {
            case RECOVER:
            case SOFTBOILED:
            case REST:
                if (BattleAI_CanUseMove((s8*)arg0, arg0[0x2B + i]) != 0) {
                    return arg0[0x2B + i];
                }
                break;
        }
    }
    return 0;
}

/**
 * Returns 1 if either of the battler's types is arg1.
 * @unverified Name and comment guessed from the code (COM AI pass).
 */
s32 BattleAI_HasType(s8 *arg0, s32 arg1) {
    if ((arg1 == M2C_FIELD(arg0, u8 *, 0x28)) || (arg1 == M2C_FIELD(arg0, u8 *, 0x29))) {
        return 1;
    }
    return 0;
}

