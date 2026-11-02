/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_343BA0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gallery.h"
#include "gfx_buffer.h"
#include "math.h"
#include "math_util.h"
extern u8* sBattleAnimAssetPointers[256];
extern s16 sBattleAnimResourceList[0x10];
extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];
extern s16 D_8219CAC0;
extern s16 D_8219CAC2;
extern Mtx D_8219CAC8;
extern s16 D_8219CB08;
extern s16 D_8219CB0A;
extern s16 D_8219CB0C;
extern s16 D_8219CB0E;
extern s16 D_8219CB10;
extern s16 D_8219CB12;
extern s16 D_8219CB14;
extern s16 D_8219CB16;
extern s16 D_8219CB18;
extern s16 D_8219CB1A;
extern const char D_821978C8[];

#include "m2c_macros.h"

void func_821329F0(void);

void func_821329F0(void) {
}

M2C_UNK func_80006998(M2C_UNK);                     /* extern */
M2C_UNK func_8212188C();                            /* extern */
M2C_UNK func_82121D78(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK func_82124984(s8 *, s32, M2C_UNK);        /* extern */
M2C_UNK func_82136918(s32, M2C_UNK);                /* extern */
extern s8 *D_82199DE0;
extern s8 *D_8219A580;
extern s8 *D_8219A5A0;

void func_821329F8(s32 arg0) {
    s8 *sp1C;

    sp1C = D_82199DE0 + 0x78C;
    M2C_FIELD(D_8219A5A0, s32 *, 0x50) = 0;
    func_82121D78(arg0, 0x41A00000, 0x457A0000);
    func_8212188C();
    M2C_FIELD(D_8219A5A0, u16 *, 0x2C) = 0U;
    D_8219A580 = (&D_82199DE0)[M2C_FIELD(D_8219A5A0, u16 *, 0x2C)];
    M2C_FIELD(sp1C, s32 *, 8) = 0;
    func_82124984(D_8219A580, arg0, 3);
    func_82136918(M2C_FIELD(D_8219A580, s32 *, 0x85C), 9);
    func_80006998(0);
    M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
}

s32 func_82101FD4(s32);                             /* extern */
extern s8 *D_8219A5A0;

void func_82132AC4(s32 arg0) {
    if (func_82101FD4(D_8219A580) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

/*
 * func_82132B04
 *
 * Clears the byte at D_8219A4F1, calls func_821351F8(arg0, D_8219A580) and
 * func_82104C68(D_8219A580, 1), then adds 1 to the word at offset 0x20 of the
 * structure that D_8219A5A0 points to.  That word is advanced by neighbouring
 * functions in this file in the same way (see func_82132AC4), so it looks
 * like a step counter, but this is not established from the code alone.
 */
extern s8 D_8219A4F1;
void func_821351F8(CameraNode* arg0, s8* arg1);
void func_82104C68(s8* arg0, s32 arg1);

void func_82132B04(CameraNode* arg0) {
    D_8219A4F1 = 0;
    func_821351F8(arg0, D_8219A580);
    func_82104C68(D_8219A580, 1);
    M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
}

/*
 * func_82132B54
 *
 * Calls func_82135894(arg0, D_8219A580).  If that returns non-zero, adds 1
 * to the word at offset 0x20 of the structure that D_8219A5A0 points to.
 * func_82132AC4, just above, is the same pattern with func_82101FD4 and a
 * single argument.  What the counter at +0x20 counts is not established
 * from the code alone.
 */
s32 func_82135894(CameraNode* arg0, s8* arg1);

void func_82132B54(CameraNode* arg0) {
    if (func_82135894(arg0, D_8219A580) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

M2C_UNK func_80006998(M2C_UNK);
s32 func_80005B98(s32);
/*
 * func_82132B90
 *
 * Looks at the word at offset 8 of the state block (D_8219A580 + 0x78C, i.e.
 * ActivePokemonState::rosterIndex).  If rosterIndex + 1 is 6 or more as an
 * unsigned value (rosterIndex outside -1..4), it writes 3 to offset 0x40 and 7
 * to offset 0x20 of the structure D_8219A5A0 points to and returns.
 * Otherwise it calls func_80006998(0) and func_80005B98(5) and adds 1 to the
 * word at offset 0x20, the same step counter that func_82132AC4 and
 * func_82132B04 advance.  What the two values written in the first case mean
 * is not established from the code alone.
 * Note: the local "st" is only there to reproduce the retail register use;
 * the ROM also computes D_8219A580 + 0x78C in a branch delay slot.
 */
void func_82132B90(CameraNode* arg0) {
    s8* st = D_8219A580 + 0x78C;
    if ((u32)(M2C_FIELD(st, s32*, 8) + 1) >= 6U) {
        M2C_FIELD(D_8219A5A0, s32*, 0x40) = 3;
        M2C_FIELD(D_8219A5A0, s32*, 0x20) = 7;
        return;
    }
    func_80006998(0);
    func_80005B98(5);
    M2C_FIELD(D_8219A5A0, s32*, 0x20) = (s32)(M2C_FIELD(D_8219A5A0, s32*, 0x20) + 1);
}

s32 func_821217DC(s32);
/*
 * func_82132C14
 *
 * Once func_821217DC(0xA) returns non-zero it advances the roster index of the
 * Pokemon in D_8219A580 (state.rosterIndex) by one and makes that roster entry
 * the current one in the session teams block: sessionTeams->displayModel gets
 * the first byte of the new entry, sessionTeams->unk_04 is pointed at the entry
 * itself, and bit 0x80 is set in sessionTeams->uniqueStatusFlags.  It then adds
 * 1 to the word at offset 0x20 of the structure D_8219A5A0 points to, the same
 * step counter that func_82132AC4 and func_82132B04 advance.
 * The meaning of the entry's first byte and of flag 0x80 is not established
 * here.  Notes: the casts of D_8219A580 repeat because the ROM re-reads the
 * global for each statement, and "mon" is only used for the first read (the ROM
 * keeps its address in a register); arg0 is unused.
 */
void func_82132C14(UNUSED CameraNode* arg0) {
    ActivePokemonState* st = &((ActivePokemon*)D_8219A580)->state;
    BattleMon* mon;

    if (func_821217DC(0xA) != 0) {
        st->rosterIndex++;
        mon = &((ActivePokemon*)D_8219A580)->teamRoster->pokemonPicked[st->rosterIndex];
        ((ActivePokemon*)D_8219A580)->sessionTeams->displayModel = mon->unk_00.unk_00;
        ((ActivePokemon*)D_8219A580)->sessionTeams->unk_04 = (TeamRoster*)&((ActivePokemon*)D_8219A580)->teamRoster->pokemonPicked[st->rosterIndex];
        ((ActivePokemon*)D_8219A580)->sessionTeams->uniqueStatusFlags |= 0x80;
        M2C_FIELD(D_8219A5A0, s32*, 0x20) = M2C_FIELD(D_8219A5A0, s32*, 0x20) + 1;
    }
}

/*
 * func_82132CDC
 *
 * Case 6 of the scene-state switch in func_82132D60. The word at
 * D_8219A580 + 0x85C is a pointer to a flag byte. If bit 0x10 of that byte is
 * set, the code clears bits 0x10 and 0x80 in it (the mask is 0xFF6F), calls
 * func_821088BC with D_8219A580, calls func_80005B98(0xF), and sets the word
 * at D_8219A5A0 + 0x20 to 2. D_8219A5A0 is the address of sBattleScene, whose
 * first member is `scene`, so that word is sBattleScene.scene->unk_20, the
 * field func_82132D60 switches on. The argument is not used. What the flag bits and the
 * two calls mean is not established from this function.
 */
void func_82132CDC(CameraNode* arg0) {
    u8* flags;

    flags = M2C_FIELD(D_8219A580, u8**, 0x85C);
    if (*flags & 0x10) {
        *flags &= 0xFF6F;
        func_821088BC(D_8219A580);
        func_80005B98(0xF);
        M2C_FIELD(D_8219A5A0, s32*, 0x20) = 2;
    }
}

// Zero's version takes only the particle; the header keeps Stadium 1's callback signature.
void func_82132D3C(Particle* arg0) {
    BattleAnim_DrawI4AtlasYScaled(arg0, D_8219A580);
}

void func_82132B04(CameraNode* arg0);
void func_82132B54(CameraNode* arg0);
void func_82132B90(CameraNode* arg0);
void func_82132C14(CameraNode* arg0);
void func_82132CDC(CameraNode* arg0);

void func_82132D60(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_821329F8((s32)arg0);
            break;
        case 1:
            func_82132AC4((s32)arg0);
            break;
        case 2:
            func_82132B04(arg0);
            break;
        case 3:
            func_82132B54(arg0);
            break;
        case 4:
            func_82132B90(arg0);
            break;
        case 5:
            func_82132C14(arg0);
            break;
        case 6:
            func_82132CDC(arg0);
            break;
        case 7:
            func_82132D3C((Particle*)arg0);
            break;
    }
}
