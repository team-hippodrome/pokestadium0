/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "lab_pc_icons.h"

extern s32 D_8A21DE08;
extern M2C_UNK D_8A21DE10;

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A201598.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2018E0.s")

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

s32 func_80001AA4(void);
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

void func_8A201D3C(s8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 unused;
    s32 count;
    s32 i;
    s32 handle;
    s32 move;

    func_8002A8C4(arg0, arg1, arg2, 0x228, 0x16A);
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x1001;
    M2C_FIELD(arg0, s32*, 0x34) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = arg3;
    count = func_8002D3D0((u8*)arg3);
    while (func_80001AA4() == 0) {
    }
    for (i = 0; i < count; i++) {
        handle = func_80002BA4(D_8A21DA60[i], 0x14800);
        move = func_8002D454(arg3, i);
        D_8A21DA70[i] = func_80017304(handle, D_8A21DA54, func_8001FA8C((move == -2) ? 0 : D_8006B190[move].type), D_8A21DA58, 0x3000);
    }
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_8A201EAC(s8 *arg0, s32 arg1)
{
  s32 temp_v0;
  if (((*((s32 *) (((s8 *) arg0) + 0x28))) != 2) && (func_8002AB84() == 0))
  {
    if (arg1 == 0)
    {
      func_80029864((*((s32 *) (((s8 *) arg0) + 0))) + 0xF9, *((s32 *) (((s8 *) arg0) + 4)), *((s32 *) (((s8 *) arg0) + 0xC)), &D_8007356C);
      func_80029658(*((s32 *) (((s8 *) arg0) + 0)), (*((s32 *) (((s8 *) arg0) + 4))) + 0xD7, 0x100, &D_8007356C);
      func_80029658((*((s32 *) (((s8 *) arg0) + 0))) + 0xFA, (*((s32 *) (((s8 *) arg0) + 4))) + 0x95, 0x12E, &D_8007356C);
      func_8A2009CC((*((s32 *) (((s8 *) arg0) + 0))) + 6, (*((s32 *) (((s8 *) arg0) + 4))) + 0xDE, *((s32 *) (((s8 *) arg0) + 0x2C)));
      func_8A200B78((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 6, *((s32 *) (((s8 *) arg0) + 0x2C)));
      func_8A200DE0((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 0x9C, *((s32 *) (((s8 *) arg0) + 0x2C)));
    }
    else
    {
      func_80029658(*((s32 *) (((s8 *) arg0) + 0)), (*((s32 *) (((s8 *) arg0) + 4))) + 0xD7, *((s32 *) (((s8 *) arg0) + 8)), &D_8007356C);
      func_80029864((*((s32 *) (((s8 *) arg0) + 0))) + 0xF9, *((s32 *) (((s8 *) arg0) + 4)), 0xDE, &D_8007356C);
      func_8A201394((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 6, *((s32 *) (((s8 *) arg0) + 0x2C)));
      func_8A2010C8((*((s32 *) (((s8 *) arg0) + 0))) + 6, (*((s32 *) (((s8 *) arg0) + 4))) + 0xDE, *((s32 *) (((s8 *) arg0) + 0x2C)), *((s32 *) (((s8 *) arg0) + 0x30)));
      func_8A2018E0((*((s32 *) (((s8 *) arg0) + 0))) + 0x100, (*((s32 *) (((s8 *) arg0) + 4))) + 0x54, *((s32 *) (((s8 *) arg0) + 0x2C)), *((s32 *) (((s8 *) arg0) + 0x30)));
    }
  }
  temp_v0 = *((s32 *) (((s8 *) arg0) + 0x28));
  if (((temp_v0 ^ 0) == 1) || (temp_v0 == 2))
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
    func_8002C064(0x38, 0x1E0, M2C_FIELD(&D_8A203300, u8 *, 0), M2C_FIELD(&D_8A203300, u8 *, 1), (s32) M2C_FIELD(&D_8A203300, u8 *, 2));
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

void func_8A2023F4(s32* arg0, s32 arg1) {
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
            func_8A201EAC(CTX->unk0D4, 0);
            break;
        case 5:
            if (func_8002AAC4(CTX->unk0D4) != 0) {
                func_8A202160();
            }
            func_8A201EAC(CTX->unk0D4, 1);
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A20291C.s")

void func_8A202EF4(void) {
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
    func_8002C064(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
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

    func_8A202EF4();
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
