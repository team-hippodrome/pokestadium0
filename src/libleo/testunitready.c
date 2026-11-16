/* Stadium Zero resident code. */

#include "global.h"
#include "libleo/internal.h"

s32 LeoTestUnitReady(u8* status) {
    volatile LEOCmdTestUnitReady cmd_block;

    if (!__leoActive) {
        return -1;
    }
    if (HW_REG(PI_STATUS_REG, u32) & 1) {
        return LEO_STATUS_BUSY;
    }
    cmd_block.header.command = 3;
    cmd_block.header.reserve1 = 0;
    cmd_block.header.control = 0;
    cmd_block.header.reserve3 = 0;
    leoCommand((void*)&cmd_block);

    while (cmd_block.header.status == LEO_STATUS_BUSY) {}

    *status = cmd_block.test;
    return cmd_block.header.sense;
}
