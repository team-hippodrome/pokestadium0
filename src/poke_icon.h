/* Declarations for src/poke_icon.c, src/poke_icon_2.c. */
#ifndef POKE_ICON_H
#define POKE_ICON_H

#include "global.h"
#include "gfx_rect.h"

typedef struct PokeModelPreview {
    /* 0x00 */ u16 flags; // @unverified: 2 = rotate by input, 4 = spin when idle
    /* 0x02 */ u16 fillColor; // @unverified: background fill when there is no background image
    /* 0x04 */ s16 width; // @unverified: image width in pixels
    /* 0x06 */ s16 height; // @unverified: image height in pixels
    /* 0x08 */ s16 backgroundWidth; // @unverified: background image width
    /* 0x0A */ s16 backgroundHeight; // @unverified: background image height
    /* 0x0C */ s32 backgroundImage; // @unverified: RGBA16 background drawn before the model, 0 for a fill
    /* 0x10 */ s16 idleTimer; // @unverified: 0x78 frames after input before the model spins again
    /* 0x12 */ s16 spinSpeed; // @unverified: y rotation per frame, ramps by 0x10 to 0x100
    /* 0x14 */ s32 source; // @unverified: BattleMon* or species id
    /* 0x18 */ f32 scale; // @unverified: species scale / 100
    /* 0x1C */ ModelLoadContext* loadContext; // @unverified: model loader
    /* 0x20 */ GraphNode* rootNode; // @unverified: preview geo root
    /* 0x24 */ DisplayObject* displayObject; // @unverified: preview model
    /* 0x28 */ GfxImage* colorImage; // @unverified: color image the preview renders into
    /* 0x2C */ GfxImage* depthImage; // @unverified: depth image of colorImage
} PokeModelPreview; // size = 0x30

typedef union PokeIconSource {
    struct {
        /* 0x00 */ s16 unk_00;
        /* 0x02 */ s16 speciesId; // @unverified: species id when the slot was set from an id (low half of raw)
    };
    u8* ptr; // @unverified: BattleMon* when slot flag 2 is set
    u32 raw;
} PokeIconSource; // size = 0x4

typedef struct PokeIconSlot {
    /* 0x00 */ s16 flags; // @unverified: 1 = needs render, 2 = source is a BattleMon, 4 = colors to adjust
    /* 0x02 */ u16 fillColor; // @unverified: background fill (GfxImage_FillCurrent)
    /* 0x04 */ PokeIconSource source; // @unverified: species id or BattleMon*
    /* 0x08 */ f32 scale; // @unverified: species scale / 100
    /* 0x0C */ GfxImage* image; // @unverified: rendered icon image
    /* 0x10 */ arg1_func_80010CA8 colorVariant; // @unverified: nickname color variant for the model colors
} PokeIconSlot; // size = 0x14

typedef struct PokeIconRenderer {
    /* 0x00 */ u8 flags; // @unverified: bit 0 = a model load is pending
    /* 0x01 */ u8 slotCount; // @unverified: number of slots
    /* 0x02 */ s8 nextSlot; // @unverified: slot the next load starts from
    /* 0x03 */ s8 lastRenderedSlot; // @unverified: -1 before the first render
    /* 0x04 */ ModelLoadContext* loadContext; // @unverified: model loader the slots use
    /* 0x08 */ PokeIconSlot* slots; // @unverified: slotCount icon slots
    /* 0x0C */ GraphNode* rootNode; // @unverified: geo root drawn into each slot image
    /* 0x10 */ DisplayObject* displayObject; // @unverified: model drawn for the icon
    /* 0x14 */ GfxImage* depthImage; // @unverified: depth image shared by every slot
    /* 0x18 */ unk_D_8006FF00* unk_18;
} PokeIconRenderer; // size = 0x1C

#include "game_state.h"

// poke_icon.c
PokeIconRenderer* PokeIcon_CreateRenderList(ModelLoadContext*, s16, s16, s16);
void func_80018234(PokeIconRenderer*, s32, s32, u16);
void func_8001833C(PokeIconRenderer*, s32, BattleMon*, u16);
s32 PokeIcon_ProcessNextSlot(PokeIconRenderer*, s32);
s32 PokeIcon_ProcessAllSlots(PokeIconRenderer*, s32);
s32 PokeIcon_RenderNextSlotBlocking(PokeIconRenderer*, s32);
s32 PokeIcon_GetImage(s8 *arg0, s32 arg1);
s32 PokeIcon_AreSlotsIdle(PokeIconRenderer*);

// poke_icon_2.c
PokeModelPreview* PokeIcon_CreateModelPreview(ModelLoadContext*, s16, s16, s16, s16, s16, s16, u8*);
void PokeIcon_SetPreviewMon(PokeModelPreview* arg0, BattleMon* arg1, u16 arg2);
void PokeIcon_SetPreviewSpecies(PokeModelPreview*, s32, u16);
u8* PokeIcon_RenderPreview(PokeModelPreview*);

#endif // POKE_ICON_H
