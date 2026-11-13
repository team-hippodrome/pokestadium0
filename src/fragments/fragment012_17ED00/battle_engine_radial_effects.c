/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_343BA0.c, src/fragments/ekans_game/ekans_game.c. */

#include "global.h"
#include "fragments/particle_math/particle_math.h"
#include "jpeg_stream.h"
#include "controller.h"
#include "geo_render.h"
#include "model_animation.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sound_state.h"
#include "audio_sfx.h"
#include "audio_channel.h"
#include "audio_loop_point.h"
#include "audio_commands_category2.h"
#include "audio_category_fade.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "fragments/widget_toolkit/widget_toolkit.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"
#include "stage_loader.h"
#include "geo_layout.h"

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math.h"
#include "math_util.h"
extern u8* sBattleAnimAssetPointers[256];
extern s16 sBattleAnimResourceList[0x10];
extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];
extern s16 D_8219CAC0;
extern s16 D_8219CAC2;
extern Mtx D_8219CAC8;
extern s16 D_8219CB08;
extern s16 D_8219CB0A;
extern s16 D_8219CB0C;
extern s16 D_8219CB0E;
extern s16 D_8219CB10;
extern s16 D_8219CB12;
extern s16 D_8219CB14;
extern s16 D_8219CB16;
extern s16 D_8219CB18;
extern s16 D_8219CB1A;
extern const char D_821978C8[];

void BattleAnim_InitializeSurfUse(void);
s32 BattleAnim_SurfCompleteImmediately(void);
void func_8216E0C0(void);
void BattleAnim_StartTrappingLassoMove_Init(void);
s32 BattleAnim_StartTrappingLassoMove_Update(void);
void BattleAnim_StartTrappingLassoMove_Draw(void);
s32 BattleAnim_EndEffect9Radial20_Update(void);
void BattleAnim_EndEffect9Radial20_Draw(void);
void BattleAnim_SetupSwiftUseRibbonSheet(void);
s32 BattleAnim_RunSwiftUseRibbonSheet(void);
void BattleAnim_DrawSwiftUseRibbonSheet(void);
void BattleAnim_SetupStringShotUseRadial(void);
s32 BattleAnim_RunStringShotUseRadial(void);
void BattleAnim_DrawStringShotUseRadial(void);
s32 BattleAnim_RunStringShotHitRadial(void);
void BattleAnim_DrawStringShotHitRadial(void);
s32 BattleAnim_RunDisableHitRadial(void);
void BattleAnim_DrawDisableHitRadial(void);

void BattleAnim_ResetSharedEffectMatrix(void);
void BattleAnim_StartEffect19Radial20_EmitVariantD(void);
void BattleAnim_StartEffect7TexturedRibbonSheet_Emit(void);
void BattleAnim_StartEffect33Radial20_EmitVariantC(void);

/**
 * Effect init that spawns the Surf animation. Player sweep (all 165 moves used in battle): only
 * Surf reached this function.
 */
void BattleAnim_InitializeSurfUse(void) {
}

/**
 * Moves: Surf (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Surf.
 */
s32 BattleAnim_SurfCompleteImmediately(void) {
    return -1;
}

void func_8216E0C0(void) {
}

void BattleAnim_CalcVectorAtToDm(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void func_82175440(f32, f32, f32, f32, f32, f32, s16, u8, u8, u8, u8, f32, f32, f32, s16);
/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_StartEffect19Radial20_EmitVariantD(void) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s32 r2;
    s32 r1;

    BattleAnim_CalcVectorAtToDm(&sp64, &sp60, &sp5C, &sp58, &sp54, &sp50);
    sp58 *= 8.0f;
    sp54 *= 4.0f;
    sp50 = 0.0f;
    sp54 += 6.0f;
    r1 = guRandom();
    r2 = guRandom();
    func_82175440(sp64, sp60, sp5C, sp58, ((r1 % 4) * 0.01) + sp54 - 0.02, sp50 - ((r2 % 5) * 0.3) + 0.6, 3, 0x80, 0xC0, 0xFF, 0xC8, 0.1f, 2.0f, 5.0f, 0x3C);
}

/**
 * Moves: Bind (use), Constrict (use), Wrap (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bind, Wrap, Constrict.
 */
void BattleAnim_StartTrappingLassoMove_Init(void) {
    D_8219CB0E = 0;
    BattleAnim_ResetSharedEffectMatrix();
    Radial20_ResetPool();
    BattleAnim_StartEffect19Radial20_EmitVariantD();
}

/**
 * Moves: Bind (use), Constrict (use), Wrap (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bind, Wrap, Constrict.
 */
s32 BattleAnim_StartTrappingLassoMove_Update(void) {
    D_8219CB0E++;
    if (D_8219CB0E >= 0xB5) {
        return -1;
    }

    if ((D_8219CB0E < 0x78) && ((D_8219CB0E % 7) == 0)) {
        BattleAnim_StartEffect19Radial20_EmitVariantD();
    }
    return Radial20_IsComplete();
}

/**
 * Moves: Bind (use), Constrict (use), Wrap (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Bind, Wrap, Constrict.
 */
void BattleAnim_StartTrappingLassoMove_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Radial20_Draw(gDisplayListHead);
}

void func_8216DAC0(Vec3f*);

/**
 * Init hook for end effect 9: resets the shared matrix and starts the lasso hit effect at
 * the target, sized for the tertiary owner.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_EndEffect9Radial20_Init(void) {
    Vec3f sp34;
    f32 sp30;

    BattleAnim_ResetSharedEffectMatrix();
    func_8216DAC0(&sp34);
    sp30 = BattleAnim_EffectTertiaryOwnerModelScale();
    BattleAnim_ResetSharedEffectMatrix();
    LassoHit_Init(sp34.x, sp34.y, sp34.z, sp30, 0x40, 0xFF, 0xFF, 0, 0, 0xFF);
}

/**
 * Update hook for end effect 9: advances the lasso hit effect.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
s32 BattleAnim_EndEffect9Radial20_Update(void) {
    return LassoHit_Update();
}

/**
 * Draw hook for end effect 9: loads the shared matrix and draws the trail strip.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_EndEffect9Radial20_Draw(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Strip400_Draw(gDisplayListHead);
}

/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_StartEffect7TexturedRibbonSheet_Emit(void) {
    Vec3f pos;
    f32 x;
    f32 y;
    f32 z;
    f32 angle;
    UNUSED s32 pad[2]; // FAKE: stack padding
    f32 scale = BattleAnim_EffectSecondaryOwnerModelScale();

    BattleAnim_EffectSecondaryOwnerAnchorPosition(&pos);
    x = pos.x;
    y = pos.y;
    z = pos.z;
    angle = 15.0f;
    if (x > 0.0) {
        angle = -angle;
    }
    x += scale * (30.0f - ((s32)guRandom() % 60));
    y += scale * (30.0f - ((s32)guRandom() % 60));
    z += scale * (30.0f - ((s32)guRandom() % 60));
    SwiftRibbonSheet_Start(x, y, z, angle, 0.0f, 0.0f, 0xFF, 0xFF, 0, 0x3C, 0.3f, 0x1E);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Swift.
 */
void BattleAnim_SetupSwiftUseRibbonSheet(void) {
    D_8219CB10 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    SwiftRibbonSheet_Init();
    BattleAnim_StartEffect7TexturedRibbonSheet_Emit();
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Swift.
 */
s32 BattleAnim_RunSwiftUseRibbonSheet(void) {
    D_8219CB10++;
    if (D_8219CB10 >= 0x709) {
        return -1;
    }

    if ((D_8219CB10 < 0x6EA) && ((D_8219CB10 % 3) == 0)) {
        BattleAnim_StartEffect7TexturedRibbonSheet_Emit();
    }

    return SwiftRibbonSheet_IsComplete();
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Swift.
 */
void BattleAnim_DrawSwiftUseRibbonSheet(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = SwiftRibbonSheet_Draw(gDisplayListHead);
}

/**
 * Emits one radial effect for start effect 33 from the owner toward the target with a
 * small random spread.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep.
 * @unverified Name guessed from the code.
 */
void BattleAnim_StartEffect33Radial20_EmitVariantC(void) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;

    BattleAnim_CalcVectorAtToDm(&sp74, &sp70, &sp6C, &sp68, &sp64, &sp60);
    sp68 *= 8.0f;
    sp64 *= 4.0f;
    sp60 = 0.0f;
    sp64 += 6.0f;
    Radial20_VariantC(sp74, sp70, sp6C, sp68, (((guRandom() % 5) * 0.1) + sp64) - 0.2,
                      (sp60 - ((guRandom() % 5) * 0.3)) + 0.6, 3, 0xFF, 0xFF, 0xFF, 0x64, 0.1f, 1.0f, 3.0f, 0x3C);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for String Shot.
 */
void BattleAnim_SetupStringShotUseRadial(void) {
    D_8219CB12 = 0;
    BattleAnim_ResetSharedEffectMatrix();
    Radial20_ResetPool();
    BattleAnim_StartEffect33Radial20_EmitVariantC();
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for String Shot.
 */
s32 BattleAnim_RunStringShotUseRadial(void) {
    D_8219CB12++;
    if (D_8219CB12 >= 0xB5) {
        return -1;
    }

    if ((D_8219CB12 < 0x78) && ((D_8219CB12 % 7) == 0)) {
        BattleAnim_StartEffect33Radial20_EmitVariantC();
    }

    return Radial20_IsComplete();
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for String Shot.
 */
void BattleAnim_DrawStringShotUseRadial(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Radial20_Draw(gDisplayListHead);
}

/**
 * Effect init that spawns the String Shot animation. Player sweep (all 165 moves used in battle):
 * only String Shot reached this function.
 */
void BattleAnim_InitializeStringShotUse(void) {
    Vec3f sp34;
    f32 sp30;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerBonePosition(&sp34);
    sp30 = BattleAnim_EffectTertiaryOwnerModelScale();
    BattleAnim_ResetSharedEffectMatrix();
    LassoHit_Init(sp34.x, sp34.y, sp34.z, sp30, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for String Shot.
 */
s32 BattleAnim_RunStringShotHitRadial(void) {
    return LassoHit_Update();
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for String Shot.
 */
void BattleAnim_DrawStringShotHitRadial(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Strip400_Draw(gDisplayListHead);
}

/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_SetupStringShotHitRadial(void) {
    Vec3f sp34;
    f32 sp30;

    BattleAnim_ResetSharedEffectMatrix();
    BattleAnim_EffectSecondaryOwnerBonePosition(&sp34);
    sp30 = BattleAnim_EffectTertiaryOwnerModelScale();
    BattleAnim_ResetSharedEffectMatrix();
    LassoHit_Init(sp34.x, sp34.y, sp34.z, sp30, 0xFF, 0xFF, 0x40, 0xFF, 0xFF, 0x40);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Disable.
 */
s32 BattleAnim_RunDisableHitRadial(void) {
    return LassoHit_Update();
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Disable.
 */
void BattleAnim_DrawDisableHitRadial(void) {
    gSPMatrix(gDisplayListHead++, &D_8219CAC8, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Strip400_Draw(gDisplayListHead);
}

/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_StartEffect98Radial20_EmitVariantD(void) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s32 r2;
    s32 r1;

    BattleAnim_CalcVectorAtToDm(&sp64, &sp60, &sp5C, &sp58, &sp54, &sp50);
    sp58 *= 8.0f;
    sp54 *= 4.0f;
    sp50 = 0.0f;
    sp54 += 6.0f;
    r1 = guRandom();
    r2 = guRandom();
    func_82175440(sp64, sp60, sp5C, sp58, ((r1 % 4) * 0.01) + sp54 - 0.02, sp50 - ((r2 % 5) * 0.3) + 0.6, 3, 0xFF, 0xFF, 0x40, 0xC8, 0.1f, 2.0f, 5.0f, 0x3C);
}
