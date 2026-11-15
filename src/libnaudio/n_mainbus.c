/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libnaudio/n_mainbus.c (no second stream loop in Stadium Zero). */

#include "libnaudio/n_synthInternals.h"

extern u8 D_800B3CE0;
extern s16* D_800B41EC;
extern u32 D_800FDED0;

Acmd* n_alMainBusPull(s32 sample_offset, Acmd* p) {
    Acmd* ptr = p;

    aClearBuffer(ptr++, N_AL_MAIN_L_OUT, N_AL_DIVIDED << 1);

    ptr = (n_syn->mainBus->filter.handler)(sample_offset, ptr);

    aMix(ptr++, 0, 0x7fff, N_AL_AUX_L_OUT, N_AL_MAIN_L_OUT);
    aMix(ptr++, 0, 0x7fff, N_AL_AUX_R_OUT, N_AL_MAIN_R_OUT);

    if (D_800B3CE0 != 0) {
        aClearBuffer(ptr++, 0x7C0, 0x2E0);
        n_aLoadBuffer(ptr++, 0x170, 0x7C0, osVirtualToPhysical(&D_800B41EC[D_800FDED0]));
        n_aLoadBuffer(ptr++, 0x170, 0x930, osVirtualToPhysical(&D_800B41EC[D_800FDED0]));

        D_800FDED0 += 0xB8;
        if (D_800FDED0 >= 0xB80) {
            D_800FDED0 = 0;
        }
        aMix(ptr++, 0, 0x7fff, N_AL_AUX_L_OUT, N_AL_MAIN_L_OUT);
        aMix(ptr++, 0, 0x7fff, N_AL_AUX_R_OUT, N_AL_MAIN_R_OUT);
        aClearBuffer(ptr++, 0x7C0, 0x2E0);
    }

    return ptr;
}
