# Stadium Zero cartridge save (SRAM)

Zero saves to 32 KiB of battery SRAM (PI domain 2 at 0x08000000). Code:
`src/save_data.c`, transfers in `Sram_TransferChunked`. Confirmed in
pj64-pokestadium-debug on 2026-11-12/13 unless a row says "code".

## Load and write

* `Save_LoadSram` reads all 0x8000 bytes once into a 'BU64' block
  (`gSaveBuffer`). `Save_LoadTypedRecordWithRepair` checks both copies of
  every record: both bad, the record is reset and written; one bad, the good
  copy is written over it. Seen: a corrupted primary team came back from its
  backup; a box with both copies corrupted came back empty.
* Every record is stored twice, back to back (primary, then backup). A
  commit writes the footer, copies primary over backup and writes both in one
  transfer of 2 × size bytes.
* GB transfers (せいとん) first write the record with the invalid footer
  (`Save_InvalidateTypedRecord`), write the Game Boy save, then commit
  (`Save_CommitPokemonRecords`). Power loss in between resets the record
  rather than duplicating Pokémon or items.
* Data is big-endian. Project64 stores the .sra with each 32-bit word
  byte-swapped.

## Record footer

The last 6 bytes of each copy: `50 4F 4B 45` ("POKE") and a u16 sum of every
byte of the copy before the sum. An invalidated copy has `58 58 58 58`
("XXXX") and the sum XOR 0xFF. The first u16 of every record is flags: bit 0
present, bit 1 dirty (always clear in a committed copy).

## Layout

| Kind | SRAM offset | Copy size | Count | Contents |
|---|---|---|---|---|
| 16 | 0x0000 + 0x250 × n | 0x128 | 16 | とうろく registered teams, 6 Pokémon |
| 17 | 0x2500 + 0xAC0 × n | 0x560 | 4 | 64のボックス 1–4, 30 Pokémon |
| 18 | 0x5000 + 0x1C0 × n | 0xE0 | 4 | 64の カセット item storage, one per trainer, 100 items |
| 19 | 0x5700 | 0x11A0 | 1 | List of 100 Pokémon. No screen using it was found; never written in play |
| 20 | 0x7A40 | 0x10 | 1 | Options, GB Tower settings, cup progress |
| 21 | 0x7A60 | 0x288 | 1 | Tournament continue data |

0x7F70–0x7FFF is unused. Backup copy = primary + copy size.

### Teams and boxes (16, 17)

| Offset | Type | Field |
|---|---|---|
| 0x00 | u16 | flags (teams: bit 0 set when registered; boxes leave it clear) |
| 0x02 | 6 bytes | trainer name, GB charset, 0x50-terminated (empty in boxes) |
| 0x08 | u16 | trainer ID |
| 0x0A | 8 bytes | second name, empty in every record seen (code) |
| 0x12 | u16 | Pokémon count |
| 0x14 | 0x2D × n | Pokémon: Gen 1 box struct (0x21), nickname (6), OT name (6) |

### Items (18)

0x00 flags, 0x02 trainer name, 0x08 trainer ID, 0x0A u16 count, 0x0C 100 ×
(item ID, quantity). The record whose name and ID match the cartridge is the
one shown.

### List (19)

0x00 flags (bit 0 set on reset), 0x02 u16 count, 0x04 100 × 0x2D Pokémon (code).

### Options (20)

| Offset | Type | Field |
|---|---|---|
| 0x02 | u8 | GB Tower picture frames unlocked, 0–2 (1 Doduo, 2 Dodrio); Z cycles them in the tower. Seen: Master Ball Cup clear 0 → 1 |
| 0x03 | u8 | bit 0 サウンド モノラル, bit 1 じっきょう なし |
| 0x04 | s32 | GB Tower コンフィグ: bits 8–15 START button, bits 0–7 SELECT button − 1. Choices 0 START, 1 L, 2 R, 3 C-Left, 4 C-Down. Seen: START → R stored 0x0200 |
| 0x08 | u8 | high byte of progress: bit 0 L50～55 tournament won (code), bit 1 マスターボールカップ won. Seen: bit 1 set by the final |
| 0x09 | u8 | L1～30 cups cleared, 0–4. A win raises it only when the cup index ≥ the count. Seen: 2 opens ハイパーボールカップ; Master Ball Cup win 0 → 1 |

### Continue data (21)

Written by ちゅうだんする at トーナメントをつづけますか？, read by
トーナメントのつづきをする？ at the main menu. Cleared (flags 0) when the
tournament is won. Seen: after the Master Ball Cup final.

| Offset | Type | Field |
|---|---|---|
| 0x002 | u8 | mode: 1 L50～55, 2 L1～30 cups. Seen: 2 |
| 0x003 | u8 | cup (0 モンスターボールカップ) |
| 0x004 | u8 | next round. Seen: 3 after two wins, resumed at バトル-3 |
| 0x005 | u8 | padding (stack garbage) |
| 0x006 | 8 bytes | opponents faced so far |
| 0x00E | s16 | Pokémon count |
| 0x010 | 6 × 0x2D | the team as Game Boy records |
| 0x11E | 0x162 bytes | snapshot of the GB save used; all zero for rentals. A GB team resumes only if the cartridge still matches |
| 0x280 | u8 | bit n: Pokémon n has BattleMon unk_01 == 1 (code) |
