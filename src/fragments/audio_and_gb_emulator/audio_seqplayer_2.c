/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "audio_and_gb_emulator.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void AudioPlayback_NotePoolClear(s8*);


extern u32 D_811859CC;

s32 func_81113A44(SequenceLayer* layer, s32 cmd) {
    SeqScriptState* state = &layer->scriptState;
    u16 delay;
    s32 velocity;
    SequenceChannel* channel = layer->channel;
    SequencePlayer* seqPlayer = channel->seqPlayer;
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
                layer->noteDuration = *(state->pc++);
                layer->lastDelay = delay;
                break;
            case 0x40:
                delay = AudioSeq_ScriptReadCompressedU16(&state->pc);
                velocity = *(state->pc++);
                layer->noteDuration = 0;
                layer->lastDelay = delay;
                break;
            case 0x80:
                delay = layer->lastDelay;
                velocity = *(state->pc++);
                layer->noteDuration = *(state->pc++);
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
    layer->gateDelay = (layer->noteDuration * delay) >> 8;
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

    if ((seqPlayer->muted && (channel->muteBehavior & 0x50)) || channel->muted) {
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
            ((ChannelFlags81113EF4*)arg0)->hasInstrument = 0;
            return;
        }
    }
    ((ChannelFlags81113EF4*)arg0)->hasInstrument = 1;
}

void func_81113F84(u8* arg0, u8 arg1) {
    *(f32*)(arg0 + 0x2C) = (f32)(s32)arg1 / 127.0f;
}

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

void func_81113FA8(SequenceChannel* channel) {
    s32 i;
    u8* data;
    s8 signed_param;
    u8 command;
    u8 highBits;
    u8 low_bits;
    u8* test;
    SequencePlayer* seqPlayer;

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
        SeqScriptState* scriptState = &channel->scriptState;
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
                            channel->fontId = command;
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
                        channel->adsr.envelope = &seqPlayer->seqData[offset];
                        break;
                    case 0xD9:
                        command = (u8)parameters[0];
                        channel->adsr.decayIndex = command;
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
                            channel->fontId = command;
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
                        channel->adsr.sustain = command;
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
                        channel->adsr.sustain = 0;
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
                        channel->layers[low_bits]->scriptState.pc = &seqPlayer->seqData[offset];
                    }
                    break;
                case 0x90:
                    AudioSeq_SeqLayerFree((s8**)channel, low_bits);
                    break;
                case 0x98:
                    if (scriptState->value != -1 && AudioSeq_SeqChannelSetLayer(channel, low_bits) != -1) {
                        data = (*channel->dynTable)[scriptState->value];
                        offset = (data[0] << 8) + data[1];
                        channel->layers[low_bits]->scriptState.pc = &seqPlayer->seqData[offset];
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
                    if (func_8110E500(channel->fontId, scriptState->value, &channel->soundScriptIO[low_bits]) == -1) {} // karodo
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
                    AudioSeq_SequenceChannelEnable(seqPlayer, low_bits, &seqPlayer->seqData[offset]);
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
