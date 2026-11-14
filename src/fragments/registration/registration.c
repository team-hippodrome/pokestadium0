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
 * Reads up to six Pokémon of deck `deck` (0x10 the Stadium save, 0x20 a Game Boy cartridge), Transfer Pak
 * `pak` and slot `slot` into `mons` and stores the count.
 * Seen in play (2026-11-12): read the cartridge party ハナ L5, ヒノコ L5, カメ L5 into the list.
 * Seen in play (2026-11-14): ran with (0x20, 0, 0) for the 1P cartridge and (0x10, 0, 0) for registered slot 01.
 */
void Registration_ReadTeam(s32 deck, s32 pak, s32 slot, ByteMatrix* mons) {
    TeamMonSlot* entry = (TeamMonSlot*)mons->rows;
    s32 handle = func_80020AFC(deck, pak, slot, 0);
    s32 i;

    for (i = 0; i < 6; i++, entry++) {
        if (func_80020CE4(&entry->mon, 1, handle) == 0) {
            break;
        }
        entry->flags = 0;
    }
    func_80020C60(handle);
    mons->count = i;
}

s32 func_80020B94(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s8 *, s32); /* extern */
M2C_UNK func_80020C60(s32);                         /* extern */
s32 func_80020DF0(s32, M2C_UNK, s32);               /* extern */
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Writes `team` into registered slot `slot` of the Stadium save (deck 0x10).
 * Seen in play (2026-11-12): 「このポケモンをとうろくする？」 > はい stored the party in slot 01.
 */
void Registration_WriteTeam(s8 *team, M2C_UNK slot)
{
  s32 temp_s3;
  s32 var_s0;
  s32 var_s1;
  var_s1 = *((s32 *) (((s8 *) team) + 0x18));
  if ((!team) && (!team))
  {
  }
  temp_s3 = func_80020B94(0x10, 0, slot, 0, team + 8, *((s32 *) (((s8 *) team) + 4)));
  var_s0 = 0;
  if ((*((s32 *) (((s8 *) team) + 0x20))) > 0)
  {
    loop_1:
    if (func_80020DF0(var_s1 + 4, 1, temp_s3) != 0)
    {
      var_s0 += 1;
      var_s1 += 0x54;
      if (var_s0 < (*((s32 *) (((s8 *) team) + 0x20))))
      {
        goto loop_1;
      }
    }

  }
  func_80020C60(temp_s3);
}

s32 func_800245E0(M2C_UNK, s32);
/**
 * Writes every team of `teams` back to slots 0.. in order, then deletes the saved teams in the
 * slots after them, so the registered teams stay packed from slot 01.
 * The separate `base` local reproduces the ROM's register copy (the array pointer is loaded
 * before the first count is tested).
 * Seen in play (2026-11-12) in とうろく: ran after はい on 「このポケモンをけす？」 (「へんしん していた メタモンが もとの すがたに
 * もどった。」). With no team left, the view and delete entries were then greyed out.
 */
void Registration_WriteAllTeams(PointerList* teams) {
    s32 i;
    s8 **p;
    s8 **base;

    base = teams->items;
    i = 0;
    if (teams->count > 0) {
        p = base;
        do {
            Registration_WriteTeam(*p, i);
            i++;
            p++;
        } while (i < teams->count);
    }
    for (; i < teams->capacity; i++) {
        if (func_800246A8(0x10, i) != 0) {
            func_800245E0(0x10, i);
        }
    }
}

s32 Deck_GetSaveEntryCount(s32, s32);
void func_80027410(void*, void*, s32, s32, s32);
s32 Deck_GetSaveEntryTrainerId(s32, s32);
s32 Deck_GetSaveEntryName(s32 arg0, s32 arg1, u8* arg2);
/**
 * Reads every used registered slot (deck 0x10) with its trainer id and name.
 * Seen in play (2026-11-12): filled the 01 slot row (Ditto placeholders until the copy finished).
 */
void Registration_LoadRegisteredTeams(ByteMatrix* table) {
    RegisteredTeam* p = (RegisteredTeam*)table->rows;
    s32 i;

    for (i = 0; i < 0x10; i++) {
        if (func_800246A8(0x10, i) == 0) {
            continue;
        }
        if (Deck_GetSaveEntryCount(0x10, i) == 0) {
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
    table->count = p - (RegisteredTeam*)table->rows;
}

s32 func_80021894(s32);
s32 GbSave_GetTrainerId(s32 arg0);
void func_80022D84(s32, u8*);
/**
 * Reads the party of each Game Boy cartridge in the four Transfer Paks (deck 0x20).
 * Seen in play (2026-11-12): ポケモンを とうろくする listed the 1P cartridge's party.
 */
void Registration_LoadGbTeams(ByteMatrix* table) {
    RegisteredTeam* p = (RegisteredTeam*)table->rows;
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
    table->count = p - (RegisteredTeam*)table->rows;
}

extern Color_RGBA8 D_88102D74;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);

/**
 * Draws one menu row label with the selection highlight.
 * Seen in play (2026-11-12): one row of the とうろく menu.
 */
void Registration_DrawMenuRow(s32 x, s32 y, char* label, s32 index, s32 flags, s32* width) {
    s32 temp_v0 = *width;

    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, temp_v0 - 6, 0x1A, D_88102D74);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 8, y + 4, label);
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
void Registration_InitMainMenu(MenuWindow* menu, s32 x, s32 y, s32 width, s32 height, M2C_UNK* labels, s32 labelCount, M2C_UNK* descriptions, s32 descriptionLines, M2C_UNK* title) {
    s32 sp2C;

    Window_SetRect(menu, x, y, width, height);
    menu->window.state = 0;
    menu->window.animTimer = 0;
    menu->window.frame.style = 0x801;
    menu->window.title = (s32)title;
    func_80027804(&menu->itemList, (s8*)labels, labelCount, labelCount);
    Menu_Init(&menu->menu, &menu->itemList, &menu->itemFlags, (M2C_UNK*)Registration_DrawMenuRow, width - 0xC, 0x20);
    menu->menu.options = (s32) (menu->menu.options | 0x10000);
    menu->descriptions = (s32)descriptions;
    menu->descriptionLines = descriptionLines;
    sp2C = Registration_FindFreeSlot();
    if ((func_800226BC(0x20, D_88103078, 0) == 0) || (sp2C == -1)) {
        menu->menu.itemFlags[0] |= 1;
    }
    if (sp2C == 0) {
        menu->menu.itemFlags[1] |= 1;
        menu->menu.itemFlags[2] |= 1;
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
void Registration_DrawMainMenu(MenuWindow* menu, s32 flags) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 sp38;
    s32 h;

    if (func_8002AE6C() == 0) {
        h = (menu->menu.items->count << 5) + 8;
        Ui_DrawTexturedDivider(menu->window.frame.x, menu->window.frame.y + h + 5, menu->window.frame.width, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(menu->window.frame.x + 6, menu->window.frame.y + 6, menu->window.frame.width - 0xC, h, *(Color88100D9C*)&D_88102D74);
        Ui_FillRectPrimEnvColor(menu->window.frame.x + 6, menu->window.frame.y + h + 0xC, menu->window.frame.width - 0xC, menu->descriptionLines * 0x1C, D_88102D9C, D_88102DA0);
        sp38 = menu->window.frame.width - 0xC;
        Menu_DrawItems(&menu->menu, menu->window.frame.x + 6, menu->window.frame.y + 0xA, flags | 0xFFED, (s32)&sp38);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(menu->window.frame.x + 0xE, menu->window.frame.y + h + 0x10, menu->descriptions[menu->menu.cursor]);
        Font_EndTexturedTextRendering();
    }
}

s32 Menu_UpdateCursor(void*);
M2C_UNK func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;

/**
 * Menu-list input handler (same pattern as PartyScreen_UpdateActionMenu and FreeBattle_UpdatePopupMenu). Returns 0
 * immediately unless the window state is 1 or 2. Then, while Menu_UpdateCursor(&menu->menu)
 * is zero, reads the input result from func_8002BC14(D_800603C0): -1 plays sound
 * func_8003F6AC(3) and returns -1; 1 checks bit 0 of the cursor item's menu.itemFlags
 * -- if it is clear it plays sound 2 and returns
 * cursor + 1, otherwise it plays sound 8 and returns 0. Every other case returns 0.
 * (The meaning of the table bit is inferred from the sound choice only.)
 * Seen in play (2026-11-12): picked ポケモンを とうろくする from the menu.
 */
s32 Registration_UpdateMainMenu(MenuWindow* menu) {
    s32 ret = 0;
    s32 dir;

    switch (menu->window.state) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (Menu_UpdateCursor(&menu->menu) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (dir == 1) {
            if (!(menu->menu.itemFlags[menu->menu.cursor] & 1)) {
                func_8003F6AC(2);
                ret = menu->menu.cursor + 1;
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
void Registration_InitConfirmWindow(RegistrationConfirmWindow* confirm, s32 x, s32 y, s32 text) {
    RegistrationConfirmWindow* w = confirm;
    Window_SetRect(confirm, x, y, 0x174, 0x66);
    w->window.animTimer = 0;
    w->window.title = 0;
    w->window.state = 0;
    w->window.frame.style = 0x1001;
    Window_InitLabeled(&w->yesButton, w->window.frame.x + 0x62, w->window.frame.y + 0x42, 0x48, D_88102DA4, D_88102F14);
    w->yesButton.labelX = 0xA;
    w->yesButton.unk_34 = 0xC;
    Window_InitLabeled(&w->noButton, w->window.frame.x + 0xCA, w->window.frame.y + 0x42, 0x48, D_88102DA4, D_88102F1C);
    w->choice.count = 2;
    w->choice.cursor = 0;
    w->choice.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    w->text = (char*)text;
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
void Registration_DrawConfirmWindow(RegistrationConfirmWindow* confirm) {
    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(confirm->window.frame.x, confirm->window.frame.y + 0x35, confirm->window.frame.width, D_8007356C);
        Ui_FillRectPrimEnvColor(confirm->window.frame.x + 6, confirm->window.frame.y + 6, confirm->window.frame.width - 0xC, 0x30, D_88102DA8, D_88102DAC);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(confirm->window.frame.x + 6, confirm->window.frame.y + 0x3C, confirm->window.frame.width - 0xC, 0x24, *(Color88100D9C*)&D_88102D74);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(0x10, 0);
        Font_Printf(confirm->window.frame.x + 0x12, confirm->window.frame.y + 0x12, confirm->text);
        Font_EndTexturedTextRendering();
        Window_DrawLabeled(&confirm->yesButton, (confirm->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&confirm->noButton, (confirm->choice.cursor == 1) ? 2 : 0);
    }
}

s32 func_8002B390(void*);
M2C_UNK func_8002BC14(s32);
extern s32 D_800603C0;
/**
 * Handles the confirm window. Returns 1 for yes, -1 for no or cancel.
 * Seen in play (2026-11-12): はい confirmed the registration.
 */
s32 Registration_UpdateConfirmWindow(RegistrationConfirmWindow* confirm) {
    s32 ret = 0;

    if (func_8002B390(&confirm->choice) == 0) {
        ret = func_8002BC14(D_800603C0);
        if (ret == 1) {
            switch (confirm->choice.cursor) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    ret = -1;
                    break;
            }
        }
    }
    return ret;
}


extern u8 D_88102DB0[];
extern u8 D_88102DB4[];
void Window_SetRect(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/**
 * Sets up the message window (368x104).
 * Seen in play (2026-11-12): opened the message after registering.
 */
void Registration_InitMessageWindow(RegistrationMessageWindow* message, s32 x, s32 y, s32 text) {
    Window_SetRect(message, x, y, 0x170, 0x68);
    message->window.animTimer = 0;
    message->window.title = 0;
    message->window.state = 0;
    message->window.frame.style = 0x1006;
    message->window.frame.color = *(Color_RGBA8*)D_88102DB0;
    message->window.frame.color2 = *(Color_RGBA8*)D_88102DB4;
    message->text = text;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
/**
 * Draws the message window text.
 * Seen in play (2026-11-12): 「メタモンのへんしんがおわりました。ポケモンは GBカートリッジに そのまま のこっています。」.
 */
void Registration_DrawMessageWindow(RegistrationMessageWindow* message) {
    u8* c;

    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        c = D_800734A8;
        Gfx_SetEnvColor(c[0], c[1], c[2], c[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(message->window.frame.x + 0xE, message->window.frame.y + 0xE, message->text);
        Font_EndTexturedTextRendering();
    }
}

M2C_UNK func_8002BC14(s32);                         /* extern */
extern s32 D_800603C0;

/**
 * Returns the confirm/cancel input while the message window is open.
 * Seen in play (2026-11-12): A closed that message.
 */
s32 Registration_UpdateMessageWindow(s32 message) {
    return func_8002BC14(D_800603C0);
}

/**
 * Fills the trainer panel (136x100) of a team row at (`x`, `y`) with `color`.
 * Seen in play (2026-11-13) ran when the registration screen opened its Pokémon list, which shows
 * the trainer panel (1P, サトシ, IDNo/12345) on the left.
 */
void Registration_FillTrainerPanel(s32 x, s32 y, Color88100D9C color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x88, 0x64, color);
}

/**
 * Fills the team panel (396x100) right of the trainer panel of a team row at (`x`, `y`) with `color`.
 * Seen in play (2026-11-13) ran when the registration screen opened its Pokémon list, which shows
 * the party (フシ, ヒト, カメ, L10) next to the trainer panel.
 */
void Registration_FillTeamPanel(s32 x, s32 y, Color88100D9C color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x + 0x88, y, 0x18C, 0x64, color);
}

/**
 * Draws the top and bottom border lines of a team row.
 * Seen in play (2026-11-12): the border lines of the team rows.
 */
void Registration_DrawRowBorders(s32 x, s32 y, Color88100D9C color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x214, 1, color);
    func_80029028(x, y + 0x63, 0x214, 1, color);
}

extern Color88100D9C D_88102D7C;
extern u8 D_88102DB8[];
extern char D_88102F24[];
extern char D_88102F2C[];
extern Gfx D_80073450[];
extern u8 D_04010918[];
void func_8001BCB4(s32, s32, s32, s32, void*, s32, s32);
u8 GbSave_GetPortGame(s32 arg0);
void GbSave_DrawCartridgeIcon(s32, s32, u8, s32);
void Ui_DrawImageInStrips(u8*, s32, s32);
void Ui_DrawNumberZeroPadded(s32, s32, s32, s32);
/**
 * Draws the team source (GB cartridge port or registered slot number), なまえ (name) and trainer id.
 * Seen in play (2026-11-12): the 1P cartridge or 01 slot icon, なまえ サトシ and IDNo/12345.
 */
void Registration_DrawTrainerPanel(s32 x, s32 y, s32 textFlags, RegisteredTeam* team) {
    UNUSED s32 pad[3]; // FAKE: stack padding

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x88, 0x64, D_88102D7C);
    if (team->unk_00 == 0) {
        if (team->source == 0x20) {
            GbSave_DrawCartridgeIcon(x + 5, y + 4, team->pak, GbSave_GetPortGame(team->pak));
        } else if (team->source == 0x10) {
            Ui_DrawImageInStrips(D_88102DB8, x + 4, y + 4);
            Font_BeginTranslucentTextRendering();
            Font_SetColorForFlags(textFlags);
            Font_SetActive(8, 0);
            Font_Printf(x + 0x1B, y + 0x1A, D_88102F24, team->slot + 1);
            Font_EndTexturedTextRendering();
        }
    }
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(0xFF, 0xC8, 0xC8, 0xFF);
    Font_SetActive(4, -1);
    Font_Printf(x + 4, y + 0x41, D_88102F2C);
    Font_SetColorForFlags(textFlags);
    Font_SetActive(4, 0);
    Font_Printf(x + 0x38, y + 0x41, (char*)team->name);
    Font_EndTexturedTextRendering();
    if (team->trainerId != 0) {
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(x + 0x25, y + 0x56, 0x28, 0xA, D_04010918, 0x28, 0);
        Ui_DrawNumberZeroPadded(x + 0x51, y + 0x54, team->trainerId, 5);
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
void Registration_DrawMonCell(s32 x, s32 y, u8* mon, s32 iconId, s32 textFlags, RegistrationIconCache* cache) {
    UNUSED s32 pad[4]; // FAKE
    s32 slot;
    s32* p;

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x84, 0x32, D_88102D78[0]);
    if (mon != NULL) {
        Font_BeginTranslucentTextRendering();
        Font_SetColorForFlags(textFlags);
        Font_SetActive(4, 0);
        Font_Printf(x + 4, y + 4, mon + 0x30);
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80073450);
        func_8001BCB4(x + 0x2C, y + 0x19, 8, 0xA, D_04011A60, 8, 0);
        Ui_DrawNumber(x + 0x38, y + 0x17, mon[0x24], 3);
        slot = cache->base + iconId % cache->count;
        p = &cache->slots[slot];
        if (iconId != *p) {
            *p = iconId;
            func_8001833C(D_88103074, slot, mon, ((D_88102D78[0].c[1] << 3) & 0x7C0) | ((D_88102D78[0].c[2] >> 2) & 0x3E) | ((D_88102D78[0].c[0] << 8) & 0xF800) | 1);
        }
        if (cache) {} // FAKE: keeps cache live through the block above so the textFlags table address takes t1
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
 * Draws a cell with the Ditto placeholder icon (icon slot 0x18, which Registration_AllocScreen
 * renders from species 0x84 = Ditto).
 * Seen in play (2026-11-12): the pink Ditto placeholders in slot 01.
 * Seen in play (2026-11-14): also ran while the delete animation turned the Pokémon back into Ditto.
 */
void Registration_DrawDittoCell(s32 x, s32 y) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x84, 0x32, D_88102D78[0]);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    func_8001B884(x + 0x56, y + 6, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_88103074, 0x18), 0x28, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}

extern Gfx D_80073450[];
extern u8 D_04011A60[];
void func_8001BCB4(s32, s32, s32, s32, void*, s32, s32);
void Ui_DrawNumber(s32, s32, s32, s32);
/**
 * Draws a Pokémon cell of the Ditto transform row: nickname, level and the icon already in
 * `cache` (unlike Registration_DrawMonCell it does not render the icon again).
 * Seen in play (2026-11-14): drew ハナ L5, ヒノコ L5, カメ L5 in the 01 row as each Ditto transformed.
 */
void Registration_DrawRevealedMonCell(s32 x, s32 y, u8* mon, s32 iconId, s32 textFlags, s32* cache) {
    s32 idx;

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x84, 0x32, D_88102D78[0]);
    if (mon != NULL) {
        Font_BeginTranslucentTextRendering();
        Font_SetColorForFlags(textFlags);
        Font_SetActive(4, 0);
        Font_Printf(x + 4, y + 4, mon + 0x30);
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80073450);
        func_8001BCB4(x + 0x2C, y + 0x19, 8, 0xA, D_04011A60, 8, 0);
        Ui_DrawNumber(x + 0x38, y + 0x17, mon[0x24], 3);
        idx = iconId % cache[2] + cache[1];
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(x + 0x56, y + 6, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_88103074, idx), 0x28, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }
}

/**
 * Starts a timer at 0 that counts up to `steps` x 15 frames.
 * Seen in play (2026-11-14): はい on 「このポケモンをとうろくする？」 started it with steps = 3 (the party size); the
 * Ditto placeholders then turned into the party one every 15 frames.
 */
void Registration_InitTimer(RegistrationTimer* timer, s32 steps) {
    timer->frame = 0;
    timer->steps = steps;
    timer->framesPerStep = 0xF;
}

/**
 * Starts a timer at its end, `steps` x 15 frames, for counting down.
 * Seen in play (2026-11-14): はい on 「このポケモンをけす？」 started it with steps = 3 (frame 45); the registered
 * Pokémon then turned back into Ditto one every 15 frames.
 */
void Registration_InitTimerFull(RegistrationTimer* timer, s32 steps) {
    timer->steps = steps;
    timer->framesPerStep = 0xF;
    timer->frame = (s32) (steps * 0xF);
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Returns whether the timer has counted up to its end.
 * Seen in play (2026-11-14): returned nonzero when the last Ditto had transformed, which opened
 * 「メタモンのへんしんがおわりました。」.
 */
s32 Registration_IsTimerDone(s8 *timer)
{
 if (0) { }  // karodo
  return (*((s32 *) (((s8 *) timer) + 0))) >= ((*((s32 *) (((s8 *) timer) + 4))) * (*((s32 *) (((s8 *) timer) + 8)))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
}

/**
 * Returns whether the timer has counted down to 0.
 * Seen in play (2026-11-14): returned 0 while the delete countdown ran (frame 45 down to 0).
 */
s32 Registration_IsTimerZero(s32 *timer) {
    return *timer == 0;
}

/**
 * Advances the timer by one frame (up to its end) and returns whether it is done.
 * Seen in play (2026-11-14): ran every frame of the register animation.
 */
s32 Registration_StepTimer(RegistrationTimer* timer) {
    if (timer->frame < timer->framesPerStep * timer->steps) {
        timer->frame += 1;
    }
    return Registration_IsTimerDone(timer);
}

/**
 * Moves the timer back one frame (down to 0) and returns whether it reached 0.
 * Seen in play (2026-11-14): ran every frame of the delete animation, before
 * 「へんしん していた メタモンが もとの すがたに もどった。」.
 */
s32 Registration_StepTimerDown(s32* timer) {
    if (*timer > 0) {
        *timer -= 1;
    }
    return Registration_IsTimerZero(timer);
}

/**
 * Returns the timer's current frame.
 * Seen in play (2026-11-14): returned 45, 44, ... 0 while the delete animation ran.
 */
s32 Registration_GetTimer(s32 *timer) {
    return *timer;
}

extern Color88100D9C D_88102D80;
extern s32 D_88103098[];
/**
 * Draws one team row of the list (trainer panel and six cells); the ScrollList row callback.
 * `item` is the RegisteredTeam (NULL draws an empty row) and `row` its index.
 * Seen in play (2026-11-12): the six cells of a team row.
 */
void Registration_DrawTeamRow(s32 x, s32 y, s32 item, s32 row, s32 flags, s32 unused) {
    RegisteredTeam* box = (RegisteredTeam*)item;
    s32 pad[2]; // FAKE
    RegistrationIconCache cache;
    s32 pad2; // FAKE
    s32 i;
    u8* entry;
    s32 color;

    if (box != NULL) {
        Registration_DrawTrainerPanel(x, y, flags, box);
        cache.slots = D_88103098;
        cache.base = 0;
        cache.count = 24;
        cache.start = row * 6;
        entry = box->mons.rows;
        for (i = 0; i < box->mons.count; i++, entry += sizeof(TeamMonSlot)) {
            color = 0;
            if (flags & 2) {
                color = 0x10000;
            }
            Registration_DrawMonCell(x + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + y, entry + 4, row * 6 + i, color, &cache);
        }
        for (; i < 6; i++) {
            color = 0;
            if (flags & 2) {
                color = 0x10000;
            }
            Registration_DrawMonCell(x + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + y, NULL, row * 6 + i, color, &cache);
        }
    } else {
        Registration_FillTrainerPanel(x, y, D_88102D7C);
        Registration_FillTeamPanel(x, y, D_88102D78[0]);
    }
    Registration_DrawRowBorders(x, y, D_88102D80);
}

/**
 * Draws the team being registered or deleted: trainer panel and six cells. `revealTimer`
 * picks how many Pokémon show: 0 none (all Ditto), 1 all, otherwise (revealTimer - 2) / 15;
 * the rest of the team shows as Ditto (Registration_DrawDittoCell).
 * Seen in play (2026-11-14): the lower row (slot 01) during register, and the cursor row during delete.
 */
void Registration_DrawDittoTransformRow(s32 x, s32 y, RegisteredTeam* team, s32 row, s32 revealTimer) {
    s32 pad[2]; // FAKE
    RegistrationIconCache cache;
    s32 i;
    s32 n;
    u8* entry;

    entry = team->mons.rows;
    Registration_DrawTrainerPanel(x, y, 0, team);
    cache.slots = D_88103098;
    cache.base = 0;
    cache.count = 24;
    cache.start = row * 6;
    if (revealTimer == 0) {
        n = 0;
    } else if (revealTimer == 1) {
        n = team->mons.count;
    } else {
        n = (revealTimer - 2) / 15;
        if (n >= team->mons.count) {
            n = team->mons.count;
        }
    }
    for (i = 0; i < n; i++, entry += 0x54) {
        Registration_DrawRevealedMonCell(x + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + y, entry + 4, row * 6 + i, 0, (s32*)&cache);
    }
    for (; i < team->mons.count; i++) {
        Registration_DrawDittoCell(x + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + y);
    }
    for (; i < 6; i++) {
        Registration_DrawMonCell(x + 0x88 + (i % 3) * 0x84, (i / 3) * 0x32 + y, NULL, i, 0, NULL);
    }
    Registration_DrawRowBorders(x, y, D_88102D80);
}

/**
 * Sets `count` entries of `slots` from `start` to -1, so every icon cache slot renders again.
 * Seen in play (2026-11-12) in とうろく: ran with D_88103098 (the icon cache slots), 0, 0x18 when a
 * team list opened.
 */
void Registration_ClearIconCacheSlots(s32* slots, s32 start, s32 count) {
    s32 end;

    end = start + count;
    for (; start < end; start++) {
        slots[start] = -1;
    }
}

/**
 * Sets the team list mode and its first state: 0 register, 1 view, 2 delete.
 * Seen in play (2026-11-14): ran with 0 for ポケモンを とうろくする, 1 for みる and 2 for けす.
 */
void Registration_SetListMode(RegistrationTeamList* list, s32 mode) {
    list->mode = mode;
    switch (mode) {                                 /* irregular */
    case 0:
        list->state = 0;
        return;
    case 1:
        list->state = 1;
        return;
    case 2:
        list->state = 2;
        return;
    }
}

extern M2C_UNK D_88102D84;
extern s32 D_88103098[];
M2C_UNK ScrollList_Init();
/**
 * Sets up the team list window (544x344) in `mode` (0 register, 1 view, 2 delete).
 * Seen in play (2026-11-12): opened the team list.
 */
void Registration_InitTeamList(RegistrationTeamList* list, s32 x, s32 y, s8 *teams, s32 mode) {
    Window_SetRect(&list->window, x, y, 0x220, 0x158);
    list->window.animTimer = 0;
    list->window.title = 0;
    list->window.state = 0;
    list->window.frame.style = 0x801;
    Registration_SetListMode(list, mode);
    list->window.title = ((s32 *)&D_88102D84)[list->mode];
    list->teams = teams;
    ScrollList_Init(&list->list, teams, &list->itemFlags, 3, Registration_DrawTeamRow, 0x214, 0x64);
    list->list.options |= 0x10000;
    list->unk_00 = 0;
    Registration_ClearIconCacheSlots(D_88103098, 0, 0x18);
}


/**
 * Draws the team row under the list cursor at the top of the list window.
 * Seen in play (2026-11-14): the 1P party row above 「このポケモンをとうろくする？」.
 */
void Registration_DrawCursorTeamRow(RegistrationTeamList* list) {
    s32 index = list->list.cursor;
    s32* entry = &((s32*)list->list.items->rows)[index];

    Registration_DrawTeamRow(list->window.frame.x + 6, list->window.frame.y + 6, *entry, index, 0, 0);
}

void func_800189C0(s32, s32);
void BgStage_DrawFrame(void);
void ScrollList_DrawItems(void*, s32, s32, s32, s32);
/**
 * Draws the team list window for its current state.
 * Seen in play (2026-11-12): the ポケモンを とうろくする list window.
 */
void Registration_DrawTeamList(RegistrationTeamList* list) {
    func_800189C0(D_88103074, 0);
    BgStage_DrawFrame();
    if (func_8002AE6C(&list->window) == 0) {
        switch (list->state) {
            case 0:
            case 1:
            case 2:
                ScrollList_DrawItems(&list->list, list->window.frame.x + 6, list->window.frame.y + 0x16, 0xFFFF, 0);
                break;
            case 3:
                Registration_DrawCursorTeamRow(list);
                Registration_FillRowBackground(list->window.frame.x + 6, list->window.frame.y + 0x6A, 0x84);
                Registration_DrawDittoTransformRow(list->window.frame.x + 6, list->window.frame.y + 0xEE, &list->selectedTeam,
                              list->list.cursor, 0);
                Registration_DrawConfirmWindow(&list->confirmWindow);
                break;
            case 4:
                Registration_DrawCursorTeamRow(list);
                Registration_FillRowBackground(list->window.frame.x + 6, list->window.frame.y + 0x6A, 0x84);
                Registration_DrawDittoTransformRow(list->window.frame.x + 6, list->window.frame.y + 0xEE, &list->selectedTeam,
                              list->list.cursor, Registration_GetTimer((s32*)(&list->timer)) + 0x10);
                break;
            case 5:
                Registration_DrawCursorTeamRow(list);
                Registration_FillRowBackground(list->window.frame.x + 6, list->window.frame.y + 0x6A, 0x84);
                Registration_DrawDittoTransformRow(list->window.frame.x + 6, list->window.frame.y + 0xEE, &list->selectedTeam,
                              list->list.cursor, 1);
                Registration_DrawMessageWindow(&list->messageWindow);
                break;
            case 6:
                Registration_DrawDittoTransformRow(list->window.frame.x + 6, list->window.frame.y + 6, &list->selectedTeam,
                              list->list.cursor, 1);
                Registration_FillRowBackground(list->window.frame.x + 6, list->window.frame.y + 0x6A, 0xE8);
                Registration_DrawConfirmWindow(&list->confirmWindow);
                break;
            case 7:
                Registration_DrawDittoTransformRow(list->window.frame.x + 6, list->window.frame.y + 6, &list->selectedTeam,
                              list->list.cursor, Registration_GetTimer((s32*)(&list->timer)) + 2);
                Registration_FillRowBackground(list->window.frame.x + 6, list->window.frame.y + 0x6A, 0xE8);
                break;
            case 8:
                Registration_DrawDittoTransformRow(list->window.frame.x + 6, list->window.frame.y + 6, &list->selectedTeam,
                              list->list.cursor, 0);
                Registration_FillRowBackground(list->window.frame.x + 6, list->window.frame.y + 0x6A, 0xE8);
                Registration_DrawMessageWindow(&list->messageWindow);
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
s32 Registration_UpdateTeamList(RegistrationTeamList* list) {
    s32 ret = 0;
    s32 res;

    switch (list->state) {
        case 0:
            if (ScrollList_UpdateCursor(&list->list) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (res == 1) {
                    func_8003F6AC(2);
                    list->state = 3;
                    Registration_InitConfirmWindow(&list->confirmWindow, list->window.frame.x + 0x56, list->window.frame.y + 0x79, (s32)D_88102F34);
                    list->selectedTeam = *((RegisteredTeam**)list->list.items->rows)[list->list.cursor];
                    list->selectedTeam.source = 0x10;
                    list->selectedTeam.slot = Registration_FindFreeSlot();
                }
            }
            break;
        case 1:
            if ((ScrollList_UpdateCursor(&list->list) == 0) && (func_8002BC14(D_800603C0) == -1)) {
                func_8003F6AC(3);
                ret = -1;
            }
            break;
        case 2:
            if (ScrollList_UpdateCursor(&list->list) == 0) {
                res = func_8002BC14(D_800603C0);
                if (res == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                    Registration_WriteAllTeams(list->teams);
                } else if (res == 1) {
                    func_8003F6AC(2);
                    list->selectedTeam = *((RegisteredTeam**)list->list.items->rows)[list->list.cursor];
                    Registration_InitConfirmWindow(&list->confirmWindow, list->window.frame.x + 0x56, list->window.frame.y + 0x79, (s32)D_88102F54);
                    list->confirmWindow.choice.cursor = 1;
                    list->state = 6;
                }
            }
            break;
        case 3:
            res = Registration_UpdateConfirmWindow((s32)(&list->confirmWindow));
            if (res == -1) {
                func_8003F6AC(3);
                list->state = 0;
            } else if (res == 1) {
                func_8003F6AC(2);
                Registration_WriteTeam(((RegisteredTeam**)list->list.items->rows)[list->list.cursor], Registration_FindFreeSlot());
                Registration_InitTimer(&list->timer, list->selectedTeam.mons.count);
                list->state = 4;
            }
            break;
        case 4:
            if (list->timer.frame % 15 == 0) {
                Audio_PlayMoveSound(0x90, 1, 0);
            }
            if (Registration_StepTimer(&list->timer) != 0) {
                func_8003F6AC(0x1E);
                Registration_InitMessageWindow(&list->messageWindow, list->window.frame.x + 0x58, list->window.frame.y + 0x78, (s32)D_88102F6C);
                list->state = 5;
            }
            break;
        case 5:
            res = Registration_UpdateMessageWindow((s32)(&list->messageWindow));
            if ((res == -1) || (res == 1)) {
                func_8003F6AC(2);
                ret = -1;
            }
            break;
        case 6:
            res = Registration_UpdateConfirmWindow((s32)(&list->confirmWindow));
            if (res == -1) {
                func_8003F6AC(3);
                list->state = 2;
            } else if (res == 1) {
                func_8003F6AC(2);
                Registration_InitTimerFull(&list->timer, list->selectedTeam.mons.count);
                list->state = 7;
            }
            break;
        case 7:
            if (list->timer.frame % 15 == 0) {
                Audio_PlayMoveSound(0x90, 1, 0);
            }
            if (Registration_StepTimerDown((s32*)(&list->timer)) != 0) {
                func_8003F6AC(0x1F);
                func_80027868(list->teams, list->list.cursor);
                Registration_WriteAllTeams(list->teams);
                Registration_InitMessageWindow(&list->messageWindow, list->window.frame.x + 0x58, list->window.frame.y + 0x78, (s32)D_88102FC8);
                list->state = 8;
            }
            break;
        case 8:
            res = Registration_UpdateMessageWindow((s32)(&list->messageWindow));
            if ((res == -1) || (res == 1)) {
                func_8003F6AC(2);
                ret = -1;
            }
            break;
    }
    return ret;
}

/**
 * Fills `pointers` with one pointer per RegisteredTeam (0x220 bytes) in `table` and copies the count.
 * FreeBattle_BuildTeamPointers is the same routine with a record size of 0x214.
 * Seen in play (2026-11-14): ran each time a team list opened (register, view, delete).
 */
void Registration_BuildTeamPointers(s32* pointers, s32* table) {
    s32 value = table[0];
    s32* out = (s32*)pointers[0];
    s32 i = 0;

    if (table[2] > 0) {
        do {
            *out = value;
            i += 1;
            value += 0x220;
            out += 1;
        } while (i < table[2]);
    }
    pointers[2] = table[2];
}

void func_80027410(void*, void*, s32, s32, s32);
void func_80027804(void*, void*, s32, s32);

/**
 * Loads the registered teams and opens the list in view mode.
 * Seen in play (2026-11-12) in とうろく: とうろくした ポケモンをみる ran this and showed the registered team (slot
 * 01: ハナ, ヒノコ, カメ).
 */
void Registration_OpenViewList(RegistrationScreen* screen) {
    func_80027410(&screen->teamTable, screen->teamBuffer, sizeof(RegisteredTeam), 0x10, 0);
    Registration_LoadRegisteredTeams(&screen->teamTable);
    func_80027804(&screen->teamPointerList, screen->teamPointers, 0x10, 0);
    Registration_BuildTeamPointers((s32*)&screen->teamPointerList, (s32*)&screen->teamTable);
    Registration_InitTeamList(&screen->teamList, 0x30, 0x5C, &screen->teamPointerList, 1);
}

void func_80027410(void*, void*, s32, s32, s32);
void func_80027804(void*, void*, s32, s32);

/**
 * Loads the registered teams and opens the list in delete mode.
 * Seen in play (2026-11-12) in とうろく: とうろくした ポケモンをけす ran this and showed the same list with
 * 「このポケモンをけす？」 on A.
 */
void Registration_OpenDeleteList(RegistrationScreen* screen) {
    func_80027410(&screen->teamTable, screen->teamBuffer, sizeof(RegisteredTeam), 0x10, 0);
    Registration_LoadRegisteredTeams(&screen->teamTable);
    func_80027804(&screen->teamPointerList, screen->teamPointers, 0x10, 0);
    Registration_BuildTeamPointers((s32*)&screen->teamPointerList, (s32*)&screen->teamTable);
    Registration_InitTeamList(&screen->teamList, 0x30, 0x5C, &screen->teamPointerList, 2);
}

void func_80027410(void*, void*, s32, s32, s32);
void func_80027804(void*, void*, s32, s32);

/**
 * Loads the Game Boy teams and opens the list in register mode.
 * Seen in play (2026-11-12): ポケモンを とうろくする loaded the cartridge party and opened the list.
 */
void Registration_OpenRegisterList(RegistrationScreen* screen) {
    func_80027410(&screen->teamTable, screen->teamBuffer, sizeof(RegisteredTeam), 4, 0);
    Registration_LoadGbTeams(&screen->teamTable);
    func_80027804(&screen->teamPointerList, screen->teamPointers, 4, 0);
    Registration_BuildTeamPointers((s32*)&screen->teamPointerList, (s32*)&screen->teamTable);
    Registration_InitTeamList(&screen->teamList, 0x30, 0x5C, &screen->teamPointerList, 0);
}

s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);
extern M2C_UNK D_88102D84;
extern M2C_UNK D_88102D90;
extern M2C_UNK D_88103000;
extern s32 D_88103078;
extern M2C_UNK D_88103080;

/**
 * Reads which Game Boy cartridge is selected (D_88103078, -1 for none) and its summary, then
 * opens the とうろく menu (state 0).
 * Seen in play (2026-11-14): ran once when the とうろく screen loaded, with the screen from Registration_AllocScreen.
 */
void Registration_InitScreen(RegistrationScreen* screen) {
    D_88103078 = func_80025BD8();
    if (D_88103078 != -1) {
        func_80027FF8(&D_88103080, D_88103078);
    }
    Registration_InitMainMenu(&screen->mainMenu, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3, &D_88102D90, 3, &D_88103000);
    screen->state = 0;
}

void BgStage_DrawFrame(void);
void Ui_DrawTintedScreenBackground(s32, s32, s32, s32, s32);
extern u8 D_88102D70[];
/**
 * Draws the registration screen for its current state.
 * Seen in play (2026-11-12): drew the とうろく screen every frame.
 */
M2C_UNK Registration_DrawScreen(RegistrationScreen* screen) {
    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, D_88102D70[0], D_88102D70[1], D_88102D70[2]);
    switch (screen->state) {
        case 0:
            Registration_DrawMainMenu(&screen->mainMenu, 2);
            break;
        case 1:
            Registration_DrawTeamList(&screen->teamList);
            break;
    }
}

extern M2C_UNK D_88102D84;
extern M2C_UNK D_88102D90;
extern M2C_UNK D_8810300C;

/**
 * Runs the registration screen's state machine for one frame and returns 1 when B leaves the
 * menu. State 0 is the menu: choice 1 opens the register list, 2 the view list, 3 the delete
 * list. State 1 is a team list, which goes back to the menu when it returns -1.
 * Seen in play (2026-11-12): ran the とうろく screen.
 */
s32 Registration_UpdateScreen(RegistrationScreen* screen) {
    s32 done;
    s32 temp_v0;
    s32 choice;

    done = 0;
    temp_v0 = screen->state;
    switch (temp_v0) {
    case 0:
        choice = Registration_UpdateMainMenu(&screen->mainMenu);
        if (choice == -1) {
            done = 1;
        } else if (choice == 1) {
            Registration_OpenRegisterList(screen);
            screen->state = 1;
        } else if (choice == 2) {
            Registration_OpenViewList(screen);
            screen->state = 1;
        } else if (choice == 3) {
            Registration_OpenDeleteList(screen);
            screen->state = 1;
        }
        break;
    case 1:
        if (Registration_UpdateTeamList(&screen->teamList) == -1) {
            Registration_InitMainMenu(&screen->mainMenu, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3, &D_88102D90, 3, &D_8810300C);
            screen->state = 0;
        }
        break;
    }
    return done;
}

s32 func_80002D98(s32);
extern s32 D_88103074;
extern RegistrationScreen* D_881030F8;

/**
 * Allocates the RegistrationScreen (0x26B4 bytes) into D_881030F8, initialises it and renders the
 * Ditto placeholder icon (species 0x84) into icon slot 0x18.
 * Matching note: the call result is stored straight into D_881030F8 and the global is read back
 * for the next call; going through a local gives a different store sequence.
 * Seen in play (2026-11-14): ran once when the とうろく screen loaded.
 */
void Registration_AllocScreen(void) {
    D_881030F8 = (RegistrationScreen*)func_80002D98(sizeof(RegistrationScreen));
    Registration_InitScreen(D_881030F8);
    func_80018234(D_88103074, 0x18, 0x84, 0xF800);
}

typedef struct Col88102A2C { u8 r, g, b, a; } Col88102A2C;
extern s32 D_88102DCC;
extern s32 D_88102DD0;
/* Second name for D_88102DCC; see PartyScreen_FadeFrame in party_summary/mon_summary.c. */
extern s32 D_88102DCC_2;
extern M2C_UNK D_88103018;
void func_800189C0(s32, s32);
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32);
void func_8002C8D8(Col88102A2C*, Col88102A2C, f32);
/**
 * Draws the screen fade: the background tint fades in over 8 frames, and the second run fades it
 * out. Always returns 0, so BgStage_RunUntilCondition runs it for its full 8 frames.
 * Seen in play (2026-11-13) ran on the frames the registration screen faded in from the main menu.
 * Seen in play (2026-11-14): also ran when B left for the main menu.
 */
s32 Registration_UpdateFade(s32 fadeMode) {
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
 * One frame of the registration screen: reads input, draws and updates. It is declared void, but
 * Registration_UpdateScreen's result is left in v0, so BgStage_RunUntilCondition stops once B
 * leaves the menu.
 * Seen in play (2026-11-12): ran every frame of the とうろく screen.
 */
void Registration_RunFrame(s32 fadeMode) {
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
 * Seen in play (2026-11-14): breakpoint hit when B left for the main menu.
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
 * Entry point of the とうろく (registration) fragment: pushes the 'REGS' pool, loads the font, icons
 * and segments, fades in, runs the screen until B, fades out and loads the main menu back.
 * Its arguments are not used. Returns 0x8040.
 * Seen in play (2026-11-14): breakpoint hit when はい on the main menu's 「ポケモンとうろく」 prompt loaded the fragment.
 */
s32 Registration_Init(s32 unused0, s32 unused1) {
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
