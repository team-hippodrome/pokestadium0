/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_347330.h"

/**
 * Part of the stat-change ribbon (see StatRibbon_Spawn).
 * @unverified Named after the ribbon seen in play; this function itself was not traced.
 */
void StatRibbon_Init(void) {
    RibbonMesh* ptr = &D_8219CB20[0];
    s32 i;

    for (i = 0; i < 4; i++) {
        ptr->unk_018 = ptr->unk_000 = 0;
        ptr++;
    }
}

/**
 * @unverified Named after the ribbon seen in play; this function itself was not traced.
 */
void StatRibbon_Configure(RibbonMesh* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                   s32 arg9) {
    arg0->unk_028 = arg1;
    arg0->unk_02C = arg2;
    arg0->unk_030 = arg3;
    arg0->unk_038 = arg4;
    arg0->unk_03C = arg5;
    arg0->unk_040 = arg6;
    arg0->unk_024 = arg7;
    arg0->unk_034 = arg8;
    arg0->unk_044 = arg9;
}


/**
 * Spawns one stat-change ribbon in a free slot of the 4-entry pool, centred on (arg0, arg1, arg2)
 * with radius arg3 and scale arg4. arg5 picks the direction: 0 is the rising ribbon used when a
 * stat goes up, 1 the falling curtain used when a stat goes down (Haze spawns both).
 * Seen in play (2026-11-13) in the per-move sweep it ran for 23 moves: every stat-raising and stat-
 * lowering move plus Mist and Haze. On screen (Swords Dance) a translucent pale-yellow wavy band
 * rose around the user while the attack-rose message showed; for Growl a brownish curtain came down
 * from the top of the screen in front of the target.
 */
void StatRibbon_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    RibbonMesh* ptr;
    RibbonMeshVertexState* ptr1;
    RibbonMeshVertexState* ptr2;
    RibbonMeshVertexState* ptr3;
    s32 i;
    u8 temp_lo;
    u8 temp_lo_2;
    s32 temp_v0_2;
    s32 var_v1;
    u8 temp_a0;
    u8 temp_a1;
    u8 temp_v1;

    var_v1 = -1;

    for (i = 0; i < 4; i++) {
        if (D_8219CB20[i].unk_000 == 0) {
            var_v1 = i;
            break;
        }
    }

    if (var_v1 == -1) {
        return;
    }

    ptr = &D_8219CB20[var_v1];

    ptr->unk_000 = 1;
    ptr->unk_018 = 0;
    ptr->unk_004 = arg0;
    ptr->unk_00C = arg2;
    ptr->unk_010 = arg3 * arg4;
    ptr->unk_014 = arg4;
    ptr->unk_01E = -1;

    switch (arg5) {
        case 0:
            ptr->unk_01C = 1;
            ptr->unk_008 = (arg4 * 0.0) + arg1;
            ptr->unk_01A = 0x3C;
            ptr->unk_020 = 1.5f;
            StatRibbon_Configure(&D_8219CB20[var_v1], 0xFF, 0xFF, 0xC8, 0x20, 0x20, 0xFF, 0x80, 0x80, 0xFF);
            ptr->unk_01E = AuxiliaryEffect_Alloc();
            break;

        case 1:
            ptr->unk_01C = -1;
            ptr->unk_01A = 0x78;
            ptr->unk_008 = (arg4 * 100.0) + arg1;
            ptr->unk_020 = 1.5f;
            StatRibbon_Configure(&D_8219CB20[var_v1], 0xFF, 0xFF, 0xC8, 0xFF, 0x20, 0x20, 0x80, 0x80, 0);
            break;

        default:
        case 2:
            ptr->unk_01C = 1;
            ptr->unk_008 = (arg4 * 0.0) + arg1;
            ptr->unk_01A = 0x1E;
            ptr->unk_020 = 1.5f;
            break;
    }

    ptr1 = &ptr->unk_430[0];
    for (i = 0; i < 31; i++) {
        ptr2 = ptr1++;
        ptr3 = ptr1++;

        switch (arg5) {
            case 0:
                temp_v0_2 = ((i % 3) * 2) + 1;
                temp_lo = 0x44 / temp_v0_2;
                temp_lo_2 = 0xFF / temp_v0_2;

                ptr2->unk_10.r = 0x66;
                ptr2->unk_10.g = ((temp_lo * 6) + 0x3FC) / 10;
                ptr2->unk_10.b = ((temp_lo_2 * 6) + 0x3FC) / 10;
                ptr2->unk_10.a = 0xFF;

                ptr3->unk_10.r = 0;
                ptr3->unk_10.g = temp_lo;
                ptr3->unk_10.b = temp_lo_2;
                ptr3->unk_10.a = 0;

                ptr2->unk_0E = 0x20;
                ptr3->unk_0E = 0x7E0;
                break;

            case 1:
                temp_v0_2 = ((i % 3) * 2) + 1;
                temp_lo = 0xFF / temp_v0_2;
                temp_lo_2 = 0x44 / temp_v0_2;

                ptr2->unk_10.r = ((temp_lo * 4) + 0x5FA) / 10;
                ptr2->unk_10.g = ((temp_lo_2 * 4) + 0x5FA) / 10;
                ptr2->unk_10.b = 0x99;
                ptr2->unk_10.a = 0x10;

                ptr3->unk_10.r = temp_lo;
                ptr3->unk_10.g = temp_lo_2;
                ptr3->unk_10.b = 0;
                ptr3->unk_10.a = 0;

                ptr2->unk_0E = 0x7E0;
                ptr3->unk_0E = 0x20;
                break;

            default:
            case 2:
                temp_v1 = (((u32)(i & 0x3F) >> 4) & 3) << 6;
                temp_a0 = (((u32)(i & 0x3F) >> 2) & 3) << 6;
                temp_a1 = ((u32)(i & 0x3F) & 3) << 6;

                ptr2->unk_10.r = ((temp_v1 * 6) + 0x3FC) / 10;
                ptr2->unk_10.g = ((temp_a0 * 6) + 0x3FC) / 10;
                ptr2->unk_10.b = ((temp_a1 * 6) + 0x3FC) / 10;
                ptr2->unk_10.a = 0xFF;

                ptr3->unk_10.r = temp_v1;
                ptr3->unk_10.g = temp_a0;
                ptr3->unk_10.b = temp_a1;
                ptr3->unk_10.a = 0;

                ptr2->unk_0E = 0x20;
                ptr3->unk_0E = 0x7E0;
                break;
        }

        ptr2->unk_0C = ((i % 31) * 0x3000) / 30;
        ptr3->unk_0C = ptr2->unk_0C;
        ptr2->unk_18 = 0.0f;
        ptr2->unk_14 = (i * TWO_PI) / 30.0;
        ptr2->unk_00 = (__cosf((i * TWO_PI) / 30.0) * (arg3 * arg4)) + arg0;
        ptr2->unk_04 = ptr->unk_008;

        if (ptr2->unk_04 < 0.0) {
            ptr2->unk_04 = 0.0f;
        }
        ptr2->unk_08 = (__sinf(ptr2->unk_14) * (arg3 * arg4)) + arg2;

        ptr3->unk_18 = 0.0f;
        ptr3->unk_14 = ptr2->unk_14;
        ptr3->unk_00 = ptr2->unk_00;
        ptr3->unk_04 = ptr->unk_008;
        if (ptr3->unk_04 < 0.0) {
            ptr3->unk_04 = 0.0f;
        }

        ptr3->unk_08 = ptr2->unk_08;
    }
}
