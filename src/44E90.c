/* Stadium Zero resident code. */

#include "global.h"

/*
 * func_80044290: initialises the record `arg0` from the descriptor `arg1` and
 * tries to attach a second object to it.
 *
 * `arg1` holds a s16 at +0 (copied to arg0+0x16 and used as the lookup key), a s16 at
 * +2 (copied to arg0+0x18) and a u8 at +4 (copied, widened, to arg0+0x1A).  arg0+0x14
 * and the words at arg0+0x8 / +0xC are cleared.  func_800443C4(&obj, key) then looks
 * up an object.  If it leaves a non-NULL `obj`, the two are linked (obj+0x8 and
 * arg0+0x8 point at each other).  If func_800443C4 also returned non-zero, obj's word
 * at +0x88 is set to 0x200 (after clearing word +0x8 of the record that obj+0x8 pointed
 * at before the link) and two blocks are posted with func_8003AE2C(obj, 3, block): the
 * first has halfword +8 = 0xB (word +4 = D_80075E44[+0x1C], word +0xC = 0, word +0x10 = obj[+0x88] - 0x40) and,
 * if func_800448F8 can supply a second block, one with halfword +8 = 0xF (word +0 = 0,
 * word +4 = D_80075E44[+0x1C] + obj[+0x88]).  If it returned zero, obj[+0x88] is cleared
 * and only the link is made.  Returns 1 if an object was found, else 0.  (The meaning
 * of these records is not established here; the field offsets are taken from the retail code.)
 */

#include "m2c_macros.h"
M2C_UNK func_8003AE2C(void *, M2C_UNK, void *);
s32 func_800443C4(void **, s16);
void *func_800448F8();
extern void *D_80075E44;

s32 func_80044290(void *arg0, void *arg1) {
    void *obj;
    s32 found;
    void *msg_a;
    void *msg_b;

    obj = NULL;
    M2C_FIELD(arg0, s16 *, 0x16) = (s16) M2C_FIELD(arg1, s16 *, 0);
    M2C_FIELD(arg0, s16 *, 0x1A) = (s16) M2C_FIELD(arg1, u8 *, 4);
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0x18) = (s16) M2C_FIELD(arg1, s16 *, 2);
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    M2C_FIELD(arg0, void **, 8) = NULL;
    found = func_800443C4(&obj, M2C_FIELD(arg1, s16 *, 0));
    if (obj) {
        if (found != 0) {
            M2C_FIELD(obj, s32 *, 0x88) = 0x200;
            M2C_FIELD(M2C_FIELD(obj, void **, 8), s32 *, 8) = 0;
            M2C_FIELD(obj, void **, 8) = arg0;
            M2C_FIELD(arg0, void **, 8) = obj;
            msg_a = func_800448F8();
            M2C_FIELD(msg_a, s32 *, 4) = (s32) M2C_FIELD(D_80075E44, s32 *, 0x1C);
            M2C_FIELD(msg_a, s16 *, 8) = 0xB;
            M2C_FIELD(msg_a, s32 *, 0xC) = 0;
            M2C_FIELD(msg_a, s32 *, 0x10) = (s32) (M2C_FIELD(obj, s32 *, 0x88) - 0x40);
            func_8003AE2C(M2C_FIELD(arg0, void **, 8), 3, msg_a);
            msg_b = func_800448F8();
            if (msg_b != NULL) {
                M2C_FIELD(msg_b, s32 *, 4) = (s32) (M2C_FIELD(obj, s32 *, 0x88) + M2C_FIELD(D_80075E44, s32 *, 0x1C));
                M2C_FIELD(msg_b, s16 *, 8) = 0xF;
                M2C_FIELD(msg_b, s32 *, 0) = 0;
                func_8003AE2C(M2C_FIELD(arg0, void **, 8), 3, msg_b);
            }
        } else {
            M2C_FIELD(obj, s32 *, 0x88) = 0;
            M2C_FIELD(obj, void **, 8) = arg0;
            M2C_FIELD(arg0, void **, 8) = obj;
        }
    }
    return obj != NULL;
}

#ifdef NON_MATCHING
/* TODO: decompile func_800443C4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800443C4.s")
#endif
