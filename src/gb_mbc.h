/* Declarations for src/gb_mbc.c. */
#ifndef GB_MBC_H
#define GB_MBC_H

#include "global.h"

// gb_mbc.c
s32 osGbmbcRamEnable(OSPfs*);
s32 osGbmbcSelectRamBank(OSPfs*, u8);
s32 osGbmbcReadWrite(OSPfs*, u16, u32, u8*, u32);

#endif // GB_MBC_H
