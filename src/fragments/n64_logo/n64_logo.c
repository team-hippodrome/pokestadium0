/* Stadium Zero fragment003_15F390. */
/* C ported from the Stadium 1 decomp: src/fragments/n64_logo/n64_logo.c. */

#include "fragments/n64_logo/n64_logo.h"
#include "save_data.h"
#include "gb_data.h"
#include "ui_graphics.h"
#include "text_system.h"
#include "3D140.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "audio_channel.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "memory.h"
#include "stage_loader.h"

void N64Logo_DrawLogoTexture(void);
s32 N64Logo_DrawFrame(UNUSED u8 arg0);
void N64Logo_WaitForElapsed(u64 arg0);
void N64Logo_ScanTransferPaks(void);

/**
 * Draws the 128x112 RGBA16 "NINTENDO 64" logo (n64_logo_texture, loaded at segment 0x02)
 * centered at screen (96, 64)-(223, 175), as seven 128x16 strips in COPY mode.
 * Seen in play (2026-11-13) ran while the N64 logo was on screen (console reset, then N64 logo,
 * opening, title and main menu).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void N64Logo_DrawLogoTexture(void) {
    s32 var_t4;
    u8* var_t5;
    u32 tmp = 0xF;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync(gDisplayListHead++);

    var_t5 = D_2000000;
    for (var_t4 = 0x40; var_t4 < 0xB0; var_t4 += 0x10, var_t5 += 0x1000) {
        gDPLoadTextureBlock(gDisplayListHead++, var_t5, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 16, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 7, 4, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, 0x0180, var_t4 << 2, 0x037C, (var_t4 + tmp) << 2, G_TX_RENDERTILE, 0, 0,
                            0x1000, 0x0400);
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
}

/**
 * Per-frame draw callback: clears the framebuffer to black (RGBA5551 0x0001) and draws the logo.
 * Seen in play (2026-11-13) ran while the N64 logo was on screen (console reset, then N64 logo,
 * opening, title and main menu).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 N64Logo_DrawFrame(UNUSED u8 arg0) {
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    N64Logo_DrawLogoTexture();

    return 0;
}

/**
 * Busy-waits until 1,000,000 microseconds (1 second) have passed since start_time.
 * ticks * 64 / 3000 is the libultra OS_CYCLES_TO_USEC conversion for the 46.875 MHz counter.
 * Seen in play (2026-11-13) ran while the N64 logo was on screen (console reset, then N64 logo,
 * opening, title and main menu).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void N64Logo_WaitForElapsed(u64 arg0) {
    u32 temp_ret = 0xF;

    while (temp_ret < 0xF4240) {
        temp_ret = __ull_div(__ll_mul(osGetTime() - arg0, 0x40), 0xBB8);
    }
}

/**
 * Boot-time Transfer Pak scan, run once while the logo is held on screen.
 * GbSave_ScanAllPorts (via GbTower_ScanPaks) initializes every plugged-in Transfer Pak,
 * identifies supported Pokemon Red/Green/Blue/Yellow cartridges for the region, checks
 * cartridge RAM, resets the per-port Game Boy save cache and enables disconnect polling for
 * ports holding a recognized Pokemon cartridge. This is the only caller of
 * GbSave_ScanAllPorts, so later Transfer Pak features rely on this boot scan.
 * N64Logo_Main starts its 1-second hold timer before the scan, so the controller-bus work
 * overlaps the logo instead of adding a blank delay.
 * A faulty pak or cartridge sends the game straight to the fatal error screen via
 * Game_ShutdownAndLoadFragment. //@src/pokemon_stats.c //@src/gb_tower.c
 * Allocations made during the scan are released when the 'GPAK' pool state is popped.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment from Stadium 1.
 */
void N64Logo_ScanTransferPaks(void) {
    main_pool_push_state('GPAK');

    GbSave_ScanAllPorts();

    main_pool_pop_state('GPAK');
}

void func_80023C30(void);
u8 func_80025214(void);
void func_8003BC9C(s32);
void func_800418F0(s32);

/**
 * Boot logo sequence, loaded by State_N64LogoIntro and State_FastN64Logo. //@src/game_state.c
 * Fades in the Nintendo 64 logo, applies the saved sound options (bit 0 = mono output,
 * bit 1 = Announcer voice off, as in Options_ApplySoundSettings), plays SFX_N64_LOGO, scans the
 * Transfer Paks while holding the logo for at least 1 second from the sound, then fades out.
 * Returns 2.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 N64Logo_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    u8 sp37;
    u64 sp28;
    StageContext* sp24;

    main_pool_push_state('LOGO');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = StageContext_Allocate(0, 1, 2, 0, 2, 1);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, n64_logo_texture, 0);

    func_80023C30();
    StageContext_Activate(sp24);
    StageFade_Start(1);
    BgStage_RunUntilCondition(3, N64Logo_DrawFrame);
    sp37 = func_80025214();

    if (sp37 & 1) {
        func_8003BC9C(0);
    } else {
        func_8003BC9C(1);
    }

    if (sp37 & 2) {
        func_800418F0(0);
    } else {
        func_800418F0(1);
    }

    Audio_PlaySoundEffectById(SFX_N64_LOGO);
    sp28 = osGetTime();
    N64Logo_ScanTransferPaks();
    N64Logo_WaitForElapsed(sp28);
    StageFade_Start(0x10);
    BgStage_RunUntilCondition(0x10, N64Logo_DrawFrame);
    StageContext_Deactivate();
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('LOGO');
    return 0x8010;
}
