/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/pokemon_stats.c. */

#include "pokemon_stats.h"
#include "gb_data.h"
#include "save_data.h"
#include "text_system.h"
#include "gb_tower.h"
#include "hal_libc.h"
#include "util.h"
#include "m2c_macros.h"

// Zero's per-port Game Boy save state; Stadium 1's GbSavePort is 0x58 bytes.
typedef struct GbSavePortZero {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05[0x13];
    /* 0x18 */ u8 unk_18[0x20];
    /* 0x38 */ u16 unk_38;
    /* 0x3A */ u8 unk_3A[6];
    /* 0x40 */ u8* unk_40;
    /* 0x44 */ u8* unk_44;
} GbSavePortZero; // size = 0x48
extern s8 D_800AD210;
#define sGbSavePorts ((GbSavePortZero*)&D_800AD210)

// Zero's (Japanese) layout of the party block at offset 0x955 of the main save
// data.  The offsets and strides come from the retail code (GbSave_SaveMainPokemon
// style accesses); array lengths are not established, so they are left at 1.
typedef struct GbSavePartyZero {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001[1];
    /* 0x002 */ char unk002[6];
    /* 0x008 */ GbPokemonRecordExt unk_008[1]; // stride 0x2C
    /* 0x034 */ char unk034[0x110 - 0x34];
    /* 0x110 */ char unk_110[1][6];            // stride 6
    /* 0x116 */ char unk116[0x134 - 0x116];
    /* 0x134 */ char unk_134[1][6];            // stride 6
} GbSavePartyZero;

// Zero's layout of one Game Boy box as returned by GbSave_GetBoxEntry.
typedef struct GbSaveBoxZero {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001[1];
    /* 0x002 */ char unk002[0x1E];
    /* 0x020 */ GbPokemonRecord unk_020[1];    // stride 0x21
    /* 0x041 */ char unk041[0x3FE - 0x41];
    /* 0x3FE */ char unk_3FE[1][6];            // stride 6
    /* 0x404 */ char unk404[0x4B2 - 0x404];
    /* 0x4B2 */ char unk_4B2[1][6];            // stride 6
} GbSaveBoxZero;
extern u8 D_8006BB9C[];

// The parts of Zero's main save data touched by the Deck_* functions.  Three
// lists share one shape: a count byte followed by 2-byte BattleMonSpecies
// entries ended by 0xFF (offsets 0x44, 0x25C) or a byte list in the party
// block (0x955).  Offsets and strides come from the retail code; array
// lengths are not established.
typedef struct GbSaveMainZero {
    /* 0x000 */ char pad000[0x44];
    /* 0x044 */ u8 unk_044;
    /* 0x045 */ BattleMonSpecies unk_045[1];
    /* 0x047 */ char pad047[0x25C - 0x47];
    /* 0x25C */ u8 unk_25C;
    /* 0x25D */ BattleMonSpecies unk_25D[1];
    /* 0x25F */ char pad25F[0x955 - 0x25F];
    /* 0x955 */ GbSavePartyZero unk_955;
} GbSaveMainZero;
extern u8 D_8006B8C4[];
typedef struct unk_func_800228F0_sp24 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u16 unk_02;
    // Two 6-byte Game Boy names, read with Text_UntranscodeFixedName.
    /* 0x04 */ char unk_04[0xC];
} unk_func_800228F0_sp24;
extern u8 gDexToInternalIndex[];
extern u8 gInternalIndexToDex[];
extern u32 D_800AD330;
extern u8 D_800AD334;
extern u8 D_800AD335;
extern GbSaveMainData D_800AD338;

s32 GbSave_HasPlayerNameMarker(u8* arg0);
s32 GbSave_VerifyChecksum(u8* arg0, u8* arg1);
void GbSave_ComputeChecksum(u8* arg0, u8* arg1);
s32 GbSave_VerifyWriteback(u8* arg0, s32 arg1);
void GbSave_RequirePakPresent(s32 arg0);
s32 GbSave_GetBoxEntryCount(s32 arg0, s32 arg1);
void GbSave_SetBoxEntryCount(s32 arg0, s32 arg1, s32 arg2);
s32 Deck_GetCapacity(s32 arg0);
s32 Deck_GetEntrySize(s32 arg0);
s32 GbSave_GetPresentPortMask(void);
s32 GbSave_GetPortAvailability(s32 arg0);

GbSaveBoxEntry* GbSave_GetBoxEntry(s32 arg0, s32 arg1);

s32 GbSave_HasPlayerNameMarker(u8* arg0) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (*arg0++ == 'P') {
            return 1;
        }
    }

    return 0;
}

s32 GbSave_VerifyChecksum(u8* arg0, u8* arg1) {
    s32 sp1C = 0;
    s32 sp18 = 0;

    if (GbSave_HasPlayerNameMarker(arg0) != 0) {
        while (arg1 >= arg0) {
            sp18 += *arg0++;
        }
        sp1C = (sp18 & 0xFF) == 0xFF;
    }

    return sp1C;
}

void GbSave_ComputeChecksum(u8* arg0, u8* arg1) {
    s32 var_v0 = 0;

    while (arg0 < arg1) {
        var_v0 += *arg0++;
    }

    *arg1 = 0xFF - (var_v0 & 0xFF);
}

s32 GbSave_VerifyWriteback(u8* arg0, s32 arg1) {
    u8* var_v0 = D_800AD338.unk_000;

    while (arg1-- > 0) {
        if (*arg0++ != *var_v0++) {
            return 0;
        }
    }

    return 1;
}

s8 GbCart_IdentifyGame(s32 arg0) {
    // Only part of the rom header,
    // osGbpakReadId reads from 0x100 but this reads from 0x120
    typedef struct RomHeader {
        /* 0x00 */ char nintendo_chr[0x14];
        /* 0x14 */ char game_title[16];
        /* 0x24 */ u16 company_code;
        /* 0x26 */ u8 body_code;
        /* 0x27 */ u8 cart_type;
        /* 0x28 */ u8 rom_size;
        /* 0x29 */ u8 ram_size;
        /* 0x2A */ s8 country_code;
        /* 0x2B */ u8 fixed2;
        /* 0x2C */ u8 version;
        /* 0x2D */ u8 isum;
        /* 0x2E */ u16 sum;
        /* 0x30 */ char unk30[0x10];
    } RomHeader; // size = 0x40

    RomHeader sp28;
    s8 var_s0 = POKEMON_ROM_NONE;

    if (GbPak_ReadRom(arg0, &sp28, 0x120, sizeof(RomHeader)) == 0) {
        sp28.game_title[7] = '\x0';
        sp28.game_title[16] = '\x0';

        if (HAL_Strcmp(&sp28.game_title[0], "POKEMON") == 0) {
            if (HAL_Strcmp(&sp28.game_title[8], "RED") == 0) {
                var_s0 = POKEMON_ROM_RED;
            } else if (HAL_Strcmp(&sp28.game_title[8], "GREEN") == 0) {
                var_s0 = POKEMON_ROM_GREEN;
            } else if (HAL_Strcmp(&sp28.game_title[8], "BLUE") == 0) {
                var_s0 = POKEMON_ROM_BLUE;
            } else if (HAL_Strcmp(&sp28.game_title[8], "YELLOW") == 0) {
                var_s0 = POKEMON_ROM_YELLOW;
            }
        }
    }

    return var_s0;
}

s32 GbSave_CheckMainDataUnchanged(s32 arg0) {
    UNUSED s32 pad;
    s32 sp18 = 0;

    if ((GbPak_MbcRead(arg0, &D_800AD338, 0x2580, 0x1020) == 0) &&
        (GbSave_VerifyChecksum(&D_800AD338.unk_018, (u8*)&D_800AD338 + 0x1014) != 0)) {
        sp18 = ((u8*)&D_800AD338)[0x1014] == sGbSavePorts[arg0].unk_04;
    }
    return sp18;
}

s32 GbSave_ReadMainData(s32 arg0) {
    s32 i;
    s32 sp30;
    u8* temp_s4 = sGbSavePorts[arg0].unk_40;

    sp30 = NULL;

    if (GbPak_MbcRead(arg0, temp_s4, 0x2580, 0x1020) == 0) {
        for (i = 0; i < 3; i++) {
            sp30 = GbSave_VerifyChecksum(temp_s4 + 0x18, temp_s4 + 0x1014);
            if (sp30 != 0) {
                if (sGbSavePorts[arg0].unk_00 & 0x20) {
                    sGbSavePorts[arg0].unk_04 = temp_s4[0x1014];
                    sGbSavePorts[arg0].unk_00 = sGbSavePorts[arg0].unk_00 & ~0x20;
                } else {
                    sp30 = temp_s4[0x1014] == sGbSavePorts[arg0].unk_04;
                }
                return sp30;
            }
        }
    }

    return sp30;
}

s32 func_8000C1B4(s32, M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
s32 func_8000C238(s32, s8 *, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8002107C(s32, s32);                    /* extern */
s32 func_800210AC(s8 *, M2C_UNK);                 /* extern */
extern s8 D_800AD210;
s32 func_80021334(s32 arg0) {
    s32 var_s0;
    s8 *temp_s1;
    s8 *temp_s3;

    temp_s3 = (arg0 * 0x48) + &D_800AD210;
    temp_s1 = M2C_FIELD(temp_s3, s8 **, 0x40);
    func_8002107C(temp_s1 + 0x18, temp_s1 + 0x1014);
    var_s0 = 0;
    M2C_FIELD(temp_s3, u8 *, 4) = (u8) M2C_FIELD(temp_s1, u8 *, 0x1014);
loop_1:
    if ((func_8000C238(arg0, temp_s1, 0x2580, 0x1020) == 0) && (func_8000C1B4(arg0, &D_800AD338, 0x2580, 0x1020) == 0) && (func_800210AC(temp_s1, 0x1020) != 0)) {
        return 1;
    }
    var_s0 += 1;
    if (var_s0 == 4) {
        return 0;
    }
    goto loop_1;
}

/*
 * func_80021410
 *
 * Recomputes the checksum of the main save data of Game Boy port arg0 and
 * writes it back to the cartridge.  The checksum over bytes 0x18.. is stored
 * at offset 0x1014 and then inverted (^ 0xFF); the 0x20-byte block at offset
 * 0x1000 is written to cartridge address 0x3580, read back into D_800AD338
 * and verified, retrying up to four times.  Returns 1 on success, 0 if all
 * four attempts fail.
 *
 * Same structure as GbSave_InvalidateMainDataChecksum in the Stadium 1
 * decomp (its VERSION_JP branch uses the same 0x1000/0x1014/0x3580 values).
 */
s32 func_80021410(s32 arg0) {
    u8* temp_s3 = sGbSavePorts[arg0].unk_40;
    s32 i;

    GbSave_ComputeChecksum(temp_s3 + 0x18, temp_s3 + 0x1014);
    temp_s3[0x1014] ^= 0xFF;

    for (i = 0; i < 4; i++) {
        if ((GbPak_MbcWrite(arg0, temp_s3 + 0x1000, 0x3580, 0x20) == 0) &&
            (GbPak_MbcRead(arg0, &D_800AD338, 0x3580, 0x20) == 0) &&
            (GbSave_VerifyWriteback(temp_s3 + 0x1000, 0x20) != 0)) {
            return 1;
        }
    }
    return 0;
}

extern GbSavePort D_800AC910[4];
s32 GbSave_ReadBoxBank(s32 arg0, s32 arg1) {
    UNUSED s32 pad[2];
    u8* sp1C = sGbSavePorts[arg0].unk_44 + arg1 * 0x15A0;

    return GbPak_MbcRead(arg0, sp1C, (arg1 == 0) ? 0x4000 : 0x6000, 0x15A0) == 0;
}

/*
 * func_80021570
 *
 * Writes box bank arg1 (0 or 1) of Game Boy port arg0 from the in-memory
 * box data to the cartridge and verifies it by reading it back into
 * D_800AD338, retrying up to four times.  Bank 0 lives at cartridge address
 * 0x4000 and bank 1 at 0x6000; each bank is 0x15A0 bytes in Zero's (Japanese)
 * layout.  Returns 1 on success, 0 if all four attempts fail.
 *
 * Same structure as GbSave_WriteBoxBank in the Stadium 1 decomp (its
 * VERSION_JP branch also uses 0x15A0).
 */
s32 func_80021570(s32 arg0, s32 arg1) {
    s32 var_v0;
    u8* temp_s2 = sGbSavePorts[arg0].unk_44 + arg1 * 0x15A0;
    s32 i;

    if (arg1 == 0) {
        var_v0 = 0x4000;
    } else {
        var_v0 = 0x6000;
    }

    var_v0 &= 0xFFFF;

    for (i = 0; i < 4; i++) {
        if ((GbPak_MbcWrite(arg0, temp_s2, var_v0, 0x15A0) == 0) &&
            (GbPak_MbcRead(arg0, &D_800AD338, var_v0, 0x15A0) == 0) && (GbSave_VerifyWriteback(temp_s2, 0x15A0) != 0)) {
            return 1;
        }
    }
    return 0;
}

extern s8 D_800AD210;
void func_80021678(s32 arg0, u32 arg1) {
    s8 *temp_v0;
    s8 *temp_v0_2;

    if ((arg1 >= 0x44415430U) && (arg1 < 0x44415434U)) {
        temp_v0 = ((arg1 - 0x44415430) * 0x48) + &D_800AD210;
        M2C_FIELD(temp_v0, s32 *, 0x40) = 0;
        M2C_FIELD(temp_v0, u16 *, 0) = (u16) (M2C_FIELD(temp_v0, u16 *, 0) & 0xFFF6);
        return;
    }
    if ((arg1 >= 0x424F5830U) && (arg1 < 0x424F5834U)) {
        temp_v0_2 = ((arg1 - 0x424F5830) * 0x48) + &D_800AD210;
        M2C_FIELD(temp_v0_2, s32 *, 0x44) = 0;
        M2C_FIELD(temp_v0_2, u16 *, 0) = (u16) (M2C_FIELD(temp_v0_2, u16 *, 0) & 0xFFED);
    }
}

void GbSave_CheckLocationFlag(s32 arg0) {
    extern u8 D_8006BB90[12];

    s32 i;
    s32 temp_t1 = sGbSavePorts[arg0].unk_40[0x80];

    sGbSavePorts[arg0].unk_00 &= ~0x4000;

    for (i = 0; i < 12; i++) {
        if (D_8006BB90[i] == temp_t1) {
            sGbSavePorts[arg0].unk_00 |= 0x4000;
            break;
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002178C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002178C.s")
#endif

s32 GbSave_EnsureMainDataLoaded(s32 arg0) {
    s32 sp1C = 0;

    if (((1 << arg0) & D_800AD330) && (sGbSavePorts[arg0].unk_03 == 0)) {
        sp1C = GbSave_OpenMainData(arg0);
        if (sp1C == 0) {
            Game_ShutdownAndLoadFragment(arg0, 2);
        }
    }

    return sp1C;
}

s32 func_80021910(s32 arg0) {
    u8 sp37;
    s32 i;
    s32 sp2C;

    sp2C = 0;

    if (!(sGbSavePorts[arg0].unk_00 & 1)) {
        return 0;
    }

    if (sGbSavePorts[arg0].unk_00 & 2) {
        return 1;
    }

    sGbSavePorts[arg0].unk_44 = main_pool_alloc_with_func(0x2B40, 0, arg0 + 'BOX0', GbSave_ReleasePortBuffers);

    if (sGbSavePorts[arg0].unk_44 != NULL) {
        sGbSavePorts[arg0].unk_00 |= 2;
        if (GbSave_GetBoxCount(arg0) > 0) {
            if (GbTower_ProbePak(arg0, &sp37, sGbSavePorts[arg0].unk_18) == 0) {
                Game_ShutdownAndLoadFragment(arg0, 2);
            }

            if (GbSave_ReadBoxBank(arg0, 0) != 0) {
                sp2C = GbSave_ReadBoxBank(arg0, 1);
            }

            if (GbTower_CheckPakRemoved(arg0, sp37) == 0) {
                Game_ShutdownAndLoadFragment(arg0, 2);
            }

            if (sp2C == 0) {
                main_pool_try_free(sGbSavePorts[arg0].unk_44);
            }
        } else {
            HAL_Memset(sGbSavePorts[arg0].unk_44, 0xFF, 0x2B40);

            for (i = 0; i < 4; i++) {
                sGbSavePorts[arg0].unk_44[i * 0x566] = 0;
                sGbSavePorts[arg0].unk_44[0x15A0 + i * 0x566] = 0;
            }

            sp2C = 1;
        }
    }
    return sp2C;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80021A8C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80021A8C.s")
#endif

extern GbSavePort D_800AC910[4];
/*
 * func_80021B30
 *
 * Per-port state machine that waits for a Game Boy cartridge to be pulled
 * out and put back, then checks it is the same one.  D_8006BB9C[arg0] is
 * the state:
 *   0  start the removal check (GbTower_CheckPakRemoved), fall into 1
 *   1  wait until the cartridge is off (GbPak_IsCartOff)
 *   2  wait until it is back on (GbPak_IsCartOn); returns 1 meanwhile
 *   3  re-initialise the pak (GbTower_ReinitPak); if that worked, return 3,
 *      or 2 if the cartridge also identifies as the same game as before
 *      (GbCart_IdentifyGame == port byte 2) and
 *      GbTower_VerifyPakStillInserted accepts the port's data at offset
 *      0x18.  The state returns to 0.
 * Returns 0 when there is nothing to report yet.
 *
 * Same structure as GbSave_PollCartRemoval in the Stadium 1 decomp.
 */
s32 func_80021B30(s32 arg0) {
    s32 sp24 = 0;

    switch (D_8006BB9C[arg0]) {
        case 0:
            GbTower_CheckPakRemoved(arg0, 0);
            D_8006BB9C[arg0] += 1;
            // fallthrough

        case 1:
            if (GbPak_IsCartOff(arg0) != 0) {
                D_8006BB9C[arg0] += 1;
            }
            break;

        case 2:
            if (GbPak_IsCartOn(arg0) != 0) {
                D_8006BB9C[arg0] += 1;
            }
            sp24 = 1;
            break;

        case 3:
            if (GbTower_ReinitPak(arg0) != 0) {
                sp24 = 3;
                if (GbCart_IdentifyGame(arg0) == sGbSavePorts[arg0].unk_02) {
                    if (GbTower_VerifyPakStillInserted(arg0, sGbSavePorts[arg0].unk_18) != 0) {
                        sp24 = 2;
                    }
                }
            }
            D_8006BB9C[arg0] = 0;
            break;
    }
    return sp24;
}

/*
 * func_80021C6C
 *
 * If bit arg0 of D_800AD330 is set: sets bit 0x20 in the first halfword of
 * Game Boy port arg0's record, then calls GbSave_OpenMainData(arg0). If that
 * returns non-zero, calls func_80022BC8(arg0) and clears the record's
 * unk_03 byte; if it returns 0, sets unk_03 to 3.
 *
 * What bit 0x20 and the values 0 and 3 of unk_03 mean is not established.
 * The port index expression is repeated rather than cached in a local:
 * the compiler then spills the record pointer to sp+0x1C as in the ROM,
 * whereas a `port` local put the spill at sp+0x18.
 */
s32 func_80022BC8(s32 arg0);
void func_80021C6C(s32 arg0) {
    if ((1 << arg0) & D_800AD330) {
        sGbSavePorts[arg0].unk_00 |= 0x20;
        if (GbSave_OpenMainData(arg0) != 0) {
            func_80022BC8(arg0);
            sGbSavePorts[arg0].unk_03 = 0;
        } else {
            sGbSavePorts[arg0].unk_03 = 3;
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_80021CF4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80021CF4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80021E64; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80021E64.s")
#endif

s32 GbSave_WriteBoxBanks(s32 arg0) {
    u8 sp2F;
    s32 sp28 = 0;

    if (sGbSavePorts[arg0].unk_00 & 2) {
        if (GbTower_ProbePak(arg0, &sp2F, sGbSavePorts[arg0].unk_18) == 0) {
            Game_ShutdownAndLoadFragment(arg0, 2);
        }

        sp28 = GbSave_WriteBoxBank(arg0, 0);

        if (sp28 != 0) {
            sp28 = GbSave_WriteBoxBank(arg0, 1);
        }
        sp28 &= GbTower_CheckPakRemoved(arg0, sp2F);
    }
    return sp28;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80021FF4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80021FF4.s")
#endif

s32 GbSave_RebuildAndWriteSave(s32 arg0) {
    u8 sp2F;
    s32 sp28;

    if (GbTower_ProbePak(arg0, &sp2F, sGbSavePorts[arg0].unk_18) == 0) {
        Game_ShutdownAndLoadFragment(arg0, 2);
    }

    sp28 = GbSave_InvalidateMainDataChecksum(arg0);

    if (sp28 != 0) {
        sp28 = GbSave_WriteBoxBanks(arg0);
        if (sp28 != 0) {
            sp28 = GbSave_CommitMainData(arg0);
        }
    }

    sp28 &= GbTower_CheckPakRemoved(arg0, sp2F);
    return sp28;
}

void GbSave_ValidateBeforeWrite(s32 arg0) {
    u8 sp27;

    if (GbTower_ProbePak(arg0, &sp27, sGbSavePorts[arg0].unk_18) == 0) {
        Game_ShutdownAndLoadFragment(arg0, 2);
    }

    if (GbSave_CheckMainDataUnchanged(arg0) == 0) {
        Game_ShutdownAndLoadFragment(arg0, 1);
    }
}

void GbSave_RequirePakPresent(s32 arg0) {
    if (GbTower_CheckPakRemoved(arg0, 0) == 0) {
        Game_ShutdownAndLoadFragment(arg0, 2);
    }
}

GbSaveBoxEntry* GbSave_GetBoxEntry(s32 arg0, s32 arg1) {
    GbSaveBoxEntry* sp1C = NULL;
    s32 temp_v0 = GbSave_GetBoxCount(arg0);

    if (temp_v0 > 0) {
        if (arg1 == (temp_v0 - 1)) {
            sp1C = (GbSaveBoxEntry*)(sGbSavePorts[arg0].unk_40 + 0xAAD);
        } else if (arg1 < 4) {
            sp1C = (GbSaveBoxEntry*)(sGbSavePorts[arg0].unk_44 + arg1 * 0x566);
        } else {
            sp1C = (GbSaveBoxEntry*)(sGbSavePorts[arg0].unk_44 + arg1 * 0x566 + 8);
        }
    }
    return sp1C;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80022284; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80022284.s")
#endif

/*
 * func_8002234C
 *
 * Stores battle Pokemon slot arg2 of arg0 into slot arg2 of the party block
 * (offset 0x955 of the main save data) of Game Boy port arg1: the record
 * itself (Pokemon_ToGbRecordExt), the transcoded name at offset 0x30 of the
 * Pokemon, two 3-byte fields (offsets 0x3D and 0x4D of the Pokemon; their
 * meaning is not established here) and the species byte in the party's
 * species list.
 *
 * Same structure as GbSave_SaveMainPokemon in the Stadium 1 decomp.
 */
void func_8002234C(unk_func_88205880_00D0* arg0, s32 arg1, s32 arg2) {
    GbSavePartyZero* sp24 = (GbSavePartyZero*)(sGbSavePorts[arg1].unk_40 + 0x955);

    Pokemon_ToGbRecordExt(arg0, &sp24->unk_008[arg2]);
    Text_TranscodeName(sp24->unk_134[arg2], (char*)arg0->unk_000[0].unk_30);
    _bcopy((u8*)&arg0->unk_000[0] + 0x3D, sp24->unk_110[arg2], 3);
    _bcopy((u8*)&arg0->unk_000[0] + 0x4D, sp24->unk_110[arg2] + 3, 3);
    sp24->unk_001[arg2] = sp24->unk_008[arg2].unk_00.unk_00;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80022424; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80022424.s")
#endif

/*
 * func_800224E8
 *
 * Stores battle Pokemon arg0 into slot arg3 of box arg2 of Game Boy port
 * arg1, if that box exists (GbSave_GetBoxEntry returns non-NULL): the
 * record (Pokemon_ToGbRecord), the transcoded name at offset 0x30, two
 * 3-byte fields (offsets 0x3D and 0x4D of the Pokemon; their meaning is not
 * established here) and the species byte in the box's species list.
 * Before the conversion the Pokemon's byte at +0x04 is set from its byte at
 * +0x24.
 *
 * Same structure as GbSave_SaveBoxPokemon in the Stadium 1 decomp.
 */
void func_800224E8(BattleMon* arg0, s32 arg1, s32 arg2, s32 arg3) {
    GbSaveBoxZero* sp2C = (GbSaveBoxZero*)GbSave_GetBoxEntry(arg1, arg2);

    if (sp2C != NULL) {
        arg0->unk_04 = arg0->unk_24;
        Pokemon_ToGbRecord(arg0, &sp2C->unk_020[arg3]);
        Text_TranscodeName(sp2C->unk_4B2[arg3], (char*)arg0->unk_30);
        _bcopy((u8*)arg0 + 0x3D, sp2C->unk_3FE[arg3], 3);
        _bcopy((u8*)arg0 + 0x4D, sp2C->unk_3FE[arg3] + 3, 3);
        sp2C->unk_001[arg3] = sp2C->unk_020[arg3].unk_00;
    }
}

s32 GbSave_GetBoxEntryCount(s32 arg0, s32 arg1) {
    s32 sp1C = 0;
    GbSaveBoxEntry* temp_v0 = GbSave_GetBoxEntry(arg0, arg1);

    if (temp_v0 != NULL) {
        sp1C = temp_v0->unk_000;
    }
    return sp1C;
}

void GbSave_SetBoxEntryCount(s32 arg0, s32 arg1, s32 arg2) {
    GbSaveBoxEntry* temp_v0 = GbSave_GetBoxEntry(arg0, arg1);

    if (temp_v0 != NULL) {
        temp_v0->unk_000 = arg2;
        temp_v0->unk_001[arg2] = 0xFF;
    }
}

s32 Deck_GetCapacity(s32 arg0) {
    s32 ret = 0;

    switch (arg0) {
        case 32:
            ret = 6;
            break;

        case 33:
            ret = 0x1E;
            break;

        case 34:
            ret = 0x32;
            break;

        case 35:
            ret = 0x14;
            break;
    }

    return ret;
}

s32 Deck_GetEntrySize(s32 arg0) {
    s32 ret = 0;

    switch (arg0) {
        case 32:
            ret = 0x50;
            break;
        case 33:
            ret = 0x50;
            break;
        case 34:
            ret = 2;
            break;
        case 35:
            ret = 2;
            break;
    }
    return ret;
}

s32 Deck_GetCount(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    u8* ptr = sGbSavePorts[arg1].unk_40;

    switch (arg0) {
        case 32:
            var_v1 = ptr[0x955];
            break;

        case 33:
            var_v1 = GbSave_GetBoxEntryCount(arg1, arg2);
            break;

        case 34:
            var_v1 = ptr[0x25C];
            break;

        case 35:
            var_v1 = ptr[0x44];
            break;
    }
    return var_v1;
}

/*
 * func_8002274C
 *
 * Truncates the deck arg0 (32 = party, 33 = box, 34 and 35 = the two
 * BattleMonSpecies lists of the main save data) of Game Boy port arg1 to
 * arg3 entries, if it currently holds more than that: the count byte is set
 * to arg3 and the list is terminated with 0xFF at entry arg3.  For box
 * decks (33) the count is set through GbSave_SetBoxEntryCount using box
 * arg2.  Nothing happens if arg3 is not below the current count
 * (Deck_GetCount).
 *
 * Same structure as Deck_DeleteEntry in the Stadium 1 decomp, using its
 * VERSION_JP offsets.
 */
void func_8002274C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    GbSaveMainZero* sp1C = (GbSaveMainZero*)sGbSavePorts[arg1].unk_40;

    if (arg3 < Deck_GetCount(arg0, arg1, arg2)) {
        switch (arg0) {
            case 32:
                sp1C->unk_955.unk_000 = arg3;
                sp1C->unk_955.unk_001[arg3] = 0xFF;
                break;

            case 33:
                GbSave_SetBoxEntryCount(arg1, arg2, arg3);
                break;

            case 34:
                sp1C->unk_25C = arg3;
                sp1C->unk_25D[arg3].unk_00 = 0xFF;
                break;

            case 35:
                sp1C->unk_044 = arg3;
                sp1C->unk_045[arg3].unk_00 = 0xFF;
                break;
        }
    }
}

/*
 * func_80022828
 *
 * Appends one entry to deck arg0 of Game Boy port arg1 (box arg2 for box
 * decks), if the deck is below its capacity (Deck_GetCapacity): the count
 * becomes count + 1 and the list is re-terminated with 0xFF at the new
 * count.  The entry's contents are written separately (see Deck_WriteEntry).
 * Deck numbers are as in func_8002274C.
 *
 * Same structure as Deck_AppendEntry in the Stadium 1 decomp, using its
 * VERSION_JP offsets.
 */
void func_80022828(s32 arg0, s32 arg1, s32 arg2) {
    GbSaveMainZero* sp1C = (GbSaveMainZero*)sGbSavePorts[arg1].unk_40;
    s32 sp18 = Deck_GetCount(arg0, arg1, arg2);

    if (sp18 < Deck_GetCapacity(arg0)) {
        sp18++;

        switch (arg0) {
            case 32:
                sp1C->unk_955.unk_000 = sp18;
                sp1C->unk_955.unk_001[sp18] = 0xFF;
                break;

            case 33:
                GbSave_SetBoxEntryCount(arg1, arg2, sp18);
                break;

            case 34:
                sp1C->unk_25C = sp18;
                sp1C->unk_25D[sp18].unk_00 = 0xFF;
                break;

            case 35:
                sp1C->unk_044 = sp18;
                sp1C->unk_045[sp18].unk_00 = 0xFF;
                break;
        }
    }
}

/*
 * func_8002290C
 *
 * Reads entry arg3 of deck arg0 (port arg1, box arg2 for box decks) into
 * the BattleMon arg4.  Decks 32 and 33 load a full Pokemon
 * (GbSave_LoadMainPokemon / GbSave_LoadBoxPokemon); decks 34 and 35 copy
 * the 2-byte BattleMonSpecies list entry into the start of arg4.  Returns 1
 * if arg3 is below the deck's count (Deck_GetCount), else 0 and arg4 is
 * untouched.
 *
 * Same structure as Deck_ReadEntry in the Stadium 1 decomp, using its
 * VERSION_JP offsets.
 */
s32 func_8002290C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, BattleMon* arg4) {
    s32 sp1C = 0;

    if (arg3 < Deck_GetCount(arg0, arg1, arg2)) {
        GbSaveMainZero* temp_v0 = (GbSaveMainZero*)sGbSavePorts[arg1].unk_40;

        switch (arg0) {
            case 32:
                GbSave_LoadMainPokemon(arg4, arg1, arg3);
                break;

            case 33:
                GbSave_LoadBoxPokemon(arg4, arg1, arg2, arg3);
                break;

            case 35:
                arg4->unk_00 = temp_v0->unk_045[arg3];
                break;

            case 34:
                arg4->unk_00 = temp_v0->unk_25D[arg3];
                break;
        }
        sp1C = 1;
    }
    return sp1C;
}

/*
 * func_80022A00
 *
 * Writes the Pokemon in arg4 to entry arg3 of deck arg0 (port arg1, box
 * arg2 for box decks).  Allowed when arg3 is an existing entry, or the
 * entry just past the end while the deck is below its capacity; returns 1
 * in those cases, else 0 and nothing is written.  Decks 32 and 33 store a
 * full Pokemon (GbSave_SaveMainPokemon / GbSave_SaveBoxPokemon); decks 34
 * and 35 store the 2-byte BattleMonSpecies at the start of arg4's first
 * Pokemon.  When writing at the end, the deck is then extended with
 * func_80022828.
 *
 * Same structure as Deck_WriteEntry in the Stadium 1 decomp, using its
 * VERSION_JP offsets.
 */
s32 func_80022A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, unk_func_88205880_00D0* arg4) {
    s32 sp2C = 0;
    s32 sp28 = Deck_GetCapacity(arg0);
    s32 sp24 = Deck_GetCount(arg0, arg1, arg2);

    if ((arg3 < sp24) || ((arg3 == sp24) && (arg3 < sp28))) {
        GbSaveMainZero* ptr = (GbSaveMainZero*)sGbSavePorts[arg1].unk_40;

        switch (arg0) {
            case 32:
                GbSave_SaveMainPokemon(arg4, arg1, arg3);
                break;

            case 33:
                GbSave_SaveBoxPokemon(arg4, arg1, arg2, arg3);
                break;

            case 35:
                ptr->unk_045[arg3] = arg4->unk_000[0].unk_00;
                break;

            case 34:
                ptr->unk_25D[arg3] = arg4->unk_000[0].unk_00;
                break;
        }

        if (arg3 == sp24) {
            Deck_AppendEntry(arg0, arg1, arg2);
        }

        sp2C = 1;
    }
    return sp2C;
}

s32 GbSave_GetPresentPortMask(void) {
    return D_800AD330;
}

extern s8 D_800AD213;
u8 func_80022B4C(s32 arg0) {
    return *(&D_800AD213 + (arg0 * 0x48));
}

s32 GbSave_GetPortAvailability(s32 arg0) {
    s32 temp_v0 = 1 << arg0;

    if (!(D_800AD334 & temp_v0)) {
        return 1;
    }

    if (!(D_800AD335 & temp_v0)) {
        return 2;
    }

    return 0;
}

extern s8 D_800AD212;
u8 func_80022BAC(s32 arg0) {
    return *(&D_800AD212 + (arg0 * 0x48));
}

/*
 * func_80022BC8
 *
 * Refreshes the cached player identity of Game Boy port arg0 from that
 * port's loaded save image.  Returns 0 if the port's "present" bit
 * (bit 0 of the port's first halfword) is clear; otherwise stores the
 * big-endian halfword at offset 0x7B of the save image into the port's
 * unk_38, copies the 6-byte name at image offset 0x18 to the port's
 * unk_3A, and returns 1.
 *
 * Same structure as GbSave_RefreshPlayerIdentity in the Stadium 1 decomp
 * (found by comparing the compiled donor function against Zero's
 * instruction shape); Zero's port stride is 0x48 rather than 0x58.
 * func_8001FAB0 reads a big-endian halfword (the donor calls the
 * equivalent GbData_ReadU16BE) and the copy is _bcopy(src, dst, size).
 * The index expression is repeated rather than cached in a local: caching
 * it moves the compiler's spill of the port pointer from sp+0x1C to
 * sp+0x18 and no longer matches.
 */
s32 func_8001FAB0(u8*);

s32 func_80022BC8(s32 arg0) {
    if (!(sGbSavePorts[arg0].unk_00 & 1)) {
        return 0;
    }
    sGbSavePorts[arg0].unk_38 = func_8001FAB0(sGbSavePorts[arg0].unk_40 + 0x7B);
    _bcopy(sGbSavePorts[arg0].unk_40 + 0x18, sGbSavePorts[arg0].unk_3A, 6);
    return 1;
}

/*
 * func_80022C40
 *
 * Copies the 8-byte cached player identity of Game Boy port arg0 (the
 * halfword at port offset 0x38 followed by the 6-byte name at 0x3A, the
 * pair that func_80022BC8 refreshes) to arg1.  Zero's equivalent of
 * GbSave_CopyPlayerIdentity in the Stadium 1 decomp, which copies a
 * 0x10-byte record with the same 64-bit load/store; Zero's record is
 * only 8 bytes and its port stride is 0x48.
 */
void func_80022C40(s32 arg0, void* arg1) {
    u64* ptr = (u64*)&sGbSavePorts[arg0].unk_38;
    u64* ptr2 = arg1;

    *ptr2++ = *ptr++;
}

extern s8 D_800AD210;
s32 func_80022C70(s32 arg0) {
    s8 *temp_v0;

    temp_v0 = (arg0 * 0x48) + &D_800AD210;
    if (!(M2C_FIELD(temp_v0, u16 *, 0) & 1)) {
        return -1;
    }
    return func_8001FAB0((u8*)M2C_FIELD(temp_v0, s32 *, 0x40) + 0x7B);
}

void GbSave_SetTrainerId(s32 arg0, u16 arg1) {
    if (sGbSavePorts[arg0].unk_00 & 1) {
        GbData_WriteU16BE(sGbSavePorts[arg0].unk_40 + 0x7B, arg1);
    }
}

s32 GbSave_GetBoxCount(s32 arg0) {
    s32 temp_a0;
    s32 phi_v1 = -1;

    if (sGbSavePorts[arg0].unk_00 & 1) {
        temp_a0 = GbData_ReadU16BE(sGbSavePorts[arg0].unk_40 + 0x2C2) >> 8;
        if (temp_a0 & 0x80) {
            phi_v1 = (temp_a0 & 0x7F) + 1;
        } else {
            phi_v1 = 0;
        }
    }
    return phi_v1;
}

s32 func_8001FCC0(M2C_UNK, s32, M2C_UNK);           /* extern */
extern s8 D_800AD210;
s32 func_80022D84(s32 arg0, M2C_UNK arg1)
{
  s8 *temp_v0;
  temp_v0 = (arg0 * 0x48) + (&D_800AD210);
  if (!((*((u16 *) (((s8 *) temp_v0) + 0))) & 1))
  {
    return 0;
  }
  return func_8001FCC0(arg1 & 0xFFFFFFFFFFFFFFFF, (*((s32 *) (((s8 *) temp_v0) + 0x40))) + 0x18, arg1);
}

s32 func_8001FBE4(s32);                             /* extern */
extern s8 D_800AD210;
s32 func_80022DDC(s32 arg0) {
    s8 *temp_v0;

    temp_v0 = (arg0 * 0x48) + &D_800AD210;
    if (!(M2C_FIELD(temp_v0, u16 *, 0) & 1)) {
        return 0;
    }
    return func_8001FBE4(M2C_FIELD(temp_v0, s32 *, 0x40) + 0x18);
}

s32 func_8001FCC0(M2C_UNK, s32, M2C_UNK);           /* extern */
extern s8 D_800AD210;
s32 func_80022E30(s32 arg0, M2C_UNK arg1)
{
  s8 *temp_v0;
  temp_v0 = (arg0 * 0x48) + (&D_800AD210);
  if (!((*((u16 *) (((s8 *) temp_v0) + 0))) & 1))
  {
    return 0;
  }
  return func_8001FCC0(arg1 ^ 0, (*((s32 *) (((s8 *) temp_v0) + 0x40))) + 0x71, arg1);
}

s32 func_8001FBE4(s32);                             /* extern */
extern s8 D_800AD210;
s32 func_80022E88(s32 arg0) {
    s8 *temp_v0;

    temp_v0 = (arg0 * 0x48) + &D_800AD210;
    if (!(M2C_FIELD(temp_v0, u16 *, 0) & 1)) {
        return 0;
    }
    return func_8001FBE4(M2C_FIELD(temp_v0, s32 *, 0x40) + 0x71);
}

/*
 * GbSave_SavedAtPokemonCenter (owner func_80022EDC)
 *
 * Returns 1 if the Game Boy save on port `arg0` was last saved at a
 * Pokemon Center, otherwise 0.  The flag is bit 0x4000 of the first
 * halfword of that port's record (each record is 0x48 bytes).  The name
 * comes from the Stadium 1 decomp, where the same test is written against
 * the 0x58-byte Stadium 1 record.
 */
s32 GbSave_SavedAtPokemonCenter(s32 arg0) {
    return (sGbSavePorts[arg0].unk_00 & 0x4000) != 0;
}

extern s8 D_800AD210;
s32 func_80022F00(s32 arg0) {
    s32 var_v1;
    s8 *temp_v0;

    var_v1 = 0;
    if (arg0 >= 0) {
        temp_v0 = (arg0 * 0x48) + &D_800AD210;
        if (M2C_FIELD(temp_v0, u16 *, 0) & 1) {
            var_v1 = (M2C_FIELD(M2C_FIELD(temp_v0, s8 **, 0x40), s8 *, 0x46D) & 0x20) != 0;
        }
    }
    return var_v1;
}

extern s8 D_800AD210;
s32 func_80022F48(s32 arg0) {
    s32 var_v1;
    s8 *temp_v0;

    var_v1 = 0;
    if (arg0 >= 0) {
        temp_v0 = (arg0 * 0x48) + &D_800AD210;
        if (M2C_FIELD(temp_v0, u16 *, 0) & 1) {
            var_v1 = (M2C_FIELD(M2C_FIELD(temp_v0, s8 **, 0x40), s8 *, 0x513) & 1) != 0;
        }
    }
    return var_v1;
}

s32 GbSave_CopyPortSnapshot(s32 arg0, GbSavePortSnapshot* arg1) {
    s32 temp_v1 = (sGbSavePorts[arg0].unk_00 & 1) != 0;

    if (temp_v1 != 0) {
        arg1->unk_000 = sGbSavePorts[arg0].unk_02;
        arg1->unk_001 = sGbSavePorts[arg0].unk_04;
        arg1->unk_002 = sGbSavePorts[arg0].unk_38;

        _bcopy(sGbSavePorts[arg0].unk_3A, arg1->unk_004, 6);
        _bcopy(sGbSavePorts[arg0].unk_40 + 0x955, (u8*)arg1 + 0xA, 0x158);
    }
    return temp_v1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_8002302C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_8002302C.s")
#endif

void GbSave_RebuildSeenBitfield(s32 arg0) {
    GbSavePortZero* ptr = &sGbSavePorts[arg0];
    u8* temp_s0 = ptr->unk_40;
    u8* ptr6 = ptr->unk_05;
    u8* ptr541 = ptr->unk_44;
    u8* ptr542 = ptr->unk_44 + 0x15A0;
    s32 i;

    for (i = 0; i < 19; i++) {
        ptr6[i] = 0;
    }

    GbSave_MarkSeenBits(ptr6, temp_s0[0x955], temp_s0 + 0x956);
    GbSave_MarkSeenBits(ptr6, temp_s0[0xAAD], temp_s0 + 0xAAE);

    for (i = 0; i < 4; i++) {
        GbSave_MarkSeenBits(ptr6, ptr541[i * 0x566], ptr541 + i * 0x566 + 1);
        GbSave_MarkSeenBits(ptr6, ptr542[i * 0x566], ptr542 + i * 0x566 + 1);
    }
}

s32 GbSave_GetSpeciesProgressLevel(s32 arg0, s32 arg1) {
    s32 temp_t1;
    s32 temp_t2;
    u8* ptr23;
    u8* ptr36;

    if ((arg1 > 0) && (arg1 < 0x98)) {
        ptr23 = sGbSavePorts[arg0].unk_40 + 0x1E;
        ptr36 = sGbSavePorts[arg0].unk_40 + 0x31;

        temp_t1 = (arg1 - 1) / 8;
        temp_t2 = (arg1 - 1) % 8;

        return ((ptr23[temp_t1] >> temp_t2) & 1) + ((ptr36[temp_t1] >> temp_t2) & 1) +
               ((sGbSavePorts[arg0].unk_05[temp_t1] >> temp_t2) & 1);
    }
    return 0;
}

void func_80023268(s32 arg0, s32 arg1, s32 arg2) {
    u8* temp_a3;
    u8* temp_v0;
    s32 var_a2;
    s32 var_a3;
    u8* temp_v1;

    if ((arg1 > 0) && (arg1 < 0x98)) {
        temp_v0 = (sGbSavePorts[arg0].unk_40 + 0x1E);
        temp_a3 = (sGbSavePorts[arg0].unk_40 + 0x31);
        temp_v1 = sGbSavePorts[arg0].unk_05;

        var_a2 = (arg1 - 1) / 8;
        var_a3 = (arg1 - 1) % 8;

        if (arg2 > 0) {
            temp_a3[var_a2] |= (1 << var_a3);
        } else {
            temp_a3[var_a2] &= ~(1 << var_a3);
        }

        if (arg2 >= 2) {
            temp_v0[var_a2] |= (1 << var_a3);
        } else {
            temp_v0[var_a2] &= ~(1 << var_a3);
        }

        if (arg2 >= 3) {
            temp_v1[var_a2] |= (1 << var_a3);
        } else {
            temp_v1[var_a2] &= ~(1 << var_a3);
        }
    }
}

/*
 * func_800233AC
 *
 * Counts the set bits among the first 0x97 (151) bits of the bit array at
 * offset 0x31 of the main save data of Game Boy port arg0 (bit i is bit
 * i % 8 of byte i / 8).  Which Pokedex flag set that array is (seen or
 * owned) is not established here; see func_800234EC for the other array,
 * at offset 0x1E.
 *
 * Same structure as GbSave_CountSpeciesProgressField036 in the Stadium 1
 * decomp (its VERSION_JP offset is also 0x31).
 */
s32 func_800233AC(s32 arg0) {
    s32 i;
    s32 temp_v1 = 0;

    for (i = 0; i < 0x97; i++) {
        temp_v1 += (sGbSavePorts[arg0].unk_40[0x31 + i / 8] >> (i % 8)) & 1;
    }

    return temp_v1;
}

/*
 * func_800234EC
 *
 * Same as func_800233AC but over the bit array at offset 0x1E of the main
 * save data: counts the set bits among the first 0x97 (151) bits, where
 * bit i is bit i % 8 of byte i / 8.
 *
 * Same structure as GbSave_CountSpeciesProgressField023 in the Stadium 1
 * decomp (its VERSION_JP offset is also 0x1E).
 */
s32 func_800234EC(s32 arg0) {
    s32 i;
    s32 temp_v1 = 0;

    for (i = 0; i < 0x97; i++) {
        temp_v1 += (sGbSavePorts[arg0].unk_40[0x1E + i / 8] >> (i % 8)) & 1;
    }

    return temp_v1;
}

s32 func_8002362C(s32 arg0) {
    s32 i;
    s32 temp_v1 = 0;

    for (i = 0; i < 0x97; i++) {
        temp_v1 += (sGbSavePorts[arg0].unk_05[i / 8] >> (i % 8)) & 1;
    }

    return temp_v1;
}
