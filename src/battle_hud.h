/* Declarations for src/battle_hud.c. */
#ifndef BATTLE_HUD_H
#define BATTLE_HUD_H

#include "global.h"

// battle_hud.c
void ModelAnim_UpdateFrameChangeState(void);
s32 ModelPhase_IsIdle(void);
u8 ModelRenderer_GetActiveMode(void);
void ModelAnim_UpdateDisplayObjectAnimation(u32 arg0, u32 arg1);
void ModelAnim_FinalizeDisplayObjectAnimation(u32 arg0, u32 arg1);
void Gfx_SetCombineMode(Gfx*, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

// functions defined in assembly
void ModelAnim_StartDisplayObjectAnimation(DisplayObject* arg0);

#endif // BATTLE_HUD_H
