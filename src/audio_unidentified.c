/* Stadium Zero resident code. */

#include "global.h"

/**
 * Handwritten Yay0 decoder (src, dst): the header at src holds the decoded size (+0x4), the offset of the
 * back-reference table (+0x8) and of the literal bytes (+0xC); 32-bit control words follow at +0x10, one
 * bit per step, set for a literal byte and clear for a back-reference. Called by
 * Audio_CopyDataWithCacheSync.
 */
#ifdef NON_MATCHING
/* TODO: decompile func_80048010; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80048010.s")
#endif
