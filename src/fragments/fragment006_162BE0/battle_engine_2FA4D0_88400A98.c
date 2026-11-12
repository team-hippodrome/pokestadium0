/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_2FA4D0.h"

extern M2C_UNK D_88402E40;
extern M2C_UNK D_88402E5C;
extern s8 D_88402D98;
extern s8 D_88402DB4;
extern s8 D_88402E78;
extern s8 D_88402E94;

void func_88400A98(void) {
    s16 var_s0;
    s16 var_s1;
    s32 var_s2;

    var_s0 = 0x20;
    var_s1 = 0x14;
    var_s2 = 0;
    do {
        func_88400108(0);
        func_88400A1C((s16) (0xA0 - (var_s0 / 2)), (s16) (0x3C - (var_s1 / 2)), var_s0, var_s1);
        func_80006780();
        var_s2 += 1;
        var_s0 += 0x14;
        var_s1 += 4;
    } while (var_s2 != 8);
}

void func_88400B70(void) {
    s16 var_s0;
    s16 var_s1;
    s32 var_s2;

    var_s0 = 0xC4;
    var_s1 = 0x34;
    var_s2 = 0;
    do {
        func_88400108(0);
        func_88400A1C((s16) (0xA0 - (var_s0 / 2)), (s16) (0x3C - (var_s1 / 2)), var_s0, var_s1);
        func_80006780();
        var_s2 += 1;
        var_s0 -= 0x14;
        var_s1 -= 4;
    } while (var_s2 != 8);
}

void func_88400C48(s16 arg0, s16 arg1) {
    s32 var_a3;

    if (D_88403364 < 0x10) {
        var_a3 = D_88403364 * 0x10;
    } else if (D_88403364 < 0x23) {
        var_a3 = 0xFF;
    } else if (D_88403364 < 0x32) {
        var_a3 = (-D_88403364 * 0x10) + 0x320;
    } else {
        var_a3 = 0;
    }

    D_88403364++;
    if (D_88403364 >= 0x3D) {
        D_88403364 = 0;
    }

    Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, var_a3);
    Font_DrawCharAt(arg0, arg1, 0x2177);
}

void func_88400CE8(s32 arg0) {
    D_88403364 = 0x10;
    do {
        func_88400108(0);
        func_88400A1C(0x1E, 0x20, 0x104, 0x34);
        func_8001AB6C();
        func_8001A384(4, -1);
        func_8001AB2C(0x14);
        func_8001A944(0x2E, 0x28, arg0);
        func_88400C48(0x104, 0x3C);
        func_8001ABBC();
        func_80006780();
    } while (!(M2C_FIELD(D_800603C0, u16 *, 8) & 0x8000));
    func_8003F6AC(1);
    D_88402D70 = arg0;
}

void func_88400DAC(s8* arg0) {
    s32 i;
    s32 x1 = 0x1E;
    s32 x2 = 0x122;
    s32 y1 = 0x28;
    s32 y2 = 0x48;

    for (i = 1; i < 9; i++) {
        func_88400108(0);
        func_88400A1C(0x1E, 0x20, 0x104, 0x34);

        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x1, y1, x2, y2);

        Font_BeginTranslucentTextRendering();
        Font_SetActive(4, -1);
        Font_SetLineHeight(0x14);
        Font_Printf(0x2E, y1 - i * 4, (s8*)D_88402D70);
        Font_Printf(0x2E, 0x50 - i * 4, arg0);
        Font_EndTexturedTextRendering();
        BgStage_AdvanceFrame();
    }

    D_88402D70 = (s32)arg0;
}

void func_88400F4C(void) {
    func_8000A7B0(0xC);
    M2C_FIELD(&D_884034E0, u8 *, 1) = (u8) (M2C_FIELD(&D_884034E0, u8 *, 1) | 1);
    func_80006828(0x73, &func_88400108);
    M2C_FIELD(&D_884034E0, u8 *, 2) = (u8) (M2C_FIELD(&D_884034E0, u8 *, 2) & 0xFFDF);
    func_88400A98();
    func_800407B0(0x51, 0, 0);
    if (D_800AF986 & 8) {
        func_88400CE8(D_88402D88);
        func_88400DAC(D_88402D8C);
        func_88400CE8((s32) D_88402D8C);
    } else {
        func_88400CE8(D_88402D90);
        func_88400DAC(D_88402D94);
        func_88400CE8((s32) D_88402D94);
    }
    func_88400B70();
    M2C_FIELD(&D_884034E0, u8 *, 2) = (u8) (M2C_FIELD(&D_884034E0, u8 *, 2) | 0x20);
    func_80006828(0x2D, &func_88400108);
}

void func_800273E8(s8* arg0, s32 arg1);
s32 func_80027214(s8*, s32);
extern M2C_UNK D_88403648;
extern s8 D_88402D98;
extern s8 D_88402DB4;
M2C_UNK func_8003F6AC(M2C_UNK);
void func_88401040(void) {
    s8 sp8C[0x3C];
    s8 sp50[0x3C];
    s32 i = 0;
    s32 rec;
    s32 pad; // FAKE: stack padding

    rec = M2C_FIELD(D_88403370, s32 *, 0xC);
    func_800273E8(sp8C, (s32) &D_88402DB4);
    func_800273E8(sp50, (s32) &D_88402D98);
    if (func_80027214(sp8C, rec + 0xA8) != 0) {
        do {
            if (i++ == 0x2A) {
                M2C_FIELD(&D_88403648, s32 *, 0x14) = 1;
                func_8003F6AC(0x10);
                M2C_FIELD(&D_88403648, u8 *, 2) |= 0x20;
            }
            func_80027214(sp50, rec + 0xB4);
            func_88400108(0);
            func_80006780();
        } while (func_80027214(sp8C, rec + 0xA8) != 0);
    }
    func_80006828(0x19, &func_88400108);
}

void func_800273E8(s8* arg0, s32 arg1);
s32 func_80027214(s8*, s32);
extern M2C_UNK D_88403648;
extern s8 D_88402DD0;
extern s8 D_88402DEC;

M2C_UNK func_8003F6AC(M2C_UNK);
void func_8840115C(void) {
    s8 sp8C[0x3C];
    s8 sp50[0x3C];
    s32 i = 0;
    s32 rec;
    s32 pad; // FAKE: stack padding

    rec = M2C_FIELD(D_88403370, s32 *, 0xC);
    if (D_800AF986 & 0x18) {
        func_88400F4C();
    }
    func_800273E8(sp8C, (s32) &D_88402DEC);
    func_800273E8(sp50, (s32) &D_88402DD0);
    if (func_80027214(sp8C, rec + 0xA8) != 0) {
        do {
            if (i++ == 0xA) {
                M2C_FIELD(&D_88403648, s32 *, 0x14) = 1;
                M2C_FIELD(&D_88403648, u8 *, 2) |= 0x20;
                func_8003F6AC(0x10);
            }
            func_80027214(sp50, rec + 0xB4);
            func_88400108(0);
            func_80006780();
        } while (func_80027214(sp8C, rec + 0xA8) != 0);
    }
    func_80006828(0x19, &func_88400108);
}

extern Color_RGB8 D_88402F94;
extern Color_RGB8 D_88402F98;
extern char* D_88402D80;
extern char* D_88402D84;
extern char D_88403228[];
extern u8 D_8F4B2B30[];
extern Gfx D_80060398[];
s32 func_8840079C(s32);
void func_88400458(s32, s32, s32);

void func_88401290(void) {
    Color_RGB8 top = D_88402F94;
    Color_RGB8 bottom = D_88402F98;

    if (D_88403358 >= 0) {
        D_88403358 = func_8840079C(D_88403358);
        Ui_DrawGradientPanel(0x1E, 0x1E, 0x104, 0x18, &top, &bottom);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, -1);
        Font_SetLineHeight(0x10);
        Font_Printf(0x23, 0x24, D_88402D80);
        Font_EndTexturedTextRendering();
        func_88400458(0, 0x1E, 0x38);
        func_88400458(1, 0xA2, 0x38);
        func_88400458(2, 0x1E, 0x80);
        func_88400458(3, 0xA2, 0x80);
    } else {
        Ui_DrawGradientPanel(0x1E, 0x1E, 0x104, 0x4A, &top, &bottom);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(2, -1);
        Font_SetLineHeight(0x10);
        Font_Printf(0x32, 0x23, D_88402D84);
        Font_EndTexturedTextRendering();
    }
    Ui_DrawGradientPanel(0xBE, 0xCA, 0x64, 0x18, &top, &bottom);
    gSPDisplayList(gDisplayListHead++, gUiEnvTintTextureDL);
    Gfx_DrawTextureRgba32(0xC8, 0xCF, 0x10, 0xE, (u8*)Util_ConvertAddrToVirtAddr((uintptr_t)D_8F4B2B30), 0x10, 0);
    gSPDisplayList(gDisplayListHead++, D_80060398);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(2, -1);
    Font_Printf(0xDC, 0xD0, D_88403228);
    Font_EndTexturedTextRendering();
}

extern char D_88403234[];
extern char D_88403240[];
extern char D_8840324C[];
extern char D_88403254[];
extern char D_8840325C[];
extern char D_88403268[];
extern char D_8840327C[];
extern char D_88403290[];
extern char D_884032A0[];
extern u8 D_8F4B2EB0[];
void func_884014B4(s32 arg0, u8 arg1) {
    Color_RGB8 sp44 = {0x00, 0x00, 0x32};
    Color_RGB8 sp40 = {0x00, 0x00, 0xC8};
    static char *D_88402FA4[] = {D_88403234, D_88403240};
    static char *D_88402FAC[] = {D_8840324C, D_88403254};
    s32 row;

    row = arg0;
    Ui_DrawGradientPanel(0x32, 0x3C, 0xDC, 0x7D, &sp44, &sp40);
    gSPDisplayList(gDisplayListHead++, D_80060290);
    Gfx_DrawTextureRgba16(0x3A, (row * 20) + 0x63, 0x18, 0xE, (u8 *) Util_ConvertAddrToVirtAddr((uintptr_t) D_8F4B2EB0), 0x18, 0x200000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
    Font_BeginTranslucentTextRendering();
    Font_EnableTwoCycleTexturing();
    Font_SetActive(8, -2);
    Gfx_SetPrimColor(100, 255, 150, 255);
    Font_Printf(0x6E, 0x44, D_8840325C);
    Font_DisableTwoCycleTexturing();
    Font_SetActive(4, -2);
    Gfx_SetEnvColor(255, 255, ((row * 20) + 0x63 == 0x63) ? 0 : 255, 255);
    Font_Printf(0x52, 0x62, D_88403268, D_88402FA4[(arg1 & 1) != 0]);
    Gfx_SetEnvColor(255, 255, ((row * 20) + 0x63 == 0x77) ? 0 : 255, 255);
    Font_Printf(0x52, 0x76, D_8840327C, D_88402FAC[(arg1 & 2) != 0]);
    Gfx_SetEnvColor(255, 255, ((row * 20) + 0x63 == 0x8B) ? 0 : 255, 255);
    Font_Printf(0x52, 0x8A, D_88403290);
    Gfx_SetEnvColor(255, 255, ((row * 20) + 0x63 == 0x9F) ? 0 : 255, 255);
    Font_Printf(0x52, 0x9E, D_884032A0);
    Font_EndTexturedTextRendering();
}

void func_8840173C(s32 arg0, s32 arg1) {
    Color_RGB8 sp4C = { 0x00, 0x00, 0x32 };
    Color_RGB8 sp48 = { 0x00, 0x00, 0xC8 };
    UNUSED s32 pad; // FAKE: stack padding
    s16 pos[2];
    s32 temp;

    if (arg1 == 0) {
        temp = 0x28;
    } else {
        temp = 0x6E;
    }
    pos[1] = temp + 0x28;
    Ui_DrawGradientPanel(0x28, 0x82, 0xF0, 0x5A, &sp4C, &sp48);
    gSPDisplayList(gDisplayListHead++, D_80060290);
    Gfx_DrawTextureRgba16(pos[1], 0xC5, 0x18, 0xE, (u8*)Util_ConvertAddrToVirtAddr((uintptr_t)D_8F4B2EB0), 0x18, 0x200000);
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    Font_BeginTranslucentTextRendering();
    Font_EnableTwoCycleTexturing();
    Font_SetActive(4, -2);
    Gfx_SetPrimColor(100, 255, 150, 255);
    Font_Printf(0x30, 0x8A, D_884032A8);
    Font_DisableTwoCycleTexturing();
    Font_SetActive(8, -2);
    Gfx_SetEnvColor(255, 255, 100, 255);
    if (arg0 == 0) {
        Font_Printf(0x5A, 0xA2, D_884032CC);
    } else {
        Font_Printf(0x32, 0xA2, D_884032E0);
    }
    Font_SetActive(4, -1);
    if (arg1 == 0) {
        temp = 0;
    } else {
        temp = 0xFF;
    }
    Gfx_SetEnvColor(255, 255, temp, 255);
    Font_Printf(100, 0xC4, D_884032FC);
    if (arg1 == 1) {
        temp = 0;
    } else {
        temp = 0xFF;
    }
    Gfx_SetEnvColor(255, 255, temp, 255);
    Font_Printf(0xAA, 0xC4, D_88403304);
    Font_EndTexturedTextRendering();
}

s32 func_88401970(s32 arg0, s32 arg1, u8 arg2) {
    s32 loop = 1;
    s32 sel = 1;
    s32 buttons;

    do {
        func_88400108(0);
        func_884014B4(arg1, arg2);
        buttons = M2C_FIELD(D_800603C0, u16 *, 8);
        if (buttons & 0x300) {
            func_8003F6AC(1);
            sel ^= 1;
        } else if (buttons & 0x8000) {
            loop = 0;
        } else if (buttons & 0x4000) {
            sel = 1;
            loop = 0;
        }
        func_8840173C(arg0, sel);
        func_80006780();
    } while (loop);

    loop = sel == 0;
    if (loop) {
        if (arg0 == 0) {
            func_8003F6AC(2);
        } else {
            func_8003F6AC(0x1F);
        }
    } else {
        func_8003F6AC(3);
    }
    return loop;
}

void Save_InitializeBank3(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        func_800245E0(16, i);
    }
    for (i = 0; i < 4; i++) {
        func_800245E0(17, i);
    }
    for (i = 0; i < 4; i++) {
        func_800245E0(18, i);
    }
    func_800245E0(19, 0);
    func_800245E0(20, 0);
    func_800245E0(21, 0);
    func_8003BC9C(1);
    func_800418F0(1);
}

s32 func_80025214(void);
void func_80025224(u8);
void Save_CommitTypedRecord(s32, s32);
void func_88401B40(void) {
    s32 done = 0;
    s32 sel = 0;
    u8 flags = func_80025214();
    u8 diff;

    do {
        if (M2C_FIELD(D_800603C0, u16*, 8) & 0x800) {
            sel--;
            if (sel < 0) {
                sel = 3;
            }
            func_8003F6AC(1);
        } else if (M2C_FIELD(D_800603C0, u16*, 8) & 0x400) {
            sel++;
            if (sel >= 4) {
                sel = 0;
            }
            func_8003F6AC(1);
        } else if (M2C_FIELD(D_800603C0, u16*, 8) & 0x8000) {
            switch (sel) {
                case 0:
                    func_8003F6AC(2);
                    flags ^= 1;
                    break;
                case 1:
                    func_8003F6AC(2);
                    flags ^= 2;
                    break;
                case 2:
                    func_8003F6AC(2);
                    if (func_88401970(0, sel, flags) != 0 && func_88401970(1, sel, flags) != 0) {
                        flags = 0;
                        Save_InitializeBank3();
                    }
                    break;
                case 3:
                    done = 1;
                    func_8003F6AC(0x1D);
                    break;
            }
        } else if (M2C_FIELD(D_800603C0, u16*, 8) & 0x4000) {
            done = 2;
            func_8003F6AC(3);
        }
        func_88400108(0);
        func_884014B4(sel, flags);
        func_80006780();
    } while (done == 0);
    if (done == 1) {
        diff = func_80025214() ^ flags;
        if (diff != 0) {
            if (diff & 1) {
                if (flags & 1) {
                    func_8003BC9C(0);
                } else {
                    func_8003BC9C(1);
                }
            }
            if (diff & 2) {
                if (flags & 2) {
                    func_800418F0(0);
                } else {
                    func_800418F0(1);
                }
            }
            func_80025224(flags);
            Save_CommitTypedRecord(0x14, 0);
        }
    }
}

s32 func_88401D54(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_88400108(0);
        func_88401290();
        func_80006780();
        if (M2C_FIELD(D_800603C0, u16 *, 8) & 0x8000) {
            var_s0 = 1;
            func_8003F6AC(0x1B);
        } else if (M2C_FIELD(D_800603C0, u16 *, 8) & 0x4000) {
            func_8003F6AC(3);
            var_s0 = 2;
        } else if (M2C_FIELD(D_800603C0, u16 *, 8) & 1) {
            func_8003F6AC(2);
            func_88401B40();
        }
    } while (var_s0 == 0);
    if ((var_s0 == 1) && (D_88403358 >= 0)) {
        func_80025BE4(D_88403358);
    }
    return var_s0;
}

void func_88401E24(void) {
    s8 sp74[0x3C];
    s8 sp38[0x3C];
    s32 sp34;

    sp34 = M2C_FIELD(D_88403370, s32 *, 0xC);
    func_800273E8(sp74, (s32)&D_88402E24);
    func_800273E8(sp38, (s32)&D_88402E08);
    func_80010F8C(&D_88403648, 0xFFFF0000);
    func_80010F9C(&D_88403648, 0x2E);
    M2C_FIELD(&D_88403648, u8 *, 2) |= 0x20;
    func_80006998(0xFFFF);
    func_80005B98(0x1E);
    func_8000A7FC(0x3C);
    func_80041374(0x46, 0x3C);
    func_8003F6AC(0x23);
    while (func_80027214(sp74, sp34 + 0xA8)) {
        func_80027214(sp38, sp34 + 0xB4);
        func_88400108(0);
        func_80006780();
    }
}

void func_88401F38(void) {
    s8 sp1F;

    func_80025100(&sp1F, 0);
    func_8001107C(&D_88403648, 1, &D_8F4889B8);
    func_80010F14(&D_88403648, 1, &D_8F4014CC, 0x10000);
    func_80010F9C(&D_88403648, 0x2E);
    M2C_FIELD(&D_88403648, u8 *, 2) = (u8) (M2C_FIELD(&D_88403648, u8 *, 2) | 0x20);
    if (D_88403358 >= 0) {
        func_80019924(&D_88403378, 0, 0, *((M2C_UNK*)((u8*)&D_884037B0 + (sp1F * 4))));
        func_80010F14(&D_88403378, 1, *((M2C_UNK*)((u8*)&D_88402D74 + (sp1F * 4))), 0x10000);
        func_80010F9C(&D_88403378, 0x2E);
    }
    func_8003F6AC(0xB);
    func_80006828(0x14, (s32 *) func_88400108);
}

void func_88402038(void) {
    func_80006998(0xFFFF);
    func_80006828(0x13, &func_88400108);
    M2C_FIELD(&D_88403648, u8 *, 2) = (u8) (M2C_FIELD(&D_88403648, u8 *, 2) & 0xFFDF);
    if (D_88403358 >= 0) {
        func_800199E4(&D_88403378);
    }
}

void func_88402098(void) {
    s8 sp7C[0x3C];
    s8 sp40[0x3C];
    s32 temp_s0;

    temp_s0 = M2C_FIELD(D_88403370, s32 *, 0xC);
    func_8000A7FC(0x32);
    func_800273E8(sp7C, (s32) &D_88402E5C);
    func_800273E8(sp40, (s32) &D_88402E40);
    if (func_80027214(sp7C, temp_s0 + 0xA8) != 0) {
        do {
            func_80027214(sp40, temp_s0 + 0xB4);
            if (D_88403360 < 0x19) {
                D_88403360 += 1;
            }
            func_88400108(0);
            func_80006780();
        } while (func_80027214(sp7C, temp_s0 + 0xA8) != 0);
    }
}

extern M2C_UNK D_88403378;
extern M2C_UNK D_88403648;
extern s8 D_88402E78;
extern s8 D_88402E94;
M2C_UNK func_8003F6AC(M2C_UNK);
void func_88402174(void) {
    s8 sp94[0x3C];
    s8 sp58[0x3C];
    s32 i = 0;
    s32 temp_s1;
    s32 pad; // FAKE: stack padding

    temp_s1 = M2C_FIELD(D_88403370, s32 *, 0xC);
    func_800273E8(sp94, (s32) &D_88402E94);
    func_800273E8(sp58, (s32) &D_88402E78);
    if (func_80027214(sp94, temp_s1 + 0xA8) != 0) {
        do {
            if (i++ == 0xF) {
                M2C_FIELD(&D_88403648, u8 *, 2) |= 0x20;
                if (D_88403358 >= 0) {
                    M2C_FIELD(&D_88403378, u8 *, 2) |= 0x20;
                }
                func_8003F6AC(0x11);
            }
            func_80027214(sp58, temp_s1 + 0xB4);
            func_88400108(0);
            func_80006780();
        } while (func_80027214(sp94, temp_s1 + 0xA8) != 0);
    }
}

void func_884022A4(void) {
}

void func_884022AC(void) {
    func_88401F38();
    func_88402098();
    func_80006998(1);
    func_80006828(2, &func_88400108);
    func_80041374(0x46, 0x1E);
    if (D_88403358 < 0 || D_88403310[D_88403358].saveState != 0) {
        func_80006828(0x14, &func_88400108);
    }
}

s32 func_88402334(void) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp18 = M2C_FIELD(D_88403370, s32 *, 0xC);
    D_88403360 = 0;
    func_884000CC();
    func_800067BC(1);
    func_8000A7B0(0xA);
    func_80005B98(0x1E);
    func_8000D520(sp18 + 0xB4, &D_88402D98 + 2);
    func_8000D520(sp18 + 0xA8, &D_88402DB4 + 2);
    func_80006828(5, &func_88400108);
    func_88401040();
    temp_v0 = func_88401D54();
    sp1C = temp_v0;
    if (temp_v0 == 1) {
        func_884022AC();
    } else {
        func_88401E24();
    }
    return sp1C;
}

s32 func_884023F0(void) {
    s32 sp1C;

    sp1C = M2C_FIELD(D_88403370, s32 *, 0xC);
    func_80025BE4(D_88403358);
    D_88403360 = 0;
    func_884000CC();
    func_800067BC(1);
    func_80005B98(0x1E);
    func_8000D520(sp1C + 0xB4, &D_88402DD0 + 2);
    func_8000D520(sp1C + 0xA8, &D_88402DEC + 2);
    func_80006828(5, &func_88400108);
    func_8840115C();
    func_884022AC();
    return 1;
}

s32 func_8840248C(void) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp18 = M2C_FIELD(D_88403370, s32 *, 0xC);
    D_88403360 = 0;
    func_884000CC();
    func_8000A7FC(0x3C);
    func_800067BC(1);
    func_8000D520(sp18 + 0xB4, &D_88402E78 + 2);
    func_8000D520(sp18 + 0xA8, &D_88402E94 + 2);
    func_88402174();
    func_88402038();
    temp_v0 = func_88401D54();
    sp1C = temp_v0;
    if (temp_v0 == 1) {
        func_884022AC();
    } else {
        func_88401E24();
    }
    return sp1C;
}

void func_88402538(void) {
    s32 i;
    GbIdentityZ identity;

    for (i = 0; i < 4; i++) {
        GbSave_CopyPlayerIdentity(i, (GbSavePlayerIdentity*)&identity);
        Text_UntranscodeName(D_88403310[i].name, identity.name);
        D_88403310[i].trainerId = identity.trainerId;
        D_88403310[i].game = GbSave_GetPortGame(i);
        D_88403310[i].saveState = GbSave_GetSaveState(i);
    }
}

void func_884025E4(void) {
    if (func_80022B40() == 0) {
        D_88403358 = -1;
        return;
    }
    D_88403358 = func_80025BD8();
    if ((D_88403358 < 0) || (D_88403310[D_88403358].game == 0)) {
        D_88403358 = 0;
        while (D_88403310[D_88403358].game == 0) {
            D_88403358++;
        }
    }
}

extern u8 D_88402EB0[];
extern u8 D_8F4A4240[];
extern u8 D_8F4B2AF0[];
extern u8 D_8F4959C8[];
extern u8 D_8F4886F8[];
extern u8 D_8E825FE8[];
extern M2C_UNK D_8E802B64;
extern u8 D_8E924770[];
extern M2C_UNK D_8E902B64;
extern M2C_UNK D_8F4014B0;
extern Vec3f D_88403504;
extern Vec3f D_88403510;
extern s32 D_884037B4;
extern s32 D_884037B8;
extern s32 D_8840365C;
void func_884026A4(s32 arg0) {
    s8 sp27;
    MemoryBlock* sp20;

    sp20 = MainPool_AllocState(main_pool_get_available(), 0);
    ModelRenderer_InitDisplayRoots();
    ModelRenderer_AttachDisplayObject((DisplayObject*)&D_88403648);
    ModelRenderer_AttachDisplayObject((DisplayObject*)&D_88403378);
    ModelRenderer_AttachDisplayObject((DisplayObject*)&D_884034E0);
    D_88403370 = (s32)process_geo_layout(sp20, D_88402EB0);
    D_884037B0 = (s32)process_geo_layout(sp20, D_8F4A4240);
    D_884037B4 = (s32)process_geo_layout(sp20, D_8F4B2AF0);
    D_884037B8 = (s32)process_geo_layout(sp20, D_8F4959C8);
    func_80019924(&D_88403648, 0, 0, (s32)process_geo_layout(sp20, D_8F4886F8));
    if (D_800AF986 & 8) {
        func_80019924(&D_884034E0, 1, 0, (s32)process_geo_layout(sp20, D_8E825FE8));
        func_80010F14(&D_884034E0, 1, &D_8E802B64, 0x10000);
        M2C_FIELD(&D_884034E0, u8 *, 1) &= ~1;
        Vec3f_SetComponentsDuplicate(&D_88403504, 0.0f, 275.0f, 750.0f);
        Vec3f_SetComponentsDuplicate(&D_88403510, 3.0f, 3.0f, 3.0f);
    } else if (D_800AF986 & 0x10) {
        func_80019924(&D_884034E0, 0, 0, (s32)process_geo_layout(sp20, D_8E924770));
        func_80010F14(&D_884034E0, 1, &D_8E902B64, 0x10000);
        M2C_FIELD(&D_884034E0, u8 *, 1) &= ~1;
        Vec3f_SetComponentsDuplicate(&D_88403504, 0.0f, 275.0f, 750.0f);
        Vec3f_SetComponentsDuplicate(&D_88403510, 3.0f, 3.0f, 3.0f);
    }
    MainPool_FinalizeAllocation(sp20);
    if (arg0 == 0) {
        func_80010F14(&D_88403648, 1, &D_8F4014B0, 0x10000);
        M2C_FIELD(&D_88403648, s32 *, 0x14) = 0;
        M2C_FIELD(&D_88403648, u8 *, 2) &= ~0x20;
        return;
    }
    func_80010F14(&D_88403648, 1, &D_8F4014CC, 0xFFFF0000);
    func_80010F9C(&D_88403648, 0x4A);
    M2C_FIELD(&D_88403648, u8 *, 2) &= ~0x20;
    if (D_88403358 >= 0) {
        func_80025100(&sp27, 0);
        func_80019924(&D_88403378, 0, 0, *((M2C_UNK*)((u8*)&D_884037B0 + (sp27 * 4))));
        func_80010F14(&D_88403378, 1, *((M2C_UNK**)((u8*)&D_88402D74 + (sp27 * 4))), 0xFFFF0000);
        func_80010F9C(&D_88403378, 0x4A);
        M2C_FIELD(&D_88403378, u8 *, 2) &= ~0x20;
    }
    D_8840365C = 1;
}

void func_884029FC(void) {
    s32 sp2C;

    sp2C = func_800051F0(0, 2, 0x140, 0xF0, 0);
    M2C_FIELD(D_8840336C, s32 *, 0x18) = func_800023C4(0x10, 0);
    M2C_FIELD(D_8840336C, s32 *, 0x1C) = func_800023C4(0x10, 0);
    func_800051C0(M2C_FIELD(D_8840336C, s32 *, 0x18), 0, 2, 0x140, 0xF0, M2C_FIELD(M2C_FIELD(D_88403368, s8 **, 0x18), s32 *, 8));
    func_800051C0(M2C_FIELD(D_8840336C, s32 *, 0x1C), 0, 2, 0x140, 0xF0, M2C_FIELD(M2C_FIELD(D_88403368, s8 **, 0x1C), s32 *, 8));
    func_800052E8(M2C_FIELD(D_8840336C, s32 *, 0x18), sp2C);
    func_800052E8(M2C_FIELD(D_8840336C, s32 *, 0x1C), sp2C);
}

/**
 * Entry point of fragment006 (pool tag 'BCMP'). Loads its segments and the fragments
 * at 0x8F400000/0x8E800000/0x8E900000, polls the Game Boy saves, runs one of three
 * loops depending on arg0 and D_800AF986, and on success queues fragment014
 * (0x88000000) and returns 0x8040; otherwise returns 0x8010. Which game mode this is
 * has not been identified.
 * @unverified Name says only which fragment this is.
 */
s32 Fragment006_Main(s32 arg0, s32 arg1) {
    s32 result;
    s32 ret;

    main_pool_push_state('BCMP');

    D_88403368 = (s8*)StageContext_GetCurrent();
    D_8840336C = (s8*)StageContext_Allocate(0, 1, 2, 1, 2, 0);
    func_884029FC();

    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);
    Fragment_Load(((((u32)D_8F400000) & 0x0FF00000) >> 0x14) - 0x10, D_0038A540, D_003C5200);
    if (D_800AF986 & 8) {
        Fragment_Load(((((u32)D_8E800000) & 0x0FF00000) >> 0x14) - 0x10, D_003C5200, D_003CE090);
    }
    if (D_800AF986 & 0x10) {
        Fragment_Load(((((u32)D_8E900000) & 0x0FF00000) >> 0x14) - 0x10, D_003CE090, D_003D64A0);
    }

    func_8001A194(0xF, 0);
    func_88402538();
    func_884025E4();
    func_884026A4(arg0);
    StageLoader_UpdateSegments();
    StageContext_SaveAndSwitch((StageContext*)D_8840336C);
    Audio_PlayCommand(0x46, 3, 0);

    if (arg0 == 0) {
        if (D_800AF986 == 0) {
            result = func_88402334();
        } else {
            result = func_884023F0();
        }
    } else {
        result = func_8840248C();
    }

    StageContext_SaveAndSwitch((StageContext*)D_88403368);
    StageLoader_RunFrames(1);
    StageLoader_WaitForRetrace();
    Font_Free();

    main_pool_pop_state('BCMP');

    if (result == 1) {
        Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 1, arg1);
        ret = 0x8040;
    } else {
        ret = 0x8010;
    }
    return ret;
}
