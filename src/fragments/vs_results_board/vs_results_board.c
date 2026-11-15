/**
 * Stadium Zero fragment033_35E790 (loaded at 0x8F600000): the VS scene's results board.
 *
 * VsScene_Run loads this fragment with the other VS scene models, and VsScene_LoadGeoLayout
 * builds its geo layout (D_8F619890) into D_82203250. VsScene_PlayFreeBattleResults (after a
 * single battle) and VsScene_PlayTournamentResults (after a tournament round) show it through
 * VsScene_PlayResultsBoard: one board per side with the Pokémon each side brought
 * (VsSceneSide.teamMember, not the whole roster), each with its icon, nickname and an HP bar that
 * drains to the HP left, then a red cross on each fainted one. VsScene_PlayWinLose then flips the
 * board over to the two trainer panels (portrait, title line, name), かち / まけ fly in and the
 * loser's panel shatters. Each node's callbackArg is the side (index into D_82203170), or
 * (side << 16) | slot for the per-Pokémon nodes.
 *
 * The board has two layouts, picked by VsResults_SelectLayout: a row of three per side
 * (VsResults_RowIconCallback, teamLayout 0) and a grid of six per side that also handles a
 * two-trainer side (VsResults_GridIconCallback, teamLayout 1 or 2).
 *
 * Seen in play (2026-11-14): a Free Battle 1P vs COM won by 1P (COM forced to 1 HP) showed the
 * board, then 「トレーナー 1P」 / 「トレーナー ＣＯＭ」 with portraits and 「かち」. Tests started
 * from a savestate taken as the board loaded; "stub" means `jr ra; nop` over the callback.
 * vs_trainer_panel (fragment 032) is the matching panel model shown before the battle.
 */

#include "global.h"
#include "vs_results_board.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"

extern Gfx sVsResultsPortraitDL[];
extern Gfx sVsResultsRowIconDL[];
extern Gfx sVsResultsGridIconDL[];
extern Gfx sVsResultsHpBarDL[];
extern u8 sVsResultsNicknameText[];

/**
 * Boot-code check: with interrupts masked and the PI idle, reads the cartridge word at ROM 0x800
 * (inside the IPL3 boot code, 0x24050001 in the retail ROM) and returns -1 instead of
 * `display_list` when its low half is not 1. A copier or a ROM with other boot code then gets a
 * broken portrait display list. vs_trainer_panel (VsPanel_CheckBootCode, ROM 0xD10) and
 * cartridge_check_models (CartridgeCheckModels_CheckBootCode) check other boot-code words.
 * Seen in play (2026-11-14): ran for both portraits every frame of the board and the panels and
 * returned `display_list` unchanged.
 * @unverified: the -1 path; the emulator runs the retail boot code, so it was not taken.
 */
s32 VsResults_CheckBootCode(s32 display_list) {
    OSIntMask prev_mask;

    prev_mask = osSetIntMask(OS_IM_NONE);
    if (!((*(volatile s32 *)0xA4600010) & 3) && (((*(volatile s32 *)0xB0000800) & 0xFFFF) != 1)) {
        display_list = -1;
    }
    osSetIntMask(prev_mask);
    return display_list;
}

/**
 * Writes the portrait display list: segment 0x0F = the trainer's BinArchive file, then a branch
 * to sVsResultsPortraitDL.
 */
Gfx* VsResults_WritePortraitGfx(Gfx* gfx, void* trainer_file) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(trainer_file));
    gSPBranchList(gfx++, sVsResultsPortraitDL);
    return gfx;
}

/**
 * Portrait node callback: builds the display list of the side's trainer portrait
 * (VsSceneSide.trainerFile), passed through VsResults_CheckBootCode.
 * Seen in play (2026-11-14): stubbing it removed the portraits from both win/lose panels.
 */
void VsResults_PortraitCallback(s32 event, DemoGeoNode* node) {
    s32 pad; // FAKE: stack padding
    VsSceneSide* teams;

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        node->displayList = Gfx_AllocDisplayList(0x10);
        VsResults_WritePortraitGfx(node->displayList, teams[(s32)node->node.callbackArg].trainerFile);
        node->displayList = (Gfx*)VsResults_CheckBootCode((s32)node->displayList);
    }
}

/**
 * Title text node callback: shows the side's title line (rosterInfo[0]->title, 「トレーナー」 in
 * Free Battle) on the win/lose panel.
 * Seen in play (2026-11-14): poking 1P's title to ＡＢ showed ＡＢ over the name.
 */
void VsResults_TitleTextCallback(s32 event, DemoGeoNode* node) {
    VsSceneSide* teams;

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        node->unk_24 = (u8*)teams[(s32)node->node.callbackArg].rosterInfo[0]->title;
    }
}

/**
 * Name text node callback: shows the side's name (rosterInfo[0]->fullName, 1P / ＣＯＭ in Free
 * Battle) on the win/lose panel and moves the text by the roster's flags: bit 0 sets unk_20 to
 * 210, bit 1 sets unk_22 to -240, otherwise unk_22 is -300.
 * Seen in play (2026-11-14): poking 1P's fullName to ＣＤ showed ＣＤ as the name.
 * @unverified: the offsets; setting COM's unk_000 to 1 or 2 moved nothing visible.
 */
void VsResults_NameTextCallback(s32 event, DemoGeoNode* node) {
    VsSceneSide* teams;

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        node->unk_24 = (u8*)teams[(s32)node->node.callbackArg].rosterInfo[0]->fullName;
        if (*(s16*)&teams[(s32)node->node.callbackArg].rosterInfo[0]->unk_000 & 1) {
            node->unk_20 = 210;
        } else if (*(s16*)&teams[(s32)node->node.callbackArg].rosterInfo[0]->unk_000 & 2) {
            node->unk_22 = -240;
        } else {
            node->unk_22 = -300;
        }
    }
}

/**
 * Nickname node callback (callbackArg = (side << 16) | slot): copies the slot's nickname from the
 * picked team (teamMember[0]) into sVsResultsNicknameText after a 9 prefix byte and shows it, or
 * nothing past the number brought. Both layouts use it.
 * Seen in play (2026-11-14): stubbing it left every label on the board showing the last nickname
 * copied (フデフデ).
 */
void VsResults_NicknameCallback(s32 event, DemoGeoNode* node) {
    VsSceneSide* teams;
    s32 team;
    s32 slot;

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        team = ((u32)node->node.callbackArg >> 16) & 0xFFFF;
        slot = (u32)node->node.callbackArg & 0xFFFF;
        if (slot < teams[team].teamMember[0]->numberOfPokemonBrought) {
            sVsResultsNicknameText[0] = 9;
            _bcopy(teams[team].teamMember[0]->pokemonPicked[slot].nickname, &sVsResultsNicknameText[1], 12);
            node->unk_24 = sVsResultsNicknameText;
        } else {
            node->unk_24 = NULL;
        }
    }
}

/**
 * Switch node callback: picks the board layout for side rootId, case 0 (a row of three) when
 * VsSceneSide.teamLayout is 0 and case 1 (a grid of six) otherwise.
 * Seen in play (2026-11-14): Free Battle sides have teamLayout 1 and showed the grid; poking both
 * to 0 showed one row of three per side.
 */
void VsResults_SelectLayout(s32 event, GeoModelRootNode* node) {
    VsSceneSide* teams;

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        node->unk_1A = teams[node->rootId].teamLayout != 0;
    }
}

/**
 * Writes a row-layout icon display list: segment 0x0F = the Pokémon's icon image, then a branch
 * to sVsResultsRowIconDL.
 */
Gfx* VsResults_WriteRowIconGfx(Gfx* gfx, void* icon_image) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(icon_image));
    gSPBranchList(gfx++, sVsResultsRowIconDL);
    return gfx;
}

/**
 * Icon node callback of the row layout (callbackArg = (side << 16) | slot): draws the slot's
 * Pokémon icon (VsSceneSide.iconImages), or nothing past the number brought.
 * Seen in play (2026-11-14): with both sides' teamLayout poked to 0 it ran every frame with event
 * 2 for the row of three; it does not draw in the Free Battle grid.
 */
void VsResults_RowIconCallback(s32 event, DemoGeoNode *node)
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
    if (slot < teams[team].teamMember[0]->numberOfPokemonBrought)
    {
      node->displayList = Gfx_AllocDisplayList(0x10);
      VsResults_WriteRowIconGfx(node->displayList, teams[team].iconImages[slot]);
    }
    else
    {
      node->displayList = 0;
      if (node) // karodo
      {
      }
    }
  }
}

/**
 * Writes a grid-layout icon display list: segment 0x0F = the Pokémon's icon image, then a branch
 * to sVsResultsGridIconDL.
 */
Gfx* VsResults_WriteGridIconGfx(Gfx* gfx, void* icon_image) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(icon_image));
    gSPBranchList(gfx++, sVsResultsGridIconDL);
    return gfx;
}

/**
 * Icon node callback of the grid layout (callbackArg = (side << 16) | slot): draws the slot's
 * Pokémon icon (VsSceneSide.iconImages), or nothing past the number brought. A two-trainer side
 * (teamLayout 2) gives slots 0-2 to teamMember[0] and 3-5 to teamMember[1].
 * Seen in play (2026-11-14): swapping 1P's iconImages[0] with another slot's moved that icon to
 * the first slot of the board.
 * @unverified: the two-trainer branch (Free Battle sides have teamLayout 1).
 */
void VsResults_GridIconCallback(s32 event, DemoGeoNode* node) {
    s32 pad0; // FAKE: stack padding
    VsSceneSide* teams;
    s32 team;
    s32 slot;
    s32 pad1[2]; // FAKE: stack padding

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        team = ((u32)node->node.callbackArg >> 16) & 0xFFFF;
        slot = (u32)node->node.callbackArg & 0xFFFF;
        if (teams[team].teamLayout == 2) {
            if (slot % 3 < teams[team].teamMember[slot / 3]->numberOfPokemonBrought) {
                node->displayList = Gfx_AllocDisplayList(0x10);
                VsResults_WriteGridIconGfx(node->displayList, teams[team].iconImages[slot]);
            } else {
                node->displayList = NULL;
            }
        } else if (slot < teams[team].teamMember[0]->numberOfPokemonBrought) {
            node->displayList = Gfx_AllocDisplayList(0x10);
            VsResults_WriteGridIconGfx(node->displayList, teams[team].iconImages[slot]);
        } else {
            node->displayList = NULL;
        }
    }
}

/**
 * Writes an HP bar display list: segment 0x0F = the slot's HP bar image, then a branch to
 * sVsResultsHpBarDL.
 */
Gfx* VsResults_WriteHpBarGfx(Gfx* gfx, void* hp_bar_image) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(hp_bar_image));
    gSPBranchList(gfx++, sVsResultsHpBarDL);
    return gfx;
}

/**
 * HP bar node callback (callbackArg = (side << 16) | slot): draws the slot's HP bar image
 * (VsSceneSide.hpBarImages, which VsScene_DrawHpBars draws into), or nothing past the number
 * brought, with the same two-trainer split as VsResults_GridIconCallback. Both layouts use it.
 * Seen in play (2026-11-14): swapping 1P's hpBarImages[0] and [1] moved the low red bar from
 * slot 0 to slot 1.
 * @unverified: the two-trainer branch (Free Battle sides have teamLayout 1).
 */
void VsResults_HpBarCallback(s32 event, DemoGeoNode* node) {
    s32 pad0; // FAKE: stack padding
    VsSceneSide* teams;
    s32 team;
    s32 slot;
    s32 pad1[2]; // FAKE: stack padding

    if (event == 2) {
        teams = D_80060490->node.callbackArg;
        team = ((u32)node->node.callbackArg >> 16) & 0xFFFF;
        slot = (u32)node->node.callbackArg & 0xFFFF;
        if (teams[team].teamLayout == 2) {
            if (slot % 3 < teams[team].teamMember[slot / 3]->numberOfPokemonBrought) {
                node->displayList = Gfx_AllocDisplayList(0x10);
                VsResults_WriteHpBarGfx(node->displayList, teams[team].hpBarImages[slot]);
            } else {
                node->displayList = NULL;
            }
        } else if (slot < teams[team].teamMember[0]->numberOfPokemonBrought) {
            node->displayList = Gfx_AllocDisplayList(0x10);
            VsResults_WriteHpBarGfx(node->displayList, teams[team].hpBarImages[slot]);
        } else {
            node->displayList = NULL;
        }
    }
}
