#ifndef ZERO_BATTLE_ENGINE_3438B0_H
#define ZERO_BATTLE_ENGINE_3438B0_H

/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3438B0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gfx_buffer.h"

#include "m2c_macros.h"

void BattleMessage_ShowForSide(s32, s32);
extern s32 D_8219A520;

void BattleAnim_RenderNop1(void);
void BattleAnim_RenderNop2(void);

extern ActivePokemon* D_8219A540;
extern s32 D_8219A544;
extern s32 D_8219A560;
extern s32 D_8219A564;
extern s32 D_8219A570;
extern s32 D_8219A578;
extern u8* D_82189180[];
typedef struct Cue8212B270 {
    /* 0x00 */ u8 unk_00[6];
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07[3];
    /* 0x0A */ u8 unk_0A;
} Cue8212B270; // size = 0xB
s32 func_82107A5C(ActivePokemon*);
void func_8212A554(void*);
void func_82124A40(void);
void func_82121EB0(ActivePokemon*);
void func_82104C68(ActivePokemon*, s32);
void func_8212A768(ActivePokemon*, CameraNode*, void*);
void func_82124E80(void);
void func_82135098(ActivePokemon*);
void BattleCamera_CaptureModelOrbit(ActivePokemon*, CameraNode*);
s32 func_82122DFC(CameraNode*, ActivePokemon*);
void ActivePokemon_CommitPendingStatus(ActivePokemon*);
void func_8212A4A4(s32);
void func_821061A8(ActivePokemon*);
void Audio_FadeAndClearStoredSounds(void);
s32 Battle_StepPartyHpToDisplay(ActivePokemon*);
s32 func_82105C8C(ActivePokemon*, s32);
s32 func_82124BF8(ActivePokemon*);
void func_8212A4CC(CameraNode*, s32*, s32*);
void BattleScene_ReactionMultiHitEnd(CameraNode* arg0, void* arg1);

void BattleScene_ReactionSideEffect(CameraNode* arg0, void* arg1);

void func_821255EC(CameraNode*);
void BattleScene_ReactionNormal(CameraNode*, void*);
void BattleScene_ReactionCritical(CameraNode*, void*);
void BattleScene_ReactionMultiHitEnd(CameraNode*, void*);
void BattleScene_ReactionSideEffect(CameraNode*, void*);

void BattleScene_ActionStepReaction(CameraNode* arg0, void* arg1);

extern u8* D_8218B2F4[];
extern u8 D_8219A4F4;
extern u8 D_80073D84[];
void BattleScene_ActionStepIntro(CameraNode*, s32);
void BattleScene_ActionStepSetHitCount(CameraNode*, s32);
void BattleScene_ActionStepUseMove(CameraNode*, s32);
void BattleScene_ActionStepTravel(CameraNode*, s32);
void BattleScene_PhaseFirstAction(CameraNode* arg0);

extern u8* D_8218B320[];
void BattleScene_PhaseSecondAction(CameraNode* arg0);

s32 func_8210C020(M2C_UNK, s32);                    /* extern */
void BattleCamera_PlayShot(s32, s32, s32);
extern s32 D_8219A568;
void func_8212C398(s32 arg0);

s32 func_8210C020(M2C_UNK, s32);                    /* extern */
void func_8212C454(s32 arg0);

s32 func_8210C020(M2C_UNK, s32);                    /* extern */
void func_8212C530(s32 arg0);

void BattleCamera_PlayUserShot(s32 arg0, s32 arg1);

void BattleScene_CameraShotTargetHighThunk(void*, void*);
s32 func_82124810(void*, void*);
void func_82124830(void*, void*);
void func_82124874(void*, void*);

void BattleCamera_PlayTargetShot(ActivePokemon* arg0, CameraNode* arg1, s32 arg2);

typedef struct MoveAnimInfoZ {
    /* 0x00 */ u8 pad00[2];
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u8 pad04[2];
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u8 pad08[2];
} MoveAnimInfoZ; // size = 0xA
extern MoveAnimInfoZ D_80073D90[];
void BattleCamera_PlayUserShot(s32, s32);

void func_8212C78C(s32 arg0);

void func_821255B4(CameraNode*);
void func_8212C78C(s32);
void func_82125C80(CameraNode*);
s32 func_82105724(ActivePokemon*, s32);
void func_82105E64(ActivePokemon*);
void func_82122B9C(CameraNode*, ActivePokemon*);
void BattleScene_PhaseSelfEffect(CameraNode* arg0);

void BattleCamera_PlayTargetShot(ActivePokemon*, CameraNode*, s32);
void func_82122A7C(CameraNode*, ActivePokemon*);
void BattleScene_PhaseExplosion(CameraNode* arg0);

M2C_UNK func_8211EE8C();
void BattleScene_PhaseMoveFailedMessage(CameraNode* arg0);

void BattleScene_PhaseHeal(CameraNode* arg0);

s32 func_821217DC(s32);
void func_821233EC(CameraNode*, ActivePokemon*);
void func_8210881C(ActivePokemon*);
void func_82107408(ActivePokemon*);
void func_82107160(ActivePokemon*);
void func_82101B54(ActivePokemon*, s32);
void Audio_PlayMoveSound(s32, s32, s32);
void func_82125C34(CameraNode*);
void BattleScene_PhaseTransform(CameraNode* arg0);

void func_821020FC(s8*);
void BattleScene_PhaseSubstitute(CameraNode* arg0);

void func_821224F4();
void ActivePokemon_SetStateFlags(ActivePokemon*, s32);
void func_8212311C(CameraNode*, ActivePokemon*, f32);
s32 func_82121820(s32);
void func_8213C4B8(void);
extern f32 D_FLT_82189354[][4];
void BattleScene_PhaseFlyUp(CameraNode* arg0);

extern s32 D_84390220;
extern ActivePokemon* D_84390204;
extern s32 D_84390224;

void BattleScene_PhaseCannotMove(CameraNode* arg0);

s32 Battle_ClearRuntimeFlags(s8 *arg0, unsigned short arg1);
void func_82136708(s32, ActivePokemon*);
void func_8212E9C8(ActivePokemon* arg0);

void func_8212E9C8(ActivePokemon*);
void BattleAnim_QueueEffectList(u8 arg0, s32 arg1);
void BattleScene_PhaseConfusionSelfHit(CameraNode* arg0);

void BattleScene_PhaseFullParalysis(CameraNode* arg0);

void func_8212EEC0(ActivePokemon* arg0, CameraNode* arg1);

void func_8212EF74(ActivePokemon*, CameraNode*);

void func_8212F044(CameraNode* arg0);

M2C_UNK func_8211EE8C();                            /* extern */
M2C_UNK func_82125384();                            /* extern */
extern s8 *D_8219A5A0;

void BattleScene_PhaseEndTurn(s32 arg0);

void func_82108C0C(ActivePokemon* active_pokemon);
s32 func_82124B30(ActivePokemon*);
void BattleScene_PhaseCrashDamage(CameraNode* arg0);

extern s32 D_84390228;
extern ActivePokemon* D_84390200;
void func_8210626C(ActivePokemon*);

void BattleScene_PhaseMoveMissed(CameraNode* arg0);

void BattleScene_PhaseInflictStatus(CameraNode* arg0);

void func_82125AC8(CameraNode* arg0);
void BattleScene_PhaseLowerStat(CameraNode* arg0);

s16 func_82107B54(ActivePokemon*);
void BattleScene_PhaseDisable(CameraNode* arg0);

void func_821365E8(s32, ActivePokemon*);
void func_82125AC8(CameraNode*);
void func_8212F9FC(CameraNode* arg0);

void func_82124894(CameraNode*, ActivePokemon*);
void func_82106374(ActivePokemon*);
void func_82106354(ActivePokemon*);
s32 func_82124A50(ActivePokemon*);
void func_82108C0C(ActivePokemon*);
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);
s32 func_82107CA0(ActivePokemon*);
void BattleScene_PhaseResidualDamageAfterMove(CameraNode* arg0);

s32 func_82124A50(ActivePokemon* active_pokemon);
void func_82124894(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_Phase10(CameraNode* arg0);

void BattleScene_PhaseResidualDamageWithoutMove(CameraNode* arg0);

void func_82130D48(ActivePokemon* active_pokemon);

Vec3f* Vec3f_SetComponentsDuplicate(Vec3f* dest, f32 x, f32 y, f32 z);
s32 ModelAnim_IsAnimationDone(DisplayObject* display_object);
void func_82130D48(ActivePokemon*);
void func_8212562C(void);
void BattleScene_PhaseWithdraw(CameraNode* arg0);

void BattleCamera_CaptureModelOrbit(ActivePokemon* arg0, CameraNode* arg1);
void func_82122A7C(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_PhaseSendOutAfterFaint(CameraNode* arg0);

void func_82125FD0(void);
void BattleScene_InitTurnPresentation(CameraNode* arg0);
void BattleScene_PhaseFaint(CameraNode* arg0);
void func_82126E34(CameraNode* arg0);
void BattleScene_PhaseCommand(CameraNode* arg0);
void BattleScene_PhaseBide(CameraNode* arg0);
void BattleScene_PhaseHaze(CameraNode* arg0);
void BattleScene_PhaseDigUnder(CameraNode* arg0);
void BattleScene_PhaseChargeUp(CameraNode* arg0);
void BattleScene_PhaseConfusionSelfHit(CameraNode* arg0);
void BattleScene_PhaseMoveMissed(CameraNode* arg0);
void BattleScene_PhaseRecoilDamage(CameraNode* arg0);
void func_82130494(CameraNode* arg0);
void BattleScene_PhaseResidualDamageFaintCheck(CameraNode* arg0);
// Zero numbers its phases differently, so the cases call the Zero handlers by address.
void BattleScene_UpdatePhase(CameraNode* arg0);

extern const f32 D_FLT_82196668;
extern const f32 D_FLT_8219666C;
extern Vec3f D_8218B630;
void func_80041914(u8, u8);
void func_82131880(CameraNode* arg0);

s32 func_82101FD4(s32);                             /* extern */
extern s32 D_82199DE0;

void func_821319FC(s32 arg0);

s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);   /* extern */
M2C_UNK ActivePokemon_SetModelTransform(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821365B0(M2C_UNK, s8 *, s8 *, M2C_UNK, s32); /* extern */
extern M2C_UNK D_82199DE0;

void BattleScene_OpeningStepThrowSide1(s32 arg0);

void BattleScene_IntroPanCamera(CameraNode* arg0);

s32 func_8001101C(s8 *, M2C_UNK *);               /* extern */

void BattleScene_OpeningStepWaitSide0Ball(s32 arg0);

s32 ActivePokemon_GetNickname(ActivePokemon*);
s32 BattleMessage_Format(s32, s32, s32, ...);
extern char D_82196650[];
void BattleScene_SendOutSide0(CameraNode* arg0);

s32 func_821057D4(ActivePokemon*, s32);
void BattleScene_OpeningStepWaitSide0SendOut(CameraNode* arg0);

extern char D_8219665C[];
void BattleScene_SendOutSide1(CameraNode* arg0);

M2C_UNK func_82125384();

void BattleScene_OpeningStepWaitSide1SendOut(CameraNode* arg0);

#endif
