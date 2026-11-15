/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/audio_cache.c. */

#include "global.h"
#include "audio_cache.h"

void Audio_CopyDataWithCacheSync(s32 arg0, void* arg1, s32 arg2);

/**
 * Invalidates the instruction and data caches over a range after audio data
 * was copied.
 */
void Audio_CopyDataWithCacheSync(s32 arg0, void* arg1, s32 arg2) {
    osInvalICache(arg1, arg2);
    osInvalDCache(arg1, arg2);
    D_80048010(arg0, arg1);
    osWritebackDCache(arg1, arg2);
}
