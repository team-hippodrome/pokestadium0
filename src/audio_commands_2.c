/* Stadium Zero resident code. */
/* Split from audio_commands.c so the jump table of func_80042A6C lands at 0x8007EA3C. */


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
typedef struct unk_D_80077970 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
} unk_D_80077970;
extern u8 pad_D_800FC694[4];
extern unk_D_800FC6CC* D_800B41E4;
extern u8* D_800B41E8;
extern unk_D_800FC6D4* D_800FD688;
extern s16* D_800B41EC;
extern u32* gAudioRegions;
extern s32 pad_D_800FC70C;
extern s32 pad_D_800FC710;
extern u8 pad_D_800FC718[0x80];
#define AUDIO_HEAP_SIZE 300000
extern s32 pad_D_80077C80;

#include "audio_data.h"
#include "libnumus/player.h"
#include "rom_device.h"
#include "audio_cache.h"
#include "audio_category_fade.h"
#include "audio_commands.h"

#include "m2c_macros.h"

void Audio_RelocateOffsets(u32* arg0, u32 arg1, s32 arg2);
void Audio_CreateFrameTaskWrapper(void* arg0);
void Audio_ClearWaveDataLoaded(void);
extern s32 D_800FD608;
extern u8 D_8007752C;
s32 func_80037AC4(s32, s32);
void func_800419F8(s32);
s32 func_800376E8(s32);
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);
extern u8 D_80077524;
extern s32 D_800B4188;
extern s32 D_800B41A4;
extern u8* D_800FD690;
void func_80037C04(s32, u32);
extern s32 D_800B41A0;
extern s32 D_800FD610[];
extern u8 D_800FD620;
extern s32 D_800FD628[];
extern u8 D_800FD68C;
extern u8 D_80077528;
extern u8 D_80077520;
extern s32 D_800FD5F8[];
extern u8* D_800B41B0[];
extern u8* D_800B41F0;
extern File1Header* D_800B4160;
extern s32 D_800B4190;
extern s32 D_800B4188;
extern s32 D_800B41A4;
extern s32 D_800775A8;
s32 func_80037B7C(s32);
s32 func_80037AC4(s32, s32);
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);
void func_8003A710(u8*);
void func_80037D4C(s32, f32);
void func_80037E84(s32, s32);
void func_80037DF4(s32, s32);
void func_8003FE58(s32, s32, s32);
M2C_UNK func_80037AC4(s32, M2C_UNK);                /* extern */
extern u8 D_80077524;
extern s32 D_800FD64C;
extern s32 D_800FD650;
extern s32 D_800FD654;
extern s32 D_800B3CE4;
extern s32 D_800FD66C;
extern s32 D_800FD658[];
extern s32 D_800FD738;
extern s32 D_800FD680;
M2C_UNK func_8003834C(s32, s32, s32, M2C_UNK, s32, s32, s32); /* extern */
extern s32 D_800B418C;
extern s32 D_800B41A8;
extern s32 D_800FD698[];
extern s32 D_800FD6A8[];
extern u8 D_800FD6B4[2];
extern u8 D_80077538;
extern u8 D_800FD6B2[2];
extern s32 D_800FD6A0[];
extern u8 D_800FD6B0[];
extern u8 D_800FD6B6[];
extern u8 D_80077560;

extern u8 D_80077548;
extern u8 D_80077550;
extern u8 D_80077554;
extern u8 D_80077564;
extern u8 D_8007756C;
extern u8 D_80077570;
extern u8 D_80077574;
extern u8 D_80077580;
u32 func_80053A80(void);
void func_80043CE8(s32, f32, s32);

/**
 * Probably picks an announcer line (func_80043CE8 ID) from the HP ratios of the two sides.
 * D_800FD698 / D_800FD6A8 are current / max HP per side (max 0 is fixed to 100).
 */
void func_80042508(u32 arg0) {
    s32 other;
    u32 pct;
    u32 otherPct;

    if (arg0 < 2) {
        D_80077550++;
        D_80077554 = arg0;
        D_80077564 = 0;
        D_8007756C = 0;
        D_80077570 = 1;
        D_80077574 = 0;
        D_80077580 = 0;
        other = arg0 & 0xF0; // FAKE: reuses `other` for the high nibble (fixes the spill slot)
        arg0 &= 0xF;
        if (other == 0) {
            if (D_800FD6A8[0] == 0) {
                D_800FD698[0] = 100;
                D_800FD6A8[0] = 100;
            }
            if (D_800FD6A8[1] == 0) {
                D_800FD698[1] = 100;
                D_800FD6A8[1] = 100;
            }
            other = arg0 ^ 1;
            pct = (u32)(D_800FD698[arg0] * 100) / (u32)D_800FD6A8[arg0];
            otherPct = (u32)(D_800FD698[other] * 100) / (u32)D_800FD6A8[other];

            if (D_800FD6B0[arg0] != 0) {
                D_8007756C = 1;
                if ((D_800FD6B4[arg0] < 3) && (D_800FD6B2[arg0] >= 3)) {
                    if ((u32)D_800FD698[arg0] < 50) {
                        func_80043CE8(0x54, 0.0f, 0x80);
                    } else {
                        func_80043CE8(0x37, 0.0f, 0x80);
                    }
                    D_800FD6B0[arg0] = 0;
                    return;
                }
                if ((D_800FD6B4[arg0] < D_800FD6B4[other]) && (D_800FD6B2[arg0] >= 3)) {
                    func_80043CE8(0x6D, 0.0f, 0x80);
                    D_800FD6B0[arg0] = 0;
                    return;
                }
                D_800FD6B0[arg0] = 0;
            }
            if ((pct < 50) && (pct >= 21)) {
                if ((u8)func_80053A80() & 1) {
                    if (D_80077550 == 1) {
                        func_80043CE8(0x42, 0.0f, 0x80);
                        return;
                    }
                    func_80043CE8(0x44, 0.0f, 0x80);
                    return;
                }
                func_80043CE8(0x20, 0.0f, 0x80);
                return;
            }
            if ((pct < 21) && (pct >= 6)) {
                if ((u8)func_80053A80() & 1) {
                    if (D_80077550 == 1) {
                        func_80043CE8(0x42, 0.0f, 0x80);
                        return;
                    }
                    func_80043CE8(0x44, 0.0f, 0x80);
                    return;
                }
                func_80043CE8(0x21, 0.0f, 0x80);
                return;
            }
            if ((pct < 6) && (D_800FD698[arg0] != 0)) {
                if ((D_800FD6B4[arg0] < 3) && ((u8)func_80053A80() & 0x11)) {
                    func_80043CE8(0x54, 0.0f, 0x80);
                    return;
                }
                if ((u8)func_80053A80() & 0x10) {
                    func_80043CE8(0x42, 0.0f, 0x80);
                    return;
                }
                func_80043CE8(0x38, 0.0f, 0x80);
                return;
            }
            if ((D_800FD6B4[other] < 3) && (D_800FD6B2[other] >= 3)) {
                if ((u32)D_800FD698[other] < 30) {
                    func_80043CE8(0x46, 0.0f, 0x80);
                    return;
                }
                if ((u8)func_80053A80() & 1) {
                    if (D_80077550 == 1) {
                        if ((u8)func_80053A80() & 1) {
                            func_80043CE8(0x42, 0.0f, 0x80);
                            return;
                        }
                        func_80043CE8(0x43, 0.0f, 0x80);
                        return;
                    }
                    func_80043CE8(0x44, 0.0f, 0x80);
                    return;
                }
                func_80043CE8(0x36, 0.0f, 0x80);
                return;
            }
            if ((D_800FD698[arg0] != 0) && (otherPct < 21)) {
                if (D_800FD6B4[other] < 3) {
                    func_80043CE8(0x40, 0.0f, 0x80);
                    return;
                }
                func_80043CE8(0x39, 0.0f, 0x80);
                return;
            }
            if (D_80077550 == 1) {
                if (D_80077548 < 2) {
                    func_80043CE8(0x41, 0.0f, 0x80);
                    return;
                }
                if (D_80077548 == 2) {
                    func_80043CE8(0x43, 0.0f, 0x80);
                    return;
                }
                if ((u8)func_80053A80() & 1) {
                    func_80043CE8(0x42, 0.0f, 0x80);
                    return;
                }
                func_80043CE8(0x43, 0.0f, 0x80);
                return;
            }
            func_80043CE8(0x44, 0.0f, 0x80);
        }
    }
}

extern u8 D_8007755C;
extern u8 D_80077564;
extern u8 D_80077568;
extern u8 D_8007756C;
extern u8 D_80077574;
extern u8 D_8007757C;
extern u8 D_80077580;
extern u8 D_800FD6B8;
extern s32 D_800FD6BC;
void func_80043CE8(s32, f32, s32);

void func_80042A6C(s32 arg0) {
    switch (arg0) {
        case 3:
            if (D_80077560 != 0 && D_8007757C == 0) {
                func_80043CE8(0x45, 0.0f, 0x80);
                D_80077560 = 0;
            } else {
                func_80043CE8(0x1D, 0.0f, 0x80);
            }
            func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
            break;
        case 5:
            if (D_8007756C != 0) {
                func_80043CE8(0x56, 0.0f, 0x80);
                D_8007756C = 0;
            } else if (D_80077568 == 0) {
                func_80043CE8(0x3A, 0.0f, 0x80);
            }
            break;
        case 6:
            func_80043CE8(0x26, 0.0f, 0x80);
            func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x70, 0x80, 0, -1);
            break;
        case 7:
            if (D_8007756C != 0) {
                func_80043CE8(0x56, 0.0f, 0x80);
                D_8007756C = 0;
            } else if (D_80077568 == 0) {
                func_80043CE8(0x3A, 0.0f, 0x80);
            }
            break;
        case 8:
        case 9:
        case 10:
            func_80043CE8(0x3A, 0.0f, 0x80);
            break;
        case 14:
            func_80043CE8(0x49, 0.0f, 0x80);
            break;
        case 15:
            func_80043CE8(0x68, 0.0f, 0x80);
            break;
        case 16:
            func_80043CE8(0x3A, 0.0f, 0x80);
            break;
        case 18:
            func_80043CE8(0x4D, 0.0f, 0x80);
            break;
        case 19:
            if ((u8)osGetCount() & 1) {
                func_80043CE8(0x50, 0.0f, 0x80);
            } else {
                func_80043CE8(0x67, 0.0f, 0x80);
            }
            break;
        case 25:
            func_80043CE8(0x4C, 0.0f, 0x80);
            break;
        case 26:
            func_80043CE8(0x3B, 0.0f, 0x80);
            D_80077580 = 1;
            break;
        case 27:
            func_80043CE8(0x4C, 0.0f, 0x80);
            break;
        case 29:
            func_80043CE8(0x19, 0.0f, 0x80);
            D_800FD6BC = func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
            D_800FD6B8 = 1;
            D_8007755C = 1;
            break;
        case 30:
            func_80043CE8(0x1A, 0.0f, 0x80);
            func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
            D_8007755C = 1;
            break;
        case 31:
            func_80043CE8(0x51, 0.0f, 0x80);
            D_80077574 = 1;
            break;
        case 32:
            func_80043CE8(0x3C, 0.0f, 0x80);
            break;
        case 33:
        case 34:
        case 35:
        case 36:
            func_80037AC4(D_800775A8, 0x50);
            D_800775A8 = func_8003834C(D_800B4188, D_800B41A4, 0xF, 0x80, 0x80, 0, -1);
            break;
        case 37:
        case 38:
        case 39:
        case 40:
            if (D_800FD6B4[0] >= 2 && D_800FD6B4[1] >= 2) {
                func_80043CE8(0x1F, 0.0f, 0x80);
            }
            break;
        case 41:
            func_80043CE8(0x1B, 0.0f, 0x80);
            if (D_800FD6B8 == 0) {
                func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
            }
            D_8007755C = 1;
            break;
        case 42:
            if (D_800FD6B4[0] >= 2 && D_800FD6B4[1] >= 2) {
                func_80043CE8(0x1C, 0.0f, 0x80);
                func_80037AC4(D_800FD6BC, 0x3C);
                D_800FD6BC = 0;
                func_8003834C(D_800B4188, D_800B41A4, 0x1C, 0x80, 0x80, 0, -1);
                D_8007755C = 1;
                D_80077564 = 1;
            }
            break;
        case 43:
            if (D_80077580 == 0) {
                func_80043CE8(0x69, 0.0f, 0x80);
            }
            break;
        case 44:
            if (D_80077580 == 0) {
                func_80043CE8(0x5B, 0.0f, 0x80);
            }
            break;
        case 45:
            func_80043CE8(0x1E, 0.0f, 0x80);
            break;
        case 46:
            func_80043CE8(0x4E, 0.0f, 0x80);
            break;
    }
}

u32 func_80053A80(void);
void func_80042FF8(s32 arg0) {
    switch (arg0) {
    case 0x0:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x1:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x2:
        func_80043CE8(0x24, 0.0f, 0x80);
        if ((u8)func_80053A80() & 1) {
            func_80043CE8(0x2F, 0.0f, 0x80);
            D_80077568 = 1;
        }
        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
        break;
    case 0x3:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x4:
        if (D_80077564 == 0) {
            func_80043CE8(0x5C, 0.0f, 0x80);
        }
        break;
    case 0x5:
        if (D_80077564 == 0) {
            func_80043CE8(0x5C, 0.0f, 0x80);
        }
        break;
    case 0x6:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x9:
        func_80043CE8(0x27, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
        break;
    case 0xA:
        if (D_80077564 == 0) {
            func_80043CE8(0x5C, 0.0f, 0x80);
        }
        break;
    case 0xB:
        func_80043CE8(0x25, 0.0f, 0x80);
        if ((u8)func_80053A80() & 1) {
            func_80043CE8(0x2F, 0.0f, 0x80);
            D_80077568 = 1;
        }
        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
        break;
    case 0xC:
        if (D_80077564 == 0) {
            func_80043CE8(0x5C, 0.0f, 0x80);
        }
        break;
    case 0xD:
        if (D_80077574 == 0) {
            func_80043CE8(0x5F, 0.0f, 0x80);
        } else {
            D_80077574 = 0;
        }
        break;
    case 0xE:
        func_80043CE8(0x60, 0.0f, 0x80);
        break;
    case 0xF:
        func_80043CE8(0x61, 0.0f, 0x80);
        break;
    case 0x10:
        func_80043CE8(0x62, 0.0f, 0x80);
        break;
    case 0x11:
        func_80043CE8(0x63, 0.0f, 0x80);
        break;
    case 0x12:
        func_80043CE8(0x64, 0.0f, 0x80);
        break;
    case 0x13:
        if (D_80077574 == 0) {
            func_80043CE8(0x5F, 0.0f, 0x80);
        } else {
            D_80077574 = 0;
        }
        break;
    case 0x14:
        func_80043CE8(0x60, 0.0f, 0x80);
        break;
    case 0x15:
        func_80043CE8(0x61, 0.0f, 0x80);
        break;
    case 0x16:
        func_80043CE8(0x62, 0.0f, 0x80);
        break;
    case 0x17:
        func_80043CE8(0x63, 0.0f, 0x80);
        break;
    case 0x18:
        func_80043CE8(0x64, 0.0f, 0x80);
        break;
    case 0x19:
        func_80043CE8(0x4C, 0.0f, 0x80);
        break;
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
        if (D_80077564 == 0) {
            func_80043CE8(0x5C, 0.0f, 0x80);
        }
        break;
    case 0x26:
        func_80043CE8(0x4C, 0.0f, 0x80);
        break;
    case 0x27:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x28:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x29:
        func_80043CE8(0x4C, 0.0f, 0x80);
        break;
    case 0x2D:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x2E:
        func_80043CE8(0x4C, 0.0f, 0x80);
        break;
    case 0x35:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x36:
        func_80043CE8(0x65, 0.0f, 0x80);
        break;
    case 0x37:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x38:
        func_80043CE8(0x48, 0.0f, 0x80);
        break;
    case 0x3A:
        if (D_80077564 == 0) {
            func_80043CE8(0x5C, 0.0f, 0x80);
        }
        break;
    case 0x3B:
        if (D_80077564 == 0) {
            func_80043CE8(0x5C, 0.0f, 0x80);
        }
        break;
    case 0x3C:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x3D:
        if (D_80077564 == 0) {
            func_80043CE8(0x5C, 0.0f, 0x80);
        }
        break;
    case 0x3E:
        func_80043CE8(0x4C, 0.0f, 0x80);
        break;
    case 0x3F:
        func_80043CE8(0x4C, 0.0f, 0x80);
        break;
    case 0x40:
        func_80043CE8(0x6B, 0.0f, 0x80);
        break;
    case 0x41:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x42:
        if (D_80077564 == 0) {
            func_80043CE8(0x47, 0.0f, 0x80);
        }
        break;
    case 0x43:
        func_80043CE8(0x3B, 0.0f, 0x80);
        break;
    case 0x44:
        func_80043CE8(0x4C, 0.0f, 0x80);
        break;
    case 0x45:
        if (D_80077564 == 0) {
            func_80043CE8(0x5C, 0.0f, 0x80);
        }
        break;
    case 0x46:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x48:
        func_80043CE8(0x6B, 0.0f, 0x80);
        break;
    case 0x49:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x4A:
        func_80043CE8(0x2B, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
        break;
    case 0x4D:
        func_80043CE8(0x2A, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
        break;
    case 0x4E:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x4F:
        func_80043CE8(0x28, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
        break;
    case 0x50:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x51:
        func_80043CE8(0x65, 0.0f, 0x80);
        break;
    case 0x52:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x53:
        func_80043CE8(0x66, 0.0f, 0x80);
        break;
    case 0x54:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x55:
    case 0x56:
        func_80043CE8(0x3C, 0.0f, 0x80);
        break;
    case 0x57:
        func_80043CE8(0x29, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
        break;
    }
}


extern u8 D_80077548;
void func_80043CE8(s32, f32, s32);
extern s32 D_800B4188;
extern s32 D_800B41A4;
extern u8 D_80077554;
extern u8 D_80077570;
extern u8 D_8007755C;
extern u8 D_80077564;
void func_80043860(u32 arg0) {
    u32 hp;
    s32 lost;
    u32* prev;

    if (arg0 < 2) {
        hp = D_800FD698[arg0];
        if (hp != 0) {
            prev = (u32*)&D_800FD6A0[arg0];
            if (arg0 == D_80077554) {
                if ((hp < 30) && (D_80077570 != 0)) {
                    func_80043CE8(0x6A, 0.0f, 0x80);
                    D_80077570 = 0;
                }
            } else {
                lost = *prev - hp;
                *prev = hp;
                if (lost > 0) {
                    if ((hp < 10) && (hp != 0)) {
                        func_80043CE8(0x22, 0.0f, 0x80);
                        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
                        return;
                    }
                    if (D_8007755C == 0) {
                        if (lost < 15) {
                            if (((u8)osGetCount() & 0x11) || (D_80077548 < 2)) {
                                func_80043CE8(0x3F, 0.0f, 0x80);
                                D_80077564 = 1;
                            }
                        } else if (lost < 60) {
                            if (((u8)osGetCount() & 1) || (D_80077548 < 2)) {
                                func_80043CE8(0x3D, 0.0f, 0x80);
                                D_80077564 = 1;
                            }
                        } else {
                            func_80043CE8(0x3E, 0.0f, 0x80);
                        }
                    } else {
                        D_8007755C = 0;
                    }
                }
            }
        }
    }
}

/*
 * func_80043A10
 *
 * Chooses between two settings depending on D_80077540 and D_800FD6B4 and
 * sets the flag byte D_80077530.
 *
 *   - If D_80077540 == 8 and the byte D_800FD6B4 is at least 2:
 *     func_80043CE8(0x18, 0.0f, 0x80) and D_80077530 = 1; nothing else.
 *   - In every other case: func_80043CE8(0x1E, 0.0f, 0x80), D_80077530 = 0,
 *     then func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1).
 *
 * The second argument of func_80043CE8 is a float: with a float parameter
 * the compiler loads the constant into $a1 with `li`, which is what the ROM
 * does (an integer 0 would use `move $a1, $zero`).  What func_80043CE8
 * (still assembly) and func_8003834C do with these values is not
 * established here.
 */
void func_80043CE8(s32, f32, s32);
extern s8 D_80077530;
extern u8 D_80077540;
extern s32 D_800B4188;
extern s32 D_800B41A4;

void func_80043A10(void) {
    if (D_80077540 == 8) {
        if (D_800FD6B4[0] >= 2) {
            func_80043CE8(0x18, 0.0f, 0x80);
            D_80077530 = 1;
            return;
        }
        func_80043CE8(0x1E, 0.0f, 0x80);
        D_80077530 = 0;
        func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
        return;
    }
    func_80043CE8(0x1E, 0.0f, 0x80);
    D_80077530 = 0;
    func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
}

extern s32 D_80077590;
extern u8 D_80077550;
extern u32 D_8007758C;
extern u32 D_80077588;
extern u32 D_80077558;
extern u8 D_8007754C;
extern u32 D_80077598;
extern u8 D_8007759C;
extern s32 D_800775A4;
extern s32 D_800775A0;
extern u8 D_80077578;
extern u8 D_80077584;
extern u8 D_8007753C;
void func_80043B00(s32 arg0, u32 arg1) {
    func_800419F8(0);
    D_80077590 = 0;
    D_800FD738 = 0;
    D_80077540 = arg0;
    D_80077548 = 0;
    D_80077550 = 0;
    D_8007758C = 0;
    D_80077588 = 0;
    D_80077558 = 0;
    D_800FD6B0[0] = 0;
    D_800FD6B0[1] = 0;
    D_800FD698[0] = D_800FD6A0[0] = 100;
    D_800FD698[1] = D_800FD6A0[1] = 100;
    D_800FD6A8[0] = 100;
    D_800FD6A8[1] = 100;
    if (D_80077540 > 0) {
        D_800FD6B4[0] = 6;
        D_800FD6B4[1] = 6;
    } else if ((arg1 != 0) && (arg1 < 6)) {
        D_800FD6B4[0] = D_800FD6B2[0] = 6;
        D_800FD6B4[1] = D_800FD6B2[1] = 6;
    } else {
        D_800FD6B4[0] = D_800FD6B2[0] = 12;
        D_800FD6B4[1] = D_800FD6B2[1] = 12;
    }
    D_800FD6B6[0] = 0;
    D_800FD6B6[1] = 0;
    D_8007754C = 0;
    D_80077598 = 0;
    D_8007759C = 0;
    D_800775A4 = 0;
    D_800775A0 = 0;
    D_800FD6B8 = 0;
    D_800FD6BC = 0;
    D_80077564 = 0;
    D_80077568 = 0;
    D_8007756C = 0;
    D_80077570 = 0;
    D_80077574 = 0;
    D_80077578 = 0;
    D_80077580 = 0;
    D_80077584 = 1;
    D_8007755C = 0;
    D_80077560 = 0;
    D_8007757C = 0;
    D_80077554 = 0;
    D_8007753C = 0;
    D_80077530 = 0;
}

/** One pending entry in the 10-slot ring buffer D_800FD6C0. */
typedef struct QueuedEntry80043CE8 {
    /* 0x0 */ s32 id;
    /* 0x4 */ f32 value;
    /* 0x8 */ u32 level;
} QueuedEntry80043CE8;

extern u8 D_80077528;
extern u8 D_8007753C;
extern u32 D_80077558;
extern u32 D_8007758C;
extern QueuedEntry80043CE8 D_800FD6C0[];
s32 func_8004D300(s32);

/**
 * Appends (arg0, arg1, arg2 + 0x70) to the 10-entry ring buffer D_800FD6C0,
 * with the level clamped to 0xFF.
 *
 * Does nothing unless D_80077528 == 0, D_80077538 != 0 and D_8007753C == 0,
 * and also does nothing when D_80077558 (the number of queued entries) is
 * already 2 or more. D_8007758C is the write index and wraps modulo 10. The
 * update runs with the interrupt mask raised by func_8004D300 (libultra's
 * osSetIntMask) and restored afterwards.
 */
void func_80043CE8(s32 arg0, f32 arg1, s32 arg2) {
    s32 prevMask;
    QueuedEntry80043CE8* entry;
    u32 level;
    u32 idx;
    u32 count;

    if ((D_80077528 == 0) && (D_80077538 != 0) && (D_8007753C == 0)) {
        prevMask = func_8004D300(1);
        count = D_80077558;
        if (count < 2) {
            idx = D_8007758C;
            entry = &D_800FD6C0[idx];
            level = arg2 + 0x70;
            entry->level = level;
            entry->id = arg0;
            entry->value = arg1;
            if (level >= 0x100) {
                entry->level = 0xFF;
            }
            D_8007758C = idx + 1;
            D_80077558 = count + 1;
            D_8007758C %= 10;
        }
        func_8004D300(prevMask);
    }
}

extern u8 D_80077548;
extern u8 D_8007754C;
extern u32 D_80077588;
extern s32 D_80077590;
extern u32 D_80077598;
extern u8 D_8007759C;
extern s32 D_800775A0;
extern u8 D_800B3CC8;
s32 func_80037B7C(s32);
s32 func_800383DC(s32, s32, s32, s32, s32, s32, s32);

void func_80043DD0(void) {
    s32 ret;

    if ((D_80077538 != 0) && (D_8007753C == 0) && (func_80037B7C(D_80077590) == 0) && (D_80077588 != D_8007758C) &&
        (D_800B3CC8 == 0)) {
        ret = func_800383DC(D_800B418C, D_800B41A8, D_800FD6C0[D_80077588].id, D_800FD6C0[D_80077588].level, 0x80, 0, -1);
        if (ret != -1) {
            D_80077590 = ret;
            D_80077588++;
            D_80077588 %= 10;
            D_80077558--;
        }
    }

    if (D_8007754C != 0) {
        if ((D_80077598 >= 0x3E9) && (D_8007759C == 0) && (D_80077548 > 0)) {
            func_80043CE8(0x2E, 0.0f, 0x80);
            D_8007759C = 1;
        } else if ((D_80077598 >= 0xA29) && (D_8007759C == 0) && (D_80077548 == 0)) {
            func_80043CE8(0x2E, 0.0f, 0x80);
            D_8007759C = 1;
        } else if ((D_80077598 >= 0x641) && (D_8007759C == 1) && (D_80077548 > 0)) {
            func_80043CE8(0x31, 0.0f, 0x80);
            if (D_800775A0 == 0) {
                D_800775A0 = func_800383DC(D_800B4188, D_800B41A4, 0x19, 0x80, 0x80, 0, -1);
            }
            D_8007759C = 2;
        } else if ((D_80077598 >= 0xC81) && (D_8007759C == 1) && (D_80077548 == 0)) {
            func_80043CE8(0x31, 0.0f, 0x80);
            if (D_800775A0 == 0) {
                D_800775A0 = func_800383DC(D_800B4188, D_800B41A4, 0x19, 0x80, 0x80, 0, -1);
            }
            D_8007759C = 2;
        } else if ((D_80077598 >= 0x899) && (D_80077548 > 0)) {
            func_80043CE8(0x32, 0.0f, 0x80);
            D_80077598 = 0x3E8;
            D_8007759C = 1;
        } else if ((D_80077598 >= 0xED9) && (D_80077548 == 0)) {
            func_80043CE8(0x32, 0.0f, 0x80);
            D_80077598 = 0xA28;
            D_8007759C = 1;
        }
        D_80077598++;
    }
}

extern u8* D_800FD690;
extern File1Header* D_800B4164;
extern u8* D_800B41F0;
extern u8* D_800B419C;
s32 func_80037F68(u8*, u8*);
void func_80037C04(s32, u32);

s32 func_80044158(u8* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    u8* sp1C;

    D_800FD690 = arg0;
    sp1C = D_800FD690 + 0x32C0;

    if (1) {}  // karodo

    Rom_DmaRead(D_800B4164->offset1, (u32)D_800B41F0, D_800B4164->wave_tables_offset - D_800B4164->offset1);
    Audio_CopyDataWithCacheSync((s32)D_800B41F0, D_800FD690, 0x32C0);
    Rom_DmaRead(D_800B4164->wave_tables_offset, (u32)sp1C, D_800B4164->files[0] - D_800B4164->wave_tables_offset);
    Audio_RelocateSoundBankWrapper((s32)D_800FD690, (s32)sp1C);
    D_80075C30 |= 0x80000000;
    Rom_DmaRead(D_800B4164->files[0], (u32)D_800B41F0, D_800B4164->files[1] - D_800B4164->files[0]);
    Audio_CopyDataWithCacheSync((s32)D_800B41F0, D_800B419C, 0x8CA0);
    D_800FD608 = func_80037F68(D_800FD690, D_800B419C);
    func_80037C04(D_800FD608, 0x70);

    return D_800FD608;
}

void Audio_ClearWaveDataLoaded(void) {
    D_80075C30 &= ~0x80000000;
}
