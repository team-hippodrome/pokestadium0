/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libleo/leofunc.c. */

#include "global.h"
#include "libleo/internal.h"
#include "PR/os_message.h"
extern const u8 LEO_ZERO_MESG[];
extern s32 __leoResetCalled;
extern s32 __leoQueuesCreated;
extern OSMesgQueue LEOpost_que;
extern OSMesg LEOpost_que_buf[1];
extern leo_sys_form LEO_sys_data;
extern OSThread LEOcommandThread;
extern OSThread LEOinterruptThread;
extern u8 LEOinterruptThreadStack[0x400];
extern u8 LEOcommandThreadStack[0x400];
extern OSMesgQueue LEOcommand_que;
extern OSMesgQueue LEOevent_que;
extern OSMesgQueue LEOcontrol_que;
extern OSMesgQueue LEOdma_que;
extern OSMesgQueue LEOblock_que;
extern OSMesg LEOevent_que_buf[1];
extern OSMesg LEOcontrol_que_buf[1];
extern OSMesg LEOdma_que_buf[2];

#include "m2c_macros.h"

s32 __leoSetReset(void);
s32 LeoResetClear(void);

M2C_UNK func_8004CFB0(M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_80051B20(M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *, s32); /* extern */
M2C_UNK func_800552D0(M2C_UNK, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_800567E0(M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_8005C130(M2C_UNK *);                   /* extern */
extern M2C_UNK D_80100190;
extern M2C_UNK D_801001A8;
extern M2C_UNK D_80100298;
extern M2C_UNK D_80100448;
extern M2C_UNK D_801009F8;
extern M2C_UNK D_80100DF8;
extern M2C_UNK D_80100E10;
extern M2C_UNK D_80100E28;
extern M2C_UNK D_80100E40;
extern M2C_UNK D_80100E58;
extern M2C_UNK D_80100E70;
extern M2C_UNK D_80100E74;
extern M2C_UNK D_80100E78;
extern M2C_UNK D_80100E80;
extern M2C_UNK func_800487A0;
extern M2C_UNK func_800491A0;

void func_800483E0(s32 arg0, s32 arg1, M2C_UNK *arg2, M2C_UNK arg3) {
    func_800567E0(&D_80100DF8, arg2, arg3);
    func_800567E0(&D_80100E28, &D_80100E74, 1);
    func_800567E0(&D_80100E10, &D_80100E70, 1);
    func_800567E0(&D_80100E40, &D_80100E78, 2);
    func_800567E0(&D_80100E58, &D_80100E80, 1);
    func_800567E0(&D_80100190, &D_801001A8, 1);
    func_80051B20(&D_80100298, 1, &func_800491A0, 0, &D_801009F8, arg0);
    func_8005C130(&D_80100298);
    func_80051B20(&D_80100448, 1, &func_800487A0, 0, &D_80100DF8, arg1);
    func_8005C130(&D_80100448);
    func_800552D0(2, &D_80100E10, 0x30000);
    func_8004CFB0(&D_80100E58, 0, 0);
}

/*
 * func_80048530 (leoCommand in the Stadium 1 decomp): submits a 64DD command block.
 *
 * Takes the block-queue (D_80100E58) lock, marks the block busy (status 8, sense 0)
 * and then dispatches on the command byte:
 *   - command 1 (queue clear): clears the command queue via leoClr_queue (with
 *     LEOclr_que_flag set around it), marks the block GOOD and, if the POST bit
 *     (0x80) of its control byte is set, posts 0 to the block's reply queue;
 *   - commands 5 and 6 (read/write): zero the transfer byte count, then queue;
 *   - any other command: rejected with sense INVALID_COMMAND_OPERATION_CODE and
 *     status CHECK_CONDITION unless it is one of commands 1..0xE, which are queued;
 *   - queueing posts the block to LEOcommand_que without blocking; if the queue is
 *     full the block is marked QUEUE_FULL / CHECK_CONDITION.
 * Finally the block-queue lock is released.
 *
 * Unlike the Stadium 1 version there is no __leoResetCalled check at the start.
 */
void func_80048530(void* cmd_blk_addr) {
    osRecvMesg((OSMesgQueue*)&D_80100E58, NULL, 1);
    ((LEOCmd*)cmd_blk_addr)->header.status = LEO_STATUS_BUSY;
    ((LEOCmd*)cmd_blk_addr)->header.sense = LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION;
    switch (((LEOCmd*)cmd_blk_addr)->header.command) {
        case 1:
            LEOclr_que_flag = 0xFF;
            leoClr_queue();
            LEOclr_que_flag = 0;
            ((LEOCmd*)cmd_blk_addr)->header.status = LEO_STATUS_GOOD;
            if (((LEOCmd*)cmd_blk_addr)->header.control & LEO_CONTROL_POST) {
                osSendMesg(((LEOCmd*)cmd_blk_addr)->header.post, (OSMesg)0, 1);
            }
            break;
        case 5:
        case 6:
            ((LEOCmd*)cmd_blk_addr)->data.readwrite.rw_bytes = 0;
            goto cmd_queing;
        default:
            if ((u32)(((LEOCmd*)cmd_blk_addr)->header.command - 1) >= 0xE) {
                ((LEOCmd*)cmd_blk_addr)->header.sense = LEO_SENSE_INVALID_COMMAND_OPERATION_CODE;
                ((LEOCmd*)cmd_blk_addr)->header.status = LEO_STATUS_CHECK_CONDITION;
                break;
            }
        cmd_queing:
            if (osSendMesg(&LEOcommand_que, (OSMesg)cmd_blk_addr, 0) != 0) {
                ((LEOCmd*)cmd_blk_addr)->header.sense = LEO_SENSE_QUEUE_FULL;
                ((LEOCmd*)cmd_blk_addr)->header.status = LEO_STATUS_CHECK_CONDITION;
            }
    }
    osSendMesg((OSMesgQueue*)&D_80100E58, (OSMesg)0, 1);
}

void LeoReset(void) {
    osRecvMesg((OSMesgQueue*)&D_80100E58, NULL, 1);
    LEOclr_que_flag = 0xFF;
    leoClr_queue();
    LEOclr_que_flag = 0;
    osRecvMesg(&LEOevent_que, NULL, 0);
    osSendMesg(&LEOevent_que, (OSMesg)ASIC_SOFT_RESET_CODE, 1);
    osSendMesg(&LEOcommand_que, (OSMesg)LEO_ZERO_MESG, 1);
}

s32 __leoSetReset(void) {
    leoDrive_reset();
    return 0;
}

s32 LeoResetClear(void) {
    LEOCmdHeader resetclear;

    resetclear.command = 0xF;
    resetclear.control = LEO_CONTROL_POST;
    resetclear.status = 0;
    resetclear.post = &LEOpost_que;
    if (osSendMesg(&LEOcommand_que, &resetclear.command, 0) != 0) {
        return LEO_SENSE_QUEUE_FULL;
    }
    osRecvMesg(&LEOpost_que, NULL, 1);
    if (resetclear.status == LEO_STATUS_GOOD) {
        return LEO_SENSE_NO_ADDITIONAL_SENSE_INFOMATION;
    }
    return resetclear.sense;
}
