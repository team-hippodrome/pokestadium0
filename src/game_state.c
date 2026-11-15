/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/dp_intro.c, src/game_state.c. */

#include "game_state.h"
#include "asset_archive.h"
#include "audio_music.h"
#include "font.h"
#include "gb_player.h"
#include "gb_player_launch.h"
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
extern s16 gActiveGbPort;
extern s16 gActiveGbPortChanged;
extern unk_D_800AE520 D_800AF990;
extern s32 pad_D_800AE534[2];
SessionContext gSessionContext;

#include "global.h"
#include <PR/os_internal_reg.h>
extern u64 F3DEX2_data_bin[];
extern s32 sImageGridDisplayList;
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
void Game_UnusedStub(void);
void Game_ShutdownAndLoadFragment(s32 arg0, s32 arg1);
void Game_ResetStorageDevice(void);
void ImageGrid_Clear(void);

void Display_ClearFramebufferLine(u16 color);
void Display_WaitForFrames(s32 arg0);
void Display_ApplyPendingVideoMode(void);

typedef struct { u8 b[5]; } Unk5Bytes;
M2C_UNK func_8001FD8C(void *, s32);                 /* extern */
M2C_UNK func_800203FC(void *);                      /* extern */
s32 func_8002057C(s32, s32, s32);                 /* extern */
extern M2C_UNK D_80065D00;
extern M2C_UNK D_8007B7B0;

/**
 * Fills `mon` with a default level 50 Pokémon of species `species`: Pound only, vitamin-cap stat
 * experience and DVs, its species name and the default OT name.
 * Seen in play (2026-11-14): at boot, Session_InitHumanTrainer builds both trainers' demo Pokémon with it
 * (species 3 for both sides).
 */
void Pokemon_CreateDefault(BattleMon *mon, s32 species) {
    u8 *temp_v1;

    mon->species.id = species;
    mon->boxLevel = 0;
    mon->statusCondition = 0;
    mon->type1 = ((u8 *)&D_80065D00)[species * 0x17 - 0x11];
    mon->type2 = ((u8 *)&D_80065D00)[species * 0x17 - 0x10];
    mon->catchRate = 0;
    mon->moves[0] = 1;
    mon->moves[1] = 0;
    mon->moves[2] = 0;
    mon->moves[3] = 0;
    mon->otId = 0;
    mon->statExp[0] = 25600;
    mon->statExp[1] = 25600;
    mon->statExp[2] = 25600;
    mon->statExp[3] = 25600;
    mon->statExp[4] = 25600;
    mon->dvs = 0xFFFF;
    mon->pp[0] = 35;
    mon->pp[1] = 0;
    mon->pp[2] = 0;
    mon->pp[3] = 0;
    mon->exp = func_8002057C(species, 50, species);
    func_800203FC(mon);
    mon->hp = mon->maxHp;
    func_8001FD8C(mon->nickname, species);
    *(Unk5Bytes *)mon->otName = *(Unk5Bytes *)&D_8007B7B0;
}

typedef struct { s32 w[20]; } Unk50Bytes;
extern u8 D_800AAF50[];
extern M2C_UNK D_8007B7B8;

/**
 * Sets up trainer slot `arg1` as a human player on controller port `arg0` with roster info `arg2`.
 * Seen in play (2026-11-13) ran during boot, before the opening (console reset, then N64 logo,
 * opening, title and main menu).
 * @unverified Name and comment guessed from the code.
 */
M2C_UNK Session_InitHumanTrainer(M2C_UNK port, TeamRoster *trainer, ExtendedRosterInfo *roster_info, s32 species) {

    trainer->isHuman = 1;
    trainer->controllerPort = port;
    trainer->controller = (Controller *)(D_800AAF50 + port * 0x24);
    trainer->trainerId = 0;
    trainer->rosterInfo = roster_info;
    trainer->numberOfPokemonBrought = 1;
    *(Unk5Bytes *)trainer->trainerName = *(Unk5Bytes *)&D_8007B7B8;
    Pokemon_CreateDefault(&trainer->pokemonPicked[0], species);
    roster_info->unk_000 = 0;
    roster_info->numberOfPokemonCanBePicked = 1;
    roster_info->trainerIndex = 0;
    roster_info->title[0] = 0;
    roster_info->fullName[0] = 0;
    roster_info->battleMon[0] = trainer->pokemonPicked[0];
}

/**
 * Resets battle side `side` to one trainer, `trainer`, with no model loaded and no tag team.
 * Seen in play (2026-11-14): at boot, Session_InitTwoTrainers sets up both sides with it.
 */
void BattleSide_InitSingleTrainer(BattleSide *side, TeamRoster *trainer) {
    side->modelFlags = 0;
    side->tagTeamSize = 1;
    side->displayModel = 0;
    side->displayMon = NULL;
    side->loadedModel = NULL;
    side->teamMember[0] = trainer;
    side->teamMember[1] = NULL;
    side->backgroundLoadFlags = 0;
    side->backgroundFileList = 0;
}

M2C_UNK Session_InitHumanTrainer(M2C_UNK, TeamRoster *, ExtendedRosterInfo *, s32);

/**
 * Sets the session mode to `arg0` and sets up both trainer slots and battle sides.
 * Seen in play (2026-11-13) ran during boot, before the opening (console reset, then N64 logo,
 * opening, title and main menu).
 * @unverified Name and comment guessed from the code.
 */
M2C_UNK Session_InitTwoTrainers(M2C_UNK mode, M2C_UNK species1, M2C_UNK species2) {
    gSessionContext.mode = mode;
    gSessionContext.ruleCategory = 1;
    gSessionContext.roundOrDemoId = 1;
    Session_InitHumanTrainer(0, &gSessionContext.trainerSlots[0], &gSessionContext.rosterInfo[0], species1);
    Session_InitHumanTrainer(1, &gSessionContext.trainerSlots[1], &gSessionContext.rosterInfo[1], species2);
    BattleSide_InitSingleTrainer(&gSessionContext.battleSides[0], &gSessionContext.trainerSlots[0]);
    BattleSide_InitSingleTrainer(&gSessionContext.battleSides[1], &gSessionContext.trainerSlots[1]);
}

/*
 * Session_LoadPortSnapshot
 *
 * If arg0 is a valid controller-port index (0 to 3), copies that port's
 * save snapshot into the buffer at gSessionGbSnapshot with GbSave_CopyPortSnapshot
 * (its return value is ignored).  Otherwise the first byte of the buffer is
 * cleared.  The buffer is the destination that Tournament_SaveContinueData later passes on
 * as its second argument to Save_WriteContinueData.
 */
extern GbSavePortSnapshot gSessionGbSnapshot;

/**
 * Copies the GB save snapshot of port `arg0` into the session; clears it for an invalid port.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Session_LoadPortSnapshot(s32 port) {
    if ((port >= 0) && (port < 4)) {
        GbSave_CopyPortSnapshot(port, &gSessionGbSnapshot);
        return;
    }
    gSessionGbSnapshot.gameType = 0;
}


/**
 * Saves the current tournament (mode, cup, next round, opponents, team, GB snapshot) to the continue
 * record and commits it.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): ran on ちゅうだんする (Suspend) at トーナメントをつづけますか？ ("Continue the tournament?")
 */
void Tournament_SaveContinueData(void) {
    SaveContinueSession sp1C;
    ExtendedRosterInfo* info = gSessionContext.battleSides[0].teamMember[0]->rosterInfo;

    sp1C.mode = gSessionContext.mode;
    sp1C.modeSelection = gSessionContext.modeSelection;
    sp1C.round = gSessionContext.roundOrDemoId + 1;
    _bcopy(gSessionContext.opponentHistory, sp1C.opponentHistory, 8);
    Save_WriteContinueData(&sp1C, &gSessionGbSnapshot, info->battleMon, info->numberOfPokemonCanBePicked);
    Save_CommitTypedRecord(0x15, 0);
}

M2C_UNK func_80058410();
extern SaveContinueSession gContinueSession;

/**
 * Copies the mode, cup, round and opponent history of a saved tournament (gContinueSession, read by
 * Tournament_LoadContinueData) back into gSessionContext.
 * State_Battle calls it when the session is flagged as resumed.
 * @unverified Name and comment read from the code; not reached in play.
 */
void Session_RestoreContinueSession(void) {
    gSessionContext.mode = (u8) gContinueSession.mode;
    gSessionContext.ruleCategory = (u8) gContinueSession.mode;
    gSessionContext.modeSelection = (u8) gContinueSession.modeSelection;
    gSessionContext.roundOrDemoId = (u8) gContinueSession.round;
    func_80058410(gContinueSession.opponentHistory, gSessionContext.opponentHistory, 8, &gContinueSession);
}

typedef struct { u8 b[3]; } Unk3Bytes;
typedef struct { u8 b[11]; } Unk11Bytes;
M2C_UNK func_8000A460(M2C_UNK *, M2C_UNK *);
s32 GbSave_GetTrainerId(s32 arg0);
extern s16 gActiveGbPort;
extern M2C_UNK D_8007B7C0;
extern M2C_UNK D_8007B7C4;


/**
 * Sets up trainer slot 0 for a resumed tournament: human on port 0, its saved team copied into the
 * roster. `isGbTeam` is the first byte of the saved GB snapshot: when it is set and the GB pak is on
 * port 0, the trainer ID and name come from the cartridge, otherwise the default name is used.
 * @unverified Name and comment read from the code; not reached in play.
 */
void Session_InitContinueTrainer(s32 is_gb_team)
{
  SessionContext *st = &gSessionContext;
  st->trainerSlots[0].isHuman = 1;
  st->trainerSlots[0].controllerPort = 0;
  st->trainerSlots[0].controller = gPlayer1Controller;
  st->trainerSlots[0].rosterInfo = &st->rosterInfo[0];
  if ((is_gb_team != 0) && (gActiveGbPort == 0))
  {
    st->trainerSlots[0].trainerId = GbSave_GetTrainerId(gActiveGbPort);
    GbSave_GetPlayerName(gActiveGbPort, (M2C_UNK *) st->trainerSlots[0].trainerName);
  }
  else
  {
    st->trainerSlots[0].trainerId = 0;
    *((Unk3Bytes *) st->trainerSlots[0].trainerName) = *((Unk3Bytes *) (&D_8007B7C0));
  }
  st->rosterInfo[0].unk_000 = 0;
  st->rosterInfo[0].numberOfPokemonCanBePicked = st->trainerSlots[0].numberOfPokemonBrought;
  st->rosterInfo[0].trainerIndex = 0;
  func_80058410(st->trainerSlots[0].pokemonPicked, st->rosterInfo[0].battleMon, 0x1E0);
  *((Unk11Bytes *) st->rosterInfo[0].title) = *((Unk11Bytes *) (&D_8007B7C4));
  func_8000A460(st->rosterInfo[0].fullName, st->trainerSlots[0].trainerName);
  BattleSide_InitSingleTrainer(&st->battleSides[0], &st->trainerSlots[0]);
}

s8 Save_ReadContinueData(M2C_UNK *, s8 *, M2C_UNK *);       /* extern */
void Session_InitContinueTrainer(s32);                          /* extern */
s32 func_80057910(s8 *, M2C_UNK *, M2C_UNK);        /* extern */

/**
 * Loads the continue record. A rental team is always accepted; a GB team only if the cartridge's
 * 0x162-byte snapshot is unchanged. Returns 1 and flags the session when the tournament can be resumed.
 * Matching: the unused pad local sits between the buffer and ret as in the ROM's frame, and the bit-0
 * update comes before the 0xFF store to match the register order.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): the main menu asked
 * トーナメントのつづきをする？ ("Continue the tournament?") after a saved round.
 */
s32 Tournament_LoadContinueData(void) {
    s8 buf[354];
    UNUSED s32 pad; // FAKE: stack padding
    s32 ret;
    s8 temp_v0;

    ret = 0;
    gSessionContext.sessionFlags = 0U;
    temp_v0 = Save_ReadContinueData(&gContinueSession, buf, gSessionContext.trainerSlots[0].pokemonPicked);
    if (temp_v0 != -1) {
        gSessionContext.trainerSlots[0].numberOfPokemonBrought = temp_v0;
        if (buf[0] == 0) {
            Session_InitContinueTrainer(buf[0]);
            gSessionContext.sessionFlags = (u8) (gSessionContext.sessionFlags | 1);
            gSessionContext.teamGbPort = 0xFF;
            Session_LoadPortSnapshot(-1);
            ret = 1;
        } else if ((gActiveGbPort >= 0) && (gActiveGbPort < 4) && (GbSave_CopyPortSnapshot(gActiveGbPort, &gSessionGbSnapshot) != 0) && (func_80057910(buf, &gSessionGbSnapshot, 0x162) == 0)) {
            Session_InitContinueTrainer(buf[0]);
            gSessionContext.sessionFlags = (u8) (gSessionContext.sessionFlags | 1);
            gSessionContext.teamGbPort = (s8) gActiveGbPort;
            Session_LoadPortSnapshot((s32) gActiveGbPort);
            ret = 1;
        }
    }
    return ret;
}

/** Loads a fragment from a ROM range and calls its entry point. */
s32 Fragment_LoadAndCall(s32 arg0, u8* rom_start, u8* rom_end, u32 arg3, u32 arg4) {
    s32 result;
    FragmentEntry func;

    func = Fragment_Load(arg0, rom_start, rom_end);

    result = func(arg3, arg4);

    MainPool_TryFree(func);

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
    return gActiveGbPort;
}

/** Sets the active Game Boy save port when it is in range. */
void GbSave_SetActivePort(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4)) {
        gActiveGbPort = arg0;
        gActiveGbPortChanged = 1;
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
    Ui_DrawGradientPanel(144, 100, 352, 200, &sp2C, &sp28);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(8, -2);
    Font_Printf(176, 180, D_8007B7D0);
    Font_Printf(176, 208, D_8007B7E0);
    Font_Printf(176, 236, D_8007B804);
    Font_Printf(176, 264, D_8007B824);
    Gfx_SetEnvColor(0xFF, 0xFF, 0, 0xFF); // #FFFF00
    Font_Printf(302, 180, D_8007B844);
    if (arg0 == 2) {
        Font_SetActive(0x10, -2);
        Font_Printf(188, 132, D_8007B858);
    } else if (arg0 == 3) {
        Font_Printf(176, 116, D_8007B874);
        Font_Printf(176, 144, D_8007B894);
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
    Ui_DrawGradientPanel(144, 150, 352, 56, &sp2C, &sp28);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(0x10, -2);
    Font_Printf(221, 166, D_8007B8B4);
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
extern s32 gNextGameState;
extern M2C_UNK D_81500000;
extern M2C_UNK D_82100000;

/**
 * Game state 0x8001: runs the N64 logo fragment, then the opening demo battle (mode 5) in the battle
 * fragment, and moves on to the title screen (0x8010).
 * Seen in play (2026-11-14): the first state after reset; it loaded fragment slot 5 (N64 logo) and then
 * slot 0x11 (battle) with the opening battle on screen.
 */
void State_Boot(void) {
    func_80025B60(((u32) ((s32) &D_81500000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015F390, &D_0015F8F0, 0, 0);
    Session_InitTwoTrainers(5, 3, 3);
    func_80025B60(((u32) ((s32) &D_82100000 & 0x0FF00000) >> 0x14) - 0x10, &D_0017ED00, &D_00232510, 0, (s32) &gSessionContext);
    gNextGameState = 0x8010;
}

extern M2C_UNK D_81200000;
extern M2C_UNK D_0015E220;
extern s32 D_800AF988;

/**
 * Game state 0x8010: runs the title screen fragment (slot 2). It returns 0x8010 to play the attract demo
 * battle, 0x8020 for Start (to the main menu, 0x8040) or 0xF000 for the 64DD boot.
 * Seen in play (2026-11-14): runs while ポケモンスタジアム (Pokémon Stadium) / PUSH START is on screen, after the opening.
 */
void State_TitleScreen(void) {
    gNextGameState = func_80025B60(((u32) ((s32) &D_81200000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015E220, &D_0015F390, 0, 0);
    gSessionContext.modeSelection = 0;
    gSessionContext.transitionFlags = 0;
    switch (gNextGameState) {
        case 0x8010:
            func_80025B60(((u32) ((s32) &D_82100000 & 0x0FF00000) >> 0x14) - 0x10, &D_0017ED00, &D_00232510, 0, (s32) &gSessionContext);
            break;
        case 0x8020:
            gActiveGbPort = -1;
            D_800AF988 = 0;
            gNextGameState = 0x8040;
            break;
        default:
            gActiveGbPort = 0;
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
extern StageContext *D_800AF9A4;
s32 GbSave_LoadPort(s32 arg0);
s32 GbSave_InitializeBoxesAndWrite(s32);
void GbSave_ValidateBeforeWrite(s32);
void GbSave_RequirePakPresent(s32);
u8 GbSave_GetSaveState(s32 arg0);
s32 GbSave_GetBoxCount(s32);
void Save_LoadSram(void);
void Save_RunGbReportErrorScreen(s32);
/**
 * Game state 0x8040: loads the save, then runs the queued menu fragments (cartridge check, main menu and
 * the modes it opens) until one returns a state other than 0x8040. Reloads the GB save when the
 * active port changes.
 * Seen in play (2026-11-14): every main menu mode (Pokédex, party, organize, list, registration) and
 * the GB cartridge select screen ran with the game state at 0x8040.
 */
void State_MainMenu(void)
{
  s32 pushed = 0;
  MainPool_PushState('OVLY');
  Save_LoadSram();
  Gfx_InitDisplayListBuffers(0x10000, 0);
  D_800AF9A4 = StageContext_Allocate(1, 1, 2, 0, 2, 1);
  StageContext_Activate(D_800AF9A4);
  if ((gSessionContext.transitionFlags & 1) && (!(gSessionContext.transitionFlags & 2)))
  {
    gSessionContext.transitionFlags |= 0x100;
  }
  gActiveGbPortChanged = 0;
  if ((D_800AF988 != 0) || (gSessionContext.transitionFlags & 0x100))
  {
    D_800AF988 = 0;
    GbSave_SetActivePort(gActiveGbPort);
    Fragment_QueueCall((((u32) (((s32) (&D_88000000)) & 0x0FF00000)) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, (s32) (&gSessionContext));
  }
  else
  {
    Fragment_QueueCall((((u32) (((s32) (&D_88400000)) & 0x0FF00000)) >> 0x14) - 0x10, D_00162BE0, D_00166580, 0, (s32) (&gSessionContext));
  }
  Tournament_LoadContinueData();
  while ((gNextGameState == 0x8040) && (D_800AF990.unk_00 != 0))
  {
    if (gActiveGbPortChanged != 0)
    {
      gActiveGbPortChanged = 0;
      if (GbSave_GetSaveState(gActiveGbPort) == 0)
      {
        if (pushed)
        {
          MainPool_PopState('BUDT');
        }
        pushed = 1;
        MainPool_PushState('BUDT');
        GbSave_LoadPort(gActiveGbPort);
        if (GbSave_GetBoxCount(gActiveGbPort) == 0)
        {
          GbSave_ValidateBeforeWrite(gActiveGbPort);
          while (GbSave_InitializeBoxesAndWrite(gActiveGbPort) == 0)
          {
            Save_RunGbReportErrorScreen(gActiveGbPort);
          }

          GbSave_RequirePakPresent(gActiveGbPort);
        }
        Tournament_LoadContinueData();
      }
    }
    D_800AF990.unk_00 = 0;
    gNextGameState = Fragment_LoadAndCall(D_800AF990.fragment_id, D_800AF990.rom_start, D_800AF990.rom_end, D_800AF990.arg0, D_800AF990.arg1);
  }

  gSessionContext.transitionFlags = (!(gSessionContext.transitionFlags & 2)) * 0;
  StageContext_Deactivate();
  Gfx_FreeDisplayListBuffers();
  MainPool_PopState('OVLY');
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

/**
 * Game state 0x8050: runs a battle session. Loads the cup/rule select and order select fragments and
 * the battle fragment in a loop until the session ends, then the Pikachu reward and award screens when
 * the session flags ask for them, and returns to the main menu (0x8040).
 * Seen in play (2026-11-14): a Free Battle COM match ran with the game state at 0x8050.
 * @unverified The tournament and reward branches were not reached in play.
 */
void State_Battle(void)
{
  s32 prev;
  TeamRoster *roster;
  ExtendedRosterInfo *info;
  func_80001948(0xFFFF);
  if (gSessionContext.sessionFlags & 2)
  {
    Session_RestoreContinueSession();
  }
  else
  {
    gSessionContext.roundOrDemoId = 1;
  }
  if (gSessionContext.mode == 0)
  {
    gSessionContext.roundOrDemoId = 1;
    func_80025B60((((u32) (((s32) (&D_82200000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00232510, &D_00235D70, 0, (s32) &gSessionContext);
    func_80025B60((((u32) (((s32) (&D_82300000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0015FCE0, &D_00162BE0, 0, (s32) &gSessionContext);
    func_80025B60((((u32) (((s32) (&D_82100000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017ED00, &D_00232510_2, 0, (s32) &gSessionContext);
    func_80025B60((((u32) (((s32) (&D_82200000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00232510, &D_00235D70, 1, (s32) &gSessionContext);
  }
  else
  {
    prev = gSessionContext.mode;
    func_80025B60((((u32) (((s32) (&D_82200000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00232510, &D_00235D70, 0, (s32) &gSessionContext);
    while (!(gSessionContext.transitionFlags & 1))
    {
      func_80025B60((((u32) (((s32) (&D_82300000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0015FCE0, &D_00162BE0, 0, (s32) &gSessionContext);
      func_80025B60((((u32) (((s32) (&D_82100000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017ED00, &D_00232510_2, 0, (s32) &gSessionContext);
      func_80025B60((((u32) (((s32) (&D_82200000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00232510, &D_00235D70, 2, (s32) &gSessionContext);
    }

    if (gSessionContext.transitionFlags & 0x40)
    {
      gNextGameState = 0x8010;
      return;
    }
    else
    {
      if (gSessionContext.transitionFlags & 2)
      {
        roster = gSessionContext.battleSides[0].teamMember[0];
        gSessionContext.mode = 4;
        info = roster->rosterInfo;
        roster->numberOfPokemonBrought = info->numberOfPokemonCanBePicked;
        _bcopy(info->battleMon, roster->pokemonPicked, 0x1E0);
        func_80025B60((((u32) (((s32) (&D_82100000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017ED00, &D_00232510_2, 0, (s32) &gSessionContext);
        if (prev == 1)
        {
          func_80025B60((((u32) (((s32) (&D_81800000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017E340, &D_0017ED00_2, 0, 4);
        }
        else
        {
          func_80025B60((((u32) (((s32) (&D_81800000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017E340, &D_0017ED00_2, 0, (s32) gSessionContext.modeSelection);
        }
      }
      if (gSessionContext.transitionFlags & 4)
      {
        Session_InitTwoTrainers(6, 0xA, 0xD);
        gSessionContext.roundOrDemoId = 8;
        func_80025B60((((u32) (((s32) (&D_82100000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017ED00, &D_00232510_2, 0, (s32) &gSessionContext);
      }
      if (gSessionContext.transitionFlags & 0x20)
      {
        func_80025B60((((u32) (((s32) (&D_81700000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_0017BE70, &D_0017E340, 0, (s32) &gSessionContext);
      }
      }
  }
  gNextGameState = 0x8040;
}

extern M2C_UNK D_81300000;
extern M2C_UNK D_0015FCE0;
extern s32 gPrevGameState;
void func_8000A838(s32);
void func_8000A8DC(void);
void func_8000A904(void);
void GbPlayer_Start(GbPlayerLaunchParams*);
s32 GbPlayer_WaitForExit(void);
void func_8000AE1C(GbPlayerLaunchParams*);
void func_800268E4(s32, s32);
void GbSave_ForceReloadPort(s32);
void Save_LoadSram(void);
void Save_SetGbPlayerButtonConfig(s32);
void Save_CommitTypedRecord(s32, s32);

/** Game state: runs Game Boy Tower. */
void State_GbPlayer(void) {
    s32 sp2C;
    GbPlayerLaunchParams sp24;

    MainPool_PushState('EMU0');
    func_8000A838(1);
    Display_WaitForFrames(2);
    func_8000A8DC();

    sp24.partyIcons = MainPool_Alloc(sizeof(*sp24.partyIcons), 0);

    func_80025B60(((u32) ((s32) &D_81300000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015F8F0, &D_0015FCE0, gActiveGbPort, (s32) &sp24);
    GbPlayer_Start(&sp24);

    sp2C = GbPlayer_WaitForExit();

    func_8000AE1C(&sp24);
    Display_WaitForFrames(2);
    func_8000A904();

    if (sp2C != 0) {
        func_800268E4(gActiveGbPort, sp2C);
    }

    GbSave_ForceReloadPort(gActiveGbPort);
    Save_LoadSram();
    Save_SetGbPlayerButtonConfig(sp24.buttonConfig);
    Save_CommitTypedRecord(0x14, 0);
    gNextGameState = gPrevGameState;
    D_800AF988 = 1;
    MainPool_PopState('EMU0');
}

extern s32 gNextGameState;

/**
 * Game state 0x8080: goes back to the title screen state (0x8010).
 * @unverified Not reached in play: OFF on the main menu went back to the cartridge select screen
 * without leaving state 0x8040.
 */
void State_ReturnToTitle(void) {
    gNextGameState = 0x8010;
}

/** Game state: unused 64DD boot sequence. */
void State_N64ddBootUnused(void) {
    Audio_WaitForIdle(1);
    Display_WaitForFrames(2);
    LeoBootGame(D_800AB200.loadAddr);
}

/**
 * Empty function with no callers.
 */
void Game_UnusedStub(void) {
}

/** Powers off the paks, blanks the screen and loads a fragment. */
void Game_ShutdownAndLoadFragment(s32 arg0, s32 arg1) {
    osViBlack(1);
    GbPlayer_PowerOffAllPaks();
    Audio_FadeOutForShutdown();
    Game_ResetStorageDevice();
    Display_ClearFramebufferLine(1);
    Display_ApplyPendingVideoMode();
    Display_WaitForFrames(0xA);

    MainPool_PopState('GAME');

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
void State_Battle(void);
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
    gSessionContext.mode = 1;
    while (1) {
        state = gNextGameState;
        switch (state) {
            case 0x8001:
                State_Boot();
                break;
            case 0x8010:
                func_80025FDC();
                break;
            case 0x8040:
                State_MainMenu();
                break;
            case 0x8050:
                State_Battle();
                break;
            case 0x8060:
                func_8002677C();
                break;
            case 0x8080:
                State_ReturnToTitle();
                break;
            case 0xF000:
                func_800268A8();
                break;
        }
        gPrevGameState = state;
    }
}

/*
 * ImageGrid_BuildDisplayList
 *
 * Builds a display list that draws a 320x240 RGBA16 image `tex` as a grid of
 * 10 columns by 4 rows of 32x60 texel tiles, centered on (x, y) and scaled to
 * width x height. For each column it loads 32 vertices into the RSP, then for
 * each row it loads that tile into TMEM, writes the tile's four corner
 * vertices into `vtx` (shade 0x00007F, alpha 0xFF) and draws it as two
 * triangles. Returns the display list pointer after gSPEndDisplayList.
 *
 * `vtx` needs room for 10 * 4 * 4 vertices (0xA00 bytes, as ImageGrid_Create
 * allocates).
 *
 * Matching notes: y0/y1 and then ult must be assigned at the top of the row
 * loop, in that order, before the tile load; the texture coordinates of the
 * right/bottom edges are written out inline. That fixes the order uopt numbers
 * its expression temps in, and so the stack temp slots and s-registers.
 */
Gfx* ImageGrid_BuildDisplayList(s16 x, s16 y, s16 z, Vtx* vtx, Gfx* gfx, void* tex, s16 width, s16 height) {
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
extern s32 sImageGridDisplayList;

/**
 * Allocates a vertex buffer and a display list, builds the tiled 320x240 image `tex` into them with
 * ImageGrid_BuildDisplayList and keeps the display list in sImageGridDisplayList for
 * ImageGrid_GeoCallback to draw. Returns the display list.
 * Called by the VS scene for its trainer name images.
 * @unverified Name read from the code; not hit in the battle tour.
 */
s32 ImageGrid_Create(s16 x, s16 y, s16 z, s32 tex, s16 width, s16 height) {
    s32 pad; // FAKE: stack padding
    s32 sp30;
    s32 sp2C;

    sp30 = func_800023C4(0xA00, 0);
    sp2C = func_800023C4(0xA70, 0);
    ImageGrid_BuildDisplayList(x, y, z, (Vtx*)sp30, (Gfx*)sp2C, (void*)tex, width, height);
    sImageGridDisplayList = sp2C;
    return sp2C;
}

/**
 * Forgets the display list made by ImageGrid_Create.
 * @unverified Name read from the code.
 */
void ImageGrid_Clear(void) {
    sImageGridDisplayList = 0;
}

extern s32 sImageGridDisplayList;
/**
 * Geo layout callback: on the draw pass (`stage` 2), points the node's display list at the one built
 * by ImageGrid_Create.
 * Seen in play (2026-11-14): called from Geo_ProcessNodeChildren with stage 2 during a COM battle.
 */
volatile long long ImageGrid_GeoCallback(s32 stage, s8 *node) // FAKE: volatile long long return type on a void callback
{
  s32 new_var; // FAKE: permuter temp
  new_var = stage; // FAKE: permuter temp
  if ((new_var == 2) && (sImageGridDisplayList != 0)) // FAKE: permuter temp
  {
    *((s32 *) (((s8 *) node) + 0x18)) = (s32) sImageGridDisplayList; // FAKE: cast chain, node + 0x18 is the display list field
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

/**
 * Loads the next segment of a Bezier path. Each key holds a frame count, a point and a tangent; the
 * segment runs from key.point through key.point + key.tangent and next.point - next.tangent to
 * next.point. Returns 0 when the key list ends (frame count 0).
 * @unverified Name read from the code.
 */
M2C_UNK BezierPath_LoadNextSegment(path)
    Obj80027168* path;
{
    Vec3s sp30;
    Vec3s sp28;

    if ((path->unk_3A = path->keys->n) == 0) {
        return 0;
    }
    path->unk_38 = 0;
    Vec3s_Add(&sp30, &path->keys->a, &path->keys->b);
    Vec3s_Subtract(&sp28, &path->keys[1].a, &path->keys[1].b);
    Vec3f_FromVec3s(&path->unk_08, &path->keys->a);
    Vec3f_FromVec3s(&path->unk_14, &sp30);
    Vec3f_FromVec3s(&path->unk_20, &sp28);
    Vec3f_FromVec3s(&path->unk_2C, &path->keys[1].a);
    path->keys++;
    return 1;
}

/**
 * Advances a Bezier path by one frame and writes the position to `out`. With bit 0 of the flags
 * the time is eased (smoothstep). Returns 0 once the last segment is done.
 * Used by the cartridge check and VS scene camera moves.
 * @unverified Name read from the code.
 */
s32 BezierPath_Step(Obj80027168* path, Vec3f* out) {
    f32 t;
    f32 u;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (path->unk_3A > 0) {
        if ((path->unk_38 >= path->unk_3A) && (BezierPath_LoadNextSegment(path) == 0)) {
            return 0;
        }
        path->unk_38++;
        t = (f32)path->unk_38 / (f32)path->unk_3A;
        if (path->unk_00 & 1) {
            t = (-2.0f * t * t * t) + (3.0f * t * t);
        }
        u = 1.0f - t;
        b0 = u * u * u;
        b1 = 3.0f * t * u * u;
        b2 = 3.0f * t * t * u;
        b3 = t * t * t;
        out->x = (path->unk_2C.x * b3) + ((b0 * path->unk_08.x) + (b1 * path->unk_14.x) + (b2 * path->unk_20.x));
        out->y = (path->unk_2C.y * b3) + ((b0 * path->unk_08.y) + (b1 * path->unk_14.y) + (b2 * path->unk_20.y));
        out->z = (path->unk_2C.z * b3) + ((b0 * path->unk_08.z) + (b1 * path->unk_14.z) + (b2 * path->unk_20.z));
    }
    return 1;
}

M2C_UNK BezierPath_LoadNextSegment();                            /**
 * Starts a Bezier path over the keys at `keys` with linear time.
 * @unverified Name read from the code.
 */
void BezierPath_InitLinear(s8 *path, s32 keys) {
    M2C_FIELD(path, s32 *, 4) = keys;
    M2C_FIELD(path, s32 *, 0) = 0;
    BezierPath_LoadNextSegment();
}

M2C_UNK BezierPath_LoadNextSegment();                            /**
 * Starts a Bezier path over the keys at `keys` with eased (smoothstep) time.
 * @unverified Name read from the code.
 */
void BezierPath_InitEased(s8 *path, s32 keys) {
    M2C_FIELD(path, s32 *, 4) = keys;
    M2C_FIELD(path, s32 *, 0) = 1;
    BezierPath_LoadNextSegment();
}
