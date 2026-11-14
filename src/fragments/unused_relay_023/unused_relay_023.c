/* Stadium Zero fragment023_2B1510: an unused relay to the main menu launcher (fragment 020). */

#include "global.h"
#include "unused_relay_023.h"
#include "game_state.h"

extern u8 D_8E000000[];
extern u8 D_002B1360[];
extern u8 D_002B13F0[];

/**
 * Entry point of fragment 023. Queues fragment 020 (the main menu launcher, VRAM 0x8E000000,
 * ROM D_002B1360..D_002B13F0, //@src/fragments/main_menu_launcher) with entry arguments 0, 0,
 * and returns 0x8040 so the fragment loop in func_800260C4 runs the queued call. Fragment 020
 * in turn queues the main menu. Both arguments are ignored.
 *
 * Fragments 021, 022 and 024 are byte-for-byte the same relay at 0x8E100000, 0x8E200000 and
 * 0x8E400000. Nothing in the retail ROM loads this fragment: no lui/addiu pair or data word
 * refers to its ROM range 0x2B1510..0x2B15A0 or its VRAM 0x8E300000, so it looks like a
 * leftover slot.
 *
 * Seen when forced (2026-11-14): after boot, when Fragment006_Main queued the main menu, the
 * pending call at D_800AF990 was rewritten to fragment 0xD3 (this one, ROM 0x2B1510..0x2B15A0).
 * The fragment loop loaded it and ran this function, which queued fragment 0xD0 (020,
 * 0x2B1360..0x2B13F0, args 0, 0); 020 then queued the main menu (0x70, 0x235D70..0x238BD0)
 * and the main menu came up.
 */
s32 UnusedRelay023_QueueMainMenuLauncher(s32 unusedArg0, s32 unusedArg1) {
    Fragment_QueueCall(((((u32)D_8E000000) & 0x0FF00000) >> 0x14) - 0x10, D_002B1360, D_002B13F0, 0, 0);
    return 0x8040;
}
