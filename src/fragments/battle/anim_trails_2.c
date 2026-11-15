/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"

/**
 * Starts one Hyper Beam trail from the attacker toward the target, with the direction jittered at
 * random.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam.
 */
void BattleAnim_SeedHyperBeamUseSixSlotTrail(void) {
    static CombinerCycleArgs D_84388240 = {
        0x00000002, 0x00000001, 0x0000000E, 0x00000001, 0x00000002, 0x00000001, 0x00000003, 0x00000001,
    };
    static CombinerCycleArgs D_84388260 = {
        0x00000003, 0x00000005, 0x00000000, 0x00000005, 0x00000000, 0x00000007, 0x00000005, 0x00000007,
    };

    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;

    BattleAnim_CalcVectorAtToDm(&spA4, &spA0, &sp9C, &sp98, &sp94, &sp90);

    sp94 += (0.4f * __cosf((RAND(10) * M_PI_F) / 10));
    sp90 += (0.4f * __cosf((RAND(10) * M_PI_F) / 10));

    sp98 *= 12.0f;
    sp94 *= 12.0f;
    sp90 *= 12.0f;

    HyperBeamIceBeamTrail_Spawn(0, spA4, spA0, sp9C, sp98, sp94, sp90, 0xFF, 0xFF, 0x64, 0x32, 0xC8, 0xFF, 0x32, 0, 0xFF, 0.4f, 2.0f,
                  5.0f, 0x3C, 0x95, 0x95, 0, 0x14, 0, 0xD, 0, 0x19, 0, 0xD, &D_84388240, &D_84388260);
}


/**
 * Init hook for Hyper Beam's use animation: resets the shared matrix and both trail pools, then
 * starts the double-texture beams and the first six-slot trail.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam.
 */
void BattleAnim_SetupHyperBeamUseCombinedTrail(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_SeedHyperBeamUseDoubleTextureTrail();
    HyperBeamIceBeamTrail_ResetPool();
    BattleAnim_SeedHyperBeamUseSixSlotTrail();
}

/**
 * Update hook for Hyper Beam's use animation: starts another six-slot trail every 10 frames,
 * advances both pools, and returns whether the double-texture beams have finished.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam.
 */
s32 BattleAnim_RunHyperBeamUseCombinedTrail(void) {
    D_8219CB14++;
    if ((D_8219CB14 % 10) == 0) {
        BattleAnim_SeedHyperBeamUseSixSlotTrail();
    }
    HyperBeamIceBeamTrail_UpdateAll();
    return DoubleTextureTrail_UpdateAll();
}

/**
 * Draw hook for Hyper Beam's use animation: loads the shared effect matrix and draws both trail
 * pools.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam.
 */
void BattleAnim_DrawHyperBeamUseCombinedTrail(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
    gDisplayListHead = HyperBeamIceBeamTrail_DrawAll(gDisplayListHead);
}
