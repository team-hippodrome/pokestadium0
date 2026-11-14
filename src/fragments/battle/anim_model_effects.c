#include "pokemon.h"
#include "moves.h"
/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle.h"
#include "geo_node.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "matrix.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK BattleAnim_InitializeSolarBeamUseSequence();
M2C_UNK BattleAnim_InitializeWaterfallUseB();
M2C_UNK Particle_AnimateFramesForwardLooped(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK Particle_AnimateFramesForwardLoopedThenAdvance(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK Particle_ApproachEnvGreen(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_ApproachEnvRed(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_ApproachPrimBlue(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_ApproachPrimGreen(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_ApproachPrimRed(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_ApproachStepMagnitude(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_ApproachScratchA(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_ApproachScratchB(s8 *, M2C_UNK, M2C_UNK);
M2C_UNK Particle_GetUnkCE();
M2C_UNK Particle_SetRotationY(s8 *, s16);
M2C_UNK Particle_SetParam0(s8 *, s16);
M2C_UNK Particle_SetScratchB(s8 *, M2C_UNK);
M2C_UNK func_8213831C(s8 *, M2C_UNK);
M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32);
M2C_UNK func_8213C9D0(s8 *);
M2C_UNK func_8213E77C(s8 *);
M2C_UNK func_821401D4(s8 *, M2C_UNK);
M2C_UNK func_82143478(s8 *, M2C_UNK);
extern M2C_UNK BattleAnim_RunBlizzardHitUpwardColdAir;
extern M2C_UNK BattleAnim_RunDigHitDust;
extern M2C_UNK BattleAnim_RunDigHitRocks;
extern M2C_UNK BattleAnim_RunOscillatingFlameUnderneathPokemon;
extern M2C_UNK D_8218E7B8;
extern M2C_UNK func_82144750;
extern M2C_UNK func_82163D7C;
extern M2C_UNK func_82164AD0;
s16 Particle_GetUnkCD();
s16 func_8213C484();
s32 func_821385C0();
s32 func_82140690(s8 *);
void Particle_AddPosOffsetYScaled(s8*, f32);
void func_8213E1FC(Particle* arg0, f32 arg1);

/**
 * Lifecycle init for one of three side-by-side animated models (model 0x21, anim 0x22,
 * scale 0.2). Slot arg1 picks the X offset and the Z rotation (slot 0 tilts one way, slot 2
 * the other, slot 1 sits higher and upright). Detaches the particle if no display object
 * could be allocated.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitModelAnimationSlot(Particle* arg0, s16 arg1) {
    Vec3f sp24;

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);

    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x21, 0x22);
        Particle_SetScaleScaled(arg0, 0.2f);
        BattleAnim_ApplyModelSpeciesOffset(arg0);
        Vec3f_SetComponentsDuplicate(&sp24, (arg1 * 5.0f * 2) + -10.0f, 5.0f, 10.0f);
        Particle_AddPositionRotatedVectorByYaw(arg0, sp24);

        switch (arg1) {
            case 0:
                Particle_Rotation_SetZ_0A2CC(arg0, 0x1400);
                break;

            case 1:
                Particle_PositionOffset_AddYScaled_08E90(arg0, 2.0f);
                Particle_Rotation_SetZ_0A2CC(arg0, 0);
                break;

            case 2:
                Particle_Rotation_SetZ_0A2CC(arg0, -0x1400);
                break;
        }

        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Particle callback: waits eight frames per spawn index, starts model animation slot arg AC,
 * waits for the animation to finish and detaches.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name guessed from the code.
 */
void BattleAnim_ConfuseRayAmnesiaModelAnimWait(Particle* arg0) {
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);

    switch (arg0->lifecycle) {
        case 1:
            Particle_Param0_SetS16_0BCA8(arg0, sp26 * 8);
            Particle_AdvanceLifecycle(arg0);
            break;

        case 2:
            if (Particle_DecrementParam0ToZero(arg0) != 0) {
                BattleAnim_InitModelAnimationSlot(arg0, sp26);
            }
            break;

        case 3:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Effect start init 12 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Amnesia.
 */
void BattleAnim_InitializeAmnesiaUse(void) {
    BattleAnim_SpawnCategory17MarkerSlot(0x55, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_ConfuseRayAmnesiaModelAnimWait, &gDefaultParticleDescriptor, 0x1E, 3, 6, 0, 0, 0);
}

s32 func_82107CF0(s32);
void func_8213D720(s8*, f32);
void func_8213D790(s8*, f32);
/**
 * Raises or lowers the particle by a per-species offset (species from the owner at +0x10):
 * -10, 10 or 15 for the listed species, and also pushes it forward for species 0x3B.
 */
void func_82154704(s8* arg0) {
    f32 var_f20 = 0.0f;

    switch (func_82107CF0(M2C_FIELD(arg0, s32*, 0x10))) {
        case 0xF:
            var_f20 = -10.0f;
            break;
        case 0x16:
            var_f20 = -10.0f;
            break;
        case 0x33:
            var_f20 = 10.0f;
            break;
        case 0x3B:
            var_f20 = 15.0f;
            func_8213D644(arg0, 5.0f);
            break;
        case 0x4C:
            var_f20 = -10.0f;
            break;
        case 0x5B:
            var_f20 = -8.0f;
            break;
        case 0x5E:
            var_f20 = -5.0f;
            func_8213D644(arg0, 5.0f);
            break;
        case 0x5F:
            func_8213D790(arg0, 15.0f);
            break;
        case 0x73:
            func_8213D790(arg0, 5.0f);
            var_f20 = -5.0f;
            break;
        case 0x79:
            var_f20 = -8.0f;
            break;
        case 0x7F:
            var_f20 = 15.0f;
            break;
        case 0x80:
            var_f20 = -10.0f;
            break;
        case 0x84:
            var_f20 = 10.0f;
            break;
        case 0x8E:
            var_f20 = -25.0f;
            func_8213D644(arg0, 20.0f);
            break;
        case 0x95:
            func_8213D720(arg0, 5.0f);
            func_8213D644(arg0, 5.0f);
            break;
    }
    Particle_AddPosOffsetYScaled(arg0, var_f20);
}

/**
 * Moves: Barrier (use), Light Screen (use), Reflect (use)
 * TODO: Human contributor add screenshot
 * Effect start init 14 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Barrier, Light Screen, Reflect.
 */
void BattleAnim_InitializeScreenMove(void) {
    s32 temp_v0;

    func_8213B560(0, &func_82152FB0, &D_8218E580, 0x1E, 1, 0xB, 0, 0x1E, 0);
    func_8213B464(0xF);
    temp_v0 = func_8213646C();
    switch (temp_v0) {                              /* irregular */
    case 0x70:
        func_8213B5D8(0, 0x10, 8, &func_821624FC, &D_8218E7A0, 0, 4, 0xB, 0, 0x18, 5);
        return;
    case 0x71:
        func_8213B644(0, 0x10, 0x1E);
        func_8213BC7C(0, 0, 8, 0, 0xFF, 0x30);
        func_8213B5D8(0, 0x10, 8, &func_821624FC, &D_8218E7A0, 0, 8, 0xB, 0, 0x17, 5);
        func_8213B6AC(0, 1, 0x20, 8, 0xFF);
        return;
    case 0x73:
        func_8213B644(0, 0x10, 0x1E);
        func_8213BC7C(0, 0, 8, 0, 0xFF, 0x30);
        func_8213B5D8(0, 0x10, 8, &func_821624FC, &D_8218E7A0, 0, 8, 0xB, 0, 0, 5);
        func_8213B6AC(0, 1, 0x20, 8, 0xFF);
        return;
    }
}

/**
 * Builds the display list for the Barrier, Light Screen and Reflect wall: sets up the
 * reflective camera, picks the move's primitive and environment colors, then adds the
 * animated tile.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_BuildReflectiveTextureDisplayList(Gfx* arg0, s32 arg1, u16 arg2) {
    BattleAnim_SetupReflectiveCamera();

    switch (BattleAnim_GetQueuedMoveId()) {
        case BARRIER:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, 255); // #FFFFFFFF
            gDPSetEnvColor(arg0++, 155, 255, 255, 255); // #9BFFFFFF
            break;

        case LIGHT_SCREEN:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, 255); // #FFFFFFFF
            gDPSetEnvColor(arg0++, 255, 255, 100, 255); // #FFFF64FF
            break;

        case REFLECT:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 100, 255); // #FFFF64FF
            gDPSetEnvColor(arg0++, 255, 100, 0, 255); // #FF6400FF
            break;
    }

    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, 0, 2, 0, 0, 0, 1, 0, 0);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with BattleAnim_BuildReflectiveTextureDisplayList.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_AllocateReflectiveTextureDisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        BattleAnim_BuildReflectiveTextureDisplayList(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Seen in play (2026-11-13) (unattended all-Metronome Free Battle with randomized teams, battle 0
 * turn 8): ran. The move was not logged.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_ApplyEffect125ModelScaleOffset(Particle* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    f32 scale = 1.2f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case VENUSAUR:
            scale = 1.5f;
            break;
        case PIKACHU:
            scale = 0.6f;
            break;
        case NIDOKING:
            scale = 1.5f;
            break;
        case DUGTRIO:
            scale = 1.0f;
            break;
        case ALAKAZAM:
            scale = 0.9f;
            break;
        case MACHAMP:
            scale = 1.5f;
            break;
        case SCYTHER:
            scale = 1.5f;
            break;
        case GYARADOS:
            scale = 0.8f;
            break;
        case LAPRAS:
            scale = 0.8f;
            break;
        case DITTO:
            scale = 0.8f;
            break;
        case JOLTEON:
            scale = 0.8f;
            break;
        case AERODACTYL:
            scale = 2.5f;
            break;
        case SNORLAX:
            scale = 1.5f;
            break;
        case ARTICUNO:
            scale = 1.5f;
            break;
        case ZAPDOS:
            scale = 2.5f;
            break;
        case MOLTRES:
            scale = 1.5f;
            break;
    }
    Particle_PositionOffset_AddYScaled_08E90(arg0, 0.0f);
    Particle_SetScaleScaled(arg0, scale);
}

/**
 * Lifecycle init for effect 125: loads model 0x25 with anim 0x26 turned half a turn about
 * Y, applies the species scale and offset, and arms a 32-frame timer.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitEffect125Model(Particle* arg0, UNUSED s16 arg1) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x25, 0x26);
        Particle_Rotation_AddY_0A594(arg0, -0x8000);
        BattleAnim_ApplyEffect125ModelScaleOffset(arg0);
        Particle_Param0_SetS16_0BCA8(arg0, 0x20);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Particle callback for effect 125: inits the model, emits a burst of 8 sparkle hits when
 * the timer runs out, then shrinks and fades the model out before detaching.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackStartEffect125ModelBurstEmitter(Particle* arg0) {
    s16 temp_a1 = Particle_SpawnIndex_GetS16_0C038(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitEffect125Model(arg0, temp_a1);
            break;

        case 2:
            if (Particle_DecrementParam0ToZero(arg0) != 0) {
                BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 8, 0x18, 3);
                Particle_Param0_SetS16_0BCA8(arg0, 0x10);
            }
            break;

        case 3:
            Particle_ApproachScaleThenAdvance(arg0, 0.0f, 0.05f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 8);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Builds effect 125's display list: white primitive color with the display object's LOD
 * fraction as alpha, and two scrolling 32x32 tiles.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_BuildEffect125DisplayList(Gfx* arg0, u16 arg1) {
    DisplayObject* tmp = D_8006049C;

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, tmp->alpha);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, 1, 1, 0x20, 0x20);
    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, 2, 2, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 10 commands into arg1->unk_18 and
 * fills them with BattleAnim_BuildEffect125DisplayList.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_AllocateEffect125DisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 10);
        BattleAnim_BuildEffect125DisplayList(arg1->displayList, D_80060484);
    }
}

/**
 * Queues two effect slots on the current owner: func_82154EA4 at once (lifetime 30) and
 * func_82144750 after 20 frames (lifetime 80).
 */
void func_82155084(void) {
    func_8213B560(0, &func_82154EA4, &D_8218E580, 0x1E, 1, 7, 0, 0, 0);
    func_8213B560(0x14, &func_82144750, &D_8218E580, 0x50, 1, 0, 0, 0x33, 0);
}

/**
 * Lifecycle init for effect 65's full-screen overlay: centers it on the 320x240 screen
 * and picks the primitive and environment palette entries from the queued move (the
 * powder moves and Spore), starting fully transparent.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (4 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitEffect65Overlay(Particle* arg0) {
    s16 sp26;
    u16 sp24;
    u16 sp22;

    sp26 = BattleAnim_GetQueuedMoveId();
    sp24 = 0x17;
    sp22 = 0x8;
    Particle_EffectList_SetU8_0BECC(arg0, 7);
    Particle_SetScaleScaled(arg0, 1.0f);
    Particle_SetPosition(arg0, 160.0f, 120.0f, 0.0f);

    switch (sp26) {
        case STUN_SPORE:
        case SPORE:
            break;

        case POISONPOWDER:
            sp24 = 0x3B;
            sp22 = 0;
            break;

        case SLEEP_POWDER:
            sp24 = 0x33;
            break;
    }

    ParticleGfx_RecolorPrim(arg0, sp24);
    ParticleGfx_RecolorEnv(arg0, sp22);
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Moves: Poison Powder (use), Sleep Powder (use), Spore (use), Stun Spore (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Poison Powder, Stun Spore, Sleep Powder, Spore.
 */
void BattleAnim_RunSporePowderMoveOverlay(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitEffect65Overlay(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0xFF, 4);
            break;
    }
}

/**
 * Effect start init 65 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Poison Powder, Sleep Powder, Spore, Stun Spore.
 */
void ParticleEffect_RegisterParticleNodes(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSporePowderMoveOverlay, &gBattleAnimParticleDescriptors[0x32], 0, 1, 0x18, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSporePowderMoveOverlay, &gBattleAnimParticleDescriptors[0x31], 0, 1, 0x18, 0, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 3, 0x14, BattleAnim_PowderCloudScaleMotion, &gBattleAnimParticleDescriptors[0x46], 0, 1, 0x10, 0x64, 0, 0);
}

/**
 * Lifecycle init for effect 28's full-screen overlay: centers it on screen, takes its
 * palette pair from the particle's CF parameter and starts fully transparent.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (5 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitEffect28Overlay(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_EffectList_SetU8_0BECC(arg0, 7);
    Particle_SetScaleScaled(arg0, 1.0f);
    Particle_SetPosition(arg0, 160.0f, 120.0f, 0.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp26);
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Moves: Haze (use), Mist (use), Poison Gas (use), Smog (use), Smokescreen (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Mist, Smokescreen, Haze, Smog, Poison Gas.
 */
void BattleAnim_RunGasAttack(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitEffect28Overlay(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0xB4, 8);
            break;
    }
}

/**
 * Effect init for the start of the Haze and Poison Gas and Smokescreen animation.
 * Effect start init 28 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Haze, Poison Gas, Smokescreen.
 */
void BattleAnim_InitializeHazePoisonGasSmokescreenUse(void) {
    func_8213B560(8, &func_82155380, &D_8218E720, 0, 1, 0x18, 0, 0x1C, 0);
    func_8213B560(0, &func_82163D7C, &D_8218E7B8, 0, 0xF, 0x11, (s32) D_8219A80A, 0, 0);
}

/**
 * Effect init that spawns the Smog animation. Player sweep (all 165 moves used in battle): only
 * Smog reached this function.
 * Effect start init 76 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Smog.
 */
void BattleAnim_InitializeSmogUse(void) {
    func_8213B560(8, &func_82155380, &D_8218E720, 0, 1, 0x18, 0, 0x1E, 0);
    func_8213B560(0, &func_82163D7C, &D_8218E7B8, 0, 0xF, 0x11, (s32) D_8219A80A, 0, 0);
}

/**
 * Effect init that spawns the Mist animation. Player sweep (all 165 moves used in battle): only
 * Mist reached this function.
 * Effect start init 53 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Mist.
 */
void BattleAnim_InitializeMistUse(void) {
    func_8213B560(8, &func_82155380, &D_8218E720, 0, 1, 0x18, 0, 0x1D, 0);
    func_8213B560(0, &func_82163D7C, &D_8218E7B8, 0, 0xF, 0x11, (s32) D_8219A80A, 0, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Leech Seed.
 */
void BattleAnim_SetupLeechSeedUseEffect1(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.2f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0xD);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback of the Leech Seed animation. Player sweep (all 165 moves used in battle):
 * only Leech Seed reached this function.
 */
void BattleAnim_LeechSeedParticleUpdate(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215558C(arg0);
        break;
    case 2:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        Particle_ApproachPrimAlpha(arg0, 0x20, 0x18);
        break;
    case 3:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_82140228(arg0, 0x3DCCCCCD, 0x3C23D70A);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Leech Seed.
 */
void BattleAnim_SetupLeechSeedUseEffect2(Particle* arg0) {
    s16 sp2E = Particle_SpawnIndex_GetS16_0C038(arg0);

    Particle_SetScaleScaled(arg0, 0.5f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 4.5f);
    Particle_Rotation_AddVec_0A52C(arg0, ParticleMath_RandomSignedOffset(0x800, -0x3800), ParticleMath_RandomSigned(0x1400), 0);
    Particle_Param0_SetS16_0BCA8(arg0, sp2E * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback for effect 8 (Leech Seed use): sets up the seed, loads model 0x9F
 * after a delay, emits a sparkle hit, waits 30 frames, then spawns the Leech Seed
 * particle.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackStartEffect8ModelBurstEmitter(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupLeechSeedUseEffect2(arg0);
            break;

        case 2:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
                BattleAnim_InitModel(arg0->displayObject, 0x9F);
                Particle_EnableRendering(arg0);
                Particle_Param0_SetS16_0BCA8(arg0, ParticleMath_RandomRange(3));
            }
            break;

        case 3:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_RunSparkleHit, &D_8218E798, 1, 0x17, 4);
            }
            break;

        case 4:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 30);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_ApproachRotationXTo(arg0, 0x1800, 0x400);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_Rotation_AddZ_0A5B0(arg0, 0x2000);
        BattleAnim_EmitParticleBurst(arg0, BattleAnim_LeechSeedParticleUpdate, &D_8218E7D0, 1);
    }
}

/**
 * Lifecycle init for effect 31: loads model 0x2B with anim 0x2C at quarter scale with a
 * random rotation about Y.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name guessed from the code.
 */
void BattleAnim_InitEffect31Model(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x2B, 0x2C);
        Particle_SetScaleScaled(arg0, 0.25f);
        Particle_Rotation_SetY_0A2B8(arg0, ParticleMath_RandomRange(0x10000));
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Particle callback (lifecycle at 0xAE): starts after a random delay of up to 24 frames,
 * then when the spawn step reports done spawns a func_821624FC hit effect, and finishes once
 * the owner's model animation (+0x14) ends.
 */
void func_821558F4(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        Particle_SetParam0(arg0, ParticleMath_RandomRange(0x18));
        func_8213C9D0(arg0);
        return;
    case 2:
        if (func_82140690(arg0) != 0) {
            func_82155878(arg0);
            func_8213B560(0, &func_821624FC, &D_8218E798, 0, 1, 0x10, (s32) M2C_FIELD(arg0, u8 *, 0xC9), 0x17, 4);
            return;
        }
        return;
    case 3:
        if (func_8001104C(M2C_FIELD(arg0, s32 *, 0x14)) != 0) {
            func_8213C9D0(arg0);
        }
        break;
    }
}

/**
 * Effect start init 8 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Leech Seed.
 */
void BattleAnim_InitializeLeechSeedUse(void) {
    func_8213B5D8(0, 4, 5, &func_82155724, &D_8218E580, 0, 2, 0x11, (s32) D_8219A80A, 0, 0);
    func_8213B5D8(0, 8, 3, &func_82164AD0, &D_8218E7D0, 0, 1, 0x11, (s32) D_8219A80A, 0x33, 6);
}

/**
 * Effect end init 31 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Leech Seed.
 */
void BattleAnim_InitializeLeechSeedHit(void) {
    s32 i;
    s32 var_s2 = 0;
    s32 tmp;
    s32 end = gBattleAnimCurrentOwner->displayObject.anchorCount;

    if (end != 0) {
        for (i = 0; i < end; i++) {
            tmp = gBattleAnimCurrentOwner->displayObject.anchors[i].id;
            BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackMove73EndEffect31SpawnDescriptor42, &gDefaultParticleDescriptor, 0, 1, 0x10, tmp, 0, 0);
            var_s2++;
            if (var_s2 >= 8) {
                break;
            }
        }
    }
}

/**
 * initializes being hit by Pay Day
 * Effect end init 13 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Pay Day.
 */
void BattleAnim_InitializePayDayHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_InitializeParticleModel, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x22, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 2, 4, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 4, 9, 0, 0x17, 1);
}

/**
 * Builds a display list with the reflective camera and one animated 32x32 tile that
 * scrolls 2 units per frame in S.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_DrawSimple(Gfx* arg0, u8* arg1) {
    BattleAnim_SetupReflectiveCamera();
    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, 2, 0, 0, 0, 1, 0, 0, 0);
    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with ParticleEffect_DrawSimple.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_CreateSimpleDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawSimple(arg1->displayList, arg1->texture);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Blizzard.
 */
void BattleAnim_SetupBlizzardHitSpark(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocParticleDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x30);
        Particle_SetFlags(arg0, 0x200);
        Particle_SetScale(arg0, 5.3f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Particle callback of the Blizzard animation. Player sweep (all 165 moves used in battle): only
 * Blizzard reached this function.
 */
void BattleAnim_BlizzardParticleUpdate(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82155CC0(arg0);
        break;
    case 2:
        func_82140548(arg0, 0xFF, 0x20);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_8213831C(arg0 + 0x4C, 0x45674000);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Blizzard.
 */
void BattleAnim_SetupBlizzard(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);
    UNUSED s16 pad2; // FAKE: stack padding
    s16 sp22;

    Particle_FieldCE_GetS32_0C040(arg0);
    sp22 = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_Param0_SetS16_0BCA8(arg0, sp26 * 2);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetScaleScaled(arg0, 1.2f);
    Particle_SetScaleTarget(arg0, 1.0f);
    Particle_SetScaleStep(arg0, 0.02f);
    Particle_SetRandomVelocityXYZ(arg0, 5, 0xF, 0xF);
    Particle_PositionOffset_AddYScaled_08E90(arg0, 10.0f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.5f) + 8.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp22);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_ScratchA_SetS16_0BF4C(arg0, 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Blizzard.
 */
void BattleAnim_RunBlizzard(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82155DB8(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            Particle_SetParam0(arg0, 4);
            return;
        }
        return;
    case 3:
        func_821402B8(arg0);
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 1, 7, 1, 2, 0);
        func_8213E6BC(arg0);
        Particle_ApproachPrimAlpha(arg0, 0x40, 8);
        return;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * initializes using blizzard
 * Effect start init 34 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Blizzard.
 */
void BattleAnim_InitializeBlizzardUse(void) {
    func_8213B644(0, 0x10, 0x33);
    func_8213B8EC(0, 0xFF, 0x10, 8, 0x96);
    func_8213B560(0, &BattleAnim_BlizzardParticleUpdate, &D_8218E580, 0x1E, 1, 0x14, 0, 0, 0);
}

/**
 * initializes being hit by blizzard
 * Effect end init 23 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Blizzard.
 */
void BattleAnim_InitializeBlizzardHit(void) {
    func_8213B5D8(0, 8, 3, &func_82152F44, &D_8218E580, 0, 1, 0xC, 0, 0x2A, 0);
    func_8213BE70(4, 8, 0x33, 8, 0xC8, 0x18);
    func_8213B458(4);
    func_8213B5D8(0, 4, 6, &BattleAnim_RunBlizzard, &D_8218E7D0, 0, 4, 0xB, 9, 0x13, 0);
    func_8213B5D8(0, 2, 0xC, &func_821626F4, &D_8218E7A0, 0, 4, 0xB, 9, 0x18, 0xB);
    func_8213B5D8(0, 5, 4, &BattleAnim_RunBlizzardHitUpwardColdAir, &D_8218E650, 0, 6, 0x10, (s32) D_8219A80A, 0x26, 0);
    func_8213B644(0x32, 0x20, 8);
}

/**
 * Builds a display list for a 64x64 two-tile texture that scrolls in opposite directions,
 * using the owner particle's alpha on a white primitive color.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_DrawNode(Gfx* arg0, s32 arg1, u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x40, 6, -4, 0xF, 0, 0, -0xF, 5, 0, 0);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with ParticleEffect_DrawNode.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_CreateNodeDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawNode(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Like ParticleEffect_DrawNode, but with no color setup and a slower second tile.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_DrawNodeVariant(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x40, 6, -4, 0xF, 0, 0, -5, 5, 0, 0);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with ParticleEffect_DrawNodeVariant.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_CreateNodeVariantDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawNodeVariant(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Builds a display list with one offset, scrolling 32x32 two-tile texture and no camera
 * setup.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_DrawSimpleOffsetTileNoCamera(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, -8, -0x1E, 0, 0, -0xB, -0xA, 0, 0);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with ParticleEffect_DrawSimpleOffsetTileNoCamera.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_CreateSimpleOffsetTileNoCameraDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawSimpleOffsetTileNoCamera(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Empty draw hook used by end effects that draw nothing.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_DefaultEndEffect_Draw(void) {
}

/**
 * Lifecycle init for a model in a ring of three (model 0x31, anim 0x32, quarter scale,
 * raised 5 units): the CF parameter picks a rotation of 0, 1/3 or 2/3 of a turn.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name guessed from the code.
 */
void BattleAnim_InitMove146Model(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);
    s16 sp24;

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);

    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x31, 0x32);
        Particle_SetScaleScaled(arg0, 0.25f);
        Particle_PositionOffset_SetYScaled_08CA0(arg0, 5.0f);
        switch (sp26) {
            case 0:
                sp24 = 0;
                break;

            case 1:
                sp24 = 0x5555;
                break;

            case 2:
                sp24 = -0x5556;
                break;
        }

        Particle_Rotation_AddY_0A594(arg0, sp24);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Dizzy Punch.
 */
void BattleAnim_RunDizzyPunchHitEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitMove146Model(arg0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Effect end init 6 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Dizzy Punch.
 */
void BattleAnim_InitializeDizzyPunchHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDizzyPunchHitEffect, &gDefaultParticleDescriptor, 0x1E, 1, 6, gBattleAnimCurrentAnchor, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDizzyPunchHitEffect, &gDefaultParticleDescriptor, 0x1E, 1, 6, gBattleAnimCurrentAnchor, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDizzyPunchHitEffect, &gDefaultParticleDescriptor, 0x1E, 1, 6, gBattleAnimCurrentAnchor, 2, 0);
}

/**
 * Lifecycle init for effect 49, the draining orb of Absorb, Mega Drain and Leech Life:
 * picks the palette pair from the queued move and loads model 0x33.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitEffect49Model(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);
    u16 sp24;

    switch (BattleAnim_GetQueuedMoveId()) {
        case ABSORB:
            sp24 = 0x18;
            break;

        case MEGA_DRAIN:
            sp24 = 0x1F;
            break;

        case LEECH_LIFE:
            sp24 = 0x21;
            break;
    }

    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x33);
        if (sp26 == 0) {
            BattleAnim_BindModelAnim(arg0->displayObject, 0x34);
        } else {
            BattleAnim_BindModelAnimReversed(arg0->displayObject, 0x34);
        }
        Particle_SetScaleScaled(arg0, 1.0f);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Passed as a callback by ParticleEffect_RegisterColorAnim (a 2026-11-13 no-caller note here was
 * wrong). Not reached in play.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_CallbackEndEffect49Model33Anim34WaitCleanup(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            func_82156654(arg0);
            break;

        case 2:
            if (func_82136E2C(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Seen in play (2026-11-13) (unattended Free Battle in which every Pokémon knows only Metronome, 40
 * turns): ran.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_CallbackEndEffect21ModelAnimWait(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            func_82156654(arg0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Builds effect 49's display list from the owner particle's primitive and environment
 * colors.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_BuildEffect49DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 0);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with BattleAnim_BuildEffect49DisplayList.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_AllocateEffect49DisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        BattleAnim_BuildEffect49DisplayList(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Starts effect 49's model particle for the current animation owner.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_RegisterColorAnim(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffect49Model33Anim34WaitCleanup, &gDefaultParticleDescriptor, 0, 1, 2, gBattleAnimCurrentAnchor, 1, 0);
}

/**
 * Effect init for the end (impact) of the Absorb and Leech Life and Mega Drain animation.
 * Effect end init 21 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Absorb, Leech Life, Mega Drain.
 */
void BattleAnim_InitializeDrainingMoveHit(void) {
    switch (BattleAnim_GetQueuedMoveId()) {
        case LEECH_LIFE:
            BattleAnim_SpawnDrainFlameHueChange(0, 0xA, 0x3E, 2, 0xC8, 0x10);
            break;

        case ABSORB:
            BattleAnim_SpawnDrainFlameHueChange(0, 0x35, 0x3E, 2, 0xC8, 0x10);
            break;

        case MEGA_DRAIN:
            BattleAnim_SpawnDrainFlameHueChange(0, 0x27, 0x3E, 2, 0xC8, 0x10);
            break;
    }

    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffect21ModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 2, gBattleAnimCurrentAnchor, 0, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fly, Teleport.
 */
void BattleAnim_SetupFlyUpwardMovementEffect(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x35);
        Particle_SetScaleScaled(arg0, 5.0f);
        Particle_PositionOffset_AddYScaled_08E90(arg0, -100.0f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Handles the lines that give the impression of upward movement on the first turn of using fly.
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Fly, Teleport.
 */
void BattleAnim_RunFlyUpwardMovementEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupFlyUpwardMovementEffect(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0x80, 0x10);
            break;

        case 3:
            Particle_DecrementParam0ToZeroThenAdvance(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x20);
            break;
    }
}

/**
 * initializes the first turn of using fly
 * Effect start init 40 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Fly.
 */
void BattleAnim_InitializeFlyUse(void) {
    func_8213B560(0, &func_82156B0C, &D_8218E580, 0xA, 1, 0xA, 0, 0, 0);
}

/**
 * Effect start init 86 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Teleport.
 */
void BattleAnim_InitializeTeleportUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFlyUpwardMovementEffect, &gDefaultParticleDescriptor, 0x40, 1, 0xA, 0, 0, 0);
    BattleAnim_SpawnInvisibility(0, 0xFF, 0, 0x10);
    BattleAnim_SpawnInvisibility(0x2D, 0, 0xFF, 0x20);
}

/**
 * Builds effect 63's display list: two scrolling 32x32 tiles, the owner particle's alpha
 * on white, and a pink-red environment color.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_BuildEffect63DisplayList(Gfx* arg0, s32 arg1, u16 arg2) {
    UNUSED s32 pad; // FAKE: stack padding
    Particle* sp28 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, 1, 0x28, 0x20, 0x20);
    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, -1, 0x1E, 0x20, 0x20);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, sp28->prim_a);
    gDPSetEnvColor(arg0++, 255, 55, 100, 255); // #FF3764FF

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with BattleAnim_BuildEffect63DisplayList.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_AllocateEffect63DisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        BattleAnim_BuildEffect63DisplayList(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Builds effect 75's display list: the owner particle's alpha on white, with a yellow
 * environment color.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_BuildEffect75DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, 255, 255, 100, 255); // #FFFF64FF

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with BattleAnim_BuildEffect75DisplayList.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_AllocateEffect75DisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        BattleAnim_BuildEffect75DisplayList(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Strength, Rock Throw and Rock Slide.
 */
void BattleAnim_InitRockModel(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        if (sp26 == 0) {
            BattleAnim_InitModelWithAnim(arg0->displayObject, 0x36, 0x37);
            Particle_SetScaleScaled(arg0, 0.75f);
        } else {
            BattleAnim_InitModelWithAnim(arg0->displayObject, 0x61, 0x62);
            Particle_SetScaleScaled(arg0, 1.0f);
        }
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Strength, Rock Throw and Rock Slide.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_RockModelAnimWait(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            func_82156E54(arg0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Lifecycle init shared by effects 10 and 50: loads model 0x39 (anim 0x3A) at half scale
 * and moves it to one of several fixed offsets chosen by the CF parameter.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_InitEffects10And50Model(Particle* arg0) {
    u16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x39, 0x3A);
        Particle_SetScaleScaled(arg0, 0.5f);

        switch (sp26) {
            case 0:
                break;

            case 1:
                Particle_PositionOffset_AddVecScaled_08E18(arg0, -10.0f, 0.0f, 20.0f);
                break;

            case 2:
                Particle_PositionOffset_AddVecScaled_08E18(arg0, 10.0f, 0.0f, -20.0f);
                break;

            case 3:
                Particle_PositionOffset_AddVecScaled_08E18(arg0, 20.0f, 0.0f, -20.0f);
                break;

            case 4:
                Particle_PositionOffset_AddVecScaled_08E18(arg0, -20.0f, 0.0f, 20.0f);
                break;

            case 5:
                Particle_PositionOffset_AddVecScaled_08E18(arg0, 15.0f, 0.0f, -25.0f);
                break;

            case 6:
                Particle_PositionOffset_AddVecScaled_08E18(arg0, 20.0f, 0.0f, 30.0f);
                break;

            case 7:
                Particle_PositionOffset_AddVecScaled_08E18(arg0, 15.0f, 0.0f, -10.0f);
                break;

            case 8:
                Particle_SetScaleScaled(arg0, 1.5f);
                break;
        }
        Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Moves: Rock Slide (hit), Rock Throw (hit), Strength (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Strength, Rock Throw, Rock Slide.
 */
void BattleAnim_RunFallingRock(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82156F70(arg0);
        return;
    case 2:
        func_8213CA80(arg0, 0xA);
        return;
    case 3:
        Particle_ApproachPrimRed(arg0, 0, 0x10);
        Particle_ApproachPrimGreen(arg0, 0, 0x20);
        if (func_8001104C(M2C_FIELD(arg0, s32 *, 0x14)) != 0) {
            func_8213C9D0(arg0);
            return;
        }
        return;
    case 4:
        Particle_DisableAndDetach(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Strength, Rock Throw and Rock Slide.
 */
void BattleAnim_ApplyRockSpeciesScaleOffset(Particle* arg0) {
    f32 sp1C = 0.6f;
    f32 sp18 = 0.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case VENUSAUR:
            sp1C = 1.0f;
            sp18 = 5.0f;
            break;

        case NIDOKING:
            sp1C = 1.0f;
            sp18 = 5.0f;
            break;

        case GOLEM:
            sp1C = 0.8f;
            sp18 = 5.0f;
            break;

        case GENGAR:
            sp1C = 0.8f;
            sp18 = 5.0f;
            break;

        case TAUROS:
            sp1C = 0.8f;
            sp18 = 10.0f;
            break;

        case GYARADOS:
            sp18 = 20.0f;
            break;

        case FLAREON:
            sp1C = 1.2f;
            sp18 = 10.0f;
            break;

        case AERODACTYL:
            sp1C = 1.2f;
            sp18 = 20.0f;
            break;

        case ZAPDOS:
            sp1C = 1.2f;
            sp18 = 15.0f;
            break;

        case DRAGONITE:
            sp18 = 10.0f;
            break;
    }

    Particle_SetScaleScaled(arg0, sp1C);
    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, sp18);
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Strength, Rock Throw and Rock Slide.
 */
void BattleAnim_InitRockModel38(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x38);
        BattleAnim_ApplyRockSpeciesScaleOffset(arg0);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (Strength, Rock Throw): step 1 attached a model
 * and set prim alpha to 0; step 2 then raised prim alpha by 4 per frame (0, 4, 8, ...).
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Strength, Rock Throw and Rock Slide.
 */
void BattleAnim_RockModelFadeIn(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            func_82157354(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0xFF, 4);
            break;
    }
}

/**
 * Builds a display list with the owner particle's alpha on white, an orange environment
 * color and a scrolling two-tile texture.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticleAlpha(Gfx* arg0, s32 arg1, u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0xC8, 255, 255, 255, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, 255, 155, 0, 255); // #FF9B00FF

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 1, 0, 0, 0, -1, 0, 0, 0);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticleAlpha.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_CreateDisplayList_Alpha(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleAlpha(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Builds a display list that loads a 32x32 4-bit intensity texture, tinted orange, with
 * the owner particle's prim_r field used as the alpha.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticleTexture4b(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, temp_v0->prim_r);
    gDPSetEnvColor(arg0++, 255, 155, 0, 255); // #FF9B00FF
    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);
    gDPSetTextureLUT(arg0++, G_TT_NONE);
    gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock_4b(arg0++, arg1, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticleTexture4b.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_CreateDisplayList_Texture4b(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleTexture4b(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Same as Gfx_DrawParticleTexture4b but tinted yellow, with the owner particle's prim_g
 * field used as the alpha.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticleGreenPrim(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, temp_v0->prim_g);
    gDPSetEnvColor(arg0++, 255, 255, 0, 255); // #FFFF00FF
    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);
    gDPSetTextureLUT(arg0++, G_TT_NONE);
    gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock_4b(arg0++, arg1, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticleGreenPrim.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_CreateDisplayList_GreenPrim(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleGreenPrim(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Effect init for the start of the Rock Slide and Rock Throw animation.
 * Effect start init 63 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Rock Slide, Rock Throw.
 */
void BattleAnim_InitializeRockThrowRockSlideUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RockModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RockModelFadeIn, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
}

/**
 * Effect end init 10 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Rock Slide, Rock Throw.
 */
void BattleAnim_InitializeRockSlideRockThrowHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(2, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 2, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(5, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 3, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(9, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 5, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(10, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 6, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(13, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 7, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(10, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect start init 75 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Strength.
 */
void BattleAnim_InitializeStrengthUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RockModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 1, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RockModelFadeIn, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
}

/**
 * Effect end init 50 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Strength.
 */
void BattleAnim_InitializeStrengthHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffects10And50ModelAnimColorFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 8, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(10, 3, 2, BattleAnim_HeavyHitAnimatedRiseFade, &gBattleAnimParticleDescriptors[0x3E], 0, 0x10, 0xA, 0, 0x11, 0);
}

/**
 * Effect start init 64 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Egg Bomb.
 */
void BattleAnim_InitializeEggBombUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x23, 0);
}

/**
 * Seen in play (2026-11-12): Soft-Boiled used with 1P's HP lowered to 20 ran this as start effect
 * 0x42.
 */
void BattleAnim_InitializeSoftBoiledUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x24, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 1, 0x24, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 2, 0x24, 0);
    BattleAnim_SpawnOwnerModelTintPulseDetach(0x5F, 0, 0x8, 0, 0xFF, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(95, 8, 0xC, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0x17, 6);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Gust, Whirlwind.
 */
void BattleAnim_SetupStrongWinds(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0x60);
        Particle_EffectList_SetU8_0BECC(arg0, 7);
        Particle_SetFlags(arg0, 0x200);
        Particle_SetScale(arg0, 3.3f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Particle callback: init, fade alpha toward 155, then mark inactive. While running it
 * keeps motionOffset (+0x4C) moving toward 200.
 */
void func_82157E28(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82157DA0(arg0);
        break;
    case 2:
        Particle_ApproachPrimAlpha(arg0, 0x9B, 8);
        break;
    case 3:
        Particle_MarkInactive(arg0);
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        func_8213831C(arg0 + 0x4C, 0x43480000);
    }
}

/**
 * Builds a display list with a light cyan environment color and a scrolling two-tile
 * texture.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticleCyanEnv(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);
    gDPSetEnvColor(arg0++, 155, 255, 255, 255); // #9BFFFFFF

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 2, 1, 0xE, 0xF, 0, 4, 0xC, 5);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticleCyanEnv.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_CreateDisplayList_CyanEnv(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleCyanEnv(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Builds a display list with the owner particle's alpha on white, a cyan environment
 * color and a scrolling two-tile texture.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticleBluePrim(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, 0, 255, 255, 255); // #00FFFFFF

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, -3, -5, 0xD, 3, 0, -2, 0xF, 2);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticleBluePrim.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (3 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_CreateDisplayList_BluePrim(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleBluePrim(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Full screen overlay for gust, razor wind, and whirlwind
 * Effect start init 10 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Gust, Whirlwind.
 */
void BattleAnim_InitializeStrongWind(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xE, 0, 0x25, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect10Model60AlphaFadeIn, &gDefaultParticleDescriptor, 0, 1, 0x14, 0, 0, 0);
}

/**
 * initializes charging razor wind
 * Effect start init 72 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Razor Wind.
 */
void BattleAnim_InitializeRazorWindUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xE, 0, 0x25, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_RunBoomUseEffect1(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            break;

        case 2:
            Particle_TickDelayAndAdvanceLifecycle(arg0, arg0->param0);
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (Selfdestruct): it set scale to 7.2 (2.0 times
 * 3.6), moved positionOffset.x by -36 (10 along rotation.y + 0x8000), set a random rotation.z
 * (0xF0E2) and advanced the lifecycle.
 */
void BattleAnim_CallbackStartEffects50And82ScalePulse_InitParticle(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 2.0f);
    Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 10.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTextureFrame(arg0, 1);
    Particle_Rotation_SetZ_0A2CC(arg0, ParticleMath_RandomRange(0x10000));
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_RunBoomUseEffect2(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_CallbackStartEffects50And82ScalePulse_InitParticle(arg0);
            break;

        case 2:
            Particle_ApproachScaleThenAdvance(arg0, 10.0f, 1.0f);
            break;

        case 3:
            Particle_ApproachScaleThenAdvance(arg0, 0.0f, 1.0f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x40, 0x20);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_SetupBoomUseEffect3(Particle* arg0) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp34;
    Vec3s sp2C;
    UNUSED s32 pad2[3]; // FAKE: stack padding

    Particle_SpawnIndex_GetS16_0C038(arg0);
    sp34 = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_SetRandomVelocityXYZ(arg0, 5, 5, 5);
    Particle_SetScaleScaled(arg0, 1.5f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 1.5f);
    sp2C.x = ParticleMath_RandomRange(0x2000) - 0x1000;
    sp2C.y = ParticleMath_RandomRange(0x10000);
    sp2C.z = 0;
    Particle_Rotation_AddVecFromVec3s_0A4F0(arg0, sp2C);
    Particle_AddRotationTargetXY(arg0, sp2C.x, sp2C.y);
    Particle_RotationStep_SetXY_0A3A0(arg0, 0, 0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp34);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_Param0_SetS16_0BCA8(arg0, arg0->spawnIndex * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_RunBoomUseEffect3(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82158344(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            Particle_SetParam0(arg0, 0xA);
            func_8213CB3C(arg0);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        func_82140228(arg0, 0x40200000, 0x3E800000);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        Particle_AddPosOffsetYScaled(arg0, 0.5f);
        if (func_82140690(arg0) != 0) {
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x10);
            Particle_ApproachPrimGreen(arg0, 0, 0x14);
            Particle_ApproachEnvRed(arg0, 0, 0x14);
            return;
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_SetupBoomUseEffect4(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    UNUSED s16 pad2; // FAKE: stack padding
    s16 sp24;

    Particle_SpawnIndex_GetS16_0C038(arg0);
    sp24 = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_FieldCE_GetS32_0C040(arg0);
    Particle_SetScaleScaled(arg0, 1.0f);
    Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0x14);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0x32) * 0.02f) + 1.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_RunBoomUseEffect4(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215856C(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            Particle_SetParam0(arg0, 5);
            return;
        }
        return;
    case 3:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        func_8213E77C(arg0);
        if (func_82140690(arg0) != 0) {
            Particle_ApproachPrimGreen(arg0, 0, 0x14);
            Particle_ApproachEnvRed(arg0, 0, 0x14);
            Particle_ApproachPrimAlpha(arg0, 0x20, 4);
            return;
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * Builds a display list from the owner particle's own primitive and environment colors,
 * blending two scrolling tiles by the LOD fraction.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticleCustomColors(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x78, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, temp_v0->scratchB);
    gDPSetCombineLERP(arg0++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, ENVIRONMENT);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 2, 0xA, 0xD, 0xF, -2, 5, 0xE, 0xF);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticleCustomColors.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (5 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_CreateDisplayList_CustomColors(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleCustomColors(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Particle callback: init with scale 0.5, field B0 100, palette 0x17 and a 5-frame delay;
 * then grows toward scale 7 by 0.25 with 5-frame delays between stages before it is marked
 * inactive.
 */
void func_821588C0(Particle* arg0) {
    s16 temp_v1;

    Particle_GetUnkCE();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_82152730(arg0, 2);
        func_821401D4(arg0, 0x3F000000);
        Particle_SetScratchB(arg0, 0x64);
        func_82143478(arg0, 0x17);
        Particle_SetParam0(arg0, 5);
        return;
    case 2:
        func_82140228(arg0, 0x40E00000, 0x3E800000);
        if (func_821406B4(arg0) != 0) {
            Particle_SetParam0(arg0, 5);
            return;
        }
        return;
    case 3:
        func_82140228(arg0, 0x40E00000, 0x3E800000);
        func_821437E0(arg0, 0x1A, 0x19);
        if (func_82140690(arg0) != 0) {
            Particle_ApproachScratchB(arg0, 0, 8);
            func_82140548(arg0, 0, 0x10);
            return;
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_RunBoomUseEffect6(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 2);
            Particle_SetScaleScaled(arg0, 0.5f);
            Particle_ScratchB_SetS16_0BFEC(arg0, 0x64);
            ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x17);
            Particle_Param0_SetS16_0BCA8(arg0, 5);

            switch (sp26) {
                case 0:
                    Particle_PositionOffset_SetXScaled_08C88(arg0, 15.0f);
                    Particle_PositionOffset_SetYScaled_08CA0(arg0, 15.0f);
                    break;

                case 1:
                    Particle_PositionOffset_SetXScaled_08C88(arg0, -15.0f);
                    Particle_PositionOffset_SetZScaled_08CB8(arg0, 15.0f);
                    Particle_PositionOffset_SetYScaled_08CA0(arg0, -10.0f);
                    break;

                case 2:
                    Particle_PositionOffset_SetXScaled_08C88(arg0, -10.0f);
                    Particle_PositionOffset_SetZScaled_08CB8(arg0, -15.0f);
                    break;
            }
            break;

        case 2:
            Particle_ApproachScale(arg0, 5.0f, 0.15f);
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_Param0_SetS16_0BCA8(arg0, 5);
            }
            break;

        case 3:
            Particle_ApproachScale(arg0, 5.0f, 0.15f);
            ParticleGfx_ApproachPrimEnvPalettePair(arg0, 0x1A, 0x19);
            if (Particle_DecrementParam0ToZero(arg0) != 0) {
                Particle_ScratchB_Approach_0C000(arg0, 0, 8);
                Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x10);
            }
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_RunBoomHitEffect1(Particle* arg0) {
    s16 temp_v1;

    Particle_GetUnkCE();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_82152730(arg0, 2);
        func_821401D4(arg0, 0x3E800000);
        Particle_SetScratchB(arg0, 0x64);
        func_82143478(arg0, 0x17);
        Particle_SetParam0(arg0, 5);
        func_8213D644(arg0, 30.0f);
        return;
    case 2:
        func_82140228(arg0, 0x40A00000, 0x3E99999A);
        if (func_821406B4(arg0) != 0) {
            Particle_SetParam0(arg0, 5);
            return;
        }
        return;
    case 3:
        func_82140228(arg0, 0x40A00000, 0x3E99999A);
        func_821437E0(arg0, 0x1A, 0x19);
        if (func_82140690(arg0) != 0) {
            Particle_ApproachScratchB(arg0, 0, 8);
            func_82140548(arg0, 0, 0x10);
            return;
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_SetupBoomHitEffect2(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);

    Particle_FieldCE_GetS32_0C040(arg0);
    Particle_FieldCF_GetS16_0C058(arg0);
    Particle_Param0_SetS16_0BCA8(arg0, sp26 * 2);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetScaleScaled(arg0, 1.2f);
    Particle_SetScaleTarget(arg0, 1.0f);
    Particle_SetScaleStep(arg0, 0.02f);
    Particle_SetRandomVelocityXYZ(arg0, 5, 0xF, 0xF);
    Particle_PositionOffset_AddYScaled_08E90(arg0, 10.0f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.5f) + 8.0f);
    ParticleGfx_RecolorPrim(arg0, 0x17);
    ParticleGfx_RecolorEnv(arg0, 0x17);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_ScratchA_SetS16_0BF4C(arg0, 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_RunBoomHitEffect2(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82158CE0(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            Particle_SetParam0(arg0, 4);
            return;
        }
        return;
    case 3:
        func_821402B8(arg0);
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 1, 7, 1, 2, 0);
        func_8213E6BC(arg0);
        Particle_ApproachPrimGreen(arg0, 0, 0x20);
        Particle_ApproachEnvGreen(arg0, 0, 0x20);
        if (func_82140690(arg0) != 0) {
            return;
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_SetupBoomHitEffect3(Particle* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);
    UNUSED s16 pad2; // FAKE: stack padding
    s16 sp22;

    Particle_FieldCE_GetS32_0C040(arg0);
    sp22 = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_Param0_SetS16_0BCA8(arg0, sp26 * 2);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetScaleScaled(arg0, 1.0f);
    Particle_SetScaleTarget(arg0, 0.5f);
    Particle_SetScaleStep(arg0, 0.01f);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0xF);
    Particle_AddPositionOffsetAlongRotationY(arg0, 10.0f);
    Particle_PositionOffset_AddYScaled_08E90(arg0, 5.0f);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, (ParticleMath_RandomRange(0xA) * 0.5f) + 8.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp22);
    Particle_SetPrimAlpha(arg0, 0xB4);
    Particle_ScratchA_SetS16_0BF4C(arg0, 4);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Self-Destruct, Explosion.
 */
void BattleAnim_RunBoomHitEffect3(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82158F20(arg0);
        break;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            Particle_SetParam0(arg0, 4);
        }
        break;
    case 3:
        func_82140548(arg0, 0x40, 0x10);
        if (func_82140690(arg0) != 0) {
            func_821437E0(arg0, 0x16, 0x20);
        }
        Particle_ApproachStepMagnitude(arg0, 0x40800000, 0x3F000000);
        func_8213E6BC(arg0);
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        func_821402B8(arg0);
        Particle_AnimateFramesForwardLooped(arg0, 0, 7, 1, 2, 0);
    }
}

/**
 * Effect start init 50, start init 82 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all
 * 165 moves used: it ran for exactly Explosion, Self Destruct.
 */
void BattleAnim_InitializeBoomUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunBoomUseEffect1, &gDefaultParticleDescriptor, 0x19, 1, 0xE, 0, 0x27, 0);
    BattleAnim_SpawnDescriptor25AlphaFadeInHold(0, 0, 4, 0x8, 0x80);
    BattleAnim_CreateEffectSlotForCurrentOwner(22, BattleAnim_RunBoomUseEffect2, &D_8218E580[0x54], 0, 1, 0xC, 0, 0x33, 0);
    BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(0x1A, 3, 0x20, 0x8, 0xC8);
    BattleAnim_CreateEffectSlotForCurrentOwner(27, BattleAnim_CallbackStartEffects50And82CenterModelScalePaletteFade, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x21, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(30, BattleAnim_RunBoomUseEffect6, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x21, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(34, BattleAnim_RunBoomUseEffect6, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x21, 1);
    BattleAnim_CreateEffectSlotForCurrentOwner(38, BattleAnim_RunBoomUseEffect6, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x21, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(40, BattleAnim_CallbackStartEffects50And82Descriptor48AnimatedScaleFade, &D_8218E580[0x48], 0, 6, 0x10, 9, 0x1A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(50, 2, 2, BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade, &D_8218E580[0x4A], 0, 1, 9, 0, 0x1A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(51, 2, 2, BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade, &D_8218E580[0x4A], 0, 1, 9, 0, 0x1A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(52, 2, 2, BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade, &D_8218E580[0x4A], 0, 1, 9, 0, 0x1A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(54, 2, 2, BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade, &D_8218E580[0x4A], 0, 1, 9, 0, 0x1A, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x16, 0x8, 0, 0xFF, 0x40);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x24, 0x8, 0xFF, 0xDC, 0xC);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x28, 0x8, 0x17, 0x10, 0xDC);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x38, 0x17, 0x11, 0x10, 0xDC);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x40, 0x11, 0xE, 0x10, 0xDC);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x48, 0xE, 0xDC, 0xB4, 6);
}

/**
 * Effect end init 81, end init 82 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165
 * moves used: it ran for exactly Explosion, Self Destruct.
 */
void BattleAnim_InitializeBoomHit(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0xFF, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffects81And82ModelScalePaletteFade, &gDefaultParticleDescriptor, 0, 1, 0xB, 0, 0x21, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackEndEffects81And82ModelScalePaletteFade, &gDefaultParticleDescriptor, 0, 1, 0xB, 0, 0x21, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(10, 8, 4, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xC, 0, 0x8, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(12, 8, 5, BattleAnim_CallbackEndEffects81And82Descriptor46AnimatedFade, &D_8218E580[0x46], 0, 5, 0x10, 9, 0x48, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(12, 4, 0xA, BattleAnim_CallbackEndEffects81And82Descriptor4AAnimatedColorFade, &D_8218E580[0x4A], 0, 4, 0xB, 9, 0, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(12, 4, 0xA, BattleAnim_CallbackEndEffects81And82Descriptor4FAnimatedPaletteFade, &D_8218E580[0x4F], 0, 4, 0xE, 9, 0x1A, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(3, 0x8, 0, 0xFF, 0x40);
    BattleAnim_SpawnOwnerModelTintRampDetach(0xA, 0x8, 0xFF, 0xE6, 5);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x10, 0x8, 0x17, 0x10, 0xDC);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x18, 0x17, 0x9, 0x10, 0xD2);
    BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(0x28, 0x9, 0xE, 0x10, 0xC8);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x30, 0xE, 0xC8, 0xB4, 6);
}

/**
 * Empty.
 */
void func_821597B8(UNUSED ActivePokemon* active_pokemon, UNUSED s32 unused) {
}

/**
 * Model transform hook that does nothing.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_TransformNop(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon) {
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Vise Grip, Guillotine, Bite, Clamp, Hyper Fang, Super Fang.
 */
void BattleAnim_SetupBitingEffect(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    arg0->displayObject = BattleAnim_AllocParticleDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        if (sp26 == 0) {
            BattleAnim_InitModel(arg0->displayObject, 0x55);
        } else {
            BattleAnim_InitModel(arg0->displayObject, 0x63);
        }
        BattleAnim_BindModelAnim(arg0->displayObject, 0x56);
        Particle_SetFlags(arg0, 0x200);
        Particle_EffectList_SetU8_0BECC(arg0, 7);
        Particle_SetScale(arg0, 1.0f);
        ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x24);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Particle callback: init, then a color stage that brightens prim green/blue, env green and
 * alpha, then one that fades blue and green back out. While running it moves motionOffset
 * toward 140.
 */
void func_82159898(s8 *arg0) {
    s16 sp26;
    s16 temp_v1;

    sp26 = func_8213C484();
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v1) {                              /* irregular */
    case 1:
        func_821597D0(arg0);
        break;
    case 2:
        func_8213CA80(arg0, 0xE);
        Particle_ApproachPrimGreen(arg0, 0xFF, 7);
        Particle_ApproachPrimBlue(arg0, 0xFF, 0x13);
        Particle_ApproachEnvGreen(arg0, 0xFF, 0x13);
        Particle_ApproachPrimAlpha(arg0, 0xFF, 0x13);
        break;
    case 3:
        func_8213CA80(arg0, 0x10);
        Particle_ApproachPrimBlue(arg0, 0, 0x11);
        Particle_ApproachEnvGreen(arg0, 0, 0x11);
        Particle_ApproachPrimAlpha(arg0, 0, 0x11);
        break;
    case 4:
        if (func_8001104C(M2C_FIELD(arg0, s32 *, 0x14)) != 0) {
            Particle_MarkInactive(arg0);
        }
        break;
    }
    if (Particle_IsRunning(arg0) != 0) {
        if (sp26 == 0) {
            func_8213831C(arg0 + 0x4C, 0x432A0000);
            return;
        }
        func_8213831C(arg0 + 0x4C, 0x430C0000);
    }
}

/**
 * Builds a display list from the owner particle's primitive and environment colors with a
 * static (non-scrolling) tile.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (6 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticleFromTempColors(Gfx* arg0, s32 arg1, u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 0);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 0, 0, 0, 0, 0, 0, 0, 0);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticleFromTempColors.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (6 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_CreateDisplayList_TempColors(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleFromTempColors(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Effect start init 71 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Clamp, Vice Grip.
 */
void BattleAnim_InitializeClampViceGripUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle, &gDefaultParticleDescriptor, 0, 1, 0x14, 0, 0, 0);
}

/**
 * initializes using guillotine
 * Effect start init 111 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Guillotine.
 */
void BattleAnim_InitializeGuillotineUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle, &gDefaultParticleDescriptor, 0, 1, 0x14, 0, 0, 0);
}

/**
 * Moves: Bite (use), Hyper Fang (use), Super Fang (use)
 * TODO: Human contributor add screenshot
 * Effect start init 74 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Bite, Hyper Fang, Super Fang.
 */
void BattleAnim_InitializeBitingMoveUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle, &gDefaultParticleDescriptor, 0, 1, 0x14, 0, 1, 0);
}

/**
 * Moves: Bite (hit), Clamp (hit), Hyper Fang (hit), Super Fang (hit), Vice Grip (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 41 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Bite, Clamp, Hyper Fang, Super Fang, Vice Grip.
 */
void BattleAnim_InitializeBitingMoveHit(void) {
    BattleAnim_InitializeBitingMoveEndEffect();
}

/**
 * initializes being hit by guillotine
 * Seen in play (2026-11-13) (Free Battle, 1P Onix's Guillotine with its accuracy raised so it
 * lands): called through the effect table as the hit animation started, and Pinsir dropped from
 * 75 to 0 HP. In the earlier sweep Guillotine missed and this did not run.
 */
void BattleAnim_InitializeGuillotineHit(void) {
    func_8213BC00(0, 0xA, 0, 0xFF, 0x40);
    func_82166B34();
    func_8213BC00(0x30, 0xA, 0xFF, 0, 2);
}

/**
 * Builds a display list with two tiles that scroll diagonally in opposite directions.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticleDualTileDiagonal4(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    BattleAnim_GetOwnerContextParticle(D_8006049C);
    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, -4, -4, 0xD, 6, 4, 4, 0xF, 1);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticleDualTileDiagonal4.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_CreateDisplayList_DualTileDiagonal4(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleDualTileDiagonal4(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Builds a display list with two tiles that scroll slowly along the anti-diagonal in
 * opposite directions.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticleDualTileAntiDiagonal1(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    BattleAnim_GetOwnerContextParticle(D_8006049C);
    arg0 = BattleAnim_BuildAnimatedTileDisplayList(arg0, arg1, 0x20, 5, 1, -1, 0xE, 0xE, -1, 1, 2, 2);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticleDualTileAntiDiagonal1.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Particle_CreateDisplayList_DualTileAntiDiagonal1(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticleDualTileAntiDiagonal1(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * initializes using swords dance
 * Effect start init 68 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Swords Dance.
 */
void BattleAnim_InitializeSwordsDanceUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 2, 0, 0x28, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 8, 0xC, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 8, 9, 0, 0x22, 6);
}

/**
 * Returns the effect scale for the owner's species: 1.45 for Arcanine, 0.9 for Onix
 * (which also moves the effect 20 units sideways) and Gyarados, otherwise 1.0.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
f32 BattleAnim_GetSpeciesScaleAdjust(Particle* arg0) {
    f32 sp1C = 1.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case ARCANINE:
            sp1C = 1.45f;
            break;

        case ONIX:
            Particle_AddPositionOffsetAlongRotationYMinus90(arg0, 20.0f);
            sp1C = 0.9f;
            break;

        case GYARADOS:
            sp1C = 0.9f;
            break;
    }
    return sp1C;
}

/**
 * Particle callback for effect 69: selects the model frames, idles until something else
 * advances its lifecycle, then detaches.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackStartEffect69ModelPhaseWait(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            break;

        case 2:
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Effect init for the start of the Dig animation.
 * Effect start init 69 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Dig.
 */
void BattleAnim_InitializeDigBurrowUse(void) {
    func_8213B560(0, &func_82159F70, &D_8218E580, 0, 1, 0xA, 0, 0x29, 0);
    func_8213B5D8(5, 2, 0xA, &BattleAnim_RunDigHitDust, &D_8218E7D0, 0, 2, 0xA, 0, 0x44, 9);
    func_8213B5D8(0xA, 5, 6, &BattleAnim_RunDigHitRocks, &D_8218E708, 0, 3, 0xA, 0, 0x44, 0xB);
}

/**
 * Seen in play (2026-11-12): Dig's second turn, the attack out of the ground, ran this as start
 * effect 0x34. The first turn uses 0x45 (BattleAnim_InitializeDigBurrowUse).
 */
void BattleAnim_InitializeDigUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_InitializeParticleModel, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x16, 0);
}

/**
 * Seen in play (2026-11-12): Dig's second turn ran this as end effect 0x4E.
 */
void BattleAnim_InitializeDigHit(void) {
    func_8213B560(0, &func_82152FB0, &D_8218E580, 0, 1, 0xA, 0, 0x1D, 0);
    func_8213B5D8(0, 3, 3, &func_82162C68, &D_8218E728, 0, 1, 0xE, 9, 0, 0xF);
    func_8213B5D8(4, 1, 4, &BattleAnim_RunDigHitDust, &D_8218E7D0, 0, 8, 0x1B, 0, 0x44, 0xA);
    func_8213B560(4, &BattleAnim_RunDigHitRocks, &D_8218E708, 0, 0xC, 0x1B, 0, 0x44, 0xB);
}

/**
 * Effect start init 55 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Kinesis.
 */
void BattleAnim_InitializeKinesisUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xB, 0, 0, 0);
    BattleAnim_SpawnCategory19MarkerSlot(0x28, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(4, 4, 3, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 0, 4, 0xB, 0, 0x17, 0xA);
}

/**
 * Effect start init 79 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Bone Club.
 */
void BattleAnim_InitializeBoneClubUse(void) {
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 4, 0, 1, 0);
    func_8213B720(0x1D, 2, 0x20, 0x12);
}

/**
 * Effect start init 80 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Bonemerang.
 */
void BattleAnim_InitializeBonemerangUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xB, gBattleAnimCurrentAnchor, 2, 0);
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Acid, Toxic and Sludge.
 */
void BattleAnim_SludgeModelAnimFinish_InitParticle(Particle* arg0) {
    Particle_FieldCD_GetU8_0C048(arg0);
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x71, 0x72);
        Particle_SetScaleScaled(arg0, 1.0f);
        Particle_Param0_SetS16_0BCA8(arg0, 30);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Acid, Toxic and Sludge.
 */
void BattleAnim_SludgeModelAnimFinish(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SludgeModelAnimFinish_InitParticle(arg0);
            break;

        case 2:
            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Acid, Toxic, Lick, Sludge.
 */
void BattleAnim_SetupSlimePuddle(Particle* arg0) {
    s16 sp26 = Particle_FieldCD_GetU8_0C048(arg0);

    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        switch (sp26) {
            case 0:
                Particle_SetPosition(arg0, 8.0f, 0.0f, -10.0f);
                break;

            case 1:
                Particle_SetPosition(arg0, -10.0f, 0.0f, 12.0f);
                break;

            case 2:
                Particle_SetPosition(arg0, 0.0f, 0.0f, -2.0f);
                break;

            case 3:
                Particle_SetPosition(arg0, 15.0f, 0.0f, 3.0f);
                break;
        }

        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x6E, 0x6F);
        Particle_SetScaleScaled(arg0, 1.0f);
        Particle_Param0_SetS16_0BCA8(arg0, 30);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Moves: Acid (hit), Lick (hit), Sludge (hit), Toxic (hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Acid, Toxic, Lick, Sludge.
 */
void BattleAnim_RunSlimePuddle(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupSlimePuddle(arg0);
            break;

        case 2:
            Particle_DecrementParam0ToZeroThenAdvance(arg0);
            break;

        case 3:
            Particle_ApproachScaleThenAdvance(arg0, 0.0f, 0.05f);
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x10);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Builds a display list for a 32x32 RGBA16 texture whose primitive and environment colors
 * come from a table keyed by the owner particle's CF parameter.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (4 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_DrawParticlePaletteBased(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s16 sp2E = Particle_FieldCF_GetS16_0C058(BattleAnim_GetOwnerContextParticle(D_8006049C));
    u8 sp2D;
    u8 sp2C;
    u8 sp2B;
    u8 sp2A;
    u8 sp29;
    u8 sp28;

    gDPLoadTextureBlock(arg0++, arg1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, 5, 0, 0x20, 0x20);

    switch (sp2E) {
        case 0:
            sp2D = 0x96;
            sp2C = 0x32;
            sp2B = 0x32;
            sp2A = 0;
            sp29 = 0;
            sp28 = 0;
            break;

        case 1:
            sp2D = 0x78;
            sp2C = 0x96;
            sp2B = 0;
            sp2A = 0x64;
            sp29 = 0x78;
            sp28 = 0;
            break;

        case 2:
            sp2D = 0x46;
            sp2C = 0;
            sp2B = 0x78;
            sp2A = 0x64;
            sp29 = 0;
            sp28 = 0x96;
            break;

        case 3:
            sp2D = 0x64;
            sp2C = 0x96;
            sp2B = 0x96;
            sp2A = 0x64;
            sp29 = 0x96;
            sp28 = 0x96;
            break;
    }

    gDPSetPrimColor(arg0++, 0, 0xFF, sp2D, sp2C, sp2B, 255);
    gDPSetEnvColor(arg0++, sp2A, sp29, sp28, 255);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_DrawParticlePaletteBased.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (7 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_ParticlePaletteCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_DrawParticlePaletteBased(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Builds a display list of only the primitive and environment colors, picked from a table
 * keyed by the owner particle's CF parameter.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (4 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_ParticlePaletteDL(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    DisplayObject* sp24 = D_8006049C;
    s32 tmp = BattleAnim_GetOwnerContextParticle(D_8006049C);
    UNUSED u8 sp1F;
    UNUSED u8 sp1E;
    u8 sp1D;
    u8 sp1C;
    u8 sp1B;
    u8 sp1A;
    u8 sp19;
    u8 sp18;

    switch (Particle_FieldCF_GetS16_0C058(tmp)) {
        case 0:
            sp1D = 0xFF;
            sp1C = 0x96;
            sp1B = 0x32;
            sp1A = 0;
            sp19 = 0;
            sp18 = 0;
            break;

        case 1:
            sp1D = 0xFF;
            sp1C = 0xFF;
            sp1B = 0xFF;
            sp1A = 0x96;
            sp19 = 0xB4;
            sp18 = 0;
            break;

        case 2:
            sp1D = 0xFF;
            sp1C = 0xFF;
            sp1B = 0xFF;
            sp1A = 0x96;
            sp19 = 0;
            sp18 = 0xC8;
            break;

        case 3:
            sp1D = 0x64;
            sp1C = 0xFF;
            sp1B = 0xFF;
            sp1A = 0xC8;
            sp19 = 0xFF;
            sp18 = 0xFF;
            break;
    }

    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);
    gDPSetPrimColor(arg0++, 0, 0xFF, sp1D, sp1C, sp1B, sp24->alpha);
    gDPSetEnvColor(arg0++, sp1A, sp19, sp18, 255);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_ParticlePaletteDL.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (7 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_ParticlePaletteColorOnlyCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_ParticlePaletteDL(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Moves: Acid (use/hit), Lick (hit), Sludge (use/hit), Toxic (use/hit)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Acid, Lick, Sludge and Toxic.
 */
s16 BattleAnim_GetSlimeVariantIndex(void) {
    s16 sp1E;

    switch (BattleAnim_GetQueuedMoveId()) {
        case SLUDGE:
            sp1E = 0;
            break;

        case ACID:
            sp1E = 1;
            break;

        case TOXIC:
            sp1E = 2;
            break;

        case LICK:
            sp1E = 3;
            break;
    }

    return sp1E;
}

/**
 * Returns the tint palette index for the queued poison-style move (Sludge, Acid, Toxic or
 * Lick).
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (4 of the moves).
 * @unverified Name from Stadium 1.
 */
s16 BattleAnim_GetMoveKeyedTintRampParam(void) {
    s16 sp1E;

    switch (BattleAnim_GetQueuedMoveId()) {
        case SLUDGE:
            sp1E = 0x10;
            break;

        case ACID:
            sp1E = 0x29;
            break;

        case TOXIC:
            sp1E = 0x3B;
            break;

        case LICK:
            sp1E = 0x36;
            break;
    }

    return sp1E;
}

/**
 * Returns the trail palette index for the queued poison-style move (Sludge, Acid, Toxic or
 * Lick).
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (4 of the moves).
 * @unverified Name from Stadium 1.
 */
s16 BattleAnim_GetMoveKeyedTrailVariantParam(void) {
    s16 sp1E;

    switch (BattleAnim_GetQueuedMoveId()) {
        case SLUDGE:
            sp1E = 8;
            break;

        case ACID:
            sp1E = 0x33;
            break;

        case TOXIC:
            sp1E = 0x33;
            break;

        case LICK:
            sp1E = 0x33;
            break;
    }

    return sp1E;
}

/**
 * Handles the slime using in Toxic, Sludge, and Acid
 * Effect start init 17 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Acid, Sludge, Toxic.
 */
void BattleAnim_InitializeSlimeMove(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_SludgeModelAnimFinish, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, BattleAnim_GetSlimeVariantIndex(), 0);
}

/**
 * Effect end init 7 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Acid, Lick, Sludge, Toxic.
 */
void ParticleEffect_PaletteMultiBurst(void) {
    s16 sp4E;
    s16 sp44;
    s16 sp4A;

    sp4E = BattleAnim_GetSlimeVariantIndex();
    sp44 = BattleAnim_GetMoveKeyedTintRampParam();
    sp4A = BattleAnim_GetMoveKeyedTrailVariantParam();

    BattleAnim_SpawnOwnerModelTintRampDetach(4, sp44, 0, 0xFF, 0x10);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunSlimePuddle, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, sp4E, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_RunSlimePuddle, &gDefaultParticleDescriptor, 0, 1, 0xA, 1, sp4E, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_RunSlimePuddle, &gDefaultParticleDescriptor, 0, 1, 0xA, 2, sp4E, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(12, BattleAnim_RunSlimePuddle, &gDefaultParticleDescriptor, 0, 1, 0xA, 3, sp4E, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x28, sp44, 0xFF, 0, 0x10);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(6, 4, 0xA, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 9, 0, sp4A, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(7, 8, 5, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 9, 0, sp4A, 0);
}

/**
 * Returns the particle scale for the owner's species: 0.3 for Onix, 0.25 for Gyarados, 0.4
 * for Lapras, 0.5 for any other.
 */
f32 func_8215AEA4(Particle* arg0) {
    f32 sp1C = 0.5f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case ONIX:
            sp1C = 0.3f;
            break;

        case GYARADOS:
            sp1C = 0.25f;
            break;

        case LAPRAS:
            sp1C = 0.4f;
            break;
    }
    return sp1C;
}

/**
 * Builds a display list with two slowly scrolling tiles and no color setup.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_ParticleTextureTileCallback(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    BattleAnim_GetOwnerContextParticle(D_8006049C);
    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0, arg1, 0x20, 5, 0, 0, 1, 1, 0, -3, 1, 1);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_ParticleTextureTileCallback.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_ParticleTextureTileAllocCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_ParticleTextureTileCallback(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Builds a display list that sets a red primitive color with the owner particle's alpha.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_ParticleRedPrimCallback(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, 255, 0, 0, temp_v0->prim_a);
    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_ParticleRedPrimCallback.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_ParticleRedPrimAllocCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_ParticleRedPrimCallback(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Effect start init 83 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Glare, Leer.
 */
void BattleAnim_InitializeGlareLeerUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunScaryEyes, &gDefaultParticleDescriptor, 0x64, 1, 0xB, 0, 3, 6);
}

/**
 * initializes using hyper beam
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Hyper Beam.
 */
void BattleAnim_InitializeHyperBeamUseSequence(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x26, 0);
}

/**
 * Effect start init 37 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Earthquake, Fissure.
 */
void BattleAnim_InitializeEarthquakeFissureUse(void) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp34;

    switch (BattleAnim_GetQueuedMoveId()) {
        case EARTHQUAKE:
            sp34 = 0xE;
            break;

        case FISSURE:
            sp34 = 0;
            break;
    }

    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, sp34);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x26, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Earthquake.
 */
void BattleAnim_InitializeEarthquakeFissureHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(6, BattleAnim_InitializeParticleModel, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 4, 2);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 5, 0);
    BattleAnim_InitializeEarthquakeFissureHitSequence();
}

/**
 * Effect end init 75 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Earthquake.
 */
void BattleAnim_InitializeEarthquakeHit(void) {
    BattleAnim_InitializeEarthquakeFissureHit();
}

/**
 * Effect start init 87 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Defense Curl.
 */
void BattleAnim_InitializeDefenseCurlUse(void) {
    func_8213BC00(4, 8, 0, 0xFF, 0x40);
    func_8213C1BC(8);
    func_8213B560(0xC, &func_82152FB0, &D_8218E580, 0, 1, 0xE, 0, 6, 0);
    func_82168504();
}

/**
 * Effect start init 88 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Sharpen.
 */
void BattleAnim_InitializeSharpenUse(void) {
    func_8213BC00(6, 8, 0, 0xFF, 0x40);
    func_8213C1BC(0xA);
    func_8213B560(0xC, &func_82152FB0, &D_8218E580, 0, 1, 0xA, 0, 7, 0);
    func_82168504();
}

/**
 * Builds a display list that loads frame arg1 of the owner side's 76x19 Pokémon
 * thumbnail strip as a texture.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_PokemonPortraitCallback(Gfx* arg0, u8 arg1, UNUSED u16 arg2) {
    u8* var_a3;
    s32 idx = arg1 * 0xB48;

    if (BattleScene_GetParticipantSideIndex(BattleAnim_GetOwnerContextParticle(D_8006049C)->pokemon) == 0) {
        var_a3 = sSide1PokemonThumbnailImage + idx;
    } else {
        var_a3 = sSide2PokemonThumbnailImage + idx;
    }

    gDPLoadTextureTile(arg0++, var_a3, G_IM_FMT_RGBA, G_IM_SIZ_16b, 76, 0, 0, 0, 75, 18, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_PokemonPortraitCallback.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (2 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_PokemonPortraitAllocCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_PokemonPortraitCallback(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Moves: Double-Edge (use), Hi Jump Kick (use), Quick Attack (use), Skull Bash (use), Take Down (use)
 * TODO: Human contributor add screenshot
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Take Down, Double Edge, Quick Attack, Hi Jump Kick.
 */
void BattleAnim_InitializeSpeedLines(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 6, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 8, 0);
}

/**
 * Sets the spawn timing (0, 32, 14) and starts the Quick Attack / Hi Jump Kick use effect.
 */
void func_8215B5B8(void) {
    func_8213B644(0, 0x20, 0xE);
    BattleAnim_InitializeQuickAttackHiJumpKickUse();
}

/**
 * Effect start init 91 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Withdraw.
 */
void BattleAnim_InitializeWithdrawUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_InitializeParticleModel, &gDefaultParticleDescriptor, 0, 1, 0xE, 0, 9, 0);
}

/**
 * Effect init that spawns the Lick animation. Player sweep (all 165 moves used in battle): only
 * Lick reached this function.
 * Effect start init 92 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Lick.
 */
void BattleAnim_InitializeLickUse(void) {
    if (func_8213C4D0(0x5E) == 0) {
        func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 0x10, (s32) D_8219A80A, 0xA, 0);
    }
}

/**
 * Adjusts the particle for large species and returns its scale: Onix is moved 15 to the
 * side, Onix, Gyarados and Lapras are raised by 10, and the scale is 0.5 (Onix), 0.4
 * (Gyarados, Lapras) or 1.
 */
f32 func_8215B6A4(Particle* arg0) {
    f32 a = 0.0f;
    f32 b = 1.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case ONIX:
            Particle_AddPositionOffsetAlongRotationYMinus90(arg0, 15.0f);
            a = 10.0f;
            b = 0.5f;
            break;
        case GYARADOS:
            a = 10.0f;
            b = 0.4f;
            break;
        case LAPRAS:
            a = 10.0f;
            b = 0.4f;
            break;
    }
    Particle_PositionOffset_AddYScaled_08E90(arg0, a);
    return b;
}

/**
 * Effect start init 94 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Lovely Kiss.
 */
void BattleAnim_InitializeLovelyKissUse(void) {
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 0xB, 0, 0xB, 0);
    func_8213B644(0x2A, 0x10, 0x15);
}

/**
 * Effect end init 61 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Lovely Kiss.
 */
void BattleAnim_InitializeLovelyKissHit(void) {
    func_8213BC7C(0, 1, 0x16, 0xFF, 0, 8);
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 9, 0, 0xC, 0);
}

/**
 * Init step: creates a model object for the particle (+0x14) and picks model 0x8C, 0x8E or
 * 0x8D from field CD (0-1, 2-3, other), with scale 1 and alpha 0. Detaches if no model
 * could be created.
 */
void func_8215B83C(s8 *arg0) {
    s16 sp26;
    s32 temp_v0;

    sp26 = Particle_GetUnkCD();
    temp_v0 = func_82136AC0(arg0);
    M2C_FIELD(arg0, s32 *, 0x14) = temp_v0;
    if (temp_v0 != 0) {
        if ((sp26 == 0) || (sp26 == 1)) {
            func_82136D58(M2C_FIELD(arg0, s32 *, 0x14), 0x8C);
        } else if ((sp26 == 2) || (sp26 == 3)) {
            func_82136D58(M2C_FIELD(arg0, s32 *, 0x14), 0x8E);
        } else {
            func_82136D58(M2C_FIELD(arg0, s32 *, 0x14), 0x8D);
        }
        func_821401D4(arg0, 0x3F800000);
        Particle_SetPrimAlpha(arg0, 0);
        func_8213C9D0(arg0);
        return;
    }
    Particle_DisableAndDetach(arg0);
}

/**
 * Used to make the overlays for mediate, night shade, and dream eater
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Meditate, Night Shade, Dream Eater.
 */
void BattleAnim_RunPsychedelicOverlay(Particle* arg0) {
    u32 temp_v0 = Particle_FieldCD_GetU8_0C048(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_CallbackStartEffects95To97EndEffects62And63ModelFadeIn_InitParticle(arg0);
            break;

        case 2:
            if ((temp_v0 == 0) || ((s32)temp_v0 == 1)) {
                Particle_ApproachPrimAlphaThenAdvance(arg0, 0x80, 8);
            } else if (temp_v0 == 3) {
                Particle_ApproachPrimAlphaThenAdvance(arg0, 0xFF, 0xFF);
            } else {
                Particle_ApproachPrimAlphaThenAdvance(arg0, 0xFF, 4);
            }
            break;
    }
}

/**
 * Builds a display list for a palette-driven particle: the owner particle's CD parameter
 * selects texture size, colors and two tile scroll offsets.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (12 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_PaletteParticleDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    u8* a1;
    Particle* spC8;
    u8 var_t0;
    s16 spC4;
    s16 spC2;
    s16 spC0;
    s16 spBE;
    s16 var_a1;
    s16 var_a2;
    s16 var_a3;
    s16 var_s1;
    UNUSED s16 pad2; // FAKE: stack padding
    s16 spB2;
    s16 spB0;
    s16 spAE;
    s16 spAC;
    u16 temp_v0_2;
    s16 var_t2;
    s16 var_t1;

    spC8 = BattleAnim_GetOwnerContextParticle(D_8006049C);
    temp_v0_2 = Particle_FieldCD_GetU8_0C048(spC8);
    var_s1 = 0x20;
    var_t1 = 5;
    var_t2 = 5;
    var_a3 = 0;
    var_a1 = 0;
    var_a2 = 0;
    var_t0 = spC8->prim_a;

    switch (temp_v0_2) {
        case 0:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xF;
            spB0 = 0;
            spAE = 0xE;
            spAC = 0xF;
            break;

        case 1:
            spC4 = -1;
            spC2 = 1;
            spC0 = 1;
            spBE = 1;
            spB2 = 0xF;
            spB0 = 0;
            spAE = 0xE;
            spAC = 0xF;
            break;

        case 2:
            spC4 = -2;
            spC2 = 2;
            spC0 = 2;
            var_a3 = 0xFF;
            spBE = 3;
            spB2 = 0xC;
            spB0 = 1;
            spAE = 0xC;
            spAC = 0;
            break;

        case 3:
            spC4 = -2;
            spC2 = -2;
            spC0 = 2;
            var_a3 = 0xFF;
            spBE = -3;
            spB2 = 0xC;
            spB0 = 1;
            spAE = 0xC;
            spAC = 0;
            break;

        case 4:
            var_a2 = 0xFF;
            var_a1 = 0x9B;
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xC;
            spB0 = 1;
            spAE = 0xC;
            spAC = 0;

            break;

        case 5:
            spC0 = -0xA;
            spBE = -0xF;
            spC4 = 0;
            spC2 = 0;
            spB2 = 0xF;
            spB0 = 1;
            spAE = 0xF;
            spAC = 1;
            var_a2 = 0xFF;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            var_t0 = 0x32;
            break;

        case 6:
            spC4 = 2;
            spC2 = -1;
            spC0 = -2;
            spBE = -2;
            spB2 = 0xD;
            spB0 = 0xE;
            spAE = 0xC;
            spAC = 0xE;
            var_a2 = 0xFF;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            var_s1 = 0x40;
            var_t1 = 6;
            var_t2 = 6;
            break;

        case 7:
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0xF;
            spAE = 0xF;
            spAC = 0xE;
            var_a2 = 0xFF;
            var_a3 = 0x80;
            break;

        case 8:
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0xF;
            spAE = 0xF;
            spAC = 0xE;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            break;

        case 9:
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0xF;
            spAE = 0xF;
            spAC = 0xE;
            var_a2 = 0x64;
            var_a1 = 0xFF;
            break;

        case 10:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a2 = 0xC8;
            var_a1 = 0x64;
            break;

        case 11:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            break;

        case 12:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a2 = 0xC8;
            var_a1 = 0xFF;
            break;

        case 13:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a2 = 0xFF;
            break;
    }

    a1 = arg1;

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, var_a2, var_a1, var_a3, var_t0);

    gDPLoadTextureTile_4b(arg0++, arg1, G_IM_FMT_I, var_s1, var_s1, 0, 0, var_s1 - 1, var_s1 - 1, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, var_t2, var_t1, spB2, spB0);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, spC4, spC2, var_s1, var_s1);

    gDPLoadMultiTile_4b(arg0++, a1, 0x0100, 1, G_IM_FMT_I, var_s1, var_s1, 0, 0, var_s1 - 1, var_s1 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, var_t2, var_t1, spAE, spAC);

    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, spC0, spBE, var_s1, var_s1);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_PaletteParticleDL.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (17 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_PaletteParticleDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_PaletteParticleDL(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Effect start init 95 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Dream Eater.
 */
void BattleAnim_InitializeDreamEaterUse(void) {
    func_8213B560(0, &func_8215B904, &D_8218E580, 0, 1, 0xC, 0, 0, 0);
    func_8213B560(0, &func_82153040, &D_8218E580, 0, 1, 9, 0, 0xD, 0);
    func_8213B560(4, &func_82153040, &D_8218E580, 0, 1, 9, 1, 0xD, 0);
    func_8213B560(8, &func_82153040, &D_8218E580, 0, 1, 9, 2, 0xD, 0);
    func_8213B560(0xC, &func_82153040, &D_8218E580, 0, 1, 9, 0, 0xD, 0);
    func_8213B560(0x10, &func_82153040, &D_8218E580, 0, 1, 9, 1, 0xD, 0);
    func_8213B560(0x14, &func_82153040, &D_8218E580, 0, 1, 9, 2, 0xD, 0);
    func_8213B560(0x18, &func_82153040, &D_8218E580, 0, 1, 9, 0, 0xD, 0);
    func_8213B560(0x1C, &func_82153040, &D_8218E580, 0, 1, 9, 1, 0xD, 0);
    func_8213B560(0x20, &func_82153040, &D_8218E580, 0, 1, 9, 2, 0xD, 0);
    func_8213B644(0, 8, 0x33);
}

/**
 * Seen in play (2026-11-12): Dream Eater on a sleeping COM Pinsir ran this as end effect 0x3E.
 */
void BattleAnim_InitializeDreamEaterHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPsychedelicOverlay, &gDefaultParticleDescriptor, 0, 1, 0xC, 1, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(4, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 1, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(8, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 2, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(12, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 1, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(20, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 2, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(24, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(28, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 1, 0xD, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x20, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 2, 0xD, 0);
}

/**
 * Moves: Absorb (use), Leech Life (use), Mega Drain (use)
 * TODO: Human contributor add screenshot
 * Effect start init 24 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Absorb, Leech Life, Mega Drain.
 */
void BattleAnim_CreateDrainingMoveOverlay(void) {
    switch (BattleAnim_GetQueuedMoveId()) {
        case LEECH_LIFE:
            BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 6);
            BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xD, 0x1A, 0x20);
            break;

        case ABSORB:
            BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 0x37);
            BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xB, 0x1A, 0x20);
            break;

        case MEGA_DRAIN:
            BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 0x1F);
            BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xC, 0x1A, 0x20);
            break;
    }
}

/**
 * Effect start init 96 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Meditate.
 */
void BattleAnim_InitializeMeditateUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPsychedelicOverlay, &gDefaultParticleDescriptor, 0, 1, 0xC, 4, 0, 0);
}

/**
 * Effect start init 97 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Night Shade.
 */
void BattleAnim_InitializeNightShadeUse(void) {
    func_8213B560(0, &func_8215B904, &D_8218E580, 0, 1, 0xC, 2, 0, 0);
    func_8213B644(0, 8, 0);
    func_8213B464(0x40);
    func_8213B720(0, 2, 0x10, 8);
}

/**
 * Moves: Night Shade (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 63 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Night Shade.
 */
void BattleAnim_InitializeNightShadeHit(void) {
    func_8213B720(0, 2, 0x10, 8);
    func_8213BC00(4, 8, 0xFF, 0, 8);
    func_8213B560(0, &func_8215B904, &D_8218E580, 0, 1, 0xC, 3, 0, 0);
    func_8213B5D8(4, 4, 4, &func_82162C68, &D_8218E728, 0, 3, 9, 0, 0x18, 0xD);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Confuse Ray.
 */
void BattleAnim_SetupConfuseRayUseSpotlight(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x42, 0xC2);
        Particle_SetScaleScaled(arg0, 1.0f);
        ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x23);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_ScratchA_SetS16_0BF4C(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Particle callback: init, then fades in to full alpha while field AE moves toward 200.
 * Always turns the particle to face away from the camera (camera yaw + 0x8000).
 */
void func_8215C984(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215C8FC(arg0);
        break;
    case 2:
        Particle_ApproachPrimAlpha(arg0, 0xFF, 8);
        Particle_ApproachScratchA(arg0, 0xC8, 6);
        break;
    }
    Particle_SetRotationY(arg0, (s16) (func_821385C0() + 0x8000));
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Confuse Ray.
 */
void BattleAnim_SetupConfuseRayHitSpotlight(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModelWithAnim(arg0->displayObject, 0x42, 0xC2);
        BattleAnim_SetModelAnimFrame(arg0->displayObject, 0x28);
        Particle_SetScaleScaled(arg0, 1.0f);
        ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x23);
        Particle_ScratchA_SetS16_0BF4C(arg0, 0xFF);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Particle callback of the Confuse Ray animation. Player sweep (all 165 moves used in battle):
 * only Confuse Ray reached this function.
 */
void BattleAnim_ConfuseRayParticleUpdate(Particle* arg0) {
    if (M2C_FIELD(arg0, s16 *, 0xAE) == 1) {
        func_8215CA14();
    }
    Particle_SetRotationY(arg0, (s16) (func_821385C0() + 0x8000));
}

/**
 * Builds a display list from the owner particle's colors. Pass arg1 0 uses prim_a as the
 * alpha and pass 1 uses unk_AE.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_WaterAnimPrimEnvDL(Gfx* arg0, u8 arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    switch (arg1) {
        case 0:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
            break;

        case 1:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->scratchA);
            break;
    }

    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 0);
    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_WaterAnimPrimEnvDL.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_WaterAnimPrimEnvDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_WaterAnimPrimEnvDL(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Starts a global tint fade, then the effect 21/93 model particle for the current
 * animation owner.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_WaterAnimBurst(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 8, 3);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects21And93ModelAlphaAnchorFollow, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0, 0);
}

/**
 * Sets the spawn timing (16, 16, 8).
 */
void func_8215CCF0(void) {
    func_8213B644(0x10, 0x10, 8);
}

/**
 * Effect start init 93 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Confuse Ray.
 */
void BattleAnim_InitializeConfuseRayUse(void) {
    func_8213B560(0, &func_8215C984, &D_8218E580, 0, 1, 0xA, 0, 0, 0);
    func_8213B644(0, 0x20, 3);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B878(0xC, 5, 0x10, 8);
    func_8213B560(0xC, &func_82162C68, &D_8218E728, 0, 4, 9, 0, 0x18, 0xD);
    func_8213B464(0x21);
    func_8213B720(0, 0, 0x10, 8);
    func_8213BC00(0, 8, 0xFF, 0, 0x10);
}

/**
 * Moves: Confuse Ray (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 60 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Confuse Ray.
 */
void BattleAnim_InitializeConfuseRayHit(void) {
    func_8213B560(0, &BattleAnim_ConfuseRayParticleUpdate, &D_8218E580, 0, 1, 0xA, 0, 0, 0);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B644(0, 0x20, 3);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B560(0xC, &func_82162C68, &D_8218E728, 0, 4, 9, 0, 0x18, 0xD);
    func_8213B464(0x21);
    func_8213BC00(0, 8, 0xFF, 0, 0x10);
}

/**
 * Builds a display list for two layers of a scrolling 32x32 4-bit intensity texture with
 * the owner particle's alpha.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_WaterAnimDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    Particle* temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);

    gDPLoadTextureTile_4b(arg0++, arg1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 14, 15);

    ParticleGfx_SetPartiallyAnimatedTileSize(arg0++, -0xB, -8, 0x20, 0x20);

    gDPLoadMultiTile_4b(arg0++, arg1, 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 13, 15);

    ParticleGfx_SetPartiallyAnimatedAuxTileSize(arg0++, 0x35, -4, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_WaterAnimDL.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_WaterAnimDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_WaterAnimDL(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Effect init for the start of the Waterfall animation.
 * Effect start init 99 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Waterfall.
 */
void BattleAnim_InitializeWaterfallUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &D_8218E580, 0xFF, 1, 0xC, 0, 0xE, 8);
    BattleAnim_AddSpawnDelay(4);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x10, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E7D0, 0, 2, 0xE, 0, 0x33, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x10, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E650, 0, 2, 0xE, 0, 0xC, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x10, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E5F8, 0, 2, 0xE, 0, 0xC, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 5, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E5D8, 0, 2, 0xE, 0, 0xC, 4);
}

/**
 * Effect init for the end (impact) of the Waterfall animation.
 * Effect end init 64 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Waterfall.
 */
void BattleAnim_InitializeWaterfallHit(void) {
    func_8213B560(0, &func_821530F4, &D_8218E580, 0xFF, 1, 0xC, 0, 0xF, 0x40);
    BattleAnim_InitializeWaterfallUseB();
    func_8213B464(0x10);
    func_8213B5D8(0, 4, 5, &func_82164AD0, &D_8218E5D8, 0, 1, 0xE, 0, 0xC, 4);
}

/**
 * Effect init for the start of the Surf animation.
 * Effect start init 36 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Surf.
 */
void BattleAnim_InitializeSurfUseSpray(void) {
    BattleAnim_AddSpawnDelay(65);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x20, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E7D0, 0, 2, 7, 0, 0x33, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x20, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E650, 0, 2, 7, 0, 0xC, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 0x20, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E5F8, 0, 2, 7, 0, 0xC, 8);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 8, 0xA, BattleAnim_CallbackSharedAnimatedVerticalFade, &D_8218E5D8, 0, 2, 7, 0, 0xC, 4);
}

/**
 * Moves: Surf (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 16 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Surf.
 */
void BattleAnim_InitializeSurfHit(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 4, BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade, &D_8218E7D0, 0, 3, 0xE, 0, 0x33, 0xC);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 4, BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade, &D_8218E650, 0, 3, 0xE, 0, 0xC, 0xC);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 4, BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade, &D_8218E5F8, 0, 3, 0xE, 0, 0xC, 0xC);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 4, BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade, &D_8218E5D8, 0, 3, 0xE, 0, 0xC, 4);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 2, 0xC, BattleAnim_CallbackEndEffect16Descriptor45DelayedRotatingMotion, &D_8218E7A8, 0, 4, 0x11, 7, 0x33, 0);
}

/**
 * Effect start init 100 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Crabhammer.
 */
void BattleAnim_InitializeCrabhammerUse(void) {
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 0x13, (s32) D_8219A80A, 0x10, 0);
    func_8213B720(0x22, 0, 0x10, 8);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Barrage.
 */
void BattleAnim_SetupBarrageEffect(Particle* arg0) {
    Particle_SetScaleScaled(arg0, 0.2f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, 0x33);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback: init, then loops frames 0-7 while fading alpha toward 32, then detaches.
 * Scale moves toward 0.5 by 0.1 every frame.
 */
void func_8215D76C(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215D724(arg0);
        break;
    case 2:
        Particle_AnimateFramesForwardLoopedThenAdvance(arg0, 0, 7, 1, 2, 0);
        Particle_ApproachPrimAlpha(arg0, 0x20, 0x40);
        break;
    case 3:
        Particle_DisableAndDetach(arg0);
        break;
    }
    func_82140228(arg0, 0x3F000000, 0x3DCCCCCD);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Barrage.
 */
void BattleAnim_SetupBarrageUseEffect1(Particle* arg0) {
    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.3f);
    Particle_Rotation_AddVec_0A52C(arg0, -0x1000, 0, 0);
    Particle_RotationTarget_SetY_0A414(arg0, BattleAnim_GetParticleAngleYToTertiaryOwner(arg0));
    Particle_RotationStep_SetY_0A3D8(arg0, 0x80);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback for effect 101 (Barrage use): sets up the throw, loads model 0xA0
 * (anim 0xA1), then after 10 frames launches the projectile and a 12-particle burst.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name guessed from the code.
 */
void BattleAnim_CallbackStartEffect101ModelBurstEmitter(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupBarrageUseEffect1(arg0);
            break;

        case 2:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
                BattleAnim_InitModelWithAnim(arg0->displayObject, 0xA0, 0xA1);
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, 10) != 0) {
                Particle_StepMagnitude_SetScaled_0AD8C(arg0, 8.0f);
                BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackStartEffect101EndEffect65Descriptor4ABurstChild, &D_8218E7D0, 1);
                BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_RunBarrageUseEffect2, &D_8218E770, 0xC, 0x33, 0);
            }
            break;

        case 4:
            BattleAnim_EmitParticleBurst(arg0, BattleAnim_CallbackStartEffect101EndEffect65Descriptor4ABurstChild, &D_8218E7D0, 1);
            Particle_ApproachRotationXTo(arg0, 0x1000, 0x200);
            Particle_ApproachRotationTargetY(arg0);
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0xF);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

/**
 * Effect start init 101 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Barrage.
 */
void BattleAnim_InitializeBarrageUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect101ModelBurstEmitter, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Barrage.
 */
void BattleAnim_SetupBarrageHitEffect(Particle* arg0) {
    Particle_SpawnIndex_GetS16_0C038(arg0);
    Particle_SetScaleScaled(arg0, 0.4f);
    Particle_PositionOffset_SetYScaled_08CA0(arg0, 15.0f);
    Particle_AddPositionOffsetAlongRotationY(arg0, 50.0f);
    Particle_Rotation_AddVec_0A52C(arg0, 0x800, -0x8000, 0);
    Particle_StepMagnitude_SetScaled_0AD8C(arg0, 8.0f);
    Particle_AdvanceLifecycle(arg0);
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    BattleAnim_InitModel(arg0->displayObject, 0xA0);
}

/**
 * Particle callback: init, then emits one func_8215D76C child per frame while spinning and
 * counting down 7 frames, then detaches. Moves along its rotation while the countdown runs.
 */
void func_8215DAEC(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215DA5C(arg0);
        break;
    case 2:
        func_82139E5C(arg0, &func_8215D76C, &D_8218E7D0, 1);
        func_8213EF88(arg0, 0x1000, 0x80);
        func_8213CA80(arg0, 7);
        break;
    case 3:
        Particle_DisableAndDetach(arg0);
        break;
    }
    if (func_8213CB7C(arg0) != 0) {
        Particle_AddVelocityFromRotationTemplate1(arg0);
    }
}

/**
 * Effect end init 65 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Barrage.
 */
void BattleAnim_InitializeBarrageHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackMove140EndEffect65EmitDescriptor4A, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(5, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(7, BattleAnim_RunPhysicalHitPurpleSmoke, &gBattleAnimParticleDescriptors[0x3D], 0, 8, 0x11, 9, 0, 0);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psywave.
 */
void BattleAnim_SetupPsywaveEffect(Particle* arg0) {
    arg0->displayObject = BattleAnim_AllocOwnerDisplayContext(arg0);
    if (arg0->displayObject != NULL) {
        BattleAnim_InitModel(arg0->displayObject, 0xA2);
        Particle_SetScaleScaled(arg0, 1.0f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_AdvanceLifecycle(arg0);
    } else {
        Particle_DisableAndDetach(arg0);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Psywave.
 */
void BattleAnim_RunPsywaveEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SetupPsywaveEffect(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0x80, 8);
            break;
    }
}

/**
 * Builds a display list with a cyan primitive color and two tiles whose scroll direction
 * is chosen by the owner particle's CF parameter.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_SimpleNodeDL(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    UNUSED s32 pad; // FAKE: stack padding
    Particle* sp48 = BattleAnim_GetOwnerContextParticle(D_8006049C);
    UNUSED s16 pad2; // FAKE: stack padding
    s16 sp44;
    s16 sp42;

    switch (Particle_FieldCF_GetS16_0C058(sp48)) {
        case 0:
            sp44 = -5;
            sp42 = 3;
            break;

        case 1:
            sp44 = 5;
            sp42 = -3;
            break;
    }

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 55, 255, 255, sp48->prim_a);

    arg0 = BattleAnim_BuildAnimatedTileDisplayListFromStruct(arg0++, arg1, 0x20, 5, 1, sp44, 0xD, 0xC, -1, sp42, 0xB, 0xD);
    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with Gfx_SimpleNodeDL.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (9 of the moves).
 * @unverified Name from Stadium 1.
 */
void Gfx_SimpleNodeDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        Gfx_SimpleNodeDL(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Effect start init 49 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Psywave.
 */
void BattleAnim_InitializePsywaveUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunPsywaveEffect, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0, 0);
}

/**
 * Effect end init 66 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Psywave.
 */
void BattleAnim_InitializePsywaveHit(void) {
    func_8213BC7C(0, 2, 8, 0xFF, 0, 0x10);
    func_8213B560(0, &func_8215DCE8, &D_8218E580, 0, 1, 9, 0, 1, 0);
    func_8213B5D8(4, 4, 4, &func_82162C68, &D_8218E728, 0, 3, 9, 0, 0x18, 0xD);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Confusion, Psychic M.
 */
void BattleAnim_RunConfusionPsychicHitEffect(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 2);
            break;

        case 2:
            Particle_ApproachPrimAlphaThenAdvance(arg0, arg0->param0, Particle_FieldCE_GetS32_0C040(arg0));
            break;

        case 3:
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0x20);
            break;

        case 4:
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0xA);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

/**
 * Effect start init 106 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Psychic.
 */
void BattleAnim_InitializePsychicUse(void) {
    func_8213B644(0, 5, 0);
    func_8213B560(0, &func_821530F4, &D_8218E580, 0xFF, 1, 0xC, 8, 0x18, 5);
    func_8213BC7C(0x32, 1, 8, 0, 0xFF, 0x20);
    func_8213B6AC(0x32, 1, 0x20, 8, 0xFF);
}

/**
 * Effect start init 107 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Confusion.
 */
void BattleAnim_InitializeConfusionUse(void) {
    func_8213B644(0, 6, 0);
    func_8213B560(0, &func_821530F4, &D_8218E580, 0xFF, 1, 0xC, 7, 0x17, 6);
    func_8213B6AC(0x32, 1, 0x20, 8, 0xFF);
    func_8213BC7C(0x32, 1, 8, 0, 0xFF, 0x20);
}

/**
 * Effect init for the end (impact) of the Psychic animation.
 * Effect end init 74 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Psychic.
 */
void BattleAnim_InitializePsychicHit(void) {
    func_8213B644(0, 0x40, 0);
    func_8213B560(0, &func_8215DFB4, &D_8218E580, 0xFF, 1, 0xC, 8, 0x18, 0x20);
    func_8213B5D8(4, 4, 4, &func_82162C68, &D_8218E728, 0, 3, 9, 0, 0x18, 0xD);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B464(0x21);
    func_8213BC00(0, 8, 0xFF, 0, 4);
    func_8213B644(8, 4, 8);
}

/**
 * Effect init for the end (impact) of the Confusion animation.
 * Effect end init 73 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Confusion.
 */
void BattleAnim_InitializeConfusionHit(void) {
    func_8213B644(0, 0x40, 0);
    func_8213B560(0, &func_8215DFB4, &D_8218E580, 0xFF, 1, 0xC, 7, 0x17, 0x20);
    func_8213B5D8(4, 4, 4, &func_82162C68, &D_8218E728, 0, 3, 9, 0, 0x18, 0xD);
    func_8213BC00(8, 8, 0, 0xFF, 0x40);
    func_8213B720(0, 0, 0x10, 8);
    func_8213B464(0x21);
    func_8213BC00(0, 8, 0xFF, 0, 4);
    func_8213B644(8, 4, 8);
}

/**
 * Effect start init 3 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Focus Energy.
 */
void BattleAnim_InitializeFocusEnergyUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x10, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xA, 0x1A, 4);
    BattleAnim_SpawnOwnerModelTintPulseDetach(0, 1, 0xA, 0, 0xC8, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(60, 4, 0xE, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 0x11, 7, 0x33, 7);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(61, 8, 7, BattleAnim_CallbackSharedAnimatedVerticalFade, &gBattleAnimParticleDescriptors[0x3D], 0, 1, 0x11, 7, 0x33, 7);
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Rage.
 */
void BattleAnim_InitializeBideRageUseSequence(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 6);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunFillScreenOverlay, &gDefaultParticleDescriptor, 0x80, 1, 0xC, 0xA, 0x1A, 0x20);
}

/**
 * Effect start init 104 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Sky Attack.
 */
void BattleAnim_InitializeSkyAttackUse1(void) {
    func_82168844(0xE);
    func_8213B644(0, 2, 0xE);
    func_8213BC00(0, 0xA, 0, 0xC8, 4);
    func_8213BD78(0x32, 0xA, 0x17, 2, 0xC8);
    func_8213B560(0x40, &BattleAnim_RunOscillatingFlameUnderneathPokemon, &D_8218E7F8, 0, 0x20, 7, 0, 0, 0);
}

/**
 * Seen in play (2026-11-12): Sky Attack's second turn ran this as start effect 0x67. The charge
 * turn uses 0x68.
 */
void BattleAnim_InitializeSkyAttackUse2(void) {
    func_8213B644(0, 0x20, 6);
    func_8213BC00(0, 0x12, 0, 0x80, 0x10);
    func_8213C0D8(0, 0xFF, 0, 0x10);
    func_8213B560(0, &func_82152FE0, &D_8218E580, 0xFF, 1, 9, (s32) D_8219A80A, 0x12, 0x20);
    func_8213B5D8(0, 1, 0xC, &func_82164AD0, &D_8218E770, 0, 1, 9, 0, 0x16, 5);
}

/**
 * Seen in play (2026-11-12): Sky Attack's second turn ran this as end effect 0x19.
 */
void BattleAnim_InitializeSkyAttackHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 9, 0, 0x13, 0);
    BattleAnim_SetSpawnDelay(4);
    BattleAnim_EndEffect71PaletteApproachWithExpandingScaleFades();
}

/**
 * Builds a display list whose colors, texture size and tile scroll are chosen by the
 * owner particle's parameters.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_DrawQuad(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    Particle* temp_v0;
    UNUSED s32 pad; // FAKE: stack padding
    s16 var_t2;
    s16 tmp;
    s16 sp82;
    s16 sp80;
    s16 sp7E;
    s16 sp7C;
    s16 sp7A;
    s16 sp78;
    s16 sp76;
    s16 sp74;
    s16 var_s1;
    s16 var_t1;
    UNUSED s16 pad2; // FAKE: stack padding
    s16 var_t5;

    temp_v0 = BattleAnim_GetOwnerContextParticle(D_8006049C);
    var_t1 = 0x96;
    var_t2 = 0xFF;
    var_s1 = 0x20;
    var_t5 = 5;
    tmp = arg1->variant;

    switch (tmp) {
        case 1:
            sp82 = -5;
            sp80 = -0xF;
            sp7E = -0xA;
            sp7C = -0xA;
            sp7A = 0;
            sp78 = 1;
            sp76 = 0;
            sp74 = 1;
            break;

        case 2:
            sp82 = 5;
            sp80 = -0xF;
            sp7E = 0;
            sp7C = -0xA;
            sp7A = 0;
            sp78 = 0xF;
            sp76 = 0;
            sp74 = 0xF;
            break;

        case 3:
            sp82 = 5;
            sp80 = -0xF;
            sp7C = -0xA;
            sp7E = 0;
            sp7A = 1;
            sp78 = 1;
            sp76 = 1;
            sp74 = 1;
            break;

        case 4:
            sp82 = 5;
            sp80 = -0xF;
            sp7E = 0;
            sp7C = -0xA;
            sp7A = 0;
            sp78 = 0;
            sp76 = 0;
            sp74 = 0;
            break;

        case 5:
            sp82 = -5;
            sp80 = -0xA;
            sp7E = 0;
            sp7C = 0;
            sp7A = 1;
            sp78 = 0;
            sp76 = 0;
            sp74 = 0;
            var_t1 = 0x78;
            var_t2 = 0xC8;
            var_s1 = 0x40;
            var_t5 = 6;
            break;

        case 6:
            sp82 = 0;
            sp80 = -0xA;
            sp7E = 0;
            sp7C = 0;
            sp7A = 1;
            sp78 = 1;
            sp76 = 0;
            sp74 = 0;
            var_t1 = 0x78;
            var_t2 = 0xC8;
            var_s1 = 0x40;
            var_t5 = 6;
            break;
    }

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, var_t1, 255, var_t2, 0, temp_v0->prim_a);

    gDPLoadTextureTile_4b(arg0++, arg1->textureA, G_IM_FMT_I, 32, 32, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, 5, 5, sp7A, sp78);

    ParticleGfx_SetAnimatedTileSizeOnList(arg0++, sp82, sp80, 0x20, 0x20);

    gDPLoadMultiTile_4b(arg0++, arg1->textureB, 0x0100, 1, G_IM_FMT_I, var_s1, 0, 0, 0, var_s1 - 1, var_s1 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, var_t5, var_t5, sp76, sp74);

    ParticleGfx_SetAnimatedAuxTileSizeOnList(arg0++, sp7E, sp7C, var_s1, var_s1);

    gSPEndDisplayList(arg0++);
}

/**
 * Display-list callback: on draw pass 2, allocates 30 commands into arg1->unk_18 and
 * fills them with ParticleEffect_DrawQuad.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_AllocateDisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->displayList = Gfx_AllocDisplayList(sizeof(Gfx) * 30);
        ParticleEffect_DrawQuad(arg1->displayList, arg1->texture, D_80060484);
    }
}

/**
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Thunder.
 */
void BattleAnim_InitializeThunderHitSequence(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0xE, 5, 0x14, 0);
}

/**
 * Effect start init 105 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Solar Beam.
 */
void BattleAnim_InitializeSolarBeamUse2(void) {
    func_8213B560(0, &func_821530F4, &D_8218E580, 0xBE, 1, 9, 6, 0x15, 2);
    func_8213BC00(8, 8, 0, 0xFF, 4);
    BattleAnim_InitializeSolarBeamUseSequence();
}

/**
 * Seen in play (2026-11-13) in the 165-move sweep (each move used once by the 1P Pokémon): it ran
 * only for Mega Punch and Mega Kick.
 */
void BattleAnim_MegaHitModelFade(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            Particle_Param0_SetS16_0BCA8(arg0, 2);
            break;

        case 2:
            Particle_PrimG_Approach_0BB14(arg0, 0, 0x20);

            if (Particle_DecrementParam0ToZero != NULL) { //!bug: compares the function pointer instead of calling it, so this is always true
                Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 0x20);
            }

            if (ModelAnim_IsFinished(arg0->displayObject) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

/**
 * Using to make a horizontal cylindrical hit spark for Skull Bash, Mega Punch, and Mega Kick
 * Effect end init 76 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Mega Kick, Mega Punch.
 */
void BattleAnim_InitializeLargePhysicalHitSpark(void) {
    func_8213BC00(4, 8, 0xFF, 0, 0x20);
    func_8213B560(4, &func_8215ED1C, &D_8218E580, 0, 1, 9, 0, 0x19, 0);
}

/**
 * initializes using drill peck
 * Effect start init 113 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Drill Peck.
 */
void BattleAnim_InitializeDrillPeckUse(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x1B, 1);
}

/**
 * initializes being hit by drill peck
 * Effect end init 77 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Drill Peck.
 */
void BattleAnim_InitializeDrillPeckHit(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x1C, 1);
}

/**
 * initializes getting using horn drill
 * Effect start init 121 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Horn Drill.
 */
void BattleAnim_InitializeHornDrillUse(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0x20, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackInitModelAnimWait, &gDefaultParticleDescriptor, 0, 1, 0x11, gBattleAnimCurrentAnchor, 0x1B, 1);
}

/**
 * initializes getting hit by horn drill
 * Seen in play (2026-11-13) (Free Battle, 1P Onix's Horn Drill with its accuracy raised so it
 * lands): called through the effect table as the hit animation started. In the
 * earlier sweep Horn Drill missed and this did not run.
 */
void BattleAnim_InitializeHornDrillHit(void) {
    func_8213BC00(0, 0xA, 0, 0xFF, 0x40);
    func_8213B560(0, &func_82152F44, &D_8218E580, 0, 1, 0x11, (s32) D_8219A80A, 0x1C, 1);
    func_8213BC00(0x30, 0xA, 0xFF, 0, 2);
}

/**
 * Used to create the spear projectile for fury attack, peck, and horn attack
 * Seen in play (2026-11-12): in the per-move sweep (each of the 165 moves used once) it ran only
 * for Horn Attack, Fury Attack, Peck.
 */
void BattleAnim_RunWeakSpear(Particle* arg0) {
    s16 sp26 = Particle_FieldCE_GetS32_0C040(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_SelectParticleModelFrames(arg0, 0);
            if (sp26 == 1) {
                Particle_SetScaleScaled(arg0, 1.5f);
                Particle_AddPositionOffsetAlongRotationYPlus180(arg0, 40.0f);
            }
            break;

        case 2:
            ParticleGfx_ApproachPrimEnvPalettePair(arg0, 0x33, 0x40);
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0xFF, 0x40);
            break;

        case 3:
            ParticleGfx_ApproachPrimEnvPalettePair(arg0, 0, 0x40);
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0, 0x40);
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * Effect start init 118 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Fury Attack, Peck.
 */
void BattleAnim_InitializeFuryAttackPeckUse(void) {
    func_8213B5D8(0, 2, 3, &func_8215EFF8, &D_8218E580, 0, 1, 0x11, 7, 0x20, 0);
}

/**
 * initializes using horn attack
 * Effect start init 119 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Horn Attack.
 */
void BattleAnim_InitializeHornAttackUse(void) {
    func_8213B560(0, &func_8215EFF8, &D_8218E580, 0, 1, 0x11, 7, 0x20, 1);
}

/**
 * Particle callback: starts a model animation (func_82152730 0), then fades alpha in and
 * marks itself inactive once the model animation ends.
 */
void func_8215F1B0(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82152730(arg0, 0);
        return;
    case 2:
        func_821437E0(arg0, 0x33, 0x24);
        Particle_ApproachPrimAlpha(arg0, 0xFF, 0x1D);
        if (func_8001104C(M2C_FIELD(arg0, s32 *, 0x14)) != 0) {
            Particle_MarkInactive(arg0);
        }
        return;
    }
}

/**
 * Moves: Body Slam (hit), Fly (hit), Seismic Toss (hit), Stomp (hit)
 * TODO: Human contributor add screenshot
 * Effect end init 79 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used: it
 * ran for exactly Body Slam, Seismic Toss, Stomp.
 */
void BattleAnim_InitializeVerticalLandingHitSpark(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackEndEffect79DefaultDescriptorPaletteFade, &gDefaultParticleDescriptor, 0, 1, 0xA, 0, 0x1F, 0);
}

/**
 * Effect init that spawns the Sonicboom animation. Player sweep (all 165 moves used in battle):
 * only Sonicboom reached this function.
 * Effect start init 45 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Sonic Boom.
 */
void BattleAnim_InitializeSonicBoomUse(void) {
    func_8213B644(0, 8, 0x20);
}

/**
 * Lifecycle init for effects 127 and 128: places the particle at one of three positions
 * by slot, starts it small and growing, and delays it 8 frames per slot.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_FieldCE_GetS32_0C040(arg0);

    switch (sp26) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, 0.0f, 0.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, 10.0f, 10.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, 15.0f, -15.0f);
            break;
    }

    Particle_SetScaleScaled(arg0, 0.1f);
    Particle_SetScaleTarget(arg0, 2.0f);
    Particle_SetScaleStep(arg0, 0.0625f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_Param0_SetS16_0BCA8(arg0, sp26 * 8);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback with several staged waits: init, wait for the spawn step, then a
 * 10-frame delay, then the approach steps of func_821402B8 / func_82140548, then inactive.
 */
void func_8215F3EC(Particle* arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_8215F2B8(arg0);
        return;
    case 2:
        if (func_821406B4(arg0) != 0) {
            func_8213CB3C(arg0);
            Particle_SetParam0(arg0, 0xA);
            return;
        }
        return;
    case 3:
        func_821402B8(arg0);
        if (func_82140690(arg0) != 0) {
            func_82140548(arg0, 0, 0x10);
            return;
        }
        break;
    case 4:
        Particle_MarkInactive(arg0);
        break;
    }
}

/**
 * Starts effect 127's three scale-fade particles for the current animation owner.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_StartEffect127Descriptor39ScaleFade(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade, &gBattleAnimParticleDescriptors[0x39], 8, 3, 2, 0, 0x45, 0);
}

/**
 * Starts effect 128's three scale-fade particles for the current animation owner.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_StartEffect128Descriptor39ScaleFade(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade, &gBattleAnimParticleDescriptors[0x39], 8, 3, 2, 0, 0x47, 0);
}

/**
 * Starts the three delayed model particles of effect 12/129 for the current animation
 * owner.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_CreateTypeX(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_ConfuseRayAmnesiaModelAnimWait, &gDefaultParticleDescriptor, 0x1E, 3, 6, 0, 0, 0);
}

/**
 * Starts a default hit spark with particle descriptor 0x34 for the current animation
 * owner.
 * Seen in play (2026-11-13): ran in the 165-move battle sweep (1 of the moves).
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_CreateSmoke(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 6);
}

/**
 * Effect start init 129 (BattleAnim_RunEffectInitStart/End). Effect-id sweep, all 165 moves used:
 * it ran for exactly Double Edge, Struggle, Submission, Take Down.
 */
void ParticleEffect_CreateSmokeHighPriority(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_RunDefaultHitSpark, &gBattleAnimParticleDescriptors[0x34], 0, 1, 0x11, 9, 0, 6);
}

/**
 * Lifecycle init for effect 132: places the particle at one of three positions by slot,
 * starts it tiny and growing, and delays it 8 frames per slot.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade_InitParticle(Particle* arg0) {
    s16 sp26 = Particle_SpawnIndex_GetS16_0C038(arg0);
    s16 sp24 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_FieldCE_GetS32_0C040(arg0);

    switch (sp26) {
        case 0:
            Particle_SetPosition(arg0, 0.0f, 0.0f, 0.0f);
            break;

        case 1:
            Particle_SetPosition(arg0, 0.0f, 10.0f, 10.0f);
            break;

        case 2:
            Particle_SetPosition(arg0, 0.0f, 15.0f, -15.0f);
            break;
    }

    Particle_SetScaleScaled(arg0, 0.01f);
    Particle_SetScaleTarget(arg0, 0.5f);
    Particle_SetScaleStep(arg0, 0.05f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_Param0_SetS16_0BCA8(arg0, sp26 * 8);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

/**
 * Particle callback for effect 132: after its delay, grows the particle, then rises and
 * fades it out before marking it inactive.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade_InitParticle(arg0);
            break;

        case 2:
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_EnableRendering(arg0);
                Particle_Param0_SetS16_0BCA8(arg0, 10);
            }
            break;

        case 3:
            Particle_ApproachScaleTarget(arg0);
            func_8213E1FC(arg0, 1.0f);
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                Particle_Param0_SetS16_0BCA8(arg0, 0x10);
            }
            break;

        case 4:
            Particle_ApproachStepMagnitude(arg0, 0x40800000, 0x3F000000);
            func_8213E1FC(arg0, arg0->stepMagnitude);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 0x10);
            if (Particle_DecrementParam0ToZeroThenAdvance(arg0) != 0) {
                break;
            }
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }
}

/**
 * Starts effect 132's particles for the current animation owner twice, the second set 16
 * frames later.
 * Not reached in play (2026-11-13): did not run in the 165-move battle sweep (each move used once,
 * from the command menu to the end of its turn) or in a tour of the menus and a COM battle.
 * @unverified Name from Stadium 1.
 */
void ParticleEffect_CreateDual(void) {
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade, &gBattleAnimParticleDescriptors[0x39], 8, 3, 2, 0, 0x46, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x10, BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade, &gBattleAnimParticleDescriptors[0x39], 8, 3, 2, 0, 0x46, 0);
}
