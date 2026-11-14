/* Stadium Zero fragment005_15FCE0. */
/* C ported from the Stadium 1 decomp: src/fragments/battle_order_select/battle_order_select.c. */

#include "battle_order_select.h"
#include "asset_archive.h"
#include "audio_music.h"
#include "font.h"
#include "fragments/pikachu_reward/pikachu_reward.h"
#include "fragments/vs_scene/vs_scene.h"
#include "gb_data.h"
#include "gb_save.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "graphics_textures.h"
#include "input.h"
#include "memory_main.h"
#include "ui_graphics.h"
#include "m2c_macros.h"
extern OrderSidebarIcons D_82302B20[2];
extern u16 D_82302800[];

void BattleMenu_AppendOrderSlotIcon(s32 arg0, s32 arg1);
void BattleMenu_ResetOrderSlotIcons(s32 arg0);
void BattleMenu_DrawPanelBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
s32 BattleMenu_IsSlotAlreadySelected(OrderSelectPanel* arg0, s8 arg1);
void BattleMenu_HandleOrderSelectPanel_LevelCapNoticeInput(Controller* arg0, OrderSelectPanel* arg1);
void BattleMenu_SetLeadTagTeamMember(BattleSide* arg0, OrderSidebarIcons* arg1);
void BattleMenu_AppendUnpickedSlots(s8* arg0, s32 arg1);

extern void* D_84803784;
extern char** D_84803790;
void func_8001CC90(s32, s32, s32, s32, s32);
extern char D_82302A08[];
extern char D_82302A0C[];
extern char D_82302A10[];
extern char D_82302A20[];

/**
 * Draws the instructions for the L and R button at the bottom of the screen
 * (L) Button to cancel
 * (R) Button to check
 * Seen in play: runs every frame on the order screen of a モンスターボールカップ round, which shows 「＊L
 * ボタンでもどる ＊R ボタンでかくにん」 along the bottom.
 */
void BattleMenu_DrawBottomActionButtons(void) {
    func_8001CC90(0, 0x1E0, 0xAB, 0x49, 0x66);

    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(0x71, 0x1A8, 0x20, 0x18, D_3002220, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x162, 0x1A8, 0x20, 0x18, D_3002820, 0x20, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    Font_BeginTranslucentTextRendering();
    Font_SetActive(8, 0);
    Font_Printf(0x5A, 0x1AA, D_82302A08);
    Font_Printf(0x149, 0x1AA, D_82302A0C);
    Font_Printf(0x91, 0x1A8, D_82302A10);
    Font_Printf(0x180, 0x1A8, D_82302A20);
    Font_EndTexturedTextRendering();
}

extern Color_RGB8 D_823028C4;
extern Color_RGB8 D_823028C8;
extern SessionContext* D_82302BD0;
extern s16* D_82302808[];
extern s16 D_82302B42;
/**
 * Draws the tall gradient panel on the right of the order screen and scrolls its vertical
 * instruction text (「どのポケモンを えらぶかは…」) inside a scissor box.
 * Seen in play: runs every frame while that text scrolls down the right edge.
 */
void BattleMenu_DrawScrollingInstructionPanel(void) {
    s32 i;
    s32 var_s2;
    s32 var_s4;
    s32 idx;
    GfxImage* sp4C;
    Color_RGB8 sp48;
    Color_RGB8 sp44;

    idx = D_82302BD0->ruleCategory == 0;
    var_s4 = 0x30 - (D_82302B42 % 24);
    var_s2 = D_82302B42 / 24;
    sp4C = StageContext_GetCurrentImage();
    sp48 = D_823028C4;
    sp44 = D_823028C8;
    Ui_DrawGradientPanel(0x228, 0x20, 0x2E, 0x186, &sp48, &sp44);

    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 563, 48, 587, 408);

    Font_BeginTranslucentTextRendering();
    Font_SetActive(0x10, 0);
    Gfx_SetEnvColor(0xA5, 0xDE, 0x8C, 0xFF);

    for (i = 0; i < 16; i++) {
        Font_DrawCharAt(0x233, var_s4, D_82302808[idx][var_s2]);
        var_s2 += 1;
        if (var_s2 >= 0x35) {
            var_s2 = 0;
        }
        var_s4 += 0x18;
    }
    Font_EndTexturedTextRendering();

    gDPSetScissorFrac(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, sp4C->width * 4.0f, sp4C->height * 4.0f);

    D_82302B42 += 1;
    if (D_82302B42 >= 0x4F8) {
        D_82302B42 = 0;
    }
}

void func_823003B8(OrderSidebarIcons* sidebar, BattleSide* side, s32 ruleCategory) {
    s32 i;

    sidebar->iconCount = 0;
    sidebar->isCom = 0;
    for (i = 0; i < 6; i++) {
        sidebar->slotIcons[i] = 0;
        sidebar->slotIconGrowth[i] = 1;
    }
    if (ruleCategory != 0) {
        i = 3;
        do {
            sidebar->slotIcons[i] = -1;
            i++;
        } while (i < 6);
    }
    if (side->tagTeamSize == 1) {
        sidebar->firstPort = side->teamMember[0]->controllerPort;
        sidebar->secondPort = -1;
        sidebar->isCom = (side->teamMember[0]->isHuman & 2) != 0;
    } else if (side->teamMember[0]->controllerPort < side->teamMember[1]->controllerPort) {
        sidebar->firstPort = side->teamMember[0]->controllerPort;
        sidebar->secondPort = side->teamMember[1]->controllerPort;
    } else {
        sidebar->firstPort = side->teamMember[1]->controllerPort;
        sidebar->secondPort = side->teamMember[0]->controllerPort;
    }
}

extern u8* D_84803698[];
extern u8* D_84803690[];
extern u8* D_84803684[];
extern u8* D_8480369C[][3];
extern u8 D_03008880[];
extern u8* D_823028CC[];
extern u8* D_823028D8[];
extern u8* D_823028E0[];
extern u8* D_823028E4[][3];
/** Draws the lead Pokemon icon in the battle order sidebar. */
void BattleMenu_DrawSidebarLeadIcon(s32 x, s32 y, OrderSidebarIcons* sidebar) {
    u8* sp2C;

    if (sidebar->secondPort == -1) {
        if (sidebar->isCom != 0) {
            Gfx_DrawTextureRgba16(x, y, 0x24, 0x1A, D_03008880, 0x24, 0x200000);
        } else {
            Gfx_DrawTextureRgba16(x, y, 0x24, 0x1A, D_823028CC[sidebar->firstPort], 0x24, 0x200000);
        }
    } else {
        switch (sidebar->firstPort) {
            case 0:
                sp2C = D_823028D8[sidebar->secondPort];
                break;

            case 1:
                sp2C = D_823028E0[sidebar->secondPort];
                break;

            case 2:
                sp2C = D_823028E4[0][sidebar->secondPort];
                break;
        }
        Gfx_DrawTextureRgba16(x, y, 0x24, 0x2D, sp2C, 0x24, 0x200000);
    }
}

extern u8* D_823028E4[][3];

/** Draws a row's type icon in the battle order sidebar. */
s32 BattleMenu_DrawSidebarRowTypeIcon(s32 x, s32 y, s8 icon, s8 growth) {
    s32 sp34;
    s32 sp30;

    if (icon != 0) {
        if (icon == -1) {
            Gfx_DrawTextureRgba16(x, y, 0x20, 0x14, D_3005680, 0x20, 0x200000);
        } else {
            sp34 = (icon >> 4) & 0xF;
            sp30 = icon & 0xF;

            if (growth > 0) {
                if (sp30 < 3) {
                    sp30++;
                }
            } else if (sp30 > 0) {
                sp30--;
            }

            if (sp30 > 0) {
                Gfx_DrawTextureRgba16(x + 6, y, 0x18, 0x14, D_823028E4[sp34][sp30], 0x18, 0x200000);
                icon = (sp34 * 0x10) | sp30;
            } else {
                icon = 0;
            }
        }
    }
    return icon;
}

/**
 * Draws side 0's order sidebar and advances its selection icons.
 * Seen in play: runs every frame on the order screen (the 1P column of ball icons on the left).
 */
void BattleMenu_DrawTeamOrderSidebarTeam0(void) {
    OrderSidebarIcons* temp_v0 = &D_82302B20[0];
    s32 i;
    s16 var_s2;
    s32 var_s1;

    if (temp_v0->secondPort == -1) {
        var_s2 = 0x3F;
    } else {
        var_s2 = 0x4A;
    }

    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(0x2D, var_s2, 0x20, 0xC, D_3003C80, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x2D, var_s2 + 0xC, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x2D, var_s2 + 0x23, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x2D, var_s2 + 0x3A, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x2D, var_s2 + 0x51, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x25, var_s2 + 0x68, 0x28, 0x2E, D_3002E20, 0x28, 0x200000);

    if (temp_v0->secondPort == -1) {
        BattleMenu_DrawSidebarLeadIcon(0x2D, 0x21, &D_82302B20[0]);
    } else {
        BattleMenu_DrawSidebarLeadIcon(0x2D, 0x1D, &D_82302B20[0]);
    }

    var_s1 = var_s2 + 0x76;
    for (i = 0; i < 6; i++) {
        temp_v0->slotIcons[i] = BattleMenu_DrawSidebarRowTypeIcon(0x2D, var_s1 - i * 0x17, temp_v0->slotIcons[i], temp_v0->slotIconGrowth[i]);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/**
 * Draws side 1's order sidebar and advances its selection icons.
 * Seen in play: runs every frame on the order screen (the COM column of ball icons on the left).
 */
void BattleMenu_DrawTeamOrderSidebarTeam1(void) {
    OrderSidebarIcons* temp_v0 = &D_82302B20[1];
    s32 i;
    s16 var_s2;
    s32 var_s1;

    if (temp_v0->secondPort == -1) {
        var_s2 = 0xF1;
    } else {
        var_s2 = 0xE6;
    }

    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(0x2D, var_s2, 0x28, 0x2C, D_3003F80, 0x28, 0x200000);
    Gfx_DrawTextureRgba16(0x2D, var_s2 + 0x2C, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x2D, var_s2 + 0x43, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x2D, var_s2 + 0x5A, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x2D, var_s2 + 0x71, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawTextureRgba16(0x2D, var_s2 + 0x88, 0x20, 0xE, D_3004D40, 0x20, 0x200000);

    if (temp_v0->secondPort == -1) {
        BattleMenu_DrawSidebarLeadIcon(0x2D, 0x189, &D_82302B20[1]);
    } else {
        BattleMenu_DrawSidebarLeadIcon(0x2D, 0x17C, &D_82302B20[1]);
    }

    var_s1 = var_s2 + 0xC;
    for (i = 0; i < 6; i++) {
        temp_v0->slotIcons[i] = BattleMenu_DrawSidebarRowTypeIcon(0x2D, var_s1 + i * 0x17, temp_v0->slotIcons[i], temp_v0->slotIconGrowth[i]);
    }

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);
}

/**
 * Appends a growing selection icon owned by the given controller port.
 * Seen in play: runs on each pick (B, C buttons, A) on the order screen.
 */
void BattleMenu_AppendOrderSlotIcon(s32 sidebarTeam, s32 controllerPort) {
    OrderSidebarIcons* temp_v0 = &D_82302B20[sidebarTeam];

    temp_v0->slotIcons[temp_v0->iconCount] = ((controllerPort + 1) << 4) | (temp_v0->slotIcons[temp_v0->iconCount] & 0xF);
    temp_v0->slotIconGrowth[temp_v0->iconCount] = 1;
    temp_v0->iconCount++;
}

/**
 * Starts shrinking all selection icons and clears the side's pick count.
 * Seen in play: runs when L cancels the picks on the order screen.
 */
void BattleMenu_ResetOrderSlotIcons(s32 sidebarTeam) {
    OrderSidebarIcons* ptr = &D_82302B20[sidebarTeam];
    s32 i;

    for (i = 0; i < 6; i++) {
        ptr->slotIconGrowth[i] = -1;
    }
    ptr->iconCount = 0;
}

/**
 * Draws a panel using the border color assigned to its controller port.
 * Seen in play (2026-11-13) ran every frame on the Free Battle order screen, drawing the 1P panel
 * in blue and the COM panel in green.
 */
void BattleMenu_DrawPanelBorder(s16 x, s16 y, s16 width, s16 height, s16 controllerPort) {
    Ui_DrawBorderedPanelStyleB(x, y, width, height, D_82302800[controllerPort]);
}

extern u8 D_03000000[];
extern u8 D_030005B0[];
extern u8 D_03001110[];
extern u8 D_03001C70[];
extern u8 D_03000B60[];
extern u8 D_030016C0[];
void func_8001D148(s32 x, s32 y, s32 width, s32 height, s32 r, s32 g, s32 b);
s32 PokeIcon_GetImage(s8 *arg0, s32 arg1);
extern char D_82302A34[];
extern s32 D_82302BCC;
/**
 * Battle order select: draws the brought Pokemon grid with their levels (L%d).
 * Seen in play: runs every frame on the order screen, which shows each side's six Pokemon with
 * L20/L25.
 */
void BattleMenu_DrawOrderSelectPartyGrid(OrderSelectPanel* panel) {
    s32 i;
    s16 x;
    s16 y;
    s32 tx;
    s32 ty;
    s32 sel;

    x = panel->x;
    y = panel->y;

    BattleMenu_DrawPanelBorder(x, y, 0x1D7, 0x5E, panel->controllerPort);

    gSPDisplayList(gDisplayListHead++, D_80060290);

    Gfx_DrawTextureRgba16(x + 7, y + 0xB, 0x1A, 0x1A, D_030005B0, 0x1C, 0x200000);
    Gfx_DrawTextureRgba16(x + 0xA1, y + 0xB, 0x1A, 0x1A, D_03001110, 0x1C, 0x200000);
    Gfx_DrawTextureRgba16(x + 0x13B, y + 0xB, 0x1A, 0x1A, D_03001C70, 0x1C, 0x200000);
    Gfx_DrawTextureRgba16(x + 7, y + 0x35, 0x1A, 0x1A, D_03000000, 0x1C, 0x200000);
    Gfx_DrawTextureRgba16(x + 0xA1, y + 0x35, 0x1A, 0x1A, D_03000B60, 0x1C, 0x200000);
    Gfx_DrawTextureRgba16(x + 0x13B, y + 0x35, 0x1A, 0x1A, D_030016C0, 0x1C, 0x200000);

    Gfx_DrawTextureRgba16(x + 0x23, y + 6, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_82302BCC, panel->panelIndex), 0x28, 0x200000);
    Gfx_DrawTextureRgba16(x + 0xBD, y + 6, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_82302BCC, panel->panelIndex + 4), 0x28, 0x200000);
    Gfx_DrawTextureRgba16(x + 0x157, y + 6, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_82302BCC, panel->panelIndex + 8), 0x28, 0x200000);
    Gfx_DrawTextureRgba16(x + 0x23, y + 0x30, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_82302BCC, panel->panelIndex + 0xC), 0x28, 0x200000);
    Gfx_DrawTextureRgba16(x + 0xBD, y + 0x30, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_82302BCC, panel->panelIndex + 0x10), 0x28, 0x200000);
    Gfx_DrawTextureRgba16(x + 0x157, y + 0x30, 0x28, 0x28, (u8*)PokeIcon_GetImage((s8*)D_82302BCC, panel->panelIndex + 0x14), 0x28, 0x200000);

    gSPDisplayList(gDisplayListHead++, gUiRestoreTextureDL);

    Font_BeginTranslucentTextRendering();
    Font_SetActive(4, 0);

    for (i = 0; i < panel->candidateCount; i++) {
        sel = BattleMenu_IsSlotAlreadySelected(panel, i);
        if ((panel->showingSummary != 0) && (sel != 0)) {
            Gfx_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
        }
        tx = x + ((i % 3) * 0x9A) + 0x4C;
        ty = y + ((i / 3) * 0x2A) + 8;
        Font_Printf(tx, ty, (char*)panel->candidates[i].nickname);
        if ((panel->showingSummary != 0) && (sel != 0)) {
            Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        }
        Font_Printf(tx, ty + 0x14, D_82302A34, panel->candidates[i].level);
    }

    Font_EndTexturedTextRendering();

    if (panel->unk_07 > 0) {
        if (panel->sidebarTeam == 0) {
            func_8001D148(0xC8, 0x81, 0x15F, 0x53, 0xAB, 0x49, 0x66);
        } else {
            func_8001D148(0x50, 0xF0, 0x15F, 0x53, 0xAB, 0x49, 0x66);
        }
        panel->unk_07 -= 1;
    }
}

extern char D_82302A38[];
extern char D_82302A4C[];
extern char D_82302A60[];
extern char D_82302A74[];
extern char D_82302A7C[];
void BattleMenu_DrawOrderSelectPartyGrid(OrderSelectPanel*);
void Ui_DrawPrimColorRect(s32, s32, s32, s32, s32, s32, s32, s32);
/**
 * Battle order select: これで いいですか？ (Is this OK?) with はい (Yes) / えらびなおす (Choose again).
 * Seen in play: after the sixth pick, 「これで いいですか？ はい えらびなおす」 appears in 1P's panel as this starts
 * running.
 */
void BattleMenu_DrawOrderSelectConfirmPrompt(OrderSelectPanel* panel) {
    s32 x;
    s32 y;

    if (panel->partnerPanelIndex == -1) {
        if (panel->sidebarTeam == 0) {
            x = 0xC8;
            y = 0x81;
        } else {
            x = 0x50;
            y = 0xF0;
        }
        BattleMenu_DrawOrderSelectPartyGrid(panel);
        BattleMenu_DrawPanelBorder(x, y, 0x15F, 0x53, panel->controllerPort);
        if (panel->confirmCursor == 0) {
            Ui_DrawTextureMarker(x + 0x26, y + 0x30);
        } else {
            Ui_DrawTextureMarker(x + 0x86, y + 0x30);
        }
        Font_BeginTranslucentTextRendering();
        Font_SetActive(0x10, 0);
        Font_Printf(x + 0x1F, y + 0xB, D_82302A38);
        Font_Printf(x + 0x4F, y + 0x30, D_82302A4C);
        Font_EndTexturedTextRendering();
        panel->unk_07 = 2;
    } else {
        x = panel->x;
        y = panel->y;
        BattleMenu_DrawOrderSelectPartyGrid(panel);
        Ui_DrawPrimColorRect(x + 5, y + 5, 0x1CD, 0x54, 0, 0, 0, 0x80);
        if (panel->confirmCursor == 0) {
            Ui_DrawTextureMarker(x + 0x5C, y + 0x3C);
        } else {
            Ui_DrawTextureMarker(x + 0xBC, y + 0x3C);
        }
        Font_BeginTranslucentTextRendering();
        Font_SetActive(0x10, 0);
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Font_Printf(x + 0x50, y + 0x14, D_82302A60);
        Font_Printf(x + 0x80, y + 0x3C, D_82302A74);
        Font_Printf(x + 0xE0, y + 0x3C, D_82302A7C);
        Font_EndTexturedTextRendering();
    }
}

extern char D_82302A8C[];
extern char D_82302AA0[];
extern char D_82302AB8[];
extern char D_82302ACC[];


/**
 * Battle order select: レベルの ごうけいが 155を こえてしまいます (The level total goes over 155).
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment guessed from the code.
 */
void BattleMenu_DrawLevelSumOverNotice(OrderSelectPanel* panel) {
    s32 x;
    s32 y;

    if (panel->partnerPanelIndex == -1) {
        if (panel->sidebarTeam == 0) {
            x = 0xC8;
            y = 0x81;
        } else {
            x = 0x50;
            y = 0xF0;
        }
        BattleMenu_DrawPanelBorder(x, y, 0x15F, 0x53, panel->controllerPort);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(0x10, 0);
        Gfx_SetEnvColor(0xFF, 0x63, 0x63, 0xFF);
        Font_Printf(x + 0x10, y + 0xB, D_82302A8C);
        Font_Printf(x + 0x10, y + 0x30, D_82302AA0);
        Font_EndTexturedTextRendering();
        panel->unk_07 = 2;
    } else {
        x = panel->x;
        y = panel->y;
        BattleMenu_DrawOrderSelectPartyGrid(panel);
        Ui_DrawPrimColorRect(x + 5, y + 5, 0x1CD, 0x54, 0, 0, 0, 0x80);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(0x10, 0);
        Gfx_SetEnvColor(0xFF, 0x63, 0x63, 0xFF);
        Font_Printf(x + 0x50, y + 0x14, D_82302AB8);
        Font_Printf(x + 0x50, y + 0x3C, D_82302ACC);
        Font_EndTexturedTextRendering();
    }
}

extern char** D_84803790;
extern char D_82302AE4[];
extern char D_82302AFC[];
/**
 * Draws the ready message, pulsing its text alpha for tag-team panels.
 * Seen in play: runs every frame while the COM panel shows 「じゅんび かんりょう！」.
 */
void BattleMenu_DrawOrderSelectPanel_Ready(OrderSelectPanel* panel) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;

    if (panel->partnerPanelIndex == -1) {
        // clang-format off
        if (panel->sidebarTeam == 0) {
            sp3C = 0xC8; sp38 = 0x81;
        } else {
            sp3C = 0x50; sp38 = 0xF0;
        }
        // clang-format on
        panel->unk_07 = 0;
        BattleMenu_DrawOrderSelectPartyGrid(panel);
        BattleMenu_DrawPanelBorder(sp3C, sp38, 0x15F, 0x53, panel->controllerPort);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(0x20, -4);
        Font_EnableTwoCycleTexturing();
        Gfx_SetPrimColor(0x1C, 0x74, 0xFF, 0xFF);
        Font_Printf(sp3C + 0x14, sp38 + 0x19, D_82302AE4);
        Font_DisableTwoCycleTexturing();
        Font_EndTexturedTextRendering();
    } else {
        sp3C = panel->x;
        sp38 = panel->y;

        if (panel->readyBlinkTimer < 0x10) {
            sp34 = panel->readyBlinkTimer * 0x10;
        } else if (panel->readyBlinkTimer < 0x23) {
            sp34 = 0xFF;
        } else if (panel->readyBlinkTimer < 0x32) {
            sp34 = (-panel->readyBlinkTimer * 0x10) + 0x320;
        } else {
            sp34 = 0;
        }

        panel->readyBlinkTimer++;
        if (panel->readyBlinkTimer >= 0x3D) {
            panel->readyBlinkTimer = 0;
        }

        BattleMenu_DrawOrderSelectPartyGrid(panel);
        Ui_DrawPrimColorRect(sp3C + 5, sp38 + 5, 0x1CD, 0x54, 0, 0, 0, 0x80);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(0x20, 0);
        Font_EnableTwoCycleTexturing();
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, sp34);
        Gfx_SetPrimColor(0x1C, 0x74, 0xFF, sp34);
        Font_Printf(sp3C + 0x39, sp38 + 0x25, D_82302AFC);
        Font_DisableTwoCycleTexturing();
        Font_EndTexturedTextRendering();
    }
}

/** Draws the label of the confirm button. */
void BattleMenu_DrawConfirmButtonLabel(OrderSelectPanel* panel) {
    s16 sp26;
    s16 sp24;

    if (panel->sidebarTeam == 0) {
        // clang-format off
        sp26 = 0x50; sp24 = 0x81;
        // clang-format on
    } else {
        sp26 = 0x1B1;
        sp24 = 0x123;
    }

    BattleMenu_DrawPanelBorder(sp26, sp24, 0x76, 0x20, panel->controllerPort);
    Font_BeginTranslucentTextRendering();
    Font_SetActive(8, 0);
    Font_Printf(sp26 + 9, sp24 + 5, panel->roster->trainerName);
    Font_EndTexturedTextRendering();
}

extern s16 D_82302B40;
void BattleMenu_DrawOrderSelectConfirmPrompt(OrderSelectPanel*);
void BattleMenu_DrawOrderSelectPanel_Ready(OrderSelectPanel*);
/**
 * Draws the current panel mode when needed and updates its redraw countdown.
 * Seen in play (2026-11-13) ran every frame on the Free Battle order screen, which shows the 1P and
 * COM panels with their six Pokémon each.
 */
void BattleMenu_DrawOrderSelectPanel(OrderSelectPanel* panel) {
    if ((D_82302B40 != 0) || (panel->redrawFrames != 0)) {
        if ((D_82302B40 != 0) && (panel->partnerPanelIndex == -1)) {
            BattleMenu_DrawConfirmButtonLabel(panel);
        }

        switch (panel->state) {
            case 0:
                BattleMenu_DrawOrderSelectPartyGrid(panel);
                break;

            case 1:
                BattleMenu_DrawOrderSelectConfirmPrompt(panel);
                break;

            case 2:
                BattleMenu_DrawLevelSumOverNotice(panel);
                break;

            case 3:
                BattleMenu_DrawOrderSelectPanel_Ready(panel);
                break;
        }

        if (panel->redrawFrames != 0) {
            panel->redrawFrames--;
        }
    } else if (panel->state == 3) {
        BattleMenu_DrawOrderSelectPanel_Ready(panel);
    }
}

extern s32 D_84816450;
extern Controller D_84816428;
extern unk_D_84803548* D_848035E0[];
extern OrderSelectPanel D_848037A0[4];
extern SessionContext* D_84816420;
extern s32 D_8481644C;
extern OrderSelectPanel D_82302B48[];
extern SessionContext* D_82302BD0;
extern Controller D_82302BD8;
extern s32 D_82302BFC;
extern s32 D_82302C00;
extern unk_D_84803548* D_823028A8[];

/**
 * When side 1 is locked (isHuman & 2, the COM), feeds it scripted button presses from D_823028A8,
 * one entry per countdown, so the COM picks its order like a player.
 * Seen in play: runs every frame on the order screen against the COM, whose panel shows 「じゅんび
 * かんりょう！」.
 * Seen in play (2026-11-12) on the order screen of a COM free battle: ran each frame for the COM
 * side, whose panel showed じゅんび かんりょう！ (ready) without any input.
 */
void BattleMenu_FeedScriptedComOrderInput(void) {
    s32 var_v0;
    unk_D_84803548* ptr;

    if (D_82302B48[1].roster->isHuman & 2) {
        if (D_82302BD0->ruleCategory != 0) {
            var_v0 = 3;
        } else {
            var_v0 = D_82302B48[1].candidateCount;
            if (D_82302B48[0].candidateCount < var_v0) {
                var_v0 = D_82302B48[0].candidateCount;
            }
        }
        D_82302BD8.buttonPressed = 0;
        if (D_82302C00 == 0) {
            ptr = D_823028A8[var_v0];

            D_82302C00 = ptr[D_82302BFC].unk_00;
            if (D_82302C00 != 0) {
                D_82302BD8.buttonPressed = ptr[D_82302BFC].unk_02;
                D_82302BFC++;
            }
        }

        if (D_82302C00 > 0) {
            D_82302C00--;
        }
    }
}

/**
 * Tests whether a roster slot already occurs in the panel's picked order.
 * Seen in play (2026-11-12) on the order screen of a COM free battle: returned 1 for slots 0 and
 * 1 of COM's finished order.
 */
s32 BattleMenu_IsSlotAlreadySelected(OrderSelectPanel* panel, s8 slot) {
    s32 i;
    s8 temp_v1;
    OrderSelectPanel* var_a2;

    for (i = 0; i < panel->pickCount; i++) {
        if (slot == panel->pickedSlots[i]) {
            return 1;
        }
    }

    return 0;
}

/**
 * Returns 1 when the picks so far break the level-sum rule (ruleCategory 1 only, not for a locked
 * side): two picks summing to 106 or more, or three summing to 156 or more. The caller then shows
 * the 155 level-total notice.
 * Seen in play: runs on every pick on the order screen (Free Battle, rule 0, so it never fires).
 * Seen in play (2026-11-13) on the Free Battle order screen it ran after each 1P pick (pick counts
 * 0, 1, 2) and returned 0; Free Battle has no level-sum rule.
 */
s32 BattleMenu_OrderExceedsLevelSumLimit(OrderSelectPanel* panel) {
    s32 sum;
    s32 i;
    s32 locked = (panel->roster->isHuman & 2) != 0;

    if ((D_82302BD0->ruleCategory == 1) && !locked) {
        sum = 0;
        for (i = 0; i < panel->pickCount; i++) {
            sum += panel->candidates[panel->pickedSlots[i]].level;
        }
        if ((panel->pickCount == 2) && (sum >= 0x6A)) {
            return 1;
        }
        if ((panel->pickCount == 3) && (sum >= 0x9C)) {
            return 1;
        }
    }
    return 0;
}

/**
 * Returns whether the panel has picked enough Pokemon: 3 under cup rules, otherwise the party
 * size (capped by the partner's for a locked side, and at 3 for a tag-team panel). When it does,
 * the panel switches to the confirm prompt.
 * Seen in play: runs on every pick; the sixth Free Battle pick opened 「これで いいですか？」.
 */
s32 BattleMenu_IsOrderComplete(OrderSelectPanel* panel) {
    s32 var_v1;

    if (D_82302BD0->ruleCategory != 0) {
        var_v1 = 3;
    } else if (panel->roster->isHuman & 2) {
        var_v1 = panel->candidateCount;
        if (D_82302B48[0].candidateCount < var_v1) {
            var_v1 = D_82302B48[0].candidateCount;
        }
    } else {
        var_v1 = panel->candidateCount;
        if ((panel->partnerPanelIndex != -1) && (var_v1 >= 4)) {
            var_v1 = 3;
        }
    }

    return panel->pickCount >= var_v1;
}

s32 BattleMenu_OrderExceedsLevelSumLimit(OrderSelectPanel* arg0);
s32 BattleMenu_IsOrderComplete(OrderSelectPanel* arg0);
/**
 * Opens a slot's details or adds it to the picked order and checks the result.
 * Seen in play (2026-11-12) on the order screen of a COM free battle: B added slot 0 (イワワ) to
 * 1P's order and C-Left added slot 1 (パルパル); each call checked
 * BattleMenu_OrderExceedsLevelSumLimit, which returned 0.
 */
void BattleMenu_SelectSlotOrShowSummary(OrderSelectPanel* panel, s8 slot) {
    if (slot >= panel->candidateCount) {
        Audio_PlaySoundEffectById(SFX_MENU_ERROR);
        return;
    }

    if (BattleMenu_IsSlotAlreadySelected(panel, slot) != 0) {
        Audio_PlaySoundEffectById(SFX_MENU_ERROR);
        return;
    }

    panel->pickedSlots[panel->pickCount] = slot;
    panel->pickCount++;
    BattleMenu_AppendOrderSlotIcon(panel->sidebarTeam, panel->controllerPort);

    if (panel->showingSummary != 0) {
        panel->redrawFrames = 2;
    }

    if (BattleMenu_OrderExceedsLevelSumLimit(panel) != 0) {
        Audio_PlaySoundEffectById(SFX_MENU_ERROR);
        panel->state = 2;
        panel->redrawFrames = 2;
        return;
    }

    Audio_PlaySoundEffectById(SFX_MENU_CONFIRM);
    if (BattleMenu_IsOrderComplete(panel) != 0) {
        panel->state = 1;
        panel->confirmCursor = 0;
        panel->redrawFrames = 2;
    }
}

extern OrderSelectPanel D_82302B48[];
/**
 * Clears a nonempty panel's picks, resetting the partner panel when present.
 * Seen in play (2026-11-12) on the order screen of a COM free battle: L cleared 1P's picks after
 * two had been made; the pick markers emptied.
 */
void BattleMenu_UndoSelections(OrderSelectPanel* panel) {
    s8 temp_v1;
    OrderSelectPanel* temp_v0;

    if (panel->pickCount > 0) {
        panel->pickCount = 0;
        BattleMenu_ResetOrderSlotIcons(panel->sidebarTeam);
        if (panel->showingSummary != 0) {
            panel->redrawFrames = 2;
        }
        Audio_PlaySoundEffectById(SFX_MENU_BACK);
        temp_v1 = panel->partnerPanelIndex;
        if (temp_v1 != -1) {
            temp_v0 = (OrderSelectPanel*)((temp_v1 << 5) + (s8*)D_82302B48);
            temp_v0->state = 0;
            temp_v0->pickCount = 0;
            temp_v0->showingSummary = 0;
            temp_v0->redrawFrames = 2;
        }
    }
}

void BattleMenu_SelectSlotOrShowSummary(OrderSelectPanel*, s8);

/**
 * Maps slot buttons to picking or checking Pokemon and handles L-cancel.
 * Seen in play: runs every frame while 1P is still picking.
 */
void BattleMenu_HandleOrderSelectPanel_PartyInput(Controller* cont, OrderSelectPanel* panel) {
    if (BTN_IS_PRESSED(cont, BTN_R)) {
        // clang-format off
        panel->showingSummary = 1; panel->redrawFrames = 2;
        // clang-format on
    }

    if (cont->buttonReleased & 0x10) {
        panel->showingSummary = 0;
        panel->redrawFrames = 2;
    }

    if (BTN_IS_PRESSED(cont, BTN_L)) {
        BattleMenu_UndoSelections(panel);
    } else if (BTN_IS_PRESSED(cont, BTN_B)) {
        BattleMenu_SelectSlotOrShowSummary(panel, 0);
    } else if (BTN_IS_PRESSED(cont, BTN_CLEFT)) {
        BattleMenu_SelectSlotOrShowSummary(panel, 1);
    } else if (BTN_IS_PRESSED(cont, BTN_CUP)) {
        BattleMenu_SelectSlotOrShowSummary(panel, 2);
    } else if (BTN_IS_PRESSED(cont, BTN_A)) {
        BattleMenu_SelectSlotOrShowSummary(panel, 3);
    } else if (BTN_IS_PRESSED(cont, BTN_CDOWN)) {
        BattleMenu_SelectSlotOrShowSummary(panel, 4);
    } else if (BTN_IS_PRESSED(cont, BTN_CRIGHT)) {
        BattleMenu_SelectSlotOrShowSummary(panel, 5);
    }
}

extern OrderSelectPanel D_848037A0[4];
/**
 * Handles confirmation choices, accepting the order or restarting selection.
 * Seen in play: starts running when the sixth pick opens the confirm prompt.
 */
void BattleMenu_HandleOrderSelectPanel_ConfirmInput(Controller* cont, OrderSelectPanel* panel) {
    OrderSelectPanel* temp_v0_2;

    if (BTN_IS_PRESSED(cont, BTN_R)) {
        panel->showingSummary = 1;
        panel->redrawFrames = 2;
    }
    if (cont->buttonReleased & 0x10) {
        panel->showingSummary = 0;
        panel->redrawFrames = 2;
    }

    if (BTN_IS_PRESSED(cont, BTN_DLEFT | BTN_DRIGHT)) {
        panel->redrawFrames = 2;
        panel->confirmCursor ^= 1;
        Audio_PlaySoundEffectById(SFX_MENU_SCROLL);
    } else if (BTN_IS_PRESSED(cont, BTN_A)) {
        if (panel->confirmCursor == 0) {
            panel->redrawFrames = 2;
            panel->state = 3;
            panel->readyBlinkTimer = 0;
            Audio_PlaySoundEffectById(9);
        } else {
            panel->redrawFrames = 2;
            panel->state = 0;
            panel->pickCount = 0;
            panel->showingSummary = 0;
            BattleMenu_ResetOrderSlotIcons(panel->sidebarTeam);
            Audio_PlaySoundEffectById(SFX_MENU_BACK);
            if (panel->partnerPanelIndex != -1) {
                temp_v0_2 = &D_82302B48[panel->partnerPanelIndex];
                temp_v0_2->state = 0;
                temp_v0_2->pickCount = 0;
                temp_v0_2->showingSummary = 0;
                temp_v0_2->redrawFrames = 2;
            }
        }
    }
}

/**
 * Dismisses the level-limit warning and clears this panel's picks.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleMenu_HandleOrderSelectPanel_LevelCapNoticeInput(Controller* cont, OrderSelectPanel* panel) {
    if (BTN_IS_PRESSED(cont, BTN_A | BTN_B)) {
        panel->state = 0;
        panel->pickCount = 0;
        panel->showingSummary = 0;
        panel->redrawFrames = 2;
        BattleMenu_ResetOrderSlotIcons(panel->sidebarTeam);
        Audio_PlaySoundEffectById(SFX_MENU_BACK);
    }
}

extern Controller D_84816428;
extern Controller D_82302BD8;
/**
 * Dispatches panel input while enabled and reports whether the panel is ready.
 * Seen in play (2026-11-12) on the order screen of a COM free battle: returned 0 for 1P's panel
 * before any pick and 1 for COM's panel, which was already ready.
 */
s32 BattleMenu_UpdateOrderSelectPanel(s32 fadeMode, OrderSelectPanel* panel) {
    Controller* var_a0;
    s32 sp18 = 0;

    if (panel->roster->isHuman & 2) {
        var_a0 = &D_82302BD8;
    } else {
        var_a0 = &gControllers[panel->controllerPort];
    }

    if (fadeMode == 0) {
        switch (panel->state) {
            case 0:
                BattleMenu_HandleOrderSelectPanel_PartyInput(var_a0, panel);
                break;

            case 1:
                BattleMenu_HandleOrderSelectPanel_ConfirmInput(var_a0, panel);
                break;

            case 2:
                BattleMenu_HandleOrderSelectPanel_LevelCapNoticeInput(var_a0, panel);
                break;

            case 3:
                sp18 = 1;
                break;
        }
    }
    return sp18;
}

extern s32 D_8480379C;
extern s16 D_84803798;
extern OrderSelectPanel D_848037A0[4];
extern s32 D_82302BCC;
void BattleMenu_FeedScriptedComOrderInput(void);
extern s16 D_82302B40;
extern s32 D_82302B44;
void BattleMenu_DrawScrollingInstructionPanel(void);
/**
 * Runs the order select screen (both sides pick their three Pokemon) for one frame.
 * Seen in play (2026-11-13) ran every frame on the Free Battle order screen (じゅんばんを きめてください, 1P and
 * COM panels).
 */
s32 BattleMenu_UpdateOrderSelect(s32 fadeMode) {
    UNUSED s32 pad; // FAKE: stack padding
    s32 i;
    s32 var_s2;
    s32 sp30;

    var_s2 = 0;
    sp30 = 0;

    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
    BattleMenu_FeedScriptedComOrderInput();
    GeoRender_AdvanceFrameCounter();
    i = PokeIcon_ProcessAllSlots((PokeIconRenderer*)D_82302BCC, 0);
    if (i != -1) {
        (D_82302B48)[i % 4].redrawFrames = 3;
    }
    BgStage_DrawFrame();

    if (D_82302B40 != 0) {
        BattleMenu_DrawBottomActionButtons();
    }

    for (i = 0; i < D_82302B44; i++) {
        var_s2 += BattleMenu_UpdateOrderSelectPanel(fadeMode, &(D_82302B48)[i]);
        BattleMenu_DrawOrderSelectPanel(&(D_82302B48)[i]);
    }

    BattleMenu_DrawTeamOrderSidebarTeam0();
    BattleMenu_DrawTeamOrderSidebarTeam1();
    BattleMenu_DrawScrollingInstructionPanel();

    if (fadeMode == 0) {
        if (var_s2 == D_82302B44) {
            sp30 = 1;
            Audio_StopMusic(0x1E);
            Audio_PlayCommand(0x54, 0, 0);
        }

        if (D_82302B40 > 0) {
            D_82302B40 -= 1;
        }
    } else {
        D_82302B40 = 2;
    }
    return sp30;
}

/**
 * Moves the trainer owning the first selection into the lead tag-team position.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment from Stadium 1.
 */
void BattleMenu_SetLeadTagTeamMember(BattleSide* side, OrderSidebarIcons* sidebar) {
    TeamRoster* temp_v0;
    s32 tmp;

    if (side->tagTeamSize == 2) {
        tmp = ((sidebar->slotIcons[0] >> 4) & 0xF) - 1;
        if (tmp == side->teamMember[1]->controllerPort) {
            temp_v0 = side->teamMember[0];
            side->teamMember[0] = side->teamMember[1];
            side->teamMember[1] = temp_v0;
        }
    }
}

/**
 * Appends the unpicked roster slots in ascending order to fill six entries.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name and comment from Stadium 1.
 */
void BattleMenu_AppendUnpickedSlots(s8* order, s32 count) {
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++) {
        for (j = 0; j < count; j++) {
            if (i == order[j]) {
                break;
            }
        }

        if (j == count) {
            order[count] = i;
            count += 1;
        }
    }
}

extern s32 D_82302B44;
extern SessionContext* D_82302BD0;

// Zero's order-select slot keeps only the first 0x20 bytes of Stadium 1's OrderSelectPanel.
/**
 * Copies final orders into battle rosters and sets each tag team's lead trainer.
 * COM rosters keep their original order rather than using the scripted panel picks.
 * Seen in play (2026-11-12) on the order screen of a COM free battle: ran when はい was chosen at
 * 「これで いいですか？」 after all six picks, then the battle started in that order.
 */
void BattleMenu_CommitOrderSelection(void) {
    s32 i;
    s32 var_s4;
    TeamRoster* temp_s1;
    OrderSelectPanel* var_s2;

    var_s2 = (OrderSelectPanel*)D_82302B48;
    var_s4 = D_82302B44;

    while (var_s4-- > 0) {
        temp_s1 = var_s2->roster;
        if (temp_s1->isHuman & 2) {
            temp_s1->numberOfPokemonBrought = temp_s1->rosterInfo->numberOfPokemonCanBePicked;
            _bcopy(temp_s1->rosterInfo->battleMon, temp_s1->pokemonPicked, sizeof(temp_s1->pokemonPicked));
        } else {
            BattleMenu_AppendUnpickedSlots(var_s2->pickedSlots, var_s2->pickCount);
            temp_s1->numberOfPokemonBrought = var_s2->pickCount;

            for (i = 0; i < temp_s1->rosterInfo->numberOfPokemonCanBePicked; i++) {
                temp_s1->pokemonPicked[i] = var_s2->candidates[var_s2->pickedSlots[i]];
            }
        }
        var_s2++;
    }

    BattleMenu_SetLeadTagTeamMember(&D_82302BD0->battleSides[0], &D_82302B20[0]);
    BattleMenu_SetLeadTagTeamMember(&D_82302BD0->battleSides[1], &D_82302B20[1]);
}


/**
 * Initializes one trainer's panel and loads its roster icons.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleMenu_AddOrderSelectPanel(s16 x, s16 y, TeamRoster* roster, s32 sidebarTeam, s32 partnerPanelIndex) {
    s32 i;
    OrderSelectPanel* temp_v1;
    s32 j;

    j = D_82302B44;
    temp_v1 = &(D_82302B48)[D_82302B44];
    temp_v1->panelIndex = D_82302B44;
    temp_v1->controllerPort = roster->controllerPort;
    temp_v1->partnerPanelIndex = partnerPanelIndex;
    temp_v1->sidebarTeam = sidebarTeam;
    temp_v1->state = 0;
    temp_v1->pickCount = 0;
    temp_v1->redrawFrames = 2;
    temp_v1->unk_07 = 0;
    temp_v1->showingSummary = 0;
    temp_v1->confirmCursor = 0;
    temp_v1->x = x;
    temp_v1->y = y;
    temp_v1->candidateCount = roster->rosterInfo->numberOfPokemonCanBePicked;
    temp_v1->candidates = roster->rosterInfo->battleMon;
    temp_v1->roster = roster;

    for (i = 0; i < roster->rosterInfo->numberOfPokemonCanBePicked; i++, j += 4) {
        Pokemon_PrepareBattleMon(&roster->rosterInfo->battleMon[i]);
        func_8001833C((PokeIconRenderer*)D_82302BCC, j, &roster->rosterInfo->battleMon[i], D_82302800[roster->controllerPort]);
    }

    D_82302B44++;
}

extern s32 D_82302BFC;
extern s16 D_82302B42;
extern s16 D_82302B40;
extern s32 D_82302C00;
extern Controller D_82302BD8;
/**
 * Resets selection state and creates controller-ordered panels for both sides.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
void BattleMenu_InitOrderSelectPanels(SessionContext* session) {
    BattleSide* temp_s0 = &session->battleSides[0];

    D_82302BD0 = session;
    D_82302B44 = 0;
    D_82302B40 = 2;
    D_82302B42 = 0;
    D_82302BFC = 0;
    D_82302C00 = 0;
    D_82302BD8.buttonPressed = 0;

    BattleMenu_InitTeamOrderState(&D_82302B20[0], &D_82302BD0->battleSides[0], D_82302BD0->ruleCategory);
    BattleMenu_InitTeamOrderState(&D_82302B20[1], &D_82302BD0->battleSides[1], D_82302BD0->ruleCategory);

    if (temp_s0->tagTeamSize == 1) {
        BattleMenu_AddOrderSelectPanel(0x50, 0x21, temp_s0->teamMember[0], 0, -1);
    } else if (temp_s0->teamMember[0]->controllerPort < temp_s0->teamMember[1]->controllerPort) {
        BattleMenu_AddOrderSelectPanel(0x50, 0x21, temp_s0->teamMember[0], 0, D_82302B44 + 1);
        BattleMenu_AddOrderSelectPanel(0x50, 0x81, temp_s0->teamMember[1], 0, D_82302B44 - 1);
    } else {
        BattleMenu_AddOrderSelectPanel(0x50, 0x21, temp_s0->teamMember[1], 0, D_82302B44 + 1);
        BattleMenu_AddOrderSelectPanel(0x50, 0x81, temp_s0->teamMember[0], 0, D_82302B44 - 1);
    }

    temp_s0++;
    if (temp_s0->tagTeamSize == 1) {
        BattleMenu_AddOrderSelectPanel(0x50, 0x146, temp_s0->teamMember[0], 1, -1);
    } else if (temp_s0->teamMember[0]->controllerPort < temp_s0->teamMember[1]->controllerPort) {
        BattleMenu_AddOrderSelectPanel(0x50, 0xE6, temp_s0->teamMember[0], 1, D_82302B44 + 1);
        BattleMenu_AddOrderSelectPanel(0x50, 0x146, temp_s0->teamMember[1], 1, D_82302B44 - 1);
    } else {
        BattleMenu_AddOrderSelectPanel(0x50, 0xE6, temp_s0->teamMember[1], 1, D_82302B44 + 1);
        BattleMenu_AddOrderSelectPanel(0x50, 0x146, temp_s0->teamMember[0], 1, D_82302B44 - 1);
    }
}

extern char** D_8480378C;
extern char** D_84803788;
extern void* D_84803784;
extern char** D_84803790;
extern BinArchive* D_84803780;
extern char** D_84803794;
extern s8* D_82302BC8;
extern s32 D_82302BCC;
extern u8 D_81000000[];
extern u8 D_01000000[];
extern u8 D_02000000[];
extern u8 D_03000000[];
extern u8 D_030005B0[];
extern u8 D_03001110[];
extern u8 D_03001C70[];
extern u8 D_03000B60[];
extern u8 D_030016C0[];
extern u8 D_0015B1A0[];
extern u8 D_0015E220[];
extern u8 D_002E0BE0[];
extern u8 D_002E2B90[];
extern u8 D_002F0A50[];
extern u8 D_002F3BD0[];
extern u8 D_003D64A0[];
extern u8 D_003DCB60[];
s8 *PokeIcon_AllocFramebuffers(s32 arg0);
s32 func_80017FDC(s8*, s32, s32, s32);
s32 Font_Init(s32 load_size, s32 side);
void PokeIcon_OpenModelArchives(void);

/**
 * Loads selection resources, runs the screen through its fades, and commits the orders.
 * Not reached in play (2026-11-13): did not run in a tour of the main menu, Pokédex, party, Lab,
 * registration, Free Battle setup and a COM battle (opening, a switch, running, a Pound turn).
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
s32 BattleMenu_RunOrderSelectScreen(s32 arg0, s32 session) {
    StageContext* sp24;

    main_pool_push_state('MSEL');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = StageContext_Allocate(1, 1, 2, 0, 2, 1);
    D_82302BC8 = PokeIcon_AllocFramebuffers(1);
    D_82302BCC = func_80017FDC(D_82302BC8, 0x18, 0x28, 0x28);
    Font_Init(0x3C, 0);
    PokeIcon_OpenModelArchives();

    Fragment_Load(((((u32)D_81000000) & 0x0FF00000) >> 0x14) - 0x10, D_0015B1A0, D_0015E220);
    Asset_LoadToSegment(((u32)D_01000000 & 0x0F000000) >> 0x18, D_002E0BE0, D_002E2B90, 0);
    Asset_LoadToSegment(((u32)D_02000000 & 0x0F000000) >> 0x18, D_002F0A50, D_002F3BD0, 0);
    Asset_LoadToSegment(((u32)D_03000000 & 0x0F000000) >> 0x18, D_003D64A0, D_003DCB60, 0);

    BattleMenu_InitOrderSelectPanels((SessionContext*)session);
    Audio_PlayMusicIfChanged(7);
    StageContext_Activate(sp24);
    BgStage_WaitForCondition((s32(*)(u8))BattleMenu_UpdateOrderSelect, 0x10, 0x10);
    StageContext_Deactivate();
    BattleMenu_CommitOrderSelection();
    Font_Free();
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('MSEL');
    return 0;
}
