/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/ekans_game/ekans_game.c, src/fragments/free_battle_rules/free_battle_rules.c, src/fragments/gallery_backgrounds/gallery_backgrounds_2A1B50.c, src/fragments/gallery_camera/gallery_camera_14EC80.c, src/fragments/gallery_camera/gallery_camera_150AC0.c, src/fragments/gallery_debugger/gallery_debugger.c, src/fragments/gallery_enlarge/gallery_enlarge.c, src/fragments/gym_leader_castle/gym_leader_castle.c, src/fragments/jigglypuff_doodle/jigglypuff_doodle.c. */

#include "fragments/ekans_game/ekans_game.h"
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
typedef struct ActiveDiglettInfo {
    /* 0x00 */ s16 diglettId;
    /* 0x02 */ s16 state;
    /* 0x04 */ s16 timer;
    /* 0x06 */ s16 unk_06; //	0
    /* 0x08 */ s16 gotHoop;
    /* 0x0A */ s16 unk_0A; //	0
    /* 0x0C */ s16 collidingActorId;
} ActiveDiglettInfo;
typedef struct ActorOriginPosition {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ char unk0C[0x6];
    /* 0x12 */ s16 unk_12;
    /* 0x12 */ s16 unk_14;
} ActorOriginPosition;
extern MiniActor miniDigletts[9];
extern MiniActor miniDiglettHoles[9];
extern MiniActor miniEkanses[4];
extern ActiveDiglettInfo activeDigletts[3];
extern s16 ekansMinigameCountdownStarted;
extern u32 redDiglettTileTexture[];
extern u32 yellowDiglettTileTexture[];
extern u32 blueDiglettTileTexture[];
extern u32 floorTexture1[];
extern u32 floorTexture2[];
extern u32 sceneDecorationTextureBlue[];
extern u32 sceneDecorationTextureGreen[];
extern u32 sceneDecorationTextureRed[];
extern u32 sceneDecorationTextureYellow[];
extern unk_D_86002F34_018 sceneTextures[];
extern Vtx sceneGeometry_1[];
extern Vtx sceneGeometry_2[];
extern Vtx sceneGeometry_3[];
extern Vtx sceneGeometry_4[];
extern Vtx sceneGeometry_5[];
extern Vtx sceneGeometry_6[];
extern Vtx sceneGeometry_7[];
extern Vtx sceneGeometry_8[];
extern Vtx sceneGeometry_9[];
extern Vtx sceneGeometry_10[];
extern Vtx sceneGeometry_11[];
extern Vtx sceneGeometry_12[];
extern Vtx sceneGeometry_13[];
extern u32 ekansShadowTexture[];
extern MiniActor* miniDiglettPtr;
extern MiniActor* miniDiglettHolePtr;
extern MiniActor* miniEkansPtr;
extern s16 miniEkansDifficulties[4][4];
extern ActorOriginPosition skansActorInfo[];
extern ActorOriginPosition diglettActorInfo[];
extern s16 playerGUIScoreXPositions[];
extern Color_RGB8 playerColors[];

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
#include "fragments/minigame_actor_framework/minigame_actor_framework.h"

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

#include "fragments/jigglypuff_doodle/jigglypuff_doodle.h"
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
#include "fragments/minigame_shared_graphics/minigame_shared_graphics.h"
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
void GalleryDebugger_SaveControllerPak(void);
void GalleryDebugger_LoadControllerPak(void);
void func_821853F4(void);
void func_821853FC(void);
void JigglypuffGame_UpdateEffects(void);

extern s32 D_821CF2B0;
extern u32 D_821CF2B4;
u32 Audio_NextRandom(void) {
    D_821CF2B0 = (D_821CF2B0 * 0x41C64E6D) + 0x3039;

    if (D_821CF2B4 & 1) {
        D_821CF2B4 ^= 0x11020;
    }

    D_821CF2B4 >>= 1;

    return (u8)((D_821CF2B0 ^ D_821CF2B4) % 100);
}

s32 func_80053A80();                                /* extern */
M2C_UNK func_82183AF0();                            /* extern */

void func_82183B60(void) {
    u32 var_s0;

    var_s0 = (u32) (func_80053A80() & 0x1F0) >> 4;
    if (var_s0 != 0) {
        do {
            func_82183AF0();
            var_s0 -= 1;
        } while (var_s0 != 0);
    }
}

void func_82183BA8(void) {
}

f32 func_80055340(f32);                             /* extern */

s32 func_82183BB0(s32 arg0, s32 arg1, s32 arg2) {
    return ((s32) ((((s32) func_80055340((f32) arg1) / 4) + (arg0 * 2)) * arg2) / 100) + 5;
}

/*
 * func_82183C24
 *
 * Returns func_82183BB0(arg0, 0xFFFF, arg1) + arg1 + 5.  The four functions
 * that follow (func_82183C54 .. func_82183CC0) make the same call to
 * func_82183BB0 without the extra "+ arg1 + 5".
 */
s32 func_82183C24(s32 arg0, s32 arg1) {
    return func_82183BB0(arg0, 0xFFFF, arg1) + arg1 + 5;
}

s32 func_82183C54(s32 arg0, s32 arg1) {
    return func_82183BB0(arg0, 0xFFFF, arg1);
}

s32 func_82183C78(s32 arg0, s32 arg1) {
    return func_82183BB0(arg0, 0xFFFF, arg1);
}

s32 func_82183C9C(s32 arg0, s32 arg1) {
    return func_82183BB0(arg0, 0xFFFF, arg1);
}

s32 func_82183CC0(s32 arg0, s32 arg1) {
    return func_82183BB0(arg0, 0xFFFF, arg1);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s32 func_82183CE4(s8 *arg0)
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

/*
 * func_82183D50
 *
 * arg0 points to an array of 0x90-byte entries whose count is the byte at
 * offset 2 of the record that the first word of arg0 points to. Returns the
 * number of entries whose halfword at offset 0x1C is non-zero.
 *
 * What the entries and the count's record are is not established (the first
 * word of arg0 is read through to find the count, so the first entry's own
 * first word is that record pointer). Matching note: the loop is a do/while
 * over a byte pointer with the end address `arg0 + n * 0x90` recomputed in
 * its condition, as in the ROM.
 */
s32 func_82183D50(u8 *arg0) {
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

void func_82183DCC(s8* arg0) {
    func_82183B60();
    M2C_FIELD(arg0, s32*, 4) += (func_82183AF0() & 0xF) * 400;
}

void GalleryDebugger_SaveControllerPak(void) {
}

typedef struct BattleSlotZ {
    /* 0x00 */ TeamRoster* roster;
    /* 0x04 */ u8 pad04[4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 pad0C[0xF];
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 pad1E[0xE];
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
    /* 0x2E */ u8 pad2E[8];
    /* 0x36 */ u8 unk_36;
    /* 0x37 */ u8 pad37[0x48];
    /* 0x7F */ u8 unk_7F;
    /* 0x80 */ u8 pad80[0x10];
} BattleSlotZ; // size = 0x90
extern BattleSlotZ* D_821CF298;

/**
 * Returns 1 if any of the first `numberOfPokemonCanBePicked` BattleSlotZ
 * entries has a non-zero unk_1C and unk_1B equal to arg0, otherwise 0.
 * (func_82183FD4 below walks the same array.)
 */
s32 func_82183E24(s32 arg0) {
    s32 i;

    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].unk_1C != 0) && (arg0 == D_821CF298[i].unk_1B)) {
            return 1;
        }
    }
    return 0;
}

/**
 * Counts how many of the first `numberOfPokemonCanBePicked` BattleSlotZ entries
 * (walked like func_82183E24 / func_82183FD4) have unk_2C or unk_2D equal to 0x15
 * or 2. What the two bytes and the values mean is not established.
 */
s32 func_82183E88(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].unk_2C == 0x15) || (D_821CF298[i].unk_2D == 0x15) || (D_821CF298[i].unk_2C == 2) || (D_821CF298[i].unk_2D == 2)) {
            count++;
        }
    }
    return count;
}

/**
 * Counts how many of the first `numberOfPokemonCanBePicked` BattleSlotZ entries
 * (walked like func_82183E24 / func_82183FD4) have unk_2C or unk_2D equal to 4.
 * What the two bytes and the value 4 mean is not established.
 */
s32 func_82183F04(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].unk_2C == 4) || (D_821CF298[i].unk_2D == 4)) {
            count++;
        }
    }
    return count;
}

/**
 * Counts how many of the first `numberOfPokemonCanBePicked` BattleSlotZ entries
 * (walked like func_82183E24 / func_82183FD4) have unk_2C or unk_2D equal to 1.
 * What the two bytes and the value 1 mean is not established.
 */
s32 func_82183F6C(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].unk_2C == 1) || (D_821CF298[i].unk_2D == 1)) {
            count++;
        }
    }
    return count;
}

s32 func_82183FD4(void) {
    s32 i;

    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].unk_1B == 0x80) && (D_821CF298[i].unk_36 == 0x37)) {
            return 1;
        }
    }
    return 0;
}

/**
 * Counts how many of the first `numberOfPokemonCanBePicked` BattleSlotZ entries
 * (walked like func_82183E24 / func_82183FD4) have unk_2C or unk_2D equal to 0x17
 * or 3. What the two bytes and the values mean is not established.
 */
s32 func_8218403C(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].unk_2C == 0x17) || (D_821CF298[i].unk_2D == 0x17) || (D_821CF298[i].unk_2C == 3) || (D_821CF298[i].unk_2D == 3)) {
            count++;
        }
    }
    return count;
}

/**
 * Counts how many of the first `numberOfPokemonCanBePicked` BattleSlotZ entries
 * (walked like func_82183E24 / func_82183FD4) have unk_2C or unk_2D equal to 5
 * or 0x15. What the two bytes and the values mean is not established.
 */
s32 func_821840B8(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].unk_2C == 5) || (D_821CF298[i].unk_2D == 5) || (D_821CF298[i].unk_2C == 0x15) || (D_821CF298[i].unk_2D == 0x15)) {
            count++;
        }
    }
    return count;
}

/**
 * Counts how many of the first `numberOfPokemonCanBePicked` BattleSlotZ entries
 * (walked like func_82183E24 / func_82183FD4) have unk_2C or unk_2D equal to 0x17.
 * What the two bytes and the value 0x17 mean is not established.
 */
s32 func_82184134(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_821CF298->roster->rosterInfo->numberOfPokemonCanBePicked; i++) {
        if ((D_821CF298[i].unk_2C == 0x17) || (D_821CF298[i].unk_2D == 0x17)) {
            count++;
        }
    }
    return count;
}

extern BattleSlotZ* D_821CF294;
s32 func_821866F0(s32);

void func_8218419C(u8* arg0, s32 arg1) {
    s32 score = 0;
    s32 id = D_821CF294->roster->unk_018;

    switch (arg0[0x17]) {
        case 0x5E:
            if ((id == 0x6974) && func_82183E24(0x80)) {
                score = 0x7530;
            }
            break;
        case 0x41:
            if ((id == 0x6974) && func_82183E24(0x5E)) {
                score = 0x2710;
            }
            if (id == 0x3C5E) {
                score = 0x3E8;
            }
            if (id == 0xBBBD) {
                score = 0x1388;
            }
            if (id == 0x95EC) {
                if (func_82183E24(0x5E)) {
                    score = 0x1388;
                }
                if (func_82183E24(0x71) || func_82183E24(0x67) || func_82183E24(0x7C)) {
                    break;
                }
                score += 0x1388;
            }
            break;
        case 0x84:
            if (((u8*)D_821CF294)[0x368] != 0) {
                score = 0x3E8;
            }
            break;
        case 0x7C:
            if (id == 0x6974) {
                score = 0x2710;
            }
            if (id == 0x6299) {
                score = func_821866F0(arg1);
            }
            break;
        case 0x87:
            if (id == 0x6974) {
                score = 0x2710;
            }
            if ((id == 0xC0FC) && (func_82183E24(0x83) || func_82183E24(0x57) || func_82183E24(0x5B))) {
                score = 0x2710;
            }
            if ((id == 0x6299) && (func_82183E88() >= 2)) {
                score = 0x2710;
            }
            if (id == 0x3C5E) {
                score = 0x2710;
            }
            if (id == 0x813A) {
                if (func_82183E24(0x67) || func_82183E24(0x8F)) {
                    break;
                }
                score = 0x2710;
            }
            if (((id == 0x77CB) || (id == 0xBBBD) || (id == 0x940F)) && func_82183E88()) {
                score = 0x1388;
            }
            if ((id == 0xD870) && !func_82183F04()) {
                score = 0x2710;
            }
            if ((id == 0x940F) && func_82183E24(0x67)) {
                score += 0x1388;
            }
            if (id == 0x95EC) {
                if (func_82183E24(0x79) || func_82183E24(0x91) || func_82183E24(0x82)) {
                    score = 0x1388;
                }
                if (func_82183E24(0x71) || func_82183E24(0x67) || func_82183F04()) {
                    break;
                }
                score += 0x1388;
            }
            break;
        case 0x79:
            if (id == 0x6974) {
                score = 0x2710;
            }
            if (id == 0xCD7E) {
                score = 0x2710;
            }
            if ((id == 0xC0FC) && func_82183F04()) {
                score = 0x1388;
            }
            if (id == 0x3C5E) {
                score = 0x1388;
            }
            if (id == 0x95EC) {
                score = 0x1388;
                if (func_82183E24(0x5E) || func_82183E24(0x95)) {
                    score = 0x2710;
                }
                if (func_82183E24(0x7C)) {
                    break;
                }
                score += 0x1388;
            }
            if ((id == 0x813A) && (func_82183E24(0x67) || func_82183E24(0x8F))) {
                score = 0x2710;
            }
            break;
        case 0x80:
            if (id == 0x4FC7) {
                score = 0x1388;
            }
            if ((id == 0x6299) && !func_82183F6C()) {
                score = 0x2710;
            }
            if (id == 0x813A) {
                if (func_82183E24(0x67) || func_82183E24(0x8F)) {
                    break;
                }
                score = 0x2710;
            }
            if ((id == 0xBBBD) || (id == 0xD870) || (id == 0x940F)) {
                score = 0x2710;
            }
            if (id == 0x95EC) {
                if (func_82183E24(0x7C) || func_82183E24(0x71) || func_82183E24(0x33) || func_82183E24(0x5E) ||
                    func_82183E24(0x95)) {
                    score = 0x1388;
                }
                if (func_82183E24(0x83) || func_82183E24(0x90)) {
                    break;
                }
                score += 0x1388;
            }
            break;
        case 0x65:
            if (id == 0x4FC7) {
                score = 0x2710;
            }
            break;
        case 0x73:
            if ((id == 0x4FC7) && func_82183E24(0x90)) {
                score = 0x1388;
            }
            break;
        case 0x67:
            if (((u8*)D_821CF294)[0x368] != 0) {
                score = 0x3E8;
                break;
            }
            if ((id == 0xC0FC) && func_82183F04()) {
                score = 0x1388;
            }
            if ((id == 0xD870) && func_82183FD4()) {
                score = 0x2710;
            }
            if (id == 0x95EC) {
                if (func_82183E24(0x87) || func_82183E24(0x41)) {
                    score = 0x1388;
                }
                if (func_82183E24(0x7C)) {
                    break;
                }
                score += 0x1388;
            }
            break;
        case 0x83:
            if (id == 0x813A) {
                if (func_82183E24(0x67) || func_82183E24(0x8F)) {
                    break;
                }
                score = 0x2710;
            }
            if (id == 0xBBBD) {
                score = 0x3E8;
            }
            if ((id == 0x95EC) && (func_82183E24(0x90) || func_82183E24(0x80) || func_82183E24(0x5B) ||
                                   func_82183E24(0x57) || func_82183E24(0x83) || func_82183E24(0x67) ||
                                   func_82183E24(0x79) || func_82183E24(0x95))) {
                score = 0x1388;
            }
            break;
        case 0x33:
            if (func_8218403C()) {
                score = 0x1388;
            }
            break;
        case 0x4C:
        case 0x90:
            if ((id == 0x813A) && (func_82183E24(0x67) || func_82183E24(0x8F))) {
                score = 0x2710;
            }
            break;
        case 0x3:
            if ((id == 0x6299) && func_821866F0(arg1) && (func_821840B8() >= 2)) {
                score = 0x2710;
            }
            break;
        case 0x71:
            if ((id == 0x6299) && func_821866F0(arg1) && !func_82183F6C()) {
                score = 0x2710;
            }
            break;
        case 0x82:
            if ((id == 0x6299) && (func_82184134() < 2)) {
                score = 0x2710;
            }
            break;
        case 0x7F:
            if (((u8*)D_821CF294)[0x368] != 0) {
                score = 0x3E8;
            }
            break;
    }
    if ((((u8*)D_821CF294)[0x368] == 0) && (arg0[0x17] != 0x84)) {
        score += 0xC350;
    }
    M2C_FIELD(arg0, s32*, 4) += score;
}

u8* func_82184AA8(u8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8* p;

    for (p = arg0; arg2 != 0; p += arg1) {
        arg2 -= arg1;
        if (arg3 == *p) {
            return p;
        }
    }
    return NULL;
}

typedef struct Move82184ADC { u8 unk00; u8 unk01; u8 power; u8 type; u8 unk04; u8 unk05; } Move82184ADC;
extern Move82184ADC D_8006B190[];
extern u8 D_8218AC50[];
s32 func_82184ADC(s8* arg0, s8* arg1, s32 move) {
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

s32 func_82184BC8(s8 *arg0, s32 arg1) {
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

u8 func_82184CE0(u8 *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            return 0;
        }
        switch (arg0[0x2B + i]) {
            case 0x69:
            case 0x87:
            case 0x9C:
                if (func_82184BC8((s8*)arg0, arg0[0x2B + i]) != 0) {
                    return arg0[0x2B + i];
                }
                break;
        }
    }
    return 0;
}

s32 func_82184D9C(s8 *arg0, s32 arg1) {
    if ((arg1 == M2C_FIELD(arg0, u8 *, 0x28)) || (arg1 == M2C_FIELD(arg0, u8 *, 0x29))) {
        return 1;
    }
    return 0;
}

