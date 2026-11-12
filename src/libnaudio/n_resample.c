/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libnaudio/n_resample.c. */

#include "libnaudio/n_synthInternals.h"
#include <os.h>
#include <stdio.h>

Acmd* n_alResamplePull(N_PVoice* e, s16* outp, Acmd* p);
s32 n_alResampleParam(N_PVoice* filter, s32 paramID, void* param);

/***********************************************************************
 * Resampler filter public interfaces
 ***********************************************************************/
Acmd* n_alResamplePull(N_PVoice* e, s16* outp, Acmd* p) {
    Acmd* ptr = p;
    s16 inp;
    s32 in_count;
    s32 incr;
    f32 fin_count;


    inp = N_AL_DECODER_OUT;

    /*
     * check if resampler is required
     */
    if (e->rs_upitch) {

        ptr = n_alAdpcmPull(e, &inp, FIXED_SAMPLE, p);
        aDMEMMove(ptr++, inp, *outp, FIXED_SAMPLE << 1);

    } else {

        /*
         * clip to maximum allowable pitch
         * FIXME: should we check for some minimum as well?
         */
        if (e->rs_ratio > MAX_RATIO)
            e->rs_ratio = MAX_RATIO;

        /*
         * quantize the pitch
         */
        e->rs_ratio = (s32)(e->rs_ratio * UNITY_PITCH);
        e->rs_ratio = e->rs_ratio / UNITY_PITCH;

        /*
         * determine how many samples to generate
         */
        fin_count = e->rs_delta + (e->rs_ratio * (f32)FIXED_SAMPLE);
        in_count = (s32)fin_count;
        e->rs_delta = fin_count - (f32)in_count;

        /*
         * ask all filters upstream from us to build their command
         * lists.
         */
        ptr = n_alAdpcmPull(e, &inp, in_count, p);

        /*
         * construct our portion of the command list
         */
        incr = (s32)(e->rs_ratio * UNITY_PITCH);
        n_aResample(ptr++, osVirtualToPhysical(e->rs_state), e->rs_first, incr, inp, 0);
        e->rs_first = 0;
    }

    return ptr;
}

s32 n_alResampleParam(N_PVoice* filter, s32 paramID, void* param) {
    N_PVoice* r = filter;
    union {
        f32 f;
        s32 i;
    } data;

    switch (paramID) {
        default:
            n_alLoadParam(filter, paramID, param);
            break;
    }
    return 0;
}
