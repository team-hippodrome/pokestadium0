/* Fixed-layout split at GbEmu_UpdateFrame so its jump table lands at 0x81154258. */
/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_emulator/gb_tower_emulator_7F9A0.c. */

#include "global.h"
#include "audio_and_gb_emulator.h"
#include "variables.h"

#include "m2c_macros.h"

// Declared here instead of in a header: the callers of these disagree on their types.
void GbAudio_UpdateFrame();

void GbEmu_BlitWithPixelOp(u16* dst, u16* src, s32 mode, s32 width, s32 height);
void GbEmu_BlendScrollingLayer(u16* arg0, u16* arg1, s16* arg2, s32 arg3, s32 arg4);

s32 func_811020A8(void *arg0);

extern GbPakChannel D_811561C8[4];
extern volatile u8 D_81156475;
extern volatile u8 D_81156476;
extern OSMesgQueue D_81156458;
s32 func_8004CFB0(OSMesgQueue*, s32, s32);
s32 GbPak_WriteBackDirtySramBlock(s32 arg0);
u32 func_80053A80(void);
M2C_UNK func_8005C0A0();
extern s32 D_81156550;
extern u8 D_8111E308;
void func_81103C40(s32, u8*, s32, s32, s32);
extern s8 D_811565A2;
extern GbEmuState D_81156540;
extern u8 D_811565A0;
void func_80058410(void*, void*, s32);
extern s32 D_81154C48;

void func_81103D30(void);
void GbEmu_DrawAccessIcon(u16* arg0, s32 arg1, s32 arg2);
void func_81104618(s32 arg0);
void func_811047A0(s32 arg0);
void func_81104930(void);


typedef struct GbEmuTask {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 flags;
    /* 0x08 */ void* ucode;
    /* 0x0C */ s32 ucodeSize;
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ u8 unk_16[2];
    /* 0x18 */ u8* unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ u8 unk_24[0xC];
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ u8 unk_34[4];
    /* 0x38 */ s32 unk_38;
} GbEmuTask;

#define GB_RUN (&D_81156540)
#define GB_MEM (GB_RUN->mem)

extern volatile u8 D_81156475;
extern volatile u8 D_81156476;
extern OSMesgQueue D_81156458;
extern u8 D_811565A0;
extern u8 D_811565A1;
extern u8 D_811565A3;
extern u8 D_811565A4;
extern u8 D_811565A5;
extern u8* D_811565A8;
extern u8 D_811565B8;
extern u8 D_811565B9;
extern u8 D_8111E308;
extern u16 D_8111E30C;
extern u16 D_8111E310;
extern u16 D_811228B4;
extern u8 D_811228B8;
extern s32 D_81154C48;
extern u8 D_81154C0F;
extern u8 D_81154C4F;
extern GbEmuTask D_81154BF0;
extern u8* D_800603C0;
extern u8 D_8112AF3C[];
extern u8 D_81130024[];
extern u8 D_811565F0[];
extern u8 D_811645F0[];
extern u8 D_811725F0[];
extern u8 D_81135178[];
extern u8 D_81135378[];
extern u8 D_8113556C[];
extern u8 D_8111F470[];
extern u8 D_8111E678[];
void func_800093E0(void*, void*);
void GbPak_QueueNextBankLoad(GbPakChannel*);
void Cont_StartReadInputs(void);
void Cont_ReadInputs(void);
u8 func_81118018(void*, s32);
void func_80056730(void*, s32, void*);
void func_811177D0(s32);

/**
 * Runs one frame of the GB Tower emulator (Stadium 1's GbEmu_UpdateFrame).
 * Services the Transfer Pak, builds the emulated joypad from the controller,
 * lets C-Right cycle the emulation speed, steps the CPU core that many times
 * and queues the RSP task that draws the Game Boy screen. When enabled, Z
 * cycles the graphics set copied in for the screen frame. Returns 1 when only
 * C-Up is held, a negative value on a Transfer Pak error, -100 when the core
 * stopped, otherwise 0.
 * Seen in play (2026-11-12): runs Green frame by frame and, while banks load, restores the header
 * bytes once the GB PC (gbPc) reaches 0x100.
 */
s32 GbEmu_UpdateFrame(void) {
    s32 i;
    s32 err;
    s32 status;
    u8* src;
    u8* state;
    u8* timer;
    s32 j;
    s32 count;
    s32 cycles;
    u8 steps;
    s32 btn;
    u16 val;
    s32 z1; // FAKE
    s32 z2; // FAKE
    s32 z3; // FAKE
    u8* dst;
    u32 mode;
    s32 k;
    u16 h;

    status = 0;
    if (D_81156476 != 0) {
        // While banks stream in, the GB runs a boot stub that ends in `jr $` at 0x100 (see
        // GbEmu_LoadCartridge). Once it gets there, put the real header bytes back.
        if (D_811565A4 != 0 && GB_RUN->gbPc == 0x100) {
            if (--D_811565A4 == 0) {
                func_800093E0(D_8112AF3C, D_811645F0);
                func_800093E0(D_81130024, D_811725F0);
                for (j = 0; j < 258; j++) {
                    GB_RUN->rom[j] = D_811565A8[j];
                }
            }
        }
        GbPak_QueueNextBankLoad(&D_811561C8[D_811565A0]);
        if (D_81156476 != 0) {
            if (D_811561C8[D_811565A0].error != 0) {
                status = (D_811561C8[D_811565A0].unkA2 != 0) ? -3 : -1;
            }
            if (++D_811565A3 >= 11) {
                D_811565A3 = 0;
            }
            GbEmu_DrawAccessIcon((u16*)(GB_RUN->unk_50 + 0xB0), 0, D_811565A3);
            GB_RUN->buttons = 0;
        } else {
            func_81103D30();
            func_81104930();
        }
    } else {
        for (i = 0; i < 5; i++) {
            D_811561C8[D_811565A0].blockDirty[i] = 0xFF;
            D_811561C8[D_811565A0].blockState[i] = D_811561C8[D_811565A0].blockDirty[i];
        }
        timer = &D_811565B8;
        err = GbPak_WriteBackDirtySramBlock(D_811565A0);
        if (err == 0) {
            Cont_StartReadInputs();
            Cont_ReadInputs();
            if ((++*timer & 3) == 0) {
                D_811561C8[D_811565A0].request = 8;
                func_8004CFB0(&D_81156458, D_811565A0, 1);
            }
            k = ((*(u16*)(D_800603C0 + 6) & D_8111E30C) ? 0x1000 : 0);
            mode = ((*(u16*)(D_800603C0 + 6) & D_8111E310) ? 0x2000U : 0);
            GB_RUN->buttons = (*(u16*)(D_800603C0 + 6) & ~0x3000) | k | mode;
            if (D_8111E308 != 0) {
                btn = GB_MEM[0x101B9];
                h = *(u16*)(D_800603C0 + 8);
                if (h & 1) {
                    *(u16*)(D_800603C0 + 8) = h & 0xFFFE;
                    switch ((u32)btn) { // FAKE
                        case 1:
                            btn = 2;
                            break;
                        case 2:
                            if (D_8111E308 >= 2) {
                                btn = 4;
                                break;
                            }
                        default:
                            btn = 1;
                            break;
                    }
                    GB_MEM[0x101B9] = btn;
                    func_81104618(GB_RUN->framebuffer);
                }
            }
        } else if (D_811561C8[D_811565A0].error != 0) {
            status = (D_811561C8[D_811565A0].unkA2 != 0) ? -3 : -2;
        } else {
            if (err == 2) {
                if (D_811565A1 == 0) {
                    func_811047A0(1);
                }
                D_811565A1 = 10;
            }
            GB_RUN->buttons = 0;
        }
    }

    if (D_811565A1) {
        if (!err) {
            D_811565A1--;
        }
        if (!D_811565A1) {
            func_81104930();
        } else {
            if (++*(u8*)&D_811565A2 >= 11) { // FAKE
                *(u8*)&D_811565A2 = 0; // FAKE
            }
            GbEmu_DrawAccessIcon((u16*)(GB_RUN->unk_50 + 0xB0), 1, *(u8*)&D_811565A2); // FAKE
        }
        GB_RUN->buttons = 0;
    }

    if (GB_RUN->unk_06 != 0) {
        GB_RUN->unk_06 = 0;
        func_811177D0(0);
    }

    if (status == 0) {
        count = GB_MEM[0x101B9];
        if ((GB_MEM[0x1017D] == 0) && (GB_MEM[0x10181] == 0) && (GB_MEM[0xFF40] & 0x80) &&
            ((count != 1) || (GB_RUN->colorIndex != 3))) {
            i = GB_MEM[0x101D1];
            if (i == 0) {
                if (GB_MEM[0x101CD] != 0) {
                    GB_MEM[0x101CD] = 0;
                    D_811228B4 = 0xFFFF;
                    i = 10;
                }
            } else {
                i--;
                if (i == 10) {
                    GB_MEM[0x101CD] = D_811228B4 != GB_MEM[0xFF47];
                } else if ((i < 10) && (GB_MEM[0x101CD] != 0)) {
                    GB_MEM[0x101CD] = 0;
                    i = 20;
                    D_811228B4 = GB_MEM[0xFF47];
                }
            }
        } else {
            GB_MEM[0x101CD] = 0;
            i = 0;
        }
        GB_MEM[0x101D1] = i;

        steps = count;
        cycles = 0;
        state = &D_811228B8;
        timer = &D_811565B9;
        while (count != 0) {
            *(s32*)(GB_MEM + 0x10100) = cycles;
            if (count == 1) {
                GB_MEM[0x101C1] = 0;
            } else {
                GB_MEM[0x101C1] = 1;
            }
            i = func_81118018(&D_81156540, 0);
            if ((i != 0) || (GB_MEM[0x1017D] != 0) || (cycles += 17248, GB_MEM[0x10181] != 0) ||
                (GB_MEM[0x1018D] != 0)) {
                if ((s32)src * 0) {} // FAKE
                break;
            }
            count--;
            if ((steps == 4) || (steps == 2)) {
                val = GB_MEM[0xFF47];
                switch (*state) {
                    case 0:
                        GB_MEM[0x101D5] = 0;
                        if (val == 0xE4) {
                            *state = 1;
                        }
                        break;
                    case 1:
                        if ((val == 0x1B) || (val == 0xE6)) {
                            *state = 2;
                        } else if (val != 0xE4) {
                            *state = 0;
                        }
                        break;
                    case 2:
                    case 4:
                        if (val == 0xE4) {
                            (*state)++;
                            *timer = steps * 20;
                        } else if (val == 0) {
                            *state = 6;
                            *timer = steps * 20;
                        } else if ((val != 0x1B) && (val != 0xE6)) {
                            *state = 0;
                        }
                        break;
                    case 3:
                    case 5:
                        if (val == 0xE4) {
                            if (--*timer == 0) {
                                *state = 1;
                            }
                        } else if ((val == 0x1B) || (val == 0xE6)) {
                            (*state)++;
                            *timer = steps * 20;
                        } else {
                            *state = 0;
                        }
                        break;
                    case 6:
                        GB_MEM[0x101D1] = 0;
                        GB_MEM[0xFF47] = 0xE4;
                        GB_MEM[0x101D5] = 0xFF;
                        if (val == 0x40) {
                            *state = 0;
                        }
                        if (--*timer == 0) {
                            *state = 0;
                        }
                        break;
                }
            } else {
                GB_MEM[0x101D5] = 0;
            }
        }
    } else {
        i = 0;
    }

    while (D_811561C8[D_811565A0].request == 8) {
    }
    if (D_811561C8[D_811565A0].error != 0) {
        D_81154C48 = 2;
        status = (D_811561C8[D_811565A0].unkA2 != 0) ? -3 : -1;
    }

    if ((GB_MEM[0x1017D] != 0) || (GB_MEM[0x10181] != 0) || (GB_MEM[0x1018D] != 0)) {
        if (GB_MEM[0x10181]) {
            if (GB_MEM[0x10181] != GB_MEM[0x10185]) {
                GB_MEM[0x10185] = GB_MEM[0x10181];
                GB_MEM[0x1018D] = 2;
            } else {
                GB_MEM[0x1018D]--;
                if (GB_MEM[0x1018D] == 0) {
                    func_80056730(GB_MEM + 0x12F00, 0x1000, GB_MEM);
                    GB_MEM[0x10181] = 0;
                    GB_MEM[0x10185] = GB_MEM[0x10181];
                }
            }
        }
        D_81154BF0.type = 2;
        D_81154BF0.flags = 0;
        D_81154BF0.ucode = D_8111F470;
        D_81154BF0.ucodeSize = 0xE38;
        D_81154BF0.unk_18 = GB_MEM + 0xFE00;
        D_81154BF0.unk_1C = 0x0E300100;
        D_81154BF0.unk_30 = *(s32*)(GB_MEM + 0x10140);
        D_81154BF0.unk_38 = *(s32*)(GB_MEM + 0x10190);
        D_81154BF0.unk_20 = GB_RUN->unk_44;
        D_81154BF0.unk_14 = 0x10;
        D_81154BF0.unk_15 = 0xD1 - (D_811565A5 / 2);
        ((u8*)&D_81154BF0)[0x1F] = GB_MEM[0x101A1];
    } else {
        D_81154BF0.type = 2;
        D_81154BF0.flags = 0;
        D_81154BF0.ucode = D_8111E678;
        D_81154BF0.ucodeSize = 0xDF8;
        D_81154BF0.unk_18 = GB_MEM + 0xFE00;
        D_81154BF0.unk_1C = 0x0E300100;
        D_81154BF0.unk_30 = *(s32*)(GB_MEM + 0x10140);
        D_81154BF0.unk_38 = *(s32*)(GB_MEM + 0x10190);
        D_81154BF0.unk_20 = GB_RUN->unk_44;
        D_81154BF0.unk_14 = 0x10;
        D_81154BF0.unk_15 = 0xD1 - (D_811565A5 / 2);
        ((u8*)&D_81154BF0)[0x1F] = GB_MEM[0x101A1];
        if ((D_81156475 == 0) && (status == 0)) {
            if ((GB_RUN->buttons == 8) && (D_81154C0F == 0)) {
                return 1;
            }
            val = *(u16*)(D_800603C0 + 8);
            if ((val & 0x2000) && (D_81154C0F == 0) && (D_8111E308 != 0)) {
                *(u16*)(D_800603C0 + 8) = val & 0xDFFF;
                if (((GB_MEM[0x1019A] | GB_MEM[0x1019B] | GB_MEM[0x1019D]) == 0) && (GB_MEM[0x101C9] != 0)) {
                    btn = ++D_81154C4F;
                    if (btn > D_8111E308) {
                        btn = D_81154C4F = 0;
                    }
                    switch ((u32)btn) { // FAKE
                        case 1: src = D_811645F0; dst = D_81135378; break;
                        case 2: src = D_811725F0; dst = D_8113556C; break;
                        default: src = D_811565F0; dst = D_81135178; break;
                    }
                    func_80058410(src, GB_RUN->unk_48 + 0x800, 0xE000);
                    func_80058410(dst, GB_MEM + 0x27D80, 0x200);
                    GB_MEM[0x1019D] = 1;
                }
            }
        }
    }

    if ((D_811565A5) && (D_811565A5 != 0x20)) {
        D_811565A5--;
    }
    if (status != 0) {
        return status;
    }
    if (i != 0) {
        return -100;
    }
    return 0;
}

extern OSMesgQueue D_81156458;
extern u8 D_811565A0;

s32 func_811064DC(void) {
    volatile u8* chan = (volatile u8*)&D_811561C8[D_811565A0];

    while (chan[0x99] != 0) {
    }
    if (chan[0x9A] != 0) {
        return -1;
    }
    chan[0x99] = 8;
    osSendMesg(&D_81156458, (OSMesg)(u32)D_811565A0, OS_MESG_BLOCK);
    while (chan[0x99] != 0) {
    }
    if (chan[0x9A] != 0) {
        return -1;
    }
    return 0;
}

extern u8 D_811565A0;
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s32 func_8110659C(void)
{
  GbPakChannel *ch = &D_811561C8[D_811565A0];
  ch->unk00[0x99] = 0x80;
  ch->unk00[0x9A] = 0;
  func_8004CFB0(&D_81156458, D_811565A0, 1);
  while (D_81156475 != 0)
  {
  }

  if (((u8) (*((s8 *) (((s8 *) ch) + 0x9A)))) != 0)
  {
    return *((u8 *) (((s8 *) ch) + 0x9A));
  }
  if (ch->unk00[0x98] != 0)
  {
    return func_811020A8(ch);
  }
  return 0;
}

s32 func_8110665C(void) {
    u8 idx = D_811565A0;
    volatile GbPakChannel* ch = &D_811561C8[idx];

    ch->status = 0;
    ch->request = 8;
    func_8004CFB0(&D_81156458, idx, 1);
    while (D_81156475 != 0) {
    }
    return D_811561C8[D_811565A0].status & 0x80;
}

extern M2C_UNK D_8115623C;
extern u8 D_811565A1;

s32 func_81106700(void) {
    s32 var_v0;
    u8 *var_v1;

    var_v0 = 0;
    if (D_811565A1 != 0) {
        return 1;
    }
    var_v1 = *((M2C_UNK*)((u8*)&D_8115623C + (D_811565A0 * 0xA4)));
loop_3:
    var_v0 += 4;
    if (M2C_FIELD(var_v1, u8 *, 0) == 0) {
        return 1;
    }
    if (M2C_FIELD(var_v1, u8 *, 1) == 0) {
        return 1;
    }
    if (M2C_FIELD(var_v1, u8 *, 2) == 0) {
        return 1;
    }
    if (M2C_FIELD(var_v1, u8 *, 3) == 0) {
        return 1;
    }
    var_v1 += 4;
    if (var_v0 == 0x80) {
        return 0;
    }
    goto loop_3;
}

extern u8 D_81156261[];
extern OSMesgQueue D_81156458;
extern volatile u8 D_81156475;

void func_811067B0(void) {
    D_81156261[D_811565A0 * 0xA4] = 4;
    osSendMesg(&D_81156458, (OSMesg)(u32)D_811565A0, OS_MESG_BLOCK);
    while (D_81156475 != 0) {
    }
}

extern s8 D_81156546;

void func_81106820(void) {
    D_81156546 = 1;
}

extern s16 D_82608542;
extern s16 D_82608544;
extern s16 D_8260854C;
extern s16 D_8260854E;
extern s16 D_800AA148;
extern s32 D_81156550;
void GbAudio_UpdateFrame(void);
void osViBlack(u8);
/**
 * Per-frame tail of the GB Tower emulator: unless emulation is paused (D_81156546) or
 * the screen is being blanked (D_800AA148), runs the GB audio frame and mirrors the
 * emulated NR52 (0xFF26) register into GB memory; while D_800AA148 is set it blanks video.
 * Seen in play (2026-11-13) ran every frame from the moment JP Green booted in the N64 GB player.
 */
void GbEmu_UpdateAudioOrBlankVideo(UNUSED s32 arg0) {
    if ((*(u8*)&D_81156546 == 0) && (D_800AA148 == 0)) {
        GbAudio_UpdateFrame();
        ((u8*)D_81156550)[0xFF26] = GbMem_ReadIoRegister(0xFF26);
    }
    if (D_800AA148 != 0) {
        osViBlack(1);
    }
}

extern u16 D_811248C0[];
extern u16 D_81124940[];
extern u16 D_811249C0[];
extern u16 D_81124A40[];
extern u16 D_81124AC0[];
extern u16 D_81124B40[];
extern u16 D_81124BC0[];
extern u16 D_81124C40[];
/**
 * Draws a 46x46 framed panel (8x8 edge and corner tiles from sUiGraphics) with a
 * solid interior, used behind each party icon on the loading screen.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void GbEmu_DrawFramedPanel(u16* arg0) {
    s32 i;
    s32 j;

    for (i = 1; i != 5; i++) {
        GbEmu_BlitWithPixelOp(&arg0[i * 8], D_81124940, 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(&arg0[38 * 320 + i * 8], D_81124BC0, 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(&arg0[i * 8 * 320], D_81124A40, 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(&arg0[i * 8 * 320 + 38], D_81124AC0, 0xFFFF, 8, 8);
    }
    GbEmu_BlitWithPixelOp(arg0, D_811248C0, 0, 8, 8);
    GbEmu_BlitWithPixelOp(&arg0[38], D_811249C0, 0, 8, 8);
    GbEmu_BlitWithPixelOp(&arg0[38 * 320], D_81124B40, 0, 8, 8);
    GbEmu_BlitWithPixelOp(&arg0[38 * 320 + 38], D_81124C40, 0, 8, 8);

    for (j = 0; j < 30; j++) {
        for (i = 0; i < 30; i++) {
            arg0[(j + 8) * 320 + i + 8] = 0xC14;
        }
    }
}

extern u16 D_81129AB8[];
extern u16 D_8112A138[];
extern u16 D_81129238[];
extern u16 D_811296B8[];
extern u16 D_81129D38[];
extern u16 D_8112A538[];
extern u16 D_81129638[];
extern u8 D_811565E1;

void func_81106AA0(s32 addr, s32 frame) {
    s32 i;

    for (i = 0; i < 6; i++) {
        func_81103C40(addr, (u8*)&D_81129AB8[frame * 0x28], 0, 8, 5);
        addr += 0x10;
    }
    func_81103C40(addr, (u8*)&D_8112A138[frame * 0x40], 0, 8, 8);
    addr += 0x1406;
    for (i = 0; i < 5; i++) {
        func_81103C40(addr, (u8*)&D_81129238[frame * 0x40], 0, 8, 8);
        addr += 0x1400;
    }
    func_81103C40(addr, (u8*)&D_811296B8[frame * 0x40], 0, 8, 8);
    addr += 0x10;
    switch (D_811565E1) {
        case 1:
            i = 7;
            break;
        case 2:
            i = 0xA;
            break;
        case 3:
            i = 0xB;
            break;
        default:
            i = 6;
            break;
    }
    for (; i > 0; i--) {
        func_81103C40(addr + 0x780, (u8*)&D_81129AB8[frame * 0x28], 0, 8, 5);
        addr += 0x10;
    }
    func_81103C40(addr, (u8*)&D_81129D38[frame * 0x40], 0, 8, 8);
    addr -= 0x13FA;
    func_81103C40(addr, (u8*)&D_8112A538[frame * 0x40], 0, 8, 8);
    addr -= 0x1400;
    func_81103C40(addr, (u8*)&D_8112A538[frame * 0x40], 0, 8, 8);
    addr -= 0x1400;
    func_81103C40(addr, (u8*)D_81129638, 0, 8, 8);
}

extern s32 D_811565C0;
extern s32 D_811565C4;
extern u32 D_811565C8;
extern u32 D_811565CC;
extern u16* D_811565D0;
extern u16* D_811565D4;
extern u32 D_811565D8;
extern u8 D_811565E0;
extern u8 D_811565E1;
extern u16 D_811228C0[];
extern u16 D_81124CC0[];
extern u16 D_81124D40[];
extern u16 D_81124DC0[];
extern u16 D_811270E8[];
extern u16 D_81127390[];
extern u16 D_81127638[];
extern u16 D_811278E0[];
extern u16 D_81127B88[];
extern u8 D_8112A938[];
void GbEmu_DrawTextCommands(u16*, u8*);
void GbEmu_DrawFramedPanel(u16* arg0);
u32 func_80053A80(void);
M2C_UNK func_8005C0A0();
void func_81106CC8(u16* dst, u8 (*arg1)[0xC80], s32 arg2, s32 arg3) {
    s32 y;
    s32 x;
    u16* row;
    s32 j;
    s32 step;
    s32 i;

    D_811565C0 = (s32)dst;
    step = 0x5000;
    for (y = 0; y < 0x14000; y += step) {
        row = dst + y;
        for (j = 0; j != 320u; j += 64) {
            GbEmu_BlitWithPixelOp(row, D_811228C0, 0xFFFF, 64, (y == 0xF000) ? 48 : 64);
            row += 64;
        }
    }

    D_811565D0 = (u16*)GbEmu_AllocAligned64(0x2580, 0);
    _bcopy(dst + 0x10540, D_811565D0, 0x2580);
    D_811565D4 = (u16*)GbEmu_AllocAligned64(0x2580, 0);
    bzero(D_811565D4, 0x2580);
    GbEmu_DrawTextCommands(D_811565D4, D_8112A938);

    for (i = 0; i < 6; i++) {
        GbEmu_DrawFramedPanel(dst + 0xB916 + i * 46);
        osInvalDCache(arg1[i], sizeof(arg1[i]));
        GbEmu_BlitWithPixelOp(dst + 0xBCD9 + i * 46, (u16*)arg1[i], 0, 40, 40);
    }

    for (j = 0; j < 6; j++) {
        for (i = 0; i < 320; i++) {
            dst[(j + 27) * 320 + i] = 0x25A;
            dst[(j + 121) * 320 + i] = 0x25A;
        }
    }

    for (i = 0; i < 320; i += 8) {
        GbEmu_BlitWithPixelOp(dst + 33 * 320 + i, D_81124CC0, 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(dst + 113 * 320 + i, D_81124D40, 0xFFFF, 8, 8);
    }

    for (j = 0; j < 72; j++) {
        for (i = 0; i < 320; i++) {
            dst[(j + 41) * 320 + i] = 0x2BA4;
        }
    }

    switch (arg2) {
        case 1:
            D_811565C4 = (s32)((u8*)dst + 2);
            break;
        case 2:
            D_811565C4 = (s32)((u8*)dst + 4);
            break;
        case 3:
            D_811565C4 = (s32)((u8*)dst + 6);
            break;
        default:
            D_811565C4 = (s32)dst;
            break;
    }

    GbEmu_BlitWithPixelOp(dst + 0x4E38, D_81127B88, 0, 0x56, 0x21);
    GbEmu_BlitWithPixelOp((u16*)(D_811565C4 + 0x61E0), D_81124DC0, 0, 0x3C, 0x4B);

    switch (arg3) {
        case 0:
            GbEmu_BlitWithPixelOp((u16*)(D_811565C4 + 0x7608), D_811270E8, 0, 0x13, 0x11);
            break;
        case 1:
            GbEmu_BlitWithPixelOp((u16*)(D_811565C4 + 0x7608), D_81127390, 0, 0x13, 0x11);
            break;
        case 2:
            GbEmu_BlitWithPixelOp((u16*)(D_811565C4 + 0x7608), D_81127638, 0, 0x13, 0x11);
            break;
        case 3:
            GbEmu_BlitWithPixelOp((u16*)(D_811565C4 + 0x7608), D_811278E0, 0, 0x13, 0x11);
            break;
    }

    D_811565E1 = arg2;
    func_81106AA0(D_811565C4 + 0x87BA, 0);
    func_8005C0A0();
    D_811565E0 = 0;
    D_811565D8 = 0x800000;
    D_811565C8 = func_80053A80();
    D_811565CC = 0;
}

/**
 * Adds a scrolling image layer to the destination with per-channel saturation.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void GbEmu_BlendScrollingLayer(u16* arg0, u16* arg1, s16* arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 j;
    s32 var_v1;
    s32 var_t4;

    for (j = 0; j < arg3; j++) {
        for (i = 0; i < 320; i++) {
            var_v1 = (arg0[(j * 320) + ((arg4 + i) % 320)] & 0xF800) + (arg1[(j * 320) + i] & 0xF800);
            if (var_v1 > 0xF800) {
                var_v1 = 0xF800;
            }
            var_t4 = var_v1;
            var_v1 = (arg0[(j * 320) + ((arg4 + i) % 320)] & 0x7C0) + (arg1[(j * 320) + i] & 0x7C0);
            if (var_v1 > 0x7C0) {
                var_v1 = 0x7C0;
            }
            var_t4 |= var_v1;
            var_v1 = (arg0[(j * 320) + ((arg4 + i) % 320)] & 0x3E) + (arg1[(j * 320) + i] & 0x3E);
            if (var_v1 > 0x3E) {
                var_v1 = 0x3E;
            }
            arg2[(j * 320) + i] = var_t4 | var_v1;
        }
    }
}

extern u32 D_811565DC;
extern u32 D_811565D8;
extern u8 D_811565E0;
extern s32 D_811565C4;
extern u32 D_811565C8;
extern u32 D_811565CC;
extern s32 D_811565C0;
extern u16* D_811565D4;
extern u16* D_811565D0;
void func_81106AA0(s32, s32);
void func_8110724C(void) {
    if ((osGetCount() - D_811565DC) > D_811565D8) {
        D_811565DC = osGetCount();
        D_811565E0 = (D_811565E0 + 1) & 7;
        func_81106AA0(D_811565C4 + 0x87BA, D_811565E0);
        if (D_811565D8 > 0x80000) {
            D_811565D8 -= D_811565D8 >> 8;
        }
    }
    if ((osGetCount() - D_811565C8) >= 0x200000) {
        D_811565C8 = osGetCount();
        D_811565CC++;
        if (D_811565CC >= 0x140) {
            D_811565CC = 0;
        }
        GbEmu_BlendScrollingLayer(D_811565D4, D_811565D0, (s16*)(D_811565C0 + 0x20A80), 0xF, D_811565CC);
        func_8005C0A0();
    }
}
