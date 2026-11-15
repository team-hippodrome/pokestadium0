/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "cartridge_check.h"
#include "audio_commands.h"
#include "font.h"
#include "geo_render.h"
#include "graphics_textures.h"
#include "input.h"
#include "matrix.h"
#include "pokemon_stats.h"
#include "stage_loader.h"
#include "ui_graphics.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK func_8001B5F0();
extern s8 *D_800603C0;

/**
 * Geo callback (referenced from the console model in fragment038, the 0x8F400000 model
 * fragment this fragment loads). On event 2 it shows the node (flag bit 0 at +1) while a
 * cartridge port is selected (D_88403358 >= 0) and hides it otherwise.
 * Seen in play (2026-11-14): with four Transfer Paks, pressing A drops a Poké Ball and the
 * Game Boy onto the console; with D_88403358 poked to -1 (or no pak) no Poké Ball appears. The
 * Game Boy is a separate model (D_88403378) that the code only creates for a selected port,
 * so the node this callback toggles is the Poké Ball.
 */
void CartridgeCheck_PokeBallVisibilityCallback(s32 event, s8 *node) {
    if (event == 2) {
        if (D_88403358 >= 0) {
            M2C_FIELD(node, u8 *, 1) = (u8) (M2C_FIELD(node, u8 *, 1) | 1);
            return;
        }
        M2C_FIELD(node, u8 *, 1) = (u8) (M2C_FIELD(node, u8 *, 1) & 0xFFFE);
    }
}

/**
 * Empty function. Nothing in the ROM calls it or holds its address (scan of every built
 * image for a jal to it or its address as a word, 2026-11-14).
 */
void CartridgeCheck_UnusedNoop1(void) {
}

/**
 * Geo light callback of this fragment's scene layout (D_88402EB0 holds its address twice).
 * On event 2 it points the light along the camera's eye-to-target direction
 * (Vec3f_CalculateDistanceAngles) and stores both angles plus 0x2000 in the light's rotationX
 * and rotationY. Always returns 0.
 * Seen in play (2026-11-14): called with event 2 every frame of the cartridge check scene.
 * Same shape as Intro_LightAngleCallbackA in the Stadium 1 decomp, which subtracts 0x2000
 * from the second angle where Zero adds it.
 */
s32 CartridgeCheck_LightAngleCallback(s32 event, GeoLightNode* light) {
    UNUSED s32 pad; // FAKE: stack padding; keeps the retail stack layout: the three locals below sit 4 bytes lower
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (event == 2) {
        Vec3f_CalculateDistanceAngles(&D_80060488->view.targetPosition, &D_80060488->view.eyePosition, &sp28, &sp26, &sp24);
        light->rotationX = sp26 + 0x2000;
        light->rotationY = sp24 + 0x2000;
    }
    return 0;
}

/**
 * Reads the controllers for this frame (Cont_StartReadInputs, Cont_ReadInputs,
 * Input_ResetRepeatState). Seen in play: runs every frame of the scene, from CartridgeCheck_DrawFrame.
 */
s32 CartridgeCheck_ReadInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    func_8001B5F0();
    return 0;
}

/** Empty function; nothing in the ROM calls it or holds its address (same scan as CartridgeCheck_UnusedNoop1). */
void CartridgeCheck_UnusedNoop2(void) {
}

/**
 * Per-frame callback of the scene: reads input, draws the 3D stage and the frame. Every loop in
 * this fragment calls it once per frame, and it is the callback passed to BgStage_RunUntilCondition.
 * Seen in play (2026-11-14): runs every frame on every screen of the fragment.
 */
s32 CartridgeCheck_DrawFrame(s32 arg0) {
    CartridgeCheck_ReadInputs();
    GeoRender_AdvanceFrameCounter();
    BgStage_DrawFrame();
    GfxImage_ClearDepthRectangle(&D_800AA150, 0, 0, 320, 240);
    Geo_RenderRootNode(D_88403370);
    return 0;
}

extern u8* D_88402F6C[4];
extern u8 D_04007298[];
extern u8 D_04008298[];
extern u8 D_04008F20[];
extern Gfx gUiEnvTintTextureDL[];
extern Gfx gUiRestoreTextureDL[];
void Gfx_DrawTextureIa8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);

/**
 * Draws the Game Boy cartridge icon of a port panel, tinted by `game` (1 Red, 2 Green,
 * 3 Blue, 7 Pikachu/Yellow; 0 = no Pokémon cartridge, drawn faded), with the 1P-4P label of `port`.
 * Seen in play (2026-11-14): with Green, Red, Blue and Pikachu in ports 1-4 the icons were
 * green 1P, red 2P, blue 3P and yellow 4P.
 */
void CartridgeCheck_DrawGameBoyIcon(s32 x, s32 y, s32 port, s32 game) {
    u8* icons[4] = D_88402F6C;

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    if (game == 0) {
        gDPSetEnvColor(gDisplayListHead++, 0xFF, 0xFF, 0xFF, 0x64); // #FFFFFF64
    }
    Gfx_DrawTextureRgba16(x, y, 50, 0x20, D_04007298, 0x40, 0);
    Gfx_DrawTextureRgba16(x, y + 0x20, 50, 25, D_04008298, 0x40, 0);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    if (game != 0) {
        switch (game) {
            case 1:
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 0xFF, 0x00, 0x00, 0xFF); // #FF0000FF
                break;
            case 2:
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 0x00, 0x96, 0x00, 0xFF); // #009600FF
                break;
            case 3:
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 0x00, 0x32, 0xFF, 0xFF); // #0032FFFF
                break;
            case 7:
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 0xFF, 0xFF, 0x00, 0xFF); // #FFFF00FF
                break;
        }
        Gfx_DrawTextureIa8(x + 6, y + 0x10, 38, 34, D_04008F20, 40, 0);
        gDPSetPrimColor(gDisplayListHead++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFFFF
        Gfx_DrawTextureIa8(x + 9, y + 23, 0x20, 20, icons[port], 0x20, 0);
    } else {
        gDPSetPrimColor(gDisplayListHead++, 0, 0, 0x80, 0x80, 0x80, 0x64); // #80808064
        Gfx_DrawTextureIa8(x + 9, y + 23, 0x20, 20, icons[port], 0x20, 0);
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

extern Color_RGB8 D_88402F7C;
extern Color_RGB8 D_88402F80;
extern Color_RGB8 D_88402F84;
extern Color_RGB8 D_88402F88;
extern char D_88403170[];
extern char D_88403174[];
extern char D_88403178[];
extern char D_88403184[];
extern char D_8840318C[];
extern char D_88403198[];
extern char D_884031A4[];
extern char D_884031BC[];
extern char D_884031D0[];
extern char D_884031E0[];
extern char D_884031F4[];
extern char D_88403210[];
void CartridgeCheck_DrawGameBoyIcon(s32, s32, s32, s32);

/**
 * Draws one port's panel on the 「ゲームボーイのカートリッジをえらんでください。」 screen: the cartridge
 * icon, then ID No. and トレーナー (trainer name) from the save, ＊＊＊＊＊ / ？？？？？ when the
 * cartridge has no valid save, or an error: 「ポケモンのカートリッジではありません。」 (not a Pokémon
 * cartridge), 「64GBパックがささっていません。」 (no Transfer Pak) or 「ゲームボーイのカートリッジが
 * ささっていません。」 (no Game Boy cartridge). The selected port gets the brighter panel.
 * Seen in play (2026-11-13, 2026-11-14): port 1 showed ID 12345 and サトシ from a crafted Green
 * save, ports 2-4 (blank saves) showed ＊＊＊＊＊ and ？？？？？, and "64GB Pak not inserted" for empty ports.
 */
void CartridgeCheck_DrawPortPanel(s32 port, s32 x, s32 y) {
    Color_RGB8 top = D_88402F7C;
    Color_RGB8 bottom = D_88402F80;
    Color_RGB8 sel_top = D_88402F84;
    Color_RGB8 sel_bottom = D_88402F88;

    if (port == D_88403358) {
        Ui_DrawGradientPanel(x, y, 0x80, 70, &sel_top, &sel_bottom);
    } else {
        Ui_DrawGradientPanel(x, y, 0x80, 70, &top, &bottom);
    }
    CartridgeCheck_DrawGameBoyIcon(x + 6, y + 6, port, D_88403310[port].game);
    Font_BeginTranslucentTextRendering();
    if (D_88403310[port].game != 0) {
        Font_SetActive(1, -2);
        Gfx_SetEnvColor(0xFF, 0xBD, 0x6B, 0xFF); // #FFBD6B
        Font_Printf(x + 62, y + 6, D_88403170);
        Font_Printf(x + 82, y + 6, D_88403174);
        Font_Printf(x + 62, y + 36, D_88403178);
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFF
        if (D_88403310[port].saveState == 0) {
            Font_SetActive(2, -2);
            Font_Printf(x + 62, y + 18, D_88403184, D_88403310[port].trainerId);
            Font_SetActive(2, -1);
            Font_Printf(x + 62, y + 48, D_88403310[port].name);
        } else {
            Font_SetActive(2, -2);
            Font_Printf(x + 62, y + 18, D_8840318C);
            Font_SetActive(2, -1);
            Font_Printf(x + 62, y + 48, D_88403198);
        }
    } else {
        Font_SetActive(1, -1);
        Gfx_SetEnvColor(0xFF, 0xFF, 0x64, 0xFF); // #FFFF64
        if (D_88403310[port].saveState == 2) {
            Font_Printf(x + 14, y + 20, D_884031A4);
            Font_Printf(x + 30, y + 35, D_884031BC);
        } else if (D_88403310[port].saveState == 1) {
            switch (GbSave_GetPortAvailability(port)) {
                case 1:
                    Font_Printf(x + 25, y + 20, D_884031D0);
                    Font_Printf(x + 25, y + 35, D_884031E0);
                    break;
                case 2:
                    Font_Printf(x + 4, y + 20, D_884031F4);
                    Font_Printf(x + 20, y + 35, D_88403210);
                    break;
            }
        }
    }
    Font_EndTexturedTextRendering();
}

/**
 * Moves the cartridge cursor around the 2x2 grid of controller ports on D-pad presses. A port
 * without a Pokémon cartridge (D_88403310[port].game == 0) is skipped for the diagonal one.
 * Returns the new port.
 * Seen in play (2026-11-14): with paks in all four ports, D-Right, D-Down, D-Left and D-Up moved
 * the highlight 1P → 2P → 4P → 3P → 1P.
 */
s32 CartridgeCheck_MoveCursor(s32 cursor) {
    if ((M2C_FIELD(D_800603C0, u16*, 8) & 0x800) && (cursor >= 2)) {
        if (D_88403310[cursor ^ 2].game != 0) {
            Audio_PlaySystemSound(0x25);
            cursor ^= 2;
        } else if (D_88403310[cursor ^ 3].game != 0) {
            Audio_PlaySystemSound(0x25);
            cursor ^= 3;
        }
    }
    if ((M2C_FIELD(D_800603C0, u16*, 8) & 0x400) && (cursor < 2)) {
        if (D_88403310[cursor ^ 2].game != 0) {
            Audio_PlaySystemSound(0x25);
            cursor ^= 2;
        } else if (D_88403310[cursor ^ 3].game != 0) {
            Audio_PlaySystemSound(0x25);
            cursor ^= 3;
        }
    }
    if ((M2C_FIELD(D_800603C0, u16*, 8) & 0x200) && ((cursor % 2) == 1)) {
        if (D_88403310[cursor ^ 1].game != 0) {
            Audio_PlaySystemSound(0x25);
            cursor ^= 1;
        } else if (D_88403310[cursor ^ 3].game != 0) {
            Audio_PlaySystemSound(0x25);
            cursor ^= 3;
        }
    }
    if ((M2C_FIELD(D_800603C0, u16*, 8) & 0x100) && ((cursor % 2) == 0)) {
        if (D_88403310[cursor ^ 1].game != 0) {
            Audio_PlaySystemSound(0x25);
            cursor ^= 1;
        } else if (D_88403310[cursor ^ 3].game != 0) {
            Audio_PlaySystemSound(0x25);
            cursor ^= 3;
        }
    }
    return cursor;
}


/**
 * Draws the blue gradient message window at (x, y), width x height.
 * Seen in play (2026-11-14): the window of the Game Boy gift messages, called with growing and
 * shrinking sizes while it opens and closes.
 */
void CartridgeCheck_DrawMessageWindow(s16 x, s16 y, s16 width, s16 height) {
    Color_RGB8 sp24 = { 0x00, 0x00, 0x32 }; // #000032
    Color_RGB8 sp20 = { 0x00, 0x00, 0xC8 }; // #0000C8

    Ui_DrawGradientPanel(x, y, width, height, &sp24, &sp20);
}
