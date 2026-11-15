/* Stadium Zero fragment004_15F8F0. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_player_party_icons/gb_player_party_icons.c. */

#include "gb_player_party_icons.h"
#include "display_object_textures.h"
#include "gfx_buffer.h"
#include "memory_main.h"
#include "poke_icon.h"
#include "pokemon_stats.h"
#include "stage_loader.h"
extern PokeIconRenderer* sGbPlayerIconRenderer;
extern BattleMon sGbPlayerParty[6];
extern s32 sGbPlayerPartyCount;

s32 GbPlayer_PartyIconsFrameCallback(u8 fadeMode);

/**
 * Reads the party from the Game Boy save in the Transfer Pak on `port` (0-based) and queues a
 * 40x40 icon for each Pokémon. Leaves the count at 0 when the save can't be read.
 * Seen in play (2026-11-14): Deck_Open(0x20, 0, 0, 0) with the pak in port 1, and a count of 2
 * for a two-Pokémon Green party.
 */
void GbPlayer_LoadPartyFromDeck(s32 port) {
    s32 i;
    DeckHandle* deck;

    if (GbSave_EnsureMainDataLoaded(port) != 0) {
        deck = Deck_Open(0x20, port, 0, 0);
        sGbPlayerPartyCount = Deck_ReadEntries(sGbPlayerParty, 6, deck);
        Deck_CloseAndFlush(deck);
    }

    for (i = 0; i < sGbPlayerPartyCount; i++) {
        PokeIcon_SetMonSlot(sGbPlayerIconRenderer, i, &sGbPlayerParty[i], 1);
    }
}

/**
 * Per-frame callback while the party icons render: polls input (unused), renders the queued icons
 * and draws a blank frame. Returns 0, so it runs for the full 8 frames.
 * Seen in play (2026-11-14): 8 calls on a black screen with fadeMode 1, before the GB screen.
 */
s32 GbPlayer_PartyIconsFrameCallback(u8 fadeMode) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    PokeIcon_ProcessAllSlots(sGbPlayerIconRenderer, 0);
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    return 0;
}

s32 Save_LoadSram(void);
s32 Save_GetGbPlayerSettings(s8*, s32*);

/**
 * Fills the GB emulator's launch parameters: the saved frame and button options, the party count
 * and a copy of each rendered icon, with the unused icon slots zeroed.
 * Seen in play (2026-11-14): partyCount 2, buttonConfig 0, framesUnlocked 0 with a fresh N64 save.
 */
void GbPlayer_FillLaunchParams(GbPlayerLaunchParams* params) {
    s32 i;
    s8 framesUnlocked;
    s32 buttonConfig;
    u16(*icon)[0x640] = params->partyIcons[0];

    Save_GetGbPlayerSettings(&framesUnlocked, &buttonConfig);
    params->framesUnlocked = framesUnlocked;
    params->buttonConfig = buttonConfig;
    params->partyCount = sGbPlayerPartyCount;

    for (i = 0; i < sGbPlayerPartyCount; i++, icon++) {
        _bcopy(PokeIcon_GetImage(sGbPlayerIconRenderer, i), icon, sizeof(icon[0]));
    }

    if (sGbPlayerPartyCount < 6) {
        bzero(icon, 0x4B00 + (-sGbPlayerPartyCount * 0xC80));
    }
}

extern ModelLoadContext* sGbPlayerIconFramebuffers;
/**
 * Fragment entry, called by State_GbPlayer before the GB emulator starts (Zero's main menu "GB",
 * ゲームボーイのポケモン). Reads the party from the Game Boy save on `port`, renders a 40x40 icon of
 * each Pokémon over 8 blank frames and fills `params` for the emulator. Returns the party count.
 * There is no team selection screen; the name GB Tower comes from Stadium 1.
 * Seen in play (2026-11-14): runs between confirming GB and the GB boot screen, screen black.
 */
s32 GbPlayer_PreparePartyIcons(s32 port, GbPlayerLaunchParams* params) {
    StageContext* stageCtx;

    main_pool_push_state('PREP');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    stageCtx = StageContext_Allocate(0, 1, 2, 0, 1, 1);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(FRAGMENT_PARTICLE_DATA_LIBRARY);

    sGbPlayerIconFramebuffers = PokeIcon_AllocFramebuffers(1);
    sGbPlayerIconRenderer = PokeIcon_CreateRenderList(sGbPlayerIconFramebuffers, 6, 0x28, 0x28);
    PokeIcon_OpenModelArchives();
    GbPlayer_LoadPartyFromDeck(port);
    Save_LoadSram();
    StageContext_Activate(stageCtx);
    BgStage_RunUntilCondition(8, GbPlayer_PartyIconsFrameCallback);
    StageContext_Deactivate();
    GbPlayer_FillLaunchParams(params);
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('PREP');

    return sGbPlayerPartyCount;
}
