/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/dp_intro.c, src/game_state.c. */

#include "game_state.h"
#include "functions.h"
#include "input.h"
#include "save_data.h"
#include "audio_commands.h"
#include "gallery.h"
#include "gb_data.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "DDC0.h"
#include "session.h"
#include "save_data.h"
#include "minigame_dispatch.h"
#include "gb_save.h"
#include "gb_tower_audio.h"
#include "leo.h"
#include "display_object_textures.h"
#include "pokemon_stats.h"
#include "controller.h"
#include "dp_intro.h"
#include "gb_tower.h"
#include "memory.h"
#include "rsp.h"
#include "stage_loader.h"
#include "lib/ultralib/include/PR/os_internal_reg.h"
extern u16 D_8006BBB0[16][256];
extern s32 pad_D_80075660;
extern s32 pad_D_80075664;
extern s32 gCurrentGameState;
extern s32 gLastGameState;
extern s32 pad_D_80075670;
extern s16 D_800733D4;
extern s16 D_800733D8;
extern unk_D_800AE520 D_800AF990;
extern s32 pad_D_800AE534[2];
extern SessionContext gSessionContext;

#include "global.h"
#include <PR/os_internal_reg.h>
#include "dp_intro.h"
#include "scheduler.h"
#include "gfx_rect.h"
#include "crash_screen.h"
#include "profiler.h"
#include "memory.h"
extern u64 F3DEX2_data_bin[];
extern s32 D_800733F0;
extern UnkStruct80083CA0_2 D_800870A0;
extern u64 D_80087B88[0x100 / sizeof(u64)];
extern u64 D_80087C88[0x408 / sizeof(u64)];
extern u64 D_80088090[0xC08 / sizeof(u64)];
extern u64 D_80088C98[0x20000 / sizeof(u64)];
void Display_ClearFramebufferLine(u16 color);
void Display_SetBufferConfig(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);

#include "m2c_macros.h"

s32 Fragment_LoadAndCall(s32 arg0, u8* romStart, u8* romEnd, u32 arg3, u32 arg4);
void Fragment_QueueCall(s32 arg0, u8* arg1, u8* arg2, s32 arg3, s32 arg4);
TeamRoster* Trainer_GetSlots(void);
s32 GbSave_GetActivePort(void);
void GbSave_SetActivePort(s32 arg0);
void State_N64ddBootUnused(void);
void func_800268DC(void);
void Game_ShutdownAndLoadFragment(s32 arg0, s32 arg1);
void Game_ResetStorageDevice(void);
void Display_DisableBlackout(void);

void Display_ClearFramebufferLine(u16 color);
void Display_WaitForFrames(s32 arg0);
void Display_ApplyPendingVideoMode(void);

#ifdef NON_MATCHING
/* TODO: decompile func_80025540; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80025540.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80025640; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80025640.s")
#endif

void func_8002572C(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 1) = 1;
    M2C_FIELD(arg0, s16 *, 2) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80025758; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80025758.s")
#endif

/*
 * func_800257F0
 *
 * If arg0 is a valid controller-port index (0 to 3), copies that port's
 * save snapshot into the buffer at D_800AF9A8 with GbSave_CopyPortSnapshot
 * (its return value is ignored).  Otherwise the first byte of the buffer is
 * cleared.  The buffer is the destination that func_80025830 later passes on
 * as its second argument to func_80025260.
 */
extern GbSavePortSnapshot D_800AF9A8;

void func_800257F0(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4)) {
        GbSave_CopyPortSnapshot(arg0, &D_800AF9A8);
        return;
    }
    D_800AF9A8.unk_000 = 0;
}

typedef struct ContinueDataZ {
    /* 0x00 */ u8 mode;
    /* 0x01 */ u8 modeSelection;
    /* 0x02 */ u8 round;
    /* 0x03 */ u8 pad03;
    /* 0x04 */ u8 opponentHistory[8];
} ContinueDataZ; // size = 0xC
extern M2C_UNK D_800AF974;
void func_80025260(ContinueDataZ* arg0, void* arg1, BattleMon* arg2, s32 arg3);

void func_80025830(void) {
    ContinueDataZ sp1C;
    ExtendedRosterInfo* info = (*(TeamRoster**)((u8*)&gSessionContext + 0x103C))->rosterInfo;

    sp1C.mode = gSessionContext.mode;
    sp1C.modeSelection = gSessionContext.modeSelection;
    sp1C.round = gSessionContext.roundOrDemoId + 1;
    _bcopy(&D_800AF974, sp1C.opponentHistory, 8);
    func_80025260(&sp1C, &D_800AF9A8, info->unk_028, info->numberOfPokemonCanBePicked);
    Save_CommitTypedRecord(0x15, 0);
}

M2C_UNK func_80058410(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
extern M2C_UNK D_800AE8F0;
extern M2C_UNK D_800AF974;
extern M2C_UNK D_800AFB10;
extern M2C_UNK D_800AFB14;

void func_800258B4(void) {
    M2C_FIELD(&D_800AE8F0, u8 *, 0) = (u8) M2C_FIELD(&D_800AFB10, u8 *, 0);
    M2C_FIELD(&D_800AE8F0, u8 *, 1) = (u8) M2C_FIELD(&D_800AFB10, u8 *, 0);
    M2C_FIELD(&D_800AE8F0, u8 *, 2) = (u8) M2C_FIELD(&D_800AFB10, u8 *, 1);
    M2C_FIELD(&D_800AE8F0, u8 *, 3) = (u8) M2C_FIELD(&D_800AFB10, u8 *, 2);
    func_80058410(&D_800AFB14, &D_800AF974, 8, &D_800AFB10);
}

#ifdef NON_MATCHING
/* TODO: decompile func_80025910; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80025910.s")
#endif

s8 func_800253BC(M2C_UNK *, s8 *, M2C_UNK *);       /* extern */
M2C_UNK func_80025910(s8);                          /* extern */
s32 func_80057910(s8 *, M2C_UNK *, M2C_UNK);        /* extern */
extern s8 D_800AE8F6;
extern M2C_UNK D_800AE910;

/*
 * func_80025A64
 *
 * Clears the byte at D_800AE8F0 + 0x1095, then calls
 * func_800253BC(&D_800AFB10, buf, &D_800AE910) with a 0x162-byte local
 * buffer. If it returns -1 the function returns 0. Otherwise the result is
 * stored to the byte D_800AE8F6 and:
 *  - if buf[0] == 0: calls func_80025910(buf[0]), sets bit 0 of the byte at
 *    D_800AE8F0 + 0x1095, sets the byte at + 0x1094 to 0xFF, calls
 *    func_800257F0(-1) and returns 1;
 *  - otherwise, if D_800733D4 is in 0..3, GbSave_CopyPortSnapshot(D_800733D4,
 *    &D_800AF9A8) is non-zero and func_80057910(buf, &D_800AF9A8, 0x162)
 *    returns 0 (func_80057910 is libultra bcmp, so: the 0x162 bytes of buf
 *    equal the snapshot just copied): calls func_80025910(buf[0]), sets
 *    bit 0 of + 0x1095, stores D_800733D4 at + 0x1094, calls
 *    func_800257F0(D_800733D4) and returns 1;
 *  - in every other case returns 0.
 *
 * What the buffer, D_800AE8F0's fields and the two helpers do is not
 * established. Matching notes: the unused `pad` local sits between the
 * buffer and `ret` as in the ROM's frame (buffer at sp+0x34, ret at sp+0x2C),
 * and the bit-0 update is written before the store of 0xFF to match the
 * ROM's register order.
 */
s32 func_80025A64(void) {
    s8 buf[0x162];
    UNUSED s32 pad;
    s32 ret;
    s8 temp_v0;

    ret = 0;
    M2C_FIELD(&D_800AE8F0, u8 *, 0x1095) = 0U;
    temp_v0 = func_800253BC(&D_800AFB10, buf, &D_800AE910);
    if (temp_v0 != -1) {
        D_800AE8F6 = temp_v0;
        if (buf[0] == 0) {
            func_80025910(buf[0]);
            M2C_FIELD(&D_800AE8F0, u8 *, 0x1095) = (u8) (M2C_FIELD(&D_800AE8F0, u8 *, 0x1095) | 1);
            M2C_FIELD(&D_800AE8F0, u8 *, 0x1094) = 0xFF;
            func_800257F0(-1);
            ret = 1;
        } else if ((D_800733D4 >= 0) && (D_800733D4 < 4) && (GbSave_CopyPortSnapshot(D_800733D4, &D_800AF9A8) != 0) && (func_80057910(buf, &D_800AF9A8, 0x162) == 0)) {
            func_80025910(buf[0]);
            M2C_FIELD(&D_800AE8F0, u8 *, 0x1095) = (u8) (M2C_FIELD(&D_800AE8F0, u8 *, 0x1095) | 1);
            M2C_FIELD(&D_800AE8F0, s8 *, 0x1094) = (s8) D_800733D4;
            func_800257F0((s32) D_800733D4);
            ret = 1;
        }
    }
    return ret;
}

s32 Fragment_LoadAndCall(s32 arg0, u8* romStart, u8* romEnd, u32 arg3, u32 arg4) {
    s32 result;
    FragmentEntry func;

    func = Fragment_Load(arg0, romStart, romEnd);

    result = func(arg3, arg4);

    main_pool_try_free(func);

    return result;
}

void Fragment_QueueCall(s32 arg0, u8* arg1, u8* arg2, s32 arg3, s32 arg4) {
    D_800AF990.unk_00 = 1;
    D_800AF990.fragment_id = arg0;
    D_800AF990.rom_start = arg1;
    D_800AF990.rom_end = arg2;
    D_800AF990.arg0 = arg3;
    D_800AF990.arg1 = arg4;
}

TeamRoster* Trainer_GetSlots(void) {
    return gSessionContext.trainerSlots;
}

s32 GbSave_GetActivePort(void) {
    return D_800733D4;
}

void GbSave_SetActivePort(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4)) {
        D_800733D4 = arg0;
        D_800733D8 = 1;
    }
}

void Ui_DrawGradientPanel(s32 x1, s32 y1, s32 width, s32 height, Color_RGB8* top_color, Color_RGB8* bottom_color);
extern Color_RGB8 D_800733DC;
extern Color_RGB8 D_800733E0;
extern char D_8007B7D0[];
extern char D_8007B7E0[];
extern char D_8007B804[];
extern char D_8007B824[];
extern char D_8007B844[];
extern char D_8007B858[];
extern char D_8007B874[];
extern char D_8007B894[];

void func_80025C0C(s32 arg0) {
    Color_RGB8 sp2C = D_800733DC;
    Color_RGB8 sp28 = D_800733E0;
    UNUSED s32 pad[2];

    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    Ui_DrawGradientPanel(0x90, 0x64, 0x160, 0xC8, &sp2C, &sp28);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(8, -2);
    Font_Printf(0xB0, 0xB4, D_8007B7D0);
    Font_Printf(0xB0, 0xD0, D_8007B7E0);
    Font_Printf(0xB0, 0xEC, D_8007B804);
    Font_Printf(0xB0, 0x108, D_8007B824);
    Gfx_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
    Font_Printf(0x12E, 0xB4, D_8007B844);
    if (arg0 == 2) {
        Font_SetActive(0x10, -2);
        Font_Printf(0xBC, 0x84, D_8007B858);
    } else if (arg0 == 3) {
        Font_Printf(0xB0, 0x74, D_8007B874);
        Font_Printf(0xB0, 0x90, D_8007B894);
    }
    Font_EndTexturedTextRendering();
    BgStage_AdvanceFrame();
}

void Ui_DrawGradientPanel(s32 x1, s32 y1, s32 width, s32 height, Color_RGB8* top_color, Color_RGB8* bottom_color);
extern Color_RGB8 D_800733E4;
extern Color_RGB8 D_800733E8;
extern char D_8007B8B4[];

void func_80025D8C(void) {
    Color_RGB8 sp2C = D_800733E4;
    Color_RGB8 sp28 = D_800733E8;
    UNUSED s32 pad[2];

    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    Ui_DrawGradientPanel(0x90, 0x96, 0x160, 0x38, &sp2C, &sp28);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(0x10, -2);
    Font_Printf(0xDD, 0xA6, D_8007B8B4);
    Font_EndTexturedTextRendering();
    BgStage_AdvanceFrame();
}

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_80006724();                            /* extern */
M2C_UNK func_8000675C();                            /* extern */
M2C_UNK func_8001A194(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8001A360();                            /* extern */
s32 func_80021B30(s32);                             /* extern */
void func_80025C0C(s32);
void func_80025D8C(void);
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_01000000;

void func_80025E3C(s32 arg0) {
    M2C_UNK var_s0;
    s32 temp_v0;

    var_s0 = 2;
    func_8000256C(0x47424552);
    func_8001A194(0x18, 0);
    func_80003EB8((u32) ((s32) &D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_8000675C();
    do {
        temp_v0 = func_80021B30(arg0);
        if (temp_v0 == 1) {
            var_s0 = 1;
        }
        if (temp_v0 == 3) {
            var_s0 = 3;
        }
        func_80025C0C(var_s0);
    } while (temp_v0 != 2);
    func_80025D8C();
    func_80025D8C();
    func_80006724();
    func_8001A360();
    func_80002620(0x47424552);
}

M2C_UNK func_80025758(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_80025B60(s32, M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
extern M2C_UNK D_0015F390;
extern M2C_UNK D_0015F8F0;
extern M2C_UNK D_0017ED00;
extern M2C_UNK D_00232510;
extern s32 D_800733C8;
extern M2C_UNK D_800AE8F0;
extern M2C_UNK D_81500000;
extern M2C_UNK D_82100000;

void func_80025F3C(void) {
    func_80025B60(((u32) ((s32) &D_81500000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015F390, &D_0015F8F0, 0, NULL);
    func_80025758(5, 3, 3);
    func_80025B60(((u32) ((s32) &D_82100000 & 0x0FF00000) >> 0x14) - 0x10, &D_0017ED00, &D_00232510, 0, &D_800AE8F0);
    D_800733C8 = 0x8010;
}

extern M2C_UNK D_81200000;
extern M2C_UNK D_0015E220;
extern s32 D_800AF988;

void State_FastN64Logo(void) {
    D_800733C8 = func_80025B60(((u32) ((s32) &D_81200000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015E220, &D_0015F390, 0, NULL);
    M2C_FIELD(&D_800AE8F0, u8*, 2) = 0;
    M2C_FIELD(&D_800AE8F0, s16*, 0x1096) = 0;
    switch (D_800733C8) {
        case 0x8010:
            func_80025B60(((u32) ((s32) &D_82100000 & 0x0FF00000) >> 0x14) - 0x10, &D_0017ED00, &D_00232510, 0, &D_800AE8F0);
            break;
        case 0x8020:
            D_800733D4 = -1;
            D_800AF988 = 0;
            D_800733C8 = 0x8040;
            break;
        default:
            D_800733D4 = 0;
            D_800AF988 = 1;
            break;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_800260C4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800260C4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80026368; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80026368.s")
#endif

extern M2C_UNK D_81300000;
extern M2C_UNK D_0015FCE0;
extern s32 D_800733CC;
void func_8000A838(s32);
void func_8000A8DC(void);
void func_8000A904(void);
void func_8000AC78(UnkInputStruct8000D738*);
s32 func_8000ADE8(void);
void func_8000AE1C(UnkInputStruct8000D738*);
void func_800268E4(s32, s32);
void func_80021C6C(s32);
void func_80023C30(void);
void func_80025130(s32);
void func_8002404C(s32, s32);

void State_GbTower(void) {
    s32 sp2C;
    UnkInputStruct8000D738 sp24;

    main_pool_push_state('EMU0');
    func_8000A838(1);
    Display_WaitForFrames(2);
    func_8000A8DC();

    sp24.unk_04 = main_pool_alloc(sizeof(*sp24.unk_04), 0);

    func_80025B60(((u32) ((s32) &D_81300000 & 0x0FF00000) >> 0x14) - 0x10, &D_0015F8F0, &D_0015FCE0, D_800733D4, (M2C_UNK*)&sp24);
    func_8000AC78(&sp24);

    sp2C = func_8000ADE8();

    func_8000AE1C(&sp24);
    Display_WaitForFrames(2);
    func_8000A904();

    if (sp2C != 0) {
        func_800268E4(D_800733D4, sp2C);
    }

    func_80021C6C(D_800733D4);
    func_80023C30();
    func_80025130(sp24.unk_00);
    func_8002404C(0x14, 0);
    D_800733C8 = D_800733CC;
    D_800AF988 = 1;
    main_pool_pop_state('EMU0');
}

extern s32 D_800733C8;

void func_80026898(void) {
    D_800733C8 = 0x8010;
}

void State_N64ddBootUnused(void) {
    Audio_WaitForIdle(1);
    Display_WaitForFrames(2);
    LeoBootGame(D_800AB200.unk_08);
}

void func_800268DC(void) {
}

void Game_ShutdownAndLoadFragment(s32 arg0, s32 arg1) {
    osViBlack(1);
    GbTower_PowerOffAllPaks();
    Audio_FadeOutForShutdown();
    Game_ResetStorageDevice();
    Display_ClearFramebufferLine(1);
    Display_ApplyPendingVideoMode();
    Display_WaitForFrames(0xA);

    main_pool_pop_state('GAME');

    FRAGMENT_LOAD_AND_CALL(FRAGMENT_FATAL_ERROR_SCREEN, arg0, arg1);
}

void Game_ResetStorageDevice(void) {
    Storage_ResetDisk();
}

#ifdef NON_MATCHING
/* TODO: decompile func_800269A0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800269A0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80026B50; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80026B50.s")
#endif

s32 func_800023C4(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_80026B50(s16, s16, s16, s32, s32, s32, s32, s32); /* extern */
extern s32 D_800733F0;

/*
 * func_800270B4
 *
 * Calls func_800023C4(0xA00, 0) and func_800023C4(0xA70, 0) (they look like
 * allocations, but that is not established here), then calls func_80026B50
 * with (arg0, arg1, arg2 as halfwords, first result, second result, arg3,
 * arg4, arg5). Stores the second result in D_800733F0 (the word that
 * Display_DisableBlackout clears) and returns it.
 *
 * Matching note: the unused leading `pad1` local only makes the stack frame
 * and slots match the ROM (0x38 bytes, blocks at sp+0x30 and sp+0x2C).
 */
s32 func_800270B4(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s16 arg4, s16 arg5) {
    s32 pad;
    s32 sp30;
    s32 sp2C;

    sp30 = func_800023C4(0xA00, 0);
    sp2C = func_800023C4(0xA70, 0);
    func_80026B50(arg0, arg1, arg2, sp30, sp2C, arg3, (s32) arg4, (s32) arg5);
    D_800733F0 = sp2C;
    return sp2C;
}

void Display_DisableBlackout(void) {
    D_800733F0 = 0;
}

extern s32 D_800733F0;
volatile long long func_80027140(s32 arg0, s8 *arg1)
{
  s32 new_var;
  new_var = arg0;
  if ((new_var == 2) && (D_800733F0 != 0))
  {
    *((s32 *) (((s8 *) arg1) + 0x18)) = (s32) D_800733F0;
  }
}

typedef struct Key80027168 {
    s16 n;
    Vec3s a;
    Vec3s b;
} Key80027168;
typedef struct Obj80027168 {
    s32 unk_00;
    Key80027168* keys;
    Vec3f unk_08;
    Vec3f unk_14;
    Vec3f unk_20;
    Vec3f unk_2C;
    s16 unk_38;
    s16 unk_3A;
} Obj80027168;
Vec3f* Vec3f_FromVec3s(Vec3f* float_vector, Vec3s* int_vector);
Vec3s* Vec3s_Add(Vec3s* dest, Vec3s* a, Vec3s* b);
Vec3s* Vec3s_Subtract(Vec3s* dest, Vec3s* a, Vec3s* subtrahend);

M2C_UNK func_80027168(arg0)
    Obj80027168* arg0;
{
    Vec3s sp30;
    Vec3s sp28;

    if ((arg0->unk_3A = arg0->keys->n) == 0) {
        return 0;
    }
    arg0->unk_38 = 0;
    Vec3s_Add(&sp30, &arg0->keys->a, &arg0->keys->b);
    Vec3s_Subtract(&sp28, &arg0->keys[1].a, &arg0->keys[1].b);
    Vec3f_FromVec3s(&arg0->unk_08, &arg0->keys->a);
    Vec3f_FromVec3s(&arg0->unk_14, &sp30);
    Vec3f_FromVec3s(&arg0->unk_20, &sp28);
    Vec3f_FromVec3s(&arg0->unk_2C, &arg0->keys[1].a);
    arg0->keys++;
    return 1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80027214; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80027214.s")
#endif

M2C_UNK func_80027168();                            /* extern */

void func_800273C4(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    func_80027168();
}

M2C_UNK func_80027168();                            /* extern */

void func_800273E8(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 0) = 1;
    func_80027168();
}
