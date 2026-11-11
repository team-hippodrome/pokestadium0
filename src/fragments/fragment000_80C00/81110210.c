/* Stadium Zero fragment000_80C00. */

#include "global.h"
#include "fragments/particle_math/particle_math.h"
#include "m2c_macros.h"
struct LayerE3C;
void func_81110E3C(struct LayerE3C*, s32);

void func_811105DC(s8* arg0, f32 arg1);

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

void func_81110210(s8* note, ReverbInfo81110210* reverbInfo) {
    NoteSub81110210* sub;
    f32 volRight;
    f32 volLeft;
    s32 smallPanIndex;
    UNUSED u32 pad;
    UNUSED u32 pad1;
    u8 strongRight;
    u8 strongLeft;
    f32 velocity;
    u8 pan;
    u8 reverbVol;
    ReverbBits81110210 reverbBits;

    func_811105DC(note, reverbInfo->freqScale);
    velocity = reverbInfo->velocity;
    pan = reverbInfo->pan;
    reverbVol = reverbInfo->reverbVol;
    reverbBits = reverbInfo->reverbBits;
    sub = (NoteSub81110210*)(note + 0xB4);
    pan &= 0x7F;

    if (sub->stereoHeadsetEffects && D_811858EE == 1) {
        smallPanIndex = pan >> 1;
        if (smallPanIndex > 0x3F) {
            smallPanIndex = 0x3F;
        }
        sub->headsetPanLeft = D_811369D8[smallPanIndex];
        sub->headsetPanRight = D_811369D8[0x3F - smallPanIndex];
        sub->stereoStrongRight = 0;
        sub->stereoStrongLeft = 0;
        sub->usesHeadsetPanEffects = 1;
        volLeft = D_81136AD8[pan];
        volRight = D_81136AD8[0x7F - pan];
    } else if (sub->stereoHeadsetEffects && D_811858EE == 0) {
        strongLeft = strongRight = 0;
        sub->headsetPanRight = 0;
        sub->headsetPanLeft = 0;
        sub->usesHeadsetPanEffects = 0;
        volLeft = D_81136CD8[pan];
        volRight = D_81136CD8[0x7F - pan];
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
        volLeft = 0.707f;
        volRight = 0.707f;
    } else {
        volLeft = D_81136ED8[pan];
        volRight = D_81136ED8[0x7F - pan];
    }

    if (velocity < 0.0f) {
        velocity = 0.0f;
    }
    if (velocity > 1.0f) {
        velocity = 1.0f;
    }

    sub->targetVolLeft = (s32)(velocity * volLeft * 4095.999f);
    sub->targetVolRight = (s32)(velocity * volRight * 4095.999f);
    sub->bankId = reverbInfo->bankId;
    sub->synthesisVolume = reverbInfo->synthesisVolume;

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

void func_811105DC(s8* arg0, f32 arg1) {
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

void func_81110694(Obj0694* arg0) {
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

void func_8111073C(Note8111073C* note) {
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
void func_811110B0(Particle* arg0);
void func_811114BC(s8*);
void func_8111147C(M2C_UNK* arg0, M2C_UNK* arg1);
s32 func_81112EAC(s8*, struct Rec81111130*);
void func_81111568(s8* arg0, s8* arg1);
void func_81112B84(Channel81110798*);
void func_81112278(Note81110798*);
f32 func_81112380(u8*);
void func_8111220C(Note81110798*);

void func_81110798(void)
{
  Note81110798 *note;
  PlaybackState81110798 *playbackState;
  NoteSubEu81110798 *noteSubEu;
  NoteAttributes81110798 *attrs;
  s32 pad[2]; // FAKE
  ReverbInfo81110210 subAttrs;
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
        if (((!playbackState->parentLayer->enabled) && (playbackState->unk_04 == 0)) && ((playbackState->priority >= 1) ^ 0))
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
      func_811110B0((Particle *) playbackState->parentLayer);
      func_811114BC((s8 *) note);
      func_8111147C((M2C_UNK *) (note->pool + 0x10), (M2C_UNK *) note);
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
            func_8111073C((Note8111073C *) note);
            if (playbackState->wantedParentLayer->channel != 0)
            {
              func_81111568((s8 *) note, (s8 *) playbackState->wantedParentLayer);
              func_81112278(note);
              func_811114BC((s8 *) note);
              func_81112EAC(note->pool + 0x30, (struct Rec81111130 *) note);
              playbackState->wantedParentLayer = (Layer81110798 *) (-1);
              goto process;
            }
            func_8111073C((Note8111073C *) note);
            func_811114BC((s8 *) note);
            func_81112EAC(note->pool, (struct Rec81111130 *) note);
            playbackState->wantedParentLayer = (Layer81110798 *) (-1);
          }
          else
          {
            if (playbackState->parentLayer != ((Layer81110798 *) (-1)))
            {
              playbackState->parentLayer->bit1 = 1;
            }
            func_8111073C((Note8111073C *) note);
            func_811114BC((s8 *) note);
            func_81112EAC(note->pool, (struct Rec81111130 *) note);
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
        func_8111073C((Note8111073C *) note);
        func_811114BC((s8 *) note);
        func_81112EAC(note->pool, (struct Rec81111130 *) note);
      }
      else
      {
        process:
        attrs = &playbackState->attributes;

        scale = func_81112380((u8 *) (&playbackState->adsr));
        func_8111220C(note);
        if ((playbackState->unk_04 == 1) || (playbackState->unk_04 == 2))
        {
          subAttrs.freqScale = attrs->freqScale;
          subAttrs.velocity = attrs->velocity;
          subAttrs.pan = attrs->pan;
          subAttrs.reverbVol = attrs->reverbVol;
          subAttrs.reverbBits = attrs->reverbBits;
          subAttrs.bankId = attrs->bankId;
          subAttrs.synthesisVolume = attrs->unk0C;
          bookOffset = noteSubEu->bookOffset;
        }
        else
        {
          Channel81110798 *channel = playbackState->parentLayer->channel;
          Layer81110798 *layer = playbackState->parentLayer;
          subAttrs.freqScale = layer->noteFreqScale;
          subAttrs.velocity = layer->noteVelocity;
          subAttrs.pan = layer->notePan;
          subAttrs.reverbBits = layer->stereo;
          subAttrs.reverbVol = channel->reverb;
          subAttrs.bankId = channel->gain;
          subAttrs.synthesisVolume = channel->filter;
          bookOffset = channel->bookOffset & 7;
          if (channel->seqPlayer->muted && (channel->muteBehavior & 8))
          {
            subAttrs.freqScale = 0.0f;
            subAttrs.velocity = 0.0f;
          }
        }
        subAttrs.freqScale *= playbackState->vibratoFreqScale * playbackState->portamentoFreqScale;
        subAttrs.freqScale *= D_811858D0;
        subAttrs.velocity *= scale;
        func_81110210((s8 *) note, &subAttrs);
        noteSubEu->bookOffset = bookOffset;
      }
    }

  }

}

u8* func_81110C6C(u8* arg0, s32 arg1) {
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

s32 func_8110CA2C(s32 arg0);
extern ParticleBank81110CA8* D_811858B0;
extern s32 D_811859D0;

u8* func_81110CA8(s32 arg0, s32 arg1) {
    ParticleBank81110CA8* bank;
    u8* ret;

    if (func_8110CA2C(arg0) == 0) {
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

u8* func_81110D6C(s32 arg0, s32 arg1) {
    ParticleBank81110CA8* bank;
    u8* ret;

    if (func_8110CA2C(arg0) == 0) {
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
void func_811114BC(s8*);
void func_8111147C(M2C_UNK* arg0, M2C_UNK* arg1);

void func_81110E3C(LayerE3C* layer, s32 target) {
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
        func_811114BC((s8*)note);
        func_8111147C((M2C_UNK*)(note->pool + 0x10), (M2C_UNK*)note);
    }
}

void func_81111090(Particle* arg0) {
    func_81110E3C((struct LayerE3C*)arg0, 6);
}

void func_811110B0(Particle* arg0) {
    func_81110E3C((struct LayerE3C*)arg0, 7);
}

void func_811110D0(s8 *arg0) {
    M2C_FIELD(arg0, s8 **, 0) = arg0;
    M2C_FIELD(arg0, s8 **, 4) = arg0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

/*
 * func_811110E0
 *
 * Calls func_811110D0 on four 16-byte blocks at arg0 + 0x00, 0x10, 0x20 and
 * 0x30.  func_811110D0 stores the block's own address in its first two words
 * and clears the third, giving an empty circular list head {next, prev,
 * count, owner}: func_8111147C and func_81112EAC, which insert into such a
 * list, link through the first two words, increment the third and copy the
 * fourth into the inserted node.  Afterwards arg0 itself is stored in the
 * fourth word (offset 0xC) of each block.
 */
void func_811110E0(s8 *arg0) {
    func_811110D0(arg0);
    func_811110D0(arg0 + 0x10);
    func_811110D0(arg0 + 0x20);
    func_811110D0(arg0 + 0x30);
    M2C_FIELD(arg0, s8 **, 0xC) = arg0;
    M2C_FIELD(arg0, s8 **, 0x1C) = arg0;
    M2C_FIELD(arg0, s8 **, 0x2C) = arg0;
    M2C_FIELD(arg0, s8 **, 0x3C) = arg0;
}

/* Same 0xCC-byte record array as func_81109678 (gb_tower_emulator_86920.c); only the fields used here are named. */
typedef struct Rec81111130 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 pad04[4];
    /* 0x08 */ struct Rec81111130* unk_08;
    /* 0x0C */ u8 pad0C[0xCC - 0xC];
} Rec81111130; // size = 0xCC

s32 func_81112EAC(s8*, Rec81111130*);
extern Rec81111130* D_81184664;
extern s8 D_81184938;
extern s32 D_811858E8;

/*
 * func_81111130
 *
 * Calls func_811110E0(&D_81184938), then for each of the D_811858E8 records of
 * the array at D_81184664 (0xCC bytes each, indexed directly each time):
 * stores the record's own address at offset 8, clears the word at offset 0,
 * and calls func_81112EAC(&D_81184938, record). func_81109678, which walks the
 * same array, passes the same list argument to the same function. What the
 * records are is not established from this function.
 */
void func_81111130(void) {
    s32 i;

    func_811110E0(&D_81184938);
    for (i = 0; i < D_811858E8; i++) {
        D_81184664[i].unk_08 = &D_81184664[i];
        D_81184664[i].unk_00 = 0;
        func_81112EAC(&D_81184938, &D_81184664[i]);
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
void func_811114BC(s8*);

/**
 * Moves every note in the four lists of a note pool back to the matching
 * global free list (D_81184938, D_81184948, D_81184958, D_81184968). Same
 * structure as note_pool_clear in the Super Mario 64 audio library.
 */
void func_811111E0(NotePool811111E0* pool) {
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
            func_811114BC((s8*)cur);
            func_81112EAC(dest, (Rec81111130*)cur);
        }
    }
}

s32 func_81112EEC(s8 *);
void func_81111340(s8* arg0, s32 arg1) {
    s32 pad[3]; /* places src/dst at sp+0x48/0x44 and the frame at 0x58 as in the ROM */
    s8* src;
    s8* dst;
    s32 n;
    s32 pass;
    s32 r;

    func_811111E0((NotePool811111E0*)arg0);
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
            r = func_81112EEC(src);
            if (r == 0) {
                break;
            }
            func_81112EAC(dst, (Rec81111130*)r);
            n++;
        }
    }
}

void func_8111147C(M2C_UNK *arg0, M2C_UNK *arg1) {
    if (M2C_FIELD(arg1, M2C_UNK **, 0) == NULL) {
        M2C_FIELD(arg1, M2C_UNK **, 0) = arg0;
        M2C_FIELD(arg1, M2C_UNK **, 4) = (M2C_UNK *) M2C_FIELD(arg0, M2C_UNK **, 4);
        *M2C_FIELD(arg0, M2C_UNK **, 4) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = arg1;
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + 1);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    }
}

void func_811114BC(s8 *arg0) {
    s8 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s8 ***, 4) = (s8 **) M2C_FIELD(arg0, s8 ***, 4);
        *M2C_FIELD(arg0, s8 ***, 4) = M2C_FIELD(arg0, s8 **, 0);
        M2C_FIELD(arg0, s8 **, 0) = NULL;
    }
}

s8 *func_811114E8(s8 *arg0, s32 arg1) {
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
void func_81111568(s8* arg0, s8* arg1) {
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
    func_81110694((Obj0694*)arg0);
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


void func_81111688(s8 *arg0, s32 arg1) {
    func_811110B0(M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
}

extern f32 D_FLT_811858D4;
void func_811116BC(s8 *arg0, s8 *arg1)
{
  *((s8 **) (((s8 *) arg0) + 0x48)) = arg1;
  *((u8 *) (((s8 *) arg0) + 0x30)) = (u8) (*((u8 *) (((s8 *) (*((s8 **) (((s8 *) arg1) + 0x54)))) + 5)));
  *((f32 *) (((s8 *) arg0) + 0x6C)) = (f32) D_FLT_811858D4;
  *((u8 *) (((s8 *) arg0) + 0x5C)) = (u8) ((*((u8 *) (((s8 *) arg0) + 0x5C))) | 0x10);
}

/*
 * func_811116E8
 *
 * Moves one entry from the list headed at arg0 to the list headed at
 * arg0 + 0x30.  The list heads are 16-byte blocks laid out as
 * {next, prev, count, owner}, as set up by func_811110D0 and func_811110E0.
 *
 *   1. func_81112EEC(arg0) unlinks the first node of the list at arg0 and
 *      returns the word stored at offset 8 of that node (0 if the list is
 *      empty).  That value is the entry used below and the return value.
 *   2. If it is not 0, func_81111568(entry, arg1) is called on it, and
 *      func_8111147C then appends the entry to the list at arg0 + 0x30
 *      (it does nothing if the entry's first word is already non-zero).
 *
 * Returns the entry, or 0 if there was none.  What func_81111568 does with
 * arg1 is not established (it is still assembly).
 */
s32 func_81112EEC(s8 *);
void func_81111568(s8*, s8*);

s32 func_811116E8(s8 *arg0, s32 arg1) {
    s32 ret;

    ret = func_81112EEC(arg0);
    if (ret != 0) {
        func_81111568((s8*)ret, (s8*)arg1);
        func_8111147C((M2C_UNK *) (arg0 + 0x30), (M2C_UNK *) ret);
    }
    return ret;
}

/*
 * func_81111734
 *
 * Like func_811116E8, but it takes the entry from the list headed at
 * arg0 + 0x10, initialises it with func_811116BC(entry, arg1), and inserts
 * it at the front of the list headed at arg0 + 0x20 with func_81112EAC.
 * List heads are {next, prev, count, owner} blocks (see func_811110D0).
 *
 * func_81112EEC unlinks the first node of the list at arg0 + 0x10 and
 * returns the word at offset 8 of that node, or 0 if the list is empty.
 * Returns that entry, or 0 if there was none; nothing else happens then.
 */
s32 func_81112EEC(s8 *);

s32 func_81111734(s8 *arg0, s8 *arg1) {
    s32 ret;

    ret = func_81112EEC(arg0 + 0x10);
    if (ret != 0) {
        func_811116BC((s8 *) ret, arg1);
        func_81112EAC(arg0 + 0x20, (s8 *) ret);
    }
    return ret;
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s8 *func_81111784(s8 *arg0, s8 *arg1)
{
  s8 *a;
  s8 *b;
  s32 prioA;
  s32 prioB;
  prioA = (prioB = 0x10);
  a = func_811114E8(arg0 + 0x20, *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5)));
  if (a != 0)
  {
    prioA = *((u8 *) (((s8 *) a) + 0x30));
  }
  b = func_811114E8(arg0 + 0x30, *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5)));
  if (b != 0)
  {
    prioB = *((u8 *) (((s8 *) b) + 0x30));
  }
  if ((a == 0) && (b == 0))
  {
    return 0;
  }
  if (prioB < (prioA ^ 0))
  {
    func_811114BC(b);
    func_81111688(b, (s32) arg1);
    func_81112EAC(arg0 + 0x20, (Rec81111130 *) b);
    *((u8 *) (((s8 *) b) + 0x30)) = *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5));
    return b;
  }
  *((s8 **) (((s8 *) a) + 0x48)) = arg1;
  *((u8 *) (((s8 *) a) + 0x30)) = *((u8 *) (((s8 *) (*((u8 **) (((s8 *) arg1) + 0x54)))) + 5));
  return a;
}

s8* func_8111187C(s8* arg0) {
    s8* voice;
    s32 flags = M2C_FIELD(arg0, u8**, 0x54)[2];

    if (flags & 1) {
        voice = M2C_FIELD(arg0, s8**, 0x48);
        if ((voice != NULL) && (arg0 == M2C_FIELD(voice, s8**, 0x40)) && (M2C_FIELD(voice, s32*, 0x48) == -1)) {
            func_811116BC(voice, arg0);
            func_811114BC(voice);
            func_81112EAC(M2C_FIELD(voice, s8**, 0xC) + 0x20, (Rec81111130*)voice);
            return voice;
        }
    }
    if (flags & 2) {
        if (((voice = (s8*)func_811116E8(M2C_FIELD(arg0, s8**, 0x54) + 0x84, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = func_81111784(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL)) {
            return voice;
        }
    } else if (flags & 4) {
        if (((voice = (s8*)func_811116E8(M2C_FIELD(arg0, s8**, 0x54) + 0x84, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_811116E8(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x54), s8**, 0x4C) + 0x98, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x54), s8**, 0x4C) + 0x98, arg0)) != NULL) ||
            ((voice = func_81111784(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = func_81111784(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x54), s8**, 0x4C) + 0x98, arg0)) != NULL)) {
            return voice;
        }
    } else if (flags & 8) {
        if (((voice = (s8*)func_811116E8(&D_81184938, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(&D_81184938, arg0)) != NULL) ||
            ((voice = func_81111784(&D_81184938, arg0)) != NULL)) {
            return voice;
        }
    } else {
        if (((voice = (s8*)func_811116E8(M2C_FIELD(arg0, s8**, 0x54) + 0x84, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_811116E8(&D_81184938, (s32)arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = (s8*)func_81111734(&D_81184938, arg0)) != NULL) ||
            ((voice = func_81111784(M2C_FIELD(arg0, s8**, 0x54) + 0x84, arg0)) != NULL) ||
            ((voice = func_81111784(&D_81184938, arg0)) != NULL)) {
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
void func_81111AF4(void) {
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
