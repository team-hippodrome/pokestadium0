/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libleo/leodiskinit.c. */

#include "global.h"
#include "PR/R4300.h"
#include "libleo/internal.h"
extern OSPiHandle __LeoDiskHandle;
extern OSPiHandle* __osDiskHandle;
extern OSPiHandle* __osPiTable;

OSPiHandle* osLeoDiskInit(void);

OSPiHandle* osLeoDiskInit(void) {
    u32 save_mask;

    __LeoDiskHandle.type = DEVICE_TYPE_64DD;
    __LeoDiskHandle.baseAddress = PHYS_TO_K1(PI_DOM2_ADDR1);
    __LeoDiskHandle.latency = 3;
    __LeoDiskHandle.pulse = 6;
    __LeoDiskHandle.pageSize = 6;
    __LeoDiskHandle.relDuration = 2;
    __LeoDiskHandle.domain = PI_DOMAIN2;
    __LeoDiskHandle.speed = 0;

    bzero(&__LeoDiskHandle.transferInfo, sizeof(__OSTranxInfo));

    save_mask = __osDisableInt();
    __LeoDiskHandle.next = __osPiTable;
    __osPiTable = &__LeoDiskHandle;
    __osDiskHandle = &__LeoDiskHandle;
    __osRestoreInt(save_mask);

    return &__LeoDiskHandle;
}
