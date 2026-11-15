/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/33E30.c. */

#include "fragments/cartridge_check/cartridge_check.h"
#include "gfx_buffer.h"
#include "vector_math.h"
#include "debug_print.h"
extern Gfx D_800745F0[];

Gfx* Gfx_DrawTriangleMarker(Gfx* arg0, Vec3f* arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6);

extern char D_8007DBA0[];
extern char D_8007DBA8[];
extern char D_8007DBAC[];
void func_8005666C();
/**
 * Prints an Mtx as 8 rows of 2 hex words via rmonPrintf.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void Debug_PrintMtx(s32 *arg0) {
    s32 i;
    s32 j;
    s32 *p = arg0;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 2; j++) {
            func_8005666C(D_8007DBA0, *p);
            p++;
        }
        func_8005666C(D_8007DBA8);
    }
    func_8005666C(D_8007DBAC);
}

void rmonPrintf(const char* fmt, ...);
extern char D_8007DBB0[];
extern char D_8007DBBC[];
extern char D_8007DBC0[];

/**
 * Prints an MtxF as 4x4 floats via rmonPrintf.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment from Stadium 1, matched by code similarity.
 */
void Debug_PrintMtxF(f32* arg0) {
    s32 i;
    s32 j;
    f32* p = arg0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++, p++) {
            rmonPrintf(D_8007DBB0, *p);
        }
        rmonPrintf(D_8007DBBC);
    }
    rmonPrintf(D_8007DBC0);
}

/**
 * Draws a triangle marker at a position with the given color and scale,
 * returning the advanced display list pointer.
 */
Gfx* Gfx_DrawTriangleMarker(Gfx* arg0, Vec3f* arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6) {
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    Mtx* sp138;
    Mtx spF8;
    Mtx spB8;
    Mtx sp78;
    UNUSED s32 pad; // FAKE: stack padding
    MtxF sp34;

    sp144 = arg1->x;
    sp140 = arg1->y;
    sp13C = arg1->z;

    MtxF_ExtractScale(&sp34, &D_80060488->view.floatMatrix);
    guMtxF2L(&sp34, &sp78);
    guScale(&spB8, arg6, arg6, arg6);
    guTranslate(&spF8, sp144, sp140, sp13C);
    sp138 = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    guMtxCatL(&spB8, &spF8, sp138);
    guMtxCatL(&sp78, sp138, sp138);

    gSPMatrix(arg0++, sp138, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(arg0++, 0, 0, arg2, arg3, arg4, arg5);
    gSPDisplayList(arg0++, D_800745F0);
    gSPPopMatrix(arg0++, G_MTX_MODELVIEW);

    return arg0;
}
