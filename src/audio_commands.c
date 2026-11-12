#include "pokemon.h"
#include "moves.h"
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
#include "audio_commands_types.h"
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

typedef struct SoundFileTable {
    /* 0x00 */ u32 num_files;
    /* 0x04 */ u32 offset1;
    /* 0x08 */ u32 wave_tables_offset;
    /* 0x0C */ u32 files[1];
} SoundFileTable; // size >= 0x10
extern SoundFileTable* D_800B4178;
extern u8* D_800B41C0[];

typedef struct AudioInitConfig {
    /* 0x00 */ s32 channels;
    /* 0x04 */ void* heap;
    /* 0x08 */ void* bank;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 outputRate;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
} AudioInitConfig; // size = 0x30

typedef struct AudioSeqEntry {
    /* 0x0 */ u32 offset;
    /* 0x4 */ u32 len;
} AudioSeqEntry; // size = 0x8

extern s32 D_80075C30;
extern u8 D_00B98000[];
extern u8 D_800B41F8[];
extern u8 D_800B4208[];
extern File1Header* D_800B4160;
extern File1Header* D_800B4164;
extern u32* D_800B4168;
extern u32* D_800B416C;
extern u32* D_800B4170;
extern struct Bank8003F96C* D_800B4174;
extern u32* D_800B417C;
extern s32 D_800B4180;
extern s32 D_800B4184;
extern s32 D_800B4188;
extern s32 D_800B418C;
extern s32 D_800B4190;
extern s32 D_800B4194;
extern s32 D_800B4198;
extern s32 D_800B419C;
extern s32 D_800B41A0;
extern s32 D_800B41A4;
extern s32 D_800B41A8;
extern u8* D_800B41B0[];
extern void* D_800B41D0[5];
extern u8* D_800B41F0;
extern s32 D_800FD5E8;
extern u8 D_800FD5EC;
extern s32 D_800FD5F0[2];
extern s32 D_800FD5F8[];
extern u8 D_800FD604;
extern u8 D_800FD605;
extern s32 D_800FD608;
extern s32 D_800FD610[];
extern u8 D_800FD620;
s32 D_800FD628[8];
s32 D_800FD648;
s32 D_800FD64C;
s32 D_800FD650;
s32 D_800FD654;
s32 D_800FD658[4];
extern s32 D_800FD668;
extern s32 D_800FD66C;
extern s32 D_800FD670[4];
extern s32 D_800FD680;
extern u32 D_800FD684;
extern u8 D_800FD68C;
extern s32 D_800B3CE4;
extern u8 D_80077520;
extern u8 D_80077524;
extern u8 D_80077528;
extern u8 D_80077534;
extern u8 D_80077538;
extern u8 D_8007753C;
s32 func_80058100(s32);
void func_80056610(void*, void*, s32);
void* func_8005C0D0(s32, s32, void*, s32, s32);
void Rom_InitDevice(s32);
void func_8004609C(u32, u8*, s32);
void func_80047FB0(u8*, s32, s32);
void func_80037F48(s32, s32);
void func_8003A710(u8*);
s32 func_800371A4(s8*);
void func_80046170(s32, s32);

s32 func_8003E1F8(void) {
    u32 i;
    u32* hdr;
    s32 num;
    s32 pad; // FAKE: unused stack word
    s32 rate;
    s32 ret;
    AudioInitConfig config;

    rate = func_80058100(32000);
    D_80075C30 = 0;
    func_80056610(D_800B41F8, D_800B4208, 300000);
    D_800B41F0 = func_8005C0D0(0, 0, D_800B41F8, 1, 0x55F0);
    Rom_InitDevice(0);

    D_800B4160 = func_8005C0D0(0, 0, D_800B41F8, 10, 4);
    func_8004609C((u32)D_00B98000, (u8*)D_800B4160, 0x28);
    Audio_RelocateOffsets((u32*)D_800B4160 + 1, (u32)D_00B98000, 9);

    hdr = D_800B4170 = func_8005C0D0(0, 0, D_800B41F8, 4, 4);
    func_8004609C(D_800B4160->wave_tables_offset, (u8*)hdr, 0xC);
    num = hdr[2];
    D_800B4164 = func_8005C0D0(0, 0, D_800B41F8, 4, num + 3);
    func_8004609C(D_800B4160->wave_tables_offset, (u8*)D_800B4164, num * 4 + 0xC);
    Audio_RelocateOffsets(&D_800B4164->offset1, D_800B4160->wave_tables_offset, 2);
    Audio_RelocateOffsets(D_800B4164->files, D_800B4160->wave_tables_offset, num);
    func_8004609C(D_800B4164->offset1, D_800B41F0, D_800B4164->wave_tables_offset - D_800B4164->offset1);
    D_800B4180 = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0x32C0);
    func_80047FB0(D_800B41F0, D_800B4180, 0x32C0);
    func_80037F48(D_800B4180, D_800B4164->wave_tables_offset);

    D_800B4168 = func_8005C0D0(0, 0, D_800B41F8, 4, 3);
    func_8004609C(D_800B4160->num_files, (u8*)D_800B4168, 0xC);
    Audio_RelocateOffsets(D_800B4168, D_800B4160->num_files, 3);
    func_8004609C(D_800B4168[0], D_800B41F0, D_800B4168[1] - D_800B4168[0]);
    D_800B41A0 = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0xAC0);
    func_80047FB0(D_800B41F0, D_800B41A0, 0xAC0);
    func_8003A710((u8*)D_800B41A0);
    func_8004609C(D_800B4168[1], D_800B41F0, D_800B4168[2] - D_800B4168[1]);
    D_800B4184 = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0xD60);
    func_80047FB0(D_800B41F0, D_800B4184, 0xD60);
    func_80037F48(D_800B4184, D_800B4168[2]);

    D_800B416C = func_8005C0D0(0, 0, D_800B41F8, 4, 3);
    func_8004609C(D_800B4160->files[0], (u8*)D_800B416C, 0xC);
    Audio_RelocateOffsets(D_800B416C, D_800B4160->files[0], 3);
    func_8004609C(D_800B416C[0], D_800B41F0, D_800B416C[1] - D_800B416C[0]);
    D_800B41A4 = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0xC80);
    func_80047FB0(D_800B41F0, D_800B41A4, 0xC80);
    func_8003A710((u8*)D_800B41A4);
    func_8004609C(D_800B416C[1], D_800B41F0, D_800B416C[2] - D_800B416C[1]);
    D_800B4188 = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0x2060);
    func_80047FB0(D_800B41F0, D_800B4188, 0x2060);
    func_80037F48(D_800B4188, D_800B416C[2]);

    func_8004609C(D_800B4160->files[2], (u8*)hdr, 0xC);
    num = hdr[0];
    D_800B4174 = func_8005C0D0(0, 0, D_800B41F8, 4, num + 3);
    func_8004609C(D_800B4160->files[2], (u8*)D_800B4174, num * 4 + 0xC);
    Audio_RelocateOffsets((u32*)D_800B4174 + 1, D_800B4160->files[2], num + 2);
    func_8004609C(((u32*)D_800B4174)[1], D_800B41F0, ((u32*)D_800B4174)[2] - ((u32*)D_800B4174)[1]);
    D_800B4190 = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0x1E20);
    func_80047FB0(D_800B41F0, D_800B4190, 0x1E20);
    func_80037F48(D_800B4190, ((u32*)D_800B4174)[2]);

    func_8004609C(D_800B4160->files[3], (u8*)hdr, 0xC);
    num = hdr[0];
    D_800B4178 = (SoundFileTable*) func_8005C0D0(0, 0, D_800B41F8, 4, num + 3);
    func_8004609C(D_800B4160->files[3], (u8*)D_800B4178, num * 4 + 0xC);
    Audio_RelocateOffsets(&D_800B4178->offset1, D_800B4160->files[3], num + 2);
    func_8004609C(D_800B4178->offset1, D_800B41F0, D_800B4178->wave_tables_offset - D_800B4178->offset1);
    D_800B4194 = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0x2EE0);
    func_80047FB0(D_800B41F0, D_800B4194, 0x2EE0);
    func_80037F48(D_800B4194, D_800B4178->wave_tables_offset);

    func_8004609C(D_800B4160->files[4], (u8*)hdr, 0xC);
    num = hdr[0];
    D_800B417C = func_8005C0D0(0, 0, D_800B41F8, 4, num + 3);
    func_8004609C(D_800B4160->files[4], (u8*)D_800B417C, num * 4 + 0xC);
    Audio_RelocateOffsets(D_800B417C + 1, D_800B4160->files[4], num + 2);
    func_8004609C(D_800B417C[1], D_800B41F0, D_800B417C[2] - D_800B417C[1]);
    D_800B4198 = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0x7D0);
    func_80047FB0(D_800B41F0, D_800B4198, 0x7D0);
    func_80037F48(D_800B4198, D_800B417C[2]);

    func_8004609C(D_800B4160->files[1], (u8*)D_800B4170, 0xC);
    Audio_RelocateOffsets(D_800B4170, D_800B4160->files[1], 3);
    func_8004609C(D_800B4170[0], D_800B41F0, D_800B4170[1] - D_800B4170[0]);
    D_800B41A8 = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0xC80);
    func_80047FB0(D_800B41F0, D_800B41A8, 0xC80);
    func_8003A710((u8*)D_800B41A8);
    func_8004609C(D_800B4170[1], D_800B41F0, D_800B4170[2] - D_800B4170[1]);
    D_800B418C = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0x5EE0);
    func_80047FB0(D_800B41F0, D_800B418C, 0x5EE0);
    func_80037F48(D_800B418C, D_800B4170[2]);

    D_800B41EC = func_8005C0D0(0, 0, D_800B41F8, 2, 0xB80);
    D_800FD688 = func_8005C0D0(0, 0, D_800B41F8, 1, 0x1388);
    func_8004609C(D_800B4160->files[5], (u8*)D_800FD688, D_800B4160->files[6] - D_800B4160->files[5]);
    D_800B41E4 = func_8005C0D0(0, 0, D_800B41F8, 1, 0x100);
    func_8004609C(D_800B4160->files[6], (u8*)D_800B41E4, 0x100);
    for (i = 0; i < 0x20; i++) {
        D_800B41E4[i].unk_00 += D_800B4160->files[6];
    }

    D_800B41E8 = func_8005C0D0(0, 0, D_800B41F8, 1, 0x2328);
    D_800B419C = (s32)func_8005C0D0(0, 0, D_800B41F8, 1, 0x8CA0);
    D_800B41B0[0] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x140);
    D_800B41B0[1] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x140);
    D_800B41B0[2] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x140);
    D_800B41C0[0] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x320);
    D_800B41C0[1] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x320);
    D_800B41C0[2] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x320);
    D_800B41D0[0] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x200);
    D_800B41D0[1] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x200);
    D_800B41D0[2] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x200);
    D_800B41D0[3] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x200);
    D_800B41D0[4] = func_8005C0D0(0, 0, D_800B41F8, 1, 0x200);

    D_800FD5E8 = 2;
    D_800FD5EC = 0;
    D_800FD5F0[0] = 200;
    D_800FD5F0[1] = 200;
    D_800FD608 = 0;
    D_800FD610[0] = 0;
    D_800FD610[1] = 0;
    D_800FD610[2] = 0;
    D_800FD610[3] = 0;
    D_800FD620 = 0;
    for (i = 0; i < 8; i++) {
        D_800FD628[i] = 0xFFFF;
    }
    D_800FD68C = 0;
    D_800FD5F8[0] = 0;
    D_800FD5F8[1] = 0;
    D_800FD5F8[2] = 0;
    D_80077520 = 0;
    D_800FD64C = 0;
    D_800FD650 = 0;
    D_800FD654 = 0;
    for (i = 0; i < 4; i++) {
        D_800FD658[i] = 0;
    }
    D_800FD668 = 0;
    D_800FD66C = 0;
    D_800B3CE4 = 0;
    D_800FD648 = 0;
    D_800FD680 = 0;
    D_800FD604 = 0;
    D_80077534 = 0;
    D_800FD670[0] = 0;
    D_800FD670[1] = 0;
    D_800FD670[2] = 0;
    D_800FD670[3] = 0;
    D_800FD605 = 0;
    D_800FD684 = 0;
    D_80077524 = 0;
    D_80077528 = 0;
    D_80077538 = 1;
    D_8007753C = 1;

    config.channels = 0x18;
    config.heap = D_800B41F8;
    config.bank = (void*)D_800B4184;
    config.unk_0C = ((s32*)D_800B41A0)[3];
    config.unk_10 = ((s32*)D_800B41A0)[2];
    config.outputRate = rate;
    config.unk_14 = 0x100;
    config.unk_1C = 0x400;
    config.unk_20 = 1;
    config.unk_24 = 0x30;
    config.unk_28 = 0x500;
    ret = func_800371A4((s8*)&config);
    func_80046170(2, 2);
    func_80046170(1, 3);
    return ret;
}

void Audio_StopAllSoundEffects(void);
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

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Audio_StartMusicTrack(u32 track_id) {
    u32 file_index[1]; // FAKE
    s32 pad; // FAKE
    s32 volume_scale[1]; // FAKE
    s32 file_size;
    u32 start;

    if (track_id == 0x1E) {
        return 0;
    }
    if (func_80037B7C(D_800FD608) != 0) {
        Audio_StopAllSoundEffects();
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

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Audio_FadeOutAll(s32 arg0) {
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

s32 func_8003FE58(u32, u32, u32);

void func_8003FE34(s32 arg0, s32 arg1) {
    func_8003FE58(arg0, 1, arg1);
}

extern u8 D_80077062[];
extern u8 D_8007755C;
extern u8 D_8007757C;
extern s32 D_800B4194;
extern u8 D_800FD604;
extern s32 D_800FD648;
extern s32 D_800FD64C;
extern s32 D_800FD650;
extern s32 D_800FD670[4];
void func_800386E4(s32, s32);
s32 func_800407B0(s32, s32, s32);
s32 func_8003FE58(u32 move_id, u32 species, u32 sound_kind) {
    s32 var;
    u32 size;
    s32 ret;
    s32 i;

    if (D_80077528 != 0) {
        return 0;
    }

    if (move_id >= 0xA7) {
        return 0;
    }

    switch (species) {
        case BLASTOISE:
            switch (move_id) {
                case WITHDRAW:
                    goto skip;

                case SKULL_BASH:
                    if (sound_kind == 4) {
                        goto skip;
                    }
                    break;
            }
            break;

        case PIKACHU:
            if (move_id == 0x39) {
                goto skip;
            }
            break;

        case GOLEM:
            switch (move_id) {
                case SURF:
                case THUNDERSHOCK:
                case RECOVER:
                case EGG_BOMB:
                case SKULL_BASH:
                case SPLASH:
                    goto skip;
            }
            break;

        case CHANSEY:
            if ((move_id == 0x27) || (move_id == 0x64) || (move_id == 0x70) || (move_id == 0x71) || (move_id == 0x73)) {
                goto skip;
            }
            break;

        case MACHAMP:
        case CLOYSTER:
        case ONIX:
        case EXEGGUTOR:
        case TAUROS:
        case ARTICUNO:
        case MOLTRES:
            goto skip;
    }

    for (i = 0; i < 4; i++) {
        if (func_80037B7C(D_800FD670[i]) != 0) {
            func_800386E4(D_800FD670[i], 0xF);
            D_800FD670[i] = 0;
        }
    }

skip:
    if (func_80037B7C(D_800FD648) != 0) {
        func_80037AC4(D_800FD648, 2);
        D_800FD648 = 0;
    }

    if (move_id == 0xA6) {
        var = sound_kind;
        sound_kind = 0xFF;
    }

    switch (sound_kind) {
        case 4:
            if (func_80037B7C(D_800FD650) != 0) {
                func_80037AC4(D_800FD650, 0x14);
                D_800FD650 = 0;
            }
            switch (move_id) {
                case DIG:
                    func_80043CE8(0x4B, 0.0f, 0x80);
                    var = 4;
                    break;

                case FLY:
                    func_80043CE8(0x4A, 0.0f, 0x80);
                    var = 4;
                    break;

                case RAZOR_WIND:
                case SOLARBEAM:
                case SKULL_BASH:
                case SKY_ATTACK:
                    func_80043CE8(0x52, 0.0f, 0x80);
                    var = 4;
                    break;

                default:
                    return 0;
            }
            break;

        case 0:
            if (func_80037B7C(D_800FD650) != 0) {
                func_80037AC4(D_800FD650, 0x14);
                D_800FD650 = 0;
            }
            if ((move_id == 0x2F) && (D_80077528 != 0)) {
                return 0;
            }
            switch (move_id) {
                case FLAMETHROWER:
                case DRAGON_RAGE:
                case FIRE_SPIN:
                    if (D_80077062[species * 8] == 1) {
                        var = 0;
                    } else {
                        var = 4;
                    }
                    break;

                case SELFDESTRUCT:
                case EXPLOSION:
                    func_80043CE8(0x23, 0.0f, 0x80);
                    var = 0;
                    D_8007757C = 1;
                    break;

                default:
                    var = 0;
            }
            break;

        case 1:
            if ((move_id == 6) && (D_8007755C == 0)) {
                func_80043CE8(0x53, 0.0f, 0x80);
            }
            switch (move_id) {
                case LEER: case SUPERSONIC: case BLIZZARD: case BUBBLEBEAM: case AURORA_BEAM: case HYPER_BEAM: case CONFUSE_RAY: case KINESIS:
                case GLARE:
                    if (func_80037B7C(D_800FD650) != 0) {
                        func_80037AC4(D_800FD650, 0x3C);
                        D_800FD650 = 0;
                    }
                    break;

                case BIND: case WRAP: case DISABLE: case FLAMETHROWER: case ABSORB: case MEGA_DRAIN: case RAZOR_LEAF: case PETAL_DANCE:
                case STRING_SHOT: case DRAGON_RAGE: case MIMIC: case FIRE_BLAST: case CONSTRICT: case DREAM_EATER: case LEECH_LIFE: case CONVERSION:
                    if (func_80037B7C(D_800FD650) != 0) {
                        func_80037AC4(D_800FD64C, 0x14);
                        D_800FD650 = 0;
                    }
                    break;

                default:
                    if (func_80037B7C(D_800FD650) != 0) {
                        func_80037AC4(D_800FD650, 2);
                        D_800FD650 = 0;
                    }
                    break;

                case VICEGRIP: case GUILLOTINE: case RAZOR_WIND: case GUST: case WHIRLWIND: case SING: case SURF: case POISONPOWDER:
                case STUN_SPORE: case SLEEP_POWDER: case THUNDERSHOCK: case THUNDERBOLT: case THUNDER_WAVE: case THUNDER: case HYPNOSIS: case NIGHT_SHADE:
                case SCREECH: case SMOKESCREEN: case HAZE: case SELFDESTRUCT: case SMOG: case WATERFALL: case 0x80: /* Clamp; the CLAMP name is taken by the macro */ case SWIFT:
                case POISON_GAS: case LOVELY_KISS: case SPORE: case FLASH: case PSYWAVE: case EXPLOSION:
                    break;
            }
            var = 1;
            break;

        case 2:
            if (func_80037B7C(D_800FD650) != 0) {
                func_80037AC4(D_800FD650, 0x14);
                D_800FD650 = 0;
            }
            switch (move_id) {
                case SWORDS_DANCE: case MIST: case GROWTH: case MEDITATE: case AGILITY: case MIMIC: case DOUBLE_TEAM: case RECOVER:
                case HARDEN: case MINIMIZE: case WITHDRAW: case DEFENSE_CURL: case BARRIER: case LIGHT_SCREEN: case HAZE: case REFLECT:
                case FOCUS_ENERGY: case AMNESIA: case SOFTBOILED: case TRANSFORM: case ACID_ARMOR: case REST: case SHARPEN: case SUBSTITUTE:
                    return 0;

                case POUND: case KARATE_CHOP: case DOUBLESLAP: case COMET_PUNCH: case PAY_DAY: case SCRATCH: case VICEGRIP: case GUILLOTINE:
                case CUT: case SLAM: case VINE_WHIP: case STOMP: case HORN_DRILL: case BITE: case COUNTER: case BONE_CLUB:
                case 0x80: /* Clamp; the CLAMP name is taken by the macro */ case FURY_SWIPES: case HYPER_FANG: case SUPER_FANG: case SLASH:
                    var = 2;
                    break;

                case FLAMETHROWER: case DRAGON_RAGE: case FIRE_SPIN:
                    if (D_80077062[species * 8] == 1) {
                        var = 0;
                    } else {
                        var = 4;
                    }
                    break;

                default:
                    var = 0;
                    break;
            }
            break;

        case 3:
            if (func_80037B7C(D_800FD650) != 0) {
                func_80037AC4(D_800FD650, 0x14);
                D_800FD650 = 0;
            }
            var = 0;
            break;

        case 5:
            switch (move_id) {
                case RAZOR_WIND: case GUST: case WHIRLWIND: case SING: case SURF: case POISONPOWDER: case STUN_SPORE: case SLEEP_POWDER:
                case THUNDERSHOCK: case THUNDERBOLT: case THUNDER_WAVE: case THUNDER: case HYPNOSIS: case SCREECH: case SMOKESCREEN: case CONFUSE_RAY:
                case HAZE: case SELFDESTRUCT: case SMOG: case 0x80: /* Clamp; the CLAMP name is taken by the macro */ case SWIFT: case POISON_GAS: case LOVELY_KISS: case SPORE:
                case FLASH: case EXPLOSION:
                    return 0;

                case SUPERSONIC:
                    if (func_80037B7C(D_800FD650) != 0) {
                        func_80037AC4(D_800FD650, 0x28);
                        D_800FD650 = 0;
                    }
                    return 0;

                default:
                    if (func_80037B7C(D_800FD650) != 0) {
                        func_80037AC4(D_800FD650, 0x3C);
                        D_800FD650 = 0;
                    }
                    return 0;
            }
            break;

        case 0xFF:
            break;

        default:
            return 0;
    }

    move_id--;
    D_800FD604++;
    D_800FD604 %= 3;

    if (move_id < D_800B4178->num_files - 1) {
        size = D_800B4178->files[move_id + 1] - D_800B4178->files[move_id];
    } else {
        size = D_800B4160->files[4] - D_800B4178->files[move_id];
    }

    func_8004609C(D_800B4178->files[move_id], D_800B41F0, size);
    func_80047FB0(D_800B41F0, (s32)D_800B41C0[D_800FD604], 0x320);
    func_8003A710(D_800B41C0[D_800FD604]);

    if (sound_kind == 0xFF) {
        ret = func_8003834C(D_800B4194, (s32)D_800B41C0[D_800FD604], var + 1, 0x80, 0x80, 0, -1);
    } else {
        D_800FD64C = func_8003834C(D_800B4194, (s32)D_800B41C0[D_800FD604], var + 1, 0x80, 0x80, 0, -1);
        ret = D_800FD64C;
    }

    if ((sound_kind == 0) || (sound_kind == 2) || (sound_kind == 3) || (sound_kind == 4)) {
        D_800FD650 = D_800FD64C;
    }

    if ((sound_kind == 0) || (sound_kind == 2)) {
        switch (move_id + 1) {
            case 0x85:
                func_8003834C(D_800B4188, D_800B41A4, 0xE, 0x80, 0x80, 0, -1);
                break;

            case 0x9C:
                func_800407B0(0x32, species, 0);
                break;

            case 0x2D:
            case 0x2E:
                func_8003F96C(species, 0);
                break;
        }
    }

    return ret;
}

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
