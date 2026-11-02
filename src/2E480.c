/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"

/**
 * Paged grid menu fields used by func_80031004, func_8002D948,
 * func_8002F32C and the other grid/list menu helpers. Offsets other than the ones
 * named here are unknown/unused by this function.
 */
typedef struct GridMenu80031004 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 cellWidth;
    /* 0x10 */ s32 cellHeight;
    /* 0x14 */ char unk14[0x16];
    /* 0x2A */ u16 flags;
    /* 0x2C */ s32 scroll;
    /* 0x30 */ char unk30[0x4];
    /* 0x34 */ s32 scrollTarget;
    /* 0x38 */ char unk38[0x10];
    /* 0x48 */ s32 columns;
} GridMenu80031004;

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
    /* 0x18 */ char unk18[0x8];
    /* 0x20 */ s32 options;
    /* 0x24 */ s32 columns;
} Menu8002E230;

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
void func_8002F32C(GridMenu80031004*, s32, s32);

extern u8 D_80073520[];
M2C_UNK func_80029A64(s32, s32, s32, s32, Color_RGBA8);

#ifdef NON_MATCHING
/* TODO: decompile func_8002D880; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002D880.s")
#endif

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

/**
 * Draws the cursor rectangle (via func_80029A64) for a list menu with one cell per row:
 * x = arg1 + 2, y = cursor * cellHeight + arg2 + 2, size = (cellWidth - 4) x (cellHeight - 4),
 * colour read from D_80073520. Compare func_8002F32C and func_80031004. The separate `y`
 * local only fixes the order in which the fields are loaded.
 */
void func_8002D948(GridMenu80031004* arg0, s32 arg1, s32 arg2) {
    s32 y;

    y = arg0->cursor * arg0->cellHeight + arg2 + 2;
    func_80029A64(arg1 + 2, y, arg0->cellWidth - 4, arg0->cellHeight - 4, *(Color_RGBA8*)D_80073520);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002D9B8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002D9B8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002DAD8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002DAD8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8002DC04; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002DC04.s")
#endif

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
extern s32 D_800603C0;
M2C_UNK func_8000B2F4(s32);

/**
 * Initialises a menu object at arg0: stores arg4, arg5, arg6 and arg3 at
 * offsets 0x24, 0x0C, 0x10 and 0x14, calls func_8002DF2C(arg0, arg1, arg2),
 * sets offset 0x1C to 0xC00 and offset 0x20 to 0, then stores D_800603C0 at
 * offset 0x18 and passes it to func_8000B2F4. What the fields mean is not
 * established.
 */
void func_8002DECC(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    M2C_FIELD(arg0, s32*, 0x24) = arg4;
    M2C_FIELD(arg0, s32*, 0xC) = arg5;
    M2C_FIELD(arg0, s32*, 0x10) = arg6;
    M2C_FIELD(arg0, s32*, 0x14) = arg3;
    func_8002DF2C(arg0, arg1, arg2);
    M2C_FIELD(arg0, s32*, 0x1C) = 0xC00;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    func_8000B2F4(M2C_FIELD(arg0, s32*, 0x18) = D_800603C0);
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

/**
 * Draws the cursor rectangle (via func_80029A64) for a multi-column menu: the cursor cell is
 * at column cursor % columns, row cursor / columns, so x = column * colSpacing + arg_x + 2 and
 * y = row * rowSpacing + arg_y + 2; the size is (colSpacing - 4) x (rowSpacing - 4) and the
 * colour is read from D_80073520. Compare func_80031004. The `px`/`py` locals only fix the
 * evaluation order of the argument expressions.
 */
void func_8002DF9C(Menu8002E230* menu, s32 x, s32 y) {
    s32 px;
    s32 py;

    px = (menu->cursor % menu->columns) * menu->colSpacing + x + 2;
    py = (menu->cursor / menu->columns) * menu->rowSpacing + y + 2;
    func_80029A64(px, py, menu->colSpacing - 4, menu->rowSpacing - 4, *(Color_RGBA8*)D_80073520);
}

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

/**
 * Draws the cursor rectangle (via func_80029A64) for a scrolling list menu. Same shape as
 * func_80031004 but with x = arg1 + 2 (no column calculation) and the rectangle size taken from
 * cellWidth/cellHeight minus 4: y = scrollTarget + arg2 - scroll + 2, and when flag 0x400 is
 * set, (cellHeight - 1) is subtracted from it. The colour argument is read from D_80073520.
 * Matching note: the redundant (s32) cast on arg2 only fixes the operand order of the addu.
 */
void func_8002F32C(GridMenu80031004* arg0, s32 arg1, s32 arg2) {
    s32 sp2C;

    sp2C = (s32)arg2 + arg0->scrollTarget - arg0->scroll + 2;
    if (arg0->flags & 0x400) {
        sp2C = sp2C - arg0->cellHeight + 1;
    }
    func_80029A64(arg1 + 2, sp2C, arg0->cellWidth - 4, arg0->cellHeight - 4, *(Color_RGBA8*)D_80073520);
}

/**
 * Draws a scrolling list menu whose entries are an array of words (def->items[i], passed to the
 * draw callback by value as the entry argument) rather than fixed-size records -- compare
 * func_8002F6C4, which indexes records by def->itemSize. Sets the scissor rectangle to the
 * menu area (x, y, width x rows * rowSpacing), calls func_8002EDA8, then draws every visible
 * row i (from scroll / rowSpacing) through menu->draw(x, rowY, entry, i, flags & mask, arg4),
 * where the flags halfword for row i comes from menu->flags and is OR'd with 0x12 for the
 * cursor row; rows at or past def->itemCount get entry 0 and flags 0. Afterwards the scissor
 * is restored to the full 640x480 screen, func_8002F030 draws when option bit 0x100000 is set
 * and func_8002F32C (cursor box) draws when mask bit 2, option bit 0x10000 and a non-empty
 * list agree.
 */
void func_8002F3C4(ScrollMenu8002F6C4* menu, s32 x, s32 y, s32 mask, s32 arg4) {
    s32 height = menu->rowSpacing * menu->rows;
    s32 i;
    s32 rowY;
    s32 end;
    s32 item;
    s32 f;
    s32* items = (s32*)menu->def->items;

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x, y, menu->width + x, y + height);
    func_8002EDA8(menu);
    rowY = y - menu->scroll % menu->rowSpacing;
    i = menu->scroll / menu->rowSpacing;
    end = (menu->scroll + height - 1) / menu->rowSpacing + 1;
    for (; i < end; i++) {
        item = 0;
        f = 0;
        if (i < menu->def->itemCount) {
            item = items[i];
            f = menu->flags[i];
            if (i == menu->cursor) {
                f |= 0x12;
            }
        }
        menu->draw(x, rowY, (u8*)item, i, f & mask, arg4);
        rowY += menu->rowSpacing;
    }
    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    if (menu->options & 0x100000) {
        func_8002F030(menu, x, y - 16, y + menu->rowSpacing * menu->rows, menu->width);
    }
    if ((menu->def->itemCount > 0) && (mask & 2) && (menu->options & 0x10000)) {
        func_8002F32C((GridMenu80031004*)menu, x, y);
    }
}

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


/**
 * Draws a rectangle (via func_80029A64) for the cursor of a paged grid menu.
 * The column is cursor % columns, so x = column * cellWidth + arg1. y is
 * scrollTarget + arg2 - scroll + 2; when flag 0x400 is set, (cellHeight - 1)
 * is subtracted from it. The rectangle size is the cell size minus 4 in each
 * direction, and the colour argument is read from D_80073520.
 */
void func_80031004(GridMenu80031004* arg0, s32 arg1, s32 arg2) {
    s32 sp2C;
    s32 sp28;

    sp2C = arg0->scrollTarget + arg2 - arg0->scroll + 2;
    sp28 = (arg0->cursor % arg0->columns) * arg0->cellWidth + arg1;
    if (arg0->flags & 0x400) {
        sp2C = sp2C - arg0->cellHeight + 1;
    }
    func_80029A64(sp28, sp2C, arg0->cellWidth - 4, arg0->cellHeight - 4, *(Color_RGBA8*)D_80073520);
}

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
