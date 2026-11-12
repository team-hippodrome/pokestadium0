/* Stadium Zero resident code. */

#include "global.h"

/*
 * n_alSynAllocVoice: initialises the record `arg0` from the descriptor `arg1` and
 * tries to attach a second object to it.
 *
 * `arg1` holds a s16 at +0 (copied to arg0+0x16 and used as the lookup key), a s16 at
 * +2 (copied to arg0+0x18) and a u8 at +4 (copied, widened, to arg0+0x1A).  arg0+0x14
 * and the words at arg0+0x8 / +0xC are cleared.  _allocatePVoice(&obj, key) then looks
 * up an object.  If it leaves a non-NULL `obj`, the two are linked (obj+0x8 and
 * arg0+0x8 point at each other).  If _allocatePVoice also returned non-zero, obj's word
 * at +0x88 is set to 0x200 (after clearing word +0x8 of the record that obj+0x8 pointed
 * at before the link) and two blocks are posted with func_8003AE2C(obj, 3, block): the
 * first has halfword +8 = 0xB (word +4 = D_80075E44[+0x1C], word +0xC = 0, word +0x10 = obj[+0x88] - 0x40) and,
 * if func_800448F8 can supply a second block, one with halfword +8 = 0xF (word +0 = 0,
 * word +4 = D_80075E44[+0x1C] + obj[+0x88]).  If it returned zero, obj[+0x88] is cleared
 * and only the link is made.  Returns 1 if an object was found, else 0.  (The meaning
 * of these records is not established here; the field offsets are taken from the retail code.)
 */

#include "m2c_macros.h"
M2C_UNK func_8003AE2C(void *, M2C_UNK, void *);
s32 _allocatePVoice(void **, s16);
void *func_800448F8();
extern void *D_80075E44;

s32 n_alSynAllocVoice(void *arg0, void *arg1) {
    void *obj;
    s32 found;
    void *msg_a;
    void *msg_b;

    obj = NULL;
    M2C_FIELD(arg0, s16 *, 0x16) = (s16) M2C_FIELD(arg1, s16 *, 0);
    M2C_FIELD(arg0, s16 *, 0x1A) = (s16) M2C_FIELD(arg1, u8 *, 4);
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0x18) = (s16) M2C_FIELD(arg1, s16 *, 2);
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    M2C_FIELD(arg0, void **, 8) = NULL;
    found = _allocatePVoice(&obj, M2C_FIELD(arg1, s16 *, 0));
    if (obj) {
        if (found != 0) {
            M2C_FIELD(obj, s32 *, 0x88) = 0x200;
            M2C_FIELD(M2C_FIELD(obj, void **, 8), s32 *, 8) = 0;
            M2C_FIELD(obj, void **, 8) = arg0;
            M2C_FIELD(arg0, void **, 8) = obj;
            msg_a = func_800448F8();
            M2C_FIELD(msg_a, s32 *, 4) = (s32) M2C_FIELD(D_80075E44, s32 *, 0x1C);
            M2C_FIELD(msg_a, s16 *, 8) = 0xB;
            M2C_FIELD(msg_a, s32 *, 0xC) = 0;
            M2C_FIELD(msg_a, s32 *, 0x10) = (s32) (M2C_FIELD(obj, s32 *, 0x88) - 0x40);
            func_8003AE2C(M2C_FIELD(arg0, void **, 8), 3, msg_a);
            msg_b = func_800448F8();
            if (msg_b != NULL) {
                M2C_FIELD(msg_b, s32 *, 4) = (s32) (M2C_FIELD(obj, s32 *, 0x88) + M2C_FIELD(D_80075E44, s32 *, 0x1C));
                M2C_FIELD(msg_b, s16 *, 8) = 0xF;
                M2C_FIELD(msg_b, s32 *, 0) = 0;
                func_8003AE2C(M2C_FIELD(arg0, void **, 8), 3, msg_b);
            }
        } else {
            M2C_FIELD(obj, s32 *, 0x88) = 0;
            M2C_FIELD(obj, void **, 8) = arg0;
            M2C_FIELD(arg0, void **, 8) = obj;
        }
    }
    return obj != NULL;
}

typedef struct ALLink800443C4 {
    struct ALLink800443C4* next;
    struct ALLink800443C4* prev;
} ALLink800443C4;
typedef struct PVoice800443C4 {
    /* 0x00 */ ALLink800443C4 node;
    /* 0x08 */ s8* vvoice;
    /* 0x0C */ char unk0C[0x7C];
    /* 0x88 */ s32 offset;
} PVoice800443C4;
typedef struct Synth800443C4 {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ ALLink800443C4 pFreeList;
    /* 0x0C */ ALLink800443C4 pAllocList;
    /* 0x14 */ ALLink800443C4 pLameList;
} Synth800443C4;
void func_8004D600(ALLink800443C4*);
void func_8004D630(ALLink800443C4*, ALLink800443C4*);
/**
 * @unverified Name from Stadium 1, matched by code similarity.
 */
s32 _allocatePVoice(void** pvoice, s16 priority) {
    ALLink800443C4* dl;
    PVoice800443C4* pv;
    s32 stolen = 0;

    if ((dl = ((Synth800443C4*)D_80075E44)->pLameList.next) != NULL) {
        *pvoice = dl;
        func_8004D600(dl);
        func_8004D630(dl, &((Synth800443C4*)D_80075E44)->pAllocList);
    } else if ((dl = ((Synth800443C4*)D_80075E44)->pFreeList.next) != NULL) {
        *pvoice = dl;
        func_8004D600(dl);
        func_8004D630(dl, &((Synth800443C4*)D_80075E44)->pAllocList);
    } else {
        for (dl = ((Synth800443C4*)D_80075E44)->pAllocList.next; dl != NULL; dl = dl->next) {
            pv = (PVoice800443C4*)dl;
            if (M2C_FIELD(pv->vvoice, s16*, 0x16) <= priority && pv->offset == 0) {
                *pvoice = pv;
                priority = M2C_FIELD(pv->vvoice, s16*, 0x16);
                stolen = 1;
            }
        }
    }
    return stolen;
}
