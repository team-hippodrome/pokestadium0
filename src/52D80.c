/* Stadium Zero resident libultra: osInitialize from an ultralib revision before 2.0I (os/initialize.c). */

#include "PR/os_internal.h"
#include "PR/rcp.h"

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;
extern __osExceptionVector func_8004DD80[];
OSTime D_80077F20 = OS_CLOCK_RATE;
s32 osViClock = VI_NTSC_CLOCK;
u32 __osShutdown = 0;
u32 __OSGlobalIntMask = OS_IM_ALL;
extern u32 D_80102980;
extern u8 D_8000031C[];
u32 __osGetSR(void);
void __osSetSR(u32);
u32 __osSetFpcCsr(u32);
s32 __osSiRawReadIo(u32, u32*);
s32 __osSiRawWriteIo(u32, u32);
void osMapTLBRdb(void);

void func_80052180(void) {
    u32 pifdata;
    u32 clock = 0;

    D_80102980 = TRUE;

    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV);

    while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) {
        ;
    }
    while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8)) {
        ;
    }
    *(__osExceptionVector*)UT_VEC = *func_8004DD80;
    *(__osExceptionVector*)XUT_VEC = *func_8004DD80;
    *(__osExceptionVector*)ECC_VEC = *func_8004DD80;
    *(__osExceptionVector*)E_VEC = *func_8004DD80;
    osWritebackDCache((void*)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void*)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));

    osMapTLBRdb();
    osPiRawReadIo(4, &clock);
    clock &= ~0xf;
    if (clock != 0) {
        D_80077F20 = clock;
    }
    D_80077F20 = D_80077F20 * 3 / 4;

    if (osResetType == 0) {
        bzero(D_8000031C, OS_APP_NMI_BUFSIZE);
    }

    if (osTvType == OS_TV_PAL) {
        osViClock = VI_PAL_CLOCK;
    } else if (osTvType == OS_TV_MPAL) {
        osViClock = VI_MPAL_CLOCK;
    } else {
        osViClock = VI_NTSC_CLOCK;
    }
}
