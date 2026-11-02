/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_343BA0_8.h"

void BattleAnim_StartEffect39SixSlotTrail_Seed(void) {
    static unk_D_843C2C00_024 D_84388240 = {
        0x00000002, 0x00000001, 0x0000000E, 0x00000001, 0x00000002, 0x00000001, 0x00000003, 0x00000001,
    };
    static unk_D_843C2C00_024 D_84388260 = {
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

    BattleAnim_SixSlotTrail_Spawn(0, spA4, spA0, sp9C, sp98, sp94, sp90, 0xFF, 0xFF, 0x64, 0x32, 0xC8, 0xFF, 0x32, 0, 0xFF, 0.4f, 2.0f,
                  5.0f, 0x3C, 0x95, 0x95, 0, 0x14, 0, 0xD, 0, 0x19, 0, 0xD, &D_84388240, &D_84388260);
}


void BattleAnim_StartEffect39CombinedTrail_Init(void) {
    BattleAnim_ResetSharedEffectMatrix();
    DoubleTextureTrail_InitPool();
    BattleAnim_StartEffect39DoubleTextureTrail_Seed();
    BattleAnim_SixSlotTrail_ResetPool();
    BattleAnim_StartEffect39SixSlotTrail_Seed();
}

s32 BattleAnim_StartEffect39CombinedTrail_Update(void) {
    D_8219CB14++;
    if ((D_8219CB14 % 10) == 0) {
        BattleAnim_StartEffect39SixSlotTrail_Seed();
    }
    BattleAnim_SixSlotTrail_UpdateAll();
    return DoubleTextureTrail_UpdateAll();
}

void BattleAnim_StartEffect39CombinedTrail_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = DoubleTextureTrail_DrawAll(gDisplayListHead);
    gDisplayListHead = BattleAnim_SixSlotTrail_DrawAll(gDisplayListHead);
}
