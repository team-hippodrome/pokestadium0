/* Fixed-layout split (func_88000020 only); original translation-unit boundaries remain unconfirmed. */

#include "global.h"
#include "m2c_macros.h"

M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32);
extern M2C_UNK D_89000000;
extern M2C_UNK D_89100000;
extern M2C_UNK D_8A100000;
extern M2C_UNK D_82000000;
extern M2C_UNK D_8A200000;
extern M2C_UNK D_88400000;
extern M2C_UNK D_88100000;
extern M2C_UNK D_00238BD0;
extern M2C_UNK D_00252E10;
extern M2C_UNK D_00261F00;
extern M2C_UNK D_00262620;
extern M2C_UNK D_00293410;
extern M2C_UNK D_00166580;
extern M2C_UNK D_001720F0;
extern M2C_UNK D_002B1360;
extern M2C_UNK D_00162BE0;
extern M2C_UNK D_00175570;

/**
 * Queues the fragment for lab menu choice arg0 with func_80025BA0 and returns
 * the next state (0x8040, or 0x8060 for choice 6, which loads nothing).
 */
s32 func_88000020(u32 arg0) {
    s32 ret;

    // Each "ret = ...; func_80025BA0(...);" pair has to share one line (as a macro
    // expansion would) for IDO to schedule it like the retail code.
    switch (arg0) {
        case 0:
            ret = 0x8040; func_80025BA0(((u32)((s32)&D_89000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00238BD0, &D_00252E10, 0, 0);
            break;
        case 2:
            ret = 0x8040; func_80025BA0(((u32)((s32)&D_89100000 & 0x0FF00000) >> 0x14) - 0x10, &D_00252E10, &D_00261F00, 0, 0);
            break;
        case 3:
            ret = 0x8040; func_80025BA0(((u32)((s32)&D_8A100000 & 0x0FF00000) >> 0x14) - 0x10, &D_00262620, &D_00293410, 0, 0);
            break;
        case 4:
            ret = 0x8040; func_80025BA0(((u32)((s32)&D_82000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00166580, &D_001720F0, 0, 0);
            break;
        case 5:
            ret = 0x8040; func_80025BA0(((u32)((s32)&D_8A200000 & 0x0FF00000) >> 0x14) - 0x10, &D_00293410, &D_002B1360, 0, 0);
            break;
        case 6:
            ret = 0x8060;
            break;
        case 7:
            ret = 0x8040; func_80025BA0(((u32)((s32)&D_88400000 & 0x0FF00000) >> 0x14) - 0x10, &D_00162BE0, &D_00166580, 1, 0);
            break;
        case 8:
            ret = 0x8040; func_80025BA0(((u32)((s32)&D_88100000 & 0x0FF00000) >> 0x14) - 0x10, &D_001720F0, &D_00175570, 0, 0);
            break;
    }
    return ret;
}
