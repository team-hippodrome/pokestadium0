/* Stadium Zero resident code. */
/* Split from audio_commands.c: the code after the jump tables of Audio_PlayCommand. */

#include "audio_commands.h"
#include "pokemon.h"
#include "libnumus/player.h"
#include "m2c_macros.h"

extern u8 D_80077528;
extern u8 D_80077534;
extern s32 D_80077064[][2];
extern s32 D_800FD670[];
extern s32 D_800FD680;
extern u8 D_800FD605;
extern s32* D_800B417C;
extern s32* D_800B4160;
extern u8* D_800B41F0;
extern s32 D_800B41D0[];
extern s32 D_800B4198;
s32 Audio_QueueSetMonoOutputCommand(s32 handle);
s32 func_80037AC4(s32, s32);
void func_8004609C(u32, u8*, s32);
void func_80047FB0(u8*, s32, s32);
void Block_RelocateSelf(s32);
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);

/**
 * Plays the announcer's voice clip for a Pokémon and move: `species` (dex number, table D_80077064) and
 * `move` (below 166), on `side` (0 or 1). Stops that side's previous clip, and both sides' for events 1 and 5.
 * Ignored while the announcer is busy or within 20 frames of the last call.
 * Seen in play (2026-11-14, COM battle, breakpoint): called from BattleScene_EnterIdleRow with side 0, species 95 (Onix), event 10. The Pikachu reward calls it
 * with Pikachu and Surf, the opening demo with Blastoise and Hydro Pump.
 * @unverified: that these are announcer clips (not cries) is inferred, audio is not heard in the headless emulator.
 */
s32 Announcer_CallMove(u8 side, u32 move, u32 species, u32 event, u8 hi) {
    u32 addr;
    s32 size;
    s32 flags;
    u8* entry;

    if (D_80077528 != 0) {
        return 0;
    }
    if (D_80077534 != 0) {
        return 0;
    }
    if (move >= 166U) {
        return 0;
    }
    if (species == DITTO || species == GENGAR) {
        return 0;
    }
    D_80077534 = 20;
    if (species >= 152U) {
        return 0;
    }
    hi = (event & 0xFF00) >> 8;
    event &= 0xFF;
    if ((event == 10 || event == 11) && (hi == 0x10 || hi == 0x20)) {
        return 0;
    }
    if (side >= 2) {
        return 0;
    }
    if (D_80077064[species][0] == 0) {
        return 0;
    } else {
        entry = (u8*)D_80077064[species][0];
    }
    if (Audio_QueueSetMonoOutputCommand(D_800FD670[side])) {
        func_80037AC4(D_800FD670[side], 10);
        D_800FD670[side] = 0;
    }
    if (event == 1 || event == 5) {
        for (flags = 0; flags < 4; flags++) {
            func_80037AC4(D_800FD670[flags], 10);
            D_800FD670[flags] = 0;
        }
    }
    switch (event) {
    case 11:
        if (Audio_QueueSetMonoOutputCommand(D_800FD670[side ^ 1])) {
            func_80037AC4(D_800FD670[side ^ 1], 10);
            D_800FD670[side ^ 1] = 0;
        }
        flags = (entry[0] & 0xF0) >> 4;
        break;
    case 0:
    case 2:
    case 3:
        flags = (entry[move] & 0xF0) >> 4;
        break;
    case 4:
        flags = (entry[move] & 0xE) >> 1;
        break;
    case 1:
        flags = entry[move] & 1;
        break;
    default:
        return 0;
    }
    if (flags == 0) {
        return 0;
    }
    D_800FD605++;
    D_800FD605 %= 5;
    species--;
    if (species < (u32)(D_800B417C[0] - 1)) {
        addr = D_800B417C[species + 3];
        size = D_800B417C[species + 4] - addr;
    } else {
        addr = D_800B417C[species + 3];
        size = D_800B4160[8] - addr;
    }
    func_8004609C(addr, D_800B41F0, size);
    func_80047FB0(D_800B41F0, D_800B41D0[D_800FD605], 0x200);
    Block_RelocateSelf(D_800B41D0[D_800FD605]);
    return (D_800FD670[side] = func_8003834C(D_800B4198, D_800B41D0[D_800FD605], flags, 0x80, 0x80, 0, -1));
}

M2C_UNK func_8003834C(s32, s32, s32, M2C_UNK, s32, s32, s32); /* extern */
extern s32 D_800B418C;
extern s32 D_800B41A8;

/**
 * Plays sound `id` from the system sound bank (D_800B418C) at default volume and pan.
 * @unverified: no callers found.
 */
void Audio_PlaySystemBankSound(s32 id) {
    func_8003834C(D_800B418C, D_800B41A8, id, 0x80, 0x80, 0, -1);
}

extern s32 D_800FD698[];
/**
 * Returns the announcer's copy of `side`'s current HP, or -1 for a bad side.
 */
s32 Announcer_GetHp(u32 side) {
    if (side >= 2U) {
        return -1;
    }
    return D_800FD698[side];
}

extern s32 D_800FD6A8[];
/**
 * Returns the announcer's copy of `side`'s max HP, or -1 for a bad side.
 */
s32 Announcer_GetMaxHp(u32 side) {
    if (side >= 2U) {
        return -1;
    }
    return D_800FD6A8[side];
}

extern M2C_UNK D_800FD6B4;

/**
 * Returns how many Pokémon the announcer counts as left on `side`, or -1 for a bad side.
 */
s32 Announcer_GetRemainingCount(u32 side) {
    if (side >= 2) {
        return -1;
    }
    return ((u8*)&D_800FD6B4)[side];
}

extern u8 D_80077538;

/**
 * Turns the announcer's queued lines on or off. Set from the saved options at boot (N64 logo) and by
 * the cartridge-check options screen.
 */
void Announcer_SetEnabled(s32 enabled) {
    if (enabled != 0) {
        D_80077538 = 1;
        return;
    }
    D_80077538 = 0;
}

extern M2C_UNK D_800FD6B2;
extern M2C_UNK D_800FD6B4;

/**
 * Stores both sides' team sizes (doubled) as the announcer's team and remaining counts. Called by the
 * battle opening with each side's numberOfPokemonBrought.
 */
void Announcer_SetTeamSizes(s32 side0_count, s32 side1_count) {
    s8 temp_v0;
    s8 temp_v1;

    temp_v0 = side0_count * 2;
    temp_v1 = side1_count * 2;
    M2C_FIELD(&D_800FD6B2, s8 *, 0) = temp_v0;
    M2C_FIELD(&D_800FD6B4, s8 *, 0) = temp_v0;
    M2C_FIELD(&D_800FD6B2, s8 *, 1) = temp_v1;
    M2C_FIELD(&D_800FD6B4, s8 *, 1) = temp_v1;
}

extern s32 D_800FD6A0[];
extern u8 D_800FD6B0[];
extern u8 D_800FD6B6[];
extern u8 D_80077560;
/**
 * Updates the announcer's HP for `side` (previous HP is kept for the drop comments). At 0 HP it counts a
 * faint: the remaining count drops and a faint comment is armed for Announcer_CommentOnMove.
 * Seen in play (2026-11-14, COM battle, breakpoint): called after damage with side 1, hp 73, maxHp 73.
 */
void Announcer_SetHp(u32 side, s32 hp, s32 max_hp) {
    s32* cur;
    s32* prev;
    s32* next;

    if (side < 2) {
        prev = &D_800FD6A0[side];
        cur = &D_800FD698[side];
        next = &D_800FD6A8[side];
        *prev = *cur;
        *cur = hp;
        *next = max_hp;
        if (hp == 0) {
            if (*prev == *next) {
                D_80077560 = 1;
            } else {
                D_80077560 = 0;
            }
            if (((u8*)&D_800FD6B4)[side] != 0) {
                ((u8*)&D_800FD6B4)[side]--;
            }
            D_800FD6B6[side]++;
            D_800FD6B0[side] = 1;
        }
    }
}

void Announcer_QueueLine(s32, f32, s32);
extern u8 D_80077528;
extern u8 D_8007754C;
extern s32 D_800FD6A8[];
extern u8 D_800FD6B6[];
extern u8 D_80077540;
extern s32 D_800B4188;
extern s32 D_800B41A4;
s32 func_8003834C(s32, s32, s32, s32, s32, s32, s32);
s32 Audio_QueueSetMonoOutputCommand(s32 handle);
s32 func_80037AC4(s32, s32);
s32 func_8004D300(s32);
u32 func_80053A80(void);
void func_800386E4(s32, s32);
extern u8 D_80077548;
extern u8 D_80077550;
extern u8 D_80077564;
extern u8 D_80077568;
extern u8 D_8007756C;
extern u8 D_80077570;
extern u8 D_80077574;
extern u8 D_80077578;
extern u8 D_8007757C;
extern u8 D_80077594;
extern s32 D_80077598;
extern u8 D_8007759C;
extern s32 D_800775A0;
extern s32 D_800775A4;
extern s32 D_800FD670[];
extern s32 D_800FD698[];
extern u8 D_800FD6B8;
extern s32 D_800FD6BC;

/**
 * Starts (`enable` != 0) or stops the announcer and crowd for a battle. Starting plays the crowd loop and
 * may queue an opening line comparing both sides' HP (close match, both low, both healthy). Stopping
 * fades out the crowd and any voice clips, clears the comment flags and counts one more stop.
 * Called with 1 when battle music starts (Audio_StartMusicTrack) and 0 when it changes or fades.
 * Seen in play (2026-11-14, COM battle, breakpoint): called with 0 from BattleScene_InitTurnPresentation.
 * Also reached as AudioFrameUpdate (alias, see docs/annotation/alias-backlog.md).
 */
void Announcer_SetActive(u32 enable) {
    s32 d;
    s32 mask;
    s32 ratio[2];
    s32 i;

    if (enable != 0) {
        if ((D_80077528 == 0) && (D_8007754C == 0)) {
            mask = func_8004D300(mask); // mask is read uninitialized here, as in the original
            D_8007754C = 1;
            D_80077598 = 0;
            D_80077594 = 0;
            D_800775A4 = 0;
            D_800775A0 = 0;
            func_8004D300(mask);
            if (D_800775A4 == 0) {
                D_800775A4 = func_8003834C(D_800B4188, D_800B41A4, 24, 0x80, 0x80, 0, -1);
            }
            if (D_80077548 == 0) {
                return;
            }
            if (D_800FD6A8[0] == 0) {
                D_800FD698[0] = 100;
                D_800FD6A8[0] = 100;
            }
            if (D_800FD6A8[1] == 0) {
                D_800FD698[1] = 100;
                D_800FD6A8[1] = 100;
            }
            ratio[0] = (u32)(D_800FD698[0] * 100) / (u32)D_800FD6A8[0];
            ratio[1] = (u32)(D_800FD698[1] * 100) / (u32)D_800FD6A8[1];
            if (D_80077548 >= 21) {
                if ((D_800FD698[0] != 0) && (D_800FD698[1] != 0)) {
                    if ((u8)func_80053A80() & 1) {
                        d = (ratio[1] < ratio[0]) ? ratio[0] - ratio[1] : ratio[1] - ratio[0];
                        if (d >= 51) {
                            Announcer_QueueLine(48, 0.0f, 0x80);
                            return;
                        }
                    }
                    if (((u8)func_80053A80() & 4) && (ratio[0] < 21) && (ratio[1] < 21)) {
                        Announcer_QueueLine(45, 0.0f, 0x80);
                        return;
                    }
                    if (((u8)func_80053A80() & 8) && (ratio[0] >= 61) && (ratio[1] >= 61) && (ratio[0] < 100) && (ratio[1] < 100)) {
                        d = (ratio[1] < ratio[0]) ? ratio[0] - ratio[1] : ratio[1] - ratio[0];
                        if (d < 10) {
                            Announcer_QueueLine(87, 0.0f, 0x80);
                            return;
                        }
                        Announcer_QueueLine(44, 0.0f, 0x80);
                        return;
                    }
                    if ((u8)func_80053A80() & 2) {
                        d = (((u8*)&D_800FD6B4)[1] < ((u8*)&D_800FD6B4)[0]) ? ((u8*)&D_800FD6B4)[0] - ((u8*)&D_800FD6B4)[1] : ((u8*)&D_800FD6B4)[1] - ((u8*)&D_800FD6B4)[0];
                        if ((d >= 4) && (((u8*)&D_800FD6B2)[0] >= 3) && (((u8*)&D_800FD6B2)[1] >= 3)) {
                            Announcer_QueueLine(88, 0.0f, 0x80);
                            return;
                        }
                        if ((((u8*)&D_800FD6B4)[0] < 3) && (((u8*)&D_800FD6B4)[1] < 3) && (((u8*)&D_800FD6B2)[0] >= 3) && (((u8*)&D_800FD6B2)[1] >= 3)) {
                            Announcer_QueueLine(90, 0.0f, 0x80);
                            return;
                        }
                        if (D_80077578 != 1) {
                            Announcer_QueueLine(52, 0.0f, 0x80);
                            D_80077578 = 1;
                            return;
                        }
                        Announcer_QueueLine(93, 0.0f, 0x80);
                        D_80077578 = 2;
                        return;
                    }
                    if (((u8)func_80053A80() & 2) && (D_80077578 != 1)) {
                        Announcer_QueueLine(52, 0.0f, 0x80);
                        D_80077578 = 1;
                        return;
                    }
                    if (((u8)func_80053A80() & 1) && (D_80077578 != 2)) {
                        Announcer_QueueLine(93, 0.0f, 0x80);
                        D_80077578 = 2;
                        return;
                    }
                    Announcer_QueueLine(53, 0.0f, 0x80);
                    D_80077578 = 0;
                    return;
                }
                if ((((u8*)&D_800FD6B4)[0] < 3) && (((u8*)&D_800FD6B4)[1] < 3) && (D_80077540 == 8)) {
                    Announcer_QueueLine(108, 0.0f, 0x80);
                } else if (D_80077578 != 1) {
                    Announcer_QueueLine(52, 0.0f, 0x80);
                    D_80077578 = 1;
                } else {
                    Announcer_QueueLine(93, 0.0f, 0x80);
                    D_80077578 = 2;
                }
                mask = func_8004D300(1);
                D_80077598 = 800;
                D_8007759C = 1;
                func_8004D300(mask);
                return;
            }
            if (D_80077548 >= 4) {
                if ((D_800FD698[0] != 0) && (D_800FD698[1] != 0)) {
                    if ((u8)func_80053A80() & 1) {
                        d = (ratio[1] < ratio[0]) ? ratio[0] - ratio[1] : ratio[1] - ratio[0];
                        if (d >= 51) {
                            Announcer_QueueLine(48, 0.0f, 0x80);
                            return;
                        }
                    }
                    if (((u8)func_80053A80() & 4) && (ratio[0] < 21) && (ratio[1] < 21)) {
                        Announcer_QueueLine(45, 0.0f, 0x80);
                        return;
                    }
                    if (((u8)func_80053A80() & 8) && (ratio[0] >= 81) && (ratio[1] >= 81) && (ratio[0] < 100) && (ratio[1] < 100)) {
                        if ((D_800FD6B6[0] == 0) && (D_800FD6B6[1] == 0)) {
                            Announcer_QueueLine(94, 0.0f, 0x80);
                            return;
                        }
                        Announcer_QueueLine(44, 0.0f, 0x80);
                        return;
                    }
                    if ((u8)func_80053A80() & 2) {
                        d = (((u8*)&D_800FD6B4)[1] < ((u8*)&D_800FD6B4)[0]) ? ((u8*)&D_800FD6B4)[0] - ((u8*)&D_800FD6B4)[1] : ((u8*)&D_800FD6B4)[1] - ((u8*)&D_800FD6B4)[0];
                        if ((d >= 4) && (((u8*)&D_800FD6B2)[0] >= 3) && (((u8*)&D_800FD6B2)[1] >= 3)) {
                            Announcer_QueueLine(88, 0.0f, 0x80);
                            return;
                        }
                        if ((((u8*)&D_800FD6B4)[0] < 3) && (((u8*)&D_800FD6B4)[1] < 3) && (((u8*)&D_800FD6B2)[0] >= 3) && (((u8*)&D_800FD6B2)[1] >= 3)) {
                            Announcer_QueueLine(90, 0.0f, 0x80);
                            return;
                        }
                        if (D_80077578 != 1) {
                            Announcer_QueueLine(52, 0.0f, 0x80);
                            D_80077578 = 1;
                            return;
                        }
                        if ((u8)func_80053A80() & 2) {
                            Announcer_QueueLine(93, 0.0f, 0x80);
                            D_80077578 = 2;
                        }
                    } else {
                        if (((u8)func_80053A80() & 1) && (D_80077578 != 2)) {
                            Announcer_QueueLine(93, 0.0f, 0x80);
                            D_80077578 = 2;
                            return;
                        }
                        if (((u8)func_80053A80() & 2) && (D_80077578 != 1)) {
                            Announcer_QueueLine(52, 0.0f, 0x80);
                            D_80077578 = 1;
                            return;
                        }
                        if ((u8)func_80053A80() & 0x40) {
                            Announcer_QueueLine(53, 0.0f, 0x80);
                            D_80077578 = 0;
                        }
                    }
                } else {
                    if (D_80077578 != 1) {
                        Announcer_QueueLine(52, 0.0f, 0x80);
                        D_80077578 = 1;
                    } else {
                        Announcer_QueueLine(93, 0.0f, 0x80);
                        D_80077578 = 2;
                    }
                    mask = func_8004D300(1);
                    D_80077598 = 800;
                    D_8007759C = 1;
                    func_8004D300(mask);
                }
            } else if ((D_800FD698[0] != 0) && (D_800FD698[1] != 0)) {
                if ((u8)func_80053A80() & 1) {
                    d = (ratio[1] < ratio[0]) ? ratio[0] - ratio[1] : ratio[1] - ratio[0];
                    if (d >= 51) {
                        Announcer_QueueLine(48, 0.0f, 0x80);
                        return;
                    }
                }
                if (((u8)func_80053A80() & 4) && (ratio[0] < 21) && (ratio[1] < 21)) {
                    if ((u8)func_80053A80() & 1) {
                        Announcer_QueueLine(45, 0.0f, 0x80);
                        return;
                    }
                    Announcer_QueueLine(89, 0.0f, 0x80);
                    return;
                }
                if ((ratio[0] >= 91) && (ratio[1] >= 91) && (D_800FD6B6[0] == 0) && (D_800FD6B6[1] == 0)) {
                    Announcer_QueueLine(51, 0.0f, 0x80);
                }
            } else {
                Announcer_QueueLine(89, 0.0f, 0x80);
                mask = func_8004D300(1);
                D_80077598 = 800;
                D_8007759C = 1;
                func_8004D300(mask);
            }
        }
    } else {
        mask = func_8004D300(1);
        D_8007754C = 0;
        func_8004D300(mask);
        func_80037AC4(D_800775A4, 120);
        func_80037AC4(D_800775A0, 120);
        for (i = 0; i < 4; i++) {
            if (Audio_QueueSetMonoOutputCommand(D_800FD670[i]) != 0) {
                func_800386E4(D_800FD670[i], 0xF);
                D_800FD670[i] = 0;
            }
        }
        D_800775A4 = 0;
        D_800775A0 = 0;
        D_8007759C = 0;
        D_800FD6BC = 0;
        D_800FD6B8 = 0;
        D_80077564 = 0;
        D_80077568 = 0;
        D_8007756C = 0;
        D_80077570 = 0;
        D_80077574 = 0;
        D_8007757C = 0;
        D_80077550 = 0;
        D_80077548++;
    }
}
