/* Stadium Zero fragment014_235D70. */
/* C ported from the Stadium 1 decomp: src/fragments/lab_pc/lab_pc_1B4EA0.c, src/fragments/lab_pc_icons/lab_pc_icons.c. */

#include "main_menu.h"
#include "font.h"
#include "fragments/party_summary/party_summary.h"
#include "graphics_textures.h"
#include "pokemon_stats.h"
#include "stage_loader.h"

typedef struct unk_D_88218060 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Color_RGBA8* unk_04;
} unk_D_88218060;
typedef struct unk_D_88218070 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ Color_RGBA8* unk_10;
} unk_D_88218070;

#include "m2c_macros.h"

void func_8800075C(void);
void func_88000FE0(void);

extern Color_RGBA8 D_88001FD0;
void Ui_FillRectHighlighted(s32, s32, s32, s32, Color_RGBA8);
void Font_SetColorForFlags(s32);

/**
 * Menu draw callback for one row of the continue-tournament prompt: the highlight bar when
 * `flags` bit 3 is set, then the row text.
 * Seen in play (2026-11-14): with the continue flag poked on, it drew つづきをする (Continue),
 * つづきをしない (Don't continue) and つづきのデータをけす (Erase the continue data), index 0 first.
 */
void MainMenu_DrawMenuRow(s32 x, s32 y, char* text, s32 index, s32 flags) {
    if (flags & 8) {
        Ui_FillRectHighlighted(x + 3, y + 3, 354, 30, D_88001FD0);
    }
    Font_BeginTranslucentTextRendering();
    Font_SetColorForFlags(flags);
    Font_SetActive(0x10, 0);
    Font_Printf(x + 12, y + 6, text);
    Font_EndTexturedTextRendering();
}

void Window_SetRect(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
M2C_UNK func_80027804();
M2C_UNK Menu_Init();
extern s8 D_88001FD4[];
extern u8 D_88001FE0[];
extern u8 D_88001FE4[];
/**
 * Sets up the continue-tournament prompt (372x274) and its three-row menu.
 * Seen in play (2026-11-14): runs from MainMenu_InitScreen at (130, 110) when
 * gSessionContext.sessionFlags bit 0 (poked on in the emulator) says a tournament is in progress.
 */
M2C_UNK MainMenu_InitPromptWindow(MainMenuPromptWindow* prompt, s32 x, s32 y) {
    MainMenuPromptWindow* obj = prompt;
    s32 pad; // FAKE: stack padding

    Window_SetRect(obj, x, y, 372, 274);
    obj->window.animTimer = 0;
    obj->window.title = 0;
    obj->window.state = 0;
    obj->window.frame.style = 0x1001;
    Window_SetRect(&obj->textFrame, obj->window.frame.x + 6, obj->window.frame.y + 6, obj->window.frame.width - 12, 136);
    obj->textFrame.style = 6;
    obj->textFrame.color = *(Color_RGBA8 *)D_88001FE0;
    obj->textFrame.color2 = *(Color_RGBA8 *)D_88001FE4;
    func_80027804(&obj->itemList, D_88001FD4, 3, 3);
    Menu_Init(&obj->menu, &obj->itemList, obj->itemFlags, MainMenu_DrawMenuRow, 360, 36);
    obj->menu.options |= 0x10000;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
extern u8 D_8007356C[];
extern Gfx D_80060270[];
extern Color_RGBA8 D_88001FE8;
extern char D_88002308[];
extern char D_88002328[];
void Ui_DrawTexturedDivider(s32, s32, s32, u8 *);
void func_80029028(s32, s32, s32, s32, Color_RGBA8);
void Window_DrawFrame(void*);
void Menu_DrawItems(s8 *, s32, s32, s32, s32);
/**
 * Draws トーナメントのつづきをする？ (Continue the tournament?) with its note
 * 「たいせんちゅうに ゲームを やめると 1かいせんから やりなおしに なります！」 (If you quit
 * during a battle, you start over from round 1!) and the three choices.
 * Seen in play (2026-11-14) with the continue flag poked on: the prompt drew over the main menu.
 */
void MainMenu_DrawContinueTournamentPrompt(MainMenuPromptWindow* prompt) {
    if (func_8002AE6C() == 0) {
        Window_DrawFrame(&prompt->textFrame);
        Ui_DrawTexturedDivider(prompt->window.frame.x, prompt->window.frame.y + 141, prompt->window.frame.width, D_8007356C);
        gSPDisplayList(gDisplayListHead++, D_80060270);
        func_80029028(prompt->window.frame.x + 6, prompt->window.frame.y + 148, prompt->window.frame.width - 12, 120, D_88001FE8);
        Font_BeginTranslucentTextRendering();
        Font_SetActive(0x10, 0);
        Gfx_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF); // #FFFFFF
        Font_EnableTwoCycleTexturing();
        Gfx_SetPrimColor(0xFF, 0x96, 0x96, 0xFF); // #FF9696
        Font_Printf(prompt->textFrame.x + 12, prompt->textFrame.y + 12, D_88002308);
        Font_DisableTwoCycleTexturing();
        Font_SetActive(8, 0);
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetLineHeight(28);
        Font_Printf(prompt->textFrame.x + 52, prompt->textFrame.y + 48, D_88002328);
        Font_EndTexturedTextRendering();
        Menu_DrawItems(&prompt->menu, prompt->window.frame.x + 6, prompt->window.frame.y + 154, 0xFFEF, 0);
    }
}

s32 Menu_UpdateCursor(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;

/**
 * Moves the prompt cursor while the window is open. Returns the 1-based choice on confirm, otherwise 0.
 * Seen in play (2026-11-14): A on choice 1 made MainMenu_UpdateScreen return 0x8050 and load the
 * tournament fragment (id 0x12); choices 2 and 3 went back to the item grid and cleared the flag.
 */
s32 MainMenu_UpdatePromptCursor(MainMenuPromptWindow* prompt) {
    s32 ret = 0;

    switch (prompt->window.state) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (Menu_UpdateCursor(&prompt->menu) == 0) {
        if (func_8002BC14(D_800603C0) == 1) {
            ret = prompt->menu.cursor + 1;
        }
    }
    return ret;
}

extern Gfx D_80073450[];
void func_8001B884(s32, s32, s32, s32, u8*, s32, s32);
/**
 * Draws an IA image at (x, y) in strips with primitive alpha `alpha`.
 * Seen in play (2026-11-12) on the main menu: it drew the 96 x 64 item pictures at x 89
 * (せいとん column) and 455 (いちらん column).
 */
void MainMenu_DrawImageWithAlpha(s32 x, s32 y, s32 width, s32 height, s32 stride, u8* pixels, s32 alpha) {
    s32 rows;
    s32 n;
    s32 max_rows;
    s32 cur_y;
    u8* pix;

    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, alpha); // #FFFFFF
    rows = height;
    pix = pixels;
    cur_y = y;
    if (rows > 0) {
        max_rows = 0x1000 / (stride * 2);
        do {
            if (max_rows < rows) {
                n = max_rows;
            } else {
                n = rows;
            }
            func_8001B884(x, cur_y, width, n, pix, stride, 0);
            rows -= n;
            cur_y += n;
            pix += n * stride * 2;
        } while (rows > 0);
    }
}

/**
 * Empty stub.
 * @unverified No caller found in this fragment's C.
 */
void func_8800075C(void) {
}

extern Gfx D_80073450[];
void Ui_DrawTexturedFrame(s32, s32, s32, s32, u8*);
/**
 * Appends a call of display list D_80073450, a gDPSetCombineMode(G_CC_MODULATEIA_PRIM,
 * G_CC_MODULATEIA_PRIM) and a white primitive color with alpha `alpha` to the current display
 * list, then forwards its first five arguments unchanged to Ui_DrawTexturedFrame (compare
 * Ui_DrawTexturedFrameDecal, which does the same with a decal combiner and no primitive color).
 * Seen in play (2026-11-14): a breakpoint bound to this fragment hit for each item panel's frame
 * (first call x 79, y 78, 116 x 112, the せいとん panel).
 */
void MainMenu_DrawTexturedFrameWithAlpha(s32 x, s32 y, s32 width, s32 height, u8* texture, s32 alpha) {
    gSPDisplayList(gDisplayListHead++, D_80073450);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, alpha); // #FFFFFF
    Ui_DrawTexturedFrame(x, y, width, height, texture);
}

extern u8 D_88002034[][0x18];
/* A main menu item's frame. */
typedef struct MainMenuRect { s32 x; s32 y; s32 w; s32 h; } MainMenuRect;
/* A main menu item's label: x, y offset in the frame, an argument of func_8001A384 and the text (none when NULL). */
typedef struct MainMenuLabel { s32 x; s32 y; s32 unk_08; char* text; } MainMenuLabel;
extern Color_RGBA8 D_88002010[];
extern MainMenuRect D_8800210C[];
extern MainMenuLabel D_8800219C[];
extern Gfx D_80073480[];
extern Color_RGBA8 D_80073520;
extern u8 D_80073554[];
void Ui_FillRectPrimColor(s32, s32, s32, s32, Color_RGBA8);
void Ui_DrawRoundedFrame(s32, s32, s32, s32, Color_RGBA8);
void func_8001AB6C(void);
void func_8001AA9C(u8, u8, u8, u8);
void func_8001A384(s32, s32);
void Font_Printf(s32 x, s32 y, const char* fmt, ...);
void func_8001ABBC(void);

// D_88002034 is declared as raw bytes in this file; each 0x18 byte row is one MainMenuImage.
#define ICON(i) (((MainMenuImage*)D_88002034)[i])

/**
 * GridMenu draw callback for main menu item `index` (0-8; slot 1 is empty and draws nothing): its
 * picture, frame and label, faded by `*opacity` (capped at 0.3 when `flags` bit 0 marks it
 * disabled), plus the cursor frame when `flags` bit 1 is set.
 * Seen in play (2026-11-14): runs every frame for the item panels; first call index 0 (せいとん).
 */
void MainMenu_DrawItem(s32 x, s32 y, s32 item, s32 index, s32 flags, f32* opacity) {
    Color_RGBA8 frame_color;
    Color_RGBA8 text_color;
    f32 fade;
    f32 value;
    s32 alpha;

    value = *opacity;
    // the fade is capped at 0.3 when bit 0 is set
    if ((flags & 1) && (value > 0.3f)) {
        fade = 0.3f;
    } else {
        fade = value;
    }
    if (index == 1) {
        return;
    }
    alpha = (s32)(fade * 255.0f);
    MainMenu_DrawImageWithAlpha(D_8800210C[index].x + ICON(index).x, D_8800210C[index].y + ICON(index).y, ICON(index).width, ICON(index).height,
                  ICON(index).stride, ICON(index).pixels, alpha);
    frame_color = D_88002010[index];
    frame_color.a = alpha;
    if (D_8800219C[index].text) {
        gSPDisplayList(gDisplayListHead++, D_80073480);
        Ui_FillRectPrimColor(D_8800210C[index].x + 6, D_8800210C[index].y + 6, D_8800210C[index].w - 12, 4, frame_color);
        Ui_FillRectPrimColor(D_8800210C[index].x + 6, D_8800210C[index].y + 6, 4, D_8800219C[index].y - 10, frame_color);
        Ui_FillRectPrimColor(D_8800210C[index].x + D_8800210C[index].w - 10, D_8800210C[index].y + 6, 4, D_8800219C[index].y - 10, frame_color);
        Ui_FillRectPrimColor(D_8800210C[index].x + 6, D_8800210C[index].y + D_8800219C[index].y - 4, D_8800210C[index].w - 12, 0x20, frame_color);
    } else {
        gSPDisplayList(gDisplayListHead++, D_80073480);
        Ui_FillRectPrimColor(D_8800210C[index].x + 6, D_8800210C[index].y + 6, D_8800210C[index].w - 12, 8, frame_color);
        Ui_FillRectPrimColor(D_8800210C[index].x + 6, D_8800210C[index].y + D_8800210C[index].h - 14, D_8800210C[index].w - 12, 8, frame_color);
        Ui_FillRectPrimColor(D_8800210C[index].x + 6, D_8800210C[index].y + 14, 9, D_8800210C[index].h - 28, frame_color);
        Ui_FillRectPrimColor(D_8800210C[index].x + D_8800210C[index].w - 15, D_8800210C[index].y + 14, 9, D_8800210C[index].h - 28, frame_color);
    }
    MainMenu_DrawTexturedFrameWithAlpha(D_8800210C[index].x, D_8800210C[index].y, D_8800210C[index].w, D_8800210C[index].h, D_80073554, alpha);
    if (D_8800219C[index].text) {
        text_color = *(Color_RGBA8*)D_800734A8;
        text_color.a = alpha;
        func_8001AB6C();
        func_8001AA9C(text_color.r, text_color.g, text_color.b, text_color.a);
        func_8001A384(0x10, D_8800219C[index].unk_08);
        Font_Printf(D_8800210C[index].x + D_8800219C[index].x, D_8800210C[index].y + D_8800219C[index].y, D_8800219C[index].text);
        func_8001ABBC();
    }
    if (flags & 2) {
        Ui_DrawRoundedFrame(D_8800210C[index].x - 4, D_8800210C[index].y - 4, D_8800210C[index].w + 8, D_8800210C[index].h + 8, D_80073520);
    }
}

void func_80027410(void*, void*, s32, s32, s32);
void GridMenu_Init(void*, void*, void*, void*, s32, s32, s32);
s32 func_800226BC(s32, s32, s32);
s32 func_80025BD8();
void MainMenu_DrawItem();
/**
 * Sets up the main menu item grid with the cursor on `cursor` and disables (bit 0) the items
 * that `gb_save_status` (see MainMenu_LoadGbSaveSummary) does not allow.
 * Seen in play (2026-11-14): with a blank Green save (status 3) ずかん, てもち and とうろく drew grayed out.
 * Seen in play (2026-11-13) ran once each time the main menu came back from another screen, before
 * its eight items were drawn.
 */
M2C_UNK MainMenu_InitItemList(MainMenuItemList* item_list, s32 cursor, s32 gb_save_status) {
    item_list->fadeTimer = 0;
    func_80027410(&item_list->items, &item_list->itemBuffer, 0x30, 9, 9);
    GridMenu_Init(&item_list->menu, &item_list->items, item_list->itemFlags, MainMenu_DrawItem, 3, 0, 0);
    item_list->menu.cursor = cursor;
    item_list->menu.itemFlags[1] |= 1;
    switch (gb_save_status) {
        case 4:
            item_list->menu.itemFlags[0] |= 1;
            item_list->menu.itemFlags[2] |= 1;
            item_list->menu.itemFlags[3] |= 1;
            item_list->menu.itemFlags[5] |= 1;
            item_list->menu.itemFlags[6] |= 1;
            item_list->menu.itemFlags[8] |= 1;
            break;
        case 3:
            item_list->menu.itemFlags[0] |= 1;
            item_list->menu.itemFlags[2] |= 1;
            item_list->menu.itemFlags[3] |= 1;
            item_list->menu.itemFlags[5] |= 1;
            item_list->menu.itemFlags[8] |= 1;
            break;
        case 2:
            item_list->menu.itemFlags[0] |= 1;
            item_list->menu.itemFlags[2] |= 1;
            item_list->menu.itemFlags[3] |= 1;
            break;
        case 1:
            item_list->menu.itemFlags[0] |= 1;
            item_list->menu.itemFlags[2] |= 1;
            break;
    }
    if ((gb_save_status == 1 || gb_save_status == 2) && func_800226BC(0x20, func_80025BD8(), 0) == 0) {
        item_list->menu.itemFlags[5] |= 1;
    }
}

/**
 * Advances the item list fade timer and its state (fade in, shown, fade out, done).
 * Seen in play (2026-11-13) ran every frame on the main menu while the cursor moved between items.
 */
s32 MainMenu_StepItemFade(MainMenuItemList* item_list) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = item_list->fadeTimer;
    var_v1 = 1;
    if (temp_v0 >= 23) {
        item_list->fadeState = 4;
        return 1;
    }
    if (temp_v0 >= 13) {
        item_list->fadeState = 3;
        item_list->fadeTimer = (s32) (temp_v0 + 1);
    } else if (temp_v0 < 10) {
        item_list->fadeState = 0;
        item_list->fadeTimer = (s32) (temp_v0 + 1);
    } else {
        var_v1 = 0;
        if (temp_v0 < 12) {
            item_list->fadeState = 1;
            item_list->fadeTimer = (s32) (temp_v0 + 1);
        } else {
            item_list->fadeState = 2;
        }
    }
    return var_v1;
}

extern u8 D_05018868[];
void GridMenu_DrawInlineItems(void*, s32, s32, s32, f32*);

/**
 * Draws the main menu items with the current fade. `cursor_flags` (2) is OR'd into the item flags
 * mask once the fade-in is over, so the cursor frame shows; the prompt state passes 0.
 * Seen in play: runs every frame while the main menu's item panels (ずかん, バトル, てもち, GB, とうろく, OFF)
 * are drawn.
 */
s32 MainMenu_DrawItemList(MainMenuItemList* item_list, s32 cursor_flags) {
    f32 alpha;
    s32 ret = 1;
    s32 color = 0xFFED;
    s32 n;

    MainMenu_StepItemFade(item_list);
    switch (item_list->fadeState) {
        case 4:
            return 1;
        case 3:
            n = 23 - item_list->fadeTimer;
            alpha = (f32)n / 10.0f;
            break;
        case 0:
            n = item_list->fadeTimer - 1;
            alpha = (f32)n / 10.0f;
            break;
        case 1:
        case 2:
            ret = 0;
            alpha = 1.0f;
            color = cursor_flags | 0xFFED;
            break;
    }
    GridMenu_DrawInlineItems(&item_list->menu, 0, 0, color, &alpha);
    MainMenu_DrawImageWithAlpha(230, 86, 200, 100, 200, D_05018868, 255.0f * alpha);
    return ret;
}

/**
 * Empty stub.
 * @unverified No caller found in this fragment's C.
 */
void func_88000FE0(void) {
}

void Window_InitLabeled(s8* arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8 arg4, char* arg5);
M2C_UNK func_8000B2F4(s32);
extern u8 D_8800222C[];
extern char D_880023C0[];
extern char D_880023C8[];
/**
 * Sets up the message window (532x138) with its color and text.
 * Seen in play: A on バトル opens its window (「コンピュータや ともだちと たいせん する。 はいりますか？ はい いいえ」) and runs
 * this.
 */
void MainMenu_InitMessageWindow(MainMenuMessageWindow* window, s32 x, s32 y, s32 title, s32 text, s32 text2, Color_RGBA8 color, s32 image) {
    Window_SetRect(window, x, y, 532, 138);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 0x800;
    window->window.frame.color = color;
    window->window.title = title;
    window->text = text;
    window->text2 = text2;
    Window_InitLabeled(&window->yesButton, window->window.frame.x + 357, window->window.frame.y + 102, 72, *(Color_RGBA8 *)D_8800222C, D_880023C0);
    window->yesButton.labelX = 10;
    window->yesButton.unk_34 = 12;
    Window_InitLabeled(&window->noButton, window->window.frame.x + 442, window->window.frame.y + 102, 72, *(Color_RGBA8 *)D_8800222C, D_880023C8);
    window->choice.count = 2;
    window->choice.cursor = 0;
    window->choice.controller = (Controller*)D_800603C0;
    func_8000B2F4(D_800603C0);
    window->color = color;
    window->image = image;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
extern u8 D_8007356C[];
void Ui_DrawTexturedDivider(s32, s32, s32, u8 *);
void Window_DrawLabeled(s8 *, s32);
void MainMenu_DrawImageWithAlpha(s32, s32, s32, s32, s32, u8*, s32);
/**
 * Draws the message window: divider and text.
 * Seen in play: draws the item window opened by A (「…はいりますか？ はい いいえ」).
 */
void MainMenu_DrawMessageWindow(MainMenuMessageWindow* window) {
    MainMenuImage* p;

    if (func_8002AE6C() == 0) {
        Ui_DrawTexturedDivider(window->window.frame.x, window->window.frame.y + 89, window->window.frame.width, D_8007356C);
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(28);
        Font_Printf(window->window.frame.x + 138, window->window.frame.y + 10, window->text);
        Font_Printf(window->window.frame.x + 188, window->window.frame.y + 104, window->text2);
        Font_EndTexturedTextRendering();
        Window_DrawLabeled(&window->yesButton, (window->choice.cursor == 0) ? 2 : 0);
        Window_DrawLabeled(&window->noButton, (window->choice.cursor == 1) ? 2 : 0);
        p = window->image;
        MainMenu_DrawImageWithAlpha(window->window.frame.x + 10, window->window.frame.y + 10, p->width, p->height, p->stride, p->pixels, 0xFF);
    }
}

s32 func_8002B390(s8*);
s32 func_8002BC14(s32);
extern s32 D_800603C0;

/**
 * Handles input on the message window while it is open.
 * Seen in play: runs while that window is open; D-Right moves the cursor between はい and いいえ.
 */
s32 MainMenu_UpdateMessageWindow(MainMenuMessageWindow* window) {
    s32 ret = 0;

    switch (window->window.state) {
        case 1:
        case 2:
            break;
        default:
            return 0;
    }
    if (func_8002B390(&window->choice) == 0) {
        ret = func_8002BC14(D_800603C0);
        if (ret == 1) {
            switch (window->choice.cursor) {
                case 0:
                    ret = 1;
                    break;
                case 1:
                    ret = -1;
                    break;
            }
        }
    }
    return ret;
}

extern Color_RGBA8 D_88002230;
void Window_SetRect(s8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/**
 * Sets up the text window (MainMenuTextWindow; same family as FreeBattle_InitLevelSumWarning):
 * a 548x96 window with style 0x2800, fill color D_88002230, title `title` and text `text`.
 * Seen in play (2026-11-14): runs from MainMenu_InitScreen whenever the GB save status is above 0,
 * e.g. title ポケモンセンターにいない (Not at a Pokémon Center) for a save made outside one and
 * ＧＢのポケモンがいない (No GB Pokémon) for a blank save.
 */
void MainMenu_InitTextWindow(MainMenuTextWindow* window, s32 x, s32 y, s32 title, s32 text) {
    Window_SetRect(window, x, y, 548, 96);
    window->window.animTimer = 0;
    window->window.title = 0;
    window->window.state = 0;
    window->window.frame.style = 0x2800;
    window->window.frame.color = D_88002230;
    window->window.title = title;
    window->text = text;
}

s32 func_8002AE6C();
extern u8 D_800734A8[4];
/**
 * Draws the text window's text.
 * Seen in play: runs while the main menu shows the 「GBのカートリッジがない」 warning window at the top.
 */
void MainMenu_DrawTextWindow(MainMenuTextWindow* window) {
    if (func_8002AE6C() == 0) {
        Font_BeginTranslucentTextRendering();
        Gfx_SetEnvColor(D_800734A8[0], D_800734A8[1], D_800734A8[2], D_800734A8[3]);
        Font_SetActive(8, 0);
        Font_SetLineHeight(28);
        Font_Printf(window->window.frame.x + 10, window->window.frame.y + 10, window->text);
        Font_EndTexturedTextRendering();
    }
}

M2C_UNK MainMenu_InitPromptWindow(MainMenuPromptWindow*, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK MainMenu_InitItemList(MainMenuItemList*, s32, s32);            /* extern */
extern M2C_UNK D_88002240;

/**
 * Sets up the main menu screen: the continue-tournament prompt (state 1) when
 * gSessionContext.sessionFlags bit 0 says a tournament is in progress, otherwise the item grid
 * (state 2), plus the GB save warning window when `gb_save_status` is above 0.
 * The caller MainMenu_LoadGbSaveSummary passes a fourth argument, &D_88002B20, which this function
 * never reads. It is declared so that call compiles; the empty `if (unused_screen_ptr)` only stops
 * the compiler from spilling the unused argument, which the ROM does not do.
 * Seen in play (2026-11-13) ran once each time the main menu came back from another screen, after
 * MainMenu_LoadGbSaveSummary.
 */
void MainMenu_InitScreen(MainMenuScreen* screen, s32 gb_save_status, s32 cursor, MainMenuScreen** unused_screen_ptr) {
    s32 temp_v0;

    if (unused_screen_ptr) {  // karodo
    }

    if (gSessionContext.sessionFlags & 1) {
        MainMenu_InitPromptWindow(&screen->promptWindow, 130, 110);
        screen->state = 1;
    } else {
        screen->state = 2;
    }
    screen->nextState = 0;
    MainMenu_InitItemList(&screen->itemList, cursor, gb_save_status);
    screen->mode = gb_save_status;
    if (gb_save_status > 0) {
        temp_v0 = gb_save_status * 4;
        MainMenu_InitTextWindow(&screen->textWindow, 46, 83, *((M2C_UNK*)((u8*)&D_88002230 + temp_v0)), *((M2C_UNK*)((u8*)&D_88002240 + temp_v0))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    }
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
void MainMenu_DrawContinueTournamentPrompt(MainMenuPromptWindow*);
M2C_UNK MainMenu_DrawItemList(MainMenuItemList*, M2C_UNK);             /* extern */
void MainMenu_DrawMessageWindow(MainMenuMessageWindow*);
extern M2C_UNK D_88002254;

/**
 * Draws the main menu for its current state, including the continue-tournament prompt.
 * Seen in play: runs every frame on the メインメニュー screen.
 */
void MainMenu_DrawScreen(MainMenuScreen* screen) {
    s32 temp_v0;

    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(56, 480, M2C_FIELD(&D_88002254, u8 *, 0), M2C_FIELD(&D_88002254, u8 *, 1), (s32) M2C_FIELD(&D_88002254, u8 *, 2));
    temp_v0 = screen->state;
    switch (temp_v0) {                              /* irregular */
    case 1:
        MainMenu_DrawItemList(&screen->itemList, 0);
        MainMenu_DrawContinueTournamentPrompt(&screen->promptWindow);
        return;
    case 2:
        MainMenu_DrawItemList(&screen->itemList, 2);
        if (screen->mode > 0) {
            MainMenu_DrawTextWindow(&screen->textWindow);
            return;
        }
        return;
    case 3:
        MainMenu_DrawItemList(&screen->itemList, 2);
        MainMenu_DrawMessageWindow(&screen->messageWindow);
        break;
    }
}

extern s32 D_88002258[];
extern s32 D_8800227C[];
extern s32 D_880022A0[];
extern Color_RGBA8 D_88001FEC[];
extern u8 D_88002034[][0x18];
s32 GridMenu_UpdateCursorSkipDisabled(s8*);
void func_800245E0(s32, s32);
s32 MainMenu_LoadSelectedFragment(s32);
/**
 * Runs the main menu screen's state machine for one frame and returns the chosen item.
 * Seen in play (2026-11-13) ran every frame while the main menu was up and the cursor moved between
 * its items.
 */
s32 MainMenu_UpdateScreen(MainMenuScreen* screen) {
    s32 ret = 0;
    s32 idx;
    s32 dir;

    switch (screen->state) {
        case 1:
            if (screen->nextState == 4 && screen->itemList.fadeState == 4) {
                ret = screen->result;
            } else if (screen->nextState == 2 && screen->promptWindow.window.state == 4) {
                screen->state = screen->nextState;
                screen->nextState = 0;
            } else {
                switch (MainMenu_UpdatePromptCursor(&screen->promptWindow)) {
                    case 1:
                        Audio_PlaySystemSound(0x1E);
                        gSessionContext.sessionFlags |= 2;
                        screen->result = 0x8050;
                        screen->promptWindow.window.animTimer = 7;
                        screen->nextState = 4;
                        screen->itemList.fadeTimer = 13;
                        break;
                    case 2:
                        Audio_PlaySystemSound(3);
                        gSessionContext.sessionFlags &= ~1;
                        screen->promptWindow.window.animTimer = 7;
                        screen->nextState = 2;
                        break;
                    case 3:
                        Audio_PlaySystemSound(0x1F);
                        func_800245E0(0x15, 0);
                        gSessionContext.sessionFlags &= ~1;
                        screen->promptWindow.window.animTimer = 7;
                        screen->nextState = 2;
                        break;
                }
            }
            break;
        case 2:
            if (GridMenu_UpdateCursorSkipDisabled(&screen->itemList.menu) == 0) {
                dir = func_8002BC14(D_800603C0);
                if (dir == -1) {
                    Audio_PlaySystemSound(8);
                } else if (dir == 1) {
                    Audio_PlaySystemSound(2);
                    screen->state = 3;
                    idx = screen->itemList.menu.cursor;
                    MainMenu_InitMessageWindow(&screen->messageWindow, 54, 87, D_88002258[idx], D_8800227C[idx], D_880022A0[idx], D_88001FEC[idx], (s32)D_88002034[idx]);
                }
            }
            break;
        case 3:
            if (screen->nextState == 4 && screen->itemList.fadeState == 4) {
                ret = screen->result;
            } else if (screen->nextState == 2 && screen->messageWindow.window.state == 4) {
                screen->state = screen->nextState;
                screen->nextState = 0;
            } else {
                dir = MainMenu_UpdateMessageWindow(&screen->messageWindow);
                if (dir == -1) {
                    Audio_PlaySystemSound(3);
                    screen->messageWindow.window.animTimer = 7;
                    screen->nextState = 2;
                } else if (dir == 1) {
                    if (screen->itemList.menu.cursor == 7) {
                        Audio_PlaySystemSound(2);
                    } else {
                        Audio_PlaySystemSound(0x1C);
                    }
                    screen->result = MainMenu_LoadSelectedFragment(screen->itemList.menu.cursor);
                    screen->messageWindow.window.animTimer = 7;
                    screen->nextState = 4;
                    screen->itemList.fadeTimer = 13;
                }
            }
            break;
    }
    return ret;
}

s32 func_80002D98(M2C_UNK);
M2C_UNK func_8000B2F4(s32);
u8 GbSave_GetSaveState(s32 arg0);
s32 GbSave_HasPokedex(s32);
s32 func_80022EDC(s32);
s32 func_80025BD8();
M2C_UNK func_80027FF8(M2C_UNK *, s32);
extern s32 D_800603C0;
extern s32 D_80073400;
extern s32 D_88002B00;
extern M2C_UNK D_88002B08;
extern MainMenuScreen* D_88002B20;

/**
 * Allocates the 0x3B0-byte object stored in D_88002B20 and starts it with
 * MainMenu_InitScreen. Steps:
 *  1. port = GbSave_GetActivePort() (-1 when no Transfer Pak cartridge is chosen); D_88002B00 = port;
 *     if there is one, GbSave_BuildPortSummary fills D_88002B08 for the summary bar.
 *  2. Picks the GB save status: no port -> 4; GbSave_GetSaveState != 0 -> 3 (no GB Pokémon:
 *     blank or broken save); no Pokédex -> 2; not saved at a Pokémon Center -> 1; else 0.
 *  3. D_88002B20 = func_80002D98(0x3B0), then
 *     MainMenu_InitScreen(D_88002B20, status, D_80073400 == 0 ? 4 : D_80073400 - 1, &D_88002B20)
 *     and finally func_8000B2F4(D_800603C0). D_80073400 is the last cursor + 1 (MainMenu_Init
 *     stores it), so the menu reopens on the item last chosen, and on バトル (4) the first time.
 * pad1/pad2 are unused locals that reproduce the retail 0x30-byte frame.
 * Seen in play (2026-11-14) with crafted Green saves: status 0 (full save), 1 (saved outside a
 * Pokémon Center), 2 (no Pokédex) and 3 (blank save); status 4 was not reached, because without a
 * cartridge the game stops at the cartridge screen (fragment 0x74) and never loads the menu.
 * Seen in play (2026-11-13) ran once each time the main menu came back from another screen; the
 * menu then showed the GB save summary bar (1P サトシ IDNo/12345).
 */
void MainMenu_LoadGbSaveSummary(void) {
    s32 pad1; // FAKE: stack padding
    s32 pad2; // FAKE: stack padding
    s32 sp24;
    s32 var_s0;

    var_s0 = 0;
    sp24 = func_80025BD8();
    D_88002B00 = sp24;
    if (D_88002B00 != -1) {
        func_80027FF8(&D_88002B08, D_88002B00);
    }
    if (sp24 == -1) {
        var_s0 = 4;
    } else if (GbSave_GetSaveState(sp24) != 0) {
        var_s0 = 3;
    } else if (GbSave_HasPokedex(sp24) == 0) {
        var_s0 = 2;
    } else if (func_80022EDC(sp24) == 0) {
        var_s0 = 1;
    }
    D_88002B20 = (MainMenuScreen*)func_80002D98(sizeof(MainMenuScreen));
    MainMenu_InitScreen(D_88002B20, var_s0, (D_80073400 == 0) ? 4 : D_80073400 - 1, &D_88002B20);
    func_8000B2F4(D_800603C0);
}

/**
 * Returns `color` with its RGB scaled by `scale` (alpha kept).
 * Seen in play (2026-11-14): called by MainMenu_DrawFadeInBackground with color 0xC8C8C8FF.
 */
Color_RGBA8 MainMenu_ScaleColor(Color_RGBA8 color, f32 scale) {
    Color_RGBA8 scaled;

    scaled.r = (s32)(color.r * scale);
    scaled.g = (s32)(color.g * scale);
    scaled.b = (s32)(color.b * scale);
    scaled.a = color.a;
    return scaled;
}

M2C_UNK StageFade_Start(M2C_UNK);
extern s32 D_880022C4;
/**
 * Draws the background, brightening it a little more each call (20 frames on the first entry).
 * Seen in play (2026-11-14): the screen was black three frames into it, then the background rose.
 */
s32 MainMenu_DrawFadeInBackground(s32 fade_mode) {
    Color_RGBA8 sp24;

    if (fade_mode == 1) {
        /* Dead read of the counter; the retail code loads it here. */
        if (D_880022C4) {}  // karodo
        StageFade_Start(1);
    }
    BgStage_DrawFrame();
    sp24 = MainMenu_ScaleColor(*(Color_RGBA8*)&D_88002254, D_880022C4 / 20.0);
    Ui_DrawTintedScreenBackground(0, 480, sp24.r, sp24.g, sp24.b);
    D_880022C4++;
    return 0;
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_88002254;

/**
 * Draws the tinted main menu background (2 frames after the fade-in on the first entry).
 * Seen in play (2026-11-14): ran between MainMenu_DrawFadeInBackground and the summary bar slide-in.
 */
s32 MainMenu_DrawBackground(s32 fade_mode) {
    BgStage_DrawFrame();
    Ui_DrawTintedScreenBackground(0, 480, M2C_FIELD(&D_88002254, u8 *, 0), M2C_FIELD(&D_88002254, u8 *, 1), (s32) M2C_FIELD(&D_88002254, u8 *, 2));
    return 0;
}

M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
extern M2C_UNK D_88002A8C;

/**
 * Draws the GB save summary bar sliding in from the top (6 frames, y from -56 to 0).
 * Seen in play (2026-11-14): three frames in, the bar was still above the screen; once it ended,
 * the bar (1P シトシ IDNo/12345 メインメニュー) sat at the top.
 */
s32 MainMenu_DrawSummaryBarSlideIn(UNUSED s32 fade_mode) {
    static s32 D_880022C8;
    s32 sp1C;
    M2C_UNK *var_a1;

    sp1C = ((D_880022C8 * 56) / 6) - 56;
    BgStage_DrawFrame();
    if (D_88002B00 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88002B08;
    }
    GbSave_DrawSummaryBar(sp1C, var_a1, &D_88002A8C, D_88002B00);
    D_880022C8++;
    return 0;
}

void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
extern M2C_UNK D_88002A9C;
extern s32 D_88002B00;
extern M2C_UNK D_88002B08;

/**
 * Draws the GB save summary bar at rest (2 frames after the slide-in on the first entry).
 * Seen in play (2026-11-14): ran right after MainMenu_DrawSummaryBarSlideIn, before MainMenu_RunFrame.
 */
s32 MainMenu_DrawSummaryBar(s32 fade_mode) {
    M2C_UNK *var_a1;

    BgStage_DrawFrame();
    if (D_88002B00 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88002B08;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_88002A9C, D_88002B00);
    return 0;
}

M2C_UNK StageFade_Start(M2C_UNK);                     /* extern */
void BgStage_DrawFrame(void);                            /* extern */
M2C_UNK GbSave_DrawSummaryBar(M2C_UNK, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK Ui_DrawTintedScreenBackground(M2C_UNK, M2C_UNK, u8, u8, s32); /* extern */
extern M2C_UNK D_88002254;
extern M2C_UNK D_88002AAC;
extern s32 D_88002B00;
extern M2C_UNK D_88002B08;
extern MainMenuScreen* D_88002B20;

/**
 * Draws the GB save summary bar over the background.
 * Seen in play (2026-11-13) ran when the main menu came back with its top bar (1P サトシ IDNo/12345)
 * over the background.
 */
s32 MainMenu_DrawSummaryBarAndBackground(s32 fade_mode) {
    M2C_UNK *var_a1;

    if (fade_mode == 1) {
        StageFade_Start(15);
    }
    BgStage_DrawFrame();
    if (D_88002B00 == -1) {
        var_a1 = NULL;
    } else {
        var_a1 = &D_88002B08;
    }
    GbSave_DrawSummaryBar(0, var_a1, &D_88002AAC, D_88002B00);
    Ui_DrawTintedScreenBackground(56, 480, M2C_FIELD(&D_88002254, u8 *, 0), M2C_FIELD(&D_88002254, u8 *, 1), (s32) M2C_FIELD(&D_88002254, u8 *, 2));
    MainMenu_DrawItemList(&D_88002B20->itemList, 2);
    return 0;
}

void Cont_StartReadInputs(void);                            /* extern */
void Cont_ReadInputs(void);                            /* extern */
M2C_UNK func_8001B5F0();                            /* extern */
s32 MainMenu_UpdateScreen(MainMenuScreen*);
extern MainMenuScreen* D_88002B20;

/**
 * One frame: reads the controllers, draws the main menu and, when `fade_mode` is 0 (no fade running), updates it.
 * Seen in play: runs every frame on the メインメニュー screen (ずかん, バトル, てもち, GB, とうろく, OFF).
 */
s32 MainMenu_RunFrame(s32 fade_mode) {
    s32 sp1C;

    sp1C = 0;
    Cont_StartReadInputs();
    Cont_ReadInputs();
    func_8001B5F0();
    MainMenu_DrawScreen(D_88002B20);
    if (fade_mode == 0) {
        sp1C = MainMenu_UpdateScreen(D_88002B20);
    }
    return sp1C;
}

M2C_UNK func_80002DC0(s32);                         /* extern */
extern MainMenuScreen* D_88002B20;

/**
 * Frees the main menu state.
 * Seen in play (2026-11-12): ran once as the main menu was left for いちらん.
 */
void MainMenu_Free(void) {
    func_80002DC0(D_88002B20);
}

extern MainMenuScreen* D_88002B20;

/**
 * Draws the main menu without updating it.
 * Seen in play (2026-11-14): after はい on GB (result 0x8060) it ran with fade_mode 3 while the
 * screen faded out, and MainMenu_Free followed.
 */
s32 MainMenu_DrawFrame(s32 fade_mode) {
    MainMenu_DrawScreen(D_88002B20);
    return 0;
}

M2C_UNK func_8000256C(M2C_UNK);                     /* extern */
M2C_UNK func_80002620(M2C_UNK);                     /* extern */
M2C_UNK func_80003EB8(u32, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK StageFade_Start(M2C_UNK);                     /* extern */
M2C_UNK func_80006724();                            /* extern */
M2C_UNK func_8000675C();                            /* extern */
s32 func_80006828(M2C_UNK, M2C_UNK *);              /* extern */
M2C_UNK func_80006998(M2C_UNK);                     /* extern */
M2C_UNK func_8000A7B0(M2C_UNK);                     /* extern */
M2C_UNK func_8000A7FC(M2C_UNK);                     /* extern */
s32 Font_Init(s32 load_size, s32 side);            /* extern */
M2C_UNK func_8001A360();                            /* extern */
void MainMenu_LoadGbSaveSummary(void);                          /* extern */
extern M2C_UNK D_002E0BE0;
extern M2C_UNK D_002E2B90;
extern M2C_UNK D_00400F70;
extern M2C_UNK D_004076E0;
extern M2C_UNK D_004199E0;
extern M2C_UNK D_01000000;
extern M2C_UNK D_04000000;
extern M2C_UNK D_05000000;
extern s32 D_80073400;
s32 MainMenu_DrawFadeInBackground(s32 arg0);
s32 MainMenu_DrawSummaryBarSlideIn(s32 arg0);

/**
 * Entry point: pushes the 'COMP' pool state, loads the font and segments, and sets up the screen.
 * `is_first_entry` 1 plays the full intro (background fade-in, summary bar slide-in); otherwise the
 * menu fades straight in. Returns the chosen item's result (0x8040 fragment queued, 0x8050 continue
 * the tournament, 0x8060 GB).
 * Seen in play (2026-11-14): 1 when the menu followed the cartridge select screen after a reset,
 * 0 when it came back from the Pokédex with B.
 */
s32 MainMenu_Init(s32 is_first_entry) {
    s32 sp1C;
    s32 temp_v0;

    func_8000256C(0x434F4D50); // 'COMP'
    Font_Init(0x18, 0);
    func_80003EB8((u32) ((s32) &D_01000000 & 0x0F000000) >> 0x18, &D_002E0BE0, &D_002E2B90, 0);
    func_80003EB8((u32) ((s32) &D_04000000 & 0x0F000000) >> 0x18, &D_00400F70, &D_004076E0, 0);
    func_80003EB8((u32) ((s32) &D_05000000 & 0x0F000000) >> 0x18, &D_004076E0, &D_004199E0, 0);
    MainMenu_LoadGbSaveSummary();
    func_8000675C();
    if (is_first_entry == 1) {
        D_80073400 = 4;
        func_80006828(20, &MainMenu_DrawFadeInBackground);
        func_80006828(2, &MainMenu_DrawBackground);
        func_80006828(6, &MainMenu_DrawSummaryBarSlideIn);
        func_80006828(2, &MainMenu_DrawSummaryBar);
    } else {
        func_80006828(17, &MainMenu_DrawSummaryBarAndBackground);
    }
    func_8000A7B0(9);
    temp_v0 = func_80006828(0, &MainMenu_RunFrame);
    sp1C = temp_v0;
    D_80073400 = D_88002B20->itemList.menu.cursor + 1;
    if (temp_v0 != 0x8040) {
        if (temp_v0 == 0x8050) {
            func_80006998(0xFFFF); // #FFFFFF
        } else {
            func_80006998(1);
        }
        StageFade_Start(15);
        func_80006828(17, &MainMenu_DrawFrame);
        func_8000A7FC(15);
    } else {
        func_80006998(1);
    }
    func_80006724();
    MainMenu_Free();
    func_8001A360();
    func_80002620(0x434F4D50); // 'COMP'
    return sp1C;
}

extern M2C_UNK D_82000000;
extern M2C_UNK D_00166580;
extern M2C_UNK D_001720F0;

/**
 * Queues the バトル (Battle) fragment at 0x82000000 directly when gSessionContext.transitionFlags
 * bit 8 is set, otherwise runs the main menu. `unused` is never read (0 when coming back from the
 * Pokédex, &gSessionContext after the cartridge select screen).
 * Seen in play (2026-11-14): ran with is_first_entry 1 after the cartridge select screen and 0 when
 * the Pokédex was left with B.
 */
s32 MainMenu_Enter(s32 is_first_entry, s32 unused) {
    s32 ret;

    if (gSessionContext.transitionFlags & 0x100) {
        ret = 0x8040;
        Fragment_QueueCall(((u32)((s32)&D_82000000 & 0x0FF00000) >> 0x14) - 0x10, &D_00166580, &D_001720F0, 0, 0);
    } else {
        ret = MainMenu_Init(is_first_entry);
    }
    return ret;
}
