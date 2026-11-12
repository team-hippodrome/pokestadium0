/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "lab_pc_icons.h"

extern s32 D_8A21DE08;
extern M2C_UNK D_8A21DE10;

s32 Display_IsFrameReady(void);
s32 func_80002BA4(void*, s32);
s32 func_80017304(s32, BinArchive*, s32, void*, s32);
s32 func_8001FA8C(s32);
s32 func_8002D3D0(u8*);
s32 func_8002D454();
typedef struct Move8A201D3C { u8 unk00; u8 unk01; u8 power; u8 type; u8 unk04; u8 unk05; } Move8A201D3C;
extern Move8A201D3C D_8006B190[];
extern BinArchive* D_8A21DA54;
extern void* D_8A21DA58;
extern void* D_8A21DA60[4];
extern s32 D_8A21DA70[];

/**
 * Draws a 282x130 YUV image at (x, y) as 16x16 tiles (the last column and row are cut
 * to 10 and 2 pixels).
 */
void func_8A201598(s32 x, s32 y, u8* image) {
    s32 j;
    s32 i;
    s32 w;
    s32 h;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, 0x0F0A4000, 0);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombine(gDisplayListHead++, 0x17FE2F, 0x77FCF87C);
    gDPSetTextureConvert(gDisplayListHead++, G_TC_CONV);
    gDPSetConvert(gDisplayListHead++, G_CV_K0, G_CV_K1, G_CV_K2, G_CV_K3, G_CV_K4, G_CV_K5);
    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 0x90; i += 0x10) {
        h = 0x82 - i;
        if (h > 0x10) {
            h = 0x10;
        }
        for (j = 0; j < 0x120; j += 0x10) {
            w = 0x11A - j;
            if (w > 0x10) {
                w = 0x10;
            }
            left = (x + j) << 2;
            top = (y + i) << 2;
            right = (x + j + w) << 2;
            bottom = (y + i + h) << 2;
            gDPLoadTextureBlockYuv(gDisplayListHead++, image, G_IM_FMT_YUV, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, left, top, right, bottom, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
            image += 0x200;
        }
    }

    gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
}

void func_8A201598(s32, s32, u8*);
s32 func_8001FA8C(s32);
extern Color_RGBA8 D_8A203424;
extern char D_8A21D9B4[];
extern char D_8A21D9BC[];
extern char D_8A21D9C8[];
extern char D_8A21D9D4[];
extern char D_8A21D9D8[];
extern char D_8A21D9DC[];
typedef struct Entry8006A9DC { char* str; s32 unk4; s32 unk8; } Entry8006A9DC;
extern Entry8006A9DC D_8006A9DC[];
/**
 * Declared s32 with no return statement: only then does IDO stop reading the
 * move id from v0 after the -2 check.
 * @unverified Name guessed from the code; comment kept.
 */
s32 MonSummary_DrawMoveInfo(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 move;
    func_8A201598(arg0 + 4, arg1 + 2, (u8*)D_8A21DA70[arg3]);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x122, 2, D_8A203424);
    func_80029028(arg0, arg1 + 2, 4, 0x82, D_8A203424);
    func_80029028(arg0 + 0x11E, arg1 + 2, 4, 0x82, D_8A203424);
    move = func_8002D454(arg2, arg3);
    if (move != (-2)) {
        s32 type_id;
        Entry80066AD8 *type;
        s32 pp;
        type_id = func_8001FA8C(D_8006B190[move].type);
        type = &D_80066AD8[type_id];
        pp = ((((D_8006B190[move].unk04 * 100) / 255) + 2) / 5) * 5;
        func_8001AB6C();
        func_8001A384(4, 0);
        func_8001AA9C(0xFF, 0xC8, 0xC8, 0xFF);
        func_8001A944(arg0 + 9, arg1 + 4, D_8A21D9B4);
        func_8001A944(arg0 + 0x99, arg1 + 4, D_8A21D9BC);
        func_8001A944(arg0 + 9, arg1 + 0x17, D_8A21D9C8);
        func_8001AA9C(type->color.r, type->color.g, type->color.b, type->color.a);
        func_8001A944(arg0 + 0x49, arg1 + 4, type->str);
        func_8001AA9C(*((u8 *) (((s8 *) (&D_800734A8)) + 0)), *((u8 *) (((s8 *) (&D_800734A8)) + 1)), *((u8 *) (((s8 *) (&D_800734A8)) + 2)), *((u8 *) (((s8 *) (&D_800734A8)) + 3))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
        Font_SetLineHeight(0x14);
        if (D_8006B190[move].power >= 2)
        {
            func_8001A944(arg0 + 0xE9, arg1 + 4, D_8A21D9D4, D_8006B190[move].power);
        }
        else
        {
            func_8001A944(arg0 + 0xE9, arg1 + 4, D_8A21D9D8, D_8006B190[move].power);
        }
        func_8001A944(arg0 + 0x69, arg1 + 0x17, D_8A21D9DC, pp);
        func_8001A384(4, -1);
        Font_SetLineHeight(0x18);
        func_8001A944(arg0 + 9, arg1 + 0x3A, D_8006A9DC[move].str);
        func_8001ABBC();
    }
}

void func_8A201C08(s32 arg0, s32 arg1, s32 arg2) {
    u8* tex;
    s32 i;
    s32 n;

    tex = func_800196F8(D_8A21DA4C);
    func_800069CC();
    gSPDisplayList(gDisplayListHead++, D_80060290);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    for (i = 0; i < 0xD2; i += n) {
        if ((0xD2 - i) < 8) {
            n = 0xD2 - i;
        } else {
            n = 8;
        }
        func_8001B884(arg0, arg1 + i, 0xF4, n, tex, 0x100, 0x200000);
        tex += n << 9;
    }
    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}


void func_8A201D3C(s8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 unused; // FAKE: stack padding
    s32 count;
    s32 i;
    s32 handle;
    s32 move;

    Window_SetRect(arg0, arg1, arg2, 0x228, 0x16A);
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x1001;
    M2C_FIELD(arg0, s32*, 0x34) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = arg3;
    count = func_8002D3D0((u8*)arg3);
    while (Display_IsFrameReady() == 0) {
    }
    for (i = 0; i < count; i++) {
        handle = func_80002BA4(D_8A21DA60[i], 0x14800);
        move = func_8002D454(arg3, i);
        D_8A21DA70[i] = func_80017304(handle, D_8A21DA54, func_8001FA8C((move == -2) ? 0 : D_8006B190[move].type), D_8A21DA58, 0x3000);
    }
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Draws the summary page: header, stats, trainer info and moves.
 * @unverified Name and comment guessed from the code.
 */
void MonSummary_DrawPage(s8 *arg0, s32 arg1)
{
  s32 temp_v0;
  if (((*((s32 *) (((s8 *) arg0) + 0x28))) != 2) && (func_8002AB84() == 0))
  {
    if (arg1 == 0)
    {
      func_80029864((*((s32 *) (((s8 *) arg0) + 0))) + 0xF9, *((s32 *) (((s8 *) arg0) + 4)), *((s32 *) (((s8 *) arg0) + 0xC)), &D_8007356C); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      Ui_DrawTexturedDivider(*((s32 *) (((s8 *) arg0) + 0)), (*((s32 *) (((s8 *) arg0) + 4))) + 0xD7, 0x100, &D_8007356C); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      Ui_DrawTexturedDivider((*((s32 *) (((s8 *) arg0) + 0))) + 0xFA, (*((s32 *) (((s8 *) arg0) + 4))) + 0x95, 0x12E, &D_8007356C); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      MonSummary_DrawStats((*((s32 *) (((s8 *) arg0) + 0))) + 6, (*((s32 *) (((s8 *) arg0) + 4))) + 0xDE, *((s32 *) (((s8 *) arg0) + 0x2C))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      MonSummary_DrawHeader((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 6, *((s32 *) (((s8 *) arg0) + 0x2C))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      MonSummary_DrawTrainerInfo((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 0x9C, *((s32 *) (((s8 *) arg0) + 0x2C))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    }
    else
    {
      Ui_DrawTexturedDivider(*((s32 *) (((s8 *) arg0) + 0)), (*((s32 *) (((s8 *) arg0) + 4))) + 0xD7, *((s32 *) (((s8 *) arg0) + 8)), &D_8007356C); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      func_80029864((*((s32 *) (((s8 *) arg0) + 0))) + 0xF9, *((s32 *) (((s8 *) arg0) + 4)), 0xDE, &D_8007356C); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      func_8A201394((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 6, *((s32 *) (((s8 *) arg0) + 0x2C))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      func_8A2010C8((*((s32 *) (((s8 *) arg0) + 0))) + 6, (*((s32 *) (((s8 *) arg0) + 4))) + 0xDE, *((s32 *) (((s8 *) arg0) + 0x2C)), *((s32 *) (((s8 *) arg0) + 0x30))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      MonSummary_DrawMoveInfo((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 0x54, *((s32 *) (((s8 *) arg0) + 0x2C)), *((s32 *) (((s8 *) arg0) + 0x30))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    }
  }
  temp_v0 = *((s32 *) (((s8 *) arg0) + 0x28));
  if (((temp_v0 ^ 0) == 1) || (temp_v0 == 2)) // FAKE: no-op ^ 0
  {
    if ((*((s32 *) (((s8 *) arg0) + 0x34))) == 0)
    {
      *((s32 *) (((s8 *) arg0) + 0x34)) = 1;
      func_80019008(D_8A21DA4C, *((s32 *) (((s8 *) arg0) + 0x2C)), 0x108D);
    }
    func_8A201C08(0x32, 0x5A, *((s32 *) (((s8 *) arg0) + 0x2C)));
  }
}

s32 func_8A202078(s8 *arg0) {
    s32 var_s0;
    u16 temp_v0;

    var_s0 = -1;
    if (func_80022B40() != 0) {
        temp_v0 = M2C_FIELD(D_800603C0, u16 *, 8);
        if (temp_v0 & 8) {
            var_s0 = 0;
        } else if (temp_v0 & 1) {
            var_s0 = 1;
        } else if (temp_v0 & 4) {
            var_s0 = 2;
        } else if (temp_v0 & 2) {
            var_s0 = 3;
        }
        if (var_s0 >= 0) {
            if (func_8002D454(M2C_FIELD(arg0, s32 *, 0x2C), var_s0, arg0) == -1) {
                func_8003F6AC(8);
            } else {
                func_8003F6AC(2);
                M2C_FIELD(arg0, s32 *, 0x30) = var_s0;
                if (M2C_FIELD(arg0, s32 *, 0x28) <= 0) {
                    M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
                } else {
                    M2C_FIELD(arg0, s32 *, 0x24) = 4;
                }
            }
        }
    }
    return var_s0 >= 0;
}

void func_8A202160(void) {
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, M2C_FIELD(&D_8A203300, u8 *, 0), M2C_FIELD(&D_8A203300, u8 *, 1), (s32) M2C_FIELD(&D_8A203300, u8 *, 2));
}

s32 LabPC_ComputeExpForLevel(s32 arg0, s32 arg1) {
    s32 sp4;

    switch (gBaseStats[arg0].unk_13) {
        case 0:
            sp4 = arg1 * arg1 * arg1;
            break;

        case 1:
            sp4 = (((arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 0xA * arg1)) - 0x1E;
            break;

        case 2:
            sp4 = (((arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 0x14 * arg1)) - 0x1E;
            break;

        case 3:
            sp4 = ((((arg1 * arg1 * arg1 * 6) / 5) - (arg1 * 0xF * arg1)) + (arg1 * 0x64)) - 0x8C;
            break;

        case 4:
            sp4 = (arg1 * arg1 * arg1 * 4) / 5;
            break;

        case 5:
            sp4 = (arg1 * arg1 * arg1 * 5) / 4;
            break;
    }
    return sp4;
}

void func_8A202390(s8 *arg0) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp1C = M2C_FIELD(arg0, s32 *, 0);
    temp_v0 = func_80020AFC(0x20, D_8A21DA40, 0, 0);
    sp18 = temp_v0;
    M2C_FIELD(arg0, s32 *, 8) = func_80020CE4(sp1C, M2C_FIELD(arg0, s32 *, 4), temp_v0);
    func_80020C60(sp18);
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void LabPC_WriteDeckBack(s32* arg0, s32 arg1) {
    s32* sp2C;
    s32 i;
    s32 temp_s3;

    sp2C = (s32*)arg0[0];
    func_80022118(D_8A21DA40);
    temp_s3 = func_80020AFC(0x20, D_8A21DA40, 0, 1);

    for (i = 0; i < arg0[2]; i++) {
        func_80020DF0(sp2C[i], 1, temp_s3);
    }

    func_80020C60(temp_s3);
    if (func_8002207C(D_8A21DA40) == 0) {
        func_8002D7D4(D_8A21DA40);
        func_8A20261C((M2C_UNK*)arg1);
    }
    func_80022188(D_8A21DA40);
}

void func_80027410(s8 *, s8 *, s32, s32, s32);
void func_80027804(s8 *, s8 *, s32, s32);
void func_8A2024D0(s8 *arg0) {
    s32 i;

    M2C_FIELD(arg0, s32 *, 0) = 1;
    M2C_FIELD(arg0, s8 **, 8) = arg0 + 0x10;
    M2C_FIELD(arg0, s32 *, 0x384) = 0;
    for (i = 0; i < 6; i++) {
        M2C_FIELD(arg0, s8 **, 0x18C + i * 4) = arg0 + 0x1A4 + i * 0x50;
    }
    func_80027410(arg0 + 0x170, arg0 + 0x1A4, 0x50, 6, 0);
    func_8A202390(arg0 + 0x170);
    func_80027804(arg0 + 0x180, arg0 + 0x18C, 6, M2C_FIELD(arg0, s32 *, 0x178));
    for (i = 0; i < M2C_FIELD(arg0, s32 *, 0x178); i++) {
        func_8001833C((unk_func_8001A024*)D_8A21DA50, i, (BattleMon*)(M2C_FIELD(arg0, s32 *, 0x170) + i * 0x50),
                      GPACK_RGBA5551(D_8A203304.r, D_8A203304.g, D_8A203304.b, 1));
    }
    func_8A20034C(arg0 + 0x10, 0x2F, 0x4D, (s32)(arg0 + 0x180));
}

typedef struct Ctx8A20261C {
    /* 0x000 */ s32 state;
    /* 0x004 */ s32 mode;
    /* 0x008 */ char unk008[0x8];
    /* 0x010 */ s8 list[0x24];
    /* 0x034 */ s32 unk034;
    /* 0x038 */ s32 unk038;
    /* 0x03C */ char unk03C[0x34];
    /* 0x070 */ s8 unk070[0x64];
    /* 0x0D4 */ s8 unk0D4[0x38];
    /* 0x10C */ s8 unk10C[0x4];
} Ctx8A20261C;
s32 func_8002AAC4(s8*);
void func_8002CAD0(s8*);
void func_8A2003C0(s8*, s32);
#define CTX ((Ctx8A20261C*)arg0)
void func_8A20261C(void* arg0) {
    func_800069CC();
    switch (CTX->state) {
        case 1:
            if (func_8002AAC4(CTX->list) != 0) {
                func_8A202160();
            }
            func_8A2003C0(CTX->list, 0);
            break;
        case 2:
            if ((CTX->mode == 4) || (CTX->mode == 7)) {
                func_8A202160();
                func_8002AAC4(CTX->list);
                func_8002AAC4(CTX->unk070);
                func_8A2003C0(CTX->list, 1);
            } else if (func_8002AAC4(CTX->unk070) != 0) {
                CTX->unk034 = (CTX->unk038 <= 0) ? CTX->unk034 : 4;
                func_8002AAC4(CTX->list);
                func_8A2003C0(CTX->list, 1);
                CTX->unk034 = (CTX->unk038 <= 0) ? CTX->unk034 : 4;
            } else {
                func_8002AAC4(CTX->list);
                func_8A2003C0(CTX->list, 1);
            }
            func_8A2008F4(CTX->unk070);
            break;
        case 3:
            if (func_8002AAC4(CTX->list) != 0) {
                func_8A202160();
            }
            func_8A2003C0(CTX->list, 2);
            break;
        case 4:
            if (func_8002AAC4(CTX->unk0D4) != 0) {
                func_8A202160();
            }
            MonSummary_DrawPage(CTX->unk0D4, 0);
            break;
        case 5:
            if (func_8002AAC4(CTX->unk0D4) != 0) {
                func_8A202160();
            }
            MonSummary_DrawPage(CTX->unk0D4, 1);
            break;
        case 6:
            if (CTX->mode == 7) {
                func_8A202160();
                func_8002AAC4(CTX->list);
                func_8002AAC4(CTX->unk10C);
                func_8A2003C0(CTX->list, 0);
            } else if (func_8002AAC4(CTX->unk10C) != 0) {
                CTX->unk034 = (CTX->unk038 <= 0) ? CTX->unk034 : 4;
                func_8002AAC4(CTX->list);
                func_8A2003C0(CTX->list, 0);
                CTX->unk034 = (CTX->unk038 <= 0) ? CTX->unk034 : 4;
            } else {
                func_8002AAC4(CTX->list);
                func_8A2003C0(CTX->list, 0);
            }
            func_8002CAD0(CTX->unk10C);
            break;
    }
}
#undef CTX

void func_8A202904(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(M2C_FIELD(arg0, s8 **, 8), s32 *, 0x24) = 7;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = arg2;
}

typedef struct Ctx8A20291C { char pad[0x18C]; s32 ptrs[6]; } Ctx8A20291C;
s32 func_8002DC04(s8*);
s32 func_8002BC14(s32);
void func_8002CA34(s8*, s32, s32);
void func_8002D900(s8*);
s32 func_8002CD7C(s8*);
void Save_DrawReportingWindow(s8*);
s32 func_8A20093C(s8*);
void func_8A20080C(s8* arg0, s32 arg1, s32 arg2, u8* arg3);
s32 func_8A202078(s8* arg0);
void LabPC_WriteDeckBack(s32* arg0, s32 arg1);
M2C_UNK func_8A20291C(M2C_UNK* ctx) {
    s32 ret = 0;
    s8* arg0 = (s8*)ctx;
    s32 res;

    if (M2C_FIELD(M2C_FIELD(arg0, s8**, 8), s32*, 0x28) == 4) {
        M2C_FIELD(arg0, s32*, 0) = M2C_FIELD(arg0, s32*, 4);
        if (M2C_FIELD(arg0, s32*, 0) == 7) {
            ret = 1;
        } else {
            M2C_FIELD(arg0, s32*, 4) = 0;
            M2C_FIELD(arg0, s8**, 8) = M2C_FIELD(arg0, s8**, 0xC);
        }
        return ret;
    }
    if ((M2C_FIELD(M2C_FIELD(arg0, s8**, 8), s32*, 0x28) != 1) && (M2C_FIELD(M2C_FIELD(arg0, s8**, 8), s32*, 0x28) != 2)) {
        return 0;
    }

    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 1:
            if (func_8002DC04(arg0 + 0x3C) != 0) {
                M2C_FIELD(arg0, s32*, 0x34) = (M2C_FIELD(arg0, s32*, 0x38) <= 0) ? M2C_FIELD(arg0, s32*, 0x34) : 4;
            } else {
                res = func_8002BC14((s32)D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    if (M2C_FIELD(arg0, s32*, 0x384) != 0) {
                        func_8002CA34(arg0 + 0x10C, 0xCA, 0xAD);
                        M2C_FIELD(arg0, s32*, 0) = 6;
                        M2C_FIELD(arg0, s8**, 8) = arg0 + 0x10C;
                    } else {
                        func_8A202904(arg0, 7, 0);
                    }
                } else if (res == 1) {
                    func_8003F6AC(2);
                    func_8A20080C(arg0 + 0x70, 0x194, 0x123, (u8*)((Ctx8A20291C*)arg0)->ptrs[M2C_FIELD(arg0, s32*, 0x44)]);
                    M2C_FIELD(arg0, s32*, 0) = 2;
                    M2C_FIELD(arg0, s8**, 8) = arg0 + 0x70;
                }
            }
            break;
        case 2:
            res = func_8A20093C(arg0 + 0x70);
            if (res == -1) {
                func_8003F6AC(3);
                func_8A202904(arg0, 1, (s32)(arg0 + 0x10));
            } else if (res > 0) {
                switch (res) {
                    case 1:
                        func_8003F6AC(2);
                        func_8A202904(arg0, 4, (s32)(arg0 + 0xD4));
                        M2C_FIELD(arg0, s32*, 0x104) = 0;
                        M2C_FIELD(arg0, s32*, 0x34) = 7;
                        func_8A201D3C(arg0 + 0xD4, 0x2C, 0x54, ((Ctx8A20291C*)arg0)->ptrs[M2C_FIELD(arg0, s32*, 0x44)]);
                        break;
                    case 2:
                        func_8003F6AC(2);
                        func_8A202904(arg0, 3, (s32)(arg0 + 0x10));
                        M2C_FIELD(arg0, u16**, 0x40)[M2C_FIELD(arg0, s32*, 0x44)] |= 8;
                        M2C_FIELD(arg0, s32*, 0x6C) = M2C_FIELD(arg0, s32*, 0x44);
                        break;
                    case 3:
                        func_8003F6AC(3);
                        if (M2C_FIELD(arg0, s32*, 0x384) != 0) {
                            func_8002CA34(arg0 + 0x10C, 0xD4, 0xAD);
                            func_8A202904(arg0, 6, (s32)(arg0 + 0x10C));
                        } else {
                            func_8A202904(arg0, 7, 0);
                            M2C_FIELD(arg0, s32*, 0x34) = 7;
                        }
                        break;
                }
            }
            break;
        case 3:
            if (func_8002DC04(arg0 + 0x3C) != 0) {
                M2C_FIELD(arg0, s32*, 0x34) = (M2C_FIELD(arg0, s32*, 0x38) <= 0) ? M2C_FIELD(arg0, s32*, 0x34) : 4;
            } else {
                res = func_8002BC14((s32)D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    M2C_FIELD(arg0, s32*, 0) = 1;
                    M2C_FIELD(arg0, s8**, 8) = arg0 + 0x10;
                    M2C_FIELD(arg0, s32*, 0x34) = (M2C_FIELD(arg0, s32*, 0x38) <= 0) ? M2C_FIELD(arg0, s32*, 0x34) : 4;
                    func_8002D900(arg0 + 0x3C);
                } else if (res == 1) {
                    func_8003F6AC(0x18);
                    res = ((Ctx8A20291C*)arg0)->ptrs[M2C_FIELD(arg0, s32*, 0x6C)];
                    ((Ctx8A20291C*)arg0)->ptrs[M2C_FIELD(arg0, s32*, 0x6C)] = ((Ctx8A20291C*)arg0)->ptrs[M2C_FIELD(arg0, s32*, 0x44)];
                    ((Ctx8A20291C*)arg0)->ptrs[M2C_FIELD(arg0, s32*, 0x44)] = res;
                    func_8001833C((unk_func_8001A024*)D_8A21DA50, M2C_FIELD(arg0, s32*, 0x6C), (BattleMon*)((Ctx8A20291C*)arg0)->ptrs[M2C_FIELD(arg0, s32*, 0x6C)], 0);
                    func_8001833C((unk_func_8001A024*)D_8A21DA50, M2C_FIELD(arg0, s32*, 0x44), (BattleMon*)((Ctx8A20291C*)arg0)->ptrs[M2C_FIELD(arg0, s32*, 0x44)], 0);
                    M2C_FIELD(arg0, s32*, 0x384) = 1;
                    M2C_FIELD(arg0, s32*, 0) = 1;
                    M2C_FIELD(arg0, s8**, 8) = arg0 + 0x10;
                    M2C_FIELD(arg0, s32*, 0x34) = (M2C_FIELD(arg0, s32*, 0x38) <= 0) ? M2C_FIELD(arg0, s32*, 0x34) : 4;
                    func_8002D900(arg0 + 0x3C);
                }
            }
            break;
        case 4:
            res = func_8002BC14((s32)D_800603C0);
            if (res == -1) {
                func_8003F6AC(3);
                func_8A202904(arg0, 1, (s32)(arg0 + 0x10));
                M2C_FIELD(arg0, s32*, 0x34) = 0;
            } else if (res == 1) {
                func_8003F6AC(2);
                M2C_FIELD(arg0, s32*, 0) = 5;
                M2C_FIELD(arg0, s32*, 0xF8) = (M2C_FIELD(arg0, s32*, 0xFC) <= 0) ? M2C_FIELD(arg0, s32*, 0xF8) : 4;
            }
            break;
        case 5:
            if (func_8A202078(arg0 + 0xD4) == 0) {
                res = func_8002BC14((s32)D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    M2C_FIELD(arg0, s32*, 0) = 4;
                    M2C_FIELD(arg0, s32*, 0xF8) = (M2C_FIELD(arg0, s32*, 0xFC) <= 0) ? M2C_FIELD(arg0, s32*, 0xF8) : 4;
                } else if (res == 1) {
                    func_8003F6AC(2);
                    func_8A202904(arg0, 1, (s32)(arg0 + 0x10));
                    M2C_FIELD(arg0, s32*, 0x34) = 0;
                }
            }
            break;
        case 6:
            res = func_8002CD7C(arg0 + 0x10C);
            if (res == -1) {
                func_8A202904(arg0, 1, (s32)(arg0 + 0x10));
            } else if (res > 0) {
                switch (res) {
                    case 1:
                        Save_DrawReportingWindow(arg0 + 0x10C);
                        LabPC_WriteDeckBack((s32*)(arg0 + 0x180), (s32)arg0);
                        func_8A202904(arg0, 7, 0);
                        M2C_FIELD(arg0, s32*, 0x34) = 7;
                        break;
                    case 2:
                        func_8A202904(arg0, 7, 0);
                        M2C_FIELD(arg0, s32*, 0x34) = 7;
                        break;
                }
            }
            break;
        case 7:
            ret = 1;
            break;
    }
    return ret;
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattlePrep_RenderFrame(void) {
    D_8A21DA40 = func_80025BD8();
    D_8A21DE08 = D_8A21DA40;
    if (D_8A21DE08 != -1) {
        func_80027FF8(&D_8A21DE10, D_8A21DE08);
    }
    func_8A2024D0(&D_8A21DA80);
}

typedef struct ColF50 { u8 r, g, b, a; } ColF50;
extern s32 D_8A203428;
extern s32 D_8A20342C;
/*
 * Second name for D_8A203428. The fade-out store in this function family
 * (also func_8200579C, func_8900429C, func_891049E8, func_8A101B30) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_8A203428_2;
extern M2C_UNK D_8A21D9E4;
M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(ColF50*, ColF50, f32);
s32 func_8A202F50(u8 arg0) {
    ColF50 sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_8A203428;
    if (n >= 8) {
        D_8A20342C = 1;
    }
    if (D_8A20342C != 0) {
        n--;
        D_8A203428_2 = n;
    }
    func_800069CC();
    if (D_8A21DE08 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8A21DE10;
    }
    func_80028060(0, var_a1, &D_8A21D9E4, D_8A21DE08);
    n = D_8A203428;
    func_8002C8D8(&sp2C, *(ColF50*)&D_8A203300, n / (f64)8.0f);
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_8A20342C == 0) {
        n = D_8A203428;
        n++;
        D_8A203428 = n;
    }
    return 0;
}

void func_8A203070(s32 arg0) {
    func_8000B1FC();
    func_8000B220();
    func_8001B5F0();
    func_800158C0();
    func_8A20261C(&D_8A21DA80);
    func_8A20291C(&D_8A21DA80);
}

s32 func_8A2030C0(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {
    s32 i;

    main_pool_push_state('VIEW');
    Font_Init(0x1C, 0);
    D_8A21DA54 = BinArchive_Open(D_003DCB60, D_003F53C0, 1, 1);
    D_8A21DA48 = (ModelLoadContext*)PokeIcon_AllocFramebuffers(1);
    D_8A21DA4C = (s32)PokeIcon_CreateModelPreview(D_8A21DA48, 0x100, 0xD2, 0, 0, 0xF4, 0xD2, D_8A203438);
    D_8A21DA50 = (s8*)PokeIcon_CreateRenderList(D_8A21DA48, 6, 0x28, 0x28);
    PokeIcon_OpenModelArchives();

    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);

    D_8A21DA58 = main_pool_alloc(0x3000, 0);
    for (i = 0; i < 4; i++) {
        D_8A21DA60[i] = main_pool_alloc(0x14800, 0);
    }

    BattlePrep_RenderFrame();
    StageLoader_UpdateSegments();
    BgStage_RunUntilCondition(8, func_8A202F50);
    BgStage_RunUntilCondition(0, (s32 (*)(u8))func_8A203070);
    BgStage_RunUntilCondition(8, func_8A202F50);
    StageLoader_WaitForRetrace();
    Font_Free();
    main_pool_pop_state('VIEW');
    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
