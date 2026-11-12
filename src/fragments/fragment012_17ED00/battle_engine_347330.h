#ifndef ZERO_BATTLE_ENGINE_347330_H
#define ZERO_BATTLE_ENGINE_347330_H

/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_347330.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math_util.h"
#include "math.h"
typedef struct unk_D_843951D0_1010 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 unk_10;
} unk_D_843951D0_1010;
typedef struct unk_D_843951D0 {
    /* 0x0000 */ s16 unk_0000;
    /* 0x0004 */ f32 unk_0004;
    /* 0x0008 */ s16 unk_0008;
    /* 0x000A */ s16 unk_000A;
    /* 0x000C */ Vtx* unk_000C;
    /* 0x0010 */ char unk0010[0x1000];
    /* 0x1010 */ unk_D_843951D0_1010 grid[16][16];
} unk_D_843951D0;
extern RibbonMesh D_8219CB20[4];
extern s16 D_8219F700;
extern s16 D_8219F702;
extern s32 pad_D_843951C8[2];
extern unk_D_843951D0 sWaterHeightMap;
extern s16 D_821A1B20;
extern s16 D_821A1B22;
extern s16 D_821A1B24;
extern unk_D_843975E8 D_821A1B28;
extern func_D_84390320 gMoveAnimEffectStartFuncs[];
extern func_D_84390320 gMoveAnimEffectEndFuncs[];
extern func_D_84390320 gMoveAnimEffectStartUpdateFuncs[];
extern func_D_84390320 gMoveAnimEffectEndUpdateFuncs[];
extern func_D_84390320 gMoveAnimEffectStartDrawFuncs[];
extern func_D_84390320 gMoveAnimEffectEndDrawFuncs[];
extern s32 pad_D_84388E38[2];
extern Gfx D_82192890[];
extern s32 pad_D_84388F78[2];

void MistHaze_Init(void);
void MistHaze_Configure(RibbonMesh* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                   s32 arg9);
void MistHaze_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
void MistHaze_UpdateEnvAlpha(RibbonMesh* arg0);
s32 MistHaze_Update(RibbonMesh* arg0);
s32 MistHaze_UpdatePool(void);
Gfx* MistHaze_Draw(Gfx* arg0, RibbonMesh* arg1);
Gfx* MistHaze_DrawPool(Gfx* arg0);
void SurfTerrainGrid_BuildCameraBounds(unk_D_843975E8* arg0, f32 arg1);
f32 SurfTerrainGrid_SampleHeightAndSlope(f32 x, f32 z, f32* rotation_x);
s32 SurfTerrainGrid_UpdateWaves(void);
void SurfTerrainGrid_Init(s32 arg0, s16 arg1, s16 arg2);
s32 SurfTerrainGrid_Update(void);
Gfx* SurfTerrainGrid_Draw(Gfx* arg0);

void MistHaze_Configure(RibbonMesh* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                   s32 arg9);

extern const f64 D_DBL_821979B8;
extern const f32 D_FLT_821979C0;
extern const f64 D_DBL_821979C8;
extern const f64 D_DBL_821979D0;
extern const f64 D_DBL_821979D8;
extern const f64 D_DBL_821979E0;
extern const f64 D_DBL_821979E8;
extern const f64 D_DBL_821979F0;

/**
 * Samples the Surf water surface (sWaterHeightMap) at world position (x, z).
 *
 * Returns the water height (world Y) at that point and writes the surface tilt
 * in degrees, in the range [-90, 90], to *rotation_x. The surface is a 16x16
 * grid of vertices, so the height is found by picking the grid cell under
 * (x, z), picking one of the cell's two triangles, and evaluating that
 * triangle's plane at (x, z).
 *
 * Called by BattleAnim_SurfContinue to keep the Surf rider on the wave:
 * the return value is added to the model's base height and the tilt becomes its
 * X rotation. Also called by SurfTerrainGrid_Draw to compare the camera-aligned
 * quad corners against the water surface.
 * //@src/fragments/battle_engine/battle_engine_2F3CB0.c
 * //@src/fragments/battle_engine/battle_engine_347330.c SurfTerrainGrid_UpdateWaves
 */

extern const f64 D_DBL_82197A28;
extern const f64 D_DBL_82197A30;
extern const f64 D_DBL_82197A38;
extern const f32 D_FLT_82197A40;

#endif
