/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "lab_pc_icons.h"

void func_8A200020(s32 arg0, s32 arg1, BattleMon* arg2) {
    Entry80066AA0* e;

    if (arg2->hp == 0) {
        e = &D_80066AA8;
    } else {
        e = &D_80066AA0[func_8001FA30(arg2->statusCondition)];
    }
    Gfx_SetEnvColor(e->r, e->g, e->b, 0xFF);
    Font_Printf(arg0, arg1, e->str);
}

void func_8A20009C(s32 arg0, s32 arg1, BattleMon* arg2, s32 arg3) {
    BattleHud_DrawHpBarTexture(arg0 + 0x16D, arg1 + 9, 0x94, arg2->hp, arg2->unk_26);
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg3);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0x4C, arg1 + 0xD, arg2->unk_30);
    Gfx_SetEnvColor(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    Font_SetActive(4, 0);
    Font_Printf(arg0 + 0x13B, arg1 + 6, D_8A21D850);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x11B, arg1 + 0x19, D_8A21D854, arg2->unk_24);
    Font_Printf(arg0 + 0x175, arg1 + 0x19, D_8A21D858, arg2->hp, arg2->unk_26);
    func_8A200020(arg0 + 0xD4, arg1 + 0x19, arg2);
    Font_EndTexturedTextRendering();
}

void UI_DrawTextureRgba16(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(arg0, arg1, 0x28, 0x28, M2C_FIELD(M2C_FIELD(M2C_FIELD(D_8A21DA50, s8**, 8) + arg2 * 0x14, s8**, 0xC), u8**, 8), 0x28, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A200274.s")

void func_8A20034C(s8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8002A8C4(arg0, arg1, arg2, 0x221, 0x168);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x1001;
    func_8002D880(arg0 + 0x2C, arg3, arg0 + 0x50, &func_8A200274, 0x215, 0x33);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2003C0.s")

void func_8A200770(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0xA2, 0x1E, D_8A203304);
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, arg1 + 6, arg2);
    Font_EndTexturedTextRendering();
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A20080C.s")

void func_8A2008F4(s8 *arg0) {
    if (func_8002AB84() == 0) {
        func_8002D9B8(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0xC, 0xFEF, 0);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A20093C.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2009CC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A200B78.s")

void func_8A200D44(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Color82000BC4 c;
    s32 idx = func_8002D498(arg3, arg4);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(arg2, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(arg0, arg1, D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A200DE0.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment019_293410/func_8A2010C8.s")


void func_8A201394(s32 arg0, s32 arg1, BattleMon* arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x122, 0x4E, D_8A203304);
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8001ABE8();
    func_8001A384(0x10, 0);
    func_8001AAE4(0x5A, 0x6B, 0xFF, 0xFF);
    func_8001A944(arg0 + 0x25, arg1 + 0x1E, *(char**)D_80064C44[arg2->unk_00.unk_00]);
    func_8001AC3C();
    func_8001A384(8, 0);
    func_8001AA9C(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    func_8001A944(arg0 + 9, arg1 + 6, "No.%03d", arg2->unk_00.unk_00);
    func_8001A944(arg0 + 0xC9, arg1 + 0x21, "L%d", arg2->unk_24);
    func_8001A384(4, 0);
    func_8001A944(arg0 + 9, arg1 + 0x3C, "タイプ");
    func_8001A944(arg0 + 0x4F, arg1 + 0x3C, "1/");
    if (func_8002D498((s32)arg2, 1) != -1) {
        func_8001A944(arg0 + 0xB9, arg1 + 0x3C, "2/");
    }
    func_8A200D44(arg0 + 0x6F, arg1 + 0x3C, 4, (s32)arg2, 0);
    func_8A200D44(arg0 + 0xD9, arg1 + 0x3C, 4, (s32)arg2, 1);
    func_8001ABBC();
}
