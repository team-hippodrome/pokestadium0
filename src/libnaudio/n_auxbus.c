/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libnaudio/n_auxbus.c. */

#include "libnaudio/n_synthInternals.h"

Acmd* n_alAuxBusPull(s32 sampleOffset, Acmd* p);

Acmd* n_alAuxBusPull(s32 sample_offset, Acmd* p) {
    Acmd* ptr = p;
    N_ALAuxBus* m = (N_ALAuxBus*)n_syn->auxBus;
    N_PVoice** sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, N_AL_AUX_L_OUT, N_AL_DIVIDED << 1);

    for (i = 0; i < m->sourceCount; i++)
        ptr = n_alEnvmixerPull(sources[i], sample_offset, ptr);
    return ptr;
}
