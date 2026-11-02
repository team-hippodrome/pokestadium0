/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_315D50.c, src/fragments/battle_engine/battle_engine_32B680.c, src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math.h"
#include "math_util.h"
/* Spline camera path state (scene spline block pointer, keyframe buffer) and helper shared by the func_82135xxx camera path functions. */
extern s8 D_FLT_8219A5B0;
extern BattleScene* D_8219A5A0;
void Battle_ComputeSplineWeightsVariantC(f32* arg0, f32 arg1);
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

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "matrix.h"
#include "math_util.h"

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "audio_commands.h"
#include "3D140.h"
#include "audio_fade.h"
#include "audio_sfx.h"
#include "audio_loop_point.h"
#include "cry.h"
#include "matrix.h"
#include "math_util.h"
typedef struct unk_D_84392040 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ char unk14[0x4];
} unk_D_84392040;
#include "prevent_bss_reordering.h"
extern s32 gBattleAnimFrameCounter;
extern s32 gBattleAnimSpawnDelay;
extern s32 sBattleAnimQueuedMoveId;
extern s32 sBattleAnimQueuedEffectListMode;
#define BATTLE_ANIMATION_QUEUE_INACTIVE 0
#define BATTLE_ANIMATION_QUEUE_START 1
#define BATTLE_ANIMATION_QUEUE_END 2
extern s32 sD_843902B4;
extern s32 sBattleAnimQueuedEffectList;
extern s32 sD_843902BC;
extern s32 sBattleAnimQueuedResourceListPending;
extern s32 sBattleAnimQueuedResourceListId;
extern s32 sBattleAnimQueuedAlternatePending;
extern s32 sBattleAnimQueuedAlternateMoveId;
extern s32 sBattleAnimQueuedAlternateList;
extern s32 sBattleAnimQueuedExtraPending;
extern s32 sBattleAnimQueuedExtraMoveId;
extern s32 sBattleAnimQueuedExtraList;
extern s8 sBattleAnimCurrentEffectList;
extern s16 gBattleAnimCurrentAnchor;
extern s16 gBattleAnimDefaultAnchor;
extern s16 sBattleAnimAlternateAnchor;
extern ActivePokemon* gBattleAnimCurrentOwner;
extern ActivePokemon* gBattleAnimSecondaryOwner;
extern ActivePokemon* gBattleAnimTertiaryOwner;
extern s32 D_811842A0;
extern s32 D_8219A830;
extern s8 sBattleAnimEffectCallbackIndex;
extern func_D_84390300 gBattleAnimEffectUpdateFuncs[8];
extern func_D_84390320 gBattleAnimEffectDrawFuncs[8];
extern f32 sD_84390344;
extern Vec3s sD_84390354;
extern Vec3f sD_84390360;
extern Vec3s sD_8439036C;
extern Vec3s sD_84390374;
extern s16 gSavedPrimColorR;
extern s16 gSavedPrimColorG;
extern s16 gSavedPrimColorB;
extern s16 gSavedPrimColorA;
extern s16 gPrimColorR;
extern s16 gPrimColorG;
extern s16 gPrimColorB;
extern s16 gPrimColorA;
extern s16 gEnvColorR;
extern s16 gEnvColorG;
extern s16 gEnvColorB;
extern s16 gEnvColorA;
extern s16 gFogColorR;
extern s16 gFogColorG;
extern s16 gFogColorB;
extern s16 gFogColorA;
extern s16 gBlendColorR;
extern s16 gBlendColorG;
extern s16 gBlendColorB;
extern s16 gBlendColorA;
extern s32 pad_D_843903A8[2];
extern s32 sD_843903B0;
extern s32 sD_843903B4;
extern s32 pad_D_843903B8[6];
extern DisplayObject sD_843903D0[16];
extern s32 sD_84391A50[16];
extern DisplayObject sD_84391A90[4];
extern s32 sD_84392030[4];
extern unk_D_84392040 sD_84392040;
extern f32 D_8219C590[26];
extern s32 sD_84385BB0[];
extern ParticleDescriptorChild gParticleDescriptorChildren[];
extern ParticleDescriptor gBattleAnimParticleDescriptors[];
extern func_D_84390320 sMoveAnimEffectStartInitFuncs[];
extern func_D_84390320 sMoveAnimEffectEndInitFuncs[];
extern u8 sD_8438682C[];
extern u8 sD_84386844[];
extern u8 sD_84386848[];
extern u8 sD_8438684C[];
extern u8 sD_84386850[];
extern u8 sD_84386854[];
extern u8 sD_84386858[];
extern u8 sD_8438685C[];
extern u8 sD_84386860[];
extern u8 sD_84386868[];
extern u8 sD_8438686C[];
extern u8 sD_84386870[];
extern u8 sD_84386874[];
extern u8 sD_84386878[];
extern u8 sD_8438687C[];
extern u8 sD_84386880[];
extern u8 sD_84386884[];
extern u8 sD_8438688C[];
extern u8 sD_84386894[];
extern u8 sD_84386898[];
extern u8 sD_8438689C[];
extern u8 sD_843868A0[];
extern u8 sD_843868A4[];
extern u8 sD_843868A8[];
extern u8 sD_843868AC[];
extern u8 sD_843868B0[];
extern u8 sD_843868B4[];
extern u8 sD_843868B8[];
extern u8 sD_843868BC[];
extern u8 sD_843868C0[];
extern u8 sD_843868C8[];
extern u8 sD_843868CC[];
extern u8 sD_843868D0[];
extern u8 sD_843868D4[];
extern u8 sD_843868D8[];
extern u8 sD_843868DC[];
extern u8 sD_843868E0[];
extern u8 sD_843868E4[];
extern u8 sD_843868E8[];
extern u8 sD_843868EC[];
extern u8 sD_843868F4[];
extern u8 sD_843868F8[];
extern u8 sD_843868FC[];
extern u8 sD_84386900[];
extern u8 sD_84386904[];
extern u8 sD_84386908[];
extern u8 sD_8438690C[];
extern u8 sD_84386910[];
extern u8 sD_84386914[];
extern u8 sD_84386918[];
extern u8 sD_84386920[];
extern u8 sD_84386924[];
extern u8 sD_84386928[];
extern u8 sD_8438692C[];
extern u8 sD_84386930[];
extern u8 sD_84386934[];
extern u8 sD_84386938[];
extern u8 sD_8438693C[];
extern u8 sD_84386940[];
extern u8 sD_84386944[];
extern u8 sD_84386948[];
extern u8 sD_8438694C[];
extern u8 sD_84386950[];
extern u8 sD_84386954[];
extern u8 sD_84386958[];
extern u8 sD_8438695C[];
extern u8 sD_84386960[];
extern u8 sD_84386964[];
extern u8 sD_84386968[];
extern u8 sD_84386970[];
extern u8 sD_84386974[];
extern u8 sD_84386978[];
extern u8 sD_8438697C[];
extern u8 sD_84386980[];
extern u8 sD_84386988[];
extern u8 sD_8438698C[];
extern u8 sD_84386990[];
extern u8 sD_84386994[];
extern u8 sD_8438699C[];
extern u8 sD_843869A0[];
extern u8 sD_843869A8[];
extern u8 sD_843869AC[];
extern u8 sD_843869B0[];
extern u8 sD_843869B4[];
extern u8 sD_843869B8[];
extern u8 sD_843869BC[];
extern u8 sD_843869C0[];
extern u8 sD_843869C4[];
extern u8 sD_843869C8[];
extern u8 sD_843869D0[];
extern u8 sD_843869D4[];
extern u8 sD_843869D8[];
extern u8 sD_843869DC[];
extern u8 sD_843869E0[];
extern u8 sD_843869E8[];
extern u8 sD_843869EC[];
extern u8 sD_843869F0[];
extern u8 sD_843869F8[];
extern u8 sD_843869FC[];
extern u8 sD_84386A00[];
extern u8 sD_84386A04[];
extern u8 sD_84386A08[];
extern u8 sD_84386A0C[];
extern u8 sD_84386A10[];
extern u8 sD_84386A14[];
extern u8 sD_84386A18[];
extern u8 sD_84386A1C[];
extern u8 sD_84386A20[];
extern u8 sD_84386A24[];
extern u8 sD_84386A28[];
extern u8 sD_84386A2C[];
extern u8 sD_84386A30[];
extern u8 sD_84386A38[];
extern u8 sD_84386A3C[];
extern u8 sD_84386A40[];
extern u8 sD_84386A44[];
extern u8 sD_84386A48[];
extern u8 sD_84386A4C[];
extern u8 sD_84386A50[];
extern u8 sD_84386A5C[];
extern u8 sD_84386A60[];
extern u8 sD_84386A64[];
extern u8 sD_84386A68[];
extern u8 sD_84386A6C[];
extern u8 sD_84386A70[];
extern u8 sD_84386A74[];
extern u8 sD_84386A78[];
extern u8 sD_84386A7C[];
extern u8 sD_84386A80[];
extern u8 sD_84386A84[];
extern u8 sD_84386A88[];
extern u8 sD_84386A8C[];
extern u8 sD_84386A90[];
extern u8 sD_84386A94[];
extern u8 sD_84386A98[];
extern u8 sD_84386A9C[];
extern u8 sD_84386AA0[];
extern u8 sD_84386AA4[];
extern u8 sD_84386AA8[];
extern u8 sD_84386AAC[];
extern u8 sD_84386AB0[];
extern u8 sD_84386AB4[];
extern u8 sD_84386AB8[];
extern u8 sD_84386ABC[];
extern u8 sD_84386AC0[];
extern u8 sD_84386AC4[];
extern u8 sD_84386AC8[];
extern u8 sD_84386ACC[];
extern u8 sD_84386AD0[];
extern u8 sD_84386AD4[];
extern u8 sD_84386AD8[];
extern u8 sD_84386ADC[];
extern u8 sD_84386AE0[];
extern u8 sD_84386AE4[];
extern u8 sD_84386AE8[];
extern u8 sD_84386AEC[];
extern u8 sD_84386AF0[];
extern u8 sD_84386AF4[];
extern u8 sD_84386AF8[];
extern u8 sD_84386AFC[];
extern u8 sD_84386B00[];
extern u8 sD_84386B04[];
extern u8 sD_84386B08[];
extern u8 sD_84386B0C[];
extern u8 sD_84386B10[];
extern u8 sD_84386B14[];
extern u8 sD_84386B18[];
extern u8 sD_84386B1C[];
extern u8 sD_84386B20[];
extern u8 sD_84386B24[];
extern u8 sD_84386B28[];
extern u8 sD_84386B2C[];
extern u8 sD_84386B30[];
extern u8 sD_84386B34[];
extern u8 sD_84386B38[];
extern u8 sD_84386B3C[];
extern u8 sD_84386B40[];
extern u8 sD_84386B44[];
extern u8 sD_84386B48[];
extern u8 sD_84386B4C[];
extern u8 sD_84386B50[];
extern u8 sD_84386B54[];
extern u8 sD_84386B58[];
extern u8 sD_84386B5C[];
extern u8 sD_84386B60[];
extern u8 sD_84386B64[];
extern u8 sD_84386B68[];
extern u8 sD_84386B6C[];
extern u8 sD_84386B70[];
extern u8 sD_84386B74[];
extern u8 sD_84386B78[];
extern u8 sD_84386B7C[];
extern u8 sD_84386B80[];
extern u8 sD_84386B84[];
extern u8 sD_84386B88[];
extern u8 sD_84386B8C[];
extern u8 sD_84386B90[];
extern u8 sD_84386B94[];
extern u8 sD_84386B98[];
extern u8 sD_84386B9C[];
extern u8 sD_84386BA0[];
extern u8 sD_84386BA4[];
extern u8 sD_84386BA8[];
extern u8 sD_84386BAC[];
extern u8 sD_84386BB0[];
extern u8 sD_84386BB4[];
extern u8 sD_84386BB8[];
extern u8 sD_84386BBC[];
extern u8 sD_84386BC4[];
extern u8 sD_84386BC8[];
extern u8 sD_84386BD0[];
extern u8 sD_84386BD4[];
extern u8 sD_84386BD8[];
extern u8 sD_84386BE0[];
extern u8 sD_84386BE4[];
extern u8 sD_84386BE8[];
extern u8 sD_84386BEC[];
extern u8 sD_84386BF0[];
extern u8 sD_84386C00[];
extern u8 sD_84386C04[];
extern u8 sD_84386C08[];
extern u8 sD_84386C0C[];
extern u8 sD_84386C10[];
extern u8 sD_84386C14[];
extern u8 sD_84386C18[];
extern u8 sD_84386C1C[];
extern u8 sD_84386C20[];
extern u8 sD_84386C24[];
extern u8 sD_84386C28[];
extern u8 sD_84386C34[];
extern u8 sD_84386C38[];
extern u8 sD_84386C3C[];
extern u8 sD_84386C40[];
extern u8 sD_84386C44[];
extern u8 sD_84386C48[];
extern u8 sD_84386C4C[];
extern u8 sD_84386C50[];
extern u8 sD_84386C54[];
extern u8 sD_84386C58[];
extern u8 sD_84386C5C[];
extern u8 sD_84386C64[];
extern u8 sD_84386C68[];
extern u8 sD_84386C6C[];
extern u8 sD_84386C70[];
extern u8 sD_84386C78[];
extern u8 sD_84386C7C[];
extern u8 sD_84386C80[];
extern u8 sD_84386C84[];
extern u8 sD_84386C88[];
extern u8 sD_84386C8C[];
extern u8 sD_84386C90[];
extern u8 sD_84386C94[];
extern u8 sD_84386C98[];
extern u8 sD_84386C9C[];
extern u8 sD_84386CA0[];
extern u8 sD_84386CA4[];
extern u8 sD_84386CA8[];
extern u8 sD_84386CAC[];
extern u8 sD_84386CB0[];
extern u8 sD_84386CB4[];
extern u8 sD_84386CB8[];
extern u8 sD_84386CBC[];
extern u8 sD_84386CC0[];
extern u8 sD_84386CC8[];
extern u8 sD_84386CCC[];
extern u8 sD_84386CD0[];
extern u8 sD_84386CD4[];
extern u8 sD_84386CD8[];
extern u8 sD_84386CDC[];
extern u8 sD_84386CE0[];
extern u8 sD_84386CE4[];
extern u8 sD_84386CE8[];
extern u8 sD_84386CEC[];
extern u8 sD_84386CF0[];
extern u8 sD_84386CF4[];
extern u8 sD_84386CF8[];
extern u8 sD_84386CFC[];
extern u8 sD_84386D00[];
extern u8 sD_84386D04[];
extern u8 sD_84386D08[];
extern u8 sD_84386D0C[];
extern u8 sD_84386D10[];
extern u8 sD_84386D14[];
extern u8 sD_84386D18[];
extern u8 sD_84386D1C[];
extern u8 sD_84386D24[];
extern u8 sD_84386D2C[];
extern u8 sD_84386D30[];
extern u8 sD_84386D34[];
extern u8 sD_84386D38[];
extern u8 sD_84386D3C[];
extern u8 sD_84386D40[];
extern u8* sD_84386D44[][2];
extern u8* sBattleAnimMode4StartEffectLists[];
extern u8* sD_84386DEC[];
extern u8* sBattleAnimMode9StartEffectLists[];
extern u8* sMoveAnimEffectScripts[][5];

#include "m2c_macros.h"

void func_82135100(void);
void func_821351EC(UNUSED s32 arg0, UNUSED s32 arg1);
void func_82136010(void);
void func_82136018(void);
void BattleAnim_RegisterEffectSlot(func_D_84390300 arg0, func_D_84390320 arg1);
void BattleAnim_SetQueuedEffectList(u8 effect_list_index);

void func_82135100(void) {
}

M2C_UNK func_80003824(M2C_UNK *, s8 *, s8 *, M2C_UNK); /* extern */
extern s8 D_00434C00;
extern u32 D_8218A2DC[];
extern u32 D_8218A544[];
/*
 * func_82135108
 *
 * Picks one of two model records by the participant's object type
 * (display object objectType - 1 indexes the two word tables D_8218A544 and
 * D_8218A2DC; the low 24 bits of each entry are an offset from D_00434C00)
 * and hands that record, together with the address 0x168 bytes after it, to
 * func_80003824 with the destination D_FLT_8219A5B0 and a final argument of 0.
 * The record from D_8218A2DC is used when the scene's unk_1C is 9; otherwise it
 * is used when BattleAnim_RandomRange(100) is below 0x33, and the record from
 * D_8218A544 when it is 0x33 or higher.  What func_80003824 does with the two
 * addresses (0x168 is the size of a DisplayObject) is not established here.
 * Note: the local pad arrays only reproduce the retail stack layout, and the
 * order of the two table lookups matches the register allocation.
 */
void func_82135108(ActivePokemon* arg0) {
    s16 temp_a2;
    UNUSED s32 padC[2];
    s8* temp_a1;
    UNUSED s32 padA[1];
    s8* sp18;

    temp_a2 = arg0->displayObject.objectType - 1;
    temp_a1 = (s8*)((D_8218A2DC[temp_a2] & 0xFFFFFF) + (u32)&D_00434C00);
    sp18 = (s8*)((D_8218A544[temp_a2] & 0xFFFFFF) + (u32)&D_00434C00);
    if (sBattleScene.scene->unk_1C == 9) {
        func_80003824(&D_FLT_8219A5B0, temp_a1, temp_a1 + 0x168, 0);
        return;
    }
    if (BattleAnim_RandomRange(0x64) >= 0x33) {
        func_80003824(&D_FLT_8219A5B0, sp18, sp18 + 0x168, 0);
        return;
    }
    func_80003824(&D_FLT_8219A5B0, temp_a1, temp_a1 + 0x168, 0);
}

void func_821351EC(UNUSED s32 arg0, UNUSED s32 arg1) {
}

#ifdef NON_MATCHING
/* TODO: decompile func_821351F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821351F8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82135384; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82135384.s")
#endif

extern f32 D_FLT_82189350[][4];
extern f32 D_FLT_82196810;

/*
 * func_82135458
 *
 * Same camera-target easing as func_82122FD8 (see func_82122A7C for the
 * step-by-step description) with the arguments in the opposite order (the
 * participant first, the camera second). It first copies the scene's saved eye
 * (+0xB4) into the camera's eye position, uses the bare object-type table width
 * (D_FLT_82189350[type][0]) as the distance threshold and eases the camera
 * target by D_FLT_82196810 times the remaining distance.
 */
void func_82135458(ActivePokemon* arg0, CameraNode* arg1) {
    u8* ptr = (u8*)&arg0->modelTransform;
    Vec3f sp58;
    Vec3f sp4C;
    UNUSED s32 pad[3];
    Vec3f sp34;
    f32 sp30;
    s16 sp2E;
    s16 sp2C;

    BattleAnim_Vec3fCopy(&arg1->view.eyePosition, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xB4));
    func_82121908(arg0, &sp58);
    BattleAnim_CalculateDistanceAngles(&sp58, &M2C_FIELD(arg0, Vec3f*, 0x5D0), &sp30, &sp2E, &sp2C);
    BattleAnim_Vec3fCopy(&sp34, &arg1->view.targetPosition);
    if (D_FLT_82189350[arg0->displayObject.objectType][0] <= sp30) {
        Camera_ComputeEyeFromAngles(&sp58, &sp4C, M2C_FIELD(ptr, f32*, 0x38), M2C_FIELD(ptr, s16*, 0x30), M2C_FIELD(ptr, s16*, 0x32));
        BattleAnim_CalculateDistanceAngles(&sp34, &sp4C, &sp30, &sp2E, &sp2C);
    } else {
        BattleAnim_CalculateDistanceAngles(&sp34, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xA8), &sp30, &sp2E, &sp2C);
    }
    Camera_ComputeEyeFromAngles(&sp34, &arg1->view.targetPosition, sp30 * D_FLT_82196810, sp2E, sp2C);
}

void func_82135384(ActivePokemon*, CameraNode*, Vec3f*, Vec3f*, s32, s32);

/*
 * func_8213558C
 *
 * Evaluates one step of the spline camera path. func_82135384 is called four
 * times to turn the keyframes arg4[arg5 + 0..3] into points relative to the
 * participant and camera (stored in a local array of four vectors); arg2 then
 * receives the weighted sum of those four points using the four weights in
 * arg3 (the weights come from func_8210C274 / func_8210C330 / func_8210C40C,
 * the Stadium 1 Battle_ComputeSplineWeights variants). Finally the scene's path
 * parameter (+0x04, f32) advances by 1 / (s8 at +0x00).
 *
 * func_82135CD8 has an identical body (it is the same step with a different
 * caller).
 */
void func_8213558C(ActivePokemon* arg0, CameraNode* arg1, Vec3f* arg2, f32* arg3, Vec3f* arg4, s32 arg5) {
    Vec3f sp28[4];

    func_82135384(arg0, arg1, arg4, sp28, arg5, 0);
    func_82135384(arg0, arg1, arg4, sp28, arg5, 1);
    func_82135384(arg0, arg1, arg4, sp28, arg5, 2);
    func_82135384(arg0, arg1, arg4, sp28, arg5, 3);
    arg2->x = (((arg3[0] * sp28[0].x) + (arg3[1] * sp28[1].x)) + (arg3[2] * sp28[2].x)) + (arg3[3] * sp28[3].x);
    arg2->y = (((arg3[0] * sp28[0].y) + (arg3[1] * sp28[1].y)) + (arg3[2] * sp28[2].y)) + (arg3[3] * sp28[3].y);
    arg2->z = (((arg3[0] * sp28[0].z) + (arg3[1] * sp28[1].z)) + (arg3[2] * sp28[2].z)) + (arg3[3] * sp28[3].z);
    M2C_FIELD(sBattleScene.scene, f32*, 4) += 1.0f / (f32)M2C_FIELD(sBattleScene.scene, s8*, 0);
}

/*
 * func_82135734
 *
 * Advances the spline camera path by one frame. Unless the participant is an
 * Onix (95) or object type 0x52, it first runs func_82135458 to ease the camera
 * target. The scene holds the current segment (s8 at +0x01), the parameter t
 * (f32 at +0x04) and the keyframe count (s8 at +0x08). Returns 1 without doing
 * anything else once segment + 3 reaches the keyframe count. Otherwise it picks
 * the weight formula for the segment (VariantB for segment 1, VariantC for
 * segment 2, VariantA for segment 3 and up), blends the keyframes in
 * D_FLT_8219A5B0 into the camera's eye position with func_8213558C, raises the
 * eye Y to at least 15, and moves to the next segment (resetting t) once t has
 * reached 1. Returns 0.
 */
s32 func_82135734(CameraNode* arg0, ActivePokemon* arg1) {
    f32 sp28[4];
    s16 temp_v0;
    s8 var_v1;

    temp_v0 = arg1->displayObject.objectType;
    if ((temp_v0 != 0x5F) && (temp_v0 != 0x52)) {
        func_82135458(arg1, arg0);
    }
    var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    if (M2C_FIELD(D_8219A5A0, s8*, 8) < (var_v1 + 3)) {
        return 1;
    }
    if (var_v1 == 1) {
        Battle_ComputeSplineWeightsVariantB(sp28, M2C_FIELD(D_8219A5A0, f32*, 4));
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    if (var_v1 == 2) {
        Battle_ComputeSplineWeightsVariantC(sp28, M2C_FIELD(D_8219A5A0, f32*, 4));
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    if (var_v1 >= 3) {
        Battle_ComputeSplineWeightsVariantA(sp28, M2C_FIELD(D_8219A5A0, f32*, 4));
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    func_8213558C(arg1, arg0, &arg0->view.eyePosition, sp28, (Vec3f*)&D_FLT_8219A5B0, var_v1 - 1);
    if (arg0->view.eyePosition.y < 15.0f) {
        arg0->view.eyePosition.y = 15.0f;
    }
    if ((f64)M2C_FIELD(D_8219A5A0, f32*, 4) >= 1.0) {
        M2C_FIELD(D_8219A5A0, s8*, 1) = (s8)(M2C_FIELD(D_8219A5A0, s8*, 1) + 1);
        M2C_FIELD(sBattleScene.scene, f32*, 4) = 0.0f;
    }
    return 0;
}

/*
 * func_82135894
 *
 * Advances the spline camera path by one frame (the variant used when the
 * target easing runs after the end-of-path test, paired with func_82135734).
 * The scene holds the current segment (s8 at +0x01), the parameter t (f32 at
 * +0x04) and the keyframe count (s8 at +0x08). Returns 1 immediately once
 * segment + 3 reaches the keyframe count. Otherwise, unless the participant is
 * an Onix (95) or object type 0x52, it runs func_82135458 to ease the camera
 * target. It then picks the weight formula for the segment (VariantB for
 * segment 1, VariantC for segment 2, VariantA for segment 3 and up), blends
 * the keyframes in D_FLT_8219A5B0 into the camera's eye position with
 * func_8213558C, raises the eye Y to at least 15, and moves to the next
 * segment (resetting t) once t has reached 1. Returns 0.
 */
s32 func_82135894(CameraNode* arg0, ActivePokemon* arg1) {
    f32 sp30[4];
    UNUSED s32 pad[2];
    s16 temp_a0;
    s8 var_v1;

    var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    if ((var_v1 + 3) >= M2C_FIELD(D_8219A5A0, s8*, 8)) {
        return 1;
    }
    temp_a0 = arg1->displayObject.objectType;
    if ((temp_a0 != 0x5F) && (temp_a0 != 0x52)) {
        func_82135458(arg1, arg0);
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    if (var_v1 == 1) {
        Battle_ComputeSplineWeightsVariantB(sp30, M2C_FIELD(D_8219A5A0, f32*, 4));
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    if (var_v1 == 2) {
        Battle_ComputeSplineWeightsVariantC(sp30, M2C_FIELD(D_8219A5A0, f32*, 4));
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    if (var_v1 >= 3) {
        Battle_ComputeSplineWeightsVariantA(sp30, M2C_FIELD(D_8219A5A0, f32*, 4));
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    func_8213558C(arg1, arg0, &arg0->view.eyePosition, sp30, (Vec3f*)&D_FLT_8219A5B0, var_v1 - 1);
    if (arg0->view.eyePosition.y < 15.0f) {
        arg0->view.eyePosition.y = 15.0f;
    }
    if ((f64)M2C_FIELD(D_8219A5A0, f32*, 4) >= 1.0) {
        M2C_FIELD(D_8219A5A0, s8*, 1) = (s8)(M2C_FIELD(D_8219A5A0, s8*, 1) + 1);
        M2C_FIELD(sBattleScene.scene, f32*, 4) = 0.0f;
    }
    return 0;
}

M2C_UNK func_80003824(M2C_UNK *, s8 *, s8 *, M2C_UNK); /* extern */
extern s8 D_00434C00;
extern s32 D_8218A2D4;
extern s8 D_FLT_8219A5B0;
void func_82135A04(s32 arg0) {
    s8 *temp_a1;

    temp_a1 = (D_8218A2D4 & 0xFFFFFF) + &D_00434C00;
    func_80003824(&D_FLT_8219A5B0, temp_a1, temp_a1 + 0x168, 0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_82135A54; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82135A54.s")
#endif

extern f32 D_FLT_82189350[][4];
extern f32 D_FLT_82196814;

/*
 * func_82135BE4
 *
 * Another variant of the camera-target easing in func_82122A7C (see there).
 * It measures the participant's anchor against the point at +0x5D0, rebuilds
 * the goal from the anchor and the model transform's distance and angles
 * (+0x38 / +0x30 / +0x32 within the transform) and measures the camera target
 * against that goal. Only when that distance is at least the object type's
 * table width (D_FLT_82189350[type][0]) does it ease the camera target towards
 * the goal, by D_FLT_82196814 times the remaining distance.
 */
void func_82135BE4(ActivePokemon* arg0, CameraNode* arg1) {
    u8* ptr = (u8*)&arg0->modelTransform;
    Vec3f sp58;
    Vec3f sp4C;
    UNUSED s32 pad[3];
    Vec3f sp34;
    f32 sp30;
    s16 sp2E;
    s16 sp2C;

    func_82121908(arg0, &sp58);
    BattleAnim_CalculateDistanceAngles(&sp58, &M2C_FIELD(arg0, Vec3f*, 0x5D0), &sp30, &sp2E, &sp2C);
    BattleAnim_Vec3fCopy(&sp34, &arg1->view.targetPosition);
    Camera_ComputeEyeFromAngles(&sp58, &sp4C, M2C_FIELD(ptr, f32*, 0x38), M2C_FIELD(ptr, s16*, 0x30), M2C_FIELD(ptr, s16*, 0x32));
    BattleAnim_CalculateDistanceAngles(&sp34, &sp4C, &sp30, &sp2E, &sp2C);
    if (D_FLT_82189350[arg0->displayObject.objectType][0] <= sp30) {
        Camera_ComputeEyeFromAngles(&sp34, &arg1->view.targetPosition, sp30 * D_FLT_82196814, sp2E, sp2C);
    }
}

void func_82135384(ActivePokemon*, CameraNode*, Vec3f*, Vec3f*, s32, s32);

/*
 * func_82135CD8
 *
 * Identical in code to func_8213558C (see there): evaluates one step of the
 * spline camera path from four keyframes and advances the scene's path
 * parameter by 1 / (s8 at +0x00). Called by func_82135E80.
 */
void func_82135CD8(ActivePokemon* arg0, CameraNode* arg1, Vec3f* arg2, f32* arg3, Vec3f* arg4, s32 arg5) {
    Vec3f sp28[4];

    func_82135384(arg0, arg1, arg4, sp28, arg5, 0);
    func_82135384(arg0, arg1, arg4, sp28, arg5, 1);
    func_82135384(arg0, arg1, arg4, sp28, arg5, 2);
    func_82135384(arg0, arg1, arg4, sp28, arg5, 3);
    arg2->x = (((arg3[0] * sp28[0].x) + (arg3[1] * sp28[1].x)) + (arg3[2] * sp28[2].x)) + (arg3[3] * sp28[3].x);
    arg2->y = (((arg3[0] * sp28[0].y) + (arg3[1] * sp28[1].y)) + (arg3[2] * sp28[2].y)) + (arg3[3] * sp28[3].y);
    arg2->z = (((arg3[0] * sp28[0].z) + (arg3[1] * sp28[1].z)) + (arg3[2] * sp28[2].z)) + (arg3[3] * sp28[3].z);
    M2C_FIELD(sBattleScene.scene, f32*, 4) += 1.0f / (f32)M2C_FIELD(sBattleScene.scene, s8*, 0);
}

/*
 * func_82135E80
 *
 * Advances the spline camera path by one frame using the func_82135BE4 /
 * func_82135CD8 pair (the counterpart of func_82135734). It always eases the
 * camera target with func_82135BE4 first. The scene holds the current segment
 * (s8 at +0x01), the parameter t (f32 at +0x04) and the keyframe count (s8 at
 * +0x08). Returns 1 without doing anything else once segment + 3 reaches the
 * keyframe count. Otherwise it picks the weight formula for the segment
 * (VariantB for segment 1, VariantC for segment 2, VariantA for segment 3 and
 * up), blends the keyframes in D_FLT_8219A5B0 into the camera's eye position
 * with func_82135CD8, raises the eye Y to at least 15, and moves to the next
 * segment (resetting t) once t has reached 1. Returns 0.
 */
s32 func_82135E80(CameraNode* arg0, ActivePokemon* arg1) {
    f32 sp30[4];
    s8 var_v1;

    func_82135BE4(arg1, arg0);
    var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    if (M2C_FIELD(D_8219A5A0, s8*, 8) < (var_v1 + 3)) {
        return 1;
    }
    if (var_v1 == 1) {
        Battle_ComputeSplineWeightsVariantB(sp30, M2C_FIELD(D_8219A5A0, f32*, 4));
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    if (var_v1 == 2) {
        Battle_ComputeSplineWeightsVariantC(sp30, M2C_FIELD(D_8219A5A0, f32*, 4));
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    if (var_v1 >= 3) {
        Battle_ComputeSplineWeightsVariantA(sp30, M2C_FIELD(D_8219A5A0, f32*, 4));
        var_v1 = M2C_FIELD(D_8219A5A0, s8*, 1);
    }
    func_82135CD8(arg1, arg0, &arg0->view.eyePosition, sp30, (Vec3f*)&D_FLT_8219A5B0, var_v1 - 1);
    if (arg0->view.eyePosition.y < 15.0f) {
        arg0->view.eyePosition.y = 15.0f;
    }
    if ((f64)M2C_FIELD(D_8219A5A0, f32*, 4) >= 1.0) {
        M2C_FIELD(D_8219A5A0, s8*, 1) = (s8)(M2C_FIELD(D_8219A5A0, s8*, 1) + 1);
        M2C_FIELD(sBattleScene.scene, f32*, 4) = 0.0f;
    }
    return 0;
}

M2C_UNK func_82136338();                            /* extern */
M2C_UNK func_82136E48();                            /* extern */
M2C_UNK func_8213A68C();                            /* extern */
M2C_UNK func_8213AE68();                            /* extern */
M2C_UNK func_8216D970();                            /* extern */

void func_82135FD0(s32 arg0) {
    func_82136E48();
    func_82136338();
    func_8213AE68();
    func_8213A68C();
    func_8216D970();
}

void func_82136010(void) {
}

void func_82136018(void) {
}

void BattleAnim_RunEffectInitStart(s16 arg0) {
    sMoveAnimEffectStartInitFuncs[arg0]();
    if (sBattleAnimAlternateAnchor != 0xFF) {
        gBattleAnimCurrentAnchor = sBattleAnimAlternateAnchor;
        sMoveAnimEffectStartInitFuncs[arg0]();
    }
}

extern func_D_84390320 D_8218EA6C[];

void BattleAnim_RunEffectInitEnd(s16 arg0) {
    D_8218EA6C[arg0]();
}

void BattleAnim_RegisterEffectSlot(func_D_84390300 arg0, func_D_84390320 arg1) {
    if (sBattleAnimEffectCallbackIndex >= 8) {
        sBattleAnimEffectCallbackIndex = 0;
    }

    if (gBattleAnimEffectUpdateFuncs[sBattleAnimEffectCallbackIndex]) {}

    gBattleAnimEffectUpdateFuncs[sBattleAnimEffectCallbackIndex] = arg0;
    gBattleAnimEffectDrawFuncs[sBattleAnimEffectCallbackIndex] = arg1;
    sBattleAnimEffectCallbackIndex++;
}


void func_82136430(u8);

extern u8* D_8218F154[];
extern u8* D_8218F198[];
extern func_D_84390320 D_821920B8[];
extern func_D_84390320 D_821924A0[];
extern func_D_84390320 D_82191CD0[];
extern u8* D_8218F184[];
extern func_D_84390320 D_821926F8[];
extern func_D_84390320 D_82191F28[];
extern func_D_84390320 D_82192310[];
void func_8213608C(s16 arg0);
void BattleAnim_RunEffectList(s32 arg0, s32 arg1, s32 arg2) {
    u8* sp2C;

    func_82136430(arg1);

    if (arg2 == 1) {
        switch (arg1) {
            case 0:
                sp2C = sMoveAnimEffectScripts[arg0][0];
                break;

            case 1:
                sp2C = sMoveAnimEffectScripts[arg0][1];
                break;

            case 3:
                sp2C = sD_84386D44[arg0][0];
                break;

            case 4:
                sp2C = D_8218F154[arg0];
                break;

            case 9:
                sp2C = D_8218F198[arg0];
                break;
        }

        while (*sp2C != 0) {
            BattleAnim_RunEffectInitStart(*sp2C);
            D_82191CD0[*sp2C]();
            BattleAnim_RegisterEffectSlot(D_821920B8[*sp2C], D_821924A0[*sp2C]);
            sp2C++;
        }
    } else {
        switch (arg1) {
            case 2:
                sp2C = sMoveAnimEffectScripts[arg0][2];
                break;

            case 6:
                sp2C = D_8218F184[arg0];
                break;
        }

        while (*sp2C != 0) {
            func_8213608C(*sp2C);
            D_82191F28[*sp2C]();
            BattleAnim_RegisterEffectSlot(D_82192310[*sp2C], D_821926F8[*sp2C]);
            sp2C++;
        }
    }
}

extern s16 D_8219A80A;
extern s16 D_8219A80C;

void BattleAnim_ProcessQueuedEffects(void) {
    if (sBattleAnimQueuedEffectListMode != BATTLE_ANIMATION_QUEUE_INACTIVE) {
        BattleAnim_ResetSpawnDelayAlias();
        D_8219A80A = D_8219A80C;
        BattleAnim_RunEffectList(sBattleAnimQueuedMoveId, sBattleAnimQueuedEffectList, sBattleAnimQueuedEffectListMode);
        sBattleAnimQueuedEffectListMode = BATTLE_ANIMATION_QUEUE_INACTIVE;
    }

    if (sBattleAnimQueuedAlternatePending != 0) {
        BattleAnim_RunEffectList(sBattleAnimQueuedAlternateMoveId, sBattleAnimQueuedAlternateList, sBattleAnimQueuedAlternatePending);
        sBattleAnimQueuedAlternatePending = 0;
    }

    if (sBattleAnimQueuedExtraPending != 0) {
        BattleAnim_RunEffectList(sBattleAnimQueuedExtraMoveId, sBattleAnimQueuedExtraList, sBattleAnimQueuedExtraPending);
        sBattleAnimQueuedExtraPending = 0;
    }

    if (sBattleAnimQueuedResourceListPending != 0) {
        BattleAnim_RunEffectList(sBattleAnimQueuedResourceListId, 4, sBattleAnimQueuedResourceListPending);
        sBattleAnimQueuedResourceListPending = 0;
    }
}

void BattleAnim_SetQueuedEffectList(u8 effect_list_index) {
    sBattleAnimQueuedEffectList = effect_list_index;
}

extern s8 D_8219A808;
void func_82136430(u8 arg0)
{
  D_8219A808 = arg0;
}
