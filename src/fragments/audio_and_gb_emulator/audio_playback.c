/* Stadium Zero fragment000_80C00. */

#include "global.h"
#include "audio_and_gb_emulator.h"
#include "m2c_macros.h"

/* The attributes AudioPlayback_InitSampleState is given (built on the stack from a note's attributes). */
typedef struct NoteSubAttributes {
    /* 0x00 */ u8 reverbVol; // @unverified: same offset/use as OoT's NoteSubAttributes.reverbVol
    /* 0x01 */ u8 gain; // @unverified: same offset/use as OoT's NoteSampleStateAttributes.gain (from channel->gain)
    /* 0x02 */ u8 pan; // @unverified: same offset/use as OoT's NoteSubAttributes.pan
    /* 0x03 */ Stereo reverbBits; // @unverified: same offset/use as OoT's NoteSubAttributes.reverbBits
    /* 0x04 */ f32 freqScale; // @unverified: same offset/use as OoT's NoteSubAttributes.frequency
    /* 0x08 */ f32 velocity; // @unverified: same offset/use as OoT's NoteSubAttributes.velocity
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 filter; // @unverified: takes channel->filter / NoteAttributes.filter, like OoT's NoteSampleStateAttributes.filter
} NoteSubAttributes;
void AudioPlayback_SeqLayerDecayRelease(struct SequenceLayer*, s32);

void AudioPlayback_NoteSetResamplingRate(s8* arg0, f32 arg1);

extern s8 D_811858EE;
extern u16 D_811369D8[];
extern f32 D_81136AD8[];
extern f32 D_81136CD8[];
extern f32 D_81136ED8[];

/**
 * Sets a note's left and right volume, pan and reverb from its attributes. Zelda 64 audio driver (playback.c), same position and shape.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_InitSampleState(s8* note, NoteSubAttributes* reverb_info) {
    NoteSampleState* sub;
    f32 vol_right;
    f32 vol_left;
    s32 small_pan_index;
    UNUSED u32 pad; // FAKE: stack padding
    UNUSED u32 pad1; // FAKE: stack padding
    u8 strongRight;
    u8 strongLeft;
    f32 velocity;
    u8 pan;
    u8 reverbVol;
    Stereo reverbBits;

    AudioPlayback_NoteSetResamplingRate(note, reverb_info->freqScale);
    velocity = reverb_info->velocity;
    pan = reverb_info->pan;
    reverbVol = reverb_info->reverbVol;
    reverbBits = reverb_info->reverbBits;
    sub = (NoteSampleState*)(note + 0xB4);
    pan &= 0x7F;

    if (sub->stereoHeadsetEffects && D_811858EE == 1) {
        small_pan_index = pan >> 1;
        if (small_pan_index > 0x3F) {
            small_pan_index = 0x3F;
        }
        sub->headsetPanLeft = D_811369D8[small_pan_index];
        sub->headsetPanRight = D_811369D8[0x3F - small_pan_index];
        sub->stereoStrongRight = 0;
        sub->stereoStrongLeft = 0;
        sub->usesHeadsetPanEffects = 1;
        vol_left = D_81136AD8[pan];
        vol_right = D_81136AD8[0x7F - pan];
    } else if (sub->stereoHeadsetEffects && D_811858EE == 0) {
        strongLeft = strongRight = 0;
        sub->headsetPanRight = 0;
        sub->headsetPanLeft = 0;
        sub->usesHeadsetPanEffects = 0;
        vol_left = D_81136CD8[pan];
        vol_right = D_81136CD8[0x7F - pan];
        if (pan < 0x20) {
            strongLeft = 1;
        } else if (pan > 0x60) {
            strongRight = 1;
        }
        sub->stereoStrongRight = strongRight;
        sub->stereoStrongLeft = strongLeft;
        switch (reverbBits.s.stereoHeadsetEffects) {
            case 0:
                sub->stereoStrongRight = reverbBits.s.strongRight;
                sub->stereoStrongLeft = reverbBits.s.strongLeft;
                break;
            case 1:
                break;
            case 2:
                sub->stereoStrongRight = reverbBits.s.strongRight | strongRight;
                sub->stereoStrongLeft = reverbBits.s.strongLeft | strongLeft;
                break;
            case 3:
                sub->stereoStrongRight = reverbBits.s.strongRight ^ strongRight;
                sub->stereoStrongLeft = reverbBits.s.strongLeft ^ strongLeft;
                break;
        }
    } else if (D_811858EE == 3) {
        vol_left = 0.707f;
        vol_right = 0.707f;
    } else {
        vol_left = D_81136ED8[pan];
        vol_right = D_81136ED8[0x7F - pan];
    }

    if (velocity < 0.0f) {
        velocity = 0.0f;
    }
    if (velocity > 1.0f) {
        velocity = 1.0f;
    }

    sub->targetVolLeft = (s32)(velocity * vol_left * 4095.999f);
    sub->targetVolRight = (s32)(velocity * vol_right * 4095.999f);
    sub->gain = reverb_info->gain;
    sub->filter = reverb_info->filter;

    if (sub->reverbVol != reverbVol) {
        sub->reverbVol = reverbVol;
        sub->envMixerNeedsInit = 1;
    } else if (sub->needsInit) {
        sub->envMixerNeedsInit = 1;
    } else {
        sub->envMixerNeedsInit = 0;
    }
}

typedef struct StereoFlags811105DC {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 pad : 7;
    /* 0x1 */ u8 wide : 1;
} StereoFlags811105DC;

/**
 * Sets a note's resampling rate, marking it as wide (half rate) when the rate is 2.0 or more. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteSetResamplingRate(s8* arg0, f32 arg1) {
    StereoFlags811105DC* flags = (StereoFlags811105DC*)(arg0 + 0xB4);
    f32 pan;

    if (arg1 < 2.0f) {
        flags->wide = 0;
        if (1.99998f < arg1) {
            pan = 1.99998f;
        } else {
            pan = arg1;
        }
    } else {
        flags->wide = 1;
        if (3.99996f < arg1) {
            pan = 1.99998f;
        } else {
            pan = arg1 * 0.5f;
        }
    }
    M2C_FIELD(arg0, s16*, 0xC0) = pan * 32768.0f;
}

extern NoteSampleState D_811369C0;
void func_8111235C(u8*, s32, char*);

/**
 * Starts a note's envelope from its instrument or the layer's own envelope. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteInit(Note* arg0) {
    SequenceLayer* def = arg0->playbackState.parentLayer;

    if (def->adsr.decayIndex == 0) {
        func_8111235C(&arg0->playbackState.adsr.action, def->channel->adsr.envelope, &arg0->playbackState.adsrVolScale);
    } else {
        func_8111235C(&arg0->playbackState.adsr.action, def->adsr.envelope, &arg0->playbackState.adsrVolScale);
    }
    arg0->playbackState.unk_04 = 0;
    arg0->playbackState.adsr.state = 1;
    arg0->sampleState = D_811369C0;
}

/**
 * Turns a note off and clears its playback state. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteDisable(Note* note) {
    if (note->sampleState.needsInit == 1) {
        note->sampleState.needsInit = 0;
    }
    note->playbackState.priority = 0;
    note->playbackState.unk_04 = 0;
    note->sampleState.enabled = 0;
    note->playbackState.parentLayer = (void*)-1;
    note->playbackState.prevParentLayer = (void*)-1;
    note->sampleState.finished = 0;
    note->playbackState.adsr.state = 0;
    note->playbackState.adsr.current = 0.0f;
}

extern struct Note* D_81184664;
extern s32 D_811858E8;
extern f32 D_811858D0;
extern f32 D_811858D4;
void AudioPlayback_SeqLayerNoteRelease(Particle* arg0);
void AudioPlayback_AudioListRemove(s8*);
void AudioPlayback_AudioListPushFront(M2C_UNK* arg0, M2C_UNK* arg1);
s32 AudioSeq_AudioListPushBack(s8*, struct Note*);
void AudioPlayback_NoteInitForLayer(s8* arg0, s8* arg1);
void func_81112B84(SequenceChannel*);
void func_81112278(Note*);
f32 AudioEffects_UpdateAdsr(u8*);
void func_8111220C(Note*);

/**
 * Updates every note once per audio frame: envelopes, releases, pitch, volume and pan. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_ProcessNotes(void)
{
  Note *note;
  NotePlaybackState *playbackState;
  NoteSampleState *noteSubEu;
  NoteAttributes *attrs;
  s32 pad[2]; // FAKE
  NoteSubAttributes sub_attrs;
  u8 bookOffset;
  f32 scale;
  s32 i;
  for (i = 0; i < D_811858E8; i++)
  {
    note = (Note *) (i * 0xCC + (u32) D_81184664); // FAKE: integer-cast address form
    playbackState = &note->playbackState;
    if (playbackState->parentLayer != ((SequenceLayer *) (-1)))
    {
      if (((u32) playbackState->parentLayer) < 0x7FFFFFFF)
      {
        continue;
      }
      if ((note != playbackState->parentLayer->note) && (playbackState->unk_04 == 0))
      {
        playbackState->adsr.action |= 0x10;
        playbackState->adsr.fadeOutVel = D_811858D4;
        playbackState->priority = 1;
        playbackState->unk_04 = 2;
        goto d;
      }
      else
        if (((!playbackState->parentLayer->enabled) && (playbackState->unk_04 == 0)) && ((playbackState->priority >= 1) ^ 0)) // FAKE: no-op ^ 0
      {
      }
      else
        if (playbackState->parentLayer->channel->seqPlayer == 0)
      {
        func_81112B84(playbackState->parentLayer->channel);
        playbackState->priority = 1;
        playbackState->unk_04 = 1;
        continue;
      }
      else
        if (playbackState->parentLayer->channel->seqPlayer->muted && (playbackState->parentLayer->channel->muteBehavior & 0x40))
      {
      }
      else
      {
        goto d;
      }
      AudioPlayback_SeqLayerNoteRelease((Particle *) playbackState->parentLayer);
      AudioPlayback_AudioListRemove((s8 *) note);
      AudioPlayback_AudioListPushFront((M2C_UNK*)&note->listItem.pool->decaying, (M2C_UNK *) note);
      playbackState->priority = 1;
      playbackState->unk_04 = 2;
    }
    else
      if ((playbackState->unk_04 == 0) && (playbackState->priority >= 1))
    {
      continue;
    }
    d:
    if (playbackState->priority != 0)
    {
      if (1)
      {
        noteSubEu = &note->sampleState;
      }
      if ((playbackState->unk_04 >= 1) || noteSubEu->finished)
      {
        if ((playbackState->adsr.state == 0) || noteSubEu->finished)
        {
          if (playbackState->wantedParentLayer != ((SequenceLayer *) (-1)))
          {
            AudioPlayback_NoteDisable((Note *) note);
            if (playbackState->wantedParentLayer->channel != 0)
            {
              AudioPlayback_NoteInitForLayer((s8 *) note, (s8 *) playbackState->wantedParentLayer);
              func_81112278(note);
              AudioPlayback_AudioListRemove((s8 *) note);
              AudioSeq_AudioListPushBack(&note->listItem.pool->active, (struct Note *) note);
              playbackState->wantedParentLayer = (SequenceLayer *) (-1);
              goto process;
            }
            AudioPlayback_NoteDisable((Note *) note);
            AudioPlayback_AudioListRemove((s8 *) note);
            AudioSeq_AudioListPushBack(&note->listItem.pool->disabled, (struct Note *) note);
            playbackState->wantedParentLayer = (SequenceLayer *) (-1);
          }
          else
          {
            if (playbackState->parentLayer != ((SequenceLayer *) (-1)))
            {
              playbackState->parentLayer->bit1 = 1;
            }
            AudioPlayback_NoteDisable((Note *) note);
            AudioPlayback_AudioListRemove((s8 *) note);
            AudioSeq_AudioListPushBack(&note->listItem.pool->disabled, (struct Note *) note);
          }
        }
        else
        {
          goto process;
        }
      }
      else
        if (playbackState->adsr.state == 0)
      {
        if (playbackState->parentLayer != ((SequenceLayer *) (-1)))
        {
          playbackState->parentLayer->bit1 = 1;
        }
        AudioPlayback_NoteDisable((Note *) note);
        AudioPlayback_AudioListRemove((s8 *) note);
        AudioSeq_AudioListPushBack(&note->listItem.pool->disabled, (struct Note *) note);
      }
      else
      {
        process:
        attrs = &playbackState->attributes;

        scale = AudioEffects_UpdateAdsr((u8 *) (&playbackState->adsr));
        func_8111220C(note);
        if ((playbackState->unk_04 == 1) || (playbackState->unk_04 == 2))
        {
          sub_attrs.freqScale = attrs->freqScale;
          sub_attrs.velocity = attrs->velocity;
          sub_attrs.pan = attrs->pan;
          sub_attrs.reverbVol = attrs->reverbVol;
          sub_attrs.reverbBits = attrs->stereo;
          sub_attrs.gain = attrs->gain;
          sub_attrs.filter = attrs->filter;
          bookOffset = noteSubEu->bookOffset;
        }
        else
        {
          SequenceChannel *channel = playbackState->parentLayer->channel;
          SequenceLayer *layer = playbackState->parentLayer;
          sub_attrs.freqScale = layer->noteFreqScale;
          sub_attrs.velocity = layer->noteVelocity;
          sub_attrs.pan = layer->notePan;
          sub_attrs.reverbBits = layer->stereo;
          sub_attrs.reverbVol = channel->reverb;
          sub_attrs.gain = channel->gain;
          sub_attrs.filter = channel->filter;
          bookOffset = channel->bookOffset & 7;
          if (channel->seqPlayer->muted && (channel->muteBehavior & 8))
          {
            sub_attrs.freqScale = 0.0f;
            sub_attrs.velocity = 0.0f;
          }
        }
        sub_attrs.freqScale *= playbackState->vibratoFreqScale * playbackState->portamentoFreqScale;
        sub_attrs.freqScale *= D_811858D0;
        sub_attrs.velocity *= scale;
        AudioPlayback_InitSampleState((s8 *) note, &sub_attrs);
        noteSubEu->bookOffset = bookOffset;
      }
    }

  }

}

/**
 * Returns the low, normal or high sample of instrument `arg0` for semitone `arg1`. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
u8* AudioPlayback_GetInstrumentTunedSample(u8* arg0, s32 arg1) {
    u8* ret;

    if (arg1 < arg0[1]) {
        ret = arg0 + 8;
    } else if (arg0[2] >= arg1) {
        ret = arg0 + 0x10;
    } else {
        ret = arg0 + 0x18;
    }
    return ret;
}


s32 AudioLoad_IsFontLoadComplete(s32 arg0);
extern SoundFont* D_811858B0;
extern s32 D_811859D0;

/**
 * Returns instrument `arg1` of font `arg0`, or NULL when the font is not loaded or the id is out of range. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
u8* AudioPlayback_GetInstrumentInner(s32 arg0, s32 arg1) {
    SoundFont* bank;
    u8* ret;

    if (AudioLoad_IsFontLoadComplete(arg0) == 0) {
        D_811859D0 = arg0 + 0x10000000;
        return NULL;
    }
    bank = (SoundFont*)((u8*)D_811858B0 + arg0 * sizeof(SoundFont));
    if (arg1 >= bank->numInstruments) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x03000000;
        return NULL;
    }
    ret = bank->instruments[arg1];
    if (ret == NULL) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x01000000;
        return ret;
    }
    return ret;
}

/**
 * Returns drum `arg1` of font `arg0`, or NULL when the font is not loaded or the id is out of range. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
u8* AudioPlayback_GetDrum(s32 arg0, s32 arg1) {
    SoundFont* bank;
    u8* ret;

    if (AudioLoad_IsFontLoadComplete(arg0) == 0) {
        D_811859D0 = arg0 + 0x10000000;
        return NULL;
    }
    bank = (SoundFont*)((u8*)D_811858B0 + arg0 * sizeof(SoundFont));
    if (arg1 >= bank->numDrums) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x04000000;
        return NULL;
    }
    if ((u32)bank->drums < 0x80000000) {
        return NULL;
    }
    ret = bank->drums[arg1];
    if (ret == NULL) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x05000000;
    }
    return ret;
}

#define ADSR_ACTION_RELEASE_E3C 0x10
#define ADSR_ACTION_DECAY_E3C 0x20

extern f32 D_811858D4;
extern f32 D_811858D8;
void AudioPlayback_AudioListRemove(s8*);
void AudioPlayback_AudioListPushFront(M2C_UNK* arg0, M2C_UNK* arg1);

/**
 * Starts the decay (6) or release (7) of the note a sequence layer is playing. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_SeqLayerDecayRelease(SequenceLayer* layer, s32 target) {
    Note* note;
    NoteAttributes* attrs;

    if (layer == (SequenceLayer*)-1) {
        return;
    }

    layer->status = 0;

    if (layer->note == NULL) {
        return;
    }

    note = layer->note;
    attrs = &note->playbackState.attributes;

    if (note->playbackState.wantedParentLayer == layer) {
        note->playbackState.wantedParentLayer = (SequenceLayer*)-1;
    }

    if (note->playbackState.parentLayer != layer) {
        if (note->playbackState.parentLayer == (SequenceLayer*)-1 && note->playbackState.wantedParentLayer == (SequenceLayer*)-1 &&
            note->playbackState.prevParentLayer == layer && target != 6) {
            note->playbackState.adsr.fadeOutVel = D_811858D4;
            note->playbackState.adsr.action |= ADSR_ACTION_RELEASE_E3C;
        }
        return;
    }

    if (note->playbackState.adsr.state != 6) {
        attrs->freqScale = layer->noteFreqScale;
        attrs->velocity = layer->noteVelocity;
        attrs->pan = layer->notePan;
        attrs->stereo = layer->stereo;
        if (layer->channel != NULL) {
            attrs->reverbVol = layer->channel->reverb;
            attrs->gain = layer->channel->gain;
            attrs->filter = layer->channel->filter;
            if (layer->channel->seqPlayer->muted && (layer->channel->muteBehavior & 8)) {
                note->sampleState.finished = 1;
            }
            note->playbackState.priority = layer->channel->someOtherPriority;
        } else {
            note->playbackState.priority = 1;
        }

        note->playbackState.prevParentLayer = note->playbackState.parentLayer;
        note->playbackState.parentLayer = (SequenceLayer*)-1;
        if (target == 7) {
            note->playbackState.adsr.fadeOutVel = D_811858D4;
            note->playbackState.adsr.action |= ADSR_ACTION_RELEASE_E3C;
            note->playbackState.unk_04 = 2;
        } else {
            note->playbackState.unk_04 = 1;
            note->playbackState.adsr.action |= ADSR_ACTION_DECAY_E3C;
            if (layer->adsr.decayIndex == 0) {
                note->playbackState.adsr.fadeOutVel = layer->channel->adsr.decayIndex * D_811858D8;
            } else {
                note->playbackState.adsr.fadeOutVel = layer->adsr.decayIndex * D_811858D8;
            }
            note->playbackState.adsr.sustain = ((f32)(s32)layer->channel->adsr.sustain * note->playbackState.adsr.current) / 256.0f;
        }
    }

    if (target == 6) {
        AudioPlayback_AudioListRemove((s8*)note);
        AudioPlayback_AudioListPushFront((M2C_UNK*)&note->listItem.pool->decaying, (M2C_UNK*)note);
    }
}

/**
 * Starts the decay of the layer's note. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_SeqLayerNoteDecay(Particle* arg0) {
    AudioPlayback_SeqLayerDecayRelease((struct SequenceLayer*)arg0, 6);
}

/**
 * Starts the release of the layer's note. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_SeqLayerNoteRelease(Particle* arg0) {
    AudioPlayback_SeqLayerDecayRelease((struct SequenceLayer*)arg0, 7);
}

/**
 * Makes an empty circular note list. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_InitNoteList(s8 *arg0) {
    M2C_FIELD(arg0, s8 **, 0) = arg0;
    M2C_FIELD(arg0, s8 **, 4) = arg0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

/**
 * AudioPlayback_InitNoteLists
 *
 * Calls AudioPlayback_InitNoteList on four 16-byte blocks at arg0 + 0x00, 0x10, 0x20 and
 * 0x30.  AudioPlayback_InitNoteList stores the block's own address in its first two words
 * and clears the third, giving an empty circular list head {next, prev,
 * count, owner}: AudioPlayback_AudioListPushFront and AudioSeq_AudioListPushBack, which insert into such a
 * list, link through the first two words, increment the third and copy the
 * fourth into the inserted node.  Afterwards arg0 itself is stored in the
 * fourth word (offset 0xC) of each block.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name guessed from the code; comment kept.
 */
void AudioPlayback_InitNoteLists(s8 *arg0) {
    AudioPlayback_InitNoteList(arg0);
    AudioPlayback_InitNoteList(arg0 + 0x10);
    AudioPlayback_InitNoteList(arg0 + 0x20);
    AudioPlayback_InitNoteList(arg0 + 0x30);
    M2C_FIELD(arg0, s8 **, 0xC) = arg0;
    M2C_FIELD(arg0, s8 **, 0x1C) = arg0;
    M2C_FIELD(arg0, s8 **, 0x2C) = arg0;
    M2C_FIELD(arg0, s8 **, 0x3C) = arg0;
}

s32 AudioSeq_AudioListPushBack(s8*, Note*);
extern Note* D_81184664;
extern s8 D_81184938;
extern s32 D_811858E8;

/**
 * AudioPlayback_InitNoteFreeList
 *
 * Calls AudioPlayback_InitNoteLists(&D_81184938), then for each of the D_811858E8 records of
 * the array at D_81184664 (0xCC bytes each, indexed directly each time):
 * stores the record's own address at offset 8, clears the word at offset 0,
 * and calls AudioSeq_AudioListPushBack(&D_81184938, record). AudioHeap_DiscardFont, which walks the
 * same array, passes the same list argument to the same function. What the
 * records are is not established from this function.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name guessed from the code; comment kept.
 */
void AudioPlayback_InitNoteFreeList(void) {
    s32 i;

    AudioPlayback_InitNoteLists(&D_81184938);
    for (i = 0; i < D_811858E8; i++) {
        D_81184664[i].listItem.u.value = &D_81184664[i];
        D_81184664[i].listItem.prev = 0;
        AudioSeq_AudioListPushBack(&D_81184938, &D_81184664[i]);
    }
}

extern s8 D_81184948;
extern s8 D_81184958;
extern s8 D_81184968;
void AudioPlayback_AudioListRemove(s8*);

/**
 * Moves every note in the four lists of a note pool back to the matching
 * global free list (D_81184938, D_81184948, D_81184958, D_81184968). Same
 * structure as note_pool_clear in the Super Mario 64 audio library.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name guessed from the code; comment kept.
 */
void AudioPlayback_NotePoolClear(NotePool* pool) {
    s32 i;
    AudioListItem* source;
    AudioListItem* cur;
    s8* dest;

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                source = &pool->disabled;
                dest = &D_81184938;
                break;

            case 1:
                source = &pool->decaying;
                dest = &D_81184948;
                break;

            case 2:
                source = &pool->releasing;
                dest = &D_81184958;
                break;

            case 3:
                source = &pool->active;
                dest = &D_81184968;
                break;
        }

        for (;;) {
            cur = source->next;
            if (cur == source) {
                break;
            }
            if (cur == NULL) {
                break;
            }
            AudioPlayback_AudioListRemove((s8*)cur);
            AudioSeq_AudioListPushBack(dest, (Note*)cur);
        }
    }
}

s32 AudioSeq_AudioListPopBack(AudioListItem* list);
/**
 * Takes `arg1` notes from the global free lists into a pool. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NotePoolFill(s8* arg0, s32 arg1) {
    s32 pad[3]; /* places src/dst at sp+0x48/0x44 and the frame at 0x58 as in the ROM */
    s8* src;
    s8* dst;
    s32 n;
    s32 pass;
    s32 r;

    AudioPlayback_NotePoolClear((NotePool*)arg0);
    for (pass = 0, n = 0; n < arg1; pass++) {
        if (pass == 4) {
            return;
        }
        switch (pass) {
            case 0:
                src = &D_81184938;
                dst = arg0;
                break;
            case 1:
                src = &D_81184948;
                dst = arg0 + 0x10;
                break;
            case 2:
                src = &D_81184958;
                dst = arg0 + 0x20;
                break;
            case 3:
                src = &D_81184968;
                dst = arg0 + 0x30;
                break;
        }
        while (n < arg1) {
            r = AudioSeq_AudioListPopBack(src);
            if (r == 0) {
                break;
            }
            AudioSeq_AudioListPushBack(dst, (Note*)r);
            n++;
        }
    }
}

/**
 * Pushes list item `arg1` onto the front of list `arg0` if it is on no list. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_AudioListPushFront(M2C_UNK *arg0, M2C_UNK *arg1) {
    if (M2C_FIELD(arg1, M2C_UNK **, 0) == NULL) {
        M2C_FIELD(arg1, M2C_UNK **, 0) = arg0;
        M2C_FIELD(arg1, M2C_UNK **, 4) = (M2C_UNK *) M2C_FIELD(arg0, M2C_UNK **, 4);
        *M2C_FIELD(arg0, M2C_UNK **, 4) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = arg1;
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + 1);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    }
}

/**
 * Unlinks a list item from its list. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_AudioListRemove(s8 *arg0) {
    s8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s8 ***, 4) = (s8 **) M2C_FIELD(arg0, s8 ***, 4);
        *M2C_FIELD(arg0, s8 ***, 4) = M2C_FIELD(arg0, s8 **, 0);
        M2C_FIELD(arg0, s8 **, 0) = NULL;
    }
}

/**
 * Returns the note in list `arg0` with the lowest priority below `arg1`, or NULL. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s8 *AudioPlayback_FindNodeWithPrioLessThan(s8 *arg0, s32 arg1) {
    s8 *temp_a0;
    s8 *var_v0;
    s8 *var_v1;

    var_v0 = M2C_FIELD(arg0, s8 **, 4);
    if (var_v0 == arg0) {
        return NULL;
    }
    var_v1 = var_v0;
    if (var_v0 != arg0) {
        do {
            if ((s32) M2C_FIELD(M2C_FIELD(var_v1, s8 **, 8), u8 *, 0x30) >= (s32) M2C_FIELD(M2C_FIELD(var_v0, s8 **, 8), u8 *, 0x30)) {
                var_v1 = var_v0;
            }
            var_v0 = M2C_FIELD(var_v0, s8 **, 4);
        } while (var_v0 != arg0);
    }
    if (var_v1 == NULL) {
        return NULL;
    }
    temp_a0 = M2C_FIELD(var_v1, s8 **, 8);
    if ((s32) M2C_FIELD(temp_a0, u8 *, 0x30) >= arg1) {
        return NULL;
    }
    return temp_a0;
}

/**
 * Gives note `arg0` to layer `arg1` and sets it up from the layer's instrument. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteInitForLayer(s8* arg0, s8* arg1) {
    NoteSampleState* flags;
    s32 v;

    M2C_FIELD(arg0, s32*, 0x40) = -1;
    M2C_FIELD(arg0, s8**, 0x44) = arg1;
    M2C_FIELD(arg0, u8*, 0x30) = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x54), u8*, 5);
    ((SequenceLayer*)arg1)->notePropertiesNeedInit = 1;
    M2C_FIELD(arg1, u8*, 3) = 3;
    M2C_FIELD(arg1, s8**, 0x48) = arg0;
    M2C_FIELD(M2C_FIELD(arg1, s8**, 0x54), s8**, 0x40) = arg0;
    M2C_FIELD(M2C_FIELD(arg1, s8**, 0x54), s8**, 0x44) = arg1;
    M2C_FIELD(arg1, f32*, 0x34) = 0.0f;
    AudioPlayback_NoteInit((Note*)arg0);
    v = M2C_FIELD(arg1, u8*, 2);
    flags = (NoteSampleState*)(arg0 + 0xB4);
    if (v == 0xFF) {
        v = M2C_FIELD(M2C_FIELD(arg1, s8**, 0x54), s16*, 0x22);
    }
    flags->tunedSample = M2C_FIELD(arg1, s32*, 0x50);
    if (v >= 0x80 && v < 0xC0) {
        flags->isSyntheticWave = 1;
    } else {
        flags->isSyntheticWave = 0;
    }
    M2C_FIELD(arg0, u8*, 0x33) = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x54), u8*, 7);
    flags->stereoHeadsetEffects = M2C_FIELD(arg1, SequenceChannel**, 0x54)->stereoHeadsetEffects;
    flags->reverbIndex = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x54), u8*, 8) & 3;
}


/**
 * Releases the note's current layer and queues layer `arg1` to take it over. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteReleaseOwnerAndQueueLayer(s8 *arg0, s32 arg1) {
    AudioPlayback_SeqLayerNoteRelease(M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
}

extern f32 D_FLT_811858D4;
/**
 * Starts releasing the note and hands it to layer `arg1` with the layer's priority. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteReleaseAndTakeOwnership(s8 *arg0, s8 *arg1)
{
  *((s8 **) (((s8 *) arg0) + 0x48)) = arg1;
  *((u8 *) (((s8 *) arg0) + 0x30)) = (u8) (*((u8 *) (((s8 *) (*((s8 **) (((s8 *) arg1) + 0x54)))) + 5))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((f32 *) (((s8 *) arg0) + 0x6C)) = (f32) D_FLT_811858D4;
  *((u8 *) (((s8 *) arg0) + 0x5C)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x5C))) | 0x10); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

/*
 * AudioPlayback_AllocNoteFromDisabled
 *
 * Moves one entry from the list headed at arg0 to the list headed at
 * arg0 + 0x30.  The list heads are 16-byte blocks laid out as
 * {next, prev, count, owner}, as set up by AudioPlayback_InitNoteList and AudioPlayback_InitNoteLists.
 *
 *   1. AudioSeq_AudioListPopBack(arg0) unlinks the first node of the list at arg0 and
 *      returns the word stored at offset 8 of that node (0 if the list is
 *      empty).  That value is the entry used below and the return value.
 *   2. If it is not 0, AudioPlayback_NoteInitForLayer(entry, arg1) is called on it, and
 *      AudioPlayback_AudioListPushFront then appends the entry to the list at arg0 + 0x30
 *      (it does nothing if the entry's first word is already non-zero).
 *
 * Returns the entry, or 0 if there was none.  What AudioPlayback_NoteInitForLayer does with
 * arg1 is not established (it is still assembly).
 */
s32 AudioSeq_AudioListPopBack(AudioListItem* list);
void AudioPlayback_NoteInitForLayer(s8*, s8*);

/**
 * Allocates a note for a layer from a pool's disabled list. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioPlayback_AllocNoteFromDisabled(s8 *arg0, s32 arg1) {
    s32 ret;

    ret = AudioSeq_AudioListPopBack(arg0);
    if (ret != 0) {
        AudioPlayback_NoteInitForLayer((s8*)ret, (s8*)arg1);
        AudioPlayback_AudioListPushFront((M2C_UNK *) (arg0 + 0x30), (M2C_UNK *) ret);
    }
    return ret;
}

/*
 * AudioPlayback_AllocNoteFromDecaying
 *
 * Like AudioPlayback_AllocNoteFromDisabled, but it takes the entry from the list headed at
 * arg0 + 0x10, initializes it with AudioPlayback_NoteReleaseAndTakeOwnership(entry, arg1), and inserts
 * it at the front of the list headed at arg0 + 0x20 with AudioSeq_AudioListPushBack.
 * List heads are {next, prev, count, owner} blocks (see AudioPlayback_InitNoteList).
 *
 * AudioSeq_AudioListPopBack unlinks the first node of the list at arg0 + 0x10 and
 * returns the word at offset 8 of that node, or 0 if the list is empty.
 * Returns that entry, or 0 if there was none; nothing else happens then.
 */
s32 AudioSeq_AudioListPopBack(AudioListItem* list);

/**
 * Takes over a decaying note for a layer. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioPlayback_AllocNoteFromDecaying(s8 *arg0, s8 *arg1) {
    s32 ret;

    ret = AudioSeq_AudioListPopBack(arg0 + 0x10);
    if (ret != 0) {
        AudioPlayback_NoteReleaseAndTakeOwnership((s8 *) ret, arg1);
        AudioSeq_AudioListPushBack(arg0 + 0x20, (s8 *) ret);
    }
    return ret;
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Steals the lowest-priority active note for a layer. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s8 *AudioPlayback_AllocNoteFromActive(s8 *arg0, s8 *arg1)
{
  s8 *a;
  s8 *b;
  s32 prioA;
  s32 prioB;
  prioA = (prioB = 0x10);
  a = AudioPlayback_FindNodeWithPrioLessThan(arg0 + 0x20, *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  if (a != 0)
  {
    prioA = *((u8 *) (((s8 *) a) + 0x30));
  }
  b = AudioPlayback_FindNodeWithPrioLessThan(arg0 + 0x30, *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  if (b != 0)
  {
    prioB = *((u8 *) (((s8 *) b) + 0x30));
  }
  if ((a == 0) && (b == 0))
  {
    return 0;
  }
  if (prioB < (prioA ^ 0)) // FAKE: no-op ^ 0
  {
    AudioPlayback_AudioListRemove(b);
    AudioPlayback_NoteReleaseOwnerAndQueueLayer(b, (s32) arg1);
    AudioSeq_AudioListPushBack(arg0 + 0x20, (Note *) b);
    *((u8 *) (((s8 *) b) + 0x30)) = *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    return b;
  }
  *((s8 **) (((s8 *) a) + 0x48)) = arg1;
  *((u8 *) (((s8 *) a) + 0x30)) = *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  return a;
}

/**
 * Allocates a note for a layer by its channel's note-stealing policy. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s8* AudioPlayback_AllocNote(s8* arg0) {
    s8* voice;
    s32 flags = M2C_FIELD(arg0, u8**, 0x54)[2];

    if (flags & 1) {
        voice = M2C_FIELD(arg0, s8**, 0x48);
        if ((voice != NULL) && (arg0 == M2C_FIELD(voice, s8**, 0x40)) && (M2C_FIELD(voice, s32*, 0x48) == -1)) {
            AudioPlayback_NoteReleaseAndTakeOwnership(voice, arg0);
            AudioPlayback_AudioListRemove(voice);
            AudioSeq_AudioListPushBack(M2C_FIELD(voice, s8**, 0xC) + 0x20, (Note*)voice);
            return voice;
        }
    }
    if (flags & 2) {
        if (((voice = (s8*)AudioPlayback_AllocNoteFromDisabled(M2C_FIELD(arg0, s8**, 0x54) + 0x84, (s32)arg0)) != NULL) ||
            ((voice = (s8*)AudioPlayback_AllocNoteFromDecaying(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = AudioPlayback_AllocNoteFromActive(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL)) {
            return voice;
        }
    } else if (flags & 4) {
        if (((voice = (s8*)AudioPlayback_AllocNoteFromDisabled(M2C_FIELD(arg0, s8**, 0x54) + 0x84, (s32)arg0)) != NULL) ||
            ((voice = (s8*)AudioPlayback_AllocNoteFromDisabled(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x54), s8**, 0x4C) + 0x98, (s32)arg0)) != NULL) ||
            ((voice = (s8*)AudioPlayback_AllocNoteFromDecaying(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = (s8*)AudioPlayback_AllocNoteFromDecaying(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x54), s8**, 0x4C) + 0x98, arg0)) != NULL) ||
            ((voice = AudioPlayback_AllocNoteFromActive(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = AudioPlayback_AllocNoteFromActive(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x54), s8**, 0x4C) + 0x98, arg0)) != NULL)) {
            return voice;
        }
    } else if (flags & 8) {
        if (((voice = (s8*)AudioPlayback_AllocNoteFromDisabled(&D_81184938, (s32)arg0)) != NULL) ||
            ((voice = (s8*)AudioPlayback_AllocNoteFromDecaying(&D_81184938, arg0)) != NULL) ||
            ((voice = AudioPlayback_AllocNoteFromActive(&D_81184938, arg0)) != NULL)) {
            return voice;
        }
    } else {
        if (((voice = (s8*)AudioPlayback_AllocNoteFromDisabled(M2C_FIELD(arg0, s8**, 0x54) + 0x84, (s32)arg0)) != NULL) ||
            ((voice = (s8*)AudioPlayback_AllocNoteFromDisabled(&D_81184938, (s32)arg0)) != NULL) ||
            ((voice = (s8*)AudioPlayback_AllocNoteFromDecaying(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = (s8*)AudioPlayback_AllocNoteFromDecaying(&D_81184938, arg0)) != NULL) ||
            ((voice = AudioPlayback_AllocNoteFromActive(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = AudioPlayback_AllocNoteFromActive(&D_81184938, arg0)) != NULL)) {
            return voice;
        }
    }
    arg0[3] = 0;
    return NULL;
}

extern NoteSampleState D_811369A8;
extern s8 D_811842C0;
s32 func_81109868(s8 *, s32);
/**
 * Resets every note's state and sample buffers. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteInitAll(void) {
    s32 i;
    Note* rec;

    for (i = 0; i < D_811858E8; i++) {
        rec = (Note*)&D_81184664[i];
        rec->sampleState = D_811369A8;
        rec->playbackState.priority = 0;
        rec->playbackState.unk_04 = 0;
        rec->playbackState.parentLayer = -1;
        rec->playbackState.wantedParentLayer = -1;
        rec->playbackState.prevParentLayer = -1;
        rec->playbackState.waveId = 0;
        rec->playbackState.attributes.velocity = 0.0f;
        rec->playbackState.adsrVolScale = 0;
        rec->playbackState.adsr.state = 0;
        rec->playbackState.adsr.action = 0;
        rec->playbackState.vibratoState.active = 0;
        rec->playbackState.portamento.cur = 0.0f;
        rec->playbackState.portamento.speed = 0.0f;
        rec->synthesisState.synthesisBuffers = func_81109868(&D_811842C0, 0x80);
    }
}
