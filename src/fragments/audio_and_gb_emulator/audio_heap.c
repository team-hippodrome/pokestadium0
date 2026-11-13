/* Stadium Zero fragment000_80C00. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_emulator/gb_tower_emulator_86920.c. */

#include "global.h"
#include "audio_and_gb_emulator.h"

extern unk_D_81234690 D_811858B8;
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

/**
 * Marks the fonts that are not permanently loaded (status 5) as unloaded. Zelda 64 audio driver (heap.c), same position and shape.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_ResetLoadStatus(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (D_81184655[i] != 5) {
            D_81184655[i] = 0;
        }
    }
    for (i = 0; i < 1; i++) {
        if (D_81184654[i] != 5) {
            D_81184654[i] = 0;
        }
    }
    for (i = 0; i < 1; i++) {
        if (D_81184656[i] != 5) {
            D_81184656[i] = 0;
        }
    }
}

/* One 0xCC-byte record; only the fields AudioHeap_DiscardFont touches are named. */

s32 AudioPlayback_NoteDisable(Rec81109678*);
s32 AudioPlayback_AudioListRemove(Rec81109678*);
s32 AudioSeq_AudioListPushBack(s8*, Rec81109678*);
extern Rec81109678* D_81184664;
extern s8 D_81184938;
extern s32 D_811858E8;

/**
 * AudioHeap_DiscardFont
 *
 * Walks the D_811858E8 records of the array at D_81184664 (0xCC bytes each,
 * the array pointer is re-read on every iteration). For each record whose
 * byte at 0x33 equals arg0: if the bytes at 0x34 and 0x30 are 0 and non-zero
 * respectively, it clears bit 7 and then sets bit 6 of the byte that the
 * pointer at 0x44 points to. In every matching record it then calls
 * AudioPlayback_NoteDisable(rec), AudioPlayback_AudioListRemove(rec) and AudioSeq_AudioListPushBack(&D_81184938, rec).
 * Records whose byte at 0x33 differs are skipped. What the record and the
 * flag bits mean is not established from this function.
 *
 * Matching notes: the two single-bit writes are declared as bit-fields; the
 * bit-field form gives the retail `andi 0xFF7F` / `ori 0x40` read-modify-write
 * sequences and register numbering (a plain `&= 0xFF7F; |= 0x40` on a byte
 * was one temporary register off). Indexing the array with the loop counter,
 * instead of a separate byte offset, gives the retail loop setup order.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioHeap_DiscardFont(s32 arg0) {
    s32 i;
    Rec81109678* p;

    for (i = 0; i < D_811858E8; i++) {
        p = &D_81184664[i];
        if (arg0 == p->fontId) {
            if ((p->unk_34 == 0) && (p->priority != 0)) {
                p->parentLayer->enabled = 0;
                p->parentLayer->finished = 1;
            }
            AudioPlayback_NoteDisable(p);
            AudioPlayback_AudioListRemove(p);
            AudioSeq_AudioListPushBack(&D_81184938, p);
        }
    }
}

M2C_UNK AudioSeq_SequencePlayerDisable(M2C_UNK *);                   /* extern */
extern s8 D_81184668;
extern s16 D_811858CC;
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
/**
 * Stops every sequence player that plays sequence `arg0`. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_DiscardSequence(s32 arg0)
{
  s32 new_var2; // FAKE: permuter temp
  s8 *new_var; // FAKE: permuter temp
  s32 var_s1;
  var_s1 = 0;
  if (D_811858CC > 0)
  {
    new_var = &D_81184668;
    new_var = new_var; // FAKE: self-assignment
    new_var2 = arg0;
    do
    {
      if (((((u32) (*((u32 *) (((s8 *) new_var) + 0)))) >> 0x1F) != 0) && (new_var2 == (*((u8 *) (((s8 *) new_var) + 4))))) // FAKE: decomp slop, raw pointer casts stand in for struct fields
      {
        AudioSeq_SequencePlayerDisable(new_var);
      }
      var_s1 += 1;
      new_var += 0x15C;
    }
    while (var_s1 < D_811858CC);
  }
}

/**
 * Like alHeapDBAlloc: carves a 16-byte aligned block and zeroes it. Returns 0 when the arena is full.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
u32 GbApu_AllocZeroed(AudioAllocPool* arg0, s32 arg1) {
  s32 temp_v0;
  u32 temp_a2;
  u32 var_a1;
  temp_v0 = ALIGN16(arg1);
  temp_a2 = arg0->curRamAddr;
  if ((u32)(arg0->startRamAddr + arg0->size) >= (temp_a2 + temp_v0)) {
      arg0->curRamAddr += temp_v0;
      var_a1 = temp_a2;
      while (var_a1 < (u32)arg0->curRamAddr) {
          *((u8*)var_a1++) = 0;
      }
  } else {
      return 0;
  }
  arg0->numEntries++;
  return temp_a2;
}

/**
 * GbApu_AllocZeroed without the clear.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 GbApu_Alloc(AudioAllocPool* arg0, s32 arg1) {
  s32 temp_a2;
  u32 temp_v0;

  temp_v0 = ALIGN16(arg1);
  temp_a2 = arg0->curRamAddr;
  if ((arg0->startRamAddr + arg0->size) >= (arg0->curRamAddr + temp_v0)) {
      arg0->curRamAddr = temp_v0 + temp_a2;
  } else {
      return 0;
  }
  arg0->numEntries++;
  return temp_a2;
}

/**
 * Like alHeapInit.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void GbApu_InitAllocator(AudioAllocPool* arg0, s32 arg1, s32 arg2) {
  arg0->startRamAddr = ALIGN16(arg1);
  arg0->curRamAddr = ALIGN16(arg1);
  arg0->size = (s32) (arg2 - (arg1 & 0xF));
  arg0->numEntries = 0;
}

/**
 * Empties a persistent cache and rewinds its pool. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_PersistentCacheClear(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 4);
}

/**
 * AudioHeap_TemporaryCacheClear
 *
 * Resets a small record: the words at +0x00 and +0x10 are cleared, the words
 * at +0x08 and +0x14 are set to the value at +0x04, the word at +0x20 is set
 * to (+0x0C) + (+0x04), and the halfwords at +0x1E and +0x2A are set to -1.
 * It reads like the set-up of a cursor over a buffer (start at +0x04, length
 * at +0x0C, end stored at +0x20), but the role of the record is not
 * established from the code alone, so the fields are left unnamed.
 *
 * The sum is written with the fields in this order, and read from memory
 * rather than through a local, because IDO orders the two operands of the
 * addu differently otherwise.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name guessed from the code; comment kept.
 */
void AudioHeap_TemporaryCacheClear(s32* arg0) {
    arg0[4] = 0;
    arg0[0] = 0;
    arg0[8] = arg0[3] + arg0[1];
    ((s16*)arg0)[0xF] = -1;
    ((s16*)arg0)[0x15] = -1;
    arg0[2] = arg0[1];
    arg0[5] = arg0[1];
}

/**
 * Rewinds an allocation pool to its start. Zelda 64 audio driver.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_ResetPool(s8 *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0);
}

M2C_UNK func_811098C0(M2C_UNK *, s32, s32);
extern M2C_UNK D_81184290;
extern M2C_UNK D_811842B0;
extern u8 D_81186270[];
extern s32 D_811526FC;
extern s32 D_811842A0;

/**
 * Runs func_811098C0 twice: first on D_811842B0 with the buffer D_81186270 and
 * length arg0, then on D_81184290 with the remainder of the buffer (starting
 * at arg0 and D_811526FC - arg0 long). Finally clears D_811842A0. What
 * func_811098C0 does with its arguments is not established.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name guessed from the code; comment kept.
 */
void AudioHeap_InitMainPools(s32 arg0) {
    func_811098C0(&D_811842B0, (s32)D_81186270, arg0);
    func_811098C0(&D_81184290, (s32)(D_81186270 + arg0), D_811526FC - arg0);
    D_811842A0 = 0;
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184290;
extern M2C_UNK D_811842C0;
extern M2C_UNK D_811842F0;

/**
 * Splits the session pool into the misc and cache pools. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_InitSessionPools(s8 *arg0) {
    M2C_FIELD(&D_81184290, s32 *, 4) = (s32) M2C_FIELD(&D_81184290, s32 *, 0);
    func_811098C0(&D_811842C0, func_81109868(&D_81184290, M2C_FIELD(arg0, s32 *, 0)), M2C_FIELD(arg0, s32 *, 0));
    func_811098C0(&D_811842F0, func_81109868(&D_81184290, M2C_FIELD(arg0, s32 *, 0xC)), M2C_FIELD(arg0, s32 *, 0xC));
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_811842F0;
extern M2C_UNK D_81184300;
extern M2C_UNK D_81184310;

/**
 * Splits the cache pool into the persistent and temporary pools. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_InitCachePools(s8 *arg0) {
    M2C_FIELD(&D_811842F0, s32 *, 4) = (s32) M2C_FIELD(&D_811842F0, s32 *, 0);
    func_811098C0(&D_81184300, func_81109868(&D_811842F0, M2C_FIELD(arg0, s32 *, 0)), M2C_FIELD(arg0, s32 *, 0));
    func_811098C0(&D_81184310, func_81109868(&D_811842F0, M2C_FIELD(arg0, s32 *, 4)), M2C_FIELD(arg0, s32 *, 4));
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184300;
extern M2C_UNK D_81184320;
extern M2C_UNK D_81184324;
extern M2C_UNK D_81184380;
extern M2C_UNK D_81184384;
extern M2C_UNK D_811843E0;
extern M2C_UNK D_811843E4;

/**
 * Splits the persistent pool between the sequence, font and sample caches. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_InitPersistentCache(s8 *arg0) {
    M2C_FIELD(&D_81184300, s32 *, 4) = (s32) M2C_FIELD(&D_81184300, s32 *, 0);
    func_811098C0(&D_81184324, func_81109868(&D_81184300, M2C_FIELD(arg0, s32 *, 0)), M2C_FIELD(arg0, s32 *, 0));
    func_811098C0(&D_81184384, func_81109868(&D_81184300, M2C_FIELD(arg0, s32 *, 4)), M2C_FIELD(arg0, s32 *, 4));
    func_811098C0(&D_811843E4, func_81109868(&D_81184300, M2C_FIELD(arg0, s32 *, 8)), M2C_FIELD(arg0, s32 *, 8));
    AudioHeap_PersistentCacheClear(&D_81184320);
    AudioHeap_PersistentCacheClear(&D_81184380);
    AudioHeap_PersistentCacheClear(&D_811843E0);
}

s32 func_81109868(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_811098C0(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_81184310;
extern M2C_UNK D_81184340;
extern M2C_UNK D_81184344;
extern M2C_UNK D_811843A0;
extern M2C_UNK D_811843A4;
extern M2C_UNK D_81184400;
extern M2C_UNK D_81184404;

/**
 * Splits the temporary pool between the sequence, font and sample caches. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_InitTemporaryCache(s8 *arg0) {
    M2C_FIELD(&D_81184310, s32 *, 4) = (s32) M2C_FIELD(&D_81184310, s32 *, 0);
    func_811098C0(&D_81184344, func_81109868(&D_81184310, M2C_FIELD(arg0, s32 *, 0)), M2C_FIELD(arg0, s32 *, 0));
    func_811098C0(&D_811843A4, func_81109868(&D_81184310, M2C_FIELD(arg0, s32 *, 4)), M2C_FIELD(arg0, s32 *, 4));
    func_811098C0(&D_81184404, func_81109868(&D_81184310, M2C_FIELD(arg0, s32 *, 8)), M2C_FIELD(arg0, s32 *, 8));
    AudioHeap_TemporaryCacheClear(&D_81184340);
    AudioHeap_TemporaryCacheClear(&D_811843A0);
    AudioHeap_TemporaryCacheClear(&D_81184400);
}

typedef struct PersistentCache81109C0C {
    /* 0x00 */ u32 numEntries;
    /* 0x04 */ AudioAllocPool pool;
    /* 0x14 */ CacheEntry81109C0C entries[1];
} PersistentCache81109C0C; // size = 0x20

typedef struct TemporaryCache81109C0C {
    /* 0x00 */ u32 nextSide;
    /* 0x04 */ AudioAllocPool pool;
    /* 0x14 */ CacheEntry81109C0C entries[2];
} TemporaryCache81109C0C; // size = 0x2C

typedef struct Cache81109C0C {
    /* 0x00 */ PersistentCache81109C0C persistent;
    /* 0x20 */ TemporaryCache81109C0C temporary;
} Cache81109C0C;

extern u8 D_81184654[1];
extern u8 D_81184655[1];
extern u8 D_81184656[1];
void AudioLoad_SetFontLoadStatus(s32, s32);

/**
 * Allocates `size` bytes for entry `id` of a table's persistent or temporary cache, evicting the older temporary entry when needed. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void* AudioHeap_AllocCached(s32 table_type, s32 size, s32 cache, s32 id) {
    Cache81109C0C* loaded_cache;
    TemporaryCache81109C0C* t_cache;
    AudioAllocPool* temp_pool;
    void* persistent_addr;
    void* temp_addr;
    u8 load_status_entry0;
    u8 load_status_entry1;
    s32 i;
    u8* load_status;

    switch (table_type) {
        case 0:
            loaded_cache = (Cache81109C0C*)&D_81184320;
            load_status = D_81184656;
            break;
        case 1:
            loaded_cache = (Cache81109C0C*)&D_81184380;
            load_status = D_81184655;
            break;
        case 2:
            loaded_cache = (Cache81109C0C*)&D_811843E0;
            load_status = D_81184654;
            break;
    }

    if (cache == 0) {
        t_cache = &loaded_cache->temporary;
        temp_pool = &t_cache->pool;

        if (t_cache->entries[0].id == -1) {
            load_status_entry0 = 0;
        } else {
            load_status_entry0 = load_status[t_cache->entries[0].id];
        }

        if (t_cache->entries[1].id == -1) {
            load_status_entry1 = 0;
        } else {
            load_status_entry1 = load_status[t_cache->entries[1].id];
        }

        if (table_type == 1) {
            if (load_status_entry0 == 4) {
                for (i = 0; i < D_811858E8; i++) {
                    if (D_81184664[i].fontId == t_cache->entries[0].id && D_81184664[i].enabled) {
                        break;
                    }
                }

                if (i == D_811858E8) {
                    AudioLoad_SetFontLoadStatus(t_cache->entries[0].id, 3);
                    load_status_entry0 = 3;
                }
            }

            if (load_status_entry1 == 4) {
                for (i = 0; i < D_811858E8; i++) {
                    if (D_81184664[i].fontId == t_cache->entries[1].id && D_81184664[i].enabled) {
                        break;
                    }
                }

                if (i == D_811858E8) {
                    AudioLoad_SetFontLoadStatus(t_cache->entries[1].id, 3);
                    load_status_entry1 = 3;
                }
            }
        }

        if (load_status_entry0 == 0) {
            t_cache->nextSide = 0;
        } else if (load_status_entry1 == 0) {
            t_cache->nextSide = 1;
        } else if (load_status_entry0 == 3 && load_status_entry1 == 3) {
            // Use the opposite side from last time.
        } else if (load_status_entry0 == 3) {
            t_cache->nextSide = 0;
        } else if (load_status_entry1 == 3) {
            t_cache->nextSide = 1;
        } else {
            if (table_type == 0) {
                if (load_status_entry0 == 2) {
                    for (i = 0; i < D_811858CC; i++) {
                        if (((SeqPlayer81109C0C*)&D_81184668)[i].enabled && ((SeqPlayer81109C0C*)&D_81184668)[i].seqId == t_cache->entries[0].id) {
                            break;
                        }
                    }
                    if (i == D_811858CC) {
                        t_cache->nextSide = 0;
                        goto done;
                    }
                }
                if (load_status_entry1 == 2) {
                    for (i = 0; i < D_811858CC; i++) {
                        if (((SeqPlayer81109C0C*)&D_81184668)[i].enabled && ((SeqPlayer81109C0C*)&D_81184668)[i].seqId == t_cache->entries[1].id) {
                            break;
                        }
                    }
                    if (i == D_811858CC) {
                        t_cache->nextSide = 1;
                        goto done;
                    }
                }
            } else if (table_type == 1) {
                if (load_status_entry0 == 2) {
                    for (i = 0; i < D_811858E8; i++) {
                        if (D_81184664[i].fontId == t_cache->entries[0].id && D_81184664[i].enabled) {
                            break;
                        }
                    }
                    if (i == D_811858E8) {
                        t_cache->nextSide = 0;
                        goto done;
                    }
                }
                if (load_status_entry1 == 2) {
                    for (i = 0; i < D_811858E8; i++) {
                        if (D_81184664[i].fontId == t_cache->entries[1].id && D_81184664[i].enabled) {
                            break;
                        }
                    }
                    if (i == D_811858E8) {
                        t_cache->nextSide = 1;
                        goto done;
                    }
                }
            }

            if (t_cache->nextSide == 0) {
                if (load_status_entry0 == 1) {
                    if (load_status_entry1 == 1) {
                        goto fail;
                    }
                    t_cache->nextSide = 1;
                }
            } else {
                if (load_status_entry1 == 1) {
                    if (load_status_entry0 == 1) {
                        goto fail;
                    }
                    t_cache->nextSide = 0;
                }
            }

            if (0) {
            fail:
                return NULL;
            }
        }

    done:
        if (t_cache->entries[t_cache->nextSide].id != -1) {
            load_status[t_cache->entries[t_cache->nextSide].id] = 0;
            if (table_type == 1) {
                AudioHeap_DiscardFont(t_cache->entries[t_cache->nextSide].id);
            }
        }

        switch (t_cache->nextSide) {
            case 0:
                t_cache->entries[0].ramAddr = temp_pool->startRamAddr;
                t_cache->entries[0].id = id;
                t_cache->entries[0].size = size;
                temp_pool->curRamAddr = temp_pool->startRamAddr + size;

                if (t_cache->entries[1].id != -1 && t_cache->entries[1].ramAddr < temp_pool->curRamAddr) {
                    load_status[t_cache->entries[1].id] = 0;
                    switch (table_type) {
                        case 0:
                            AudioHeap_DiscardSequence(t_cache->entries[1].id);
                            break;
                        case 1:
                            AudioHeap_DiscardFont(t_cache->entries[1].id);
                            break;
                    }
                    t_cache->entries[1].id = -1;
                    t_cache->entries[1].ramAddr = temp_pool->startRamAddr + temp_pool->size;
                }
                temp_addr = t_cache->entries[0].ramAddr;
                break;

            case 1:
                t_cache->entries[1].ramAddr = (u8*)((u32)(temp_pool->startRamAddr + temp_pool->size - size) & ~0xF);
                t_cache->entries[1].id = id;
                t_cache->entries[1].size = size;
                if (t_cache->entries[0].id != -1 && t_cache->entries[1].ramAddr < temp_pool->curRamAddr) {
                    load_status[t_cache->entries[0].id] = 0;
                    switch (table_type) {
                        case 0:
                            AudioHeap_DiscardSequence(t_cache->entries[0].id);
                            break;
                        case 1:
                            AudioHeap_DiscardFont(t_cache->entries[0].id);
                            break;
                    }
                    t_cache->entries[0].id = -1;
                    temp_pool->curRamAddr = temp_pool->startRamAddr;
                }
                temp_addr = t_cache->entries[1].ramAddr;
                break;

            default:
                return NULL;
        }

        t_cache->nextSide ^= 1;
        return temp_addr;
    }

    persistent_addr = (void*)func_81109868((M2C_UNK*)&loaded_cache->persistent.pool, size);
    loaded_cache->persistent.entries[loaded_cache->persistent.numEntries].ramAddr = persistent_addr;

    if (persistent_addr == NULL) {
        switch (cache) {
            case 2:
                return AudioHeap_AllocCached(table_type, size, 0, id);
            case 0:
            case 1:
                return NULL;
        }
    }

    loaded_cache->persistent.entries[loaded_cache->persistent.numEntries].id = id;
    loaded_cache->persistent.entries[loaded_cache->persistent.numEntries].size = size;
    return loaded_cache->persistent.entries[loaded_cache->persistent.numEntries++].ramAddr;
}

/*
 * AudioHeap_SearchCaches
 *
 * Calls AudioHeap_SearchPermanentCache(arg0, arg2) and returns its result if that is
 * non-zero.  Otherwise returns 0 if arg1 is 3, and
 * AudioHeap_SearchRegularCaches(arg0, arg1, arg2) for any other arg1.
 */
s32 AudioHeap_SearchRegularCaches(s32 arg0, s32 arg1, s32 arg2);
s32 AudioHeap_SearchPermanentCache(s32 arg0, s32 arg1);

/**
 * Looks up entry `arg2` of table `arg0`, in the permanent cache first, then the regular caches. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioHeap_SearchCaches(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = AudioHeap_SearchPermanentCache(arg0, arg2);

    if (result != 0) {
        return result;
    }
    if (arg1 == 3) {
        return 0;
    }
    return AudioHeap_SearchRegularCaches(arg0, arg1, arg2);
}

/**
 * Looks up entry `arg2` of table `arg0` in its temporary or persistent cache. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
s32 AudioHeap_SearchRegularCaches(s32 arg0, s32 arg1, s32 arg2) {
    Tbl8110A368* sub;
    Tbl8110A368* tbl;
    u32 i;
    switch (arg0) {
    case 0:
        tbl = (Tbl8110A368*)&D_81184320;
        break;
    case 1:
        tbl = (Tbl8110A368*)&D_81184380;
        break;
    case 2:
        tbl = (Tbl8110A368*)&D_811843E0;
        break;
    }
    sub = (Tbl8110A368*)((u8*)tbl + 0x20);
    if (arg1 == 0) {
        if (arg2 == sub->entries[0].key) {
            sub->count = 1;
            return sub->entries[0].val;
        }
        if (arg2 == sub->entries[1].key) {
            sub->count = 0;
            return sub->entries[1].val;
        }
        return 0;
    }
    sub = tbl;
    for (i = 0; i < sub->count; i++) {
        if (arg2 == tbl->entries[i].key) {
            return tbl->entries[i].val;
        }
    }
    if (arg1 == 2) {
        return AudioHeap_SearchCaches(arg0, 0, arg2);
    }
    return 0;
}

/**
 * Unused in the code seen so far. Fills out[0..15] from two recurrences in p
 * and q seeded with 262159.0f; as in the Ocarina of Time version
 * (func_800DDF80) the first loop writes to out instead of tmp, so the second
 * loop copies partly uninitialised values.
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioHeap_ComputeFilterCoefficients(f32 p, f32 q, u16* out) {
    s32 i;
    f32 tmp[16];

    tmp[0] = (f32)(q * 262159.0f);
    tmp[8] = (f32)(p * 262159.0f);
    tmp[1] = (f32)((q * p) * 262159.0f);
    tmp[9] = (f32)(((p * p) + q) * 262159.0f);

    for (i = 2; i < 8; i++) {
        out[i] = q * tmp[i - 2] + p * tmp[i - 1];
        out[8 + i] = q * tmp[6 + i] + p * tmp[7 + i];
    }

    for (i = 0; i < 16; i++) {
        out[i] = tmp[i];
    }
}

/**
 * AudioHeap_ClearFilter
 *
 * Sets the eight s16 values at arg0 to zero (the loop is unrolled by four in
 * the retail code).
 * No caller (2026-11-13): nothing in the built ROM jumps to it or holds its address (no jal or j,
 * no pointer word, no lui/addiu pair in any fragment), so play cannot reach it.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioHeap_ClearFilter(s16* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        arg0[i] = 0;
    }
}

extern s16 D_811371D8[];

/**
 * AudioHeap_LoadLowPassFilter
 *
 * Copies eight s16 values into arg0 from entry arg1 of the table at
 * D_811371D8 (entries are 8 s16 = 16 bytes long; the loop is unrolled by four
 * in the retail code).
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioHeap_LoadLowPassFilter(s16* arg0, s32 arg1) {
    s16* src;
    s32 i;

    src = &D_811371D8[arg1 * 8];
    for (i = 0; i < 8; i++) {
        arg0[i] = src[i];
    }
}

extern s16 D_811373C8[];

/**
 * AudioHeap_LoadHighPassFilter
 *
 * Copies eight s16 values into arg0 from the table at D_811373C8. The entry is
 * numbered from 1: entry arg1 starts at D_811373C8 + (arg1 - 1) * 16 bytes
 * (8 s16 per entry; the loop is unrolled by four in the retail code).
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name guessed from the code; comment kept.
 */
void AudioHeap_LoadHighPassFilter(s16* arg0, s32 arg1) {
    s16* src;
    s32 i;

    src = &D_811373C8[arg1 * 8 - 8];
    for (i = 0; i < 8; i++) {
        arg0[i] = src[i];
    }
}

/**
 * Loads a low-pass, high-pass or band-pass filter from the two cutoffs. Zelda 64 audio driver.
 * No caller in play (2026-11-13): nothing that runs reaches it, not even through callbacks, data
 * tables or fragment headers.
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_LoadFilter(s16* arg0, s32 arg1, s32 arg2) {
    s32 i;

    if ((arg1 == 0) && (arg2 == 0)) {
        AudioHeap_LoadLowPassFilter(arg0, 0);
    } else if (arg2 == 0) {
        AudioHeap_LoadLowPassFilter(arg0, arg1);
    } else if (arg1 == 0) {
        AudioHeap_LoadHighPassFilter(arg0, arg2);
    } else {
        for (i = 0; i < 8; i++) {
            arg0[i] = (D_811371D8[arg2 * 8 + i] + D_811373C8[arg2 * 8 + i]) / 2;
        }
    }
}

extern Voice8110AA50 D_81184110[];
extern s8 D_8118427B;
/**
 * Steps every reverb's settings once per audio frame. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_UpdateReverbs(void) {
    s32 n;
    s32 i;
    s32 j;

    if (*(s16*)&D_811858B8 == 2) {
        n = 2;
    } else {
        n = 1;
    }
    for (i = 0; i < D_8118427B; i++) {
        for (j = 0; j < n; j++) {
            D_81184110[i].unk_0C -= D_81184110[i].unk_0C / 3;
        }
    }
}

extern s16 D_811858C2;

/**
 * Clears the audio buffer that is being filled. Zelda 64 audio driver.
 * Not reached in play (2026-11-13): did not run in a GB player session (boot, Continue, menus) or
 * in a tour of the menus and a COM battle.
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_ClearCurrentAiBuffer(void) {
    s32 idx = D_811858FC;
    s32 i;

    D_811859C4[idx] = D_811858C2;
    for (i = 0; i < 2016; i++) {
        D_811859B8[idx][i] = 0;
    }
}

extern volatile u8 D_81184657;
extern s32 D_8118465C;
void AudioHeap_Init(void);
void AudioHeap_DiscardSampleCaches(void);

/**
 * Runs one step of the audio reset: fade out, stop notes, clear buffers, reinitialize. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
s32 AudioHeap_ResetStep(void) {
    s32 i;
    s32 j;
    s32 sp24;

    if (D_811858B8.specUnk4 == 2) {
        sp24 = 2;
    } else {
        sp24 = 1;
    }

    switch (D_81184657) {
        case 5:
            for (i = 0; i < D_811858B8.numSequencePlayers; i++) {
                AudioSeq_SequencePlayerDisable(&D_81184668 + i * 0x15C);
            }
            D_8118465C = 4 / sp24;
            D_81184657--;
            break;
        case 4:
            if (D_8118465C != 0) {
                D_8118465C--;
                AudioHeap_UpdateReverbs();
            } else {
                for (i = 0; i < D_811858E8; i++) {
                    if (D_81184664[i].enabled && D_81184664[i].adsrState != 0) {
                        D_81184664[i].adsrFadeOutVel = D_811858B8.ticksPerUpdateInv;
                        D_81184664[i].adsrAction |= 0x10;
                    }
                }
                D_8118465C = 16 / sp24;
                D_81184657--;
            }
            break;
        case 3:
            if (D_8118465C != 0) {
                D_8118465C--;
                AudioHeap_UpdateReverbs();
            } else {
                D_8118465C = 4 / sp24;
                D_81184657--;
            }
            break;
        case 2:
            AudioHeap_ClearCurrentAiBuffer();
            if (!D_8118465C && !D_8118465C && !D_8118465C) {} // FAKE: empty test found by a fake search; only changes register use
            if (D_8118465C != 0) {
                D_8118465C--;
            } else {
                D_81184657--;
                AudioHeap_DiscardSampleCaches();
            }
            if (!D_811858B8.specUnk4) {} // FAKE: empty test found by the permuter; keeps &D_811858B8 in a saved register
            break;
        case 1:
            AudioHeap_Init();
            D_81184657 = 0;
            for (i = 0; i < 3; i++) {
                D_811859C4[i] = D_811858B8.maxAiBufferLength;
                for (j = 0; j < 2016; j++) {
                    D_811859B8[i][j] = 0;
                }
            }
            break;
    }

    if (D_81184657 < 3) {
        return 0;
    }
    return 1;
}

typedef struct SplitAFF0 {
    /* 0x00 */ s32 a;
    /* 0x04 */ s32 b;
    /* 0x08 */ s32 c;
} SplitAFF0;

extern AudioSpecAFF0 D_811526C4[];
extern s16 D_811526F8;
extern u16 D_81184278;
extern s16 D_8118427C;
extern void* D_81184288;
extern s32 D_81184298;
extern SessionSplitAFF0 D_81184620;
extern SplitAFF0 D_81184630;
extern SplitAFF0 D_81184638;
extern SplitAFF0 D_81184648;
extern u8 D_81184658;
extern s32 D_811858E4;
extern s16 D_811858EC;
extern void* D_81185900[2];
extern s32 D_811859B4;
extern f32 D_811859B0;
extern u32 D_8118568C;
extern s32 D_8118557C;
// AudioHeap_InitSampleCaches is defined as void in the next file, but this file calls it as
// if it returned a value (as with an implicit declaration); the call only
// matches that way.
s32 AudioHeap_InitSampleCaches(s32, s32);
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
#define REVERBS_AFF0 ((SynthesisReverbAFF0*)D_81184110)

/**
 * Lays out the audio heap and reverbs for the current audio spec. Zelda 64 audio driver.
 * Seen in play (2026-11-13) ran when the GB player started (main menu GB, Yes; second entry after
 * quitting).
 * @unverified Name and comment guessed from the code.
 */
void AudioHeap_Init(void) {
    UNUSED s32 pad[5]; // FAKE: stack pad of unknown origin; only reserves frame space
    s32 persistent_mem;
    s32 temporary_mem;
    s32 total_mem;
    s32 want_misc;
    s32 j;
    s32 i;
    ReverbSettingsAFF0* settings;
    SynthesisReverbAFF0* reverb;
    AudioSpecAFF0* spec = &D_811526C4[D_81184658];

    D_8118568C = 0;
    D_811858B8.samplingFrequency = spec->frequency;
    D_811858B8.aiSamplingFrequency = func_80058100(D_811858B8.samplingFrequency);
    D_811858B8.samplesPerFrameTarget = ((D_811858B8.samplingFrequency / D_811859B4) + 0xF) & 0xFFF0;
    D_811858B8.minAiBufferLength = D_811858B8.samplesPerFrameTarget - 0x10;
    D_811858B8.maxAiBufferLength = D_811858B8.samplesPerFrameTarget + 0x10;
    D_811858B8.ticksPerUpdate = ((D_811858B8.samplesPerFrameTarget + 0x10) / 0xD0) + 1;
    D_811858B8.samplesPerTick = (D_811858B8.samplesPerFrameTarget / D_811858B8.ticksPerUpdate) & ~7;
    D_811858B8.samplesPerTickMax = D_811858B8.samplesPerTick + 8;
    D_811858B8.samplesPerTickMin = D_811858B8.samplesPerTick - 8;
    D_811858B8.resampleRate = 32000.0f / (s32)D_811858B8.samplingFrequency;
    D_811858B8.ticksPerUpdateInvScaled = (1.0f / 256.0f) / D_811858B8.ticksPerUpdate;
    D_811858B8.ticksPerUpdateScaled = D_811858B8.ticksPerUpdate / 4.0f;
    D_811858B8.ticksPerUpdateInv = 1.0f / D_811858B8.ticksPerUpdate;
    D_811858E8 = spec->numNotes;
    D_811858B8.numSequencePlayers = spec->numSequencePlayers;
    if (D_811858B8.numSequencePlayers >= 2) {
        D_811858B8.numSequencePlayers = 1;
    }
    D_81184278 = spec->unk_0C;
    D_811858EC = (u32)(D_811858B8.ticksPerUpdate * 2880000.0f / D_811526F8 / D_811859B0);
    D_811858B8.specUnk4 = spec->unk_04;
    D_811858B8.samplesPerFrameTarget *= D_811858B8.specUnk4;
    D_811858B8.maxAiBufferLength *= D_811858B8.specUnk4;
    D_811858B8.minAiBufferLength *= D_811858B8.specUnk4;
    D_811858B8.ticksPerUpdate *= D_811858B8.specUnk4;
    if (D_811858B8.specUnk4 >= 2) {
        D_811858B8.maxAiBufferLength -= 0x10;
    }
    D_811858E4 = D_811858E8 * 0x14 * D_811858B8.ticksPerUpdate + spec->numReverbs * 0x20 + 0x1E0;
    persistent_mem = spec->persistentSeqMem + spec->persistentFontMem + spec->persistentSampleMem + spec->persistentSampleCacheSize + 0x10;
    temporary_mem = spec->temporarySeqMem + spec->temporaryFontMem + spec->temporarySampleMem + spec->temporarySampleCacheSize + 0x10;
    total_mem = persistent_mem + temporary_mem;
    want_misc = D_81184298 - total_mem - 0x100;
    D_81184620.miscPoolSize = want_misc;
    D_81184620.cachePoolSize = total_mem;
    AudioHeap_InitSessionPools((s8*)&D_81184620);
    D_81184630.a = persistent_mem;
    D_81184630.b = temporary_mem;
    AudioHeap_InitCachePools((s8*)&D_81184630);
    D_81184638.a = spec->persistentSeqMem;
    D_81184638.b = spec->persistentFontMem;
    D_81184638.c = spec->persistentSampleMem;
    AudioHeap_InitPersistentCache((s8*)&D_81184638);
    D_81184648.a = spec->temporarySeqMem;
    D_81184648.b = spec->temporaryFontMem;
    D_81184648.c = spec->temporarySampleMem;
    AudioHeap_InitTemporaryCache((s8*)&D_81184648);
    AudioHeap_InitSampleCaches(spec->persistentSampleCacheSize, spec->temporarySampleCacheSize);
    if (EXTERNAL_POOL_AFF0.startRamAddr != NULL) {
        EXTERNAL_POOL_AFF0.curRamAddr = EXTERNAL_POOL_AFF0.startRamAddr;
    }
    AudioHeap_ResetLoadStatus();
    D_81184664 = (Rec81109678*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, D_811858E8 * 0xCC);
    AudioPlayback_NoteInitAll();
    AudioPlayback_InitNoteFreeList();
    D_81184288 = (void*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, D_811858B8.ticksPerUpdate * D_811858E8 * 0x18);
    for (i = 0; i != 2; i++) {
        D_81185900[i] = (void*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, D_811858E4 * 8);
    }
    for (i = 0; i < 1; i++) {
        reverb = &REVERBS_AFF0[i];
        reverb->useReverb = 0;
    }
    D_8118427B = spec->numReverbs;
    for (i = 0; i < D_8118427B; i++) {
        reverb = &REVERBS_AFF0[i];
        settings = &spec->reverbSettings[i];

        reverb->downsampleRate = settings->downsampleRate;
        reverb->windowSize = settings->windowSize * 64;
        reverb->windowSize /= reverb->downsampleRate;
        reverb->decayRatio = settings->decayRatio;
        reverb->volume = settings->volume;
        reverb->leakRtl = settings->leakRtl;
        reverb->leakLtr = settings->leakLtr;
        reverb->mixReverbIndex = settings->mixReverbIndex;
        reverb->mixReverbStrength = settings->mixReverbStrength;
        reverb->useReverb = 8;
        reverb->leftRingBuf = (s16*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, reverb->windowSize * 2);
        reverb->rightRingBuf = (s16*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, reverb->windowSize * 2);
        reverb->nextRingBufPos = 0;
        reverb->unk_18 = 0;
        reverb->curFrame = 0;
        reverb->bufSizePerChan = reverb->windowSize;
        reverb->framesToIgnore = 2;
        reverb->resampleFlags = 1;
        reverb->soundSample = &reverb->sample;
        reverb->sample.loop = &reverb->loop;
        reverb->soundTuning = 1.0f;
        reverb->sample.codec = 3;
        reverb->sample.medium = 0;
        reverb->sample.size = reverb->windowSize * 2;
        reverb->sample.sampleAddr = reverb->leftRingBuf;
        reverb->loop.start = 0;
        reverb->loop.count = 1;
        reverb->loop.end = reverb->windowSize;
        if (reverb->downsampleRate != 1) {
            reverb->resampleRate = 0x8000 / reverb->downsampleRate;
            reverb->resampleStateLeft = (void*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, 0x20);
            reverb->resampleStateRight = (void*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, 0x20);
            reverb->unk_30 = (void*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, 0x20);
            reverb->unk_34 = (void*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, 0x20);
            for (j = 0; j < D_811858B8.ticksPerUpdate; j++) {
                s16* mem = (s16*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, 0x340);

                reverb->items[0][j].toDownsampleLeft = mem;
                reverb->items[0][j].toDownsampleRight = mem + 0xD0;
                mem = (s16*)GbApu_AllocZeroed((AudioAllocPool*)&D_811842C0, 0x340);
                reverb->items[1][j].toDownsampleLeft = mem;
                reverb->items[1][j].toDownsampleRight = mem + 0xD0;
            }
        }
        if (settings->lowPassFilterCutoffLeft != 0) {
            reverb->filterLeftState = (s16*)GbApu_Alloc((AudioAllocPool*)&D_811842C0, 0x20);
            reverb->filterLeft = (s16*)GbApu_Alloc((AudioAllocPool*)&D_811842C0, 0x10);
            AudioHeap_LoadLowPassFilter(reverb->filterLeft, settings->lowPassFilterCutoffLeft);
        } else {
            reverb->filterLeft = NULL;
        }
        if (settings->lowPassFilterCutoffRight != 0) {
            reverb->filterRightState = (s16*)GbApu_Alloc((AudioAllocPool*)&D_811842C0, 0x20);
            reverb->filterRight = (s16*)GbApu_Alloc((AudioAllocPool*)&D_811842C0, 0x10);
            AudioHeap_LoadLowPassFilter(reverb->filterRight, settings->lowPassFilterCutoffRight);
        } else {
            reverb->filterRight = NULL;
        }
    }
    func_81115480();
    for (j = 0; j < D_811858B8.numSequencePlayers; j++) {
        func_8111539C(j);
        func_811152A4(j);
    }
    AudioLoad_InitSampleDmaBuffers(D_811858E8);
    D_8118557C = 0;
    D_8118427C = 0x1000;
    func_8110FAF4();
    func_8005C0A0();
}
