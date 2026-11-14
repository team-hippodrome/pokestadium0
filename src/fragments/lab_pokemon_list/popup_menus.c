/* Stadium Zero fragment016_252E10. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_list/lab_pc_list_1D7B40.c. */

#include "lab_pokemon_list.h"
#include "font.h"
#include "graphics_textures.h"
extern u8 D_8910D7D0[];
typedef struct unk_func_88309614 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
} unk_func_88309614;
typedef struct unk_func_88313894 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ unk_func_8830867C_02C_0CC_000_000* unk_0C;
    /* 0x10 */ char unk10[0xC];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ unk_func_88313894_020 unk_20;
    /* 0x40 */ unk_func_88313894_020 unk_40;
} unk_func_88313894;

#include "m2c_macros.h"

void func_8001A384(s32, s32);
void func_8001A944(s32 x, s32 y, const char* fmt, ...);
void func_8001AB6C(void);
void func_8001ABBC(void);
void func_891053E0(void);
void func_89108F0C(void);

extern Color_RGBA8 D_8910A910;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);

void func_89104C70(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 temp_v0 = *arg5;

    if (arg4 & 8) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x16, D_8910A910);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

typedef struct Str89104D14 { s8 c[4]; } Str89104D14;
extern Str89104D14 D_8910A914;
void func_80027804(s8 *, s32 *, s32, s32);
void Window_SetRect(s8 *, s32, s32, s32, s32);
void Menu_Init(s8 *, s8 *, s32, void *, s32, s32);
u32 func_800566BC(s32);
void func_89104C70();
void func_89104D14(s8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4, s32 arg5) {
    s32 i;
    s32 w;
    s32 max = 0;
    s32 h;

    for (i = 0; i < arg5; i++) {
        w = func_800566BC(arg3[i]) >> 1;
        if (max < w) {
            max = w;
        }
    }
    func_80027804(arg0 + 0x50, arg3, arg5, arg5);
    h = max * 0x14 + 0x10;
    Menu_Init(arg0 + 0x2C, arg0 + 0x50, arg4, func_89104C70, h, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x4C) |= 0x10000;
    Window_SetRect(arg0, arg1, arg2, h + 0xC, 0x84);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, Str89104D14 *, 0x18) = D_8910A914;
}

s32 func_8002AE6C();
M2C_UNK Menu_DrawItems(s32, s32, s32, s32, s8*);

typedef struct Box89104E38 {
    s32 x;
    s32 y;
    s32 w;
    char padC[0x20];
    s8 label[1];
} Box89104E38;

void func_89104E38(Box89104E38* arg0) {
    s32 label;

    if (func_8002AE6C() == 0) {
        s32 sp2C[4];

        sp2C[0] = arg0->w - 0xC;
        label = (s32)arg0->label;
        Menu_DrawItems(label, arg0->x + 6, arg0->y + 0xA, 0xFFEF, (s8*)sp2C);
    }
    /* Empty test kept from the permuter: it keeps arg0 in $s0 as in the ROM. */
    if (arg0) {  // karodo
    }
}

M2C_UNK Menu_UpdateCursor(s32);                         /* extern */

void func_89104E94(s32 arg0) {
    Menu_UpdateCursor(arg0 + 0x2C);
}

typedef struct Entry891078E0 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry891078E0;
extern Entry891078E0 D_8006A9D4[];
extern Color_RGBA8 D_800734A8[];
extern char D_8910E000[];
extern char D_8910E010[];

void func_89104EB4(s32 arg0, s32 arg1, s32* arg2, s32 arg3, s32 arg4, s32* arg5) {
    UNUSED s32 padA[4]; // FAKE: stack padding
    const char* name;
    s32 temp;
    s32 alpha;

    temp = *arg2;
    switch (temp) {
        case -2:
            name = D_8910E000;
            break;
        case -1:
            name = D_8910E010;
            break;
        default:
            name = D_8006A9D4[temp].name;
            break;
    }
    Font_BeginTranslucentTextRendering();
    if (arg4 & 0x100) {
        Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, *arg5);
    } else if (arg4 & 0x200) {
        alpha = *arg5;
        Gfx_SetEnvColor(0xFF, 0xC8, 0xC8, alpha);
    } else {
        Font_SetColorForFlags(arg4);
    }
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, name);
    Font_EndTexturedTextRendering();
}

typedef struct Str89104FC0 { s8 c[4]; } Str89104FC0;
extern Str89104FC0 D_8910A91C;
s32 BattleMon_CountMoves(u8* arg0);
s32 BattleMon_GetMoveIndex(s32, s32);
void func_80027410(void*, void*, s32, s32, s32);
void func_89104EB4();

void func_89104FC0(LabMoveSelectWindow* arg0, s32 arg1, s32 arg2, u8* arg3) {
    s32 n = BattleMon_CountMoves(arg3);
    s32 i;

    for (i = 0; i < n; i++) {
        arg0->moves[i] = BattleMon_GetMoveIndex((s32)arg3, i);
    }
    for (i = n; i < 4; i++) {
        arg0->moves[i] = -1;
    }
    func_80027410(&arg0->moveMatrix, arg0->moves, 4, 4, 4);
    Menu_Init(&arg0->menu, &arg0->moveMatrix, (s32)arg0->itemFlags, func_89104EB4, 0x9C, 0x1C);
    arg0->menu.options |= 0x10000;
    Window_SetRect(&arg0->window, arg1, arg2, 0xA8, 0x84);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0;
    *(Str89104FC0*)&arg0->window.frame.color = D_8910A91C;
}

extern s32 D_8910A920[5];
/** Disables the move list entries that are restricted for the current cup. */
void BattleMoveListWidget_DisableRestrictedMoves(LabMoveSelectWindow* arg0) {
    s32 j;
    s32 i;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (arg0->moves[i] == D_8910A920[j]) {
                arg0->itemFlags[i] |= 1;
                break;
            }
        }
    }
}

M2C_UNK Menu_DrawInlineItems(s8*, s32, s32, s32, s8*);

void func_891051A4(LabMoveSelectWindow* arg0) {
    Menu* label;

    if (func_8002AE6C() == 0) {
        s32 sp2C[4];

        sp2C[0] = arg0->window.frame.width - 0xC;
        label = &arg0->menu;
        Menu_DrawInlineItems(label, arg0->window.frame.x + 6, arg0->window.frame.y + 0xA, 0xFFEF, (s8*)sp2C);
    }
    /* Empty test kept from the permuter: it keeps arg0 in $s0 as in the ROM. */
    if (arg0) {  // karodo
    }
}

M2C_UNK func_8003F6AC(M2C_UNK);

s32 func_89105200(LabMoveSelectWindow* arg0) {
    s32 color;
    s32 params[4]; // only params[0] (alpha) is set here, as in func_891051A4

    if (func_8002AE6C() != 0) {
        return 0;
    }
    if (arg0->learnTimer > 0) {
        arg0->learnTimer--;
    }
    if (arg0->learnTimer >= 30) {
        color = 0xFDED;
        params[0] = (arg0->learnTimer * 0xFF - 30 * 0xFF) / 30;
    } else {
        if (arg0->learnTimer == 29) {
            arg0->moves[arg0->learnSlot] = arg0->learnMove;
            func_8003F6AC(0x22);
        }
        color = 0xFEED;
        params[0] = ((30 - arg0->learnTimer) * 0xFF) / 30;
    }
    Menu_DrawInlineItems(&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 0xA, color, (s8*)params);
    return arg0->learnTimer == 0;
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_89105340(s8 *arg0, s32 arg1, s32 arg2)
{
  u16 *temp_v0;
  int new_var; // FAKE: permuter temp
  *((s32 *) (((s8 *) arg0) + 0x7C)) = arg1;
  new_var = arg1 * 4;
  *((s32 *) (((s8 *) arg0) + 0x80)) = (s32) (arg2 - 1);
  if ((*((s32 *) (((s8 *) (arg0 + new_var)) + 0x60))) == (-1))
  {
    *((s32 *) (((s8 *) arg0) + 0x78)) = 0x3C;
  }
  else
  {
    *((s32 *) (((s8 *) arg0) + 0x78)) = 0x3C;
  }
  temp_v0 = (*((s32 *) (((s8 *) arg0) + 0x30))) + (arg1 * 2);
  *temp_v0 |= 0x300;
}

M2C_UNK Menu_UpdateCursor(s32);                         /* extern */

s32 func_89105390(s32 arg0) {
    return Menu_UpdateCursor(arg0 + 0x2C);
}

s32 func_891053B0(s8 *arg0) {
    s32 var_v1;

    var_v1 = 0x100;
    if (M2C_FIELD(arg0, s32 *, 0xC) != 0) {
        var_v1 = 0x108;
    }
    if (M2C_FIELD(arg0, s32 *, 0x1C) > 0) {
        var_v1 &= ~0x100;
    }
    return var_v1;
}

void func_891053E0(void) {
}

/** Updates the flags of every entry in the info widget. */
void BattleInfoWidget_UpdateEntryFlags(LabBoxListWindow* arg0) {
    s32 i;
    ByteMatrix** sub = &arg0->menu.items;
    s8* var_s2 = (*sub)->rows;

    for (i = 0; i < (*sub)->count; i++, var_s2 += 0x20) {
        arg0->menu.itemFlags[i] = 0;
        arg0->menu.itemFlags[i] |= func_891053B0(var_s2);
    }
}

/* Set or clear bit 3 in every laboratory list entry flag. */
void func_8910548C(u8* widget, s32 enabled) {
    s32 value = enabled ? 8 : 0;
    s32 offset;
    s32 index;
    s32* list;
    u16* flags;

    list = *(s32**)(widget + 0x20);
    index = 0;
    if (list[2] > 0) {
        offset = 0;
        do {
            index++;
            flags = (u16*)(*(u8**)(widget + 0x24) + offset);
            *flags &= ~8;
            flags = (u16*)(*(u8**)(widget + 0x24) + offset);
            *flags |= value;
            offset += 2;
        } while (index < *(s32*)(*(u8**)(widget + 0x20) + 8));
    }
}

void func_89105504(LabBoxListWindow* arg0) {
    s32 i;
    s32* entry = (s32*)arg0->menu.items->rows;

    for (i = 0; i < arg0->menu.items->count; i++) {
        entry[3] = (arg0->menu.itemFlags[i] & 8) != 0;
        entry += 8;
    }
}

void Ui_DrawImageInStrips(void*, s32, s32);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
extern u8 D_80073614[];
extern u8 D_80073624[];
extern Color_RGBA8 D_80073520;
extern Color_RGBA8 D_8910A934[];
extern Color_RGBA8 D_800734A8[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_8910CF80[];
extern char D_8910E018[];
/**
 * Draws ボックス%d (Box %d).
 * Seen in play (2026-11-12): ボックス1 ... ボックス4 in the 64カセットのボックス submenu.
 */
void PcSort_DrawBoxName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Color_RGBA8 color;
    s32 pad[6]; // FAKE: stack padding
    s32 sel;

    if (arg4 & 8) {
        Ui_DrawImageInStrips(D_80073614, arg0 + 8, arg1 + 4);
    } else {
        Ui_DrawImageInStrips(D_80073624, arg0 + 8, arg1 + 4);
    }
    sel = arg4 & 2;
    if (sel) {
        Ui_DrawRoundedFrame(arg0 + 0x2A, arg1 + 2, 0x70, 0x18, D_80073520);
        gSPDisplayList(gDisplayListHead++, D_80060290);
        func_8001B884(arg0 + 0x1D, arg1 + 5, 0xB, 0x12, D_8910CF80, 0xC, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
    if (arg4 & 0x100) {
        color = D_8910A934[sel ? 0 : 1];
    } else {
        color = D_800734A8[sel ? 0 : 1];
    }
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x30, arg1 + 4, D_8910E018, arg3 + 1);
    Font_EndTexturedTextRendering();
}


void PcSort_DrawBoxName();

void func_8910576C(LabBoxListWindow* arg0, s32 arg1, s32 arg2, ByteMatrix* arg3, s32 arg4, Color_RGBA8 arg5) {
    Window_SetRect(&arg0->frame, arg1, arg2, 0x9C, arg3->count * 0x1C + 8);
    arg0->frame.style = 0;
    arg0->frame.color = arg5;
    Menu_Init(&arg0->menu, arg3, arg4, PcSort_DrawBoxName, 0x9C, 0x1C);
    BattleInfoWidget_UpdateEntryFlags(arg0);
}

M2C_UNK Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, M2C_UNK *); /* extern */
M2C_UNK Window_DrawFrame(s8 *);                      /* extern */
M2C_UNK Menu_DrawInlineItems(s8 *, s32, s32, s32, s8 *); /* extern */
extern M2C_UNK D_80073554;

void func_891057FC(LabBoxListWindow* arg0, s32 arg1) {
    Ui_DrawTexturedFrameDecal(arg0->frame.x - 6, arg0->frame.y - 6, arg0->frame.width + 0xC, arg0->frame.height + 0xC, &D_80073554);
    Window_DrawFrame(&arg0->frame);
    Menu_DrawInlineItems(&arg0->menu, arg0->frame.x, arg0->frame.y + 4, arg1 | 0xFFED, arg0);
}

M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;

/**
 * List-menu input handler (same family as PartyScreen_UpdateActionMenu). arg0 is the menu object (passed as
 * an integer address here, as elsewhere in this file). Calls Menu_UpdateCursor(arg0 + 0x20) and
 * acts on its result: 0x200 plays sound func_8003F6AC(1) and returns 2. 0 reads the button
 * halfword at D_800603C0 + 8: if bit 0x8000 is set it plays sound 2, toggles bit 3 of the
 * halfword table entry arg0->0x24[arg0->0x28] and returns 1; otherwise if bit 0x4000 is set it
 * plays sound 3 and returns -1. Any other case returns 0. (The button-bit names are not
 * established, so they are left as raw masks.)
 */
s32 func_8910587C(LabBoxListWindow* arg0) {
    s32 ret = 0;
    s32 res;
    s32 buttons;
    u16* entry;

    res = Menu_UpdateCursor(&arg0->menu);
    if (res == 0x200) {
        func_8003F6AC(1);
        ret = 2;
    } else if (res == 0) {
        buttons = ((u16*)D_800603C0)[4];
        if (buttons & 0x8000) {
            func_8003F6AC(2);
            ret = 1;
            arg0->menu.itemFlags[arg0->menu.cursor] ^= 8;
        } else if (buttons & 0x4000) {
            func_8003F6AC(3);
            ret = -1;
        }
    }
    return ret;
}

typedef struct Entry89105924 { char unk00[0xC]; s32 unk0C; char unk10[0xC]; s32 unk1C; } Entry89105924;
typedef struct List89105924 { char unk00[0x10]; Entry89105924* entries; char unk14[4]; s32 count; } List89105924;
s32 func_89105924(List89105924* arg0) {
    Entry89105924* entries = arg0->entries;
    s32 flags = 0x100;
    s32 i;
    for (i = 0; i < arg0->count; i++) {
        if (entries[i].unk0C != 0) {
            flags |= 8;
        }
        if (entries[i].unk1C > 0) {
            flags &= ~0x100;
        }
    }
    return flags;
}

void func_8910597C(LabSourceSelectWindow* arg0, LabBoxListWindow* arg1) {
    s32 flag = 0;
    s32 i = 0;
    s32 count = arg1->menu.items->count;
    u16* items;

    if (count > 0) {
        if (!arg0) {} // fake, keeps arg0 live in a saved register
        items = arg1->menu.itemFlags;
        do {
            i++;
            if (*items & 8) {
                flag = 8;
                break;
            }
            items++;
        } while (i < count);
    }
    arg0->menu.itemFlags[arg0->menu.cursor] &= ~8;
    arg0->menu.itemFlags[arg0->menu.cursor] |= flag;
}

/* Rebuild entry flags from the current laboratory records. */
void func_891059FC(u8* widget) {
    s32 offset;
    s32 entry = (*(s32**)(widget + 0x70))[0];
    s32 index;
    s32* list;
    s32 flags;
    u16* destination;

    list = *(s32**)(widget + 0x70);
    offset = 0;
    index = 0;

    if (list[2] > 0) {
        do {
            *(u16*)(*(u8**)(widget + 0x74) + offset) = 0;
            flags = func_89105924((List89105924*)entry);
            index++;
            entry += 0x24;
            destination = (u16*)(*(u8**)(widget + 0x74) + offset);
            *destination |= flags;
            offset += 2;
        } while (index < *(s32*)(*(u8**)(widget + 0x70) + 8));
    }
}

/** Applies the selection state to an info widget entry. */
void BattleInfoWidget_ApplyEntrySelection(LabSourceSelectWindow* arg0, s32 arg1) {
    s8* ptr = (s8*)arg0->menu.items->rows + arg1 * 0x24;
    s8* ptr2 = M2C_FIELD(ptr, s8**, 0x10);

    M2C_FIELD(ptr2, s32*, 0xC) = (arg0->menu.itemFlags[arg1] & 8) != 0;
}

void Ui_DrawImageInStrips(void*, s32, s32);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
extern u8 D_80073614[];
extern u8 D_80073624[];
extern Color_RGBA8 D_80073520;
extern Color_RGBA8 D_8910A934[];
extern Color_RGBA8 D_800734A8[];
void func_89105AD4(s32 arg0, s32 arg1, char** arg2, s32 arg3, s32 arg4) {
    Color_RGBA8 color;
    s32 pad[5]; // FAKE: stack padding
    s32 sel;

    if (arg4 & 8) {
        Ui_DrawImageInStrips(D_80073614, arg0 + 8, arg1 + 4);
    } else {
        Ui_DrawImageInStrips(D_80073624, arg0 + 8, arg1 + 4);
    }
    sel = arg4 & 2;
    if (sel) {
        Ui_DrawRoundedFrame(arg0 + 0x2A, arg1 + 2, 0xE8, 0x18, D_80073520);
    }
    if (arg4 & 0x100) {
        color = D_8910A934[sel ? 0 : 1];
    } else {
        color = D_800734A8[sel ? 0 : 1];
    }
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x30, arg1 + 4, *arg2);
    Font_EndTexturedTextRendering();
}

void Window_InitLabeled(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5);
void func_89105AD4(s32 arg0, s32 arg1, char** arg2, s32 arg3, s32 arg4);
void func_891059FC(u8* widget);
void func_8000B2F4(s32);
extern s32 D_800603C0;
extern Color_RGBA8 D_8910A93C;
extern Color_RGBA8 D_8910A940;
extern char D_8910E024[];
void func_89105C54(LabSourceSelectWindow* arg0, s32 arg1, s32 arg2, s8* arg3, Color_RGBA8 arg4) {
    s32 pad[5]; // FAKE: stack padding
    s32 list;

    Window_SetRect(&arg0->window, arg1, arg2, 0x134, 0xCE);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 1;
    arg0->window.frame.color = arg4;
    Window_SetRect(&arg0->textFrame, arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, 0x40);
    arg0->textFrame.style = 6;
    arg0->textFrame.color = D_8910A93C;
    arg0->textFrame.color2 = D_8910A940;
    Window_SetRect(&arg0->listFrame, arg0->window.frame.x + 6, arg0->window.frame.y + 0x4C, arg0->window.frame.width - 0xC, 0x7C);
    arg0->listFrame.style = 0;
    arg0->listFrame.color = arg4;
    Window_InitLabeled(&arg0->okButton, arg0->listFrame.x + 0x70, arg0->listFrame.y + 0x5C, 0x48, arg4, D_8910E024);
    arg0->okButton.labelX = 0xA;
    arg0->okButton.unk_34 = 0xC;
    list = *(s32*)arg3;
    func_8910576C(&arg0->gbBoxes, arg0->window.frame.x + arg0->window.frame.width, arg0->listFrame.y + 0x1C, (ByteMatrix*)(list + 0x34), (s32)(&arg0->gbBoxFlags), arg4);
    func_8910576C(&arg0->cartBoxes, arg0->window.frame.x + arg0->window.frame.width, arg0->listFrame.y + 0x38, (ByteMatrix*)(list + 0x58), (s32)(&arg0->cartBoxFlags), arg4);
    Menu_Init(&arg0->menu, arg3, (s32)(&arg0->itemFlags), func_89105AD4, 0x128, 0x1C);
    func_891059FC((u8*)arg0);
    arg0->cursor.count = 4;
    arg0->cursor.cursor = 0;
    arg0->cursor.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->cursor.cursor = 3;
    arg0->openBoxList = 0;
}

void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Window_DrawLabeled(s8 *, s32);
extern u8 D_8007356C[];
extern Color_RGBA8 D_800734A8[];
extern char D_8910E02C[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_8910D138[];
void func_89105E70(LabSourceSelectWindow* arg0, s32 arg1) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s32 sp38 = 0xFFED;
    s32 sp34 = 0;

    if (func_8002AE6C(&arg0->window) == 0) {
        Window_DrawFrame(&arg0->textFrame);
        Window_DrawFrame(&arg0->listFrame);
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x45, arg0->window.frame.width, D_8007356C);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(arg0->textFrame.x + 8, arg0->textFrame.y + 8, D_8910E02C);
        Font_EndTexturedTextRendering();
        if ((arg1 & 2) && (arg0->openBoxList == 0)) {
            if (arg0->cursor.cursor == 3) {
                sp34 = 2;
            } else {
                sp38 = 0xFFEF;
                if ((arg0->cursor.cursor == 1) || (arg0->cursor.cursor == 2)) {
                    gSPDisplayList(gDisplayListHead++, D_80060290);
                    func_8001B884((arg0->listFrame.x + arg0->listFrame.width) - 0x11, arg0->listFrame.y + (arg0->cursor.cursor * 0x1C) + 9, 0xB, 0x12, D_8910D138, 0xC, 0x200000);
                    gSPDisplayList(gDisplayListHead++, D_80060398);
                }
            }
        }
        Menu_DrawInlineItems(&arg0->menu, arg0->listFrame.x, arg0->listFrame.y + 4, sp38, arg0);
        Window_DrawLabeled(&arg0->okButton, sp34);
        if (arg0->cursor.cursor == 1) {
            func_891057FC(&arg0->gbBoxes, (arg0->openBoxList == 1) ? 2 : 0);
        } else if (arg0->cursor.cursor == 2) {
            func_891057FC(&arg0->cartBoxes, (arg0->openBoxList == 2) ? 2 : 0);
        }
    }
}

s32 func_8002B2B0(s8*);

s32 func_891060BC(LabSourceSelectWindow* arg0) {
    s32 ret = 0;
    s32 res;
    s32 buttons;

    res = func_8002B2B0(&arg0->cursor);
    if (res == 0x100) {
        if (arg0->cursor.cursor == 1) {
            func_8003F6AC(1);
            arg0->openBoxList = 1;
        } else if (arg0->cursor.cursor == 2) {
            func_8003F6AC(1);
            arg0->openBoxList = 2;
        }
    } else if (res == 0) {
        buttons = ((u16*)D_800603C0)[4];
        if (buttons & 0x8000) {
            if (arg0->cursor.cursor == 3) {
                func_8003F6AC(2);
                BattleInfoWidget_ApplyEntrySelection(arg0, 0);
                func_89105504(&arg0->gbBoxes);
                func_89105504(&arg0->cartBoxes);
                ret = 1;
            } else {
                func_8003F6AC(2);
                arg0->menu.itemFlags[arg0->menu.cursor] ^= 8;
                if (arg0->cursor.cursor == 1) {
                    func_8910548C((u8*)(&arg0->gbBoxes), arg0->menu.itemFlags[arg0->menu.cursor] & 8);
                } else if (arg0->cursor.cursor == 2) {
                    func_8910548C((u8*)(&arg0->cartBoxes), arg0->menu.itemFlags[arg0->menu.cursor] & 8);
                }
            }
        } else if (buttons & 0x4000) {
            func_8003F6AC(3);
            ret = -1;
        }
    }
    if (arg0->cursor.cursor < 4) {
        arg0->menu.cursor = arg0->cursor.cursor;
    }
    return ret;
}

s32 func_89106254(LabSourceSelectWindow* arg0) {
    s32 ret = 0;
    s32 r;

    if (arg0->window.state == 0) {
        return 0;
    }
    switch (arg0->openBoxList) {
        case 0:
            ret = func_891060BC(arg0);
            break;
        case 1:
            r = func_8910587C(&arg0->gbBoxes);
            if (r == -1) {
                ret = -1;
            } else if (r == 1) {
                func_8910597C(arg0, &arg0->gbBoxes);
            } else if (r == 2) {
                arg0->openBoxList = 0;
            }
            break;
        case 2:
            r = func_8910587C(&arg0->cartBoxes);
            if (r == -1) {
                ret = -1;
            } else if (r == 1) {
                func_8910597C(arg0, &arg0->cartBoxes);
            } else if (r == 2) {
                arg0->openBoxList = 0;
            }
            break;
    }
    return ret;
}

/**
 * Draws one popup menu row with the selection highlight.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): drew the popup rows, with
 * the highlight on the selected one.
 */
void LabPCList_DrawPopupRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s8* arg5) {
    s32 temp_v0 = M2C_FIELD(arg5, s32*, 8) - 0xC;

    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x16, M2C_FIELD(arg5, Color_RGBA8*, 0x18));
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

/**
 * Sets up a popup menu sized to its widest string.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): A on フシギダネ set up the popup
 * (フシギダネをあつめる, おなじタイプをあつめる, いどうする, どうぐをつかう).
 */
void LabPCList_InitPopupMenu(LabPopupMenu* arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 w;
    s32 max = 0;
    s32 h;

    arg0->title = arg4;
    for (i = 0; i < arg3; i++) {
        w = func_800566BC(arg1[i]) >> 1;
        if (max < w) {
            max = w;
        }
    }
    func_80027804((s8*)&arg0->itemList, arg1, arg3, arg3);
    h = max * 0x14 + 0x10;
    Menu_Init((s8*)&arg0->menu, (s8*)&arg0->itemList, arg2, LabPCList_DrawPopupRow, h, 0x1C);
    arg0->menu.options |= 0x10000;
    Window_SetRect(arg0, 0, 0, h + 0xC, arg0->itemList.count * 0x1C + 0x14);
    arg0->window.animTimer = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    arg0->window.state = 0;
    if (arg4 != 0) {
        arg0->window.frame.style = 0x800;
    } else {
        arg0->window.frame.style = 0;
    }
    if (arg4 != 0) {
        M2C_FIELD(arg0, s32 *, 0x20) = arg4;
    }
}


/**
 * LabPCList_PlacePopup
 *
 * Places a popup next to its anchor rectangle while keeping it inside the
 * limits at +0x74/+0x78.  With flag 0x01000000 it goes to the right of the
 * anchor (or to its left when that would overflow) and is pushed up by the
 * overflow, at least 8; otherwise it goes below the anchor (or above it) and
 * is pushed left the same way.  Field names describe that geometry only.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): placed that popup over the
 * list next to the selected row.
 */
void LabPCList_PlacePopup(LabPopupMenu* arg0) {
    s32 over;

    if (arg0->window.frame.style & 0x01000000) {
        if (arg0->limitY >= arg0->anchorY + arg0->window.frame.height) {
            arg0->window.frame.y = arg0->anchorY;
        } else {
            over = (arg0->anchorY + arg0->window.frame.height) - arg0->limitY;
            arg0->window.frame.y = arg0->anchorY - ((over > 8) ? over : 8);
        }
        if (arg0->limitX >= arg0->anchorX + arg0->anchorW + arg0->window.frame.width) {
            arg0->window.frame.x = arg0->anchorX + arg0->anchorW;
        } else {
            arg0->window.frame.x = arg0->anchorX - arg0->window.frame.width;
        }
    } else {
        if (arg0->limitX >= arg0->anchorX + arg0->window.frame.width) {
            arg0->window.frame.x = arg0->anchorX;
        } else {
            over = (arg0->anchorX + arg0->window.frame.width) - arg0->limitX;
            arg0->window.frame.x = arg0->anchorX - ((over > 8) ? over : 8);
        }
        if (arg0->limitY >= arg0->anchorY + arg0->anchorH + arg0->window.frame.height) {
            arg0->window.frame.y = arg0->anchorY + arg0->anchorH;
        } else {
            arg0->window.frame.y = arg0->anchorY - arg0->window.frame.height;
        }
    }
    arg0->window.animTimer = 0;
}

s32 func_8002AE6C();                                /* extern */
M2C_UNK Menu_DrawItems(s32, s32, s32, s32, s8 *);  /* extern */
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Draws a popup menu's items.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): drew that popup's four rows.
 */
void LabPCList_DrawPopupMenu(LabPopupMenu* arg0, s32 arg1)
{
  s8 *new_var; // FAKE: permuter temp
  if (func_8002AE6C() == 0)
  {
    new_var = (s8 *) arg0;
    if ((arg0 && arg0) && arg0)
    {
    }
    Menu_DrawItems((s8*)&arg0->menu, (*((s32 *) (((s8 *) arg0) + 0))) + 6, (*((s32 *) (new_var + 4))) + 0xA, arg1 | 0xFFED, arg0); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    if (arg1)
    {
    }
  }
}

M2C_UNK Menu_UpdateCursor(s32);                         /* extern */

/**
 * Moves a popup menu's cursor.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): D-Down twice moved the popup
 * cursor from フシギダネをあつめる to いどうする.
 */
s32 LabPCList_UpdatePopupMenu(LabPopupMenu* arg0) {
    return Menu_UpdateCursor((s32)&arg0->menu);
}

extern char D_8910E064[];
extern Color_RGBA8 D_8910A94C;
extern char D_8910E07C[];
extern char D_8910E088[];
/**
 * Sets up the レベルのにゅうりょく (level input) window.
 * Seen in play (2026-11-12) in いちらん: レベルをきめてあつめる (page 3/3, A on the レベル header) ran this once
 * and opened 「001 から 100」; かいじょ is greyed out when no level filter is active.
 */
void LabPCList_InitLevelInputWindow(LabLevelInputWindow* arg0, s32 arg1, s32 arg2, Color_RGBA8 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Window_SetRect(arg0, arg1, arg2, 0x13C, 0x50);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x800;
    arg0->window.title = D_8910E064;
    arg0->window.frame.color = arg3;
    arg0->minLevel.digitCount = 3;
    arg0->minLevel.value = arg4;
    arg0->minLevel.min = 1; arg0->minLevel.max = 0x64; // FAKE: same line
    arg0->minLevel.digit = 0;
    arg0->maxLevel.digitCount = 3;
    arg0->maxLevel.value = arg5;
    arg0->maxLevel.digit = 0;
    arg0->maxLevel.max = 0x64;
    arg0->maxLevel.min = 1;
    Window_InitLabeled((s8*)&arg0->gatherButton, arg0->window.frame.x + 0xD2, arg0->window.frame.y + 0xE, 0x5C, D_8910A94C, D_8910E07C);
    Window_InitLabeled((s8*)&arg0->clearButton, arg0->window.frame.x + 0xD2, arg0->window.frame.y + 0x2A, 0x5C, D_8910A94C, D_8910E088);
    if (arg6 == 0) {
        arg0->clearButton.flags |= 1;
    }
    arg0->cursor.cursor = 0;
    arg0->cursor.count = 2;
    M2C_FIELD(arg0, s32*, 0xCC) = D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->column = 2; arg0->unk_E0 = 7; // FAKE: same line
    arg0->unk_D8 = D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->focus = 0;
}

extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern u8 D_04002130[];
extern u8 D_04002238[];
extern u8 D_04002340[];
extern u8 D_04002448[];
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
extern Color_RGBA8 D_80073520;
M2C_UNK func_8001AA60(s32, s32, s32);

/**
 * Draws the level input digits and the up/down arrows.
 * Seen in play (2026-11-12) in いちらん: drew the three digits of each bound with a yellow frame on
 * the selected digit.
 */
void LabPCList_DrawLevelInput(s8* arg0, s32 x, s32 y, s32 flags) {
    s32 hl = flags & 2;
    s32 bx;
    s32 v;

    if (hl & 2) {
        bx = x - M2C_FIELD(arg0, s32*, 0x10) * 0x16 + 0x2C;
        gSPDisplayList(gDisplayListHead++, D_80073408);
        if (((u16*)D_800603C0)[3] & 0x800) {
            v = (s32)D_04002340;
        } else {
            v = (s32)D_04002130;
        }
        func_8001B884(bx + 3, y - 0xA, 0xE, 8, (u8*)v, 0x10, 0x200000);
        if (((u16*)D_800603C0)[3] & 0x400) {
            v = (s32)D_04002448;
        } else {
            v = (s32)D_04002238;
        }
        func_8001B884(bx + 3, y + 0x16, 0xE, 8, (u8*)v, 0x10, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
        Ui_DrawRoundedFrame(bx - 3, y - 3, 0x1A, 0x1A, D_80073520);
    }
    func_8001AB6C();
    func_8001A384(8, 2);
    v = (M2C_FIELD(arg0, s32*, 0x10) == 2) ? hl : 0;
    Font_SetColorForFlags(v);
    func_8001AA60(x, y, M2C_FIELD(arg0, s32*, 0) / 100 + '0');
    v = (M2C_FIELD(arg0, s32*, 0x10) == 1) ? hl : 0;
    Font_SetColorForFlags(v);
    func_8001AA60(x + 0x16, y, M2C_FIELD(arg0, s32*, 0) / 10 % 10 + '0');
    v = (M2C_FIELD(arg0, s32*, 0x10) == 0) ? hl : 0;
    Font_SetColorForFlags(v);
    func_8001AA60(x + 0x2C, y, M2C_FIELD(arg0, s32*, 0) % 10 + '0');
    func_8001ABBC();
}

void Window_DrawLabeled(s8 *, s32);
void LabPCList_DrawLevelInput(s8 *, s32, s32, s32);
extern char D_8910E094[];
/**
 * Draws the レベルのにゅうりょく (level input) window: the lower and upper level digits with から
 * between them, and the あつめる and かいじょ buttons.
 * Seen in play (2026-11-12) in いちらん: ran every frame while the window showed 「001 から 100」.
 * D_8910E094 is から ("from"), not "Empty".
 */
void LabPCList_DrawLevelInputWindow(LabLevelInputWindow* arg0) {
    if (func_8002AE6C() == 0) {
        func_8001AB6C();
        func_8001A384(4, 0);
        func_8001AA9C(0xC8, 0xC8, 0xFF, 0xFF);
        func_8001A944(arg0->window.frame.x + 0x54, arg0->window.frame.y + 0x13, D_8910E094);
        func_8001ABBC();
        LabPCList_DrawLevelInput((s8*)&arg0->minLevel, arg0->window.frame.x + 0xE, arg0->window.frame.y + 0x10, (arg0->focus == 0) ? 2 : 0);
        LabPCList_DrawLevelInput((s8*)&arg0->maxLevel, arg0->window.frame.x + 0x7A, arg0->window.frame.y + 0x10, (arg0->focus == 1) ? 2 : 0);
        Window_DrawLabeled((s8*)&arg0->gatherButton, (arg0->focus == 2 && arg0->cursor.cursor == 0) ? 2 : 0);
        Window_DrawLabeled((s8*)&arg0->clearButton, (arg0->focus == 2 && arg0->cursor.cursor == 1) ? 2 : 0);
    }
}

s32 func_8000B30C();                                /* extern */
M2C_UNK func_8002B204(s8 *, s32, s8 *);         /* extern */
M2C_UNK func_8002B2E4(s32, s32, s8 *);            /* extern */
M2C_UNK func_8002B4B4(s8 *, s32, s8 *);         /* extern */
s32 func_8002BC14(s32, s32, s8 *);                /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */
extern s32 D_800603C0;

/**
 * Handles the level input digits.
 * Seen in play (2026-11-12) in いちらん: D-Up raised the selected digit (001 to 006), D-Right moved
 * across the six digits to あつめる/かいじょ, and A on those returned 1 or 2.
 */
s32 LabPCList_UpdateLevelInput(LabLevelInputWindow* arg0) {
    s32 sp1C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;

    sp1C = 0;
    temp_v1 = func_8000B30C() & 0xFFFF;
    if (temp_v1 & 0x300) {
        func_8002B2E4((s8*)&arg0->unk_D8, temp_v1, arg0);
        temp_v1_2 = arg0->column;
        if (temp_v1_2 < 3) {
            arg0->focus = 0;
            arg0->minLevel.digit = (s32) (2 - temp_v1_2);
        } else if (temp_v1_2 < 6) {
            arg0->focus = 1;
            arg0->maxLevel.digit = (s32) (5 - temp_v1_2);
        } else {
            arg0->focus = 2;
            arg0->cursor.cursor = 0;
        }
    } else if (temp_v1 & 0xC00) {
        temp_v0 = arg0->focus;
        switch (temp_v0) {                          /* irregular */
        case 0:
            func_8002B4B4((s8*)&arg0->minLevel, temp_v1, arg0);
            break;
        case 1:
            func_8002B4B4((s8*)&arg0->maxLevel, temp_v1, arg0);
            break;
        case 2:
            func_8002B204((s8*)&arg0->cursor, temp_v1, arg0);
            break;
        }
    } else if (temp_v1 == 0) {
        temp_v0_2 = func_8002BC14(D_800603C0, temp_v1, arg0);
        if (temp_v0_2 == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if ((temp_v0_2 == 1) && (arg0->focus == 2)) {
            if (arg0->cursor.cursor == 0) {
                func_8003F6AC(2);
                sp1C = 1;
            } else if (!(arg0->clearButton.flags & 1)) {
                func_8003F6AC(2);
                sp1C = 2;
            } else {
                func_8003F6AC(8);
            }
        }
    }
    return sp1C;
}

/*
 * func_89106E34
 *
 * Calls Window_SetRect(arg0, arg1, arg2, arg3, 0), which fills the first five
 * words of the object (arg1, arg2, arg3, 0, 0), then stores arg4 at +0x14.
 */
void func_89106E34(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Window_SetRect(arg0, arg1, arg2, arg3, 0);
    M2C_FIELD(arg0, s32 *, 0x14) = arg4;
}

typedef struct Tex89106E64 {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
    /* 0x08 */ u8* img08;
    /* 0x0C */ u8* img0C;
    /* 0x10 */ u8* img10;
    /* 0x14 */ u8* img14;
} Tex89106E64;
typedef struct Win89106E64 {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 width;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 flags;
    /* 0x14 */ Tex89106E64* tex;
} Win89106E64;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_89106E64(Win89106E64* arg0) {
    gSPDisplayList(gDisplayListHead++, D_80073408);
    func_8001B884(arg0->x, arg0->y, arg0->tex->width, arg0->tex->height,
                  (arg0->flags & 8) ? arg0->tex->img08 : arg0->tex->img0C, arg0->tex->width, 0x200000);
    func_8001B884(arg0->x + arg0->width - arg0->tex->width, arg0->y, arg0->tex->width, arg0->tex->height,
                  (arg0->flags & 8) ? arg0->tex->img14 : arg0->tex->img10, arg0->tex->width, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s32 func_89106F74(s8 *arg0)
{
  s32 temp_v0;
  s32 var_v1;
  u16 temp_a1;
  temp_v0 = *((s32 *) (((s8 *) arg0) + 0x10));
  var_v1 = 0;
  if (temp_v0 & 1)
  {
    return 0;
  }
  temp_a1 = *((u16 *) (((s8 *) (*((s8 **) (&D_800603C0)))) + 8)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  if ((*((u16 *) (((s8 *) (*((s8 **) (&D_800603C0)))) + 8))) & 0x200) // FAKE: decomp slop, raw pointer casts stand in for struct fields
  {
    *((s32 *) (((s8 *) arg0) + 0x10)) = (s32) (temp_v0 | 8);
    var_v1 = 0x200;
  }
  else
    if ((*((u16 *) (((s8 *) (*((s8 **) (&D_800603C0)))) + 8))) & 0x100) // FAKE: decomp slop, raw pointer casts stand in for struct fields
  {
    *((s32 *) (((s8 *) arg0) + 0x10)) = (s32) (temp_v0 & (~8));
    var_v1 = 0x100;
  }
  return var_v1;
}

extern Gfx D_80060270[];
extern u8 D_8910A968[];
extern u8 D_8910A970[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawNumber(s32, s32, s32, s32);
/**
 * Draws one numbered row of the type filter list.
 * Seen in play (2026-11-12) in いちらん: drew the numbered rows of the type list (1 ノーマル, 2 かくとう, 3
 * ひこう, ...).
 */
void LabPCList_DrawTypeFilterRow(s32 arg0, s32 arg1, char **arg2, s32 arg3, s32 arg4) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xAE, 0x1A, *(Color_RGBA8 *)D_8910A968);
    func_80029028(arg0, arg1, 0xAE, 1, *(Color_RGBA8 *)D_8910A970);
    func_80029028(arg0, arg1 + 0x1B, 0xAE, 1, *(Color_RGBA8 *)D_8910A970);
    if (arg4 & 8) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xA8, 0x16, *(Color_RGBA8 *)D_8910A968);
    }
    Ui_DrawNumber(arg0 + 9, arg1 + 8, arg3 + 1, 2);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x42, arg1 + 4, *arg2);
    Font_EndTexturedTextRendering();
}

/** Converts a move table index to its display index by skipping unused slots. */
s32 Move_NormalizeDisplayIndex(s32 a) {
    return a >= 20 ? a - 12 : (a >= 7 ? a - 1 : a);
}

s32 func_89107170(s32 a) {
    return a >= 8 ? a + 12 : (a >= 6 ? a + 1 : a);
}

typedef struct Entry891071A4 {
    const char* str;
    u8 color[4];
} Entry891071A4;

void ScrollList_Init(s8*, s32, s32, s32, void*, s32, s32);
void Window_InitLabeled(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5);
void func_8000B2F4(s32);
extern Entry891071A4 D_80066AD8[];
extern Color_RGBA8 D_8910A974;
extern char D_8910E09C[];
extern char D_8910E0B0[];
extern char D_8910E0B8[];
extern char D_8910E0C4[];

/**
 * Sets up the type filter window.
 * Seen in play (2026-11-12) in いちらん: A on the タイプ1 header opened the タイプであつめる (gather by type)
 * window, with two empty type slots, the numbered type list (1 ノーマル, 2 かくとう, ... 8 ゴースト) and あつめる
 * / かいじょ buttons.
 */
void LabPCList_InitTypeFilter(LabTypeFilterWindow* arg0, s32 x, s32 y, s32* arg3) {
    s32 i;

    Window_SetRect((s8*)arg0, x, y, 0x156, 0x120);
    arg0->window.animTimer = 0;
    arg0->window.title = NULL;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x800;
    arg0->window.frame.color = D_8910A974;
    arg0->window.title = D_8910E09C;
    func_80027804(&arg0->typeList, (s32*)arg0->names, 0xF, 0xF);
    for (i = 0; i < 0xF; i++) {
        arg0->names[i] = (s8*)&D_80066AD8[i + ((i < 6) ? 0 : 1)];
    }
    ScrollList_Init(&arg0->list, (s32)&arg0->typeList, (s32)arg0->typeFlags, 8, LabPCList_DrawTypeFilterRow, 0xAE, 0x1C);
    arg0->list.options |= 0x10000;
    for (i = 0; i < *arg3; i++) {
        arg0->slots[i].index = Move_NormalizeDisplayIndex(((u8*)arg3)[4 + i]);
    }
    for (; i < 2; i++) {
        arg0->slots[i].index = -1;
    }
    for (i = 0; i < 2; i++) {
        if (arg0->slots[i].index == -1) {
            Window_InitLabeled(&arg0->slots[i].button, arg0->window.frame.x + 0x20, arg0->window.frame.y + i * 0x1C + 0x22, 0x5C, D_8910A974, D_8910E0B0);
        } else {
            Window_InitLabeled(&arg0->slots[i].button, arg0->window.frame.x + 0x20, arg0->window.frame.y + i * 0x1C + 0x22, 0x5C, D_8910A974, *(char**)arg0->names[arg0->slots[i].index]);
            arg0->list.itemFlags[arg0->slots[i].index] |= 8;
        }
    }
    Window_InitLabeled(&arg0->gatherButton, arg0->window.frame.x + 0x20, arg0->window.frame.y + 0xCA, 0x5C, D_8910A974, D_8910E0B8);
    Window_InitLabeled(&arg0->clearButton, arg0->window.frame.x + 0x20, arg0->window.frame.y + 0xE6, 0x5C, D_8910A974, D_8910E0C4);
    if (*arg3 == 0) {
        arg0->clearButton.flags |= 1;
    }
    arg0->cursor.cursor = 0;
    arg0->cursor.count = 4;
    arg0->cursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->mode = 0;
}

extern u8 D_800735C4[];
void ScrollList_DrawItems(s8*, s32, s32, s32, s32);

/**
 * Draws the type filter window.
 * Seen in play (2026-11-12) in いちらん: drew the タイプであつめる window.
 */
void LabPCList_DrawTypeFilter(LabTypeFilterWindow* arg0) {
    s32 i;
    s32 hl;
    s32 mask;

    if (func_8002AE6C() == 0) {
        hl = (arg0->mode == 0) ? 2 : 0x10;
        for (i = 0; i < 2; i++) {
            Window_DrawLabeled(&arg0->slots[i].button, (i == arg0->cursor.cursor) ? hl : 0);
        }
        hl = (arg0->mode == 0) ? 2 : 0;
        Window_DrawLabeled(&arg0->gatherButton, (arg0->cursor.cursor == 2) ? hl : 0);
        Window_DrawLabeled(&arg0->clearButton, (arg0->cursor.cursor == 3) ? hl : 0);
        Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0x96, arg0->window.frame.y + 0xE, 0xB2, 0x104, D_800735C4);
        mask = 0xFFED;
        if (arg0->mode == 1) {
            mask = 0xFFEF;
        }
        ScrollList_DrawItems(&arg0->list, arg0->window.frame.x + 0x98, arg0->window.frame.y + 0x20, mask, 0);
    }
}

s32 ScrollList_UpdateCursor(s8*);



/**
 * Handles the type filter window. Returns -1 on cancel, 1 on confirm, 2 on clear.
 * Seen in play (2026-11-12) in いちらん: handled the タイプであつめる window; A moved the cursor into the
 * type list (1 ノーマル).
 */
s32 LabPCList_UpdateTypeFilter(LabTypeFilterWindow* arg0) {
    s32 ret = 0;
    u16 buttons;

    switch (arg0->mode) {
        case 0:
            if (func_8002B2B0(&arg0->cursor) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (buttons & 0x8000) {
                    switch (arg0->cursor.cursor) {
                        case 0:
                        case 1:
                            func_8003F6AC(2);
                            arg0->mode = 1;
                            break;
                        case 2:
                            func_8003F6AC(2);
                            ret = 1;
                            break;
                        case 3:
                            if (arg0->clearButton.flags & 1) {
                                func_8003F6AC(8);
                            } else {
                                func_8003F6AC(2);
                                ret = 2;
                            }
                            break;
                    }
                }
            }
            break;
        case 1:
            if (ScrollList_UpdateCursor(&arg0->list) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    func_8003F6AC(3);
                    arg0->mode = 0;
                } else if (buttons & 0x8000) {
                    if (arg0->list.itemFlags[arg0->list.cursor] & 8) {
                        func_8003F6AC(8);
                    } else {
                        s32 prev;

                        func_8003F6AC(2);
                        prev = arg0->slots[arg0->cursor.cursor].index;
                        if (prev != -1) {
                            arg0->list.itemFlags[prev] &= ~8;
                        }
                        arg0->list.itemFlags[arg0->list.cursor] |= 8;
                        arg0->slots[arg0->cursor.cursor].index = arg0->list.cursor;
                        arg0->slots[arg0->cursor.cursor].button.label = *(char**)arg0->names[arg0->list.cursor];
                        arg0->mode = 0;
                        arg0->cursor.cursor++;
                    }
                }
            }
            break;
    }
    return ret;
}

/**
 * Copies the chosen types into the list's filter state.
 * Seen in play (2026-11-12) in いちらん: after choosing どく and pressing あつめる, it wrote count 1 and
 * type byte 0x03 (Poison) into the filter state at +0x9918.
 */
void LabPCList_CommitTypeFilter(LabTypeFilterWindow* arg0, s32* arg1) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (arg0->slots[i].index != -1) {
            M2C_FIELD((s8*)arg1 + count, s8*, 4) = func_89107170(arg0->slots[i].index);
            count++;
        }
    }
    *arg1 = count;
}

extern u8 D_8910AAC0[];
extern u8 D_8910AAC8[];
/**
 * Draws one numbered row of the move filter list.
 * Seen in play (2026-11-12) in いちらん: drew the numbered move rows of わざであつめる (row index 0 = 1
 * 10まんボルト, 1 = 2 あくまのキッス).
 */
void LabPCList_DrawMoveFilterRow(s32 arg0, s32 arg1, u8* arg2, s32 arg3, s32 arg4) {
    s32 idx;

    idx = *arg2;
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xD4, 0x1A, *(Color_RGBA8 *)D_8910AAC0);
    func_80029028(arg0, arg1, 0xD4, 1, *(Color_RGBA8 *)D_8910AAC8);
    func_80029028(arg0, arg1 + 0x1B, 0xD4, 1, *(Color_RGBA8 *)D_8910AAC8);
    if (arg4 & 8) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xCE, 0x16, *(Color_RGBA8 *)D_8910AAC0);
    }
    Ui_DrawNumber(arg0 + 9, arg1 + 8, arg3 + 1, 3);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x37, arg1 + 4, D_8006A9D4[idx].name);
    Font_EndTexturedTextRendering();
}


void ScrollList_Init(s8*, s32, s32, s32, void*, s32, s32);
void Window_InitLabeled(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5);
void func_8000B2F4(s32);
extern u8 D_8910A978[];
extern u8 D_8910AA1C[];
extern Color_RGBA8 D_8910AACC;
extern char D_8910E0D0[];
extern char D_8910E0E0[];
extern char D_8910E0E8[];
extern char D_8910E0F4[];

/**
 * Sets up the move filter window.
 * Seen in play (2026-11-12) in いちらん: A on the わざ header (detail page 2/3) ran this once and
 * opened わざであつめる, with four empty slots and the move list starting at 1 10まんボルト.
 */
void LabPCList_InitMoveFilter(LabMoveFilterWindow* arg0, s32 x, s32 y, u8* arg3) {
    s32 i;

    Window_SetRect((s8*)arg0, x, y, 0x194, 0x120);
    arg0->window.animTimer = 0;
    arg0->window.title = NULL;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x800;
    arg0->window.frame.color = D_8910AACC;
    arg0->window.title = D_8910E0D0;
    func_80027410(&arg0->moveMatrix, D_8910A978, 1, 0xA4, 0xA4);
    ScrollList_Init(&arg0->list, (s32)&arg0->moveMatrix, (s32)arg0->moveFlags, 8, LabPCList_DrawMoveFilterRow, 0xD4, 0x1C);
    arg0->list.options |= 0x10000;
    for (i = 0; i < M2C_FIELD(arg3, s32*, 4); i++) {
        arg0->slots[i].index = D_8910AA1C[arg3[i] - 1];
    }
    for (; i < 4; i++) {
        arg0->slots[i].index = -1;
    }
    for (i = 0; i < 4; i++) {
        if (arg0->slots[i].index == -1) {
            Window_InitLabeled(&arg0->slots[i].button, arg0->window.frame.x + 0xE, arg0->window.frame.y + i * 0x1C + 0x22, 0x98, D_8910AACC, D_8910E0E0);
        } else {
            Window_InitLabeled(&arg0->slots[i].button, arg0->window.frame.x + 0xE, arg0->window.frame.y + i * 0x1C + 0x22, 0x98, D_8910AACC, (char*)D_8006A9D4[D_8910A978[arg0->slots[i].index]].name);
            arg0->list.itemFlags[arg0->slots[i].index] |= 8;
        }
    }
    Window_InitLabeled(&arg0->gatherButton, arg0->window.frame.x + 0x4A, arg0->window.frame.y + 0xCA, 0x5C, D_8910AACC, D_8910E0E8);
    Window_InitLabeled(&arg0->clearButton, arg0->window.frame.x + 0x4A, arg0->window.frame.y + 0xE6, 0x5C, D_8910AACC, D_8910E0F4);
    if (M2C_FIELD(arg3, s32*, 4) == 0) {
        arg0->clearButton.flags |= 1;
    }
    arg0->cursor.cursor = 0;
    arg0->cursor.count = 6;
    arg0->cursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->mode = 0;
}

void ScrollList_DrawInlineItems(s8*, s32, s32, s32, s32);

/**
 * Draws the move filter window.
 * Seen in play (2026-11-12) in いちらん: ran every frame while わざであつめる was open.
 */
void LabPCList_DrawMoveFilter(LabMoveFilterWindow* arg0) {
    s32 i;
    s32 hl;
    s32 mask;

    if (func_8002AE6C() == 0) {
        hl = (arg0->mode == 0) ? 2 : 0x10;
        for (i = 0; i < 4; i++) {
            Window_DrawLabeled(&arg0->slots[i].button, (i == arg0->cursor.cursor) ? hl : 0);
        }
        hl = (arg0->mode == 0) ? 2 : 0;
        Window_DrawLabeled(&arg0->gatherButton, (arg0->cursor.cursor == 4) ? hl : 0);
        Window_DrawLabeled(&arg0->clearButton, (arg0->cursor.cursor == 5) ? hl : 0);
        Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0xAE, arg0->window.frame.y + 0xE, 0xD8, 0x104, D_800735C4);
        mask = 0xFFED;
        if (arg0->mode == 1) {
            mask = 0xFFEF;
        }
        ScrollList_DrawInlineItems(&arg0->list, arg0->window.frame.x + 0xB0, arg0->window.frame.y + 0x20, mask, 0);
    }
}

extern u8 D_8910A978[];

/**
 * Handles the move filter window. Returns -1 on cancel, 1 on confirm, 2 on clear.
 * Seen in play (2026-11-12) in いちらん: handled わざであつめる. あつめる led to the commit path (1) and かいじょ to
 * the clear path (2).
 */
s32 LabPCList_UpdateMoveFilter(LabMoveFilterWindow* arg0) {
    s32 ret = 0;
    u16 buttons;

    switch (arg0->mode) {
        case 0:
            if (func_8002B2B0(&arg0->cursor) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (buttons & 0x8000) {
                    switch (arg0->cursor.cursor) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            func_8003F6AC(2);
                            arg0->mode = 1;
                            break;
                        case 4:
                            func_8003F6AC(2);
                            ret = 1;
                            break;
                        case 5:
                            if (arg0->clearButton.flags & 1) {
                                func_8003F6AC(8);
                            } else {
                                func_8003F6AC(2);
                                ret = 2;
                            }
                            break;
                    }
                }
            }
            break;
        case 1:
            if (ScrollList_UpdateCursor(&arg0->list) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    func_8003F6AC(3);
                    arg0->mode = 0;
                } else if (buttons & 0x8000) {
                    if (arg0->list.itemFlags[arg0->list.cursor] & 8) {
                        func_8003F6AC(8);
                    } else {
                        s32 prev;

                        func_8003F6AC(2);
                        prev = arg0->slots[arg0->cursor.cursor].index;
                        if (prev != -1) {
                            arg0->list.itemFlags[prev] &= ~8;
                        }
                        arg0->list.itemFlags[arg0->list.cursor] |= 8;
                        arg0->slots[arg0->cursor.cursor].index = arg0->list.cursor;
                        arg0->slots[arg0->cursor.cursor].button.label = (s32)D_8006A9D4[D_8910A978[arg0->list.cursor]].name;
                        arg0->mode = 0;
                        arg0->cursor.cursor++;
                    }
                }
            }
            break;
    }
    return ret;
}

extern u8 D_8910A978[];

/**
 * Copies the chosen moves into the list's filter state.
 * Seen in play (2026-11-12) in いちらん: after choosing ひっさつまえば and pressing あつめる, it wrote move 0x9E
 * (Hyper Fang) and count 1 into the filter state at +0x9B00.
 */
void LabPCList_CommitMoveFilter(LabMoveFilterWindow* arg0, u8* arg1) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0->slots[i].index != -1) {
            arg1[count++] = D_8910A978[arg0->slots[i].index] + 1;
        }
    }
    M2C_FIELD(arg1, s32*, 4) = count;
}

extern Color_RGBA8 D_8910AAD0;
extern Color_RGBA8 D_8910AAD4;
extern Color_RGBA8 D_8910AAD8;
extern char D_8910E100[];
extern char D_8910E104[];
extern char D_8910E110[];
extern char D_8910E118[];
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
char* func_8001FDC8(u8, char*);
s32 func_80031CC8(u8);
/**
 * Draws an item row with パソコン (PC) / てもち (Party) and ×%02d.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void PcSort_DrawItemRow(s32 x, s32 y, u8** item, UNUSED s32 index, s32 flags) {
    char buf[0x38];

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y + 1, 0x10C, 0x1A, D_8910AAD0);
    func_80029028(x + 0x10C, y + 1, 0x6C, 0x1A, D_8910AAD4);
    func_80029028(x, y, 0x178, 1, D_8910AAD8);
    func_80029028(x, y + 0x1B, 0x178, 1, D_8910AAD8);
    if (item != NULL) {
        if (flags & 0x10) {
            Ui_FillRectHighlighted(x + 3, y + 3, 0x109, 0x16, D_8910AAD0);
            Ui_FillRectHighlighted(x + 0x10C, y + 3, 0x69, 0x16, D_8910AAD4);
        }
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(8, 0);
        func_8001A944(x + 8, y + 4, func_8001FDC8(item[0][0], buf));
        if (item[1][0] == 0x12) {
            func_8001A384(8, 0);
            func_8001A944(x + 0x120, y + 4, D_8910E100);
        } else if (item[1][0] == 0x22) {
            func_8001A384(8, 0);
            func_8001A944(x + 0x120, y + 4, D_8910E104);
        } else {
            func_8001A384(8, 0);
            func_8001A944(x + 0x120, y + 4, D_8910E110);
        }
        if (func_80031CC8(item[0][0]) == 0) {
            func_8001A384(8, 0);
            func_8001A944(x + 0xBC, y + 4, D_8910E118, item[0][1]);
        }
        func_8001ABBC();
    }
}

/* Layouts below are partial and local to this function: only the fields the
 * function touches are named, and the names say where they are, not what
 * they mean. */
typedef struct {
    s32 pad0[4];
    s32 word10;
} FlagScanEntry;

typedef struct {
    FlagScanEntry** entries; /* 0x00 */
    s32 unk4;
    s32 count;               /* 0x08 */
} FlagScanTable;

typedef struct {
    u8 pad0[0x4C];
    FlagScanTable* table;    /* 0x4C */
    u16* flags;              /* 0x50 */
} FlagScanOwner;

/*
 * func_89108450
 *
 * Walks the pointer array arg0->table->entries (arg0->table->count items).
 * For every entry whose word at offset 0x10 has any of its low five bits
 * (mask 0x1F) set, bit 0 is set in the matching halfword of the array at
 * arg0->flags (same index). What the entries and the flags are is not
 * established here. The loop bound re-reads arg0->table->count each pass.
 * Matching note: the entries pointer is held in a local and indexed;
 * advancing a pointer through arg0->table->entries directly gives a
 * different register assignment.
 */
void func_89108450(FlagScanOwner* arg0) {
    s32 i;
    FlagScanEntry** entries;

    entries = arg0->table->entries;
    for (i = 0; i < arg0->table->count; i++) {
        if (entries[i]->word10 & 0x1F) {
            arg0->flags[i] |= 1;
        }
    }
}

typedef struct Str891084B4 {
    /* 0x00 */ u8 c[0x11];
} Str891084B4; // size = 0x11
typedef struct Rgba891084B4 {
    u8 r, g, b, a;
} Rgba891084B4;
extern s8 D_89119BD0[];
extern u8 D_8910E120[];
extern u8 D_8910AAE0[];
extern u8 D_8910AAE4[];
void func_8000A460(s8*, s8*);
void ScrollList_Init(s8*, s32, s32, s32, void*, s32, s32);
void PcSort_DrawItemRow();
/**
 * Sets up the window that uses an item on the selected Pokemon.
 * Seen in play (2026-11-12) in いちらん: どうぐをつかう on フシギダネ opened 「フシギダネがつかえるどうぐ」, listing the bag
 * items from the Game Boy save (マックスアップ ×5, タウリン ×5, ふしぎなアメ ×5, ポイントアップ ×3, わざマシン06, ひでんマシン01).
 */
void LabPCList_InitItemWindow(LabItemWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8* arg5) {
    Window_SetRect(&arg0->window, arg1, arg2, 0x184, 0x16E);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    func_8000A460(D_89119BD0, *(s8**)D_80064C44[arg5[8]]);
    *(Str891084B4*)(func_800566BC((s32)D_89119BD0) + D_89119BD0) = *(Str891084B4*)D_8910E120;
    arg0->window.title = (char*)D_89119BD0;
    Window_SetRect(&arg0->textFrame, arg1 + 6, arg2 + 0x10C, 0x178, 0x5C);
    arg0->textFrame.style = 6;
    *(Rgba891084B4*)&arg0->textFrame.color = *(Rgba891084B4*)D_8910AAE0;
    *(Rgba891084B4*)&arg0->textFrame.color2 = *(Rgba891084B4*)D_8910AAE4;
    ScrollList_Init(&arg0->list, arg3, arg4, 8, PcSort_DrawItemRow, 0x178, 0x1C);
    arg0->list.options |= 0x10000;
    func_89108450((FlagScanOwner*)arg0);
    arg0->mon = arg5;
    arg0->mode = 0;
}

extern Color_RGBA8 D_800734B8[];
extern char D_8910E134[];
extern char D_8910E150[];
extern char D_8910E16C[];
char* func_80031BC0(u8, char*);
/**
 * Draws このどうぐをつかいますか？ (Use this item?), どの わざに つかいますか？ (On which move?) or どの わざを わすれさせたい？ (Which move should it forget?).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void PcSort_DrawUseItemPrompt(LabItemWindow* arg0) {
    s32 flags;
    s32 x;
    s32 y;
    char buf[0x70];

    if (Window_DrawAnimatedFrame() == 0) {
        Window_DrawFrame(&arg0->textFrame);
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->textFrame.y - 7, arg0->window.frame.width, D_8007356C);
        flags = 0xFFED;
        flags |= (arg0->mode == 0) ? 2 : 0x10;
        ScrollList_DrawItems(&arg0->list, arg0->window.frame.x + 6, arg0->window.frame.y + 0x16, flags, 0);
        if (arg0->list.items->count > 0) {
            Font_BeginTranslucentTextRendering();
            Font_SetActive(8, 0);
            Font_SetLineHeight(0x1C);
            x = arg0->textFrame.x + 8;
            y = arg0->textFrame.y + 8;
            switch (arg0->mode) {
                case 0:
                    Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
                    Font_Printf(x, y + 0x1C, func_80031BC0(**((u8***)arg0->list.items->rows)[arg0->list.cursor], buf));
                    break;
                case 1:
                    Gfx_SetEnvColor(D_800734B8[0].r, D_800734B8[0].g, D_800734B8[0].b, D_800734B8[0].a);
                    Font_Printf(x, y, D_8910E134);
                    Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
                    Font_Printf(x, y + 0x1C, func_80031BC0(**((u8***)arg0->list.items->rows)[arg0->list.cursor], buf));
                    break;
                case 2:
                    Gfx_SetEnvColor(D_800734B8[0].r, D_800734B8[0].g, D_800734B8[0].b, D_800734B8[0].a);
                    Font_Printf(x, y, D_8910E150);
                    Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
                    Font_Printf(x, y + 0x1C, func_80031BC0(**((u8***)arg0->list.items->rows)[arg0->list.cursor], buf));
                    break;
                case 3:
                    Gfx_SetEnvColor(D_800734B8[0].r, D_800734B8[0].g, D_800734B8[0].b, D_800734B8[0].a);
                    Font_Printf(x, y, D_8910E16C);
                    Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
                    Font_Printf(x, y + 0x1C, func_80031BC0(**((u8***)arg0->list.items->rows)[arg0->list.cursor], buf));
                    break;
            }
            Font_EndTexturedTextRendering();
            switch (arg0->mode) {
                case 1:
                    LabPCList_DrawPopupMenu(&arg0->confirmPopup, 2);
                    break;
                case 2:
                case 3:
                    func_891051A4(&arg0->moveSelect);
                    break;
                case 4:
                    func_89105200(&arg0->moveSelect);
                    break;
            }
        }
    }
}

extern u8 D_8910AAE8[];
extern Rgba891084B4 D_8910AAEC;
s32 ScrollList_UpdateCursor(s8 *);
void func_89105144(s8 *);
s32 func_80020974(s32);
/**
 * Handles the item window. Returns 1 for a vitamin, 2 for PP Up, 3 for a TM or HM.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 LabPCList_UpdateItemWindow(s8 *arg0)
{
  s32 ret = 0;
  s8 *self = arg0;
  u8 **entry;
  s32 n;
  s32 species;
  unsigned int i;
  switch (*((u32 *) (((s8 *) self) + 0x1B0)))
  {
    case 0:
      if (ScrollList_UpdateCursor(self + 0x4C) == 0)
    {
      if (((u16 *) D_800603C0)[4] & 0x4000)
      {
        func_8003F6AC(3);
        ret = -1;
      }
      else
        if (((u16 *) D_800603C0)[4] & 0x8000)
      {
        if (!((*((u16 **) (((s8 *) self) + 0x50)))[*((s32 *) (((s8 *) self) + 0x54))] & 1)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
        {
          func_8003F6AC(2);
          LabPCList_InitPopupMenu((LabPopupMenu *) (self + 0x94), (s32 *) D_8910AAE8, (s32) (self + 0x90), 1, 0);
          Window_SetRect(self + 0xC0, (*((s32 *) (((s8 *) self) + 0))) + 6, (((*((s32 *) (((s8 *) self) + 4))) + (*((s32 *) (((s8 *) self) + 0x80)))) - (*((s32 *) (((s8 *) self) + 0x78)))) + 0x16, (*((s32 *) (((s8 *) self) + 8))) - 0xC, 0x1C); // FAKE: decomp slop, raw pointer casts stand in for struct fields
          *((s32 *) (((s8 *) self) + 0x108)) = ((*((s32 *) (((s8 *) self) + 8))) + (*((s32 *) (((s8 *) self) + 0)))) - 6; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          *((s32 *) (((s8 *) self) + 0x10C)) = (*((s32 *) (((s8 *) self) + 4))) + 0xF6; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          LabPCList_PlacePopup((LabPopupMenu *) (self + 0x94));
          *((Rgba891084B4 *) (((s8 *) self) + 0xAC)) = D_8910AAEC;
          *((u32 *) (((s8 *) self) + 0x1B0)) = 1;
        }
        else
        {
          func_8003F6AC(8);
        }
      }
    }
      break;

    case 1:
      if (LabPCList_UpdatePopupMenu((LabPopupMenu *) (self + 0x94)) == 0)
    {
      if (((u16 *) D_800603C0)[4] & 0x4000)
      {
        func_8003F6AC(3);
        *((u32 *) (((s8 *) self) + 0x1B0)) = 0;
      }
      else
        if (((u16 *) D_800603C0)[4] & 0x8000)
      {
        if ((*((s32 *) (((s8 *) self) + 0xDC))) == 0)
        {
          entry = (*(*((u8 *****) (((s8 *) self) + 0x4C))))[*((s32 *) (((s8 *) self) + 0x54))]; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          if ((*((s32 *) (((s8 *) entry) + 8))) >= 100)
          {
            n = BattleMon_CountMoves((*((u8 **) (((s8 *) self) + 0x1AC))) + 8);
            func_8003F6AC(2);
            if (n < 4)
            {
              *((u32 *) (((s8 *) self) + 0x1B0)) = 4;
              if ((*entry[0]) >= 201)
              {
                species = (*entry[0]) - 201;
              }
              else
              {
                species = (*entry[0]) - 146;
              }
              func_89104FC0(self + 0x110, (*((s32 *) (((s8 *) self) + 0))) + 0xD5, (*((s32 *) (((s8 *) self) + 4))) + 0x81, (*((u8 **) (((s8 *) self) + 0x1AC))) + 8); // FAKE: decomp slop, raw pointer casts stand in for struct fields
              *((s32 *) (((s8 *) self) + 0x144)) = n;
              func_89105340(self + 0x110, *((s32 *) (((s8 *) self) + 0x144)), func_80020974(species));
            }
            else
            {
              func_89104FC0(self + 0x110, (*((s32 *) (((s8 *) self) + 0))) + 0xD5, (*((s32 *) (((s8 *) self) + 4))) + 0x81, (*((u8 **) (((s8 *) self) + 0x1AC))) + 8); // FAKE: decomp slop, raw pointer casts stand in for struct fields
              func_89105144(self + 0x110);
              *((u32 *) (((s8 *) self) + 0x1B0)) = 3;
            }
          }
          else
            if ((*((s32 *) (((s8 *) entry) + 8))) >= 50)
          {
            func_8003F6AC(2);
            func_89104FC0(self + 0x110, (*((s32 *) (((s8 *) self) + 0))) + 0xD5, (*((s32 *) (((s8 *) self) + 4))) + 0x81, (*((u8 **) (((s8 *) self) + 0x1AC))) + 8); // FAKE: decomp slop, raw pointer casts stand in for struct fields
            for (i = 0; i < 4; i++)
            {
              if ((((*((s32 *) (((s8 *) self) + (0x170 + (i * 4))))) == (-1)) || ((*((s32 *) (((s8 *) self) + (0x170 + (i * 4))))) == (-2))) || ((*((u8 **) (((s8 *) self) + 0x1AC)))[0x28 + i] >= 0xC0)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
              {
                (*((u16 **) (((s8 *) self) + 0x140)))[i] |= 1;
              }
            }

            *((u32 *) (((s8 *) self) + 0x1B0)) = 2;
          }
          else
          {
            func_8003F6AC(0x22);
            *((u32 *) (((s8 *) self) + 0x1B0)) = 0;
            ret = 1;
          }
        }
        else
        {
          func_8003F6AC(3);
          *((u32 *) (((s8 *) self) + 0x1B0)) = 0;
        }
      }
    }
      break;

    case 2:
      if (func_89105390((s32) (self + 0x110)) == 0)
    {
      if (((u16 *) D_800603C0)[4] & 0x4000)
      {
        func_8003F6AC(3);
        *((u32 *) (((s8 *) self) + 0x1B0)) = 0;
      }
      else
        if (((u16 *) D_800603C0)[4] & 0x8000)
      {
        if (!((*((u16 **) (((s8 *) self) + 0x140)))[*((s32 *) (((s8 *) self) + 0x144))] & 1)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
        {
          func_8003F6AC(0x22);
          *((u32 *) (((s8 *) self) + 0x1B0)) = 0;
          ret = 2;
        }
        else
        {
          func_8003F6AC(8);
        }
      }
    }
      break;

    case 3:
      if (func_89105390((s32) (self + 0x110)) == 0)
    {
      if (((u16 *) D_800603C0)[4] & 0x4000)
      {
        func_8003F6AC(3);
        *((u32 *) (((s8 *) self) + 0x1B0)) = 0;
      }
      else
        if (((u16 *) D_800603C0)[4] & 0x8000)
      {
        if (!((*((u16 **) (((s8 *) self) + 0x140)))[*((s32 *) (((s8 *) self) + 0x144))] & 1)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
        {
          u8 **entry2;
          s32 sp38;
          entry2 = (*(*((u8 *****) (((s8 *) self) + 0x4C))))[*((s32 *) (((s8 *) self) + 0x54))]; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          if ((*entry2[0]) >= 201)
          {
            sp38 = (*entry2[0]) - 201;
          }
          else
          {
            sp38 = (*entry2[0]) - 146;
          }
          func_8003F6AC(2);
          func_89105340(self + 0x110, *((s32 *) (((s8 *) self) + 0x144)), func_80020974(sp38));
          *((u32 *) (((s8 *) self) + 0x1B0)) = 4;
        }
        else
        {
          func_8003F6AC(8);
        }
      }
    }
      break;

    case 4:
      if (((*((s32 *) (((s8 *) self) + 0x188))) == 0) && (((u16 *) D_800603C0)[4] & 0xC000)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
    {
      func_8003F6AC(3);
      *((u32 *) (((s8 *) self) + 0x1B0)) = 0;
      ret = 3;
    }
      break;

  }

  return ret;
}

void func_89108F0C(void) {
}

typedef struct Rgba89108F14 {
    u8 r, g, b, a;
} Rgba89108F14;

extern u8 D_8910AAF4[];
extern u8 D_8910AAF8[];

/**
 * Sets up the result message window.
 * Seen in play (2026-11-12) in いちらん: opened the result window after an item was used (「HP 19 ->
 * 20」).
 */
void LabPCList_InitMessageWindow(LabMessageWindow* arg0, s32 arg1, s32 arg2, LabItemResult* arg3) {
    Window_SetRect(&arg0->window, arg1, arg2, 0x114, 0x60);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 6;
    *(Rgba89108F14*)&arg0->window.frame.color = *(Rgba89108F14*)D_8910AAF4;
    *(Rgba89108F14*)&arg0->window.frame.color2 = *(Rgba89108F14*)D_8910AAF8;
    arg0->message = arg3;
}

extern u8 D_8910D2F0[];
extern char D_8910E1AC[];
extern char D_8910E1B0[];

/**
 * Draws the result message window.
 * Seen in play (2026-11-12) in いちらん: drew the item result window every frame while it was open.
 */
void LabPCList_DrawMessageWindow(LabMessageWindow* arg0) {
    LabItemResult* entry;

    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Font_SetActive(0x10, 0);
        Font_EnableTwoCycleTexturing();
        Gfx_SetPrimColor(0xFF, 0xAC, 0xAC, 0xFF);
        Font_Printf(arg0->window.frame.x + 0x12, arg0->window.frame.y + 0x12, arg0->message->title);
        Font_DisableTwoCycleTexturing();
        Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
        entry = arg0->message;
        if (entry->kind == 0) {
            Font_Printf(arg0->window.frame.x + 0x12, arg0->window.frame.y + 0x36, D_8910E1AC, entry->left);
            Font_Printf(arg0->window.frame.x + 0xA2, arg0->window.frame.y + 0x36, D_8910E1B0, arg0->message->right);
        } else if (entry->kind == 1) {
            Font_Printf(arg0->window.frame.x + 0x12, arg0->window.frame.y + 0x36, entry->left);
            Font_Printf(arg0->window.frame.x + 0xA2, arg0->window.frame.y + 0x36, arg0->message->right);
        }
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(arg0->window.frame.x + 0x7A, arg0->window.frame.y + 0x36, 0x20, 0x18, D_8910D2F0, 0x20, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }
}

M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */

/**
 * Returns 1 once the message has been confirmed.
 * Seen in play (2026-11-12) in いちらん: returned 0 while the item result window was up and 1 after
 * A.
 */
s32 LabPCList_UpdateMessageWindow(LabMessageWindow* arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(D_800603C0, u16 *, 8) & 0xC000) {
        func_8003F6AC(3);
        var_v1 = 1;
    }
    return var_v1;
}
