/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libleo/spdlmotor.c. */

#include "global.h"
#include "libleo/internal.h"

s32 LeoSpdlMotor(LEOCmd* cmdBlock, u8 mode, OSMesgQueue* mq);

s32 LeoSpdlMotor(LEOCmd* cmd_block, u8 mode, OSMesgQueue* mq) {
    if (!__leoActive) {
        return -1;
    }
    cmd_block->header.command = LEO_COMMAND_START_STOP;
    cmd_block->header.reserve1 = 0;

    switch (mode) {
        case LEO_MOTOR_ACTIVE:
            cmd_block->header.control = LEO_CONTROL_START;
            break;
        case LEO_MOTOR_STANDBY:
            cmd_block->header.control = LEO_CONTROL_STBY;
            break;
        case LEO_MOTOR_SLEEP:
            cmd_block->header.control = 0;
            break;
        case LEO_MOTOR_BRAKE:
            cmd_block->header.control = LEO_CONTROL_BRAKE;
            break;
    }
    cmd_block->header.reserve3 = 0;

    if (mq != NULL) {
        cmd_block->header.post = mq;
        cmd_block->header.control |= LEO_CONTROL_POST;
    }

    leoCommand(cmd_block);
    return 0;
}
