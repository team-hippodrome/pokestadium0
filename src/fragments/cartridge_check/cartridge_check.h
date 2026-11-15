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

extern CameraNode* D_80060488;

extern M2C_UNK D_800AA150;

extern s32 D_88403370;

extern s32 D_88403364;

extern s32 D_88402D70;


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
void CartridgeCheck_PokeBallVisibilityCallback(s32 event, s8 *node);
void CartridgeCheck_UnusedNoop1(void);
s32 CartridgeCheck_LightAngleCallback(s32 event, GeoLightNode* light);
s32 CartridgeCheck_ReadInputs(void);
void CartridgeCheck_UnusedNoop2(void);
s32 CartridgeCheck_DrawFrame(s32 arg0);
void CartridgeCheck_DrawGameBoyIcon(s32 x, s32 y, s32 port, s32 game);
void CartridgeCheck_DrawPortPanel(s32 port, s32 x, s32 y);
s32 CartridgeCheck_MoveCursor(s32 cursor);
void CartridgeCheck_DrawMessageWindow(s16 x, s16 y, s16 width, s16 height);

// cartridge_check_options.c
void CartridgeCheck_OpenMessageWindow(void);
void CartridgeCheck_CloseMessageWindow(void);
void CartridgeCheck_DrawNextArrow(s16 x, s16 y);
void CartridgeCheck_ShowMessageUntilA(s32 text);
void CartridgeCheck_ScrollToNextMessage(s8* text);
void CartridgeCheck_RunGameBoyGiftEvent(void);
void CartridgeCheck_PlayBootIntro(void);
void CartridgeCheck_PlayCupWinIntro(void);
void CartridgeCheck_DrawScreen(void);
void Options_DrawMenu(s32 row, u8 flags);
void Options_DrawClearSavePrompt(s32 second_ask, s32 choice);
s32 Options_RunClearSavePrompt(s32 second_ask, s32 row, u8 flags);
void Save_ResetAll(void);
void Options_RunMenu(void);
s32 CartridgeCheck_RunScreen(void);
void CartridgeCheck_PlayExitToTitle(void);
void CartridgeCheck_PlaySetCartridgeAnimation(void);
void CartridgeCheck_PlayLowerMonitor(void);
void CartridgeCheck_PlayZoomIntoMonitor(void);
void CartridgeCheck_PlayZoomOutOfMonitor(void);
void CartridgeCheck_UnusedNoop3(void);
void CartridgeCheck_TransitionToMainMenu(void);
s32 CartridgeCheck_EnterFromBoot(void);
s32 CartridgeCheck_EnterAfterCupWin(void);
s32 CartridgeCheck_EnterFromMainMenu(void);
void CartridgeCheck_ReadPortSummaries(void);
void CartridgeCheck_InitCursor(void);
void CartridgeCheck_InitModels(s32 from_main_menu);
void CartridgeCheck_InitRenderTargets(void);
s32 CartridgeCheck_Main(s32 from_main_menu, s32 arg1);

#endif // FRAGMENT_CARTRIDGE_CHECK_H
