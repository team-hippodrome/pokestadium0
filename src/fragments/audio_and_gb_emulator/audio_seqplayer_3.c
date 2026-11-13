/* Audio driver, matching the end of OoT src/audio/internal/seqplayer.c in function order, then
 * (from func_811155A0) Zero's own game-side wrappers that queue audio thread commands. The driver
 * is Nintendo's "Nas" library (original names Nas_*); this revision sits between SM64 Shindou and
 * OoT. See docs/annotation/audio-driver.md for the per-function mapping. */
/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "audio_and_gb_emulator.h"

// Declared here instead of in a header: the callers of these disagree on their types.
M2C_UNK AudioEffects_SequencePlayerProcessSound(s8 *);
extern SequencePlayer D_81184668[];
void AudioPlayback_NotePoolClear(s8*);
void AudioThread_QueueCmdS8(s32 cmd, s8 arg1);
void AudioThread_ScheduleProcessCmds(void);

s32 AudioLoad_IsFontLoadComplete(s32);
s32 AudioLoad_IsSeqLoadComplete(s32);
void AudioLoad_SetFontLoadStatus(s32, s32);
void AudioLoad_SetSeqLoadStatus(s32, s32);
u16 AudioSeq_GetScriptControlFlowArgument(u8** stream, u8 kind);
s32 AudioSeq_HandleScriptFlowControl(void*, void*, s32, s32);
void AudioSeq_SequencePlayerSetupChannels(SequencePlayer* seqPlayer, u16 mask);
void AudioSeq_SequencePlayerDisable(u8* arg0);
void func_81112B84(SequenceChannel*);

extern s16 D_811858EC;
void AudioPlayback_NotePoolFill(void*, s32);
void AudioSeq_SequenceChannelProcessScript(SequenceChannel*);

/**
 * Runs one tick of a sequence player's script, then its channels.
 * Corresponds to OoT AudioSeq_SequencePlayerProcessSequence (original name Nas_GroupSeq). OoT adds
 * script loads and slow sequence loads.
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioSeq_SequencePlayerProcessSequence(SequencePlayer* seq_player) {
    u8 cmd;
    u8 lo_bits;
    u16 temp;
    s32 value;
    s32 i;
    u8* data;
    SeqScriptState* state;
    UNUSED s32 pad[4]; // FAKE: stack pad of unknown origin; only reserves frame space

    if (!seq_player->enabled) {
        return;
    }
    if (!AudioLoad_IsSeqLoadComplete(seq_player->seqId) || !AudioLoad_IsFontLoadComplete(seq_player->defaultFont)) {
        AudioSeq_SequencePlayerDisable((u8*)seq_player);
        return;
    }
    AudioLoad_SetSeqLoadStatus(seq_player->seqId, 2);
    AudioLoad_SetFontLoadStatus(seq_player->defaultFont, 2);

    if (seq_player->muted && (seq_player->muteBehavior & 0x80)) {
        return;
    }

    seq_player->scriptCounter++;
    seq_player->tempoAcc += seq_player->tempo;
    seq_player->tempoAcc += seq_player->tempoChange;
    if (seq_player->tempoAcc < D_811858EC) {
        return;
    }
    seq_player->tempoAcc -= (u16)D_811858EC;

    if (seq_player->stopScript == 1) {
        return;
    }

    state = &seq_player->scriptState;
    if (seq_player->delay > 1) {
        seq_player->delay--;
    } else {
        seq_player->recalculateVolume = 1;
        while (1) {
            cmd = AudioSeq_ScriptReadU8(&state->pc);
            if (cmd >= 0xF2) {
                value = AudioSeq_HandleScriptFlowControl(seq_player, state, cmd, AudioSeq_GetScriptControlFlowArgument(&state->pc, cmd));
                if (value != 0) {
                    if (value == -1) {
                        AudioSeq_SequencePlayerDisable((u8*)seq_player);
                    } else {
                        seq_player->delay = value;
                    }
                    break;
                }
            } else if (cmd >= 0xC0) {
                switch (cmd) {
                    case 0xF1:
                        AudioPlayback_NotePoolClear((s8*)&seq_player->notePool);
                        AudioPlayback_NotePoolFill(&seq_player->notePool, AudioSeq_ScriptReadU8(&state->pc));
                        break;
                    case 0xF0:
                        AudioPlayback_NotePoolClear((s8*)&seq_player->notePool);
                        break;
                    case 0xDF:
                        seq_player->transposition = 0;
                    case 0xDE:
                        seq_player->transposition += (s8)AudioSeq_ScriptReadU8(&state->pc);
                        break;
                    case 0xDD:
                        seq_player->tempo = AudioSeq_ScriptReadU8(&state->pc) * 48;
                        if (seq_player->tempo > D_811858EC) {
                            seq_player->tempo = (u16)D_811858EC;
                        }
                        if ((s16)seq_player->tempo <= 0) {
                            seq_player->tempo = 1;
                        }
                        break;
                    case 0xDC:
                        seq_player->tempoChange = (s8)AudioSeq_ScriptReadU8(&state->pc) * 48;
                        break;
                    case 0xDA:
                        cmd = AudioSeq_ScriptReadU8(&state->pc);
                        temp = AudioSeq_ScriptReadS16(&state->pc);
                        switch (cmd) {
                            case 0:
                            case 1:
                                if (seq_player->state != 2) {
                                    seq_player->storedFadeTimer = temp;
                                    seq_player->state = cmd;
                                }
                                break;
                            case 2:
                                seq_player->fadeTimer = temp;
                                seq_player->state = cmd;
                                seq_player->fadeVelocity = (0.0f - seq_player->fadeVolume) / (s32)seq_player->fadeTimer;
                                break;
                        }
                        break;
                    case 0xDB:
                        value = AudioSeq_ScriptReadU8(&state->pc);
                        switch (seq_player->state) {
                            case 1:
                                seq_player->state = 0;
                                seq_player->fadeVolume = 0.0f;
                            case 0:
                                seq_player->fadeTimer = seq_player->storedFadeTimer;
                                if (seq_player->storedFadeTimer != 0) {
                                    seq_player->fadeVelocity = ((value / 127.0f) - seq_player->fadeVolume) / (s32)seq_player->fadeTimer;
                                } else {
                                    seq_player->fadeVolume = value / 127.0f;
                                }
                                break;
                            case 2:
                                break;
                        }
                        break;
                    case 0xD9:
                        seq_player->fadeVolumeScale = (s8)AudioSeq_ScriptReadU8(&state->pc) / 127.0f;
                        break;
                    case 0xD7:
                        temp = AudioSeq_ScriptReadS16(&state->pc);
                        AudioSeq_SequencePlayerSetupChannels(seq_player, temp);
                        break;
                    case 0xD6:
                        AudioSeq_ScriptReadS16(&state->pc);
                        break;
                    case 0xD5:
                        seq_player->muteVolumeScale = (s8)AudioSeq_ScriptReadU8(&state->pc) / 127.0f;
                        break;
                    case 0xD4:
                        seq_player->muted = 1;
                        break;
                    case 0xD3:
                        seq_player->muteBehavior = AudioSeq_ScriptReadU8(&state->pc);
                        break;
                    case 0xD1:
                    case 0xD2:
                        temp = AudioSeq_ScriptReadS16(&state->pc);
                        data = seq_player->seqData + temp;
                        if (cmd == 0xD2) {
                            seq_player->shortNoteVelocityTable = data;
                        } else {
                            seq_player->shortNoteGateTimeTable = data;
                        }
                        break;
                    case 0xD0:
                        seq_player->noteAllocPolicy = AudioSeq_ScriptReadU8(&state->pc);
                        break;
                    case 0xCC:
                        state->value = AudioSeq_ScriptReadU8(&state->pc);
                        break;
                    case 0xC9:
                        state->value &= AudioSeq_ScriptReadU8(&state->pc);
                        break;
                    case 0xC8:
                        state->value -= AudioSeq_ScriptReadU8(&state->pc);
                        break;
                    case 0xC7:
                        cmd = AudioSeq_ScriptReadU8(&state->pc);
                        temp = AudioSeq_ScriptReadS16(&state->pc);
                        data = seq_player->seqData + temp;
                        *data = (u8)state->value + cmd;
                        break;
                    case 0xC6:
                        seq_player->stopScript = 1;
                        return;
                    case 0xC5:
                        seq_player->scriptCounter = (u16)AudioSeq_ScriptReadS16(&state->pc);
                        break;
                }
            } else {
                lo_bits = cmd & 0xF;
                switch (cmd & 0xF0) {
                    case 0x00:
                        state->value = seq_player->channels[lo_bits]->finished;
                        break;
                    case 0x10:
                        break;
                    case 0x20:
                        break;
                    case 0x50:
                        state->value -= seq_player->soundScriptIO[lo_bits];
                        break;
                    case 0x70:
                        seq_player->soundScriptIO[lo_bits] = state->value;
                        break;
                    case 0x80:
                        state->value = seq_player->soundScriptIO[lo_bits];
                        if (lo_bits < 2) {
                            seq_player->soundScriptIO[lo_bits] = -1;
                        }
                        break;
                    case 0x40:
                        func_81112B84((SequenceChannel*)seq_player->channels[lo_bits]);
                        break;
                    case 0x90:
                        temp = AudioSeq_ScriptReadS16(&state->pc);
                        AudioSeq_SequenceChannelEnable(seq_player, lo_bits, seq_player->seqData + temp);
                        break;
                    case 0x60:
                    case 0xA0:
                        break;
                }
            }
        }
    }

    for (i = 0; i < 16; i++) {
        if (seq_player->channels[i]->enabled) {
            AudioSeq_SequenceChannelProcessScript(seq_player->channels[i]);
        }
    }
}

/**
 * Runs every enabled sequence player for one tick, then updates the notes.
 * Corresponds to OoT AudioSeq_ProcessSequences (original name Nas_MySeqMain).
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioSeq_ProcessSequences(s32 arg0) {
    u32 i;

    for (i = 0; i < D_811858CC; i++) {
        if (D_81184668[i].enabled == 1) {
            AudioSeq_SequencePlayerProcessSequence((s8*)&D_81184668[i]);
            AudioEffects_SequencePlayerProcessSound((s8*)&D_81184668[i]);
        }
    }
    AudioPlayback_ProcessNotes();
}

/**
 * Runs a sequence player's skipTicks ticks at once.
 * Corresponds to OoT AudioSeq_SkipForwardSequence (original name Nas_SeqSkip).
 * @unverified Name follows the counterpart; not checked in play.
 */
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void AudioSeq_SkipForwardSequence(s8 *arg0)
{
  s8 *new_var; // FAKE: permuter temp
  s32 temp_t8;
  if ((*((s32 *) (((s8 *) arg0) + 0xD8))) > 0)
  {
    do
    {
      AudioSeq_SequencePlayerProcessSequence(arg0);
      AudioEffects_SequencePlayerProcessSound(arg0);
      new_var = (s8 *) arg0;
      temp_t8 = (unsigned long long) ((*((s32 *) (new_var + 0xD8))) - 1);
      *((s32 *) (((s8 *) arg0) + 0xD8)) = temp_t8;
    }
    while (temp_t8 > 0);
  }
}

extern u8 D_81136978[];
extern u8 D_81136988[];
void AudioSeq_InitSequenceChannel(void*);
/**
 * Stops sequence player `arg0` and restores its tempo, volumes and channels to their defaults.
 * Corresponds to OoT AudioSeq_ResetSequencePlayer (original name Nas_InitMySeq).
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioSeq_ResetSequencePlayer(s32 arg0) {
    SequencePlayer* chan = (SequencePlayer*)&D_81184668[arg0];
    s32 i;

    AudioSeq_SequencePlayerDisable((u8*)chan);
    chan->stopScript = 0;
    chan->delay = 0;
    chan->state = 1;
    chan->fadeTimer = 0;
    chan->storedFadeTimer = 0;
    chan->tempoAcc = 0;
    chan->tempo = 0x1680;
    chan->tempoChange = 0;
    chan->transposition = 0;
    chan->noteAllocPolicy = 0;
    chan->shortNoteVelocityTable = D_81136978;
    chan->shortNoteGateTimeTable = D_81136988;
    chan->scriptCounter = 0;
    chan->fadeVolume = 1.0f;
    chan->fadeVolumeScale = 1.0f;
    chan->fadeVelocity = 0.0f;
    chan->volume = 0.0f;
    chan->muteVolumeScale = 0.5f;
    for (i = 0; i < 16; i++) {
        AudioSeq_InitSequenceChannel(chan->channels[i]);
    }
}

extern u8 D_811842C0[];
extern SequenceChannel D_81184850;
void* func_811097E8(void*, s32);
/**
 * Allocates sequence player `arg0`'s 16 channels, falling back to the shared dummy channel.
 * Corresponds to OoT AudioSeq_InitSequencePlayerChannels (original name Nas_AssignSubTrack).
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioSeq_InitSequencePlayerChannels(s32 arg0) {
    SequencePlayer* rec = (SequencePlayer*)&D_81184668[arg0];
    s32 i;
    s32 j;
    SequenceChannel* item;

    for (i = 0; i < 16; i++) {
        rec->channels[i] = func_811097E8(D_811842C0, 0xD4);
        if (rec->channels[i] == NULL) {
            rec->channels[i] = &D_81184850;
        } else {
            item = rec->channels[i];
            item->enabled = 0;
            item->seqPlayer = rec;
            for (j = 0; j < 1; j++) {
                item->layers[j] = NULL;
            }
        }
    }
}

void AudioPlayback_InitNoteLists(void*);
/**
 * Sets up the layer free list, the sequence layers and the one sequence player.
 * Corresponds to OoT AudioSeq_InitSequencePlayers (original name Nas_InitPlayer). Zero has OoT's
 * AudioSeq_InitSequencePlayer (__InitGroup) inlined for its single player.
 * @unverified Name follows the counterpart; not checked in play.
 */
void AudioSeq_InitSequencePlayers(void) {
    s32 i;
    s32 j;
    SequencePlayer* rec;

    AudioSeq_InitLayerFreelist();
    for (i = 0; i < 1; i++) {
        ((SequenceLayer*)D_811847C8)[i].channel = 0;
        ((SequenceLayer*)D_811847C8)[i].enabled = 0;
    }
    for (i = 0; i < 1; i++) {
        rec = (SequencePlayer*)&D_81184668[i];
        for (j = 0; j < 16; j++) {
            rec->channels[j] = &D_81184850;
        }
        rec->soundScriptIO[0] = -1;
        rec->muteBehavior = 0x60;
        rec->enabled = 0;
        rec->muted = 0;
        rec->fontDmaInProgress = 0;
        rec->seqDmaInProgress = 0;
        AudioPlayback_InitNoteLists(&rec->notePool);
        AudioSeq_ResetSequencePlayer(i);
    }
}

/**
 * Sends the queued audio commands. First function of Zero's game-side audio layer, which follows
 * the driver and has no counterpart in OoT's driver files.
 */
void func_811155A0(void) {
    AudioThread_ScheduleProcessCmds();
}

/**
 * Queues a global mute (OoT AUDIOCMD_OP_GLOBAL_MUTE, 0xF1) and sets D_81138A70.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from the command it queues; not checked in play.
 */
void Audio_QueueGlobalMute(void) {
    AudioThread_QueueCmdS32(0xF1000000, 0);
    D_81138A70 = 1;
}

/**
 * Queues a global unmute (OoT AUDIOCMD_OP_GLOBAL_UNMUTE, 0xF2) and clears D_81138A70.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name from the command it queues; not checked in play.
 */
void Audio_QueueGlobalUnmute(void) {
    AudioThread_QueueCmdS32(0xF2000000, 0);
    D_81138A70 = 0;
}

void func_81215C14_jp(s32 arg0, s32 arg1, u8 arg2) {
    SequencePlayer* ch = &D_81287B08_jp[arg0];
    f32 target;

    ch->fadeTimer = 0;
    target = ((s32)arg2 / 100.0f) * ch->fadeVolume;
    ch->volume = ch->fadeVolume;
    if (arg1 == 0) {
        ch->fadeVolume = target;
        return;
    }
    ch->state = 0;
    ch->fadeTimer = arg1;
    ch->fadeVelocity = (target - ch->fadeVolume) / arg1;
}

void func_81215C9C_jp(s32 arg0, s32 arg1) {
    SequencePlayer* ch = &D_81287B08_jp[arg0];

    ch->fadeTimer = 0;
    if (arg1 == 0) {
        ch->fadeVolume = ch->volume;
        return;
    }
    ch->state = 0;
    ch->fadeTimer = arg1;
    ch->fadeVelocity = (ch->volume - ch->fadeVolume) / arg1;
}

/** Empty. */
void func_81115704(void) {
}

/**
 * Queues a mute (`arg2` nonzero) or unmute of channel `arg1` of sequence player `arg0`: OoT's
 * AUDIOCMD_CHANNEL_SET_MUTE, op 0x08 with an s8 argument.
 * @unverified Name from the command it queues; not checked in play.
 */
void Audio_QueueChannelMute(s32 arg0, s32 arg1, s32 arg2) {
    AudioThread_QueueCmdS8(((arg0 & 0xFF) << 16) | 0x08000000 | ((arg1 & 0xFF) << 8), arg2);
}

/**
 * Queues sequence 1 on sequence player 2 (OoT AUDIOCMD_OP_GLOBAL_INIT_SEQPLAYER, 0x82), sends it,
 * then queues 0xF8 (AUDIOCMD_OP_GLOBAL_STOP_AUDIOCMDS).
 */
void func_81215D50_jp(void) {
    AudioThread_QueueCmdS32(0x82020100, 0);
    AudioThread_ScheduleProcessCmds();
    AudioThread_QueueCmdS32(0xF8000000, 0);
}

/**
 * Writes `arg1`, `arg0` and `arg2` to IO ports 2, 1 and 0 of sequence player 2's channel 0
 * (OoT AUDIOCMD_OP_CHANNEL_SET_IO, 0x06).
 */
void func_81215D8C_jp(s32 arg0, s32 arg1, s32 arg2) {
    AudioThread_QueueCmdS8(0x06020002, arg1);
    AudioThread_QueueCmdS8(0x06020001, arg0);
    AudioThread_QueueCmdS8(0x06020000, arg2);
}

/** Writes -1 to IO port 4 of sequence player 2's channel 0 (OoT AUDIOCMD_OP_CHANNEL_SET_IO, 0x06). */
void func_81215DDC_jp(void) {
    AudioThread_QueueCmdS8(0x06020004, -1);
}

/**
 * No callers.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment from Stadium 1.
 */
void GbApu_SetNoiseLoopBounds(s32 arg0, s32 arg1) {
    D_81138AD0 = arg0;
    D_81138AD4 = arg1;
}
