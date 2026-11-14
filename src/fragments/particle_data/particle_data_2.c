/* Stadium Zero fragment031_3553C0. */
/* C ported from the Stadium 1 decomp: src/fragments/particle_data_library/particle_data_library_257DE0.c. */

#include "particle_data.h"
#include "geo_render.h"
#include "gfx_buffer.h"

#include "m2c_macros.h"

extern Gfx D_8F2128D0[];
extern void* D_8F212910[];
extern u16 D_80060484;

void DisplayList_InitRotationMatrixSegment(s32 arg0, DisplayListState* state);
Gfx* func_8F200160(Gfx* gfx, s32 frame, Gfx* next);
Gfx* func_8F200290(Gfx* gfx, Gfx* next);

void DisplayList_BuildRotationMatrixSegment(Gfx* gfx);

Gfx* func_8F200160(Gfx* gfx, s32 frame, Gfx* next) {
    gSPDisplayList(gfx++, D_8F2128D0);
    gDPLoadTextureBlock(gfx++, D_8F212910[frame], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5,
                        5, 1, 1);
    gSPDisplayList(gfx++, next);
    gSPEndDisplayList(gfx++);
    return gfx;
}

void func_8F200244(s32 arg0, GeoDisplayListNode* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(0x50);
        func_8F200160(arg1->displayList, D_80060484 & 7, (Gfx*)arg1->node.callbackArg);
    }
}

Gfx* func_8F200290(Gfx* gfx, Gfx* next) {
    static s32 D_8F212930;

    D_8F212930--;
    if (D_8F212930 < 0) {
        D_8F212930 = 0x80;
    }
    gSPDisplayList(gfx++, D_8F2128D0);
    gDPLoadTextureBlock(gfx++, D_8F212910[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_CLAMP, 5,
                        5, 1, 1);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, D_8F212930, 0, (D_8F212930 + 0x1F) << 2, 0x7C);
    gSPDisplayList(gfx++, next);
    gSPEndDisplayList(gfx++);
    return gfx;
}

void func_8F2003AC(s32 arg0, GeoDisplayListNode* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(0x58);
        func_8F200290(arg1->displayList, (Gfx*)arg1->node.callbackArg);
    }
}

Gfx* func_8F2003EC(Gfx* gfx) {
    static s32 D_8F212934;

    D_8F212934--;
    if (D_8F212934 < 0) {
        D_8F212934 = 0x80;
    }
    gSPDisplayList(gfx++, D_8F2128D0);
    gDPLoadTextureBlock(gfx++, D_8F212910[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_CLAMP, 5,
                        5, 1, 1);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, D_8F212934, 0, (D_8F212934 + 0x1F) << 2, 0x7C);
    gSPEndDisplayList(gfx++);
    return gfx;
}

/** Initializes a display list segment holding a rotation matrix. */
void DisplayList_InitRotationMatrixSegment(s32 arg0, DisplayListState* state) {
    Gfx* gfx;

    if (arg0 == 2) {
        gfx = (Gfx*)Gfx_AllocDisplayList(0x50);
        state->gfx = gfx;
        DisplayList_BuildRotationMatrixSegment(gfx);
    }
}
