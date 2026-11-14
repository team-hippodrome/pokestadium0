/* Stadium Zero fragment000_80C00. */

#include "global.h"
#include "audio_and_gb_emulator.h"

/**
 * Puts the emulated Game Boy CPU in its post-boot-ROM state: registers (SP 0xFFFE, PC 0x0100), the
 * sound registers NR52 0x8F, NR50 0x77 and NR51 0xFF through GbApu_QueueRegisterWrite, and zeroes a
 * block of emulator memory.
 * Seen in play (2026-11-14) ran once when the GB Tower started with JP Green, from
 * GbEmu_LoadCartridge, before Green's boot logo.
 */
#ifdef NON_MATCHING
/* TODO: decompile GbCpu_Reset; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81117B20.s")
#endif

/**
 * The Game Boy CPU interpreter: runs the emulated LR35902 until it has to return to
 * GbEmu_UpdateFrame. Bank switches call GbPak_RequestBankLoadCurrentPort from inside it.
 * Seen in play (2026-11-14) ran from GbEmu_UpdateFrame while Green booted and played its intro.
 */
#ifdef NON_MATCHING
/* TODO: decompile GbCpu_Run; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81118018.s")
#endif
