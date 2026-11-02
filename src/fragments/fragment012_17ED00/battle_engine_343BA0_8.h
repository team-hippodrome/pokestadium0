#ifndef ZERO_BATTLE_ENGINE_343BA0_8_H
#define ZERO_BATTLE_ENGINE_343BA0_8_H

/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_343BA0.c. */

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

void BattleAnim_StartEffect98Radial20_Init(void);
s32 BattleAnim_StartEffect98Radial20_Update(void);
void BattleAnim_StartEffect98Radial20_Draw(void);
void BattleAnim_StartEffect11Trail50Alt_Init(void);
s32 BattleAnim_StartEffect11Trail50Alt_Update(void);
void BattleAnim_StartEffect11Trail50Alt_Draw(void);
void BattleAnim_StartEffect57Trail50_Init(void);
s32 BattleAnim_StartEffect57Trail50_Update(void);
void BattleAnim_StartEffect57Trail50_Draw(void);
void BattleAnim_StartEffect42Trail40_Init(void);
s32 BattleAnim_StartEffect42Trail40_Update(void);
void BattleAnim_StartEffect42Trail40_Draw(void);
void BattleAnim_StartEffect43Trail40Variant_Init(void);
s32 BattleAnim_StartEffect43Trail40Variant_Update(void);
void BattleAnim_StartEffect43Trail40Variant_Draw(void);
void BattleAnim_StartEffect44Trail40GridAlt_Init(void);
s32 BattleAnim_StartEffect44Trail40GridAlt_Update(void);
void BattleAnim_StartEffect44Trail40GridAlt_Draw(void);
void BattleAnim_StartEffect45FourStreamTrail_Init(void);
void BattleAnim_StartEffect45FourStreamTrail_Draw(void);
void BattleAnim_StartEffect62OwnerLinkedFourStream_Init(void);
s32 BattleAnim_StartEffect62OwnerLinkedFourStream_Update(void);
void BattleAnim_StartEffect62OwnerLinkedFourStream_Draw(void);
void BattleAnim_StartEffect67OwnerAnchoredFourStream_Init(void);
s32 BattleAnim_StartEffect67OwnerAnchoredFourStream_Update(void);
void BattleAnim_StartEffect67OwnerAnchoredFourStream_Draw(void);
void BattleAnim_StartEffect78Radial20_Init(void);
s32 BattleAnim_StartEffect78Radial20_Update(void);
void BattleAnim_StartEffect78Radial20_Draw(void);
void BattleAnim_StartEffect26DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect26DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect26DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect26DoubleTextureTrail_Draw(void);
void BattleAnim_StartEffect47SixSlotTrail_Seed(void);
void BattleAnim_StartEffect47SixSlotTrail_Init(void);
s32 BattleAnim_StartEffect47SixSlotTrail_Update(void);
void BattleAnim_StartEffect47SixSlotTrail_Draw(void);
void BattleAnim_StartEffect4DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect4DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect4DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect4DoubleTextureTrail_Draw(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect77DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Draw(void);
void BattleAnim_StartEffect70DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect70DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect70DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect70DoubleTextureTrail_Draw(void);
void BattleAnim_StartEffect39DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect39SixSlotTrail_Seed(void);
void BattleAnim_StartEffect39CombinedTrail_Init(void);
s32 BattleAnim_StartEffect39CombinedTrail_Update(void);
void BattleAnim_StartEffect39CombinedTrail_Draw(void);

void BattleAnim_EffectSecondaryOwnerAnchorPosition(Vec3f* arg0);
f32 BattleAnim_EffectSecondaryOwnerModelScale(void);
void BattleAnim_CalcVectorAtToDm(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void BattleAnim_ResetSharedEffectMatrix(void);
void BattleAnim_StartEffect98Radial20_EmitVariantD(void);
void BattleAnim_StartEffect78Radial20_EmitVariantA(void);

/*
 * func_8216F3A0
 *
 * Per-frame update of the "four stream trail" part of effect 45: counts
 * frames in D_8219CAC0 (returns -1, which ends the effect, from frame 0x32
 * on).  During the first four frames (counter < 4) it starts one trail at the
 * secondary owner's bone position: the trail leaves in a direction in the
 * Y/Z plane given by an angle of (counter % 3) * pi / 3 + pi/6 (the sine and
 * cosine of that angle, normalised together with a 1.0 X component and
 * then scaled by 20), at X speed +-10 (negative when the start X is
 * negative), with colour 0xC0FFFF, alpha 0x80, a random +-0.3 drift and
 * fixed shape parameters 2.0, 13.0 and 0x28.  From frame 2 on it returns
 * whether the trail has completed (FourStreamTrail_IsComplete), else 0.
 *
 * Same code as BattleAnim_StartEffect45FourStreamTrail_Update in the Stadium
 * 1 decomp.  pi (D_FLT_82197934), pi/6 as a double (D_DBL_82197938) and 0.3
 * (D_DBL_82197940) are read from the retail rodata because this file's own
 * rodata is not placed; the names of the values are inferred from their use
 * and the donor source's M_PI_F, 0.5235987901687622 and 0.3.
 */
extern f32 D_FLT_82197934;
extern f64 D_DBL_82197938;
extern f64 D_DBL_82197940;

s32 func_8216F3A0(void);

extern const f32 D_FLT_82197948;
extern const f32 D_FLT_8219794C;
extern const f32 D_FLT_82197950;

extern const f32 D_FLT_82197954;

extern const f32 D_FLT_82197958;

extern const f32 D_FLT_8219795C;
extern const f32 D_FLT_82197960;

extern const f32 D_FLT_82197974;
extern const f32 D_FLT_82197964;
extern const f32 D_FLT_82197968;
extern const f32 D_FLT_8219796C;
extern const f32 D_FLT_82197970;

extern const f32 D_FLT_82197978;
extern const f32 D_FLT_8219797C;

extern const f32 D_FLT_82197980;
extern const f32 D_FLT_82197984;

extern const f32 D_FLT_82197988;

extern const f32 D_FLT_8219798C;
extern const f32 D_FLT_82197990;

#endif
