/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libleo/seek.c. */

#include "global.h"
#include "libleo/internal.h"

s32 LeoSeek(LEOCmd* cmdBlock, u32 lba, OSMesgQueue* mq);

s32 LeoSeek(LEOCmd* cmd_block, u32 lba, OSMesgQueue* mq) {
    if (!__leoActive) {
        return -1;
    }
    cmd_block->header.command = LEO_COMMAND_SEEK;
    cmd_block->header.reserve1 = 0;
    cmd_block->header.control = 0;
    cmd_block->header.reserve3 = 0;
    cmd_block->data.readwrite.lba = lba;
    if (mq != NULL) {
        cmd_block->header.control |= LEO_CONTROL_POST;
        cmd_block->header.post = mq;
    }
    leoCommand(cmd_block);
    return 0;
}
