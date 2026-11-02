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
void GbApu_SetNoisePeriodBounds(s32 arg0, s32 arg1);
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
void GbAudio_SetAlternateRendererEnabled(s32 arg0);
void GbAudio_SetAlternateStreamId(s32 arg0);
void func_811177E8(s32 numSamples, s16* out);
void func_81117AFC(UNUSED s32 arg0);
void func_81218104_jp(UNUSED s32 arg0);

#ifdef NON_MATCHING
/* TODO: decompile func_81112650; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81112650.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811126B8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811126B8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81112894; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81112894.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811129E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811129E0.s")
#endif

typedef struct Particle31FlagsA {
    u8 b80 : 1;
    u8 b40 : 1;
} Particle31FlagsA;

void func_81111090(Particle31FlagsA*);
void func_81112AF8(Particle31FlagsA* arg0) {
    if (arg0 != NULL) {
        func_81111090(arg0);
        arg0->b80 = 0;
        arg0->b40 = 1;
    }
}

extern struct GbEmuListZ D_81184928;
void func_81112EAC(s8* arg0, s8* arg1);
void func_81112B34(s8** arg0, s32 arg1) {
    s8* temp = arg0[arg1 + 0x14];

    if (temp != NULL) {
        func_81112EAC((s8*)&D_81184928, temp + 0x74);
        func_81112AF8((Particle31FlagsA*)temp);
        arg0[arg1 + 0x14] = NULL;
    }
}

typedef struct Particle31Flags {
    u8 b80 : 1;
    u8 b40 : 1;
} Particle31Flags;

void func_811111E0(s8*);

void func_81112B34();
void Particle31_ResetAllSlots(DisplayObject* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_81112B34(arg0, i);
    }
    func_811111E0((s8*)arg0 + 0x84);
    ((Particle31Flags*)arg0)->b80 = 0;
    ((Particle31Flags*)arg0)->b40 = 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81112BF0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81112BF0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81112CE8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81112CE8.s")
#endif

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

void func_81112D68(Particle2D68** arg0, u8 arg1, s32 arg2) {
    Particle2D68* p = arg0[arg1 + 13];
    s32 i;

    p->unk_78 = 0;
    p->unk_60 = arg2;
    p->b80 = 1;
    p->b40 = 0;
    p->unk_1E = 0;
    for (i = 0; i < 4; i++) {
        if (p->unk_50[i] != NULL) {
            func_81112B34((s8**)p, i);
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_81112E00; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81112E00.s")
#endif

void func_81112EAC(s8 *arg0, s8 *arg1)
{
  if ((*((s8 **) (((s8 *) arg1) + 0))) == 0)
  {
    *((s8 **) (((s8 *) (*((s8 **) (((s8 *) arg0) + 0)))) + 4)) = arg1;
    *((s8 **) (((s8 *) arg1) + 0)) = (s8 *) (*((s8 **) (((s8 *) arg0) + 0)));
    *((s8 **) (((s8 *) arg1) + 4)) = arg0;
    *((s8 **) (((s8 *) arg0) + 0)) = arg1;
    *((s32 *) (((s8 *) arg0) + 8)) = ((s32) ((*((s32 *) (((s8 *) arg0) + 8))) + 1)) ^ 0;
    *((s32 *) (((s8 *) arg1) + 0xC)) = (s32) (*((s32 *) (((s8 *) arg0) + 0xC)));
  }
}

s32 func_81112EEC(s8 *arg0) {
    s8 *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_v1 == arg0) {
        return 0;
    }
    M2C_FIELD(M2C_FIELD(temp_v1, s8 **, 0), s8 **, 4) = arg0;
    M2C_FIELD(arg0, s8 **, 0) = (s8 *) M2C_FIELD(temp_v1, s8 **, 0);
    M2C_FIELD(temp_v1, s8 **, 0) = NULL;
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) - 1);
    return M2C_FIELD(temp_v1, s32 *, 8);
}

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

void func_81112F2C(void) {
    s32 i;

    D_81184928.next = &D_81184928;
    D_81184928.prev = &D_81184928;
    D_81184928.count = 0;
    D_81184928.unk_0C = 0;
    for (i = 0; i < 1; i++) {
        D_811847C8[i].owner = &D_811847C8[i];
        D_811847C8[i].next = NULL;
        func_81112EAC((s8*)&D_81184928, (s8*)&D_811847C8[i].next);
    }
}

u8 func_81112FB0(u8 **arg0)
{
  u8 new_var;
  u8 *temp_a1;
  new_var = *(*arg0);
  temp_a1 = *arg0;
  *arg0 = temp_a1 + 1;
  return new_var;
}

s16 func_81112FC4(u8** arg0) {
    s16 tmp = *(*arg0)++ << 8;

    tmp = *(*arg0)++ | tmp;
    return tmp;
}

/*
 * func_81112FFC
 *
 * Reads a one- or two-byte value from the byte stream whose current position
 * is stored at *arg0, advancing that position. If the first byte has bit 7
 * clear it is the result. Otherwise the result is ((first & 0x7F) << 8) |
 * second byte, and the position advances past both bytes.
 */
u16 func_81112FFC(u8** arg0) {
    u16 v;

    v = *(*arg0)++;
    if (v & 0x80) {
        v = (v << 8) & 0x7F00;
        v = *(*arg0)++ | v;
    }
    return v;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8111303C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8111303C.s")
#endif

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

void func_81113140(Particle3140* arg0) {
    if (!arg0->b10) {
        func_81111090((Particle31FlagsA*)arg0);
    } else if (arg0->unk_48 != NULL && arg0 == arg0->unk_48->unk_48) {
        func_81111090((Particle31FlagsA*)arg0);
    }
    switch (arg0->unk_08 & ~0x80) {
        case 1:
        case 2:
            arg0->unk_08 = 0;
            break;
    }
    arg0->b04 = 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_811131CC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811131CC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811132E4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811132E4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81113650; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81113650.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81113A44; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81113A44.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_81113E84; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81113E84.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81113EF4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81113EF4.s")
#endif

/*
 * func_81113F84
 *
 * Stores (float)arg1 / 127.0f into the float at offset 0x2C of the object
 * arg0 points to.  arg1 is an unsigned byte (the generated code masks it
 * with 0xFF), so the stored value runs from 0.0 to 255/127 (about 2.0);
 * the stored value is 1.0 when arg1 is 127.  What the field at +0x2C
 * represents is not known.
 */
void func_81113F84(u8* arg0, u8 arg1) {
    *(f32*)(arg0 + 0x2C) = (f32)(s32)arg1 / 127.0f;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81113FA8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81113FA8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81114B54; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81114B54.s")
#endif

M2C_UNK func_81111DC8(s8 *);
M2C_UNK func_81114B54(s8 *);
typedef struct Entry811151C8 {
    u32 b80 : 1;
    char pad[0x15C - 4];
} Entry811151C8;
extern s16 D_811858CC;
extern Entry811151C8 D_81184668[];
void func_81110798(void);
void func_811151C8(s32 arg0) {
    u32 i;

    for (i = 0; i < D_811858CC; i++) {
        if (D_81184668[i].b80 == 1) {
            func_81114B54((s8*)&D_81184668[i]);
            func_81111DC8((s8*)&D_81184668[i]);
        }
    }
    func_81110798();
}

M2C_UNK func_81111DC8(s8 *);                      /* extern */
M2C_UNK func_81114B54(s8 *);                      /* extern */
void func_81115254(s8 *arg0)
{
  s8 *new_var;
  s32 temp_t8;
  if ((*((s32 *) (((s8 *) arg0) + 0xD8))) > 0)
  {
    do
    {
      func_81114B54(arg0);
      func_81111DC8(arg0);
      new_var = (s8 *) arg0;
      temp_t8 = (unsigned long long) ((*((s32 *) (new_var + 0xD8))) - 1);
      *((s32 *) (((s8 *) arg0) + 0xD8)) = temp_t8;
    }
    while (temp_t8 > 0);
  }
}

#ifdef NON_MATCHING
/* TODO: decompile func_811152A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811152A4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8111539C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8111539C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81115480; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81115480.s")
#endif

void func_811155A0(void) {
    func_812103F0_jp();
}

void GbApu_SetActiveFlag(void) {
    func_8121036C_jp(0xF1000000, 0);
    D_81138A70 = 1;
}

void GbApu_ClearActiveFlag(void) {
    func_8121036C_jp(0xF2000000, 0);
    D_81138A70 = 0;
}

// Scales channel arg0's unk_01C by arg2 percent: at once when arg1 == 0, otherwise as a ramp
// of unk_020 per step over unk_012 = arg1 steps. unk_024 keeps the value before the change.
void func_81215C14_jp(s32 arg0, s32 arg1, u8 arg2) {
    unk_D_81287B08_jp* ch = &D_81287B08_jp[arg0];
    f32 target;

    ch->unk_012 = 0;
    target = ((s32)arg2 / 100.0f) * ch->unk_01C;
    ch->unk_024 = ch->unk_01C;
    if (arg1 == 0) {
        ch->unk_01C = target;
        return;
    }
    ch->unk_001 = 0;
    ch->unk_012 = arg1;
    ch->unk_020 = (target - ch->unk_01C) / arg1;
}

// Returns channel arg0's unk_01C to the unk_024 value saved by func_81215C14_jp, at once or
// as a ramp over arg1 steps.
void func_81215C9C_jp(s32 arg0, s32 arg1) {
    unk_D_81287B08_jp* ch = &D_81287B08_jp[arg0];

    ch->unk_012 = 0;
    if (arg1 == 0) {
        ch->unk_01C = ch->unk_024;
        return;
    }
    ch->unk_001 = 0;
    ch->unk_012 = arg1;
    ch->unk_020 = (ch->unk_024 - ch->unk_01C) / arg1;
}

void func_81115704(void) {
}

void func_81215D0C_jp(s32 arg0, s32 arg1, s32 arg2) {
    func_81210390_jp(((arg0 & 0xFF) << 16) | 0x08000000 | ((arg1 & 0xFF) << 8), arg2);
}

void func_81215D50_jp(void) {
    func_8121036C_jp(0x82020100, 0);
    func_812103F0_jp();
    func_8121036C_jp(0xF8000000, 0);
}

void func_81215D8C_jp(s32 arg0, s32 arg1, s32 arg2) {
    func_81210390_jp(0x06020002, arg1);
    func_81210390_jp(0x06020001, arg0);
    func_81210390_jp(0x06020000, arg2);
}

void func_81215DDC_jp(void) {
    func_81210390_jp(0x06020004, -1);
}

void GbApu_SetNoisePeriodBounds(s32 arg0, s32 arg1) {
    D_81138AD0 = arg0;
    D_81138AD4 = arg1;
}

u32 GbApu_FreqToStep(u16 arg0) {
  u32 temp;
  if (arg0 == 0) {
      return 0;
  }
  temp = ((65536.0f / (0x800 - arg0)) / 1500.0f) * 65536;
  return temp;
}

u32 func_811158F4(u16 arg0, u16 arg1, u16 arg2) {
    u32 temp;
    s32 temp2;

    D_811824A8 = (arg1 * 16 + arg0) << 14;
    temp = D_81138B50[arg2];
    temp2 = (f32)temp;
    temp = (temp2 / 48000.0f) * 24000.0f;
    D_81138AD0 = D_81138ADC[arg0 * 2 + arg1];
    return temp;
}

u32 GbApu_FreqToStep2x(u16 arg0) {
  u32 temp;
  temp = ((131072.0f / (0x800 - arg0)) / 1500.0f) * 65536;
  return temp;
}

void func_81115AF0(void) {
}

s32 func_81115AF8(u32 arg0, s32 arg1) {
    switch (arg0) {
    case 0:
        if ((arg1 >= 4) && (arg1 < 8)) {
            return 0x7F;
        }
        return 0;
    case 1:
        if (arg1 < 8) {
            return 0x7F;
        }
        return 0;
    case 2:
        if (arg1 < 0x10) {
            return 0x7F;
        }
        return 0;
    case 3:
        if (arg1 < 8) {
            return 0;
        }
        return 0x7F;
    case 4:
    case 5:
        break;
    case 6:
        return (u8)(D_81180704[arg1 + D_811824A8] & 0x7F);
    case 7:
        return (u8)(D_81182468[arg1] << 3);
    }
}

u16 GbApu_UpdateSquare1Channel(void) {
    u16 var_t0;

    if (gGbApuSquare1.unk_00 == 0) {
        if (gGbApuSquare1.unk_3C == 0) {
            return 0U;
        }
        gGbApuSquare1.unk_3C--;
        gGbApuSquare1.unk_20 = gGbApuSquare1.unk_3C;
        gGbApuSquare1.unk_0C = (s32) gGbApuSquare1.unk_40;
    }
    if ((s32) gGbApuSquare1.unk_10 <= 0) {
        gGbApuSquare1.unk_4C = 1U;
    } else if (((s32) gGbApuSquare1.unk_10 >= 0x7FF) && (gGbApuSquare1.unk_39 == 0)) {
        gGbApuSquare1.unk_4C = 1U;
    } else {
        gGbApuSquare1.unk_4C = 0U;
    }
    {
        s32 temp_v0 = func_81115AF8(gGbApuSquare1.unk_3B, gGbApuSquare1.unk_08.unk_00);
        gGbApuSquare1.unk_08.unk_02 += gGbApuSquare1.unk_0C;
        gGbApuSquare1.unk_08.unk_02 &= 0x1FFFFF;
        if (gGbApuSquare1.unk_4C == 1) {
            if (gGbApuSquare1.unk_3C != 0) {
                gGbApuSquare1.unk_3C--;
            }
            var_t0 = ((temp_v0 & 0xFFFF) * gGbApuSquare1.unk_3C);
        } else {
            gGbApuSquare1.unk_40 = (s32) gGbApuSquare1.unk_0C;
            gGbApuSquare1.unk_3C = (u8) gGbApuSquare1.unk_20;
            var_t0 = ((temp_v0 & 0xFFFF) * gGbApuSquare1.unk_20);
        }
    }
    if ((gGbApuSquare1.unk_3A != 0) && (((++gGbApuSquare1.unk_30 % (u32) gGbApuSquare1.unk_34) == 0))) {
        s32 temp_a2 = ((s32) gGbApuSquare1.unk_10 >> gGbApuSquare1.unk_38) & 0xFFFF;
        switch (gGbApuSquare1.unk_39) {
        case 0:
            gGbApuSquare1.unk_10 += temp_a2;
            break;
        case 1:
            gGbApuSquare1.unk_10 = (gGbApuSquare1.unk_10 - temp_a2) - 1;;
            break;
        }
        if (gGbApuSquare1.unk_10 <= 0) {
            gGbApuSquare1.unk_00 = 0U;
            return var_t0;
        } else {
            if ((gGbApuSquare1.unk_10 >= 0x800) && (gGbApuSquare1.unk_39 == 0)) {
                gGbApuSquare1.unk_10 = 0x7FFU;
                gGbApuSquare1.unk_00 = 0U;
            }
            gGbApuSquare1.unk_0C = GbApu_FreqToStep2x(gGbApuSquare1.unk_10);
        }
    }
    if (gGbApuSquare1.unk_28 != 0) {
        gGbApuSquare1.unk_24++;
        if ((gGbApuSquare1.unk_24 % (u32) gGbApuSquare1.unk_28) == 0) {
            switch (gGbApuSquare1.unk_2E) {
            case 0:
                if (gGbApuSquare1.unk_2D != 0) {
                    gGbApuSquare1.unk_2D--;
                }
                if (!gGbApuSquare1.unk_2D) {
                    gGbApuSquare1.unk_00 = 0;
                }
                break;
            
            case 1:
                if (gGbApuSquare1.unk_2D < 0xF) {
                    gGbApuSquare1.unk_2D++;
                }
                break;
            
            default:
                break;
            }
        gGbApuSquare1.unk_20 = D_81138B1C[gGbApuSquare1.unk_2D];
        }
    } else {
        gGbApuSquare1.unk_20 = D_81138B1C[gGbApuSquare1.unk_2D];
    }
    if (gGbApuSquare1.unk_18 == 1U) {
        if (gGbApuSquare1.unk_14 != 0) {
            gGbApuSquare1.unk_14--;
        }
        if (gGbApuSquare1.unk_14 == 0) {
            gGbApuSquare1.unk_00 = 0U;
        }
    }
    return var_t0;
}

s32 GbApu_UpdateSquare2Channel(void) {
    s32 temp_v0;
    s32 var_a3;
    u8 var_v0;

    if (gGbApuSquare2.unk_00 == 0) {
        if (gGbApuSquare2.unk_3C == 0) {
            return 0;
        }
        gGbApuSquare2.unk_3C--;
        gGbApuSquare2.unk_20 = gGbApuSquare2.unk_3C;
        gGbApuSquare2.unk_0C = (s32) gGbApuSquare2.unk_40;
    }
    if ((s32) gGbApuSquare2.unk_10 >= 0x7FF) {
        gGbApuSquare2.unk_4C = 1U;
    } else {
        gGbApuSquare2.unk_4C = 0U;
    }
    temp_v0 = func_81115AF8(gGbApuSquare2.unk_3B, gGbApuSquare2.unk_08.unk_00);
    gGbApuSquare2.unk_08.unk_02 += gGbApuSquare2.unk_0C;
    gGbApuSquare2.unk_08.unk_02 &= 0x1FFFFF;
    if (gGbApuSquare2.unk_4C == 1) {
        if (gGbApuSquare2.unk_3C != 0) {
            gGbApuSquare2.unk_3C--;
        }
        var_a3 = ((temp_v0 & 0xFFFF) * gGbApuSquare2.unk_3C) & 0xFFFF;
    } else {
        if (gGbApuSquare2.unk_20 != gGbApuSquare2.unk_3C) {
            gGbApuSquare2.unk_3C = (u8) gGbApuSquare2.unk_20;
        }
        gGbApuSquare2.unk_40 = (s32) gGbApuSquare2.unk_0C;
        var_a3 = ((temp_v0 & 0xFFFF) * gGbApuSquare2.unk_20) & 0xFFFF;
    }
    if (gGbApuSquare2.unk_28 != 0) {
        gGbApuSquare2.unk_24++;
        if ((gGbApuSquare2.unk_24 % (u32) gGbApuSquare2.unk_28) == 0) {
            switch (gGbApuSquare2.unk_2E) {
                case 0:
                    if (gGbApuSquare2.unk_2D != 0) {
                        gGbApuSquare2.unk_2D--;
                    }
                    if (!gGbApuSquare2.unk_2D) {
                        gGbApuSquare2.unk_00 = 0;
                    }
                    break;
                
                case 1:
                    if (gGbApuSquare2.unk_2D < 0xF) {
                        gGbApuSquare2.unk_2D++;
                    }
                    break;
                
                default:
                    break;
                }
            gGbApuSquare2.unk_20 = D_81138B1C[gGbApuSquare2.unk_2D];
        }
    } else {
        gGbApuSquare2.unk_20 = D_81138B1C[gGbApuSquare2.unk_2D];
    }
    if (gGbApuSquare2.unk_18 == 1U) {
        if (gGbApuSquare2.unk_14 != 0) {
            gGbApuSquare2.unk_14--;
        }
        if (gGbApuSquare2.unk_14 == 0) {
            gGbApuSquare2.unk_00 = 0U;
        }
    }
    return var_a3;
}

u16 GbApu_UpdateWaveChannel(void) {
    u16 temp_v0;
    u16 temp_a0;
    u16 temp_a1;
    u16 var_a0;

    if (gGbApuWave.unk_00 == 0) {
        if (gGbApuWave.unk_3C == 0) {
            return 0U;
        }
        gGbApuWave.unk_3C--;
        gGbApuWave.unk_20 = gGbApuWave.unk_3C;
        gGbApuWave.unk_0C = (s32) gGbApuWave.unk_40;
    } else {    
        if (gGbApuWave.unk_04 != 0) {
            gGbApuWave.unk_04--;
            if (gGbApuWave.unk_04 >= 0x21) {
                if (gGbApuWave.unk_3C == 0) {
                    gGbApuWave.unk_04 = 0x20;
                    gGbApuWave.unk_08.unk_02 = 0;
                    gGbApuWave.unk_0C = GbApu_FreqToStep(gGbApuWave.unk_10);
                    gGbApuWave.unk_20 = D_81138B2C[gGbApuWave.unk_21];
                } else {
                    if (!(gGbApuWave.unk_04 & 7)) {
                        gGbApuWave.unk_3C--;
                    }
                    gGbApuWave.unk_20 = gGbApuWave.unk_3C;
                    gGbApuWave.unk_0C = (s32) gGbApuWave.unk_40;
                }
            }
        }
    }
    temp_a0 = func_81115AF8(7, gGbApuWave.unk_08.unk_00);
    gGbApuWave.unk_08.unk_02 += gGbApuWave.unk_0C;
    gGbApuWave.unk_08.unk_02 &= 0x1FFFFF;
    if (gGbApuWave.unk_4C - 1 == 0) {

        if (gGbApuWave.unk_3C != 0) {
            gGbApuWave.unk_3C--;
        }
        temp_a1 = gGbApuWave.unk_3C;
    } else {
        gGbApuWave.unk_3C = gGbApuWave.unk_20;
        gGbApuWave.unk_40 = gGbApuWave.unk_0C;
        temp_a1 = gGbApuWave.unk_20;
    }

    temp_a0 *= temp_a1;
    temp_a0 = (gGbApuWave.unk_44 + temp_a0) >> 1;
    gGbApuWave.unk_44 = temp_a0;
    if (gGbApuWave.unk_18 == 1) {
        if (gGbApuWave.unk_14 != 0) {
            gGbApuWave.unk_14--;
        }
        if (gGbApuWave.unk_14 == 0) {
            gGbApuWave.unk_00 = 0U;
        }
    }
    return temp_a0;
}

u16 func_81207C5C_Empty(void) {
    
}

u16 func_81116258(void) {
    static s32 D_8120EB6C = 0;
    u16 temp_v0;
    u32 var_a2;

    if (gGbApuNoise.unk_0C < gGbApuNoise.unk_40) {
        gGbApuNoise.unk_40 -= gGbApuNoise.unk_48;
        var_a2 = gGbApuNoise.unk_40;
    } else if (gGbApuNoise.unk_40 < gGbApuNoise.unk_0C) {
        gGbApuNoise.unk_40 += gGbApuNoise.unk_48;
        var_a2 = gGbApuNoise.unk_40;
    } else {
        var_a2 = gGbApuNoise.unk_40;
    }

    if (gGbApuNoise.unk_00 == 0) {
        if (gGbApuNoise.unk_3C == 0) {
            return 0;
        }
        gGbApuNoise.unk_3C--;
        gGbApuNoise.unk_20 = gGbApuNoise.unk_3C;
        gGbApuNoise.unk_0C = gGbApuNoise.unk_40;
    }
    temp_v0 = func_81115AF8(6, gGbApuNoise.unk_08.unk_00);
    gGbApuNoise.unk_08.unk_02 += var_a2;
    if (gGbApuNoise.unk_08.unk_00  >= (u32)D_81138AD4) {
        gGbApuNoise.unk_08.unk_00  = D_81138AD0;
    }
    temp_v0 *= gGbApuNoise.unk_3C;
    if ((gGbApuNoise.unk_3C != gGbApuNoise.unk_20) && ((D_8120EB6C % 95) == 0)) {
        if (gGbApuNoise.unk_3C > gGbApuNoise.unk_20) {
            gGbApuNoise.unk_3C--;
        } else {
            gGbApuNoise.unk_3C++;
        }
    }
    D_8120EB6C++;
    if (gGbApuNoise.unk_28 != 0) {
        gGbApuNoise.unk_24++;
        if ((gGbApuNoise.unk_24 % (u32) gGbApuNoise.unk_28) == 0) {
            switch (gGbApuNoise.unk_2E) {             /* irregular */
            case 0:
                if (gGbApuNoise.unk_2D) {
                    gGbApuNoise.unk_2D--;
                }
                if (gGbApuNoise.unk_2D == 0) {
                    gGbApuNoise.unk_00 = 0;
                }
                break;
            case 1:
                if (gGbApuNoise.unk_2D < 0xF) {
                    gGbApuNoise.unk_2D++;
                }
                break;
            }
            switch ((D_81138A90 << 0x14) >> 0x1F) {                    /* switch 1; irregular */
            case 0:                                 /* switch 1 */
                gGbApuNoise.unk_20 = D_81138B30[gGbApuNoise.unk_2D];
                break;
            case 1:                                 /* switch 1 */
                gGbApuNoise.unk_20 = D_81138B40[gGbApuNoise.unk_2D];
                break;
            }
        }
    }
    if (gGbApuNoise.unk_18 == 1) {
        if (gGbApuNoise.unk_14 != 0) {
            gGbApuNoise.unk_14--;
        }
        if (gGbApuNoise.unk_14 == 0) {
            gGbApuNoise.unk_00 = 0U;
        }
    }
    
    return (temp_v0 << 1);
}

void func_811164CC(u16 reg, u8 value) {
    s32 pad;
    s32 i;
    s32 pad2;

    if ((reg == 0x26) && !(value & 0x80)) {
        for (i = 0x23; i != 0xF; i--) {
            func_811164CC(i, 0);
        }
    }

    if ((reg < 0x24) && !GB_APU_REGS.power) {
        return;
    }

    D_81138A80[reg - 0x10] = value;

    switch (reg) {
        case 0x10:
            gGbApuSquare1.unk_34 = GB_APU_REGS.sweepTime * 400;
            gGbApuSquare1.unk_39 = GB_APU_REGS.sweepDir;
            gGbApuSquare1.unk_38 = GB_APU_REGS.sweepShift;
            if (gGbApuSquare1.unk_3A == 0) {
                gGbApuSquare1.unk_30 = 0;
            }
            if (gGbApuSquare1.unk_34 == 0) {
                gGbApuSquare1.unk_3A = 0;
            } else {
                gGbApuSquare1.unk_3A = 1;
            }
            break;
        case 0x11:
            gGbApuSquare1.unk_3B = GB_APU_REGS.duty1;
            gGbApuSquare1.unk_1C = 0x40 - GB_APU_REGS.length1;
            break;
        case 0x12:
            gGbApuSquare1.unk_21 = GB_APU_REGS.volume1;
            if ((GB_APU_REGS.volume1 == 0) && (GB_APU_REGS.envDir1 == 0)) {
                gGbApuSquare1.unk_00 = 0;
            }
            break;
        case 0x13:
            gGbApuSquare1.unk_10 = GB_APU_REGS.freqLo1 | (GB_APU_REGS.freqHi1 << 8);
            gGbApuSquare1.unk_0C = GbApu_FreqToStep2x(gGbApuSquare1.unk_10);
            break;
        case 0x14:
            gGbApuSquare1.unk_18 = GB_APU_REGS.counter1;
            gGbApuSquare1.unk_10 = GB_APU_REGS.freqLo1 | (GB_APU_REGS.freqHi1 << 8);
            gGbApuSquare1.unk_0C = GbApu_FreqToStep2x(gGbApuSquare1.unk_10);
            if ((s32)GB_APU_REGS.trigger1 == 1) {
                gGbApuSquare1.unk_14 = gGbApuSquare1.unk_1C * 200;
                gGbApuSquare1.unk_20 = D_81138B1C[gGbApuSquare1.unk_21];
                gGbApuSquare1.unk_24 = 0;
                gGbApuSquare1.unk_30 = 0;
                gGbApuSquare1.unk_2E = GB_APU_REGS.envDir1;
                gGbApuSquare1.unk_28 = GB_APU_REGS.envSweep1 * 800;
                gGbApuSquare1.unk_2D = gGbApuSquare1.unk_21;
                if (GB_APU_REGS.power) {
                    gGbApuSquare1.unk_00 = 1;
                }
            }
            if (gGbApuSquare1.unk_34 == 0) {
                gGbApuSquare1.unk_3A = 0;
            } else {
                gGbApuSquare1.unk_3A = 1;
            }
            break;
        case 0x16:
            gGbApuSquare2.unk_3B = GB_APU_REGS.duty2;
            gGbApuSquare2.unk_1C = 0x40 - GB_APU_REGS.length2;
            break;
        case 0x17:
            gGbApuSquare2.unk_21 = GB_APU_REGS.volume2;
            if ((GB_APU_REGS.volume2 == 0) && (GB_APU_REGS.envDir2 == 0)) {
                gGbApuSquare2.unk_00 = 0;
            }
            break;
        case 0x18:
            gGbApuSquare2.unk_10 = GB_APU_REGS.freqLo2 | (GB_APU_REGS.freqHi2 << 8);
            gGbApuSquare2.unk_0C = GbApu_FreqToStep2x(gGbApuSquare2.unk_10);
            break;
        case 0x19:
            gGbApuSquare2.unk_18 = GB_APU_REGS.counter2;
            gGbApuSquare2.unk_10 = GB_APU_REGS.freqLo2 | (GB_APU_REGS.freqHi2 << 8);
            gGbApuSquare2.unk_0C = GbApu_FreqToStep2x(gGbApuSquare2.unk_10);
            if ((s32)GB_APU_REGS.trigger2 == 1) {
                gGbApuSquare2.unk_14 = gGbApuSquare2.unk_1C * 200;
                gGbApuSquare2.unk_08.unk_02 = 0;
                gGbApuSquare2.unk_20 = D_81138B1C[gGbApuSquare2.unk_21];
                gGbApuSquare2.unk_24 = 0;
                gGbApuSquare2.unk_2E = GB_APU_REGS.envDir2;
                gGbApuSquare2.unk_28 = GB_APU_REGS.envSweep2 * 800;
                gGbApuSquare2.unk_2D = gGbApuSquare2.unk_21;
                if (GB_APU_REGS.power) {
                    gGbApuSquare2.unk_00 = 1;
                }
            }
            break;
        case 0x1A:
            if (GB_APU_REGS.waveOn == 0) {
                gGbApuWave.unk_00 = GB_APU_REGS.waveOn;
            }
            break;
        case 0x1B:
            gGbApuWave.unk_1C = 0x100 - GB_APU_REGS.length3;
            break;
        case 0x1C:
            gGbApuWave.unk_21 = GB_APU_REGS.level3;
            gGbApuWave.unk_20 = D_81138B2C[gGbApuWave.unk_21];
            break;
        case 0x1D:
            gGbApuWave.unk_10 = GB_APU_REGS.freqLo3 | (GB_APU_REGS.freqHi3 << 8);
            gGbApuWave.unk_0C = GbApu_FreqToStep(gGbApuWave.unk_10);
            break;
        case 0x1E:
            gGbApuWave.unk_10 = GB_APU_REGS.freqLo3 | (GB_APU_REGS.freqHi3 << 8);
            gGbApuWave.unk_0C = GbApu_FreqToStep(gGbApuWave.unk_10);
            gGbApuWave.unk_18 = GB_APU_REGS.counter3;
            if ((s32)GB_APU_REGS.trigger3 == 1) {
                gGbApuWave.unk_14 = gGbApuWave.unk_1C * 200;
                gGbApuWave.unk_04 = 0x140;
                if (GB_APU_REGS.power && ((s32)GB_APU_REGS.waveOn == 1)) {
                    gGbApuWave.unk_00 = 1;
                }
            }
            break;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
            D_81182468[(reg - 0x30) * 2 + 0] = (D_81138A80[reg - 0x10] >> 4) & 0xF;
            D_81182468[(reg - 0x30) * 2 + 1] = D_81138A80[reg - 0x10] & 0xF;
            break;
        case 0x20:
            gGbApuNoise.unk_1C = 0x40 - GB_APU_REGS.length4;
            break;
        case 0x21:
            gGbApuNoise.unk_21 = GB_APU_REGS.volume4;
            if ((GB_APU_REGS.volume4 == 0) && (GB_APU_REGS.envDir4 == 0)) {
                gGbApuNoise.unk_00 = 0;
            }
            break;
        case 0x22:
            gGbApuNoise.unk_10 = GB_APU_REGS.shift4;
            gGbApuNoise.unk_0C = func_811158F4(GB_APU_REGS.shift4, GB_APU_REGS.width4, GB_APU_REGS.ratio4);
            if (gGbApuNoise.unk_00 == 0) {
                gGbApuNoise.unk_40 = gGbApuNoise.unk_0C;
            }
            if (gGbApuNoise.unk_40 < gGbApuNoise.unk_0C) {
                gGbApuNoise.unk_48 = gGbApuNoise.unk_0C - gGbApuNoise.unk_40;
            } else {
                gGbApuNoise.unk_48 = gGbApuNoise.unk_40 - gGbApuNoise.unk_0C;
            }
            gGbApuNoise.unk_48 >>= 7;
            if (gGbApuNoise.unk_48 == 0) {
                gGbApuNoise.unk_48 = 1;
            }
            break;
        case 0x23:
            gGbApuNoise.unk_18 = GB_APU_REGS.counter4;
            if ((s32)GB_APU_REGS.trigger4 == 1) {
                gGbApuNoise.unk_14 = gGbApuNoise.unk_1C * 200;
                if (gGbApuNoise.unk_00 == 0) {
                    gGbApuNoise.unk_08.unk_02 = 0;
                }
                gGbApuNoise.unk_2D = gGbApuNoise.unk_21;
                switch ((s32)GB_APU_REGS.width4) {
                    case 0:
                        gGbApuNoise.unk_20 = D_81138B30[gGbApuNoise.unk_2D];
                        break;
                    case 1:
                        gGbApuNoise.unk_20 = D_81138B40[gGbApuNoise.unk_2D];
                        break;
                }
                if ((gGbApuNoise.unk_00 == 0) || (gGbApuNoise.unk_3C < gGbApuNoise.unk_20)) {
                    gGbApuNoise.unk_3C = gGbApuNoise.unk_20;
                }
                gGbApuNoise.unk_24 = 0;
                gGbApuNoise.unk_2E = GB_APU_REGS.envDir4;
                gGbApuNoise.unk_28 = GB_APU_REGS.envSweep4 * 800;
                if (GB_APU_REGS.power) {
                    gGbApuNoise.unk_00 = 1;
                }
            }
            break;
        case 0x26:
            if (!(value & 0x80)) {
                gGbApuSquare1.unk_00 = 0;
                gGbApuSquare2.unk_00 = 0;
                gGbApuWave.unk_00 = 0;
                gGbApuNoise.unk_00 = 0;
            }
            break;
    }
}

void func_81116C88(s32 numSamples, s16* out) {
    s32 i;
    u32 sq1R;
    u32 sq1L;
    u32 sq2R;
    u32 sq2L;
    u32 waveR;
    u32 waveL;
    u32 noiseR;
    u32 noiseL;
    u32 right;
    u32 left;
    s32 sq1;
    s32 sq2;
    GbApuWrite msg;
    s32 wave;
    s32 noise;
    s32 count;
    s32 idx;
    f32 step;
    f32 pos;
    s32 flush;
    s32 first;
    s32 startTime;
    u32 lastTime;
    s32 pad[3];

    first = TRUE;
    count = 0;
    idx = 0;
    lastTime = 0;
    while (TRUE) {
        if (osRecvMesg(&D_811824C0, (OSMesg*)&msg, OS_MESG_NOBLOCK) == -1) {
            break;
        }
        if (first) {
            startTime = msg.time;
            first = FALSE;
        }
        if (msg.time < lastTime) {
            if (startTime < D_81138AD8) {
                osJamMesg(&D_811824C0, *(OSMesg*)&msg, OS_MESG_NOBLOCK);
                break;
            }
            startTime = 0;
            D_81180848[count++] = msg;
            lastTime = msg.time;
        } else {
            D_81180848[count++] = msg;
            lastTime = msg.time;
        }
    }

    pos = 0.0f;
    step = 17784.0f / (f32)numSamples;
    if (numSamples < count) {
        flush = TRUE;
    } else {
        flush = FALSE;
    }

    for (i = 0; i < numSamples; i++) {
        pos += step;
        if (flush) {
            while (TRUE) {
                if (count == 0) {
                    break;
                }
                if (((s32)pos & 0xFFFF) < D_81180848[idx].time) {
                    break;
                }
                func_811164CC(D_81180848[idx].reg, D_81180848[idx].value);
                count--;
                idx++;
            }
        } else if ((count != 0) && (((s32)pos & 0xFFFF) >= D_81180848[idx].time)) {
            func_811164CC(D_81180848[idx].reg, D_81180848[idx].value);
            count--;
            idx++;
        }

        sq1 = GbApu_UpdateSquare1Channel();
        sq2 = GbApu_UpdateSquare2Channel();
        wave = GbApu_UpdateWaveChannel();
        noise = func_81116258();

        noiseL = GB_APU_REGS.noiseLeft ? noise : 0;
        noiseR = GB_APU_REGS.noiseRight ? noise : 0;
        waveL = GB_APU_REGS.waveLeft ? wave : 0;
        waveR = GB_APU_REGS.waveRight ? wave : 0;
        sq2L = GB_APU_REGS.sq2Left ? sq2 : 0;
        sq2R = GB_APU_REGS.sq2Right ? sq2 : 0;
        sq1L = GB_APU_REGS.sq1Left ? sq1 : 0;
        sq1R = GB_APU_REGS.sq1Right ? sq1 : 0;

        right = (sq1R + sq2R + waveR + noiseR) / (8 - GB_APU_REGS.rightVolume);
        left = (sq1L + sq2L + waveL + noiseL) / (8 - GB_APU_REGS.leftVolume);
        if (right >= 0x8000) {
            right = 0x7FFF;
        }
        if (left >= 0x8000) {
            left = 0x7FFF;
        }
        out[i * 2 + 0] = left;
        out[i * 2 + 1] = right;
    }

    while (count != 0) {
        func_811164CC(D_81180848[idx].reg, D_81180848[idx].value);
        count--;
        idx++;
    }

    D_811824B8.unk_00 = 0;
    D_811824B8.unk_01 = 0;
    D_811824B8.unk_02 = 0;
    D_811824B8.unk_03 = 0;
}

void func_81117068(u16 arg0, u8 arg1, u16 arg2) {
    s32 temp_v1;

    temp_v1 = arg0 + 0xFFFF0100;
    osSendMesg(&D_811824C0, (temp_v1 << 0x18) | (arg1 << 0x10) | arg2, 0);
    D_81138AD8 = (s32) arg2;
    switch (temp_v1) {
    case 20:
        if (arg1 & 0x80) {
            D_811824B8.unk_00 = 2;
            return;
        }
    default:
        return;
    case 25:
        if (arg1 & 0x80) {
            D_811824B8.unk_01 = 2;
            return;
        }
        break;
    case 30:
        if (arg1 & 0x80) {
            D_811824B8.unk_02 = 2;
            return;
        }
        break;
    case 35:
        if (arg1 & 0x80) {
            D_811824B8.unk_03 = 2;
            return;
        }
        break;
    case 38:
        if (!(arg1 & 1)) {
            D_811824B8.unk_00 = 1;
        }
        if (!(arg1 & 2)) {
            D_811824B8.unk_01 = 1;
        }
        if (!(arg1 & 4)) {
            D_811824B8.unk_02 = 1;
        }
        if (!(arg1 & 8)) {
            D_811824B8.unk_03 = 1;
        }
        if (!(arg1 & 0x80)) {
            D_811824B8.unk_00 = 1;
            D_811824B8.unk_01 = 1;
            D_811824B8.unk_02 = 1;
            D_811824B8.unk_03 = 1;
        }
        break;
    }
}

void GbApu_ResetChannels(void) {
  s32 pad[6];
  s32 i;
  OSMesgQueue sp24;
  OSMesg sp20;

  osCreateMesgQueue(&sp24, &sp20, 1);
  osCreateMesgQueue(&D_811824C0, D_811824D8, GB_APU_WRITE_QUEUE_LEN);
  for (i = 0x50; i > 0xF; i--) {
      func_811164CC(i, 0);
  }
  gGbApuSquare1.unk_3C = 0;
  gGbApuSquare2.unk_3C = 0;
  gGbApuWave.unk_3C = 0;
  gGbApuNoise.unk_3C = 0;
  gGbApuSquare1.unk_08.unk_02 = 0;
  gGbApuSquare2.unk_08.unk_02 = 0;
  gGbApuWave.unk_08.unk_02 = 0;
  gGbApuNoise.unk_08.unk_02 = 0;
}

void GbApu_Reset(s32 arg0) {
  D_81180704 = arg0;
  GbApu_ResetChannels();
}

void func_811172AC(void) {
    void* sp34 = D_811859B8[0];
    f32 x = (f32) D_81180700;
    f32 y = (f32) D_81180702;
    f32 dx = x / 640.0f;
    f32 dy = y / 640.0f;
    s32 i;
    s32 idx;

    GbApu_ResetChannels();
    for (i = 0, idx = 0; i != 0x280; i++) {
        ((s16*)sp34)[idx + 0] = x;
        ((s16*)sp34)[idx + 1] = y;
        x -= dx;
        y -= dy;
        idx += 2;
    }
     do {
     } while (osAiGetStatus() & 0x80000000);
    osWritebackDCache(sp34, 0xA00);
    osGbSetNextBuffer(sp34, 0xA00);
}

void func_811173F4(void) {
}

u8 GbMem_ReadIoRegister(u16 arg0) {
  u8 var_a0;
  u8 var_a1;
  u8 var_a2;
  u8 var_v1;
  u8 temp;
  if ((arg0 & 0xFFFF) == 0xFF26) {
      if (D_811824B8.unk_00 != 0) {
          var_v1 = (D_811824B8.unk_00 - 1) & 0xFF;
      } else {
          var_v1 = gGbApuSquare1.unk_00;
      }
      if (D_811824B8.unk_01 != 0) {
          var_a0 = (D_811824B8.unk_01 - 1) & 0xFF;
      } else {
          var_a0 = gGbApuSquare2.unk_00;
      }
      if (D_811824B8.unk_02 != 0) {
          var_a1 = (D_811824B8.unk_02 - 1) & 0xFF;
      } else {
          var_a1 = gGbApuWave.unk_00;
      }
      if (D_811824B8.unk_03 != 0) {
          var_a2 = (D_811824B8.unk_03 - 1) & 0xFF;
      } else {
          var_a2 = gGbApuNoise.unk_00;
      }
      temp = ((((u32)D_81138A96 >> 0xF) << 7) | (var_a2 * 8) | (var_a1 * 4) | (var_a0 * 2) | var_v1);
      return temp;
  }
  return gGbMemoryMap[arg0 & 0xFFFF];
}

s32 func_811174D8(void) {
    u32 aiLen;
    s32 n;
    s32 idx;
    s32 status;
    s16* queued;
    s16* buf;
    s32 pad[2];
    s16* len;
    s16** bufPtr;

    D_811858F0++;
    osSendMesg(D_812896A0_jp, (OSMesg)D_811858F0, OS_MESG_NOBLOCK);
    D_811858F8 ^= 1;
    D_811858FC++;
    D_811858FC %= 3;
    idx = (D_811858FC + 2) % 3;
    aiLen = osAiGetLength() >> 2;

    if (D_811859D4 < 16) {
        len = &D_811859C4[idx];
        if (*len != 0) {
            bufPtr = &D_811859B8[idx];
            if (osGbSetNextBuffer(*bufPtr, *len * 4) == -1) {
                status = 0;
            } else {
                queued = *bufPtr;
                n = *len;
                D_81180700 = queued[n * 2 - 2];
                D_81180702 = queued[n * 2 - 1];
                status = 2;
            }
            // Discarded reads; they only steer IDO's register allocation.
            if (status) {}
            if (bufPtr) {}
        }
    }

    if (D_811859D4 > 16) {
        return 0;
    }
    if (D_811859D4 != 0) {
        D_811859D4++;
    }

    idx = D_811858FC;
    bufPtr = &D_811859B8[idx];
    len = &D_811859C4[idx];
    buf = *bufPtr;
    *len = ((D_811858B8.unk_06 - aiLen + 0x80) & 0xFFF0) + 0x10;
    if (*len < D_811858B8.unk_0A) {
        *len = D_811858B8.unk_0A;
    }
    if (D_811858B8.unk_08 < *len) {
        *len = D_811858B8.unk_08;
    }
    if (D_81138B80 == 0) {
        func_81116C88(*len, buf);
    } else {
        func_811177E8(*len, buf);
    }
    osWritebackDCache(buf, *len * 4);
    D_811859CC = osGetCount() * (D_811859CC + D_811858F0);
    D_811859CC = D_811859B8[idx][D_811858F0 & 0xFF] + D_811859CC;
    return 0;
}

void GbAudio_SetAlternateRendererEnabled(s32 arg0) {
  D_81138B80 = arg0;
}

void GbAudio_SetAlternateStreamId(s32 arg0) {
  D_81138B84.id = arg0;
}

#ifdef NON_MATCHING
// Matches the ROM, but uses data data that is not placed in this file yet.
void func_811177E8(s32 numSamples, s16* out) {
    static u32 D_8122869C = 0;

    s32 i;
    s8* mainData;
    s8* altData;
    s32 a;
    s32 b;
    s32 mainEnd;
    s32 altEnd;

    mainData = NULL;
    altData = NULL;
    if (D_81138B84.id != 0) {
        D_81138B94 = D_81138B8C;
        D_81138B8C = D_81138B84;
        D_81138B8C.pos = 0;
        D_81138B84.id = 0;
        D_8122869C = 0x400;
    }
    if (D_81138B8C.id != 0) {
        mainData = GB_AUDIO_STREAM_DATA[D_81138B8C.id];
        mainEnd = GB_AUDIO_STREAM_SIZE[D_81138B8C.id];
    }
    i = D_81138B94.id;
    if (i != 0) {
        altData = GB_AUDIO_STREAM_DATA[i];
        altEnd = GB_AUDIO_STREAM_SIZE[i];
    }

    for (i = 0; i < numSamples; i++) {
        if (mainData != NULL) {
            if (mainEnd == D_81138B8C.pos) {
                D_81138B8C.id = 0;
                mainData = NULL;
                a = 0;
            } else {
                a = mainData[D_81138B8C.pos++];
            }
        } else {
            a = 0;
        }
        if (altData != NULL) {
            if (altEnd == D_81138B94.pos) {
                D_81138B94.id = 0;
                altData = NULL;
                b = 0;
            } else {
                b = altData[D_81138B94.pos++];
                b = (s32)(b * D_8122869C) / 1024;
            }
        } else {
            b = 0;
        }
        ((GbStereoSample*)out)[i].left = (a + b) << 6;
        ((GbStereoSample*)out)[i].right = (a - b) << 6;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811177E8.s")
#endif

void func_81117AFC(UNUSED s32 arg0) {
}

// Second empty handler; in the Japanese build this file's .text ends here (0x81218110).
void func_81218104_jp(UNUSED s32 arg0) {
}
