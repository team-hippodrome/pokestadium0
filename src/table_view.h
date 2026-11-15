/* Declarations for src/table_view.c. */
#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include "global.h"
#include "game_state.h"

typedef struct unk_func_88201DA0_034 {
    /* 0x0000 */ s32 unk_000;
    /* 0x0004 */ char unk004[0x4];
    /* 0x0008 */ u16 unk_008[0x640];
} unk_func_88201DA0_034; // size = 0xC88

/* A list of pointers over a caller-owned array (PointerList_Initialize, PointerList_Insert,
 * PointerList_Remove, PointerList_Sort, PointerList_Filter). Lists whose element type is known
 * have their own typed struct with the same layout. */
typedef struct PointerList {
    /* 0x00 */ void** items;
    /* 0x04 */ s32 capacity; // number of slots in items: 3 for the Free Battle rule window
    /* 0x08 */ s32 count; // number of slots in use: 3 for the Free Battle rule window
} PointerList; // size = 0xC

/* A table of fixed-size rows over a caller-owned buffer (TableView_Initialize, ByteMatrix_AppendRow,
 * ByteMatrix_InsertRow, ByteMatrix_RemoveRow, ByteMatrix_CopyRow). Also the item table of a menu
 * whose items are drawn in place (Menu_DrawInlineItems). */
typedef struct ByteMatrix {
    /* 0x00 */ u8* rows;
    /* 0x04 */ s32 capacity; // number of rows the buffer holds
    /* 0x08 */ s32 count; // number of rows in use: 3 for the Free Battle rule window's items
    /* 0x0C */ s32 rowSize; // bytes per row: 80 (sizeof BattleMon) for the せいとん box tables, 2 for the item tables
} ByteMatrix; // size = 0x10

typedef struct unk_func_8830867C_02C_0CC_000_000_000 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} unk_func_8830867C_02C_0CC_000_000_000; // size >= 0x10

typedef struct unk_func_8830867C_02C_0CC_000_000_010_000_000 {
    /* 0x00 */ struct unk_func_8830867C_02C_0CC_000_000* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ BattleMon unk_08;
} unk_func_8830867C_02C_0CC_000_000_010_000_000; // size >= 0x5C

typedef struct unk_func_8830867C_02C_0CC_000_000_010_000 {
    /* 0x00 */ unk_func_8830867C_02C_0CC_000_000_010_000_000* unk_00;
} unk_func_8830867C_02C_0CC_000_000_010_000; // size >= 0x4

typedef struct unk_func_8830867C_02C_0CC_000_000_010 {
    /* 0x00 */ unk_func_8830867C_02C_0CC_000_000_010_000* items;
    /* 0x04 */ s32 capacity;
    /* 0x08 */ s32 count;
} unk_func_8830867C_02C_0CC_000_000_010; // size = 0xC

typedef struct unk_func_8830867C_02C_0CC_000_000 {
    /* 0x00 */ unk_func_8830867C_02C_0CC_000_000_000* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ unk_func_8830867C_02C_0CC_000_000_010 unk_10;
} unk_func_8830867C_02C_0CC_000_000; // size = 0x1C

/* One Pokémon in a Lab Pokémon list (いちらん): the list's sort comparators and filters
 * (LabPCList_CompareBy*, LabPCList_FilterBy*) read the Pokémon's record at 0x08. */
typedef struct LabMonEntry {
    /* 0x00 */ unk_func_8830867C_02C_0CC_000_000* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ BattleMon mon; // @unverified: LabPCList_CompareBy* sort on its level, stats, nickname and OT
    /* 0x58 */ char unk58[0x4];
} LabMonEntry; // size = 0x5C

typedef struct LabMonEntryList {
    /* 0x00 */ LabMonEntry** items;
    /* 0x04 */ s32 capacity;
    /* 0x08 */ s32 count;
} LabMonEntryList; // size = 0xC

typedef struct unk_func_8830867C_04C_030_02C_000_000_00C {
    /* 0x00 */ s32 items;
    /* 0x04 */ s32 capacity;
    /* 0x08 */ s32 count;
} unk_func_8830867C_04C_030_02C_000_000_00C; // size >= 0xC

typedef s32 (*func_func_8002D1AC)(LabMonEntry*, s32*);

typedef s32 (*unk_D_8831A1F8)(s32, s32);

// table_view.c
void TableView_Initialize(ByteMatrix*, void*, s32, s32, s32);
s32 ByteMatrix_InsertRow(ByteMatrix*, s8*, s32);
s32 ByteMatrix_RemoveRow(ByteMatrix*, s32);
s32 WordList_Remove(unk_func_8830867C_04C_030_02C_000_000_00C*, s32);
void PointerList_Initialize(PointerList*, void**, s32, s32);
void PointerList_Insert(PointerList*, char*, s32);
void PointerList_Remove(LabMonEntryList*, s32);
void PointerList_Sort(LabMonEntryList*, unk_D_8831A1F8);
void PointerList_Filter(LabMonEntryList*, LabMonEntryList*, func_func_8002D1AC, s32*);
s32 Text_CompareGlyphCodes(u8*, u8*);

#endif // TABLE_VIEW_H
