/* Stadium Zero resident code. */

#include "global.h"
#include "input.h"
#include "audio_sfx.h"
#include "m2c_macros.h"

typedef struct MenuDef8002E230 {
    /* 0x00 */ u8* items;
    /* 0x04 */ s32 count;
    /* 0x08 */ s32 itemCount;
    /* 0x0C */ s32 itemSize;
} MenuDef8002E230;
typedef void (*MenuDrawFunc8002E230)(s32, s32, u8*, s32, s32, s32);
typedef struct Menu8002E230 {
    /* 0x00 */ MenuDef8002E230* def;
    /* 0x04 */ u16* flags;
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 colSpacing;
    /* 0x10 */ s32 rowSpacing;
    /* 0x14 */ MenuDrawFunc8002E230 draw;
    /* 0x18 */ Controller* controller;
    /* 0x1C */ s32 repeatMask;
    /* 0x20 */ s32 options;
    /* 0x24 */ s32 columns;
} Menu8002E230;

void func_8002D8D8(s8*, s32, s32);
void func_8002D880(s8* arg0, s32 def, s32 flags, MenuDrawFunc8002E230 draw, s32 width, s32 height) {
    Menu8002E230* menu = (Menu8002E230*)arg0;

    menu->colSpacing = width;
    menu->rowSpacing = height;
    menu->draw = draw;
    func_8002D8D8(arg0, def, flags);
    menu->repeatMask = 0xC00;
    menu->options = 0;
    menu->controller = gPlayer1Controller;
    Input_SetRepeatController(menu->controller);
}

void func_8002D900(u8* arg0);

void func_8002D8D8(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    func_8002D900((u8*)arg0);
}

void func_8002D900(u8* arg0) {
    s32 i;

    for (i = 0; i < M2C_FIELD(M2C_FIELD(arg0, u8**, 0), s32*, 4); i++) {
        M2C_FIELD(arg0, s16**, 4)[i] = 0;
    }
}

void func_80029A64(s32, s32, s32, s32, Color_RGBA8);
extern Color_RGBA8 D_80073520;
void func_8002D948(Menu8002E230* menu, s32 x, s32 y) {
    s32 h = menu->rowSpacing; s32 row = menu->cursor * h + y + 2;
    func_80029A64(x + 2, row, menu->colSpacing - 4, h - 4, D_80073520);
}

void func_8002D9B8(Menu8002E230* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    u8** items;
    u8** item;
    s32 i;
    s32 flagOffset;
    s32 rowY;
    s32 count;
    s32 loopCount;
    s32 flags;
    MenuDef8002E230* def;

    def = menu->def;
    count = def->itemCount;
    loopCount = count;
    rowY = y;
    i = 0;
    items = (u8**)def->items;
    if (count > 0) {
        flagOffset = 0;
        item = items;
        do {
            flags = *(u16*)((u8*)menu->flags + flagOffset);
            if (i == menu->cursor) {
                flags |= 0x12;
            }
            menu->draw(x, rowY, *item, i, flags & mask, arg4);
            i++;
            flagOffset += 2;
            item++;
            rowY += menu->rowSpacing;
        } while (i != loopCount);
        count = menu->def->itemCount;
    }
    if (count > 0 && (mask & 2) && (menu->options & 0x10000)) {
        func_8002D948(menu, x, y);
    }
}

void func_8002DAD8(Menu8002E230* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    s32 count;
    u8* items;
    s32 i;
    s32 flagOffset;
    s32 rowY;
    s32 flags;
    MenuDef8002E230* def;

    def = menu->def;
    count = def->itemCount;
    rowY = y;
    i = 0;
    items = def->items;
    if (count > 0) {
        flagOffset = 0;
        do {
            flags = *(u16*)((u8*)menu->flags + flagOffset);
            if (i == menu->cursor) {
                flags |= 0x12;
            }
            menu->draw(x, rowY, items + def->itemSize * i, i, flags & mask, arg4);
            i++;
            flagOffset += 2;
            rowY += menu->rowSpacing;
        } while (i != count);
    }
    if (menu->def->itemCount > 0 && (mask & 2) && (menu->options & 0x10000)) {
        func_8002D948(menu, x, y);
    }
}

s32 func_8002DC04(Menu8002E230* menu) {
    s32 input = 0;
    s32 old = menu->cursor;
    if (menu->def->itemCount == 0) {
        return input;
    }
    input = Input_GetRepeatedDPad() & 0xFFFF;
    if (input != 0x400) {
        if (input == 0x800) {
            if (menu->cursor == 0) {
                menu->cursor += menu->def->itemCount;
            }
            menu->cursor--;
        }
    } else {
        if (menu->cursor >= menu->def->itemCount - 1) {
            menu->cursor -= menu->def->itemCount;
        }
        menu->cursor++;
    }
    if (old != menu->cursor) {
        Audio_PlaySoundEffectById(1);
    }
    return input;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002DCE0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002DCE0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002DDFC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002DDFC.s")
#endif

void func_8002DF2C(s8*, s32, s32);
void func_8002DECC(s8* arg0, s32 def, s32 flags, MenuDrawFunc8002E230 draw, s32 columns, s32 width, s32 height) {
    Menu8002E230* menu = (Menu8002E230*)arg0;
    menu->columns = columns;
    menu->colSpacing = width;
    menu->rowSpacing = height;
    menu->draw = draw;
    func_8002DF2C(arg0, def, flags);
    menu->repeatMask = 0xC00;
    menu->options = 0;
    menu->controller = gPlayer1Controller;
    Input_SetRepeatController(menu->controller);
}

void func_8002DF54(u8* arg0);

void func_8002DF2C(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    func_8002DF54((u8*)arg0);
}

void func_8002DF54(u8* arg0) {
    s32 i;

    for (i = 0; i < M2C_FIELD(M2C_FIELD(arg0, u8**, 0), s32*, 4); i++) {
        M2C_FIELD(arg0, s16**, 4)[i] = 0;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002DF9C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002DF9C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002E078; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002E078.s")
#endif

void func_8002DF9C(Menu8002E230*, s32, s32);
void func_8002E230(Menu8002E230* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    MenuDef8002E230* def = menu->def;
    s32 i;
    u8* items = def->items;
    u8* item;
    s32 f;

    for (i = 0; i < def->count; i++) {
        item = (i < def->itemCount) ? items + def->itemSize * i : NULL;
        f = menu->flags[i];
        if (i == menu->cursor) {
            f |= 0x12;
        }
        menu->draw(x + (i % menu->columns) * menu->colSpacing, y + (i / menu->columns) * menu->rowSpacing, item, i, f & mask, arg4);
    }
    if ((menu->def->itemCount > 0) && (mask & 2) && (menu->options & 0x10000)) {
        func_8002DF9C(menu, x, y);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002E3F0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002E3F0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002E70C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002E70C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002EC24; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002EC24.s")
#endif

void func_8002D900(u8* arg0);

void func_8002ED18(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    func_8002D900((u8*)arg0);
}

void func_8002ED50(s8 *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_v0 < M2C_FIELD(arg0, s32 *, 0x2C)) {
        M2C_FIELD(arg0, s32 *, 0x2C) = temp_v0;
    }
}

void func_8002ED70(s8 *arg0)
{
  s32 *new_var3;
  s32 *new_var2;
  int temp_v0;
  s8 *new_var;
  s32 *new_var4;
  new_var = (s8 *) arg0;
  new_var4 = (s32 *) (new_var + 0x34);
  new_var3 = &(*new_var4);
  temp_v0 = ((*(new_var2 = new_var3)) - ((*((s32 *) (((s8 *) arg0) + 0x24))) * (*((s32 *) (((s8 *) arg0) + 0x10))))) + 1;
  if ((*((s32 *) (((s8 *) arg0) + 0x2C))) < temp_v0)
  {
    *((s32 *) (new_var + 0x2C)) = temp_v0;
  }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002EDA8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002EDA8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002F030; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002F030.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002F32C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002F32C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002F3C4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002F3C4.s")
#endif

typedef struct ScrollMenu8002F6C4 {
    /* 0x00 */ MenuDef8002E230* def;
    /* 0x04 */ u16* flags;
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 width;
    /* 0x10 */ s32 rowSpacing;
    /* 0x14 */ MenuDrawFunc8002E230 draw;
    /* 0x18 */ char unk18[0x8];
    /* 0x20 */ s32 options;
    /* 0x24 */ s32 rows;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 scroll;
} ScrollMenu8002F6C4;
void func_8002EDA8(ScrollMenu8002F6C4*);
void func_8002F030(ScrollMenu8002F6C4*, s32, s32, s32, s32);
void func_8002F32C(ScrollMenu8002F6C4*, s32, s32);
void func_8002F6C4(ScrollMenu8002F6C4* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    MenuDef8002E230* def = menu->def;
    u8* items = def->items;
    s32 height = menu->rowSpacing * menu->rows;
    s32 i;
    s32 rowY;
    s32 end;
    u8* item;
    s32 f;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x, y, menu->width + x, y + height);
    func_8002EDA8(menu);
    rowY = y - menu->scroll % menu->rowSpacing;
    i = menu->scroll / menu->rowSpacing;
    end = (menu->scroll + height - 1) / menu->rowSpacing + 1;
    for (; i < end; i++) {
        item = NULL;
        f = 0;
        if (i < menu->def->itemCount) {
            item = items + def->itemSize * i;
            f = menu->flags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->draw(x, rowY, item, i, f & mask, arg4);
        rowY += menu->rowSpacing;
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        func_8002F030(menu, x, y - 16, y + menu->rowSpacing * menu->rows, menu->width);
    }
    if ((menu->def->itemCount > 0) && (mask & 2) && (menu->options & 0x10000)) {
        func_8002F32C(menu, x, y);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002F9D8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002F9D8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002FD8C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002FD8C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80030230; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80030230.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_800306E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800306E0.s")
#endif

void func_80030744(s32* arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    arg0[16] = 0;
    arg0[2] = arg1;
    temp_v0 = arg0[13] - arg0[11];
    arg0[13] = arg0[4] * arg1;

    temp_a2 = ((s32*)arg0[0])[2] - arg0[9];

    var_a1 = temp_a2 = (temp_a2 > 0) ? temp_a2 : 0;
    temp_a2 *= arg0[4];

    var_v0 = (arg0[13] - temp_v0 > 0) ? arg0[13] - temp_v0 : 0;

    var_v1 = (var_v0 < temp_a2) ? var_v0 : temp_a2;
    arg0[11] = var_v1;
    arg0[12] = var_v1;
}

void WidgetTree_SetPagedGridSelectionWithOffset(s8* arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_lo;
    s32 temp_v1;
    s32 var_v0_2;
    s8* temp_v0 = M2C_FIELD(arg0, s8**, 0);

    if (M2C_FIELD(temp_v0, s32*, 8) != 0) {
        M2C_FIELD(arg0, s32*, 0x40) = 0;
        temp_v1 = M2C_FIELD(temp_v0, s32*, 8) - 1;
        if (arg1 >= temp_v1) {
            arg1 = temp_v1;
        }
        M2C_FIELD(arg0, s32*, 8) = arg1;
        M2C_FIELD(arg0, s32*, 0x34) = M2C_FIELD(arg0, s32*, 0x10) * arg1;

        temp_a2 = M2C_FIELD(temp_v0, s32*, 8) - M2C_FIELD(arg0, s32*, 0x24);
        temp_lo = M2C_FIELD(arg0, s32*, 0x10) * ((temp_a2 > 0) ? temp_a2 : 0);

        temp_a2_2 = -(arg2 * M2C_FIELD(arg0, s32*, 0x10)) + M2C_FIELD(arg0, s32*, 0x34);
        if (temp_a2_2 > 0) {
            var_v0_2 = temp_a2_2;
        } else {
            var_v0_2 = 0;
        }

        temp_v1 = (var_v0_2 < temp_lo) ? var_v0_2 : temp_lo;
        M2C_FIELD(arg0, s32*, 0x2C) = temp_v1;
        M2C_FIELD(arg0, s32*, 0x30) = temp_v1;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_80030894; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80030894.s")
#endif

void func_8002D900(u8* arg0);

void func_800309D4(s8 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    func_8002D900((u8*)arg0);
}

void func_800309FC(s8 *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_v0 < M2C_FIELD(arg0, s32 *, 0x2C)) {
        M2C_FIELD(arg0, s32 *, 0x2C) = temp_v0;
    }
}

void func_80030A1C(s8 *arg0)
{
  s32 temp_v0;
  s8 *new_var;
  temp_v0 = ((*((s32 *) (((s8 *) arg0) + 0x34))) - ((*((s32 *) (((s8 *) arg0) + 0x24))) * (*((s32 *) (((s8 *) arg0) + 0x10))))) + 1;
  new_var = ((s8 *) arg0) + 0x2C;
  if ((*((s32 *) (((s8 *) arg0) + 0x2C))) < temp_v0)
  {
    *((s32 *) new_var) = temp_v0;
  }
}

#ifdef NON_MATCHING
/* TODO: decompile func_80030A54; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80030A54.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80030D3C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80030D3C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80031004; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80031004.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_800310D8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800310D8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80031464; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80031464.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8003152C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8003152C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80031AB0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80031AB0.s")
#endif

M2C_UNK func_8002DDFC();                            /* extern */
M2C_UNK func_80031AB0(s8 *, s32);                 /* extern */

void func_80031B88(s8 *arg0) {
    func_8002DDFC();
    func_80031AB0(arg0, M2C_FIELD(arg0, s32 *, 8));
}
