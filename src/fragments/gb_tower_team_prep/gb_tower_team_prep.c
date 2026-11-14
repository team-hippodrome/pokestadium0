/* Stadium Zero fragment004_15F8F0. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_team_prep/gb_tower_team_prep.c. */

#include "gb_tower_team_prep.h"
#include "display_object_textures.h"
#include "gfx_buffer.h"
#include "memory_main.h"
#include "poke_icon.h"
#include "pokemon_stats.h"
#include "stage_loader.h"
extern PokeIconRenderer* sGbTowerIconRenderer;
extern BattleMon sGbTowerParty[6];
extern s32 sGbTowerPartyCount;

s32 GbTower_PartyIconsFrameCallback(u8 fadeMode);

/**
 * Reads the party from the Game Boy save in the Transfer Pak on `port` (0-based) and queues a
 * 40x40 icon for each Pokémon. Leaves the count at 0 when the save can't be read.
 * Seen in play (2026-11-14): Deck_Open(0x20, 0, 0, 0) with the pak in port 1, and a count of 2
 * for a two-Pokémon Green party.
 */
void GbTower_LoadPartyFromDeck(s32 port) {
    s32 i;
    DeckHandle* deck;

    if (GbSave_EnsureMainDataLoaded(port) != 0) {
        deck = Deck_Open(0x20, port, 0, 0);
        sGbTowerPartyCount = Deck_ReadEntries(sGbTowerParty, 6, deck);
        Deck_CloseAndFlush(deck);
    }

    for (i = 0; i < sGbTowerPartyCount; i++) {
        func_8001833C(sGbTowerIconRenderer, i, &sGbTowerParty[i], 1);
    }
}

/**
 * Per-frame callback while the party icons render: polls input (unused), renders the queued icons
 * and draws a blank frame. Returns 0, so it runs for the full 8 frames.
 * Seen in play (2026-11-14): 8 calls on a black screen with fadeMode 1, before the GB screen.
 */
s32 GbTower_PartyIconsFrameCallback(u8 fadeMode) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    PokeIcon_ProcessAllSlots(sGbTowerIconRenderer, 0);
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    return 0;
}

s32 Save_LoadSram(void);
s32 Save_GetGbTowerSettings(s8*, s32*);

/**
 * Fills the GB emulator's launch parameters: the saved frame and button options, the party count
 * and a copy of each rendered icon, with the unused icon slots zeroed.
 * Seen in play (2026-11-14): partyCount 2, buttonConfig 0, framesUnlocked 0 with a fresh N64 save.
 */
void GbTower_FillLaunchParams(GbTowerLaunchParams* params) {
    s32 i;
    s8 framesUnlocked;
    s32 buttonConfig;
    u16(*icon)[0x640] = params->partyIcons[0];

    Save_GetGbTowerSettings(&framesUnlocked, &buttonConfig);
    params->framesUnlocked = framesUnlocked;
    params->buttonConfig = buttonConfig;
    params->partyCount = sGbTowerPartyCount;

    for (i = 0; i < sGbTowerPartyCount; i++, icon++) {
        _bcopy(PokeIcon_GetImage(sGbTowerIconRenderer, i), icon, sizeof(icon[0]));
    }

    if (sGbTowerPartyCount < 6) {
        bzero(icon, 0x4B00 + (-sGbTowerPartyCount * 0xC80));
    }
}

extern ModelLoadContext* sGbTowerIconFramebuffers;
/**
 * Fragment entry, called by State_GbTower before the GB emulator starts (Zero's main menu "GB",
 * ゲームボーイのポケモン). Reads the party from the Game Boy save on `port`, renders a 40x40 icon of
 * each Pokémon over 8 blank frames and fills `params` for the emulator. Returns the party count.
 * There is no team selection screen; the name GB Tower comes from Stadium 1.
 * Seen in play (2026-11-14): runs between confirming GB and the GB boot screen, screen black.
 */
s32 GbTower_PreparePartyIcons(s32 port, GbTowerLaunchParams* params) {
    StageContext* stageCtx;

    main_pool_push_state('PREP');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    stageCtx = StageContext_Allocate(0, 1, 2, 0, 1, 1);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(FRAGMENT_PARTICLE_DATA_LIBRARY);

    sGbTowerIconFramebuffers = PokeIcon_AllocFramebuffers(1);
    sGbTowerIconRenderer = PokeIcon_CreateRenderList(sGbTowerIconFramebuffers, 6, 0x28, 0x28);
    PokeIcon_OpenModelArchives();
    GbTower_LoadPartyFromDeck(port);
    Save_LoadSram();
    StageContext_Activate(stageCtx);
    BgStage_RunUntilCondition(8, GbTower_PartyIconsFrameCallback);
    StageContext_Deactivate();
    GbTower_FillLaunchParams(params);
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('PREP');

    return sGbTowerPartyCount;
}
