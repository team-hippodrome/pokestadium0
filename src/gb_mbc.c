/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/gb_mbc.c. */

#include "global.h"
#define MBC_RAM_ENABLE        0x0000
#define MBC_ROM_BANK_ADDRESS  0x2000
#define MBC_RAM_BANK_ADDRESS  0x4000
#define MBC_BANKING_MODE      0x6000
#define RAM_BASE_ADDRESS      0xA000
#define RAM_BANK_NONE         0XFF;
#define ERRCK(fn) \
    ret = fn;     \
    if (ret != 0) \
        return ret
extern u8 D_800AB040[16];

s32 osGbmbcRamEnable(OSPfs* pfs);
s32 osGbmbcSelectRamBank(OSPfs* pfs, u8 bank);
s32 osGbmbcReadWrite(OSPfs* pfs, u16 flag, u32 address, u8* buffer, u32 size);

/** Enables cartridge RAM on a Game Boy cartridge's memory bank controller. */
s32 osGbmbcRamEnable(OSPfs* pfs) {
  s32 i;
  s32 ret;
  u8 status;
  u8 buffer[BLOCKSIZE];

  ret = osGbpakGetStatus(pfs, &status);
  if (ret != 0) {
      return ret;
  }
  for (i = 0; i < BLOCKSIZE; i++) {
      buffer[i] = 1;
  }
  // Select Banking Mode 1
  ERRCK(osGbpakReadWrite(pfs, OS_WRITE, MBC_BANKING_MODE, buffer, BLOCKSIZE));

  for (i = 0; i < BLOCKSIZE; i++) buffer[i] = 0;
  
  buffer[0x1F] = 0xA;

  ERRCK(osGbpakReadWrite(pfs, OS_WRITE, MBC_RAM_ENABLE, buffer, BLOCKSIZE));

  D_800AB040[pfs->channel] = RAM_BANK_NONE;

  ret = osGbpakGetStatus(pfs, &status);
  if ((ret == 0) && !(status & OS_GBPAK_POWER)) {
      ret = PFS_ERR_CONTRFAIL;
  }
  return ret;
}

/** Selects a RAM bank on a Game Boy cartridge's memory bank controller. */
s32 osGbmbcSelectRamBank(OSPfs* pfs, u8 bank) {
    s32 i;
    s32 ret;
    u8 buffer[BLOCKSIZE];
    
    for (i = 0; i < BLOCKSIZE; i++) buffer[i] = bank;

    ret = osGbpakReadWrite(pfs, OS_WRITE, MBC_RAM_BANK_ADDRESS, buffer, BLOCKSIZE);
    if (ret == 0) {
        D_800AB040[pfs->channel] = bank;
    }
    return ret;
}

/** Reads or writes cartridge memory through the memory bank controller. */
s32 osGbmbcReadWrite(OSPfs* pfs, u16 flag, u32 address, u8* buffer, u32 size) {
    s32 ret;
    s32 var_s0;
    u8 status;
    u8 var_s2;

    ERRCK(osGbpakGetStatus(pfs, &status));

    var_s2 = address >> 0xD;
    if (var_s2 != D_800AB040[pfs->channel]) {
        ERRCK(osGbmbcSelectRamBank(pfs, var_s2));
    }
    address &= 0x1FFF;
    var_s0 = address + size;

    while (1) {
        if (var_s0 > MBC_ROM_BANK_ADDRESS) {
            var_s0 -= MBC_ROM_BANK_ADDRESS;
            ret = osGbpakReadWrite(pfs, flag, address + RAM_BASE_ADDRESS, buffer, MBC_ROM_BANK_ADDRESS - address);
            if (ret != 0) {
                break;
            }
            buffer = (buffer - address) + MBC_ROM_BANK_ADDRESS;
            var_s2++;
            ret = osGbmbcSelectRamBank(pfs, var_s2);
            if (ret != 0) {
                break;
            }
            size = var_s0;
            address = 0;
        } else {
            ret = osGbpakReadWrite(pfs, flag, address + RAM_BASE_ADDRESS, buffer, size);
            break;
        }
    }

    if (ret == 0) {
        ret = osGbpakGetStatus(pfs, &status);
    }
    if ((ret == 0) && !(status & 1)) {
        ret = PFS_ERR_CONTRFAIL;
    }
    return ret;
}
