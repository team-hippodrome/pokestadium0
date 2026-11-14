/*
 * Stadium Zero fragment032_35C390 (loaded at 0x8F500000): the VS screen's trainer panels.
 *
 * VsScene_LoadGeoLayout builds the panel model from this fragment's geo layout (D_8F504830), and
 * VsScene_PlayTitleAndRevealTeams shows it after the flaming title: one panel per side with the trainer
 * portrait, the title line, the name, and a row of six Pokémon icons with nicknames. Each node's
 * callbackArg is the side (index into D_82203170), or (side << 16) | slot for the six
 * icon and nickname nodes. The panels show the whole team the order screen picks from
 * (rosterInfo[0]), not the picked Pokémon. geo_model_033 is the panel model of the other VS
 * routines (VsScene_PlayFreeBattleResults, VsScene_PlayTournamentResults), which read the picked teams (teamMember).
 * Seen in play (2026-11-14, Free Battle 1P vs COM): the two panels flip in after the 「VS」
 * letters, first with portrait, 「トレーナー」 and 1P / ＣＯＭ, then turned over to the six icons
 * with nicknames. Stub tests below wrote `jr ra; nop` over one callback each.
 *
 * VsPanel_SelectTitleRound is not used by the panel: the title model's geo layout in fragment
 * 035 (0x8EC00000) calls it as its root callback.
 */

#include "global.h"
#include "fragments/geo_model_033/geo_model_033.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"
#include "vs_trainer_panel.h"

extern Gfx sVsPanelPortraitDL[];
extern Gfx sVsPanelIconDL[];
extern u8 sVsPanelNicknameText[];

/**
 * Boot-code check: with interrupts masked and the PI idle, reads the cartridge word at ROM 0xD10
 * (inside the IPL3 boot code, 0x00800400 in the retail ROM) and returns -1 instead of
 * `displayList` when its low half is not 0x0400. A copier or a ROM with other boot code then gets
 * a broken display list pointer. geo_model_033 and geo_model_038
 * (CartridgeCheckModels_CheckBootCode) have the same check on other boot-code words.
 * Seen in play (2026-11-14): called for both portraits every frame of the panels; forcing it to
 * return -1 turned the whole screen black from the panels on.
 */
s32 VsPanel_CheckBootCode(s32 displayList) {
    OSIntMask prevMask;

    prevMask = osSetIntMask(OS_IM_NONE);
    if (!((*(volatile s32 *)0xA4600010) & 3) && (((*(volatile s32 *)0xB0000D10) & 0xFFFF) != 0x400)) {
        displayList = -1;
    }
    osSetIntMask(prevMask);
    return displayList;
}

/**
 * Root callback of the flaming battle-title model (geo layout in fragment 035): selects the
 * switch case rootId - 1, the round's title. rootId is the round (roundOrDemoId) that
 * VsScene_PlayTitleAndRevealTeams passes to Model_InitDisplayObject.
 * @unverified: in Free Battle it ran once, with event 0, while the title layout was built (the
 * title model is only animated in tournaments, D_822036A4->mode != 0), so the round switch was not
 * seen.
 */
void VsPanel_SelectTitleRound(s32 event, GeoModelRootNode* node) {
    if (event == 2) {
        node->unk_1A = D_80060490->rootId - 1;
    }
}

/**
 * Writes the portrait display list: segment 0x0F = the trainer's BinArchive file, then a branch
 * to sVsPanelPortraitDL.
 */
Gfx* VsPanel_WritePortraitGfx(Gfx* gfx, void* trainerFile) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(trainerFile));
    gSPBranchList(gfx++, sVsPanelPortraitDL);
    return gfx;
}

/**
 * Portrait node callback: builds the display list of the side's trainer portrait
 * (VsSceneSide.trainerFile), passed through VsPanel_CheckBootCode.
 * Seen in play (2026-11-14): stubbing it removed both trainer portraits from the panels.
 */
void VsPanel_PortraitCallback(s32 event, DemoGeoNode* node) {
    s32 pad; // FAKE: stack padding
    VsSceneSide* teams;

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        node->displayList = Gfx_AllocDisplayList(0x10);
        VsPanel_WritePortraitGfx(node->displayList, teams[(s32)node->node.callbackArg].trainerFile);
        node->displayList = (Gfx*)VsPanel_CheckBootCode((s32)node->displayList);
    }
}

/**
 * Title text node callback: shows the side's title line (rosterInfo[0]->title, 「トレーナー」 in
 * Free Battle).
 * Seen in play (2026-11-14): stubbing it removed the 「トレーナー」 lines from both panels.
 */
void VsPanel_TitleTextCallback(s32 event, DemoGeoNode* node) {
    VsSceneSide* teams;

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        node->unk_24 = (u8*)teams[(s32)node->node.callbackArg].rosterInfo[0]->title;
    }
}

/**
 * Name text node callback: shows the side's name (rosterInfo[0]->fullName) and moves the text by
 * the roster's flags: bit 0 sets unk_20 to 0xD2, bit 1 sets unk_22 to -0xF0, otherwise unk_22 is
 * -0x12C.
 * Seen in play (2026-11-14): stubbing it removed the names (1P, ＣＯＭ) from both panels.
 * @unverified: the offsets; Free Battle rosters have unk_000 = 0, so only the -0x12C case ran.
 */
void VsPanel_NameTextCallback(s32 event, DemoGeoNode* node) {
    VsSceneSide* teams;

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        node->unk_24 = (u8*)teams[(s32)node->node.callbackArg].rosterInfo[0]->fullName;
        if (*(s16*)&teams[(s32)node->node.callbackArg].rosterInfo[0]->unk_000 & 1) {
            node->unk_20 = 0xD2;
        } else if (*(s16*)&teams[(s32)node->node.callbackArg].rosterInfo[0]->unk_000 & 2) {
            node->unk_22 = -0xF0;
        } else {
            node->unk_22 = -0x12C;
        }
    }
}

/**
 * Writes an icon display list: segment 0x0F = the Pokémon's icon image, then a branch to
 * sVsPanelIconDL.
 */
Gfx* VsPanel_WriteIconGfx(Gfx* gfx, void* iconImage) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(iconImage));
    gSPBranchList(gfx++, sVsPanelIconDL);
    return gfx;
}

/**
 * Icon node callback (callbackArg = (side << 16) | slot): draws the slot's Pokémon icon
 * (VsSceneSide.iconImages, from VsScene_LoadTeamIcons), or nothing past the team size.
 * Seen in play (2026-11-14): stubbing it removed the team icons from the panels; the nicknames
 * stayed.
 */
void VsPanel_IconCallback(s32 event, DemoGeoNode *node)
{
  s32 pad; // FAKE: stack padding
  VsSceneSide *teams;
  s32 team;
  s32 slot;
  if (event == 2)
  {
    teams = D_80060490->node.callbackArg;
    team = (((u32) node->node.callbackArg) >> 16) & 0xFFFF;
    slot = ((u32) node->node.callbackArg) & 0xFFFF;
    if (slot < teams[team].rosterInfo[0]->numberOfPokemonCanBePicked)
    {
      node->displayList = Gfx_AllocDisplayList(0x10);
      VsPanel_WriteIconGfx(node->displayList, teams[team].iconImages[slot]);
    }
    else
    {
      node->displayList = 0;
      if (node) // FAKE: karodo
      {
      }
    }
  }
}

/**
 * Nickname node callback (callbackArg = (side << 16) | slot): copies the slot's nickname into the
 * shared buffer sVsPanelNicknameText behind a 0x09 text control byte and shows it, or nothing past
 * the team size.
 * Seen in play (2026-11-14): stubbing it removed the nicknames (ピカのすけ ...); the icons stayed.
 */
void VsPanel_NicknameCallback(s32 event, DemoGeoNode* node) {
    VsSceneSide* teams;
    s32 team;
    s32 slot;

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        team = ((u32)node->node.callbackArg >> 16) & 0xFFFF;
        slot = (u32)node->node.callbackArg & 0xFFFF;
        if (slot < teams[team].rosterInfo[0]->numberOfPokemonCanBePicked) {
            sVsPanelNicknameText[0] = 9;
            _bcopy(teams[team].rosterInfo[0]->battleMon[slot].nickname, &sVsPanelNicknameText[1], 0xC);
            node->unk_24 = sVsPanelNicknameText;
        } else {
            node->unk_24 = NULL;
        }
    }
}
