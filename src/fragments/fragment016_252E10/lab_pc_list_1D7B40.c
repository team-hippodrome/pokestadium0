/* Stadium Zero fragment016_252E10. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc_list/lab_pc_list_1D7B40.c. */

#include "fragments/lab_pc_list/lab_pc_list.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "audio_sfx.h"
#include "hal_libc.h"
#include "memmap.h"
#include "memory.h"
#include "pokemon_stats.h"
extern u8 D_8910D7D0[];
typedef struct unk_func_88309614 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
} unk_func_88309614;
typedef struct unk_func_88313894 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ unk_func_8830867C_02C_0CC_000_000* unk_0C;
    /* 0x10 */ char unk10[0xC];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ unk_func_88313894_020 unk_20;
    /* 0x40 */ unk_func_88313894_020 unk_40;
} unk_func_88313894;

#include "m2c_macros.h"

void func_891053E0(void);
void func_89108F0C(void);

extern Color_RGBA8 D_8910A910;
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_80027F20(s32);

void func_89104C70(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 temp_v0 = *arg5;

    if (arg4 & 8) {
        func_8002A0AC(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x16, D_8910A910);
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_89104D14; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89104D14.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89104E38; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89104E38.s")
#endif

M2C_UNK func_8002DC04(s32);                         /* extern */

void func_89104E94(s32 arg0) {
    func_8002DC04(arg0 + 0x2C);
}

#ifdef NON_MATCHING
/* TODO: decompile func_89104EB4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89104EB4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89104FC0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89104FC0.s")
#endif

extern s32 D_8910A920[5];
void BattleMoveListWidget_DisableRestrictedMoves(unk_func_8830867C_04C_078* arg0) {
    s32 j;
    s32 i;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (M2C_FIELD(arg0, s32*, 0x60 + i * 4) == D_8910A920[j]) {
                M2C_FIELD(arg0, u16*, 0x70 + i * 2) |= 1;
                break;
            }
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_891051A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891051A4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89105200; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89105200.s")
#endif

void func_89105340(s8 *arg0, s32 arg1, s32 arg2)
{
  u16 *temp_v0;
  int new_var;
  *((s32 *) (((s8 *) arg0) + 0x7C)) = arg1;
  new_var = arg1 * 4;
  *((s32 *) (((s8 *) arg0) + 0x80)) = (s32) (arg2 - 1);
  if ((*((s32 *) (((s8 *) (arg0 + new_var)) + 0x60))) == (-1))
  {
    *((s32 *) (((s8 *) arg0) + 0x78)) = 0x3C;
  }
  else
  {
    *((s32 *) (((s8 *) arg0) + 0x78)) = 0x3C;
  }
  temp_v0 = (*((s32 *) (((s8 *) arg0) + 0x30))) + (arg1 * 2);
  *temp_v0 |= 0x300;
}

M2C_UNK func_8002DC04(s32);                         /* extern */

void func_89105390(s32 arg0) {
    func_8002DC04(arg0 + 0x2C);
}

s32 func_891053B0(s8 *arg0) {
    s32 var_v1;

    var_v1 = 0x100;
    if (M2C_FIELD(arg0, s32 *, 0xC) != 0) {
        var_v1 = 0x108;
    }
    if (M2C_FIELD(arg0, s32 *, 0x1C) > 0) {
        var_v1 &= ~0x100;
    }
    return var_v1;
}

void func_891053E0(void) {
}

void BattleInfoWidget_UpdateEntryFlags(unk_func_8830867C_034* arg0) {
    s32 i;
    s8** sub = &M2C_FIELD(arg0, s8**, 0x20);
    s8* var_s2 = M2C_FIELD(*sub, s8**, 0);

    for (i = 0; i < M2C_FIELD(*sub, s32*, 8); i++, var_s2 += 0x20) {
        M2C_FIELD(arg0, u16**, 0x24)[i] = 0;
        M2C_FIELD(arg0, u16**, 0x24)[i] |= func_891053B0(var_s2);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8910548C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_8910548C.s")
#endif

void func_89105504(s32 arg0) {
    s32 i;
    s32* entry = *M2C_FIELD(arg0, s32**, 0x20);

    for (i = 0; i < M2C_FIELD(arg0, s32**, 0x20)[2]; i++) {
        entry[3] = (M2C_FIELD(arg0, u16**, 0x24)[i] & 8) != 0;
        entry += 8;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_89105560; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89105560.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8910576C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_8910576C.s")
#endif

M2C_UNK func_800295E8(s32, s32, s32, s32, M2C_UNK *); /* extern */
M2C_UNK func_8002A8E0(s8 *);                      /* extern */
M2C_UNK func_8002DAD8(s8 *, s32, s32, s32, s8 *); /* extern */
extern M2C_UNK D_80073554;

void func_891057FC(s8 *arg0, s32 arg1) {
    func_800295E8(M2C_FIELD(arg0, s32 *, 0) - 6, M2C_FIELD(arg0, s32 *, 4) - 6, M2C_FIELD(arg0, s32 *, 8) + 0xC, M2C_FIELD(arg0, s32 *, 0xC) + 0xC, &D_80073554);
    func_8002A8E0(arg0);
    func_8002DAD8(arg0 + 0x20, M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4) + 4, arg1 | 0xFFED, arg0);
}

M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;

/**
 * List-menu input handler (same family as func_8A20093C). arg0 is the menu object (passed as
 * an integer address here, as elsewhere in this file). Calls func_8002DC04(arg0 + 0x20) and
 * acts on its result: 0x200 plays sound func_8003F6AC(1) and returns 2. 0 reads the button
 * halfword at D_800603C0 + 8: if bit 0x8000 is set it plays sound 2, toggles bit 3 of the
 * halfword table entry arg0->0x24[arg0->0x28] and returns 1; otherwise if bit 0x4000 is set it
 * plays sound 3 and returns -1. Any other case returns 0. (The button-bit names are not
 * established, so they are left as raw masks.)
 */
s32 func_8910587C(s32 arg0) {
    s32 ret = 0;
    s32 res;
    s32 buttons;
    u16* entry;

    res = func_8002DC04(arg0 + 0x20);
    if (res == 0x200) {
        func_8003F6AC(1);
        ret = 2;
    } else if (res == 0) {
        buttons = ((u16*)D_800603C0)[4];
        if (buttons & 0x8000) {
            func_8003F6AC(2);
            ret = 1;
            M2C_FIELD(arg0, u16**, 0x24)[M2C_FIELD(arg0, s32*, 0x28)] ^= 8;
        } else if (buttons & 0x4000) {
            func_8003F6AC(3);
            ret = -1;
        }
    }
    return ret;
}

#ifdef NON_MATCHING
/* TODO: decompile func_89105924; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89105924.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8910597C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_8910597C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891059FC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891059FC.s")
#endif

void BattleInfoWidget_ApplyEntrySelection(unk_func_8830867C_034* arg0, s32 arg1) {
    s8* ptr = M2C_FIELD(M2C_FIELD(arg0, s8**, 0x70), s8**, 0) + arg1 * 0x24;
    s8* ptr2 = M2C_FIELD(ptr, s8**, 0x10);

    M2C_FIELD(ptr2, s32*, 0xC) = (M2C_FIELD(arg0, u16**, 0x74)[arg1] & 8) != 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_89105AD4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89105AD4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89105C54; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89105C54.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89105E70; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89105E70.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891060BC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891060BC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89106254; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89106254.s")
#endif

void func_89106384(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s8* arg5) {
    s32 temp_v0 = M2C_FIELD(arg5, s32*, 8) - 0xC;

    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x16, M2C_FIELD(arg5, Color_RGBA8*, 0x18));
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_89106424; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89106424.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89106570; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89106570.s")
#endif

s32 func_8002AE6C();                                /* extern */
M2C_UNK func_8002D9B8(s32, s32, s32, s32, s8 *);  /* extern */
void func_8910666C(s8 *arg0, s32 arg1)
{
  s8 *new_var;
  if (func_8002AE6C() == 0)
  {
    new_var = (s8 *) arg0;
    if ((arg0 && arg0) && arg0)
    {
    }
    func_8002D9B8(arg0 + 0x40, (*((s32 *) (((s8 *) arg0) + 0))) + 6, (*((s32 *) (new_var + 4))) + 0xA, arg1 | 0xFFED, arg0);
    if (arg1)
    {
    }
  }
}

M2C_UNK func_8002DC04(s32);                         /* extern */

void func_891066C0(s32 arg0) {
    func_8002DC04(arg0 + 0x40);
}

#ifdef NON_MATCHING
/* TODO: decompile func_891066E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891066E0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89106864; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89106864.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89106B54; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89106B54.s")
#endif

s32 func_8000B30C();                                /* extern */
M2C_UNK func_8002B204(s8 *, s32, s8 *);         /* extern */
M2C_UNK func_8002B2E4(s32, s32, s8 *);            /* extern */
M2C_UNK func_8002B4B4(s8 *, s32, s8 *);         /* extern */
s32 func_8002BC14(s32, s32, s8 *);                /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */
extern s32 D_800603C0;

s32 func_89106C98(s8 *arg0) {
    s32 sp1C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;

    sp1C = 0;
    temp_v1 = func_8000B30C() & 0xFFFF;
    if (temp_v1 & 0x300) {
        func_8002B2E4(arg0 + 0xD8, temp_v1, arg0);
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0xDC);
        if (temp_v1_2 < 3) {
            M2C_FIELD(arg0, s32 *, 0xE4) = 0;
            M2C_FIELD(arg0, s32 *, 0xB4) = (s32) (2 - temp_v1_2);
        } else if (temp_v1_2 < 6) {
            M2C_FIELD(arg0, s32 *, 0xE4) = 1;
            M2C_FIELD(arg0, s32 *, 0xC8) = (s32) (5 - temp_v1_2);
        } else {
            M2C_FIELD(arg0, s32 *, 0xE4) = 2;
            M2C_FIELD(arg0, s32 *, 0xD0) = 0;
        }
    } else if (temp_v1 & 0xC00) {
        temp_v0 = M2C_FIELD(arg0, s32 *, 0xE4);
        switch (temp_v0) {                          /* irregular */
        case 0:
            func_8002B4B4(arg0 + 0xA4, temp_v1, arg0);
            break;
        case 1:
            func_8002B4B4(arg0 + 0xB8, temp_v1, arg0);
            break;
        case 2:
            func_8002B204(arg0 + 0xCC, temp_v1, arg0);
            break;
        }
    } else if (temp_v1 == 0) {
        temp_v0_2 = func_8002BC14(D_800603C0, temp_v1, arg0);
        if (temp_v0_2 == -1) {
            func_8003F6AC(3);
            sp1C = -1;
        } else if ((temp_v0_2 == 1) && (M2C_FIELD(arg0, s32 *, 0xE4) == 2)) {
            if (M2C_FIELD(arg0, s32 *, 0xD0) == 0) {
                func_8003F6AC(2);
                sp1C = 1;
            } else if (!(M2C_FIELD(arg0, s32 *, 0x3C) & 1)) {
                func_8003F6AC(2);
                sp1C = 2;
            } else {
                func_8003F6AC(8);
            }
        }
    }
    return sp1C;
}

/*
 * func_89106E34
 *
 * Calls func_8002A8C4(arg0, arg1, arg2, arg3, 0), which fills the first five
 * words of the object (arg1, arg2, arg3, 0, 0), then stores arg4 at +0x14.
 */
void func_89106E34(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8002A8C4(arg0, arg1, arg2, arg3, 0);
    M2C_FIELD(arg0, s32 *, 0x14) = arg4;
}

typedef struct Tex89106E64 {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
    /* 0x08 */ u8* img08;
    /* 0x0C */ u8* img0C;
    /* 0x10 */ u8* img10;
    /* 0x14 */ u8* img14;
} Tex89106E64;
typedef struct Win89106E64 {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 width;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 flags;
    /* 0x14 */ Tex89106E64* tex;
} Win89106E64;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_89106E64(Win89106E64* arg0) {
    gSPDisplayList(gDisplayListHead++, D_80073408);
    func_8001B884(arg0->x, arg0->y, arg0->tex->width, arg0->tex->height,
                  (arg0->flags & 8) ? arg0->tex->img08 : arg0->tex->img0C, arg0->tex->width, 0x200000);
    func_8001B884(arg0->x + arg0->width - arg0->tex->width, arg0->y, arg0->tex->width, arg0->tex->height,
                  (arg0->flags & 8) ? arg0->tex->img14 : arg0->tex->img10, arg0->tex->width, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80073438);
}

s32 func_89106F74(s8 *arg0)
{
  s32 temp_v0;
  s32 var_v1;
  u16 temp_a1;
  temp_v0 = *((s32 *) (((s8 *) arg0) + 0x10));
  var_v1 = 0;
  if (temp_v0 & 1)
  {
    return 0;
  }
  temp_a1 = *((u16 *) (((s8 *) (*((s8 **) (&D_800603C0)))) + 8));
  if ((*((u16 *) (((s8 *) (*((s8 **) (&D_800603C0)))) + 8))) & 0x200)
  {
    *((s32 *) (((s8 *) arg0) + 0x10)) = (s32) (temp_v0 | 8);
    var_v1 = 0x200;
  }
  else
    if ((*((u16 *) (((s8 *) (*((s8 **) (&D_800603C0)))) + 8))) & 0x100)
  {
    *((s32 *) (((s8 *) arg0) + 0x10)) = (s32) (temp_v0 & (~8));
    var_v1 = 0x100;
  }
  return var_v1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_89106FD8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89106FD8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8910713C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_8910713C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89107170; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89107170.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891071A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891071A4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891074CC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891074CC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89107614; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89107614.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89107850; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89107850.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891078E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891078E0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89107A60; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89107A60.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89107D7C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89107D7C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89107EC4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89107EC4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89108108; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89108108.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891081A8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891081A8.s")
#endif

/* Layouts below are partial and local to this function: only the fields the
 * function touches are named, and the names say where they are, not what
 * they mean. */
typedef struct {
    s32 pad0[4];
    s32 word10;
} FlagScanEntry;

typedef struct {
    FlagScanEntry** entries; /* 0x00 */
    s32 unk4;
    s32 count;               /* 0x08 */
} FlagScanTable;

typedef struct {
    u8 pad0[0x4C];
    FlagScanTable* table;    /* 0x4C */
    u16* flags;              /* 0x50 */
} FlagScanOwner;

/*
 * func_89108450
 *
 * Walks the pointer array arg0->table->entries (arg0->table->count items).
 * For every entry whose word at offset 0x10 has any of its low five bits
 * (mask 0x1F) set, bit 0 is set in the matching halfword of the array at
 * arg0->flags (same index). What the entries and the flags are is not
 * established here. The loop bound re-reads arg0->table->count each pass.
 * Matching note: the entries pointer is held in a local and indexed;
 * advancing a pointer through arg0->table->entries directly gives a
 * different register assignment.
 */
void func_89108450(FlagScanOwner* arg0) {
    s32 i;
    FlagScanEntry** entries;

    entries = arg0->table->entries;
    for (i = 0; i < arg0->table->count; i++) {
        if (entries[i]->word10 & 0x1F) {
            arg0->flags[i] |= 1;
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_891084B4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891084B4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89108650; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89108650.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_891089BC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_891089BC.s")
#endif

void func_89108F0C(void) {
}

#ifdef NON_MATCHING
/* TODO: decompile func_89108F14; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89108F14.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_89108F94; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment016_252E10/func_89108F94.s")
#endif

M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */

s32 func_89109174(s32 arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(D_800603C0, u16 *, 8) & 0xC000) {
        func_8003F6AC(3);
        var_v1 = 1;
    }
    return var_v1;
}
