/* Stadium Zero fragment021_2B13F0: an unused relay to the main menu launcher (fragment 020). */

#include "global.h"
#include "unused_relay_021.h"

extern u8 D_8E000000[];
extern u8 D_002B1360[];
extern u8 D_002B13F0[];

/**
 * Entry point of fragment 021. Queues fragment 020 (the main menu launcher, VRAM 0x8E000000,
 * ROM D_002B1360..D_002B13F0) with entry arguments 0, 0, and returns 0x8040 so the fragment
 * loop in State_MainMenu runs the queued call. Fragment 020 in turn queues the main menu.
 * All arguments are ignored. The loader passes only two (FragmentEntry), but the retail code
 * spills a third argument register, so the definition takes three (fragment 022 too; 023 and
 * 024 take two).
 *
 * Fragments 022-024 are byte-for-byte the same relay at 0x8E200000, 0x8E300000 and 0x8E400000.
 * Nothing in the retail ROM loads this fragment: a ROM-wide scan (2026-11-14) finds no
 * lui/addiu pair or data word for its ROM start 0x2B13F0, its ROM end 0x2B1480 or its VRAM
 * 0x8E100000, so it looks like a leftover slot.
 * @unverified Not reachable in play; name and comment come from the code and the ROM scan.
 */
s32 UnusedRelay021_QueueMainMenuLauncher(s32 unused_arg0, s32 unused_arg1, s32 unused_arg2) {
    Fragment_QueueCall(((((u32)D_8E000000) & 0x0FF00000) >> 0x14) - 0x10, D_002B1360, D_002B13F0, 0, 0);
    return 0x8040;
}
