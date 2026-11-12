/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libleo/readrtc.c. */

#include "global.h"
#include "libleo/internal.h"

s32 LeoReadRTC(LEOCmd* cmdBlock, OSMesgQueue* mq);

s32 LeoReadRTC(LEOCmd* cmd_block, OSMesgQueue* mq) {
    if (!__leoActive) {
        return -1;
    }
    cmd_block->header.command = LEO_COMMAND_READ_TIMER;
    cmd_block->header.reserve1 = 0;
    cmd_block->header.control = 0;
    cmd_block->header.reserve3 = 0;
    if (mq != NULL) {
        cmd_block->header.control |= LEO_CONTROL_POST;
        cmd_block->header.post = mq;
    }
    leoCommand(cmd_block);
    return 0;
}
