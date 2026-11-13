/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gb_tower.c. */

#include "gb_tower.h"
#include "hal_libc.h"
#include "controller.h"
#include "game_state.h"
#include "gb_mbc.h"
extern OSPfs D_800AB050[4];
extern u8 D_800AB1F0[4];
extern u8 D_800AB1F4;
extern u8 D_800AB1F5;
extern u8 D_800AB1F7;
extern s32 D_800AB1F8;
s32 GbPak_MbcRead(s32 arg0, void* arg1, u16 arg2, u16 arg3);
s32 GbPak_MbcWrite(s32 arg0, void* arg1, u16 arg2, u16 arg3);

s32 GbPak_DetectRam(s32 arg0, u8* arg1);
s32 GbTower_ProbePak(s32 arg0, u8* arg1, u8* arg2);
s32 GbTower_IsPakInserted(s32 arg0, u8 arg1);
void GbTower_PowerOffAllPaks(void);
s32 GbPak_IsCartOff(s32 arg0);
s32 GbPak_IsCartOn(s32 arg0);
s32 GbTower_ReinitPak(s32 arg0);
s32 GbPak_MbcRead(s32 arg0, void* arg1, u16 arg2, u16 arg3);
s32 GbPak_MbcWrite(s32 arg0, void* arg1, u16 arg2, u16 arg3);
s32 GbPak_RawRead(s32 arg0, u8* arg1, u16 arg2, u16 arg3);
s32 GbPak_RawWrite(s32 arg0, u8* arg1, u16 arg2, u16 arg3);
int GbPak_SelectRomBank(s32 arg0, s32 arg1);
s32 GbPak_ReadRom(s32 arg0, u8* arg1, s32 arg2, s32 arg3);
u8 GbTower_SetPollMask(u8 arg0);
void GbTower_PollPakConnection(void);
void func_8000B340_jp(void);

s32 GbPak_VerifyPattern(s32 arg0, void* arg1);

/**
 * Writes a 32-byte pattern to cartridge RAM 0xA000 through the MBC, reads it back
 * and returns 1 if it matches and the pak status bit 2 is clear.
 * Seen in play (2026-11-12) at power-on with a Transfer Pak holding Pocket Monsters Green in port
 * 1: wrote a pattern through GbPak_MbcWrite, read it back through GbPak_MbcRead and returned 1,
 * both times it ran.
 */
s32 GbPak_VerifyPattern(s32 arg0, void* arg1) {
    u8 sp47;
    u8 sp24[0x20];
    s32 sp20 = 0;
    UNUSED u8 padding[8];

    if ((GbPak_MbcWrite(arg0, arg1, 0, 0x20) == 0) && (GbPak_MbcRead(arg0, (uintptr_t)&sp24, 0, 0x20) == 0) &&
        (bcmp(&sp24, arg1, 0x20) == 0) && (osGbpakGetStatus(&D_800AB050[arg0], &sp47) == 0)) {
        sp20 = ((sp47 & 4) != 0) == 0;
    }
    return sp20;
}

/**
 * Detects working cartridge RAM by verifying 0x55, 0xAA and then an osGetCount
 * pattern; the last pattern is left in the pattern buffer for GbTower_VerifyPakStillInserted.
 * Seen in play (2026-11-12) at power-on with a Transfer Pak holding Pocket Monsters Green in port
 * 1: ran GbPak_VerifyPattern twice (both returned 1), then returned 1.
 */
s32 GbPak_DetectRam(s32 arg0, u8* arg1) {
    s32 var_s0 = 0;
    u8 sp34[0x20];

    if (arg1 == NULL) {
        arg1 = sp34;
    }
    HAL_Memset((char*)arg1, 0x55, 0x20);
    if (GbPak_VerifyPattern(arg0, arg1) != 0) {
        HAL_Memset((char*)arg1, 0xAA, 0x20);
        if (GbPak_VerifyPattern(arg0, arg1) != 0) {
            s32 i;
            for (i = 0; i < ARRAY_COUNT(sp34); i++) {
                arg1[i] = osGetCount();
            }
            var_s0 = GbPak_VerifyPattern(arg0, arg1);
        }
    }
    return var_s0;
}

/**
 * Prepares the pak on a port once (gGbPakPortReady): reads the ID, enables
 * cartridge RAM and runs GbPak_DetectRam. Shuts down with error 1 if the read fails.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbTower_ProbePak(s32 arg0, u8* arg1, u8* arg2) {
    u8 status;
    OSGbpakId gbpak_id;
    s32 sp28 = 0;

    if (arg1 != NULL) {
        *arg1 = D_800AB1F0[arg0];
    }

    if (D_800AB1F0[arg0] == 1) {
        return 1;
    }

    if (osGbpakReadId(&D_800AB050[arg0], &gbpak_id, &status) != 0) {
        Game_ShutdownAndLoadFragment(arg0, 1);
    }
    if ((status & OS_GBPAK_RSTB_STATUS) && (osGbpakCheckConnector(&D_800AB050[arg0], &status) == 0)) {
        osGbmbcRamEnable(&D_800AB050[arg0]);
        sp28 = GbPak_DetectRam(arg0, arg2);
    }
    D_800AB1F0[arg0] = 1;
    return sp28;
}

/**
 * Returns 1 if the pak has not latched a reset (OS_GBPAK_RSTB_DETECTION clear), i.e. the
 * cartridge was not removed; powers the pak off when keep_powered == 0.
 * Seen in play (2026-11-12) at power-on with a Transfer Pak holding Pocket Monsters Green in port
 * 1: returned 1 for port 1, twice during the boot scan.
 */
s32 GbTower_IsPakInserted(s32 arg0, u8 arg1) {
    u8 status;
    s32 temp_v1;

    if (osGbpakGetStatus(&D_800AB050[arg0], &status) != 0) {
        Game_ShutdownAndLoadFragment(arg0, 1);
    }

    temp_v1 = !((status & OS_GBPAK_RSTB_DETECTION) != 0);
    if (arg1 == 0) {
        osGbpakPower(&D_800AB050[arg0], 0);
        D_800AB1F0[arg0] = 0;
    }
    return temp_v1;
}

/**
 * Powers off every pak that was initialized by GbTower_ScanPaks.
 * Seen in play (2026-11-13) with a JP Green cart in the Transfer Pak, it ran once, right as the GB
 * session ended on the "report is not correct" panel, and not while the game played.
 */
void GbTower_PowerOffAllPaks(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_800AB1F4 & (1 << i)) {
            osGbpakPower(&D_800AB050[i], 0);
            D_800AB1F0[i] = 0;
        }
    }
}

extern u8 D_800A82A6;
extern u8 D_800AB1F6;

/**
 * Initializes every plugged-in Transfer Pak and checks its cartridge. Returns
 * (gGbPakUsableMask << 16) | gGbPakInitMask.
 * Seen in play (2026-11-12) at power-on with a Transfer Pak holding Pocket Monsters Green in port
 * 1: returned 0x10001, port 1 both usable and inserted.
 */
s32 GbTower_ScanPaks(void) {
    s32 i;
    s32 temp_v0;
    u8 status;
    OSGbpakId sp4C;

    D_800AB1F5 = 0;
    D_800AB1F4 = 0;
    D_800AB1F7 = 0;
    D_800AB1F8 = 0;
    osPfsIsPlug(&gSIEventMesgQueue, &D_800AB1F6);

    for (i = 0; i < 4; i++) {
        if (D_800AB1F6 & (1 << i)) {
            if (osGbpakInit(&gSIEventMesgQueue, &D_800AB050[i], i) == 0) {
                D_800AB1F4 |= (1 << i);
                temp_v0 = osGbpakReadId(&D_800AB050[i], &sp4C, &status);
                if (temp_v0 == 0) {
                    if (!(status & 8)) {
                        Game_ShutdownAndLoadFragment(i, 2);
                    }
                    if (osGbpakCheckConnector(&D_800AB050[i], &status) == 0) {
                        osGbmbcRamEnable(&D_800AB050[i]);
                        D_800AB1F5 |= (1 << i);
                        D_800AB1F0[i] = 1;
                    } else {
                        Game_ShutdownAndLoadFragment(i, 2);
                    }
                } else {
                    D_800AB1F0[i] = 0;
                    if (temp_v0 == 4) {
                        Game_ShutdownAndLoadFragment(i, 2);
                    }
                }
            }
        }
    }
    return (D_800AB1F5 << 0x10) | D_800AB1F4;
}

/**
 * Returns 1 if the Transfer Pak reports no powered cartridge; shuts down on a pak error.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbPak_IsCartOff(s32 arg0) {
    u8 status;
    s32 ret = osGbpakGetStatus(&D_800AB050[arg0], &status);
    UNUSED u8 filler;

    // check the error code returned (if applicable) by the osGbpakGetStatus
    // call.
    if ((ret == PFS_ERR_NOPACK) || (ret == PFS_ERR_DEVICE) || (ret == PFS_ERR_CONTRFAIL)) {
        Game_ShutdownAndLoadFragment(arg0, 1);
    }
    return !((status & OS_GBPAK_GBCART_ON) != 0);
}

/**
 * Returns 1 if the Transfer Pak reports a powered cartridge; shuts down on a pak error.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbPak_IsCartOn(s32 arg0) {
    u8 status;
    s32 ret = osGbpakGetStatus(&D_800AB050[arg0], &status);

    if ((ret == PFS_ERR_NOPACK) || (ret == PFS_ERR_DEVICE) || (ret == PFS_ERR_CONTRFAIL)) {
        Game_ShutdownAndLoadFragment(arg0, 1);
    }
    return ((status & OS_GBPAK_GBCART_ON) != 0);
}

/**
 * Re-initializes the pak on a port and enables cartridge RAM; returns 1 on success.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbTower_ReinitPak(s32 arg0) {
    UNUSED u8 filler[4];
    u8 status;
    OSGbpakId sp28;

    D_800AB1F0[arg0] = 0;
    if ((osGbpakInit(&gSIEventMesgQueue, &D_800AB050[arg0], arg0) == 0) &&
        (osGbpakReadId(&D_800AB050[arg0], &sp28, &status) == 0) && (status & OS_GBPAK_RSTB_STATUS) &&
        (osGbpakCheckConnector(&D_800AB050[arg0], &status) == 0)) {

        osGbmbcRamEnable(&D_800AB050[arg0]);
        D_800AB1F0[arg0] = 1;
    }

    return D_800AB1F0[arg0] == 1;
}

/**
 * Returns 1 if the 32-byte pattern left by GbPak_DetectRam is still in
 * cartridge RAM and the pak was not reset, i.e. the same cartridge is still inserted.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbTower_VerifyPakStillInserted(s32 arg0, void* arg1) {
    u8 status;
    u8 sp1C[0x20];
    s32 sp18;

    sp18 = 0;
    if ((GbPak_MbcRead(arg0, (uintptr_t)&sp1C, 0, 0x20) == 0) && (bcmp(&sp1C, arg1, 0x20) == 0) &&
        (osGbpakGetStatus(&D_800AB050[arg0], &status) == 0) && !(status & OS_GBPAK_RSTB_DETECTION)) {
        sp18 = 1;
    }
    return sp18;
}

/**
 * Reads cartridge memory through osGbmbcReadWrite if the port is usable.
 * Seen in play (2026-11-12) at power-on with a Transfer Pak holding Pocket Monsters Green in port
 * 1: GbPak_VerifyPattern read its pattern back through it (returned 0, success).
 */
s32 GbPak_MbcRead(s32 arg0, void* arg1, u16 arg2, u16 arg3) {
    s32 var_v1;

    var_v1 = 1;
    if (D_800AB1F5 & (1 << arg0)) {
        var_v1 = osGbmbcReadWrite(&D_800AB050[arg0], 0, arg2, arg1, arg3);
    }
    return var_v1;
}

/**
 * Writes cartridge memory through osGbmbcReadWrite if the port is usable.
 * Seen in play (2026-11-12) at power-on with a Transfer Pak holding Pocket Monsters Green in port
 * 1: GbPak_VerifyPattern wrote its pattern through it (returned 0, success).
 */
s32 GbPak_MbcWrite(s32 arg0, void* arg1, u16 arg2, u16 arg3) {
    s32 var_v1;

    var_v1 = 1;
    if (D_800AB1F5 & (1 << arg0)) {
        var_v1 = osGbmbcReadWrite(&D_800AB050[arg0], 1, arg2, (uintptr_t)arg1, arg3);
    }
    return var_v1;
}

/**
 * Reads raw Transfer Pak address space through osGbpakReadWrite if the port is usable.
 * Seen in play (2026-11-12) at power-on with a Transfer Pak holding Pocket Monsters Green in port
 * 1: GbPak_ReadRom read the header through it (returned 0, success).
 */
s32 GbPak_RawRead(s32 arg0, u8* arg1, u16 arg2, u16 arg3) {
    s32 var_v1;

    var_v1 = 1;
    if (D_800AB1F5 & (1 << arg0)) {
        var_v1 = osGbpakReadWrite(&D_800AB050[arg0], 0, arg2, arg1, arg3);
    }
    return var_v1;
}

/**
 * Writes raw Transfer Pak address space through osGbpakReadWrite if the port is usable.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbPak_RawWrite(s32 arg0, u8* arg1, u16 arg2, u16 arg3) {
    s32 var_v1;

    var_v1 = 1;
    if (D_800AB1F5 & (1 << arg0)) {
        var_v1 = osGbpakReadWrite(&D_800AB050[arg0], 1, arg2, arg1, arg3);
    }
    return var_v1;
}

/**
 * Selects a ROM bank by writing 0x5000, the upper bank bits to 0x4000 and the
 * lower 5 bits to 0x2000.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
int GbPak_SelectRomBank(s32 arg0, s32 arg1) {
    u8 sp28[0x20];
    int i;
    int ret;

    for (i = 0; i < 0x20; i++) {
        sp28[i] = 0;
    }
    ret = GbPak_RawWrite(arg0, sp28, 0x5000U, 0x20U);
    if (ret) {
        return ret;
    }
    for (i = 0; i < 0x20; i++) {
        sp28[i] = (arg1 / 32);
    }
    ret = GbPak_RawWrite(arg0, sp28, 0x4000U, 0x20U);
    if (ret) {
        return ret;
    }
    for (i = 0; i < 0x20; i++) {
        sp28[i] = (arg1 % 32);
    }
    return GbPak_RawWrite(arg0, sp28, 0x2000U, 0x20U);
}

/**
 * Reads a linear range of cartridge ROM, aligned to 32 bytes, switching banks
 * for addresses at or above 0x4000.
 * Seen in play (2026-11-12) at power-on with a Transfer Pak holding Pocket Monsters Green in port
 * 1: read the cartridge header range from 0x120 into 0x80082A00. The bytes matched the ROM,
 * including the title POKEMON GREEN at 0x134.
 */
s32 GbPak_ReadRom(s32 arg0, u8* arg1, s32 arg2, s32 arg3) {
    s32 ret = 1;
    u32 temp_s1 = (arg2 & ~0x1F);
    u32 temp_s4 = ((arg2 + arg3) + 0x1F) & ~0x1F;

    s32 temp_s1_2;
    s32 temp_v0_4;
    u32 temp_v0_5;
    u32 var_v1_2;

    if (temp_s1 < 0x4000U) {
        if (temp_s4 < 0x4001U) {
            var_v1_2 = temp_s4;
        } else {
            var_v1_2 = 0x4000;
        }
        temp_v0_4 = var_v1_2 - temp_s1;
        ret = GbPak_RawRead(arg0, arg1, temp_s1, temp_v0_4);
        if (ret != 0) {
            return ret;
        }
        temp_s1 += temp_v0_4;
        arg1 = &arg1[temp_v0_4];
    }
    while (temp_s1 < temp_s4) {
        temp_v0_5 = (temp_s1 & ~0x3FFF) + 0x4000;
        if (temp_v0_5 >= temp_s4) {
            var_v1_2 = temp_s4;
        } else {
            var_v1_2 = temp_v0_5;
        }
        temp_s1_2 = var_v1_2 - temp_s1;
        ret = GbPak_SelectRomBank(arg0, temp_s1 >> 0xE);
        if (ret != 0) {
            return ret;
        }
        ret = GbPak_RawRead(arg0, arg1, ((temp_s1 & 0x3FFF) + 0x4000) & 0xFFFF, temp_s1_2);
        if (ret != 0) {
            return ret;
        }
        temp_s1 += temp_s1_2;
        arg1 = &arg1[temp_s1_2];
    }
    return ret;
}

/**
 * Sets the ports polled by GbTower_PollPakConnection; returns the old mask.
 * Seen in play (2026-11-12) at power-on with a Transfer Pak holding Pocket Monsters Green in port
 * 1: was set to 1 (port 1) at the end of the scan and returned the old mask 0.
 */
u8 GbTower_SetPollMask(u8 arg0) {
    u8 temp_v0 = D_800AB1F7;

    D_800AB1F7 = arg0;
    return temp_v0;
}

// Polls one Game Boy pak per call, rotating through ports 0-3. The first
// osGbpakGetStatus failure on a port enabled by GbTower_SetPollMask latches
// D_800AB1F8 and calls Game_ShutdownAndLoadFragment(port, 1); the per-port
// failure counter D_800A82AC is not used.
/** Polls the Transfer Pak connection state. */
void GbTower_PollPakConnection(void) {
    u8 sp1F;
    static s32 D_800697D0 = 0; // .data

    if (D_800AB1F8 == 0) {
        if (D_800AB1F7 & (1 << D_800697D0)) {
            if (osGbpakGetStatus(&D_800AB050[D_800697D0], &sp1F) != 0) {
                D_800AB1F8 = 1;
                Game_ShutdownAndLoadFragment(D_800697D0, 1);
            }
        }
        D_800697D0 = (D_800697D0 + 1) & 3;
    }
}

// Checks every pak enabled by GbTower_SetPollMask in one call, using the same
// failure handling as GbTower_PollPakConnection.
void func_8000B340_jp(void) {
    s32 i;
    u8 status;

    for (i = 0; i < 4; i++) {
        if (D_800AB1F7 & (1 << i)) {
            if (osGbpakGetStatus(&D_800AB050[i], &status) != 0) {
                D_800AB1F8 = 1;
                Game_ShutdownAndLoadFragment(i, 1);
            }
        }
    }
}
