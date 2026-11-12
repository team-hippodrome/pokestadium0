/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragments/lab_pc_list/lab_pc_list.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "pokemon_stats.h"
#include "save_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "status_icons.h"
#include "gb_save.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#include "fragments/pokemon_lab_support/pokemon_lab_support.h"
extern s32 pad_D_8831A4DC[8];
#include "fragments/lab_pc/lab_pc.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "pokemon_stats.h"
#include "save_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "audio_sfx.h"
#include "hal_libc.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#include "fragments/particle_math/particle_math.h"
#include "m2c_macros.h"
void func_8002ED18(s8*, s32, s8*);
void func_8900020C(void);
s32 LabItem_ComputeRemainingCapacity(s32 arg0, unk_func_8820BE14_06C* arg1);
s32 LabItem_ComputeMaxTransferQuantity(s32 arg0, unk_func_8820BE14_06C* arg1);
s32 LabItem_FindOrAllocateGamePakBoxSlot(unk_func_8821421C_07C* arg0, s32 arg1, char* arg2);
void LabItem_LoadGamePakBoxSlots(unk_func_8821421C_07C* arg0);
void LabItem_ReadDeckEntries(s32 arg0, s32 arg1, s32 arg2, unk_func_8820BE14_06C* arg3);
void func_800275E4(s32, s32);
void func_80030744(s32*, s32);
void func_800275E4(s32, s32);
int func_800274E0();
void func_80030744(s32*, s32);
extern M2C_UNK D_8900A5B8;
void func_8002A8C4(s8*, s32, s32, s32, s32);
void func_8002AE94(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);
extern Color_RGBA8 D_8900A5C0;
extern char D_89018460[];
extern char D_89018468[];
extern s32 D_800603C0;
M2C_UNK func_8001A944(s32, s32, ...);
void func_80029658(s32, s32, s32, void*);
void func_8002A550(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_8002AF04(s8*, s32);
extern u8 D_8007356C[];
extern M2C_UNK D_800734A8;
extern Gfx D_80060270[];
extern Color_RGBA8 D_8900A5C4;
extern Color_RGBA8 D_8900A5C8;
extern Color_RGBA8 D_8900A5CC;
s32 func_8002B390(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;
#include "fragments/fragment015_238BD0/lab_pc_list_1CEA00_types.h"
extern Rgba89000D50 D_8900A5BC;
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_8001AA60(s32, s32, s32);
void func_80027F20(s32);
void func_80029A64(s32, s32, s32, s32, Color_RGBA8);
void func_8002D024(s8*);
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern Color_RGBA8 D_80073520;
extern u8 D_04002130[];
extern u8 D_04002238[];
extern u8 D_04002340[];
extern u8 D_04002448[];
extern char D_89018470[];
extern s32 D_800603C0;
extern M2C_UNK D_89018474;
void func_8002A0AC(s32, s32, s32, s32, Rgba89000D50);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
extern Rgba89000D50 D_8900A5D4[];
extern M2C_UNK D_800734A8;
void func_8002A8C4(s8*, s32, s32, s32, s32);
void func_8002D880(s8*, s32, s32, s32, s32, s32);
M2C_UNK func_80027804();
s32 func_8002DCE0(void*);
extern Gfx D_80060270[];
extern Rgba89000D50 D_8900A5E0;
extern Rgba89000D50 D_8900A5E8;
extern Rgba89000D50 D_8900A5EC[];
extern char D_8901848C[];
char* func_8001FDC8(u8, char*);
s32 func_80031C24(u8);
s32 func_80031CC8(u8);
void func_80027F20(s32);
void func_8002EC24(s8*, s32, s8*, s32, void*, s32, s32);
void LabItem_DrawItemCountRow();
void func_8002F9D8(void *, s32, s32, s32, s32);
void func_8002F6C4(void *, s32, s32, s32, s32);
void func_8002BAB8(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void *, s32, s32);
extern Gfx D_80073450[];
extern u8 D_04011AB8[];
s32 func_8002FD8C(void*);
s32 func_80030230(void*);
extern ColorPair890017FC D_8900A608;
extern ColorPair890017FC D_8900A610;
extern u8* D_89017A80[];
extern u8 D_89017A98[];
extern s32 D_89019114;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);
void func_80027F20(s32);
s32 func_8002BC44(s32);
M2C_UNK func_8001A944(s32, s32, ...);
extern M2C_UNK D_800734A8;
M2C_UNK func_8001A944(s32, s32, ...);
extern M2C_UNK D_800734A8;
extern s32 D_8900A650[];
extern char* D_8900A660[];
extern char* D_8900A66C[];
extern s8* D_8900A678[];
s32 func_80031BC0(u8, char *);
typedef struct LabItemGridZ {
    /* 0x00 */ u8* data;
    /* 0x04 */ s32 pad04[2];
    /* 0x0C */ s32 stride;
} LabItemGridZ;
typedef struct LabItemCursorZ {
    /* 0x00 */ LabItemGridZ* grid;
    /* 0x04 */ s32 pad04;
    /* 0x08 */ s32 selected;
} LabItemCursorZ;
#define CURSOR(p) ((LabItemCursorZ*)((p) + 0x1E4))
void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);
void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);
extern Color_RGBA8 D_8900A698;
extern u8 D_8900A69C[];
extern char D_89018660[];
extern char D_8901866C[];
void func_8002A3F8(void*, s32, s32);
void func_80027F20(s32);
extern Col89002C10 D_8900A6AC;
extern Col89002C10 D_8900A6B0;
extern char D_89018678[];
void LabItem_DrawTrainerInfo();
void func_8002A8C4(s8*, s32, s32, s32, s32);
void func_8002D880(s8*, s32, s32, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void func_80029658(s32, s32, s32, void*);
void func_8002A8E0(void*);
void func_8002DAD8(void*, s32, s32, s32, s32);
extern u8 D_8007356C[];
extern u8 D_89018688[];
s32 func_8002DC04(void*);
void func_8002B018(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern u8 D_8900A580[];
extern u8 D_8900A584[];
extern u8 D_8900A5A0[];
extern u8 D_8900A5A4[];
extern u8 D_8900A5A8[];
extern u8 D_8900A5AC[];
extern Rgba89000D50 D_8900A6B4;
extern Rgba89000D50 D_8900A6B8;
extern u8 D_8900BFC0[];
extern u8 D_89010368[];
extern u8 D_890110F0[];
typedef Color_RGBA8 Rgba8900A6BC; // size = 0x4
typedef struct Color8900A6BC {
    /* 0x0 */ Rgba8900A6BC c[2];
} Color8900A6BC; // size = 0x8
extern Color8900A6BC D_8900A6BC;
extern Color8900A6BC D_8900A6C4;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern u8 D_89017A98[];
extern char D_890186C0[];
extern char D_890186CC[];
void func_8002A550(s32, s32, s32, s32, Rgba8900A6BC, Rgba8900A6BC);
void func_80027F20(s32);
extern s32 D_8900A6CC[];
extern s8 *D_8900A6D8[];
void func_800295E8(s32, s32, s32, s32, u8*);
extern u8 D_800735C4[];
void func_8002B054(s8*, s32);
void func_8002A8E0(void*);
s32 func_8002B2B0(void *);
s32 func_890013F8(void *, u32);
M2C_UNK func_800069CC();


extern s32 D_89019108;
extern s32 D_89019118;
extern u8 D_8901911C[];
void func_80022118(s32);
void func_80022188(s32);
s32 func_8002207C(s32);
void func_8002D7D4(s32);
void func_800243B8(void);
void func_800245E0(s32, s32);
void func_89000494(s32, s32, s32, s8*, s32, void*, s32);
void func_8900379C(void*);
typedef struct Slot89003880 {
    /* 0x00 */ s32 active;
    /* 0x04 */ char unk04[0x10];
} Slot89003880; // size = 0x14
typedef struct Ctx89003880 {
    /* 0x000 */ char unk000[0xA20];
    /* 0xA20 */ Slot89003880 slots[1];
} Ctx89003880;
void func_89003880(s8* arg0) {
    s32 locked = 0;
    s32 flush = 0;

    if ((M2C_FIELD(arg0, s32*, 0xA10) != 0) || (M2C_FIELD(arg0, s32*, 0xA14) != 0)) {
        locked = 1;
    }
    if (locked) {
        func_80022118(D_89019108);
    }
    if (M2C_FIELD(arg0, s32*, 0xA10) != 0) {
        func_89000494(0x23, D_89019108, 0, arg0 + 0x9E0, 0, NULL, -1);
    }
    if (M2C_FIELD(arg0, s32*, 0xA14) != 0) {
        func_89000494(0x22, D_89019108, 0, arg0 + 0x9F0, 0, NULL, -1);
    }
    if (M2C_FIELD(arg0, s32*, 0xA1C) != -1) {
        if (((Ctx89003880*)arg0)->slots[M2C_FIELD(arg0, s32*, 0xA1C)].active != 0) {
            if (M2C_FIELD(arg0, s32*, 0xA18) != 0) {
                flush = 1;
                if (M2C_FIELD(arg0, s32*, 0xA08) == 0) {
                    func_800245E0(0x12, M2C_FIELD(arg0, s32*, 0xA1C));
                } else {
                    func_89000494(0x12, 0, M2C_FIELD(arg0, s32*, 0xA1C), arg0 + 0xA00, 0, NULL, -1);
                }
            }
        } else if (M2C_FIELD(arg0, s32*, 0xA08) > 0) {
            flush = 1;
            func_89000494(0x12, 0, M2C_FIELD(arg0, s32*, 0xA1C), arg0 + 0xA00, 0, D_8901911C, D_89019118);
        }
    }
    if (locked) {
        if (func_8002207C(D_89019108) == 0) {
            func_8002D7D4(D_89019108);
            func_8900379C((M2C_UNK*)arg0);
        }
        func_80022188(D_89019108);
    }
    if (flush) {
        func_800243B8();
    }
}

s32 func_89003A50(s32* arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (arg0[0x284 + i] != 0) {
            return 1;
        }
    }

    return 0;
}

void func_8002CA34(s8*, s32, s32);
void func_89000588(s8*, s32, s32, s8*, s8*);
s32 func_8002CD7C(s8*);
void func_8002CC44(s8*);
s32 func_89000828(s8*);
void func_89002C10(s8*, s32, s32, s8*);
s32 func_89002DE4(s8*);
void func_89000448(s32, s32, s32, s8*);
void func_89002E58(s8*, s32, s32, s8*, s8*);
s32 func_8900352C(s8*);
void func_890022D0(s8*);
s32 func_89002318(s8*);
extern s8 D_8901871C[];
extern s8 D_89018728[];
extern s8 D_89018760[];
extern s8 D_8901876C[];

s32 func_89003A88(s8* arg0) {
    s32 ret = 0;
    s32 res;

    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 1:
            res = func_89002318(arg0 + 4);
            if (res == -1) {
                if (func_89003A50((s32*)arg0) != 0) {
                    M2C_FIELD(arg0, s32*, 0) = 2;
                    func_8002CA34(arg0 + 0x4E8, 0xCA, 0xAD);
                } else {
                    ret = 1;
                }
            } else if (res > 0) {
                switch (res) {
                    case 1:
                        M2C_FIELD(arg0, s32*, 0) = 3;
                        func_89000588(arg0 + 0x54C, 0xBA, 0xAE, D_8901871C, D_89018728);
                        M2C_FIELD(arg0, s32*, 0x5FC) = 1;
                        break;
                }
            }
            break;
        case 2:
            res = func_8002CD7C(arg0 + 0x4E8);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 1;
            } else if (res > 0) {
                ret = 1;
                switch (res) {
                    case 2:
                        break;
                    case 1:
                        func_8002CC44(arg0 + 0x4E8);
                        func_89003880(arg0);
                        break;
                }
            }
            break;
        case 3:
            res = func_89000828(arg0 + 0x54C);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 1;
            } else if (res == 1) {
                func_89002C10(arg0 + 0x604, 0x2B, 0x5C, arg0 + 0xA20);
                M2C_FIELD(arg0, s32*, 0) = 4;
            }
            break;
        case 4:
            res = func_89002DE4(arg0 + 0x604);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 1;
                M2C_FIELD(arg0, s32*, 0xA08) = 0;
            } else if (res == 1) {
                func_89000448(0x12, 0, M2C_FIELD(arg0, s32*, 0x658), arg0 + 0xA00);
                func_89002E58(arg0 + 0x68C, 0xD6, 0x45, (s8*)&((Ctx89003880*)arg0)->slots[M2C_FIELD(arg0, s32*, 0x658)], arg0 + 0xA00);
                M2C_FIELD(arg0, s32*, 0) = 5;
            }
            break;
        case 5:
            res = func_8900352C(arg0 + 0x68C);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 4;
            } else if (res == 1) {
                M2C_FIELD(arg0, s32*, 0) = 6;
                func_89000588(arg0 + 0x54C, 0xBA, 0xAE, D_89018760, D_8901876C);
                M2C_FIELD(arg0, s32*, 0x5FC) = 1;
            }
            break;
        case 6:
            res = func_89000828(arg0 + 0x54C);
            if (res == -1) {
                M2C_FIELD(arg0, s32*, 0) = 5;
            } else if (res == 1) {
                M2C_FIELD(arg0, s32*, 0xA1C) = M2C_FIELD(arg0, s32*, 0x658);
                M2C_FIELD(arg0 + M2C_FIELD(arg0, s32*, 0xA1C) * 0x14, s32*, 0xA20) = 0;
                M2C_FIELD(arg0, s32*, 0xA08) = 0;
                func_890022D0(arg0 + 4);
                M2C_FIELD(arg0, s32*, 0) = 1;
            }
            break;
    }
    return ret;
}

extern Color_RGBA8 D_8900A6E8;
extern Color_RGBA8 D_80073520;
void func_8002A354(s32, s32, s32, s32, Color_RGBA8);
void func_80029A64(s32, s32, s32, s32, Color_RGBA8);
void func_80027F20(s32);
void func_89003D40(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 temp_v0 = *arg5;

    if (arg4 & 8) {
        func_8002A354(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x1A, D_8900A6E8);
    } else if (arg4 & 2) {
        func_80029A64(arg0 + 2, arg1 + 2, temp_v0 - 4, 0x1C, D_80073520);
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

M2C_UNK func_80027804();
void func_89003E2C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, char *arg5, s32 arg6, char *arg7, s32 arg8, char *arg9) {

    func_8002A8C4(((s8 *)arg0), arg1, arg2, arg3, arg4);
    M2C_FIELD(((s8 *)arg0), s32 *, 0x28) = 0;
    M2C_FIELD(((s8 *)arg0), s32 *, 0x24) = 0;
    M2C_FIELD(((s8 *)arg0), s32 *, 0x14) = 0x801;
    M2C_FIELD(((s8 *)arg0), char **, 0x20) = arg9;
    func_80027804(((s8 *)arg0) + 0x50, arg5, arg6, arg6);
    func_8002D880(((s8 *)arg0) + 0x2C, (s32)(((s8 *)arg0) + 0x50), (s32)(((s8 *)arg0) + 0x5C), (s32)func_89003D40, arg3 - 0xC, 0x20);
    M2C_FIELD(((s8 *)arg0), char **, 0x7C) = arg7;
    M2C_FIELD(((s8 *)arg0), s32 *, 0x80) = arg8;
}

extern Color_RGBA8 D_8900A6FC;
extern Color_RGBA8 D_8900A700;
void func_89003ECC(s8* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 sp38;
    s32 h;

    if (func_8002AE6C() == 0) {
        h = (M2C_FIELD(M2C_FIELD(arg0, s8**, 0x2C), s32*, 8) << 5) + 8;
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + h + 5, M2C_FIELD(arg0, s32*, 8), D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) - 0xC, h, *(Color_RGBA8*)&D_8900A5BC);
        func_8002A550(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + h + 0xC, M2C_FIELD(arg0, s32*, 8) - 0xC, M2C_FIELD(arg0, s32*, 0x80) * 0x1C, D_8900A6FC, D_8900A700);
        sp38 = M2C_FIELD(arg0, s32*, 8) - 0xC;
        func_8002D9B8(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0xA, 0xFFEF, (s32)&sp38);
        Font_BeginTranslucentTextRendering();
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8 *, 0), M2C_FIELD(&D_800734A8, u8 *, 1), M2C_FIELD(&D_800734A8, u8 *, 2), M2C_FIELD(&D_800734A8, u8 *, 3));
        Font_SetActive(8, 0);
        func_8001AB2C(0x1C);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + h + 0x10, (*(char***)(arg0 + 0x7C))[M2C_FIELD(arg0, s32*, 0x34)]);
        Font_EndTexturedTextRendering();
    }
}

s32 func_8900408C(s8* arg0) {
    s32 ret = 0;
    s32 temp_v0;

    switch (M2C_FIELD(arg0, s32*, 0x28)) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (func_8002DC04(arg0 + 0x2C) == 0) {
        temp_v0 = func_8002BC14(D_800603C0);
        if (temp_v0 == -1) {
            ret = -1;
        } else if (temp_v0 == 1) {
            ret = M2C_FIELD(arg0, s32*, 0x34) + 1;
        }
    }
    return ret;
}

extern char D_8900A704[];
extern char D_8900A710[];
extern char D_890188F4[];
void func_89003E2C(s32, s32, s32, s32, s32, char*, s32, char*, s32, char*);

/**
 * Calls func_89003E2C with its own first argument passed straight through
 * followed by 0x30, 0x5C, 0x170, 0xCE, D_8900A704, 3, D_8900A710, 3 and
 * D_890188F4. What func_89003E2C does (it is still assembly) and what the
 * arguments mean are not established.
 */
void func_89004120(s32 arg0) {
    func_89003E2C(arg0, 0x30, 0x5C, 0x170, 0xCE, D_8900A704, 3, D_8900A710, 3, D_890188F4);
}

M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
void func_89003ECC(s8*);
extern M2C_UNK D_89018900;
extern s32 D_89019108;
extern M2C_UNK D_89019110;

void func_89004184(s32 arg0) {
    M2C_UNK *var_a1;

    func_800069CC();
    if (D_89019108 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_89019110;
    }
    func_80028060(0, var_a1, &D_89018900, D_89019108);
    func_8900054C();
    func_89003ECC(arg0);
}

/**
 * Wrapper around func_8900408C(arg0): -1 calls func_8003F6AC(3) and returns -1;
 * a positive result calls func_8003F6AC(2) and returns the word at arg0 + 0x34
 * plus 1; any other result returns 0. (Same pattern as func_820076DC.)
 */
s32 func_890041E4(s8* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = func_8900408C(arg0);
    if (tmp == -1) {
        func_8003F6AC(3);
        result = -1;
    } else if (tmp > 0) {
        func_8003F6AC(2);
        result = M2C_FIELD(arg0, s32*, 0x34) + 1;
    }
    return result;
}

extern M2C_UNK D_89019110;
extern M2C_UNK D_89028950;
extern s32 D_890289D4;
s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);

/**
 * Stores the result of func_80025BD8() in D_89019108. If it is not -1, passes it with
 * &D_89019110 to func_80027FF8. Then calls func_89004120(&D_89028950) and sets
 * D_890289D4 to 1. (The value is re-read from D_89019108 after the store, which is
 * what the retail register allocation needs.) What the value means is not established.
 */
void func_89004244(void) {
    D_89019108 = func_80025BD8();
    if (D_89019108 != -1) {
        func_80027FF8(&D_89019110, D_89019108);
    }
    func_89004120(&D_89028950);
    D_890289D4 = 1;
}

typedef struct Col8900429C { u8 r, g, b, a; } Col8900429C;
extern s32 D_8900A71C;
extern s32 D_8900A720;
/*
 * Second name for D_8900A71C. The fade-out store in this function family
 * (also func_8200579C, func_8900429C, func_891049E8, func_8A101B30) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_8900A71C_2;
extern M2C_UNK D_8901890C;
M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(Col8900429C*, Col8900429C, f32);
s32 func_8900429C(s32 arg0) {
    Col8900429C sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_8900A71C;
    if (n >= 8) {
        D_8900A720 = 1;
    }
    if (D_8900A720 != 0) {
        n--;
        D_8900A71C_2 = n;
    }
    func_800069CC();
    if (D_89019108 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_89019110;
    }
    func_80028060(0, var_a1, &D_8901890C, D_89019108);
    n = D_8900A71C;
    func_8002C8D8(&sp2C, *(Col8900429C*)&D_8900A5B8, n / (f64)8.0f);
    func_8002C064(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_8900A720 == 0) {
        n = D_8900A71C;
        n++;
        D_8900A71C = n;
    }
    return 0;
}

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
void func_89003650(s8*);
void func_8900379C(void*);
M2C_UNK func_890067B0(M2C_UNK *, M2C_UNK *);        /* extern */
M2C_UNK func_890069C0(M2C_UNK *);                   /* extern */
M2C_UNK func_890069E8(M2C_UNK *);                   /* extern */
s32 func_89006D60(M2C_UNK *);                       /* extern */
M2C_UNK func_8900A014(M2C_UNK *);                   /* extern */
M2C_UNK func_8900A1A4(M2C_UNK *);                   /* extern */
M2C_UNK func_8900A1CC(M2C_UNK *);                   /* extern */
s32 func_8900A324(M2C_UNK *);                       /* extern */
extern M2C_UNK D_89018918;
extern M2C_UNK D_89019128;
extern M2C_UNK D_89019B98;
extern M2C_UNK D_89021428;
extern M2C_UNK D_89028950;
extern s32 D_890289D4;

s32 func_890043BC(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    sp1C = 0;
    func_8000B1FC();
    func_8000B220();
    switch (D_890289D4) {                           /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        func_89004184(&D_89028950);
        temp_v0 = func_890041E4(&D_89028950);
        if (temp_v0 == -1) {
            sp1C = 1;
        } else if (temp_v0 > 0) {
            D_890289D4 = temp_v0 + 1;
            switch (D_890289D4) {                   /* switch 2; irregular */
            case 2:                                 /* switch 2 */
                func_890067B0(&D_89019B98, &D_89018918);
                break;
            case 3:                                 /* switch 2 */
                func_89003650((s8*)&D_89019128);
                break;
            case 4:                                 /* switch 2 */
                func_8900A014(&D_89021428);
                break;
            }
        }
        break;
    case 3:                                         /* switch 1 */
        func_8900379C(&D_89019128);
        if (func_89003A88(&D_89019128) != 0) {
            D_890289D4 = 1;
        }
        break;
    case 2:                                         /* switch 1 */
        func_890069E8(&D_89019B98);
        if (func_89006D60(&D_89019B98) != 0) {
            D_890289D4 = 1;
            func_890069C0(&D_89019B98);
        }
        break;
    case 4:                                         /* switch 1 */
        func_8900A1CC(&D_89021428);
        if (func_8900A324(&D_89021428) != 0) {
            D_890289D4 = 1;
            func_8900A1A4(&D_89021428);
        }
        break;
    }
    return sp1C;
}

extern FontContext* D_86A06200;
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_04000000[];
extern u8 D_00400F70[];
extern u8 D_004076E0[];
extern u8 D_88000000[];
extern u8 D_00235D70[];
extern u8 D_00238BD0[];
void func_89004244(void);
s32 func_8900429C(s32);

/*
 * func_89004560
 *
 * Fragment entry point.  It follows the same template as the Pokedex entry
 * function func_8A101ED4, and neither argument is used.  The steps are:
 *
 *   1. main_pool_push_state('TERM') saves the main pool state under that tag;
 *      the matching main_pool_pop_state('TERM') is near the end.
 *   2. func_8001A194(0x3C, 0) is called (Font_Init in symbol_addrs.txt).
 *   3. Two assets are loaded with Asset_LoadToSegment: the ROM range
 *      D_002E0BE0..D_002E2B90 into segment 1 and D_00400F70..D_004076E0 into
 *      segment 4.  The segment number is bits 24-27 of the address of
 *      D_01000000 / D_04000000.
 *   4. func_89004244() and StageLoader_UpdateSegments() are called.
 *   5. BgStage_RunUntilCondition is run three times, with timer values 8, 0
 *      and 8: the first and third with callback func_8900429C, the second
 *      with func_890043BC.  What those callbacks do is not established
 *      (func_8900429C is still assembly).
 *   6. StageLoader_WaitForRetrace() and main_pool_pop_state('TERM').
 *   7. Fragment_QueueCall queues a call to the fragment whose id comes from
 *      the address D_88000000 (bits 20-27, minus 0x10), with the ROM range
 *      D_00235D70..D_00238BD0.
 *
 * Returns 0x8040.
 */
s32 func_89004560(s32 arg0, s32 arg1) {
    main_pool_push_state('TERM');
    func_8001A194(0x3C, 0);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);
    func_89004244();
    StageLoader_UpdateSegments();
    BgStage_RunUntilCondition(8, func_8900429C);
    BgStage_RunUntilCondition(0, func_890043BC);
    BgStage_RunUntilCondition(8, func_8900429C);
    StageLoader_WaitForRetrace();
    main_pool_pop_state('TERM');
    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
