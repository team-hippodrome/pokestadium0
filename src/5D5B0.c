/* Stadium Zero resident code. */

#include "global.h"

s32 func_8005C9B0(void) {
    register s32 status = IO_READ(AI_STATUS_REG);

    if (status & AI_STATUS_FIFO_FULL) {
        return 1;
    } else {
        return 0;
    }
}

