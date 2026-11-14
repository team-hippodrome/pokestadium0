/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "audio_and_gb_emulator.h"

// Declared here instead of in a header: the callers of these disagree on their types.
extern SeqPlayer811151C8 D_81184668[];
extern AudioBufferParameters D_811858B8;
extern volatile u32 D_811859D4;
void AudioPlayback_NotePoolClear(s8*);
void AudioPlayback_SeqLayerNoteDecay(SeqLayerFlags*);
void AudioSeq_AudioListPushBack(s8 *arg0, s8 *arg1);

extern u8 D_81138690[];
void AudioSeq_SequencePlayerDisableChannels(u8*, s32);
s32 AudioLoad_IsFontLoadComplete(s32);
s32 AudioLoad_IsSeqLoadComplete(s32);
void AudioLoad_SetFontLoadStatus(s32, s32);
void AudioLoad_SetSeqLoadStatus(s32, s32);
extern M2C_UNK D_81184380;
u8* AudioPlayback_GetInstrumentInner(s32, s32);
typedef struct SeqPlayerFlags81112E00 {
    u8 enabled : 1; // @unverified: cleared by AudioSeq_SequencePlayerDisable, OoT's SequencePlayer.enabled
    u8 finished : 1; // @unverified: set by AudioSeq_SequencePlayerDisable, OoT's SequencePlayer.finished
    u8 rest : 6;
} SeqPlayerFlags81112E00;

extern u16 D_81138A96;
extern u32 D_81138A90;
extern s16 D_81180700;
extern s16 D_81180702;
extern u8* D_81180704;
extern GbApuWrite D_81180848[GB_APU_WRITE_QUEUE_LEN];
extern u8 D_81182468[0x40];
extern s32 D_811824A8;
extern unk_D_8122EEA8 D_811824B8;
extern OSMesgQueue D_811824C0;
extern OSMesg D_811824D8[GB_APU_WRITE_QUEUE_LEN + 1];
extern AudioBufferParameters D_811858B8;
extern volatile s32 D_811858F0;
extern s32 D_811858F8;
extern s32 D_811858FC;
extern s16* D_811859B8[3];
extern s16 D_811859C4[3];
extern u32 D_811859CC;
extern volatile u32 D_811859D4;
extern unk_D_81287B08_jp D_81287B08_jp[];
extern OSMesgQueue* D_812896A0_jp;
extern s32 D_81138A70;
extern u8 D_81138A80[0x10];
extern s32 D_81138AD0;
extern s32 D_81138AD4;
extern s32 D_81138AD8;
extern u16 D_81138ADC[32];
extern u8 D_81138B1C[0x10];
extern u8 D_81138B2C[0x4];
extern u8 D_81138B30[0x10];
extern u8 D_81138B40[0x10];
extern u32 D_81138B50[9];
extern s32 D_81138B80;
extern GbAudioStream D_81138B84;
extern struct AudioListItem D_81184928;
extern AudioListItem D_81184928;
extern SeqLayer811847C8 D_811847C8[1];
extern s16 D_811858CC;
extern SeqPlayer811151C8 D_81184668[];

/**
 * Reads the argument of a control-flow command of kind `kind` from the script stream. Zelda 64 audio driver (seqplayer.c), same position and shape.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
u16 AudioSeq_GetScriptControlFlowArgument(u8** stream, u8 kind) {
    u8 flags = D_81138690[kind];
    u16 value = 0;

    if (((flags & 0xFF) & 3) == 1) {
        if (!(flags & 0x80)) {
            value = AudioSeq_ScriptReadU8(stream);
        } else {
            value = AudioSeq_ScriptReadS16(stream);
        }
    }
    return value;
}

typedef struct SeqScriptState811126B8 {
    /* 0x00 */ u8* pc;
    /* 0x04 */ u8* stack[4];
    /* 0x14 */ u8 remLoopIters[4];
    /* 0x18 */ u8 depth;
    /* 0x19 */ s8 value;
} SeqScriptState811126B8;

typedef struct SeqPlayer811126B8 {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ u8* seqData;
} SeqPlayer811126B8;

u16 AudioSeq_ScriptReadCompressedU16(u8** arg0);

/**
 * Runs a script control-flow command (end, call, loop, jump, branch). Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_HandleScriptFlowControl(SeqPlayer811126B8* seq_player, SeqScriptState811126B8* state, s32 cmd, s32 cmd_arg) {
    u8 depth;

    switch (cmd) {
        case 0xFF:
            if (state->depth == 0) {
                return -1;
            }
            state->pc = state->stack[--state->depth];
            break;
        case 0xFD:
            return AudioSeq_ScriptReadCompressedU16(&state->pc);
        case 0xFE:
            return 1;
        case 0xFC:
            depth = state->depth;
            state->stack[depth] = state->pc;
            state->depth++;
            state->pc = seq_player->seqData + (u16)cmd_arg;
            break;
        case 0xF8:
            depth = state->depth;
            state->remLoopIters[depth] = cmd_arg;
            state->stack[state->depth++] = state->pc;
            break;
        case 0xF7:
            state->remLoopIters[state->depth - 1]--;
            if (state->remLoopIters[state->depth - 1] != 0) {
                state->pc = state->stack[state->depth - 1];
            } else {
                state->depth--;
            }
            break;
        case 0xF6:
            state->depth--;
            break;
        case 0xF5:
        case 0xF9:
        case 0xFA:
        case 0xFB:
            if (cmd == 0xFA && state->value != 0) {
                break;
            }
            if (cmd == 0xF9 && state->value >= 0) {
                break;
            }
            if (cmd == 0xF5 && state->value < 0) {
                break;
            }
            state->pc = seq_player->seqData + (u16)cmd_arg;
            break;
        case 0xF2:
        case 0xF3:
        case 0xF4:
            if (cmd == 0xF3 && state->value != 0) {
                break;
            }
            if (cmd == 0xF2 && state->value >= 0) {
                break;
            }
            state->pc += (s8)(cmd_arg & 0xFF);
            break;
    }
    return 0;
}

extern Channel8111539C D_81184850;

void AudioPlayback_InitNoteLists(void*);
typedef struct ChannelFlags81112894 {
    u8 enabled : 1; // @unverified: same bit/use as OoT's SequenceChannel.enabled (AudioSeq_InitSequenceChannel)
    u8 finished : 1; // @unverified: same bit/use as OoT's SequenceChannel.finished
    u8 stopScript : 1; // @unverified: same bit/use as OoT's SequenceChannel.stopScript
    u8 muted : 1; // @unverified: same bit/use as OoT's SequenceChannel.muted
    u8 hasInstrument : 1; // @unverified: same bit/use as OoT's SequenceChannel.hasInstrument
    u8 stereoHeadsetEffects : 1; // @unverified: same bit/use as OoT's SequenceChannel.stereoHeadsetEffects
    u8 largeNotes : 1; // @unverified: same bit/use as OoT's SequenceChannel.largeNotes
    u8 unused : 1; // @unverified: same bit/use as OoT's SequenceChannel.unused
} ChannelFlags81112894;
extern u8 D_81136998[];
/**
 * Resets a sequence channel to its defaults. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_InitSequenceChannel(void* obj) {
    s8* arg0 = obj;
    s32 i;

    if ((Channel8111539C*)arg0 != &D_81184850) {
        ((ChannelFlags81112894*)arg0)->enabled = 0;
        ((ChannelFlags81112894*)arg0)->finished = 0;
        ((ChannelFlags81112894*)arg0)->stopScript = 0;
        ((ChannelFlags81112894*)arg0)->muted = 0;
        ((ChannelFlags81112894*)arg0)->hasInstrument = 0;
        ((ChannelFlags81112894*)arg0)->stereoHeadsetEffects = 0;
        M2C_FIELD(arg0, s16*, 0x24) = 0;
        ((ChannelFlags81112894*)arg0)->largeNotes = 0;
        M2C_FIELD(arg0, s8*, 9) = 0;
        M2C_FIELD(arg0, u8*, 1) = 0xFF;
        M2C_FIELD(arg0, s8*, 0x78) = 0;
        M2C_FIELD(arg0, s8*, 0xA) = 0x40;
        M2C_FIELD(arg0, u8*, 0xB) = 0x80;
        M2C_FIELD(arg0, s8*, 0xD) = 0;
        M2C_FIELD(arg0, s8*, 0xE) = 0;
        M2C_FIELD(arg0, s32*, 0x40) = 0;
        M2C_FIELD(arg0, s8*, 8) = 0;
        M2C_FIELD(arg0, s8*, 4) = 0;
        M2C_FIELD(arg0, s8*, 0xC) = 0;
        M2C_FIELD(arg0, s8*, 5) = 3;
        M2C_FIELD(arg0, s8*, 6) = 1;
        M2C_FIELD(arg0, s16*, 0x1E) = 0;
        M2C_FIELD(arg0, u8**, 0x80) = D_81136998;
        M2C_FIELD(arg0, s8*, 0x7C) = 0x20;
        M2C_FIELD(arg0, s16*, 0x14) = 0x800;
        M2C_FIELD(arg0, s16*, 0x10) = 0x800;
        M2C_FIELD(arg0, s8*, 0x7D) = 0;
        M2C_FIELD(arg0, s16*, 0x16) = 0;
        M2C_FIELD(arg0, s16*, 0x12) = 0;
        M2C_FIELD(arg0, s16*, 0x18) = 0;
        M2C_FIELD(arg0, s16*, 0x1A) = 0;
        M2C_FIELD(arg0, s16*, 0x1C) = 0;
        M2C_FIELD(arg0, s32*, 0xD0) = 0;
        M2C_FIELD(arg0, s16*, 0x20) = 0;
        M2C_FIELD(arg0, s8*, 0xF) = 0;
        M2C_FIELD(arg0, f32*, 0x2C) = 1.0f;
        M2C_FIELD(arg0, f32*, 0x28) = 1.0f;
        M2C_FIELD(arg0, f32*, 0x38) = 1.0f;
        for (i = 0; i < 8; i++) {
            M2C_FIELD(arg0, s8*, 0xC4 + i) = -1;
        }
        ((ChannelFlags81112894*)arg0)->unused = 0;
        AudioPlayback_InitNoteLists(arg0 + 0x84);
    }
}

extern struct AudioListItem D_81184928;
typedef struct AdsrSettings811129E0 { u8 decayIndex; u8 pad[3]; s32 envelope; } AdsrSettings811129E0; // @unverified: same offset as OoT's AdsrSettings.envelope
typedef struct Layer811129E0 {
    u8 enabled : 1; // @unverified: same bit/use as OoT's SequenceLayer.enabled (AudioSeq_SeqChannelSetLayer)
    u8 finished : 1; // @unverified: same bit/use as OoT's SequenceLayer.finished
    u8 stopSomething : 1; // @unverified: same bit as the stopSomething of the other layer views (OoT's SequenceLayer.muted)
    u8 continuousNotes : 1; // @unverified: same bit/use as OoT's SequenceLayer.continuousNotes
    u8 b08 : 1;
    u8 b04 : 1;
    u8 ignoreDrumPan : 1; // @unverified: same bit as the ignoreDrumPan of the other layer views
    u8 bit1 : 1; // @unverified: same bit as the bit1 of the other layer views (OoT's SequenceLayer.bit1)
    u8 stereo; // @unverified: set to 0x40, SM64 Shindou's SequenceChannelLayer.reverbBits / OoT's stereo
    u8 instOrWave; // @unverified: set to 0xFF, same offset as instOrWave in the other layer views
    u8 status; // @unverified: zeroed where SM64 Shindou's seq_channel_set_layer clears layer->status
    u8 noteDuration; // @unverified: set to 0x80, same offset as noteDuration in Layer811132E4
    u8 pad05;
    u8 pan; // @unverified: set to 0x40, same offset as pan in the other layer views
    u8 pad07;
    u8 portamentoMode; // @unverified: same offset as Layer811132E4.portamentoMode (OoT's SequenceLayer.portamento.mode)
    char pad09[0xF];
    AdsrSettings811129E0 adsr; // @unverified: copied from the channel's adsr, decayIndex then cleared (OoT's SequenceLayer.adsr)
    char pad20[2];
    s16 transposition; // @unverified: same offset as transposition in the other layer views
    f32 freqScale; // @unverified: set to 1.0, same offset as Layer81113650.freqScale
    f32 bend; // @unverified: set to 1.0, same offset as Layer81113650.bendPitch (OoT's SequenceLayer.bend)
    f32 velocitySquare2; // @unverified: zeroed where OoT's AudioSeq_SeqLayerSetLayer clears velocitySquare2
    char pad30[0x10];
    s16 delay; // @unverified: same offset as Layer81113650.delay
    s16 gateDelay; // @unverified: same offset/use as OoT's SequenceLayer.gateDelay (compared with delay in AudioSeq_SeqLayerProcessScript)
    s16 duration; // @unverified: same offset as Layer81113650.duration
    s32 note; // @unverified: same offset as Layer81110798.note
    s32 instrument; // @unverified: same offset as instrument in the other layer views
    char pad50[4];
    void* channel; // @unverified: same offset as channel in the other layer views (OoT's SequenceLayer.channel)
    char pad58[0x18];
    u8 scriptStateDepth; // @unverified: layer scriptState starts at 0x58, so this is scriptState.depth (OoT)
} Layer811129E0;
typedef struct Channel811129E0 {
    char pad0[0x50];
    Layer811129E0* layers[11]; // @unverified: same offset/use as OoT's SequenceChannel.layers
    AdsrSettings811129E0 adsr; // @unverified: same offset/use as OoT's SequenceChannel.adsr
} Channel811129E0;
s32 AudioSeq_AudioListPopBack(s8*);
void AudioPlayback_SeqLayerNoteDecay();
/**
 * Gives channel `arg0` a layer in slot `arg1`, taking one from the free list when needed. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqChannelSetLayer(Channel811129E0* arg0, s32 arg1) {
    Layer811129E0* p;
    s32 pad; // FAKE: stack padding
    if (arg0->layers[arg1] == NULL) {
        arg0->layers[arg1] = (Layer811129E0*)AudioSeq_AudioListPopBack((s8*)&D_81184928);
        if (arg0->layers[arg1] == NULL) {
            arg0->layers[arg1] = NULL;
            return -1;
        }
    } else {
        AudioPlayback_SeqLayerNoteDecay(arg0->layers[arg1]);
    }
    p = arg0->layers[arg1];
    p->channel = arg0;
    p->adsr = arg0->adsr;
    p->enabled = 1;
    p->stopSomething = 0;
    p->continuousNotes = 0;
    p->finished = 0;
    p->ignoreDrumPan = 0;
    p->adsr.decayIndex = 0;
    p->bit1 = 0;
    p->stereo = 0x40;
    p->portamentoMode = 0;
    p->scriptStateDepth = 0;
    p->status = 0;
    p->noteDuration = 0x80;
    p->pan = 0x40;
    p->transposition = 0;
    p->delay = 0;
    p->gateDelay = 0;
    p->duration = 0;
    p->note = 0;
    p->instrument = 0;
    p->instOrWave = 0xFF;
    p->freqScale = 1.0f;
    p->bend = 1.0f;
    p->velocitySquare2 = 0.0f;
    return 0;
}

/**
 * Decays the layer's note and turns the layer off. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SeqLayerDisable(SeqLayerFlags* arg0) {
    if (arg0 != NULL) {
        AudioPlayback_SeqLayerNoteDecay(arg0);
        arg0->enabled = 0;
        arg0->finished = 1;
    }
}

/**
 * Returns layer slot `arg1` of a channel to the free list. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SeqLayerFree(s8** arg0, s32 arg1) {
    s8* temp = arg0[arg1 + 0x14];

    if (temp != NULL) {
        AudioSeq_AudioListPushBack((s8*)&D_81184928, temp + 0x74);
        AudioSeq_SeqLayerDisable((SeqLayerFlags*)temp);
        arg0[arg1 + 0x14] = NULL;
    }
}

/** Resets all particle slots of a display object. */
void Particle31_ResetAllSlots(DisplayObject* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        AudioSeq_SeqLayerFree(arg0, i);
    }
    AudioPlayback_NotePoolClear((s8*)arg0 + 0x84);
    ((SeqChannelFlags*)arg0)->enabled = 0;
    ((SeqChannelFlags*)arg0)->finished = 1;
}

/**
 * Resets each channel selected in `mask`. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequencePlayerSetupChannels(s8* arg0, u16 mask) {
    s32 i;
    s8* item;

    for (i = 0; i < 16; i++) {
        if (mask & 1) {
            item = M2C_FIELD(arg0, s8**, 0x34 + i * 4);
            M2C_FIELD(item, u8*, 7) = M2C_FIELD(arg0, u8*, 5);
            M2C_FIELD(item, u8*, 3) = M2C_FIELD(arg0, u8*, 3);
            M2C_FIELD(item, u8*, 2) = M2C_FIELD(arg0, u8*, 2);
        }
        mask = (s32)mask >> 1;
    }
}

void func_81112B84(Channel8111539C*);

/**
 * Disables each channel selected in `channel_bits`. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequencePlayerDisableChannels(u8* seqPlayer, s32 channel_bits) {
    Channel8111539C* channel;
    s32 i;

    for (i = 0; i < 16; i++) {
        channel = M2C_FIELD(seqPlayer, Channel8111539C**, 0x34 + i * 4);
        if (((u32)channel != (u32)&D_81184850) == 1) {
            func_81112B84(channel);
        }
    }
}

/**
 * Starts channel `arg1` at script address `arg2`. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequenceChannelEnable(Channel81112D68** arg0, u8 arg1, s32 arg2) {
    Channel81112D68* p = arg0[arg1 + 13];
    s32 i;

    p->scriptDepth = 0;
    p->scriptPc = arg2;
    p->enabled = 1;
    p->finished = 0;
    p->delay = 0;
    for (i = 0; i < 4; i++) {
        if (p->layers[i] != NULL) {
            AudioSeq_SeqLayerFree((s8**)p, i);
        }
    }
}

/**
 * Stops a sequence player: disables its channels, clears its note pool and marks its data discardable. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequencePlayerDisable(u8* arg0) {
    AudioSeq_SequencePlayerDisableChannels(arg0, 0xFFFF);
    AudioPlayback_NotePoolClear((s8*)arg0 + 0x98);
    ((SeqPlayerFlags81112E00*)arg0)->finished = 1;
    ((SeqPlayerFlags81112E00*)arg0)->enabled = 0;
    if (AudioLoad_IsSeqLoadComplete(arg0[4]) != 0) {
        AudioLoad_SetSeqLoadStatus(arg0[4], 3);
    }
    if (AudioLoad_IsFontLoadComplete(arg0[5]) != 0) {
        AudioLoad_SetFontLoadStatus(arg0[5], 4);
    }
    if (arg0[5] == M2C_FIELD(&D_81184380, s16*, 0x3E)) {
        M2C_FIELD(&D_81184380, s32*, 0x20) = 1;
    } else if (arg0[5] == M2C_FIELD(&D_81184380, s16*, 0x4A)) {
        M2C_FIELD(&D_81184380, s32*, 0x20) = 0;
    }
}

/**
 * Appends an item to the end of a list if it is on no list. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_AudioListPushBack(s8 *arg0, s8 *arg1)
{
  if ((*((s8 **) (((s8 *) arg1) + 0))) == 0)
  {
    *((s8 **) (((s8 *) (*((s8 **) (((s8 *) arg0) + 0)))) + 4)) = arg1; // FAKE: decomp slop, raw pointer casts stand in for struct fields
    *((s8 **) (((s8 *) arg1) + 0)) = (s8 *) (*((s8 **) (((s8 *) arg0) + 0))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    *((s8 **) (((s8 *) arg1) + 4)) = arg0;
    *((s8 **) (((s8 *) arg0) + 0)) = arg1;
    *((s32 *) (((s8 *) arg0) + 8)) = ((s32) ((*((s32 *) (((s8 *) arg0) + 8))) + 1)) ^ 0; // FAKE: decomp slop, raw pointer casts stand in for struct fields
    *((s32 *) (((s8 *) arg1) + 0xC)) = (s32) (*((s32 *) (((s8 *) arg0) + 0xC))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  }
}

/**
 * Removes and returns the last item of a list, or 0 when it is empty. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_AudioListPopBack(s8 *arg0) {
    s8 *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_v1 == arg0) {
        return 0;
    }
    M2C_FIELD(M2C_FIELD(temp_v1, s8 **, 0), s8 **, 4) = arg0;
    M2C_FIELD(arg0, s8 **, 0) = (s8 *) M2C_FIELD(temp_v1, s8 **, 0);
    M2C_FIELD(temp_v1, s8 **, 0) = NULL;
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) - 1);
    return M2C_FIELD(temp_v1, s32 *, 8);
}

/**
 * Puts every sequence layer on the free list. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_InitLayerFreelist(void) {
    s32 i;

    D_81184928.prev = &D_81184928;
    D_81184928.next = &D_81184928;
    D_81184928.count = 0;
    D_81184928.pool = 0;
    for (i = 0; i < 1; i++) {
        D_811847C8[i].listItemValue = &D_811847C8[i];
        D_811847C8[i].listItemPrev = NULL;
        AudioSeq_AudioListPushBack((s8*)&D_81184928, (s8*)&D_811847C8[i].listItemPrev);
    }
}

/**
 * Reads one byte from the script stream. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
u8 AudioSeq_ScriptReadU8(u8 **arg0)
{
  u8 new_var; // FAKE: permuter temp
  u8 *temp_a1;
  new_var = *(*arg0);
  temp_a1 = *arg0;
  *arg0 = temp_a1 + 1;
  return new_var; // FAKE: permuter temp
}

/**
 * Reads a big-endian 16-bit value from the script stream. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s16 AudioSeq_ScriptReadS16(u8** arg0) {
    s16 tmp = *(*arg0)++ << 8;

    tmp = *(*arg0)++ | tmp;
    return tmp;
}

/**
 * AudioSeq_ScriptReadCompressedU16
 *
 * Reads a one- or two-byte value from the byte stream whose current position
 * is stored at *arg0, advancing that position. If the first byte has bit 7
 * clear it is the result. Otherwise the result is ((first & 0x7F) << 8) |
 * second byte, and the position advances past both bytes.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
u16 AudioSeq_ScriptReadCompressedU16(u8** arg0) {
    u16 v;

    v = *(*arg0)++;
    if (v & 0x80) {
        v = (v << 8) & 0x7F00;
        v = *(*arg0)++ | v;
    }
    return v;
}

typedef struct Layer8111303C {
    u32 enabled : 1; // @unverified: same bit/use as OoT's SequenceLayer.enabled (AudioSeq_SeqLayerProcessScript)
    u32 b40 : 1;
    u32 stopSomething : 1; // @unverified: set once delay reaches gateDelay, as OoT's SequenceLayer.muted
    u32 continuousNotes : 1; // @unverified: same bit/use as OoT's SequenceLayer.continuousNotes
    u32 rest : 28;
    char pad04[0x3C];
    s16 delay; // @unverified: same offset/use as OoT's SequenceLayer.delay (counted down)
    s16 gateDelay; // @unverified: same offset/use as OoT's SequenceLayer.gateDelay
    char pad44[4];
    s32 note; // @unverified: same offset/use as OoT's SequenceLayer.note
} Layer8111303C;
void AudioSeq_SeqLayerProcessScriptStep1();
s32 AudioSeq_SeqLayerProcessScriptStep2();
s32 func_81113A44();
s32 AudioSeq_SeqLayerProcessScriptStep4();
s32 AudioSeq_SeqLayerProcessScriptStep5();
/**
 * Runs a layer's script for one tick. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SeqLayerProcessScript(Layer8111303C* arg0) {
    s32 ret;
    if (arg0->enabled) {
        if (arg0->delay >= 2) {
            arg0->delay--;
            if (!arg0->stopSomething && arg0->gateDelay >= arg0->delay) {
                AudioPlayback_SeqLayerNoteDecay((SeqLayerFlags*)arg0);
                arg0->stopSomething = 1;
            }
        } else {
            AudioSeq_SeqLayerProcessScriptStep1(arg0);
            ret = AudioSeq_SeqLayerProcessScriptStep2(arg0);
            if (ret != -1) {
                ret = func_81113A44(arg0, ret);
                if (ret != -1) {
                    ret = AudioSeq_SeqLayerProcessScriptStep4(arg0, ret);
                }
                if (ret != -1) {
                    AudioSeq_SeqLayerProcessScriptStep5(arg0, ret);
                }
                if (arg0->stopSomething == 1 && (arg0->note != 0 || arg0->continuousNotes)) {
                    AudioPlayback_SeqLayerNoteDecay((SeqLayerFlags*)arg0);
                }
            }
        }
    }
}

/**
 * Decays or releases the layer's note before the next script command. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SeqLayerProcessScriptStep1(Layer81113140* arg0) {
    if (!arg0->continuousNotes) {
        AudioPlayback_SeqLayerNoteDecay((SeqLayerFlags*)arg0);
    } else if (arg0->note != NULL && arg0 == arg0->note->wantedParentLayer) {
        AudioPlayback_SeqLayerNoteDecay((SeqLayerFlags*)arg0);
    }
    switch (arg0->portamentoMode & ~0x80) {
        case 1:
        case 2:
            arg0->portamentoMode = 0;
            break;
    }
    arg0->notePropertiesNeedInit = 1;
}

s8* AudioPlayback_AllocNote(s8*);
void func_81112278(void*);

typedef struct Sample811131CC {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 rest : 26;
} Sample811131CC;

typedef struct Sound811131CC {
    /* 0x00 */ Sample811131CC* sample;
} Sound811131CC;

typedef struct Layer811131CC {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 stopSomething : 1;
    /* 0x00 */ u32 continuousNotes : 1;
    /* 0x00 */ u32 bit3 : 1;
    /* 0x00 */ u32 ignoreDrumPan : 1;
    /* 0x00 */ u32 bit6 : 1;
    /* 0x00 */ u32 bit1 : 1;
    /* 0x01 */ u32 pad01 : 16;
    /* 0x03 */ u8 status;
    /* 0x04 */ u8 pad04[0x48 - 0x04];
    /* 0x48 */ struct Note811131CC* note;
    /* 0x4C */ u8 pad4C[4];
    /* 0x50 */ Sound811131CC* sound;
} Layer811131CC;

typedef struct Note811131CC {
    /* 0x00 */ u8 pad00[0x44];
    /* 0x44 */ Layer811131CC* parentLayer;
} Note811131CC;

/**
 * Gets a note for the layer, reusing the current one for the same sound. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqLayerProcessScriptStep5(Layer811131CC* layer, u32 same_sound) {
    Note811131CC* note;

    if (!layer->stopSomething && layer->sound != NULL && layer->sound->sample->codec == 2 &&
        layer->sound->sample->medium != 0) {
        layer->stopSomething = 1;
        return -1;
    }

    if (layer->continuousNotes == 1 && layer->bit1 == 1) {
        return 0;
    }

    if (layer->continuousNotes != 1 || layer->note == NULL || !layer->status || same_sound != 1 ||
        layer != layer->note->parentLayer) {
        if (same_sound == 0) {
            AudioPlayback_SeqLayerNoteDecay((SeqLayerFlags*)layer);
        }
        layer->note = (Note811131CC*)AudioPlayback_AllocNote((s8*)layer);
    }
    if (layer->note != NULL && layer->note->parentLayer == layer) {
        note = layer->note;
        func_81112278(note);
    }
    return 0;
}

typedef struct SeqPlayer811132E4 {
    /* 0x00 */ u8 unk00[0xE];
    /* 0x0E */ s16 transposition;
    /* 0x10 */ u8 unk10[0x18 - 0x10];
    /* 0x18 */ u8* seqData;
    /* 0x1C */ u8 unk1C[0x90 - 0x1C];
    /* 0x90 */ u8* velocityTable;
    /* 0x94 */ u8* durationTable;
} SeqPlayer811132E4;

typedef struct Channel811132E4 {
    /* 0x00 */ u8 unk00[0x24];
    /* 0x24 */ s16 transposition;
    /* 0x26 */ u8 unk26[0x4C - 0x26];
    /* 0x4C */ struct SeqPlayer811132E4* seqPlayer;
} Channel811132E4;

typedef struct ScriptState811132E4 {
    /* 0x00 */ u8* pc;
} ScriptState811132E4;

typedef struct Layer811132E4 {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stopSomething : 1;
    /* 0x00 */ u8 continuousNotes : 1;
    /* 0x00 */ u8 bit3 : 1;
    /* 0x00 */ u8 notePropertiesNeedInit : 1;
    /* 0x00 */ u8 ignoreDrumPan : 1;
    /* 0x00 */ u8 bit1 : 1;
    /* 0x01 */ s8 stereo; // @unverified: set by layer command 0xCD, as OoT's SequenceLayer.stereo.asByte
    /* 0x02 */ u8 instOrWave;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 noteDuration;
    /* 0x05 */ u8 portamentoTargetNote;
    /* 0x06 */ u8 pan;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ u8 portamentoMode;
    /* 0x09 */ u8 unk09[0x18 - 0x09];
    /* 0x18 */ u8 releaseRate;
    /* 0x19 */ u8 unk19[3];
    /* 0x1C */ u8* envelope;
    /* 0x20 */ s16 portamentoTime;
    /* 0x22 */ s16 transposition;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ f32 bend; // @unverified: set from the one-octave bend table, OoT's SequenceLayer.bend (Layer81113650 multiplies freqScale by it)
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ f32 velocitySquare;
    /* 0x34 */ u8 unk34[0x3C - 0x34];
    /* 0x3C */ s16 shortNoteDefaultDelay;
    /* 0x3E */ u8 unk3E[0x4C - 0x3E];
    /* 0x4C */ u8* instrument;
    /* 0x50 */ u8 unk50[4];
    /* 0x54 */ Channel811132E4* channel;
    /* 0x58 */ ScriptState811132E4 scriptState;
} Layer811132E4;

extern f32 D_81136378[];
u8 func_81113E84(u8* arg0, u8 arg1, u8** arg2, u8* arg3);

/**
 * Runs layer script commands until a note command. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqLayerProcessScriptStep2(Layer811132E4* layer) {
    Channel811132E4* channel = layer->channel;
    ScriptState811132E4* state = &layer->scriptState;
    SeqPlayer811132E4* seqPlayer = channel->seqPlayer;
    u8 cmd;
    u8 cmd_arg8;
    u16 cmd_arg16;
    u16 velocity;

    while (1) {
        cmd = AudioSeq_ScriptReadU8(&state->pc);
        if (cmd <= 0xC0) {
            return cmd;
        }
        if (cmd >= 0xF2) {
            cmd_arg16 = AudioSeq_GetScriptControlFlowArgument(&state->pc, cmd);
            if (AudioSeq_HandleScriptFlowControl(seqPlayer, state, cmd, cmd_arg16) == 0) {
                continue;
            }
            AudioSeq_SeqLayerDisable((SeqLayerFlags*)layer);
            return -1;
        }

        switch (cmd) {
            case 0xC1:
            case 0xCA:
                cmd_arg8 = *(state->pc++);
                if (cmd == 0xC1) {
                    layer->velocitySquare = (f32)(cmd_arg8 * cmd_arg8) / 16129.0f;
                } else {
                    layer->pan = cmd_arg8;
                }
                break;
            case 0xC9:
            case 0xC2:
                cmd_arg8 = *(state->pc++);
                if (cmd == 0xC9) {
                    layer->noteDuration = cmd_arg8;
                } else {
                    layer->transposition = cmd_arg8;
                }
                break;
            case 0xC4:
            case 0xC5:
                if (cmd == 0xC4) {
                    layer->continuousNotes = 1;
                } else {
                    layer->continuousNotes = 0;
                }
                layer->bit1 = 0;
                AudioPlayback_SeqLayerNoteDecay((SeqLayerFlags*)layer);
                break;
            case 0xC3:
                cmd_arg16 = AudioSeq_ScriptReadCompressedU16(&state->pc);
                layer->shortNoteDefaultDelay = cmd_arg16;
                break;
            case 0xC6:
                cmd = AudioSeq_ScriptReadU8(&state->pc);
                if (cmd >= 0x7F) {
                    if (cmd == 0x7F) {
                        layer->instOrWave = 0;
                    } else {
                        layer->instOrWave = cmd;
                        layer->instrument = NULL;
                    }
                    if (cmd == 0xFF) {
                        layer->releaseRate = 0;
                    }
                    break;
                }
                if ((layer->instOrWave = func_81113E84((u8*)channel, cmd, &layer->instrument, &layer->releaseRate)) == 0) {
                    layer->instOrWave = 0xFF;
                }
                break;
            case 0xC7:
                layer->portamentoMode = AudioSeq_ScriptReadU8(&state->pc);
                cmd = AudioSeq_ScriptReadU8(&state->pc);
                cmd += channel->transposition;
                cmd += layer->transposition;
                cmd += seqPlayer->transposition;
                if (cmd >= 0x80) {
                    cmd = 0;
                }
                layer->portamentoTargetNote = cmd;
                if (layer->portamentoMode & 0x80) {
                    layer->portamentoTime = *(state->pc++);
                    break;
                }
                cmd_arg16 = AudioSeq_ScriptReadCompressedU16(&state->pc);
                layer->portamentoTime = cmd_arg16;
                break;
            case 0xC8:
                layer->portamentoMode = 0;
                break;
            case 0xCB:
                cmd_arg16 = AudioSeq_ScriptReadS16(&state->pc);
                layer->envelope = seqPlayer->seqData + cmd_arg16;
            case 0xCF:
                layer->releaseRate = AudioSeq_ScriptReadU8(&state->pc);
                break;
            case 0xCC:
                layer->ignoreDrumPan = 1;
                break;
            case 0xCD:
                layer->stereo = AudioSeq_ScriptReadU8(&state->pc);
                break;
            case 0xCE:
                layer->bend = D_81136378[(u8)(AudioSeq_ScriptReadU8(&state->pc) + 0x80)];
                break;
            default:
                switch (cmd & 0xF0) {
                    case 0xD0:
                        velocity = seqPlayer->velocityTable[cmd & 0xF];
                        layer->velocitySquare = (f32)(velocity * velocity) / 16129.0f;
                        break;
                    case 0xE0:
                        layer->noteDuration = seqPlayer->durationTable[cmd & 0xF];
                        break;
                }
                break;
        }
    }
}

typedef struct Sound81113650 {
    /* 0x00 */ u8* sample;
    /* 0x04 */ f32 tuning;
} Sound81113650;

typedef struct Drum81113650 {
    /* 0x00 */ u8 releaseRate;
    /* 0x01 */ u8 pan;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ Sound81113650 sound;
    /* 0x0C */ u8* envelope;
} Drum81113650;

typedef struct SeqPlayer81113650 {
    /* 0x00 */ u8 unk00[8];
    /* 0x08 */ u16 tempo;
    /* 0x0A */ u8 unk0A[4];
    /* 0x0E */ s16 transposition;
} SeqPlayer81113650;

typedef struct Channel81113650 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 stopScript : 1;
    /* 0x00 */ u32 stopSomething2 : 1;
    /* 0x00 */ u32 hasInstrument : 1;
    /* 0x00 */ u32 rest : 27;
    /* 0x04 */ u8 unk04[3];
    /* 0x07 */ u8 bankId;
    /* 0x08 */ u8 unk08[0x22 - 0x08];
    /* 0x22 */ s16 instOrWave;
    /* 0x24 */ s16 transposition;
    /* 0x26 */ u8 unk26[0x48 - 0x26];
    /* 0x48 */ u8* instrument;
    /* 0x4C */ SeqPlayer81113650* seqPlayer;
} Channel81113650;

typedef struct Portamento81113650 {
    /* 0x00 */ u8 mode;
    /* 0x04 */ f32 cur;
    /* 0x08 */ f32 speed;
    /* 0x0C */ f32 extent;
} Portamento81113650;

typedef struct Layer81113650 {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stopSomething : 1;
    /* 0x00 */ u8 continuousNotes : 1;
    /* 0x00 */ u8 bit3 : 1;
    /* 0x00 */ u8 notePropertiesNeedInit : 1;
    /* 0x00 */ u8 ignoreDrumPan : 1;
    /* 0x00 */ u8 bit1 : 1;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 instOrWave;
    /* 0x03 */ u8 unk03[2];
    /* 0x05 */ u8 portamentoTargetNote;
    /* 0x06 */ u8 pan;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ Portamento81113650 portamento;
    /* 0x18 */ u8 releaseRate;
    /* 0x19 */ u8 unk19[3];
    /* 0x1C */ u8* envelope;
    /* 0x20 */ u16 portamentoTime;
    /* 0x22 */ s16 transposition;
    /* 0x24 */ f32 freqScale;
    /* 0x28 */ f32 bendPitch;
    /* 0x2C */ u8 unk2C[0x40 - 0x2C];
    /* 0x40 */ s16 delay;
    /* 0x42 */ u8 unk42[2];
    /* 0x44 */ s16 duration;
    /* 0x46 */ u8 unk46[0x4C - 0x46];
    /* 0x4C */ u8* instrument;
    /* 0x50 */ Sound81113650* sound;
    /* 0x54 */ Channel81113650* channel;
} Layer81113650;

extern f32 D_81136778[];
extern s16 D_811858EC;
typedef struct Reverb81113650 {
    /* 0x000 */ u8 unk000[0x110];
    /* 0x110 */ Sound81113650 sound;
    /* 0x118 */ u8 unk118[0x158 - 0x118];
} Reverb81113650; // size = 0x158

extern Reverb81113650 D_81184110[];
u8* AudioPlayback_GetInstrumentTunedSample(u8* arg0, s32 arg1);
u8* AudioPlayback_GetDrum(s32 arg0, s32 arg1);

/**
 * Sets up the note's instrument, pitch and velocity from a note command. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqLayerProcessScriptStep4(Layer81113650* layer, s32 cmd_semitone) {
    s32 same_sound = 1;
    s32 instOrWave;
    s32 vel;
    f32 temp_f14;
    f32 temp_f2;
    Portamento81113650* portamento;
    f32 freqScale;
    f32 freq_scale2;
    Sound81113650* sound;
    u8* instrument;
    Drum81113650* drum;
    f32 tuning;
    Channel81113650* channel;
    SeqPlayer81113650* seqPlayer;
    u8 semitone = cmd_semitone;

    instOrWave = layer->instOrWave;
    channel = layer->channel;
    seqPlayer = channel->seqPlayer;

    if (instOrWave == 0xFF) {
        if (!channel->hasInstrument) {
            return -1;
        }
        instOrWave = channel->instOrWave;
    }

    switch (instOrWave) {
        case 0:
            semitone += channel->transposition + layer->transposition;
            drum = (Drum81113650*)AudioPlayback_GetDrum(channel->bankId, semitone);
            if (drum == NULL) {
                layer->stopSomething = 1;
                layer->duration = layer->delay;
                return -1;
            }
            sound = &drum->sound;
            layer->envelope = drum->envelope;
            layer->releaseRate = drum->releaseRate;
            if (!layer->ignoreDrumPan) {
                layer->pan = drum->pan;
            }
            layer->sound = sound;
            layer->freqScale = sound->tuning;
            break;

        default:
            semitone += seqPlayer->transposition + channel->transposition + layer->transposition;
            if (semitone >= 0x80) {
                layer->stopSomething = 1;
                return -1;
            }
            if (layer->instOrWave == 0xFF) {
                instrument = channel->instrument;
            } else {
                instrument = layer->instrument;
            }
            if (layer->portamento.mode != 0) {
                vel = (semitone > layer->portamentoTargetNote) ? semitone : layer->portamentoTargetNote;
                if (instrument != NULL) {
                    sound = (Sound81113650*)AudioPlayback_GetInstrumentTunedSample(instrument, vel);
                    same_sound = (layer->sound == sound);
                    layer->sound = sound;
                    tuning = sound->tuning;
                } else {
                    layer->sound = NULL;
                    tuning = 1.0f;
                    if (instOrWave >= 0xC0) {
                        layer->sound = &D_81184110[instOrWave - 0xC0].sound;
                    }
                }
                temp_f2 = D_81136778[(s32)semitone] * tuning; // FAKE: no-op cast; only changes the spill slot
                temp_f14 = D_81136778[layer->portamentoTargetNote] * tuning;
                portamento = &layer->portamento;
                switch (layer->portamento.mode & ~0x80) {
                    case 1:
                    case 3:
                    case 5:
                        freq_scale2 = temp_f2;
                        freqScale = temp_f14;
                        break;
                    case 2:
                    case 4:
                        freqScale = temp_f2;
                        freq_scale2 = temp_f14;
                        break;
                    default:
                        freqScale = temp_f2;
                        freq_scale2 = temp_f2;
                        break;
                }
                portamento->extent = (freq_scale2 / freqScale) - 1.0f;
                if (layer->portamento.mode & 0x80) {
                    portamento->speed = 32512.0f * (f32)(s32)seqPlayer->tempo /
                                        ((f32)layer->delay * (f32)D_811858EC * (f32)(s32)layer->portamentoTime);
                } else {
                    portamento->speed = 127.0f / (f32)(s32)layer->portamentoTime;
                }
                portamento->cur = 0.0f;
                layer->freqScale = freqScale;
                if ((layer->portamento.mode & ~0x80) == 5) {
                    layer->portamentoTargetNote = semitone;
                }
                break;
            }
            if (instrument != NULL) {
                sound = (Sound81113650*)AudioPlayback_GetInstrumentTunedSample(instrument, semitone);
                same_sound = (sound == layer->sound);
                layer->sound = sound;
                layer->freqScale = D_81136778[(s32)semitone] * sound->tuning; // FAKE: no-op cast
            } else {
                layer->sound = NULL;
                layer->freqScale = D_81136778[(s32)semitone]; // FAKE: no-op cast
                if (instOrWave >= 0xC0) {
                    layer->sound = &D_81184110[instOrWave - 0xC0].sound;
                }
            }
            break;
    }
    layer->duration = layer->delay;
    layer->freqScale *= layer->bendPitch;
    return same_sound;
}
