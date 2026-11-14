/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/dp_intro.c, src/game_state.c. */

#include "game_state.h"
#include "asset_archive.h"
#include "audio_music.h"
#include "font.h"
#include "gb_tower.h"
#include "gb_tower_launch.h"
#include "gfx_buffer.h"
#include "graphics_textures.h"
#include "leo.h"
#include "matrix.h"
#include "memory_main.h"
#include "menu.h"
#include "pokemon_stats.h"
#include "rsp.h"
#include "save_data.h"
#include "stage_loader.h"
#include "functions.h"
#include "lib/ultralib/include/PR/os_internal_reg.h"
extern u16 D_8006BBB0[16][256];
extern s32 pad_D_80075660;
extern s32 pad_D_80075664;
extern s32 gCurrentGameState;
extern s32 gLastGameState;
extern s32 pad_D_80075670;
extern s16 D_800733D4;
extern s16 D_800733D8;
extern unk_D_800AE520 D_800AF990;
extern s32 pad_D_800AE534[2];
extern SessionContext gSessionContext;
typedef struct SessionBlock {
    /* 0x0000 */ s8 unk_0000;
    /* 0x0001 */ s8 unk_0001;
    /* 0x0002 */ s8 unk_0002;
    /* 0x0003 */ s8 unk_0003;
    /* 0x0004 */ u8 unk_0004[0x1038];
    /* 0x103C */ TeamRoster* unk_103C;
    /* 0x1040 */ u8 unk_1040[0x54];
    /* 0x1094 */ u8 unk_1094;
    /* 0x1095 */ u8 unk_1095;
    /* 0x1096 */ u16 unk_1096;
} SessionBlock; // size = 0x1098
SessionBlock D_800AE8F0;

#include "global.h"
#include <PR/os_internal_reg.h>
extern u64 F3DEX2_data_bin[];
extern s32 D_800733F0;
extern u64 D_80087B88[0x100 / sizeof(u64)];
extern u64 D_80087C88[0x408 / sizeof(u64)];
extern u64 D_80088090[0xC08 / sizeof(u64)];
extern u64 D_80088C98[0x20000 / sizeof(u64)];
void Display_ClearFramebufferLine(u16 color);
void Display_SetBufferConfig(DisplayFrame* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);

#include "m2c_macros.h"

s32 Fragment_LoadAndCall(s32 arg0, u8* romStart, u8* romEnd, u32 arg3, u32 arg4);
void Fragment_QueueCall(s32 arg0, u8* arg1, u8* arg2, s32 arg3, s32 arg4);
TeamRoster* Trainer_GetSlots(void);
s32 GbSave_GetActivePort(void);
void GbSave_SetActivePort(s32 arg0);
void State_N64ddBootUnused(void);
void func_800268DC(void);
void Game_ShutdownAndLoadFragment(s32 arg0, s32 arg1);
void Game_ResetStorageDevice(void);
void Display_DisableBlackout(void);

void Display_ClearFramebufferLine(u16 color);
void Display_WaitForFrames(s32 arg0);
void Display_ApplyPendingVideoMode(void);

typedef struct { u8 b[5]; } Unk5Bytes;
M2C_UNK func_8001FD8C(void *, s32);                 /* extern */
M2C_UNK func_800203FC(void *);                      /* extern */
s32 func_8002057C(s32, s32, s32);                 /* extern */
extern M2C_UNK D_80065D00;
extern M2C_UNK D_8007B7B0;

void func_80025540(s8 *arg0, s32 arg1) {
    u8 *temp_v1;

    M2C_FIELD(arg0, s8 *, 0) = arg1;
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 5) = 0;
    M2C_FIELD(arg0, u8 *, 6) = ((u8 *)&D_80065D00)[arg1 * 0x17 - 0x11];
    M2C_FIELD(arg0, u8 *, 7) = ((u8 *)&D_80065D00)[arg1 * 0x17 - 0x10];
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 9) = 1;
    M2C_FIELD(arg0, s8 *, 0xA) = 0;
    M2C_FIELD(arg0, s8 *, 0xB) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
    M2C_FIELD(arg0, s16 *, 0x14) = 0x6400;
    M2C_FIELD(arg0, s16 *, 0x16) = 0x6400;
    M2C_FIELD(arg0, s16 *, 0x18) = 0x6400;
    M2C_FIELD(arg0, s16 *, 0x1A) = 0x6400;
    M2C_FIELD(arg0, s16 *, 0x1C) = 0x6400;
    M2C_FIELD(arg0, u16 *, 0x1E) = 0xFFFF;
    M2C_FIELD(arg0, s8 *, 0x20) = 0x23;
    M2C_FIELD(arg0, s8 *, 0x21) = 0;
    M2C_FIELD(arg0, s8 *, 0x22) = 0;
    M2C_FIELD(arg0, s8 *, 0x23) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = func_8002057C(arg1, 0x32, arg1);
    func_800203FC(arg0);
    M2C_FIELD(arg0, u16 *, 2) = M2C_FIELD(arg0, u16 *, 0x26);
    func_8001FD8C(arg0 + 0x30, arg1);
    *(Unk5Bytes *)(arg0 + 0x40) = *(Unk5Bytes *)&D_8007B7B0;
}

typedef struct { s32 w[0x14]; } Unk50Bytes;
extern u8 D_800AAF50[];
extern M2C_UNK D_8007B7B8;

/**
 * Sets up trainer slot `arg1` as a human player on controller port `arg0` with roster info `arg2`.
 * Seen in play (2026-11-13) ran during boot, before the opening (console reset, then N64 logo,
 * opening, title and main menu).
 * @unverified Name and comment guessed from the code.
 */
M2C_UNK Session_InitHumanTrainer(M2C_UNK arg0, M2C_UNK *arg1, M2C_UNK *arg2, s32 arg3) {

    M2C_FIELD(arg1, s8 *, 0) = 1;
    M2C_FIELD(arg1, s8 *, 1) = arg0;
    M2C_FIELD(arg1, u8 **, 4) = D_800AAF50 + arg0 * 0x24;
    M2C_FIELD(arg1, s32 *, 0x18) = 0;
    M2C_FIELD(arg1, s8 **, 0x1FC) = (s8 *)arg2;
    M2C_FIELD(arg1, s8 *, 2) = 1;
    *(Unk5Bytes *)((s8 *)arg1 + 8) = *(Unk5Bytes *)&D_8007B7B8;
    func_80025540((s8 *)arg1 + 0x1C, arg3);
    M2C_FIELD(arg2, s16 *, 0) = 0;
    M2C_FIELD(arg2, s8 *, 2) = 1;
    M2C_FIELD(arg2, s8 *, 3) = 0;
    M2C_FIELD(arg2, s8 *, 4) = 0;
    M2C_FIELD(arg2, s8 *, 0x14) = 0;
    *(Unk50Bytes *)((s8 *)arg2 + 0x28) = *(Unk50Bytes *)((s8 *)arg1 + 0x1C);
}

void func_8002572C(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 1) = 1;
    M2C_FIELD(arg0, s16 *, 2) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}

M2C_UNK Session_InitHumanTrainer(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
extern M2C_UNK D_800AE8F4;
extern M2C_UNK D_800AEAF8;
typedef struct { s16 unk_00; u8 unk_02; u8 unk_03; } Unk800AF104;
extern Unk800AF104 D_800AF104;
extern M2C_UNK D_800AF30C;
extern M2C_UNK D_800AF924;
extern M2C_UNK D_800AF94C;

/**
 * Sets the session mode to `arg0` and sets up both trainer slots and battle sides.
 * Seen in play (2026-11-13) ran during boot, before the opening (console reset, then N64 logo,
 * opening, title and main menu).
 * @unverified Name and comment guessed from the code.
 */
M2C_UNK Session_InitTwoTrainers(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    D_800AE8F0.unk_0000 = arg0;
    D_800AE8F0.unk_0001 = 1;
    D_800AE8F0.unk_0003 = 1;
    Session_InitHumanTrainer(0, &D_800AE8F4, (M2C_UNK *)&D_800AF104, arg1);
    Session_InitHumanTrainer(1, &D_800AEAF8, &D_800AF30C, arg2);
    func_8002572C((s8 *)&D_800AF924, (s32)&D_800AE8F4);
    func_8002572C((s8 *)&D_800AF94C, (s32)&D_800AEAF8);
}

/*
 * Session_LoadPortSnapshot
 *
 * If arg0 is a valid controller-port index (0 to 3), copies that port's
 * save snapshot into the buffer at D_800AF9A8 with GbSave_CopyPortSnapshot
 * (its return value is ignored).  Otherwise the first byte of the buffer is
 * cleared.  The buffer is the destination that func_80025830 later passes on
 * as its second argument to Save_WriteContinueData.
 */
extern GbSavePortSnapshot D_800AF9A8;

/**
 * Copies the GB save snapshot of port `arg0` into the session; clears it for an invalid port.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Session_LoadPortSnapshot(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4)) {
        GbSave_CopyPortSnapshot(arg0, &D_800AF9A8);
        return;
    }
    D_800AF9A8.gameType = 0;
}

typedef struct ContinueDataZ {
    /* 0x00 */ u8 mode;
    /* 0x01 */ u8 modeSelection;
    /* 0x02 */ u8 round;
    /* 0x03 */ u8 pad03;
    /* 0x04 */ u8 opponentHistory[8];
} ContinueDataZ; // size = 0xC
extern M2C_UNK D_800AF974;
void Save_WriteContinueData(ContinueDataZ* arg0, void* arg1, BattleMon* arg2, s32 arg3);

void func_80025830(void) {
    ContinueDataZ sp1C;
    ExtendedRosterInfo* info = (*(TeamRoster**)((u8*)&gSessionContext + 0x103C))->rosterInfo;

    sp1C.mode = gSessionContext.mode;
    sp1C.modeSelection = gSessionContext.modeSelection;
    sp1C.round = gSessionContext.roundOrDemoId + 1;
    _bcopy(&D_800AF974, sp1C.opponentHistory, 8);
    Save_WriteContinueData(&sp1C, &D_800AF9A8, info->battleMon, info->numberOfPokemonCanBePicked);
    Save_CommitTypedRecord(0x15, 0);
}

M2C_UNK func_80058410();
extern M2C_UNK D_800AF974;
extern M2C_UNK D_800AFB10;
extern M2C_UNK D_800AFB14;

void func_800258B4(void) {
    M2C_FIELD(&D_800AE8F0, u8 *, 0) = (u8) M2C_FIELD(&D_800AFB10, u8 *, 0);
    M2C_FIELD(&D_800AE8F0, u8 *, 1) = (u8) M2C_FIELD(&D_800AFB10, u8 *, 0);
    M2C_FIELD(&D_800AE8F0, u8 *, 2) = (u8) M2C_FIELD(&D_800AFB10, u8 *, 1);
    M2C_FIELD(&D_800AE8F0, u8 *, 3) = (u8) M2C_FIELD(&D_800AFB10, u8 *, 2);
    func_80058410(&D_800AFB14, &D_800AF974, 8, &D_800AFB10);
}

typedef struct { u8 b[3]; } Unk3Bytes;
typedef struct { u8 b[11]; } Unk11Bytes;
M2C_UNK func_8000A460(M2C_UNK *, M2C_UNK *);
s32 GbSave_GetTrainerId(s32 arg0);
M2C_UNK func_80022D84(s16, M2C_UNK *);
extern s32 D_800603C0;
extern s16 D_800733D4;
extern M2C_UNK D_8007B7C0;
extern M2C_UNK D_8007B7C4;

extern s32 D_800AE90C;
extern M2C_UNK D_800AE910;
extern M2C_UNK D_800AF108;
extern M2C_UNK D_800AF118;
extern M2C_UNK D_800AF12C;
extern s8 D_800AE8F6;

void func_80025910(s32 arg0)
{
  s8 *st = (s8 *) (&D_800AE8F0);
  *((s8 *) (st + 4)) = 1;
  *((s8 *) (st + 5)) = 0;
  *((s32 *) (st + 8)) = D_800603C0;
  *((s8 **) (st + 0x200)) = st + 0x814;
  if ((arg0 != 0) && (D_800733D4 == 0))
  {
    (*((s32 *) (st + 0x1C))) = GbSave_GetTrainerId(D_800733D4);
    func_80022D84(D_800733D4, (st + 0xC));
  }
  else
  {
    (*((s32 *) (st + 0x1C))) = 0;
    *((Unk3Bytes *) ((st + 0xC))) = *((Unk3Bytes *) (&D_8007B7C0));
  }
  *((s16 *) (st + 0x814)) = 0;
  *((u8 *) (st + 0x816)) = *((u8 *) ((st + 6)));
  *((u8 *) (st + 0x817)) = 0;
  func_80058410((st + 0x20), (st + 0x83C), 0x1E0);
  *((Unk11Bytes *) ((st + 0x818))) = *((Unk11Bytes *) (&D_8007B7C4));
  func_8000A460((st + 0x828), (st + 0xC));
  func_8002572C((s8 *) ((st + 0x1034)), (s32) ((st + 4)));
}

s8 Save_ReadContinueData(M2C_UNK *, s8 *, M2C_UNK *);       /* extern */
void func_80025910(s32);                          /* extern */
s32 func_80057910(s8 *, M2C_UNK *, M2C_UNK);        /* extern */
extern s8 D_800AE8F6;
extern M2C_UNK D_800AE910;

/*
 * func_80025A64
 *
 * Clears the byte at D_800AE8F0 + 0x1095, then calls
 * Save_ReadContinueData(&D_800AFB10, buf, &D_800AE910) with a 0x162-byte local
 * buffer. If it returns -1 the function returns 0. Otherwise the result is
 * stored to the byte D_800AE8F6 and:
 *  - if buf[0] == 0: calls func_80025910(buf[0]), sets bit 0 of the byte at
 *    D_800AE8F0 + 0x1095, sets the byte at + 0x1094 to 0xFF, calls
 *    Session_LoadPortSnapshot(-1) and returns 1;
 *  - otherwise, if D_800733D4 is in 0..3, GbSave_CopyPortSnapshot(D_800733D4,
 *    &D_800AF9A8) is non-zero and func_80057910(buf, &D_800AF9A8, 0x162)
 *    returns 0 (func_80057910 is libultra bcmp, so: the 0x162 bytes of buf
 *    equal the snapshot just copied): calls func_80025910(buf[0]), sets
 *    bit 0 of + 0x1095, stores D_800733D4 at + 0x1094, calls
 *    Session_LoadPortSnapshot(D_800733D4) and returns 1;
 *  - in every other case returns 0.
 *
 * What the buffer, D_800AE8F0's fields and the two helpers do is not
 * established. Matching notes: the unused `pad` local sits between the
 * buffer and `ret` as in the ROM's frame (buffer at sp+0x34, ret at sp+0x2C),
 * and the bit-0 update is written before the store of 0xFF to match the
 * ROM's register order.
 */
s32 func_80025A64(void) {
    s8 buf[0x162];
    UNUSED s32 pad; // FAKE: stack padding
    s32 ret;
    s8 temp_v0;

    ret = 0;
    D_800AE8F0.unk_1095 = 0U;
    temp_v0 = Save_ReadContinueData(&D_800AFB10, buf, &D_800AE910);
    if (temp_v0 != -1) {
        D_800AE8F6 = temp_v0;
        if (buf[0] == 0) {
            func_80025910(buf[0]);
            D_800AE8F0.unk_1095 = (u8) (D_800AE8F0.unk_1095 | 1);
            D_800AE8F0.unk_1094 = 0xFF;
            Session_LoadPortSnapshot(-1);
            ret = 1;
        } else if ((D_800733D4 >= 0) && (D_800733D4 < 4) && (GbSave_CopyPortSnapshot(D_800733D4, &D_800AF9A8) != 0) && (func_80057910(buf, &D_800AF9A8, 0x162) == 0)) {
            func_80025910(buf[0]);
            D_800AE8F0.unk_1095 = (u8) (D_800AE8F0.unk_1095 | 1);
            M2C_FIELD(&D_800AE8F0, s8 *, 0x1094) = (s8) D_800733D4;
            Session_LoadPortSnapshot((s32) D_800733D4);
            ret = 1;
        }
    }
    return ret;
}

/** Loads a fragment from a ROM range and calls its entry point. */
s32 Fragment_LoadAndCall(s32 arg0, u8* romStart, u8* romEnd, u32 arg3, u32 arg4) {
    s32 result;
    FragmentEntry func;

    func = Fragment_Load(arg0, romStart, romEnd);

    result = func(arg3, arg4);

    main_pool_try_free(func);

    return result;
}

/** Queues a fragment to be loaded and called by the game state loop. */
void Fragment_QueueCall(s32 arg0, u8* arg1, u8* arg2, s32 arg3, s32 arg4) {
    D_800AF990.unk_00 = 1;
    D_800AF990.fragment_id = arg0;
    D_800AF990.rom_start = arg1;
    D_800AF990.rom_end = arg2;
    D_800AF990.arg0 = arg3;
    D_800AF990.arg1 = arg4;
}

/** Returns the trainer slots of the session context. */
TeamRoster* Trainer_GetSlots(void) {
    return gSessionContext.trainerSlots;
}

/** Returns the controller port of the active Game Boy save. */
s32 GbSave_GetActivePort(void) {
    return D_800733D4;
}

/** Sets the active Game Boy save port when it is in range. */
void GbSave_SetActivePort(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4)) {
        D_800733D4 = arg0;
        D_800733D8 = 1;
    }
}

void Ui_DrawGradientPanel(s32 x1, s32 y1, s32 width, s32 height, Color_RGB8* top_color, Color_RGB8* bottom_color);
extern Color_RGB8 D_800733DC;
extern Color_RGB8 D_800733E0;
extern char D_8007B7D0[];
extern char D_8007B7E0[];
extern char D_8007B804[];
extern char D_8007B824[];
extern char D_8007B844[];
extern char D_8007B858[];
extern char D_8007B874[];
extern char D_8007B894[];

/**
 * Full-screen Game Boy save error: remove the cartridge, clean the connector and insert it again without turning the power off; "could not save (report)"; "wrong cartridge or the data changed". `arg0` picks the message.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Save_DrawGbReportErrorScreen(s32 arg0) {
    Color_RGB8 sp2C = D_800733DC;
    Color_RGB8 sp28 = D_800733E0;
    UNUSED s32 pad[2]; // FAKE: stack padding

    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    Ui_DrawGradientPanel(0x90, 0x64, 0x160, 0xC8, &sp2C, &sp28);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(8, -2);
    Font_Printf(0xB0, 0xB4, D_8007B7D0);
    Font_Printf(0xB0, 0xD0, D_8007B7E0);
    Font_Printf(0xB0, 0xEC, D_8007B804);
    Font_Printf(0xB0, 0x108, D_8007B824);
    Gfx_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
    Font_Printf(0x12E, 0xB4, D_8007B844);
    if (arg0 == 2) {
        Font_SetActive(0x10, -2);
        Font_Printf(0xBC, 0x84, D_8007B858);
    } else if (arg0 == 3) {
        Font_Printf(0xB0, 0x74, D_8007B874);
        Font_Printf(0xB0, 0x90, D_8007B894);
    }
    Font_EndTexturedTextRendering();
    BgStage_AdvanceFrame();
}

void Ui_DrawGradientPanel(s32 x1, s32 y1, s32 width, s32 height, Color_RGB8* top_color, Color_RGB8* bottom_color);
extern Color_RGB8 D_800733E4;
extern Color_RGB8 D_800733E8;
extern char D_8007B8B4[];

/**
 * Full-screen レポートちゅうです (Saving...) message.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Save_DrawReportingScreen(void) {
    Color_RGB8 sp2C = D_800733E4;
    Color_RGB8 sp28 = D_800733E8;
    UNUSED s32 pad[2]; // FAKE: stack padding

    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    Ui_DrawGradientPanel(0x90, 0x96, 0x160, 0x38, &sp2C, &sp28);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(0x10, -2);
    Font_Printf(0xDD, 0xA6, D_8007B8B4);
    Font_EndTexturedTextRendering();
    BgStage_AdvanceFrame();
}

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_80006724();                            /* extern */
M2C_UNK func_8000675C();                            /* extern */
s32 Font_Init(s32 load_size, s32 side);            /* extern */
M2C_UNK func_8001A360();                            /* extern */
s32 GbSave_PollCartRemoval(s32);                             /* extern */
void Save_DrawGbReportErrorScreen(s32);
void Save_DrawReportingScreen(void);
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_01000000;

/**
 * Pushes the 'GBER' pool state and shows the GB report error screen until the cartridge check passes.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Save_RunGbReportErrorScreen(s32 arg0) {
    M2C_UNK var_s0;
    s32 temp_v0;

    var_s0 = 2;
    func_8000256C(0x47424552);
    Font_Init(0x18, 0);
    func_80003EB8((u32) ((s32) &D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_8000675C();
    do {
        temp_v0 = GbSave_PollCartRemoval(arg0);
        if (temp_v0 == 1) {
            var_s0 = 1;
        }
        if (temp_v0 == 3) {
            var_s0 = 3;
        }
        Save_DrawGbReportErrorScreen(var_s0);
    } while (temp_v0 != 2);
    Save_DrawReportingScreen();
    Save_DrawReportingScreen();
    func_80006724();
    func_8001A360();
    func_80002620(0x47424552);
}

M2C_UNK Session_InitTwoTrainers(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_80025B60(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32); /* extern */
extern M2C_UNK D_0015F390;
extern M2C_UNK D_0015F8F0;
extern M2C_UNK D_0017ED00;
extern M2C_UNK D_00232510;
extern s32 D_800733C8;
extern M2C_UNK D_81500000;
extern M2C_UNK D_82100000;

void func_80025F3C(void) {
    func_80025B60(((u32) ((s32) &D_81500000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015F390, &D_0015F8F0, 0, 0);
    Session_InitTwoTrainers(5, 3, 3);
    func_80025B60(((u32) ((s32) &D_82100000 & 0x0FF00000) >> 0x14) - 0x10, &D_0017ED00, &D_00232510, 0, (s32) &D_800AE8F0);
    D_800733C8 = 0x8010;
}

extern M2C_UNK D_81200000;
extern M2C_UNK D_0015E220;
extern s32 D_800AF988;

/** Game state: shows the N64 logo quickly. */
void State_FastN64Logo(void) {
    D_800733C8 = func_80025B60(((u32) ((s32) &D_81200000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015E220, &D_0015F390, 0, 0);
    M2C_FIELD(&D_800AE8F0, u8*, 2) = 0;
    M2C_FIELD(&D_800AE8F0, s16*, 0x1096) = 0;
    switch (D_800733C8) {
        case 0x8010:
            func_80025B60(((u32) ((s32) &D_82100000 & 0x0FF00000) >> 0x14) - 0x10, &D_0017ED00, &D_00232510, 0, (s32) &D_800AE8F0);
            break;
        case 0x8020:
            D_800733D4 = -1;
            D_800AF988 = 0;
            D_800733C8 = 0x8040;
            break;
        default:
            D_800733D4 = 0;
            D_800AF988 = 1;
            break;
    }
}

extern M2C_UNK D_88000000;
extern M2C_UNK D_88400000;
extern u8 D_00162BE0[];
extern u8 D_00166580[];
extern u8 D_00235D70[];
extern u8 D_00238BD0[];
extern s16 D_800AF986;
extern StageContext *D_800AF9A4;
s32 GbSave_LoadPort(s32 arg0);
s32 func_80021E64(s32);
void GbSave_ValidateBeforeWrite(s32);
void GbSave_RequirePakPresent(s32);
u8 GbSave_GetSaveState(s32 arg0);
s32 GbSave_GetBoxCount(s32);
void func_80023C30(void);
void Save_RunGbReportErrorScreen(s32);
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_800260C4(void)
{
  s32 pushed = 0;
  main_pool_push_state('OVLY');
  func_80023C30();
  Gfx_InitDisplayListBuffers(0x10000, 0);
  D_800AF9A4 = StageContext_Allocate(1, 1, 2, 0, 2, 1);
  StageContext_Activate(D_800AF9A4);
  if (((*((u16 *) (((s8 *) (&D_800AE8F0)) + 0x1096))) & 1) && (!((*((u16 *) (((s8 *) (&D_800AE8F0)) + 0x1096))) & 2))) // FAKE: decomp slop, raw pointer casts stand in for struct fields
  {
    *((u16 *) (((s8 *) (&D_800AE8F0)) + 0x1096)) |= 0x100;
  }
  D_800733D8 = 0;
  if ((D_800AF988 != 0) || ((*((u16 *) (((s8 *) (&D_800AE8F0)) + 0x1096))) & 0x100))
  {
    D_800AF988 = 0;
    GbSave_SetActivePort(D_800733D4);
    Fragment_QueueCall((((u32) (((s32) (&D_88000000)) & 0x0FF00000)) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, (s32) (&D_800AE8F0));
  }
  else
  {
    Fragment_QueueCall((((u32) (((s32) (&D_88400000)) & 0x0FF00000)) >> 0x14) - 0x10, D_00162BE0, D_00166580, 0, (s32) (&D_800AE8F0));
  }
  func_80025A64();
  while ((D_800733C8 == 0x8040) && (D_800AF990.unk_00 != 0))
  {
    if (D_800733D8 != 0)
    {
      D_800733D8 = 0;
      if (GbSave_GetSaveState(D_800733D4) == 0)
      {
        if (pushed)
        {
          main_pool_pop_state('BUDT');
        }
        pushed = 1;
        main_pool_push_state('BUDT');
        GbSave_LoadPort(D_800733D4);
        if (GbSave_GetBoxCount(D_800733D4) == 0)
        {
          GbSave_ValidateBeforeWrite(D_800733D4);
          while (func_80021E64(D_800733D4) == 0)
          {
            Save_RunGbReportErrorScreen(D_800733D4);
          }

          GbSave_RequirePakPresent(D_800733D4);
        }
        func_80025A64();
      }
    }
    D_800AF990.unk_00 = 0;
    D_800733C8 = Fragment_LoadAndCall(D_800AF990.fragment_id, D_800AF990.rom_start, D_800AF990.rom_end, D_800AF990.arg0, D_800AF990.arg1);
  }

  D_800AF986 = (!((*((u16 *) (((s8 *) (&D_800AE8F0)) + 0x1096))) & 2)) * 0;
  StageContext_Deactivate();
  Gfx_FreeDisplayListBuffers();
  main_pool_pop_state('OVLY');
}

extern M2C_UNK D_00232510_2;
extern M2C_UNK D_0017ED00_2;
extern M2C_UNK D_0017BE70;
extern M2C_UNK D_0017E340;
extern M2C_UNK D_81700000;
extern M2C_UNK D_81800000;
extern M2C_UNK D_82200000;
extern M2C_UNK D_82300000;
extern M2C_UNK D_0015FCE0;
void func_80001948(s32);
void _bcopy(void* src, void* dst, s32);

void func_80026368(void)
{
  s32 prev;
  TeamRoster *roster;
  ExtendedRosterInfo *info;
  func_80001948(0xFFFF);
  if (D_800AE8F0.unk_1095 & 2)
  {
    func_800258B4();
  }
  else
  {
    D_800AE8F0.unk_0003 = 1;
  }
  if (D_800AE8F0.unk_0000 == 0)
  {
    D_800AE8F0.unk_0003 = 1;
    func_80025B60((((u32) (((s32) (&D_82200000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00232510, &D_00235D70, 0, (s32) &D_800AE8F0);
    func_80025B60((((u32) (((s32) (&D_82300000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0015FCE0, &D_00162BE0, 0, (s32) &D_800AE8F0);
    func_80025B60((((u32) (((s32) (&D_82100000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017ED00, &D_00232510_2, 0, (s32) &D_800AE8F0);
    func_80025B60((((u32) (((s32) (&D_82200000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00232510, &D_00235D70, 1, (s32) &D_800AE8F0);
  }
  else
  {
    prev = D_800AE8F0.unk_0000;
    func_80025B60((((u32) (((s32) (&D_82200000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00232510, &D_00235D70, 0, (s32) &D_800AE8F0);
    while (!(D_800AE8F0.unk_1096 & 1))
    {
      func_80025B60((((u32) (((s32) (&D_82300000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0015FCE0, &D_00162BE0, 0, (s32) &D_800AE8F0);
      func_80025B60((((u32) (((s32) (&D_82100000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017ED00, &D_00232510_2, 0, (s32) &D_800AE8F0);
      func_80025B60((((u32) (((s32) (&D_82200000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00232510, &D_00235D70, 2, (s32) &D_800AE8F0);
    }

    if (D_800AE8F0.unk_1096 & 0x40)
    {
      D_800733C8 = 0x8010;
      return;
    }
    else
    {
      if (D_800AE8F0.unk_1096 & 2)
      {
        roster = D_800AE8F0.unk_103C;
        D_800AE8F0.unk_0000 = 4;
        info = roster->rosterInfo;
        roster->numberOfPokemonBrought = info->numberOfPokemonCanBePicked;
        _bcopy(info->battleMon, roster->pokemonPicked, 0x1E0);
        func_80025B60((((u32) (((s32) (&D_82100000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017ED00, &D_00232510_2, 0, (s32) &D_800AE8F0);
        if (prev == 1)
        {
          func_80025B60((((u32) (((s32) (&D_81800000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017E340, &D_0017ED00_2, 0, 4);
        }
        else
        {
          func_80025B60((((u32) (((s32) (&D_81800000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017E340, &D_0017ED00_2, 0, (s32) D_800AE8F0.unk_0002);
        }
      }
      if (D_800AE8F0.unk_1096 & 4)
      {
        Session_InitTwoTrainers(6, 0xA, 0xD);
        D_800AE8F0.unk_0003 = 8;
        func_80025B60((((u32) (((s32) (&D_82100000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017ED00, &D_00232510_2, 0, (s32) &D_800AE8F0);
      }
      if (D_800AE8F0.unk_1096 & 0x20)
      {
        func_80025B60((((u32) (((s32) (&D_81700000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017BE70, &D_0017E340, 0, (s32) &D_800AE8F0);
      }
      }
  }
  D_800733C8 = 0x8040;
}

extern M2C_UNK D_81300000;
extern M2C_UNK D_0015FCE0;
extern s32 D_800733CC;
void func_8000A838(s32);
void func_8000A8DC(void);
void func_8000A904(void);
void GbTower_Start(UnkInputStruct8000D738*);
s32 func_8000ADE8(void);
void func_8000AE1C(UnkInputStruct8000D738*);
void func_800268E4(s32, s32);
void GbSave_ForceReloadPort(s32);
void func_80023C30(void);
void func_80025130(s32);
void Save_CommitTypedRecord(s32, s32);

/** Game state: runs Game Boy Tower. */
void State_GbTower(void) {
    s32 sp2C;
    UnkInputStruct8000D738 sp24;

    main_pool_push_state('EMU0');
    func_8000A838(1);
    Display_WaitForFrames(2);
    func_8000A8DC();

    sp24.unk_04 = main_pool_alloc(sizeof(*sp24.unk_04), 0);

    func_80025B60(((u32) ((s32) &D_81300000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015F8F0, &D_0015FCE0, D_800733D4, (s32) &sp24);
    GbTower_Start(&sp24);

    sp2C = func_8000ADE8();

    func_8000AE1C(&sp24);
    Display_WaitForFrames(2);
    func_8000A904();

    if (sp2C != 0) {
        func_800268E4(D_800733D4, sp2C);
    }

    GbSave_ForceReloadPort(D_800733D4);
    func_80023C30();
    func_80025130(sp24.unk_00);
    Save_CommitTypedRecord(0x14, 0);
    D_800733C8 = D_800733CC;
    D_800AF988 = 1;
    main_pool_pop_state('EMU0');
}

extern s32 D_800733C8;

void func_80026898(void) {
    D_800733C8 = 0x8010;
}

/** Game state: unused 64DD boot sequence. */
void State_N64ddBootUnused(void) {
    Audio_WaitForIdle(1);
    Display_WaitForFrames(2);
    LeoBootGame(D_800AB200.loadAddr);
}

void func_800268DC(void) {
}

/** Powers off the paks, blanks the screen and loads a fragment. */
void Game_ShutdownAndLoadFragment(s32 arg0, s32 arg1) {
    osViBlack(1);
    GbTower_PowerOffAllPaks();
    Audio_FadeOutForShutdown();
    Game_ResetStorageDevice();
    Display_ClearFramebufferLine(1);
    Display_ApplyPendingVideoMode();
    Display_WaitForFrames(0xA);

    main_pool_pop_state('GAME');

    FRAGMENT_LOAD_AND_CALL(FRAGMENT_FATAL_ERROR_SCREEN, arg0, arg1);
}

/** Resets the storage device. */
void Game_ResetStorageDevice(void) {
    Storage_ResetDisk();
}

u32 func_800594D0(u32);
void func_8000B170(s32);
void func_8000D20C(void);
void func_800177DC(void);
void func_80025FDC(void);
void func_80026368(void);
void func_8002677C(void);
void func_800268A8(void);

/**
 * Pushes the 'GAME' pool state and runs the top-level state machine (0x8001, 0x8010, 0x8040, 0x8050, 0x8060, 0x8080, 0xF000) forever.
 * Seen in play (2026-11-13) ran at boot (console reset, then N64 logo, opening, title and main
 * menu).
 * @unverified Name and comment guessed from the code.
 */
void Game_RunStateLoop(s32 arg0) {
    s32 state;

    func_800594D0(0x01000F00);
    func_8000B170(0);
    func_8000D20C();
    func_800177DC();
    func_8000256C(0x47414D45);
    D_800AE8F0.unk_0000 = 1;
    while (1) {
        state = D_800733C8;
        switch (state) {
            case 0x8001:
                func_80025F3C();
                break;
            case 0x8010:
                func_80025FDC();
                break;
            case 0x8040:
                func_800260C4();
                break;
            case 0x8050:
                func_80026368();
                break;
            case 0x8060:
                func_8002677C();
                break;
            case 0x8080:
                func_80026898();
                break;
            case 0xF000:
                func_800268A8();
                break;
        }
        D_800733CC = state;
    }
}

/*
 * func_80026B50
 *
 * Builds a display list that draws a 320x240 RGBA16 image `tex` as a grid of
 * 10 columns by 4 rows of 32x60 texel tiles, centered on (x, y) and scaled to
 * width x height. For each column it loads 32 vertices into the RSP, then for
 * each row it loads that tile into TMEM, writes the tile's four corner
 * vertices into `vtx` (shade 0x00007F, alpha 0xFF) and draws it as two
 * triangles. Returns the display list pointer after gSPEndDisplayList.
 *
 * `vtx` needs room for 10 * 4 * 4 vertices (0xA00 bytes, as func_800270B4
 * allocates).
 *
 * Matching notes: y0/y1 and then ult must be assigned at the top of the row
 * loop, in that order, before the tile load; the texture coordinates of the
 * right/bottom edges are written out inline. That fixes the order uopt numbers
 * its expression temps in, and so the stack temp slots and s-registers.
 */
Gfx* func_80026B50(s16 x, s16 y, s16 z, Vtx* vtx, Gfx* gfx, void* tex, s16 width, s16 height) {
    s32 i;
    s32 j;
    s32 uls;
    s32 ult;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s16 s0;
    s16 t0;

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_DECALRGB, G_CC_PASS2);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    for (i = 0; i < 10; i++) {
        if (tex && tex && tex) {} // FAKE
        gSPVertex(gfx++, vtx, 32, 0);
        x0 = x + i * width / 10 - width / 2;
        x1 = x + (i + 1) * width / 10 - width / 2;
        uls = i * 32;
        s0 = uls << 5;
        for (j = 0; j < 4; j++) {
            y0 = y + height / 2 - j * height / 4;
            y1 = y + height / 2 - (j + 1) * height / 4;
            ult = j * 60;
            gDPLoadTextureTile(gfx++, tex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0, uls, ult, uls + 31, ult + 59, 0,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
            t0 = ult << 5;
            Gfx_SetVertexAttributes(vtx++, x0, y0, z, s0, t0, 0, 0, 0x7F, 0xFF);
            Gfx_SetVertexAttributes(vtx++, x0, y1, z, s0, (ult + 59) << 5, 0, 0, 0x7F, 0xFF);
            Gfx_SetVertexAttributes(vtx++, x1, y1, z, (uls + 31) << 5, (ult + 59) << 5, 0, 0, 0x7F, 0xFF);
            Gfx_SetVertexAttributes(vtx++, x1, y0, z, (uls + 31) << 5, t0, 0, 0, 0x7F, 0xFF);
            gSP2Triangles(gfx++, j * 4, j * 4 + 1, j * 4 + 2, 0, j * 4, j * 4 + 2, j * 4 + 3, 0);
        }
    }
    gSPEndDisplayList(gfx++);
    return gfx;
}

s32 func_800023C4(M2C_UNK, M2C_UNK);                /* extern */
extern s32 D_800733F0;

/*
 * func_800270B4
 *
 * Calls func_800023C4(0xA00, 0) and func_800023C4(0xA70, 0) (they look like
 * allocations, but that is not established here), then calls func_80026B50
 * to build the tiled image display list for texture arg3, with the first
 * result as its vertex buffer and the second as the display list. Stores the
 * second result in D_800733F0 (the word that Display_DisableBlackout clears)
 * and returns it.
 *
 * Matching note: the unused leading `pad1` local only makes the stack frame
 * and slots match the ROM (0x38 bytes, blocks at sp+0x30 and sp+0x2C).
 */
s32 func_800270B4(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s16 arg4, s16 arg5) {
    s32 pad; // FAKE: stack padding
    s32 sp30;
    s32 sp2C;

    sp30 = func_800023C4(0xA00, 0);
    sp2C = func_800023C4(0xA70, 0);
    func_80026B50(arg0, arg1, arg2, (Vtx*)sp30, (Gfx*)sp2C, (void*)arg3, arg4, arg5);
    D_800733F0 = sp2C;
    return sp2C;
}

/** Turns off the screen blackout flag. */
void Display_DisableBlackout(void) {
    D_800733F0 = 0;
}

extern s32 D_800733F0;
volatile long long func_80027140(s32 arg0, s8 *arg1)
{
  s32 new_var; // FAKE: permuter temp
  new_var = arg0;
  if ((new_var == 2) && (D_800733F0 != 0))
  {
    *((s32 *) (((s8 *) arg1) + 0x18)) = (s32) D_800733F0;
  }
}

typedef struct Key80027168 {
    s16 n;
    Vec3s a;
    Vec3s b;
} Key80027168;
typedef struct Obj80027168 {
    s32 unk_00;
    Key80027168* keys;
    Vec3f unk_08;
    Vec3f unk_14;
    Vec3f unk_20;
    Vec3f unk_2C;
    s16 unk_38;
    s16 unk_3A;
} Obj80027168;
Vec3f* Vec3f_FromVec3s(Vec3f* float_vector, Vec3s* int_vector);
Vec3s* Vec3s_Add(Vec3s* dest, Vec3s* a, Vec3s* b);
Vec3s* Vec3s_Subtract(Vec3s* dest, Vec3s* a, Vec3s* subtrahend);

M2C_UNK func_80027168(arg0)
    Obj80027168* arg0;
{
    Vec3s sp30;
    Vec3s sp28;

    if ((arg0->unk_3A = arg0->keys->n) == 0) {
        return 0;
    }
    arg0->unk_38 = 0;
    Vec3s_Add(&sp30, &arg0->keys->a, &arg0->keys->b);
    Vec3s_Subtract(&sp28, &arg0->keys[1].a, &arg0->keys[1].b);
    Vec3f_FromVec3s(&arg0->unk_08, &arg0->keys->a);
    Vec3f_FromVec3s(&arg0->unk_14, &sp30);
    Vec3f_FromVec3s(&arg0->unk_20, &sp28);
    Vec3f_FromVec3s(&arg0->unk_2C, &arg0->keys[1].a);
    arg0->keys++;
    return 1;
}

s32 func_80027214(Obj80027168* arg0, Vec3f* arg1) {
    f32 t;
    f32 u;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (arg0->unk_3A > 0) {
        if ((arg0->unk_38 >= arg0->unk_3A) && (func_80027168(arg0) == 0)) {
            return 0;
        }
        arg0->unk_38++;
        t = (f32)arg0->unk_38 / (f32)arg0->unk_3A;
        if (arg0->unk_00 & 1) {
            t = (-2.0f * t * t * t) + (3.0f * t * t);
        }
        u = 1.0f - t;
        b0 = u * u * u;
        b1 = 3.0f * t * u * u;
        b2 = 3.0f * t * t * u;
        b3 = t * t * t;
        arg1->x = (arg0->unk_2C.x * b3) + ((b0 * arg0->unk_08.x) + (b1 * arg0->unk_14.x) + (b2 * arg0->unk_20.x));
        arg1->y = (arg0->unk_2C.y * b3) + ((b0 * arg0->unk_08.y) + (b1 * arg0->unk_14.y) + (b2 * arg0->unk_20.y));
        arg1->z = (arg0->unk_2C.z * b3) + ((b0 * arg0->unk_08.z) + (b1 * arg0->unk_14.z) + (b2 * arg0->unk_20.z));
    }
    return 1;
}

M2C_UNK func_80027168();                            /* extern */

void func_800273C4(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    func_80027168();
}

M2C_UNK func_80027168();                            /* extern */

void func_800273E8(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 0) = 1;
    func_80027168();
}
