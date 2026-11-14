/* Stadium Zero fragment 001 (model callbacks): Fixed and texture-mode-dependent segment callbacks. */
#include "global.h"
#include "model_callbacks.h"
#include "gfx_buffer.h"
#include "geo_render.h"
#include "model_renderer_callbacks.h"
#include "battle_hud.h"
#include "vector_math.h"

/**
 * Builds a display list that calls both segments.
 * @unverified No model data uses this callback.
 */
void ModelCallback_BuildTwoSegmentList(Gfx* gfx, DisplayListAddresses* addresses) {
    gSPDisplayList(gfx++, addresses->segments[0]);
    gSPDisplayList(gfx++, addresses->segments[1]);
    gSPEndDisplayList(gfx++);
}

/**
 * Phase 2: builds ModelCallback_BuildTwoSegmentList.
 * @unverified No model data uses this callback.
 */
void ModelCallback_TwoSegments(s32 phase, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (phase == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(0x18);
        state->gfx = gfx;
        ModelCallback_BuildTwoSegmentList(gfx, addresses);
    }
}

/**
 * Builds a display list that calls the segment only while the current model's textureMode is 0.
 */
void ModelCallback_BuildDefaultModeList(Gfx* gfx, s32* address) {
    if (D_8006049C->textureMode == 0) {
        gSPDisplayList(gfx++, *address);
    }
    gSPEndDisplayList(gfx++);
}

/**
 * Phase 2: builds ModelCallback_BuildDefaultModeList. Ditto's model data uses it; hit for Ditto in play.
 */
void ModelCallback_DefaultModeSegment(s32 phase, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (phase == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(0x50);
        state->gfx = gfx;
        ModelCallback_BuildDefaultModeList(gfx, addresses);
    }
}
