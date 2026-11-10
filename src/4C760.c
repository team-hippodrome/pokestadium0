/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libleo/leomode_sel.c (libleo, built at -O2). */

#include "global.h"

#include "libleo/internal.h"
void func_8004BB60(void) {
    u32 sense;

    sense = leoSend_asic_cmd_w_nochkDiskChange(ASIC_SET_STBY, LEOcur_command->data.time.yearlo << 0x10);
    if (sense != LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION) {
        goto mselerror;
    }
    sense = leoSend_asic_cmd_w_nochkDiskChange(ASIC_SET_SLEEP, LEOcur_command->data.time.month << 0x10);
    if (sense != LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION) {
        goto mselerror;
    }
    sense = leoSend_asic_cmd_w_nochkDiskChange(ASIC_SET_LED_TIMER, LEOcur_command->data.readwrite.xfer_blks);
    if (sense != LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION) {
    mselerror:
        LEOcur_command->header.sense = sense;
        LEOcur_command->header.status = LEO_STATUS_CHECK_CONDITION;
        return;
    }

    LEOcur_command->header.sense = sense;
    LEOcur_command->header.status = LEO_STATUS_GOOD;
}
