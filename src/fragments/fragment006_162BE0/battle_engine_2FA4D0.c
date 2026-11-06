/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_2FA4D0.h"

void func_88400020(s32 arg0, s8 *arg1) {
    if (arg0 == 2) {
        if (D_88403358 >= 0) {
            M2C_FIELD(arg1, u8 *, 1) = (u8) (M2C_FIELD(arg1, u8 *, 1) | 1);
            return;
        }
        M2C_FIELD(arg1, u8 *, 1) = (u8) (M2C_FIELD(arg1, u8 *, 1) & 0xFFFE);
    }
}

void BattleHud_Noop(void) {
}

s32 func_88400064(s32 arg0, unk_D_86002F34_alt18* arg1) {
    UNUSED s32 pad; // keeps the retail stack layout: the three locals below sit 4 bytes lower
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        Vec3f_CalculateDistanceAngles(&D_80060488->view.targetPosition, &D_80060488->view.eyePosition, &sp28, &sp26, &sp24);
        arg1->unk_1C = sp26 + 0x2000;
        arg1->unk_1E = sp24 + 0x2000;
    }
    return 0;
}

s32 func_884000CC(void) {
    func_8000B1FC();
    func_8000B220();
    func_8001B5F0();
    return 0;
}

void func_88400100(void) {
}

s32 func_88400108(s32 arg0) {
    func_884000CC();
    func_800158C0();
    func_800069CC();
    func_80005770(&D_800AA150, 0, 0, 0x140, 0xF0);
    func_8001560C(D_88403370);
    return 0;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_88400168.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_88400458.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment006_162BE0/func_8840079C.s")


void Trade_DrawSaveSeqMessageBackdrop(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Color_RGB8 sp24 = { 0x00, 0x00, 0x32 };
    Color_RGB8 sp20 = { 0x00, 0x00, 0xC8 };

    Ui_DrawGradientPanel(arg0, arg1, arg2, arg3, &sp24, &sp20);
}
