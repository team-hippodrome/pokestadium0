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

/*
 * func_881001A8
 *
 * arg0 points to a record whose first word is a pointer to an array of
 * pointers, with two counts at offsets 4 and 8. For each index i below the
 * count at offset 8, calls func_88100100(entries[i], i). Then, for the
 * remaining indices i up to the count at offset 4, calls
 * func_800245E0(0x10, i) when func_800246A8(0x10, i) is non-zero.
 *
 * What the record fields and the 0x10 argument mean is not established.
 * The separate `base` local reproduces the ROM's register copy (the array
 * pointer is loaded before the first count is tested).
 */
s32 func_800245E0(M2C_UNK, s32);
void func_881001A8(void *arg0) {
    s32 i;
    s8 **p;
    s8 **base;

    base = M2C_FIELD(arg0, s8 ***, 0);
    i = 0;
    if (M2C_FIELD(arg0, s32 *, 8) > 0) {
        p = base;
        do {
            func_88100100(*p, i);
            i++;
            p++;
        } while (i < M2C_FIELD(arg0, s32 *, 8));
    }
    for (; i < M2C_FIELD(arg0, s32 *, 4); i++) {
        if (func_800246A8(0x10, i) != 0) {
            func_800245E0(0x10, i);
        }
    }
}

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

s32 func_8002DC04(s8*);
M2C_UNK func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;

/**
 * Menu-list input handler (same pattern as func_8A20093C and func_8200639C). Returns 0
 * immediately unless the word at arg0 + 0x28 is 1 or 2. Then, while func_8002DC04(arg0 + 0x2C)
 * is zero, reads the input result from func_8002BC14(D_800603C0): -1 plays sound
 * func_8003F6AC(3) and returns -1; 1 checks the halfword table at arg0 + 0x30 indexed by the
 * cursor word at arg0 + 0x34 -- if bit 0 of the entry is clear it plays sound 2 and returns
 * cursor + 1, otherwise it plays sound 8 and returns 0. Every other case returns 0.
 * (The meaning of the table bit is inferred from the sound choice only.)
 */
s32 func_881007AC(void* arg0) {
    s32 ret = 0;
    s32 dir;

    switch (M2C_FIELD(arg0, s32*, 0x28)) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (func_8002DC04((s8*)arg0 + 0x2C) == 0) {
        dir = func_8002BC14(D_800603C0);
        if (dir == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (dir == 1) {
            if (!(M2C_FIELD(arg0, u16**, 0x30)[M2C_FIELD(arg0, s32*, 0x34)] & 1)) {
                func_8003F6AC(2);
                ret = M2C_FIELD(arg0, s32*, 0x34) + 1;
            } else {
                func_8003F6AC(8);
            }
        }
    }
    return ret;
}

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

#ifdef NON_MATCHING
/* TODO: decompile func_88100BA4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88100BA4.s")
#endif

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

typedef struct Color88100D9C {
    u8 c[4];
} Color88100D9C;
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color88100D9C);

/**
 * Appends a call of display list D_80060270 to the current display list and
 * then calls func_80029028(arg0, arg1, 0x88, 0x64, arg2). arg0 and arg1 are
 * passed straight through (the retail code never touches $a0/$a1); arg2 is a
 * 4-byte colour passed by value.
 */
void func_88100CD0(s32 arg0, s32 arg1, Color88100D9C arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x88, 0x64, arg2);
}

/**
 * Appends a call of display list D_80060270 to the current display list and
 * then calls func_80029028(arg0 + 0x88, arg1, 0x18C, 0x64, arg2). arg1 is
 * passed straight through (the retail code never touches $a1); arg2 is a
 * 4-byte colour passed by value.
 */
void func_88100D30(s32 arg0, s32 arg1, Color88100D9C arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0 + 0x88, arg1, 0x18C, 0x64, arg2);
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

/*
 * func_88101D7C
 *
 * Stores -1 into arg2 consecutive words of the s32 array arg0, starting at
 * index arg1 (indices arg1 .. arg1 + arg2 - 1). Does nothing when
 * arg1 + arg2 <= arg1, i.e. when arg2 is not positive. The compare is signed.
 * What the -1 entries mean is not established from this function.
 */
void func_88101D7C(s32* arg0, s32 arg1, s32 arg2) {
    s32 end;

    end = arg1 + arg2;
    for (; arg1 < end; arg1++) {
        arg0[arg1] = -1;
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

typedef struct {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[0x44];
    /* 0x54 */ s32** tables;
    /* 0x58 */ char unk58[0x4];
    /* 0x5C */ s32 index;
} IndexedDrawer;

void func_8810173C(s32, s32, s32, s32, s32, s32);

/*
 * func_88101EC8
 *
 * Calls func_8810173C with the fields at +0x08 and +0x0C each increased by 6,
 * the entry at the current index (+0x5C) in the first table of arg0->tables,
 * that index, and two zero arguments.
 */
void func_88101EC8(IndexedDrawer* arg0) {
    s32 index = arg0->index;
    s32* entry = &(*arg0->tables)[index];

    func_8810173C(arg0->unk_08 + 6, arg0->unk_0C + 6, *entry, index, 0, 0);
}

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

#ifdef NON_MATCHING
/* TODO: decompile func_88102600; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88102600.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88102688; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88102688.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_88102710; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88102710.s")
#endif

s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);
M2C_UNK func_881004CC(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK *, s32, M2C_UNK *, s32, M2C_UNK *);
extern M2C_UNK D_88102D84;
extern M2C_UNK D_88102D90;
extern M2C_UNK D_88103000;
extern s32 D_88103078;
extern M2C_UNK D_88103080;

/**
 * Stores the result of func_80025BD8() in D_88103078. If it is not -1, passes it with
 * &D_88103080 to func_80027FF8 (the value is re-read from D_88103078 after the store,
 * as the retail register allocation requires). Then restarts the sub-object at
 * arg0 + 4 with func_881004CC(arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3,
 * &D_88102D90, 3, &D_88103000) and sets the state word *arg0 to 0.
 * arg0 is declared s32 to agree with the existing func_88102794(s32) prototype; it is
 * used as a byte-addressed pointer. What the object and the value mean is not established.
 */
void func_88102794(s32 arg0) {
    D_88103078 = func_80025BD8();
    if (D_88103078 != -1) {
        func_80027FF8(&D_88103080, D_88103078);
    }
    func_881004CC((s8 *)arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3, &D_88102D90, 3, &D_88103000);
    *(s32 *)arg0 = 0;
}

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

/*
 * func_881028B8
 *
 * One step of a two-state routine on the object at address `arg0` (passed
 * as an integer); the first word of the object is the state.  Returns 1 when
 * finished, otherwise 0.
 *
 *   state 0: r = func_881007AC(arg0 + 4)
 *            r == -1: return 1
 *            r == 1:  func_88102710(arg0), state = 1
 *            r == 2:  func_88102600(arg0), state = 1
 *            r == 3:  func_88102688(arg0), state = 1
 *   state 1: if func_88102184(arg0 + 0x88) == -1, restart the sub-object
 *            with func_881004CC(arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE,
 *            &D_88102D84, 3, &D_88102D90, 3, &D_8810300C) and set state 0.
 *
 * Offsets are byte offsets: `arg0 + 4` is the address four bytes in (the
 * m2c draft treated arg0 as an s32 pointer, which scales by four and does
 * not match).  What the states and helpers do is not established; the
 * helpers are still assembly.
 */
M2C_UNK func_881004CC(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK *, s32, M2C_UNK *, s32, M2C_UNK *);
s32 func_881007AC(void *);
s32 func_88102184(void *);
M2C_UNK func_88102600(s32 *);
M2C_UNK func_88102688(s32 *);
M2C_UNK func_88102710(s32 *);
extern M2C_UNK D_88102D84;
extern M2C_UNK D_88102D90;
extern M2C_UNK D_8810300C;

s32 func_881028B8(s32 arg0) {
    s32 sp3C;
    s32 temp_v0;
    s32 temp_v0_2;

    sp3C = 0;
    temp_v0 = *(s32 *)arg0;
    switch (temp_v0) {
    case 0:
        temp_v0_2 = func_881007AC((s8 *)arg0 + 4);
        if (temp_v0_2 == -1) {
            sp3C = 1;
        } else if (temp_v0_2 == 1) {
            func_88102710((s32 *)arg0);
            *(s32 *)arg0 = 1;
        } else if (temp_v0_2 == 2) {
            func_88102600((s32 *)arg0);
            *(s32 *)arg0 = 1;
        } else if (temp_v0_2 == 3) {
            func_88102688((s32 *)arg0);
            *(s32 *)arg0 = 1;
        }
        break;
    case 1:
        if (func_88102184((s8 *)arg0 + 0x88) == -1) {
            func_881004CC((s8 *)arg0 + 4, 0x40, 0x74, 0x1AC, 0xCE, &D_88102D84, 3, &D_88102D90, 3, &D_8810300C);
            *(s32 *)arg0 = 0;
        }
        break;
    }
    return sp3C;
}

s32 func_80002D98(s32);
void func_80018234(s32, s32, s32, s32);
void func_88102794(s32);
extern s32 D_88103074;
extern s32 D_881030F8;

/*
 * func_881029E0
 *
 * Setup step for this fragment: calls func_80002D98(0x26B4) (the symbol file
 * names that address Util_Malloc), keeps the result in D_881030F8, passes it
 * to func_88102794, then calls func_80018234(D_88103074, 0x18, 0x84, 0xF800).
 * What the 0x26B4-byte block holds and what func_88102794 does with it are
 * not established here (D_881030F8 is later passed to func_88102834 and
 * func_881028B8 by func_88102B58).
 * Matching note: the call result is stored straight into D_881030F8 and the
 * global is read back for the next call; going through a local gives a
 * different store sequence.
 */
void func_881029E0(void) {
    D_881030F8 = func_80002D98(0x26B4);
    func_88102794(D_881030F8);
    func_80018234(D_88103074, 0x18, 0x84, 0xF800);
}

#ifdef NON_MATCHING
/* TODO: decompile func_88102A2C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment008_1720F0/func_88102A2C.s")
#endif

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_88102834(s32);                         /* extern */
s32 func_881028B8(s32);
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
