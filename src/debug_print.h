/* Declarations for src/debug_print.c. */
#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include "global.h"

// debug_print.c
void Debug_PrintMtx(s32 *arg0);
void Debug_PrintMtxF(f32* arg0);
Gfx* Gfx_DrawTriangleMarker(Gfx* arg0, Vec3f* arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6);

#endif // DEBUG_PRINT_H
