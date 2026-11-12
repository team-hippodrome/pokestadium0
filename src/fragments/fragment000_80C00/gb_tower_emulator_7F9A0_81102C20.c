/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
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
void func_81101FA0(void *arg0, s32 arg1, s32 arg2);

s32 GbPak_InitializeCartridgeMapper(unk_D_8122B2C0* arg0);

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
s32 func_811020A8(void *arg0);

s32 func_80051110(s32, s8 *, s8 *);             /* extern */

s32 GbPak_CheckCartInserted(s8 *arg0);

s32 func_81101FE8(s8 *);                            /* extern */
s32 GbPak_WriteVerifiedSramBlock(s32, s32, s32);                     /* extern */

/*
 * GbPak_ProbeCartridge
 *
 * Returns 0 right away when bit 0 of the byte at arg0 + 0x9B is set.
 * Otherwise runs GbPak_CheckCartInserted(arg0), then func_81101FE8(arg0) while the
 * result is 0, then, if bit 0 of the byte at 0x9B is (now) set and the byte
 * at 0x98 is non-zero, func_811020A8(arg0), then
 * GbPak_WriteVerifiedSramBlock(byte 0x9C, word 0x94, byte 0x98), stopping at the first
 * non-zero result. If the result is non-zero, clears bit 0 of the byte at
 * 0x9B. Returns the result.
 *
 * Same record as GbPak_TransferBankedRam and func_811020A8 take; what the
 * flag bit and the other fields mean is not established.
 *
 * Matching note: the empty `if` on `arg0` has no meaning of its own. It was
 * found with decomp-permuter and is the only form tried that makes the
 * compiler copy arg0 to s0 before the first load, as the ROM does; the
 * triple test is needed (one or two do not match). The same kind of empty
 * test already exists in Registration_WriteTeam.
 */
s32 GbPak_ProbeCartridge(u8 *arg0);

s32 GbPak_SelectRomAddress(unk_D_8122B2C0* arg0, s32 arg1);

s32 GbPak_SelectRamBank(unk_D_8122B2C0* arg0, s32 arg1);

typedef struct GbpakChannel811023DC {
    /* 0x00 */ char unk00[0x48];
    /* 0x48 */ u8 cartType;
    /* 0x49 */ char unk49[0x3];
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ char unk4D[0x1];
    /* 0x4E */ u8 checksum[2];
    /* 0x50 */ OSPfs* pfs;
    /* 0x54 */ u8* buf;
    /* 0x58 */ u8* romBuf;
    /* 0x5C */ u8* sramBuf;
    /* 0x60 */ u8* bankState;
    /* 0x64 */ u8* sramState;
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
    /* 0x9D */ char unk9D[0x3];
    /* 0xA0 */ u8 unkA0;
    /* 0xA1 */ u8 unkA1;
    /* 0xA2 */ u8 unkA2;
    /* 0xA3 */ char unkA3[0x1];
} GbpakChannel811023DC; // size = 0xA4
GbpakChannel811023DC D_811561C8[4];
s32 GbPak_CheckTransferStatus(OSPfs* arg0);

s32 GbPak_ProbeCartridge(u8*);
s32 func_81102280(u8*, s32);
s32 GbPak_CheckTransferStatus(OSPfs*);
s32 GbPak_ReadRomSummed(u8* arg0);

s32 GbPak_ProbeCartridge(u8*);
s32 func_81102344(u8*, s32);
s32 GbPak_CheckTransferStatus(OSPfs*);

s32 GbPak_TransferBankedRam(u8* arg0, s32 arg1);



extern volatile u8 D_81156475;
extern volatile u8 D_81156476;
extern OSMesgQueue D_81156458;
s32 func_8004CFB0(OSMesgQueue*, s32, s32);

s32 GbPak_RequestBankLoad(s32 chan, s32 bank);

extern volatile u8 D_81156475;
extern volatile u8 D_81156476;
extern volatile u8 D_81156477;
extern OSMesgQueue D_81156458;
s32 func_8004CFB0(OSMesgQueue*, s32, s32);

s32 GbPak_WriteBackDirtySramBlock(s32 arg0);

/**
 * Reads each clean 0x100-byte block of cartridge RAM back and compares it with the cached copy; a
 * mismatch rewrites the block and restarts the pass, up to 20 times. Returns -1 on failure.
 * @unverified Name and comment from the code; no Transfer Pak was emulated.
 */
s32 GbPak_VerifyRamBlocks(s32 arg0) {
    GbpakChannel811023DC* ch2;
    GbpakChannel811023DC* ch;
    s32 retries;
    s32 r;
    u32 i;
    s32 off;

    ch = &D_811561C8[arg0];
    ch2 = ch;
    retries = 20;
    for (;;) {
        r = GbPak_WriteBackDirtySramBlock(arg0);
        if (r >= 3) {
        fail:
            for (i = 0; i < ch->ramSize >> 8; i++) {
                ch->blockState[i] = ch->blockDirty[i];
            }
            return -1;
        }
        if (r == 0) {
            break;
        }
    }
    while (D_81156475 != 0) {
    }
    if (ch->error != 0) {
        goto fail;
    }
restart:
    for (i = 0; i < ch2->ramSize >> 8; i++) {
        off = i << 8;
        if (ch->blockDirty[i] == 0) {
            ch->request = 2;
            ch->addr = i << 8;
            ch->size = 0x100;
            ch->buf = ch->verifyBuf;
            func_8004CFB0(&D_81156458, arg0, 1);
            while (D_81156475 != 0) {
            }
            if (ch->error != 0) {
                goto fail;
            }
            if (func_80057910(ch->verifyBuf, ch->ramBuf + (i << 8), 0x100) != 0) {
                if (retries == 0) {
                    goto fail;
                }
                if ((GbPak_CheckCartInserted((s8*)ch) != 0) || ((ch->unk98 != 0) && (func_811020A8(ch) != 0))) {
                    goto fail;
                }
                retries--;
                ch->request = 3;
                ch->addr = off;
                ch->buf = ch->ramBuf + off;
                ch->size = 0x100;
                func_8004CFB0(&D_81156458, arg0, 1);
                while (D_81156475 != 0) {
                }
                if (ch->error) {
                    goto fail;
                }
                goto restart;
            }
        }
    }
    return 0;
}

void func_80058260(u32*);
u32 func_80053A80(void);
M2C_UNK func_8005C0A0();

/**
 * Fills the 32-byte probe block (probePattern and unk_5D90) for the writable-RAM
 * probe: mode 3 all zeros, mode 2 all ones, mode 1 DP counters and osGetCount values
 * so the pattern differs each run.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void GbPak_PrepareProbeBlock(u32* arg0, s32 arg1) {
    s32 i;

    switch (arg1) {
        case 3:
            for (i = 0; i < 8; i++) {
                arg0[i] = 0;
            }
            break;
        case 2:
            for (i = 0; i < 8; i++) {
                arg0[i] = -1;
            }
            break;
        case 1:
            func_80058260(arg0);
            arg0[3] = func_80053A80();
            func_8005C0A0();
            func_80058260(arg0 + 4);
            arg0[7] = func_80053A80();
            break;
    }
}

void func_81102EB0(u8*, s32);

/**
 * Selects the SRAM bank for the address, then writes a 0x20-byte block at 0xA000 + offset and
 * reads it back until three writes in a row compare equal.
 * Seen in play (2026-11-12): wrote and read back 0x55, 0xAA and 0xAC blocks at GB 0xA000 when the
 * GB item started.
 */
s32 GbPak_WriteVerifiedSramBlock(s32 arg0, s32 arg1, s32 arg2) {
    GbpakChannel811023DC* ch = &D_811561C8[arg0];
    s32 ret;
    s32 n;
    u8* entry;
    u16 addr;

    ch->unk98 = 0;
    if (arg2 == 0) {
        return 0;
    }
    ch->unkA2 = 3;
    ret = func_81102344((u8*)ch, arg1 / 0x2000);
    n = 3;
    if (ret == 0) {
        entry = (u8*)&D_811564C0 + ((arg0 << 1) << 4);
        addr = (arg1 & 0x1FFF) | 0xA000;
        do {
            func_81102EB0(entry, n);
            ret = func_8005C670((s32)ch->pfs, 1, addr, (M2C_UNK*)entry, 0x20);
            if (ret == 0 && (ret = func_8005C670((s32)ch->pfs, 0, addr, &D_811564A0, 0x20)) == 0 &&
                (ret = func_80057910(&D_811564A0, entry, 0x20)) == 0 && --n == 0) {
                ch->unk98 = arg2;
                ch->sramAddr = arg1;
                ch->unkA2 = 0;
                break;
            }
        } while (ret == 0);
    }
    return ret;
}

extern s32 D_81156470;
extern OSPfs D_81156018[];
extern u8 D_81155E18[];
extern u8 D_81155F18[];
extern volatile u8 D_81156474;
s32 func_81102690(GbpakChannel811023DC*, s32);
s32 GbPak_CheckGen1SaveChecksum(s8*);

/**
 * Game Boy Pak I/O thread: takes a channel number from the queue and serves that channel's
 * request (init and read the cartridge ID, read or write cartridge RAM). 0xFF ends the thread.
 * Seen in play (2026-11-12): serviced requests 6 (bank load with checksum check), 8 (status) and
 * 4 (power off) while Green loaded. A bank whose 0x2000-byte sums differ from the table sets
 * error 1.
 */
void GbPak_IoThreadMain(s32 arg0) {
    s32 pad0; // FAKE
    s32 chan;
    OSPfs* pfs;
    s32 pad1; // FAKE
    u8 id[0x50];
    u8* idp;
    GbpakChannel811023DC* ch;
    s32 pad2; // FAKE

    for (;;) {
        if (D_81156458.validCount == 0) {
            D_81156475 = 0;
        }
        osRecvMesg(&D_81156458, (OSMesg*)&chan, OS_MESG_BLOCK);
        if (chan == 0xFF) {
            D_81156474 = 0;
            osDestroyThread(NULL);
        }
        ch = &D_811561C8[chan];
        pfs = &D_81156018[chan];
        D_81156475 = 1;
        idp = NULL;
        osGetCount();
        if (ch->request & 0x80) {
            bzero(id, 0x50);
            if (osGbpakInit(*(OSMesgQueue**)&D_81156470, pfs, chan) != 0) {
                goto error;
            }
            if (ch->request == 0x80) {
                idp = (u8*)ch;
                goto retry;
            }
            idp = id;
        retry:
            if (osGbpakReadId(pfs, (OSGbpakId*)idp, &ch->status) != 0) {
                goto error;
            }
            if (GbPak_CheckCartInserted((s8*)ch) != 0) {
                goto error;
            }
            if (func_81101FE8((s8*)ch) != 0) {
                goto error;
            }
            if (GbPak_CheckTransferStatus(pfs) != 0) {
                goto error;
            }
            if (!(ch->status & 1)) {
                goto error;
            }
            if (ch->unk98 != 0 && func_811020A8(ch) != 0) {
                goto error;
            }
            if (idp != (u8*)ch && bcmp(idp, ch, 0x50) != 0) {
                goto error;
            }
            ch->unk9D[3] = 0;
            ch->sum = 0;
            ch->unkA3[0] = 0;
            goto next;
        error:
            if (ch->unkA1 != 0 && --ch->unkA1 != 0 && idp != NULL) {
                idp = id;
                goto retry;
            }
            ch->error = 1;
            ch->request = 0;
            continue;
        }
    next:
        idp = (u8*)ch;
        switch (ch->request & 0x7F) {
            case 1:
                if (GbPak_ReadRomSummed((u8*)ch) != 0) {
                    goto error;
                }
                break;
            case 2:
                if (func_81102690(ch, 0) != 0) {
                    goto error;
                }
                break;
            case 3:
                if (func_81102690(ch, 1) != 0) {
                    goto error;
                }
                break;
            case 5:
                if (GbPak_ProbeCartridge((u8*)ch) != 0) {
                    goto error;
                }
                if (func_81102344((u8*)ch, (u32)ch->addr >> 13) != 0) {
                    goto error;
                }
                bcopy(ch->buf, D_81155E18, 0x100);
                if (osGbpakReadWrite(pfs, OS_WRITE, (ch->addr & 0x1FFF) | 0xA000, D_81155E18, ch->size) == 0 &&
                    osGbpakReadWrite(pfs, OS_READ, (ch->addr & 0x1FFF) | 0xA000, D_81155F18, ch->size) == 0 &&
                    bcmp(D_81155E18, D_81155F18, 0x100) == 0) {
                    break;
                }
                ch->blockState[(u32)ch->addr >> 8] = 0;
                goto error;
            case 6:
                *(s32*)ch->unk88 = ch->sum;
                if (GbPak_ReadRomSummed((u8*)ch) != 0) {
                    goto error;
                }
                if ((((u16*)ch->bankEntry)[1] ^ (ch->sum - *(s32*)ch->unk88)) & 0xFFFF) {
                    goto error;
                }
                *(s32*)ch->unk88 = ch->sum;
                ch->buf += ch->size;
                ch->addr += ch->size;
                if (GbPak_ReadRomSummed((u8*)ch) != 0) {
                    goto error;
                }
                if ((((u16*)ch->bankEntry)[2] ^ (ch->sum - *(s32*)ch->unk88)) & 0xFFFF) {
                    goto error;
                }
                ch->bankState[ch->bankEntry[0] & 0x7F] = 0;
                break;
            case 7:
            loop7:
                if (func_81102690(ch, 0) != 0) {
                    goto error;
                }
                if (GbPak_CheckGen1SaveChecksum((s8*)ch) != 0 && ch->unkA3[0] < 3) {
                    ch->unkA3[0]++;
                    goto loop7;
                }
                ch->sramState[ch->bankEntry[0] & 0x7F] = 0;
                break;
            case 8:
                if (GbPak_CheckTransferStatus(pfs) != 0) {
                    goto error;
                }
                break;
            case 4:
                ch->status &= ~1;
                if (osGbpakPower(ch->pfs, 0) != 0) {
                    goto error;
                }
                break;
        }
        ch->request = 0;
        ch->unkA1 = 0x18;
    }
}

extern volatile u8 D_81156474;
extern volatile u8 D_81156475;
extern volatile u8 D_81156476;
extern volatile u8 D_81156477;
extern s8 D_81156478;
extern s8 D_81156479;
extern s32 D_81156470;
extern OSMesgQueue D_81156458;
extern OSPfs D_81156018[4];
extern OSMesg D_811561B8[4];
extern OSThread D_81154C68;
extern u8 D_81155E18[];
void func_800567E0(OSMesgQueue*, OSMesg*, s32);
void func_80051B20(OSThread*, s32, void (*)(), s32, u8*, s32);
void func_8005C130(OSThread*);
void func_8004FD20(s32, s32);
void GbPak_IoThreadMain();
/**
 * Clears the four Transfer Pak channel records, gives each its OSPfs and starts the Game Boy Pak
 * I/O thread (GbPak_IoThreadMain) on the given message queue.
 * Seen in play (2026-11-12): runs when the GB item is entered, before the cartridge loads.
 */
void GbPak_StartIoThread(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    D_81156470 = arg2;
    D_81156474 = 1;
    D_81156475 = 0;
    D_81156476 = 0;
    D_81156477 = 0;
    D_81156478 = 0;
    D_81156479 = 0;
    func_8004FD20((s32) D_811561C8, 0x290);
    func_8004FD20((s32) &D_81156480, 0x20);
    for (i = 0; i < 4; i++) {
        D_811561C8[i].channel = i;
        D_811561C8[i].unkA1 = 0x18;
        D_811561C8[i].pfs = &D_81156018[i];
    }
    func_800567E0(&D_81156458, D_811561B8, 4);
    func_80051B20(&D_81154C68, arg0, GbPak_IoThreadMain, 0, D_81155E18, arg1);
    func_8005C130(&D_81154C68);
}

extern volatile u8 D_81156474;
extern volatile u8 D_81156475;
extern volatile u8 D_81156476;
extern volatile u8 D_81156477;
extern s8 D_81156478;
extern s8 D_81156479;
extern s32 D_81156470;
extern OSMesgQueue D_81156458;
void func_800515B0(s32, s32);
s32 func_8004CFB0(OSMesgQueue *, s32, s32);
/**
 * Waits for the I/O thread to go idle, sends it the 0xFF quit message and waits until it has
 * exited.
 * @unverified Name and comment from the code; no Transfer Pak was emulated.
 */
void GbPak_StopIoThread(s32 arg0) {
    s32 i;

    while (D_81156475 != 0) {
    }
    for (i = 0; i < 4; i++) {
        if ((1 << i) & arg0) {
            func_800515B0(*(s32 *)((u8 *)&D_811561C8[i] + 0x50), 0);
        }
    }
    while (D_81156475 != 0) {
    }
    func_8004CFB0(&D_81156458, 0xFF, 1);
    while (D_81156474 != 0) {
    }
    D_81156470 = 0;
    D_81156475 = 0;
    D_81156476 = 0;
    D_81156477 = 0;
    D_81156478 = 0;
    D_81156479 = 0;
}

extern u8* D_81156598;
extern u8* D_8115659C;
extern u16 D_81122260[];
extern u16 D_81122280[];
extern u16 D_811222A0[];
extern u16 D_811222C0[];
extern u16 D_811222E0[];
extern u16 D_81122300[];
extern u16 D_81122320[];
extern u16 D_81122340[];
extern u16 D_81122360[];
extern u16 D_81122380[];
extern u16 D_811223A0[];
extern u16 D_811223C0[];
/**
 * Draws a list of text commands into a 320-wide RGBA5551 image. Each command is
 * 0x80|flags, x, y, font height (0x0A = font1, 0x0C = font2), palette index, length,
 * then ASCII characters mapped through sFont1GlyphTable/sFont2GlyphTable.
 * A zero byte ends the list.
 * Seen in play (2026-11-12): opening the GB Tower menu (C-Up) passed the list 80 38 07 0C 0B 04 +
 * 4 glyphs (メニュー), 80 20 1B 0C 0A 08 + 8 glyphs (ゲームをつづける), C0 03 59 0C 09 0A + 10 glyphs
 * (このメニューをぬけて), matching flags, x, y, font height, palette, length and characters; the same glyph
 * bytes repeat for the same kana (71 65 4C 3B = メニュー).
 */
void GbEmu_DrawTextCommands(u16* fb, u8* cmd) {
    u8* ptr;
    u8* data;
    u8* src;
    u16* dst;
    u16* pal;
    u8 flags;
    u8 y;
    s32 width;
    s32 x;
    s32 dir;
    s32 trans;
    s32 tile_size;
    s32 row;
    s32 col;
    s32 n;

    flags = *cmd;
    ptr = cmd;
    while (flags) {
        trans = flags;
        x = ptr[1] + ((flags & 1) << 8);
        y = ptr[2];
        if (flags & 0x40) {
            dir = -1;
        } else {
            dir = 0;
        }
        dst = fb + ((y * 0x140) + x);
        trans &= 0x20;
        switch (ptr[3]) {
            case 0xC:
                width = 0xC;
                tile_size = 0xC;
                data = D_8115659C;
                break;
            case 0xA:
            default:
                data = D_81156598;
                width = 0xA;
                tile_size = 0xA;
                break;
        }

        switch (ptr[4]) {
            case 1:
                pal = D_81122280;
                break;
            case 2:
                pal = D_811222A0;
                break;
            case 3:
                pal = D_811222C0;
                break;
            case 4:
                pal = D_811222E0;
                break;
            case 5:
                pal = D_81122300;
                break;
            case 6:
                pal = D_81122320;
                break;
            case 7:
                pal = D_81122340;
                break;
            case 8:
                pal = D_81122360;
                break;
            case 9:
                pal = D_81122380;
                break;
            case 10:
                pal = D_811223A0;
                break;
            case 11:
                pal = D_811223C0;
                break;
            case 0: // FAKE
            default:
                pal = D_81122260;
                break;
        }

        n = ptr[5];
        while (n != 0) {
            n--;
            src = data + ((ptr[6] * tile_size) * 0x10);
            for (row = 0; row != tile_size; row++) {
                for (col = 0; col != width; col++) {
                    if (trans || (pal[*src & 0xF] != 0)) {
                        *dst = pal[*src & 0xF];
                    }
                    dst++;
                    src++;
                }
                dst = (dst - width) + 0x140;
                src = (src - width) + 0x10;
            }
            ptr++;
            dst -= ((tile_size * 0x140) - width) - dir;
        }

        flags = ptr[6];
        ptr += 6;
    }
}

/**
 * Pixel op: keeps the destination when the source alpha bit is clear, else the source.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbEmu_PixelOpDitherA(s32 arg0, s32 arg1) {
  return (arg1 & 1) ? arg1 : arg0;
}

/**
 * Pixel op: alternate keyed source/destination selection.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbEmu_PixelOpDitherB(s32 arg0, s32 arg1) {
  return (arg1 & 1) ? arg0 : arg1;
}

/**
 * Pixel op: averages source and destination per RGBA5551 channel.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbEmu_PixelOpAverage555(s32 arg0, s32 arg1) {
  return (((s32) ((arg0 & 0xF800) + (arg1 & 0xF800)) >> 1) & 0xF800) | (((s32) ((arg0 & 0x7C0) + (arg1 & 0x7C0)) >> 1) & 0x7C0) | (((s32) ((arg0 & 0x3E) + (arg1 & 0x3E)) >> 1) & 0x3E);
}

/**
 * Pixel op: replaces the destination with the source.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbEmu_PixelOpReplace(UNUSED s32 arg0, s32 arg1) {
  return arg1;
}

/**
 * Copies a width x height RGBA5551 image into a 320-wide destination, combining
 * each pixel with the selected pixel op.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void GbEmu_BlitWithPixelOp(u16* dst, u16* src, s32 mode, s32 width, s32 height) {
  s32 (*operation)(s32, s32);
  s32 x;
  s32 y;
  width = ((width + 3) & 0xFFC);
  switch (mode) {
      case 0:  operation = GbEmu_PixelOpDitherA; break;
      case 1:  operation = GbEmu_PixelOpDitherB; break;
      case 2:  operation = GbEmu_PixelOpAverage555; break;
      default: operation = GbEmu_PixelOpReplace; break;
  }

  for (x = 0; x != height; x++) {
      for (y = 0; y != width; y++) {
          *dst = operation(*dst, *src);
          dst++;
          src++;
      }
      dst = dst - width + 0x140;
  }
}

void func_8004FD20(s32, s32);                /* extern */
M2C_UNK func_8005C0A0();                            /* extern */
extern s32 D_8115658C;

void func_81103D30(void) {
    func_8004FD20(D_8115658C, 0x2800);
    func_8005C0A0();
}

/**
 * Copies an image using its blue channel as intensity to scale the given color.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void GbEmu_BlitTinted(u16* dst, u16* src, s32 color, s32 width, s32 height) {
    s32 x;
    s32 y;
    s32 intensity;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            intensity = (src[y * width + x] & 0x3E) >> 1;
            dst[y * 320 + x] = ((((color & 0xF800) * intensity) / 31) & 0xF800) |
                               ((((color & 0x7C0) * intensity) / 31) & 0x7C0) |
                               ((((color & 0x3E) * intensity) / 31) & 0x3E);
        }
    }
}

/**
 * Additively blends a solid color into the destination using a 4-bit alpha map.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void GbEmu_BlendColorWithAlphaMap(u16* dst, u8* alpha_map, s32 color, s32 width, s32 height, u32 alpha_stride) {
  u16* dst_row;
  u8* alpha_row;
  s32 x;
  s32 y;
  s32 var_t0;
  s32 var_t4;
  s32 var_a0;
  for (y = 0; y < height; y++) {
      for (x = 0; x < width; x++) {
          var_a0 = alpha_map[y * alpha_stride + x] & 0xF;
          var_t0 = (dst[y * 320 + x] & 0xF800) + (((color & 0xF800) * var_a0) / 15 & 0xF800);
          if (var_t0 > 0xF800) var_t0 = 0xF800;
          var_t4 = var_t0;
          var_t0 = (dst[y * 320 + x] & 0x07C0) + (((color & 0x07C0) * var_a0) / 15 & 0x07C0);
          if (var_t0 > 0x07C0) var_t0 = 0x07C0;
          var_t4 |= var_t0;
          var_t0 = (dst[y * 320 + x] & 0x003E) + (((color & 0x003E) * var_a0) / 15 & 0x003E);
          if (var_t0 > 0x003E) var_t0 = 0x003E;
          dst[y * 320 + x] = (s16)(var_t4 | var_t0);
      }
  }
}

extern u16 D_811205F8[];
extern u16 D_811206F8[];
extern u16 D_811207F8[];

/**
 * Draws a horizontal bar into a 16-bit framebuffer from tinted 8x16 tiles: left cap, repeated
 * middle, right cap.
 * @unverified Name and comment from the code.
 */
void GbEmu_DrawTintedBar(u8* arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 8; i < arg2 - 8; i += 8) {
        GbEmu_BlitTinted((u16*)arg0 + i, D_811206F8, arg1, 8, 0x10);
    }
    GbEmu_BlitTinted((u16*)arg0, D_811205F8, arg1, 8, 0x10);
    GbEmu_BlitTinted((u16*)(arg0 + arg2 * 2 - 0x10), D_811207F8, arg1, 8, 0x10);
}

extern u16 D_81120FD8[];
void func_80052100(void*, s32);
/**
 * Draws one 12x11 frame of the animated Transfer Pak access icon; direction selects
 * the mirrored (zero) or normal direction, frame selects the frame (0-10).
 * Seen in play (2026-11-12): draws the animated pak icon on the 「ロードちゅう」 banner below the GB
 * screen while Green loads.
 */
void GbEmu_DrawAccessIcon(u16* arg0, s32 arg1, s32 arg2) {
    u16* src;
    u32 row;
    s32 y;
    s32 x;
    u16 pixel;

    if (arg1 != 0) {
        src = &D_81120FD8[arg2 * 0x84];
        arg1 = 1;
    } else {
        src = &D_81120FD8[arg2 * 0x84 + 0x83];
        arg1 = -1;
    }
    for (y = 0; y < 11; y++) {
        for (x = 0; x < 12; x++) {
            pixel = *src;
            if (pixel & 1) {
                row = y;
                arg0[row * 0x140 + x + 0x2D2] = pixel;
            }
            src += arg1;
        }
    }
    func_80052100(arg0, 0x1E00);
}

extern s32 D_81156550;
extern u8 D_8111E308;
extern u8 D_811221C0[];
extern u8 D_81121B30[];
extern u8 D_811220D0[];
extern u8 D_81122010[];
extern u8 D_81122070[];
extern u8 D_81121DA0[];
void func_81103C40(s32, u8*, s32, s32, s32);

void func_81104618(s32 arg0) {
    s32 sp2C;
    s32 mode;

    sp2C = ((u8*)D_81156550)[0x101B9];
    mode = D_8111E308;

    if (mode == 1) {
        arg0 += 0xA8;
        func_81103C40(arg0 + 0x16BE, D_811221C0, 0, 0x10, 5);
        func_81103C40(arg0 + 0x506, D_81121B30, 0, 0x18, 0xD);
    } else if (mode == 2) {
        arg0 += 0x94;
        func_81103C40(arg0 + 0x16BE, D_811220D0, 0, 0x18, 5);
        func_81103C40(arg0 + 0x55A, (sp2C >= 3) ? D_81122010 : D_81122070, 0, 8, 6);
        func_81103C40(arg0 + 0x506, D_81121DA0, 0, 0x18, 0xD);
    }
    if (D_8111E308 != 0) {
        func_81103C40(arg0 + 0x53A, D_81122010, 0, 8, 6);
        func_81103C40(arg0 + 0x54A, (sp2C >= 2) ? D_81122010 : D_81122070, 0, 8, 6);
    }
}

extern s32 D_81156590;
extern u16 D_811223E0[];
extern s32 D_81154C00;
extern s32 D_81156594;
extern u8* D_81156598;
extern s8 D_811565A2;
extern u8 D_811541F0[];
extern u8 D_81120A18[];
extern u16 D_81120B58[];
void func_811047A0(s32 arg0) {
    s32 pos;
    s32 dst;
    s32 i;
    u8* p;

    pos = D_81156590;
    func_8004FD20(pos, 0x2800);
    pos += 0xAE;
    GbEmu_DrawTintedBar((u8*)pos, D_811223E0[D_81156594], 0x70);
    i = 0;
    dst = pos + 0x788;
    if (arg0 != 0) {
        arg0 = 6;
    }
    p = &D_811541F0[arg0];
    do {
        GbEmu_BlendColorWithAlphaMap((u16*)dst, D_81156598 + *p * 0xA0, 0xFFFE, 0xC, 0xA, 0x10);
        i += 0x12;
        dst += 0x12;
        p++;
    } while (i != 0x6C);
    func_81103C40(pos + 0x7FE, D_81120A18, 0, 0x10, 0xA);
    func_81103C40(pos + 0x5C2, (u8*)&D_81120B58[D_81156594 * 12 * 12], 0, 0xC, 0xC);
    GbEmu_DrawAccessIcon((u16*)pos, arg0, 0);
    D_811565A2 = 0;
    D_81154C00 = D_81156590;
}

typedef struct Screen81104930 {
    /* 0x00 */ u8 unk_00[6];
    /* 0x06 */ s8 unk_06;
    /* 0x07 */ s8 unk_07;
    /* 0x08 */ u8 unk_08[4];
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 unk_0E[2];
    /* 0x10 */ u8* unk_10;
    /* 0x14 */ u8 unk_14[8];
    /* 0x1C */ u8* unk_1C;
    /* 0x20 */ u8* unk_20;
    /* 0x24 */ u8 unk_24[0x14];
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ u32 unk_3C;
    /* 0x40 */ u32 unk_40;
    /* 0x44 */ u8* unk_44;
    /* 0x48 */ u8* unk_48;
    /* 0x4C */ s32 framebuffer;
    /* 0x50 */ u8* unk_50;
    /* 0x54 */ s32 colorIndex;
} Screen81104930;

extern Screen81104930 D_81156540;
extern u16 D_811223E0[];
extern u8 D_811208F8[];
extern u8 D_811541FC[5];
extern u8* D_8115659C;
extern s32 D_81154C00;

void func_81104930(void) {

    s32 pos;
    s32 dst;
    u8* p;

    func_81103D30();
    switch (D_8111E308) {
        case 1:

            pos = D_81156540.framebuffer + 0xA4;
            GbEmu_DrawTintedBar((u8*)pos, D_811223E0[D_81156540.colorIndex], 0x7C);
            func_81104618(D_81156540.framebuffer);
            pos += 0x2DE;
            break;
        case 2:

            pos = D_81156540.framebuffer + 0x94;
            GbEmu_DrawTintedBar((u8*)pos, D_811223E0[D_81156540.colorIndex], 0x84);
            func_81104618(D_81156540.framebuffer);
            pos += 0x2EE;
            break;
        case 0:
        default:

            pos = D_81156540.framebuffer + 0xCE;
            GbEmu_DrawTintedBar((u8*)pos, D_811223E0[D_81156540.colorIndex], 0x50);
            pos += 0x288;
            break;
    }
    func_81103C40(pos + 0x280, D_811208F8, 0, 0xC, 0xC);
    dst = pos + 0x29C;
    /* The comma expression is what gives the ROM's register allocation. */
    for (p = D_811541FC; (0, p) != &D_811541FC[5]; p++) { // FAKE: comma expression
        GbEmu_BlendColorWithAlphaMap((u16*)dst, D_8115659C + *p * 0xC0, 0xFFFE, 0xC, 0xC, 0x10);
        dst += 0x18;
    }
    D_81154C00 = D_81156540.framebuffer;
}

void func_8004FD20(s32, s32);                /* extern */
extern s32 D_81156550;

void func_81104AE4(void) {
    func_8004FD20(D_81156550 + 0x12D00, 0x20);
}

extern u32 D_811565AC;
extern u32 D_811565B0;
/**
 * Bump allocator: aligns the heap pointer to 64 bytes, reserves the size and hangs when the heap
 * runs out.
 * @unverified Name and comment from the code.
 */
s32 GbEmu_AllocAligned64(s32 arg0, M2C_UNK arg1)
{
  s32 new_var; // FAKE: permuter temp
  s32 temp_v1;
  u32 temp_t6;
  temp_v1 = (D_811565AC + 0x3F) & (~0x3F);
  new_var = temp_v1;
  ;
  if ((D_811565AC = new_var + arg0) >= ((u32) D_811565B0))
  {
    loop_1:
    goto loop_1;

  }
  return new_var; // FAKE: permuter temp
}

s32 GbPak_RequestBankLoad(s32, s32);                     /* extern */
extern u8 D_811565A0;

void func_81104B60(s32 arg0) {
    GbPak_RequestBankLoad(D_811565A0, arg0);
}

/**
 * Blocks on an OS timer for the given number of milliseconds.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void GbEmu_Delay(OSTime arg0) {
  OSMesgQueue sp68;
  void* sp64;
  OSTimer sp40;

  osCreateMesgQueue(&sp68, &sp64, 1);
  osSetTimer(&sp40, (1000 * arg0) * 64 / 3, 0, &sp68, NULL);
  osRecvMesg(&sp68, NULL, 1);
}

void func_80058410(void*, void*, s32);
extern u8 D_81122854[];

/**
 * Compares the cartridge header title and version bytes with the four known cartridges in
 * D_81122854 and returns 4..1 for a match, 0 for none.
 * Seen in play (2026-11-12): the table D_81122854 holds YELLOW, BLUE, GREEN and RED with
 * destination 0 (Japan) and licensee 01, so it returns 4 Yellow, 3 Blue, 2 Green, 1 Red; Pocket
 * Monsters Green got 2 and went on to load. The version byte is not compared.
 */
s32 GbPak_IdentifyCartridge(u8* arg0) {
    u8 buf[8];
    u8* entry = D_81122854;
    s32 i;

    func_80058410(arg0 + 0x44, buf, 8);
    for (i = 4; i != 0; i--, entry += 0x18) {
        buf[3] = entry[0x13];
        if ((func_80057910(arg0 + 0x34, entry, 0x10) == 0) && (func_80057910(buf, entry + 0x10, 8) == 0)) {
            break;
        }
    }
    return i;
}

/**
 * For a cartridge with RAM bank 1 loaded, checks the Gen 1 main save: the player name at 0x598
 * must end in 0x50 within 6 bytes (else 11), and the byte after 0x598-0x1593 must be the inverted
 * sum (else 10). Returns 0 when the save is valid.
 * @unverified Name and comment from the code; no Transfer Pak was emulated.
 */
s32 GbPak_CheckGen1SaveChecksum(s8* arg0) {
    s32 i;
    s32 sum;

    if ((M2C_FIELD(arg0, u32*, 0x8C) >> 13) == 1) {
        for (i = 0x598; i < 0x59E; i++) {
            if (M2C_FIELD(arg0, u8**, 0x54)[i] == 0x50) {
                goto found;
            }
        }
        return 11;
    found:
        sum = 0;
        for (i = 0x598; i < 0x1594; i++) {
            sum += M2C_FIELD(arg0, u8**, 0x54)[i];
        }
        sum = (sum & 0xFF) ^ 0xFF;
        if (sum != M2C_FIELD(arg0, u8**, 0x54)[i]) {
            return 10;
        }
    }
    return 0;
}

extern s32 D_81154C48;

/**
 * Blacks out the screen, resets the VI X scale, stores the error code in D_81154C48 and returns
 * -1.
 * Seen in play (2026-11-12): error 1 after a failed bank checksum blacked out the screen and led
 * to the 「64GBパックが ただしくセットされていません」 screen.
 */
s32 GbEmu_BlackScreenAndFail(s32 arg0) {
    osViBlack(1);
    GbEmu_Delay(20);
    osViSetXScale(1.0f);
    D_81154C48 = arg0;
    return -1;
}

void func_8110724C(void);
void func_800093E0(void*, void*);
s32 func_80025BD8(void);
void func_80052DC0(s32);
void func_8005C280(f32);
void func_81100020(void);
void GbPak_QueueNextBankLoad(GbpakChannel811023DC*);
void func_81106CC8(u16*, u8 (*)[0xC80], s32, s32);
void func_81117B20(Screen81104930*);
extern u8 D_8111E570[];
extern u8 D_811565A1;
extern s16 D_800AA148;
extern u8 D_811565A3;
extern u8 D_811565A4;
extern u8 D_811565A5;
extern u8* D_811565A8;
extern s32 D_811565B4;
extern u8 D_8112AF3C[];
extern u8 D_81130024[];
extern u8 D_811645F0[];
extern u8 D_811725F0[];
extern u8 D_811223F4[];
extern u8 D_811224D4[];
extern u8 D_811225B4[];
extern u8 D_81122694[];
extern u8 D_81122774[];
extern f32 D_FLT_81154254;

/**
 * Starts a Game Boy session on Transfer Pak channel arg3: allocates the GB memory, ROM and RAM
 * buffers and identifies the cartridge on every port (GbPak_IdentifyCartridge). A cartridge
 * without a bank list (Yellow, or a revision the tables don't cover) has its four SRAM banks and
 * whole ROM copied before play; Red, Green and Blue instead stream their banks in the background
 * while the game runs. For a streamed load it keeps ROM bytes 0x000-0x101 in D_811565A8 and
 * replaces them with the boot stub D_8111E570, which ends in `jr $` at 0x100. GbEmu_UpdateFrame
 * puts the real bytes back once the GB PC reaches 0x100 while banks are still loading. Seen in
 * play: with Green this showed the 「ロードちゅう」 banner and the Nintendo logo, then the game's own
 * copyright screen.
 */
s32 GbEmu_LoadCartridge(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4) {
    GbpakChannel811023DC* cur;
    GbpakChannel811023DC* slot;
    u8* buf;
    s32 i;
    u32 j;
    u8* p;
    s32 pad[2]; // FAKE

    D_811565B4 = 0;
    D_811565AC = arg1;
    D_811565B0 = arg1 + arg2;
    D_811565A0 = arg3;
    D_81156598 = M2C_FIELD(arg4, u8**, 0x21CC);
    D_8115659C = M2C_FIELD(arg4, u8**, 0x21D0);
    D_81156540.unk_10 = (u8*)GbEmu_AllocAligned64(0x27F80, 0);
    D_81156540.unk_1C = (u8*)GbEmu_AllocAligned64(0x100000, 0);
    D_81156540.unk_40 = 0x8000;
    D_81156540.unk_20 = (u8*)GbEmu_AllocAligned64(D_81156540.unk_40, 0);
    D_81156540.unk_44 = (u8*)GbEmu_AllocAligned64(0xF000, 0);
    D_81156540.unk_48 = (u8*)GbEmu_AllocAligned64(0xF000, 0);
    D_81154C00 = D_81156540.framebuffer = GbEmu_AllocAligned64(0x2800, 0);
    D_81156540.unk_50 = (u8*)GbEmu_AllocAligned64(0x2800, 0);
    D_811565A8 = (u8*)GbEmu_AllocAligned64(0x102, 0);
    D_811565A3 = 0;
    D_81156477 = 1;
    D_811565A1 = 0;
    D_811565A5 = 0x20;
    D_811565A4 = 0;
    func_8004FD20((s32)D_81156540.unk_10, 0xFF80);
    for (i = 0, p = D_81156540.unk_10 + 0x16B20; i < 0x40; i++) {
        *p++ = 1;
    }
    for (i = 0, p = D_81156540.unk_10 + 0x16B60; i < 0x20; i++) {
        *p++ = 1;
    }
    func_81103D30();
    i = func_80025BD8();
    D_811561C8[i].request = 0x80;
    func_8004CFB0(&D_81156458, i, 1);
    while (D_81156475 != 0) {
    }

    buf = (u8*)GbEmu_AllocAligned64(0x200, 0);
    for (i = 0; i < 4; i++) {
        slot = &D_811561C8[i];
        slot->bankState = D_81156540.unk_10 + 0x16B20;
        slot->sramState = D_81156540.unk_10 + 0x16B60;
        slot->ramBuf = D_81156540.unk_20;
        slot->blockState = D_81156540.unk_10 + 0x16B80;
        slot->verifyBuf = buf;
        slot->blockDirty = buf + 0x100;
        slot->ramSize = D_81156540.unk_40;
        for (j = 0; j < (D_81156540.unk_40 >> 8); j++) {
            slot->blockDirty[j] = 0xFF;
            slot->blockState[j] = 0xFF;
        }
        slot->unkA0 = GbPak_IdentifyCartridge((u8*)slot);
        slot->romBuf = D_81156540.unk_1C;
        slot->sramBuf = D_81156540.unk_20;
    }
    cur = &D_811561C8[D_811565A0];
    if (cur->error != 0) {
        GbEmu_BlackScreenAndFail(1);
        return (cur->unkA2 != 0) ? 2 : 1;
    }
    if (cur->unkA0 == 0) {
        return GbEmu_BlackScreenAndFail(1);
    }
    D_81156540.colorIndex = cur->unkA0 - 1;
    while (D_81156475 != 0) {
    }
    if (GbPak_WriteVerifiedSramBlock(D_811565A0, 0, 0xFF) != 0) {
        GbEmu_BlackScreenAndFail(1);
        return (cur->unkA2 != 0) ? 2 : 1;
    }
    D_81156540.unk_38 = 0xE;
    if (cur->cartType == 4) {
        D_81156540.unk_3C = 0x80000;
    } else {
        D_81156540.unk_3C = 0x100000;
    }
    D_81156540.unk_07 = 0;
    D_81156540.unk_06 = 1;
    func_81117B20(&D_81156540);
    func_81103D30();

    /* FAKE: the unsigned `1U` compares stop the constant 1 from sharing a register with unk_06 = 1. */
    cur->bankList = (cur->unkA0 == 4)   ? NULL
                    : (cur->unkA0 == 3) ? ((cur->unk4C == 0) ? D_81122774 : NULL)
                    : (cur->unkA0 == 2) ? ((cur->unk4C == 1U) ? D_81122694 : (cur->unk4C == 0) ? D_811225B4 : NULL)
                                        : ((cur->unk4C == 1U) ? D_811224D4 : (cur->unk4C == 0) ? D_811223F4 : NULL);
    cur->sum = 0;

    if (cur->bankList == NULL) {
        func_81106CC8((u16*)arg0, M2C_FIELD(arg4, u8 (**)[0xC80], 0x2204), func_80025BD8(), D_81156540.colorIndex);
        func_81104930();
        func_8005C0A0();
        func_80052DC0(0);
        for (i = 0; i < 4; i++) {
            cur->request = 2;
            cur->addr = i * 0x2000;
            cur->buf = i * 0x2000 + D_81156540.unk_20;
            cur->size = 0x2000;
            func_8004CFB0(&D_81156458, D_811565A0, 1);
            while (D_81156475 != 0) {
                func_8110724C();
            }
            if (cur->error) goto fail; /* one line: gives the ROM's beqz/b pair */
            if (D_800AA148 != 0) {
                GbEmu_BlackScreenAndFail(0);
            }
        }
        for (i = 0; i < (D_81156540.unk_3C >> 13); i++) {
            cur->request = 1;
            if (1) {} // karodo
            if (1) {} // karodo
            if (1) {} // karodo
            cur->addr = i * 0x2000;
            cur->buf = i * 0x2000 + D_81156540.unk_1C;
            cur->size = 0x2000;
            func_8004CFB0(&D_81156458, D_811565A0, 1);
            while (D_81156475 != 0) {
                func_8110724C();
            }
            if (cur->error) goto fail; /* one line: gives the ROM's beqz/b pair */
            if (D_800AA148 != 0) {
                GbEmu_BlackScreenAndFail(0);
            }
        }
        for (i = 0; i < (D_81156540.unk_3C >> 14); i++) {
            cur->bankState[i] = 0;
        }
        for (i = 0; i < (D_81156540.unk_40 >> 13); i++) {
            cur->sramState[i] = 0;
        }
        func_800093E0(D_8112AF3C, D_811645F0);
        func_800093E0(D_81130024, D_811725F0);
    } else {
        func_811047A0(0);
        func_8005C0A0();
        D_81156476 = 1;
        GbPak_RequestBankLoad(D_811565A0, 0);
        while (*cur->bankState != 0) {
            GbPak_QueueNextBankLoad(cur);
            if (cur->error != 0) {
            fail:
                GbEmu_BlackScreenAndFail(1);
                return (cur->unkA2 != 0) ? 2 : 1;
            }
            if (D_800AA148 != 0) {
                GbEmu_BlackScreenAndFail(0);
            }
        }
        D_811565A4 = 1;
        for (i = 0; i < 0x102; i++) {
            D_811565A8[i] = D_81156540.unk_1C[i];
            D_81156540.unk_1C[i] = D_8111E570[i];
        }
        D_81156540.unk_0C = 0;
        D_81156540.unk_10[0xFF42] = 0x64;
    }
    D_81156540.unk_06 = 0;
    func_81100020();
    func_8005C280(D_FLT_81154254);
    func_80052DC0(0);
    return 0;
}
