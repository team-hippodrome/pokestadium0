/* Stadium Zero fragment015_238BD0. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc/lab_pc_1B4EA0.c, src/fragments/lab_pc_list/lab_pc_list_1CEA00.c. */

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
typedef struct unk_D_88317298 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_88317298;
typedef struct unk_D_883172F4 {
    /* 0x00 */ u16* unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_883172F4;

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
typedef struct unk_D_88218060 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Color_RGBA8* unk_04;
} unk_D_88218060;
typedef struct unk_D_88218070 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ Color_RGBA8* unk_10;
} unk_D_88218070;

#include "fragments/particle_math/particle_math.h"
#include "m2c_macros.h"
void func_8002ED18(s8*, s32, s8*);

void func_8900020C(void);
s32 LabItem_ComputeRemainingCapacity(s32 arg0, unk_func_8820BE14_06C* arg1);
s32 LabItem_ComputeMaxTransferQuantity(s32 arg0, unk_func_8820BE14_06C* arg1);
s32 LabItem_FindOrAllocateGamePakBoxSlot(unk_func_8821421C_07C* arg0, s32 arg1, char* arg2);
void LabItem_LoadGamePakBoxSlots(unk_func_8821421C_07C* arg0);
void LabItem_ReadDeckEntries(s32 arg0, s32 arg1, s32 arg2, unk_func_8820BE14_06C* arg3);

void func_89000020(unk_func_8830867C_02C_0CC* arg0, s32 (*arg1)(s32, s32)) {
    func_800274E0(arg0->unk_00, arg1, arg0->unk_08);
}

typedef struct LabItemGrid {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ char unk04[0x8];
    /* 0x0C */ s32 unk_0C;
} LabItemGrid;

typedef struct LabItemCursor {
    /* 0x00 */ LabItemGrid* unk_00;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 unk_08;
} LabItemCursor;

void func_800275E4(s32, s32);
void func_80030744(s32*, s32);

/*
 * func_89000048
 *
 * Removes one row from the grid referenced by the cursor arg0 and fixes up
 * the cursor.  arg0->unk_00 is the grid and arg0->unk_08 the current index.
 *
 *   1. func_800275E4(grid, index) is called.  This is ByteMatrix_RemoveRow
 *      (name from symbol_addrs.txt; its code was read and agrees): it
 *      removes row `index` from a byte matrix whose row count is the word at
 *      offset 8 and whose row size is the word at offset 0xC, decrements
 *      the count, and returns 1 if the index was out of range.  The return
 *      value is not used here.
 *   2. If the index is now at or past the (already decremented) count, i.e.
 *      the removed row was the last one, it is decremented.
 *   3. func_80030744(arg0, index) is called
 *      (WidgetTree_SetScrollableGridIndexPreserveScroll in symbol_addrs.txt).
 *
 * symbol_addrs.txt names this function WidgetTree_RemoveScrollableGridEntry,
 * a Stadium 1 name.  The Stadium 1 function of that name is NOT the same
 * code: it removes from a pointer list and, when the index is past the end
 * and positive, sets the index to count - 1.  Zero's version operates on a
 * byte matrix and the retail code simply subtracts 1 from the index, so the
 * name is a rough match at best.
 */
void func_89000048(LabItemCursor* arg0) {
    func_800275E4((s32)arg0->unk_00, arg0->unk_08);
    if (arg0->unk_08 >= M2C_FIELD(arg0->unk_00, s32*, 8)) {
        arg0->unk_08 -= 1;
    }
    func_80030744((s32*)arg0, arg0->unk_08);
}

void func_800275E4(s32, s32);
int func_800274E0();
void func_80030744(s32*, s32);

void func_890000A4(s32* arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 var_s3;
    s32 var_v0;
    s32* temp_s4;
    u8 sp3C[2];
    u8* var_s2;
    u8* temp_v1;

    temp_s4 = (s32*)arg0[0];
    temp_v1 = (u8*)temp_s4[0];
    i = 0;

    if (temp_s4[2] > 0) {
        var_s2 = temp_v1;
        do {
            if (arg1 == var_s2[0]) {
                arg2 += var_s2[1];
                func_800275E4(arg0[0], i);
                if (i < arg0[2]) {
                    arg0[2]--;
                }
            } else {
                i++;
                var_s2 += 2;
            }
        } while (i < temp_s4[2]);
    }

    sp3C[0] = arg1;
    var_s3 = arg0[2];

    while (arg2 > 0) {
        if (arg2 < 0x63) {
            var_v0 = arg2;
        } else {
            var_v0 = 0x63;
        }
        arg2 -= var_v0;
        sp3C[1] = var_v0;
        func_800274E0(temp_s4, sp3C, var_s3++);
    }

    func_80030744(arg0, arg0[2]);
}

void func_890001B4(LabItemCursor* arg0, s32 arg1) {
    u8* temp_v1 = &arg0->unk_00->unk_00[arg0->unk_00->unk_0C * arg0->unk_08];

    if (arg1 >= temp_v1[1]) {
        func_89000048(arg0);
        return;
    }
    temp_v1[1] -= arg1;
}

void func_8900020C(void) {
}

s32 LabItem_ComputeRemainingCapacity(s32 arg0, unk_func_8820BE14_06C* arg1) {
    s32 i;
    s32 var_v1 = 0;
    u8* var_v0 = arg1->unk_00;

    for (i = 0; i < arg1->unk_08; i++, var_v0 += 2) {
        if (arg0 == var_v0[0]) {
            var_v1 = (var_v1 - var_v0[1]) + 0x63;
        }
    }

    return var_v1;
}

s32 LabItem_ComputeMaxTransferQuantity(s32 arg0, unk_func_8820BE14_06C* arg1) {
    s32 var_v1;

    if (LabItem_IsQuantitylessItemForOperation(arg0) != 0) {
        if (arg1->unk_08 < arg1->unk_04) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
    } else if (arg1->unk_08 < arg1->unk_04) {
        var_v1 = 0x63;
    } else {
        var_v1 = LabItem_ComputeRemainingCapacity(arg0, arg1);
    }
    return var_v1;
}

s32 LabItem_FindOrAllocateGamePakBoxSlot(unk_func_8821421C_07C* arg0, s32 arg1, char* arg2) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((arg0[i].unk_00 != 0) && (arg1 == arg0[i].unk_04) && (HAL_Strcmp(arg0[i].unk_08, arg2) == 0)) {
            return i;
        }
    }

    for (i = 0; i < 4; i++) {
        if (arg0[i].unk_00 == 0) {
            return i;
        }
    }

    return -1;
}

void LabItem_LoadGamePakBoxSlots(unk_func_8821421C_07C* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        arg0[i].unk_00 = Deck_IsSaveEntryPresent(0x12, i);
        if (arg0[i].unk_00 != 0) {
            arg0[i].unk_04 = Deck_GetSaveEntryTrainerId(0x12, i) & 0xFFFF;
            Deck_GetSaveEntryName(0x12, i, arg0[i].unk_08);
        }
    }
}

void LabItem_ReadDeckEntries(s32 arg0, s32 arg1, s32 arg2, unk_func_8820BE14_06C* arg3) {
    DeckHandle* sp1C = Deck_Open(arg0, arg1, arg2, 0);

    arg3->unk_08 = Deck_ReadEntries(arg3->unk_00, arg3->unk_04, sp1C);
    Deck_CloseAndFlush(sp1C);
}

void LabItem_WriteDeckBack(s32 arg0, s32 arg1, s32 arg2, unk_func_8820BE14_06C* arg3, s32 arg4, char* arg5, s32 arg6) {
    DeckHandle* sp2C;

    if (arg6 != -1) {
        if (1) {}  // karodo
        sp2C = Deck_OpenAndSetName(arg0, arg1, arg2, arg4, arg5, arg6);
    } else {
        sp2C = Deck_Open(arg0, arg1, arg2, 1);
    }

    Deck_WriteEntries(arg3->unk_00, arg3->unk_08, sp2C);

    if ((arg0 == 0x10) || (arg0 == 0x11) || (arg0 == 0x12) || (arg0 == 0x13)) {
        Deck_CloseAndFlushBox(sp2C);
    } else {
        Deck_CloseAndFlush(sp2C);
    }
}

M2C_UNK func_8002C064(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_8900A5B8;

void func_8900054C(void) {
    func_8002C064(0x38, 0x1E0, M2C_FIELD(&D_8900A5B8, u8 *, 0), M2C_FIELD(&D_8900A5B8, u8 *, 1), (s32) M2C_FIELD(&D_8900A5B8, u8 *, 2));
}

void func_8002A8C4(s8*, s32, s32, s32, s32);
void func_8002AE94(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);
extern Color_RGBA8 D_8900A5C0;
extern char D_89018460[];
extern char D_89018468[];
extern s32 D_800603C0;
void func_89000588(s8* arg0, s32 arg1, s32 arg2, char *arg3, s32 arg4) {
    func_8002A8C4(arg0, arg1, arg2, 0x10C, 0x92);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x2801;
    M2C_FIELD(arg0, char**, 0x20) = arg3;
    func_8002AE94(arg0 + 0x34, M2C_FIELD(arg0, s32*, 0) + 0x2E, M2C_FIELD(arg0, s32*, 4) + 0x6E, 0x48, D_8900A5C0, D_89018460);
    M2C_FIELD(arg0, s32*, 0x60) = 0xA;
    M2C_FIELD(arg0, s32*, 0x68) = 0xC;
    func_8002AE94(arg0 + 0x70, M2C_FIELD(arg0, s32*, 0) + 0x96, M2C_FIELD(arg0, s32*, 4) + 0x6E, 0x48, D_8900A5C0, D_89018468);
    M2C_FIELD(arg0, s32*, 0xB4) = 2;
    M2C_FIELD(arg0, s32*, 0xB0) = 0;
    M2C_FIELD(arg0, s32*, 0xAC) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32*, 0x30) = arg4;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AB2C(M2C_UNK);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
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

void func_89000694(s8* arg0) {
    if (func_8002AE6C() == 0) {
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0x61, M2C_FIELD(arg0, s32*, 8), D_8007356C);
        func_8002A550(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x5C, D_8900A5C4, D_8900A5C8);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0x68, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x24, D_8900A5CC);
        func_8001AB6C();
        if (!arg0) { // FAKE: empty test only changes register allocation; needed to match
        }
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8 *, 0), M2C_FIELD(&D_800734A8, u8 *, 1), M2C_FIELD(&D_800734A8, u8 *, 2), M2C_FIELD(&D_800734A8, u8 *, 3));
        func_8001A384(8, 0);
        func_8001AB2C(0x1C);
        func_8001A944(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0xA, M2C_FIELD(arg0, s32*, 0x30));
        func_8001ABBC();
        func_8002AF04(arg0 + 0x34, (M2C_FIELD(arg0, s32*, 0xB0) == 0) ? 2 : 0);
        func_8002AF04(arg0 + 0x70, (M2C_FIELD(arg0, s32*, 0xB0) == 1) ? 2 : 0);
    }
}

s32 func_8002B390(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;

s32 func_89000828(s8* arg0) {
    s32 ret = 0;

    switch (M2C_FIELD(arg0, s32*, 0x28)) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (func_8002B390(arg0 + 0xAC) == 0) {
        ret = func_8002BC14(D_800603C0);
        if (ret == 1) {
            switch (M2C_FIELD(arg0, s32*, 0xB0)) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    ret = -1;
                    break;
            }
        }
    }
    return ret;
}

typedef struct Rgba89000D50 {
    /* 0x0 */ u8 r, g, b, a;
} Rgba89000D50; // size = 0x4
extern Rgba89000D50 D_8900A5BC;

void func_890008C8(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8002A8C4(arg0 + 4, arg1, arg2, 0x54, 0x34);
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = 0;
    M2C_FIELD(arg0, s32*, 0x18) = 0;
    M2C_FIELD(arg0, Rgba89000D50*, 0x1C) = D_8900A5BC;
    M2C_FIELD(arg0, s32*, 0x40) = 2;
    M2C_FIELD(arg0, s32*, 0x34) = 1;
    M2C_FIELD(arg0, s32*, 0x38) = 1;
    M2C_FIELD(arg0, s32*, 0x3C) = arg3;
    M2C_FIELD(arg0, s32*, 0x44) = 0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32*, 0x30) = arg4;
    M2C_FIELD(arg0, s32*, 0) = 0;
}

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

void func_89000960(s8* arg0) {
    UNUSED s32 pad[1];
    s32 x;
    s32 v;

    if (func_8002AE6C(arg0 + 4) == 0) {
        x = M2C_FIELD(arg0, s32*, 4) - M2C_FIELD(arg0, s32*, 0x44) * 0x16 + 0x36;
        gSPDisplayList(gDisplayListHead++, D_80073408);
        if (((u16*)D_800603C0)[3] & 0x800) {
            v = (s32)D_04002340;
        } else {
            v = (s32)D_04002130;
        }
        func_8001B884(x + 3, M2C_FIELD(arg0, s32*, 8) + 6, 0xE, 8, (u8*)v, 0x10, 0x200000);
        if (((u16*)D_800603C0)[3] & 0x400) {
            v = (s32)D_04002448;
        } else {
            v = (s32)D_04002238;
        }
        func_8001B884(x + 3, M2C_FIELD(arg0, s32*, 8) + 0x26, 0xE, 8, (u8*)v, 0x10, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
        func_80029A64(x - 3, M2C_FIELD(arg0, s32*, 8) + 0xD, 0x1A, 0x1A, D_80073520);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(8, 0);
        Gfx_SetEnvColor(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2),
                      M2C_FIELD(&D_800734A8, u8*, 3));
        func_8001A944(M2C_FIELD(arg0, s32*, 4) + 0xA, M2C_FIELD(arg0, s32*, 8) + 0x10, D_89018470);
        if (M2C_FIELD(arg0, s32*, 0x44) == 1) {
            v = 2;
        } else {
            v = 0;
        }
        func_80027F20(v);
        func_8001AA60(M2C_FIELD(arg0, s32*, 4) + 0x20, M2C_FIELD(arg0, s32*, 8) + 0x10, M2C_FIELD(arg0, s32*, 0x34) / 10 + '0');
        if (M2C_FIELD(arg0, s32*, 0x44) == 0) {
            v = 2;
        } else {
            v = 0;
        }
        func_80027F20(v);
        func_8001AA60(M2C_FIELD(arg0, s32*, 4) + 0x36, M2C_FIELD(arg0, s32*, 8) + 0x10, M2C_FIELD(arg0, s32*, 0x34) % 10 + '0');
        Font_EndTexturedTextRendering();
        if (M2C_FIELD(arg0, s32*, 0) == 1) {
            func_8002D024(arg0 + 0x48);
        }
    }
}

s32 func_8002B638(s8 *);                          /* extern */
s32 func_8002BC14(s32);                             /* extern */
M2C_UNK func_8002CEEC(s8 *, M2C_UNK *, M2C_UNK, M2C_UNK, s32); /* extern */
s32 func_8002D138(s8 *);                          /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */
extern s32 D_800603C0;
extern M2C_UNK D_89018474;

s32 func_89000BEC(s8 *arg0) {
    s32 sp2C;
    s32 temp_v0;
    s32 temp_v0_2;

    sp2C = 0;
    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    switch (temp_v0) {                              /* irregular */
    case 0:
        if (func_8002B638(arg0 + 0x34) == 0) {
            temp_v0_2 = func_8002BC14(D_800603C0);
            if (temp_v0_2 == -1) {
                func_8003F6AC(3);
                sp2C = -1;
            } else if (temp_v0_2 == 1) {
                if (M2C_FIELD(arg0, s32 *, 0x30) < M2C_FIELD(arg0, s32 *, 0x34)) {
                    func_8003F6AC(8);
                    func_8002CEEC(arg0 + 0x48, &D_89018474, 0, 1, 0);
                    M2C_FIELD(arg0, s32 *, 0) = 1;
                } else {
                    func_8003F6AC(2);
                    sp2C = 1;
                }
            }
        }
        break;
    case 1:
        if (func_8002D138(arg0 + 0x48) == 1) {
            M2C_FIELD(arg0, s32 *, 0) = 0;
            M2C_FIELD(arg0, s32 *, 0x34) = (s32) M2C_FIELD(arg0, s32 *, 0x30);
        }
        break;
    }
    return sp2C;
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_89000CF0(s8 *arg0, s8 *arg1)
{
  s32 var_v0;
  u16 *temp_a1;
  s8 *var_v1;
  s8 *new_var;
  var_v0 = 0;
  new_var = ((s8 *) arg0) + 0x30;
  var_v1 = arg1;
  do
  {
    if ((*((s32 *) (((s8 *) var_v1) + 8))) == 0)
    {
      temp_a1 = (*((s32 *) new_var)) + (var_v0 * 2);
      *temp_a1 |= 0x100;
    }
    var_v0 += 1;
    var_v1 += 0x10;
  }
  while (var_v0 != 3);
}

void func_89000D34(s8 *arg0, s32 arg1) {
    u16 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x30) + (arg1 * 2);
    *temp_v0 |= 1;
}

/*
 * func_89000D50: draws one line of text `str` at (x, y) in the Lab PC list style.
 *
 * `flags` bit 0x10 first draws a 0xD2 x 0x16 highlight (func_8002A0AC, colour
 * D_8900A5BC) at (x + 3, y + 3).  The text colour is then picked:
 *   - flags & 1: D_800734A8[1] with alpha forced to 0x4C;
 *   - else flags & 0x100: D_8900A5D4[(flags & 2) ? 0 : 1];
 *   - otherwise: D_800734A8[(flags & 2) ? 0 : 1];
 * and the string is printed at (x + 8, y + 4) with font set 8 in translucent text
 * mode.  `index` is unused.  (A shorter sibling of func_89004908, which has two more
 * colour tables.)
 */
void func_8002A0AC(s32, s32, s32, s32, Rgba89000D50);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
extern Rgba89000D50 D_8900A5D4[];
extern M2C_UNK D_800734A8;
void func_89000D50(s32 x, s32 y, char* str, UNUSED s32 index, s32 flags) {
    Rgba89000D50 color;
    UNUSED s32 pad[4];

    if (flags & 0x10) {
        func_8002A0AC(x + 3, y + 3, 0xD2, 0x16, D_8900A5BC);
    }
    Font_BeginTranslucentTextRendering();
    if (flags & 1) {
        color = ((Rgba89000D50*)&D_800734A8)[1];
        color.a = 0x4C;
    } else if (flags & 0x100) {
        color = D_8900A5D4[(flags & 2) ? 0 : 1];
    } else {
        color = ((Rgba89000D50*)&D_800734A8)[(flags & 2) ? 0 : 1];
    }
    func_8001AA9C(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(x + 8, y + 4, str);
    Font_EndTexturedTextRendering();
}

void func_8002A8C4(s8*, s32, s32, s32, s32);
void func_8002D880(s8*, s32, s32, s32, s32, s32);
M2C_UNK func_80027804();
void func_89000E98(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad[2];

    func_8002A8C4((s8 *)arg0, arg1, arg2, 0xE4, (arg4 * 0x1C) + 0x14);
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, Rgba89000D50 *, 0x18) = D_8900A5BC;
    func_80027804((s8 *)arg0 + 0x50, arg3, arg4, arg4);
    func_8002D880((s8 *)arg0 + 0x2C, (s32)((s8 *)arg0 + 0x50), (s32)((s8 *)arg0 + 0x5C), (s32)func_89000D50, 0xD8, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x34) = arg5;
    M2C_FIELD(arg0, s32 *, 0x4C) |= 0x10000;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK func_8002D9B8(s8 *, s32, s32, M2C_UNK, s32); /* extern */

void func_89000F5C(s8 *arg0) {
    if (func_8002AE6C() == 0) {
        func_8002D9B8(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0xA, 0xFFEF, 0);
    }
}

s32 func_8002DCE0(void*);
s32 func_89000FA4(s32 arg0) {
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
extern Rgba89000D50 D_8900A5E0;
extern Rgba89000D50 D_8900A5E8;
extern Rgba89000D50 D_8900A5EC[];
extern char D_8901848C[];
char* func_8001FDC8(u8, char*);
s32 func_80031C24(u8);
s32 func_80031CC8(u8);
void func_80027F20(s32);
void func_89001018(s32 arg0, s32 arg1, u8* arg2, s32 arg3, s32 arg4) {
    char buf[0x30];

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xEC, 0x1A, *(Color_RGBA8*)&D_8900A5E0);
    func_80029028(arg0, arg1, 0xEC, 1, *(Color_RGBA8*)&D_8900A5E8);
    func_80029028(arg0, arg1 + 0x1B, 0xEC, 1, *(Color_RGBA8*)&D_8900A5E8);
    if (arg4 & 0x18) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0xE6, 0x16, D_8900A5BC);
    }
    if (arg2 != NULL) {
        func_8001AB6C();
        func_8001A384(8, 0);
        if (func_80031C24(arg2[0]) != 0) {
            Rgba89000D50 color;

            color = D_8900A5EC[(arg4 & 2) ? 0 : 1];
            func_8001AA9C(color.r, color.g, color.b, color.a);
        } else {
            func_80027F20(arg4);
        }
        func_8001A944(arg0 + 8, arg1 + 4, func_8001FDC8(arg2[0], buf));
        if (func_80031CC8(arg2[0]) == 0) {
            func_8001A384(4, 0);
            func_8001A944(arg0 + 0xB4, arg1 + 8, D_8901848C, arg2[1]);
        }
        func_8001ABBC();
    }
}

void func_89001230(s8* arg0, s32 arg1) {
    func_8002ED18(arg0, arg1, arg0 + 0x44);
}

void func_8002EC24(s8*, s32, s8*, s32, void*, s32, s32);
void func_89001018();

void func_89001250(s8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32*, 0x10C) = arg1;
    M2C_FIELD(arg0, s32*, 0x110) = arg2;
    func_8002EC24(arg0, arg3, arg0 + 0x44, 8, func_89001018, 0xEC, 0x1C);
    M2C_FIELD(arg0, s32*, 0x20) |= 0x10000;
}

void func_8002F9D8(void *, s32, s32, s32, s32);
void func_8002F6C4(void *, s32, s32, s32, s32);
void func_8002BAB8(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void *, s32, s32);
extern Gfx D_80073450[];
extern u8 D_04011AB8[];
void func_890012C4(s8 *arg0, s32 arg1) {
    if (arg1 & 0x200) {
        func_8002F9D8(arg0, M2C_FIELD(arg0, s32 *, 0x10C), M2C_FIELD(arg0, s32 *, 0x110) + 0x10, arg1 | 0xFFED, 0);
    } else {
        func_8002F6C4(arg0, M2C_FIELD(arg0, s32 *, 0x10C), M2C_FIELD(arg0, s32 *, 0x110) + 0x10, arg1 | 0xFFED, 0);
    }
    func_8002BAB8(M2C_FIELD(arg0, s32 *, 0x10C) + 0xA8, M2C_FIELD(arg0, s32 *, 0x110) + 0xF2, M2C_FIELD(M2C_FIELD(arg0, s8 **, 0), s32 *, 8), 3);
    func_8002BAB8(M2C_FIELD(arg0, s32 *, 0x10C) + 0xCE, M2C_FIELD(arg0, s32 *, 0x110) + 0xF2, M2C_FIELD(M2C_FIELD(arg0, s8 **, 0), s32 *, 4), 3);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001BCB4(M2C_FIELD(arg0, s32 *, 0x10C) + 0xC4, M2C_FIELD(arg0, s32 *, 0x110) + 0xF4, 8, 0xA, D_04011AB8, 8, 0);
}

s32 func_8002FD8C(void*);
s32 func_80030230(void*);

/* Navigate the selected menu mode, then report cancel or confirm input. */
s32 func_890013F8(void* menu, u32 flags) {
    s32 result = 0;
    s32 moved;
    s32 action;

    if (flags & 0x200) {
        moved = func_80030230(menu);
    } else {
        moved = func_8002FD8C(menu);
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

void func_8002B018(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_80027410(s8*, s8*, s32, s32, s32);
s32 func_800564D4(char*, const char*, ...);
extern Rgba89000D50 D_8900A600;
extern Rgba89000D50 D_8900A604;
extern u8 D_8900A580[];
extern u8 D_8900BFC0[];
extern u8 D_8900DAD0[];
extern u8 D_8900E858[];
extern u8 D_8900F5E0[];
extern char D_890184BC[];
extern char D_890190F0[];
extern char D_890184CC[];
extern s32 D_8901911C;
extern u8 D_8900A5F4[];
void func_8900147C(s8* arg0, s32 x, s32 y, s8* arg3, s32* arg4, s32* arg5) {
    func_8002A8C4(arg0 + 4, x, y, 0x234, 0x174);
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = 0;
    M2C_FIELD(arg0, s32*, 0x18) = 0x801;
    M2C_FIELD(arg0, char**, 0x24) = D_890184BC;
    func_8002A8C4(arg0 + 0x30, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 0x136, M2C_FIELD(arg0, s32*, 0xC) - 0xC, 0x38);
    M2C_FIELD(arg0, s32*, 0x44) = 6;
    M2C_FIELD(arg0, Rgba89000D50*, 0x48) = D_8900A600;
    M2C_FIELD(arg0, Rgba89000D50*, 0x4C) = D_8900A604;
    func_8002B018(arg0 + 0x50, x + 0xFF, y + 0x3A, 0x36, 0x2A, 0x30, (s32)D_8900BFC0);
    M2C_FIELD(arg0, Rgba89000D50*, 0x68) = ((Rgba89000D50*)D_8900A580)[0];
    M2C_FIELD(arg0, Rgba89000D50*, 0x6C) = ((Rgba89000D50*)D_8900A580)[1];
    M2C_FIELD(arg0, Rgba89000D50*, 0x70) = D_8900A5BC;
    func_8002B018(arg0 + 0x7C, x + 0xFF, y + 0x74, 0x36, 0x2A, 0x30, (s32)D_8900DAD0);
    M2C_FIELD(arg0, Rgba89000D50*, 0x94) = ((Rgba89000D50*)D_8900A580)[2];
    M2C_FIELD(arg0, Rgba89000D50*, 0x98) = ((Rgba89000D50*)D_8900A580)[3];
    M2C_FIELD(arg0, Rgba89000D50*, 0x9C) = D_8900A5BC;
    func_8002B018(arg0 + 0xA8, x + 0xFF, y + 0xAE, 0x36, 0x2A, 0x30, (s32)D_8900E858);
    M2C_FIELD(arg0, Rgba89000D50*, 0xC0) = ((Rgba89000D50*)D_8900A580)[4];
    M2C_FIELD(arg0, Rgba89000D50*, 0xC4) = ((Rgba89000D50*)D_8900A580)[5];
    M2C_FIELD(arg0, Rgba89000D50*, 0xC8) = D_8900A5BC;
    func_8002B018(arg0 + 0xD4, x + 0xFF, y + 0xE8, 0x36, 0x2A, 0x30, (s32)D_8900F5E0);
    M2C_FIELD(arg0, Rgba89000D50*, 0xEC) = ((Rgba89000D50*)D_8900A580)[6];
    M2C_FIELD(arg0, Rgba89000D50*, 0xF0) = ((Rgba89000D50*)D_8900A580)[7];
    M2C_FIELD(arg0, Rgba89000D50*, 0xF4) = D_8900A5BC;
    M2C_FIELD(arg0, s32*, 0x1D8) = 1;
    M2C_FIELD(arg0, s32*, 0x1D4) = 0;
    func_800564D4(D_890190F0, D_890184CC, &D_8901911C);
    M2C_FIELD(arg0, u8**, 0x1DC) = D_8900A5F4;
    M2C_FIELD(arg0, s32*, 0x1E0) = 3;
    M2C_FIELD(arg0, s32*, 0x108) = 4;
    M2C_FIELD(arg0, s32*, 0x104) = 0;
    M2C_FIELD(arg0, s32*, 0x100) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32*, 0) = 1;
    M2C_FIELD(arg0, s8**, 0x490) = arg3;
    M2C_FIELD(arg0, s32**, 0x494) = arg4;
    M2C_FIELD(arg0, s32**, 0x498) = arg5;
    func_89001250(arg0 + 0x1E4, M2C_FIELD(arg0, s32*, 4) + 0xC, M2C_FIELD(arg0, s32*, 8) + 0x2A, (s32)(arg3 + M2C_FIELD(arg0, s32*, 0x1D4) * 0x10));
    func_89001250(arg0 + 0x2F8, M2C_FIELD(arg0, s32*, 4) + 0x13C, M2C_FIELD(arg0, s32*, 8) + 0x2A, (s32)(arg3 + M2C_FIELD(arg0, s32*, 0x1D8) * 0x10));
    func_80027410(arg0 + 0x49C, M2C_FIELD(M2C_FIELD(arg0, s8**, 0x490), s8**, 0), 2, M2C_FIELD(M2C_FIELD(arg0, s8**, 0x490), s32*, 4), 0);
}

typedef struct ColorPair890017FC {
    /* 0x0 */ Color_RGBA8 prim;
    /* 0x4 */ Color_RGBA8 env;
} ColorPair890017FC;

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

void func_890017FC(s8* arg0, s32 x, s32 y, s32 flags, s32 icon) {
    ColorPair890017FC* colors;

    if (flags & 2) {
        colors = &D_8900A608;
    } else {
        colors = &D_8900A610;
    }
    func_8002A550(x, y, 0xEC, 0x1E, colors->prim, colors->env);
    if (icon != -1) {
        gSPDisplayList(gDisplayListHead++, D_80073408);
        switch (icon) {
            case 0:
            case 1:
                Gfx_DrawTextureRgba16(x + 5, y + 2, 0x18, 0x1A, D_89017A80[func_8002BC44(D_89019114)], 0x18, 0x200000);
                break;
            case 2:
                Gfx_DrawTextureRgba16(x + 5, y + 2, 0x2E, 0x1A, D_89017A98, 0x30, 0x200000);
                break;
        }
        gSPDisplayList(gDisplayListHead++, D_80073438);
        func_8001AB6C();
        func_80027F20(flags);
        func_8001A384(8, 0);
        func_8001A944(x + 0x21, y + 4, M2C_FIELD(arg0, s32**, 0x1DC)[icon]);
        func_8001ABBC();
    }
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AAE4(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
M2C_UNK func_8001ABE8();                            /* extern */
M2C_UNK func_8001AC3C();                            /* extern */
u32 func_800566BC(s32);                             /* extern */

void func_890019C8(s32 arg0, s32 arg1, s32 arg2, s8 *arg3) {
    func_8001AB6C();
    func_8001A384(0x20, 0);
    func_8001AA9C(M2C_FIELD(arg3, u8 *, 0), M2C_FIELD(arg3, u8 *, 1), M2C_FIELD(arg3, u8 *, 2), M2C_FIELD(arg3, u8 *, 3));
    func_8001ABE8();
    func_8001AAE4(M2C_FIELD(arg3, u8 *, 4), M2C_FIELD(arg3, u8 *, 5), M2C_FIELD(arg3, u8 *, 6), M2C_FIELD(arg3, u8 *, 7));
    func_8001A944(((u32) (0x178 - ((func_800566BC(arg2) >> 1) << 5)) >> 1) + arg0, arg1 + 0xC, arg2);
    func_8001AC3C();
    func_8001ABBC();
}

extern M2C_UNK D_800734A8;

void func_89001A7C(s32 arg0, s32 arg1, char* arg2) {
    Font_BeginTranslucentTextRendering();
    Font_SetActive(0x10, 0);
    Gfx_SetEnvColor(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
    Font_Printf(((0x178 - (strlen(arg2) / 2) * 0x18) / 2) + arg0, arg1 + 0x10, arg2);
    Font_EndTexturedTextRendering();
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AB2C(M2C_UNK);                     /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
extern M2C_UNK D_800734A8;

void func_89001B10(s32 arg0, s32 arg1, s32 arg2) {
    func_8001AB6C();
    func_8001A384(8, 0);
    func_8001AA9C(M2C_FIELD(&D_800734A8, u8 *, 0), M2C_FIELD(&D_800734A8, u8 *, 1), M2C_FIELD(&D_800734A8, u8 *, 2), M2C_FIELD(&D_800734A8, u8 *, 3));
    func_8001AB2C(0x1C);
    func_8001A944(arg0 + 8, arg1 + 4, arg2);
    func_8001ABBC();
}

typedef struct List89001B88 {
    /* 0x00 */ u8** data;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 index;
} List89001B88;
extern s32 D_8900A650[];
extern char* D_8900A660[];
extern char* D_8900A66C[];
extern s8* D_8900A678[];
s32 func_80031BC0(u8, char *);
void func_89001B88(s32* arg0) {
    char sp2C[0x54];
    List89001B88* list;

    switch (arg0[0]) {
        case 1:
            func_890019C8(arg0[0xC] + 0x58, arg0[0xD], D_8900A650[arg0[0x41]], D_8900A678[arg0[0x41]]);
            break;
        case 2:
            func_89001A7C(arg0[0xC] + 0x58, arg0[0xD], D_8900A660[arg0[0x41]]);
            break;
        case 3:
            func_89001A7C(arg0[0xC] + 0x58, arg0[0xD], D_8900A66C[arg0[0x41]]);
            break;
        case 4:
        case 6:
        case 7:
            if (arg0[0] == 6) {
                list = (List89001B88*)(arg0 + 0xBE);
            } else {
                list = (List89001B88*)(arg0 + 0x79);
            }
            func_89001B10(arg0[0xC] + 0x58, arg0[0xD], func_80031BC0((*list->data)[list->index * 2], sp2C));
            break;
    }
}

void func_800295E8(s32, s32, s32, s32, u8*);
extern u8 D_800735C4[];
void func_8002B054(s8*, s32);
void func_8002A8E0(void*);
void func_890017FC(s8* arg0, s32 x, s32 y, s32 flags, s32 icon);
void func_890012C4(s8* arg0, s32 arg1);
void func_89001CB0(s8 *arg0)
{
  s32 v;
  s32 flags;
  if (func_8002AE6C(arg0 + 4) == 0)
  {
    func_8002A8E0(arg0 + 0x30);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028((*((s32 *) (((s8 *) arg0) + 4))) + 6, (*((s32 *) (((s8 *) arg0) + 8))) + 6, (*((s32 *) (((s8 *) arg0) + 0xC))) - 0xC, 6, *((Color_RGBA8 *) (&D_8900A5BC)));
    func_80029028((*((s32 *) (((s8 *) arg0) + 4))) + 6, (*((s32 *) (((s8 *) arg0) + 8))) + 0x12A, (*((s32 *) (((s8 *) arg0) + 0xC))) - 0xC, 6, *((Color_RGBA8 *) (&D_8900A5BC)));
    func_80029028((*((s32 *) (((s8 *) arg0) + 4))) + 6, (*((s32 *) (((s8 *) arg0) + 8))) + 0xC, 6, 0x11E, *((Color_RGBA8 *) (&D_8900A5BC)));
    func_80029028(((*((s32 *) (((s8 *) arg0) + 0xC))) + (*((s32 *) (((s8 *) arg0) + 4)))) - 0xC, (*((s32 *) (((s8 *) arg0) + 8))) + 0xC, 6, 0x11E, *((Color_RGBA8 *) (&D_8900A5BC)));
    func_80029028((*((s32 *) (((s8 *) arg0) + 4))) + 0xF8, (*((s32 *) (((s8 *) arg0) + 8))) + 0xC, 0x44, 0x11E, *((Color_RGBA8 *) (&D_8900A5BC)));
    func_80029658(*((s32 *) (((s8 *) arg0) + 4)), (*((s32 *) (((s8 *) arg0) + 8))) + 0x12F, *((s32 *) (((s8 *) arg0) + 0xC)), D_8007356C);
    func_800295E8((*((s32 *) (((s8 *) arg0) + 4))) + 0xA, (*((s32 *) (((s8 *) arg0) + 8))) + 0xA, 0xF0, 0x122, D_800735C4);
    func_800295E8((*((s32 *) (((s8 *) arg0) + 4))) + 0x13A, (*((s32 *) (((s8 *) arg0) + 8))) + 0xA, 0xF0, 0x122, D_800735C4);
    v = ((*((s32 *) (((s8 *) arg0) + 0))) == 1) ? (2) : (0x10);
    func_8002B054(arg0 + 0x50, ((*((s32 *) (((s8 *) arg0) + 0x104))) == 3) ? (v) : (0));
    func_8002B054(arg0 + 0x7C, ((*((s32 *) (((s8 *) arg0) + 0x104))) == 0) ? (v) : (0));
    func_8002B054(arg0 + 0xA8, ((*((s32 *) (((s8 *) arg0) + 0x104))) == 1) ? (v) : (0));
 func_8002B054(arg0 + 0xD4, ((*((s32 *) (((s8 *) arg0) + 0x104))) == 2) ? (v) : (0)); func_890017FC(arg0, (*((s32 *) (((s8 *) arg0) + 4))) + 0xC, (*((s32 *) (((s8 *) arg0) + 8))) + 0xC, 0, *((s32 *) (((s8 *) arg0) + 0x1D4)));
    func_890017FC(arg0, (*((s32 *) (((s8 *) arg0) + 4))) + 0x13C, (*((s32 *) (((s8 *) arg0) + 8))) + 0xC, 0, *((s32 *) (((s8 *) arg0) + 0x1D8)));
    func_890012C4(arg0 + 0x1E4, (((*((s32 *) (((s8 *) arg0) + 0))) == 4) || ((*((s32 *) (((s8 *) arg0) + 0))) == 7)) ? (2) : ((((*((s32 *) (((s8 *) arg0) + 0))) == 5) || ((*((s32 *) (((s8 *) arg0) + 0))) == 6)) ? (0x10) : (0)));
    flags = ((((*((s32 *) (((s8 *) arg0) + 0))) == 5) || ((*((s32 *) (((s8 *) arg0) + 0))) == 6)) ? 2 : 0);
    flags |= (((*((s32 *) (((s8 *) arg0) + 0))) == 5) ? 0x200 : 0);
    func_890012C4(arg0 + 0x2F8, flags);
    if (((*((s32 *) (((s8 *) arg0) + 0))) == 2) || ((*((s32 *) (((s8 *) arg0) + 0))) == 9))
    {
      func_89000F5C(arg0 + 0x10C);
    }
    if (((*((s32 *) (((s8 *) arg0) + 0))) == 3) || ((*((s32 *) (((s8 *) arg0) + 0))) == 0xA))
    {
      func_89000F5C(arg0 + 0x170);
    }
    func_89001B88((s32 *) arg0);
    if (((((*((s32 *) (((s8 *) arg0) + 0))) == 9) || ((*((s32 *) (((s8 *) arg0) + 0))) == 0xA)) || ((*((s32 *) (((s8 *) arg0) + 0))) == 0xB)) || ((*((s32 *) (((s8 *) arg0) + 0))) == 0xC))
    {
      func_8002D024(arg0 + 0x4AC);
    }
    if ((*((s32 *) (((s8 *) arg0) + 0))) == 8)
    {
      func_89000960(arg0 + 0x410);
    }
  }
}

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

void func_890020C0(u8* arg0) {
    u8* item;

    item = CURSOR(arg0)->grid->data + CURSOR(arg0)->selected * 2;
    M2C_FIELD(arg0, s32**, 0x494)[M2C_FIELD(arg0, s32*, 0x1A4)] = 1;
    M2C_FIELD(arg0, s32**, 0x494)[M2C_FIELD(arg0, s32*, 0x140)] = M2C_FIELD(arg0, s32**, 0x494)[M2C_FIELD(arg0, s32*, 0x1A4)];
    if (LabItem_IsQuantitylessItemForOperation(item[0]) != 0) {
        func_89000020((unk_func_8830867C_02C_0CC*)(arg0 + 0x2F8), (void*)(CURSOR(arg0)->grid->data + CURSOR(arg0)->grid->stride * CURSOR(arg0)->selected));
        func_89000048((LabItemCursor*)CURSOR(arg0));
    } else {
        func_890000A4((s32*)(arg0 + 0x2F8), item[0], M2C_FIELD(arg0, s32*, 0x444));
        LabItem_SubtractSelectedItemQuantity((unk_func_8820BE14_02C_038*)CURSOR(arg0), M2C_FIELD(arg0, s32*, 0x444));
    }
}
#undef CURSOR

void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);

void func_8900219C(s8* arg0) {
    u8 row[4];
    s32* matrix;

    func_80027654(M2C_FIELD(arg0, s32**, 0x2F8), row, M2C_FIELD(arg0, s32*, 0x300));
    matrix = M2C_FIELD(arg0, s32**, 0x1E4);
    func_80027700(M2C_FIELD(arg0, s32**, 0x2F8), (u8*)(matrix[3] * M2C_FIELD(arg0, s32*, 0x1EC) + matrix[0]), M2C_FIELD(arg0, s32*, 0x300));
    func_80027700(M2C_FIELD(arg0, s32**, 0x1E4), row, M2C_FIELD(arg0, s32*, 0x1EC));
    M2C_FIELD(arg0, s32**, 0x494)[M2C_FIELD(arg0, s32*, 0x1D8)] = 1;
    M2C_FIELD(arg0, s32**, 0x494)[M2C_FIELD(arg0, s32*, 0x1D4)] = M2C_FIELD(arg0, s32**, 0x494)[M2C_FIELD(arg0, s32*, 0x1D8)];
}

void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);

void func_89002248(s8* arg0) {
    u8 row[4];
    s32* matrix = M2C_FIELD(arg0, s32**, 0x1E4);

    func_80027654(matrix, row, M2C_FIELD(arg0, s32*, 0x1EC));
    func_80027700(matrix, (u8*)(matrix[3] * M2C_FIELD(arg0, s32*, 0x40C) + matrix[0]), M2C_FIELD(arg0, s32*, 0x1EC));
    func_80027700(matrix, row, M2C_FIELD(arg0, s32*, 0x40C));
    M2C_FIELD(arg0, s32**, 0x494)[M2C_FIELD(arg0, s32*, 0x1D4)] = 1;
}


void func_890022D0(s8 *arg0) {
    s32 temp_v0;
    s8 *temp_a0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x1A4);
    temp_a0 = arg0 + 0x2F8;
    M2C_FIELD(temp_a0, s32 *, -0x120) = temp_v0;
    func_89001230(temp_a0, M2C_FIELD(arg0, s32 *, 0x490) + (temp_v0 * 0x10));
    M2C_FIELD(arg0, s32 *, 0) = 4;
}

s32 func_8002B2B0(void *);
s32 func_89000258(u8, s32);
s32 func_8002DDFC(s8*);
extern s32 D_8900A688[];
extern s32 D_8900A694;
extern s8 D_89018648[];

typedef struct Pair89002318 { u8 unk0; u8 unk1; } Pair89002318;
typedef struct Ent89002318 { char unk0[0x10]; } Ent89002318;

s32 func_89002318(s8* arg0) {
    s32 ret = 0;
    s32 idx;
    s32 next = 0;
    u8* ptr;
    s32 v;
    u8* ptr2;

    switch (*(s32*)arg0) {
        case 1:
            if (func_8002B2B0(arg0 + 0x100) != 0) {
                break;
            }
            v = func_8002BC14(D_800603C0);
            if (v == -1) {
                func_8003F6AC(3);
                ret = -1;
                break;
            }
            if (v != 1) {
                break;
            }
            if (*(s32*)(arg0 + 0x104) == 3) {
                func_8003F6AC(3);
                ret = -1;
                break;
            }
            func_8003F6AC(2);
            next = 2;
            if (*(s32*)(arg0 + 0x104) != 1) {
                break;
            }
            func_89001230(arg0 + 0x2F8, arg0 + 0x49C);
            *(s32*)(arg0 + 0x1D8) = -1;
            break;

        case 2:
            v = func_89000FA4(arg0 + 0x10C);
            if (v == -1) {
                *(s32*)arg0 = 1;
                break;
            }
            if (v <= 0) {
                break;
            }
            if ((*(u16**)(arg0 + 0x13C))[*(s32*)(arg0 + 0x140)] & 0x100) {
                *(s32*)arg0 = 9;
                func_8002CEEC(arg0 + 0x4AC, (void*)D_8900A688[*(s32*)(arg0 + 0x104)], 0, 1, 0);
                func_8003F6AC(8);
                break;
            }
            func_8003F6AC(2);
            idx = *(s32*)(arg0 + 0x140);
            *(s32*)(arg0 + 0x1D4) = idx;
            func_89001230(arg0 + 0x1E4, *(s32*)(arg0 + 0x490) + (idx * 0x10));
            if (*(s32*)(arg0 + 0x104) == 1) {
                *(s32*)arg0 = 4;
                break;
            }
            next = 3;
            break;

        case 3:
            v = func_89000FA4(arg0 + 0x170);
            if (v == -1) {
                next = 2;
                break;
            }
            if (v <= 0) {
                break;
            }
            if ((*(u16**)(arg0 + 0x1A0))[*(s32*)(arg0 + 0x1A4)] & 0x100) {
                func_8003F6AC(8);
                *(s32*)arg0 = 10;
                func_8002CEEC(arg0 + 0x4AC, (void*)D_8900A688[*(s32*)(arg0 + 0x104)], 0, 1, 0);
                break;
            }
            func_8003F6AC(2);
            if (*(s32*)(arg0 + 0x1A4) == 2) {
                if (*(s32*)(*(s32*)(arg0 + 0x498)) == -1) {
                    ret = 1;
                    break;
                }
            }
            func_890022D0(arg0);
            break;

        case 4:
            v = func_890013F8(arg0 + 0x1E4, 0);
            if (v == -1) {
                *(s32*)arg0 = 1;
                break;
            }
            if (v != 1) {
                break;
            }
            ptr = ((LabItemCursorZ*)(arg0 + 0x1E4))->grid->data + ((LabItemCursorZ*)(arg0 + 0x1E4))->selected * 2;
            if (*(s32*)(arg0 + 0x104) == 0) {
                if (func_80031C24(*ptr) != 0 && *(s32*)(arg0 + 0x1D8) == 2) {
                    func_8003F6AC(8);
                    func_8002CEEC(arg0 + 0x4AC, (void*)D_8900A694, 1, 2, 0xC);
                    *(s32*)arg0 = 11;
                    break;
                }
                v = func_89000258(*ptr, *(s32*)(arg0 + 0x2F8));
                if (v == 0) {
                    func_8003F6AC(8);
                    *(s32*)arg0 = 11;
                    func_8002CEEC(arg0 + 0x4AC, D_89018648, 0, 1, 0);
                    break;
                }
                func_8003F6AC(2);
                if (func_80031CC8(*ptr) == 0) {
                    func_890008C8(arg0 + 0x410, *(s32*)(arg0 + 0x2F0) + 0x98,
                                  *(s32*)(arg0 + 0x2F4) + *(s32*)(arg0 + 0x218) - *(s32*)(arg0 + 0x210) + 0x2C,
                                  ptr[1], v);
                    *(s32*)arg0 = 8;
                } else {
                    *(s32*)arg0 = 5;
                }
                break;
            }
            if (*(s32*)(arg0 + 0x104) == 2) {
                if (func_80031C24(*ptr) != 0 && *(s32*)(arg0 + 0x1D8) == 2) {
                    func_8003F6AC(8);
                    func_8002CEEC(arg0 + 0x4AC, (void*)D_8900A694, 1, 2, 0xC);
                    *(s32*)arg0 = 11;
                    break;
                }
                func_8003F6AC(2);
                *(s32*)arg0 = 6;
                break;
            }
            func_8003F6AC(2);
            (*(u16**)(arg0 + 0x1E8))[*(s32*)(arg0 + 0x1EC)] |= 8;
            *(s32*)(arg0 + 0x40C) = *(s32*)(arg0 + 0x1EC);
            *(s32*)arg0 = 7;
            break;

        case 8:
            v = func_89000BEC(arg0 + 0x410);
            if (v == -1) {
                *(s32*)arg0 = 4;
                break;
            }
            if (v == 1) {
                *(s32*)arg0 = 5;
            }
            break;

        case 5:
            v = func_890013F8(arg0 + 0x2F8, 0x200);
            if (v == -1) {
                *(s32*)arg0 = 4;
                break;
            }
            if (v != 1) {
                break;
            }
            func_8003F6AC(0x18);
            func_890020C0((u8*)arg0);
            if (*(s32*)(*(s32*)(arg0 + 0x1E4) + 8) == 0) {
                *(s32*)arg0 = 1;
                break;
            }
            *(s32*)arg0 = 4;
            break;

        case 7:
            v = func_890013F8(arg0 + 0x1E4, 0);
            if (v == -1) {
                func_8002D900(arg0 + 0x1E4);
                *(s32*)arg0 = 4;
                break;
            }
            if (v != 1) {
                break;
            }
            func_8003F6AC(0x18);
            func_89002248(arg0);
            func_8002D900(arg0 + 0x1E4);
            *(s32*)arg0 = 4;
            break;

        case 6:
            v = func_890013F8(arg0 + 0x2F8, 0);
            if (v == -1) {
                *(s32*)arg0 = 4;
                break;
            }
            if (v != 1) {
                break;
            }
            ptr2 = ((LabItemCursorZ*)(arg0 + 0x2F8))->grid->data + ((LabItemCursorZ*)(arg0 + 0x2F8))->selected * 2;
            if (func_80031C24(*ptr2) != 0 &&
                *(s32*)(arg0 + 0x1D4) == 2) {
                func_8003F6AC(8);
                func_8002CEEC(arg0 + 0x4AC, (void*)D_8900A694, 1, 2, 0xC);
                *(s32*)arg0 = 12;
                break;
            }
            func_8003F6AC(0x18);
            func_8900219C(arg0);
            *(s32*)arg0 = 4;
            break;

        case 9:
            if (func_8002D138(arg0 + 0x4AC) == 1) {
                *(s32*)arg0 = 2;
            }
            break;
        case 10:
            if (func_8002D138(arg0 + 0x4AC) == 1) {
                *(s32*)arg0 = 3;
            }
            break;
        case 11:
            if (func_8002D138(arg0 + 0x4AC) == 1) {
                *(s32*)arg0 = 4;
            }
            break;
        case 12:
            if (func_8002D138(arg0 + 0x4AC) == 1) {
                *(s32*)arg0 = 6;
            }
            break;
    }

    if (next > 0) {
        switch (next) {
            case 2:
                func_89000E98(arg0 + 0x10C, *(s32*)(arg0 + 4) + 0x1F, *(s32*)(arg0 + 8) + 0x29, *(s32*)(arg0 + 0x1DC),
                              *(s32*)(arg0 + 0x1E0), *(s32*)(arg0 + 0x1D4));
                func_89000CF0(arg0 + 0x10C, *(s8**)(arg0 + 0x490));
                break;
            case 3:
                func_89000E98(arg0 + 0x170, *(s32*)(arg0 + 4) + 0x14F, *(s32*)(arg0 + 8) + 0x29, *(s32*)(arg0 + 0x1DC),
                              *(s32*)(arg0 + 0x1E0), *(s32*)(arg0 + 0x1D8));
                if (*(s32*)(arg0 + 0x104) == 2) {
                    func_89000CF0(arg0 + 0x170, *(s8**)(arg0 + 0x490));
                }
                func_89000D34(arg0 + 0x170, *(s32*)(arg0 + 0x1D4));
                *(s32*)(arg0 + 0x1A4) = 0;
                func_8002DDFC(arg0 + 0x19C);
                break;
        }
        *(s32*)arg0 = next;
    }
    return ret;
}

extern Color_RGBA8 D_8900A698;
extern u8 D_8900A69C[];
extern char D_89018660[];
extern char D_8901866C[];
void func_8002A3F8(void*, s32, s32);
void func_80027F20(s32);
void func_89002A80(s32 arg0, s32 arg1, s8* arg2, s32 arg3, s32 arg4) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0x13C, 0x3C, *(Color_RGBA8*)&D_8900A5BC);
    func_80029028(arg0, arg1, 0x13C, 1, D_8900A698);
    func_80029028(arg0, arg1 + 0x3D, 0x13C, 1, D_8900A698);
    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0x136, 0x38, D_8900A5BC);
    }
    func_8002A3F8(D_8900A69C, arg0 + 0xB, arg1 + 0xB);
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0x53, arg1 + 6, D_89018660, arg2 + 8);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x58, arg1 + 0x24, D_8901866C, M2C_FIELD(arg2, s32*, 4));
    Font_EndTexturedTextRendering();
}

typedef struct Col89002C10 { u8 r, g, b, a; } Col89002C10;
typedef struct Win89002C10 {
    s32 x; s32 y; s32 w; s32 h; s32 unk10; s32 unk14; s32 unk18; s32 unk1C;
    void* unk20; s32 unk24; s32 unk28;
    char unk2C[0x14];
    s32 unk40;
    Col89002C10 unk44;
    Col89002C10 unk48;
    char unk4C[0x20];
    s32 unk6C;
    char unk70[0x10];
    char unk80[1];
} Win89002C10;
extern Col89002C10 D_8900A6AC;
extern Col89002C10 D_8900A6B0;
extern char D_89018678[];
void func_89002A80();
void func_8002A8C4(s8*, s32, s32, s32, s32);
void func_8002D880(s8*, s32, s32, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void func_89002C10(s8* arg, s32 arg1, s32 arg2, s8* arg3) {
    Win89002C10* arg0 = (Win89002C10*)arg;
    s32 pad;
    func_8002A8C4(arg, arg1, arg2, 0x148, 0x14A);
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk14 = 0x801;
    arg0->unk20 = D_89018678;
    func_8002A8C4((s8*)arg0->unk2C, arg0->x + 6, arg0->y + 0x104, arg0->w - 0xC, 0x40);
    arg0->unk40 = 6;
    arg0->unk44 = D_8900A6AC;
    arg0->unk48 = D_8900A6B0;
    func_80027410((s8*)arg0->unk70, arg3, 0x14, 4, 4);
    func_8002D880((s8*)arg0->unk4C, (s32)arg0->unk70, (s32)arg0->unk80, (s32)func_89002A80, 0x13C, 0x3E);
    arg0->unk6C |= 0x10000;
}

void func_80029658(s32, s32, s32, void*);
void func_8002A8E0(void*);
void func_8002DAD8(void*, s32, s32, s32, s32);
extern u8 D_8007356C[];
extern u8 D_89018688[];
void func_89002D14(s8* arg0, s32 arg1) {
    if (func_8002AE6C() == 0) {
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 0x30) - 7, M2C_FIELD(arg0, s32*, 8), D_8007356C);
        func_8002A8E0(arg0 + 0x2C);
        func_8002DAD8(arg0 + 0x4C, M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, 0xFFEF, 0);
        func_8001AB6C();
        func_8001A384(8, 0);
        if (!arg0) { // FAKE: empty test only changes register allocation; needed to match
        }
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8 *, 0), M2C_FIELD(&D_800734A8, u8 *, 1), M2C_FIELD(&D_800734A8, u8 *, 2), M2C_FIELD(&D_800734A8, u8 *, 3));
        func_8001AB2C(0x1C);
        func_8001A944(M2C_FIELD(arg0, s32*, 0x2C) + 8, M2C_FIELD(arg0, s32*, 0x30) + 8, D_89018688);
        func_8001ABBC();
    }
}

s32 func_8002DC04(void*);

s32 func_89002DE4(unk_func_8820E99C_030* arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (func_8002DC04((u8*)arg0 + 0x4C) == 0) {
        dir = Ui_GetSelectionDirection((unk_func_8002EBD8_arg0*)gPlayer1Controller);
        if (dir == -1) {
            Audio_PlaySoundEffectById(3);
            sp1C = -1;
        } else if (dir == 1) {
            Audio_PlaySoundEffectById(2);
            sp1C = 1;
        }
    }
    return sp1C;
}

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

void func_89002E58(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8002A8C4(arg0 + 4, arg1, arg2, 0x184, 0x180);
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = 0;
    M2C_FIELD(arg0, s32*, 0x18) = 0x1001;
    func_8002A8C4(arg0 + 0x30, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 0x142,
                  M2C_FIELD(arg0, s32*, 0xC) - 0xC, 0x38);
    M2C_FIELD(arg0, s32*, 0x44) = 6;
    M2C_FIELD(arg0, Rgba89000D50*, 0x48) = D_8900A6B4;
    M2C_FIELD(arg0, Rgba89000D50*, 0x4C) = D_8900A6B8;
    func_8002B018(arg0 + 0x50, arg1 + 0x2B, arg2 + 0x47, 0x36, 0x2A, 0x30, (s32)D_8900BFC0);
    M2C_FIELD(arg0, Rgba89000D50*, 0x68) = *(Rgba89000D50*)D_8900A580;
    M2C_FIELD(arg0, Rgba89000D50*, 0x6C) = *(Rgba89000D50*)D_8900A584;
    M2C_FIELD(arg0, Rgba89000D50*, 0x70) = D_8900A5BC;
    func_8002B018(arg0 + 0xA8, arg1 + 0x2B, arg2 + 0x9F, 0x36, 0x2A, 0x30, (s32)D_890110F0);
    M2C_FIELD(arg0, Rgba89000D50*, 0xC0) = *(Rgba89000D50*)D_8900A5A8;
    M2C_FIELD(arg0, Rgba89000D50*, 0xC4) = *(Rgba89000D50*)D_8900A5AC;
    M2C_FIELD(arg0, Rgba89000D50*, 0xC8) = D_8900A5BC;
    func_8002B018(arg0 + 0x7C, arg1 + 0x2B, arg2 + 0xF7, 0x36, 0x2A, 0x30, (s32)D_89010368);
    M2C_FIELD(arg0, Rgba89000D50*, 0x94) = *(Rgba89000D50*)D_8900A5A0;
    M2C_FIELD(arg0, Rgba89000D50*, 0x98) = *(Rgba89000D50*)D_8900A5A4;
    M2C_FIELD(arg0, Rgba89000D50*, 0x9C) = D_8900A5BC;
    M2C_FIELD(arg0, s32*, 0xDC) = 3;
    M2C_FIELD(arg0, s32*, 0xD8) = 0;
    M2C_FIELD(arg0, s32*, 0xD4) = D_800603C0;
    func_8000B2F4(D_800603C0);
    func_89001250(arg0 + 0xE0, M2C_FIELD(arg0, s32*, 4) + 0x88, M2C_FIELD(arg0, s32*, 8) + 0x36, arg4);
    M2C_FIELD(arg0, s32*, 0x1F4) = arg3;
    M2C_FIELD(arg0, s32*, 0) = 1;
}

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
void func_890030C8(s32 arg0, s32 arg1, s8* arg2, s32 arg3) {
    Color8900A6BC* color;

    if (arg3 & 2) {
        color = &D_8900A6BC;
    } else {
        color = &D_8900A6C4;
    }
    func_8002A550(arg0, arg1, 0xEC, 0x2A, color->c[0], color->c[1]);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    Gfx_DrawTextureRgba16(arg0 + 6, arg1 + 8, 0x2E, 0x1A, D_89017A98, 0x30, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg3);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x34, arg1 + 2, D_890186C0, arg2 + 8);
    Font_SetActive(4, 0);
    Font_Printf(arg0 + 0x38, arg1 + 0x18, D_890186CC, M2C_FIELD(arg2, s32*, 4));
    Font_EndTexturedTextRendering();
}

extern s32 D_8900A6CC[];
extern s8 *D_8900A6D8[];
void func_8900323C(s32 *arg0) {
    char sp2C[0x54];
    List89001B88 *list;

    switch (arg0[0]) {
        case 1:
            func_890019C8(arg0[0xC], arg0[0xD], D_8900A6CC[arg0[0x36]], D_8900A6D8[arg0[0x36]]);
            break;
        case 2:
            list = (List89001B88 *)(arg0 + 0x38);
            func_89001B10(arg0[0xC], arg0[0xD], func_80031BC0((*list->data)[list->index * 2], sp2C));
            break;
    }
}

void func_800295E8(s32, s32, s32, s32, u8*);
extern u8 D_800735C4[];
void func_8002B054(s8*, s32);
void func_8002A8E0(void*);
void func_890032E4(s8* arg0) {
    s32 v;

    if (func_8002AE6C(arg0 + 4) == 0) {
        func_8002A8E0(arg0 + 0x30);
        func_80029658(M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 0x34) - 7, M2C_FIELD(arg0, s32*, 0xC), D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 6, 0x82, 0x136, *(Color_RGBA8*)&D_8900A5BC);
        func_80029028(M2C_FIELD(arg0, s32*, 4) + 0x88, M2C_FIELD(arg0, s32*, 8) + 6, 0xEC, 6, *(Color_RGBA8*)&D_8900A5BC);
        func_80029028(M2C_FIELD(arg0, s32*, 4) + 0x88, M2C_FIELD(arg0, s32*, 8) + 0x136, 0xEC, 6, *(Color_RGBA8*)&D_8900A5BC);
        func_80029028(M2C_FIELD(arg0, s32*, 4) + 0x174, M2C_FIELD(arg0, s32*, 8) + 6, 0xA, 0x136, *(Color_RGBA8*)&D_8900A5BC);
        func_800295E8(M2C_FIELD(arg0, s32*, 4) + 0x86, M2C_FIELD(arg0, s32*, 8) + 0xA, 0xF0, 0x12E, D_800735C4);
        v = (M2C_FIELD(arg0, s32*, 0) == 1) ? 2 : 0x10;
        func_8002B054(arg0 + 0x50, (M2C_FIELD(arg0, s32*, 0xD8) == 2) ? v : 0);
        func_8002B054(arg0 + 0xA8, (M2C_FIELD(arg0, s32*, 0xD8) == 0) ? v : 0);
        func_8002B054(arg0 + 0x7C, (M2C_FIELD(arg0, s32*, 0xD8) == 1) ? v : 0);
        func_890030C8(M2C_FIELD(arg0, s32*, 4) + 0x88, M2C_FIELD(arg0, s32*, 8) + 0xC, M2C_FIELD(arg0, s8**, 0x1F4), 0);
        func_890012C4(arg0 + 0xE0, (M2C_FIELD(arg0, s32*, 0) == 2) ? 2 : 0);
        func_8900323C((s32*)arg0);
    }
}

s32 func_8002B2B0(void *);
s32 func_890013F8(void *, u32);
s32 func_8900352C(s32* arg0) {
    s32 ret = 0;

    switch (arg0[0]) {
        case 1:
            if (func_8002B2B0(arg0 + 0x35) == 0) {
                s32 r = func_8002BC14(D_800603C0);
                if (r == -1) {
                        func_8003F6AC(3);
                        ret = -1;
                } else if (r == 1) {
                        switch (arg0[0x36]) {
                            case 1:
                                func_8003F6AC(2);
                                arg0[0] = 2;
                                break;
                            case 0:
                                func_8003F6AC(2);
                                ret = 1;
                                break;
                            case 2:
                                func_8003F6AC(3);
                                ret = -1;
                                break;
                        }
                }
            }
            break;
        case 2:
            if (func_890013F8(arg0 + 0x38, 0) == -1) {
                arg0[0] = 1;
            }
            break;
    }
    return ret;
}

typedef struct Entry89003650 { s32 unk00; char unk04[0x10]; } Entry89003650;
typedef struct Ctx89003650 {
    /* 0x000 */ s32 unk000;
    /* 0x004 */ s8 unk004[0x880];
    /* 0x884 */ s8 unk884[0x2A];
    /* 0x8AE */ s8 unk8AE[0x66];
    /* 0x914 */ s8 unk914[0xCC];
    /* 0x9E0 */ s8 list0[0x10];
    /* 0x9F0 */ s8 list1[0x10];
    /* 0xA00 */ s8 list2[0x10];
    /* 0xA10 */ s32 sel[3];
    /* 0xA1C */ s32 idx;
    /* 0xA20 */ Entry89003650 entries[1];
} Ctx89003650;
s32 func_890002D4(Entry89003650*, s32, s32*);
void func_890003C0(Entry89003650*);
void func_89000448(s32, s32, s32, s8*);
void func_8900147C(s8*, s32, s32, s8*, s32*, s32*);
extern s32 D_89019108;
extern s32 D_89019118;
extern s32 D_8901911C;

void func_89003650(Ctx89003650* arg0) {
    s32 i;

    func_80027410(arg0->list0, arg0->unk884, 2, 0x14, 0);
    func_80027410(arg0->list1, arg0->unk8AE, 2, 0x32, 0);
    func_80027410(arg0->list2, arg0->unk914, 2, 0x64, 0);
    func_89000448(0x23, D_89019108, 0, arg0->list0);
    func_89000448(0x22, D_89019108, 0, arg0->list1);
    func_890003C0(arg0->entries);
    arg0->idx = func_890002D4(arg0->entries, D_89019118, &D_8901911C);
    if ((arg0->idx != -1) && (arg0->entries[arg0->idx].unk00 != 0)) {
        func_89000448(0x12, 0, arg0->idx, arg0->list2);
    }
    i = 0;
    do {
        arg0->sel[i] = 0;
        i++;
    } while (i != 3);
    func_8900147C(arg0->unk004, 0x26, 0x51, arg0->list0, arg0->sel, &arg0->idx);
    arg0->unk000 = 1;
}
