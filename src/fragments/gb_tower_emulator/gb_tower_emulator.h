#ifndef _FRAGMENT1_H_
#define _FRAGMENT1_H_

#include "global.h"
#include "src/gb_tower_audio.h"

// Yay0 files in fragment1_misc_yay0 (retail ROM 0xADC80), named by their retail ROM address.
// Offsets from the segment rather than fixed addresses, so they follow it when an earlier
// segment changes size.
#define D_F4130 (fragment1_misc_yay0_ROM_START + 0x464B0)
#define D_F4920 (fragment1_misc_yay0_ROM_START + 0x46CA0)
#define D_F5450 (fragment1_misc_yay0_ROM_START + 0x477D0)
#define D_FDE40 (fragment1_misc_yay0_ROM_START + 0x501C0)
#define D_102BA0 (fragment1_misc_yay0_ROM_START + 0x54F20)

void GbAudio_UpdateFrame();
s32 osGbSetNextBuffer(void*, s32);
void GbAudio_PlayMenuSound(s32);
u8 GbMem_ReadIoRegister(u16);
void func_811177E8(s32, s16*);

#endif /* _FRAGMENT1_H_ */
