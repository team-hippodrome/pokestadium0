/* Declarations for src/model_animation_events.c. */
#ifndef MODEL_ANIMATION_EVENTS_H
#define MODEL_ANIMATION_EVENTS_H

#include "global.h"

typedef struct unk_D_800ABD00 {
    /* 0x00 */ u8 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ EventTrackData* unk_04;
    /* 0x08 */ void* unk_08;
    /* 0x0C */ void* unk_0C;
} unk_D_800ABD00; // size = 0x10

// model_animation_events.c
s32 ModelAnim_IsEventFrame(DisplayObject* display_object, s16 frame_number);
s32 ModelAnim_IsEventTrackNearEnd(DisplayObject* display_object);
s32 ModelAnim_IsEventTrackDone(DisplayObject* display_object);

#endif // MODEL_ANIMATION_EVENTS_H
