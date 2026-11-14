/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"
#include "gb_tower_launch.h"

M2C_UNK (*func_80002C80(M2C_UNK *))(s32);           /* extern */
M2C_UNK func_80004920(s32);                         /* extern */
M2C_UNK func_80004EA8(s32);                         /* extern */
M2C_UNK func_800567E0(s32, s32, M2C_UNK);           /* extern */
M2C_UNK func_800594D0(M2C_UNK);                     /* extern */
extern M2C_UNK D_800A9710;
extern s32 D_800AAF44;
extern M2C_UNK D_81106830;

void func_8000AAE0(s32 arg0) {
    M2C_UNK (*temp_s2)(s32);

    temp_s2 = func_80002C80(&D_81106830);
    func_800594D0(0x01000F00);
    func_800567E0(D_800AAF44 + 0x21C0, D_800AAF44 + 0x21B0, 1);
    func_80004EA8(D_800AAF44 + 0x21B0);
loop_1:
    func_80004920(D_800AAF44 + 0x21B0);
    if (M2C_FIELD(&D_800A9710, s16 *, 0xA38) >= 0x15) {
        goto loop_1;
    }
    temp_s2(D_800AAF44);
    goto loop_1;
}

M2C_UNK (*func_80002C80(M2C_UNK *))(s32);           /* extern */
M2C_UNK func_80004920(s32);                         /* extern */
M2C_UNK func_80004EA8(s32);                         /* extern */
M2C_UNK func_800567E0(s32, s32, M2C_UNK);           /* extern */
M2C_UNK func_800594D0(M2C_UNK);                     /* extern */
M2C_UNK func_8005C130(s32);                         /* extern */
extern M2C_UNK D_800A9710;
extern s32 D_800AAF40;
extern s32 D_800AAF44;
extern M2C_UNK D_811008DC;
extern M2C_UNK D_81100C84;
void func_8000AB98(s32 arg0) {
    M2C_UNK (*temp_s1)(s32);
    M2C_UNK (*temp_s2)(s32);

    temp_s1 = func_80002C80(&D_811008DC);
    temp_s2 = func_80002C80(&D_81100C84);
    func_800594D0(0x01000F00);
    func_800567E0(D_800AAF40 + 0x21E4, D_800AAF40 + 0x21D4, 1);
    func_80004EA8(D_800AAF40 + 0x21D4);
    temp_s1(D_800AAF40);
    func_8005C130(D_800AAF44);
loop_1:
    func_80004920(D_800AAF40 + 0x21D4);
    if (M2C_FIELD(&D_800A9710, s16 *, 0xA38) >= 0x15) {
        goto loop_1;
    }
    temp_s2(D_800AAF40);
    goto loop_1;
}

/*
 * GbTower_Start
 *
 * Starts the Game Boy Tower emulator (the counterpart of GbTower_Stop below;
 * the donor decomp calls this function GbTower_Start and the symbol table
 * keeps that name).  Steps, in the order the code does them:
 *   1. push a memory-pool state tagged 'GBEM' and allocate two blocks:
 *      D_800AAF40 (0x2208 bytes, the emulator thread's data) and D_800AAF44
 *      (0x21E0 bytes, the audio thread's data);
 *   2. load the emulator fragment (ROM 0x80C00..0xDA9B0, linked at
 *      0x81100000) and open the font archive at ROM 0x2B2C80..0x2E0BE0,
 *      storing its files 0 and 1 at offsets 0x21CC and 0x21D0 of D_800AAF40;
 *   3. save the 8-byte input state *arg0 at offset 0x2200 of D_800AAF40
 *      (GbTower_Stop copies it back);
 *   4. create a one-slot message queue at D_800AAF40 + 0x21B4 with its
 *      buffer at +0x21B0, then create the audio thread (id 9, priority 0x11,
 *      func_8000AAE0) and the emulator thread (id 8, priority 0xF,
 *      func_8000AB98), each with its stack top at its block + 0x21B0;
 *   5. record the previous GbTower_SetPollMask(0) value in D_800AAF48 and
 *      start the emulator thread.
 *
 * Same sequence as GbTower_Start in the Stadium 1 decomp; Zero's block
 * sizes and layout differ (0x2208 here, 0x2210 there).
 */
extern u8 D_81100000[];
extern u8 D_00080C00[];
extern u8 D_000DA9B0[];
extern u8 D_002B2C80[];
extern u8 D_002E0BE0[];
extern u8 D_800AAF48;
void main_pool_push_state(u32 tag);
void* main_pool_alloc(u32 size, s32 side);
M2C_UNK Fragment_Load(s32 id, u8* romStart, u8* romEnd);
void* BinArchive_Open(u8* romStart, u8* romEnd, s32 arg2, s32 arg3);
void* BinArchive_GetFile(void* archive, s32 index);
M2C_UNK func_800567E0(s32, s32, M2C_UNK);
M2C_UNK func_80051B20(s32, s32, void (*)(s32), s32, s32, s32);
u8 func_8000C610(u8);

/**
 * Starts a GB Tower session: allocates both thread blocks, loads the emulator
 * fragment and fonts, copies the session parameters and starts the emulator thread.
 * Seen in play (2026-11-13) ran each time the GB player started (main menu GB, Yes), twice in one
 * session.
 * @unverified Name was previously used only by callers of this address; the definition was still func_. Comment from Stadium 1.
 */
void GbTower_Start(GbTowerLaunchParams* arg0) {
    void* temp_v0;

    main_pool_push_state('GBEM');
    D_800AAF40 = (s32)main_pool_alloc(0x2208, 0);
    D_800AAF44 = (s32)main_pool_alloc(0x21E0, 0);
    Fragment_Load(((((u32)D_81100000) & 0x0FF00000) >> 0x14) - 0x10, D_00080C00, D_000DA9B0);
    temp_v0 = BinArchive_Open(D_002B2C80, D_002E0BE0, 1, 1);
    M2C_FIELD(D_800AAF40, void**, 0x21CC) = BinArchive_GetFile(temp_v0, 0);
    M2C_FIELD(D_800AAF40, void**, 0x21D0) = BinArchive_GetFile(temp_v0, 1);
    M2C_FIELD(D_800AAF40, GbTowerLaunchParams*, 0x2200) = *arg0;
    func_800567E0(D_800AAF40 + 0x21B4, D_800AAF40 + 0x21B0, 1);
    func_80051B20(D_800AAF44, 9, func_8000AAE0, 0, D_800AAF44 + 0x21B0, 0x11);
    func_80051B20(D_800AAF40, 8, func_8000AB98, 0, D_800AAF40 + 0x21B0, 0xF);
    D_800AAF48 = func_8000C610(0);
    func_8005C130(D_800AAF40);
}

M2C_UNK func_8004D1C0(s32, s32 *, M2C_UNK);         /* extern */
extern s32 D_800AAF40;

s32 func_8000ADE8(void) {
    s32 sp1C;

    func_8004D1C0(D_800AAF40 + 0x21B4, &sp1C, 1);
    return sp1C;
}

extern u8 D_800AAF48;
void func_80052DC0(s32);
void Display_ApplyPendingVideoMode(void);
void func_80004EF0(s32);
void func_8004D9B0(s32);
void func_80002620(s32);

/**
 * Ends the session: copies the session parameters back (button bindings), restores
 * the pak poll mask and destroys both threads.
 * Seen in play (2026-11-13) ran when quitting the GB player (C-Up menu, Quit game, Yes) back to the
 * main menu.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void GbTower_Stop(GbTowerLaunchParams* arg0) {
    *arg0 = M2C_FIELD(D_800AAF40, GbTowerLaunchParams*, 0x2200);
    func_8000C610(D_800AAF48);
    func_80052DC0(1);
    Display_ApplyPendingVideoMode();
    func_80004EF0(D_800AAF40 + 0x21D4);
    func_80004EF0(D_800AAF44 + 0x21B0);
    func_8004D9B0(D_800AAF40);
    func_8004D9B0(D_800AAF44);
    func_80002620('GBEM');
}
