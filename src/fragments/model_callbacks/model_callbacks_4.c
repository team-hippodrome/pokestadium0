/* Stadium Zero fragment 001 (model callbacks): per-species particle effects
 * (Koffing, Weezing, Gastly, Ponyta, Rapidash, Vaporeon, Articuno, Moltres). */
#include "global.h"
#include "model_callbacks.h"
#include "gfx_buffer.h"
#include "geo_render.h"
#include "model_renderer_callbacks.h"
#include "battle_hud.h"
#include "vector_math.h"
#include "pokemon.h"

extern Vec3f sModelParticleResetPosition;
extern Vec3f sModelParticleResetVelocity;
extern Vec3f sModelParticleResetScale;
extern Vec3f sModelParticleSpawnScale;
extern ModelParticle sModelParticles[][MODEL_PARTICLE_COUNT];
extern s32 sModelParticleDrawCount;
extern s32 sModelParticleCallbackCount;
extern ModelSmokeSpawnFrames sModelSmokeSpawnFrames[18];
extern s16 sModelSmokeSpawnFrameSets[18];
extern CameraNode* D_80060488;

/** Clears particle `index` of an effect slot. Hit in play. */
void ModelParticle_ResetSlot(s32 effect_slot, s32 index) {
    s32 pad[2]; // FAKE
    Vec3f sp1C = sModelParticleResetPosition;
    Vec3f sp10 = sModelParticleResetVelocity;
    Vec3f sp4 = sModelParticleResetScale;

    sModelParticles[effect_slot][index].active = 0;
    sModelParticles[effect_slot][index].age = 0;
    sModelParticles[effect_slot][index].position = sp1C;
    sModelParticles[effect_slot][index].velocity = sp10;
    sModelParticles[effect_slot][index].scale = sp4;
}

/**
 * Clears every particle of an effect slot. Resident ModelRenderer_ResetSlot calls it through
 * Util_ConvertAddrToVirtAddr when a display object animation starts (hit in play).
 */
void ModelParticle_ResetEffectSlot(s32 effect_slot) {
    s32 i;

    for (i = 0; i < 10; i++) {
        ModelParticle_ResetSlot(effect_slot, i);
    }
}

/**
 * Resets the per-frame draw and callback counters. Resident
 * ModelAnim_UpdateDisplayObjectAnimation calls it every frame through Util_ConvertAddrToVirtAddr.
 */
void ModelParticle_ResetFrameCounters(void) {
    sModelParticleDrawCount = 0;
    sModelParticleCallbackCount = 0;
}

/**
 * Spawns one particle into the first free slot of `particles`, at the model's root with a
 * species-specific spread, scale and outward speed. Hit for Articuno and Moltres in Free Battle.
 */
void ModelParticle_Spawn(ModelParticle* particles) {
    s32 var_v0;
    Vec3f sp90;
    Vec3f sp84;
    Vec3f sp78;
    s32 var_s1;
    f32 temp_fv0_2;
    Vec3f sp64 = sModelParticleSpawnScale;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    u32 pad[2]; // FAKE
    f32 var_fs0;

    var_s1 = 10;
    guMtxXFMF(GeoRender_GetRelativeMatrix(-1)->mf, 0, 0, 0, &sp90.x, &sp90.y, &sp90.z);
    guMtxXFMF(GeoRender_GetRelativeMatrix(0)->mf, 0, 0, 0, &sp84.x, &sp84.y, &sp84.z);
    sp60 = D_8006049C->scale.x;
    sp5C = D_8006049C->scale.y;
    sp58 = D_8006049C->scale.z;
    switch (D_8006049C->objectType) {
        case KOFFING:
        case WEEZING:
            var_fs0 = 0.5f;
            break;
        case MOLTRES:
            var_fs0 = 1.0f;
            sp64.x = 0.1f;
            sp64.y = 0.1f;
            sp64.z = 0.1f;
            sp84.x += (f32)((guRandom() % 10) - 5) * sp60;
            sp84.y += (f32)((guRandom() % 10) - 5) * sp5C;
            sp84.z += (f32)((guRandom() % 10) - 5) * sp58;
            break;
        case PONYTA:
            var_fs0 = 0.5f;
            sp64.x = 0.002f;
            sp64.y = 0.002f;
            sp64.z = 0.002f;
            sp84.x += (f32)((guRandom() % 20) - 10) * sp60;
            sp84.y += (f32)((guRandom() % 20) - 10) * sp5C;
            sp84.z += (f32)((guRandom() % 20) - 10) * sp58;
            break;
        case RAPIDASH:
            var_fs0 = 0.5f;
            sp64.x = 0.05f;
            sp64.y = 0.05f;
            sp64.z = 0.05f;
            sp84.x += (f32)((guRandom() % 20) - 10) * sp60;
            sp84.y += (f32)((guRandom() % 10) - 5) * sp5C;
            sp84.z += (f32)((guRandom() % 20) - 10) * sp58;
            break;
        case ARTICUNO:
            var_fs0 = 0.0f;
            sp64.x = 0.5f;
            sp64.y = 0.5f;
            sp64.z = 0.5f;
            sp84.x += (f32)((guRandom() % 20) - 10) * sp60;
            sp84.y += (f32)((guRandom() % 20) - 10) * sp5C;
            sp84.z += (f32)((guRandom() % 20) - 10) * sp58;
            break;
        case VAPOREON:
            var_fs0 = 0.0f;
            sp64.x = 0.5f;
            sp64.y = 0.5f;
            sp64.z = 0.5f;
            sp84.x += (f32)((guRandom() % 60) - 30) * sp60;
            sp84.y += (f32)((guRandom() % 40) - 10) * sp5C;
            sp84.z += (f32)((guRandom() % 60) - 30) * sp58;
            break;
        case GASTLY:
            var_fs0 = 0.0f;
            var_s1 = 3;
            sp64.x = 20.0f;
            sp64.y = 20.0f;
            sp64.z = 20.0f;
            break;
        default:
            var_fs0 = 0.0f;
            break;
    }
    for (var_v0 = 0; var_v0 < 10; var_v0++) {
        if (var_v0 >= var_s1) {
            break;
        }
        if (particles->active == 0) {
            sp78.x = sp84.x - sp90.x;
            sp78.y = sp84.y - sp90.y;
            sp78.z = sp84.z - sp90.z;
            temp_fv0_2 = sqrtf((sp78.x * sp78.x) + (sp78.y * sp78.y) + (sp78.z * sp78.z));
            if (temp_fv0_2 > 0.0f) {
                sp78.x /= temp_fv0_2;
                sp78.y /= temp_fv0_2;
                sp78.z /= temp_fv0_2;
            }
            particles->velocity.x = (f32)(var_fs0 * sp78.x);
            particles->velocity.y = (f32)(var_fs0 * sp78.y);
            particles->velocity.z = (f32)(var_fs0 * sp78.z);
            particles->position = sp84;
            particles->scale = sp64;
            particles->age = 0;
            particles->active = 1;
            break;
        }
        particles++;
    }
}

/**
 * Decides whether the current model spawns a particle this frame: on fixed animation frames for
 * Koffing and Weezing and every 8th frame for Gastly, otherwise at random. Hit for Articuno and
 * Moltres in Free Battle.
 */
void ModelParticle_UpdateSpawn(ModelParticle* particles) {
    s32 pad[1]; // FAKE
    s16 temp_v1;
    s32 var_a1;
    s16 temp_a0;
    s32 var_v0;
    s16* var_v1;

    var_a1 = D_8006049C->transformAnim.frameFixed >> 0x10;
    switch (D_8006049C->objectType) {
        case KOFFING:
        case WEEZING:
            temp_v1 = D_8006049C->transformAnim.animationId;
            temp_a0 = sModelSmokeSpawnFrameSets[sModelParticleCallbackCount % 18];
            switch (temp_v1) {
                case 4:
                    if (var_a1 == sModelSmokeSpawnFrames[temp_a0].animation4Frame) {
                        ModelParticle_Spawn(particles);
                        return;
                    }
                    break;
                case 3:
                    var_v0 = 0;
                    var_v1 = &sModelSmokeSpawnFrames[temp_a0].defaultFrame; // FAKE: walks animation3Frames as var_v1[2..4]
                    do {
                        if (var_a1 == var_v1[2]) {
                            ModelParticle_Spawn(particles);
                        }
                        var_v0 += 2;
                        var_v1++;
                    } while (var_v0 != 6);
                    return;
                    break;
                case 2:
                    if (var_a1 == sModelSmokeSpawnFrames[temp_a0].animation2Frame) {
                        ModelParticle_Spawn(particles);
                        return;
                    }
                    break;
                default:
                    if (var_a1 == sModelSmokeSpawnFrames[temp_a0].defaultFrame) {
                        ModelParticle_Spawn(particles);
                        return;
                    }
                    return;
            }
            break;
        case MOLTRES:
            if ((guRandom() % 60) == 0) {
                ModelParticle_Spawn(particles);
                return;
            }
            break;
        case ARTICUNO:
            if ((guRandom() % 30) == 0) {
                ModelParticle_Spawn(particles);
                return;
            }
            break;
        case VAPOREON:
            if ((guRandom() % 7) == 0) {
                ModelParticle_Spawn(particles);
                return;
            }
            break;
        case GASTLY:
            if ((var_a1 & 7) == 0) {
                ModelParticle_Spawn(particles);
                return;
            }
            break;
        case PONYTA:
        case RAPIDASH:
            if ((guRandom() % 7) == 0) {
                ModelParticle_Spawn(particles);
            }
            break;
    }
}

/**
 * Draws one particle as a camera-facing billboard with a species-specific texture and color, then
 * ages and moves it. Hit for Articuno and Moltres in Free Battle.
 */
Gfx* ModelParticle_Draw(Gfx* gfx, ModelParticle* particle, DisplayListAddresses* addresses, s16 effect_slot) {
    Mtx* sp1EC;
    Mtx sp1A8;
    Mtx sp168;
    Mtx sp128;
    s32 pad; // FAKE
    MtxF spE4;
    DisplayObject* ptr;

    sp1EC = Gfx_AllocDisplayList(0x40);
    MtxF_ExtractScale(&spE4, &D_80060488->view.floatMatrix);
    guMtxF2L(spE4.mf, &sp128);
    guScale(&sp1A8, D_8006049C->scale.x * particle->scale.x * 0.1f, D_8006049C->scale.y * particle->scale.y * 0.1f,
            D_8006049C->scale.z * particle->scale.z * 0.1f);
    guTranslate(&sp168, particle->position.x, particle->position.y, particle->position.z);
    guMtxCatL(&sp1A8, &sp168, sp1EC);
    guMtxCatL(&sp128, sp1EC, sp1EC);
    gSPMatrix(gfx++, sp1EC, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, addresses->segments[0]);
    switch (D_8006049C->objectType) {
        case KOFFING:
        case WEEZING:
            gDPLoadTextureBlock_4b(gfx++, addresses->textures[particle->age / 2], G_IM_FMT_I, 32, 32, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetPrimColor(gfx++, 0, 0, 0x0A, 0x00, 0x00, 0xC8 - (particle->age * 0xD)); // #0A0000
            break;
        case GASTLY:
            gDPLoadTextureBlock_4b(gfx++, addresses->textures[particle->age / 2], G_IM_FMT_I, 32, 32, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetEnvColor(gfx++, 0x32, 0x14, 0x46, 0x00); // #321446
            if (particle->age < 10) {
                gDPSetPrimColor(gfx++, 0, 0, 0x64, 0x46, 0x82, 0xFF); // #644682
            } else {
                gDPSetPrimColor(gfx++, 0, 0, 0x64, 0x46, 0x82, 0x28F - (particle->age * 0x28)); // #644682
            }
            break;
        case MOLTRES:
        case PONYTA:
        case RAPIDASH:
            gDPLoadTextureBlock_4b(gfx++, addresses->textures[particle->age / 2], G_IM_FMT_I, 32, 32, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0x00, 0xFA - (particle->age * 3)); // #FFFF00
            break;
        case VAPOREON:
        case ARTICUNO:
            gDPLoadTextureBlock(gfx++, addresses->textures[particle->age / 2], G_IM_FMT_IA, G_IM_SIZ_16b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            if (particle->age < 4) {
                gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, (particle->age * 0x14) + 0xB4); // #FFFFFF
            } else {
                gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, 0x122 - (particle->age * 0xA)); // #FFFFFF
            }
            break;
        default:
            gDPLoadTextureBlock_4b(gfx++, addresses->textures[particle->age / 2], G_IM_FMT_I, 32, 32, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gDPSetPrimColor(gfx++, 0, 0, 0x0A, 0x00, 0x00, 0xC8 - (particle->age * 0xD)); // #0A0000
            break;
    }
    gSPDisplayList(gfx++, addresses->segments[1]);
    gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
    if (ModelPhase_IsIdle() == 0) {
        ptr = D_8006049C;
        switch (ptr->objectType) {
            case KOFFING:
            case WEEZING:
                particle->position.y += 0.5f * ptr->scale.y;
                particle->age++;
                particle->scale.x += 0.1f;
                particle->scale.y += 0.1f;
                particle->scale.z += 0.1f;
                if (particle->age >= 0x10) {
                    particle->active = 0;
                }
                break;
            case GASTLY:
                particle->age++;
                if (particle->age >= 0x10) {
                    particle->active = 0;
                }
                break;
            case MOLTRES:
                particle->position.y += 1.5f * ptr->scale.y;
                particle->age++;
                particle->scale.x += 0.005f;
                particle->scale.y += 0.005f;
                particle->scale.z += 0.005f;
                if (particle->age >= 0x10) {
                    particle->active = 0;
                }
                break;
            case PONYTA:
                particle->position.y += 0.75f * ptr->scale.y;
                particle->age++;
                particle->scale.x += 0.005f;
                particle->scale.y += 0.005f;
                particle->scale.z += 0.005f;
                if (particle->age >= 0x10) {
                    particle->active = 0;
                }
                break;
            case RAPIDASH:
                particle->position.y += ptr->scale.y;
                particle->age++;
                particle->scale.x += 0.005f;
                particle->scale.y += 0.005f;
                particle->scale.z += 0.005f;
                if (particle->age >= 0x10) {
                    particle->active = 0;
                }
                break;
            case ARTICUNO:
                particle->position.y -= 0.5f * ptr->scale.y;
                if (particle->age < 4) {
                    particle->scale.x += 0.15f;
                    particle->scale.y += 0.15f;
                    particle->scale.z += 0.15f;
                } else {
                    particle->scale.x -= 0.075f;
                    particle->scale.y -= 0.075f;
                    particle->scale.z -= 0.075f;
                }
                particle->age++;
                if ((particle->age >= 12) || (particle->position.y < 0.0f)) {
                    particle->active = 0;
                }
                break;
            case VAPOREON:
                if (particle->age < 4) {
                    particle->scale.x += 0.15f;
                    particle->scale.y += 0.15f;
                    particle->scale.z += 0.15f;
                } else {
                    particle->scale.x -= 0.075f;
                    particle->scale.y -= 0.075f;
                    particle->scale.z -= 0.075f;
                }
                particle->age++;
                if ((particle->age >= 12) || (particle->position.y < 0.0f)) {
                    particle->active = 0;
                }
                break;
            default:
                particle->age++;
                if (particle->age >= 0x10) {
                    particle->active = 0;
                }
                break;
        }
        particle->position.x = (f32)(particle->position.x + particle->velocity.x);
        particle->position.y = (f32)(particle->position.y + particle->velocity.y);
        particle->position.z = (f32)(particle->position.z + particle->velocity.z);
        particle->velocity.x *= 0.9f;
        particle->velocity.y *= 0.9f;
        particle->velocity.z *= 0.9f;
    }
    return gfx;
}

/** Draws every active particle of an effect slot. Hit in Free Battle. */
Gfx* ModelParticle_DrawAll(Gfx* gfx, ModelParticle* particles, DisplayListAddresses* addresses, s16 effect_slot) {
    s32 i;

    for (i = 0; i < 10; i++, particles++) {
        if (particles->active == 1) {
            gfx = ModelParticle_Draw(gfx, particles, addresses, effect_slot);
            sModelParticleDrawCount++;
        }
    }
    return gfx;
}

/**
 * Model callback for species particle effects. Phase 2 updates spawning and draws the particles
 * of the model's effect slot, on the first call of the frame only. Used by Ponyta, Rapidash,
 * Gastly, Koffing, Weezing, Vaporeon, Articuno and Moltres model data; hit for Vaporeon,
 * Articuno and Moltres.
 */
void ModelCallback_Particles(s32 phase, DisplayListState* state) {
    s32 pad0[2]; // FAKE
    DisplayListAddresses* sp4C;
    s32 pad; // FAKE
    s16 temp_v1;
    s32 pad3[3]; // FAKE
    ModelParticle* sp1C;
    s32 sp18;
    ModelParticle* temp_a1;
    Gfx* gfx;
    s32 pad4[1]; // FAKE

    sp4C = state->addresses;
    if (phase == 0) { // karodo
    } else if (phase == 2) {
        if (sModelParticleCallbackCount == 0) {
            state->gfx = Gfx_AllocDisplayList(1048);
        } else {
            state->gfx = Gfx_AllocDisplayList(8);
        }
        gfx = state->gfx;
        temp_v1 = D_8006049C->effectSlot;
        if ((temp_v1 < 2) && (sModelParticleDrawCount >= 0) && (sModelParticleDrawCount < 11)) {
            temp_a1 = sModelParticles[temp_v1];
            sp1C = temp_a1;
            sp18 = temp_v1;
            ModelParticle_UpdateSpawn(temp_a1);
            if (sModelParticleCallbackCount == 0) {
                gfx = ModelParticle_DrawAll(gfx, temp_a1, sp4C, temp_v1);
            }
        }
        gSPEndDisplayList(gfx++);
    }
    sModelParticleCallbackCount++;
}
