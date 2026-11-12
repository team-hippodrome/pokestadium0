/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "gb_tower_emulator_86CB0.h"

#include "fragments/fragment000_80C00/gb_tower_emulator_86CB0_types.h"

typedef struct SeqPlayer81113A44 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 muted : 1;
    /* 0x00 */ u32 rest : 29;
    /* 0x04 */ u8 unk04[0xD8 - 0x04];
    /* 0xD8 */ s32 skipTicks;
} SeqPlayer81113A44;

typedef struct Channel81113A44 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 stopScript : 1;
    /* 0x00 */ u32 stopSomething2 : 1;
    /* 0x00 */ u32 hasInstrument : 1;
    /* 0x00 */ u32 stereoHeadsetEffects : 1;
    /* 0x00 */ u32 largeNotes : 1;
    /* 0x00 */ u32 rest : 17;
    /* 0x03 */ u8 muteBehavior;
    /* 0x04 */ u8 unk04[9];
    /* 0x0D */ u8 velocityRandomVariance;
    /* 0x0E */ u8 gateTimeRandomVariance;
    /* 0x0F */ u8 unk0F[0x4C - 0x0F];
    /* 0x4C */ SeqPlayer81113A44* seqPlayer;
} Channel81113A44;

typedef struct ScriptState81113A44 {
    /* 0x00 */ u8* pc;
} ScriptState81113A44;

typedef struct Layer81113A44 {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stopSomething : 1;
    /* 0x00 */ u8 continuousNotes : 1;
    /* 0x00 */ u8 rest : 4;
    /* 0x01 */ u8 unk01[3];
    /* 0x04 */ u8 gateTime;
    /* 0x05 */ u8 unk05[0x2C - 0x05];
    /* 0x2C */ f32 velocitySquare2;
    /* 0x30 */ f32 velocitySquare;
    /* 0x34 */ u8 unk34[0x3C - 0x34];
    /* 0x3C */ s16 shortNoteDefaultDelay;
    /* 0x3E */ s16 lastDelay;
    /* 0x40 */ s16 delay;
    /* 0x42 */ s16 gateDelay;
    /* 0x44 */ u8 unk44[0x54 - 0x44];
    /* 0x54 */ Channel81113A44* channel;
    /* 0x58 */ ScriptState81113A44 scriptState;
} Layer81113A44;

extern u32 D_811859CC;

s32 func_81113A44(Layer81113A44* layer, s32 cmd) {
    ScriptState81113A44* state = &layer->scriptState;
    u16 delay;
    s32 velocity;
    Channel81113A44* channel = layer->channel;
    SeqPlayer81113A44* seqPlayer = channel->seqPlayer;
    s32 int_delta;
    f32 float_delta;

    if (cmd == 0xC0) {
        layer->delay = AudioSeq_ScriptReadCompressedU16(&state->pc);
        layer->stopSomething = 1;
        return -1;
    }

    layer->stopSomething = 0;

    if (channel->largeNotes == 1) {
        switch (cmd & 0xC0) {
            case 0x00:
                delay = AudioSeq_ScriptReadCompressedU16(&state->pc);
                velocity = *(state->pc++);
                layer->gateTime = *(state->pc++);
                layer->lastDelay = delay;
                break;
            case 0x40:
                delay = AudioSeq_ScriptReadCompressedU16(&state->pc);
                velocity = *(state->pc++);
                layer->gateTime = 0;
                layer->lastDelay = delay;
                break;
            case 0x80:
                delay = layer->lastDelay;
                velocity = *(state->pc++);
                layer->gateTime = *(state->pc++);
                break;
        }
        if (velocity > 0x7F || velocity < 0) {
            velocity = 0x7F;
        }
        layer->velocitySquare = (f32)velocity * (f32)velocity / 16129.0f;
        cmd -= (cmd & 0xC0);
    } else {
        switch (cmd & 0xC0) {
            case 0x00:
                delay = AudioSeq_ScriptReadCompressedU16(&state->pc);
                layer->lastDelay = delay;
                break;
            case 0x40:
                delay = layer->shortNoteDefaultDelay;
                break;
            case 0x80:
                delay = layer->lastDelay;
                break;
        }
        cmd -= (cmd & 0xC0);
    }

    if (channel->velocityRandomVariance != 0) {
        float_delta = layer->velocitySquare * (f32)(D_811859CC % channel->velocityRandomVariance) / 100.0f;
        if ((D_811859CC & 0x8000) != 0) {
            float_delta = -float_delta;
        }
        layer->velocitySquare2 = layer->velocitySquare + float_delta;
        if (layer->velocitySquare2 < 0.0f) {
            layer->velocitySquare2 = 0.0f;
        } else if (layer->velocitySquare2 > 1.0f) {
            layer->velocitySquare2 = 1.0f;
        }
    } else {
        layer->velocitySquare2 = layer->velocitySquare;
    }

    layer->delay = delay;
    layer->gateDelay = (layer->gateTime * delay) >> 8;
    if (channel->gateTimeRandomVariance != 0) {
        int_delta = (layer->gateDelay * (D_811859CC % channel->velocityRandomVariance)) / 100;
        if ((D_811859CC & 0x4000) != 0) {
            int_delta = -int_delta;
        }
        layer->gateDelay += int_delta;
        if (layer->gateDelay < 0) {
            layer->gateDelay = 0;
        } else if (layer->gateDelay > layer->delay) {
            layer->gateDelay = layer->delay;
        }
    }

    if ((seqPlayer->muted && (channel->muteBehavior & 0x50)) || channel->stopSomething2) {
        layer->stopSomething = 1;
        return -1;
    }
    if (seqPlayer->skipTicks != 0) {
        layer->stopSomething = 1;
        return -1;
    }
    return cmd;
}

/**
 * Splits the byte arg1 into two nibbles and stores each non-zero one in arg0:
 * the low nibble at offset 5 and the high nibble at offset 6. A zero nibble
 * leaves the corresponding byte unchanged. (arg1 itself is reused for the
 * high nibble, which is what the retail register use needs.)
 */
void func_81113E54(u8* arg0, u8 arg1) {
    s32 low;

    low = arg1 & 0xF;
    if (low != 0) {
        arg0[5] = low;
    }
    arg1 = arg1 >> 4;
    if (arg1 != 0) {
        arg0[6] = arg1;
    }
}

u8 func_81113E84(u8* arg0, u8 arg1, u8** arg2, u8* arg3) {
    u8* p = AudioPlayback_GetInstrumentInner(arg0[7], arg1);

    if (p == NULL) {
        *arg2 = NULL;
        return 0;
    }
    M2C_FIELD(arg3, s32*, 4) = M2C_FIELD(p, s32*, 4);
    arg3[0] = p[3];
    *arg2 = p;
    arg1++;
    return arg1;
}

void func_81113EF4(u8* arg0, u8 arg1) {
    s16 ret;

    if (arg1 >= 0x80) {
        M2C_FIELD(arg0, s16*, 0x22) = arg1;
        M2C_FIELD(arg0, s32*, 0x48) = 0;
    } else if (arg1 == 0x7F) {
        M2C_FIELD(arg0, s16*, 0x22) = 0;
        M2C_FIELD(arg0, s32*, 0x48) = 1;
    } else {
        ret = M2C_FIELD(arg0, s16*, 0x22) = func_81113E84(arg0, arg1, (u8**)(arg0 + 0x48), arg0 + 0x7C);
        if (ret == 0) {
            ((AudioStreamFlags*)arg0)->active = 0;
            return;
        }
    }
    ((AudioStreamFlags*)arg0)->active = 1;
}

void func_81113F84(u8* arg0, u8 arg1) {
    *(f32*)(arg0 + 0x2C) = (f32)(s32)arg1 / 127.0f;
}

typedef struct ScriptState81113FA8 {
    /* 0x00 */ u8* pc;
    /* 0x04 */ u8* stack[4];
    /* 0x14 */ u8 remLoopIters[4];
    /* 0x18 */ u8 depth;
    /* 0x19 */ s8 value;
} ScriptState81113FA8;

typedef struct Layer81113FA8 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 rest : 30;
    /* 0x04 */ u8 unk04[0x58 - 0x04];
    /* 0x58 */ u8* pc;
} Layer81113FA8;

typedef struct SeqPlayer81113FA8 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 muted : 1;
    /* 0x00 */ u32 rest : 29;
    /* 0x04 */ u8 seqId;
    /* 0x05 */ u8 unk05[0x18 - 0x05];
    /* 0x18 */ u8* seqData;
    /* 0x1C */ u8 unk1C[0x34 - 0x1C];
    /* 0x34 */ struct Channel81113FA8* channels[16];
} SeqPlayer81113FA8;

typedef struct Channel81113FA8 {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stopScript : 1;
    /* 0x00 */ u8 stopSomething2 : 1;
    /* 0x00 */ u8 hasInstrument : 1;
    /* 0x00 */ u8 stereoHeadsetEffects : 1;
    /* 0x00 */ u8 largeNotes : 1;
    /* 0x00 */ u8 unused : 1;
    /* 0x01 */ u8 changeFreqScale : 1;
    /* 0x01 */ u8 changeVolume : 1;
    /* 0x01 */ u8 changePan : 1;
    /* 0x01 */ u8 changeRest : 5;
    /* 0x02 */ u8 noteAllocPolicy;
    /* 0x03 */ u8 muteBehavior;
    /* 0x04 */ u8 reverb;
    /* 0x05 */ u8 notePriority;
    /* 0x06 */ u8 someOtherPriority;
    /* 0x07 */ u8 bankId;
    /* 0x08 */ u8 reverbIndex;
    /* 0x09 */ u8 bookOffset;
    /* 0x0A */ u8 newPan;
    /* 0x0B */ u8 panChannelWeight;
    /* 0x0C */ u8 gain;
    /* 0x0D */ u8 velocityRandomVariance;
    /* 0x0E */ u8 gateTimeRandomVariance;
    /* 0x0F */ u8 combFilterSize;
    /* 0x10 */ u16 vibratoRateStart;
    /* 0x12 */ u16 vibratoExtentStart;
    /* 0x14 */ u16 vibratoRateTarget;
    /* 0x16 */ u16 vibratoExtentTarget;
    /* 0x18 */ u16 vibratoRateChangeDelay;
    /* 0x1A */ u16 vibratoExtentChangeDelay;
    /* 0x1C */ u16 vibratoDelay;
    /* 0x1E */ u16 delay;
    /* 0x20 */ u16 combFilterGain;
    /* 0x22 */ s16 instOrWave;
    /* 0x24 */ s16 transposition;
    /* 0x26 */ u8 unk26[2];
    /* 0x28 */ f32 volumeScale;
    /* 0x2C */ f32 volume;
    /* 0x30 */ s32 pan;
    /* 0x34 */ f32 appliedVolume;
    /* 0x38 */ f32 freqScale;
    /* 0x3C */ u8 (*dynTable)[][2];
    /* 0x40 */ u8 unk40[0x48 - 0x40];
    /* 0x48 */ u8* instrument;
    /* 0x4C */ SeqPlayer81113FA8* seqPlayer;
    /* 0x50 */ Layer81113FA8* layers[4];
    /* 0x60 */ ScriptState81113FA8 scriptState;
    /* 0x7C */ u8 decayIndex;
    /* 0x7D */ u8 sustain;
    /* 0x7E */ u8 unk7E[2];
    /* 0x80 */ u8* envelope;
    /* 0x84 */ u8 notePool[0xC4 - 0x84];
    /* 0xC4 */ s8 soundScriptIO[8];
    /* 0xCC */ u16 unk_CC;
    /* 0xCE */ u8 unkCE[2];
    /* 0xD0 */ s16* filter;
} Channel81113FA8;

extern u8* D_811858A8;
extern u8 D_81138690[];
extern u32 D_811859CC;
extern f32 D_81135F78[];
extern f32 D_81136378[];
s32 AudioHeap_SearchCaches(s32, s32, s32);
void AudioHeap_LoadFilter(s16*, s32, s32);
s32 func_8110E500(s32, u8, s8*);
void AudioPlayback_NotePoolFill(void*, s32);
void func_81112B84(void*);
s32 AudioSeq_SeqChannelSetLayer(void*, s32);
void AudioSeq_SeqLayerProcessScript(void*);
s32 AudioSeq_HandleScriptFlowControl(void*, void*, s32, s32);

void func_81113FA8(Channel81113FA8* channel) {
    s32 i;
    u8* data;
    s8 signed_param;
    u8 command;
    u8 highBits;
    u8 low_bits;
    u8* test;
    SeqPlayer81113FA8* seqPlayer;

    if (channel->stopScript) {
        goto exit_loop;
    }
    seqPlayer = channel->seqPlayer;
    if (seqPlayer->muted && (channel->muteBehavior & 0x80)) {
        return;
    }

    if (channel->delay >= 2) {
        channel->delay--;
        goto exit_loop;
    }

    while (1) {
        ScriptState81113FA8* scriptState = &channel->scriptState;
        UNUSED s16 pad1; // FAKE: stack pad; only reserves frame space
        u16 offset;
        u32 parameters[3];
        s32 result;

        command = AudioSeq_ScriptReadU8(&scriptState->pc);
        if (command >= 0xB0) {
            highBits = (D_81138690 + 0xB0)[command - 0xB0]; // FAKE: the +0xB0/-0xB0 pair only changes register allocation
            low_bits = highBits & 3;

            for (i = 0; i < low_bits; i++, highBits <<= 1) {
                if (!(highBits & 0x80)) {
                    parameters[i] = AudioSeq_ScriptReadU8(&scriptState->pc);
                } else {
                    parameters[i] = AudioSeq_ScriptReadS16(&scriptState->pc);
                }
            }
            if (command >= 0xF2) {
                result = AudioSeq_HandleScriptFlowControl(seqPlayer, scriptState, command, parameters[0]);
                if (result != 0) {
                    if (result == -1) {
                        func_81112B84(channel);
                    } else {
                        channel->delay = result;
                    }
                    break;
                }
            } else {
                switch (command) {
                    case 0xEA:
                        channel->stopScript = 1;
                        goto exit_loop;
                    case 0xF1:
                        AudioPlayback_NotePoolClear((s8*)&channel->notePool);
                        command = (u8)parameters[0];
                        AudioPlayback_NotePoolFill(&channel->notePool, command);
                        break;
                    case 0xF0:
                        AudioPlayback_NotePoolClear((s8*)&channel->notePool);
                        break;
                    case 0xC2:
                        offset = (u16)parameters[0];
                        channel->dynTable = (void*)&seqPlayer->seqData[offset];
                        break;
                    case 0xC5:
                        if (scriptState->value != -1) {
                            data = (*channel->dynTable)[scriptState->value];
                            offset = (u16)((data[0] << 8) + data[1]);
                            channel->dynTable = (void*)&seqPlayer->seqData[offset];
                        }
                        break;
                    case 0xEB:
                        command = (u8)parameters[0];
                        offset = ((u16*)D_811858A8)[seqPlayer->seqId];
                        low_bits = D_811858A8[offset];
                        command = D_811858A8[offset + low_bits - command];
                        if (AudioHeap_SearchCaches(1, 2, command)) {
                            channel->bankId = command;
                        }
                        parameters[0] = parameters[1];
                    case 0xC1:
                        command = (u8)parameters[0];
                        func_81113EF4((u8*)channel, command);
                        break;
                    case 0xC3:
                        channel->largeNotes = 0;
                        break;
                    case 0xC4:
                        channel->largeNotes = 1;
                        break;
                    case 0xDF:
                        command = (u8)parameters[0];
                        func_81113F84((u8*)channel, command);
                        channel->changeVolume = 1;
                        break;
                    case 0xE0:
                        command = (u8)parameters[0];
                        channel->volumeScale = (f32)(s32)command / 128.0f;
                        channel->changeVolume = 1;
                        break;
                    case 0xDE:
                        offset = (u16)parameters[0];
                        channel->freqScale = (f32)(s32)offset / 32768.0f;
                        channel->changeFreqScale = 1;
                        break;
                    case 0xD3:
                        command = (u8)parameters[0];
                        command += 0x80;
                        channel->freqScale = D_81135F78[command];
                        channel->changeFreqScale = 1;
                        break;
                    case 0xEE:
                        command = (u8)parameters[0];
                        command += 0x80;
                        channel->freqScale = D_81136378[command];
                        channel->changeFreqScale = 1;
                        break;
                    case 0xDD:
                        command = (u8)parameters[0];
                        channel->newPan = command;
                        channel->changePan = 1;
                        break;
                    case 0xDC:
                        command = (u8)parameters[0];
                        channel->panChannelWeight = command;
                        channel->changePan = 1;
                        break;
                    case 0xDB:
                        signed_param = (s8)parameters[0];
                        channel->transposition = signed_param;
                        break;
                    case 0xDA:
                        offset = (u16)parameters[0];
                        channel->envelope = &seqPlayer->seqData[offset];
                        break;
                    case 0xD9:
                        command = (u8)parameters[0];
                        channel->decayIndex = command;
                        break;
                    case 0xD8:
                        command = (u8)parameters[0];
                        channel->vibratoExtentTarget = command * 8;
                        channel->vibratoExtentStart = 0;
                        channel->vibratoExtentChangeDelay = 0;
                        break;
                    case 0xD7:
                        command = (u8)parameters[0];
                        channel->vibratoRateChangeDelay = 0;
                        channel->vibratoRateTarget = command * 32;
                        channel->vibratoRateStart = command * 32;
                        break;
                    case 0xE2:
                        command = (u8)parameters[0];
                        channel->vibratoExtentStart = command * 8;
                        command = (u8)parameters[1];
                        channel->vibratoExtentTarget = command * 8;
                        command = (u8)parameters[2];
                        channel->vibratoExtentChangeDelay = command * 16;
                        break;
                    case 0xE1:
                        command = (u8)parameters[0];
                        channel->vibratoRateStart = command * 32;
                        command = (u8)parameters[1];
                        channel->vibratoRateTarget = command * 32;
                        command = (u8)parameters[2];
                        channel->vibratoRateChangeDelay = command * 16;
                        break;
                    case 0xE3:
                        command = (u8)parameters[0];
                        channel->vibratoDelay = command * 16;
                        break;
                    case 0xD4:
                        command = (u8)parameters[0];
                        channel->reverb = command;
                        break;
                    case 0xC6:
                        command = (u8)parameters[0];
                        offset = ((u16*)D_811858A8)[seqPlayer->seqId];
                        low_bits = D_811858A8[offset];
                        command = D_811858A8[offset + low_bits - command];
                        if (AudioHeap_SearchCaches(1, 2, command)) {
                            channel->bankId = command;
                        }
                        break;
                    case 0xC7:
                        command = (u8)parameters[0];
                        offset = (u16)parameters[1];
                        test = &seqPlayer->seqData[offset];
                        test[0] = (u8)scriptState->value + command;
                        break;
                    case 0xC8:
                    case 0xC9:
                    case 0xCC:
                        signed_param = (s8)parameters[0];
                        if (command == 0xC8) {
                            scriptState->value -= signed_param;
                        } else if (command == 0xCC) {
                            scriptState->value = signed_param;
                        } else {
                            scriptState->value &= signed_param;
                        }
                        break;
                    case 0xCD:
                        command = (u8)parameters[0];
                        func_81112B84(seqPlayer->channels[command]);
                        break;
                    case 0xCA:
                        command = (u8)parameters[0];
                        channel->muteBehavior = command;
                        channel->changeVolume = 1;
                        break;
                    case 0xCB:
                        offset = (u16)parameters[0];
                        scriptState->value = *(seqPlayer->seqData + (u32)(offset + scriptState->value));
                        break;
                    case 0xCE:
                        offset = (u16)parameters[0];
                        channel->unk_CC = offset;
                        break;
                    case 0xCF:
                        offset = (u16)parameters[0];
                        test = &seqPlayer->seqData[offset];
                        test[0] = (channel->unk_CC >> 8) & 0xFF;
                        test[1] = channel->unk_CC & 0xFF;
                        break;
                    case 0xD0:
                        command = (u8)parameters[0];
                        channel->stereoHeadsetEffects = command;
                        break;
                    case 0xD1:
                        command = (u8)parameters[0];
                        channel->noteAllocPolicy = command;
                        break;
                    case 0xD2:
                        command = (u8)parameters[0];
                        channel->sustain = command;
                        break;
                    case 0xE5:
                        command = (u8)parameters[0];
                        channel->reverbIndex = command;
                        break;
                    case 0xE4:
                        if (scriptState->value != -1) {
                            data = (*channel->dynTable)[scriptState->value];
                            highBits = scriptState->depth; // FAKE: reuses highBits as a depth copy for register allocation
                            scriptState->stack[highBits] = scriptState->pc;
                            scriptState->depth++;
                            offset = (u16)((data[0] << 8) + data[1]);
                            scriptState->pc = seqPlayer->seqData + offset;
                        }
                        break;
                    case 0xE6:
                        command = (u8)parameters[0];
                        channel->bookOffset = command;
                        break;
                    case 0xE7:
                        offset = (u16)parameters[0];
                        data = &seqPlayer->seqData[offset];
                        channel->muteBehavior = data[0];
                        data += 3;
                        channel->noteAllocPolicy = data[-2];
                        func_81113E54((u8*)channel, data[-1]);
                        channel->transposition = (s8)data[0];
                        data += 4;
                        channel->newPan = data[-3];
                        channel->panChannelWeight = data[-2];
                        channel->reverb = data[-1];
                        channel->reverbIndex = data[0];
                        channel->changePan = 1;
                        break;
                    case 0xE8:
                        channel->muteBehavior = parameters[0];
                        channel->noteAllocPolicy = parameters[1];
                        command = (u8)parameters[2];
                        func_81113E54((u8*)channel, command);
                        channel->transposition = (s8)AudioSeq_ScriptReadU8(&scriptState->pc);
                        channel->newPan = AudioSeq_ScriptReadU8(&scriptState->pc);
                        channel->panChannelWeight = AudioSeq_ScriptReadU8(&scriptState->pc);
                        channel->reverb = AudioSeq_ScriptReadU8(&scriptState->pc);
                        channel->reverbIndex = AudioSeq_ScriptReadU8(&scriptState->pc);
                        channel->changePan = 1;
                        break;
                    case 0xEC:
                        channel->vibratoExtentTarget = 0;
                        channel->vibratoExtentStart = 0;
                        channel->vibratoExtentChangeDelay = 0;
                        channel->vibratoRateTarget = 0;
                        channel->vibratoRateStart = 0;
                        channel->vibratoRateChangeDelay = 0;
                        channel->filter = NULL;
                        channel->gain = 0;
                        channel->sustain = 0;
                        channel->velocityRandomVariance = 0;
                        channel->gateTimeRandomVariance = 0;
                        channel->combFilterSize = 0;
                        channel->combFilterGain = 0;
                        channel->bookOffset = 0;
                        channel->freqScale = 1.0f;
                        break;
                    case 0xE9:
                        func_81113E54((u8*)channel, (u8)parameters[0]);
                        break;
                    case 0xED:
                        command = (u8)parameters[0];
                        channel->gain = command;
                        break;
                    case 0xB0:
                        offset = (u16)parameters[0];
                        data = seqPlayer->seqData + offset;
                        channel->filter = (s16*)data;
                        break;
                    case 0xB1:
                        channel->filter = NULL;
                        break;
                    case 0xB3:
                        command = parameters[0];
                        if (channel->filter != NULL) {
                            low_bits = (command >> 4) & 0xF;
                            command &= 0xF;
                            AudioHeap_LoadFilter(channel->filter, low_bits, command);
                        }
                        break;
                    case 0xB2:
                        offset = (u16)parameters[0];
                        channel->unk_CC = *(u16*)(seqPlayer->seqData + (u32)(offset + scriptState->value * 2));
                        break;
                    case 0xB4:
                        channel->dynTable = (void*)&seqPlayer->seqData[channel->unk_CC];
                        break;
                    case 0xB5:
                        channel->unk_CC = ((u16*)(channel->dynTable))[scriptState->value];
                        break;
                    case 0xB6:
                        scriptState->value = (*channel->dynTable)[0][scriptState->value];
                        break;
                    case 0xB7:
                        channel->unk_CC = (parameters[0] == 0) ? D_811859CC & 0xFFFF : D_811859CC % parameters[0];
                        break;
                    case 0xB8:
                        scriptState->value = (parameters[0] == 0) ? D_811859CC & 0xFF : D_811859CC % parameters[0];
                        break;
                    case 0xB9:
                        channel->velocityRandomVariance = parameters[0];
                        break;
                    case 0xBA:
                        channel->gateTimeRandomVariance = parameters[0];
                        break;
                    case 0xBB:
                        channel->combFilterSize = parameters[0];
                        channel->combFilterGain = parameters[1];
                        break;
                }
            }
        } else if (command >= 0x80) {
            low_bits = command & 7;
            switch (command & 0xF8) {
                case 0x80:
                    if (channel->layers[low_bits] != NULL) {
                        scriptState->value = channel->layers[low_bits]->finished;
                    } else {
                        scriptState->value = -1;
                    }
                    break;
                case 0x88:
                    offset = AudioSeq_ScriptReadS16(&scriptState->pc);
                    if (!AudioSeq_SeqChannelSetLayer(channel, low_bits)) {
                        channel->layers[low_bits]->pc = &seqPlayer->seqData[offset];
                    }
                    break;
                case 0x90:
                    AudioSeq_SeqLayerFree((s8**)channel, low_bits);
                    break;
                case 0x98:
                    if (scriptState->value != -1 && AudioSeq_SeqChannelSetLayer(channel, low_bits) != -1) {
                        data = (*channel->dynTable)[scriptState->value];
                        offset = (data[0] << 8) + data[1];
                        channel->layers[low_bits]->pc = &seqPlayer->seqData[offset];
                    }
                    break;
            }
        } else {
            low_bits = command & 0xF;
            switch (command & 0xF0) {
                case 0x00:
                    channel->delay = low_bits;
                    goto exit_loop;
                case 0x10:
                    channel->soundScriptIO[low_bits] = -1;
                    if (func_8110E500(channel->bankId, scriptState->value, &channel->soundScriptIO[low_bits]) == -1) {} // karodo
                    break;
                case 0x70:
                    channel->soundScriptIO[low_bits] = scriptState->value;
                    break;
                case 0x60:
                    scriptState->value = channel->soundScriptIO[low_bits];
                    if (low_bits < 2) {
                        channel->soundScriptIO[low_bits] = -1;
                    }
                    break;
                case 0x50:
                    scriptState->value -= channel->soundScriptIO[low_bits];
                    break;
                case 0x20:
                    offset = AudioSeq_ScriptReadS16(&scriptState->pc);
                    AudioSeq_SequenceChannelEnable((Particle2D68**)seqPlayer, low_bits, (s32)&seqPlayer->seqData[offset]);
                    break;
                case 0x30:
                    command = AudioSeq_ScriptReadU8(&scriptState->pc);
                    seqPlayer->channels[low_bits]->soundScriptIO[command] = scriptState->value;
                    break;
                case 0x40:
                    command = AudioSeq_ScriptReadU8(&scriptState->pc);
                    scriptState->value = seqPlayer->channels[low_bits]->soundScriptIO[command];
                    break;
            }
        }
    }
exit_loop:
    for (i = 0; i < 4; i++) {
        if (channel->layers[i] != NULL) {
            AudioSeq_SeqLayerProcessScript(channel->layers[i]);
        }
    }
}
