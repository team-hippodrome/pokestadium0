/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"
#include "audio_fade_helpers.h"

void func_80037AC4(s32 arg0, s32 arg1);
/**
 * Fades out sound `handle` over `frames` (at least 1). @unverified: what func_80037AC4 does is read from callers.
 */
void Audio_FadeOutHandle(s32 handle, s32 frames) {
    if (frames == 0) {
        frames = 1;
    }
    func_80037AC4(handle, frames);
}

void func_8003798C(s32 arg0, s32 arg1);
/**
 * Same as Audio_FadeOutHandle through func_8003798C. @unverified: difference between the two not known.
 */
void Audio_FadeOutHandleAlt(s32 handle, s32 frames) {
    if (frames == 0) {
        frames = 1;
    }
    func_8003798C(handle, frames);
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
M2C_UNK Audio_FadeCategoriesAndStreams(s32);                         /* extern */
extern s8 D_8007753C;
extern s8 D_8007754C;
extern s32 D_80077588;
extern s32 D_8007758C;
/**
 * Mutes the announcer (D_8007753C), marks it inactive, empties its line queue and then fades all audio
 * through Audio_FadeCategoriesAndStreams over `arg0` frames (at least 1).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Audio_FadeCategoriesAndStreamsWithDuration(s32 arg0)
{
  s32 var_a0;
  if (1) // FAKE: wraps the body to order the stores
  {
    var_a0 = arg0;
    D_8007754C = 0;
    D_8007753C = 1;
    D_8007758C = 0;
    D_80077588 = 0;
    if (var_a0 == 0)
    {
      var_a0 = 1;
    }
  }
  Audio_FadeCategoriesAndStreams(var_a0);
}
