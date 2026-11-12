/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/audio_channel.c, src/audio_sound_state.c. */

#include "audio_channel.h"
#include "audio_sfx.h"
#include "libnumus/player.h"
#include "3D140.h"

#include "audio_sound_state.h"
#include "libnumus/player.h"
#include "audio_stream.h"
#include "3D140.h"
#include "audio_commands.h"

void Audio_SetMonoOutput(s32 arg0);
void Audio_IsSoundPlayingWrapper(s32 arg0);

/** Sets mono or stereo audio output. */
void Audio_SetMonoOutput(s32 arg0) {
    Audio_QueueSetMonoOutputCommand(arg0);
}

/** Wrapper that checks whether a sound is playing. */
void Audio_IsSoundPlayingWrapper(s32 arg0) {
    Audio_IsSoundPlaying(arg0);
}
