/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "fragments/lab_pc_list/lab_pc_list.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "pokemon_stats.h"
#include "save_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "status_icons.h"
#include "gb_save.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#include "fragments/pokemon_lab_support/pokemon_lab_support.h"
extern s32 pad_D_8831A4DC[8];
#include "fragments/lab_pc/lab_pc.h"
#include "graphics_textures.h"
#include "input.h"
#include "gb_data.h"
#include "pokemon_stats.h"
#include "save_data.h"
#include "game_state.h"
#include "table_view.h"
#include "text_system.h"
#include "gb_save.h"
#include "audio_sfx.h"
#include "hal_libc.h"
#include "memmap.h"
#include "memory.h"
#include "stage_loader.h"
#include "fragments/particle_math/particle_math.h"
#include "m2c_macros.h"
void func_8002ED18(s8*, s32, s8*);
void func_8900020C(void);
s32 LabItem_ComputeRemainingCapacity(s32 arg0, unk_func_8820BE14_06C* arg1);
s32 LabItem_ComputeMaxTransferQuantity(s32 arg0, unk_func_8820BE14_06C* arg1);
s32 LabItem_FindOrAllocateGamePakBoxSlot(unk_func_8821421C_07C* arg0, s32 arg1, char* arg2);
void LabItem_LoadGamePakBoxSlots(unk_func_8821421C_07C* arg0);
void LabItem_ReadDeckEntries(s32 arg0, s32 arg1, s32 arg2, unk_func_8820BE14_06C* arg3);
void func_800275E4(s32, s32);
void func_80030744(s32*, s32);
void func_800275E4(s32, s32);
int func_800274E0();
void func_80030744(s32*, s32);
extern M2C_UNK D_8900A5B8;
void Window_SetRect(s8*, s32, s32, s32, s32);
void Window_InitLabeled(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);
extern Color_RGBA8 D_8900A5C0;
extern char D_89018460[];
extern char D_89018468[];
extern s32 D_800603C0;
M2C_UNK func_8001A944(s32, s32, ...);
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void func_8002AF04(s8*, s32);
extern u8 D_8007356C[];
extern M2C_UNK D_800734A8;
extern Gfx D_80060270[];
extern Color_RGBA8 D_8900A5C4;
extern Color_RGBA8 D_8900A5C8;
extern Color_RGBA8 D_8900A5CC;
s32 func_8002B390(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;
#include "fragments/fragment015_238BD0/lab_pc_list_1CEA00_types.h"
extern Rgba89000D50 D_8900A5BC;
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_8001AA60(s32, s32, s32);
void Font_SetColorForFlags(s32);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
void func_8002D024(s8*);
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern Color_RGBA8 D_80073520;
extern u8 D_04002130[];
extern u8 D_04002238[];
extern u8 D_04002340[];
extern u8 D_04002448[];
extern char D_89018470[];
extern s32 D_800603C0;
extern M2C_UNK D_89018474;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Rgba89000D50);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
extern Rgba89000D50 D_8900A5D4[];
extern M2C_UNK D_800734A8;
void Window_SetRect(s8*, s32, s32, s32, s32);
void func_8002D880(s8*, s32, s32, s32, s32, s32);
M2C_UNK func_80027804();
s32 func_8002DCE0(void*);
extern Gfx D_80060270[];
extern Rgba89000D50 D_8900A5E0;
extern Rgba89000D50 D_8900A5E8;
extern Rgba89000D50 D_8900A5EC[];
extern char D_8901848C[];
char* func_8001FDC8(u8, char*);
s32 func_80031C24(u8);
s32 func_80031CC8(u8);
void Font_SetColorForFlags(s32);
void func_8002EC24(s8*, s32, s8*, s32, void*, s32, s32);
void LabItem_DrawItemCountRow();
void func_8002F9D8(void *, s32, s32, s32, s32);
void func_8002F6C4(void *, s32, s32, s32, s32);
void func_8002BAB8(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void *, s32, s32);
extern Gfx D_80073450[];
extern u8 D_04011AB8[];
s32 func_8002FD8C(void*);
s32 func_80030230(void*);
extern ColorPair890017FC D_8900A608;
extern ColorPair890017FC D_8900A610;
extern u8* D_89017A80[];
extern u8 D_89017A98[];
extern s32 D_89019114;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void Gfx_DrawTextureRgba16(s32, s32, s32, s32, u8*, s32, s32);
void Font_SetColorForFlags(s32);
s32 func_8002BC44(s32);
M2C_UNK func_8001A944(s32, s32, ...);
extern M2C_UNK D_800734A8;
M2C_UNK func_8001A944(s32, s32, ...);
extern M2C_UNK D_800734A8;
extern s32 D_8900A650[];
extern char* D_8900A660[];
extern char* D_8900A66C[];
extern s8* D_8900A678[];
s32 func_80031BC0(u8, char *);
typedef struct LabItemGridZ {
    /* 0x00 */ u8* data;
    /* 0x04 */ s32 pad04[2];
    /* 0x0C */ s32 stride;
} LabItemGridZ;
typedef struct LabItemCursorZ {
    /* 0x00 */ LabItemGridZ* grid;
    /* 0x04 */ s32 pad04;
    /* 0x08 */ s32 selected;
} LabItemCursorZ;
#define CURSOR(p) ((LabItemCursorZ*)((p) + 0x1E4))
void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);
void func_80027654(s32* matrix, u8* out, s32 row);
void func_80027700(s32* matrix, u8* in, s32 row);
extern Color_RGBA8 D_8900A698;
extern u8 D_8900A69C[];
extern char D_89018660[];
extern char D_8901866C[];
void func_8002A3F8(void*, s32, s32);
void Font_SetColorForFlags(s32);
extern Col89002C10 D_8900A6AC;
extern Col89002C10 D_8900A6B0;
extern char D_89018678[];
void LabItem_DrawTrainerInfo();
void Window_SetRect(s8*, s32, s32, s32, s32);
void func_8002D880(s8*, s32, s32, s32, s32, s32);
void func_80027410(s8*, s8*, s32, s32, s32);
void Ui_DrawTexturedDivider(s32, s32, s32, void*);
void func_8002A8E0(void*);
void func_8002DAD8(void*, s32, s32, s32, s32);
extern u8 D_8007356C[];
extern u8 D_89018688[];
s32 func_8002DC04(void*);
void func_8002B018(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern u8 D_8900A580[];
extern u8 D_8900A584[];
extern u8 D_8900A5A0[];
extern u8 D_8900A5A4[];
extern u8 D_8900A5A8[];
extern u8 D_8900A5AC[];
extern Rgba89000D50 D_8900A6B4;
extern Rgba89000D50 D_8900A6B8;
extern u8 D_8900BFC0[];
extern u8 D_89010368[];
extern u8 D_890110F0[];
typedef Color_RGBA8 Rgba8900A6BC; // size = 0x4
typedef struct Color8900A6BC {
    /* 0x0 */ Rgba8900A6BC c[2];
} Color8900A6BC; // size = 0x8
extern Color8900A6BC D_8900A6BC;
extern Color8900A6BC D_8900A6C4;
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern u8 D_89017A98[];
extern char D_890186C0[];
extern char D_890186CC[];
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Rgba8900A6BC, Rgba8900A6BC);
void Font_SetColorForFlags(s32);
extern s32 D_8900A6CC[];
extern s8 *D_8900A6D8[];
void Ui_DrawTexturedFrameDecal(s32, s32, s32, s32, u8*);
extern u8 D_800735C4[];
void func_8002B054(s8*, s32);
void func_8002A8E0(void*);
s32 func_8002B2B0(void *);
s32 func_890013F8(void *, u32);

M2C_UNK func_800069CC();
void func_8900379C(void* arg) {
    s8* arg0 = arg;

    func_800069CC();
    func_8900054C();
    switch (M2C_FIELD(arg0, s32*, 0)) {
        case 1:
            func_89001CB0(arg0 + 4);
            break;
        case 2:
            func_89001CB0(arg0 + 4);
            func_8002CAD0(arg0 + 0x4E8);
            break;
        case 3:
            func_89001CB0(arg0 + 4);
            func_89000694(arg0 + 0x54C);
            break;
        case 4:
            func_89002D14(arg0 + 0x604, 2);
            break;
        case 5:
            func_89002D14(arg0 + 0x604, 0x10);
            func_890032E4(arg0 + 0x68C);
            break;
        case 6:
            func_89002D14(arg0 + 0x604, 0x10);
            func_890032E4(arg0 + 0x68C);
            func_89000694(arg0 + 0x54C);
            break;
    }
}
