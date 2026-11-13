#ifndef _32D10_H_
#define _32D10_H_

#include "global.h"

void ModelAnim_UpdateFrameChangeState(void);
s32 ModelPhase_IsIdle(void);
u8 ModelRenderer_GetActiveMode(void);
void ModelAnim_StartDisplayObjectAnimation(DisplayObject* arg0);
void ModelAnim_UpdateDisplayObjectAnimation(u32 arg0, u32 arg1);
void ModelAnim_FinalizeDisplayObjectAnimation(u32 arg0, u32 arg1);
void Gfx_SetCombineMode(Gfx*, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

#endif // _32D10_H_
