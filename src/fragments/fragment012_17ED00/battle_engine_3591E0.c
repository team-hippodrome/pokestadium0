/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3591E0.c, src/fragments/ekans_game/ekans_game.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gfx_buffer.h"
#include "geo_render.h"
#include "gallery.h"
#include "battle_hud.h"
extern AuxiliaryEffect D_821CEEA0[2];
extern Gfx D_82193E18[];

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

void AuxiliaryEffect_Init(void);
s16 AuxiliaryEffect_Alloc(void);
void AuxiliaryEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5);
void AuxiliaryEffect_Update(s16 arg0);
Gfx* AuxiliaryEffect_DrawOne(Gfx* arg0, AuxiliaryEffectNode* arg1, MtxF* arg2);
Gfx* AuxiliaryEffect_Draw(s16 arg0, Gfx* arg1);
void func_821832F4(void);
void func_821832FC(void);
s32 AuxEffect_GetId(s32 arg0);

void AuxiliaryEffect_Init(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_821CEEA0[i].unk_000 = 0;
    }
}

s16 AuxiliaryEffect_Alloc(void) {
    AuxiliaryEffect* var_a0;
    AuxiliaryEffectNode* var_v1;
    s32 i;
    s32 j;

    for (i = 0, var_a0 = &D_821CEEA0[0]; i < 2; i++, var_a0++) {
        if (var_a0->unk_000 == 0) {
            var_v1 = &var_a0->unk_004[0];
            for (j = 0; j < 20; j++, var_v1++) {
                var_v1->unk_00 = 0;
                var_v1->unk_04 = 0;
                var_v1->unk_08 = 1.0f;
                var_v1->unk_0C.x = 0.0f;
                var_v1->unk_0C.y = 0.0f;
                var_v1->unk_0C.z = 0.0f;
            }
            var_a0->unk_000 = 1;
            return i;
        }
    }
    return -1;
}

void AuxiliaryEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5) {
    s32 i;
    AuxiliaryEffect* temp_v0 = &D_821CEEA0[arg0];
    AuxiliaryEffectNode* var_v1;

    if (temp_v0->unk_000 != 0) {
        var_v1 = &temp_v0->unk_004[0];
        for (i = 0; i < 20; i++, var_v1++) {
            if (var_v1->unk_00 == 0) {
                var_v1->unk_00 = 1;
                var_v1->unk_04 = 0;
                var_v1->unk_06 = arg4;
                var_v1->unk_08 = arg5;
                var_v1->unk_0C.x = arg1;
                var_v1->unk_0C.y = arg2;
                var_v1->unk_0C.z = arg3;
                return;
            }
        }
    }
}

void AuxiliaryEffect_Update(s16 arg0) {
    AuxiliaryEffect* temp_v0 = &D_821CEEA0[arg0];
    AuxiliaryEffectNode* var_v1;
    s32 i;

    if (temp_v0->unk_000 != 0) {
        var_v1 = &temp_v0->unk_004[0];
        for (i = 0; i < 20; i++, var_v1++) {
            if (var_v1->unk_00 == 1) {
                var_v1->unk_04++;
                if (var_v1->unk_06 < var_v1->unk_04) {
                    var_v1->unk_00 = 0;
                }
                var_v1->unk_0C.y -= 0.75f;
            }
        }
    }
}

Gfx* AuxiliaryEffect_DrawOne(Gfx* arg0, AuxiliaryEffectNode* arg1, MtxF* arg2) {
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    Mtx* spBC;
    Mtx sp78;
    Mtx sp38;

    spCC = arg1->unk_0C.x;
    spC8 = arg1->unk_0C.y;
    spC4 = arg1->unk_0C.z;
    spC0 = arg1->unk_08;
    spC0 *= __sinf((arg1->unk_04 * 3.1415927f) / 10.0f);

    guScale(&sp38, spC0, spC0, spC0);
    guTranslate(&sp78, spCC, spC8, spC4);
    spBC = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    guMtxCatL(&sp38, &sp78, spBC);
    guMtxCatL(arg2, spBC, spBC);

    gSPMatrix(arg0++, spBC, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, 200);
    gSPDisplayList(arg0++, D_82193E18);
    gSPPopMatrix(arg0++, G_MTX_MODELVIEW);

    return arg0;
}

Gfx* AuxiliaryEffect_Draw(s16 arg0, Gfx* arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    AuxiliaryEffect* temp_s3 = &D_821CEEA0[arg0];
    AuxiliaryEffectNode* var_s0;
    s32 i;
    MtxF sp78;
    MtxF sp38;

    if (temp_s3->unk_000 == 0) {
        return arg1;
    }

    MtxF_ExtractScale(sp78.mf, &D_80060488->view.floatMatrix);
    guMtxF2L(sp78.mf, sp38.mf);

    var_s0 = &temp_s3->unk_004;
    for (i = 0; i < 20; i++, var_s0++) {
        if (var_s0->unk_00 == 1) {
            arg1 = AuxiliaryEffect_DrawOne(arg1, var_s0, &sp38);
        }
    }

    return arg1;
}

void func_821832F4(void) {
}

void func_821832FC(void) {
}

s32 AuxEffect_GetId(s32 arg0) {
    return arg0;
}
