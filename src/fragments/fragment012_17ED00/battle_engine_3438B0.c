/* Stadium Zero fragment012_17ED00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_3438B0.c. */

#include "fragments/battle_engine/battle_engine.h"
#include "gfx_buffer.h"

#include "m2c_macros.h"

void func_8211F034(s32, s32);
extern s32 D_8219A520;

void BattleAnim_RenderNop1(void);
void BattleAnim_RenderNop2(void);

void BattleAnim_RenderNop1(void) {
}

void BattleAnim_RenderNop2(void) {
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
extern ActivePokemon* D_8219A540;
extern s32 D_8219A544;
extern s32 D_8219A560;
extern s32 D_8219A564;
extern s32 D_8219A570;
extern s32 D_8219A578;
extern u8* D_82189180[];
typedef struct Cue8212B270 {
    /* 0x00 */ u8 unk_00[6];
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07[3];
    /* 0x0A */ u8 unk_0A;
} Cue8212B270; // size = 0xB
s32 func_82107A5C(ActivePokemon*);
void func_8212A554(void*);
void func_82124A40(void);
void func_82121EB0(ActivePokemon*);
void func_82104C68(ActivePokemon*, s32);
void func_8212A768(ActivePokemon*, CameraNode*, void*);
void func_82124E80(void);
void func_82135098(ActivePokemon*);
void func_8212239C(ActivePokemon*, CameraNode*);
s32 func_82122DFC(CameraNode*, ActivePokemon*);
void func_82110B44(ActivePokemon*);
void func_8212A4A4(s32);
void func_821061A8(ActivePokemon*);
void func_80040738(void);
s32 func_8210F31C(ActivePokemon*);
s32 func_82105C8C(ActivePokemon*, s32);
s32 func_82124BF8(ActivePokemon*);
void func_8212A4CC(CameraNode*, s32*, s32*);
void func_8212B270(CameraNode* arg0, void* arg1) {
    u8* sp24 = (u8*)D_8219A544 + 0x7C6;
    Cue8212B270* temp_v1 = (sp24[0x5A] - 1) + (Cue8212B270*)D_82189180[func_82107A5C(D_8219A540)];
    volatile s32 sp1C;

    if (M2C_FIELD(D_8219A540, s16*, 0x1A) == 0x98) {
        sp1C = 0xF;
    } else if (temp_v1->unk_0A == 0xFF) {
        sp1C = M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x44), u16*, 0xA) - temp_v1->unk_06;
    } else {
        sp1C = temp_v1->unk_0A - temp_v1->unk_06;
    }

    switch (sBattleScene.scene->unk_3C) {
        case 0:
            func_8212A554(arg1);
            func_82124A40();
            func_82121EB0(D_8219A540);
            func_82104C68((ActivePokemon*)D_8219A544, 4);
            func_8212A768(D_8219A540, arg0, (void*)D_8219A570);
            D_8219A570--;
            if (D_8219A570 < 0) {
                func_82124E80();
                func_82135098(D_8219A540);
                func_8212A768(D_8219A540, arg0, (void*)D_8219A570);
                func_8212239C(D_8219A540, arg0);
                func_82122DFC(arg0, D_8219A540);
                func_82110B44(D_8219A540);
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->unk_3C = 2;
                D_8219A578 = 0;
                func_8212A4A4(D_8219A520 + 0x148);
                if (M2C_FIELD(D_8219A520, s8*, 0x149) != 0) {
                    D_8219A578 = 1;
                }
                func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->unk_2C);
                func_821061A8(D_8219A540);
            } else {
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(sp1C) != 0) {
                func_80040738();
                BattleAnim_CleanupEffects(1);
                sBattleScene.scene->unk_3C = 0;
            }
            break;

        case 2:
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
                func_8211F034(D_8219A520 + 0x308, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 3:
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 4:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (D_8219A578 == 0) {
                func_8212A4A4(D_8219A520 + 0x88);
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                func_8212A4A4(D_8219A520 + 0x88);
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 5:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (D_8219A578 == 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8212A4A4(D_8219A520 + 0x208);
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8212A4A4(D_8219A520 + 0x208);
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 6:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sp24, u16*, 0xC) != 0) {
                if (func_82105C8C(D_8219A540, 0xF) != 0) {
                    sBattleScene.scene->unk_3C++;
                }
                if (func_82122DFC(arg0, D_8219A540) != 0) {
                    sBattleScene.scene->unk_3C = 8;
                }
            } else if ((func_82122DFC(arg0, D_8219A540) != 0) && (BattleScene_AdvanceCameraFrameCounterUntil(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->unk_3C = 9;
            }
            break;

        case 7:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (func_82122DFC(arg0, D_8219A540) != 0) {
                sBattleScene.scene->unk_3C = 9;
            }
            break;

        case 8:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (func_82105C8C(D_8219A540, 0xF) != 0) {
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 9:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (M2C_FIELD(D_8219A520, s8*, 0x3C9) == 0) {
                sBattleScene.scene->unk_3C = 0xB;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x3C8, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 10:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->unk_3C++;
                Battle_ClearMessageCursor();
            }
            break;

        case 11:
            if (func_82124BF8(D_8219A540) == 0) {
                D_8219A560 = func_8210F31C(D_8219A540);
                D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
                func_82122DFC(arg0, D_8219A540);
                func_8212A4CC(arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212B270.s")
#endif

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_82110B44(ActivePokemon*);
extern ActivePokemon* D_8219A540;
extern s32 D_8219A544;
extern s32 D_8219A560;
extern s32 D_8219A564;
void func_82135098(ActivePokemon*);
void func_8212A554(void*);
void func_82124A40(void);
void func_8212A4A4(s32);
void func_8212A768(ActivePokemon*, CameraNode*, void*);
void func_8212239C(ActivePokemon*, CameraNode*);
void func_82104C68(ActivePokemon*, s32);
void func_82124E80(void);
s32 func_8210F31C(ActivePokemon*);
s32 func_82122DFC(CameraNode*, ActivePokemon*);
s32 func_82105C8C(ActivePokemon*, s32);
s32 func_82124BF8(ActivePokemon*);
void func_8212A4CC(CameraNode*, s32*, s32*);
void func_8212BA28(CameraNode* arg0, void* arg1) {

    u8* sp1C = (u8*)D_8219A540 + 0x7C6;

    switch (sBattleScene.scene->unk_3C) {
        case 0:
            func_82135098(D_8219A540);
            func_8212A554(arg1);
            func_82124A40();
            BattleScene_ResetCameraFrameCounter();
            func_82110B44(D_8219A540);
            func_8212A4A4(D_8219A520 + 0x148);
            func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->unk_2C);
            func_8212A768(D_8219A540, arg0, arg1);
            func_8212239C(D_8219A540, arg0);
            func_82104C68((ActivePokemon*)D_8219A544, 0xB);
            sBattleScene.scene->unk_3C++;
            break;

        case 1:
            func_82124E80();
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 2:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                BattleScene_ResetCameraSubstepCounter();
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 3:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sp1C, u16*, 0xC) != 0) {
                if (func_82105C8C(D_8219A540, 0xF) != 0) {
                    sBattleScene.scene->unk_3C++;
                }
                if (func_82122DFC(arg0, D_8219A540) != 0) {
                    sBattleScene.scene->unk_3C = 5;
                }
            } else if ((func_82122DFC(arg0, D_8219A540) != 0) && (BattleScene_AdvanceCameraFrameCounterUntil(0x14) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->unk_3C = 6;
            }
            break;

        case 4:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (func_82122DFC(arg0, D_8219A540) != 0) {
                sBattleScene.scene->unk_3C = 6;
            }
            break;

        case 5:
            if (BattleScene_AdvanceCameraSubstepCounter(0x1E) != 0) {
                Battle_ClearMessageCursor();
            }
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            func_82122DFC(arg0, D_8219A540);
            if (func_82105C8C(D_8219A540, 0xF) != 0) {
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 6:
            if (M2C_FIELD(D_8219A520, s8*, 0x3C9) == 0) {
                sBattleScene.scene->unk_3C = 8;
            } else if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                D_8219A560 = func_8210F31C(D_8219A540);
                D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x3C8, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_3C++;
            }
            break;

        case 7:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x1E) != 0) {
                sBattleScene.scene->unk_3C++;
                Battle_ClearMessageCursor();
            }
            break;

        case 8:
            if (func_82124BF8(D_8219A540) == 0) {
                D_8219A560 = func_8210F31C(D_8219A540);
                D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
                func_82122DFC(arg0, D_8219A540);
                func_8212A4CC(arg0, &D_8219A560, &D_8219A564);
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212BA28.s")
#endif

void func_821255EC(CameraNode*);
void func_82110B44(ActivePokemon*);
void func_8212A850(CameraNode*, void*);
void func_8212AD10(CameraNode*, void*);
void func_8212B270(CameraNode*, void*);
void func_8212BA28(CameraNode*, void*);

void func_8212BF28(CameraNode* arg0, void* arg1) {
    s32 other;

    func_821255EC(arg0);
    sBattleScene.scene->unk_50 = 2;
    other = sBattleScene.scene->unk_2C == 0;
    func_82110B44(sActivePokemon[other]);
    if (sBattleScene.scene->unk_1A == 3) {
        func_8212BA28(arg0, arg1);
    } else if (sBattleScene.scene->unk_1A == 1) {
        func_8212B270(arg0, arg1);
    } else if (sBattleScene.scene->unk_1A == 2) {
        func_8212AD10(arg0, arg1);
    } else {
        func_8212A850(arg0, arg1);
    }
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
extern u8* D_8218B2F4[];
extern u8 D_8219A4F4;
extern u8 D_80073D84[];
void func_82128CDC(CameraNode*, s32);
void func_82128F2C(CameraNode*, s32);
void func_82129AE8(CameraNode*, s32);
void func_8212A328(CameraNode*, s32);
void func_8212BFF0(CameraNode* arg0) {
    s32 n = 10;
    u8* sp = (u8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x7C6;

    if (sBattleScene.scene->unk_1C == n) {
        switch (sBattleScene.scene->unk_20) {
            case 0:
                func_82128CDC(arg0, D_8218B2F4[D_8219A4F4][0]);
                break;
            case 1:
                func_82128F2C(arg0, 0);
                break;
            case 2:
                func_82129AE8(arg0, D_8218B2F4[D_8219A4F4][1]);
                break;
            case 3:
                func_8212A328(arg0, D_8218B2F4[D_8219A4F4][2]);
                break;
            case 4:
                func_8212BF28(arg0, (void*)D_8218B2F4[D_8219A4F4][3]);
                break;
        }
    } else {
        switch (sBattleScene.scene->unk_20) {
            case 0:
                func_82128CDC(arg0, *(u16*)(D_80073D84 + 2 + sp[0x5A] * n));
                break;
            case 1:
                func_82128F2C(arg0, 0);
                break;
            case 2:
                func_82129AE8(arg0, *(u16*)(D_80073D84 + 4 + sp[0x5A] * n));
                break;
            case 3:
                func_8212A328(arg0, *(u16*)(D_80073D84 + 6 + sp[0x5A] * n));
                break;
            case 4:
                func_8212BF28(arg0, (void*)*(u16*)(D_80073D84 + 8 + sp[0x5A] * n));
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212BFF0.s")
#endif

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
extern u8* D_8218B320[];
void func_8212C1C4(CameraNode* arg0) {
    s32 n = 10;
    u8* sp = (u8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x7C6;

    if (sBattleScene.scene->unk_1C == n) {
        switch (sBattleScene.scene->unk_20) {
            case 0:
                func_82128CDC(arg0, D_8218B320[D_8219A4F4][0]);
                break;
            case 1:
                func_82128F2C(arg0, 0);
                break;
            case 2:
                func_82129AE8(arg0, D_8218B320[D_8219A4F4][1]);
                break;
            case 3:
                func_8212A328(arg0, D_8218B320[D_8219A4F4][2]);
                break;
            case 4:
                func_8212BF28(arg0, (void*)D_8218B320[D_8219A4F4][3]);
                break;
        }
    } else {
        switch (sBattleScene.scene->unk_20) {
            case 0:
                func_82128CDC(arg0, *(u16*)(D_80073D84 + 2 + sp[0x5A] * n));
                break;
            case 1:
                func_82128F2C(arg0, 0);
                break;
            case 2:
                func_82129AE8(arg0, *(u16*)(D_80073D84 + 4 + sp[0x5A] * n));
                break;
            case 3:
                func_8212A328(arg0, *(u16*)(D_80073D84 + 6 + sp[0x5A] * n));
                break;
            case 4:
                func_8212BF28(arg0, (void*)*(u16*)(D_80073D84 + 8 + sp[0x5A] * n));
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212C1C4.s")
#endif

s32 func_8210C020(M2C_UNK, s32);                    /* extern */
void func_82124984(s32, s32, s32);
extern s32 D_8219A544;
extern s32 D_8219A568;
void func_8212C398(s32 arg0)
{
  s32 temp_v0;
  s32 var_v1;
 temp_v0 = func_8210C020(3, arg0); D_8219A568 = temp_v0; var_v1 = temp_v0; if (temp_v0 >= 4) { D_8219A568 = 0 ^ 0; var_v1 = 0; } switch (var_v1) { case 0:
      func_82124984(D_8219A544, arg0, 0);
      return;

    case 1:
      func_82124984(D_8219A544, arg0, 1);
      return;

    case 2:
      func_82124984(D_8219A544, arg0, 2);
      return;

    default:
      func_82124984(D_8219A544, arg0, 0);
      return;

  }

}

s32 func_8210C020(M2C_UNK, s32);                    /* extern */
void func_82124984(s32, s32, s32);
extern s32 D_8219A544;
extern s32 D_8219A568;
void func_8212C454(s32 arg0)
{
  s32 temp_v0;
  s32 var_v1;
 temp_v0 = func_8210C020(4, arg0); D_8219A568 = temp_v0;
  var_v1 = temp_v0;
  if (temp_v0 >= 5)
  {
    D_8219A568 = 0;
    var_v1 = 0;
  }
  switch (var_v1)
  {
    case 0:
      func_82124984(D_8219A544, arg0, 0);
      return;

    case 1:
      func_82124984(D_8219A544, arg0, 1);
      return;

    case 2:
      func_82124984(D_8219A544, arg0, 2);
      return;

    case 3:
      func_82124984(D_8219A544, arg0, 3);
      return;

    default:
      func_82124984(D_8219A544, arg0, 0);
      return;

  }

}

s32 func_8210C020(M2C_UNK, s32);                    /* extern */
void func_82124984(s32, s32, s32);
extern s32 D_8219A544;
extern s32 D_8219A568;
void func_8212C530(s32 arg0)
{
  s32 temp_v0;
  s32 var_v1;
 do { temp_v0 = func_8210C020(4, arg0); D_8219A568 = temp_v0; var_v1 = temp_v0 & 0xFFFFFFFFFFFFFFFF; } while (0);
  if (temp_v0 >= 5)
  {
    D_8219A568 = 0;
    var_v1 = 0;
  }
  switch (var_v1)
  {
    case 0:
      func_82124984(D_8219A544, arg0, 0);
      return;

    case 1:
      func_82124984(D_8219A544, arg0, 1);
      return;

    case 2:
      func_82124984(D_8219A544, arg0, 2);
      return;

    case 3:
      func_82124984(D_8219A544, arg0, 4);
      return;

    default:
      func_82124984(D_8219A544, arg0, 0);
      return;

  }

}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_8212C60C(s32 arg0, s32 arg1) {
    switch (arg1) {
        case 0:
            func_82124984(D_8219A544, arg0, 0);
            break;
        case 1:
            func_82124984(D_8219A544, arg0, 1);
            break;
        case 2:
            func_82124984(D_8219A544, arg0, 2);
            break;
        case 3:
            func_82124984(D_8219A544, arg0, 3);
            break;
        case 4:
            func_82124984(D_8219A544, arg0, 4);
            break;
        default:
            func_82124984(D_8219A544, arg0, 0);
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212C60C.s")
#endif

void func_821247F0(void*, void*);
s32 func_82124810(void*, void*);
void func_82124830(void*, void*);
void func_82124874(void*, void*);

void func_8212C6E8(ActivePokemon* arg0, CameraNode* arg1, s32 arg2) {
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
        default:
            func_82124874(arg1, arg0);
            break;
    }
}

typedef struct MoveAnimInfoZ {
    /* 0x00 */ u8 pad00[2];
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u8 pad04[2];
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u8 pad08[2];
} MoveAnimInfoZ; // size = 0xA
extern MoveAnimInfoZ D_80073D90[];
void func_8212C60C(s32, s32);

void func_8212C78C(s32 arg0) {
    BattleMonRuntime* runtime;

    runtime = &((ActivePokemon*)D_8219A544)->state.runtime;
    M2C_FIELD(sBattleScene.scene, s32*, 0x54) = 0;
    if (D_80073D90[runtime->usedMove - 1].unk_02 == 5) {
        func_8212C398(arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_02 == 6) {
        func_8212C454(arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_02 == 7) {
        func_8212C530(arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_02 == 4) {
        M2C_FIELD(sBattleScene.scene, s32*, 0x54) = 1;
        func_8212C60C(arg0, D_80073D90[runtime->usedMove - 1].unk_02);
    } else {
        func_8212C60C(arg0, D_80073D90[runtime->usedMove - 1].unk_02);
    }
}

void func_821255B4(CameraNode*);
void func_8212239C(ActivePokemon*, CameraNode*);
void func_82110B44(ActivePokemon*);
void func_8211F034(s32, s32);
void func_8212C78C(s32);
extern s32 D_8219A560;
extern s32 D_8219A564;
extern ActivePokemon* D_8219A540;
s32 func_8210F31C(ActivePokemon*);
void func_82125C80(CameraNode*);
void func_82104C68(ActivePokemon*, s32);
s32 func_82105724(ActivePokemon*, s32);
void func_82105E64(ActivePokemon*);
void func_82122B9C(CameraNode*, ActivePokemon*);
void func_8212C874(CameraNode* arg0) {
    sBattleScene.scene->unk_50 = 4;
    switch (sBattleScene.scene->unk_20) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 5) != 0) {
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                func_8212C78C((s32)arg0);
                func_8212239C((ActivePokemon*)D_8219A544, arg0);
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->unk_20++;
            }
            break;

        case 1:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x23) != 0) {
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 2:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (sBattleScene.scene->unk_14 == 0x37) {
                Battle_ClearMessageCursor();
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x3C) != 0) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 3:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->unk_34 = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_80040738(void);
void func_82135098(ActivePokemon*);
void func_821255B4(CameraNode*);
void func_82105E64(ActivePokemon*);
void func_8212C6E8(ActivePokemon*, CameraNode*, s32);
void func_82122A7C(CameraNode*, ActivePokemon*);
void func_82124A40(void);
void func_8212CB58(CameraNode* arg0) {
    u8* sp1C = (u8*)D_8219A540 + 0x7C6;

    switch (sBattleScene.scene->unk_20) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 5) != 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                func_82135098(D_8219A540);
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                func_8212C78C((s32)arg0);
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetCameraSubstepCounter();
                sBattleScene.scene->unk_20++;
            }
            break;

        case 1:
            if (sBattleScene.scene->unk_14 == 0x46) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x6E) != 0) {
                BattleAnim_CleanupEffects(1);
                func_80040738();
                func_8211F034(D_8219A520 + 0x148, !sBattleScene.scene->unk_2C);
                func_8212C6E8(D_8219A540, arg0, BattleAnim_RandomRange(2));
                func_8212239C(D_8219A540, arg0);
                func_82104C68((ActivePokemon*)D_8219A544, 4);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 2:
            func_82122A7C(arg0, D_8219A540);
            if (sBattleScene.scene->unk_14 == 0x28) {
                Battle_ClearMessageCursor();
                func_8211F034(D_8219A520 + 0x88, !sBattleScene.scene->unk_2C);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (BattleScene_AdvanceCameraFrameCounter(0x50) != 0) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 3:
            func_82122A7C(arg0, D_8219A540);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if ((D_8219A564 == 1) && (D_8219A560 == 1)) {
                if (M2C_FIELD(sp1C, u16*, 0xC) != 0) {
                    BattleAnim_CleanupEffects(1);
                    func_82135098((ActivePokemon*)D_8219A544);
                    func_80040738();
                    func_82124984(D_8219A544, (s32)arg0, 3);
                    sBattleScene.scene->unk_20++;
                } else {
                    func_82135098(D_8219A540);
                    if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                        sBattleScene.scene->unk_34 = 3;
                    }
                    BattleScene_ResetCameraFrameCounter();
                    func_82124A40();
                    BattleScene_SetPhase(arg0, 5);
                }
            }
            break;

        case 4:
            func_82122A7C(arg0, D_8219A540);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->unk_34 = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            func_82124A40();
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212CB58.s")
#endif

M2C_UNK func_8211EE8C();
extern s32 D_8219A560;
extern s32 D_8219A564;
extern ActivePokemon* D_8219A540;
s32 func_8210F31C(ActivePokemon*);
s32 func_82105724(ActivePokemon*, s32);
void func_821255B4(CameraNode*);
void func_82125C80(CameraNode*);
void func_82105E64(ActivePokemon*);
void func_8212CF90(CameraNode* arg0) {
    M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 4;

    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_821255B4(arg0);
            func_82124984(D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0xA) != 0) {
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 1:
            func_82124984(D_8219A544, arg0, 3);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 2:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x14) == 0x37) {
                func_8211EE8C();
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 3:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->unk_34 = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_82124A40(void);
void func_82135098(ActivePokemon*);
void func_82125C80(CameraNode*);
s32 func_8210F31C(ActivePokemon*);
void func_82122B9C(CameraNode*, ActivePokemon*);
void func_821255B4(CameraNode*);
void func_8212239C(ActivePokemon*, CameraNode*);
void func_82110B44(ActivePokemon*);
void func_8212D194(CameraNode* arg0) {

    u8* sp24 = (u8*)D_8219A544 + 0x78C;

    switch (sBattleScene.scene->unk_20) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                func_8212C78C((s32)arg0);
                func_8212239C((ActivePokemon*)D_8219A544, arg0);
                BattleScene_ResetCameraFrameCounter();
                func_82104C68((ActivePokemon*)D_8219A544, 3);
                func_82110B44((ActivePokemon*)D_8219A544);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 1:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x64) != 0) {
                sBattleScene.scene->unk_20 = 4;
            }
            if (BattleScene_IsCameraFrameCounterAtLeast(0x1E) != 0) {
                Battle_ClearMessageCursor();
                if (M2C_FIELD(sp24, u16*, 0x36) & 1) {
                    func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                    sBattleScene.scene->unk_20++;
                } else {
                    func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->unk_2C);
                    sBattleScene.scene->unk_20 = 3;
                }
            }
            break;

        case 2:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x64) != 0) {
                sBattleScene.scene->unk_20 = 4;
            }
            if (BattleScene_IsCameraFrameCounterAtLeast(0x3C) != 0) {
                func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 3:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (func_821058E8((ActivePokemon*)D_8219A544, 0x64) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->unk_20++;
            }
            break;

        case 4:
            func_82122B9C(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->unk_34 = 3;
            }
            func_82124A40();
            func_82125C80(arg0);
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212D194.s")
#endif

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
s32 func_821217DC(s32);
void func_821233EC(CameraNode*, ActivePokemon*);
void func_8210881C(ActivePokemon*);
void func_82107408(ActivePokemon*);
void func_82107160(ActivePokemon*);
void func_82101B54(ActivePokemon*, s32);
void func_8003FE58(s32, s32, s32);
void func_82104C68(ActivePokemon*, s32);
s32 func_82105724(ActivePokemon*, s32);
void func_82124A40(void);
void func_82125C34(CameraNode*);
void func_8212D504(CameraNode* arg0) {
    UNUSED s32 pad[3];
    u8* sp30 = (u8*)D_8219A544 + 0x7C6;
    u8* sp2C = (u8*)D_8219A540 + 0x7C6;
    u8* sp28 = (u8*)D_8219A544 + 0x78C;
    u8* sp24 = (u8*)D_8219A540 + 0x78C;

    switch (sBattleScene.scene->unk_20) {
        case 0:
            if (func_821217DC(0x14) != 0) {
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                func_8212C78C((s32)arg0);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 1:
            if (func_821217DC(0x19) != 0) {
                func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->unk_2C);
                func_821233EC(arg0, (ActivePokemon*)D_8219A544);
                if (sp30[0x4D] & 0x10) {
                    if (sp2C[0x4E] & 8) {
                        M2C_FIELD(sp28, s16*, 0xC0) = M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = M2C_FIELD(sp24, s16*, 0xC2);
                    } else if (M2C_FIELD(M2C_FIELD(D_8219A540, u8**, 0x85C), s16*, 2) == 0x98) {
                        M2C_FIELD(sp28, s16*, 0xC0) = M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = sp2C[0xB];
                    } else {
                        M2C_FIELD(sp28, s16*, 0xC0) = M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = M2C_FIELD(M2C_FIELD(D_8219A540, u8**, 0x85C), s16*, 2);
                    }
                } else if (sp2C[0x4E] & 8) {
                    M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = M2C_FIELD(sp24, s16*, 0xC2);
                } else if (M2C_FIELD(M2C_FIELD(D_8219A540, u8**, 0x85C), s16*, 2) == 0x98) {
                    M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = sp2C[0xB];
                } else {
                    M2C_FIELD(M2C_FIELD(D_8219A544, u8**, 0x85C), s16*, 2) = M2C_FIELD(M2C_FIELD(D_8219A540, u8**, 0x85C), s16*, 2);
                }
                *M2C_FIELD(D_8219A544, u8**, 0x85C) |= 0x80;
                sBattleScene.scene->unk_20++;
            }
            break;

        case 2:
            if (*M2C_FIELD(D_8219A544, u8**, 0x85C) & 0x10) {
                *M2C_FIELD(D_8219A544, u8**, 0x85C) &= ~0x90;
                func_8210881C((ActivePokemon*)D_8219A544);
                func_82107408((ActivePokemon*)D_8219A544);
                func_82101B54((ActivePokemon*)D_8219A544, sp30[0x5A]);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 3:
            func_8003FE58(sp30[0x5A], M2C_FIELD(D_8219A544, s16*, 0x1A), 0);
            func_82104C68((ActivePokemon*)D_8219A544, 0x12);
            func_821233EC(arg0, (ActivePokemon*)D_8219A544);
            sBattleScene.scene->unk_20++;
            break;

        case 4:
            M2C_FIELD(D_8219A544, u8**, 0x9CC)[1] |= 1;
            M2C_FIELD(D_8219A544, u8*, 0x865) |= 1;
            func_82107160((ActivePokemon*)D_8219A544);
            func_821233EC(arg0, (ActivePokemon*)D_8219A544);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x32) != 0) {
                func_82124A40();
                func_82125C34(arg0);
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212D504.s")
#endif

void func_82135098(ActivePokemon*);
void func_821255B4(CameraNode*);
void func_821020FC(s8*);
void func_82125C80(CameraNode*);
extern s32 D_8219A560;
extern s32 D_8219A564;
extern ActivePokemon* D_8219A540;
s32 func_8210F31C(ActivePokemon*);
void func_8212D820(CameraNode* arg0) {
    BattleMonRuntime* sp1C = &sActivePokemon[sBattleScene.scene->unk_2C]->state.runtime;
    ActivePokemonState* sp18 = &sActivePokemon[sBattleScene.scene->unk_2C]->state;

    switch (sBattleScene.scene->unk_20) {
        case 0:
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                func_821255B4(arg0);
                BattleAnim_PlayMoveEffectScript((ActivePokemon*)D_8219A544, sp1C->usedMove);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                func_8212C78C((s32)arg0);
                if (sp18->flags & 0x800) {
                    func_821020FC((s8*)D_8219A544);
                }
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 1:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (sp18->flags & 0x800) {
                BattleScene_ResetOwnerModelIfLoaded((ActivePokemon*)D_8219A544);
            }
            if (BattleAnim_IsSessionBusy((ActivePokemon*)D_8219A544) == 0) {
                Battle_ClearRuntimeFlags((ActivePokemon*)D_8219A544, 0x800);
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 2:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            BattleScene_RecenterCameraOnOwner(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (BattleScene_AdvanceCameraFrameCounter(0x46) != 0) {
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 3:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            BattleScene_RecenterCameraOnOwner(arg0, (ActivePokemon*)D_8219A544);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->unk_34 = 3;
            }
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

void func_80042A6C(s32);

/**
 * Camera state machine (sibling of func_8212C874). Sets scene->unk_50 = 4 and switches on
 * scene->unk_20:
 *   0: once func_82105724(D_8219A544, 0x1E) succeeds, runs the shared camera setup
 *      (func_821255B4, func_8212C78C, func_8211F034, ...), plays sound 0x2E, resets the
 *      camera frame counter and advances to state 1.
 *   1: while scene->unk_54 == 1, eases the camera field at +0x2C towards 60.0f; when the frame
 *      counter reaches 0x32, clears the message cursor and advances to state 2.
 *   2: same easing, caches func_8210F31C for both active Pokemon in D_8219A560/D_8219A564,
 *      sets scene->unk_34 = 3 if byte 0x820 of D_8219A540 is 0xFF, resets the frame counter
 *      and animation step and finishes through func_82125C80.
 */
void func_8212DB28(CameraNode* arg0) {
    sBattleScene.scene->unk_50 = 4;
    switch (sBattleScene.scene->unk_20) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_821255B4(arg0);
                func_80042A6C(0x2E);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                func_8212C78C((s32)arg0);
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82105E64((ActivePokemon*)D_8219A544);
                BattleScene_ResetCameraFrameCounter();
                sBattleScene.scene->unk_20++;
            }
            break;

        case 1:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x32) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->unk_20++;
            }
            break;

        case 2:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (M2C_FIELD(D_8219A540, u8*, 0x820) == 0xFF) {
                sBattleScene.scene->unk_34 = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8212DD14; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212DD14.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8212DE30; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212DE30.s")
#endif

void func_82125C34(CameraNode*);
void func_82104C68(ActivePokemon*, s32);
s32 func_82105724(ActivePokemon*, s32);
void func_821224F4();
void func_82105E38(ActivePokemon*, s32);
void func_8212311C(CameraNode*, ActivePokemon*, f32);
s32 func_82121820(s32);
void func_8213C4B8(void);
extern f32 D_FLT_82189354[][4];
void func_8212E0B0(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                BattleScene_ResetCameraFrameCounter();
                func_821224F4();
                func_82125570();
                Battle_ClearMessageCursor();
                func_82104C68((ActivePokemon*)D_8219A544, 8);
                M2C_FIELD(sBattleScene.scene, f32*, 0x88) = 0.5f;
                BattleAnim_Vec3fCopy(&M2C_FIELD(sBattleScene.scene, Vec3f*, 0xA8), &arg0->view.targetPosition);
                BattleAnim_Vec3fCopy(&M2C_FIELD(sBattleScene.scene, Vec3f*, 0xB4), &arg0->view.eyePosition);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 1:
            BattleAnim_ApproachF(&M2C_FIELD(sBattleScene.scene, f32*, 0x88), 0.0f, 0.06f);
            func_8212311C(arg0, (ActivePokemon*)D_8219A544, M2C_FIELD(sBattleScene.scene, f32*, 0x88));
            if (((ActivePokemon*)D_8219A544)->displayObject.position.y - D_FLT_82189354[M2C_FIELD(D_8219A544, s16*, 0x1A)][0] >= 800.0f) {
                func_8211F034(D_8219A520 + 0x148, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 2:
            func_82105E38((ActivePokemon*)D_8219A544, 0x200);
            BattleAnim_Vec3fCopy(&arg0->view.targetPosition, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xA8));
            BattleAnim_Vec3fCopy(&arg0->view.eyePosition, &M2C_FIELD(sBattleScene.scene, Vec3f*, 0xB4));
            sBattleScene.scene->unk_20++;
            break;

        case 3:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (func_82121820(0x28) != 0)) {
                func_82105E38(sActivePokemon[sBattleScene.scene->unk_2C], 4);
                func_8213C4B8();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8212E350; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212E350.s")
#endif

extern s32 D_84390220;
extern ActivePokemon* D_84390204;
extern s32 D_84390224;
s32 func_82121798(s32);
void func_8212188C(void);
void func_8212189C(void);
s32 func_82105AB0(ActivePokemon*, s32);
void func_82124A40(void);
/*
 * func_8212E634: two-step camera/animation state for a battle move effect.
 * Sets the scene's unk_50 to 4, then switches on the scene state counter
 * (unk_20):
 *   0: calls func_82124984 for the active Pokemon (D_8219A544) and waits on
 *      func_82105724(.., 0x1E), a "move cue reached" check that falls back to
 *      a 0x1E-frame wait when the Pokemon is frozen, asleep, airborne or
 *      underground.  Once it reports true the effect is set up
 *      (func_821255B4, func_8211F034, func_8212188C/func_8212189C,
 *      func_82104C68 with 8, func_82110B44) and the state counter advances.
 *   1: calls func_8211EE8C when func_82121798(0x28) fires, refreshes
 *      D_8219A560/D_8219A564 from the two entries of sActivePokemon (the
 *      indices unk_2C and !unk_2C), and when func_82105AB0(.., 0x1E) -- the
 *      same kind of cue check -- reports true calls func_82124A40 and
 *      func_82125C80.
 * Same shape as func_8212C874 and func_8212E7B0.
 */
void func_8212E634(CameraNode* arg0) {
    sBattleScene.scene->unk_50 = 4;
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_82124984(D_8219A544, (s32)arg0, 3);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                func_8212188C();
                func_8212189C();
                func_82104C68((ActivePokemon*)D_8219A544, 8);
                func_82110B44((ActivePokemon*)D_8219A544);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 1:
            if (func_82121798(0x28) != 0) {
                func_8211EE8C();
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (func_82105AB0((ActivePokemon*)D_8219A544, 0x1E) != 0) {
                func_82124A40();
                func_82125C80(arg0);
            }
            break;
    }
}

void func_82104C68(ActivePokemon*, s32);
void func_82124A40(void);
void func_8212E7B0(CameraNode* arg0) {
    sBattleScene.scene->unk_50 = 4;
    switch (sBattleScene.scene->unk_20) {
        case 0:
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                func_821255B4(arg0);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                func_8212C78C((s32)arg0);
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                func_82110B44((ActivePokemon*)D_8219A544);
                func_82104C68((ActivePokemon*)D_8219A544, 9);
                sBattleScene.scene->unk_20++;
                func_82110B44((ActivePokemon*)D_8219A544);
            }
            break;

        case 1:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 2:
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x54) == 1) {
                BattleAnim_ApproachF(&M2C_FIELD(arg0, f32*, 0x2C), 60.0f, 0.03f);
            }
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            func_82124A40();
            func_82125C80(arg0);
            break;
    }
}

void func_82105E4C(ActivePokemon*, s32);
void func_82136708(s32, ActivePokemon*);
void func_8212E9C8(ActivePokemon* arg0) {
    u8* ptr = (u8*)arg0 + 0x78C;

    if (M2C_FIELD(ptr, u16*, 0x36) & 0x200) {
        arg0->displayObject.position.y = D_FLT_82189354[M2C_FIELD(arg0, s16*, 0x1A)][0];
        func_82105E4C(arg0, 0x608);
    } else if (M2C_FIELD(ptr, u16*, 0x36) & 0x4008) {
        arg0->displayObject.lodFraction = 0xFF;
        func_82136708(4, arg0);
        arg0->displayObject.position.y = D_FLT_82189354[M2C_FIELD(arg0, s16*, 0x1A)][0];
        arg0->displayObject.node.renderFlags &= ~0x2;
        arg0->displayObject.node.renderFlags |= 0x20;
        arg0->displayObject.node.flags |= 1;
        func_82105E4C(arg0, 0x4608);
    }
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_821255EC(CameraNode*);
void func_8212E9C8(ActivePokemon*);
void func_8212C6E8(ActivePokemon*, CameraNode*, s32);
void func_8212239C(ActivePokemon*, CameraNode*);
void func_821366B0(s32, ActivePokemon*);
s32 func_8210F31C(ActivePokemon*);
s32 func_82122DFC(CameraNode*, ActivePokemon*);
s32 func_82105724(ActivePokemon*, s32);
s32 func_82124BF8(ActivePokemon*);
void func_82125C34(CameraNode*);
extern s32 D_8219A560;
extern s32 D_8219A564;
void BattleScene_PhaseFaint(CameraNode* arg0) {
    func_821255EC(arg0);

    switch (sBattleScene.scene->unk_20) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98((ActivePokemon*)D_8219A544) == 0) {
                func_8212E9C8((ActivePokemon*)D_8219A544);
                func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 1:
            BattleScene_ResetAnimationStep();
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xF);
            func_8212C6E8((ActivePokemon*)D_8219A544, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            func_8212239C((ActivePokemon*)D_8219A544, arg0);
            BattleScene_SetDamageShakeAmplitude((ActivePokemon*)D_8219A544);
            func_821366B0(8, (ActivePokemon*)D_8219A544);
            sBattleScene.scene->unk_20 += 1;
            break;

        case 2:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            func_82122DFC(arg0, (ActivePokemon*)D_8219A544);
            if (func_82105724((ActivePokemon*)D_8219A544, 0x32) != 0) {
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 3:
            if (func_82124BF8((ActivePokemon*)D_8219A544) == 0) {
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 4:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (func_82122DFC(arg0, (ActivePokemon*)D_8219A544) != 0) {
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212EA84.s")
#endif

void func_821255B4(CameraNode*);
void func_82125C80(CameraNode*);
void func_8212ECC8(CameraNode* arg0) {
    sBattleScene.scene->unk_50 = 4;

    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_821255B4(arg0);
            func_8211F034(D_8219A520 + 0xC8, sBattleScene.scene->unk_2C);
            func_8212E9C8((ActivePokemon*)D_8219A544);
            func_82124984(D_8219A544, arg0, 3);
            sBattleScene.scene->unk_20 += 1;
            break;

        case 1:
            func_82124984(D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x14) != 0) {
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                func_82110B44((ActivePokemon*)D_8219A544);
                BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 9);
                sBattleScene.scene->unk_20 += 1;
                func_82110B44((ActivePokemon*)D_8219A544);
            }
            break;

        case 2:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 3:
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            BattleScene_ResetAnimationStep();
            func_82125C80(arg0);
            break;
    }
}

extern s32 D_8219A568;
void func_821247F0(void*, void*);
s32 func_82124810(void*, void*);
void func_82124830(void*, void*);
void func_82124874(void*, void*);

void func_8212EEC0(ActivePokemon* arg0, CameraNode* arg1) {
    D_8219A568 = BattleAnim_RandomRange(3);
    if (D_8219A568 >= 4) {
        D_8219A568 = 0;
    }
    switch (D_8219A568) {
        case 0:
            func_821247F0(arg1, arg0);
            break;
        case 1:
            func_82124810(arg1, arg0);
            break;
        case 2:
            func_82124830(arg1, arg0);
            break;
        default:
            func_82124874(arg1, arg0);
            break;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8212EF74; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212EF74.s")
#endif

void func_8212EF74(ActivePokemon*, CameraNode*);

void func_8212F044(CameraNode* arg0) {
    s32 other = sBattleScene.scene->unk_2C == 0;
    ActivePokemon* opp = sActivePokemon[other];
    BattleMonRuntime* runtime = &opp->state.runtime;

    if (D_80073D90[runtime->usedMove - 1].unk_06 == 5) {
        func_8212C6E8(opp, arg0, D_8219A568);
    } else if (D_80073D90[runtime->usedMove - 1].unk_06 == 4) {
        func_8212EEC0(opp, arg0);
    } else if (D_80073D90[runtime->usedMove - 1].unk_06 == 6) {
        func_8212EF74(opp, arg0);
    } else {
        func_8212C6E8(opp, arg0, D_80073D90[runtime->usedMove - 1].unk_06);
    }
}

M2C_UNK func_8211EE8C();                            /* extern */
M2C_UNK func_82125384();                            /* extern */
extern s8 *D_8219A5A0;

void func_8212F118(s32 arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_8219A5A0, s32 *, 0x20);
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8211EE8C();
        func_82125384();
        /* fallthrough */
    case 1:
        return;
    }
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_82121EB0(ActivePokemon*);
void func_82108C0C(ActivePokemon* active_pokemon);
void func_8212C6E8(ActivePokemon*, CameraNode*, s32);
s32 func_82124BF8(ActivePokemon*);
void func_82135098(ActivePokemon*);
extern u8* D_82189180[];
s32 func_82124B30(ActivePokemon*);
void func_8212F16C(CameraNode* arg0) {
    UNUSED s32 pad;
    s32 side = sBattleScene.scene->unk_2C;
    u8* sp1C = D_82189180[side] + 0x738;

    func_821255EC(arg0);
    switch (sBattleScene.scene->unk_20) {
        case 0:
            BattleScene_ResetAnimationStep();
            sBattleScene.scene->unk_20++;
            break;

        case 1:
            if (func_82124B30((ActivePokemon*)D_8219A544) == 0) {
                func_82135098((ActivePokemon*)D_8219A544);
                sBattleScene.scene->unk_50 = 1;
                func_82108C0C((ActivePokemon*)D_8219A544);
                func_8213B31C(1);
                func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
                func_8212C6E8((ActivePokemon*)D_8219A544, arg0, 3);
                func_8212239C((ActivePokemon*)D_8219A544, arg0);
                func_82121EB0((ActivePokemon*)D_8219A544);
                BattleScene_ResetAnimationStep();
                ModelAnim_SetAnimation((DisplayObject*)D_8219A544, *sp1C);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 2:
            sBattleScene.scene->unk_50 = 1;
            func_8212C6E8((ActivePokemon*)D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                Battle_ClearMessageCursor();
                func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 3:
            sBattleScene.scene->unk_50 = 1;
            func_8212C6E8((ActivePokemon*)D_8219A544, arg0, 3);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                Battle_ClearMessageCursor();
                sBattleScene.scene->unk_20++;
            }
            break;

        case 4:
            sBattleScene.scene->unk_50 = 1;
            if (func_82124BF8((ActivePokemon*)D_8219A544) == 0) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 5:
            sBattleScene.scene->unk_50 = 1;
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            func_8212C6E8((ActivePokemon*)D_8219A544, arg0, 3);
            if ((D_8219A560 != 0) && (D_8219A564 != 0)) {
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212F16C.s")
#endif

extern s32 D_84390228;
extern ActivePokemon* D_84390200;
void func_821255EC(CameraNode*);
void func_8212C6E8(ActivePokemon*, CameraNode*, s32);
void func_8210626C(ActivePokemon*);
void func_82124E80(void);

M2C_UNK func_8211EE8C();
void func_82125C34(CameraNode*);
extern ActivePokemon* D_8219A540;
void BattleScene_PhaseMoveFailedMessage(CameraNode* arg0) {
    ActivePokemonState* sp1C = &D_8219A540->state;

    func_821255EC(arg0);
    M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 2;

    switch (sBattleScene.scene->unk_20) {
        case 0:
            BattleAnim_CleanupEffects(1);
            if (sp1C->flags & 0x200) {
                func_8212C6E8(D_8219A540, arg0, D_8219A568 = 2);
            } else {
                func_8212C6E8(D_8219A540, arg0, D_8219A568 = BattleAnim_RandomRange(2));
            }
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xC);
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
            BattleScene_ResetCameraFrameCounter();
            sBattleScene.scene->unk_20 += 1;
            func_8210626C(D_8219A540);
            break;

        case 1:
            func_82124E80();
            if (func_821217DC(0x32) != 0) {
                BattleScene_CleanupParticipantEffectMode((ActivePokemon*)D_8219A544);
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                func_8211EE8C();
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}

void func_8212F5B4(CameraNode* arg0) {
    M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 2;
    func_821255EC(arg0);

    switch (sBattleScene.scene->unk_20) {
        case 0:
            BattleAnim_CleanupEffects(1);
            func_8212F044(arg0);
            func_8212239C(D_8219A540, arg0);
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xE);
            sBattleScene.scene->unk_20 += 1;
            break;

        case 1:
            func_82122DFC(arg0, D_8219A540);
            if (M2C_FIELD(sBattleScene.scene, s32*, 0x14) == 0x1E) {
                func_82110B44(D_8219A540);
            }
            if (func_821217DC(0x50) != 0) {
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                func_8211EE8C();
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}

void func_82125AC8(CameraNode* arg0);
void func_82122A7C(CameraNode*, ActivePokemon*);
void func_8212F6E4(CameraNode* arg0) {
    M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 2;
    func_821255EC(arg0);

    switch (sBattleScene.scene->unk_20) {
        case 0:
            BattleAnim_CleanupEffects(1);
            BattleScene_ResetAnimationStep();
            BattleScene_ResetCameraFrameCounter();
            func_82110B44(D_8219A540);
            func_8212F044(arg0);
            func_8212239C(D_8219A540, arg0);
            BattleScene_EnterStateRow((ActivePokemon*)D_8219A544, 0xB);
            func_8211F034(D_8219A520 + 0x208, sBattleScene.scene->unk_2C);
            sBattleScene.scene->unk_20 += 1;
            break;

        case 1:
            func_82122DFC(arg0, D_8219A540);
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x6E) != 0) {
                sBattleScene.scene->unk_20 += 1;
                func_8211EE8C();
                BattleScene_ResetCameraFrameCounter();
            }
            break;

        case 2:
            if (func_82124BF8(D_8219A540) == 0) {
                func_82124E80();
                D_8219A560 = func_8210F31C(D_8219A540);
                D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
                func_82122A7C(arg0, D_8219A540);
                BattleScene_ResetAnimationStep();
                func_82125AC8(arg0);
            }
            break;
    }
}

s16 func_82107B54(ActivePokemon*);
void func_8212F894(CameraNode* arg0) {
    BattleMonRuntime* runtime = &((ActivePokemon*)D_8219A544)->state.runtime;

    M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 2;
    func_821255EC(arg0);

    switch (sBattleScene.scene->unk_20) {
        case 0:
            BattleAnim_CleanupEffects(1);
            func_8212C6E8(D_8219A540, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
            BattleScene_ResetCameraFrameCounter();
            BattleAnim_QueueMoveEffectEnd(runtime->usedMove, (ActivePokemon*)D_8219A544, D_8219A540, BattleScene_GetHitCueDefaultAnchor(D_8219A540), func_82107B54(D_8219A540));
            BattleScene_SetParticipantModelTransform(D_8219A540, 0x10, 0);
            sBattleScene.scene->unk_20 += 1;
            break;

        case 1:
            func_82124E80();
            if (func_821217DC(0x50) != 0) {
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                func_8211EE8C();
                BattleScene_ResetAnimationStep();
                func_82125C34(arg0);
            }
            break;
    }
}

void func_80040738(void);
void func_82104C68(ActivePokemon*, s32);
void func_8212C6E8(ActivePokemon*, CameraNode*, s32);
void func_82121EB0(ActivePokemon*);
void func_821365E8(s32, ActivePokemon*);
s32 func_82105724(ActivePokemon*, s32);
void func_82124E80(void);
void func_82125AC8(CameraNode*);
void func_8212F9FC(CameraNode* arg0) {
    func_821255EC(arg0);
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_82135098((ActivePokemon*)D_8219A544);
            func_82135098(D_8219A540);
            func_8213B31C(1);
            sBattleScene.scene->unk_50 = 2;
            func_82104C68((ActivePokemon*)D_8219A544, 4);
            func_8212C6E8(D_8219A540, arg0, D_8219A568 = BattleAnim_RandomRange(4));
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
            BattleScene_ResetCameraFrameCounter();
            func_82121EB0(D_8219A540);
            sBattleScene.scene->unk_20++;
            break;

        case 1:
            sBattleScene.scene->unk_50 = 2;
            D_8219A564 = func_8210F31C(D_8219A540);
            if (sBattleScene.scene->unk_14 == 0x3C) {
                Battle_ClearMessageCursor();
            }
            if ((D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounter(0x96) != 0)) {
                func_8212C6E8((ActivePokemon*)D_8219A544, arg0, D_8219A568 = BattleAnim_RandomRange(4));
                func_80040738();
                func_8213B31C(1);
                func_821365E8(4, (ActivePokemon*)D_8219A544);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 2:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if (BattleScene_AdvanceCameraFrameCounter(0x5A) != 0) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 3:
            D_8219A560 = func_8210F31C(D_8219A540);
            D_8219A564 = func_8210F31C((ActivePokemon*)D_8219A544);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (func_82105724((ActivePokemon*)D_8219A544, 0x1E) != 0)) {
                func_82125570();
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                func_82124E80();
                func_82125AC8(arg0);
            }
            break;
    }
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_82124894(CameraNode*, ActivePokemon*);
void func_82106374(ActivePokemon*);
void func_82106354(ActivePokemon*);
s32 func_82124A50(ActivePokemon*);
void func_82108C0C(ActivePokemon*);
void func_821366B0(s32, ActivePokemon*);
M2C_UNK func_800407B0(M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_82107CA0(ActivePokemon*);
void func_8212FC98(CameraNode* arg0) {
    u8* sp2C = (u8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x7C6;
    u8* sp28 = (u8*)sActivePokemon[!sBattleScene.scene->unk_2C] + 0x7C6;
    ActivePokemon* sp24 = sActivePokemon[sBattleScene.scene->unk_2C];

    M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 4;
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            func_82124A40();
            func_82135098((ActivePokemon*)D_8219A544);
            func_82106374((ActivePokemon*)D_8219A544);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->unk_20++;
            break;

        case 1:
            func_82106354(sp24);
            if (func_82124A50(sActivePokemon[sBattleScene.scene->unk_2C]) == 0) {
                func_82108C0C((ActivePokemon*)D_8219A544);
                func_80040738();
                BattleAnim_CleanupEffects(1);
                func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
                func_82104C68(sActivePokemon[sBattleScene.scene->unk_2C], 0xD);
                if (sp2C[0x15] & 0x18) {
                    func_8211F034(D_8219A520 + 0x248, sBattleScene.scene->unk_2C);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0xE);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0xE);
                    if (sp2C[0x15] & 0x10) {
                        func_821366B0(6, (ActivePokemon*)D_8219A544);
                    } else {
                        func_821366B0(5, (ActivePokemon*)D_8219A544);
                    }
                    sBattleScene.scene->unk_20++;
                } else {
                    func_82135098(D_8219A540);
                    func_8211F034(D_8219A520 + 0x288, sBattleScene.scene->unk_2C);
                    func_800407B0(0x22, 0, 0);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    func_821366B0(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->unk_20 = 3;
                }
            }
            break;

        case 2:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                if (func_82107CA0(sActivePokemon[sBattleScene.scene->unk_2C]) == 0) {
                    func_82125570();
                    BattleScene_SetPhase(arg0, 5);
                    sBattleScene.scene->unk_2C = !sBattleScene.scene->unk_2C;
                } else if (sp2C[0x4D] & 0x80) {
                    func_82135098(D_8219A540);
                    func_800407B0(0x22, 0, 0);
                    func_8211F034(D_8219A520 + 0x288, sBattleScene.scene->unk_2C);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    func_821366B0(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->unk_20++;
                } else {
                    sBattleScene.scene->unk_20 = 4;
                }
            }
            break;

        case 3:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if ((BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0) && (D_8219A560 == 1) && (D_8219A564 == 1)) {
                sBattleScene.scene->unk_20++;
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
            }
            break;

        case 4:
            if (func_82124BF8(D_8219A540) == 0) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 5:
            func_82124A40();
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_8212FC98.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_821301EC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821301EC.s")
#endif

void func_82106354(ActivePokemon*);
extern ActivePokemon* D_8219A540;
s32 func_82124A50(ActivePokemon* active_pokemon);
void func_82108C0C(ActivePokemon* active_pokemon);
void func_80040738(void);
void func_82124894(CameraNode* arg0, ActivePokemon* arg1);
void func_82125AC8(CameraNode* arg0);
void BattleScene_Phase10(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            BattleScene_CleanupParticipantEffectMode((ActivePokemon*)D_8219A544);
            func_82106354(sActivePokemon[sBattleScene.scene->unk_2C]);
            if (func_82124A50(sActivePokemon[sBattleScene.scene->unk_2C]) == 0) {
                func_82108C0C((ActivePokemon*)D_8219A544);
                func_80040738();
                BattleAnim_CleanupEffects(1);
                BattleScene_ResetCameraFrameCounter();
                func_8211F034(D_8219A520 + 0x348, !sBattleScene.scene->unk_2C);
                BattleAnim_QueueEffectList6(3, D_8219A540);
                Audio_PlayCommand(0x23, 0, 0);
                func_82124894(arg0, D_8219A540);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(0x37) != 0) {
                func_8211EE8C();
                func_8211F034(D_8219A520 + 0x2C8, !sBattleScene.scene->unk_2C);
                sBattleScene.scene->unk_20 += 1;
            }

        case 2:
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                func_8211EE8C();
                func_82125AC8(arg0);
            }
            break;
    }
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
void func_82130628(CameraNode* arg0) {
    u8* sp2C = (u8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x7C6;
    u8* sp28 = (u8*)sActivePokemon[!sBattleScene.scene->unk_2C] + 0x7C6;
    ActivePokemon* cur = sActivePokemon[sBattleScene.scene->unk_2C];

    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_82135098((ActivePokemon*)D_8219A544);
            func_82106374((ActivePokemon*)D_8219A544);
            BattleAnim_CleanupEffects(2);
            sBattleScene.scene->unk_20++;
            break;

        case 1:
            func_82106354(cur);
            if (func_82124A50(sActivePokemon[sBattleScene.scene->unk_2C]) == 0) {
                func_82108C0C((ActivePokemon*)D_8219A544);
                func_80040738();
                BattleAnim_CleanupEffects(1);
                func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
                func_82104C68(sActivePokemon[sBattleScene.scene->unk_2C], 0xD);
                if (sp2C[0x15] & 0x18) {
                    func_8211F034(D_8219A520 + 0x248, sBattleScene.scene->unk_2C);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0xE);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0xE);
                    if (sp2C[0x15] & 0x10) {
                        func_821366B0(6, (ActivePokemon*)D_8219A544);
                    } else {
                        func_821366B0(5, (ActivePokemon*)D_8219A544);
                    }
                    sBattleScene.scene->unk_20++;
                } else {
                    func_8211F034(D_8219A520 + 0x288, sBattleScene.scene->unk_2C);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    func_821366B0(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->unk_20 = 3;
                }
            }
            break;

        case 2:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if ((D_8219A560 == 1) && (D_8219A564 == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
                if (func_82107CA0(sActivePokemon[sBattleScene.scene->unk_2C]) == 0) {
                    func_82125570();
                    BattleScene_SetPhase(arg0, 5);
                    sBattleScene.scene->unk_2C = !sBattleScene.scene->unk_2C;
                } else if (sp2C[0x4D] & 0x80) {
                    func_800407B0(0x22, 0, 0);
                    func_8211F034(D_8219A520 + 0x288, sBattleScene.scene->unk_2C);
                    M2C_FIELD(sp2C, u16*, 0xC) = M2C_FIELD(sp2C, u16*, 0x10);
                    M2C_FIELD(sp28, u16*, 0xC) = M2C_FIELD(sp28, u16*, 0x10);
                    func_821366B0(0xA, (ActivePokemon*)D_8219A544);
                    sBattleScene.scene->unk_20++;
                } else {
                    sBattleScene.scene->unk_20 = 4;
                }
            }
            break;

        case 3:
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            if ((BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0) && (D_8219A560 == 1) && (D_8219A564 == 1)) {
                sBattleScene.scene->unk_20++;
                BattleScene_ResetCameraFrameCounter();
                Battle_ClearMessageCursor();
            }
            break;

        case 4:
            if (func_82124BF8(D_8219A540) == 0) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 5:
            func_82124A40();
            func_82124894(arg0, sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A560 = func_8210F31C(sActivePokemon[sBattleScene.scene->unk_2C]);
            D_8219A564 = func_8210F31C(sActivePokemon[!sBattleScene.scene->unk_2C]);
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82130628.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82130B10; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82130B10.s")
#endif

void func_82130D48(ActivePokemon* active_pokemon) {
    BattleMon* party_pokemon = &active_pokemon->teamRoster->pokemonPicked[M2C_FIELD(active_pokemon, s32*, 0x9D0)];

    if (M2C_FIELD(party_pokemon, u8*, 5) & 0x20) {
        BattleAnim_StopOwnerCategoryParticles(1, active_pokemon);
        active_pokemon->displayObject.node.renderFlags |= 0x20;
    }
}

#ifdef NON_MATCHING
// Matches the ROM, but uses rodata data that is not placed in this file yet.
Vec3f* Vec3f_SetComponentsDuplicate(Vec3f* dest, f32 x, f32 y, f32 z);
s32 ModelAnim_IsAnimationDone(DisplayObject* display_object);
void func_82130D48(ActivePokemon*);
void func_82107408(ActivePokemon*);
void func_8212562C(void);
void func_82130DAC(CameraNode* arg0) {
    u8* sp2C = (u8*)sActivePokemon[sBattleScene.scene->unk_2C] + 0x78C;
    ActivePokemon* temp_s0 = sActivePokemon[sBattleScene.scene->unk_2C];

    if (sBattleScene.scene->unk_2C) {}

    M2C_FIELD(sBattleScene.scene, s32*, 0x50) = 4;
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_821255EC(arg0);
            func_82124984((s32)temp_s0, (s32)arg0, 2);
            BattleScene_ResetCameraFrameCounter();
            func_8211F034(D_8219A520 + 0x1C8, sBattleScene.scene->unk_2C);
            sBattleScene.scene->unk_20++;
            break;

        case 1:
            BattleScene_ApproachCameraZoom(arg0, temp_s0);
            func_82104C68(temp_s0, 2);
            func_82130D48(temp_s0);
            sBattleScene.scene->unk_20++;
            break;

        case 2:
            BattleScene_ApproachCameraZoom(arg0, temp_s0);
            if (sBattleScene.scene->unk_14 == 0x23) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_AdvanceCameraFrameCounter(0x69) != 0) {
                Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)arg0 + 0xB4), M2C_FIELD(temp_s0, s32*, 0x60C) * -150.0f, 0.0, 0.0f);
                if (sBattleScene.scene && sBattleScene.scene) {}
                Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)arg0 + 0xA8), M2C_FIELD(temp_s0, s32*, 0x60C) * -50.0f, 5.0f, 0.0f);
                BattleScene_SetParticipantModelTransform(temp_s0, 2, 0);
                BattleAnim_QueueEffectList3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 3:
            if (M2C_FIELD(temp_s0, f32*, 0x64C) == 2.5f) {
                M2C_FIELD(temp_s0, u8*, 0x626) |= 0x20;
            }
            if (ModelAnim_IsAnimationDone((DisplayObject*)((u8*)temp_s0 + 0x624)) == 1) {
                sBattleScene.scene->unk_20++;
            }
            break;

        case 4:
            M2C_FIELD(temp_s0, u8*, 0x625) &= ~1;
            *M2C_FIELD(temp_s0, u8**, 0x85C) |= 0x80;
            sBattleScene.scene->unk_20++;
            break;

        case 5:
            if (*M2C_FIELD(temp_s0, u8**, 0x85C) & 0x10) {
                *M2C_FIELD(temp_s0, u8**, 0x85C) &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                func_82107408(temp_s0);
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                func_800407B0(2, 0, 0);
                BattleScene_RebindParticipantTeamMember(temp_s0, sp2C[0x2D]);
                sBattleScene.scene->unk_20++;
            }
            break;

        case 6:
            func_82104C68(temp_s0, 0x12);
            func_82124984((s32)temp_s0, (s32)arg0, 3);
            func_8212239C(temp_s0, arg0);
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
            BattleScene_ResetCameraFrameCounter();
            sBattleScene.scene->unk_20++;
            break;

        case 7:
            func_82122A7C(arg0, temp_s0);
            if (sBattleScene.scene->unk_14 == 0x1E) {
                Battle_ClearMessageCursor();
            }
            if (BattleScene_IsRowWaitCompleteWithEventCount(temp_s0, 0x64) != 0) {
                func_80040738();
                BattleAnim_CleanupEffects(2);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                Vec3f_SetComponentsDuplicate((Vec3f*)((u8*)temp_s0 + 0x30), 1.0f, 1.0f, 1.0f);
                func_8212562C();
                M2C_FIELD(sp2C, u16*, 0x36) &= ~0x3800;
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82130DAC.s")
#endif

Vec3f* Vec3f_SetComponentsDuplicate(Vec3f* dest, f32 x, f32 y, f32 z);
void func_82124984(s32, s32, s32);
void func_8212239C(ActivePokemon* arg0, CameraNode* arg1);
void func_82122A7C(CameraNode* arg0, ActivePokemon* arg1);
void func_80040738(void);
void func_8212562C(void);
void func_821311A0(CameraNode* arg0) {
    ActivePokemonState* sp3C = &sActivePokemon[sBattleScene.scene->unk_2C]->state;
    ActivePokemonState* sp38 = &sActivePokemon[!sBattleScene.scene->unk_2C]->state;
    ActivePokemon* temp_s0 = sActivePokemon[sBattleScene.scene->unk_2C];
    BattleMonRuntime* sp2C = &sActivePokemon[sBattleScene.scene->unk_2C]->state.runtime;

    sBattleScene.scene->unk_50 = 4;

    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_821255EC(arg0);
            Vec3f_SetComponentsDuplicate(&arg0->view.targetPosition, temp_s0->facingDirection * -150.0f, 0.0, 0.0f);
            Vec3f_SetComponentsDuplicate(&arg0->view.eyePosition, temp_s0->facingDirection * -50.0f, 5.0f, 0.0f);
            Vec3f_SetComponentsDuplicate(&temp_s0->displayObject.position, temp_s0->facingDirection * -150.0f, 25.0f, 0.0f);
            BattleScene_ResetCameraFrameCounter();
            Battle_ClearMessageCursor();
            func_8211F034(D_8219A520 + 0x88, sBattleScene.scene->unk_2C);
            BattleAnim_LoadModeResourceList(temp_s0->sessionTeams, 3);
            sBattleScene.scene->unk_20 += 1;
            break;

        case 1:
            if (BattleAnim_TryRegisterAssetTables(temp_s0) != 0) {
                temp_s0->sessionTeams->displayModel = sp2C->id;
                temp_s0->sessionTeams->unk_04 = (TeamRoster*)&temp_s0->teamRoster->pokemonPicked[temp_s0->state.rosterIndex];
                BattleScene_SetParticipantModelTransform(temp_s0, 2, 0);
                BattleAnim_QueueEffectList3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 2:
            if (temp_s0->pokeBall.position.y == 2.5f) {
                temp_s0->pokeBall.node.renderFlags |= 0x20;
            }

            if (ModelAnim_IsAnimationDone(&temp_s0->pokeBall) == 1) {
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 3:
            temp_s0->pokeBall.node.flags &= ~1;
            temp_s0->sessionTeams->uniqueStatusFlags |= 0x80;
            sBattleScene.scene->unk_20 += 1;
            break;

        case 4:
            if (temp_s0->sessionTeams->uniqueStatusFlags & 0x10) {
                temp_s0->sessionTeams->uniqueStatusFlags &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                BattleThumbnail_TickOwnerCameraFraming(temp_s0);
                Audio_PlayCommand(2, 0, 0);
                M2C_FIELD(temp_s0, s32*, 0x9D0) = sp3C->rosterIndex;
                M2C_FIELD(temp_s0, s32*, 0x9D4) = sp3C->teamMemberIndex;
                BattleScene_RebindParticipantTeamMember(temp_s0, sp3C->unk_2D_zero);
                BattleScene_ResetCameraFrameCounter();
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                BattleScene_EnterStateRow(temp_s0, 0x12);
                func_82124984((s32)temp_s0, (s32)arg0, 3);
                func_8212239C(temp_s0, arg0);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 5:
            func_82124984((s32)temp_s0, (s32)arg0, 3);
            func_8212239C(temp_s0, arg0);
            sBattleScene.scene->unk_20 += 1;
            break;

        case 6:
            func_82122A7C(arg0, temp_s0);
            if (BattleScene_AdvanceCameraFrameCounter(0x15) != 0) {
                Battle_ClearMessageCursor();
                BattleAnim_ResetFreezeStatusAndRestoreAnimation(temp_s0);
                sBattleScene.scene->unk_20 += 1;
            }
            break;

        case 7:
            func_82122A7C(arg0, temp_s0);
            if (BattleScene_IsRowWaitCompleteWithEventCount(temp_s0, 0x32) != 0) {
                func_80040738();
                BattleAnim_CleanupEffects(2);
                Battle_ClearMessageCursor();
                BattleScene_ResetCameraFrameCounter();
                Vec3f_SetComponentsDuplicate(&temp_s0->displayObject.scale, 1.0f, 1.0f, 1.0f);
                if (sp38->unk_2D != 0x10) {
                    sBattleScene.scene->unk_34 = 3;
                }
                sBattleScene.scene->unk_2E = 2;
                func_8212562C();
                sp3C->flags &= 0xC7FF;
            }
            break;
    }
}

void func_82125FD0(void);
void func_8212601C(CameraNode* arg0);
void func_82126C74(CameraNode* arg0);
void func_82126E34(CameraNode* arg0);
void func_82127250(CameraNode* arg0);
void func_8212BFF0(CameraNode* arg0);
void func_8212C1C4(CameraNode* arg0);
void func_8212C874(CameraNode* arg0);
void func_8212CB58(CameraNode* arg0);
void func_8212CF90(CameraNode* arg0);
void func_8212D194(CameraNode* arg0);
void func_8212D504(CameraNode* arg0);
void func_8212D820(CameraNode* arg0);
void func_8212DB28(CameraNode* arg0);
void func_8212DE30(CameraNode* arg0);
void func_8212E0B0(CameraNode* arg0);
void func_8212E350(CameraNode* arg0);
void func_8212E634(CameraNode* arg0);
void func_8212E7B0(CameraNode* arg0);
void func_8212EA84(CameraNode* arg0);
void func_8212ECC8(CameraNode* arg0);
void func_8212F16C(CameraNode* arg0);
void func_8212F440(CameraNode* arg0);
void func_8212F5B4(CameraNode* arg0);
void func_8212F6E4(CameraNode* arg0);
void func_8212F894(CameraNode* arg0);
void func_8212F9FC(CameraNode* arg0);
void func_8212FC98(CameraNode* arg0);
void func_821301EC(CameraNode* arg0);
void func_82130494(CameraNode* arg0);
void func_82130628(CameraNode* arg0);
void func_82130B10(CameraNode* arg0);
void func_82130DAC(CameraNode* arg0);
void func_821311A0(CameraNode* arg0);
// Zero numbers its phases differently, so the cases call the Zero handlers by address.
void BattleScene_UpdatePhase(CameraNode* arg0) {
    func_82125FD0();
    switch (sBattleScene.scene->unk_38) {
    case 0:
        func_8212601C(arg0);
        BattleScene_SetPhase(arg0, 1);
        /* fallthrough */
    case 1:
        func_82127250(arg0);
        break;
    case 2:
        func_8212BFF0(arg0);
        break;
    case 3:
        func_8212C1C4(arg0);
        break;
    case 4:
        func_8212F118((s32)arg0);
        break;
    case 7:
        func_8212C874(arg0);
        break;
    case 30:
        func_8212CB58(arg0);
        break;
    case 29:
        func_8212DE30(arg0);
        break;
    case 28:
        func_8212CF90(arg0);
        break;
    case 25:
        func_8212D820(arg0);
        break;
    case 21:
        func_8212D194(arg0);
        break;
    case 27:
        func_8212DB28(arg0);
        break;
    case 12:
        func_8212E0B0(arg0);
        break;
    case 13:
        func_8212E350(arg0);
        break;
    case 14:
        func_8212E634(arg0);
        break;
    case 15:
        func_8212D504(arg0);
        break;
    case 17:
        func_8212E7B0(arg0);
        break;
    case 31:
        func_8212ECC8(arg0);
        break;
    case 20:
        func_8212EA84(arg0);
        break;
    case 8:
        func_8212F440(arg0);
        break;
    case 22:
        func_8212F5B4(arg0);
        break;
    case 32:
        func_8212F894(arg0);
        break;
    case 23:
        func_8212F9FC(arg0);
        break;
    case 10:
        func_82130494(arg0);
        break;
    case 6:
        func_8212FC98(arg0);
        break;
    case 33:
        func_82130B10(arg0);
        break;
    case 35:
        func_82130628(arg0);
        break;
    case 9:
        func_821301EC(arg0);
        break;
    case 16:
        func_8212F16C(arg0);
        break;
    case 11:
        func_82130DAC(arg0);
        break;
    case 18:
        func_821311A0(arg0);
        break;
    case 26:
        func_8212F6E4(arg0);
        break;
    case 5:
        func_82126C74(arg0);
        break;
    case 34:
        func_82126E34(arg0);
        break;
    }
}

extern const f32 D_FLT_82196668;
extern const f32 D_FLT_8219666C;
extern Vec3f D_8218B630;
void func_80041914(u8, u8);
void func_82131880(CameraNode* arg0) {
    BattleScene_ResetCameraFrameCounter();
    BattleScene_SetCameraAtFromPosition(arg0, D_8218B630, 0, 0, 0.0f, 0.0f);
    BattleScene_SetCameraEyeAndStoreAngles(arg0, D_8218B630, 0x3C6E, M2C_FIELD(sBattleScene.scene, s16*, 0x5A) = 0, sBattleScene.scene->unk_74 = D_FLT_82196668, 0.0f);
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    M2C_FIELD(sBattleScene.scene, f32*, 0x64) = D_FLT_8219666C;
    Battle_SetStageScale(M2C_FIELD(sBattleScene.scene, f32*, 0x64));
    Audio_PlayCommand(4, 0, 0);
    func_80041914(M2C_FIELD(sActivePokemon[0]->teamRoster, u8*, 2), M2C_FIELD(sActivePokemon[1]->teamRoster, u8*, 2));
    BattleAnim_LoadModeResourceList(sActivePokemon[0]->sessionTeams, 3);
    sBattleScene.scene->unk_20 += 1;
}

s32 func_82101FD4(s32);                             /* extern */
extern s32 D_82199DE0;
extern s8 *D_8219A5A0;

void func_821319FC(s32 arg0) {
    if (func_82101FD4(D_82199DE0) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_82131A3C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82131A3C.s")
#endif

M2C_UNK func_800407B0(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_82108A88(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821365B0(M2C_UNK, s8 *, s8 *, M2C_UNK, s32); /* extern */
extern M2C_UNK D_82199DE0;
extern s8 *D_8219A5A0;

void func_82131C64(s32 arg0) {
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), f32 *, 0x64C) == 0.0f) {
        func_800407B0(1, 1, 0);
        func_82108A88(M2C_FIELD(&D_82199DE0, s8 **, 4), 1, 0);
        func_821365B0(0xA, M2C_FIELD(&D_82199DE0, s8 **, 4), M2C_FIELD(&D_82199DE0, s8 **, 4), 0xFF, 0xFF);
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_82131D24; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82131D24.s")
#endif

void BattleScene_IntroPanCamera(CameraNode* arg0) {
    Vec3f sp2C;

    sp2C.y = 0.0f;
    sp2C.z = 0.0f;
    sp2C.x = -150.0f;
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    BattleAnim_ApproachF(&M2C_FIELD(sBattleScene.scene, f32*, 0x74), 60.000004f, 0.1f);
    BattleAnim_StepToS16(&M2C_FIELD(sBattleScene.scene, s16*, 0x58), 0, 0x1E);
    BattleScene_SetCameraEyeFromPosition(arg0, sp2C, M2C_FIELD(sBattleScene.scene, s16*, 0x58), 0x4000, M2C_FIELD(sBattleScene.scene, f32*, 0x74), 0.0f);

    if ((M2C_FIELD(sBattleScene.scene, s16*, 0x58) >= 0x2E) && (M2C_FIELD(sActivePokemon[0], f32*, 0x64C) == 2.5f)) {
        Audio_PlayCommand(2, 0, 0);
        M2C_FIELD(sActivePokemon[0], u8*, 0x626) |= 0x20;
        sBattleScene.scene->unk_20 += 1;
    }
}

s32 func_8001101C(s8 *, M2C_UNK *);               /* extern */
extern M2C_UNK D_82199DE0;
extern s8 *D_8219A5A0;

void func_8213201C(s32 arg0) {
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 0), u8 *, 1) & 0xFFFE);
    M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) = (u8) (M2C_FIELD(M2C_FIELD(&D_82199DE0, s8 **, 4), u8 *, 1) & 0xFFFE);
    if (func_8001101C(M2C_FIELD(&D_82199DE0, s8 **, 0) + 0x624, &D_82199DE0) == 1) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

s32 func_82107F88(ActivePokemon*);
s32 func_8211EF74(s32, s32, s32, ...);
void func_82104C68(ActivePokemon*, s32);
extern char D_82196650[];
void func_82132088(CameraNode* arg0) {
    sActivePokemon[0]->displayObject.node.flags &= ~1;
    sActivePokemon[1]->displayObject.node.flags &= ~1;
    func_821365B0(3, (s8*)sActivePokemon[0], (s8*)sActivePokemon[0], 0xFF, 0xFF);
    func_8211EF74(D_8219A520 + 0x448, 0, (s32)D_82196650, func_82107F88(sActivePokemon[0]));
    func_8211EE8C();
    func_8211F034(D_8219A520 + 0x448, 0);
    sActivePokemon[0]->displayObject.node.flags |= 1;
    sActivePokemon[0]->pokeBall.node.flags &= ~1;
    func_82124984((s32)sActivePokemon[0], (s32)arg0, 3);
    func_8212239C(sActivePokemon[0], arg0);
    func_82104C68(sActivePokemon[0], 0x10);
    sBattleScene.scene->unk_10 = 0;
    sBattleScene.scene->unk_20++;
}

s32 func_821057D4(ActivePokemon*, s32);
void func_821321A4(CameraNode* arg0) {
    M2C_FIELD(sActivePokemon[1], u8*, 1) &= ~1;
    func_82122A7C(arg0, sActivePokemon[0]);
    sBattleScene.scene->unk_10++;
    if (sBattleScene.scene->unk_10 == 0x28) {
        func_8211EE8C();
    }
    if (func_821057D4(sActivePokemon[0], 0x3C) != 0) {
        sBattleScene.scene->unk_20++;
    }
}

extern char D_8219665C[];
void func_82132238(CameraNode* arg0) {
    func_800407B0(2, 0, 0);
    BattleAnim_QueueEffectList3(3, sActivePokemon[1], sActivePokemon[1], 0xFF, 0xFF);
    func_8211EF74(D_8219A520 + 0x488, 0, (s32)D_8219665C, func_82107F88(sActivePokemon[1]));
    func_8211EE8C();
    func_8211F034(D_8219A520 + 0x488, 1);
    BattleScene_ResetCameraFrameCounter();
    M2C_FIELD(sActivePokemon[1], u8*, 0x1) |= 1;
    func_82124984((s32)sActivePokemon[1], (s32)arg0, 3);
    func_8212239C(sActivePokemon[1], arg0);
    func_82104C68(sActivePokemon[1], 0x10);
    sBattleScene.scene->unk_20++;
    sBattleScene.scene->unk_10 = 0;
}

M2C_UNK func_82125384();
void func_82122A7C(CameraNode* arg0, ActivePokemon* arg1);

void func_8213233C(CameraNode* arg0) {
    M2C_FIELD(sActivePokemon[0], u8*, 1) &= ~1;
    func_82122A7C(arg0, sActivePokemon[1]);
    sBattleScene.scene->unk_10++;
    if (sBattleScene.scene->unk_10 == 0x28) {
        Battle_ClearMessageCursor();
    }
    if (BattleScene_IsRowWaitCompleteWithEventCount(sActivePokemon[1], 0x3C) != 0) {
        Battle_ClearMessageCursor();
        func_82125384();
    }
}
