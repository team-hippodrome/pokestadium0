/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "gb_tower_emulator_86CB0.h"

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
            if (status) {}  // karodo
            if (bufPtr) {}  // karodo
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
