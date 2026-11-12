/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/jpegutils.c. */

#include "jpegutils.h"
typedef struct JpegHuffmanTableOld {
    /* 0x000 */ u8 codeOffs[16];
    /* 0x010 */ u16 dcCodes[120];
    /* 0x100 */ u16 acCodes[256];
} JpegHuffmanTableOld;

void JpegUtils_ProcessQuantizationTable(u8* dqt, JpegQuantizationTable* qt, u8 num_tables);
s32 JpegUtils_ParseHuffmanCodesLengths(u8* ptr, u8* codesLengths);
s16 JpegUtils_GetHuffmanCodes(u8* codesLengths, u16* codes);
u16 JpegUtils_SetHuffmanTable(u8* data, JpegHuffmanTable* ht, u16* codes);
u32 JpegUtils_ProcessHuffmanTableImpl(u8* data, JpegHuffmanTable* ht, u8* codesLengths, u16* codes, u8 isAc);
s32 JpegUtils_ProcessHuffmanTable(u8* dht, JpegHuffmanTable* ht, u8* codesLengths, u16* codes, u8 count);
void JpegUtils_SetHuffmanTableOld(u8* data, JpegHuffmanTableOld* ht, u8* codesLengths, u16* codes, s16 count, u8 isAc);
u32 JpegUtils_ProcessHuffmanTableImplOld(u8* dht, JpegHuffmanTableOld* ht, u8* codesLengths, u16* codes);

void JpegUtils_ProcessQuantizationTable(u8* dqt, JpegQuantizationTable* qt, u8 num_tables) {
    u8 i;

    for (i = 0; i < num_tables; i++) {
        u8 j;

        dqt++;
        for (j = 0; j < 64; j++) {
            qt[i].table[j] = *dqt++;
        }
    }
}

s32 JpegUtils_ParseHuffmanCodesLengths(u8* ptr, u8* codes_lengths) {
    u8 off = 1;
    s16 count = 0;
    s16 idx = 1;

    while (off < 0x11) {
        while (idx <= ptr[off - 1]) {
            codes_lengths[count++] = off;
            idx++;
        }
        idx = 1;
        off++;
    }

    codes_lengths[count] = 0;
    return count;
}

s16 JpegUtils_GetHuffmanCodes(u8* codes_lengths, u16* codes) {
    s16 idx = 0;
    u16 code = 0;
    u8 last_len = codes_lengths[0];

    while (true) {
        while (true) {
            codes[idx++] = code++;

            if (codes_lengths[idx] != last_len) {
                break;
            }
        }

        if (codes_lengths[idx] == 0) {
            break;
        }

        while (true) {
            if (code <<= 1, codes_lengths[idx] == ++last_len) {
                break;
            }
        }
    }

    return idx;
}

u16 JpegUtils_SetHuffmanTable(u8* data, JpegHuffmanTable* ht, u16* codes) {
    u8 idx;
    u16 code_off = 0;

    for (idx = 0; idx < 0x10; idx++) {
        if (data[idx]) {
            ht->codeOffs[idx] = code_off;
            ht->codesA[idx] = codes[code_off];
            code_off += data[idx] - 1;
            ht->codesB[idx] = codes[code_off];
            code_off++;
        } else {
            ht->codesB[idx] = 0xFFFF;
        }
    }

    return code_off;
}

u32 JpegUtils_ProcessHuffmanTableImpl(u8* data, JpegHuffmanTable* ht, u8* codes_lengths, u16* codes, u8 is_ac) {
    s16 ret;
    s32 count = JpegUtils_ParseHuffmanCodesLengths(data, codes_lengths);
    s32 temp;

    ret = count;
    if (count == 0 || (is_ac && count > 0x100) || (!is_ac && count > 0x10)) {
        return 0;
    }
    if (ret != JpegUtils_GetHuffmanCodes(codes_lengths, codes)) {
        return 0;
    }
    if (temp = JpegUtils_SetHuffmanTable(data, ht, codes), temp != ret) {
        return 0;
    }

    return ret;
}

s32 JpegUtils_ProcessHuffmanTable(u8* dht, JpegHuffmanTable* ht, u8* codes_lengths, u16* codes, u8 count) {
    u8 idx;
    u32 code_count;

    for (idx = 0; idx < count; idx++) {
        u32 ac = (*dht++ >> 4);

        code_count = JpegUtils_ProcessHuffmanTableImpl(dht, &ht[idx], codes_lengths, codes, ac);
        if (code_count == 0) {
            return 1;
        }

        dht += 0x10;
        ht[idx].symbols = dht;
        dht += code_count;
    }
    return 0;
}

void JpegUtils_SetHuffmanTableOld(u8* data, JpegHuffmanTableOld* ht, u8* codes_lengths, u16* codes, s16 count, u8 is_ac) {
    s16 idx;
    u8 a;

    for (idx = 0; idx < count; idx++) {
        a = data[idx];
        if (is_ac) {
            ht->acCodes[a] = codes[idx];
            ht->codeOffs[a] = codes_lengths[idx];
        } else {
            ht->dcCodes[a] = codes[idx];
            ht->codeOffs[a] = codes_lengths[idx];
        }
    }
}

u32 JpegUtils_ProcessHuffmanTableImplOld(u8* dht, JpegHuffmanTableOld* ht, u8* codes_lengths, u16* codes) {
     u8 is_ac = *dht++ >> 4;
    s16 count2;
    s32 count;

    count2 = count = JpegUtils_ParseHuffmanCodesLengths(dht, codes_lengths);

    if (count == 0 || (is_ac && count > 0x100) || (!is_ac && count > 0x10)) {
        return 1;
    }

    if (JpegUtils_GetHuffmanCodes(codes_lengths, codes) != count2) {
        return 1;
    }

    JpegUtils_SetHuffmanTableOld(dht + 0x10, ht, codes_lengths, codes, count2, is_ac);

    return 0;
}
