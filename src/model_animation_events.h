/* Declarations for src/model_animation_events.c. */
#ifndef MODEL_ANIMATION_EVENTS_H
#define MODEL_ANIMATION_EVENTS_H

#include "global.h"

// model_animation_events.c
s32 ModelAnim_IsEventFrame(DisplayObject* display_object, s16 frame_number);
s32 ModelAnim_IsEventTrackNearEnd(DisplayObject* display_object);
s32 ModelAnim_IsEventTrackDone(DisplayObject* display_object);

#endif // MODEL_ANIMATION_EVENTS_H
