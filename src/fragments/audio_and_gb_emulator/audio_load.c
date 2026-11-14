/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_emulator/gb_tower_emulator_86920.c. */

#include "global.h"
#include "audio_and_gb_emulator.h"

extern AudioBufferParameters D_811858B8;
extern volatile s32 D_811858F0;
extern s32 D_811858F8;
extern s32 D_811858FC;
extern s16* D_811859B8[3];
extern s16 D_811859C4[3];
extern u32 D_811859CC;
extern volatile s32 D_811859D4;

#include "m2c_macros.h"

u32 GbApu_AllocZeroed(AudioAllocPool* arg0, s32 arg1);
s32 GbApu_Alloc(AudioAllocPool* arg0, s32 arg1);
void GbApu_InitAllocator(AudioAllocPool* arg0, s32 arg1, s32 arg2);

extern u8 D_81184654[1];
extern u8 D_81184655[1];
extern u8 D_81184656[1];

/* Declarations copied from gb_tower_emulator_86920.c. */
s32 AudioHeap_SearchCaches(s32, M2C_UNK, s32);
s32 AudioPlayback_NoteDisable(Note*);
s32 AudioPlayback_AudioListRemove(Note*);
s32 AudioSeq_AudioListPushBack(s8*, Note*);
extern Note* D_81184664;
extern s8 D_81184938;
extern s32 D_811858E8;
M2C_UNK AudioSeq_SequencePlayerDisable(M2C_UNK *);                   /* extern */
extern s8 D_81184668;
extern s16 D_811858CC;
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);
extern M2C_UNK D_81184290;
extern M2C_UNK D_811842B0;
extern u8 D_81186270[];
extern s32 D_811526FC;
extern s32 D_811842A0;
s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184290;
extern M2C_UNK D_811842C0;
extern M2C_UNK D_811842F0;
s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_811842F0;
extern M2C_UNK D_81184300;
extern M2C_UNK D_81184310;
s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184300;
extern M2C_UNK D_81184320;
extern M2C_UNK D_81184324;
extern M2C_UNK D_81184380;
extern M2C_UNK D_81184384;
extern M2C_UNK D_811843E0;
extern M2C_UNK D_811843E4;
s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184310;
extern M2C_UNK D_81184340;
extern M2C_UNK D_81184344;
extern M2C_UNK D_811843A0;
extern M2C_UNK D_811843A4;
extern M2C_UNK D_81184400;
extern M2C_UNK D_81184404;
extern u8 D_81184654[1];
extern u8 D_81184655[1];
extern u8 D_81184656[1];
void AudioLoad_SetFontLoadStatus(s32, s32);
s32 AudioHeap_SearchRegularCaches(s32 arg0, s32 arg1, s32 arg2);
s32 AudioHeap_SearchPermanentCache(s32 arg0, s32 arg1);
extern s16 D_811371D8[];
extern s16 D_811373C8[];
extern Reverb8110AA50 D_81184110[];
extern s8 D_8118427B;
extern s16 D_811858C2;
extern AudioSpec D_811526C4[];
extern s16 D_811526F8;
extern u16 D_81184278;
extern s16 D_8118427C;
extern void* D_81184288;
extern s32 D_81184298;
extern AudioSessionPoolSplit D_81184620;
extern AudioCachePoolSplit D_81184630;
extern AudioCommonPoolSplit D_81184638;
extern AudioCommonPoolSplit D_81184648;
extern u8 D_81184658;
extern s32 D_811858E4;
extern s16 D_811858EC;
extern void* D_81185900[2];
extern s32 D_811859B4;
extern f32 D_811859B0;
extern u32 D_8118568C;
extern s32 D_8118557C;
void AudioLoad_InitSampleDmaBuffers(s32);
void func_811152A4(s32);
s32 func_80058100(s32);
void func_8005C0A0(void);
void func_8110FAF4(void);
void AudioPlayback_InitNoteFreeList(void);
void AudioPlayback_NoteInitAll(void);
void func_8111539C(s32);
void func_81115480(void);
#define EXTERNAL_POOL_AFF0 (*(AudioAllocPool*)&D_811842A0)
#define REVERBS_AFF0 ((SynthesisReverb*)D_81184110)



extern AudioPermanentCache D_81184440;
/**
 * Returns the permanent cache entry for table `arg0`, id `arg1`, or 0. Name follows the Zelda 64 audio driver, whose loader this matches.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioHeap_SearchPermanentCache(s32 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < D_81184440.pool.numEntries; i++) {
        if (arg0 == D_81184440.entries[i].tableType && arg1 == D_81184440.entries[i].id) {
            return D_81184440.entries[i].ramAddr;
        }
    }

    return 0;
}

/**
 * Allocates `size` bytes in the permanent cache for table `x`, id `y`. Name follows the Zelda 64 audio driver, whose loader this matches.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioHeap_AllocPermanent(s32 x, s32 y, s32 size) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 index = D_81184440.pool.numEntries;

    D_81184440.entries[index].ramAddr = func_81109868((M2C_UNK*)&D_81184440, size);
    if (D_81184440.entries[index].ramAddr == 0) {
        return 0;
    }
    D_81184440.entries[index].tableType = x;
    D_81184440.entries[index].id = y;
    D_81184440.entries[index].size = size;
    // No return here; the original falls off the end with the allocation still in v0.
}

struct SampleCacheEntry8110BA8C* AudioHeap_AllocTemporarySampleCacheEntry(u32);
/**
 * Allocates a temporary sample cache entry of `arg0` bytes for font `arg1`. Zelda 64 audio driver (heap.c).
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioHeap_AllocTemporarySampleCache(s32 arg0, s32 arg1, s32 arg2, s8 arg3) {
    s8* p = (s8*)AudioHeap_AllocTemporarySampleCacheEntry(arg0);

    if (p != NULL) {
        M2C_FIELD(p, u8*, 2) = arg1;
        M2C_FIELD(p, s32*, 0xC) = arg2;
        M2C_FIELD(p, s8*, 1) = arg3;
        return M2C_FIELD(p, s32*, 8);
    }
    return 0;
}

s8* AudioHeap_AllocPersistentSampleCacheEntry(s32 arg0);
/**
 * Allocates a persistent sample cache entry of `arg0` bytes for font `arg1`. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioHeap_AllocPersistentSampleCache(s32 arg0, s32 arg1, s32 arg2, s8 arg3) {
    s8* p = AudioHeap_AllocPersistentSampleCacheEntry(arg0);

    if (p != NULL) {
        M2C_FIELD(p, u8*, 2) = arg1;
        M2C_FIELD(p, s32*, 0xC) = arg2;
        M2C_FIELD(p, s8*, 1) = arg3;
        return M2C_FIELD(p, s32*, 8);
    }
    return 0;
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184300;
extern M2C_UNK D_81184310;
extern M2C_UNK D_811845D0;
extern s32 D_811845D8;
extern s32 D_811845F4;
typedef struct SampleCacheEntry8110BA8C {
    /* 0x00 */ s8 inUse;
    /* 0x01 */ s8 origMedium;
    /* 0x02 */ s8 sampleBankId;
    /* 0x04 */ s32 sampleAddr;
    /* 0x08 */ u8* allocatedAddr;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u32 size;
} SampleCacheEntry8110BA8C; // size = 0x14

typedef struct SampleCache8110BA8C {
    /* 0x00 */ u8* startRamAddr;
    /* 0x04 */ u8* curRamAddr;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 numAllocatedEntries;
    /* 0x10 */ SampleCacheEntry8110BA8C entries[1];
    /* 0x24 */ s32 numEntries;
} SampleCache8110BA8C;

typedef struct PreloadSample8110BA8C {
    /* 0x00 */ u32 unk_bits : 8;
    /* 0x00 */ u32 size : 24;
} PreloadSample8110BA8C;

typedef struct Preload8110BA8C {
    /* 0x00 */ u32 endAndMediumKey;
    /* 0x04 */ PreloadSample8110BA8C* sample;
    /* 0x08 */ u8* ramAddr;
    /* 0x0C */ u32 encodedInfo;
    /* 0x10 */ s32 isFree;
} Preload8110BA8C; // size = 0x14

extern SampleCache8110BA8C D_811845F8;
extern s32 D_81184600;
extern s32 D_8118461C;

/**
 * Sets up the persistent and temporary sample caches from the misc pool. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_InitSampleCaches(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_81109868(&D_81184300, arg0);
    if (temp_v0 == 0) {
        D_811845D8 = 0;
    } else {
        func_811098C0(&D_811845D0, temp_v0, arg0);
    }
    temp_v0_2 = func_81109868(&D_81184310, arg1);
    if (temp_v0_2 == 0) {
        D_81184600 = 0;
    } else {
        func_811098C0((M2C_UNK*)&D_811845F8, temp_v0_2, arg1);
    }
    D_811845F4 = 0;
    D_8118461C = 0;
}

extern Preload8110BA8C D_81184B78[];
extern s32 D_8118557C;
void AudioHeap_DiscardSampleCacheEntry(SampleCacheEntry8110BA8C*);

/**
 * Takes `size` bytes from the temporary sample cache, discarding the entries it overwrites. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
SampleCacheEntry8110BA8C* AudioHeap_AllocTemporarySampleCacheEntry(u32 size) {
    u8* alloc_after;
    u8* alloc_before;
    void* mem;
    s32 index;
    s32 i;
    SampleCacheEntry8110BA8C* entry;
    Preload8110BA8C* preload;
    SampleCache8110BA8C* cache;
    u8* startRamAddr;
    u8* end_ram_addr;

    cache = &D_811845F8;
    alloc_before = cache->curRamAddr;
    mem = (void*)func_81109868((M2C_UNK*)cache, size);
    if (mem == NULL) {
        u8* old = cache->curRamAddr;

        cache->curRamAddr = cache->startRamAddr;
        mem = (void*)func_81109868((M2C_UNK*)cache, size);
        if (mem == NULL) {
            cache->curRamAddr = old;
            return NULL;
        }
        alloc_before = cache->startRamAddr;
    }

    alloc_after = cache->curRamAddr;

    index = -1;
    for (i = 0; i < D_8118557C; i++) {
        preload = &D_81184B78[i];
        if (preload->isFree == 0) {
            startRamAddr = preload->ramAddr;
            end_ram_addr = preload->ramAddr + preload->sample->size - 1;

            if (end_ram_addr < alloc_before && startRamAddr < alloc_before) {
                continue;
            }
            if (end_ram_addr >= alloc_after && startRamAddr >= alloc_after) {
                continue;
            }

            preload->isFree = 1;
        }
    }

    for (i = 0; i < cache->numEntries; i++) {
        if (!cache->entries[i].inUse) {
            continue;
        }

        startRamAddr = cache->entries[i].allocatedAddr;
        end_ram_addr = startRamAddr + cache->entries[i].size - 1;

        if (end_ram_addr < alloc_before && startRamAddr < alloc_before) {
            continue;
        }
        if (end_ram_addr >= alloc_after && startRamAddr >= alloc_after) {
            continue;
        }

        AudioHeap_DiscardSampleCacheEntry(&cache->entries[i]);
        if (index == -1) {
            index = i;
        }
    }

    if (index == -1) {
        index = cache->numEntries++;
    }

    entry = &cache->entries[index];
    entry->inUse = 1;
    entry->allocatedAddr = mem;
    entry->size = size;

    return entry;
}

/* First byte of a Sample; AudioHeap_UnapplySampleCache restores its medium (bits 2-3). */
typedef struct {
    u8 pad0 : 4;
    u8 medium : 2; // @unverified: bits 2-3 of Sample byte 0; AudioHeap_UnapplySampleCache restores the original medium here (OoT's Sample.medium)
    u8 pad1 : 2;
} SampleMedium8110D4E0;

extern SoundFont* D_811858B0;
extern u8* D_811858A0;
s32 AudioLoad_IsFontLoadComplete(s32 arg0);
u8* AudioPlayback_GetInstrumentInner(s32, s32);
u8* AudioPlayback_GetDrum(s32, s32);

void AudioHeap_UnapplySampleCache(u8* arg0, SampleMedium8110D4E0* arg1);

/**
 * Points every font that used a cached sample back at the original sample. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_DiscardSampleCacheEntry(SampleCacheEntry8110BA8C* entry) {
    u8* inst;
    s32 num_fonts;
    s32 font_id;
    s32 sample_bank_id1;
    s32 sample_bank_id2;
    s32 inst_id;
    u8* drum;
    s32 drum_id;

    num_fonts = *(s16*)D_811858A0;
    for (font_id = 0; font_id < num_fonts; font_id++) {
        sample_bank_id1 = D_811858B0[font_id].sampleBankId1;
        sample_bank_id2 = D_811858B0[font_id].sampleBankId2;
        if (((sample_bank_id1 != 0xFF) && (entry->sampleBankId == sample_bank_id1)) ||
            ((sample_bank_id2 != 0xFF) && (entry->sampleBankId == sample_bank_id2)) || entry->sampleBankId == 0) {
            if (AudioHeap_SearchCaches(1, 2, font_id) != 0) {
                if (AudioLoad_IsFontLoadComplete(font_id) != 0) {
                    for (inst_id = 0; inst_id < D_811858B0[font_id].numInstruments; inst_id++) {
                        inst = AudioPlayback_GetInstrumentInner(font_id, inst_id);
                        if (inst != NULL) {
                            if (inst[1] != 0) {
                                AudioHeap_UnapplySampleCache((u8*)entry, M2C_FIELD(inst, SampleMedium8110D4E0**, 8));
                            }
                            if (inst[2] != 0x7F) {
                                if (1) {
                                    AudioHeap_UnapplySampleCache((u8*)entry, M2C_FIELD(inst, SampleMedium8110D4E0**, 0x18));
                                }
                            }
                            AudioHeap_UnapplySampleCache((u8*)entry, M2C_FIELD(inst, SampleMedium8110D4E0**, 0x10));
                        }
                    }
                    for (drum_id = 0; drum_id < D_811858B0[font_id].numDrums; drum_id++) {
                        drum = AudioPlayback_GetDrum(font_id, drum_id);
                        if (drum != NULL) {
                            AudioHeap_UnapplySampleCache((u8*)entry, M2C_FIELD(drum, SampleMedium8110D4E0**, 4));
                        }
                    }
                }
            }
        }
    }
}

/**
 * AudioHeap_UnapplySampleCache
 *
 * If arg1 is non-NULL and the word at arg0 + 0x08 equals the word at
 * arg1 + 0x04, copies the word at arg0 + 0x0C into arg1 + 0x04 and stores the
 * low two bits of the signed byte at arg0 + 0x01 into bits 2-3 of the byte at
 * arg1 + 0x00 (a bit-field write: the retail code masks with 0xFFF3 / 0x0C).
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioHeap_UnapplySampleCache(u8* arg0, SampleMedium8110D4E0* arg1) {
    if ((arg1 != NULL) && (M2C_FIELD(arg0, s32*, 8) == M2C_FIELD(arg1, s32*, 4))) {
        M2C_FIELD(arg1, s32*, 4) = M2C_FIELD(arg0, s32*, 0xC);
        arg1->medium = M2C_FIELD(arg0, s8*, 1);
    }
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
/**
 * Takes `arg0` bytes from the persistent sample cache. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
s8 *AudioHeap_AllocPersistentSampleCacheEntry(s32 arg0)
{
  s32 temp_v0_2;
  s8 *temp_v0;
  s32 *new_var; // FAKE: permuter temp
  new_var = (s32 *) (&D_811845F4);
  temp_v0_2 = func_81109868(&(*((s8 *) (&D_811845D0))), arg0);
  if (temp_v0_2 == 0)
  {
    return 0;
  }
  temp_v0 = (((*new_var) * 0x14) + 0x10) + (&(*((s8 *) (&D_811845D0))));
  *((s8 *) (((s8 *) temp_v0) + 0)) = 1;
  *((s32 *) (((s8 *) temp_v0) + 8)) = temp_v0_2;
  *((s32 *) (((s8 *) temp_v0) + 0x10)) = arg0;
  *new_var += 1;
  return temp_v0;
}

/**
 * Discards the sample cache entries of fonts that are no longer loaded. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_DiscardSampleCaches(void) {
    UNUSED s32 pad2[1]; // FAKE: stack padding
    s32 j;
    s32 count;
    UNUSED s32 pad[5]; // FAKE: stack padding
    s32 a;
    s32 b;
    s8* slot;
    s32 k;
    s32 m;
    s32 i;
    u8* p;
    s32 off;

    count = *(s16*)D_811858A0;
    for (i = 0; i < count; i++) {
        a = D_811858B0[i].sampleBankId1;
        b = D_811858B0[i].sampleBankId2;
        if ((a != 0xFF) || (b != 0xFFU)) {
            off = 0x12;
            if ((AudioHeap_SearchCaches(1, 3, i) != 0) && (AudioLoad_IsFontLoadComplete(i) != 0)) {
                slot = (s8*)&D_811845D0;
                for (j = 0; j < D_811845F4; j++, slot += 0x14) {
                    if ((a != slot[off]) && (b != slot[0x12]) && (slot[0x12] != 0)) {
                        break;
                    }
                    {
                        for (k = 0; k < D_811858B0[i].numInstruments; k++) {
                            p = AudioPlayback_GetInstrumentInner(i, k);
                            if (p != NULL) {
                                if (p[1] != 0) {
                                    AudioHeap_UnapplySampleCache(slot + 0x10, M2C_FIELD(p, SampleMedium8110D4E0**, 8));
                                }
                                if (p[2] != 0x7F) {
                                    AudioHeap_UnapplySampleCache(slot + 0x10, M2C_FIELD(p, SampleMedium8110D4E0**, 0x18));
                                }
                                AudioHeap_UnapplySampleCache(slot + 0x10, M2C_FIELD(p, SampleMedium8110D4E0**, 0x10));
                            }
                        }
                        for (m = 0; m < D_811858B0[i].numDrums; m++) {
                            p = AudioPlayback_GetDrum(i, m);
                            if (p != NULL) {
                                AudioHeap_UnapplySampleCache(slot + 0x10, M2C_FIELD(p, SampleMedium8110D4E0**, 4));
                            }
                        }
                    }
                }
            }
        }
    }
}

typedef struct SampleDma8110C1C0 {
    /* 0x00 */ u8* ramAddr;
    /* 0x04 */ u32 devAddr;
    /* 0x08 */ u16 sizeUnused;
    /* 0x0A */ u16 size;
    /* 0x0C */ u8 unused;
    /* 0x0D */ u8 reuseIndex; // @unverified: same offset/use as OoT's SampleDma.reuseIndex
    /* 0x0E */ u8 ttl; // @unverified: same offset/use as OoT's SampleDma.ttl (counted down in AudioLoad_DecreaseSampleDmaTtls)
} SampleDma8110C1C0; // size = 0x10
extern SampleDma8110C1C0* D_81185688;
extern u32 D_8118568C;
extern u32 D_81185690;
extern s32 D_81185694;
extern u8 D_81185698[];
extern u8 D_81185798[];
extern u8 D_8118589A;
extern u8 D_8118589B;
/**
 * Ticks down the time-to-live of each sample DMA buffer and returns expired ones to the free list. Name follows the Zelda 64 audio driver, whose loader this matches.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void AudioLoad_DecreaseSampleDmaTtls(void) {
    u32 i;
    SampleDma8110C1C0* t;
    for (i = 0; i < D_81185690; i++) {
        t = &D_81185688[i];
        if (t->ttl != 0) {
            if (--t->ttl == 0) {
                t->reuseIndex = D_8118589A;
                D_81185698[D_8118589A++] = i;
            }
        }
    }
    for (i = D_81185690; i < D_8118568C; i++) {
        t = &D_81185688[i];
        if (t->ttl != 0) {
            if (--t->ttl == 0) {
                t->reuseIndex = D_8118589B;
                D_81185798[D_8118589B++] = i;
            }
        }
    }
    D_81185694 = 0;
}

extern u8 D_81185898;
extern u8 D_81185899;
extern u8 D_81185638[];
extern u32 D_811858F4;
extern u8 D_81185618[];
extern s8 D_81137ACC[];
s32 AudioLoad_Dma();

/**
 * Returns RAM holding the sample bytes at `devAddr`, reusing a cached DMA buffer or starting a new DMA. Name follows the Zelda 64 audio driver, whose loader this matches.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void* AudioLoad_DmaSampleData(u32 devAddr, u32 size, s32 arg2, u8* dma_index_ref, s32 medium) {
    UNUSED s32 pad1; // FAKE: stack padding
    SampleDma8110C1C0* dma;
    s32 has_dma = FALSE;
    u32 dma_dev_addr;
    UNUSED u32 pad2; // FAKE: stack padding
    u32 dma_index;
    u32 transfer;
    s32 buffer_pos;
    u32 i;

    if (arg2 != 0 || *dma_index_ref >= D_81185690) {
        for (i = D_81185690; i < D_8118568C; i++) {
            dma = &D_81185688[i];
            buffer_pos = devAddr - dma->devAddr;
            if (0 <= buffer_pos && (u32)buffer_pos <= (dma->size - size)) {
                if (dma->ttl == 0 && D_81185899 != D_8118589B) {
                    if (dma->reuseIndex != D_81185899) {
                        D_81185798[dma->reuseIndex] = D_81185798[D_81185899];
                        D_81185688[D_81185798[D_81185899]].reuseIndex = dma->reuseIndex;
                    }
                    D_81185899++;
                }
                dma->ttl = 32;
                *dma_index_ref = (u8)i;
                return (dma->ramAddr + devAddr) - dma->devAddr;
            }
        }

        if (D_81185899 != D_8118589B && arg2 != 0) {
            dma_index = D_81185798[D_81185899];
            D_81185899++;
            dma = D_81185688 + dma_index;
            has_dma = TRUE;
        }
    } else {
        dma = D_81185688 + *dma_index_ref;
        buffer_pos = devAddr - dma->devAddr;
        if (0 <= buffer_pos && (u32)buffer_pos <= dma->size - size) {
            if (dma->ttl == 0) {
                if (dma->reuseIndex != D_81185898) {
                    D_81185698[dma->reuseIndex] = D_81185698[D_81185898];
                    D_81185688[D_81185698[D_81185898]].reuseIndex = dma->reuseIndex;
                }
                D_81185898++;
            }
            dma->ttl = 2;
            return (dma->ramAddr + devAddr) - dma->devAddr;
        }
    }

    if (!has_dma) {
        if (D_81185898 == D_8118589A) {
            return NULL;
        }
        dma_index = D_81185698[D_81185898++];
        dma = D_81185688 + dma_index;
        has_dma = TRUE;
    }

    transfer = dma->size;
    dma_dev_addr = devAddr & ~0xF;
    dma->ttl = 3;
    dma->devAddr = dma_dev_addr;
    dma->sizeUnused = transfer;
    AudioLoad_Dma(&D_81185638[D_811858F4++ * 0x18], 0, 0, dma_dev_addr, dma->ramAddr, transfer, D_81185618, medium, D_81137ACC);
    *dma_index_ref = dma_index;
    return (devAddr - dma_dev_addr) + dma->ramAddr;
}

extern s32 D_811858E0;

/**
 * Allocates the sample DMA buffers: three per note (times the buffer
 * multiplier) of 0xA0 bytes for the first list, then one per note for the
 * second, trying D_811842A0 when D_811842C0 is full. Each list's reuse queue
 * is filled with the buffer indices and the rest of the queue cleared. Same
 * structure as AudioLoad_InitSampleDmaBuffers in the Ocarina of Time audio
 * library.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name guessed from the code; comment kept.
 */
void AudioLoad_InitSampleDmaBuffers(s32 num_notes) {
    s32 i;

    D_811858E0 = 0xA0;
    D_81185688 = (SampleDma8110C1C0*)func_81109868(&D_811842C0, 4 * D_811858E8 * sizeof(SampleDma8110C1C0) * D_811858B8.specUnk4);
    for (i = 0; i < 3 * D_811858E8 * D_811858B8.specUnk4; i++) {
        if ((D_81185688[D_8118568C].ramAddr = (u8*)func_81109868(&D_811842C0, D_811858E0)) == NULL) {
            if (D_811842A0 == 0) {
                break;
            }
            if ((D_81185688[D_8118568C].ramAddr = (u8*)func_81109868((M2C_UNK*)&D_811842A0, D_811858E0)) == NULL) {
                break;
            }
        }
        D_81185688[D_8118568C].size = D_811858E0;
        D_81185688[D_8118568C].devAddr = 0;
        D_81185688[D_8118568C].sizeUnused = 0;
        D_81185688[D_8118568C].unused = 0;
        D_81185688[D_8118568C].ttl = 0;
        D_8118568C++;
    }

    for (i = 0; (u32)i < D_8118568C; i++) {
        D_81185698[i] = i;
        D_81185688[i].reuseIndex = i;
    }

    for (i = D_8118568C; i < 0x100; i++) {
        D_81185698[i] = 0;
    }

    D_81185898 = 0;
    D_8118589A = D_8118568C;
    D_81185690 = D_8118568C;
    D_811858E0 = 0xA0;

    for (i = 0; i < D_811858E8; i++) {
        if ((D_81185688[D_8118568C].ramAddr = (u8*)func_81109868(&D_811842C0, D_811858E0)) == NULL) {
            if (D_811842A0 == 0) {
                break;
            }
            if ((D_81185688[D_8118568C].ramAddr = (u8*)func_81109868((M2C_UNK*)&D_811842A0, D_811858E0)) == NULL) {
                break;
            }
        }
        D_81185688[D_8118568C].size = D_811858E0;
        D_81185688[D_8118568C].devAddr = 0;
        D_81185688[D_8118568C].sizeUnused = 0;
        D_81185688[D_8118568C].unused = 0;
        D_81185688[D_8118568C].ttl = 0;
        D_8118568C++;
    }

    for (i = D_81185690; (u32)i < D_8118568C; i++) {
        D_81185798[i - D_81185690] = i;
        D_81185688[i].reuseIndex = i - D_81185690;
    }

    for (i = D_8118568C; i < 0x100; i++) {
        D_81185798[i] = D_81185690;
    }

    D_81185899 = 0;
    D_8118589B = D_8118568C - D_81185690;
}

extern u8 D_81184655[1];

/**
 * Returns 1 when font `arg0` is loaded (status 2 or above) or is 0xFF. Name follows the Zelda 64 audio driver, whose loader this matches.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
s32 AudioLoad_IsFontLoadComplete(s32 arg0) {
    if (arg0 == 0xFF) {
        return 1;
    }
    if (((u8*)&D_81184655)[arg0] >= 2) {
        return 1;
    }
    return 0;
}

extern u8 D_81184656[1];

/**
 * Returns 1 when sequence `arg0` is loaded (status 2 or above) or is 0xFF. Name follows the Zelda 64 audio driver, whose loader this matches.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
s32 AudioLoad_IsSeqLoadComplete(s32 arg0) {
    if (arg0 == 0xFF) {
        return 1;
    }
    if (((u8*)&D_81184656)[arg0] >= 2) {
        return 1;
    }
    return 0;
}

extern u8 D_81184654[1];

/**
 * Returns 1 when sample bank `arg0` is loaded (status 2 or above) or is 0xFF. Name follows the Zelda 64 audio driver, whose loader this matches.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioLoad_IsSampleLoadComplete(s32 arg0) {
    if (arg0 == 0xFF) {
        return 1;
    }
    if (((u8*)&D_81184654)[arg0] >= 2) {
        return 1;
    }
    return 0;
}

extern u8 D_81184655[1];
/**
 * Sets font `arg0`'s load status unless it is permanent (5). Name follows the Zelda 64 audio driver, whose loader this matches.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioLoad_SetFontLoadStatus(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    if (arg0 != 0xFF) {
        temp_v0 = arg0 + &D_81184655;
        if (*temp_v0 != 5) {
            *temp_v0 = arg1;
        }
    }
}

extern u8 D_81184656[1];
/**
 * Sets sequence `arg0`'s load status unless it is permanent (5). Name follows the Zelda 64 audio driver, whose loader this matches.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioLoad_SetSeqLoadStatus(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    if (arg0 != 0xFF) {
        temp_v0 = arg0 + &D_81184656;
        if (*temp_v0 != 5) {
            *temp_v0 = arg1;
        }
    }
}

extern u8 D_81184654[1];
/**
 * Sets sample bank `arg0`'s load status unless it is permanent (5). Name follows the Zelda 64 audio driver, whose loader this matches.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioLoad_SetSampleLoadStatus(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    if (arg0 != 0xFF) {
        temp_v0 = arg0 + &D_81184654;
        if (*temp_v0 != 5) {
            *temp_v0 = arg1;
        }
    }
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_8110CB70(s8 *arg0, s32 arg1, unsigned short arg2)
{
  s32 var_v0;
  s8 *var_a2;
  *((s16 *) (((s8 *) arg0) + 2)) = arg2;
  *((s32 *) (((s8 *) arg0) + 4)) = arg1;
  var_v0 = 0;
  if ((*((s16 *) (((s8 *) arg0) + 0))) > 0)
  {
 var_a2 = arg0; do { var_v0 += 1; if (((*((s32 *) (((s8 *) var_a2) + 0x14))) != 0) && ((*((s8 *) (((s8 *) var_a2) + 0x18))) == 2)) { // FAKE: decomp slop, raw pointer casts stand in for struct fields
        *((s32 *) (((s8 *) var_a2) + 0x10)) = (s32) ((*((s32 *) (((s8 *) var_a2) + 0x10))) + arg1); // FAKE: decomp slop, raw pointer casts stand in for struct fields
      }
      var_a2 += 0x10;
 } while (var_v0 < (*((s16 *) (((s8 *) arg0) + 0)))); }
}

extern u8* D_811858A8;
extern u16 D_811858AC;
s32 AudioLoad_GetRealTableIndex(M2C_UNK, s32);
s32 func_8110D4E0(s32);

s32 func_8110CBD0(s32 arg0, s32* arg1) {
    s32 off;
    s32 count;
    u8 id;
    s32 ret;

    if (arg0 >= D_811858AC) {
        return 0;
    }
    off = ((u16*)D_811858A8)[AudioLoad_GetRealTableIndex(0, arg0)];
    id = 0xFF;
    count = *(off + D_811858A8);
    off++;
    while (count > 0) {
        id = D_811858A8[off++];
        ret = func_8110D4E0(id);
        count--;
    }
    *arg1 = id;
    return ret;
}

extern u16 D_811858AC;
s32 AudioLoad_GetRealTableIndex(M2C_UNK, s32);
s32 func_8110CBD0(s32, s32*);
s32 func_8110D3D4(s32);
void func_8110CC94(s32 arg0, s32 arg1) {
    s32 sp18[2];

    if (arg0 < D_811858AC) {
        arg0 = AudioLoad_GetRealTableIndex(0, arg0);
        if (arg1 & 2) {
            func_8110CBD0(arg0, sp18);
        }
        if (arg1 & 1) {
            func_8110D3D4(arg0);
        }
    }
}

typedef struct Sample8110CD0C {
    /* 0x00 */ u32 unk00_0 : 4;
    /* 0x00 */ u32 medium : 2; // @unverified: Sample.medium bits (0 = RAM after the load), as in OoT's AudioLoad_SyncLoadSample
    /* 0x00 */ u32 unk00_6 : 1;
    /* 0x00 */ u32 isRelocated : 1; // @unverified: bit 7 of Sample byte 0, OoT's Sample.isRelocated (load only relocated samples)
    /* 0x00 */ u32 size : 24; // @unverified: Sample.size (24 bits), passed as the DMA size
    /* 0x04 */ s32 sampleAddr; // @unverified: Sample.sampleAddr: ROM address in, RAM address out
} Sample8110CD0C;
void func_8110DB8C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3);
void AudioLoad_SyncDma(s32, s32, u32, s32);
extern u8* D_811858A4;
s32 func_8110CD0C(Sample8110CD0C* arg0, s32 arg1) {
    s32 ret;

    if (arg0->isRelocated == 1) {
        if (arg0->medium != 0) {
            ret = AudioHeap_AllocPersistentSampleCache(arg0->size, arg1, arg0->sampleAddr, arg0->medium);
            if (ret == 0) {
                return -1;
            }
            if (arg0->medium == 1) {
                func_8110DB8C(arg0->sampleAddr, ret, arg0->size, *(s16*)(D_811858A4 + 2));
            } else {
                AudioLoad_SyncDma(arg0->sampleAddr, ret, arg0->size, arg0->medium);
            }
            arg0->medium = 0;
            arg0->sampleAddr = ret;
        }
    }
}

u8* AudioPlayback_GetInstrumentInner(s32, s32);
u8* AudioPlayback_GetDrum(s32, s32);
s32 func_8110CDF0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p;

    if (arg1 < 0x7F) {
        p = AudioPlayback_GetInstrumentInner(arg0, arg1);
        if (p == NULL) {
            return -1;
        }
        if (p[1] != 0) {
            func_8110CD0C(M2C_FIELD(p, Sample8110CD0C **, 8), arg0);
        }
        func_8110CD0C(M2C_FIELD(p, Sample8110CD0C **, 0x10), arg0);
        if (p[2] != 0x7F) {
            func_8110CD0C(M2C_FIELD(p, Sample8110CD0C **, 0x18), arg0);
        }
    } else if (arg1 == 0x7F) {
        p = AudioPlayback_GetDrum(arg0, arg2);
        if (p == NULL) {
            return -1;
        }
        func_8110CD0C(M2C_FIELD(p, Sample8110CD0C **, 4), arg0);
        return 0;
    }
}

M2C_UNK func_8004CFB0(s32, M2C_UNK, M2C_UNK);       /* extern */
s32 AudioLoad_GetRealTableIndex(M2C_UNK, s32);                    /* extern */
s32 AudioLoad_AsyncLoadInner(M2C_UNK, s32, s32, s32, s32);     /* extern */

/**
 * Starts an async load of sample bank `arg0`, or sends an empty message to `arg3` when nothing needs loading. Zelda 64 audio driver (load.c).
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void AudioLoad_AsyncLoadSampleBank(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (AudioLoad_AsyncLoadInner(2, AudioLoad_GetRealTableIndex(2, arg0), arg1, arg2, arg3) == 0) {
        func_8004CFB0(arg3, 0, 0);
    }
}

extern u8* D_811858A8;
void func_8110CF24(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 off;
    s32 count;

    off = ((u16*)D_811858A8)[AudioLoad_GetRealTableIndex(0, arg0)];
    count = *(off + D_811858A8);
    off++;
    while (count > 0) {
        AudioLoad_AsyncLoadInner(1, AudioLoad_GetRealTableIndex(1, D_811858A8[off++]), arg1, arg2, arg3);
        count--;
    }
}

/**
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
u8* Audio_CountActiveSoundsByCategory(s32 arg0, s32* arg1) {
    s32 off;

    off = ((u16*)D_811858A8)[AudioLoad_GetRealTableIndex(0, arg0)];
    *arg1 = *(off + D_811858A8);
    off++;
    if (*arg1 == 0) {
        return NULL;
    }
    return D_811858A8 + off;
}

void func_8110D110(s32 arg0);

void func_8110D054(s32 arg0) {
    s32 off;
    s32 count;
    s32 id;

    off = ((u16*)D_811858A8)[AudioLoad_GetRealTableIndex(0, arg0)];
    count = *(off + D_811858A8);
    off++;
    while (count > 0) {
        count--;
        id = AudioLoad_GetRealTableIndex(1, D_811858A8[off++]);
        if (AudioHeap_SearchPermanentCache(1, id) == 0) {
            func_8110D110(id);
            AudioLoad_SetFontLoadStatus(id, 0);
        }
    }
}

extern s16 D_811843BE;
extern s16 D_811843CA;
void func_8110D110(s32 arg0) {
    Cache8110A368* tbl2;
    s32 none;
    Cache8110A368* tbl = (Cache8110A368*)&D_81184380;
    u32 i;

    none = -1;
    if (arg0 == ((Cache8110A368*)((u8*)tbl + 0x20))->entries[0].id) {
        D_811843BE = none;
    } else if (arg0 == D_811843CA) {
        D_811843CA = none;
    }
    tbl2 = tbl;
    for (i = 0; i < tbl2->numEntries; i++) {
        if (arg0 == tbl2->entries[i].id) {
            tbl2->entries[i].id = none;
        }
    }
    AudioHeap_DiscardFont(arg0);
}

typedef struct SequencePlayerFromSkipTicks {
    /* 0x000 */ s32 skipTicks; // @unverified: this view starts at SequencePlayer+0xD8, OoT's SequencePlayer.skipTicks (set by AudioLoad_SyncInitSeqPlayerSkipTicks)
    /* 0x004 */ char unk004[0x158];
} SequencePlayerFromSkipTicks; // size = 0x15C
extern SequencePlayerFromSkipTicks D_81184740[];
s32 AudioLoad_SyncInitSeqPlayerInternal(s32, s32, s32);

/**
 * Clears the first word of slot arg0 in the D_81184740 array (stride 0x15C) and
 * returns AudioLoad_SyncInitSeqPlayerInternal(arg0, arg1, arg2); returns 0 without touching anything if
 * D_811859D4 is nonzero. arg1 and arg2 are passed through unchanged. Sibling of
 * AudioLoad_SyncInitSeqPlayerSkipTicks, which stores its arg2 instead of 0 and passes 0 as the last argument.
 * What the slot and the flag mean is not established.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name guessed from the code; comment kept.
 */
s32 AudioLoad_SyncInitSeqPlayer(s32 arg0, s32 arg1, s32 arg2) {
    if (D_811859D4 != 0) {
        return 0;
    }
    D_81184740[arg0].skipTicks = 0;
    return AudioLoad_SyncInitSeqPlayerInternal(arg0, arg1, arg2);
}

/**
 * Like AudioLoad_SyncInitSeqPlayer, but skips the first `arg2` ticks. Name follows the Zelda 64 audio driver, whose loader this matches.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioLoad_SyncInitSeqPlayerSkipTicks(s32 arg0, s32 arg1, s32 arg2) {
    if (D_811859D4 != 0) {
        return 0;
    }
    D_81184740[arg0].skipTicks = arg2;
    return AudioLoad_SyncInitSeqPlayerInternal(arg0, arg1, 0);
}

s32 func_8110D3D4(s32);
void func_811152A4(s32);
void func_81115254(s8*);
/**
 * Loads the sequence and its fonts, then initializes player `arg0` to play it. Name follows the Zelda 64 audio driver, whose loader this matches.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioLoad_SyncInitSeqPlayerInternal(s32 arg0, s32 arg1, s32 arg2) {
    s8* slot;
    u8 id;
    s32 count;
    s32 off;
    s32 r;
    s32 i;

    if (arg1 >= D_811858AC) {
        return 0;
    }
    slot = &D_81184668 + arg0 * 0x15C;
    arg1 = AudioLoad_GetRealTableIndex(0, arg1);
    AudioSeq_SequencePlayerDisable(slot);
    id = 0xFF;
    /* do-while(0) block (likely a macro in the original) is required for the register choice */
    do {  // FAKE
        off = ((u16*)D_811858A8)[arg1];
        count = *(off + D_811858A8);
        off++;
    } while (0);
    while (count > 0) {
        id = D_811858A8[off++];
        func_8110D4E0(id);
        count--;
    }
    r = func_8110D3D4(arg1);
    func_811152A4(arg0);
    M2C_FIELD(slot, s8*, 4) = arg1;
    M2C_FIELD(slot, u8*, 5) = id;
    ((SequencePlayer*)slot)->enabled = 1;
    M2C_FIELD(slot, s32*, 0x18) = r;
    M2C_FIELD(slot, s32*, 0x74) = r;
    M2C_FIELD(slot, s8*, 0x8C) = 0;
    M2C_FIELD(slot, s16*, 0x10) = 0;
    ((SequencePlayer*)slot)->finished = 0;
    func_81115254(slot);
    for (i = 0; i < 16; i++) {
    }
}

s32 AudioLoad_SyncLoad(s32 tableType, s32 id, s32* didAllocate);

s32 func_8110D3D4(s32 arg0) {
    s32 idx;
    s32 sp18;

    idx = AudioLoad_GetRealTableIndex(0, arg0);
    AudioLoad_SyncLoad(0, idx, &sp18);
}

u8* AudioLoad_GetLoadTable(s32);
s32 AudioLoad_SearchCaches(s32, s32);
#define ENTRY ((u8*)&((s32(*)[4])table)[arg0])
s32 func_8110D408(s32 arg0, s32* arg1) {
    s32 ret;
    u8* table = AudioLoad_GetLoadTable(2);
    s32 state;
    s32 sp28;

    arg0 = AudioLoad_GetRealTableIndex(2, arg0);
    if ((ret = AudioLoad_SearchCaches(2, arg0)) != 0) {
        AudioLoad_SetSampleLoadStatus(arg0, 2);
        *arg1 = 0;
        return ret;
    }
    state = (s8)ENTRY[0x19];
    if (state == 4) {
        *arg1 = (s8)ENTRY[0x18];
        return *(s32*)(ENTRY + 0x10);
    }
    if ((ret = AudioLoad_SyncLoad(2, arg0, &sp28)) != 0) {
        *arg1 = 0;
        return ret;
    }
    *arg1 = (s8)ENTRY[0x18];
    return *(s32*)(ENTRY + 0x10);
}
#undef ENTRY

s32 func_8110D408(s32, s32*);
void func_8110EF7C(s32, s32, s32*, s32);
s32 func_8110D4E0(s32 arg0) {
    s32 ret;
    s32 a;
    s32 b;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp20[4];

    arg0 = AudioLoad_GetRealTableIndex(1, arg0);
    a = D_811858B0[arg0].sampleBankId1;
    b = D_811858B0[arg0].sampleBankId2;
    sp20[0] = a;
    sp20[1] = b;
    if (a != 0xFF) {
        sp20[2] = func_8110D408(a, &sp30);
    } else {
        sp20[2] = 0;
    }
    if (b != 0xFF) {
        sp20[3] = func_8110D408(b, &sp34);
    } else {
        sp20[3] = 0;
    }
    ret = AudioLoad_SyncLoad(1, arg0, &sp38);
    if (ret == 0) {
        return 0;
    }
    if (sp38 == 1) {
        func_8110EF7C(arg0, ret, sp20, 0);
    }
    return ret;
}

typedef struct AudioTableEntry8110D5BC {
    /* 0x00 */ u32 romAddr;
    /* 0x04 */ u32 size;
    /* 0x08 */ s8 medium;
    /* 0x09 */ s8 cachePolicy;
    /* 0x0A */ s16 shortData1;
    /* 0x0C */ s16 shortData2;
    /* 0x0E */ s16 shortData3;
} AudioTableEntry8110D5BC; // size = 0x10

typedef struct AudioTable8110D5BC {
    /* 0x00 */ s16 numEntries;
    /* 0x02 */ s16 unkMediumParam;
    /* 0x04 */ u32 romAddr;
    /* 0x08 */ char pad[0x8];
    /* 0x10 */ AudioTableEntry8110D5BC entries[1];
} AudioTable8110D5BC;

s32 AudioHeap_AllocCached(s32, s32, s32, s32);

/**
 * Loads entry id of audio table tableType (0 sequences, 1 sound fonts, 2 sample
 * banks) synchronously and returns its RAM address, or 0 if no memory could be
 * allocated. *didAllocate says whether new memory was used (0 when the entry
 * was already cached). The table's load status is updated. Same structure as
 * AudioLoad_SyncLoad in the Ocarina of Time audio library.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
s32 AudioLoad_SyncLoad(s32 table_type, s32 id, s32* did_allocate) {
    u32 size;
    AudioTable8110D5BC* table;
    s32 ram_addr;
    u32 medium;
    s32 status;
    u32 romAddr;
    s32 cachePolicy;
    UNUSED s32 pad; // FAKE: stack padding

    ram_addr = AudioLoad_SearchCaches(table_type, id);
    if (ram_addr != 0) {
        *did_allocate = 0;
        status = 2;
    } else {
        table = (AudioTable8110D5BC*)AudioLoad_GetLoadTable(table_type);
        size = table->entries[id].size;
        size = ALIGN16(size);
        medium = table->entries[id].medium;
        cachePolicy = table->entries[id].cachePolicy;
        romAddr = table->entries[id].romAddr;
        switch (cachePolicy) {
            case 0:
                ram_addr = AudioHeap_AllocPermanent(table_type, id, size);
                if (ram_addr == 0) {
                    return ram_addr;
                }
                break;
            case 1:
                ram_addr = AudioHeap_AllocCached(table_type, size, 1, id);
                if (ram_addr == 0) {
                    return ram_addr;
                }
                break;
            case 2:
                ram_addr = AudioHeap_AllocCached(table_type, size, 0, id);
                if (ram_addr == 0) {
                    return ram_addr;
                }
                break;
            case 3:
            case 4:
                ram_addr = AudioHeap_AllocCached(table_type, size, 2, id);
                if (ram_addr == 0) {
                    return ram_addr;
                }
                break;
        }

        *did_allocate = 1;
        if (medium == 1) {
            func_8110DB8C(romAddr, ram_addr, size, table->unkMediumParam);
        } else {
            AudioLoad_SyncDma(romAddr, ram_addr, size, medium);
        }

        status = cachePolicy == 0 ? 5 : 2;
    }

    switch (table_type) {
        case 0:
            AudioLoad_SetSeqLoadStatus(id, status);
            break;
        case 1:
            AudioLoad_SetFontLoadStatus(id, status);
            break;
        case 2:
            AudioLoad_SetSampleLoadStatus(id, status);
            break;
    }

    return ram_addr;
}

u8* AudioLoad_GetLoadTable(s32);
/**
 * Returns the real index of entry `arg1` in load table `arg0`: an entry with size 0 is an alias whose ROM address field holds the real index. Name follows the Zelda 64 audio driver, whose loader this matches.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioLoad_GetRealTableIndex(s32 arg0, s32 arg1) {
    s32* entry = (s32*)(AudioLoad_GetLoadTable(arg0) + arg1 * 16);

    if (entry[5] == 0) {
        arg1 = entry[4];
    }
    return arg1;
}

s32 AudioHeap_SearchCaches(s32, M2C_UNK, s32);               /* extern */

/**
 * Looks entry `arg1` of table `arg0` up in the permanent cache, then the other caches. Name follows the Zelda 64 audio driver, whose loader this matches.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioLoad_SearchCaches(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = AudioHeap_SearchPermanentCache(arg0, arg1);
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = AudioHeap_SearchCaches(arg0, 2, arg1);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

extern u8* D_8118589C;
extern u8* D_811858A0;
extern u8* D_811858A4;

/**
 * AudioLoad_GetLoadTable
 *
 * Returns the pointer stored in D_8118589C, D_811858A0 or D_811858A4 for
 * arg0 = 0, 1 or 2, and NULL for any other value (the caller treats the result
 * as a byte pointer to a table indexed in 16-byte steps). What the three
 * tables are is not established.
 * Matching note: the result is built in a local and returned once; separate
 * `return` statements in each case give a different register choice.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name guessed from the code; comment kept.
 */
u8* AudioLoad_GetLoadTable(s32 arg0) {
    u8* ret;
    ret = NULL;
    switch (arg0) {
    case 0:
        ret = D_8118589C;
        break;
    case 1:
        ret = D_811858A0;
        break;
    case 2:
        ret = D_811858A4;
        break;
    }
    return ret;
}

void AudioLoad_RelocateSample(void* sampleP, u32 fontDataAddr, void* relocInfo);

/**
 * Relocates a sound font loaded at fontData: the drum and instrument pointer
 * lists, each drum's and instrument's samples and envelope, and records the
 * font's drum and instrument lists in D_811858B0. Same structure as
 * AudioLoad_RelocateFont in the Ocarina of Time audio library.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioLoad_RelocateFont(s32 font_id, u32 font_data, void* reloc_info) {
    u32 reloc2;
    u32 reloc;
    s32 i;
    u8* drum;
    u32* ptrs = (u32*)font_data;
    s32 num_drums = D_811858B0[font_id].numDrums;
    u8* inst;
    s32 num_instruments = D_811858B0[font_id].numInstruments;

    reloc2 = ptrs[0];
    if ((reloc2 != 0) && (num_drums != 0)) {
        ptrs[0] = reloc2 + font_data;
        for (i = 0; i < num_drums; i++) {
            reloc = ((u32*)ptrs[0])[i];
            if (reloc != 0) {
                reloc += font_data;
                ((u32*)ptrs[0])[i] = reloc;
                drum = (u8*)reloc;
                if (drum[2] == 0) {
                    AudioLoad_RelocateSample(drum + 4, font_data, reloc_info);
                    reloc = *(u32*)(drum + 0xC);
                    drum[2] = 1;
                    *(u32*)(drum + 0xC) = reloc + font_data;
                }
            }
        }
    }

    if (num_instruments >= 0x80) {
        num_instruments = 0x7F;
    }

    for (i = 1; i <= num_instruments; i++) {
        if (ptrs[i] != 0) {
            ptrs[i] += font_data;
            inst = (u8*)ptrs[i];
            if (inst[0] == 0) {
                if (inst[1] != 0) {
                    AudioLoad_RelocateSample(inst + 8, font_data, reloc_info);
                }
                AudioLoad_RelocateSample(inst + 0x10, font_data, reloc_info);
                if (inst[2] != 0x7F) {
                    AudioLoad_RelocateSample(inst + 0x18, font_data, reloc_info);
                }
                reloc = *(u32*)(inst + 4);
                inst[0] = 1;
                *(u32*)(inst + 4) = reloc + font_data;
            }
        }
    }

    D_811858B0[font_id].drums = (u8**)ptrs[0];
    D_811858B0[font_id].instruments = (u8**)(ptrs + 1);
}

extern s8 D_81137C1C[];
extern s8 D_81137C28[];
extern u8 D_81185650[];
extern u8 D_81185670[];
void func_80056730(s32, u32);
void func_8004D1C0(void*, s32, s32);
s32 AudioLoad_Dma();
/**
 * Copies `arg2` bytes (rounded up to 16) from ROM `arg0` to RAM `arg1` in 1 KB DMA chunks and waits for each. Name follows the Zelda 64 audio driver, whose loader this matches.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioLoad_SyncDma(s32 arg0, s32 arg1, u32 arg2, s32 arg3) {

    arg2 = (arg2 + 0xF) & ~0xF;
    func_80056730(arg1, arg2);
    while (TRUE) {
        if (arg2 < 0x400) {
            break;
        }
        AudioLoad_Dma(D_81185670, 1, 0, arg0, arg1, 0x400, D_81185650, arg3, D_81137C1C);
        func_8004D1C0(D_81185650, 0, 1);
        arg2 -= 0x400;
        arg0 += 0x400;
        arg1 += 0x400;
    }
    if (arg2 != 0) {
        AudioLoad_Dma(D_81185670, 1, 0, arg0, arg1, arg2, D_81185650, arg3, D_81137C28);
        func_8004D1C0(D_81185650, 0, 1);
    }
}

void func_8110DB8C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {

}

typedef struct IoMesg8110DBA0 {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 pri;
    /* 0x03 */ u8 status;
    /* 0x04 */ void* retQueue;
    /* 0x08 */ void* dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
} IoMesg8110DBA0;
s32 func_800593D0(void);
s32 func_80051E60(void);
void func_80056530(s32, IoMesg8110DBA0*, s32);
/**
 * Starts a PI DMA for audio data through the message queue `mq`; refuses when more than 16 are pending. Name follows the Zelda 64 audio driver, whose loader this matches.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioLoad_Dma(IoMesg8110DBA0* mb, s32 pri, s32 direction, u32 devAddr, void* dramAddr, u32 size, void* mq, s32 kind) {
    s32 handle;

    if ((u32)D_811859D4 > 16) {
        return -1;
    }
    switch (kind) {
        case 2:
            handle = func_800593D0();
            break;
        case 3:
            handle = func_80051E60();
            break;
        default:
            return 0;
    }
    if (size & 0xF) {
        size = (size + 0xF) & ~0xF;
    }
    mb->pri = pri;
    mb->retQueue = mq;
    mb->dramAddr = dramAddr;
    mb->devAddr = devAddr;
    mb->size = size;
    M2C_FIELD(handle, s32*, 0x14) = 2;
    func_80056530(handle, mb, direction);
    return 0;
}
