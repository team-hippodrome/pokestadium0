/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_31C660.c, src/fragments/battle_engine/battle_engine_343BA0.c, src/fragments/particle_math/particle_math_26E6D0.c. */

#include "battle.h"
#include "model_renderer.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void BattleAnim_LoadGlobalTintToParticle(Particle* arg0);
extern u8 gParticlePalette[][3];
extern u8 gParticlePaletteSetA[];
extern u8 gParticlePaletteSetB[];
extern u8 gParticleRandomPaletteIndices[];
extern u8 gParticlePalettePairs[][2];


#include "math.h"
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

#include "m2c_macros.h"

void ParticleGfx_CopyPaletteRgb(u8* arg0, u16 arg1);
void ParticleGfx_CopyPalettePairRgb(u8* arg0, u8* arg1, u16 arg2);
void ParticleGfx_RecolorPrimEnvFromPalettePair(Particle* arg0, u16 arg1);
void ParticleGfx_RecolorPrimFromPaletteSetA(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorEnvFromPaletteSetA(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorPrimFromPaletteSetB(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorEnvFromPaletteSetB(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorPrimEnvFromPaletteSetA(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorPrimEnvFromPaletteSetB(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorPrimRandomPalette(Particle* arg0);
void ParticleGfx_RecolorEnvRandomPalette(Particle* arg0);
s32 ParticleGfx_ApproachPrimPalette(Particle* arg0, u16 arg1, u8 arg2);
s32 ParticleGfx_ApproachEnvPalette(Particle* arg0, u16 arg1, u8 arg2);
s32 ParticleGfx_ApproachPrimEnvPalettePair(Particle* arg0, u16 arg1, u8 arg2);
void BattleAnim_SetupBackgroundRecolor(Particle* arg0);
void func_82143C08(void);
void BattleAnim_SetupIceBeamBlizzardHitHueChange(Particle* arg0);

void ParticleGfx_RecolorPrim(Particle* arg0, u16 arg1);
void ParticleGfx_RecolorEnv(Particle* arg0, u16 arg1);

/**
 * Copy the selected RGB palette entry or pair into the caller's color buffers.
 * Seen in play (2026-11-13) in the 165-move sweep (Guillotine): it wrote three RGB bytes into the
 * caller's buffer at a0.
 */
void ParticleGfx_CopyPaletteRgb(u8* arg0, u16 arg1) {
    arg0[0] = gParticlePalette[arg1][0];
    arg0[1] = gParticlePalette[arg1][1];
    arg0[2] = gParticlePalette[arg1][2];
}

/**
 * Copy the selected RGB palette entry or pair into the caller's color buffers.
 * Seen in play (2026-11-13) in the 165-move sweep (Double Kick): it wrote three RGB bytes into the
 * caller's buffer at a0.
 */
void ParticleGfx_CopyPalettePairRgb(u8* arg0, u8* arg1, u16 arg2) {
    u8 sp1C = gParticlePalettePairs[arg2][0];
    u8 sp1E = gParticlePalettePairs[arg2][1];

    ParticleGfx_CopyPaletteRgb(arg0, sp1C);
    ParticleGfx_CopyPaletteRgb(arg1, sp1E);
}

/**
 * Sets the particle's prim color (0xBA-0xBC) from palette entry arg1.
 */
void func_82143408(u8* arg0, u16 arg1) {
    arg0[0xBA] = gParticlePalette[arg1][0];
    arg0[0xBB] = gParticlePalette[arg1][1];
    arg0[0xBC] = gParticlePalette[arg1][2];
}

/**
 * Sets the particle's env color (0xBD-0xBF) from palette entry arg1.
 */
void func_82143440(u8* arg0, u16 arg1) {
    arg0[0xBD] = gParticlePalette[arg1][0];
    arg0[0xBE] = gParticlePalette[arg1][1];
    arg0[0xBF] = gParticlePalette[arg1][2];
}

/**
 * Set the particle's primitive and environment RGB channels from the selected palette pair, leaving alpha unchanged.
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day, Fire Punch): it changed prim_b (0xBC)
 * and env r, g, b (0xBD-0xBF) to (0xF0, 0x28, 0x28) and left prim alpha alone.
 */
void ParticleGfx_RecolorPrimEnvFromPalettePair(Particle* arg0, u16 arg1) {
    u8 sp1C = gParticlePalettePairs[arg1][0];
    u8 sp1E = gParticlePalettePairs[arg1][1];

    ParticleGfx_RecolorPrim(arg0, sp1C);
    ParticleGfx_RecolorEnv(arg0, sp1E);
}

/**
 * Set the particle's primitive RGB channels from the selected palette-set index, leaving alpha unchanged.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_RecolorPrimFromPaletteSetA(Particle* arg0, s16 arg1) {
    ParticleGfx_RecolorPrim(arg0, gParticlePaletteSetA[arg1]);
}

/**
 * Set the particle's environment RGB channels from the selected palette-set index, leaving alpha unchanged.
 * Seen in play (2026-11-13) in the 165-move sweep (Ice Beam): it changed env_r and env_b (0xBD,
 * 0xBF) only.
 */
void ParticleGfx_RecolorEnvFromPaletteSetA(Particle* arg0, s16 arg1) {
    ParticleGfx_RecolorEnv(arg0, gParticlePaletteSetA[arg1]);
}

/**
 * Set the particle's primitive RGB channels from the selected palette-set index, leaving alpha unchanged.
 * Seen in play (2026-11-13) in the 165-move sweep (Psybeam): with index 9 it changed prim from
 * FFFFFF to 64C8FF; env was untouched.
 */
void ParticleGfx_RecolorPrimFromPaletteSetB(Particle* arg0, s16 arg1) {
    ParticleGfx_RecolorPrim(arg0, gParticlePaletteSetB[arg1]);
}

/**
 * Set the particle's environment RGB channels from the selected palette-set index, leaving alpha unchanged.
 * Seen in play (2026-11-13) in the 165-move sweep (Psybeam): with index 9 it changed env from
 * FFFFFF to FF78C8; prim was untouched.
 */
void ParticleGfx_RecolorEnvFromPaletteSetB(Particle* arg0, s16 arg1) {
    ParticleGfx_RecolorEnv(arg0, gParticlePaletteSetB[arg1]);
}

/**
 * Set the particle's primitive and environment RGB channels from the selected palette-set index, leaving alpha
 * unchanged.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_RecolorPrimEnvFromPaletteSetA(Particle* arg0, s16 arg1) {
    u8 sp1F = gParticlePaletteSetA[arg1];

    ParticleGfx_RecolorPrim(arg0, sp1F);
    ParticleGfx_RecolorEnv(arg0, sp1F);
}

/**
 * Set the particle's primitive and environment RGB channels from the selected palette-set index, leaving alpha
 * unchanged.
 * Not reached in play (2026-11-13): no move in the 165-move battle sweep called it (each move used
 * once, from the command menu to the end of its turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_RecolorPrimEnvFromPaletteSetB(Particle* arg0, s16 arg1) {
    u8 sp1F = gParticlePaletteSetB[arg1];

    ParticleGfx_RecolorPrim(arg0, sp1F);
    ParticleGfx_RecolorEnv(arg0, sp1F);
}

/**
 * Set the particle's primitive RGB channels from a randomly selected palette index, leaving alpha unchanged.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void ParticleGfx_RecolorPrimRandomPalette(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, gParticleRandomPaletteIndices[(ParticleMath_RandomRange(5) & 0xFF)]);
}

/**
 * Set the particle's environment RGB channels from a randomly selected palette index, leaving alpha unchanged.
 * Seen in play (2026-11-13) in the 165-move sweep (Bubble Beam): it changed env_g and env_b (0xBE,
 * 0xBF) only.
 */
void ParticleGfx_RecolorEnvRandomPalette(Particle* arg0) {
    ParticleGfx_RecolorEnv(arg0, gParticleRandomPaletteIndices[ParticleMath_RandomRange(5) & 0xFF]);
}

/**
 * Approach each selected RGB channel toward its palette value; return 1 only when all channel helpers report
 * completion.
 * Seen in play (2026-11-13) in the 165-move sweep (Guillotine): prim r, g, b (0xBA-0xBC) each
 * stepped from 0xFF to 0xDF (step 0x20) and it returned 0.
 */
s32 ParticleGfx_ApproachPrimPalette(Particle* arg0, u16 arg1, u8 arg2) {
    s32 sp2C = 0;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    u8 sp1C[3];

    ParticleGfx_CopyPaletteRgb(sp1C, arg1);

    sp28 = Particle_PrimR_Approach_0BAE4(arg0, sp1C[0], arg2);
    sp24 = Particle_PrimG_Approach_0BB14(arg0, sp1C[1], arg2);
    sp20 = Particle_PrimB_Approach_0BB44(arg0, sp1C[2], arg2);

    if ((sp28 * sp24 * sp20) != 0) {
        sp2C = 1;
    }
    return sp2C;
}

/**
 * Approach each selected RGB channel toward its palette value; return 1 only when all channel helpers report
 * completion.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal,
 * no function-pointer word in any fragment), so play cannot reach it.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 ParticleGfx_ApproachEnvPalette(Particle* arg0, u16 arg1, u8 arg2) {
    s32 sp2C = 0;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    u8 sp1C[3];

    ParticleGfx_CopyPaletteRgb(&sp1C, arg1);

    sp28 = Particle_EnvR_Approach_0BB90(arg0, sp1C[0], arg2);
    sp24 = Particle_EnvG_Approach_0BBF0(arg0, sp1C[1], arg2);
    sp20 = Particle_EnvB_Approach_0BBC0(arg0, sp1C[2], arg2);

    if ((sp28 * sp24 * sp20) != 0) {
        sp2C = 1;
    }
    return sp2C;
}

/**
 * Approach each selected RGB channel toward its palette value; return 1 only when all channel helpers report
 * completion.
 * Seen in play (2026-11-13) in the 165-move sweep (Double Kick): env_b (0xBF) stepped from 0 to
 * 0x24 and it returned 0.
 */
s32 ParticleGfx_ApproachPrimEnvPalettePair(Particle* arg0, u16 arg1, u8 arg2) {
    s32 sp44 = 0;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    u8 sp28[3];
    u8 sp24[3];

    ParticleGfx_CopyPalettePairRgb(sp28, sp24, arg1);

    sp40 = Particle_PrimR_Approach_0BAE4(arg0, sp28[0], arg2);
    sp3C = Particle_PrimG_Approach_0BB14(arg0, sp28[1], arg2);
    sp38 = Particle_PrimB_Approach_0BB44(arg0, sp28[2], arg2);
    sp34 = Particle_EnvR_Approach_0BB90(arg0, sp24[0], arg2);
    sp30 = Particle_EnvG_Approach_0BBF0(arg0, sp24[1], arg2);
    sp2C = Particle_EnvB_Approach_0BBC0(arg0, sp24[2], arg2);

    if ((sp40 * sp3C * sp38 * sp34 * sp30 * sp2C) != 0) {
        sp44 = 1;
    }
    return sp44;
}

/**
 * Moves: Absorb (use), Aurora Beam (use/hit), Barrier (use), Bide (use), Blizzard (use/hit), Bubble Beam
 * (use/hit), Confuse Ray (use/hit), Confusion (use/hit), Conversion (use), Double-Edge (use), Dragon Rage
 * (use), Dream Eater (use), Earthquake (use), Explosion (use/hit), Fire Blast (use/hit), Fire Spin (use),
 * Fissure (use), Flamethrower (use), Flash (use/hit), Focus Energy (use), Glare (use), Guillotine (use), Horn
 * Drill (use), Hydro Pump (use), Hyper Beam (use), Ice Beam (use/hit), Leech Life (use), Leer (use), Light
 * Screen (use), Lovely Kiss (use), Mega Drain (use), Mimic (use), Night Shade (use), Petal Dance (use),
 * Psybeam (use/hit), Psychic (use/hit), Psywave (use), Rage (use), Razor Leaf (use/hit), Recover (use),
 * Reflect (use), Self-Destruct (use/hit), Skull Bash (use), Sky Attack (use/hit), Solar Beam (use/hit), Sonic
 * Boom (use), Swift (use), Take Down (use), Thunder (use/hit), Thunder Shock (use/hit), Thunder Wave (hit),
 * Thunderbolt (use/hit), Tri Attack (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the battle opening and a
 * switch in battle.
 * @unverified Name and comment from Stadium 1.
 */
void BattleAnim_SetupBackgroundRecolor(Particle* arg0) {
    BattleAnim_LoadGlobalTintToParticle(arg0);
    Particle_AdvanceLifecycle(arg0);
}

s32 func_8213C494(s8 *);                          /* extern */
void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK Particle_StorePrimColorInTemp(s8 *);                      /* extern */
s32 func_821436A0(s8 *, u8, s32);                 /* extern */
M2C_UNK func_8214390C(s8 *);                      /* extern */

void func_82143934(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8214390C(arg0);
        break;
    case 2:
        if (func_821436A0(arg0, M2C_FIELD(arg0, u8 *, 0xCB), func_8213C494(arg0) & 0xFF) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        Particle_DisableAndDetach(arg0);
        break;
    }
    Particle_StorePrimColorInTemp(arg0);
}

/**
 * Moves: Acid (hit), Acid Armor (use), Confuse Ray (use/hit), Confusion (hit), Defense Curl (use), Dragon Rage
 * (hit), Ember (hit), Explosion (use/hit), Fire Punch (hit), Flamethrower (hit), Flash (use/hit), Guillotine
 * (hit), Harden (use), Horn Drill (hit), Hyper Beam (use/hit), Ice Punch (hit), Lick (hit), Mega Kick (hit),
 * Mega Punch (hit), Night Shade (hit), Psychic (hit), Self-Destruct (use/hit), Sharpen (use), Skull Bash
 * (hit), Sky Attack (use), Sludge (hit), Solar Beam (use), Substitute (use), Thunder Punch (hit), Toxic (hit),
 * Transform (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-13) in the 165-move sweep (Pay Day, Fly, Sonic Boom): it advanced the
 * particle's lifecycle (0xAE, 1 to 2) and wrote its colors.
 */
void BattleAnim_SetupTargetHueChange(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_ScratchA_SetS16_0BF4C(arg0, arg0->param0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B28(s32, u8, u8, u8, s32);        /* extern */
void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
s32 Particle_ApproachScratchA(s8 *, u8, s16);                 /* extern */
M2C_UNK func_821439D0(s8 *);                      /* extern */

void func_82143A18(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_821439D0(arg0);
        break;
    case 2:
        if (Particle_ApproachScratchA(arg0, M2C_FIELD(arg0, u8 *, 0xC9), M2C_FIELD(arg0, s16 *, 0xA6)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        Particle_DisableAndDetach(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_80019B28(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), (s32) M2C_FIELD(arg0, s16 *, 0xAA));
    }
}

/**
 * Moves: Barrier (use), Bide (use), Confusion (use), Focus Energy (use), Growth (use), Light Screen (use),
 * Lovely Kiss (hit), Poison Gas (hit), Poison Powder (hit), Psychic (use), Psywave (hit), Rage (use), Reflect
 * (use), Sleep Powder (hit), Smog (hit), Soft-Boiled (use), Spore (hit), Struggle (use), Stun Spore (hit),
 * Thrash (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-13) in the 165-move sweep (Thrash, Growth, Poison Powder): it advanced the
 * lifecycle and, for Thrash, set prim r, g, b to (0xF0, 0x28, 0x28), red.
 */
void BattleAnim_SetupUserHueChange(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_ScratchA_SetS16_0BF4C(arg0, arg0->byteParam2);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Changes User's Hue. Examples:
 * - Thrash -> red
 * - Recover -> rainbow
 * Seen in play (2026-11-13) in the 165-move sweep: for Thrash it set the user's tint to (0xF0,
 * 0x28, 0x28), red, as its comment says.
 */
void BattleAnim_RunUserHueChange(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupUserHueChange(arg0);
            break;

        case 2:
            if (Particle_ScratchA_Approach_0BF60(arg0, arg0->byteParam0, arg0->param1) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DecrementParam0ToZeroThenAdvance(arg0);
            break;

        case 4:
            if (Particle_ScratchA_Approach_0BF60(arg0, 0, arg0->param1) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->pokemon->displayObject, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->scratchA);
    }
}

/**
 * Empty.
 */
void func_82143C08(void) {
}

M2C_UNK func_80019B28(s32, u8, u8, u8, s32);        /* extern */
void Particle_DisableAndDetach(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_82143AD0(s8 *);                      /* extern */

void func_82143C10(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82143AD0(arg0);
        break;
    case 2:
        func_821406B4(arg0);
        break;
    case 3:
        if (Particle_ApproachScratchA(arg0, 0, M2C_FIELD(arg0, s16 *, 0xA6)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_80019B28(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), (s32) M2C_FIELD(arg0, s16 *, 0xAA));
    }
}

/**
 * Init step: recolors the prim color from palette CF, copies field A6 into AE and advances.
 */
void func_82143CE0(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_ScratchA_SetS16_0BF4C(arg0, arg0->param0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B28(s32, u8, u8, u8, s32);        /* extern */
void Particle_MarkInactive(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK Particle_SetScratchA(s8 *, M2C_UNK);             /* extern */

void func_82143D28(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82143CE0(arg0);
        break;
    case 2:
        if (func_821436A0(arg0, M2C_FIELD(arg0, u8 *, 0xC9), M2C_FIELD(arg0, u8 *, 0xA7)) != 0) {
            Particle_SetScratchA(arg0, 0);
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_80019B28(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), (s32) M2C_FIELD(arg0, s16 *, 0xAA));
    }
}

/**
 * Same init step as func_82143CE0.
 */
void func_82143DE8(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_ScratchA_SetS16_0BF4C(arg0, arg0->param0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B28(s32, u8, u8, u8, s32);        /* extern */
void Particle_MarkInactive(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */

void func_82143E30(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82143DE8(arg0);
        break;
    case 2:
        if (func_821436A0(arg0, M2C_FIELD(arg0, u8 *, 0xC9), M2C_FIELD(arg0, u8 *, 0xA7)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_80019B28(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), (s32) M2C_FIELD(arg0, s16 *, 0xAA));
    }
}

/**
 * Sets the hue coloration change of a pokemon hit by ice beam or blizzard
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam, Blizzard.
 */
void BattleAnim_SetupIceBeamBlizzardHitHueChange(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_ScratchA_SetS16_0BF4C(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Runs the hue coloration of a pokemon hit by ice beam or blizzard
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Ice Beam, Blizzard.
 */
void BattleAnim_RunIceBeamBlizzardHitHueChange(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupIceBeamBlizzardHitHueChange(arg0);
            break;

        case 2:
            Particle_ApproachScratchAThenAdvance(arg0, arg0->param0, arg0->byteParam2);
            break;

        case 3:
            if (ParticleGfx_ApproachPrimPalette(arg0, arg0->byteParam0, arg0->param1) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_ApproachScratchAThenAdvance(arg0, 0, arg0->byteParam2);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->pokemon->displayObject, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->scratchA);
    }
}

/**
 * Same init step as func_82143CE0.
 */
void func_82144010(Particle* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_ScratchA_SetS16_0BF4C(arg0, arg0->param0);
    Particle_AdvanceLifecycle(arg0);
}

M2C_UNK func_80019B28(s32, u8, u8, u8, s32);        /* extern */
void Particle_MarkInactive(Particle* arg0);                      /* extern */
s32 Particle_IsRunning(Particle* arg0);                          /* extern */
M2C_UNK func_8213C9D0(s8 *);                      /* extern */
M2C_UNK func_82140874(s8 *, M2C_UNK, u8);         /* extern */

void func_82144058(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82144010(arg0);
        break;
    case 2:
        if (func_821436A0(arg0, M2C_FIELD(arg0, u8 *, 0xC9), M2C_FIELD(arg0, u8 *, 0xA7)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    case 3:
        func_82140874(arg0, 0, M2C_FIELD(arg0, u8 *, 0xCA));
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_80019B28(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, u8 *, 0xBA), M2C_FIELD(arg0, u8 *, 0xBB), M2C_FIELD(arg0, u8 *, 0xBC), (s32) M2C_FIELD(arg0, s16 *, 0xAA));
    }
}
