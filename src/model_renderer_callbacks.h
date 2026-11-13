/* Declarations for src/model_renderer_callbacks.c. */
#ifndef MODEL_RENDERER_CALLBACKS_H
#define MODEL_RENDERER_CALLBACKS_H

#include "global.h"

// model_renderer_callbacks.c
void ModelRenderer_ClearSlotModels(s32);
void ModelRenderer_UpdateSlotVertices(void);
void ModelRenderer_CacheSlotMatrices(u8);
void ModelRenderer_ApplySlotScale(u8);
void ModelRenderer_RebuildSlotMatrix(u8);

#endif // MODEL_RENDERER_CALLBACKS_H
