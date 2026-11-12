/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/model_animation_events.c. */

#include "model_animation_events.h"
#include "util.h"

s32 ModelAnim_IsEventFrame(DisplayObject* display_object, s16 frame_number);
s32 ModelAnim_IsEventTrackNearEnd(DisplayObject* display_object);
s32 ModelAnim_IsEventTrackDone(DisplayObject* display_object);

/** Returns whether the event track is on the given frame. */
s32 ModelAnim_IsEventFrame(DisplayObject* display_object, s16 frame_number) {
    return (display_object->eventTrack.frame + 1) == frame_number;
}

/** Returns whether the event track is two frames from its end. */
s32 ModelAnim_IsEventTrackNearEnd(DisplayObject* display_object) {
    return (display_object->eventTrack.frame + 2) == display_object->eventTrack.data->endFrame;
}

/** Returns whether the event track is on its last frame. */
s32 ModelAnim_IsEventTrackDone(DisplayObject* display_object) {
    return (display_object->eventTrack.frame + 1) == display_object->eventTrack.data->endFrame;
}
