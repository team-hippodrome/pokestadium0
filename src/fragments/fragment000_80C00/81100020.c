/* Stadium Zero fragment000_80C00. */

#include "global.h"

#ifdef NON_MATCHING
/* TODO: decompile func_81100020; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81100020.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811000DC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811000DC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81100284; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81100284.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_81100818; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81100818.s")
#endif

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
