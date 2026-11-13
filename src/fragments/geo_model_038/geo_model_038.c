/* Stadium Zero fragment038_38A540. */

#include "global.h"
#include "m2c_macros.h"

s32 func_8004D300(s32);                             /* extern */
s32 func_8F400020(s32 arg0) {
    s32 temp_a0;

    temp_a0 = func_8004D300(1);
    if (!((*(volatile s32 *)0xA4600010) & 3) && (((*(volatile s32 *)0xB0000504) & 0xFFFF) != 0xA460)) {
        arg0 = -1;
    }
    func_8004D300(temp_a0);
    return arg0;
}

s32 func_8F400020(s32);                             /* extern */
extern s8 *D_8006049C;

void func_8F400088(s32 arg0, s8 *arg1) {
    if (arg0 == 2) {
        M2C_FIELD(arg1, s32 *, 0xC) = func_8F400020(M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s16 *, 0x1A) = (s16) M2C_FIELD(D_8006049C, s32 *, 0x14);
    }
}
