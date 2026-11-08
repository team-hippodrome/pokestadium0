/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/33FE0.c, src/DDC0.c. */

#include <PR/os_internal_reg.h>
#include "global.h"
#include "dp_intro.h"
#include "profiler.h"
#include "audio_loop_point.h"
#include "scheduler.h"
#include "gb_tower_audio.h"
#include "audio_commands.h"
#include "audio_category_fade.h"
#include "audio_sound_state.h"
#include "audio_channel.h"
#include "audio_loop_point.h"
typedef struct unk_D_800A8480 {
  /* 0x0000 */ OSThread thread;
  /* 0x01B0 */ char unk01B0[0x2030];
} unk_D_800A8480;
extern s32 D_800AAE30;
extern s32 D_800AAF3C;

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

void func_80033750(void);
s16 Model_GetVertexHeightClass(s16* arg0, s32 arg1);
void Model_BuildVertexRuntimeData(StadiumModel* model, MtxF* mtx);
void func_800339CC(StadiumModel* model, void* arg1,  void* arg2, void* arg3);
void func_80033BBC(StadiumModel* model, MtxF* mtx);
void func_80033BE4(StadiumModel* model, s16 maxDist, f32 radius, f32 ax, f32 ay, f32 az, f32 bx, f32 by, f32 bz, MtxF* mtx);
void func_800340F4(StadiumModel* model);
void func_800346C4(ModelSegment* segment, StadiumTransform* xf, s32 index, ModelVertex* vertices);
void Model_ApplyVertexTransforms(StadiumModel* model);
void func_80034A74(u32 modelSegment, StadiumTransform* xf, s32 index, ModelVertex* vertices);
void Model_TransformPoint(MtxF* mtx, Vec3f* out, s16 (*in)[3]);

f32 Math_FAbs(f32 value);
void Math_CrossProduct(f32 ax, f32 ay, f32 az, f32 bx, f32 by, f32 bz, f32* cx, f32* cy, f32* cz);
f32 func_80033360(
    f32 px, f32 py, f32 pz,
    f32 ax, f32 ay, f32 az,
    f32 bx, f32 by, f32 bz
);
f32 func_80033408(
    f32 px, f32 py, f32 pz,
    f32 ax, f32 ay, f32 az,
    f32 bx, f32 by, f32 bz,
    f32* outX, f32* outY, f32* outZ
);
s16 Model_GetVertexClass(s16* table, s32 index);
s16 Model_GetVertexJoint(s16* arg0, s32 arg1);
void Model_InitializeVertexPositions(ModelSegment* segment, MtxF* mtx, ModelVertex* mvtx);
void func_80035694(StadiumModel* model);
void Model_ApplyTransformCommands(ModelSegment* segment, ModelVertex* vertices, StadiumModel* model, f32 deltaTime);
void func_80035E48(ModelSegment* segment, ModelVertex* vertices);

void func_80033750(void) {
}

s16 Model_GetVertexHeightClass(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_80075690[temp_v1];
    return temp_a2;
}

void Model_BuildVertexRuntimeData(StadiumModel* model, MtxF* mtx) {
    ModelSegment* segment;
    ModelVertex* base;
    ModelVertex* mvtx;
    Vtx* vtx;
    s16* indexTable;
    s16 temp_t0;
    s16 temp_v0_2;
    s16 var_a1;
    s16* temp_s2;
    s32 i;
    s32 var_a0;
    s32 var_s3;
    UNUSED s32 pad[8];

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    base = &model->mvtx;
    mvtx = base;
    vtx = Memmap_GetSegmentVaddr(segment->vertexSegment);

    for (var_a0 = 0; var_a0 < segment->vertexCount; var_a0++) {

        mvtx->position.base.x = (f32)vtx->v.ob[0];
        mvtx->position.base.y = (f32)vtx->v.ob[1];
        mvtx->position.base.z = (f32)vtx->v.ob[2];
        mvtx->position.color.r = (s8)vtx->v.cn[0];
        mvtx->position.color.g = (s8)vtx->v.cn[1];
        mvtx->position.color.b = (s8)vtx->v.cn[2];
        mvtx->position.texS = vtx->v.tc[0];
        mvtx->position.texT = vtx->v.tc[1];
        mvtx->position.alpha = vtx->v.cn[3];
        mvtx->position.offset.x = 0.0f;
        mvtx->position.offset.y = 0.0f;
        mvtx->position.offset.z = 0.0f;
        mvtx->position.disabled = 0;
        mvtx->position.drawGroup = 0;
        mvtx++;
        vtx++;
    }

    mvtx = base;
    Model_InitializeVertexPositions(segment, mtx, base);

    var_s3 = 0;
    i = 0;
    while (var_s3 < 0x10) {
        temp_s2 = Memmap_GetSegmentVaddr(segment->tableSegment);
        for (i = 0; i < segment->vertexCount; i++) {
            u16 temp_v0 = Model_GetVertexJoint(temp_s2, i);
            if (var_s3 == temp_v0) {
                mvtx->jointIndex = i;
                mvtx++;
            }
        }
        var_s3++;
    }

    mvtx = base;
    var_a1 = 0;
    indexTable = Memmap_GetSegmentVaddr(segment->unk_0C);
    for (i = 0; i < segment->vertexCount; i++) {
        mvtx->childIndex = var_a1;
        do {
            temp_v0_2 = *indexTable++;
            var_a1++;
        } while (temp_v0_2 != -1);
        mvtx++;
    }

    mvtx = base;
    for (i = 0; i < segment->vertexCount; i++) {
        ModelVertex* temp_v0 = &base[mvtx->jointIndex];
        mvtx->parentIndex = temp_v0->childIndex;
        mvtx++;
    }
}

void func_800339CC(StadiumModel* model, void* arg1,  void* arg2, void* arg3) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    MtxF* temp_s0;
    ModelSegment* segment;
    ModelSegment* temp_v0;

    model = Memmap_GetSegmentVaddr(model);
    arg1 = Memmap_GetSegmentVaddr(arg1);
    temp_s0 = Memmap_GetSegmentVaddr(arg2);
    temp_v0 = Memmap_GetSegmentVaddr(arg3);
    segment = &model->unkSegment;
    D_800B32C0 = arg1;
    *segment = *temp_v0;
    model->unk_00 = 1;
    model->unk_02 = 0;
    model->modelSegment = segment;
    sp40 = temp_s0->xx;
    sp3C = temp_s0->yx;
    sp38 = temp_s0->zx;
    sp34 = temp_s0->xy;
    sp30 = temp_s0->yy;
    sp2C = temp_s0->zy;
    sp28 = temp_s0->xz;
    sp24 = temp_s0->yz;
    sp20 = temp_s0->zz;
    sp4C = sqrtf((sp40 * sp40) + (sp3C * sp3C) + (sp38 * sp38));
    sp48 = sqrtf((sp34 * sp34) + (sp30 * sp30) + (sp2C * sp2C));
    sp44 = sqrtf((sp28 * sp28) + (sp24 * sp24) + (sp20 * sp20));
    if (sp4C == 0.0f) {
        sp4C = 1.0f;
    }
    if (sp48 == 0.0f) {
        sp48 = 1.0f;
    }
    if (sp44 == 0.0f) {
        sp44 = 1.0f;
    }
    model->position.x = sp4C;
    model->position.y = sp48;
    model->position.z = sp44;
    guScale(&D_800B35C8, 0.1f, 0.1f, 0.1f);
    Model_BuildVertexRuntimeData(model, temp_s0);
    func_80035694(model);
}

void func_80033BBC(StadiumModel* model, MtxF* mtx) {
    Model_BuildVertexRuntimeData(model, mtx);
    func_80035694(model);
}

void func_80033BE4(StadiumModel* model, s16 maxDist, f32 radius, f32 ax, f32 ay, f32 az, f32 bx, f32 by, f32 bz, MtxF* mtx) {
    ModelSegment* segment;
    f32 cx, cy, cz;
    f32 dx, dy, dz;
    f32 tax, tay, taz;
    f32 tbx, tby, tbz;
    f32 tcx, tcy, tcz;
    f32 tdx, tdy, tdz;
    f32 x, y, z;
    f32 nx, ny, nz;
    f32 dir[3];
    ModelVertex* mvtx;
    f32 upX, upY, upZ;
    f32 px, py, pz;
    f32 dist;
    f32 len;
    ModelBlendWeight* w;
    f32 vx, vy, vz;
    StadiumTransform* t;
    s16 index;
    s32 i;

    segment = (ModelSegment*) Memmap_GetSegmentVaddr(model->modelSegment);
    index = model->unk_02++;

    vx = bx - ax;
    len = sqrtf((vx * vx) + ((by - ay) * (by - ay)) + ((bz - az) * (bz - az)));
    if (len != 0.0f) {
        upZ = upY = 0;
        upX = -1.0f;
        dir[2] = vx / len;
        dir[0] = (bz - az) / len;
        x = (by - ay) / len;
        dist = Math_FAbs((dir[0] * upZ) + ((x * upY) + (dir[2] * upX)));
        if (0.9f < dist) {
            upY = 1.0f;
            upX = 0.0f;
            upZ = 0.0f;
            if (0.9f < Math_FAbs(x)) {
                upZ = 1.0f;
                upY = 0.0f;
            }
        }
        Math_CrossProduct(dir[2], x, dir[0], upX, upY, upZ, &px, &py, &pz);
        cx = ax + px;
        cy = ay + py;
        cz = az + pz;
        Math_CrossProduct(dir[2], x, dir[0], px, py, pz, &px, &py, &pz);
        dx = ax + px;
        dy = ay + py;
        dz = az + pz;

        t = &model->transforms[index];
        t->unk_00 = maxDist;
        t->maxDist = radius;
        t->x0 = ax;
        t->y0 = ay;
        t->z0 = az;
        t->x1 = bx;
        t->y1 = by;
        t->z1 = bz;
        t->x2 = cx;
        t->y2 = cy;
        t->z2 = cz;
        t->x3 = dx;
        t->y3 = dy;
        t->z3 = dz;
        t->mtx = mtx;

        guMtxXFMF(mtx->mf, ax, ay, az, &tax, &tay, &taz);
        if (ax) {}
        guMtxXFMF(mtx->mf, bx, by, bz, &tbx, &tby, &tbz);
        guMtxXFMF(mtx->mf, cx, cy, cz, &tcx, &tcy, &tcz);
        guMtxXFMF(mtx->mf, dx, dy, dz, &tdx, &tdy, &tdz);

        mvtx = &model->mvtx;
        for (i = 0; i < segment->vertexCount; i++) {
            x = mvtx->position.base.x;
            y = mvtx->position.base.y;
            z = mvtx->position.base.z;
            dist = func_80033408(x, y, z, tax, tay, taz, tbx, tby, tbz, &nx, &ny, &nz);
            if (dist > 0.0f) {
                x = (((x - nx) * radius) / dist) + nx;
                y = (((y - ny) * radius) / dist) + ny;
                z = (((z - nz) * radius) / dist) + nz;
            }
            w = &mvtx->cmd.weights[index];
            w->w0 = func_80033360(x, y, z, tax, tay, taz, tbx, tby, tbz);
            w->w1 = func_80033360(x, y, z, tax, tay, taz, tcx, tcy, tcz);
            w->w2 = func_80033360(x, y, z, tax, tay, taz, tdx, tdy, tdz);
            w->dist = dist;
            mvtx++;
        }
    }
}

void func_800340F4(StadiumModel* model) {
    u32 pad[2];
    ModelSegment* segment;
    s16* indexTable;
    f32 var_fv0;
    s16 temp_v1;
    s32 j;
    s32 i;
    ModelVertex* temp_a1;
    ModelVertex* var_a2;
    ModelBlendWeight* var_a0;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    indexTable = Memmap_GetSegmentVaddr(segment->remapSegment);
    temp_a1 = &model->mvtx;
    var_a2 = temp_a1;
    for(i = 0; i < segment->vertexCount; i++) {
        var_a2->position.nextIndex = -1;
        var_a2++;
    }
    var_a2 = temp_a1;
    for (i = 0; i < segment->vertexCount; i++) {
        temp_v1 = indexTable[i];
        if (temp_v1 == i) {
            var_fv0 = 10000.0f;
            for (j = 0; j < model->unk_02; j++) {
                var_a0 = &var_a2->cmd.weights[j];
                if (var_a0->dist < var_fv0) {
                    var_fv0 = var_a0->dist;
                    var_a2->position.nextIndex = j;
                }
            }
        }
        var_a2++;
    }
}

void func_800341E8(ModelSegment* segment, ModelVertex* vertices) {
    s32 i;
    f32 x0, y0, z0;
    f32 x1, y1, z1;
    f32 x2, y2, z2;
    f32 nx, ny, nz;
    f32 len;
    s16 i0, i1, i2;
    f32 scale;
    s16* indices;
    s16 triangleCount;
    s16 vertexCount;
    ModelVertex* v0;
    ModelVertex* v1;
    ModelVertex* v2;
    ModelVertex* vtx;
    Vec3fCounter* counter;
    UNUSED s32 pad[4];
    s16* remap;
    UNUSED s32 pad2[4];

    triangleCount = segment->triangleCount;
    vertexCount = segment->vertexCount;
    indices = Memmap_GetSegmentVaddr(segment->indexSegment);
    remap = Memmap_GetSegmentVaddr(segment->remapSegment);
    counter = D_800B32C0;
    for (i = 0; i < vertexCount; i++) {
        counter->x = 0.0f;
        counter->y = 0.0f;
        counter->z = 0.0f;
        counter->count = 0;
        counter++;
    }
    for (i = 0; i < triangleCount; i++) {
        i0 = remap[indices[0]];
        v0 = &vertices[i0];
        x0 = v0->position.base.x;
        y0 = v0->position.base.y;
        z0 = v0->position.base.z;
        i1 = remap[indices[1]];
        v1 = &vertices[i1];
        x1 = v1->position.base.x;
        y1 = v1->position.base.y;
        z1 = v1->position.base.z;
        i2 = remap[indices[2]];
        v2 = &vertices[i2];
        x2 = v2->position.base.x;
        y2 = v2->position.base.y;
        z2 = v2->position.base.z;
        indices += 3;
        nx = ((y1 - y0) * (z2 - z1)) - ((z1 - z0) * (y2 - y1));
        ny = ((z1 - z0) * (x2 - x1)) - ((x1 - x0) * (z2 - z1));
        nz = ((x1 - x0) * (y2 - y1)) - ((y1 - y0) * (x2 - x1));
        len = sqrtf((nx * nx) + (ny * ny) + (nz * nz));
        if ((s32) len > 0) {
            nx = (nx * 120.0f) / len;
            ny = (ny * 120.0f) / len;
            nz = (nz * 120.0f) / len;
        }
        counter = &D_800B32C0[i0];
        counter->x += nx;
        counter->y += ny;
        counter->z += nz;
        counter->count++;
        counter = &D_800B32C0[i0];
        counter->x += nx;
        counter->y += ny;
        counter->z += nz;
        counter->count++;
        counter = &D_800B32C0[i0];
        counter->x += nx;
        counter->y += ny;
        counter->z += nz;
        counter->count++;
    }
    counter = D_800B32C0;
    vtx = vertices;
    for (i = 0; i < vertexCount; i++) {
        if (counter->count > 0) {
            len = counter->count;
            vtx->position.color.r = counter->x / len;
            vtx->position.color.g = counter->y / len;
            vtx->position.color.b = counter->z / len;
        }
        counter++;
        vtx++;
    }
}

void func_800346C4(ModelSegment* segment, StadiumTransform* xf, s32 index, ModelVertex* vertices) {
    f32 x0, y0, z0;
    f32 x1, y1, z1;
    f32 x2, y2, z2;
    MtxF* mtx;
    s32 pad0[4];
    f32 sp184, sp180, sp17C;
    f32 sp178, sp174, sp170;
    f32 sp16C, sp168, sp164;
    f32 sp160, sp15C, sp158;
    f32 sp154, sp150, sp14C;
    f32 sp148, sp144, sp140;
    f32 sp13C, sp138, sp134;
    f32 sp130, sp12C, sp128;
    f32 w0, w1, w2;
    f32 bx, by, bz;
    s32 pad1[27];
    s16* spA0;
    s16 temp_s6;
    s16* temp_v0;
    s32 i;
    s32 temp_s0;
    ModelVertex* var_s1;
    PosBlend* temp_v0_2;

    temp_s6 = segment->vertexCount;
    spA0 = Memmap_GetSegmentVaddr(segment->remapSegment);
    temp_v0 = Memmap_GetSegmentVaddr(segment->tableSegment);
    x0 = xf->x0;
    y0 = xf->y0;
    z0 = xf->z0;
    x1 = xf->x1;
    y1 = xf->y1;
    z1 = xf->z1;
    x2 = xf->x2;
    y2 = xf->y2;
    z2 = xf->z2;
    sp184 = xf->x3;
    sp180 = xf->y3;
    sp17C = xf->z3;
    mtx = xf->mtx;

    guMtxXFMF(mtx->mf, x0, y0, z0, &sp178, &sp174, &sp170);
    guMtxXFMF(mtx->mf, x1, y1, z1, &sp16C, &sp168, &sp164);
    guMtxXFMF(mtx->mf, x2, y2, z2, &sp160, &sp15C, &sp158);
    guMtxXFMF(mtx->mf, sp184, sp180, sp17C, &sp154, &sp150, &sp14C);
    sp148 = sp16C - sp178;
    sp144 = sp168 - sp174;
    sp140 = sp164 - sp170;
    sp13C = sp160 - sp178;
    sp138 = sp15C - sp174;
    sp134 = sp158 - sp170;
    sp130 = sp154 - sp178;
    sp12C = sp150 - sp174;
    sp128 = sp14C - sp170;
    var_s1 = vertices;
    for (i = 0; i < temp_s6; i++) {
        temp_s0 = spA0[i];
        if (Model_GetVertexClass(temp_v0, temp_s0) != 0) {
            temp_v0_2 = &var_s1->position;
            if (temp_s0 == i) {
                if (index == temp_v0_2->nextIndex) {
                    w0 = var_s1->cmd.weights[index].w0;
                    w1 = var_s1->cmd.weights[index].w1;
                    w2 = var_s1->cmd.weights[index].w2;
                    x1 = (w0 * sp148) + sp178 + (w1 * sp13C) + (w2 * sp130);
                    y1 = (w0 * sp144) + sp174 + (w1 * sp138) + (w2 * sp12C);
                    bx = temp_v0_2->base.x;
                    by = temp_v0_2->base.y;
                    bz = temp_v0_2->base.z;
                    z1 = (w0 * sp140) + sp170 + (w1 * sp134) + (w2 * sp128);
                    temp_v0_2->disabled |= (1 << index);
                    temp_v0_2->offset.x = x1 - bx;
                    temp_v0_2->offset.y = y1 - by;
                    temp_v0_2->offset.z = z1 - bz;
                }
            }
        }
        var_s1++;
    }
}

void Model_ApplyVertexTransforms(StadiumModel* model) {
    ModelSegment* segment;
    s32 count;
    s32 i;
    ModelVertex* mvtx;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    mvtx = &model->mvtx;
    count = model->unk_02;

    for (i = 0; i < count; i++) {
        func_800346C4(segment, &model->transforms[i], i, mvtx);
    }

    func_80035E48(segment, mvtx);
    Model_ApplyTransformCommands(segment, mvtx, model, 1.0f);
}

void func_80034A74(u32 modelSegment, StadiumTransform* xf, s32 index, ModelVertex* vertices) {
    ModelBlendWeight* wt;
    ModelVertex* vtx;
    s32 pad0[3];
    f32 sp180;
    f32 sp17C;
    f32 sp178;
    f32 sp174;
    f32 sp170;
    f32 sp16C;
    f32 sp168;
    f32 sp164;
    f32 sp160;
    f32 sp15C;
    f32 sp158;
    f32 sp154;
    f32 sp150;
    f32 sp14C;
    f32 sp148;
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    s32 pad1[10];
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 one = 1.0f;
    f32 w0;
    f32 w1;
    f32 w2;
    f32 x;
    f32 y;
    f32 z;
    f32 temp_fv0;
    s32 pad2[4];
    s16 spCA;
    s32 pad3[1];
    s16* spC0;
    MtxF* mtx;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    s16 temp_s1_2;
    s16* temp_s1;
    ModelSegment* temp_v0;
    s32 temp_s1_3;
    s32 i;
    PosBlend* temp_v0_2;

    temp_v0 = Memmap_GetSegmentVaddr(modelSegment);
    spCA = temp_v0->vertexCount;
    temp_s1 = Memmap_GetSegmentVaddr(temp_v0->remapSegment);
    spC0 = Memmap_GetSegmentVaddr(temp_v0->tableSegment);
    mtx = xf->mtx;
    guMtxXFMF(mtx->mf, xf->x0, xf->y0, xf->z0, &sp180, &sp17C, &sp178);
    guMtxXFMF(mtx->mf, xf->x1, xf->y1, xf->z1, &sp174, &sp170, &sp16C);
    guMtxXFMF(mtx->mf, xf->x2, xf->y2, xf->z2, &sp168, &sp164, &sp160);
    guMtxXFMF(mtx->mf, xf->x3, xf->y3, xf->z3, &sp15C, &sp158, &sp154);
    sp150 = sp174 - sp180;
    sp14C = sp170 - sp17C;
    sp148 = sp16C - sp178;
    sp144 = sp168 - sp180;
    sp140 = sp164 - sp17C;
    sp13C = sp160 - sp178;
    sp138 = sp15C - sp180;
    sp134 = sp158 - sp17C;
    sp130 = sp154 - sp178;
    vtx = vertices;
    for (i = 0; i < spCA; i++) {
        temp_s1_2 = temp_s1[i];
        if ((Model_GetVertexClass(spC0, temp_s1_2) != 0) && (temp_s1_2 == i)) {
            temp_fs0 = vtx->position.base.x;
            temp_fs1 = vtx->position.base.y;
            temp_fs2 = vtx->position.base.z;
            temp_s1_3 = 1 << index;
            temp_fv0 = func_80033408(temp_fs0, temp_fs1, temp_fs2, sp180, sp17C, sp178, sp174, sp170, sp16C, &sp104, &sp100, &spFC);
            temp_v0_2 = &vtx->position;
            if ((temp_fv0 > 0.0f) && (temp_fv0 < xf->maxDist)) {
                wt = &vtx->cmd.weights[index];
                w0 = wt->w0;
                w1 = wt->w1;
                w2 = wt->w2;
                x = (w0 * sp150) + sp180 + (w1 * sp144) + (w2 * sp138);
                y = (w0 * sp14C) + sp17C + (w1 * sp140) + (w2 * sp134);
                z = (w0 * sp148) + sp178 + (w1 * sp13C) + (w2 * sp130);
                temp_v0_2->disabled |= temp_s1_3;
                temp_v0_2->offset.x = (x - temp_fs0) * one;
                temp_v0_2->offset.y = (y - temp_fs1) * one;
                temp_v0_2->offset.z = (z - temp_fs2) * one;
            } else {
                temp_v0_2->disabled &= ~temp_s1_3;
            }
        }
        vtx++;
    }
}

void Model_TransformPoint(MtxF* mtx, Vec3f* out, s16 (*in)[3]) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    sp34 = (f32) (*in)[0];
    sp30 = (f32) (*in)[1];
    sp2C = (f32) (*in)[2];

    guMtxXFMF(mtx->mf, sp34, sp30, sp2C, &sp34, &sp30, &sp2C);

    out->x = sp34;
    out->y = sp30;
    out->z = sp2C;
}
