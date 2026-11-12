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

s32 func_80033280(s32 arg0);
s32 func_800332B0(s32 arg0);
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
s16 Model_GetVertexThreshold(s16* arg0, s32 arg1);
s16 Model_GetVertexJoint(s16* arg0, s32 arg1);
s16 Model_GetVertexMergeClass(s16* arg0, s32 arg1);
s16 Model_GetVertexTargetClass(s16* arg0, s32 arg1);
s16 Model_GetVertexSourceClass(s16* arg0, s32 arg1);
s16 Model_GetVertexMatrixClass(s16* arg0, s32 arg1);

s32 func_80033280(s32 arg0) {
    u8 stack[4];
    u8* ptr = stack;

    return ((u8*)((s32)ptr + (arg0 * 0x94)) - ptr) + 0x170;
}

s32 func_800332B0(s32 arg0) {
    u8 stack[4];
    u8* ptr = stack;

    return ((u8*)(s32)ptr + (arg0 * 0x10)) - ptr;
}

f32 Math_FAbs(f32 value) {
    if (value < 0.0f) {
        value = -value;
    }
    return value;
}

void Math_CrossProduct(f32 ax, f32 ay, f32 az, f32 bx, f32 by, f32 bz, f32* cx, f32* cy, f32* cz) {
    *cx = (ay * bz) - (az * by);
    *cy = (az * bx) - (ax * bz);
    *cz = (ax * by) - (ay * bx);
}

f32 func_80033360(
    f32 px, f32 py, f32 pz,
    f32 ax, f32 ay, f32 az,
    f32 bx, f32 by, f32 bz
) {
    UNUSED s32 pad[4];
    f32 len_sq;

    len_sq = ((bx - ax) * (bx - ax)) + ((by - ay) * (by - ay)) + ((bz - az) * (bz - az));

    if (len_sq == 0.0f) {
        return 0.0f;
    }

    return (((bx - ax) * (px - ax)) + ((by - ay) * (py - ay)) + ((bz - az) * (pz - az))) / len_sq;
}

f32 func_80033408(
    f32 px, f32 py, f32 pz,
    f32 ax, f32 ay, f32 az,
    f32 bx, f32 by, f32 bz,
    f32* outX, f32* outY, f32* outZ
) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 sp68;
    f32 t;
    f32 ex;
    f32 ey;
    f32 ez;
    f32 dx2;
    f32 pad[1];
    f32 len_sq;

    len_sq = SQ(bx - ax) + SQ(by - ay) + SQ(bz - az);
    if (len_sq == 0.0f) {
        return -1.0f;
    }
    dx = bx - ax;
    dy = by - ay;
    dz = bz - az;
    dx2 = px - ax;

    sp68 = t = ((dx * dx2) + (dy * (py - ay)) + (dz * (pz - az))) / len_sq;
    if (t < -0.5f || t > 1.5f) {
        return -2.0f;
    }
    *outX = ex = ax + (sp68 * dx);
    *outY = ey = ay + (sp68 * dy);
    *outZ = ez = az + (sp68 * dz);

    return sqrtf(SQ(ex - px) + SQ(ey - py) + SQ(ez - pz));
}

s16 Model_GetVertexClass(s16* table, s32 index) {
    s16 temp;
    s16 slot = table[index];
    
    temp = D_80074C7C[slot];
    if (temp > 0) {
        return 0;
    }
    temp = D_80074A78[slot];
    if (temp > 0) {
        return 1;
    }
    temp = D_80074E80[slot];
    if (temp > 0) {
        return 2;
    }
    temp = D_80075084[slot];
    if (temp > 0) {
        return 3;
    }
    temp = D_80075288[slot];
    if (temp > 0) {
        return 4;
    }
    temp = D_8007548C[slot];
    if (temp > 0) {
        return 5;
    }
    temp = D_80075690[slot];
    if (temp > 0) {
        return 6;
    }
    return slot;
}

s16 Model_GetVertexThreshold(s16* arg0, s32 arg1) {
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = arg0[arg1];
    temp_v1 = D_80074874[temp_v0];

    if (temp_v1 > 0) {
        return temp_v1;
    }

    return 0;
}

s16 Model_GetVertexJoint(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_80074670[temp_v1];
    return temp_a2;
}

s16 Model_GetVertexMergeClass(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_80074A78[temp_v1];
    return temp_a2;
}

s16 Model_GetVertexTargetClass(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_80074E80[temp_v1];
    return temp_a2;
}

s16 Model_GetVertexSourceClass(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_80075084[temp_v1];
    return temp_a2;
}

s16 Model_GetVertexMatrixClass(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_80075288[temp_v1];
    return temp_a2;
}
