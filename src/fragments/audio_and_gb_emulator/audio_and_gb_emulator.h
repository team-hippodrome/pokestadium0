/* Declarations for the audio_and_gb_emulator fragment (src/fragments/audio_and_gb_emulator/). */
#ifndef FRAGMENT_AUDIO_AND_GB_EMULATOR_H
#define FRAGMENT_AUDIO_AND_GB_EMULATOR_H

#include "global.h"
#include "m2c_macros.h"

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_7F9A0.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_7F9A0_81102C20.c
 */

typedef struct unk_D_8122C4FA {
  /* 0x00 */ u8 unk_00;
  /* 0x01 */ u8 unk_01;
} unk_D_8122C4FA;

typedef struct unk_D_8122B2F8 {
  /* 0x000000 */ char unk000000[0x1FEAE8];
} unk_D_8122B2F8;

typedef struct unk_D_8122B1E8 {
  /* 0x00 */ OSMesg mesg[1];
  /* 0x04 */ OSMesgQueue queue;
  /* 0x1C */ char unk1C[0x4];
  /* 0x20 */ s32 unk_20;
  /* 0x24 */ s32 unk_24;
  /* 0x28 */ void* unk_28;
  /* 0x2C */ s32 unk_2C;
  /* 0x30 */ char unk30[0x8];
  /* 0x38 */ s32 unk_38;
  /* 0x3C */ s32 unk_3C;
  /* 0x40 */ void* unk_40;
  /* 0x44 */ char unk44[0x4];
  /* 0x48 */ void* unk_48;
  /* 0x4C */ void* unk_4C;
  /* 0x50 */ u32 unk_50;
  /* 0x54 */ s32 unk_54;
  /* 0x58 */ void* unk_58;
  /* 0x5C */ s32 unk_5C;
  /* 0x60 */ char unk60[0x8];
} unk_D_8122B1E8;

typedef struct unk_D_8120D7F3 {
    u8 pad[0x116];
    u8 unk116;
} unk_D_8120D7F3;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_86920.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_86920_8110B880.c
 */

/* A bump allocator over one region of the audio heap. */
typedef struct AudioAllocPool {
  /* 0x00 */ u8* startRamAddr; // @unverified: same offset/use as OoT's AudioAllocPool.startRamAddr (AudioHeap_InitPool)
  /* 0x04 */ u8* curRamAddr; // @unverified: same offset/use as OoT's AudioAllocPool.curRamAddr (bumped by each alloc)
  /* 0x08 */ s32 size; // @unverified: same offset/use as OoT's AudioAllocPool.size
  /* 0x0C */ s32 numEntries; // @unverified: same offset/use as OoT's AudioAllocPool.numEntries (counts allocations)
} AudioAllocPool; // size = 0x10

typedef struct unk_D_812346E0 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} unk_D_812346E0;

typedef struct unk_D_81231450 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_81231450;

typedef struct unk_D_81234650 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_81234650;

typedef struct SeqLayerFlags81109678 {
    /* 0x0 */ u8 enabled : 1; // @unverified: same use as OoT's SequenceLayer.enabled (AudioHeap_DiscardFont)
    /* 0x0 */ u8 finished : 1; // @unverified: same use as OoT's SequenceLayer.finished (AudioHeap_DiscardFont)
    /* 0x0 */ u8 rest : 6;
} SeqLayerFlags81109678;

typedef struct Note81109678 {
    /* 0x00 */ u8 pad00[0x30];
    /* 0x30 */ u8 priority; // @unverified: same offset/use as OoT's Note.playbackState.priority (AudioHeap_DiscardFont)
    /* 0x31 */ u8 pad31[2];
    /* 0x33 */ u8 fontId; // @unverified: same offset/use as OoT's Note.playbackState.fontId (compared with the font being discarded)
    /* 0x34 */ u8 unk_34;
    /* 0x35 */ u8 pad35[0x44 - 0x35];
    /* 0x44 */ SeqLayerFlags81109678* parentLayer; // @unverified: same offset/use as OoT's Note.playbackState.parentLayer
    /* 0x48 */ u8 pad48[0x5C - 0x48];
    /* 0x5C */ u8 adsrAction; // @unverified: same offset/use as OoT's Note.playbackState.adsr.action (0x10 = release)
    /* 0x5D */ u8 adsrState; // @unverified: same offset/use as OoT's Note.playbackState.adsr.action.s.state
    /* 0x5E */ u8 pad5E[0x6C - 0x5E];
    /* 0x6C */ f32 adsrFadeOutVel; // @unverified: same offset/use as OoT's Note.playbackState.adsr.fadeOutVel
    /* 0x70 */ u8 pad70[0xB4 - 0x70];
    /* 0xB4 */ u32 enabled : 1; // @unverified: same offset/use as OoT's Note.sampleState.bitField0.enabled
    /* 0xB4 */ u32 restB4 : 31;
    /* 0xB8 */ u8 padB8[0xCC - 0xB8];
} Note81109678; // size = 0xCC

typedef struct AudioCacheEntry {
    /* 0x00 */ u8* ramAddr; // @unverified: same offset/use as OoT's AudioCacheEntry.addr
    /* 0x04 */ u32 size; // @unverified: same offset/use as OoT's AudioCacheEntry.size
    /* 0x08 */ s16 tableType; // @unverified: same offset/use as OoT's AudioCacheEntry.tableType (0 sequence, 1 font, 2 sample bank)
    /* 0x0A */ s16 id; // @unverified: same offset/use as OoT's AudioCacheEntry.id
} AudioCacheEntry; // size = 0xC

typedef struct AudioPersistentCache {
    /* 0x00 */ u32 numEntries;
    /* 0x04 */ AudioAllocPool pool;
    /* 0x14 */ AudioCacheEntry entries[1];
} AudioPersistentCache; // size = 0x20

typedef struct AudioTemporaryCache {
    /* 0x00 */ u32 nextSide;
    /* 0x04 */ AudioAllocPool pool;
    /* 0x14 */ AudioCacheEntry entries[2];
} AudioTemporaryCache; // size = 0x2C

/* A loaded font (D_811858B0[fontId]). */
typedef struct SoundFont {
    /* 0x00 */ u8 numInstruments; // @unverified: same offset/use as OoT's SoundFont.numInstruments (high byte of shortData2; instrument loop bound)
    /* 0x01 */ u8 numDrums; // @unverified: same offset/use as OoT's SoundFont.numDrums (low byte of shortData2; drum loop bound)
    /* 0x02 */ u8 sampleBankId1; // @unverified: same offset/use as OoT's SoundFont.sampleBankId1 (high byte of shortData1)
    /* 0x03 */ u8 sampleBankId2; // @unverified: same offset/use as OoT's SoundFont.sampleBankId2 (low byte of shortData1)
    /* 0x04 */ u8** instruments; // @unverified: same offset/use as OoT's SoundFont.instruments (AudioPlayback_GetInstrumentInner)
    /* 0x08 */ u8** drums; // @unverified: same offset/use as OoT's SoundFont.drums (AudioPlayback_GetDrum)
} SoundFont; // size = 0xC

/* One of the sequence, font and sample bank caches (D_81184320, D_81184380, D_811843E0; 0x60 apart). */
typedef struct AudioCache {
    /* 0x00 */ AudioPersistentCache persistent;
    /* 0x20 */ AudioTemporaryCache temporary;
} AudioCache;

/* The permanent pool and the entries allocated from it (D_81184440). */
typedef struct AudioPermanentCache {
    /* 0x00 */ AudioAllocPool pool; // @unverified: allocated from by AudioLoad's permanent alloc; pool.numEntries indexes the next entry (OoT's permanentPool)
    /* 0x10 */ AudioCacheEntry entries[1]; // @unverified: same use as OoT's AudioContext.permanentCache
} AudioPermanentCache;


typedef struct SeqPlayer81109C0C {
    /* 0x000 */ u32 enabled : 1;
    /* 0x000 */ u32 rest0 : 31;
    /* 0x004 */ u8 seqId;
    /* 0x005 */ u8 pad5[0x15C - 0x5];
} SeqPlayer81109C0C; // size = 0x15C

typedef struct CacheEntry8110A368 { s32 ramAddr; char pad4[6]; s16 id; } CacheEntry8110A368; // @unverified: same offset/use as OoT's AudioCacheEntry.id

typedef struct Cache8110A368 { u32 numEntries; char pad4[0x10]; CacheEntry8110A368 entries[1]; } Cache8110A368; // @unverified: persistent cache numEntries; for the temporary cache this word is nextSide

typedef struct Reverb8110AA50 {
    /* 0x000 */ char unk000[0xC];
    /* 0x00C */ u16 decayRatio; // @unverified: same offset/use as OoT's SynthesisReverb.decayRatio (AudioHeap_UpdateReverbs)
    /* 0x00E */ char unk00E[0x14A];
} Reverb8110AA50; // size = 0x158

typedef struct ReverbSettings {
    /* 0x00 */ u8 downsampleRate;
    /* 0x01 */ u8 windowSize;
    /* 0x02 */ u16 decayRatio;
    /* 0x04 */ u16 volume; // @unverified: copied to SynthesisReverb.volume (OoT's ReverbSettings.volume)
    /* 0x06 */ u16 leakRtl; // @unverified: copied to SynthesisReverb.leakRtl (OoT's ReverbSettings.leakRtl)
    /* 0x08 */ u16 leakLtr; // @unverified: copied to SynthesisReverb.leakLtr (OoT's ReverbSettings.leakLtr)
    /* 0x0A */ s8 mixReverbIndex; // @unverified: copied to SynthesisReverb.mixReverbIndex (OoT's ReverbSettings.unk_10)
    /* 0x0C */ u16 mixReverbStrength; // @unverified: copied to SynthesisReverb.mixReverbStrength (OoT's ReverbSettings.unk_12)
    /* 0x0E */ s16 lowPassFilterCutoffLeft;
    /* 0x10 */ s16 lowPassFilterCutoffRight;
} ReverbSettings; // size = 0x12

typedef struct AudioSpec {
    /* 0x00 */ u32 frequency;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 numNotes;
    /* 0x06 */ u8 numSequencePlayers;
    /* 0x07 */ u8 numReverbs;
    /* 0x08 */ ReverbSettings* reverbSettings;
    /* 0x0C */ u16 unk_0C;
    /* 0x10 */ s32 persistentSeqMem;
    /* 0x14 */ s32 persistentFontMem;
    /* 0x18 */ s32 persistentSampleMem;
    /* 0x1C */ s32 temporarySeqMem;
    /* 0x20 */ s32 temporaryFontMem;
    /* 0x24 */ s32 temporarySampleMem;
    /* 0x28 */ s32 persistentSampleCacheSize;
    /* 0x2C */ s32 temporarySampleCacheSize;
} AudioSpec; // size = 0x30

typedef struct LoopAFF0 {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u32 count;
} LoopAFF0;

typedef struct SampleAFF0 {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 unk_bit26 : 1;
    /* 0x00 */ u32 unk_bit25 : 1;
    /* 0x01 */ u32 size : 24;
    /* 0x04 */ s16* sampleAddr;
    /* 0x08 */ struct LoopAFF0* loop;
    /* 0x0C */ void* book;
} SampleAFF0; // size = 0x10

typedef struct ReverbRingBufferItem {
    /* 0x00 */ s16 numSamplesAfterDownsampling;
    /* 0x02 */ s16 chunkLen;
    /* 0x04 */ s16* toDownsampleLeft;
    /* 0x08 */ s16* toDownsampleRight;
    /* 0x0C */ u8 unk0C[8];
} ReverbRingBufferItem; // size = 0x14

typedef struct SynthesisReverb {
    /* 0x000 */ u8 resampleFlags;
    /* 0x001 */ u8 useReverb;
    /* 0x002 */ u8 framesToIgnore;
    /* 0x003 */ u8 curFrame;
    /* 0x004 */ u8 downsampleRate;
    /* 0x005 */ s8 mixReverbIndex; // @unverified: from the code: index of another reverb mixed in when != -1 (OoT's SynthesisReverb.unk_05)
    /* 0x006 */ u16 windowSize;
    /* 0x008 */ u16 mixReverbStrength; // @unverified: from the code: aMix gain of that mixed-in reverb (OoT's SynthesisReverb.unk_08)
    /* 0x00A */ u16 volume; // @unverified: same offset/use as OoT's SynthesisReverb.volume
    /* 0x00C */ u16 decayRatio;
    /* 0x00E */ s16 resampleRate; // @unverified: 0x8000 / downsampleRate, the aResample pitch (OoT's SynthesisReverb.unk_0E)
    /* 0x010 */ u16 leakRtl; // @unverified: same offset/use as OoT's SynthesisReverb.leakRtl
    /* 0x012 */ u16 leakLtr; // @unverified: same offset/use as OoT's SynthesisReverb.leakLtr
    /* 0x014 */ s32 nextRingBufPos;
    /* 0x018 */ s32 unk_18;
    /* 0x01C */ s32 bufSizePerChan;
    /* 0x020 */ s16* leftRingBuf;
    /* 0x024 */ s16* rightRingBuf;
    /* 0x028 */ void* resampleStateLeft; // @unverified: 0x20-byte aResample state, left (OoT's SynthesisReverb.unk_30)
    /* 0x02C */ void* resampleStateRight; // @unverified: 0x20-byte aResample state, right (OoT's SynthesisReverb.unk_34)
    /* 0x030 */ void* unk_30;
    /* 0x034 */ void* unk_34;
    /* 0x038 */ ReverbRingBufferItem items[2][5];
    /* 0x100 */ s16* filterLeft;
    /* 0x104 */ s16* filterRight;
    /* 0x108 */ s16* filterLeftState;
    /* 0x10C */ s16* filterRightState;
    /* 0x110 */ SampleAFF0* soundSample;
    /* 0x114 */ f32 soundTuning;
    /* 0x118 */ SampleAFF0 sample;
    /* 0x128 */ LoopAFF0 loop;
    /* 0x134 */ u8 unk134[0x158 - 0x134];
} SynthesisReverb; // size = 0x158

typedef struct AudioSessionPoolSplit {
    /* 0x00 */ s32 miscPoolSize;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 cachePoolSize;
} AudioSessionPoolSplit; // size = 0x10

typedef struct AudioCachePoolSplit {
    /* 0x00 */ s32 persistentCommonPoolSize; // @unverified: same offset/use as OoT's AudioCachePoolSplit.persistentCommonPoolSize
    /* 0x04 */ s32 temporaryCommonPoolSize; // @unverified: same offset/use as OoT's AudioCachePoolSplit.temporaryCommonPoolSize
} AudioCachePoolSplit; // size = 0x8

typedef struct AudioCommonPoolSplit {
    /* 0x00 */ s32 seqCacheSize; // @unverified: same offset/use as OoT's AudioCommonPoolSplit.seqCacheSize
    /* 0x04 */ s32 fontCacheSize; // @unverified: same offset/use as OoT's AudioCommonPoolSplit.fontCacheSize
    /* 0x08 */ s32 sampleBankCacheSize; // @unverified: same offset/use as OoT's AudioCommonPoolSplit.sampleBankCacheSize
} AudioCommonPoolSplit; // size = 0xC


typedef struct GbApuChannelState {
  /* 0x00 */ u8 enabled; // @unverified: from the code: channel on (the NR52 status bit); set on trigger, cleared at length/envelope end and on power-off
  /* 0x01 */ char unk01[0x3];
  /* 0x04 */ s32 retriggerTimer; // @unverified: from the code: wave channel only; set to 0x140 on trigger, the old note fades out while it counts down
  /* 0x08 */ union {
      u16 index; // @unverified: top half of the accumulator, passed to GbApu_GetWaveformSample
      s32 acc; // @unverified: the accumulator, advanced by step and masked to 21 bits
  } phase; // @unverified: from the code: waveform phase, a 21-bit accumulator whose top bits index the waveform
  /* 0x0C */ u32 step; // @unverified: from the code: phase increment per sample, from the frequency (GbApu_FreqToStep*) or the NR43 noise table
  /* 0x10 */ u16 frequency; // @unverified: from the code: the 11-bit NRx3/NRx4 frequency (noise: the NR43 shift); changed by the square 1 sweep
  /* 0x12 */ u16 unk_12;
  /* 0x14 */ s32 lengthTimer; // @unverified: from the code: length * 200 samples, counted down while lengthEnabled; 0 turns the channel off
  /* 0x18 */ s32 lengthEnabled; // @unverified: from the code: NRx4 bit 6 (counter/consecutive)
  /* 0x1C */ s32 length; // @unverified: from the code: 64 - NRx1 length (256 - NR31 for the wave channel)
  /* 0x20 */ u8 amplitude; // @unverified: from the code: target output level, from the envelope volume through a table
  /* 0x21 */ u8 initialVolume; // @unverified: from the code: NRx2 initial volume (NR32 output level for the wave channel)
  /* 0x22 */ char unk22[0x2];
  /* 0x24 */ u32 envelopeCounter; // @unverified: from the code: samples since the last envelope step
  /* 0x28 */ u32 envelopePeriod; // @unverified: from the code: NRx2 envelope sweep * 800 samples; 0 = envelope off
  /* 0x2C */ char unk2C[0x1];
  /* 0x2D */ u8 envelopeVolume; // @unverified: from the code: current envelope volume 0-15
  /* 0x2E */ u8 envelopeDir; // @unverified: from the code: NRx2 envelope direction (0 down, 1 up)
  /* 0x2F */ char unk2F[0x1];
  /* 0x30 */ u32 sweepCounter; // @unverified: from the code: square 1 only; samples since the last frequency sweep step
  /* 0x34 */ u32 sweepPeriod; // @unverified: from the code: square 1 only; NR10 sweep time * 400 samples
  /* 0x38 */ u8 sweepShift; // @unverified: from the code: square 1 only; NR10 sweep shift
  /* 0x39 */ u8 sweepDir; // @unverified: from the code: square 1 only; NR10 sweep direction (0 up, 1 down)
  /* 0x3A */ u8 sweepEnabled; // @unverified: from the code: square 1 only; set when sweepPeriod != 0
  /* 0x3B */ u8 duty; // @unverified: from the code: NRx1 duty (index of the square waveform)
  /* 0x3C */ u8 appliedAmplitude; // @unverified: from the code: amplitude actually multiplied into the sample; fades to 0 after the channel stops
  /* 0x3D */ char unk3D[0x3];
  /* 0x40 */ u32 appliedStep; // @unverified: from the code: step kept for the fade-out; the noise channel slews it toward step
  /* 0x44 */ u16 prevSample; // @unverified: from the code: wave channel only; last output, averaged with the next sample
  /* 0x46 */ u16 unk46;
  /* 0x48 */ u32 stepSlew; // @unverified: from the code: noise channel only; per-sample change of appliedStep, |step - appliedStep| >> 7
  /* 0x4C */ u8 outOfRange; // @unverified: from the code: 1 while the frequency is outside 1-0x7FE, the channel then fades out
  /* 0x4D */ char unk4D[0x3];
} GbApuChannelState;

typedef struct GbApuStatusOverride {
  /* 0x00 */ u8 square1; // @unverified: from the code (GbApu_QueueRegisterWrite, GbMem_ReadIoRegister): pending NR52 status of square 1: 0 none, 1 off, 2 triggered, until the queued write is rendered
  /* 0x01 */ u8 square2; // @unverified: from the code (GbApu_QueueRegisterWrite, GbMem_ReadIoRegister): same for square 2
  /* 0x02 */ u8 wave; // @unverified: from the code (GbApu_QueueRegisterWrite, GbMem_ReadIoRegister): same for the wave channel
  /* 0x03 */ u8 noise; // @unverified: from the code (GbApu_QueueRegisterWrite, GbMem_ReadIoRegister): same for the noise channel
} GbApuStatusOverride;

typedef struct GbApuRegs {
    /* 0x00 NR10 */ u32 : 1;
                    u32 sweepTime : 3;
                    u32 sweepDir : 1;
                    u32 sweepShift : 3;
    /* 0x01 NR11 */ u32 duty1 : 2;
                    u32 length1 : 6;
    /* 0x02 NR12 */ u32 volume1 : 4;
                    u32 envDir1 : 1;
                    u32 envSweep1 : 3;
    /* 0x03 NR13 */ u32 freqLo1 : 8;
    /* 0x04 NR14 */ u32 trigger1 : 1;
                    u32 counter1 : 1;
                    u32 : 3;
                    u32 freqHi1 : 3;
    /* 0x05 */      u32 : 8;
    /* 0x06 NR21 */ u32 duty2 : 2;
                    u32 length2 : 6;
    /* 0x07 NR22 */ u32 volume2 : 4;
                    u32 envDir2 : 1;
                    u32 envSweep2 : 3;
    /* 0x08 NR23 */ u32 freqLo2 : 8;
    /* 0x09 NR24 */ u32 trigger2 : 1;
                    u32 counter2 : 1;
                    u32 : 3;
                    u32 freqHi2 : 3;
    /* 0x0A NR30 */ u32 waveOn : 1;
                    u32 : 7;
    /* 0x0B NR31 */ u32 length3 : 8;
    /* 0x0C NR32 */ u32 : 1;
                    u32 level3 : 2;
                    u32 : 5;
    /* 0x0D NR33 */ u32 freqLo3 : 8;
    /* 0x0E NR34 */ u32 trigger3 : 1;
                    u32 counter3 : 1;
                    u32 : 3;
                    u32 freqHi3 : 3;
    /* 0x0F */      u32 : 8;
    /* 0x10 NR41 */ u32 : 2;
                    u32 length4 : 6;
    /* 0x11 NR42 */ u32 volume4 : 4;
                    u32 envDir4 : 1;
                    u32 envSweep4 : 3;
    /* 0x12 NR43 */ u16 shift4 : 4;
                    u32 width4 : 1;
                    u32 ratio4 : 3;
    /* 0x13 NR44 */ u32 trigger4 : 1;
                    u32 counter4 : 1;
                    u32 : 6;
    /* 0x14 NR50 */ u32 vinLeft : 1;
                    u32 leftVolume : 3;
                    u32 vinRight : 1;
                    u32 rightVolume : 3;
    /* 0x15 NR51 */ u32 noiseLeft : 1;
                    u32 waveLeft : 1;
                    u32 sq2Left : 1;
                    u32 sq1Left : 1;
                    u32 noiseRight : 1;
                    u32 waveRight : 1;
                    u32 sq2Right : 1;
                    u32 sq1Right : 1;
    /* 0x16 NR52 */ u32 power : 1;
                    u32 : 7;
    /* 0x17 */      u32 : 8;
} GbApuRegs;

#define GB_APU_REGS (*(GbApuRegs*)D_81138A80)

#define GB_APU_WRITE_QUEUE_LEN 1800

typedef struct GbApuWrite {
    /* 0x0 */ u8 reg;
    /* 0x1 */ u8 value;
    /* 0x2 */ u16 time;
} GbApuWrite;

typedef union GbApuMesg {
    OSMesg mesg;
    GbApuWrite write;
} GbApuMesg;

typedef struct AudioBufferParameters {
    /* 0x00 */ s16 specUnk4; // @unverified: same offset/use as OoT's AudioBufferParameters.specUnk4 (set from AudioSpec.unk_04; 2 doubles the AI buffer bounds)
    /* 0x02 */ u16 samplingFrequency; // @unverified: same offset/use as OoT's AudioBufferParameters.samplingFrequency
    /* 0x04 */ s16 aiSamplingFrequency; // @unverified: same offset/use as OoT's AudioBufferParameters.aiSamplingFrequency (osAiSetFrequency result)
    /* 0x06 */ s16 samplesPerFrameTarget; // @unverified: same offset/use as OoT's AudioBufferParameters.samplesPerFrameTarget
    /* 0x08 */ s16 maxAiBufferLength; // @unverified: same offset/use as OoT's AudioBufferParameters.maxAiBufferLength
    /* 0x0A */ s16 minAiBufferLength; // @unverified: same offset/use as OoT's AudioBufferParameters.minAiBufferLength
    /* 0x0C */ s16 ticksPerUpdate; // @unverified: same offset/use as OoT's AudioBufferParameters.ticksPerUpdate
    /* 0x0E */ s16 samplesPerTick; // @unverified: same offset/use as OoT's AudioBufferParameters.samplesPerTick
    /* 0x10 */ s16 samplesPerTickMax; // @unverified: same offset/use as OoT's AudioBufferParameters.samplesPerTickMax
    /* 0x12 */ s16 samplesPerTickMin; // @unverified: same offset/use as OoT's AudioBufferParameters.samplesPerTickMin
    /* 0x14 */ s16 numSequencePlayers; // @unverified: same offset/use as OoT's AudioBufferParameters.numSequencePlayers
    /* 0x16 */ u8 pad16[0x18 - 0x16];
    /* 0x18 */ f32 resampleRate; // @unverified: same offset/use as OoT's AudioBufferParameters.resampleRate (32000 / samplingFrequency)
    /* 0x1C */ f32 ticksPerUpdateInv; // @unverified: same offset/use as OoT's AudioBufferParameters.ticksPerUpdateInv
    /* 0x20 */ f32 ticksPerUpdateInvScaled; // @unverified: same offset/use as OoT's AudioBufferParameters.ticksPerUpdateInvScaled
    /* 0x24 */ f32 ticksPerUpdateScaled; // @unverified: same offset/use as OoT's AudioBufferParameters.ticksPerUpdateScaled
    /* 0x28 */ u8 pad28[0x38 - 0x28];
} AudioBufferParameters;

typedef struct unk_D_81287B08_jp {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001;
    /* 0x002 */ char unk002[0x10];
    /* 0x012 */ s16 unk_012;
    /* 0x014 */ char unk014[0x8];
    /* 0x01C */ f32 unk_01C;
    /* 0x020 */ f32 unk_020;
    /* 0x024 */ f32 unk_024;
    /* 0x028 */ char unk028[0x134];
} unk_D_81287B08_jp;

typedef struct GbAudioStream {
    /* 0x0 */ s32 id;
    /* 0x4 */ s32 pos;
} GbAudioStream;

#define GB_AUDIO_STREAM_DATA ((s8**)D_8115265C)

#define GB_AUDIO_STREAM_SIZE ((s32*)D_81152680)

typedef struct GbStereoSample {
    /* 0x0 */ s16 left;
    /* 0x2 */ s16 right;
} GbStereoSample;

typedef struct SeqLayerFlags {
    u8 enabled : 1; // @unverified: cleared by AudioSeq_SeqLayerDisable, OoT's SequenceLayer.enabled
    u8 finished : 1; // @unverified: set by AudioSeq_SeqLayerDisable, OoT's SequenceLayer.finished
} SeqLayerFlags;

typedef struct SeqChannelFlags {
    u8 enabled : 1; // @unverified: cleared when a channel is disabled, OoT's SequenceChannel.enabled
    u8 finished : 1; // @unverified: set when a channel is disabled, OoT's SequenceChannel.finished
} SeqChannelFlags;

typedef struct Channel81112D68 {
    u8 enabled : 1; // @unverified: set by AudioSeq_SequenceChannelEnable, OoT's SequenceChannel.enabled
    u8 finished : 1; // @unverified: cleared by AudioSeq_SequenceChannelEnable, OoT's SequenceChannel.finished
    char pad01[0x1E - 1];
    s16 delay; // @unverified: same offset/use as OoT's SequenceChannel.delay (zeroed on enable)
    char pad20[0x50 - 0x20];
    s8* layers[4]; // @unverified: same offset/use as OoT's SequenceChannel.layers
    s32 scriptPc; // @unverified: same offset/use as OoT's SequenceChannel.scriptState.pc (script start)
    char pad64[0x78 - 0x64];
    u8 scriptDepth; // @unverified: same offset/use as OoT's SequenceChannel.scriptState.depth
} Channel81112D68;

/* A node or head of a circular list (D_81184928 is the free list of sequence layers). */
typedef struct AudioListItem {
    /* 0x00 */ void* prev; // @unverified: same offset/use as OoT's AudioListItem.prev (NULL when not on a list)
    /* 0x04 */ void* next; // @unverified: same offset/use as OoT's AudioListItem.next
    /* 0x08 */ s32 count; // @unverified: same offset/use as OoT's AudioListItem.u.count (list heads)
    /* 0x0C */ s32 pool; // @unverified: same offset/use as OoT's AudioListItem.pool
} AudioListItem; // size = 0x10

/* A sequence layer (D_811847C8[]), only its list item. */
typedef struct SeqLayer811847C8 {
    /* 0x00 */ u8 pad00[0x74];
    /* 0x74 */ void* listItemPrev; // @unverified: same use as OoT's SequenceLayer.listItem.prev (cleared before the push)
    /* 0x78 */ void* listItemNext;
    /* 0x7C */ struct SeqLayer811847C8* listItemValue; // @unverified: points back at the layer, OoT's listItem.u.value
    /* 0x80 */ s32 listItemPool;
} SeqLayer811847C8; // size = 0x84

struct Layer81113140;

/* The note a layer plays, as AudioSeq_SeqLayerProcessScriptStep1 sees it. */
typedef struct Note81113140 {
    /* 0x00 */ char pad00[0x48];
    /* 0x48 */ struct Layer81113140* wantedParentLayer; // @unverified: same offset/use as OoT's Note.playbackState.wantedParentLayer
} Note81113140;

typedef struct Layer81113140 {
    u32 enabled : 1;
    u32 finished : 1;
    u32 stopSomething : 1;
    u32 continuousNotes : 1; // @unverified: same bit/use as OoT's SequenceLayer.continuousNotes (AudioSeq_SeqLayerProcessScriptStep1)
    u32 bit3 : 1;
    u32 notePropertiesNeedInit : 1; // @unverified: set at the end of AudioSeq_SeqLayerProcessScriptStep1, as OoT's SequenceLayer.notePropertiesNeedInit
    u32 rest : 26;
    char pad04[4];
    u8 portamentoMode; // @unverified: same offset/use as OoT's SequenceLayer.portamento.mode (modes 1 and 2 reset to 0)
    char pad09[0x48 - 0x09];
    Note81113140* note; // @unverified: same offset/use as OoT's SequenceLayer.note
} Layer81113140;

struct SeqPlayer81114B54;

typedef struct SeqPlayer811151C8 {
    u32 enabled : 1; // @unverified: players with this bit are stepped each update, OoT's SequencePlayer.enabled
    char pad[0x15C - 4];
} SeqPlayer811151C8;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0_81113A44.c
 */

typedef struct ChannelFlags81113EF4 {
    u8 pad0 : 4;
    u8 hasInstrument : 1; // @unverified: cleared when the instrument lookup fails, OoT's SequenceChannel.hasInstrument (AudioSeq_SetInstrument)
    u8 pad1 : 3;
} ChannelFlags81113EF4;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0.c
 * src/fragments/fragment000_80C00/gb_tower_emulator_86CB0_81114B54.c
 */

typedef struct Channel8111539C {
    /* 0x00 */ u32 enabled : 1; // @unverified: cleared when the channel is allocated, OoT's SequenceChannel.enabled
    /* 0x00 */ u32 unk00 : 31;
    /* 0x04 */ char unk04[0x48];
    /* 0x4C */ void* seqPlayer; // @unverified: same offset/use as OoT's SequenceChannel.seqPlayer
    /* 0x50 */ void* layers[1]; // @unverified: same offset as OoT's SequenceChannel.layers (only layers[0] is cleared here)
} Channel8111539C;

// Yay0 files in fragment1_misc_yay0 (retail ROM 0xADC80), named by their retail ROM address.
// Offsets from the segment rather than fixed addresses, so they follow it when an earlier
// segment changes size.
#define D_F4130 (fragment1_misc_yay0_ROM_START + 0x464B0)

#define D_F4920 (fragment1_misc_yay0_ROM_START + 0x46CA0)

#define D_F5450 (fragment1_misc_yay0_ROM_START + 0x477D0)

#define D_FDE40 (fragment1_misc_yay0_ROM_START + 0x501C0)

#define D_102BA0 (fragment1_misc_yay0_ROM_START + 0x54F20)

#include "fragments/battle/battle.h"

extern u8 gGbMemoryMap[];

extern u16 D_81138A96;

extern u32 D_81138A90;

extern s16 D_81180700;

extern s16 D_81180702;

extern u8* D_81180704;

extern GbApuChannelState gGbApuSquare1;

extern GbApuChannelState gGbApuSquare2;

extern GbApuChannelState gGbApuWave;

extern GbApuChannelState gGbApuNoise;

extern GbApuWrite D_81180848[GB_APU_WRITE_QUEUE_LEN];

extern u8 D_81182468[0x40];

extern s32 D_811824A8;

extern GbApuStatusOverride D_811824B8;

extern OSMesgQueue D_811824C0;

extern OSMesg D_811824D8[GB_APU_WRITE_QUEUE_LEN + 1];

extern volatile s32 D_811858F0;

extern s32 D_811858F8;

extern s32 D_811858FC;

extern s16* D_811859B8[3];

extern s16 D_811859C4[3];

extern u32 D_811859CC;

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

extern GbAudioStream D_81138B8C;

extern GbAudioStream D_81138B94;

extern u8 D_8115265C[0x24];

extern u8 D_81152680[0x24];

extern struct AudioListItem D_81184928;

extern SeqLayer811847C8 D_811847C8[1];

extern s16 D_811858CC;

// audio_load_2.c
void func_8110DC90(void);
void func_8110DC98(void);
void func_8110E714(void);
s32 BattleScene_EndStatusAnimationsAndCommit(ActivePokemon* active_pokemon);
s32 BattleAnim_EndSleepStatusAnimation(s32 arg0);
void Battle_ApplyAnimStateEffects(s32 arg0);

// audio_thread.c
s32 Audio_CountCategorySounds(s32 arg0);
void func_8110FD6C(s32 cmd, s32 arg1);
void func_8110FC30(void);
void func_8110FE90(void);
void BattleAnim_DisableEffectSpawning(void);
void BattleAnim_DisableEffectSpawningAlias(void);
void BattleAnim_EffectStartNop(void);
void BattleAnim_ClearEffectStateFlag(void);

// audio_playback.c
void AudioPlayback_ProcessNotes(void);

// audio_seqplayer.c
void AudioSeq_SeqLayerDisable(SeqLayerFlags* arg0);
void AudioSeq_SeqLayerFree(s8** arg0, s32 arg1);
void Particle31_ResetAllSlots(DisplayObject* arg0);
void AudioSeq_SequenceChannelEnable(Channel81112D68** arg0, u8 arg1, s32 arg2);
s32 AudioSeq_AudioListPopBack(s8 *arg0);
void AudioSeq_InitLayerFreelist(void);
u8 AudioSeq_ScriptReadU8(u8 **arg0);
s16 AudioSeq_ScriptReadS16(u8** arg0);
void AudioSeq_SeqLayerProcessScriptStep1(Layer81113140* arg0);

// audio_seqplayer_2.c
/*
 * func_81113F84
 *
 * Stores (float)arg1 / 127.0f into the float at offset 0x2C of the object
 * arg0 points to.  arg1 is an unsigned byte (the generated code masks it
 * with 0xFF), so the stored value runs from 0.0 to 255/127 (about 2.0);
 * the stored value is 1.0 when arg1 is 127.  What the field at +0x2C
 * represents is not known.
 */
void func_81113F84(u8* arg0, u8 arg1);

// audio_seqplayer_3.c
void func_811155A0(void);
void GbApu_SetActiveFlag(void);
void GbApu_ClearActiveFlag(void);
void func_81215C14_jp(s32 arg0, s32 arg1, u8 arg2);
void func_81215C9C_jp(s32 arg0, s32 arg1);
void func_81115704(void);
void func_81215D0C_jp(s32 arg0, s32 arg1, s32 arg2);
void func_81215D50_jp(void);
void func_81215D8C_jp(s32 arg0, s32 arg1, s32 arg2);
void func_81215DDC_jp(void);
void GbApu_SetNoiseLoopBounds(s32 arg0, s32 arg1);
void func_81114B54(struct SeqPlayer81114B54*);
void func_811151C8(s32 arg0);
void func_81115254(s8 *arg0);

// gb_apu.c
u32 GbApu_FreqToStep(u16 arg0);
u32 GbApu_ConfigureNoiseTable(u16 arg0, u16 arg1, u16 arg2);
u32 GbApu_FreqToStep2x(u16 arg0);
void func_81115AF0(void);
s32 GbApu_GetWaveformSample(u32 arg0, s32 arg1);
u16 GbApu_UpdateSquare1Channel(void);
s32 GbApu_UpdateSquare2Channel(void);
u16 GbApu_UpdateWaveChannel(void);
u16 func_81207C5C_Empty(void);
u16 GbApu_UpdateNoiseChannel(void);
void GbApu_WriteRegister(u16 reg, u8 value);
void GbApu_RenderBuffer(s32 numSamples, s16* out);
void GbApu_QueueRegisterWrite(u16 arg0, u8 arg1, u16 arg2);
void GbApu_ResetChannels(void);
void GbAudio_RampToSilence(void);
void func_811173F4(void);
u8 GbMem_ReadIoRegister(u16 arg0);
void GbAudio_SetMenuSoundMode(s32 arg0);
void GbAudio_PlayMenuSound(s32 arg0);

// gb_apu_2.c
void func_811177E8(s32 numSamples, s16* out);
void func_81117AFC(UNUSED s32 arg0);
void func_81218104_jp(UNUSED s32 arg0);

// functions defined in assembly
void BattleAnim_ClearFreezeStatusAnimation(ActivePokemon* active_pokemon);

#endif // FRAGMENT_AUDIO_AND_GB_EMULATOR_H
