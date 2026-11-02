/* Stadium Zero fragment018_262620. */
/* C ported from the Stadium 1 decomp: src/fragments/pokedex/pokedex_214920.c. */

#include "fragments/pokedex/pokedex.h"
#include "geo_render.h"
#include "display_object_textures.h"
#include "poke_icon.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "3D140.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "gfx_rect.h"
#include "controller.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#include "pokemon_stats.h"
s32 Pokedex_DrawListScrollArrows(unk_func_888044BC_050*, s32, s32);
s32 Pokedex_HandleSpeciesListInput(unk_func_888044BC_038*, Controller*);
void Pokedex_DrawTrainerInfoCard(unk_func_888044BC_03C_02C*, s32, s32);
s32 Pokedex_DrawSortOrderLabel(unk_func_888044BC_040_030*, s32, s32);
s32 Pokedex_HandleEntryMenuInput(unk_func_888044BC_040*, Controller*);
s32 Pokedex_DrawDataPanel(unk_func_888044BC_044_02C*, s32, s32);
s32 Pokedex_DrawPreview(unk_func_888044BC_04C_02C*, s32, s32);
extern StageContext* D_8A12FF9C;
extern StageContext* D_8A12FFA0;
extern ModelLoadContext* D_8A12FFA4;
extern s32 D_8A12FFA8;
extern s32 D_8A12FFAC;
extern s32 D_8A12FFB0;
extern u8 pad_D_88826948[0x58];
extern u32 pad_D_888269A4;
extern u8 gPokedexAlphabeticalOrder[];

#include "m2c_macros.h"

void Pokedex_LoadIcon(u8* arg0, s32 arg1);
void Pokedex_ExitAreaMapScreen(void);
void Pokedex_RunEntryFlow(void);
s32 Pokedex_GetHighestSeenSpeciesIndex(void);
void Pokedex_InitFramebuffers(void);

s32 func_8A10122C(void);
s32 Pokedex_ShowEntryMenu(void);
s32 Pokedex_ShowEntry(void);
s32 Pokedex_PlayCry(void);
s32 Pokedex_RedrawAreaMapTransition(u8 arg0);
s32 Pokedex_ShowAreaMapScreen(void);

extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern u8 D_04002BA8[];
extern u8 D_04002ED0[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_8A100020(s32 arg0, s32 arg1, s32 arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060290);
    func_8001B884(arg0, arg1, 0x14, 0x14, arg2 ? D_04002BA8 : D_04002ED0, 0x14, 0x200000);
    gSPDisplayList(gDisplayListHead++, D_80060398);
}

s32 func_800209A4(s32, s8 *);                     /* extern */

s32 func_8A1000C0(s8 *arg0) {
    s32 var_v1;

    if (M2C_FIELD(arg0, s32 *, 0x1B0) != 0) {
        var_v1 = func_800209A4(M2C_FIELD(arg0, s32 *, 0x34) + 1, arg0) - 1;
    } else {
        var_v1 = M2C_FIELD(arg0, s32 *, 0x34);
    }
    return var_v1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A100104; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A100104.s")
#endif

/*
 * func_8A100318
 *
 * Initialises a record in the same way as func_8A1009E0, func_8A20034C and
 * func_8002CA34: func_8002A8C4 fills the first five words with
 * (arg1, arg2, 0x110, 0x16E, 0), the words at +0x24 and +0x28 are cleared,
 * +0x14 is set to 0x801 and +0x20 to the address of D_8A12FC38.  It then
 * sets up two sub-objects:
 *
 *   - func_80027410 (TableView_Initialize in symbol_addrs.txt) is called on
 *     the area at arg0 + 0x70 with D_80064C5C, 0x1C, 0x97 and 0x97;
 *   - func_8002EC24 is called on the object at arg0 + 0x2C with that area,
 *     arg0 + 0x80, 8, the callback func_8A100104 and the constants 0x104
 *     and 0x24.
 *
 * Finally the word at +0x1B0 is cleared and bit 0x10000 is set in the word at
 * +0x4C.  What func_80027410 and func_8002EC24 do is not established yet,
 * so the roles of those arguments are not named.
 */
M2C_UNK func_80027410(s8 *, M2C_UNK *, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8002EC24(s8 *, s8 *, s8 *, M2C_UNK, M2C_UNK *, s32, s32); /* extern */
extern M2C_UNK D_80064C5C;
extern M2C_UNK D_8A12FC38;
extern M2C_UNK func_8A100104;

void func_8A100318(void* arg0, s32 arg1, s32 arg2) {
    func_8002A8C4((s8 *)arg0, arg1, arg2, 0x110, 0x16E);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x801;
    M2C_FIELD(arg0, M2C_UNK **, 0x20) = &D_8A12FC38;
    func_80027410((s8 *)arg0 + 0x70, &D_80064C5C, 0x1C, 0x97, 0x97);
    func_8002EC24((s8 *)arg0 + 0x2C, (s8 *)arg0 + 0x70, (s8 *)arg0 + 0x80, 8, &func_8A100104, 0x104, 0x24);
    M2C_FIELD(arg0, s32 *, 0x1B0) = 0;
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) | 0x10000);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A1003D0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A1003D0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A100588; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A100588.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A100620; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A100620.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A10068C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A10068C.s")
#endif

extern Color_RGBA8 D_8A1057D4;
void func_8002A0AC(s32, s32, s32, s32, Color_RGBA8);
void func_80027F20(s32);

void func_8A100808(s32 arg0, s32 arg1, char* arg2, s32 arg3, s32 arg4) {
    if (arg4 & 0x10) {
        func_8002A0AC(arg0 + 3, arg1 + 3, 0xA2, 0x1E, D_8A1057D4);
    }
    Font_BeginTranslucentTextRendering();
    func_80027F20(arg4);
    Font_SetActive(0x10, 0);
    Font_Printf(arg0 + 0xC, arg1 + 6, arg2);
    Font_EndTexturedTextRendering();
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A1008A4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A1008A4.s")
#endif

s32 func_8002AE6C();                                /* extern */
M2C_UNK func_8002D9B8(s8 *, s32, s32, s32, s32);  /* extern */

void func_8A100954(s8 *arg0, s32 arg1) {
    if (func_8002AE6C() == 0) {
        func_8002D9B8(arg0 + 0x2C, M2C_FIELD(arg0, s32 *, 0) + 6, M2C_FIELD(arg0, s32 *, 4) + 0xC, arg1 | 0xFFED, 0);
    }
}

s32 func_8002BC14(s32);                             /* extern */
s32 func_8002DC04(s32);                             /* extern */
extern s32 D_800603C0;

s32 func_8A1009A4(s32 arg0) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_8002DC04(arg0 + 0x2C);
    var_v1 = temp_v0;
    if (temp_v0 == 0) {
        var_v1 = func_8002BC14(D_800603C0);
    }
    return var_v1;
}

/*
 * func_8A1009E0
 *
 * Initialises a record in the same way as func_8A20034C and func_8002CA34:
 * func_8002A8C4 fills the first five words with (arg1, arg2, 0x228, 0x15C, 0)
 * (the last two constants look like a width and a height, not confirmed),
 * the words at +0x20, +0x24 and +0x28 are cleared, and +0x14 is set to
 * 0x1001.
 */
void func_8A1009E0(s8 *arg0, s32 arg1, s32 arg2) {
    func_8002A8C4(arg0, arg1, arg2, 0x228, 0x15C);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x1001;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A100A24; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A100A24.s")
#endif

extern char D_8A12FCDC[];
void func_8001A944(s32, s32, const char*, ...);
void func_8001AA60(s32, s32, s32);

/**
 * Prints the two decimal digits of arg2 at (arg0, arg1). The tens digit is
 * printed by func_8001A944(arg0, arg1, D_8A12FCDC, arg2 / 10), with D_8A12FCDC
 * passed in the format-string position; the units digit is drawn by
 * func_8001AA60(arg0 + 0x54, arg1, arg2 % 10 + '0').
 * What D_8A12FCDC contains and the exact roles of the two callees are not
 * established.
 */
void func_8A100BEC(s32 arg0, s32 arg1, s32 arg2) {
    func_8001A944(arg0, arg1, D_8A12FCDC, arg2 / 10);
    func_8001AA60(arg0 + 0x54, arg1, (arg2 % 10) + 0x30);
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A100C50; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A100C50.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A100F20; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A100F20.s")
#endif

s32 func_80029658(s32, s32, s32, void*);
s32 func_80029864(s32, s32, s32, void*);
s32 func_8002A3F8(void*, s32, s32);
s32 func_8002AB84();
void func_8A100A24(s32, s32, s32, s32);
void func_8A100C50(s32, s32);
void func_8A100F20(s32, s32);
extern u8 D_8007356C;
extern u8 D_8A11FC18;

/*
 * func_8A101020
 *
 * Per-frame draw helper for the screen in this file, called by
 * func_8A10164C with D_8A130204, the value returned by func_800196F8, and
 * that function's second argument. `arg0` is a layout record: words at
 * offsets 0 and 4 act as an x/y origin that the draw calls below offset
 * (x + 0xF9, y + 0xD7 and so on), the word at offset 8 is passed to
 * func_80029658, and the word at offset 0x28 is a mode value. When the mode
 * is not 2 and func_8002AB84() returns 0, it runs func_80029658,
 * func_80029864, func_8A100C50 and func_8A100F20 at those offsets. When the
 * mode is 1 or 2 it also calls func_8002A3F8 on D_8A11FC18 with (0x32, 0x5A)
 * and then func_8A100A24(0x32, 0x5A, v, arg1), where v is 0xFF if arg2 >= 2
 * and 0x64 otherwise. What the individual calls draw is not established here;
 * the field meanings are inferred from the offsets only.
 */
void func_8A101020(void* arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    if ((M2C_FIELD(arg0, s32*, 0x28) != 2) && (func_8002AB84() == 0)) {
        func_80029658(M2C_FIELD(arg0, s32*, 0), M2C_FIELD(arg0, s32*, 4) + 0xD7, M2C_FIELD(arg0, s32*, 8), &D_8007356C);
        func_80029864(M2C_FIELD(arg0, s32*, 0) + 0xF9, M2C_FIELD(arg0, s32*, 4), 0xDE, &D_8007356C);
        func_8A100C50(M2C_FIELD(arg0, s32*, 0) + 0x100, M2C_FIELD(arg0, s32*, 4) + 6);
        func_8A100F20(M2C_FIELD(arg0, s32*, 0) + 6, M2C_FIELD(arg0, s32*, 4) + 0xDE);
    }
    temp_v0 = M2C_FIELD(arg0, s32*, 0x28);
    if ((temp_v0 == 1) || (temp_v0 == 2)) {
        func_8002A3F8(&D_8A11FC18, 0x32, 0x5A);
        func_8A100A24(0x32, 0x5A, (arg2 >= 2) ? 0xFF : 0x64, arg1);
    }
}

M2C_UNK func_8002C064(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_8A1057D0;

void func_8A101118(void) {
    func_8002C064(0x38, 0x1E0, M2C_FIELD(&D_8A1057D0, u8 *, 0), M2C_FIELD(&D_8A1057D0, u8 *, 1), (s32) M2C_FIELD(&D_8A1057D0, u8 *, 2));
}

/*
 * func_8A101154
 *
 * Makes three calls on the object arg0 points to:
 *   func_8A100318(arg0, 0x36, 0x55)
 *   func_8A100620(arg0 + 0x1B4, 0x156, 0x72)
 *   func_8A1008A4(arg0 + 0x1E0, 0x186, 0x106)
 * The second and third calls address sub-objects at fixed offsets inside
 * arg0.  The constant pairs look like screen positions, but what the
 * callees do with them has not been established.
 */
void func_8A100318(void* arg0, s32 arg1, s32 arg2);
void func_8A100620(void* arg0, s32 arg1, s32 arg2);
void func_8A1008A4(void* arg0, s32 arg1, s32 arg2);

void func_8A101154(void* arg0) {
    func_8A100318(arg0, 0x36, 0x55);
    func_8A100620((u8*)arg0 + 0x1B4, 0x156, 0x72);
    func_8A1008A4((u8*)arg0 + 0x1E0, 0x186, 0x106);
}

M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_80028060(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK func_8A1003D0(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_8A10068C(M2C_UNK *);                   /* extern */
extern M2C_UNK D_8A12FD2C;
extern M2C_UNK D_8A12FFC0;
extern M2C_UNK D_8A130174;
extern M2C_UNK D_8A1301A0;
extern s32 D_8A130230;
extern M2C_UNK D_8A130238;

s32 func_8A1011A4(s32 arg0) {
    M2C_UNK *var_a1;

    func_800069CC();
    func_8A101118();
    if (D_8A130230 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_8A130238;
    }
    func_80028060(0, var_a1, &D_8A12FD2C, D_8A130230);
    func_8A1003D0(&D_8A12FFC0, 0x10);
    func_8A10068C(&D_8A130174);
    func_8A100954(&D_8A1301A0, 2);
    return 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A10122C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A10122C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8A1013C0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A1013C0.s")
#endif

/*
 * func_8A1014EC
 *
 * Frame loop of a screen in this file (the meaning of the screen is not
 * established).  Starts with func_8000B2F4(D_800603C0) and a result `var_s3`
 * of 2, then repeats until the result is no longer 2.  Each iteration:
 *
 *   - runs the frame helpers func_8000B1FC, func_8000B220, func_8001B5F0;
 *   - while the state word at D_8A12FFC0 + 0x208 is 1 or 2, takes
 *     func_8A1009A4(&D_8A1301A0); if that is non-zero it is passed to
 *     func_8A1013C0(value, &sp50).  A return of 1 sets the result to the
 *     value func_8A1013C0 stored in sp50; a return of 2 sets the words at
 *     D_8A12FFC0 + 0x24, + 0x1D8 and + 0x204 to 7;
 *   - runs func_800158C0, func_800069CC, func_8A101118, func_8A1003D0
 *     (D_8A12FFC0, 0x10), func_8A10068C(&D_8A130174), func_8A100954
 *     (&D_8A1301A0, 2) and func_80006780;
 *   - if the word at D_8A12FFC0 + 0x28 is 4, the result becomes sp50.
 *
 * Returns the result.  What the values mean is not established.
 *
 * Note for matching: the unused leading `pad` local moves sp50 down 4 bytes
 * to the ROM's stack offset (0x50); func_8001B5F0 must be declared void.
 */
void func_8000B1FC(void);
M2C_UNK func_8000B220();
M2C_UNK func_8000B2F4(s32);
M2C_UNK func_800158C0();
void func_8001B5F0(void);
M2C_UNK func_80006780();
s32 func_8A1013C0(s32, s32 *);

s32 func_8A1014EC(void) {
    UNUSED s32 pad;
    s32 sp50;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s3;

    var_s3 = 2;
    sp50 = 0;
    func_8000B2F4(D_800603C0);
    do {
        func_8000B1FC();
        func_8000B220();
        func_8001B5F0();
        if ((M2C_FIELD(&D_8A12FFC0, s32 *, 0x208) == 1) || (M2C_FIELD(&D_8A12FFC0, s32 *, 0x208) == 2)) {
            temp_v0 = func_8A1009A4((s32) &D_8A1301A0);
            if (temp_v0 != 0) {
                temp_v0_2 = func_8A1013C0(temp_v0, &sp50);
                if (temp_v0_2 == 1) {
                    var_s3 = sp50;
                } else if (temp_v0_2 == 2) {
                    M2C_FIELD(&D_8A12FFC0, s32 *, 0x24) = 7;
                    M2C_FIELD(&D_8A12FFC0, s32 *, 0x1D8) = 7;
                    M2C_FIELD(&D_8A12FFC0, s32 *, 0x204) = 7;
                }
            }
        }
        func_800158C0();
        func_800069CC();
        func_8A101118();
        func_8A1003D0(&D_8A12FFC0, 0x10);
        func_8A10068C(&D_8A130174);
        func_8A100954(&D_8A1301A0, 2);
        func_80006780();
        if (M2C_FIELD(&D_8A12FFC0, s32 *, 0x28) == 4) {
            var_s3 = sp50;
        }
    } while (var_s3 == 2);
    return var_s3;
}

extern s32 D_8A12FF98;
extern u8 D_8A130204[];
s32 func_800196F8(s32);
s32 func_8002AAC4(void*);
void func_8A101020(void*, s32, s32);

s32 func_8A10164C(s32 arg0, s32 arg1) {
    UNUSED s32 pad[4];
    s32 sp1C;

    GeoRender_AdvanceFrameCounter();
    sp1C = func_800196F8(D_8A12FF98);
    BgStage_DrawFrame();
    if (func_8002AAC4(D_8A130204) != 0) {
        func_8A101118();
    }
    func_8A101020(D_8A130204, sp1C, arg1);
    return 0;
}

void Pokedex_LoadIcon(u8* arg0, s32 arg1) {
    unk_func_8001A024* sp1C;
    void* sp18;

    main_pool_push_state('ICON');
    sp1C = PokeIcon_CreateRenderList(D_8A12FFA4, 1, 0x50, 0x50);
    sp18 = PokeIcon_GetImage(sp1C, 0);
    func_80018234(sp1C, 0, arg1, 0x9530);
    PokeIcon_ProcessAllSlots(sp1C, 0);
    StageLoader_RunFrames(2);
    osInvalDCache(sp18, 0x3200);
    _bcopy(sp18, arg0, 0x3200);
    main_pool_pop_state('ICON');
}

extern u8 D_8A105818;

/*
 * func_8A101760
 *
 * Pushes the main-pool state with tag 0x50494354 ('PICT'), builds a model
 * preview with PokeIcon_CreateModelPreview(arg0, 0x100, 0xD2, 0, 0, 0xF4,
 * 0xD2, &D_8A105818), stores the result in D_8A12FF98, and passes it to
 * PokeIcon_SetPreviewSpecies together with arg1 and 0x108D. Only called by
 * func_8A10180C, which passes D_8A12FFA4 and D_8A12FFB8 + 1; the meaning of
 * arg1 and of D_8A105818 is not established here.
 * Matching note: the call result is stored straight into D_8A12FF98 and
 * D_8A12FF98 is read back for the second call, which the compiler folds into
 * a register move; going through a local gives a different store sequence.
 */
void func_8A101760(s32 arg0, s32 arg1) {
    main_pool_push_state(0x50494354);
    D_8A12FF98 = (s32)PokeIcon_CreateModelPreview((ModelLoadContext*)arg0, 0x100, 0xD2, 0, 0, 0xF4, 0xD2, &D_8A105818);
    PokeIcon_SetPreviewSpecies((unk_func_8001B1FC*)D_8A12FF98, arg1, 0x108D);
}

M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_800199E4(M2C_UNK *);                   /* extern */
extern M2C_UNK D_8A12FE30;

void func_8A1017DC(void) {
    func_800199E4(&D_8A12FE30);
    func_80002620(0x50494354);
}

/*
 * func_8A10180C
 *
 * Frame loop of a screen in this file (the meaning of the screen is not
 * established).  Calls func_8A101760(D_8A12FFA4, D_8A12FFB8 + 1) once, then
 * keeps the result of func_800231C8(D_8A12FFB0, D_8A12FFB8 + 1) and runs
 * one frame per iteration (func_8000B1FC, func_8000B220, func_8001B5F0,
 * func_8A10164C(0, that result), func_80006780) until the state word at
 * D_8A12FFC0 + 0x26C becomes 4.
 *
 * While that state is 1 or 2 and bit 0xC000 is set in the halfword at
 * offset 8 of the structure D_800603C0 points to (read here as a controller
 * button field; not confirmed), and func_8003BECC() returns 0, the state
 * at D_8A12FFC0 + 0x268 is set to 7 and func_8003F6AC(3) is called.
 *
 * After the loop, func_8A1017DC() is called and the words at offsets 0x24,
 * 0x1D8 and 0x204 of D_8A12FFC0 are cleared.  Always returns 1.
 */
void func_8000B1FC(void);
M2C_UNK func_8000B220();
void func_8001B5F0(void);
M2C_UNK func_80006780();
s32 func_8003BECC();
M2C_UNK func_8003F6AC(M2C_UNK);
void func_8A101760(s32, s32);
s32 func_800231C8(s32, s32);
extern s32 D_8A12FFB8;

s32 func_8A10180C(void) {
    s32 temp_s1;

    func_8A101760((s32)D_8A12FFA4, D_8A12FFB8 + 1);
    temp_s1 = func_800231C8(D_8A12FFB0, D_8A12FFB8 + 1);
    do {
        func_8000B1FC();
        func_8000B220();
        func_8001B5F0();
        if (((M2C_FIELD(&D_8A12FFC0, s32 *, 0x26C) == 1) || (M2C_FIELD(&D_8A12FFC0, s32 *, 0x26C) == 2)) && (M2C_FIELD((void *)D_800603C0, u16 *, 8) & 0xC000) && (func_8003BECC() == 0)) {
            M2C_FIELD(&D_8A12FFC0, s32 *, 0x268) = 7;
            func_8003F6AC(3);
        }
        func_8A10164C(0, temp_s1);
        func_80006780();
    } while (M2C_FIELD(&D_8A12FFC0, s32 *, 0x26C) != 4);
    func_8A1017DC();
    M2C_FIELD(&D_8A12FFC0, s32 *, 0x24) = 0;
    M2C_FIELD(&D_8A12FFC0, s32 *, 0x1D8) = 0;
    M2C_FIELD(&D_8A12FFC0, s32 *, 0x204) = 0;
    return 1;
}

M2C_UNK func_80006780();                            /* extern */
M2C_UNK func_800069CC();                            /* extern */
M2C_UNK func_8003BD3C(s32);                         /* extern */
s32 func_8003BECC();                                /* extern */
extern s32 D_8A12FFB8;
extern M2C_UNK D_8A1301A0;

s32 func_8A10193C(void) {
    func_8003BD3C(D_8A12FFB8 + 1);
    if (func_8003BECC() != 0) {
        do {
            func_800069CC();
            func_8A100954(&D_8A1301A0, 0x10);
            func_80006780();
        } while (func_8003BECC() != 0);
    }
    return 2;
}

M2C_UNK func_80005B98(M2C_UNK);                     /* extern */
M2C_UNK func_8000661C(s32);                         /* extern */
M2C_UNK func_800067BC(M2C_UNK);                     /* extern */
M2C_UNK func_80006828(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_8A1053E8(s32, s32, M2C_UNK, s32, s32); /* extern */
extern s32 D_8A12FFA8;
extern s32 D_8A12FFAC;
extern s32 D_8A12FFB8;
extern M2C_UNK func_8A104B00;

void func_8A1019AC(void) {
    func_80005B98(8);
    func_80006828(8, &func_8A1011A4);
    func_800067BC(2);
    func_8000661C(D_8A12FFA0);
    func_800067BC(2);
    func_8A1053E8(D_8A12FFB8 + 1, D_8A12FFA8, 0x70800, D_8A12FFAC, 0x4B000);
    func_80005B98(8);
    func_80006828(0xA, &func_8A104B00);
}

void Pokedex_ExitAreaMapScreen(void) {
    StageFade_Start(8);
    BgStage_RunUntilCondition(8, Pokedex_DrawAreaMapFrame);
    StageLoader_RunFrames(2);
    StageContext_SaveAndSwitch(D_8A12FF9C);
    Pokedex_ExitAreaMapPool();
    StageFade_Start(8);
    BgStage_RunUntilCondition(0xA, Pokedex_RedrawAreaMapTransition);
}

s32 Pokedex_ShowAreaMapScreen(void) {
    s32 var_s0 = 3;

    Pokedex_EnterAreaMapScreen();

    while (var_s0 == 3) {
        Cont_StartReadInputs();
        Cont_ReadInputs();
        Input_ResetRepeatState();
        Pokedex_DrawAreaMapFrame(0);
        if (Pokedex_CheckAreaMapExit() != 0) {
            var_s0 = 1;
        }
        BgStage_AdvanceFrame();
    }

    Audio_PlaySoundEffectById(SFX_MENU_BACK);
    Pokedex_ExitAreaMapScreen();
    return var_s0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8A101B30; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment018_262620/func_8A101B30.s")
#endif

void Pokedex_RunEntryFlow(void) {
    s32 var_v0 = 1;

    while (var_v0 != 0) {
        switch (var_v0) {
            case 1:
                var_v0 = func_8A10122C();
                break;

            case 2:
                var_v0 = Pokedex_ShowEntryMenu();
                break;

            case 3:
                var_v0 = Pokedex_ShowEntry();
                break;

            case 4:
                var_v0 = Pokedex_PlayCry();
                break;

            case 5:
                var_v0 = Pokedex_ShowAreaMapScreen();
                break;
        }
    }
}

s32 Pokedex_GetHighestSeenSpeciesIndex(void) {
    s32 i;

    for (i = 151; i > 0; i--) {
        if (GbSave_GetSpeciesProgressLevel(D_8A12FFB0, i) != 0) {
            break;
        }
    }

    return i;
}

void Pokedex_InitFramebuffers(void) {
    u32 sp34;
    u32 sp30;
    u32 sp2C;
    DepthBuffer* sp28;

    sp28 = main_pool_alloc(sizeof(DepthBuffer), 0);

    sp34 = D_8A12FF9C->renderTargets[0]->img_p;
    D_8A12FFA8 = D_8A12FF9C->renderTargets[0]->img_p + 0x25800;
    sp30 = D_8A12FF9C->renderTargets[1]->img_p;
    D_8A12FFAC = D_8A12FF9C->renderTargets[1]->img_p + 0x25800;
    sp2C = D_8A12FF9C->renderTargets[1]->img_p + 0x70800;

    D_8A12FFA0->renderTargets[0] = main_pool_alloc(sizeof(DepthBuffer), 0);
    D_8A12FFA0->renderTargets[1] = main_pool_alloc(sizeof(DepthBuffer), 0);

    GfxImage_Initialize(D_8A12FFA0->renderTargets[0], 0, 2, 0x140, 0xF0, sp34);
    GfxImage_Initialize(D_8A12FFA0->renderTargets[1], 0, 2, 0x140, 0xF0, sp30);
    GfxImage_Initialize(sp28, 0, 2, 0x140, 0xF0, sp2C);
    GfxImage_AttachDepthBuffer(D_8A12FFA0->renderTargets[0], sp28);
    GfxImage_AttachDepthBuffer(D_8A12FFA0->renderTargets[1], sp28);
}

void func_80027FF8(void*, s32);
void func_8A101154(void*);

void func_8A101E84(void) {
    D_8A130230 = func_80025BD8();
    if (D_8A130230 != -1) {
        func_80027FF8(&D_8A130238, D_8A130230);
    }
    func_8A101154(&D_8A12FFC0);
}

extern u32 D_86806CD0[];
extern s32 D_8A12FFB4;
extern s32 D_8A12FFB8;
extern u8 D_81000000[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_01000000[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_04000000[];
extern u8 D_00400F70[];
extern u8 D_004076E0[];
extern u8 D_88000000[];
extern u8 D_00235D70[];
extern u8 D_00238BD0[];
void func_8A101E84(void);
s32 func_8A101B30(u8);

s32 func_8A101ED4(s32 arg0, s32 arg1) {
    D_8A12FFB0 = GbSave_GetActivePort();
    D_8A12FFB4 = Pokedex_GetHighestSeenSpeciesIndex() - 1;
    D_8A12FFB8 = 0;

    main_pool_push_state('BOOK');

    D_8A12FF9C = StageContext_GetCurrent();
    D_8A12FFA0 = StageContext_Allocate(0, 1, 2, 1, 2, 0);
    Pokedex_InitFramebuffers();
    GbSave_RebuildSeenBitfield(D_8A12FFB0);
    func_8001A194(0x3D, 0);
    D_8A12FFA4 = PokeIcon_AllocFramebuffers(1);
    PokeIcon_OpenModelArchives();

    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_04000000 & 0x0F000000) >> 0x18, D_00400F70, D_004076E0, 0);

    StageLoader_UpdateSegments();
    ModelRenderer_InitDisplayRoots();
    func_8A101E84();
    BgStage_RunUntilCondition(8, func_8A101B30);
    Pokedex_RunEntryFlow();
    BgStage_RunUntilCondition(8, func_8A101B30);
    StageLoader_WaitForRetrace();
    Font_Free();

    main_pool_pop_state('BOOK');

    Fragment_QueueCall(((((u32)D_88000000) & 0x0FF00000) >> 0x14) - 0x10, D_00235D70, D_00238BD0, 0, 0);
    return 0x8040;
}
