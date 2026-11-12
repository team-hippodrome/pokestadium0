#ifndef ZERO_GB_TOWER_EMULATOR_86CB0_H
#define ZERO_GB_TOWER_EMULATOR_86CB0_H

/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_emulator/gb_tower_emulator_86CB0.c. */

#include "global.h"
typedef struct GbApuChannelState {
  /* 0x00 */ u8 unk_00;
  /* 0x02 */ char unk02[0x02];
  /* 0x04 */ s32 unk_04;
  /* 0x08 */ union {
      u16 unk_00;
      s32 unk_02;
  } unk_08;
  /* 0x0C */ u32 unk_0C;
  /* 0x10 */ u16 unk_10;
  /* 0x12 */ u16 unk_12;
  /* 0x14 */ s32 unk_14;
  /* 0x18 */ s32 unk_18;
  /* 0x1C */ s32 unk_1C;
  /* 0x20 */ u8 unk_20;
  /* 0x21 */ u8 unk_21;
  /* 0x22 */ char unk22[0x2];
  /* 0x24 */ u32 unk_24;
  /* 0x28 */ u32 unk_28;
  /* 0x2C */ char unk2C[0x1];
  /* 0x2D */ u8 unk_2D;
  /* 0x2E */ u8 unk_2E;
  /* 0x2F */ char unk2F[0x1];
  /* 0x30 */ u32 unk_30;
  /* 0x34 */ u32 unk_34;
  /* 0x38 */ u8 unk_38;
  /* 0x39 */ u8 unk_39;
  /* 0x3A */ u8 unk_3A;
  /* 0x3B */ u8 unk_3B;
  /* 0x3C */ u8 unk_3C;
  /* 0x3D */ char unk3D[0x3];
  /* 0x40 */ u32 unk_40;
  /* 0x44 */ u16 unk_44;
  /* 0x46 */ u16 unk46;
  /* 0x48 */ u32 unk_48;
  /* 0x4C */ u8 unk_4C;
  /* 0x4D */ char unk4D[0x3];
} GbApuChannelState;
typedef struct unk_D_8122EEA8 {
  /* 0x00 */ u8 unk_00;
  /* 0x01 */ u8 unk_01;
  /* 0x02 */ u8 unk_02;
  /* 0x03 */ u8 unk_03;
} unk_D_8122EEA8;
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
extern unk_D_8122EEA8 D_811824B8;
extern OSMesgQueue D_811824C0;
extern OSMesg D_811824D8[GB_APU_WRITE_QUEUE_LEN + 1];
typedef struct unk_D_81234690 {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 pad0E[0x2A];
} unk_D_81234690;
extern unk_D_81234690 D_811858B8;
extern volatile s32 D_811858F0;
extern s32 D_811858F8;
extern s32 D_811858FC;
extern s16* D_811859B8[3];
extern s16 D_811859C4[3];
extern u32 D_811859CC;
extern volatile u32 D_811859D4;
void func_811177E8(s32 numSamples, s16* out);
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
extern unk_D_81287B08_jp D_81287B08_jp[];
extern OSMesgQueue* D_812896A0_jp;
void func_8121036C_jp(s32 cmd, s32 arg1);
void func_81210390_jp(s32 cmd, s8 arg1);
void func_812103F0_jp(void);
extern s32 D_81138A70;
extern u8 D_81138A80[0x10];
extern u8 sGbApuRegs[0x40];
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
typedef struct GbAudioStream {
    /* 0x0 */ s32 id;
    /* 0x4 */ s32 pos;
} GbAudioStream;
extern GbAudioStream D_81138B84;
extern GbAudioStream D_81138B8C;
extern GbAudioStream D_81138B94;
extern u8 D_8115265C[0x24];
extern u8 D_81152680[0x24];
#define GB_AUDIO_STREAM_DATA ((s8**)D_8115265C)
#define GB_AUDIO_STREAM_SIZE ((s32*)D_81152680)
typedef struct GbStereoSample {
    /* 0x0 */ s16 left;
    /* 0x2 */ s16 right;
} GbStereoSample;

#include "m2c_macros.h"

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
u32 GbApu_FreqToStep(u16 arg0);
u32 func_811158F4(u16 arg0, u16 arg1, u16 arg2);
u32 GbApu_FreqToStep2x(u16 arg0);
void func_81115AF0(void);
s32 func_81115AF8(u32 arg0, s32 arg1);
u16 GbApu_UpdateSquare1Channel(void);
s32 GbApu_UpdateSquare2Channel(void);
u16 GbApu_UpdateWaveChannel(void);
u16 func_81207C5C_Empty(void);
u16 func_81116258(void);
void func_811164CC(u16 reg, u8 value);
void func_81116C88(s32 numSamples, s16* out);
void func_81117068(u16 arg0, u8 arg1, u16 arg2);
void GbApu_ResetChannels(void);
void GbApu_Reset(s32 arg0);
void func_811172AC(void);
void func_811173F4(void);
u8 GbMem_ReadIoRegister(u16 arg0);
s32 func_811174D8(void);
void GbAudio_SetMenuSoundMode(s32 arg0);
void GbAudio_PlayMenuSound(s32 arg0);
void func_81117AFC(UNUSED s32 arg0);
void func_81218104_jp(UNUSED s32 arg0);

typedef struct Particle31FlagsA {
    u8 b80 : 1;
    u8 b40 : 1;
} Particle31FlagsA;

void func_81111090(Particle31FlagsA*);
void func_81112AF8(Particle31FlagsA* arg0);

extern struct GbEmuListZ D_81184928;
void func_81112EAC(s8* arg0, s8* arg1);
void func_81112B34(s8** arg0, s32 arg1);

typedef struct Particle31Flags {
    u8 b80 : 1;
    u8 b40 : 1;
} Particle31Flags;

void func_811111E0(s8*);

void func_81112B34();
void Particle31_ResetAllSlots(DisplayObject* arg0);

typedef struct Particle2D68 {
    u8 b80 : 1;
    u8 b40 : 1;
    char pad01[0x1E - 1];
    s16 unk_1E;
    char pad20[0x50 - 0x20];
    s8* unk_50[4];
    s32 unk_60;
    char pad64[0x78 - 0x64];
    u8 unk_78;
} Particle2D68;

void func_81112D68(Particle2D68** arg0, u8 arg1, s32 arg2);

void func_81112EAC(s8 *arg0, s8 *arg1);

s32 func_81112EEC(s8 *arg0);

typedef struct GbEmuListZ {
    /* 0x00 */ void* next;
    /* 0x04 */ void* prev;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 unk_0C;
} GbEmuListZ; // size = 0x10
typedef struct GbEmuEntryZ {
    /* 0x00 */ u8 pad00[0x74];
    /* 0x74 */ void* next;
    /* 0x78 */ void* prev;
    /* 0x7C */ struct GbEmuEntryZ* owner;
    /* 0x80 */ s32 unk_80;
} GbEmuEntryZ; // size = 0x84
extern GbEmuListZ D_81184928;
extern GbEmuEntryZ D_811847C8[1];

void func_81112F2C(void);

u8 func_81112FB0(u8 **arg0);

s16 func_81112FC4(u8** arg0);

typedef struct Particle3140 {
    u32 b80 : 1;
    u32 b40 : 1;
    u32 b20 : 1;
    u32 b10 : 1;
    u32 b08 : 1;
    u32 b04 : 1;
    u32 rest : 26;
    char pad04[4];
    u8 unk_08;
    char pad09[0x48 - 0x09];
    struct Particle3140* unk_48;
} Particle3140;

void func_81113140(Particle3140* arg0);

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

M2C_UNK func_81111DC8(s8 *);
struct SeqPlayer81114B54;
void func_81114B54(struct SeqPlayer81114B54*);
typedef struct Entry811151C8 {
    u32 b80 : 1;
    char pad[0x15C - 4];
} Entry811151C8;
extern s16 D_811858CC;
extern Entry811151C8 D_81184668[];
void func_81110798(void);
void func_811151C8(s32 arg0);

M2C_UNK func_81111DC8(s8 *);                      /* extern */
void func_81115254(s8 *arg0);

// Scales channel arg0's unk_01C by arg2 percent: at once when arg1 == 0, otherwise as a ramp
// of unk_020 per step over unk_012 = arg1 steps. unk_024 keeps the value before the change.

// Returns channel arg0's unk_01C to the unk_024 value saved by func_81215C14_jp, at once or
// as a ramp over arg1 steps.

// Second empty handler; in the Japanese build this file's .text ends here (0x81218110).

#endif
