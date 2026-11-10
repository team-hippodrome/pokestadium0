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

/* Reverb ring-buffer view of an AudioChannel81107E70 entry (same 0x158-byte layout). */
typedef struct ReverbItem81107390 {
    /* 0x00 */ s16 numSamplesAfterDownsampling;
    /* 0x02 */ s16 chunkLen;
    /* 0x04 */ s16* toDownsampleLeft;
    /* 0x08 */ s16* toDownsampleRight;
    /* 0x0C */ s32 startPos;
    /* 0x10 */ s16 lengthA;
    /* 0x12 */ s16 lengthB;
} ReverbItem81107390; // size = 0x14

typedef struct Reverb81107390 {
    /* 0x000 */ u8 unk00;
    /* 0x001 */ u8 unk01;
    /* 0x002 */ u8 framesLeftToIgnore;
    /* 0x003 */ u8 curFrame;
    /* 0x004 */ u8 downsampleRate;
    /* 0x005 */ char unk05[0xF];
    /* 0x014 */ s32 nextRingBufferPos;
    /* 0x018 */ char unk18[0x4];
    /* 0x01C */ s32 bufSizePerChannel;
    /* 0x020 */ s16* ringBufferLeft;
    /* 0x024 */ s16* ringBufferRight;
    /* 0x028 */ char unk28[0x10];
    /* 0x038 */ ReverbItem81107390 items[2][5];
    /* 0x100 */ char unk100[0x58];
} Reverb81107390; // size = 0x158

void func_80056730(void*, s32);

void func_81107390(s32 chunkLen, s32 updateIndex, s32 reverbIndex) {
    ReverbItem81107390* item;
    s32 srcPos;
    s32 dstPos;
    s32 nSamples;
    s32 excessiveSamples;
    s32 pad[3]; // FAKE
    Reverb81107390* reverb;

    reverb = (Reverb81107390*)&D_81184110[reverbIndex];
    if (reverb->downsampleRate >= 3 && reverb->framesLeftToIgnore == 0) {
        item = &reverb->items[reverb->curFrame][updateIndex];
        func_80056730(item->toDownsampleLeft, 0x340);
        for (srcPos = 0, dstPos = 0; dstPos < item->lengthA / 2; srcPos += reverb->downsampleRate, dstPos++) {
            reverb->ringBufferLeft[item->startPos + dstPos] = item->toDownsampleLeft[srcPos];
            reverb->ringBufferRight[item->startPos + dstPos] = item->toDownsampleRight[srcPos];
        }
        for (dstPos = 0; dstPos < item->lengthB / 2; srcPos += reverb->downsampleRate, dstPos++) {
            reverb->ringBufferLeft[dstPos] = item->toDownsampleLeft[srcPos];
            reverb->ringBufferRight[dstPos] = item->toDownsampleRight[srcPos];
        }
    }
    item = &reverb->items[reverb->curFrame][updateIndex];
    nSamples = chunkLen / reverb->downsampleRate;
    excessiveSamples = (nSamples + reverb->nextRingBufferPos) - reverb->bufSizePerChannel;
    if (excessiveSamples < 0) {
        item->lengthA = nSamples * 2;
        item->lengthB = 0;
        item->startPos = reverb->nextRingBufferPos;
        reverb->nextRingBufferPos += nSamples;
    } else {
        item->lengthA = (nSamples - excessiveSamples) * 2;
        item->lengthB = excessiveSamples * 2;
        item->startPos = reverb->nextRingBufferPos;
        reverb->nextRingBufferPos = excessiveSamples;
    }
    item->numSamplesAfterDownsampling = nSamples;
    item->chunkLen = chunkLen;
}

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

typedef struct Reverb81107AEC {
    /* 0x000 */ u8 resampleFlags;
    /* 0x001 */ u8 unk01;
    /* 0x002 */ u8 framesLeftToIgnore;
    /* 0x003 */ u8 curFrame;
    /* 0x004 */ u8 downsampleRate;
    /* 0x005 */ char unk05[0x5];
    /* 0x00A */ u16 reverbGain;
    /* 0x00C */ u16 wetGain;
    /* 0x00E */ u16 resampleRate;
    /* 0x010 */ u16 leakRtl;
    /* 0x012 */ u16 leakLtr;
    /* 0x014 */ char unk14[0x14];
    /* 0x028 */ s32 resampleStateLeft;
    /* 0x02C */ s32 resampleStateRight;
    /* 0x030 */ char unk30[0x8];
    /* 0x038 */ ReverbItem81107390 items[2][5];
    /* 0x100 */ char unk100[0x58];
} Reverb81107AEC; // size = 0x158
#define ACMD_81107AEC(pkt, a, b)            \
    {                                       \
        AudioCmd* _a = (AudioCmd*)(pkt);    \
        _a->w0 = (a);                       \
        _a->w1 = (b);                       \
    }
void* func_81107AEC(AudioCmd* cmd, s32 bufLen, s16 reverbIndex, s16 updateIndex) {
    ReverbItem81107390* item;
    s16 startPad;
    s16 paddedLengthA;

    item = &((Reverb81107AEC*)&D_81184110[reverbIndex])->items[((Reverb81107AEC*)&D_81184110[reverbIndex])->curFrame][updateIndex];
    if (((Reverb81107AEC*)&D_81184110[reverbIndex])->downsampleRate == 1) {
        cmd = func_81107634(cmd, 0xC80, item->startPos, item->lengthA, reverbIndex);
        if (item->lengthB != 0) {
            cmd = func_81107634(cmd, item->lengthA + 0xC80, 0, item->lengthB, reverbIndex);
        }
        ACMD_81107AEC(cmd++, SHL_8110(0xC, 24, 8) | SHL_8110(0x34, 16, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->reverbGain, 0, 16), 0x0C800940);
        ACMD_81107AEC(cmd++, SHL_8110(0xC, 24, 8) | SHL_8110(0x34, 16, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->wetGain + 0x8000, 0, 16), 0x0C800C80);
    } else {
        startPad = (item->startPos & 7) * 2;
        paddedLengthA = (startPad + item->lengthA + 0xF) & ~0xF;
        cmd = func_81107634(cmd, 0x3E0, item->startPos - startPad / 2, 0x1A0, reverbIndex);
        if (item->lengthB != 0) {
            cmd = func_81107634(cmd, paddedLengthA + 0x3E0, 0, 0x1A0 - paddedLengthA, reverbIndex);
        }
        ACMD_81107AEC(cmd++, SHL_8110(8, 24, 8) | SHL_8110(startPad + 0x3E0, 0, 16), SHL_8110(0xC80, 16, 16) | SHL_8110(bufLen * 2, 0, 16));
        ACMD_81107AEC(cmd++, SHL_8110(5, 24, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->resampleRate, 0, 16) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->resampleFlags, 16, 8), ((Reverb81107AEC*)&D_81184110[reverbIndex])->resampleStateLeft + 0x80000000);
        ACMD_81107AEC(cmd++, SHL_8110(8, 24, 8) | SHL_8110(startPad + 0x580, 0, 16), SHL_8110(0xE20, 16, 16) | SHL_8110(bufLen * 2, 0, 16));
        ACMD_81107AEC(cmd++, SHL_8110(5, 24, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->resampleRate, 0, 16) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->resampleFlags, 16, 8), ((Reverb81107AEC*)&D_81184110[reverbIndex])->resampleStateRight + 0x80000000);
        ACMD_81107AEC(cmd++, SHL_8110(0xC, 24, 8) | SHL_8110(0x34, 16, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->reverbGain, 0, 16), 0x0C800940);
        ACMD_81107AEC(cmd++, SHL_8110(0xC, 24, 8) | SHL_8110(0x34, 16, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->wetGain + 0x8000, 0, 16), 0x0C800C80);
    }
    if ((((Reverb81107AEC*)&D_81184110[reverbIndex])->leakRtl != 0) || (((Reverb81107AEC*)&D_81184110[reverbIndex])->leakLtr != 0)) {
        ACMD_81107AEC(cmd++, SHL_8110(0xA, 24, 8) | SHL_8110(0xC80, 0, 16), SHL_8110(0x3E0, 16, 16) | SHL_8110(0x1A0, 0, 16));
        ACMD_81107AEC(cmd++, SHL_8110(0xC, 24, 8) | SHL_8110(0x1A, 16, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->leakRtl, 0, 16), 0x0E200C80);
        ACMD_81107AEC(cmd++, SHL_8110(0xC, 24, 8) | SHL_8110(0x1A, 16, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->leakLtr, 0, 16), 0x03E00E20);
    }
    return cmd;
}

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

void* func_811076D0(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel);

/* Loads a voice's samples (or points the mixer at them in RAM) as one macro statement, like AUDIO_CMDS_811092F4. */
// FAKE: the do-while (0) wrapper in this macro is only there for register allocation.
#define AUDIO_LOAD_VOICE_81107F40(cmd, tmp, ch, voice, slot, channel)                                  \
    do {                                                                                              \
        if ((ch)->mode == 1) {                                                                        \
            cmd = func_811076D0(cmd, 0xC80, (voice)->offset, (voice)->count, channel);                \
            if ((voice)->wrapCount != 0) {                                                            \
                cmd = func_811076D0(cmd, (voice)->count + 0xC80, 0, (voice)->wrapCount, channel);     \
            }                                                                                         \
        } else {                                                                                      \
            tmp = (cmd)++;                                                                            \
            tmp->w0 = 0x15340C80;                                                                     \
            tmp->w1 = (ch)->voices[(ch)->bank][slot].addr + 0x80000000;                               \
        }                                                                                             \
    } while (0)

void* func_81107F40(AudioCmd* cmd, s16 channel, s16 slot) {
    AudioVoice81107E70* voice = &D_81184110[channel].voices[D_81184110[channel].bank][slot];
    AudioCmd* c;

    AUDIO_LOAD_VOICE_81107F40(cmd, c, &D_81184110[channel], voice, slot, channel);
    D_81184110[channel].active = 0;
    return cmd;
}

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

typedef struct ZAdpcmLoop {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u32 count;
    /* 0x0C */ u32 pad;
    /* 0x10 */ s16 state[16];
} ZAdpcmLoop;

typedef struct ZAdpcmBook {
    /* 0x00 */ s32 order;
    /* 0x04 */ s32 npredictors;
    /* 0x08 */ s16 book[1];
} ZAdpcmBook;

typedef struct ZAudioBankSample {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 bit1 : 1;
    /* 0x00 */ u32 isPatched : 1;
    /* 0x00 */ u32 size : 24;
    /* 0x04 */ u8* sampleAddr;
    /* 0x08 */ ZAdpcmLoop* loop;
    /* 0x0C */ ZAdpcmBook* book;
} ZAudioBankSample;

typedef struct ZAudioBankSound {
    /* 0x00 */ ZAudioBankSample* sample;
} ZAudioBankSound;

typedef struct ZNoteSubEu {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 needsInit : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 envMixerNeedsInit : 1;
    /* 0x00 */ u8 stereoStrongRight : 1;
    /* 0x00 */ u8 stereoStrongLeft : 1;
    /* 0x00 */ u8 stereoHeadsetEffects : 1;
    /* 0x00 */ u8 usesHeadsetPanEffects : 1;
    /* 0x01 */ u8 reverbIndex : 3;
    /* 0x01 */ u8 bookOffset : 2;
    /* 0x01 */ u8 unk01 : 2;
    /* 0x01 */ u8 hasTwoAdpcmParts : 1;
    /* 0x02 */ u8 synthesisVolume;
    /* 0x03 */ u8 headsetPanRight;
    /* 0x04 */ u8 headsetPanLeft;
    /* 0x05 */ u8 reverbVol;
    /* 0x06 */ u16 targetVolLeft;
    /* 0x08 */ u16 targetVolRight;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 resamplingRateFixedPoint;
    /* 0x10 */ ZAudioBankSound* audioBankSound;
    /* 0x14 */ s16* filter;
} ZNoteSubEu;

typedef struct ZSynthesisBuffers {
    /* 0x00 */ s16 adpcmdecState[0x10];
    /* 0x20 */ s16 finalResampleState[0x10];
    /* 0x40 */ s16 mixEnvelopeState[0x10];
    /* 0x60 */ s16 filterBuffer[0x10];
} ZSynthesisBuffers;

typedef struct ZNoteSynthesisState {
    /* 0x00 */ u8 restart;
    /* 0x01 */ u8 sampleDmaIndex;
    /* 0x02 */ u8 prevHeadsetPanRight;
    /* 0x03 */ u8 prevHeadsetPanLeft;
    /* 0x04 */ u8 reverbVol;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u16 samplePosFrac;
    /* 0x08 */ s32 samplePosInt;
    /* 0x0C */ ZSynthesisBuffers* synthesisBuffers;
    /* 0x10 */ s16 curVolLeft;
    /* 0x12 */ s16 curVolRight;
} ZNoteSynthesisState;

typedef struct ZNote {
    /* 0x00 */ char unk00[0xB4];
    /* 0xB4 */ ZNoteSubEu noteSubEu;
} ZNote; // size = 0xCC

void* func_811092F4(AudioCmd*, s8*, s32, u16, u16, s32);
extern s16 D_81136A58[];
u8* func_8110C2D8(u8*, s32, s32, u8*, u32);
AudioCmd* func_8110938C(AudioCmd*, ZNoteSubEu*, ZNoteSynthesisState*, s32, u16, s32, s32);

#define ZALIGN(val, amnt) (((val) + (1 << amnt) - 1) & ~((1 << amnt) - 1))
#define ZSHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define ZV2P(addr) ((u8*)(addr) - 0x80000000U)
#define ZCMD(pkt, a, b)            \
    {                              \
        AudioCmd* _a = (AudioCmd*)(pkt);      \
        _a->w0 = (a);              \
        _a->w1 = (u32)(b);         \
    }
#define zLoadBuffer(pkt, s, d, c) ZCMD(pkt, ZSHIFTL(0x14, 24, 8) | ZSHIFTL((c) >> 4, 16, 8) | ZSHIFTL(d, 0, 16), s)
#define zSetBuffer(pkt, f, i, o, c) ZCMD(pkt, ZSHIFTL(8, 24, 8) | ZSHIFTL(f, 16, 8) | ZSHIFTL(i, 0, 16), ZSHIFTL(o, 16, 16) | ZSHIFTL(c, 0, 16))
#define zADPCMdec(pkt, f, s) ZCMD(pkt, ZSHIFTL(1, 24, 8) | ZSHIFTL(f, 16, 8), s)
#define zS8Dec(pkt, f, s) ZCMD(pkt, ZSHIFTL(0x17, 24, 8) | ZSHIFTL(f, 16, 8), s)
#define zDMEMMove(pkt, i, o, c) ZCMD(pkt, ZSHIFTL(0x0A, 24, 8) | ZSHIFTL(i, 0, 24), ZSHIFTL(o, 16, 16) | ZSHIFTL(c, 0, 16))
#define zClearBuffer(pkt, d, c) ZCMD(pkt, ZSHIFTL(2, 24, 8) | ZSHIFTL(d, 0, 24), c)
#define zSetLoop(pkt, a) ZCMD(pkt, ZSHIFTL(0x0F, 24, 8), a)
#define zLoadADPCM(pkt, c, d) ZCMD(pkt, ZSHIFTL(0x0B, 24, 8) | ZSHIFTL(c, 0, 24), d)
#define zDownsampleHalf(pkt, c, i, o) ZCMD(pkt, ZSHIFTL(0x11, 24, 8) | ZSHIFTL(c, 0, 16), ZSHIFTL(i, 16, 16) | ZSHIFTL(o, 0, 16))
#define zUnknown25(pkt, op, f, c, o, i) ZCMD(pkt, ZSHIFTL(op, 24, 8) | ZSHIFTL(f, 16, 8) | ZSHIFTL(c, 0, 16), ZSHIFTL(o, 16, 16) | ZSHIFTL(i, 0, 16))
#define zHiLoGain(pkt, g, buflen, i) ZCMD(pkt, ZSHIFTL(0x18, 24, 8) | ZSHIFTL(g, 16, 8) | ZSHIFTL(buflen, 0, 16), ZSHIFTL(i, 16, 16))
#define zFilter(pkt, f, countOrBuf, addr) ZCMD(pkt, ZSHIFTL(0x1B, 24, 8) | ZSHIFTL(f, 16, 8) | ZSHIFTL(countOrBuf, 0, 16), addr)

AudioCmd* func_81108750(s32 noteIndex, ZNoteSubEu* noteSubEu, ZNoteSynthesisState* synthesisState, s16* aiBuf,
                        s32 bufLen, AudioCmd* cmd, s32 updateIndex) {
    UNUSED s32 pad0[3]; // FAKE
    ZAudioBankSample* audioBookSample;
    ZAdpcmLoop* loopInfo;
    s16* curLoadedBook;
    UNUSED u8 padEU[0x04]; // FAKE
    UNUSED u8 pad8[0x04]; // FAKE
    s32 noteFinished;
    s32 restart;
    s32 flags;
    u16 resamplingRateFixedPoint;
    s32 nSamplesToLoad;
    UNUSED u8 pad7[0x0c]; // FAKE
    s32 sp130;
    UNUSED s32 tempBufLen; // FAKE
    UNUSED u32 pad9; // FAKE
    s32 t0;
    u8* sampleAddr;
    s32 s6;
    s32 samplesLenAdjusted;
    s32 nAdpcmSamplesProcessed;
    s32 endPos;
    s32 nSamplesToProcess;
    UNUSED s32 samplesLenInt; // FAKE
    s32 s2;
    s32 leftRight;
    s32 s5;
    u32 samplesLenFixedPoint;
    s32 s3;
    s32 nSamplesInThisIteration;
    u32 a3;
    u8* v0_2;
    s32 unk_s6;
    s32 s5Aligned;
    s32 sp88;
    s32 sp84;
    u32 temp;
    s32 nParts;
    s32 curPart;
    s32 aligned;
    UNUSED u32 padSH1; // FAKE
    s32 resampledTempLen;
    u16 noteSamplesDmemAddrBeforeResampling;
    UNUSED u32 padSH2; // FAKE
    s16 addr;
    u8 synthesisVolume;
    u32 nEntries;
    ZNote* note;
    u16 sp56;

    curLoadedBook = NULL;
    note = (ZNote*)&D_81184664[noteIndex];
    if (noteSubEu->audioBankSound != NULL) {
        flags = 0;
        if (noteSubEu->needsInit == TRUE) {
            flags = 1;
            synthesisState->restart = 0;
            synthesisState->samplePosInt = 0;
            synthesisState->samplePosFrac = 0;
            synthesisState->curVolLeft = 0;
            synthesisState->curVolRight = 0;
            synthesisState->prevHeadsetPanRight = 0;
            synthesisState->prevHeadsetPanLeft = 0;
            synthesisState->reverbVol = noteSubEu->reverbVol;
            synthesisState->unk5 = 0;
            note->noteSubEu.finished = 0;
        }

        resamplingRateFixedPoint = noteSubEu->resamplingRateFixedPoint;
        nParts = noteSubEu->hasTwoAdpcmParts + 1;
        samplesLenFixedPoint = (resamplingRateFixedPoint * bufLen * 2) + synthesisState->samplePosFrac;
        nSamplesToLoad = (samplesLenFixedPoint >> 0x10);
        synthesisState->samplePosFrac = samplesLenFixedPoint & 0xFFFF;

        if ((synthesisState->unk5 == 1) && (nParts == 2)) {
        } else if ((synthesisState->unk5 == 2) && (nParts == 1)) {
        } else {
            sp56 = 0;
        }

        synthesisState->unk5 = nParts;

        audioBookSample = noteSubEu->audioBankSound->sample;
        loopInfo = audioBookSample->loop;
        endPos = loopInfo->end;
        sampleAddr = audioBookSample->sampleAddr;
        resampledTempLen = 0;
        for (curPart = 0; curPart < nParts; curPart++) {
            nAdpcmSamplesProcessed = 0;
            s5 = 0;

            if (nParts == 1) {
                samplesLenAdjusted = nSamplesToLoad;
            } else if (nSamplesToLoad & 1) {
                samplesLenAdjusted = (nSamplesToLoad & ~1) + (curPart * 2);
            } else {
                samplesLenAdjusted = nSamplesToLoad;
            }

            if (audioBookSample->codec == 0) {
                if (curLoadedBook != audioBookSample->book->book) {
                    switch (noteSubEu->bookOffset) {
                        case 1:
                            curLoadedBook = D_81136A58 + 1;
                            break;
                        case 2:
                        case 3:
                        default:
                            curLoadedBook = audioBookSample->book->book;
                            break;
                    }
                    nEntries = 16 * audioBookSample->book->order * audioBookSample->book->npredictors;
                    zLoadADPCM(cmd++, nEntries, ZV2P(curLoadedBook));
                }
            }

            while (nAdpcmSamplesProcessed != samplesLenAdjusted) {
                s32 samplesRemaining;
                s32 s0;

                noteFinished = FALSE;
                restart = FALSE;
                s5Aligned = 0;
                s2 = synthesisState->samplePosInt & 0xf;
                samplesRemaining = endPos - synthesisState->samplePosInt;
                nSamplesToProcess = samplesLenAdjusted - nAdpcmSamplesProcessed;

                if (s2 == 0 && synthesisState->restart == FALSE) {
                    s2 = 16;
                }
                s6 = 16 - s2;
                if (nSamplesToProcess < samplesRemaining) {
                    t0 = (nSamplesToProcess - s6 + 0xf) / 16;
                    s0 = t0 * 16;
                    s3 = s6 + s0 - nSamplesToProcess;
                } else {
                    s0 = samplesRemaining - s6;
                    s3 = 0;
                    if (s0 <= 0) {
                        s0 = 0;
                        s6 = samplesRemaining;
                    }
                    t0 = (s0 + 0xf) / 16;
                    if (loopInfo->count != 0) {
                        restart = 1;
                    } else {
                        noteFinished = 1;
                    }
                }
                switch (audioBookSample->codec) {
                    case 0:
                        unk_s6 = 9;
                        sp88 = 0x10;
                        sp84 = 0;
                        break;
                    case 1:
                        unk_s6 = 0x10;
                        sp88 = 0x10;
                        sp84 = 0;
                        break;
                    case 2:
                        goto skip;
                }
                if (t0 != 0) {
                    temp = (synthesisState->samplePosInt + sp88 - s2) / 16;
                    if (audioBookSample->medium == 0) {
                        v0_2 = sp84 + (temp * unk_s6) + sampleAddr;
                    } else {
                        v0_2 = func_8110C2D8(sp84 + (temp * unk_s6) + sampleAddr, ZALIGN(t0 * unk_s6 + 16, 4), flags,
                                             &synthesisState->sampleDmaIndex, audioBookSample->medium);
                    }

                    a3 = ((u32)v0_2 & 0xf);
                    aligned = ZALIGN(t0 * unk_s6 + 16, 4);
                    addr = 0x940 - aligned;
                    zLoadBuffer(cmd++, ZV2P(v0_2 - a3), addr, ZALIGN(t0 * unk_s6 + 16, 4));
                } else {
                    s0 = 0;
                    a3 = 0;
                }
                if (synthesisState->restart != FALSE) {
                    zSetLoop(cmd++, ZV2P(audioBookSample->loop->state));
                    flags = 2;
                    synthesisState->restart = FALSE;
                }
                nSamplesInThisIteration = s0 + s6 - s3;
                if (nAdpcmSamplesProcessed == 0) {
                    sp130 = s2 * 2;
                } else {
                    s5Aligned = ZALIGN(s5 + 16, 4);
                }
                switch (audioBookSample->codec) {
                    case 0:
                        aligned = ZALIGN(t0 * unk_s6 + 16, 4);
                        addr = 0x940 - aligned;
                        zSetBuffer(cmd++, 0, addr + a3, 0x580 + s5Aligned, s0 * 2);
                        zADPCMdec(cmd++, flags, ZV2P(synthesisState->synthesisBuffers->adpcmdecState));
                        break;
                    case 1:
                        aligned = ZALIGN(t0 * unk_s6 + 16, 4);
                        addr = 0x940 - aligned;
                        zSetBuffer(cmd++, 0, addr + a3, 0x580 + s5Aligned, s0 * 2);
                        zS8Dec(cmd++, flags, ZV2P(synthesisState->synthesisBuffers->adpcmdecState));
                        break;
                }
                if (nAdpcmSamplesProcessed != 0) {
                    zDMEMMove(cmd++, 0x580 + s5Aligned + (s2 * 2), 0x580 + s5, nSamplesInThisIteration * 2);
                }
                nAdpcmSamplesProcessed += nSamplesInThisIteration;
                switch (flags) {
                    case 1:
                        sp130 = 0x20;
                        s5 = (s0 + 0x10) * 2;
                        break;
                    case 2:
                        s5 = (nSamplesInThisIteration) * 2 + s5;
                        break;
                    default:
                        if (s5 != 0) {
                            s5 = (nSamplesInThisIteration) * 2 + s5;
                        } else {
                            s5 = (s2 + (nSamplesInThisIteration)) * 2;
                        }
                        break;
                }
                flags = 0;
            skip:
                if (noteFinished) {
                    zClearBuffer(cmd++, 0x580 + s5, (samplesLenAdjusted - nAdpcmSamplesProcessed) * 2);
                    noteSubEu->finished = 1;
                    note->noteSubEu.finished = 1;
                    func_8110776C(updateIndex, noteIndex);
                    break;
                }
                if (restart != 0) {
                    synthesisState->restart = TRUE;
                    synthesisState->samplePosInt = loopInfo->start;
                } else {
                    synthesisState->samplePosInt += nSamplesToProcess;
                }
            }

            switch (nParts) {
                case 1:
                    noteSamplesDmemAddrBeforeResampling = 0x580 + sp130;
                    break;
                case 2:
                    switch (curPart) {
                        case 0:
                            zDownsampleHalf(cmd++, ZALIGN(samplesLenAdjusted / 2, 3), 0x580 + sp130, 0x3E0);
                            resampledTempLen = samplesLenAdjusted;
                            noteSamplesDmemAddrBeforeResampling = 0x3E0;
                            if (noteSubEu->finished != FALSE) {
                                zClearBuffer(cmd++, noteSamplesDmemAddrBeforeResampling + resampledTempLen, samplesLenAdjusted + 0x10);
                            }
                            break;
                        case 1:
                            zDownsampleHalf(cmd++, ZALIGN(samplesLenAdjusted / 2, 3), 0x580 + sp130, resampledTempLen + 0x3E0);
                            break;
                    }
            }
            if (noteSubEu->finished != FALSE) {
                break;
            }
        }

        flags = 0;
        if (noteSubEu->needsInit == TRUE) {
            flags = 1;
            noteSubEu->needsInit = FALSE;
        }
        cmd = func_811092F4(cmd, (s8*)synthesisState, bufLen * 2, resamplingRateFixedPoint,
                            noteSamplesDmemAddrBeforeResampling, sp56 | flags);

        if (noteSubEu->bookOffset == 3) {
            zUnknown25(cmd++, 0x19, 0, bufLen * 2, 0x3C0, 0x3C0);
        }
        if (noteSubEu->bookOffset == 2) {
            zUnknown25(cmd++, 0x03, 0, bufLen * 2, 0x3C0, 0x3C0);
        }

        synthesisVolume = noteSubEu->synthesisVolume;
        if (synthesisVolume != 0) {
            if (synthesisVolume < 0x10) {
                synthesisVolume = 0x10;
            }
            zHiLoGain(cmd++, synthesisVolume, (bufLen + 0x10) * 2, 0x3C0);
        }

        if (noteSubEu->filter) {
            zFilter(cmd++, 2, bufLen * 2, noteSubEu->filter);
            zFilter(cmd++, flags, 0x3C0, synthesisState->synthesisBuffers->filterBuffer);
        }

        if (noteSubEu->headsetPanRight != 0 || synthesisState->prevHeadsetPanRight != 0) {
            leftRight = 1;
        } else if (noteSubEu->headsetPanLeft != 0 || synthesisState->prevHeadsetPanLeft != 0) {
            leftRight = 2;
        } else {
            leftRight = 0;
        }
        cmd = func_8110938C(cmd, noteSubEu, synthesisState, bufLen, 0x3C0, leftRight, flags);
    }
    return cmd;
}

#define SHIFTL_81109(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
/* Emits the two-or-one command sequence as a single macro statement, like the libultra audio macros. */
// FAKE: the do-while (0) wrapper in this macro is only there for register allocation.
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
