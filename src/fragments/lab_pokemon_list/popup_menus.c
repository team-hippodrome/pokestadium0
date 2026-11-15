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
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void func_8001AB6C(void);
void func_8001ABBC(void);
void LabPCList_UnusedStub1(void);
void LabPCList_UnusedStub2(void);

extern Color_RGBA8 D_8910A910;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);

/**
 * Draws one text row of a plain popup menu.
 * No callers: no jal, j, address word or lui/addiu pair in any built fragment or the resident code reaches it (2026-11-14 scan), so it never runs.
 * @unverified Name guessed from the code.
 */
void LabTextMenu_DrawRow(s32 x, s32 y, char* text, s32 index, s32 flags, s32* width) {
    s32 temp_v0 = *width;

    if (flags & 8) {
        Ui_FillRectHighlighted(x + 3, y + 3, temp_v0 - 6, 22, D_8910A910);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(8, 0);
    Font_Printf(x + 8, y + 4, text);
    Font_EndTexturedTextRendering();
}

typedef struct Str89104D14 { s8 c[4]; } Str89104D14;
extern Str89104D14 D_8910A914;
void func_80027804(s8 *, s32 *, s32, s32);
void Window_SetRect(s8 *, s32, s32, s32, s32);
void Menu_Init(s8 *, s8 *, s32, void *, s32, s32);
u32 func_800566BC(s32);
void LabTextMenu_DrawRow();
/**
 * Sets up a plain popup menu of text rows sized to its longest row.
 * No callers: no jal, j, address word or lui/addiu pair in any built fragment or the resident code reaches it (2026-11-14 scan), so it never runs.
 * @unverified Name guessed from the code.
 */
void LabTextMenu_Init(s8 *menu, s32 x, s32 y, s32 *texts, s32 flags, s32 count) {
    s32 i;
    s32 w;
    s32 max = 0;
    s32 h;

    for (i = 0; i < count; i++) {
        w = func_800566BC(texts[i]) >> 1;
        if (max < w) {
            max = w;
        }
    }
    func_80027804(menu + 0x50, texts, count, count);
    h = max * 20 + 0x10;
    Menu_Init(menu + 0x2C, menu + 0x50, flags, LabTextMenu_DrawRow, h, 28);
    M2C_FIELD(menu, s32 *, 0x4C) |= 0x10000;
    Window_SetRect(menu, x, y, h + 12, 132);
    M2C_FIELD(menu, s32 *, 0x24) = 0;
    M2C_FIELD(menu, s32 *, 0x20) = 0;
    M2C_FIELD(menu, s32 *, 0x28) = 0;
    M2C_FIELD(menu, s32 *, 0x14) = 0;
    M2C_FIELD(menu, Str89104D14 *, 0x18) = D_8910A914;
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

/**
 * Draws a plain popup menu.
 * No callers: no jal, j, address word or lui/addiu pair in any built fragment or the resident code reaches it (2026-11-14 scan), so it never runs.
 * @unverified Name guessed from the code.
 */
void LabTextMenu_Draw(Box89104E38* menu) {
    s32 label;

    if (func_8002AE6C() == 0) {
        s32 sp2C[4];

        sp2C[0] = menu->w - 12;
        label = (s32)menu->label;
        Menu_DrawItems(label, menu->x + 6, menu->y + 10, 0xFFEF, (s8*)sp2C);
    }
    /* Empty test kept from the permuter: it keeps menu in $s0 as in the ROM. */
    if (menu) {  // karodo
    }
}

M2C_UNK Menu_UpdateCursor(s32);                         /* extern */

/**
 * Moves the cursor of a plain popup menu.
 * No callers: no jal, j, address word or lui/addiu pair in any built fragment or the resident code reaches it (2026-11-14 scan), so it never runs.
 * @unverified Name guessed from the code.
 */
void LabTextMenu_Update(s32 menu) {
    Menu_UpdateCursor(menu + 0x2C);
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

/**
 * Draws one move of the move list; the forgotten move fades out and the new one fades in during the learn animation.
 * Seen in play (2026-11-14) in いちらん: drew たいあたり, なきごえ and the dashes for empty slots in the PP Up and TM move lists.
 */
void LabMoveSelect_DrawMoveRow(s32 x, s32 y, s32* move, s32 index, s32 flags, s32* alpha_ptr) {
    UNUSED s32 padA[4]; // FAKE: stack padding
    const char* name;
    s32 temp;
    s32 alpha;

    temp = *move;
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
    if (flags & 0x100) {
        Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, *alpha_ptr);
    } else if (flags & 0x200) {
        alpha = *alpha_ptr;
        Gfx_SetEnvColor(0xFF, 0xC8, 0xC8, alpha); // #FFC8C8
    } else {
        Font_SetColorForFlags(flags);
    }
    Font_SetActive(8, 0);
    Font_Printf(x + 8, y + 4, name);
    Font_EndTexturedTextRendering();
}

typedef struct Str89104FC0 { s8 c[4]; } Str89104FC0;
extern Str89104FC0 D_8910A91C;
s32 BattleMon_CountMoves(u8* arg0);
s32 BattleMon_GetMoveIndex(s32, s32);
void func_80027410(void*, void*, s32, s32, s32);
void LabMoveSelect_DrawMoveRow();

/**
 * Sets up the 168x132 move list of a Pokémon (four slots, -1 when empty).
 * Seen in play (2026-11-14) in いちらん: opened for ポイントアップ (「どの わざに つかいますか？」) and わざマシン06 on ゼニガメ (「どの わざを わすれさせたい？」).
 */
void LabMoveSelect_Init(LabMoveSelectWindow* window, s32 x, s32 y, u8* mon) {
    s32 n = BattleMon_CountMoves(mon);
    s32 i;

    for (i = 0; i < n; i++) {
        window->moves[i] = BattleMon_GetMoveIndex((s32)mon, i);
    }
    for (i = n; i < 4; i++) {
        window->moves[i] = -1;
    }
    func_80027410(&window->moveMatrix, window->moves, 4, 4, 4);
    Menu_Init(&window->menu, &window->moveMatrix, (s32)window->itemFlags, LabMoveSelect_DrawMoveRow, 156, 28);
    window->menu.options |= 0x10000;
    Window_SetRect(&window->window, x, y, 168, 132);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 0;
    *(Str89104FC0*)&window->window.frame.color = D_8910A91C;
}

extern s32 D_8910A920[5];
/** Disables the move list entries that are restricted for the current cup. */
void LabMoveSelect_DisableHmMoves(LabMoveSelectWindow* window) {
    s32 j;
    s32 i;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (window->moves[i] == D_8910A920[j]) {
                window->itemFlags[i] |= 1;
                break;
            }
        }
    }
}

M2C_UNK Menu_DrawInlineItems(s8*, s32, s32, s32, s8*);

/**
 * Draws the move list.
 * Seen in play (2026-11-14) in いちらん: drew the move lists of ポイントアップ and わざマシン06.
 */
void LabMoveSelect_Draw(LabMoveSelectWindow* window) {
    Menu* label;

    if (func_8002AE6C() == 0) {
        s32 sp2C[4];

        sp2C[0] = window->window.frame.width - 12;
        label = &window->menu;
        Menu_DrawInlineItems(label, window->window.frame.x + 6, window->window.frame.y + 10, 0xFFEF, (s8*)sp2C);
    }
    /* Empty test kept from the permuter: it keeps window in $s0 as in the ROM. */
    if (window) {  // karodo
    }
}

M2C_UNK Audio_PlaySystemSound(M2C_UNK);

/**
 * Runs the 60-frame learn animation: the old move fades out, then at frame 29 the new move replaces it and fades in. Returns 1 when done.
 * Seen in play (2026-11-14) in いちらん: たいあたり faded into どくどく when ゼニガメ learned TM06.
 */
s32 LabMoveSelect_DrawLearnAnimation(LabMoveSelectWindow* window) {
    s32 color; // not a color: the item draw-flags mask for Menu_DrawInlineItems
    s32 params[4]; // only params[0] (alpha) is set here, as in LabMoveSelect_Draw

    if (func_8002AE6C() != 0) {
        return 0;
    }
    if (window->learnTimer > 0) {
        window->learnTimer--;
    }
    if (window->learnTimer >= 30) {
        color = 0xFDED;
        params[0] = (window->learnTimer * 0xFF - 30 * 0xFF) / 30;
    } else {
        if (window->learnTimer == 29) {
            window->moves[window->learnSlot] = window->learnMove;
            Audio_PlaySystemSound(34);
        }
        color = 0xFEED;
        params[0] = ((30 - window->learnTimer) * 0xFF) / 30;
    }
    Menu_DrawInlineItems(&window->menu, window->window.frame.x + 6, window->window.frame.y + 10, color, (s8*)params);
    return window->learnTimer == 0;
}

/**
 * Starts the learn animation of move `move` into slot `slot`.
 * Seen in play (2026-11-14) in いちらん: ran for ゼニガメ slot 0 (たいあたり -> どくどく) and フシギダネ slot 2.
 */
void LabMoveSelect_StartLearnAnimation(LabMoveSelectWindow* window, s32 slot, s32 move) {
    window->learnSlot = slot;
    window->learnMove = move - 1;
    if (window->moves[slot] == -1) {
        window->learnTimer = 60;
    } else {
        window->learnTimer = 60;
    }
    window->menu.itemFlags[slot] |= 0x300;
}

M2C_UNK Menu_UpdateCursor(s32);                         /* extern */

/**
 * Moves the cursor of the move list.
 * Seen in play (2026-11-14) in いちらん: ran while picking the move for ポイントアップ.
 */
s32 LabMoveSelect_Update(s32 window) {
    return Menu_UpdateCursor(window + 0x2C);
}

/**
 * Returns a box row's menu flags: 8 when it is checked, 0x100 (disabled) when it holds no Pokémon.
 * Seen in play (2026-11-14) in いちらん: ボックス1 and 2 (with Pokémon) were selectable and ボックス3-8 were drawn green (empty).
 */
s32 LabBoxList_GetBoxFlags(s8 *box) {
    s32 var_v1;

    var_v1 = 0x100;
    if (M2C_FIELD(box, s32 *, 0xC) != 0) {
        var_v1 = 0x108;
    }
    if (M2C_FIELD(box, s32 *, 0x1C) > 0) {
        var_v1 &= ~0x100;
    }
    return var_v1;
}

/**
 * Does nothing.
 * No callers: no jal, j, address word or lui/addiu pair in any built fragment or the resident code reaches it (2026-11-14 scan), so it never runs.
 * @unverified Name guessed from the code.
 */
void LabPCList_UnusedStub1(void) {
}

/** Updates the flags of every entry in the info widget. */
void LabBoxList_UpdateItemFlags(LabBoxListWindow* box_list) {
    s32 i;
    ByteMatrix** sub = &box_list->menu.items;
    s8* var_s2 = (*sub)->rows;

    for (i = 0; i < (*sub)->count; i++, var_s2 += 0x20) {
        box_list->menu.itemFlags[i] = 0;
        box_list->menu.itemFlags[i] |= LabBoxList_GetBoxFlags(var_s2);
    }
}

/**
 * Checks or unchecks every box of a box list.
 * Seen in play (2026-11-14) in いちらん: A on ゲームボーイのボックス turned all eight box balls red or gray at once.
 */
void LabBoxList_SetAllChecked(u8* widget, s32 enabled) {
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

/**
 * Copies each box row's check into the box, so only checked boxes are listed.
 * Seen in play (2026-11-14) in いちらん: ran on OK; the list then held the Pokémon of GB 1 and GB 2.
 */
void LabBoxList_ApplyChecks(LabBoxListWindow* box_list) {
    s32 i;
    s32* entry = (s32*)box_list->menu.items->rows;

    for (i = 0; i < box_list->menu.items->count; i++) {
        entry[3] = (box_list->menu.itemFlags[i] & 8) != 0;
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
void LabBoxList_DrawBoxName(s32 x, s32 y, s32 box, s32 index, s32 flags) {
    Color_RGBA8 color;
    s32 pad[6]; // FAKE: stack padding
    s32 sel;

    if (flags & 8) {
        Ui_DrawImageInStrips(D_80073614, x + 8, y + 4);
    } else {
        Ui_DrawImageInStrips(D_80073624, x + 8, y + 4);
    }
    sel = flags & 2;
    if (sel) {
        Ui_DrawRoundedFrame(x + 42, y + 2, 112, 24, D_80073520);
        gSPDisplayList(gDisplayListHead++, D_80060290);
        func_8001B884(x + 29, y + 5, 11, 18, D_8910CF80, 0xC, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
    if (flags & 0x100) {
        color = D_8910A934[sel ? 0 : 1];
    } else {
        color = D_800734A8[sel ? 0 : 1];
    }
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(x + 48, y + 4, D_8910E018, index + 1);
    Font_EndTexturedTextRendering();
}


void LabBoxList_DrawBoxName();

/**
 * Sets up a box list window (156 wide, 28 per row) beside the source window.
 * Seen in play (2026-11-14) in いちらん: set up ボックス1-8 and ボックス1-4.
 */
void LabBoxList_Init(LabBoxListWindow* box_list, s32 x, s32 y, ByteMatrix* boxes, s32 item_flags, Color_RGBA8 color) {
    Window_SetRect(&box_list->frame, x, y, 156, boxes->count * 28 + 8);
    box_list->frame.style = 0;
    box_list->frame.color = color;
    Menu_Init(&box_list->menu, boxes, item_flags, LabBoxList_DrawBoxName, 156, 28);
    LabBoxList_UpdateItemFlags(box_list);
}

M2C_UNK Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, M2C_UNK *); /* extern */
M2C_UNK Window_DrawFrame(s8 *);                      /* extern */
M2C_UNK Menu_DrawInlineItems(s8 *, s32, s32, s32, s8 *); /* extern */
extern M2C_UNK D_80073554;

/**
 * Draws a box list window.
 * Seen in play (2026-11-14) in いちらん: drew ボックス1-8 next to ゲームボーイのボックス.
 */
void LabBoxList_Draw(LabBoxListWindow* box_list, s32 flags) {
    Ui_DrawTexturedFrameDecal(box_list->frame.x - 6, box_list->frame.y - 6, box_list->frame.width + 12, box_list->frame.height + 12, &D_80073554);
    Window_DrawFrame(&box_list->frame);
    Menu_DrawInlineItems(&box_list->menu, box_list->frame.x, box_list->frame.y + 4, flags | 0xFFED, box_list);
}

M2C_UNK Audio_PlaySystemSound(M2C_UNK);
extern s32 D_800603C0;

/**
 * Handles a box list: A toggles the box (returns 1), B returns -1, D-Left goes back to the sources (returns 2).
 * Seen in play (2026-11-14) in いちらん: D-Right then A toggled ボックス2 off.
 */
s32 LabBoxList_Update(LabBoxListWindow* box_list) {
    s32 ret = 0;
    s32 res;
    s32 buttons;
    u16* entry;

    res = Menu_UpdateCursor(&box_list->menu);
    if (res == 0x200) {
        Audio_PlaySystemSound(1);
        ret = 2;
    } else if (res == 0) {
        buttons = ((u16*)D_800603C0)[4];
        if (buttons & 0x8000) {
            Audio_PlaySystemSound(2);
            ret = 1;
            box_list->menu.itemFlags[box_list->menu.cursor] ^= 8;
        } else if (buttons & 0x4000) {
            Audio_PlaySystemSound(3);
            ret = -1;
        }
    }
    return ret;
}

typedef struct Entry89105924 { char unk00[0xC]; s32 unk0C; char unk10[0xC]; s32 unk1C; } Entry89105924;
typedef struct List89105924 { char unk00[0x10]; Entry89105924* entries; char unk14[4]; s32 count; } List89105924;
/**
 * Returns a source row's menu flags: 8 when any box is checked, 0x100 when no box holds a Pokémon.
 * Seen in play (2026-11-14) in いちらん: 64カセットのボックス (all four boxes empty) was drawn green.
 */
s32 LabSourceSelect_GetSourceFlags(List89105924* source) {
    Entry89105924* entries = source->entries;
    s32 flags = 0x100;
    s32 i;
    for (i = 0; i < source->count; i++) {
        if (entries[i].unk0C != 0) {
            flags |= 8;
        }
        if (entries[i].unk1C > 0) {
            flags &= ~0x100;
        }
    }
    return flags;
}

/**
 * Checks a source when any of its boxes is checked, and unchecks it otherwise.
 * Seen in play (2026-11-14) in いちらん: ran after toggling ボックス2.
 */
void LabSourceSelect_SyncSourceCheck(LabSourceSelectWindow* window, LabBoxListWindow* box_list) {
    s32 flag = 0;
    s32 i = 0;
    s32 count = box_list->menu.items->count;
    u16* items;

    if (count > 0) {
        if (!window) {} // karodo
        items = box_list->menu.itemFlags;
        do {
            i++;
            if (*items & 8) {
                flag = 8;
                break;
            }
            items++;
        } while (i < count);
    }
    window->menu.itemFlags[window->menu.cursor] &= ~8;
    window->menu.itemFlags[window->menu.cursor] |= flag;
}

/* Rebuild entry flags from the current laboratory records. */
void LabSourceSelect_UpdateItemFlags(u8* widget) {
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
            flags = LabSourceSelect_GetSourceFlags((List89105924*)entry);
            index++;
            entry += 0x24;
            destination = (u16*)(*(u8**)(widget + 0x74) + offset);
            *destination |= flags;
            offset += 2;
        } while (index < *(s32*)(*(u8**)(widget + 0x70) + 8));
    }
}

/** Applies the selection state to an info widget entry. */
void LabSourceSelect_ApplyCheck(LabSourceSelectWindow* window, s32 row) {
    s8* ptr = (s8*)window->menu.items->rows + row * 0x24;
    s8* ptr2 = M2C_FIELD(ptr, s8**, 0x10);

    M2C_FIELD(ptr2, s32*, 0xC) = (window->menu.itemFlags[row] & 8) != 0;
}

void Ui_DrawImageInStrips(void*, s32, s32);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
extern u8 D_80073614[];
extern u8 D_80073624[];
extern Color_RGBA8 D_80073520;
extern Color_RGBA8 D_8910A934[];
extern Color_RGBA8 D_800734A8[];
/**
 * Draws one source row with its Poké Ball check mark.
 * Seen in play (2026-11-14) in いちらん: drew てもち, ゲームボーイのボックス and 64カセットのボックス.
 */
void LabSourceSelect_DrawRow(s32 x, s32 y, char** label, s32 index, s32 flags) {
    Color_RGBA8 color;
    s32 pad[5]; // FAKE: stack padding
    s32 sel;

    if (flags & 8) {
        Ui_DrawImageInStrips(D_80073614, x + 8, y + 4);
    } else {
        Ui_DrawImageInStrips(D_80073624, x + 8, y + 4);
    }
    sel = flags & 2;
    if (sel) {
        Ui_DrawRoundedFrame(x + 42, y + 2, 232, 24, D_80073520);
    }
    if (flags & 0x100) {
        color = D_8910A934[sel ? 0 : 1];
    } else {
        color = D_800734A8[sel ? 0 : 1];
    }
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(x + 48, y + 4, *label);
    Font_EndTexturedTextRendering();
}

void Window_InitLabeled(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5);
void LabSourceSelect_DrawRow(s32 x, s32 y, char** label, s32 index, s32 flags);
void LabSourceSelect_UpdateItemFlags(u8* widget);
void func_8000B2F4(s32);
extern s32 D_800603C0;
extern Color_RGBA8 D_8910A93C;
extern Color_RGBA8 D_8910A940;
extern char D_8910E024[];
/**
 * Sets up the 308x206 「どこのポケモンを いちらん するか えらんでください。」 window, its box lists and the ＯＫ button.
 * Seen in play (2026-11-14) in いちらん: opened on entry with the cursor on ＯＫ.
 */
void LabSourceSelect_Init(LabSourceSelectWindow* window, s32 x, s32 y, s8* sources, Color_RGBA8 color) {
    s32 pad[5]; // FAKE: stack padding
    s32 list;

    Window_SetRect(&window->window, x, y, 308, 206);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 1;
    window->window.frame.color = color;
    Window_SetRect(&window->textFrame, window->window.frame.x + 6, window->window.frame.y + 6, window->window.frame.width - 12, 0x40);
    window->textFrame.style = 6;
    window->textFrame.color = D_8910A93C;
    window->textFrame.color2 = D_8910A940;
    Window_SetRect(&window->listFrame, window->window.frame.x + 6, window->window.frame.y + 76, window->window.frame.width - 12, 124);
    window->listFrame.style = 0;
    window->listFrame.color = color;
    Window_InitLabeled(&window->okButton, window->listFrame.x + 112, window->listFrame.y + 92, 72, color, D_8910E024);
    window->okButton.labelX = 10;
    window->okButton.unk_34 = 0xC;
    list = *(s32*)sources;
    LabBoxList_Init(&window->gbBoxes, window->window.frame.x + window->window.frame.width, window->listFrame.y + 28, (ByteMatrix*)(list + 0x34), (s32)(&window->gbBoxFlags), color);
    LabBoxList_Init(&window->cartBoxes, window->window.frame.x + window->window.frame.width, window->listFrame.y + 56, (ByteMatrix*)(list + 0x58), (s32)(&window->cartBoxFlags), color);
    Menu_Init(&window->menu, sources, (s32)(&window->itemFlags), LabSourceSelect_DrawRow, 296, 28);
    LabSourceSelect_UpdateItemFlags((u8*)window);
    window->cursor.count = 4;
    window->cursor.cursor = 0;
    window->cursor.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    window->cursor.cursor = 3;
    window->openBoxList = 0;
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
/**
 * Draws the source window, the arrow of the source under the cursor and its box list.
 * Seen in play (2026-11-14) in いちらん: drew the window and the open box lists.
 */
void LabSourceSelect_Draw(LabSourceSelectWindow* window, s32 flags) {
    UNUSED s32 pad[3]; // FAKE: stack padding
    s32 sp38 = 0xFFED;
    s32 sp34 = 0;

    if (func_8002AE6C(&window->window) == 0) {
        Window_DrawFrame(&window->textFrame);
        Window_DrawFrame(&window->listFrame);
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + 69, window->window.frame.width, D_8007356C);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
        Font_SetActive(8, 0);
        Font_SetLineHeight(28);
        Font_Printf(window->textFrame.x + 8, window->textFrame.y + 8, D_8910E02C);
        Font_EndTexturedTextRendering();
        if ((flags & 2) && (window->openBoxList == 0)) {
            if (window->cursor.cursor == 3) {
                sp34 = 2;
            } else {
                sp38 = 0xFFEF;
                if ((window->cursor.cursor == 1) || (window->cursor.cursor == 2)) {
                    gSPDisplayList(gDisplayListHead++, D_80060290);
                    func_8001B884((window->listFrame.x + window->listFrame.width) - 17, window->listFrame.y + (window->cursor.cursor * 28) + 9, 11, 18, D_8910D138, 0xC, 0x200000);
                    gSPDisplayList(gDisplayListHead++, D_80060398);
                }
            }
        }
        Menu_DrawInlineItems(&window->menu, window->listFrame.x, window->listFrame.y + 4, sp38, window);
        Window_DrawLabeled(&window->okButton, sp34);
        if (window->cursor.cursor == 1) {
            LabBoxList_Draw(&window->gbBoxes, (window->openBoxList == 1) ? 2 : 0);
        } else if (window->cursor.cursor == 2) {
            LabBoxList_Draw(&window->cartBoxes, (window->openBoxList == 2) ? 2 : 0);
        }
    }
}

s32 func_8002B2B0(s8*);

/**
 * Handles the source rows and ＯＫ: A toggles a source with all its boxes, D-Right opens its box list, A on ＯＫ applies the checks (returns 1), B returns -1.
 * Seen in play (2026-11-14) in いちらん: each of those inputs did that.
 */
s32 LabSourceSelect_UpdateSources(LabSourceSelectWindow* window) {
    s32 ret = 0;
    s32 res;
    s32 buttons;

    res = func_8002B2B0(&window->cursor);
    if (res == 0x100) {
        if (window->cursor.cursor == 1) {
            Audio_PlaySystemSound(1);
            window->openBoxList = 1;
        } else if (window->cursor.cursor == 2) {
            Audio_PlaySystemSound(1);
            window->openBoxList = 2;
        }
    } else if (res == 0) {
        buttons = ((u16*)D_800603C0)[4];
        if (buttons & 0x8000) {
            if (window->cursor.cursor == 3) {
                Audio_PlaySystemSound(2);
                LabSourceSelect_ApplyCheck(window, 0);
                LabBoxList_ApplyChecks(&window->gbBoxes);
                LabBoxList_ApplyChecks(&window->cartBoxes);
                ret = 1;
            } else {
                Audio_PlaySystemSound(2);
                window->menu.itemFlags[window->menu.cursor] ^= 8;
                if (window->cursor.cursor == 1) {
                    LabBoxList_SetAllChecked((u8*)(&window->gbBoxes), window->menu.itemFlags[window->menu.cursor] & 8);
                } else if (window->cursor.cursor == 2) {
                    LabBoxList_SetAllChecked((u8*)(&window->cartBoxes), window->menu.itemFlags[window->menu.cursor] & 8);
                }
            }
        } else if (buttons & 0x4000) {
            Audio_PlaySystemSound(3);
            ret = -1;
        }
    }
    if (window->cursor.cursor < 4) {
        window->menu.cursor = window->cursor.cursor;
    }
    return ret;
}

/**
 * Runs the source window, passing input to the open box list if there is one.
 * Seen in play (2026-11-14) in いちらん: ran the whole time the window was open.
 */
s32 LabSourceSelect_Update(LabSourceSelectWindow* window) {
    s32 ret = 0;
    s32 r;

    if (window->window.state == 0) {
        return 0;
    }
    switch (window->openBoxList) {
        case 0:
            ret = LabSourceSelect_UpdateSources(window);
            break;
        case 1:
            r = LabBoxList_Update(&window->gbBoxes);
            if (r == -1) {
                ret = -1;
            } else if (r == 1) {
                LabSourceSelect_SyncSourceCheck(window, &window->gbBoxes);
            } else if (r == 2) {
                window->openBoxList = 0;
            }
            break;
        case 2:
            r = LabBoxList_Update(&window->cartBoxes);
            if (r == -1) {
                ret = -1;
            } else if (r == 1) {
                LabSourceSelect_SyncSourceCheck(window, &window->cartBoxes);
            } else if (r == 2) {
                window->openBoxList = 0;
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
void LabPCList_DrawPopupRow(s32 x, s32 y, char* text, s32 index, s32 flags, s8* popup) {
    s32 temp_v0 = M2C_FIELD(popup, s32*, 8) - 0xC;

    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, temp_v0 - 6, 22, M2C_FIELD(popup, Color_RGBA8*, 0x18));
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(8, 0);
    Font_Printf(x + 8, y + 4, text);
    Font_EndTexturedTextRendering();
}

/**
 * Sets up a popup menu sized to its widest string.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): A on フシギダネ set up the popup
 * (フシギダネをあつめる, おなじタイプをあつめる, いどうする, どうぐをつかう).
 */
void LabPCList_InitPopupMenu(LabPopupMenu* popup, s32 *labels, s32 item_flags, s32 count, s32 message) {
    s32 i;
    s32 w;
    s32 max = 0;
    s32 h;

    popup->title = message;
    for (i = 0; i < count; i++) {
        w = func_800566BC(labels[i]) >> 1;
        if (max < w) {
            max = w;
        }
    }
    func_80027804((s8*)&popup->itemList, labels, count, count);
    h = max * 20 + 0x10;
    Menu_Init((s8*)&popup->menu, (s8*)&popup->itemList, item_flags, LabPCList_DrawPopupRow, h, 28);
    popup->menu.options |= 0x10000;
    Window_SetRect(popup, 0, 0, h + 12, popup->itemList.count * 28 + 20);
    popup->window.animTimer = 0;
    M2C_FIELD(popup, s32 *, 0x20) = 0;
    popup->window.state = 0;
    if (message != 0) {
        popup->window.frame.style = 0x800;
    } else {
        popup->window.frame.style = 0;
    }
    if (message != 0) {
        M2C_FIELD(popup, s32 *, 0x20) = message;
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
void LabPCList_PlacePopup(LabPopupMenu* popup) {
    s32 over;

    if (popup->window.frame.style & 0x01000000) {
        if (popup->limitY >= popup->anchorY + popup->window.frame.height) {
            popup->window.frame.y = popup->anchorY;
        } else {
            over = (popup->anchorY + popup->window.frame.height) - popup->limitY;
            popup->window.frame.y = popup->anchorY - ((over > 8) ? over : 8);
        }
        if (popup->limitX >= popup->anchorX + popup->anchorW + popup->window.frame.width) {
            popup->window.frame.x = popup->anchorX + popup->anchorW;
        } else {
            popup->window.frame.x = popup->anchorX - popup->window.frame.width;
        }
    } else {
        if (popup->limitX >= popup->anchorX + popup->window.frame.width) {
            popup->window.frame.x = popup->anchorX;
        } else {
            over = (popup->anchorX + popup->window.frame.width) - popup->limitX;
            popup->window.frame.x = popup->anchorX - ((over > 8) ? over : 8);
        }
        if (popup->limitY >= popup->anchorY + popup->anchorH + popup->window.frame.height) {
            popup->window.frame.y = popup->anchorY + popup->anchorH;
        } else {
            popup->window.frame.y = popup->anchorY - popup->window.frame.height;
        }
    }
    popup->window.animTimer = 0;
}

s32 func_8002AE6C();                                /* extern */
/**
 * Draws a popup menu's items.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): drew that popup's four rows.
 */
void LabPCList_DrawPopupMenu(LabPopupMenu* popup, s32 flags)
{
  s8 *new_var; // FAKE: permuter temp
  if (func_8002AE6C() == 0)
  {
    new_var = (s8 *) popup; // FAKE: permuter temp
    if ((popup && popup) && popup) // FAKE: empty if on a repeated test
    {
    }
    Menu_DrawItems((s8*)&popup->menu, (*((s32 *) (((s8 *) popup) + 0))) + 6, (*((s32 *) (new_var + 4))) + 10, flags | 0xFFED, popup); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    if (flags) // karodo
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
s32 LabPCList_UpdatePopupMenu(LabPopupMenu* popup) {
    return Menu_UpdateCursor((s32)&popup->menu);
}

extern char D_8910E064[];
extern Color_RGBA8 D_8910A94C;
extern char D_8910E07C[];
extern char D_8910E088[];
/**
 * Sets up the レベルのにゅうりょく (level input) window.
 * Seen in play (2026-11-12) in いちらん: レベルをきめてあつめる (page 3/3, A on the レベル header) ran this once
 * and opened 「001 から 100」; かいじょ is grayed out when no level filter is active.
 */
void LabPCList_InitLevelInputWindow(LabLevelInputWindow* window, s32 x, s32 y, Color_RGBA8 color, s32 min_level, s32 max_level, s32 filter_on) {
    Window_SetRect(window, x, y, 316, 80);
    window->window.animTimer = 0;
    window->window.state = 0;
    window->window.frame.style = 0x800;
    window->window.title = D_8910E064;
    window->window.frame.color = color;
    window->minLevel.digitCount = 3;
    window->minLevel.value = min_level;
    window->minLevel.min = 1; window->minLevel.max = 100; // IDO: same line
    window->minLevel.digit = 0;
    window->maxLevel.digitCount = 3;
    window->maxLevel.value = max_level;
    window->maxLevel.digit = 0;
    window->maxLevel.max = 100;
    window->maxLevel.min = 1;
    Window_InitLabeled((s8*)&window->gatherButton, window->window.frame.x + 210, window->window.frame.y + 14, 92, D_8910A94C, D_8910E07C);
    Window_InitLabeled((s8*)&window->clearButton, window->window.frame.x + 210, window->window.frame.y + 42, 92, D_8910A94C, D_8910E088);
    if (filter_on == 0) {
        window->clearButton.flags |= 1;
    }
    window->cursor.cursor = 0;
    window->cursor.count = 2;
    M2C_FIELD(window, s32*, 0xCC) = D_800603C0;
    func_8000B2F4(D_800603C0);
    window->column = 2; window->unk_E0 = 7; // IDO: same line
    window->unk_D8 = D_800603C0;
    func_8000B2F4(D_800603C0);
    window->focus = 0;
}

extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern u8 D_04002130[];
extern u8 D_04002238[];
extern u8 D_04002340[];
extern u8 D_04002448[];
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
extern Color_RGBA8 D_80073520;
void Font_DrawCharAt(s32 x, s32 y, s32 chr);

/**
 * Draws the level input digits and the up/down arrows.
 * Seen in play (2026-11-12) in いちらん: drew the three digits of each bound with a yellow frame on
 * the selected digit.
 */
void LabPCList_DrawLevelInput(s8* input, s32 x, s32 y, s32 flags) {
    s32 hl = flags & 2;
    s32 bx;
    s32 v;

    if (hl & 2) {
        bx = x - M2C_FIELD(input, s32*, 0x10) * 0x16 + 0x2C;
        gSPDisplayList(gDisplayListHead++, D_80073408);
        if (((u16*)D_800603C0)[3] & 0x800) {
            v = (s32)D_04002340;
        } else {
            v = (s32)D_04002130;
        }
        func_8001B884(bx + 3, y - 10, 14, 8, (u8*)v, 0x10, 0x200000);
        if (((u16*)D_800603C0)[3] & 0x400) {
            v = (s32)D_04002448;
        } else {
            v = (s32)D_04002238;
        }
        func_8001B884(bx + 3, y + 22, 14, 8, (u8*)v, 0x10, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
        Ui_DrawRoundedFrame(bx - 3, y - 3, 26, 26, D_80073520);
    }
    func_8001AB6C();
    func_8001A384(8, 2);
    v = (M2C_FIELD(input, s32*, 0x10) == 2) ? hl : 0;
    Font_SetColorForFlags(v);
    Font_DrawCharAt(x, y, M2C_FIELD(input, s32*, 0) / 100 + '0');
    v = (M2C_FIELD(input, s32*, 0x10) == 1) ? hl : 0;
    Font_SetColorForFlags(v);
    Font_DrawCharAt(x + 22, y, M2C_FIELD(input, s32*, 0) / 10 % 10 + '0');
    v = (M2C_FIELD(input, s32*, 0x10) == 0) ? hl : 0;
    Font_SetColorForFlags(v);
    Font_DrawCharAt(x + 44, y, M2C_FIELD(input, s32*, 0) % 10 + '0');
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
void LabPCList_DrawLevelInputWindow(LabLevelInputWindow* window) {
    if (func_8002AE6C() == 0) {
        func_8001AB6C();
        func_8001A384(4, 0);
        func_8001AA9C(0xC8, 0xC8, 0xFF, 0xFF); // #C8C8FFFF
        Font_Printf(window->window.frame.x + 84, window->window.frame.y + 19, D_8910E094);
        func_8001ABBC();
        LabPCList_DrawLevelInput((s8*)&window->minLevel, window->window.frame.x + 14, window->window.frame.y + 0x10, (window->focus == 0) ? 2 : 0);
        LabPCList_DrawLevelInput((s8*)&window->maxLevel, window->window.frame.x + 122, window->window.frame.y + 0x10, (window->focus == 1) ? 2 : 0);
        Window_DrawLabeled((s8*)&window->gatherButton, (window->focus == 2 && window->cursor.cursor == 0) ? 2 : 0);
        Window_DrawLabeled((s8*)&window->clearButton, (window->focus == 2 && window->cursor.cursor == 1) ? 2 : 0);
    }
}

s32 func_8000B30C();                                /* extern */
M2C_UNK func_8002B204(s8 *, s32, s8 *);         /* extern */
M2C_UNK func_8002B2E4(s32, s32, s8 *);            /* extern */
M2C_UNK func_8002B4B4(s8 *, s32, s8 *);         /* extern */
s32 func_8002BC14(s32, s32, s8 *);                /* extern */
M2C_UNK Audio_PlaySystemSound(M2C_UNK);                     /* extern */
extern s32 D_800603C0;

/**
 * Handles the level input digits.
 * Seen in play (2026-11-12) in いちらん: D-Up raised the selected digit (001 to 006), D-Right moved
 * across the six digits to あつめる/かいじょ, and A on those returned 1 or 2.
 */
s32 LabPCList_UpdateLevelInput(LabLevelInputWindow* window) {
    s32 sp1C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;

    sp1C = 0;
    temp_v1 = func_8000B30C() & 0xFFFF;
    if (temp_v1 & 0x300) {
        func_8002B2E4((s8*)&window->unk_D8, temp_v1, window);
        temp_v1_2 = window->column;
        if (temp_v1_2 < 3) {
            window->focus = 0;
            window->minLevel.digit = (s32) (2 - temp_v1_2);
        } else if (temp_v1_2 < 6) {
            window->focus = 1;
            window->maxLevel.digit = (s32) (5 - temp_v1_2);
        } else {
            window->focus = 2;
            window->cursor.cursor = 0;
        }
    } else if (temp_v1 & 0xC00) {
        temp_v0 = window->focus;
        switch (temp_v0) {                          /* irregular */
        case 0:
            func_8002B4B4((s8*)&window->minLevel, temp_v1, window);
            break;
        case 1:
            func_8002B4B4((s8*)&window->maxLevel, temp_v1, window);
            break;
        case 2:
            func_8002B204((s8*)&window->cursor, temp_v1, window);
            break;
        }
    } else if (temp_v1 == 0) {
        temp_v0_2 = func_8002BC14(D_800603C0, temp_v1, window);
        if (temp_v0_2 == -1) {
            Audio_PlaySystemSound(3);
            sp1C = -1;
        } else if ((temp_v0_2 == 1) && (window->focus == 2)) {
            if (window->cursor.cursor == 0) {
                Audio_PlaySystemSound(2);
                sp1C = 1;
            } else if (!(window->clearButton.flags & 1)) {
                Audio_PlaySystemSound(2);
                sp1C = 2;
            } else {
                Audio_PlaySystemSound(8);
            }
        }
    }
    return sp1C;
}

/**
 * Sets up a two-state image toggle.
 * No callers: no jal, j, address word or lui/addiu pair in any built fragment or the resident code reaches it (2026-11-14 scan), so it never runs.
 * @unverified Name guessed from the code.
 */
void LabToggle_Init(s8 *toggle, s32 x, s32 y, s32 width, s32 tex) {
    Window_SetRect(toggle, x, y, width, 0);
    M2C_FIELD(toggle, s32 *, 0x14) = tex;
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
/**
 * Draws a two-state image toggle, each end lit by flag 8.
 * No callers: no jal, j, address word or lui/addiu pair in any built fragment or the resident code reaches it (2026-11-14 scan), so it never runs.
 * @unverified Name guessed from the code.
 */
void LabToggle_Draw(Win89106E64* toggle) {
    gSPDisplayList(gDisplayListHead++, D_80073408);
    func_8001B884(toggle->x, toggle->y, toggle->tex->width, toggle->tex->height,
                  (toggle->flags & 8) ? toggle->tex->img08 : toggle->tex->img0C, toggle->tex->width, 0x200000);
    func_8001B884(toggle->x + toggle->width - toggle->tex->width, toggle->y, toggle->tex->width, toggle->tex->height,
                  (toggle->flags & 8) ? toggle->tex->img14 : toggle->tex->img10, toggle->tex->width, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}

typedef struct unk_func_89106F74 {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ s32 flags;
} unk_func_89106F74;

/**
 * D-Left sets a toggle's flag 8 and D-Right clears it.
 * No callers: no jal, j, address word or lui/addiu pair in any built fragment or the resident code reaches it (2026-11-14 scan), so it never runs.
 * @unverified Name guessed from the code.
 */
s32 LabToggle_Update(unk_func_89106F74* arg0) {
    s32 flags = arg0->flags;
    s32 ret = 0;

    if (flags & 1) {
        return 0;
    }
    if (gPlayer1Controller->buttonPressed & 0x200) {
        arg0->flags = flags | 8;
        ret = 0x200;
    } else if (gPlayer1Controller->buttonPressed & 0x100) {
        arg0->flags = flags & ~8;
        ret = 0x100;
    }
    return ret;
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
void LabPCList_DrawTypeFilterRow(s32 x, s32 y, char **name, s32 index, s32 flags) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y + 1, 174, 26, *(Color_RGBA8 *)D_8910A968);
    func_80029028(x, y, 174, 1, *(Color_RGBA8 *)D_8910A970);
    func_80029028(x, y + 27, 174, 1, *(Color_RGBA8 *)D_8910A970);
    if (flags & 8) {
        Ui_FillRectHighlighted(x + 3, y + 3, 168, 22, *(Color_RGBA8 *)D_8910A968);
    }
    Ui_DrawNumber(x + 9, y + 8, index + 1, 2);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(8, 0);
    Font_Printf(x + 66, y + 4, *name);
    Font_EndTexturedTextRendering();
}

/**
 * Converts a type id to its row in the type list, skipping the unused ids 6 and 9-19.
 * Seen in play (2026-11-14) in いちらん: reopening タイプであつめる showed ひこう in row 3.
 */
s32 LabPCList_TypeIdToListIndex(s32 a) {
    return a >= 20 ? a - 12 : (a >= 7 ? a - 1 : a);
}

/**
 * Converts a row of the type list to a type id, skipping the unused ids 6 and 9-19.
 * Seen in play (2026-11-14) in いちらん: row 3 of タイプであつめる became ひこう (2), and あつめる left only ポッポ.
 */
s32 LabPCList_ListIndexToTypeId(s32 a) {
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
void LabPCList_InitTypeFilter(LabTypeFilterWindow* window, s32 x, s32 y, s32* filter) {
    s32 i;

    Window_SetRect((s8*)window, x, y, 342, 288);
    window->window.animTimer = 0;
    window->window.title = NULL;
    window->window.state = 0;
    window->window.frame.style = 0x800;
    window->window.frame.color = D_8910A974;
    window->window.title = D_8910E09C;
    func_80027804(&window->typeList, (s32*)window->names, 0xF, 0xF);
    for (i = 0; i < 0xF; i++) {
        window->names[i] = (s8*)&D_80066AD8[i + ((i < 6) ? 0 : 1)];
    }
    ScrollList_Init(&window->list, (s32)&window->typeList, (s32)window->typeFlags, 8, LabPCList_DrawTypeFilterRow, 174, 28);
    window->list.options |= 0x10000;
    for (i = 0; i < *filter; i++) {
        window->slots[i].index = LabPCList_TypeIdToListIndex(((u8*)filter)[4 + i]);
    }
    for (; i < 2; i++) {
        window->slots[i].index = -1;
    }
    for (i = 0; i < 2; i++) {
        if (window->slots[i].index == -1) {
            Window_InitLabeled(&window->slots[i].button, window->window.frame.x + 0x20, window->window.frame.y + i * 28 + 34, 92, D_8910A974, D_8910E0B0);
        } else {
            Window_InitLabeled(&window->slots[i].button, window->window.frame.x + 0x20, window->window.frame.y + i * 28 + 34, 92, D_8910A974, *(char**)window->names[window->slots[i].index]);
            window->list.itemFlags[window->slots[i].index] |= 8;
        }
    }
    Window_InitLabeled(&window->gatherButton, window->window.frame.x + 0x20, window->window.frame.y + 202, 92, D_8910A974, D_8910E0B8);
    Window_InitLabeled(&window->clearButton, window->window.frame.x + 0x20, window->window.frame.y + 230, 92, D_8910A974, D_8910E0C4);
    if (*filter == 0) {
        window->clearButton.flags |= 1;
    }
    window->cursor.cursor = 0;
    window->cursor.count = 4;
    window->cursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    window->mode = 0;
}

extern u8 D_800735C4[];
void ScrollList_DrawItems(s8*, s32, s32, s32, s32);

/**
 * Draws the type filter window.
 * Seen in play (2026-11-12) in いちらん: drew the タイプであつめる window.
 */
void LabPCList_DrawTypeFilter(LabTypeFilterWindow* window) {
    s32 i;
    s32 hl;
    s32 mask;

    if (func_8002AE6C() == 0) {
        hl = (window->mode == 0) ? 2 : 0x10;
        for (i = 0; i < 2; i++) {
            Window_DrawLabeled(&window->slots[i].button, (i == window->cursor.cursor) ? hl : 0);
        }
        hl = (window->mode == 0) ? 2 : 0;
        Window_DrawLabeled(&window->gatherButton, (window->cursor.cursor == 2) ? hl : 0);
        Window_DrawLabeled(&window->clearButton, (window->cursor.cursor == 3) ? hl : 0);
        Ui_DrawTexturedFrameDecal(window->window.frame.x + 150, window->window.frame.y + 14, 178, 260, D_800735C4);
        mask = 0xFFED;
        if (window->mode == 1) {
            mask = 0xFFEF;
        }
        ScrollList_DrawItems(&window->list, window->window.frame.x + 152, window->window.frame.y + 0x20, mask, 0);
    }
}

s32 ScrollList_UpdateCursor(s8*);



/**
 * Handles the type filter window. Returns -1 on cancel, 1 on confirm, 2 on clear.
 * Seen in play (2026-11-12) in いちらん: handled the タイプであつめる window; A moved the cursor into the
 * type list (1 ノーマル).
 */
s32 LabPCList_UpdateTypeFilter(LabTypeFilterWindow* window) {
    s32 ret = 0;
    u16 buttons;

    switch (window->mode) {
        case 0:
            if (func_8002B2B0(&window->cursor) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    Audio_PlaySystemSound(3);
                    ret = -1;
                } else if (buttons & 0x8000) {
                    switch (window->cursor.cursor) {
                        case 0:
                        case 1:
                            Audio_PlaySystemSound(2);
                            window->mode = 1;
                            break;
                        case 2:
                            Audio_PlaySystemSound(2);
                            ret = 1;
                            break;
                        case 3:
                            if (window->clearButton.flags & 1) {
                                Audio_PlaySystemSound(8);
                            } else {
                                Audio_PlaySystemSound(2);
                                ret = 2;
                            }
                            break;
                    }
                }
            }
            break;
        case 1:
            if (ScrollList_UpdateCursor(&window->list) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    Audio_PlaySystemSound(3);
                    window->mode = 0;
                } else if (buttons & 0x8000) {
                    if (window->list.itemFlags[window->list.cursor] & 8) {
                        Audio_PlaySystemSound(8);
                    } else {
                        s32 prev;

                        Audio_PlaySystemSound(2);
                        prev = window->slots[window->cursor.cursor].index;
                        if (prev != -1) {
                            window->list.itemFlags[prev] &= ~8;
                        }
                        window->list.itemFlags[window->list.cursor] |= 8;
                        window->slots[window->cursor.cursor].index = window->list.cursor;
                        window->slots[window->cursor.cursor].button.label = *(char**)window->names[window->list.cursor];
                        window->mode = 0;
                        window->cursor.cursor++;
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
void LabPCList_CommitTypeFilter(LabTypeFilterWindow* window, s32* filter) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (window->slots[i].index != -1) {
            M2C_FIELD((s8*)filter + count, s8*, 4) = LabPCList_ListIndexToTypeId(window->slots[i].index);
            count++;
        }
    }
    *filter = count;
}

extern u8 D_8910AAC0[];
extern u8 D_8910AAC8[];
/**
 * Draws one numbered row of the move filter list.
 * Seen in play (2026-11-12) in いちらん: drew the numbered move rows of わざであつめる (row index 0 = 1
 * 10まんボルト, 1 = 2 あくまのキッス).
 */
void LabPCList_DrawMoveFilterRow(s32 x, s32 y, u8* move, s32 index, s32 flags) {
    s32 idx;

    idx = *move;
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y + 1, 212, 26, *(Color_RGBA8 *)D_8910AAC0);
    func_80029028(x, y, 212, 1, *(Color_RGBA8 *)D_8910AAC8);
    func_80029028(x, y + 27, 212, 1, *(Color_RGBA8 *)D_8910AAC8);
    if (flags & 8) {
        Ui_FillRectHighlighted(x + 3, y + 3, 206, 22, *(Color_RGBA8 *)D_8910AAC0);
    }
    Ui_DrawNumber(x + 9, y + 8, index + 1, 3);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(8, 0);
    Font_Printf(x + 55, y + 4, D_8006A9D4[idx].name);
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
void LabPCList_InitMoveFilter(LabMoveFilterWindow* window, s32 x, s32 y, u8* filter) {
    s32 i;

    Window_SetRect((s8*)window, x, y, 404, 288);
    window->window.animTimer = 0;
    window->window.title = NULL;
    window->window.state = 0;
    window->window.frame.style = 0x800;
    window->window.frame.color = D_8910AACC;
    window->window.title = D_8910E0D0;
    func_80027410(&window->moveMatrix, D_8910A978, 1, 0xA4, 0xA4);
    ScrollList_Init(&window->list, (s32)&window->moveMatrix, (s32)window->moveFlags, 8, LabPCList_DrawMoveFilterRow, 212, 28);
    window->list.options |= 0x10000;
    for (i = 0; i < M2C_FIELD(filter, s32*, 4); i++) {
        window->slots[i].index = D_8910AA1C[filter[i] - 1];
    }
    for (; i < 4; i++) {
        window->slots[i].index = -1;
    }
    for (i = 0; i < 4; i++) {
        if (window->slots[i].index == -1) {
            Window_InitLabeled(&window->slots[i].button, window->window.frame.x + 14, window->window.frame.y + i * 28 + 34, 152, D_8910AACC, D_8910E0E0);
        } else {
            Window_InitLabeled(&window->slots[i].button, window->window.frame.x + 14, window->window.frame.y + i * 28 + 34, 152, D_8910AACC, (char*)D_8006A9D4[D_8910A978[window->slots[i].index]].name);
            window->list.itemFlags[window->slots[i].index] |= 8;
        }
    }
    Window_InitLabeled(&window->gatherButton, window->window.frame.x + 74, window->window.frame.y + 202, 92, D_8910AACC, D_8910E0E8);
    Window_InitLabeled(&window->clearButton, window->window.frame.x + 74, window->window.frame.y + 230, 92, D_8910AACC, D_8910E0F4);
    if (M2C_FIELD(filter, s32*, 4) == 0) {
        window->clearButton.flags |= 1;
    }
    window->cursor.cursor = 0;
    window->cursor.count = 6;
    window->cursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
    window->mode = 0;
}

void ScrollList_DrawInlineItems(s8*, s32, s32, s32, s32);

/**
 * Draws the move filter window.
 * Seen in play (2026-11-12) in いちらん: ran every frame while わざであつめる was open.
 */
void LabPCList_DrawMoveFilter(LabMoveFilterWindow* window) {
    s32 i;
    s32 hl;
    s32 mask;

    if (func_8002AE6C() == 0) {
        hl = (window->mode == 0) ? 2 : 0x10;
        for (i = 0; i < 4; i++) {
            Window_DrawLabeled(&window->slots[i].button, (i == window->cursor.cursor) ? hl : 0);
        }
        hl = (window->mode == 0) ? 2 : 0;
        Window_DrawLabeled(&window->gatherButton, (window->cursor.cursor == 4) ? hl : 0);
        Window_DrawLabeled(&window->clearButton, (window->cursor.cursor == 5) ? hl : 0);
        Ui_DrawTexturedFrameDecal(window->window.frame.x + 174, window->window.frame.y + 14, 216, 260, D_800735C4);
        mask = 0xFFED;
        if (window->mode == 1) {
            mask = 0xFFEF;
        }
        ScrollList_DrawInlineItems(&window->list, window->window.frame.x + 176, window->window.frame.y + 0x20, mask, 0);
    }
}

extern u8 D_8910A978[];

/**
 * Handles the move filter window. Returns -1 on cancel, 1 on confirm, 2 on clear.
 * Seen in play (2026-11-12) in いちらん: handled わざであつめる. あつめる led to the commit path (1) and かいじょ to
 * the clear path (2).
 */
s32 LabPCList_UpdateMoveFilter(LabMoveFilterWindow* window) {
    s32 ret = 0;
    u16 buttons;

    switch (window->mode) {
        case 0:
            if (func_8002B2B0(&window->cursor) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    Audio_PlaySystemSound(3);
                    ret = -1;
                } else if (buttons & 0x8000) {
                    switch (window->cursor.cursor) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            Audio_PlaySystemSound(2);
                            window->mode = 1;
                            break;
                        case 4:
                            Audio_PlaySystemSound(2);
                            ret = 1;
                            break;
                        case 5:
                            if (window->clearButton.flags & 1) {
                                Audio_PlaySystemSound(8);
                            } else {
                                Audio_PlaySystemSound(2);
                                ret = 2;
                            }
                            break;
                    }
                }
            }
            break;
        case 1:
            if (ScrollList_UpdateCursor(&window->list) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    Audio_PlaySystemSound(3);
                    window->mode = 0;
                } else if (buttons & 0x8000) {
                    if (window->list.itemFlags[window->list.cursor] & 8) {
                        Audio_PlaySystemSound(8);
                    } else {
                        s32 prev;

                        Audio_PlaySystemSound(2);
                        prev = window->slots[window->cursor.cursor].index;
                        if (prev != -1) {
                            window->list.itemFlags[prev] &= ~8;
                        }
                        window->list.itemFlags[window->list.cursor] |= 8;
                        window->slots[window->cursor.cursor].index = window->list.cursor;
                        window->slots[window->cursor.cursor].button.label = (s32)D_8006A9D4[D_8910A978[window->list.cursor]].name;
                        window->mode = 0;
                        window->cursor.cursor++;
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
void LabPCList_CommitMoveFilter(LabMoveFilterWindow* window, u8* filter) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (window->slots[i].index != -1) {
            filter[count++] = D_8910A978[window->slots[i].index] + 1;
        }
    }
    M2C_FIELD(filter, s32*, 4) = count;
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
 * Seen in play (2026-11-14) in いちらん: drew マックスアップ ×05 てもち ... わざマシン06 ×01 てもち in 「フシギダネがつかえるどうぐ」.
 */
void LabPCList_DrawItemRow(s32 x, s32 y, u8** item, UNUSED s32 index, s32 flags) {
    char buf[0x38];

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y + 1, 268, 26, D_8910AAD0);
    func_80029028(x + 268, y + 1, 108, 26, D_8910AAD4);
    func_80029028(x, y, 376, 1, D_8910AAD8);
    func_80029028(x, y + 27, 376, 1, D_8910AAD8);
    if (item != NULL) {
        if (flags & 0x10) {
            Ui_FillRectHighlighted(x + 3, y + 3, 265, 22, D_8910AAD0);
            Ui_FillRectHighlighted(x + 268, y + 3, 105, 22, D_8910AAD4);
        }
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(8, 0);
        Font_Printf(x + 8, y + 4, func_8001FDC8(item[0][0], buf));
        if (item[1][0] == 0x12) {
            func_8001A384(8, 0);
            Font_Printf(x + 288, y + 4, D_8910E100);
        } else if (item[1][0] == 0x22) {
            func_8001A384(8, 0);
            Font_Printf(x + 288, y + 4, D_8910E104);
        } else {
            func_8001A384(8, 0);
            Font_Printf(x + 288, y + 4, D_8910E110);
        }
        if (func_80031CC8(item[0][0]) == 0) {
            func_8001A384(8, 0);
            Font_Printf(x + 188, y + 4, D_8910E118, item[0][1]);
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

/**
 * Grays out the items whose usability flags (LabPCList_UpdateItemUsability) say they can't be used on the Pokémon.
 * Seen in play (2026-11-14) in いちらん: ran when どうぐをつかう opened 「フシギダネがつかえるどうぐ」.
 * Matching note: the entries pointer is held in a local and indexed; advancing a pointer through
 * window->table->entries directly gives a different register assignment.
 */
void LabPCList_DisableUnusableItems(FlagScanOwner* window) {
    s32 i;
    FlagScanEntry** entries;

    entries = window->table->entries;
    for (i = 0; i < window->table->count; i++) {
        if (entries[i]->word10 & 0x1F) {
            window->flags[i] |= 1;
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
void LabPCList_DrawItemRow();
/**
 * Sets up the window that uses an item on the selected Pokemon.
 * Seen in play (2026-11-12) in いちらん: どうぐをつかう on フシギダネ opened 「フシギダネがつかえるどうぐ」, listing the bag
 * items from the Game Boy save (マックスアップ ×5, タウリン ×5, ふしぎなアメ ×5, ポイントアップ ×3, わざマシン06, ひでんマシン01).
 */
void LabPCList_InitItemWindow(LabItemWindow* window, s32 x, s32 y, s32 items, s32 item_flags, u8* mon) {
    Window_SetRect(&window->window, x, y, 388, 366);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 0x801;
    func_8000A460(D_89119BD0, *(s8**)D_80064C44[mon[8]]);
    *(Str891084B4*)(func_800566BC((s32)D_89119BD0) + D_89119BD0) = *(Str891084B4*)D_8910E120;
    window->window.title = (char*)D_89119BD0;
    Window_SetRect(&window->textFrame, x + 6, y + 268, 376, 92);
    window->textFrame.style = 6;
    *(Rgba891084B4*)&window->textFrame.color = *(Rgba891084B4*)D_8910AAE0;
    *(Rgba891084B4*)&window->textFrame.color2 = *(Rgba891084B4*)D_8910AAE4;
    ScrollList_Init(&window->list, items, item_flags, 8, LabPCList_DrawItemRow, 376, 28);
    window->list.options |= 0x10000;
    LabPCList_DisableUnusableItems((FlagScanOwner*)window);
    window->mon = mon;
    window->mode = 0;
}

extern Color_RGBA8 D_800734B8[];
extern char D_8910E134[];
extern char D_8910E150[];
extern char D_8910E16C[];
char* func_80031BC0(u8, char*);
/**
 * Draws このどうぐをつかいますか？ (Use this item?), どの わざに つかいますか？ (On which move?) or どの わざを わすれさせたい？ (Which move should it forget?).
 * Seen in play (2026-11-14) in いちらん: drew the item list with このどうぐをつかいますか？, どの わざに つかいますか？ and どの わざを わすれさせたい？, and the move list and learn animation under them.
 */
void LabPCList_DrawItemWindow(LabItemWindow* window) {
    s32 flags;
    s32 x;
    s32 y;
    char buf[0x70];

    if (Window_DrawAnimatedFrame() == 0) {
        Window_DrawFrame(&window->textFrame);
        Ui_DrawTexturedDivider(window->window.frame.x, window->textFrame.y - 7, window->window.frame.width, D_8007356C);
        flags = 0xFFED;
        flags |= (window->mode == 0) ? 2 : 0x10;
        ScrollList_DrawItems(&window->list, window->window.frame.x + 6, window->window.frame.y + 22, flags, 0);
        if (window->list.items->count > 0) {
            Font_BeginTranslucentTextRendering();
            Font_SetActive(8, 0);
            Font_SetLineHeight(28);
            x = window->textFrame.x + 8;
            y = window->textFrame.y + 8;
            switch (window->mode) {
                case 0:
                    Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
                    Font_Printf(x, y + 28, func_80031BC0(**((u8***)window->list.items->rows)[window->list.cursor], buf));
                    break;
                case 1:
                    Gfx_SetEnvColor(D_800734B8[0].r, D_800734B8[0].g, D_800734B8[0].b, D_800734B8[0].a);
                    Font_Printf(x, y, D_8910E134);
                    Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
                    Font_Printf(x, y + 28, func_80031BC0(**((u8***)window->list.items->rows)[window->list.cursor], buf));
                    break;
                case 2:
                    Gfx_SetEnvColor(D_800734B8[0].r, D_800734B8[0].g, D_800734B8[0].b, D_800734B8[0].a);
                    Font_Printf(x, y, D_8910E150);
                    Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
                    Font_Printf(x, y + 28, func_80031BC0(**((u8***)window->list.items->rows)[window->list.cursor], buf));
                    break;
                case 3:
                    Gfx_SetEnvColor(D_800734B8[0].r, D_800734B8[0].g, D_800734B8[0].b, D_800734B8[0].a);
                    Font_Printf(x, y, D_8910E16C);
                    Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
                    Font_Printf(x, y + 28, func_80031BC0(**((u8***)window->list.items->rows)[window->list.cursor], buf));
                    break;
            }
            Font_EndTexturedTextRendering();
            switch (window->mode) {
                case 1:
                    LabPCList_DrawPopupMenu(&window->confirmPopup, 2);
                    break;
                case 2:
                case 3:
                    LabMoveSelect_Draw(&window->moveSelect);
                    break;
                case 4:
                    LabMoveSelect_DrawLearnAnimation(&window->moveSelect);
                    break;
            }
        }
    }
}

extern u8 D_8910AAE8[];
extern Rgba891084B4 D_8910AAEC;
s32 ScrollList_UpdateCursor(s8 *);
s32 func_80020974(s32);
/**
 * Handles the item window. Returns 1 for a vitamin, 2 for PP Up, 3 for a TM or HM.
 * Seen in play (2026-11-14) in いちらん: ran マックスアップ (HP 21 -> 21), ポイントアップ (たいあたりのPP 35 -> 42) and わざマシン06 on フシギダネ (learned in slot 3) and on ゼニガメ (たいあたり forgotten).
 */
s32 LabPCList_UpdateItemWindow(s8 *window)
{
  s32 ret = 0;
  s8 *self = window;
  u8 **entry;
  s32 n;
  s32 species;
  unsigned int i;
  switch (*((u32 *) (((s8 *) self) + 0x1B0))) // FAKE: decomp slop, raw pointer casts stand in for struct fields
  {
    case 0:
      if (ScrollList_UpdateCursor(self + 0x4C) == 0)
    {
      if (((u16 *) D_800603C0)[4] & 0x4000)
      {
        Audio_PlaySystemSound(3);
        ret = -1;
      }
      else
        if (((u16 *) D_800603C0)[4] & 0x8000)
      {
        if (!((*((u16 **) (((s8 *) self) + 0x50)))[*((s32 *) (((s8 *) self) + 0x54))] & 1)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
        {
          Audio_PlaySystemSound(2);
          LabPCList_InitPopupMenu((LabPopupMenu *) (self + 0x94), (s32 *) D_8910AAE8, (s32) (self + 0x90), 1, 0);
          Window_SetRect(self + 0xC0, (*((s32 *) (((s8 *) self) + 0))) + 6, (((*((s32 *) (((s8 *) self) + 4))) + (*((s32 *) (((s8 *) self) + 0x80)))) - (*((s32 *) (((s8 *) self) + 0x78)))) + 0x16, (*((s32 *) (((s8 *) self) + 8))) - 0xC, 28); // FAKE: decomp slop, raw pointer casts stand in for struct fields
          *((s32 *) (((s8 *) self) + 0x108)) = ((*((s32 *) (((s8 *) self) + 8))) + (*((s32 *) (((s8 *) self) + 0)))) - 6; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          *((s32 *) (((s8 *) self) + 0x10C)) = (*((s32 *) (((s8 *) self) + 4))) + 0xF6; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          LabPCList_PlacePopup((LabPopupMenu *) (self + 0x94));
          *((Rgba891084B4 *) (((s8 *) self) + 0xAC)) = D_8910AAEC; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          *((u32 *) (((s8 *) self) + 0x1B0)) = 1; // FAKE: decomp slop, raw pointer casts stand in for struct fields
        }
        else
        {
          Audio_PlaySystemSound(8);
        }
      }
    }
      break;

    case 1:
      if (LabPCList_UpdatePopupMenu((LabPopupMenu *) (self + 0x94)) == 0)
    {
      if (((u16 *) D_800603C0)[4] & 0x4000)
      {
        Audio_PlaySystemSound(3);
        *((u32 *) (((s8 *) self) + 0x1B0)) = 0; // FAKE: decomp slop, raw pointer casts stand in for struct fields
      }
      else
        if (((u16 *) D_800603C0)[4] & 0x8000)
      {
        if ((*((s32 *) (((s8 *) self) + 0xDC))) == 0) // FAKE: decomp slop, raw pointer casts stand in for struct fields
        {
          entry = (*(*((u8 *****) (((s8 *) self) + 0x4C))))[*((s32 *) (((s8 *) self) + 0x54))]; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          if ((*((s32 *) (((s8 *) entry) + 8))) >= 100) // FAKE: decomp slop, raw pointer casts stand in for struct fields
          {
            n = BattleMon_CountMoves((*((u8 **) (((s8 *) self) + 0x1AC))) + 8); // FAKE: decomp slop, raw pointer casts stand in for struct fields
            Audio_PlaySystemSound(2);
            if (n < 4)
            {
              *((u32 *) (((s8 *) self) + 0x1B0)) = 4; // FAKE: decomp slop, raw pointer casts stand in for struct fields
              if ((*entry[0]) >= 201)
              {
                species = (*entry[0]) - 201;
              }
              else
              {
                species = (*entry[0]) - 146;
              }
              LabMoveSelect_Init(self + 0x110, (*((s32 *) (((s8 *) self) + 0))) + 0xD5, (*((s32 *) (((s8 *) self) + 4))) + 0x81, (*((u8 **) (((s8 *) self) + 0x1AC))) + 8); // FAKE: decomp slop, raw pointer casts stand in for struct fields
              *((s32 *) (((s8 *) self) + 0x144)) = n; // FAKE: decomp slop, raw pointer casts stand in for struct fields
              LabMoveSelect_StartLearnAnimation(self + 0x110, *((s32 *) (((s8 *) self) + 0x144)), func_80020974(species)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
            }
            else
            {
              LabMoveSelect_Init(self + 0x110, (*((s32 *) (((s8 *) self) + 0))) + 0xD5, (*((s32 *) (((s8 *) self) + 4))) + 0x81, (*((u8 **) (((s8 *) self) + 0x1AC))) + 8); // FAKE: decomp slop, raw pointer casts stand in for struct fields
              LabMoveSelect_DisableHmMoves((LabMoveSelectWindow*)(self + 0x110));
              *((u32 *) (((s8 *) self) + 0x1B0)) = 3; // FAKE: decomp slop, raw pointer casts stand in for struct fields
            }
          }
          else
            if ((*((s32 *) (((s8 *) entry) + 8))) >= 50) // FAKE: decomp slop, raw pointer casts stand in for struct fields
          {
            Audio_PlaySystemSound(2);
            LabMoveSelect_Init(self + 0x110, (*((s32 *) (((s8 *) self) + 0))) + 0xD5, (*((s32 *) (((s8 *) self) + 4))) + 0x81, (*((u8 **) (((s8 *) self) + 0x1AC))) + 8); // FAKE: decomp slop, raw pointer casts stand in for struct fields
            for (i = 0; i < 4; i++)
            {
              if ((((*((s32 *) (((s8 *) self) + (0x170 + (i * 4))))) == (-1)) || ((*((s32 *) (((s8 *) self) + (0x170 + (i * 4))))) == (-2))) || ((*((u8 **) (((s8 *) self) + 0x1AC)))[0x28 + i] >= 0xC0)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
              {
                (*((u16 **) (((s8 *) self) + 0x140)))[i] |= 1; // FAKE: decomp slop, raw pointer casts stand in for struct fields
              }
            }

            *((u32 *) (((s8 *) self) + 0x1B0)) = 2; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          }
          else
          {
            Audio_PlaySystemSound(34);
            *((u32 *) (((s8 *) self) + 0x1B0)) = 0; // FAKE: decomp slop, raw pointer casts stand in for struct fields
            ret = 1;
          }
        }
        else
        {
          Audio_PlaySystemSound(3);
          *((u32 *) (((s8 *) self) + 0x1B0)) = 0; // FAKE: decomp slop, raw pointer casts stand in for struct fields
        }
      }
    }
      break;

    case 2:
      if (LabMoveSelect_Update((s32) (self + 0x110)) == 0)
    {
      if (((u16 *) D_800603C0)[4] & 0x4000)
      {
        Audio_PlaySystemSound(3);
        *((u32 *) (((s8 *) self) + 0x1B0)) = 0; // FAKE: decomp slop, raw pointer casts stand in for struct fields
      }
      else
        if (((u16 *) D_800603C0)[4] & 0x8000)
      {
        if (!((*((u16 **) (((s8 *) self) + 0x140)))[*((s32 *) (((s8 *) self) + 0x144))] & 1)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
        {
          Audio_PlaySystemSound(34);
          *((u32 *) (((s8 *) self) + 0x1B0)) = 0; // FAKE: decomp slop, raw pointer casts stand in for struct fields
          ret = 2;
        }
        else
        {
          Audio_PlaySystemSound(8);
        }
      }
    }
      break;

    case 3:
      if (LabMoveSelect_Update((s32) (self + 0x110)) == 0)
    {
      if (((u16 *) D_800603C0)[4] & 0x4000)
      {
        Audio_PlaySystemSound(3);
        *((u32 *) (((s8 *) self) + 0x1B0)) = 0; // FAKE: decomp slop, raw pointer casts stand in for struct fields
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
          Audio_PlaySystemSound(2);
          LabMoveSelect_StartLearnAnimation(self + 0x110, *((s32 *) (((s8 *) self) + 0x144)), func_80020974(sp38)); // FAKE: decomp slop, raw pointer casts stand in for struct fields
          *((u32 *) (((s8 *) self) + 0x1B0)) = 4; // FAKE: decomp slop, raw pointer casts stand in for struct fields
        }
        else
        {
          Audio_PlaySystemSound(8);
        }
      }
    }
      break;

    case 4:
      if (((*((s32 *) (((s8 *) self) + 0x188))) == 0) && (((u16 *) D_800603C0)[4] & 0xC000)) // FAKE: decomp slop, raw pointer casts stand in for struct fields
    {
      Audio_PlaySystemSound(3);
      *((u32 *) (((s8 *) self) + 0x1B0)) = 0; // FAKE: decomp slop, raw pointer casts stand in for struct fields
      ret = 3;
    }
      break;

  }

  return ret;
}

/**
 * Does nothing.
 * No callers: no jal, j, address word or lui/addiu pair in any built fragment or the resident code reaches it (2026-11-14 scan), so it never runs.
 * @unverified Name guessed from the code.
 */
void LabPCList_UnusedStub2(void) {
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
void LabPCList_InitMessageWindow(LabMessageWindow* window, s32 x, s32 y, LabItemResult* message) {
    Window_SetRect(&window->window, x, y, 276, 96);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 6;
    *(Rgba89108F14*)&window->window.frame.color = *(Rgba89108F14*)D_8910AAF4;
    *(Rgba89108F14*)&window->window.frame.color2 = *(Rgba89108F14*)D_8910AAF8;
    window->message = message;
}

extern u8 D_8910D2F0[];
extern char D_8910E1AC[];
extern char D_8910E1B0[];

/**
 * Draws the result message window.
 * Seen in play (2026-11-12) in いちらん: drew the item result window every frame while it was open.
 */
void LabPCList_DrawMessageWindow(LabMessageWindow* window) {
    LabItemResult* entry;

    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFFFF
        Font_SetActive(0x10, 0);
        Font_EnableTwoCycleTexturing();
        Gfx_SetPrimColor(0xFF, 0xAC, 0xAC, 0xFF); // #FFACACFF
        Font_Printf(window->window.frame.x + 18, window->window.frame.y + 18, window->message->title);
        Font_DisableTwoCycleTexturing();
        Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
        entry = window->message;
        if (entry->kind == 0) {
            Font_Printf(window->window.frame.x + 18, window->window.frame.y + 54, D_8910E1AC, entry->left);
            Font_Printf(window->window.frame.x + 162, window->window.frame.y + 54, D_8910E1B0, window->message->right);
        } else if (entry->kind == 1) {
            Font_Printf(window->window.frame.x + 18, window->window.frame.y + 54, entry->left);
            Font_Printf(window->window.frame.x + 162, window->window.frame.y + 54, window->message->right);
        }
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(window->window.frame.x + 122, window->window.frame.y + 54, 0x20, 24, D_8910D2F0, 0x20, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }
}

M2C_UNK Audio_PlaySystemSound(M2C_UNK);                     /* extern */

/**
 * Returns 1 once the message has been confirmed.
 * Seen in play (2026-11-12) in いちらん: returned 0 while the item result window was up and 1 after
 * A.
 */
s32 LabPCList_UpdateMessageWindow(LabMessageWindow* window) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(D_800603C0, u16 *, 8) & 0xC000) {
        Audio_PlaySystemSound(3);
        var_v1 = 1;
    }
    return var_v1;
}
