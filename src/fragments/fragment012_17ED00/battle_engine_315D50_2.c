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
#include "fragments/fragment012_17ED00/battle_engine_315D50_types.h"
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

u8 BattleAnim_GetCurrentEffectList(void);
void BattleAnim_SetQueuedResourceListId(u8 arg0);
u8 BattleAnim_GetQueuedResourceListId(void);
s16 BattleAnim_GetQueuedMoveId(void);
void BattleAnim_QueueMoveEffectScript(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor);
void BattleAnim_QueueMoveEffectEnd(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor);
void BattleAnim_QueueChargingMoveEffectScript(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor);
void BattleAnim_QueueEffectList3(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternative_anchor);
void BattleAnim_QueueEffectList6(s32 move_id, ActivePokemon* owner);
void BattleAnim_QueueEffectList5(s32 arg0, ActivePokemon* arg1);
void BattleAnim_QueueEffectList6Alt(s32 arg0, ActivePokemon* arg1);
void BattleAnim_StopOwnerCategoryParticles(u8 category, ActivePokemon* owner);
void BattleAnim_RegisterAssetTable(arg1_func_80019420* arg0);
void BattleAnim_ResetAssetTable(void);
void BattleAnim_BuildResourceListForMove(s16 arg0);
void BattleAnim_LoadMoveResourceList(BattleSessionTeams* battle_session_teams, s16 move_id);
void BattleAnim_LoadModeResourceList(BattleSessionTeams* battle_session_teams, s16 mode);
void BattleAnim_RegisterAllAssetTables(void);
void BattleAnim_RegisterAssetTablesForSession(BattleSessionTeams* battle_session_teams);
void BattleAnim_ResetDisplayContexts(void);
Particle* BattleAnim_GetOwnerContextParticle(DisplayObject* arg0);
DisplayObject* BattleAnim_AllocOwnerDisplayContext(Particle* arg0);
void BattleAnim_FreeOwnerDisplayContext(DisplayObject* arg0);
DisplayObject* BattleAnim_AllocParticleDisplayContext(Particle* arg0);
void BattleAnim_FreeParticleDisplayContext(DisplayObject* arg0);
void BattleAnim_InitModelWithAnim(DisplayObject* arg0, s16 arg1, s16 arg2);
void BattleAnim_SetModelAnimFrame(DisplayObject* arg0, s16 arg1);
void BattleAnim_InitModel(DisplayObject* arg0, s16 arg1);
void BattleAnim_BindModelAnim(DisplayObject* arg0, s16 arg1);
void BattleAnim_BindModelAnimReversed(DisplayObject* arg0, s16 arg1);
s32 BattleAnim_IsModelAnimComplete(DisplayObject* arg0);
void BattleAnim_UpdateEffectCallbacks(UNUSED CameraNode* arg0);
void BattleAnim_DrawEffectCallbacks(UNUSED CameraNode* arg0);

void BattleAnim_SetQueuedEffectList(u8 effect_list_index);
void BattleAnim_QueueMoveEffect(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4);

u8 BattleAnim_GetCurrentEffectList(void) {
    return sBattleAnimCurrentEffectList;
}

void BattleAnim_SetQueuedResourceListId(u8 arg0) {
    sBattleAnimQueuedResourceListId = arg0;
}

u8 BattleAnim_GetQueuedResourceListId(void) {
    return sBattleAnimQueuedResourceListId;
}

s16 BattleAnim_GetQueuedMoveId(void) {
    return sBattleAnimQueuedMoveId;
}

M2C_UNK func_8213641C(M2C_UNK);                     /* extern */
extern s32 D_8219A7CC;
extern s32 D_8219A7D4;
extern s32 D_8219A7D8;
extern s16 D_8219A80C;
extern s16 D_8219A80E;
extern s32 D_8219A810;
extern s32 D_8219A814;
extern s32 D_8219A818;

void BattleAnim_QueueMoveEffect(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4) {
    D_8219A7D8 = 1;
    D_8219A7D4 = arg0;
    D_8219A7CC = 0;
    func_8213641C(0);
    D_8219A80C = arg3;
    D_8219A80E = arg4;
    D_8219A810 = arg1;
    D_8219A814 = arg1;
    D_8219A818 = arg2;
}

void BattleAnim_QueueMoveEffectScript(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor) {
    BattleAnim_QueueMoveEffect(move_id, user, user_fallback, default_anchor, alternate_anchor);
}

void BattleAnim_QueueMoveEffectEnd(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor) {
    BattleAnim_QueueMoveEffect(move_id, user, user_fallback, default_anchor, alternate_anchor);
    BattleAnim_SetQueuedEffectList(2);
    gBattleAnimCurrentOwner = user_fallback;
    sBattleAnimQueuedEffectListMode = BATTLE_ANIMATION_QUEUE_END;
}

void BattleAnim_QueueChargingMoveEffectScript(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor) {
    BattleAnim_QueueMoveEffect(move_id, user, user_fallback, default_anchor, alternate_anchor);
    BattleAnim_SetQueuedEffectList(1);
}

void BattleAnim_QueueEffectList3(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternative_anchor) {
    BattleAnim_QueueMoveEffect(move_id, user, user_fallback, default_anchor, alternative_anchor);
    BattleAnim_SetQueuedEffectList(3);
}

void BattleAnim_QueueEffectList6(s32 move_id, ActivePokemon* owner) {
    sBattleAnimQueuedAlternatePending = 2;
    sBattleAnimQueuedAlternateMoveId = move_id;
    sBattleAnimQueuedAlternateList = 6;
    gBattleAnimDefaultAnchor = 0xFF;
    sBattleAnimAlternateAnchor = 0xFF;
    gBattleAnimCurrentOwner = owner;
    gBattleAnimSecondaryOwner = owner;
    gBattleAnimTertiaryOwner = owner;
}

void BattleAnim_QueueEffectList5(s32 arg0, ActivePokemon* arg1) {
    BattleAnim_QueueEffectList6(arg0, arg1);
    sBattleAnimQueuedAlternatePending = 1;
    sBattleAnimQueuedAlternateList = 5;
}

void BattleAnim_QueueEffectList6Alt(s32 arg0, ActivePokemon* arg1) {
    BattleAnim_QueueEffectList6(arg0, arg1);
}

extern s32 D_8219A7FC;
extern s32 D_8219A800;
extern s32 D_8219A804;

/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_QueueEffectList9(s32 arg0) {
    D_8219A7FC = 1;
    D_8219A804 = 9;
    D_8219A800 = arg0;
}

M2C_UNK func_8213644C(u8);                          /* extern */
extern s32 D_8219A7E8;
extern s16 D_8219A80C;
extern s32 D_8219A810;

void BattleAnim_QueueEffectList(u8 arg0, s32 arg1) {
    D_8219A7E8 = 1;
    func_8213644C(arg0);
    D_8219A810 = arg1;
    if (arg0 == 3) {
        D_8219A80C = 7;
    }
}

void BattleAnim_StopOwnerCategoryParticles(u8 category, ActivePokemon* owner) {
    BattleAnim_StopParticlesForOwnerCategory(category, owner);
}

M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213C220(M2C_UNK, M2C_UNK);            /* extern */

void func_8213672C(void) {
    func_8213C220(0x80, 1);
    func_8213B644(0, 0x20, 8);
}

M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */

void func_82136760(void) {
    func_8213B644(0, 0x20, 8);
}

void BattleAnim_RegisterAssetTable(arg1_func_80019420* arg0) {
    if (arg0 != NULL) {
        do {
            if (arg0->unk_02 != 0) {
                sBattleAnimAssetPointers[arg0->unk_02] = arg0->unk_04;
                arg0++;
            }
        } while (arg0->unk_00 != 0);
    }
}

void BattleAnim_ResetAssetTable(void) {
    s32 i;

    // clang-format off
    for (i = 0; i < 256; i++) { sBattleAnimAssetPointers[i] = NULL; }
    // clang-format on

    BattleAnim_RegisterAssetTable(BattleAnim_LoadResourceTable(0));
}

void BattleAnim_BuildResourceListForMove(s16 arg0) {
    s32 var_v0 = 0;
    u8* temp_a1 = sMoveAnimEffectScripts[arg0][3];

    while (*temp_a1 != 0x3F) {
        sBattleAnimResourceList[var_v0] = *temp_a1;
        temp_a1++;
        var_v0++;
    }

    temp_a1 = sMoveAnimEffectScripts[arg0][4];
    while (*temp_a1 != 0x3F) {
        sBattleAnimResourceList[var_v0] = *temp_a1;
        temp_a1++;
        var_v0++;
    }

    sBattleAnimResourceList[var_v0] = -1;
}

void BattleAnim_LoadMoveResourceList(BattleSessionTeams* battle_session_teams, s16 move_id) {
    if (move_id != 0xFF) {
        BattleAnim_BuildResourceListForMove(move_id);
        battle_session_teams->assetIsBusy |= 0x80;
        battle_session_teams->unk_20 = sBattleAnimResourceList;
        battle_session_teams->unk_24 = sBattleAnimResourceTablePointers;
    }
}

void BattleAnim_LoadModeResourceList(BattleSessionTeams* battle_session_teams, s16 mode) {
    s32 index = 0;
    u8* var_v1 = sD_84386D44[mode][1];

    while (*var_v1 != 0x3F) {
        sBattleAnimResourceList[index] = *var_v1;
        var_v1++;
        index++;
    }

    sBattleAnimResourceList[index] = -1;
    battle_session_teams->unk_20 = sBattleAnimResourceList;
    battle_session_teams->assetIsBusy |= 0x80;
    battle_session_teams->unk_24 = sBattleAnimResourceTablePointers;
}

void BattleAnim_RegisterAllAssetTables(void) {
    s32 i = 0;
    arg1_func_80019420* var_v0;
    arg1_func_80019420** var_s1 = sBattleAnimResourceTablePointers;

    while (*var_s1 != NULL) {
        var_v0 = *var_s1;
        if (i) {}  // karodo
        BattleAnim_RegisterAssetTable(var_v0);
        var_s1++;
        i++;
    }
}

void BattleAnim_RegisterAssetTablesForSession(BattleSessionTeams* battle_session_teams) {
    battle_session_teams->assetIsBusy &= ~0x10;
    BattleAnim_RegisterAllAssetTables();
}

void BattleAnim_ResetDisplayContexts(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        ModelRenderer_AttachDisplayObject(&sD_843903D0[i]);
        sD_84391A50[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        ModelRenderer_AttachSecondaryDisplayObject(&sD_84391A90[i]);
        sD_84392030[i] = 0;
    }
}

Particle* BattleAnim_GetOwnerContextParticle(DisplayObject* arg0) {
    return arg0->node.callbackArg;
}

DisplayObject* BattleAnim_AllocOwnerDisplayContext(Particle* arg0) {
    s32 i;
    s32 var_v0 = -1;
    DisplayObject* temp_a0;

    for (i = 0; i < 16; i++) {
        if (sD_84391A50[i] == 0) {
            var_v0 = i;
            break;
        }
    }

    if (var_v0 >= 0) {
        temp_a0 = &sD_843903D0[var_v0];
        sD_84391A50[var_v0] = 1;
        temp_a0->node.callbackArg = arg0;
    } else {
        temp_a0 = NULL;
    }
    return temp_a0;
}

void BattleAnim_FreeOwnerDisplayContext(DisplayObject* arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg0 == &sD_843903D0[i]) {
            break;
        }
    }

    if (i != 16) {
        sD_84391A50[i] = 0;
        ModelRenderer_ClearDisplayObject(arg0);
    }
}

DisplayObject* BattleAnim_AllocParticleDisplayContext(Particle* arg0) {
    s32 i;
    s32 var_a2 = -1;
    DisplayObject* sp1C;

    for (i = 0; i < 4; i++) {
        if (sD_84392030[i] == 0) {
            var_a2 = i;
            break;
        }
    }

    if (var_a2 >= 0) {
        sp1C = &sD_84391A90[var_a2];
        sD_84392030[var_a2] = 1;
        Particle_SetFlags(arg0, 0x400);
        sp1C->node.callbackArg = arg0;
    } else {
        sp1C = NULL;
    }
    return sp1C;
}

void BattleAnim_FreeParticleDisplayContext(DisplayObject* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0 == &sD_84391A90[i]) {
            break;
        }
    }

    if (i != 4) {
        sD_84392030[i] = 0;
        ModelRenderer_ClearDisplayObject(arg0);
    }
}

void BattleAnim_InitModelWithAnim(DisplayObject* arg0, s16 arg1, s16 arg2) {
    Model_InitDisplayObject(arg0, 0, 0, sBattleAnimAssetPointers[arg1]);
    ModelAnim_BindTransformCurve(arg0, 0, sBattleAnimAssetPointers[arg2], 0x10000);
}

void BattleAnim_SetModelAnimFrame(DisplayObject* arg0, s16 arg1) {
    ModelAnim_SetFrame(arg0, arg1);
}

void BattleAnim_InitModel(DisplayObject* arg0, s16 arg1) {
    Model_InitDisplayObject(arg0, 0, 0, sBattleAnimAssetPointers[arg1]);
}

void BattleAnim_BindModelAnim(DisplayObject* arg0, s16 arg1) {
    ModelAnim_BindTransformCurve(arg0, 0, sBattleAnimAssetPointers[arg1], 0x10000);
}

void BattleAnim_BindModelAnimReversed(DisplayObject* arg0, s16 arg1) {
    ModelAnim_BindTransformCurve(arg0, 0, sBattleAnimAssetPointers[arg1], -0x10000);
    ModelAnim_SetFrame(arg0, arg0->transformAnim.data->endFrame - 1);
}

s32 BattleAnim_IsModelAnimComplete(DisplayObject* arg0) {
    s32 ret = 0;

    if (arg0->transformAnim.frameFixed == 0) {
        ret = 1;
    }
    return ret;
}

extern s32 D_8219A77C;
extern s32 D_8219A780;
extern s32 D_8219A784;
extern s32 D_8219A788;
extern s32 D_8219A78C;
extern s32 D_8219A790;
extern s32 D_8219A794;
extern s32 D_8219A798;
extern s32 D_8219A79C;
extern s32 D_8219A7A0;
extern s32 D_8219A7A4;
extern s32 D_8219A7A8;
extern s32 D_8219A7AC;
extern s32 D_8219A7B0;
extern s32 D_8219A7B4;
extern s32 D_8219A7B8;
extern s32 D_8219A7BC;
extern s32 D_8219A7C0;
extern s32 D_8219A7C4;
extern s32 D_8219A7C8;

void func_82136E48(void) {
    D_8219A780++;
    D_8219A77C--;
    if (D_8219A77C <= 0) {
        D_8219A77C = 0;
    }
    D_8219A784 = D_8219A780 & 0x3F;
    D_8219A788 = D_8219A780 & 0x1F;
    D_8219A78C = D_8219A780 & 0xF;
    D_8219A790 = D_8219A780 & 7;
    D_8219A794 = D_8219A780 & 3;
    D_8219A798 = D_8219A780 & 1;
    if (D_8219A784 == 0) {
        D_8219A79C++;
        D_8219A7B4 ^= 1;
    }
    if (D_8219A788 == 0) {
        D_8219A7A0++;
        D_8219A7B8 ^= 1;
    }
    if (D_8219A78C == 0) {
        D_8219A7A4++;
        D_8219A7BC ^= 1;
    }
    if (D_8219A790 == 0) {
        D_8219A7A8++;
        D_8219A7C0 ^= 1;
    }
    if (D_8219A794 == 0) {
        D_8219A7AC++;
        D_8219A7C4 ^= 1;
    }
    if (D_8219A798 == 0) {
        D_8219A7B0++;
        D_8219A7C8 ^= 1;
    }
}

void BattleAnim_UpdateEffectCallbacks(UNUSED CameraNode* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if ((gBattleAnimEffectUpdateFuncs[i] != NULL) && (gBattleAnimEffectUpdateFuncs[i]() != 0)) {
            gBattleAnimEffectUpdateFuncs[i] = NULL;
            gBattleAnimEffectDrawFuncs[i] = 0;
        }
    }
}

void BattleAnim_DrawEffectCallbacks(UNUSED CameraNode* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gBattleAnimEffectDrawFuncs[i] != NULL) {
            gBattleAnimEffectDrawFuncs[i]();
        }
    }
}

M2C_UNK func_82135FD0(s32);                         /* extern */
M2C_UNK func_82137000(s32);                         /* extern */
M2C_UNK func_82137160();                            /* extern */
M2C_UNK func_8216D720(s32);                         /* extern */
extern s32 D_8219A878;
s32 func_821370DC(u32 arg0, s32 arg1) {
    switch (arg0) {
    case 1:
    case 3:
    case 4:
        break;
    case 0:
        func_82137160();
        break;
    case 2:
        D_8219A878 = arg1;
        func_82135FD0(arg1);
        func_82137000(arg1);
        break;
    case 5:
        func_8216D720(arg1);
        break;
    }
    return 0;
}
