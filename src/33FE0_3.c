/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/33FE0.c. */

#include "global.h"
#include "33FE0.h"
#include "geo_render.h"
#include "battle_hud.h"
#include "memmap.h"
extern s16 D_80074670[0x102];
extern s16 D_80074874[0x102];
extern s16 D_80074A78[0x102];
extern s16 D_80074C7C[0x102];
extern s16 D_80074E80[0x102];
extern s16 D_80075084[0x102];
extern s16 D_80075288[0x102];
extern s16 D_8007548C[0x102];
extern s16 D_80075690[0x102];
extern f32 D_80075894[16];
extern Vec3fCounter* D_800B32C0;
extern PosBlend D_800B32C8[0x10];
extern Mtx D_800B35C8;

void Model_AccumulateVertexOffset(MtxF* mtx, PosBlend* position, s16 (*target)[3], f32 alpha);
void Model_InitializeVertexPositions(ModelSegment* segment, MtxF* mtx, ModelVertex* mvtx);
void Model_CopyPositionBuffer(PosBlend* src, PosBlend* dst);

s16 Model_GetVertexClass(s16* table, s32 index);
s16 Model_GetVertexMatrixClass(s16* arg0, s32 arg1);
void Model_TransformPoint(MtxF* mtx, Vec3f* out, s16 (*in)[3]);

void Model_AccumulateVertexOffset(MtxF* mtx, PosBlend* position, s16 (*target)[3], f32 alpha) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 dx;
    f32 dy;
    f32 dz;

    sp44 = (f32) (*target)[0];
    sp40 = (f32) (*target)[1];
    sp3C = (f32) (*target)[2];

    guMtxXFMF(mtx->mf, sp44, sp40, sp3C, &sp44, &sp40, &sp3C);

    dx = sp44 - position->base.x;
    dy = sp40 - position->base.y;
    dz = sp3C - position->base.z;

    dx *= alpha;
    dy *= alpha;
    dz *= alpha;

    position->offset.x += dx;
    position->offset.y += dy;
    position->offset.z += dz;
}

void Model_InitializeVertexPositions(ModelSegment* segment, MtxF* mtx, ModelVertex* mvtx) {
    s16* index_table;
    s32 i;
    Vtx* vtx;
    PosBlend* position;
    ModelVertex* tmp;

    index_table = Memmap_GetSegmentVaddr(segment->tableSegment);
    vtx = Memmap_GetSegmentVaddr(segment->vertexSegment);
    Memmap_GetSegmentVaddr(segment->remapSegment);
    tmp = mvtx;
    
    for(i = 0; i < segment->vertexCount; i++) {
        position = &tmp->position;
        switch (Model_GetVertexClass(index_table, i)) {
            case 0:
            default:
                Model_TransformPoint(mtx, &position->base, &vtx->v.ob);
                position->offset.x = 0.0f;
                position->offset.y = 0.0f;
                position->offset.z = 0.0f;
                break;
            case 4:
                Model_TransformPoint(mtx + Model_GetVertexMatrixClass(index_table, i), &position->base, &vtx->v.ob);
                position->offset.x = 0.0f;
                position->offset.y = 0.0f;
                position->offset.z = 0.0f;
                break;
        }
        vtx++;
        tmp++;
    }
}

void Model_CopyPositionBuffer(PosBlend* src, PosBlend* dst) {
    *dst = *src;
}
