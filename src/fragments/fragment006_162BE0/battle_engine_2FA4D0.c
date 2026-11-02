/* Stadium Zero fragment006_162BE0. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_2FA4D0.c, src/fragments/battle_engine/battle_engine_3020D0.c, src/fragments/trade_machine/trade_machine_291D60.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "status_icons.h"
#include "game_state.h"
#include "text_system.h"
#include "3D140.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"

#include "fragments/trade_machine/trade_machine.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "pokemon_stats.h"
#include "text_system.h"
#include "audio_sfx.h"
#define U64_NOP(x) ((u32)((u64)(x) | 0ULL))

#include "fragments/battle_engine/battle_engine.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "status_icons.h"
#include "game_state.h"
#include "text_system.h"
#include "3D140.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"
#include "stdarg.h"
#include "moves.h"
extern unk_D_843901A0* gBattleMessageQueues;

#include "m2c_macros.h"

void BattleHud_Noop(void);
void func_88400100(void);
void Trade_DrawSaveSeqMessageBackdrop(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_884022A4(void);

extern s32 D_88403358;

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

/*
 * func_88400064
 *
 * Light-node callback (the stage light's "angle" callback A, declared in
 * battle_engine.h as Battle_StageLightAngleCallbackA).  When called with
 * event 2 it takes the direction from the current camera's eye position to
 * its target position (Vec3f_CalculateDistanceAngles) and stores the two
 * resulting angles, each offset by +0x2000, in the light's halfwords at
 * offsets 0x1C and 0x1E.  Always returns 0.
 *
 * Structure follows Intro_LightAngleCallbackA / Completion_LightAngleCallbackA
 * in the Stadium 1 decomp, but Zero adds +0x2000 to both angles where those
 * subtract 0x2000 from the second one (the constants come from the retail
 * code).  The locals sit 4 bytes below where a plain declaration would put
 * them, which the unused leading `pad` reproduces.
 */
extern CameraNode* D_80060488;

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

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_8001B5F0();                            /* extern */

s32 func_884000CC(void) {
    func_8000B1FC();
    func_8000B220();
    func_8001B5F0();
    return 0;
}

void func_88400100(void) {
}

M2C_UNK func_80005770(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_8001560C(s32);                         /* extern */
M2C_UNK func_800158C0();                            /* extern */
extern M2C_UNK D_800AA150;
extern s32 D_88403370;

s32 func_88400108(s32 arg0) {
    func_884000CC();
    func_800158C0();
    func_800069CC();
    func_80005770(&D_800AA150, 0, 0, 0x140, 0xF0);
    func_8001560C(D_88403370);
    return 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_88400168; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_88400168.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88400458; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_88400458.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8840079C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_8840079C.s")
#endif

#ifdef NON_MATCHING
// Matches the ROM, but uses data data that is not placed in this file yet.
void Trade_DrawSaveSeqMessageBackdrop(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Color_RGB8 sp24 = { 0x58, 0x08, 0x00 };
    Color_RGB8 sp20 = { 0x58, 0x08, 0x00 };

    Ui_DrawGradientPanel(arg0, arg1, arg2, arg3, &sp24, &sp20);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_88400A1C.s")
#endif

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_88400A1C(s16, s16, s16, s16);          /* extern */

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

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_88400A1C(s16, s16, s16, s16);          /* extern */

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

extern s32 D_88403364;
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

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_8001AB2C(M2C_UNK);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */
extern s8 *D_800603C0;
extern s32 D_88402D70;
extern s32 D_88403364;

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

/*
 * func_88400F4C
 *
 * Scene setup that brackets some work between two runs of the same
 * callback.  Names in brackets are the ones symbol_addrs.txt gives the
 * called addresses; the meaning of the data and of most of the file-local
 * callees is not established.
 *
 *   1. func_8000A7B0(0xC) (Audio_PlayMusicIfChanged) is called.
 *   2. Bit 0 of byte 1 of D_884034E0 is set.
 *   3. func_80006828(0x73, func_88400108) (BgStage_RunUntilCondition) is
 *      run, i.e. timer value 0x73 with func_88400108 as the callback.
 *   4. Bit 5 (0x20) of byte 2 of D_884034E0 is cleared, func_88400A98() is
 *      called and func_800407B0(0x51, 0, 0) (Audio_PlayCommand) is called.
 *   5. Depending on bit 3 (value 8) of D_800AF986, the pair
 *      (D_88402D88, D_88402D8C) or the pair (D_88402D90, D_88402D94) is
 *      used: func_88400CE8 is called with the first value, func_88400DAC
 *      with the second, and func_88400CE8 again with the second value
 *      read as an integer.
 *   6. func_88400B70() is called, bit 5 of byte 2 of D_884034E0 is set
 *      again, and func_80006828(0x2D, func_88400108) is run.
 */
M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_8000A7B0(M2C_UNK);                     /* extern */
M2C_UNK func_800407B0(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
extern u16 D_800AF986;
extern s32 D_88402D88;
extern s8 *D_88402D8C;
extern s32 D_88402D90;
extern s8 *D_88402D94;
extern M2C_UNK D_884034E0;

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

#ifdef NON_MATCHING
/* TODO: decompile func_88401040; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_88401040.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8840115C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_8840115C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88401290; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_88401290.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_884014B4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_884014B4.s")
#endif

extern u8 D_8F4B2EB0[];
extern char D_884032A8[];
extern char D_884032CC[];
extern char D_884032E0[];
extern char D_884032FC[];
extern char D_88403304[];
void func_8840173C(s32 arg0, s32 arg1) {
    Color_RGB8 sp4C = { 0x00, 0x00, 0x32 };
    Color_RGB8 sp48 = { 0x00, 0x00, 0xC8 };
    UNUSED s32 pad;
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

void func_884014B4(s32, u8);
void func_8840173C(s32, s32);
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

void func_800245E0(s32 arg0, s32 arg1);
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

#ifdef NON_MATCHING
/* TODO: decompile func_88401B40; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_88401B40.s")
#endif

/*
 * func_88401D54
 *
 * Loops until a choice is made. Each pass calls func_88400108(0),
 * func_88401290() and func_80006780(), then tests the halfword at offset 8 of
 * the record D_800603C0 points to:
 *  - bit 0x8000: choice = 1, calls func_8003F6AC(0x1B);
 *  - else bit 0x4000: choice = 2, calls func_8003F6AC(3);
 *  - else bit 0x1: calls func_8003F6AC(2) and func_88401B40() and goes round
 *    again.
 * After the loop, if the choice is 1 and D_88403358 is not negative, calls
 * func_80025BE4(D_88403358). Returns the choice (1 or 2).
 *
 * What the bits, the functions called and D_88403358 are is not
 * established (the bits look like controller buttons but that is a guess
 * from the masks only). Matching notes: the halfword is read directly at
 * each test (the compiler shares one load) rather than through a local, and
 * func_8003F6AC(3) is written before `choice = 2` to match the ROM's
 * instruction order.
 */
M2C_UNK func_88401290();                            /* extern */
M2C_UNK func_88401B40();                            /* extern */
M2C_UNK func_80025BE4(s32);                         /* extern */
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

void func_800273E8(s8* arg0, s32 arg1);
s32 func_80027214(s8*, s32);
void func_80010F8C(void*, s32);
void func_80010F9C(void*, s32);
void func_8000A7FC(s32);
void func_80041374(s32, s32);
M2C_UNK func_80006998(M2C_UNK);
M2C_UNK func_80005B98(M2C_UNK);
extern M2C_UNK D_88403648;
extern s8 D_88402E24;
extern s8 D_88402E08;
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

void func_80025100(s8 *, void *);
M2C_UNK func_8001107C(M2C_UNK *, M2C_UNK, M2C_UNK *);
M2C_UNK func_80010F14(M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_80019924(M2C_UNK *, M2C_UNK, M2C_UNK, s32);
extern M2C_UNK D_88403378;
extern s32 D_88403358;
extern s32 D_884037B0[];
extern s32 D_88402D74[];
extern M2C_UNK D_8F4014CC;
extern M2C_UNK D_8F4889B8;

/**
 * Scene set-up that ends by running func_80006828(0x14, &func_88400108). Reads a signed
 * byte index through func_80025100(&sp1F, NULL), then sets up the object at D_88403648
 * (func_8001107C, func_80010F14 with D_8F4014CC and a 0x10000 argument, func_80010F9C
 * with 0x2E, and sets bit 0x20 of its byte at +2). If D_88403358 is not negative, also
 * sets up D_88403378 the same way, using the table entries D_884037B0[sp1F] and
 * D_88402D74[sp1F]. Finally calls func_8003F6AC(0xB) and func_80006828(0x14,
 * &func_88400108). What the index and the tables hold is not established.
 */
void func_88401F38(void) {
    s8 sp1F;

    func_80025100(&sp1F, NULL);
    func_8001107C(&D_88403648, 1, &D_8F4889B8);
    func_80010F14(&D_88403648, 1, &D_8F4014CC, 0x10000);
    func_80010F9C(&D_88403648, 0x2E);
    M2C_FIELD(&D_88403648, u8 *, 2) |= 0x20;
    if (D_88403358 >= 0) {
        func_80019924(&D_88403378, 0, 0, D_884037B0[sp1F]);
        func_80010F14(&D_88403378, 1, (M2C_UNK *)D_88402D74[sp1F], 0x10000);
        func_80010F9C(&D_88403378, 0x2E);
    }
    func_8003F6AC(0xB);
    func_80006828(0x14, &func_88400108);
}

M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_80006998(M2C_UNK);                     /* extern */
M2C_UNK func_800199E4(M2C_UNK *);                   /* extern */
extern s32 D_88403358;
extern M2C_UNK D_88403378;
extern M2C_UNK D_88403648;

void func_88402038(void) {
    func_80006998(0xFFFF);
    func_80006828(0x13, &func_88400108);
    M2C_FIELD(&D_88403648, u8 *, 2) = (u8) (M2C_FIELD(&D_88403648, u8 *, 2) & 0xFFDF);
    if (D_88403358 >= 0) {
        func_800199E4(&D_88403378);
    }
}

extern s32 D_88403360;
extern M2C_UNK D_88402E40;
extern M2C_UNK D_88402E5C;

/*
 * func_88402098
 *
 * Reads the word at offset 0xC of D_88403370 (call it `rec`), calls
 * func_8000A7FC(0x32) and fills two 0x3C-byte local buffers with
 * func_800273E8 from D_88402E5C and D_88402E40. Then, while
 * func_80027214(buf1, rec + 0xA8) returns non-zero, it calls
 * func_80027214(buf2, rec + 0xB4), increments D_88403360 if it is below
 * 0x19 (25), and calls func_88400108(0) and func_80006780().
 *
 * Same buffer pair and loop shape as func_88401E24 and func_82200618. What
 * the buffers and helpers are is not established. Matching note: the only
 * declared scalar is `temp_s0`; declaring a second one for rec + 0xA8
 * makes the stack frame 8 bytes larger than the ROM's (each declared local
 * seems to reserve a stack slot even when it lives in a register).
 */
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

#ifdef NON_MATCHING
/* TODO: decompile func_88402174; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_88402174.s")
#endif

void func_884022A4(void) {
}

#ifdef NON_MATCHING
/* TODO: decompile func_884022AC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_884022AC.s")
#endif

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_800067BC(M2C_UNK);                     /* extern */
M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_8000D520(s32, s8 *);                 /* extern */
M2C_UNK func_80025BE4(s32);                         /* extern */
M2C_UNK func_8840115C();                            /* extern */
M2C_UNK func_884022AC();                            /* extern */

M2C_UNK func_88401040();
extern s8 D_88402D98;
extern s8 D_88402DB4;
/**
 * Sibling of func_8840248C and func_884023F0. Reads the record pointer from
 * D_88403370 (+0xC), clears D_88403360, then calls func_884000CC(), func_800067BC(1),
 * func_8000A7B0(0xA) and func_80005B98(0x1E). Calls func_8000D520 twice with
 * (record + 0xB4, D_88402D98 + 2) and (record + 0xA8, D_88402DB4 + 2), runs
 * func_80006828(5, &func_88400108) and func_88401040(), then r = func_88401D54();
 * calls func_884022AC() if r == 1 and func_88401E24() otherwise. Returns r.
 * The record pointer is read before D_88403360 is cleared, as in func_8840248C.
 * What the screen is, and what the two +2 offsets select, is not established.
 */
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

extern s8 D_88402DD0;
extern s8 D_88402DEC;
extern s32 D_88403358;
extern s32 D_88403360;
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

/*
 * func_8840248C
 *
 * Clears D_88403360; reads the word at offset 0xC of D_88403370 (used as a
 * pointer); calls func_884000CC(), func_8000A7FC(0x3C) and func_800067BC(1).
 * Then calls func_8000D520 twice with (record + 0xB4, D_88402E78 + 2) and
 * (record + 0xA8, D_88402E94 + 2), where `record` is the pointer read above
 * (the neighbouring function func_884023F0 makes the same two calls with
 * D_88402DD0 and D_88402DEC). Calls func_88402174() and func_88402038(),
 * then r = func_88401D54(); calls func_884022AC() if r == 1 and
 * func_88401E24() otherwise. Returns r.
 *
 * What the screen/state it sets up is, and what the two +2 offsets select
 * (they are byte offsets into the data at D_88402E78 and D_88402E94), is not
 * established. Matching note: D_88403360 is cleared after the load of
 * the record pointer; the reverse order does not match.
 */
s32 func_88401D54();                                /* extern */
M2C_UNK func_88402174();                            /* extern */
extern s8 D_88402E78;
extern s8 D_88402E94;
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

typedef struct GbPortSummaryZ {
    /* 0x00 */ u8 saveState;
    /* 0x01 */ u8 game;
    /* 0x02 */ u16 trainerId;
    /* 0x04 */ char name[0xE];
} GbPortSummaryZ; // size = 0x12
extern GbPortSummaryZ D_88403310[4];
typedef struct GbIdentityZ {
    /* 0x00 */ u16 trainerId;
    /* 0x02 */ char name[10];
} GbIdentityZ;

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

#ifdef NON_MATCHING
/* TODO: decompile func_884025E4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_884025E4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_884026A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_884026A4.s")
#endif

s32 func_800023C4(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_800051C0(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
s32 func_800051F0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_800052E8(s32, s32);                    /* extern */
extern s8 *D_88403368;
extern s8 *D_8840336C;

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

#include "stage_loader.h"
extern u16 D_800AF986;
extern u8 D_01000000[];
extern u8 D_04000000[];
extern u8 D_8F400000[];
extern u8 D_8E800000[];
extern u8 D_8E900000[];
extern u8 D_88000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_00400F70[];
extern u8 D_004076E0[];
extern u8 D_0038A540[];
extern u8 D_003C5200[];
extern u8 D_003CE090[];
extern u8 D_003D64A0[];
extern u8 D_00235D70[];
extern u8 D_00238BD0[];
void func_88402538(void);
void func_884025E4(void);
void func_884026A4(s32);
s32 func_88402334(void);
s32 func_884023F0(void);
s32 func_8840248C(void);

s32 ClefairyGame_Main(s32 arg0, s32 arg1) {
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
