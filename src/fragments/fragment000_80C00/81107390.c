/* Stadium Zero fragment000_80C00. */

#include "global.h"

#ifdef NON_MATCHING
/* TODO: decompile func_81107390; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81107390.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81107634; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81107634.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811076D0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811076D0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110776C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110776C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811077FC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811077FC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811078D8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811078D8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81107AEC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81107AEC.s")
#endif

typedef struct AudioVoice81107E70 {
    /* 0x00 */ char unk00[0xE];
    /* 0x0E */ u16 offset;
    /* 0x10 */ s16 count;
    /* 0x12 */ s16 wrapCount;
} AudioVoice81107E70; // size = 0x14

typedef struct AudioChannel81107E70 {
    /* 0x000 */ char unk000[0x3];
    /* 0x003 */ u8 bank;
    /* 0x004 */ char unk004[0x34];
    /* 0x038 */ AudioVoice81107E70 voices[2][5];
    /* 0x100 */ char unk100[0x58];
} AudioChannel81107E70; // size = 0x158

void* func_81107634(void* cmd, u16 dmem, u16 offset, s32 count, s32 channel);
extern AudioChannel81107E70 D_81184110[];

void* func_81107E70(void* cmd, s16 channel, s16 slot) {
    AudioVoice81107E70* voice = &D_81184110[channel].voices[D_81184110[channel].bank][slot];

    cmd = func_81107634(cmd, 0x3E0, voice->offset, voice->count, channel);
    if (voice->wrapCount != 0) {
        cmd = func_81107634(cmd, voice->count + 0x3E0, 0, voice->wrapCount, channel);
    }
    return cmd;
}

#ifdef NON_MATCHING
/* TODO: decompile func_81107F40; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81107F40.s")
#endif

void* func_811076D0(void* cmd, u16 dmem, u16 offset, s32 count, s32 channel);

void* func_8110807C(void* cmd, s16 channel, s16 slot) {
    AudioVoice81107E70* voice = &D_81184110[channel].voices[D_81184110[channel].bank][slot];

    cmd = func_811076D0(cmd, 0x3E0, voice->offset, voice->count, channel);
    if (voice->wrapCount != 0) {
        cmd = func_811076D0(cmd, voice->count + 0x3E0, 0, voice->wrapCount, channel);
    }
    return cmd;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8110814C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110814C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81108750; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81108750.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811092F4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811092F4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110938C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110938C.s")
#endif
