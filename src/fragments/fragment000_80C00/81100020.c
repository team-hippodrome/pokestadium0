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
    if (i) {
    }
    p = arg0 + 0x786;
    for (i = 0; i != 5; i++) {
        func_81103C40(p, func_81100284(i), 0, 0x10, 0xC);
        p += 0x24;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_81100390; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81100390.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_811008DC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811008DC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81100C84; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81100C84.s")
#endif
