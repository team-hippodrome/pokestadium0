/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "lab_pokemon_list.h"
#include "m2c_macros.h"

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
typedef struct Label89100FC4 {
    Color82000BC4 color;
    const char* str;
} Label89100FC4;

extern u8 D_80073520[];
M2C_UNK Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
extern s32 D_8910A7F8[3];
void func_80027410(void*, void*, s32, s32, s32);
void func_89109990(void*, void*, void*, s32);
extern s32 D_800603C0;
void func_8000B2F4(s32);
void Window_SetRect(s8 *, s32, s32, s32, s32);
void func_80027804(s8*, s8*, s32, s32);
void func_89109B60(s8*);
void func_80027D68(s32, s32);
void ScrollList_Init(s8*, s8*, s8*, s32, void*, s32, s32);
void LabPCList_DrawMonRow();
void func_89105C54(s8*, s32, s32, s8*, Rgba891024A4);
extern s32 D_8910D990[];
extern Rgba891024A4 D_8910A7F4;
extern u8 D_8910A844[];
extern u8 D_8910A848[];
extern u8 D_8910A804[];
extern u8 D_8910A84C[];
s32 LabPCList_GetColumnCursorX();
extern Entry80066AD8 D_80066AD8[];
s32 Pokemon_GetTypeIndex(u8*, s32);
M2C_UNK func_8001A384(M2C_UNK, M2C_UNK);
M2C_UNK func_8001A944(s32, s32, M2C_UNK *, ...);
M2C_UNK func_8001AA9C(u8, u8, u8, u8);
M2C_UNK func_8001AB6C();
M2C_UNK func_8001ABBC();
extern Entry89100FC4 D_8006A9D4[];
extern M2C_UNK D_800734A8;
extern char D_8910DBAC[];
s32 BattleMon_GetMoveIndexChecked(s32, s32);
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
void ScrollList_SetItems(s32*, void*, void*);
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
void LabPCList_InitPopupMenu(s8*, void*, s8*, s32, s32);
void LabPCList_PlacePopup(s8*);
void func_8910A21C(s8*, s8*, s8*, s32);
extern s8* D_8910A890[];
extern u8 D_8910A898[];
extern u8 D_8910DC50[];
extern s8 D_8910E2D0[];
extern s8 D_8910E312[];
s32 func_8003F6AC();
s32 ScrollList_UpdateCursor(void*);
void ScrollList_SetCursor(void*, s32);
void LabPCList_FormatGatherPrompt(s8*);
void func_8000A460(s8 *, s8 *);
u32 func_800566BC(s8*);
void LabPCList_InitPopupMenu(s8 *, void *, s8 *, s32, s32);
void LabPCList_PlacePopup(s8 *);
void Window_SetRect(s8 *, s32, s32, s32, s32);
extern Rgba891024A4 D_8910A7F4;
extern s8 *D_8910A8A8[];
extern s8 D_8910A8B0[];
extern u8 D_8910A8C8[];
extern s8 D_8910E358[];
s32 LabPCList_UpdateHeaderCursor(void*);
M2C_UNK LabPCList_ApplyFiltersAndSort();
extern s32 D_8910E37C;

s32 LabPCList_UpdatePopupMenu(s8*);
void func_80027D68(s32, s32);
void func_89105C54(s8*, s32, s32, s8*, Rgba891024A4);
M2C_UNK LabPCList_ApplyFiltersAndSort();
extern s32 D_8910D9D0;
extern s32 D_8910D9D4;

/**
 * Handles the sort menu: sort by name or number, gather battle Pokemon, clear selections, or choose the boxes to list.
 * Seen in play (2026-11-12) in いちらん: handled that menu: ポケモンばんごうでならべる sorted the party as フシギダネ,
 * ヒトカゲ, ゼニガメ, and アイウエオじゅんにならべる as ゼニガメ, ヒトカゲ, フシギダネ.
 */
s32 LabPCList_UpdateSortMenu(s8* arg0) {
    s32 buttons;

    if (LabPCList_UpdatePopupMenu(arg0 + 0x9654) != 0) {
        return 0;
    }
    buttons = ((u16*)D_800603C0)[4];
    if (buttons & 0x4000) {
        func_8003F6AC(3);
        M2C_FIELD(arg0, s32*, 0x88) = 0;
    } else if (buttons & 0x8000) {
        if (!(M2C_FIELD(arg0, u16**, 0x9698)[M2C_FIELD(arg0, s32*, 0x969C)] & 1)) {
            func_8003F6AC(2);
            switch (M2C_FIELD(arg0, s32*, 0x969C)) {
                case 0:
                    M2C_FIELD(arg0, s32*, 0x78) = 0x10;
                    func_80027D68(M2C_FIELD(arg0, s32*, 0xB160), D_8910D9D0);
                    M2C_FIELD(arg0, s32*, 0x88) = 0;
                    break;
                case 1:
                    M2C_FIELD(arg0, s32*, 0x78) = 0x11;
                    func_80027D68(M2C_FIELD(arg0, s32*, 0xB160), D_8910D9D4);
                    M2C_FIELD(arg0, s32*, 0x88) = 0;
                    break;
                case 2:
                    LabPCList_ToggleFilterFlag(arg0, 0x20);
                    LabPCList_ApplyFiltersAndSort(arg0);
                    M2C_FIELD(arg0, s32*, 0x88) = 0;
                    break;
                case 3:
                    LabPCList_ResetFilterState((LabPCListScreen*)arg0);
                    LabPCList_ClearFilterFlags(arg0);
                    LabPCList_ApplyFiltersAndSort(arg0);
                    M2C_FIELD(arg0, s32*, 0x88) = 0;
                    break;
                case 4:
                    M2C_FIELD(arg0, s32*, 0x88) = 1;
                    func_89105C54(arg0 + 0x230, 0x78, 0x67, arg0 + 0x420, D_8910A7F4);
                    return 0;
            }
        } else {
            func_8003F6AC(8);
        }
    }
    return 0;
}
