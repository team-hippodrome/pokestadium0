/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "m2c_macros.h"

extern u8* D_821CF29C;
extern s8* D_821CF2A0;
s32 func_82185220(u8 *arg0, u8 *arg1, s32 arg2);
s32 func_8218540C(s8 *arg0, s8 *arg1);
s32 func_82184BC8(s8 *arg0, s32 arg1);
s32 func_82184DC8(s8 *, s8 *, u8);

s32 func_82188050(s32 arg0) {
    s32 i;
    s32 tier;
    s32 best;
    s32 threshold;
    s32 v;
    u8 move;

    if (arg0 >= 0 && arg0 < 4 && func_82185220((u8*)D_821CF2A0, D_821CF29C, 0) < M2C_FIELD(D_821CF29C, u16*, 0x18) && (D_821CF29C + arg0)[0x2B] == 0x3F) {
        threshold = M2C_FIELD(D_821CF2A0, u16*, 0x18) - func_82184DC8((s8*)D_821CF29C + 0xC, D_821CF2A0 + 0xC, 0x3F) * 9 / 10;
        best = -1;
        if (threshold > 0) {
            for (tier = 0; tier < 4; tier++) {
                for (i = 0; i < 4; i++) {
                    if ((D_821CF29C + i)[0x2B] == 0) {
                        break;
                    }
                    if (func_8218540C((s8*)D_821CF29C, D_821CF2A0) != 0 || (D_821CF29C + i)[0x2B] == 0x62) {
                        move = (D_821CF29C + i)[0x2B];
                        switch (move) {
                            case 0x14:
                            case 0x15:
                            case 0x19:
                            case 0x38:
                            case 0x42:
                            case 0x79:
                            case 0x80:
                            case 0x9A:
                                if (tier < 3) {
                                    break;
                                }
                            case 0x03:
                            case 0x04:
                            case 0x05:
                            case 0x1B:
                            case 0x1F:
                            case 0x23:
                            case 0x24:
                            case 0x2A:
                            case 0x31:
                            case 0x3B:
                            case 0x43:
                            case 0x7D:
                            case 0x7E:
                            case 0x88:
                            case 0x8C:
                            case 0x98:
                            case 0x9B:
                            case 0x9D:
                            case 0x9E:
                            case 0xA2:
                                if (tier < 2) {
                                    break;
                                }
                            case 0x0F:
                            case 0x13:
                            case 0x1A:
                            case 0x21:
                            case 0x4B:
                                if (tier < 1) {
                                    break;
                                }
                            case 0x01:
                            case 0x02:
                            case 0x06:
                            case 0x07:
                            case 0x08:
                            case 0x09:
                            case 0x0A:
                            case 0x0B:
                            case 0x10:
                            case 0x11:
                            case 0x16:
                            case 0x17:
                            case 0x18:
                            case 0x1D:
                            case 0x1E:
                            case 0x22:
                            case 0x26:
                            case 0x28:
                            case 0x29:
                            case 0x2C:
                            case 0x33:
                            case 0x34:
                            case 0x35:
                            case 0x37:
                            case 0x39:
                            case 0x3A:
                            case 0x3C:
                            case 0x3D:
                            case 0x3E:
                            case 0x40:
                            case 0x41:
                            case 0x45:
                            case 0x46:
                            case 0x47:
                            case 0x48:
                            case 0x52:
                            case 0x54:
                            case 0x55:
                            case 0x59:
                            case 0x5B:
                            case 0x5D:
                            case 0x5E:
                            case 0x62:
                            case 0x65:
                            case 0x7A:
                            case 0x7C:
                            case 0x7F:
                            case 0x81:
                            case 0x83:
                            case 0x84:
                            case 0x8D:
                            case 0x91:
                            case 0x92:
                            case 0xA1:
                            case 0xA3:
                                v = func_82184DC8((s8*)D_821CF29C + 0xC, D_821CF2A0 + 0xC, move) * 9 / 10;
                                if (best < v && threshold < v) {
                                    best = v;
                                    arg0 = i;
                                }
                                break;
                        }
                    }
                }
            }
        }
    }
    return arg0;
}

s32 func_8218824C(s32 arg0) {
    s32 i;
    s32 best = -1;
    s32 bestIdx = -1;
    s32 v;

    for (i = 0; i < 4; i++) {
        if ((D_821CF29C + i)[0x2B] == 0) {
            break;
        }
        if (func_82184BC8((s8*)D_821CF29C, (D_821CF29C + i)[0x2B]) != 0) {
            v = func_82184DC8((s8*)D_821CF29C + 0xC, D_821CF2A0 + 0xC, (D_821CF29C + i)[0x2B]);
            if (best < v) {
                best = v;
                bestIdx = i;
            }
        }
    }
    best = best * 9 / 10;
    if ((M2C_FIELD(D_821CF2A0, u16 *, 0x18) != 0) && (arg0 < (best * 100) / M2C_FIELD(D_821CF2A0, u16 *, 0x18))) {
        return bestIdx;
    }
    return -1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82188394; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82188394.s")
#endif


/**
 * Searches for another entry that matches entry arg0 in the per-entry byte tables
 * addressed through D_821CF29C (the byte at +0x2B + index and the byte at +0x3E + index,
 * index 0..3). If the +0x3E byte of arg0 has any of the bits 0x3F set, returns arg0.
 * Otherwise scans indices 0..3 in order: stops and returns arg0 at the first index
 * whose +0x2B byte is zero; skips index arg0; and returns the first other index whose
 * +0x2B byte equals that of arg0 and whose +0x3E byte has any of bits 0x3F set.
 * Returns arg0 when no such index is found. What the tables mean is not established.
 */
s32 func_821886F0(s32 arg0) {
    s32 i;
    u8* base;
    u8* cur;
    u8* me;
    u8 v;

    base = D_821CF29C;
    me = base + arg0;
    i = 0;
    if (!(me[0x3E] & 0x3F)) {
        cur = base;
        do {
            v = cur[0x2B];
            if (v == 0) {
                break;
            }
            if ((i != arg0) && (v != 0) && (v == me[0x2B]) && (cur[0x3E] & 0x3F)) {
                return i;
            }
            i++;
            cur++;
        } while (i != 4);
    }
    return arg0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82188770; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82188770.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82188B8C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82188B8C.s")
#endif
