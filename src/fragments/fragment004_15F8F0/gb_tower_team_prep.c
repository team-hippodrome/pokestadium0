/* Stadium Zero fragment004_15F8F0. */
/* C ported from the Stadium 1 decomp: src/fragments/gb_tower_team_prep/gb_tower_team_prep.c. */

#include "fragments/gb_tower_team_prep/gb_tower_team_prep.h"
#include "display_object_textures.h"
#include "poke_icon.h"
#include "pokemon_stats.h"
#include "save_data.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
extern unk_func_8001A024* D_81300384;
extern BattleMon D_81300388[6];
extern s32 D_81300370;

s32 GbTower_TeamPrepFrameCallback(u8 arg0);

void GbTower_LoadPartyFromDeck(s32 arg0) {
    s32 i;
    DeckHandle* temp_v0;

    if (GbSave_EnsureMainDataLoaded(arg0) != 0) {
        temp_v0 = Deck_Open(0x20, arg0, 0, 0);
        D_81300370 = Deck_ReadEntries(D_81300388, 6, temp_v0);
        Deck_CloseAndFlush(temp_v0);
    }

    for (i = 0; i < D_81300370; i++) {
        func_8001833C(D_81300384, i, &D_81300388[i], 1);
    }
}

s32 GbTower_TeamPrepFrameCallback(u8 arg0) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    PokeIcon_ProcessAllSlots(D_81300384, 0);
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    return 0;
}

s32 func_80023C30(void);
s32 func_80025100(s8*, s32*);

void GbTower_BuildPartyResult(UnkInputStruct8000D738* arg0) {
    s32 i;
    s8 tier;
    s32 field;
    u16(*var_s1)[0x640] = arg0->unk_04[0];

    func_80025100(&tier, &field);
    arg0->unk_02 = tier;
    arg0->unk_00 = field;
    arg0->unk_03 = D_81300370;

    for (i = 0; i < D_81300370; i++, var_s1++) {
        _bcopy(PokeIcon_GetImage(D_81300384, i), var_s1, sizeof(var_s1[0]));
    }

    if (D_81300370 < 6) {
        bzero(var_s1, 0x4B00 + (-D_81300370 * 0xC80));
    }
}

extern ModelLoadContext* D_81300380;
s32 GbTower_TeamPrep(s32 arg0, UnkInputStruct8000D738* arg1) {
    StageContext* sp24;

    main_pool_push_state('PREP');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = StageContext_Allocate(0, 1, 2, 0, 1, 1);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(FRAGMENT_PARTICLE_DATA_LIBRARY);

    D_81300380 = PokeIcon_AllocFramebuffers(1);
    D_81300384 = PokeIcon_CreateRenderList(D_81300380, 6, 0x28, 0x28);
    PokeIcon_OpenModelArchives();
    GbTower_LoadPartyFromDeck(arg0);
    func_80023C30();
    StageContext_Activate(sp24);
    BgStage_RunUntilCondition(8, GbTower_TeamPrepFrameCallback);
    StageContext_Deactivate();
    GbTower_BuildPartyResult(arg1);
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('PREP');

    return D_81300370;
}
