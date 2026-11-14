/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/DDC0.c, src/audio_sound_state.c, src/save_data.c. */

#include "save_data.h"

#include "libnumus/player.h"

#include <PR/os_internal_reg.h>
#include "global.h"
extern s32 D_800AAE30;
extern s32 D_800AAF3C;

#include "m2c_macros.h"

u16 Save_Checksum(u8* arg0, s32 arg1);
s32 Save_RecordIsValid(u8* arg0, s32 arg1);
void Save_WriteFooter(u8* arg0, s32 arg1, s32 arg2);
s32 Audio_GetFreeVoiceCount(void);
void func_80024044(void);
void Save_ResetAndCommitTypedRecord(s32 arg0, s32 arg1);
s32 Deck_IsSaveEntryPresent(s32 arg0, s32 arg1);

s32 Save_IsTypedRecordFlagSet(s32 arg0, s32 arg1, s16 arg2);
void Save_CommitTypedRecord(s32 arg0, s32 arg1);
void Save_ClearTypedRecord(s32 arg0, s32 arg1);

/** Computes the checksum of a save record. */
u16 Save_Checksum(u8* arg0, s32 arg1) {
    u16 var_v1 = 0;

    while (arg1-- > 2) {
        var_v1 += *arg0++;
    }
    return var_v1;
}

/** Returns whether a save record's checksum is valid. */
s32 Save_RecordIsValid(u8* arg0, s32 arg1) {
    u16* temp_v1 = arg1 + arg0;

    temp_v1 -= 3;

    if (temp_v1[0] != 'PO') {
        return 0;
    }

    if (temp_v1[1] != 'KE') {
        return 0;
    }

    if (temp_v1[2] != Save_Checksum(arg0, arg1)) {
        return 0;
    }

    return 1;
}

/** Writes the footer of a save record. */
void Save_WriteFooter(u8* arg0, s32 arg1, s32 arg2) {
    u16* temp_v1;

    if (arg2 != 0) {
        temp_v1 = arg1 + arg0;

        temp_v1 -= 3;
        *temp_v1++ = 'PO';
        *temp_v1++ = 'KE';
        *temp_v1++ = Save_Checksum(arg0, arg1);
    } else {
        temp_v1 = arg1 + arg0;
        temp_v1 -= 3;

        *temp_v1++ = 'XX';
        *temp_v1++ = 'XX';
        *temp_v1++ = Save_Checksum(arg0, arg1) ^ 0xFF;
    }
}

M2C_UNK func_80058410(s32, s32, s32);
M2C_UNK func_80003774(s32, M2C_UNK, M2C_UNK, M2C_UNK);
extern s32 D_800AE8E0;
#define gSaveSram (*(SaveSram**)&D_800AE8E0)
void func_80023890(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp1C = arg1 - D_800AE8E0;

    func_80058410(arg0, arg1, arg2);
    func_80003774(arg1, sp1C, arg2, 1);
}

/*
 * func_800238D8: flushes one save record whose "dirty" flag is set.
 *
 * `arg0` is the address of the record inside the buffer at D_800AE8E0 and
 * `arg1` its size in bytes (halfword flag at the start of the record).  If
 * bit 1 of that halfword is set: the bit is cleared, the footer is rewritten
 * with Save_WriteFooter(record, size, 1) (the valid 'PO' 'KE' form), the
 * record is copied to record + size via func_80058410(src, dst, size) -- a
 * second copy directly behind it -- and func_80003774 is called with the
 * record address, its offset from the start of the buffer, twice the size and
 * 1.  What func_80003774 does with them (the offset and doubled size suggest
 * a write of both copies out to the save medium) is not established here.
 *
 * Callers such as Save_CommitTypedRecord pass a third argument that this function
 * ignores, so the prototype is left unspecified at the call sites and the
 * definition is written in K&R style.  The unused pad[2] only reproduces the
 * retail stack frame.
 */
void func_800238D8(arg0, arg1)
    s32 arg0;
    s32 arg1;
{
    UNUSED s32 pad[2];
    s32 offset;
    s16 flags = *(s16*)arg0;

    if (flags & 2) {
        offset = arg0 - D_800AE8E0;
        *(s16*)arg0 = flags & 0xFFFD;
        Save_WriteFooter((u8*)arg0, arg1, 1);
        func_80058410(arg0, arg0 + arg1, arg1);
        func_80003774(arg0, offset, arg1 * 2, 1);
    }
}

/*
 * func_80023954: same as func_800238D8, but for invalidating a dirty record.
 *
 * If bit 1 of the record's leading halfword is set, the footer is written with
 * Save_WriteFooter(record, size, 0) (the 'XX' 'XX' form with the inverted
 * checksum), the record is copied to record + size via func_80058410 and
 * func_80003774 is called with the record address, its offset from the start
 * of the buffer at D_800AE8E0, twice the size and 1.  Unlike func_800238D8
 * the flag bit is left set.  `arg0` is the record address and `arg1` its size.
 * A third argument passed by Save_InvalidateTypedRecord is ignored; the definition is K&R
 * style for that reason, and the unused pad[2] reproduces the retail stack
 * frame.
 */
void func_80023954(arg0, arg1)
    s32 arg0;
    s32 arg1;
{
    UNUSED s32 pad[2];
    s32 offset;

    if (*(s16*)arg0 & 2) {
        offset = arg0 - D_800AE8E0;
        Save_WriteFooter((u8*)arg0, arg1, 0);
        func_80058410(arg0, arg0 + arg1, arg1);
        func_80003774(arg0, offset, arg1 * 2, 1);
    }
}

M2C_UNK func_80058410(s32, s32, s32);               /* extern */

void func_800239C4(s32 arg0, s32 arg1) {
    func_80058410(arg0 + arg1, arg0, arg1);
}


M2C_UNK func_8004FD20();                            /* extern */
void func_800239F0(arg0)
    s16* arg0;
{
  if (1)
  {
    func_8004FD20();
    *arg0 |= 2;
  }
}

s32 func_800237AC(s32, s32);
void func_800245E0(s32, s32);
void func_80023A20(s32 arg0, s32 arg1) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 size;
    s32 primary;
    s32 backup;
    s32 status;

    switch (arg0) {
        case 16:
            primary = (s32)&gSaveSram->teams[arg1][0];
            backup = (s32)&gSaveSram->teams[arg1][1];
            size = 0x128;
            break;
        case 17:
            primary = (s32)&gSaveSram->boxes[arg1][0];
            backup = (s32)&gSaveSram->boxes[arg1][1];
            size = 0x560;
            break;
        case 18:
            primary = (s32)&gSaveSram->items[arg1][0];
            backup = (s32)&gSaveSram->items[arg1][1];
            size = 0xE0;
            break;
        case 19:
            primary = (s32)&gSaveSram->list[0];
            backup = (s32)&gSaveSram->list[1];
            size = 0x11A0;
            break;
        case 20:
            primary = (s32)&gSaveSram->options[0];
            backup = (s32)&gSaveSram->options[1];
            size = 0x10;
            break;
        case 21:
            primary = (s32)&gSaveSram->continueData[0];
            backup = (s32)&gSaveSram->continueData[1];
            size = 0x288;
            break;
    }
    status = func_800237AC(primary, size);
    status = (func_800237AC(backup, size) << 1) | status;
    switch (status) {
        case 0:
            func_800245E0(arg0, arg1);
            break;
        case 1:
            func_80023890(primary, backup, size);
            break;
        case 2:
            func_80023890(backup, primary, size);
            break;
    }
}

extern s32 D_8006BBA0;
extern s32 D_800AE8E0;

void func_80023C08(s32 arg0, s32 arg1) {
    if (arg1 == 0x42553634) {
        D_8006BBA0 = 0;
        D_800AE8E0 = 0;
    }
}

s32 func_8000234C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *); /* extern */
M2C_UNK func_80003774(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
void func_80023A20(s32, s32);
M2C_UNK func_8004FD20(s32, M2C_UNK);                /* extern */
s32 func_80023C30(void)
{
  s32 temp_v0;
  int new_var; // FAKE: permuter temp
  s32 var_s0;
  s32 var_s0_2;
  if ((*((s32 *) (&D_8006BBA0))) == 0)
  {
 do { temp_v0 = func_8000234C(0x8000, 0, 0x42553634, &(*((s8 *) (&func_80023C08)))); *((s32 *) (&D_800AE8E0)) = temp_v0; } while (0);  // FAKE
    if (temp_v0 != 0)
    {
      *((s32 *) (&D_8006BBA0)) = 1;
      new_var = 0;
      func_8004FD20(temp_v0, 0x8000);
      func_80003774(*((s32 *) (&D_800AE8E0)), 0, 0x8000, 0);
      var_s0 = new_var;
      do
      {
        func_80023A20(0x10, var_s0);
        var_s0 += 1;
      }
      while (var_s0 < 0x10);
      var_s0_2 = 0;
      do
      {
        func_80023A20(0x11, var_s0_2);
        func_80023A20(0x12, var_s0_2);
        var_s0_2 += 1;
      }
      while (var_s0_2 != 4);
      func_80023A20(0x13, new_var);
      func_80023A20(0x14, 0);
      func_80023A20(0x15, new_var);
    }
  }
  return *((s32 *) (&D_8006BBA0));
}

/** Returns the number of free voices. */
s32 Audio_GetFreeVoiceCount(void) {
    return mus_free_voices_count;
}

M2C_UNK func_8001FB10(s32, s32);                    /* extern */
M2C_UNK func_8001FE84();                            /* extern */
M2C_UNK func_800203FC(s32);                         /* extern */
M2C_UNK func_80058410(s32, s32, M2C_UNK);           /* extern */

// Unpacks a save record (arg1, SaveMonRecord*) into a BattleMon (arg0). The arguments stay s32:
// typing them as pointers grows the stack frame.
void func_80023D3C(s32 arg0, s32 arg1) {
    s32 sp24;
    s32 temp_a0;

    func_8001FE84();
    func_800203FC(arg0);
    temp_a0 = (s32)((SaveMonRecord*)arg1)->otName;
    sp24 = temp_a0;
    func_80058410(temp_a0, (s32)((BattleMon*)arg0)->gbOtNameHead, 3);
    func_80058410((s32)&((SaveMonRecord*)arg1)->otName[3], (s32)((BattleMon*)arg0)->gbOtNameTail, 3);
    func_8001FB10((s32)((BattleMon*)arg0)->nickname, (s32)((SaveMonRecord*)arg1)->nickname);
    func_8001FB10((s32)((BattleMon*)arg0)->otName, sp24);
}

/**
 * Packs a BattleMon into a GB-format save record with its transcoded name and trainer data.
 * Seen in play (2026-11-13) ran when the party was registered into slot 01 and again into slot 02
 * (とうろく > ポケモンをとうろくする, はい).
 * @unverified Name and comment guessed from the code.
 */
void BattleMon_ToGbSaveRecord(BattleMon* arg0, SaveMonRecord* arg1) {
    arg0->boxLevel = arg0->level;
    Pokemon_ToGbRecord(arg0, &arg1->mon);
    Text_TranscodeName((char*)arg1->nickname, (char*)arg0->nickname);
    func_80058410((s32)arg0->gbOtNameHead, (s32)arg1->otName, 3);
    func_80058410((s32)arg0->gbOtNameTail, (s32)&arg1->otName[3], 3);
}

/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the Lab list, registration,
 * the Lab PC and Free Battle setup.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Save_IsTypedRecordFlagSet(arg0, arg1, arg2)
    s32 arg0;
    s32 arg1;
    s16 arg2;
{
    s32 ret = 0;
    switch (arg0) {
    case 16:
        ret = (gSaveSram->teams[arg1][0].flags & arg2) != 0;
        break;
    case 17:
        ret = (gSaveSram->boxes[arg1][0].flags & arg2) != 0;
        break;
    case 18:
        ret = (gSaveSram->items[arg1][0].flags & arg2) != 0;
        break;
    case 19:
        ret = (gSaveSram->list[0].flags & arg2) != 0;
        break;
    case 20:
        ret = (gSaveSram->options[0].flags & arg2) != 0;
        break;
    case 21:
        ret = (gSaveSram->continueData[0].flags & arg2) != 0;
        break;
    }
    return ret;
}

M2C_UNK func_80023F38(arg0, arg1, arg2)
    s32 arg0;
    s32 arg1;
    s16 arg2;
{
    switch (arg0) {
    case 16:
        gSaveSram->teams[arg1][0].flags |= arg2;
        break;
    case 17:
        gSaveSram->boxes[arg1][0].flags |= arg2;
        break;
    case 18:
        gSaveSram->items[arg1][0].flags |= arg2;
        break;
    case 19:
        gSaveSram->list[0].flags |= arg2;
        break;
    case 20:
        gSaveSram->options[0].flags |= arg2;
        break;
    case 21:
        gSaveSram->continueData[0].flags |= arg2;
        break;
    }
}

void func_80024044(void) {
}

void func_800238D8(); // Called with two or three arguments.
/**
 * Seen in play (2026-11-13) ran when quitting the GB player (C-Up menu, Quit game, Yes) back to the
 * main menu.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Save_CommitTypedRecord(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16:
        func_800238D8((s32)gSaveSram->teams[arg1], 0x128, arg1);
        return;
    case 17:
        func_800238D8((s32)gSaveSram->boxes[arg1], 0x560, arg1);
        return;
    case 18:
        func_800238D8((s32)gSaveSram->items[arg1], 0xE0, arg1);
        return;
    case 19:
        func_800238D8((s32)gSaveSram->list, 0x11A0, arg1);
        return;
    case 20:
        func_800238D8((s32)gSaveSram->options, 0x10, arg1);
        return;
    case 21:
        func_800238D8((s32)gSaveSram->continueData, 0x288, arg1);
        /* fallthrough */
    default:
        return;
    }
}

void func_80023954(); // Called with three arguments; the third is ignored.
/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Save_InvalidateTypedRecord(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16:
        func_80023954((s32)gSaveSram->teams[arg1], 0x128, arg1);
        return;
    case 17:
        func_80023954((s32)gSaveSram->boxes[arg1], 0x560, arg1);
        return;
    case 18:
        func_80023954((s32)gSaveSram->items[arg1], 0xE0, arg1);
        return;
    case 19:
        func_80023954((s32)gSaveSram->list, 0x11A0, arg1);
        return;
    case 20:
        func_80023954((s32)gSaveSram->options, 0x10, arg1);
        return;
    case 21:
        func_80023954((s32)gSaveSram->continueData, 0x288, arg1);
        /* fallthrough */
    default:
        return;
    }
}

void func_80024294(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16:
        func_800239C4((s32)gSaveSram->teams[arg1], 0x128);
        break;
    case 17:
        func_800239C4((s32)gSaveSram->boxes[arg1], 0x560);
        break;
    case 18:
        func_800239C4((s32)gSaveSram->items[arg1], 0xE0);
        break;
    case 19:
        func_800239C4((s32)gSaveSram->list, 0x11A0);
        break;
    case 20:
        func_800239C4((s32)gSaveSram->options, 0x10);
        break;
    case 21:
        func_800239C4((s32)gSaveSram->continueData, 0x288);
        break;
    }
}

void func_800243B8(void) {
    s32 i;

    for (i = 0; i < 0x2500; i += 0x250) {
        func_800238D8(*(s32*)&D_800AE8E0 + i, 0x128);
    }
    for (i = 0; i < 0x2B00; i += 0xAC0) {
        func_800238D8(*(s32*)&D_800AE8E0 + i + 0x2500, 0x560);
    }
    for (i = 0; i < 0x700; i += 0x1C0) {
        func_800238D8(*(s32*)&D_800AE8E0 + i + 0x5000, 0xE0);
    }
    func_800238D8(*(s32*)&D_800AE8E0 + 0x5700, 0x11A0);
}

/**
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Save_ClearTypedRecord(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16: {
        SaveTeamRecord* rec = &gSaveSram->teams[arg1][0];
        func_800239F0(&rec->flags, 0x128);
        rec->trainerName[0] = 0x50;
        rec->secondName[0] = 0x50;
        break;
    }
    case 17: {
        SaveBoxRecord* rec = &gSaveSram->boxes[arg1][0];
        func_800239F0(&rec->flags, 0x560);
        rec->trainerName[0] = 0x50;
        rec->secondName[0] = 0x50;
        break;
    }
    case 18: {
        SaveItemRecord* rec = &gSaveSram->items[arg1][0];
        func_800239F0(&rec->flags, 0xE0);
        rec->trainerName[0] = 0x50;
        break;
    }
    case 19: {
        s16* rec = &gSaveSram->list[0].flags;
        func_800239F0(rec, 0x11A0);
        *rec |= 1;
        break;
    }
    case 20: {
        s16* rec = &gSaveSram->options[0].flags;
        func_800239F0(rec, 0x10);
        *rec |= 1;
        break;
    }
    case 21:
        func_800239F0(&gSaveSram->continueData[0].flags, 0x288);
        break;
    }
}

/** Clears a typed save record and commits it. */
void Save_ResetAndCommitTypedRecord(s32 arg0, s32 arg1) {
    Save_ClearTypedRecord(arg0, arg1);
    Save_CommitTypedRecord(arg0, arg1);
}

/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the Lab list, Lab sort and the
 * Lab PC.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Deck_GetSaveRecordCapacity(s32 arg0) {
    s32 ret = 0;

    switch (arg0) {
        case 16:
            ret = 6;
            break;

        case 17:
            ret = 0x1E;
            break;

        case 18:
            ret = 0x64;
            break;

        case 19:
            ret = 0x64;
            break;
    }

    return ret;
}

/**
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the Lab list, Lab sort and the
 * Lab PC.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Deck_GetSaveRecordSize(s32 arg0) {
    s32 ret = 0;

    switch (arg0) {
        case 16:
            ret = 0x50;
            break;
        case 17:
            ret = 0x50;
            break;
        case 18:
            ret = 2;
            break;
        case 19:
            ret = 80;
            break;
    }
    return ret;
}

/** Returns whether a deck entry exists in the save data. */
s32 Deck_IsSaveEntryPresent(s32 arg0, s32 arg1) {
    return Save_IsTypedRecordFlagSet(arg0, arg1, 1);
}

s32 func_800246A8(s32, s32);
/**
 * Seen in play (2026-11-13) ran when slot 01 was picked in とうろく > とうろくしたポケモンをけす, before the
 * このポケモンをけす？ prompt.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
s32 Deck_GetSaveEntryTrainerId(s32 arg0, s32 arg1) {
    s32 ret = -1;

    if (func_800246A8(arg0, arg1) != 0) {
        switch (arg0) {
            case 16:
                ret = gSaveSram->teams[arg1][0].trainerId;
                break;
            case 17:
                ret = gSaveSram->boxes[arg1][0].trainerId;
                break;
            case 18:
                ret = gSaveSram->items[arg1][0].trainerId;
                break;
        }
    }
    return ret;
}

s32 func_800246A8(s32, s32);
/** Copies the name of a deck entry from the save data. */
s32 Deck_GetSaveEntryName(s32 arg0, s32 arg1, u8* arg2) {
    s32 ret = 0;
    s32 src;

    *arg2 = 0;
    if (func_800246A8(arg0, arg1) != 0) {
        src = 0;
        switch (arg0) {
            case 16:
                src = (s32)gSaveSram->teams[arg1][0].trainerName;
                break;
            case 17:
                src = (s32)gSaveSram->boxes[arg1][0].trainerName;
                break;
            case 18:
                src = (s32)gSaveSram->items[arg1][0].trainerName;
                break;
        }
        if (src != 0) {
            ret = func_8001FB10((s32)arg2, src);
        }
    }
    return ret;
}

s32 func_800246A8(s32, s32);
s32 func_8002488C(s32 arg0, s32 arg1, u8* arg2) {
    s32 ret = 0;
    s32 src;

    *arg2 = 0;
    if (func_800246A8(arg0, arg1) != 0) {
        src = 0;
        switch (arg0) {
            case 16:
                src = (s32)gSaveSram->teams[arg1][0].secondName;
                break;
            case 17:
                src = (s32)gSaveSram->boxes[arg1][0].secondName;
                break;
        }
        if (src != 0) {
            ret = func_8001FB10((s32)arg2, src);
        }
    }
    return ret;
}

/** Sets the trainer ID and name of a deck entry in the save data. */
void Deck_SetSaveEntryTrainerIdAndName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    switch (arg0) {
        case 16: {
            SaveTeamRecord* rec = &gSaveSram->teams[arg1][0];
            if ((s32)arg4 >= 0) {
                rec->trainerId = arg4;
            }
            if (arg3 != 0) {
                func_8001FBE4(rec->trainerName, arg3);
            }
            if (arg2 != 0) {
                func_8001FBE4(rec->secondName, arg2);
            }
            func_80023F38(arg0, arg1, 3);
            break;
        }
        case 17: {
            SaveBoxRecord* rec = &gSaveSram->boxes[arg1][0];
            if ((s32)arg4 >= 0) {
                rec->trainerId = arg4;
            }
            if (arg3 != 0) {
                func_8001FBE4(rec->trainerName, arg3);
            }
            if (arg2 != 0) {
                func_8001FBE4(rec->secondName, arg2);
            }
            func_80023F38(arg0, arg1, 3);
            break;
        }
        case 18: {
            SaveItemRecord* rec = &gSaveSram->items[arg1][0];
            if ((s32)arg4 >= 0) {
                rec->trainerId = arg4;
            }
            if (arg3 != 0) {
                func_8001FBE4(rec->trainerName, arg3);
            }
            func_80023F38(arg0, arg1, 3);
            break;
        }
    }
}

/* Old-style definition: callers pass their own args through (see below). */
s32 func_80024ADC(arg0, arg1) s32 arg0; s32 arg1; {
    s32 ret = 0;

    switch (arg0) {
        case 16:
            ret = gSaveSram->teams[arg1][0].count;
            break;
        case 17:
            ret = gSaveSram->boxes[arg1][0].count;
            break;
        case 18:
            ret = gSaveSram->items[arg1][0].count;
            break;
        case 19:
            ret = gSaveSram->list[0].count;
            break;
    }
    return ret;
}

M2C_UNK func_80023F38(s32, s32, M2C_UNK);           /* extern */
s32 func_80024ADC();                                /* extern */

/**
 * Seen in play (2026-11-13) ran when the party was registered into slot 01 and again into slot 02
 * (とうろく > ポケモンをとうろくする, はい).
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void Deck_SetSaveEntryCount(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 < func_80024ADC()) {
        switch (arg0) {                             /* irregular */
        case 16:
            gSaveSram->teams[arg1][0].count = (s16) arg2;
            break;
        case 17:
            gSaveSram->boxes[arg1][0].count = (s16) arg2;
            break;
        case 18:
            gSaveSram->items[arg1][0].count = (s16) arg2;
            break;
        case 19:
            gSaveSram->list[0].count = (s16) arg2;
            break;
        }
        func_80023F38(arg0, arg1, 2);
    }
}

M2C_UNK func_80023F38(s32, s32, M2C_UNK);           /* extern */
s32 Deck_GetSaveRecordCapacity(s32);                             /* extern */
s32 func_80024ADC();                                /* extern */

void func_80024C80(s32 arg0, s32 arg1) {
    s32 sp1C;

    sp1C = func_80024ADC();
    if (sp1C < Deck_GetSaveRecordCapacity(arg0)) {
        switch (arg0) {                             /* irregular */
        case 16:
            gSaveSram->teams[arg1][0].count = (s16) (sp1C + 1);
            break;
        case 17:
            gSaveSram->boxes[arg1][0].count = (s16) (sp1C + 1);
            break;
        case 18:
            gSaveSram->items[arg1][0].count = (s16) (sp1C + 1);
            break;
        case 19:
            gSaveSram->list[0].count = (s16) (sp1C + 1);
            break;
        }
        func_80023F38(arg0, arg1, 2);
    }
}

/** Reads a deck entry from the save data. */
s32 Deck_ReadSaveEntry(s32 arg0, s32 arg1, s32 arg2, u8* arg3) {
    s32 ret = 0;

    if (arg2 < func_80024ADC()) {
        switch (arg0) {
            case 16:
                func_80023D3C((s32)arg3, (s32)&gSaveSram->teams[arg1][0].mons[arg2]);
                break;
            case 17:
                func_80023D3C((s32)arg3, (s32)&gSaveSram->boxes[arg1][0].mons[arg2]);
                break;
            case 19:
                func_80023D3C((s32)arg3, (s32)&gSaveSram->list[0].mons[arg2]);
                break;
            case 18:
                *(SaveItemSlot*)arg3 = gSaveSram->items[arg1][0].items[arg2];
                break;
        }
        ret = 1;
    }
    return ret;
}

/** Writes a typed record to the save data, up to its capacity. */
s32 Save_WriteTypedRecord(s32 arg0, s32 arg1, s32 arg2, u8* arg3) {
    s32 ret = 0;
    s32 max = Deck_GetSaveRecordCapacity(arg0);
    s32 count = func_80024ADC(arg0, arg1);

    if ((arg2 < count) || ((arg2 == count) && (arg2 < max))) {
        switch (arg0) {
            case 16:
                BattleMon_ToGbSaveRecord((BattleMon*)arg3, &gSaveSram->teams[arg1][0].mons[arg2]);
                break;
            case 17:
                BattleMon_ToGbSaveRecord((BattleMon*)arg3, &gSaveSram->boxes[arg1][0].mons[arg2]);
                break;
            case 19:
                BattleMon_ToGbSaveRecord((BattleMon*)arg3, &gSaveSram->list[0].mons[arg2]);
                break;
            case 18:
                gSaveSram->items[arg1][0].items[arg2] = *(SaveItemSlot*)arg3;
                break;
        }
        if (arg2 == count) {
            func_80024C80(arg0, arg1);
        } else {
            func_80023F38(arg0, arg1, 2);
        }
        ret = 1;
    }
    return ret;
}

s32 func_80025100(s8 *arg0, s32 *arg1) {
    if (arg0 != NULL) {
        *arg0 = gSaveSram->options[0].towerFrames;
    }
    if (arg1 != NULL) {
        *arg1 = gSaveSram->options[0].towerButtons;
    }
    return 1;
}

M2C_UNK func_80023F38(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */

s32 func_80025130(s32 arg0) {
    gSaveSram->options[0].towerButtons = arg0;
    func_80023F38(0x14, 0, 2);
    return 1;
}

M2C_UNK func_80023F38(s32, s32, M2C_UNK);
M2C_UNK func_80023F38(M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_80025168(s8 arg0) {
    gSaveSram->options[0].towerFrames = arg0;
    func_80023F38(0x14, 0, 2);
    return 1;
}

/**
 * Returns the 16-bit progress flags at save offset 0x7A48.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 Save_GetProgressFlags(void) {
    return ((gSaveSram->options[0].progress[0] << 8) | gSaveSram->options[0].progress[1]) & 0xFFFF;
}

/**
 * Sets the progress flags at save offset 0x7A48 and writes the block.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Save_SetProgressFlags(u16 arg0) {
    gSaveSram->options[0].progress[0] = (arg0 >> 8) & 0xFF;
    gSaveSram->options[0].progress[1] = arg0 & 0xFF;
    func_80023F38(0x14, 0, 2);
}

u8 func_80025214(void) {
    return gSaveSram->options[0].soundFlags;
}

M2C_UNK func_80023F38(s32, s32, M2C_UNK);
M2C_UNK func_80023F38(M2C_UNK, M2C_UNK, M2C_UNK);
void func_80025224(s8 arg0) {
    gSaveSram->options[0].soundFlags = arg0;
    func_80023F38(0x14, 0, 2);
}

/**
 * Fills the continue block at save offset 0x7A60 with the name, session and Pokemon data.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Save_WriteContinueData(SaveContinueSession* arg0, GbSavePortSnapshot* arg1, BattleMon* arg2, s32 arg3) {
    SaveContinueRecord* f;
    s32 i;

    if (gSaveSram != NULL) {
        f = &gSaveSram->continueData[0];
        f->flags |= 3;
        f->session = *arg0;
        f->gbSnapshot = *arg1;
        f->count = arg3;
        f->rentalMask = 0;
        for (i = 0; i < arg3; i++) {
            BattleMon_ToGbSaveRecord(&arg2[i], &f->team[i]);
            if (arg2[i].species.isRental == 1) {
                f->rentalMask |= 1 << i;
            }
        }
    }
}

/**
 * Reads the continue block at save offset 0x7A60 back; returns -1 when it is empty.
 * Seen in play (2026-11-13) ran on Start at the title screen and again at the main menu (console
 * reset, then N64 logo, opening, title and main menu).
 * @unverified Name and comment guessed from the code.
 */
s16 Save_ReadContinueData(SaveContinueSession* arg0, GbSavePortSnapshot* arg1, BattleMon* arg2) {
    s16 count = -1;
    SaveContinueRecord* blk;
    s32 i;

    if (gSaveSram != NULL) {
        blk = &gSaveSram->continueData[0];
        if (blk->flags & 1) {
            *arg0 = blk->session;
            *arg1 = blk->gbSnapshot;
            count = blk->count;
            for (i = 0; i < count; i++) {
                func_80023D3C((s32)&arg2[i], (s32)&blk->team[i]);
                if (blk->rentalMask & (1 << i)) {
                    arg2[i].species.isRental = 1;
                }
            }
        }
    }
    return count;
}
