/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/audio_commands.c, src/audio_data.c. */

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

void Audio_RelocateOffsets(u32* arg0, u32 arg1, s32 arg2) {
    u32 i;

    for (i = 0; i < arg2; i++, arg0++) {
        *arg0 += arg1;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003E1F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003E1F8.s")
#endif

void func_80038588(void);
s32 func_80037F68(s32, s32);
void func_80043CE8(s32, f32, s32);
void func_8004609C(u32, u8*, s32);
void func_80047FB0(u8*, s32, s32);
extern u8 D_80077524;
extern u8 D_80077528;
extern u8 D_8007752C;
extern u8 D_8007753C;
extern u8 D_80077540;
extern u8 D_80077544;
extern u8 D_8007754C;
extern s32 D_80077558;
extern s32 D_80077588;
extern s32 D_8007758C;
extern File1Header* D_800B4160;
extern File1Header* D_800B4164;
extern s32 D_800B4180;
extern s32 D_800B419C;
extern u8* D_800B41F0;
extern s32 D_800FD608;
extern u32 D_800FD684;
s32 func_80037B7C(s32);
void func_80037C04(s32, u32);
void func_800419F8(u32);

s32 func_8003EECC(u32 track_id) {
    u32 file_index[1]; // FAKE
    s32 pad; // FAKE
    s32 volume_scale[1]; // FAKE
    s32 file_size;
    u32 start;

    if (track_id == 0x1E) {
        return 0;
    }
    if (func_80037B7C(D_800FD608) != 0) {
        func_80038588();
        D_800FD608 = 0;
    }
    if (D_8007754C != 0) {
        func_800419F8(0);
    }
    file_index[0] = track_id;
    switch (track_id) {
        case 0x0:
            D_80077524 = 0;
            D_8007753C = 0;
            D_80077528 = 0;
            volume_scale[0] = 0x90;
            D_8007752C = 0;
            break;
        case 0x1:
            D_8007753C = 1;
            D_80077524 = 0;
            D_80077528 = 0;
            volume_scale[0] = 0x68;
            D_8007752C = 0;
            func_800419F8(1);
            break;
        case 0x29:
            D_80077524 = 0;
            D_80077528 = 0;
            volume_scale[0] = 0x50;
            file_index[0] = 1;
            D_8007752C = 0;
            break;
        case 0x28:
            D_800FD684 = 1;
            D_8007752C = 0;
            volume_scale[0] = 0x50;
            file_index[0] = 9;
            break;
        case 0x2A:
            D_80077528 = 0;
            volume_scale[0] = 0x50;
            D_8007752C = 0;
            file_index[0] = 9;
            break;
        case 0x9:
            D_80077524 = 0;
            D_8007753C = 1;
            D_8007758C = 0;
            D_80077588 = 0;
            D_80077558 = 0;
            D_80077528 = 0;
            volume_scale[0] = 0x50;
            D_8007752C = 0;
            break;
        case 0x6:
            D_80077528 = 0;
            D_8007753C = 0;
            volume_scale[0] = 0x50;
            D_8007752C = 1;
            break;
        case 0xF:
            D_80077528 = 0;
            D_8007753C = 0;
            volume_scale[0] = 0x50;
            D_8007752C = 1;
            break;
        case 0xD:
            D_80077528 = 0;
            D_8007753C = 0;
            volume_scale[0] = 0x50;
            D_8007752C = 0;
            break;
        case 0xE:
            D_80077528 = 0;
            D_8007752C = 0;
            volume_scale[0] = 0x50;
            D_8007753C = 0;
            break;
        case 0x10:
            D_80077528 = 0;
            D_8007753C = 0;
            volume_scale[0] = 0x60;
            D_8007752C = 0;
            break;
        case 0x11:
            D_80077528 = 0;
            D_8007753C = 0;
            volume_scale[0] = 0x58;
            D_8007752C = 0;
            break;
        case 0x1E:
            return 0;
        case 0x13:
            D_80077528 = 0;
            D_8007753C = 0;
            volume_scale[0] = 0x78;
            D_8007752C = 0;
            break;
        case 0x7:
            D_80077528 = 0;
            D_8007753C = 0;
            volume_scale[0] = 0x78;
            D_8007752C = 1;
            break;
        case 0x8:
            D_80077528 = 0;
            D_8007753C = 1;
            volume_scale[0] = 0xA0;
            D_8007752C = 1;
            func_800419F8(1);
            break;
        case 0xA:
            D_80077528 = 0;
            D_8007753C = 1;
            D_8007752C = 0;
            return 0;
        case 0x14:
            volume_scale[0] = 0x60;
            break;
        case 0xC:
            D_80077528 = 0;
            D_8007753C = 1;
            D_8007752C = 0;
            volume_scale[0] = 0x60;
            break;
        case 0x12:
            D_80077528 = 0;
            D_8007753C = 0;
            volume_scale[0] = 0x50;
            D_8007752C = 1;
            break;
        case 0xB:
            D_80077524 = 0;
            D_80077528 = 1;
            D_8007753C = 1;
            volume_scale[0] = 0x68;
            D_8007752C = 0;
            break;
        case 0x2:
        case 0x32:
            if (D_80077524 != 0) {
                return 0;
            }
            D_80077528 = 0;
            D_8007752C = 0;
            D_8007753C = 0;
            volume_scale[0] = 0x40;
            switch (D_80077540) {
                case 0:
                    switch (D_80077544) {
                        case 6:
                            file_index[0] = 3;
                            func_80043CE8(0x11, 0.0f, 0x80);
                            break;
                        case 1:
                            file_index[0] = 2;
                            func_80043CE8(0x11, 0.0f, 0x80);
                            func_80043CE8(0x12, 0.0f, 0x80);
                            break;
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            file_index[0] = 2;
                            func_80043CE8(0x11, 0.0f, 0x80);
                            func_80043CE8(0x13, 0.0f, 0x80);
                            break;
                        default:
                            file_index[0] = 3;
                            func_80043CE8(0x11, 0.0f, 0x80);
                            break;
                    }
                    break;
                case 1:
                    switch (D_80077544) {
                        case 1:
                            func_80043CE8(9, 0.0f, 0x80);
                            file_index[0] = 2;
                            break;
                        case 2:
                            func_80043CE8(0x14, 0.0f, 0x80);
                            file_index[0] = 2;
                            break;
                        case 3:
                            func_80043CE8(0x15, 0.0f, 0x80);
                            file_index[0] = 2;
                            break;
                        case 4:
                            func_80043CE8(0x16, 0.0f, 0x80);
                            file_index[0] = 2;
                            break;
                        case 5:
                            func_80043CE8(0x17, 0.0f, 0x80);
                            file_index[0] = 2;
                            break;
                    }
                    break;
                case 2:
                    file_index[0] = 2;
                    func_80043CE8(0xB, 0.0f, 0x80);
                    break;
                case 3:
                    file_index[0] = 2;
                    func_80043CE8(0xA, 0.0f, 0x80);
                    break;
                case 4:
                    file_index[0] = 3;
                    func_80043CE8(0xF, 0.0f, 0x80);
                    break;
                case 5:
                    file_index[0] = 3;
                    func_80043CE8(0xE, 0.0f, 0x80);
                    break;
                case 6:
                    file_index[0] = 3;
                    func_80043CE8(0xC, 0.0f, 0x80);
                    break;
                case 7:
                    if (D_80077544 == 1) {
                        file_index[0] = 4;
                    } else {
                        file_index[0] = 3;
                    }
                    func_80043CE8(0x10, 0.0f, 0x80);
                    break;
                case 8:
                    if (D_80077544 == 1) {
                        file_index[0] = 5;
                    } else {
                        file_index[0] = 4;
                    }
                    func_80043CE8(0xD, 0.0f, 0x80);
                    break;
            }
            func_800419F8(1);
            break;
        case 0x3:
        case 0x4:
        case 0x5:
            volume_scale[0] = 0x50;
            break;
        default:
            return 0;
    }

    if (file_index[0] < D_800B4164->num_files - 1) {
        start = D_800B4164->files[file_index[0]];
        file_size = D_800B4164->files[file_index[0] + 1] - start;
    } else {
        start = D_800B4164->files[file_index[0]];
        file_size = D_800B4160->num_files - start;
    }
    func_8004609C(start, D_800B41F0, file_size);
    func_80047FB0(D_800B41F0, D_800B419C, 0x8CA0);
    D_800FD608 = func_80037F68(D_800B4180, D_800B419C);
    func_80037C04(D_800FD608, volume_scale[0]);
    return D_800FD608;
}

extern s32 D_800FD608;
extern u8 D_8007752C;
s32 func_80037AC4(s32, s32);
void func_800419F8(u32);

s32 func_8003F654(s32 arg0) {
    s32 ret;

    if (arg0 == 0) {
        arg0 = 1;
    }
    ret = func_80037AC4(D_800FD608, arg0);

    if (D_8007752C == 0) {
        func_800419F8(0);
    }
    return ret;
}

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

s32 func_8003F6AC(s32 arg0) {
    s32 ret;
    s32 pad[2]; // FAKE
    u32 i;
    volatile s32 id; // FAKE: keeps the copy in its stack slot
    s32* p;

    if (arg0 == 0xF) {
        if (!(D_80075C30 & 0x80000000)) {
            return 0;
        }
        ret = func_8003834C((s32)D_800FD690, D_800B41A0, 0xF, 0x80, 0x80, 0, -1);
        func_80037AC4(D_800FD608, 0x28);
        return ret;
    }
    if (arg0 == 0x17) {
        return func_8003834C(D_800B4188, D_800B41A0, 0x17, 0x80, 0x80, 0, -1);
    }
    i = 0;
    if (D_800FD68C != 0) {
        p = D_800FD628;
    loop:
        i++;
        if (arg0 == *p) {
            return 0;
        }
        p++;
        if (i < D_800FD68C) {
            goto loop;
        }
    }
    D_800FD628[D_800FD68C] = arg0;
    D_800FD68C++;
    id = arg0;
    switch (arg0) {
        case 36:
            func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
            break;
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            func_8003834C(D_800B4188, D_800B41A4, 0x1A, 0x80, 0x80, 0, -1);
            break;
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
        case 11: case 12: case 13: case 14: case 16: case 17: case 24: case 25: case 26:
        case 27: case 28: case 29: case 30: case 31: case 32: case 33: case 34: case 35: case 37:
            break;
        case 15:
        case 23:
        default:
            return 0;
    }
    if (arg0 == 0xA) {
        D_80077524 = 1;
    }
    switch (id) {
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 8:
            if (D_800FD610[D_800FD620] != 0) {
                func_80037AC4(D_800FD610[D_800FD620], 1);
            }
            ret = func_800376E8(arg0);
            D_800FD610[D_800FD620++] = ret;
            D_800FD620 %= 4;
            break;
        default:
            ret = func_800376E8(arg0);
            break;
    }
    if (id == 0xA) {
        func_80037C04(ret, 0xE0);
    }
    return ret;
}

typedef struct Bank8003F96C {
    /* 0x00 */ u32 count;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 files[1];
} Bank8003F96C;
extern u8 D_80077528;
extern u8 D_80077520;
extern s32 D_800FD5F8[];
extern u8* D_800B41B0[];
extern u8* D_800B41F0;
extern Bank8003F96C* D_800B4174;
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

s32 func_8003F96C(u32 arg0, u32 arg1) {
    u8 pad[0x28C]; // FAKE
    s32 sp30;
    u32 start;
    u32 size;

    if (D_80077528 != 0) {
        return 0;
    }
    if (arg0 >= 0x98) {
        return 0;
    }
    D_80077520++;
    D_80077520 %= 3;
    if (func_80037B7C(D_800FD5F8[D_80077520]) != 0) {
        D_80077520 += 2;
        D_80077520 %= 3;
        return 0;
    }
    arg0--;
    if (arg0 < D_800B4174->count - 1) {
        start = D_800B4174->files[arg0];
        size = D_800B4174->files[arg0 + 1] - start;
    } else {
        start = D_800B4174->files[arg0];
        size = D_800B4160->files[3] - start;
    }
    Rom_DmaRead(start, (u32)D_800B41F0, size);
    Audio_CopyDataWithCacheSync((s32)D_800B41F0, D_800B41B0[D_80077520], 0x140);
    func_8003A710(D_800B41B0[D_80077520]);
    switch (arg1) {
        case 0:
            D_800FD5F8[D_80077520] = func_8003834C(D_800B4190, (s32)D_800B41B0[D_80077520], 1, 0xA0, 0x80, 0, -1);
            break;
        case 5:
            D_800FD5F8[D_80077520] = func_8003834C(D_800B4190, (s32)D_800B41B0[D_80077520], 3, 0x80, 0x80, 0, -1);
            break;
        case 1:
            D_800FD5F8[D_80077520] = func_8003834C(D_800B4190, (s32)D_800B41B0[D_80077520], 4, 0x78, 0x50, 0, -1);
            sp30 = func_8003834C(D_800B4190, (s32)D_800B41B0[D_80077520], 4, 0x78, 0xB0, 0, -1);
            func_80037D4C(D_800FD5F8[D_80077520], 5.0f);
            func_80037E84(D_800FD5F8[D_80077520], 0x3C);
            func_80037D4C(sp30, 6.0f);
            func_80037E84(sp30, 0x3C);
            break;
        case 2:
            D_800FD5F8[D_80077520] = func_8003834C(D_800B4190, (s32)D_800B41B0[D_80077520], 2, 0x70, 0x80, 0, -1);
            func_80037D4C(D_800FD5F8[D_80077520], -1.0f);
            func_80037DF4(D_800FD5F8[D_80077520], 0x70);
            break;
        case 3:
            D_800FD5F8[D_80077520] = func_8003834C(D_800B4190, (s32)D_800B41B0[D_80077520], 2, 0xA0, 0x80, 0, -1);
            func_80037AC4(D_800775A8, 0x50);
            D_800775A8 = func_8003834C(D_800B4188, D_800B41A4, 0xF, 0x80, 0x80, 0, -1);
            break;
        case 4:
            D_800FD5F8[D_80077520] = func_8003834C(D_800B4190, (s32)D_800B41B0[D_80077520], 1, 0xA0, 0x80, 0, -1);
        default:
            return 0;
    }
    return D_800FD5F8[D_80077520];
}

s32 func_8003FE58(s32, s32, s32);

void func_8003FE34(s32 arg0, s32 arg1) {
    func_8003FE58(arg0, 1, arg1);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8003FE58; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003FE58.s")
#endif

void Audio_CreateFrameTaskWrapper(void* arg0) {
    Audio_CreateFrameTask(arg0);
}

M2C_UNK func_80037AC4(s32, M2C_UNK);                /* extern */
extern u8 D_80077524;
extern s32 D_800FD64C;
extern s32 D_800FD650;

void func_80040738(void) {
    if (D_80077524 != 0) {
        func_80037AC4(D_800FD64C, 0x32);
        func_80037AC4(D_800FD650, 0x32);
    } else {
        func_80037AC4(D_800FD64C, 0x5A);
        func_80037AC4(D_800FD650, 0x5A);
    }
    D_800FD64C = 0;
    D_800FD650 = 0;
}
