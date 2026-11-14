/* Stadium Zero fragment032_35C390: geo callbacks for the demo scene models. */

#include "global.h"
#include "fragments/geo_model_033/geo_model_033.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"
#include "geo_model_032.h"

extern Gfx D_8F505570[];
extern Gfx D_8F5056B0[];
extern u8 D_8F505770[];

s32 func_8004D300(s32);
s32 func_8F500020(s32 arg0) {
    s32 temp_a0;

    temp_a0 = func_8004D300(1);
    if (!((*(volatile s32 *)0xA4600010) & 3) && (((*(volatile s32 *)0xB0000D10) & 0xFFFF) != 0x400)) {
        arg0 = -1;
    }
    func_8004D300(temp_a0);
    return arg0;
}

void func_8F500088(s32 arg0, GeoModelRootNode* arg1) {
    if (arg0 == 2) {
        arg1->unk_1A = D_80060490->rootId - 1;
    }
}

Gfx* func_8F5000AC(Gfx* gfx, void* segment) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(segment));
    gSPBranchList(gfx++, D_8F505570);
    return gfx;
}

void func_8F50010C(s32 arg0, DemoGeoNode* arg1) {
    s32 pad; // FAKE: stack padding
    VsSceneSide* teams;

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        arg1->displayList = Gfx_AllocDisplayList(0x10);
        func_8F5000AC(arg1->displayList, teams[(s32)arg1->node.callbackArg].trainerFile);
        arg1->displayList = (Gfx*)func_8F500020((s32)arg1->displayList);
    }
}

void func_8F500188(s32 arg0, DemoGeoNode* arg1) {
    VsSceneSide* teams;

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        arg1->unk_24 = (u8*)teams[(s32)arg1->node.callbackArg].rosterInfo[0]->title;
    }
}

void func_8F5001C4(s32 arg0, DemoGeoNode* arg1) {
    VsSceneSide* teams;

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        arg1->unk_24 = (u8*)teams[(s32)arg1->node.callbackArg].rosterInfo[0]->fullName;
        if (*(s16*)&teams[(s32)arg1->node.callbackArg].rosterInfo[0]->unk_000 & 1) {
            arg1->unk_20 = 0xD2;
        } else if (*(s16*)&teams[(s32)arg1->node.callbackArg].rosterInfo[0]->unk_000 & 2) {
            arg1->unk_22 = -0xF0;
        } else {
            arg1->unk_22 = -0x12C;
        }
    }
}

Gfx* func_8F500238(Gfx* gfx, void* segment) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(segment));
    gSPBranchList(gfx++, D_8F5056B0);
    return gfx;
}

void func_8F500298(s32 arg0, DemoGeoNode *arg1)
{
  s32 pad; // FAKE: stack padding
  VsSceneSide *teams;
  s32 team;
  s32 slot;
  if (arg0 == 2)
  {
    teams = D_80060490->node.callbackArg;
    team = (((u32) arg1->node.callbackArg) >> 16) & 0xFFFF;
    slot = ((u32) arg1->node.callbackArg) & 0xFFFF;
    if (slot < teams[team].rosterInfo[0]->numberOfPokemonCanBePicked)
    {
      arg1->displayList = Gfx_AllocDisplayList(0x10);
      func_8F500238(arg1->displayList, teams[team].iconImages[slot]);
    }
    else
    {
      arg1->displayList = 0;
      if (arg1)
      {
      }
    }
  }
}

void func_8F500358(s32 arg0, DemoGeoNode* arg1) {
    VsSceneSide* teams;
    s32 team;
    s32 slot;

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        team = ((u32)arg1->node.callbackArg >> 16) & 0xFFFF;
        slot = (u32)arg1->node.callbackArg & 0xFFFF;
        if (slot < teams[team].rosterInfo[0]->numberOfPokemonCanBePicked) {
            D_8F505770[0] = 9;
            _bcopy(teams[team].rosterInfo[0]->battleMon[slot].nickname, &D_8F505770[1], 0xC);
            arg1->unk_24 = D_8F505770;
        } else {
            arg1->unk_24 = NULL;
        }
    }
}
