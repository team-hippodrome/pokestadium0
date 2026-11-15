/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/audio_cache.c. */

#include "global.h"
#include "audio_cache.h"

void Audio_CopyDataWithCacheSync(s32 arg0, void* arg1, s32 arg2);

/**
 * Decodes the Yay0 data at `arg0` into `arg1` (func_80048010, handwritten): invalidates both caches over
 * the `arg2`-byte destination first and writes the data cache back after. Audio_PlayCry uses it to
 * unpack a cry.
 */
void Audio_CopyDataWithCacheSync(s32 arg0, void* arg1, s32 arg2) {
    osInvalICache(arg1, arg2);
    osInvalDCache(arg1, arg2);
    D_80048010(arg0, arg1);
    osWritebackDCache(arg1, arg2);
}
