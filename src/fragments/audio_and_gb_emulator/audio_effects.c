/* Stadium Zero fragment000_80C00. */

#include "global.h"
#include "m2c_macros.h"
#include "audio_and_gb_emulator.h"

typedef struct SeqPlayer81111C20 {
    /* 0x00 */ u32 unk00_31 : 2;
    /* 0x00 */ u32 muted : 1; // @unverified: bit 2 of the player flags, OoT's SequencePlayer.muted (softens the channel volume)
    /* 0x00 */ u32 unk00_28 : 29;
    /* 0x04 */ char unk04[0x28 - 0x4];
    /* 0x28 */ f32 muteVolumeScale; // @unverified: same offset/use as OoT's SequencePlayer.muteVolumeScale
    /* 0x2C */ char unk2C[0x30 - 0x2C];
    /* 0x30 */ f32 appliedFadeVolume; // @unverified: same offset/use as OoT's SequencePlayer.appliedFadeVolume
} SeqPlayer81111C20;
typedef struct Layer81111C20 {
    /* 0x00 */ u32 enabled : 1; // @unverified: same bit/use as OoT's SequenceLayer.enabled
    /* 0x00 */ u32 unk00_30 : 4;
    /* 0x00 */ u32 notePropertiesNeedInit : 1; // @unverified: same use as OoT's SequenceLayer.notePropertiesNeedInit (cleared once the note properties are set)
    /* 0x00 */ u32 unk00_25 : 26;
    /* 0x04 */ u8 unk04[2];
    /* 0x06 */ u8 pan; // @unverified: same offset/use as OoT's SequenceLayer.pan
    /* 0x07 */ s8 notePan; // @unverified: same offset/use as OoT's SequenceLayer.notePan
    /* 0x08 */ char unk08[0x24 - 0x8];
    /* 0x24 */ f32 freqScale; // @unverified: same offset/use as OoT's SequenceLayer.freqScale
    /* 0x28 */ char unk28[0x2C - 0x28];
    /* 0x2C */ f32 velocitySquare2; // @unverified: same offset as Layer81113A44.velocitySquare2, the randomized velocity
    /* 0x30 */ char unk30[0x34 - 0x30];
    /* 0x34 */ f32 noteVelocity; // @unverified: same offset/use as OoT's SequenceLayer.noteVelocity
    /* 0x38 */ f32 noteFreqScale; // @unverified: same offset/use as OoT's SequenceLayer.noteFreqScale
    /* 0x3C */ char unk3C[0x48 - 0x3C];
    /* 0x48 */ s32 note; // @unverified: same offset/use as OoT's SequenceLayer.note (only layers with a note are updated)
} Layer81111C20;
typedef struct Channel81111C20 {
    /* 0x00 */ u32 unk00_31 : 8;
    /* 0x00 */ u32 changeFreqScale : 1; // @unverified: same bit/use as OoT's SequenceChannel.changes.s.freqScale
    /* 0x00 */ u32 changeVolume : 1; // @unverified: same bit/use as OoT's SequenceChannel.changes.s.volume
    /* 0x00 */ u32 changePan : 1; // @unverified: same bit/use as OoT's SequenceChannel.changes.s.pan
    /* 0x00 */ u32 unk00_20 : 21;
    /* 0x04 */ char unk04[0xA - 0x4];
    /* 0x0A */ u8 newPan; // @unverified: same offset/use as OoT's SequenceChannel.newPan
    /* 0x0B */ u8 panChannelWeight; // @unverified: same offset/use as OoT's SequenceChannel.panChannelWeight
    /* 0x0C */ char unk0C[0x28 - 0xC];
    /* 0x28 */ f32 volumeScale; // @unverified: same offset/use as OoT's SequenceChannel.volumeScale
    /* 0x2C */ f32 volume; // @unverified: same offset/use as OoT's SequenceChannel.volume
    /* 0x30 */ s32 pan; // @unverified: same offset/use as OoT's SequenceChannel.pan (newPan * panChannelWeight)
    /* 0x34 */ f32 appliedVolume; // @unverified: same offset/use as OoT's SequenceChannel.appliedVolume
    /* 0x38 */ f32 freqScale; // @unverified: same offset/use as OoT's SequenceChannel.freqScale
    /* 0x3C */ char unk3C[0x4C - 0x3C];
    /* 0x4C */ SeqPlayer81111C20* seqPlayer; // @unverified: same offset/use as OoT's SequenceChannel.seqPlayer
    /* 0x50 */ Layer81111C20* layers[4]; // @unverified: same offset/use as OoT's SequenceChannel.layers
} Channel81111C20;
void func_81111C20(Channel81111C20* arg0, u32 force) {
    f32 vol;
    s32 i;
    Layer81111C20* v;

    if (arg0->changeVolume || force) {
        vol = arg0->volume * arg0->volumeScale * arg0->seqPlayer->appliedFadeVolume;
        if (arg0->seqPlayer->muted && (M2C_FIELD(arg0, u8*, 3) & 0x20)) {
            vol = arg0->seqPlayer->muteVolumeScale * vol;
        }
        arg0->appliedVolume = vol * vol;
    }
    if (arg0->changePan) {
        arg0->pan = arg0->newPan * arg0->panChannelWeight;
    }
    for (i = 0; i < 4; i++) {
        v = arg0->layers[i];
        if (v != NULL && v->enabled && v->note != 0) {
            if (v->notePropertiesNeedInit) {
                v->noteFreqScale = v->freqScale * arg0->freqScale;
                v->noteVelocity = v->velocitySquare2 * arg0->appliedVolume;
                v->notePan = (arg0->pan + v->pan * (0x80 - arg0->panChannelWeight)) >> 7;
                v->notePropertiesNeedInit = 0;
            } else {
                if (arg0->changeFreqScale) {
                    v->noteFreqScale = v->freqScale * arg0->freqScale;
                }
                if (arg0->changeVolume || force) {
                    v->noteVelocity = v->velocitySquare2 * arg0->appliedVolume;
                }
                if (arg0->changePan) {
                    v->notePan = (arg0->pan + v->pan * (0x80 - arg0->panChannelWeight)) >> 7;
                }
            }
        }
    }
    M2C_FIELD(arg0, u8*, 1) = 0;
}

typedef struct Channel81111DC8 {
    /* 0x00 */ u32 enabled : 1; // @unverified: same bit/use as OoT's SequenceChannel.enabled
} Channel81111DC8;
typedef struct SeqPlayer81111DC8 {
    /* 0x00 */ u32 unk00_0 : 5;
    /* 0x00 */ u32 recalculateVolume : 1; // @unverified: same bit/use as OoT's SequencePlayer.recalculateVolume
    /* 0x00 */ u32 unk00_6 : 2;
    /* 0x01 */ u32 state : 8; // @unverified: same offset/use as OoT's SequencePlayer.state (2 = fade out, then disable)
    /* 0x02 */ char unk02[0x12 - 0x2];
    /* 0x12 */ u16 fadeTimer; // @unverified: same offset/use as OoT's SequencePlayer.fadeTimer
    /* 0x14 */ char unk14[0x1C - 0x14];
    /* 0x1C */ f32 fadeVolume; // @unverified: same offset/use as OoT's SequencePlayer.fadeVolume
    /* 0x20 */ f32 fadeVelocity; // @unverified: same offset/use as OoT's SequencePlayer.fadeVelocity
    /* 0x24 */ char unk24[0x2C - 0x24];
    /* 0x2C */ f32 fadeVolumeScale; // @unverified: same offset/use as OoT's SequencePlayer.fadeVolumeScale
    /* 0x30 */ f32 appliedFadeVolume; // @unverified: same offset/use as OoT's SequencePlayer.appliedFadeVolume
    /* 0x34 */ Channel81111DC8* channels[16]; // @unverified: same offset/use as OoT's SequencePlayer.channels
} SeqPlayer81111DC8;
void func_81111C20();
void AudioSeq_SequencePlayerDisable(SeqPlayer81111DC8 *);
void func_81111DC8(SeqPlayer81111DC8 *arg0) {
    s32 i;

    if (arg0->fadeTimer != 0) {
        arg0->fadeVolume += arg0->fadeVelocity;
        arg0->recalculateVolume = 1;
        if (arg0->fadeVolume > 1.0f) {
            arg0->fadeVolume = 1.0f;
        }
        if (arg0->fadeVolume < 0.0f) {
            arg0->fadeVolume = 0.0f;
        }
        if ((--arg0->fadeTimer == 0) && (arg0->state == 2)) {
            AudioSeq_SequencePlayerDisable(arg0);
            return;
        }
    }
    if (arg0->recalculateVolume) {
        arg0->appliedFadeVolume = arg0->fadeVolume * arg0->fadeVolumeScale;
    }
    for (i = 0; i < 16; i++) {
        if (arg0->channels[i]->enabled == 1) {
            func_81111C20(arg0->channels[i], arg0->recalculateVolume);
        }
    }
    arg0->recalculateVolume = 0;
}

extern f32 D_FLT_81136178[];

f32 func_81111F0C(arg0)
    s8* arg0;
{
    u32 idx;
    f32 ret;

    M2C_FIELD(arg0, f32*, 4) += M2C_FIELD(arg0, f32*, 8);
    idx = M2C_FIELD(arg0, f32*, 4);
    if (idx >= 0x80) {
        idx = 0x7F;
    }
    ret = (M2C_FIELD(arg0, f32*, 0xC) * (D_FLT_81136178[idx] - 1.0f)) + 1.0f;
    return ret;
}

typedef struct {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ u32 time; // @unverified: same offset/use as OoT's VibratoState.time
    /* 0x08 */ s16* curve; // @unverified: same offset/use as OoT's VibratoState.curve
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ f32 rate; // @unverified: same offset/use as OoT's VibratoState.rate
} VibratoState81111FE0;

/*
 * func_81111FE0
 *
 * Advances the vibrato time by its rate (truncated to an integer) and
 * returns the curve entry selected by time bits 10-15 (a 64-entry table of
 * s16), shifted right by 8 (sign-extended). Same as OoT's
 * AudioEffects_GetVibratoPitchChange.
 */
s16 func_81111FE0(VibratoState81111FE0* arg0) {
    s32 index;

    arg0->time += (s32)arg0->rate;
    index = (arg0->time >> 10) & 0x3F;
    return (s16)(arg0->curve[index] >> 8);
}

typedef struct Channel81112278 {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ u16 vibratoRateStart;
    /* 0x12 */ u16 vibratoExtentStart;
    /* 0x14 */ u16 vibratoRateTarget;
    /* 0x16 */ u16 vibratoExtentTarget;
    /* 0x18 */ u16 vibratoRateChangeDelay;
    /* 0x1A */ u16 vibratoExtentChangeDelay;
    /* 0x1C */ u16 vibratoDelay;
} Channel81112278;

typedef struct Portamento81112278 {
    /* 0x00 */ s32 words[4];
} Portamento81112278; // size = 0x10

typedef struct Layer81112278 {
    /* 0x00 */ char pad00[0x8];
    /* 0x08 */ Portamento81112278 portamento;
    /* 0x18 */ char pad18[0x54 - 0x18];
    /* 0x54 */ Channel81112278* seqChannel;
} Layer81112278;

typedef struct PlaybackState81112278 {
    /* 0x00 */ char pad00[0x14];
    /* 0x14 */ Layer81112278* parentLayer;
    /* 0x18 */ char pad18[0x50 - 0x18];
    /* 0x50 */ Portamento81112278 portamento;
} PlaybackState81112278;

typedef struct Vibrato81112278 {
    /* 0x00 */ Channel81112278* seqChannel;
    /* 0x04 */ u32 time;
    /* 0x08 */ s16* curve;
    /* 0x0C */ f32 extent;
    /* 0x10 */ f32 rate;
    /* 0x14 */ u8 active;
    /* 0x16 */ u16 rateChangeTimer;
    /* 0x18 */ u16 extentChangeTimer;
    /* 0x1A */ u16 delay;
} Vibrato81112278;

typedef struct Note81112278 {
    /* 0x00 */ char pad00[0x30];
    /* 0x30 */ u8 priority;
    /* 0x31 */ char pad31[0x38 - 0x31];
    /* 0x38 */ f32 portamentoFreqScale;
    /* 0x3C */ f32 vibratoFreqScale;
    /* 0x40 */ char pad40[0x4];
    /* 0x44 */ Layer81112278* parentLayer;
    /* 0x48 */ char pad48[0x90 - 0x48];
    /* 0x90 */ Vibrato81112278 vibratoState;
} Note81112278;

/**
 * Returns the frequency scale for a note's vibrato and steps it: counts down
 * the delay, moves the extent and rate toward their channel targets over their
 * change timers, and scales the curve value at the current phase by the
 * extent. Same structure as get_vibrato_freq_scale in the Super Mario 64 audio
 * library.
 */
f32 func_81112024(vib)
    Vibrato81112278* vib;
{
    s32 pitch_change;
    f32 extent;
    f32 result;
    Channel81112278* seqChannel = vib->seqChannel;

    if (vib->delay != 0) {
        vib->delay--;
        return 1;
    }

    if (vib->extentChangeTimer) {
        if (vib->extentChangeTimer == 1) {
            vib->extent = (s32)seqChannel->vibratoExtentTarget;
        } else {
            vib->extent += ((s32)seqChannel->vibratoExtentTarget - vib->extent) / (s32)vib->extentChangeTimer;
        }

        vib->extentChangeTimer--;
    } else if (seqChannel->vibratoExtentTarget != (s32)vib->extent) {
        if ((vib->extentChangeTimer = seqChannel->vibratoExtentChangeDelay) == 0) {
            vib->extent = (s32)seqChannel->vibratoExtentTarget;
        }
    }

    if (vib->rateChangeTimer) {
        if (vib->rateChangeTimer == 1) {
            vib->rate = (s32)seqChannel->vibratoRateTarget;
        } else {
            vib->rate += ((s32)seqChannel->vibratoRateTarget - vib->rate) / (s32)vib->rateChangeTimer;
        }

        vib->rateChangeTimer--;
    } else if (seqChannel->vibratoRateTarget != (s32)vib->rate) {
        if ((vib->rateChangeTimer = seqChannel->vibratoRateChangeDelay) == 0) {
            vib->rate = (s32)seqChannel->vibratoRateTarget;
        }
    }

    if (vib->extent == 0) {
        return 1.0f;
    }

    pitch_change = func_81111FE0((VibratoState81111FE0*)vib);
    extent = (f32)vib->extent / 4096.0f;

    result = 1.0f + extent * (D_FLT_81136178[pitch_change] - 1.0f);
    return result;
}

f32 func_81111F0C(); // The caller passes a second argument the callee ignores.
f32 func_81112024(); // The caller passes a second argument the callee ignores.

void func_8111220C(s8 *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x80) != 0) {
        M2C_FIELD(arg0, f32 *, 0x38) = func_81111F0C(arg0 + 0x80, arg0);
    }
    if ((M2C_FIELD(arg0, u8 *, 0xA4) != 0) && (M2C_FIELD(arg0, s32 *, 0x44) != -1)) {
        M2C_FIELD(arg0, f32 *, 0x3C) = func_81112024(arg0 + 0x90, arg0);
    }
}

extern s16* D_81135F68;

/**
 * Starts a note's vibrato from its channel's vibrato settings (extent and rate
 * start at their start values when they have a change delay, otherwise at
 * their targets) and copies the layer's portamento into the note. Same
 * structure as note_vibrato_init in the Super Mario 64 audio library.
 */
void func_81112278(Note81112278* note) {
    Vibrato81112278* vib;
    Channel81112278* seqChannel;
    PlaybackState81112278* seq_player_state = (PlaybackState81112278*)&note->priority;

    note->vibratoFreqScale = 1.0f;
    note->portamentoFreqScale = 1.0f;
    vib = &note->vibratoState;

    vib->active = 1;
    vib->time = 0;

    vib->curve = D_81135F68;
    vib->seqChannel = note->parentLayer->seqChannel;
    seqChannel = vib->seqChannel;

    if ((vib->extentChangeTimer = seqChannel->vibratoExtentChangeDelay) == 0) {
        vib->extent = (s32)seqChannel->vibratoExtentTarget;
    } else {
        vib->extent = (s32)seqChannel->vibratoExtentStart;
    }

    if ((vib->rateChangeTimer = seqChannel->vibratoRateChangeDelay) == 0) {
        vib->rate = (s32)seqChannel->vibratoRateTarget;
    } else {
        vib->rate = (s32)seqChannel->vibratoRateStart;
    }
    vib->delay = seqChannel->vibratoDelay;

    seq_player_state->portamento = seq_player_state->parentLayer->portamento;
}

void func_8111235C(s8 *arg0, s32 arg1, M2C_UNK arg2) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 1) = 0;
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    M2C_FIELD(arg0, f32 *, 8) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x14) = 0.0f;
}

typedef struct EnvelopePoint81112380 {
    /* 0x0 */ s16 delay;
    /* 0x2 */ s16 arg;
} EnvelopePoint81112380;

typedef struct Adsr81112380 {
    /* 0x00 */ u8 action;
    /* 0x01 */ u8 state;
    /* 0x02 */ s16 envIndex;
    /* 0x04 */ s16 delay;
    /* 0x08 */ f32 sustain;
    /* 0x0C */ f32 velocity;
    /* 0x10 */ f32 fadeOutVel;
    /* 0x14 */ f32 current;
    /* 0x18 */ f32 target;
    /* 0x1C */ char pad1C[4];
    /* 0x20 */ EnvelopePoint81112380* envelope;
} Adsr81112380;

extern f32 D_811858DC;

/**
 * Steps an ADSR envelope by one update and returns its level clamped to
 * [0, 1]. Envelope points with a delay of 0, -1, -2 and -3 disable, hang,
 * jump and restart; other points fade toward their target over their delay.
 * Same structure as AudioEffects_UpdateAdsr in the Ocarina of Time audio
 * library.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
f32 AudioEffects_UpdateAdsr(Adsr81112380* adsr) {
    u8 action = adsr->action;
    u8 state = adsr->state;

    switch (state) {
        case 0:
            return 0.0f;

        case 1:
            if (action & 0x40) {
                adsr->state = 5;
                break;
            }
        case 2:
            adsr->envIndex = 0;
            adsr->state = 3;
        retry:
        case 3:
            adsr->delay = adsr->envelope[adsr->envIndex].delay;
            switch (adsr->delay) {
                case 0:
                    adsr->state = 0;
                    break;
                case -1:
                    adsr->state = 5;
                    break;
                case -2:
                    adsr->envIndex = adsr->envelope[adsr->envIndex].arg;
                    goto retry;
                case -3:
                    adsr->state = 1;
                    break;
                default:
                    adsr->delay *= D_811858DC;
                    if (adsr->delay == 0) {
                        adsr->delay = 1;
                    }
                    adsr->target = adsr->envelope[adsr->envIndex].arg / 32767.0f;
                    adsr->target = adsr->target * adsr->target;
                    adsr->velocity = (adsr->target - adsr->current) / adsr->delay;
                    adsr->state = 4;
                    adsr->envIndex++;
                    break;
            }
            if (adsr->state != 4) {
                break;
            }
        case 4:
            adsr->current += adsr->velocity;
            if (--adsr->delay <= 0) {
                adsr->state = 3;
            }
        case 5:
            break;

        case 6:
        case 7:
            adsr->current -= adsr->fadeOutVel;
            if (adsr->sustain != 0.0f && state == 6) {
                if (adsr->current < adsr->sustain) {
                    adsr->current = adsr->sustain;
                    adsr->delay = 128;
                    adsr->state = 8;
                }
                break;
            }

            if (adsr->current < 0.00001f) {
                adsr->current = 0.0f;
                adsr->state = 0;
            }
            break;

        case 8:
            adsr->delay--;
            if (adsr->delay == 0) {
                adsr->state = 7;
            }
            break;
    }

    if (action & 0x20) {
        adsr->state = 6;
        adsr->action = action & ~0x20;
    }

    if (action & 0x10) {
        adsr->state = 7;
        adsr->action = action & ~0x10;
    }

    if (adsr->current < 0.0f) {
        return 0.0f;
    }
    if (adsr->current > 1.0f) {
        return 1.0f;
    }
    return adsr->current;
}
