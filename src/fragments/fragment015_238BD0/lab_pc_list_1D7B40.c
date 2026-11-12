/* Stadium Zero fragment015_238BD0. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_list/lab_pc_list_1D7B40.c. */

#include "fragments/lab_pc_list/lab_pc_list.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "audio_sfx.h"
#include "hal_libc.h"
#include "memmap.h"
#include "memory.h"
#include "pokemon_stats.h"
extern u8 D_8910D7D0[];
typedef struct unk_func_88309614 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
} unk_func_88309614;
typedef struct unk_func_88313894 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ unk_func_8830867C_02C_0CC_000_000* unk_0C;
    /* 0x10 */ char unk10[0xC];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ unk_func_88313894_020 unk_20;
    /* 0x40 */ unk_func_88313894_020 unk_40;
} unk_func_88313894;

#include "fragments/particle_math/particle_math.h"
#include "m2c_macros.h"
void func_8002ED18(s8*, s32, s8*);

void func_89004708(void);
void func_89004710(void);

void func_89004680(s32 arg0, s32 arg1, s32 arg2, u8* arg3) {
    DeckHandle* sp1C = Deck_Open(arg0, arg1, arg2, 1);

    Deck_WriteEntries(M2C_FIELD(arg3, u8**, 0), M2C_FIELD(arg3, s32*, 8), sp1C);

    if ((arg0 == 0x10) || (arg0 == 0x11) || (arg0 == 0x12) || (arg0 == 0x13)) {
        Deck_CloseAndFlushBox(sp1C);
    } else {
        Deck_CloseAndFlush(sp1C);
    }
}

void func_89004708(void) {
}

void func_89004710(void) {
}

void func_89004718(s8* arg0, s8* arg1) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (M2C_FIELD(arg1 + i * 0x10, s32*, 8) == 0) {
            M2C_FIELD(arg0, u16**, 0x30)[i] |= 0x100;
        }
    }
}

void func_890047E4(s8 *arg0, s8 *arg1) {
    u16 *temp_v0;

    if (M2C_FIELD(arg1, s32 *, 8) == 1) {
        temp_v0 = M2C_FIELD(arg0, u16 **, 0x30);
        *temp_v0 |= 0x200;
    }
}

void func_8900480C(s8* arg0, s8* arg1) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (M2C_FIELD(arg1 + i * 0x10, s32*, 8) == M2C_FIELD(arg1 + i * 0x10, s32*, 4)) {
            M2C_FIELD(arg0, u16**, 0x30)[i] |= 0x400;
        }
    }
}

void func_890048EC(s8 *arg0, s32 arg1) {
    u16 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x30) + (arg1 * 2);
    *temp_v0 |= 1;
}

typedef struct Rgba89004908 {
    /* 0x0 */ u8 r, g, b, a;
} Rgba89004908; // size = 0x4
void Ui_FillRectHighlighted(s32, s32, s32, s32, Rgba89004908);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
extern Rgba89004908 D_8900A5BC;
extern Rgba89004908 D_8900A730[];
extern Rgba89004908 D_800734B0[];
extern M2C_UNK D_800734A8;
void func_89004908(s32 x, s32 y, char* str, UNUSED s32 index, s32 flags) {
    Rgba89004908 color;
    UNUSED s32 pad[4]; // FAKE: stack padding

    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 0xD2, 0x16, D_8900A5BC);
    }
    Font_BeginTranslucentTextRendering();
    if (flags & 1) {
        color = ((Rgba89004908*)&D_800734A8)[1];
        color.a = 0x4C;
    } else if (flags & 0x100) {
        color = D_8900A730[(flags & 2) ? 0 : 1];
    } else if (flags & 0x200) {
        color = D_8900A730[(flags & 2) ? 0 : 1];
    } else if (flags & 0x400) {
        color = D_800734B0[(flags & 2) ? 0 : 1];
    } else {
        color = ((Rgba89004908*)&D_800734A8)[(flags & 2) ? 0 : 1];
    }
    func_8001AA9C(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(x + 8, y + 4, str);
    Font_EndTexturedTextRendering();
}

void Window_SetRect(s8*, s32, s32, s32, s32);
void Menu_Init(s8*, s32, s32, s32, s32, s32);
M2C_UNK func_80027804();
void func_89004AD4(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad[2]; // FAKE: stack padding

    Window_SetRect((s8 *)arg0, arg1, arg2, 0xBC, (arg4 * 0x1C) + 0x14);
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, Rgba89004908 *, 0x18) = D_8900A5BC;
    func_80027804((s8 *)arg0 + 0x50, arg3, arg4, arg4);
    Menu_Init((s8 *)arg0 + 0x2C, (s32)((s8 *)arg0 + 0x50), (s32)((s8 *)arg0 + 0x5C), (s32)func_89004908, 0xB0, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x34) = arg5;
    M2C_FIELD(arg0, s32 *, 0x4C) |= 0x10000;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawItems(s8 *, s32, s32, M2C_UNK, s32); /* extern */

void func_89004B98(s8 *arg0) {
    if (func_8002AE6C() == 0) {
        Menu_DrawItems(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0xA, 0xFFEF, 0);
    }
}

s32 func_8002DCE0(void*);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;
s32 func_89004BE0(s32 arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (func_8002DCE0((u8*)arg0 + 0x2C) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = M2C_FIELD(arg0, s32*, 0x34) + 1;
        }
    }
    return sp1C;
}

extern Gfx D_80060270[];
extern Rgba89004908 D_8900A73C;
extern Rgba89004908 D_8900A744;
extern char D_890189B0[];
void func_80029028(s32, s32, s32, s32, Rgba89004908);
void Font_SetColorForFlags(s32);
/**
 * Draws a Pokemon list row with its level (Ｌ%d).
 * @unverified Name and comment guessed from the code.
 */
void PcSort_DrawMonRow(s32 arg0, s32 arg1, u8* arg2, s32 arg3, s32 arg4) {
    u8* mon = arg2;
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xCC, 0x1A, D_8900A73C);
    func_80029028(arg0, arg1, 0xCC, 1, D_8900A744);
    func_80029028(arg0, arg1 + 0x1B, 0xCC, 1, D_8900A744);
    if (arg4 & 0x18) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xC6, 0x16, D_8900A5BC);
    }
    if (mon != NULL) {
        Font_BeginTranslucentTextRendering();
        Font_SetActive(8, 0);
        if ((mon[0] > 0) && (mon[0] < 0x98) && (D_80064C44[mon[0]][8] & 1)) {
            func_8001AA9C(0xFF, 0xC8, 0xA0, 0xFF);
        } else {
            Font_SetColorForFlags(arg4);
        }
        Font_Printf(arg0 + 0xA, arg1 + 4, (char*)(mon + 0x30));
        Font_SetActive(4, 0);
        Font_Printf(arg0 + 0x83, arg1 + 8, D_890189B0, mon[0x24]);
        Font_EndTexturedTextRendering();
    }
}

void func_89004E1C(s8* arg0, s32 arg1) {
    func_8002ED18(arg0, arg1, arg0 + 0x44);
}

void ScrollList_Init(s8*, s32, s8*, s32, void*, s32, s32);
void PcSort_DrawMonRow(s32, s32, u8*, s32, s32);

void func_89004E3C(s8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32*, 0x80) = arg1;
    M2C_FIELD(arg0, s32*, 0x84) = arg2;
    ScrollList_Init(arg0, arg3, arg0 + 0x44, 6, PcSort_DrawMonRow, 0xCC, 0x1C);
    M2C_FIELD(arg0, s32*, 0x20) |= 0x10000;
}

void func_8002F9D8(void *, s32, s32, s32, s32);
void func_8002F6C4(void *, s32, s32, s32, s32);
void func_8002BAB8(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void *, s32, s32);
extern Gfx D_80073450[];
extern u8 D_04011AB8[];
void func_89004EB0(s8 *arg0, s32 arg1) {
    if (arg1 & 0x200) {
        func_8002F9D8(arg0, M2C_FIELD(arg0, s32 *, 0x80), M2C_FIELD(arg0, s32 *, 0x84) + 0x10, arg1 | 0xFFED, 0);
    } else {
        func_8002F6C4(arg0, M2C_FIELD(arg0, s32 *, 0x80), M2C_FIELD(arg0, s32 *, 0x84) + 0x10, arg1 | 0xFFED, 0);
    }
    func_8002BAB8(M2C_FIELD(arg0, s32 *, 0x80) + 0x98, M2C_FIELD(arg0, s32 *, 0x84) + 0xBA, M2C_FIELD(M2C_FIELD(arg0, s8 **, 0), s32 *, 8), 2);
    func_8002BAB8(M2C_FIELD(arg0, s32 *, 0x80) + 0xB3, M2C_FIELD(arg0, s32 *, 0x84) + 0xBA, M2C_FIELD(M2C_FIELD(arg0, s8 **, 0), s32 *, 4), 2);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001BCB4(M2C_FIELD(arg0, s32 *, 0x80) + 0xAA, M2C_FIELD(arg0, s32 *, 0x84) + 0xBC, 8, 0xA, D_04011AB8, 8, 0);
}

s32 ScrollList_UpdateCursor(void*);
s32 func_80030230(void*);

/* Navigate the selected menu mode, then report cancel or confirm input. */
s32 func_89004FE4(void* menu, u32 flags) {
    s32 result = 0;
    s32 moved;
    s32 action;

    if (flags & 0x200) {
        moved = func_80030230(menu);
    } else {
        moved = ScrollList_UpdateCursor(menu);
    }
    if (moved == 0) {
        action = func_8002BC14(D_800603C0);
        if (action == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (action == 1) {
            result = 1;
        }
    }
    return result;
}

M2C_UNK func_8002B054(M2C_UNK, s32);                /* extern */

void func_89005068(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    func_8002B054(arg2, arg4);
}

void func_8002B018(s8*, s32, s32, s32, s32, s32, void*);
void func_8002DECC(s8*, s8*, s8*, void*, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
extern Rgba89004908 D_8900A580[];
extern Rgba89004908 D_8900A750;
extern Rgba89004908 D_8900A754;
extern u8 D_8900BFC0[];
extern u8 D_8900DAD0[];
extern u8 D_8900E858[];
extern u8 D_8900F5E0[];
extern u8 D_89010368[];
extern u8 D_89011E78[];
extern char D_890189B8[];

void func_89005098(s8* arg0, s32 x, s32 y, s8* arg3, s8* arg4) {

    Window_SetRect(arg0 + 4, x, y, 0x234, 0x172);
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = 0;
    M2C_FIELD(arg0, s32*, 0x18) = 0x801;
    M2C_FIELD(arg0, char**, 0x24) = D_890189B8;
    Window_SetRect(arg0 + 0x30, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 0x100, M2C_FIELD(arg0, s32*, 0xC) - 0xC, 0x6C);
    M2C_FIELD(arg0, s32*, 0x44) = 6;
    M2C_FIELD(arg0, Rgba89004908*, 0x48) = D_8900A750;
    M2C_FIELD(arg0, Rgba89004908*, 0x4C) = D_8900A754;
    func_8002B018(arg0 + 0x50, x + 0xE1, y + 0x48, 0x36, 0x2A, 0x30, D_8900DAD0);
    M2C_FIELD(arg0, Rgba89004908*, 0x68) = D_8900A580[2];
    M2C_FIELD(arg0, Rgba89004908*, 0x6C) = D_8900A580[3];
    M2C_FIELD(arg0, Rgba89004908*, 0x70) = D_8900A5BC;
    func_8002B018(arg0 + 0x7C, x + 0x11D, y + 0x48, 0x36, 0x2A, 0x30, D_8900BFC0);
    M2C_FIELD(arg0, Rgba89004908*, 0x94) = D_8900A580[0];
    M2C_FIELD(arg0, Rgba89004908*, 0x98) = D_8900A580[1];
    M2C_FIELD(arg0, Rgba89004908*, 0x9C) = D_8900A5BC;
    func_8002B018(arg0 + 0xA8, x + 0xE1, y + 0x78, 0x36, 0x2A, 0x30, D_8900F5E0);
    M2C_FIELD(arg0, Rgba89004908*, 0xC0) = D_8900A580[6];
    M2C_FIELD(arg0, Rgba89004908*, 0xC4) = D_8900A580[7];
    M2C_FIELD(arg0, Rgba89004908*, 0xC8) = D_8900A5BC;
    func_8002B018(arg0 + 0xD4, x + 0x11D, y + 0x78, 0x36, 0x2A, 0x30, D_8900E858);
    M2C_FIELD(arg0, Rgba89004908*, 0xEC) = D_8900A580[4];
    M2C_FIELD(arg0, Rgba89004908*, 0xF0) = D_8900A580[5];
    M2C_FIELD(arg0, Rgba89004908*, 0xF4) = D_8900A5BC;
    func_8002B018(arg0 + 0x100, x + 0xE1, y + 0xA8, 0x36, 0x2A, 0x30, D_89010368);
    M2C_FIELD(arg0, Rgba89004908*, 0x118) = D_8900A580[8];
    M2C_FIELD(arg0, Rgba89004908*, 0x11C) = D_8900A580[9];
    M2C_FIELD(arg0, Rgba89004908*, 0x120) = D_8900A5BC;
    func_8002B018(arg0 + 0x12C, x + 0x11D, y + 0xA8, 0x36, 0x2A, 0x30, D_89011E78);
    M2C_FIELD(arg0, Rgba89004908*, 0x144) = D_8900A580[12];
    M2C_FIELD(arg0, Rgba89004908*, 0x148) = D_8900A580[13];
    M2C_FIELD(arg0, Rgba89004908*, 0x14C) = D_8900A5BC;
    func_80027410(arg0 + 0x158, arg0 + 0x50, 0x2C, 6, 6);
    func_8002DECC(arg0 + 0x168, arg0 + 0x158, arg0 + 0x190, func_89005068, 2, 0, 0);
    M2C_FIELD(arg0, s32*, 0x290) = 1;
    M2C_FIELD(arg0, s32*, 0x28C) = 0;
    func_89004E3C(arg0 + 0x294, M2C_FIELD(arg0, s32*, 4) + 0xE, M2C_FIELD(arg0, s32*, 8) + 0x2C, (s32)arg3);
    func_89004E3C(arg0 + 0x31C, M2C_FIELD(arg0, s32*, 4) + 0x15A, M2C_FIELD(arg0, s32*, 8) + 0x2C, (s32)(arg3 + M2C_FIELD(arg0, s32*, 0x290) * 0x10));
    M2C_FIELD(arg0, s8**, 0x3A8) = arg3;
    M2C_FIELD(arg0, s8**, 0x3AC) = arg4;
    func_80027410(arg0 + 0x3B0, M2C_FIELD(arg3, s8**, 0), 0x50, M2C_FIELD(arg3, s32*, 4), 0);
    M2C_FIELD(arg0, s32*, 0) = 1;
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
M2C_UNK func_8001A944(s32, s32, s32);
M2C_UNK func_8001AB6C();
M2C_UNK func_8001ABBC();
void func_8001B884(s32, s32, s32, s32, void*, s32, s32);
void Font_SetColorForFlags(s32);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
s32 func_8002BC44(s32);
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern s32 D_8900A758[];
extern Color_RGBA8 D_8900A78C[2];
extern Color_RGBA8 D_8900A794[2];
extern void* D_89017A80[];
extern u8 D_89017A98[];
extern s32 D_89019114;

void func_890054D4(s32 arg0, s32 x, s32 y, s32 flags, u32 idx) {
    Color_RGBA8* col;

    if (flags & 2) {
        col = D_8900A78C;
    } else {
        col = D_8900A794;
    }
    Ui_FillRectPrimEnvColor(x, y, 0xCC, 0x1E, col[0], col[1]);
    if (idx != -1) {
        gSPDisplayList(gDisplayListHead++, D_80073408);
        switch (idx) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                func_8001B884(x + 0x10, y + 2, 0x18, 0x1A, D_89017A80[func_8002BC44(D_89019114)], 0x18, 0x200000);
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                func_8001B884(x + 2, y + 2, 0x28, 0x1A, D_89017A98, 0x30, 0x200000);
                break;
        }
        gSPDisplayList(gDisplayListHead++, D_80073438);
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(8, 0);
        func_8001A944(x + 0x2B, y + 5, D_8900A758[idx]);
        func_8001ABBC();
    }
}

typedef struct Slot890056A4 {
    s32 x;
    s32 y;
    s32 type;
    s32 iconX;
    void* tex;
} Slot890056A4;
s32 func_8002D3D0(u8*);
s32 func_8002D430(s32, s32);
void func_890074E0(s32, s32, s32, s32);
extern Slot890056A4 D_8900A79C[];
extern char D_89018AC4[];
extern char D_89018AD0[];
extern char D_89018ADC[];
extern char D_89018AE8[];
extern char D_89018AF4[];
extern char D_89018B00[];
extern char D_89018B08[];
extern char D_89018B0C[];
extern char D_89018B10[];
extern char D_89018B14[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];

/**
 * Draws Attack, Defense, Speed, Special and HP:%3d (？？？？？ when unknown).
 * @unverified Name and comment guessed from the code.
 */
void PcSort_DrawMonStats(s32 x, s32 y, u8* mon) {
    s32 count;
    s32 i;
    char* name;

    count = func_8002D3D0(mon);
    Font_BeginTranslucentTextRendering();
    func_8001AA9C(0xFF, 0xC8, 0xC8, 0xFF);
    Font_SetActive(4, 0);
    Font_Printf(x + 6, y + 0x56, D_89018AC4);
    Font_Printf(x + 0x91, y + 0x56, D_89018AD0);
    Font_Printf(x + 0x11C, y + 0x56, D_89018ADC);
    Font_Printf(x + 0x1A7, y + 0x56, D_89018AE8);
    func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
    Font_SetActive(8, 0);
    if ((mon[0] <= 0) || (mon[0] >= 0x98)) {
        name = D_89018AF4;
    } else {
        name = *(char**)D_80064C44[mon[0]];
    }
    Font_Printf(x + 8, y + 8, name);
    Font_Printf(x + 8, y + 0x24, D_89018B00, *(u16*)(mon + 0x26));
    Font_Printf(x + 0x46, y + 0x54, D_89018B08, *(u16*)(mon + 0x28));
    Font_Printf(x + 0xD1, y + 0x54, D_89018B0C, *(u16*)(mon + 0x2A));
    Font_Printf(x + 0x15C, y + 0x54, D_89018B10, *(u16*)(mon + 0x2C));
    Font_Printf(x + 0x1E7, y + 0x54, D_89018B14, *(u16*)(mon + 0x2E));
    for (i = 0; i < count; i++) {
        func_890074E0(D_8900A79C[i].x + x, D_8900A79C[i].y + y, func_8002D430((s32)mon, i), D_8900A79C[i].type);
    }
    Font_EndTexturedTextRendering();
    gSPDisplayList(gDisplayListHead++, D_80060290);
    for (i = 0; i < count; i++) {
        func_8001B884(D_8900A79C[i].iconX + x, D_8900A79C[i].y + y, 0x14, 0x14, D_8900A79C[i].tex, 0x14, 0x200000);
    }
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, s32);               /* extern */
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AB2C(M2C_UNK);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
extern M2C_UNK D_800734A8;

void func_89005958(s32 arg0, s32 arg1, s32 arg2) {
    func_8001AB6C();
    func_8001A384(0x10, 0);
    func_8001AA9C(M2C_FIELD(&D_800734A8, u8 *, 0), M2C_FIELD(&D_800734A8, u8 *, 1), M2C_FIELD(&D_800734A8, u8 *, 2), M2C_FIELD(&D_800734A8, u8 *, 3));
    func_8001AB2C(0x2C);
    func_8001A944(arg0 + 0xC, arg1 + 0x14, arg2);
    func_8001ABBC();
}

extern s32 D_8900A7EC[];
extern s32 D_8900A804[];
extern s32 D_8900A81C[];
extern s32 D_8900A834[];
void func_890019C8(s32, s32, s32, s32);
void PcSort_DrawMonStats();

void func_890059D0(s32* arg0) {
    s32 idx = arg0[0x170 / 4];
    s32** list;

    switch (arg0[0]) {
        case 1:
            func_890019C8(arg0[0x30 / 4] + 0x58, arg0[0x34 / 4] + 0x1A, D_8900A7EC[idx], D_8900A834[idx]);
            break;
        case 2:
            func_89005958(arg0[0x30 / 4], arg0[0x34 / 4], D_8900A804[idx]);
            break;
        case 3:
            func_89005958(arg0[0x30 / 4], arg0[0x34 / 4], D_8900A81C[idx]);
            break;
        case 4:
        case 6:
        case 7:
            if (arg0[0] == 7) {
                list = (s32**)&arg0[0x31C / 4];
            } else {
                list = (s32**)&arg0[0x294 / 4];
            }
            PcSort_DrawMonStats(arg0[0x30 / 4], arg0[0x34 / 4], ((s32*)list)[2] * 0x50 + *list[0]);
            break;
    }
}

void func_8002A8E0(s8*);
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, void*);
void func_8002E230(s8*, s32, s32, s32, s32);
void func_8002D024(s8*);
extern u8 D_8007356C[];
extern u8 D_800735C4[];

void func_89005AE0(s8* arg0) {
    s32 pad[1]; // FAKE: stack padding
    s32 m1;
    s32 m2;
    s32 mode;

    if (func_8002AE6C(arg0 + 4) == 0) {
        func_8002A8E0(arg0 + 0x30);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) - 0xC, 8, D_8900A5BC);
        func_80029028(M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 0xF4, M2C_FIELD(arg0, s32*, 0xC) - 0xC, 6, D_8900A5BC);
        func_80029028(M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 0xE, 8, 0xE6, D_8900A5BC);
        func_80029028(M2C_FIELD(arg0, s32*, 0xC) + M2C_FIELD(arg0, s32*, 4) - 0xE, M2C_FIELD(arg0, s32*, 8) + 0xE, 8, 0xE6, D_8900A5BC);
        func_80029028(M2C_FIELD(arg0, s32*, 4) + 0xDA, M2C_FIELD(arg0, s32*, 8) + 0xE, 0x80, 0xE6, D_8900A5BC);
        Ui_DrawTexturedDivider(M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 0x34) - 7, M2C_FIELD(arg0, s32*, 0xC), D_8007356C);
        Ui_DrawTexturedFrameDecal(M2C_FIELD(arg0, s32*, 4) + 0xC, M2C_FIELD(arg0, s32*, 8) + 0xC, 0xD0, 0xEA, D_800735C4);
        Ui_DrawTexturedFrameDecal(M2C_FIELD(arg0, s32*, 4) + 0x158, M2C_FIELD(arg0, s32*, 8) + 0xC, 0xD0, 0xEA, D_800735C4);
        func_8002E230(arg0 + 0x168, 0, 0, (M2C_FIELD(arg0, s32*, 0) == 1) ? 2 : 0x10, 0);
        func_890054D4((s32)arg0, M2C_FIELD(arg0, s32*, 4) + 0xE, M2C_FIELD(arg0, s32*, 8) + 0xE, 0, M2C_FIELD(arg0, s32*, 0x28C));
        func_890054D4((s32)arg0, M2C_FIELD(arg0, s32*, 4) + 0x15A, M2C_FIELD(arg0, s32*, 8) + 0xE, 0, M2C_FIELD(arg0, s32*, 0x290));
        m1 = 0xFDED;
        m2 = 0xFDED;
        mode = M2C_FIELD(arg0, s32*, 0);
        switch (mode) {
            case 4:
            case 6:
                m1 = 0xFDEF;
                break;
            case 5:
                m2 = 0xFFED;
            case 7:
                m1 = 0xFDFD;
                m2 |= 2;
                break;
        }
        func_89004EB0(arg0 + 0x294, m1);
        func_89004EB0(arg0 + 0x31C, m2);
        if ((M2C_FIELD(arg0, s32*, 0) == 2) || (M2C_FIELD(arg0, s32*, 0) == 0xA)) {
            func_89004B98(arg0 + 0x19C);
        }
        if ((M2C_FIELD(arg0, s32*, 0) == 3) || (M2C_FIELD(arg0, s32*, 0) == 0xB)) {
            func_89004B98(arg0 + 0x214);
        }
        func_890059D0((s32*)arg0);
        if ((M2C_FIELD(arg0, s32*, 0) == 0xA) || (M2C_FIELD(arg0, s32*, 0) == 0xB) || (M2C_FIELD(arg0, s32*, 0) == 0xC) || (M2C_FIELD(arg0, s32*, 0) == 0xD)) {
            func_8002D024(arg0 + 0x3C0);
        }
    }
}

void func_89000020(void* arg0, void* arg1);
void func_89000048(void*);

void func_89005E14(s8* arg0) {
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x248)] = 1;
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x1D0)] = M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x248)];
    func_89000020(arg0 + 0x31C, (void*)(M2C_FIELD(arg0, s32**, 0x294)[3] * M2C_FIELD(arg0, s32*, 0x29C) + M2C_FIELD(arg0, s32**, 0x294)[0]));
    func_89000048(arg0 + 0x294);
}

void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);

void func_89005EA4(s8* arg0) {
    u8 row[0x50];
    s32* matrix = M2C_FIELD(arg0, s32**, 0x294);

    func_80027654(matrix, row, M2C_FIELD(arg0, s32*, 0x29C));
    func_80027700(matrix, (u8*)(matrix[3] * M2C_FIELD(arg0, s32*, 0x3A4) + matrix[0]), M2C_FIELD(arg0, s32*, 0x29C));
    func_80027700(matrix, row, M2C_FIELD(arg0, s32*, 0x3A4));
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x28C)] = 1;
}


void func_89005F2C(s8* arg0) {
    u8 row[0x50];
    s32* matrix;

    func_80027654(M2C_FIELD(arg0, s32**, 0x31C), row, M2C_FIELD(arg0, s32*, 0x324));
    matrix = M2C_FIELD(arg0, s32**, 0x294);
    func_80027700(M2C_FIELD(arg0, s32**, 0x31C), (u8*)(matrix[3] * M2C_FIELD(arg0, s32*, 0x29C) + matrix[0]), M2C_FIELD(arg0, s32*, 0x324));
    func_80027700(M2C_FIELD(arg0, s32**, 0x294), row, M2C_FIELD(arg0, s32*, 0x29C));
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x290)] = 1;
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x28C)] = M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x290)];
}

void func_89000048(void*);

void func_89005FD8(s8* arg0) {
    func_89000048(arg0 + 0x294);
    M2C_FIELD(arg0, s32**, 0x3AC)[M2C_FIELD(arg0, s32*, 0x28C)] = 1;
    M2C_FIELD(arg0, s32*, 0) = (((M2C_FIELD(arg0, s32*, 0x28C) == 0) ? 1 : 0) == M2C_FIELD(M2C_FIELD(arg0, s8**, 0x294), s32*, 8)) ? 1 : 4;
}


void func_89006054(s8 *arg0) {
    s32 temp_v0;
    s8 *temp_a0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x248);
    temp_a0 = arg0 + 0x31C;
    M2C_FIELD(temp_a0, s32 *, -0x8C) = temp_v0;
    func_89004E1C(temp_a0, M2C_FIELD(arg0, s32 *, 0x3A8) + (temp_v0 * 0x10));
    M2C_FIELD(arg0, s32 *, 0) = 4;
}

void func_8002CEEC(s8*, s8*, s32, s32, s32);
s32 Ui_CheckConfirmPressed(s8*);
void func_8002D900(s8*);
void Menu_SkipDisabledForward(s8*);
s32 func_8002E3F0(s8*);
extern s8* D_8900A84C[];
extern s8 D_89018D8C[];
extern s8 D_89018DA4[];

typedef struct Mon8900609C {
    u8 species;
    u8 unk01[0x4F];
} Mon8900609C;

s32 func_8900609C(s8* arg0) {
    s32 ret;
    s32 res;
    s32 next;
    u16 flags;
    u8 species;
    Mon8900609C* mon;

    ret = 0;
    next = 0;
    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 1:
            if (func_8002E3F0(arg0 + 0x168) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (res == 1) {
                    if (M2C_FIELD(arg0, s32*, 0x170) == 1) {
                        func_8003F6AC(3);
                        ret = -1;
                    } else {
                        func_8003F6AC(2);
                        next = 2;
                        if ((M2C_FIELD(arg0, s32*, 0x170) == 3) || (M2C_FIELD(arg0, s32*, 0x170) == 4) || (M2C_FIELD(arg0, s32*, 0x170) == 5)) {
                            func_89004E1C(arg0 + 0x31C, (s32)(arg0 + 0x3B0));
                            M2C_FIELD(arg0, s32*, 0x290) = -1;
                        }
                    }
                }
            }
            break;
        case 2:
            res = func_89004BE0(arg0 + 0x19C);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 1;
            } else if (res > 0) {
                flags = M2C_FIELD(arg0, u16**, 0x1CC)[M2C_FIELD(arg0, s32*, 0x1D0)];
                if (flags & 0x100) {
                    M2C_FIELD(arg0, s32*, 0) = 0xA;
                    func_8002CEEC(arg0 + 0x3C0, D_8900A84C[M2C_FIELD(arg0, s32*, 0x170)], 0, 1, 0);
                    func_8003F6AC(8);
                } else if (flags & 0x200) {
                    func_8003F6AC(8);
                    M2C_FIELD(arg0, s32*, 0) = 0xA;
                    func_8002CEEC(arg0 + 0x3C0, D_89018D8C, 0, 1, 0);
                } else {
                    func_8003F6AC(2);
                    M2C_FIELD(arg0, s32*, 0x28C) = M2C_FIELD(arg0, s32*, 0x1D0);
                    func_89004E1C(arg0 + 0x294, (M2C_FIELD(arg0, s32*, 0x1D0) * 0x10) + M2C_FIELD(arg0, s32*, 0x3A8));
                    if ((M2C_FIELD(arg0, s32*, 0x170) == 3) || (M2C_FIELD(arg0, s32*, 0x170) == 4) || (M2C_FIELD(arg0, s32*, 0x170) == 5)) {
                        M2C_FIELD(arg0, s32*, 0) = 4;
                    } else {
                        next = 3;
                    }
                }
            }
            break;
        case 3:
            res = func_89004BE0(arg0 + 0x214);
            if (res == -1) {
                next = 2;
            } else if (res > 0) {
                flags = M2C_FIELD(arg0, u16**, 0x244)[M2C_FIELD(arg0, s32*, 0x248)];
                if (flags & 0x100) {
                    func_8003F6AC(8);
                    M2C_FIELD(arg0, s32*, 0) = 0xB;
                    func_8002CEEC(arg0 + 0x3C0, D_8900A84C[M2C_FIELD(arg0, s32*, 0x170)], 0, 1, 0);
                } else if (flags & 0x400) {
                    func_8003F6AC(8);
                    M2C_FIELD(arg0, s32*, 0) = 0xB;
                    func_8002CEEC(arg0 + 0x3C0, D_89018DA4, 0, 1, 0);
                } else {
                    func_8003F6AC(2);
                    func_89006054(arg0);
                }
            }
            break;
        case 4:
            res = func_89004FE4(arg0 + 0x294, 0);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 1;
            } else if (res == 1) {
                if (M2C_FIELD(arg0, s32*, 0x170) == 0) {
                    func_8003F6AC(2);
                    M2C_FIELD(arg0, s32*, 0) = 5;
                } else if (M2C_FIELD(arg0, s32*, 0x170) == 2) {
                    func_8003F6AC(2);
                    M2C_FIELD(arg0, s32*, 0) = 7;
                } else if (M2C_FIELD(arg0, s32*, 0x170) == 3) {
                    func_8003F6AC(2);
                    M2C_FIELD(arg0, u16**, 0x298)[M2C_FIELD(arg0, s32*, 0x29C)] |= 8;
                    M2C_FIELD(arg0, s32*, 0x3A4) = M2C_FIELD(arg0, s32*, 0x29C);
                    M2C_FIELD(arg0, s32*, 0) = 6;
                } else if (M2C_FIELD(arg0, s32*, 0x170) == 4) {
                    mon = M2C_FIELD(arg0, s32*, 0x29C) + *M2C_FIELD(arg0, Mon8900609C***, 0x294);
                    if ((mon->species <= 0) || (mon->species >= 0x98)) {
                        func_8003F6AC(8);
                    } else {
                        func_8003F6AC(2);
                        ret = 2;
                    }
                } else {
                    mon = M2C_FIELD(arg0, s32*, 0x29C) + *M2C_FIELD(arg0, Mon8900609C***, 0x294);
                    species = mon->species;
                    if ((species <= 0) || (species >= 0x98)) {
                        func_8003F6AC(8);
                    } else {
                        func_8003F6AC(2);
                        ret = 3;
                    }
                }
            }
            break;
        case 5:
            res = func_89004FE4(arg0 + 0x31C, 0x200);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 4;
            } else if (res == 1) {
                func_8003F6AC(0x18);
                func_89005E14(arg0);
                if ((((M2C_FIELD(arg0, s32*, 0x28C) == 0) ? 1 : 0) == M2C_FIELD(M2C_FIELD(arg0, s8**, 0x294), s32*, 8)) ||
                    (M2C_FIELD(M2C_FIELD(arg0, s8**, 0x31C), s32*, 4) == M2C_FIELD(M2C_FIELD(arg0, s8**, 0x31C), s32*, 8))) {
                    M2C_FIELD(arg0, s32*, 0) = 1;
                } else {
                    M2C_FIELD(arg0, s32*, 0) = 4;
                }
            }
            break;
        case 6:
            res = func_89004FE4(arg0 + 0x294, 0);
            if (res == -1) {
                func_8002D900(arg0 + 0x294);
                M2C_FIELD(arg0, s32*, 0) = 4;
            } else if (res == 1) {
                func_8003F6AC(0x18);
                func_89005EA4(arg0);
                func_8002D900(arg0 + 0x294);
                M2C_FIELD(arg0, s32*, 0) = 4;
            }
            break;
        case 7:
            res = func_89004FE4(arg0 + 0x31C, 0);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 4;
            } else if (res == 1) {
                func_8003F6AC(0x18);
                func_89005F2C(arg0);
                M2C_FIELD(arg0, s32*, 0) = 4;
            }
            break;
        case 10:
            if (Ui_CheckConfirmPressed(arg0 + 0x3C0) == 1) {
                M2C_FIELD(arg0, s32*, 0) = 2;
            }
            break;
        case 11:
            if (Ui_CheckConfirmPressed(arg0 + 0x3C0) == 1) {
                M2C_FIELD(arg0, s32*, 0) = 3;
            }
            break;
        case 12:
            if (Ui_CheckConfirmPressed(arg0 + 0x3C0) == 1) {
                M2C_FIELD(arg0, s32*, 0) = 4;
            }
            break;
        case 13:
            if (Ui_CheckConfirmPressed(arg0 + 0x3C0) == 1) {
                M2C_FIELD(arg0, s32*, 0) = 7;
            }
            break;
    }
    if (next > 0) {
        switch (next) {
            case 2:
                func_89004AD4(arg0 + 0x19C, M2C_FIELD(arg0, s32*, 4) + 0x25, M2C_FIELD(arg0, s32*, 8) - 0x14,
                              (s32)D_8900A758, 0xD, M2C_FIELD(arg0, s32*, 0x28C));
                func_89004718(arg0 + 0x19C, (s8*)M2C_FIELD(arg0, s32*, 0x3A8));
                if ((M2C_FIELD(arg0, s32*, 0x170) == 0) || (M2C_FIELD(arg0, s32*, 0x170) == 5)) {
                    func_890047E4(arg0 + 0x19C, (s8*)M2C_FIELD(arg0, s32*, 0x3A8));
                }
                break;
            case 3:
                func_89004AD4(arg0 + 0x214, M2C_FIELD(arg0, s32*, 4) + 0x173, M2C_FIELD(arg0, s32*, 8) - 0x14,
                              (s32)D_8900A758, 0xD, M2C_FIELD(arg0, s32*, 0x290));
                if (M2C_FIELD(arg0, s32*, 0x170) == 0) {
                    func_8900480C(arg0 + 0x214, (s8*)M2C_FIELD(arg0, s32*, 0x3A8));
                } else if (M2C_FIELD(arg0, s32*, 0x170) == 2) {
                    func_89004718(arg0 + 0x214, (s8*)M2C_FIELD(arg0, s32*, 0x3A8));
                }
                func_890048EC(arg0 + 0x214, M2C_FIELD(arg0, s32*, 0x28C));
                M2C_FIELD(arg0, s32*, 0x248) = 0;
                Menu_SkipDisabledForward(arg0 + 0x240);
                break;
        }
        M2C_FIELD(arg0, s32*, 0) = next;
    }
    return ret;
}

s8* func_80017860(s32);
void PokeIcon_OpenModelArchives(void);
s32 func_80018F2C(s8*, s32, s32, s32, s32, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void func_89000448(s32, s32, s32, s8*);
void func_89005098(s8*, s32, s32, s8*, s8*);
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern s32 D_89019108;
void func_890067B0(s8* arg0, s32 arg1) {
    s32 i;

    main_pool_push_state('OTPC');
    M2C_FIELD(arg0, s8**, 4) = func_80017860(1);
    M2C_FIELD(arg0, s32*, 8) = func_80018F2C(M2C_FIELD(arg0, s8**, 4), 0x80, 0x78, 0, 0, 0x78, 0x78, 0);
    PokeIcon_OpenModelArchives();
    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    M2C_FIELD(arg0, s32*, 0xC) = arg1;
    func_80027410(arg0 + 0x778C, arg0 + 0x52C, 0x50, 6, 0);
    for (i = 0; i < 8; i++) {
        func_80027410(arg0 + 0x779C + i * 0x10, arg0 + 0x70C + i * 0x960, 0x50, 0x1E, 0);
    }
    for (i = 0; i < 4; i++) {
        func_80027410(arg0 + 0x781C + i * 0x10, arg0 + 0x520C + i * 0x960, 0x50, 0x1E, 0);
    }
    func_89000448(0x20, D_89019108, 0, arg0 + 0x778C);
    for (i = 0; i < 8; i++) {
        func_89000448(0x21, D_89019108, i, arg0 + 0x779C + i * 0x10);
    }
    for (i = 0; i < 4; i++) {
        func_89000448(0x11, 0, i, arg0 + 0x781C + i * 0x10);
    }
    M2C_FIELD(arg0, s32*, 0x785C) = 0;
    i = 1;
    do {
        ((s32*)(arg0 + 0x785C))[i] = 0;
        i++;
    } while (i != 13);
    func_89005098(arg0 + 0x10, 0x26, 0x53, arg0 + 0x778C, arg0 + 0x785C);
    M2C_FIELD(arg0, s32*, 0) = 1;
}

M2C_UNK func_80002620(M2C_UNK);                     /* extern */

void func_890069C0(s32 arg0) {
    func_80002620(0x4F545043);
}

void Ui_DrawTintedScreenBackground(s32, s32, s32, s32, s32);
void func_89005AE0();
void func_8002CAD0(void*);
void PcBox_DrawMonStatusWindow(void*);
extern Color_RGB8 D_8900A5B8;

/**
 * Draws the Pokemon sorting screen for its current state, including the status window.
 * @unverified Name and comment guessed from the code.
 */
void PcSort_DrawScreen(s32* arg0) {
    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, D_8900A5B8.r, D_8900A5B8.g, D_8900A5B8.b);
    switch (*arg0) {
        case 1:
            func_89005AE0(arg0 + 4);
            break;
        case 2:
            func_89005AE0(arg0 + 4);
            func_8002CAD0((u8*)arg0 + 0x408);
            break;
        case 3:
            func_89005AE0(arg0 + 4);
            PcBox_DrawMonStatusWindow((u8*)arg0 + 0x46C);
            break;
        case 4:
            func_89005AE0(arg0 + 4);
            PcBox_DrawMonStatusWindow((u8*)arg0 + 0x46C);
            break;
    }
}

M2C_UNK func_80023268(s32, u8, M2C_UNK);            /* extern */
extern s32 D_89019108;

void func_89006AB4(s8 *arg0) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = M2C_FIELD(arg0, u8 **, 0);
    var_s1 = 0;
    if (M2C_FIELD(arg0, s32 *, 8) > 0) {
        do {
            func_80023268(D_89019108, *var_s0, 3);
            var_s1 += 1;
            var_s0 += 0x50;
        } while (var_s1 < M2C_FIELD(arg0, s32 *, 8));
    }
}

typedef struct Save89006B2C {
    /* 0x0000 */ char unk0000[0x778C];
    /* 0x778C */ s8 entry0[0x10];
    /* 0x779C */ s8 entries[8][0x10];
    /* 0x781C */ u8 entries2[4][0x10];
    /* 0x785C */ s32 flag0;
    /* 0x7860 */ s32 flags[8];
    /* 0x7880 */ s32 flags2[4];
} Save89006B2C;
void func_80022118(s32);
void func_800230C4(s32);
s32 func_8002207C(s32);
void func_80022188(s32);
void func_800243B8(void);
void func_8002D7D4(s32);
void func_89006B2C(Save89006B2C* arg0) {
    s32 dirty = 0;
    s32 i;
    s32 saved = 0;

    if (arg0->flag0 != 0) {
        dirty = 1;
    }
    for (i = 0; i < 8; i++) {
        if (arg0->flags[i] != 0) {
            dirty = 1;
            break;
        }
    }
    if (dirty != 0) {
        func_80022118(D_89019108);
    }
    if (arg0->flag0 != 0) {
        func_89004680(0x20, D_89019108, 0, (u8*)arg0->entry0);
        func_89006AB4(arg0->entry0);
    }
    for (i = 0; i < 8; i++) {
        if (arg0->flags[i] != 0) {
            func_89004680(0x21, D_89019108, i, (u8*)arg0->entries[i]);
            func_89006AB4(arg0->entries[i]);
        }
    }
    for (i = 0; i < 4; i++) {
        if (arg0->flags2[i] != 0) {
            func_89004680(0x11, D_89019108, i, arg0->entries2[i]);
            saved = 1;
        }
    }
    if (dirty != 0) {
        func_800230C4(D_89019108);
        if (func_8002207C(D_89019108) == 0) {
            func_8002D7D4(D_89019108);
            PcSort_DrawScreen((s32*)arg0);
        }
        func_80022188(D_89019108);
    }
    if (saved != 0) {
        func_800243B8();
    }
}

s32 func_89006CDC(s8* arg0) {
    s32 i;

    for (i = 0; i < 13; i++) {
        if (((s32*)(arg0 + 0x785C))[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8002CA34(s8* arg0, s32 arg1, s32 arg2);
void Save_DrawReportingWindow(s8* arg0);
s32 func_8002CD7C(s8* arg0);
void func_800407B0(s32, s32, s32);
s32 func_8900609C(s8* arg0);
void func_89007374(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16* arg6);
s32 func_89007CD8(s8* arg0);
extern u8 D_89018DBC[];

s32 func_89006D60(s8* arg0) {
    s32 ret = 0;
    s8* sub;
    u8* mon;
    s32 res;

    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 1:
            res = func_8900609C(arg0 + 0x10);
            if (res == -1) {
                if (func_89006CDC(arg0) != 0) {
                    M2C_FIELD(arg0, s32*, 0) = 2;
                    func_8002CA34(arg0 + 0x408, 0xCA, 0xAD);
                } else {
                    ret = 1;
                }
            } else if (res == 2) {
                mon = M2C_FIELD(arg0, s32*, 0x2AC) * 0x50 + M2C_FIELD(arg0, u8***, 0x2A4)[0];
                M2C_FIELD(arg0, s32*, 0) = 3;
                func_89007374(arg0 + 0x46C, 0x69, 0x7D, (s32)mon, 0,
                              D_800603C0, M2C_FIELD(arg0, u16**, 8));
            } else if (res == 3) {
                mon = M2C_FIELD(arg0, s32*, 0x2AC) * 0x50 + M2C_FIELD(arg0, u8***, 0x2A4)[0];
                M2C_FIELD(arg0, s32*, 0) = 4;
                func_89007374(arg0 + 0x46C, 0x69, 0x7D, (s32)mon,
                              (s32)D_89018DBC, D_800603C0, M2C_FIELD(arg0, u16**, 8));
                M2C_FIELD(arg0, s32*, 0x514) = 1;
            }
            break;
        case 2:
            sub = arg0 + 0x408;
            res = func_8002CD7C(sub);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 1;
            } else if (res > 0) {
                ret = 1;
                M2C_FIELD(arg0, s32*, 0x38) = 7;
                switch (res) {
                    case 2:
                        break;
                    case 1:
                        Save_DrawReportingWindow(sub);
                        func_89006B2C((Save89006B2C*)arg0);
                        break;
                }
            }
            break;
        case 3:
            res = func_8002BC14(D_800603C0);
            if ((res == -1) || (res == 1)) {
                func_8003F6AC(3);
                M2C_FIELD(arg0, s32*, 0) = 1;
            }
            break;
        case 4:
            res = func_89007CD8(arg0 + 0x46C);
            if (res == -1) {
                func_8003F6AC(3);
                M2C_FIELD(arg0, s32*, 0) = 1;
            } else if (res == 1) {
                func_800407B0(0x57, 0, 0);
                func_89005FD8(arg0 + 0x10);
                M2C_FIELD(arg0, s32*, 0) = 1;
            }
            break;
    }
    return ret;
}
