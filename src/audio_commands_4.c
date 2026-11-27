/* Stadium Zero resident code. */
/* Split from audio_commands.c so the jump table of Announcer_CommentOnSideMessage lands at 0x8007EA3C. */


#include "audio_commands.h"
#include "audio_cache.h"
#include "rom_device.h"
#include "libnumus/player.h"
extern u8 pad_D_800FC694[4];
extern GbNoiseSampleEntry* D_800B41E4;
extern u8* D_800B41E8;
extern GbMusicBank* D_800FD688;
extern s16* D_800B41EC;
extern u32* gAudioRegions;
extern s32 pad_D_800FC70C;
extern s32 pad_D_800FC710;
extern u8 pad_D_800FC718[0x80];
#define AUDIO_HEAP_SIZE 300000
extern s32 pad_D_80077C80;

#include "libnumus/player.h"

#include "m2c_macros.h"

void Audio_RelocateOffsets(u32* arg0, u32 arg1, s32 arg2);
void Audio_CreateFrameTaskWrapper(void* arg0);
void Audio_ClearWaveDataLoaded(void);
extern s32 D_800FD608;
extern u8 D_8007752C;
s32 func_80037AC4(s32, s32);
void Announcer_SetActive(s32);
s32 func_800376E8(s32);
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);
extern u8 D_80077524;
extern s32 D_800B4188;
extern s32 D_800B41A4;
extern u8* D_800FD690;
void func_80037C04(s32, u32);
extern s32 D_800B41A0;
extern s32 D_800FD610[];
extern u8 D_800FD620;
extern s32 D_800FD628[];
extern u8 D_800FD68C;
extern u8 D_80077528;
extern u8 D_80077520;
extern s32 D_800FD5F8[];
extern u8* D_800B41B0[];
extern u8* D_800B41F0;
extern File1Header* D_800B4160;
extern s32 D_800B4190;
extern s32 D_800B4188;
extern s32 D_800B41A4;
extern s32 D_800775A8;
s32 Audio_QueueSetMonoOutputCommand(s32 handle);
s32 func_80037AC4(s32, s32);
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);
void Block_RelocateSelf(u8*);
void func_80037D4C(s32, f32);
void func_80037E84(s32, s32);
void func_80037DF4(s32, s32);
void Audio_PlayMoveSound(s32, s32, s32);
M2C_UNK func_80037AC4(s32, M2C_UNK);                /* extern */
extern u8 D_80077524;
extern s32 D_800FD64C;
extern s32 D_800FD650;
extern s32 D_800FD654;
extern s32 D_800B3CE4;
extern s32 D_800FD66C;
extern s32 D_800FD658[];
extern s32 D_800FD738;
extern s32 D_800FD680;
M2C_UNK func_8003834C(s32, s32, s32, M2C_UNK, s32, s32, s32); /* extern */
extern s32 D_800B418C;
extern s32 D_800B41A8;
extern s32 D_800FD698[];
extern s32 D_800FD6A8[];
extern u8 D_800FD6B4[2];
extern u8 D_80077538;
extern u8 D_800FD6B2[2];
extern s32 D_800FD6A0[];
extern u8 D_800FD6B0[];
extern u8 D_800FD6B6[];
extern u8 D_80077560;

extern u8 D_80077548;
extern u8 D_80077550;
extern u8 D_80077554;
extern u8 D_80077564;
extern u8 D_8007756C;
extern u8 D_80077570;
extern u8 D_80077574;
extern u8 D_80077580;
u32 osGetCount(void);
void Announcer_QueueLine(s32, f32, s32);

/**
 * Commentary when `side` acts (low nibble; bit 4 set skips the HP checks): picks a line from the side's
 * HP percentage, the opponent's, and a faint armed by Announcer_SetHp.
 * Seen in play (2026-11-14, COM battle, breakpoint): queued line 65 from here during a turn.
 */
void Announcer_CommentOnMove(u32 arg0) {
    s32 other;
    u32 pct;
    u32 other_pct;

    if (arg0 < 2) {
        D_80077550++;
        D_80077554 = arg0;
        D_80077564 = 0;
        D_8007756C = 0;
        D_80077570 = 1;
        D_80077574 = 0;
        D_80077580 = 0;
        other = arg0 & 0xF0; // FAKE: reuses `other` for the high nibble (fixes the spill slot)
        arg0 &= 0xF;
        if (other == 0) {
            if (D_800FD6A8[0] == 0) {
                D_800FD698[0] = 100;
                D_800FD6A8[0] = 100;
            }
            if (D_800FD6A8[1] == 0) {
                D_800FD698[1] = 100;
                D_800FD6A8[1] = 100;
            }
            other = arg0 ^ 1;
            pct = (u32)(D_800FD698[arg0] * 100) / (u32)D_800FD6A8[arg0];
            other_pct = (u32)(D_800FD698[other] * 100) / (u32)D_800FD6A8[other];

            if (D_800FD6B0[arg0] != 0) {
                D_8007756C = 1;
                if ((D_800FD6B4[arg0] < 3) && (D_800FD6B2[arg0] >= 3)) {
                    if ((u32)D_800FD698[arg0] < 50) {
                        Announcer_QueueLine(84, 0.0f, 0x80);
                    } else {
                        Announcer_QueueLine(55, 0.0f, 0x80);
                    }
                    D_800FD6B0[arg0] = 0;
                    return;
                }
                if ((D_800FD6B4[arg0] < D_800FD6B4[other]) && (D_800FD6B2[arg0] >= 3)) {
                    Announcer_QueueLine(109, 0.0f, 0x80);
                    D_800FD6B0[arg0] = 0;
                    return;
                }
                D_800FD6B0[arg0] = 0;
            }
            if ((pct < 50) && (pct >= 21)) {
                if ((u8)osGetCount() & 1) {
                    if (D_80077550 == 1) {
                        Announcer_QueueLine(66, 0.0f, 0x80);
                        return;
                    }
                    Announcer_QueueLine(68, 0.0f, 0x80);
                    return;
                }
                Announcer_QueueLine(32, 0.0f, 0x80);
                return;
            }
            if ((pct < 21) && (pct >= 6)) {
                if ((u8)osGetCount() & 1) {
                    if (D_80077550 == 1) {
                        Announcer_QueueLine(66, 0.0f, 0x80);
                        return;
                    }
                    Announcer_QueueLine(68, 0.0f, 0x80);
                    return;
                }
                Announcer_QueueLine(33, 0.0f, 0x80);
                return;
            }
            if ((pct < 6) && (D_800FD698[arg0] != 0)) {
                if ((D_800FD6B4[arg0] < 3) && ((u8)osGetCount() & 0x11)) {
                    Announcer_QueueLine(84, 0.0f, 0x80);
                    return;
                }
                if ((u8)osGetCount() & 0x10) {
                    Announcer_QueueLine(66, 0.0f, 0x80);
                    return;
                }
                Announcer_QueueLine(56, 0.0f, 0x80);
                return;
            }
            if ((D_800FD6B4[other] < 3) && (D_800FD6B2[other] >= 3)) {
                if ((u32)D_800FD698[other] < 30) {
                    Announcer_QueueLine(70, 0.0f, 0x80);
                    return;
                }
                if ((u8)osGetCount() & 1) {
                    if (D_80077550 == 1) {
                        if ((u8)osGetCount() & 1) {
                            Announcer_QueueLine(66, 0.0f, 0x80);
                            return;
                        }
                        Announcer_QueueLine(67, 0.0f, 0x80);
                        return;
                    }
                    Announcer_QueueLine(68, 0.0f, 0x80);
                    return;
                }
                Announcer_QueueLine(54, 0.0f, 0x80);
                return;
            }
            if ((D_800FD698[arg0] != 0) && (other_pct < 21)) {
                if (D_800FD6B4[other] < 3) {
                    Announcer_QueueLine(64, 0.0f, 0x80);
                    return;
                }
                Announcer_QueueLine(57, 0.0f, 0x80);
                return;
            }
            if (D_80077550 == 1) {
                if (D_80077548 < 2) {
                    Announcer_QueueLine(65, 0.0f, 0x80);
                    return;
                }
                if (D_80077548 == 2) {
                    Announcer_QueueLine(67, 0.0f, 0x80);
                    return;
                }
                if ((u8)osGetCount() & 1) {
                    Announcer_QueueLine(66, 0.0f, 0x80);
                    return;
                }
                Announcer_QueueLine(67, 0.0f, 0x80);
                return;
            }
            Announcer_QueueLine(68, 0.0f, 0x80);
        }
    }
}

extern u8 D_8007755C;
extern u8 D_80077564;
extern u8 D_80077568;
extern u8 D_8007756C;
extern u8 D_80077574;
extern u8 D_8007757C;
extern u8 D_80077580;
extern u8 D_800FD6B8;
extern s32 D_800FD6BC;
void Announcer_QueueLine(s32, f32, s32);

/**
 * Queues the announcer line for battle message kind `kind` shown for a side (BattleMessage_ShowForSide).
 * Seen in play (2026-11-14, COM battle, breakpoint): called with 0 when the turn's message appeared.
 */
void Announcer_CommentOnSideMessage(s32 kind) {
    switch (kind) {
        case 3:
            if (D_80077560 != 0 && D_8007757C == 0) {
                Announcer_QueueLine(69, 0.0f, 0x80);
                D_80077560 = 0;
            } else {
                Announcer_QueueLine(29, 0.0f, 0x80);
            }
            func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
            break;
        case 5:
            if (D_8007756C != 0) {
                Announcer_QueueLine(86, 0.0f, 0x80);
                D_8007756C = 0;
            } else if (D_80077568 == 0) {
                Announcer_QueueLine(58, 0.0f, 0x80);
            }
            break;
        case 6:
            Announcer_QueueLine(38, 0.0f, 0x80);
            func_8003834C(D_800B4188, D_800B41A4, 26, 112, 0x80, 0, -1);
            break;
        case 7:
            if (D_8007756C != 0) {
                Announcer_QueueLine(86, 0.0f, 0x80);
                D_8007756C = 0;
            } else if (D_80077568 == 0) {
                Announcer_QueueLine(58, 0.0f, 0x80);
            }
            break;
        case 8:
        case 9:
        case 10:
            Announcer_QueueLine(58, 0.0f, 0x80);
            break;
        case 14:
            Announcer_QueueLine(73, 0.0f, 0x80);
            break;
        case 15:
            Announcer_QueueLine(104, 0.0f, 0x80);
            break;
        case 16:
            Announcer_QueueLine(58, 0.0f, 0x80);
            break;
        case 18:
            Announcer_QueueLine(77, 0.0f, 0x80);
            break;
        case 19:
            if ((u8)osGetCount() & 1) {
                Announcer_QueueLine(80, 0.0f, 0x80);
            } else {
                Announcer_QueueLine(103, 0.0f, 0x80);
            }
            break;
        case 25:
            Announcer_QueueLine(76, 0.0f, 0x80);
            break;
        case 26:
            Announcer_QueueLine(59, 0.0f, 0x80);
            D_80077580 = 1;
            break;
        case 27:
            Announcer_QueueLine(76, 0.0f, 0x80);
            break;
        case 29:
            Announcer_QueueLine(25, 0.0f, 0x80);
            D_800FD6BC = func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
            D_800FD6B8 = 1;
            D_8007755C = 1;
            break;
        case 30:
            Announcer_QueueLine(26, 0.0f, 0x80);
            func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
            D_8007755C = 1;
            break;
        case 31:
            Announcer_QueueLine(81, 0.0f, 0x80);
            D_80077574 = 1;
            break;
        case 32:
            Announcer_QueueLine(60, 0.0f, 0x80);
            break;
        case 33:
        case 34:
        case 35:
        case 36:
            func_80037AC4(D_800775A8, 80);
            D_800775A8 = func_8003834C(D_800B4188, D_800B41A4, 15, 0x80, 0x80, 0, -1);
            break;
        case 37:
        case 38:
        case 39:
        case 40:
            if (D_800FD6B4[0] >= 2 && D_800FD6B4[1] >= 2) {
                Announcer_QueueLine(31, 0.0f, 0x80);
            }
            break;
        case 41:
            Announcer_QueueLine(27, 0.0f, 0x80);
            if (D_800FD6B8 == 0) {
                func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
            }
            D_8007755C = 1;
            break;
        case 42:
            if (D_800FD6B4[0] >= 2 && D_800FD6B4[1] >= 2) {
                Announcer_QueueLine(28, 0.0f, 0x80);
                func_80037AC4(D_800FD6BC, 60);
                D_800FD6BC = 0;
                func_8003834C(D_800B4188, D_800B41A4, 28, 0x80, 0x80, 0, -1);
                D_8007755C = 1;
                D_80077564 = 1;
            }
            break;
        case 43:
            if (D_80077580 == 0) {
                Announcer_QueueLine(105, 0.0f, 0x80);
            }
            break;
        case 44:
            if (D_80077580 == 0) {
                Announcer_QueueLine(91, 0.0f, 0x80);
            }
            break;
        case 45:
            Announcer_QueueLine(30, 0.0f, 0x80);
            break;
        case 46:
            Announcer_QueueLine(78, 0.0f, 0x80);
            break;
    }
}

u32 osGetCount(void);
/**
 * Queues the announcer line for battle text `kind` (low 7 bits of the message id; battle message.c).
 */
void Announcer_CommentOnMessage(s32 kind) {
    switch (kind) {
    case 0:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 1:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 2:
        Announcer_QueueLine(36, 0.0f, 0x80);
        if ((u8)osGetCount() & 1) {
            Announcer_QueueLine(47, 0.0f, 0x80);
            D_80077568 = 1;
        }
        func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
        break;
    case 3:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 4:
        if (D_80077564 == 0) {
            Announcer_QueueLine(92, 0.0f, 0x80);
        }
        break;
    case 5:
        if (D_80077564 == 0) {
            Announcer_QueueLine(92, 0.0f, 0x80);
        }
        break;
    case 6:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 9:
        Announcer_QueueLine(39, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
        break;
    case 10:
        if (D_80077564 == 0) {
            Announcer_QueueLine(92, 0.0f, 0x80);
        }
        break;
    case 11:
        Announcer_QueueLine(37, 0.0f, 0x80);
        if ((u8)osGetCount() & 1) {
            Announcer_QueueLine(47, 0.0f, 0x80);
            D_80077568 = 1;
        }
        func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
        break;
    case 12:
        if (D_80077564 == 0) {
            Announcer_QueueLine(92, 0.0f, 0x80);
        }
        break;
    case 13:
        if (D_80077574 == 0) {
            Announcer_QueueLine(95, 0.0f, 0x80);
        } else {
            D_80077574 = 0;
        }
        break;
    case 14:
        Announcer_QueueLine(96, 0.0f, 0x80);
        break;
    case 15:
        Announcer_QueueLine(97, 0.0f, 0x80);
        break;
    case 16:
        Announcer_QueueLine(98, 0.0f, 0x80);
        break;
    case 17:
        Announcer_QueueLine(99, 0.0f, 0x80);
        break;
    case 18:
        Announcer_QueueLine(100, 0.0f, 0x80);
        break;
    case 19:
        if (D_80077574 == 0) {
            Announcer_QueueLine(95, 0.0f, 0x80);
        } else {
            D_80077574 = 0;
        }
        break;
    case 20:
        Announcer_QueueLine(96, 0.0f, 0x80);
        break;
    case 21:
        Announcer_QueueLine(97, 0.0f, 0x80);
        break;
    case 22:
        Announcer_QueueLine(98, 0.0f, 0x80);
        break;
    case 23:
        Announcer_QueueLine(99, 0.0f, 0x80);
        break;
    case 24:
        Announcer_QueueLine(100, 0.0f, 0x80);
        break;
    case 25:
        Announcer_QueueLine(76, 0.0f, 0x80);
        break;
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
        if (D_80077564 == 0) {
            Announcer_QueueLine(92, 0.0f, 0x80);
        }
        break;
    case 38:
        Announcer_QueueLine(76, 0.0f, 0x80);
        break;
    case 39:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 40:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 41:
        Announcer_QueueLine(76, 0.0f, 0x80);
        break;
    case 45:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 46:
        Announcer_QueueLine(76, 0.0f, 0x80);
        break;
    case 53:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 54:
        Announcer_QueueLine(101, 0.0f, 0x80);
        break;
    case 55:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 56:
        Announcer_QueueLine(72, 0.0f, 0x80);
        break;
    case 58:
        if (D_80077564 == 0) {
            Announcer_QueueLine(92, 0.0f, 0x80);
        }
        break;
    case 59:
        if (D_80077564 == 0) {
            Announcer_QueueLine(92, 0.0f, 0x80);
        }
        break;
    case 60:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 61:
        if (D_80077564 == 0) {
            Announcer_QueueLine(92, 0.0f, 0x80);
        }
        break;
    case 62:
        Announcer_QueueLine(76, 0.0f, 0x80);
        break;
    case 63:
        Announcer_QueueLine(76, 0.0f, 0x80);
        break;
    case 64:
        Announcer_QueueLine(107, 0.0f, 0x80);
        break;
    case 65:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 66:
        if (D_80077564 == 0) {
            Announcer_QueueLine(71, 0.0f, 0x80);
        }
        break;
    case 67:
        Announcer_QueueLine(59, 0.0f, 0x80);
        break;
    case 68:
        Announcer_QueueLine(76, 0.0f, 0x80);
        break;
    case 69:
        if (D_80077564 == 0) {
            Announcer_QueueLine(92, 0.0f, 0x80);
        }
        break;
    case 70:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 72:
        Announcer_QueueLine(107, 0.0f, 0x80);
        break;
    case 73:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 74:
        Announcer_QueueLine(43, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
        break;
    case 77:
        Announcer_QueueLine(42, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
        break;
    case 78:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 79:
        Announcer_QueueLine(40, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
        break;
    case 80:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 81:
        Announcer_QueueLine(101, 0.0f, 0x80);
        break;
    case 82:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 83:
        Announcer_QueueLine(102, 0.0f, 0x80);
        break;
    case 84:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 85:
    case 86:
        Announcer_QueueLine(60, 0.0f, 0x80);
        break;
    case 87:
        Announcer_QueueLine(41, 0.0f, 0x80);
        func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
        break;
    }
}


extern u8 D_80077548;
void Announcer_QueueLine(s32, f32, s32);
extern s32 D_800B4188;
extern s32 D_800B41A4;
extern u8 D_80077554;
extern u8 D_80077570;
extern u8 D_8007755C;
extern u8 D_80077564;
/**
 * Commentary as `side`'s HP bar moves: low-HP warning for the acting side, small/medium/big hit lines
 * (< 15, < 60, else) for the other side. Seen in play (2026-11-14, COM battle, breakpoint): called from Battle_StepPartyHpToDisplay with side 0.
 */
void Announcer_CommentOnHpChange(u32 side) {
    u32 hp;
    s32 lost;
    u32* prev;

    if (side < 2) {
        hp = D_800FD698[side];
        if (hp != 0) {
            prev = (u32*)&D_800FD6A0[side];
            if (side == D_80077554) {
                if ((hp < 30) && (D_80077570 != 0)) {
                    Announcer_QueueLine(106, 0.0f, 0x80);
                    D_80077570 = 0;
                }
            } else {
                lost = *prev - hp;
                *prev = hp;
                if (lost > 0) {
                    if ((hp < 10) && (hp != 0)) {
                        Announcer_QueueLine(34, 0.0f, 0x80);
                        func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
                        return;
                    }
                    if (D_8007755C == 0) {
                        if (lost < 15) {
                            if (((u8)osGetCount() & 0x11) || (D_80077548 < 2)) {
                                Announcer_QueueLine(63, 0.0f, 0x80);
                                D_80077564 = 1;
                            }
                        } else if (lost < 60) {
                            if (((u8)osGetCount() & 1) || (D_80077548 < 2)) {
                                Announcer_QueueLine(61, 0.0f, 0x80);
                                D_80077564 = 1;
                            }
                        } else {
                            Announcer_QueueLine(62, 0.0f, 0x80);
                        }
                    } else {
                        D_8007755C = 0;
                    }
                }
            }
        }
    }
}

void Announcer_QueueLine(s32, f32, s32);
extern s8 D_80077530;
extern u8 D_80077540;
extern s32 D_800B4188;
extern s32 D_800B41A4;

/**
 * Queues the closing line when a side wins (turn_actions sets the winner right before). In mode 8, if
 * side 0 has two or more Pokémon left it queues line 24 and sets D_80077530 (Audio_PlayCommand 80 then
 * skips the music); otherwise it queues line 30 and plays system sound 26.
 * @unverified: called right after the winner is set; the line ids are not mapped to clips.
 */
void Announcer_CommentOnBattleEnd(void) {
    if (D_80077540 == 8) {
        if (D_800FD6B4[0] >= 2) {
            Announcer_QueueLine(24, 0.0f, 0x80);
            D_80077530 = 1;
            return;
        }
        Announcer_QueueLine(30, 0.0f, 0x80);
        D_80077530 = 0;
        func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
        return;
    }
    Announcer_QueueLine(30, 0.0f, 0x80);
    D_80077530 = 0;
    func_8003834C(D_800B4188, D_800B41A4, 26, 0x80, 0x80, 0, -1);
}

extern s32 D_80077590;
extern u8 D_80077550;
extern u32 D_8007758C;
extern u32 D_80077588;
extern u32 D_80077558;
extern u8 D_8007754C;
extern u32 D_80077598;
extern u8 D_8007759C;
extern s32 D_800775A4;
extern s32 D_800775A0;
extern u8 D_80077578;
extern u8 D_80077584;
extern u8 D_8007753C;
/**
 * Resets the announcer for a new battle: HP to 100/100, counts to 6 (mode > 0, or team size 1..5) or 12,
 * clears the queue and flags.
 */
void Announcer_Reset(s32 mode, u32 team_size) {
    Announcer_SetActive(0);
    D_80077590 = 0;
    D_800FD738 = 0;
    D_80077540 = mode;
    D_80077548 = 0;
    D_80077550 = 0;
    D_8007758C = 0;
    D_80077588 = 0;
    D_80077558 = 0;
    D_800FD6B0[0] = 0;
    D_800FD6B0[1] = 0;
    D_800FD698[0] = D_800FD6A0[0] = 100;
    D_800FD698[1] = D_800FD6A0[1] = 100;
    D_800FD6A8[0] = 100;
    D_800FD6A8[1] = 100;
    if (D_80077540 > 0) {
        D_800FD6B4[0] = 6;
        D_800FD6B4[1] = 6;
    } else if ((team_size != 0) && (team_size < 6)) {
        D_800FD6B4[0] = D_800FD6B2[0] = 6;
        D_800FD6B4[1] = D_800FD6B2[1] = 6;
    } else {
        D_800FD6B4[0] = D_800FD6B2[0] = 12;
        D_800FD6B4[1] = D_800FD6B2[1] = 12;
    }
    D_800FD6B6[0] = 0;
    D_800FD6B6[1] = 0;
    D_8007754C = 0;
    D_80077598 = 0;
    D_8007759C = 0;
    D_800775A4 = 0;
    D_800775A0 = 0;
    D_800FD6B8 = 0;
    D_800FD6BC = 0;
    D_80077564 = 0;
    D_80077568 = 0;
    D_8007756C = 0;
    D_80077570 = 0;
    D_80077574 = 0;
    D_80077578 = 0;
    D_80077580 = 0;
    D_80077584 = 1;
    D_8007755C = 0;
    D_80077560 = 0;
    D_8007757C = 0;
    D_80077554 = 0;
    D_8007753C = 0;
    D_80077530 = 0;
}

/** One pending entry in the 10-slot ring buffer D_800FD6C0. */
typedef struct QueuedEntry80043CE8 {
    /* 0x0 */ s32 id;
    /* 0x4 */ f32 value;
    /* 0x8 */ u32 level;
} QueuedEntry80043CE8;

extern u8 D_80077528;
extern u8 D_8007753C;
extern u32 D_80077558;
extern u32 D_8007758C;
extern QueuedEntry80043CE8 D_800FD6C0[];
s32 func_8004D300(s32);

/**
 * Queues announcer line `line_id` with `delay` and volume `volume` + 112 (clamped to 255) in a ring of 10, at
 * most 2 pending. Does nothing while the announcer is off. Seen in play (2026-11-14, COM battle, breakpoint): called with line 65, 0.0, 128.
 */
void Announcer_QueueLine(s32 line_id, f32 delay, s32 volume) {
    s32 prev_mask;
    QueuedEntry80043CE8* entry;
    u32 level;
    u32 idx;
    u32 count;

    if ((D_80077528 == 0) && (D_80077538 != 0) && (D_8007753C == 0)) {
        prev_mask = func_8004D300(1);
        count = D_80077558;
        if (count < 2) {
            idx = D_8007758C;
            entry = &D_800FD6C0[idx];
            level = volume + 112;
            entry->level = level;
            entry->id = line_id;
            entry->value = delay;
            if (level >= 0x100) {
                entry->level = 0xFF;
            }
            D_8007758C = idx + 1;
            D_80077558 = count + 1;
            D_8007758C %= 10;
        }
        func_8004D300(prev_mask);
    }
}

extern u8 D_80077548;
extern u8 D_8007754C;
extern u32 D_80077588;
extern s32 D_80077590;
extern u32 D_80077598;
extern u8 D_8007759C;
extern s32 D_800775A0;
extern u8 D_800B3CC8;
s32 Audio_QueueSetMonoOutputCommand(s32 handle);
s32 func_800383DC(s32, s32, s32, s32, s32, s32, s32);

/**
 * Runs once per audio frame (from __amHandleFrame): when the previous announcer clip has ended, plays the
 * next line queued by Announcer_QueueLine from the announcer bank (D_800B418C). While the announcer is
 * active it also counts frames (D_80077598) and queues lines 46, 49 (with system sound 25) and 50 as the
 * count passes 1001, 1601 and 2201 (2601, 3201 and 3801 while D_80077548 is 0); line 50 rewinds the count.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the main menu, the Pokédex,
 * the party screen, the Lab list, Lab sort, registration, the Lab PC, Free Battle setup, the battle
 * opening, a switch in battle, running from battle and a Pound turn.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Audio_UpdateBattleAudioFrame(void) {
    s32 ret;

    if ((D_80077538 != 0) && (D_8007753C == 0) && (Audio_QueueSetMonoOutputCommand(D_80077590) == 0) && (D_80077588 != D_8007758C) &&
        (D_800B3CC8 == 0)) {
        ret = func_800383DC(D_800B418C, D_800B41A8, D_800FD6C0[D_80077588].id, D_800FD6C0[D_80077588].level, 0x80, 0, -1);
        if (ret != -1) {
            D_80077590 = ret;
            D_80077588++;
            D_80077588 %= 10;
            D_80077558--;
        }
    }

    if (D_8007754C != 0) {
        if ((D_80077598 >= 1001) && (D_8007759C == 0) && (D_80077548 > 0)) {
            Announcer_QueueLine(46, 0.0f, 0x80);
            D_8007759C = 1;
        } else if ((D_80077598 >= 2601) && (D_8007759C == 0) && (D_80077548 == 0)) {
            Announcer_QueueLine(46, 0.0f, 0x80);
            D_8007759C = 1;
        } else if ((D_80077598 >= 1601) && (D_8007759C == 1) && (D_80077548 > 0)) {
            Announcer_QueueLine(49, 0.0f, 0x80);
            if (D_800775A0 == 0) {
                D_800775A0 = func_800383DC(D_800B4188, D_800B41A4, 25, 0x80, 0x80, 0, -1);
            }
            D_8007759C = 2;
        } else if ((D_80077598 >= 3201) && (D_8007759C == 1) && (D_80077548 == 0)) {
            Announcer_QueueLine(49, 0.0f, 0x80);
            if (D_800775A0 == 0) {
                D_800775A0 = func_800383DC(D_800B4188, D_800B41A4, 25, 0x80, 0x80, 0, -1);
            }
            D_8007759C = 2;
        } else if ((D_80077598 >= 2201) && (D_80077548 > 0)) {
            Announcer_QueueLine(50, 0.0f, 0x80);
            D_80077598 = 1000;
            D_8007759C = 1;
        } else if ((D_80077598 >= 3801) && (D_80077548 == 0)) {
            Announcer_QueueLine(50, 0.0f, 0x80);
            D_80077598 = 2600;
            D_8007759C = 1;
        }
        D_80077598++;
    }
}

extern u8* D_800FD690;
extern File1Header* D_800B4164;
extern u8* D_800B41F0;
extern u8* D_800B419C;
s32 func_80037F68(u8*, u8*);
void func_80037C04(s32, u32);

/**
 * Loads the second sound bank and its wave table into `arg0` (13000 bytes of bank, then the wave data),
 * relocates them, marks the wave data as loaded (D_80075C30 bit 31), then loads the first sequence file
 * and starts it at volume 112. Returns the sound handle.
 * Seen in play (2026-11-13) ran just after Start at the title screen (console reset, then N64 logo,
 * opening, title and main menu).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Audio_LoadWaveTablesAndMusic(u8* arg0) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    u8* sp1C;

    D_800FD690 = arg0;
    sp1C = D_800FD690 + 12992;

    if (1) {}  // karodo

    Rom_DmaRead(D_800B4164->offset1, (u32)D_800B41F0, D_800B4164->wave_tables_offset - D_800B4164->offset1);
    Audio_CopyDataWithCacheSync((s32)D_800B41F0, D_800FD690, 12992);
    Rom_DmaRead(D_800B4164->wave_tables_offset, (u32)sp1C, D_800B4164->files[0] - D_800B4164->wave_tables_offset);
    Audio_RelocateSoundBankWrapper((s32)D_800FD690, (s32)sp1C);
    D_80075C30 |= 0x80000000;
    Rom_DmaRead(D_800B4164->files[0], (u32)D_800B41F0, D_800B4164->files[1] - D_800B4164->files[0]);
    Audio_CopyDataWithCacheSync((s32)D_800B41F0, D_800B419C, 36000);
    D_800FD608 = func_80037F68(D_800FD690, D_800B419C);
    func_80037C04(D_800FD608, 112);

    return D_800FD608;
}

/** Clears the flag that marks wave data as loaded. */
void Audio_ClearWaveDataLoaded(void) {
    D_80075C30 &= ~0x80000000;
}
