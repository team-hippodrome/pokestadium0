/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/ekans_game/ekans_game.c. */

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

void func_82183AE0(void);

void func_82183AE0(void) {
}
