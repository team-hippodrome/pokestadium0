/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "gb_tower_emulator_86CB0.h"

void func_811177E8(s32 numSamples, s16* out) {
    static u32 D_8122869C = 0;

    s32 i;
    s8* mainData;
    s8* altData;
    s32 a;
    s32 b;
    s32 mainEnd;
    s32 altEnd;

    mainData = NULL;
    altData = NULL;
    if (D_81138B84.id != 0) {
        D_81138B94 = D_81138B8C;
        D_81138B8C = D_81138B84;
        D_81138B8C.pos = 0;
        D_81138B84.id = 0;
        D_8122869C = 0x400;
    }
    if (D_81138B8C.id != 0) {
        mainData = GB_AUDIO_STREAM_DATA[D_81138B8C.id];
        mainEnd = GB_AUDIO_STREAM_SIZE[D_81138B8C.id];
    }
    i = D_81138B94.id;
    if (i != 0) {
        altData = GB_AUDIO_STREAM_DATA[i];
        altEnd = GB_AUDIO_STREAM_SIZE[i];
    }

    for (i = 0; i < numSamples; i++) {
        if (mainData != NULL) {
            if (mainEnd == D_81138B8C.pos) {
                D_81138B8C.id = 0;
                mainData = NULL;
                a = 0;
            } else {
                a = mainData[D_81138B8C.pos++];
            }
        } else {
            a = 0;
        }
        if (altData != NULL) {
            if (altEnd == D_81138B94.pos) {
                D_81138B94.id = 0;
                altData = NULL;
                b = 0;
            } else {
                b = altData[D_81138B94.pos++];
                b = (s32)(b * D_8122869C) / 1024;
            }
        } else {
            b = 0;
        }
        ((GbStereoSample*)out)[i].left = (a + b) << 6;
        ((GbStereoSample*)out)[i].right = (a - b) << 6;
    }
}


void func_81117AFC(UNUSED s32 arg0) {
}

void func_81218104_jp(UNUSED s32 arg0) {
}
