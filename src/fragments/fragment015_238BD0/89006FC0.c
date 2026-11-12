/* Stadium Zero fragment015_238BD0. */

#include "global.h"
#include "m2c_macros.h"
#include "pokemon_stats.h"

M2C_UNK func_80023268(s32, u8, M2C_UNK);            /* extern */
extern s32 D_89019108;

void func_89006FC0(u8 *arg0) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = arg0;
    var_s1 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x960) > 0) {
        do {
            func_80023268(D_89019108, *var_s0, 3);
            var_s1 += 1;
            var_s0 += 0x50;
        } while (var_s1 < M2C_FIELD(arg0, s32 *, 0x960));
    }
}

void LabPC_WriteBoxEntries(s32 arg0, s32 arg1, s32 arg2, u8* arg3) {
    DeckHandle* sp1C = Deck_Open(arg0, arg1, arg2, 1);

    Deck_WriteEntries(arg3, M2C_FIELD(arg3, s32*, 0x960), sp1C);

    if ((arg0 == 0x10) || (arg0 == 0x11) || (arg0 == 0x12) || (arg0 == 0x13)) {
        Deck_CloseAndFlushBox(sp1C);
    } else {
        Deck_CloseAndFlush(sp1C);
    }
}

typedef struct Ent890070BC {
    u8* box;
    s32 dirty;
} Ent890070BC;
s32 func_8002207C(s32);
void func_80022118(s32);
void func_80022188(s32);
void func_800230C4(s32);
void func_800243B8(void);
void func_8002D7D4(s32);
void func_8900A1CC(s8* arg0);

void func_890070BC(s8* arg0) {
    s32 any;
    s32 i;
    s32 any2;

    any2 = 0;
    any = 0;

    for (i = 0; i < 8; i++) {
        if (((Ent890070BC*)(arg0 + 0x7498))[i].dirty != 0) {
            any = 1;
            break;
        }
    }
    if (any != 0) {
        func_80022118(D_89019108);
    }
    for (i = 0; i < 8; i++) {
        if (((Ent890070BC*)(arg0 + 0x7498))[i].dirty != 0) {
            LabPC_WriteBoxEntries(0x21, D_89019108, i, ((Ent890070BC*)(arg0 + 0x7498))[i].box);
            func_89006FC0(((Ent890070BC*)(arg0 + 0x7498))[i].box);
        }
    }
    for (i = 0; i < 4; i++) {
        if (((Ent890070BC*)(arg0 + 0x74D8))[i].dirty != 0) {
            LabPC_WriteBoxEntries(0x11, 0, i, ((Ent890070BC*)(arg0 + 0x74D8))[i].box);
            any2 = 1;
        }
    }
    if (any != 0) {
        func_800230C4(D_89019108);
        if (func_8002207C(D_89019108) == 0) {
            func_8002D7D4(D_89019108);
            func_8900A1CC(arg0);
        }
        func_80022188(D_89019108);
    }
    if (any2 != 0) {
        func_800243B8();
    }
}

s32 func_8900721C(s32 arg0, s32 arg1, s32 arg2, s8* arg3, s32 arg4) {
    s32 sp1C;
    DeckHandle* sp18;

    sp18 = Deck_Open(arg0, arg1, arg2, 0);
    sp1C = Deck_ReadEntries((u8*)arg3, arg4, sp18);
    Deck_CloseAndFlush(sp18);
    return sp1C;
}

s32 func_8900721C(M2C_UNK, M2C_UNK, s32, s8 *, s32); /* extern */
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
      temp_v0 = func_8900721C(arg1, arg2, var_s0, arg0, 0x1E);
      var_s0 += 1;
      arg0 += 0x964;
      new_var2 = (s32 *) (((s8 *) arg0) + (-4));
      *new_var2 = temp_v0;
    }
    while (var_s0 != arg3);
  }
}

typedef struct LabPCBoxEntry {
    /* 0x0 */ s8* box;
    /* 0x4 */ s32 unk_04;
} LabPCBoxEntry; // size = 0x8

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 LabPC_NoEmptyBoxAvailable(s8* arg0) {
    s32 i;
    LabPCBoxEntry* var_a0 = M2C_FIELD(arg0, LabPCBoxEntry**, 0);

    for (i = 0; i < M2C_FIELD(arg0, s32*, 8); i++, var_a0++) {
        if (M2C_FIELD(var_a0->box, s32*, 0x960) == 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 LabPC_AllBoxesEmpty(s8* arg0) {
    s32 i;
    LabPCBoxEntry* var_a0 = M2C_FIELD(arg0, LabPCBoxEntry**, 0);

    for (i = 0; i < M2C_FIELD(arg0, s32*, 8); i++, var_a0++) {
        if (M2C_FIELD(var_a0->box, s32*, 0x960) > 0) {
            return 0;
        }
    }

    return 1;
}

void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_8002AE94(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5);
M2C_UNK func_8000B2F4(s32);
extern s32 D_800603C0;
extern u8 D_8900A870[];
extern char D_89018E60[];
extern char D_89018E68[];
void func_89007374(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    func_8002A8C4(arg0, arg1, arg2, 0x1AE, 0x124);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x1001;
    func_8002AE94(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 0x10A, M2C_FIELD(arg0, s32 *, 4) + 0x100, 0x48, *(Color_RGBA8 *)D_8900A870, D_89018E60);
    M2C_FIELD(arg0, s32 *, 0x58) = 0xA;
    M2C_FIELD(arg0, s32 *, 0x60) = 0xC;
    func_8002AE94(arg0 + 0x68, M2C_FIELD(arg0, s32 *, 0) + 0x15A, M2C_FIELD(arg0, s32 *, 4) + 0x100, 0x48, *(Color_RGBA8 *)D_8900A870, D_89018E68);
    M2C_FIELD(arg0, s32 *, 0xAC) = 2;
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    M2C_FIELD(arg0, s32 *, 0xA4) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32 *, 0xA4) = arg5;
    func_8000B2F4(arg5);
    M2C_FIELD(arg0, s32 *, 0xB4) = arg4;
    M2C_FIELD(arg0, s32 *, 0xB0) = arg3;
    M2C_FIELD(arg0, s32 *, 0xB8) = 0;
    M2C_FIELD(arg0, u16 **, 0xBC) = arg6;
    if (arg4 != 0) {
        *M2C_FIELD(arg0, u16 **, 0xBC) &= ~2;
        *M2C_FIELD(arg0, u16 **, 0xBC) &= ~4;
    } else {
        *M2C_FIELD(arg0, u16 **, 0xBC) |= 2;
        *M2C_FIELD(arg0, u16 **, 0xBC) |= 4;
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
s32 func_8002D498(s32, s32);
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

void func_890074E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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


void func_890075E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Color890075E0 c;
    s32 idx = func_8002D498(arg2, arg3);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(8, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(arg0, arg1, D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

typedef struct Rgba8900806C { u8 r, g, b, a; } Rgba8900806C;
typedef struct Mon89007678 {
    /* 0x00 */ char unk00[0x24];
    /* 0x24 */ u8 level;
    /* 0x25 */ char unk25[1];
    /* 0x26 */ u16 maxHp;
    /* 0x28 */ u16 attack;
    /* 0x2A */ u16 defense;
    /* 0x2C */ u16 speed;
    /* 0x2E */ u16 special;
    /* 0x30 */ char nickname[1];
} Mon89007678;
typedef struct Screen89007678 {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 w;
    /* 0x0C */ char unk0C[0x20];
    /* 0x2C */ char button1[0x3C];
    /* 0x68 */ char button2[0x40];
    /* 0xA8 */ s32 selection;
    /* 0xAC */ char unkAC[4];
    /* 0xB0 */ Mon89007678* mon;
    /* 0xB4 */ char* title;
    /* 0xB8 */ s32 animLoaded;
    /* 0xBC */ s32 anim;
} Screen89007678;
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
extern Rgba8900806C D_8900A5BC;
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
void func_800069CC();
void func_80019008(s32, Mon89007678*, s32);
u8* func_800196F8(s32);
void func_8001AAE4(u8, u8, u8, u8);
void func_8001ABE8(void);
void func_8001AC3C(void);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_80029658(s32, s32, s32, u8*);
void func_8002A550(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
s32 func_8002AE6C();
void func_8002AF04(char*, s32);
s32 func_8002D3D0(Mon89007678*);
s32 func_8002D430(Mon89007678*, s32);
void func_89007678(Screen89007678* arg0) {
    s32 y = arg0->y + 6;
    s32 x = arg0->x + 6;
    s32 count = func_8002D3D0(arg0->mon);
    s32 i;
    s32 n;
    s32 row;
    u8* tex;

    if (func_8002AE6C(arg0) == 0) {
        func_80029658(arg0->x, arg0->y + 0xF3, arg0->w, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(x, y, arg0->w - 0xC, 0x20, D_8900A874);
        func_80029028(x + 0x78, y + 0x20, arg0->w - 0x84, 0x78, D_8900A878);
        func_80029028(x, y + 0xF4, arg0->w - 0xC, 0x24, *(Color_RGBA8*)&D_8900A5BC);
        func_8002A550(x, y + 0x98, arg0->w - 0xC, 0x56, D_8900A87C, D_8900A880);
        func_8001AB6C();
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001A384(8, 0);
        func_8001ABE8();
        func_8001AAE4(0x7F, 0xA8, 0xFF, 0xFF);
        func_8001A944(x + 0xA, y + 5, arg0->mon->nickname);
        func_8001AC3C();
        func_8001A384(4, -1);
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        func_8001A944(x + 0x84, y + 9, D_89018E80);
        func_8001A944(x + 0x112, y + 9, D_89018E84);
        func_8001A384(8, 0);
        func_8001A944(x + 0xB2, y + 5, D_89018E88, arg0->mon->level);
        func_8001A944(x + 0x140, y + 5, D_89018E8C, arg0->mon->maxHp);
        func_8001A944(x + 0x88, y + 0x28, D_89018E90);
        if (func_8002D498((s32)arg0->mon, 1) != -1) {
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
            func_890074E0(D_8900A884[i].x + x, D_8900A884[i].y + y, func_8002D430(arg0->mon, i), D_8900A884[i].centered);
        }
        func_8001ABBC();
        func_890075E0(x + 0x9C, y + 0x40, (s32)arg0->mon, 0);
        func_890075E0(x + 0x9C, y + 0x7C, (s32)arg0->mon, 1);
        gSPDisplayList(gDisplayListHead++, D_80060290);
        for (i = 0; i < count; i++) {
            func_8001B884(D_8900A884[i].iconX + x, D_8900A884[i].y + y, 0x14, 0x14, (u8*)D_8900A884[i].icon, 0x14, 0x200000);
        }
        gSPDisplayList(gDisplayListHead++, D_80060398);
        if (arg0->title != NULL) {
            func_8001AB6C();
            func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
            func_8001A384(8, 0);
            func_8001A944(arg0->x + 0xE, arg0->y + 0x102, arg0->title);
            func_8001ABBC();
            func_8002AF04(arg0->button1, (arg0->selection == 0) ? 2 : 0);
            func_8002AF04(arg0->button2, (arg0->selection == 1) ? 2 : 0);
        }
        if (arg0->animLoaded == 0) {
            arg0->animLoaded = 1;
            func_80019008(arg0->anim, arg0->mon, 0x416D);
        }
        tex = func_800196F8(arg0->anim);
        func_800069CC();
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

s32 func_89007CD8(u8* arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (Ui_HandleHorizontalSelectionInput(arg0 + 0xA4) == 0) {
        dir = Ui_GetSelectionDirection(*(void**)(arg0 + 0xA4));
        if (dir == -1) {
            sp1C = -1;
        } else if (dir == 1) {
            if (*(s32*)(arg0 + 0xA8) == 1) {
                sp1C = -1;
            } else {
                sp1C = 1;
            }
        }
    }
    return sp1C;
}

extern Rgba8900806C D_8900A5BC;
extern Color_RGBA8 D_8900A8D4;
extern Color_RGBA8 D_8900A8D8;
extern Gfx D_80060270[];
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern Gfx D_80073450[];
extern u8 D_04011A60[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_8001BCB4(s32, s32, s32, s32, u8*, s32, s32);
void Trade_DrawDigitStrip(s32, s32, u8);
void func_80027F20(s32);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
u8* func_80018DEC(s32, s32);
void func_89007D54(s32 arg0, s32 arg1, u8* arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad[4]; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0 + 1, arg1 + 1, 0x58, 0x2E, *(Color_RGBA8*)&D_8900A5BC);
    func_80029028(arg0 + 1, arg1 + 0x2F, 0x58, 0x12, D_8900A8D4);
    func_80029028(arg0, arg1, 0x5A, 1, D_8900A8D8);
    func_80029028(arg0, arg1 + 0x41, 0x5A, 1, D_8900A8D8);
    func_80029028(arg0, arg1 + 1, 1, 0x40, D_8900A8D8);
    func_80029028(arg0 + 0x59, arg1 + 1, 1, 0x40, D_8900A8D8);
    if (arg2 != NULL) {
        if (arg4 & 0x10) {
            func_8002A0AC(arg0 + 3, arg1 + 3, 0x54, 0x2C, *(Color_RGBA8*)&D_8900A5BC);
            func_8002A0AC(arg0 + 3, arg1 + 0x2F, 0x54, 0x10, D_8900A8D4);
        }
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(arg0 + 4, arg1 + 0x24, 8, 0xA, D_04011A60, 8, 0);
        Trade_DrawDigitStrip(arg0 + 0xE, arg1 + 0x22, arg2[0x24]);
        func_8001AB6C();
        func_80027F20(arg4);
        func_8001A384(4, 0);
        func_8001A944(arg0 + 5, arg1 + 0x30, arg2 + 0x30);
        func_8001ABBC();
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(arg0 + 0x2C, arg1 + 4, 0x28, 0x28, func_80018DEC(arg5, arg3), 0x28, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }
}

typedef struct Str8900806C { char s[13]; } Str8900806C;
char* func_8000A460(char*, const char*);
void func_80018168(s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void func_8002DECC(s8*, s8*, s8*, void*, s32, s32, s32);
extern char D_89018EE8[];
extern char D_89018EF0[];
extern char D_89018EF8[];
extern s8 D_890289E0[];
void func_89007D54();
void func_8900806C(s8* arg0, s32 arg1, s32 arg2, u8* arg3, s32 arg4, s32 arg5, s32 arg6) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 i;
    u8* p;

    func_8000A460((char*)D_890289E0, (arg5 == 0) ? D_89018EE8 : D_89018EF0);
    *(Str8900806C*)(func_800566BC((char*)D_890289E0) + D_890289E0) = *(Str8900806C*)D_89018EF8;
    D_890289E0[func_800566BC((char*)D_890289E0) - 1] += arg6 + 1;
    func_8002A8C4(arg0, arg1, arg2, 0x228, 0x156);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x801;
    M2C_FIELD(arg0, s8**, 0x20) = D_890289E0;
    func_80027410(arg0 + 0x94, (s8*)arg3, 0x50, 0x1E, M2C_FIELD(arg3, s32*, 0x960));
    func_8002DECC(arg0 + 0x2C, arg0 + 0x94, arg0 + 0x54, func_89007D54, 6, 0x5A, 0x42);
    M2C_FIELD(arg0, s32*, 0x4C) |= 0x10000;
    func_80018168(arg4);
    for (p = arg3, i = 0; i < M2C_FIELD(arg3, s32*, 0x960); i++, p += 0x50) {
        Rgba8900806C c = D_8900A5BC;

        func_8001833C((unk_func_8001A024*)arg4, i, (BattleMon*)p, GPACK_RGBA5551(c.r, c.g, c.b, 1));
    }
    M2C_FIELD(arg0, s32*, 0x90) = arg4;
}

void func_800069CC();                            /* extern */
M2C_UNK func_800189C0(s32, M2C_UNK);                /* extern */
s32 func_8002AE6C();                                /* extern */
M2C_UNK func_8002E230(s8 *, s32, s32, s32, s32);  /* extern */

void func_89008284(s8 *arg0, s32 arg1) {
    if (func_8002AE6C() == 0) {
        if (!(arg1 & 0x10)) {
            func_800189C0(M2C_FIELD(arg0, s32 *, 0x90), 0);
            func_800069CC();
        }
        func_8002E230(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 6, arg1 | 0xFFED, M2C_FIELD(arg0, s32 *, 0x90));
    }
}

s32 func_8002E3F0(void*);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;
s32 func_890082FC(s32 arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (func_8002E3F0((u8*)arg0 + 0x2C) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if (dir == 1) {
            sp1C = M2C_FIELD(arg0, s32*, 0x34) + 1;
        }
    }
    return sp1C;
}

extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_8002A3F8(void*, s32, s32);
extern Color_RGBA8 D_8900A8F8;
extern Color_RGBA8 D_8900A900;
extern Color_RGBA8 D_8900A8DC[];

extern Color_RGBA8 D_8900A8E8;
extern Color_RGBA8 D_8900A8F0;
extern char D_89018F08[];
extern u8 D_80073614[];
extern u8 D_04011AB8[];
extern Gfx D_80073450[];
void func_8002B940(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, u8*, s32, s32);
void func_89008370(s32 arg0, s32 arg1, u8** arg2, s32 arg3, s32 arg4) {
    Color_RGBA8 color;
    s32 pad[2]; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xCE, 0x1A, D_8900A8E8);
    func_80029028(arg0, arg1, 0xCE, 1, D_8900A8F0);
    func_80029028(arg0, arg1 + 0x1B, 0xCE, 1, D_8900A8F0);
    if (arg4 & 0x18) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0xC8, 0x16, *(Color_RGBA8*)&D_8900A5BC);
    }
    func_8001AB6C();
    func_8001A384(8, 0);
    if (M2C_FIELD(*arg2, s32*, 0x960) == 0) {
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
    if (M2C_FIELD(*arg2, s32*, 0x960) > 0) {
        func_8002A3F8(D_80073614, arg0 + 0x78, arg1 + 4);
    }
    func_8002B940(arg0 + 0x98, arg1 + 8, M2C_FIELD(*arg2, s32*, 0x960), 2);
    func_8002B940(arg0 + 0xB3, arg1 + 8, 0x1E, 2);
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    func_8001BCB4(arg0 + 0xAA, arg1 + 0xA, 8, 0xA, D_04011AB8, 8, 0);
}

extern char D_89018F14[];
extern char D_89018F20[];
extern u8 D_80073634[];

void func_8900865C(s32 arg0, s32 arg1, u8** arg2, s32 arg3, s32 arg4) {
    Color_RGBA8 color;
    s32 pad[11]; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0x104, 0x36, D_8900A8F8);
    func_80029028(arg0, arg1, 0x104, 1, D_8900A900);
    func_80029028(arg0, arg1 + 0x37, 0x104, 1, D_8900A900);
    if (arg4 & 0x18) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0xFE, 0x32, *(Color_RGBA8*)&D_8900A5BC);
    }
    func_8001AB6C();
    func_8001A384(0x10, 0);
    if (M2C_FIELD(*arg2, s32*, 0x960) == 0) {
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
    func_8001A944(arg0 + 0xB0, arg1 + 0x14, D_89018F20, M2C_FIELD(*arg2, s32*, 0x960), 0x1E);
    func_8001ABBC();
    if (M2C_FIELD(*arg2, s32*, 0x960) > 0) {
        func_8002A3F8(D_80073634, arg0 + 0x8C, arg1 + 0x10);
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
void func_8002A550(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
s32 func_8002BC44(s32);
void func_80027F20(s32);
void func_890088F8(s32 x, s32 y, s32 flags, s32 kind) {
    ColorPair890088F8* c;

    if (flags & 2) {
        c = &D_8900A904;
    } else {
        c = &D_8900A90C;
    }
    func_8002A550(x, y, D_8900A914[kind], 0x2C, c->prim, c->env);
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
    func_80027F20(flags);
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

void func_8002B018(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_8002D880(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern Rgba8900806C D_8900A91C;
extern Rgba8900806C D_8900A920;
extern Rgba8900806C D_8900A580[];
extern u8 D_8900BFC0[];
extern u8 D_8900DAD0[];
extern u8 D_8900CD48[];
extern u8 D_8900E858[];
extern u8 D_8900F5E0[];
extern u8 D_89010368[];
extern char D_89018F4C[];
void func_89008AF4(s8* arg0, s32 x, s32 y, s8* arg3) {
    func_8002A8C4(arg0 + 4, x, y, 0x234, 0x172);
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = 0;
    M2C_FIELD(arg0, s32*, 0x18) = 0x801;
    M2C_FIELD(arg0, char**, 0x24) = D_89018F4C;
    func_8002A8C4(arg0 + 0x30, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 0x12C, M2C_FIELD(arg0, s32*, 0xC) - 0xC, 0x40);
    M2C_FIELD(arg0, s32*, 0x44) = 6;
    M2C_FIELD(arg0, Rgba8900806C*, 0x48) = D_8900A91C;
    M2C_FIELD(arg0, Rgba8900806C*, 0x4C) = D_8900A920;
    func_8002B018(arg0 + 0x50, x + 0xE4, y + 0xE, 0x36, 0x2A, 0x30, (s32)D_8900BFC0);
    M2C_FIELD(arg0, Rgba8900806C*, 0x68) = D_8900A580[0];
    M2C_FIELD(arg0, Rgba8900806C*, 0x6C) = D_8900A580[1];
    M2C_FIELD(arg0, Rgba8900806C*, 0x70) = D_8900A5BC;
    func_8002B018(arg0 + 0xA8, x + 0xE4, y + 0x3C, 0x36, 0x2A, 0x30, (s32)D_8900DAD0);
    M2C_FIELD(arg0, Rgba8900806C*, 0xC0) = D_8900A580[2];
    M2C_FIELD(arg0, Rgba8900806C*, 0xC4) = D_8900A580[3];
    M2C_FIELD(arg0, Rgba8900806C*, 0xC8) = D_8900A5BC;
    func_8002B018(arg0 + 0x7C, x + 0xE4, y + 0x6A, 0x36, 0x2A, 0x30, (s32)D_8900CD48);
    M2C_FIELD(arg0, Rgba8900806C*, 0x94) = D_8900A580[2];
    M2C_FIELD(arg0, Rgba8900806C*, 0x98) = D_8900A580[3];
    M2C_FIELD(arg0, Rgba8900806C*, 0x9C) = D_8900A5BC;
    func_8002B018(arg0 + 0xD4, x + 0xE4, y + 0x98, 0x36, 0x2A, 0x30, (s32)D_8900E858);
    M2C_FIELD(arg0, Rgba8900806C*, 0xEC) = D_8900A580[4];
    M2C_FIELD(arg0, Rgba8900806C*, 0xF0) = D_8900A580[5];
    M2C_FIELD(arg0, Rgba8900806C*, 0xF4) = D_8900A5BC;
    func_8002B018(arg0 + 0x100, x + 0xE4, y + 0xC6, 0x36, 0x2A, 0x30, (s32)D_8900F5E0);
    M2C_FIELD(arg0, Rgba8900806C*, 0x118) = D_8900A580[6];
    M2C_FIELD(arg0, Rgba8900806C*, 0x11C) = D_8900A580[7];
    M2C_FIELD(arg0, Rgba8900806C*, 0x120) = D_8900A5BC;
    func_8002B018(arg0 + 0x12C, x + 0xE4, y + 0xF4, 0x36, 0x2A, 0x30, (s32)D_89010368);
    M2C_FIELD(arg0, Rgba8900806C*, 0x144) = D_8900A580[8];
    M2C_FIELD(arg0, Rgba8900806C*, 0x148) = D_8900A580[9];
    M2C_FIELD(arg0, Rgba8900806C*, 0x14C) = D_8900A5BC;
    M2C_FIELD(arg0, s32*, 0x160) = 6;
    M2C_FIELD(arg0, s32*, 0x15C) = 0;
    M2C_FIELD(arg0, s32*, 0x158) = D_800603C0;
    func_8000B2F4(D_800603C0);
    func_8002D880(arg0 + 0x170, (s32)arg3, (s32)(arg0 + 0x1B8), (s32)func_89008370, 0xCE, 0x1C);
    M2C_FIELD(arg0, s32*, 0x190) |= 0x10000;
    func_8002D880(arg0 + 0x194, (s32)(arg3 + 0x10), (s32)(arg0 + 0x1C8), (s32)func_8900865C, 0x104, 0x38);
    M2C_FIELD(arg0, s32*, 0x1B4) |= 0x10000;
    M2C_FIELD(arg0, s32*, 0) = 1;
}

extern s32 D_8900A924[];
extern s32 D_8900A93C[];
void func_890019C8(s32, s32, s32, s32);
void func_89008EF0(s8* arg0) {
    if (M2C_FIELD(arg0, s32*, 0) == 1) {
        if (0) {}  // karodo
        func_890019C8(M2C_FIELD(arg0, s32*, 0x30) + 0x58, M2C_FIELD(arg0, s32*, 0x34), D_8900A924[M2C_FIELD((0, arg0), s32*, 0x15C)], D_8900A93C[M2C_FIELD(arg0, s32*, 0x15C)]); // FAKE: comma expression
    }
}

void func_8002A8E0(s8*);
void func_80029658(s32, s32, s32, u8*);
void func_800295E8(s32, s32, s32, s32, u8*);
void func_8002B054(s8*, s32);
void func_8002DAD8(s8*, s32, s32, s32, s32);
void func_8002D024(s8*);
extern u8 D_8007356C[];
extern u8 D_800735C4[];
void func_89008F4C(s8* arg0) {
    s32 sel = 0x10;
    s32 flags[2];
    s32 pad[2]; // FAKE
    s32 a;
    s32 b;

    if (func_8002AE6C(arg0 + 4) != 0) {
        return;
    }
    func_8002A8E0(arg0 + 0x30);
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) - 0xC, 0xA, *(Color_RGBA8*)&D_8900A5BC);
    func_80029028(M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 0x11C, M2C_FIELD(arg0, s32*, 0xC) - 0xC, 0xA, *(Color_RGBA8*)&D_8900A5BC);
    func_80029028(M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 0x10, 0xA, 0x10C, *(Color_RGBA8*)&D_8900A5BC);
    func_80029028(M2C_FIELD(arg0, s32*, 0xC) + M2C_FIELD(arg0, s32*, 4) - 0x10, M2C_FIELD(arg0, s32*, 8) + 0x10, 0xA, 0x10C, *(Color_RGBA8*)&D_8900A5BC);
    func_80029028(M2C_FIELD(arg0, s32*, 4) + 0xDE, M2C_FIELD(arg0, s32*, 8) + 0x10, 0x42, 0x10C, *(Color_RGBA8*)&D_8900A5BC);
    func_80029658(M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 8) + 0x125, M2C_FIELD(arg0, s32*, 0xC), D_8007356C);
    func_800295E8(M2C_FIELD(arg0, s32*, 4) + 0xE, M2C_FIELD(arg0, s32*, 8) + 0xE, 0xD2, 0x110, D_800735C4);
    func_800295E8(M2C_FIELD(arg0, s32*, 4) + 0x11E, M2C_FIELD(arg0, s32*, 8) + 0xE, 0x108, 0x110, D_800735C4);
    flags[1] = flags[0] = 0xFFED;
    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 1:
            sel = 2;
            break;
        case 2:
            flags[(M2C_FIELD(arg0, s32*, 0x15C) == 1) ? 1 : 0] |= 2;
            break;
        case 3:
        case 4:
            if (M2C_FIELD(arg0, s32*, 0x15C) == 1) {
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
            flags[(M2C_FIELD(arg0, s32*, 0x168) < 8) ? 0 : 1] |= 2;
            break;
    }
    func_8002B054(arg0 + 0x50, (M2C_FIELD(arg0, s32*, 0x15C) == 5) ? sel : 0);
    func_8002B054(arg0 + 0xA8, (M2C_FIELD(arg0, s32*, 0x15C) == 0) ? sel : 0);
    func_8002B054(arg0 + 0x7C, (M2C_FIELD(arg0, s32*, 0x15C) == 1) ? sel : 0);
    func_8002B054(arg0 + 0xD4, (M2C_FIELD(arg0, s32*, 0x15C) == 2) ? sel : 0);
    func_8002B054(arg0 + 0x100, (M2C_FIELD(arg0, s32*, 0x15C) == 3) ? sel : 0);
    func_8002B054(arg0 + 0x12C, (M2C_FIELD(arg0, s32*, 0x15C) == 4) ? sel : 0);
    func_890088F8(M2C_FIELD(arg0, s32*, 4) + 0x10, M2C_FIELD(arg0, s32*, 8) + 0x10, 2, 0);
    func_890088F8(M2C_FIELD(arg0, s32*, 4) + 0x120, M2C_FIELD(arg0, s32*, 8) + 0x10, 2, 1);
    func_8002DAD8(arg0 + 0x170, M2C_FIELD(arg0, s32*, 4) + 0x10, M2C_FIELD(arg0, s32*, 8) + 0x3C, flags[0], 0);
    func_8002DAD8(arg0 + 0x194, M2C_FIELD(arg0, s32*, 4) + 0x120, M2C_FIELD(arg0, s32*, 8) + 0x3C, flags[1], 0);
    func_89008EF0(arg0);
    if (M2C_FIELD(arg0, s32*, 0) == 7) {
        func_8002D024(arg0 + 0x1E0);
    }
}

s32 func_8002DCE0(void* arg0);

s32 func_890093AC(void* arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (func_8002DCE0(arg0) == 0) {
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

typedef struct {
    /* 0x0 */ s32 value;
    /* 0x4 */ s32 flag;
} SwapEntry;

typedef struct {
    /* 0x0 */ SwapEntry** entries;
    /* 0x4 */ char unk04[4];
    /* 0x8 */ s32 index;
} SwapList;

/**
 * Swaps the first word of the entry selected by the list at arg0 + 0x1D8 with
 * that of the entry selected by the list at arg0 + 0x1DC, then sets the second
 * word (flag) of both entries to 1. Each list is {Entry** entries, ?, index};
 * the entry is `(*entries)[index]` with 8-byte entries. The operands of the
 * pointer addition are written `index + *entries` because that order gives the
 * retail temp numbering.
 */
void func_89009414(void* arg0) {
    SwapEntry* a;
    SwapEntry* b;
    s32 tmp;

    a = M2C_FIELD(arg0, SwapList**, 0x1D8)->index + *M2C_FIELD(arg0, SwapList**, 0x1D8)->entries;
    b = M2C_FIELD(arg0, SwapList**, 0x1DC)->index + *M2C_FIELD(arg0, SwapList**, 0x1DC)->entries;
    tmp = b->value;
    b->value = a->value;
    a->flag = 1;
    a->value = tmp;
    b->flag = 1;
}

typedef struct Entry89009464 {
    s32 unk_00;
    s32 unk_04;
} Entry89009464;
void func_89009464(s32 arg0) {
    Entry89009464* a = (Entry89009464*)(M2C_FIELD(arg0, s32*, 0x218) * 8 + **M2C_FIELD(arg0, s32***, 0x1D8));
    Entry89009464* b = (Entry89009464*)(M2C_FIELD(arg0, s32**, 0x1D8)[2] * 8 + **M2C_FIELD(arg0, s32***, 0x1D8));
    s32 temp = b->unk_00;

    b->unk_00 = a->unk_00;
    a->unk_04 = 1;
    a->unk_00 = temp;
    b->unk_04 = 1;
}

typedef struct LabPCBoxList890094A8 {
    /* 0x0 */ LabPCBoxEntry* entries;
    /* 0x4 */ s32 unk_04;
    /* 0x8 */ s32 count;
} LabPCBoxList890094A8;
s32 func_8002DDFC(s8 *);
s32 func_890094A8(s8* arg0) {
    s32 i;
    LabPCBoxList890094A8* list = M2C_FIELD(arg0, LabPCBoxList890094A8**, 0);
    s32 n = list->count;
    LabPCBoxEntry* e = list->entries;

    for (i = 0; i < n; i++, e++) {
        if (M2C_FIELD(e->box, s32*, 0x960) == 0) {
            M2C_FIELD(arg0, u16**, 4)[i] |= 1;
        }
    }
    M2C_FIELD(arg0, s32*, 8) = 0;
    return func_8002DDFC(arg0);
}

typedef struct LabPCBoxList890095DC {
    /* 0x0 */ LabPCBoxEntry* entries;
    /* 0x4 */ s32 unk_04;
    /* 0x8 */ s32 count;
} LabPCBoxList890095DC;

void func_890095DC(s8* arg0) {
    s32 i;
    LabPCBoxList890095DC* list = M2C_FIELD(arg0, LabPCBoxList890095DC**, 0);
    s32 n = list->count;
    LabPCBoxEntry* e = list->entries;

    for (i = 0; i < n; i++, e++) {
        if (M2C_FIELD(e->box, s32*, 0x960) > 0) {
            M2C_FIELD(arg0, u16**, 4)[i] |= 1;
        }
    }
    M2C_FIELD(arg0, s32*, 8) = 0;
    func_8002DDFC(arg0);
}

void func_89009710(s8 *arg0, s8 *arg1, s8 *arg2) {
    if (arg1 != NULL) {
        M2C_FIELD(arg0, s8 **, 0x1D8) = arg1;
        M2C_FIELD(arg1, s32 *, 8) = 0;
    }
    if (arg2 != NULL) {
        M2C_FIELD(arg0, s8 **, 0x1DC) = arg2;
        M2C_FIELD(arg2, s32 *, 8) = 0;
    }
}

s32 func_8002B204();
s32 func_89009738(u8 *arg0, s32 arg1) {
    s32 r;
    s32 idx;
    s32 pos;

    for (r = func_8002B204(arg0 + 0x164, arg1); r != 0; r = func_8002B204(arg0 + 0x164, arg1)) {
        pos = *(s32 *)(arg0 + 0x168);
        idx = pos - 8;
        if (pos < 8) {
            *(u8 **)(arg0 + 0x1D8) = arg0 + 0x170;
            idx = pos;
        } else {
            *(u8 **)(arg0 + 0x1D8) = arg0 + 0x194;
        }
        if (!((*(u16 **)(*(u8 **)(arg0 + 0x1D8) + 4))[idx] & 1)) {
            break;
        }
    }
    return r;
}

s32 func_8000B30C(void);
s32 func_8002B2B0(s8*);
void func_8002CEEC(s8*, void*, s32, s32, s32);
s32 Ui_CheckConfirmPressed(s8*);
void func_8002D900(s8*);
extern void* D_8900A954[];
extern u8 D_8900A96C[];

s32 func_890097E0(s8* arg0) {
    s32 ret = 0;
    s32 pad; // FAKE
    s32 next = 0;
    s32 back = 0;
    s32 pad2; // FAKE
    s32 r;
    s8* list;
    LabPCBoxEntry* e;

    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 1:
            if (func_8002B2B0(arg0 + 0x158) == 0) {
                r = func_8002BC14(D_800603C0);
                if (r == -1) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (r == 1) {
                    switch (M2C_FIELD(arg0, u32*, 0x15C)) {
                        case 5:
                            func_8003F6AC(3);
                            ret = -1;
                            break;
                        case 0:
                            if (LabPC_AllBoxesEmpty(M2C_FIELD(arg0, s8**, 0x170)) != 0) {
                                func_8003F6AC(8);
                                M2C_FIELD(arg0, s32*, 0) = 7;
                                func_8002CEEC(arg0 + 0x1E0, D_8900A954[M2C_FIELD(arg0, u32*, 0x15C)], 0, 1, 0);
                            } else if (LabPC_NoEmptyBoxAvailable(M2C_FIELD(arg0, s8**, 0x194)) != 0) {
                                func_8003F6AC(8);
                                M2C_FIELD(arg0, s32*, 0) = 7;
                                func_8002CEEC(arg0 + 0x1E0, D_8900A96C, 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 2;
                                func_89009710(arg0, arg0 + 0x170, arg0 + 0x194);
                            }
                            break;
                        case 1:
                            if (LabPC_AllBoxesEmpty(M2C_FIELD(arg0, s8**, 0x194)) != 0) {
                                func_8003F6AC(8);
                                M2C_FIELD(arg0, s32*, 0) = 7;
                                func_8002CEEC(arg0 + 0x1E0, D_8900A954[M2C_FIELD(arg0, u32*, 0x15C)], 0, 1, 0);
                            } else if (LabPC_NoEmptyBoxAvailable(M2C_FIELD(arg0, s8**, 0x170)) != 0) {
                                func_8003F6AC(8);
                                M2C_FIELD(arg0, s32*, 0) = 7;
                                func_8002CEEC(arg0 + 0x1E0, D_8900A96C, 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 2;
                                func_89009710(arg0, arg0 + 0x194, arg0 + 0x170);
                            }
                            break;
                        case 2:
                            if (LabPC_AllBoxesEmpty(M2C_FIELD(arg0, s8**, 0x170)) != 0) {
                                func_8003F6AC(8);
                                M2C_FIELD(arg0, s32*, 0) = 7;
                                func_8002CEEC(arg0 + 0x1E0, D_8900A954[M2C_FIELD(arg0, u32*, 0x15C)], 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                M2C_FIELD(arg0, s32*, 0) = 2;
                                func_89009710(arg0, arg0 + 0x170, NULL);
                            }
                            break;
                        case 3:
                            if ((LabPC_AllBoxesEmpty(M2C_FIELD(arg0, s8**, 0x170)) != 0) ||
                                (LabPC_AllBoxesEmpty(M2C_FIELD(arg0, s8**, 0x194)) != 0)) {
                                func_8003F6AC(8);
                                M2C_FIELD(arg0, s32*, 0) = 7;
                                func_8002CEEC(arg0 + 0x1E0, D_8900A954[M2C_FIELD(arg0, u32*, 0x15C)], 0, 1, 0);
                            } else {
                                func_8003F6AC(2);
                                next = 2;
                                func_89009710(arg0, arg0 + 0x170, arg0 + 0x194);
                            }
                            break;
                        case 4:
                            if ((LabPC_AllBoxesEmpty(M2C_FIELD(arg0, s8**, 0x170)) != 0) &&
                                (LabPC_AllBoxesEmpty(M2C_FIELD(arg0, s8**, 0x194)) != 0)) {
                                func_8003F6AC(8);
                                M2C_FIELD(arg0, s32*, 0) = 7;
                                func_8002CEEC(arg0 + 0x1E0, D_8900A954[M2C_FIELD(arg0, u32*, 0x15C)], 0, 1, 0);
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
            r = func_890093AC(M2C_FIELD(arg0, s8**, 0x1D8));
            if (r == -1) {
                back = 1;
            } else if (r == 1) {
                if ((M2C_FIELD(arg0, u32*, 0x15C) == 0) || (M2C_FIELD(arg0, u32*, 0x15C) == 1)) {
                    func_8003F6AC(2);
                    next = 3;
                } else if (M2C_FIELD(arg0, u32*, 0x15C) == 3) {
                    func_8003F6AC(2);
                    next = 4;
                } else {
                    func_8003F6AC(2);
                    list = M2C_FIELD(arg0, s8**, 0x1D8);
                    M2C_FIELD(list, u16**, 4)[M2C_FIELD(list, s32*, 8)] |= 8;
                    M2C_FIELD(arg0, s32*, 0x218) = M2C_FIELD(M2C_FIELD(arg0, s8**, 0x1D8), s32*, 8);
                    M2C_FIELD(arg0, s32*, 0) = 5;
                }
            }
            break;

        case 3:
            r = func_890093AC(M2C_FIELD(arg0, s8**, 0x1DC));
            if (r == -1) {
                M2C_FIELD(arg0, s32*, 0) = 2;
            } else if (r == 1) {
                e = M2C_FIELD(M2C_FIELD(arg0, s8**, 0x1DC), s32*, 8) + M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x1DC), s8**, 0), LabPCBoxEntry**, 0);
                if (M2C_FIELD(e->box, s32*, 0x960) > 0) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(0x18);
                    func_89009414(arg0);
                    if ((LabPC_AllBoxesEmpty(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x1D8), s8**, 0)) != 0) ||
                        (LabPC_NoEmptyBoxAvailable(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x1DC), s8**, 0)) != 0)) {
                        back = 1;
                    } else {
                        next = 2;
                    }
                }
            }
            break;

        case 5:
            r = func_890093AC(M2C_FIELD(arg0, s8**, 0x1D8));
            if (r == -1) {
                M2C_FIELD(M2C_FIELD(arg0, s8**, 0x1D8), u16**, 4)[M2C_FIELD(arg0, s32*, 0x218)] &= ~8;
                M2C_FIELD(arg0, s32*, 0) = 2;
            } else if (r == 1) {
                func_8003F6AC(0x18);
                func_89009464(arg0);
                M2C_FIELD(M2C_FIELD(arg0, s8**, 0x1D8), u16**, 4)[M2C_FIELD(arg0, s32*, 0x218)] &= ~8;
                M2C_FIELD(arg0, s32*, 0) = 2;
            }
            break;

        case 4:
            r = func_890093AC(M2C_FIELD(arg0, s8**, 0x1DC));
            if (r == -1) {
                M2C_FIELD(arg0, s32*, 0) = 2;
            } else if (r == 1) {
                e = M2C_FIELD(M2C_FIELD(arg0, s8**, 0x1DC), s32*, 8) + M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s8**, 0x1DC), s8**, 0), LabPCBoxEntry**, 0);
                if (M2C_FIELD(e->box, s32*, 0x960) == 0) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(0x18);
                    func_89009414(arg0);
                    M2C_FIELD(arg0, s32*, 0) = 2;
                }
            }
            break;

        case 6:
            if (func_89009738(arg0, func_8000B30C() & 0xFFFF) != 0) {
                r = M2C_FIELD(arg0, s32*, 0x168);
                if (r < 8) {
                    M2C_FIELD(arg0, s8**, 0x1D8) = arg0 + 0x170;
                    M2C_FIELD(arg0, s32*, 0x178) = r;
                } else {
                    M2C_FIELD(arg0, s8**, 0x1D8) = arg0 + 0x194;
                    M2C_FIELD(arg0, s32*, 0x19C) = r - 8;
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
            if (Ui_CheckConfirmPressed(arg0 + 0x1E0) == 1) {
                M2C_FIELD(arg0, s32*, 0) = 1;
            }
            break;
    }

    if (back > 0) {
        if (back == 1) {
            func_8002D900(arg0 + 0x170);
            func_8002D900(arg0 + 0x194);
        }
        M2C_FIELD(arg0, s32*, 0) = back;
    }
    if (next > 0) {
        switch (next) {
            case 2:
            func_8002D900(arg0 + 0x170);
            func_8002D900(arg0 + 0x194);
            func_890094A8(M2C_FIELD(arg0, s8**, 0x1D8));
            switch (M2C_FIELD(arg0, u32*, 0x15C)) {
                case 0:
                case 1:
                    func_890095DC(M2C_FIELD(arg0, s8**, 0x1DC));
                    break;
                case 3:
                    func_890094A8(M2C_FIELD(arg0, s8**, 0x1DC));
                    break;
            }
            break;
            case 6: {
            s32 a;
            s32 b;
            func_8002D900(arg0 + 0x170);
            func_8002D900(arg0 + 0x194);
            a = func_890094A8(arg0 + 0x170);
            b = func_890094A8(arg0 + 0x194);
            if (a >= 0) {
                M2C_FIELD(arg0, s32*, 0x16C) = 0xC;
                M2C_FIELD(arg0, s32*, 0x168) = a;
                M2C_FIELD(arg0, s32*, 0x164) = D_800603C0;
                func_8000B2F4(D_800603C0);
                M2C_FIELD(arg0, s8**, 0x1D8) = arg0 + 0x170;
            } else {
                M2C_FIELD(arg0, s32*, 0x168) = b + 8;
                M2C_FIELD(arg0, s32*, 0x16C) = 0xC;
                M2C_FIELD(arg0, s32*, 0x164) = D_800603C0;
                func_8000B2F4(D_800603C0);
                M2C_FIELD(arg0, s8**, 0x1D8) = arg0 + 0x194;
            }
            } break;
        }
        M2C_FIELD(arg0, s32*, 0) = next;
    }
    return ret;
}

typedef struct Ent8900A014 { s32 unk0; s32 unk4; } Ent8900A014;
s8* func_80017860(s32);
s32 func_80017FDC(s8*, s32, s32, s32);
void PokeIcon_OpenModelArchives(void);
s32 func_80018F2C(s8*, s32, s32, s32, s32, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void func_89008AF4(s8*, s32, s32, s8*);
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];

void func_8900A014(s8* arg0) {
    s32 i;

    main_pool_push_state('PBOX');
    M2C_FIELD(arg0, s8**, 0x7518) = func_80017860(1);
    M2C_FIELD(arg0, s32*, 0x751C) = func_80018F2C(M2C_FIELD(arg0, s8**, 0x7518), 0x80, 0x78, 0, 0, 0x78, 0x78, 0);
    M2C_FIELD(arg0, s32*, 0x7520) = func_80017FDC(M2C_FIELD(arg0, s8**, 0x7518), 0x1E, 0x28, 0x28);
    PokeIcon_OpenModelArchives();
    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    func_89007264(arg0 + 0x3E8, 0x21, D_89019108, 8);
    func_89007264(arg0 + 0x4F08, 0x11, 0, 4);
    for (i = 0; i < 8; i++) {
        ((Ent8900A014*)(arg0 + 0x7498))[i].unk0 = (s32)(arg0 + 0x3E8 + i * 0x964);
        ((Ent8900A014*)(arg0 + 0x7498))[i].unk4 = 0;
    }
    for (i = 0; i < 4; i++) {
        ((Ent8900A014*)(arg0 + 0x74D8))[i].unk0 = (s32)(arg0 + 0x4F08 + i * 0x964);
        ((Ent8900A014*)(arg0 + 0x74D8))[i].unk4 = 0;
    }
    func_80027410(arg0 + 0x74F8, arg0 + 0x7498, 8, 8, 8);
    func_80027410(arg0 + 0x7508, arg0 + 0x74D8, 8, 4, 4);
    func_89008AF4(arg0 + 4, 0x26, 0x53, arg0 + 0x74F8);
    M2C_FIELD(arg0, s32*, 0) = 1;
}

M2C_UNK func_80002620(M2C_UNK);                     /* extern */

void func_8900A1A4(s32 arg0) {
    func_80002620(0x50424F58);
}

void func_8002C064(s32, s32, s32, s32, s32);
extern u8 D_8900A5B8[];
void func_89008F4C(s8*);
void func_8002CAD0(s8*);
void func_89007678(Screen89007678*);
void func_8900A1CC(s8* arg0) {
    func_800069CC();
    func_8002C064(0x38, 0x1E0, D_8900A5B8[0], D_8900A5B8[1], D_8900A5B8[2]);
    switch (*(s32*)arg0) {
        case 1:
            func_89008F4C(arg0 + 4);
            break;
        case 4:
            func_89008F4C(arg0 + 4);
            func_8002CAD0(arg0 + 0x220);
            break;
        case 2:
            func_89008284(arg0 + 0x284, 2);
            break;
        case 3:
            func_89008284(arg0 + 0x284, 0x10);
            func_89007678((Screen89007678*)(arg0 + 0x328));
            break;
    }
}

typedef struct Ent8900A298 {
    s32 unk0;
    s32 unk4;
} Ent8900A298;

s32 func_8900A298(s8* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (((Ent8900A298*)(arg0 + 0x749C))[i].unk0 != 0) {
            return 1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (((Ent8900A298*)(arg0 + 0x74DC))[i].unk0 != 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_890097E0(s8*);
void func_8002CA34(s8*, s32, s32);
void func_8002CC44(s8*);
s32 func_8002CD7C(s8*);
s32 func_8900A298(s8* arg0);
void func_890070BC(s8* arg0);
void func_8900806C(s8* arg0, s32 arg1, s32 arg2, u8* arg3, s32 arg4, s32 arg5, s32 arg6);
void func_89007374(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6);
typedef struct Item8900A324 {
    u8 unk0;
    char unk1[0x4F];
} Item8900A324;
typedef struct Ent8900A324 {
    Item8900A324* ptr;
    s32 unk4;
} Ent8900A324;
typedef struct List8900A324 {
    Ent8900A324** tbl;
    s32 unk4;
    s32 idx;
} List8900A324;
typedef struct Obj8900A324 {
    /* 0x0000 */ s32 state;
    /* 0x0004 */ char unk4[0x168];
    /* 0x016C */ s32 unk16C;
    /* 0x0170 */ char unk170[0x6C];
    /* 0x01DC */ List8900A324* list;
    /* 0x01E0 */ char unk1E0[0xD8];
    /* 0x02B8 */ s32 sel;
    /* 0x02BC */ char unk2BC[0x7260];
    /* 0x751C */ u16* unk751C;
    /* 0x7520 */ s32 unk7520;
} Obj8900A324;
#define OBJ ((Obj8900A324*)arg0)
s32 func_8900A324(s8* arg0) {
    s32 ret = 0;
    s32 r;
    Ent8900A324* ent;
    Ent8900A324* ent2;
    Item8900A324* entry;

    switch (OBJ->state) {
        case 1:
            r = func_890097E0(arg0 + 4);
            if (r == -1) {
                if (func_8900A298(arg0) != 0) {
                    OBJ->state = 4;
                    func_8002CA34(arg0 + 0x220, 0xCA, 0xAD);
                } else {
                    ret = 1;
                }
            } else if (r == 2) {
                ent = OBJ->list->idx + *OBJ->list->tbl;
                OBJ->state = 2;
                func_8900806C(arg0 + 0x284, 0x2C, 0x5F, (u8*)ent->ptr, OBJ->unk7520,
                              (OBJ->unk16C < 8) ? 0 : 1, OBJ->list->idx);
            }
            break;
        case 4:
            r = func_8002CD7C(arg0 + 0x220);
            if (r == -1) {
                OBJ->state = 1;
            } else if (r > 0) {
                ret = 1;
                switch (r) {
                    case 1:
                        func_8002CC44(arg0 + 0x220);
                        func_890070BC(arg0);
                        break;
                    case 2:
                        break;
                }
            }
            break;
        case 2:
            r = func_890082FC((s32)(arg0 + 0x284));
            if (r == -1) {
                OBJ->state = 1;
            } else if (r > 0) {
                ent2 = OBJ->list->idx + *OBJ->list->tbl;
                entry = &ent2->ptr[OBJ->sel];
                if ((entry->unk0 <= 0) || (entry->unk0 >= 0x98)) {
                    func_8003F6AC(8);
                } else {
                    func_8003F6AC(2);
                    OBJ->state = 3;
                    func_89007374(arg0 + 0x328, 0x69, 0x7D, (s32)entry, 0, D_800603C0, OBJ->unk751C);
                }
            }
            break;
        case 3:
            r = func_8002BC14(D_800603C0);
            if ((r == -1) || (r == 1)) {
                func_8003F6AC(3);
                OBJ->state = 2;
            }
            break;
    }
    return ret;
}
