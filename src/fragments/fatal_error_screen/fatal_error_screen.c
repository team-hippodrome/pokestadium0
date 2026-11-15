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

s32 FatalError_DrawFrame(u8 fadeMode);

void FatalError_DrawBackground(s32 unused0, s32 unused1, s32 unused2);
void FatalError_DrawMessagePanel(s32 messageId);
void FatalError_DrawPortDiagram(s32 port);

void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Fills the 320x240 screen with the green Poke Ball wallpaper from transfer_pak_error_ui
 * (64x64 RGBA16 at segment offset 0x0), drawn in COPY mode as 64x16 strips.
 * The three arguments (0x55, 0x70, 0x88 from FatalError_DrawFrame) are unused.
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

    for (i = 0; i < 0xF0; i += 0x10) {
        for (j = 0; j < 0x140; j += 0x40) {
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

    func_8001B884(x, y, 0x18, 0x18, D_2002000, 0x18, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

extern char* sFatalErrorMessages[];

/**
 * Draws the bordered message panel, the warning icon and message messageId of
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
void FatalError_DrawMessagePanel(s32 messageId) {
    Ui_DrawBorderedPanel(0x16, 0x10, 0x114, 0x76, 0x11C5);
    FatalError_DrawWarningIcon(0x27, 0x22);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(2, 0);
    Font_SetLineHeight(0x10);
    Font_Printf(0x52, 0x21, sFatalErrorMessages[messageId]);
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
        0x00BC,
        0x00C6,
        0x00DF,
        0x00E9,
    };

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    Gfx_DrawTextureRgba16(0x98, 0xA1, 8, 8, D_20069A0, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x01C8, 0x0284, 0x0260, 0x02A4, G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(0x4D, 0x94, 0x40, 0x20, D_2002900, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(0x4D, 0xB4, 0x40, 0x20, D_2003900, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(0x4D, 0xD4, 0x40, 6, D_2004900, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(0x5D, 0x98, 0x18, 0x18, D_2002480, 0x18, 0x200000);
    Gfx_DrawTextureRgba16(0xAA, 0xAA, 0x64, 0x12, D_2004C00, 0x64, 0x200000);
    Gfx_DrawTextureRgba16(0xAA, 0xBC, 0x64, 0x12, D_2005A10, 0x64, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);

    Gfx_DrawTextureRgba16(0x9B, 0xD4, 8, 8, D_20068A0, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x026C, 0x02A4, 0x028C, 0x0350, G_TX_RENDERTILE, 0, 0, 0x0400, 0);

    func_8001B884(sp80[port], 0xD4, 8, 8, D_2006920, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x028C, 0x0350, sp80[port] << 2, 0x0370, G_TX_RENDERTILE, 0, 0, 0, 0x0400);

    func_8001B884(sp80[port], 0xC0, 8, 8, D_2006820, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, sp80[port] << 2, 0x0320, (sp80[port] + 8) << 2, 0x0350, G_TX_RENDERTILE, 0,
                        0x00E0, 0x0400, 0);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/**
 * Per-frame draw callback for BgStage_WaitForCondition: wallpaper, message panel and port
 * diagram for the stored error. fadeMode is unused, and it always returns 0, so the screen never
 * fades out.
 * Seen in play (2026-11-14): breakpoint hit every frame on the error screen.
 */
s32 FatalError_DrawFrame(u8 fade_mode) {
    BgStage_DrawFrame();
    FatalError_DrawBackground(0x55, 0x70, 0x88);
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
 * Game_ShutdownAndLoadFragment(0, 1); the breakpoint here hit with port 0, messageId 1, and the
 * screen showed message 1 with the cable in controller port 1.
 */
void FatalError_Main(s32 port, s32 messageId) {
    StageContext* temp_s0;

    sFatalErrorPort = port;
    sFatalErrorMessageId = messageId;

    main_pool_push_state('FATL');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    temp_s0 = StageContext_Allocate(0, 1, 2, 0, 2, 1);
    Font_Init(6, 0);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, transfer_pak_error_ui, 0);
    StageContext_Activate(temp_s0);

    while (TRUE) {
        BgStage_WaitForCondition(FatalError_DrawFrame, 8, 8);
    }
}
