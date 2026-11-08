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
  s32 *new_var2;
  int new_var;
  s32 var_s0;
  arg0 = arg0;
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

s32 func_890072E4(s8* arg0) {
    s32 i;
    LabPCBoxEntry* var_a0 = M2C_FIELD(arg0, LabPCBoxEntry**, 0);

    for (i = 0; i < M2C_FIELD(arg0, s32*, 8); i++, var_a0++) {
        if (M2C_FIELD(var_a0->box, s32*, 0x960) == 0) {
            return 0;
        }
    }

    return 1;
}

s32 func_8900732C(s8* arg0) {
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

#ifdef NON_MATCHING
/* TODO: decompile func_89007678; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89007678.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_89007D54; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89007D54.s")
#endif

typedef struct Str8900806C { char s[13]; } Str8900806C;
typedef struct Rgba8900806C { u8 r, g, b, a; } Rgba8900806C;
char* func_8000A460(char*, const char*);
void func_80018168(s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void func_8002DECC(s8*, s8*, s8*, void*, s32, s32, s32);
extern Rgba8900806C D_8900A5BC;
extern char D_89018EE8[];
extern char D_89018EF0[];
extern char D_89018EF8[];
extern s8 D_890289E0[];
void func_89007D54();
void func_8900806C(s8* arg0, s32 arg1, s32 arg2, u8* arg3, s32 arg4, s32 arg5, s32 arg6) {
    UNUSED s32 pad[2];
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

M2C_UNK func_800069CC();                            /* extern */
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

#ifdef NON_MATCHING
/* TODO: decompile func_89008370; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89008370.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8900865C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_8900865C.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_89008AF4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89008AF4.s")
#endif

extern s32 D_8900A924[];
extern s32 D_8900A93C[];
void func_890019C8(s32, s32, s32, s32);
void func_89008EF0(s8* arg0) {
    if (M2C_FIELD(arg0, s32*, 0) == 1) {
        if (0) {}  // karodo
        func_890019C8(M2C_FIELD(arg0, s32*, 0x30) + 0x58, M2C_FIELD(arg0, s32*, 0x34), D_8900A924[M2C_FIELD((0, arg0), s32*, 0x15C)], D_8900A93C[M2C_FIELD(arg0, s32*, 0x15C)]);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_89008F4C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89008F4C.s")
#endif

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
void func_8002DDFC(s8 *);
void func_890094A8(s8* arg0) {
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
    func_8002DDFC(arg0);
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

#ifdef NON_MATCHING
/* TODO: decompile func_890097E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890097E0.s")
#endif

typedef struct Ent8900A014 { s32 unk0; s32 unk4; } Ent8900A014;
s8* func_80017860(s32);
s32 func_80017FDC(s8*, s32, s32, s32);
void func_80017934(void);
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
    func_80017934();
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
void func_89007678(s8*);
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
            func_89007678(arg0 + 0x328);
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

#ifdef NON_MATCHING
/* TODO: decompile func_8900A324; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_8900A324.s")
#endif
