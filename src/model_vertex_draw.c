/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/33FE0.c. */

#include "global.h"
#include "model_vertex_draw.h"
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

void func_80035500(PosBlend* src, PosBlend* dst, f32 totalTime, f32 elapsed, f32 stiffness);
void func_80035694(StadiumModel* model);
void Model_ApplyTransformCommands(ModelSegment* segment, ModelVertex* vertices, StadiumModel* model, f32 deltaTime);
void func_800359C0(ModelSegment* segment, ModelVertex* vertices, StadiumModel* model, f32 deltaTime);
void Model_OffsetVertexHeights(ModelSegment* segment, ModelVertex* vertices, f32 yOffset);
void func_80035BA8(ModelSegment* segment, ModelVertex* vertices, f32 yOffset);
void func_80035CCC(ModelSegment* segment, ModelVertex* vertices, f32 arg2, StadiumModel* arg3);
void func_80035E48(ModelSegment* segment, ModelVertex* vertices);
void func_80036064(StadiumModel* model, MtxF* mtx);
void Model_WriteVtxBuffer(StadiumModel* model, Vtx* vtxBuf);
Gfx* Model_Draw(Gfx* gfx, StadiumModel* model, Vtx* vtxBuf);

f32 Math_FAbs(f32 value);
s16 Model_GetVertexClass(s16* table, s32 index);
s16 Model_GetVertexThreshold(s16* arg0, s32 arg1);
s16 Model_GetVertexJoint(s16* arg0, s32 arg1);
s16 Model_GetVertexHeightClass(s16* arg0, s32 arg1);
void func_800341E8(ModelSegment* segment, ModelVertex* vertices);
void Model_ApplyVertexTransforms(StadiumModel* model);
void func_80034A74(u32 modelSegment, StadiumTransform* xf, s32 index, ModelVertex* vertices);
void func_800350E8(ModelSegment* segment, MtxF* mtx, ModelVertex* mvtx);
f32 Model_ComputeScaledDistance(Vec3f* a, Vec3f* b, Vec3f* scale);
f32 Model_ComputeDistance(s16 (*a)[3], s16 (*b)[3]);
void Model_ExtrapolateVertexPosition(Vec3f* from, Vec3f* to, f32 currentTime, f32 deltaTime, f32 scale);

void func_80035500(PosBlend* src, PosBlend* dst, f32 total_time, f32 elapsed, f32 stiffness) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 var_fv0;

    if (!(elapsed < 10e-05f)) {
        if (Math_FAbs(dst->base.x) < 10e-05f) {
            dst->base.x = 0.0f;
        }
        if (Math_FAbs(dst->base.y) < 10e-05f) {
            dst->base.y = 0.0f;
        }
        if (Math_FAbs(dst->base.z) < 10e-05f) {
            dst->base.z = 0.0f;
        }
        sp3C = dst->base.x - src->base.x;
        sp38 = dst->base.y - src->base.y;
        sp34 = dst->base.z - src->base.z;
        stiffness *= ((total_time - elapsed) / elapsed);
        if (elapsed < total_time) {
            stiffness /= 2.0f;
        }
        dst->base.x += sp3C * stiffness;
        dst->base.y += sp38 * stiffness;
        dst->base.z += sp34 * stiffness;
        dst->offset.x += sp3C * stiffness;
        dst->offset.y += sp38 * stiffness;
        dst->offset.z += sp34 * stiffness;
    }
}

void func_80035694(StadiumModel* model) {
    s32 i;
    s32 pad1[4]; // FAKE: stack padding
    s16* sp70;
    s32 pad2[1]; // FAKE: stack padding
    s16* sp68;
    s32 pad3[7]; // FAKE: stack padding
    ModelVertex* sp48;
    f32 temp_fv0;
    ModelSegment* sp40;
    s16 temp_s0;
    s16 temp_s1;
    s16 temp_s1_2;
    s16 temp_s2;
    s16 temp_s4;
    s16 temp_s4_2;
    s16 temp_s5;
    s16 temp_v0_2;
    s16* var_s6;
    s32 temp_t4;
    s32 temp_t7;
    Vtx* temp_fp;
    s16* temp_s3;
    ModelSegment* segment;
    ModelTransformCmd* cmd;
    ModelVertex* mvtx;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    sp40 = segment;
    temp_s3 = Memmap_GetSegmentVaddr(segment->tableSegment);
    sp70 = Memmap_GetSegmentVaddr(sp40->remapSegment);
    temp_fp = Memmap_GetSegmentVaddr(sp40->vertexSegment);
    sp68 = Memmap_GetSegmentVaddr(sp40->neighborSegment);
    mvtx = &model->mvtx;
    sp48 = mvtx;
    for (i = 0; i < sp40->vertexCount; i++) {
        temp_s2 = sp48->jointIndex;
        var_s6 = &sp68[sp48->parentIndex];
        while (1) {
            temp_v0_2 = *var_s6;
            var_s6++;
            if (temp_v0_2 == -1) {
                break;
            }
            temp_s0 = *(&sp70[temp_v0_2]);
            temp_s4 = Model_GetVertexJoint(temp_s3, temp_s2);
            temp_s5 = Model_GetVertexJoint(temp_s3, temp_s0);
            temp_s1 = Model_GetVertexThreshold(temp_s3, temp_s2);
            temp_t7 = Model_GetVertexThreshold(temp_s3, temp_s0) << 0x10;
            if ((temp_s4 < temp_s5) && (temp_s1 == (temp_t7 >> 0x10)) && (temp_s1 > 0)) {
                temp_s1_2 = Model_GetVertexClass(temp_s3, temp_s2);
                temp_s4_2 = Model_GetVertexClass(temp_s3, temp_s0);
                temp_fv0 = Model_ComputeDistance(&temp_fp[temp_s2].v.ob, &temp_fp[temp_s0].v.ob);
                cmd = &mvtx->cmd;
                mvtx++;
                cmd->targetIndex = temp_s2;
                cmd->sourceIndex = temp_s0;
                cmd->enableFrom = temp_s1_2;
                cmd->enableTo = temp_s4_2;
                cmd->blendWeight = temp_fv0;
            }
        }
        sp48++;
    }
    mvtx->cmd.targetIndex = -1;
    mvtx->cmd.sourceIndex = -1;
    mvtx->cmd.blendWeight = -1.0f;
}

/**
 * Applies a model segment's transform commands to its vertices over a time
 * step.
 */
void Model_ApplyTransformCommands(ModelSegment* segment, ModelVertex* vertices, StadiumModel* model, f32 delta_time) {
    f32 temp_fs0;
    f32 temp_fv0;
    s16 temp_v1;
    s16 var_a0;
    s16 var_a1;
    s16 var_a2;
    ModelTransformCmd* temp_v0;
    ModelVertex* temp_a3;
    Vec3f* temp_s0;
    Vec3f* temp_s1;
    ModelVertex* temp_v0_2;
    ModelVertex* var_s2;

    Memmap_GetSegmentVaddr(segment->remapSegment);
    var_s2 = vertices;

    while (1) {
        temp_v0 = &var_s2->cmd;
        var_s2++;
        temp_v1 = temp_v0->targetIndex;
        if (temp_v1 == -1) {
            break;
        }
    
        var_a1 = temp_v0->sourceIndex;
        var_a2 = temp_v0->enableFrom;
        var_a0 = temp_v0->enableTo;
        temp_fs0 = temp_v0->blendWeight;
        temp_a3 = &vertices[temp_v1];
    
        if (temp_a3->position.disabled != 0) {
            var_a2 = 0;
        }
    
        temp_v0_2 = &vertices[var_a1];
        if (temp_v0_2->position.disabled != 0) {
            var_a0 = 0;
        }
    
        if ((var_a0 != 0) || (var_a2 != 0)) {
            temp_fv0 = Model_ComputeScaledDistance(&temp_a3->position.base, &temp_v0_2->position.base, &model->scale);
            Model_ExtrapolateVertexPosition(&temp_a3->position.base, &temp_v0_2->position.base, temp_fs0, temp_fv0, delta_time);
        }
        
    }
}

void func_800359C0(ModelSegment* segment, ModelVertex* vertices, StadiumModel* model, f32 delta_time) {
    f32 temp_fs0;
    s16 temp_v1;
    s16 var_a0;
    s16 var_a1;
    s16 var_a2;
    ModelVertex* temp_a3;
    PosBlend* temp_s0;
    PosBlend* temp_s1;
    ModelTransformCmd* temp_v0;
    ModelVertex* temp_v0_2;
    ModelVertex* var_s2;

    Memmap_GetSegmentVaddr(segment->tableSegment);
    Memmap_GetSegmentVaddr(segment->remapSegment);
    var_s2 = vertices;
    while (1) {
        temp_v0 = &var_s2->cmd;
        var_s2++;
        temp_v1 = temp_v0->targetIndex;
        if (temp_v1 != -1) {
            var_a1 = temp_v0->sourceIndex;
            var_a2 = temp_v0->enableFrom;
            var_a0 = temp_v0->enableTo;
            temp_fs0 = temp_v0->blendWeight;
            temp_a3 = &vertices[temp_v1];
            if (temp_a3->position.disabled != 0) {
                var_a2 = 0;
            }
            temp_v0_2 = &vertices[var_a1];
            if (temp_v0_2->position.disabled != 0) {
                var_a0 = 0;
            }
            if ((var_a0 != 0) || (var_a2 != 0)) {
                temp_s0 = &temp_a3->position;
                temp_s1 = &temp_v0_2->position;
                func_80035500(temp_s0, temp_s1, temp_fs0, Model_ComputeScaledDistance(&temp_s0->base, &temp_s1->base, &model->scale), delta_time);
            }
            continue;
        }
        break;
    }
}

/** Offsets the heights of a segment's vertices by a y offset. */
void Model_OffsetVertexHeights(ModelSegment* segment, ModelVertex* vertices, f32 y_offset) {
    s16* index_table;
    s16* remap;
    s32 i;
    ModelVertex* tmp;

    index_table = Memmap_GetSegmentVaddr(segment->tableSegment);
    remap = Memmap_GetSegmentVaddr(segment->remapSegment);
    tmp = vertices;
    for(i = 0; i < segment->vertexCount; i++) {
        if ((Model_GetVertexClass(index_table, i) != 0) && (i == *remap)) {
            tmp->position.base.y += y_offset;
        }
        tmp++;
        remap++;
    }
}

void func_80035BA8(ModelSegment* segment, ModelVertex* vertices, f32 y_offset) {
    s16* index_table;
    s16* var_s2;
    s32 temp_v0;
    ModelVertex* tmp;
    s32 i;
    PosBlend* temp_v0_2;

    index_table = Memmap_GetSegmentVaddr(segment->tableSegment);
    var_s2 = Memmap_GetSegmentVaddr(segment->remapSegment);
    tmp = vertices;
    for(i = 0; i < segment->vertexCount; i++) {
        if ((Model_GetVertexClass(index_table, i) != 0) && (i == *var_s2)) {
            temp_v0 = Model_GetVertexHeightClass(index_table, i);
            temp_v0_2 = &tmp->position;
            switch (temp_v0) {
            case 1:
                temp_v0_2->base.y += y_offset;
                break;
            case 2:
                temp_v0_2->base.y += y_offset * 0.25f;
                break;
            }
        }
        tmp++;
        var_s2++;
    }
}

void func_80035CCC(ModelSegment* segment, ModelVertex* vertices, f32 arg2, StadiumModel* arg3) {
    s16* index_table;
    s16* remap;
    s32 type;
    ModelVertex* vertex;
    s32 i;
    PosBlend* position;
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 quarter = 0.25f;

    index_table = Memmap_GetSegmentVaddr(segment->tableSegment);
    remap = Memmap_GetSegmentVaddr(segment->remapSegment);
    vertex = vertices;
    for (i = 0; i < segment->vertexCount; i++) {
        if ((Model_GetVertexClass(index_table, i) != 0) && (i == *remap)) {
            type = Model_GetVertexHeightClass(index_table, i);
            position = &vertex->position;
            switch (type) {
            case 1:
                position->base.x += zero;
                position->base.y += arg2 * one;
                position->base.z += zero;
                break;
            case 2:
                position->base.x = position->base.x + zero;
                position->base.y = position->base.y + (quarter * arg2 * one);
                position->base.z = position->base.z + zero;
                break;
            }
        }
        vertex++;
        remap++;
    }
}

void func_80035E48(ModelSegment* segment, ModelVertex* vertices) {
    f32 drawGroup;
    s16* index_table;
    s16* remap;
    s32 i;
    PosBlend* position;
    ModelVertex* vertex;

    vertex = vertices;
    index_table = Memmap_GetSegmentVaddr(segment->tableSegment);
    remap = Memmap_GetSegmentVaddr(segment->remapSegment);
    for (i = 0; i < segment->vertexCount; i++) {
        position = &vertex->position;
        if ((Model_GetVertexClass(index_table, i) != 0) && (i == *remap)) {
            if (Math_FAbs(position->offset.x) < 9.999999747e-05f) {
                position->offset.x = 0.0f;
            }
            if (Math_FAbs(position->offset.y) < 9.999999747e-05f) {
                position->offset.y = 0.0f;
            }
            if (Math_FAbs(position->offset.z) < 9.999999747e-05f) {
                position->offset.z = 0.0f;
            }
            if ((s32)position->drawGroup > 0) {
                drawGroup = (f32)position->drawGroup;
                position->base.x = position->base.x + (position->offset.x / drawGroup);
                position->base.y = position->base.y + (position->offset.y / drawGroup);
                position->base.z = position->base.z + (position->offset.z / drawGroup);
                position->offset.x = position->offset.x - (0.3f * position->offset.x);
                position->offset.y = position->offset.y - (0.3f * position->offset.y);
                position->offset.z = position->offset.z - (0.3f * position->offset.z);
            } else {
                position->base.x = position->base.x + position->offset.x;
                position->base.y = position->base.y + position->offset.y;
                position->base.z = position->base.z + position->offset.z;
                position->offset.x = position->offset.x - (0.3f * position->offset.x);
                position->offset.y = position->offset.y - (0.3f * position->offset.y);
                position->offset.z = position->offset.z - (0.3f * position->offset.z);
            }
        }
        position->drawGroup = 0;
        vertex++;
        remap++;
    }
}

void func_80036064(StadiumModel* model, MtxF* mtx) {
    s32 var_s0;
    s32 var_v1;

    ModelVertex* mvtx = &model->mvtx;
    ModelSegment* segment = Memmap_GetSegmentVaddr(model->modelSegment);
    switch (segment->type) {
    case 3:
        func_800350E8(segment, mtx, mvtx);
        Model_OffsetVertexHeights(segment, mvtx, model->scale.y * -10.0f);
        func_800341E8(segment, mvtx);
        for(var_s0 = 0; var_s0 < model->transformCount; var_s0++) {
            func_80034A74(segment, &model->transforms[var_s0], var_s0, mvtx);
        }
        func_80035E48(segment, mvtx);
        Model_ApplyTransformCommands(segment, mvtx, model, 0.7f);        
        break;
    case 4:
        func_800350E8(segment, mtx, mvtx);
        Model_OffsetVertexHeights(segment, mvtx, model->scale.y * -10.0f);
        func_800341E8(segment, mvtx);
        func_80035E48(segment, mvtx);
        break;
    case 10:
        func_800350E8(segment, mtx, mvtx);
        func_80035BA8(segment, mvtx, model->scale.y * 160.0f);
        func_80035E48(segment, mvtx);
        func_800359C0(segment, mvtx, model, 1.0f);
        break;
    case 11:
        func_800350E8(segment, mtx, mvtx);
        func_80035CCC(segment, mvtx, 160.0f, model);
        func_80035E48(segment, mvtx);
        func_800359C0(segment, mvtx, model, 1.0f);
        break;
    case 1:
        func_800350E8(segment, mtx, mvtx);
        func_800341E8(segment, mvtx);
        func_80035E48(segment, mvtx);
        break;
    case 2:
        func_800350E8(segment, mtx, mvtx);
        Model_OffsetVertexHeights(segment, mvtx, model->scale.y * -10.0f);
        func_800341E8(segment, mvtx);
        func_80035E48(segment, mvtx);
        break;
    case 5:
        func_800350E8(segment, mtx, mvtx);
        func_800341E8(segment, mvtx);
        func_80035E48(segment, mvtx);
        break;
    case 6:
        func_800350E8(segment, mtx, mvtx);
        func_800341E8(segment, mvtx);
        func_80035E48(segment, mvtx);
        break;
    case 9:
        func_800350E8(segment, mtx, mvtx);
        Model_ApplyVertexTransforms(model);
        func_800341E8(segment, mvtx);
        break;
    default:
        return;
    }
    {
        s16* var_a0 = Memmap_GetSegmentVaddr(segment->remapSegment);
        for(var_v1 = 0; var_v1 < segment->vertexCount; var_v1++) {
            s16 segment_2 = *var_a0;
            if (segment_2 != var_v1) {
                 *(PosBlend*)&(var_v1 + mvtx)->position = *(PosBlend*)&mvtx[segment_2].position;
            }
            var_a0++;
        }
    }
}

/**
 * Writes a model's computed vertex positions into a display list vertex
 * buffer.
 */
void Model_WriteVtxBuffer(StadiumModel* model, Vtx* vtx_buf) {
    ModelSegment* segment;
    ModelVertex* mvtx;
    Vtx* vtx;
    s32 i;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    if ((s32) segment->type >= 0xC) {
        return;
    }
    mvtx = &model->mvtx;
    vtx = vtx_buf;
    for(i = 0; i < segment->vertexCount; i++) {
        vtx->v.ob[0] = (s16)(mvtx->position.base.x * 10.0f);
        vtx->v.ob[1] = (s16)(mvtx->position.base.y * 10.0f);
        vtx->v.ob[2] = (s16)(mvtx->position.base.z * 10.0f);
        vtx->v.cn[0] = (s16)mvtx->position.color.r;
        vtx->v.cn[1] = (s16)mvtx->position.color.g;
        vtx->v.cn[2] = (s16)mvtx->position.color.b;
        vtx->v.tc[0] = mvtx->position.texS;
        vtx->v.tc[1] = mvtx->position.texT;
        vtx->v.cn[3] = mvtx->position.alpha;
        vtx++;
        mvtx++;
    }
}

/**
 * Draws a model's segments using a vertex buffer and returns the advanced
 * display list pointer.
 */
Gfx* Model_Draw(Gfx* gfx, StadiumModel* model, Vtx* vtxBuf) {
    ModelSegment* segment;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    if ((s32) segment->type >= 0xC) {
        return gfx;
    }
    Model_WriteVtxBuffer(model, vtxBuf);
    gSPSegment(gfx++, 0x0E, vtxBuf);
    gSPMatrix(gfx++, &D_800B35C8, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(gfx++, segment->displayList);
    gSPPopMatrixN(gfx++, G_MTX_MODELVIEW, 1);
    return gfx;
}
