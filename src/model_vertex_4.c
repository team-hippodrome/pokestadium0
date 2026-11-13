/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/33FE0.c, src/DDC0.c. */

#include <PR/os_internal_reg.h>
#include "global.h"
#include "model_vertex.h"
#include "memmap.h"
extern s32 D_800AAE30;
extern s32 D_800AAF3C;

#include "global.h"
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

void func_800350E0(void);
void func_800350E8(ModelSegment* segment, MtxF* mtx, ModelVertex* mvtx);
f32 Model_ComputeScaledDistance(Vec3f* a, Vec3f* b, Vec3f* scale);
f32 Model_ComputeDistance(s16 (*a)[3], s16 (*b)[3]);
void Model_ExtrapolateVertexPosition(Vec3f* from, Vec3f* to, f32 currentTime, f32 deltaTime, f32 scale);

f32 Math_FAbs(f32 value);
s16 Model_GetVertexClass(s16* table, s32 index);
s16 Model_GetVertexMergeClass(s16* arg0, s32 arg1);
s16 Model_GetVertexTargetClass(s16* arg0, s32 arg1);
s16 Model_GetVertexSourceClass(s16* arg0, s32 arg1);
s16 Model_GetVertexMatrixClass(s16* arg0, s32 arg1);
void Model_TransformPoint(MtxF* mtx, Vec3f* out, s16 (*in)[3]);
void Model_AccumulateVertexOffset(MtxF* mtx, PosBlend* position, s16 (*target)[3], f32 alpha);
void Model_CopyPositionBuffer(PosBlend* src, PosBlend* dst);

void func_800350E0(void) {
}

void func_800350E8(ModelSegment* segment, MtxF* mtx, ModelVertex* mvtx) {
    ModelVertex* tmp;
    Vtx* vtx;
    PosBlend* position;
    s16* var_s7;
    s32 i;
    s16* temp_s5;
    temp_s5 = Memmap_GetSegmentVaddr(segment->tableSegment);
    vtx = Memmap_GetSegmentVaddr(segment->vertexSegment);
    var_s7 = Memmap_GetSegmentVaddr(segment->remapSegment);
    tmp = mvtx;

    for(i = 0; i < segment->vertexCount; i++) {
        position = &tmp->position;
        if (i == *var_s7) {
            switch (Model_GetVertexClass(temp_s5, i)) {
            case 0:
                Model_TransformPoint(mtx, &position->base, &vtx->v.ob);
                break;
            case 4:
                Model_TransformPoint(mtx + Model_GetVertexMatrixClass(temp_s5, i), &position->base, &vtx->v.ob);
                break;
            case 1:
                Model_AccumulateVertexOffset(mtx, position, &vtx->v.ob, D_80075894[Model_GetVertexMergeClass(temp_s5, i)]);
                break;
            case 2:
                Model_TransformPoint(mtx, &position->base, &vtx->v.ob);
                Model_CopyPositionBuffer(position, &D_800B32C8[Model_GetVertexTargetClass(temp_s5, i)]);
                break;
            case 3:
                Model_TransformPoint(mtx, &position->base, &vtx->v.ob);
                Model_CopyPositionBuffer(position, &D_800B32C8[Model_GetVertexSourceClass(temp_s5, i)]);
                break;
            default:
                break;
            }
        }
        vtx++;
        var_s7++;
        tmp++;
    }
}

/** Returns the distance between two points after applying a per-axis scale. */
f32 Model_ComputeScaledDistance(Vec3f* a, Vec3f* b, Vec3f* scale) {
    f32 dx;
    f32 dy;
    f32 dz;

    dx = (a->x - b->x) / scale->x;
    dy = (a->y - b->y) / scale->y;
    dz = (a->z - b->z) / scale->z;

    if (Math_FAbs(dx) < 10e-05f) {
        dx = 0.0f;
    }
    if (Math_FAbs(dy) < 10e-05f) {
        dy = 0.0f;
    }
    if (Math_FAbs(dz) < 10e-05f) {
        dz = 0.0f;
    }
    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

/** Returns the distance between two short-vector points. */
f32 Model_ComputeDistance(s16 (*a)[3], s16 (*b)[3]) {
    f32 dx;
    f32 dy;
    f32 dz;

    dx = (f32) ((*a)[0] - (*b)[0]);
    dy = (f32) ((*a)[1] - (*b)[1]);
    dz = (f32) ((*a)[2] - (*b)[2]);
    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

/**
 * Extrapolates a vertex position from two positions given the current time and
 * time step.
 */
void Model_ExtrapolateVertexPosition(Vec3f* from, Vec3f* to, f32 current_time, f32 delta_time, f32 scale) {
    s32 pad; // FAKE: stack padding
    f32 temp_fv0;
    f32 temp_fa1;
    f32 temp_ft5;

    if (delta_time < 10e-05f) {
        return;
    }

    temp_fv0 = to->x - from->x;
    temp_fa1 = to->y - from->y;
    temp_ft5 = to->z - from->z;

    scale *= (current_time - delta_time) / delta_time;
    if (delta_time < current_time) {
        scale /= 2.0f;
    }

    to->x += temp_fv0 * scale;
    to->y += temp_fa1 * scale;
    to->z += temp_ft5 * scale;
}
