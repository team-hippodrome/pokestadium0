/* Fixed-layout split (from func_82004CE0); original translation-unit boundaries remain unconfirmed. */

#include "global.h"
#include "m2c_macros.h"


void func_82004518(s32, s32, s32);

void func_800069CC(void);
M2C_UNK func_8002C064(M2C_UNK, M2C_UNK, u8, u8, s32);
extern u8 D_82008F50[];
void func_8200752C(s8*);
void func_82005EE4(s8*, s32);
void func_82006348(s8*, s32);
void func_82007D94(s8*, s32);
void func_82006810(s8*);
void func_82006DF8(s8*);
void func_82007AF4(s8*, s32);
void func_8200339C(s8*);
void func_8002D2BC(s8*);
M2C_UNK func_82004CE0(s32 arg0) {
    s8* base = (s8*)arg0;

    func_800069CC();
    func_8002C064(0x38, 0x1E0, D_82008F50[0], D_82008F50[1], D_82008F50[2]);
    switch (*(s32*)base) {
        case 1:
            func_8200752C(base + 0x4378);
            break;
        case 2:
        case 3:
            func_82005EE4(base + 0x43E4, 2);
            break;
        case 4:
            func_82005EE4(base + 0x43E4, 0x10);
            func_82005EE4(base + 0x4468, 2);
            break;
        case 12:
            func_82006348(base + 0x4E50, 2);
            break;
        case 13:
            func_82006348(base + 0x4E50, 0x10);
            func_82006348(base + 0x4EAC, 0);
            break;
        case 14:
            func_82007D94(base + 0x4F30, 0);
            break;
        case 5:
            func_82005EE4(base + 0x43E4, 0x10);
            func_82005EE4(base + 0x4468, 0x10);
            func_82006810(base + 0x4554);
            break;
        case 6:
            func_82005EE4(base + 0x43E4, 0x10);
            func_82005EE4(base + 0x4468, 0x10);
            func_82006DF8(base + 0x45C8);
            break;
        case 7:
        case 8:
            func_82005EE4(base + 0x43E4, 0x10);
            func_82005EE4(base + 0x4468, 2);
            break;
        case 9:
            func_82005EE4(base + 0x43E4, 0x10);
            func_82005EE4(base + 0x4468, 0x10);
            func_82007AF4(base + 0x44EC, 2);
            break;
        case 10:
            func_8200339C(base + 0x4690);
            break;
        case 11:
            func_8200339C(base + 0x4690);
            func_8002D2BC(base + 0x4E1C);
            break;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_82004E9C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82004E9C.s")
#endif

/*
 * func_8200569C
 *
 * Writes two words in the structure `arg0` points to, derived from the
 * bytes D_800AE8F0[0] and D_800AE8F0[1] of the session context, and then
 * calls func_82004518(arg0, 2, 0) or func_82004518(arg0, 3, 0).
 *
 *   D_800AE8F0[0] == 0:
 *     arg0->0x43AC = 0
 *     arg0->0x4418 = 0 if D_800AE8F0[1] == 0, else 1 if it is 2, else 2
 *     func_82004518(arg0, 2, 0)
 *   otherwise:
 *     arg0->0x43AC = 1
 *     arg0->0x4418 = 0 if D_800AE8F0[0] == 2, else 1
 *     func_82004518(arg0, 3, 0)
 *
 * func_82004518 is still assembly, so what the 2 / 3 select is not
 * established.  The first argument of every call is `arg0` itself; the ROM
 * never writes $a0 before the call, so it is the caller's argument passed
 * through.
 */
extern s8 D_800AE8F0;

void func_8200569C(s32 arg0) {
    s32 var_v0;

    if (D_800AE8F0 == 0) {
        M2C_FIELD((void*)arg0, s32 *, 0x43AC) = 0;
        if (((s8*)&D_800AE8F0)[1] == 0) {
            M2C_FIELD((void*)arg0, s32 *, 0x4418) = 0;
        } else {
            if (((s8*)&D_800AE8F0)[1] == 2) {
                var_v0 = 1;
            } else {
                var_v0 = 2;
            }
            M2C_FIELD((void*)arg0, s32 *, 0x4418) = var_v0;
        }
        func_82004518(arg0, 2, 0);
        return;
    }
    M2C_FIELD((void*)arg0, s32 *, 0x43AC) = 1;
    if (D_800AE8F0 == 2) {
        M2C_FIELD((void*)arg0, s32 *, 0x4418) = 0;
    } else {
        M2C_FIELD((void*)arg0, s32 *, 0x4418) = 1;
    }
    func_82004518(arg0, 3, 0);
}

extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;
s32 func_80025BD8(void);
void func_80027FF8(void*, s32);
s32 func_80002D98(s32);
void func_8200573C(void) {
    D_8200AD2C = func_80025BD8();
    if (D_8200AD2C != -1) {
        func_80027FF8(&D_8200AD30, D_8200AD2C);
    }
    D_8200AD28 = func_80002D98(0x5020);
    func_82004B0C(D_8200AD28);
}

typedef struct Col8200579C { u8 r, g, b, a; } Col8200579C;
extern s32 D_820090D4;
extern s32 D_820090D8;
/*
 * Second name for D_820090D4. The fade-out store in this function family
 * (also func_8200579C, func_8900429C, func_891049E8, func_8A101B30) does not
 * share the counter's address with the load before it, which only happens
 * when the two accesses name different symbols.
 */
extern s32 D_820090D4_2;
extern M2C_UNK D_82009E10;
M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_800069CC(void);
M2C_UNK func_8002C064(M2C_UNK, M2C_UNK, u8, u8, s32);
void func_8002C8D8(Col8200579C*, Col8200579C, f32);
s32 func_8200579C(s32 arg0) {
    Col8200579C sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_820090D4;
    if (n >= 8) {
        D_820090D8 = 1;
    }
    if (D_820090D8 != 0) {
        n--;
        D_820090D4_2 = n;
    }
    func_800069CC();
    if (D_8200AD2C == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8200AD30;
    }
    func_80028060(0, var_a1, &D_82009E10, D_8200AD2C);
    n = D_820090D4;
    func_8002C8D8(&sp2C, *(Col8200579C*)&D_82008F50, n / (f64)8.0f);
    func_8002C064(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_820090D8 == 0) {
        n = D_820090D4;
        n++;
        D_820090D4 = n;
    }
    return 0;
}

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_82004CE0(s32);                         /* extern */
M2C_UNK func_82004E9C(s32);                         /* extern */
extern s32 D_8200AD28;

void func_820058BC(s32 arg0) {
    func_8000B1FC();
    func_8000B220();
    func_82004CE0(D_8200AD28);
    func_82004E9C(D_8200AD28);
}

M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK func_82004CE0(s32);                         /* extern */
extern M2C_UNK D_82009E18;
extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;

s32 func_820058FC(s32 arg0) {
    M2C_UNK *var_a1;

    func_82004CE0(D_8200AD28);
    if (D_8200AD2C == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8200AD30;
    }
    func_80028060(0, var_a1, &D_82009E18, D_8200AD2C);
    return 0;
}

M2C_UNK func_80002DC0(s32);                         /* extern */
extern s32 D_8200AD28;

void func_82005958(void) {
    func_80002DC0(D_8200AD28);
}

extern s32 D_8200AD08[8];
extern s32 D_8200AC40;
extern s32 D_820090DC[8];
s32 func_800044AC(s32, s32);

void func_8200597C(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_8200AD08[i] = func_800044AC(D_8200AC40, D_820090DC[i]);
    }
}

void func_8001A194(s32, s32);
s32 func_80017860(s32);
u16* func_80018F2C(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80017FDC(s32, s32, s32, s32);
s32 func_80004154(u8*, u8*, s32, s32);
void func_80017934(void);
void func_800040B4(s32, u8*, u8*);
void func_80003EB8(s32, u8*, u8*, s32);
s32 func_80001B10(u8*);
void func_8200569C(s32);
void func_80005B98(s32);
void func_80006828(s32, void*);
void func_8000A7B0(s32);
void func_80006998(s32);
void func_8000A7FC(s32);
void func_80006724(void);
void func_8000675C(void);
s32 func_8200579C(s32);
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_0A000000[];
extern u8 D_0A000C80[];
extern u8 D_0A0016D0[];
extern u8 D_003FFD60[];
extern u8 D_00400F70[];
extern u8 D_04000000[];
extern u8 D_004076E0[];
extern u8 D_05000000[];
extern u8 D_004199E0[];
extern u8 D_0042C4A0[];
extern u8 D_002F5940[];
extern u8 D_003139C0[];
extern s32 D_8200AC44;
extern u16* D_8200AC48;
extern s32 D_8200AC4C;
extern s32 D_8200AC50;
extern s32 D_8200ACFC;
extern s32 D_8200AD00;
extern s32 D_8200AD04;
extern s32 D_8200AD28;
extern s8 D_800AE8F0;
extern s32 D_82008F84;
M2C_UNK func_820059EC(void) {
    func_8001A194(0x3C, 0);
    D_8200AC44 = func_80017860(1);
    D_8200AC48 = func_80018F2C(D_8200AC44, 0x80, 0x78, 0, 0, 0x78, 0x78, 0);
    *D_8200AC48 &= ~2;
    *D_8200AC48 &= ~4;
    D_8200AC4C = 0;
    D_8200AC50 = func_80017FDC(D_8200AC44, 0x28, 0x28, 0x28);
    D_8200AC40 = func_80004154(D_002F5940, D_003139C0, 1, 1);
    func_80017934();

    func_800040B4(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    func_80003EB8(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    func_80003EB8(((u32)D_0A000000 & 0x0F000000) >> 0x18, D_003FFD60, D_00400F70, 0);
    func_80003EB8(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);
    func_80003EB8(((u32)D_05000000 & 0x0F000000) >> 0x18, D_004199E0, D_0042C4A0, 0);

    D_8200ACFC = func_80001B10(D_0A000000);
    D_8200AD00 = func_80001B10(D_0A000C80);
    D_8200AD04 = func_80001B10(D_0A0016D0);
    func_8200597C();
    func_8200573C();
    func_8000675C();

    if (M2C_FIELD(&D_800AE8F0, u16*, 0x1096) & 0x100) {
        M2C_FIELD(&D_800AE8F0, u16*, 0x1096) &= ~0x100;
        func_8200569C(D_8200AD28);
        func_80005B98(0xF);
        func_80006828(0x11, func_820058FC);
        func_8000A7B0(9);
    } else {
        func_80006828(8, func_8200579C);
    }
    func_80006828(0, func_820058BC);

    if (D_82008F84 == 0x8050) {
        func_80006998(0xFFFF);
        func_80005B98(0xF);
        func_80006828(0x11, func_820058FC);
        func_8000A7FC(0xF);
    } else {
        func_80006828(8, func_8200579C);
    }
    func_80006724();
    func_82005958();
}

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32); /* extern */
M2C_UNK func_820059EC();                            /* extern */
M2C_UNK func_82008F14();                            /* extern */
extern s8 D_00235D70;
extern s8 D_00238BD0;
extern s8 D_800AE8F0;
extern s32 D_82008F84;
extern s8* D_8200ACF8;
extern s8 D_88000000;
s32 func_82005CCC(s32 arg0, M2C_UNK arg1)
{
  s32 temp_v1;
  func_8000256C(0x4D454E54);
  D_8200ACF8 = &D_800AE8F0;
  if (arg0 == 1)
  {
    func_82008F14();
  }
  else
  {
    func_820059EC();
  }
  func_80002620(0x4D454E54);
  temp_v1 = D_82008F84;
  if (temp_v1 == 0x8040)
  {
    func_80025BA0((((u32) (((s32) (&D_88000000)) & 0x0FF00000)) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
  }
  return D_82008F84;
}
