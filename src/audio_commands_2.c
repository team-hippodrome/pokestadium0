/* Stadium Zero resident code. */
/* Split from audio_commands.c so the jump tables of Audio_PlayCommand land at 0x8007E87C. */

#include "audio_commands.h"
#include "libnumus/player.h"

typedef struct SoundBank8 {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
    /* 0x2 */ u8 unk_2[6];
} SoundBank8; // size = 0x8

extern SoundBank8 D_80077068[];
extern u8 D_80077528;
extern u8 D_80077530;
extern u8 D_8007753C;
extern u8 D_80077540;
extern u8 D_80077544;
extern s32 D_800B3CE4;
extern s32 D_800B4188;
extern s32 D_800B418C;
extern s32 D_800B41A4;
extern s32 D_800B41A8;
extern s32 D_800FD608;
extern s32 D_800FD654;
extern s32 D_800FD66C;
extern s32 D_800FD680;
extern s32 D_800FD738;
s32 Audio_QueueSetMonoOutputCommand(s32 handle);
s32 func_80037AC4(s32, s32);
void func_80037C04(s32, u32);
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);
s32 func_80047260(s32);
void Announcer_Reset(s32, s32);

/**
 * Plays sound command `arg0` from the system sound bank (D_800B4188) and returns its handle, or 0 when
 * nothing plays. `arg1` is a species for commands 6-8, 15-17, 50 and 51 (its sound class from
 * D_80077068), a pan angle (-90 to 90) for command 1 and the announcer mode for command 60 (with `arg2`
 * the team size, see Announcer_Reset). Commands 30-35 play the special move sound 166 with kinds 0-5.
 */
s32 Audio_PlayCommand(u32 arg0, s32 arg1, s32 arg2) {
    s32 pad[3]; // FAKE
    s32 ret;
    s32 pan;

    if (D_80077528 != 0) {
        return 0;
    }

    switch (arg0) {
        case 0:
            if (Audio_QueueSetMonoOutputCommand(D_800FD654) != 0) {
                return 0;
            }
            ret = D_800FD654 = func_8003834C(D_800B4188, D_800B41A4, 1, 112, 0x80, 0, -1);
            break;

        case 1:
            if (arg1 < -90) {
                arg1 = -90;
            } else if (arg1 > 90) {
                arg1 = 90;
            }
            pan = (arg1 + 90) * 1.4111111f;
            if (pan < 0) {
                pan = 0;
            } else if (pan > 244) {
                pan = 244;
            }
            ret = func_8003834C(D_800B4188, D_800B41A4, 2, 0x80, pan, 0, -1);
            break;

        case 2:
            if (func_80047260(D_800FD66C) != 0) {
                func_80037AC4(D_800FD66C, 20);
                D_800FD66C = 0;
            }
            ret = func_8003834C(D_800B4188, D_800B41A4, 3, 0x80, 0x80, 0, -1);
            break;

        case 3:
            D_800FD66C = ret = func_8003834C(D_800B4188, D_800B41A4, 4, 0x80, 0x80, 0, -1);
            break;

        case 4:
            ret = D_800B3CE4 = func_8003834C(D_800B4188, D_800B41A4, 1, 0x80, 0x80, 0, -1);
            break;

        case 5:
            break;

        case 6:
        case 7:
        case 8:
            arg1 = 3;
        case 51:
            if ((arg1 > 0) && (arg1 < 152)) {
                arg1--;
            } else {
                arg1 = 0;
            }
            switch (D_80077068[arg1].unk_0) {
                case 0:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 7, 0x80, 0x80, 0, -1);
                    break;
                case 1:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 6, 0x80, 0x80, 0, -1);
                    break;
                case 2:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 5, 0x80, 0x80, 0, -1);
                    break;
            }
            break;

        case 9:
        case 10:
        case 11:
            return 0;

        case 12:
        case 13:
        case 14:
            return 0;

        case 15:
        case 16:
        case 17:
            arg1 = 2;
        case 50:
            if ((arg1 > 0) && (arg1 < 152)) {
                arg1--;
            } else {
                arg1 = 0;
            }
            switch (D_80077068[arg1].unk_1) {
                case 0:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 10, 0x80, 0x80, 0, -1);
                    break;
                case 1:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 9, 0x80, 0x80, 0, -1);
                    break;
                case 2:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 8, 0x80, 0x80, 0, -1);
                    break;
            }
            break;

        case 18:
            ret = func_8003834C(D_800B4188, D_800B41A4, 11, 0x80, 0x80, 0, -1);
            break;

        case 19:
            ret = func_8003834C(D_800B4188, D_800B41A4, 12, 0x80, 0x80, 0, -1);
            break;

        case 20:
            ret = func_8003834C(D_800B4188, D_800B41A4, 13, 0x80, 0x80, 0, -1);
            break;

        case 21:
        case 22:
        case 23:
        case 24:
            break;

        case 60:
            if (Audio_QueueSetMonoOutputCommand(D_800FD738) != 0) {
                func_80037AC4(D_800FD738, 100);
                D_800FD738 = 0;
            }
            if ((arg2 <= 0) || (arg2 >= 7)) {
                D_80077544 = 1;
            } else {
                D_80077544 = arg2;
            }
            if (arg1 == 10) {
                Announcer_Reset(1, 1);
                return 0;
            }
            if (arg1 >= 9) {
                return 0;
            }
            Announcer_Reset(arg1, arg2);
            if (arg1 == 0) {
                ret = func_8003834C(D_800B4188, D_800B41A4, 35, 160, 0x80, 0, -1);
            } else {
                ret = func_8003834C(D_800B4188, D_800B41A4, arg1 + 15, 160, 0x80, 0, -1);
            }
            break;

        case 61:
            D_8007753C = 1;
            switch (arg1) {
                case 0:
                    D_800FD738 = ret = func_8003834C(D_800B4188, D_800B41A4, 29, 0x80, 0x80, 0, -1);
                    break;
                case 1:
                    ret = func_8003834C(D_800B4188, D_800B41A4, 30, 0x80, 0x80, 0, -1);
                    break;
                case 2:
                    switch (arg2) {
                        case 1:
                            pan = 30;
                            break;
                        case 2:
                            pan = 100;
                            break;
                        case 3:
                            pan = 170;
                            break;
                        case 4:
                            pan = 85;
                            break;
                        case 5:
                            pan = 155;
                            break;
                        case 6:
                            pan = 225;
                            break;
                        default:
                            pan = 127;
                            break;
                    }
                    ret = func_8003834C(D_800B4188, D_800B41A4, 31, 0x80, pan, 0, -1);
                    break;
                case 3:
                    if (D_80077540 == 8) {
                        ret = func_8003834C(D_800B4188, D_800B41A4, 42, 0x80, 0x80, 0, -1);
                    } else {
                        Audio_StartMusicTrack(20);
                        ret = func_8003834C(D_800B4188, D_800B41A4, 32, 0x80, 0x80, 0, -1);
                    }
                    break;
                case 4:
                    if (D_80077540 == 0) {
                        Audio_StartMusicTrack(20);
                        ret = func_8003834C(D_800B4188, D_800B41A4, 43, 0x80, 0x80, 0, -1);
                    } else {
                        ret = func_8003834C(D_800B4188, D_800B41A4, 33, 0x80, 0x80, 0, -1);
                    }
                    break;
                default:
                    return 0;
            }
            break;

        case 80:
            ret = func_8003834C(D_800B418C, D_800B41A8, D_80077540, 0xFF, 96, 0, -1);
            func_8003834C(D_800B418C, D_800B41A8, D_80077540, 0xFF, 160, 0, -1);
            if (D_80077530 == 0) {
                D_800FD608 = Audio_StartMusicTrack(14);
            }
            break;

        case 81:
            ret = func_8003834C(D_800B4188, D_800B41A4, 36, 0x80, 0x80, 0, -1);
            break;

        case 82:
            ret = func_8003834C(D_800B4188, D_800B41A4, 39, 0xFF, 96, 0, -1);
            func_8003834C(D_800B4188, D_800B41A4, 39, 0xFF, 160, 0, -1);
            func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
            break;

        case 83:
        case 84:
        case 85:
        case 86:
            break;

        case 87:
            ret = func_8003834C(D_800B4188, D_800B41A4, 41, 0xFF, 0x80, 0, -1);
            break;

        case 70:
            switch (arg1) {
                case 1:
                    if (Audio_QueueSetMonoOutputCommand(D_800FD680) == 0) {
                        D_800FD680 = func_8003834C(D_800B4188, D_800B41A4, 34, 80, 0x80, 0, -1);
                    } else {
                        func_80037C04(D_800FD680, 80);
                    }
                    break;
                case 2:
                    if (Audio_QueueSetMonoOutputCommand(D_800FD680) == 0) {
                        D_800FD680 = func_8003834C(D_800B4188, D_800B41A4, 34, 80, 0x80, 0, -1);
                    } else {
                        func_80037C04(D_800FD680, 80);
                    }
                    break;
                case 3:
                    if (Audio_QueueSetMonoOutputCommand(D_800FD680) == 0) {
                        D_800FD680 = func_8003834C(D_800B4188, D_800B41A4, 34, 80, 0x80, 0, -1);
                    } else {
                        func_80037C04(D_800FD680, 80);
                    }
                    break;
                default:
                    func_80037AC4(D_800FD680, 90);
                    D_800FD680 = 0;
                    return 0;
            }
            break;

        case 30:
            ret = Audio_PlayMoveSound(166, 1, 0);
            break;
        case 31:
            ret = Audio_PlayMoveSound(166, 1, 1);
            break;
        case 32:
            ret = Audio_PlayMoveSound(166, 1, 2);
            break;
        case 33:
            ret = Audio_PlayMoveSound(166, 1, 3);
            break;
        case 34:
            ret = Audio_PlayMoveSound(166, 1, 4);
            break;
        case 35:
            ret = Audio_PlayMoveSound(166, 1, 5);
            break;

        default:
            return 0;
    }
    return ret;
}

extern s32 D_800FD654;
extern s32 D_800B3CE4;
extern s32 D_800FD66C;
extern s32 D_800FD658[];
extern s32 D_800FD738;
extern s32 D_800FD680;
/**
 * Fades out the stored sound handle of `category` (0 music, 3, 4, 5 = per-slot, 61, 70) over
 * `frames` (at least 1; some categories use fixed times) and clears it. Returns 0 for an unknown category.
 * @unverified: categories named from the handles they use.
 */
s32 Audio_StopSoundByCategory(s32 category, s32 frames) {
    s32 idx;

    switch (category) {
        case 0:
            if (frames == 0) {
                frames = 1;
            }
            func_80037AC4(D_800FD654, frames);
            D_800FD654 = 0;
            break;
        case 4:
            if (frames == 0) {
                frames = 1;
            }
            func_80037AC4(D_800B3CE4, frames);
            D_800B3CE4 = 0;
            break;
        case 3:
            func_80037AC4(D_800FD66C, 60);
            D_800FD66C = 0;
            break;
        case 5:
            idx = frames - 1;
            func_80037AC4(D_800FD658[idx ^ 0], 10); // FAKE: keeps idx unfolded in v0
            D_800FD658[idx] = 0;
            break;
        case 61:
            func_80037AC4(D_800FD738, 120);
            D_800FD738 = 0;
            break;
        case 70:
            if (frames == 0) {
                frames = 1;
            }
            func_80037AC4(D_800FD680, frames);
            D_800FD680 = 0;
            break;
        default:
            return 0;
    }
    return 1;
}
