/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_emulator/gb_tower_emulator_7F9A0.c. */

#include "global.h"
#include "fragments/gb_tower_emulator/gb_tower_emulator.h"
#include "game_state.h"
#include "jpeg_stream.h"
#include "scheduler.h"
#include "gfx_rect.h"
#include "controller.h"
#include "memory.h"
#include "variables.h"
typedef struct unk_D_8122C4FA {
  /* 0x00 */ u8 unk_00;
  /* 0x01 */ u8 unk_01;
} unk_D_8122C4FA;
typedef struct unk_D_8122B2F8 {
  /* 0x000000 */ char unk000000[0x1FEAE8];
} unk_D_8122B2F8;
typedef struct unk_D_8122B1E8 {
  /* 0x00 */ OSMesg mesg[1];
  /* 0x04 */ OSMesgQueue queue;
  /* 0x1C */ char unk1C[0x4];
  /* 0x20 */ s32 unk_20;
  /* 0x24 */ s32 unk_24;
  /* 0x28 */ void* unk_28;
  /* 0x2C */ s32 unk_2C;
  /* 0x30 */ char unk30[0x8];
  /* 0x38 */ s32 unk_38;
  /* 0x3C */ s32 unk_3C;
  /* 0x40 */ void* unk_40;
  /* 0x44 */ char unk44[0x4];
  /* 0x48 */ void* unk_48;
  /* 0x4C */ void* unk_4C;
  /* 0x50 */ u32 unk_50;
  /* 0x54 */ s32 unk_54;
  /* 0x58 */ void* unk_58;
  /* 0x5C */ s32 unk_5C;
  /* 0x60 */ char unk60[0x8];
} unk_D_8122B1E8;
typedef struct unk_func_812009D0 {
  /* 0x00 */ u8 unk00[0x34];
  /* 0x34 */ u8 data[0x10];  
  /* 0x44 */ u16 unk_44;
  /* 0x46 */ u8 unk_46;
  /* 0x47 */ u8 unk47;
  /* 0x48 */ u8 unk_48;
  /* 0x49 */ u8 unk_49;
  /* 0x4A */ u8 unk_4A;
} unk_func_812009D0;
typedef struct unk_D_8120D7F3 {
    u8 pad[0x116];
    u8 unk116;
} unk_D_8120D7F3;
extern OSThread gGbPakServiceThread;
extern u8 gGbPakServiceThreadStack[0x1000];
extern OSMesg gGbPakServiceQueueMessages[4];
extern OSMesgQueue gGbPakServiceQueue;
extern OSMesgQueue* gGbPakSiEventQueue;
extern volatile u8 gGbPakServiceThreadActive;
extern u8 gGbEmuPresentationMode;
extern unk_D_8122C4FA gGbEmuButtonBindingSelections;
extern u8* gGbEmuFont1Data;
extern u8* gGbEmuFont2Data;
void func_812070A0(void);
void GbApu_SelectRegionClock(s32);
void func_81117068(u16, u8, u16);
void GbApu_ResetChannels(void);
void GbApu_Reset(unk_D_8122B2F8*);
void func_811173F4(void);
void GbAudio_SetAlternateRendererEnabled(s32);
#define GB_EMU_PAL_Y_SCALE 0.833f

#include "m2c_macros.h"

s32 GbEmu_PixelOpDitherA(s32 arg0, s32 arg1);
s32 GbEmu_PixelOpDitherB(s32 arg0, s32 arg1);
s32 GbEmu_PixelOpAverage555(s32 arg0, s32 arg1);
s32 GbEmu_PixelOpReplace(UNUSED s32 arg0, s32 arg1);
void GbEmu_BlitWithPixelOp(u16* dst, u16* src, s32 mode, s32 width, s32 height);
void func_81103D60(u16* dst, u16* src, s32 color, s32 width, s32 height);
void func_8110427C(u16* dst, u8* alpha_map, s32 color, s32 width, s32 height, u32 alpha_stride);
void GbEmu_Delay(OSTime arg0);
void func_81107128(u16* arg0, u16* arg1, s16* arg2, s32 arg3, s32 arg4);

M2C_UNK func_8005C670(s32, M2C_UNK, u16, M2C_UNK *, s32); /* extern */
extern M2C_UNK D_81156480;
void func_81101FA0(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(&D_81156480, s8 *, 0x1F) = arg2;
    func_8005C670(M2C_FIELD(arg0, s32 *, 0x50), 1, arg1, &D_81156480, 0x20);
}

s32 GbPak_InitializeCartridgeMapper(unk_D_8122B2C0* arg0) {
  s32 ret;

  if (!(ret = GbPak_WriteFilledRegisterBlock(arg0, 0, 0xA))    && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 1))
   && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, 0)) && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 0))
   && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, 0)) && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x2100, 1))) {
      *((u8*)arg0 + 0x9D) = 1;
      *((u8*)arg0 + 0x9E) = 0;
      *((u8*)arg0 + 0x9F) = 0;
  }
  
  return ret;
}

/*
 * func_811020A8
 *
 * Operates on a record arg0 that looks like the one GbPak_TransferBankedRam
 * takes (it holds a handle at 0x50 and is passed to func_81102344 in both),
 * but that is inferred from those uses only. Sets the byte at 0xA2 to 2 and
 * saves then clears the byte at 0x98. Calls func_81102344(arg0, word94 >> 13) (the same
 * bank-select helper GbPak_TransferBankedRam uses with address / 0x2000);
 * if that returns 0, calls func_8005C670 with the handle at 0x50, the
 * mode 0 (func_81101FA0 passes 1 here), the address (word94 & 0x1FFF) | 0xA000,
 * the buffer D_811564A0 and a length of 0x20; if that also returns 0, calls
 * func_80057910(D_811564A0, entry, 0x20) where entry is the 0x20-byte record
 * number byte9C of the table at D_811564C0. If the last result is 0 the byte
 * at 0xA2 is reset to 0. The saved byte at 0x98 is restored and the first
 * non-zero (or final) result is returned.
 *
 * What func_8005C670 mode 0 and func_80057910 do, and what the two tables
 * hold, is not established. Matching notes: the unused first local `pad`
 * places `sp28` at sp+0x28, and the table index is scaled as
 * `(x << 1) << 4` because a single `<< 5` (or `* 0x20`) uses one temporary
 * register fewer and does not match.
 */
s32 func_81102344(u8*, s32);
s32 func_80057910(M2C_UNK *, void *, M2C_UNK); /* extern */
extern M2C_UNK D_811564A0;
extern M2C_UNK D_811564C0;
s32 func_811020A8(void *arg0) {
    s32 pad;
    s32 sp28;
    s32 var_v0;
    s32 var_v1;

    M2C_FIELD(arg0, s8 *, 0xA2) = 2;
    sp28 = (s32) M2C_FIELD(arg0, u8 *, 0x98);
    M2C_FIELD(arg0, u8 *, 0x98) = 0U;
    var_v0 = func_81102344(arg0, (u32) M2C_FIELD(arg0, u32 *, 0x94) >> 0xD);
    var_v1 = var_v0;
    if (var_v0 == 0) {
        var_v0 = func_8005C670(M2C_FIELD(arg0, s32 *, 0x50), 0, ((M2C_FIELD(arg0, u32 *, 0x94) & 0x1FFF) | 0xA000) & 0xFFFF, &D_811564A0, 0x20);
        var_v1 = var_v0;
        if (var_v0 == 0) {
            var_v0 = func_80057910(&D_811564A0, (u8 *)&D_811564C0 + ((M2C_FIELD(arg0, u8 *, 0x9C) << 1) << 4), 0x20);
            var_v1 = var_v0;
        }
    }
    if (var_v0 == 0) {
        M2C_FIELD(arg0, s8 *, 0xA2) = 0;
    }
    M2C_FIELD(arg0, u8 *, 0x98) = (u8) sp28;
    return var_v1;
}

s32 func_80051110(s32, s8 *, s8 *);             /* extern */

s32 func_81102168(s8 *arg0) {
    s32 temp_v0;
    s32 var_v1;

    M2C_FIELD(arg0, s8 *, 0xA2) = 1;
    temp_v0 = func_80051110(M2C_FIELD(arg0, s32 *, 0x50), arg0 + 0x9B, arg0);
    var_v1 = temp_v0;
    if ((temp_v0 == 0) && ((M2C_FIELD(arg0, u8 *, 0x9B) & 9) != 9)) {
        var_v1 = 0x63;
    }
    if (var_v1 != 0) {
        return var_v1;
    }
    M2C_FIELD(arg0, s8 *, 0xA2) = 0;
    return 0;
}

s32 func_81101FE8(s8 *);                            /* extern */
s32 func_81102F7C(u8, s32, u8);                     /* extern */

/*
 * func_811021D4
 *
 * Returns 0 right away when bit 0 of the byte at arg0 + 0x9B is set.
 * Otherwise runs func_81102168(arg0), then func_81101FE8(arg0) while the
 * result is 0, then, if bit 0 of the byte at 0x9B is (now) set and the byte
 * at 0x98 is non-zero, func_811020A8(arg0), then
 * func_81102F7C(byte 0x9C, word 0x94, byte 0x98), stopping at the first
 * non-zero result. If the result is non-zero, clears bit 0 of the byte at
 * 0x9B. Returns the result.
 *
 * Same record as GbPak_TransferBankedRam and func_811020A8 take; what the
 * flag bit and the other fields mean is not established.
 *
 * Matching note: the empty `if` on `arg0` has no meaning of its own. It was
 * found with decomp-permuter and is the only form tried that makes the
 * compiler copy arg0 to s0 before the first load, as the ROM does; the
 * triple test is needed (one or two do not match). The same kind of empty
 * test already exists in func_88100100.
 */
s32 func_811021D4(u8 *arg0) {
    s32 ret;

    if (((!arg0) && (!arg0)) && (!arg0)) {
    }
    ret = 0;
    if (!(M2C_FIELD(arg0, u8 *, 0x9B) & 1)) {
        ret = func_81102168(arg0);
        if (ret == 0) {
            ret = func_81101FE8(arg0);
            if ((ret == 0) && (M2C_FIELD(arg0, u8 *, 0x9B) & 1) && (M2C_FIELD(arg0, u8 *, 0x98) != 0)) {
                ret = func_811020A8(arg0);
                if (ret == 0) {
                    ret = func_81102F7C(M2C_FIELD(arg0, u8 *, 0x9C), M2C_FIELD(arg0, s32 *, 0x94), M2C_FIELD(arg0, u8 *, 0x98));
                }
            }
        }
        if (ret != 0) {
            M2C_FIELD(arg0, u8 *, 0x9B) &= ~1;
        }
    }
    return ret;
}

s32 GbPak_SelectRomAddress(unk_D_8122B2C0* arg0, s32 arg1) {
    s32 temp_a2;
    s32 var_v1;

    var_v1 = 0;
    M2C_FIELD(arg0, u8*, 0x9E) = 0xFF;
    if (M2C_FIELD(arg0, u8*, 0x9F) != 0) {
        M2C_FIELD(arg0, u8*, 0x9D) = 0xFF;
        var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 0);
        if (var_v1 == 0) {
            M2C_FIELD(arg0, u8*, 0x9F) = 0;
        }
    }
    if (var_v1 == 0) {
        if (arg1 != M2C_FIELD(arg0, u8*, 0x9D)) {
            temp_a2 = arg1 / 32;
            if (temp_a2 != ((s32)M2C_FIELD(arg0, u8*, 0x9D) / 32)) {
                var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, temp_a2);
            }
            if (var_v1 == 0) {
                var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x2100, arg1);
                if (var_v1 == 0) {
                    M2C_FIELD(arg0, u8*, 0x9D) = arg1;
                }
            }
        }
    }
    return var_v1;
}

s32 GbPak_SelectRamBank(unk_D_8122B2C0* arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    M2C_FIELD(arg0, u8*, 0x9D) = 0xFF;
    if (M2C_FIELD(arg0, u8*, 0x9F) != 1) {
        M2C_FIELD(arg0, u8*, 0x9E) = 0xFF;
        var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 1);
        if (var_v1 == 0) {
            M2C_FIELD(arg0, u8*, 0x9F) = 1;
        }
    }
    if ((var_v1 == 0) && (arg1 != M2C_FIELD(arg0, u8*, 0x9E))) {
        var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, arg1);
        if (var_v1 == 0) {
            M2C_FIELD(arg0, u8*, 0x9E) = arg1;
        }
    }
    return var_v1;
}

typedef struct GbpakChannel811023DC {
    /* 0x00 */ char unk00[0x9B];
    /* 0x9B */ u8 status;
    /* 0x9C */ char unk9C[0x8];
} GbpakChannel811023DC; // size = 0xA4
extern GbpakChannel811023DC D_811561C8[];
s32 func_811023DC(OSPfs* arg0) {
    s32 ret = osGbpakGetStatus(arg0, &D_811561C8[arg0->channel].status);

    if (ret == 0) {
        ret = (D_811561C8[arg0->channel].status & 0xC0) ^ 0x80;
    }
    return ret;
}

s32 func_811021D4(u8*);
s32 func_81102280(u8*, s32);
s32 func_811023DC(OSPfs*);
s32 func_81102460(u8* arg0) {
    s32 ret;
    u8* buf;
    s32 addr;
    s32 remaining;
    s32 size;
    s32 sum;
    s32 off;

    ret = func_811021D4(arg0);
    buf = M2C_FIELD(arg0, u8**, 0x54);
    addr = M2C_FIELD(arg0, s32*, 0x8C);
    remaining = M2C_FIELD(arg0, s32*, 0x80);
    if ((ret == 0) && (addr < 0x4000)) {
        if ((addr + remaining) >= 0x4001) {
            size = 0x4000 - addr;
        } else {
            size = remaining;
        }
        ret = osGbpakReadWrite(M2C_FIELD(arg0, OSPfs**, 0x50), 0, addr, buf, size);
        if (ret == 0) {
            sum = 0;
            for (ret = size; ret != 0; ret--) {
                sum += *buf++;
            }
            M2C_FIELD(arg0, s32*, 0x84) += sum;
            remaining -= size;
            addr = 0x4000;
        }
    }
    while ((ret == 0) && (remaining != 0)) {
        ret = func_81102280(arg0, addr / 0x4000);
        if (ret == 0) {
            off = addr & 0x3FFF;
            if ((off + remaining) >= 0x4001) {
                size = 0x4000 - off;
            } else {
                size = remaining;
            }
            ret = osGbpakReadWrite(M2C_FIELD(arg0, OSPfs**, 0x50), 0, (off | 0x4000) & 0xFFFF, buf, size);
            if (ret == 0) {
                sum = 0;
                for (ret = size; ret != 0; ret--) {
                    sum += *buf++;
                }
                M2C_FIELD(arg0, s32*, 0x84) += sum;
                remaining -= size;
                addr = (addr + 0x4000) & ~0x3FFF;
            }
        }
    }
    if (ret == 0) {
        ret = func_811023DC(M2C_FIELD(arg0, OSPfs**, 0x50));
    }
    return ret;
}

s32 func_811021D4(u8*);
s32 func_81102344(u8*, s32);
s32 func_811023DC(OSPfs*);

s32 GbPak_TransferBankedRam(u8* arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    u8* var_s3;
    s32 var_v0;
    s32 var_v1;
    s32 var_s2;

    var_v0 = func_811021D4(arg0);
    var_v1 = var_v0;
    var_s3 = M2C_FIELD(arg0, u8**, 0x54);
    var_s2 = M2C_FIELD(arg0, s32*, 0x8C);
    var_s1 = M2C_FIELD(arg0, s32*, 0x80);
    while ((var_v0 == 0) && (var_s1 != 0)) {
        var_v0 = func_81102344(arg0, var_s2 / 0x2000);
        var_v1 = var_v0;
        if (var_v0 == 0) {
            temp_v0 = var_s2 & 0x1FFF;
            if ((temp_v0 + var_s1) >= 0x2001) {
                var_s0 = 0x2000 - temp_v0;
            } else {
                var_s0 = var_s1;
            }
            var_v0 = osGbpakReadWrite(M2C_FIELD(arg0, OSPfs**, 0x50), arg1, (temp_v0 | 0xA000) & 0xFFFF, var_s3, var_s0);
            var_v1 = var_v0;
            var_s3 += var_s0;
            var_s1 -= var_s0;
            var_s2 = (var_s2 + 0x2000) & ~0x1FFF;
        }
    }
    if (var_v0 == 0) {
        var_v1 = func_811023DC(M2C_FIELD(arg0, OSPfs**, 0x50));
    }
    return var_v1;
}

#ifdef NON_MATCHING
/* TODO: decompile func_811027A8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811027A8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81102970; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81102970.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81102AC8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81102AC8.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81102C20; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81102C20.s")
#endif

void func_80058260(u32*);
u32 func_80053A80(void);
M2C_UNK func_8005C0A0();

void GbPak_PrepareProbeBlock(u32* arg0, s32 arg1) {
    s32 i;

    switch (arg1) {
        case 3:
            for (i = 0; i < 8; i++) {
                arg0[i] = 0;
            }
            break;
        case 2:
            for (i = 0; i < 8; i++) {
                arg0[i] = -1;
            }
            break;
        case 1:
            func_80058260(arg0);
            arg0[3] = func_80053A80();
            func_8005C0A0();
            func_80058260(arg0 + 4);
            arg0[7] = func_80053A80();
            break;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_81102F7C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81102F7C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811030F0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811030F0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811035B4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811035B4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81103728; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81103728.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81103850; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81103850.s")
#endif

s32 GbEmu_PixelOpDitherA(s32 arg0, s32 arg1) {
  return (arg1 & 1) ? arg1 : arg0;
}

s32 GbEmu_PixelOpDitherB(s32 arg0, s32 arg1) {
  return (arg1 & 1) ? arg0 : arg1;
}

s32 GbEmu_PixelOpAverage555(s32 arg0, s32 arg1) {
  return (((s32) ((arg0 & 0xF800) + (arg1 & 0xF800)) >> 1) & 0xF800) | (((s32) ((arg0 & 0x7C0) + (arg1 & 0x7C0)) >> 1) & 0x7C0) | (((s32) ((arg0 & 0x3E) + (arg1 & 0x3E)) >> 1) & 0x3E);
}

s32 GbEmu_PixelOpReplace(UNUSED s32 arg0, s32 arg1) {
  return arg1;
}

void GbEmu_BlitWithPixelOp(u16* dst, u16* src, s32 mode, s32 width, s32 height) {
  s32 (*operation)(s32, s32);
  s32 x;
  s32 y;
  width = ((width + 3) & 0xFFC);
  switch (mode) {
      case 0:  operation = GbEmu_PixelOpDitherA; break;
      case 1:  operation = GbEmu_PixelOpDitherB; break;
      case 2:  operation = GbEmu_PixelOpAverage555; break;
      default: operation = GbEmu_PixelOpReplace; break;
  }

  for (x = 0; x != height; x++) {
      for (y = 0; y != width; y++) {
          *dst = operation(*dst, *src);
          dst++;
          src++;
      }
      dst = dst - width + 0x140;
  }
}

M2C_UNK func_8004FD20(s32, M2C_UNK);                /* extern */
M2C_UNK func_8005C0A0();                            /* extern */
extern s32 D_8115658C;

void func_81103D30(void) {
    func_8004FD20(D_8115658C, 0x2800);
    func_8005C0A0();
}

void func_81103D60(u16* dst, u16* src, s32 color, s32 width, s32 height) {
    s32 x;
    s32 y;
    s32 intensity;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            intensity = (src[y * width + x] & 0x3E) >> 1;
            dst[y * 320 + x] = ((((color & 0xF800) * intensity) / 31) & 0xF800) |
                               ((((color & 0x7C0) * intensity) / 31) & 0x7C0) |
                               ((((color & 0x3E) * intensity) / 31) & 0x3E);
        }
    }
}

void func_8110427C(u16* dst, u8* alpha_map, s32 color, s32 width, s32 height, u32 alpha_stride) {
  u16* dst_row;
  u8* alpha_row;
  s32 x;
  s32 y;
  s32 var_t0;
  s32 var_t4;
  s32 var_a0;
  for (y = 0; y < height; y++) {
      for (x = 0; x < width; x++) {
          var_a0 = alpha_map[y * alpha_stride + x] & 0xF;
          var_t0 = (dst[y * 320 + x] & 0xF800) + (((color & 0xF800) * var_a0) / 15 & 0xF800);
          if (var_t0 > 0xF800) var_t0 = 0xF800;
          var_t4 = var_t0;
          var_t0 = (dst[y * 320 + x] & 0x07C0) + (((color & 0x07C0) * var_a0) / 15 & 0x07C0);
          if (var_t0 > 0x07C0) var_t0 = 0x07C0;
          var_t4 |= var_t0;
          var_t0 = (dst[y * 320 + x] & 0x003E) + (((color & 0x003E) * var_a0) / 15 & 0x003E);
          if (var_t0 > 0x003E) var_t0 = 0x003E;
          dst[y * 320 + x] = (s16)(var_t4 | var_t0);
      }
  }
}

extern u16 D_811205F8[];
extern u16 D_811206F8[];
extern u16 D_811207F8[];

void func_8110445C(u8* arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 8; i < arg2 - 8; i += 8) {
        func_81103D60((u16*)arg0 + i, D_811206F8, arg1, 8, 0x10);
    }
    func_81103D60((u16*)arg0, D_811205F8, arg1, 8, 0x10);
    func_81103D60((u16*)(arg0 + arg2 * 2 - 0x10), D_811207F8, arg1, 8, 0x10);
}

#ifdef NON_MATCHING
/* TODO: decompile func_81104540; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81104540.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81104618; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81104618.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811047A0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811047A0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81104930; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81104930.s")
#endif

M2C_UNK func_8004FD20(s32, M2C_UNK);                /* extern */
extern s32 D_81156550;

void func_81104AE4(void) {
    func_8004FD20(D_81156550 + 0x12D00, 0x20);
}

extern u32 D_811565AC;
extern u32 D_811565B0;
s32 func_81104B18(s32 arg0, M2C_UNK arg1)
{
  s32 new_var;
  s32 temp_v1;
  u32 temp_t6;
  temp_v1 = (D_811565AC + 0x3F) & (~0x3F);
  new_var = temp_v1;
  ;
  if ((D_811565AC = new_var + arg0) >= ((u32) D_811565B0))
  {
    loop_1:
    goto loop_1;

  }
  return new_var;
}

M2C_UNK func_81102970(u8, s32);                     /* extern */
extern u8 D_811565A0;

void func_81104B60(s32 arg0) {
    func_81102970(D_811565A0, arg0);
}

void GbEmu_Delay(OSTime arg0) {
  OSMesgQueue sp68;
  void* sp64;
  OSTimer sp40;

  osCreateMesgQueue(&sp68, &sp64, 1);
  osSetTimer(&sp40, (1000 * arg0) * 64 / 3, 0, &sp68, NULL);
  osRecvMesg(&sp68, NULL, 1);
}

#ifdef NON_MATCHING
/* TODO: decompile func_81104C30; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81104C30.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81104CD4; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81104CD4.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81104D84; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81104D84.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81104DD0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81104DD0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811056CC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811056CC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_811064DC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811064DC.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110659C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110659C.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_8110665C; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_8110665C.s")
#endif

extern M2C_UNK D_8115623C;
extern u8 D_811565A1;

s32 func_81106700(void) {
    s32 var_v0;
    u8 *var_v1;

    var_v0 = 0;
    if (D_811565A1 != 0) {
        return 1;
    }
    var_v1 = *((M2C_UNK*)((u8*)&D_8115623C + (D_811565A0 * 0xA4)));
loop_3:
    var_v0 += 4;
    if (M2C_FIELD(var_v1, u8 *, 0) == 0) {
        return 1;
    }
    if (M2C_FIELD(var_v1, u8 *, 1) == 0) {
        return 1;
    }
    if (M2C_FIELD(var_v1, u8 *, 2) == 0) {
        return 1;
    }
    if (M2C_FIELD(var_v1, u8 *, 3) == 0) {
        return 1;
    }
    var_v1 += 4;
    if (var_v0 == 0x80) {
        return 0;
    }
    goto loop_3;
}

#ifdef NON_MATCHING
/* TODO: decompile func_811067B0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_811067B0.s")
#endif

extern s8 D_81156546;

void func_81106820(void) {
    D_81156546 = 1;
}

extern s16 D_82608542;
extern s16 D_82608544;
extern s16 D_8260854C;
extern s16 D_8260854E;
extern s16 D_800AA148;
extern s32 D_81156550;
void func_811174D8(void);
void osViBlack(u8);
void VictoryPalace_ResetPillarGlow(UNUSED s32 arg0) {
    if ((*(u8*)&D_81156546 == 0) && (D_800AA148 == 0)) {
        func_811174D8();
        ((u8*)D_81156550)[0xFF26] = GbMem_ReadIoRegister(0xFF26);
    }
    if (D_800AA148 != 0) {
        osViBlack(1);
    }
}

extern u16 D_811248C0[];
extern u16 D_81124940[];
extern u16 D_811249C0[];
extern u16 D_81124A40[];
extern u16 D_81124AC0[];
extern u16 D_81124B40[];
extern u16 D_81124BC0[];
extern u16 D_81124C40[];
void func_811068A0(u16* arg0) {
    s32 i;
    s32 j;

    for (i = 1; i != 5; i++) {
        GbEmu_BlitWithPixelOp(&arg0[i * 8], D_81124940, 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(&arg0[38 * 320 + i * 8], D_81124BC0, 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(&arg0[i * 8 * 320], D_81124A40, 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(&arg0[i * 8 * 320 + 38], D_81124AC0, 0xFFFF, 8, 8);
    }
    GbEmu_BlitWithPixelOp(arg0, D_811248C0, 0, 8, 8);
    GbEmu_BlitWithPixelOp(&arg0[38], D_811249C0, 0, 8, 8);
    GbEmu_BlitWithPixelOp(&arg0[38 * 320], D_81124B40, 0, 8, 8);
    GbEmu_BlitWithPixelOp(&arg0[38 * 320 + 38], D_81124C40, 0, 8, 8);

    for (j = 0; j < 30; j++) {
        for (i = 0; i < 30; i++) {
            arg0[(j + 8) * 320 + i + 8] = 0xC14;
        }
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_81106AA0; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81106AA0.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_81106CC8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/fragments/fragment000_80C00/func_81106CC8.s")
#endif

void func_81107128(u16* arg0, u16* arg1, s16* arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 j;
    s32 var_v1;
    s32 var_t4;

    for (j = 0; j < arg3; j++) {
        for (i = 0; i < 320; i++) {
            var_v1 = (arg0[(j * 320) + ((arg4 + i) % 320)] & 0xF800) + (arg1[(j * 320) + i] & 0xF800);
            if (var_v1 > 0xF800) {
                var_v1 = 0xF800;
            }
            var_t4 = var_v1;
            var_v1 = (arg0[(j * 320) + ((arg4 + i) % 320)] & 0x7C0) + (arg1[(j * 320) + i] & 0x7C0);
            if (var_v1 > 0x7C0) {
                var_v1 = 0x7C0;
            }
            var_t4 |= var_v1;
            var_v1 = (arg0[(j * 320) + ((arg4 + i) % 320)] & 0x3E) + (arg1[(j * 320) + i] & 0x3E);
            if (var_v1 > 0x3E) {
                var_v1 = 0x3E;
            }
            arg2[(j * 320) + i] = var_t4 | var_v1;
        }
    }
}

extern u32 D_811565DC;
extern u32 D_811565D8;
extern u8 D_811565E0;
extern s32 D_811565C4;
extern u32 D_811565C8;
extern u32 D_811565CC;
extern s32 D_811565C0;
extern u16* D_811565D4;
extern u16* D_811565D0;
void func_81106AA0(s32, u8);
void func_8110724C(void) {
    if ((osGetCount() - D_811565DC) > D_811565D8) {
        D_811565DC = osGetCount();
        D_811565E0 = (D_811565E0 + 1) & 7;
        func_81106AA0(D_811565C4 + 0x87BA, D_811565E0);
        if (D_811565D8 > 0x80000) {
            D_811565D8 -= D_811565D8 >> 8;
        }
    }
    if ((osGetCount() - D_811565C8) >= 0x200000) {
        D_811565C8 = osGetCount();
        D_811565CC++;
        if (D_811565CC >= 0x140) {
            D_811565CC = 0;
        }
        func_81107128(D_811565D4, D_811565D0, (s16*)(D_811565C0 + 0x20A80), 0xF, D_811565CC);
        func_8005C0A0();
    }
}
