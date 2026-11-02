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
    /* 0x04 */ u8 pad04[0x17];
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 pad1E[0xE];
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
    /* 0x2E */ u8 pad2E[8];
    /* 0x36 */ u8 unk_36;
    /* 0x37 */ u8 pad37[0x59];
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

#ifdef NON_MATCHING
/* TODO: decompile func_8218419C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8218419C.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_82184ADC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82184ADC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82184BC8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82184BC8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82184CE0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82184CE0.s")
#endif

s32 func_82184D9C(s8 *arg0, s32 arg1) {
    if ((arg1 == M2C_FIELD(arg0, u8 *, 0x28)) || (arg1 == M2C_FIELD(arg0, u8 *, 0x29))) {
        return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82184DC8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82184DC8.s")
#endif

extern u8 D_80065CF8[];

s32 func_82185044(s32 species, s32 bit) {
    s32 byteIndex;
    s32 bits;

    if (species == 0) {
        return 0;
    }

    bits = D_80065CF8[species * 0x17 + bit / 8];
    switch (species) {
        case 6:
            if (bit / 8 == 6) {
                bits |= 8;
            }
            break;
        case 0xC:
        case 0x30:
        case 0x31:
            if (bit / 8 == 6) {
                bits |= 0x40;
            }
            break;
        case 0x32:
        case 0x33:
        case 0x8D:
            if (bit / 8 == 6) {
                bits |= 4;
            }
            break;
    }
    return (1 << (bit & 7)) & bits;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82185108; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82185108.s")
#endif

s32 func_82185108(u8*, s32);

/**
 * Searches the four slots of arg0 (id bytes at offsets 0x2B..0x2E, flag bytes
 * at 0x3E..0x41) for id arg1. Returns arg1 as soon as a slot with that id
 * has a non-zero flag; the search stops at the first empty (zero) id. When
 * nothing matched it returns func_82185108(arg0, arg1).
 */
s32 func_821851B4(u8* arg0, s32 arg1) {
    s32 i;
    u8* slot;

    for (i = 0, slot = arg0; i < 4; i++, slot++) {
        if (slot[0x2B] == 0) {
            break;
        }
        if ((arg1 == slot[0x2B]) && (slot[0x3E] != 0)) {
            return arg1;
        }
    }
    return func_82185108(arg0, arg1);
}

#ifdef NON_MATCHING
/* TODO: decompile func_82185220; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82185220.s")
#endif

void func_82185378(s8 *arg0, s8 *arg1)
{
  s32 var_v0;
  s8 *var_v1;
  *((s8 *) (((s8 *) arg0) + 0x4A)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x4B)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x4C)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x4D)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x4E)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x52)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x57)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x56)) = 0;
  var_v1 = arg0;
  var_v0 = 0;
  *((u16 *) (((s8 *) arg0) + 0x2A)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x28)));
  *((u16 *) (((s8 *) arg0) + 0x2C)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x2A)));
  *((u16 *) (((s8 *) arg0) + 0x2E)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x2C)));
  var_v1 = (s8 *) var_v1;
  *((u16 *) (((s8 *) arg0) + 0x30)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x2E)));
  do
  {
    var_v0 += 4;
    *((s8 *) (((s8 *) var_v1) + 0x5D)) = 7;
    *((s8 *) (var_v1 + 0x5E)) = 7;
    *((s8 *) (var_v1 + 0x5F)) = 7;
    var_v1 += 4;
    *((s8 *) (((s8 *) var_v1) + 0x58)) = 7;
  }
  while (var_v0 != 8);
}

void GalleryDebugger_LoadControllerPak(void) {
}

void func_821853F4(void) {
}

void func_821853FC(void) {
}

void JigglypuffGame_UpdateEffects(void) {
}

s32 func_8218540C(s8 *arg0, s8 *arg1)
{
  if ((*((u8 *) (((s8 *) arg1) + 0x75))) & (*((u8 *) (((s8 *) arg0) + 0x76))))
  {
    return 1;
  }
  if (((s32) (*((u16 *) (((s8 *) arg1) + 0x3A)))) < ((s32) (*((u16 *) (((s8 *) arg0) + 0x3A)))))
  {
    return 1;
  }
  return 0;
}

extern u8 D_8438B0C4[];
s32 BattleAI_IsRestrictedRandomMove(s32 arg0, s8* arg1) {
    if ((M2C_FIELD(arg1, u8*, 0x58) & 0x40) && (func_8218540C(arg0, arg1) != 0)) {
        return 1;
    }
    return 0;
}

extern s8 *D_821CF2A0;

s32 func_82185494(void) {
    return (M2C_FIELD(D_821CF2A0, u8 *, 0x59) & 0x10) == 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_821854AC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821854AC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821855F0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821855F0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82185684; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82185684.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821857CC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821857CC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821858DC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821858DC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82185A30; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82185A30.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82185BE0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82185BE0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82185D44; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82185D44.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82186394; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82186394.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821864D4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821864D4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8218663C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8218663C.s")
#endif

extern u8 D_821CF280;
extern u8 D_821CF281;
extern BattleSlotZ* D_821CF294;

extern BattleSlotZ* D_821CF294;
extern u8 D_821CF280;
extern u8 D_821CF281;

/**
 * Returns 0x2710 or 0 depending on arg0 and the BattleSlotZ entries (array D_821CF294)
 * selected by the indices D_821CF281 and D_821CF280:
 *   arg0 == 2: if the entry at D_821CF281 has unk_1B equal to 3, 0x71 or 0x7C, returns 0;
 *              otherwise falls through to the arg0 == 1 check;
 *   arg0 == 1: if the entry at D_821CF280 has unk_1B equal to 3, 0x71 or 0x7C, returns 0;
 *              otherwise falls through to return 0x2710;
 *   arg0 == 0: returns 0x2710;
 *   any other arg0: returns 0.
 * What the 0x2710 / 0 results and the unk_1B values mean is not established.
 */
s32 func_821866F0(s32 arg0) {
    switch (arg0) {
        case 2:
            if ((D_821CF294[D_821CF281].unk_1B == 3) || (D_821CF294[D_821CF281].unk_1B == 0x71) || (D_821CF294[D_821CF281].unk_1B == 0x7C)) {
                return 0;
            }
        case 1:
            if ((D_821CF294[D_821CF280].unk_1B == 3) || (D_821CF294[D_821CF280].unk_1B == 0x71) || (D_821CF294[D_821CF280].unk_1B == 0x7C)) {
                return 0;
            }
        case 0:
            return 0x2710;
        default:
            return 0;
    }
}

/**
 * Copies up to four bytes from the string arg0 into arg1. Each of the four
 * output bytes is the current source byte; the source pointer only advances
 * while the byte is non-zero, so once the NUL is reached the remaining output
 * bytes are all zero. (The output is always exactly four bytes.)
 */
void func_821867A8(u8* arg0, u8* arg1) {
    s32 i;
    u8 c;

    for (i = 0; i < 4; i++) {
        c = *arg0;
        if (c == 0) {
            *arg1 = 0;
            arg1++;
        } else {
            *arg1 = c;
            arg1++;
            arg0++;
        }
    }
}

M2C_UNK func_80058410(s8*, s8*, M2C_UNK);

/**
 * Copies a set of fields from the record arg1 into the record arg0, which has a
 * different layout (arg1's offsets 0, 2, 4, 5, 6, 7, 0x1E, 0x24 and 0x26..0x2E map to
 * arg0's 0xB, 0xC, 0x14, 0x15, 0x1C, 0x1D, 0x24, 0x26 and 0x28..0x30). The name field
 * at arg1 + 9 is expanded into the four bytes at arg0 + 0x1F by func_821867A8, and the
 * four bytes at arg1 + 0x20 are copied to arg0 + 0x32. Compare func_821869C4, which
 * copies the already-expanded layout. What the fields mean is not established.
 */
void func_82186834(s8* arg0, s8* arg1) {
    M2C_FIELD(arg0, u8*, 0xB) = M2C_FIELD(arg1, u8*, 0);
    M2C_FIELD(arg0, u16*, 0xC) = M2C_FIELD(arg1, u16*, 2);
    M2C_FIELD(arg0, u8*, 0x14) = M2C_FIELD(arg1, u8*, 4);
    M2C_FIELD(arg0, u8*, 0x15) = M2C_FIELD(arg1, u8*, 5);
    M2C_FIELD(arg0, u8*, 0x1C) = M2C_FIELD(arg1, u8*, 6);
    M2C_FIELD(arg0, u8*, 0x1D) = M2C_FIELD(arg1, u8*, 7);
    func_821867A8(arg1 + 9, arg0 + 0x1F);
    M2C_FIELD(arg0, u16*, 0x24) = M2C_FIELD(arg1, u16*, 0x1E);
    M2C_FIELD(arg0, u8*, 0x26) = M2C_FIELD(arg1, u8*, 0x24);
    M2C_FIELD(arg0, u16*, 0x28) = M2C_FIELD(arg1, u16*, 0x26);
    M2C_FIELD(arg0, u16*, 0x2A) = M2C_FIELD(arg1, u16*, 0x28);
    M2C_FIELD(arg0, u16*, 0x2C) = M2C_FIELD(arg1, u16*, 0x2A);
    M2C_FIELD(arg0, u16*, 0x2E) = M2C_FIELD(arg1, u16*, 0x2C);
    M2C_FIELD(arg0, u16*, 0x30) = M2C_FIELD(arg1, u16*, 0x2E);
    func_80058410(arg1 + 0x20, arg0 + 0x32, 4);
}

#ifdef NON_MATCHING
/* TODO: decompile func_821868E8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821868E8.s")
#endif

M2C_UNK func_80058410(s8 *, s8 *, M2C_UNK);     /* extern */
extern s8 *D_821CF2A0;
void func_821869C4(s8 *arg0, s8 *arg1)
{
  long temp_v1;
  u8 *new_var;
  *((u16 *) (((s8 *) arg0) + 0x28)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x28)));
  *((u16 *) (((s8 *) arg0) + 0xC)) = (u16) (*((u16 *) (((s8 *) arg1) + 0xC)));
  *((u8 *) (((s8 *) arg0) + 0x15)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x15)));
  func_80058410(arg1 + 0x44, arg0 + 0x44, 6);
  *((u8 *) (((s8 *) arg0) + 0x4A)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4A)));
  *((u8 *) (((s8 *) arg0) + 0x4B)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4B)));
  *((u8 *) (((s8 *) arg0) + 0x4C)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4C)));
  *((u8 *) (((s8 *) arg0) + 0x4D)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4D)));
  *((u8 *) (((s8 *) arg0) + 0x4E)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4E)));
  *((u16 *) (((s8 *) arg0) + 0x54)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x54)));
  *((u8 *) (((s8 *) arg0) + 0x56)) = (u8) (*(new_var = (u8 *) (((s8 *) arg1) + 0x56)));
  *((u8 *) (((s8 *) arg0) + 0x57)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x57)));
  *((u8 *) (((s8 *) arg0) + 0x58)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x58)));
  *((u8 *) (((s8 *) arg0) + 0x59)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x59)));
  *((u8 *) (((s8 *) arg0) + 0x5A)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x5A)));
  *((u8 *) (((s8 *) arg0) + 0x5B)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x5B)));
  func_80058410(arg1 + 0x5C, arg0 + 0x5C, 8);
  if ((*((u8 *) (((s8 *) arg1) + 0x4E))) & 8)
  {
    func_821867A8(arg1 + 0x1F, arg0 + 0x1F);
    func_80058410(arg1 + 0x32, arg0 + 0x32, 4);
    return;
  }
  temp_v1 = *((u8 *) (((s8 *) D_821CF2A0) + 0x78));
  if (((s32) temp_v1) < 4)
  {
    *((u8 *) (((s8 *) (arg0 + temp_v1)) + 0x1F)) = (u8) (*((u8 *) (((s8 *) (arg1 + temp_v1)) + 0x1F)));
    *((u8 *) (((s8 *) (arg0 + (*((u8 *) (((s8 *) D_821CF2A0) + 0x78))))) + 0x32)) = (u8) (*((u8 *) (((s8 *) D_821CF2A0) + 0x79)));
  }
}

#ifdef NON_MATCHING
/* TODO: decompile func_82186AF4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82186AF4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82186CA8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82186CA8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82186F28; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82186F28.s")
#endif

extern BattleSlotZ* D_821CF294;
s32 func_82186F28(s32, s32);

s32 func_821870D8(s32 arg0, s32 arg1, s32 arg2) {
    if ((M2C_FIELD(D_821CF294, u8*, 0x368) != 0) || (arg0 != 0)) {
        return 1;
    }
    if (func_82186F28(arg1, arg2) == 0) {
        return 0;
    } else {
        return 1;
    }
    return 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82187134; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82187134.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82187414; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82187414.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82187738; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82187738.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821879A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821879A4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82187DB4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82187DB4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82188050; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82188050.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8218824C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8218824C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82188394; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82188394.s")
#endif

extern u8* D_821CF29C;

/**
 * Searches for another entry that matches entry arg0 in the per-entry byte tables
 * addressed through D_821CF29C (the byte at +0x2B + index and the byte at +0x3E + index,
 * index 0..3). If the +0x3E byte of arg0 has any of the bits 0x3F set, returns arg0.
 * Otherwise scans indices 0..3 in order: stops and returns arg0 at the first index
 * whose +0x2B byte is zero; skips index arg0; and returns the first other index whose
 * +0x2B byte equals that of arg0 and whose +0x3E byte has any of bits 0x3F set.
 * Returns arg0 when no such index is found. What the tables mean is not established.
 */
s32 func_821886F0(s32 arg0) {
    s32 i;
    u8* base;
    u8* cur;
    u8* me;
    u8 v;

    base = D_821CF29C;
    me = base + arg0;
    i = 0;
    if (!(me[0x3E] & 0x3F)) {
        cur = base;
        do {
            v = cur[0x2B];
            if (v == 0) {
                break;
            }
            if ((i != arg0) && (v != 0) && (v == me[0x2B]) && (cur[0x3E] & 0x3F)) {
                return i;
            }
            i++;
            cur++;
        } while (i != 4);
    }
    return arg0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82188770; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82188770.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82188B8C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82188B8C.s")
#endif
