/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/jpeg_decoder.c. */

#include "jpegutils.h"
#include "jpeg_decoder.h"
extern u8* sJpegBitStreamPtr;
extern u32 sJpegBitStreamByteIdx;
extern u8 sJpegBitStreamBitIdx;
extern u8 sJpegBitStreamDontSkip;
extern u32 sJpegBitStreamCurWord;

s32 Jpeg_DecodeMcus(JpegDecoder* decoder, u16* mcuBuff, s32 count, u8 isFollowing, JpegDecoderState* state);
s32 Jpeg_DecodeBlock(JpegHuffmanTable* hTable0, JpegHuffmanTable* hTable1, u16* mcu, s16* unk);
s32 Jpeg_DecodeHuffmanSymbol(JpegHuffmanTable* hTable, s16* outCoeff, s8* outZeroCount);
u16 Jpeg_ReadBits(u8 len);

s32 Jpeg_DecodeMcus(JpegDecoder* decoder, u16* mcu_buff, s32 count, u8 is_following, JpegDecoderState* state) {
    s16 pad; // FAKE: stack padding
    s16 unk0;
    s16 unk1;
    s16 unk2;
    u32 idx;
    s32 inc;
    u16 unk_count;

    JpegHuffmanTable* h_table0;
    JpegHuffmanTable* h_table1;
    JpegHuffmanTable* h_table2;
    JpegHuffmanTable* h_table3;

    inc = 0;
    sJpegBitStreamPtr = decoder->imageData;
    if (decoder->mode == 0) {
        unk_count = 2;
    } else {
        unk_count = 4;
        if (decoder->unk_05 == 1) {
            inc = 8 * 8 * 2;
        }
    }

    h_table0 = decoder->hTablePtrs[0];
    h_table1 = decoder->hTablePtrs[1];
    h_table2 = decoder->hTablePtrs[2];
    h_table3 = decoder->hTablePtrs[3];

    if (!is_following) {
        sJpegBitStreamByteIdx = 0;
        sJpegBitStreamBitIdx = 32;
        sJpegBitStreamCurWord = 0;
        sJpegBitStreamDontSkip = 0;
        unk0 = 0;
        unk1 = 0;
        unk2 = 0;
    } else {
        sJpegBitStreamByteIdx = state->byteIdx;
        sJpegBitStreamBitIdx = state->bitIdx;
        sJpegBitStreamCurWord = state->curWord;
        sJpegBitStreamDontSkip = state->dontSkip;
        unk0 = state->unk_0C;
        unk1 = state->unk_0E;
        unk2 = state->unk_10;
    }

    while (count != 0) {
        for (idx = 0; idx < unk_count; idx++) {
            if (Jpeg_DecodeBlock(h_table0, h_table1, mcu_buff, &unk0)) {
                return 2;
            }
            mcu_buff += 8 * 8;
        }

        if (Jpeg_DecodeBlock(h_table2, h_table3, mcu_buff, &unk1)) {
            return 2;
        }
        mcu_buff += 8 * 8;

        if (Jpeg_DecodeBlock(h_table2, h_table3, mcu_buff, &unk2)) {
            return 2;
        }

        count--;
        mcu_buff += 8 * 8;
        mcu_buff += inc;
    }

    state->byteIdx = sJpegBitStreamByteIdx;
    state->bitIdx = sJpegBitStreamBitIdx;
    state->curWord = sJpegBitStreamCurWord;
    state->dontSkip = sJpegBitStreamDontSkip;
    state->unk_0C = unk0;
    state->unk_0E = unk1;
    state->unk_10 = unk2;
    return 0;
}

s32 Jpeg_DecodeBlock(JpegHuffmanTable* h_table0, JpegHuffmanTable* h_table1, u16* mcu, s16* unk) {
    s8 i = 0;
    s8 zero_count;
    s16 coeff;

    if (Jpeg_DecodeHuffmanSymbol(h_table0, &coeff, &zero_count)) {
        return 1;
    }

    *unk += coeff;
    mcu[i++] = *unk;
    while (i < 8 * 8) {
        if (Jpeg_DecodeHuffmanSymbol(h_table1, &coeff, &zero_count) != 0) {
            return 1;
        }

        if (coeff == 0) {
            if (zero_count == 0xF) {
                while (zero_count-- >= 0) {
                    mcu[i++] = 0;
                }
            } else {
                while (i < 8 * 8) {
                    mcu[i++] = 0;
                }
                break;
            }
        } else {
            while (0 < zero_count--) {
                mcu[i++] = 0;
            }
            mcu[i++] = coeff;
        }
    }

    return 0;
}

s32 Jpeg_DecodeHuffmanSymbol(JpegHuffmanTable* h_table, s16* out_coeff, s8* out_zero_count) {
    u8 code_idx;
    u8 sym;
    u16 code_off = 0;
    u16 buff = Jpeg_ReadBits(16);

    for (code_idx = 0; code_idx < 16; code_idx++) {
        if (h_table->codesB[code_idx] == 0xFFFF) {
            continue;
        }

        code_off = buff >> (15 - code_idx);
        if (code_off <= h_table->codesB[code_idx]) {
            break;
        }
    }

    if (code_idx >= 16) {
        return 1;
    }

    sym = h_table->symbols[h_table->codeOffs[code_idx] + code_off - h_table->codesA[code_idx]];
    *out_zero_count = sym >> 4;
    sym &= 0xF;

    sJpegBitStreamBitIdx += code_idx - 15;
    *out_coeff = 0;
    if (sym) {
        *out_coeff = Jpeg_ReadBits(sym);
        if (*out_coeff < (1 << (sym - 1))) {
            *out_coeff += (-1U << sym) + 1;
        }
    }

    return 0;
}

u16 Jpeg_ReadBits(u8 len) {
    u8 byte_count;
    u8 data;
    s32 ret = 0;
    u32 temp;

    for (byte_count = sJpegBitStreamBitIdx >> 3; byte_count > 0; byte_count--) {
        data = sJpegBitStreamPtr[sJpegBitStreamByteIdx++];
        if (sJpegBitStreamDontSkip) {
            if (data == 0) {
                data = sJpegBitStreamPtr[sJpegBitStreamByteIdx++];
            }
        }

        sJpegBitStreamDontSkip = (data == 0xFF) ? 1 : 0;

        sJpegBitStreamCurWord <<= 8;
        sJpegBitStreamCurWord |= data;
        sJpegBitStreamBitIdx -= 8;
    }

    ret = sJpegBitStreamCurWord << sJpegBitStreamBitIdx;
    temp = ret;
    ret = temp >> -len;
    sJpegBitStreamBitIdx += len;
    return ret;
}
