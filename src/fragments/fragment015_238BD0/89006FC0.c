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

#ifdef NON_MATCHING
/* TODO: decompile func_890070BC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890070BC.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_89007374; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89007374.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_8900806C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_8900806C.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_890088F8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890088F8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89008AF4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89008AF4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89008EF0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89008EF0.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_890094A8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890094A8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_890095DC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890095DC.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_89009738; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_89009738.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_890097E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_890097E0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8900A014; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_8900A014.s")
#endif

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

#ifdef NON_MATCHING
/* TODO: decompile func_8900A298; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_8900A298.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8900A324; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment015_238BD0/func_8900A324.s")
#endif
