/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_engine/battle_engine_309ED0.c. */

#include "audio_and_gb_emulator.h"
extern s32 pad_D_84390210[4];
extern s32 sMultihitCount;
extern s32 sMultihitCountdown;

#include "m2c_macros.h"

void func_8110DC90(void);
void func_8110DC98(void);
s32 BattleScene_EndStatusAnimationsAndCommit(ActivePokemon* arg0);
void func_8110E714(void);

void func_8110DC90(void) {
}

void func_8110DC98(void) {
}

void AudioLoad_SyncLoad(Particle* arg0, s32 arg1, s32* arg2);

void func_8110DCA0(Particle* arg0, s32 arg1) {
    s32 sp1C;

    AudioLoad_SyncLoad(arg0, arg1, &sp1C);
}

typedef struct AudioTableEntry8110DCC0 {
    /* 0x00 */ s32 romAddr;
    /* 0x04 */ u32 size;
    /* 0x08 */ s8 medium;
    /* 0x09 */ s8 cachePolicy;
    /* 0x0A */ s16 shortData1;
    /* 0x0C */ s16 shortData2;
    /* 0x0E */ s16 shortData3;
} AudioTableEntry8110DCC0; // size = 0x10

typedef struct AudioTable8110DCC0 {
    /* 0x00 */ s16 numEntries;
    /* 0x02 */ s16 unkMediumParam;
    /* 0x04 */ s32 romAddr;
    /* 0x08 */ char pad[0x8];
    /* 0x10 */ AudioTableEntry8110DCC0 entries[1];
} AudioTable8110DCC0;

extern u8 D_81184654[];
extern u8 D_81184655[];
extern u8 D_81184656[];
s32 AudioLoad_SearchCaches(s32, s32);
struct Table8110D840* AudioLoad_GetLoadTable(s32);
s32 AudioHeap_AllocPermanent(s32, s32, s32);
s32 AudioHeap_AllocCached(s32, s32, s32, s32);
s32 func_8004CFB0(OSMesgQueue*, OSMesg, s32);
void AudioLoad_SetFontLoadStatus(s32, s32);
void AudioLoad_SetSeqLoadStatus(s32, s32);
void AudioLoad_SetSampleLoadStatus(s32, s32);
struct Entry8110EABC* func_8110E9A8(s32, s32, u32, s32, s32, OSMesgQueue*, u32);

/**
 * Starts an asynchronous load of entry id of audio table tableType (0 sequences,
 * 1 sound fonts, 2 sample banks). Returns 0 if a load of it is already in
 * progress or no memory could be allocated. If the entry is already cached the
 * cached address is returned and retData is posted to retQueue at once;
 * otherwise memory is allocated by the entry's cache policy and a chunked DMA
 * is started. The table's load status is updated either way. Same structure as
 * AudioLoad_AsyncLoadInner in the Ocarina of Time audio library.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
s32 AudioLoad_AsyncLoadInner(s32 table_type, s32 id, s32 n_chunks, s32 ret_data, OSMesgQueue* ret_queue) {
    u32 size;
    AudioTable8110DCC0* table;
    s32 ram_addr;
    s32 medium;
    s8 cachePolicy;
    u32 dev_addr;
    s32 load_status;

    switch (table_type) {
        case 0:
            if (D_81184656[id] == 1) {
                return 0;
            }
            break;
        case 1:
            if (D_81184655[id] == 1) {
                return 0;
            }
            break;
        case 2:
            if (D_81184654[id] == 1) {
                return 0;
            }
            break;
    }

    ram_addr = AudioLoad_SearchCaches(table_type, id);
    if (ram_addr != 0) {
        load_status = 2;
        func_8004CFB0(ret_queue, (OSMesg)(ret_data << 0x18), 0);
    } else {
        table = (AudioTable8110DCC0*)AudioLoad_GetLoadTable(table_type);
        size = table->entries[id].size;
        size = ALIGN16(size);
        medium = table->entries[id].medium;
        cachePolicy = table->entries[id].cachePolicy;
        dev_addr = table->entries[id].romAddr;
        load_status = 2;

        switch (cachePolicy) {
            case 0:
                ram_addr = AudioHeap_AllocPermanent(table_type, id, size);
                if (ram_addr == 0) {
                    return ram_addr;
                }
                load_status = 5;
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

        func_8110E9A8(dev_addr, ram_addr, size, medium, n_chunks, ret_queue, (ret_data << 0x18) | (table_type << 0x10) | (id << 8) | load_status);
        load_status = 1;
    }

    switch (table_type) {
        case 0:
            AudioLoad_SetSeqLoadStatus(id, load_status);
            break;
        case 1:
            AudioLoad_SetFontLoadStatus(id, load_status);
            break;
        case 2:
            AudioLoad_SetSampleLoadStatus(id, load_status);
            break;
    }

    return ram_addr;
}

/** Ends a Pokemon's status animations and commits the result. */
s32 BattleScene_EndStatusAnimationsAndCommit(ActivePokemon* arg0) {
    BattleAnim_ClearFreezeStatusAnimation(arg0);
    BattleAnim_EndSleepStatusAnimation(arg0);
    Battle_ApplyAnimStateEffects(arg0);
}

extern SoundFont* D_811858B0;

extern volatile s32 D_811859D4;
extern s32 D_811526FC;
extern u64 D_81186270[];
extern u64 D_81184100;
extern u64 D_81186258;
extern f32 D_811859B0;
extern s32 D_811859B4;
extern s16 D_811859C4[3];
extern s16* D_811859B8[3];
extern volatile s32 D_811858F0;
extern s32 D_811858F8;
extern s32 D_811858FC;
extern s8 D_811858EE;
extern s32 D_8118590C;
extern u8 D_81185910[];
extern OSMesgQueue D_81185650;
extern OSMesg D_81185668[];
extern OSMesgQueue D_81185618;
extern OSMesg D_81185630[];
extern OSMesgQueue D_811855D8;
extern OSMesg D_811855F0[];
extern OSMesgQueue D_811855F8;
extern OSMesg D_81185610[];
extern s32 D_811858F4;
extern s32 D_8118568C;
extern s32 D_81152700;
extern s32 D_81152704;
extern u8 D_811842B0[];
extern AudioPermanentCache D_81184440;
extern volatile s8 D_81184657;
extern s8 D_81184658;
extern AudioTable8110DCC0* D_8118589C;
extern AudioTable8110DCC0* D_811858A0;
extern u8* D_811858A4;
extern u8* D_811858A8;
extern s16 D_811858AC;
extern AudioTable8110DCC0 D_81152760;
extern AudioTable8110DCC0 D_81152720;
extern AudioTable8110DCC0 D_81152740;
extern u8 D_81152710[];
extern u8 D_0015AE60[];
extern u8 D_0015A9B0[];
extern u8 D_0015AA60[];
void func_8111016C(void);
void AudioHeap_InitMainPools(s32);
void* func_81109868(void*, s32);
void func_811098C0(void*, void*, s32);
s32 AudioHeap_ResetStep(void);
void func_8110CB70(AudioTable8110DCC0*, u8*, s32);

/**
 * Initializes the audio system: clears the heap and the audio globals, sets up
 * the message queues and the three output buffers, points the sequence, font
 * and sample tables at their ROM copies and fills in each font's sample bank
 * ids and instrument and drum counts. Same structure as AudioLoad_Init in the
 * Ocarina of Time audio library.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name guessed from the code; comment kept.
 */
void AudioLoad_Init(void) {
    s32 num_fonts;
    void* ram_addr;
    s32 i;
    s32 j;
    u64* ptr;
    s16* buf;
    s32 count;

    D_811859D4 = 0;

    for (i = 0; i < D_811526FC / 8; i++) {
        D_81186270[i] = 0;
    }

    ptr = &D_81184100;
    for (count = ((u32)&D_81186258 - (u32)&D_81184100) / 8; count >= 0; count--) {
        *ptr++ = 0;
    }

    D_811859B0 = 16.713f;
    D_811859B4 = 0x3C;
    func_8111016C();

    for (i = 0; i < 3; i++) {
        D_811859C4[i] = 0xA0;
    }

    D_811858F0 = 0;
    D_811858F8 = 0;
    D_811858FC = 0;
    D_811858EE = 0;
    D_8118590C = 0;
    *(s32*)(D_81185910 + 0x34) = 0;
    *(s32*)(D_81185910 + 0x84) = 0;

    osCreateMesgQueue(&D_81185650, D_81185668, 1);
    osCreateMesgQueue(&D_81185618, D_81185630, 1);
    osCreateMesgQueue(&D_811855D8, D_811855F0, 1);
    osCreateMesgQueue(&D_811855F8, D_81185610, 1);
    D_811858F4 = 0;
    D_8118568C = 0;
    AudioHeap_InitMainPools(D_81152700);

    for (i = 0; i < 3; i++) {
        buf = D_811859B8[i] = func_81109868(D_811842B0, 0xFC0);
        for (j = 0; j < 2016; j++) {
            *buf++ = 0;
        }
    }

    D_81184658 = 0;
    D_81184657 = 1;
    AudioHeap_ResetStep();

    D_8118589C = &D_81152760;
    D_811858A0 = &D_81152720;
    D_811858A4 = (u8*)&D_81152740;
    D_811858A8 = D_81152710;
    D_811858AC = D_8118589C->numEntries;

    func_8110CB70(D_8118589C, D_0015AE60, 0);
    func_8110CB70(D_811858A0, D_0015A9B0, 0);
    func_8110CB70((AudioTable8110DCC0*)D_811858A4, D_0015AA60, 0);

    num_fonts = D_811858A0->numEntries;
    D_811858B0 = func_81109868(D_811842B0, num_fonts * sizeof(SoundFont));
    for (i = 0; i < num_fonts; i++) {
        D_811858B0[i].sampleBankId1 = D_811858A0->entries[i].shortData1 >> 8 & 0xFF;
        D_811858B0[i].sampleBankId2 = D_811858A0->entries[i].shortData1 & 0xFF;
        D_811858B0[i].numInstruments = D_811858A0->entries[i].shortData2 >> 8 & 0xFF;
        D_811858B0[i].numDrums = D_811858A0->entries[i].shortData2 & 0xFF;
    }

    ram_addr = func_81109868(D_811842B0, D_81152704);
    if (ram_addr == NULL) {
        D_81152704 = 0;
    }
    func_811098C0(&D_81184440, ram_addr, D_81152704);
}

typedef struct Sample8110E500 {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 unk_00 : 2;
    /* 0x00 */ u32 size : 24;
    /* 0x04 */ s32 devAddr;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} Sample8110E500; // size = 0x10

typedef struct SlowLoad8110E500 {
    /* 0x00 */ u8 medium;
    /* 0x01 */ u8 seqOrFontId; // @unverified: same offset/use as OoT's AudioSlowLoad.seqOrFontId
    /* 0x02 */ u8 instId; // @unverified: same offset/use as OoT's AudioSlowLoad.instId
    /* 0x04 */ s32 curDevAddr; // @unverified: same offset/use as OoT's AudioSlowLoad.curDevAddr
    /* 0x08 */ s32 curRamAddr; // @unverified: same offset/use as OoT's AudioSlowLoad.curRamAddr (the allocation; advanced while loading)
    /* 0x0C */ s32 ramAddr; // @unverified: same offset/use as OoT's AudioSlowLoad.ramAddr (start of the loaded sample)
    /* 0x10 */ s32 state;
    /* 0x14 */ s32 bytesRemaining; // @unverified: same offset/use as OoT's AudioSlowLoad.bytesRemaining
    /* 0x18 */ s8* status;
    /* 0x1C */ Sample8110E500 sample; // @unverified: same offset/use as OoT's AudioSlowLoad.sample (copy of the font's sample header)
    /* 0x2C */ u8 unk_2C[0x34];
} SlowLoad8110E500; // size = 0x60

typedef struct SlowLoads8110E500 {
    /* 0x00 */ s32 index;
    /* 0x04 */ SlowLoad8110E500 slots[2];
} SlowLoads8110E500;

extern SlowLoads8110E500 D_81180610;
s32 AudioHeap_AllocTemporarySampleCache(s32, s32, s32, s8);
s32 func_8110E6B0(s32 arg0, s32 arg1);

s32 func_8110E500(s32 arg0, u8 arg1, s8* status) {
    Sample8110E500* header = (Sample8110E500*)func_8110E6B0(arg0, arg1);
    SlowLoad8110E500* load;

    if (header == NULL) {
        *status = 0;
        return -1;
    }
    if (header->medium == 0) {
        *status = 2;
        return 0;
    }
    load = &D_81180610.slots[D_81180610.index];
    if (load->state == 3) {
        load->state = 0;
    }
    load->sample = *header;
    load->status = status;
    load->curRamAddr = AudioHeap_AllocTemporarySampleCache(header->size, arg0, header->devAddr, header->medium);
    if (load->curRamAddr == 0) {
        if ((header->medium == 1) || (header->codec == 2)) {
            *status = 0;
            return -1;
        }
        *status = 3;
        return -1;
    }
    load->state = 1;
    load->bytesRemaining = ALIGN16(header->size);
    load->ramAddr = load->curRamAddr;
    load->curDevAddr = header->devAddr;
    load->medium = header->medium;
    load->seqOrFontId = arg0;
    load->instId = arg1;
    D_81180610.index ^= 1;
    return 0;
}

s32* AudioPlayback_GetInstrumentInner(s32, s32);
s32* AudioPlayback_GetDrum(s32, s32);
s32 func_8110E6B0(s32 arg0, s32 arg1) {
    s32* p;
    s32 v;

    if (arg1 < 0x80) {
        p = AudioPlayback_GetInstrumentInner(arg0, arg1);
        if (p == NULL) {
            return 0;
        }
        v = p[4];
    } else {
        p = AudioPlayback_GetDrum(arg0, arg1 - 0x80);
        if (p == NULL) {
            return 0;
        }
        v = p[1];
    }
    return v;
}

void func_8110E714(void) {
}

/** Four consecutive words, copied as a unit. */
typedef struct Words4_8110E71C {
    s32 w[4];
} Words4_8110E71C;

/** The Sample that func_8110E6B0 returns for a font instrument or drum. */
typedef struct Sample8110E71C {
    /* 0x00 */ u8 flags; // @unverified: Sample byte 0 (codec/medium/flags); func_8110E71C clears medium (bits 2-3) to RAM
    /* 0x01 */ u8 unk_01[3];
    /* 0x04 */ s32 sampleAddr; // @unverified: Sample.sampleAddr, pointed at the slow-loaded copy (OoT's AudioLoad_FinishSlowLoad)
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} Sample8110E71C;

/** A slow sample load (OoT AudioSlowLoad), as func_8110E71C (OoT AudioLoad_FinishSlowLoad) sees it. */
typedef struct SlowLoad8110E71C {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 seqOrFontId; // @unverified: same offset/use as OoT's AudioSlowLoad.seqOrFontId
    /* 0x02 */ u8 instId; // @unverified: same offset/use as OoT's AudioSlowLoad.instId
    /* 0x03 */ u8 unk_03[9];
    /* 0x0C */ s32 ramAddr; // @unverified: same offset/use as OoT's AudioSlowLoad.ramAddr
    /* 0x10 */ u8 unk_10[0xC];
    /* 0x1C */ Words4_8110E71C sample; // @unverified: same offset/use as OoT's AudioSlowLoad.sample
} SlowLoad8110E71C;

/**
 * Looks up the entry for (keyA, keyB) with func_8110E6B0. If one exists, its
 * 16 bytes are copied into arg0->copy, the entry's second word is
 * overwritten with arg0->unk_0C, and bits 2 and 3 of its first byte are
 * cleared.
 */
void func_8110E71C(SlowLoad8110E71C* arg0) {
    Sample8110E71C* entry;

    entry = (Sample8110E71C*)func_8110E6B0(arg0->seqOrFontId, arg0->instId);
    if (entry != NULL) {
        arg0->sample = *(Words4_8110E71C*)entry;
        entry->sampleAddr = arg0->ramAddr;
        entry->flags &= 0xFFF3;
    }
}

s32 func_8004D1C0(OSMesgQueue*, u32*, s32);
void func_8110E910(s8* arg0, s32 arg1);
void func_8110E994(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3);

/**
 * Zero's version of OoT's AudioLoad_ProcessSlowLoads: steps the two slow sample
 * loads, copying at most 0x1000 bytes per call and finishing a load once nothing
 * is left.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioLoad_ProcessSlowLoads(s32 reset_status) {
    u8* table = D_811858A4;
    SlowLoad8110E500* load;
    s32 i;

    for (i = 0; i < 2; i++) {
        load = &D_81180610.slots[i];
        switch (D_81180610.slots[i].state) {
            case 2:
                func_8004D1C0((OSMesgQueue*)load->unk_2C, NULL, 1);
                if (reset_status != 0) {
                    load->state = 3;
                    break;
                }
            case 1:
                load->state = 2;
                if (load->bytesRemaining == 0) {
                    func_8110E71C((SlowLoad8110E71C*)load);
                    load->state = 3;
                    *load->status = 1;
                } else if (load->bytesRemaining < 0x1000) {
                    if (load->medium == 1) {
                        u32 size = load->bytesRemaining;

                        func_8110E994(load->curDevAddr, load->curRamAddr, size, *(s16*)(table + 2));
                    } else {
                        func_8110E910((s8*)load, load->bytesRemaining);
                    }
                    load->bytesRemaining = 0;
                } else {
                    if (load->medium == 1) {
                        func_8110E994(load->curDevAddr, load->curRamAddr, 0x1000, *(s16*)(table + 2));
                    } else {
                        func_8110E910((s8*)load, 0x1000);
                    }
                    load->bytesRemaining -= 0x1000;
                    load->curRamAddr += 0x1000;
                    load->curDevAddr += 0x1000;
                }
                break;
        }
    }
}

extern u8 D_81137E3C[];
void AudioLoad_Dma(s8*, s32, s32, s32, s32, s32, OSMesgQueue*, s32, u8*);

void func_8110E910(s8* arg0, s32 arg1) {
    osInvalDCache((void*)M2C_FIELD(arg0, s32*, 8), arg1);
    osCreateMesgQueue((OSMesgQueue*)(arg0 + 0x2C), (OSMesg*)(arg0 + 0x44), 1);
    AudioLoad_Dma(arg0 + 0x48, 0, 0, M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 8), arg1, (OSMesgQueue*)(arg0 + 0x2C), *(u8*)arg0, D_81137E3C);
}

void func_8110E994(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {

}

typedef struct Entry8110EABC {
    /* 0x00 */ s8 active;
    /* 0x01 */ s8 state;
    /* 0x02 */ s8 medium;
    /* 0x04 */ s32 ramAddr;
    /* 0x08 */ s32 romAddr;
    /* 0x0C */ s32 curAddr;
    /* 0x10 */ u32 size;
    /* 0x14 */ u32 chunkSize;
    /* 0x18 */ OSMesg info;
    /* 0x1C */ OSMesgQueue* doneQueue;
    /* 0x20 */ OSMesgQueue queue;
    /* 0x38 */ OSMesg msg;
    /* 0x3C */ char unk3C[0x18];
} Entry8110EABC; // size = 0x54
extern Entry8110EABC D_81185580[1];

Entry8110EABC* func_8110E9A8(s32, s32, u32, s32, s32, OSMesgQueue*, u32);

void func_800567E0(OSMesgQueue*, OSMesg*, s32);
/**
 * Claims the free async load slot and starts a chunked DMA of size bytes from
 * devAddr to ramAddr. nChunks == 0 means 0x1000-byte chunks; otherwise the size
 * is split into nChunks pieces rounded up to 0x100 (at least 0x100). retMsg is
 * sent to retQueue when the load finishes. Returns NULL when no slot is free.
 */
Entry8110EABC* func_8110E9A8(s32 dev_addr, s32 ramAddr, u32 size, s32 medium, s32 n_chunks, OSMesgQueue* ret_queue, u32 ret_msg) {
    Entry8110EABC* load;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_81185580); i++) {
        if (D_81185580[i].active == 0) {
            load = &D_81185580[i];
            break;
        }
    }

    if (i == ARRAY_COUNT(D_81185580)) {
        return NULL;
    }

    load->active = 1;
    load->romAddr = dev_addr;
    load->ramAddr = ramAddr;
    load->curAddr = ramAddr;
    load->size = size;

    if (n_chunks == 0) {
        load->chunkSize = 0x1000;
    } else {
        load->chunkSize = ((s32)size / n_chunks + 0xFF) & ~0xFF;
        if (load->chunkSize < 0x100) {
            load->chunkSize = 0x100;
        }
    }

    load->doneQueue = ret_queue;
    load->state = 3;
    load->medium = medium;
    load->info = (OSMesg)ret_msg;
    func_800567E0(&load->queue, &load->msg, 1);
    return load;
}

extern volatile s32 D_811859D4;
void func_8110EB40(Entry8110EABC*, s32);
/** Applies animation state effects for every Pokemon. */
void Battle_ApplyAnimStateEffects(s32 arg0) {
    s32 i;

    if (D_811859D4 != 1U) {
        for (i = 0; i < 1; i++) {
            if (D_81185580[i].active == 1) {
                func_8110EB40(&D_81185580[i], arg0);
            }
        }
    }
}

typedef struct RelocInfo8110EF7C {
    /* 0x00 */ s32 sampleBankId1;
    /* 0x04 */ s32 sampleBankId2;
    /* 0x08 */ s32 baseAddr1;
    /* 0x0C */ s32 baseAddr2;
    /* 0x10 */ u32 medium1;
    /* 0x14 */ u32 medium2;
} RelocInfo8110EF7C;

s32 func_8004D1C0(OSMesgQueue*, u32*, s32);
s32 func_8110D408(s32, u32*);
void func_8110ED98(s8* arg0, u32 arg1);
void func_8110EE28(s32 arg0, M2C_UNK arg1, u32 arg2, M2C_UNK arg3);
void func_8110EF7C(s32 size, s32 fontData, RelocInfo8110EF7C* relocInfo, s32 async);

void func_8110EB40(Entry8110EABC* load, s32 reset_status) {
    u8* table = D_811858A4;
    u32 info;
    s32 font_id;
    UNUSED s32 pad[2]; // FAKE
    u32 sampleBankId1;
    u32 sampleBankId2;
    RelocInfo8110EF7C reloc_info;

    if (load->state >= 2) {
        load->state--;
        return;
    }
    if (load->state == 1) {
        load->state = 0;
    } else if (reset_status != 0) {
        func_8004D1C0(&load->queue, 0, 1);
        load->active = 0;
        return;
    } else if (func_8004D1C0(&load->queue, 0, 0) == -1) {
        return;
    }
    if (load->size == 0) {
        info = (u32)load->info;
        switch ((u8)(info >> 16)) {
            case 0:
                AudioLoad_SetSeqLoadStatus((u8)(info >> 8), (u8)info);
                break;
            case 2:
                AudioLoad_SetSampleLoadStatus((u8)(info >> 8), (u8)info);
                break;
            case 1:
                font_id = (u8)(info >> 8);
                AudioLoad_SetFontLoadStatus(font_id, (u8)info);
                sampleBankId1 = D_811858B0[font_id].sampleBankId1;
                sampleBankId2 = D_811858B0[font_id].sampleBankId2;
                reloc_info.sampleBankId1 = sampleBankId1;
                reloc_info.sampleBankId2 = sampleBankId2;
                reloc_info.baseAddr1 = (sampleBankId1 != 0xFF) ? func_8110D408(sampleBankId1, &reloc_info.medium1) : 0;
                reloc_info.baseAddr2 = (sampleBankId2 != 0xFF) ? func_8110D408(sampleBankId2, &reloc_info.medium2) : 0;
                func_8110EF7C(font_id, load->ramAddr, &reloc_info, 1);
                break;
        }
        load->active = 0;
        func_8004CFB0(load->doneQueue, load->info, 0);
        return;
    }
    if (load->size < load->chunkSize) {
        if (load->medium == 1) {
            func_8110EE28(load->romAddr, load->curAddr, load->size, *((s16*)(table + 2)));
        } else {
            func_8110ED98((s8*)load, load->size);
        }
        load->size = 0;
        return;
    }
    if (load->medium == 1) {
        func_8110EE28(load->romAddr, load->curAddr, load->chunkSize, *((s16*)(table + 2)));
    } else {
        func_8110ED98((s8*)load, load->chunkSize);
    }
    load->size -= load->chunkSize;
    load->romAddr += load->chunkSize;
    load->curAddr += load->chunkSize;
}

extern u8 D_81137F04[];

void func_8110ED98(s8* arg0, u32 arg1) {
    arg1 = (arg1 + 0xF) & ~0xF;
    osInvalDCache((void*)M2C_FIELD(arg0, s32*, 0xC), arg1);
    osCreateMesgQueue((OSMesgQueue*)(arg0 + 0x20), (OSMesg*)(arg0 + 0x38), 1);
    AudioLoad_Dma(arg0 + 0x3C, 0, 0, M2C_FIELD(arg0, s32*, 8), M2C_FIELD(arg0, s32*, 0xC), arg1, (OSMesgQueue*)(arg0 + 0x20), arg0[2], D_81137F04);
    if (arg1) {}  // karodo
}

void func_8110EE28(s32 arg0, M2C_UNK arg1, u32 arg2, M2C_UNK arg3) {

}

/* First word of a Sample (OoT layout: codec, medium, unk_bit26, isRelocated, size). */
typedef struct {
    u32 bits31_28 : 4;
    u32 medium : 2; // @unverified: Sample.medium bits (OoT layout)
    u32 unk_bit26 : 1; // @unverified: Sample bit 26, same position as OoT's Sample.unk_bit26
    u32 bit24 : 1;
    u32 size : 24; // @unverified: Sample.size (24 bits)
} SampleFlags8110F64C;

extern SampleFlags8110F64C *D_81184978[];
extern s32 D_81185578;

typedef struct Sample8110EE3C {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 unk_bit26 : 1;
    /* 0x00 */ u32 isRelocated : 1;
    /* 0x00 */ u32 size : 24;
    /* 0x04 */ s32 sampleAddr;
    /* 0x08 */ s32 loop;
    /* 0x0C */ s32 book;
} Sample8110EE3C;

/**
 * Relocates a sound font sample: the sample pointer and its loop and book
 * pointers are made absolute against the font's RAM address, and the sample
 * data address against the sample bank chosen by its medium. Samples flagged
 * for preloading that are not in RAM are added to D_81184978. Same structure as
 * AudioLoad_RelocateSample in the Ocarina of Time audio library.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioLoad_RelocateSample(Sample8110EE3C** sampleP, s32 font_data_addr, RelocInfo8110EF7C* reloc_info) {
    Sample8110EE3C* sample;
    s32 reloc;

    if ((u32)*sampleP <= 0x80000000) {
        reloc = (u32)*sampleP + font_data_addr;
        *sampleP = (Sample8110EE3C*)reloc;
        sample = (Sample8110EE3C*)reloc;

        if ((sample->size != 0) && (sample->isRelocated != 1)) {
            reloc = sample->loop + font_data_addr;
            sample->loop = reloc;
            reloc = sample->book + font_data_addr;
            sample->book = reloc;

            switch (sample->medium) {
                case 0:
                    reloc = sample->sampleAddr + reloc_info->baseAddr1;
                    sample->sampleAddr = reloc;
                    sample->medium = reloc_info->medium1;
                    break;
                case 1:
                    reloc = sample->sampleAddr + reloc_info->baseAddr2;
                    sample->sampleAddr = reloc;
                    sample->medium = reloc_info->medium2;
                    break;
                case 2:
                case 3:
                    break;
            }

            sample->isRelocated = 1;
            if (sample->unk_bit26 && (sample->medium != 0)) {
                D_81184978[D_81185578++] = (SampleFlags8110F64C*)sample;
            }
        }
    }
}

typedef struct Sample8110EF7C {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 unk_bit26 : 1;
    /* 0x00 */ u32 isRelocated : 1;
    /* 0x00 */ u32 size : 24;
    /* 0x04 */ s32 sampleAddr;
} Sample8110EF7C;

typedef struct Preload8110EF7C {
    /* 0x00 */ u32 endAndMediumKey;
    /* 0x04 */ Sample8110EF7C* sample;
    /* 0x08 */ s32 ramAddr;
    /* 0x0C */ u32 encodedInfo;
    /* 0x10 */ s32 isFree;
} Preload8110EF7C; // size = 0x14

extern s32 D_811806D8;
extern Preload8110EF7C D_81184B78[];
extern s32 D_8118557C;
extern OSMesgQueue D_811855F8;
extern u8* D_811858A4;
void AudioLoad_RelocateFont(s32, s32, RelocInfo8110EF7C*);
void func_8110DB8C(s32, s32, u32, s16);
void AudioLoad_SyncDma(s32, s32, u32, s32);

s32 AudioHeap_AllocPersistentSampleCache(s32, s32, s32, s8);


void func_8110EF7C(s32 font_id, s32 font_data, RelocInfo8110EF7C* reloc_info, s32 async) {
    UNUSED s32 pad[2]; // FAKE: stack padding
    s32 sample_ram_addr;
    Sample8110EF7C* sample;
    s32 size;
    s32 n_chunks;
    s32 preload_in_progress;
    s32 i;

    preload_in_progress = 0;
    if (D_8118557C != 0) {
        preload_in_progress = 1;
    } else {
        D_811806D8 = 0;
    }

    D_81185578 = 0;
    AudioLoad_RelocateFont(font_id, font_data, reloc_info);

    size = 0;
    for (i = 0; i < D_81185578; i++) {
        size += ALIGN16(((Sample8110EF7C*)D_81184978[i])->size);
    }

    for (i = 0; i < D_81185578; i++) {
        if (D_8118557C == 0x78) {
            break;
        }

        sample = (Sample8110EF7C*)D_81184978[i];
        switch (async) {
            case 0:
                if (sample->medium == reloc_info->medium1) {
                    // Assigning size here keeps it live, which the ROM's register allocation needs.
                    sample_ram_addr = AudioHeap_AllocPersistentSampleCache(size = sample->size, reloc_info->sampleBankId1, sample->sampleAddr, sample->medium);
                } else if (sample->medium == reloc_info->medium2) {
                    sample_ram_addr = AudioHeap_AllocPersistentSampleCache(sample->size, reloc_info->sampleBankId2, sample->sampleAddr, sample->medium);
                }
                break;

            case 1:
                if (sample->medium == reloc_info->medium1) {
                    sample_ram_addr = AudioHeap_AllocTemporarySampleCache(sample->size, reloc_info->sampleBankId1, sample->sampleAddr, sample->medium);
                } else if (sample->medium == reloc_info->medium2) {
                    sample_ram_addr = AudioHeap_AllocTemporarySampleCache(sample->size, reloc_info->sampleBankId2, sample->sampleAddr, sample->medium);
                }
                break;
        }

        if (sample_ram_addr == 0) {
            continue;
        }

        switch (async) {
            case 0:
                if (sample->medium == 1) {
                    func_8110DB8C(sample->sampleAddr, sample_ram_addr, sample->size, *(s16*)(D_811858A4 + 2));
                    sample->sampleAddr = sample_ram_addr;
                    sample->medium = 0;
                } else {
                    AudioLoad_SyncDma(sample->sampleAddr, sample_ram_addr, sample->size, sample->medium);
                    sample->sampleAddr = sample_ram_addr;
                    sample->medium = 0;
                }
                break;

            case 1:
                D_81184B78[D_8118557C].sample = sample;
                D_81184B78[D_8118557C].ramAddr = sample_ram_addr;
                D_81184B78[D_8118557C].encodedInfo = (D_8118557C << 24) | 0xFFFFFF;
                D_81184B78[D_8118557C].isFree = 0;
                D_81184B78[D_8118557C].endAndMediumKey = sample->sampleAddr + sample->size + sample->medium;
                D_8118557C++;
                break;
        }
    }
    D_81185578 = 0;

    if ((D_8118557C != 0) && !preload_in_progress) {
        sample = D_81184B78[D_8118557C - 1].sample;
        n_chunks = (sample->size >> 12) + 1;
        func_8110E9A8(sample->sampleAddr, D_81184B78[D_8118557C - 1].ramAddr, sample->size, sample->medium, n_chunks, &D_811855F8, D_81184B78[D_8118557C - 1].encodedInfo);
    }
}

s32 func_8004D1C0(OSMesgQueue*, u32*, s32);
/**
 * Finishes queued sample preloads. When the message for a finished DMA arrives,
 * the sample is pointed at its RAM copy (if it still matches the request), and
 * the next pending request on the stack is started. Returns 0 while a DMA is
 * still in flight or on reset (arg0 != 0), otherwise 1.
 */
s32 BattleAnim_EndSleepStatusAnimation(s32 arg0) {
    Sample8110EF7C* sample;
    u32 preload_index;
    u32 key;
    u32 n_chunks;
    s32 pad; // FAKE: stack padding

    if (D_8118557C > 0) {
        if (arg0 != 0) {
            func_8004D1C0(&D_811855F8, &preload_index, 0);
            D_8118557C = 0;
            return 0;
        }
        if (func_8004D1C0(&D_811855F8, &preload_index, 0) == -1) {
            return 0;
        }

        preload_index >>= 24;
        if (D_81184B78[preload_index].isFree == 0) {
            sample = D_81184B78[preload_index].sample;
            key = sample->sampleAddr + sample->size + sample->medium;
            if (key == D_81184B78[preload_index].endAndMediumKey) {
                sample->sampleAddr = D_81184B78[preload_index].ramAddr;
                sample->medium = 0;
            }
            D_81184B78[preload_index].isFree = 1;
        }

        for (;;) {
            if (D_8118557C <= 0) {
                break;
            }
            if (D_81184B78[D_8118557C - 1].isFree == 1) {
                D_8118557C--;
                continue;
            }

            sample = D_81184B78[D_8118557C - 1].sample;
            n_chunks = (sample->size >> 12) + 1;
            key = sample->sampleAddr + sample->size + sample->medium;
            if (key != D_81184B78[D_8118557C - 1].endAndMediumKey) {
                D_81184B78[D_8118557C - 1].isFree = 1;
                D_8118557C--;
            } else {
                func_8110E9A8(sample->sampleAddr, D_81184B78[D_8118557C - 1].ramAddr, sample->size, sample->medium, n_chunks, &D_811855F8, D_81184B78[D_8118557C - 1].encodedInfo);
                break;
            }
        }
    }
    return 1;
}

typedef struct Item8110F4D0 {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 key;
} Item8110F4D0;

/**
 * Appends `arg0` to the list `list` unless an entry with the same `key` (offset 0x4)
 * is already present among the first `count` entries.
 *
 * @param arg0  Item to add.
 * @param count Number of entries currently in `list`.
 * @param list  Array of item pointers; must have room for `count + 1` entries.
 * @return The new entry count (count + 1 if added, otherwise unchanged).
 */
s32 func_8110F4D0(Item8110F4D0* arg0, s32 count, Item8110F4D0** list) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (arg0->key == list[i]->key) {
            break;
        }
    }
    if (i == count) {
        list[count] = arg0;
        count++;
    }
    return count;
}


s32 func_8110F518(s32 arg0, Item8110F4D0** arg1) {
    s32 count = 0;
    s32 i;
    s32 n1 = D_811858B0[arg0].numDrums;
    s32 n0 = D_811858B0[arg0].numInstruments;
    s32* p;
    u8* q;

    for (i = 0; i < n1; i++) {
        p = AudioPlayback_GetDrum(arg0, i);
        if (p != 0) {
            // FAKE: do-while(0) wrapper only changes register allocation; needed to match
            do {  // FAKE
                count = func_8110F4D0((Item8110F4D0*)p[1], count, arg1);
            } while (0);
        }
    }
    for (i = 0; i < n0; i++) {
        q = (u8*)AudioPlayback_GetInstrumentInner(arg0, i);
        if (q != 0) {
            if (q[1] != 0) {
                count = func_8110F4D0(*(Item8110F4D0**)(q + 8), count, arg1);
            }
            if (q[2] != 0x7F) {
                count = func_8110F4D0(*(Item8110F4D0**)(q + 0x18), count, arg1);
            }
            count = func_8110F4D0(*(Item8110F4D0**)(q + 0x10), count, arg1);
        }
    }
    return count;
}


/*
 * func_8110F64C
 *
 * Takes a pointer to a pointer to a record whose first word is read as the
 * bit ranges above. When the low 24 bits, bit 25 and bits 27..26 are all
 * non-zero, the record pointer is appended to the pointer array D_81184978
 * and the count D_81185578 is incremented. There is no bounds check on the
 * count. This is Zero's version of OoT's AudioLoad_AddUsedSample: the caller
 * AudioLoad_PreloadSamplesForFont collects a font's used samples here and then preloads them.
 * Matching note: the bit-field reads are what produce the ROM's shift
 * sequence; the equivalent masks and shifts on a plain word differ in
 * temporary register numbering.
 */
void func_8110F64C(SampleFlags8110F64C **arg0) {
    SampleFlags8110F64C *rec;

    rec = *arg0;
    if (rec->size && rec->unk_bit26 && rec->medium) {
        D_81184978[D_81185578] = rec;
        D_81185578 += 1;
    }
}

/**
 * Zero's version of OoT's AudioLoad_PreloadSamplesForFont: gathers the samples
 * used by a font's instruments and drums, then copies them into the sample
 * cache (async == 0) or queues them on the preload stack (async == 1).
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioLoad_PreloadSamplesForFont(s32 font_id, s32 async, RelocInfo8110EF7C* reloc_info) {
    s32 num_drums;
    s32 num_instruments;
    s32 pad[2]; // FAKE
    u8* instrument;
    u8* drum;
    s32 sample_ram_addr;
    Sample8110EF7C* sample;
    s32 size;
    s32 n_chunks;
    s32 preload_in_progress;
    s32 i;

    preload_in_progress = 0;
    if (D_8118557C != 0) {
        preload_in_progress = 1;
    }
    D_81185578 = 0;
    num_instruments = D_811858B0[font_id].numInstruments;
    num_drums = D_811858B0[font_id].numDrums;

    for (i = 0; i < num_instruments; i++) {
        instrument = (u8*)AudioPlayback_GetInstrumentInner(font_id, i);
        if (instrument != NULL) {
            if (instrument[1] != 0) {
                func_8110F64C((SampleFlags8110F64C**)(instrument + 8));
                if (!reloc_info->medium2) {} // FAKE
            }
            if (instrument[2] != 0x7F) {
                func_8110F64C((SampleFlags8110F64C**)(instrument + 0x18));
            }
            func_8110F64C((SampleFlags8110F64C**)(instrument + 0x10));
        }
    }

    for (i = 0; i < num_drums; i++) {
        drum = (u8*)AudioPlayback_GetDrum(font_id, i);
        if (drum != NULL) {
            func_8110F64C((SampleFlags8110F64C**)(drum + 4));
        }
    }

    if (D_81185578 == 0) {
        return;
    }

    size = 0;
    for (i = 0; i < D_81185578; i++) {
        size += ALIGN16(((Sample8110EF7C*)D_81184978[i])->size);
    }
    if (size) {} // karodo

    for (i = 0; i < D_81185578; i++) {
        if (D_8118557C == 0x78) {
            break;
        }

        sample = (Sample8110EF7C*)D_81184978[i];
        switch (async) {
            case 0:
                if (sample->medium == reloc_info->medium1) {
                    sample_ram_addr = AudioHeap_AllocPersistentSampleCache(sample->size, reloc_info->sampleBankId1, sample->sampleAddr, sample->medium);
                } else if (sample->medium == reloc_info->medium2) {
                    sample_ram_addr = AudioHeap_AllocPersistentSampleCache(sample->size, reloc_info->sampleBankId2, sample->sampleAddr, sample->medium);
                }
                break;

            case 1:
                if (sample->medium == reloc_info->medium1) {
                    sample_ram_addr = AudioHeap_AllocTemporarySampleCache(sample->size, reloc_info->sampleBankId1, sample->sampleAddr, sample->medium);
                } else if (sample->medium == reloc_info->medium2) {
                    sample_ram_addr = AudioHeap_AllocTemporarySampleCache(sample->size, reloc_info->sampleBankId2, sample->sampleAddr, sample->medium);
                }
                break;
        }

        if (sample_ram_addr == 0) {
            continue;
        }

        switch (async) {
            case 0:
                if (sample->medium == 1) {
                    func_8110DB8C(sample->sampleAddr, sample_ram_addr, sample->size, *(s16*)(D_811858A4 + 2));
                    sample->sampleAddr = sample_ram_addr;
                    sample->medium = 0;
                } else {
                    AudioLoad_SyncDma(sample->sampleAddr, sample_ram_addr, sample->size, sample->medium);
                    sample->sampleAddr = sample_ram_addr;
                    sample->medium = 0;
                }
                break;

            case 1:
                D_81184B78[D_8118557C].sample = sample;
                D_81184B78[D_8118557C].ramAddr = sample_ram_addr;
                D_81184B78[D_8118557C].encodedInfo = (D_8118557C << 24) | 0xFFFFFF;
                D_81184B78[D_8118557C].isFree = 0;
                D_81184B78[D_8118557C].endAndMediumKey = sample->sampleAddr + sample->size + sample->medium;
                D_8118557C++;
                break;
        }
    }
    D_81185578 = 0;

    if ((D_8118557C != 0) && !preload_in_progress) {
        sample = D_81184B78[D_8118557C - 1].sample;
        n_chunks = (sample->size >> 12) + 1;
        func_8110E9A8(sample->sampleAddr, D_81184B78[D_8118557C - 1].ramAddr, sample->size, sample->medium, n_chunks, &D_811855F8, D_81184B78[D_8118557C - 1].encodedInfo);
    }
}

extern s32 D_8118444C;
typedef struct Entry8110D840 {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char unk09[7];
} Entry8110D840; // size = 0x10
typedef struct Table8110D840 {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ Entry8110D840 entries[1];
} Table8110D840;
Table8110D840* AudioLoad_GetLoadTable(s32);
s32 AudioLoad_GetRealTableIndex(s32, s32);
void AudioLoad_PreloadSamplesForFont(s32, s32, RelocInfo8110EF7C*);
void func_8110FAF4(void) {
    Table8110D840* base = AudioLoad_GetLoadTable(2);
    s32 i;
    s32 idx;
    s32 buf[8];
    s32 id;

    for (i = 0; i < D_8118444C; i++) {
        if (D_81184440.entries[i].tableType == 1) {
            id = AudioLoad_GetRealTableIndex(1, D_81184440.entries[i].id);
            buf[0] = D_811858B0[id].sampleBankId1;
            buf[0] = AudioLoad_GetRealTableIndex(2, buf[0]);
            buf[1] = D_811858B0[id].sampleBankId2;
            buf[1] = AudioLoad_GetRealTableIndex(2, buf[1]);
            buf[4] = base->entries[buf[0]].unk_08;
            idx = buf[1];
            buf[5] = base->entries[idx].unk_08;
            AudioLoad_PreloadSamplesForFont(id, 0, buf);
        }
    }
}
