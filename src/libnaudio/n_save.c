/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libnaudio/n_save.c. */

#include "libnaudio/n_synthInternals.h"
#include <os.h>

Acmd* n_alSavePull(s32 sampleOffset, Acmd* p);

Acmd* n_alSavePull(s32 sample_offset, Acmd* p) {
    Acmd* ptr = p;

    ptr = n_alMainBusPull(sample_offset, ptr);

    // clang-format off
    n_aInterleave(ptr++);                                           \
    n_aSaveBuffer(ptr++, FIXED_SAMPLE << 2, 0, n_syn->sv_dramout);
    // clang-format on
    return ptr;
}
