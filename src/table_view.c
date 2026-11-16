/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/table_view.c. */

#include "table_view.h"

void TableView_Initialize(ByteMatrix* arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4);
s32 ByteMatrix_AppendRow(ByteMatrix* arg0, s8* a1);
s32 ByteMatrix_InsertRow(ByteMatrix* arg0, s8* arg1, s32 arg2);
s32 ByteMatrix_RemoveRow(ByteMatrix* arg0, s32 arg1);
s32 ByteMatrix_CopyRow(ByteMatrix* arg0, s8* a1, s32 arg2);
s32 ByteMatrix_CopyRowAt(ByteMatrix* arg0, s8* a1, s32 arg2);
s32 WordList_Remove(unk_func_8830867C_04C_030_02C_000_000_00C* arg0, s32 arg1);
void PointerList_Initialize(PointerList* arg0, void** arg1, s32 arg2, s32 arg3);
void PointerList_Insert(PointerList* arg0, char* arg1, s32 arg2);
void PointerList_Remove(LabMonEntryList* arg0, s32 arg1);
void PointerList_SwapRange(void** arg0, void** arg1, s32 arg2);
s32* Sort_SelectMedianPointer(s32* arg0, s32* arg1, s32* arg2, s32 (*arg3)(s32, s32));
void Sort_QuickSort(void** base, s32 n, s32 (*cmp)(s32, s32));
void PointerList_Sort(LabMonEntryList* arg0, s32 (*arg1)(s32, s32));
void PointerList_Filter(LabMonEntryList* arg0, LabMonEntryList* arg1,
                   s32 (*arg2)(LabMonEntry*, s32*), s32* arg3);
s32 Text_CompareU16Terminated(u16* a0, u16* a1);
s32 Text_CompareGlyphCodes(u8* a0, u8* a1);

/** Initializes a table view over a data table with the given dimensions. */
void TableView_Initialize(ByteMatrix* arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0->rows = arg1;
    arg0->rowSize = arg2;
    arg0->capacity = arg3;
    arg0->count = arg4;
}

/** Appends a row to a byte matrix. */
s32 ByteMatrix_AppendRow(ByteMatrix* arg0, s8* a1) {
    s8* var_v0;
    s32 i;
    s8* arg1;

    if (arg0->count >= arg0->capacity) {
        return 1;
    }

    var_v0 = (u8*)arg0->rows + (arg0->rowSize * arg0->count);
    arg1 = a1;

    for (i = arg0->rowSize; i > 0; i--) {
        *var_v0++ = *arg1++;
    }

    arg0->count++;
    return 0;
}

/** Inserts a row into a byte matrix at an index. */
s32 ByteMatrix_InsertRow(ByteMatrix* arg0, s8* arg1, s32 arg2) {
    s32 var_t1;
    s8* var_t0;
    s8* var_v1;

    if ((arg0->count >= arg0->capacity) || (arg0->count < arg2)) {
        return 1;
    }

    var_v1 = (s8*)arg0->rows + (arg0->rowSize * arg0->count);
    var_t0 = var_v1 + arg0->rowSize;
    var_t1 = (arg0->count - arg2) * arg0->rowSize;

    while (var_t1 > 0) {
        *--var_t0 = *--var_v1;
        var_t1--;
    }

    var_v1 = arg1;
    var_t1 = arg0->rowSize;
    var_t0 = (u8*)arg0->rows + (arg0->rowSize * arg2);

    while (var_t1 > 0) {
        *var_t0++ = *var_v1++;
        var_t1--;
    }

    arg0->count += 1;
    return 0;
}

/** Removes a row from a byte matrix. */
s32 ByteMatrix_RemoveRow(ByteMatrix* arg0, s32 arg1) {
    s32 var_t0;
    s8* var_a3;
    s8* var_v1;

    if (arg1 >= arg0->count) {
        return 1;
    }

    var_v1 = (s8*)arg0->rows + (arg0->rowSize * arg1);

    arg0->count--;

    var_a3 = arg0->rowSize + var_v1;
    var_t0 = (arg0->count - arg1) * arg0->rowSize;

    while (var_t0 > 0) {
        *var_v1++ = *var_a3++;
        var_t0--;
    }

    return 0;
}

/** Copies a row into a byte matrix. */
s32 ByteMatrix_CopyRow(ByteMatrix* arg0, s8* a1, s32 arg2) {
    s8* var_v0;
    s32 i;
    s8* arg1;

    if (arg2 >= arg0->count) {
        return 1;
    }

    var_v0 = (s8*)arg0->rows + (arg0->rowSize * arg2);
    arg1 = a1;

    for (i = arg0->rowSize; i > 0; i--) {
        *arg1++ = *var_v0++;
    }

    return 0;
}

/** Copies a row into a byte matrix at an index. */
s32 ByteMatrix_CopyRowAt(ByteMatrix* arg0, s8* a1, s32 arg2) {
    s8* var_v0;
    s32 i;
    s8* arg1;

    if (arg2 >= arg0->count) {
        return 1;
    }

    var_v0 = (s8*)arg0->rows + (arg0->rowSize * arg2);
    arg1 = a1;

    for (i = arg0->rowSize; i > 0; i--) {
        *var_v0++ = *arg1++;
    }

    return 0;
}

/** Removes an entry from a list of 16-bit values. */
s32 WordList_Remove(unk_func_8830867C_04C_030_02C_000_000_00C* arg0, s32 arg1) {
    s16* var_a2;
    s32 var_a3;
    s16* var_v1;

    if (arg1 >= arg0->count) {
        return 1;
    }

    var_v1 = (s16*)arg0->items + arg1;

    arg0->count--;

    var_a2 = var_v1 + 1;
    var_a3 = arg0->count - arg1;

    while (var_a3 > 0) {
        *var_v1++ = *var_a2++;
        var_a3--;
    }

    return 0;
}

/** Initializes a pointer list over a given array. */
void PointerList_Initialize(PointerList* arg0, void** arg1, s32 arg2, s32 arg3) {
    arg0->items = arg1;
    arg0->capacity = arg2;
    arg0->count = arg3;
}

/** Inserts a pointer into a pointer list at an index. */
void PointerList_Insert(PointerList* arg0, char* arg1, s32 arg2) {
    s32 var_t1;
    void** var_t0;
    void** var_v0;

    var_v0 = &arg0->items[arg0->count];
    var_t0 = var_v0 + 1;
    var_t1 = arg0->count - arg2;

    while (var_t1 > 0) {
        *--var_t0 = *--var_v0;
        var_t1--;
    }

    arg0->items[arg2] = arg1;
    arg0->count++;
}

/** Removes a pointer from a pointer list. */
void PointerList_Remove(LabMonEntryList* arg0, s32 arg1) {
    s32 var_a2;
    LabMonEntry** var_v0;
    LabMonEntry** var_v1;

    var_v0 = &arg0->items[arg1];
    var_v1 = var_v0 + 1;

    arg0->count--;

    var_a2 = arg0->count - arg1;

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
void PointerList_Sort(LabMonEntryList* arg0, s32 (*arg1)(s32, s32)) {
    Sort_QuickSort(arg0->items, arg0->count, arg1);
}

/**
 * Copies every entry of pointer list arg0 for which arg2(entry, arg3) returns nonzero into
 * list arg1, and sets arg1's count.
 */
void PointerList_Filter(LabMonEntryList* arg0, LabMonEntryList* arg1,
                   s32 (*arg2)(LabMonEntry*, s32*), s32* arg3) {
    s32 var_s2;
    LabMonEntry** var_s0;
    LabMonEntry** var_s1;

    var_s1 = arg1->items;
    var_s2 = arg0->count;
    var_s0 = arg0->items;

    while (var_s2 > 0) {
        if (arg2(*var_s0, arg3) != 0) {
            *var_s1++ = *var_s0;
        }
        var_s2--;
        var_s0++;
    }

    arg1->count = ((s32)var_s1 - (s32)arg1->items) >> 2;
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
