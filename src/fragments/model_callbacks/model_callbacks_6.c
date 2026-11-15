/* Stadium Zero fragment 001 (model callbacks): Dual scrolling texture callback (Grimer, Muk). */
#include "global.h"
#include "model_callbacks.h"
#include "gfx_buffer.h"
#include "geo_render.h"
#include "model_renderer_callbacks.h"
#include "battle_hud.h"
#include "vector_math.h"

/**
 * Builds a display list with two texture layers that scroll by the counters at D_81002C20,
 * stepped with D_800AFB28, but only while the current model's textureMode is 0.
 * Still asm (docs/function-matches.csv lists it as asm), so the signature is a guess from the
 * caller: (Gfx* gfx, DisplayListAddresses* addresses).
 * @unverified Only Grimer and Muk use it, and neither can battle in Stadium Zero.
 */
#ifdef NON_MATCHING
/* TODO: decompile func_81001CE0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment001_15B1A0/func_81001CE0.s")
#endif

/**
 * Phase 2: builds func_81001CE0, two scrolling texture layers.
 * @unverified Only Grimer and Muk use it, and neither can battle in Stadium Zero.
 */
void ModelCallback_DualScrollTexture(s32 phase, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (phase == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(240);
        state->gfx = gfx;
        func_81001CE0(gfx, addresses);
    }
}
