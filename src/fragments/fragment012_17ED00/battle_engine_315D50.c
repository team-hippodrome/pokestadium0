/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_315D50.c. */

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

void BattleAnim_PlaySoundEffect1(void);
void BattleAnim_PlaySoundEffect2(void);
void BattleAnim_PlaySoundEffect3(void);

void BattleAnim_PlaySoundEffect1(void) {
    Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
}

void BattleAnim_PlaySoundEffect2(void) {
    Audio_PlaySoundEffectById(SFX_MENU_CONFIRM);
}

void BattleAnim_PlaySoundEffect3(void) {
    Audio_PlaySoundEffectById(SFX_MENU_BACK);
}

/*
 * func_82134DA0
 *
 * Calls Audio_PlayCommand(5, arg1, arg1).  The first argument (a 16-bit
 * value) is accepted but never used; the second argument is passed both as
 * the command parameter and in the third (unused) slot.  The meaning of
 * command 5 is not determined here.
 */
void func_82134DA0(s16 arg0, s32 arg1) {
    Audio_PlayCommand(5, arg1, arg1);
}

M2C_UNK func_80041374(M2C_UNK, s32);                /* extern */

void func_82134DC8(s32 arg0) {
    func_80041374(5, arg0);
}

/*
 * func_82134DEC
 *
 * Calls func_8003F96C(arg0, 2) with arg0 taken as a signed 16-bit value
 * (sign-extended before the call).  The `* 1` is there on purpose: it makes
 * IDO emit the separate shift pair (sll 16 / sra 16) the retail code has
 * instead of folding it into the argument register.
 */
void func_8003F96C(s32, s32);
void func_82134DEC(s16 arg0) {
    func_8003F96C(arg0 * 1, 2);
}

extern f32 D_FLT_82189360[][4];

void func_82134E18(ActivePokemon* active_pokemon) {
    s16 idx = active_pokemon->displayObject.objectType - 1;
    f32 height = D_FLT_82189360[idx][0];

    if (height >= 25.0f) {
        Audio_PlayCommand(6, 0, 0);
    } else if (height >= 12.5f) {
        Audio_PlayCommand(7, 0, 0);
    } else {
        Audio_PlayCommand(8, 0, 0);
    }
}

void BattleAnim_PlayBattleSequenceById(ActivePokemon* active_pokemon, s32 sequence_id) {
    s16 species = active_pokemon->displayObject.objectType;

    if (sequence_id == 0x14) {
        Audio_PlayCommand(0x14, 0, 0);
    } else if (sequence_id == 0x12) {
        Audio_PlayCommand(0x12, 0, 0);
    } else if (sequence_id == 0x32) {
        Audio_PlayCommand(0x32, species, 0);
    } else if (sequence_id == 0x21) {
        Audio_PlayCommand(0x21, 0, 0);
    } else if (sequence_id == 0x13) {
        Audio_PlayCommand(0x13, 0, 0);
    } else if (sequence_id == 0x1E) {
        Audio_PlayCommand(0x1E, 0, 0);
    } else if (sequence_id == 0x1F) {
        Audio_PlayCommand(0x1F, 0, 0);
    } else if (sequence_id == 0x20) {
        Audio_PlayCommand(0x20, 0, 0);
    }
}

M2C_UNK func_80041940();
void func_80042508(s32);
s32 func_82107A5C(s8*);
/*
 * func_82134FD0
 *
 * Takes the active Pokemon's roster entry (teamRoster->pokemonPicked indexed
 * by state.rosterIndex) and calls func_80041940 with the side index of the
 * Pokemon (func_82107A5C), the entry's hp and its unk_26.  Unless the display
 * object's objectType is 0x98, it then calls func_80042508 with the side index,
 * OR-ed with 0x10 when the entry's status byte has a sleep bit (mask 0x07) or
 * the freeze bit (0x20) set, or when the scene's unk_48 is 0x1F or 0x1B.
 * Related to func_82135098, which makes the func_80041940 call alone.
 * Notes: func_80041940 is declared without a prototype because this function
 * passes three arguments while func_82135098 passes four; the unused "pad"
 * local only reproduces the retail stack slot of "mon" (0x18).  What
 * func_80041940/func_80042508 do is not established here (they look like
 * audio calls, but that is a guess).
 */
void func_82134FD0(ActivePokemon* arg0) {
    UNUSED s32 pad;
    BattleMon* mon = &arg0->teamRoster->pokemonPicked[arg0->state.rosterIndex];

    func_80041940(func_82107A5C(arg0), mon->hp, mon->unk_26);
    if (arg0->displayObject.objectType != 0x98) {
        if ((mon->statusCondition & 7) || (mon->statusCondition & 0x20) ||
            (sBattleScene.scene->unk_48 == 0x1F) || (sBattleScene.scene->unk_48 == 0x1B)) {
            func_80042508(func_82107A5C(arg0) | 0x10);
        } else {
            func_80042508(func_82107A5C(arg0));
        }
    }
}

s32 func_82107A5C(s8 *);                          /* extern */
void func_82135098(s8 *arg0)
{
  s8 *sp18;
  s8 *temp_v1;
  temp_v1 = (((*((s32 *) (((s8 *) arg0) + 0x794))) * 0x50) + (*((s32 *) (((s8 *) arg0) + 0x860)))) + 0x1C;
  if ((*((s16 *) (((s8 *) arg0) + 0x1A))) != 0x98)
  {
    sp18 = temp_v1;
    func_80041940(func_82107A5C(arg0), *((u16 *) (((s8 *) arg0) + 0x7D2)), *((u16 *) (((s8 *) temp_v1) + 0x26)), arg0);
  }
}
