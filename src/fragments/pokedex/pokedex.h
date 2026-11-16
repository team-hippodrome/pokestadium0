/* Declarations for the pokedex fragment (src/fragments/pokedex/). */
#ifndef FRAGMENT_POKEDEX_H
#define FRAGMENT_POKEDEX_H

#include "global.h"
#include "menu.h"
#include "table_view.h"

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/pokedex/pokedex.c
 * src/fragments/pokedex/pokedex_2.c
 */

typedef struct unk_D_80064C60 {
    /* 0x00 */ char* unk_00;
    /* 0x04 */ char unk04[0x18];
} unk_D_80064C60; // size = 0x1C

/* The ずかんもくじ (index) list window: 151 rows of number, name and caught icon, and the アイウエオじゅん /
 * ばんごうじゅん (kana / number order) bar (Pokedex_InitListWindow, Pokedex_DrawListWindow). */
typedef struct PokedexListWindow {
    /* 0x000 */ Window window; // the ずかんもくじ window, 272x366 at (54, 85)
    /* 0x02C */ ScrollList list; // rows drawn by Pokedex_DrawListRow; D-Down moved list.cursor 0 -> 1, D-Right paged it to 9
    /* 0x070 */ ByteMatrix entries; // rows = the 0x1C-byte entries of D_80064C5C: capacity and count 151, rowSize 28
    /* 0x080 */ u16 itemFlags[0x97]; // @unverified: itemFlags of list
    /* 0x1AE */ char pad1AE[0x2];
    /* 0x1B0 */ s32 sortByKana; // C-Right (button bit 1, not A) toggles it (Pokedex_UpdateListCursor): 1 showed アイウエオじゅん with 023, 024, 119, 133 first; 0 ばんごうじゅん
} PokedexListWindow; // size = 0x1B4

/* The データをみる / なきごえ / ぶんぷをみる / やめる (data, cry, area, quit) menu window (Pokedex_InitActionMenuWindow). */
typedef struct PokedexMenuWindow {
    /* 0x00 */ Window window; // 180x168 at (390, 262)
    /* 0x2C */ Menu menu; // rows drawn by Pokedex_DrawActionMenuRow: データをみる, なきごえ, ぶんぷをみる, やめる; D-Down moved menu.cursor to 1
    /* 0x50 */ u16 itemFlags[4]; // @unverified: itemFlags of menu; bit 0 = disabled (Pokedex_HandleActionMenuResult)
    /* 0x58 */ PointerList items; // func_80027804 over the 4 strings D_8A1057E8 (count 4)
} PokedexMenuWindow; // size = 0x64

/* The ずかんもくじ screen, sIndexScreen (Pokedex_InitIndexWindows). The code also reaches the windows through
 * their own symbols sCountsWindow, sActionMenuWindow and sEntryWindow. */
typedef struct PokedexIndexScreen {
    /* 0x000 */ PokedexListWindow listWindow; // the ずかんもくじ list
    /* 0x1B4 */ Window countsWindow; // みつけたかず / つかまえたかず / もっているかず (Pokedex_DrawCounts), 248x104 at (342, 114)
    /* 0x1E0 */ PokedexMenuWindow menuWindow; // the データをみる / なきごえ / ぶんぷをみる / やめる menu
    /* 0x244 */ Window entryWindow; // the データをみる page (Pokedex_InitEntryWindow), also reached as sEntryWindow: 552x348 at (44, 84) with ヒトカゲ's entry
} PokedexIndexScreen; // size = 0x270

#include "controller.h"

// pokedex.c
s32 Pokedex_RunIndexScreen(void);
s32 Pokedex_RunActionMenu(void);
s32 Pokedex_DrawIndexScreen(u8 unused);
void Pokedex_LoadIcon(u8* dest, s32 species);
s32 Pokedex_ShowEntry(void);
s32 Pokedex_PlayCry(void);
void Pokedex_EnterAreaMapScreen(void);
void Pokedex_ExitAreaMapScreen(void);
s32 Pokedex_ShowAreaMapScreen(void);
void Pokedex_RunScreenLoop(void);
s32 Pokedex_GetHighestSeenSpeciesIndex(void);
void Pokedex_InitFramebuffers(void);

// pokedex_2.c
s32 Pokedex_FindNextMapArea(s32 current_area);
s32 Pokedex_FindPrevMapArea(s32 current_area);
void Pokedex_BuildGbMapDisplayList(void);
void Pokedex_BuildAreaPinsDisplayList(void);
void Pokedex_BuildGbMapMarkersDisplayList(void);
Gfx* Pokedex_DrawRButtonIcon(Gfx* gfx, s16 x, s16 y);
Gfx* Pokedex_DrawLabelFrame(Gfx* gfx, s32 left, s32 top, s32 width, s32 height, s32 style, s32 filled);
void Pokedex_BuildLabelFramesDisplayList(void);
void Pokedex_ResetCameraEase(void);
void Pokedex_UpdateCameraEaseSpeed(void);
void Pokedex_EaseVec3Toward(Vec3f* current, Vec3f* target);
void Pokedex_UpdateAreaMapFrame(void);
s32 Pokedex_GetEncounterRateTier(s32 rate);
s32 Pokedex_DrawAreaMapScreen(u8 unused);
s32 Pokedex_HandleAreaMapInput(void);
void Pokedex_ExitAreaMapPool(void);

#endif // FRAGMENT_POKEDEX_H
