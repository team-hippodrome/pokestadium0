/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/table_view.c. */

#include "table_view.h"

void TableView_Initialize(unk_func_88201DA0_038* arg0, unk_func_88201DA0_034* arg1, s32 arg2, s32 arg3, s32 arg4);
s32 ByteMatrix_AppendRow(unk_func_8820BE14_06C* arg0, s8* a1);
s32 ByteMatrix_InsertRow(unk_func_8820BE14_06C* arg0, s8* arg1, s32 arg2);
s32 ByteMatrix_RemoveRow(unk_func_8820BE14_06C* arg0, s32 arg1);
s32 ByteMatrix_CopyRow(unk_func_8820BE14_06C* arg0, s8* a1, s32 arg2);
s32 ByteMatrix_CopyRowAt(unk_func_8820BE14_06C* arg0, s8* a1, s32 arg2);
s32 WordList_Remove(unk_func_8830867C_04C_030_02C_000_000_00C* arg0, s32 arg1);
void PointerList_Initialize(unk_func_88205880_A030* arg0, void** arg1, s32 arg2, s32 arg3);
void PointerList_Insert(unk_func_88200FA0_030_038* arg0, char* arg1, s32 arg2);
void PointerList_Remove(unk_func_8830867C_02C_0CC* arg0, s32 arg1);
void PointerList_SwapRange(void** arg0, void** arg1, s32 arg2);
s32* Sort_SelectMedianPointer(s32* arg0, s32* arg1, s32* arg2, s32 (*arg3)(s32, s32));
void Sort_QuickSort(void** base, s32 n, s32 (*cmp)(s32, s32));
void PointerList_Sort(unk_func_8830867C_02C_0CC* arg0, s32 (*arg1)(s32, s32));
void PointerList_Filter(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_0CC* arg1,
                   s32 (*arg2)(unk_func_8830867C_02C_0CC_000*, s32*), s32* arg3);
s32 Text_CompareU16Terminated(u16* a0, u16* a1);
s32 Text_CompareGlyphCodes(u8* a0, u8* a1);

/** Initializes a table view over a data table with the given dimensions. */
void TableView_Initialize(unk_func_88201DA0_038* arg0, unk_func_88201DA0_034* arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0->unk_00 = arg1;
    arg0->unk_0C = arg2;
    arg0->unk_04 = arg3;
    arg0->unk_08 = arg4;
}

/** Appends a row to a byte matrix. */
s32 ByteMatrix_AppendRow(unk_func_8820BE14_06C* arg0, s8* a1) {
    s8* var_v0;
    s32 i;
    s8* arg1;

    if (arg0->unk_08 >= arg0->unk_04) {
        return 1;
    }

    var_v0 = (u8*)arg0->unk_00 + (arg0->unk_0C * arg0->unk_08);
    arg1 = a1;

    for (i = arg0->unk_0C; i > 0; i--) {
        *var_v0++ = *arg1++;
    }

    arg0->unk_08++;
    return 0;
}

/** Inserts a row into a byte matrix at an index. */
s32 ByteMatrix_InsertRow(unk_func_8820BE14_06C* arg0, s8* arg1, s32 arg2) {
    s32 var_t1;
    s8* var_t0;
    s8* var_v1;

    if ((arg0->unk_08 >= arg0->unk_04) || (arg0->unk_08 < arg2)) {
        return 1;
    }

    var_v1 = (s8*)arg0->unk_00 + (arg0->unk_0C * arg0->unk_08);
    var_t0 = var_v1 + arg0->unk_0C;
    var_t1 = (arg0->unk_08 - arg2) * arg0->unk_0C;

    while (var_t1 > 0) {
        *--var_t0 = *--var_v1;
        var_t1--;
    }

    var_v1 = arg1;
    var_t1 = arg0->unk_0C;
    var_t0 = (u8*)arg0->unk_00 + (arg0->unk_0C * arg2);

    while (var_t1 > 0) {
        *var_t0++ = *var_v1++;
        var_t1--;
    }

    arg0->unk_08 += 1;
    return 0;
}

/** Removes a row from a byte matrix. */
s32 ByteMatrix_RemoveRow(unk_func_8820BE14_06C* arg0, s32 arg1) {
    s32 var_t0;
    s8* var_a3;
    s8* var_v1;

    if (arg1 >= arg0->unk_08) {
        return 1;
    }

    var_v1 = (s8*)arg0->unk_00 + (arg0->unk_0C * arg1);

    arg0->unk_08--;

    var_a3 = arg0->unk_0C + var_v1;
    var_t0 = (arg0->unk_08 - arg1) * arg0->unk_0C;

    while (var_t0 > 0) {
        *var_v1++ = *var_a3++;
        var_t0--;
    }

    return 0;
}

/** Copies a row into a byte matrix. */
s32 ByteMatrix_CopyRow(unk_func_8820BE14_06C* arg0, s8* a1, s32 arg2) {
    s8* var_v0;
    s32 i;
    s8* arg1;

    if (arg2 >= arg0->unk_08) {
        return 1;
    }

    var_v0 = (s8*)arg0->unk_00 + (arg0->unk_0C * arg2);
    arg1 = a1;

    for (i = arg0->unk_0C; i > 0; i--) {
        *arg1++ = *var_v0++;
    }

    return 0;
}

/** Copies a row into a byte matrix at an index. */
s32 ByteMatrix_CopyRowAt(unk_func_8820BE14_06C* arg0, s8* a1, s32 arg2) {
    s8* var_v0;
    s32 i;
    s8* arg1;

    if (arg2 >= arg0->unk_08) {
        return 1;
    }

    var_v0 = (s8*)arg0->unk_00 + (arg0->unk_0C * arg2);
    arg1 = a1;

    for (i = arg0->unk_0C; i > 0; i--) {
        *var_v0++ = *arg1++;
    }

    return 0;
}

/** Removes an entry from a list of 16-bit values. */
s32 WordList_Remove(unk_func_8830867C_04C_030_02C_000_000_00C* arg0, s32 arg1) {
    s16* var_a2;
    s32 var_a3;
    s16* var_v1;

    if (arg1 >= arg0->unk_08) {
        return 1;
    }

    var_v1 = (s16*)arg0->unk_00 + arg1;

    arg0->unk_08--;

    var_a2 = var_v1 + 1;
    var_a3 = arg0->unk_08 - arg1;

    while (var_a3 > 0) {
        *var_v1++ = *var_a2++;
        var_a3--;
    }

    return 0;
}

/** Initializes a pointer list over a given array. */
void PointerList_Initialize(unk_func_88205880_A030* arg0, void** arg1, s32 arg2, s32 arg3) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
    arg0->unk_08 = arg3;
}

/** Inserts a pointer into a pointer list at an index. */
void PointerList_Insert(unk_func_88200FA0_030_038* arg0, char* arg1, s32 arg2) {
    s32 var_t1;
    unk_func_88205880_00D0** var_t0;
    unk_func_88205880_00D0** var_v0;

    var_v0 = &arg0->unk_00[arg0->unk_08];
    var_t0 = var_v0 + 1;
    var_t1 = arg0->unk_08 - arg2;

    while (var_t1 > 0) {
        *--var_t0 = *--var_v0;
        var_t1--;
    }

    arg0->unk_00[arg2] = arg1;
    arg0->unk_08++;
}

/** Removes a pointer from a pointer list. */
void PointerList_Remove(unk_func_8830867C_02C_0CC* arg0, s32 arg1) {
    s32 var_a2;
    unk_func_8830867C_02C_0CC_000** var_v0;
    unk_func_8830867C_02C_0CC_000** var_v1;

    var_v0 = &arg0->unk_00[arg1];
    var_v1 = var_v0 + 1;

    arg0->unk_08--;

    var_a2 = arg0->unk_08 - arg1;

    while (var_a2 > 0) {
        *var_v0++ = *var_v1++;
        var_a2--;
    }
}

/** Swaps two ranges of pointers. */
void PointerList_SwapRange(void** arg0, void** arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        void* tmp = *arg0;
        *arg0++ = *arg1;
        *arg1++ = tmp;
    }
}

/** Returns the median of three pointers according to a comparison function. */
s32* Sort_SelectMedianPointer(s32* arg0, s32* arg1, s32* arg2, s32 (*arg3)(s32, s32)) {
    return (arg3(*arg0, *arg1) < 0)   ? (arg3(*arg1, *arg2) < 0)   ? arg1
                                        : (arg3(*arg0, *arg2) < 0) ? arg2
                                                                   : arg0
           : (arg3(*arg1, *arg2) > 0) ? arg1
           : (arg3(*arg0, *arg2) > 0) ? arg2
                                      : arg0;
}

/** Sorts an array of pointers with a quicksort using a comparison function. */
void Sort_QuickSort(void** base, s32 n, s32 (*cmp)(s32, s32)) {
    void** sp8C;
    s32 temp_s2;
    void* temp_s4;
    s32 temp_s4_2;
    void* temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_6;
    s32 var_a2_2;
    s32 var_v0;
    void** var_a2;
    void** var_s0;
    void** var_s0_2;
    void** var_s1;
    void** var_s1_2;
    void** var_s2;
    void** var_s2_2;
    void** var_s3;
    void** var_s6;

    if (n < 7) {
        for (var_s1 = base; var_s1 < base + n; var_s1++) {
            var_s0 = var_s1;
            if ((base < var_s1) && (cmp(*(var_s1 - 1), *var_s1) > 0)) {
                while (1) {
                    temp_v0 = *var_s0;
                    *(var_s0) = *(var_s0 - 1);
                    *(var_s0 - 1) = temp_v0;
                    var_s0--;
                    if (base < var_s0) {
                        if (cmp(*(var_s0 - 1), *var_s0) > 0) {
                            continue;
                        }
                    }
                    break;
                }
            }
        }
        return;
    }

    sp8C = base + (n / 2);
    if (n >= 8) {
        var_s2 = base;
        var_a2 = (base + n) - 1;
        if (n >= 0x29) {
            temp_v0_2 = n / 8;
            var_s2 = (void**)Sort_SelectMedianPointer((s32*)base, (s32*)(base + temp_v0_2), (s32*)(base + temp_v0_2 * 2), cmp);
            sp8C = (void**)Sort_SelectMedianPointer((s32*)(sp8C - temp_v0_2), (s32*)sp8C, (s32*)(sp8C + temp_v0_2), cmp);
            var_a2 = (void**)Sort_SelectMedianPointer((s32*)(var_a2 - temp_v0_2 * 2), (s32*)(var_a2 - temp_v0_2), (s32*)var_a2, cmp);
        }
        sp8C = (void**)Sort_SelectMedianPointer((s32*)var_s2, (s32*)sp8C, (s32*)var_a2, cmp);
    }

    temp_s4 = *sp8C;
    var_s0_2 = (base + n) - 1;
    var_s2_2 = base;
    var_s1_2 = base;
    var_s3 = (base + n) - 1;

    while (1) {
        if (var_s0_2 >= var_s1_2) {
            var_v0 = cmp(*var_s1_2, temp_s4);
            while (var_v0 <= 0) {
                if (var_v0 == 0) {
                    temp_v0 = *var_s2_2;
                    *var_s2_2 = *var_s1_2;
                    *var_s1_2 = temp_v0;
                    var_s2_2++;
                }
                var_s1_2++;
                if (var_s0_2 < var_s1_2) {
                    break;
                }
                var_v0 = cmp(*var_s1_2, temp_s4);
            }
        }
        if (var_s0_2 >= var_s1_2) {
            var_v0 = cmp(*var_s0_2, temp_s4);
            while (var_v0 >= 0) {
                if (var_v0 == 0) {
                    temp_v0 = *var_s0_2;
                    *var_s0_2 = *var_s3;
                    *var_s3 = temp_v0;
                    var_s3 -= 1;
                }
                var_s0_2 -= 1;
                if (var_s0_2 < var_s1_2) {
                    break;
                }
                var_v0 = cmp(*var_s0_2, temp_s4);
            }
        }
        if (var_s0_2 < var_s1_2) {
            break;
        }
        temp_v0 = *var_s1_2;
        *var_s1_2 = *var_s0_2;
        *var_s0_2 = temp_v0;
        var_s1_2++;
        var_s0_2--;
    }
    temp_s4_2 = (s32)(var_s1_2 - var_s2_2);
    temp_v0_6 = (s32)(var_s2_2 - base);
    if (temp_v0_6 < temp_s4_2) {
        var_a2_2 = temp_v0_6;
    } else {
        var_a2_2 = temp_s4_2;
    }
    var_s6 = base + n;
    PointerList_SwapRange(base, var_s1_2 - var_a2_2, var_a2_2);
    temp_s2 = (s32)(var_s3 - var_s0_2);
    temp_v0_6 = ((s32)(var_s6 - var_s3)) - 1;
    if (temp_s2 < temp_v0_6) {
        var_a2_2 = temp_s2;
    } else {
        var_a2_2 = temp_v0_6;
    }
    PointerList_SwapRange(var_s1_2, var_s6 - var_a2_2, var_a2_2);
    if (temp_s4_2 >= 2) {
        Sort_QuickSort(base, temp_s4_2, cmp);
    }
    if (temp_s2 >= 2) {
        Sort_QuickSort(var_s6 - temp_s2, temp_s2, cmp);
    }
}

/** Sorts a pointer list with a comparison function. */
void PointerList_Sort(unk_func_8830867C_02C_0CC* arg0, s32 (*arg1)(s32, s32)) {
    Sort_QuickSort(arg0->unk_00, arg0->unk_08, arg1);
}

void PointerList_Filter(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_0CC* arg1,
                   s32 (*arg2)(unk_func_8830867C_02C_0CC_000*, s32*), s32* arg3) {
    s32 var_s2;
    unk_func_8830867C_02C_0CC_000** var_s0;
    unk_func_8830867C_02C_0CC_000** var_s1;

    var_s1 = arg1->unk_00;
    var_s2 = arg0->unk_08;
    var_s0 = arg0->unk_00;

    while (var_s2 > 0) {
        if (arg2(*var_s0, arg3) != 0) {
            *var_s1++ = *var_s0;
        }
        var_s2--;
        var_s0++;
    }

    arg1->unk_08 = ((s32)var_s1 - (s32)arg1->unk_00) >> 2;
}

/** Compares two zero-terminated 16-bit strings. */
s32 Text_CompareU16Terminated(u16* a0, u16* a1) {
    u16* arg0 = a0;
    u16* arg1 = a1;
    s32 tmpa;
    s32 tmp = tmpa - (*arg1);

    while (true) {
        tmpa = *arg0++;

        tmp = tmpa - *arg1;
        if (tmp != 0) {
            return tmp;
        }

        if (tmpa == 0) {
            break;
        }

        arg1++;
    }

    return 0;
}

// Compares two zero-terminated two-byte (EUC-JP) strings. The first pass
// subtracts 0x100 from every code whose lead byte is 0xA5 (katakana row), which
// maps it onto the matching 0xA4 hiragana code so both kana scripts sort
// together; ties are then broken by an exact code comparison.
/** Compares two strings of 16-bit glyph codes. */
s32 Text_CompareGlyphCodes(u8* a0, u8* a1) {
    u16* arg0 = (u16*)a0;
    u16* arg1 = (u16*)a1;
    s32 tmpa;
    s32 tmpb;
    s32 tmp;
    s32 tmpc;
    s32 tmpd;

    while (true) {
        tmpa = *arg0;
        tmpb = *arg1;
        if (*(u8*)arg0 == 0xA5) {
            tmpa -= 0x100;
        }
        if (*(u8*)arg1 == 0xA5) {
            tmpb -= 0x100;
        }

        tmp = tmpa - tmpb;
        if (tmp != 0) {
            return tmp;
        }

        if (tmpa == 0) {
            arg0 = (u16*)a0;
            arg1 = (u16*)a1;
            break;
        }

        arg0++;
        arg1++;
    }

    while (true) {
        tmpc = *arg0++;

        tmpd = tmpc - *arg1;
        if (tmpd != 0) {
            return tmpd;
        }

        if (tmpc == 0) {
            break;
        }

        arg1++;
    }

    return 0;
}
