/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_2FA4D0.h"

void func_88400020(s32 arg0, s8 *arg1) {
    if (arg0 == 2) {
        if (D_88403358 >= 0) {
            M2C_FIELD(arg1, u8 *, 1) = (u8) (M2C_FIELD(arg1, u8 *, 1) | 1);
            return;
        }
        M2C_FIELD(arg1, u8 *, 1) = (u8) (M2C_FIELD(arg1, u8 *, 1) & 0xFFFE);
    }
}

void BattleHud_Noop(void) {
}

s32 func_88400064(s32 arg0, unk_D_86002F34_alt18* arg1) {
    UNUSED s32 pad; // keeps the retail stack layout: the three locals below sit 4 bytes lower
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        Vec3f_CalculateDistanceAngles(&D_80060488->view.targetPosition, &D_80060488->view.eyePosition, &sp28, &sp26, &sp24);
        arg1->unk_1C = sp26 + 0x2000;
        arg1->unk_1E = sp24 + 0x2000;
    }
    return 0;
}

s32 func_884000CC(void) {
    func_8000B1FC();
    func_8000B220();
    func_8001B5F0();
    return 0;
}

void func_88400100(void) {
}

s32 func_88400108(s32 arg0) {
    func_884000CC();
    func_800158C0();
    func_800069CC();
    func_80005770(&D_800AA150, 0, 0, 0x140, 0xF0);
    func_8001560C(D_88403370);
    return 0;
}

extern u8* D_88402F6C[4];
extern u8 D_04007298[];
extern u8 D_04008298[];
extern u8 D_04008F20[];
extern Gfx gUiEnvTintTextureDL[];
extern Gfx gUiRestoreTextureDL[];
void Gfx_DrawTextureIa8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);

void func_88400168(s32 x, s32 y, s32 port, s32 game) {
    u8* icons[4] = D_88402F6C;

    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    if (game == 0) {
        gDPSetEnvColor(gDisplayListHead++, 0xFF, 0xFF, 0xFF, 0x64);
    }
    Gfx_DrawTextureRgba16(x, y, 0x32, 0x20, D_04007298, 0x40, 0);
    Gfx_DrawTextureRgba16(x, y + 0x20, 0x32, 0x19, D_04008298, 0x40, 0);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    if (game != 0) {
        switch (game) {
            case 1:
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 0xFF, 0x00, 0x00, 0xFF);
                break;
            case 2:
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 0x00, 0x96, 0x00, 0xFF);
                break;
            case 3:
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 0x00, 0x32, 0xFF, 0xFF);
                break;
            case 7:
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 0xFF, 0xFF, 0x00, 0xFF);
                break;
        }
        Gfx_DrawTextureIa8(x + 6, y + 0x10, 0x26, 0x22, D_04008F20, 0x28, 0);
        gDPSetPrimColor(gDisplayListHead++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        Gfx_DrawTextureIa8(x + 9, y + 0x17, 0x20, 0x14, icons[port], 0x20, 0);
    } else {
        gDPSetPrimColor(gDisplayListHead++, 0, 0, 0x80, 0x80, 0x80, 0x64);
        Gfx_DrawTextureIa8(x + 9, y + 0x17, 0x20, 0x14, icons[port], 0x20, 0);
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
void func_88400168(s32, s32, s32, s32);

void func_88400458(s32 port, s32 x, s32 y) {
    Color_RGB8 top = D_88402F7C;
    Color_RGB8 bottom = D_88402F80;
    Color_RGB8 selTop = D_88402F84;
    Color_RGB8 selBottom = D_88402F88;

    if (port == D_88403358) {
        Ui_DrawGradientPanel(x, y, 0x80, 0x46, &selTop, &selBottom);
    } else {
        Ui_DrawGradientPanel(x, y, 0x80, 0x46, &top, &bottom);
    }
    func_88400168(x + 6, y + 6, port, D_88403310[port].game);
    Font_BeginTranslucentTextRendering();
    if (D_88403310[port].game != 0) {
        Font_SetActive(1, -2);
        Gfx_SetEnvColor(0xFF, 0xBD, 0x6B, 0xFF);
        Font_Printf(x + 0x3E, y + 6, D_88403170);
        Font_Printf(x + 0x52, y + 6, D_88403174);
        Font_Printf(x + 0x3E, y + 0x24, D_88403178);
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        if (D_88403310[port].saveState == 0) {
            Font_SetActive(2, -2);
            Font_Printf(x + 0x3E, y + 0x12, D_88403184, D_88403310[port].trainerId);
            Font_SetActive(2, -1);
            Font_Printf(x + 0x3E, y + 0x30, D_88403310[port].name);
        } else {
            Font_SetActive(2, -2);
            Font_Printf(x + 0x3E, y + 0x12, D_8840318C);
            Font_SetActive(2, -1);
            Font_Printf(x + 0x3E, y + 0x30, D_88403198);
        }
    } else {
        Font_SetActive(1, -1);
        Gfx_SetEnvColor(0xFF, 0xFF, 0x64, 0xFF);
        if (D_88403310[port].saveState == 2) {
            Font_Printf(x + 0xE, y + 0x14, D_884031A4);
            Font_Printf(x + 0x1E, y + 0x23, D_884031BC);
        } else if (D_88403310[port].saveState == 1) {
            switch (GbSave_GetPortAvailability(port)) {
                case 1:
                    Font_Printf(x + 0x19, y + 0x14, D_884031D0);
                    Font_Printf(x + 0x19, y + 0x23, D_884031E0);
                    break;
                case 2:
                    Font_Printf(x + 4, y + 0x14, D_884031F4);
                    Font_Printf(x + 0x14, y + 0x23, D_88403210);
                    break;
            }
        }
    }
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_8840079C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_8840079C.s")
#endif


void Trade_DrawSaveSeqMessageBackdrop(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Color_RGB8 sp24 = { 0x00, 0x00, 0x32 };
    Color_RGB8 sp20 = { 0x00, 0x00, 0xC8 };

    Ui_DrawGradientPanel(arg0, arg1, arg2, arg3, &sp24, &sp20);
}
