/* Stadium Zero resident code. */

#include "global.h"
#include "m2c_macros.h"
#include "block_relocate.h"

void func_80037F48(s32, s32);

/**
 * Relocates a sound bank against its own address (Audio_RelocateSoundBankWrapper(bank, bank)).
 * @unverified: no callers found.
 */
void Audio_RelocateSoundBankInPlace(s32 bank) {
    func_80037F48(bank, bank);
}

/**
 * Relocates a loaded block in place: adds the block's own address to the word at +0x08, to the
 * table offset at +0x0C, and to each of the `count` words of that table, then sets bit 0 of the flags
 * word at +0x04 so it is not relocated twice. Used on sequence and audio data after loading.
 * `i` doubles as the offset temporary, which reproduces the retail register choice.
 */
void Block_RelocateSelf(RelocHeader8003A710* arg0) {
    u32 n;
    u32 i;
    u32* p;

    n = arg0->count;
    i = arg0->unk08;
    arg0->unk08 = (u32)arg0 + i;
    i = arg0->table;
    arg0->table = (u32)arg0 + i;
    p = (u32*)arg0->table;
    for (i = 0; i < n; i++) {
        *p++ += (u32)arg0;
    }
    arg0->flags |= 1;
}

/**
 * Relocates the sound bank that follows this header against the header's end, marks it relocated
 * (flags bit 0) and returns the bank data. @unverified: no callers found.
 */
s32 Audio_RelocateSoundBankHeader(Unk8003A7AC* arg0) {
    s32 end = arg0->size + (s32)arg0;

    func_80037F48((s32)arg0->data, end);
    arg0->flags |= 1;
    return (s32)arg0->data;
}
