/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"

M2C_UNK func_80000C14();                            /* extern */
M2C_UNK DpIntro_SetViMode(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_80001868();                            /* extern */
M2C_UNK func_80004E34();                            /* extern */
M2C_UNK func_8000803C();                            /* extern */
M2C_UNK func_80051B20(M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *, s32); /* extern */
M2C_UNK func_80052DC0(M2C_UNK);                     /* extern */
M2C_UNK func_80057370(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_8005BD80(M2C_UNK);                     /* extern */
M2C_UNK func_8005C130(M2C_UNK *);                   /* extern */
extern M2C_UNK D_8000A92C;
extern M2C_UNK D_800269A0;
extern M2C_UNK D_800809B0;
extern M2C_UNK D_80082B60;

/**
 * Idle thread: sets up the VI mode, interrupts and subsystems, starts thread 4,
 * then idles. Name from Stadium 1's Idle_ThreadEntry.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Idle_ThreadEntry(s32 arg0) {
    func_8005BD80(0xFE);
    DpIntro_SetViMode(0, 1);
    func_80052DC0(1);
    func_8000803C();
    func_80000C14();
    func_80004E34();
    func_80051B20(&D_80082B60, 4, &D_8000A92C, 0, &D_80084D10, 0x50);
    func_8005C130(&D_80082B60);
    func_80001868();
    func_80051B20(&D_800809B0, 6, &D_800269A0, 0, &D_80082B60, 0x14);
    func_8005C130(&D_800809B0);
    func_80057370(0, 0);
loop_1:
    goto loop_1;
}

M2C_UNK func_80002D58();                            /* extern */
M2C_UNK func_800093C0(M2C_UNK);                     /* extern */
M2C_UNK func_80051B20(M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *, s32); /* extern */
M2C_UNK func_80052180();                            /* extern */
M2C_UNK func_8005C130(M2C_UNK *);                   /* extern */
extern M2C_UNK D_80080400;
extern M2C_UNK D_800809B0;

/**
 * Boot entry: initializes the OS, then creates and starts the idle thread
 * (id 1, Idle_ThreadEntry). Name from Stadium 1's Main.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void Main(void) {
    func_80052180();
    func_800093C0(0);
    func_80002D58();
    func_80051B20(&D_80080400, 1, &Idle_ThreadEntry, 0, &D_800809B0, 0x64);
    func_8005C130(&D_80080400);
}
