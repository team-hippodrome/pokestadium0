/* Declarations for src/fragments/pokedex_menu/. */
#ifndef POKEDEX_MENU_H
#define POKEDEX_MENU_H

#include "global.h"
#include "m2c_macros.h"

// pokedex_menu.c
void PokedexMenu_DrawItem(s32 index, s32 x, s32 y, char* text);
s32 PokedexMenu_Draw(s32 fade_mode);
void PokedexMenu_UpdateCursor(void);
void PokedexMenu_LoadSelectedFragment(void);
s32 PokedexMenu_RunFrame(s32 fade_mode);
s32 PokedexMenu_Init(s32 unused0, M2C_UNK unused1);

#endif // POKEDEX_MENU_H
