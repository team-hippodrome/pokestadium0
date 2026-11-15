/* Stadium Zero fragment007_166580. */

#include "global.h"
#include "m2c_macros.h"
#include "free_battle_setup.h"

/* Unprototyped on purpose: different callers in this file pass one or two arguments. */
s32 Menu_UpdateCursor();
M2C_UNK GridMenu_UpdateCursor();
s32 Menu_UpdateCursorSkipDisabled();
void FreeBattle_SetScreenState(s32, s32, s32);

/**
 * FreeBattle_ClearIndices
 *
 * Stores -1 into count consecutive words of the s32 array indices, starting at
 * index start (indices start .. start + count - 1). Does nothing when
 * start + count <= start, i.e. when count is not positive. The compare is signed.
 * What the -1 entries mean is not established from this function.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * @unverified Name guessed from the code; comment kept.
 */
void FreeBattle_ClearIndices(s32* indices, s32 start, s32 count) {
    s32 end;

    end = start + count;
    for (; start < end; start++) {
        indices[start] = -1;
    }
}

s32 func_80020AFC(s32, s32, s32, s32);
s32 func_80020CE4(void*, s32, s32);
void func_80020C60(s32);
void func_800207F8(u8*);
extern u8 D_80065D00[];

/**
 * Reads up to six Pokemon from deck (`deckKind`, `port`, `deckIndex`) into `entry` and returns the count.
 * Seen in play (2026-11-13) ran once as the entry screen opened, which then listed the GB party
 * (フシ, ヒト, カメ at L10).
 */
s32 FreeBattle_ReadTeam(s32 deck_kind, s32 port, s32 deck_index, TeamMonSlot* entry) {
    s32 handle = func_80020AFC(deck_kind, port, deck_index, 0);
    s32 i;
    u8* row;
    s32 idx;

    for (i = 0; i < 6; i++, entry++) {
        if (func_80020CE4(&entry->mon, 1, handle) == 0) {
            break;
        }
        if ((entry->mon.species.id > 0) && (entry->mon.species.id < 0x98)) {
            func_800207F8(&entry->mon);
            idx = entry->mon.species.id - 1;
            row = &D_80065D00[idx * 0x17];
            entry->mon.type1 = row[6];
            entry->mon.type2 = row[7];
            entry->flags = 0;
        }
    }
    func_80020C60(handle);
    return i;
}


/**
 * FreeBattle_MarkEmptySlots
 *
 * Sets the first word (flag) to 1 in each of the slots start .. 5 of an array
 * of six 0x54-byte slots starting at slots (nothing happens when start >= 6).
 * The retail code unrolls the loop by four.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * Seen in play (2026-11-14): the empty slots of a rental team being built read flags 1 in RAM.
 */
void FreeBattle_MarkEmptySlots(TeamMonSlot* slots, s32 start) {
    s32 i;

    slots += start;
    for (i = start; i < 6; i++) {
        slots->flags = 1;
        slots++;
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
TeamMonSlot* FreeBattle_FindFlaggedSlot(TeamMonSlot* slots, s32* out_count) {
    TeamMonSlot* found = NULL;
    s32 count = 0;

    slots += 5;

    if (slots->flags != 0) {
        found = slots;
        count++;
    }
    slots--;
    if (slots->flags != 0) {
        found = slots;
        count++;
    }
    slots--;
    if (slots->flags != 0) {
        found = slots;
        count++;
    }
    slots--;
    if (slots->flags != 0) {
        found = slots;
        count++;
    }
    slots--;
    if (slots->flags != 0) {
        found = slots;
        count++;
    }
    slots--;
    if (slots->flags != 0) {
        found = slots;
        count++;
    }
    *out_count = count;
    return found;
}

/**
 * Returns 1 when no three of the six Pokemon have levels summing to 155 or less (the さいていレベル warning). The running sum keeps the levels of earlier `j` iterations, so later trios are overestimated.
 * Seen in play (2026-11-14): with five rentals poked to L55 and a sixth at L50 in L50～55 Battle,
 * 「さいていレベル ３びきの ごうけいが１５５をこえます。」 (the lowest three levels add up to more
 * than 155) appeared.
 */
s32 FreeBattle_AllTriosOverLevelLimit(TeamMonSlot* mons) {
    s32 i;
    s32 j;
    s32 k;
    s32 sum;

    for (i = 0; i < 4; i++) {
        sum = mons[i].mon.level;
        for (j = i + 1; j < 5; j++) {
            sum += mons[j].mon.level;
            for (k = j + 1; k < 6; k++) {
                if (mons[k].mon.level + sum < 156) {
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

/* Header (0x1C bytes) followed by six 0x54-byte slots (see TeamMonSlot). */
typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk08[0x10];
    /* 0x18 */ s32 slotCount;
    /* 0x1C */ TeamMonSlot slots[6];
} SlotList;

s32 func_80021894(s32);
s32 GbSave_GetTrainerId(s32 arg0);
s32 GbSave_GetPlayerName(s32, void*);
s32 func_800246A8(s32, s32);
s32 Deck_GetSaveEntryTrainerId(s32, s32);
s32 Deck_GetSaveEntryName(s32 arg0, s32 arg1, u8* arg2);

/**
 * Reads the party of each Game Boy cartridge in the four Transfer Paks into the team list.
 * Seen in play: runs when the entry screen opens (no Transfer Pak, so no Game Boy teams were
 * added).
 */
void FreeBattle_LoadGbTeams(RecordList* list) {
    SlotList* rec = (SlotList*)list->records;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_80021894(i) == 0) {
            continue;
        }
        rec->unk_00 = 0;
        rec->unk_01 = 0x20;
        rec->unk_02 = i;
        rec->unk_03 = 0;
        FreeBattle_MarkEmptySlots(rec->slots, FreeBattle_ReadTeam(rec->unk_01, rec->unk_02, rec->unk_03, (TeamMonSlot*)rec->slots));
        rec->slotCount = 6;
        rec->unk_04 = GbSave_GetTrainerId(rec->unk_02);
        GbSave_GetPlayerName(rec->unk_02, rec->unk08);
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
        FreeBattle_MarkEmptySlots(rec->slots, FreeBattle_ReadTeam(rec->unk_01, rec->unk_02, rec->unk_03, (TeamMonSlot*)rec->slots));
        rec->slotCount = 6;
        rec->unk_04 = Deck_GetSaveEntryTrainerId(rec->unk_01, rec->unk_03);
        Deck_GetSaveEntryName(rec->unk_01, rec->unk_03, rec->unk08);
        rec++;
    }

    list->count = rec - (SlotList*)list->records;
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
void FreeBattle_AddRentalEntry(RecordList* list) {
    Record214* rec;

    rec = &list->records[list->count];
    rec->type = 2;
    rec->unk_01 = 0;
    rec->unk_02 = 0;
    rec->unk_03 = 0;
    rec++;
    list->count = rec - list->records;
}

typedef struct Src82000594Entry { s32 data[0x14]; } Src82000594Entry;
typedef struct Src82000594 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ char unk04[0x8];
    /* 0x0C */ s32 name;
    /* 0x10 */ Src82000594Entry entries[6];
} Src82000594; // size = 0x1F0
typedef struct Slot82000594 { s32 flags; Src82000594Entry data; } Slot82000594;
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
void FreeBattle_AddPresetTeams(List82000594* list) {
    s32 i;
    s32 j;
    Rec82000594* rec;

    rec = &list->records[list->count];
    for (i = 0; i < 8; i++) {
        rec->type = 4;
        rec->unk_01 = 0;
        rec->unk_02 = 0;
        rec->index = i;
        rec->unk_04 = D_8200AD04[i].unk_02;
        func_8000A460(rec->name, func_80001B10(D_8200AD04[i].name));
        rec->slotCount = 6;
        for (j = 0; j < 6; j++) {
            rec->slots[j].flags = 0;
            rec->slots[j].data = D_8200AD04[i].entries[j];
        }
        rec++;
    }
    list->count = rec - list->records;
}

/**
 * FreeBattle_BuildTeamPointers
 *
 * Builds a table of pointers into a block of equally sized records.
 * teams holds the address of the first record at +0x00 and the record count
 * at +0x08.  dest holds the address of the pointer table at +0x00; entry i
 * is set to (first record + i * 0x214), so each record is 0x214 bytes.
 * The count is then copied to dest + 0x08.  What the records are is not
 * known from the code alone.
 *
 * Registration_BuildTeamPointers is the same routine with a record size of 0x220.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * @unverified Name guessed from the code; comment kept.
 */
void FreeBattle_BuildTeamPointers(s32* dest, s32* teams) {
    s32 value = teams[0];
    s32* out = (s32*)dest[0];
    s32 i = 0;

    if (teams[2] > 0) {
        do {
            *out = value;
            i += 1;
            value += 0x214;
            out += 1;
        } while (i < teams[2]);
    }
    dest[2] = teams[2];
}

char* HAL_Strcpy(char*, char*);
extern s32 D_82008F84;

/**
 * FreeBattle_InitNamedTeam
 *
 * Initializes a slot-list object: sets its four header bytes to 1, 0, 0, 0
 * and the word at +0x04 to 0; copies the string D_82008F84[nameIndex] (a table of string
 * pointers) into the buffer at +0x08 with HAL_Strcpy; clears the flag word of all six slots and then
 * sets them all with FreeBattle_MarkEmptySlots(slots, 0) (so the explicit clear is
 * overwritten); finally stores slotCount = 6.
 * Seen in play: A on the rental row starts a new team named 「なまえ 1P」 and runs this.
 */
void FreeBattle_InitNamedTeam(SlotList* team, s32 name_index) {
    s32 i;

    team->unk_00 = 1;
    team->unk_01 = 0;
    team->unk_02 = 0;
    team->unk_03 = 0;
    team->unk_04 = 0;
    HAL_Strcpy(team->unk08, ((char**)&D_82008F84)[name_index]);
    for (i = 0; i < 6; i++) {
        team->slots[i].flags = 0;
    }
    FreeBattle_MarkEmptySlots(team->slots, 0);
    team->slotCount = 6;
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
 * Initializes the object window (size and layout not established); a sibling of
 * FreeBattle_InitLevelSumWarning. Calls Window_SetRect(window, x, y, 430, 292), clears the
 * words at 0x20, 0x24 and 0x28 and sets the word at 0x14 to 0x1001. Calls
 * Window_InitLabeled twice, on the sub-objects at window + 0x2C (string D_82009B80)
 * and window + 0x68 (string D_82009B88), both with width 0x48 and color
 * D_8200902C and positions derived from the words at 0 and 4. Then sets the
 * words at 0x58, 0x60, 0xAC and 0xA8 to 0xA, 0xC, 2 and 0, stores D_800603C0
 * and then controller in the word at 0xA4 (calling func_8000B2F4 with each), stores
 * prompt at 0xB4 and mon at 0xB0, and clears D_8200AC4C.
 * What the object is and what the constants mean is not established.
 * Seen in play: A on a rental Pokemon opens its status window with 「レンタルしますか？ はい いいえ」 and runs
 * this.
 */
void FreeBattle_InitConfirmWindow(s8* window, s32 x, s32 y, s32 mon, s32 prompt, s32 controller) {
    Window_SetRect(window, x, y, 430, 292);
    M2C_FIELD(window, s32*, 0x24) = 0;
    M2C_FIELD(window, s32*, 0x20) = 0;
    M2C_FIELD(window, s32*, 0x28) = 0;
    M2C_FIELD(window, s32*, 0x14) = 0x1001;
    Window_InitLabeled(window + 0x2C, M2C_FIELD(window, s32*, 0) + 266, M2C_FIELD(window, s32*, 4) + 0x100, 72, D_8200902C, D_82009B80);
    M2C_FIELD(window, s32*, 0x58) = 0xA;
    M2C_FIELD(window, s32*, 0x60) = 0xC;
    Window_InitLabeled(window + 0x68, M2C_FIELD(window, s32*, 0) + 346, M2C_FIELD(window, s32*, 4) + 0x100, 72, D_8200902C, D_82009B88);
    M2C_FIELD(window, s32*, 0xAC) = 2;
    M2C_FIELD(window, s32*, 0xA8) = 0;
    M2C_FIELD(window, s32*, 0xA4) = D_800603C0;
    func_8000B2F4(D_800603C0);
    M2C_FIELD(window, s32*, 0xA4) = controller;
    func_8000B2F4(controller);
    M2C_FIELD(window, s32*, 0xB4) = prompt;
    M2C_FIELD(window, s32*, 0xB0) = mon;
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
void Font_Printf(s32 x, s32 y, const char* fmt, ...);

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
void FreeBattle_DrawMoveName(s32 x, s32 y, s32 move, s32 centered) {
    Entry8006A9D4* entry;
    const char* str;
    Color82000BC4* c;

    func_8001A384(8, 0);
    if (move == -2) {
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        str = D_82009B90;
    } else {
        entry = &D_8006A9D4[move];
        c = &D_80066AD8[entry->type].color;
        func_8001AA9C(c->r, c->g, c->b, c->a);
        str = entry->name;
    }
    if (centered != 0) {
        x = x - (func_800566BC(str) >> 1) * 20 + 0x8C;
    }
    Font_Printf(x, y, str);
}

/**
 * Draws the colored type icon for type slot `typeSlot` of Pokemon `mon`.
 * Seen in play: draws タイプ1/タイプ2 (くさ, どく) in the rental status window.
 */
void FreeBattle_DrawTypeName(s32 x, s32 y, s32 mon, s32 type_slot) {
    Color82000BC4 c;
    s32 idx = Pokemon_GetTypeIndex(mon, type_slot);

    if (idx != -1) {
        c = D_80066AD8[idx].color;
        func_8001AB6C();
        func_8001A384(8, 0);
        func_8001AA9C(c.r, c.g, c.b, c.a);
        Font_Printf(x, y, D_80066AD8[idx].str);
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
void FreeBattle_DrawMonStatusWindow(Screen82000C5C* window) {
    s32 y = window->y + 6;
    s32 x = window->x + 6;
    s32 count = BattleMon_CountMoves(window->mon);
    s32 i;
    s32 n;
    s32 row;
    u8* tex;

    if (func_8002AE6C(window) == 0) {
        Ui_DrawTexturedDivider(window->x, window->y + 243, window->w, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(x, y, window->w - 12, 0x20, D_82009030);
        func_80029028(x + 120, y + 0x20, window->w - 132, 120, D_82009034);
        func_80029028(x, y + 244, window->w - 12, 36, D_82008F54);
        Ui_FillRectPrimEnvColor(x, y + 152, window->w - 12, 86, D_82009038, D_8200903C);
        func_8001AB6C();
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        func_8001A384(8, 0);
        Font_Printf(window->x + 14, window->y + 258, window->title);
        func_8001ABBC();
        func_8001AB6C();
        func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
        func_8001A384(8, 0);
        func_8001ABE8();
        func_8001AAE4(0x7F, 0xA8, 0xFF, 0xFF);
        Font_Printf(x + 10, y + 5, window->mon->nickname);
        func_8001AC3C();
        func_8001A384(4, -1);
        func_8001AA9C(((u8*)&D_800734A8)[0], ((u8*)&D_800734A8)[1], ((u8*)&D_800734A8)[2], ((u8*)&D_800734A8)[3]);
        Font_Printf(x + 132, y + 9, D_82009BA0);
        Font_Printf(x + 274, y + 9, D_82009BA4);
        func_8001A384(8, 0);
        Font_Printf(x + 178, y + 5, D_82009BA8, window->mon->level);
        Font_Printf(x + 320, y + 5, D_82009BAC, window->mon->maxHp);
        Font_Printf(x + 136, y + 40, D_82009BB0);
        if (Pokemon_GetTypeIndex((s32)window->mon, 1) != -1) {
            Font_Printf(x + 136, y + 100, D_82009BBC);
        }
        Font_Printf(x + 258, y + 40, D_82009BC8);
        Font_Printf(x + 258, y + 68, D_82009BD4);
        Font_Printf(x + 258, y + 96, D_82009BE0);
        Font_Printf(x + 258, y + 124, D_82009BEC);
        Font_Printf(x + 348, y + 40, D_82009BF8, window->mon->attack);
        Font_Printf(x + 348, y + 68, D_82009BFC, window->mon->defense);
        Font_Printf(x + 348, y + 96, D_82009C00, window->mon->speed);
        Font_Printf(x + 348, y + 124, D_82009C04, window->mon->special);
        for (i = 0; i < count; i++) {
            FreeBattle_DrawMoveName(D_82009040[i].x + x, D_82009040[i].y + y, BattleMon_GetMoveIndex(window->mon, i), D_82009040[i].centered);
        }
        func_8001ABBC();
        FreeBattle_DrawTypeName(x + 0x9C, y + 0x40, (s32)window->mon, 0);
        FreeBattle_DrawTypeName(x + 0x9C, y + 0x7C, (s32)window->mon, 1);
        gSPDisplayList(gDisplayListHead++, D_80060290);
        for (i = 0; i < count; i++) {
            func_8001B884(D_82009040[i].iconX + x, D_82009040[i].y + y, 20, 20, (u8*)D_82009040[i].icon, 20, 0x200000);
        }
        gSPDisplayList(gDisplayListHead++, D_80060398);
        Window_DrawLabeled(window->button1, (window->selection == 0) ? 2 : 0);
        Window_DrawLabeled(window->button2, (window->selection == 1) ? 2 : 0);
        if (D_8200AC4C == 0) {
            D_8200AC4C = 1;
            func_80019008(D_8200AC48, window->mon, 0x416D);
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
            func_8001B884(x, y + row + 0x20, 120, n, tex, 0x80, 0x200000);
            tex += n << 8;
        }
        gSPDisplayList(gDisplayListHead++, D_80060398);
    }
}

s32 func_8002B390(s32);
s32 func_8002BC14(s32);
M2C_UNK Audio_PlaySystemSound(M2C_UNK);

/**
 * Runs the はい/いいえ choice of 「レンタルしますか？」: returns 1 for はい, -1 for いいえ or B (with the cancel
 * sound), 0 while undecided.
 * Seen in play: runs while the rental status window asks 「レンタルしますか？」.
 */
s32 FreeBattle_UpdateRentalConfirmChoice(s8* window) {
    s32 ret = 0;
    s32 temp_v0;

    if (func_8002B390(window + 0xA4) == 0) {
        temp_v0 = func_8002BC14(M2C_FIELD(window, s32*, 0xA4));
        if (temp_v0 == -1) {
            Audio_PlaySystemSound(3);
            ret = -1;
        } else if (temp_v0 == 1) {
            switch (M2C_FIELD(window, s32*, 0xA8)) {
                case 1:
                    Audio_PlaySystemSound(3);
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
 * team being built, except the one in slot exceptSpecies.
 * Seen in play: runs when the L50～55 rental grid 「レンタルポケモン」 opens.
 * Seen in play (2026-11-14): rentals already in the team are drawn with blue names in the
 * 「レンタルポケモン」 grid (スピアー after it was rented).
 */
void FreeBattle_MarkPickedRentals(FlagOwner* grid, TeamMonSlot* slots, s32 except_species) {
    Record50* records;
    Record50* rec;
    s32 i;
    s32 count;
    s32 slot;
    TeamMonSlot* p;

    records = grid->table->records;
    Menu_ClearItemFlags(grid);
    slot = 0;
    p = slots;
    for (; slot != 0x1F8; slot += 0x54, p++) {
        if ((p->flags == 0) && (except_species != M2C_FIELD(p, u8*, 4))) {
            i = 0;
            rec = records;
            count = grid->table->count;
            if (count > 0) {
                do {
                    if (rec->id == M2C_FIELD(p, u8*, 4)) {
                        grid->flags[i] |= 0x101;
                        count = grid->table->count;
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
void FreeBattle_MarkIneligibleMons(TeamList8200140C *list, s32 rule_category) {
    s32 i;
    s32 j;
    Team8200140C* team = list->teams;
    Mon8200140C* mon;

    for (i = 0; i < list->count; i++, team++) {
        for (mon = team->mons, j = 0; j < 6; j++, mon++) {
            if (mon->flags & 1) {
                continue;
            }
            if ((mon->species <= 0) || (mon->species >= 0x98)) {
                mon->flags |= 0x20;
            } else if (rule_category == 1) {
                if (!(D_80064C5C[mon->species - 1].flags & 1) || (mon->level < 50) || (mon->level >= 56)) {
                    mon->flags |= 2;
                }
            } else if (rule_category == 2) {
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
 * Seen in play (2026-11-14): two スピアー in a rental team gave 「おなじポケモンが ２たいいます」.
 */
s32 FreeBattle_CountDuplicateSpecies(void* slot_array, s32* index) {
    Slot82001558* slots = slot_array;
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
 * After 「このポケモンにしますか？」 → はい on a duplicate: clears the duplicate mark (0x40) of every slot
 * and marks the duplicates other than `keep` with 0x10 (to be replaced from the rentals).
 * Seen in play (2026-11-14): with a poked second スピアー, keeping the first left the second slot's
 * flags 0x10.
 */
void FreeBattle_KeepChosenDuplicate(TeamMonSlot* slots, s32 keep) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (!(slots[i].flags & 0x40)) {
        } else {
            slots[i].flags &= ~0x40;
            if (i != keep) {
                slots[i].flags |= 0x10;
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
s32 PokeIcon_GetImage(s8 *arg0, s32 arg1);
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws one Pokemon cell of a team row: nickname, level and icon.
 * Seen in play: draws each Pokemon cell of a team row (icon, nickname, L20).
 */
void FreeBattle_DrawMonCell(s32 x, s32 y, s32* entry, s32 frame, s32 flags, s32 icon_cache) {
    IconCache82001810* cache = (IconCache82001810*)icon_cache;
    s32 pad[2]; // FAKE
    s32 key;
    s32 idx;
    s32 pad2; // FAKE

    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 132, 50, D_82008F58);
    if (flags & 0x10) {
        Ui_FillRectHighlighted(x + 3, y + 3, 126, 44, D_82008F58);
    }
    if (entry != NULL) {
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(4, 0);
        Font_Printf(x + 4, y + 4, (char*)entry + 0x30);
        func_8001ABBC();
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(x + 44, y + 25, 8, 10, D_04011A60, 8, 0);
        Ui_DrawNumberUnpadded(x + 0x38, y + 0x17, ((u8*)entry)[0x24]);
        key = cache->start + frame;
        idx = cache->base + key % cache->count;
        if (key != cache->slots[idx]) {
            cache->slots[idx] = key;
            PokeIcon_SetMonSlot((PokeIconRenderer*)D_8200AC50, idx, (BattleMon*)entry, ((D_82008F58.c[1] << 3) & 0x7C0) | ((D_82008F58.c[2] >> 2) & 0x3E) | ((D_82008F58.c[0] << 8) & 0xF800) | 1);
        }
        gSPDisplayList(gDisplayListHead++, D_80073408);
        func_8001B884(x + 86, y + 6, 40, 40, PokeIcon_GetImage(D_8200AC50, idx), 40, 0x200000);
        gSPDisplayList(gDisplayListHead++, D_80073438);
        if (flags & 0x800) {
            gSPDisplayList(gDisplayListHead++, D_80073408);
            func_8001B884(x + 4, y + 20, 28, 28, D_05000AA0, 28, 0x200000);
            gSPDisplayList(gDisplayListHead++, D_80073438);
        }
        if (flags & 0x200) {
            gSPDisplayList(gDisplayListHead++, D_80073408);
            func_8001B884(x + 4, y + 20, 28, 28, D_05000478, 28, 0x200000);
            gSPDisplayList(gDisplayListHead++, D_80073438);
        }
    }
}

void FreeBattle_DrawMonCell(s32, s32, s32*, s32, s32, s32);

/**
 * Draws a team slot's Pokemon cell, or an empty cell when the slot is empty.
 * Seen in play: draws each Pokemon cell of the picked team's window.
 */
void FreeBattle_DrawSlotCell(s32 x, s32 y, s32* slot, s32 index, s32 flags, s32 icon_cache) {
    FreeBattle_DrawMonCell(x, y, (*slot & 1) ? NULL : slot + 1, index, flags, icon_cache);
}

/**
 * FreeBattle_FillTrainerPanel
 *
 * Emits the display list D_80060270, then fills a 0x88 by 0x64 rectangle at
 * (x, y) with the color in color using func_80029028
 * (Trade_DrawSolidFillRect).
 * Seen in play: fills each team row's trainer panel (portrait, 「なまえ ガール」, IDNo/15235).
 */
void FreeBattle_FillTrainerPanel(s32 x, s32 y, Color82001CCC color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 136, 100, color);
}

/**
 * FreeBattle_FillTeamPanel
 *
 * Emits the display list D_80060270, then fills a 0x18C by 0x64 rectangle at
 * (x + 0x88, y) with the color in color using func_80029028
 * (Trade_DrawSolidFillRect).
 * Seen in play (2026-11-13) ran while the tournament entry screen showed the GB party row (フシ, ヒト,
 * カメ, L10).
 */
void FreeBattle_FillTeamPanel(s32 x, s32 y, Color82001CCC color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x + 136, y, 396, 100, color);
}

/**
 * Draws the top and bottom border lines of a team row.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in Free Battle setup.
 * @unverified Name and comment guessed from the code.
 */
void FreeBattle_DrawRowBorders(s32 x, s32 y, Color82001CCC color) {
    gSPDisplayList(gDisplayListHead++, D_80060270);
    func_80029028(x, y, 532, 1, color);
    func_80029028(x, y + 99, 532, 1, color);
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
 * environment color, font set mask 0x20, Font_SetLineHeight(42), prim color
 * 255/100/255/255) and prints the string D_82009C08 at
 * (x + 0xAE, y + 0xE) before ending text rendering. flags is not used.
 * Seen in play: draws 「レンタルポケモンから 6たいえらぶ」 in the rental entry row.
 */
void FreeBattle_DrawRentalPrompt(s32 x, s32 y, s32 flags) {
    FreeBattle_FillTeamPanel(x, y, D_82008F58);
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xFF, 0xFF, 0xFF);
    func_8001A384(0x20, 0);
    Font_SetLineHeight(42);
    func_8001ABE8();
    func_8001AAE4(0xFF, 0x64, 0xFF, 0xFF);
    Font_Printf(x + 174, y + 14, D_82009C08);
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
void GbSave_DrawCartridgeIcon(s32, s32, s32, s32);
void func_8001BCB4(s32, s32, s32, s32, void*, s32, s32);
/**
 * Draws the レンタルポケモン (Rental Pokemon) list with its なまえ (Name) header.
 * Seen in play (2026-11-13) ran while the entry screen showed the rental teams (ガール and むしとり rows
 * with なまえ headers).
 */
void FreeBattle_DrawRentalNameList(s32 x, s32 y, s32 flags, Slot82001E20* team) {
    s32 pad[3]; // FAKE
    Img82001E20 img;

    FreeBattle_FillTrainerPanel(x, y, D_82008F5C);
    if (team->flags == 0) {
        if (team->kind == 0x20) {
            GbSave_DrawCartridgeIcon(x + 5, y + 4, team->species, GbSave_GetPortGame(team->species));
        } else if (team->kind == 0x10) {
            Ui_DrawImageInStrips(&D_82008F64, x + 4, y + 4);
            func_8001AB6C();
            Font_SetColorForFlags(flags);
            func_8001A384(8, 0);
            Font_Printf(x + 27, y + 26, D_82009C2C, team->index + 1);
            func_8001ABBC();
        }
    } else if (team->flags & 4) {
        img.width = img.height = img.stride = 0x40;
        img.pixels = D_8200AD08[team->index];
        Ui_DrawImageInStrips(&img, x + 22, y + 2);
    }
    if (team->flags & 2) {
        func_8001AB6C();
        Font_SetColorForFlags(flags);
        func_8001A384(4, 0);
        Font_Printf(x + 4, y + 65, D_82009C34);
        func_8001ABBC();
        return;
    }
    func_8001AB6C();
    func_8001AA9C(0xFF, 0xC8, 0xC8, 0xFF);
    func_8001A384(4, -1);
    Font_Printf(x + 4, y + 65, D_82009C48);
    Font_SetColorForFlags(flags);
    func_8001A384(4, 0);
    Font_Printf(x + 56, y + 65, team->name);
    func_8001ABBC();
    if (team->value != 0) {
        gSPDisplayList(gDisplayListHead++, D_80073450);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        func_8001BCB4(x + 37, y + 86, 40, 10, D_04010918, 40, 0);
        Ui_DrawNumberZeroPadded(x + 81, y + 84, team->value, 5);
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
void FreeBattle_DrawTeamRow(s32 x, s32 y, SlotList *team, s32 row, s32 flags, SlotList **icon_cache)
{
  SlotList **new_var; // FAKE: permuter temp
  s32 hl;
  s32 *name;
  s32 i;
  s32 pad[1]; // FAKE
  MenuDef820020EC def;
  SlotList *list = team; // FAKE: alias kept in s6 for loop bound
  if (team != 0)
  {
    FreeBattle_DrawRentalNameList(x, y, flags, (Slot82001E20 *) team);
    new_var = icon_cache; // FAKE: permuter temp
    if (team->unk_00 & 2)
    {
      FreeBattle_DrawRentalPrompt(x, y, flags);
    }
    else
    {
      def.items = D_8200AC58;
      def.count = 0;
      def.itemCount = 0x18;
      def.itemSize = row * 6;
      i = 0;
      if (team->slotCount > 0)
      {
        do
        {
          hl = 0;
          name = 0;
          if (!(list->slots[i].flags & 1))
          {
            name = ((s32 *) (&team->slots[i])) + 1;
            if (list->slots[i].flags & 0x26)
            {
              hl = 0x200;
            }
          }
          FreeBattle_DrawMonCell((x + 0x88) + ((i % 3) * 0x84), ((i / 3) * 0x32) + y, name, i, hl, (s32) (&def));
          i++;
        } while (i < list->slotCount);
      }

    }
    for (i = 0; i != 4; i++)
    {
      if (team == new_var[i]) // FAKE: permuter temp
      {
        {
          Gfx *_g = (Gfx *) (gDisplayListHead++);
          _g->words.w1 = (unsigned int) D_80073408; // FAKE: hand-expanded gbi macro
          _g->words.w0 = (((unsigned int) ((((unsigned int) 0xde) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0x00) & ((0x01 << 8) - 1)) << 16))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 16) - 1)) << 0)); // FAKE: hand-expanded gbi macro
        }
        ;
        func_8001B884(x + 96, (y + 5) + (i * 14), 40, 14, D_82008F74[i], 40, 0x200000);
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
    FreeBattle_FillTrainerPanel(x, y, D_82008F5C);
    FreeBattle_FillTeamPanel(x, y, D_82008F58);
  }
  FreeBattle_DrawRowBorders(x, y, D_82008F60);
}

typedef struct {
    /* 0x00 */ TeamMonSlot** slots;
    /* 0x04 */ u16* flags;
} SlotFlags;

/**
 * Sets bit 0x200 on each of the six slots whose Pokemon a rule forbids (flags 0x26) and that is
 * not empty (flag 1).
 * Seen in play: runs when A picks a team on 「エントリーポケモンのせんたく」.
 * @unverified Name from the code.
 */
void FreeBattle_MarkIneligibleSlots(SlotFlags* rows) {
    TeamMonSlot* slots;
    s32 i;

    slots = *rows->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flags & 1) && (slots[i].flags & 0x26)) {
            rows->flags[i] |= 0x200;
        }
    }
}

/**
 * Sets row flag 0x800 on each filled slot marked 0x10 (a duplicate to replace), which draws the
 * replace marker on its cell.
 * Seen in play (2026-11-14): after keeping one of two スピアー, the other row got 0x800 and a
 * yellow marker, and the rental list opened to replace it.
 */
void FreeBattle_MarkSlotsToReplace(SlotFlags* rows) {
    TeamMonSlot* slots;
    s32 i;

    slots = *rows->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flags & 1) && (slots[i].flags & 0x10)) {
            rows->flags[i] |= 0x800;
        }
    }
}

/**
 * Sets row flag 1 (drawn dimmed) on each slot that is not a duplicate (no 0x40), so the
 * duplicates stand out while the player picks one to keep. The cursor can still land on the dimmed
 * rows; A there only buzzes (FreeBattle_UpdateEntrySelect checks 0x40).
 * Seen in play (2026-11-14): on 「おなじポケモンが ２たいいます」 rows 2-5 had flag 1 and blue names,
 * the two duplicates white.
 */
void FreeBattle_DisableNonDuplicateRows(SlotFlags* rows) {
    TeamMonSlot* slots;
    s32 i;

    slots = *rows->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flags & 0x40)) {
            rows->flags[i] |= 1;
        }
    }
}

/**
 * Counterpart of FreeBattle_DisableNonDuplicateRows: clears row flag 1 on each slot that is not a
 * duplicate (no 0x40).
 * Seen in play (2026-11-14): ran after はい on 「このポケモンにしますか？」 in the duplicate flow.
 */
void FreeBattle_EnableNonDuplicateRows(SlotFlags* rows) {
    TeamMonSlot* slots;
    s32 i;

    slots = *rows->slots;
    for (i = 0; i < 6; i++) {
        if (!(slots[i].flags & 0x40)) {
            rows->flags[i] &= ~1;
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
 * Draws the rental Pokemon list window; `cursorStyle` picks the cursor style.
 * Seen in play: draws the picked team's window (trainer panel and six Pokemon) under the confirm
 * prompt.
 */
void FreeBattle_DrawRentalListWindow(s8 *entry, s32 cursor_style)
{
  s32 x;
  s32 y;
  s32 pad[2]; // FAKE: stack padding
  MenuDef8200288C def;
  s32 mode;
 x = (*((s32 *) (((s8 *) entry) + 0x14))) + 6; y = (*((s32 *) (((s8 *) entry) + 0x18))) + 6; // FAKE: decomp slop, raw pointer casts stand in for struct fields
  mode = 0xFFED;
  FreeBattle_DrawRentalNameList(x, y, 2, entry + 0xC8);
  def.items = D_8200AC58;
  def.count = 0;
  def.itemCount = 0x18;
  def.itemSize = (*((s32 *) (((s8 *) entry) + 0x48))) * 6; // FAKE: decomp slop, raw pointer casts stand in for struct fields
  switch (cursor_style)
  {
    case 1:
      mode = 0xFFEF;
      break;

    case 2:
      mode = 0xFFFD;
      break;

  }

  GridMenu_DrawInlineItems(entry + 0x2F8, x + 0x88, y, mode, &def);
  FreeBattle_DrawRowBorders(x, y, D_82008F60);
}
