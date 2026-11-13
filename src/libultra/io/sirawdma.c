/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"

s32 func_80051FD0(s32);                             /* extern */
M2C_UNK func_80052100(s32, M2C_UNK, s32);           /* extern */
M2C_UNK func_80056730(s32, M2C_UNK, s32);           /* extern */
s32 func_80052CC0(s32 arg0, s32 arg1) {
    if ((*(volatile s32 *)0xA4800018) & 3) {
        return -1;
    }
    if (arg0 == 1) {
        func_80052100(arg1, 0x40, arg0);
    }
    (*(volatile s32 *)0xA4800000) = func_80051FD0(arg1);
    if (arg0 == 0) {
        (*(volatile s32 *)0xA4800004) = 0x1FC007C0;
    } else {
        (*(volatile s32 *)0xA4800010) = 0x1FC007C0;
    }
    if (arg0 == 0) {
        func_80056730(arg1, 0x40, arg0);
    }
    return 0;
}
