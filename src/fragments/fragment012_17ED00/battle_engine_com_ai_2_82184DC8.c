/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "global.h"
#include "fragments/particle_math/particle_math.h"
#include "jpeg_stream.h"
#include "controller.h"
#include "geo_render.h"
#include "model_animation.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sound_state.h"
#include "audio_sfx.h"
#include "audio_channel.h"
#include "audio_loop_point.h"
#include "audio_commands_category2.h"
#include "audio_category_fade.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "fragments/widget_toolkit/widget_toolkit.h"
#include "fragments/particle_math/particle_math.h"
#include "memory.h"
#include "stage_loader.h"
#include "geo_layout.h"
#include "fragments/free_battle_rules/free_battle_rules.h"
#include "graphics_textures.h"
#include "input.h"
#include "ui_graphics.h"
#include "pokemon_stats.h"
#include "game_state.h"
#include "session.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "DDC0.h"
#include "matrix.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
extern s32 pad_D_84002D10;
extern s32 pad_D_84002D1C;
#include "fragments/gallery_backgrounds/gallery_backgrounds.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "gb_data.h"
#include "save_data.h"
#include "gfx_rect.h"
#include "controller_ram.h"
#include "memory.h"
#include "fragments/gallery_camera/gallery_camera.h"
#include "matrix.h"
#include "stage_loader.h"
#include "fragments/gallery_camera/gallery_camera.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "text_system.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
extern u8 D_50002A0[];
extern u8 D_50003F0[];
extern u8 D_5000BA0[];
extern u8 D_5000C90[];
extern u8 D_50011D0[];
extern u8 D_5001680[];
extern u8 D_50017E8[];
#include "fragments/gallery_debugger/gallery_debugger.h"
#include "graphics_textures.h"
#include "input.h"
#include "save_data.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "controller.h"
#include "memory.h"
#include "stage_loader.h"
#include "fragments/gallery_enlarge/gallery_enlarge.h"
#include "display_object_textures.h"
#include "graphics_textures.h"
#include "input.h"
#include "gallery.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "gfx_buffer.h"
#include "controller.h"
#include "fragments/gallery_backgrounds/gallery_backgrounds.h"
#include "memory.h"
#include "stage_loader.h"
#include "fragments/gym_leader_castle/gym_leader_castle.h"
#include "graphics_textures.h"
#include "ui_graphics.h"
#include "save_data.h"
#include "game_state.h"
#include "text_system.h"
#include "jpeg_stream.h"
#include "audio_sfx.h"
#include "audio_commands_category2.h"
#include "DDC0.h"
#include "memory.h"
#include "stage_loader.h"
extern char** sUiText;
extern char** sTrainerNameText;
extern GymLeaderCastleTrainer sCurrentNodeTrainers[4];
extern BinArchive* sTrainerDataArchive;
extern BinArchive* sPortraitArchive;
extern BinArchive* sBackgroundArchive;
extern u8* sGymLeaderCastleTexture;
extern u8* sEliteFourTexture;
extern s16 sCurrentHoverNodeIndex;
#define CHAMPION 11
#define ELITE_4 10
#define ELITE_4_TO_GLC 9
#define GLC_TO_ELITE_4 8
#define GIOVANNI 7
extern CastleMapNode sCastleMapNodes[];
extern s16 sSelectedMapNode;
extern s16 sCursorMoveTimer;
extern s16 sRoomDescriptionHeight;
extern s16 sEliteFourTransition;
#include "math.h"
#include "geo_render.h"
#include "model_animation_events.h"
#include "geo_layout.h"
#include "display_object_textures.h"
#include "model_renderer.h"
#include "graphics_textures.h"
#include "input.h"
#include "ui_graphics.h"
#include "gallery.h"
#include "jpeg_stream.h"
#include "gfx_buffer.h"
#include "gfx_rect.h"
#include "matrix.h"
#include "controller.h"
#include "fragments/widget_toolkit/widget_toolkit.h"
#include "memory.h"
#include "stage_loader.h"
#include "m2c_macros.h"
void func_82183BA8(void);
void func_82183D9C(void);
void func_82183DA4(void);
void func_82183DAC(void);
void func_82183DB4(void);
void func_82183DBC(void);
void func_82183DC4(void);
void func_82183E1C(void);
void func_821853EC(void);
void func_821853F4(void);
void func_821853FC(void);
void func_82185404(void);
extern s32 D_821CF2B0;
extern u32 D_821CF2B4;
typedef struct BattleSlotZ {
    /* 0x00 */ TeamRoster* roster;
    /* 0x04 */ u8 pad04[4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ u8 pad10[0xB];
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 pad1E[7];
    /* 0x25 */ u8 unk_25;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
    /* 0x2E */ u8 pad2E[8];
    /* 0x36 */ u8 unk_36;
    /* 0x37 */ u8 pad37[0x27];
    /* 0x5E */ u8 unk_5E;
    /* 0x5F */ u8 pad5F[0x20];
    /* 0x7F */ u8 unk_7F;
    /* 0x80 */ u8 pad80[0x10];
} BattleSlotZ; // size = 0x90
extern BattleSlotZ* D_821CF298;
typedef struct Move82184ADC { u8 unk00; u8 unk01; u8 power; u8 type; u8 unk04; u8 unk05; } Move82184ADC;
extern Move82184ADC D_8006B190[];
extern u8 D_8218AC50[];

/* The definition has no return statement, so the value left in v0 by its last
 * call comes back. Reading it as u16 here is what makes IDO keep a saved copy. */
u16 func_8210EED8(s8*, s8*, u8);
s32 func_82184DC8(s8* arg0, s8* arg1, u8 move) {
    s32 score;
    s32 power;

    power = func_8210EED8(arg0, arg1, move);
    score = power;
    switch (move) {
        case 0x8A:
            if (M2C_FIELD(arg1, u8*, 0x15) & 7) {
                break;
            }
        case 0x49:
        case 0x4F:
        case 0x56:
        case 0x5F:
        case 0x64:
        case 0x68:
        case 0x69:
        case 0x6B:
        case 0x6D:
        case 0x73:
        case 0x78:
        case 0x87:
        case 0x8E:
        case 0x99:
        case 0x9C:
            return 0;
    }
    if ((power >= 6) && (M2C_FIELD(arg1, u8*, 0x61) >= 8)) {
        if (func_82183AF0() >= (-M2C_FIELD(arg1, u8*, 0x61) * 10) + 0x8C) {
            return 1;
        }
    }
    switch (move) {
        case 0x3:
        case 0x4:
        case 0x14:
        case 0x18:
        case 0x1F:
        case 0x23:
        case 0x29:
        case 0x2A:
        case 0x53:
        case 0x80:
        case 0x83:
        case 0x8C:
        case 0x9A:
        case 0x9B:
            score += score;
            break;
        case 0x2:
        case 0x4B:
        case 0x98:
        case 0xA3:
            score += (score / 2) + (score / 4);
            break;
        case 0xD:
        case 0x4C:
        case 0x82:
        case 0x8F:
            if ((M2C_FIELD(arg0, u16*, 0x2E) < M2C_FIELD(arg1, u16*, 0x2E)) ||
                (func_82184AA8((u8*)arg1 + 0x1F, 1, 4, 0x13) != 0) ||
                (func_82184AA8((u8*)arg1 + 0x1F, 1, 4, 0x5B) != 0)) {
                score = 0xA;
            }
            break;
        case 0xA2:
            score = M2C_FIELD(arg1, u16*, 0xC) / 2;
            break;
        case 0x5A:
            if ((M2C_FIELD(arg1, u8*, 0x1C) == 2) || (M2C_FIELD(arg1, u8*, 0x1D) == 2)) {
                score = 0;
            }
            break;
        case 0xC:
        case 0x20:
            if ((M2C_FIELD(arg1, u8*, 0x1C) == 8) || (M2C_FIELD(arg1, u8*, 0x1D) == 8)) {
                score = 0;
            }
            break;
    }
    return score;
}

extern u8 D_80065CF8[];

/* Old-style definition: func_82185108 calls this with two extra (unused) args. */
s32 func_82185044(species, bit) s32 species; s32 bit; {
    s32 byteIndex;
    s32 bits;

    if (species == 0) {
        return 0;
    }

    bits = D_80065CF8[species * 0x17 + bit / 8];
    switch (species) {
        case 6:
            if (bit / 8 == 6) {
                bits |= 8;
            }
            break;
        case 0xC:
        case 0x30:
        case 0x31:
            if (bit / 8 == 6) {
                bits |= 0x40;
            }
            break;
        case 0x32:
        case 0x33:
        case 0x8D:
            if (bit / 8 == 6) {
                bits |= 4;
            }
            break;
    }
    return (1 << (bit & 7)) & bits;
}

extern u8 D_821944CF[];
extern u32 D_821945C4[];
s32 func_82185108(u8 *arg0, s32 arg1) {
    s32 v = 0;

    if (arg1 != 0) {
        v = D_821944CF[arg1];
        if ((v != 0) && (v < 0x38)) {
            if (func_82185044(arg0[0x17], v - 1, v, arg1) != 0) {
                v = arg1;
            } else {
                v = 0;
            }
        } else if (v >= 0x38) {
            if (D_821945C4[arg0[0x17]] & (1 << (v + 8))) {
                v = arg1;
            } else {
                v = 0;
            }
        }
    }
    return v;
}

s32 func_82185108(u8*, s32);

/**
 * Searches the four slots of arg0 (id bytes at offsets 0x2B..0x2E, flag bytes
 * at 0x3E..0x41) for id arg1. Returns arg1 as soon as a slot with that id
 * has a non-zero flag; the search stops at the first empty (zero) id. When
 * nothing matched it returns func_82185108(arg0, arg1).
 */
s32 func_821851B4(u8* arg0, s32 arg1) {
    s32 i;
    u8* slot;

    for (i = 0, slot = arg0; i < 4; i++, slot++) {
        if (slot[0x2B] == 0) {
            break;
        }
        if ((arg1 == slot[0x2B]) && (slot[0x3E] != 0)) {
            return arg1;
        }
    }
    return func_82185108(arg0, arg1);
}

s32 func_821851B4(u8 *arg0, s32 arg1);
s32 func_82184DC8(s8 *, s8 *, u8);
extern u8 D_82194578[];
s32 func_82185220(u8 *arg0, u8 *arg1, s32 arg2)
{
  s32 best = 0;
  s32 i;
  s32 d;
  unsigned long move;
  if (!((*(*(*((u8 ***) arg0)))) & 2))
  {
    goto check;
  }
  slots:
  for (i = 0; i < 4; i++)
  {
    if (arg0[0x2B + i] == 0)
    {
      break;
    }
    if (func_82184BC8((s8 *) arg0, arg0[0x2B + i]) != 0)
    {
      d = func_82184DC8(((s8 *) arg0) + 0xC, ((s8 *) arg1) + 0xC, arg0[0x2B + i]);
      if (best < d)
      {
        best = d;
      }
    }
  }


  goto end;
  check:
  if (arg0[0x2E] != 0)
  {
    goto slots;
  }

  for (i = 0; i < 0x4E; i++)
  {
    move = D_82194578[i];
    if (((move != 0) && (((move != 0x78) && (move != 0x99)) || (arg2 > 0))) && (func_821851B4(arg0, move) != 0))
    {
      d = func_82184DC8(((s8 *) arg0) + 0xC, ((s8 *) arg1) + 0xC, move);
      if (best < d)
      {
        best = d;
      }
    }
  }

  end:
  return best;

}

void func_82185378(s8 *arg0, s8 *arg1)
{
  s32 var_v0;
  s8 *var_v1;
  *((s8 *) (((s8 *) arg0) + 0x4A)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x4B)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x4C)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x4D)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x4E)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x52)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x57)) = 0;
  *((s8 *) (((s8 *) arg0) + 0x56)) = 0;
  var_v1 = arg0;
  var_v0 = 0;
  *((u16 *) (((s8 *) arg0) + 0x2A)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x28))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u16 *) (((s8 *) arg0) + 0x2C)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x2A))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u16 *) (((s8 *) arg0) + 0x2E)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x2C))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  var_v1 = (s8 *) var_v1;
  *((u16 *) (((s8 *) arg0) + 0x30)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x2E))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  do
  {
    var_v0 += 4;
    *((s8 *) (((s8 *) var_v1) + 0x5D)) = 7;
    *((s8 *) (var_v1 + 0x5E)) = 7;
    *((s8 *) (var_v1 + 0x5F)) = 7;
    var_v1 += 4;
    *((s8 *) (((s8 *) var_v1) + 0x58)) = 7;
  }
  while (var_v0 != 8);
}

void func_821853EC(void) {
}

void func_821853F4(void) {
}

void func_821853FC(void) {
}

void func_82185404(void) {
}

// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s32 func_8218540C(s8 *arg0, s8 *arg1)
{
  if ((*((u8 *) (((s8 *) arg1) + 0x75))) & (*((u8 *) (((s8 *) arg0) + 0x76)))) // FAKE: decomp slop, raw pointer casts stand in for struct fields
  {
    return 1;
  }
  if (((s32) (*((u16 *) (((s8 *) arg1) + 0x3A)))) < ((s32) (*((u16 *) (((s8 *) arg0) + 0x3A))))) // FAKE: decomp slop, raw pointer casts stand in for struct fields
  {
    return 1;
  }
  return 0;
}

extern u8 D_8438B0C4[];
s32 BattleAI_IsRestrictedRandomMove(s32 arg0, s8* arg1) {
    if ((M2C_FIELD(arg1, u8*, 0x58) & 0x40) && (func_8218540C(arg0, arg1) != 0)) {
        return 1;
    }
    return 0;
}

extern s8 *D_821CF2A0;

s32 func_82185494(void) {
    return (M2C_FIELD(D_821CF2A0, u8 *, 0x59) & 0x10) == 0;
}

s32 func_821854AC(u8* arg0) {
    s32 i;
    s32 t;

    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            return -1;
        }
        if (func_82184BC8((s8*)arg0, arg0[0x2B + i]) != 0) {
            switch (arg0[0x2B + i]) {
                case 0x0E:
                case 0x4A:
                case 0x60:
                case 0x61:
                case 0x68:
                case 0x6A:
                case 0x6B:
                case 0x6E:
                case 0x6F:
                case 0x70:
                case 0x85:
                case 0x97:
                case 0x9F:
                    t = (D_8006B190[arg0[0x2B + i] - 1].unk01 - 10) & 7;
                    if ((arg0 + 0x68)[t] < 9) {
                        return i;
                    }
                    break;
                case 0x44:
                case 0x75:
                case 0x77:
                case 0x96:
                    return i;
                case 0xA4:
                    if (func_82185494() != 0 && func_82183CE4((s8*)arg0) >= 0x33) {
                        return i;
                    }
                    break;
            }
        }
    }
    return -1;
}

extern s32 D_821CF288;
s32 func_821855F0(BattleSlotZ *arg0)
{
  s32 i;
  BattleSlotZ *p;
  int new_var; // FAKE: permuter temp
  if ((arg0 == D_821CF298) && (((u8 *) D_821CF2A0)[0x21] & 7))
  {
    new_var = !D_821CF288;
    if ((new_var && (!D_821CF288)) && (!D_821CF288))
    {
    }
    return 0;
  }
  for (i = 0, p = arg0; i < D_821CF288; i++, p++)
  {
    if (((p->unk_1C != 0) && (((u8 *) p)[0x25] & 7)) && (((u8 *) p)[0x7F] == 0))
    {
      return 0;
    }
  }

  return 1;
}

extern u8 D_82194824[];
extern u8 D_82194840[];
s32 func_82185684(u8 *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            goto check;
        }
        if (func_82184BC8((s8*)arg0, arg0[0x2B + i]) != 0) {
            switch (arg0[0x2B + i]) {
                case 0:
                    goto check;
                case 0x2F:
                case 0x4F:
                case 0x5F:
                case 0x8E:
                case 0x93:
                    return 1;
            }
        }
    }
    return 0;
check:
    if (func_82184AA8(D_82194824, 1, 0x19, arg0[0x74]) != 0) {
        return 1;
    }
    if ((arg0[0x32] >= 0x32) && (func_82184AA8(D_82194840, 1, 8, arg0[0x74]) != 0)) {
        return 1;
    }
    return 0;
}

s32 func_821857CC(u8* arg0) {
    s32 i;
    s32 t;

    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            return -1;
        }
        if (func_82184BC8((s8*)arg0, arg0[0x2B + i]) != 0) {
            switch (arg0[0x2B + i]) {
                case 0x0E:
                case 0x4A:
                case 0x60:
                case 0x61:
                case 0x68:
                case 0x6A:
                case 0x6B:
                case 0x6E:
                case 0x6F:
                case 0x70:
                case 0x85:
                case 0x97:
                case 0x9F:
                    t = (D_8006B190[arg0[0x2B + i] - 1].unk01 - 10) & 7;
                    if ((arg0 + 0x68)[t] < 0xD) {
                        return i;
                    }
                    break;
            }
        }
    }
    return -1;
}

extern u8* D_821CF29C;
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
s32 func_821858DC(u8 *arg0)
{
  s32 i;
  if ((arg0[0x5A] & 1) || (((*((u16 *) (((s8 *) arg0) + 0x34))) / 2) < (*((u16 *) (((s8 *) arg0) + 0x72))))) // FAKE: decomp slop, raw pointer casts stand in for struct fields
  {
    return -1;
  }
  switch (arg0[0x7C])
  {
    case 0x69:

    case 0x87:

    case 0x9C:
      return -1;

  }

  if (func_82183CE4((s8 *) D_821CF29C) < 0x28)
  {
    for (i = 0; i < 4; i++)
    {
      if (arg0[0x2B + i] == 0)
      {
        return -1;
      }
      if (func_82184BC8((s8 *) arg0, arg0[0x2B + i]) != 0)
      {
        switch (arg0[0x2B + i])
        {
          case 0x69:

          case 0x87:
            return i;

          case 0x9C:
            if ((arg0[0x7E] != 0x9C) && (arg0[0x7D] != 0x9C))
          {
            return i;
            break;
          }

        }

      }
    }

  }
  return -1;
}

extern u8* D_821CF29C;
s32 func_8218824C(s32);
s32 func_82185A30(u8 *arg0) {
    s32 i;
    s32 r;

    if (func_82185494() == 0) {
        return -1;
    }
    if (D_821CF29C[0x7C] == 0x5C) {
        return -1;
    }
    r = func_8218824C((func_82183CE4(D_821CF2A0) * 5) / 4);
    if (r >= 0) {
        return r;
    }
    if ((((u8 *)D_821CF2A0)[0x21] == 0) && (func_82184D9C(D_821CF2A0, 3) == 0)) {
        for (i = 0; i < 4; i++) {
            if (arg0[0x2B + i] == 0) {
                break;
            }
            if ((func_82184BC8((s8 *)arg0, arg0[0x2B + i]) != 0) && (arg0[0x2B + i] == 0x5C)) {
                return i;
            }
        }
    }
    if (!(((u8 *)D_821CF2A0)[0x21] & 8)) {
        return -1;
    }
    if ((((u8 *)D_821CF2A0)[0x75] & D_821CF29C[0x77]) || (func_82184D9C(D_821CF2A0, 0x16) != 0)) {
        return -1;
    }
    {
        for (i = 0; i < 4; i++) {
            if (arg0[0x2B + i] == 0) {
                break;
            }
            if ((func_82184BC8((s8 *)arg0, arg0[0x2B + i]) != 0) && (arg0[0x2B + i] == 0x49)) {
                return i;
            }
        }
    }
    return -1;
}

extern u8 D_8006B18B[];
s32 func_82185BE0(u8 *arg0, s32 arg1) {
    s32 i;
    s32 t;
    s32 pad; // FAKE: stack padding
    u8 *p;

    if (func_82185494() != 0) {
        i = 0;
        p = arg0;
        if (!(((u8 *)D_821CF2A0)[0x59] & 2)) {
        loop:
            if (p[0x2B] == 0) goto end;
            if (func_82184BC8((s8 *)arg0, p[0x2B]) != 0) {
                switch (p[0x2B]) {
                    case 0x1C:
                    case 0x27:
                    case 0x2B:
                    case 0x2D:
                    case 0x51:
                    case 0x67:
                    case 0x6C:
                    case 0x86:
                    case 0x94:
                        t = D_8006B18B[p[0x2B] * 6];
                        if (t >= 0x44) {
                            t -= 0x44;
                        } else {
                            t -= 0x12;
                            if (t >= 8) {
                                t -= 0x28;
                            }
                        }
                        t &= 7;
                        if ((((u8 *)D_821CF2A0)[t + 0x68] >= 6) && (arg0[0x7C] != p[0x2B])) {
                            return i;
                        }
                        break;
                }
            }
            i++;
            p++;
            if (i != 4) goto loop;
        }
    }
end:
    return -1;
}

s32 func_82185D44(s32 move) {
    s32 v1;
    s32 i;

    if (D_8006B190[move - 1].power != 0) {
        if (func_82184ADC((s8 *)D_821CF29C, D_821CF2A0, move) == 0) {
            fail:
            return 0;
        }
    }
    switch (D_8006B190[move - 1].unk01) {
        case 28:
            goto fail;
        case 66:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (func_82184D9C(D_821CF2A0, 3) != 0) {
                goto fail;
            }
            if (((u8 *)D_821CF2A0)[0x21] != 0) {
                goto fail;
            }
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 3:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            /* fallthrough */
        case 7:
        case 24:
        case 82:
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 4:
        case 5:
        case 6:
        case 34:
        case 35:
        case 36:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (((u8 *)D_821CF2A0)[0x21] != 0) {
                goto fail;
            }
            if (func_82184D9C(D_821CF2A0, D_8006B190[move - 1].type) == 0) {
                break;
            }
            return 0;
        case 8:
            if ((((u8 *)D_821CF2A0)[0x21] & 7) == 0) {
                goto fail;
            }
            if (func_82185494() == 0) {
                goto fail;
            }
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 10: case 11: case 12: case 13: case 14: case 15:
        case 50: case 51: case 52: case 53: case 54: case 55:
            v1 = D_8006B190[move - 1].unk01 - 10;
            v1 &= 7;
            if (((u8 *)D_821CF2A0)[v1 + 0x68] != 0xD) {
                break;
            }
            return 0;
        case 18: case 19: case 20: case 21: case 22: case 23:
        case 58: case 59: case 60: case 61: case 62: case 63:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (((u8 *)D_821CF2A0)[0x59] & 2) {
                goto fail;
            }
            v1 = D_8006B190[move - 1].unk01;
            if (v1 >= 0x44) {
                v1 -= 0x44;
            } else {
                if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                    goto fail;
                }
                v1 -= 0x12;
                if (v1 >= 8) {
                    v1 -= 0x28;
                }
            }
            v1 &= 7;
            if (((u8 *)D_821CF2A0)[v1 + 0x68] != 1) {
                break;
            }
            return 0;
        case 25:
            for (i = 0; i < 8; i++) {
                if (((u8 *)D_821CF29C)[i + 0x68] != 7) {
                    goto done;
                }
                if (((u8 *)D_821CF2A0)[i + 0x68] != 7) {
                    goto done;
                }
            }
            if (((u8 *)D_821CF29C)[0x21] != 0) break;
            if (((u8 *)D_821CF2A0)[0x21] != 0) break;
            if (((u8 *)D_821CF29C)[0x63] != 0) break;
            if (((u8 *)D_821CF2A0)[0x63] != 0) break;
            if (((u8 *)D_821CF29C)[0x58] != 0) break;
            if (((u8 *)D_821CF29C)[0x59] != 0) break;
            if (((u8 *)D_821CF29C)[0x5A] != 0) break;
            if (((u8 *)D_821CF2A0)[0x58] != 0) break;
            if (((u8 *)D_821CF2A0)[0x59] != 0) break;
            if (((u8 *)D_821CF2A0)[0x5A] != 0) break;
            if (((u8 *)D_821CF29C)[0x62] != 0) break;
            if (((u8 *)D_821CF2A0)[0x62] != 0) break;
            goto fail;
        case 29: case 30: case 44: case 77:
            if (!(((u8 *)D_821CF2A0)[0x58] & 4)) {
                break;
            }
            return 0;
        case 31: case 37:
            if (func_82185494() != 0) {
                break;
            }
            return 0;
        case 32:
            if (((u8 *)D_821CF2A0)[0x21] != 0) {
                goto fail;
            }
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            if (func_821855F0(D_821CF298) != 0) {
                break;
            }
            return 0;
        case 38:
            if (func_8218540C((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                break;
            }
            return 0;
        case 42:
            if (!(((u8 *)D_821CF29C)[0x58] & 0x20)) {
                break;
            }
            return 0;
        case 46:
            if (!(((u8 *)D_821CF29C)[0x59] & 2)) {
                break;
            }
            return 0;
        case 47:
            if (!(((u8 *)D_821CF29C)[0x59] & 4)) {
                break;
            }
            return 0;
        case 49:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (((u8 *)D_821CF2A0)[0x58] & 0x80) {
                goto fail;
            }
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 56:
            if (((u16 *)D_821CF29C)[0x34 / 2] != ((u16 *)D_821CF29C)[0x18 / 2]) {
                break;
            }
            return 0;
        case 57:
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            if (func_82185494() != 0) {
                break;
            }
            return 0;
        case 64:
            if (!(((u8 *)D_821CF29C)[0x5A] & 2)) {
                break;
            }
            return 0;
        case 65:
            if (!(((u8 *)D_821CF29C)[0x5A] & 4)) {
                break;
            }
            return 0;
        case 67:
            if (((u8 *)D_821CF2A0)[0x21] != 0) {
                goto fail;
            }
            if (D_8006B190[move - 1].type == 0x17) {
                if (func_82184D9C(D_821CF2A0, 4) != 0) {
                    goto fail;
                }
            }
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) == 0) {
                break;
            }
            return 0;
        case 79:
            if (func_82185494() == 0) {
                goto fail;
            }
            if (((u16 *)D_821CF29C)[0x18 / 2] >= (((u16 *)D_821CF29C)[0x34 / 2] >> 2)) {
                break;
            }
            return 0;
        case 84:
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            if (func_82184D9C(D_821CF2A0, 0x16) != 0) {
                goto fail;
            }
            if (!(((u8 *)D_821CF2A0)[0x59] & 0x80)) {
                break;
            }
            return 0;
        case 86:
            if (func_82185450((s8 *)D_821CF29C, D_821CF2A0) != 0) {
                goto fail;
            }
            if (((u8 *)D_821CF2A0)[0x5E] != 0) {
                goto fail;
            }
            break;
        case 0:
        default:
            break;
    }
done:
    return move;
}

extern u8* D_821CF29C;
s32 func_82186394(u8 *arg0, u8 *arg1) {
    s32 i;

    if ((arg1[0x21] != 0) || (func_82185450(D_821CF29C, D_821CF2A0) != 0) || (func_82183CE4(D_821CF2A0) < 0x1E) ||
        (func_82183CE4((s8*)D_821CF29C) < 0x1E)) {
        return -1;
    }
    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            return -1;
        }
        if (func_82184BC8((s8*)arg0, arg0[0x2B + i]) != 0) {
            switch (arg0[0x2B + i]) {
                case 0x56:
                    if (func_82184D9C((s8*)arg1, 4) != 0) {
                        return -1;
                    }
                case 0x4E:
                case 0x89:
                    return i;
            }
        }
    }
    return -1;
}

s32 func_821855F0();
s32 func_821864D4(u8 *arg0, u8 *arg1) {
    s32 i;

    if ((arg1[0x21] != 0) || (func_82185450(D_821CF29C, D_821CF2A0) != 0) || (func_821855F0(D_821CF298) == 0) ||
        (func_82183CE4(D_821CF2A0) < 0x1E) || (func_82183CE4((s8*)D_821CF29C) < 0x1E)) {
        return -1;
    }
    switch (arg0[0x7C]) {
        case 0x2F:
        case 0x4F:
        case 0x5F:
        case 0x8E:
        case 0x93:
            return -1;
    }
    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            return -1;
        }
        if (func_82184BC8((s8*)arg0, arg0[0x2B + i]) != 0) {
            switch (arg0[0x2B + i]) {
                case 0x2F:
                case 0x4F:
                case 0x5F:
                case 0x8E:
                    if (arg1[0x6D] < 9) {
                        return i;
                    }
                    break;
                case 0x93:
                    return i;
            }
        }
    }
    return -1;
}

s32 func_8218663C(u8 *arg0, u8 *arg1) {
    s32 i;

    if (func_82185450(arg0, arg1) != 0) {
        return -1;
    }
    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            break;
        }
        if (func_82184BC8((s8*)arg0, arg0[0x2B + i]) != 0) {
            switch (arg0[0x2B + i]) {
                case 0x78:
                case 0x99:
                    return i;
            }
        }
    }
    return -1;
}

extern u8 D_821CF280[];
extern u8 D_821CF281;
extern BattleSlotZ* D_821CF294;

extern BattleSlotZ* D_821CF294;
extern u8 D_821CF280[];
extern u8 D_821CF281;

/**
 * Returns 0x2710 or 0 depending on arg0 and the BattleSlotZ entries (array D_821CF294)
 * selected by the indices D_821CF281 and D_821CF280:
 *   arg0 == 2: if the entry at D_821CF281 has unk_1B equal to 3, 0x71 or 0x7C, returns 0;
 *              otherwise falls through to the arg0 == 1 check;
 *   arg0 == 1: if the entry at D_821CF280 has unk_1B equal to 3, 0x71 or 0x7C, returns 0;
 *              otherwise falls through to return 0x2710;
 *   arg0 == 0: returns 0x2710;
 *   any other arg0: returns 0.
 * What the 0x2710 / 0 results and the unk_1B values mean is not established.
 */
s32 func_821866F0(s32 arg0) {
    switch (arg0) {
        case 2:
            if ((D_821CF294[D_821CF281].unk_1B == 3) || (D_821CF294[D_821CF281].unk_1B == 0x71) || (D_821CF294[D_821CF281].unk_1B == 0x7C)) {
                return 0;
            }
        case 1:
            if ((D_821CF294[D_821CF280[0]].unk_1B == 3) || (D_821CF294[D_821CF280[0]].unk_1B == 0x71) || (D_821CF294[D_821CF280[0]].unk_1B == 0x7C)) {
                return 0;
            }
        case 0:
            return 0x2710;
        default:
            return 0;
    }
}

/**
 * Copies up to four bytes from the string arg0 into arg1. Each of the four
 * output bytes is the current source byte; the source pointer only advances
 * while the byte is non-zero, so once the NUL is reached the remaining output
 * bytes are all zero. (The output is always exactly four bytes.)
 */
void func_821867A8(u8* arg0, u8* arg1) {
    s32 i;
    u8 c;

    for (i = 0; i < 4; i++) {
        c = *arg0;
        if (c == 0) {
            *arg1 = 0;
            arg1++;
        } else {
            *arg1 = c;
            arg1++;
            arg0++;
        }
    }
}

M2C_UNK func_80058410(s8*, s8*, M2C_UNK);

/**
 * Copies a set of fields from the record arg1 into the record arg0, which has a
 * different layout (arg1's offsets 0, 2, 4, 5, 6, 7, 0x1E, 0x24 and 0x26..0x2E map to
 * arg0's 0xB, 0xC, 0x14, 0x15, 0x1C, 0x1D, 0x24, 0x26 and 0x28..0x30). The name field
 * at arg1 + 9 is expanded into the four bytes at arg0 + 0x1F by func_821867A8, and the
 * four bytes at arg1 + 0x20 are copied to arg0 + 0x32. Compare func_821869C4, which
 * copies the already-expanded layout. What the fields mean is not established.
 */
void func_82186834(s8* arg0, s8* arg1) {
    M2C_FIELD(arg0, u8*, 0xB) = M2C_FIELD(arg1, u8*, 0);
    M2C_FIELD(arg0, u16*, 0xC) = M2C_FIELD(arg1, u16*, 2);
    M2C_FIELD(arg0, u8*, 0x14) = M2C_FIELD(arg1, u8*, 4);
    M2C_FIELD(arg0, u8*, 0x15) = M2C_FIELD(arg1, u8*, 5);
    M2C_FIELD(arg0, u8*, 0x1C) = M2C_FIELD(arg1, u8*, 6);
    M2C_FIELD(arg0, u8*, 0x1D) = M2C_FIELD(arg1, u8*, 7);
    func_821867A8(arg1 + 9, arg0 + 0x1F);
    M2C_FIELD(arg0, u16*, 0x24) = M2C_FIELD(arg1, u16*, 0x1E);
    M2C_FIELD(arg0, u8*, 0x26) = M2C_FIELD(arg1, u8*, 0x24);
    M2C_FIELD(arg0, u16*, 0x28) = M2C_FIELD(arg1, u16*, 0x26);
    M2C_FIELD(arg0, u16*, 0x2A) = M2C_FIELD(arg1, u16*, 0x28);
    M2C_FIELD(arg0, u16*, 0x2C) = M2C_FIELD(arg1, u16*, 0x2A);
    M2C_FIELD(arg0, u16*, 0x2E) = M2C_FIELD(arg1, u16*, 0x2C);
    M2C_FIELD(arg0, u16*, 0x30) = M2C_FIELD(arg1, u16*, 0x2E);
    func_80058410(arg1 + 0x20, arg0 + 0x32, 4);
}

typedef struct BaseStats821868E8 { u8 species; u8 hp; u8 atk; u8 def; u8 spd; u8 spc; u8 type1; u8 type2; char unk08[0xF]; } BaseStats821868E8;
extern u8 D_80065D00[];
s32 func_82183C78(s32, s32);
s32 func_82183C9C(s32, s32);
s32 func_82183CC0(s32, s32);
void func_821868E8(s8* arg0, s32 species, s32 level) {
    BaseStats821868E8* stats;

    if (species != 0 && species < 0x98) {
        M2C_FIELD(arg0, u8*, 0xB) = species;
        stats = &((BaseStats821868E8*)D_80065D00)[species - 1];
        M2C_FIELD(arg0, s16*, 0xC) = M2C_FIELD(arg0, s16*, 0x28) = func_82183C24(stats->hp, level);
        M2C_FIELD(arg0, u8*, 0x1C) = stats->type1;
        M2C_FIELD(arg0, u8*, 0x1D) = stats->type2;
        M2C_FIELD(arg0, s16*, 0x24) = 0x7777;
        M2C_FIELD(arg0, u8*, 0x26) = level;
        M2C_FIELD(arg0, s16*, 0x2A) = func_82183C54(stats->atk, level);
        M2C_FIELD(arg0, s16*, 0x2C) = func_82183C78(stats->def, level);
        M2C_FIELD(arg0, s16*, 0x2E) = func_82183C9C(stats->spd, level);
        M2C_FIELD(arg0, s16*, 0x30) = func_82183CC0(stats->spc, level);
    }
}

M2C_UNK func_80058410(s8 *, s8 *, M2C_UNK);     /* extern */
extern s8 *D_821CF2A0;
// FAKE: decomp slop. Raw pointer-offset casts stand in for struct fields.
void func_821869C4(s8 *arg0, s8 *arg1)
{
  long temp_v1;
  u8 *new_var; // FAKE: permuter temp
  *((u16 *) (((s8 *) arg0) + 0x28)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x28))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u16 *) (((s8 *) arg0) + 0xC)) = (u16) (*((u16 *) (((s8 *) arg1) + 0xC))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x15)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x15))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  func_80058410(arg1 + 0x44, arg0 + 0x44, 6);
  *((u8 *) (((s8 *) arg0) + 0x4A)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4A))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x4B)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4B))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x4C)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4C))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x4D)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4D))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x4E)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x4E))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u16 *) (((s8 *) arg0) + 0x54)) = (u16) (*((u16 *) (((s8 *) arg1) + 0x54))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x56)) = (u8) (*(new_var = (u8 *) (((s8 *) arg1) + 0x56))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x57)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x57))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x58)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x58))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x59)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x59))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x5A)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x5A))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  *((u8 *) (((s8 *) arg0) + 0x5B)) = (u8) (*((u8 *) (((s8 *) arg1) + 0x5B))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  func_80058410(arg1 + 0x5C, arg0 + 0x5C, 8);
  if ((*((u8 *) (((s8 *) arg1) + 0x4E))) & 8)
  {
    func_821867A8(arg1 + 0x1F, arg0 + 0x1F);
    func_80058410(arg1 + 0x32, arg0 + 0x32, 4);
    return;
  }
  temp_v1 = *((u8 *) (((s8 *) D_821CF2A0) + 0x78));
  if (((s32) temp_v1) < 4)
  {
    *((u8 *) (((s8 *) (arg0 + temp_v1)) + 0x1F)) = (u8) (*((u8 *) (((s8 *) (arg1 + temp_v1)) + 0x1F))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
    *((u8 *) (((s8 *) (arg0 + (*((u8 *) (((s8 *) D_821CF2A0) + 0x78))))) + 0x32)) = (u8) (*((u8 *) (((s8 *) D_821CF2A0) + 0x79))); // FAKE: decomp slop, raw pointer casts stand in for struct fields
  }
}

void func_8004FD20(void*, s32);
typedef struct PartyMon82186AF4 {
    /* 0x00 */ u8 species;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u16 hp;
    /* 0x04 */ u8 unk04[5];
    /* 0x09 */ u8 moves[4];
    /* 0x0D */ u8 unk0D[0x17];
    /* 0x24 */ u8 level;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u16 maxHp;
    /* 0x28 */ u8 unk28[0x28];
} PartyMon82186AF4; // size = 0x50

typedef struct Party82186AF4 {
    /* 0x000 */ u8 flags;
    /* 0x001 */ u8 unk001[0x1B];
    /* 0x01C */ PartyMon82186AF4 mons[6];
    /* 0x1FC */ u8* info;
} Party82186AF4;

typedef struct Slot82186AF4 {
    /* 0x00 */ void* owner;
    /* 0x04 */ u8 unk04[8];
    /* 0x0C */ u8 mon[0x0C];
    /* 0x18 */ u16 hp;
    /* 0x1A */ u8 unk1A[0x56];
    /* 0x70 */ u16 hp2;
    /* 0x72 */ u8 unk72[2];
    /* 0x74 */ u8 species;
    /* 0x75 */ u8 mask;
    /* 0x76 */ u8 unk76[2];
    /* 0x78 */ u8 moveCount;
    /* 0x79 */ u8 unk79;
    /* 0x7A */ u8 unk7A[0x16];
} Slot82186AF4; // size = 0x90

typedef struct Side82186AF4 {
    /* 0x000 */ Party82186AF4* party;
    /* 0x004 */ Slot82186AF4 slots[6];
    /* 0x364 */ f32 unk364;
    /* 0x368 */ s8 unk368;
    /* 0x369 */ u8 unk369;
    /* 0x36A */ u8 unk36A;
    /* 0x36B */ u8 unk36B;
} Side82186AF4;

void func_82186AF4(Side82186AF4 *arg0, Party82186AF4 *arg1, s32 arg2)
{
  s32 i;
  s32 j;
  u8 species;
  u8 level;
  arg0->party = arg1;
  arg0->unk368 = arg2;
  arg0->unk369 = 0xFF;
  arg0->unk36B = 0xFF;
  arg0->unk364 = 0.5f;
  if (arg2 >= 2)
  {
    arg0->unk364 = 10.0f;
  }
  for (i = 0; i < 6; i++)
  {
    func_8004FD20(&arg0->slots[i], sizeof(Slot82186AF4));
    arg0->slots[i].mask = 1 << i;
    arg0->slots[i].owner = arg0;
    arg0->slots[i].species = arg1->mons[i].species;
    if (i < arg1->info[2])
    {
      species = arg1->mons[i].species;
      if (((species != 0) && (arg1->mons[i].hp != 0)) && (arg1->mons[i].maxHp != 0))
      {
        level = arg1->mons[i].level;
        if (level != 0)
        {
          j = 0; // FAKE: permuter; early init of the move counter
          level = arg1->mons[i].level; // FAKE: permuter; redundant reload of level
          if (arg1->flags & 2)
          {
            func_82186834((s8 *) arg0->slots[i].mon, (s8 *) (&arg1->mons[i]));
            arg0->slots[i].hp2 = arg0->slots[i].hp;
          }
          else
          {
            func_821868E8((s8 *) arg0->slots[i].mon, arg1->mons[i].species, level);
          }
          for (j = 0; j < 4; j++)
          {
            if ((arg1->mons[i].moves[j] == 0) || (arg1->mons[i].moves[j] == 0x66))
            {
              break;
            }
          }

        }
      }
    }
    arg0->slots[i].moveCount = j;
    arg0->slots[i].unk79 = 0x10;
  }

}

extern u8 D_82194848[];
void func_82186CA8(u8 *arg0, u8 *arg1) {
    s32 score;
    s32 i;
    s32 acc;

    switch (arg0[0x17]) {
        default:
            score = 0;
            break;
        case 0x84:
            score = 0;
            break;
        case 0x79:
            score = 0;
            break;
    }
    if (*(u16 *)(arg0 + 0x18) != 0) {
        score = 0x8000;
    }
    if (!(arg0[0x21] & 0x20)) {
        score += 0x4000;
    }
    if (!(arg0[0x5A] & 1) || (arg0[0x7A] < 3)) {
        score += 0x2000;
    }
    if (!(arg0[0x21] & 7)) {
        score += 0x1000;
    }
    if (func_82184CE0(arg0) != 0) {
        score += 0x200;
    }
    if ((func_82184D9C((s8 *)arg0, 0x19) != 0) || (func_82184D9C((s8 *)arg0, 3) != 0)) {
        score += 0x200;
    }
    if (*(u16 *)(arg1 + 0x3A) < *(u16 *)(arg0 + 0x3A)) {
        score += 0x300;
    }
    for (i = 0; i < 4; i++) {
        if (arg0[0x2B + i] == 0) {
            break;
        }
        if ((func_82184BC8((s8 *)arg0, arg0[0x2B + i]) != 0) && (func_82184AA8(D_82194848, 1, 0x2B, arg0[0x2B + i]) != 0)) {
            acc = (D_8006B190[arg0[0x2B + i]].unk04 * D_8006B190[arg0[0x2B + i]].unk04) / 650;
            score += (((func_82184ADC((s8 *)arg0, (s8 *)arg1, arg0[0x2B + i]) * 8) / 100) * acc) / 100;
        }
    }
    *(s32 *)(arg0 + 4) += score;
}

s32 func_82186F28(s32 arg0, s32 arg1) {
    s32 i;
    s32 sum;

    if ((arg0 == 0) || (arg0 >= 3)) {
        return 1;
    }
    if (arg0 == 1) {
        for (i = 0; i < 6; i++) {
            if ((i != D_821CF280[0]) && (i != arg1)) {
                sum = D_821CF294[D_821CF280[0]].unk_36 + D_821CF294[i].unk_36 + D_821CF294[arg1].unk_36;
                if ((sum >= 0x96) && (sum < 0x9C)) {
                    return 1;
                }
            }
        }
        return 0;
    }
    sum = D_821CF294[D_821CF280[0]].unk_36 + D_821CF294[D_821CF280[1]].unk_36 + D_821CF294[arg1].unk_36;
    if ((sum >= 0x96) && (sum < 0x9C)) {
        return 1;
    }
    return 0;
}

extern BattleSlotZ* D_821CF294;
s32 func_82186F28(s32, s32);

s32 func_821870D8(s32 arg0, s32 arg1, s32 arg2) {
    if ((M2C_FIELD(D_821CF294, u8*, 0x368) != 0) || (arg0 != 0)) {
        return 1;
    }
    if (func_82186F28(arg1, arg2) == 0) {
        return 0;
    } else {
        return 1;
    }
    return 1;
}

void func_8218419C(u8 *, s32);
s32 func_82187134(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 i;
  s32 j;
  s32 best;
  s32 bestScore;

  for (i = 0; i < 6; i++)
  {
    D_821CF294[i].unk_08 = -1;
    if ((D_821CF294[i].unk_1C != 0) && (((arg1 == 0) && (!(((u8 *) D_821CF294)[0x36C] & (1 << i)))) || ((arg1 != 0) && (((u8 *) D_821CF294)[0x36C] & (1 << i)))))
    {
      if (arg0 == NULL)
      {
        for (j = 0; j < 6; j++)
        {
          if ((D_821CF298[j].unk_1C != 0) && (D_821CF298[j].unk_1B != 0) && (D_821CF298[j].unk_36 != 0))
          {
            func_82186CA8(D_821CF294[i].pad04, D_821CF298[j].pad04);
          }
        }
      }
      else
      {
        func_82186CA8(D_821CF294[i].pad04, arg0);
      }
      if ((arg2 != 0) && (func_82183AF0() < 0x28))
      {
        func_82183DCC((s8 *) D_821CF294[i].pad04);
      }
      if (((u8 *) D_821CF294)[0x368] >= 2)
      {
        D_821CF294[i].unk_08 += func_82183AF0() * 1000;
      }
      else if (((u8 *) D_821CF294)[0x368] == 1)
      {
        func_82183DCC((s8 *) D_821CF294[i].pad04);
      }
      func_8218419C(D_821CF294[i].pad04, arg3);
    }
  }

  bestScore = -1;
  best = -1;
  for (i = 0; i < 6; i++)
  {
    if ((D_821CF294[i].unk_1C != 0) && (((arg1 == 0) && (!(((u8 *) D_821CF294)[0x36C] & (1 << i)))) || ((arg1 != 0) && (((u8 *) D_821CF294)[0x36C] & (1 << i)))) && (func_821870D8(arg1, arg3, i) != 0))
    {
      if (bestScore < D_821CF294[i].unk_08)
      {
        bestScore = D_821CF294[i].unk_08;
        best = i;
      }
    }
  }

  if (best < 0)
  {
    return -1;
  }
  ((u8 *) D_821CF294)[0x36C] |= 1 << best;
  return best;
}

s32 func_82187134(u8 *, s32, s32, s32);
extern u8 D_821CF2B8[];
s32 func_82187414(s32 arg0)
{
  s32 best;
  s32 i;
  f32 max;
  f32 scores[6];
  s32 r;
  s32 j;

  D_821CF288 = arg0;
  for (i = 0; i < D_821CF288; i++)
  {
    r = func_82187134(0, 0, 1, i);
    if (r < 0)
    {
      return -1;
    }
    D_821CF280[i] = r;
  }

  for (i = 0; i < D_821CF288; i++)
  {
    scores[i] = 0.0f;
    for (j = 0; j < 6; j++)
    {
      if (D_821CF298[j].unk_1C != 0)
      {
        r = func_82185220(D_821CF298[j].pad04, D_821CF294[D_821CF280[i]].pad04, 0);
        if (r == 0)
        {
          scores[i] += 2.0f;
        }
        else
        {
          scores[i] += ((f32) func_82185220(D_821CF294[D_821CF280[i]].pad04, D_821CF298[j].pad04, 0)) / ((f32) r);
        }
      }
    }
  }

  max = 0.0f;
  best = 0;
  for (i = 0; i < D_821CF288; i++)
  {
    if (max < scores[i])
    {
      best = i;
      max = scores[i];
    }
  }

  if ((best != 0) && (func_82183AF0() < 0x32))
  {
    i = D_821CF280[best]; // FAKE: i reused as swap temp
    D_821CF280[best] = D_821CF280[0];
    D_821CF280[0] = i;
  }

  for (i = 0; i < D_821CF288; i++)
  {
    func_80058410((s8 *) D_821CF294[D_821CF280[i]].pad04, (s8 *) &D_821CF2B8[i * 0x90], 0x90);
  }

  for (i = 0; i < D_821CF288; i++)
  {
    func_80058410((s8 *) &D_821CF2B8[i * 0x90], (s8 *) D_821CF294[i].pad04, 0x90);
    ((u8 *) &D_821CF294[i])[0x79] = 1 << i;
  }

  ((u8 *) D_821CF294)[0x36C] = (1 << D_821CF288) - 1;
  return 0;
}

extern BattleSlotZ D_821CF618[6];
extern BattleSlotZ D_821CF998[6];
extern s32 D_821CF2A4;
void func_8004FD20(void*, s32);
void func_82186AF4(); /* real types are declared with the definition below */
s32 func_82187414(s32);

s32 func_82187738(u8* arg0, u8* arg1, s32 arg2, s8* arg3, s32 arg4) {
    s32 j;
    s32 i;
    s32 ret;

    D_821CF2B0 = 0x3039;
    D_821CF2B4 = 0x1A85;
    func_82183B60();
    func_8004FD20(D_821CF618, 0x700);
    D_821CF2A4 = 0xFEDC;
    if (*arg0 & 2) {
        D_821CF294 = D_821CF618;
        D_821CF298 = D_821CF998;
    } else {
        D_821CF294 = D_821CF998;
        D_821CF298 = D_821CF618;
    }
    func_82186AF4(D_821CF294, arg0, arg2);
    func_82186AF4(D_821CF298, arg1, arg2);
    D_821CF294 = D_821CF618;
    D_821CF298 = D_821CF998;
    D_821CF29C = (u8*)D_821CF294 + 4;
    D_821CF2A0 = (s8*)D_821CF298 + 4;
    for (i = 0; i < 6; i++) {
        D_821CF280[i] = 0;
        D_821CF294[i].unk_7F = 0;
        D_821CF298[i].unk_7F = 0;
    }
    ret = func_82187414(arg4);
    if (ret == 0) {
        for (j = 0; j < arg4; j++) {
            arg3[j] = D_821CF280[j];
        }
    } else {
        for (i = 0; i < arg4; i++) {
            arg3[i] = i;
        }
    }
    return ret;
}

s32 func_821879A4(void) {
    s32 flag;
    s32 r;
    f32 fa[6];
    f32 f20;
    s32 k;
    s32 best;
    s32 i;

    flag = 0;
    k = 0;
    best = -1;
    if (M2C_FIELD(D_821CF29C, u16*, 0x18) == 0 || (D_821CF29C[0x21] & 0x20) || (D_821CF29C[0x5A] & 1)) {
        flag = 1;
    } else if ((D_821CF29C[0x21] & 7) && D_821CF29C[0x6D] < 10) {
        flag = 1;
    }
    if (M2C_FIELD(D_821CF29C, u16*, 0x18) == 0) {
        ((u8*)D_821CF294)[0x36C] &= ~D_821CF29C[0x75];
    }
    for (i = 0; i < D_821CF288; i++) {
        if ((r = func_82185220((u8*)D_821CF2A0, D_821CF294[i].pad04, 0)) == 0) {
            fa[i] = 255.0f;
        } else {
            fa[i] = (f32)func_82185220(D_821CF294[i].pad04, (u8*)D_821CF2A0, 0) / (f32)r;
        }
        // FAKE: the dead store to r is needed for the operand order
        if (D_821CF29C[0x75] == (r = 1 << i)) {
            f20 = fa[i];
        }
        D_821CF294[i].unk_0C = fa[i];
    }
    do {
        for (i = 0; i < D_821CF288; i++) {
            if (D_821CF294[i].unk_1C == 0) {
                continue;
            }
            switch (k) {
            case 0:
                if (fa[i] - f20 < *(f32*)((u8*)D_821CF294 + 0x364)) break;
                if (func_82183CE4((s8*)D_821CF294[i].pad04) < 0x28) break;
            case 1:
            case 2:
                if (fa[i] < f20) break;
            case 3:
                if (D_821CF294[i].unk_25 & 7) break;
            case 4:
                if (D_821CF294[i].unk_5E & 1) break;
            case 5:
                if (flag && func_8218663C(D_821CF294[i].pad04, (u8*)D_821CF2A0) < 0) break;
            case 6:
                if (flag && func_8218540C((s8*)D_821CF294[i].pad04, D_821CF2A0) == 0) break;
            case 7:
                if (func_82183CE4((s8*)D_821CF294[i].pad04) < 0x37) break;
            case 8:
                if (D_821CF294[i].unk_25 & 0x20) break;
            default:
            case 9:
                *(f32*)((u8*)D_821CF294 + 0x364) = 10.0f;
                best = i;
                f20 = fa[i] - *(f32*)((u8*)D_821CF294 + 0x364);
            }
        }
        k++;
        if (flag && k == 2) {
            f20 = -1.0f;
        }
    } while (flag && best < 0);
    if (!flag) {
        if (func_82183AF0() < 0x46) {
            if (func_821855F0(D_821CF294) != 0 && func_82185684(D_821CF2A0) != 0) {
                return -1;
            }
        }
    }
    return best;
}

