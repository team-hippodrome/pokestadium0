/* Stadium Zero fragment003_15F390. */
/* C ported from the Stadium 1 decomp: src/fragments/n64_logo/n64_logo.c. */

#include "n64_logo.h"
#include "fragments/battle/battle.h"
#include "gfx_buffer.h"
#include "memory_main.h"

void N64Logo_DrawLogoTexture(void);
s32 N64Logo_DrawFrame(UNUSED u8 fadeMode);
void N64Logo_HoldForOneSecond(u64 startTime);
void N64Logo_ScanTransferPaks(void);

/**
 * Draws the 128x112 RGBA16 "NINTENDO 64" logo (n64_logo_texture, loaded at segment 0x02)
 * centered at screen (96, 64)-(223, 175), as seven 128x16 strips in COPY mode.
 * Verified in play (2026-11-14): called once per drawn frame from N64Logo_DrawFrame at boot.
 * The logo sits at (192, 128)-(446, 350) of a 640x480 screenshot, i.e. the box above at 2x.
 * With this function stubbed (jr ra) the screen stays black for the whole logo hold.
 */
void N64Logo_DrawLogoTexture(void) {
    s32 y;
    u8* strip;
    u32 stripHeightMinusOne = 0xF;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync(gDisplayListHead++);

    strip = D_2000000;
    for (y = 0x40; y < 0xB0; y += 0x10, strip += 0x1000) {
        gDPLoadTextureBlock(gDisplayListHead++, strip, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 16, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 7, 4, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, 0x0180, y << 2, 0x037C, (y + stripHeightMinusOne) << 2, G_TX_RENDERTILE, 0, 0,
                            0x1000, 0x0400);
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
}

/**
 * Per-frame draw callback for BgStage_RunUntilCondition, which passes the stage's fadeMode:
 * clears the framebuffer to black (RGBA5551 0x0001) and draws the logo. Always returns 0, so
 * each BgStage_RunUntilCondition call runs its full frame count.
 * Verified in play (2026-11-14): at boot it ran 3 times for the fade-in (first call with
 * fadeMode 2) and 16 times for the fade-out, each time calling N64Logo_DrawLogoTexture.
 */
s32 N64Logo_DrawFrame(UNUSED u8 fadeMode) {
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    N64Logo_DrawLogoTexture();

    return 0;
}

/**
 * Busy-waits until 1,000,000 microseconds (1 second) have passed since startTime (an osGetTime
 * count). ticks * 64 / 3000 is the libultra OS_CYCLES_TO_USEC conversion for the 46.875 MHz
 * counter. No frames are drawn meanwhile, so the last logo frame stays on screen.
 * Verified in play (2026-11-14): called once at boot right after N64Logo_ScanTransferPaks, with
 * startTime taken just after SFX_N64_LOGO; it returned 59 frames later (about 1 second).
 * Renamed from Stadium 1's N64Logo_WaitForElapsed: the wait is always one second.
 */
void N64Logo_HoldForOneSecond(u64 startTime) {
    u32 elapsedUsec = 0xF;

    while (elapsedUsec < 0xF4240) {
        elapsedUsec = __ull_div(__ll_mul(osGetTime() - startTime, 0x40), 0xBB8);
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
 * Verified in play (2026-11-14): runs once at boot while the logo is held, and calls
 * GbSave_ScanAllPorts. With a Transfer Pak holding Pocket Monsters Green in port 1, the pak masks
 * at 0x800AB1F4 read 01 01 01 01 after it; with this function stubbed (jr ra) they stay 0, so no
 * pak is initialized.
 */
void N64Logo_ScanTransferPaks(void) {
    main_pool_push_state('GPAK');

    GbSave_ScanAllPorts();

    main_pool_pop_state('GPAK');
}

void Save_LoadSram(void);
u8 Save_GetOptionFlags(void);
void func_8003BC9C(s32);
void func_800418F0(s32);

/**
 * Boot logo sequence: the fragment's entry point. Its only loader is func_80025F3C, the boot
 * state (0x8001) of Game_RunStateLoop, which passes 0 for both arguments through func_80025B60
 * and ignores the return value. //@src/game_state.c
 * Fades in the Nintendo 64 logo over 3 frames, applies the saved sound options (bit 0 = mono
 * output, bit 1 = Announcer voice off, as in Options_ApplySoundSettings), plays SFX_N64_LOGO,
 * scans the Transfer Paks while holding the logo for at least 1 second from the sound, then fades
 * out over 16 frames. Returns 0x8010, the game state the boot state switches to next anyway.
 * Verified in play (2026-11-14): pushes the 'LOGO' pool state at boot (frame ~310 after a power
 * cycle), Audio_PlaySoundEffectById got 0x0A (SFX_N64_LOGO), and it returned 0x8010.
 */
s32 N64Logo_Main(UNUSED s32 loaderArg0, UNUSED s32 loaderArg1) {
    u8 soundOptions;
    u64 logoStartTime;
    StageContext* stageContext;

    main_pool_push_state('LOGO');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    stageContext = StageContext_Allocate(0, 1, 2, 0, 2, 1);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, n64_logo_texture, 0);

    Save_LoadSram();
    StageContext_Activate(stageContext);
    StageFade_Start(1);
    BgStage_RunUntilCondition(3, N64Logo_DrawFrame);
    soundOptions = Save_GetOptionFlags();

    if (soundOptions & 1) {
        func_8003BC9C(0);
    } else {
        func_8003BC9C(1);
    }

    if (soundOptions & 2) {
        func_800418F0(0);
    } else {
        func_800418F0(1);
    }

    Audio_PlaySoundEffectById(SFX_N64_LOGO);
    logoStartTime = osGetTime();
    N64Logo_ScanTransferPaks();
    N64Logo_HoldForOneSecond(logoStartTime);
    StageFade_Start(0x10);
    BgStage_RunUntilCondition(0x10, N64Logo_DrawFrame);
    StageContext_Deactivate();
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('LOGO');
    return 0x8010;
}
