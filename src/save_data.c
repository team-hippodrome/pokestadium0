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
s32 Save_GetBuffer(void);
void func_80024044(void);
void Save_ResetAndCommitTypedRecord(s32 arg0, s32 arg1);
s32 Deck_IsSaveEntryPresent(s32 arg0, s32 arg1);

s32 Save_IsTypedRecordFlagSet(s32 arg0, s32 arg1, s16 arg2);
void Save_CommitTypedRecord(s32 arg0, s32 arg1);
void Save_ClearTypedRecord(s32 arg0, s32 arg1);

/**
 * 16-bit sum of every byte of a save record except its last two (the stored sum).
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): every record in a fresh and a played save checks out with it.
 */
u16 Save_Checksum(u8* arg0, s32 arg1) {
    u16 var_v1 = 0;

    while (arg1-- > 2) {
        var_v1 += *arg0++;
    }
    return var_v1;
}

/**
 * Returns 1 if a save record ends in 'PO' 'KE' followed by Save_Checksum of the record.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): a record with one corrupted byte fails and is repaired from the other copy at boot.
 */
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

/**
 * Writes a record's 6-byte footer: 'POKE' + checksum when arg2 is set, else 'XXXX' + (checksum ^ 0xFF), which marks it invalid.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): both footers were caught being written to SRAM.
 */
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
extern s32 gSaveBuffer;
#define gSaveSram (*(SaveSram**)&gSaveBuffer)
/**
 * Repairs one copy of a save record: copies arg2 bytes from arg0 to arg1 and writes arg1 to its SRAM offset.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): after a corrupted primary team record, the boot rewrote it from its backup.
 */
void Save_CopyRecordAndWrite(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp1C = arg1 - gSaveBuffer;

    func_80058410(arg0, arg1, arg2);
    func_80003774(arg1, sp1C, arg2, 1);
}

/**
 * Commits a dirty save record (flag bit 1): clears the bit, writes the 'POKE' footer, copies the record over its
 * backup right behind it and writes both copies (2 * arg1 bytes) to SRAM in one transfer.
 * Callers such as Save_CommitTypedRecord pass a third argument that this function ignores, so the prototype is
 * left unspecified and the definition is K&R. The unused pad[2] only reproduces the retail stack frame.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): registering a team wrote 0x250 bytes at SRAM 0x0000, a 64 box 0xAC0 bytes at 0x2500.
 */
void Save_CommitRecord(arg0, arg1)
    s32 arg0;
    s32 arg1;
{
    UNUSED s32 pad[2];
    s32 offset;
    s16 flags = *(s16*)arg0;

    if (flags & 2) {
        offset = arg0 - gSaveBuffer;
        *(s16*)arg0 = flags & 0xFFFD;
        Save_WriteFooter((u8*)arg0, arg1, 1);
        func_80058410(arg0, arg0 + arg1, arg1);
        func_80003774(arg0, offset, arg1 * 2, 1);
    }
}

/**
 * Writes a dirty save record and its backup to SRAM with the 'XXXX' footer, so both copies read as invalid.
 * Used while a Pokémon or item transfer to or from the Game Boy cartridge is in progress: if the power goes off
 * before Save_CommitRecord runs, the next boot resets the record instead of keeping a duplicate. The dirty bit stays set.
 * A third argument passed by Save_InvalidateTypedRecord is ignored (K&R definition); pad[2] reproduces the frame.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): moving a Pokémon into 64のボックス1 wrote 'XXXX' first, then 'POKE' once the GB save was written.
 */
void Save_InvalidateRecord(arg0, arg1)
    s32 arg0;
    s32 arg1;
{
    UNUSED s32 pad[2];
    s32 offset;

    if (*(s16*)arg0 & 2) {
        offset = arg0 - gSaveBuffer;
        Save_WriteFooter((u8*)arg0, arg1, 0);
        func_80058410(arg0, arg0 + arg1, arg1);
        func_80003774(arg0, offset, arg1 * 2, 1);
    }
}

M2C_UNK func_80058410(s32, s32, s32);               /**
 * Copies a save record's backup copy (at arg0 + arg1) back over the primary copy, undoing unsaved edits.
 * @unverified Read from the code.
 */
void Save_RevertRecordFromBackup(s32 arg0, s32 arg1) {
    func_80058410(arg0 + arg1, arg0, arg1);
}


M2C_UNK func_8004FD20();                            /**
 * Zeroes a save record (bzero with the caller's a0/a1 still in place) and marks it dirty.
 * The size argument passed by Save_ClearTypedRecord is used only through that register.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): つづきのデータをけす wrote the continue record back as zeroes with a valid footer.
 */
void Save_ClearRecord(arg0)
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
/**
 * Validates both copies of save record (arg0 kind, arg1 slot) after the SRAM read. Both bad: the record is reset
 * and committed. Only one good: it is copied over the bad one and written back. Both good: nothing is done.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): a corrupted primary team record came back from its backup, a box with both copies corrupted came back empty.
 */
void Save_LoadTypedRecordWithRepair(s32 arg0, s32 arg1) {
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
            Save_CopyRecordAndWrite(primary, backup, size);
            break;
        case 2:
            Save_CopyRecordAndWrite(backup, primary, size);
            break;
    }
}

extern s32 gSaveBufferLoaded;
extern s32 gSaveBuffer;

/**
 * Free callback of the 'BU64' block that holds the SRAM image: clears gSaveBuffer and gSaveBufferLoaded.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): gSaveBuffer is 0 on the title screen and filled again on the next load.
 */
void Save_OnBufferFreed(s32 arg0, s32 arg1) {
    if (arg1 == 0x42553634) {
        gSaveBufferLoaded = 0;
        gSaveBuffer = 0;
    }
}

s32 func_8000234C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *); /* extern */
M2C_UNK func_80003774(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
void Save_LoadTypedRecordWithRepair(s32, s32);
M2C_UNK func_8004FD20(s32, M2C_UNK);                /**
 * Loads the 32 KiB SRAM image into a new 'BU64' block once (gSaveBufferLoaded) and validates or repairs every record.
 * Returns whether the image is loaded.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): the image sits at gSaveBuffer while menus are open; a blank SRAM is formatted on first boot.
 */
s32 Save_LoadSram(void)
{
  s32 temp_v0;
  int new_var; // FAKE: permuter temp
  s32 var_s0;
  s32 var_s0_2;
  if ((*((s32 *) (&gSaveBufferLoaded))) == 0)
  {
 do { temp_v0 = func_8000234C(0x8000, 0, 0x42553634, &(*((s8 *) (&Save_OnBufferFreed)))); *((s32 *) (&gSaveBuffer)) = temp_v0; } while (0);  // FAKE
    if (temp_v0 != 0)
    {
      *((s32 *) (&gSaveBufferLoaded)) = 1;
      new_var = 0;
      func_8004FD20(temp_v0, 0x8000);
      func_80003774(*((s32 *) (&gSaveBuffer)), 0, 0x8000, 0);
      var_s0 = new_var;
      do
      {
        Save_LoadTypedRecordWithRepair(0x10, var_s0);
        var_s0 += 1;
      }
      while (var_s0 < 0x10);
      var_s0_2 = 0;
      do
      {
        Save_LoadTypedRecordWithRepair(0x11, var_s0_2);
        Save_LoadTypedRecordWithRepair(0x12, var_s0_2);
        var_s0_2 += 1;
      }
      while (var_s0_2 != 4);
      Save_LoadTypedRecordWithRepair(0x13, new_var);
      Save_LoadTypedRecordWithRepair(0x14, 0);
      Save_LoadTypedRecordWithRepair(0x15, new_var);
    }
  }
  return *((s32 *) (&gSaveBufferLoaded));
}

/**
 * Returns the address of the SRAM image (gSaveBuffer).
 * @unverified Read from the code; no caller was found.
 */
s32 Save_GetBuffer(void) {
    return gSaveBuffer;
}

M2C_UNK func_8001FB10(s32, s32);                    /* extern */
M2C_UNK func_8001FE84();                            /* extern */
M2C_UNK func_800203FC(s32);                         /* extern */
M2C_UNK func_80058410(s32, s32, M2C_UNK);           /* extern */

/**
 * Unpacks a 0x2D-byte Game Boy save record (box struct, nickname at +0x21, OT name at +0x27) into the BattleMon at arg0.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): registered and boxed Pokémon came back with their names and stats.
 */
void BattleMon_FromGbSaveRecord(s32 arg0, s32 arg1) {
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
 * Returns whether any of the flag bits arg2 are set on save record (arg0 kind, arg1 slot).
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): the registration list showed exactly the slots with bit 0 set.
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

/**
 * ORs arg2 into the flag halfword of save record (arg0 kind, arg1 slot). Bit 0 = present, bit 1 = dirty.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): the items record went from flags 0 to 3 before its commit and was stored as 1.
 */
M2C_UNK Save_SetTypedRecordFlags(arg0, arg1, arg2)
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

void Save_CommitRecord(); // Called with two or three arguments.
/**
 * Commits save record (arg0 kind 16-21, arg1 slot) to SRAM if it is dirty (Save_CommitRecord).
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): options, team, box, item and continue records were each written through it.
 */
void Save_CommitTypedRecord(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16:
        Save_CommitRecord((s32)gSaveSram->teams[arg1], 0x128, arg1);
        return;
    case 17:
        Save_CommitRecord((s32)gSaveSram->boxes[arg1], 0x560, arg1);
        return;
    case 18:
        Save_CommitRecord((s32)gSaveSram->items[arg1], 0xE0, arg1);
        return;
    case 19:
        Save_CommitRecord((s32)gSaveSram->list, 0x11A0, arg1);
        return;
    case 20:
        Save_CommitRecord((s32)gSaveSram->options, 0x10, arg1);
        return;
    case 21:
        Save_CommitRecord((s32)gSaveSram->continueData, 0x288, arg1);
        /* fallthrough */
    default:
        return;
    }
}

void Save_InvalidateRecord(); // Called with three arguments; the third is ignored.
/**
 * Writes save record (arg0 kind, arg1 slot) to SRAM marked invalid while a Game Boy transfer is open (Save_InvalidateRecord).
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): the 'XXXX' write before a 64 box and an item record were committed.
 */
void Save_InvalidateTypedRecord(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16:
        Save_InvalidateRecord((s32)gSaveSram->teams[arg1], 0x128, arg1);
        return;
    case 17:
        Save_InvalidateRecord((s32)gSaveSram->boxes[arg1], 0x560, arg1);
        return;
    case 18:
        Save_InvalidateRecord((s32)gSaveSram->items[arg1], 0xE0, arg1);
        return;
    case 19:
        Save_InvalidateRecord((s32)gSaveSram->list, 0x11A0, arg1);
        return;
    case 20:
        Save_InvalidateRecord((s32)gSaveSram->options, 0x10, arg1);
        return;
    case 21:
        Save_InvalidateRecord((s32)gSaveSram->continueData, 0x288, arg1);
        /* fallthrough */
    default:
        return;
    }
}

/**
 * Restores save record (arg0 kind, arg1 slot) from its backup copy, dropping unsaved edits.
 * @unverified Read from the code.
 */
void Save_RevertTypedRecord(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16:
        Save_RevertRecordFromBackup((s32)gSaveSram->teams[arg1], 0x128);
        break;
    case 17:
        Save_RevertRecordFromBackup((s32)gSaveSram->boxes[arg1], 0x560);
        break;
    case 18:
        Save_RevertRecordFromBackup((s32)gSaveSram->items[arg1], 0xE0);
        break;
    case 19:
        Save_RevertRecordFromBackup((s32)gSaveSram->list, 0x11A0);
        break;
    case 20:
        Save_RevertRecordFromBackup((s32)gSaveSram->options, 0x10);
        break;
    case 21:
        Save_RevertRecordFromBackup((s32)gSaveSram->continueData, 0x288);
        break;
    }
}

/**
 * Commits every dirty team, 64 box and item record and the 100-Pokémon list (kinds 16 to 19).
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): it ran after the GB save was written when leaving せいとん with レポートしてやめる.
 */
void Save_CommitPokemonRecords(void) {
    s32 i;

    for (i = 0; i < 0x2500; i += 0x250) {
        Save_CommitRecord(*(s32*)&gSaveBuffer + i, 0x128);
    }
    for (i = 0; i < 0x2B00; i += 0xAC0) {
        Save_CommitRecord(*(s32*)&gSaveBuffer + i + 0x2500, 0x560);
    }
    for (i = 0; i < 0x700; i += 0x1C0) {
        Save_CommitRecord(*(s32*)&gSaveBuffer + i + 0x5000, 0xE0);
    }
    Save_CommitRecord(*(s32*)&gSaveBuffer + 0x5700, 0x11A0);
}

/**
 * Zeroes save record (arg0 kind, arg1 slot) and marks it dirty; names are set to the 0x50 terminator and kinds 19
 * and 20 are marked present.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): a blank SRAM comes up with exactly these contents in every record.
 */
void Save_ClearTypedRecord(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16: {
        SaveTeamRecord* rec = &gSaveSram->teams[arg1][0];
        Save_ClearRecord(&rec->flags, 0x128);
        rec->trainerName[0] = 0x50;
        rec->secondName[0] = 0x50;
        break;
    }
    case 17: {
        SaveBoxRecord* rec = &gSaveSram->boxes[arg1][0];
        Save_ClearRecord(&rec->flags, 0x560);
        rec->trainerName[0] = 0x50;
        rec->secondName[0] = 0x50;
        break;
    }
    case 18: {
        SaveItemRecord* rec = &gSaveSram->items[arg1][0];
        Save_ClearRecord(&rec->flags, 0xE0);
        rec->trainerName[0] = 0x50;
        break;
    }
    case 19: {
        s16* rec = &gSaveSram->list[0].flags;
        Save_ClearRecord(rec, 0x11A0);
        *rec |= 1;
        break;
    }
    case 20: {
        s16* rec = &gSaveSram->options[0].flags;
        Save_ClearRecord(rec, 0x10);
        *rec |= 1;
        break;
    }
    case 21:
        Save_ClearRecord(&gSaveSram->continueData[0].flags, 0x288);
        break;
    }
}

/**
 * Clears save record (arg0 kind, arg1 slot) and commits it.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): つづきのデータをけす reset the continue record this way.
 */
void Save_ResetAndCommitTypedRecord(s32 arg0, s32 arg1) {
    Save_ClearTypedRecord(arg0, arg1);
    Save_CommitTypedRecord(arg0, arg1);
}

/**
 * Entries per save record kind: 6 Pokémon per team, 30 per 64 box, 100 items per item record, 100 in the kind 19 list.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): 64のボックス shows 00/30 and 64の カセット items 000/100.
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
 * Size of one entry as the deck code copies it: 80 bytes for a BattleMon (kinds 16, 17, 19), 2 for an item (kind 18).
 * @unverified Read from the code.
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

/**
 * Returns whether save record (arg0 kind, arg1 slot) is marked present (flag bit 0).
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): registered team slots and the item record of the current trainer.
 */
s32 Deck_IsSaveEntryPresent(s32 arg0, s32 arg1) {
    return Save_IsTypedRecordFlagSet(arg0, arg1, 1);
}

s32 func_800246A8(s32, s32);
/**
 * Trainer ID stored at +0x08 of a team, box or item record, or -1 when the record is not present.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): IDNo/04660 under a registered team.
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
/**
 * Copies the trainer name at +0x02 of a team, box or item record into arg2; returns its length.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): なまえ サトシ under a registered team.
 */
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
/**
 * Copies the second name field at +0x0A of a team or box record into arg2. It was empty in every record written in play.
 * @unverified Read from the code.
 */
s32 Deck_GetSaveEntrySecondName(s32 arg0, s32 arg1, u8* arg2) {
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

/**
 * Sets the trainer ID (+0x08, when arg4 is not negative), name (+0x02 from arg3) and second name (+0x0A from arg2) of a
 * team, box or item record, then marks it present and dirty.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): the item record got サトシ and ID 0x1234 when the first item was moved in.
 */
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
            Save_SetTypedRecordFlags(arg0, arg1, 3);
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
            Save_SetTypedRecordFlags(arg0, arg1, 3);
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
            Save_SetTypedRecordFlags(arg0, arg1, 3);
            break;
        }
    }
}

/* Old-style definition: callers pass their own args through (see below). */
s32 Deck_GetSaveEntryCount(arg0, arg1) s32 arg0; s32 arg1; {
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

M2C_UNK Save_SetTypedRecordFlags(s32, s32, M2C_UNK);           /* extern */
s32 Deck_GetSaveEntryCount();                                /* extern */

/**
 * Sets the entry count of a save record when arg2 is below the current count, and marks it dirty.
 * @unverified Read from the code.
 */
void Deck_SetSaveEntryCount(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 < Deck_GetSaveEntryCount()) {
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
        Save_SetTypedRecordFlags(arg0, arg1, 2);
    }
}

M2C_UNK Save_SetTypedRecordFlags(s32, s32, M2C_UNK);           /* extern */
s32 Deck_GetSaveRecordCapacity(s32);                             /* extern */
s32 Deck_GetSaveEntryCount();                                /**
 * Adds one to a save record's entry count when it is below the kind's capacity, and marks it dirty.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): the 64 box count went from 0 to 1 when ハナ was moved in.
 */
void Deck_IncrementSaveEntryCount(s32 arg0, s32 arg1) {
    s32 sp1C;

    sp1C = Deck_GetSaveEntryCount();
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
        Save_SetTypedRecordFlags(arg0, arg1, 2);
    }
}

/**
 * Reads entry arg2 of save record (arg0 kind, arg1 slot) into arg3: a 0x2D-byte Game Boy record unpacked to a BattleMon,
 * or the 2-byte item pair. Returns 0 when arg2 is past the count.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): registered and boxed Pokémon came back with their nicknames and stats.
 */
s32 Deck_ReadSaveEntry(s32 arg0, s32 arg1, s32 arg2, u8* arg3) {
    s32 ret = 0;

    if (arg2 < Deck_GetSaveEntryCount()) {
        switch (arg0) {
            case 16:
                BattleMon_FromGbSaveRecord((s32)arg3, (s32)&gSaveSram->teams[arg1][0].mons[arg2]);
                break;
            case 17:
                BattleMon_FromGbSaveRecord((s32)arg3, (s32)&gSaveSram->boxes[arg1][0].mons[arg2]);
                break;
            case 19:
                BattleMon_FromGbSaveRecord((s32)arg3, (s32)&gSaveSram->list[0].mons[arg2]);
                break;
            case 18:
                *(SaveItemSlot*)arg3 = gSaveSram->items[arg1][0].items[arg2];
                break;
        }
        ret = 1;
    }
    return ret;
}

/**
 * Writes entry arg2 of save record (arg0 kind, arg1 slot) from arg3, appending when arg2 equals the count.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): the bytes of a registered team match the GB party it came from.
 */
s32 Save_WriteTypedRecord(s32 arg0, s32 arg1, s32 arg2, u8* arg3) {
    s32 ret = 0;
    s32 max = Deck_GetSaveRecordCapacity(arg0);
    s32 count = Deck_GetSaveEntryCount(arg0, arg1);

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
            Deck_IncrementSaveEntryCount(arg0, arg1);
        } else {
            Save_SetTypedRecordFlags(arg0, arg1, 2);
        }
        ret = 1;
    }
    return ret;
}

/**
 * Reads the GB Tower settings from the options record: picture frames unlocked (+0x02, s8) and button config (+0x04, s32).
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): the button config set in the GB Tower menu came back the next time the tower started.
 */
s32 Save_GetGbTowerSettings(s8 *arg0, s32 *arg1) {
    if (arg0 != NULL) {
        *arg0 = gSaveSram->options[0].towerFrames;
    }
    if (arg1 != NULL) {
        *arg1 = gSaveSram->options[0].towerButtons;
    }
    return 1;
}

M2C_UNK Save_SetTypedRecordFlags(M2C_UNK, M2C_UNK, M2C_UNK);   /**
 * Stores the GB Tower button config at +0x04 of the options record: high byte = START choice, low byte = SELECT choice - 1
 * (choices 0 START, 1 L, 2 R, 3 C-Left, 4 C-Down).
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): START → R in コンフィグ stored 0x0200.
 */
s32 Save_SetGbTowerButtonConfig(s32 arg0) {
    gSaveSram->options[0].towerButtons = arg0;
    Save_SetTypedRecordFlags(0x14, 0, 2);
    return 1;
}

M2C_UNK Save_SetTypedRecordFlags(s32, s32, M2C_UNK);
M2C_UNK Save_SetTypedRecordFlags(M2C_UNK, M2C_UNK, M2C_UNK);
/**
 * Stores how many extra GB Tower picture frames are unlocked (+0x02 of the options record, 0 to 2). Z cycles the frame around the
 * Game Boy screen in the tower: 1 adds the Doduo frame, 2 the Dodrio frame.
 * Seen in play (2026-11-13, docs/annotation/n64-save-format.md): clearing マスターボールカップ raised it from 0 to 1; with 2 set, Z cycled
 * green, Doduo and Dodrio frames.
 */
s32 Save_SetGbTowerFrameTier(s8 arg0) {
    gSaveSram->options[0].towerFrames = arg0;
    Save_SetTypedRecordFlags(0x14, 0, 2);
    return 1;
}

/**
 * Returns the tournament progress halfword (options record +0x08, big-endian). Low byte: L1～30 cups cleared (0-4).
 * High byte: bit 0 L50～55 tournament won, bit 1 マスターボールカップ won.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): setting the low byte to 2 opened ハイパーボールカップ with ball marks on the first two cups.
 */
s32 Save_GetProgressFlags(void) {
    return ((gSaveSram->options[0].progress[0] << 8) | gSaveSram->options[0].progress[1]) & 0xFFFF;
}

/**
 * Stores the tournament progress halfword and marks the options record dirty.
 * @unverified Read from the code; no cup was cleared in play.
 */
void Save_SetProgressFlags(u16 arg0) {
    gSaveSram->options[0].progress[0] = (arg0 >> 8) & 0xFF;
    gSaveSram->options[0].progress[1] = arg0 & 0xFF;
    Save_SetTypedRecordFlags(0x14, 0, 2);
}

/**
 * Returns the option flags at +0x03 of the options record: bit 0 サウンド モノラル, bit 1 じっきょう なし.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): モノラル and なし stored 0x03.
 */
u8 Save_GetOptionFlags(void) {
    return gSaveSram->options[0].soundFlags;
}

M2C_UNK Save_SetTypedRecordFlags(s32, s32, M2C_UNK);
M2C_UNK Save_SetTypedRecordFlags(M2C_UNK, M2C_UNK, M2C_UNK);
/**
 * Stores the option flags at +0x03 of the options record and marks it dirty.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): leaving オプション with おわり wrote the 0x20-byte options record pair.
 */
void Save_SetOptionFlags(s8 arg0) {
    gSaveSram->options[0].soundFlags = arg0;
    Save_SetTypedRecordFlags(0x14, 0, 2);
}

/**
 * Fills the tournament continue record: mode, cup, next round and opponents (+0x02), Pokémon count (+0x0E), the six
 * Pokémon as Game Boy records (+0x10), the GB save snapshot (+0x11E) and a mask of Pokémon flagged in unk_01 (+0x280).
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): ちゅうだんする after round 2 of モンスターボールカップ stored mode 2, cup 0, round 3.
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
 * Reads the tournament continue record back; returns the Pokémon count, or -1 when the record is not present.
 * Seen in play (2026-11-12, docs/annotation/n64-save-format.md): つづきをする resumed at バトル-3 with the saved team.
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
                BattleMon_FromGbSaveRecord((s32)&arg2[i], (s32)&blk->team[i]);
                if (blk->rentalMask & (1 << i)) {
                    arg2[i].species.isRental = 1;
                }
            }
        }
    }
    return count;
}
