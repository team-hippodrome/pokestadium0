/* Stadium Zero fragment033_35E790: geo callbacks for the demo scene models. */

#include "global.h"
#include "geo_model_033.h"
#include "geo_render.h"
#include "gfx_buffer.h"
#include "m2c_macros.h"

extern Gfx D_8F626220[];
extern Gfx D_8F626360[];
extern Gfx D_8F6264A0[];
extern Gfx D_8F6265A0[];
extern u8 D_8F626620[];

s32 func_8004D300(s32);
s32 func_8F600020(s32 arg0) {
    s32 temp_a0;

    temp_a0 = func_8004D300(1);
    if (!((*(volatile s32 *)0xA4600010) & 3) && (((*(volatile s32 *)0xB0000800) & 0xFFFF) != 1)) {
        arg0 = -1;
    }
    func_8004D300(temp_a0);
    return arg0;
}

Gfx* func_8F600088(Gfx* gfx, void* segment) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(segment));
    gSPBranchList(gfx++, D_8F626220);
    return gfx;
}

void func_8F6000E8(s32 arg0, DemoGeoNode* arg1) {
    s32 pad; // FAKE: stack padding
    DemoGeoTeam* teams;

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        arg1->displayList = Gfx_AllocDisplayList(0x10);
        func_8F600088(arg1->displayList, teams[(s32)arg1->node.callbackArg].unk_04);
        arg1->displayList = (Gfx*)func_8F600020((s32)arg1->displayList);
    }
}

void func_8F600164(s32 arg0, DemoGeoNode* arg1) {
    DemoGeoTeam* teams;

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        arg1->unk_24 = teams[(s32)arg1->node.callbackArg].unk_40[0] + 4;
    }
}

void func_8F6001A0(s32 arg0, DemoGeoNode* arg1) {
    DemoGeoTeam* teams;

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        arg1->unk_24 = teams[(s32)arg1->node.callbackArg].unk_40[0] + 0x14;
        if (*(s16*)teams[(s32)arg1->node.callbackArg].unk_40[0] & 1) {
            arg1->unk_20 = 0xD2;
        } else if (*(s16*)teams[(s32)arg1->node.callbackArg].unk_40[0] & 2) {
            arg1->unk_22 = -0xF0;
        } else {
            arg1->unk_22 = -0x12C;
        }
    }
}

void func_8F600214(s32 arg0, DemoGeoNode* arg1) {
    DemoGeoTeam* teams;
    s32 team;
    s32 slot;

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        team = ((u32)arg1->node.callbackArg >> 16) & 0xFFFF;
        slot = (u32)arg1->node.callbackArg & 0xFFFF;
        if (slot < teams[team].unk_38[0][2]) {
            D_8F626620[0] = 9;
            _bcopy(teams[team].unk_38[0] + slot * 0x50 + 0x4C, &D_8F626620[1], 0xC);
            arg1->unk_24 = D_8F626620;
        } else {
            arg1->unk_24 = NULL;
        }
    }
}

void func_8F6002C4(s32 arg0, GeoModelRootNode* arg1) {
    DemoGeoTeam* teams;

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        arg1->unk_1A = teams[arg1->rootId].unk_00 != 0;
    }
}

Gfx* func_8F600300(Gfx* gfx, void* segment) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(segment));
    gSPBranchList(gfx++, D_8F626360);
    return gfx;
}

void func_8F600360(s32 arg0, DemoGeoNode *arg1)
{
  s32 pad; // FAKE: stack padding
  DemoGeoTeam *teams;
  s32 team;
  s32 slot;
  if (arg0 == 2)
  {
    teams = D_80060490->node.callbackArg;
    team = (((u32) arg1->node.callbackArg) >> 16) & 0xFFFF;
    slot = ((u32) arg1->node.callbackArg) & 0xFFFF;
    if (slot < teams[team].unk_38[0][2])
    {
      arg1->displayList = Gfx_AllocDisplayList(0x10);
      func_8F600300(arg1->displayList, teams[team].unk_08[slot]);
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

Gfx* func_8F600420(Gfx* gfx, void* segment) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(segment));
    gSPBranchList(gfx++, D_8F6264A0);
    return gfx;
}

void func_8F600480(s32 arg0, DemoGeoNode* arg1) {
    s32 pad0; // FAKE: stack padding
    DemoGeoTeam* teams;
    s32 team;
    s32 slot;
    s32 pad1[2]; // FAKE: stack padding

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        team = ((u32)arg1->node.callbackArg >> 16) & 0xFFFF;
        slot = (u32)arg1->node.callbackArg & 0xFFFF;
        if (teams[team].unk_00 == 2) {
            if (slot % 3 < teams[team].unk_38[slot / 3][2]) {
                arg1->displayList = Gfx_AllocDisplayList(0x10);
                func_8F600420(arg1->displayList, teams[team].unk_08[slot]);
            } else {
                arg1->displayList = NULL;
            }
        } else if (slot < teams[team].unk_38[0][2]) {
            arg1->displayList = Gfx_AllocDisplayList(0x10);
            func_8F600420(arg1->displayList, teams[team].unk_08[slot]);
        } else {
            arg1->displayList = NULL;
        }
    }
}

Gfx* func_8F6005E8(Gfx* gfx, void* segment) {
    gSPSegment(gfx++, 0x0F, osVirtualToPhysical(segment));
    gSPBranchList(gfx++, D_8F6265A0);
    return gfx;
}

void func_8F600648(s32 arg0, DemoGeoNode* arg1) {
    s32 pad0; // FAKE: stack padding
    DemoGeoTeam* teams;
    s32 team;
    s32 slot;
    s32 pad1[2]; // FAKE: stack padding

    if (arg0 == 2) {
        teams = D_80060490->node.callbackArg;
        team = ((u32)arg1->node.callbackArg >> 16) & 0xFFFF;
        slot = (u32)arg1->node.callbackArg & 0xFFFF;
        if (teams[team].unk_00 == 2) {
            if (slot % 3 < teams[team].unk_38[slot / 3][2]) {
                arg1->displayList = Gfx_AllocDisplayList(0x10);
                func_8F6005E8(arg1->displayList, teams[team].unk_20[slot]);
            } else {
                arg1->displayList = NULL;
            }
        } else if (slot < teams[team].unk_38[0][2]) {
            arg1->displayList = Gfx_AllocDisplayList(0x10);
            func_8F6005E8(arg1->displayList, teams[team].unk_20[slot]);
        } else {
            arg1->displayList = NULL;
        }
    }
}
