/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/audio_sfx_wrapper.c. */

#include "audio_sfx_wrapper.h"
#include "fragments/battle/battle.h"

void Audio_PlaySoundEffectByIdWrapper(s32 arg0);

/** Wrapper that plays a sound effect by id. */
void Audio_PlaySoundEffectByIdWrapper(s32 arg0) {
    Audio_PlaySoundEffectById(arg0);
}

/**
 * Audio_QueueSequenceId
 *
 * Returns the word 0x3C bytes above this function's own stack pointer, i.e.
 * a value the caller left in its outgoing-argument area (the 16th word
 * counting from the argument save area).  It touches no globals and writes
 * nothing, so it ignores whatever it is given: in this build it behaves as
 * a stub.  The C below is just the shape that produces
 * `lw $v0, 0x3C($sp)`.  Its purpose is unknown.
 *
 * NOTE: linker_scripts/jp/symbol_addrs.txt calls this address
 * Audio_QueueSequenceId, and Audio_QueueSequenceIdWrapper (func_80031D00)
 * calls it with one argument.  A function that really queued a sequence id
 * would have to store something, so that name does not fit this code and
 * should be double-checked.  The address-style name is used here.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Audio_QueueSequenceId(void) {
    s32 arr[1];

    return arr[16];
}
