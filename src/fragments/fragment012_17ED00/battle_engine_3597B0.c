/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3597B0.c. */

#include "fragments/battle_engine/battle_engine.h"
extern s16 D_821CF270;
extern s16 D_821CF272;
extern s16 D_821CF274;
extern Gfx D_821941F0[];
extern s32 pad_D_8438AA58[];
extern u32 D_821942D8[];
extern Gfx D_82194458[];
extern Gfx D_821944A0[];

void BattleScene_SetStripWipeState(s32 arg0, s32 arg1);
s32 BattleScene_GetStripWipeState(void);
void BattleScene_UpdateStripWipe(void);
Gfx* BattleScene_BuildStripWipeDisplayList(Gfx* arg0, s32 arg1);
void BattleScene_DrawStripWipe(void);

/**
 * Sets the strip wipe state (0 off, 1 covered, 2 opening, 3 closing) and its speed. The
 * wipe position starts at 320 (screen width) for states 0 and 3, otherwise at 0.
 * @unverified Name from Stadium 1.
 */
void BattleScene_SetStripWipeState(s32 arg0, s32 arg1) {
    D_821CF270 = arg0;
    D_821CF274 = arg1;

    if ((D_821CF270 == 0) || ((D_821CF270 != 1) && (D_821CF270 != 2) && (D_821CF270 == 3))) {
        D_821CF272 = 320;
    } else {
        D_821CF272 = 0;
    }
}

/**
 * Returns the strip wipe state.
 * @unverified Name from Stadium 1.
 */
s32 BattleScene_GetStripWipeState(void) {
    return D_821CF270;
}

/**
 * Moves the strip wipe by its speed: opening runs to the screen width (320) and turns the
 * wipe off, closing runs to 0 and leaves the screen covered.
 * @unverified Name from Stadium 1.
 */
void BattleScene_UpdateStripWipe(void) {
    s16 var_v0 = D_821CF272;

    switch (D_821CF270) {
        case 2:
            if (var_v0 < 320) {
                var_v0 += D_821CF274;
            } else {
                D_821CF270 = 0;
            }
            break;

        case 3:
            if (var_v0 > 0) {
                var_v0 -= D_821CF274;
            } else {
                D_821CF270 = 1;
            }
            if (var_v0 < 0) {
                var_v0 = 0;
            }
            break;
    }
    D_821CF272 = var_v0;
}

/**
 * Adds the display list that draws the strip wipe at its current position; arg1 picks the
 * strip direction. Returns the new end of the list.
 * @unverified Name from Stadium 1.
 */
Gfx* BattleScene_BuildStripWipeDisplayList(Gfx* arg0, s32 arg1) {
    s32 i;
    s16 left;
    s16 top;
    s32 temp_a1;
    s32 temp_v1;

    temp_a1 = arg1 & 1;
    temp_v1 = (arg1 + 1) & 1;

    gSPDisplayList(arg0++, D_82194458);
    gDPLoadTextureBlock_4b(arg0++, D_821942D8, G_IM_FMT_I, 12, 48, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(arg0++);

    for (i = temp_a1; i < 5; i += 2) {
        left = D_821CF272 * 2 - 320;
        top = i * 48;
        gSPScisTextureRectangle(arg0++, left << 2, top << 2, (left + 640) << 2, (top + 24) << 2, 0, 0, 0, 1 << 6,
                                1 << 10);

        gSPScisTextureRectangle(arg0++, left << 2, (top + 24) << 2, (left + 640) << 2, (top + 48) << 2, 0, 0, 0, 1 << 6,
                                1 << 10);
    }

    for (i = temp_v1; i < 5; i += 2) {
        left = -D_821CF272 * 2;
        top = i * 48;
        gSPScisTextureRectangle(arg0++, left << 2, top << 2, (left + 640) << 2, (top + 24) << 2, 0, 0x500, 0, -(1 << 6),
                                1 << 10);

        gSPScisTextureRectangle(arg0++, left << 2, (top + 24) << 2, (left + 640) << 2, (top + 48) << 2, 0, 0x500, 0,
                                -(1 << 6), 1 << 10);
    }

    gSPDisplayList(arg0++, D_821944A0);

    return arg0;
}

/**
 * Draws the strip wipe if it is on.
 * @unverified Name from Stadium 1.
 */
void BattleScene_DrawStripWipe(void) {
    Gfx* gfx = gDisplayListHead;

    if (D_821CF270 != 0) {
        if (D_821CF270 == 2) {
            gfx = BattleScene_BuildStripWipeDisplayList(gfx, 0);
        } else {
            gfx = BattleScene_BuildStripWipeDisplayList(gfx, 1);
        }
    }
    gDisplayListHead = gfx;
}
