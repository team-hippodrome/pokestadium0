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
extern s32 D_81600A70;
extern s32 D_81600A74;

s32 TransferPakError_DrawFrame(u8 arg0);

void TransferPakError_DrawBackgroundPattern(s32 arg0, s32 arg1, s32 arg2);
void FatalError_DrawMessagePanel(s32 arg0);
void FatalError_DrawPortDiagram(s32 arg0);

void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Fills the 320x240 screen with the green Poke Ball wallpaper from transfer_pak_error_ui
 * (64x64 RGBA16 at segment offset 0x0), drawn in COPY mode as 64x16 strips.
 * The three arguments (0x55, 0x70, 0x88 from TransferPakError_DrawFrame) are unused.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment from Stadium 1.
 */
void TransferPakError_DrawBackgroundPattern(s32 arg0, s32 arg1, s32 arg2) {
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

/** Draws the icon of the fatal error screen. */
void FatalError_DrawIcon(s32 arg0, s32 arg1) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    func_8001B884(arg0, arg1, 0x18, 0x18, D_2002000, 0x18, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

extern char** D_81100938;
extern char* D_816008DC[];

/** Draws the message panel of the fatal error screen. */
void FatalError_DrawMessagePanel(s32 arg0) {
    Ui_DrawBorderedPanel(0x16, 0x10, 0x114, 0x76, 0x11C5);
    FatalError_DrawIcon(0x27, 0x22);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(2, 0);
    Font_SetLineHeight(0x10);
    Font_Printf(0x52, 0x21, D_816008DC[arg0]);
    Font_EndTexturedTextRendering();
}

/** Draws the controller port diagram of the fatal error screen. */
void FatalError_DrawPortDiagram(s32 arg0) {
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

    func_8001B884(sp80[arg0], 0xD4, 8, 8, D_2006920, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x028C, 0x0350, sp80[arg0] << 2, 0x0370, G_TX_RENDERTILE, 0, 0, 0, 0x0400);

    func_8001B884(sp80[arg0], 0xC0, 8, 8, D_2006820, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, sp80[arg0] << 2, 0x0320, (sp80[arg0] + 8) << 2, 0x0350, G_TX_RENDERTILE, 0,
                        0x00E0, 0x0400, 0);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/**
 * Per-frame draw callback: wallpaper, message window and port diagram for the stored error.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment from Stadium 1.
 */
s32 TransferPakError_DrawFrame(u8 arg0) {
    BgStage_DrawFrame();
    TransferPakError_DrawBackgroundPattern(0x55, 0x70, 0x88);
    FatalError_DrawMessagePanel(D_81600A74);
    FatalError_DrawPortDiagram(D_81600A70);
    return 0;
}

extern char** D_81100938;
/**
 * Entry point of the Transfer Pak fatal error screen, reached only through
 * Game_ShutdownAndLoadFragment(port, message_id) after the game has blanked video, powered off
 * all Transfer Paks and faded out audio. //@src/game_state.c
 * Callers in gb_tower.c and pokemon_stats.c mostly pass 1 for Transfer Pak communication
 * failures (osGbpak* errors, failed connection polling, Game Boy save changed before a write)
 * and 2 for cartridge-side failures (connector check, cartridge RAM detection, cartridge reset
 * or removal); State_GbTower forwards the Game Boy emulator exit code, where 3 means an invalid
 * Game Boy opcode or an emulator heap allocation failure.
 * Loads transfer_pak_error_ui and text file 0xD, then draws forever: the only exit is turning
 * the console off, as the message instructs.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void TransferPakError_Main(s32 arg0, s32 arg1) {
    StageContext* temp_s0;

    D_81600A70 = arg0;
    D_81600A74 = arg1;

    main_pool_push_state('FATL');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    temp_s0 = StageContext_Allocate(0, 1, 2, 0, 2, 1);
    Font_Init(6, 0);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, transfer_pak_error_ui, 0);
    StageContext_Activate(temp_s0);

    while (TRUE) {
        BgStage_WaitForCondition(TransferPakError_DrawFrame, 8, 8);
    }
}
