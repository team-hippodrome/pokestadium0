/* Stadium Zero fragment024_2B15A0: an unused relay that returns to the main menu. */

#include "global.h"
#include "m2c_macros.h"
#include "unused_relay_024.h"

void Fragment_QueueCall(s32 fragment_id, u8* rom_start, u8* rom_end, s32 arg0, s32 arg1);
extern u8 D_002B1360[]; // ROM start of fragment020 (main_menu_launcher)
extern u8 D_002B13F0[]; // ROM end of fragment020
extern M2C_UNK D_8E000000; // fragment020 link base

/**
 * Entry point. Queues fragment020 (main_menu_launcher), which in turn queues the main menu
 * (fragment014 at 0x88000000), and returns 0x8040 so the game loop loads the queued fragment.
 * Both arguments are ignored.
 *
 * Nothing in the ROM loads this fragment: no resident code or decoded fragment image holds its
 * ROM range (0x2B15A0-0x2B1630) or link base (0x8E400000), as a word or a lui/addiu pair.
 * Fragments 021-023 are the same image except for the link base (0x8E100000-0x8E300000).
 *
 * Seen in play (2026-11-14) by forcing the load: at the main menu, after バトル (Battle) queued
 * Free Battle, the queued request was rewritten to fragment 0xD4 (ROM 0x2B15A0-0x2B1630). The game
 * loop loaded this fragment and called it, it queued fragment 0xD0 (ROM 0x2B1360-0x2B13F0, args 0
 * and 0), fragment020 then queued fragment 0x70 (ROM 0x235D70-0x238BD0), and the main menu came back.
 */
s32 UnusedRelay024_QueueMainMenuLauncher(s32 unused_arg, s32 unused_context) {
    Fragment_QueueCall(((u32) ((s32) &D_8E000000 & 0x0FF00000) >> 0x14) - 0x10, D_002B1360, D_002B13F0, 0, 0);
    return 0x8040;
}
