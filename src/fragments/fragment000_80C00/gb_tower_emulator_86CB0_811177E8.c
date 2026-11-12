/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "gb_tower_emulator_86CB0.h"

void func_811177E8(s32 num_samples, s16* out) {
    static u32 D_8122869C = 0;

    s32 i;
    s8* main_data;
    s8* alt_data;
    s32 a;
    s32 b;
    s32 main_end;
    s32 alt_end;

    main_data = NULL;
    alt_data = NULL;
    if (D_81138B84.id != 0) {
        D_81138B94 = D_81138B8C;
        D_81138B8C = D_81138B84;
        D_81138B8C.pos = 0;
        D_81138B84.id = 0;
        D_8122869C = 0x400;
    }
    if (D_81138B8C.id != 0) {
        main_data = GB_AUDIO_STREAM_DATA[D_81138B8C.id];
        main_end = GB_AUDIO_STREAM_SIZE[D_81138B8C.id];
    }
    i = D_81138B94.id;
    if (i != 0) {
        alt_data = GB_AUDIO_STREAM_DATA[i];
        alt_end = GB_AUDIO_STREAM_SIZE[i];
    }

    for (i = 0; i < num_samples; i++) {
        if (main_data != NULL) {
            if (main_end == D_81138B8C.pos) {
                D_81138B8C.id = 0;
                main_data = NULL;
                a = 0;
            } else {
                a = main_data[D_81138B8C.pos++];
            }
        } else {
            a = 0;
        }
        if (alt_data != NULL) {
            if (alt_end == D_81138B94.pos) {
                D_81138B94.id = 0;
                alt_data = NULL;
                b = 0;
            } else {
                b = alt_data[D_81138B94.pos++];
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
