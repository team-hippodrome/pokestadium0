/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libleo/readwrite.c. */

#include "global.h"
#include "libleo/internal.h"

s32 LeoReadWrite(LEOCmd* cmdBlock, s32 direction, u32 LBA, void* vAddr, u32 nLBAs, OSMesgQueue* mq);

s32 LeoReadWrite(LEOCmd* cmd_block, s32 direction, u32 LBA, void* v_addr, u32 nLBAs, OSMesgQueue* mq) {
    if (!__leoActive) {
        return -1;
    }
    if (direction == OS_READ) {
        cmd_block->header.command = LEO_COMMAND_READ;
    } else {
        cmd_block->header.command = LEO_COMMAND_WRITE;
    }
    cmd_block->header.reserve1 = 0;
    if (mq != NULL) {
        cmd_block->header.control = LEO_CONTROL_POST;
    } else {
        cmd_block->header.control = 0;
    }
    cmd_block->header.reserve3 = 0;
    cmd_block->header.post = mq;
    cmd_block->data.readwrite.lba = LBA;
    cmd_block->data.readwrite.xfer_blks = nLBAs;
    cmd_block->data.readwrite.buff_ptr = v_addr;
    leoCommand(cmd_block);
    return 0;
}
