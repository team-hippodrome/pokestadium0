/* Object boundary at 0x82005D90 (16-byte text alignment). */
/* Stadium Zero fragment007_166580. */

#include "global.h"
#include "m2c_macros.h"

typedef struct Entry82000058 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x50];
} Entry82000058; // size = 0x54
s32 func_80020AFC(s32, s32, s32, s32);
s32 func_80020CE4(void*, s32, s32);
void func_80020C60(s32);
void func_800207F8(u8*);
extern u8 D_80065D00[];

s32 func_82000058(s32 arg0, s32 arg1, s32 arg2, Entry82000058* entry);

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 func_8002D498(s32, s32);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001ABBC(void);
void func_8001AB2C(s32);
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
extern char D_82009B90[];
u32 func_800566BC(const char*);

void func_82000AC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_82000BC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_8002B390(s32);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);

s32 func_820012B4(s8* arg0);

typedef struct Color82001CCC {
    u8 c[4];
} Color82001CCC;
extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color82001CCC);
void func_82001CCC(s32 arg0, s32 arg1, Color82001CCC arg2);

M2C_UNK func_82002980();                            /* extern */

void func_82002BF8(s8 *arg0, s32 arg1, s32 arg2);

extern Color82001CCC D_82008F5C;
extern Color82001CCC D_82008F58;
void func_82003234(s8* arg0);

void func_820032E8(s8* arg0);

M2C_UNK func_8002E3F0();                            /* extern */
extern char D_800735C4[];

void func_82003688(s32 arg0);

void func_82004240(s8 *arg0);

M2C_UNK func_82004268(s8 *, s8 *, s8 *, s32, s32, s32); /* extern */

void func_820044D0(s8 *arg0);

extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;
s32 func_80025BD8(void);
void func_80027FF8(void*, s32);
s32 func_80002D98(s32);
void func_82004B0C(s32);
void func_8200573C(void);

M2C_UNK func_8000B1FC();                            /* extern */
M2C_UNK func_8000B220();                            /* extern */
M2C_UNK func_82004CE0(s32);                         /* extern */
M2C_UNK func_82004E9C(s32);                         /* extern */
extern s32 D_8200AD28;

void func_820058BC(s32 arg0);

M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK func_82004CE0(s32);                         /* extern */
extern M2C_UNK D_82009E18;
extern s32 D_8200AD28;
extern s32 D_8200AD2C;
extern M2C_UNK D_8200AD30;

s32 func_820058FC(s32 arg0);

M2C_UNK func_80002DC0(s32);                         /* extern */
extern s32 D_8200AD28;

void func_82005958(void);

extern s32 D_8200AD08[8];
extern s32 D_8200AC40;
extern s32 D_820090DC[8];
s32 func_800044AC(s32, s32);

void func_8200597C(void);

void func_8001A194(s32, s32);
s32 func_80017860(s32);
u16* func_80018F2C(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80017FDC(s32, s32, s32, s32);
s32 func_80004154(u8*, u8*, s32, s32);
void func_80017934(void);
void func_800040B4(s32, u8*, u8*);
void func_80003EB8(s32, u8*, u8*, s32);
s32 func_80001B10(u8*);
void func_8200569C(s32);
void func_80005B98(s32);
void func_80006828(s32, void*);
void func_8000A7B0(s32);
void func_80006998(s32);
void func_8000A7FC(s32);
void func_80006724(void);
void func_8000675C(void);
s32 func_8200579C(s32);
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_0A000000[];
extern u8 D_0A000C80[];
extern u8 D_0A0016D0[];
extern u8 D_003FFD60[];
extern u8 D_00400F70[];
extern u8 D_04000000[];
extern u8 D_004076E0[];
extern u8 D_05000000[];
extern u8 D_004199E0[];
extern u8 D_0042C4A0[];
extern u8 D_002F5940[];
extern u8 D_003139C0[];
extern s32 D_8200AC44;
extern u16* D_8200AC48;
extern s32 D_8200AC4C;
extern s32 D_8200AC50;
extern s32 D_8200ACFC;
extern s32 D_8200AD00;
extern s32 D_8200AD04;
extern s32 D_8200AD28;
extern s8 D_800AE8F0;
extern s32 D_82008F84;
M2C_UNK func_820059EC(void);

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80025BA0(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, s32); /* extern */
M2C_UNK func_820059EC();                            /* extern */
M2C_UNK func_82008F14();                            /* extern */
extern s8 D_00235D70;
extern s8 D_00238BD0;
extern s8 D_800AE8F0;
extern s32 D_82008F84;
extern M2C_UNK *D_8200ACF8;
extern s8 D_88000000;
s32 func_82005CCC(s32 arg0, M2C_UNK arg1);

extern Color_RGBA8 D_82009100;
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_80029658(s32, s32, s32, void*);
void func_8002A550(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void func_8002AF04(s8*, s32);
extern u8 D_8007356C;
void func_80027F20(s32);

void func_82005D90(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s32* arg5) {
    s32 temp_v0 = *arg5;

    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, temp_v0 - 6, 0x1A, D_82009100);
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

/*
 * func_82005E34
 *
 * Initialises the object arg0 (layout not established): calls
 * func_8002A8C4(arg0, arg1, arg2, arg3, arg4), clears the words at 0x28 and
 * 0x24, sets the word at 0x14 to 0x801 and the word at 0x20 to arg9. Calls
 * func_80027804 on the sub-object at arg0 + 0x50 with (arg5, arg6, arg6),
 * then func_8002D880 on the sub-objects at 0x2C, 0x50 and 0x5C with the
 * callback func_82005D90, the value arg3 - 0xC and 0x20. Finally sets bit
 * 0x10000 in the word at 0x4C and stores arg7 at 0x7C and arg8 at 0x80.
 *
 * Same shape as func_82007474. What the object is and what the values mean
 * is not established. As there, the address arg0 + 0x50 is written out
 * twice rather than cached in a local, which moves the compiler's stack
 * spill and changes the frame size.
 */
void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK func_80027804(s8 *, s32, s32, s32);         /* extern */
M2C_UNK func_8002D880(s8 *, s8 *, s8 *, void (*)(s32, s32, char *, s32, s32, s32 *), s32, s32); /* extern */
void func_82005E34(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    func_8002A8C4(arg0, arg1, arg2, arg3, arg4);
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x801;
    M2C_FIELD(arg0, s32 *, 0x20) = arg9;
    func_80027804(arg0 + 0x50, arg5, arg6, arg6);
    func_8002D880(arg0 + 0x2C, arg0 + 0x50, arg0 + 0x5C, func_82005D90, arg3 - 0xC, 0x20);
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) | 0x10000);
    M2C_FIELD(arg0, s32 *, 0x7C) = arg7;
    M2C_FIELD(arg0, s32 *, 0x80) = arg8;
}

s32 func_8002AE6C();
void func_8002D9B8(s32, s32, s32, s32, s8 *);
extern Color_RGBA8 D_82009104;
extern Color_RGBA8 D_82009108;

/**
 * Draws the object arg0 (layout not established; x at +0, y at +4, width at +8) while
 * func_8002AE6C() is zero. The sub-object at +0x2C is a list whose word at +8 is the
 * number of rows; the panel height is temp_s1 = rows * 32 + 8. Draws the frame via
 * func_80029658, a filled bar (colour D_82009100, height temp_s1) via func_80029028, a
 * highlight band via func_8002A550 (colours D_82009104 / D_82009108, height = word at
 * +0x80 * 0x1C), the list via func_8002D9B8 (flags arg1 | 0xFFED, width passed by
 * pointer in sp38), and the text pointer at index [+0x34] of the table in the word at
 * +0x7C, printed in the colour from D_800734A8 via func_8001A944.
 * What the constants mean is not established. `pad` places sp38 at sp+0x38 as in the ROM.
 */
void func_82005EE4(s8* arg0, s32 arg1) {
    s32 pad;
    s32 sp38;
    s32 temp_s1;

    if (func_8002AE6C() == 0) {
        temp_s1 = (M2C_FIELD(M2C_FIELD(arg0, s8**, 0x2C), s32*, 8) << 5) + 8;
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + temp_s1 + 5, M2C_FIELD(arg0, s32*, 8), &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) - 0xC, temp_s1, *(Color82001CCC*)&D_82009100);
        func_8002A550(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + temp_s1 + 0xC, M2C_FIELD(arg0, s32*, 8) - 0xC, M2C_FIELD(arg0, s32*, 0x80) * 0x1C, D_82009104, D_82009108);
        sp38 = M2C_FIELD(arg0, s32*, 8) - 0xC;
        func_8002D9B8(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0xA, arg1 | 0xFFED, (s8*)&sp38);
        func_8001AB6C();
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
        func_8001A384(8, 0);
        func_8001AB2C(0x1C);
        func_8001A944(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + temp_s1 + 0x10, ((char**)M2C_FIELD(arg0, s32*, 0x7C))[M2C_FIELD(arg0, s32*, 0x34)]);
        func_8001ABBC();
    }
}

extern s32 D_800603C0;

/*
 * func_820060AC
 *
 * Returns 0 immediately unless the word at arg0 + 0x28 is 1 or 2. Otherwise,
 * if func_8002DC04(arg0 + 0x2C, arg0) returns 0, it reads func_8002BC14(D_800603C0):
 * -1 calls func_8003F6AC(3) and returns -1; 1 calls func_8003F6AC(2) and
 * returns the word at arg0 + 0x34 plus 1; any other value returns 0.
 * (func_8200639C is the same pattern without the mode check.)
 */
s32 func_820060AC(void* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = M2C_FIELD(arg0, s32*, 0x28);
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (func_8002DC04((u8*)arg0 + 0x2C, arg0) == 0) {
        tmp = func_8002BC14(D_800603C0);
        if (tmp == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (tmp == 1) {
            func_8003F6AC(2);
            result = M2C_FIELD(arg0, s32*, 0x34) + 1;
        }
    }
    return result;
}

void func_82006154(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4, s8* arg5) {
    if (arg4 & 0x18) {
        func_8002A0AC(arg0 + 3, arg1 + 3, M2C_FIELD(arg5, s32*, 8) - 0x12, 0x1E, M2C_FIELD(arg5, Color_RGBA8*, 0x18));
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, arg1 + 6, arg2);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_820061F0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820061F0.s")
#endif

s32 func_8002AE6C();                                /* extern */
void func_8002D9B8(s32, s32, s32, s32, s8 *);  /* extern */
void func_82006348(s8 *arg0, s32 arg1)
{
  s8 *new_var;
  if (func_8002AE6C() == 0)
  {
    if (arg0 && arg0)
    {
    }
    func_8002D9B8(new_var = arg0 + 0x2C, (*((s32 *) (((s8 *) arg0) + 0))) + 6, (*((s32 *) (((s8 *) arg0) + 4))) + 0xC, arg1 | 0xFFED, arg0);
  }
}

s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);
extern s32 D_800603C0;
s32 func_8200639C(s32 arg0) {
    s32 sp1C = 0;
    s32 dir;

    if (func_8002DC04((u8*)arg0 + 0x2C) == 0) {
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

extern M2C_UNK D_800734A8;
void func_82006410(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    UNUSED s32 pad[4];
    Color_RGBA8 c;

    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0x46, 0x16, D_82009100);
    }
    Font_BeginTranslucentTextRendering();
    c = ((Color_RGBA8*)&D_800734A8)[(arg4 & 2) ? 0 : 1];
    if (arg4 & 1) {
        c.a = 0x4C;
    }
    Gfx_SetEnvColor(c.r, c.g, c.b, c.a);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_82006508; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82006508.s")
#endif

void func_82006410(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4);
void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK func_8002DDFC(s8 *, s32);                   /* extern */
extern M2C_UNK D_8200917C;
extern M2C_UNK D_82009F70;

/*
 * func_820066E8
 *
 * Initialises the object arg0 (layout not established): calls
 * func_8002A8C4(arg0, arg1, arg2, 0x192, 0x10F), clears the words at 0x24 and
 * 0x28, sets the word at 0x14 to 0x801 and the pointer at 0x20 to
 * &D_82009F70. Calls func_80027804 on the sub-object at arg0 + 0x2C with
 * (&D_8200917C, 4, 4), then func_8002D880 on the sub-objects at 0x38, 0x2C
 * and 0x5C with the callback func_82006410, 0x4C and 0x1C. Sets bit 0x10000
 * in the word at 0x58 and stores arg3 at 0x68.
 *
 * Then, with mask = ~arg3 (OR 0xE when arg4 == 1): for each of the bits 2, 4
 * and 8 that is set in mask, sets bit 0 of the halfword at offset 0, 2 or 4
 * of the record pointed to by the word at arg0 + 0x3C. Stores arg5 at 0x70
 * and calls func_8002DDFC(arg0 + 0x38, arg3).
 *
 * Same family as func_82007474 and func_82005E34. What the object, the bits
 * and the values mean is not established. Matching notes: the sub-object
 * addresses are held in the locals sp2C and sp28 (the ROM spills them), and
 * the unused leading `pad` local places those spill slots at sp+0x2C and
 * sp+0x28.
 */
void func_820066E8(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad;
    s8 *sp2C;
    s8 *sp28;
    s32 var_v1;

    func_8002A8C4(arg0, arg1, arg2, 0x192, 0x10F);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x801;
    M2C_FIELD(arg0, M2C_UNK **, 0x20) = &D_82009F70;
    sp2C = arg0 + 0x2C;
    func_80027804(sp2C, (s32)&D_8200917C, 4, 4);
    sp28 = arg0 + 0x38;
    func_8002D880(sp28, sp2C, arg0 + 0x5C, (void (*)(s32, s32, char *, s32, s32, s32 *))func_82006410, 0x4C, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) | 0x10000);
    M2C_FIELD(arg0, s32 *, 0x68) = arg3;
    var_v1 = ~arg3;
    if (arg4 == 1) {
        var_v1 |= 0xE;
    }
    if (var_v1 & 2) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u16 *, 0) |= 1;
    }
    if (var_v1 & 4) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u16 *, 2) |= 1;
    }
    if (var_v1 & 8) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x3C), u16 *, 4) |= 1;
    }
    M2C_FIELD(arg0, s32 *, 0x70) = arg5;
    func_8002DDFC(sp28, arg3);
}

void func_8002A3F8(void*, s32, s32);
M2C_UNK func_82006508(s32, s32, s32, s32, s32, s32);
extern u8 D_8200910C[];
extern char D_82009F84[];

/**
 * Draws the object arg0 (layout not established; x at +0, y at +4, width at +8) while
 * func_8002AE6C() is zero: a frame via func_80029658 (at y + 0x92), a filled bar via
 * func_80029028 (colour D_82009100, height 0x70), the picture D_8200910C via func_8002A3F8,
 * the text D_82009F84 in the colour from D_800734A8, the sub-object at +0x38 via
 * func_8002D9B8, and finally func_82006508 with the words at +0x68 and +0x70, 1 and a
 * value chosen from the word at +0x40 (0 -> 2, 1 -> 4, 2 -> 8, otherwise 0).
 * What the constants mean is not established.
 * Matching note: func_80029658 and func_8002D9B8 must be declared void; their
 * (unused) return value would otherwise shift the compiler's register choices.
 */
void func_82006810(s8* arg0) {
    s32 sp2C;

    sp2C = 0;
    if (func_8002AE6C() == 0) {
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0x92, M2C_FIELD(arg0, s32*, 8), &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0x99, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x70, *(Color82001CCC*)&D_82009100);
        func_8002A3F8(D_8200910C, M2C_FIELD(arg0, s32*, 0) + 0xA9, M2C_FIELD(arg0, s32*, 4) + 0xC1);
        func_8001AB6C();
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
        func_8001A384(8, 0);
        func_8001A944(M2C_FIELD(arg0, s32*, 0) + 0x36, M2C_FIELD(arg0, s32*, 4) + 0xC3, D_82009F84);
        func_8001ABBC();
        func_8002D9B8(arg0 + 0x38, M2C_FIELD(arg0, s32*, 0) + 0x110, M2C_FIELD(arg0, s32*, 4) + 0x99, 0xFEF, 0);
        switch (M2C_FIELD(arg0, s32*, 0x40)) {
            case 0:
                sp2C = 2;
                break;
            case 1:
                sp2C = 4;
                break;
            case 2:
                sp2C = 8;
                break;
        }
        func_82006508(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 0x68), M2C_FIELD(arg0, s32*, 0x70), 1, sp2C);
    }
}

/**
 * Variant of func_820076DC whose sub-object is at arg0 + 0x38. Returns 0
 * immediately unless the word at arg0 + 0x28 is 1 or 2. Otherwise, if
 * func_8002DCE0(arg0 + 0x38, arg0) returns 0, it reads
 * func_8002BC14(D_800603C0): -1 calls func_8003F6AC(3) and returns -1; 1 calls
 * func_8003F6AC(2), returns 1 and maps the word at arg0 + 0x40 (0..3) to the
 * value 2..5 stored in the word at arg0 + 0x64. Any other value returns 0.
 */
s32 func_820069B8(void* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = M2C_FIELD(arg0, s32*, 0x28);
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (func_8002DCE0((u8*)arg0 + 0x38, arg0) == 0) {
        tmp = func_8002BC14(D_800603C0);
        if (tmp == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (tmp == 1) {
            func_8003F6AC(2);
            result = 1;
            switch (M2C_FIELD(arg0, s32*, 0x40)) {
                case 0:
                    M2C_FIELD(arg0, s32*, 0x64) = 2;
                    break;
                case 1:
                    M2C_FIELD(arg0, s32*, 0x64) = 3;
                    break;
                case 2:
                    M2C_FIELD(arg0, s32*, 0x64) = 4;
                    break;
                case 3:
                    M2C_FIELD(arg0, s32*, 0x64) = 5;
                    break;
            }
        }
    }
    return result;
}

void func_82006AC0(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    UNUSED s32 pad[4];
    Color_RGBA8 c;

    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0x6E, 0x16, D_82009100);
    }
    Font_BeginTranslucentTextRendering();
    c = ((Color_RGBA8*)&D_800734A8)[(arg4 & 2) ? 0 : 1];
    if (arg4 & 1) {
        c.a = 0x4C;
    }
    Gfx_SetEnvColor(c.r, c.g, c.b, c.a);
    Font_SetActive(8, 0);
    Font_Printf(arg0 + 8, arg1 + 4, arg2);
    Font_EndTexturedTextRendering();
}

/* Partial layouts local to this function: only the fields it touches are
 * named, and the names say where they are, not what they mean. */
typedef struct {
    u16 h[6];
} HalfBank6;

typedef struct {
    u8 pad0[0x70];
    HalfBank6* bank; /* 0x70 */
    u8 pad74[0x48];
    s32 flags;       /* 0xBC */
} HalfBankOwner;

/*
 * func_82006BB8
 *
 * Reads the word at arg0 + 0xBC, inverts it, and for each of bits 1, 2 and 3
 * of the inverted value (masks 2, 4 and 8) sets bit 0 in three of the six
 * halfwords of the array that arg0 + 0x70 points to:
 *   bit 1 -> halfwords 0, 3, 4
 *   bit 2 -> halfwords 1, 3, 5
 *   bit 3 -> halfwords 2, 4, 5
 * What the flags word and the halfwords mean is not established here; the
 * bank pointer is re-read from arg0 for every update because the compiler is
 * not told the stores cannot change it.
 */
void func_82006BB8(HalfBankOwner* arg0) {
    s32 inv;

    inv = ~arg0->flags;
    if (inv & 2) {
        arg0->bank->h[0] |= 1;
        arg0->bank->h[3] |= 1;
        arg0->bank->h[4] |= 1;
    }
    if (inv & 4) {
        arg0->bank->h[1] |= 1;
        arg0->bank->h[3] |= 1;
        arg0->bank->h[5] |= 1;
    }
    if (inv & 8) {
        arg0->bank->h[2] |= 1;
        arg0->bank->h[4] |= 1;
        arg0->bank->h[5] |= 1;
    }
}

extern M2C_UNK D_82009190;
extern M2C_UNK D_820091A0;
extern M2C_UNK D_82009FCC;

/*
 * func_82006C74
 *
 * Initialises the object arg0 (layout not established): the same shape as
 * func_820066E8, but the embedded window starts at arg0 + 4 (func_8002A8C4 with
 * 0x192 x 0x163), the words at 0x28 and 0x2C are cleared, the word at 0x18 is set to
 * 0x801 and the pointer at 0x24 to &D_82009FCC. Calls func_80027804 on the
 * sub-objects at arg0 + 0x30 (&D_82009190, 4, 4) and arg0 + 0x3C (&D_820091A0, 7, 7),
 * and func_8002D880 on (0x48, 0x30, 0x90) and (0x6C, 0x3C, 0x98), both with the
 * callback func_82006AC0, 0x74 and 0x1C; sets bit 0x10000 in the words at 0x68 and
 * 0x8C and stores arg3 at 0xBC.
 *
 * Then, with mask = ~arg3 (OR 0xE when arg4 == 2): for each of the bits 2, 4 and 8 that
 * is set in mask, sets bit 0 of the halfword at offset 2, 4 or 6 of the record
 * pointed to by the word at arg0 + 0x4C. Finally calls func_82006BB8(arg0), stores
 * 1 at offset 0 and arg5 at 0xC4.
 *
 * What the object, the bits and the values mean is not established. Matching
 * notes: the sub-object addresses are held in the locals sp2C and sp28 (the ROM
 * spills them), the unused leading `pad` places the spill slots, and arg5 is stored
 * before the constant 1 so that its load comes first.
 */
void func_82006C74(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 pad;
    s8 *sp2C;
    s8 *sp28;
    s32 var_v1;

    func_8002A8C4(arg0 + 4, arg1, arg2, 0x192, 0x163);
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0x801;
    M2C_FIELD(arg0, M2C_UNK **, 0x24) = &D_82009FCC;
    sp2C = arg0 + 0x30;
    func_80027804(sp2C, (s32)&D_82009190, 4, 4);
    sp28 = arg0 + 0x48;
    func_8002D880(sp28, sp2C, arg0 + 0x90, (void (*)(s32, s32, char *, s32, s32, s32 *))func_82006AC0, 0x74, 0x1C);
    sp2C = arg0 + 0x3C;
    M2C_FIELD(arg0, s32 *, 0x68) = (s32) (M2C_FIELD(arg0, s32 *, 0x68) | 0x10000);
    func_80027804(sp2C, (s32)&D_820091A0, 7, 7);
    func_8002D880(arg0 + 0x6C, sp2C, arg0 + 0x98, (void (*)(s32, s32, char *, s32, s32, s32 *))func_82006AC0, 0x74, 0x1C);
    M2C_FIELD(arg0, s32 *, 0x8C) = (s32) (M2C_FIELD(arg0, s32 *, 0x8C) | 0x10000);
    M2C_FIELD(arg0, s32 *, 0xBC) = arg3;
    var_v1 = ~arg3;
    if (arg4 == 2) {
        var_v1 |= 0xE;
    }
    if (var_v1 & 2) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x4C), u16 *, 2) |= 1;
    }
    if (var_v1 & 4) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x4C), u16 *, 4) |= 1;
    }
    if (var_v1 & 8) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x4C), u16 *, 6) |= 1;
    }
    func_82006BB8((HalfBankOwner*)arg0);
    M2C_FIELD(arg0, s32 *, 0xC4) = arg5;
    M2C_FIELD(arg0, s32 *, 0) = 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_82006DF8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82006DF8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82007030; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82007030.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_82007398; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82007398.s")
#endif

/*
 * func_82007474
 *
 * Initialises the object arg0 (size and layout not established): calls
 * func_8002A8C4(arg0, arg1, arg2, 0x190, 0x12E), clears the words at 0x24
 * and 0x28, sets the word at 0x14 to 0x801 and the word at 0x20 to arg4.
 * Calls func_80027410 on the sub-object at arg0 + 0x54 with (arg3, 0xC, 2, 2),
 * then func_8002DECC on the sub-objects at 0x2C, 0x54 and 0x64 with
 * func_82007398 as a callback and the values 2, 0xB8 and 0xC8. Finally sets
 * bit 0x10000 in the word at 0x4C and stores arg3 at 0x68.
 *
 * What the object is and what the constants mean is not established. The
 * address arg0 + 0x54 is written out twice instead of being kept in a local:
 * a local moves the compiler's spill of it from sp+0x34 to sp+0x30.
 */
void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK func_80027410(s8 *, s32, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8002DECC(s8 *, s8 *, s8 *, M2C_UNK *, s32, s32, s32); /* extern */
extern M2C_UNK func_82007398;
void func_82007474(s8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8002A8C4(arg0, arg1, arg2, 0x190, 0x12E);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x801;
    M2C_FIELD(arg0, s32 *, 0x20) = arg4;
    func_80027410(arg0 + 0x54, arg3, 0xC, 2, 2);
    func_8002DECC(arg0 + 0x2C, arg0 + 0x54, arg0 + 0x64, &func_82007398, 2, 0xB8, 0xC8);
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32)(M2C_FIELD(arg0, s32 *, 0x4C) | 0x10000);
    M2C_FIELD(arg0, s32 *, 0x68) = arg3;
}

typedef struct Entry8200752C {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ char* text;
    /* 0x8 */ s32 unk8;
} Entry8200752C; // size = 0xC

extern Color_RGBA8 D_820091BC;
extern Color_RGBA8 D_820091C0;
M2C_UNK func_8002E230(s8*, s32, s32, s32, s32);

/**
 * Draws the object arg0 (layout not established; x at +0, y at +4, width at +8)
 * while func_8002AE6C() is zero: a box via func_800295E8 (D_800735C4), the frame via
 * func_80029658, a filled bar via func_80029028 (colour D_82009100, height 0xDC), a second
 * panel via func_8002A550 (colours D_820091BC / D_820091C0), the sub-object at +0x2C via
 * func_8002E230, and the text pointer stored at index [+0x34] of the table of 12-byte
 * records pointed to by the word at +0x68 (the pointer is the second word of a record),
 * printed in the colour from D_800734A8 via func_8001A944.
 * What the constants mean is not established.
 * Matching note: func_80029658 must be declared void (see func_82006810).
 */
void func_8200752C(s8* arg0) {
    if (func_8002AE6C() == 0) {
        func_800295E8(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0xE, 0x174, 0xCC, D_800735C4);
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0xE1, M2C_FIELD(arg0, s32*, 8), &D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) - 0xC, 0xDC, *(Color82001CCC*)&D_82009100);
        func_8002A550(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0xE8, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x40, D_820091BC, D_820091C0);
        func_8002E230(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 0x10, M2C_FIELD(arg0, s32*, 4) + 0x10, 0xFFEF, 0);
        func_8001AB6C();
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
        func_8001A384(8, 0);
        func_8001AB2C(0x1C);
        func_8001A944(M2C_FIELD(arg0, s32*, 0) + 0x14, M2C_FIELD(arg0, s32*, 4) + 0xEC, ((Entry8200752C*)M2C_FIELD(arg0, s32*, 0x68))[M2C_FIELD(arg0, s32*, 0x34)].text);
        func_8001ABBC();
    }
}

extern s32 D_800603C0;

/*
 * func_820076DC
 *
 * Returns 0 immediately unless the word at arg0 + 0x28 is 1 or 2. Otherwise,
 * if func_8002E3F0(arg0 + 0x2C, arg0) returns 0, it reads func_8002BC14(D_800603C0):
 * -1 calls func_8003F6AC(3) and returns -1; 1 calls func_8003F6AC(2) and
 * returns the word at arg0 + 0x34 plus 1; any other value returns 0.
 * (func_8200639C is the same pattern without the mode check.)
 */
s32 func_820076DC(void* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = M2C_FIELD(arg0, s32*, 0x28);
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (func_8002E3F0((u8*)arg0 + 0x2C, arg0) == 0) {
        tmp = func_8002BC14(D_800603C0);
        if (tmp == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (tmp == 1) {
            func_8003F6AC(2);
            result = M2C_FIELD(arg0, s32*, 0x34) + 1;
        }
    }
    return result;
}

typedef struct {
    /* 0x00 */ char* text;
    /* 0x04 */ u8* icon;
} IconPanel;

extern Gfx D_80060290[];
extern Gfx D_80060398[];
void func_80027F8C(s32);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);

/**
 * Draws one entry of a list at (arg0, arg1). arg2 points to {text, icon}.
 * When bit 0x10 of arg4 is set it first calls func_8002A0AC(arg0 + 3,
 * arg1 + 3, 0x14A, 0x1E, D_82009100). When bit 0x100 is set it emits the
 * display list D_80060290, draws the 0x18 by 0x18 image arg2->icon at
 * (arg0 + 0x12C, arg1 + 6) with func_8001B884 and emits D_80060398. It then
 * prints arg2->text at (arg0 + 0xC, arg1 + 6) in font 0x10 after
 * func_80027F8C(arg4). arg3 is unused. The unused pad[5] reproduces the
 * retail stack frame.
 */
void func_82007784(s32 arg0, s32 arg1, IconPanel* arg2, s32 arg3, s32 arg4) {
    UNUSED s32 pad[5];
    s32 sp28;

    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0x14A, 0x1E, D_82009100);
    }
    if (arg4 & 0x100) {
        gSPDisplayList(gDisplayListHead++, D_80060290);
        func_8001B884(arg0 + 0x12C, arg1 + 6, 0x18, 0x18, arg2->icon, 0x18, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
    sp28 = arg1 + 6;
    Font_BeginTranslucentTextRendering();
    func_80027F8C(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, sp28, arg2->text);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_820078BC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_820078BC.s")
#endif

s32 func_8002AE6C();                                /* extern */
M2C_UNK func_8002DAD8(s8 *, s32, s32, s32, s32);  /* extern */

void func_82007AF4(s8 *arg0, s32 arg1) {
    if (func_8002AE6C() == 0) {
        func_8002DAD8(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0xC, arg1 | 0xFFED, 0);
    }
}

/**
 * Variant of func_820076DC with an extra check. Returns 0 immediately unless the
 * word at arg0 + 0x28 is 1 or 2. Otherwise, if func_8002DCE0(arg0 + 0x2C, arg0)
 * returns 0, it reads func_8002BC14(D_800603C0): -1 calls func_8003F6AC(3) and
 * returns -1; 1 looks at bit 0 of the u16 at index arg0->unk_34 of the array
 * pointed to by the word at arg0 + 0x30. If that bit is clear it calls
 * func_8003F6AC(2) and returns unk_34 + 1; if it is set it calls
 * func_8003F6AC(8) and returns 0. Any other value returns 0.
 */
s32 func_82007B44(void* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = M2C_FIELD(arg0, s32*, 0x28);
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    if (func_8002DCE0((u8*)arg0 + 0x2C, arg0) == 0) {
        tmp = func_8002BC14(D_800603C0);
        if (tmp == -1) {
            func_8003F6AC(3);
            result = -1;
        } else if (tmp == 1) {
            if (!(M2C_FIELD(arg0, u16**, 0x30)[M2C_FIELD(arg0, s32*, 0x34)] & 1)) {
                func_8003F6AC(2);
                result = M2C_FIELD(arg0, s32*, 0x34) + 1;
            } else {
                func_8003F6AC(8);
            }
        }
    }
    return result;
}

typedef struct Cfg82007C30 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Cfg82007C30; // size = 0xC
extern Color_RGBA8 D_820091E4[2];
extern Cfg82007C30 D_820091EC[2];
M2C_UNK func_80018234(s8*, s32, u8, u16);

/**
 * Initialises the object arg0 (size and layout not established) and fills in a
 * per-entry table. Stores arg4 and arg5 in the second word of the two entries of
 * the 12-byte table D_820091EC, selects entry 1 when arg3 == 2 (otherwise entry 0),
 * calls func_8002A8C4(arg0, arg1, arg2, 0x235, 0x174), clears the words at 0x20, 0x24
 * and 0x28 and sets the word at 0x14 to 0x801. Copies the selected entry's first word to
 * 0x20 and builds the sub-object at arg0 + 0xCC with func_80027410 from the entry's
 * second and third words (stride 0x50, width 0x50). Calls func_80018168(arg6), stores
 * arg6 at 0xDC and then, for each of the 0xD4 entries (stride 0x50 starting at the
 * pointer stored at 0xCC), calls func_80018234 with the entry's first byte and an
 * RGBA5551 value packed from the colour D_820091E4[i & 1] (the top five bits of red, green
 * and blue go to bits 15-11, 10-6 and 5-1, and bit 0 is set).
 * What the object is and what the constants mean is not established.
 */
void func_82007C30(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s8* arg6) {
    Cfg82007C30* cfg;
    u8* entry;
    s32 sel;
    s32 i;
    s32 size;
    Color_RGBA8 color;

    if (arg3 == 2) {
        sel = 1;
    } else {
        sel = 0;
    }
    D_820091EC[0].unk4 = arg4;
    D_820091EC[1].unk4 = arg5;
    func_8002A8C4(arg0, arg1, arg2, 0x235, 0x174);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x801;
    cfg = &D_820091EC[sel];
    M2C_FIELD(arg0, s32*, 0x20) = cfg->unk0;
    size = cfg->unk8;
    func_80027410(arg0 + 0xCC, cfg->unk4, 0x50, size, size);
    func_80018168(arg6);
    entry = M2C_FIELD(arg0, u8**, 0xCC);
    M2C_FIELD(arg0, s8**, 0xDC) = arg6;
    for (i = 0; i < M2C_FIELD(arg0, s32*, 0xD4); i++) {
        color = D_820091E4[i & 1];
        func_80018234(M2C_FIELD(arg0, s8**, 0xDC), i, *entry,
                      ((color.r << 8) & 0xF800) | ((color.g * 8) & 0x7C0) | ((color.b >> 2) & 0x3E) | 1);
        entry += 0x50;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_82007D94; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment007_166580/func_82007D94.s")
#endif

extern s32 D_800603C0;

/*
 * func_82008044
 *
 * Returns 0 immediately unless the word at arg0 + 0x28 is 1 or 2. Otherwise
 * reads func_8002BC14(D_800603C0): -1 or 1 calls func_8003F6AC(3) and returns
 * -1; any other value returns 0.
 */
s32 func_82008044(void* arg0) {
    s32 result = 0;
    s32 tmp;

    tmp = M2C_FIELD(arg0, s32*, 0x28);
    if ((tmp != 1) && (tmp != 2)) {
        return 0;
    }
    tmp = func_8002BC14(D_800603C0);
    if ((tmp == -1) || (tmp == 1)) {
        func_8003F6AC(3);
        result = -1;
    }
    return result;
}

typedef struct Str4_820080B8 {
    char c[4];
} Str4_820080B8;
void func_8002A8C4(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern Str4_820080B8 D_8200920C;
extern Str4_820080B8 D_82009210;
extern u8 D_8200A0A0[];
void func_820080B8(s8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8002A8C4(arg0, arg1, arg2, 0x148, 0x68);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x2806;
    M2C_FIELD(arg0, Str4_820080B8*, 0x18) = D_8200920C;
    M2C_FIELD(arg0, Str4_820080B8*, 0x1C) = D_82009210;
    M2C_FIELD(arg0, u8**, 0x20) = D_8200A0A0;
    M2C_FIELD(arg0, s32*, 0x4C) = arg3;
}

void func_8001AB6C(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A384(s32, s32);
void func_8001AB2C(s32);
void func_8001A944(s32, s32, const char*, ...);
void func_8001ABBC(void);
extern M2C_UNK D_800734A8;
extern char D_8200A0B0[];

void func_8200813C(s8* arg0) {
    if (func_8002AE6C() == 0) {
        func_8001AB6C();
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
        func_8001A384(8, 0);
        func_8001AB2C(0x1C);
        func_8001A944(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0xE, D_8200A0B0, M2C_FIELD(arg0, s32*, 0x4C));
        func_8001ABBC();
    }
}

void func_8002AE94(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);
extern Color_RGBA8 D_82009218;
extern char D_8200A104[];
extern char D_8200A114[];
extern char D_8200A11C[];

/**
 * Initialises the object arg0 (size and layout not established); the same
 * setup as func_82008524 with different strings (D_8200A104, D_8200A114 and
 * D_8200A11C) and colour (D_82009218), and one more argument. Calls
 * func_8002A8C4(arg0, arg1, arg2, 0x134, 0x92), clears the words at 0x24 and
 * 0x28, sets the word at 0x14 to 0x2801 and the pointer at 0x20 to D_8200A104.
 * Calls func_8002AE94 on the sub-objects at arg0 + 0x2C and arg0 + 0x68, sets
 * the words at 0x58, 0x60, 0xAC and 0xA8 to 0xA, 0xC, 2 and 0, stores
 * D_800603C0 and then arg3 in the word at 0xA4 (calling func_8000B2F4 with
 * each), and finally stores arg3 at 0xB4 and arg4 at 0xB0.
 * What the object is and what the constants mean is not established.
 */
void func_820081C8(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8002A8C4(arg0, arg1, arg2, 0x134, 0x92);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x2801;
    M2C_FIELD(arg0, char**, 0x20) = D_8200A104;
    func_8002AE94(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 0x2E, M2C_FIELD(arg0, s32*, 4) + 0x6E, 0x48, D_82009218, D_8200A114);
    M2C_FIELD(arg0, s32*, 0x58) = 0xA;
    M2C_FIELD(arg0, s32*, 0x60) = 0xC;
    func_8002AE94(arg0 + 0x68, M2C_FIELD(arg0, s32*, 0) + 0xBE, M2C_FIELD(arg0, s32*, 4) + 0x6E, 0x48, D_82009218, D_8200A11C);
    M2C_FIELD(arg0, s32*, 0xAC) = 2;
    M2C_FIELD(arg0, s32*, 0xA8) = 0;
    M2C_FIELD(arg0, s32*, 0xA4) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32*, 0xA4) = arg3;
    func_8000B2F4(arg3);
    M2C_FIELD(arg0, s32*, 0xB4) = arg3;
    M2C_FIELD(arg0, s32*, 0xB0) = arg4;
}

extern Color_RGBA8 D_8200921C;
extern Color_RGBA8 D_82009220;
extern char D_8200A124[];

/**
 * Draws the object arg0 (layout not established): the same drawing code as
 * func_82008640 with different colours (D_8200921C / D_82009220) and text
 * (D_8200A124), which is printed with the word at +0xB0 passed twice as extra
 * arguments to func_8001A944. See func_82008640 for the sequence of calls; the
 * selection index at +0xA8 again decides which of the two sub-objects (+0x2C,
 * +0x68) gets 2 from func_8002AF04 and which gets 0.
 * What the constants mean is not established.
 */
void func_820082EC(s8* arg0) {
    if (func_8002AE6C() == 0) {
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0x61, M2C_FIELD(arg0, s32*, 8), &D_8007356C);
        func_8002A550(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, 0x128, 0x5C, D_8200921C, D_82009220);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0x68, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x24, *(Color82001CCC*)&D_82009100);
        func_8001AB6C();
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
        func_8001A384(8, 0);
        func_8001AB2C(0x1C);
        func_8001A944(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0xE, D_8200A124, M2C_FIELD(arg0, s32*, 0xB0), M2C_FIELD(arg0, s32*, 0xB0));
        func_8001ABBC();
        func_8002AF04(arg0 + 0x2C, (M2C_FIELD(arg0, s32*, 0xA8) == 0) ? 2 : 0);
        func_8002AF04(arg0 + 0x68, (M2C_FIELD(arg0, s32*, 0xA8) == 1) ? 2 : 0);
    }
}

s32 func_8002B390(s32);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);

s32 func_82008488(s8* arg0) {
    s32 ret = 0;
    s32 temp_v0;

    if (func_8002B390(arg0 + 0xA4) == 0) {
        temp_v0 = func_8002BC14(M2C_FIELD(arg0, s32*, 0xB4));
        if (temp_v0 == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (temp_v0 == 1) {
            switch (M2C_FIELD(arg0, s32*, 0xA8)) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    func_8003F6AC(3);
                    ret = -1;
                    break;
            }
        }
    }
    return ret;
}

extern Color_RGBA8 D_82009228;
extern char D_8200A178[];
extern char D_8200A188[];
extern char D_8200A190[];
void func_8002AE94(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);

/**
 * Initialises the object arg0 (size and layout not established): calls
 * func_8002A8C4(arg0, arg1, arg2, 0x134, 0x92), clears the words at 0x24 and
 * 0x28, sets the word at 0x14 to 0x2801 and the pointer at 0x20 to
 * D_8200A178. Calls func_8002AE94 twice, on the sub-objects at arg0 + 0x2C
 * (string D_8200A188) and arg0 + 0x68 (string D_8200A190), both with width
 * 0x48 and colour D_82009228 and positions derived from the words at 0 and 4.
 * Then sets the words at 0x58, 0x60, 0xAC and 0xA8 to 0xA, 0xC, 2 and 0, and
 * stores D_800603C0 and then arg3 in the word at 0xA4, calling func_8000B2F4
 * with each value in turn. Finally stores arg3 at 0xB0.
 * What the object is and what the constants mean is not established.
 */
void func_82008524(s8* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_8002A8C4(arg0, arg1, arg2, 0x134, 0x92);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x2801;
    M2C_FIELD(arg0, char**, 0x20) = D_8200A178;
    func_8002AE94(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 0x2E, M2C_FIELD(arg0, s32*, 4) + 0x6E, 0x48, D_82009228, D_8200A188);
    M2C_FIELD(arg0, s32*, 0x58) = 0xA;
    M2C_FIELD(arg0, s32*, 0x60) = 0xC;
    func_8002AE94(arg0 + 0x68, M2C_FIELD(arg0, s32*, 0) + 0xBE, M2C_FIELD(arg0, s32*, 4) + 0x6E, 0x48, D_82009228, D_8200A190);
    M2C_FIELD(arg0, s32*, 0xAC) = 2;
    M2C_FIELD(arg0, s32*, 0xA8) = 0;
    M2C_FIELD(arg0, s32*, 0xA4) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32*, 0xA4) = arg3;
    func_8000B2F4(arg3);
    M2C_FIELD(arg0, s32*, 0xB0) = arg3;
}

extern Color_RGBA8 D_8200922C;
extern Color_RGBA8 D_82009230;
extern char D_8200A198[];

/**
 * Draws the object arg0 (layout not established; the same kind of object that
 * func_82008524 / func_82008870 initialise: x at +0, y at +4, width at +8, a
 * selection index at +0xA8 and two sub-objects at +0x2C and +0x68). Does nothing
 * while func_8002AE6C() is non-zero. Otherwise it draws the frame with
 * func_80029658 and func_8002A550, emits D_80060270 and fills a bar with
 * func_80029028 (colour D_82009100), then prints the string D_8200A198 with the
 * font colour from D_800734A8 via func_8001A944, and finally calls func_8002AF04
 * on the two sub-objects with 2 for the one whose index (0 for +0x2C, 1 for +0x68)
 * equals the selection at +0xA8 and 0 for the other.
 * What the constants mean is not established.
 */
void func_82008640(s8* arg0) {
    if (func_8002AE6C() == 0) {
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0x61, M2C_FIELD(arg0, s32*, 8), &D_8007356C);
        func_8002A550(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, 0x128, 0x5C, D_8200922C, D_82009230);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0x68, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x24, *(Color82001CCC*)&D_82009100);
        func_8001AB6C();
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
        func_8001A384(8, 0);
        func_8001AB2C(0x1C);
        func_8001A944(M2C_FIELD(arg0, s32*, 0) + 0xE, M2C_FIELD(arg0, s32*, 4) + 0xE, D_8200A198);
        func_8001ABBC();
        func_8002AF04(arg0 + 0x2C, (M2C_FIELD(arg0, s32*, 0xA8) == 0) ? 2 : 0);
        func_8002AF04(arg0 + 0x68, (M2C_FIELD(arg0, s32*, 0xA8) == 1) ? 2 : 0);
    }
}

s32 func_8002B390(s32);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);

s32 func_820087D4(s8* arg0) {
    s32 ret = 0;
    s32 temp_v0;

    if (func_8002B390(arg0 + 0xA4) == 0) {
        temp_v0 = func_8002BC14(M2C_FIELD(arg0, s32*, 0xB0));
        if (temp_v0 == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (temp_v0 == 1) {
            switch (M2C_FIELD(arg0, s32*, 0xA8)) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    func_8003F6AC(3);
                    ret = -1;
                    break;
            }
        }
    }
    return ret;
}

extern Color_RGBA8 D_82009234;
extern char D_8200A1EC[];
extern char D_8200A1F4[];
extern char D_8200A1FC[];

/**
 * Initialises the object arg0 (size and layout not established); a sibling of
 * func_820009A4. Calls func_8002A8C4(arg0, arg1, arg2, 0x18C, 0x66), clears the words at
 * 0x20, 0x24 and 0x28 and sets the word at 0x14 to 0x1001. Calls func_8002AE94 three times,
 * on the sub-objects at arg0 + 0x2C (string D_8200A1EC), + 0x68 (D_8200A1F4) and + 0xA4
 * (D_8200A1FC, width 0x5C; the other two use width 0x48), all with colour D_82009234 and
 * positions derived from the words at 0 and 4; the words at 0x58 and 0x60 are set to 0xA
 * and 0xC between the first two calls. Then clears the word at 0xE4, stores arg3 at 0xEC
 * and 3 (arg3 != 0) or 2 (arg3 == 0) at 0xE8, and stores D_800603C0 and then arg4 in the
 * word at 0xE0 (calling func_8000B2F4 with each).
 * What the object is and what the constants mean is not established.
 */
void func_82008870(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8002A8C4(arg0, arg1, arg2, 0x18C, 0x66);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x1001;
    func_8002AE94(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 0x76, M2C_FIELD(arg0, s32*, 4) + 0x42, 0x48, D_82009234, D_8200A1EC);
    M2C_FIELD(arg0, s32*, 0x58) = 0xA;
    M2C_FIELD(arg0, s32*, 0x60) = 0xC;
    func_8002AE94(arg0 + 0x68, M2C_FIELD(arg0, s32*, 0) + 0xC6, M2C_FIELD(arg0, s32*, 4) + 0x42, 0x48, D_82009234, D_8200A1F4);
    func_8002AE94(arg0 + 0xA4, M2C_FIELD(arg0, s32*, 0) + 0x122, M2C_FIELD(arg0, s32*, 4) + 0x42, 0x5C, D_82009234, D_8200A1FC);
    M2C_FIELD(arg0, s32*, 0xE4) = 0;
    M2C_FIELD(arg0, s32*, 0xEC) = arg3;
    if (arg3 != 0) {
        M2C_FIELD(arg0, s32*, 0xE8) = 3;
    } else {
        M2C_FIELD(arg0, s32*, 0xE8) = 2;
    }
    M2C_FIELD(arg0, s32*, 0xE0) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32*, 0xE0) = arg4;
    func_8000B2F4(arg4);
}

extern Color_RGBA8 D_82009238;
extern Color_RGBA8 D_8200923C;
extern char D_8200A208[];

/**
 * Draws the object arg0 (layout not established): a variant of func_82008640 /
 * func_820082EC with a shorter frame (height 0x30) and colours D_82009238 /
 * D_8200923C, text D_8200A208 in a larger font size (0x10), and a selection index
 * at +0xE4 (rather than +0xA8) that decides which of the sub-objects at +0x2C, +0x68
 * and, only when the word at +0xEC is non-zero, +0xA4 is passed 2 by func_8002AF04
 * (index 0, 1 or 2 respectively); the others get 0.
 * What the constants mean is not established.
 */
void func_820089D4(s8* arg0) {
    if (func_8002AE6C() == 0) {
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0x35, M2C_FIELD(arg0, s32*, 8), &D_8007356C);
        func_8002A550(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 6, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x30, D_82009238, D_8200923C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0x3C, M2C_FIELD(arg0, s32*, 8) - 0xC, 0x24, *(Color82001CCC*)&D_82009100);
        func_8001AB6C();
        func_8001AA9C(M2C_FIELD(&D_800734A8, u8*, 0), M2C_FIELD(&D_800734A8, u8*, 1), M2C_FIELD(&D_800734A8, u8*, 2), M2C_FIELD(&D_800734A8, u8*, 3));
        func_8001A384(0x10, 0);
        func_8001A944(M2C_FIELD(arg0, s32*, 0) + 0x12, M2C_FIELD(arg0, s32*, 4) + 0x12, D_8200A208);
        func_8001ABBC();
        func_8002AF04(arg0 + 0x2C, (M2C_FIELD(arg0, s32*, 0xE4) == 0) ? 2 : 0);
        func_8002AF04(arg0 + 0x68, (M2C_FIELD(arg0, s32*, 0xE4) == 1) ? 2 : 0);
        if (M2C_FIELD(arg0, s32*, 0xEC) != 0) {
            func_8002AF04(arg0 + 0xA4, (M2C_FIELD(arg0, s32*, 0xE4) == 2) ? 2 : 0);
        }
    }
}

s32 func_8002B390(s32);                             /* extern */
s32 func_8002BC14(s32);                             /* extern */
M2C_UNK func_8003F6AC(M2C_UNK);                     /* extern */

s32 func_82008B94(s8 *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;

    var_s0 = 0;
    if (func_8002B390(arg0 + 0xE0) == 0) {
        temp_v0 = func_8002BC14(M2C_FIELD(arg0, s32 *, 0xE0));
        if (temp_v0 == -1) {
            func_8003F6AC(3);
            var_s0 = -1;
        } else if (temp_v0 == 1) {
            temp_v0_2 = M2C_FIELD(arg0, s32 *, 0xE4);
            switch (temp_v0_2) {                    /* irregular */
            case 0:
                var_s0 = 1;
                break;
            case 2:
                var_s0 = 2;
                break;
            case 1:
                var_s0 = -1;
                func_8003F6AC(3);
                break;
            }
        }
    }
    return var_s0;
}
