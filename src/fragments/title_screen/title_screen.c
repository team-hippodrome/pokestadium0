/* Stadium Zero fragment002_15E220: the title screen. */

#include "global.h"
#include "m2c_macros.h"
#include "title_screen.h"
#include "leo.h"

s32 func_8000B2E8(void);
void Font_BeginTranslucentTextRendering(void);
void Font_SetActive(s32 mask, s32 arg1);
void Font_DrawCharAt(s32 x, s32 y, s32 chr);
void Font_EndTexturedTextRendering(void);
extern s16 sNoControllerMessage[];
extern s32 sNoControllerScroll;

/**
 * Scrolls コントローラ１がせつぞくされていません。でんげんをきって、コントローラを
 * コントローラコネクタ１にさしこんでください。 ("Controller 1 is not connected. Turn the
 * power off and plug a controller into controller connector 1.") right to left along the
 * PUSH START line, one pixel per frame, while bit 0 of func_8000B2E8() is clear.
 * Seen in play (2026-11-14): with func_8000B2E8 patched to return 0 on the title screen, PUSH START
 * gave way to this message (scrolling).
 */
void TitleScreen_DrawNoControllerTicker(void) {
    s32 unused; // FAKE: stack padding
    s32 len;
    s32 x;
    s32 idx;
    s32 i;

    if (!(func_8000B2E8() & 1)) {
        len = strlen((const char*)sNoControllerMessage) >> 1;
        x = 16 - (sNoControllerScroll % 16);
        idx = sNoControllerScroll / 16;
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 16, 0, 304, 240);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(4, 0);
        for (i = 0; i < 19; i++) {
            Font_DrawCharAt(x, 0xC0, sNoControllerMessage[idx]);
            idx++;
            if (len - 1 < idx) {
                idx = 0;
            }
            x += 16;
        }
        Font_EndTexturedTextRendering();
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
        sNoControllerScroll++;
        if (sNoControllerScroll >= len * 16) {
            sNoControllerScroll = 0;
        }
    }
}

u32 osGetCount(void);
f32 MathUtil_Random_ZeroOne(void);
void Session_InitTwoTrainers(s32, s32, s32);
extern u8 sDemoBattleSpecies[];

/**
 * Sets up the attract-mode demo battle: two different species picked at random from
 * sDemoBattleSpecies (the Pokédex numbers of Zero's 40 battle species), in session mode 3.
 * The random generator is first stepped osGetCount() & 0xFF times.
 * Seen in play (2026-11-14): left idle on the title screen, it ran at title frame 1102 and passed
 * 131 and 145; the demo battle that followed was Lapras against Zapdos.
 */
void TitleScreen_SetupDemoBattle(void) {
    s32 first;
    s32 second;

    first = osGetCount() & 0xFF;
    while (first-- > 0) {
        MathUtil_Random_ZeroOne();
    }

    first = MathUtil_Random_ZeroOne() * 40.0f;
    do {
        second = MathUtil_Random_ZeroOne() * 40.0f;
    } while (first == second);

    Session_InitTwoTrainers(3, sDemoBattleSpecies[first], sDemoBattleSpecies[second]);
}

extern char sDiskErrorCodeText1[];
extern char sDiskErrorReadManualText[];
extern char sDiskErrorCodeText2[];
extern char sDiskErrorAccessLampText1[];
extern char sDiskErrorAccessLampText2[];
extern char sDiskErrorReinsertText[];
extern char sDiskErrorCodeText3[];
extern char sDiskErrorEjectButtonText[];
extern char sDiskErrorRemoveDiskText[];
extern char sDiskErrorInsertFirmlyText[];
extern char sDiskErrorCodeText4[];
extern char sDiskErrorExpansionPakText1[];
extern char sDiskErrorExpansionPakText2[];
extern char sDiskErrorSeeManualText1[];
extern char sDiskErrorSeeManualText2[];
extern char sDiskErrorWrongDiskText1[];
extern char sDiskErrorWrongDiskText2[];
extern char sDiskErrorPleaseCheckText[];
void Ui_DrawPrimColorRect(s32, s32, s32, s32, s32, s32, s32, s32);

/**
 * Draws the 64DD disk error box over the title screen. `bootError` is the low halfword of
 * Leo_RunBootStateMachine's result: LeoBootState.errorKind << 8 | LeoBootState.leoError.
 * Kind 0 draws nothing. Kinds 1-4 start with エラー：%2d (Error: leoError):
 *   1: "Please read the instruction manual."
 *   2: "Caution: do not remove the disk while the access lamp is blinking.
 *       Please insert the disk again."
 *   3: "The eject button may have been pressed. Remove the disk once and insert it firmly."
 *   4: "Is the Expansion Pak inserted correctly? See the instruction manual for details."
 *   5 (no code): "The wrong disk may have been inserted. Please check."
 * Seen in play (2026-11-14): called every title frame with 0 (no disk). Poking
 * LeoBootState.errorKind/leoError (D_800AB210 +2/+4) to 1-5 showed each box; kind 2 with
 * leoError 23 showed エラー：23 and the access-lamp warning.
 */
void TitleScreen_DrawDiskError(s32 bootError) {
    s32 kind = (bootError >> 8) & 0xFF;
    s32 pad[1]; // FAKE: stack padding

    if (kind != 0) {
        Ui_DrawPrimColorRect(0x1E, 0x5F, 0x104, 0x5F, 0, 0, 0, 0x96);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, -2);
        switch (kind) {
            case 1:
                Font_Printf(0x32, 0x64, sDiskErrorCodeText1, bootError & 0xFF);
                Font_Printf(0x3C, 0x87, sDiskErrorReadManualText);
                break;
            case 2:
                Font_Printf(0x32, 0x64, sDiskErrorCodeText2, bootError & 0xFF);
                Font_Printf(0x3C, 0x7D, sDiskErrorAccessLampText1);
                Font_Printf(0x6E, 0x8C, sDiskErrorAccessLampText2);
                Font_Printf(0x41, 0xA5, sDiskErrorReinsertText);
                break;
            case 3:
                Font_Printf(0x32, 0x64, sDiskErrorCodeText3, bootError & 0xFF);
                Font_Printf(0x2D, 0x7D, sDiskErrorEjectButtonText);
                Font_Printf(0x69, 0x96, sDiskErrorRemoveDiskText);
                Font_Printf(0x5A, 0xA5, sDiskErrorInsertFirmlyText);
                break;
            case 4:
                Font_Printf(0x32, 0x64, sDiskErrorCodeText4, bootError & 0xFF);
                Font_Printf(0x5F, 0x73, sDiskErrorExpansionPakText1);
                Font_Printf(0x50, 0x82, sDiskErrorExpansionPakText2);
                Font_Printf(0x41, 0x9B, sDiskErrorSeeManualText1);
                Font_Printf(0x7D, 0xAA, sDiskErrorSeeManualText2);
                break;
            case 5:
                Font_Printf(0x46, 0x73, sDiskErrorWrongDiskText1);
                Font_Printf(0x50, 0x82, sDiskErrorWrongDiskText2);
                Font_Printf(0x69, 0xA5, sDiskErrorPleaseCheckText);
                break;
        }
        Font_EndTexturedTextRendering();
    }
}

extern s32 sTitleBackgroundImage;

/**
 * Draws the full-screen title picture (logo, Poké Ball, lightning and Pokémon), a 320x240 YUV
 * image, as 16x16 texture rectangles, 0x200 bytes each, row by row.
 * Seen in play (2026-11-14): overwriting the sixth row of tiles in sTitleBackgroundImage blanked
 * the band across the logo's "POCKET MONSTERS STADIUM" subtitle.
 */
void TitleScreen_DrawBackground(void) {
    u8* image = (u8*)sTitleBackgroundImage;
    s32 y;
    s32 x;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPSetCombine(gDisplayListHead++, 0x17FE2F, 0x77FCF87C);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_CONV);
    gDPSetConvert(gDisplayListHead++, G_CV_K0, G_CV_K1, G_CV_K2, G_CV_K3, G_CV_K4, G_CV_K5);
    gDPPipeSync(gDisplayListHead++);

    for (y = 0; y < 0xF0; y += 0x10) {
        for (x = 0; x < 0x140; x += 0x10) {
            gDPLoadTextureBlockYuv(gDisplayListHead++, image, G_IM_FMT_YUV, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 0x10) << 2, (y + 0x10) << 2, G_TX_RENDERTILE,
                                0, 0, 0x0400, 0x0400);
            image += 0x200;
        }
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
}

extern M2C_UNK D_02000000;
extern u8 D_020002C0[];
extern u8 D_02000580[];
extern u8 D_02000840[];
extern Gfx D_800602C8[];
extern Gfx D_80060398[];
extern s32 sPushStartBlinkTimer;
void Gfx_DrawTextureIa16(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);

/**
 * Draws the blinking PUSH START graphic (88x16 IA16, four 4-line strips from segment 2) at
 * (`x`, `y`). sPushStartBlinkTimer runs from 0x30 to 0x6C and wraps: the graphic fades in over
 * 16 frames, holds, fades out, then stays hidden.
 * Seen in play (2026-11-14): called each title frame with (0x74, 0xC0); stubbing it removed
 * PUSH START.
 */
void TitleScreen_DrawPushStart(s16 x, s16 y) {
    s32 t = sPushStartBlinkTimer - 0x30;
    s32 alpha = 0;

    if (t >= 0) {
        if (t < 0x10) {
            alpha = t * 0x10;
        } else if (t < 0x23) {
            alpha = 0xFF;
        } else if (t < 0x32) {
            alpha = -t * 0x10 + 0x320;
        }
    }
    sPushStartBlinkTimer++;
    if (sPushStartBlinkTimer >= 0x6D) {
        sPushStartBlinkTimer = 0x30;
    }
    gSPDisplayList(gDisplayListHead++, D_800602C8);
    gDPSetEnvColor(gDisplayListHead++, 0xFF, 0xFF, 0xFF, alpha);
    Gfx_DrawTextureIa16(x, y, 0x58, 4, (u8*)&D_02000000, 0x58, 0);
    Gfx_DrawTextureIa16(x, y + 4, 0x58, 4, D_020002C0, 0x58, 0);
    Gfx_DrawTextureIa16(x, y + 8, 0x58, 4, D_02000580, 0x58, 0);
    Gfx_DrawTextureIa16(x, y + 0xC, 0x58, 4, D_02000840, 0x58, 0);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

extern s32 sTitleFrameCounter;

/**
 * Returns whether the title screen may leave: the 64DD boot state `bootState` is 0, 1, 3 or 5
 * (no disk, or waiting on the drive; not while a disk read is being queued or loaded) and the
 * title has run at least 16 frames.
 * Seen in play (2026-11-14): with LeoBootState.state poked to 0, Start (and A) left the title;
 * poked to 8, Start did nothing.
 */
s32 TitleScreen_CanAcceptInput(s32 bootState)
{
  s32 var_v1_2;
  var_v1_2 = bootState == 5;
  if (var_v1_2 == 0)
  {
    var_v1_2 = bootState == 0;
    if (var_v1_2 == 0)
    {
      var_v1_2 = bootState == 1;
      if (var_v1_2 == 0)
      {
        var_v1_2 = bootState == 3;
      }
    }
  }
  var_v1_2 = var_v1_2 != 0;
  if (var_v1_2 != 0)
  {
    var_v1_2 = sTitleFrameCounter >= 0x10;
  }
  return var_v1_2;
}

s32 Audio_GetActivityScore(void);

/**
 * Returns whether to start the attract-mode demo battle: the title has run 601 (0x259) frames
 * or more, Audio_GetActivityScore() is 0 (the title music has ended) and
 * TitleScreen_CanAcceptInput(`bootState`) holds.
 * Seen in play (2026-11-14): left idle, the counter passed 601 at about frame 601 but the demo
 * started only at frame 1102, once the music was silent.
 */
s32 TitleScreen_ShouldStartDemo(s32 bootState) {
    s32 var_v1 = 0;

    if ((sTitleFrameCounter >= 0x259) && (Audio_GetActivityScore() == 0) && (TitleScreen_CanAcceptInput(bootState) != 0)) {
        var_v1 = 1;
    }
    return var_v1;
}

/*
 * Note for matching: the empty `if (!result) {}` after Cont_ReadInputs does
 * nothing at run time; decomp-permuter found that it changes the register
 * allocation to the ROM's.  It is not evidence of what the original source
 * looked like.
 */
void Cont_StartReadInputs(void);
void Cont_ReadInputs(void);
void BgStage_DrawFrame(void);
void StageContext_SetClearColor(u16 color);
M2C_UNK Audio_FadeCategoriesAndStreams(M2C_UNK);
M2C_UNK func_8003F6AC(M2C_UNK);
extern void *D_800603C0;
extern LeoBootDescriptor* sDiskBootBlock;

/**
 * The title screen's per-frame callback for BgStage_WaitForCondition; `fadeMode` is the stage's
 * fade mode, and input is read only while it is 0 (no fade running). Each frame it polls the
 * 64DD boot (Leo_RunBootStateMachine) and returns:
 *   - TITLE_EXIT_DISK_BOOT (0xF000) when the boot state reaches 10 (disk payload loaded),
 *     fading the audio out;
 *   - TITLE_EXIT_MAIN_MENU (0x8020) when A or Start is held (D_800603C0 +8 & 0x9000) and
 *     TitleScreen_CanAcceptInput allows it, playing sound 0xF;
 *   - TITLE_EXIT_DEMO (0x8010) when no button is held and TitleScreen_ShouldStartDemo holds,
 *     after TitleScreen_SetupDemoBattle;
 *   - 0 otherwise.
 * Then it draws the frame: background, PUSH START (controller 1 present) or the
 * no-controller message, and the disk error box. On exit it sets the clear color: 0xFFFF (white)
 * for the main menu, 1 (black) otherwise.
 * Seen in play (2026-11-14): Start or A with boot state 0 faded to white into the main menu
 * lobby (clear color 0xFFFF); boot state poked to 10 faded to black (clear color 1); left idle,
 * the demo battle started.
 */
s32 TitleScreen_Update(s32 fadeMode) {
    s32 result;
    s32 bootStatus;
    s32 temp_v0;

    result = 0;
    bootStatus = 0;
    Cont_StartReadInputs();
    Cont_ReadInputs();
    if (!result) {  // karodo
    }
    sTitleFrameCounter += 1;
    if (fadeMode == 0) {
        temp_v0 = Leo_RunBootStateMachine(sDiskBootBlock);
        bootStatus = temp_v0;
        if (((temp_v0 >> 0x10) & 0xFFFF) == 0xA) {
            Audio_FadeCategoriesAndStreams(0x10);
            result = TITLE_EXIT_DISK_BOOT;
        } else if (M2C_FIELD(D_800603C0, u16 *, 8) & 0x9000) {
            if (TitleScreen_CanAcceptInput((bootStatus >> 0x10) & 0xFFFF) != 0) {
                func_8003F6AC(0xF);
                result = TITLE_EXIT_MAIN_MENU;
            }
        } else if (TitleScreen_ShouldStartDemo((bootStatus >> 0x10) & 0xFFFF) != 0) {
            TitleScreen_SetupDemoBattle();
            result = TITLE_EXIT_DEMO;
        }
    }
    BgStage_DrawFrame();
    TitleScreen_DrawBackground();
    if (func_8000B2E8() & 1) {
        TitleScreen_DrawPushStart(0x74, 0xC0);
    }
    TitleScreen_DrawNoControllerTicker();
    TitleScreen_DrawDiskError(bootStatus & 0xFFFF);
    if (result != 0) {
        if (result == TITLE_EXIT_MAIN_MENU) {
            StageContext_SetClearColor(0xFFFF);
        } else {
            StageContext_SetClearColor(1);
        }
    }
    return result;
}

s32 main_pool_alloc(u32 size, s32 side);
u32 main_pool_push_state(u32 arg);
u32 main_pool_pop_state(u32 arg);
void Gfx_InitDisplayListBuffers(u32 buffer_size, s32 pool_side);
void Gfx_FreeDisplayListBuffers(void);
s32 StageContext_Allocate(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK StageContext_Activate(s32);
M2C_UNK StageContext_Deactivate();
s32 BgStage_WaitForCondition(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK Audio_WaitForIdle(M2C_UNK);
s32 Font_Init(s32 load_size, s32 side);
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2);
M2C_UNK Audio_LoadWaveTablesAndMusic(s32);
M2C_UNK Audio_ClearWaveDataLoaded();
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_002EBCB0;
extern M2C_UNK D_002F0A50;
extern M2C_UNK D_01000000;
extern M2C_UNK D_02000000;
extern s32 sTitleBackgroundImage;
extern s32 sTitleAudioHeap;
extern s32 sPushStartBlinkTimer;

/**
 * Title screen fragment entry. Loads the title assets to segments 1 and 2 and the background
 * picture, allocates the 64DD boot block buffer and a 1 MiB audio heap, then runs
 * TitleScreen_Update each frame (16-frame fades) until it returns an exit code, which it
 * returns: TITLE_EXIT_MAIN_MENU, TITLE_EXIT_DEMO or TITLE_EXIT_DISK_BOOT.
 * Seen in play (2026-11-14): runs after the opening; the fragment stays loaded while the title
 * shows, and its exit codes lead to the main menu lobby, the demo battle or a black fade.
 */
s32 TitleScreen_Main(UNUSED s32 arg0, UNUSED M2C_UNK arg1) {
    s32 result;
    s32 stage;

    main_pool_push_state(0x5449544C); // 'TITL'
    Gfx_InitDisplayListBuffers(0x10000, 0);
    stage = StageContext_Allocate(0, 1, 2, 0, 2, 1);
    Font_Init(6, 0);
    Asset_LoadToSegment((u32) ((s32) &D_01000000 & 0x0F000000) >> 0x18, (u8*)&D_002E0BE0, (u8*)&D_002E2B90, 0);
    Asset_LoadToSegment((u32) ((s32) &D_02000000 & 0x0F000000) >> 0x18, (u8*)&D_002EBCB0, (u8*)&D_002F0A50, 0);
    sDiskBootBlock = (LeoBootDescriptor*)main_pool_alloc(0x4510, 0);
    sTitleAudioHeap = main_pool_alloc(0x100000, 0);
    sTitleBackgroundImage = (s32)Asset_LoadToSegment(0U, (u8*)&D_002E2B90, (u8*)&D_002EBCB0, 0);
    sTitleFrameCounter = 0;
    sPushStartBlinkTimer = 0;
    Audio_LoadWaveTablesAndMusic(sTitleAudioHeap);
    StageContext_Activate(stage);
    result = BgStage_WaitForCondition(&TitleScreen_Update, 0x10, 0x10);
    StageContext_Deactivate();
    Leo_AbortPendingBootRequest();
    Audio_WaitForIdle(0);
    Audio_ClearWaveDataLoaded();
    if (result == 0x8080) {
        Audio_PlayCommand(0x3C, 0xA, 0);
    }
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x5449544C); // 'TITL'
    return result;
}
