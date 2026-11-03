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

void func_82132E20(void);
void func_821336E4(UNUSED s32 arg0);

void func_82132E20(void) {
}

void func_821247F0(s32, s32);
void func_82124810(s32, s32);
void func_82124830(s32, s32);
void func_82124874(s32, s32);

void func_82132E28(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {
        case 0:
            func_821247F0(arg1, arg0);
            break;
        case 1:
            func_82124810(arg1, arg0);
            break;
        case 2:
            func_82124830(arg1, arg0);
            break;
        case 3:
            func_82124874(arg1, arg0);
            break;
    }
}

void func_82107D24(s32, Vec3f*);
void func_8212254C(s32, s32, Vec3f, s32, s32, f32, f32);
void func_82122628(s32, Vec3f, s32, s32, f32, f32);
void func_82132EB4(s32 arg0, s32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5) {
    func_82107D24(arg1, &sBattleScene.scene->unk_D0);
    func_8212254C(arg1, arg0, sBattleScene.scene->unk_D0, 0, 0x4000, arg3, 0.0f);
    func_82122628(arg0, sBattleScene.scene->unk_D0, arg4, arg5, arg2, 0.0f);
}

extern s16 D_8219A4F0[];
extern s8* D_8219A590;
void func_82124984(s8* arg0, CameraNode* arg1, s32 arg2);

void func_82132F88(CameraNode* arg0) {
    D_8219A4F0[0xE] = 0;
    D_8219A4F0[0xD] = 0;
    BattleScene_SetCameraClipPlanes(arg0, 20.0f, 4000.0f);
    BattleScene_ResetCameraFrameCounter();
    sBattleScene.scene->unk_2C = 0;
    D_8219A590 = (s8*)sActivePokemon[sBattleScene.scene->unk_2C];
    func_82124984(D_8219A590, arg0, 3);
    Battle_SetStageScale(0.0f);
    sBattleScene.scene->unk_20++;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82133028; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82133028.s")
#endif

M2C_UNK func_82133028();                            /* extern */
extern s8 *D_8219A5A0;

void func_82133318(void) {
    func_82133028();
    M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
}

M2C_UNK func_82135E80(CameraNode*, s8*);
extern s16 D_8219A50C;
M2C_UNK func_80019B28(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32);
s32 func_821217DC(M2C_UNK);
extern u8 D_8219A594;
extern u8 D_8219A4F4;
s16 func_8000F1FC(s16, M2C_UNK, M2C_UNK, M2C_UNK);
void func_800414B0(s32, s32, s32, s32);
void func_82104C68(s8*, s32);
void func_8213334C(CameraNode* arg0) {
    D_8219A594 = func_8000F1FC(D_8219A594, 0xFF, 0x1E, 0x1E);
    func_80019B28(D_8219A590, 0, 0, 0, 0xFF - D_8219A594);
    switch (*(u16*)&D_8219A50C) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            if (func_821217DC(0x28) != 0) {
                M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
            }
            break;
        case 5:
            func_82135E80(arg0, D_8219A590);
            if (D_8219A5A0[1] == 4) {
                func_800414B0(0, 0x38, 9, 0);
                D_8219A4F4 = 1;
                func_82104C68(D_8219A590, 0x14);
                M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
            }
            break;
    }
}

/*
 * func_8213346C
 *
 * Entry 3 of the 7-way dispatch in func_821336EC (see its comment).  Its
 * argument is typed CameraNode* in this file.  Sets D_8219A594 (a byte) to
 * 0xFF, then:
 *   - if D_8219A50C == 5: calls func_82135E80(arg0, D_8219A590); if the
 *     upper halfword of the word at offset 0x48 of the object
 *     D_8219A590 points to is 0x26, calls func_8003FE58(0x38, 9, 0); and if
 *     func_821217DC(0x37) returns non-zero, sets the word at offset 0x40
 *     of the object D_8219A5A0 points to to 3, calls func_80006998(0xFFFF),
 *     func_80005C4C(4) and func_80040738(), and sets the word at offset
 *     0x20 of that object to 6;
 *   - otherwise adds 1 to that word at offset 0x20.
 *
 * The second argument of func_82135E80 is D_8219A590; the first is
 * `arg0` passed straight through (the retail code loads it into $a1 and
 * leaves $a0 untouched).  What these values mean is not established.
 */
M2C_UNK func_80005C4C(M2C_UNK);
M2C_UNK func_80006998(M2C_UNK);
M2C_UNK func_8003FE58(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80040738();
s32 func_821217DC(M2C_UNK);
M2C_UNK func_82135E80(CameraNode*, s8*);
extern s16 D_8219A50C;
extern u8 D_8219A594;

void func_8213346C(CameraNode* arg0) {
    D_8219A594 = 0xFF;
    if (D_8219A50C == 5) {
        func_82135E80(arg0, D_8219A590);
        if (((s32) M2C_FIELD(D_8219A590, s32 *, 0x48) >> 0x10) == 0x26) {
            func_8003FE58(0x38, 9, 0);
        }
        if (func_821217DC(0x37) != 0) {
            M2C_FIELD(D_8219A5A0, s32 *, 0x40) = 3;
            func_80006998(0xFFFF);
            func_80005C4C(4);
            func_80040738();
            M2C_FIELD(D_8219A5A0, s32 *, 0x20) = 6;
        }
    } else {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_82133534; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82133534.s")
#endif

M2C_UNK func_80019B28(s8 *, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_821088BC(s8 *);                      /* extern */
M2C_UNK func_82133028(s32);                         /* extern */
M2C_UNK func_8213B31C(M2C_UNK);                     /* extern */
extern s8 *D_8219A590;
extern u8 D_8219A594;
extern s8 *D_8219A5A0;

void func_82133640(s32 arg0) {
    u8 *temp_v0;

    if (*M2C_FIELD(D_8219A590, u8 **, 0x85C) & 0x10) {
        func_8213B31C(2);
        temp_v0 = M2C_FIELD(D_8219A590, u8 **, 0x85C);
        *temp_v0 &= 0xFF6F;
        func_821088BC(D_8219A590);
        func_82133028(arg0);
        func_80019B28(D_8219A590, 0, 0, 0, 0xFF);
        D_8219A594 = 0;
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = 2;
    }
}

void func_821336E4(UNUSED s32 arg0) {
}

/*
 * func_821336EC
 *
 * Dispatches one tick of the "faint after residual damage" phase of a
 * battle scene by the scene's step counter (sBattleScene.scene->unk_20, 0..6):
 *   0 func_82132F88   1 func_82133318   2 func_8213334C   3 func_8213346C
 *   4 func_82133534   5 func_82133640   6 func_821336E4
 * Any other step does nothing.  The camera node arg0 is passed through to
 * the step functions in the register a0 untouched.
 *
 * Same switch as BattleScene_PhaseFaintAfterResidualDamage in the Stadium 1
 * decomp (steps begin, animate, advance/finish camera close, complete,
 * no-op, alternate animation).
 */
void func_8213334C(CameraNode* arg0);
void func_8213346C(CameraNode* arg0);
void func_82133534(CameraNode* arg0);

void func_821336EC(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_82132F88(arg0);
            break;

        case 1:
            func_82133318();
            break;

        case 2:
            func_8213334C(arg0);
            break;

        case 3:
            func_8213346C(arg0);
            break;

        case 4:
            func_82133534(arg0);
            break;

        case 5:
            func_82133640((s32)arg0);
            break;

        case 6:
            func_821336E4((s32)arg0);
            break;
    }
}
