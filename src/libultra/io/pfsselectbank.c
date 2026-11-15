/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"

s32 func_80059790(OSMesgQueue* queue, s32 channel, u16 address, u8* buffer, s32 arg4);

s32 __osPfsSelectBank(OSPfs* pfs, u8 bank) {
    u8 buffer[BLOCKSIZE];
    s32 i;
    s32 ret;

    for (i = 0; i < BLOCKSIZE; i++) {
        buffer[i] = bank;
    }

    ret = func_80059790(pfs->queue, pfs->channel, 0x400, buffer, 0);
    if (ret == 0) {
        pfs->activebank = bank;
    }
    return ret;
}
