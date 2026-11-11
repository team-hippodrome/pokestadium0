/* Stadium Zero fragment000_80C00. */

#include "global.h"

void func_811177D0(s32);
void func_81106820(void);
void func_80052DC0(s32);
void func_81104B88(OSTime);
void func_8005C280(f32);
void func_80057470(s32);
void func_80008014(s32, s32, s32);
void func_8004FD20(s32, s32);
extern s8* D_81154C30[];
extern s32 D_81154C3C;
void func_81100020(void) {
    func_811177D0(0);
    func_81106820();
    func_80052DC0(1);
    func_81104B88(20);
    func_8005C280(1.0f);
    func_80057470(*(s32*)(D_81154C30[D_81154C3C] + 8));
    func_80008014(*(s32*)(D_81154C30[D_81154C3C] + 8), 0x140, 0x10);
    func_8004FD20(*(s32*)(D_81154C30[D_81154C3C] + 8), 0x25800);
}

extern u8 D_8111E318[];
extern s32 D_8111C4F0;
extern u8 D_8111E324[];
extern u8 D_8111E334[];
extern u8 D_8111E364[];
extern u8 D_8111E374[];
extern u8 D_8111E3A8[];
extern u8 D_8111E3CC[];
extern u8 D_8111E3E0[];
void func_81103850(s8* arg0, u8* arg1);
s32 func_81103C40(s32, s32*, s32, s32, s32);
extern s32 D_8111C568;
void func_811000DC(s8* arg0, u8 arg1) {
    s32 i;
    u8* last;

    arg0 += 0x787C;
    func_81103850(arg0, D_8111E318);
    for (i = 0; i != 0x140; i += 0x20) {
        func_81103C40((s32)(arg0 + 0xC806 + i), &D_8111C4F0, 0, 0xC, 5);
    }
    func_81103C40((s32)(arg0 + (arg1 & 3) * 0x2D00 + 0x4618), &D_8111C568, 0, 0x10, 0xA);
    D_8111E324[4] = 0xA;
    D_8111E364[4] = 0xA;
    D_8111E3CC[4] = 0xA;
    if (arg1 == 0) {
        D_8111E324[4] = 8;
        last = D_8111E334;
    } else if (arg1 == 1) {
        D_8111E364[4] = 8;
        last = D_8111E374;
    } else if (arg1 == 2) {
        D_8111E3CC[4] = 8;
        last = D_8111E3E0;
    } else if (arg1 == 5) {
        D_8111E364[4] = 8;
        last = D_8111E3A8;
    }
    func_81103850(arg0, D_8111E324);
    func_81103850(arg0, D_8111E364);
    func_81103850(arg0, D_8111E3CC);
    func_81103850(arg0, last);
}

extern s32 D_8111D0A8[];
extern s32 D_8111D228[];
extern s32 D_8111D528[];
extern s32 D_8111D6A8[];
extern s32 D_8111D828[];

s32* func_81100284(s32 arg0) {
    arg0 &= 7;
    return (arg0 == 1) ? D_8111D528 : (arg0 == 2) ? D_8111D6A8 : (arg0 == 3) ? D_8111D228 : (arg0 == 4) ? D_8111D0A8 : D_8111D828;
}

s32* func_81100284(s32);
s32 func_81103C40(s32, s32*, s32, s32, s32);
extern s32 D_8111DFA8;

/*
 * func_811002F4
 *
 * arg0 is treated as a plain address and offsets are added to it in bytes.
 * Calls func_81103C40 once with (arg0 + (arg1 & 7) * 0x24, &D_8111DFA8, 0,
 * 0x18, 0x12), then five more times with (arg0 + 0x786 + n * 0x24,
 * func_81100284(n), 0, 0x10, 0xC) for n = 0..4. What func_81103C40 and
 * func_81100284 do, and what arg0 points to, is not established from this
 * function.
 *
 * The empty `if (i) {}` is a matching-only construct (found with
 * decomp-permuter): the extra use of `i` makes IDO keep `arg1 & 7` in s0 and
 * reuse s0 as the loop counter, as the retail code does. Without it the mask is
 * computed in a temporary and the output differs.
 */
void func_811002F4(s32 arg0, s32 arg1) {
    s32 i;
    s32 p;

    i = arg1 & 7;
    func_81103C40(arg0 + i * 0x24, &D_8111DFA8, 0, 0x18, 0x12);
    if (i) {  // karodo
    }
    p = arg0 + 0x786;
    for (i = 0; i != 5; i++) {
        func_81103C40(p, func_81100284(i), 0, 0x10, 0xC);
        p += 0x24;
    }
}

extern u8 D_8111E308;
extern u8 D_8111E314[2];
extern s32 D_8111D3A8;
extern s32 D_8111CDA8;
extern s32 D_8111C6A8;
extern s32 D_8111C728;
extern s32 D_8111C7A8;
extern s32 D_8111C828;
extern s32 D_8111C8A8;
extern s32 D_8111C928;
extern s32 D_8111CA28;
extern s32 D_8111C9A8;
extern s32 D_8111DBE8;
extern s32 D_8111DE28;
extern s32 D_8111D9A8;
extern u8 D_8111E40C[];
extern u8 D_8111E454[];
extern u8 D_8111E47C[];
extern u8 D_8111E4A0[];
extern u8 D_8111E4AC[];
/*
 * GB Tower option screen. Draws the panel frame tiles into the framebuffer
 * (three loops), then the two cursors and the selected options.
 * Register allocation depends on reusing the same few locals: one IDO live
 * range per local, so i, j, q and r each carry several roles on purpose.
 */
void func_81100390(s32 arg0, s32 arg1, s32 arg2) {
    s32 fb;
    s32 q;
    s32 r;
    s32 i;
    s32 j;

    arg0 += 0x787C;
    fb = arg0;
    if (D_8111E308 == 0) {
        fb = arg0 - 0x4B00;
    } else {
        func_81103C40(arg0 + 0xF22, &D_8111D3A8, 0, 0x10, 0xC);
        func_81103850((s8*)arg0, D_8111E40C);
        if (D_8111E308 == 1) {
            func_81103850((s8*)arg0, D_8111E454);
        } else {
            func_81103850((s8*)arg0, D_8111E47C);
        }
    }
    func_81103850((s8*)fb, D_8111E4A0);
    func_81103850((s8*)fb, D_8111E4AC);
    func_81103C40(fb + 0x138AE, &D_8111CDA8, 0, 0x10, 0xC);
    fb += 0xBB80;
    func_81103C40(fb, &D_8111C6A8, 0, 8, 8);
    for (i = 0; i < 0x12; i++) {
        r = fb; // FAKE
        if (i == 1) {
            i = 8;
        }
        j = i * 0x10 + r + 0x10;
        r = 0; // FAKE
        func_81103C40(j, &D_8111C728, 0, 8, 8);
        j += 0x10;
    }
    func_81103C40(j, &D_8111C7A8, 0, 8, 8);
    for (j = 0, q = fb + 0x1400, r = fb + 0x1530; j < 0x7800; j += 0x1400, q += 0x1400, r += 0x1400) {
        func_81103C40(q, &D_8111C828, 0, 8, 8);
        func_81103C40(r, &D_8111C8A8, 0, 8, 8);
    }
    func_81103C40(q, &D_8111C928, 0, 8, 8);
    func_81103C40(r, &D_8111CA28, 0, 8, 8);
    for (j = 0, q = fb + 0x8C10; j != 0x120; j += 0x10, q += 0x10) {
        if (j && j && j) {} // FAKE
        func_81103C40(q, &D_8111C9A8, 0, 8, 8);
    }
    fb -= 0xBB80;
    q = 0x2D;
    r = 0x2B;
    if (arg1 & 8) {
        if (arg2 != 0) {
            r = arg2 * 6 + 0x2B;
            j = 1;
            if (arg2 == -6) {
                func_811002F4(fb + 0xFF76, arg1);
            }
        } else {
            func_81103C40(fb + 0x10BA8, &D_8111C568, 0, 0x10, 0xA);
            j = 3;
        }
    } else if (arg2 != 0) {
        q = arg2 * 6 + 0x2D;
        j = 2;
        if (arg2 == -6) {
            func_811002F4(fb + 0xCAF6, arg1);
        }
    } else {
        func_81103C40(fb + 0xD728, &D_8111C568, 0, 0x10, 0xA);
        j = 3;
    }
    i = fb + q * 2;
    q = 0; // FAKE
    func_81103C40(i + 0xD200, &D_8111DBE8, 0, 0x18, 0xC);
    func_81103C40(i + 0xD236, &D_8111DE28, 0, 0x10, 0xC);
    i = fb + r * 2;
    func_81103C40(i + 0x10680, &D_8111D9A8, 0, 0x18, 0xC);
    func_81103C40(i + 0x106BA, &D_8111DE28, 0, 0x10, 0xC);
    if (j & 1) {
        func_81103C40(fb + 0xD2C4, func_81100284(D_8111E314[0]), 0, 0x10, 0xC);
    }
    if (j & 2) {
        func_81103C40(fb + 0x10744, func_81100284(D_8111E314[1]), 0, 0x10, 0xC);
    }
}

void func_811000DC(s8* arg0, u8 arg1);
void func_81103850(s8* arg0, u8* arg1);
s32 func_81103C40(s32, s32*, s32, s32, s32);
extern u8 D_8111E4BC[];
extern s32 D_8111C568;

void func_81100818(s8* arg0, s32 arg1) {
    func_811000DC(arg0, 5);
    arg0 += 0x787C;
    D_8111E4BC[arg1 ? 4 : 0xC] = 8;
    D_8111E4BC[arg1 ? 0xC : 4] = 0xA;
    func_81103850(arg0, D_8111E4BC);
    func_81103C40((s32)&((u16*)(arg0 + 0x13B00))[arg1 ? 0xE : 0x45], &D_8111C568, 0, 0x10, 0xA);
}

extern u8 D_000DA9B0[];
extern u8 D_0015A9B0[];
extern u8 D_80077F40[];
extern u8 D_800AAFE0[];
extern u8 D_8111E308;
extern s16 D_8111E30C;
extern s16 D_8111E310;
extern u8 D_8111E314[2];
extern u8 D_8112A960[];
extern u8 D_81154B20[];
extern u8 D_81154B24[];
extern u8 D_81154B88[];
extern u8 D_81154B8C[];
extern s32 D_81154C38;
extern s32 D_81154C40;
extern s32 D_81154C44;
extern s32 D_81154C48;
extern s8 D_81154C4C;
extern s8 D_81154C4D;
extern u8 D_81154C4E;
extern s8 D_81154C4F;
extern u8 D_811565F0[];
s8* func_800051F0(s32, s32, s32, s32, s32);
s32 func_800023C4(s32, s32, u32);
void func_80003824(s32, u8*, u8*, s32);
void func_800093E0(u8*, u8*);
s32 func_80025BD8(void);
void func_800535A0(u8*);
void func_800567E0(u8*, u8*, s32);
void func_80058FB0(s32);
void func_811035B4(s32, s32, u8*);
s32 func_81104DD0(s32, s32, s32, s32, s8*);
void func_8110DF80(void);
void func_811171DC(void);
void func_81117288(s32);
void func_811008DC(s8* arg0) {

    D_81154C30[0] = func_800051F0(0, 2, 0x140, 0xF0, 1);
    D_81154C30[1] = func_800051F0(0, 2, 0x140, 0xF0, 1);
    D_81154C38 = func_800023C4((u32) D_0015A9B0 - (u32) D_000DA9B0 + 0x158000, 0, (u32) D_000DA9B0);
    if (D_81154C38 == 0) {
        D_81154C4E = 1;
        D_81154C48 = 3;
        return;
    }
    D_81154C3C = 0;
    func_8110DF80();
    func_80003824(D_81154C38, D_000DA9B0, D_0015A9B0, 0);
    func_81117288(D_81154C38);
    D_81154C38 = (D_81154C38 + (u32) D_0015A9B0) - (u32) D_000DA9B0;
    func_811171DC();
    func_800567E0(D_81154B24, D_81154B20, 1);
    func_800567E0(D_81154B8C, D_81154B88, 1);
    func_800535A0(D_80077F40);
    func_80058FB0(0x2A);
    func_80058FB0(0x80);
    func_81100020();
    func_800093E0(D_8112A960, D_811565F0);
    func_811035B4(0xC, 0x12, D_800AAFE0);
    D_8111E308 = *(u8*)(arg0 + 0x2202);
    if (D_8111E308 >= 3) {
        D_8111E308 = 0;
    }
    D_81154C4F = D_8111E308;
    switch (func_81104DD0(*(s32*)(D_81154C30[D_81154C3C] + 8), D_81154C38, 0x158000, func_80025BD8(), arg0)) {
        case 1:
        default:
            D_81154C4E = 1;
            D_81154C48 = 1;
            break;
        case 2:
            D_81154C4E = 1;
            D_81154C48 = 2;
            break;
        case 0:
            D_81154C4E = 0;
            D_81154C48 = 0;
            break;
    }
    D_81154C4C = 0;
    D_81154C4D = 0;
    D_81154C40 = 0;
    D_81154C44 = 0;
    D_8111E314[0] = ((*(s16*)(arg0 + 0x2200)) & 0xFF00) >> 8;
    D_8111E314[1] = ((*(s16*)(arg0 + 0x2200)) & 0xFF) + 1;
    if ((D_8111E314[0] >= 5) || (D_8111E314[1] >= 5) || (D_8111E314[0] == D_8111E314[1])) {
        D_8111E314[0] = 0;
        D_8111E314[1] = 1;
    }
    D_8111E30C = (D_8111E314[0] == 1) ? 0x20 : (D_8111E314[0] == 2) ? 0x10 : (D_8111E314[0] == 3) ? 2 : (D_8111E314[0] == 4) ? 4 : 0x1000;
    D_8111E310 = (D_8111E314[1] == 0) ? 0x1000 : (D_8111E314[1] == 2) ? 0x10 : (D_8111E314[1] == 3) ? 2 : (D_8111E314[1] == 4) ? 4 : 0x20;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81100C84; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81100C84.s")
#endif
