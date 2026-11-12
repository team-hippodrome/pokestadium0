/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/model_renderer_callbacks.c. */

#include "model_renderer_callbacks.h"
#include "geo_render.h"
#include "gallery.h"
#include "battle_hud.h"
#include "33FE0.h"
#include "gfx_buffer.h"
#include "matrix.h"
typedef struct StadiumModelSlot {
    /* 0x000 */ StadiumModel model;
    /* 0x204 */ char pad204[0x5CC];
} StadiumModelSlot;
typedef struct unk_func_80032F94_a0 {
    /* 0x00 */ u8 pad00[0x18];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} unk_func_80032F94_a0;
typedef struct unk_D_800B2EA8 {
    u8 unk_00[0xA8];
} unk_D_800B2EA8;
typedef struct {
    MtxF mtx[16];   // 16 (0x10) × 0x40 = 0x400
} MtxBuffer;
extern MtxBuffer D_800AFB38[2];
extern StadiumModelSlot D_800B0338[2][3];

void ModelRenderer_CacheSlotMatrices(u8 arg0);
void ModelRenderer_ApplySlotScale(u8 index);
void ModelRenderer_RebuildSlotMatrix(u8 index);
void ModelRenderer_ClearSlotModels(s32 arg0);

void func_80032840(u32 arg0) {
    s32 i;
    StadiumModelSlot* slot;

    if (arg0 < 4) {
        arg0 &= 1;
        for (i = 0; i < 3; i++) {
            slot = &D_800B0338[arg0][i];
            if (slot) {  // karodo
            }
        }
        if (slot) { // FAKE: no-op test; changes register allocation to match
        }
    }
}

extern s16 D_800AFB30[];

s32 func_80032890(u32 arg0) {
    if (arg0 >= 4) {
        return 1;
    }
    arg0 &= 1;
    if (D_800AFB30[arg0] == 3) {
        return 1;
    }
    return 0;
}

void ModelRenderer_CacheSlotMatrices(u8 arg0) {
    MtxF_Copy(D_800AFB38[arg0].mtx, GeoRender_GetRelativeMatrix(0));
    MtxF_Copy(D_800AFB38[arg0].mtx[1].mf, GeoRender_GetRelativeMatrix(-1));
}

void ModelRenderer_ApplySlotScale(u8 index) {
    MtxF* temp_a1;
    MtxF sp1C;

    temp_a1 = &D_800AFB38[index];
    MtxF_ExtractScale(&sp1C, &D_80060488->view.floatMatrix);
    guMtxCatF(sp1C.mf, temp_a1->mf, temp_a1->mf);
}

void ModelRenderer_RebuildSlotMatrix(u8 index) {
    MtxF* temp_a0;
    
    s32 pad[2]; // FAKE: stack padding
    f32 spC0;
    f32 spBC;
    f32 spB8;
    
    MtxF sp78;
    MtxF sp38;
    Vec3f sp2C;
    
    temp_a0 = &D_800AFB38[index].mtx;
    
    MtxF_GetScaleVector(temp_a0, &sp2C);
    guScaleF(sp38.mf, sp2C.x, sp2C.y, sp2C.z);
    guMtxXFMF(temp_a0->mf, 0.0f, 0.0f, 0.0f, &spC0, &spBC, &spB8);
    guTranslateF(sp78.mf, spC0, spBC, spB8);
    guMtxCatF(sp38.mf, sp78.mf, temp_a0->mf);
}

void ModelRenderer_ClearSlotModels(s32 arg0) {
    s32 i;
    StadiumModelSlot* slot = &D_800B0338[arg0];

    for (i = 0; i < 3; i++) {
        slot[i].model.unk_00 = 0;
    }
}

extern s16 D_800AFB28;
extern unk_D_800B2EA8 D_800B3218[];
extern u8 D_80075C10[];
extern u8 D_80075A68[];

void ModelRenderer_UpdateSlotModel(void) {
    u8 index;
    s32 mode;

    mode = ModelRenderer_GetActiveMode();
    index = (u8)mode;
    if (mode < 2) {
        ModelRenderer_CacheSlotMatrices(index);
        ModelRenderer_RebuildSlotMatrix(index);
        ModelRenderer_ApplySlotScale(index);

        if (D_8006049C->objectType == 0x92) {
            func_800339CC(&D_800B0338[index][D_800AFB28].model, D_800B3218, D_800AFB38[index].mtx, D_80075C10);
            return;
        }
        func_800339CC(&D_800B0338[index][D_800AFB28].model, D_800B3218, D_800AFB38[index].mtx, D_80075A68);
    }
}

extern s16 D_800AF7C0[4];
extern s16 D_800AFB30[];
extern s16 D_800AFB28;

void ModelRenderer_UpdateSlotVertices(void) {
    u8 index;
    s32 mode;

    mode = ModelRenderer_GetActiveMode();
    index = (u8)mode;
    if ((mode < 2) && (ModelPhase_IsIdle() == 0) && (D_800AFB30[index] >= 2)) {
        ModelRenderer_CacheSlotMatrices(index);
        ModelRenderer_RebuildSlotMatrix(index);
        ModelRenderer_ApplySlotScale(index);
        // Zero model slots are 0x7D0 bytes.
        func_80036064((void*)((u8 (*)[3][0x7D0])D_800B0338)[index][D_800AFB28], &D_800AFB38[index].mtx);
    }
}

extern Gfx D_800744D8[];
extern Gfx D_80074540[];
extern u16 D_80060484;
Gfx* func_80032C74(Gfx* gfx) {
    switch (D_8006049C->objectType) {
        default:
            gSPDisplayList(gfx++, D_800744D8);
            gDPSetEnvColor(gfx++, 0xB4 - (D_80060484 % 8) * 10, 0x20, 0x00, 0x00);
            break;
        case 0x92:
            gSPDisplayList(gfx++, D_80074540);
            gDPSetEnvColor(gfx++, 0xFF, 0x20, 0x00, 0x00); // #FF200000
            break;
        case 0x7E:
            gSPDisplayList(gfx++, D_800744D8);
            gDPSetEnvColor(gfx++, 0xFF, 0x20, 0x00, 0x00); // #FF200000
            gDPSetPrimColor(gfx++, 0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0xFF); // #FFFF05FF
            break;
    }
    return gfx;
}

Gfx* func_80032C74(Gfx*);
void func_80032A6C(void);
extern Gfx D_80074410[];
extern Gfx D_800744C0[];
Gfx* func_80032D90(Gfx* gfx) {
    u8 mode;
    void* vtx;

    mode = ModelRenderer_GetActiveMode();
    if (mode >= 4) {
        return gfx;
    }
    if (mode >= 2) {
        mode &= 1;
        if (D_800AFB30[mode] >= 2) {
            Gfx_AllocDisplayList(0xA0);
            gfx = func_80032C74(gfx);
            {
                ModelSegment* segment = (ModelSegment*)(&D_800B0338[mode][D_800AFB28].model.unkSegment);
                {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDB060038;    _gfx->words.w1 = (s32) segment->vertexSegment;    }
                {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDE000000;    _gfx->words.w1 = (s32) segment->displayList;    }
                {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDE000000;    _gfx->words.w1 = (s32) D_800744C0;    }
            }
            D_800AFB28++;
        }
        return gfx;
    }
    switch (D_800AFB30[mode]) {
        case 1:
            func_80032A6C();
            break;
        case 2:
        case 3:
            vtx = Gfx_AllocDisplayList(0xA0);
            {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDA380002;    _gfx->words.w1 = (s32) D_80074410;    }
            gfx = func_80032C74(gfx);
            gfx = Model_Draw(gfx, &D_800B0338[mode][D_800AFB28].model, vtx);
            {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xD8380002;    _gfx->words.w1 = 0x40;    }
            {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDE000000;    _gfx->words.w1 = (s32) D_800744C0;    }
            break;
    }
    D_800AFB28++;
    return gfx;
}
