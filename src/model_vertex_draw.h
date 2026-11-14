/* Declarations for src/model_vertex_draw.c. */
#ifndef MODEL_VERTEX_DRAW_H
#define MODEL_VERTEX_DRAW_H

#include "global.h"

typedef struct Vec3fCounter {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ s16 count;
} Vec3fCounter; // size = 0x10

typedef struct PosBlend {
    /* 0x00 */ Vec3f base;
    /* 0x0C */ Vec3f offset;
    /* 0x18 */ Color_RGBf color;
    /* 0x24 */ s16 texS;
    /* 0x26 */ s16 texT;
    /* 0x28 */ u8 alpha;
    /* 0x29 */ u8 pad8D;
    /* 0x2A */ u16 disabled;
    /* 0x2C */ u16 drawGroup;
    /* 0x2E */ s16 nextIndex;
} PosBlend; // size = 0x30

typedef struct ModelBlendWeight {
    /* 0x00 */ f32 w0;
    /* 0x04 */ f32 w1;
    /* 0x08 */ f32 w2;
    /* 0x0C */ f32 dist;
} ModelBlendWeight; // size = 0x10

typedef struct ModelTransformCmd {
    /* 0x00 */ s16 targetIndex;
    /* 0x02 */ s16 sourceIndex;
    /* 0x04 */ s16 enableFrom;
    /* 0x06 */ s16 enableTo;
    /* 0x08 */ f32 blendWeight;
    /* 0x0C */ ModelBlendWeight weights[5];
} ModelTransformCmd; // size = 0x5C

typedef struct ModelVertex {
    /* 0x00 */ s16 jointIndex;      // bone / transform index
    /* 0x02 */ s16 parentIndex;     // parent bone index
    /* 0x04 */ s16 childIndex;      // child / next transform
    /* 0x06 */ u16 pad06;
    /* 0x08 */ ModelTransformCmd cmd;
    /* 0x64 */ PosBlend position;
} ModelVertex;                      // size = 0x94

typedef struct StadiumTransform {
    /* 0x00 */ s16  unk_00;
    /* 0x02 */ s16  unk_02;
    /* 0x04 */ f32  maxDist;
    /* 0x08 */ f32  x0;
    /* 0x0C */ f32  y0;
    /* 0x10 */ f32  z0;

    /* 0x14 */ f32  x1;
    /* 0x18 */ f32  y1;
    /* 0x1C */ f32  z1;

    /* 0x20 */ f32  x2;
    /* 0x24 */ f32  y2;
    /* 0x28 */ f32  z2;

    /* 0x2C */ f32  x3;
    /* 0x30 */ f32  y3;
    /* 0x34 */ f32  z3;

    /* 0x38 */ MtxF* mtx;
} StadiumTransform; // size = 0x3C

typedef struct ModelSegment {
    /* 0x00 */ u16 type;
    /* 0x02 */ u16 nodeCount;
    /* 0x04 */ u16 vertexCount;
    /* 0x06 */ u16 triangleCount;
    /* 0x08 */ u32 indexSegment;
    /* 0x0C */ u32 neighborSegment; // @unverified: per-vertex index lists ending in -1, walked in Model_BuildVertexRuntimeData
    /* 0x10 */ u32 tableSegment;
    /* 0x14 */ u32 remapSegment;
    /* 0x18 */ u32 vertexSegment;
    /* 0x1C */ Gfx* displayList;
} ModelSegment; // size = 20

typedef struct StadiumModel {
    /* 0x00 */  s16 isActive;       // @unverified: set to 1 in func_800339CC, cleared by ModelRenderer_ClearSlotModels
    /* 0x02 */  s16 transformCount; // @unverified: used entries of transforms[], func_80033BE4 appends one
    /* 0x04 */  StadiumTransform transforms[5];
    /* 0x130 */ u32 modelSegment;
    /* 0x134 */ s8 pad134[0x4];
    /* 0x138 */ ModelSegment segment; // @unverified: func_800339CC copies the model's segment header here
    /* 0x158 */ Vec3f scale;          // @unverified: axis lengths of the model matrix (func_800339CC), fed to Model_ComputeScaledDistance
    /* 0x164 */ s8 pad164[0xC];
    /* 0x170 */ ModelVertex mvtx;
} StadiumModel; // size = 0x204

// model_vertex_draw.c
void func_80035694(StadiumModel* model);
void Model_ApplyTransformCommands(ModelSegment*, ModelVertex*, StadiumModel*, f32);
void func_80035E48(ModelSegment*, ModelVertex*);

#endif // MODEL_VERTEX_DRAW_H
