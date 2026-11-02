/* Stadium Zero fragment017_261F00. */

#include "global.h"
#include "m2c_macros.h"

M2C_UNK func_8001A944(s32, s32, s32);               /* extern */
M2C_UNK func_8001AA9C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern s32 D_8A0005F0;

void func_8A000020(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == D_8A0005F0) {
        func_8001AA9C(0xFF, 0xFF, 0, 0xFF);
    }
    func_8001A944(arg1, arg2, arg3);
    if (arg0 == D_8A0005F0) {
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    }
}

M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001AAE4(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
M2C_UNK func_8001ABE8();                            /* extern */
M2C_UNK func_8001AC3C();                            /* extern */
M2C_UNK func_8001CC90(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8001E6C0(M2C_UNK, s32);                /* extern */
extern s32 D_8A0005F0;
extern M2C_UNK D_8A000600;
extern M2C_UNK D_8A000610;
extern M2C_UNK D_8A000618;
extern M2C_UNK D_8A000624;
extern M2C_UNK D_8A00062C;
extern M2C_UNK D_8A000634;
extern M2C_UNK D_8A000640;

s32 func_8A00009C(s32 arg0) {
    func_800069CC();
    func_8001CC90(0, 0x1E0, 0x32, 0x64, 0xA2);
    func_8001E6C0(0xA0, (D_8A0005F0 * 0x1E) + 0xC8);
    func_8001AB6C();
    func_8001A384(0x20, 0);
    func_8001ABE8();
    func_8001AAE4(0xFF, 0x6B, 0x5A, 0xFF);
    func_8001A944(0xB4, 0x28, &D_8A000600);
    func_8001AC3C();
    func_8001A384(0x10, 0);
    func_8A000020(0, 0xC8, 0xC8, &D_8A000610);
    func_8A000020(1, 0xC8, 0xE6, &D_8A000618);
    func_8A000020(2, 0xC8, 0x104, &D_8A000624);
    func_8A000020(3, 0xC8, 0x122, &D_8A00062C);
    func_8A000020(4, 0xC8, 0x140, &D_8A000634);
    func_8A000020(5, 0xC8, 0x15E, &D_8A000640);
    func_8001ABBC();
    return 0;
}

s32 func_8000B30C();
void func_8003F6AC(s32);
extern s32 D_8A0005F0;

/*
 * func_8A0001F0
 *
 * Moves a selection index, D_8A0005F0, within 0..5. func_8000B30C() supplies
 * a value (read here as a button mask; not confirmed): 0x400 calls
 * func_8003F6AC(1) and increments the index, wrapping 6 to 0; 0x800 calls
 * func_8003F6AC(1) and decrements it, wrapping -1 to 5; any other value does
 * nothing.
 * Matching note: the empty `if (!D_8A0005F0) {}` before the first call has no
 * effect on behaviour. It was found with decomp-permuter and is the only form
 * tried that gives the ROM's register for the address of D_8A0005F0 (v1
 * instead of v0). Same kind of workaround as in func_81200A20.
 */
void func_8A0001F0(void) {
    s32 btn;

    if (!D_8A0005F0) {
    }
    btn = func_8000B30C();
    if (btn != 0x400) {
        if (btn == 0x800) {
            func_8003F6AC(1);
            D_8A0005F0 -= 1;
            if (D_8A0005F0 < 0) {
                D_8A0005F0 = 5;
            }
        }
    } else {
        func_8003F6AC(1);
        D_8A0005F0 += 1;
        if (D_8A0005F0 >= 6) {
            D_8A0005F0 = 0;
        }
    }
}

M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32); /* extern */
extern s8 D_00235D70;
extern s8 D_00238BD0;
extern s8 D_00262620;
extern s8 D_00293410;
extern s8 D_002B1360;
extern s8 D_88000000;
extern s8 D_8A100000;
extern s8 D_8A200000;
void func_8A000278(void) {
    switch (D_8A0005F0) {
    case 0:
        func_80025BA0(((u32) ((s32) &D_8A100000 & 0x0FF00000) >> 0x14) - 0x10, &D_00262620, &D_00293410, 0, 0);
        return;
    case 1:
        func_80025BA0(((u32) ((s32) &D_8A200000 & 0x0FF00000) >> 0x14) - 0x10, &D_00293410, &D_002B1360, 1, 0);
        return;
    case 2:
        func_80025BA0(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
        return;
    case 3:
        func_80025BA0(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
        return;
    case 4:
        func_80025BA0(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
        return;
    case 5:
        func_80025BA0(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
        /* fallthrough */
    default:
        return;
    }
}

extern s32 D_800603C0;
void func_8000B1FC(void);
void func_8000B220(void);
void func_8001B5F0(void);
void func_80005B98(s32);
void func_8003F6AC(s32);
void func_8A0001F0(void);
s32 func_8A000418(s32 arg0) {
    s32 ret = 0;

    func_8000B1FC();
    func_8000B220();
    func_8001B5F0();
    if (arg0 == 1) {
        func_80005B98(8);
    } else if (arg0 == 0) {
        if (M2C_FIELD(D_800603C0, u16*, 8) & 0x8000) {
            func_8003F6AC(2);
            func_8A000278();
            ret = 0x8000;
        } else if (M2C_FIELD(D_800603C0, u16*, 8) & 0x4000) {
            func_8003F6AC(3);
            func_80025BA0(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
            ret = 0x8000;
        } else {
            func_8A0001F0();
        }
    }
    func_8A00009C(arg0);
    return ret;
}

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_80006724();                            /* extern */
M2C_UNK func_8000675C();                            /* extern */
M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_8000A7B0(M2C_UNK);                     /* extern */
M2C_UNK func_8000B2F4(s32);                         /* extern */
M2C_UNK func_8001A194(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A360();                            /* extern */
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_002F0A50;
extern M2C_UNK D_002F3BD0;
extern M2C_UNK D_01000000;
extern M2C_UNK D_02000000;
extern s32 D_800603C0;
s32 func_8A000418(s32);

s32 func_8A000514(s32 arg0, M2C_UNK arg1) {
    func_8000256C(0x424D4E55);
    func_8001A194(0x30, 0);
    func_80003EB8((u32) ((s32) &D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_80003EB8((u32) ((s32) &D_02000000 & 0x0F000000) >> 0x18, &D_002F0A50, &D_002F3BD0, 0);
    func_8000B2F4(D_800603C0);
    func_8000A7B0(2);
    func_8000675C();
    func_80006828(0, &func_8A000418);
    func_80006724();
    func_8001A360();
    func_80002620(0x424D4E55);
    return 0x8040;
}
