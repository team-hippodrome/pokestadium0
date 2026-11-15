/* fragment039: the Doduo Game Boy (Pocket) prize model shown on the cartridge check screen. */
#include "global.h"

#include "doduo_game_boy_model.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"

extern Gfx D_8E824B00[]; // Screen glare setup: two 32x32 I8 diagonal-stripe textures on tiles 0 and 1.
extern Gfx D_8E824BB0[]; // Screen glare quad over the Game Boy Pocket's screen.

/**
 * Geo callback on the Doduo Game Boy (Pocket) prize model, the model fragment006 shows with
 * "ドードーのゲームボーイ プレゼント!!" ("A Doduo Game Boy for you!!") when
 * gSessionContext.transitionFlags has bit 3 set. On the render pass (callContext 2) it builds a
 * display list that scrolls the two glare stripe layers across the screen in opposite directions,
 * one texel per frame, wrapping at 128 (0x80 texels in 10.2 fixed point is 32 texels).
 * Seen in play (2026-11-14): with transitionFlags = 8 the cartridge check screen showed this model;
 * both counters advanced every frame (one up, one down), and stubbing the function with `jr ra`
 * froze them and removed the moving glare from the screen.
 */
void DoduoGameBoy_ScrollScreenGlare(s32 call_context, GeoDisplayListNode* node) {
    static s32 sGlareScrollA;
    static s32 sGlareScrollB;

    if (call_context == 2) {
        node->displayList = Gfx_AllocDisplayList(0x20);
        sGlareScrollA++;
        if (sGlareScrollA >= 0x80) {
            sGlareScrollA = 0;
        }
        sGlareScrollB--;
        if (sGlareScrollB < 0) {
            sGlareScrollB = 0x7F;
        }
        gSPDisplayList(&node->displayList[0], D_8E824B00);
        gDPSetTileSize(&node->displayList[1], G_TX_RENDERTILE, sGlareScrollA, 0, (sGlareScrollA + 0x1F) << 2, 0x7C);
        gDPSetTileSize(&node->displayList[2], 1, sGlareScrollB, 0, (sGlareScrollB + 0x1F) << 2, 0x7C);
        gSPBranchList(&node->displayList[3], D_8E824BB0);
    }
}
