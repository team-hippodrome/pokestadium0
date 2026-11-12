#ifndef ZERO_BATTLE_ENGINE_309ED0_H
#define ZERO_BATTLE_ENGINE_309ED0_H

/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_309ED0.c, src/fragments/battle_engine/battle_engine_339CA0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "model_animation.h"
#include "model_renderer.h"
#include "audio_commands.h"
#include "3D140.h"
#include "audio_fade.h"
#include "audio_loop_point.h"
#include "cry.h"
#include "matrix.h"
extern s32 pad_D_84390210[4];
extern s32 sMultihitCount;
extern s32 sMultihitCountdown;

#include "geo_render.h"
#include "gfx_buffer.h"
#include "math_util.h"

#include "m2c_macros.h"
void func_821254B0(void);

void BattleScene_ResetAnimationStep(void);
void func_82124EF4(void);
void BattleScene_ClearPhaseFlag(void);
void BattleScene_SetPhaseFlag(void);
void BattleScene_SetPhase(UNUSED CameraNode* arg0, s32 arg1);
s32 BattleScene_TransitionToPhaseFull(s32 arg0);
s32 BattleScene_TransitionToPhase(s32 arg0);
void func_82126A1C(UNUSED CameraNode* arg0);
void BattleScene_PhaseSendOutAfterFaint(CameraNode* arg0);

void BattleScene_AdvanceSendOutPreparation(CameraNode* arg0);
void BattleScene_AdvanceSendOutCamera(CameraNode* arg0);
void BattleScene_AdvanceSendOutCameraClose(CameraNode* arg0);
void BattleScene_FinishSendOutCameraClose(CameraNode* arg0);
void BattleScene_AdvanceSendOutFollowupCamera(CameraNode* arg0);
void BattleScene_CompleteSendOutFollowup(UNUSED CameraNode* arg0);

void func_82105E4C(ActivePokemon*, s32);

void func_8210211C(ActivePokemon* active_pokemon);
void func_82108A0C(ActivePokemon* active_pokemon);
s32 func_82124A50(ActivePokemon* arg0);

void func_821020FC(ActivePokemon*);

s32 BattleScene_AdvanceOwnerAnimation98(ActivePokemon* arg0);

s32 func_82124BF8(ActivePokemon* arg0);

void func_821089D0(ActivePokemon*);

s32 BattleScene_AdvanceBothOwnerAnimations(void);

M2C_UNK func_82108C0C(s32);                         /* extern */
extern s32 D_8219A544;
extern s8 *D_8219A5A0;

void func_82124E80(void);

M2C_UNK func_82108C0C(s32);                         /* extern */
extern s32 D_8219A540;

void func_82124EB4(void);

void func_82124EFC(void);

void BattleScene_InitializeSwitchActions(void);

M2C_UNK func_821079E8(M2C_UNK);                     /* extern */

void func_821255B4(s8 *arg0);

M2C_UNK func_821079E8(M2C_UNK);                     /* extern */

void func_821255EC(s8 *arg0);

void Audio_FadeAndClearStoredSounds(void);
void func_8212562C(void);

s32 BattleScene_HandleFaintStatusCompletion(void);

extern ActivePokemon* D_84390200;

void BattleScene_CompleteActionPhase(void);

extern s32 D_84390220;
extern s32 D_84390224;
void func_8211EE8C(void);

extern s32 D_8219A560;
extern s32 D_8219A564;
u16 func_82107CA0(ActivePokemon* active_pokemon);
void func_82125838(void);
void BattleScene_ResolveDisplayedHpCompletion(CameraNode* arg0);

void func_82125570(void);
void func_8212188C(void);
M2C_UNK func_82106220();
void func_82125594(CameraNode* arg0, s32 arg1);
M2C_UNK func_821259E8();
M2C_UNK func_82125990();
s32 func_82125930(M2C_UNK);

void BattleScene_UpdateDisplayedHpAndTransition(CameraNode* arg0);

s32 Battle_StepPartyHpToDisplay(s32);                             /* extern */
M2C_UNK func_82125AC8(s32);                         /* extern */
extern s32 D_82199DE0;
extern s32 D_82199DE4;

void func_82125C34(s32 arg0);

M2C_UNK func_82125AC8(s32);
void func_82125C80(s32 arg0);

s32 func_82125930(M2C_UNK);                         /* extern */

s32 func_82125CC8(void);

s32 func_82125930(M2C_UNK);                         /* extern */
extern u8 D_82199F31;

s32 func_82125E5C(void);

s32 BattleScene_PrepareResidualStatusPresentation(void);

void BattleScene_UpdateActiveOwnerPointers(void);

M2C_UNK func_800419F8();                     /* extern */
M2C_UNK func_82108C0C(s32);                         /* extern */
M2C_UNK func_821218AC(s32, s32, f32, s32, f32, s32, s32); /* extern */
M2C_UNK func_82121D78(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK func_821224F4();                            /* extern */
M2C_UNK func_82124A40();                            /* extern */
extern M2C_UNK D_8218B630;
extern f32 D_FLT_821962A4;

void func_8212601C(s32 arg0);

void BattleScene_CameraShotTargetHighThunk(void*, void*);
s32 func_82124810(void*, void*);
void func_82124830(void*, void*);
void func_82124874(void*, void*);

void func_821261A0(void* arg0, void* arg1, s32 arg2);

extern f32 D_FLT_82189354[][4];
void func_82136708(s32, ActivePokemon*);
void func_8210568C(ActivePokemon*, s32, s32);
M2C_UNK func_80019B28(s32, u8, u8, u8, s32);
s32 func_82126220(ActivePokemon* active_pokemon);

void func_8212239C(ActivePokemon* arg0, CameraNode* arg1);
s32 func_82126220(ActivePokemon*);
void BattleScene_AdvanceSendOutPreparation(CameraNode* arg0);

void func_821229AC(CameraNode* arg0, ActivePokemon* arg1);

s32 func_80041374(s32, u32);

s32 func_821217DC(s32);
void func_80041940(s32, s32, s32, s32);
void func_80043A10(void);
void BattleScene_CompleteSendOutFollowup(UNUSED CameraNode* arg0);

void func_82126D20(UNUSED CameraNode* arg0);

void func_82126E34(CameraNode* arg0);

void func_8000EEBC(s8*, s8*, f32, s32, s32);
void func_82126EE0(CameraNode* arg0);

void func_82126F70(CameraNode* arg0);

void BattleScene_Phase2(CameraNode* arg0);

void func_821272C0(s8 *arg0);

M2C_UNK func_82125580();
void func_8211F034(s32, s32);
s32 func_82105724(ActivePokemon*, s32);
extern s32 D_8219A520;
void func_82104C68(ActivePokemon*, s32);
void func_82128E34(s32 arg0);

void func_82124984(ActivePokemon* arg0, CameraNode* arg1, s32 arg2);
void func_821228B0(CameraNode* arg0, ActivePokemon* arg1);
s32 func_821058E8(ActivePokemon* arg0, s32 arg1);

void func_82128FBC(CameraNode* arg0);

void func_821290CC(CameraNode* arg0);

void func_821291E4(CameraNode* arg0);

void func_821292FC(CameraNode* arg0);

M2C_UNK func_8212189C();
s32 func_82121798(s32);
void func_8210C1A8(f32*, f32, f32);
void func_82129414(CameraNode* arg0);

extern s32 D_8219A568;
void func_82128FBC(CameraNode*);
void func_821290CC(CameraNode*);
void func_821291E4(CameraNode*);

void func_8212954C(CameraNode* arg0);

void func_821292FC(CameraNode*);
void func_8212960C(CameraNode* arg0);

void func_82129414(CameraNode*);
void func_821296E4(CameraNode* arg0);

void func_821366B0(s32, ActivePokemon*);
void func_821299B0(CameraNode* arg0);

extern ActivePokemon* D_84390204;
M2C_UNK func_82124284(s32, s32, f32);
M2C_UNK func_821243DC(s32, s32, f32);
void BattleScene_ActionSetupAnimationVariantB(CameraNode* arg0);

f32 BattleScene_GetParticipantHeight(s32);

void func_82129D10(CameraNode* arg0);

M2C_UNK func_82106374(s32);                         /* extern */
f32 BattleScene_GetParticipantHeight(s32);                             /* extern */
M2C_UNK func_821224F4();                            /* extern */
M2C_UNK func_82124284(s32, s32, f32);               /* extern */
M2C_UNK func_821243DC(s32, s32, f32);               /* extern */
M2C_UNK func_82125580();                            /* extern */
M2C_UNK func_8213B31C(M2C_UNK);                     /* extern */
extern f32 D_FLT_821963A0;
extern f32 D_FLT_821963A4;

void func_82129E30(s32 arg0);

/*
 * func_82129F5C
 *
 * A two-state step function with the same shape as func_82129E30 and
 * func_8212A074, which sit next to it.  arg0 is the camera node; the state
 * is the word at +0x3C of the scene object D_8219A5A0, and +0x50 of that
 * object is set to 2 on every call.
 *
 *   state 0: func_8213B31C(1), func_821224F4() and func_82125580() are
 *            called, then func_82124544(arg0, D_8219A540, 8.0, 6.0, 2.5,
 *            6.0, 0) is called.  Judging by its definition in
 *            battle_engine_3055E0.c, that sets the camera's at and eye
 *            positions from the ActivePokemon held in D_8219A540.  The
 *            retail code loads 6.0 once and reuses it for both the fourth
 *            and the sixth argument.
 *   state 1: func_82124664(arg0, D_8219A540, 0) is called.  Once the float
 *            at +0x74 of the scene object is below the float at +0x5C plus
 *            D_FLT_821963A8, func_82106374(D_8219A544) is called, the
 *            counter at +0x20 is incremented and func_82125570() and
 *            func_8212188C() are called.
 *   other states: nothing further happens.
 *
 * What the scene fields and the called helpers mean is not established here.
 */
M2C_UNK func_82106374(s32);                         /* extern */
M2C_UNK func_821224F4();                            /* extern */
M2C_UNK func_82124544(s32, s32, f32, f32, f32, f32, s32); /* extern */
M2C_UNK func_82124664(s32, s32, M2C_UNK);           /* extern */
M2C_UNK func_82125580();                            /* extern */
M2C_UNK func_8213B31C(M2C_UNK);                     /* extern */
extern f32 D_FLT_821963A8;

void func_82129F5C(CameraNode* arg0);

M2C_UNK func_82106374(s32);                         /* extern */
M2C_UNK func_821224F4();                            /* extern */
M2C_UNK func_82124544(s32, s32, f32, f32, f32, f32, s32); /* extern */
M2C_UNK func_82124664(s32, s32, M2C_UNK);           /* extern */
M2C_UNK func_82125580();                            /* extern */
M2C_UNK func_8213B31C(M2C_UNK);                     /* extern */

void func_8212A074(s32 arg0);

void func_82129C1C(CameraNode*);
void func_82129D10(CameraNode*);
void func_82129E30(s32);

void func_8212A190(CameraNode* arg0);

void func_82129F5C(CameraNode*);
void func_8212A250(CameraNode* arg0);

typedef struct MoveAnimInfoZ {
    /* 0x00 */ u8 pad00[4];
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 pad06[4];
} MoveAnimInfoZ; // size = 0xA
extern MoveAnimInfoZ D_80073D90[];
void func_82106144(s32);
void func_8212A250(CameraNode*);
void func_8212A328(CameraNode* arg0, s32 arg1);

extern s32 D_8219A578;

void func_8212A4A4(s8 *arg0);

M2C_UNK func_82108C0C(s32);                         /* extern */
s32 func_82121820(M2C_UNK);                         /* extern */
M2C_UNK func_8212189C();                            /* extern */
M2C_UNK func_82124A40();                            /* extern */
M2C_UNK func_82125AC8(s32);                         /* extern */

void func_8212A4CC(s32 arg0, s32 *arg1, s32 *arg2);


void func_8212A554(s32 arg0);

void func_8212A5AC(ActivePokemon* arg0, CameraNode* arg1);
void func_8212A67C(ActivePokemon* arg0, CameraNode* arg1);

void func_8212A768(ActivePokemon* arg0, CameraNode* arg1, s32 arg2);

void BattleScene_SetDamageShakeAmplitude(ActivePokemon*);
void func_82110B44(ActivePokemon*);
void func_82135098(ActivePokemon*);
void func_821061A8(ActivePokemon*);
s32 func_82122DFC(CameraNode*, ActivePokemon*);
void func_8212A850(CameraNode* arg0, s32 arg1);

void func_8212AD10(CameraNode* arg0, s32 arg1);

#endif
