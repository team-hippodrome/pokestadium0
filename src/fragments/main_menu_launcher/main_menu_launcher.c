/* Stadium Zero fragment020_2B1360. */

#include "global.h"
#include "m2c_macros.h"

M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32); /* extern */
extern M2C_UNK D_00235D70;
extern M2C_UNK D_00238BD0;
extern M2C_UNK D_88000000;

s32 func_8E000020(s32 arg0, M2C_UNK arg1) {
    func_80025BA0(((u32) ((s32) &D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
    return 0x8040;
}
