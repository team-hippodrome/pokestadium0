/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "game_state.h"
#include "jpeg_stream.h"
#include "memory.h"
#include "stage_loader.h"
#include "m2c_macros.h"

typedef struct Rgba891024A4 { u8 r, g, b, a; } Rgba891024A4;
typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
typedef struct Entry89100FC4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry89100FC4; // size = 0xC
typedef struct Label89100FC4 {
    Color82000BC4 color;
    const char* str;
} Label89100FC4;

extern u8 D_80073520[];
M2C_UNK func_80029A64(s32, s32, s32, s32, Color_RGBA8);
extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void func_89109990(void*, void*, void*, s32);
extern s32 D_800603C0;
void func_8000B2F4(s32);
void func_8002A8C4(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_89109B60(s8*);
void func_80027D68(s32, s32);
void func_8002EC24(s8*, s8*, s8*, s32, void*, s32, s32);
void func_891012A8();
void func_89105C54(s8*, s32, s32, s8*, Rgba891024A4);
extern s32 D_8910D990[];
extern Rgba891024A4 D_8910A7F4;
extern u8 D_8910A844[];
extern u8 D_8910A848[];
extern u8 D_8910A804[];
extern u8 D_8910A84C[];
s32 func_891005CC();
extern Entry80066AD8 D_80066AD8[];
s32 func_8002D498(u8*, s32);
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
M2C_UNK func_8001A944(s32, s32, M2C_UNK *, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
M2C_UNK func_8001AB6C();
M2C_UNK func_8001ABBC();
extern Entry89100FC4 D_8006A9D4[];
extern M2C_UNK D_800734A8;
extern char D_8910DBAC[];
s32 func_8002D454(s32, s32);
extern M2C_UNK D_800734A8;
extern M2C_UNK D_8910DBB4;
extern M2C_UNK D_8910DBBC;
extern M2C_UNK D_8910DBC0;
extern M2C_UNK D_8910DBC4;
extern u8 D_04006170[];
extern u8 D_04006CE0[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_8910C370[];
extern u8 D_8910C978[];
extern char D_8910DBF0[];
extern char D_8910DC04[];
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);
extern s32 D_8910D990[];
void func_8002ED18(s32*, void*, void*);
void func_80027D94(s32, void*, void*, void*);
void func_80027D68(s32, s32);
s32 func_891096F4();
s32 func_89109720();
s32 func_891097E4();
s32 func_89109884();
s32 func_89109898();
s32 func_89109960();
void func_8000A460(s8*, s8*);
u32 func_800566BC(s8*);
void func_89106424(s8*, void*, s8*, s32, s32);
void func_89106570(s8*);
void func_8910A21C(s8*, s8*, s8*, s32);
extern s8* D_8910A890[];
extern u8 D_8910A898[];
extern u8 D_8910DC50[];
extern s8 D_8910E2D0[];
extern s8 D_8910E312[];
s32 func_8003F6AC();
s32 func_8002FD8C(void*);
void func_800306E0(void*, s32);
void func_891020F8(s8*);
void func_8000A460(s8 *, s8 *);
u32 func_800566BC(s8*);
void func_89106424(s8 *, void *, s8 *, s32, s32);
void func_89106570(s8 *);
void func_8002A8C4(s8 *, s32, s32, s32, s32);
extern Rgba891024A4 D_8910A7F4;
extern s8 *D_8910A8A8[];
extern s8 D_8910A8B0[];
extern u8 D_8910A8C8[];
extern s8 D_8910E358[];
s32 func_891025D8(void*);
M2C_UNK func_89101D94();
extern s32 D_8910E37C;
s32 func_891066C0(s8*);
void func_80027D68(s32, s32);
void func_89105C54(s8*, s32, s32, s8*, Rgba891024A4);
M2C_UNK func_89101D94();
extern s32 D_8910D9D0;
extern s32 D_8910D9D4;

void func_891066E0(s8*, s32, s32, Rgba891024A4, s32, s32, s32);
s32 func_89101D44(s8*, s32);

s32 func_89102C40(s8* arg0) {
    UNUSED s32 pad; // FAKE: stack padding
    u32 sel;
    s32 a;
    s32 b;

    sel = M2C_FIELD(arg0, s32*, 0xB550) + M2C_FIELD(arg0, s32**, 0xB548)[M2C_FIELD(arg0, s32*, 0xB15C)] - 2;
    func_891066C0(arg0 + 0x9654);
    if (((u16*)D_800603C0)[4] & 0x4000) {
        func_8003F6AC(3);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (((u16*)D_800603C0)[4] & 0x8000) {
        func_8003F6AC(2);
        switch (M2C_FIELD(arg0, s32*, 0x969C)) {
            case 0:
                switch (sel) {
                    case 0:
                        M2C_FIELD(arg0, s32*, 0x78) = 0xF;
                        break;
                    case 1:
                        M2C_FIELD(arg0, s32*, 0x78) = 0xD;
                        break;
                    case 2:
                        M2C_FIELD(arg0, s32*, 0x78) = 0xE;
                        break;
                    case 3:
                        M2C_FIELD(arg0, s32*, 0x78) = 0;
                        break;
                    case 10:
                        M2C_FIELD(arg0, s32*, 0x78) = 2;
                        break;
                    case 11:
                        M2C_FIELD(arg0, s32*, 0x78) = 4;
                        break;
                    case 12:
                        M2C_FIELD(arg0, s32*, 0x78) = 6;
                        break;
                    case 13:
                        M2C_FIELD(arg0, s32*, 0x78) = 8;
                        break;
                    case 14:
                        M2C_FIELD(arg0, s32*, 0x78) = 0xA;
                        break;
                    case 15:
                        M2C_FIELD(arg0, s32*, 0x78) = 0xC;
                        break;
                }
                func_80027D68(M2C_FIELD(arg0, s32*, 0xB160), D_8910D990[M2C_FIELD(arg0, s32*, 0x78)]);
                M2C_FIELD(arg0, s32*, 0x88) = 0;
                break;
            case 1:
                switch (sel) {
                    case 10:
                        M2C_FIELD(arg0, s32*, 0x78) = 1;
                        break;
                    case 11:
                        M2C_FIELD(arg0, s32*, 0x78) = 3;
                        break;
                    case 12:
                        M2C_FIELD(arg0, s32*, 0x78) = 5;
                        break;
                    case 13:
                        M2C_FIELD(arg0, s32*, 0x78) = 7;
                        break;
                    case 14:
                        M2C_FIELD(arg0, s32*, 0x78) = 9;
                        break;
                    case 15:
                        M2C_FIELD(arg0, s32*, 0x78) = 0xB;
                        break;
                }
                func_80027D68(M2C_FIELD(arg0, s32*, 0xB160), D_8910D990[M2C_FIELD(arg0, s32*, 0x78)]);
                M2C_FIELD(arg0, s32*, 0x88) = 0;
                break;
            case 2:
                if (M2C_FIELD(arg0, s32*, 0x982C) != 0) {
                    a = M2C_FIELD(arg0, u8*, 0x9829);
                    b = M2C_FIELD(arg0, u8*, 0x9828);
                } else {
                    a = M2C_FIELD(arg0, u8*, 0x9828);
                    b = M2C_FIELD(arg0, u8*, 0x9829);
                }
                M2C_FIELD(arg0, s32*, 0x88) = 4;
                func_891066E0(arg0 + 0x9830, 0x110, 0xF5, D_8910A7F4, a, b, func_89101D44(arg0, 1));
                break;
        }
    }
    return 0;
}

typedef struct Ctx89102EC8 {
    /* 0x0000 */ char unk0000[0x78];
    /* 0x0078 */ s32 unk78;
    /* 0x007C */ char unk007C[0xC];
    /* 0x0088 */ s32 unk88;
    /* 0x008C */ char unk008C[0x9828 - 0x8C];
    /* 0x9828 */ u8 unk9828;
    /* 0x9829 */ u8 unk9829;
    /* 0x982A */ char unk982A[2];
    /* 0x982C */ s32 unk982C;
    /* 0x9830 */ char unk9830[0x98D4 - 0x9830];
    /* 0x98D4 */ s32 unk98D4;
    /* 0x98D8 */ char unk98D8[0x10];
    /* 0x98E8 */ s32 unk98E8;
} Ctx89102EC8;
s32 func_89106C98(void*);
M2C_UNK func_89101D94();
s32 func_89102EC8(s8 *arg)
{
  Ctx89102EC8 *arg0 = (Ctx89102EC8 *) arg;
  s32 ret;
  Ctx89102EC8 *new_var; // FAKE: permuter temp
  ret = func_89106C98(arg0->unk9830);
  if (ret == (-1))
  {
    new_var = arg0;
    new_var->unk88 = 0;
  }
  else
    if (ret == 1)
  {
    if (arg0->unk98E8 >= arg0->unk98D4)
    {
      arg0->unk982C = 0;
      arg0->unk9828 = arg0->unk98D4;
      arg0->unk9829 = arg0->unk98E8;
      arg0->unk78 = 1;
    }
    else
    {
      arg0->unk982C = 1;
      arg0->unk9829 = arg0->unk98D4;
      arg0->unk9828 = arg0->unk98E8;
      arg0->unk78 = 2;
    }
    func_89101D54((s8 *) arg0, 1);
    func_89101D94((s8 *) arg0);
    arg0->unk88 = 0;
  }
  else
  {
 do { if (ret == 2) { arg0->unk9828 = 1; arg0->unk9829 = 100; arg0->unk982C = 0; func_89101D64((s8 *) arg0, 1); func_89101D94((s8 *) arg0); arg0->unk88 = 0; } } while (0);  // FAKE
  }
  return 0;
}

s32 func_89107614(s8*);
void func_89107850(s8*, s8*);
s32 func_89102FBC(s8* arg0) {
    s8* sp24 = arg0 + 0x9920;
    s32 ret = func_89107614(sp24);

    if (ret == -1) {
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (ret == 1) {
        func_89107850(sp24, arg0 + 0x9918);
        if (M2C_FIELD(arg0, s32*, 0x9918) == 0) {
            func_89101D64(arg0, 2);
        } else {
            func_89101D54(arg0, 2);
        }
        func_89101D94(arg0);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (ret == 2) {
        M2C_FIELD(arg0, s32*, 0x9918) = 0;
        func_89101D64(arg0, 2);
        func_89101D94(arg0);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    }
    return 0;
}

s32 func_89107EC4(s8*);
void func_89108108(s8*, s8*);
s32 func_89103080(s8* arg0) {
    s8* sp24 = arg0 + 0x9B08;
    s32 ret = func_89107EC4(sp24);

    if (ret == -1) {
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (ret == 1) {
        func_89108108(sp24, arg0 + 0x9B00);
        if (M2C_FIELD(arg0, s32*, 0x9B04) == 0) {
            func_89101D64(arg0, 4);
        } else {
            func_89101D54(arg0, 4);
        }
        func_89101D94(arg0);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (ret == 2) {
        M2C_FIELD(arg0, s32*, 0x9B04) = 0;
        func_89101D64(arg0, 4);
        func_89101D94(arg0);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    }
    return 0;
}

/** One 0x20-byte list item; only the fields tested here are named. */
typedef struct Item89103144 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ char unk0C[0x10];
    /* 0x1C */ s32 unk_1C;
} Item89103144; // size = 0x20

/** List owning the items. */
typedef struct List89103144 {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ Item89103144* items;
    /* 0x14 */ char unk14[0x4];
    /* 0x18 */ s32 count;
    /* 0x1C */ char unk1C[0x4];
    /* 0x20 */ s32 limit;
} List89103144;

/** Per-item flag array holder. */
typedef struct Flags89103144 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ u16* flags;
} Flags89103144;

/**
 * For every item of arg2 whose unk_08 is zero, whose unk_1C is at
 * least arg2->limit, or that is the item *arg1, sets bit 0 of the matching
 * entry in arg0->flags.
 */
void func_89103144(Flags89103144* arg0, Item89103144** arg1, List89103144* arg2) {
    s32 i;
    Item89103144* item;

    item = arg2->items;
    i = 0;
    if (arg2->count > 0) {
        do {
            if ((item->unk_08 == 0) || (item->unk_1C >= arg2->limit) || (item == *arg1)) {
                arg0->flags[i] |= 1;
            }
            i++;
            item++;
        } while (i < arg2->count);
    }
}

void func_891031B8(s8* arg0, s8** arg1, s8* arg2) {
    s32 i;
    s32 j;
    s8* box;
    s8* entry;

    for (box = M2C_FIELD(arg2, s8**, 0), i = 0; i < M2C_FIELD(arg2, s32*, 8); i++, box += 0x24) {
        for (entry = M2C_FIELD(box, s8**, 0x10), j = 0; j < M2C_FIELD(box, s32*, 0x18); j++, entry += 0x20) {
            if ((M2C_FIELD(entry, s32*, 8) != 0) && (M2C_FIELD(entry, s32*, 0x1C) < M2C_FIELD(box, s32*, 0x20)) &&
                (entry != *arg1)) {
                break;
            }
        }
        if (j >= M2C_FIELD(box, s32*, 0x18)) {
            M2C_FIELD(arg0, u16**, 4)[i] |= 1;
        }
    }
}

typedef struct Screen89103274 {
    /* 0x0000 */ char unk0[0x2C];
    /* 0x002C */ s32 x;
    /* 0x0030 */ s32 y;
    /* 0x0034 */ s32 w;
    /* 0x0038 */ s32 h;
    /* 0x003C */ char unk3C[0x420 - 0x3C];
    /* 0x0420 */ s8 unk420[0x9654 - 0x420];
    /* 0x9654 */ s32 menuX;
    /* 0x9658 */ s32 menuY;
    /* 0x965C */ char unk965C[0x96D0 - 0x965C];
    /* 0x96D0 */ s8 menu[0x14];
    /* 0x96E4 */ s32 menuFlags;
    /* 0x96E8 */ Rgba891024A4 color;
    /* 0x96EC */ char unk96EC[0x10];
    /* 0x96FC */ s8 box[0x14];
    /* 0x9710 */ s8 list[0x34];
    /* 0x9744 */ s32 right;
    /* 0x9748 */ s32 bottom;
    /* 0x974C */ char unk974C[0x97E8 - 0x974C];
    /* 0x97E8 */ s8 items[1];
} Screen89103274;
extern u8 D_8910A8DC[];
extern s32 D_8910DD34[];
void func_89103274(Screen89103274* arg0, s8** arg1) {
    func_89106424(arg0->menu, D_8910A8DC, arg0->items, 3, (s32)D_8910DD34);
    func_8002A8C4(arg0->box, arg0->menuX + 0xE, arg0->menuY + 0x38, 0x6C, 0x1C);
    arg0->menuFlags |= 0x1000000;
    arg0->right = arg0->x + arg0->w;
    arg0->bottom = arg0->y + arg0->h;
    func_89106570(arg0->menu);
    arg0->color = D_8910A7F4;
    func_891031B8(arg0->list, arg1, arg0->unk420);
}

s32 func_89103370(s8 **arg0) {
    s32 var_v1;
    s8 *temp_v0;

    temp_v0 = *arg0;
    var_v1 = M2C_FIELD(M2C_FIELD(temp_v0, s8 **, 0), s32 *, 4) == 0x20;
    if (var_v1 != 0) {
        var_v1 = M2C_FIELD(temp_v0, s32 *, 0x1C) == 1;
    }
    return var_v1;
}

void func_8002CEEC(s8* arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4);
typedef struct Info891033A0 { u8 unk00[6]; u8 unk06; u8 unk07; u8 unk08[0xF]; } Info891033A0;
extern Info891033A0 D_80065D00[];
extern s8 D_8910DD40[];
extern s8 D_8910DD58[];

typedef struct Big891033A0 {
    /* 0x0000 */ char unk0000[0x9E58];
    /* 0x9E58 */ s32 unk9E58;
    /* 0x9E5C */ s32 unk9E5C;
} Big891033A0;
s32 func_891033A0(s8* arg0) {
    s32 ret = 0;
    s8* entry;

    func_891066C0(arg0 + 0x9654);
    if (((u16*)D_800603C0)[4] & 0x4000) {
        func_8003F6AC(3);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (((u16*)D_800603C0)[4] & 0x8000) {
        entry = M2C_FIELD(arg0, s8****, 0xB160)[0][M2C_FIELD(arg0, s32*, 0xB168)];
        switch (M2C_FIELD(arg0, s32*, 0x969C)) {
            case 0:
                func_8003F6AC(2);
                if (func_89101D80(arg0, 8) != 0) {
                    ((Big891033A0*)arg0)->unk9E58 = M2C_FIELD(entry, u8*, 8);
                }
                func_89101D94(arg0);
                M2C_FIELD(arg0, s32*, 0x88) = 0;
                break;
            case 1:
                func_8003F6AC(2);
                if (func_89101D80(arg0, 0x10) != 0) {
                    s32 id;

                    id = M2C_FIELD(entry, u8*, 8) - 1;
                    ((Big891033A0*)arg0)->unk9E5C = 1;
                    M2C_FIELD(arg0, u8*, 0x9E60) = D_80065D00[id].unk06;
                    if (D_80065D00[id].unk06 != D_80065D00[id].unk07) {
                        M2C_FIELD(arg0, u8*, 0x9E61) = D_80065D00[id].unk07;
                        ((Big891033A0*)arg0)->unk9E5C++;
                    }
                }
                func_89101D94(arg0);
                M2C_FIELD(arg0, s32*, 0x88) = 0;
                break;
            case 2:
                if (func_89103370((s8**)entry) != 0) {
                    func_8003F6AC(8);
                    func_8002CEEC(arg0 + 0xB55C, (s32)D_8910DD40, 0, 1, 0);
                    M2C_FIELD(arg0, s32*, 0x88) = 0xB;
                } else {
                    func_8003F6AC(2);
                    func_89103274((Screen89103274*)arg0, (s8**)entry);
                    M2C_FIELD(arg0, s32*, 0x88) = 8;
                }
                break;
            case 3:
                if (!(M2C_FIELD(arg0, u16**, 0x9698)[M2C_FIELD(arg0, s32*, 0x969C)] & 1)) {
                    func_8003F6AC(2);
                    M2C_FIELD(arg0, s32*, 0x88) = 0;
                    ret = 2;
                } else {
                    func_8003F6AC(8);
                    func_8002CEEC(arg0 + 0xB55C, (s32)D_8910DD58, 0, 1, 0);
                    M2C_FIELD(arg0, s32*, 0x88) = 0xC;
                }
                break;
        }
    }
    return ret;
}

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void LabPCList_ReindexBoxSlots(u8* arg0) {
    s32 i;
    s32** ptr = M2C_FIELD(arg0, s32***, 0x14);

    for (i = 0; i < M2C_FIELD(arg0, s32*, 0x1C); i++) {
        (*ptr++)[1] = i;
    }
}
