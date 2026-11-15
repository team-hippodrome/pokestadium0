/* Stadium Zero fragment025_2B16A0. */
/* C ported from the Stadium 1 decomp: src/fragments/fatal_error_screen/fatal_error_screen.c. */

#include "font.h"
#include "gfx_buffer.h"
#include "graphics_textures.h"
#include "input.h"
#include "memory_main.h"
#include "stage_loader.h"
#include "ui_graphics.h"
#include "fatal_error_screen.h"
extern s32 sFatalErrorPort;
extern s32 sFatalErrorMessageId;

s32 FatalError_DrawFrame(u8 fade_mode);

void FatalError_DrawBackground(s32 unused0, s32 unused1, s32 unused2);
void FatalError_DrawMessagePanel(s32 message_id);
void FatalError_DrawPortDiagram(s32 port);

void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Fills the 320x240 screen with the green Poké Ball wallpaper from transfer_pak_error_ui
 * (64x64 RGBA16 at segment offset 0x0), drawn in COPY mode as 64x16 strips.
 * The three arguments (85, 112, 136 from FatalError_DrawFrame) are unused.
 * Seen in play (2026-11-14): stubbed together with FatalError_DrawPortDiagram, the old diagram
 * stayed on screen; restoring this function painted the wallpaper over it.
 */
void FatalError_DrawBackground(s32 unused0, s32 unused1, s32 unused2) {
    s32 i;
    s32 j;
    s32 idx;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    for (i = 0; i < 240; i += 16) {
        for (j = 0; j < 320; j += 64) {
            idx = (i % 64) * 32;
            Gfx_DrawTextureRgba16(j, i, 0x40, 0x10, &D_2000000[idx * 4], 0x40, 0x200000);
        }
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/**
 * Draws the yellow "!" warning icon (24x24, segment offset 0x2000) at (x, y), left of the message.
 * Seen in play (2026-11-14): stubbing it removed only the icon.
 */
void FatalError_DrawWarningIcon(s32 x, s32 y) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    Gfx_DrawTextureRgba16(x, y, 24, 24, D_2002000, 24, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

extern char* sFatalErrorMessages[];

/**
 * Draws the bordered message panel, the warning icon and message message_id of
 * sFatalErrorMessages:
 * 1 "６４ＧＢパックが ただしくセットされていません。" (64GB Pak not inserted correctly; turn the power
 *   off and check the connection),
 * 2 "ゲームボーイカートリッジの コネクタぶが いじょうです。" (Game Boy cartridge connector fault; see
 *   the 64GB Pak manual),
 * 3 "レポートがただしくないので つづきからあそぶことはできません。" (the Game Boy save is invalid, so
 *   Continue is not possible; reset and choose New Game). Entry 0 is NULL.
 * Seen in play (2026-11-14): stubbing it removed the panel, icon and text; writing 2 and 3 to
 * sFatalErrorMessageId showed those texts.
 */
void FatalError_DrawMessagePanel(s32 message_id) {
    Ui_DrawBorderedPanel(22, 16, 276, 118, 0x11C5); // #103910
    FatalError_DrawWarningIcon(39, 34);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(2, 0);
    Font_SetLineHeight(0x10);
    Font_Printf(82, 33, sFatalErrorMessages[message_id]);
    Font_EndTexturedTextRendering();
}

/**
 * Draws the diagram under the message: a controller with a crossed-out 64GB Pak, cabled to the
 * console, with the cable running into controller port `port` (0-3, x from sp80).
 * Seen in play (2026-11-14): stubbing it removed the diagram; writing 1, 2 and 3 to
 * sFatalErrorPort moved the cable's plug to ports 2, 3 and 4.
 */
void FatalError_DrawPortDiagram(s32 port) {
    u16 sp80[] = {
        188,
        198,
        223,
        233,
    };

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    Gfx_DrawTextureRgba16(152, 161, 8, 8, D_20069A0, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x01C8, 0x0284, 0x0260, 0x02A4, G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(77, 148, 0x40, 0x20, D_2002900, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(77, 180, 0x40, 0x20, D_2003900, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(77, 212, 0x40, 6, D_2004900, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(93, 152, 24, 24, D_2002480, 24, 0x200000);
    Gfx_DrawTextureRgba16(170, 170, 100, 18, D_2004C00, 100, 0x200000);
    Gfx_DrawTextureRgba16(170, 188, 100, 18, D_2005A10, 100, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    Gfx_DrawTextureRgba16(155, 212, 8, 8, D_20068A0, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x026C, 0x02A4, 0x028C, 0x0350, G_TX_RENDERTILE, 0, 0, 0x0400, 0);

    Gfx_DrawTextureRgba16(sp80[port], 212, 8, 8, D_2006920, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x028C, 0x0350, sp80[port] << 2, 0x0370, G_TX_RENDERTILE, 0, 0, 0, 0x0400);

    Gfx_DrawTextureRgba16(sp80[port], 192, 8, 8, D_2006820, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, sp80[port] << 2, 0x0320, (sp80[port] + 8) << 2, 0x0350, G_TX_RENDERTILE, 0,
                        0x00E0, 0x0400, 0);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/**
 * Per-frame draw callback for BgStage_WaitForCondition: wallpaper, message panel and port
 * diagram for the stored error. fade_mode is unused, and it always returns 0, so the screen never
 * fades out.
 * Seen in play (2026-11-14): breakpoint hit every frame on the error screen.
 */
s32 FatalError_DrawFrame(u8 fade_mode) {
    BgStage_DrawFrame();
    FatalError_DrawBackground(85, 112, 136);
    FatalError_DrawMessagePanel(sFatalErrorMessageId);
    FatalError_DrawPortDiagram(sFatalErrorPort);
    return 0;
}

/**
 * Entry point of the Transfer Pak fatal error screen, reached only through
 * Game_ShutdownAndLoadFragment(port, message_id) after the game has blanked video, powered off
 * all Transfer Paks and faded out audio. //@src/game_state.c
 * Callers in gb_player.c and pokemon_stats_2.c mostly pass 1 for Transfer Pak communication
 * failures (osGbpak* errors, failed connection polling, Game Boy save changed before a write)
 * and 2 for cartridge-side failures (connector check, cartridge RAM detection, cartridge reset
 * or removal); State_GbPlayer forwards a nonzero Game Boy emulator exit code, and message 3 says
 * the Game Boy save is invalid. See FatalError_DrawMessagePanel for the texts.
 * Loads common_menu1_ui and transfer_pak_error_ui, then draws forever: the only exit is turning
 * the console off, as the message instructs.
 * Seen in play (2026-11-14): pulling the Transfer Pak (tpak.remove port 1) on the Game Boy
 * cartridge select screen made GbPlayer_PollPakConnection call
 * Game_ShutdownAndLoadFragment(0, 1); the breakpoint here hit with port 0, message_id 1, and the
 * screen showed message 1 with the cable in controller port 1.
 */
void FatalError_Main(s32 port, s32 message_id) {
    StageContext* stage;

    sFatalErrorPort = port;
    sFatalErrorMessageId = message_id;

    MainPool_PushState('FATL');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    stage = StageContext_Allocate(0, 1, 2, 0, 2, 1);
    Font_Init(6, 0);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, transfer_pak_error_ui, 0);
    StageContext_Activate(stage);

    while (TRUE) {
        BgStage_WaitForCondition(FatalError_DrawFrame, 8, 8);
    }
}
