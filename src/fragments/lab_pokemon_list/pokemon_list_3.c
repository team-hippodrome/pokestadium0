/* Stadium Zero fragment016_252E10. */

#include "global.h"
#include "lab_pokemon_list.h"
#include "m2c_macros.h"

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

M2C_UNK LabPCList_InitDeckCategories(s32, s32, s32, s32);

extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void LabPCList_InitSourceBoxes(void*, void*, void*, s32);

extern s32 D_800603C0;
void func_8000B2F4(s32);

void Window_SetRect(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void LabPCList_LoadAllBoxes(s8*);
void func_80027D68(s32, s32);
void ScrollList_Init(s8*, s8*, s8*, s32, void*, s32, s32);
void LabPCList_DrawMonRow();
extern s32 D_8910D990[];
extern Color_RGBA8 D_8910A7F4;
extern u8 D_8910A844[];
extern u8 D_8910A848[];
extern u8 D_8910A804[];
extern u8 D_8910A84C[];

void LabPCList_SaveDirtyItemDecks(s32 screen);
void LabPCList_ResetHeaderCursor(LabPCListScreen* screen);
s32 LabPCList_GetColumnCursorX(LabPCListScreen* screen);
extern u8 D_800734A8[];

extern Gfx D_80060270[];
extern Color_RGBA8 D_8910A85C[2][2];
extern Color_RGBA8 D_8910A860;
extern Color_RGBA8 D_8910A86C[2][2];
extern SpeciesInfo D_80064C5C[];
extern char D_8910DBCC[];
extern char D_8910DBD8[];
extern char D_8910DBDC[];
extern char D_8910DBE0[];
extern char D_8910DBE4[];
extern char D_8910DBE8[];
extern char D_8910DBEC[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawNumberZeroPadded(s32, s32, s32, s32);
void Font_SetColorForFlags(s32);
void LabPCList_DrawPlainText(s32, s32, s8*, s32, s32);

/**
 * Draws one Pokemon row of the list with the columns of the current detail page.
 * Seen in play (2026-11-12): the rows 0001 フシギダネ ハナ 12345 サトシ てもち くさ どく, 0002 ヒトカゲ, 0003 ゼニガメ.
 */
void LabPCList_DrawMonRow(s32 x, s32 y, Entry891012A8 *entry, s32 row, s32 flags, LabPCListScreen *ctx)
{
  s32 col;
  s32 cx;
  Color_RGBA8 *colors;
  Color_RGBA8 *loop_colors;
  LabPCListScreen *c = ctx;
  gSPDisplayList(gDisplayListHead++, D_80060270);
  colors = D_8910A85C[row & 1];
  loop_colors = D_8910A86C[row & 1];
  func_80029028(x, y, 0x26, 0x14, colors[0]);
  func_80029028(x + 0x26, y, 0x50, 0x14, colors[1]);
  col = c->pageColumnStart[c->page];
  cx = x + 0x78;
  for (; cx < c->listFrame.width; col++)
  {
    func_80029028(cx, y, c->columnWidths[col], 0x14, loop_colors[col & 1]);
    cx += c->columnWidths[col];
  }

  if (entry != 0)
  {
    if (flags & 0x10)
    {
      Ui_FillRectHighlighted(x + 0x27, y + 1, 0x4E, 0x12, D_8910A860);
    }
    Ui_DrawNumberZeroPadded(x + 1, y + 4, row + 1, 4);
    if ((entry->species <= 0) || (entry->species >= 0x98))
    {
      func_8001AB6C();
      Font_SetColorForFlags(flags);
      func_8001A384(4, -1);
      Font_Printf(x + 0x28, y + 2, (M2C_UNK *) D_8910DBCC);
      func_8001ABBC();
    }
    else
    {
      func_8001AB6C();
      if (1 & D_80064C5C[entry->species - 1].cupEligibilityFlags)
      {
        func_8001AA9C(0xFF, 0xC8, 0xA0, 0xFF);
      }
      else
      {
        Font_SetColorForFlags(flags);
      }
      func_8001A384(4, -1);
      Font_Printf(x + 0x28, y + 2, (M2C_UNK *) D_80064C5C[entry->species - 1].name);
      func_8001ABBC();
    }
    cx = x + 0x78;
    for (col = c->pageColumnStart[c->page]; cx < c->listFrame.width; col++)
    {
      switch (col)
      {
        case 0:
          LabPCList_DrawPlainText(cx + 6, y + 2, entry->nickname, 0, 0);
          break;

        case 1:
          Ui_DrawNumberZeroPadded(cx + 4, y + 4, entry->level, 5);
          break;

        case 2:
          LabPCList_DrawPlainText(cx + 4, y + 2, entry->trainer, 0, 0);
          break;

        case 3:
          LabPCList_DrawLocation(cx + 4, y + 2, (s8 ***) entry);
          break;

        case 4:

        case 5:
          LabPCList_DrawTypeIcon(cx + 4, y + 2, &entry->species, col - 4);
          break;

        case 6:

        case 7:

        case 8:

        case 9:
          LabPCList_DrawMoveName(cx + 1, y + 2, (s32) (&entry->species), col - 6);
          break;

        case 10:
          LabPCList_DrawPlainText(cx + 0xC, y + 2, D_8910DBD8, entry->unk2C, 0);
          break;

        case 11:
          LabPCList_DrawPlainText(cx + 0xC, y + 2, D_8910DBDC, entry->stats[0], 0);
          break;

        case 12:
          LabPCList_DrawPlainText(cx + 0xC, y + 2, D_8910DBE0, entry->stats[1], 0);
          break;

        case 13:
          LabPCList_DrawPlainText(cx + 0xC, y + 2, D_8910DBE4, entry->stats[2], 0);
          break;

        case 14:
          LabPCList_DrawPlainText(cx + 0xC, y + 2, D_8910DBE8, entry->stats[3], 0);
          break;

        case 15:
          LabPCList_DrawPlainText(cx + 0xC, y + 2, D_8910DBEC, entry->stats[4], 0);
          break;

      }

      cx += c->columnWidths[col];
    }

  }
}

/**
 * Fields of the scrolling list menu used by LabPCList_DrawRowCursor (same layout as GridMenu80031004
 * in src/2E480.c; offsets not listed are unknown/unused here).
 */
typedef struct ListMenu8910179C {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ s32 cellHeight;
    /* 0x14 */ char unk14[0x16];
    /* 0x2A */ u16 flags;
    /* 0x2C */ s32 scroll;
    /* 0x30 */ char unk30[0x4];
    /* 0x34 */ s32 scrollTarget;
} ListMenu8910179C;

/**
 * Draws a fixed-size (0x50 x 0x14) cursor rectangle via Ui_DrawRoundedFrame for a scrolling list
 * menu: x = left + 0x26, y = scrollTarget + top - scroll, minus (cellHeight - 1) when flag
 * 0x400 is set; color read from D_80073520. Compare ScrollGrid_DrawCursor and ScrollList_DrawCursor.
 * Seen in play (2026-11-12) in いちらん (party list: フシギダネ, ヒトカゲ, ゼニガメ): drew the cursor on the フシギダネ
 * row.
 */
void LabPCList_DrawRowCursor(ListMenu8910179C* list, s32 left, s32 top) {
    s32 y;

    y = list->scrollTarget + top - list->scroll;
    if (list->flags & 0x400) {
        y = y - list->cellHeight + 1;
    }
    Ui_DrawRoundedFrame(left + 0x26, y, 0x50, 0x14, *(Color_RGBA8*)D_80073520);
}

extern u8 D_04006170[];
extern u8 D_04006CE0[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];

extern u8 D_8910C370[];
extern u8 D_8910C978[];
extern char D_8910DBF0[];
extern char D_8910DC04[];
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);

/**
 * Draws タテ／ヨコきりかえ (switch vertical/horizontal) and ページおくり%d/3 (page %d/3).
 * Seen in play (2026-11-12): Lタテ／ヨコきりかえR and ページおくり1／3.
 */
void LabPCList_DrawPageHint(LabPCListScreen* screen) {
    func_8001AB6C();
    func_8001AA9C(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
    func_8001A384(8, 0);
    Font_Printf(screen->headerFrame.x + 0x22, screen->headerFrame.y + 5, (M2C_UNK*)D_8910DBF0);
    Font_Printf(screen->headerFrame.x + 0x152, screen->headerFrame.y + 5, (M2C_UNK*)D_8910DC04,
                  screen->page + 1);
    func_8001ABBC();
    gSPDisplayList(gDisplayListHead++, D_80060290);
    Gfx_DrawTextureRgba16(screen->headerFrame.x + 4, screen->headerFrame.y + 3, 0x1A, 0x18, D_8910C370, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(screen->headerFrame.x + 0xDA, screen->headerFrame.y + 3, 0x1A, 0x18, D_8910C978, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(screen->headerFrame.x + 0x134, screen->headerFrame.y + 2, 0x1A, 0x1A, D_04006170, 0x1C, 0x200000);
    Gfx_DrawTextureRgba16(screen->headerFrame.x + 0x20A, screen->headerFrame.y + 2, 0x1A, 0x1A, D_04006CE0, 0x1C, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

