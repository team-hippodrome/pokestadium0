/* Stadium Zero fragment020_2B1360. */

#include "global.h"
#include "m2c_macros.h"
#include "main_menu_launcher.h"

void Fragment_QueueCall(s32 arg0, u8* arg1, u8* arg2, s32 arg3, s32 arg4);
extern u8 D_00235D70[]; // main menu (fragment 014) ROM start
extern u8 D_00238BD0[]; // main menu (fragment 014) ROM end
extern u8 D_88000000[]; // main menu (fragment 014) load address

/**
 * Fragment 020's only function: queues the main menu (fragment 014) with mode 0 and no session
 * context, then returns 0x8040 so the game state loop loads the queued fragment. Both arguments
 * of the fragment entry are ignored.
 * Unreferenced: in the whole ROM only fragments 021-024 load this fragment (their ROM start
 * 0x2B1360 appears nowhere else as a start address), and nothing loads 021-024. The resident
 * code queues the main menu itself (func_800260C4 in game_state.c passes the
 * session context), so this fragment is likely a leftover.
 * @unverified Name and comment from the code; the fragment never loads in normal play.
 */
s32 MainMenuLauncher_QueueMainMenu(s32 unused0, s32 unused1) {
    Fragment_QueueCall(((u32) ((s32) D_88000000 & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
