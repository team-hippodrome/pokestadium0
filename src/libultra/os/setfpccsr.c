/* Stadium Zero resident code. */
/* Identical to ultralib src/os/setfpccsr.c (2.0I, IDO 5.3); link libultra here once the build exists. */

#include "global.h"
#include "m2c_macros.h"

s32 func_800594E0(void) {
    return (*(volatile s32 *)0xA4500004);
}
