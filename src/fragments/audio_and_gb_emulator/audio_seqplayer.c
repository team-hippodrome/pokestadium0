/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "audio_and_gb_emulator.h"

// Declared here instead of in a header: the callers of these disagree on their types.
extern SequencePlayer D_81184668[];
extern AudioBufferParameters D_811858B8;
extern volatile u32 D_811859D4;
void AudioPlayback_NotePoolClear(s8*);
void AudioPlayback_SeqLayerNoteDecay(SequenceLayer*);
void AudioSeq_AudioListPushBack(s8 *arg0, s8 *arg1);

extern u8 D_81138690[];
void AudioSeq_SequencePlayerDisableChannels(u8*, s32);
s32 AudioLoad_IsFontLoadComplete(s32);
s32 AudioLoad_IsSeqLoadComplete(s32);
void AudioLoad_SetFontLoadStatus(s32, s32);
void AudioLoad_SetSeqLoadStatus(s32, s32);
extern M2C_UNK D_81184380;
u8* AudioPlayback_GetInstrumentInner(s32, s32);
extern u16 D_81138A96;
extern u32 D_81138A90;
extern s16 D_81180700;
extern s16 D_81180702;
extern u8* D_81180704;
extern GbApuWrite D_81180848[GB_APU_WRITE_QUEUE_LEN];
extern u8 D_81182468[0x40];
extern s32 D_811824A8;
extern GbApuStatusOverride D_811824B8;
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
extern SequencePlayer D_81287B08_jp[];
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
extern SequenceLayer D_811847C8[1];
extern s16 D_811858CC;
extern SequencePlayer D_81184668[];

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

u16 AudioSeq_ScriptReadCompressedU16(u8** arg0);

/**
 * Runs a script control-flow command (end, call, loop, jump, branch). Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_HandleScriptFlowControl(SequencePlayer* seq_player, SeqScriptState811126B8* state, s32 cmd, s32 cmd_arg) {
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

extern SequenceChannel D_81184850;

void AudioPlayback_InitNoteLists(void*);
extern u8 D_81136998[];
/**
 * Resets a sequence channel to its defaults. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_InitSequenceChannel(void* obj) {
    SequenceChannel* channel = obj;
    s32 i;

    if (channel != &D_81184850) {
        channel->enabled = 0;
        channel->finished = 0;
        channel->stopScript = 0;
        channel->muted = 0;
        channel->hasInstrument = 0;
        channel->stereoHeadsetEffects = 0;
        channel->transposition = 0;
        channel->largeNotes = 0;
        channel->bookOffset = 0;
        channel->changes.asByte = 0xFF;
        channel->scriptState.depth = 0;
        channel->newPan = 0x40;
        channel->panChannelWeight = 0x80;
        channel->velocityRandomVariance = 0;
        channel->gateTimeRandomVariance = 0;
        channel->noteUnused = 0;
        channel->reverbIndex = 0;
        channel->reverb = 0;
        channel->gain = 0;
        channel->notePriority = 3;
        channel->someOtherPriority = 1;
        channel->delay = 0;
        channel->adsr.envelope = D_81136998;
        channel->adsr.decayIndex = 0x20;
        channel->vibratoRateTarget = 0x800;
        channel->vibratoRateStart = 0x800;
        channel->adsr.sustain = 0;
        channel->vibratoExtentTarget = 0;
        channel->vibratoExtentStart = 0;
        channel->vibratoRateChangeDelay = 0;
        channel->vibratoExtentChangeDelay = 0;
        channel->vibratoDelay = 0;
        channel->filter = 0;
        channel->combFilterGain = 0;
        channel->combFilterSize = 0;
        channel->volume = 1.0f;
        channel->volumeScale = 1.0f;
        channel->freqScale = 1.0f;
        for (i = 0; i < 8; i++) {
            channel->soundScriptIO[i] = -1;
        }
        channel->unused = 0;
        AudioPlayback_InitNoteLists(&channel->notePool);
    }
}

extern struct AudioListItem D_81184928;
s32 AudioSeq_AudioListPopBack(AudioListItem* list);
void AudioPlayback_SeqLayerNoteDecay();
/**
 * Gives channel `arg0` a layer in slot `arg1`, taking one from the free list when needed. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqChannelSetLayer(SequenceChannel* arg0, s32 arg1) {
    SequenceLayer* p;
    s32 pad; // FAKE: stack padding
    if (arg0->layers[arg1] == NULL) {
        arg0->layers[arg1] = (SequenceLayer*)AudioSeq_AudioListPopBack((s8*)&D_81184928);
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
    p->stereo.asByte = 0x40;
    p->portamento.mode = 0;
    p->scriptState.depth = 0;
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
void AudioSeq_SeqLayerDisable(SequenceLayer* arg0) {
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
        AudioSeq_SeqLayerDisable((SequenceLayer*)temp);
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
    ((SequenceChannel*)arg0)->enabled = 0;
    ((SequenceChannel*)arg0)->finished = 1;
}

/**
 * Resets each channel selected in `mask`. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequencePlayerSetupChannels(SequencePlayer* seqPlayer, u16 mask) {
    s32 i;
    SequenceChannel* channel;

    for (i = 0; i < 16; i++) {
        if (mask & 1) {
            channel = seqPlayer->channels[i];
            channel->fontId = seqPlayer->defaultFont;
            channel->muteBehavior = seqPlayer->muteBehavior;
            channel->noteAllocPolicy = seqPlayer->noteAllocPolicy;
        }
        mask = (s32)mask >> 1;
    }
}

void func_81112B84(SequenceChannel*);

/**
 * Disables each channel selected in `channel_bits`. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioSeq_SequencePlayerDisableChannels(u8* seqPlayer, s32 channel_bits) {
    SequenceChannel* channel;
    s32 i;

    for (i = 0; i < 16; i++) {
        channel = M2C_FIELD(seqPlayer, SequenceChannel**, 0x34 + i * 4);
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
void AudioSeq_SequenceChannelEnable(SequencePlayer* seqPlayer, u8 channelIndex, void* script) {
    SequenceChannel* p = seqPlayer->channels[channelIndex];
    s32 i;

    p->scriptState.depth = 0;
    p->scriptState.pc = script;
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
    ((SequencePlayer*)arg0)->finished = 1;
    ((SequencePlayer*)arg0)->enabled = 0;
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
s32 AudioSeq_AudioListPopBack(AudioListItem* list) {
    AudioListItem* item;

    item = list->prev;
    if (item == list) {
        return 0;
    }
    item->prev->next = list;
    list->prev = item->prev;
    item->prev = NULL;
    list->u.count = (s32)(list->u.count - 1);
    return (s32)item->u.value;
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
    D_81184928.u.count = 0;
    D_81184928.pool = 0;
    for (i = 0; i < 1; i++) {
        D_811847C8[i].listItem.u.value = &D_811847C8[i];
        D_811847C8[i].listItem.prev = NULL;
        AudioSeq_AudioListPushBack((s8*)&D_81184928, (s8*)&D_811847C8[i].listItem);
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
void AudioSeq_SeqLayerProcessScript(SequenceLayer* arg0) {
    s32 ret;
    if (arg0->enabled) {
        if (arg0->delay >= 2) {
            arg0->delay--;
            if (!arg0->stopSomething && arg0->gateDelay >= arg0->delay) {
                AudioPlayback_SeqLayerNoteDecay((SequenceLayer*)arg0);
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
                    AudioPlayback_SeqLayerNoteDecay((SequenceLayer*)arg0);
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
void AudioSeq_SeqLayerProcessScriptStep1(SequenceLayer* arg0) {
    if (!arg0->continuousNotes) {
        AudioPlayback_SeqLayerNoteDecay((SequenceLayer*)arg0);
    } else if (arg0->note != NULL && arg0 == arg0->note->playbackState.wantedParentLayer) {
        AudioPlayback_SeqLayerNoteDecay((SequenceLayer*)arg0);
    }
    switch (arg0->portamento.mode & ~0x80) {
        case 1:
        case 2:
            arg0->portamento.mode = 0;
            break;
    }
    arg0->notePropertiesNeedInit = 1;
}

s8* AudioPlayback_AllocNote(s8*);
void func_81112278(void*);

/* SequenceLayer and Sample as AudioSeq_SeqLayerProcessScriptStep5 reads them. The layouts are the same as
 * SequenceLayer/Sample, but the function only matches with the layer flags in a u32 container and the sample
 * word split as codec:4/medium:2/rest:26 (tested: SequenceLayer's u8 flag byte or Sample's finer split both
 * change the register allocation), so this view stays. */
typedef struct SampleStep5 {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 rest : 26;
} SampleStep5;
typedef struct SoundStep5 {
    /* 0x00 */ SampleStep5* sample;
} SoundStep5;

typedef struct SequenceLayerFlagsU32 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 stopSomething : 1;
    /* 0x00 */ u32 continuousNotes : 1;
    /* 0x00 */ u32 bit3 : 1;
    /* 0x00 */ u32 notePropertiesNeedInit : 1;
    /* 0x00 */ u32 ignoreDrumPan : 1;
    /* 0x00 */ u32 bit1 : 1;
    /* 0x01 */ u32 pad01 : 16;
    /* 0x03 */ u8 status;
    /* 0x04 */ u8 pad04[0x48 - 0x04];
    /* 0x48 */ Note* note;
    /* 0x4C */ u8 pad4C[4];
    /* 0x50 */ struct SoundStep5* sound;
} SequenceLayerFlagsU32;

/**
 * Gets a note for the layer, reusing the current one for the same sound. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqLayerProcessScriptStep5(SequenceLayerFlagsU32* layer, u32 same_sound) {
    Note* note;

    if (!layer->stopSomething && layer->sound != NULL && layer->sound->sample->codec == 2 &&
        layer->sound->sample->medium != 0) {
        layer->stopSomething = 1;
        return -1;
    }

    if (layer->continuousNotes == 1 && layer->bit1 == 1) {
        return 0;
    }

    if (layer->continuousNotes != 1 || layer->note == NULL || !layer->status || same_sound != 1 ||
        layer != (SequenceLayerFlagsU32*)layer->note->playbackState.parentLayer) {
        if (same_sound == 0) {
            AudioPlayback_SeqLayerNoteDecay((SequenceLayer*)layer);
        }
        layer->note = (Note*)AudioPlayback_AllocNote((s8*)layer);
    }
    if (layer->note != NULL && layer->note->playbackState.parentLayer == (SequenceLayer*)layer) {
        note = layer->note;
        func_81112278(note);
    }
    return 0;
}

extern f32 D_81136378[];
u8 func_81113E84(u8* arg0, u8 arg1, u8** arg2, u8* arg3);

/**
 * Runs layer script commands until a note command. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqLayerProcessScriptStep2(SequenceLayer* layer) {
    SequenceChannel* channel = layer->channel;
    SeqScriptState* state = &layer->scriptState;
    SequencePlayer* seqPlayer = channel->seqPlayer;
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
            AudioSeq_SeqLayerDisable((SequenceLayer*)layer);
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
                AudioPlayback_SeqLayerNoteDecay((SequenceLayer*)layer);
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
                        layer->adsr.decayIndex = 0;
                    }
                    break;
                }
                if ((layer->instOrWave = func_81113E84((u8*)channel, cmd, &layer->instrument, &layer->adsr.decayIndex)) == 0) {
                    layer->instOrWave = 0xFF;
                }
                break;
            case 0xC7:
                layer->portamento.mode = AudioSeq_ScriptReadU8(&state->pc);
                cmd = AudioSeq_ScriptReadU8(&state->pc);
                cmd += channel->transposition;
                cmd += layer->transposition;
                cmd += seqPlayer->transposition;
                if (cmd >= 0x80) {
                    cmd = 0;
                }
                layer->portamentoTargetNote = cmd;
                if (layer->portamento.mode & 0x80) {
                    layer->portamentoTime = *(state->pc++);
                    break;
                }
                cmd_arg16 = AudioSeq_ScriptReadCompressedU16(&state->pc);
                layer->portamentoTime = cmd_arg16;
                break;
            case 0xC8:
                layer->portamento.mode = 0;
                break;
            case 0xCB:
                cmd_arg16 = AudioSeq_ScriptReadS16(&state->pc);
                layer->adsr.envelope = seqPlayer->seqData + cmd_arg16;
            case 0xCF:
                layer->adsr.decayIndex = AudioSeq_ScriptReadU8(&state->pc);
                break;
            case 0xCC:
                layer->ignoreDrumPan = 1;
                break;
            case 0xCD:
                layer->stereo.asByte = AudioSeq_ScriptReadU8(&state->pc);
                break;
            case 0xCE:
                layer->bend = D_81136378[(u8)(AudioSeq_ScriptReadU8(&state->pc) + 0x80)];
                break;
            default:
                switch (cmd & 0xF0) {
                    case 0xD0:
                        velocity = seqPlayer->shortNoteVelocityTable[cmd & 0xF];
                        layer->velocitySquare = (f32)(velocity * velocity) / 16129.0f;
                        break;
                    case 0xE0:
                        layer->noteDuration = seqPlayer->shortNoteGateTimeTable[cmd & 0xF];
                        break;
                }
                break;
        }
    }
}

extern f32 D_81136778[];
extern s16 D_811858EC;
extern SynthesisReverb D_81184110[];
u8* AudioPlayback_GetInstrumentTunedSample(u8* arg0, s32 arg1);
u8* AudioPlayback_GetDrum(s32 arg0, s32 arg1);

/**
 * Sets up the note's instrument, pitch and velocity from a note command. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioSeq_SeqLayerProcessScriptStep4(SequenceLayer* layer, s32 cmd_semitone) {
    s32 same_sound = 1;
    s32 instOrWave;
    s32 vel;
    f32 temp_f14;
    f32 temp_f2;
    Portamento* portamento;
    f32 freqScale;
    f32 freq_scale2;
    SoundFontSound* sound;
    u8* instrument;
    Drum* drum;
    f32 tuning;
    SequenceChannel* channel;
    SequencePlayer* seqPlayer;
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
            drum = (Drum*)AudioPlayback_GetDrum(channel->fontId, semitone);
            if (drum == NULL) {
                layer->stopSomething = 1;
                layer->duration = layer->delay;
                return -1;
            }
            sound = &drum->sound;
            layer->adsr.envelope = drum->envelope;
            layer->adsr.decayIndex = drum->adsrDecayIndex;
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
                    sound = (SoundFontSound*)AudioPlayback_GetInstrumentTunedSample(instrument, vel);
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
                sound = (SoundFontSound*)AudioPlayback_GetInstrumentTunedSample(instrument, semitone);
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
    layer->freqScale *= layer->bend;
    return same_sound;
}
