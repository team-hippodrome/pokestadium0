/* Declarations for the n64_logo fragment (src/fragments/n64_logo/). */
#ifndef FRAGMENT_N64_LOGO_H
#define FRAGMENT_N64_LOGO_H

#include "global.h"

// n64_logo.c
void N64Logo_DrawLogoTexture(void);
s32 N64Logo_DrawFrame(UNUSED u8 fadeMode);
void N64Logo_HoldForOneSecond(u64 startTime);
void N64Logo_ScanTransferPaks(void);
s32 N64Logo_Main(UNUSED s32 loaderArg0, UNUSED s32 loaderArg1);

#endif // FRAGMENT_N64_LOGO_H
