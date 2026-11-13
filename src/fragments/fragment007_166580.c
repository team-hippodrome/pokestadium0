/* Stadium Zero fragment007_166580. */

#include "global.h"
#include "m2c_macros.h"

/* Unprototyped on purpose: different callers in this file pass one or two arguments. */
s32 Menu_UpdateCursor();
M2C_UNK GridMenu_UpdateCursor();
s32 Menu_UpdateCursorSkipDisabled();
void FreeBattle_SetScreenState(s32, s32, s32);

/**
 * FreeBattle_ClearIndices
 *
 * Stores -1 into arg2 consecutive words of the s32 array arg0, starting at
 * index arg1 (indices arg1 .. arg1 + arg2 - 1). Does nothing when
 * arg1 + arg2 <= arg1, i.e. when arg2 is not positive. The compare is signed.
 * What the -1 entries mean is not established from this function.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * @unverified Name guessed from the code; comment kept.
 */
void FreeBattle_ClearIndices(s32* arg0, s32 arg1, s32 arg2) {
    s32 end;

    end = arg1 + arg2;
    for (; arg1 < end; arg1++) {
        arg0[arg1] = -1;
    }
}

typedef struct Entry82000058 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x50];
} Entry82000058; // size = 0x54
s32 func_80020AFC(s32, s32, s32, s32);
s32 func_80020CE4(void*, s32, s32);
void func_80020C60(s32);
void func_800207F8(u8*);
extern u8 D_80065D00[];

/**
 * Reads up to six Pokemon from deck (`arg0`, `arg1`, `arg2`) into `entry` and returns the count.
 * Seen in play (2026-11-13) ran once as the entry screen opened, which then listed the GB party
 * (フシ, ヒト, カメ at L10).
 */
s32 FreeBattle_ReadTeam(s32 arg0, s32 arg1, s32 arg2, Entry82000058* entry) {
    s32 handle = func_80020AFC(arg0, arg1, arg2, 0);
    s32 i;
    u8* row;
    s32 idx;

    for (i = 0; i < 6; i++, entry++) {
        if (func_80020CE4(entry->unk_04, 1, handle) == 0) {
            break;
        }
        if ((entry->unk_04[0] > 0) && (entry->unk_04[0] < 0x98)) {
            func_800207F8(entry->unk_04);
            idx = entry->unk_04[0] - 1;
            row = &D_80065D00[idx * 0x17];
            entry->unk_04[6] = row[6];
            entry->unk_04[7] = row[7];
            entry->unk_00 = 0;
        }
    }
    func_80020C60(handle);
    return i;
}

/* One of six 0x54-byte slots; only the leading in-use flag word is known. */
typedef struct {
    /* 0x00 */ s32 flag;
    /* 0x04 */ char unk04[0x50];
} Slot54;

/**
 * FreeBattle_MarkEmptySlots
 *
 * Sets the first word (flag) to 1 in each of the slots arg1 .. 5 of an array
 * of six 0x54-byte slots starting at arg0 (nothing happens when arg1 >= 6).
 * The retail code unrolls the loop by four.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * @unverified Name guessed from the code; comment kept.
 */
void FreeBattle_MarkEmptySlots(Slot54* arg0, s32 arg1) {
    s32 i;

    arg0 += arg1;
    for (i = arg1; i < 6; i++) {
        arg0->flag = 1;
        arg0++;
    }
}

/*
 * FreeBattle_FindFlaggedSlot
 *
 * Scans the six 0x54-byte slots starting at arg0 from slot 5 down to slot 0.
 * Stores in *arg1 how many have a non-zero first word (flag) and returns the
 * lowest-numbered such slot, or NULL when none is set.
 */
/**
 * Scans a team's six slots from last to first and returns the first slot with a nonzero flag,
 * storing how many slots are flagged in *count.
 * Seen in play: runs when A picks a team on 「エントリーポケモンのせんたく」.
 * @unverified Name from the code.
 */
Slot54* FreeBattle_FindFlaggedSlot(Slot54* arg0, s32* arg1) {
    Slot54* found = NULL;
    s32 count = 0;

    arg0 += 5;

    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    arg0--;
    if (arg0->flag != 0) {
        found = arg0;
        count++;
    }
    *arg1 = count;
    return found;
}

#include "fragments/fragment007_166580_types_2.h"

/**
 * Returns 1 when no three of the six Pokemon have levels summing to 155 or less (the さいていレベル warning). The running sum keeps the levels of earlier `j` iterations, so later trios are overestimated.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
s32 FreeBattle_AllTriosOverLevelLimit(Mon82000258* mons) {
    s32 i;
    s32 j;
    s32 k;
    s32 sum;

    for (i = 0; i < 4; i++) {
        sum = mons[i].level;
        for (j = i + 1; j < 5; j++) {
            sum += mons[j].level;
            for (k = j + 1; k < 6; k++) {
                if (mons[k].level + sum < 156) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

typedef struct {
    /* 0x000 */ u8 type;
    /* 0x001 */ u8 unk_01;
    /* 0x002 */ u8 unk_02;
    /* 0x003 */ u8 unk_03;
    /* 0x004 */ char unk04[0x210];
} Record214;

typedef struct {
    /* 0x00 */ Record214* records;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 count;
} RecordList;

/* Header (0x1C bytes) followed by six 0x54-byte slots (see Slot54). */
typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk08[0x10];
    /* 0x18 */ s32 slotCount;
    /* 0x1C */ Slot54 slots[6];
} SlotList;

s32 func_80021894(s32);
s32 GbSave_GetTrainerId(s32 arg0);
s32 func_80022D84(s32, void*);
s32 func_800246A8(s32, s32);
s32 Deck_GetSaveEntryTrainerId(s32, s32);
s32 Deck_GetSaveEntryName(s32 arg0, s32 arg1, u8* arg2);

/**
 * Reads the party of each Game Boy cartridge in the four Transfer Paks into the team list.
 * Seen in play: runs when the entry screen opens (no Transfer Pak, so no Game Boy teams were
 * added).
 */
void FreeBattle_LoadGbTeams(RecordList* arg0) {
    SlotList* rec = (SlotList*)arg0->records;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_80021894(i) == 0) {
            continue;
        }
        rec->unk_00 = 0;
        rec->unk_01 = 0x20;
        rec->unk_02 = i;
        rec->unk_03 = 0;
        FreeBattle_MarkEmptySlots(rec->slots, FreeBattle_ReadTeam(rec->unk_01, rec->unk_02, rec->unk_03, (Entry82000058*)rec->slots));
        rec->slotCount = 6;
        rec->unk_04 = GbSave_GetTrainerId(rec->unk_02);
        func_80022D84(rec->unk_02, rec->unk08);
        rec++;
    }

    for (i = 0; i < 0x10; i++) {
        if (func_800246A8(0x10, i) == 0) {
            continue;
        }
        rec->unk_00 = 0;
        rec->unk_01 = 0x10;
        rec->unk_02 = 0;
        rec->unk_03 = i;
        FreeBattle_MarkEmptySlots(rec->slots, FreeBattle_ReadTeam(rec->unk_01, rec->unk_02, rec->unk_03, (Entry82000058*)rec->slots));
        rec->slotCount = 6;
        rec->unk_04 = Deck_GetSaveEntryTrainerId(rec->unk_01, rec->unk_03);
        Deck_GetSaveEntryName(rec->unk_01, rec->unk_03, rec->unk08);
        rec++;
    }

    arg0->count = rec - (SlotList*)arg0->records;
}

/**
 * FreeBattle_AddRentalEntry
 *
 * Appends an empty record to a list of 0x214-byte records: initializes the
 * header of the record at index `count` (type byte = 2, the next three bytes
 * = 0), then sets `count` to the index of the following record, computed as a
 * pointer difference from the start of the list.
 * Seen in play: under L50～55 rules the entry list opens with one 「レンタルポケモン」 row, and this runs.
 */
void FreeBattle_AddRentalEntry(RecordList* arg0) {
    Record214* rec;

    rec = &arg0->records[arg0->count];
    rec->type = 2;
    rec->unk_01 = 0;
    rec->unk_02 = 0;
    rec->unk_03 = 0;
    rec++;
    arg0->count = rec - arg0->records;
}

typedef struct Src82000594Entry { s32 data[0x14]; } Src82000594Entry;
typedef struct Src82000594 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ char unk04[0x8];
    /* 0x0C */ s32 name;
    /* 0x10 */ Src82000594Entry entries[6];
} Src82000594; // size = 0x1F0
typedef struct Slot82000594 { s32 flag; Src82000594Entry data; } Slot82000594;
typedef struct Rec82000594 {
    u8 type; u8 unk_01; u8 unk_02; s8 index; s32 unk_04; char name[0x10]; s32 slotCount;
    Slot82000594 slots[6];
} Rec82000594;
typedef struct List82000594 { Rec82000594* records; s32 unk04; s32 count; } List82000594;
extern Src82000594* D_8200AD04;
void func_8000A460(char*, void*);
void* func_80001B10(s32);
/**
 * Appends the 8 preset teams in D_8200AD04 (type 4, six Pokemon each, named via func_80001B10) to
 * the entry list.
 * Seen in play: runs when the 「エントリーポケモンのせんたく」 screen opens; the list shows the preset trainers
 * (なまえ ガール, むしとり, リかけい, …).
 * @unverified The count of 8 is from the code; only three rows fit on screen.
 */
void FreeBattle_AddPresetTeams(List82000594* arg0) {
    s32 i;
    s32 j;
    Rec82000594* rec;

    rec = &arg0->records[arg0->count];
    for (i = 0; i < 8; i++) {
        rec->type = 4;
        rec->unk_01 = 0;
        rec->unk_02 = 0;
        rec->index = i;
        rec->unk_04 = D_8200AD04[i].unk_02;
        func_8000A460(rec->name, func_80001B10(D_8200AD04[i].name));
        rec->slotCount = 6;
        for (j = 0; j < 6; j++) {
            rec->slots[j].flag = 0;
            rec->slots[j].data = D_8200AD04[i].entries[j];
        }
        rec++;
    }
    arg0->count = rec - arg0->records;
}

/**
 * FreeBattle_BuildTeamPointers
 *
 * Builds a table of pointers into a block of equally sized records.
 * arg1 holds the address of the first record at +0x00 and the record count
 * at +0x08.  arg0 holds the address of the pointer table at +0x00; entry i
 * is set to (first record + i * 0x214), so each record is 0x214 bytes.
 * The count is then copied to arg0 + 0x08.  What the records are is not
 * known from the code alone.
 *
 * Registration_BuildTeamPointers is the same routine with a record size of 0x220.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * @unverified Name guessed from the code; comment kept.
 */
void FreeBattle_BuildTeamPointers(s32* arg0, s32* arg1) {
    s32 value = arg1[0];
    s32* out = (s32*)arg0[0];
    s32 i = 0;

    if (arg1[2] > 0) {
        do {
            *out = value;
            i += 1;
            value += 0x214;
            out += 1;
        } while (i < arg1[2]);
    }
    arg0[2] = arg1[2];
}

char* HAL_Strcpy(char*, char*);
extern s32 D_82008F84;

/**
 * FreeBattle_InitNamedTeam
 *
 * Initializes a slot-list object: sets its four header bytes to 1, 0, 0, 0
 * and the word at +0x04 to 0; copies the string D_82008F84[arg1] (a table of string
 * pointers) into the buffer at +0x08 with HAL_Strcpy; clears the flag word of all six slots and then
 * sets them all with FreeBattle_MarkEmptySlots(slots, 0) (so the explicit clear is
 * overwritten); finally stores slotCount = 6.
 * Seen in play: A on the rental row starts a new team named 「なまえ 1P」 and runs this.
 */
void FreeBattle_InitNamedTeam(SlotList* arg0, s32 arg1) {
    s32 i;

    arg0->unk_00 = 1;
    arg0->unk_01 = 0;
    arg0->unk_02 = 0;
    arg0->unk_03 = 0;
    arg0->unk_04 = 0;
    HAL_Strcpy(arg0->unk08, ((char**)&D_82008F84)[arg1]);
    for (i = 0; i < 6; i++) {
        arg0->slots[i].flag = 0;
    }
    FreeBattle_MarkEmptySlots(arg0->slots, 0);
    arg0->slotCount = 6;
}

extern s32 D_800603C0;
void Window_SetRect(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern Color_RGBA8 D_8200902C;
extern char D_82009B80[];
extern char D_82009B88[];
extern s32 D_8200AC4C;
void Window_InitLabeled(s8*, s32, s32, s32, Color_RGBA8, char*);
void func_8000B2F4(s32);

/**
 * Initializes the object arg0 (size and layout not established); a sibling of
 * FreeBattle_InitLevelSumWarning. Calls Window_SetRect(arg0, arg1, arg2, 0x1AE, 0x124), clears the
 * words at 0x20, 0x24 and 0x28 and sets the word at 0x14 to 0x1001. Calls
 * Window_InitLabeled twice, on the sub-objects at arg0 + 0x2C (string D_82009B80)
 * and arg0 + 0x68 (string D_82009B88), both with width 0x48 and color
 * D_8200902C and positions derived from the words at 0 and 4. Then sets the
 * words at 0x58, 0x60, 0xAC and 0xA8 to 0xA, 0xC, 2 and 0, stores D_800603C0
 * and then arg5 in the word at 0xA4 (calling func_8000B2F4 with each), stores
 * arg4 at 0xB4 and arg3 at 0xB0, and clears D_8200AC4C.
 * What the object is and what the constants mean is not established.
 * Seen in play: A on a rental Pokemon opens its status window with 「レンタルしますか？ はい いいえ」 and runs
 * this.
 */
void FreeBattle_InitConfirmWindow(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Window_SetRect(arg0, arg1, arg2, 0x1AE, 0x124);
    M2C_FIELD(arg0, s32*, 0x24) = 0;
    M2C_FIELD(arg0, s32*, 0x20) = 0;
    M2C_FIELD(arg0, s32*, 0x28) = 0;
    M2C_FIELD(arg0, s32*, 0x14) = 0x1001;
    Window_InitLabeled(arg0 + 0x2C, M2C_FIELD(arg0, s32*, 0) + 0x10A, M2C_FIELD(arg0, s32*, 4) + 0x100, 0x48, D_8200902C, D_82009B80);
    M2C_FIELD(arg0, s32*, 0x58) = 0xA;
    M2C_FIELD(arg0, s32*, 0x60) = 0xC;
    Window_InitLabeled(arg0 + 0x68, M2C_FIELD(arg0, s32*, 0) + 0x15A, M2C_FIELD(arg0, s32*, 4) + 0x100, 0x48, D_8200902C, D_82009B88);
    M2C_FIELD(arg0, s32*, 0xAC) = 2;
    M2C_FIELD(arg0, s32*, 0xA8) = 0;
    M2C_FIELD(arg0, s32*, 0xA4) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(arg0, s32*, 0xA4) = arg5;
    func_8000B2F4(arg5);
    M2C_FIELD(arg0, s32*, 0xB4) = arg4;
    M2C_FIELD(arg0, s32*, 0xB0) = arg3;
    D_8200AC4C = 0;
}

typedef struct Color82000BC4 {
    u8 r, g, b, a;
} Color82000BC4;
typedef struct Entry80066AD8 {
    const char* str;
    Color82000BC4 color;
} Entry80066AD8;
extern Entry80066AD8 D_80066AD8[];
s32 Pokemon_GetTypeIndex(s32, s32);
void func_8001AB6C(void);
void func_8001A384(s32, s32);
void func_8001ABBC(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A944(s32, s32, const char*, ...);

typedef struct Entry8006A9D4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 type;
    /* 0x04 */ const char* name;
    /* 0x08 */ s32 unk_08;
} Entry8006A9D4; // size = 0xC
extern Entry8006A9D4 D_8006A9D4[];
extern M2C_UNK D_800734A8;
extern char D_82009B90[];
u32 func_800566BC(const char*);

/**
 * Draws a move name in its type's color (D_80066AD8 by D_8006A9D4[move].type), centered if asked;
 * move -2 draws the no-move string.
 * Seen in play: the rental status window lists the four moves on the C buttons in type colors
 * (メガドレイン and ソーラービーム green, どくどく purple, ねむりごな green).
 */
void FreeBattle_DrawMoveName(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Entry8006A9D4* entry;
    const char* str;
    Color82000BC4* c;

    func_8001A384(8, 0);
    if (arg2 == -2) {
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        str = D_82009B90;
    } else {
        entry = &D_8006A9D4[arg2];
        c = &D_80066AD8[entry->type].color;
        func_8001AA9C(c->r, c->g, c->b, c->a);
        str = entry->name;
    }
    if (arg3 != 0) {
        arg0 = arg0 - (func_800566BC(str) >> 1) * 20 + 0x8C;
    }
    func_8001A944(arg0, arg1, str);
}


/**
 * Draws the colored type icon for type slot `arg3` of Pokemon `arg2`.
 * Seen in play: draws タイプ1/タイプ2 (くさ, どく) in the rental status window.
 */
void FreeBattle_DrawTypeName(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Color82000BC4 c;
    s32 idx = Pokemon_GetTypeIndex(arg2, arg3);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(8, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        func_8001A944(arg0, arg1, D_80066AD8[idx].str);
        func_8001ABBC();
    }
}

typedef struct Color82001CCC {
    u8 c[4];
} Color82001CCC;
typedef struct Mon82000C5C {
    /* 0x00 */ char unk00[0x24];
    /* 0x24 */ u8 level;
    /* 0x25 */ char unk25[1];
    /* 0x26 */ u16 maxHp;
    /* 0x28 */ u16 attack;
    /* 0x2A */ u16 defense;
    /* 0x2C */ u16 speed;
    /* 0x2E */ u16 special;
    /* 0x30 */ char nickname[1];
} Mon82000C5C;
typedef struct Screen82000C5C {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 w;
    /* 0x0C */ char unk0C[0x20];
    /* 0x2C */ char button1[0x3C];
    /* 0x68 */ char button2[0x40];
    /* 0xA8 */ s32 selection;
    /* 0xAC */ char unkAC[4];
    /* 0xB0 */ Mon82000C5C* mon;
    /* 0xB4 */ char* title;
} Screen82000C5C;
typedef struct Slot82000C5C {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 centered;
    /* 0x0C */ s32 iconX;
    /* 0x10 */ s32 icon;
} Slot82000C5C; // size = 0x14
extern Slot82000C5C D_82009040[];
extern u8 D_8007356C[];
extern Gfx D_80060270[];
extern Gfx D_80060290[];
extern Gfx D_80060398[];
extern Color82001CCC D_82009030;
extern Color82001CCC D_82009034;
extern Color82001CCC D_82008F54;
extern Color_RGBA8 D_82009038;
extern Color_RGBA8 D_8200903C;
extern char D_82009BA0[];
extern char D_82009BA4[];
extern char D_82009BA8[];
extern char D_82009BAC[];
extern char D_82009BB0[];
extern char D_82009BBC[];
extern char D_82009BC8[];
extern char D_82009BD4[];
extern char D_82009BE0[];
extern char D_82009BEC[];
extern char D_82009BF8[];
extern char D_82009BFC[];
extern char D_82009C00[];
extern char D_82009C04[];
extern s32 D_8200AC48;
void BgStage_DrawFrame(void);
void func_80019008(s32, Mon82000C5C*, s32);
u8* func_800196F8(s32);
void func_8001AAE4(u8, u8, u8, u8);
void func_8001ABE8(void);
void func_8001AC3C(void);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
void func_80029028(s32, s32, s32, s32, Color82001CCC);
void Ui_DrawTexturedDivider(s32, s32, s32, u8*);
void Ui_FillRectPrimEnvColor(s32, s32, s32, s32, Color_RGBA8, Color_RGBA8);
s32 func_8002AE6C(Screen82000C5C*);
void Window_DrawLabeled(char*, s32);
s32 BattleMon_CountMoves(u8* arg0);
s32 BattleMon_GetMoveIndex(Mon82000C5C*, s32);
/**
 * Draws a Pokemon's status window: LV, HP, Type 1/2, Attack, Defense, Speed, Special.
 * Seen in play: draws the rental status window (name, LV 50, HP, タイプ1/タイプ2, こうげき/ぼうぎょ/すばやさ/とくしゅ,
 * and four moves).
 */
void FreeBattle_DrawMonStatusWindow(Screen82000C5C* arg0) {
    s32 y = arg0->y + 6;
    s32 x = arg0->x + 6;
    s32 count = BattleMon_CountMoves(arg0->mon);
    s32 i;
    s32 n;
    s32 row;
    u8* tex;

    if (func_8002AE6C(arg0) == 0) {
        Ui_DrawTexturedDivider(arg0->x, arg0->y + 0xF3, arg0->w, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(x, y, arg0->w - 0xC, 0x20, D_82009030);
        func_80029028(x + 0x78, y + 0x20, arg0->w - 0x84, 0x78, D_82009034);
        func_80029028(x, y + 0xF4, arg0->w - 0xC, 0x24, D_82008F54);
        Ui_FillRectPrimEnvColor(x, y + 0x98, arg0->w - 0xC, 0x56, D_82009038, D_8200903C);
        func_8001AB6C();
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        func_8001A384(8, 0);
        func_8001A944(arg0->x + 0xE, arg0->y + 0x102, arg0->title);
        func_8001ABBC();
        func_8001AB6C();
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001A384(8, 0);
        func_8001ABE8();
        func_8001AAE4(0x7F, 0xA8, 0xFF, 0xFF);
        func_8001A944(x + 0xA, y + 5, arg0->mon->nickname);
        func_8001AC3C();
        func_8001A384(4, -1);
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        func_8001A944(x + 0x84, y + 9, D_82009BA0);
        func_8001A944(x + 0x112, y + 9, D_82009BA4);
        func_8001A384(8, 0);
        func_8001A944(x + 0xB2, y + 5, D_82009BA8, arg0->mon->level);
        func_8001A944(x + 0x140, y + 5, D_82009BAC, arg0->mon->maxHp);
        func_8001A944(x + 0x88, y + 0x28, D_82009BB0);
        if (Pokemon_GetTypeIndex((s32)arg0->mon, 1) != -1) {
            func_8001A944(x + 0x88, y + 0x64, D_82009BBC);
        }
        func_8001A944(x + 0x102, y + 0x28, D_82009BC8);
        func_8001A944(x + 0x102, y + 0x44, D_82009BD4);
        func_8001A944(x + 0x102, y + 0x60, D_82009BE0);
        func_8001A944(x + 0x102, y + 0x7C, D_82009BEC);
        func_8001A944(x + 0x15C, y + 0x28, D_82009BF8, arg0->mon->attack);
        func_8001A944(x + 0x15C, y + 0x44, D_82009BFC, arg0->mon->defense);
        func_8001A944(x + 0x15C, y + 0x60, D_82009C00, arg0->mon->speed);
        func_8001A944(x + 0x15C, y + 0x7C, D_82009C04, arg0->mon->special);
        for (i = 0; i < count; i++) {
            FreeBattle_DrawMoveName(D_82009040[i].x + x, D_82009040[i].y + y, BattleMon_GetMoveIndex(arg0->mon, i), D_82009040[i].centered);
        }
        func_8001ABBC();
        FreeBattle_DrawTypeName(x + 0x9C, y + 0x40, (s32)arg0->mon, 0);
        FreeBattle_DrawTypeName(x + 0x9C, y + 0x7C, (s32)arg0->mon, 1);
        gSPDisplayList(gDisplayListHead++, D_80060290);
        for (i = 0; i < count; i++) {
            func_8001B884(D_82009040[i].iconX + x, D_82009040[i].y + y, 0x14, 0x14, (u8*)D_82009040[i].icon, 0x14, 0x200000);
        }
        gSPDisplayList(gDisplayListHead++, D_80060398);
        Window_DrawLabeled(arg0->button1, (arg0->selection == 0) ? 2 : 0);
        Window_DrawLabeled(arg0->button2, (arg0->selection == 1) ? 2 : 0);
        if (D_8200AC4C == 0) {
            D_8200AC4C = 1;
            func_80019008(D_8200AC48, arg0->mon, 0x416D);
        }
        tex = func_800196F8(D_8200AC48);
        BgStage_DrawFrame();
        gSPDisplayList(gDisplayListHead++, D_80060290);
        gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
        for (row = 0; row < 0x78; row += n) {
            if (0x78 - row < 0x10) {
                n = 0x78 - row;
            } else {
                n = 0x10;
            }
            func_8001B884(x, y + row + 0x20, 0x78, n, tex, 0x80, 0x200000);
            tex += n << 8;
        }
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
}

s32 func_8002B390(s32);
s32 func_8002BC14(s32);
M2C_UNK func_8003F6AC(M2C_UNK);

/**
 * Runs the はい/いいえ choice of 「レンタルしますか？」: returns 1 for はい, -1 for いいえ or B (with the cancel
 * sound), 0 while undecided.
 * Seen in play: runs while the rental status window asks 「レンタルしますか？」.
 */
s32 FreeBattle_UpdateRentalConfirmChoice(s8* arg0) {
    s32 ret = 0;
    s32 temp_v0;

    if (func_8002B390(arg0 + 0xA4) == 0) {
        temp_v0 = func_8002BC14(M2C_FIELD(arg0, s32*, 0xA4));
        if (temp_v0 == -1) {
            func_8003F6AC(3);
            ret = -1;
        } else if (temp_v0 == 1) {
            switch (M2C_FIELD(arg0, s32*, 0xA8)) {
                case 1:
                    func_8003F6AC(3);
                    ret = -1;
                    break;
                default:
                    ret = 1;
                    break;
            }
        }
    }
    return ret;
}

typedef struct {
    /* 0x00 */ u8 id;
    /* 0x01 */ char unk01[0x4F];
} Record50;

typedef struct {
    /* 0x00 */ Record50* records;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ s32 count;
} RecordTable;

typedef struct {
    /* 0x00 */ RecordTable* table;
    /* 0x04 */ u16* flags;
} FlagOwner;

void Menu_ClearItemFlags(FlagOwner*);

/**
 * Clears the rental grid's item flags, then flags (0x101) every rental Pokemon already in the
 * team being built, except the one in slot arg2.
 * Seen in play: runs when the L50～55 rental grid 「レンタルポケモン」 opens.
 * @unverified The flagged look was not checked on screen.
 */
void FreeBattle_MarkPickedRentals(FlagOwner* arg0, Slot54* arg1, s32 arg2) {
    Record50* records;
    Record50* rec;
    s32 i;
    s32 count;
    s32 slot;
    Slot54* p;

    records = arg0->table->records;
    Menu_ClearItemFlags(arg0);
    slot = 0;
    p = arg1;
    for (; slot != 0x1F8; slot += 0x54, p++) {
        if ((p->flag == 0) && (arg2 != M2C_FIELD(p, u8*, 4))) {
            i = 0;
            rec = records;
            count = arg0->table->count;
            if (count > 0) {
                do {
                    if (rec->id == M2C_FIELD(p, u8*, 4)) {
                        arg0->flags[i] |= 0x101;
                        count = arg0->table->count;
                    }
                    i++;
                    rec++;
                } while (i < count);
            }
        }
    }
}

typedef struct Mon8200140C {
    /* 0x00 */ s32 flags;
    /* 0x04 */ u8 species;
    /* 0x05 */ char unk05[0x28 - 0x5];
    /* 0x28 */ u8 level;
    /* 0x29 */ char unk29[0x54 - 0x29];
} Mon8200140C; // size = 0x54
typedef struct Team8200140C {
    /* 0x000 */ char unk000[0x1C];
    /* 0x01C */ Mon8200140C mons[6];
    /* 0x214 */
} Team8200140C; // size = 0x214
typedef struct TeamList8200140C {
    /* 0x0 */ Team8200140C* teams;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 count;
} TeamList8200140C;
typedef struct Species8200140C {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ u8 flags;
    /* 0x0D */ char unk0D[0xF];
} Species8200140C; // size = 0x1C
extern Species8200140C D_80064C5C[];
/**
 * Flags Pokemon the chosen rule forbids: 0x20 for an invalid species, 2 when L50～55 rules fail
 * (not allowed or level outside 50 to 55) or Free Battle's 40 usable species exclude it, 4 when
 * L1～30 rules fail.
 * Seen in play: runs when the entry screen opens after picking フリーバトル (「つかえるポケモンは 40しゅるい」).
 * @unverified Rule details from the code.
 */
void FreeBattle_MarkIneligibleMons(TeamList8200140C *arg0, s32 arg1) {
    s32 i;
    s32 j;
    Team8200140C* team = arg0->teams;
    Mon8200140C* mon;

    for (i = 0; i < arg0->count; i++, team++) {
        for (mon = team->mons, j = 0; j < 6; j++, mon++) {
            if (mon->flags & 1) {
                continue;
            }
            if ((mon->species <= 0) || (mon->species >= 0x98)) {
                mon->flags |= 0x20;
            } else if (arg1 == 1) {
                if (!(D_80064C5C[mon->species - 1].flags & 1) || (mon->level < 50) || (mon->level >= 56)) {
                    mon->flags |= 2;
                }
            } else if (arg1 == 2) {
                if (!(D_80064C5C[mon->species - 1].flags & 2) || (mon->level <= 0) || (mon->level >= 31)) {
                    mon->flags |= 4;
                }
            } else if (!(D_80064C5C[mon->species - 1].flags & 1)) {
                mon->flags |= 2;
            }
        }
    }
}

typedef struct Slot82001558 {
    /* 0x00 */ s32 flags;
    /* 0x04 */ u8 species;
    /* 0x05 */ char unk05[0x4F];
} Slot82001558; // size = 0x54

/**
 * Counts the picked Pokemon that share a species with another pick and stores the first index.
 * Seen in play (2026-11-13) ran on the entry screen while rentals were picked (Free Battle, L1-30
 * rules, six L30 rentals vs COM).
 * @unverified Name and comment guessed from the code.
 */
s32 FreeBattle_CountDuplicateSpecies(void* arg0, s32* index) {
    Slot82001558* slots = arg0;
    s32 count = 0;
    s32 i;
    s32 j;
    u8 species;
    Slot82001558* cur;

    for (i = 0, cur = slots; i < 5; i++, cur++) {
        if (cur->flags & 0x3F) {
            continue;
        }
        species = cur->species;
        for (j = i + 1; j < 6; j++) {
            if (!(slots[j].flags & 0x3F) && (species == slots[j].species)) {
                slots[j].flags |= 0x40;
                count++;
            }
        }
        if (count > 0) {
            cur->flags |= 0x40;
            *index = i;
            return count + 1;
        }
    }
    return 0;
}

/**
 * Walks the six Slot54 entries at arg0. For each entry whose flag word has
 * bit 0x40 set, clears that bit, and then sets bit 0x10 unless the entry's
 * index equals arg1 (so only the entry arg1 is left without 0x10).
 * The meaning of the flag bits is not yet established.
 */
void func_82001708(Slot54* arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (!(arg0[i].flag & 0x40)) {
        } else {
            arg0[i].flag &= ~0x40;
            if (i != arg1) {
                arg0[i].flag |= 0x10;
            }
        }
    }
}

extern Gfx D_80060270[];
void func_80029028(s32, s32, s32, s32, Color82001CCC);
extern Color82001CCC D_82008F5C;
extern Color82001CCC D_82008F58;

typedef struct IconCache82001810 {
    /* 0x00 */ s32* slots;
    /* 0x04 */ s32 base;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 start;
} IconCache82001810; // size = 0x10
extern s32 D_8200AC50;
extern Gfx D_80073450[];
extern Gfx D_80073408[];
extern Gfx D_80073438[];
extern u8 D_04011A60[];
extern u8 D_05000AA0[];
extern u8 D_05000478[];
void func_8001AB6C(void);
void func_8001ABBC(void);
void func_8001A384(s32, s32);
void Font_SetColorForFlags(s32);
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color82001CCC);
void func_8001BCB4(s32, s32, s32, s32, void*, s32, s32);
void Ui_DrawNumberUnpadded(s32, s32, u8);
void func_8001833C(s32, s32, s32*, u16);
s32 PokeIcon_GetImage(s8 *arg0, s32 arg1);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws one Pokemon cell of a team row: nickname, level and icon.
 * Seen in play: draws each Pokemon cell of a team row (icon, nickname, L20).
 */
void FreeBattle_DrawMonCell(s32 x, s32 y, s32* entry, s32 frame, s32 flags, s32 arg5) {
    IconCache82001810* cache = (IconCache82001810*)arg5;
    s32 pad[2]; // FAKE
    s32 key;
    s32 idx;
    s32 pad2; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 0x84, 0x32, D_82008F58);
    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 0x7E, 0x2C, D_82008F58);
    }
    if (entry != NULL) {
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(4, 0);
        func_8001A944(x + 4, y + 4, (char*)entry + 0x30);
        func_8001ABBC();
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(x + 0x2C, y + 0x19, 8, 0xA, D_04011A60, 8, 0);
        Ui_DrawNumberUnpadded(x + 0x38, y + 0x17, ((u8*)entry)[0x24]);
        key = cache->start + frame;
        idx = cache->base + key % cache->count;
        if (key != cache->slots[idx]) {
            cache->slots[idx] = key;
            func_8001833C(D_8200AC50, idx, entry, ((D_82008F58.c[1] << 3) & 0x7C0) | ((D_82008F58.c[2] >> 2) & 0x3E) | ((D_82008F58.c[0] << 8) & 0xF800) | 1);
        }
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(x + 0x56, y + 6, 0x28, 0x28, PokeIcon_GetImage(D_8200AC50, idx), 0x28, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
        if (flags & 0x800) {
            gSPDisplayList(gDisplayListHead++, D_80073408);
            func_8001B884(x + 4, y + 0x14, 0x1C, 0x1C, D_05000AA0, 0x1C, 0x200000);
            gSPDisplayList(gDisplayListHead++, D_80073438);
        }
        if (flags & 0x200) {
            gSPDisplayList(gDisplayListHead++, D_80073408);
            func_8001B884(x + 4, y + 0x14, 0x1C, 0x1C, D_05000478, 0x1C, 0x200000);
            gSPDisplayList(gDisplayListHead++, D_80073438);
        }
    }
}


void FreeBattle_DrawMonCell(s32, s32, s32*, s32, s32, s32);

/**
 * Draws a team slot's Pokemon cell, or an empty cell when the slot is empty.
 * Seen in play: draws each Pokemon cell of the picked team's window.
 */
void FreeBattle_DrawSlotCell(s32 arg0, s32 arg1, s32* arg2, s32 arg3, s32 arg4, s32 arg5) {
    FreeBattle_DrawMonCell(arg0, arg1, (*arg2 & 1) ? NULL : arg2 + 1, arg3, arg4, arg5);
}

/**
 * FreeBattle_FillTrainerPanel
 *
 * Emits the display list D_80060270, then fills a 0x88 by 0x64 rectangle at
 * (arg0, arg1) with the color in arg2 using func_80029028
 * (Trade_DrawSolidFillRect).
 * Seen in play: fills each team row's trainer panel (portrait, 「なまえ ガール」, IDNo/15235).
 */
void FreeBattle_FillTrainerPanel(s32 arg0, s32 arg1, Color82001CCC arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x88, 0x64, arg2);
}

/**
 * FreeBattle_FillTeamPanel
 *
 * Emits the display list D_80060270, then fills a 0x18C by 0x64 rectangle at
 * (arg0 + 0x88, arg1) with the color in arg2 using func_80029028
 * (Trade_DrawSolidFillRect).
 * Seen in play (2026-11-13) ran while the tournament entry screen showed the GB party row (フシ, ヒト,
 * カメ, L10).
 */
void FreeBattle_FillTeamPanel(s32 arg0, s32 arg1, Color82001CCC arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0 + 0x88, arg1, 0x18C, 0x64, arg2);
}

/**
 * Draws the top and bottom border lines of a team row.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * @unverified Name and comment guessed from the code.
 */
void FreeBattle_DrawRowBorders(s32 arg0, s32 arg1, Color82001CCC arg2) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(arg0, arg1, 0x214, 1, arg2);
    func_80029028(arg0, arg1 + 0x63, 0x214, 1, arg2);
}

extern char D_82009C08[];
void func_8001AAE4(u8, u8, u8, u8);
void Font_SetLineHeight(s32 arg0);
void func_8001ABE8(void);
void func_8001AC3C(void);

/**
 * FreeBattle_DrawRentalPrompt
 *
 * Draws a filled rectangle with FreeBattle_FillTeamPanel using the color D_82008F58,
 * then switches the font to translucent, two-cycle text rendering (white
 * environment color, font set mask 0x20, Font_SetLineHeight(0x2A), prim color
 * 255/100/255/255) and prints the string D_82009C08 at
 * (arg0 + 0xAE, arg1 + 0xE) before ending text rendering. arg2 is not used.
 * Seen in play: draws 「レンタルポケモンから 6たいえらぶ」 in the rental entry row.
 */
void FreeBattle_DrawRentalPrompt(s32 arg0, s32 arg1, s32 arg2) {
    FreeBattle_FillTeamPanel(arg0, arg1, D_82008F58);
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8001A384(0x20, 0);
    Font_SetLineHeight(0x2A);
    func_8001ABE8();
    func_8001AAE4(0xFF, 0x64, 0xFF, 0xFF);
    func_8001A944(arg0 + 0xAE, arg1 + 0xE, D_82009C08);
    func_8001AC3C();
    func_8001ABBC();
}

typedef struct Img82001E20 {
    /* 0x00 */ s32 stride;
    /* 0x04 */ s32 height;
    /* 0x08 */ s32 width;
    /* 0x0C */ u8* pixels;
} Img82001E20;
typedef struct Slot82001E20 {
    /* 0x00 */ u8 flags;
    /* 0x01 */ u8 kind;
    /* 0x02 */ u8 species;
    /* 0x03 */ u8 index;
    /* 0x04 */ s32 value;
    /* 0x08 */ char name[1];
} Slot82001E20;
extern Img82001E20 D_82008F64;
extern u8* D_8200AD08[];
extern char D_82009C2C[];
extern char D_82009C34[];
extern char D_82009C48[];
extern u8 D_04010918[];
extern Gfx D_80073450[];
u8 GbSave_GetPortGame(s32 arg0);
void Font_SetColorForFlags(s32);
void Ui_DrawImageInStrips(Img82001E20*, s32, s32);
void Ui_DrawNumberZeroPadded(s32, s32, s32, s32);
void func_8002BC58(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void*, s32, s32);
/**
 * Draws the レンタルポケモン (Rental Pokemon) list with its なまえ (Name) header.
 * Seen in play (2026-11-13) ran while the entry screen showed the rental teams (ガール and むしとり rows
 * with なまえ headers).
 */
void FreeBattle_DrawRentalNameList(s32 arg0, s32 arg1, s32 arg2, Slot82001E20* arg3) {
    s32 pad[3]; // FAKE
    Img82001E20 img;

    FreeBattle_FillTrainerPanel(arg0, arg1, D_82008F5C);
    if (arg3->flags == 0) {
        if (arg3->kind == 0x20) {
            func_8002BC58(arg0 + 5, arg1 + 4, arg3->species, GbSave_GetPortGame(arg3->species));
        } else if (arg3->kind == 0x10) {
            Ui_DrawImageInStrips(&D_82008F64, arg0 + 4, arg1 + 4);
            func_8001AB6C();
            Font_SetColorForFlags(arg2);
            func_8001A384(8, 0);
            func_8001A944(arg0 + 0x1B, arg1 + 0x1A, D_82009C2C, arg3->index + 1);
            func_8001ABBC();
        }
    } else if (arg3->flags & 4) {
        img.width = img.height = img.stride = 0x40;
        img.pixels = D_8200AD08[arg3->index];
        Ui_DrawImageInStrips(&img, arg0 + 0x16, arg1 + 2);
    }
    if (arg3->flags & 2) {
        func_8001AB6C();
        Font_SetColorForFlags(arg2);
        func_8001A384(4, 0);
        func_8001A944(arg0 + 4, arg1 + 0x41, D_82009C34);
        func_8001ABBC();
        return;
    }
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xC8, 0xC8, 0xFF);
    func_8001A384(4, -1);
    func_8001A944(arg0 + 4, arg1 + 0x41, D_82009C48);
    Font_SetColorForFlags(arg2);
    func_8001A384(4, 0);
    func_8001A944(arg0 + 0x38, arg1 + 0x41, arg3->name);
    func_8001ABBC();
    if (arg3->value != 0) {
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(arg0 + 0x25, arg1 + 0x56, 0x28, 0xA, D_04010918, 0x28, 0);
        Ui_DrawNumberZeroPadded(arg0 + 0x51, arg1 + 0x54, arg3->value, 5);
    }
}

typedef struct MenuDef820020EC {
    /* 0x00 */ s32* items;
    /* 0x04 */ s32 count;
    /* 0x08 */ s32 itemCount;
    /* 0x0C */ s32 itemSize;
} MenuDef820020EC;
extern s32 D_8200AC58[];
extern Color82001CCC D_82008F60;
extern u8* D_82008F74[];
extern Gfx D_80073408[];
extern Gfx D_80073438[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws a full team row: trainer panel and six Pokemon cells.
 * Seen in play: draws each team row on 「エントリーポケモンのせんたく」.
 */
void FreeBattle_DrawTeamRow(s32 arg0, s32 arg1, SlotList *arg2, s32 arg3, s32 arg4, SlotList **arg5)
{
  SlotList **new_var; // FAKE: permuter temp
  s32 hl;
  s32 *name;
  s32 i;
  s32 pad[1]; // FAKE
  MenuDef820020EC def;
  SlotList *list = arg2; // FAKE: alias kept in s6 for loop bound
  if (arg2 != 0)
  {
    FreeBattle_DrawRentalNameList(arg0, arg1, arg4, (Slot82001E20 *) arg2);
    new_var = arg5;
    if (arg2->unk_00 & 2)
    {
      FreeBattle_DrawRentalPrompt(arg0, arg1, arg4);
    }
    else
    {
      def.items = D_8200AC58;
      def.count = 0;
      def.itemCount = 0x18;
      def.itemSize = arg3 * 6;
      i = 0;
      if (arg2->slotCount > 0)
      {
        do
        {
          hl = 0;
          name = 0;
          if (!(list->slots[i].flag & 1))
          {
            name = ((s32 *) (&arg2->slots[i])) + 1;
            if (list->slots[i].flag & 0x26)
            {
              hl = 0x200;
            }
          }
          FreeBattle_DrawMonCell((arg0 + 0x88) + ((i % 3) * 0x84), ((i / 3) * 0x32) + arg1, name, i, hl, (s32) (&def));
          i++;
        } while (i < list->slotCount);
      }

    }
    for (i = 0; i != 4; i++)
    {
      if (arg2 == new_var[i])
      {
        {
          Gfx *_g = (Gfx *) (gDisplayListHead++);
          _g->words.w1 = (unsigned int) D_80073408; // FAKE: hand-expanded gbi macro
          _g->words.w0 = (((unsigned int) ((((unsigned int) 0xde) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0x00) & ((0x01 << 8) - 1)) << 16))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 16) - 1)) << 0)); // FAKE: hand-expanded gbi macro
        }
        ;
        func_8001B884(arg0 + 0x60, (arg1 + 5) + (i * 0xE), 0x28, 0xE, D_82008F74[i], 0x28, 0x200000);
        {
          Gfx *_g = (Gfx *) (gDisplayListHead++);
          _g->words.w1 = (unsigned int) D_80073438; // FAKE: hand-expanded gbi macro
          _g->words.w0 = (((unsigned int) ((((unsigned int) 0xde) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0x00) & ((0x01 << 8) - 1)) << 16))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 16) - 1)) << 0)); // FAKE: hand-expanded gbi macro
        }
        ;
      }
    }

  }
  else
  {
    FreeBattle_FillTrainerPanel(arg0, arg1, D_82008F5C);
    FreeBattle_FillTeamPanel(arg0, arg1, D_82008F58);
  }
  FreeBattle_DrawRowBorders(arg0, arg1, D_82008F60);
}

typedef struct {
    /* 0x00 */ Slot54** slots;
    /* 0x04 */ u16* flags;
} SlotFlags;

/**
 * Sets bit 0x200 on each of the six slots whose Pokemon a rule forbids (flags 0x26) and that is
 * not empty (flag 1).
 * Seen in play: runs when A picks a team on 「エントリーポケモンのせんたく」.
 * @unverified Name from the code.
 */
void FreeBattle_MarkIneligibleSlots(SlotFlags* arg0) {
    Slot54* slots;
    s32 i;

    slots = *arg0->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flag & 1) && (slots[i].flag & 0x26)) {
            arg0->flags[i] |= 0x200;
        }
    }
}

/**
 * For each of the six Slot54 entries reached through `*arg0->slots`, sets bit
 * 0x800 in the matching u16 of `arg0->flags` when the entry's flag word has bit 0
 * clear and at least one of the bits 0x10 set.
 * The meaning of the bits is not yet established.
 */
void func_82002528(SlotFlags* arg0) {
    Slot54* slots;
    s32 i;

    slots = *arg0->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flag & 1) && (slots[i].flag & 0x10)) {
            arg0->flags[i] |= 0x800;
        }
    }
}

/**
 * For each of the six Slot54 entries reached through `*arg0->slots`, sets bit 0
 * of the matching u16 in `arg0->flags` when the entry's flag word does not have
 * bit 0x40 set. The meaning of the bits is not yet established.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void FreeBattle_DisableUnpickedRows(SlotFlags* arg0) {
    Slot54* slots;
    s32 i;

    slots = *arg0->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flag & 0x40)) {
            arg0->flags[i] |= 1;
        }
    }
}

/**
 * Counterpart of FreeBattle_DisableUnpickedRows: for each of the six Slot54 entries reached
 * through `*arg0->slots`, clears bit 0 of the matching u16 in `arg0->flags`
 * when the entry's flag word does not have bit 0x40 set.
 * The meaning of the bits is not yet established.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name guessed from the code; comment kept.
 */
void FreeBattle_EnableUnpickedRows(SlotFlags* arg0) {
    Slot54* slots;
    s32 i;

    slots = *arg0->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flag & 0x40)) {
            arg0->flags[i] &= ~1;
        }
    }
}

typedef struct MenuDef8200288C {
    /* 0x00 */ s32* items;
    /* 0x04 */ s32 count;
    /* 0x08 */ s32 itemCount;
    /* 0x0C */ s32 itemSize;
} MenuDef8200288C;
extern s32 D_8200AC58[];
extern Color82001CCC D_82008F60;
void GridMenu_DrawInlineItems(void*, s32, s32, s32, MenuDef8200288C*);
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Draws the rental Pokemon list window; `arg1` picks the cursor style.
 * Seen in play: draws the picked team's window (trainer panel and six Pokemon) under the confirm
 * prompt.
 */
void FreeBattle_DrawRentalListWindow(s8 *arg0, s32 arg1)
{
  s32 x;
  s32 y;
  s32 pad[2]; // FAKE: stack padding
  MenuDef8200288C def;
  s32 mode;
 x = (*((s32 *) (((s8 *) arg0) + 0x14))) + 6; y = (*((s32 *) (((s8 *) arg0) + 0x18))) + 6; // FAKE: decomp slop, raw pointer casts stand in for struct fields
  mode = 0xFFED;
  FreeBattle_DrawRentalNameList(x, y, 2, arg0 + 0xC8);
  def.items = D_8200AC58;
  def.count = 0;
  def.itemCount = 0x18;
  def.itemSize = (*((s32 *) (((s8 *) arg0) + 0x48))) * 6;
  switch (arg1)
  {
    case 1:
      mode = 0xFFEF;
      break;

    case 2:
      mode = 0xFFFD;
      break;

  }

  GridMenu_DrawInlineItems(arg0 + 0x2F8, x + 0x88, y, mode, &def);
  FreeBattle_DrawRowBorders(x, y, D_82008F60);
}
