/* Stadium Zero resident code. */
/* Split from audio_commands.c: the code after the jump tables of func_800407B0. */

#include "audio_commands.h"
#include "audio_commands_category2.h"
#include "audio_commands.h"
#include "3D140.h"
#include "libnumus/player.h"
#include "rom_device.h"
#include "audio_channel.h"
#include "audio_cache.h"
#include "cry.h"
#include "audio_fade.h"
#include "m2c_macros.h"

extern u8 D_80077528;
extern u8 D_80077534;
extern s32 D_80077064[][2];
extern s32 D_800FD670[];
extern s32 D_800FD680;
extern u8 D_800FD605;
extern s32* D_800B417C;
extern s32* D_800B4160;
extern u8* D_800B41F0;
extern s32 D_800B41D0[];
extern s32 D_800B4198;
s32 func_80037B7C(s32);
s32 func_80037AC4(s32, s32);
void func_8004609C(u32, u8*, s32);
void func_80047FB0(u8*, s32, s32);
void func_8003A710(s32);
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);

// FAKE: callers pass four arguments. `hi` has to be a u8 that owns no stack slot
// (a u8 local matches every instruction but shifts two spill slots by 4), and a
// fifth parameter is the only form found that does that.
s32 func_800414B0(u8 arg0, u32 arg1, u32 arg2, u32 arg3, u8 hi) {
    u32 addr;
    s32 size;
    s32 flags;
    u8* entry;

    if (D_80077528 != 0) {
        return 0;
    }
    if (D_80077534 != 0) {
        return 0;
    }
    if (arg1 >= 0xA6U) {
        return 0;
    }
    if (arg2 == 0x84 || arg2 == 0x5E) {
        return 0;
    }
    D_80077534 = 0x14;
    if (arg2 >= 0x98U) {
        return 0;
    }
    hi = (arg3 & 0xFF00) >> 8;
    arg3 &= 0xFF;
    if ((arg3 == 0xA || arg3 == 0xB) && (hi == 0x10 || hi == 0x20)) {
        return 0;
    }
    if (arg0 >= 2) {
        return 0;
    }
    if (D_80077064[arg2][0] == 0) {
        return 0;
    } else {
        entry = (u8*)D_80077064[arg2][0];
    }
    if (func_80037B7C(D_800FD670[arg0])) {
        func_80037AC4(D_800FD670[arg0], 0xA);
        D_800FD670[arg0] = 0;
    }
    if (arg3 == 1 || arg3 == 5) {
        for (flags = 0; flags < 4; flags++) {
            func_80037AC4(D_800FD670[flags], 0xA);
            D_800FD670[flags] = 0;
        }
    }
    switch (arg3) {
    case 11:
        if (func_80037B7C(D_800FD670[arg0 ^ 1])) {
            func_80037AC4(D_800FD670[arg0 ^ 1], 0xA);
            D_800FD670[arg0 ^ 1] = 0;
        }
        flags = (entry[0] & 0xF0) >> 4;
        break;
    case 0:
    case 2:
    case 3:
        flags = (entry[arg1] & 0xF0) >> 4;
        break;
    case 4:
        flags = (entry[arg1] & 0xE) >> 1;
        break;
    case 1:
        flags = entry[arg1] & 1;
        break;
    default:
        return 0;
    }
    if (flags == 0) {
        return 0;
    }
    D_800FD605++;
    D_800FD605 %= 5;
    arg2--;
    if (arg2 < (u32)(D_800B417C[0] - 1)) {
        addr = D_800B417C[arg2 + 3];
        size = D_800B417C[arg2 + 4] - addr;
    } else {
        addr = D_800B417C[arg2 + 3];
        size = D_800B4160[8] - addr;
    }
    func_8004609C(addr, D_800B41F0, size);
    func_80047FB0(D_800B41F0, D_800B41D0[D_800FD605], 0x200);
    func_8003A710(D_800B41D0[D_800FD605]);
    return (D_800FD670[arg0] = func_8003834C(D_800B4198, D_800B41D0[D_800FD605], flags, 0x80, 0x80, 0, -1));
}

M2C_UNK func_8003834C(s32, s32, s32, M2C_UNK, s32, s32, s32); /* extern */
extern s32 D_800B418C;
extern s32 D_800B41A8;

void func_80041834(s32 arg0) {
    func_8003834C(D_800B418C, D_800B41A8, arg0, 0x80, 0x80, 0, -1);
}

/*
 * func_8004187C
 *
 * Bounds-checked lookup into the array of two words at D_800FD698.
 * Returns the entry for index 0 or 1, and -1 for any other index
 * (the index is treated as unsigned, so negative values also give -1).
 * What the table entries mean is not known.
 */
extern s32 D_800FD698[];
s32 func_8004187C(u32 arg0) {
    if (arg0 >= 2U) {
        return -1;
    }
    return D_800FD698[arg0];
}

/*
 * func_800418A4
 *
 * Same shape as func_8004187C but reading the array of two words at
 * D_800FD6A8: index 0 or 1 returns the entry, anything else returns -1.
 */
extern s32 D_800FD6A8[];
s32 func_800418A4(u32 arg0) {
    if (arg0 >= 2U) {
        return -1;
    }
    return D_800FD6A8[arg0];
}

extern M2C_UNK D_800FD6B4;

s32 func_800418CC(u32 arg0) {
    if (arg0 >= 2) {
        return -1;
    }
    return ((u8*)&D_800FD6B4)[arg0];
}

extern u8 D_80077538;

void func_800418F0(s32 arg0) {
    if (arg0 != 0) {
        D_80077538 = 1;
        return;
    }
    D_80077538 = 0;
}

extern M2C_UNK D_800FD6B2;
extern M2C_UNK D_800FD6B4;

void func_80041914(s32 arg0, s32 arg1) {
    s8 temp_v0;
    s8 temp_v1;

    temp_v0 = arg0 * 2;
    temp_v1 = arg1 * 2;
    M2C_FIELD(&D_800FD6B2, s8 *, 0) = temp_v0;
    M2C_FIELD(&D_800FD6B4, s8 *, 0) = temp_v0;
    M2C_FIELD(&D_800FD6B2, s8 *, 1) = temp_v1;
    M2C_FIELD(&D_800FD6B4, s8 *, 1) = temp_v1;
}

extern s32 D_800FD6A0[];
extern u8 D_800FD6B0[];
extern u8 D_800FD6B6[];
extern u8 D_80077560;
void func_80041940(u32 arg0, s32 arg1, s32 arg2) {
    s32* cur;
    s32* prev;
    s32* next;

    if (arg0 < 2) {
        prev = &D_800FD6A0[arg0];
        cur = &D_800FD698[arg0];
        next = &D_800FD6A8[arg0];
        *prev = *cur;
        *cur = arg1;
        *next = arg2;
        if (arg1 == 0) {
            if (*prev == *next) {
                D_80077560 = 1;
            } else {
                D_80077560 = 0;
            }
            if (((u8*)&D_800FD6B4)[arg0] != 0) {
                ((u8*)&D_800FD6B4)[arg0]--;
            }
            D_800FD6B6[arg0]++;
            D_800FD6B0[arg0] = 1;
        }
    }
}

void func_80043CE8(s32, f32, s32);
extern u8 D_80077528;
extern u8 D_8007754C;
extern s32 D_800FD6A8[];
extern u8 D_800FD6B6[];
extern u8 D_80077540;
extern s32 D_800B4188;
extern s32 D_800B41A4;
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);
s32 func_80037B7C(s32);
s32 func_80037AC4(s32, s32);
s32 func_8004D300(s32);
u32 func_80053A80(void);
void func_800386E4(s32, s32);
extern u8 D_80077548;
extern u8 D_80077550;
extern u8 D_80077564;
extern u8 D_80077568;
extern u8 D_8007756C;
extern u8 D_80077570;
extern u8 D_80077574;
extern u8 D_80077578;
extern u8 D_8007757C;
extern u8 D_80077594;
extern s32 D_80077598;
extern u8 D_8007759C;
extern s32 D_800775A0;
extern s32 D_800775A4;
extern s32 D_800FD670[];
extern s32 D_800FD698[];
extern u8 D_800FD6B8;
extern s32 D_800FD6BC;

void func_800419F8(u32 arg0) {
    s32 d;
    s32 mask;
    s32 ratio[2];
    s32 i;

    if (arg0 != 0) {
        if ((D_80077528 == 0) && (D_8007754C == 0)) {
            mask = func_8004D300(mask); // mask is read uninitialised here, as in the original
            D_8007754C = 1;
            D_80077598 = 0;
            D_80077594 = 0;
            D_800775A4 = 0;
            D_800775A0 = 0;
            func_8004D300(mask);
            if (D_800775A4 == 0) {
                D_800775A4 = func_8003834C(D_800B4188, D_800B41A4, 0x18, 0x80, 0x80, 0, -1);
            }
            if (D_80077548 == 0) {
                return;
            }
            if (D_800FD6A8[0] == 0) {
                D_800FD698[0] = 100;
                D_800FD6A8[0] = 100;
            }
            if (D_800FD6A8[1] == 0) {
                D_800FD698[1] = 100;
                D_800FD6A8[1] = 100;
            }
            ratio[0] = (u32)(D_800FD698[0] * 100) / (u32)D_800FD6A8[0];
            ratio[1] = (u32)(D_800FD698[1] * 100) / (u32)D_800FD6A8[1];
            if (D_80077548 >= 0x15) {
                if ((D_800FD698[0] != 0) && (D_800FD698[1] != 0)) {
                    if ((u8)func_80053A80() & 1) {
                        d = (ratio[1] < ratio[0]) ? ratio[0] - ratio[1] : ratio[1] - ratio[0];
                        if (d >= 0x33) {
                            func_80043CE8(0x30, 0.0f, 0x80);
                            return;
                        }
                    }
                    if (((u8)func_80053A80() & 4) && (ratio[0] < 0x15) && (ratio[1] < 0x15)) {
                        func_80043CE8(0x2D, 0.0f, 0x80);
                        return;
                    }
                    if (((u8)func_80053A80() & 8) && (ratio[0] >= 0x3D) && (ratio[1] >= 0x3D) && (ratio[0] < 100) && (ratio[1] < 100)) {
                        d = (ratio[1] < ratio[0]) ? ratio[0] - ratio[1] : ratio[1] - ratio[0];
                        if (d < 0xA) {
                            func_80043CE8(0x57, 0.0f, 0x80);
                            return;
                        }
                        func_80043CE8(0x2C, 0.0f, 0x80);
                        return;
                    }
                    if ((u8)func_80053A80() & 2) {
                        d = (((u8*)&D_800FD6B4)[1] < ((u8*)&D_800FD6B4)[0]) ? ((u8*)&D_800FD6B4)[0] - ((u8*)&D_800FD6B4)[1] : ((u8*)&D_800FD6B4)[1] - ((u8*)&D_800FD6B4)[0];
                        if ((d >= 4) && (((u8*)&D_800FD6B2)[0] >= 3) && (((u8*)&D_800FD6B2)[1] >= 3)) {
                            func_80043CE8(0x58, 0.0f, 0x80);
                            return;
                        }
                        if ((((u8*)&D_800FD6B4)[0] < 3) && (((u8*)&D_800FD6B4)[1] < 3) && (((u8*)&D_800FD6B2)[0] >= 3) && (((u8*)&D_800FD6B2)[1] >= 3)) {
                            func_80043CE8(0x5A, 0.0f, 0x80);
                            return;
                        }
                        if (D_80077578 != 1) {
                            func_80043CE8(0x34, 0.0f, 0x80);
                            D_80077578 = 1;
                            return;
                        }
                        func_80043CE8(0x5D, 0.0f, 0x80);
                        D_80077578 = 2;
                        return;
                    }
                    if (((u8)func_80053A80() & 2) && (D_80077578 != 1)) {
                        func_80043CE8(0x34, 0.0f, 0x80);
                        D_80077578 = 1;
                        return;
                    }
                    if (((u8)func_80053A80() & 1) && (D_80077578 != 2)) {
                        func_80043CE8(0x5D, 0.0f, 0x80);
                        D_80077578 = 2;
                        return;
                    }
                    func_80043CE8(0x35, 0.0f, 0x80);
                    D_80077578 = 0;
                    return;
                }
                if ((((u8*)&D_800FD6B4)[0] < 3) && (((u8*)&D_800FD6B4)[1] < 3) && (D_80077540 == 8)) {
                    func_80043CE8(0x6C, 0.0f, 0x80);
                } else if (D_80077578 != 1) {
                    func_80043CE8(0x34, 0.0f, 0x80);
                    D_80077578 = 1;
                } else {
                    func_80043CE8(0x5D, 0.0f, 0x80);
                    D_80077578 = 2;
                }
                mask = func_8004D300(1);
                D_80077598 = 0x320;
                D_8007759C = 1;
                func_8004D300(mask);
                return;
            }
            if (D_80077548 >= 4) {
                if ((D_800FD698[0] != 0) && (D_800FD698[1] != 0)) {
                    if ((u8)func_80053A80() & 1) {
                        d = (ratio[1] < ratio[0]) ? ratio[0] - ratio[1] : ratio[1] - ratio[0];
                        if (d >= 0x33) {
                            func_80043CE8(0x30, 0.0f, 0x80);
                            return;
                        }
                    }
                    if (((u8)func_80053A80() & 4) && (ratio[0] < 0x15) && (ratio[1] < 0x15)) {
                        func_80043CE8(0x2D, 0.0f, 0x80);
                        return;
                    }
                    if (((u8)func_80053A80() & 8) && (ratio[0] >= 0x51) && (ratio[1] >= 0x51) && (ratio[0] < 100) && (ratio[1] < 100)) {
                        if ((D_800FD6B6[0] == 0) && (D_800FD6B6[1] == 0)) {
                            func_80043CE8(0x5E, 0.0f, 0x80);
                            return;
                        }
                        func_80043CE8(0x2C, 0.0f, 0x80);
                        return;
                    }
                    if ((u8)func_80053A80() & 2) {
                        d = (((u8*)&D_800FD6B4)[1] < ((u8*)&D_800FD6B4)[0]) ? ((u8*)&D_800FD6B4)[0] - ((u8*)&D_800FD6B4)[1] : ((u8*)&D_800FD6B4)[1] - ((u8*)&D_800FD6B4)[0];
                        if ((d >= 4) && (((u8*)&D_800FD6B2)[0] >= 3) && (((u8*)&D_800FD6B2)[1] >= 3)) {
                            func_80043CE8(0x58, 0.0f, 0x80);
                            return;
                        }
                        if ((((u8*)&D_800FD6B4)[0] < 3) && (((u8*)&D_800FD6B4)[1] < 3) && (((u8*)&D_800FD6B2)[0] >= 3) && (((u8*)&D_800FD6B2)[1] >= 3)) {
                            func_80043CE8(0x5A, 0.0f, 0x80);
                            return;
                        }
                        if (D_80077578 != 1) {
                            func_80043CE8(0x34, 0.0f, 0x80);
                            D_80077578 = 1;
                            return;
                        }
                        if ((u8)func_80053A80() & 2) {
                            func_80043CE8(0x5D, 0.0f, 0x80);
                            D_80077578 = 2;
                        }
                    } else {
                        if (((u8)func_80053A80() & 1) && (D_80077578 != 2)) {
                            func_80043CE8(0x5D, 0.0f, 0x80);
                            D_80077578 = 2;
                            return;
                        }
                        if (((u8)func_80053A80() & 2) && (D_80077578 != 1)) {
                            func_80043CE8(0x34, 0.0f, 0x80);
                            D_80077578 = 1;
                            return;
                        }
                        if ((u8)func_80053A80() & 0x40) {
                            func_80043CE8(0x35, 0.0f, 0x80);
                            D_80077578 = 0;
                        }
                    }
                } else {
                    if (D_80077578 != 1) {
                        func_80043CE8(0x34, 0.0f, 0x80);
                        D_80077578 = 1;
                    } else {
                        func_80043CE8(0x5D, 0.0f, 0x80);
                        D_80077578 = 2;
                    }
                    mask = func_8004D300(1);
                    D_80077598 = 0x320;
                    D_8007759C = 1;
                    func_8004D300(mask);
                }
            } else if ((D_800FD698[0] != 0) && (D_800FD698[1] != 0)) {
                if ((u8)func_80053A80() & 1) {
                    d = (ratio[1] < ratio[0]) ? ratio[0] - ratio[1] : ratio[1] - ratio[0];
                    if (d >= 0x33) {
                        func_80043CE8(0x30, 0.0f, 0x80);
                        return;
                    }
                }
                if (((u8)func_80053A80() & 4) && (ratio[0] < 0x15) && (ratio[1] < 0x15)) {
                    if ((u8)func_80053A80() & 1) {
                        func_80043CE8(0x2D, 0.0f, 0x80);
                        return;
                    }
                    func_80043CE8(0x59, 0.0f, 0x80);
                    return;
                }
                if ((ratio[0] >= 0x5B) && (ratio[1] >= 0x5B) && (D_800FD6B6[0] == 0) && (D_800FD6B6[1] == 0)) {
                    func_80043CE8(0x33, 0.0f, 0x80);
                }
            } else {
                func_80043CE8(0x59, 0.0f, 0x80);
                mask = func_8004D300(1);
                D_80077598 = 0x320;
                D_8007759C = 1;
                func_8004D300(mask);
            }
        }
    } else {
        mask = func_8004D300(1);
        D_8007754C = 0;
        func_8004D300(mask);
        func_80037AC4(D_800775A4, 0x78);
        func_80037AC4(D_800775A0, 0x78);
        for (i = 0; i < 4; i++) {
            if (func_80037B7C(D_800FD670[i]) != 0) {
                func_800386E4(D_800FD670[i], 0xF);
                D_800FD670[i] = 0;
            }
        }
        D_800775A4 = 0;
        D_800775A0 = 0;
        D_8007759C = 0;
        D_800FD6BC = 0;
        D_800FD6B8 = 0;
        D_80077564 = 0;
        D_80077568 = 0;
        D_8007756C = 0;
        D_80077570 = 0;
        D_80077574 = 0;
        D_8007757C = 0;
        D_80077550 = 0;
        D_80077548++;
    }
}
