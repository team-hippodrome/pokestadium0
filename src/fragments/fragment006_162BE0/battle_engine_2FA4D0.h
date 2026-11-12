#ifndef ZERO_BATTLE_ENGINE_2FA4D0_H
#define ZERO_BATTLE_ENGINE_2FA4D0_H

/* Stadium Zero fragment006_162BE0. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_2FA4D0.c, src/fragments/battle_engine/battle_engine_3020D0.c, src/fragments/trade_machine/trade_machine_291D60.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "status_icons.h"
#include "game_state.h"
#include "text_system.h"
#include "3D140.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"

#include "fragments/trade_machine/trade_machine.h"
#include "pokemon_stats.h"
#include "audio_sfx.h"
#define U64_NOP(x) ((u32)((u64)(x) | 0ULL))

#include "stdarg.h"
#include "moves.h"
extern unk_D_843901A0* gBattleMessageQueues;

#include "m2c_macros.h"

void BattleHud_Noop(void);
void func_88400100(void);
void Trade_DrawSaveSeqMessageBackdrop(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_884022A4(void);

extern s32 D_88403358;

void func_88400020(s32 arg0, s8 *arg1);

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

s32 func_88400064(s32 arg0, unk_D_86002F34_alt18* arg1);

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_8001B5F0();                            /* extern */

s32 func_884000CC(void);

M2C_UNK func_80005770(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_8001560C(s32);                         /* extern */
M2C_UNK func_800158C0();                            /* extern */
extern M2C_UNK D_800AA150;
extern s32 D_88403370;

s32 func_88400108(s32 arg0);

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_88400A1C(s16, s16, s16, s16);          /* extern */

void func_88400A98(void);

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_88400A1C(s16, s16, s16, s16);          /* extern */

void func_88400B70(void);

extern s32 D_88403364;
void func_88400C48(s16 arg0, s16 arg1);

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_8001AB2C(M2C_UNK);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */
extern s8 *D_800603C0;
extern s32 D_88402D70;

void func_88400CE8(s32 arg0);

void func_88400DAC(s8* arg0);

/*
 * func_88400F4C
 *
 * Scene setup that brackets some work between two runs of the same
 * callback.  Names in brackets are the ones symbol_addrs.txt gives the
 * called addresses; the meaning of the data and of most of the file-local
 * callees is not established.
 *
 *   1. func_8000A7B0(0xC) (Audio_PlayMusicIfChanged) is called.
 *   2. Bit 0 of byte 1 of D_884034E0 is set.
 *   3. func_80006828(0x73, func_88400108) (BgStage_RunUntilCondition) is
 *      run, i.e. timer value 0x73 with func_88400108 as the callback.
 *   4. Bit 5 (0x20) of byte 2 of D_884034E0 is cleared, func_88400A98() is
 *      called and func_800407B0(0x51, 0, 0) (Audio_PlayCommand) is called.
 *   5. Depending on bit 3 (value 8) of D_800AF986, the pair
 *      (D_88402D88, D_88402D8C) or the pair (D_88402D90, D_88402D94) is
 *      used: func_88400CE8 is called with the first value, func_88400DAC
 *      with the second, and func_88400CE8 again with the second value
 *      read as an integer.
 *   6. func_88400B70() is called, bit 5 of byte 2 of D_884034E0 is set
 *      again, and func_80006828(0x2D, func_88400108) is run.
 */
M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_8000A7B0(M2C_UNK);                     /* extern */
M2C_UNK func_800407B0(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
extern u16 D_800AF986;
extern s32 D_88402D88;
extern s8 *D_88402D8C;
extern s32 D_88402D90;
extern s8 *D_88402D94;
extern M2C_UNK D_884034E0;

void func_88400F4C(void);

extern u8 D_8F4B2EB0[];
extern char D_884032A8[];
extern char D_884032CC[];
extern char D_884032E0[];
extern char D_884032FC[];
extern char D_88403304[];
void func_8840173C(s32 arg0, s32 arg1);

void func_884014B4(s32, u8);
void func_8840173C(s32, s32);
s32 func_88401970(s32 arg0, s32 arg1, u8 arg2);

void func_800245E0(s32 arg0, s32 arg1);
void Save_InitializeBank3(void);

void func_800273E8(s8* arg0, s32 arg1);
s32 func_80027214(s8*, s32);
void func_80010F8C(void*, s32);
void func_80010F9C(void*, s32);
void func_8000A7FC(s32);
void func_80041374(s32, s32);
M2C_UNK func_80006998(M2C_UNK);
M2C_UNK func_80005B98(M2C_UNK);
extern M2C_UNK D_88403648;
extern s8 D_88402E24;
extern s8 D_88402E08;
void func_88401E24(void);

M2C_UNK func_8003F6AC(M2C_UNK);
M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);
M2C_UNK func_80010F14(M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_8001107C(M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
void func_80019924(M2C_UNK *, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_80025100(s8 *, M2C_UNK);               /* extern */
extern M2C_UNK D_88402D74;
extern M2C_UNK D_884037B0;
extern M2C_UNK D_8F4014CC;
extern M2C_UNK D_8F4889B8;
extern M2C_UNK D_88403378;

void func_88401F38(void);

M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_80006998(M2C_UNK);                     /* extern */
M2C_UNK func_800199E4(M2C_UNK *);                   /* extern */

void func_88402038(void);

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_800067BC(M2C_UNK);                     /* extern */
M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_8000D520(s32, s8 *);                 /* extern */
M2C_UNK func_80025BE4(s32);                         /* extern */
void func_8840115C(void);
void func_884022AC(void);                            /* extern */
extern s8 D_88402DD0;
extern s8 D_88402DEC;
extern s32 D_88403360;
s32 func_884023F0(void);

typedef struct GbPortSummaryZ {
    /* 0x00 */ u8 saveState;
    /* 0x01 */ u8 game;
    /* 0x02 */ u16 trainerId;
    /* 0x04 */ char name[0xE];
} GbPortSummaryZ; // size = 0x12
extern GbPortSummaryZ D_88403310[4];
typedef struct GbIdentityZ {
    /* 0x00 */ u16 trainerId;
    /* 0x02 */ char name[10];
} GbIdentityZ;

void func_88402538(void);

s32 func_800023C4(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_800051C0(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
s32 func_800051F0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_800052E8(s32, s32);                    /* extern */
extern s8 *D_88403368;
extern s8 *D_8840336C;

void func_884029FC(void);

#include "stage_loader.h"
extern u8 D_01000000[];
extern u8 D_04000000[];
extern u8 D_8F400000[];
extern u8 D_8E800000[];
extern u8 D_8E900000[];
extern u8 D_88000000[];
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
void func_884025E4(void);
void func_884026A4(s32);
s32 func_88402334(void);
s32 func_8840248C(void);

s32 Fragment006_Main(s32 arg0, s32 arg1);

#endif
