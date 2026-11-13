/* Stadium Zero fragment012_17ED00. */

#include "global.h"
#include "fragments/particle_math/particle_math.h"

void func_821401D4(Particle*, f32);
void func_8213E11C(Particle*, f32);
u32 ParticleMath_RandomRange(u32 arg0);
void Particle_SetRotationStepY(Particle*, s16);
void Particle_SetStepMagnitudeScaled(Particle*, f32);
void Particle_SetMotionStepYScaled(Particle*, f32);
void func_82143478(Particle*, s32);
void Particle_SetPrimAlpha(s8 *arg0, char arg1);
void Particle_SetUnkA6(Particle*, s32);
void func_8213C9D0(Particle*);

void func_82168C20(Particle* arg0) {
    func_821401D4(arg0, 0.16f);
    func_8213E11C(arg0, -3.2f);
    Particle_SetRotationStepY(arg0, ParticleMath_RandomRange(0x10000));
    Particle_SetStepMagnitudeScaled(arg0, 0.085f);
    Particle_SetMotionStepYScaled(arg0, 0.44f);
    func_82143478(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetUnkA6(arg0, 2);
    func_8213C9D0(arg0);
}

extern Vec3f D_8219A898;

void func_82168CC4(Particle* arg0) {
    switch (arg0->lifecycle) {
        case 1:
            func_82168C20(arg0);
            break;

        case 2:
            BattleAnim_GetOwnerBonePosition(arg0->pokemon, arg0->unk_CD, &D_8219A898);
            Particle_ApproachPosition(arg0, D_8219A898);
            Particle_ApproachScale(arg0, 0.2f, 0.053f);
            Particle_ApproachPrimAlphaThenAdvance(arg0, 0x10, 0x1A);
            Particle_PrimG_Approach_0BB14(arg0, 0, 0x40);
            if (Particle_DecrementUnkA6ToZero(arg0) != 0) {
                Particle_PrimR_Approach_0BAE4(arg0, 0, 8);
                Particle_EnvR_Approach_0BB90(arg0, 0, 0xE);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (arg0->lifecycle > 0) {
        Particle_AddVelocityXZFromRotationYViaImpulse(arg0);
        Particle_Field50_AddXFromField7C_09C58(arg0);
    }

    if (BattleScene_IsParticipantModelVisible(arg0->pokemon)) {
        Particle_EnableRendering(arg0);
    } else {
        Particle_DisableRendering(arg0);
    }
}

extern void* D_82199DE0[];
extern void* D_8219A810;
extern s32 D_800733C8;
extern u8 D_8218E5A0[];
s32 func_82107CF0(void*);
void func_8213B5D8(s32, s32, s32, void (*)(Particle*), u8*, s32, s32, s32, s32, s32, s32);

void func_82168E18(s32 arg0) {
    D_8219A810 = D_82199DE0[arg0];
    if (D_800733C8 == 0x8080) {
        if (func_82107CF0(D_8219A810) == 6) {
            func_8213B5D8(0, 0, -1, func_82168CC4, D_8218E5A0, 0, 1, 0x11, 0xA, 0, 0);
        }
    }
}
