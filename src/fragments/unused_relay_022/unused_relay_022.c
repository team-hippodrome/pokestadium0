/* Stadium Zero fragment022_2B1480. */

#include "global.h"
#include "m2c_macros.h"
#include "unused_relay_022.h"

M2C_UNK Fragment_QueueCall(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32); /* extern */
extern M2C_UNK D_002B1360;
extern M2C_UNK D_002B13F0;
extern M2C_UNK D_8E000000;

/**
 * Entry point of fragment 022 (slot 0x8E200000). Queues fragment 020
 * (main_menu_launcher, ROM 0x2B1360, slot 0x8E000000), which in turn queues
 * the main menu, and returns game state 0x8040 so the overlay loop runs it.
 * All three arguments are ignored. The retail code spills a third argument
 * register, so the definition needs three parameters to match, although
 * Fragment_LoadAndCall passes only two.
 *
 * Unused: no code in the ROM loads fragment 022. Every fragment load and queue
 * call takes literal ROM ranges, and none names 0x2B1480 or 0x8E200000.
 * Fragments 021 to 024 are four identical copies of this relay. Stadium 1 has
 * the same pattern in debug_menu_slot68..77 (each queues debug_menu_exit), so
 * these are probably slots of a removed debug menu.
 * @unverified Not reachable in play.
 */
s32 UnusedRelay022_QueueMainMenuLauncher(UNUSED s32 arg0, UNUSED s32 arg1, UNUSED s32 arg2) {
    Fragment_QueueCall(((u32) ((s32) &D_8E000000 & 0x0FF00000) >> 0x14) - 0x10, &D_002B1360, &D_002B13F0, 0, 0);
    return 0x8040;
}
