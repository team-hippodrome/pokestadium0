/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gb_audio_render.c. */

#include "gb_audio_render.h"
#include "audio_commands.h"
#include "rom_device.h"
/* Emulated Game Boy sound registers. Each register is a value byte followed by a dirty byte. */
typedef struct GbSoundRegisters {
    /* 0x00 */ u16 regs[20]; /* NR10-NR44 (0xFF10-0xFF23): value byte, dirty byte */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x28 */ u8 nr50; /* master volume */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x29 */ u8 nr50Dirty; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x2A */ u8 nr51; /* panning */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x2B */ char unk2B[1];
    /* 0x2C */ u8 nr52; /* sound on/off; bits 0-3 are the channel-on flags */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x2D */ char unk2D[0x13];
    /* 0x40 */ u16 waveRam[16]; /* wave pattern RAM (0xFF30-0xFF3F): value byte, dirty byte */ /* @unverified: register 0x20 on in the 48-register reset loop of func_80044BA8 */
} GbSoundRegisters; // size = 0x60
#define GB_REG(n) (((u8*)&D_800FD7E8.regs[n])[0])
#define GB_REG_DIRTY(n) (((u8*)&D_800FD7E8.regs[n])[1])
/* A queued register write, applied when the renderer reaches its sample time. */
typedef struct GbSoundRegWrite {
    /* 0x00 */ u8* reg; /* value byte in D_800FD7E8.regs */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x04 */ u8 value; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x06 */ u16 time; /* sample time + 1; 0 ends the queue */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
} GbSoundRegWrite; // size = 0x08
/* Noise (channel 4) renderer state: plays a sampled noise clip. */
typedef struct GbSynthNoise {
    /* 0x00 */ u32 time; /* sample clock, +0x100 per sample */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x04 */ u8 sampleId; /* GbNoiseSampleEntry index, 0xFF = none */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x05 */ u8 pad05[0x3];
    /* 0x08 */ u32 sampleIndex; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x0C */ f32 pitchStep; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x10 */ f32 pitchAccum; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x14 */ f32 volume; /* capped at 0.75 */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x18 */ f32 envelopeStep; /* +-0.05 per envelope period (NR42) */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x1C */ u32 envelopePeriod; /* -1 = off */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x20 */ u32 nextEnvelopeTime; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x24 */ u32 lengthEnd; /* -1 = no length limit (NR41/NR44) */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x28 */ u8 enabled; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
} GbSynthNoise; // size = 0x2C
/* Square 2 (channel 2) renderer state: square 1 without the sweep. */
typedef struct GbSynthSquare2 {
    /* 0x00 */ u32 time; /* sample clock */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x04 */ s16 volume; /* envelope level, capped at 0x7800 */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x06 */ s16 envelopeStep; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x08 */ u32 envelopePeriod; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x0C */ u32 nextEnvelopeTime; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x10 */ u16 halfPeriods[2]; /* high and low lengths from the NR21 duty */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 phase; /* index into halfPeriods */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x18 */ u32 nextPhaseTime; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x1C */ u32 period; /* from the NR23/NR24 frequency */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x20 */ u32 lengthEnd; /* -1 = no length limit */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x24 */ u8 enabled; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
} GbSynthSquare2; // size = 0x28
/* Wave (channel 3) renderer state. Only reset here. */
typedef struct GbSynthWave {
    /* 0x00 */ u32 time; /* @unverified: reset with enabled, like the other channels' clocks */
    /* 0x04 */ u8 unk04[0x18];
    /* 0x1C */ u8 enabled; /* @unverified: reset with time, like the other channels' flags */
} GbSynthWave; // size = 0x20
/* Square 1 (channel 1) renderer state, with the NR10 frequency sweep. */
typedef struct GbSynthSquare1 {
    /* 0x00 */ u32 time; /* sample clock, +0x40 per sample */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x04 */ u16 frequency; /* 11-bit NR13/NR14 value, swept */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x06 */ char pad06[0x2];
    /* 0x08 */ u32 sweepPeriod; /* from NR10 bits 4-6, -1 = off */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x0C */ s16 volume; /* envelope level, capped at 0x7800 */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x0E */ s16 envelopeStep; /* +-0x800 (NR12 direction) */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x10 */ u32 envelopePeriod; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x14 */ u32 nextEnvelopeTime; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x18 */ u16 halfPeriods[2]; /* high and low lengths from the NR11 duty */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ u8 phase; /* index into halfPeriods */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x1F */ char pad1F[0x1];
    /* 0x20 */ u32 nextPhaseTime; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x24 */ u32 period; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x28 */ u32 lengthEnd; /* -1 = no length limit */ /* @unverified: from the code (Game Boy APU, NR10-NR52) */
    /* 0x2C */ u8 enabled; /* @unverified: from the code (Game Boy APU, NR10-NR52) */
} GbSynthSquare1; // size = 0x30
extern GbSynthSquare1 D_800FD740;
extern GbSynthSquare2 D_800FD770;
extern GbSynthWave D_800FD798;
extern GbSynthNoise D_800FD7B8;
extern u32 D_800FD7E4;
extern GbSoundRegisters D_800FD7E8;
extern GbSoundRegWrite D_800FD848[199];
extern u8 D_800FDE80[8];
extern u32 D_800FDE88;
extern u32 D_800FDE8C;
extern u8 D_800FDEC0;
extern u8 D_800FDEC1;
extern f32 D_800FDEC4;
extern s32 D_800FDEC8;
extern u32 D_800FDED0;
extern u32 D_800FDED4;
extern s16 D_800FDED8[0x1140];
extern u32 D_80100158;
extern u8 D_8010015C;
extern s32 D_80100160;
typedef struct GbNoiseEntry {
    /* 0x0 */ u8 sampleId;
    /* 0x4 */ f32 pitchStep;
} GbNoiseEntry;
#define GB_NOISE_TABLE ((GbNoiseEntry(*)[16])D_800775B0)
void func_80044D60(u32);
void GbAudio_ClearInterpolationHistory();
void GbAudio_ClearOutputBuffer();
extern u32 D_800775B0[0x100];
extern u8 sLoopPointTable[0x3C];
extern s32 D_80087B80;
void GbAudio_ApplyQueuedWrites(u16);
s16 func_800450F0(void);
s16 func_80045774(void);
s16 func_80045B9C(void);

void GbAudio_GenerateSamples(s16* arg0, s32 arg1, u32 arg2, f32 arg3);
void GbAudio_QueueRegisterWrite(u16 arg0, u8 arg1, u16 arg2);
u8 GbAudio_GetRegisterValue(u16 arg0);
void func_80044BA8(u32 arg0, u8 arg1, u32 arg2);
void func_80044D60(u32 arg0);
void GbAudio_ApplyQueuedWrites(u16 arg0);
s16 func_800450F0(void);
s16 func_80045774(void);
s16 func_80045B9C(void);
void GbAudio_ClearInterpolationHistory(void);
void GbAudio_ClearOutputBuffer(void);
void func_8004602C(void);

/** Generates emulated Game Boy audio samples. */
void GbAudio_GenerateSamples(s16* arg0, s32 arg1, u32 arg2, f32 arg3) {
    func_80044D60(arg2);
}

/** Queues a write to an emulated Game Boy sound register. */
void GbAudio_QueueRegisterWrite(u16 arg0, u8 arg1, u16 arg2) {
    D_800FD848[D_800FDE8C].reg = (u8*)&D_800FD7E8.regs[(arg0 & 0xFF) - 0x10];
    D_800FD848[D_800FDE8C].value = arg1;
    D_800FD848[D_800FDE8C].time = arg2 + 1;
    D_800FDE80[arg0 & 0xFF] = arg1;
    D_800FDE8C++;
    D_800FDE8C %= 200;
    D_800FD848[D_800FDE8C].time = 0;
}

/** Returns the last value written to an emulated Game Boy sound register. */
u8 GbAudio_GetRegisterValue(u16 arg0) {
    return D_800FDE80[arg0 & 0xFF];
}

void func_80044BA8(u32 arg0, u8 arg1, u32 arg2) {
    u32 temp_t3;
    u8* p;
    s32 i;
    D_800FD7E4 = arg0 >> 1;
    D_800FDEC4 = 1048576.0f / (f32) D_800FD7E4;

    p = (u8*) &D_800FD7E8;
    for (i = 0; i < 48; i++) {
       p[i * 2 + 1] = 1;
    }
    p = (u8*) &D_800FD7E8;
    p[0x00] = 8;
    p[0x02] = 0;
    p[0x04] = 0;
    p[0x06] = 0;
    p[0x08] = 0x40;
    p[0x0C] = 0;
    p[0x0E] = 0;
    p[0x10] = 0;
    p[0x12] = 0x40;
    p[0x14] = 0;
    p[0x16] = 0;
    p[0x18] = 0;
    p[0x1A] = 0;
    p[0x1C] = 0x40;
    p[0x20] = 0;
    p[0x22] = 0;
    p[0x24] = 0;
    p[0x26] = 0x40;
    p[0x28] = 0;
    p[0x2A] = 0;
    p[0x2C] = 0;

    p = (u8*) D_800FD7E8.waveRam;
    for (i = 0; i < 16; i++) {
        p[i * 2] = 0;
    }
    D_800FDE8C = 0;
    D_800FD848[0].time = 0;
    D_800FDE88 = 0;
    D_800FD740.time = 0;
    D_800FD740.enabled = 0;

    D_800FD770.time = 0;
    D_800FD770.enabled = 0;

    D_800FD798.time = 0;
    D_800FD798.enabled = 0;

    D_800FD7B8.time = 0;
    D_800FD7B8.enabled = 0;
    D_800FD7B8.sampleId = 0xFF;

    GbAudio_ClearOutputBuffer();
    GbAudio_ClearInterpolationHistory();

    D_8010015C = arg1;
    D_80100160 = arg2;
    D_80100160 *= 2;
    if (D_80100160 >= 0x1141U) {
        D_80100160 = 0x1140;
    }
    D_800FDEC8 = 2;
}

void func_80044D60(u32 arg0) {
    s32 pad[3]; // FAKE: stack padding
    s16 sp4C[4];
    u32 i;
    f32 var_fs0;
    s16 var_a0;
    s32 var_s4;
    s16 tmp;
    u8 var_t;

    var_fs0 = 0.0f;
    var_s4 = 1;
    arg0 >>= 1;

    var_t = D_800FDEC1;
    var_a0 = ((var_t & 1) ? -1 : 0) + ((var_t & 2) ? -1 : 0) + ((var_t & 8) ? -1 : 0);

    if (D_800FDED4 < D_800FDED0) {
        if ((0xB80 - (arg0 * 4)) < (D_800FDED0 - D_800FDED4)) {
            arg0++;
        }
    } else if ((D_800FDED4 - D_800FDED0) < (arg0 * 4)) {
        arg0++;
    }

    for (i = 0; i < arg0; i++) {
        if (var_fs0 <= i) {
            GbAudio_ApplyQueuedWrites(var_s4);
        }

        if (D_800FD7E8.nr52 & 0x80) {
            if (D_800FD7E8.nr50Dirty != 0) {
                D_800FDEC0 = D_800FD7E8.nr50 & 7;
                D_800FDEC1 = (D_800FD7E8.nr50 & 0x70) >> 4;
                D_800FD7E8.nr50Dirty = 0;
            }

            sp4C[0] = func_800450F0();
            sp4C[1] = func_80045774();
            sp4C[3] = func_80045B9C();

            var_t = D_800FD7E8.nr51;
            var_a0 =
                ((u32)((sp4C[0] & ((var_t & 1) ? -1 : 0)) + (sp4C[1] & ((var_t & 2) ? -1 : 0)) +
                       (sp4C[3] & ((var_t & 8) ? -1 : 0))) >>
                 5) *
                (D_800FDEC0 + 1);
        } else {
            var_a0 = 0;
        }

        if (D_8010015C != 0) {
            if (1) {}  // karodo
            if (1) {}  // karodo
            if (1) {}  // karodo
            if (1) {}  // karodo
            tmp = (f32)D_800FDED8[((D_80100158 - D_80100160) + 0x1140) % 4416];

            var_a0 += (s16)(((tmp - var_a0) * D_8010015C) >> 8);
            D_800FDED8[D_80100158++] = var_a0;
            if (D_80100158 >= 0x1140) {
                D_80100158 -= 0x1140;
            }
        }

        D_800B41EC[D_800FDED4 + 0] = var_a0;
        D_800B41EC[D_800FDED4 + 1] = var_a0;

        D_800FDED4 += 2;
        if (D_800FDED4 >= 0xB80) {
            D_800FDED4 -= 0xB80;
        }

        var_s4++;
        var_fs0 += D_800FDEC4;
    }
}

/** Applies the queued register writes that are due. */
void GbAudio_ApplyQueuedWrites(u16 arg0) {
    while (D_800FD848[D_800FDE88].time >= arg0) {
        D_800FD848[D_800FDE88].reg[0] = D_800FD848[D_800FDE88].value;
        D_800FD848[D_800FDE88].reg[1] = 1;
        D_800FDE88++;
        if (D_800FDE88 >= 0xC8) {
            D_800FDE88 -= 0xC8;
        }
    }
}

s16 func_800450F0(void) {
    s32 i;
    s32 changed;
    s32 nr14;
    u8 phase;
    u16 freq;
    s16 out;

    changed = 0;
    for (i = 0; i < 5; i++) {
        if (GB_REG_DIRTY(i) != 0) {
            changed = 1;
            GB_REG_DIRTY(i) = 0;
        }
    }

    if (changed) {
        nr14 = GB_REG(4);
        D_800FD740.frequency = GB_REG(3) | (((u8)nr14 & 7) << 8);
        D_800FD740.period = ((0x800 - D_800FD740.frequency) * D_800FD7E4) >> 11;
        switch ((GB_REG(1) & 0xC0) >> 6) {
            case 0:
                D_800FD740.halfPeriods[1] = D_800FD740.period >> 3;
                if (D_800FD740.halfPeriods[1] < 0x40) {
                    D_800FD740.halfPeriods[1] = 0x40;
                }
                phase = 1;
                D_800FD740.halfPeriods[0] = D_800FD740.period - D_800FD740.halfPeriods[1];
                goto duty_done;
            case 1:
                D_800FD740.halfPeriods[1] = D_800FD740.period >> 2;
                if (D_800FD740.halfPeriods[1] < 0x40) {
                    D_800FD740.halfPeriods[1] = 0x40;
                }
                phase = 0;
                D_800FD740.halfPeriods[0] = D_800FD740.period - D_800FD740.halfPeriods[1];
                goto duty_done;
            case 2:
                D_800FD740.halfPeriods[1] = D_800FD740.period >> 1;
                if (D_800FD740.halfPeriods[1] < 0x40) {
                    D_800FD740.halfPeriods[1] = 0x40;
                }
                phase = 0;
                D_800FD740.halfPeriods[0] = D_800FD740.period - D_800FD740.halfPeriods[1];
                goto duty_done;
            case 3:
                D_800FD740.halfPeriods[0] = D_800FD740.period >> 2;
                if (D_800FD740.halfPeriods[0] < 0x40) {
                    D_800FD740.halfPeriods[0] = 0x40;
                }
                phase = 1;
                D_800FD740.halfPeriods[1] = D_800FD740.period - D_800FD740.halfPeriods[0];
                goto duty_done;
        }
        D_800FD740.halfPeriods[1] = 0;
        phase = 1;
        D_800FD740.halfPeriods[0] = D_800FD740.period;
    duty_done:

        if (!(GB_REG(2) & 8) && !(GB_REG(2) & 0xF0)) {
            D_800FD740.enabled = 0;
            D_800FD7E8.nr52 &= 0xFFFE;
            return 0;
        }
        if ((GB_REG(2) & 8) && !(GB_REG(2) & 0xF0) && !(GB_REG(2) & 7)) {
            D_800FD740.enabled = 0;
            D_800FD7E8.nr52 &= 0xFFFE;
            return 0;
        }

        if (nr14 & 0x80) {
            D_800FD740.time = 0;
            D_800FD740.enabled = 1;
            D_800FD740.phase = phase;
            D_800FD740.unk_1C = 0;
            D_800FD740.nextPhaseTime = 0;
            D_800FD740.volume = (u8)(GB_REG(2) & 0xF0) << 7;
            if (GB_REG(2) & 7) {
                if (GB_REG(2) & 8) {
                    D_800FD740.envelopeStep = 0x800;
                } else {
                    D_800FD740.envelopeStep = -0x800;
                }
                D_800FD740.nextEnvelopeTime = D_800FD740.envelopePeriod = (GB_REG(2) & 7) * D_800FD7E4;
            } else {
                D_800FD740.envelopeStep = 0;
                D_800FD740.envelopePeriod = -1;
                D_800FD740.nextEnvelopeTime = -1;
            }
            D_800FD740.sweepPeriod = (((GB_REG(0) & 0x70) >> 4) * D_800FD7E4) >> 1;
            if (D_800FD740.sweepPeriod == 0) {
                D_800FD740.sweepPeriod = -1;
            }
            if (nr14 & 0x40) {
                D_800FD740.lengthEnd = ((0x40 - (GB_REG(1) & 0x3F)) * D_800FD7E4) >> 2;
            } else {
                D_800FD740.lengthEnd = -1;
            }
            GB_REG(4) = nr14 & ~0x80;
        }
        if (D_800FD740.enabled == 0) {
            return 0;
        }
    } else if (D_800FD740.enabled == 0) {
        return 0;
    }

    if (D_800FD740.lengthEnd < D_800FD740.time) {
        D_800FD740.enabled = 0;
        D_800FD7E8.nr52 &= 0xFFFE;
        return 0;
    }

    if ((D_800FD740.sweepPeriod - (D_800FD740.time % D_800FD740.sweepPeriod)) <= 0x40) {
        if (!(GB_REG(0) & 8)) {
            freq = (D_800FD740.frequency + (D_800FD740.frequency >> (GB_REG(0) & 7)));
            if (freq >= 0x800) {
                D_800FD740.enabled = 0;
                D_800FD7E8.nr52 &= 0xFFFE;
                return 0;
            }
            D_800FD740.frequency = freq;
        } else {
            freq = (D_800FD740.frequency - (D_800FD740.frequency >> (GB_REG(0) & 7)));
            if ((freq >= 0x800) || (freq < 0)) {
                goto skip;
            }
            D_800FD740.frequency = freq;
        }
        D_800FD740.period = ((0x800 - D_800FD740.frequency) * D_800FD7E4) >> 11;
        switch ((GB_REG(1) & 0xC0) >> 6) {
            case 0:
                D_800FD740.halfPeriods[1] = D_800FD740.period >> 3;
                if (D_800FD740.halfPeriods[1] < 0x40) {
                    D_800FD740.halfPeriods[1] = 0x40;
                }
                D_800FD740.halfPeriods[0] = D_800FD740.period - D_800FD740.halfPeriods[1];
                break;
            case 1:
                D_800FD740.halfPeriods[1] = D_800FD740.period >> 2;
                if (D_800FD740.halfPeriods[1] < 0x40) {
                    D_800FD740.halfPeriods[1] = 0x40;
                }
                D_800FD740.halfPeriods[0] = D_800FD740.period - D_800FD740.halfPeriods[1];
                break;
            case 2:
                D_800FD740.halfPeriods[1] = D_800FD740.period >> 1;
                if (D_800FD740.halfPeriods[1] < 0x40) {
                    D_800FD740.halfPeriods[1] = 0x40;
                }
                D_800FD740.halfPeriods[0] = D_800FD740.period - D_800FD740.halfPeriods[1];
                break;
            case 3:
                D_800FD740.halfPeriods[0] = D_800FD740.period >> 2;
                if (D_800FD740.halfPeriods[0] < 0x40) {
                    D_800FD740.halfPeriods[0] = 0x40;
                }
                D_800FD740.halfPeriods[1] = D_800FD740.period - D_800FD740.halfPeriods[0];
                break;
            default:
                D_800FD740.halfPeriods[1] = 0;
                D_800FD740.halfPeriods[0] = D_800FD740.period;
        }
    }
skip:

    if (D_800FD740.nextEnvelopeTime < D_800FD740.time) {
        D_800FD740.volume += D_800FD740.envelopeStep;
        D_800FD740.nextEnvelopeTime += D_800FD740.envelopePeriod;
    }
    while (D_800FD740.nextPhaseTime < D_800FD740.time) {
        D_800FD740.phase ^= 1;
        D_800FD740.nextPhaseTime += D_800FD740.halfPeriods[D_800FD740.phase];
    }

    if (!(GB_REG(2) & 8) && (D_800FD740.volume < 0)) {
        D_800FD740.enabled = 0;
        return 0;
    }
    if ((u16)D_800FD740.volume > 0x7800) {
        D_800FD740.volume = 0x7800;
        D_800FD740.envelopeStep = 0;
        D_800FD740.nextEnvelopeTime = -1;
    }
    out = D_800FD740.volume;
    if (D_800FD740.phase == 0) {
        out = -out;
    }
    D_800FD740.time += 0x40;
    return out;
}

s16 func_80045774(void) {
    s32 i;
    s32 changed;
    s32 nr24;
    u8 phase;
    s16 out;

    changed = 0;
    for (i = 6; i < 10; i++) {
        if (GB_REG_DIRTY(i) != 0) {
            changed = 1;
            GB_REG_DIRTY(i) = 0;
        }
    }

    if (changed) {
        nr24 = GB_REG(9);
        D_800FD770.period = ((0x800 - (GB_REG(8) | (((u8)nr24 & 7) << 8))) * D_800FD7E4) >> 11;
        switch ((GB_REG(6) & 0xC0) >> 6) {
            case 0:
                D_800FD770.halfPeriods[1] = D_800FD770.period >> 3;
                if (D_800FD770.halfPeriods[1] < 0x40) {
                    D_800FD770.halfPeriods[1] = 0x40;
                }
                phase = 1;
                D_800FD770.halfPeriods[0] = D_800FD770.period - D_800FD770.halfPeriods[1];
                goto duty_done;
            case 1:
                D_800FD770.halfPeriods[1] = D_800FD770.period >> 2;
                if (D_800FD770.halfPeriods[1] < 0x40) {
                    D_800FD770.halfPeriods[1] = 0x40;
                }
                phase = 0;
                D_800FD770.halfPeriods[0] = D_800FD770.period - D_800FD770.halfPeriods[1];
                goto duty_done;
            case 2:
                D_800FD770.halfPeriods[1] = D_800FD770.period >> 1;
                if (D_800FD770.halfPeriods[1] < 0x40) {
                    D_800FD770.halfPeriods[1] = 0x40;
                }
                phase = 0;
                D_800FD770.halfPeriods[0] = D_800FD770.period - D_800FD770.halfPeriods[1];
                goto duty_done;
            case 3:
                D_800FD770.halfPeriods[0] = D_800FD770.period >> 2;
                if (D_800FD770.halfPeriods[0] < 0x40) {
                    D_800FD770.halfPeriods[0] = 0x40;
                }
                phase = 1;
                D_800FD770.halfPeriods[1] = D_800FD770.period - D_800FD770.halfPeriods[0];
                goto duty_done;
        }
        D_800FD770.halfPeriods[1] = 0;
        phase = 1;
        D_800FD770.halfPeriods[0] = D_800FD770.period;
    duty_done:

        if (!(GB_REG(7) & 8) && !(GB_REG(7) & 0xF0)) {
            D_800FD770.enabled = 0;
            D_800FD7E8.nr52 &= 0xFFFD;
            return 0;
        }
        if ((GB_REG(7) & 8) && !(GB_REG(7) & 0xF0) && !(GB_REG(7) & 7)) {
            D_800FD770.enabled = 0;
            D_800FD7E8.nr52 &= 0xFFFD;
            return 0;
        }

        if (nr24 & 0x80) {
            D_800FD770.time = 0;
            D_800FD770.enabled = 1;
            D_800FD770.phase = phase;
            D_800FD770.unk_14 = 0;
            D_800FD770.nextPhaseTime = 0;
            D_800FD770.volume = ((GB_REG(7) & 0xF0) << 3) << 4;
            if (GB_REG(7) & 7) {
                if (GB_REG(7) & 8) {
                    D_800FD770.envelopeStep = 0x800;
                } else {
                    D_800FD770.envelopeStep = -0x800;
                }
                D_800FD770.nextEnvelopeTime = D_800FD770.envelopePeriod = (GB_REG(7) & 7) * D_800FD7E4;
            } else {
                D_800FD770.envelopeStep = 0;
                D_800FD770.envelopePeriod = -1;
                D_800FD770.nextEnvelopeTime = -1;
            }
            if (nr24 & 0x40) {
                D_800FD770.lengthEnd = ((0x40 - (GB_REG(6) & 0x3F)) * D_800FD7E4) >> 2;
            } else {
                D_800FD770.lengthEnd = -1;
            }
            GB_REG(9) = nr24 & ~0x80;
        }
        if (D_800FD770.enabled == 0) {
            return 0;
        }
    } else if (D_800FD770.enabled == 0) {
        return 0;
    }

    if (D_800FD770.lengthEnd < D_800FD770.time) {
        D_800FD770.enabled = 0;
        D_800FD7E8.nr52 &= 0xFFFD;
        return 0;
    }

    if (D_800FD770.nextEnvelopeTime < D_800FD770.time) {
        D_800FD770.volume += D_800FD770.envelopeStep;
        D_800FD770.nextEnvelopeTime += D_800FD770.envelopePeriod;
    }
    while (D_800FD770.nextPhaseTime <= D_800FD770.time) {
        D_800FD770.phase ^= 1;
        D_800FD770.nextPhaseTime += D_800FD770.halfPeriods[D_800FD770.phase];
    }

    if (!(GB_REG(7) & 8) && (D_800FD770.volume < 0)) {
        D_800FD770.enabled = 0;
        return 0;
    }
    if ((u16)D_800FD770.volume > 0x7800) {
        D_800FD770.volume = 0x7800;
        D_800FD770.envelopeStep = 0;
        D_800FD770.nextEnvelopeTime = -1;
    }
    out = D_800FD770.volume;
    if (D_800FD770.phase == 0) {
        out = -out;
    }
    D_800FD770.time += 0x40;
    return out;
}

s16 func_80045B9C(void) {
    s32 i;
    s32 nr43;
    s32 row;
    s32 changed;
    u32 nr44;
    u16 col;
    GbNoiseEntry* entry;
    u8 sampleId;
    s16 sample;
    GbNoiseSampleEntry* ent;

    changed = 0;
    for (i = 0x10; i < 0x14; i++) {
        if (GB_REG_DIRTY(i) != 0) {
            changed = 1;
            GB_REG_DIRTY(i) = 0;
        }
    }

    if (changed) {
        nr43 = GB_REG(0x12);
        row = nr43 & 7;
        col = (GB_REG(0x12) & 0xF0) >> 4;
        entry = &GB_NOISE_TABLE[row][col];
        sampleId = entry->sampleId;
        if (sampleId == 0xFF) {
            D_800FD7B8.enabled = 0;
            return 0;
        }
        if (GB_REG(0x12) & 8) {
            sampleId += 0x10;
        }
        D_800FD7B8.pitchStep = GB_NOISE_TABLE[nr43 & 7][col].pitchStep;
        if (sampleId != D_800FD7B8.sampleId) {
            D_800FD7B8.sampleId = sampleId;
            ent = (GbNoiseSampleEntry*)((u32*)D_800B41E4 + (D_800FD7B8.sampleId << 1));
            Rom_DmaRead(ent->romAddr, (u32)D_800B41E8, ent->size);
        }

        D_800FD7B8.sampleIndex = 0;
        D_800FD7B8.pitchAccum = 0;
        if (!(GB_REG(0x11) & 8) && !(GB_REG(0x11) & 0xF0)) {
            D_800FD7B8.enabled = 0;
            D_800FD7E8.nr52 &= 0xFFF7;
            return 0;
        }
        if ((GB_REG(0x11) & 8) && !(GB_REG(0x11) & 0xF0) && !(GB_REG(0x11) & 7)) {
            D_800FD7B8.enabled = 0;
            D_800FD7E8.nr52 &= 0xFFF7;
            return 0;
        }

        nr44 = GB_REG(0x13);
        if (nr44 & 0x80) {
            D_800FD7B8.time = 0;
            D_800FD7B8.enabled = 1;
            D_800FD7B8.volume = (u8)(GB_REG(0x11) & 0xF0) * 0.05f;
            if (GB_REG(0x11) & 7) {
                if (GB_REG(0x11) & 8) {
                    D_800FD7B8.envelopeStep = 0.05f;
                } else {
                    D_800FD7B8.envelopeStep = -0.05f;
                }
                D_800FD7B8.nextEnvelopeTime = D_800FD7B8.envelopePeriod = (GB_REG(0x11) & 7) * D_800FD7E4 * 4;
            } else {
                D_800FD7B8.envelopePeriod = -1;
                D_800FD7B8.nextEnvelopeTime = -1;
                D_800FD7B8.envelopeStep = 0.0f;
            }
            if (nr44 & 0x40) {
                D_800FD7B8.lengthEnd = (0x40 - (GB_REG(0x10) & 0x3F)) * D_800FD7E4;
            } else {
                D_800FD7B8.lengthEnd = -1;
            }
            GB_REG(0x13) = nr44 & 0xFF7F;
        }
        if (D_800FD7B8.enabled == 0) {
            return 0;
        }
    } else if (D_800FD7B8.enabled == 0) {
        return 0;
    }

    if (D_800FD7B8.lengthEnd < D_800FD7B8.time) {
        D_800FD7B8.enabled = 0;
        D_800FD7E8.nr52 &= 0xFFF7;
        return 0;
    }

    if (D_800FD7B8.nextEnvelopeTime < D_800FD7B8.time) {
        D_800FD7B8.nextEnvelopeTime += D_800FD7B8.envelopePeriod;
        D_800FD7B8.volume += D_800FD7B8.envelopeStep;
    }

    ent = (GbNoiseSampleEntry*)((u32*)D_800B41E4 + (D_800FD7B8.sampleId << 1));
    if (1) {}  // karodo
    sample = ((s16*)D_800B41E8)[D_800FD7B8.sampleIndex];
    D_800FD7B8.pitchAccum += 1.0f;
    if (D_800FD7B8.pitchStep <= D_800FD7B8.pitchAccum) {
        D_800FD7B8.sampleIndex++;
        D_800FD7B8.pitchAccum -= D_800FD7B8.pitchStep;
        if (D_800FD7B8.sampleIndex >= (ent->size >> 1)) {
            D_800FD7B8.sampleIndex = 0;
        }
    }

    if (!(GB_REG(0x11) & 8) && (D_800FD7B8.volume < 0.0f)) {
        D_800FD7B8.enabled = 0;
        return 0;
    }
    if (D_800FD7B8.volume > 0.75f) {
        D_800FD7B8.volume = 0.75f;
        D_800FD7B8.envelopeStep = 0.0f;
        D_800FD7B8.nextEnvelopeTime = -1;
    }
    sample = sample * D_800FD7B8.volume;
    D_800FD7B8.time += 0x100;
    return sample;
}

/** Clears the sample interpolation history. */
void GbAudio_ClearInterpolationHistory(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_800FDED8); i++) {
        D_800FDED8[i] = 0;
    }
    D_80100158 = 0;
}

/** Clears the audio output buffer. */
void GbAudio_ClearOutputBuffer(void) {
    s32 i;

    for (i = 0; i < 2944; i++) {
        D_800B41EC[i] = 0;
    }
    D_800FDED0 = 0;
    D_800FDED4 = 0;
}

void func_8004602C(void) {

}
