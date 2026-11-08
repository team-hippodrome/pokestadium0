/* Stadium Zero fragment000_80C00. */

#include "global.h"

typedef struct AudioVoice81107E70 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ s32 addr;
    /* 0x08 */ char unk08[0x6];
    /* 0x0E */ u16 offset;
    /* 0x10 */ s16 count;
    /* 0x12 */ s16 wrapCount;
} AudioVoice81107E70; // size = 0x14

typedef struct AudioChannel81107E70 {
    /* 0x000 */ u8 active;
    /* 0x001 */ char unk001[0x2];
    /* 0x003 */ u8 bank;
    /* 0x004 */ u8 mode;
    /* 0x005 */ char unk005[0x1B];
    /* 0x020 */ s32 bufL;
    /* 0x024 */ s32 bufR;
    /* 0x028 */ char unk028[0x10];
    /* 0x038 */ AudioVoice81107E70 voices[2][5];
    /* 0x100 */ char unk100[0x58];
} AudioChannel81107E70; // size = 0x158

extern AudioChannel81107E70 D_81184110[];

typedef struct AudioCmd {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} AudioCmd; // size = 0x8

typedef struct Voice811077FC {
    /* 0x00 */ u32 active : 1;
    /* 0x00 */ u32 dirty : 1;
    /* 0x00 */ u32 unk00 : 30;
    /* 0x04 */ char unk04[2];
    /* 0x06 */ u8 unk06;
    /* 0x07 */ char unk07[0x11];
} Voice811077FC; // size = 0x18
extern Voice811077FC* D_81184288;

#ifdef NON_MATCHING
/* TODO: decompile func_81107390; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81107390.s")
#endif

#define SHL_8110(v, s, w) ((u32)(((u32)(v) & ((1 << (w)) - 1)) << (s)))
#define aLoadBuf_8110(pkt, c, dmem, count, addr)                                                  \
    {                                                                                              \
        AudioCmd* _a = (AudioCmd*)(pkt);                                                           \
        _a->w0 = (SHL_8110(c, 24, 8) | SHL_8110((count) >> 4, 16, 8) | SHL_8110(dmem, 0, 16));     \
        _a->w1 = (u32)(addr);                                                                      \
    }

void* func_81107634(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel) {
    aLoadBuf_8110(cmd++, 0x14, dmem, count, D_81184110[channel].bufL + offset * 2 + 0x80000000);
    aLoadBuf_8110(cmd++, 0x14, dmem + 0x1A0, count, D_81184110[channel].bufR + offset * 2 + 0x80000000);
    return cmd;
}

void* func_811076D0(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel) {
    aLoadBuf_8110(cmd++, 0x15, dmem, count, D_81184110[channel].bufL + offset * 2 + 0x80000000);
    aLoadBuf_8110(cmd++, 0x15, dmem + 0x1A0, count, D_81184110[channel].bufR + offset * 2 + 0x80000000);
    return cmd;
}

typedef struct AudioCfg811078D8 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ s16 passes;
    /* 0x0E */ s16 chunk;
    /* 0x10 */ s16 maxChunk;
    /* 0x12 */ s16 minChunk;
} AudioCfg811078D8;
extern AudioCfg811078D8 D_811858B8;
extern s32 D_811858E8;

void func_8110776C(s32 updateIndex, s32 voiceIndex) {
    s32 i;

    for (i = updateIndex + 1; i < D_811858B8.passes; i++) {
        if (!(&(D_81184288 + D_811858E8 * i)[voiceIndex])->dirty) {
            (&(D_81184288 + D_811858E8 * i)[voiceIndex])->active = 0;
        } else {
            break;
        }
    }
}

typedef struct Rec811077FC {
    /* 0x00 */ char unk00[0xB4];
    /* 0xB4 */ Voice811077FC voice;
} Rec811077FC; // size = 0xCC
extern Rec811077FC* D_81184664;
extern s32 D_811858E8;
void func_811077FC(u32 arg0) {
    s32 i;
    Voice811077FC* src;
    Voice811077FC* dst;

    for (i = 0; i < D_811858E8; i++) {
        src = &D_81184664[i].voice;
        dst = &D_81184288[D_811858E8 * arg0 + i];
        if (src->active) {
            *dst = *src;
            src->dirty = 0;
        } else {
            dst->active = 0;
        }
        src->unk06 = 0;
    }
}

extern s8 D_8118427B;
void func_81107390(s32, s32, s32);
AudioCmd* func_8110814C(s32*, s32, AudioCmd*, s32);
void func_811151C8(s32 arg0);
AudioCmd* func_811078D8(AudioCmd* arg0, s32* arg1, s32* arg2, s32 arg3) {
    AudioCmd* cmd = arg0;
    s32 i;
    s32 j;
    s32 chunk;
    s32 q;
    s32* buf;

    for (i = D_811858B8.passes; i > 0; i--) {
        func_811151C8(i - 1);
        func_811077FC(D_811858B8.passes - i);
    }
    buf = arg2;
    for (i = D_811858B8.passes; i > 0; i--) {
        if (i == 1) {
            chunk = arg3;
        } else {
            q = arg3 / i;
            if (q >= D_811858B8.maxChunk) {
                chunk = D_811858B8.maxChunk;
            } else if (D_811858B8.minChunk >= q) {
                chunk = D_811858B8.minChunk;
            } else {
                chunk = D_811858B8.chunk;
            }
        }
        for (j = 0; j < D_8118427B; j++) {
            if (D_81184110[j].unk001[0] != 0) {
                func_81107390(chunk, D_811858B8.passes - i, j);
            }
        }
        cmd = func_8110814C(buf, chunk, cmd, D_811858B8.passes - i);
        arg3 -= chunk;
        buf += chunk;
    }
    for (j = 0; j < D_8118427B; j++) {
        if (D_81184110[j].unk001[1] != 0) {
            D_81184110[j].unk001[1]--;
        }
        D_81184110[j].bank ^= 1;
    }
    *arg1 = cmd - arg0;
    return cmd;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81107AEC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81107AEC.s")
#endif

void* func_81107634(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel);
extern AudioChannel81107E70 D_81184110[];

void* func_81107E70(void* cmd, s16 channel, s16 slot) {
    AudioVoice81107E70* voice = &D_81184110[channel].voices[D_81184110[channel].bank][slot];

    cmd = func_81107634(cmd, 0x3E0, voice->offset, voice->count, channel);
    if (voice->wrapCount != 0) {
        cmd = func_81107634(cmd, voice->count + 0x3E0, 0, voice->wrapCount, channel);
    }
    return cmd;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81107F40; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81107F40.s")
#endif

void* func_811076D0(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel);

void* func_8110807C(void* cmd, s16 channel, s16 slot) {
    AudioVoice81107E70* voice = &D_81184110[channel].voices[D_81184110[channel].bank][slot];

    cmd = func_811076D0(cmd, 0x3E0, voice->offset, voice->count, channel);
    if (voice->wrapCount != 0) {
        cmd = func_811076D0(cmd, voice->count + 0x3E0, 0, voice->wrapCount, channel);
    }
    return cmd;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110814C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110814C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81108750; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81108750.s")
#endif

#define SHIFTL_81109(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
/* Emits the two-or-one command sequence as a single macro statement, like the libultra audio macros. */
#define AUDIO_CMDS_811092F4(cmd, arg1, arg2, count, arg4, arg5)                                          \
    do {                                                                                                 \
        if ((count) == 0) {                                                                              \
            AudioCmd* a = (cmd)++;                                                                       \
            a->w0 = SHIFTL_81109(2, 24, 8) | SHIFTL_81109(0x3C0, 0, 24);                                 \
            a->w1 = (u32)(arg2);                                                                         \
        } else {                                                                                         \
            {                                                                                            \
                AudioCmd* a = (cmd)++;                                                                   \
                a->w0 = SHIFTL_81109(8, 24, 8) | SHIFTL_81109(arg4, 0, 16);                              \
                a->w1 = SHIFTL_81109(0x3C0, 16, 16) | SHIFTL_81109(arg2, 0, 16);                         \
            }                                                                                            \
            {                                                                                            \
                AudioCmd* a = (cmd)++;                                                                   \
                a->w0 = SHIFTL_81109(5, 24, 8) | SHIFTL_81109(arg5, 16, 8) | SHIFTL_81109(count, 0, 16); \
                a->w1 = (u32)(*(s32*)((arg1) + 0xC) + 0x80000020);                                       \
            }                                                                                            \
        }                                                                                                \
    } while (0)
void* func_811092F4(AudioCmd* cmd, s8* arg1, s32 arg2, u16 count, u16 arg4, s32 arg5) {
    AUDIO_CMDS_811092F4(cmd, arg1, arg2, count, arg4, arg5);
    return cmd;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110938C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110938C.s")
#endif
