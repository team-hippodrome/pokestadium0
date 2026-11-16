/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libleo/cjcreateleomanager.c (libleo, built at -O2). */

/*
 * This libleo module calls __osSetHWIntrRoutine with two arguments, as the
 * libultra headers before 2.0I-P declare it.
 */
#undef BUILD_VERSION
#define BUILD_VERSION 6 /* VERSION_I */
#include "global.h"

#include "libleo/internal.h"
OSPiHandle* osLeoDiskInit(void);
OSPiHandle* osDriveRomInit(void);
s32 __osLeoInterrupt(void);
void leoInitialize(OSPri compri, OSPri intpri, OSMesg* command_que_buf, u32 cmd_buff_size);
void leoCommand(void* cmd_blk_addr);

s32 LeoCJCreateLeoManager(OSPri com_pri, OSPri int_pri, OSMesg* cmd_buf, s32 cmd_msg_cnt) {
    OSPiHandle* drive_rom_handle;
    OSPiHandle* leo_disk_handle;
    volatile LEOCmdInquiry cmd_block_inq;
    UNUSED volatile LEOCmd cmdBlockID;
    UNUSED LEODiskID thisID;
    u32 stat;
    u32 data;

    if (__leoActive) {
        return LEO_ERROR_GOOD;
    }

    leo_disk_handle = osLeoDiskInit();
    drive_rom_handle = osDriveRomInit();
    osEPiReadIo(leo_disk_handle, 0x05000508, &data);
    if (data & 0xFFFF) {
        return LEO_ERROR_DEVICE_COMMUNICATION_FAILURE;
    }
    __leoActive = 1;

    __osSetHWIntrRoutine(1, __osLeoInterrupt);
    leoInitialize(com_pri, int_pri, cmd_buf, cmd_msg_cnt);

    if (osResetType == 1) {
        __leoSetReset();
    }

    cmd_block_inq.header.command = 2;
    cmd_block_inq.header.reserve1 = 0;
    cmd_block_inq.header.control = 0;
    cmd_block_inq.header.reserve3 = 0;
    leoCommand((void*)&cmd_block_inq);

    {
        volatile s32 dummy = (u32)&cmd_block_inq & 0xFFFFFF;

        while (dummy > 0) {
            dummy -= ((u32)__leoSetReset & 0xFFFFFF) | 0x403DF4;
        }
    }

    while (cmd_block_inq.header.status == 8) {
        ;
    }

    if (cmd_block_inq.header.status != 0) {
        return cmd_block_inq.header.sense;
    }

    __leoVersion.driver = cmd_block_inq.version;
    __leoVersion.drive = 5;
    __leoVersion.deviceType = cmd_block_inq.dev_type;
    __leoVersion.ndevices = cmd_block_inq.dev_num;

    stat = __leoVersion.driver & 0xF;
    if (stat == 4) {
        LEO_country_code = 0;
    } else if ((stat == 3) || (stat == 1)) {
        volatile u32 dummy;

        osEPiReadIo(drive_rom_handle, 0x9FF00, &data);
        data = ((data & 0xFF000000) >> 0x18);
        dummy = 0x3ED98F23;
        if (data != 0xC3) {
            while (1) {}
        }

        dummy *= data;
        dummy -= (u32)&cmd_block_inq;
        LEO_country_code = 0xE848D316;
    } else {
        while (1) {}
    }

    return LEO_ERROR_GOOD;
}
