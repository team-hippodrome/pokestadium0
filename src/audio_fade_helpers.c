/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"

/*
 * func_80047490
 *
 * Calls func_80037AC4(arg0, arg1) with arg1 replaced by 1 when it is 0.
 * (The sibling func_800474B8 does the same for func_8003798C.)  What the
 * second argument means is not known; only the "0 becomes 1" rule is
 * confirmed by the assembly.
 */
void func_80037AC4(s32 arg0, s32 arg1);
void func_80047490(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        arg1 = 1;
    }
    func_80037AC4(arg0, arg1);
}

/*
 * func_800474B8
 *
 * Calls func_8003798C(arg0, arg1) with arg1 replaced by 1 when it is 0.
 * Same pattern as func_80047490, which targets func_80037AC4 instead.
 */
void func_8003798C(s32 arg0, s32 arg1);
void func_800474B8(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        arg1 = 1;
    }
    func_8003798C(arg0, arg1);
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
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Audio_FadeCategoriesAndStreamsWithDuration(s32 arg0)
{
  s32 var_a0;
  if (1)
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
