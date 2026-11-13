/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/libnaudio/n_synthesizer.c. */

#include "libnaudio/n_synthInternals.h"
#define ONLY_ONE_PLAYER
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
s32 __n_nextSampleTime(ALPlayer** client);
s32 _n_timeToSamplesNoRound(s32 micros);
#ifndef ONLY_ONE_PLAYER
#endif

#include "m2c_macros.h"

void n_alSynNew(ALSynConfig* c);
ALParam* __n_allocParam(void);
void _n_freeParam(ALParam* param);
void _n_collectPVoices(void);
void _n_freePVoice(N_PVoice* pvoice);

/***********************************************************************
 * Synthesis driver public interfaces
 ***********************************************************************/
void n_alSynNew(ALSynConfig* c) {
    s32 i;
    N_ALVoice* vv;
    N_PVoice* pv;
    N_ALVoice* vvoices;
    N_PVoice* pvoices;
    ALHeap* hp = c->heap;
    ALSave* save;
    ALFilter* sources;
    N_PVoice* m_sources;
    ALParam* params;
    ALParam* param_ptr;

    n_syn->head = NULL;
    n_syn->numPVoices = c->maxPVoices;
    n_syn->curSamples = 0;
    n_syn->paramSamples = 0;
    n_syn->outputRate = c->outputRate;
    n_syn->maxOutSamples = FIXED_SAMPLE;
    n_syn->dma = (ALDMANew)c->dmaproc;

    /******* save new *******************************/
    n_syn->sv_dramout = 0;
    n_syn->sv_first = 1;

    /******* aux new *******************************/
    n_syn->auxBus = (N_ALAuxBus*)alHeapAlloc(hp, 1, sizeof(N_ALAuxBus));

    n_syn->auxBus->sourceCount = 0;
    n_syn->auxBus->maxSources = c->maxPVoices;
    n_syn->auxBus->sources = (N_PVoice**)alHeapAlloc(hp, c->maxPVoices, sizeof(N_PVoice*));

    /******* main new *******************************/
    n_syn->mainBus = (N_ALMainBus*)alHeapAlloc(hp, 1, sizeof(N_ALMainBus));

    /******* fx new *******************************/

    if (c->fxType != AL_FX_NONE) {
        n_syn->auxBus->fx = n_alSynAllocFX(0, c, hp);
        n_syn->mainBus->filter.handler = (N_ALCmdHandler)n_alFxPull;
    } else {
        n_syn->mainBus->filter.handler = (N_ALCmdHandler)n_alAuxBusPull;
    }

    n_syn->pFreeList.next = 0;
    n_syn->pFreeList.prev = 0;
    n_syn->pLameList.next = 0;
    n_syn->pLameList.prev = 0;
    n_syn->pAllocList.next = 0;
    n_syn->pAllocList.prev = 0;

    pvoices = alHeapAlloc(hp, c->maxPVoices, sizeof(N_PVoice));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        alLink((ALLink*)pv, &n_syn->pFreeList);
        pv->vvoice = 0;
        alN_PVoiceNew(pv, n_syn->dma, hp);
        n_syn->auxBus->sources[n_syn->auxBus->sourceCount++] = pv;
    }

    params = alHeapAlloc(hp, c->maxUpdates, sizeof(ALParam));
    n_syn->paramList = 0;
    for (i = 0; i < c->maxUpdates; i++) {
        param_ptr = &params[i];
        param_ptr->next = n_syn->paramList;
        n_syn->paramList = param_ptr;
    }
    n_syn->heap = hp;
}

Acmd* n_alAudioFrame(Acmd* cmd_list, s32* cmd_len, s16* out_buf, s32 outLen) {
    ALPlayer* client;
    s16 tmp = 0; /* Starting buffer in DMEM */
    Acmd* cmdl_end = cmd_list;
    Acmd* cmd_ptr;
    s32 n_out;
    s16* l_out_buf = out_buf;


    if (n_syn->head == 0) {
        *cmd_len = 0;
        return cmd_list; /* nothing to do */
    }

    /*
     * run down list of clients and execute callback if needed this
     * subframe. Here we do all the work for the frame at the
     * start. Time offsets that occur before the next frame are
     * executed "early".
     */


    /*
     * paramSamples = time of next parameter change.
     * curSamples = current sample time.
     * so paramSamples - curSamples is the time until the next parameter change.
     * if the next parameter change occurs within this frame time (outLen),
     * then call back the client that contains the parameter change.
     * Note, paramSamples must be rounded down to 16 sample boundary for use
     * during the client handler.
     */

#ifndef ONLY_ONE_PLAYER
    for (n_syn->paramSamples = __n_nextSampleTime(&client); n_syn->paramSamples - n_syn->curSamples < outLen;
         n_syn->paramSamples = __n_nextSampleTime(&client)) {
        n_syn->paramSamples &= ~0xf;
        client->samplesLeft += _n_timeToSamplesNoRound((*client->handler)(client));
    }
#else
    client = n_syn->head;
    while (client->samplesLeft - n_syn->curSamples < outLen) {
        n_syn->paramSamples = (client->samplesLeft & ~0xf);
        client->samplesLeft += _n_timeToSamplesNoRound((*client->handler)(client));
    }
#endif

    /* for safety's sake, always store paramSamples aligned to 16 sample boundary.
     * this way, if an voice handler routine gets called outside the N_ALVoiceHandler
     * routine (alSynAllocVoice) it will get timestamped with an aligned value and
     * will be processed immediately next audio frame.
     */
    n_syn->paramSamples &= ~0xf;


    /*
     * Now build the command list in small chunks
     */
    while (outLen > 0) {
        n_out = MIN(n_syn->maxOutSamples, outLen);

        /*
         * construct the command list for each physical voice by calling
         * the head of the filter chain.
         */
        cmd_ptr = cmdl_end;
        n_syn->sv_dramout = (s32)l_out_buf;
        cmdl_end = n_alSavePull(n_syn->curSamples, cmd_ptr);

        outLen -= n_out;
        l_out_buf += n_out << 1; /* For Stereo */
        n_syn->curSamples += n_out;
    }
    *cmd_len = (s32)(cmdl_end - cmd_list);

    _n_collectPVoices(); /* collect free physical voices */

    return cmdl_end;
}

ALParam* __n_allocParam(void) {
    ALParam* update = 0;

    if (n_syn->paramList) {
        update = n_syn->paramList;
        n_syn->paramList = n_syn->paramList->next;
        update->next = 0;
    }
    return update;
}

void _n_freeParam(ALParam* param) {
    param->next = n_syn->paramList;
    n_syn->paramList = param;
}

void _n_collectPVoices(void) {
    ALLink* dl;
    N_PVoice* pv;

    while ((dl = n_syn->pLameList.next) != 0) {
        pv = (N_PVoice*)dl;

        /* ### remove from mixer */

        alUnlink(dl);
        alLink(dl, &n_syn->pFreeList);
    }
}

void _n_freePVoice(N_PVoice* pvoice) {
    /*
     * move the voice from the allocated list to the lame list
     */
    alUnlink((ALLink*)pvoice);
    alLink((ALLink*)pvoice, &n_syn->pLameList);
}

/**
 * Add 0.5 to adjust the average affect of
 * the truncation error produced by casting
 * a float to an int.
 * Seen in play (2026-11-13) (tour of menus and a COM battle): ran in the main menu, the Pokédex,
 * the party screen, the Lab list, Lab sort, registration, the Lab PC, Free Battle setup, the battle
 * opening, a switch in battle, running from battle and a Pound turn.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 _n_timeToSamplesNoRound(s32 micros) {
    f32 tmp = ((f32)micros) * n_syn->outputRate / 1000000.0 + 0.5;

    return (s32)tmp;
}

s32 _n_timeToSamplesNoRound(s32 micros);

s32 _n_timeToSamples(s32 micros) {
    return _n_timeToSamplesNoRound(micros) & ~0xF;
}
