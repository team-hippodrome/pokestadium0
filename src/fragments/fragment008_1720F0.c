/* Stadium Zero fragment008_1720F0. */

#include "global.h"
#include "m2c_macros.h"
#include "graphics_textures.h"

s32 func_800246A8(M2C_UNK, s32);                    /* extern */

s32 func_88100020(void) {
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

typedef struct Entry88100078 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x50];
} Entry88100078; // size = 0x54
s32 func_80020AFC(s32, s32, s32, s32);
s32 func_80020CE4(void*, s32, s32);
M2C_UNK func_80020C60(s32);
void func_88100078(s32 arg0, s32 arg1, s32 arg2, s32* arg3) {
    Entry88100078* entry = (Entry88100078*)arg3[0];
    s32 handle = func_80020AFC(arg0, arg1, arg2, 0);
    s32 i;

    for (i = 0; i < 6; i++, entry++) {
        if (func_80020CE4(entry->unk_04, 1, handle) == 0) {
            break;
        }
        entry->unk_00 = 0;
    }
    func_80020C60(handle);
    arg3[2] = i;
}

s32 func_80020B94(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s8 *, s32); /* extern */
M2C_UNK func_80020C60(s32);                         /* extern */
s32 func_80020DF0(s32, M2C_UNK, s32);               /* extern */
void func_88100100(s8 *arg0, M2C_UNK arg1)
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

#ifdef NON_MATCHING
/* TODO: decompile func_881001A8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_881001A8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8810024C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_8810024C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88100348; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88100348.s")
#endif

extern Color_RGBA8 D_88102D74;
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_80027F20(s32);

void func_88100428(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 temp_v0 = *arg5;

    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x1A, D_88102D74);
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_881004CC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_881004CC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_881005E4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_881005E4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_881007AC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_881007AC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88100898; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88100898.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_881009A0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_881009A0.s")
#endif

s32 func_8002B390(void*);
M2C_UNK func_8002BC14(s32);
extern s32 D_800603C0;
s32 func_88100B2C(s32 arg0) {
    s32 sp1C = 0;

    if (func_8002B390((u8*)arg0 + 0xA4) == 0) {
        sp1C = func_8002BC14(D_800603C0);
        if (sp1C == 1) {
            switch (M2C_FIELD(arg0, s32*, 0xA8)) {
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

typedef struct Color88100D9C {
    u8 c[4];
} Color88100D9C;
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color88100D9C);

typedef struct Window88100BA4 {
    u8 pad00[0x14];
    s32 flags;
    Color88100D9C color18;
    Color88100D9C color1C;
    s32 state20;
    s32 state24;
    s32 state28;
    s32 value2C;
} Window88100BA4;
void func_8002A8C4(void*, s32, s32, s32, s32);
extern Color88100D9C D_88102DB0[2];
void func_88100BA4(Window88100BA4* window, s32 x, s32 y, s32 value) {
    func_8002A8C4(window, x, y, 0x170, 0x68);
    window->state24 = 0;
    window->state20 = 0;
    window->state28 = 0;
    window->flags = 0x1006;
    window->color18 = D_88102DB0[0];
    window->color1C = D_88102DB0[1];
    window->value2C = value;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
void Gallery_AlbumDrawStatusText(s8* arg0) {
    u8* c;

    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        c = D_800734A8;
        Gfx_SetEnvColor(c[0], c[1], c[2], c[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(0x1C);
        Font_Printf(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0xE, M2C_FIELD(arg0, char**, 0x2C));
        Font_EndTexturedTextRendering();
    }
}

M2C_UNK func_8002BC14(s32);                         /* extern */
extern s32 D_800603C0;

void func_88100CA8(s32 arg0) {
    func_8002BC14(D_800603C0);
}

void func_88100CD0(s32 x, s32 y, Color88100D9C color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x88, 0x64, color);
}

void func_88100D30(s32 x, s32 y, Color88100D9C color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x + 0x88, y, 0x18C, 0x64, color);
}

void func_88100D9C(s32 arg0, s32 arg1, Color88100D9C arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x214, 1, arg2);
    func_80029028(arg0, arg1 + 0x63, 0x214, 1, arg2);
}

#ifdef NON_MATCHING
/* TODO: decompile func_88100E34; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88100E34.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8810105C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_8810105C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8810112C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_8810112C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8810137C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_8810137C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88101478; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88101478.s")
#endif

void func_8810165C(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0xF;
}

void func_88101670(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0xF;
    M2C_FIELD(arg0, s32 *, 0) = (s32) (arg1 * 0xF);
}

s32 func_88101690(s8 *arg0)
{
 if (0) { }
  return (*((s32 *) (((s8 *) arg0) + 0))) >= ((*((s32 *) (((s8 *) arg0) + 4))) * (*((s32 *) (((s8 *) arg0) + 8))));
}

s32 func_881016B0(s32 *arg0) {
    return *arg0 == 0;
}

s32 func_881016BC(s8* arg0) {
    if (M2C_FIELD(arg0, s32*, 0) < M2C_FIELD(arg0, s32*, 4) * M2C_FIELD(arg0, s32*, 8)) {
        M2C_FIELD(arg0, s32*, 0) += 1;
    }
    return func_88101690(arg0);
}

void Audio_QueueSoundAvoidingRecent(s32* arg0) {
    if (*arg0 > 0) {
        *arg0 -= 1;
    }
    func_881016B0(arg0);
}

s32 func_88101734(s32 *arg0) {
    return *arg0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8810173C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_8810173C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88101A38; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88101A38.s")
#endif

void func_88101D7C(s32* values, s32 first, s32 count) {
    s32 end = first + count;

    for (; first < end; first++) {
        values[first] = -1;
    }
}

void func_88101DB4(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xBC) = arg1;
    switch (arg1) {                                 /* irregular */
    case 0:
        M2C_FIELD(arg0, s32 *, 4) = 0;
        return;
    case 1:
        M2C_FIELD(arg0, s32 *, 4) = 1;
        return;
    case 2:
        M2C_FIELD(arg0, s32 *, 4) = 2;
        return;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_88101DF8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88101DF8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88101EC8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88101EC8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88101F1C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88101F1C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88102184; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88102184.s")
#endif

/*
 * func_881025C8
 *
 * Builds a table of pointers into a block of equally sized records.
 * arg1 holds the address of the first record at +0x00 and the record count
 * at +0x08.  arg0 holds the address of the pointer table at +0x00; entry i
 * is set to (first record + i * 0x220), so each record is 0x220 bytes.
 * The count is then copied to arg0 + 0x08.  What the records are is not
 * known from the code alone.
 *
 * func_820008C8 is the same routine with a record size of 0x214.
 */
void func_881025C8(s32* arg0, s32* arg1) {
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
void func_8810024C(s32*);
void func_88101DF8(void*, s32, s32, s32*, s32);
void func_88102600(s32 ui) {
    s32* records = (s32*)(ui + 0x2698);
    s32* list;

    func_80027410(records, (void*)(ui + 0x458), 0x220, 0x10, 0);
    func_8810024C(records);
    list = (s32*)(ui + 0x26A8);
    func_80027804(list, (void*)(ui + 0x2658), 0x10, 0);
    func_881025C8(list, records);
    func_88101DF8((void*)(ui + 0x88), 0x30, 0x5C, list, 1);
}

void func_80027410(void*, void*, s32, s32, s32);
void func_80027804(void*, void*, s32, s32);
void func_8810024C(s32*);
void func_88101DF8(void*, s32, s32, s32*, s32);
void func_88102688(s32 ui) {
    s32* records = (s32*)(ui + 0x2698);
    s32* list;

    func_80027410(records, (void*)(ui + 0x458), 0x220, 0x10, 0);
    func_8810024C(records);
    list = (s32*)(ui + 0x26A8);
    func_80027804(list, (void*)(ui + 0x2658), 0x10, 0);
    func_881025C8(list, records);
    func_88101DF8((void*)(ui + 0x88), 0x30, 0x5C, list, 2);
}

void func_80027410(void*, void*, s32, s32, s32);
void func_80027804(void*, void*, s32, s32);
void func_88100348(s32*);
void func_88101DF8(void*, s32, s32, s32*, s32);
void func_88102710(s32 ui) {
    s32* records = (s32*)(ui + 0x2698);
    s32* list;

    func_80027410(records, (void*)(ui + 0x458), 0x220, 4, 0);
    func_88100348(records);
    list = (s32*)(ui + 0x26A8);
    func_80027804(list, (void*)(ui + 0x2658), 4, 0);
    func_881025C8(list, records);
    func_88101DF8((void*)(ui + 0x88), 0x30, 0x5C, list, 0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_88102794; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88102794.s")
#endif

void func_800069CC(void);
void func_8002C064(s32, s32, s32, s32, s32);
extern u8 D_88102D70[];
void func_881005E4(s32*, s32);
void func_88101F1C(s32*);
M2C_UNK func_88102834(s32 a) {
    s32* arg0 = (s32*)a;
    func_800069CC();
    func_8002C064(0x38, 0x1E0, D_88102D70[0], D_88102D70[1], D_88102D70[2]);
    switch (arg0[0]) {
        case 0:
            func_881005E4(arg0 + 1, 2);
            break;
        case 1:
            func_88101F1C(arg0 + 0x22);
            break;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_881028B8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_881028B8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_881029E0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_881029E0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88102A2C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88102A2C.s")
#endif

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_88102834(s32);                         /* extern */
M2C_UNK func_881028B8(s32);                         /* extern */
extern s32 D_881030F8;

void func_88102B58(s32 arg0) {
    func_8000B1FC();
    func_8000B220();
    func_88102834(D_881030F8);
    func_881028B8(D_881030F8);
}

M2C_UNK func_80002DC0(s32);                         /* extern */
extern s32 D_881030F8;

void func_88102B98(void) {
    func_80002DC0(D_881030F8);
}

#ifdef NON_MATCHING
/* TODO: decompile func_88102BBC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88102BBC.s")
#endif
