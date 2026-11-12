/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_emulator/gb_tower_emulator_7F9A0.c. */

#include "global.h"
#include "fragments/gb_tower_emulator/gb_tower_emulator.h"
#include "game_state.h"
#include "jpeg_stream.h"
#include "scheduler.h"
#include "gfx_rect.h"
#include "controller.h"
#include "memory.h"
#include "variables.h"
#include "fragments/fragment000_80C00/gb_tower_emulator_7F9A0_types.h"
typedef struct unk_func_812009D0 {
  /* 0x00 */ u8 unk00[0x34];
  /* 0x34 */ u8 data[0x10];  
  /* 0x44 */ u16 unk_44;
  /* 0x46 */ u8 unk_46;
  /* 0x47 */ u8 unk47;
  /* 0x48 */ u8 unk_48;
  /* 0x49 */ u8 unk_49;
  /* 0x4A */ u8 unk_4A;
} unk_func_812009D0;
extern OSThread gGbPakServiceThread;
extern u8 gGbPakServiceThreadStack[0x1000];
extern OSMesg gGbPakServiceQueueMessages[4];
extern OSMesgQueue gGbPakServiceQueue;
extern OSMesgQueue* gGbPakSiEventQueue;
extern volatile u8 gGbPakServiceThreadActive;
extern u8 gGbEmuPresentationMode;
extern unk_D_8122C4FA gGbEmuButtonBindingSelections;
extern u8* gGbEmuFont1Data;
extern u8* gGbEmuFont2Data;
void func_812070A0(void);
void GbApu_SelectRegionClock(s32);
void GbApu_QueueRegisterWrite(u16, u8, u16);
void GbApu_ResetChannels(void);
void GbApu_Reset(unk_D_8122B2F8*);
void func_811173F4(void);
void GbAudio_SetMenuSoundMode(s32);
#define GB_EMU_PAL_Y_SCALE 0.833f

#include "m2c_macros.h"

s32 GbEmu_PixelOpDitherA(s32 arg0, s32 arg1);
s32 GbEmu_PixelOpDitherB(s32 arg0, s32 arg1);
s32 GbEmu_PixelOpAverage555(s32 arg0, s32 arg1);
s32 GbEmu_PixelOpReplace(UNUSED s32 arg0, s32 arg1);
void GbEmu_BlitWithPixelOp(u16* dst, u16* src, s32 mode, s32 width, s32 height);
void GbEmu_BlitTinted(u16* dst, u16* src, s32 color, s32 width, s32 height);
void GbEmu_BlendColorWithAlphaMap(u16* dst, u8* alpha_map, s32 color, s32 width, s32 height, u32 alpha_stride);
void GbEmu_Delay(OSTime arg0);
void GbEmu_BlendScrollingLayer(u16* arg0, u16* arg1, s16* arg2, s32 arg3, s32 arg4);

M2C_UNK func_8005C670(s32, M2C_UNK, u16, M2C_UNK *, s32); /* extern */
extern M2C_UNK D_81156480;
void func_81101FA0(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(&D_81156480, s8 *, 0x1F) = arg2;
    func_8005C670(M2C_FIELD(arg0, s32 *, 0x50), 1, arg1, &D_81156480, 0x20);
}

/**
 * Puts the MBC1 into a known state: RAM enable (0x0A), RAM banking mode,
 * bank 0, ROM banking mode, ROM bank 1. Caches pakRomBank/pakRamBank/pakMbcMode.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbPak_InitializeCartridgeMapper(unk_D_8122B2C0* arg0) {
  s32 ret;

  if (!(ret = GbPak_WriteFilledRegisterBlock(arg0, 0, 0xA))    && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 1))
   && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, 0)) && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 0))
   && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, 0)) && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x2100, 1))) {
      *((u8*)arg0 + 0x9D) = 1;
      *((u8*)arg0 + 0x9E) = 0;
      *((u8*)arg0 + 0x9F) = 0;
  }
  
  return ret;
}

/*
 * func_811020A8
 *
 * Operates on a record arg0 that looks like the one GbPak_TransferBankedRam
 * takes (it holds a handle at 0x50 and is passed to func_81102344 in both),
 * but that is inferred from those uses only. Sets the byte at 0xA2 to 2 and
 * saves then clears the byte at 0x98. Calls func_81102344(arg0, word94 >> 13) (the same
 * bank-select helper GbPak_TransferBankedRam uses with address / 0x2000);
 * if that returns 0, calls func_8005C670 with the handle at 0x50, the
 * mode 0 (func_81101FA0 passes 1 here), the address (word94 & 0x1FFF) | 0xA000,
 * the buffer D_811564A0 and a length of 0x20; if that also returns 0, calls
 * func_80057910(D_811564A0, entry, 0x20) where entry is the 0x20-byte record
 * number byte9C of the table at D_811564C0. If the last result is 0 the byte
 * at 0xA2 is reset to 0. The saved byte at 0x98 is restored and the first
 * non-zero (or final) result is returned.
 *
 * What func_8005C670 mode 0 and func_80057910 do, and what the two tables
 * hold, is not established. Matching notes: the unused first local `pad`
 * places `sp28` at sp+0x28, and the table index is scaled as
 * `(x << 1) << 4` because a single `<< 5` (or `* 0x20`) uses one temporary
 * register fewer and does not match.
 */
s32 func_81102344(u8*, s32);
s32 func_80057910(M2C_UNK *, void *, u32); /* extern */
extern M2C_UNK D_811564A0;
extern M2C_UNK D_811564C0;
s32 func_811020A8(void *arg0) {
    s32 pad; // FAKE: stack padding
    s32 sp28;
    s32 var_v0;
    s32 var_v1;

    M2C_FIELD(arg0, s8 *, 0xA2) = 2;
    sp28 = (s32) M2C_FIELD(arg0, u8 *, 0x98);
    M2C_FIELD(arg0, u8 *, 0x98) = 0U;
    var_v0 = func_81102344(arg0, (u32) M2C_FIELD(arg0, u32 *, 0x94) >> 0xD);
    var_v1 = var_v0;
    if (var_v0 == 0) {
        var_v0 = func_8005C670(M2C_FIELD(arg0, s32 *, 0x50), 0, ((M2C_FIELD(arg0, u32 *, 0x94) & 0x1FFF) | 0xA000) & 0xFFFF, &D_811564A0, 0x20);
        var_v1 = var_v0;
        if (var_v0 == 0) {
            var_v0 = func_80057910(&D_811564A0, (u8 *)&D_811564C0 + ((M2C_FIELD(arg0, u8 *, 0x9C) << 1) << 4), 0x20);
            var_v1 = var_v0;
        }
    }
    if (var_v0 == 0) {
        M2C_FIELD(arg0, s8 *, 0xA2) = 0;
    }
    M2C_FIELD(arg0, u8 *, 0x98) = (u8) sp28;
    return var_v1;
}

s32 func_80051110(s32, s8 *, s8 *);             /* extern */

s32 func_81102168(s8 *arg0) {
    s32 temp_v0;
    s32 var_v1;

    M2C_FIELD(arg0, s8 *, 0xA2) = 1;
    temp_v0 = func_80051110(M2C_FIELD(arg0, s32 *, 0x50), arg0 + 0x9B, arg0);
    var_v1 = temp_v0;
    if ((temp_v0 == 0) && ((M2C_FIELD(arg0, u8 *, 0x9B) & 9) != 9)) {
        var_v1 = 0x63;
    }
    if (var_v1 != 0) {
        return var_v1;
    }
    M2C_FIELD(arg0, s8 *, 0xA2) = 0;
    return 0;
}

s32 func_81101FE8(s8 *);                            /* extern */
s32 GbPak_WriteVerifiedSramBlock(s32, s32, s32);                     /* extern */

/**
 * Before each transfer: checks the connector, resets the mapper, re-reads the
 * cartridge header ID and compares it with cartridgeId (detects a swapped cartridge),
 * then re-verifies the RAM probe block if one was written.
 * @unverified Name guessed from the code; comment kept.
 */
s32 GbPak_ProbeCartridge(u8 *arg0) {
    s32 ret;

    if (((!arg0) && (!arg0)) && (!arg0)) {  // FAKE
    }
    ret = 0;
    if (!(M2C_FIELD(arg0, u8 *, 0x9B) & 1)) {
        ret = func_81102168(arg0);
        if (ret == 0) {
            ret = func_81101FE8(arg0);
            if ((ret == 0) && (M2C_FIELD(arg0, u8 *, 0x9B) & 1) && (M2C_FIELD(arg0, u8 *, 0x98) != 0)) {
                ret = func_811020A8(arg0);
                if (ret == 0) {
                    ret = GbPak_WriteVerifiedSramBlock(M2C_FIELD(arg0, u8 *, 0x9C), M2C_FIELD(arg0, s32 *, 0x94), M2C_FIELD(arg0, u8 *, 0x98));
                }
            }
        }
        if (ret != 0) {
            M2C_FIELD(arg0, u8 *, 0x9B) &= ~1;
        }
    }
    return ret;
}

/**
 * Selects the MBC1 ROM bank for a 0x4000-0x7FFF read of a linear ROM address,
 * switching to ROM banking mode and writing the upper bank bits when needed.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbPak_SelectRomAddress(unk_D_8122B2C0* arg0, s32 arg1) {
    s32 temp_a2;
    s32 var_v1;

    var_v1 = 0;
    M2C_FIELD(arg0, u8*, 0x9E) = 0xFF;
    if (M2C_FIELD(arg0, u8*, 0x9F) != 0) {
        M2C_FIELD(arg0, u8*, 0x9D) = 0xFF;
        var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 0);
        if (var_v1 == 0) {
            M2C_FIELD(arg0, u8*, 0x9F) = 0;
        }
    }
    if (var_v1 == 0) {
        if (arg1 != M2C_FIELD(arg0, u8*, 0x9D)) {
            temp_a2 = arg1 / 32;
            if (temp_a2 != ((s32)M2C_FIELD(arg0, u8*, 0x9D) / 32)) {
                var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, temp_a2);
            }
            if (var_v1 == 0) {
                var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x2100, arg1);
                if (var_v1 == 0) {
                    M2C_FIELD(arg0, u8*, 0x9D) = arg1;
                }
            }
        }
    }
    return var_v1;
}

/**
 * Selects an 8 KB cartridge RAM bank (MBC1 RAM banking mode).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbPak_SelectRamBank(unk_D_8122B2C0* arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    M2C_FIELD(arg0, u8*, 0x9D) = 0xFF;
    if (M2C_FIELD(arg0, u8*, 0x9F) != 1) {
        M2C_FIELD(arg0, u8*, 0x9E) = 0xFF;
        var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 1);
        if (var_v1 == 0) {
            M2C_FIELD(arg0, u8*, 0x9F) = 1;
        }
    }
    if ((var_v1 == 0) && (arg1 != M2C_FIELD(arg0, u8*, 0x9E))) {
        var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, arg1);
        if (var_v1 == 0) {
            M2C_FIELD(arg0, u8*, 0x9E) = arg1;
        }
    }
    return var_v1;
}

typedef struct GbpakChannel811023DC {
    /* 0x00 */ char unk00[0x4E];
    /* 0x4E */ u8 checksum[2];
    /* 0x50 */ OSPfs* pfs;
    /* 0x54 */ u8* buf;
    /* 0x58 */ u8* romBuf;
    /* 0x5C */ u8* sramBuf;
    /* 0x60 */ volatile u8* bankState;
    /* 0x64 */ volatile u8* sramState;
    /* 0x68 */ u8* bankList;
    /* 0x6C */ u8* bankEntry;
    /* 0x70 */ u8* ramBuf;
    /* 0x74 */ u8* blockState;
    /* 0x78 */ u8* verifyBuf;
    /* 0x7C */ u8* blockDirty;
    /* 0x80 */ s32 size;
    /* 0x84 */ s32 sum;
    /* 0x88 */ char unk88[0x4];
    /* 0x8C */ s32 addr;
    /* 0x90 */ u32 ramSize;
    /* 0x94 */ s32 sramAddr;
    /* 0x98 */ u8 unk98;
    /* 0x99 */ volatile u8 request;
    /* 0x9A */ volatile u8 error;
    /* 0x9B */ u8 status;
    /* 0x9C */ u8 channel;
    /* 0x9D */ char unk9D[0x4];
    /* 0xA1 */ u8 unkA1;
    /* 0xA2 */ u8 unkA2;
    /* 0xA3 */ char unkA3[0x1];
} GbpakChannel811023DC; // size = 0xA4
extern GbpakChannel811023DC D_811561C8[4];
/**
 * Reads the Transfer Pak status; returns 0 only when bit 7 is set and bit 6 is clear.
 * @unverified Name guessed from the code; comment kept.
 */
s32 GbPak_CheckTransferStatus(OSPfs* arg0) {
    s32 ret = osGbpakGetStatus(arg0, &D_811561C8[arg0->channel].status);

    if (ret == 0) {
        ret = (D_811561C8[arg0->channel].status & 0xC0) ^ 0x80;
    }
    return ret;
}

s32 GbPak_ProbeCartridge(u8*);
s32 func_81102280(u8*, s32);
s32 GbPak_CheckTransferStatus(OSPfs*);
s32 func_81102460(u8* arg0) {
    s32 ret;
    u8* buf;
    s32 addr;
    s32 remaining;
    s32 size;
    s32 sum;
    s32 off;

    ret = GbPak_ProbeCartridge(arg0);
    buf = M2C_FIELD(arg0, u8**, 0x54);
    addr = M2C_FIELD(arg0, s32*, 0x8C);
    remaining = M2C_FIELD(arg0, s32*, 0x80);
    if ((ret == 0) && (addr < 0x4000)) {
        if ((addr + remaining) >= 0x4001) {
            size = 0x4000 - addr;
        } else {
            size = remaining;
        }
        ret = osGbpakReadWrite(M2C_FIELD(arg0, OSPfs**, 0x50), 0, addr, buf, size);
        if (ret == 0) {
            sum = 0;
            for (ret = size; ret != 0; ret--) {
                sum += *buf++;
            }
            M2C_FIELD(arg0, s32*, 0x84) += sum;
            remaining -= size;
            addr = 0x4000;
        }
    }
    while ((ret == 0) && (remaining != 0)) {
        ret = func_81102280(arg0, addr / 0x4000);
        if (ret == 0) {
            off = addr & 0x3FFF;
            if ((off + remaining) >= 0x4001) {
                size = 0x4000 - off;
            } else {
                size = remaining;
            }
            ret = osGbpakReadWrite(M2C_FIELD(arg0, OSPfs**, 0x50), 0, (off | 0x4000) & 0xFFFF, buf, size);
            if (ret == 0) {
                sum = 0;
                for (ret = size; ret != 0; ret--) {
                    sum += *buf++;
                }
                M2C_FIELD(arg0, s32*, 0x84) += sum;
                remaining -= size;
                addr = (addr + 0x4000) & ~0x3FFF;
            }
        }
    }
    if (ret == 0) {
        ret = GbPak_CheckTransferStatus(M2C_FIELD(arg0, OSPfs**, 0x50));
    }
    return ret;
}

s32 GbPak_ProbeCartridge(u8*);
s32 func_81102344(u8*, s32);
s32 GbPak_CheckTransferStatus(OSPfs*);

/**
 * Reads (is_write == 0) or writes (is_write != 0) transferSize bytes of banked cartridge
 * RAM at gbAddress, selecting each 8 KB bank as it goes.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbPak_TransferBankedRam(u8* arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    u8* var_s3;
    s32 var_v0;
    s32 var_v1;
    s32 var_s2;

    var_v0 = GbPak_ProbeCartridge(arg0);
    var_v1 = var_v0;
    var_s3 = M2C_FIELD(arg0, u8**, 0x54);
    var_s2 = M2C_FIELD(arg0, s32*, 0x8C);
    var_s1 = M2C_FIELD(arg0, s32*, 0x80);
    while ((var_v0 == 0) && (var_s1 != 0)) {
        var_v0 = func_81102344(arg0, var_s2 / 0x2000);
        var_v1 = var_v0;
        if (var_v0 == 0) {
            temp_v0 = var_s2 & 0x1FFF;
            if ((temp_v0 + var_s1) >= 0x2001) {
                var_s0 = 0x2000 - temp_v0;
            } else {
                var_s0 = var_s1;
            }
            var_v0 = osGbpakReadWrite(M2C_FIELD(arg0, OSPfs**, 0x50), arg1, (temp_v0 | 0xA000) & 0xFFFF, var_s3, var_s0);
            var_v1 = var_v0;
            var_s3 += var_s0;
            var_s1 -= var_s0;
            var_s2 = (var_s2 + 0x2000) & ~0x1FFF;
        }
    }
    if (var_v0 == 0) {
        var_v1 = GbPak_CheckTransferStatus(M2C_FIELD(arg0, OSPfs**, 0x50));
    }
    return var_v1;
}

/* One 6-byte entry of the bank list; the list ends with a 0xFF bank byte. */
typedef struct GbpakBankEntry {
    /* 0x0 */ u8 bank; // bit 7 set: SRAM bank, clear: ROM bank
    /* 0x1 */ u8 unk1[5];
} GbpakBankEntry; // size = 0x6
extern volatile u8 D_81156476;
extern OSMesgQueue D_81156458;
s32 func_8004CFB0(OSMesgQueue*, s32, s32);
void func_811027A8(GbpakChannel811023DC* ch) {
    GbpakBankEntry* entry;

    if ((D_81156476 != 0) && (ch->request == 0)) {
        if (ch->error) {
            return;
        }
        entry = (GbpakBankEntry*)ch->bankList;
        if (D_81156476 == 2) {
            D_81156476 = 0;
            return;
        }
        for (; entry->bank != 0xFF; entry++) {
            if (entry->bank & 0x80) {
                volatile u8* state = &ch->sramState[entry->bank & 0x7F];
                if (*state) {
                    *state = 2;
                    ch->addr = (entry->bank & 0x7F) << 13;
                    ch->buf = ch->sramBuf + ch->addr;
                    ch->size = 0x2000;
                    ch->request = 7;
                    ch->unkA1 = 1;
                    goto found;
                }
            } else {
                volatile u8* state = &ch->bankState[entry->bank & 0x7F];
                if (*state) {
                    *state = 2;
                    ch->request = 6;
                    ch->addr = (entry->bank & 0x7F) << 14;
                    ch->buf = ch->romBuf + ch->addr;
                    ch->size = 0x2000;
                    ch->unkA1 = 1;
                    goto found;
                }
            }
        }

        if (((*((u16 *) ch->checksum)) ^ ((ch->sum - ch->checksum[0]) - ch->checksum[1])) & 0xFFFF) {
            ch->error = 2;
            return;
        }
        ch->request = 4;
        func_8004CFB0(&D_81156458, ch->channel, 1);
        D_81156476 = 2;
        return;
    found:
        ch->bankEntry = (u8*)entry;
        func_8004CFB0(&D_81156458, ch->channel, 1);
    }
}

extern volatile u8 D_81156475;
extern volatile u8 D_81156476;
extern OSMesgQueue D_81156458;
s32 func_8004CFB0(OSMesgQueue*, s32, s32);

s32 func_81102970(s32 chan, s32 bank) {
    u8* entry;
    u8* state;

    while (D_81156475 != 0) {
    }
    if ((D_81156476 == 0) || (D_811561C8[chan].request != 0) || (D_811561C8[chan].error != 0)) {
        return -2;
    }
    for (entry = D_811561C8[chan].bankList; *entry != 0xFF; entry += 6) {
        if (bank == *entry) {
            goto found;
        }
    }
    return -1;

found:
    state = &D_811561C8[chan].bankState[bank];
    if (*state != 0) {
        *state = 3;
        D_811561C8[chan].request = 6;
        D_811561C8[chan].addr = (*entry & 0x7F) << 14;
        D_811561C8[chan].buf = D_811561C8[chan].addr + D_811561C8[chan].romBuf;
        D_811561C8[chan].size = 0x2000;
        D_811561C8[chan].bankEntry = entry;
        if (!entry && !entry && !entry) {} // FAKE: empty test found by the permuter; only changes instruction scheduling
        func_8004CFB0(&D_81156458, D_811561C8[chan].channel, 1);
        while (D_81156475 != 0) {
        }
    }
    if (D_811561C8[chan].error != 0) {
        return -1;
    }
    return 0;
}

extern volatile u8 D_81156475;
extern volatile u8 D_81156476;
extern volatile u8 D_81156477;
extern OSMesgQueue D_81156458;
s32 func_8004CFB0(OSMesgQueue*, s32, s32);

s32 func_81102AC8(s32 arg0) {
    s32 chan = arg0;
    GbpakChannel811023DC* ch;
    GbpakChannel811023DC* ch2;
    u32 i;

    if (D_81156475 != 0) {
        return 1;
    }
    ch = &D_811561C8[chan];
    ch2 = ch;
    if (ch->error != 0) {
        return 4;
    }
    for (i = 0; i < ch2->ramSize >> 8; i++) {
        if (ch->blockState[i] == 0) {
            if (D_81156476 == 0 && D_81156477 != 0) {
                ch->blockState[i] = 1;
                ch->blockDirty[i] = 0;
                ch->request = 5;
                ch->addr = i << 8;
                ch->buf = ch->ramBuf + (i << 8);
                ch->size = 0x100;
                func_8004CFB0(&D_81156458, chan, 1);
                return 2;
            }
            return 3;
        }
    }
    if (ch2->error == 0 && (ch2->status & 1)) {
        ch->request = 4;
        func_8004CFB0(&D_81156458, chan, 1);
    }
    return 0;
}
