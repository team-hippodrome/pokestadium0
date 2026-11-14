/* Stadium Zero fragment015_238BD0. */

#include "global.h"
#include "m2c_macros.h"
#include "lab_pc.h"
#include "asset_archive.h"
#include "memory_main.h"
#include "pokemon_stats.h"

M2C_UNK func_80023268(s32, u8, M2C_UNK);            /* extern */
extern s32 D_89019108;

/**
 * Marks every species in a Game Boy box as seen, owned and held in the cartridge's
 * Pokédex (func_80023268 with 3), after the box is written back.
 * Seen in play (2026-11-14): ran in PcBox_SaveChanges on レポートしてやめる after a box move; the same pass
 * in PcSort_MarkListInPokedex set bits that had been cleared in RAM.
 */
void PcBox_MarkBoxInPokedex(PcBoxStorage* box) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = (u8*)box;
    var_s1 = 0;
    if (box->count > 0) {
        do {
            func_80023268(D_89019108, *var_s0, 3);
            var_s1 += 1;
            var_s0 += 0x50;
        } while (var_s1 < box->count);
    }
}

/** Writes entries to a box of the Lab PC through a deck handle. */
void LabPC_WriteBoxEntries(s32 deckType, s32 port, s32 index, PcBoxStorage* box) {
    DeckHandle* sp1C = Deck_Open(deckType, port, index, 1);

    Deck_WriteEntries((u8*)box, box->count, sp1C);

    if ((deckType == 0x10) || (deckType == 0x11) || (deckType == 0x12) || (deckType == 0x13)) {
        Deck_CloseAndFlushBox(sp1C);
    } else {
        Deck_CloseAndFlush(sp1C);
    }
}

s32 func_8002207C(s32);
void func_80022118(s32);
void func_80022188(s32);
void func_800230C4(s32);
void func_800243B8(void);
void func_8002D7D4(s32);
void PcBox_DrawScreen(PcBoxScreen* arg0);

/**
 * Writes the changed GB boxes (deck 0x21, then PcBox_MarkBoxInPokedex) and 64 boxes
 * (deck 0x11) back and flushes the saves.
 * Seen in play (2026-11-14): レポートしてやめる after moving GBのボックス1 to 64のボックス1 wrote deck 0x21
 * box 0 and deck 0x11 box 0.
 */
void PcBox_SaveChanges(PcBoxScreen* screen) {
    s32 any;
    s32 i;
    s32 any2;

    any2 = 0;
    any = 0;

    for (i = 0; i < 8; i++) {
        if (screen->gbBoxEntries[i].dirty != 0) {
            any = 1;
            break;
        }
    }
    if (any != 0) {
        func_80022118(D_89019108);
    }
    for (i = 0; i < 8; i++) {
        if (screen->gbBoxEntries[i].dirty != 0) {
            LabPC_WriteBoxEntries(0x21, D_89019108, i, screen->gbBoxEntries[i].box);
            PcBox_MarkBoxInPokedex(screen->gbBoxEntries[i].box);
        }
    }
    for (i = 0; i < 4; i++) {
        if (screen->stadiumBoxEntries[i].dirty != 0) {
            LabPC_WriteBoxEntries(0x11, 0, i, screen->stadiumBoxEntries[i].box);
            any2 = 1;
        }
    }
    if (any != 0) {
        func_800230C4(D_89019108);
        if (func_8002207C(D_89019108) == 0) {
            func_8002D7D4(D_89019108);
            PcBox_DrawScreen(screen);
        }
        func_80022188(D_89019108);
    }
    if (any2 != 0) {
        func_800243B8();
    }
}

/**
 * Opens deck (`arg0`, `arg1`, `arg2`), reads `arg4` entries into `arg3`, closes it and returns the read count.
 * Seen in play (2026-11-12): read the GB and 64 boxes for ボックスのそうさ.
 */
s32 PcBox_ReadDeck(s32 deckType, s32 port, s32 index, s8* out, s32 max) {
    s32 sp1C;
    DeckHandle* sp18;

    sp18 = Deck_Open(deckType, port, index, 0);
    sp1C = Deck_ReadEntries((u8*)out, max, sp18);
    Deck_CloseAndFlush(sp18);
    return sp1C;
}

s32 PcBox_ReadDeck(M2C_UNK, M2C_UNK, s32, s8 *, s32); /* extern */
/**
 * Reads `count` boxes of deck `deckType` into consecutive 0x964-byte box buffers
 * (30 Pokémon each, the read count stored after them).
 * Seen in play (2026-11-14): ボックスを いどうする read the 8 GB boxes (deck 0x21) and the 4 64 boxes (0x11).
 */
void PcBox_ReadBoxes(s8 *boxes, M2C_UNK deckType, M2C_UNK port, s32 count)
{
  s32 temp_v0;
  s32 *new_var2; // FAKE: permuter temp
  int new_var; // FAKE: permuter temp
  s32 var_s0;
  boxes = boxes; // FAKE: self-assignment
  new_var = 0;
  new_var = count > new_var;
  var_s0 = 0;
  if (new_var)
  {
    do
    {
      temp_v0 = PcBox_ReadDeck(deckType, port, var_s0, boxes, 0x1E);
      var_s0 += 1;
      boxes += 0x964;
      new_var2 = (s32 *) (((s8 *) boxes) + (-4));
      *new_var2 = temp_v0;
    }
    while (var_s0 != count);
  }
}


/**
 * Returns 1 when every box in the table holds Pokémon (no empty box to move into).
 * Seen in play (2026-11-14): ran for the destination side of 64へボックスをいどうする and GBへボックスをいどうする.
 */
s32 LabPC_NoEmptyBoxAvailable(ByteMatrix* table) {
    s32 i;
    LabPCBoxEntry* var_a0 = (LabPCBoxEntry*)table->rows;

    for (i = 0; i < table->count; i++, var_a0++) {
        if (var_a0->box->count == 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * Seen in play (2026-11-13) in せいとん > ボックスを いどうする, pressing A with every GB and 64 box at 0/30 ran
 * it once, and the screen showed 「いどうする ボックスが ありません」.
 */
s32 LabPC_AllBoxesEmpty(ByteMatrix* table) {
    s32 i;
    LabPCBoxEntry* var_a0 = (LabPCBoxEntry*)table->rows;

    for (i = 0; i < table->count; i++, var_a0++) {
        if (var_a0->box->count > 0) {
            return 0;
        }
    }

    return 1;
}

void Window_SetRect(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void Window_InitLabeled(void* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5);
M2C_UNK func_8000B2F4(s32);
extern s32 D_800603C0;
extern u8 D_8900A870[];
extern char D_89018E60[];
extern char D_89018E68[];
/**
 * Sets up the Pokémon status window (430x292): nickname, LV, HP, types, stats, moves and
 * the animated model. With a `prompt` it also shows that question with はい/いいえ buttons.
 * Seen in play (2026-11-14): ポケモンをみる (no prompt) and ポケモンをにがす (「ほんとうにいいの？」) in
 * ポケモンのせいり, and A on a Pokémon in ボックスのなかをみる.
 */
void PcBox_InitMonStatusWindow(PcBoxConfirmWindow* win, s32 x, s32 y, s32 mon, s32 prompt, s32 controller, u16* renderer) {
    Window_SetRect((s8*)&win->window, x, y, 0x1AE, 0x124);
    win->window.animTimer = 0;
    win->window.title = NULL;
    win->window.state = 0;
    win->window.frame.style = 0x1001;
    Window_InitLabeled((s8*)&win->yesButton, win->window.frame.x + 0x10A, win->window.frame.y + 0x100, 0x48, *(Color_RGBA8 *)D_8900A870, D_89018E60);
    win->yesButton.labelX = 0xA;
    win->yesButton.unk_34 = 0xC;
    Window_InitLabeled((s8*)&win->noButton, win->window.frame.x + 0x15A, win->window.frame.y + 0x100, 0x48, *(Color_RGBA8 *)D_8900A870, D_89018E68);
    win->choice.count = 2;
    win->choice.cursor = 0;
    win->choice.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    win->choice.controller = (Controller*)controller;
    func_8000B2F4(controller);
    win->title = (char*)prompt;
    win->mon = (BattleMon*)mon;
    win->animLoaded = 0;
    win->anim = renderer;
    if (prompt != 0) {
        *win->anim &= ~2;
        *win->anim &= ~4;
    } else {
        *win->anim |= 2;
        *win->anim |= 4;
    }
}

typedef struct Color890075E0 {
    u8 r, g, b, a;
} Color890075E0;
typedef struct Entry80066AD8 {
    const char* str;
    Color890075E0 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 Pokemon_GetTypeIndex(s32, s32);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001ABBC(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A944(s32, s32, const char*, ...);

typedef struct Entry8006A9D4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry8006A9D4; // size = 0xC
extern Entry8006A9D4 D_8006A9D4[];
extern M2C_UNK D_800734A8;
extern char D_89018E70[];
u32 func_800566BC(const char*);

/**
 * Draws a move name in its type color, or the empty label for -2.
 * Seen in play (2026-11-12) in せいとん: drew ハナ's moves たいあたり and なきごえ beside its stats in ポケモンのせいり.
 */
void PcBox_DrawMoveName(s32 x, s32 y, s32 move, s32 centered) {
    Entry8006A9D4* entry;
    const char* str;
    Color890075E0* c;

    func_8001A384(8, 0);
    if (move == -2) {
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        str = D_89018E70;
    } else {
        entry = &D_8006A9D4[move];
        c = &D_80066AD8[entry->type].color;
        func_8001AA9C(c->r, c->g, c->b, c->a);
        str = entry->name;
    }
    if (centered != 0) {
        x = x - (func_800566BC(str) >> 1) * 20 + 0x8C;
    }
    func_8001A944(x, y, str);
}


/**
 * Draws the name of the species' type 1 or 2 in its type color; nothing for a missing type 2.
 * Seen in play (2026-11-13) in the せいとん > ポケモンをにがす confirm it drew くさ and どく for フシギダネ, and ほのお
 * with no type 2 for ヒトカゲ.
 */
void PcBox_DrawTypeName(s32 x, s32 y, s32 mon, s32 typeSlot) {
    Color890075E0 c;
    s32 idx = Pokemon_GetTypeIndex(mon, typeSlot);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(8, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(x, y, D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

typedef struct Slot89007678 {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 centered;
    /* 0x0C */ s32 iconX;
    /* 0x10 */ s32 icon;
} Slot89007678; // size = 0x14
extern Slot89007678 D_8900A884[];
extern u8 D_8007356C[];
extern Gfx D_80060270[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern Color_RGBA8 D_8900A874;
extern Color_RGBA8 D_8900A878;
extern Color_RGBA8 D_8900A5BC;
extern Color_RGBA8 D_8900A87C;
extern Color_RGBA8 D_8900A880;
extern char D_89018E80[];
extern char D_89018E84[];
extern char D_89018E88[];
extern char D_89018E8C[];
extern char D_89018E90[];
extern char D_89018E9C[];
extern char D_89018EA8[];
extern char D_89018EB4[];
extern char D_89018EC0[];
extern char D_89018ECC[];
extern char D_89018ED8[];
extern char D_89018EDC[];
extern char D_89018EE0[];
extern char D_89018EE4[];
void BgStage_DrawFrame(void);
void func_80019008(s32, BattleMon*, s32);
u8* func_800196F8(s32);
void func_8001AAE4(u8, u8, u8, u8);
void func_8001ABE8(void);
void func_8001AC3C(void);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawTexturedDivider(s32, s32, s32, u8*);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
s32 func_8002AE6C();
void Window_DrawLabeled(void*, s32);
s32 BattleMon_CountMoves(u8* arg0);
s32 BattleMon_GetMoveIndex(BattleMon*, s32);
/**
 * Draws a Pokemon's status window: LV, HP, Type 1/2, Attack, Defense, Speed, Special.
 * Seen in play (2026-11-13) in the せいとん > ポケモンをにがす confirm it drew フシギダネ's window (LV 10, HP 30,
 * Type 1 くさ, Type 2 どく, the four stats), and ヒトカゲ's.
 */
void PcBox_DrawMonStatusWindow(PcBoxConfirmWindow* win) {
    s32 y = win->window.frame.y + 6;
    s32 x = win->window.frame.x + 6;
    s32 count = BattleMon_CountMoves(win->mon);
    s32 i;
    s32 n;
    s32 row;
    u8* tex;

    if (func_8002AE6C(win) == 0) {
        Ui_DrawTexturedDivider(win->window.frame.x, win->window.frame.y + 0xF3, win->window.frame.width, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(x, y, win->window.frame.width - 0xC, 0x20, D_8900A874);
        func_80029028(x + 0x78, y + 0x20, win->window.frame.width - 0x84, 0x78, D_8900A878);
        func_80029028(x, y + 0xF4, win->window.frame.width - 0xC, 0x24, D_8900A5BC);
        Ui_FillRectPrimEnvColor(x, y + 0x98, win->window.frame.width - 0xC, 0x56, D_8900A87C, D_8900A880);
        func_8001AB6C();
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001A384(8, 0);
        func_8001ABE8();
        func_8001AAE4(0x7F, 0xA8, 0xFF, 0xFF);
        func_8001A944(x + 0xA, y + 5, (char*)win->mon->nickname);
        func_8001AC3C();
        func_8001A384(4, -1);
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        func_8001A944(x + 0x84, y + 9, D_89018E80);
        func_8001A944(x + 0x112, y + 9, D_89018E84);
        func_8001A384(8, 0);
        func_8001A944(x + 0xB2, y + 5, D_89018E88, win->mon->level);
        func_8001A944(x + 0x140, y + 5, D_89018E8C, win->mon->maxHp);
        func_8001A944(x + 0x88, y + 0x28, D_89018E90);
        if (Pokemon_GetTypeIndex((s32)win->mon, 1) != -1) {
            func_8001A944(x + 0x88, y + 0x64, D_89018E9C);
        }
        func_8001A944(x + 0x102, y + 0x28, D_89018EA8);
        func_8001A944(x + 0x102, y + 0x44, D_89018EB4);
        func_8001A944(x + 0x102, y + 0x60, D_89018EC0);
        func_8001A944(x + 0x102, y + 0x7C, D_89018ECC);
        func_8001A944(x + 0x15C, y + 0x28, D_89018ED8, win->mon->attack);
        func_8001A944(x + 0x15C, y + 0x44, D_89018EDC, win->mon->defense);
        func_8001A944(x + 0x15C, y + 0x60, D_89018EE0, win->mon->speed);
        func_8001A944(x + 0x15C, y + 0x7C, D_89018EE4, win->mon->special);
        for (i = 0; i < count; i++) {
            PcBox_DrawMoveName(D_8900A884[i].x + x, D_8900A884[i].y + y, BattleMon_GetMoveIndex(win->mon, i), D_8900A884[i].centered);
        }
        func_8001ABBC();
        PcBox_DrawTypeName(x + 0x9C, y + 0x40, (s32)win->mon, 0);
        PcBox_DrawTypeName(x + 0x9C, y + 0x7C, (s32)win->mon, 1);
        gSPDisplayList(gDisplayListHead++, D_80060290);
        for (i = 0; i < count; i++) {
            func_8001B884(D_8900A884[i].iconX + x, D_8900A884[i].y + y, 0x14, 0x14, (u8*)D_8900A884[i].icon, 0x14, 0x200000);
        }
        gSPDisplayList(gDisplayListHead++, D_80060398);
        if (win->title != NULL) {
            func_8001AB6C();
            func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
            func_8001A384(8, 0);
            func_8001A944(win->window.frame.x + 0xE, win->window.frame.y + 0x102, win->title);
            func_8001ABBC();
            Window_DrawLabeled((char*)&win->yesButton, (win->choice.cursor == 0) ? 2 : 0);
            Window_DrawLabeled((char*)&win->noButton, (win->choice.cursor == 1) ? 2 : 0);
        }
        if (win->animLoaded == 0) {
            win->animLoaded = 1;
            func_80019008((s32)win->anim, win->mon, 0x416D);
        }
        tex = func_800196F8((s32)win->anim);
        BgStage_DrawFrame();
        gSPDisplayList(gDisplayListHead++, D_80060290);
        gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
        for (row = 0; row < 0x78; row += n) {
            if (0x78 - row < 0x10) {
                n = 0x78 - row;
            } else {
                n = 0x10;
            }
            func_8001B884(x, y + row + 0x20, 0x78, n, tex, 0x80, 0x200000);
            tex += n << 8;
        }
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
}

s32 Ui_HandleHorizontalSelectionInput(void* arg0);
s32 Ui_GetSelectionDirection(void* arg0);

/**
 * Moves the Yes/No cursor. Returns -1 on cancel or No, 1 on Yes.
 * Seen in play (2026-11-13) in the せいとん > ポケモンをにがす confirm, D-Left moved the cursor from いいえ to はい;
 * A on いいえ canceled and A on はい released.
 */
s32 PcBox_UpdateConfirmCursor(PcBoxConfirmWindow* win) {
    s32 sp1C = 0;
    s32 dir;

    if (Ui_HandleHorizontalSelectionInput(&win->choice) == 0) {
        dir = Ui_GetSelectionDirection(win->choice.controller);
        if (dir == -1) {
            sp1C = -1;
        } else if (dir == 1) {
            if (win->choice.cursor == 1) {
                sp1C = -1;
            } else {
                sp1C = 1;
            }
        }
    }
    return sp1C;
}

extern Color_RGBA8 D_8900A5BC;
extern Color_RGBA8 D_8900A8D4;
extern Color_RGBA8 D_8900A8D8;
extern Gfx D_80060270[];
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern Gfx D_80073450[];
extern u8 D_04011A60[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void func_8001BCB4(s32, s32, s32, s32, u8*, s32, s32);
void Ui_DrawNumberUnpadded(s32, s32, u8);
void Font_SetColorForFlags(s32);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
s32 PokeIcon_GetImage(s8 *arg0, s32 arg1);
/**
 * Draws one cell of the box contents grid: the Pokémon's icon, L%d and nickname.
 * Seen in play (2026-11-14): ホ L6 and タ L4 in GBのボックス2 and 64のボックス1.
 */
void PcBox_DrawListCell(s32 x, s32 y, BattleMon* mon, s32 index, s32 flags, s32 renderer) {
    s32 pad[4]; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x + 1, y + 1, 0x58, 0x2E, D_8900A5BC);
    func_80029028(x + 1, y + 0x2F, 0x58, 0x12, D_8900A8D4);
    func_80029028(x, y, 0x5A, 1, D_8900A8D8);
    func_80029028(x, y + 0x41, 0x5A, 1, D_8900A8D8);
    func_80029028(x, y + 1, 1, 0x40, D_8900A8D8);
    func_80029028(x + 0x59, y + 1, 1, 0x40, D_8900A8D8);
    if (mon != NULL) {
        if (flags & 0x10) {
            Ui_FillRectHighlighted(x + 3, y + 3, 0x54, 0x2C, D_8900A5BC);
            Ui_FillRectHighlighted(x + 3, y + 0x2F, 0x54, 0x10, D_8900A8D4);
        }
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(x + 4, y + 0x24, 8, 0xA, D_04011A60, 8, 0);
        Ui_DrawNumberUnpadded(x + 0xE, y + 0x22, mon->level);
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(4, 0);
        func_8001A944(x + 5, y + 0x30, (char*)mon->nickname);
        func_8001ABBC();
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(x + 0x2C, y + 4, 0x28, 0x28, PokeIcon_GetImage(renderer, index), 0x28, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }
}

typedef struct Str8900806C { char s[13]; } Str8900806C;
char* func_8000A460(char*, const char*);
void func_80018168(s32);
void func_80027410(void*, s8*, s32, s32, s32);
void GridMenu_Init(void*, s8*, s8*, void*, s32, s32, s32);
extern char D_89018EE8[];
extern char D_89018EF0[];
extern char D_89018EF8[];
extern s8 D_890289E0[];
void PcBox_DrawListCell();
/**
 * Sets up the box contents window titled ＧＢ/６４のボックスN (`isStadium` picks the
 * prefix, `boxIndex` the digit) with a 6 x 5 icon grid of the box's Pokémon.
 * Seen in play (2026-11-14): ボックスのなかをみる opened 「64のボックス1」 and 「GBのボックス2」.
 */
void PcBox_InitListWindow(PcBoxListWindow* win, s32 x, s32 y, PcBoxStorage* box, s32 renderer, s32 isStadium, s32 boxIndex) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 i;
    u8* p;

    func_8000A460((char*)D_890289E0, (isStadium == 0) ? D_89018EE8 : D_89018EF0);
    *(Str8900806C*)(func_800566BC((char*)D_890289E0) + D_890289E0) = *(Str8900806C*)D_89018EF8;
    D_890289E0[func_800566BC((char*)D_890289E0) - 1] += boxIndex + 1;
    Window_SetRect((s8*)&win->window, x, y, 0x228, 0x156);
    win->window.animTimer = 0;
    win->window.state = 0;
    win->window.frame.style = 0x801;
    win->window.title = (char*)D_890289E0;
    func_80027410((s8*)&win->mons, (s8*)box, 0x50, 0x1E, box->count);
    GridMenu_Init((s8*)&win->menu, (s8*)&win->mons, (s8*)win->itemFlags, PcBox_DrawListCell, 6, 0x5A, 0x42);
    win->menu.options |= 0x10000;
    func_80018168(renderer);
    for (p = (u8*)box, i = 0; i < box->count; i++, p += 0x50) {
        Color_RGBA8 c = D_8900A5BC;

        func_8001833C((PokeIconRenderer*)renderer, i, (BattleMon*)p, GPACK_RGBA5551(c.r, c.g, c.b, 1));
    }
    win->iconRenderer = renderer;
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK func_800189C0(s32, M2C_UNK);                /* extern */
s32 func_8002AE6C();                                /* extern */
M2C_UNK GridMenu_DrawInlineItems(void*, s32, s32, s32, s32);  /* extern */

/**
 * Draws the box contents grid, refreshing the icons unless flag 0x10 is set (it is while the
 * status window is open). Seen in play (2026-11-14).
 */
void PcBox_DrawList(PcBoxListWindow* win, s32 flags) {
    if (func_8002AE6C() == 0) {
        if (!(flags & 0x10)) {
            func_800189C0(win->iconRenderer, 0);
            BgStage_DrawFrame();
        }
        GridMenu_DrawInlineItems((s8*)&win->menu, win->window.frame.x + 6, win->window.frame.y + 6, flags | 0xFFED, win->iconRenderer);
    }
}

s32 GridMenu_UpdateCursor(void*);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;
/**
 * Moves the box contents cursor. Returns -1 on cancel, the 1-based cell on confirm,
 * otherwise 0. Seen in play (2026-11-14): A on ホ opened its status window.
 */
s32 PcBox_UpdateListCursor(PcBoxListWindow* win) {
    s32 sp1C = 0;
    s32 dir;

    if (GridMenu_UpdateCursor(&win->menu) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = win->menu.cursor + 1;
        }
    }
    return sp1C;
}

extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawImageInStrips(void*, s32, s32);
extern Color_RGBA8 D_8900A8F8;
extern Color_RGBA8 D_8900A900;
extern Color_RGBA8 D_8900A8DC[];

extern Color_RGBA8 D_8900A8E8;
extern Color_RGBA8 D_8900A8F0;
extern char D_89018F08[];
extern u8 D_80073614[];
extern u8 D_04011AB8[];
extern Gfx D_80073450[];
void Ui_DrawNumber(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws one row of the GB cartridge column: ボックス%d, a Poké Ball icon when the box holds
 * Pokémon, and its %2d/30 count; empty boxes use the dim colors.
 * Seen in play (2026-11-14): the left column, ボックス１ 2/30 ... ボックス８ 0/30.
 */
void PcBox_DrawGbBoxRow(s32 x, s32 y, LabPCBoxEntry* entry, s32 index, s32 flags) {
    Color_RGBA8 color;
    s32 pad[2]; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y + 1, 0xCE, 0x1A, D_8900A8E8);
    func_80029028(x, y, 0xCE, 1, D_8900A8F0);
    func_80029028(x, y + 0x1B, 0xCE, 1, D_8900A8F0);
    if (flags & 0x18) {
        Ui_FillRectHighlighted(x + 3, y + 3, 0xC8, 0x16, D_8900A5BC);
    }
    func_8001AB6C();
    func_8001A384(8, 0);
    if (entry->box->count == 0) {
        color = D_8900A8DC[(flags & 2) ? 0 : 1];
    } else {
        color = ((Color_RGBA8*)&D_800734A8)[(flags & 2) ? 0 : 1];
    }
    if (flags & 1) {
        color.a = 0x4C;
    }
    func_8001AA9C(color.r, color.g, color.b, color.a);
    func_8001A944(x + 8, y + 4, D_89018F08, index + 1);
    func_8001ABBC();
    if (entry->box->count > 0) {
        Ui_DrawImageInStrips(D_80073614, x + 0x78, y + 4);
    }
    Ui_DrawNumber(x + 0x98, y + 8, entry->box->count, 2);
    Ui_DrawNumber(x + 0xB3, y + 8, 0x1E, 2);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001BCB4(x + 0xAA, y + 0xA, 8, 0xA, D_04011AB8, 8, 0);
}

extern char D_89018F14[];
extern char D_89018F20[];
extern u8 D_80073634[];

/**
 * Draws one row of the 64 cassette column: ボックス%d in the large font with its %2d/%2d
 * count and a Poké Ball icon when it holds Pokémon.
 * Seen in play (2026-11-14): the right column, ボックス１ 0/30 ... ボックス４ 0/30.
 */
void PcBox_DrawStadiumBoxRow(s32 x, s32 y, LabPCBoxEntry* entry, s32 index, s32 flags) {
    Color_RGBA8 color;
    s32 pad[11]; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y + 1, 0x104, 0x36, D_8900A8F8);
    func_80029028(x, y, 0x104, 1, D_8900A900);
    func_80029028(x, y + 0x37, 0x104, 1, D_8900A900);
    if (flags & 0x18) {
        Ui_FillRectHighlighted(x + 3, y + 3, 0xFE, 0x32, D_8900A5BC);
    }
    func_8001AB6C();
    func_8001A384(0x10, 0);
    if (entry->box->count == 0) {
        color = D_8900A8DC[(flags & 2) ? 0 : 1];
    } else {
        color = ((Color_RGBA8*)&D_800734A8)[(flags & 2) ? 0 : 1];
    }
    if (flags & 1) {
        color.a = 0x4C;
    }
    func_8001AA9C(color.r, color.g, color.b, color.a);
    func_8001A944(x + 8, y + 0x10, D_89018F14, index + 1);
    func_8001A384(4, -1);
    func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    func_8001A944(x + 0xB0, y + 0x14, D_89018F20, entry->box->count, 0x1E);
    func_8001ABBC();
    if (entry->box->count > 0) {
        Ui_DrawImageInStrips(D_80073634, x + 0x8C, y + 0x10);
    }
}

typedef struct ColorPair890088F8 {
    Color_RGBA8 prim;
    Color_RGBA8 env;
} ColorPair890088F8;
extern ColorPair890088F8 D_8900A904;
extern ColorPair890088F8 D_8900A90C;
extern s32 D_8900A914[];
extern u8* D_89017A80[];
extern u8 D_89017A98[];
extern char D_89018F28[];
extern char D_89018F3C[];
extern s32 D_89019114;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
s32 func_8002BC44(s32);
void Font_SetColorForFlags(s32);
/**
 * Draws ＧＢのカートリッジ (GB cartridge) or ６４のカセット (N64 cassette) for `kind`.
 * Seen in play (2026-11-12): GBのカートリッジ and 64のカセット.
 */
void PcBox_DrawStorageLabel(s32 x, s32 y, s32 flags, s32 kind) {
    ColorPair890088F8* c;

    if (flags & 2) {
        c = &D_8900A904;
    } else {
        c = &D_8900A90C;
    }
    Ui_FillRectPrimEnvColor(x, y, D_8900A914[kind], 0x2C, c->prim, c->env);
    gSPDisplayList(gDisplayListHead++, D_80073408);
    switch (kind) {
        case 0:
            func_8001B884(x + 1, y + 9, 0x18, 0x1A, D_89017A80[func_8002BC44(D_89019114)], 0x18, 0x200000);
            break;
        case 1:
            func_8001B884(x + 2, y + 9, 0x28, 0x1A, D_89017A98, 0x30, 0x200000);
            break;
    }
    gSPDisplayList(gDisplayListHead++, D_80073438);
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(8, 0);
    switch (kind) {
        case 0:
            Font_Printf(x + 0x19, y + 0xC, D_89018F28);
            break;
        case 1:
            Font_Printf(x + 0x2C, y + 0xC, D_89018F3C);
            break;
    }
    Font_EndTexturedTextRendering();
}

void Menu_Init(void* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern Color_RGBA8 D_8900A91C;
extern Color_RGBA8 D_8900A920;
extern Color_RGBA8 D_8900A580[];
extern u8 D_8900BFC0[];
extern u8 D_8900DAD0[];
extern u8 D_8900CD48[];
extern u8 D_8900E858[];
extern u8 D_8900F5E0[];
extern u8 D_89010368[];
extern char D_89018F4C[];
/**
 * Sets up the ボックスのそうさ (box operation) window and its parts.
 * Seen in play (2026-11-12): opened ボックスのそうさ.
 */
void PcBox_InitOperationWindow(PcBoxOperationWindow* win, s32 x, s32 y, ByteMatrix* gbBoxTable) {
    Window_SetRect(&win->window, x, y, 0x234, 0x172);
    win->window.animTimer = 0;
    win->window.state = 0;
    win->window.frame.style = 0x801;
    win->window.title = (char*)D_89018F4C;
    Window_SetRect(&win->footerFrame, win->window.frame.x + 6, win->window.frame.y + 0x12C, win->window.frame.width - 0xC, 0x40);
    win->footerFrame.style = 6;
    win->footerFrame.color = D_8900A91C;
    win->footerFrame.color2 = D_8900A920;
    func_8002B018(&win->backButton, x + 0xE4, y + 0xE, 0x36, 0x2A, 0x30, (s32)D_8900BFC0);
    win->backButton.selectedColor = D_8900A580[0];
    win->backButton.color = D_8900A580[1];
    win->backButton.highlightColor = D_8900A5BC;
    func_8002B018(&win->moveTo64Button, x + 0xE4, y + 0x3C, 0x36, 0x2A, 0x30, (s32)D_8900DAD0);
    win->moveTo64Button.selectedColor = D_8900A580[2];
    win->moveTo64Button.color = D_8900A580[3];
    win->moveTo64Button.highlightColor = D_8900A5BC;
    func_8002B018(&win->moveToGbButton, x + 0xE4, y + 0x6A, 0x36, 0x2A, 0x30, (s32)D_8900CD48);
    win->moveToGbButton.selectedColor = D_8900A580[2];
    win->moveToGbButton.color = D_8900A580[3];
    win->moveToGbButton.highlightColor = D_8900A5BC;
    func_8002B018(&win->reorderButton, x + 0xE4, y + 0x98, 0x36, 0x2A, 0x30, (s32)D_8900E858);
    win->reorderButton.selectedColor = D_8900A580[4];
    win->reorderButton.color = D_8900A580[5];
    win->reorderButton.highlightColor = D_8900A5BC;
    func_8002B018(&win->exchangeButton, x + 0xE4, y + 0xC6, 0x36, 0x2A, 0x30, (s32)D_8900F5E0);
    win->exchangeButton.selectedColor = D_8900A580[6];
    win->exchangeButton.color = D_8900A580[7];
    win->exchangeButton.highlightColor = D_8900A5BC;
    func_8002B018(&win->viewButton, x + 0xE4, y + 0xF4, 0x36, 0x2A, 0x30, (s32)D_89010368);
    win->viewButton.selectedColor = D_8900A580[8];
    win->viewButton.color = D_8900A580[9];
    win->viewButton.highlightColor = D_8900A5BC;
    win->operationCursor.count = 6;
    win->operationCursor.cursor = 0;
    win->operationCursor.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    Menu_Init(&win->gbBoxMenu, (s32)gbBoxTable, (s32)win->gbBoxFlags, (s32)PcBox_DrawGbBoxRow, 0xCE, 0x1C);
    win->gbBoxMenu.options |= 0x10000;
    Menu_Init(&win->stadiumBoxMenu, (s32)(gbBoxTable + 1), (s32)win->stadiumBoxFlags, (s32)PcBox_DrawStadiumBoxRow, 0x104, 0x38);
    win->stadiumBoxMenu.options |= 0x10000;
    win->state = 1;
}

extern s32 D_8900A924[];
extern s32 D_8900A93C[];
void LabItem_DrawTitleText(s32, s32, s32, s32);
/**
 * Draws the selected operation's caption while the operation column has the cursor.
 * Seen in play (2026-11-14): 「６４へボックスをいどうする」, 「ＧＢへボックスをいどうする」,
 * 「ボックスをならべかえる」 and 「ボックスのなかをみる」.
 */
void PcBox_DrawHelpText(PcBoxOperationWindow* win) {
    if (win->state == 1) {
        if (0) {}  // karodo
        LabItem_DrawTitleText(win->footerFrame.x + 0x58, win->footerFrame.y, D_8900A924[(0, win)->operationCursor.cursor], D_8900A93C[win->operationCursor.cursor]); // FAKE: comma expression
    }
}

void Window_DrawFrame(void*);
void Ui_DrawTexturedDivider(s32, s32, s32, u8*);
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
void Menu_DrawInlineItems(void*, s32, s32, s32, s32);
void TextBox_Draw(TextBox*);
extern u8 D_8007356C[];
extern u8 D_800735C4[];
/**
 * Draws the box operation window: frame, storage label and the two box lists.
 * Seen in play (2026-11-12): the ボックスのそうさ window with 「64へボックスをいどうする」.
 */
void PcBox_DrawOperationWindow(PcBoxOperationWindow* win) {
    s32 sel = 0x10;
    s32 flags[2];
    s32 pad[2]; // FAKE
    s32 a;
    s32 b;

    if (func_8002AE6C(&win->window) != 0) {
        return;
    }
    Window_DrawFrame(&win->footerFrame);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(win->window.frame.x + 6, win->window.frame.y + 6, win->window.frame.width - 0xC, 0xA, D_8900A5BC);
    func_80029028(win->window.frame.x + 6, win->window.frame.y + 0x11C, win->window.frame.width - 0xC, 0xA, D_8900A5BC);
    func_80029028(win->window.frame.x + 6, win->window.frame.y + 0x10, 0xA, 0x10C, D_8900A5BC);
    func_80029028(win->window.frame.x + win->window.frame.width - 0x10, win->window.frame.y + 0x10, 0xA, 0x10C, D_8900A5BC);
    func_80029028(win->window.frame.x + 0xDE, win->window.frame.y + 0x10, 0x42, 0x10C, D_8900A5BC);
    Ui_DrawTexturedDivider(win->window.frame.x, win->window.frame.y + 0x125, win->window.frame.width, D_8007356C);
    Ui_DrawTexturedFrameDecal(win->window.frame.x + 0xE, win->window.frame.y + 0xE, 0xD2, 0x110, D_800735C4);
    Ui_DrawTexturedFrameDecal(win->window.frame.x + 0x11E, win->window.frame.y + 0xE, 0x108, 0x110, D_800735C4);
    flags[1] = flags[0] = 0xFFED;
    switch (win->state) {
        case 1:
            sel = 2;
            break;
        case 2:
            flags[(win->operationCursor.cursor == 1) ? 1 : 0] |= 2;
            break;
        case 3:
        case 4:
            if (win->operationCursor.cursor == 1) {
                a = 1;
                b = 0;
            } else {
                a = 0;
                b = 1;
            }
            flags[a] |= 0x10;
            flags[b] |= 2;
            break;
        case 5:
            flags[0] = 0xFFEF;
            break;
        case 6:
            flags[(win->boxCursor.cursor < 8) ? 0 : 1] |= 2;
            break;
    }
    func_8002B054(&win->backButton, (win->operationCursor.cursor == 5) ? sel : 0);
    func_8002B054(&win->moveTo64Button, (win->operationCursor.cursor == 0) ? sel : 0);
    func_8002B054(&win->moveToGbButton, (win->operationCursor.cursor == 1) ? sel : 0);
    func_8002B054(&win->reorderButton, (win->operationCursor.cursor == 2) ? sel : 0);
    func_8002B054(&win->exchangeButton, (win->operationCursor.cursor == 3) ? sel : 0);
    func_8002B054(&win->viewButton, (win->operationCursor.cursor == 4) ? sel : 0);
    PcBox_DrawStorageLabel(win->window.frame.x + 0x10, win->window.frame.y + 0x10, 2, 0);
    PcBox_DrawStorageLabel(win->window.frame.x + 0x120, win->window.frame.y + 0x10, 2, 1);
    Menu_DrawInlineItems(&win->gbBoxMenu, win->window.frame.x + 0x10, win->window.frame.y + 0x3C, flags[0], 0);
    Menu_DrawInlineItems(&win->stadiumBoxMenu, win->window.frame.x + 0x120, win->window.frame.y + 0x3C, flags[1], 0);
    PcBox_DrawHelpText(win);
    if (win->state == 7) {
        TextBox_Draw(&win->textBox);
    }
}

s32 Menu_UpdateCursorSkipDisabled(void* arg0);

/**
 * Moves a box column cursor, skipping disabled rows. Returns -1 on cancel, 1 on confirm,
 * otherwise 0. Seen in play (2026-11-14): picking source and destination boxes.
 */
s32 PcBox_UpdateSimpleCursor(Menu* menu) {
    s32 sp1C = 0;
    s32 dir;

    if (Menu_UpdateCursorSkipDisabled(menu) == 0) {
        dir = Ui_GetSelectionDirection(gPlayer1Controller);
        if (dir == -1) {
            Audio_PlaySoundEffectById(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = 1;
        }
    }
    return sp1C;
}


/**
 * Swaps the boxes of the entries selected in sourceMenu and targetMenu and marks both
 * changed. The entry is `rows[cursor]` of the menu's item table, written
 * `cursor + *(LabPCBoxEntry**)menu->items` (rows is the first field) because a cast of
 * `items->rows` or the other operand order changes the load order.
 * Seen in play (2026-11-14): moved GBのボックス1 (2/30) into 64のボックス1 and back again with
 * GBへボックスをいどうする, and swapped GBのボックス2 with 64のボックス1 (operation 3).
 */
void PcBox_SwapSelectedEntries(PcBoxOperationWindow* win) {
    LabPCBoxEntry* a;
    LabPCBoxEntry* b;
    PcBoxStorage* tmp;

    a = win->sourceMenu->cursor + *(LabPCBoxEntry**)win->sourceMenu->items;
    b = win->targetMenu->cursor + *(LabPCBoxEntry**)win->targetMenu->items;
    tmp = b->box;
    b->box = a->box;
    a->dirty = 1;
    a->box = tmp;
    b->dirty = 1;
}

/**
 * Swaps two boxes of the same column (swapIndex and the cursor) and marks both changed.
 * Seen in play (2026-11-14) in ボックスをならべかえる: GBのボックス2's Pokémon (2/30) moved to GBのボックス1.
 */
void PcBox_SwapEntriesInList(PcBoxOperationWindow* win) {
    LabPCBoxEntry* a = win->swapIndex + *(LabPCBoxEntry**)win->sourceMenu->items;
    LabPCBoxEntry* b = win->sourceMenu->cursor + *(LabPCBoxEntry**)win->sourceMenu->items;
    PcBoxStorage* temp = b->box;

    b->box = a->box;
    a->dirty = 1;
    a->box = temp;
    b->dirty = 1;
}

s32 Menu_SkipDisabledForward(void*);
/**
 * Disables the rows of boxes with no Pokémon, then moves the cursor to the first enabled row
 * and returns Menu_SkipDisabledForward's result (negative when every box is empty). Seen in play (2026-11-14): only the boxes holding Pokémon stayed selectable as sources.
 */
s32 PcBox_DisableEmptyBoxes(Menu* menu) {
    s32 i;
    ByteMatrix* list = menu->items;
    s32 n = list->count;
    LabPCBoxEntry* e = (LabPCBoxEntry*)list->rows;

    for (i = 0; i < n; i++, e++) {
        if (e->box->count == 0) {
            menu->itemFlags[i] |= 1;
        }
    }
    menu->cursor = 0;
    return Menu_SkipDisabledForward(menu);
}


/**
 * Disables the rows of boxes that already hold Pokémon (the destination of a move must be
 * empty). Seen in play (2026-11-14): GBのボックス2 (2/30) was greyed out as a destination of GBへボックスをいどうする.
 */
void PcBox_DisableNonEmptyBoxes(Menu* menu) {
    s32 i;
    ByteMatrix* list = menu->items;
    s32 n = list->count;
    LabPCBoxEntry* e = (LabPCBoxEntry*)list->rows;

    for (i = 0; i < n; i++, e++) {
        if (e->box->count > 0) {
            menu->itemFlags[i] |= 1;
        }
    }
    menu->cursor = 0;
    Menu_SkipDisabledForward(menu);
}

/**
 * Sets the source and destination box columns (either may be NULL) and resets their cursors.
 * Seen in play (2026-11-14): GB then 64 for 64へボックスをいどうする, the reverse for GBへ.
 */
void PcBox_SetActiveLists(PcBoxOperationWindow* win, Menu* source, Menu* target) {
    if (source != NULL) {
        win->sourceMenu = source;
        source->cursor = 0;
    }
    if (target != NULL) {
        win->targetMenu = target;
        target->cursor = 0;
    }
}

s32 func_8002B204();
/**
 * Steps the ボックスのなかをみる cursor over all 12 boxes (GB 1-8, then 64 1-4) with the
 * D-pad, skipping disabled (empty) boxes, and sets sourceMenu to the column it lands in.
 * Returns nonzero when the cursor moved. Seen in play (2026-11-14): ran while D-Down moved between the
 * non-empty boxes; A then opened the box under the cursor.
 */
s32 PcBox_StepViewCursorSkipEmpty(PcBoxOperationWindow* win, s32 buttons) {
    s32 r;
    s32 idx;
    s32 pos;

    for (r = func_8002B204(&win->boxCursor, buttons); r != 0; r = func_8002B204(&win->boxCursor, buttons)) {
        pos = win->boxCursor.cursor;
        idx = pos - 8;
        if (pos < 8) {
            win->sourceMenu = &win->gbBoxMenu;
            idx = pos;
        } else {
            win->sourceMenu = &win->stadiumBoxMenu;
        }
        if (!(win->sourceMenu->itemFlags[idx] & 1)) {
            break;
        }
    }
    return r;
}

s32 func_8000B30C(void);
s32 func_8002B2B0(void*);
void TextBox_Init(TextBox*, char*, s32, s32, s32);
s32 Ui_CheckConfirmPressed(TextBox*);
void Menu_ClearItemFlags(void*);
extern void* D_8900A954[];
extern u8 D_8900A96C[];

/**
 * Runs the box operation window's state machine (pick, move, swap, warnings such as ボックスのあきがありません "no free space in the box").
 * Seen in play (2026-11-12): ran ボックスのそうさ.
 */
s32 PcBox_UpdateOperationWindow(PcBoxOperationWindow* win) {
    s32 ret = 0;
    s32 pad; // FAKE
    s32 next = 0;
    s32 back = 0;
    s32 pad2; // FAKE
    s32 r;
    Menu* list;
    LabPCBoxEntry* e;

    switch (win->state) {
        case 1:
            if (func_8002B2B0(&win->operationCursor) == 0) {
                r = func_8002BC14(D_800603C0);
                if (r == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (r == 1) {
                    switch ((u32)win->operationCursor.cursor) {
                        case 5:
                            func_8003F6AC(3);
                            ret = -1;
                            break;
                        case 0:
                            if (LabPC_AllBoxesEmpty(win->gbBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                win->state = 7;
                                TextBox_Init(&win->textBox, D_8900A954[win->operationCursor.cursor], 0, 1, 0);
                            } else if (LabPC_NoEmptyBoxAvailable(win->stadiumBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                win->state = 7;
                                TextBox_Init(&win->textBox, D_8900A96C, 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 2;
                                PcBox_SetActiveLists(win, &win->gbBoxMenu, &win->stadiumBoxMenu);
                            }
                            break;
                        case 1:
                            if (LabPC_AllBoxesEmpty(win->stadiumBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                win->state = 7;
                                TextBox_Init(&win->textBox, D_8900A954[win->operationCursor.cursor], 0, 1, 0);
                            } else if (LabPC_NoEmptyBoxAvailable(win->gbBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                win->state = 7;
                                TextBox_Init(&win->textBox, D_8900A96C, 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 2;
                                PcBox_SetActiveLists(win, &win->stadiumBoxMenu, &win->gbBoxMenu);
                            }
                            break;
                        case 2:
                            if (LabPC_AllBoxesEmpty(win->gbBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                win->state = 7;
                                TextBox_Init(&win->textBox, D_8900A954[win->operationCursor.cursor], 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                win->state = 2;
                                PcBox_SetActiveLists(win, &win->gbBoxMenu, NULL);
                            }
                            break;
                        case 3:
                            if ((LabPC_AllBoxesEmpty(win->gbBoxMenu.items) != 0) ||
                                (LabPC_AllBoxesEmpty(win->stadiumBoxMenu.items) != 0)) {
                                func_8003F6AC(8);
                                win->state = 7;
                                TextBox_Init(&win->textBox, D_8900A954[win->operationCursor.cursor], 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 2;
                                PcBox_SetActiveLists(win, &win->gbBoxMenu, &win->stadiumBoxMenu);
                            }
                            break;
                        case 4:
                            if ((LabPC_AllBoxesEmpty(win->gbBoxMenu.items) != 0) &&
                                (LabPC_AllBoxesEmpty(win->stadiumBoxMenu.items) != 0)) {
                                func_8003F6AC(8);
                                win->state = 7;
                                TextBox_Init(&win->textBox, D_8900A954[win->operationCursor.cursor], 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 6;
                            }
                            break;
                    }
                }
            }
            break;

        case 2:
            r = PcBox_UpdateSimpleCursor(win->sourceMenu);
            if (r == -1) {
                back = 1;
            } else if (r == 1) {
                if ((win->operationCursor.cursor == 0) || (win->operationCursor.cursor == 1)) {
                    func_8003F6AC(2);
                    next = 3;
                } else if (win->operationCursor.cursor == 3) {
                    func_8003F6AC(2);
                    next = 4;
                } else {
                    func_8003F6AC(2);
                    list = win->sourceMenu;
                    list->itemFlags[list->cursor] |= 8;
                    win->swapIndex = win->sourceMenu->cursor;
                    win->state = 5;
                }
            }
            break;

        case 3:
            r = PcBox_UpdateSimpleCursor(win->targetMenu);
            if (r == -1) {
                win->state = 2;
            } else if (r == 1) {
                e = win->targetMenu->cursor + *(LabPCBoxEntry**)win->targetMenu->items;
                if (e->box->count > 0) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(0x18);
                    PcBox_SwapSelectedEntries(win);
                    if ((LabPC_AllBoxesEmpty(win->sourceMenu->items) != 0) ||
                        (LabPC_NoEmptyBoxAvailable(win->targetMenu->items) != 0)) {
                        back = 1;
                    } else {
                        next = 2;
                    }
                }
            }
            break;

        case 5:
            r = PcBox_UpdateSimpleCursor(win->sourceMenu);
            if (r == -1) {
                win->sourceMenu->itemFlags[win->swapIndex] &= ~8;
                win->state = 2;
            } else if (r == 1) {
                func_8003F6AC(0x18);
                PcBox_SwapEntriesInList(win);
                win->sourceMenu->itemFlags[win->swapIndex] &= ~8;
                win->state = 2;
            }
            break;

        case 4:
            r = PcBox_UpdateSimpleCursor(win->targetMenu);
            if (r == -1) {
                win->state = 2;
            } else if (r == 1) {
                e = win->targetMenu->cursor + *(LabPCBoxEntry**)win->targetMenu->items;
                if (e->box->count == 0) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(0x18);
                    PcBox_SwapSelectedEntries(win);
                    win->state = 2;
                }
            }
            break;

        case 6:
            if (PcBox_StepViewCursorSkipEmpty(win, func_8000B30C() & 0xFFFF) != 0) {
                r = win->boxCursor.cursor;
                if (r < 8) {
                    win->sourceMenu = &win->gbBoxMenu;
                    win->gbBoxMenu.cursor = r;
                } else {
                    win->sourceMenu = &win->stadiumBoxMenu;
                    win->stadiumBoxMenu.cursor = r - 8;
                }
            } else {
                r = func_8002BC14(D_800603C0);
                if (r == -1) {
                    func_8003F6AC(3);
                    back = 1;
                } else if (r == 1) {
                    func_8003F6AC(2);
                    ret = 2;
                }
            }
            break;

        case 7:
            if (Ui_CheckConfirmPressed(&win->textBox) == 1) {
                win->state = 1;
            }
            break;
    }

    if (back > 0) {
        if (back == 1) {
            Menu_ClearItemFlags(&win->gbBoxMenu);
            Menu_ClearItemFlags(&win->stadiumBoxMenu);
        }
        win->state = back;
    }
    if (next > 0) {
        switch (next) {
            case 2:
            Menu_ClearItemFlags(&win->gbBoxMenu);
            Menu_ClearItemFlags(&win->stadiumBoxMenu);
            PcBox_DisableEmptyBoxes(win->sourceMenu);
            switch ((u32)win->operationCursor.cursor) {
                case 0:
                case 1:
                    PcBox_DisableNonEmptyBoxes(win->targetMenu);
                    break;
                case 3:
                    PcBox_DisableEmptyBoxes(win->targetMenu);
                    break;
            }
            break;
            case 6: {
            s32 a;
            s32 b;
            Menu_ClearItemFlags(&win->gbBoxMenu);
            Menu_ClearItemFlags(&win->stadiumBoxMenu);
            a = PcBox_DisableEmptyBoxes(&win->gbBoxMenu);
            b = PcBox_DisableEmptyBoxes(&win->stadiumBoxMenu);
            if (a >= 0) {
                win->boxCursor.count = 0xC;
                win->boxCursor.cursor = a;
                win->boxCursor.controller = (Controller*)D_800603C0;
                func_8000B2F4(D_800603C0);
                win->sourceMenu = &win->gbBoxMenu;
            } else {
                win->boxCursor.cursor = b + 8;
                win->boxCursor.count = 0xC;
                win->boxCursor.controller = (Controller*)D_800603C0;
                func_8000B2F4(D_800603C0);
                win->sourceMenu = &win->stadiumBoxMenu;
            }
            } break;
        }
        win->state = next;
    }
    return ret;
}

s8 *PokeIcon_AllocFramebuffers(s32 arg0);
s32 func_80017FDC(s8*, s32, s32, s32);
void PokeIcon_OpenModelArchives(void);
s32 func_80018F2C(s8*, s32, s32, s32, s32, s32, s32, s32);
void func_80027410(void*, s8*, s32, s32, s32);
void PcBox_InitOperationWindow(PcBoxOperationWindow*, s32, s32, ByteMatrix*);
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];

/**
 * Entry point: pushes the 'PBOX' pool state and creates the icon renderers.
 * Seen in play (2026-11-12): ボックスを いどうする opened the screen.
 */
void PcBox_Init(PcBoxScreen* screen) {
    s32 i;

    main_pool_push_state('PBOX');
    screen->iconFramebuffers = PokeIcon_AllocFramebuffers(1);
    screen->monRenderer = (u16*)func_80018F2C(screen->iconFramebuffers, 0x80, 0x78, 0, 0, 0x78, 0x78, 0);
    screen->iconRenderer = func_80017FDC(screen->iconFramebuffers, 0x1E, 0x28, 0x28);
    PokeIcon_OpenModelArchives();
    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    PcBox_ReadBoxes((s8*)screen->gbBoxes, 0x21, D_89019108, 8);
    PcBox_ReadBoxes((s8*)screen->stadiumBoxes, 0x11, 0, 4);
    for (i = 0; i < 8; i++) {
        screen->gbBoxEntries[i].box = &screen->gbBoxes[i];
        screen->gbBoxEntries[i].dirty = 0;
    }
    for (i = 0; i < 4; i++) {
        screen->stadiumBoxEntries[i].box = &screen->stadiumBoxes[i];
        screen->stadiumBoxEntries[i].dirty = 0;
    }
    func_80027410(&screen->gbBoxTable, screen->gbBoxEntries, 8, 8, 8);
    func_80027410(&screen->stadiumBoxTable, screen->stadiumBoxEntries, 8, 4, 4);
    PcBox_InitOperationWindow(&screen->operationWindow, 0x26, 0x53, &screen->gbBoxTable);
    screen->state = 1;
}

M2C_UNK func_80002620(M2C_UNK);                     /* extern */

/**
 * Pops the 'PBOX' pool state.
 * Seen in play (2026-11-12): B left it.
 */
void PcBox_Free(s32 unused) {
    func_80002620(0x50424F58);
}

void Ui_DrawTintedScreenBackground(s32, s32, s32, s32, s32);
extern u8 D_8900A5B8[];
void PcBox_DrawOperationWindow(PcBoxOperationWindow*);
void SavePrompt_Draw(SavePrompt*);
void PcBox_DrawMonStatusWindow(PcBoxConfirmWindow*);
/**
 * Draws the PC box screen for its current state, including the storage label and status window.
 * Seen in play (2026-11-12): drew ボックスのそうさ.
 */
void PcBox_DrawScreen(PcBoxScreen* screen) {
    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, D_8900A5B8[0], D_8900A5B8[1], D_8900A5B8[2]);
    switch (screen->state) {
        case 1:
            PcBox_DrawOperationWindow(&screen->operationWindow);
            break;
        case 4:
            PcBox_DrawOperationWindow(&screen->operationWindow);
            SavePrompt_Draw(&screen->savePrompt);
            break;
        case 2:
            PcBox_DrawList(&screen->listWindow, 2);
            break;
        case 3:
            PcBox_DrawList(&screen->listWindow, 0x10);
            PcBox_DrawMonStatusWindow(&screen->statusWindow);
            break;
    }
}


/**
 * Returns 1 when any box or party list is dirty.
 * Seen in play (2026-11-13) ran once when B left the box sort screen after nothing had been moved;
 * the screen closed without asking to save.
 */
s32 PcBox_HasUnsavedChanges(PcBoxScreen* screen) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (screen->gbBoxEntries[i].dirty != 0) {
            return 1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (screen->stadiumBoxEntries[i].dirty != 0) {
            return 1;
        }
    }
    return 0;
}

s32 PcBox_UpdateOperationWindow(PcBoxOperationWindow*);
void SavePrompt_Init(SavePrompt*, s32, s32);
void Save_DrawReportingWindow(SavePrompt*);
s32 SavePrompt_Update(SavePrompt*);
s32 PcBox_HasUnsavedChanges(PcBoxScreen* arg0);
void PcBox_SaveChanges(PcBoxScreen* arg0);
void PcBox_InitListWindow(PcBoxListWindow* arg0, s32 arg1, s32 arg2, PcBoxStorage* arg3, s32 arg4, s32 arg5, s32 arg6);
void PcBox_InitMonStatusWindow(PcBoxConfirmWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16* arg6);
/**
 * Runs the PC box screen's state machine for one frame.
 * Seen in play (2026-11-12): ran ボックスのそうさ.
 */
s32 PcBox_UpdateScreen(PcBoxScreen* screen) {
    s32 ret = 0;
    s32 r;
    LabPCBoxEntry* ent;
    LabPCBoxEntry* ent2;
    BattleMon* entry;

    switch (screen->state) {
        case 1:
            r = PcBox_UpdateOperationWindow(&screen->operationWindow);
            if (r == -1) {
                if (PcBox_HasUnsavedChanges(screen) != 0) {
                    screen->state = 4;
                    SavePrompt_Init(&screen->savePrompt, 0xCA, 0xAD);
                } else {
                    ret = 1;
                }
            } else if (r == 2) {
                ent = screen->operationWindow.sourceMenu->cursor + *(LabPCBoxEntry**)screen->operationWindow.sourceMenu->items;
                screen->state = 2;
                PcBox_InitListWindow(&screen->listWindow, 0x2C, 0x5F, ent->box, screen->iconRenderer,
                              (screen->operationWindow.boxCursor.cursor < 8) ? 0 : 1, screen->operationWindow.sourceMenu->cursor);
            }
            break;
        case 4:
            r = SavePrompt_Update(&screen->savePrompt);
            if (r == -1) {
                screen->state = 1;
            } else if (r > 0) {
                ret = 1;
                switch (r) {
                    case 1:
                        Save_DrawReportingWindow(&screen->savePrompt);
                        PcBox_SaveChanges(screen);
                        break;
                    case 2:
                        break;
                }
            }
            break;
        case 2:
            r = PcBox_UpdateListCursor(&screen->listWindow);
            if (r == -1) {
                screen->state = 1;
            } else if (r > 0) {
                ent2 = screen->operationWindow.sourceMenu->cursor + *(LabPCBoxEntry**)screen->operationWindow.sourceMenu->items;
                entry = &ent2->box->mons[screen->listWindow.menu.cursor];
                if ((entry->species.id <= 0) || (entry->species.id >= 0x98)) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(2);
                    screen->state = 3;
                    PcBox_InitMonStatusWindow(&screen->statusWindow, 0x69, 0x7D, (s32)entry, 0, D_800603C0, screen->monRenderer);
                }
            }
            break;
        case 3:
            r = func_8002BC14(D_800603C0);
            if ((r == -1) || (r == 1)) {
                func_8003F6AC(3);
                screen->state = 2;
            }
            break;
    }
    return ret;
}
