/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_328F10.c, src/gallery.c. */

#include "fragments/battle_engine/battle_engine.h"

#include "gallery.h"
#include "fragments/gallery_camera/gallery_camera.h"
#include "fragments/particle_data_library/particle_data_library.h"
#include "fragments/particle_math/particle_math.h"
#include "geo_node.h"
#include "geo_render.h"
#include "model_animation.h"
#include "model_animation_events.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "game_state.h"
#include "jpeg_stream.h"
#include "audio_sfx_wrapper.h"
#include "audio_loop_point.h"
#include "memory.h"
#include "util.h"
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;

    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} unk_D_800761B0;
typedef struct unk_func_8003013C_arg1 {
    /* 0x00 */ u8 pad00[0x1C];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} unk_func_8003013C_arg1;
typedef struct unk_func_80031660_sp24 {
    /* 0x00 */ u8 pad00[0x18];
    /* 0x18 */ s32 unk_18;
} unk_func_80031660_sp24;
s32 Gallery_ConfigurePhotoCamera();
s32 Gallery_SetScenePoseCamera();
s32 Gallery_SetCameraAngleOffsets();
s32 Gallery_SetCameraAngleOffsetsAlternate();
s32 Gallery_SetSceneModelNode();
s32 Gallery_SetSceneRenderState();
s32 Gallery_SetSceneGraphNode();
s32 func_800303C8();
void func_82150D1C(void);
void func_82183DA4(void);
typedef union unk_func_80026268_arg0_000_raw {
    struct {
        u8 unk_00;
        u8 unk_01;
        u16 unk_02;
    };
    f32 raw;
} unk_func_80026268_arg0_000_raw;
typedef struct unk_func_80026268_arg0_raw {
    /* 0x00 */ unk_func_80026268_arg0_000_raw unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09[4];
    /* 0x0D */ u8 pad0D;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ u16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u8 unk_20[4];
    /* 0x24 */ u8 unk_24;
    /* 0x25 */ u8 unk_25;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u8 unk_30[11];
    /* 0x3B */ u8 unk_3B[11];
    /* 0x46 */ u8 unk_46[11];
    /* 0x51 */ char unk51[0x1];
    /* 0x52 */ u8 unk_52;
    /* 0x53 */ u8 unk_53;
} unk_func_80026268_arg0_raw;
typedef struct unk_D_83403C60_raw {
    /* 0x00 */ unk_func_80026268_arg0_raw unk_00;
    /* 0x54 */ char unk54[0x18];
    /* 0x6C */ u8 unk_6C;
    /* 0x6D */ char unk6D[0x3];
    /* 0x70 */ unk_D_83407AC8 unk_70;
    /* 0x8A */ char unk8A[0x2];
} unk_D_83403C60_raw;

#include "m2c_macros.h"

void BattleAnim_InitStartEffect139Descriptor42FallingScale(Particle* arg0);
void BattleAnim_InitStartEffect139Descriptor22SpinFade(Particle* arg0);
void BattleAnim_InitStartEffects133And134And143Descriptor44ModeOrbit(Particle* arg0);
void BattleAnim_InitStartEffects133And134And143Descriptor38MetadataBurst(Particle* arg0);
void func_82150DCC(void);
void func_82150EB0(void);
void BattleAnim_StartEffect122GlobalAndOwnerTintFade(void);

void func_82150D1C(void);

void BattleAnim_InitStartEffect135Descriptor1CRisingScale(Particle* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);
    s16 sp24 = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field38_SetYScaled_08CA0(arg0, 2.5f);
    Particle_Field1C_SetScaled_0B938(arg0, 0.065789476f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    sp28.x = ParticleMath_RandomSigned(0x5000);
    sp28.y = sp24 * (0x10000 / arg0->unk_AA);
    sp28.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp28);
    ParticleGfx_RecolorPrim(arg0, sp26);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect135Descriptor1CRisingScaleFade(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitStartEffect135Descriptor1CRisingScale(arg0);
            break;

        case 2:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, Particle_FieldAC_GetS16_0C038(arg0)) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_Field1C_Approach_0B98C(arg0, 1.3157895f, 0.16447368f);
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 4:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x10);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_Field94_AddY_0A594(arg0, 0x400);
    Particle_AddVelocityFromRotationTemplate1(arg0);
}

u16 func_8213C484();                                /* extern */
M2C_UNK func_8213C9D0(s32);                         /* extern */
M2C_UNK func_821401D4(s32, M2C_UNK);                /* extern */
M2C_UNK func_82143478(s32, u16);                    /* extern */
void func_821501B4(s32 arg0)
{
  u16 sp26;
  sp26 = func_8213C484();
  func_821401D4(arg0, 0x3F286BCA);
  func_82143478(arg0, sp26);
  if (!arg0)
  {
  }
  Particle_SetTextureFrame(arg0, 2);
  func_8213C9D0(arg0);
}

void BattleAnim_CallbackStartEffect135ExpandingFlashFade(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitStartEffect135ExpandingFlash(arg0);
            break;

        case 2:
            Particle_Field1C_Approach_0B98C(arg0, 6.5789475f, 0.32894737f);
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0xF);
            break;

        case 3:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 4:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x20);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_InitStartEffect139Descriptor42FallingScale(Particle* arg0) {
    s16 sp2E = Particle_FieldCF_GetS16_0C058(arg0);
    s16 sp2C = Particle_FieldAC_GetS16_0C038(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.05f);
    Particle_SetRotation(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_Field74_SetScaled_0AD8C(arg0, 1.2f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp2E);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2C * 1);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

s32 Particle_ApproachStepMagnitude(Particle* arg0, f32 arg1, f32 arg2);
void BattleAnim_CallbackStartEffect139Descriptor42FallingScaleFade(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitStartEffect139Descriptor42FallingScale(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            if (Particle_Field1C_Approach_0B98C(arg0, 0.15f, 0.025f) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            if (Particle_Field1C_Approach_0B98C(arg0, 0.0f, 0.04f) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    Particle_ApproachStepMagnitude(arg0, 0.2, 0.2f);
    Particle_AddVelocityFromRotationTemplate1(arg0);
    Particle_Field38_AddYScaled_08E90(arg0, -1.0f);
}

void BattleAnim_InitStartEffect139Descriptor22SpinFade(Particle* arg0) {
    UNUSED s16 pad; // FAKE: stack padding
    s16 sp2C;

    Particle_FieldAC_GetS16_0C038(arg0);
    sp2C = Particle_FieldCF_GetS16_0C058(arg0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.175f);
    Particle_SetRotation(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp2C);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK Particle_ApproachPrimAlpha(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_82150474(s8 *);                      /* extern */

void func_82150504(s8 *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xAE);
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82150474(arg0);
        return;
    case 2:
        func_82140228(arg0, 0x3DCCCCCD, 0x3C23D70A);
        Particle_ApproachPrimAlpha(arg0, 0, 8);
        Particle_AddVelocityFromRotationTemplate1(arg0);
        func_821406B4(arg0);
        return;
    case 3:
        Particle_DisableAndDetach(arg0);
        return;
    }
}

void BattleAnim_InitStartEffect141Descriptor1CGridRise(Particle* arg0) {
    s16 sp2E;
    s16 sp2C;
    s16 temp_v0;
    Vec3s sp24;

    temp_v0 = Particle_FieldAC_GetS16_0C038(arg0);
    sp2E = temp_v0 / 8;
    sp2C = temp_v0 % 8;

    Particle_Field1C_SetScaled_0B938(arg0, 0.5f);
    sp24.x = 0x6000 - (sp2E * 0xC00);
    sp24.y = (sp2C << 0xC) + 0xB000;
    sp24.z = 0;
    Particle_Field94_AddVecFromVec3s_0A4F0(arg0, sp24);
    Particle_SetPrimColor(arg0, 0xC8, 0xFF, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp2E);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect141Descriptor1CGridRiseFade(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitStartEffect141Descriptor1CGridRise(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 0xA);
                Particle_EnableRendering(arg0);
            }
            break;

        case 3:
            Particle_Field94_AddY_0A594(arg0, 0x200);
            Particle_Field1C_Approach_0B98C(arg0, 2.0f, 0.01f);
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 4:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0, 0x20);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }
}

void BattleAnim_InitStartEffects133And134And143Descriptor44ModeOrbit(Particle* arg0) {
    s16 sp36;
    s16 sp34;
    s16 sp32 = Particle_FieldAC_GetS16_0C038(arg0);
    s16 sp30 = Particle_FieldCF_GetS16_0C058(arg0);
    s16 sp2E = Particle_FieldCE_GetS32_0C040(arg0);

    Particle_SetRotation(arg0, ParticleMath_RandomRange(0x10000), ParticleMath_RandomRange(0x10000), 0);
    Particle_Field1C_SetScaled_0B938(arg0, 0.01f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp30);

    switch (sp2E) {
        case 0:
            Particle_FieldAE_SetS16_0BF4C(arg0, ParticleMath_RandomRangeOffset(0x14, 0x14));
            Particle_FieldB0_SetS16_0BFEC(arg0, 0);
            sp36 = ParticleMath_RandomSignedOffsetBySign(0x200, 0x200);
            sp34 = ParticleMath_RandomSignedOffsetBySign(0x200, 0x200);
            Particle_FieldA8_SetS16_0BE14(arg0, 8);
            break;

        case 1:
            Particle_FieldAE_SetS16_0BF4C(arg0, ParticleMath_RandomRangeOffset(0x28, 0x14));
            Particle_FieldB0_SetS16_0BFEC(arg0, 1);
            sp36 = ParticleMath_RandomSignedOffsetBySign(0x200, 0x200);
            sp34 = ParticleMath_RandomSignedOffsetBySign(0x200, 0x200);
            Particle_FieldA8_SetS16_0BE14(arg0, 0x10);
            break;

        case 2:
            Particle_FieldAE_SetS16_0BF4C(arg0, ParticleMath_RandomRangeOffset(0x1E, 0x14));
            Particle_FieldB0_SetS16_0BFEC(arg0, 2);
            sp36 = ParticleMath_RandomSignedOffsetBySign(0x200, 0x200);
            sp34 = ParticleMath_RandomSignedOffsetBySign(0x200, 0x200);
            Particle_FieldA8_SetS16_0BE14(arg0, 0xA);
            break;

        case 3:
            Particle_FieldAE_SetS16_0BF4C(arg0, 0x1E - sp32);
            Particle_FieldB0_SetS16_0BFEC(arg0, 2);
            sp36 = ParticleMath_RandomSignedOffsetBySign(0x200, 0x200);
            sp34 = ParticleMath_RandomSignedOffsetBySign(0x200, 0x200);
            Particle_FieldA8_SetS16_0BE14(arg0, 0xA);
            break;
    }

    Particle_Field9A_SetX_0A3C4(arg0, sp36);
    Particle_Field9A_SetY_0A3D8(arg0, sp34);
    Particle_FieldA6_SetS16_0BCA8(arg0, sp32 * 2);
    Particle_DisableRendering(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void Particle_ApplyRotationStepX(Particle* arg0);
void BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl(Particle* arg0) {
    Particle_FieldCE_GetS32_0C040(arg0);

    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitStartEffects133And134And143Descriptor44ModeOrbit(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0) != 0) {
                Particle_EnableRendering(arg0);
                Particle_AdvancePhase(arg0);
            }
            break;

        case 3:
            if (Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.3f, 0.05f) != 0) {} // karodo
            break;

        case 4:
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, arg0->unk_A8) != 0) {
                Particle_AdvancePhase(arg0);
            }
            break;

        case 5:
            Particle_Field1C_ApproachAndStepState_0B9D0(arg0, 0.0f, 0.05f);
            break;

        case 6:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRenderingEnabled(arg0) != 0) {
        switch (arg0->phase) {
            case 1:
                Particle_ApplyRotationStepX(arg0);
                Particle_SetPositionFromRotationTemplate1(arg0, arg0->unk_AE);
                break;

            case 2:
                Particle_ApplyRotationStepX(arg0);
                Particle_FieldAE_Approach_0BF60(arg0, 0, arg0->unk_B0);
                Particle_SetPositionFromRotationTemplate1(arg0, arg0->unk_AE);
                break;
        }
    }

    Particle_Field38_AddYScaled_08E90(arg0, 10.0f);
}

void BattleAnim_InitStartEffects133And134And143Descriptor38MetadataBurst(Particle* arg0) {
    s16 sp26 = Particle_FieldCF_GetS16_0C058(arg0);

    Particle_Field1C_SetScaled_0B938(arg0, 0.2f);
    Particle_Field38_AddYScaled_08E90(arg0, 5.0f);
    ParticleGfx_RecolorPrimEnvFromPalettePair(arg0, sp26);
    Particle_SetPrimAlpha(arg0, 0x40);
    Particle_AdvanceLifecycle(arg0);
}

void func_8213E1FC(Particle* arg0, f32 arg1);
void BattleAnim_CallbackStartEffects133And134And143Descriptor38MetadataBurstEmitter(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            BattleAnim_InitStartEffects133And134And143Descriptor38MetadataBurst(arg0);
            break;

        case 2:
            Particle_Field1C_Approach_0B98C(arg0, 4.0f, 0.1f);
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0xC8, 8);
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 3:
            Particle_Field1C_Approach_0B98C(arg0, 0.25f, 0.5f);
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 6, 0x18, 7);
            if (Particle_TickDelayAndAdvanceLifecycle(arg0, 6) != 0) {
                Particle_FieldCC_SetU8_0BF04(arg0, 9);
            }
            break;

        case 4:
            func_8213E1FC(arg0, 15.0f);
            Particle_TickDelayAndAdvanceLifecycle(arg0, 0xA);
            BattleAnim_EmitParticleBurstWithMetadata(arg0, BattleAnim_RunSparkleHit, &gBattleAnimParticleDescriptors[0x42], 6, 0x18, 7);
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

M2C_UNK func_8213B5D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, s32, s32, s32, s32, s32, s32); /* extern */
extern M2C_UNK D_8218E698;
extern M2C_UNK D_8218E798;
extern M2C_UNK func_8215036C;

void func_82150D1C(void) {
    func_8213B5D8(0, 1, 0x1E, &func_82150504, &D_8218E698, 0x10, 1, 0x1E, 0, 0x3B, 0);
    func_8213B5D8(0, 1, 0x1E, &func_8215036C, &D_8218E798, 0x10, 2, 0x1E, 0, 0x3B, 0);
}

void func_82150DCC(void) {
    func_82150D1C();
}

extern M2C_UNK D_8218E668;

void func_82150DEC(void) {
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0xB, 1, 5, BattleAnim_RunSparkleHit, (ParticleDescriptor*)&D_8218E798, 0, 5, 0x1E, 0, 0x3B, 8);
    BattleAnim_SetSpawnDelay(0x10);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect141Descriptor1CGridRiseFade, (ParticleDescriptor*)&D_8218E668, 0, 0x40, 0x1E, 0, 8, 0);
    BattleAnim_SpawnDescriptor25AlphaFadeInHold(0, 2, 0x2C, 8, 0xFF);
}

void func_82150EB0(void) {
    func_82150DEC();
}

void BattleAnim_StartEffect135ExpandingFlashAndRisingScaleFade(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(0, 0, 0x10, 8);
    BattleAnim_SpawnOwnerModelTintRampDetach(0, 0x8, 0xFF, 0xFF, 0xFF);
    BattleAnim_SpawnInvisibility(0, 0xFF, 0xFF, 0xFF);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x14, 0x8, 0xFF, 0, 8);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect135ExpandingFlashFade, &gBattleAnimParticleDescriptors[0x21], 8, 1, 2, 0, 0x3C, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect135ExpandingFlashFade, &gBattleAnimParticleDescriptors[0x23], 8, 1, 2, 0, 0x3C, 0);
    BattleAnim_CreateEffectSlotForCurrentOwner(0, BattleAnim_CallbackStartEffect135ExpandingFlashFade, &gBattleAnimParticleDescriptors[0x17], 8, 1, 2, 0, 0x3C, 0);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 1, 4, BattleAnim_CallbackStartEffect135Descriptor1CRisingScaleFade, &gBattleAnimParticleDescriptors[0x1C], 5, 0x10, 7, 0, 0x36, 0);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0x32, 0x10, 0x8);
}

extern ParticleDescriptor D_8218E588[86];
extern M2C_UNK D_8218E7A0;
extern M2C_UNK D_8218E748;
void BattleAnim_StartEffect134ModeOrbitAndMetadataBurst(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 8, 6);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 5, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 4, 9, 0, 0x3C, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 5, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 4, 9, 0, 0x3C, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x18, 1, 4, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 8, 9, 0, 0x3C, 2);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x1E, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 8, 9, 0, 0x3C, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x1E, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 8, 9, 0, 0x3C, 3);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x26, 0x8, 0, 0xFF, 4);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x2D, BattleAnim_CallbackStartEffects133And134And143Descriptor38MetadataBurstEmitter, &D_8218E748, 0x1A, 1, 2, 0, 0x3C, 0);
    BattleAnim_SpawnInvisibility(0x48, 0x40, 0, 0xFF);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0x55, 6, 0x8);
}

extern ParticleDescriptor D_8218E588[86];
extern M2C_UNK D_8218E7A0;
extern M2C_UNK D_8218E748;
void BattleAnim_StartEffect143ModeOrbitAndMetadataBurst(void) {
    UNUSED s32 pad; // FAKE: stack padding

    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 8, 6);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 1, 4, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 8, 9, 0, 0x3C, 2);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(6, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 8, 9, 0, 0x3C, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(6, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 8, 9, 0, 0x3C, 3);
    BattleAnim_SpawnOwnerModelTintRampDetach(0xE, 0x8, 0, 0xFF, 4);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x14, BattleAnim_CallbackStartEffects133And134And143Descriptor38MetadataBurstEmitter, &D_8218E748, 0x1A, 1, 2, 0, 0x3C, 0);
    BattleAnim_SpawnInvisibility(0x2D, 0x40, 0, 0xFF);
    BattleAnim_SpawnGlobalTintColorFadeDetach(0x32, 6, 0x8);
}

extern ParticleDescriptor D_8218E588[86];
void BattleAnim_StartEffect133ModeOrbitBurstAndEffect135Followup(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 8, 6);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 5, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 4, 9, 0, 0x3C, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0, 4, 5, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 4, 9, 0, 0x3C, 1);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x18, 1, 4, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 8, 9, 0, 0x3C, 2);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x1E, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 8, 9, 0, 0x3C, 3);
    BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(0x1E, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &D_8218E7A0, 0, 8, 9, 0, 0x3C, 3);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x26, 0x8, 0, 0xFF, 8);
    BattleAnim_CreateEffectSlotForCurrentOwner(0x28, BattleAnim_CallbackStartEffects133And134And143Descriptor38MetadataBurstEmitter, &D_8218E748, 0x18, 1, 2, 0, 0x3C, 0);
    BattleAnim_SpawnWhiteHueChange(0x3C, 0, 0x40, 0x8, 0xFF);
    BattleAnim_SpawnInvisibility(0x40, 0xFF, 0, 0xFF);
    BattleAnim_SetSpawnDelay(0x50);
    BattleAnim_StartEffect135ExpandingFlashAndRisingScaleFade();
}

void BattleAnim_StartEffect122GlobalAndOwnerTintFade(void) {
    BattleAnim_SpawnGlobalTintColorFadeDetach(0, 0xFF, 0);
    BattleAnim_SpawnOwnerModelTintRampDetach(0x14, 0, 0, 0xFF, 0x10);
}
