/* Declarations for the n64_logo fragment (src/fragments/n64_logo/). */
#ifndef FRAGMENT_N64_LOGO_H
#define FRAGMENT_N64_LOGO_H

#include "global.h"

// n64_logo.c
void N64Logo_DrawLogoTexture(void);
s32 N64Logo_DrawFrame(UNUSED u8 fade_mode);
void N64Logo_HoldForOneSecond(u64 start_time);
void N64Logo_ScanTransferPaks(void);
s32 N64Logo_Main(UNUSED s32 loader_arg0, UNUSED s32 loader_arg1);

#endif // FRAGMENT_N64_LOGO_H
