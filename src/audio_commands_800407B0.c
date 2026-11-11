/* Stadium Zero resident code. */
/* Split from audio_commands.c so the jump tables of func_800407B0 land at 0x8007E87C. */

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

typedef struct SoundBank8 {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
    /* 0x2 */ u8 unk_2[6];
} SoundBank8; // size = 0x8

extern SoundBank8 D_80077068[];
extern u8 D_80077528;
extern u8 D_80077530;
extern u8 D_8007753C;
extern u8 D_80077540;
extern u8 D_80077544;
extern s32 D_800B3CE4;
extern s32 D_800B4188;
extern s32 D_800B418C;
extern s32 D_800B41A4;
extern s32 D_800B41A8;
extern s32 D_800FD608;
extern s32 D_800FD654;
extern s32 D_800FD66C;
extern s32 D_800FD680;
extern s32 D_800FD738;
s32 func_80037B7C(s32);
s32 func_80037AC4(s32, s32);
void func_80037C04(s32, u32);
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);
s32 func_80047260(s32);
void func_80043B00(s32, s32);

s32 func_800407B0(u32 arg0, s32 arg1, s32 arg2) {
    s32 pad[3]; // FAKE
    s32 ret;
    s32 pan;

    if (D_80077528 != 0) {
        return 0;
    }

    switch (arg0) {
        case 0:
            if (func_80037B7C(D_800FD654) != 0) {
                return 0;
            }
            ret = D_800FD654 = func_8003834C(D_800B4188, D_800B41A4, 1, 0x70, 0x80, 0, -1);
            break;

        case 1:
            if (arg1 < -90) {
                arg1 = -90;
            } else if (arg1 > 90) {
                arg1 = 90;
            }
            pan = (arg1 + 90) * 1.4111111f;
            if (pan < 0) {
                pan = 0;
            } else if (pan > 244) {
                pan = 244;
            }
            ret = func_8003834C(D_800B4188, D_800B41A4, 2, 0x80, pan, 0, -1);
            break;

        case 2:
            if (func_80047260(D_800FD66C) != 0) {
                func_80037AC4(D_800FD66C, 0x14);
                D_800FD66C = 0;
            }
            ret = func_8003834C(D_800B4188, D_800B41A4, 3, 0x80, 0x80, 0, -1);
            break;

        case 3:
            D_800FD66C = ret = func_8003834C(D_800B4188, D_800B41A4, 4, 0x80, 0x80, 0, -1);
            break;

        case 4:
            ret = D_800B3CE4 = func_8003834C(D_800B4188, D_800B41A4, 1, 0x80, 0x80, 0, -1);
            break;

        case 5:
            break;

        case 6:
        case 7:
        case 8:
            arg1 = 3;
        case 0x33:
            if ((arg1 > 0) && (arg1 < 0x98)) {
                arg1--;
            } else {
                arg1 = 0;
            }
            switch (D_80077068[arg1].unk_0) {
                case 0:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 7, 0x80, 0x80, 0, -1);
                    break;
                case 1:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 6, 0x80, 0x80, 0, -1);
                    break;
                case 2:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 5, 0x80, 0x80, 0, -1);
                    break;
            }
            break;

        case 9:
        case 10:
        case 11:
            return 0;

        case 12:
        case 13:
        case 14:
            return 0;

        case 15:
        case 16:
        case 17:
            arg1 = 2;
        case 0x32:
            if ((arg1 > 0) && (arg1 < 0x98)) {
                arg1--;
            } else {
                arg1 = 0;
            }
            switch (D_80077068[arg1].unk_1) {
                case 0:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 10, 0x80, 0x80, 0, -1);
                    break;
                case 1:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 9, 0x80, 0x80, 0, -1);
                    break;
                case 2:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 8, 0x80, 0x80, 0, -1);
                    break;
            }
            break;

        case 18:
            ret = func_8003834C(D_800B4188, D_800B41A4, 11, 0x80, 0x80, 0, -1);
            break;

        case 19:
            ret = func_8003834C(D_800B4188, D_800B41A4, 12, 0x80, 0x80, 0, -1);
            break;

        case 20:
            ret = func_8003834C(D_800B4188, D_800B41A4, 13, 0x80, 0x80, 0, -1);
            break;

        case 21:
        case 22:
        case 23:
        case 24:
            break;

        case 0x3C:
            if (func_80037B7C(D_800FD738) != 0) {
                func_80037AC4(D_800FD738, 100);
                D_800FD738 = 0;
            }
            if ((arg2 <= 0) || (arg2 >= 7)) {
                D_80077544 = 1;
            } else {
                D_80077544 = arg2;
            }
            if (arg1 == 10) {
                func_80043B00(1, 1);
                return 0;
            }
            if (arg1 >= 9) {
                return 0;
            }
            func_80043B00(arg1, arg2);
            if (arg1 == 0) {
                ret = func_8003834C(D_800B4188, D_800B41A4, 0x23, 0xA0, 0x80, 0, -1);
            } else {
                ret = func_8003834C(D_800B4188, D_800B41A4, arg1 + 0xF, 0xA0, 0x80, 0, -1);
            }
            break;

        case 0x3D:
            D_8007753C = 1;
            switch (arg1) {
                case 0:
                    D_800FD738 = ret = func_8003834C(D_800B4188, D_800B41A4, 0x1D, 0x80, 0x80, 0, -1);
                    break;
                case 1:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 0x1E, 0x80, 0x80, 0, -1);
                    break;
                case 2:
                    switch (arg2) {
                        case 1:
                            pan = 0x1E;
                            break;
                        case 2:
                            pan = 0x64;
                            break;
                        case 3:
                            pan = 0xAA;
                            break;
                        case 4:
                            pan = 0x55;
                            break;
                        case 5:
                            pan = 0x9B;
                            break;
                        case 6:
                            pan = 0xE1;
                            break;
                        default:
                            pan = 0x7F;
                            break;
                    }
                    ret = func_8003834C(D_800B4188, D_800B41A4, 0x1F, 0x80, pan, 0, -1);
                    break;
                case 3:
                    if (D_80077540 == 8) {
                        ret = func_8003834C(D_800B4188, D_800B41A4, 0x2A, 0x80, 0x80, 0, -1);
                    } else {
                        func_8003EECC(0x14);
                        ret = func_8003834C(D_800B4188, D_800B41A4, 0x20, 0x80, 0x80, 0, -1);
                    }
                    break;
                case 4:
                    if (D_80077540 == 0) {
                        func_8003EECC(0x14);
                        ret = func_8003834C(D_800B4188, D_800B41A4, 0x2B, 0x80, 0x80, 0, -1);
                    } else {
                        ret = func_8003834C(D_800B4188, D_800B41A4, 0x21, 0x80, 0x80, 0, -1);
                    }
                    break;
                default:
                    return 0;
            }
            break;

        case 0x50:
            ret = func_8003834C(D_800B418C, D_800B41A8, D_80077540, 0xFF, 0x60, 0, -1);
            func_8003834C(D_800B418C, D_800B41A8, D_80077540, 0xFF, 0xA0, 0, -1);
            if (D_80077530 == 0) {
                D_800FD608 = func_8003EECC(0xE);
            }
            break;

        case 0x51:
            ret = func_8003834C(D_800B4188, D_800B41A4, 0x24, 0x80, 0x80, 0, -1);
            break;

        case 0x52:
            ret = func_8003834C(D_800B4188, D_800B41A4, 0x27, 0xFF, 0x60, 0, -1);
            func_8003834C(D_800B4188, D_800B41A4, 0x27, 0xFF, 0xA0, 0, -1);
            func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
            break;

        case 0x53:
        case 0x54:
        case 0x55:
        case 0x56:
            break;

        case 0x57:
            ret = func_8003834C(D_800B4188, D_800B41A4, 0x29, 0xFF, 0x80, 0, -1);
            break;

        case 0x46:
            switch (arg1) {
                case 1:
                    if (func_80037B7C(D_800FD680) == 0) {
                        D_800FD680 = func_8003834C(D_800B4188, D_800B41A4, 0x22, 0x50, 0x80, 0, -1);
                    } else {
                        func_80037C04(D_800FD680, 0x50);
                    }
                    break;
                case 2:
                    if (func_80037B7C(D_800FD680) == 0) {
                        D_800FD680 = func_8003834C(D_800B4188, D_800B41A4, 0x22, 0x50, 0x80, 0, -1);
                    } else {
                        func_80037C04(D_800FD680, 0x50);
                    }
                    break;
                case 3:
                    if (func_80037B7C(D_800FD680) == 0) {
                        D_800FD680 = func_8003834C(D_800B4188, D_800B41A4, 0x22, 0x50, 0x80, 0, -1);
                    } else {
                        func_80037C04(D_800FD680, 0x50);
                    }
                    break;
                default:
                    func_80037AC4(D_800FD680, 0x5A);
                    D_800FD680 = 0;
                    return 0;
            }
            break;

        case 0x1E:
            ret = func_8003FE58(0xA6, 1, 0);
            break;
        case 0x1F:
            ret = func_8003FE58(0xA6, 1, 1);
            break;
        case 0x20:
            ret = func_8003FE58(0xA6, 1, 2);
            break;
        case 0x21:
            ret = func_8003FE58(0xA6, 1, 3);
            break;
        case 0x22:
            ret = func_8003FE58(0xA6, 1, 4);
            break;
        case 0x23:
            ret = func_8003FE58(0xA6, 1, 5);
            break;

        default:
            return 0;
    }
    return ret;
}

extern s32 D_800FD654;
extern s32 D_800B3CE4;
extern s32 D_800FD66C;
extern s32 D_800FD658[];
extern s32 D_800FD738;
extern s32 D_800FD680;
s32 func_80041374(s32 arg0, s32 arg1) {
    s32 idx;

    switch (arg0) {
        case 0:
            if (arg1 == 0) {
                arg1 = 1;
            }
            func_80037AC4(D_800FD654, arg1);
            D_800FD654 = 0;
            break;
        case 4:
            if (arg1 == 0) {
                arg1 = 1;
            }
            func_80037AC4(D_800B3CE4, arg1);
            D_800B3CE4 = 0;
            break;
        case 3:
            func_80037AC4(D_800FD66C, 0x3C);
            D_800FD66C = 0;
            break;
        case 5:
            idx = arg1 - 1;
            func_80037AC4(D_800FD658[idx ^ 0], 0xA); // FAKE: keeps idx unfolded in v0
            D_800FD658[idx] = 0;
            break;
        case 0x3D:
            func_80037AC4(D_800FD738, 0x78);
            D_800FD738 = 0;
            break;
        case 0x46:
            if (arg1 == 0) {
                arg1 = 1;
            }
            func_80037AC4(D_800FD680, arg1);
            D_800FD680 = 0;
            break;
        default:
            return 0;
    }
    return 1;
}
