/* Stadium Zero fragment000_80C00. */

#include "global.h"
#include "fragments/particle_math/particle_math.h"
#include "m2c_macros.h"
struct LayerE3C;
void AudioPlayback_SeqLayerDecayRelease(struct LayerE3C*, s32);

void AudioPlayback_NoteSetResamplingRate(s8* arg0, f32 arg1);

typedef struct ReverbBits81110210 {
    /* 0x0 */ u8 bit0 : 1;
    /* 0x0 */ u8 bit1 : 1;
    /* 0x0 */ u8 bit2 : 1;
    /* 0x0 */ u8 usesHeadsetPanEffects : 1;
    /* 0x0 */ u8 stereoHeadsetEffects : 2;
    /* 0x0 */ u8 strongRight : 1;
    /* 0x0 */ u8 strongLeft : 1;
} ReverbBits81110210;

typedef struct ReverbInfo81110210 {
    /* 0x00 */ u8 reverbVol;
    /* 0x01 */ u8 bankId;
    /* 0x02 */ u8 pan;
    /* 0x03 */ ReverbBits81110210 reverbBits;
    /* 0x04 */ f32 freqScale;
    /* 0x08 */ f32 velocity;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 synthesisVolume;
} ReverbInfo81110210;

typedef struct NoteSub81110210 {
    /* 0x00 */ volatile u8 enabled : 1;
    /* 0x00 */ u8 needsInit : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 envMixerNeedsInit : 1;
    /* 0x00 */ u8 stereoStrongRight : 1;
    /* 0x00 */ u8 stereoStrongLeft : 1;
    /* 0x00 */ u8 stereoHeadsetEffects : 1;
    /* 0x00 */ u8 usesHeadsetPanEffects : 1;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 bankId;
    /* 0x03 */ u8 headsetPanRight;
    /* 0x04 */ u8 headsetPanLeft;
    /* 0x05 */ u8 reverbVol;
    /* 0x06 */ u8 unk06[2];
    /* 0x08 */ u16 targetVolLeft;
    /* 0x0A */ u16 targetVolRight;
    /* 0x0C */ u8 unk0C[8];
    /* 0x14 */ s32 synthesisVolume;
} NoteSub81110210;

extern s8 D_811858EE;
extern u16 D_811369D8[];
extern f32 D_81136AD8[];
extern f32 D_81136CD8[];
extern f32 D_81136ED8[];

/**
 * Sets a note's left and right volume, pan and reverb from its attributes. Zelda 64 audio driver (playback.c), same position and shape.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_InitSampleState(s8* note, ReverbInfo81110210* reverb_info) {
    NoteSub81110210* sub;
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
    ReverbBits81110210 reverbBits;

    AudioPlayback_NoteSetResamplingRate(note, reverb_info->freqScale);
    velocity = reverb_info->velocity;
    pan = reverb_info->pan;
    reverbVol = reverb_info->reverbVol;
    reverbBits = reverb_info->reverbBits;
    sub = (NoteSub81110210*)(note + 0xB4);
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
        switch (reverbBits.stereoHeadsetEffects) {
            case 0:
                sub->stereoStrongRight = reverbBits.strongRight;
                sub->stereoStrongLeft = reverbBits.strongLeft;
                break;
            case 1:
                break;
            case 2:
                sub->stereoStrongRight = reverbBits.strongRight | strongRight;
                sub->stereoStrongLeft = reverbBits.strongLeft | strongLeft;
                break;
            case 3:
                sub->stereoStrongRight = reverbBits.strongRight ^ strongRight;
                sub->stereoStrongLeft = reverbBits.strongLeft ^ strongLeft;
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
    sub->bankId = reverb_info->bankId;
    sub->synthesisVolume = reverb_info->synthesisVolume;

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

typedef struct Copy18 {
    s32 w[6];
} Copy18;
typedef struct Inner0694 {
    char pad00[0x80];
    s32 unk_80;
} Inner0694;
typedef struct Def0694 {
    char pad00[0x18];
    u8 unk_18;
    s32 unk_1C;
    char pad20[0x54 - 0x20];
    Inner0694* unk_54;
} Def0694;
typedef struct Obj0694 {
    char pad00[0x34];
    u8 unk_34;
    char pad35;
    char unk_36[0x44 - 0x36];
    Def0694* unk_44;
    char pad48[0x5C - 0x48];
    u8 unk_5C;
    u8 unk_5D;
    char pad5E[0xB4 - 0x5E];
    Copy18 unk_B4;
} Obj0694;
extern Copy18 D_811369C0;
void func_8111235C(u8*, s32, char*);

/**
 * Starts a note's envelope from its instrument or the layer's own envelope. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteInit(Obj0694* arg0) {
    Def0694* def = arg0->unk_44;

    if (def->unk_18 == 0) {
        func_8111235C(&arg0->unk_5C, def->unk_54->unk_80, arg0->unk_36);
    } else {
        func_8111235C(&arg0->unk_5C, def->unk_1C, arg0->unk_36);
    }
    arg0->unk_34 = 0;
    arg0->unk_5D = 1;
    arg0->unk_B4 = D_811369C0;
}

typedef struct Flags8111073C {
    /* 0x0 */ volatile u32 enabled : 1; // volatile like SM64 NoteSubEu.enabled; stops IDO reusing the flag byte
    /* 0x0 */ u32 needsInit : 1;
    /* 0x0 */ u32 finished : 1;
    /* 0x0 */ u32 rest : 29;
} Flags8111073C;

typedef struct PlaybackState8111073C {
    /* 0x00 */ u8 priority;
    /* 0x01 */ char unk01[3];
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xB];
    /* 0x10 */ void* prevParentLayer;
    /* 0x14 */ void* parentLayer;
    /* 0x18 */ char unk18[0x2D - 0x18];
    /* 0x2D */ u8 adsrState;
    /* 0x2E */ char unk2E[0x40 - 0x2E];
    /* 0x40 */ f32 adsrCurrent;
} PlaybackState8111073C;

typedef struct Note8111073C {
    /* 0x00 */ char unk00[0x30];
    /* 0x30 */ PlaybackState8111073C playbackState;
    /* 0x74 */ char unk74[0xB4 - 0x74];
    /* 0xB4 */ Flags8111073C noteSubEu;
} Note8111073C;

/**
 * Turns a note off and clears its playback state. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteDisable(Note8111073C* note) {
    if (note->noteSubEu.needsInit == 1) {
        note->noteSubEu.needsInit = 0;
    }
    note->playbackState.priority = 0;
    note->playbackState.unk04 = 0;
    note->noteSubEu.enabled = 0;
    note->playbackState.parentLayer = (void*)-1;
    note->playbackState.prevParentLayer = (void*)-1;
    note->noteSubEu.finished = 0;
    note->playbackState.adsrState = 0;
    note->playbackState.adsrCurrent = 0.0f;
}

typedef struct SeqPlayer81110798 {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 muted : 1;
    /* 0x00 */ u32 rest : 29;
} SeqPlayer81110798;

typedef struct Channel81110798 {
    /* 0x00 */ u8 unk00[3];
    /* 0x03 */ u8 muteBehavior;
    /* 0x04 */ u8 reverb;
    /* 0x05 */ u8 unk05[4];
    /* 0x09 */ u8 bookOffset;
    /* 0x0A */ u8 unk0A[2];
    /* 0x0C */ u8 gain;
    /* 0x0D */ u8 unk0D[0x4C - 0x0D];
    /* 0x4C */ SeqPlayer81110798* seqPlayer;
    /* 0x50 */ u8 unk50[0xD0 - 0x50];
    /* 0xD0 */ s32 filter;
} Channel81110798;

typedef struct Layer81110798 {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 rest : 6;
    /* 0x00 */ u8 bit1 : 1;
    /* 0x01 */ ReverbBits81110210 stereo;
    /* 0x02 */ u8 unk02[5];
    /* 0x07 */ u8 notePan;
    /* 0x08 */ u8 unk08[0x34 - 0x08];
    /* 0x34 */ f32 noteVelocity;
    /* 0x38 */ f32 noteFreqScale;
    /* 0x3C */ u8 unk3C[0x48 - 0x3C];
    /* 0x48 */ struct Note81110798* note;
    /* 0x4C */ u8 unk4C[0x54 - 0x4C];
    /* 0x54 */ Channel81110798* channel;
} Layer81110798;

typedef struct NoteSubEu81110798 {
    /* 0x00 */ volatile u32 enabled : 1;
    /* 0x00 */ u32 needsInit : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 unk : 8;
    /* 0x01 */ u32 bookOffset : 2;
    /* 0x01 */ u32 rest : 19;
} NoteSubEu81110798;

typedef struct NoteAttributes81110798 {
    /* 0x00 */ u8 reverbVol;
    /* 0x01 */ u8 bankId;
    /* 0x02 */ u8 pan;
    /* 0x03 */ ReverbBits81110210 reverbBits;
    /* 0x04 */ f32 freqScale;
    /* 0x08 */ f32 velocity;
    /* 0x0C */ s32 unk0C;
} NoteAttributes81110798;

typedef struct Adsr81110798 {
    /* 0x00 */ u8 action;
    /* 0x01 */ u8 state;
    /* 0x02 */ u8 unk02[0xE];
    /* 0x10 */ f32 fadeOutVel;
    /* 0x14 */ f32 current;
} Adsr81110798;

typedef struct PlaybackState81110798 {
    /* 0x00 */ u8 priority;
    /* 0x01 */ u8 unk01[3];
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk05[3];
    /* 0x08 */ f32 portamentoFreqScale;
    /* 0x0C */ f32 vibratoFreqScale;
    /* 0x10 */ Layer81110798* prevParentLayer;
    /* 0x14 */ Layer81110798* parentLayer;
    /* 0x18 */ Layer81110798* wantedParentLayer;
    /* 0x1C */ NoteAttributes81110798 attributes;
    /* 0x2C */ Adsr81110798 adsr;
} PlaybackState81110798;

typedef struct Note81110798 {
    /* 0x00 */ u8 unk00[0xC];
    /* 0x0C */ s8* pool;
    /* 0x10 */ u8 unk10[0x30 - 0x10];
    /* 0x30 */ PlaybackState81110798 playbackState;
    /* 0x74 */ u8 unk74[0xB4 - 0x74];
    /* 0xB4 */ NoteSubEu81110798 noteSubEu;
    /* 0xB8 */ u8 unkB8[0xCC - 0xB8];
} Note81110798; // size = 0xCC

struct Rec81111130;
extern struct Rec81111130* D_81184664;
extern s32 D_811858E8;
extern f32 D_811858D0;
extern f32 D_811858D4;
void AudioPlayback_SeqLayerNoteRelease(Particle* arg0);
void AudioPlayback_AudioListRemove(s8*);
void AudioPlayback_AudioListPushFront(M2C_UNK* arg0, M2C_UNK* arg1);
s32 AudioSeq_AudioListPushBack(s8*, struct Rec81111130*);
void AudioPlayback_NoteInitForLayer(s8* arg0, s8* arg1);
void func_81112B84(Channel81110798*);
void func_81112278(Note81110798*);
f32 AudioEffects_UpdateAdsr(u8*);
void func_8111220C(Note81110798*);

/**
 * Updates every note once per audio frame: envelopes, releases, pitch, volume and pan. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_ProcessNotes(void)
{
  Note81110798 *note;
  PlaybackState81110798 *playbackState;
  NoteSubEu81110798 *noteSubEu;
  NoteAttributes81110798 *attrs;
  s32 pad[2]; // FAKE
  ReverbInfo81110210 sub_attrs;
  u8 bookOffset;
  f32 scale;
  s32 i;
  for (i = 0; i < D_811858E8; i++)
  {
    note = (Note81110798 *) (i * 0xCC + (u32) D_81184664); // FAKE: integer-cast address form
    playbackState = &note->playbackState;
    if (playbackState->parentLayer != ((Layer81110798 *) (-1)))
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
      AudioPlayback_AudioListPushFront((M2C_UNK *) (note->pool + 0x10), (M2C_UNK *) note);
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
        noteSubEu = &note->noteSubEu;
      }
      if ((playbackState->unk_04 >= 1) || noteSubEu->finished)
      {
        if ((playbackState->adsr.state == 0) || noteSubEu->finished)
        {
          if (playbackState->wantedParentLayer != ((Layer81110798 *) (-1)))
          {
            AudioPlayback_NoteDisable((Note8111073C *) note);
            if (playbackState->wantedParentLayer->channel != 0)
            {
              AudioPlayback_NoteInitForLayer((s8 *) note, (s8 *) playbackState->wantedParentLayer);
              func_81112278(note);
              AudioPlayback_AudioListRemove((s8 *) note);
              AudioSeq_AudioListPushBack(note->pool + 0x30, (struct Rec81111130 *) note);
              playbackState->wantedParentLayer = (Layer81110798 *) (-1);
              goto process;
            }
            AudioPlayback_NoteDisable((Note8111073C *) note);
            AudioPlayback_AudioListRemove((s8 *) note);
            AudioSeq_AudioListPushBack(note->pool, (struct Rec81111130 *) note);
            playbackState->wantedParentLayer = (Layer81110798 *) (-1);
          }
          else
          {
            if (playbackState->parentLayer != ((Layer81110798 *) (-1)))
            {
              playbackState->parentLayer->bit1 = 1;
            }
            AudioPlayback_NoteDisable((Note8111073C *) note);
            AudioPlayback_AudioListRemove((s8 *) note);
            AudioSeq_AudioListPushBack(note->pool, (struct Rec81111130 *) note);
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
        if (playbackState->parentLayer != ((Layer81110798 *) (-1)))
        {
          playbackState->parentLayer->bit1 = 1;
        }
        AudioPlayback_NoteDisable((Note8111073C *) note);
        AudioPlayback_AudioListRemove((s8 *) note);
        AudioSeq_AudioListPushBack(note->pool, (struct Rec81111130 *) note);
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
          sub_attrs.reverbBits = attrs->reverbBits;
          sub_attrs.bankId = attrs->bankId;
          sub_attrs.synthesisVolume = attrs->unk0C;
          bookOffset = noteSubEu->bookOffset;
        }
        else
        {
          Channel81110798 *channel = playbackState->parentLayer->channel;
          Layer81110798 *layer = playbackState->parentLayer;
          sub_attrs.freqScale = layer->noteFreqScale;
          sub_attrs.velocity = layer->noteVelocity;
          sub_attrs.pan = layer->notePan;
          sub_attrs.reverbBits = layer->stereo;
          sub_attrs.reverbVol = channel->reverb;
          sub_attrs.bankId = channel->gain;
          sub_attrs.synthesisVolume = channel->filter;
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

typedef struct ParticleBank81110CA8 {
    /* 0x0 */ u8 count;
    /* 0x1 */ u8 count2;
    /* 0x4 */ u8** entries;
    /* 0x8 */ u8** entries2;
} ParticleBank81110CA8; // size = 0xC

s32 AudioLoad_IsFontLoadComplete(s32 arg0);
extern ParticleBank81110CA8* D_811858B0;
extern s32 D_811859D0;

/**
 * Returns instrument `arg1` of font `arg0`, or NULL when the font is not loaded or the id is out of range. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
u8* AudioPlayback_GetInstrumentInner(s32 arg0, s32 arg1) {
    ParticleBank81110CA8* bank;
    u8* ret;

    if (AudioLoad_IsFontLoadComplete(arg0) == 0) {
        D_811859D0 = arg0 + 0x10000000;
        return NULL;
    }
    bank = (ParticleBank81110CA8*)((u8*)D_811858B0 + arg0 * sizeof(ParticleBank81110CA8));
    if (arg1 >= bank->count) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x03000000;
        return NULL;
    }
    ret = bank->entries[arg1];
    if (ret == NULL) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x01000000;
        return ret;
    }
    return ret;
}

/**
 * Returns drum `arg1` of font `arg0`, or NULL when the font is not loaded or the id is out of range. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
u8* AudioPlayback_GetDrum(s32 arg0, s32 arg1) {
    ParticleBank81110CA8* bank;
    u8* ret;

    if (AudioLoad_IsFontLoadComplete(arg0) == 0) {
        D_811859D0 = arg0 + 0x10000000;
        return NULL;
    }
    bank = (ParticleBank81110CA8*)((u8*)D_811858B0 + arg0 * sizeof(ParticleBank81110CA8));
    if (arg1 >= bank->count2) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x04000000;
        return NULL;
    }
    if ((u32)bank->entries2 < 0x80000000) {
        return NULL;
    }
    ret = bank->entries2[arg1];
    if (ret == NULL) {
        D_811859D0 = (arg0 << 8) + arg1 + 0x05000000;
    }
    return ret;
}

typedef struct StereoE3C {
    u8 type : 2;
    u8 strongRight : 1;
    u8 strongLeft : 1;
    u8 stereoHeadsetEffects : 1;
    u8 usesHeadsetPanEffects : 1;
    u8 pad : 2;
} StereoE3C;

typedef struct SeqPlayerE3C {
    /* 0x00 */ u32 enabled : 1;
    /* 0x00 */ u32 finished : 1;
    /* 0x00 */ u32 muted : 1;
    /* 0x00 */ u32 rest : 29;
} SeqPlayerE3C;

typedef struct ChannelE3C {
    /* 0x00 */ u8 unk00[3];
    /* 0x03 */ u8 muteBehavior;
    /* 0x04 */ u8 reverb;
    /* 0x05 */ u8 notePriority;
    /* 0x06 */ u8 someOtherPriority;
    /* 0x07 */ u8 unk07[5];
    /* 0x0C */ u8 gain;
    /* 0x0D */ u8 unk0D[0x4C - 0x0D];
    /* 0x4C */ SeqPlayerE3C* seqPlayer;
    /* 0x50 */ u8 unk50[0x7C - 0x50];
    /* 0x7C */ u8 decayIndex;
    /* 0x7D */ u8 sustain;
    /* 0x7E */ u8 unk7E[0xD0 - 0x7E];
    /* 0xD0 */ s16* filter;
} ChannelE3C;

typedef struct LayerE3C {
    /* 0x00 */ u8 flags;
    /* 0x01 */ StereoE3C stereo;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 status;
    /* 0x04 */ u8 unk04[3];
    /* 0x07 */ u8 notePan;
    /* 0x08 */ u8 unk08[0x18 - 0x08];
    /* 0x18 */ u8 decayIndex;
    /* 0x19 */ u8 unk19[0x34 - 0x19];
    /* 0x34 */ f32 noteVelocity;
    /* 0x38 */ f32 noteFreqScale;
    /* 0x3C */ u8 unk3C[0x48 - 0x3C];
    /* 0x48 */ struct NoteE3C* note;
    /* 0x4C */ u8 unk4C[0x54 - 0x4C];
    /* 0x54 */ ChannelE3C* channel;
} LayerE3C;

typedef struct NoteAttributesE3C {
    /* 0x00 */ u8 reverb;
    /* 0x01 */ u8 gain;
    /* 0x02 */ u8 pan;
    /* 0x03 */ StereoE3C stereo;
    /* 0x04 */ f32 freqScale;
    /* 0x08 */ f32 velocity;
    /* 0x0C */ s16* filter;
} NoteAttributesE3C;

#define ADSR_ACTION_RELEASE_E3C 0x10
#define ADSR_ACTION_DECAY_E3C 0x20

typedef struct AdsrE3C {
    /* 0x00 */ u8 action;
    /* 0x01 */ u8 state;
    /* 0x02 */ u8 unk02[6];
    /* 0x08 */ f32 sustain;
    /* 0x0C */ u8 unk0C[4];
    /* 0x10 */ f32 fadeOutVel;
    /* 0x14 */ f32 current;
} AdsrE3C;

typedef struct NoteE3C {
    /* 0x00 */ void* prev;
    /* 0x04 */ void* next;
    /* 0x08 */ void* value;
    /* 0x0C */ s8* pool;
    /* 0x10 */ u8 unk10[0x30 - 0x10];
    /* 0x30 */ u8 priority;
    /* 0x31 */ u8 unk31[3];
    /* 0x34 */ u8 unk_04;
    /* 0x35 */ u8 unk35[0x40 - 0x35];
    /* 0x40 */ LayerE3C* prevParentLayer;
    /* 0x44 */ LayerE3C* parentLayer;
    /* 0x48 */ LayerE3C* wantedParentLayer;
    /* 0x4C */ NoteAttributesE3C attributes;
    /* 0x5C */ AdsrE3C adsr;
    /* 0x74 */ u8 unk74[0xB4 - 0x74];
    /* 0xB4 */ u8 noteSubEuEnabled : 1;
    /* 0xB4 */ u8 noteSubEuNeedsInit : 1;
    /* 0xB4 */ u8 noteSubEuFinished : 1;
    /* 0xB4 */ u8 noteSubEuRest : 5;
} NoteE3C;

extern f32 D_811858D4;
extern f32 D_811858D8;
void AudioPlayback_AudioListRemove(s8*);
void AudioPlayback_AudioListPushFront(M2C_UNK* arg0, M2C_UNK* arg1);

/**
 * Starts the decay (6) or release (7) of the note a sequence layer is playing. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_SeqLayerDecayRelease(LayerE3C* layer, s32 target) {
    NoteE3C* note;
    NoteAttributesE3C* attrs;

    if (layer == (LayerE3C*)-1) {
        return;
    }

    layer->status = 0;

    if (layer->note == NULL) {
        return;
    }

    note = layer->note;
    attrs = &note->attributes;

    if (note->wantedParentLayer == layer) {
        note->wantedParentLayer = (LayerE3C*)-1;
    }

    if (note->parentLayer != layer) {
        if (note->parentLayer == (LayerE3C*)-1 && note->wantedParentLayer == (LayerE3C*)-1 &&
            note->prevParentLayer == layer && target != 6) {
            note->adsr.fadeOutVel = D_811858D4;
            note->adsr.action |= ADSR_ACTION_RELEASE_E3C;
        }
        return;
    }

    if (note->adsr.state != 6) {
        attrs->freqScale = layer->noteFreqScale;
        attrs->velocity = layer->noteVelocity;
        attrs->pan = layer->notePan;
        attrs->stereo = layer->stereo;
        if (layer->channel != NULL) {
            attrs->reverb = layer->channel->reverb;
            attrs->gain = layer->channel->gain;
            attrs->filter = layer->channel->filter;
            if (layer->channel->seqPlayer->muted && (layer->channel->muteBehavior & 8)) {
                note->noteSubEuFinished = 1;
            }
            note->priority = layer->channel->someOtherPriority;
        } else {
            note->priority = 1;
        }

        note->prevParentLayer = note->parentLayer;
        note->parentLayer = (LayerE3C*)-1;
        if (target == 7) {
            note->adsr.fadeOutVel = D_811858D4;
            note->adsr.action |= ADSR_ACTION_RELEASE_E3C;
            note->unk_04 = 2;
        } else {
            note->unk_04 = 1;
            note->adsr.action |= ADSR_ACTION_DECAY_E3C;
            if (layer->decayIndex == 0) {
                note->adsr.fadeOutVel = layer->channel->decayIndex * D_811858D8;
            } else {
                note->adsr.fadeOutVel = layer->decayIndex * D_811858D8;
            }
            note->adsr.sustain = ((f32)(s32)layer->channel->sustain * note->adsr.current) / 256.0f;
        }
    }

    if (target == 6) {
        AudioPlayback_AudioListRemove((s8*)note);
        AudioPlayback_AudioListPushFront((M2C_UNK*)(note->pool + 0x10), (M2C_UNK*)note);
    }
}

/**
 * Starts the decay of the layer's note. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_SeqLayerNoteDecay(Particle* arg0) {
    AudioPlayback_SeqLayerDecayRelease((struct LayerE3C*)arg0, 6);
}

/**
 * Starts the release of the layer's note. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_SeqLayerNoteRelease(Particle* arg0) {
    AudioPlayback_SeqLayerDecayRelease((struct LayerE3C*)arg0, 7);
}

/**
 * Makes an empty circular note list. Zelda 64 audio driver.
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

/* Same 0xCC-byte record array as AudioHeap_DiscardFont (gb_tower_emulator_86920.c); only the fields used here are named. */
typedef struct Rec81111130 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 pad04[4];
    /* 0x08 */ struct Rec81111130* unk_08;
    /* 0x0C */ u8 pad0C[0xCC - 0xC];
} Rec81111130; // size = 0xCC

s32 AudioSeq_AudioListPushBack(s8*, Rec81111130*);
extern Rec81111130* D_81184664;
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
 * @unverified Name guessed from the code; comment kept.
 */
void AudioPlayback_InitNoteFreeList(void) {
    s32 i;

    AudioPlayback_InitNoteLists(&D_81184938);
    for (i = 0; i < D_811858E8; i++) {
        D_81184664[i].unk_08 = &D_81184664[i];
        D_81184664[i].unk_00 = 0;
        AudioSeq_AudioListPushBack(&D_81184938, &D_81184664[i]);
    }
}

typedef struct ListItem811111E0 {
    /* 0x00 */ struct ListItem811111E0* prev;
    /* 0x04 */ struct ListItem811111E0* next;
    /* 0x08 */ void* u;
    /* 0x0C */ void* pool;
} ListItem811111E0; // size = 0x10

typedef struct NotePool811111E0 {
    /* 0x00 */ ListItem811111E0 disabled;
    /* 0x10 */ ListItem811111E0 decaying;
    /* 0x20 */ ListItem811111E0 releasing;
    /* 0x30 */ ListItem811111E0 active;
} NotePool811111E0;

extern s8 D_81184948;
extern s8 D_81184958;
extern s8 D_81184968;
void AudioPlayback_AudioListRemove(s8*);

/**
 * Moves every note in the four lists of a note pool back to the matching
 * global free list (D_81184938, D_81184948, D_81184958, D_81184968). Same
 * structure as note_pool_clear in the Super Mario 64 audio library.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioPlayback_NotePoolClear(NotePool811111E0* pool) {
    s32 i;
    ListItem811111E0* source;
    ListItem811111E0* cur;
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
            AudioSeq_AudioListPushBack(dest, (Rec81111130*)cur);
        }
    }
}

s32 AudioSeq_AudioListPopBack(s8 *);
/**
 * Takes `arg1` notes from the global free lists into a pool. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NotePoolFill(s8* arg0, s32 arg1) {
    s32 pad[3]; /* places src/dst at sp+0x48/0x44 and the frame at 0x58 as in the ROM */
    s8* src;
    s8* dst;
    s32 n;
    s32 pass;
    s32 r;

    AudioPlayback_NotePoolClear((NotePool811111E0*)arg0);
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
            AudioSeq_AudioListPushBack(dst, (Rec81111130*)r);
            n++;
        }
    }
}

/**
 * Pushes list item `arg1` onto the front of list `arg0` if it is on no list. Zelda 64 audio driver.
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

typedef struct Flags81111568 {
    /* 0x0 */ u32 pad0 : 6;
    /* 0x0 */ u32 flag : 1;
    /* 0x0 */ u32 pad0b : 1;
    /* 0x1 */ u8 mode : 3;
    /* 0x1 */ u8 pad1 : 2;
    /* 0x1 */ u8 range : 2;
    /* 0x1 */ u8 pad1b : 1;
    /* 0x2 */ char pad2[0xE];
    /* 0x10 */ s32 unk10;
} Flags81111568;
typedef struct Src81111568 {
    /* 0x0 */ u32 pad : 5;
    /* 0x0 */ u32 flag : 1;
    /* 0x0 */ u32 rest : 26;
} Src81111568;
typedef struct Bit81111568 { u8 pad : 5; u8 b : 1; u8 rest : 2; } Bit81111568;
/**
 * Gives note `arg0` to layer `arg1` and sets it up from the layer's instrument. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteInitForLayer(s8* arg0, s8* arg1) {
    Flags81111568* flags;
    s32 v;

    M2C_FIELD(arg0, s32*, 0x40) = -1;
    M2C_FIELD(arg0, s8**, 0x44) = arg1;
    M2C_FIELD(arg0, u8*, 0x30) = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x54), u8*, 5);
    ((Bit81111568*)arg1)->b = 1;
    M2C_FIELD(arg1, u8*, 3) = 3;
    M2C_FIELD(arg1, s8**, 0x48) = arg0;
    M2C_FIELD(M2C_FIELD(arg1, s8**, 0x54), s8**, 0x40) = arg0;
    M2C_FIELD(M2C_FIELD(arg1, s8**, 0x54), s8**, 0x44) = arg1;
    M2C_FIELD(arg1, f32*, 0x34) = 0.0f;
    AudioPlayback_NoteInit((Obj0694*)arg0);
    v = M2C_FIELD(arg1, u8*, 2);
    flags = (Flags81111568*)(arg0 + 0xB4);
    if (v == 0xFF) {
        v = M2C_FIELD(M2C_FIELD(arg1, s8**, 0x54), s16*, 0x22);
    }
    flags->unk10 = M2C_FIELD(arg1, s32*, 0x50);
    if (v >= 0x80 && v < 0xC0) {
        flags->range = 1;
    } else {
        flags->range = 0;
    }
    M2C_FIELD(arg0, u8*, 0x33) = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x54), u8*, 7);
    flags->flag = M2C_FIELD(arg1, Src81111568**, 0x54)->flag;
    flags->mode = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x54), u8*, 8) & 3;
}


/**
 * Releases the note's current layer and queues layer `arg1` to take it over. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteReleaseOwnerAndQueueLayer(s8 *arg0, s32 arg1) {
    AudioPlayback_SeqLayerNoteRelease(M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
}

extern f32 D_FLT_811858D4;
/**
 * Starts releasing the note and hands it to layer `arg1` with the layer's priority. Zelda 64 audio driver.
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
s32 AudioSeq_AudioListPopBack(s8 *);
void AudioPlayback_NoteInitForLayer(s8*, s8*);

/**
 * Allocates a note for a layer from a pool's disabled list. Zelda 64 audio driver.
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
 * arg0 + 0x10, initialises it with AudioPlayback_NoteReleaseAndTakeOwnership(entry, arg1), and inserts
 * it at the front of the list headed at arg0 + 0x20 with AudioSeq_AudioListPushBack.
 * List heads are {next, prev, count, owner} blocks (see AudioPlayback_InitNoteList).
 *
 * AudioSeq_AudioListPopBack unlinks the first node of the list at arg0 + 0x10 and
 * returns the word at offset 8 of that node, or 0 if the list is empty.
 * Returns that entry, or 0 if there was none; nothing else happens then.
 */
s32 AudioSeq_AudioListPopBack(s8 *);

/**
 * Takes over a decaying note for a layer. Zelda 64 audio driver.
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
    AudioSeq_AudioListPushBack(arg0 + 0x20, (Rec81111130 *) b);
    *((u8 *) (((s8 *) b) + 0x30)) = *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    return b;
  }
  *((s8 **) (((s8 *) a) + 0x48)) = arg1;
  *((u8 *) (((s8 *) a) + 0x30)) = *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  return a;
}

/**
 * Allocates a note for a layer by its channel's note-stealing policy. Zelda 64 audio driver.
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
            AudioSeq_AudioListPushBack(M2C_FIELD(voice, s8**, 0xC) + 0x20, (Rec81111130*)voice);
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

typedef struct Rec81111AF4 {
    /* 0x00 */ char pad00[0x1C];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ char pad20[0x10];
    /* 0x30 */ s8 unk_30;
    /* 0x31 */ s8 unk_31;
    /* 0x32 */ char pad32[2];
    /* 0x34 */ s8 unk_34;
    /* 0x35 */ char pad35;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ char pad38[8];
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ char pad4C[8];
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ char pad58[4];
    /* 0x5C */ s8 unk_5C;
    /* 0x5D */ s8 unk_5D;
    /* 0x5E */ char pad5E[0x84 - 0x5E];
    /* 0x84 */ f32 unk_84;
    /* 0x88 */ f32 unk_88;
    /* 0x8C */ char pad8C[0xA4 - 0x8C];
    /* 0xA4 */ s8 unk_A4;
    /* 0xA5 */ char padA5[0xB4 - 0xA5];
    /* 0xB4 */ Copy18 unk_B4;
    /* 0xCC */
} Rec81111AF4; // size = 0xCC
extern Copy18 D_811369A8;
extern s8 D_811842C0;
s32 func_81109868(s8 *, s32);
/**
 * Resets every note's state and sample buffers. Zelda 64 audio driver.
 * @unverified Name and comment guessed from the code.
 */
void AudioPlayback_NoteInitAll(void) {
    s32 i;
    Rec81111AF4* rec;

    for (i = 0; i < D_811858E8; i++) {
        rec = (Rec81111AF4*)&D_81184664[i];
        rec->unk_B4 = D_811369A8;
        rec->unk_30 = 0;
        rec->unk_34 = 0;
        rec->unk_44 = -1;
        rec->unk_48 = -1;
        rec->unk_40 = -1;
        rec->unk_31 = 0;
        rec->unk_54 = 0.0f;
        rec->unk_36 = 0;
        rec->unk_5D = 0;
        rec->unk_5C = 0;
        rec->unk_A4 = 0;
        rec->unk_84 = 0.0f;
        rec->unk_88 = 0.0f;
        rec->unk_1C = func_81109868(&D_811842C0, 0x80);
    }
}
