/* Stadium Zero resident code. */

#include "global.h"
#include "fabsf.h"

/*
 * fabsf
 *
 * Absolute value of a float.  The whole function is one `abs.s` followed by
 * the return, i.e. the compiler's built-in fabsf; the pragma below makes IDO
 * emit that instruction instead of a call.
 */
f32 fabsf(f32 x);
#pragma intrinsic(fabsf)

f32 fabsf(f32 arg0) {
    return fabsf(arg0);
}
