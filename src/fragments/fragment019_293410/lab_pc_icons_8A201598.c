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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A201D3C.s")

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2024D0.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A20261C.s")

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A202F50.s")

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
