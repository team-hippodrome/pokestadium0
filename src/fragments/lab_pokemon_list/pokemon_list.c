/* Stadium Zero fragment016_252E10. */

#include "global.h"
#include "lab_pokemon_list.h"
#include "m2c_macros.h"

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

M2C_UNK func_89109E5C(s32, s32, s32, s32);          /* extern */
M2C_UNK func_89109FE0(s32);                         /* extern */
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_89100020(s32 arg0)
{
  s32 var_s0;
  s32 var_s1;
  s8 *var_s2;
  func_89109E5C(arg0 + 0x9E64, arg0 + 0x9EB8, arg0 + 0x9EE0, arg0 + 0x9F44);
  var_s2 = arg0 + 0x8000;
 do { var_s0 = arg0; var_s1 = 0; do { if ((*((s32 *) (((s8 *) var_s2) + 0x1E68))) != 0) { func_89109FE0(var_s0 + 0x9E64); } var_s1 += 0x1C; var_s0 += 0x1C; var_s2 += 0x1C; } while (var_s1 != 0x54); } while (0);  // FAKE
}

M2C_UNK func_8910A03C(s32);                         /* extern */

void func_891000BC(s32 arg0) {
    s32 var_s1;
    s32 var_s2;
    s8 *var_s0;

    var_s0 = arg0 + 0x8000;
    var_s1 = arg0;
    var_s2 = 0;
    do {
        if ((M2C_FIELD(var_s0, s32 *, 0x1E68) != 0) && (M2C_FIELD(var_s0, s32 *, 0x1E6C) != 0)) {
            func_8910A03C(var_s1 + 0x9E64);
        }
        var_s2 += 0x1C;
        var_s1 += 0x1C;
        var_s0 += 0x1C;
    } while (var_s2 != 0x54);
}

extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void func_89109990(void*, void*, void*, s32);

void func_89100140(LabPCListScreen* arg0) {
    s32 i;

    arg0->sources[0].unk_04 = 0x20;
    arg0->sources[0].unk_08 = func_80025BD8();
    arg0->sources[0].unk_0C = 0;
    arg0->sources[0].unk_20 = 6;
    func_80027410(arg0->sources[0].unk_10, (s8*)arg0 + 0x90, 0x20, 1, 0);
    func_89109990(&arg0->sources[0], (s8*)arg0 + 0x8200, (s8*)arg0 + 0x430, 6);
    arg0->sources[1].unk_04 = 0x21;
    arg0->sources[1].unk_08 = arg0->sources[0].unk_08;
    arg0->sources[1].unk_0C = 1;
    arg0->sources[1].unk_20 = 0x1E;
    func_80027410(arg0->sources[1].unk_10, (s8*)arg0 + 0xB0, 0x20, 8, 0);
    func_89109990(&arg0->sources[1], (s8*)arg0 + 0x8218, (s8*)arg0 + 0x640, 0x1E);
    arg0->sources[2].unk_04 = 0x11;
    arg0->sources[2].unk_08 = 0;
    arg0->sources[2].unk_0C = 2;
    arg0->sources[2].unk_20 = 0x1E;
    func_80027410(arg0->sources[2].unk_10, (s8*)arg0 + 0x1B0, 0x20, 4, 0);
    func_89109990(&arg0->sources[2], (s8*)arg0 + 0x85D8, (s8*)arg0 + 0x58C0, 0x1E);
    for (i = 0; i < 3; i++) {
        arg0->sources[i].unk_00 = D_8910A7F8[i];
    }
    func_80027410((s8*)arg0 + 0x420, arg0->sources, 0x24, 3, 3);
}

extern s32 D_800603C0;
void func_8000B2F4(s32);
void func_89100294(LabPCListScreen* arg0) {
    s32 count;

    switch (arg0->page) {
        case 0:
            count = arg0->pageColumnStart[arg0->page + 1] - arg0->pageColumnStart[arg0->page] - 1;
            break;
        case 1:
            count = 1;
            break;
        case 2:
            count = arg0->pageColumnStart[arg0->page + 1] - arg0->pageColumnStart[arg0->page];
            break;
    }
    if (arg0->focus == 2) {
        arg0->headerCursor.cursor = arg0->headerCursor.cursor; // FAKE: self-assignment is required to match (retail reloads and stores the field)
    } else {
        arg0->headerCursor.cursor = 2;
    }
    arg0->headerCursor.count = count + 2;
    arg0->headerCursor.controller = D_800603C0;
    func_8000B2F4(D_800603C0);
}

/**
 * Resets the list filters: level range 1..100, and no type or move filter.
 * Seen in play (2026-11-12) in いちらん: すべてのせんたくをやめる ran this, then LabPCList_ClearFilterFlags, and
 * the full party list came back.
 */
void LabPCList_ResetFilterState(LabPCListScreen* state) {
    /* IDO schedules these byte stores together when they share a source line. */
    state->unk_9828 = 1; state->unk_9829 = 100;
    state->unk_982C = 0;
    state->unk_9918 = 0;
    state->unk_9B04 = 0;
}

void Window_SetRect(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_89109B60(s8*);
M2C_UNK func_89109C6C(s32, s32);                    /* extern */
void func_80027D68(s32, s32);
void ScrollList_Init(s8*, s8*, s8*, s32, void*, s32, s32);
void LabPCList_DrawMonRow();
void func_89105C54(s8*, s32, s32, s8*, Color_RGBA8);
extern s32 D_8910D990[];
extern Color_RGBA8 D_8910A7F4;
extern u8 D_8910A844[];
extern u8 D_8910A848[];
extern u8 D_8910A804[];
extern u8 D_8910A84C[];

/**
 * Sets up the Pokemon list window (564x382) and its widgets.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): ran on entry as the list
 * window appeared.
 */
void LabPCList_InitListWindow(s8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[1]; // FAKE: stack padding

    func_89100140((LabPCListScreen*)arg0);
    Window_SetRect(arg0, arg1, arg2, 0x234, 0x17E);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 1;
    Window_SetRect(arg0 + 0x4C, arg1 + 6, arg2 + 6, 0x228, 0x1E);
    M2C_FIELD(arg0, s32*, 0x60) = 6;
    M2C_FIELD(arg0, Color_RGBA8*, 0x64) = *(Color_RGBA8*)D_8910A844;
    M2C_FIELD(arg0, Color_RGBA8*, 0x68) = *(Color_RGBA8*)D_8910A848;
    Window_SetRect(arg0 + 0x2C, arg1 + 6, arg2 + 0x3A, 0x228, 0x12E);
    M2C_FIELD(arg0, s32*, 0x40) = 1;
    func_80027804(arg0 + 0x9648, arg0 + 0x87B8, 0x1D2, 0);
    func_80027804(arg0 + 0x6C, arg0 + 0x8F00, 0x1D2, 0);
    func_89109B60(arg0 + 0x420);
    M2C_FIELD(arg0, s32*, 0x7C) = 0;
    M2C_FIELD(arg0, u8**, 0x84) = D_8910A804;
    func_89109C6C((s32)(arg0 + 0x9648), (s32)(arg0 + 0x420));
    M2C_FIELD(arg0, s32*, 0x78) = 0;
    func_80027D68((s32)(arg0 + 0x9648), D_8910D990[0]);
    M2C_FIELD(arg0, s32*, 0x8C) = 0;
    func_89100020((s32)arg0);
    M2C_FIELD(arg0, s32*, 0x80) = 0;
    ((LabPCListScreen*)arg0)->page = 0;
    ScrollList_Init(arg0 + 0xB160, arg0 + 0x9648, arg0 + 0xB1A4, 0xE, LabPCList_DrawMonRow, 0x228, 0x14);
    ((LabPCListScreen*)arg0)->list.options &= ~0x100000;
    ((LabPCListScreen*)arg0)->pageColumnStart = D_8910A84C;
    func_89100294((LabPCListScreen*)arg0);
    ((LabPCListScreen*)arg0)->unk_B558 = 0;
    ((LabPCListScreen*)arg0)->msg = arg3;
    LabPCList_ResetFilterState((LabPCListScreen*)arg0);
    M2C_FIELD(arg0, s32*, 0x88) = 1;
    func_89105C54(arg0 + 0x230, 0x78, 0x67, arg0 + 0x420, D_8910A7F4);
}

/**
 * Returns the x position of the header cursor for the current detail page.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 LabPCList_GetColumnCursorX(LabPCListScreen* arg0) {
    s32 i;
    s32 x = 0;
    s32 end;

    for (i = arg0->pageColumnStart[arg0->page], end = arg0->pageColumnStart[arg0->page] + arg0->headerCursor.cursor - 2; i < end; i++) {
        x += arg0->columnWidths[i];
    }
    return arg0->listFrame.x + x + 0x78;
}

void func_89100688(LabPCListScreen* arg0) {
    s32 end;
    s32* r;
    s32 i;
    s32 w;

    switch (arg0->page) {
        case 0:
            end = arg0->pageColumnStart[arg0->page] + arg0->headerCursor.cursor - 2;
            i = end;
            if (i == 4) {
                w = arg0->columnWidths[i] + arg0->columnWidths[i + 1];
            } else {
                w = arg0->columnWidths[i];
            }
            Ui_DrawRoundedFrame(LabPCList_GetColumnCursorX(arg0), arg0->listFrame.y, w, 0x14, *(Color_RGBA8*)D_80073520);
            break;
        case 1:
            w = 0;
            r = &arg0->pageColumnStart[arg0->page];
            i = r[0] + arg0->headerCursor.cursor - 2;
            end = r[1] - r[0] + i;
            for (; i < end; i++) {
                w += arg0->columnWidths[i];
            }
            Ui_DrawRoundedFrame(LabPCList_GetColumnCursorX(arg0), arg0->listFrame.y, w, 0x14, *(Color_RGBA8*)D_80073520);
            break;
        case 2:
            Ui_DrawRoundedFrame(LabPCList_GetColumnCursorX(arg0), arg0->listFrame.y, arg0->columnWidths[arg0->pageColumnStart[arg0->page] + arg0->headerCursor.cursor - 2], 0x14, *(Color_RGBA8*)D_80073520);
            break;
    }
}

/**
 * Draws a highlight rectangle (via Ui_DrawRoundedFrame) for the screen object arg0, positioned from
 * the two words at arg0 + 0x2C / 0x30 (what they mean is not established). The word at
 * arg0 + 0xB550 selects the shape: 0 draws a 0x26 x 0x14 rectangle at the origin, 1 a
 * 0x50 x 0x14 rectangle offset 0x26 to the right; other values draw nothing. The color is
 * read from D_80073520. (Compare LabPCList_DrawRowCursor.)
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void LabPCList_DrawHeaderCursor(s8* arg0) {
    switch (M2C_FIELD(arg0, s32*, 0xB550)) {
        case 0:
            Ui_DrawRoundedFrame(M2C_FIELD(arg0, s32*, 0x2C), M2C_FIELD(arg0, s32*, 0x30), 0x26, 0x14, *(Color_RGBA8*)D_80073520);
            return;
        case 1:
            Ui_DrawRoundedFrame(M2C_FIELD(arg0, s32*, 0x2C) + 0x26, M2C_FIELD(arg0, s32*, 0x30), 0x50, 0x14, *(Color_RGBA8*)D_80073520);
            return;
    }
}
