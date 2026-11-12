/* Stadium Zero fragment016_252E10. */

#include "global.h"
#include "game_state.h"
#include "jpeg_stream.h"
#include "memory.h"
#include "stage_loader.h"
#include "m2c_macros.h"

extern u8 D_80073520[];
M2C_UNK func_80029A64(s32, s32, s32, s32, Color_RGBA8);

typedef struct Ctx89100914 {
    /* 0x0000 */ char unk0000[0x30];
    /* 0x0030 */ s32 y;
    /* 0x0034 */ s32 xEnd;
    /* 0x0038 */ char unk0038[0x84 - 0x38];
    /* 0x0084 */ s32* widths;
    /* 0x0088 */ char unk0088[0xB15C - 0x88];
    /* 0xB15C */ s32 mode;
    /* 0xB160 */ char unkB160[0xB548 - 0xB160];
    /* 0xB548 */ s32* ranges;
    /* 0xB54C */ s32 unkB54C;
    /* 0xB550 */ s32 cursor;
} Ctx89100914;
extern u8 D_8910A85C[];
extern u8 D_8910A860[];
extern Gfx D_80060270[];
extern Gfx D_80073450[];
extern u8 D_8910AB08[];
extern M2C_UNK D_800734A8;
extern char D_8910DAF8[];
extern char D_8910DB04[];
extern char D_8910DB14[];
extern char D_8910DB18[];
extern char D_8910DB20[];
extern char D_8910DB28[];
extern char D_8910DB34[];
extern char D_8910DB40[];
extern char D_8910DB4C[];
extern char D_8910DB58[];
extern char D_8910DB64[];
extern char D_8910DB70[];
extern char D_8910DB78[];
extern char D_8910DB7C[];
extern char D_8910DB88[];
extern char D_8910DB94[];
extern char D_8910DBA0[];
s32 func_891005CC(Ctx89100914* arg0);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_80027F20(s32);
void Gfx_DrawTextureIa8(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width, s32 texture_spread_x_mode);
void Font_BeginTranslucentTextRendering(void);
void Font_EndTexturedTextRendering(void);
void Gfx_SetEnvColor(s32 r, s32 g, s32 b, s32 a);
void Font_SetActive(s32 mask, s32 arg1);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void func_89100914(Ctx89100914* arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 x;
    s32 i;
    s32 hl;

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg1, arg0->y, 0x26, 0x14, *(Color_RGBA8*)D_8910A85C);
    func_80029028(arg1 + 0x26, arg0->y, 0x50, 0x14, *(Color_RGBA8*)D_8910A860);
    i = arg0->ranges[arg0->mode];
    for (x = arg1 + 0x78; x < arg0->xEnd; i++) {
        func_80029028(x, arg2, arg0->widths[i], 0x14, *(Color_RGBA8*)&D_8910A85C[(i & 1) * 4]);
        x += arg0->widths[i];
    }
    if (arg3 & 0x10) {
        func_8002A0AC(func_891005CC(arg0) + 1, arg2 + 1, arg0->widths[arg0->ranges[arg0->mode] + arg0->cursor - 2] - 2, 0x12, *(Color_RGBA8*)D_8910A860);
    }
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    Gfx_DrawTextureIa8(arg1 + 4, arg2 + 1, 0x1E, 0x12, D_8910AB08, 0x20, 0);
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    Font_SetActive(4, 0);
    Font_Printf(arg1 + 0x2E, arg2 + 2, D_8910DAF8);
    Font_EndTexturedTextRendering();
    Font_BeginTranslucentTextRendering();
    for (x = arg1 + 0x78, i = arg0->ranges[arg0->mode]; x < arg0->xEnd; i++) {
        hl = (i + 2 == arg0->ranges[arg0->mode] + arg0->cursor) ? 0x12 : 0;
        func_80027F20(hl & arg3);
        switch (i) {
            case 0:
                Font_SetActive(4, -1);
                Font_Printf(x + 1, arg2 + 2, D_8910DB04);
                break;
            case 1:
                Font_SetActive(4, 0);
                Font_Printf(x + 0xA, arg2 + 2, D_8910DB14);
                break;
            case 2:
                Font_SetActive(4, 0xC);
                Font_Printf(x + 0x16, arg2 + 2, D_8910DB18);
                break;
            case 3:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, arg2 + 2, D_8910DB20);
                break;
            case 4:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, arg2 + 2, D_8910DB28);
                break;
            case 5:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, arg2 + 2, D_8910DB34);
                break;
            case 6:
                Font_SetActive(4, 0);
                Font_Printf(x + 0x16, arg2 + 2, D_8910DB40);
                break;
            case 7:
                Font_SetActive(4, 0);
                Font_Printf(x + 0x16, arg2 + 2, D_8910DB4C);
                break;
            case 8:
                Font_SetActive(4, 0);
                Font_Printf(x + 0x16, arg2 + 2, D_8910DB58);
                break;
            case 9:
                Font_SetActive(4, 0);
                Font_Printf(x + 0x16, arg2 + 2, D_8910DB64);
                break;
            case 10:
                Font_SetActive(4, 0);
                Font_Printf(x + 0xC, arg2 + 2, D_8910DB70);
                break;
            case 11:
                Font_SetActive(4, 0xC);
                Font_Printf(x + 0xE, arg2 + 2, D_8910DB78);
                break;
            case 12:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, arg2 + 2, D_8910DB7C);
                break;
            case 13:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, arg2 + 2, D_8910DB88);
                break;
            case 14:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, arg2 + 2, D_8910DB94);
                break;
            case 15:
                Font_SetActive(4, 0);
                Font_Printf(x + 4, arg2 + 2, D_8910DBA0);
                break;
        }
        x += arg0->widths[i];
    }
    Font_EndTexturedTextRendering();
}

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 func_8002D498(u8*, s32);
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
M2C_UNK func_8001A944(s32, s32, M2C_UNK *, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
M2C_UNK func_8001AB6C();
M2C_UNK func_8001ABBC();

void func_89100F1C(s32 arg0, s32 arg1, u8* arg2, s32 arg3) {
    Color82000BC4 c;
    s32 idx;

    if ((*arg2 > 0) && (*arg2 < 0x98) && ((idx = func_8002D498(arg2, arg3)) != -1)) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(4, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(arg0, arg1, (M2C_UNK*)D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

#include "fragments/fragment016_252E10/89100020_89100914_types.h"
typedef struct Label89100FC4 {
    Color82000BC4 color;
    const char* str;
} Label89100FC4;
extern Entry89100FC4 D_8006A9D4[];
extern M2C_UNK D_800734A8;
extern char D_8910DBAC[];
s32 func_8002D454(s32, s32);
void func_89100FC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    const char* str;
    Color82000BC4 color;
    s32 idx;

    idx = func_8002D454(arg2, arg3);
    if (idx != -1) {
        if (idx == -2) {
            color = *(Color82000BC4*)&D_800734A8;
            str = D_8910DBAC;
        } else {
            color = D_80066AD8[D_8006A9D4[idx].type].color;
            str = D_8006A9D4[idx].name;
        }
        func_8001AB6C();
        func_8001A384(4, -1);
        func_8001AA9C(color.r, color.g, color.b, color.a);
        func_8001A944(arg0, arg1, (M2C_UNK*)str);
        func_8001ABBC();
    }
}

M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A944(s32, s32, M2C_UNK *, ...);         /* extern */
M2C_UNK func_8001AA60(s32, s32, s32);               /* extern */
M2C_UNK func_8001AA9C(u8, u8, u8, u8);              /* extern */
M2C_UNK func_8001AB6C();                            /* extern */
M2C_UNK func_8001ABBC();                            /* extern */
extern M2C_UNK D_800734A8;
extern M2C_UNK D_8910DBB4;
extern M2C_UNK D_8910DBBC;
extern M2C_UNK D_8910DBC0;
extern M2C_UNK D_8910DBC4;

void func_891010AC(s32 arg0, s32 arg1, s8 ***arg2) {
    s32 temp_v0;

    func_8001AB6C();
    func_8001AA9C(M2C_FIELD(&D_800734A8, u8 *, 0), M2C_FIELD(&D_800734A8, u8 *, 1), M2C_FIELD(&D_800734A8, u8 *, 2), M2C_FIELD(&D_800734A8, u8 *, 3));
    temp_v0 = M2C_FIELD(**arg2, s32 *, 4);
    switch (temp_v0) {                              /* irregular */
    case 32:
        func_8001A384(4, 0);
        func_8001A944(arg0, arg1, &D_8910DBB4);
        break;
    case 33:
        func_8001A384(4, -1);
        func_8001AA60(arg0 + 0x22, arg1, M2C_FIELD(*arg2, s32 *, 4) + 0x31);
        func_8001AA9C(0xFFU, 0xC8U, 0xFFU, 0xFFU);
        func_8001A944(arg0 - 2, arg1, &D_8910DBBC);
        break;
    case 17:
        func_8001A384(4, -1);
        func_8001AA60(arg0 + 0x22, arg1, M2C_FIELD(*arg2, s32 *, 4) + 0x31);
        func_8001AA9C(0x96U, 0xDCU, 0xD2U, 0xFFU);
        func_8001A944(arg0 - 2, arg1, &D_8910DBC0);
        break;
    case 19:
        func_8001A384(4, 0);
        func_8001A944(arg0, arg1, &D_8910DBC4);
        break;
    }
    func_8001ABBC();
}

void LabPCList_DrawPlainText(s32 arg0, s32 arg1, s8* arg2, s32 arg3, s32 arg4) {
    Font_BeginTranslucentTextRendering();
    Gfx_SetEnvColor(((Color_RGBA8*)&D_800734A8)->r, ((Color_RGBA8*)&D_800734A8)->g, ((Color_RGBA8*)&D_800734A8)->b, ((Color_RGBA8*)&D_800734A8)->a);
    Font_SetActive(4, arg4);
    Font_Printf(arg0, arg1, arg2, arg3);
    Font_EndTexturedTextRendering();
}
