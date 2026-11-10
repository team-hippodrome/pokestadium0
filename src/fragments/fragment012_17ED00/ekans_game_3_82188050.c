/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "m2c_macros.h"

extern u8* D_821CF29C;
extern s8* D_821CF2A0;
s32 func_82185220(u8 *arg0, u8 *arg1, s32 arg2);
s32 func_8218540C(s8 *arg0, s8 *arg1);
s32 func_82184BC8(s8 *arg0, s32 arg1);
s32 func_82184DC8(s8 *, s8 *, u8);

s32 func_82188050(s32 arg0) {
    s32 i;
    s32 tier;
    s32 best;
    s32 threshold;
    s32 v;
    u8 move;

    if (arg0 >= 0 && arg0 < 4 && func_82185220((u8*)D_821CF2A0, D_821CF29C, 0) < M2C_FIELD(D_821CF29C, u16*, 0x18) && (D_821CF29C + arg0)[0x2B] == 0x3F) {
        threshold = M2C_FIELD(D_821CF2A0, u16*, 0x18) - func_82184DC8((s8*)D_821CF29C + 0xC, D_821CF2A0 + 0xC, 0x3F) * 9 / 10;
        best = -1;
        if (threshold > 0) {
            for (tier = 0; tier < 4; tier++) {
                for (i = 0; i < 4; i++) {
                    if ((D_821CF29C + i)[0x2B] == 0) {
                        break;
                    }
                    if (func_8218540C((s8*)D_821CF29C, D_821CF2A0) != 0 || (D_821CF29C + i)[0x2B] == 0x62) {
                        move = (D_821CF29C + i)[0x2B];
                        switch (move) {
                            case 0x14:
                            case 0x15:
                            case 0x19:
                            case 0x38:
                            case 0x42:
                            case 0x79:
                            case 0x80:
                            case 0x9A:
                                if (tier < 3) {
                                    break;
                                }
                            case 0x03:
                            case 0x04:
                            case 0x05:
                            case 0x1B:
                            case 0x1F:
                            case 0x23:
                            case 0x24:
                            case 0x2A:
                            case 0x31:
                            case 0x3B:
                            case 0x43:
                            case 0x7D:
                            case 0x7E:
                            case 0x88:
                            case 0x8C:
                            case 0x98:
                            case 0x9B:
                            case 0x9D:
                            case 0x9E:
                            case 0xA2:
                                if (tier < 2) {
                                    break;
                                }
                            case 0x0F:
                            case 0x13:
                            case 0x1A:
                            case 0x21:
                            case 0x4B:
                                if (tier < 1) {
                                    break;
                                }
                            case 0x01:
                            case 0x02:
                            case 0x06:
                            case 0x07:
                            case 0x08:
                            case 0x09:
                            case 0x0A:
                            case 0x0B:
                            case 0x10:
                            case 0x11:
                            case 0x16:
                            case 0x17:
                            case 0x18:
                            case 0x1D:
                            case 0x1E:
                            case 0x22:
                            case 0x26:
                            case 0x28:
                            case 0x29:
                            case 0x2C:
                            case 0x33:
                            case 0x34:
                            case 0x35:
                            case 0x37:
                            case 0x39:
                            case 0x3A:
                            case 0x3C:
                            case 0x3D:
                            case 0x3E:
                            case 0x40:
                            case 0x41:
                            case 0x45:
                            case 0x46:
                            case 0x47:
                            case 0x48:
                            case 0x52:
                            case 0x54:
                            case 0x55:
                            case 0x59:
                            case 0x5B:
                            case 0x5D:
                            case 0x5E:
                            case 0x62:
                            case 0x65:
                            case 0x7A:
                            case 0x7C:
                            case 0x7F:
                            case 0x81:
                            case 0x83:
                            case 0x84:
                            case 0x8D:
                            case 0x91:
                            case 0x92:
                            case 0xA1:
                            case 0xA3:
                                v = func_82184DC8((s8*)D_821CF29C + 0xC, D_821CF2A0 + 0xC, move) * 9 / 10;
                                if (best < v && threshold < v) {
                                    best = v;
                                    arg0 = i;
                                }
                                break;
                        }
                    }
                }
            }
        }
    }
    return arg0;
}

s32 func_8218824C(s32 arg0) {
    s32 i;
    s32 best = -1;
    s32 bestIdx = -1;
    s32 v;

    for (i = 0; i < 4; i++) {
        if ((D_821CF29C + i)[0x2B] == 0) {
            break;
        }
        if (func_82184BC8((s8*)D_821CF29C, (D_821CF29C + i)[0x2B]) != 0) {
            v = func_82184DC8((s8*)D_821CF29C + 0xC, D_821CF2A0 + 0xC, (D_821CF29C + i)[0x2B]);
            if (best < v) {
                best = v;
                bestIdx = i;
            }
        }
    }
    best = best * 9 / 10;
    if ((M2C_FIELD(D_821CF2A0, u16 *, 0x18) != 0) && (arg0 < (best * 100) / M2C_FIELD(D_821CF2A0, u16 *, 0x18))) {
        return bestIdx;
    }
    return -1;
}

extern void *D_821CF294;
s32 func_82183CE4(s8 *);
s32 func_82183D50(void *);
s32 func_82184CE0(s8 *);
s32 func_82185450(s8 *, s8 *);
s32 func_821854AC(s8 *);
s32 func_821857CC(s8 *);
s32 func_821858DC(s8 *);
s32 func_82185A30(s8 *);
s32 func_82185BE0(s8 *, s8 *);
s32 func_82185D44(u8);
s32 func_82186394(s8 *, s8 *);
s32 func_821864D4(s8 *, s8 *);
s32 func_8218663C(s8 *, s8 *);
s32 func_82188394(void)
{
  s32 r;
  s32 i;
  s32 j;

  func_8218540C((s8 *) D_821CF29C, D_821CF2A0);
  r = -1;
  if ((func_8218540C((s8 *) D_821CF29C, D_821CF2A0) != 0) && (func_82185450((s8 *) D_821CF29C, D_821CF2A0) == 0) && (!(((u8 *) D_821CF2A0)[0x21] & 0x27)) && (func_8218824C(func_82183CE4(D_821CF2A0)) != 0))
  {
    r = func_821858DC((s8 *) D_821CF29C);
  }
  if (r < 0)
  {
    if (func_82185450((s8 *) D_821CF29C, D_821CF2A0) != 0)
    {
      r = func_821854AC((s8 *) D_821CF29C);
    }
    else
    {
      r = func_82185A30((s8 *) D_821CF29C);
      if (r < 0)
      {
        r = func_82186394((s8 *) D_821CF29C, D_821CF2A0);
      }
      if (r < 0)
      {
        r = func_821864D4((s8 *) D_821CF29C, D_821CF2A0);
      }
      if ((r < 0) && ((func_82184CE0(D_821CF2A0) != 0) || (func_82183CE4(D_821CF2A0) >= 0x15)))
      {
        r = func_82185BE0((s8 *) D_821CF29C, D_821CF2A0);
      }
    }
  }
  if (r < 0)
  {
    r = func_8218824C(0x32);
    if ((r < 0) && ((func_8218824C(0x1E) != 0) || (func_82184CE0(D_821CF2A0) != 0)) && ((func_82183CE4(D_821CF2A0) >= 0x33) || (func_82183CE4((s8 *) D_821CF29C) >= 0x51)))
    {
      r = func_821857CC((s8 *) D_821CF29C);
    }
  }
  if (r < 0)
  {
    if ((((func_8218540C((s8 *) D_821CF29C, D_821CF2A0) != 0) && (func_82183CE4((s8 *) D_821CF29C) < 0x14)) || ((func_8218540C((s8 *) D_821CF29C, D_821CF2A0) == 0) && ((M2C_FIELD(D_821CF29C, u16 *, 0x18) / 2) < ((func_82185220((u8 *) D_821CF2A0, D_821CF29C, 0) * 0x5A) / 100))) || ((func_82184CE0((s8 *) D_821CF29C) == 0) && (func_82183CE4((s8 *) D_821CF29C) < 0x28))) && (func_82183D50(D_821CF294) >= 2))
    {
      r = func_8218663C((s8 *) D_821CF29C, D_821CF2A0);
    }
    if (r < 0)
    {
      r = func_8218824C(0);
    }
  }
  r = func_82188050(r);
  if (r < 0)
  {
    for (j = 0; (j < 10) && (r < 0); j++)
    {
      for (i = 0; i < 4; i++)
      {
        if ((D_821CF29C + i)[0x2B] == 0)
        {
          break;
        }
        if ((func_82184BC8((s8 *) D_821CF29C, (D_821CF29C + i)[0x2B]) != 0) && ((j != 0) || (func_82185D44((D_821CF29C + i)[0x2B]) != 0)))
        {
          r = i;
          break;
        }
      }
    }
  }
  if (r < 0)
  {
    r = 0;
  }
  return r;
}


/**
 * Searches for another entry that matches entry arg0 in the per-entry byte tables
 * addressed through D_821CF29C (the byte at +0x2B + index and the byte at +0x3E + index,
 * index 0..3). If the +0x3E byte of arg0 has any of the bits 0x3F set, returns arg0.
 * Otherwise scans indices 0..3 in order: stops and returns arg0 at the first index
 * whose +0x2B byte is zero; skips index arg0; and returns the first other index whose
 * +0x2B byte equals that of arg0 and whose +0x3E byte has any of bits 0x3F set.
 * Returns arg0 when no such index is found. What the tables mean is not established.
 */
s32 func_821886F0(s32 arg0) {
    s32 i;
    u8* base;
    u8* cur;
    u8* me;
    u8 v;

    base = D_821CF29C;
    me = base + arg0;
    i = 0;
    if (!(me[0x3E] & 0x3F)) {
        cur = base;
        do {
            v = cur[0x2B];
            if (v == 0) {
                break;
            }
            if ((i != arg0) && (v != 0) && (v == me[0x2B]) && (cur[0x3E] & 0x3F)) {
                return i;
            }
            i++;
            cur++;
        } while (i != 4);
    }
    return arg0;
}

extern f64 D_DBL_82198A10;
extern s32 D_821CF2A4;
extern u8 *D_821CF2A8;
extern u8 *D_821CF2AC;
typedef struct Slot90 { u8 *roster; u8 data[0x8C]; } Slot90;
extern Slot90 D_821CF618[6];
extern Slot90 D_821CF998[6];
extern Slot90 *D_821CF298;
extern s32 D_821CF288;
void func_80058410(u8 *, u8 *, s32);
void func_821869C4(s8 *, u8 *);
void func_82185378(u8 *, u8 *);
s32 func_821879A4(void);
s32 func_82187DB4(void);
/**
 * AI action choice: sets up the current/opponent slot pointers,
 * updates per-turn bookkeeping, then picks an action (a move index 0-3, or
 * 4 + party slot to switch) and stores it in D_821CF2A4.
 */
s32 func_82188770(u8* arg0, u8* arg1, s32 arg2, s32 arg3) {
    s32 move;
    s32 r;
    s32 one; // FAKE

    D_821CF294 = D_821CF618;
    D_821CF298 = D_821CF998;
    D_821CF29C = ((Slot90*)D_821CF294)[arg2].data;
    D_821CF2A0 = (s8*)D_821CF298[arg3].data;
    D_821CF2A8 = arg0;
    D_821CF2AC = arg1;
    func_80058410(arg0, D_821CF29C + 0xC, 0x64);
    if (M2C_FIELD(D_821CF29C, u16*, 0x18) != M2C_FIELD(D_821CF29C, u16*, 0x70)) {
        if (D_821CF29C[0x67] != 0) {
            M2C_FIELD(D_821CF29C, s16*, 0x72) = (M2C_FIELD(D_821CF29C, u16*, 0x70) - M2C_FIELD(D_821CF29C, u16*, 0x18)) / 2;
        } else {
            M2C_FIELD(D_821CF29C, s16*, 0x72) = M2C_FIELD(D_821CF29C, u16*, 0x70) - M2C_FIELD(D_821CF29C, u16*, 0x18);
        }
        M2C_FIELD(D_821CF29C, u16*, 0x70) = M2C_FIELD(D_821CF29C, u16*, 0x18);
    }
    func_821869C4(D_821CF2A0 + 0xC, arg1);
    if (D_821CF29C[0x5A] & 1) {
        D_821CF29C[0x7A]++;
    } else {
        D_821CF29C[0x7A] = 0;
    }
    if (M2C_FIELD(D_821CF294, f32*, 0x364) >= 0.5) {
        M2C_FIELD(D_821CF294, f32*, 0x364) -= D_DBL_82198A10;
    }
    if (arg3 != ((u8*)D_821CF294)[0x369]) {
        move = ((u8*)D_821CF294)[0x369];
        if (move < D_821CF288) {
            func_82185378(D_821CF298[((u8*)D_821CF294)[0x369]].data + 0xC, D_821CF298->roster + move * 0x50 + 0x1C);
        }
        ((u8*)D_821CF294)[0x369] = arg3;
        ((u8*)D_821CF294)[0x36A] = 0;
    } else {
        ((u8*)D_821CF294)[0x36A]++;
    }
    for (move = 0; move < D_821CF288; move++) {
        ((u8*)D_821CF294)[move * 0x90 + 0x7F] = arg0[move + 0x16];
        D_821CF298[move].data[0x7B] = arg1[move + 0x16];
    }

    move = func_821879A4();
    if ((move >= 0) && (D_821CF29C[0x75] != ((one = 1) << move))) { // FAKE: one
        r = -1;
        if ((M2C_FIELD(D_821CF29C, u16*, 0x18) != 0) && (func_82183CE4((s8*)D_821CF29C) < 0x23) &&
            (func_82183D50(D_821CF294) >= 2) && (func_8218663C((s8*)D_821CF29C, D_821CF2A0) >= 0)) {
            r = func_8218663C((s8*)D_821CF29C, D_821CF2A0);
        }
        if (r < 0) {
            func_82185378(D_821CF29C + 0xC, *(u8**)D_821CF294 + move * 0x50 + 0x1C);
            r = move + 4;
        }
    } else if ((((u8*)D_821CF294)[0x368] == 3) && (func_82183CE4(D_821CF2A0) >= 0x1F)) {
        r = func_82187DB4();
    } else {
        r = func_82188394();
    }
    if ((r >= 0) && (r < 4) && (r < 4)) { // FAKE: repeated r < 4
        r = func_821886F0(r);
    }
    D_821CF2A4 = r;
    return r;
}

extern s32 D_821CF2A4;
extern u8* D_821CF2A8;
extern u8* D_821CF2AC;
extern u8 D_8006B18F[];

void func_82188B8C(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 pp;
    s32 bonus;
    s32 move;

    if (D_821CF2A4 == 0xFEDC) {
        return;
    }
    move = D_821CF2AC[0x5A];
    if (move != 0) {
        for (i = 0; i < 4; i++) {
            if (((u8*)D_821CF2A0)[0x2B + i] == 0) {
                ((u8*)D_821CF2A0)[0x2B + i] = move;
                pp = D_8006B18F[D_821CF2AC[0x5A] * 6];
                bonus = (pp / 5 >= 8) ? 7 : pp / 5;
                pp += bonus * 3;
                ((u8*)D_821CF2A0)[0x3E + i] = pp - 1;
                break;
            }
            if ((move == ((u8*)D_821CF2A0)[0x2B + i]) && ((pp = ((u8*)D_821CF2A0)[0x3E + i]) != 0)) {
                ((u8*)D_821CF2A0)[0x3E + i] = pp - 1;
                break;
            }
        }
    }
    if ((arg2 < 2) && (D_821CF2A4 < 4) && ((D_821CF29C + D_821CF2A4)[0x2B] == 0x49)) {
        D_821CF29C[0x77] |= ((u8*)D_821CF2A0)[0x75];
    }
    if (arg2 < 2) {
        D_821CF29C[0x7E] = D_821CF29C[0x7D];
        D_821CF29C[0x7D] = D_821CF29C[0x7C];
        D_821CF29C[0x7C] = D_821CF29C[0x66];
    }
    if (!(D_821CF2AC[0x4E] & 8)) {
        if (arg2 == 0) {
            if (((D_821CF2A8[0x5A] != 0x62) || (D_821CF2AC[0x5A] == 0x62)) && ((D_821CF2A8[0x5A] == 0x44) || (D_821CF2AC[0x5A] != 0x44))) {
                D_821CF29C[0x76] |= ((u8*)D_821CF2A0)[0x75];
            }
        } else if (arg2 == 1) {
            if (((D_821CF2AC[0x5A] != 0x62) || (D_821CF2A8[0x5A] == 0x62)) && ((D_821CF2AC[0x5A] == 0x44) || (D_821CF2A8[0x5A] != 0x44))) {
                D_821CF29C[0x76] &= ~((u8*)D_821CF2A0)[0x75];
            }
        }
    }
}
