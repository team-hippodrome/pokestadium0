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

/**
 * Sets up the next reverb ring buffer item for update `update_index` of reverb `reverb_index`. Zelda 64 audio driver (synthesis.c), same position and shape.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSynth_InitNextRingBuf(s32 chunkLen, s32 update_index, s32 reverb_index) {
    ReverbItem81107390* item;
    s32 src_pos;
    s32 dst_pos;
    s32 n_samples;
    s32 excessive_samples;
    s32 pad[3]; // FAKE
    Reverb81107390* reverb;

    reverb = (Reverb81107390*)&D_81184110[reverb_index];
    if (reverb->downsampleRate >= 3 && reverb->framesLeftToIgnore == 0) {
        item = &reverb->items[reverb->curFrame][update_index];
        func_80056730(item->toDownsampleLeft, 0x340);
        for (src_pos = 0, dst_pos = 0; dst_pos < item->lengthA / 2; src_pos += reverb->downsampleRate, dst_pos++) {
            reverb->ringBufferLeft[item->startPos + dst_pos] = item->toDownsampleLeft[src_pos];
            reverb->ringBufferRight[item->startPos + dst_pos] = item->toDownsampleRight[src_pos];
        }
        for (dst_pos = 0; dst_pos < item->lengthB / 2; src_pos += reverb->downsampleRate, dst_pos++) {
            reverb->ringBufferLeft[dst_pos] = item->toDownsampleLeft[src_pos];
            reverb->ringBufferRight[dst_pos] = item->toDownsampleRight[src_pos];
        }
    }
    item = &reverb->items[reverb->curFrame][update_index];
    n_samples = chunkLen / reverb->downsampleRate;
    excessive_samples = (n_samples + reverb->nextRingBufferPos) - reverb->bufSizePerChannel;
    if (excessive_samples < 0) {
        item->lengthA = n_samples * 2;
        item->lengthB = 0;
        item->startPos = reverb->nextRingBufferPos;
        reverb->nextRingBufferPos += n_samples;
    } else {
        item->lengthA = (n_samples - excessive_samples) * 2;
        item->lengthB = excessive_samples * 2;
        item->startPos = reverb->nextRingBufferPos;
        reverb->nextRingBufferPos = excessive_samples;
    }
    item->numSamplesAfterDownsampling = n_samples;
    item->chunkLen = chunkLen;
}

#define SHL_8110(v, s, w) ((u32)(((u32)(v) & ((1 << (w)) - 1)) << (s)))
#define aLoadBuf_8110(pkt, c, dmem, count, addr)                                                  \
    {                                                                                              \
        AudioCmd* _a = (AudioCmd*)(pkt);                                                           \
        _a->w0 = (SHL_8110(c, 24, 8) | SHL_8110((count) >> 4, 16, 8) | SHL_8110(dmem, 0, 16));     \
        _a->w1 = (u32)(addr);                                                                      \
    }

/**
 * Loads part of a reverb ring buffer into DMEM (both channels). Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void* AudioSynth_LoadRingBufferPart(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel) {
    aLoadBuf_8110(cmd++, 0x14, dmem, count, D_81184110[channel].bufL + offset * 2 + 0x80000000);
    aLoadBuf_8110(cmd++, 0x14, dmem + 0x1A0, count, D_81184110[channel].bufR + offset * 2 + 0x80000000);
    return cmd;
}

/**
 * Saves part of DMEM back into a reverb ring buffer (both channels). Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void* AudioSynth_SaveRingBufferPart(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel) {
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

/**
 * Marks voice `voice_index` as not dirty in the later updates of this frame. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSynth_DisableSampleStates(s32 update_index, s32 voice_index) {
    s32 i;

    for (i = update_index + 1; i < D_811858B8.passes; i++) {
        if (!(&(D_81184288 + D_811858E8 * i)[voice_index])->dirty) {
            (&(D_81184288 + D_811858E8 * i)[voice_index])->active = 0;
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
/**
 * Copies each note's sample state into the per-update state. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSynth_SyncSampleStates(u32 arg0) {
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
void AudioSynth_InitNextRingBuf(s32, s32, s32);
AudioCmd* AudioSynth_DoOneAudioUpdate(s32*, s32, AudioCmd*, s32);
void AudioSeq_ProcessSequences(s32 arg0);
/**
 * Builds the audio command list for one frame of `arg3` samples. Zelda 64 audio driver.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
AudioCmd* AudioSynth_Update(AudioCmd* arg0, s32* arg1, s32* arg2, s32 arg3) {
    AudioCmd* cmd = arg0;
    s32 i;
    s32 j;
    s32 chunk;
    s32 q;
    s32* buf;

    for (i = D_811858B8.passes; i > 0; i--) {
        AudioSeq_ProcessSequences(i - 1);
        AudioSynth_SyncSampleStates(D_811858B8.passes - i);
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
                AudioSynth_InitNextRingBuf(chunk, D_811858B8.passes - i, j);
            }
        }
        cmd = AudioSynth_DoOneAudioUpdate(buf, chunk, cmd, D_811858B8.passes - i);
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
/**
 * Loads a reverb's ring buffer samples for this update. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void* AudioSynth_LoadReverbSamples(AudioCmd* cmd, s32 bufLen, s16 reverbIndex, s16 update_index) {
    ReverbItem81107390* item;
    s16 startPad;
    s16 padded_length_a;

    item = &((Reverb81107AEC*)&D_81184110[reverbIndex])->items[((Reverb81107AEC*)&D_81184110[reverbIndex])->curFrame][update_index];
    if (((Reverb81107AEC*)&D_81184110[reverbIndex])->downsampleRate == 1) {
        cmd = AudioSynth_LoadRingBufferPart(cmd, 0xC80, item->startPos, item->lengthA, reverbIndex);
        if (item->lengthB != 0) {
            cmd = AudioSynth_LoadRingBufferPart(cmd, item->lengthA + 0xC80, 0, item->lengthB, reverbIndex);
        }
        ACMD_81107AEC(cmd++, SHL_8110(0xC, 24, 8) | SHL_8110(0x34, 16, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->reverbGain, 0, 16), 0x0C800940);
        ACMD_81107AEC(cmd++, SHL_8110(0xC, 24, 8) | SHL_8110(0x34, 16, 8) | SHL_8110(((Reverb81107AEC*)&D_81184110[reverbIndex])->wetGain + 0x8000, 0, 16), 0x0C800C80);
    } else {
        startPad = (item->startPos & 7) * 2;
        padded_length_a = (startPad + item->lengthA + 0xF) & ~0xF;
        cmd = AudioSynth_LoadRingBufferPart(cmd, 0x3E0, item->startPos - startPad / 2, 0x1A0, reverbIndex);
        if (item->lengthB != 0) {
            cmd = AudioSynth_LoadRingBufferPart(cmd, padded_length_a + 0x3E0, 0, 0x1A0 - padded_length_a, reverbIndex);
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

void* AudioSynth_LoadRingBufferPart(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel);
extern AudioChannel81107E70 D_81184110[];

void* AudioSynth_LoadRingBuffer1AtTemp(void* cmd, s16 channel, s16 slot) {
    AudioVoice81107E70* voice = &D_81184110[channel].voices[D_81184110[channel].bank][slot];

    cmd = AudioSynth_LoadRingBufferPart(cmd, 0x3E0, voice->offset, voice->count, channel);
    if (voice->wrapCount != 0) {
        cmd = AudioSynth_LoadRingBufferPart(cmd, voice->count + 0x3E0, 0, voice->wrapCount, channel);
    }
    return cmd;
}

void* AudioSynth_SaveRingBufferPart(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel);

/* Loads a voice's samples (or points the mixer at them in RAM) as one macro statement, like AUDIO_CMDS_811092F4. */
// FAKE: the do-while (0) wrapper in this macro is only there for register allocation.
#define AUDIO_LOAD_VOICE_81107F40(cmd, tmp, ch, voice, slot, channel)                                  \
    do {                                                                                              \
        if ((ch)->mode == 1) {                                                                        \
            cmd = AudioSynth_SaveRingBufferPart(cmd, 0xC80, (voice)->offset, (voice)->count, channel);                \
            if ((voice)->wrapCount != 0) {                                                            \
                cmd = AudioSynth_SaveRingBufferPart(cmd, (voice)->count + 0xC80, 0, (voice)->wrapCount, channel);     \
            }                                                                                         \
        } else {                                                                                      \
            tmp = (cmd)++;                                                                            \
            tmp->w0 = 0x15340C80;                                                                     \
            tmp->w1 = (ch)->voices[(ch)->bank][slot].addr + 0x80000000;                               \
        }                                                                                             \
    } while (0)

void* AudioSynth_SaveReverbSamples(AudioCmd* cmd, s16 channel, s16 slot) {
    AudioVoice81107E70* voice = &D_81184110[channel].voices[D_81184110[channel].bank][slot];
    AudioCmd* c;

    AUDIO_LOAD_VOICE_81107F40(cmd, c, &D_81184110[channel], voice, slot, channel);
    D_81184110[channel].active = 0;
    return cmd;
}

void* AudioSynth_SaveRingBufferPart(AudioCmd* cmd, u16 dmem, u16 offset, s32 count, s32 channel);

void* AudioSynth_SaveRingBuffer1AtTemp(void* cmd, s16 channel, s16 slot) {
    AudioVoice81107E70* voice = &D_81184110[channel].voices[D_81184110[channel].bank][slot];

    cmd = AudioSynth_SaveRingBufferPart(cmd, 0x3E0, voice->offset, voice->count, channel);
    if (voice->wrapCount != 0) {
        cmd = AudioSynth_SaveRingBufferPart(cmd, voice->count + 0x3E0, 0, voice->wrapCount, channel);
    }
    return cmd;
}

#define ZSHIFTL_814C(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
typedef struct Sub8110814C {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 unk00_1 : 7;
    /* 0x01 */ u8 reverbIndex : 3;
    /* 0x01 */ u8 unk01_3 : 5;
    /* 0x02 */ char unk02[0x16];
} Sub8110814C; // size = 0x18

typedef struct Note8110814C {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ char synthesisState[0xBC];
} Note8110814C; // size = 0xCC

typedef struct Reverb8110814C {
    /* 0x000 */ u8 resampleFlags;
    /* 0x001 */ u8 useReverb;
    /* 0x002 */ char unk002[0x3];
    /* 0x005 */ s8 unk_05;
    /* 0x006 */ char unk006[0x2];
    /* 0x008 */ u16 unk_08;
    /* 0x00A */ char unk00A[0xF6];
    /* 0x100 */ s16* filterLeft;
    /* 0x104 */ s16* filterRight;
    /* 0x108 */ s16* filterLeftState;
    /* 0x10C */ s16* filterRightState;
    /* 0x110 */ char unk110[0x48];
} Reverb8110814C; // size = 0x158

extern s8 D_8118427A;
void* AudioSynth_LoadReverbSamples(AudioCmd* cmd, s32 bufLen, s16 reverbIndex, s16 updateIndex);
void* AudioSynth_LoadRingBuffer1AtTemp(void* cmd, s16 channel, s16 slot);
void* AudioSynth_SaveReverbSamples(AudioCmd* cmd, s16 channel, s16 slot);
void* AudioSynth_SaveRingBuffer1AtTemp(void* cmd, s16 channel, s16 slot);
struct ZNoteSubEu;
struct ZNoteSynthesisState;
AudioCmd* AudioSynth_ProcessSample(s32 noteIndex, struct ZNoteSubEu* noteSubEu, struct ZNoteSynthesisState* synthesisState, s16* aiBuf, s32 bufLen, AudioCmd* cmd, s32 updateIndex);

/**
 * Builds the commands for one audio update: reverbs, every note, then the mix into the AI buffer. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
AudioCmd* AudioSynth_DoOneAudioUpdate(s32* ai_buf, s32 aiBufLen, AudioCmd* cmd, s32 updateIndex) {
    u8 sp94[0x3C];
    Sub8110814C* noteSubEu;
    UNUSED Sub8110814C* note_sub_eu2; // FAKE: unused, keeps the frame size
    s16 count;
    s16 reverbIndex;
    s32 i;

    count = 0;
    if (D_8118427B == 0) {
        for (i = 0; i < D_811858E8; i++) {
            if (((Sub8110814C*)D_81184288)[D_811858E8 * updateIndex + i].enabled) {
                sp94[count++] = i;
            }
        }
    } else {
        for (reverbIndex = 0; reverbIndex < D_8118427B; reverbIndex++) {
            for (i = 0; i < D_811858E8; i++) {
                noteSubEu = (D_811858E8 * updateIndex + i) + (Sub8110814C*)D_81184288;
                if (count && count && count) {} // FAKE: block boundary that stops as1 propagating the noteSubEu copy
                if (cmd && cmd && cmd) {} // FAKE: same barrier, also balances register priority
                if (noteSubEu->enabled && noteSubEu->reverbIndex == reverbIndex) {
                    sp94[count++] = i;
                }
            }
        }
        for (i = 0; i < D_811858E8; i++) {
            noteSubEu = (D_811858E8 * updateIndex + i) + (Sub8110814C*)D_81184288;
            if (count && count && count) {} // FAKE: block boundary that stops as1 propagating the noteSubEu copy
            if (noteSubEu->enabled && noteSubEu->reverbIndex >= D_8118427B) {
                sp94[count++] = i;
            }
        }
    }

    { AudioCmd* _a = cmd++; _a->w0 = ZSHIFTL_814C(2, 24, 8) | ZSHIFTL_814C(0x940, 0, 24); _a->w1 = 0x340; }

    i = 0;
    for (reverbIndex = 0; reverbIndex < D_8118427B; reverbIndex++) {
        D_8118427A = ((Reverb8110814C*)&D_81184110[reverbIndex])->useReverb;
        if (D_8118427A) {
            cmd = AudioSynth_LoadReverbSamples(cmd, aiBufLen, reverbIndex, updateIndex);
            if (reverbIndex) {} // FAKE: register priority
        }
        while (i < count) {
            if (((Sub8110814C*)D_81184288)[sp94[i] + updateIndex * D_811858E8].reverbIndex == reverbIndex) {
                cmd = AudioSynth_ProcessSample(sp94[i], (struct ZNoteSubEu*)&((Sub8110814C*)D_81184288)[sp94[i] + updateIndex * D_811858E8],
                                    (struct ZNoteSynthesisState*)&((Note8110814C*)D_81184664)[sp94[i]].synthesisState, (s16*)ai_buf, aiBufLen, cmd, updateIndex);
            } else {
                break;
            }
            i++;
        }
        if (((Reverb8110814C*)&D_81184110[reverbIndex])->useReverb) {
            if (((Reverb8110814C*)&D_81184110[reverbIndex])->filterLeft != NULL) {
                { AudioCmd* _a = cmd++; _a->w0 = ZSHIFTL_814C(0x1B, 24, 8) | ZSHIFTL_814C(2, 16, 8) | ZSHIFTL_814C(aiBufLen * 2, 0, 16); _a->w1 = (u32)((Reverb8110814C*)&D_81184110[reverbIndex])->filterLeft; }
                { AudioCmd* _a = cmd++; _a->w0 = ZSHIFTL_814C(0x1B, 24, 8) | ZSHIFTL_814C(((Reverb8110814C*)&D_81184110[reverbIndex])->resampleFlags, 16, 8) | ZSHIFTL_814C(0xC80, 0, 16); _a->w1 = (u32)((Reverb8110814C*)&D_81184110[reverbIndex])->filterLeftState; }
            }
            if (((Reverb8110814C*)&D_81184110[reverbIndex])->filterRight != NULL) {
                { AudioCmd* _a = cmd++; _a->w0 = ZSHIFTL_814C(0x1B, 24, 8) | ZSHIFTL_814C(2, 16, 8) | ZSHIFTL_814C(aiBufLen * 2, 0, 16); _a->w1 = (u32)((Reverb8110814C*)&D_81184110[reverbIndex])->filterRight; }
                { AudioCmd* _a = cmd++; _a->w0 = ZSHIFTL_814C(0x1B, 24, 8) | ZSHIFTL_814C(((Reverb8110814C*)&D_81184110[reverbIndex])->resampleFlags, 16, 8) | ZSHIFTL_814C(0xE20, 0, 16); _a->w1 = (u32)((Reverb8110814C*)&D_81184110[reverbIndex])->filterRightState; }
            }
            cmd = AudioSynth_SaveReverbSamples(cmd, reverbIndex, updateIndex);
            if (((Reverb8110814C*)&D_81184110[reverbIndex])->unk_05 != -1) {
                if (((Reverb81107390*)&D_81184110[((Reverb8110814C*)&D_81184110[reverbIndex])->unk_05])->downsampleRate == 1) {
                    cmd = AudioSynth_LoadRingBuffer1AtTemp(cmd, ((Reverb8110814C*)&D_81184110[reverbIndex])->unk_05, updateIndex);
                    cmd->w0 = ZSHIFTL_814C(0xC, 24, 8) | ZSHIFTL_814C(0x34, 16, 8) | ZSHIFTL_814C(((Reverb8110814C*)&D_81184110[reverbIndex])->unk_08, 0, 16); cmd->w1 = ZSHIFTL_814C(0xC80, 16, 16) | ZSHIFTL_814C(0x3E0, 0, 16); cmd++;
                    cmd = AudioSynth_SaveRingBuffer1AtTemp(cmd, ((Reverb8110814C*)&D_81184110[reverbIndex])->unk_05, updateIndex);
                }
            }
        }
    }

    while (i < count) {
        cmd = AudioSynth_ProcessSample(sp94[i], (struct ZNoteSubEu*)&((Sub8110814C*)D_81184288)[sp94[i] + updateIndex * D_811858E8],
                            (struct ZNoteSynthesisState*)&((Note8110814C*)D_81184664)[sp94[i]].synthesisState, (s16*)ai_buf, aiBufLen, cmd, updateIndex);
        i++;
    }

    updateIndex = aiBufLen * 2;
    { AudioCmd* _a = cmd++; _a->w0 = ZSHIFTL_814C(0xD, 24, 8) | ZSHIFTL_814C(updateIndex >> 4, 16, 8) | ZSHIFTL_814C(0x3C0, 0, 16); _a->w1 = ZSHIFTL_814C(0x940, 16, 16) | ZSHIFTL_814C(0xAE0, 0, 16); }
    { AudioCmd* _a = cmd++; _a->w0 = ZSHIFTL_814C(0x15, 24, 8) | ZSHIFTL_814C((updateIndex * 2) >> 4, 16, 8) | ZSHIFTL_814C(0x3C0, 0, 16); _a->w1 = (u32)ai_buf + 0x80000000; }
    return cmd;
}

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

void* AudioSynth_FinalResample(AudioCmd*, s8*, s32, u16, u16, s32);
extern s16 D_81136A58[];
u8* AudioLoad_DmaSampleData(u8*, s32, s32, u8*, u32);
AudioCmd* AudioSynth_ProcessEnvelope(AudioCmd*, ZNoteSubEu*, ZNoteSynthesisState*, s32, u16, s32, s32);

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

/**
 * Builds the commands that decode, resample and mix one note's sample. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
AudioCmd* AudioSynth_ProcessSample(s32 note_index, ZNoteSubEu* noteSubEu, ZNoteSynthesisState* synthesisState, s16* ai_buf,
                        s32 bufLen, AudioCmd* cmd, s32 update_index) {
    UNUSED s32 pad0[3]; // FAKE
    ZAudioBankSample* audioBookSample;
    ZAdpcmLoop* loop_info;
    s16* curLoadedBook;
    UNUSED u8 padEU[0x04]; // FAKE
    UNUSED u8 pad8[0x04]; // FAKE
    s32 note_finished;
    s32 restart;
    s32 flags;
    u16 resamplingRateFixedPoint;
    s32 n_samples_to_load;
    UNUSED u8 pad7[0x0c]; // FAKE
    s32 sp130;
    UNUSED s32 temp_buf_len; // FAKE
    UNUSED u32 pad9; // FAKE
    s32 t0;
    u8* sampleAddr;
    s32 s6;
    s32 samplesLenAdjusted;
    s32 nAdpcmSamplesProcessed;
    s32 end_pos;
    s32 n_samples_to_process;
    UNUSED s32 samples_len_int; // FAKE
    s32 s2;
    s32 left_right;
    s32 s5;
    u32 samples_len_fixed_point;
    s32 s3;
    s32 nSamplesInThisIteration;
    u32 a3;
    u8* v0_2;
    s32 unk_s6;
    s32 s5Aligned;
    s32 sp88;
    s32 sp84;
    u32 temp;
    s32 n_parts;
    s32 cur_part;
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
    note = (ZNote*)&D_81184664[note_index];
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
        n_parts = noteSubEu->hasTwoAdpcmParts + 1;
        samples_len_fixed_point = (resamplingRateFixedPoint * bufLen * 2) + synthesisState->samplePosFrac;
        n_samples_to_load = (samples_len_fixed_point >> 0x10);
        synthesisState->samplePosFrac = samples_len_fixed_point & 0xFFFF;

        if ((synthesisState->unk5 == 1) && (n_parts == 2)) {
        } else if ((synthesisState->unk5 == 2) && (n_parts == 1)) {
        } else {
            sp56 = 0;
        }

        synthesisState->unk5 = n_parts;

        audioBookSample = noteSubEu->audioBankSound->sample;
        loop_info = audioBookSample->loop;
        end_pos = loop_info->end;
        sampleAddr = audioBookSample->sampleAddr;
        resampledTempLen = 0;
        for (cur_part = 0; cur_part < n_parts; cur_part++) {
            nAdpcmSamplesProcessed = 0;
            s5 = 0;

            if (n_parts == 1) {
                samplesLenAdjusted = n_samples_to_load;
            } else if (n_samples_to_load & 1) {
                samplesLenAdjusted = (n_samples_to_load & ~1) + (cur_part * 2);
            } else {
                samplesLenAdjusted = n_samples_to_load;
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
                s32 samples_remaining;
                s32 s0;

                note_finished = FALSE;
                restart = FALSE;
                s5Aligned = 0;
                s2 = synthesisState->samplePosInt & 0xf;
                samples_remaining = end_pos - synthesisState->samplePosInt;
                n_samples_to_process = samplesLenAdjusted - nAdpcmSamplesProcessed;

                if (s2 == 0 && synthesisState->restart == FALSE) {
                    s2 = 16;
                }
                s6 = 16 - s2;
                if (n_samples_to_process < samples_remaining) {
                    t0 = (n_samples_to_process - s6 + 0xf) / 16;
                    s0 = t0 * 16;
                    s3 = s6 + s0 - n_samples_to_process;
                } else {
                    s0 = samples_remaining - s6;
                    s3 = 0;
                    if (s0 <= 0) {
                        s0 = 0;
                        s6 = samples_remaining;
                    }
                    t0 = (s0 + 0xf) / 16;
                    if (loop_info->count != 0) {
                        restart = 1;
                    } else {
                        note_finished = 1;
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
                        v0_2 = AudioLoad_DmaSampleData(sp84 + (temp * unk_s6) + sampleAddr, ZALIGN(t0 * unk_s6 + 16, 4), flags,
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
                if (note_finished) {
                    zClearBuffer(cmd++, 0x580 + s5, (samplesLenAdjusted - nAdpcmSamplesProcessed) * 2);
                    noteSubEu->finished = 1;
                    note->noteSubEu.finished = 1;
                    AudioSynth_DisableSampleStates(update_index, note_index);
                    break;
                }
                if (restart != 0) {
                    synthesisState->restart = TRUE;
                    synthesisState->samplePosInt = loop_info->start;
                } else {
                    synthesisState->samplePosInt += n_samples_to_process;
                }
            }

            switch (n_parts) {
                case 1:
                    noteSamplesDmemAddrBeforeResampling = 0x580 + sp130;
                    break;
                case 2:
                    switch (cur_part) {
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
        cmd = AudioSynth_FinalResample(cmd, (s8*)synthesisState, bufLen * 2, resamplingRateFixedPoint,
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
            left_right = 1;
        } else if (noteSubEu->headsetPanLeft != 0 || synthesisState->prevHeadsetPanLeft != 0) {
            left_right = 2;
        } else {
            left_right = 0;
        }
        cmd = AudioSynth_ProcessEnvelope(cmd, noteSubEu, synthesisState, bufLen, 0x3C0, left_right, flags);
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
/**
 * Adds the final resample command for a note. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void* AudioSynth_FinalResample(AudioCmd* cmd, s8* arg1, s32 arg2, u16 count, u16 arg4, s32 arg5) {
    AUDIO_CMDS_811092F4(cmd, arg1, arg2, count, arg4, arg5);
    return cmd;
}

typedef struct Src8110938C {
    /* 0x00 */ u32 unk00_0 : 4;
    /* 0x00 */ u32 flagA : 1;
    /* 0x00 */ u32 flagB : 1;
    /* 0x00 */ u32 unk00_6 : 26;
    /* 0x04 */ char unk04[1];
    /* 0x05 */ u8 vol;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ u16 left;
    /* 0x0A */ u16 right;
} Src8110938C;

typedef struct State8110938C {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ u8 vol;
    /* 0x05 */ char unk05[0xB];
    /* 0x10 */ u16 left;
    /* 0x12 */ u16 right;
} State8110938C;

/**
 * Adds the envelope (volume ramp, pan, reverb send) commands for a note. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
AudioCmd* AudioSynth_ProcessEnvelope(AudioCmd* cmd, ZNoteSubEu* note_sub_eu, ZNoteSynthesisState* synthesis_state, s32 ai_buf_len, u16 in_buf, s32 headset_pan_settings, s32 flags) {
    s32 reverbVol;
    u16 cur_vol_left;
    u16 target_vol_left;
    UNUSED s16 pad2; // FAKE: stack padding
    u16 cur_vol_right;
    s16 ramp_left;
    s16 ramp_right;
    s16 source_reverb_vol;
    u16 target_vol_right;
    s16 ramp_reverb;

    cur_vol_left = ((State8110938C*)synthesis_state)->left;
    cur_vol_right = ((State8110938C*)synthesis_state)->right;
    target_vol_left = ((Src8110938C*)note_sub_eu)->left;
    target_vol_right = ((Src8110938C*)note_sub_eu)->right;
    target_vol_left <<= 4;
    target_vol_right <<= 4;

    if (target_vol_left != cur_vol_left) {
        ramp_left = (target_vol_left - cur_vol_left) / (ai_buf_len >> 3);
    } else {
        ramp_left = 0;
    }
    if (target_vol_right != cur_vol_right) {
        ramp_right = (target_vol_right - cur_vol_right) / (ai_buf_len >> 3);
    } else {
        ramp_right = 0;
    }

    source_reverb_vol = ((State8110938C*)synthesis_state)->vol;
    // FAKE: dead assignment, reverbVol is overwritten before any use
    reverbVol = ((Src8110938C*)note_sub_eu)->vol;
    if (((Src8110938C*)note_sub_eu)->vol != source_reverb_vol) {
        reverbVol = ((((Src8110938C*)note_sub_eu)->vol & 0x7F) - (source_reverb_vol & 0x7F)) << 9;
        ramp_reverb = reverbVol / (ai_buf_len >> 3);
        ((State8110938C*)synthesis_state)->vol = ((Src8110938C*)note_sub_eu)->vol;
    } else {
        ramp_reverb = 0;
    }

    ((State8110938C*)synthesis_state)->left = cur_vol_left + (ramp_left * (ai_buf_len >> 3));
    ((State8110938C*)synthesis_state)->right = cur_vol_right + (ramp_right * (ai_buf_len >> 3));

    // each command is kept on one line (as a macro would expand), the line numbers affect codegen
    { AudioCmd* _a = cmd++; _a->w0 = (((u32) ((((u32) 0x12) & ((0x01 << 8) - 1)) << 24)) | ((u32) ((((u32) ((source_reverb_vol & 0x7F) * 2)) & ((0x01 << 8) - 1)) << 16))) | ((u32) ((((u32) ramp_reverb) & ((0x01 << 16) - 1)) << 0)); _a->w1 = ((u32) ((((u32) ramp_left) & ((0x01 << 16) - 1)) << 16)) | ((u32) ((((u32) ramp_right) & ((0x01 << 16) - 1)) << 0)); }
    { AudioCmd* _a = cmd++; _a->w0 = (u32) ((((u32) 0x16) & ((0x01 << 8) - 1)) << 24); _a->w1 = ((u32) ((((u32) cur_vol_left) & ((0x01 << 16) - 1)) << 16)) | ((u32) ((((u32) cur_vol_right) & ((0x01 << 16) - 1)) << 0)); }
    { AudioCmd* _a = cmd++; _a->w0 = ((((((u32) ((((u32) 0x13) & ((0x01 << 8) - 1)) << 24)) | ((u32) ((((u32) (in_buf >> 4)) & ((0x01 << 8) - 1)) << 16))) | ((u32) ((((u32) ai_buf_len) & ((0x01 << 8) - 1)) << 8))) | ((u32) ((((u32) ((source_reverb_vol & 0x80) >> 7)) & ((0x01 << 1) - 1)) << 2))) | ((u32) ((((u32) ((Src8110938C*)note_sub_eu)->flagA) & ((0x01 << 1) - 1)) << 1))) | ((u32) ((((u32) ((Src8110938C*)note_sub_eu)->flagB) & ((0x01 << 1) - 1)) << 0)); _a->w1 = 0x94AEC8E2; }
    return cmd;
}
