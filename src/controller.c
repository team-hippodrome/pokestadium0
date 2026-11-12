/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/controller.c, src/input.c. */

#include "global.h"
#include "controller.h"
#include "gb_tower.h"
#include "math_util.h"
extern Controller* gPlayer1Controller;
extern Controller* gPlayer2Controller;
extern Controller* gPlayer3Controller;
extern Controller* gPlayer4Controller;
extern Controller gControllers[4];
extern OSMesgQueue gSIEventMesgQueue;
extern u8 gControllerBits;
extern u8 gEepromProbe;
extern OSContStatus gControllerStatuses[4];
extern OSContPad gControllerPads[4];
extern OSMesg gSIEventMesgBuf[1];
extern OSMesg gEepromMesgBuf[1];
extern OSMesgQueue gEepromMesgQueue;

#include "global.h"
#include "input.h"
extern s32 pad_D_800AC880[0x2];
extern s32 D_800AB02C;
extern Controller* D_800AB030;

#include "m2c_macros.h"

void Cont_AdjustAnalogStick(Controller* controller);
void Input_SetRepeatController(Controller* arg0);
s32 Input_GetRepeatedDPad(void);
s32 Cont_IsEepromPresent(void);

/*
 * Take the updated controller struct and calculate
 * the new x, y, and distance floats.
 */
void Cont_AdjustAnalogStick(Controller* controller) {
    // reset the controller's x and y floats.
    controller->stickX = 0.0f;
    controller->stickY = 0.0f;

    // modulate the rawStickX and rawStickY to be the new f32 values by adding/subtracting 6.
    if (controller->rawStickX <= -8) {
        controller->stickX = controller->rawStickX + 6;
    }

    if (controller->rawStickX >= 8) {
        controller->stickX = controller->rawStickX - 6;
    }

    if (controller->rawStickY <= -8) {
        controller->stickY = controller->rawStickY + 6;
    }

    if (controller->rawStickY >= 8) {
        controller->stickY = controller->rawStickY - 6;
    }

    // calculate f32 magnitude from the center by vector length.
    controller->stickMag = sqrtf(controller->stickX * controller->stickX + controller->stickY * controller->stickY);

    // magnitude cannot exceed 64.0f: if it does, modify the values appropriately to
    // flatten the values down to the allowed maximum value.
    if (controller->stickMag > 64) {
        controller->stickX *= 64 / controller->stickMag;
        controller->stickY *= 64 / controller->stickMag;
        controller->stickMag = 64;
    }

    if (controller->stickMag > 0.0f) {
        controller->angle = MathUtil_Atan2s(-controller->stickY, controller->stickX);
    }
}

extern u8 D_800AAFFA;
extern u8 D_800AAFF8;
/**
 * Initialize the gControllers structs. Clear each member, then set their cont
 * id and set the status and pads pointers.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Cont_InitControllers(void) {
    s16 port;
    s16 cont;

    for (port = 0; port < 4; port++) {
        bzero(&gControllers[port], sizeof(Controller));
    }
    cont = 0;
    port = 0;
    if (D_800AAFFA == 0) {
        for (port = 0; port < 4; port++) {
            if (D_800AAFF8 & (1 << port)) {
                gControllers[port].contId = port + 1;
                gControllers[port].statusData = &gControllerStatuses[port];
                gControllers[port].controllerData = &gControllerPads[port];
            }
        }
    } else {
        for (port = 0; port < 4 && cont < 4; port++) {
            if (D_800AAFF8 & (1 << port)) {
                gControllers[cont].contId = port + 1;
                gControllers[cont].statusData = &gControllerStatuses[port];
                gControllers[cont++].controllerData = &gControllerPads[port];
            }
        }
    }
}

extern u8 D_800AAFFA;
extern u8 D_800AAFF8;
s32 func_80053A90(OSMesgQueue*);

/**
 * Setup the controllers for initial use by initializing the EEPROM queue
 * and SI Event queues. EEPROM probing was handled by game_init.c in Super
 * Mario 64 which also handled the controllers in the same file. Since
 * Nintendo EAD is also credited with co-developing Pokemon Stadium, this
 * organization may be a holdover from that era.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
u8 Cont_SetupControllers(u8 arg0) {
    D_800AAFFA = arg0;
    osCreateMesgQueue(&gSIEventMesgQueue, gSIEventMesgBuf, 1);
    osSetEventMesg(OS_EVENT_SI, &gSIEventMesgQueue, NULL);
    osContInit(&gSIEventMesgQueue, &D_800AAFF8, &gControllerStatuses[0]);
    gEepromProbe = func_80053A90(&gSIEventMesgQueue);
    Cont_InitControllers();
    return D_800AAFF8;
}

M2C_UNK func_80051C70(M2C_UNK *);                   /* extern */
extern M2C_UNK D_800AAFE0;

void func_8000B1FC(void) {
    func_80051C70(&D_800AAFE0);
}

void GbTower_PollPakConnection(void);
void func_8000B220(void) {
    OSMesg msg;
    s32 i;
    Controller* controller;

    if (D_800AAFF8 != 0) {
        osRecvMesg(&gSIEventMesgQueue, &msg, OS_MESG_BLOCK);
        osContGetReadData(&gControllerPads[0]);

        for (i = 0; i < 4; i++) {
            controller = &gControllers[i];
            if (controller->contId != 0) {
                controller->rawStickX = controller->controllerData->stick_x;
                controller->rawStickY = controller->controllerData->stick_y;
                controller->buttonPressed =
                    controller->controllerData->button & (controller->controllerData->button ^ controller->buttonDown);
                controller->buttonReleased = controller->buttonDown & (controller->controllerData->button ^ controller->buttonDown);
                controller->buttonDown = controller->controllerData->button;

                Cont_AdjustAnalogStick(controller);
            }
        }
        GbTower_PollPakConnection();
    }
}

extern u8 D_800AAFF8;

u8 func_8000B2E8(void) {
    return D_800AAFF8;
}

/**
 * Select the controller to poll and initialize its D-pad repeat delay.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void Input_SetRepeatController(Controller* arg0) {
    D_800AB02C = 0xA;
    D_800AB030 = arg0;
}

/**
 * Return one D-pad press, repeating held directions after 10 frames and then every 2 frames.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Input_GetRepeatedDPad(void) {
    if (D_800AB030->buttonPressed & 0x800) {
        D_800AB02C = 0xA;
        return 0x800;
    }

    if (D_800AB030->buttonPressed & 0x400) {
        D_800AB02C = 0xA;
        return 0x400;
    }

    if (D_800AB030->buttonPressed & 0x200) {
        D_800AB02C = 0xA;
        return 0x200;
    }

    if (D_800AB030->buttonPressed & 0x100) {
        D_800AB02C = 0xA;
        return 0x100;
    }

    D_800AB02C--;
    if (D_800AB02C <= 0) {
        D_800AB02C = 0;

        // clang-format off
        if (D_800AB030->buttonDown & 0x800) {
            D_800AB02C = 2; return 0x800;
        }
        // clang-format on

        if (D_800AB030->buttonDown & 0x400) {
            D_800AB02C = 2;
            return 0x400;
        }

        if (D_800AB030->buttonDown & 0x200) {
            D_800AB02C = 2;
            return 0x200;
        }

        if (D_800AB030->buttonDown & 0x100) {
            D_800AB02C = 2;
            return 0x100;
        }
    }

    return 0;
}

/*
 * Check if an EEPROM is connected. Since probe 0x00 is not connected and
 * 0x01 and 0x02 are otherwise, a non-0 probe means it is connected.
 */
s32 Cont_IsEepromPresent(void) {
    return gEepromProbe != 0;
}

/**
 * Attempt to read from EEPROM up to 4 times given a buffer and size and inaddr.
 * A return of 0 indicates success while -1 is an EEPROM error.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 Cont_AttemptReadEeprom(u8* buffer, u32 size, s32 inaddr) {
    s32 result = 1;
    if (gEepromProbe) {
        s32 i = 4;
        do {
            // Get the number of 8-byte buffers to send, since we are sending in 8
            // byte chunks.
            s32 count = size / 8;
            // this value must be a multiple of 8 due to hardware restrictions as
            // specified by http://n64devkit.square7.ch/n64man/os/osEepromLongRead.htm.
            // Force the value to be a multiple of 8 to adhere to the restrictions.
            s32 address = ALIGN8(inaddr);
            i--;
            // once the result is 0 (success), exit from the loop since the write was successful.
            result = osEepromLongRead(&gSIEventMesgQueue, count, buffer, address);
        } while (i > 0 && result);
    }
    return result;
}

s32 func_8000B4D4(u8* buffer, u32 size, s32 inaddr) {
    s32 result = 1;
    if (gEepromProbe) {
        s32 i = 4;
        do {
            // Get the number of 8-byte buffers to send, since we are sending in 8
            // byte chunks.
            s32 count = size / 8;
            // this value must be a multiple of 8 due to hardware restrictions as
            // specified by http://n64devkit.square7.ch/n64man/os/osEepromLongRead.htm.
            // Force the value to be a multiple of 8 to adhere to the restrictions.
            s32 address = ALIGN8(inaddr);
            i--;
            // once the result is 0 (success), exit from the loop since the write was successful.
            result = osEepromLongWrite(&gSIEventMesgQueue, count, buffer, address);
        } while (i > 0 && result);
    }
    return result;
}

/**
 * Busy-waits for `ms` milliseconds using osGetTime.
 * @unverified Name and comment guessed from the code.
 */
void Cont_BusyWaitMs(s32 ms) {
    u64 cycles = OS_USEC_TO_CYCLES(ms * 1000LL); // why not just do OS_NSEC_TO_CYCLES and not multiply by 1000LL?

    osSetTime(0);
    while (osGetTime() < cycles) {}
}

extern u16 gCrashScreenUnlockInputs[];
void Cont_BusyWaitMs(s32 ms);
void crash_screen_wait_for_button_combo(void) {
    s32 breakloop = FALSE;
    s32 i = 0;

    do {
        Cont_StartReadInputs();
        Cont_ReadInputs();
        if (gPlayer1Controller->buttonPressed != 0) {
            if (gPlayer1Controller->buttonPressed == gCrashScreenUnlockInputs[i++]) {
                // have we reached the end of the array? exit the sleep loop.
                if (i == 10) {
                    breakloop = TRUE;
                }
            } else {
                i = 0;
            }
        }
        Cont_BusyWaitMs(10);
    } while (breakloop == FALSE);
}
