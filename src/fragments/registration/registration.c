/* Stadium Zero fragment008_1720F0. */

#include "global.h"
#include "m2c_macros.h"
#include "font.h"
#include "graphics_textures.h"
#include "registration.h"

s32 func_800246A8(M2C_UNK, s32);                    /* extern */

/**
 * Returns the first empty slot of the 16 registered team slots, or -1 when all are used.
 * Seen in play (2026-11-12): the first registration went into slot 01 of the empty list.
 */
s32 Registration_FindFreeSlot(void) {
    s32 var_s0;

    var_s0 = 0;
loop_1:
    if (func_800246A8(0x10, var_s0) == 0) {
        return var_s0;
    }
    var_s0 += 1;
    if (var_s0 == 0x10) {
        return -1;
    }
    goto loop_1;
}

s32 func_80020AFC(s32, s32, s32, s32);
s32 func_80020CE4(void*, s32, s32);
M2C_UNK func_80020C60(s32);
/**
 * Reads up to six Pokemon from deck (`arg0`, `arg1`, `arg2`) into team `arg3` and stores the count.
 * Seen in play (2026-11-12): read the cartridge party ハナ L5, ヒノコ L5, カメ L5 into the list.
 */
void Registration_ReadTeam(s32 arg0, s32 arg1, s32 arg2, ByteMatrix* arg3) {
    TeamMonSlot* entry = (TeamMonSlot*)arg3->rows;
    s32 handle = func_80020AFC(arg0, arg1, arg2, 0);
    s32 i;

    for (i = 0; i < 6; i++, entry++) {
        if (func_80020CE4(&entry->mon, 1, handle) == 0) {
            break;
        }
        entry->flags = 0;
    }
    func_80020C60(handle);
    arg3->count = i;
}

s32 func_80020B94(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s8 *, s32); /* extern */
M2C_UNK func_80020C60(s32);                         /* extern */
s32 func_80020DF0(s32, M2C_UNK, s32);               /* extern */
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Writes team `arg0` into registered slot `arg1`.
 * Seen in play (2026-11-12): 「このポケモンをとうろくする？」 > はい stored the party in slot 01.
 */
void Registration_WriteTeam(s8 *arg0, M2C_UNK arg1)
{
  s32 temp_s3;
  s32 var_s0;
  s32 var_s1;
  var_s1 = *((s32 *) (((s8 *) arg0) + 0x18));
  if ((!arg0) && (!arg0))
  {
  }
  temp_s3 = func_80020B94(0x10, 0, arg1, 0, arg0 + 8, *((s32 *) (((s8 *) arg0) + 4)));
  var_s0 = 0;
  if ((*((s32 *) (((s8 *) arg0) + 0x20))) > 0)
  {
    loop_1:
    if (func_80020DF0(var_s1 + 4, 1, temp_s3) != 0)
    {
      var_s0 += 1;
      var_s1 += 0x54;
      if (var_s0 < (*((s32 *) (((s8 *) arg0) + 0x20))))
      {
        goto loop_1;
      }
    }

  }
  func_80020C60(temp_s3);
}

/*
 * Registration_WriteAllTeams
 *
 * Writes each team of the PointerList arg0 to its save slot with Registration_WriteTeam(team, i),
 * then deletes the saved teams in the slots from count up to capacity (func_800245E0(0x10, i)
 * where func_800246A8(0x10, i) says a team is there).
 * The separate `base` local reproduces the ROM's register copy (the array
 * pointer is loaded before the first count is tested).
 */
s32 func_800245E0(M2C_UNK, s32);
/**
 * Writes every listed team back to its slot and clears the registered slots after them.
 * Seen in play (2026-11-12) in とうろく: ran after はい on 「このポケモンをけす？」 (「へんしん していた メタモンが もとの すがたに
 * もどった。」). With no team left, the view and delete entries were then greyed out.
 */
void Registration_WriteAllTeams(PointerList* arg0) {
    s32 i;
    s8 **p;
    s8 **base;

    base = arg0->items;
    i = 0;
    if (arg0->count > 0) {
        p = base;
        do {
            Registration_WriteTeam(*p, i);
            i++;
            p++;
        } while (i < arg0->count);
    }
    for (; i < arg0->capacity; i++) {
        if (func_800246A8(0x10, i) != 0) {
            func_800245E0(0x10, i);
        }
    }
}

s32 func_80024ADC(s32, s32);
void func_80027410(void*, void*, s32, s32, s32);
s32 Deck_GetSaveEntryTrainerId(s32, s32);
s32 Deck_GetSaveEntryName(s32 arg0, s32 arg1, u8* arg2);
/**
 * Reads every used registered slot (deck 0x10) with its trainer id and name.
 * Seen in play (2026-11-12): filled the 01 slot row (Ditto placeholders until the copy finished).
 */
void Registration_LoadRegisteredTeams(ByteMatrix* arg0) {
    RegisteredTeam* p = (RegisteredTeam*)arg0->rows;
    s32 i;

    for (i = 0; i < 0x10; i++) {
        if (func_800246A8(0x10, i) == 0) {
            continue;
        }
        if (func_80024ADC(0x10, i) == 0) {
            continue;
        }
        p->unk_00 = 0;
        p->source = 0x10;
        p->pak = 0;
        p->slot = i;
        func_80027410(&p->mons, p->monBuffer, sizeof(TeamMonSlot), 6, 0);
        Registration_ReadTeam(p->source, p->pak, p->slot, &p->mons);
        p->trainerId = Deck_GetSaveEntryTrainerId(p->source, p->slot);
        Deck_GetSaveEntryName(p->source, p->slot, p->name);
        p++;
    }
    arg0->count = p - (RegisteredTeam*)arg0->rows;
}

s32 func_80021894(s32);
s32 GbSave_GetTrainerId(s32 arg0);
void func_80022D84(s32, u8*);
/**
 * Reads the party of each Game Boy cartridge in the four Transfer Paks (deck 0x20).
 * Seen in play (2026-11-12): ポケモンを とうろくする listed the 1P cartridge's party.
 */
void Registration_LoadGbTeams(ByteMatrix* arg0) {
    RegisteredTeam* p = (RegisteredTeam*)arg0->rows;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_80021894(i) == 0) {
            continue;
        }
        p->unk_00 = 0;
        p->source = 0x20;
        p->pak = i;
        p->slot = 0;
        func_80027410(&p->mons, p->monBuffer, sizeof(TeamMonSlot), 6, 0);
        Registration_ReadTeam(p->source, p->pak, p->slot, &p->mons);
        p->trainerId = GbSave_GetTrainerId(p->pak);
        func_80022D84(p->pak, p->name);
        p++;
    }
    arg0->count = p - (RegisteredTeam*)arg0->rows;
}

extern Color_RGBA8 D_88102D74;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);

/**
 * Draws one menu row label with the selection highlight.
 * Seen in play (2026-11-12): one row of the とうろく menu.
 */
void Registration_DrawMenuRow(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 temp_v0 = *arg5;

    if (arg4 & 0x10) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x1A, D_88102D74);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

void Window_SetRect(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_800226BC(s32, s32, s32);
void func_80027804(void*, void*, s32, s32);
M2C_UNK Menu_Init(void*, void*, void*, M2C_UNK *, s32, s32);
extern s32 D_88103078;

/**
 * Sets up the registration menu: ポケモンをとうろくする (register), とうろくしたポケモンをみる (view), とうろくしたポケモンをけす (delete).
 * Seen in play (2026-11-12): ポケモンを とうろくする / とうろくした ポケモンをみる / とうろくした ポケモンをけす.
 */
void Registration_InitMainMenu(MenuWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, M2C_UNK* arg5, s32 arg6, M2C_UNK* arg7, s32 arg8, M2C_UNK* arg9) {
    s32 sp2C;

    Window_SetRect(arg0, arg1, arg2, arg3, arg4);
    arg0->window.state = 0;
    arg0->window.animTimer = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = (s32)arg9;
    func_80027804(&arg0->itemList, (s8*)arg5, arg6, arg6);
    Menu_Init(&arg0->menu, &arg0->itemList, &arg0->itemFlags, (M2C_UNK*)Registration_DrawMenuRow, arg3 - 0xC, 0x20);
    arg0->menu.options = (s32) (arg0->menu.options | 0x10000);
    arg0->descriptions = (s32)arg7;
    arg0->descriptionLines = arg8;
    sp2C = Registration_FindFreeSlot();
    if ((func_800226BC(0x20, D_88103078, 0) == 0) || (sp2C == -1)) {
        arg0->menu.itemFlags[0] |= 1;
    }
    if (sp2C == 0) {
        arg0->menu.itemFlags[1] |= 1;
        arg0->menu.itemFlags[2] |= 1;
    }
}

s32 func_8002AE6C();
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void func_80029028(s32, s32, s32, s32, Color88100D9C);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color88100D9C, Color88100D9C);
void Menu_DrawItems(void*, s32, s32, s32, s32);
extern u8 D_8007356C[];
extern u8 D_800734A8[4];
extern Gfx D_80060270[];
extern Color88100D9C D_88102D9C;
extern Color88100D9C D_88102DA0;
/**
 * Draws the registration menu and the description of the selected item.
 * Seen in play (2026-11-12): that menu with the description 「GBカートリッジの てもちポケモンの「データ」だけを きろくする。…」.
 */
void Registration_DrawMainMenu(MenuWindow* arg0, s32 arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 sp38;
    s32 h;

    if (func_8002AE6C() == 0) {
        h = (arg0->menu.items->count << 5) + 8;
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + h + 5, arg0->window.frame.width, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, h, *(Color88100D9C*)&D_88102D74);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + h + 0xC, arg0->window.frame.width - 0xC, arg0->descriptionLines * 0x1C, D_88102D9C, D_88102DA0);
        sp38 = arg0->window.frame.width - 0xC;
        Menu_DrawItems(&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 0xA, arg1 | 0xFFED, (s32)&sp38);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(arg0->window.frame.x + 0xE, arg0->window.frame.y + h + 0x10, arg0->descriptions[arg0->menu.cursor]);
        Font_EndTexturedTextRendering();
    }
}

s32 Menu_UpdateCursor(void*);
M2C_UNK func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;

/**
 * Menu-list input handler (same pattern as PartyScreen_UpdateActionMenu and FreeBattle_UpdatePopupMenu). Returns 0
 * immediately unless the window state is 1 or 2. Then, while Menu_UpdateCursor(&arg0->menu)
 * is zero, reads the input result from func_8002BC14(D_800603C0): -1 plays sound
 * func_8003F6AC(3) and returns -1; 1 checks bit 0 of the cursor item's menu.itemFlags
 * -- if it is clear it plays sound 2 and returns
 * cursor + 1, otherwise it plays sound 8 and returns 0. Every other case returns 0.
 * (The meaning of the table bit is inferred from the sound choice only.)
 * Seen in play (2026-11-12): picked ポケモンを とうろくする from the menu.
 */
s32 Registration_UpdateMainMenu(MenuWindow* arg0) {
    s32 ret = 0;
    s32 dir;

    switch (arg0->window.state) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (Menu_UpdateCursor(&arg0->menu) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (dir == 1) {
            if (!(arg0->menu.itemFlags[arg0->menu.cursor] & 1)) {
                func_8003F6AC(2);
                ret = arg0->menu.cursor + 1;
            } else {
                func_8003F6AC(8);
            }
        }
    }
    return ret;
}

void Window_SetRect(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_800603C0;
extern Color_RGBA8 D_88102DA4;
extern char D_88102F14[];
extern char D_88102F1C[];
void Window_InitLabeled(void*, s32, s32, s32, Color_RGBA8, char*);
M2C_UNK func_8000B2F4(s32);
/**
 * Sets up the yes/no confirm window (372x102).
 * Seen in play (2026-11-12): opened 「このポケモンをとうろくする？」.
 */
void Registration_InitConfirmWindow(RegistrationConfirmWindow* arg, s32 arg1, s32 arg2, s32 arg3) {
    RegistrationConfirmWindow* arg0 = arg;
    Window_SetRect(arg, arg1, arg2, 0x174, 0x66);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x1001;
    Window_InitLabeled(&arg0->yesButton, arg0->window.frame.x + 0x62, arg0->window.frame.y + 0x42, 0x48, D_88102DA4, D_88102F14);
    arg0->yesButton.labelX = 0xA;
    arg0->yesButton.unk_34 = 0xC;
    Window_InitLabeled(&arg0->noButton, arg0->window.frame.x + 0xCA, arg0->window.frame.y + 0x42, 0x48, D_88102DA4, D_88102F1C);
    arg0->choice.count = 2;
    arg0->choice.cursor = 0;
    arg0->choice.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->text = (char*)arg3;
}

extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color88100D9C);

s32 func_8002AE6C();
extern u8 D_800734A8[4];
extern u8 D_8007356C[];
extern Color88100D9C D_88102DA8;
extern Color88100D9C D_88102DAC;
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color88100D9C, Color88100D9C);
void Window_DrawLabeled(void*, s32);

/**
 * Draws the confirm window with its message and buttons.
 * Seen in play (2026-11-12): 「このポケモンをとうろくする？」 with はい / いいえ.
 */
void Registration_DrawConfirmWindow(RegistrationConfirmWindow* arg0) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x35, arg0->window.frame.width, D_8007356C);
        Ui_FillRectPrimEnvColor(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, 0x30, D_88102DA8, D_88102DAC);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x3C, arg0->window.frame.width - 0xC, 0x24, *(Color88100D9C*)&D_88102D74);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(0x10, 0);
        Font_Printf(arg0->window.frame.x + 0x12, arg0->window.frame.y + 0x12, arg0->text);
        Font_EndTexturedTextRendering();
        Window_DrawLabeled(&arg0->yesButton, (arg0->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&arg0->noButton, (arg0->choice.cursor == 1) ? 2 : 0);
    }
}

s32 func_8002B390(void*);
M2C_UNK func_8002BC14(s32);
extern s32 D_800603C0;
/**
 * Handles the confirm window. Returns 1 for yes, -1 for no or cancel.
 * Seen in play (2026-11-12): はい confirmed the registration.
 */
s32 Registration_UpdateConfirmWindow(RegistrationConfirmWindow* arg0) {
    s32 sp1C = 0;

    if (func_8002B390(&arg0->choice) == 0) {
        sp1C = func_8002BC14(D_800603C0);
        if (sp1C == 1) {
            switch (arg0->choice.cursor) {
                case 0:
                    sp1C = 1;
                    break;
                case 1:
                    sp1C = -1;
                    break;
            }
        }
    }
    return sp1C;
}


extern u8 D_88102DB0[];
extern u8 D_88102DB4[];
void Window_SetRect(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/**
 * Sets up the message window (368x104).
 * Seen in play (2026-11-12): opened the message after registering.
 */
void Registration_InitMessageWindow(RegistrationMessageWindow* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Window_SetRect(arg0, arg1, arg2, 0x170, 0x68);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x1006;
    arg0->window.frame.color = *(Color_RGBA8*)D_88102DB0;
    arg0->window.frame.color2 = *(Color_RGBA8*)D_88102DB4;
    arg0->text = arg3;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
/**
 * Draws the message window text.
 * Seen in play (2026-11-12): 「メタモンのへんしんがおわりました。ポケモンは GBカートリッジに そのまま のこっています。」.
 */
void Registration_DrawMessageWindow(RegistrationMessageWindow* arg0) {
    u8* c;

    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        c = D_800734A8;
        Gfx_SetEnvColor(c[0], c[1], c[2], c[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(arg0->window.frame.x + 0xE, arg0->window.frame.y + 0xE, arg0->text);
        Font_EndTexturedTextRendering();
    }
}

M2C_UNK func_8002BC14(s32);                         /* extern */
extern s32 D_800603C0;

/**
 * Returns the confirm/cancel input while the message window is open.
 * Seen in play (2026-11-12): A closed that message.
 */
s32 Registration_UpdateMessageWindow(s32 arg0) {
    return func_8002BC14(D_800603C0);
}

/**
 * Appends a call of display list D_80060270 to the current display list and
 * then calls func_80029028(arg0, arg1, 0x88, 0x64, arg2). arg0 and arg1 are
 * passed straight through (the retail code never touches $a0/$a1); arg2 is a
 * 4-byte color passed by value.
 * Seen in play (2026-11-13) ran when the registration screen opened its Pokémon list, which shows
 * the trainer panel (1P, サトシ, IDNo/12345) on the left.
 */
void Registration_FillTrainerPanel(s32 arg0, s32 arg1, Color88100D9C arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x88, 0x64, arg2);
}

/**
 * Appends a call of display list D_80060270 to the current display list and
 * then calls func_80029028(arg0 + 0x88, arg1, 0x18C, 0x64, arg2). arg1 is
 * passed straight through (the retail code never touches $a1); arg2 is a
 * 4-byte color passed by value.
 * Seen in play (2026-11-13) ran when the registration screen opened its Pokémon list, which shows
 * the party (フシ, ヒト, カメ, L10) next to the trainer panel.
 */
void Registration_FillTeamPanel(s32 arg0, s32 arg1, Color88100D9C arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0 + 0x88, arg1, 0x18C, 0x64, arg2);
}

/**
 * Draws the top and bottom border lines of a team row.
 * Seen in play (2026-11-12): the border lines of the team rows.
 */
void Registration_DrawRowBorders(s32 arg0, s32 arg1, Color88100D9C arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x214, 1, arg2);
    func_80029028(arg0, arg1 + 0x63, 0x214, 1, arg2);
}

extern Color88100D9C D_88102D7C;
extern u8 D_88102DB8[];
extern char D_88102F24[];
extern char D_88102F2C[];
extern Gfx D_80073450[];
extern u8 D_04010918[];
void func_8001BCB4(s32, s32, s32, s32, void*, s32, s32);
u8 GbSave_GetPortGame(s32 arg0);
void func_8002BC58(s32, s32, u8, s32);
void Ui_DrawImageInStrips(u8*, s32, s32);
void Ui_DrawNumberZeroPadded(s32, s32, s32, s32);
/**
 * Draws the team source (GB cartridge port or registered slot number), なまえ (name) and trainer id.
 * Seen in play (2026-11-12): the 1P cartridge or 01 slot icon, なまえ サトシ and IDNo/12345.
 */
void Registration_DrawTrainerPanel(s32 arg0, s32 arg1, s32 arg2, RegisteredTeam* arg3) {
    UNUSED s32 pad[3]; // FAKE: stack padding

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x88, 0x64, D_88102D7C);
    if (arg3->unk_00 == 0) {
        if (arg3->source == 0x20) {
            func_8002BC58(arg0 + 5, arg1 + 4, arg3->pak, GbSave_GetPortGame(arg3->pak));
        } else if (arg3->source == 0x10) {
            Ui_DrawImageInStrips(D_88102DB8, arg0 + 4, arg1 + 4);
            Font_BeginTranslucentTextRendering();
            Font_SetColorForFlags(arg2);
            Font_SetActive(8, 0);
            Font_Printf(arg0 + 0x1B, arg1 + 0x1A, D_88102F24, arg3->slot + 1);
            Font_EndTexturedTextRendering();
        }
    }
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(0xFF, 0xC8, 0xC8, 0xFF);
    Font_SetActive(4, -1);
    Font_Printf(arg0 + 4, arg1 + 0x41, D_88102F2C);
    Font_SetColorForFlags(arg2);
    Font_SetActive(4, 0);
    Font_Printf(arg0 + 0x38, arg1 + 0x41, (char*)arg3->name);
    Font_EndTexturedTextRendering();
    if (arg3->trainerId != 0) {
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(arg0 + 0x25, arg1 + 0x56, 0x28, 0xA, D_04010918, 0x28, 0);
        Ui_DrawNumberZeroPadded(arg0 + 0x51, arg1 + 0x54, arg3->trainerId, 5);
    }
}

extern Color88100D9C D_88102D78[2];
/**
 * Fills both panels of a team row.
 * Seen in play (2026-11-12): the team row panels.
 */
void Registration_FillRowBackground(s32 x, s32 y, s32 height) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x88, height, D_88102D78[1]);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x + 0x88, y, 0x18C, height, D_88102D78[0]);
}

extern s32 D_88103074;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern u8 D_04011A60[];
s32 PokeIcon_GetImage(s8 *arg0, s32 arg1);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void Ui_DrawNumber(s32, s32, s32, s32);
/**
 * Draws one Pokemon cell of a team row: nickname, level and icon.
 * Seen in play (2026-11-12): ハナ L5, ヒノコ L5, カメ L5 with their icons.
 */
void Registration_DrawMonCell(s32 x, s32 y, u8* entry, s32 id, s32 color, IconCache8810173C* cache) {
    UNUSED s32 pad[4]; // FAKE
    s32 slot;
    s32* p;

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x84, 0x32, D_88102D78[0]);
    if (entry != NULL) {
        Font_BeginTranslucentTextRendering();
        Font_SetColorForFlags(color);
        Font_SetActive(4, 0);
        Font_Printf(x + 4, y + 4, entry + 0x30);
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80073450);
        func_8001BCB4(x + 0x2C, y + 0x19, 8, 0xA, D_04011A60, 8, 0);
        Ui_DrawNumber(x + 0x38, y + 0x17, entry[0x24], 3);
        slot = cache->base + id % cache->count;
        p = &cache->slots[slot];
        if (id != *p) {
            *p = id;
            func_8001833C(D_88103074, slot, entry, ((D_88102D78[0].c[1] << 3) & 0x7C0) | ((D_88102D78[0].c[2] >> 2) & 0x3E) | ((D_88102D78[0].c[0] << 8) & 0xF800) | 1);
        }
        if (cache) {} // FAKE: keeps cache live through the block above so the color table address takes t1
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(x + 0x56, y + 6, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_88103074, slot), 0x28, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }
}

extern s32 D_88103074;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
s32 PokeIcon_GetImage(s8 *arg0, s32 arg1);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws an empty Pokemon cell with the placeholder icon.
 * Seen in play (2026-11-12): the empty cells and the pink Ditto placeholders in slot 01.
 */
void Registration_DrawEmptyMonCell(s32 arg0, s32 arg1) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x84, 0x32, D_88102D78[0]);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    func_8001B884(arg0 + 0x56, arg1 + 6, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_88103074, 0x18), 0x28, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}

extern Gfx D_80073450[];
extern u8 D_04011A60[];
void func_8001BCB4(s32, s32, s32, s32, void*, s32, s32);
void Ui_DrawNumber(s32, s32, s32, s32);
void func_88101478(s32 x, s32 y, u8* entry, s32 frame, s32 color, s32* anim) {
    s32 idx;

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x84, 0x32, D_88102D78[0]);
    if (entry != NULL) {
        Font_BeginTranslucentTextRendering();
        Font_SetColorForFlags(color);
        Font_SetActive(4, 0);
        Font_Printf(x + 4, y + 4, entry + 0x30);
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80073450);
        func_8001BCB4(x + 0x2C, y + 0x19, 8, 0xA, D_04011A60, 8, 0);
        Ui_DrawNumber(x + 0x38, y + 0x17, entry[0x24], 3);
        idx = frame % anim[2] + anim[1];
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(x + 0x56, y + 6, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_88103074, idx), 0x28, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }
}

/**
 * Starts a timer at 0 that counts to `arg1` x 15.
 * Seen in play (2026-11-13) ran during the Ditto transform animation after registering the party
 * (とうろく > ポケモンをとうろくする, はい), which ends with メタモンのへんしんがおわりました.
 * @unverified Name and comment guessed from the code.
 */
void Registration_InitTimer(RegistrationTimer* arg0, s32 arg1) {
    arg0->frame = 0;
    arg0->steps = arg1;
    arg0->framesPerStep = 0xF;
}

/**
 * Starts a timer already at its end, `arg1` x 15.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Registration_InitTimerFull(RegistrationTimer* arg0, s32 arg1) {
    arg0->steps = arg1;
    arg0->framesPerStep = 0xF;
    arg0->frame = (s32) (arg1 * 0xF);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Returns whether the timer has reached its end.
 * Seen in play (2026-11-13) ran during the Ditto transform animation after registering the party
 * (とうろく > ポケモンをとうろくする, はい), which ends with メタモンのへんしんがおわりました.
 * @unverified Name and comment guessed from the code.
 */
s32 Registration_IsTimerDone(s8 *arg0)
{
 if (0) { }  // karodo
  return (*((s32 *) (((s8 *) arg0) + 0))) >= ((*((s32 *) (((s8 *) arg0) + 4))) * (*((s32 *) (((s8 *) arg0) + 8)))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

/**
 * Returns whether the timer is at 0.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 Registration_IsTimerAtStart(s32 *arg0) {
    return *arg0 == 0;
}

/**
 * Advances the timer by one and returns whether it is done.
 * Seen in play (2026-11-13) ran during the Ditto transform animation after registering the party
 * (とうろく > ポケモンをとうろくする, はい), which ends with メタモンのへんしんがおわりました.
 * @unverified Name and comment guessed from the code.
 */
s32 Registration_StepTimer(RegistrationTimer* arg0) {
    if (arg0->frame < arg0->framesPerStep * arg0->steps) {
        arg0->frame += 1;
    }
    return Registration_IsTimerDone(arg0);
}

/** Queues a sound unless one played recently, counting down a cooldown. */
s32 Audio_QueueSoundAvoidingRecent(s32* arg0) {
    if (*arg0 > 0) {
        *arg0 -= 1;
    }
    return Registration_IsTimerAtStart(arg0);
}

/**
 * Returns the timer's current value.
 * Seen in play (2026-11-13) ran during the Ditto transform animation after registering the party
 * (とうろく > ポケモンをとうろくする, はい), which ends with メタモンのへんしんがおわりました.
 * @unverified Name and comment guessed from the code.
 */
s32 Registration_GetTimer(s32 *arg0) {
    return *arg0;
}

extern Color88100D9C D_88102D80;
extern s32 D_88103098[];
/**
 * Draws the six Pokemon cells of a team row.
 * Seen in play (2026-11-12): the six cells of a team row.
 */
void Registration_DrawTeamRow(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    RegisteredTeam* box = (RegisteredTeam*)arg2;
    s32 pad[2]; // FAKE
    IconCache8810173C cache;
    s32 pad2; // FAKE
    s32 i;
    u8* entry;
    s32 color;

    if (box != NULL) {
        Registration_DrawTrainerPanel(arg0, arg1, arg4, box);
        cache.slots = D_88103098;
        cache.base = 0;
        cache.count = 24;
        cache.start = arg3 * 6;
        entry = box->mons.rows;
        for (i = 0; i < box->mons.count; i++, entry += sizeof(TeamMonSlot)) {
            color = 0;
            if (arg4 & 2) {
                color = 0x10000;
            }
            Registration_DrawMonCell(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1, entry + 4, arg3 * 6 + i, color, &cache);
        }
        for (; i < 6; i++) {
            color = 0;
            if (arg4 & 2) {
                color = 0x10000;
            }
            Registration_DrawMonCell(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1, NULL, arg3 * 6 + i, color, &cache);
        }
    } else {
        Registration_FillTrainerPanel(arg0, arg1, D_88102D7C);
        Registration_FillTeamPanel(arg0, arg1, D_88102D78[0]);
    }
    Registration_DrawRowBorders(arg0, arg1, D_88102D80);
}

/**
 * Draws a full team row: trainer panel and six Pokemon cells.
 * Seen in play (2026-11-12): a full team row.
 */
void Registration_DrawTeamRowWithTrainer(s32 arg0, s32 arg1, RegisteredTeam* arg2, s32 arg3, s32 arg4) {
    s32 pad[2]; // FAKE
    IconCache8810173C cache;
    s32 i;
    s32 n;
    u8* entry;

    entry = arg2->mons.rows;
    Registration_DrawTrainerPanel(arg0, arg1, 0, arg2);
    cache.slots = D_88103098;
    cache.base = 0;
    cache.count = 24;
    cache.start = arg3 * 6;
    if (arg4 == 0) {
        n = 0;
    } else if (arg4 == 1) {
        n = arg2->mons.count;
    } else {
        n = (arg4 - 2) / 15;
        if (n >= arg2->mons.count) {
            n = arg2->mons.count;
        }
    }
    for (i = 0; i < n; i++, entry += 0x54) {
        func_88101478(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1, entry + 4, arg3 * 6 + i, 0, (s32*)&cache);
    }
    for (; i < arg2->mons.count; i++) {
        Registration_DrawEmptyMonCell(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1);
    }
    for (; i < 6; i++) {
        Registration_DrawMonCell(arg0 + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + arg1, NULL, i, 0, NULL);
    }
    Registration_DrawRowBorders(arg0, arg1, D_88102D80);
}

/**
 * Registration_ClearIndices
 *
 * Stores -1 into arg2 consecutive words of the s32 array arg0, starting at
 * index arg1 (indices arg1 .. arg1 + arg2 - 1). Does nothing when
 * arg1 + arg2 <= arg1, i.e. when arg2 is not positive. The compare is signed.
 * What the -1 entries mean is not established from this function.
 * Seen in play (2026-11-12) in とうろく: ran with count 0x18 when the registration screen was set up,
 * before the team lists were built.
 */
void Registration_ClearIndices(s32* arg0, s32 arg1, s32 arg2) {
    s32 end;

    end = arg1 + arg2;
    for (; arg1 < end; arg1++) {
        arg0[arg1] = -1;
    }
}

/**
 * Sets the team list mode: 0 register, 1 view, 2 delete.
 * Seen in play (2026-11-12): set the list to register mode for ポケモンを とうろくする.
 */
void Registration_SetListMode(RegistrationTeamList* arg0, s32 arg1) {
    arg0->mode = arg1;
    switch (arg1) {                                 /* irregular */
    case 0:
        arg0->state = 0;
        return;
    case 1:
        arg0->state = 1;
        return;
    case 2:
        arg0->state = 2;
        return;
    }
}

extern M2C_UNK D_88102D84;
extern s32 D_88103098[];
M2C_UNK ScrollList_Init();
/**
 * Sets up the team list window (544x344) in mode `arg4`.
 * Seen in play (2026-11-12): opened the team list.
 */
void Registration_InitTeamList(RegistrationTeamList* arg0, s32 arg1, s32 arg2, s8 *arg3, s32 arg4) {
    Window_SetRect(&arg0->window, arg1, arg2, 0x220, 0x158);
    arg0->window.animTimer = 0;
    arg0->window.title = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    Registration_SetListMode(arg0, arg4);
    arg0->window.title = ((s32 *)&D_88102D84)[arg0->mode];
    arg0->teams = arg3;
    ScrollList_Init(&arg0->list, arg3, &arg0->itemFlags, 3, Registration_DrawTeamRow, 0x214, 0x64);
    arg0->list.options |= 0x10000;
    arg0->unk_00 = 0;
    Registration_ClearIndices(D_88103098, 0, 0x18);
}


/**
 * Registration_DrawTeamListRow
 *
 * Calls Registration_DrawTeamRow with the fields at +0x08 and +0x0C each increased by 6,
 * the entry at the current index (+0x5C) in the first table of arg0->tables,
 * that index, and two zero arguments.
 * Seen in play (2026-11-12): the team rows of the list.
 */
void Registration_DrawTeamListRow(RegistrationTeamList* arg0) {
    s32 index = arg0->list.cursor;
    s32* entry = &((s32*)arg0->list.items->rows)[index];

    Registration_DrawTeamRow(arg0->window.frame.x + 6, arg0->window.frame.y + 6, *entry, index, 0, 0);
}

void func_800189C0(s32, s32);
void BgStage_DrawFrame(void);
void ScrollList_DrawItems(void*, s32, s32, s32, s32);
/**
 * Draws the team list window for its current state.
 * Seen in play (2026-11-12): the ポケモンを とうろくする list window.
 */
void Registration_DrawTeamList(RegistrationTeamList* arg0) {
    func_800189C0(D_88103074, 0);
    BgStage_DrawFrame();
    if (func_8002AE6C(&arg0->window) == 0) {
        switch (arg0->state) {
            case 0:
            case 1:
            case 2:
                ScrollList_DrawItems(&arg0->list, arg0->window.frame.x + 6, arg0->window.frame.y + 0x16, 0xFFFF, 0);
                break;
            case 3:
                Registration_DrawTeamListRow(arg0);
                Registration_FillRowBackground(arg0->window.frame.x + 6, arg0->window.frame.y + 0x6A, 0x84);
                Registration_DrawTeamRowWithTrainer(arg0->window.frame.x + 6, arg0->window.frame.y + 0xEE, &arg0->selectedTeam,
                              arg0->list.cursor, 0);
                Registration_DrawConfirmWindow(&arg0->confirmWindow);
                break;
            case 4:
                Registration_DrawTeamListRow(arg0);
                Registration_FillRowBackground(arg0->window.frame.x + 6, arg0->window.frame.y + 0x6A, 0x84);
                Registration_DrawTeamRowWithTrainer(arg0->window.frame.x + 6, arg0->window.frame.y + 0xEE, &arg0->selectedTeam,
                              arg0->list.cursor, Registration_GetTimer((s32*)(&arg0->timer)) + 0x10);
                break;
            case 5:
                Registration_DrawTeamListRow(arg0);
                Registration_FillRowBackground(arg0->window.frame.x + 6, arg0->window.frame.y + 0x6A, 0x84);
                Registration_DrawTeamRowWithTrainer(arg0->window.frame.x + 6, arg0->window.frame.y + 0xEE, &arg0->selectedTeam,
                              arg0->list.cursor, 1);
                Registration_DrawMessageWindow(&arg0->messageWindow);
                break;
            case 6:
                Registration_DrawTeamRowWithTrainer(arg0->window.frame.x + 6, arg0->window.frame.y + 6, &arg0->selectedTeam,
                              arg0->list.cursor, 1);
                Registration_FillRowBackground(arg0->window.frame.x + 6, arg0->window.frame.y + 0x6A, 0xE8);
                Registration_DrawConfirmWindow(&arg0->confirmWindow);
                break;
            case 7:
                Registration_DrawTeamRowWithTrainer(arg0->window.frame.x + 6, arg0->window.frame.y + 6, &arg0->selectedTeam,
                              arg0->list.cursor, Registration_GetTimer((s32*)(&arg0->timer)) + 2);
                Registration_FillRowBackground(arg0->window.frame.x + 6, arg0->window.frame.y + 0x6A, 0xE8);
                break;
            case 8:
                Registration_DrawTeamRowWithTrainer(arg0->window.frame.x + 6, arg0->window.frame.y + 6, &arg0->selectedTeam,
                              arg0->list.cursor, 0);
                Registration_FillRowBackground(arg0->window.frame.x + 6, arg0->window.frame.y + 0x6A, 0xE8);
                Registration_DrawMessageWindow(&arg0->messageWindow);
                break;
        }
    }
}

extern char D_88102F34[];
extern char D_88102F54[];
extern char D_88102F6C[];
extern char D_88102FC8[];
s32 ScrollList_UpdateCursor(void*);
void Audio_PlayMoveSound(s32, s32, s32);
void func_80027868(s32, s32);

/**
 * Runs the team list's state machine: pick, confirm, register or delete, messages.
 * Seen in play (2026-11-12): ran the pick, confirm, register and message steps.
 */
s32 Registration_UpdateTeamList(RegistrationTeamList* arg0) {
    s32 ret = 0;
    s32 res;

    switch (arg0->state) {
        case 0:
            if (ScrollList_UpdateCursor(&arg0->list) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (res == 1) {
                    func_8003F6AC(2);
                    arg0->state = 3;
                    Registration_InitConfirmWindow(&arg0->confirmWindow, arg0->window.frame.x + 0x56, arg0->window.frame.y + 0x79, (s32)D_88102F34);
                    arg0->selectedTeam = *((RegisteredTeam**)arg0->list.items->rows)[arg0->list.cursor];
                    arg0->selectedTeam.source = 0x10;
                    arg0->selectedTeam.slot = Registration_FindFreeSlot();
                }
            }
            break;
        case 1:
            if ((ScrollList_UpdateCursor(&arg0->list) == 0) && (func_8002BC14(D_800603C0) == -1)) {
                func_8003F6AC(3);
                ret = -1;
            }
            break;
        case 2:
            if (ScrollList_UpdateCursor(&arg0->list) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                    Registration_WriteAllTeams(arg0->teams);
                } else if (res == 1) {
                    func_8003F6AC(2);
                    arg0->selectedTeam = *((RegisteredTeam**)arg0->list.items->rows)[arg0->list.cursor];
                    Registration_InitConfirmWindow(&arg0->confirmWindow, arg0->window.frame.x + 0x56, arg0->window.frame.y + 0x79, (s32)D_88102F54);
                    arg0->confirmWindow.choice.cursor = 1;
                    arg0->state = 6;
                }
            }
            break;
        case 3:
            res = Registration_UpdateConfirmWindow((s32)(&arg0->confirmWindow));
            if (res == -1) {
                func_8003F6AC(3);
                arg0->state = 0;
            } else if (res == 1) {
                func_8003F6AC(2);
                Registration_WriteTeam(((RegisteredTeam**)arg0->list.items->rows)[arg0->list.cursor], Registration_FindFreeSlot());
                Registration_InitTimer(&arg0->timer, arg0->selectedTeam.mons.count);
                arg0->state = 4;
            }
            break;
        case 4:
            if (arg0->timer.frame % 15 == 0) {
                Audio_PlayMoveSound(0x90, 1, 0);
            }
            if (Registration_StepTimer(&arg0->timer) != 0) {
                func_8003F6AC(0x1E);
                Registration_InitMessageWindow(&arg0->messageWindow, arg0->window.frame.x + 0x58, arg0->window.frame.y + 0x78, (s32)D_88102F6C);
                arg0->state = 5;
            }
            break;
        case 5:
            res = Registration_UpdateMessageWindow((s32)(&arg0->messageWindow));
            if ((res == -1) || (res == 1)) {
                func_8003F6AC(2);
                ret = -1;
            }
            break;
        case 6:
            res = Registration_UpdateConfirmWindow((s32)(&arg0->confirmWindow));
            if (res == -1) {
                func_8003F6AC(3);
                arg0->state = 2;
            } else if (res == 1) {
                func_8003F6AC(2);
                Registration_InitTimerFull(&arg0->timer, arg0->selectedTeam.mons.count);
                arg0->state = 7;
            }
            break;
        case 7:
            if (arg0->timer.frame % 15 == 0) {
                Audio_PlayMoveSound(0x90, 1, 0);
            }
            if (Audio_QueueSoundAvoidingRecent((s32*)(&arg0->timer)) != 0) {
                func_8003F6AC(0x1F);
                func_80027868(arg0->teams, arg0->list.cursor);
                Registration_WriteAllTeams(arg0->teams);
                Registration_InitMessageWindow(&arg0->messageWindow, arg0->window.frame.x + 0x58, arg0->window.frame.y + 0x78, (s32)D_88102FC8);
                arg0->state = 8;
            }
            break;
        case 8:
            res = Registration_UpdateMessageWindow((s32)(&arg0->messageWindow));
            if ((res == -1) || (res == 1)) {
                func_8003F6AC(2);
                ret = -1;
            }
            break;
    }
    return ret;
}

/**
 * Registration_BuildTeamPointers
 *
 * Builds a table of pointers into a block of equally sized records.
 * arg1 holds the address of the first record at +0x00 and the record count
 * at +0x08.  arg0 holds the address of the pointer table at +0x00; entry i
 * is set to (first record + i * 0x220), so each record is 0x220 bytes.
 * The count is then copied to arg0 + 0x08.  What the records are is not
 * known from the code alone.
 *
 * FreeBattle_BuildTeamPointers is the same routine with a record size of 0x214.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in registration.
 * @unverified Name guessed from the code; comment kept.
 */
void Registration_BuildTeamPointers(s32* arg0, s32* arg1) {
    s32 value = arg1[0];
    s32* out = (s32*)arg0[0];
    s32 i = 0;

    if (arg1[2] > 0) {
        do {
            *out = value;
            i += 1;
            value += 0x220;
            out += 1;
        } while (i < arg1[2]);
    }
    arg0[2] = arg1[2];
}

void func_80027410(void*, void*, s32, s32, s32);
void func_80027804(void*, void*, s32, s32);

/**
 * Loads the registered teams and opens the list in view mode.
 * Seen in play (2026-11-12) in とうろく: とうろくした ポケモンをみる ran this and showed the registered team (slot
 * 01: ハナ, ヒノコ, カメ).
 */
void Registration_OpenViewList(RegistrationScreen* arg0) {
    func_80027410(&arg0->teamTable, arg0->teamBuffer, sizeof(RegisteredTeam), 0x10, 0);
    Registration_LoadRegisteredTeams(&arg0->teamTable);
    func_80027804(&arg0->teamPointerList, arg0->teamPointers, 0x10, 0);
    Registration_BuildTeamPointers((s32*)&arg0->teamPointerList, (s32*)&arg0->teamTable);
    Registration_InitTeamList(&arg0->teamList, 0x30, 0x5C, &arg0->teamPointerList, 1);
}

void func_80027410(void*, void*, s32, s32, s32);
void func_80027804(void*, void*, s32, s32);

/**
 * Loads the registered teams and opens the list in delete mode.
 * Seen in play (2026-11-12) in とうろく: とうろくした ポケモンをけす ran this and showed the same list with
 * 「このポケモンをけす？」 on A.
 */
void Registration_OpenDeleteList(RegistrationScreen* arg0) {
    func_80027410(&arg0->teamTable, arg0->teamBuffer, sizeof(RegisteredTeam), 0x10, 0);
    Registration_LoadRegisteredTeams(&arg0->teamTable);
    func_80027804(&arg0->teamPointerList, arg0->teamPointers, 0x10, 0);
    Registration_BuildTeamPointers((s32*)&arg0->teamPointerList, (s32*)&arg0->teamTable);
    Registration_InitTeamList(&arg0->teamList, 0x30, 0x5C, &arg0->teamPointerList, 2);
}

void func_80027410(void*, void*, s32, s32, s32);
void func_80027804(void*, void*, s32, s32);

/**
 * Loads the Game Boy teams and opens the list in register mode.
 * Seen in play (2026-11-12): ポケモンを とうろくする loaded the cartridge party and opened the list.
 */
void Registration_OpenRegisterList(RegistrationScreen* arg0) {
    func_80027410(&arg0->teamTable, arg0->teamBuffer, sizeof(RegisteredTeam), 4, 0);
    Registration_LoadGbTeams(&arg0->teamTable);
    func_80027804(&arg0->teamPointerList, arg0->teamPointers, 4, 0);
    Registration_BuildTeamPointers((s32*)&arg0->teamPointerList, (s32*)&arg0->teamTable);
    Registration_InitTeamList(&arg0->teamList, 0x30, 0x5C, &arg0->teamPointerList, 0);
}

s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);
extern M2C_UNK D_88102D84;
extern M2C_UNK D_88102D90;
extern M2C_UNK D_88103000;
extern s32 D_88103078;
extern M2C_UNK D_88103080;

/**
 * Stores the result of func_80025BD8() in D_88103078. If it is not -1, passes it with
 * &D_88103080 to func_80027FF8 (the value is re-read from D_88103078 after the store,
 * as the retail register allocation requires). Then restarts the sub-object at
 * arg0 + 4 with Registration_InitMainMenu(arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3,
 * &D_88102D90, 3, &D_88103000) and sets the state word *arg0 to 0.
 * arg0 is declared s32 to agree with the existing Registration_InitScreen(s32) prototype; it is
 * used as a byte-addressed pointer. What the object and the value mean is not established.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void Registration_InitScreen(RegistrationScreen* arg0) {
    D_88103078 = func_80025BD8();
    if (D_88103078 != -1) {
        func_80027FF8(&D_88103080, D_88103078);
    }
    Registration_InitMainMenu(&arg0->mainMenu, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3, &D_88102D90, 3, &D_88103000);
    arg0->state = 0;
}

void BgStage_DrawFrame(void);
void Ui_DrawTintedScreenBackground(s32, s32, s32, s32, s32);
extern u8 D_88102D70[];
/**
 * Draws the registration screen for its current state.
 * Seen in play (2026-11-12): drew the とうろく screen every frame.
 */
M2C_UNK Registration_DrawScreen(RegistrationScreen* arg0) {
    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, D_88102D70[0], D_88102D70[1], D_88102D70[2]);
    switch (arg0->state) {
        case 0:
            Registration_DrawMainMenu(&arg0->mainMenu, 2);
            break;
        case 1:
            Registration_DrawTeamList(&arg0->teamList);
            break;
    }
}

/*
 * Registration_UpdateScreen
 *
 * One step of a two-state routine on the object at address `arg0` (passed
 * as an integer); the first word of the object is the state.  Returns 1 when
 * finished, otherwise 0.
 *
 *   state 0: r = Registration_UpdateMainMenu(arg0 + 4)
 *            r == -1: return 1
 *            r == 1:  Registration_OpenRegisterList(arg0), state = 1
 *            r == 2:  Registration_OpenViewList(arg0), state = 1
 *            r == 3:  Registration_OpenDeleteList(arg0), state = 1
 *   state 1: if Registration_UpdateTeamList(arg0 + 0x88) == -1, restart the sub-object
 *            with Registration_InitMainMenu(arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE,
 *            &D_88102D84, 3, &D_88102D90, 3, &D_8810300C) and set state 0.
 *
 * Offsets are byte offsets: `arg0 + 4` is the address four bytes in (the
 * m2c draft treated arg0 as an s32 pointer, which scales by four and does
 * not match).  What the states and helpers do is not established; the
 * helpers are still assembly.
 */
extern M2C_UNK D_88102D84;
extern M2C_UNK D_88102D90;
extern M2C_UNK D_8810300C;

/**
 * Runs the registration screen's state machine for one frame.
 * Seen in play (2026-11-12): ran the とうろく screen.
 */
s32 Registration_UpdateScreen(RegistrationScreen* arg0) {
    s32 sp3C;
    s32 temp_v0;
    s32 temp_v0_2;

    sp3C = 0;
    temp_v0 = arg0->state;
    switch (temp_v0) {
    case 0:
        temp_v0_2 = Registration_UpdateMainMenu(&arg0->mainMenu);
        if (temp_v0_2 == -1) {
            sp3C = 1;
        } else if (temp_v0_2 == 1) {
            Registration_OpenRegisterList(arg0);
            arg0->state = 1;
        } else if (temp_v0_2 == 2) {
            Registration_OpenViewList(arg0);
            arg0->state = 1;
        } else if (temp_v0_2 == 3) {
            Registration_OpenDeleteList(arg0);
            arg0->state = 1;
        }
        break;
    case 1:
        if (Registration_UpdateTeamList(&arg0->teamList) == -1) {
            Registration_InitMainMenu(&arg0->mainMenu, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3, &D_88102D90, 3, &D_8810300C);
            arg0->state = 0;
        }
        break;
    }
    return sp3C;
}

s32 func_80002D98(s32);
extern s32 D_88103074;
extern RegistrationScreen* D_881030F8;

/**
 * Registration_AllocScreen
 *
 * Setup step for this fragment: calls func_80002D98(0x26B4) (the symbol file
 * names that address Util_Malloc), keeps the result in D_881030F8, passes it
 * to Registration_InitScreen, then calls func_80018234(D_88103074, 0x18, 0x84, 0xF800).
 * What the 0x26B4-byte block holds and what Registration_InitScreen does with it are
 * not established here (D_881030F8 is later passed to Registration_DrawScreen and
 * Registration_UpdateScreen by Registration_RunFrame).
 * Matching note: the call result is stored straight into D_881030F8 and the
 * global is read back for the next call; going through a local gives a
 * different store sequence.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void Registration_AllocScreen(void) {
    D_881030F8 = (RegistrationScreen*)func_80002D98(sizeof(RegistrationScreen));
    Registration_InitScreen(D_881030F8);
    func_80018234(D_88103074, 0x18, 0x84, 0xF800);
}

typedef struct Col88102A2C { u8 r, g, b, a; } Col88102A2C;
extern s32 D_88102DCC;
extern s32 D_88102DD0;
/* Second name for D_88102DCC; see func_8A202F50 in lab_pc_icons.c. */
extern s32 D_88102DCC_2;
extern M2C_UNK D_88103018;
void func_800189C0(s32, s32);
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(Col88102A2C*, Col88102A2C, f32);
/**
 * Steps the screen fade; returns once eight frames have passed.
 * Seen in play (2026-11-13) ran on the frames the registration screen faded in from the main menu.
 */
s32 Registration_UpdateFade(s32 arg0) {
    Col88102A2C sp2C;
    M2C_UNK *var_a1;
    s32 n;

    n = D_88102DCC;
    if (n >= 8) {
        D_88102DD0 = 1;
    }
    if (D_88102DD0 != 0) {
        n--;
        D_88102DCC_2 = n;
    }
    func_800189C0(D_88103074, 0);
    BgStage_DrawFrame();
    if (D_88103078 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88103080;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_88103018, D_88103078);
    n = D_88102DCC;
    func_8002C8D8(&sp2C, *(Col88102A2C*)D_88102D70, n / (f64)8.0f);
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, sp2C.r, sp2C.g, sp2C.b);
    if (D_88102DD0 == 0) {
        n = D_88102DCC;
        n++;
        D_88102DCC = n;
    }
    return 0;
}

void Cont_StartReadInputs(void);                            /* extern */
void Cont_ReadInputs(void);                            /* extern */
extern RegistrationScreen* D_881030F8;

/**
 * One frame of the registration screen.
 * Seen in play (2026-11-12): ran every frame of the とうろく screen.
 */
void Registration_RunFrame(s32 arg0) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Registration_DrawScreen(D_881030F8);
    Registration_UpdateScreen(D_881030F8);
}

M2C_UNK func_80002DC0(s32);                         /* extern */
extern RegistrationScreen* D_881030F8;

/**
 * Frees the registration screen state.
 * Seen in play (2026-11-12): B on the menu left the screen for the main menu.
 */
void Registration_FreeScreen(void) {
    func_80002DC0(D_881030F8);
}

M2C_UNK func_8000256C(M2C_UNK);
M2C_UNK func_80002620(M2C_UNK);
M2C_UNK func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK func_800040B4(s32, M2C_UNK *, M2C_UNK *);
M2C_UNK func_80006724();
M2C_UNK func_8000675C();
M2C_UNK func_80006828(M2C_UNK, void*);
s8 *PokeIcon_AllocFramebuffers(s32 arg0);
M2C_UNK PokeIcon_OpenModelArchives();
s32 func_80017FDC(s32, M2C_UNK, M2C_UNK, M2C_UNK);
s32 Font_Init(s32 load_size, s32 side);
M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32);
extern M2C_UNK D_0015B1A0;
extern M2C_UNK D_0015E220;
extern M2C_UNK D_00235D70;
extern M2C_UNK D_00238BD0;
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_00400F70;
extern M2C_UNK D_004076E0;
extern M2C_UNK D_004199E0;
extern M2C_UNK D_0042C4A0;
extern M2C_UNK D_01000000;
extern M2C_UNK D_04000000;
extern M2C_UNK D_05000000;
extern M2C_UNK D_81000000;
extern M2C_UNK D_88000000;
extern s32 D_88103070;
extern s32 D_88103074;
/**
 * Entry point: pushes the 'REGS' pool state, loads the icons and segments, and runs the registration screen.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 Registration_Init(s32 arg0, s32 arg1) {
    func_8000256C(0x52454753);
    Font_Init(0x3C, 0);
    D_88103070 = PokeIcon_AllocFramebuffers(1);
    D_88103074 = func_80017FDC(D_88103070, 0x19, 0x28, 0x28);
    PokeIcon_OpenModelArchives();
    func_800040B4(((u32)((s32)&D_81000000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015B1A0, &D_0015E220);
    func_80003EB8((u32)((s32)&D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_80003EB8((u32)((s32)&D_04000000 & 0x0F000000) >> 0x18, &D_00400F70, &D_004076E0, 0);
    func_80003EB8((u32)((s32)&D_05000000 & 0x0F000000) >> 0x18, &D_004199E0, &D_0042C4A0, 0);
    Registration_AllocScreen();
    func_8000675C();
    func_80006828(8, Registration_UpdateFade);
    func_80006828(0, Registration_RunFrame);
    func_80006828(8, Registration_UpdateFade);
    func_80006724();
    Registration_FreeScreen();
    func_80002620(0x52454753);
    func_80025BA0(((u32)((s32)&D_88000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00235D70, &D_00238BD0, 0, 0);
    return 0x8040;
}
