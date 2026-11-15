/* Stadium Zero fragment016_252E10. */

#include "global.h"
#include "lab_pokemon_list.h"
#include "m2c_macros.h"

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

extern u8 D_8910A85C[];
extern u8 D_8910A860[];
extern Gfx D_80060270[];
extern Gfx D_80073450[];
extern u8 D_8910AB08[];
extern u8 D_800734A8[];
extern char D_8910DAF8[];
extern char D_8910DB04[];
extern char D_8910DB14[];
extern char D_8910DB18[];
extern char D_8910DB20[];
extern char D_8910DB28[];
extern char D_8910DB34[];
extern char D_8910DB40[];
extern char D_8910DB4C[];
extern char D_8910DB58[];
extern char D_8910DB64[];
extern char D_8910DB70[];
extern char D_8910DB78[];
extern char D_8910DB7C[];
extern char D_8910DB88[];
extern char D_8910DB94[];
extern char D_8910DBA0[];
s32 LabPCList_GetColumnCursorX(LabPCListScreen* screen);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);
void Gfx_DrawTextureIa8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Font_BeginTranslucentTextRendering(void);
void Font_EndTexturedTextRendering(void);
void Gfx_SetEnvColor(s32 r, s32 g, s32 b, s32 a);
void Font_SetActive(s32 mask, s32 arg1);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
/**
 * Draws the list column headers: Pokemon, nickname, ID, OT, location, Type 1/2, level, HP, Attack...
 * Seen in play (2026-11-12): the headers ポケモン, ニックネーム, ID, おや, ばしょ, タイプ1, タイプ2.
 */
void LabPCList_DrawDetailColumns(LabPCListScreen* screen, s32 left, s32 top, s32 flags) {
    s32 x;
    s32 i;
    s32 hl;

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(left, screen->listFrame.y, 38, 20, *(Color_RGBA8*)D_8910A85C);
    func_80029028(left + 38, screen->listFrame.y, 80, 20, *(Color_RGBA8*)D_8910A860);
    i = screen->pageColumnStart[screen->page];
    for (x = left + 120; x < screen->listFrame.width; i++) {
        func_80029028(x, top, screen->columnWidths[i], 20, *(Color_RGBA8*)&D_8910A85C[(i & 1) * 4]);
        x += screen->columnWidths[i];
    }
    if (flags & 0x10) {
        Ui_FillRectHighlighted(LabPCList_GetColumnCursorX(screen) + 1, top + 1, screen->columnWidths[screen->pageColumnStart[screen->page] + screen->headerCursor.cursor - 2] - 2, 18, *(Color_RGBA8*)D_8910A860);
    }
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    Gfx_DrawTextureIa8(left + 4, top + 1, 30, 18, D_8910AB08, 0x20, 0);
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    Font_SetActive(4, 0);
    Font_Printf(left + 46, top + 2, D_8910DAF8);
    Font_EndTexturedTextRendering();
    Font_BeginTranslucentTextRendering();
    for (x = left + 120, i = screen->pageColumnStart[screen->page]; x < screen->listFrame.width; i++) {
        hl = (i + 2 == screen->pageColumnStart[screen->page] + screen->headerCursor.cursor) ? 0x12 : 0;
        Font_SetColorForFlags(hl & flags);
        switch (i) {
            case 0:
                Font_SetActive(4, -1);
                Font_Printf(x + 1, top + 2, D_8910DB04);
                break;
            case 1:
                Font_SetActive(4, 0);
                Font_Printf(x + 10, top + 2, D_8910DB14);
                break;
            case 2:
                Font_SetActive(4, 0xC);
                Font_Printf(x + 22, top + 2, D_8910DB18);
                break;
            case 3:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, top + 2, D_8910DB20);
                break;
            case 4:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, top + 2, D_8910DB28);
                break;
            case 5:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, top + 2, D_8910DB34);
                break;
            case 6:
                Font_SetActive(4, 0);
                Font_Printf(x + 22, top + 2, D_8910DB40);
                break;
            case 7:
                Font_SetActive(4, 0);
                Font_Printf(x + 22, top + 2, D_8910DB4C);
                break;
            case 8:
                Font_SetActive(4, 0);
                Font_Printf(x + 22, top + 2, D_8910DB58);
                break;
            case 9:
                Font_SetActive(4, 0);
                Font_Printf(x + 22, top + 2, D_8910DB64);
                break;
            case 10:
                Font_SetActive(4, 0);
                Font_Printf(x + 12, top + 2, D_8910DB70);
                break;
            case 11:
                Font_SetActive(4, 0xC);
                Font_Printf(x + 14, top + 2, D_8910DB78);
                break;
            case 12:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, top + 2, D_8910DB7C);
                break;
            case 13:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, top + 2, D_8910DB88);
                break;
            case 14:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, top + 2, D_8910DB94);
                break;
            case 15:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, top + 2, D_8910DBA0);
                break;
        }
        x += screen->columnWidths[i];
    }
    Font_EndTexturedTextRendering();
}

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 Pokemon_GetTypeIndex(u8*, s32);
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
M2C_UNK func_8001AB6C();
M2C_UNK func_8001ABBC();

/**
 * Draws the colored type icon for type slot `type_slot` of Pokemon `mon`.
 * Seen in play (2026-11-12): くさ, どく, ほのお and みず in their type colors.
 */
void LabPCList_DrawTypeIcon(s32 x, s32 y, u8* mon, s32 type_slot) {
    Color82000BC4 c;
    s32 idx;

    if ((*mon > 0) && (*mon < 152) && ((idx = Pokemon_GetTypeIndex(mon, type_slot)) != -1)) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(4, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        Font_Printf(x, y, (M2C_UNK*)D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

typedef struct Label89100FC4 {
    Color82000BC4 color;
    const char* str;
} Label89100FC4;
extern Entry89100FC4 D_8006A9D4[];
extern u8 D_800734A8[];
extern char D_8910DBAC[];
s32 BattleMon_GetMoveIndexChecked(s32, s32);
/**
 * Draws move slot `slot` of a Pokémon in its type's color, or the empty-slot dash; nothing for a missing slot.
 * Seen in play (2026-11-14) in いちらん: drew the わざ1-4 columns of page 2/3.
 */
void LabPCList_DrawMoveName(s32 x, s32 y, s32 mon, s32 slot) {
    const char* str;
    Color82000BC4 color;
    s32 idx;

    idx = BattleMon_GetMoveIndexChecked(mon, slot);
    if (idx != -1) {
        if (idx == -2) {
            color = *(Color82000BC4*)&D_800734A8;
            str = D_8910DBAC;
        } else {
            color = D_80066AD8[D_8006A9D4[idx].type].color;
            str = D_8006A9D4[idx].name;
        }
        func_8001AB6C();
        func_8001A384(4, -1);
        func_8001AA9C(color.r, color.g, color.b, color.a);
        Font_Printf(x, y, (M2C_UNK*)str);
        func_8001ABBC();
    }
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void Font_DrawCharAt(s32 x, s32 y, s32 chr);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
extern u8 D_800734A8[];
extern M2C_UNK D_8910DBB4;
extern M2C_UNK D_8910DBBC;
extern M2C_UNK D_8910DBC0;
extern M2C_UNK D_8910DBC4;

/**
 * Draws a row's ばしょ (location) value, picked by the box id: てもち (party), a GB or 64
 * cartridge box number, and so on.
 * Seen in play (2026-11-12): てもち in the ばしょ column for the three party Pokemon.
 */
void LabPCList_DrawLocation(s32 x, s32 y, s8 ***entry) {
    s32 temp_v0;

    func_8001AB6C();
    func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    temp_v0 = M2C_FIELD(**entry, s32 *, 4);
    switch (temp_v0) {                              /* irregular */
    case 32:
        func_8001A384(4, 0);
        Font_Printf(x, y, &D_8910DBB4);
        break;
    case 33:
        func_8001A384(4, -1);
        Font_DrawCharAt(x + 34, y, M2C_FIELD(*entry, s32 *, 4) + 0x31);
        func_8001AA9C(0xFFU, 0xC8U, 0xFFU, 0xFFU); // #FFC8FFFF
        Font_Printf(x - 2, y, &D_8910DBBC);
        break;
    case 17:
        func_8001A384(4, -1);
        Font_DrawCharAt(x + 34, y, M2C_FIELD(*entry, s32 *, 4) + 0x31);
        func_8001AA9C(0x96U, 0xDCU, 0xD2U, 0xFFU); // #96DCD2FF
        Font_Printf(x - 2, y, &D_8910DBC0);
        break;
    case 19:
        func_8001A384(4, 0);
        Font_Printf(x, y, &D_8910DBC4);
        break;
    }
    func_8001ABBC();
}

/** Draws a line of plain text in a Lab PC list. */
void LabPCList_DrawPlainText(s32 x, s32 y, s8* fmt, s32 value, s32 font_flags) {
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    Font_SetActive(4, font_flags);
    Font_Printf(x, y, fmt, value);
    Font_EndTexturedTextRendering();
}
