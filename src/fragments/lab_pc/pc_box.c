/* Stadium Zero fragment015_238BD0. */

#include "global.h"
#include "m2c_macros.h"
#include "lab_pc.h"
#include "asset_archive.h"
#include "memory_main.h"
#include "pokemon_stats.h"

M2C_UNK func_80023268(s32, u8, M2C_UNK);            /* extern */
extern s32 D_89019108;

void func_89006FC0(PcBoxStorage* arg0) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = (u8*)arg0;
    var_s1 = 0;
    if (arg0->count > 0) {
        do {
            func_80023268(D_89019108, *var_s0, 3);
            var_s1 += 1;
            var_s0 += 0x50;
        } while (var_s1 < arg0->count);
    }
}

/** Writes entries to a box of the Lab PC through a deck handle. */
void LabPC_WriteBoxEntries(s32 arg0, s32 arg1, s32 arg2, PcBoxStorage* arg3) {
    DeckHandle* sp1C = Deck_Open(arg0, arg1, arg2, 1);

    Deck_WriteEntries((u8*)arg3, arg3->count, sp1C);

    if ((arg0 == 0x10) || (arg0 == 0x11) || (arg0 == 0x12) || (arg0 == 0x13)) {
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

void func_890070BC(PcBoxScreen* arg0) {
    s32 any;
    s32 i;
    s32 any2;

    any2 = 0;
    any = 0;

    for (i = 0; i < 8; i++) {
        if (arg0->gbBoxEntries[i].dirty != 0) {
            any = 1;
            break;
        }
    }
    if (any != 0) {
        func_80022118(D_89019108);
    }
    for (i = 0; i < 8; i++) {
        if (arg0->gbBoxEntries[i].dirty != 0) {
            LabPC_WriteBoxEntries(0x21, D_89019108, i, arg0->gbBoxEntries[i].box);
            func_89006FC0(arg0->gbBoxEntries[i].box);
        }
    }
    for (i = 0; i < 4; i++) {
        if (arg0->stadiumBoxEntries[i].dirty != 0) {
            LabPC_WriteBoxEntries(0x11, 0, i, arg0->stadiumBoxEntries[i].box);
            any2 = 1;
        }
    }
    if (any != 0) {
        func_800230C4(D_89019108);
        if (func_8002207C(D_89019108) == 0) {
            func_8002D7D4(D_89019108);
            PcBox_DrawScreen(arg0);
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
s32 PcBox_ReadDeck(s32 arg0, s32 arg1, s32 arg2, s8* arg3, s32 arg4) {
    s32 sp1C;
    DeckHandle* sp18;

    sp18 = Deck_Open(arg0, arg1, arg2, 0);
    sp1C = Deck_ReadEntries((u8*)arg3, arg4, sp18);
    Deck_CloseAndFlush(sp18);
    return sp1C;
}

s32 PcBox_ReadDeck(M2C_UNK, M2C_UNK, s32, s8 *, s32); /* extern */
void func_89007264(s8 *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3)
{
  s32 temp_v0;
  s32 *new_var2; // FAKE: permuter temp
  int new_var; // FAKE: permuter temp
  s32 var_s0;
  arg0 = arg0; // FAKE: self-assignment
  new_var = 0;
  new_var = arg3 > new_var;
  var_s0 = 0;
  if (new_var)
  {
    do
    {
      temp_v0 = PcBox_ReadDeck(arg1, arg2, var_s0, arg0, 0x1E);
      var_s0 += 1;
      arg0 += 0x964;
      new_var2 = (s32 *) (((s8 *) arg0) + (-4));
      *new_var2 = temp_v0;
    }
    while (var_s0 != arg3);
  }
}


/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 LabPC_NoEmptyBoxAvailable(ByteMatrix* arg0) {
    s32 i;
    LabPCBoxEntry* var_a0 = (LabPCBoxEntry*)arg0->rows;

    for (i = 0; i < arg0->count; i++, var_a0++) {
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
s32 LabPC_AllBoxesEmpty(ByteMatrix* arg0) {
    s32 i;
    LabPCBoxEntry* var_a0 = (LabPCBoxEntry*)arg0->rows;

    for (i = 0; i < arg0->count; i++, var_a0++) {
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
 * Sets up the confirm window (430x292) with its labeled Yes/No buttons.
 * Seen in play (2026-11-13) set up the ほんとうにいいの？ はい/いいえ window in せいとん > ポケモンをにがす.
 */
void PcBox_InitConfirmWindow(PcBoxConfirmWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16* arg6) {
    Window_SetRect((s8*)&arg0->window, arg1, arg2, 0x1AE, 0x124);
    arg0->window.animTimer = 0;
    arg0->window.title = NULL;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x1001;
    Window_InitLabeled((s8*)&arg0->yesButton, arg0->window.frame.x + 0x10A, arg0->window.frame.y + 0x100, 0x48, *(Color_RGBA8 *)D_8900A870, D_89018E60);
    arg0->yesButton.labelX = 0xA;
    arg0->yesButton.unk_34 = 0xC;
    Window_InitLabeled((s8*)&arg0->noButton, arg0->window.frame.x + 0x15A, arg0->window.frame.y + 0x100, 0x48, *(Color_RGBA8 *)D_8900A870, D_89018E68);
    arg0->choice.count = 2;
    arg0->choice.cursor = 0;
    arg0->choice.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    arg0->choice.controller = (Controller*)arg5;
    func_8000B2F4(arg5);
    arg0->title = (char*)arg4;
    arg0->mon = (BattleMon*)arg3;
    arg0->animLoaded = 0;
    arg0->anim = arg6;
    if (arg4 != 0) {
        *arg0->anim &= ~2;
        *arg0->anim &= ~4;
    } else {
        *arg0->anim |= 2;
        *arg0->anim |= 4;
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
void PcBox_DrawMoveName(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Entry8006A9D4* entry;
    const char* str;
    Color890075E0* c;

    func_8001A384(8, 0);
    if (arg2 == -2) {
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        str = D_89018E70;
    } else {
        entry = &D_8006A9D4[arg2];
        c = &D_80066AD8[entry->type].color;
        func_8001AA9C(c->r, c->g, c->b, c->a);
        str = entry->name;
    }
    if (arg3 != 0) {
        arg0 = arg0 - (func_800566BC(str) >> 1) * 20 + 0x8C;
    }
    func_8001A944(arg0, arg1, str);
}


/**
 * Draws the name of the species' type 1 or 2 in its type color; nothing for a missing type 2.
 * Seen in play (2026-11-13) in the せいとん > ポケモンをにがす confirm it drew くさ and どく for フシギダネ, and ほのお
 * with no type 2 for ヒトカゲ.
 */
void PcBox_DrawTypeName(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Color890075E0 c;
    s32 idx = Pokemon_GetTypeIndex(arg2, arg3);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(8, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(arg0, arg1, D_80066AD8[idx].str);
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
void PcBox_DrawMonStatusWindow(PcBoxConfirmWindow* arg0) {
    s32 y = arg0->window.frame.y + 6;
    s32 x = arg0->window.frame.x + 6;
    s32 count = BattleMon_CountMoves(arg0->mon);
    s32 i;
    s32 n;
    s32 row;
    u8* tex;

    if (func_8002AE6C(arg0) == 0) {
        Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0xF3, arg0->window.frame.width, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(x, y, arg0->window.frame.width - 0xC, 0x20, D_8900A874);
        func_80029028(x + 0x78, y + 0x20, arg0->window.frame.width - 0x84, 0x78, D_8900A878);
        func_80029028(x, y + 0xF4, arg0->window.frame.width - 0xC, 0x24, D_8900A5BC);
        Ui_FillRectPrimEnvColor(x, y + 0x98, arg0->window.frame.width - 0xC, 0x56, D_8900A87C, D_8900A880);
        func_8001AB6C();
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001A384(8, 0);
        func_8001ABE8();
        func_8001AAE4(0x7F, 0xA8, 0xFF, 0xFF);
        func_8001A944(x + 0xA, y + 5, (char*)arg0->mon->nickname);
        func_8001AC3C();
        func_8001A384(4, -1);
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        func_8001A944(x + 0x84, y + 9, D_89018E80);
        func_8001A944(x + 0x112, y + 9, D_89018E84);
        func_8001A384(8, 0);
        func_8001A944(x + 0xB2, y + 5, D_89018E88, arg0->mon->level);
        func_8001A944(x + 0x140, y + 5, D_89018E8C, arg0->mon->maxHp);
        func_8001A944(x + 0x88, y + 0x28, D_89018E90);
        if (Pokemon_GetTypeIndex((s32)arg0->mon, 1) != -1) {
            func_8001A944(x + 0x88, y + 0x64, D_89018E9C);
        }
        func_8001A944(x + 0x102, y + 0x28, D_89018EA8);
        func_8001A944(x + 0x102, y + 0x44, D_89018EB4);
        func_8001A944(x + 0x102, y + 0x60, D_89018EC0);
        func_8001A944(x + 0x102, y + 0x7C, D_89018ECC);
        func_8001A944(x + 0x15C, y + 0x28, D_89018ED8, arg0->mon->attack);
        func_8001A944(x + 0x15C, y + 0x44, D_89018EDC, arg0->mon->defense);
        func_8001A944(x + 0x15C, y + 0x60, D_89018EE0, arg0->mon->speed);
        func_8001A944(x + 0x15C, y + 0x7C, D_89018EE4, arg0->mon->special);
        for (i = 0; i < count; i++) {
            PcBox_DrawMoveName(D_8900A884[i].x + x, D_8900A884[i].y + y, BattleMon_GetMoveIndex(arg0->mon, i), D_8900A884[i].centered);
        }
        func_8001ABBC();
        PcBox_DrawTypeName(x + 0x9C, y + 0x40, (s32)arg0->mon, 0);
        PcBox_DrawTypeName(x + 0x9C, y + 0x7C, (s32)arg0->mon, 1);
        gSPDisplayList(gDisplayListHead++, D_80060290);
        for (i = 0; i < count; i++) {
            func_8001B884(D_8900A884[i].iconX + x, D_8900A884[i].y + y, 0x14, 0x14, (u8*)D_8900A884[i].icon, 0x14, 0x200000);
        }
        gSPDisplayList(gDisplayListHead++, D_80060398);
        if (arg0->title != NULL) {
            func_8001AB6C();
            func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
            func_8001A384(8, 0);
            func_8001A944(arg0->window.frame.x + 0xE, arg0->window.frame.y + 0x102, arg0->title);
            func_8001ABBC();
            Window_DrawLabeled((char*)&arg0->yesButton, (arg0->choice.cursor == 0) ? 2 : 0);
            Window_DrawLabeled((char*)&arg0->noButton, (arg0->choice.cursor == 1) ? 2 : 0);
        }
        if (arg0->animLoaded == 0) {
            arg0->animLoaded = 1;
            func_80019008((s32)arg0->anim, arg0->mon, 0x416D);
        }
        tex = func_800196F8((s32)arg0->anim);
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
s32 PcBox_UpdateConfirmCursor(PcBoxConfirmWindow* arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (Ui_HandleHorizontalSelectionInput(&arg0->choice) == 0) {
        dir = Ui_GetSelectionDirection(arg0->choice.controller);
        if (dir == -1) {
            sp1C = -1;
        } else if (dir == 1) {
            if (arg0->choice.cursor == 1) {
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
void func_89007D54(s32 arg0, s32 arg1, BattleMon* arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad[4]; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0 + 1, arg1 + 1, 0x58, 0x2E, D_8900A5BC);
    func_80029028(arg0 + 1, arg1 + 0x2F, 0x58, 0x12, D_8900A8D4);
    func_80029028(arg0, arg1, 0x5A, 1, D_8900A8D8);
    func_80029028(arg0, arg1 + 0x41, 0x5A, 1, D_8900A8D8);
    func_80029028(arg0, arg1 + 1, 1, 0x40, D_8900A8D8);
    func_80029028(arg0 + 0x59, arg1 + 1, 1, 0x40, D_8900A8D8);
    if (arg2 != NULL) {
        if (arg4 & 0x10) {
            Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0x54, 0x2C, D_8900A5BC);
            Ui_FillRectHighlighted(arg0 + 3, arg1 + 0x2F, 0x54, 0x10, D_8900A8D4);
        }
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(arg0 + 4, arg1 + 0x24, 8, 0xA, D_04011A60, 8, 0);
        Ui_DrawNumberUnpadded(arg0 + 0xE, arg1 + 0x22, arg2->level);
        func_8001AB6C();
        Font_SetColorForFlags(arg4);
        func_8001A384(4, 0);
        func_8001A944(arg0 + 5, arg1 + 0x30, (char*)arg2->nickname);
        func_8001ABBC();
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(arg0 + 0x2C, arg1 + 4, 0x28, 0x28, PokeIcon_GetImage(arg5, arg3), 0x28, 0x200000);
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
void func_89007D54();
void func_8900806C(PcBoxListWindow* arg0, s32 arg1, s32 arg2, PcBoxStorage* arg3, s32 arg4, s32 arg5, s32 arg6) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 i;
    u8* p;

    func_8000A460((char*)D_890289E0, (arg5 == 0) ? D_89018EE8 : D_89018EF0);
    *(Str8900806C*)(func_800566BC((char*)D_890289E0) + D_890289E0) = *(Str8900806C*)D_89018EF8;
    D_890289E0[func_800566BC((char*)D_890289E0) - 1] += arg6 + 1;
    Window_SetRect((s8*)&arg0->window, arg1, arg2, 0x228, 0x156);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = (char*)D_890289E0;
    func_80027410((s8*)&arg0->mons, (s8*)arg3, 0x50, 0x1E, arg3->count);
    GridMenu_Init((s8*)&arg0->menu, (s8*)&arg0->mons, (s8*)arg0->itemFlags, func_89007D54, 6, 0x5A, 0x42);
    arg0->menu.options |= 0x10000;
    func_80018168(arg4);
    for (p = (u8*)arg3, i = 0; i < arg3->count; i++, p += 0x50) {
        Color_RGBA8 c = D_8900A5BC;

        func_8001833C((PokeIconRenderer*)arg4, i, (BattleMon*)p, GPACK_RGBA5551(c.r, c.g, c.b, 1));
    }
    arg0->iconRenderer = arg4;
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK func_800189C0(s32, M2C_UNK);                /* extern */
s32 func_8002AE6C();                                /* extern */
M2C_UNK GridMenu_DrawInlineItems(void*, s32, s32, s32, s32);  /* extern */

/**
 * Draws the list window's rows (refreshing the icons unless flag 0x10 is set).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void PcBox_DrawList(PcBoxListWindow* arg0, s32 arg1) {
    if (func_8002AE6C() == 0) {
        if (!(arg1 & 0x10)) {
            func_800189C0(arg0->iconRenderer, 0);
            BgStage_DrawFrame();
        }
        GridMenu_DrawInlineItems((s8*)&arg0->menu, arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg1 | 0xFFED, arg0->iconRenderer);
    }
}

s32 GridMenu_UpdateCursor(void*);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;
/**
 * Moves the list cursor. Returns -1 on cancel, the 1-based row on confirm, otherwise 0.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 PcBox_UpdateListCursor(PcBoxListWindow* arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (GridMenu_UpdateCursor(&arg0->menu) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = arg0->menu.cursor + 1;
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
 * Draws ボックス%d (Box %d).
 * Seen in play (2026-11-12): ボックス1 ... ボックス4 on the 64 side.
 */
void PcBox_DrawBoxName(s32 arg0, s32 arg1, LabPCBoxEntry* arg2, s32 arg3, s32 arg4) {
    Color_RGBA8 color;
    s32 pad[2]; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xCE, 0x1A, D_8900A8E8);
    func_80029028(arg0, arg1, 0xCE, 1, D_8900A8F0);
    func_80029028(arg0, arg1 + 0x1B, 0xCE, 1, D_8900A8F0);
    if (arg4 & 0x18) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xC8, 0x16, D_8900A5BC);
    }
    func_8001AB6C();
    func_8001A384(8, 0);
    if (arg2->box->count == 0) {
        color = D_8900A8DC[(arg4 & 2) ? 0 : 1];
    } else {
        color = ((Color_RGBA8*)&D_800734A8)[(arg4 & 2) ? 0 : 1];
    }
    if (arg4 & 1) {
        color.a = 0x4C;
    }
    func_8001AA9C(color.r, color.g, color.b, color.a);
    func_8001A944(arg0 + 8, arg1 + 4, D_89018F08, arg3 + 1);
    func_8001ABBC();
    if (arg2->box->count > 0) {
        Ui_DrawImageInStrips(D_80073614, arg0 + 0x78, arg1 + 4);
    }
    Ui_DrawNumber(arg0 + 0x98, arg1 + 8, arg2->box->count, 2);
    Ui_DrawNumber(arg0 + 0xB3, arg1 + 8, 0x1E, 2);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001BCB4(arg0 + 0xAA, arg1 + 0xA, 8, 0xA, D_04011AB8, 8, 0);
}

extern char D_89018F14[];
extern char D_89018F20[];
extern u8 D_80073634[];

/**
 * Draws ボックス%d (Box %d) and its %2d/%2d fill count.
 * Seen in play (2026-11-12): ボックス1 0/30 ... ボックス8 0/30.
 */
void PcBox_DrawBoxCount(s32 arg0, s32 arg1, LabPCBoxEntry* arg2, s32 arg3, s32 arg4) {
    Color_RGBA8 color;
    s32 pad[11]; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0x104, 0x36, D_8900A8F8);
    func_80029028(arg0, arg1, 0x104, 1, D_8900A900);
    func_80029028(arg0, arg1 + 0x37, 0x104, 1, D_8900A900);
    if (arg4 & 0x18) {
        Ui_FillRectHighlighted(arg0 + 3, arg1 + 3, 0xFE, 0x32, D_8900A5BC);
    }
    func_8001AB6C();
    func_8001A384(0x10, 0);
    if (arg2->box->count == 0) {
        color = D_8900A8DC[(arg4 & 2) ? 0 : 1];
    } else {
        color = ((Color_RGBA8*)&D_800734A8)[(arg4 & 2) ? 0 : 1];
    }
    if (arg4 & 1) {
        color.a = 0x4C;
    }
    func_8001AA9C(color.r, color.g, color.b, color.a);
    func_8001A944(arg0 + 8, arg1 + 0x10, D_89018F14, arg3 + 1);
    func_8001A384(4, -1);
    func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
    func_8001A944(arg0 + 0xB0, arg1 + 0x14, D_89018F20, arg2->box->count, 0x1E);
    func_8001ABBC();
    if (arg2->box->count > 0) {
        Ui_DrawImageInStrips(D_80073634, arg0 + 0x8C, arg1 + 0x10);
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
void PcBox_InitOperationWindow(PcBoxOperationWindow* arg0, s32 x, s32 y, ByteMatrix* arg3) {
    Window_SetRect(&arg0->window, x, y, 0x234, 0x172);
    arg0->window.animTimer = 0;
    arg0->window.state = 0;
    arg0->window.frame.style = 0x801;
    arg0->window.title = (char*)D_89018F4C;
    Window_SetRect(&arg0->footerFrame, arg0->window.frame.x + 6, arg0->window.frame.y + 0x12C, arg0->window.frame.width - 0xC, 0x40);
    arg0->footerFrame.style = 6;
    arg0->footerFrame.color = D_8900A91C;
    arg0->footerFrame.color2 = D_8900A920;
    func_8002B018(&arg0->backButton, x + 0xE4, y + 0xE, 0x36, 0x2A, 0x30, (s32)D_8900BFC0);
    arg0->backButton.selectedColor = D_8900A580[0];
    arg0->backButton.color = D_8900A580[1];
    arg0->backButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->moveTo64Button, x + 0xE4, y + 0x3C, 0x36, 0x2A, 0x30, (s32)D_8900DAD0);
    arg0->moveTo64Button.selectedColor = D_8900A580[2];
    arg0->moveTo64Button.color = D_8900A580[3];
    arg0->moveTo64Button.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->moveToGbButton, x + 0xE4, y + 0x6A, 0x36, 0x2A, 0x30, (s32)D_8900CD48);
    arg0->moveToGbButton.selectedColor = D_8900A580[2];
    arg0->moveToGbButton.color = D_8900A580[3];
    arg0->moveToGbButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->reorderButton, x + 0xE4, y + 0x98, 0x36, 0x2A, 0x30, (s32)D_8900E858);
    arg0->reorderButton.selectedColor = D_8900A580[4];
    arg0->reorderButton.color = D_8900A580[5];
    arg0->reorderButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->exchangeButton, x + 0xE4, y + 0xC6, 0x36, 0x2A, 0x30, (s32)D_8900F5E0);
    arg0->exchangeButton.selectedColor = D_8900A580[6];
    arg0->exchangeButton.color = D_8900A580[7];
    arg0->exchangeButton.highlightColor = D_8900A5BC;
    func_8002B018(&arg0->viewButton, x + 0xE4, y + 0xF4, 0x36, 0x2A, 0x30, (s32)D_89010368);
    arg0->viewButton.selectedColor = D_8900A580[8];
    arg0->viewButton.color = D_8900A580[9];
    arg0->viewButton.highlightColor = D_8900A5BC;
    arg0->operationCursor.count = 6;
    arg0->operationCursor.cursor = 0;
    arg0->operationCursor.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    Menu_Init(&arg0->gbBoxMenu, (s32)arg3, (s32)arg0->gbBoxFlags, (s32)PcBox_DrawBoxName, 0xCE, 0x1C);
    arg0->gbBoxMenu.options |= 0x10000;
    Menu_Init(&arg0->stadiumBoxMenu, (s32)(arg3 + 1), (s32)arg0->stadiumBoxFlags, (s32)PcBox_DrawBoxCount, 0x104, 0x38);
    arg0->stadiumBoxMenu.options |= 0x10000;
    arg0->state = 1;
}

extern s32 D_8900A924[];
extern s32 D_8900A93C[];
void LabItem_DrawTitleText(s32, s32, s32, s32);
void func_89008EF0(PcBoxOperationWindow* arg0) {
    if (arg0->state == 1) {
        if (0) {}  // karodo
        LabItem_DrawTitleText(arg0->footerFrame.x + 0x58, arg0->footerFrame.y, D_8900A924[(0, arg0)->operationCursor.cursor], D_8900A93C[arg0->operationCursor.cursor]); // FAKE: comma expression
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
void PcBox_DrawOperationWindow(PcBoxOperationWindow* arg0) {
    s32 sel = 0x10;
    s32 flags[2];
    s32 pad[2]; // FAKE
    s32 a;
    s32 b;

    if (func_8002AE6C(&arg0->window) != 0) {
        return;
    }
    Window_DrawFrame(&arg0->footerFrame);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 6, arg0->window.frame.width - 0xC, 0xA, D_8900A5BC);
    func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x11C, arg0->window.frame.width - 0xC, 0xA, D_8900A5BC);
    func_80029028(arg0->window.frame.x + 6, arg0->window.frame.y + 0x10, 0xA, 0x10C, D_8900A5BC);
    func_80029028(arg0->window.frame.x + arg0->window.frame.width - 0x10, arg0->window.frame.y + 0x10, 0xA, 0x10C, D_8900A5BC);
    func_80029028(arg0->window.frame.x + 0xDE, arg0->window.frame.y + 0x10, 0x42, 0x10C, D_8900A5BC);
    Ui_DrawTexturedDivider(arg0->window.frame.x, arg0->window.frame.y + 0x125, arg0->window.frame.width, D_8007356C);
    Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0xE, arg0->window.frame.y + 0xE, 0xD2, 0x110, D_800735C4);
    Ui_DrawTexturedFrameDecal(arg0->window.frame.x + 0x11E, arg0->window.frame.y + 0xE, 0x108, 0x110, D_800735C4);
    flags[1] = flags[0] = 0xFFED;
    switch (arg0->state) {
        case 1:
            sel = 2;
            break;
        case 2:
            flags[(arg0->operationCursor.cursor == 1) ? 1 : 0] |= 2;
            break;
        case 3:
        case 4:
            if (arg0->operationCursor.cursor == 1) {
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
            flags[(arg0->boxCursor.cursor < 8) ? 0 : 1] |= 2;
            break;
    }
    func_8002B054(&arg0->backButton, (arg0->operationCursor.cursor == 5) ? sel : 0);
    func_8002B054(&arg0->moveTo64Button, (arg0->operationCursor.cursor == 0) ? sel : 0);
    func_8002B054(&arg0->moveToGbButton, (arg0->operationCursor.cursor == 1) ? sel : 0);
    func_8002B054(&arg0->reorderButton, (arg0->operationCursor.cursor == 2) ? sel : 0);
    func_8002B054(&arg0->exchangeButton, (arg0->operationCursor.cursor == 3) ? sel : 0);
    func_8002B054(&arg0->viewButton, (arg0->operationCursor.cursor == 4) ? sel : 0);
    PcBox_DrawStorageLabel(arg0->window.frame.x + 0x10, arg0->window.frame.y + 0x10, 2, 0);
    PcBox_DrawStorageLabel(arg0->window.frame.x + 0x120, arg0->window.frame.y + 0x10, 2, 1);
    Menu_DrawInlineItems(&arg0->gbBoxMenu, arg0->window.frame.x + 0x10, arg0->window.frame.y + 0x3C, flags[0], 0);
    Menu_DrawInlineItems(&arg0->stadiumBoxMenu, arg0->window.frame.x + 0x120, arg0->window.frame.y + 0x3C, flags[1], 0);
    func_89008EF0(arg0);
    if (arg0->state == 7) {
        TextBox_Draw(&arg0->textBox);
    }
}

s32 Menu_UpdateCursorSkipDisabled(void* arg0);

/**
 * Moves a menu cursor. Returns -1 on cancel, 1 on confirm, otherwise 0.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 PcBox_UpdateSimpleCursor(Menu* arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (Menu_UpdateCursorSkipDisabled(arg0) == 0) {
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
 * Swaps the box of the entry selected in sourceMenu with
 * that of the entry selected in targetMenu, then sets the second
 * word (dirty) of both entries to 1. The entry is `rows[cursor]` of the menu's item
 * table, written `cursor + *(LabPCBoxEntry**)menu->items` (rows is the first field) because
 * a cast of `items->rows` or the other operand order changes the load order; that form gives the
 * retail temp numbering.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void PcBox_SwapSelectedEntries(PcBoxOperationWindow* arg0) {
    LabPCBoxEntry* a;
    LabPCBoxEntry* b;
    PcBoxStorage* tmp;

    a = arg0->sourceMenu->cursor + *(LabPCBoxEntry**)arg0->sourceMenu->items;
    b = arg0->targetMenu->cursor + *(LabPCBoxEntry**)arg0->targetMenu->items;
    tmp = b->box;
    b->box = a->box;
    a->dirty = 1;
    a->box = tmp;
    b->dirty = 1;
}

/**
 * Swaps two entries of the same box list and marks both dirty.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void PcBox_SwapEntriesInList(PcBoxOperationWindow* arg0) {
    LabPCBoxEntry* a = arg0->swapIndex + *(LabPCBoxEntry**)arg0->sourceMenu->items;
    LabPCBoxEntry* b = arg0->sourceMenu->cursor + *(LabPCBoxEntry**)arg0->sourceMenu->items;
    PcBoxStorage* temp = b->box;

    b->box = a->box;
    a->dirty = 1;
    a->box = temp;
    b->dirty = 1;
}

s32 Menu_SkipDisabledForward(void*);
/**
 * Disables the list rows of boxes that hold no Pokemon.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 PcBox_DisableEmptyBoxes(Menu* arg0) {
    s32 i;
    ByteMatrix* list = arg0->items;
    s32 n = list->count;
    LabPCBoxEntry* e = (LabPCBoxEntry*)list->rows;

    for (i = 0; i < n; i++, e++) {
        if (e->box->count == 0) {
            arg0->itemFlags[i] |= 1;
        }
    }
    arg0->cursor = 0;
    return Menu_SkipDisabledForward(arg0);
}


/**
 * Disables the list rows of boxes that already hold Pokemon.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void PcBox_DisableNonEmptyBoxes(Menu* arg0) {
    s32 i;
    ByteMatrix* list = arg0->items;
    s32 n = list->count;
    LabPCBoxEntry* e = (LabPCBoxEntry*)list->rows;

    for (i = 0; i < n; i++, e++) {
        if (e->box->count > 0) {
            arg0->itemFlags[i] |= 1;
        }
    }
    arg0->cursor = 0;
    Menu_SkipDisabledForward(arg0);
}

/**
 * Sets the left and right box lists (either may be NULL) and resets their cursors.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void PcBox_SetActiveLists(PcBoxOperationWindow* arg0, Menu* arg1, Menu* arg2) {
    if (arg1 != NULL) {
        arg0->sourceMenu = arg1;
        arg1->cursor = 0;
    }
    if (arg2 != NULL) {
        arg0->targetMenu = arg2;
        arg2->cursor = 0;
    }
}

s32 func_8002B204();
s32 func_89009738(PcBoxOperationWindow* arg0, s32 arg1) {
    s32 r;
    s32 idx;
    s32 pos;

    for (r = func_8002B204(&arg0->boxCursor, arg1); r != 0; r = func_8002B204(&arg0->boxCursor, arg1)) {
        pos = arg0->boxCursor.cursor;
        idx = pos - 8;
        if (pos < 8) {
            arg0->sourceMenu = &arg0->gbBoxMenu;
            idx = pos;
        } else {
            arg0->sourceMenu = &arg0->stadiumBoxMenu;
        }
        if (!(arg0->sourceMenu->itemFlags[idx] & 1)) {
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
s32 PcBox_UpdateOperationWindow(PcBoxOperationWindow* arg0) {
    s32 ret = 0;
    s32 pad; // FAKE
    s32 next = 0;
    s32 back = 0;
    s32 pad2; // FAKE
    s32 r;
    Menu* list;
    LabPCBoxEntry* e;

    switch (arg0->state) {
        case 1:
            if (func_8002B2B0(&arg0->operationCursor) == 0) {
                r = func_8002BC14(D_800603C0);
                if (r == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (r == 1) {
                    switch ((u32)arg0->operationCursor.cursor) {
                        case 5:
                            func_8003F6AC(3);
                            ret = -1;
                            break;
                        case 0:
                            if (LabPC_AllBoxesEmpty(arg0->gbBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                arg0->state = 7;
                                TextBox_Init(&arg0->textBox, D_8900A954[arg0->operationCursor.cursor], 0, 1, 0);
                            } else if (LabPC_NoEmptyBoxAvailable(arg0->stadiumBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                arg0->state = 7;
                                TextBox_Init(&arg0->textBox, D_8900A96C, 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 2;
                                PcBox_SetActiveLists(arg0, &arg0->gbBoxMenu, &arg0->stadiumBoxMenu);
                            }
                            break;
                        case 1:
                            if (LabPC_AllBoxesEmpty(arg0->stadiumBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                arg0->state = 7;
                                TextBox_Init(&arg0->textBox, D_8900A954[arg0->operationCursor.cursor], 0, 1, 0);
                            } else if (LabPC_NoEmptyBoxAvailable(arg0->gbBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                arg0->state = 7;
                                TextBox_Init(&arg0->textBox, D_8900A96C, 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 2;
                                PcBox_SetActiveLists(arg0, &arg0->stadiumBoxMenu, &arg0->gbBoxMenu);
                            }
                            break;
                        case 2:
                            if (LabPC_AllBoxesEmpty(arg0->gbBoxMenu.items) != 0) {
                                func_8003F6AC(8);
                                arg0->state = 7;
                                TextBox_Init(&arg0->textBox, D_8900A954[arg0->operationCursor.cursor], 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                arg0->state = 2;
                                PcBox_SetActiveLists(arg0, &arg0->gbBoxMenu, NULL);
                            }
                            break;
                        case 3:
                            if ((LabPC_AllBoxesEmpty(arg0->gbBoxMenu.items) != 0) ||
                                (LabPC_AllBoxesEmpty(arg0->stadiumBoxMenu.items) != 0)) {
                                func_8003F6AC(8);
                                arg0->state = 7;
                                TextBox_Init(&arg0->textBox, D_8900A954[arg0->operationCursor.cursor], 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 2;
                                PcBox_SetActiveLists(arg0, &arg0->gbBoxMenu, &arg0->stadiumBoxMenu);
                            }
                            break;
                        case 4:
                            if ((LabPC_AllBoxesEmpty(arg0->gbBoxMenu.items) != 0) &&
                                (LabPC_AllBoxesEmpty(arg0->stadiumBoxMenu.items) != 0)) {
                                func_8003F6AC(8);
                                arg0->state = 7;
                                TextBox_Init(&arg0->textBox, D_8900A954[arg0->operationCursor.cursor], 0, 1, 0);
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
            r = PcBox_UpdateSimpleCursor(arg0->sourceMenu);
            if (r == -1) {
                back = 1;
            } else if (r == 1) {
                if ((arg0->operationCursor.cursor == 0) || (arg0->operationCursor.cursor == 1)) {
                    func_8003F6AC(2);
                    next = 3;
                } else if (arg0->operationCursor.cursor == 3) {
                    func_8003F6AC(2);
                    next = 4;
                } else {
                    func_8003F6AC(2);
                    list = arg0->sourceMenu;
                    list->itemFlags[list->cursor] |= 8;
                    arg0->swapIndex = arg0->sourceMenu->cursor;
                    arg0->state = 5;
                }
            }
            break;

        case 3:
            r = PcBox_UpdateSimpleCursor(arg0->targetMenu);
            if (r == -1) {
                arg0->state = 2;
            } else if (r == 1) {
                e = arg0->targetMenu->cursor + *(LabPCBoxEntry**)arg0->targetMenu->items;
                if (e->box->count > 0) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(0x18);
                    PcBox_SwapSelectedEntries(arg0);
                    if ((LabPC_AllBoxesEmpty(arg0->sourceMenu->items) != 0) ||
                        (LabPC_NoEmptyBoxAvailable(arg0->targetMenu->items) != 0)) {
                        back = 1;
                    } else {
                        next = 2;
                    }
                }
            }
            break;

        case 5:
            r = PcBox_UpdateSimpleCursor(arg0->sourceMenu);
            if (r == -1) {
                arg0->sourceMenu->itemFlags[arg0->swapIndex] &= ~8;
                arg0->state = 2;
            } else if (r == 1) {
                func_8003F6AC(0x18);
                PcBox_SwapEntriesInList(arg0);
                arg0->sourceMenu->itemFlags[arg0->swapIndex] &= ~8;
                arg0->state = 2;
            }
            break;

        case 4:
            r = PcBox_UpdateSimpleCursor(arg0->targetMenu);
            if (r == -1) {
                arg0->state = 2;
            } else if (r == 1) {
                e = arg0->targetMenu->cursor + *(LabPCBoxEntry**)arg0->targetMenu->items;
                if (e->box->count == 0) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(0x18);
                    PcBox_SwapSelectedEntries(arg0);
                    arg0->state = 2;
                }
            }
            break;

        case 6:
            if (func_89009738(arg0, func_8000B30C() & 0xFFFF) != 0) {
                r = arg0->boxCursor.cursor;
                if (r < 8) {
                    arg0->sourceMenu = &arg0->gbBoxMenu;
                    arg0->gbBoxMenu.cursor = r;
                } else {
                    arg0->sourceMenu = &arg0->stadiumBoxMenu;
                    arg0->stadiumBoxMenu.cursor = r - 8;
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
            if (Ui_CheckConfirmPressed(&arg0->textBox) == 1) {
                arg0->state = 1;
            }
            break;
    }

    if (back > 0) {
        if (back == 1) {
            Menu_ClearItemFlags(&arg0->gbBoxMenu);
            Menu_ClearItemFlags(&arg0->stadiumBoxMenu);
        }
        arg0->state = back;
    }
    if (next > 0) {
        switch (next) {
            case 2:
            Menu_ClearItemFlags(&arg0->gbBoxMenu);
            Menu_ClearItemFlags(&arg0->stadiumBoxMenu);
            PcBox_DisableEmptyBoxes(arg0->sourceMenu);
            switch ((u32)arg0->operationCursor.cursor) {
                case 0:
                case 1:
                    PcBox_DisableNonEmptyBoxes(arg0->targetMenu);
                    break;
                case 3:
                    PcBox_DisableEmptyBoxes(arg0->targetMenu);
                    break;
            }
            break;
            case 6: {
            s32 a;
            s32 b;
            Menu_ClearItemFlags(&arg0->gbBoxMenu);
            Menu_ClearItemFlags(&arg0->stadiumBoxMenu);
            a = PcBox_DisableEmptyBoxes(&arg0->gbBoxMenu);
            b = PcBox_DisableEmptyBoxes(&arg0->stadiumBoxMenu);
            if (a >= 0) {
                arg0->boxCursor.count = 0xC;
                arg0->boxCursor.cursor = a;
                arg0->boxCursor.controller = (Controller*)D_800603C0;
                func_8000B2F4(D_800603C0);
                arg0->sourceMenu = &arg0->gbBoxMenu;
            } else {
                arg0->boxCursor.cursor = b + 8;
                arg0->boxCursor.count = 0xC;
                arg0->boxCursor.controller = (Controller*)D_800603C0;
                func_8000B2F4(D_800603C0);
                arg0->sourceMenu = &arg0->stadiumBoxMenu;
            }
            } break;
        }
        arg0->state = next;
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
void PcBox_Init(PcBoxScreen* arg0) {
    s32 i;

    main_pool_push_state('PBOX');
    arg0->iconFramebuffers = PokeIcon_AllocFramebuffers(1);
    arg0->monRenderer = (u16*)func_80018F2C(arg0->iconFramebuffers, 0x80, 0x78, 0, 0, 0x78, 0x78, 0);
    arg0->iconRenderer = func_80017FDC(arg0->iconFramebuffers, 0x1E, 0x28, 0x28);
    PokeIcon_OpenModelArchives();
    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    func_89007264((s8*)arg0->gbBoxes, 0x21, D_89019108, 8);
    func_89007264((s8*)arg0->stadiumBoxes, 0x11, 0, 4);
    for (i = 0; i < 8; i++) {
        arg0->gbBoxEntries[i].box = &arg0->gbBoxes[i];
        arg0->gbBoxEntries[i].dirty = 0;
    }
    for (i = 0; i < 4; i++) {
        arg0->stadiumBoxEntries[i].box = &arg0->stadiumBoxes[i];
        arg0->stadiumBoxEntries[i].dirty = 0;
    }
    func_80027410(&arg0->gbBoxTable, arg0->gbBoxEntries, 8, 8, 8);
    func_80027410(&arg0->stadiumBoxTable, arg0->stadiumBoxEntries, 8, 4, 4);
    PcBox_InitOperationWindow(&arg0->operationWindow, 0x26, 0x53, &arg0->gbBoxTable);
    arg0->state = 1;
}

M2C_UNK func_80002620(M2C_UNK);                     /* extern */

/**
 * Pops the 'PBOX' pool state.
 * Seen in play (2026-11-12): B left it.
 */
void PcBox_Free(s32 arg0) {
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
void PcBox_DrawScreen(PcBoxScreen* arg0) {
    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0x38, 0x1E0, D_8900A5B8[0], D_8900A5B8[1], D_8900A5B8[2]);
    switch (arg0->state) {
        case 1:
            PcBox_DrawOperationWindow(&arg0->operationWindow);
            break;
        case 4:
            PcBox_DrawOperationWindow(&arg0->operationWindow);
            SavePrompt_Draw(&arg0->savePrompt);
            break;
        case 2:
            PcBox_DrawList(&arg0->listWindow, 2);
            break;
        case 3:
            PcBox_DrawList(&arg0->listWindow, 0x10);
            PcBox_DrawMonStatusWindow(&arg0->statusWindow);
            break;
    }
}


/**
 * Returns 1 when any box or party list is dirty.
 * Seen in play (2026-11-13) ran once when B left the box sort screen after nothing had been moved;
 * the screen closed without asking to save.
 */
s32 PcBox_HasUnsavedChanges(PcBoxScreen* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (arg0->gbBoxEntries[i].dirty != 0) {
            return 1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (arg0->stadiumBoxEntries[i].dirty != 0) {
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
void func_890070BC(PcBoxScreen* arg0);
void func_8900806C(PcBoxListWindow* arg0, s32 arg1, s32 arg2, PcBoxStorage* arg3, s32 arg4, s32 arg5, s32 arg6);
void PcBox_InitConfirmWindow(PcBoxConfirmWindow* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16* arg6);
/**
 * Runs the PC box screen's state machine for one frame.
 * Seen in play (2026-11-12): ran ボックスのそうさ.
 */
s32 PcBox_UpdateScreen(PcBoxScreen* arg0) {
    s32 ret = 0;
    s32 r;
    LabPCBoxEntry* ent;
    LabPCBoxEntry* ent2;
    BattleMon* entry;

    switch (arg0->state) {
        case 1:
            r = PcBox_UpdateOperationWindow(&arg0->operationWindow);
            if (r == -1) {
                if (PcBox_HasUnsavedChanges(arg0) != 0) {
                    arg0->state = 4;
                    SavePrompt_Init(&arg0->savePrompt, 0xCA, 0xAD);
                } else {
                    ret = 1;
                }
            } else if (r == 2) {
                ent = arg0->operationWindow.sourceMenu->cursor + *(LabPCBoxEntry**)arg0->operationWindow.sourceMenu->items;
                arg0->state = 2;
                func_8900806C(&arg0->listWindow, 0x2C, 0x5F, ent->box, arg0->iconRenderer,
                              (arg0->operationWindow.boxCursor.cursor < 8) ? 0 : 1, arg0->operationWindow.sourceMenu->cursor);
            }
            break;
        case 4:
            r = SavePrompt_Update(&arg0->savePrompt);
            if (r == -1) {
                arg0->state = 1;
            } else if (r > 0) {
                ret = 1;
                switch (r) {
                    case 1:
                        Save_DrawReportingWindow(&arg0->savePrompt);
                        func_890070BC(arg0);
                        break;
                    case 2:
                        break;
                }
            }
            break;
        case 2:
            r = PcBox_UpdateListCursor(&arg0->listWindow);
            if (r == -1) {
                arg0->state = 1;
            } else if (r > 0) {
                ent2 = arg0->operationWindow.sourceMenu->cursor + *(LabPCBoxEntry**)arg0->operationWindow.sourceMenu->items;
                entry = &ent2->box->mons[arg0->listWindow.menu.cursor];
                if ((entry->species.id <= 0) || (entry->species.id >= 0x98)) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(2);
                    arg0->state = 3;
                    PcBox_InitConfirmWindow(&arg0->statusWindow, 0x69, 0x7D, (s32)entry, 0, D_800603C0, arg0->monRenderer);
                }
            }
            break;
        case 3:
            r = func_8002BC14(D_800603C0);
            if ((r == -1) || (r == 1)) {
                func_8003F6AC(3);
                arg0->state = 2;
            }
            break;
    }
    return ret;
}
