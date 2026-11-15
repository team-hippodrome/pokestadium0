/*
 * Stadium Zero fragment017_261F00: an unused menu titled ポケモンずかん (Pokédex) with the items
 * ずかん, ポケモン, どうぐ, なまえ, せってい, とじる (Pokédex, Pokémon, Items, Name, Settings, Close),
 * laid out like the Game Boy games' Start menu.
 *
 * Nothing in the retail ROM loads this fragment: no code or data anywhere in the ROM passes
 * its ROM start (0x261F00) to the fragment loader, and 0x261F00 only appears as the end of
 * fragment 016 in MainMenu_LoadSelectedFragment. Only Pokédex and Pokémon open a screen;
 * the other four items and B go back to the main menu.
 *
 * Seen in play (2026-11-14, pj64-pokestadium-debug): the fragment was force-loaded by patching
 * the main menu's バトル case of MainMenu_LoadSelectedFragment in RAM to load 0x8A000000 from
 * ROM 0x261F00-0x262620. The menu above appeared and every function below ran.
 */

#include "global.h"
#include "m2c_macros.h"
#include "pokedex_menu.h"
#include "controller.h"
#include "font.h"
#include "game_state.h"
#include "graphics_textures.h"
#include "stage_loader.h"
#include "ui_graphics.h"

M2C_UNK Gfx_DrawPatternRows(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
void Audio_PlaySystemSound(s32); // Audio_PlaySoundEffectById
extern s32 sPokedexMenuSelection; // the selected item, 0-5
extern char sPokedexMenuTitleText[]; // "ポケモンずかん"
extern char sPokedexMenuPokedexText[]; // "ずかん"
extern char sPokedexMenuPokemonText[]; // "ポケモン"
extern char sPokedexMenuItemsText[]; // "どうぐ"
extern char sPokedexMenuNameText[]; // "なまえ"
extern char sPokedexMenuSettingsText[]; // "せってい"
extern char sPokedexMenuCloseText[]; // "とじる"

/**
 * Prints one item's text at (x, y), in yellow when `index` is the selected item.
 * Seen in play (2026-11-14): called with index 0-5 every frame; the selected item was yellow,
 * the rest white.
 */
void PokedexMenu_DrawItem(s32 index, s32 x, s32 y, char* text) {
    if (index == sPokedexMenuSelection) {
        Gfx_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
    }
    Font_Printf(x, y, text);
    if (index == sPokedexMenuSelection) {
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    }
}

/**
 * Draws the menu: the background, the hand cursor beside the selected item, the title
 * ポケモンずかん and the six items. `fade_mode` is not read.
 * Seen in play (2026-11-14): ran every frame while the menu was shown.
 */
s32 PokedexMenu_Draw(s32 fade_mode) {
    BgStage_DrawFrame();
    Gfx_DrawPatternRows(0, 0x1E0, 0x32, 0x64, 0xA2);
    Ui_DrawTextureMarker(0xA0, (sPokedexMenuSelection * 0x1E) + 0xC8);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(0x20, 0);
    Font_EnableTwoCycleTexturing();
    Gfx_SetPrimColor(0xFF, 0x6B, 0x5A, 0xFF);
    Font_Printf(0xB4, 0x28, sPokedexMenuTitleText);
    Font_DisableTwoCycleTexturing();
    Font_SetActive(0x10, 0);
    PokedexMenu_DrawItem(0, 0xC8, 0xC8, sPokedexMenuPokedexText);
    PokedexMenu_DrawItem(1, 0xC8, 0xE6, sPokedexMenuPokemonText);
    PokedexMenu_DrawItem(2, 0xC8, 0x104, sPokedexMenuItemsText);
    PokedexMenu_DrawItem(3, 0xC8, 0x122, sPokedexMenuNameText);
    PokedexMenu_DrawItem(4, 0xC8, 0x140, sPokedexMenuSettingsText);
    PokedexMenu_DrawItem(5, 0xC8, 0x15E, sPokedexMenuCloseText);
    Font_EndTexturedTextRendering();
    return 0;
}

/**
 * Moves the selection with the D-pad: Down (0x400) selects the next item and Up (0x800) the
 * previous one, wrapping between 0 and 5, with the scroll sound (SFX_MENU_SCROLL).
 * Matching note: the empty `if (!sPokedexMenuSelection) {}` before the first call has no
 * effect on behavior. It was found with decomp-permuter and is the only form
 * tried that gives the ROM's register for the address of sPokedexMenuSelection (v1
 * instead of v0). Same kind of workaround as in TitleScreen_Update.
 * Seen in play (2026-11-14): D-Down took the selection 0, 1, 2, 3, 4, 5, 0 and D-Up 2, 1, 0, 5.
 */
void PokedexMenu_UpdateCursor(void) {
    s32 dpad;

    if (!sPokedexMenuSelection) {  // karodo
    }
    dpad = Input_GetRepeatedDPad();
    if (dpad != D_JPAD) {
        if (dpad == U_JPAD) {
            Audio_PlaySystemSound(SFX_MENU_SCROLL);
            sPokedexMenuSelection -= 1;
            if (sPokedexMenuSelection < 0) {
                sPokedexMenuSelection = 5;
            }
        }
    } else {
        Audio_PlaySystemSound(SFX_MENU_SCROLL);
        sPokedexMenuSelection += 1;
        if (sPokedexMenuSelection >= 6) {
            sPokedexMenuSelection = 0;
        }
    }
}

extern s8 D_00235D70;
extern s8 D_00238BD0;
extern s8 D_00262620;
extern s8 D_00293410;
extern s8 D_002B1360;
extern s8 D_88000000;
extern s8 D_8A100000;
extern s8 D_8A200000;

/**
 * Queues the fragment for the selected item: 0 ずかん opens the Pokédex (fragment 018),
 * 1 ポケモン opens the party summary (fragment 019, with call argument 1), and 2-5 go back
 * to the main menu (fragment 014).
 * Seen in play (2026-11-14): A on each item; item 0 loaded 0x8A100000, item 1 0x8A200000,
 * items 2-5 0x88000000.
 */
void PokedexMenu_LoadSelectedFragment(void) {
    switch (sPokedexMenuSelection) {
    case 0:
        Fragment_QueueCall(((u32) ((s32) &D_8A100000 & 0x0FF00000) >> 0x14) - 0x10, &D_00262620, &D_00293410, 0, 0);
        return;
    case 1:
        Fragment_QueueCall(((u32) ((s32) &D_8A200000 & 0x0FF00000) >> 0x14) - 0x10, &D_00293410, &D_002B1360, 1, 0);
        return;
    case 2:
        Fragment_QueueCall(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
        return;
    case 3:
        Fragment_QueueCall(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
        return;
    case 4:
        Fragment_QueueCall(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
        return;
    case 5:
        Fragment_QueueCall(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
        /* fallthrough */
    default:
        return;
    }
}

/**
 * One frame of the menu, run by BgStage_RunUntilCondition with the stage's fade mode.
 * While the screen is opaque (`fade_mode` 1) it starts the fade-in. Once the screen is clear
 * (0), A plays the confirm sound and loads the selected item, B plays the back sound and
 * returns to the main menu (both return 0x8000, which ends the loop), and anything else
 * moves the cursor.
 * Seen in play (2026-11-14): A on each item and B both ended the menu. Only fade_mode 0 was
 * seen (41 frames from the first frame on); the `fade_mode == 1` branch did not run.
 */
s32 PokedexMenu_RunFrame(s32 fade_mode) {
    s32 ret = 0;

    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
    if (fade_mode == 1) {
        StageFade_Start(8);
    } else if (fade_mode == 0) {
        if (gPlayer1Controller->buttonPressed & A_BUTTON) {
            Audio_PlaySystemSound(SFX_MENU_CONFIRM);
            PokedexMenu_LoadSelectedFragment();
            ret = 0x8000;
        } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
            Audio_PlaySystemSound(SFX_MENU_BACK);
            Fragment_QueueCall(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
            ret = 0x8000;
        } else {
            PokedexMenu_UpdateCursor();
        }
    }
    PokedexMenu_Draw(fade_mode);
    return ret;
}

extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_002F0A50;
extern M2C_UNK D_002F3BD0;
extern M2C_UNK D_01000000;
extern M2C_UNK D_02000000;

/**
 * Fragment entry: pushes the 'BMNU' pool state, loads the font and the assets for segments
 * 1 and 2, runs the menu until an item or B is chosen, then frees the font, pops the pool
 * state and returns 0x8040. The two call arguments from the loader are not read.
 * Seen in play (2026-11-14): on load MainPool_PushState('BMNU') and Font_Init(0x30) were
 * called from here, then PokedexMenu_RunFrame ran every frame.
 */
s32 PokedexMenu_Init(s32 unused0, M2C_UNK unused1) {
    MainPool_PushState(0x424D4E55);
    Font_Init(0x30, 0);
    Asset_LoadToSegment((u32) ((s32) &D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    Asset_LoadToSegment((u32) ((s32) &D_02000000 & 0x0F000000) >> 0x18, &D_002F0A50, &D_002F3BD0, 0);
    Input_SetRepeatController(gPlayer1Controller);
    Audio_PlayMusicIfChanged(2);
    StageLoader_UpdateSegments();
    BgStage_RunUntilCondition(0, (s32 (*)(u8)) PokedexMenu_RunFrame);
    StageLoader_WaitForRetrace();
    Font_Free();
    MainPool_PopState(0x424D4E55);
    return 0x8040;
}
