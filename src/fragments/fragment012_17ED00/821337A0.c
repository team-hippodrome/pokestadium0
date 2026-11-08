/* Stadium Zero fragment012_17ED00. */

#include "fragments/battle_engine/battle_engine.h"
#include "m2c_macros.h"

void func_821337A0(s8 *arg0)
{
  int new_var;
  new_var = (*((s32 *) (((s8 *) arg0) + 0x860))) + 0x1C;
  *((u16 *) (((s8 *) new_var) + 2)) = (u16) (*((u16 *) (((s8 *) arg0) + 0x7D2)));
}

/*
 * func_821337B4
 *
 * Resets some fields of the battle scene object (D_8219A5A0, named
 * sBattleScene in symbol_addrs.txt; D_82199DE0 is sActivePokemon, an array
 * of two pointers):
 *
 *   - BattleScene_SetCameraSubstate(1, 0) is called.
 *   - The halfword at +0x2C of the scene object is saved, then cleared, and
 *     the halfword at +0x2A is written with the cleared value (0).
 *   - The word at +0x38 is cleared, and the halfword at +0x32 is cleared in
 *     the structure at 0x78C bytes into each of the two active Pokemon.
 *   - If the word at +0x1C is 9, the word at +0x44 is set to 10.
 *   - func_82133868 is called with the saved halfword, and the halfword is
 *     then written back to +0x2C.
 *
 * What the individual fields mean and what func_82133868 does are not
 * established here.  The saved value is kept in an s32 and func_82133868 is
 * declared with an s32 parameter because that is what reproduces the retail
 * code (a word-sized stack spill and no halfword mask on the argument).
 */
M2C_UNK func_82121D8C(M2C_UNK, M2C_UNK);            /* extern */
void func_82133868();
extern M2C_UNK D_82199DE0;
extern void *D_8219A5A0;

void func_821337B4(void) {
    s32 saved;
    void *sp20;
    void *sp1C;

    sp20 = M2C_FIELD(&D_82199DE0, s32 *, 0) + 0x78C;
    sp1C = M2C_FIELD(&D_82199DE0, s32 *, 4) + 0x78C;
    func_82121D8C(1, 0);
    saved = M2C_FIELD(D_8219A5A0, u16 *, 0x2C);
    M2C_FIELD(D_8219A5A0, u16 *, 0x2C) = 0U;
    M2C_FIELD(D_8219A5A0, u16 *, 0x2A) = (u16) M2C_FIELD(D_8219A5A0, u16 *, 0x2C);
    M2C_FIELD(D_8219A5A0, s32 *, 0x38) = 0;
    M2C_FIELD(sp20, s16 *, 0x32) = 0;
    M2C_FIELD(sp1C, s16 *, 0x32) = 0;
    if (M2C_FIELD(D_8219A5A0, s32 *, 0x1C) == 9) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x44) = 0xA;
    }
    func_82133868(saved);
    M2C_FIELD(D_8219A5A0, u16 *, 0x2C) = saved;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82133868; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82133868.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821339CC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821339CC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82133A44; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82133A44.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82133AD8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82133AD8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82133B6C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82133B6C.s")
#endif
