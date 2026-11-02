/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/DDC0.c, src/audio_sound_state.c, src/save_data.c. */

#include "save_data.h"
#include "save_data.h"
#include "gb_data.h"
#include "jpeg_stream.h"
#include "memory.h"

#include "audio_sound_state.h"
#include "libnumus/player.h"
#include "audio_stream.h"
#include "3D140.h"
#include "audio_commands.h"

#include <PR/os_internal_reg.h>
#include "global.h"
#include "dp_intro.h"
#include "profiler.h"
#include "audio_loop_point.h"
#include "scheduler.h"
#include "gb_tower_audio.h"
#include "audio_commands.h"
#include "audio_category_fade.h"
#include "audio_sound_state.h"
#include "audio_channel.h"
#include "audio_loop_point.h"
typedef struct unk_D_800A8480 {
  /* 0x0000 */ OSThread thread;
  /* 0x01B0 */ char unk01B0[0x2030];
} unk_D_800A8480;
extern s32 D_800AAE30;
extern s32 D_800AAF3C;

#include "m2c_macros.h"

u16 Save_Checksum(u8* arg0, s32 arg1);
s32 Save_RecordIsValid(u8* arg0, s32 arg1);
void Save_WriteFooter(u8* arg0, s32 arg1, s32 arg2);
s32 Audio_GetFreeVoiceCount(void);
void func_80024044(void);
void Save_ResetAndCommitTypedRecord(s32 arg0, s32 arg1);
s32 Deck_IsSaveEntryPresent(s32 arg0, s32 arg1);

s32 Save_IsTypedRecordFlagSet(s32 arg0, s32 arg1, s16 arg2);
void Save_CommitTypedRecord(s32 arg0, s32 arg1);
void Save_ClearTypedRecord(s32 arg0, s32 arg1);

u16 Save_Checksum(u8* arg0, s32 arg1) {
    u16 var_v1 = 0;

    while (arg1-- > 2) {
        var_v1 += *arg0++;
    }
    return var_v1;
}

s32 Save_RecordIsValid(u8* arg0, s32 arg1) {
    u16* temp_v1 = arg1 + arg0;

    temp_v1 -= 3;

    if (temp_v1[0] != 'PO') {
        return 0;
    }

    if (temp_v1[1] != 'KE') {
        return 0;
    }

    if (temp_v1[2] != Save_Checksum(arg0, arg1)) {
        return 0;
    }

    return 1;
}

void Save_WriteFooter(u8* arg0, s32 arg1, s32 arg2) {
    u16* temp_v1;

    if (arg2 != 0) {
        temp_v1 = arg1 + arg0;

        temp_v1 -= 3;
        *temp_v1++ = 'PO';
        *temp_v1++ = 'KE';
        *temp_v1++ = Save_Checksum(arg0, arg1);
    } else {
        temp_v1 = arg1 + arg0;
        temp_v1 -= 3;

        *temp_v1++ = 'XX';
        *temp_v1++ = 'XX';
        *temp_v1++ = Save_Checksum(arg0, arg1) ^ 0xFF;
    }
}

M2C_UNK func_80058410(s32, s32, s32);
M2C_UNK func_80003774(s32, M2C_UNK, M2C_UNK, M2C_UNK);
extern s32 D_800AE8E0;
void func_80023890(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp1C = arg1 - D_800AE8E0;

    func_80058410(arg0, arg1, arg2);
    func_80003774(arg1, sp1C, arg2, 1);
}

/*
 * func_800238D8: flushes one save record whose "dirty" flag is set.
 *
 * `arg0` is the address of the record inside the buffer at D_800AE8E0 and
 * `arg1` its size in bytes (halfword flag at the start of the record).  If
 * bit 1 of that halfword is set: the bit is cleared, the footer is rewritten
 * with Save_WriteFooter(record, size, 1) (the valid 'PO' 'KE' form), the
 * record is copied to record + size via func_80058410(src, dst, size) -- a
 * second copy directly behind it -- and func_80003774 is called with the
 * record address, its offset from the start of the buffer, twice the size and
 * 1.  What func_80003774 does with them (the offset and doubled size suggest
 * a write of both copies out to the save medium) is not established here.
 *
 * Callers such as func_8002404C pass a third argument that this function
 * ignores, so the prototype is left unspecified at the call sites and the
 * definition is written in K&R style.  The unused pad[2] only reproduces the
 * retail stack frame.
 */
void func_800238D8(arg0, arg1)
    s32 arg0;
    s32 arg1;
{
    UNUSED s32 pad[2];
    s32 offset;
    s16 flags = *(s16*)arg0;

    if (flags & 2) {
        offset = arg0 - D_800AE8E0;
        *(s16*)arg0 = flags & 0xFFFD;
        Save_WriteFooter((u8*)arg0, arg1, 1);
        func_80058410(arg0, arg0 + arg1, arg1);
        func_80003774(arg0, offset, arg1 * 2, 1);
    }
}

/*
 * func_80023954: same as func_800238D8, but for invalidating a dirty record.
 *
 * If bit 1 of the record's leading halfword is set, the footer is written with
 * Save_WriteFooter(record, size, 0) (the 'XX' 'XX' form with the inverted
 * checksum), the record is copied to record + size via func_80058410 and
 * func_80003774 is called with the record address, its offset from the start
 * of the buffer at D_800AE8E0, twice the size and 1.  Unlike func_800238D8
 * the flag bit is left set.  `arg0` is the record address and `arg1` its size.
 * A third argument passed by func_80024170 is ignored; the definition is K&R
 * style for that reason, and the unused pad[2] reproduces the retail stack
 * frame.
 */
void func_80023954(arg0, arg1)
    s32 arg0;
    s32 arg1;
{
    UNUSED s32 pad[2];
    s32 offset;

    if (*(s16*)arg0 & 2) {
        offset = arg0 - D_800AE8E0;
        Save_WriteFooter((u8*)arg0, arg1, 0);
        func_80058410(arg0, arg0 + arg1, arg1);
        func_80003774(arg0, offset, arg1 * 2, 1);
    }
}

M2C_UNK func_80058410(s32, s32, s32);               /* extern */

void func_800239C4(s32 arg0, s32 arg1) {
    func_80058410(arg0 + arg1, arg0, arg1);
}

M2C_UNK func_8004FD20();                            /* extern */
void func_800239F0(s16 *arg0)
{
  if (1)
  {
    func_8004FD20();
    *arg0 |= 2;
  }
}

#ifdef NON_MATCHING
/* TODO: decompile func_80023A20; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80023A20.s")
#endif

extern s32 D_8006BBA0;
extern s32 D_800AE8E0;

void func_80023C08(s32 arg0, s32 arg1) {
    if (arg1 == 0x42553634) {
        D_8006BBA0 = 0;
        D_800AE8E0 = 0;
    }
}

s32 func_8000234C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *); /* extern */
M2C_UNK func_80003774(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_80023A20(M2C_UNK, s32);                /* extern */
M2C_UNK func_8004FD20(s32, M2C_UNK);                /* extern */
s32 func_80023C30(void)
{
  s32 temp_v0;
  int new_var;
  s32 var_s0;
  s32 var_s0_2;
  if ((*((s32 *) (&D_8006BBA0))) == 0)
  {
 do { temp_v0 = func_8000234C(0x8000, 0, 0x42553634, &(*((s8 *) (&func_80023C08)))); *((s32 *) (&D_800AE8E0)) = temp_v0; } while (0);
    if (temp_v0 != 0)
    {
      *((s32 *) (&D_8006BBA0)) = 1;
      new_var = 0;
      func_8004FD20(temp_v0, 0x8000);
      func_80003774(*((s32 *) (&D_800AE8E0)), 0, 0x8000, 0);
      var_s0 = new_var;
      do
      {
        func_80023A20(0x10, var_s0);
        var_s0 += 1;
      }
      while (var_s0 < 0x10);
      var_s0_2 = 0;
      do
      {
        func_80023A20(0x11, var_s0_2);
        func_80023A20(0x12, var_s0_2);
        var_s0_2 += 1;
      }
      while (var_s0_2 != 4);
      func_80023A20(0x13, new_var);
      func_80023A20(0x14, 0);
      func_80023A20(0x15, new_var);
    }
  }
  return *((s32 *) (&D_8006BBA0));
}

s32 Audio_GetFreeVoiceCount(void) {
    return mus_free_voices_count;
}

M2C_UNK func_8001FB10(s32, s32);                    /* extern */
M2C_UNK func_8001FE84();                            /* extern */
M2C_UNK func_800203FC(s32);                         /* extern */
M2C_UNK func_80058410(s32, s32, M2C_UNK);           /* extern */

void func_80023D3C(s32 arg0, s32 arg1) {
    s32 sp24;
    s32 temp_a0;

    func_8001FE84();
    func_800203FC(arg0);
    temp_a0 = arg1 + 0x27;
    sp24 = temp_a0;
    func_80058410(temp_a0, arg0 + 0x3D, 3);
    func_80058410(arg1 + 0x2A, arg0 + 0x4D, 3);
    func_8001FB10(arg0 + 0x30, arg1 + 0x21);
    func_8001FB10(arg0 + 0x40, sp24);
}

void func_80023DB8(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, u8*, 4) = M2C_FIELD(arg0, u8*, 0x24);
    Pokemon_ToGbRecord((BattleMon*)arg0, (GbPokemonRecord*)arg1);
    Text_TranscodeName((char*)(arg1 + 0x21), (char*)(arg0 + 0x30));
    func_80058410(arg0 + 0x3D, arg1 + 0x27, 3);
    func_80058410(arg0 + 0x4D, arg1 + 0x2A, 3);
}

#ifdef NON_MATCHING
/* TODO: decompile func_80023E28; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80023E28.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80023F38; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80023F38.s")
#endif

void func_80024044(void) {
}

void func_800238D8(); // Called with two or three arguments.
void func_8002404C(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16:
        func_800238D8((*(s32 *)&D_800AE8E0) + (arg1 * 0x250), 0x128, arg1);
        return;
    case 17:
        func_800238D8((*(s32 *)&D_800AE8E0) + (arg1 * 0xAC0) + 0x2500, 0x560, arg1);
        return;
    case 18:
        func_800238D8((*(s32 *)&D_800AE8E0) + (arg1 * 0x1C0) + 0x5000, 0xE0, arg1);
        return;
    case 19:
        func_800238D8((*(s32 *)&D_800AE8E0) + 0x5700, 0x11A0, arg1);
        return;
    case 20:
        func_800238D8((*(s32 *)&D_800AE8E0) + 0x7A40, 0x10, arg1);
        return;
    case 21:
        func_800238D8((*(s32 *)&D_800AE8E0) + 0x7A60, 0x288, arg1);
        /* fallthrough */
    default:
        return;
    }
}

void func_80023954(); // Called with three arguments; the third is ignored.
void func_80024170(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 16:
        func_80023954((*(s32 *)&D_800AE8E0) + (arg1 * 0x250), 0x128, arg1);
        return;
    case 17:
        func_80023954((*(s32 *)&D_800AE8E0) + (arg1 * 0xAC0) + 0x2500, 0x560, arg1);
        return;
    case 18:
        func_80023954((*(s32 *)&D_800AE8E0) + (arg1 * 0x1C0) + 0x5000, 0xE0, arg1);
        return;
    case 19:
        func_80023954((*(s32 *)&D_800AE8E0) + 0x5700, 0x11A0, arg1);
        return;
    case 20:
        func_80023954((*(s32 *)&D_800AE8E0) + 0x7A40, 0x10, arg1);
        return;
    case 21:
        func_80023954((*(s32 *)&D_800AE8E0) + 0x7A60, 0x288, arg1);
        /* fallthrough */
    default:
        return;
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_80024294; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80024294.s")
#endif

void func_800243B8(void) {
    s32 i;

    for (i = 0; i < 0x2500; i += 0x250) {
        func_800238D8(*(s32*)&D_800AE8E0 + i, 0x128);
    }
    for (i = 0; i < 0x2B00; i += 0xAC0) {
        func_800238D8(*(s32*)&D_800AE8E0 + i + 0x2500, 0x560);
    }
    for (i = 0; i < 0x700; i += 0x1C0) {
        func_800238D8(*(s32*)&D_800AE8E0 + i + 0x5000, 0xE0);
    }
    func_800238D8(*(s32*)&D_800AE8E0 + 0x5700, 0x11A0);
}

#ifdef NON_MATCHING
/* TODO: decompile func_80024470; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80024470.s")
#endif

void Save_ResetAndCommitTypedRecord(s32 arg0, s32 arg1) {
    Save_ClearTypedRecord(arg0, arg1);
    Save_CommitTypedRecord(arg0, arg1);
}

s32 func_80024610(s32 arg0) {
    s32 ret = 0;

    switch (arg0) {
        case 16:
            ret = 6;
            break;

        case 17:
            ret = 0x1E;
            break;

        case 18:
            ret = 0x64;
            break;

        case 19:
            ret = 0x64;
            break;
    }

    return ret;
}

s32 func_8002465C(s32 arg0) {
    s32 ret = 0;

    switch (arg0) {
        case 16:
            ret = 0x50;
            break;
        case 17:
            ret = 0x50;
            break;
        case 18:
            ret = 2;
            break;
        case 19:
            ret = 80;
            break;
    }
    return ret;
}

s32 Deck_IsSaveEntryPresent(s32 arg0, s32 arg1) {
    return Save_IsTypedRecordFlagSet(arg0, arg1, 1);
}

s32 func_800246A8(s32, s32);
s32 func_800246C8(s32 arg0, s32 arg1) {
    s32 ret = -1;

    if (func_800246A8(arg0, arg1) != 0) {
        switch (arg0) {
            case 16:
                ret = *(u16*)((*(s32*)&D_800AE8E0) + (arg1 * 0x250) + 8);
                break;
            case 17:
                ret = *(u16*)((*(s32*)&D_800AE8E0) + (arg1 * 0xAC0) + 0x2508);
                break;
            case 18:
                ret = *(u16*)((*(s32*)&D_800AE8E0) + (arg1 * 0x1C0) + 0x5008);
                break;
        }
    }
    return ret;
}

s32 func_800246A8(s32, s32);
s32 func_8002479C(s32 arg0, s32 arg1, u8* arg2) {
    s32 ret = 0;
    s32 src;

    *arg2 = 0;
    if (func_800246A8(arg0, arg1) != 0) {
        src = 0;
        switch (arg0) {
            case 16:
                src = (*(s32*)&D_800AE8E0) + (arg1 * 0x250) + 2;
                break;
            case 17:
                src = (*(s32*)&D_800AE8E0) + (arg1 * 0xAC0) + 0x2502;
                break;
            case 18:
                src = (*(s32*)&D_800AE8E0) + (arg1 * 0x1C0) + 0x5002;
                break;
        }
        if (src != 0) {
            ret = func_8001FB10((s32)arg2, src);
        }
    }
    return ret;
}

s32 func_800246A8(s32, s32);
s32 func_8002488C(s32 arg0, s32 arg1, u8* arg2) {
    s32 ret = 0;
    s32 src;

    *arg2 = 0;
    if (func_800246A8(arg0, arg1) != 0) {
        src = 0;
        switch (arg0) {
            case 16:
                src = (*(s32*)&D_800AE8E0) + (arg1 * 0x250) + 0xA;
                break;
            case 17:
                src = (*(s32*)&D_800AE8E0) + (arg1 * 0xAC0) + 0x250A;
                break;
        }
        if (src != 0) {
            ret = func_8001FB10((s32)arg2, src);
        }
    }
    return ret;
}

#ifdef NON_MATCHING
/* TODO: decompile func_80024954; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80024954.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80024ADC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80024ADC.s")
#endif

M2C_UNK func_80023F38(s32, s32, M2C_UNK);           /* extern */
s32 func_80024ADC();                                /* extern */

void func_80024B90(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 < func_80024ADC()) {
        switch (arg0) {                             /* irregular */
        case 16:
            M2C_FIELD((D_800AE8E0 + (arg1 * 0x250)), s16 *, 0x12) = (s16) arg2;
            break;
        case 17:
            M2C_FIELD((D_800AE8E0 + (arg1 * 0xAC0)), s16 *, 0x2512) = (s16) arg2;
            break;
        case 18:
            M2C_FIELD((D_800AE8E0 + (arg1 * 0x1C0)), s16 *, 0x500A) = (s16) arg2;
            break;
        case 19:
            M2C_FIELD(D_800AE8E0, s16 *, 0x5702) = (s16) arg2;
            break;
        }
        func_80023F38(arg0, arg1, 2);
    }
}

M2C_UNK func_80023F38(s32, s32, M2C_UNK);           /* extern */
s32 func_80024610(s32);                             /* extern */
s32 func_80024ADC();                                /* extern */

void func_80024C80(s32 arg0, s32 arg1) {
    s32 sp1C;

    sp1C = func_80024ADC();
    if (sp1C < func_80024610(arg0)) {
        switch (arg0) {                             /* irregular */
        case 16:
            M2C_FIELD((D_800AE8E0 + (arg1 * 0x250)), s16 *, 0x12) = (s16) (sp1C + 1);
            break;
        case 17:
            M2C_FIELD((D_800AE8E0 + (arg1 * 0xAC0)), s16 *, 0x2512) = (s16) (sp1C + 1);
            break;
        case 18:
            M2C_FIELD((D_800AE8E0 + (arg1 * 0x1C0)), s16 *, 0x500A) = (s16) (sp1C + 1);
            break;
        case 19:
            M2C_FIELD(D_800AE8E0, s16 *, 0x5702) = (s16) (sp1C + 1);
            break;
        }
        func_80023F38(arg0, arg1, 2);
    }
}

#ifdef NON_MATCHING
/* TODO: decompile func_80024D88; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80024D88.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_80024F14; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80024F14.s")
#endif

s32 func_80025100(s8 *arg0, s32 *arg1) {
    if (arg0 != NULL) {
        *arg0 = M2C_FIELD(D_800AE8E0, s8 *, 0x7A42);
    }
    if (arg1 != NULL) {
        *arg1 = M2C_FIELD(D_800AE8E0, s32 *, 0x7A44);
    }
    return 1;
}

M2C_UNK func_80023F38(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */

s32 func_80025130(s32 arg0) {
    M2C_FIELD(D_800AE8E0, s32 *, 0x7A44) = arg0;
    func_80023F38(0x14, 0, 2);
    return 1;
}

M2C_UNK func_80023F38(s32, s32, M2C_UNK);
M2C_UNK func_80023F38(M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_80025168(s8 arg0) {
    M2C_FIELD(D_800AE8E0, s8 *, 0x7A42) = arg0;
    func_80023F38(0x14, 0, 2);
    return 1;
}

s32 func_800251A8(void)
{
  return (((*((u8 *) (((s8 *) (*((s8 **) (&D_800AE8E0)))) + 0x7A48))) << 8) | (*((u8 *) (((s8 *) (*((s8 **) (&D_800AE8E0)))) + 0x7A49)))) & 0xFFFF;
}

#ifdef NON_MATCHING
/* TODO: decompile func_800251C8; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800251C8.s")
#endif

u8 func_80025214(void) {
    return M2C_FIELD(D_800AE8E0, u8 *, 0x7A43);
}

M2C_UNK func_80023F38(s32, s32, M2C_UNK);
M2C_UNK func_80023F38(M2C_UNK, M2C_UNK, M2C_UNK);
void func_80025224(s8 arg0) {
    M2C_FIELD(D_800AE8E0, s8 *, 0x7A43) = arg0;
    func_80023F38(0x14, 0, 2);
}

#ifdef NON_MATCHING
/* TODO: decompile func_80025260; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_80025260.s")
#endif

#ifdef NON_MATCHING
/* TODO: decompile func_800253BC; signature not recovered. */
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/1060/func_800253BC.s")
#endif
