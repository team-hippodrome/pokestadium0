/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragment1_89010.h"

void func_821323D0(UNUSED s32 arg0) {
}

void BattleAnim_NoopUpdateHook(void) {
}

void BattleScene_UpdateIntroSequence(CameraNode* arg0) {
    switch (sBattleScene.scene->unk_20) {
        case 0:
            func_82131880(arg0);

        case 1:
            func_821319FC(arg0);
            break;

        case 2:
            func_82131A3C(arg0);
            break;

        case 3:
            func_82131C64(arg0);
            break;

        case 4:
            func_82131D24(arg0);
            break;

        case 5:
            func_82131EC4(arg0);
            break;

        case 6:
            func_8213201C(arg0);
            break;

        case 7:
            func_82132088(arg0);
            break;

        case 8:
            func_821321A4(arg0);
            break;

        case 9:
            func_82132238(arg0);
            break;

        case 10:
            func_8213233C(arg0);
            break;

        case 11:
            func_821323D0((s32)arg0);
            break;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821324D8.s")

void func_821325E8(s32 arg0) {
    if (func_82101FD4(D_82199DE0) != 0) {
        M2C_FIELD(D_8219A5A0, s32 *, 0x20) = (s32) (M2C_FIELD(D_8219A5A0, s32 *, 0x20) + 1);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_82132628.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment012_17ED00/func_821326E4.s")
