/* Declarations for src/gb_player.c. */
#ifndef GB_PLAYER_H
#define GB_PLAYER_H

#include "global.h"

// gb_player.c
s32 GbPak_VerifyPattern(s32 arg0, void* arg1);
s32 GbPak_DetectRam(s32 arg0, u8* arg1);
s32 GbPlayer_ProbePak(s32 arg0, u8* arg1, u8* arg2);
s32 GbPlayer_IsPakInserted(s32 arg0, u8 arg1);
void GbPlayer_PowerOffAllPaks(void);
s32 GbPlayer_ScanPaks(void);
s32 GbPak_IsCartOff(s32 arg0);
s32 GbPak_IsCartOn(s32 arg0);
s32 GbPlayer_ReinitPak(s32 arg0);
s32 GbPlayer_VerifyPakStillInserted(s32 arg0, void* arg1);
s32 GbPak_MbcRead(s32 arg0, void* arg1, u16 arg2, u16 arg3);
s32 GbPak_MbcWrite(s32 arg0, void* arg1, u16 arg2, u16 arg3);
s32 GbPak_RawRead(s32 arg0, u8* arg1, u16 arg2, u16 arg3);
s32 GbPak_RawWrite(s32 arg0, u8* arg1, u16 arg2, u16 arg3);
int GbPak_SelectRomBank(s32 arg0, s32 arg1);
s32 GbPak_ReadRom(s32 arg0, u8* arg1, s32 arg2, s32 arg3);
u8 GbPlayer_SetPollMask(u8 arg0);
void GbPlayer_PollPakConnection(void);

#endif // GB_PLAYER_H
