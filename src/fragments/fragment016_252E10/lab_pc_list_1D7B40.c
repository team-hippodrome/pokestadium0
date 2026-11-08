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

typedef struct Str89104D14 { s8 c[4]; } Str89104D14;
extern Str89104D14 D_8910A914;
void func_80027804(s8 *, s32 *, s32, s32);
void func_8002A8C4(s8 *, s32, s32, s32, s32);
void func_8002D880(s8 *, s8 *, s32, void *, s32, s32);
u32 func_800566BC(s32);
void func_89104C70();
void func_89104D14(s8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4, s32 arg5) {
    s32 i;
    s32 w;
    s32 max = 0;
    s32 h;

    for (i = 0; i < arg5; i++) {
        w = func_800566BC(arg3[i]) >> 1;
        if (max < w) {
            max = w;
        }
    }
    func_80027804(arg0 + 0x50, arg3, arg5, arg5);
    h = max * 0x14 + 0x10;
    func_8002D880(arg0 + 0x2C, arg0 + 0x50, arg4, func_89104C70, h, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x4C) |= 0x10000;
    func_8002A8C4(arg0, arg1, arg2, h + 0xC, 0x84);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, Str89104D14 *, 0x18) = D_8910A914;
}

s32 func_8002AE6C();
M2C_UNK func_8002D9B8(s32, s32, s32, s32, s8*);

typedef struct Box89104E38 {
    s32 x;
    s32 y;
    s32 w;
    char padC[0x20];
    s8 label[1];
} Box89104E38;

void func_89104E38(Box89104E38* arg0) {
    s32 label;

    if (func_8002AE6C() == 0) {
        s32 sp2C[4];

        sp2C[0] = arg0->w - 0xC;
        label = (s32)arg0->label;
        func_8002D9B8(label, arg0->x + 6, arg0->y + 0xA, 0xFFEF, (s8*)sp2C);
    }
    /* Empty test kept from the permuter: it keeps arg0 in $s0 as in the ROM. */
    if (arg0) {
    }
}

M2C_UNK func_8002DC04(s32);                         /* extern */

void func_89104E94(s32 arg0) {
    func_8002DC04(arg0 + 0x2C);
}

typedef struct Entry891078E0 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry891078E0;
extern Entry891078E0 D_8006A9D4[];
extern Color_RGBA8 D_800734A8[];
extern char D_8910E000[];
extern char D_8910E010[];

void func_89104EB4(s32 arg0, s32 arg1, s32* arg2, s32 arg3, s32 arg4, s32* arg5) {
    UNUSED s32 padA[4];
    const char* name;
    s32 temp;
    s32 alpha;

    temp = *arg2;
    switch (temp) {
        case -2:
            name = D_8910E000;
            break;
        case -1:
            name = D_8910E010;
            break;
        default:
            name = D_8006A9D4[temp].name;
            break;
    }
    Font_BeginTranslucentTextRendering();
    if (arg4 & 0x100) {
        Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, *arg5);
    } else if (arg4 & 0x200) {
        alpha = *arg5;
        Gfx_SetEnvColor(0xFF, 0xC8, 0xC8, alpha);
    } else {
        func_80027F20(arg4);
    }
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, name);
    Font_EndTexturedTextRendering();
}

typedef struct Str89104FC0 { s8 c[4]; } Str89104FC0;
extern Str89104FC0 D_8910A91C;
s32 func_8002D3D0(u8*);
s32 func_8002D430(s32, s32);
void func_80027410(void*, void*, s32, s32, s32);
void func_89104EB4();

void func_89104FC0(s8* arg0, s32 arg1, s32 arg2, u8* arg3) {
    s32 n = func_8002D3D0(arg3);
    s32 i;

    for (i = 0; i < n; i++) {
        M2C_FIELD(arg0, s32*, 0x60 + i * 4) = func_8002D430((s32)arg3, i);
    }
    for (i = n; i < 4; i++) {
        M2C_FIELD(arg0, s32*, 0x60 + i * 4) = -1;
    }
    func_80027410(arg0 + 0x50, arg0 + 0x60, 4, 4, 4);
    func_8002D880(arg0 + 0x2C, arg0 + 0x50, (s32)(arg0 + 0x70), func_89104EB4, 0x9C, 0x1C);
    M2C_FIELD(arg0, s32*, 0x4C) |= 0x10000;
    func_8002A8C4(arg0, arg1, arg2, 0xA8, 0x84);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0;
    M2C_FIELD(arg0, Str89104FC0*, 0x18) = D_8910A91C;
}

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

M2C_UNK func_8002DAD8(s8*, s32, s32, s32, s8*);

void func_891051A4(Box89104E38* arg0) {
    s8* label;

    if (func_8002AE6C() == 0) {
        s32 sp2C[4];

        sp2C[0] = arg0->w - 0xC;
        label = arg0->label;
        func_8002DAD8(label, arg0->x + 6, arg0->y + 0xA, 0xFFEF, (s8*)sp2C);
    }
    /* Empty test kept from the permuter: it keeps arg0 in $s0 as in the ROM. */
    if (arg0) {
    }
}

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

/* Set or clear bit 3 in every laboratory list entry flag. */
void func_8910548C(u8* widget, s32 enabled) {
    s32 value = enabled ? 8 : 0;
    s32 offset;
    s32 index;
    s32* list;
    u16* flags;

    list = *(s32**)(widget + 0x20);
    index = 0;
    if (list[2] > 0) {
        offset = 0;
        do {
            index++;
            flags = (u16*)(*(u8**)(widget + 0x24) + offset);
            *flags &= ~8;
            flags = (u16*)(*(u8**)(widget + 0x24) + offset);
            *flags |= value;
            offset += 2;
        } while (index < *(s32*)(*(u8**)(widget + 0x20) + 8));
    }
}

void func_89105504(s32 arg0) {
    s32 i;
    s32* entry = *M2C_FIELD(arg0, s32**, 0x20);

    for (i = 0; i < M2C_FIELD(arg0, s32**, 0x20)[2]; i++) {
        entry[3] = (M2C_FIELD(arg0, u16**, 0x24)[i] & 8) != 0;
        entry += 8;
    }
}

void func_8002A3F8(void*, s32, s32);
void func_80029A64(s32, s32, s32, s32, Color_RGBA8);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
extern u8 D_80073614[];
extern u8 D_80073624[];
extern Color_RGBA8 D_80073520;
extern Color_RGBA8 D_8910A934[];
extern Color_RGBA8 D_800734A8[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_8910CF80[];
extern char D_8910E018[];
void func_89105560(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Color_RGBA8 color;
    s32 pad[6];
    s32 sel;

    if (arg4 & 8) {
        func_8002A3F8(D_80073614, arg0 + 8, arg1 + 4);
    } else {
        func_8002A3F8(D_80073624, arg0 + 8, arg1 + 4);
    }
    sel = arg4 & 2;
    if (sel) {
        func_80029A64(arg0 + 0x2A, arg1 + 2, 0x70, 0x18, D_80073520);
        gSPDisplayList(gDisplayListHead++, D_80060290);
        func_8001B884(arg0 + 0x1D, arg1 + 5, 0xB, 0x12, D_8910CF80, 0xC, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
    if (arg4 & 0x100) {
        color = D_8910A934[sel ? 0 : 1];
    } else {
        color = D_800734A8[sel ? 0 : 1];
    }
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x30, arg1 + 4, D_8910E018, arg3 + 1);
    Font_EndTexturedTextRendering();
}

typedef struct Rgba8910576C {
    u8 r, g, b, a;
} Rgba8910576C;

void func_89105560();
void func_891053E8(void* arg0);

void func_8910576C(void* arg0, s32 arg1, s32 arg2, void* arg3, s32 arg4, Rgba8910576C arg5) {
    func_8002A8C4((s8*)arg0, arg1, arg2, 0x9C, M2C_FIELD(arg3, s32*, 8) * 0x1C + 8);
    M2C_FIELD(arg0, s32*, 0x14) = 0;
    M2C_FIELD(arg0, Rgba8910576C*, 0x18) = arg5;
    func_8002D880((s8*)arg0 + 0x20, arg3, arg4, func_89105560, 0x9C, 0x1C);
    func_891053E8(arg0);
}

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

typedef struct Entry89105924 { char unk00[0xC]; s32 unk0C; char unk10[0xC]; s32 unk1C; } Entry89105924;
typedef struct List89105924 { char unk00[0x10]; Entry89105924* entries; char unk14[4]; s32 count; } List89105924;
s32 func_89105924(List89105924* arg0) {
    Entry89105924* entries = arg0->entries;
    s32 flags = 0x100;
    s32 i;
    for (i = 0; i < arg0->count; i++) {
        if (entries[i].unk0C != 0) {
            flags |= 8;
        }
        if (entries[i].unk1C > 0) {
            flags &= ~0x100;
        }
    }
    return flags;
}

void func_8910597C(s8* arg0, s8* arg1) {
    s32 flag = 0;
    s32 i = 0;
    s32 count = M2C_FIELD(M2C_FIELD(arg1, s8**, 0x20), s32*, 8);
    u16* items;

    if (count > 0) {
        if (!arg0) {} // fake, keeps arg0 live in a saved register
        items = M2C_FIELD(arg1, u16**, 0x24);
        do {
            i++;
            if (*items & 8) {
                flag = 8;
                break;
            }
            items++;
        } while (i < count);
    }
    M2C_FIELD(arg0, u16**, 0x74)[M2C_FIELD(arg0, s32*, 0x78)] &= ~8;
    M2C_FIELD(arg0, u16**, 0x74)[M2C_FIELD(arg0, s32*, 0x78)] |= flag;
}

/* Rebuild entry flags from the current laboratory records. */
void func_891059FC(u8* widget) {
    s32 offset;
    s32 entry = (*(s32**)(widget + 0x70))[0];
    s32 index;
    s32* list;
    s32 flags;
    u16* destination;

    list = *(s32**)(widget + 0x70);
    offset = 0;
    index = 0;

    if (list[2] > 0) {
        do {
            *(u16*)(*(u8**)(widget + 0x74) + offset) = 0;
            flags = func_89105924((List89105924*)entry);
            index++;
            entry += 0x24;
            destination = (u16*)(*(u8**)(widget + 0x74) + offset);
            *destination |= flags;
            offset += 2;
        } while (index < *(s32*)(*(u8**)(widget + 0x70) + 8));
    }
}

void BattleInfoWidget_ApplyEntrySelection(unk_func_8830867C_034* arg0, s32 arg1) {
    s8* ptr = M2C_FIELD(M2C_FIELD(arg0, s8**, 0x70), s8**, 0) + arg1 * 0x24;
    s8* ptr2 = M2C_FIELD(ptr, s8**, 0x10);

    M2C_FIELD(ptr2, s32*, 0xC) = (M2C_FIELD(arg0, u16**, 0x74)[arg1] & 8) != 0;
}

void func_8002A3F8(void*, s32, s32);
void func_80029A64(s32, s32, s32, s32, Color_RGBA8);
extern u8 D_80073614[];
extern u8 D_80073624[];
extern Color_RGBA8 D_80073520;
extern Color_RGBA8 D_8910A934[];
extern Color_RGBA8 D_800734A8[];
void func_89105AD4(s32 arg0, s32 arg1, char** arg2, s32 arg3, s32 arg4) {
    Color_RGBA8 color;
    s32 pad[5];
    s32 sel;

    if (arg4 & 8) {
        func_8002A3F8(D_80073614, arg0 + 8, arg1 + 4);
    } else {
        func_8002A3F8(D_80073624, arg0 + 8, arg1 + 4);
    }
    sel = arg4 & 2;
    if (sel) {
        func_80029A64(arg0 + 0x2A, arg1 + 2, 0xE8, 0x18, D_80073520);
    }
    if (arg4 & 0x100) {
        color = D_8910A934[sel ? 0 : 1];
    } else {
        color = D_800734A8[sel ? 0 : 1];
    }
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(color.r, color.g, color.b, color.a);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x30, arg1 + 4, *arg2);
    Font_EndTexturedTextRendering();
}

void func_8002AE94(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Rgba8910576C arg4, char* arg5);
void func_8910576C(void* arg0, s32 arg1, s32 arg2, void* arg3, s32 arg4, Rgba8910576C arg5);
void func_89105AD4(s32 arg0, s32 arg1, char** arg2, s32 arg3, s32 arg4);
void func_891059FC(u8* widget);
void func_8000B2F4(s32);
extern s32 D_800603C0;
extern Rgba8910576C D_8910A93C;
extern Rgba8910576C D_8910A940;
extern char D_8910E024[];
void func_89105C54(s8* arg0, s32 arg1, s32 arg2, s8* arg3, Rgba8910576C arg4) {
    s32 pad[5];
    s32 list;

    func_8002A8C4(arg0 + 4, arg1, arg2, 0x134, 0xCE);
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x2C) = 0;
    M2C_FIELD(arg0, s32*, 0x18) = 1;
    M2C_FIELD(arg0, Rgba8910576C*, 0x1C) = arg4;
    func_8002A8C4(arg0 + 0x30, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 6, M2C_FIELD(arg0, s32*, 0xC) - 0xC, 0x40);
    M2C_FIELD(arg0, s32*, 0x44) = 6;
    M2C_FIELD(arg0, Rgba8910576C*, 0x48) = D_8910A93C;
    M2C_FIELD(arg0, Rgba8910576C*, 0x4C) = D_8910A940;
    func_8002A8C4(arg0 + 0x50, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) + 0x4C, M2C_FIELD(arg0, s32*, 0xC) - 0xC, 0x7C);
    M2C_FIELD(arg0, s32*, 0x64) = 0;
    M2C_FIELD(arg0, Rgba8910576C*, 0x68) = arg4;
    func_8002AE94(arg0 + 0x94, M2C_FIELD(arg0, s32*, 0x50) + 0x70, M2C_FIELD(arg0, s32*, 0x54) + 0x5C, 0x48, arg4, D_8910E024);
    M2C_FIELD(arg0, s32*, 0xC0) = 0xA;
    M2C_FIELD(arg0, s32*, 0xC8) = 0xC;
    list = *(s32*)arg3;
    func_8910576C(arg0 + 0xDC, M2C_FIELD(arg0, s32*, 0xC) + M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 0x54) + 0x1C, (void*)(list + 0x34), (s32)(arg0 + 0x16C), arg4);
    func_8910576C(arg0 + 0x120, M2C_FIELD(arg0, s32*, 0xC) + M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 0x54) + 0x38, (void*)(list + 0x58), (s32)(arg0 + 0x17C), arg4);
    func_8002D880(arg0 + 0x70, arg3, (s32)(arg0 + 0x164), func_89105AD4, 0x128, 0x1C);
    func_891059FC((u8*)arg0);
    M2C_FIELD(arg0, s32*, 0xD8) = 4;
    M2C_FIELD(arg0, s32*, 0xD4) = 0;
    M2C_FIELD(arg0, s32*, 0xD0) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32*, 0xD4) = 3;
    M2C_FIELD(arg0, s32*, 0) = 0;
}

void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_80029658(s32, s32, s32, void*);
void func_8002AF04(s8 *, s32);
extern u8 D_8007356C[];
extern Color_RGBA8 D_800734A8[];
extern char D_8910E02C[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_8910D138[];
void func_89105E70(s8* arg0, s32 arg1) {
    UNUSED s32 pad[3];
    s32 sp38 = 0xFFED;
    s32 sp34 = 0;

    if (func_8002AE6C(arg0 + 4) == 0) {
        func_8002A8E0(arg0 + 0x30);
        func_8002A8E0(arg0 + 0x50);
        func_80029658(M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 8) + 0x45, M2C_FIELD(arg0, s32*, 0xC), D_8007356C);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(M2C_FIELD(arg0, s32*, 0x30) + 8, M2C_FIELD(arg0, s32*, 0x34) + 8, D_8910E02C);
        Font_EndTexturedTextRendering();
        if ((arg1 & 2) && (M2C_FIELD(arg0, s32*, 0) == 0)) {
            if (M2C_FIELD(arg0, s32*, 0xD4) == 3) {
                sp34 = 2;
            } else {
                sp38 = 0xFFEF;
                if ((M2C_FIELD(arg0, s32*, 0xD4) == 1) || (M2C_FIELD(arg0, s32*, 0xD4) == 2)) {
                    gSPDisplayList(gDisplayListHead++, D_80060290);
                    func_8001B884((M2C_FIELD(arg0, s32*, 0x58) + M2C_FIELD(arg0, s32*, 0x50)) - 0x11, (M2C_FIELD(arg0, s32*, 0xD4) * 0x1C) + M2C_FIELD(arg0, s32*, 0x54) + 9, 0xB, 0x12, D_8910D138, 0xC, 0x200000);
                    gSPDisplayList(gDisplayListHead++, D_80060398);
                }
            }
        }
        func_8002DAD8(arg0 + 0x70, M2C_FIELD(arg0, s32*, 0x50), M2C_FIELD(arg0, s32*, 0x54) + 4, sp38, arg0);
        func_8002AF04(arg0 + 0x94, sp34);
        if (M2C_FIELD(arg0, s32*, 0xD4) == 1) {
            func_891057FC(arg0 + 0xDC, (M2C_FIELD(arg0, s32*, 0) == 1) ? 2 : 0);
        } else if (M2C_FIELD(arg0, s32*, 0xD4) == 2) {
            func_891057FC(arg0 + 0x120, (M2C_FIELD(arg0, s32*, 0) == 2) ? 2 : 0);
        }
    }
}

s32 func_8002B2B0(s8*);
void func_89105A98(s8*, s32);

s32 func_891060BC(s8* arg0) {
    s32 ret = 0;
    s32 res;
    s32 buttons;

    res = func_8002B2B0(arg0 + 0xD0);
    if (res == 0x100) {
        if (M2C_FIELD(arg0, s32*, 0xD4) == 1) {
            func_8003F6AC(1);
            M2C_FIELD(arg0, s32*, 0) = 1;
        } else if (M2C_FIELD(arg0, s32*, 0xD4) == 2) {
            func_8003F6AC(1);
            M2C_FIELD(arg0, s32*, 0) = 2;
        }
    } else if (res == 0) {
        buttons = ((u16*)D_800603C0)[4];
        if (buttons & 0x8000) {
            if (M2C_FIELD(arg0, s32*, 0xD4) == 3) {
                func_8003F6AC(2);
                func_89105A98(arg0, 0);
                func_89105504((s32)(arg0 + 0xDC));
                func_89105504((s32)(arg0 + 0x120));
                ret = 1;
            } else {
                func_8003F6AC(2);
                M2C_FIELD(arg0, u16**, 0x74)[M2C_FIELD(arg0, s32*, 0x78)] ^= 8;
                if (M2C_FIELD(arg0, s32*, 0xD4) == 1) {
                    func_8910548C((u8*)(arg0 + 0xDC), M2C_FIELD(arg0, u16**, 0x74)[M2C_FIELD(arg0, s32*, 0x78)] & 8);
                } else if (M2C_FIELD(arg0, s32*, 0xD4) == 2) {
                    func_8910548C((u8*)(arg0 + 0x120), M2C_FIELD(arg0, u16**, 0x74)[M2C_FIELD(arg0, s32*, 0x78)] & 8);
                }
            }
        } else if (buttons & 0x4000) {
            func_8003F6AC(3);
            ret = -1;
        }
    }
    if (M2C_FIELD(arg0, s32*, 0xD4) < 4) {
        M2C_FIELD(arg0, s32*, 0x78) = M2C_FIELD(arg0, s32*, 0xD4);
    }
    return ret;
}

s32 func_891060BC(s8 *);
s32 func_89106254(s8 *arg0) {
    s32 ret = 0;
    s32 r;

    if (M2C_FIELD(arg0, s32 *, 0x2C) == 0) {
        return 0;
    }
    switch (M2C_FIELD(arg0, s32 *, 0)) {
        case 0:
            ret = func_891060BC(arg0);
            break;
        case 1:
            r = func_8910587C((s32)(arg0 + 0xDC));
            if (r == -1) {
                ret = -1;
            } else if (r == 1) {
                func_8910597C(arg0, arg0 + 0xDC);
            } else if (r == 2) {
                M2C_FIELD(arg0, s32 *, 0) = 0;
            }
            break;
        case 2:
            r = func_8910587C((s32)(arg0 + 0x120));
            if (r == -1) {
                ret = -1;
            } else if (r == 1) {
                func_8910597C(arg0, arg0 + 0x120);
            } else if (r == 2) {
                M2C_FIELD(arg0, s32 *, 0) = 0;
            }
            break;
    }
    return ret;
}

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

void func_89106424(s8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 w;
    s32 max = 0;
    s32 h;

    M2C_FIELD(arg0, s32 *, 0x70) = arg4;
    for (i = 0; i < arg3; i++) {
        w = func_800566BC(arg1[i]) >> 1;
        if (max < w) {
            max = w;
        }
    }
    func_80027804(arg0 + 0x64, arg1, arg3, arg3);
    h = max * 0x14 + 0x10;
    func_8002D880(arg0 + 0x40, arg0 + 0x64, arg2, func_89106384, h, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x60) |= 0x10000;
    func_8002A8C4(arg0, 0, 0, h + 0xC, M2C_FIELD(arg0, s32 *, 0x6C) * 0x1C + 0x14);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    if (arg4 != 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = 0x800;
    } else {
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
    }
    if (arg4 != 0) {
        M2C_FIELD(arg0, s32 *, 0x20) = arg4;
    }
}

typedef struct Popup89106570 {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 width;
    /* 0x0C */ s32 height;
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s32 flags;
    /* 0x18 */ char unk18[0xC];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ char unk28[0x4];
    /* 0x2C */ s32 anchorX;
    /* 0x30 */ s32 anchorY;
    /* 0x34 */ s32 anchorW;
    /* 0x38 */ s32 anchorH;
    /* 0x3C */ char unk3C[0x38];
    /* 0x74 */ s32 limitX;
    /* 0x78 */ s32 limitY;
} Popup89106570;

/*
 * func_89106570
 *
 * Places a popup next to its anchor rectangle while keeping it inside the
 * limits at +0x74/+0x78.  With flag 0x01000000 it goes to the right of the
 * anchor (or to its left when that would overflow) and is pushed up by the
 * overflow, at least 8; otherwise it goes below the anchor (or above it) and
 * is pushed left the same way.  Field names describe that geometry only.
 */
void func_89106570(Popup89106570* arg0) {
    s32 over;

    if (arg0->flags & 0x01000000) {
        if (arg0->limitY >= arg0->anchorY + arg0->height) {
            arg0->y = arg0->anchorY;
        } else {
            over = (arg0->anchorY + arg0->height) - arg0->limitY;
            arg0->y = arg0->anchorY - ((over > 8) ? over : 8);
        }
        if (arg0->limitX >= arg0->anchorX + arg0->anchorW + arg0->width) {
            arg0->x = arg0->anchorX + arg0->anchorW;
        } else {
            arg0->x = arg0->anchorX - arg0->width;
        }
    } else {
        if (arg0->limitX >= arg0->anchorX + arg0->width) {
            arg0->x = arg0->anchorX;
        } else {
            over = (arg0->anchorX + arg0->width) - arg0->limitX;
            arg0->x = arg0->anchorX - ((over > 8) ? over : 8);
        }
        if (arg0->limitY >= arg0->anchorY + arg0->anchorH + arg0->height) {
            arg0->y = arg0->anchorY + arg0->anchorH;
        } else {
            arg0->y = arg0->anchorY - arg0->height;
        }
    }
    arg0->unk24 = 0;
}

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

void func_8002AF04(s8 *, s32);
void func_89106864(s8 *, s32, s32, s32);
extern char D_8910E094[];
void func_89106B54(s8 *arg0) {
    if (func_8002AE6C() == 0) {
        func_8001AB6C();
        func_8001A384(4, 0);
        func_8001AA9C(0xC8, 0xC8, 0xFF, 0xFF);
        func_8001A944(M2C_FIELD(arg0, s32 *, 0) + 0x54, M2C_FIELD(arg0, s32 *, 4) + 0x13, D_8910E094);
        func_8001ABBC();
        func_89106864(arg0 + 0xA4, M2C_FIELD(arg0, s32 *, 0) + 0xE, M2C_FIELD(arg0, s32 *, 4) + 0x10, (M2C_FIELD(arg0, s32 *, 0xE4) == 0) ? 2 : 0);
        func_89106864(arg0 + 0xB8, M2C_FIELD(arg0, s32 *, 0) + 0x7A, M2C_FIELD(arg0, s32 *, 4) + 0x10, (M2C_FIELD(arg0, s32 *, 0xE4) == 1) ? 2 : 0);
        func_8002AF04(arg0 + 0x68, (M2C_FIELD(arg0, s32 *, 0xE4) == 2 && M2C_FIELD(arg0, s32 *, 0xD0) == 0) ? 2 : 0);
        func_8002AF04(arg0 + 0x2C, (M2C_FIELD(arg0, s32 *, 0xE4) == 2 && M2C_FIELD(arg0, s32 *, 0xD0) == 1) ? 2 : 0);
    }
}

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

extern Gfx D_80060270[];
extern u8 D_8910A968[];
extern u8 D_8910A970[];
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_8002B940(s32, s32, s32, s32);
void func_89106FD8(s32 arg0, s32 arg1, char **arg2, s32 arg3, s32 arg4) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xAE, 0x1A, *(Color_RGBA8 *)D_8910A968);
    func_80029028(arg0, arg1, 0xAE, 1, *(Color_RGBA8 *)D_8910A970);
    func_80029028(arg0, arg1 + 0x1B, 0xAE, 1, *(Color_RGBA8 *)D_8910A970);
    if (arg4 & 8) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0xA8, 0x16, *(Color_RGBA8 *)D_8910A968);
    }
    func_8002B940(arg0 + 9, arg1 + 8, arg3 + 1, 2);
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x42, arg1 + 4, *arg2);
    Font_EndTexturedTextRendering();
}

s32 Move_NormalizeDisplayIndex(s32 a) {
    return a >= 20 ? a - 12 : (a >= 7 ? a - 1 : a);
}

s32 func_89107170(s32 a) {
    return a >= 8 ? a + 12 : (a >= 6 ? a + 1 : a);
}

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

s32 func_8002FD8C(s8*);

typedef struct Slot89107614 {
    s32 unk64;
    s32 unk68;
    char unk6C[0x38];
} Slot89107614;

typedef struct Lab89107614 {
    char unk000[0x64];
    Slot89107614 slots[3];
    s8 unk124[4];
    s32 unk128;
    char unk12C[4];
    s8 unk130[4];
    u16* unk134;
    s32 unk138;
    char unk13C[0x38];
    s32* unk174[26];
    s32 unk1DC;
} Lab89107614;

s32 func_89107614(Lab89107614* arg0) {
    s32 ret = 0;
    u16 buttons;

    switch (arg0->unk1DC) {
        case 0:
            if (func_8002B2B0(arg0->unk124) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    func_8003F6AC(3);
                    ret = -1;
                } else if (buttons & 0x8000) {
                    switch (arg0->unk128) {
                        case 0:
                        case 1:
                            func_8003F6AC(2);
                            arg0->unk1DC = 1;
                            break;
                        case 2:
                            func_8003F6AC(2);
                            ret = 1;
                            break;
                        case 3:
                            if (M2C_FIELD(arg0, s32*, 0xBC) & 1) {
                                func_8003F6AC(8);
                            } else {
                                func_8003F6AC(2);
                                ret = 2;
                            }
                            break;
                    }
                }
            }
            break;
        case 1:
            if (func_8002FD8C(arg0->unk130) == 0) {
                buttons = ((u16*)D_800603C0)[4];
                if (buttons & 0x4000) {
                    func_8003F6AC(3);
                    arg0->unk1DC = 0;
                } else if (buttons & 0x8000) {
                    if (arg0->unk134[arg0->unk138] & 8) {
                        func_8003F6AC(8);
                    } else {
                        s32 prev;

                        func_8003F6AC(2);
                        prev = arg0->slots[arg0->unk128].unk68;
                        if (prev != -1) {
                            arg0->unk134[prev] &= ~8;
                        }
                        arg0->unk134[arg0->unk138] |= 8;
                        arg0->slots[arg0->unk128].unk68 = arg0->unk138;
                        arg0->slots[arg0->unk128].unk64 = *arg0->unk174[arg0->unk138];
                        arg0->unk1DC = 0;
                        arg0->unk128++;
                    }
                }
            }
            break;
    }
    return ret;
}

void func_89107850(s8* arg0, s32* arg1) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (M2C_FIELD(arg0 + i * 0x40, s32*, 0x68) != -1) {
            M2C_FIELD((s8*)arg1 + count, s8*, 4) = func_89107170(M2C_FIELD(arg0 + i * 0x40, s32*, 0x68));
            count++;
        }
    }
    *arg1 = count;
}

extern u8 D_8910AAC0[];
extern u8 D_8910AAC8[];
void func_891078E0(s32 arg0, s32 arg1, u8* arg2, s32 arg3, s32 arg4) {
    s32 idx;

    idx = *arg2;
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1 + 1, 0xD4, 0x1A, *(Color_RGBA8 *)D_8910AAC0);
    func_80029028(arg0, arg1, 0xD4, 1, *(Color_RGBA8 *)D_8910AAC8);
    func_80029028(arg0, arg1 + 0x1B, 0xD4, 1, *(Color_RGBA8 *)D_8910AAC8);
    if (arg4 & 8) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0xCE, 0x16, *(Color_RGBA8 *)D_8910AAC0);
    }
    func_8002B940(arg0 + 9, arg1 + 8, arg3 + 1, 3);
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 0x37, arg1 + 4, D_8006A9D4[idx].name);
    Font_EndTexturedTextRendering();
}

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

extern u8 D_8910A978[];

void func_89108108(s8* arg0, s8* arg1) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (M2C_FIELD(arg0 + i * 0x40, s32*, 0x68) != -1) {
            arg1[count++] = D_8910A978[M2C_FIELD(arg0 + i * 0x40, s32*, 0x68)] + 1;
        }
    }
    M2C_FIELD(arg1, s32*, 4) = count;
}

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

typedef struct Str891084B4 {
    /* 0x00 */ u8 c[0x11];
} Str891084B4; // size = 0x11
typedef struct Rgba891084B4 {
    u8 r, g, b, a;
} Rgba891084B4;
extern s8 D_89119BD0[];
extern u8 D_8910E120[];
extern u8 D_8910AAE0[];
extern u8 D_8910AAE4[];
void func_8000A460(s8*, s8*);
void func_8002EC24(s8*, s32, s32, s32, void*, s32, s32);
void func_891081A8();
void func_891084B4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8* arg5) {
    func_8002A8C4(arg0, arg1, arg2, 0x184, 0x16E);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x801;
    func_8000A460(D_89119BD0, *(s8**)D_80064C44[arg5[8]]);
    *(Str891084B4*)(func_800566BC((s32)D_89119BD0) + D_89119BD0) = *(Str891084B4*)D_8910E120;
    M2C_FIELD(arg0, s8**, 0x20) = D_89119BD0;
    func_8002A8C4(arg0 + 0x2C, arg1 + 6, arg2 + 0x10C, 0x178, 0x5C);
    M2C_FIELD(arg0, s32*, 0x40) = 6;
    M2C_FIELD(arg0, Rgba891084B4*, 0x44) = *(Rgba891084B4*)D_8910AAE0;
    M2C_FIELD(arg0, Rgba891084B4*, 0x48) = *(Rgba891084B4*)D_8910AAE4;
    func_8002EC24(arg0 + 0x4C, arg3, arg4, 8, func_891081A8, 0x178, 0x1C);
    M2C_FIELD(arg0, s32*, 0x6C) |= 0x10000;
    func_89108450((FlagScanOwner*)arg0);
    M2C_FIELD(arg0, u8**, 0x1AC) = arg5;
    M2C_FIELD(arg0, s32*, 0x1B0) = 0;
}

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

typedef struct Rgba89108F14 {
    u8 r, g, b, a;
} Rgba89108F14;

extern u8 D_8910AAF4[];
extern u8 D_8910AAF8[];

void func_89108F14(void* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8002A8C4((s8*)arg0, arg1, arg2, 0x114, 0x60);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 6;
    M2C_FIELD(arg0, Rgba89108F14*, 0x18) = *(Rgba89108F14*)D_8910AAF4;
    M2C_FIELD(arg0, Rgba89108F14*, 0x1C) = *(Rgba89108F14*)D_8910AAF8;
    M2C_FIELD(arg0, s32*, 0x2C) = arg3;
}

typedef struct Entry89108F94 {
    /* 0x00 */ char* title;
    /* 0x04 */ s32 kind;
    /* 0x08 */ char* left;
    /* 0x0C */ char* right;
} Entry89108F94;

extern u8 D_8910D2F0[];
extern char D_8910E1AC[];
extern char D_8910E1B0[];

void func_89108F94(s8* arg0) {
    Entry89108F94* entry;

    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Font_SetActive(0x10, 0);
        Font_EnableTwoCycleTexturing();
        Gfx_SetPrimColor(0xFF, 0xAC, 0xAC, 0xFF);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0x12, M2C_FIELD(arg0, s32*, 4) + 0x12, M2C_FIELD(arg0, Entry89108F94**, 0x2C)->title);
        Font_DisableTwoCycleTexturing();
        Gfx_SetEnvColor(D_800734A8[0].r, D_800734A8[0].g, D_800734A8[0].b, D_800734A8[0].a);
        entry = M2C_FIELD(arg0, Entry89108F94**, 0x2C);
        if (entry->kind == 0) {
            Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0x12, M2C_FIELD(arg0, s32*, 4) + 0x36, D_8910E1AC, entry->left);
            Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xA2, M2C_FIELD(arg0, s32*, 4) + 0x36, D_8910E1B0, M2C_FIELD(arg0, Entry89108F94**, 0x2C)->right);
        } else if (entry->kind == 1) {
            Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0x12, M2C_FIELD(arg0, s32*, 4) + 0x36, entry->left);
            Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xA2, M2C_FIELD(arg0, s32*, 4) + 0x36, M2C_FIELD(arg0, Entry89108F94**, 0x2C)->right);
        }
        Font_EndTexturedTextRendering();
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(M2C_FIELD(arg0, s32*, 0) + 0x7A, M2C_FIELD(arg0, s32*, 4) + 0x36, 0x20, 0x18, D_8910D2F0, 0x20, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
    }
}

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
