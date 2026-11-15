/* fragment040: the Dodrio Game Boy (Pocket) prize model shown on the cartridge check screen. */
#include "global.h"

#include "dodrio_game_boy_model.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"

extern Gfx D_8E923290[]; // Screen glare setup: two 32x32 I8 diagonal-stripe textures on tiles 0 and 1.
extern Gfx D_8E923340[]; // Screen glare quad over the Game Boy Pocket's screen.

/**
 * Geo callback on the Dodrio Game Boy (Pocket) prize model, the model fragment006 shows with
 * "ドードリオのゲームボーイ プレゼント!!" ("A Dodrio Game Boy for you!!") when
 * gSessionContext.transitionFlags has bit 4 (0x10) set. On the render pass (callContext 2) it
 * builds a display list that scrolls the two glare stripe layers across the screen in opposite
 * directions. The scroll values are 10.2 fixed-point S coordinates, so each layer moves a quarter
 * texel per frame and wraps after 0x80 (32 texels, one texture width).
 * Seen in play (2026-11-14): with transitionFlags = 0x10 the cartridge check screen showed this
 * model and its prize text, and a breakpoint here hit every frame. Raising the glare's primitive
 * alpha in D_8E923290 from 0x5A to 0xFF turned the moving diagonal stripes on the screen bright,
 * and stubbing the function with `jr ra` removed them.
 */
void DodrioGameBoy_ScrollScreenGlare(s32 callContext, GeoDisplayListNode* node) {
    static s32 sGlareScrollA;
    static s32 sGlareScrollB;

    if (callContext == 2) {
        node->displayList = Gfx_AllocDisplayList(0x20);
        sGlareScrollA++;
        if (sGlareScrollA >= 0x80) {
            sGlareScrollA = 0;
        }
        sGlareScrollB--;
        if (sGlareScrollB < 0) {
            sGlareScrollB = 0x7F;
        }
        gSPDisplayList(&node->displayList[0], D_8E923290);
        gDPSetTileSize(&node->displayList[1], G_TX_RENDERTILE, sGlareScrollA, 0, (sGlareScrollA + 0x1F) << 2, 0x7C);
        gDPSetTileSize(&node->displayList[2], 1, sGlareScrollB, 0, (sGlareScrollB + 0x1F) << 2, 0x7C);
        gSPBranchList(&node->displayList[3], D_8E923340);
    }
}
