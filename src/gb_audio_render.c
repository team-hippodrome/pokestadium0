/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gb_audio_render.c. */

#include "gb_audio_render.h"
#include "rom_device.h"
#include "audio_commands.h"
typedef struct unk_D_800FD008 {
    /* 0x00 */ u16 unk_00[20];
    /* 0x28 */ u8 unk_28;
    /* 0x29 */ u8 unk_29;
    /* 0x2A */ u8 unk_2A;
    /* 0x2B */ char unk2B[1];
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ char unk2D[0x13];
} unk_D_800FD008;
#define GB_REG(n) (((u8*)&D_800FD7E8.unk_00[n])[0])
#define GB_REG_DIRTY(n) (((u8*)&D_800FD7E8.unk_00[n])[1])
typedef struct unk_D_800FD068 {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x06 */ u16 unk_06;
} unk_D_800FD068;
typedef struct unk_D_800FCFD8 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 pad05[0x3];
    /* 0x04 */ u32 unk_08;
    /* 0x04 */ f32 unk_0C;
    /* 0x04 */ f32 unk_10;
    /* 0x04 */ f32 unk_14;
    /* 0x04 */ f32 unk_18;
    /* 0x04 */ u32 unk_1C;
    /* 0x04 */ u32 unk_20;
    /* 0x04 */ u32 unk_24;
    /* 0x04 */ u8 unk_28;
} unk_D_800FCFD8;
typedef struct unk_D_800FCF90 {
    /* 0x00 */ u32 unk_00;
    /* 0x00 */ s16 unk_04;
    /* 0x00 */ s16 unk_06;
    /* 0x00 */ u32 unk_08;
    /* 0x00 */ u32 unk_0C;
    /* 0x10 */ u16 unk_10[2];
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16;
    /* 0x00 */ u32 unk_18;
    /* 0x00 */ u32 unk_1C;
    /* 0x00 */ u32 unk_20;
    /* 0x24 */ u8 unk_24;
} unk_D_800FCF90;
typedef struct unk_D_800FCFB8 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u8 unk04[0x18];
    /* 0x1C */ u8 unk_1C;
} unk_D_800FCFB8;
typedef struct unk_D_800FCF60 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ char pad06[0x2];
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ u16 unk_18[2];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ u8 unk_1E;
    /* 0x1F */ char pad1F[0x1];
    /* 0x20 */ u32 unk_20;
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ u32 unk_28;
    /* 0x2C */ u8 unk_2C;
} unk_D_800FCF60;
extern unk_D_800FCF60 D_800FD740;
extern unk_D_800FCF90 D_800FD770;
extern unk_D_800FCFB8 D_800FD798;
extern unk_D_800FCFD8 D_800FD7B8;
extern u32 D_800FD7E4;
extern unk_D_800FD008 D_800FD7E8;
extern u8 D_800FD828[32];
extern unk_D_800FD068 D_800FD848[199];
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

void GbAudio_GenerateSamples(s16* arg0, s32 arg1, u32 arg2, f32 arg3) {
    func_80044D60(arg2);
}

void GbAudio_QueueRegisterWrite(u16 arg0, u8 arg1, u16 arg2) {
    D_800FD848[D_800FDE8C].unk_00 = (u8*)&D_800FD7E8.unk_00[(arg0 & 0xFF) - 0x10];
    D_800FD848[D_800FDE8C].unk_04 = arg1;
    D_800FD848[D_800FDE8C].unk_06 = arg2 + 1;
    D_800FDE80[arg0 & 0xFF] = arg1;
    D_800FDE8C++;
    D_800FDE8C %= 200;
    D_800FD848[D_800FDE8C].unk_06 = 0;
}

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

    p = D_800FD828;
    for (i = 0; i < 16; i++) {
        p[i * 2] = 0;
    }
    D_800FDE8C = 0;
    D_800FD848[0].unk_06 = 0;
    D_800FDE88 = 0;
    D_800FD740.unk_00 = 0;
    D_800FD740.unk_2C = 0;

    D_800FD770.unk_00 = 0;
    D_800FD770.unk_24 = 0;

    D_800FD798.unk_00 = 0;
    D_800FD798.unk_1C = 0;

    D_800FD7B8.unk_00 = 0;
    D_800FD7B8.unk_28 = 0;
    D_800FD7B8.unk_04 = 0xFF;

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

        if (D_800FD7E8.unk_2C & 0x80) {
            if (D_800FD7E8.unk_29 != 0) {
                D_800FDEC0 = D_800FD7E8.unk_28 & 7;
                D_800FDEC1 = (D_800FD7E8.unk_28 & 0x70) >> 4;
                D_800FD7E8.unk_29 = 0;
            }

            sp4C[0] = func_800450F0();
            sp4C[1] = func_80045774();
            sp4C[3] = func_80045B9C();

            var_t = D_800FD7E8.unk_2A;
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

void GbAudio_ApplyQueuedWrites(u16 arg0) {
    while (D_800FD848[D_800FDE88].unk_06 >= arg0) {
        D_800FD848[D_800FDE88].unk_00[0] = D_800FD848[D_800FDE88].unk_04;
        D_800FD848[D_800FDE88].unk_00[1] = 1;
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
        D_800FD740.unk_04 = GB_REG(3) | (((u8)nr14 & 7) << 8);
        D_800FD740.unk_24 = ((0x800 - D_800FD740.unk_04) * D_800FD7E4) >> 11;
        switch ((GB_REG(1) & 0xC0) >> 6) {
            case 0:
                D_800FD740.unk_18[1] = D_800FD740.unk_24 >> 3;
                if (D_800FD740.unk_18[1] < 0x40) {
                    D_800FD740.unk_18[1] = 0x40;
                }
                phase = 1;
                D_800FD740.unk_18[0] = D_800FD740.unk_24 - D_800FD740.unk_18[1];
                goto duty_done;
            case 1:
                D_800FD740.unk_18[1] = D_800FD740.unk_24 >> 2;
                if (D_800FD740.unk_18[1] < 0x40) {
                    D_800FD740.unk_18[1] = 0x40;
                }
                phase = 0;
                D_800FD740.unk_18[0] = D_800FD740.unk_24 - D_800FD740.unk_18[1];
                goto duty_done;
            case 2:
                D_800FD740.unk_18[1] = D_800FD740.unk_24 >> 1;
                if (D_800FD740.unk_18[1] < 0x40) {
                    D_800FD740.unk_18[1] = 0x40;
                }
                phase = 0;
                D_800FD740.unk_18[0] = D_800FD740.unk_24 - D_800FD740.unk_18[1];
                goto duty_done;
            case 3:
                D_800FD740.unk_18[0] = D_800FD740.unk_24 >> 2;
                if (D_800FD740.unk_18[0] < 0x40) {
                    D_800FD740.unk_18[0] = 0x40;
                }
                phase = 1;
                D_800FD740.unk_18[1] = D_800FD740.unk_24 - D_800FD740.unk_18[0];
                goto duty_done;
        }
        D_800FD740.unk_18[1] = 0;
        phase = 1;
        D_800FD740.unk_18[0] = D_800FD740.unk_24;
    duty_done:

        if (!(GB_REG(2) & 8) && !(GB_REG(2) & 0xF0)) {
            D_800FD740.unk_2C = 0;
            D_800FD7E8.unk_2C &= 0xFFFE;
            return 0;
        }
        if ((GB_REG(2) & 8) && !(GB_REG(2) & 0xF0) && !(GB_REG(2) & 7)) {
            D_800FD740.unk_2C = 0;
            D_800FD7E8.unk_2C &= 0xFFFE;
            return 0;
        }

        if (nr14 & 0x80) {
            D_800FD740.unk_00 = 0;
            D_800FD740.unk_2C = 1;
            D_800FD740.unk_1E = phase;
            D_800FD740.unk_1C = 0;
            D_800FD740.unk_20 = 0;
            D_800FD740.unk_0C = (u8)(GB_REG(2) & 0xF0) << 7;
            if (GB_REG(2) & 7) {
                if (GB_REG(2) & 8) {
                    D_800FD740.unk_0E = 0x800;
                } else {
                    D_800FD740.unk_0E = -0x800;
                }
                D_800FD740.unk_14 = D_800FD740.unk_10 = (GB_REG(2) & 7) * D_800FD7E4;
            } else {
                D_800FD740.unk_0E = 0;
                D_800FD740.unk_10 = -1;
                D_800FD740.unk_14 = -1;
            }
            D_800FD740.unk_08 = (((GB_REG(0) & 0x70) >> 4) * D_800FD7E4) >> 1;
            if (D_800FD740.unk_08 == 0) {
                D_800FD740.unk_08 = -1;
            }
            if (nr14 & 0x40) {
                D_800FD740.unk_28 = ((0x40 - (GB_REG(1) & 0x3F)) * D_800FD7E4) >> 2;
            } else {
                D_800FD740.unk_28 = -1;
            }
            GB_REG(4) = nr14 & ~0x80;
        }
        if (D_800FD740.unk_2C == 0) {
            return 0;
        }
    } else if (D_800FD740.unk_2C == 0) {
        return 0;
    }

    if (D_800FD740.unk_28 < D_800FD740.unk_00) {
        D_800FD740.unk_2C = 0;
        D_800FD7E8.unk_2C &= 0xFFFE;
        return 0;
    }

    if ((D_800FD740.unk_08 - (D_800FD740.unk_00 % D_800FD740.unk_08)) <= 0x40) {
        if (!(GB_REG(0) & 8)) {
            freq = (D_800FD740.unk_04 + (D_800FD740.unk_04 >> (GB_REG(0) & 7)));
            if (freq >= 0x800) {
                D_800FD740.unk_2C = 0;
                D_800FD7E8.unk_2C &= 0xFFFE;
                return 0;
            }
            D_800FD740.unk_04 = freq;
        } else {
            freq = (D_800FD740.unk_04 - (D_800FD740.unk_04 >> (GB_REG(0) & 7)));
            if ((freq >= 0x800) || (freq < 0)) {
                goto skip;
            }
            D_800FD740.unk_04 = freq;
        }
        D_800FD740.unk_24 = ((0x800 - D_800FD740.unk_04) * D_800FD7E4) >> 11;
        switch ((GB_REG(1) & 0xC0) >> 6) {
            case 0:
                D_800FD740.unk_18[1] = D_800FD740.unk_24 >> 3;
                if (D_800FD740.unk_18[1] < 0x40) {
                    D_800FD740.unk_18[1] = 0x40;
                }
                D_800FD740.unk_18[0] = D_800FD740.unk_24 - D_800FD740.unk_18[1];
                break;
            case 1:
                D_800FD740.unk_18[1] = D_800FD740.unk_24 >> 2;
                if (D_800FD740.unk_18[1] < 0x40) {
                    D_800FD740.unk_18[1] = 0x40;
                }
                D_800FD740.unk_18[0] = D_800FD740.unk_24 - D_800FD740.unk_18[1];
                break;
            case 2:
                D_800FD740.unk_18[1] = D_800FD740.unk_24 >> 1;
                if (D_800FD740.unk_18[1] < 0x40) {
                    D_800FD740.unk_18[1] = 0x40;
                }
                D_800FD740.unk_18[0] = D_800FD740.unk_24 - D_800FD740.unk_18[1];
                break;
            case 3:
                D_800FD740.unk_18[0] = D_800FD740.unk_24 >> 2;
                if (D_800FD740.unk_18[0] < 0x40) {
                    D_800FD740.unk_18[0] = 0x40;
                }
                D_800FD740.unk_18[1] = D_800FD740.unk_24 - D_800FD740.unk_18[0];
                break;
            default:
                D_800FD740.unk_18[1] = 0;
                D_800FD740.unk_18[0] = D_800FD740.unk_24;
        }
    }
skip:

    if (D_800FD740.unk_14 < D_800FD740.unk_00) {
        D_800FD740.unk_0C += D_800FD740.unk_0E;
        D_800FD740.unk_14 += D_800FD740.unk_10;
    }
    while (D_800FD740.unk_20 < D_800FD740.unk_00) {
        D_800FD740.unk_1E ^= 1;
        D_800FD740.unk_20 += D_800FD740.unk_18[D_800FD740.unk_1E];
    }

    if (!(GB_REG(2) & 8) && (D_800FD740.unk_0C < 0)) {
        D_800FD740.unk_2C = 0;
        return 0;
    }
    if ((u16)D_800FD740.unk_0C > 0x7800) {
        D_800FD740.unk_0C = 0x7800;
        D_800FD740.unk_0E = 0;
        D_800FD740.unk_14 = -1;
    }
    out = D_800FD740.unk_0C;
    if (D_800FD740.unk_1E == 0) {
        out = -out;
    }
    D_800FD740.unk_00 += 0x40;
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
        D_800FD770.unk_1C = ((0x800 - (GB_REG(8) | (((u8)nr24 & 7) << 8))) * D_800FD7E4) >> 11;
        switch ((GB_REG(6) & 0xC0) >> 6) {
            case 0:
                D_800FD770.unk_10[1] = D_800FD770.unk_1C >> 3;
                if (D_800FD770.unk_10[1] < 0x40) {
                    D_800FD770.unk_10[1] = 0x40;
                }
                phase = 1;
                D_800FD770.unk_10[0] = D_800FD770.unk_1C - D_800FD770.unk_10[1];
                goto duty_done;
            case 1:
                D_800FD770.unk_10[1] = D_800FD770.unk_1C >> 2;
                if (D_800FD770.unk_10[1] < 0x40) {
                    D_800FD770.unk_10[1] = 0x40;
                }
                phase = 0;
                D_800FD770.unk_10[0] = D_800FD770.unk_1C - D_800FD770.unk_10[1];
                goto duty_done;
            case 2:
                D_800FD770.unk_10[1] = D_800FD770.unk_1C >> 1;
                if (D_800FD770.unk_10[1] < 0x40) {
                    D_800FD770.unk_10[1] = 0x40;
                }
                phase = 0;
                D_800FD770.unk_10[0] = D_800FD770.unk_1C - D_800FD770.unk_10[1];
                goto duty_done;
            case 3:
                D_800FD770.unk_10[0] = D_800FD770.unk_1C >> 2;
                if (D_800FD770.unk_10[0] < 0x40) {
                    D_800FD770.unk_10[0] = 0x40;
                }
                phase = 1;
                D_800FD770.unk_10[1] = D_800FD770.unk_1C - D_800FD770.unk_10[0];
                goto duty_done;
        }
        D_800FD770.unk_10[1] = 0;
        phase = 1;
        D_800FD770.unk_10[0] = D_800FD770.unk_1C;
    duty_done:

        if (!(GB_REG(7) & 8) && !(GB_REG(7) & 0xF0)) {
            D_800FD770.unk_24 = 0;
            D_800FD7E8.unk_2C &= 0xFFFD;
            return 0;
        }
        if ((GB_REG(7) & 8) && !(GB_REG(7) & 0xF0) && !(GB_REG(7) & 7)) {
            D_800FD770.unk_24 = 0;
            D_800FD7E8.unk_2C &= 0xFFFD;
            return 0;
        }

        if (nr24 & 0x80) {
            D_800FD770.unk_00 = 0;
            D_800FD770.unk_24 = 1;
            D_800FD770.unk_16 = phase;
            D_800FD770.unk_14 = 0;
            D_800FD770.unk_18 = 0;
            D_800FD770.unk_04 = ((GB_REG(7) & 0xF0) << 3) << 4;
            if (GB_REG(7) & 7) {
                if (GB_REG(7) & 8) {
                    D_800FD770.unk_06 = 0x800;
                } else {
                    D_800FD770.unk_06 = -0x800;
                }
                D_800FD770.unk_0C = D_800FD770.unk_08 = (GB_REG(7) & 7) * D_800FD7E4;
            } else {
                D_800FD770.unk_06 = 0;
                D_800FD770.unk_08 = -1;
                D_800FD770.unk_0C = -1;
            }
            if (nr24 & 0x40) {
                D_800FD770.unk_20 = ((0x40 - (GB_REG(6) & 0x3F)) * D_800FD7E4) >> 2;
            } else {
                D_800FD770.unk_20 = -1;
            }
            GB_REG(9) = nr24 & ~0x80;
        }
        if (D_800FD770.unk_24 == 0) {
            return 0;
        }
    } else if (D_800FD770.unk_24 == 0) {
        return 0;
    }

    if (D_800FD770.unk_20 < D_800FD770.unk_00) {
        D_800FD770.unk_24 = 0;
        D_800FD7E8.unk_2C &= 0xFFFD;
        return 0;
    }

    if (D_800FD770.unk_0C < D_800FD770.unk_00) {
        D_800FD770.unk_04 += D_800FD770.unk_06;
        D_800FD770.unk_0C += D_800FD770.unk_08;
    }
    while (D_800FD770.unk_18 <= D_800FD770.unk_00) {
        D_800FD770.unk_16 ^= 1;
        D_800FD770.unk_18 += D_800FD770.unk_10[D_800FD770.unk_16];
    }

    if (!(GB_REG(7) & 8) && (D_800FD770.unk_04 < 0)) {
        D_800FD770.unk_24 = 0;
        return 0;
    }
    if ((u16)D_800FD770.unk_04 > 0x7800) {
        D_800FD770.unk_04 = 0x7800;
        D_800FD770.unk_06 = 0;
        D_800FD770.unk_0C = -1;
    }
    out = D_800FD770.unk_04;
    if (D_800FD770.unk_16 == 0) {
        out = -out;
    }
    D_800FD770.unk_00 += 0x40;
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
    unk_D_800FC6CC* ent;

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
            D_800FD7B8.unk_28 = 0;
            return 0;
        }
        if (GB_REG(0x12) & 8) {
            sampleId += 0x10;
        }
        D_800FD7B8.unk_0C = GB_NOISE_TABLE[nr43 & 7][col].pitchStep;
        if (sampleId != D_800FD7B8.unk_04) {
            D_800FD7B8.unk_04 = sampleId;
            ent = (unk_D_800FC6CC*)((u32*)D_800B41E4 + (D_800FD7B8.unk_04 << 1));
            Rom_DmaRead(ent->unk_00, (u32)D_800B41E8, ent->unk_04);
        }

        D_800FD7B8.unk_08 = 0;
        D_800FD7B8.unk_10 = 0;
        if (!(GB_REG(0x11) & 8) && !(GB_REG(0x11) & 0xF0)) {
            D_800FD7B8.unk_28 = 0;
            D_800FD7E8.unk_2C &= 0xFFF7;
            return 0;
        }
        if ((GB_REG(0x11) & 8) && !(GB_REG(0x11) & 0xF0) && !(GB_REG(0x11) & 7)) {
            D_800FD7B8.unk_28 = 0;
            D_800FD7E8.unk_2C &= 0xFFF7;
            return 0;
        }

        nr44 = GB_REG(0x13);
        if (nr44 & 0x80) {
            D_800FD7B8.unk_00 = 0;
            D_800FD7B8.unk_28 = 1;
            D_800FD7B8.unk_14 = (u8)(GB_REG(0x11) & 0xF0) * 0.05f;
            if (GB_REG(0x11) & 7) {
                if (GB_REG(0x11) & 8) {
                    D_800FD7B8.unk_18 = 0.05f;
                } else {
                    D_800FD7B8.unk_18 = -0.05f;
                }
                D_800FD7B8.unk_20 = D_800FD7B8.unk_1C = (GB_REG(0x11) & 7) * D_800FD7E4 * 4;
            } else {
                D_800FD7B8.unk_1C = -1;
                D_800FD7B8.unk_20 = -1;
                D_800FD7B8.unk_18 = 0.0f;
            }
            if (nr44 & 0x40) {
                D_800FD7B8.unk_24 = (0x40 - (GB_REG(0x10) & 0x3F)) * D_800FD7E4;
            } else {
                D_800FD7B8.unk_24 = -1;
            }
            GB_REG(0x13) = nr44 & 0xFF7F;
        }
        if (D_800FD7B8.unk_28 == 0) {
            return 0;
        }
    } else if (D_800FD7B8.unk_28 == 0) {
        return 0;
    }

    if (D_800FD7B8.unk_24 < D_800FD7B8.unk_00) {
        D_800FD7B8.unk_28 = 0;
        D_800FD7E8.unk_2C &= 0xFFF7;
        return 0;
    }

    if (D_800FD7B8.unk_20 < D_800FD7B8.unk_00) {
        D_800FD7B8.unk_20 += D_800FD7B8.unk_1C;
        D_800FD7B8.unk_14 += D_800FD7B8.unk_18;
    }

    ent = (unk_D_800FC6CC*)((u32*)D_800B41E4 + (D_800FD7B8.unk_04 << 1));
    if (1) {}  // karodo
    sample = ((s16*)D_800B41E8)[D_800FD7B8.unk_08];
    D_800FD7B8.unk_10 += 1.0f;
    if (D_800FD7B8.unk_0C <= D_800FD7B8.unk_10) {
        D_800FD7B8.unk_08++;
        D_800FD7B8.unk_10 -= D_800FD7B8.unk_0C;
        if (D_800FD7B8.unk_08 >= (ent->unk_04 >> 1)) {
            D_800FD7B8.unk_08 = 0;
        }
    }

    if (!(GB_REG(0x11) & 8) && (D_800FD7B8.unk_14 < 0.0f)) {
        D_800FD7B8.unk_28 = 0;
        return 0;
    }
    if (D_800FD7B8.unk_14 > 0.75f) {
        D_800FD7B8.unk_14 = 0.75f;
        D_800FD7B8.unk_18 = 0.0f;
        D_800FD7B8.unk_20 = -1;
    }
    sample = sample * D_800FD7B8.unk_14;
    D_800FD7B8.unk_00 += 0x100;
    return sample;
}

void GbAudio_ClearInterpolationHistory(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_800FDED8); i++) {
        D_800FDED8[i] = 0;
    }
    D_80100158 = 0;
}

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
