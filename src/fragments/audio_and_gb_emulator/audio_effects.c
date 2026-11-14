/* Stadium Zero fragment000_80C00. */

#include "global.h"
#include "m2c_macros.h"
#include "audio_and_gb_emulator.h"

void func_81111C20(SequenceChannel* arg0, u32 force) {
    f32 vol;
    s32 i;
    SequenceLayer* v;

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

void func_81111C20();
void AudioSeq_SequencePlayerDisable(SequencePlayer *);
void func_81111DC8(SequencePlayer *arg0) {
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


/*
 * func_81111FE0
 *
 * Advances the vibrato time by its rate (truncated to an integer) and
 * returns the curve entry selected by time bits 10-15 (a 64-entry table of
 * s16), shifted right by 8 (sign-extended). Same as OoT's
 * AudioEffects_GetVibratoPitchChange.
 */
s16 func_81111FE0(VibratoState* arg0) {
    s32 index;

    arg0->time += (s32)arg0->rate;
    index = (arg0->time >> 10) & 0x3F;
    return (s16)(arg0->curve[index] >> 8);
}

/**
 * Returns the frequency scale for a note's vibrato and steps it: counts down
 * the delay, moves the extent and rate toward their channel targets over their
 * change timers, and scales the curve value at the current phase by the
 * extent. Same structure as get_vibrato_freq_scale in the Super Mario 64 audio
 * library.
 */
f32 func_81112024(vib)
    VibratoState* vib;
{
    s32 pitch_change;
    f32 extent;
    f32 result;
    SequenceChannel* seqChannel = vib->channel;

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

    pitch_change = func_81111FE0(vib);
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
void func_81112278(Note* note) {
    VibratoState* vib;
    SequenceChannel* seqChannel;
    NotePlaybackState* seq_player_state = &note->playbackState;

    note->playbackState.vibratoFreqScale = 1.0f;
    note->playbackState.portamentoFreqScale = 1.0f;
    vib = &note->playbackState.vibratoState;

    vib->active = 1;
    vib->time = 0;

    vib->curve = D_81135F68;
    vib->channel = note->playbackState.parentLayer->channel;
    seqChannel = vib->channel;

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
f32 AudioEffects_UpdateAdsr(AdsrState* adsr) {
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
