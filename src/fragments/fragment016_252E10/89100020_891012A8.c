/* Stadium Zero fragment016_252E10. */

#include "global.h"
#include "game_state.h"
#include "jpeg_stream.h"
#include "memory.h"
#include "stage_loader.h"
#include "m2c_macros.h"

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);

M2C_UNK func_89109E5C(s32, s32, s32, s32);
M2C_UNK func_89109FE0(s32);
M2C_UNK func_8910A03C(s32);
typedef struct Entry89100140 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk_10[0x10];
    /* 0x20 */ s32 unk_20;
} Entry89100140; // size = 0x24

typedef struct Ctx89100140 {
    /* 0x000 */ char unk000[0x3B4];
    /* 0x3B4 */ Entry89100140 unk_3B4[3];
    /* 0x420 */ char unk_420[1];
} Ctx89100140;
extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void func_89109990(void*, void*, void*, s32);
typedef struct Ctx89100294 {
    /* 0x0000 */ char unk0000[0x8C];
    /* 0x008C */ s32 unk8C;
    /* 0x0090 */ char unk0090[0xB15C - 0x90];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
    /* 0xB54C */ s32 unkB54C;
    /* 0xB550 */ s32 unkB550;
    /* 0xB554 */ s32 unkB554;
} Ctx89100294;
extern s32 D_800603C0;
void func_8000B2F4(s32);
typedef struct LabPCInitialStateFields {
    u8 pad0000[0x9828];
    u8 unk_9828;
    u8 unk_9829;
    u8 pad982A[2];
    s32 unk_982C;
    u8 pad9830[0xE8];
    s32 unk_9918;
    u8 pad991C[0x1E8];
    s32 unk_9B04;
} LabPCInitialStateFields;
typedef struct Rgba891024A4 { u8 r, g, b, a; } Rgba891024A4;
void Window_SetRect(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_89109B60(s8*);
M2C_UNK func_89109C6C(s32, s32);                    /* extern */
void func_80027D68(s32, s32);
void ScrollList_Init(s8*, s8*, s8*, s32, void*, s32, s32);
void func_891012A8();
void func_89105C54(s8*, s32, s32, s8*, Rgba891024A4);
extern s32 D_8910D990[];
extern Rgba891024A4 D_8910A7F4;
extern u8 D_8910A844[];
extern u8 D_8910A848[];
extern u8 D_8910A804[];
extern u8 D_8910A84C[];
typedef struct Big891003A4 {
    /* 0x0000 */ char unk0000[0xB15C];
    /* 0xB15C */ s32 unkB15C;
    /* 0xB160 */ char unkB160[0x20];
    /* 0xB180 */ s32 unkB180;
    /* 0xB184 */ char unkB184[0x3C4];
    /* 0xB548 */ u8* unkB548;
    /* 0xB54C */ char unkB54C[0xC];
    /* 0xB558 */ s32 unkB558;
    /* 0xB55C */ char unkB55C[0x38];
    /* 0xB594 */ s32 unkB594;
} Big891003A4;
typedef struct Ctx89100688 {
    /* 0x0000 */ char unk0000[0x2C];
    /* 0x002C */ s32 x;
    /* 0x0030 */ s32 y;
    /* 0x0034 */ char unk0034[0x84 - 0x34];
    /* 0x0084 */ s32* widths;
    /* 0x0088 */ char unk0088[0xB15C - 0x88];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
    /* 0xB54C */ s32 unkB54C;
    /* 0xB550 */ s32 cursor;
} Ctx89100688;
void func_891000BC(s32 arg0);
void func_89100294(Ctx89100294* arg0);
s32 func_891005CC(Ctx89100688* arg0);
extern M2C_UNK D_800734A8;


#include "fragments/fragment016_252E10/89100020_891012A8_types.h"


extern Gfx D_80060270[];
extern Color_RGBA8 D_8910A85C[2][2];
extern Color_RGBA8 D_8910A860;
extern Color_RGBA8 D_8910A86C[2][2];
extern unk_D_8006FF00 D_80064C5C[];
extern char D_8910DBCC[];
extern char D_8910DBD8[];
extern char D_8910DBDC[];
extern char D_8910DBE0[];
extern char D_8910DBE4[];
extern char D_8910DBE8[];
extern char D_8910DBEC[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void func_8002BAB8(s32, s32, s32, s32);
void Font_SetColorForFlags(s32);
void func_89101238(s32, s32, s8*, s32, s32);

void func_891012A8(s32 x, s32 y, Entry891012A8 *entry, s32 row, s32 flags, Ctx891012A8 *ctx)
{
  s32 col;
  s32 cx;
  Color_RGBA8 *colors;
  Color_RGBA8 *loop_colors;
  Ctx891012A8 *c = ctx;
  gSPDisplayList(gDisplayListHead++, D_80060270);
  colors = D_8910A85C[row & 1];
  loop_colors = D_8910A86C[row & 1];
  func_80029028(x, y, 0x26, 0x14, colors[0]);
  func_80029028(x + 0x26, y, 0x50, 0x14, colors[1]);
  col = c->ranges[c->mode];
  cx = x + 0x78;
  for (; cx < c->right; col++)
  {
    func_80029028(cx, y, c->widths[col], 0x14, loop_colors[col & 1]);
    cx += c->widths[col];
  }

  if (entry != 0)
  {
    if (flags & 0x10)
    {
      Ui_FillRectHighlighted(x + 0x27, y + 1, 0x4E, 0x12, D_8910A860);
    }
    func_8002BAB8(x + 1, y + 4, row + 1, 4);
    if ((entry->species <= 0) || (entry->species >= 0x98))
    {
      func_8001AB6C();
      Font_SetColorForFlags(flags);
      func_8001A384(4, -1);
      func_8001A944(x + 0x28, y + 2, (M2C_UNK *) D_8910DBCC);
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
      func_8001A944(x + 0x28, y + 2, (M2C_UNK *) D_80064C5C[entry->species - 1].name);
      func_8001ABBC();
    }
    cx = x + 0x78;
    for (col = c->ranges[c->mode]; cx < c->right; col++)
    {
      switch (col)
      {
        case 0:
          func_89101238(cx + 6, y + 2, entry->nickname, 0, 0);
          break;

        case 1:
          func_8002BAB8(cx + 4, y + 4, entry->level, 5);
          break;

        case 2:
          func_89101238(cx + 4, y + 2, entry->trainer, 0, 0);
          break;

        case 3:
          LabPCList_DrawLocationTabs(cx + 4, y + 2, (s8 ***) entry);
          break;

        case 4:

        case 5:
          func_89100F1C(cx + 4, y + 2, &entry->species, col - 4);
          break;

        case 6:

        case 7:

        case 8:

        case 9:
          func_89100FC4(cx + 1, y + 2, (s32) (&entry->species), col - 6);
          break;

        case 10:
          func_89101238(cx + 0xC, y + 2, D_8910DBD8, entry->unk2C, 0);
          break;

        case 11:
          func_89101238(cx + 0xC, y + 2, D_8910DBDC, entry->stats[0], 0);
          break;

        case 12:
          func_89101238(cx + 0xC, y + 2, D_8910DBE0, entry->stats[1], 0);
          break;

        case 13:
          func_89101238(cx + 0xC, y + 2, D_8910DBE4, entry->stats[2], 0);
          break;

        case 14:
          func_89101238(cx + 0xC, y + 2, D_8910DBE8, entry->stats[3], 0);
          break;

        case 15:
          func_89101238(cx + 0xC, y + 2, D_8910DBEC, entry->stats[4], 0);
          break;

      }

      cx += c->widths[col];
    }

  }
}

/**
 * Fields of the scrolling list menu used by func_8910179C (same layout as GridMenu80031004
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
 * menu: x = arg1 + 0x26, y = scrollTarget + arg2 - scroll, minus (cellHeight - 1) when flag
 * 0x400 is set; colour read from D_80073520. Compare func_80031004 and func_8002F32C.
 */
void func_8910179C(ListMenu8910179C* arg0, s32 arg1, s32 arg2) {
    s32 y;

    y = arg0->scrollTarget + arg2 - arg0->scroll;
    if (arg0->flags & 0x400) {
        y = y - arg0->cellHeight + 1;
    }
    Ui_DrawRoundedFrame(arg1 + 0x26, y, 0x50, 0x14, *(Color_RGBA8*)D_80073520);
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
 * @unverified Name and comment guessed from the code.
 */
void LabPCList_DrawPageHint(s8* arg0) {
    func_8001AB6C();
    func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
    func_8001A384(8, 0);
    func_8001A944(M2C_FIELD(arg0, s32*, 0x4C) + 0x22, M2C_FIELD(arg0, s32*, 0x50) + 5, (M2C_UNK*)D_8910DBF0);
    func_8001A944(M2C_FIELD(arg0, s32*, 0x4C) + 0x152, M2C_FIELD(arg0, s32*, 0x50) + 5, (M2C_UNK*)D_8910DC04,
                  M2C_FIELD(arg0, s32*, 0xB15C) + 1);
    func_8001ABBC();
    gSPDisplayList(gDisplayListHead++, D_80060290);
    Gfx_DrawTextureRgba16(M2C_FIELD(arg0, s32*, 0x4C) + 4, M2C_FIELD(arg0, s32*, 0x50) + 3, 0x1A, 0x18, D_8910C370, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(M2C_FIELD(arg0, s32*, 0x4C) + 0xDA, M2C_FIELD(arg0, s32*, 0x50) + 3, 0x1A, 0x18, D_8910C978, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(M2C_FIELD(arg0, s32*, 0x4C) + 0x134, M2C_FIELD(arg0, s32*, 0x50) + 2, 0x1A, 0x1A, D_04006170, 0x1C, 0x200000);
    Gfx_DrawTextureRgba16(M2C_FIELD(arg0, s32*, 0x4C) + 0x20A, M2C_FIELD(arg0, s32*, 0x50) + 2, 0x1A, 0x1A, D_04006CE0, 0x1C, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

