/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/audio_sound_state.c. */

#include "audio_sound_state.h"
#include "libnumus/player.h"

s32 Audio_GetActiveVoiceCount(void);

/** Returns the number of voices that are being released. */
s32 Audio_GetActiveVoiceCount(void) {
    return mus_releasing_voices_count;
}
