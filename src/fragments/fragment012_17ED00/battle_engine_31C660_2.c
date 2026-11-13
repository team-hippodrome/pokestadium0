/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31C660.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_renderer.h"

#include "m2c_macros.h"

void BattleAnim_SetupDrainFlameHueChange(Particle* arg0);
void BattleAnim_SetupParticleRecolorTransparent(Particle* arg0);
void BattleAnim_SetupWhiteHueChange(Particle* arg0);
void BattleAnim_SetupDescriptor25AlphaFadeInHold(Particle* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeOut(Particle* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeIn(Particle* arg0);

/**
 * Sets up the hue change upon being hit by
 * - A Draining move (absorb, mega drain, leech life)
 * - A flame-emitting move (Flamethrower, Fire blast, fire spin, dragon rage)
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_SetupDrainFlameHueChange(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_FieldAE_SetS16_0BF4C(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B28(s32, u8, u8, u8, s32);        /* extern */
void Particle_MarkInactive(s8 *arg0);                      /* extern */
s32 Particle_IsRunning(s8 *arg0);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
s32 Particle_ApproachUnkAE(s8 *, s16, u8);                 /* extern */
s32 func_821436A0(s8 *, u8, u8);                  /* extern */
M2C_UNK func_82144130(s8 *);                      /* extern */

void BattleAnim_CallbackOwnerModelTintPaletteFade(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82144130(arg0);
        break;
    case 2:
        if (Particle_ApproachUnkAE(arg0, M2C_FIELD(arg0, s16 *, 0xA2), M2C_FIELD(arg0, u8 *, 0xCA)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        if (func_821436A0(arg0, M2C_FIELD(arg0, u8 *, 0xC9), M2C_FIELD(arg0, u8 *, 0xA7)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_80019B28(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), (s32) M2C_FIELD(arg0, s16 *, 0xAA));
    }
}

void BattleAnim_SetupOwnerModelTintRandomPaletteCycle(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, gParticlePaletteSetA[ParticleMath_RandomRange(6)]);
    Particle_FieldCF_SetU8_0BEEC(arg0, gParticlePaletteSetA[ParticleMath_RandomRange(6)]);
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);

    if (arg0->unk_AA == 0) {
        arg0->unk_AA = 1;
    }

    Particle_FieldA6_SetS16_0BCA8(arg0, 0xFF / arg0->unk_AA);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintRandomPaletteCycle(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupOwnerModelTintRandomPaletteCycle(arg0);
            break;

        case 2:
            ParticleGfx_ApproachPrimPalette(arg0, arg0->unk_CF, arg0->unk_AA);
            if (Particle_DecrementUnkA6ToZero(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 0xFF / arg0->unk_AA);
                Particle_FieldCF_SetU8_0BEEC(arg0, gParticlePaletteSetA[ParticleMath_RandomRange(6)]);
            }
            Model_SetMaterialColor(&arg0->pokemon->displayObject, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;
    }
}

/**
 * Sets up the rainbow hue shift triggered by the user's Recover or by an incoming Psybeam or Aurora Beam.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam, Aurora Beam.
 */
void BattleAnim_SetupRainbowHueChange(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, gParticlePaletteSetA[0]);
    Particle_FieldAE_SetS16_0BF4C(arg0, 1);
    Particle_FieldCF_SetU8_0BEEC(arg0, gParticlePaletteSetA[1]);
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);

    if (arg0->unk_AA == 0) {
        arg0->unk_AA = 1;
    }

    Particle_FieldA8_SetS16_0BE14(arg0, 0xFF / arg0->unk_AA);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Runs the rainbow hue shift triggered by the user's Recover or by an incoming Psybeam or Aurora Beam.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psybeam, Aurora Beam.
 */
void BattleAnim_RunRainbowHueChange(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupRainbowHueChange(arg0);
            break;

        case 2:
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            if (Particle_DecrementUnkA8ToZero(arg0) != 0) {
                Particle_FieldA8_SetS16_0BE14(arg0, 0xFF / arg0->unk_AA);
                arg0->unk_AE = (arg0->unk_AE + 1) % 6;
                Particle_FieldCF_SetU8_0BEEC(arg0, gParticlePaletteSetA[arg0->unk_AE]);
            }
            ParticleGfx_ApproachPrimPalette(arg0, arg0->unk_CF, arg0->unk_AA);
            Model_SetMaterialColor(&arg0->pokemon->displayObject, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;

        case 3:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 8) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            Model_SetMaterialColor(&arg0->pokemon->displayObject, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Set up Fading the user's model to invisible for Teleport, defense curl, sky attack, acid armor and sharpen.
 * These moves do not replace the user's model like transform or substitute and do not have unique animation varients
 * like withdrawal; which are not covered by this function.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Acid Armor, Defense Curl, Explosion, Selfdestruct, Sharpen and Teleport. Sky Attack's
 * charge turn did not use it, and Explosion and Selfdestruct did.
 */
void BattleAnim_SetupInvisibility(Particle* arg0) {
    arg0->prim_a = arg0->unk_A6;
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B6C(s32, u8);                     /* extern */
void Particle_MarkInactive(s8 *arg0);                      /* extern */
s32 Particle_IsRunning(s8 *arg0);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
s32 Particle_ApproachPrimAlpha(s8 *, u8, u8);                  /* extern */
M2C_UNK func_82144644(s8 *);                      /* extern */

void BattleAnim_CallbackOwnerModelAlphaFade(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82144644(arg0);
        break;
    case 2:
        if (Particle_ApproachPrimAlpha(arg0, M2C_FIELD(arg0, u8 *, 0xC9), M2C_FIELD(arg0, u8 *, 0xA7)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_80019B6C(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xC0));
    }
}

void BattleAnim_SetupParticleRecolorTransparent(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B28(s32, u8, u8, u8, s32);        /* extern */
void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
M2C_UNK func_82144710(s8 *);                      /* extern */

void func_82144750(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82144710(arg0);
        break;
    case 2:
        Particle_ApproachPrimAlpha(arg0, 0x80, 4);
        break;
    case 3:
        if (Particle_ApproachPrimAlpha(arg0, 0, 8) != 0) {
            Particle_DisableAndDetach(arg0);
        }
        break;
    }
    func_80019B28(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), (s32) M2C_FIELD(arg0, u8 *, 0xC0));
}

/**
 * Sets up coloration changes to pure white for using Blizzard, Confuse Ray, Self-destruct, Flash, or Explosion.
 * Blizzard's effect is more subtle and doesn't change the user completely white like the other listed moves.
 * It is used in blizzard to make the user's hue match that of the arena.
 * Also used for the poke ball's hue change.
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_SetupWhiteHueChange(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Runs coloration changes to pure white for using Blizzard, Confuse Ray, Self-destruct, Flash, or Explosion.
 * Blizzard's effect is more subtle and doesn't change the user completely white like the other listed moves.
 * It is used in blizzard to make the user's hue match that of the arena.
 * Also used for the poke ball's hue change.
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunWhiteHueChange(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupWhiteHueChange(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, arg0->unk_CD, arg0->unk_AA);
            break;

        case 3:
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 4:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, arg0->unk_AA) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

s32 func_8213C484();                                /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
void Particle_SetPrimAlpha(s8 *arg0, char arg1);                  /* extern */
M2C_UNK func_82143408(s8 *, s32);                 /* extern */
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void BattleAnim_SetupDescriptor25AlphaHoldFadeOut(s8 *arg0)
{
  func_82143408(arg0, func_8213C484() & 0xFFFF);
  if (arg0)
  {
  }
  Particle_SetPrimAlpha(arg0, *((u8 *) (((s8 *) arg0) + 0xC9)));
  func_8213C9D0(arg0);
}

/**
 * handles full screen hue overlay changes to a single color. Examples:
 * - Vine whip -> green
 * - Slash -> red
 * - Fire punch -> white
 *
 * BattleAnim_DrawFadingFullScreenColorOverlay in @battle_engine_particle_renderers.c is the equivalent for moves
 * that change both the full screen hue and the pokemon hue at the same time
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_RunFullScreenHueChange(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaHoldFadeOut(arg0);
            break;

        case 2:
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 3:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, arg0->unk_AA) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25AlphaFadeInHold(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Used to change the Pokemon and screen hue at the same time for Blizzard, Boom, Confuse Ray, and Flash
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Blizzard, Confuse Ray, Explosion, Flash and Selfdestruct.
 */
void BattleAnim_RunPokemonAndFullScreenHueChange(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaFadeInHold(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, arg0->unk_CD, arg0->unk_AA);
            break;

        case 3:
            if (Particle_DecrementUnkA6ToZero(arg0) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void func_82144A54(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
s32 func_82140690();                                /* extern */

void BattleAnim_CallbackDescriptor25AlphaHoldDetach(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82144A54((Particle*)arg0);
        return;
    case 2:
        if (func_82140690() != 0) {
            Particle_DisableAndDetach(arg0);
        }
        return;
    }
}

void BattleAnim_SetupDescriptor25PaletteFadeOut(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25PaletteFadeOut(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupDescriptor25PaletteFadeOut(arg0);
            break;

        case 2:
            Particle_DecrementUnkA6ToZeroThenAdvance(arg0);
            break;

        case 3:
            ParticleGfx_ApproachPrimPalette(arg0, arg0->unk_CD, arg0->unk_AA);
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, arg0->unk_AA) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25PaletteFadeIn(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25PaletteFadeIn(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupDescriptor25PaletteFadeIn(arg0);
            break;

        case 2:
            ParticleGfx_ApproachPrimPalette(arg0, arg0->unk_CD, arg0->unk_AA);
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0xFF, arg0->unk_AA);
            break;

        case 3:
            if (Particle_DecrementUnkA6ToZero(arg0) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}
