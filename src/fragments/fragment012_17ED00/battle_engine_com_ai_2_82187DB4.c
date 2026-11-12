/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "fragments/particle_math/particle_math.h"
#include "jpeg_stream.h"
#include "controller.h"

struct BattleSlotZ;
extern struct BattleSlotZ* D_821CF294;
extern struct BattleSlotZ* D_821CF298;
extern u8* D_821CF29C;
extern s8* D_821CF2A0;

s32 func_82187DB4(void) {
    s32 byte;
    s32 i;
    s32 acc;
    u8 slots[4];
    s32 cnt;

    for (i = 0; i < 4; i++) {
        slots[i] = 0;
    }
    acc = 0;
    for (i = 0; i < 4; i++) {
        byte = D_821CF29C[i + 0x2B];
        if (byte == 0) {
            break;
        }
        if ((D_821CF29C[i + 0x2B] != 0) && ((D_821CF29C[i + 0x3E] & 0x3F) != 0) && (D_821CF29C[0x63] != D_821CF29C[i + 0x2B])) {
            slots[i] = byte;
        } else {
            slots[i] = 0;
        }
        acc |= slots[i];
    }
    if (acc == 0) {
        return 0;
    }
    cnt = 0;
    i = func_82183AF0() % 4;
    while (cnt != 100) {
        if (slots[i] != 0) {
            switch (slots[i]) {
                case 0x78:
                case 0x99:
                    if ((cnt < 0xA) && (func_82183CE4((s8 *) D_821CF29C) >= 0x33)) {
                        break;
                    }
                    if ((cnt < 0x32) && (func_82183AF0() < 0x5F)) {
                        break;
                    }
                    if ((cnt < 0x50) && (func_82183D50((u8 *) D_821CF294) == 1)) {
                        break;
                    }
                    return i;
                case 0x2F:
                case 0x4F:
                case 0x5F:
                case 0x8E:
                case 0x93:
                    if ((cnt < 0x1E) && (func_821855F0(D_821CF298) == 0)) {
                        break;
                    }
                    return i;
                case 0x69:
                case 0x87:
                case 0x9C:
                    if ((cnt < 0x32) && (func_82183CE4((s8 *) D_821CF29C) >= 0x5B)) {
                        break;
                    }
                    return i;
                case 0x8A:
                    if ((cnt < 0x32) && ((((u8 *) D_821CF2A0)[0x21] & 7) == 0)) {
                        break;
                    }
                    if ((cnt < 0x32) && ((((u8 *) D_821CF2A0)[0x21] & 7) != 0) && (func_82183AF0() < 0x50) && (func_82183D50((u8 *) D_821CF298) != 1)) {
                        break;
                    }
                    return i;
                default:
                    return i;
            }
        }
        i++;
        cnt++;
        i = i % 4;
    }
    return 0;
}
