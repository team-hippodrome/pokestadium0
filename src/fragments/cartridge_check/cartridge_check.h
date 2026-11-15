/* Declarations for the cartridge_check fragment (src/fragments/cartridge_check/). */
#ifndef FRAGMENT_CARTRIDGE_CHECK_H
#define FRAGMENT_CARTRIDGE_CHECK_H

#include "global.h"
#include "stdarg.h"
#include "moves.h"
#include "m2c_macros.h"

#define U64_NOP(x) ((u32)((u64)(x) | 0ULL))

typedef struct GbPortSummaryZ {
    /* 0x00 */ u8 saveState;
    /* 0x01 */ u8 game;
    /* 0x02 */ u16 trainerId;
    /* 0x04 */ char name[0xE];
} GbPortSummaryZ; // size = 0x12

typedef struct GbIdentityZ {
    /* 0x00 */ u16 trainerId;
    /* 0x02 */ char name[10];
} GbIdentityZ;

extern s32 D_88403358;

/*
 * func_88400064
 *
 * Light-node callback (the stage light's "angle" callback A, declared in
 * battle_engine.h as Battle_StageLightAngleCallbackA).  When called with
 * event 2 it takes the direction from the current camera's eye position to
 * its target position (Vec3f_CalculateDistanceAngles) and stores the two
 * resulting angles, each offset by +0x2000, in the light's halfwords at
 * offsets 0x1C and 0x1E.  Always returns 0.
 *
 * Structure follows Intro_LightAngleCallbackA / Completion_LightAngleCallbackA
 * in the Stadium 1 decomp, but Zero adds +0x2000 to both angles where those
 * subtract 0x2000 from the second one (the constants come from the retail
 * code).  The locals sit 4 bytes below where a plain declaration would put
 * them, which the unused leading `pad` reproduces.
 */
extern CameraNode* D_80060488;

extern M2C_UNK D_800AA150;

extern s32 D_88403370;

extern s32 D_88403364;

extern s32 D_88402D70;

extern u16 D_800AF986;

extern s32 D_88402D88;

extern s8 *D_88402D8C;

extern s32 D_88402D90;

extern s8 *D_88402D94;

extern M2C_UNK D_884034E0;

extern char D_884032A8[];

extern char D_884032CC[];

extern char D_884032E0[];

extern char D_884032FC[];

extern char D_88403304[];

extern M2C_UNK D_88403648;

extern s8 D_88402E24;

extern s8 D_88402E08;

extern M2C_UNK D_88402D74;

extern M2C_UNK D_884037B0;

extern M2C_UNK D_88403378;

extern s8 D_88402DD0;

extern s8 D_88402DEC;

extern s32 D_88403360;

extern GbPortSummaryZ D_88403310[4];

extern s8 *D_88403368;

extern s8 *D_8840336C;

extern u8 D_01000000[];

extern u8 D_04000000[];

extern u8 D_002E0BE0[];

extern u8 D_002E2B90[];

extern u8 D_00400F70[];

extern u8 D_004076E0[];

extern u8 D_0038A540[];

extern u8 D_003C5200[];

extern u8 D_003CE090[];

extern u8 D_003D64A0[];

extern u8 D_00235D70[];

extern u8 D_00238BD0[];

// cartridge_check.c
void BattleHud_Noop(void);
void func_88400100(void);
void Trade_DrawSaveSeqMessageBackdrop(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_88400020(s32 arg0, s8 *arg1);
s32 func_88400064(s32 arg0, unk_D_86002F34_alt18* arg1);
s32 func_884000CC(void);
s32 func_88400108(s32 arg0);
M2C_UNK func_88400A1C(s16, s16, s16, s16);          /* extern */

// cartridge_check_options.c
void func_884022A4(void);
void func_88400A98(void);
void func_88400B70(void);
void func_88400C48(s16 arg0, s16 arg1);
void func_88400CE8(s32 arg0);
void func_88400DAC(s8* arg0);
void func_88400F4C(void);
void Options_DrawClearSavePrompt(s32 arg0, s32 arg1);
void Options_DrawMenu(s32, u8);
s32 Options_RunClearSavePrompt(s32 arg0, s32 arg1, u8 arg2);
void Save_InitializeBank3(void);
void func_88401E24(void);
void func_88401F38(void);
void func_88402038(void);
void func_8840115C(void);
void func_884022AC(void);                            /* extern */
s32 TransferPak_EnterWithPakSkippingCheck(void);
void func_88402538(void);
void func_884029FC(void);
void func_884025E4(void);
void func_884026A4(s32);
s32 TransferPak_EnterCheckScreenNoPaks(void);
s32 TransferPak_EnterCheckScreenOnReturn(void);
s32 Fragment006_Main(s32 arg0, s32 arg1);

#endif // FRAGMENT_CARTRIDGE_CHECK_H
