/* Declarations for the battle fragment (src/fragments/battle/). */
#ifndef FRAGMENT_BATTLE_H
#define FRAGMENT_BATTLE_H

#include "global.h"
#include "moves.h"
#include "pokemon.h"
#include "m2c_macros.h"
#include "math.h"
#include "status.h"
#include "audio_manager.h"
#include "controller.h"
#include "game_state.h"
#include "poke_icon.h"
#include "table_view.h"

#define BTN_START       0x1000

typedef struct unk_func_88316214 {
    /* 0x00 */ char unk00[0x2C];
    /* 0x2C */ u8 unk_2C;
} unk_func_88316214;

typedef struct unk_func_88316304 {
    /* 0x00 */ unk_func_8830867C_02C_0CC_000** unk_00;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ char unk09[0x8];
    /* 0x11 */ u8 unk_11[1];
} unk_func_88316304;

typedef struct { f32 v; f32 pad[3]; } CameraTargetOffsetRow;

typedef struct MoveAnimInfoZ {
    /* 0x00 */ u8 pad00[2];
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u8 pad08[2];
} MoveAnimInfoZ; // size = 0xA

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment012_17ED00/battle_engine_313D60.c
 * src/fragments/fragment012_17ED00/battle_engine_317E70.c
 * src/fragments/fragment012_17ED00/battle_engine_359F90.c
 */

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment012_17ED00/battle_engine_315D50.c
 * src/fragments/fragment012_17ED00/battle_engine_315D50_2.c
 * src/fragments/fragment012_17ED00/battle_engine_315D50_3.c
 * src/fragments/fragment012_17ED00/battle_engine_343BA0_4.c
 */

typedef struct unk_D_84392040 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ char unk14[0x4];
} unk_D_84392040;

#define PARTNER_PIKACHU_CUE_BANK 152

#define DIGLETT_OB1 (DIGLETT - 1)

#define DUGTRIO_OB1 (DUGTRIO - 1)

#define ELECTRODE_OB1 (ELECTRODE - 1)

#define SQUIRTLE_OB1 (SQUIRTLE - 1)

#define WARTORTLE_OB1 (WARTORTLE - 1)

#define BLASTOISE_OB1 (BLASTOISE - 1)

#define CLOYSTER_OB1  (CLOYSTER - 1)

#define NINETY_DEGREES 0x4000

typedef struct Cue8212B270 {
    /* 0x00 */ u8 unk_00[6];
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07[3];
    /* 0x0A */ u8 unk_0A;
} Cue8212B270; // size = 0xB

typedef struct unk_D_843951D0_1010 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 unk_10;
} unk_D_843951D0_1010;

typedef struct unk_D_843951D0 {
    /* 0x0000 */ s16 unk_0000;
    /* 0x0004 */ f32 unk_0004;
    /* 0x0008 */ s16 unk_0008;
    /* 0x000A */ s16 unk_000A;
    /* 0x000C */ Vtx* unk_000C;
    /* 0x0010 */ char unk0010[0x1000];
    /* 0x1010 */ unk_D_843951D0_1010 grid[16][16];
} unk_D_843951D0;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment012_17ED00/battle_engine_361050_2.c
 * src/fragments/fragment012_17ED00/particle_math_269820.c
 */

typedef struct unk_D_86B10BE0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} unk_D_86B10BE0;

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment012_17ED00/battle_engine_361050.c
 * src/fragments/fragment012_17ED00/battle_engine_361050_2.c
 */

struct ComSide;

// One Pokémon in the COM AI's own model of a side (ComSide.battlers); see docs/annotation/com-ai.md.
typedef struct ComBattler {
    /* 0x00 */ struct ComSide* side; // set by BattleAi_InitSide
    /* 0x04 */ s32 pickScore; // @unverified: summed by the BattleAi_Add*PickScore helpers in team selection
    /* 0x08 */ f32 matchupRatio; // @unverified: best damage it deals / best damage it takes against the active opponent (BattleAi_ChooseSwitch)
    /* 0x0C */ BattleMonRuntime mon; // copied from the battle each turn (BattleAi_ChooseTurnAction), or built from party or base stats
    /* 0x70 */ u16 prevHp; // @unverified: mon.hp at the previous turn (BattleAi_ChooseTurnAction)
    /* 0x72 */ u16 damageTaken; // @unverified: prevHp - mon.hp, halved when the hit was a critical (BattleAi_ChooseTurnAction)
    /* 0x74 */ u8 species; // @unverified: party species, copied by BattleAi_InitSide
    /* 0x75 */ u8 partyBit; // @unverified: 1 << party slot (BattleAi_InitSide)
    /* 0x76 */ u8 outspedMask;
    /* 0x77 */ u8 leechSeededMask;
    /* 0x78 */ u8 moveCount; // @unverified: moves before an empty slot or Mimic (BattleAi_InitSide)
    /* 0x79 */ u8 unk_79;
    /* 0x7A */ u8 rechargeTurns;
    /* 0x7B */ u8 unk_7B;
    /* 0x7C */ u8 lastMoves[3];
    /* 0x7F */ char unk7F[0x11];
} ComBattler; // size = 0x90

// The COM AI's model of one side (D_821CF618 for the COM, D_821CF998 for its opponent).
typedef struct ComSide {
    /* 0x000 */ TeamRoster* roster;
    /* 0x004 */ ComBattler battlers[6];
    /* 0x364 */ f32 switchThreshold;
    /* 0x368 */ u8 mode;
    /* 0x369 */ u8 lastOpponentSlot;
    /* 0x36A */ u8 opponentTurnsIn;
    /* 0x36B */ u8 unk_36B;
    /* 0x36C */ u8 usableMask;
    /* 0x36D */ char unk36D[0x13];
} ComSide; // size = 0x380

/*
 * BattleSlotZ is a 0x90-byte view of the AI's side model (D_821CF618 /
 * D_821CF998) shifted by four bytes: each side is a party pointer followed by
 * six 0x90-byte battler records, and D_821CF29C / D_821CF2A0 point at a
 * record (slot + 4). In record terms the battle Pokemon (BattleMonRuntime,
 * 0x64 bytes) starts at +0xC; see docs/annotation/com-ai.md.
 */
typedef struct BattleSlotZ {
    /* 0x00 */ TeamRoster* roster;
    /* 0x04 */ u8 record[4]; // @unverified: first bytes of the 0x90-byte battler record (slot + 4); code passes its address to the BattleAi_* helpers
    /* 0x08 */ s32 pickScore;
    /* 0x0C */ f32 matchupRatio;
    /* 0x10 */ u8 pad10[0xB];
    /* 0x1B */ u8 species;
    /* 0x1C */ u16 hp;
    /* 0x1E */ u8 pad1E[7];
    /* 0x25 */ u8 status;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ u8 type1;
    /* 0x2D */ u8 type2;
    /* 0x2E */ u8 pad2E[8];
    /* 0x36 */ u8 level;
    /* 0x37 */ u8 pad37[0x27];
    /* 0x5E */ u8 unk_5E;
    /* 0x5F */ u8 pad5F[0x20];
    /* 0x7F */ u8 unk_7F;
    /* 0x80 */ u8 pad80[0x10];
} BattleSlotZ; // size = 0x90

/* Struct types that were defined identically in each of these files; this is
 * now the one definition they all include:
 * src/fragments/fragment012_17ED00/battle_engine_com_ai_2.c
 * src/fragments/fragment012_17ED00/battle_engine_com_ai_2_82184DC8.c
 */

typedef struct Move82184ADC { u8 unk00; u8 unk01; u8 power; u8 type; u8 unk04; u8 unk05; } Move82184ADC;

typedef s32 (*func_D_84390300)(void);

typedef void (*func_D_84390320)(void);

typedef struct unk_D_84390010_654_09C {
    /* 0x00 */ s32 unk00[4];
} unk_D_84390010_654_09C; // size = 0x10

typedef struct unk_D_84390010_654_0AC {
    /* 0x00 */ char unk00[0x10];
} unk_D_84390010_654_0AC; // size = 0x10

typedef struct PokemonAfterimage {
    /* 0x000 */ DisplayObject displayObject;
    /* 0x168 */ char unk168[0x1];
    /* 0x169 */ u8 minimized;
    /* 0x16A */ s16 unk_16A;
    /* 0x16C */ s16 unk_16C;
    /* 0x16E */ char unk16E[0x2];
} PokemonAfterimage; // size = 0x170

typedef struct ActivePokemonState {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ u32 selectedCommand; // 1 after A (たたかう, Fight), 2 after B (ポケモン, switch); COM's is 2 when it sends in a replacement
    /* 0x08 */ s32 rosterIndex;
    /* 0x0C */ s32 selectedMoveIndex; // move slot picked with the C buttons (1 after C-Right)
    /* 0x10 */ u32 selectedCommandOption; // 1 move menu open, 2 Pokémon menu open, 3 action committed, 0 back to idle
    /* 0x14 */ s32 moveIndex; // C button's move slot (Up 0, Right 1, Down 2, Left 3), set before the PP/Disable checks
    /* 0x18 */ u32 actionChosen;
    /* 0x1C */ u8 showingCommandOptions;
    /* 0x1E */ u16 actionDelayTimer;
    /* 0x20 */ char unk20[0x8];
    /* 0x28 */ u16 foeHpBeforeMove; // the opponent's HP when ShowDamageMessage ran, for the damage-dealt comment
    /* 0x2A */ u8 moveSelectionLocked;
    /* 0x2B */ u8 teamMemberIndex;
    /* 0x2C */ u8 prevMenuTeamMemberIndex; // @unverified: menuTeamMemberIndex before a tag-team partner took the menu (BattleMenu_TakeControlOn*)
    /* 0x2D */ u8 menuTeamMemberIndex; // @unverified: tag-team member (sessionTeams->teamMember index) whose controller drives the menus and whose party the switch menu lists
    /* 0x2E */ u8 faintState; // 0 healthy; 0x11 fainting (Battle_HandleFaint), 0x10 fainted, back to 0 at the send-out; 0x12 the side's last Pokémon reached 0 HP, 0x13 once it vanished (0xF also seen in turn.c)
    /* 0x2F */ u8 alpha;
    /* 0x30 */ u8 surrenderCursor; // こうさんしますか？ (Surrender?) prompt: 0 いいえ (No), 1 はい (Yes)
    /* 0x32 */ u16 infoBoxBlinkTimer; // counts down by 0x30 a frame; bit 8 picks the info box color
    /* 0x34 */ char unk34[0x2];
    /* 0x36 */ u16 flags;
    /* 0x38 */ u16 modelEventTrackState; // event_state of BattleAnim_TrySetModelEventTrackFromRow; 2 blocks a new track
    /* 0x3A */ BattleMonRuntime runtime;
    /* 0xA0 */ unk_D_84390010_654_09C unk_A0;
    /* 0xB0 */ unk_D_84390010_654_0AC unk_B0;
    /* 0xC0 */ s16 model;
    /* 0xC2 */ s16 transformSpecies; // species Transform copied (the target's own transformSpecies if it is transformed too)
    /* 0xC4 */ char unkC4[1];
    /* 0xC5 */ u8 moveSlotIllegality[4];
    /* 0xCC */ Controller* controller;
} ActivePokemonState; // size = 0xD0

typedef struct ThumbnailState {
    /* 0x000 */ DisplayObject displayObject;
    /* 0x168 */ CameraNode* camera;
    /* 0x16C */ s32 shownRosterIndex; // @unverified: roster slot (pokemonPicked index) of the Pokémon the thumbnail and HUD boxes show; set from state.rosterIndex in participants.c
    /* 0x170 */ s32 shownTeamMemberIndex; // @unverified: tag-team member (sessionTeams->teamMember index) owning that Pokémon; set from state.teamMemberIndex
    /* 0x174 */ s32 showing;
    /* 0x178 */ char unk178[0x4];
    /* 0x17C */ s32 side;
    /* 0x180 */ s32 idleAnimation;
    /* 0x184 */ s32 idleTimer;
    /* 0x188 */ s16 rotationX;
    /* 0x18A */ s16 rotationY;
    /* 0x18C */ f32 x;
    /* 0x190 */ s32 status;
    /* 0x194 */ f32 z;
    /* 0x198 */ f32 y;
    /* 0x19C */ char unk19C[0x4];
} ThumbnailState; // size = 0x1A0

typedef struct MonCaptionState {
    /* 0x00 */ s32 active;
    /* 0x04 */ s32 revealIndex; // byte index into fullText
    /* 0x08 */ s8 shownText[64]; // the part of fullText revealed so far, one character a frame
    /* 0x48 */ s8 fullText[64]; // formatted by ActivePokemon_ShowCaption
} MonCaptionState; // size = 0x88

typedef struct SpeciesLearnsetBuffer {
    /* 0x00 */ u8 unk_00[10];
    /* 0x0A */ u8 unk_0A[4];
    /* 0x0E */ char unk0E[0x12];
} SpeciesLearnsetBuffer; // size = 0x20

typedef struct SwayLayoutConfig {
    /* 0x00 */ Vec3f frontCameraShotOffset;
    /* 0x0C */ Vec3f backCameraShotOffset;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ char unk1C[4];
} SwayLayoutConfig; // size = 0x20

typedef struct SwayState {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f rotation;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ char unk24[0x18];
} SwayState; // size = 0x3C

typedef struct ActivePokemon {
    /* 0x000 */ DisplayObject displayObject;
    /* 0x168 */ PokemonAfterimage afterimages[3];
    /* 0x5B8 */ SwayState modelTransform;
    /* 0x5F4 */ f32 y;
    /* 0x5F8 */ f32 rotationZ;
    /* 0x5FC */ f32 oscillationAmplitude;
    /* 0x600 */ s16 oscillationVelocityEasePhase;
    /* 0x602 */ s16 oscillationPhase;
    /* 0x604 */ s16 oscillationAngularVelocity;
    /* 0x608 */ s32 doubleTeamTimer;
    /* 0x60C */ s32 facingDirection;
    /* 0x610 */ s32 modelTransformId;
    /* 0x614 */ s32 modelTransformTimer;
    /* 0x618 */ char unk618[0x4];
    /* 0x61C */ s32 animationState;
    /* 0x620 */ s32 animationTimer;
    /* 0x624 */ DisplayObject pokeBall;
    /* 0x78C */ ActivePokemonState state;
    /* 0x85C */ BattleSide* sessionTeams;
    /* 0x860 */ TeamRoster* teamRoster;
    /* 0x864 */ ThumbnailState thumbnail;
    /* 0xA04 */ MonCaptionState captionState;
    /* 0xA8C */ SpeciesLearnsetBuffer redBlueLearnsets[3];
    /* 0xAEC */ SpeciesLearnsetBuffer yellowLearnsets[3];
} ActivePokemon; // size = 0xB4C

typedef struct MovePresentationCue {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 defaultAnchor;
    /* 0x03 */ u8 alternateAnchor;
    /* 0x04 */ u8 animationDuration;
    /* 0x05 */ u8 flags1;
    /* 0x06 */ u8 currentFrame;
    /* 0x07 */ u8 endFrame;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 frameCounter;
} MovePresentationCue; // size = 0xB (Stadium 1: 0x10)

typedef struct PokemonBattleCues {
    /* 0x000 */ MovePresentationCue moveCues[165];
    /* 0x717 */ MovePresentationCue idleCues;
    /* 0x722 */ MovePresentationCue unk_722;
    /* 0x72D */ MovePresentationCue faintCue;
    /* 0x738 */ MovePresentationCue hitCue;
    /* 0x743 */ MovePresentationCue chargeCues[6];
    /* 0x785 */ MovePresentationCue sleepIdleCue;
    /* 0x790 */ MovePresentationCue flyingIdleCue;
    /* 0x79B */ MovePresentationCue unk_79B;
    /* 0x7A6 */ MovePresentationCue hitReactionOverride;
    /* 0x7B1 */ MovePresentationCue unk_7B1[5];
    /* 0x7E8 */ u8 unk_7E8;
    /* 0x7E9 */ u8 wakeUpEventTrack;
} PokemonBattleCues; // size >= 0x7EA

// moveCues[] has one entry per move, so cue indices past the last move alias the
// named cues that follow it (each MovePresentationCue is 0xB bytes in Zero).
#define BATTLE_CUE_IDLE 165       // idleCues (0x717)

#define BATTLE_CUE_A60 166        // unk_722 (0x722)

#define BATTLE_CUE_FAINT 167      // faintCue (0x72D)

#define BATTLE_CUE_HIT 168        // hitCue (0x738)

#define BATTLE_CUE_SLEEP_IDLE 175 // sleepIdleCue (0x785)

#define BATTLE_CUE_B00 176        // flyingIdleCue (0x790)

// Gen 1 type-effectiveness multipliers, in tenths; see sTypeEffectiveness.
#define TYPE_EFFECTIVENESS_NONE 0

#define TYPE_EFFECTIVENESS_NOT_VERY 5

#define TYPE_EFFECTIVENESS_NEUTRAL 10

#define TYPE_EFFECTIVENESS_SUPER 20

typedef struct BattleScene {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s8 visibilityPolicy;
    /* 0x0C */ s32 bRollShotIndex;
    /* 0x10 */ s32 substepFrameCounter;
    /* 0x14 */ s32 stepFrameTimer;
    /* 0x18 */ u16 transitionStage;
    /* 0x1A */ u8 hitReactionKind;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ s32 mode; // BattleScene_Update mode: 1 at the command menu, 2 while a turn plays out
    /* 0x20 */ s32 phaseStep;
    /* 0x24 */ s32 modelReloadStep;
    /* 0x28 */ char unk28[0x2];
    /* 0x2A */ u16 sideCurrentlySwitching;
    /* 0x2C */ u16 actingSide; // side whose action is presented (0 1P, 1 COM); flips between the two actions of a turn
    /* 0x2E */ u16 transitionStyle;
    /* 0x30 */ s32 transitionStep;
    /* 0x34 */ s32 actionPass;
    /* 0x38 */ s32 phase; // BattleScene_UpdatePhase case: 1 command, 2 first action, 3 second action, 15 Transform, ...
    /* 0x3C */ s32 phaseSubstep;
    /* 0x40 */ s32 winner; // 0 while the battle runs, otherwise the winning side + 1 (1 when 1P knocked out COM's last Pokémon)
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 moveEffectKind;
    /* 0x4C */ s32 rageFollowupPhase;
    /* 0x50 */ s32 cameraPresetId;
    /* 0x54 */ s32 easeFovAfterUserShot; // @unverified: func_8212C78C sets 1 for move camera shot 4; the effect phases then ease the camera's 0x2C toward 60
    /* 0x58 */ s16 rotationX; // camera pitch about the look-at point
    /* 0x5A */ s16 rotationY; // camera yaw about the look-at point (the B-roll orbit sweeps it)
    /* 0x5C */ f32 distance;
    /* 0x60 */ f32 verticalFieldOfView;
    /* 0x64 */ f32 stageScale; // @unverified: eased toward 1.0 and passed to Battle_SetStageScale in phases_2.c
    /* 0x68 */ f32 shakeAmplitude;
    /* 0x6C */ s16 shakeAngle; // @unverified: BattleScene_ApplyCameraShake adds 0x4000 a frame and scales shakeAmplitude by its cosine
    /* 0x6E */ s16 unk_6E;
    /* 0x70 */ char unk70[0x4];
    /* 0x74 */ f32 orbitDistance; // @unverified: eye-to-look-at distance that func_8210BCF0 measures next to rotationX/rotationY
    /* 0x78 */ char unk78[0xC];
    /* 0x84 */ Vec3f unk_84;
    /* 0x90 */ Vec3f unk_90;
    /* 0x9C */ char unk9C[0xC];
    /* 0xA8 */ Vec3f savedCameraAt; // @unverified: camera look-at saved and restored around a shot (phases.c, scene_camera.c)
    /* 0xB4 */ Vec3f savedCameraEye; // @unverified: camera eye saved and restored with savedCameraAt
    /* 0xC0 */ Vec3f anchorPosition; // @unverified: an owner's default anchor (BattleAnim_GetOwnerDefaultAnchorPosition) that camera shots orbit
    /* 0xCC */ CameraNode* camera;
} BattleScene; // size = 0xD0 (Stadium 1: 0xE0)

typedef struct unk_D_84390240 {
    /* 0x00 */ BattleScene* scene;
    /* 0x04 */ char unk04[0x3C];
} unk_D_84390240; // size = 0x40

typedef void (*BattleSceneStateCallback)(ActivePokemon*);

typedef struct BattleSceneStateRow {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ BattleSceneStateCallback unk_04[7];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 mode;
    /* 0x28 */ s32 unk_28;
} BattleSceneStateRow; // size = 0x2C

typedef struct BattleSceneStateTickSlot {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ BattleSceneStateCallback callback;
} BattleSceneStateTickSlot; // size = 0x8

typedef struct unk_D_84390178 {
    /* 0x00 */ s32 timeLeft;
    /* 0x04 */ char unk04[0x14];
} unk_D_84390178; // size >= 0x18

typedef struct SpeciesModelTransform {
    /* 0x00 */ Vec3f coordinates;
    /* 0x0C */ s16 rotationX;
    /* 0x0E */ s16 rotationY;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u16 idleTimer;
    /* 0x14 */ char unk14[0xC];
} SpeciesModelTransform; // size = 0x20

typedef struct unk_D_84390028 {
    /* 0x00 */ f32 width;
    /* 0x04 */ f32 height;
    /* 0x08 */ f32 restingHeight;
    /* 0x0C */ f32 cameraTargetOffsetY;
} ModelDimensions; // size = 0x10

typedef struct unk_D_84384608 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u16 unk_04;
} unk_D_84384608; // size = 0x8

typedef struct unk_D_843847BC {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 width;
    /* 0x08 */ f32 verticalFieldOfView;
    /* 0x0C */ f32 nearPlane;
    /* 0x10 */ f32 farPlane;
    /* 0x14 */ s16 unk_14;
} ThumbnailSettings; // size = 0x18

typedef struct unk_D_843901B0 {
    /* 0x00 */Vec3f unk_00;
    /* 0x0C */s16 unk_0C;
    /* 0x0E */s16 unk_0E;
    /* 0x10 */char unk10[0x2];
    /* 0x12 */s16 unk_12;
    /* 0x14 */s16 unk_14;
    /* 0x18 */f32 unk_18;
    /* 0x1C */f32 unk_1C;
    /* 0x20 */s16 unk_20;
    /* 0x22 */s16 unk_22;
    /* 0x24 */char unk24[0x2];
    /* 0x26 */s16 unk_26;
    /* 0x28 */s16 unk_28;
    /* 0x2C */f32 unk_2C;
    /* 0x30 */f32 unk_30;
    /* 0x34 */f32 unk_34;
    /* 0x38 */f32 unk_38;
    /* 0x3C */f32 unk_3C;
} unk_D_843901B0; // size >= 0x40

typedef struct unk_D_843901A0_4C8 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s16 unk_2A;
} unk_D_843901A0_4C8; // size = 0x2C

typedef struct unk_D_843901A0 {
    /* 0x000 */ u8 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ u8 unk_008[4];
    /* 0x00C */ char unk00C[0x3C];
    /* 0x048 */ u8 unk_048[64];
    /* 0x088 */ s8 unk_088[64];
    /* 0x0C8 */ s8 unk_0C8[64];
    /* 0x148 */ s8 unk_108[64];
    /* 0x148 */ s8 unk_148[64];
    /* 0x188 */ s8 unk_188[64];
    /* 0x1C8 */ s8 unk_1C8[64];
    /* 0x208 */ s8 unk_208[64];
    /* 0x248 */ s8 unk_248[64];
    /* 0x288 */ s8 unk_288[64];
    /* 0x2C8 */ s8 unk_2C8[64];
    /* 0x2C8 */ s8 unk_308[64];
    /* 0x348 */ s8 unk_348[64];
    /* 0x388 */ s8 unk_388[64];
    /* 0x3C8 */ s8 unk_3C8[64];
    /* 0x408 */ s8 unk_408[64];
    /* 0x448 */ s8 unk_448[2][64];
    /* 0x4C8 */ unk_D_843901A0_4C8 unk_4C8;
} unk_D_843901A0; // size = 0x4F4

typedef struct unk_D_84385790 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Color_RGBA8 unk_04;
} unk_D_84385790; // size = 0x8

typedef struct arg1_func_84344CE8 {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ u8* unk_14;
    /* 0x18 */ Gfx* unk_18;
} arg1_func_84344CE8; // size >= 0x1C

typedef struct arg1_func_8434E21C {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u8* unk_04;
    /* 0x08 */ char unk08[0x2];
    /* 0x0A */ s16 unk_0A;
} arg1_func_8434E21C; // size >= 0xC

typedef struct RibbonMeshVertexState {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ Color_RGBA8 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
} RibbonMeshVertexState; // size = 0x1C

typedef struct RibbonMesh {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ f32 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ s16 unk_018;
    /* 0x01A */ s16 unk_01A;
    /* 0x01C */ s16 unk_01C;
    /* 0x01E */ s16 unk_01E;
    /* 0x020 */ f32 unk_020;
    /* 0x024 */ s32 unk_024;
    /* 0x028 */ s32 unk_028;
    /* 0x02C */ s32 unk_02C;
    /* 0x030 */ s32 unk_030;
    /* 0x034 */ s32 unk_034;
    /* 0x038 */ s32 unk_038;
    /* 0x03C */ s32 unk_03C;
    /* 0x040 */ s32 unk_040;
    /* 0x044 */ s32 unk_044;
    /* 0x048 */ char unk048[0x8];
    /* 0x050 */ Vtx unk_050[31 * 2];
    /* 0x430 */ RibbonMeshVertexState unk_430[31 * 2];
} RibbonMesh; // size = 0xAF8

typedef struct unk_D_843975E8 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ char unk24[0x4];
} unk_D_843975E8; // size = 0x28

typedef struct Radial20Node {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ char unk28[0x20];
} Radial20Node; // size = 0x48

typedef struct Radial20 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ Color_RGBA8 unk_00A; // Stadium 1 follows this with a Color_RGB8
    /* 0x010 */ f32 unk_014;
    /* 0x014 */ f32 unk_018;
    /* 0x018 */ Vtx* unk_01C;
    /* 0x01C */ char unk020[0x18];
    /* 0x034 */ s32 unk_038[3];
    /* 0x040 */ Radial20Node unk_048[20];
} Radial20; // size = 0x5E0 (Stadium 1: 0x5E8)

typedef struct Trail40Node {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} Trail40Node; // size = 0x1C

typedef struct Trail40 {
    /* 0x0000 */ s16 unk_0000;
    /* 0x0002 */ s16 unk_0002;
    /* 0x0004 */ s16 unk_0004;
    /* 0x0008 */ f32 unk_0008;
    /* 0x000C */ Vtx* unk_000C;
    /* 0x0010 */ Mtx* unk_0010;
    /* 0x0014 */ Trail40Node unk_0014[16][16];
} Trail40; // size >= 0x1C14

typedef struct Trail40VariantNode {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ f32 unk_1C;
} Trail40VariantNode; // size = 0x20

typedef struct Trail40Variant {
    /* 0x0000 */ s16 unk_0000;
    /* 0x0002 */ s16 unk_0002;
    /* 0x0004 */ s16 unk_0004;
    /* 0x0008 */ f32 unk_0008;
    /* 0x000C */ Vtx* unk_000C;
    /* 0x0010 */ Mtx* unk_0010;
    /* 0x0014 */ Trail40VariantNode unk_0014[16][16];
} Trail40Variant; // size >= 0x2014

typedef struct TexturedRibbonSheetNode {
    /* 0x00 */ f32 unk_00;
    /* 0x08 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ Vtx unk_30[2];
} TexturedRibbonSheetNode; // size = 0x50

typedef struct TexturedRibbonSheet {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ Color_RGB8 unk_00A;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ char unk01C[0x1C];
    /* 0x038 */ TexturedRibbonSheetNode unk_038[10];
} TexturedRibbonSheet; // size = 0x358

typedef struct FourStreamTrailNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
} FourStreamTrailNode; // size = 0x44

typedef struct FourStreamTrail {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ Vec3f unk_01C;
    /* 0x028 */ char unk028[0xC];
    /* 0x034 */ FourStreamTrailNode unk_034[15];
} FourStreamTrail; // size = 0x430

typedef struct OwnerLinkedFourStreamNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
} OwnerLinkedFourStreamNode; // size = 0x44

typedef void (*unk_D_8140E728_01C_004_1_04)(struct Particle*, s32, struct ParticleDescriptorChild*);

typedef void (*unk_D_8140E728_01C_004_1_08)(struct Particle*, s32, struct ParticleDescriptorChild*);

typedef struct unk_D_8140E728_01C_00C_1 {
    /* 0x00 */ s32 arg;
} unk_D_8140E728_01C_00C_1;

typedef union unk_D_8140E728_01C_00C {
    s32 arg;
    unk_D_8140E728_01C_00C_1* s;
} unk_D_8140E728_01C_00C;

typedef struct ParticleDescriptorChild {
    /* 0x00 */ u8 unk_00;
    /* 0x00 */ u8 unk_01;
    /* 0x00 */ s16 unk_02;
    /* 0x04 */ unk_D_8140E728_01C_004_1_04 unk_04;
    /* 0x08 */ unk_D_8140E728_01C_004_1_08 unk_08;
    /* 0x0C */ unk_D_8140E728_01C_00C unk_0C;
} ParticleDescriptorChild; // size = 0x10

typedef void (*ParticleRenderCallback)(struct Particle*, CameraNode*);

typedef union ParticleDescriptorPayload {
    ParticleDescriptorChild* a;
    ParticleRenderCallback func;
} ParticleDescriptorPayload;

typedef struct ParticleDescriptor {
    /* 0x00 */ s32 kind; /* unk_04: 1 = a, 3 = func */
    /* 0x04 */ ParticleDescriptorPayload payload;
} ParticleDescriptor; // size = 0x08

typedef void (*ParticleUpdateCallback)(struct Particle*);

/*
 * Same record as Stadium 1's Particle, but 4 bytes shorter: from 0x28 on, every
 * field sits 4 bytes lower than in Stadium 1 (unk_XX names keep the Stadium 1
 * offset). Field names follow Stadium 1. @unverified
 */
typedef struct Particle {
    /* 0x00 */ struct Particle* next;
    /* 0x04 */ struct Particle* prev;
    /* 0x08 */ ParticleUpdateCallback updateCallback;
    /* 0x0C */ ParticleDescriptor* descriptor;
    /* 0x10 */ struct ActivePokemon* pokemon;
    /* 0x14 */ DisplayObject* displayObject;
    /* 0x18 */ u32 flags;
    /* 0x1C */ f32 scale;
    /* 0x20 */ f32 scaleTarget;
    /* 0x24 */ f32 scaleStep;
    /* 0x28 */ Vec3f worldPosition;
    /* 0x34 */ Vec3f positionOffset;
    /* 0x40 */ char unk44[0xC];
    /* 0x4C */ Vec3f motionOffset;
    /* 0x58 */ Vec3f motionTarget;
    /* 0x64 */ Vec3f origin;
    /* 0x70 */ f32 stepMagnitude;
    /* 0x74 */ f32 magnitudeStep;
    /* 0x78 */ Vec3f motionStep;
    /* 0x84 */ char unk88[0xC];
    /* 0x90 */ Vec3s rotation;
    /* 0x96 */ Vec3s rotationStep;
    /* 0x9C */ Vec3s rotationTarget;
    /* 0xA2 */ s16 unk_A6;
    /* 0xA4 */ s16 unk_A8;
    /* 0xA6 */ s16 unk_AA;
    /* 0xA8 */ s16 unk_AC;
    /* 0xAA */ s16 unk_AE;
    /* 0xAC */ s16 unk_B0;
    /* 0xAE */ s16 lifecycle;
    /* 0xB0 */ char unkB4[0x2];
    /* 0xB2 */ s16 frameTimer;
    /* 0xB4 */ s16 phase;
    /* 0xB6 */ s16 phaseTimer;
    /* 0xB8 */ s16 delayTimer;
    /* 0xBA */ u8 prim_r;
    /* 0xBB */ u8 prim_g;
    /* 0xBC */ u8 prim_b;
    /* 0xBD */ u8 env_r;
    /* 0xBE */ u8 env_g;
    /* 0xBF */ u8 env_b;
    /* 0xC0 */ u8 prim_a;
    /* 0xC1 */ char unkC5[0x1];
    /* 0xC2 */ s8 loopsRemaining;
    /* 0xC3 */ s8 textureFrame;
    /* 0xC4 */ char unkC8[0x2];
    /* 0xC6 */ u8 unk_CA;
    /* 0xC7 */ u8 unk_CB;
    /* 0xC8 */ u8 unk_CC;
    /* 0xC9 */ u8 unk_CD;
    /* 0xCA */ u8 unk_CE;
    /* 0xCB */ u8 unk_CF;
    /* 0xCC */ s8 allocated;
} Particle; // size = 0xD0

typedef struct OwnerLinkedFourStream {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ Vec3f unk_01C;
    /* 0x028 */ char unk028[0xC];
    /* 0x034 */ Particle* unk_034;
    /* 0x038 */ OwnerLinkedFourStreamNode unk_038[15];
} OwnerLinkedFourStream; // size = 0x434

typedef struct OwnerAnchoredFourStreamNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
} OwnerAnchoredFourStreamNode; // size = 0x44

typedef struct OwnerAnchoredFourStream {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x010 */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ Vtx* unk_014;
    /* 0x018 */ Particle* unk_018;
    /* 0x01C */ OwnerAnchoredFourStreamNode unk_01C[15];
    /* 0x418 */ f32 unk_418;
} OwnerAnchoredFourStream; // size = 0x41C

typedef struct Trail50EffectNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ Vec3f unk_38;
    /* 0x44 */ Vec3f unk_44;
} Trail50EffectNode; // size = 0x50

typedef struct Trail50Effect {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ Color_RGB8 unk_00A;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ char unk01C[0x4];
    /* 0x020 */ Vtx* unk_020;
    /* 0x024 */ Vec3f unk_024;
    /* 0x030 */ char unk030[0x10];
    /* 0x040 */ Trail50EffectNode unk_040[10];
} Trail50Effect; // size = 0x360

typedef struct unk_D_843C2C00_0B0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
} unk_D_843C2C00_0B0; // size = 0x28

typedef struct unk_D_843C2C00_064 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_843C2C00_064; // size = 0xC

typedef struct unk_D_843C2C00_024 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} unk_D_843C2C00_024; // size = 0x20

typedef struct unk_D_84389CE0 {
    /* 0x00 */ Color_RGBA8 unk_00;
    /* 0x04 */ u8 unk_04;
} unk_D_84389CE0; // size = 0x8

typedef struct DoubleTextureTrail {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ s32 unk_01C;
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ unk_D_843C2C00_024 unk_024;
    /* 0x044 */ unk_D_843C2C00_024 unk_044;
    /* 0x064 */ unk_D_843C2C00_064 unk_064;
    /* 0x070 */ unk_D_843C2C00_064 unk_070;
    /* 0x07C */ unk_D_84389CE0 unk_07C;
    /* 0x081 */ unk_D_84389CE0 unk_081;
    /* 0x086 */ Color_RGBA8 unk_086;
    /* 0x08C */ f32 unk_08C;
    /* 0x090 */ f32 unk_090;
    /* 0x094 */ s16 unk_094;
    /* 0x096 */ char unk096[0x1A];
    /* 0x0B0 */ unk_D_843C2C00_0B0 unk_0B0[10];
} DoubleTextureTrail; // size = 0x240

typedef struct AuxiliaryEffectNode {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
} AuxiliaryEffectNode; // size = 0x18

typedef struct AuxiliaryEffect {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ char pad002[2];
    /* 0x004 */ AuxiliaryEffectNode unk_004[20];
} AuxiliaryEffect; // size = 0x1E4

typedef struct unk_D_843C3508_0A4 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
} unk_D_843C3508_0A4; // size = 0x24

typedef struct unk_D_843C3508 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ unk_D_84389CE0 unk_008;
    /* 0x00D */ unk_D_84389CE0 unk_00D;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ s16 unk_01C;
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ s32 unk_024;
    /* 0x028 */ unk_D_843C2C00_024 unk_028;
    /* 0x048 */ unk_D_843C2C00_024 unk_048;
    /* 0x068 */ unk_D_843C2C00_064 unk_068;
    /* 0x074 */ unk_D_843C2C00_064 unk_074;
    /* 0x080 */ f32 unk_080;
    /* 0x084 */ f32 unk_084;
    /* 0x088 */ Vtx* unk_088;
    /* 0x08C */ char unk08C[0x18];
    /* 0x0A4 */ unk_D_843C3508_0A4 unk_0A4[20];
} unk_D_843C3508; // size = 0x374

typedef struct StatStageMultiplier {
    /* 0x00 */ u8 multiplier;
    /* 0x01 */ u8 divisor;
} StatStageMultiplier; // size = 0x2

typedef struct TypeEffectivenessEntry {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
} TypeEffectivenessEntry; // size = 0x3

typedef struct unk_D_843C6148 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk06[0x2];
} unk_D_843C6148; // size <= 0x8

struct Particle;

struct ParticleDescriptorChild;

struct ActivePokemon;

struct BattleAnimEffectSlot;

typedef struct ParticleEmitter {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ Vec3f origin;
    /* 0x10 */ Vec3s rotation;
    /* 0x18 */ ParticleUpdateCallback updateCallback;
    /* 0x1C */ ParticleDescriptor* descriptor;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s8 unk_2A;
    /* 0x2B */ s8 unk_2B;
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
    /* 0x2E */ u8 unk_2E; // 0 healthy; 0x11 fainting (Battle_HandleFaint), 0x10 fainted, back to 0 at the send-out; 0x12 the side's last Pokémon reached 0 HP, 0x13 once it vanished (0xF also seen in turn.c)
    /* 0x2F */ u8 unk_2F;
} ParticleEmitter; // size = 0x30

typedef void (*func_unk_D_8140E724)(struct Particle*);

typedef struct BattleAnimEffectSlot {
    /* 0x00 */ func_unk_D_8140E724 unk_00;
    /* 0x04 */ ParticleDescriptor* unk_04;
    /* 0x08 */ struct ActivePokemon* unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s8 unk_14;
    /* 0x15 */ s8 unk_15;
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
} BattleAnimEffectSlot; // size = 0x1C

typedef struct arg1_func_81407874_014_000_014_000_000 {
    /* 0x00 */ Color_RGBA8 color;
    /* 0x04 */ u8 l;
} arg1_func_81407874_014_000_014_000_000; // size = 0x5

typedef struct arg1_func_81407874_014_000_018_000_000 {
    /* 0x00 */ Color_RGBA8 color;
} arg1_func_81407874_014_000_018_000_000; // size = 0x4

typedef union arg1_func_81407874_014_000_014_000 {
    arg1_func_81407874_014_000_014_000_000* ptr5;
    arg1_func_81407874_014_000_018_000_000* ptr4;
    Color_RGBA8_u32 color;
    u8** texture;
} arg1_func_81407874_014_000_014_000; // size = 0x4

typedef struct arg1_func_81407874_014_000_014 {
    /* 0x00 */ arg1_func_81407874_014_000_014_000 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} arg1_func_81407874_014_000_014; // size >= 0x08

typedef struct arg1_func_81407874_014_000_01C {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
} arg1_func_81407874_014_000_01C; // size >= 0x04

typedef struct arg1_func_81407874_014_000 {
    /* 0x00 */ struct arg1_func_81407874_014_000* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk08[0x8];
    /* 0x10 */ arg1_func_81407874_014_000_010* unk_10;
    /* 0x14 */ arg1_func_81407874_014_000_014* unk_14;
    /* 0x18 */ arg1_func_81407874_014_000_014* unk_18;
    /* 0x1C */ arg1_func_81407874_014_000_01C* unk_1C;
} arg1_func_81407874_014_000; // size >= 0x20

typedef struct arg1_func_81407874_014_004_008 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
} arg1_func_81407874_014_004_008; // size >= 0xA

typedef struct arg1_func_81407874_014_004_004 {
    /* 0x00 */ s16 fmt;
    /* 0x02 */ s16 size;
    /* 0x04 */ s16 width;
    /* 0x06 */ s16 height;
    /* 0x08 */ s16 cms;
    /* 0x0A */ s16 cmt;
    /* 0x0C */ s16 masks;
    /* 0x0E */ s16 maskt;
    /* 0x10 */ s16 shfits;
    /* 0x12 */ s16 shiftt;
} arg1_func_81407874_014_004_004; // size >= 0x14

typedef struct arg1_func_81407874_014_004 {
    /* 0x00 */ arg1_func_81407874_014_000* unk_00;
    /* 0x04 */ arg1_func_81407874_014_004_004* unk_04;
    /* 0x08 */ arg1_func_81407874_014_004_008* unk_08;
    /* 0x0C */ arg1_func_81407874_014_000_014* unk_0C;
} arg1_func_81407874_014_004; // size >= 0x4

typedef struct arg1_func_81407874_014 {
    /* 0x00 */ arg1_func_81407874_014_000* unk_00;
    /* 0x04 */ arg1_func_81407874_014_004* unk_04;
} arg1_func_81407874_014; // size >= 0x8

typedef struct arg1_func_81407874 {
    /* 0x00 */ char unk00[0x14];
    /* 0x00 */ arg1_func_81407874_014* unk_14;
} arg1_func_81407874; // size >= 0x18

typedef struct ParticleCameraState {
    /* 0x00 */ MtxF viewMatrix;
    /* 0x40 */ Vec3f eyePosition;
    /* 0x4C */ Vec3f targetPosition;
    /* 0x58 */ Vec3f lookDirection;
    /* 0x64 */ Vec3f eyeDirection;
    /* 0x70 */ s16 unk_70;
    /* 0x72 */ s16 unk_72;
    /* 0x74 */ char unk74[0x2];
    /* 0x76 */ s16 unk_76;
    /* 0x78 */ s16 unk_78;
} ParticleCameraState; // size = 0x7C

typedef struct ParticleRenderContext {
    /* 0x00 */ Vec3f scale;
    /* 0x0C */ CameraNode* camera;
    /* 0x10 */ ParticleCameraState cameraState;
} ParticleRenderContext; // size = 0x8C

typedef struct ParticleMatrixPool {
    /* 0x0000 */ MtxF unk_0000[364];
    /* 0x5B00 */ char unk5B00[0x80];
    /* 0x5B80 */ Mtx unk_5B80;
    /* 0x5BC0 */ char unk5BC0[0x20];
} ParticleMatrixPool; // size = 0x5BE0



typedef struct unk_D_82F20A88 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ s16 unk_00A;
    /* 0x00C */ s16 unk_00C;
    /* 0x00E */ s16 unk_00E;
    /* 0x010 */ s16 unk_010;
    /* 0x012 */ s16 unk_012;
    /* 0x014 */ s16 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ f32 unk_01C;
    /* 0x020 */ f32 unk_020;
    /* 0x024 */ u8* unk_024;
    /* 0x028 */ DisplayObject unk_028;
} unk_D_82F20A88; // size = 0x190

#include "gfx_rect.h"
#include "stage_loader.h"

extern unk_D_843901B0 gCameraPreset;

extern f32 gCameraDistTarget;

extern f32 D_8219A534;

extern s32 pad_86104B64[];

extern const f32 D_FLT_82196258;

extern const f64 D_DBL_82196260;

extern const f32 D_FLT_82196268;

extern f32 D_8219A530;

extern f32 D_FLT_82196274;

extern s32 pad_D_84390210[4];

extern s32 sMultihitCount;

extern s32 sMultihitCountdown;

extern ActivePokemon* D_84390200;

extern s32 D_84390220;

extern s32 D_84390224;

extern s32 D_8219A560;

extern s32 D_8219A564;

extern f32 D_FLT_821962A4;

extern s32 D_8219A568;

extern ActivePokemon* D_84390204;

extern f32 D_FLT_821963A0;

extern f32 D_FLT_821963A4;

extern f32 D_FLT_821963A8;

extern MoveAnimInfoZ D_80073D90[];

extern s32 D_8219A578;

extern s8 D_8218B008;

extern s8 D_8218B014;

extern s8 D_8219597C;

extern f32 D_FLT_82199EB0;

extern f32 D_FLT_82199EB4;

extern Color_RGB8 D_84385860[];

extern unk_D_84385790 D_84385790[];

extern u8 D_030096C0[];

extern u8 D_03009440[];

extern u8 D_03009840[];

extern u8 D_030094C0[];

extern u8 D_030097C0[];

extern u8 D_03009940[];

extern u8 D_030098C0[];

extern u8 D_030095C0[];

extern u8 D_03009740[];

extern u8 D_03009640[];

extern u8 D_030078C0[];

extern u8 D_03007A80[];

extern u8 D_030077E0[];

extern u8 D_0300A080[];

extern u8 D_0300A200[];

extern u8 D_030070E0[];

extern u8 D_030072A0[];

extern u8 D_03007380[];

extern u8 D_03007540[];

extern u8 D_03009E40[];

extern u8 D_03009FC0[];

extern Gfx D_80060308[];

extern u8* D_8218AFDC[];

extern M2C_UNK D_82195BE4;

extern s32 D_8218B15C[];

extern s32 D_8219A5A4;

extern u8* sBattleAnimAssetPointers[256];

extern s16 sBattleAnimResourceList[0x10];

extern arg1_func_80019420* sBattleAnimResourceTablePointers[40];

extern s16 D_8219CAC0;

extern s16 D_8219CAC2;

extern Mtx D_8219CAC8;

extern s16 D_8219CB08;

extern s16 D_8219CB0A;

extern s16 D_8219CB0C;

extern s16 D_8219CB0E;

extern s16 D_8219CB10;

extern s16 D_8219CB12;

extern s16 D_8219CB14;

extern s16 D_8219CB16;

extern s16 D_8219CB18;

extern s16 D_8219CB1A;

extern const char D_821978C8[];

extern PokemonBattleCues sSide1BattleCues;

extern PokemonBattleCues sSide2BattleCues;

extern SpeciesModelTransform sSide1PresentationTransform;

extern SpeciesModelTransform sSide2PresentationTransform;

extern ActivePokemon* sActivePokemon[2];

extern ActivePokemon* sSide1ActivePokemon;

extern ActivePokemon* sSide2ActivePokemon;

extern MovePresentationCue* sCurrentAnimation;

extern ModelDimensions sPokemonModelDimensions[2];

extern SwayLayoutConfig sDefaultSwayLayout;

extern BattleSceneStateTickSlot sBattleSceneStateTickSlots[7];

extern s32 sBattleSceneStateTickSlotIndex;

extern PokemonBattleCues* sSideBattleCues[];

extern SpeciesModelTransform* sSidePresentationTransform[];

extern u8 sPokemonWithAlternateSleepIdle[];

extern u8 sPokemonWithAlternateSleepHitReactions[];

extern u8 sPokemonWithNewHmInYellow[];

extern u8 sCharizardLearnsFlyInYellow[];

extern u8 sButterfreeLearnsFlashInYellow[];

extern u8 sVenonatLearnsFlashInYellow[];

extern u8 sVenomothLearnsFlashInYellow[];

extern u8 sDiglettLearnsCutInYellow[];

extern u8 sDugtrioLearnsCutInYellow[];

extern u8 sKabutopsLearnsCutInYellow[];

extern u8 sMewtwoLearnsNothingNewInYellow[];

extern u8 sMewLearnsNothingNewInYellow[];

extern u8* sPokemonYellowHmAdditions[];

extern u8 sAerodactyl;

extern u8 sFearow;

extern u8 sFarfetchD;

extern u8 sDoduoEvoLine[];

extern char** sBattleMessagesTable;

extern char** sPokemonNameTable;

extern char** sMoveNameTable;

extern char** sStatusConditionNameTable;

extern char** sBattleControllerDisconnectedMessage;

extern f32 sModelTransformConstants[];

extern s16 sChargeMoveCues[];

extern ThumbnailSettings sSideThumbnailSettings[2];

extern BattleSceneStateCallback sBattleSceneStateTickSentinel;

extern BattleSceneStateRow sBattleSceneStateRowTable[];

extern M2C_UNK D_8218E6A8;

extern s16 D_8219A80A;

extern M2C_UNK func_82153C50;

extern const f32 D_FLT_82196EC8;

extern const f32 D_FLT_82196ECC;

extern M2C_UNK D_8218E700;

extern M2C_UNK func_82154248;

extern ParticleDescriptor D_8218E580[];

extern M2C_UNK D_8218E7A0;

extern M2C_UNK func_82152FB0;

extern M2C_UNK func_821624FC;

extern M2C_UNK func_82154EA4;

extern M2C_UNK D_8218E720;

extern M2C_UNK func_82155380;

extern M2C_UNK D_8218E798;

extern M2C_UNK D_8218E7D0;

extern M2C_UNK func_82155724;

extern M2C_UNK D_8218E650;

extern M2C_UNK func_82152F44;

extern M2C_UNK func_821626F4;

extern M2C_UNK func_82156B0C;

extern M2C_UNK D_8218E708;

extern M2C_UNK func_82159F70;

extern M2C_UNK D_8218E728;

extern M2C_UNK func_82162C68;

extern M2C_UNK func_82153040;

extern M2C_UNK func_8215B904;

extern M2C_UNK D_8218E5F8;

extern M2C_UNK D_8218E5D8;

extern M2C_UNK func_821530F4;

extern M2C_UNK D_8218E7A8;

extern M2C_UNK D_8218E770;

extern M2C_UNK func_8215DCE8;

extern M2C_UNK func_8215DFB4;

extern M2C_UNK D_8218E7F8;

extern M2C_UNK func_82152FE0;

extern M2C_UNK func_8215ED1C;

extern M2C_UNK func_8215EFF8;

/*
 * BattleAnim_AcidArmorParticleUpdateB
 *
 * Particle initializer: sets the particle's scale to 0.2, recolours its
 * primitive/environment colors from its descriptor's palette pair, sets
 * the primitive alpha to 0xC8, stores 0x18 with Particle_FieldA6_SetS16_0BCA8,
 * sets the float at offset 0x70 (the donor calls it stepMagnitude; the
 * value, 0.02 in the donor, is the rodata float D_FLT_82197730 here) and
 * advances the particle's lifecycle.
 *
 * Same sequence as
 * BattleAnim_SetupHydroPumpColorShiftFade
 * in the Stadium 1 decomp.  The 0xC8 alpha is passed as -0x38 in the retail
 * code (the same byte).
 */
extern f32 D_FLT_82197730;

extern const f32 D_FLT_82197734;

extern const f32 D_FLT_82197850;

extern const f32 D_FLT_82197854;

extern Vec3f D_8219A880;

extern const f32 D_FLT_8219786C;

extern M2C_UNK D_8218E610;

extern M2C_UNK D_8218E788;

extern M2C_UNK func_82162938;

extern M2C_UNK D_8218E6C8;

extern M2C_UNK D_8218E6D0;

extern s32 D_8219A814;

extern M2C_UNK D_8218E6D8;

extern M2C_UNK D_8218E790;

extern M2C_UNK D_8218E7B0;

extern M2C_UNK func_82163540;

extern M2C_UNK D_8218E7C8;

extern M2C_UNK D_8218E7D8;

extern M2C_UNK func_821640A0;

extern M2C_UNK D_8218E768;

extern M2C_UNK func_821655C0;

extern s32 D_8219A570;

extern u8* D_8218B2F4[];

extern u8 D_8219A4F4;

extern u8 D_80073D84[];

extern u8* D_8218B320[];

extern s32 D_84390228;

extern const f32 D_FLT_82196668;

extern const f32 D_FLT_8219666C;

extern char D_82196650[];

extern char D_8219665C[];

/*
 * BattleAnim_RunSonicBoomUseFourStream
 *
 * Per-frame update of the "four stream trail" part of effect 45: counts
 * frames in D_8219CAC0 (returns -1, which ends the effect, from frame 0x32
 * on).  During the first four frames (counter < 4) it starts one trail at the
 * secondary owner's bone position: the trail leaves in a direction in the
 * Y/Z plane given by an angle of (counter % 3) * pi / 3 + pi/6 (the sine and
 * cosine of that angle, normalized together with a 1.0 X component and
 * then scaled by 20), at X speed +-10 (negative when the start X is
 * negative), with color 0xC0FFFF, alpha 0x80, a random +-0.3 drift and
 * fixed shape parameters 2.0, 13.0 and 0x28.  From frame 2 on it returns
 * whether the trail has completed (FourStreamTrail_IsComplete), else 0.
 *
 * Same code as BattleAnim_RunSonicBoomUseFourStream in the Stadium
 * 1 decomp.  pi (D_FLT_82197934), pi/6 as a double (D_DBL_82197938) and 0.3
 * (D_DBL_82197940) are read from the retail rodata because this file's own
 * rodata is not placed; the names of the values are inferred from their use
 * and the donor source's M_PI_F, 0.5235987901687622 and 0.3.
 */
extern f32 D_FLT_82197934;

extern f64 D_DBL_82197938;

extern f64 D_DBL_82197940;

extern const f32 D_FLT_82197948;

extern const f32 D_FLT_8219794C;

extern const f32 D_FLT_82197950;

extern const f32 D_FLT_82197954;

extern const f32 D_FLT_82197958;

extern const f32 D_FLT_8219795C;

extern const f32 D_FLT_82197960;

extern const f32 D_FLT_82197974;

extern const f32 D_FLT_82197964;

extern const f32 D_FLT_82197968;

extern const f32 D_FLT_8219796C;

extern const f32 D_FLT_82197970;

extern const f32 D_FLT_82197978;

extern const f32 D_FLT_8219797C;

extern const f32 D_FLT_82197980;

extern const f32 D_FLT_82197984;

extern const f32 D_FLT_82197988;

extern const f32 D_FLT_8219798C;

extern const f32 D_FLT_82197990;

extern RibbonMesh D_8219CB20[4];

extern s16 D_8219F700;

extern s16 D_8219F702;

extern unk_D_843951D0 sWaterHeightMap;

extern s16 D_821A1B20;

extern s16 D_821A1B22;

extern s16 D_821A1B24;

extern unk_D_843975E8 D_821A1B28;

extern Gfx D_82192890[];

extern s32 pad_D_84388F78[2];

extern const f64 D_DBL_821979B8;

extern const f32 D_FLT_821979C0;

extern const f64 D_DBL_821979C8;

extern const f64 D_DBL_821979D0;

extern const f64 D_DBL_821979D8;

extern const f64 D_DBL_821979E0;

extern const f64 D_DBL_821979E8;

extern const f64 D_DBL_821979F0;

/**
 * Samples the Surf water surface (sWaterHeightMap) at world position (x, z).
 *
 * Returns the water height (world Y) at that point and writes the surface tilt
 * in degrees, in the range [-90, 90], to *rotation_x. The surface is a 16x16
 * grid of vertices, so the height is found by picking the grid cell under
 * (x, z), picking one of the cell's two triangles, and evaluating that
 * triangle's plane at (x, z).
 *
 * Called by BattleAnim_SurfContinue to keep the Surf rider on the wave:
 * the return value is added to the model's base height and the tilt becomes its
 * X rotation. Also called by SurfTerrainGrid_Draw to compare the camera-aligned
 * quad corners against the water surface.
 * //@src/fragments/battle_engine/battle_engine_2F3CB0.c
 * //@src/fragments/battle_engine/battle_engine_347330.c SurfTerrainGrid_UpdateWaves
 */

extern const f64 D_DBL_82197A28;

extern const f64 D_DBL_82197A30;

extern const f64 D_DBL_82197A38;

extern const f32 D_FLT_82197A40;

extern const f32 D_FLT_82194900;

extern const f32 D_FLT_82194904;

extern const f32 D_FLT_82194908;

extern const f32 D_FLT_8219490C;

extern const f32 D_FLT_82194910;

extern Vec3f D_821891CC;

extern const f64 D_DBL_82194920;

extern ParticleDescriptor gBattleAnimParticleDescriptors[86];

extern Gfx D_82193350[];

extern Gfx D_821941F0[];

extern StatStageMultiplier gStatStageMultipliers[];

extern u8 sTypeEffects[];

extern u8* sSide1PokemonThumbnailImage;

extern u8* sSide2PokemonThumbnailImage;

extern u8 sBattleMoveFailed;

extern u8 sBattleCritFlag;

extern s32 sTypeEffectiveness;
extern u8 sConfused;

extern u8 sStatCanBeChangedFurther;

extern u16 sBattleDamage;

extern BattleMonRuntime* sBattleUser;

extern BattleMonRuntime* sBattleTarget;

extern unk_D_843901A0* gBattleMessageQueues;

extern unk_D_84390240 sBattleScene;

extern s32 gBattleAnimFrameCounter;

extern s32 gBattleAnimSpawnDelay;

extern s16 gBattleAnimCurrentAnchor;

extern s16 gBattleAnimDefaultAnchor;

extern ActivePokemon* gBattleAnimCurrentOwner;

extern ActivePokemon* gBattleAnimSecondaryOwner;

extern ActivePokemon* gBattleAnimTertiaryOwner;

extern s32 D_811842A0;

extern s32 D_8219A830;

extern func_D_84390300 gBattleAnimEffectUpdateFuncs[8];

extern func_D_84390320 gBattleAnimEffectDrawFuncs[8];

extern s16 gSavedPrimColorR;

extern s16 gSavedPrimColorG;

extern s16 gSavedPrimColorB;

extern s16 gSavedPrimColorA;

extern s16 gPrimColorR;

extern s16 gPrimColorG;

extern s16 gPrimColorB;

extern s16 gPrimColorA;

extern s16 gEnvColorR;

extern s16 gEnvColorG;

extern s16 gEnvColorB;

extern s16 gEnvColorA;

extern s16 gFogColorR;

extern s16 gFogColorG;

extern s16 gFogColorB;

extern s16 gFogColorA;

extern s16 gBlendColorR;

extern s16 gBlendColorG;

extern s16 gBlendColorB;

extern s16 gBlendColorA;

extern f32 D_8219C590[26];

extern Gfx gDL_ItemIcon[];

extern Gfx D_821904C8[];

extern Gfx D_82190548[];

extern Gfx gDL_BeginUIOverlay[];

extern Gfx gDL_EndColorFill[];

extern Gfx gDL_BeginColorFill[];

extern Vtx gVtx_UI_TriangleSmall[];

extern Vtx gVtx_UI_TriangleLarge[];

extern Vtx gVtx_UI_RectVertical[];

extern Vtx gVtx_UI_ComplexQuad[];

extern Vtx gFullscreenQuadVtx[];

extern Gfx gDL_PanelBackground[];

extern ParticleDescriptor gDefaultParticleDescriptor;

extern u8 gParticlePaletteSetA[];

extern ParticleMatrixPool* gParticleMatrixPool;

extern s32 gParticleMatrixPoolIndex;

extern ParticleRenderContext gParticleRenderContext;

extern ParticleCameraState* gParticleCameraState;

extern u32 gParticleFrameCounter;

extern s32 gParticleFrameMod64;

extern s32 gParticleFrameMod32;

extern s32 gParticleFrameMod16;

extern s32 gParticleFrameMod8;

extern s32 gParticleFrameMod4;

extern u32 gParticleFrameMod3;

extern s32 gParticleFrameMod2;

extern u32 gParticleFrameDiv64;

extern u32 gParticleFrameDiv32;

extern u32 gParticleFrameDiv16;

extern u32 gParticleFrameDiv8;

extern u32 gParticleFrameDiv4;

extern u32 gParticleFrameDiv3;

extern u32 gParticleFrameDiv2;

extern s32 gParticleFrameDiv64Parity;

extern s32 gParticleFrameDiv32Parity;

extern s32 gParticleFrameDiv16Parity;

extern s32 gParticleFrameDiv8Parity;

extern s32 gParticleFrameDiv4Parity;

extern s32 gParticleFrameDiv3Parity;

extern s32 gParticleFrameDiv2Parity;

extern s32 gParticleRandomOffset;

extern Particle* gParticlePool;

extern BattleAnimEffectSlot* gBattleAnimEffectSlots;

extern ParticleEmitter* gMiniFxEmitters;

extern s32 gParticlePoolIndex;

extern s32 gBattleAnimEffectSlotIndex;

extern s32 gMiniFxEmitterIndex;

// libnumus/player.c
void Audio_FadeCategoriesAndStreams(s32);
s32 Team_IsOpponentIndexUsed(s32 arg0);

// stage.c
s32 Battle_StageGeoDispatchCallback(s32 event, GraphNode* node);
s32 Battle_StageLightAngleCallbackA(s32 event, unk_D_86002F34_alt18* light);
s32 Battle_StageMaterialTintCallback(s32 event, DisplayObject* object);
void Battle_SetStageTintColor(u8 r, u8 g, u8 b);
void Battle_SetStageScale(f32 scale);
void Battle_DrawStageBackdrop(void);
void Battle_RenderActivePokemonThumbnail(GraphNode* thumbnail_root, DepthBuffer* thumbnail);
void Battle_DrawClippedTextureRect(s32 x1, s32 y1, s32 x2, s32 y2);
void Battle_DrawTexturedRectSegment(s32 x1, s32 y1, s32 draw_width, s32 height, u8* texture, s32 load_width);
void Battle_FillActivePokemonThumbnail(GraphNode* thumbnail_root, DepthBuffer* thumbnail);
void Battle_ResetFaintBatches(void);
void Battle_UpdateFaintBatches(void);
void func_82100CB8(void);
s32 BattleScene_UpdateFrame(s32 fade_mode);
s32 BattleScene_UpdatePausedFrame(s32 fade_mode);
void Battle_UpdateCompletionGate(void);
s32 Battle_FrameCallback(s32 fade_mode);
void Battle_CompleteRosterOrder(u8* roster_order, s32 number_of_pokemon_picked);
void Battle_SelectComRoster(void);
void BattleScene_InitializeParticipantPresentation(BattleSide* side, unk_D_86002F30* model);
void func_82100CC0(void);
void func_8210186C(void);

// move_animation.c
s32 Battle_ClearRuntimeFlags(s8 *arg0, unsigned short arg1);
void func_8210568C(ActivePokemon*, s32, s32);
s32 func_82105724(ActivePokemon*, s32);
s32 func_821058E8(ActivePokemon* arg0, s32 arg1);
void func_821061A8(ActivePokemon*);
s32 func_82105C8C(ActivePokemon*, s32);
void func_82105E64(ActivePokemon*);
void func_82107160(ActivePokemon*);
void func_82101B54(ActivePokemon*, s32);
void func_8210626C(ActivePokemon*);
s32 func_821057D4(ActivePokemon*, s32);
void BattleScene_ClearStateTickCallbacks(void);
void BattleScene_QueueRowEffectList3(ActivePokemon* actor, s32 effect_entry);
void BattleAnim_PlayMoveEffectScript(ActivePokemon* user, s32 move_id);
void BattleAnim_PlayChargingMoveEffectScript(ActivePokemon* user, s32 move_id);
void BattleAnim_PlayMoveEffectEnd(ActivePokemon* user, s32 move_id);
void BattleScene_TickClearAnimRecordIfLoaded(ActivePokemon* active_pokemon);
void BattleScene_TickStartRowAnimRecord(ActivePokemon* active_pokemon);
void BattleScene_TickQueueRowEffectList3AtAnimEnd(ActivePokemon* active_pokemon);
void BattleScene_ResetOpponentStateFrameCounter(ActivePokemon* active_pokemon);
void BattleAnim_SetFlagForRockThrowingMoves(ActivePokemon* active_pokemon);
void BattleAnim_ClearRockThrowingMoveFlag(ActivePokemon* active_pokemon);
s32 BattleAnim_IsAssetLoadBusy(s8 *arg0);
s32 BattleAnim_TryRegisterAssetTables(ActivePokemon* active_pokemon);
void BattleScene_LoadMoveResourceList(ActivePokemon* active_pokemon);
void BattleScene_LoadRowResourceList(ActivePokemon* active_pokemon);
void BattleScene_TickRow10CleanupAndEnterState18(ActivePokemon* active_pokemon);
void Battle_HandleStatBoostingMoveAnimation(ActivePokemon* active_pokemon);
void BattleScene_TickRow22PlaySpeciesSound(ActivePokemon* active_pokemon);
void BattleScene_StartHitCueAnimation(ActivePokemon* active_pokemon);
void BattleScene_TickRow1PlayOwnerCry(ActivePokemon* active_pokemon);
void BattleScene_TickQueueRowEffectList3OnFirstFrame(ActivePokemon* active_pokemon);
void BattleScene_TickRow21CleanupAndEnterState18(ActivePokemon* active_pokemon);
void BattleScene_ResetOwnerModelIfLoaded(ActivePokemon* active_pokemon);
void BattleScene_EnterChargeTurnRow(ActivePokemon* active_pokemon);
void BattleScene_TickRow8PlayMoveEffectScriptB(ActivePokemon* active_pokemon);
void BattleScene_EnterRow9QueueEffectList6(ActivePokemon* active_pokemon);
void BattleScene_Row13PlaySequences14And21(ActivePokemon* active_pokemon);
void BattleScene_TickQueueList3Selector2OrCFromB10(ActivePokemon* active_pokemon);
void BattleScene_StateCallbackNop(ActivePokemon* active_pokemon);
void BattleScene_RegisterStateTickCallback(ActivePokemon* active_pokemon, BattleSceneStateCallback callback);
void BattleScene_SetOpponentEventTrackA6(ActivePokemon* active_pokemon);
void BattleScene_EnterStateRow(ActivePokemon* active_pokemon, s32 row_index);
void BattleScene_TickStateCallbacks(void);
void BattleAnim_SetModelEventTrackFromRow(ActivePokemon* pokemon, s32 cue_index);
s32 BattleAnim_TrySetModelEventTrackFromRow(ActivePokemon* active_pokemon, s32 cue_index, s32 event_state);
s32 BattleScene_IsRowWaitCompleteWithEventCount(ActivePokemon* active_pokemon, s32 frame_limit);
s32 BattleScene_IsMoveKeyedRowWaitComplete(ActivePokemon* active_pokemon, s32 frame_limit);
s32 BattleScene_IsRowAnimWaitComplete(ActivePokemon* active_pokemon, s32 frame_limit);
void BattleScene_ResetBothParticipantsAnimationState(void);
void BattleScene_CleanupOpponentSpecialAnimFlag(ActivePokemon* active_pokemon);
void BattleScene_CleanupOpponentAnimationFlags(ActivePokemon* active_pokemon);
void BattleScene_CleanupParticipantEffectMode(ActivePokemon* active_pokemon);
void BattleAnim_TriggerStatusAfflictionCry(ActivePokemon* active_pokemon);
void BattleScene_AllocateParticipantRecord(BattleSide* session_teams, s32 side_index);
void BattleScene_AllocateParticipants(BattleSide* battle_teams);
void BattleScene_InitializeParticipantController(ActivePokemon* active_pokemon);
void BattleScene_InitializePresentation(UNUSED BattleSide* session_teams);
void BattleScene_ResetParticipantAuxTransform(UNUSED ActivePokemon* owner, ActivePokemon* active_pokemon, s32 facing_direction);
void BattleScene_InitializeRuntime(BattleSide* session_teams);
void BattleScene_UpdateParticipantsAndQueueEffects(UNUSED ActivePokemon* side1_pokemon, UNUSED ActivePokemon* side2_pokemon);
s32 BattleScene_DispatchLifecycle(s32 lifecycle_stage, BattleSide* session_teams);
void BattleThumbnail_TriggerOwnerModelAnimation(ActivePokemon* active_pokemon);
void BattleThumbnail_ClearBothOwnerIdleFlags(void);
void BattleThumbnail_SetBothOwnerIdleFlags(void);
void BattleThumbnail_SetFlagToUpdatePokemonThumbnail(CameraNode* camera);
void BattleThumbnail_LoadOwnerCameraFramingConstants(ActivePokemon* active_pokemon);
void Battle_InitMessageQueues(void);
void BattleAnim_ResetFreezeStatusAndRestoreAnimation(ActivePokemon* active_pokemon);

// thumbnail.c
void BattleThumbnail_SetupOwnerCameraFraming(ActivePokemon* side1_pokemon, ActivePokemon* side2_pokemon);
void BattleThumbnail_OwnerCameraLifecycleNop(void);
void BattleThumbnail_ApplyOwnerCameraFraming(ActivePokemon* active_pokemon);
void BattleThumbnail_TickOwnerCameraFraming(ActivePokemon* active_pokemon);
void BattleThumbnail_TickOwnerSlideIn(ActivePokemon* active_pokemon, s32 delta);
void BattleThumbnail_TickOwnerSlideAnimation(ActivePokemon* active_pokemon);
void BattleThumbnail_TickBothOwnerSlideAnimations(ActivePokemon* side1_pokemon, ActivePokemon* side2_pokemon);
s32 BattleThumbnail_DispatchOwnerCameraLifecycle(s32 state, CameraNode* side1_camera_node, CameraNode* side2_camera_node);

// participants.c
s16 BattleScene_GetParticipantFacingAngle(ActivePokemon* arg0);
void func_82108A0C(ActivePokemon* active_pokemon);
void func_821089D0(ActivePokemon*);
void func_8210881C(ActivePokemon*);
s16 func_82107B54(ActivePokemon*);
M2C_UNK func_82107790(s8 *);                      /* extern */
void BattleScene_InitializeParticipantModel(ActivePokemon* active_pokemon);
void BattleScene_InitializeParticipantOwnerModel(ActivePokemon* active_pokemon);
void BattleScene_InitializeParticipantSecondaryModels(ActivePokemon* active_pokemon, UNUSED s32* secondary_models);
void BattleScene_InitializeParticipantAuxiliaryModel(ActivePokemon* active_pokemon);
void BattleScene_PositionParticipantModel(ActivePokemon* active_pokemon);
f32 BattleScene_GetParticipantModelXOffset(ActivePokemon* active_pokemon);
void BattleScene_SetParticipantModelScale(ActivePokemon* arg0, f32 arg1);
s32 BattleScene_GetParticipantSideIndex(ActivePokemon* active_pokemon);
u8 BattleScene_GetMoveCueDefaultAnchor(ActivePokemon* active_pokemon);
u8 BattleScene_GetMoveCueAlternateAnchor(ActivePokemon* active_pokemon);
s16 BattleScene_GetHitCueDefaultAnchor(ActivePokemon* active_pokemon);
void BattleScene_GetParticipantModelRotation(ActivePokemon* arg0, Vec3s* arg1);
u16 Battle_GetActiveMonHp(ActivePokemon* active_pokemon);
s32 BattleAnim_GetSpeciesBySideIndex(s32 arg0);
s32 BattleAnim_GetOwnerSpecies(ActivePokemon* active_pokemon);
u8 BattleScene_IsParticipantModelVisible(ActivePokemon* active_pokemon);
void BattleScene_GetParticipantModelPosition(ActivePokemon* arg0, Vec3f* arg1);
f32 BattleScene_GetParticipantModelRadiusScaled(ActivePokemon* active_pokemon);
ModelNodeView* Battle_GetLoadedModelNode(ActivePokemon* active_pokemon, s32 node_index);
void Battle_ReturnToIdleAnimIfFinished(ActivePokemon* active_pokemon, ActivePokemon* animated_pokemon);
void Battle_ResetModelToIdleAnim(ActivePokemon* active_pokemon);
void Battle_SetModelToHitAnim(ActivePokemon* active_pokemon);
void BattleScene_RebindParticipantTeamMember(ActivePokemon* arg0, s32 arg1);
s32 Battle_FreezeClauseInEffect(ActivePokemon* active_pokemon);
s32 Battle_SleepClauseInEffect(ActivePokemon* active_pokemon);
void BattleScene_ReinitParticipantBodyModel(ActivePokemon* owner, ActivePokemon* pokemon, s16 object_type);
void BattleScene_ReinitParticipantThumbnailModel(ActivePokemon* arg0, ThumbnailState* arg1, s16 arg2);
void BattleScene_ReinitParticipantAfterimages(ActivePokemon* arg0, s16 arg1);
void Battle_ResetEventTrack(ActivePokemon* active_pokemon);
void Battle_LoadOwnerModelForSpecies(ActivePokemon* active_pokemon);
void Battle_LoadOwnerModelForSwitchIn(ActivePokemon* active_pokemon);
void Battle_ResetOwnerModelToSubstituteDoll(ActivePokemon* active_pokemon);
void Battle_ReloadSubstituteDoll(ActivePokemon* active_pokemon);
void Battle_ReloadDisplayModel(ActivePokemon* active_pokemon);
f32 BattleAnim_GetSpeciesBaseScale(ActivePokemon* active_pokemon);

// model_transforms.c
void BattleScene_ShowSecondaryModelsStaggeredFrame(ActivePokemon* active_pokemon);
void BattleAnim_InitSwayOffset(ActivePokemon* pokemon, f32 y, s16 theta);
void BattleAnim_UpdateTransform(ActivePokemon* owner, ActivePokemon* animated_pokemon, f32 height, f32 delta_y, s32 delta_theta);
void BattleAnim_UpdateSwayPhysicsToTarget(UNUSED ActivePokemon* owner, ActivePokemon* animated_object, f32 target, f32 delta, s32 theta0, s32 theta1);
void BattleScene_HideParticipantSecondaryModels(ActivePokemon* active_pokemon);
/*
 * BattleScene_ShowSecondaryModelsAtMainTransform
 *
 * Resets the three trailing afterimage models of a Pokemon so that they show
 * at the main model's transform: for afterimages 0..2 it clears the field at
 * +0x16C of the entry and the byte at +0x185 (lodFraction), sets bit 0 of the
 * node flags, stores a per-afterimage value in the halfword at +0x16A (0, 0xE38
 * and 0xF1C8 for the three), and copies the main display object's position
 * (+0x24), rotation (+0x1E) and scale (+0x30) into the afterimage.
 *
 * The local six-byte array is placed at D_821891A8. The orbit
 * helpers use a separate data region recovered for this split.
 *
 * Same code as BattleScene_ShowSecondaryModelsAtMainTransform in the Stadium
 * 1 decomp, except that Zero loops over three afterimages where the donor
 * loops over two.
 */
void BattleScene_ShowSecondaryModelsAtMainTransform(ActivePokemon* pokemon);
void BattleScene_UpdateSecondaryModelOrbit(ActivePokemon* pokemon);
void BattleScene_ShowSecondaryModelsAtMainPose(ActivePokemon* active_pokemon);
s32 func_82109824(ActivePokemon* arg0);
M2C_UNK func_821099CC(s8 *);                      /* extern */
M2C_UNK func_82109764(s8 *);                      /* extern */
M2C_UNK func_8210942C(s32);                         /* extern */

// model_transforms_2.c
void BattleScene_UpdateSecondaryModelTrailPosition(ActivePokemon* pokemon, s16 new_position);
void BattleScene_ResetParticipantModelFlags(ActivePokemon* active_pokemon);
void BattleAnim_WaterfallEnd(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
s32 BattleAnim_ApproachAngleAndCheckThreshold(ActivePokemon* pokemon, s16 phase, s16 camera_offset_scale);
void BattleAnim_WithdrawContinue(ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_DrawParticleNoop(UNUSED Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_PokeBallThrowStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_PokeBallThrowContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_PokeBallThrow(s32 arg0, s8 *arg1);
void BattleAnim_PokeBallLandStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_PokeBallLandContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
M2C_UNK func_82109E60();                         /* extern */
M2C_UNK func_82109EF8(s32, s8 *);                 /* extern */
void BattleAnim_PokeBallLand(s32 arg0, s8 *arg1);
void BattleAnim_FlyStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_FlyContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
M2C_UNK func_82109FFC(s32);                         /* extern */
M2C_UNK func_8210A084(s32, s8 *);                 /* extern */
void BattleAnim_Fly(s32 arg0, s8 *arg1);
void BattleAnim_WaterfallStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_WaterfallContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Waterfall(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210A2F4(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210A374(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210A3DC(s32 arg0, s8 *arg1);
void BattleAnim_SubmissionStart(s32 arg0, s8 *arg1);
M2C_UNK func_82109AF4(s8 *, s16);                 /* extern */
s32 func_8210A430(s32, s16, s16);                   /* extern */
void BattleAnim_SubmissionContinue(s32 arg0, s8 *arg1);
void BattleAnim_SubmissionEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210A584(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_Submission(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_DigStart(s32 arg0, s8 *arg1);
void BattleAnim_DigContinue(s32 arg0, s8 *arg1);
void func_8210A7D8(s32 arg0, s8* arg1);
void BattleAnim_Dig(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_AgilityStart(s32 arg0, s8 *arg1);
void BattleAnim_AgilityContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_AgilityEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210A9B4(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210AAA4(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_Agility(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_DoubleTeamStart(s32 arg0, s8 *arg1);
void BattleAnim_DoubleTeamContinue(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_DoubleTeam(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_ResetOwnerFacingAndExitStatusIdle(ActivePokemon* arg0);
void BattleAnim_SeismicTossStart(s32 arg0, s8 *arg1);
void BattleAnim_SeismicTossContinue(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210AE34(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_SeismicToss(ActivePokemon* owner, ActivePokemon* animated_pokemon);
M2C_UNK func_82109C88(s8 *);                      /* extern */
void BattleAnim_MinimizeStart(s8 *arg0, s8 *arg1);
void BattleAnim_MinimizeContinue(s32 arg0, s32 arg1);
void BattleAnim_Minimize(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_WithdrawStart(s32 arg0, s8 *arg1);
void func_8210B164(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Withdraw(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_MeditateStart(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_MeditateContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_MeditateEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210B2C4(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void func_8210B3F0(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void func_8210B280(UNUSED ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Meditate(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_SquishHitReactionStart(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_SquishHitReactionContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
M2C_UNK func_8210B58C(s32);                         /* extern */
M2C_UNK func_8210B5C8(s32, s8 *);                 /* extern */
void BattleAnim_SquishHitReaction(s32 arg0, s8 *arg1);
void BattleAnim_BindHitReactionStart(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_BindHitReactionContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
M2C_UNK func_8210B824(s32, s8 *);                 /* extern */
void BattleAnim_BindHitReaction(s32 arg0, s8 *arg1);
void BattleAnim_SurfStart(s32 arg0, s8 *arg1);
void BattleAnim_SurfContinue(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_Surf(ActivePokemon* owner, ActivePokemon* animated_pokemon);
void BattleAnim_PlayTransformInducingAnimation(s32 side_index);

// anim_math.c
void BattleAnim_CalculateDistanceAngles(Vec3f* arg0, Vec3f* arg1, f32* arg2, s16* arg3, s16* arg4);
Vec3f* BattleAnim_Vec3fSetZero(Vec3f* arg0);
Vec3f* BattleAnim_Vec3fOffsetByPolarXZ(Vec3f* arg0, Vec3f* arg1, f32 arg2, s16 arg3);
void BattleAnim_Vec3fSetPolarXZ(Vec3f* dest_vector, f32 magnitude, s16 theta);
Vec3f* BattleAnim_Vec3fCopy(Vec3f* dest, Vec3f* src);
Vec3s* BattleAnim_Vec3sCopy(Vec3s* arg0, Vec3s* arg1);
Vec3f* BattleAnim_Vec3fScaleComponents(Vec3f* arg0, f32 arg1, f32 arg2, f32 arg3);
s16 BattleAnim_Atan2sFromPoints(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
f32 BattleAnim_Vec3fDistance(Vec3f arg0, Vec3f arg1);
f32 BattleAnim_Distance2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
u16 BattleAnim_RandomRange(s32 range);
s32 BattleAnim_StepToS16(s16* dest, s16 finish, s16 rate);
void BattleAnim_ApproachF(f32* dest, f32 value, f32 speed);
void BattleAnim_ApproachS16(s16* dest, s16 value, s16 speed);
void BattleAnim_ApproachU16(u16* dest, u16 value, s16 speed);
void Battle_ComputeSplineWeightsVariantA(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantB(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantC(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantD(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantE(f32* arg0, f32 arg1);

// command_menu.c
void BattleScene_SelectActiveController(ActivePokemon* active_pokemon);
s32 BattleScene_HandleCpuFaintedSwitch(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleScene_CompleteCpuForcedAction(ActivePokemon* arg0, UNUSED ActivePokemon* arg1);
void BattleScene_AutoConfirmCpuMove(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleScene_ApplyCpuChoice(ActivePokemon* arg0, ActivePokemon* arg1);
s32 BattleScene_ApplyCpuSwitchChoice(ActivePokemon* arg0, ActivePokemon* arg1);
s32 BattleScene_CollectCpuAction(ActivePokemon* arg0, ActivePokemon* arg1);
s32 BattleScene_ValidateSelectedPartyMember(ActivePokemon* active_pokemon);
void BattleScene_ConfirmForcedMoveRepeat(ActivePokemon* active_pokemon);
s32 BattleScene_HandlePlayerActionInput(ActivePokemon* active_pokemon);
s32 BattleScene_HandlePlayerFaintedSwitch(ActivePokemon* arg0, ActivePokemon* arg1);
void BattleScene_CollectPlayerAction(ActivePokemon* arg0, ActivePokemon* arg1);

// damage_estimate.c
s32 BattleScene_FindU16InByteArray(u16 lookup_value, u8* array, s32 array_length);
void BattleScene_IntroInitNop(void);
u8 Battle_Random(void);
u16 BattleAi_ApplyMoveEffectDamageOverride(BattleMonRuntime* arg0, BattleMonRuntime* arg1);
void BattleAi_ClampDamageRatio(void);
void BattleAi_PrepareDamageCalcState(BattleMonRuntime* arg0, BattleMonRuntime* arg1, u8 arg2);

// turn_order.c
void func_8210F4E0(void);
void func_8210FA74(void);
void ShowDamageMessage(s32 arg0, s32 arg1);
void Battle_ResetTransientRuntimeState(s32 arg0, s32 arg1);
void Battle_FormatDamageComment(ActivePokemon* active_pokemon);
u16 Battle_DetermineMoveOrder(ActivePokemon* arg0, ActivePokemon* arg1);
s32 IsByteInArray(u8 arg0, u8* arg1, s32 arg2);
void Battle_SetActiveMoveFromSlotIndex(void);
s32 Battle_CheckMoveSuccess(void);
void ComputePokemonStat(s32 arg0, BattleMon* arg1);

// damage.c
void ActivePokemon_CommitPendingStatus(ActivePokemon*);
void ComputeAllPokemonStats(BattleMon* arg0);
void InitBattleParameters(void);
s32 Battle_CalcDamage(void);
void Battle_ApplyDamage(void);
void Battle_DecrementPP(s32 arg0);
void Battle_MoveHitTest(void);
void ApplyParalysisSpeedCut(ActivePokemon* active_pokemon);
void ApplyBurnAttackCut(ActivePokemon* active_pokemon);
void Battle_InitPokemonRuntimeState(ActivePokemon* active_pokemon);
void func_82110FB0(void);
void func_82110FB8(void);
void Battle_LoadMoveCache(void);
void Battle_HandleBuildingRage(void);
void Battle_DisplayEffectiveness(void);
void Battle_PrintCriticalOHKOText(void);
void Battle_ApplyAttackToTarget(void);
void Battle_PrintMoveFailureText(void);
void Battle_RefundSelectedMovePp(void);
s32 Battle_Effect_Metronome(void);
void Battle_ApplyPoisonOrBurnDamage(void);
void Battle_ApplyLeechSeedDamage(void);
s32 Battle_ApplyResidualEffects(void);
void func_82111870(void);

// turn.c
void BattleAnim_EffectEndNop(void);
s32 Battle_TryLoadFollowupMoveFromTarget(void);
void Battle_ApplyTypeEffectAndSTAB(void);
s32 Battle_Effect_Counter(void);
s32 Battle_CheckCriticalHit(void);
s32 Battle_CheckMonCanAct(void);
void ProcessBattleTurn(void);
void Battle_HandleFaint(ActivePokemon* active_pokemon);
void Battle_CheckAllBroughtFainted_PoisonBurn(ActivePokemon* active_pokemon);
void Battle_CheckAllBroughtFainted_LeechSeed(ActivePokemon* active_pokemon);
void Battle_CheckAllBroughtFainted_PendingHp(ActivePokemon* active_pokemon);
void Battle_CheckAllBroughtFainted_Hp(ActivePokemon* active_pokemon);
s32 Battle_CheckSideDefeatAfterResidualStatus(ActivePokemon* active_pokemon);
s32 Battle_CheckFaintAfterMove(void);
void Battle_ResolveMonAction(void);
void BeginBattleForEntity(ActivePokemon* active_pokemon);

// move_effects_status.c
void func_82113660(void);
void Battle_Effect_Sleep(void);
void Battle_Effect_Poison(void);
void Battle_Effect_DrainHP(void);
void BattleEffect_Explosion(void);
void BattleEffect_ApplyStatBoost(void);
void Battle_Effect_LowerStat(void);

// move_effects.c
void BattleEffect_Bide(void);
void BattleEffect_Thrash(void);
void Battle_Effect_ForceSwitchOrFlee(void);
void BattleEffect_MultiHit(void);
void Battle_Effect_Flinch(void);
void BattleEffect_OHKO(void);
void Battle_Effect_Mist(void);
void Battle_Effect_FocusEnergy(void);
void Battle_Effect_Recoil(void);
void Battle_Effect_ConfuseChance(void);
void Battle_Effect_Confuse(void);
void Battle_Effect_Paralyze(void);
void Battle_Effect_Substitute(void);
void BattleEffect_Recharge(void);
void BattleEffect_Rage(void);
void BattleEffect_Mimic(void);
void Battle_Effect_LeechSeed(void);
void Battle_Effect_Splash(void);
void Battle_Effect_Disable(void);
void Battle_Effect_PayDay(void);
void Battle_Effect_Conversion(void);
void Battle_Effect_Haze(void);
void Battle_Effect_Heal(void);
void Battle_Effect_Transform(void);
void Battle_Effect_ReflectLightScreen(void);
void BattleEffect_RunMoveEffect(void);
void BattleEffect_ExecuteMoveEffect(void);

// gradient_rect.c
M2C_UNK func_82116CF4(s32, s32, M2C_UNK, M2C_UNK, s8 *, s8 *); /* extern */
void func_82116480(s8* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawTranslucentShadowRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void Battle_DrawGradientRectWrapper(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void Ui_DrawGradientRectangle(s32 x1, s32 y1, s32 width, s32 height, Color_RGB8* top_color,
                              Color_RGB8* bottom_color);

// hud_mon_info.c
void func_82116D20(void);
void func_82116D28(void);
s32 BattleHud_DrawBorderTile(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4);
void ParticleEffect_InitNoop(void);
void BattleHud_DrawLevelNumber(s32 arg0, s32 arg1, s32 arg2);
void BattleHud_DrawHpFractionText(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BattleHud_DrawTrainerNameLabel(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4);
void BattleHud_DrawTrainerNameLabelBlink(s16 arg0, s16 arg1, s32 arg2, s32 arg3, u16 arg4, s32 arg5);
void BattleHud_DrawTrainerNameLabelAuto(ActivePokemon* arg0, TeamRoster* arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s32 arg6);
void BattleHud_DrawMonInfoBox(ActivePokemon* arg0, BattleMon* arg1, unk_D_84385790* arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);

// hud_status_boxes.c
void func_82117610(s16 x, s16 y);
void func_8211778C(s16 x, s16 y);
void BattleHud_DrawPartyBallRow(ActivePokemon* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawMonStatusBoxPlayer(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void BattleHud_DrawMonStatusBoxOpponent(ActivePokemon* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void BattleHud_DrawTextCentered(s32 arg0, s32 arg1, s32 arg2);

// menu_panels.c
void BattleHud_DrawPlainText(s16 arg0, s16 arg1, char* arg2);
void BattleScene_DrawStripWipeIfActive(void);
s32 BattleHud_DrawMovePpTextLTR(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BattleHud_DrawMovePpTextRTL(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BattleMenu_DrawSwitchPanelEntry(TeamRoster* arg0, BattleMon* arg1, s32 arg2, s32 arg3, s32 arg4);
void BattleDebug_DrawCameraLabel(s16 arg0, s16 arg1);
void BattleHud_DrawCompactMonStatusBox(ActivePokemon* arg0, s16 arg1, s16 arg2, s32 arg3);

// message.c
void Battle_ClearAllMessageQueues(void);
void Battle_ClearMessageCursor(void);
void Battle_SimpleStringFormat(s8* arg0, s8* arg1, ...);
void Battle_DrawCompactStatusBoxesIfVisible(void);
void BattleScene_ResetMessageQueue(void);
void Battle_RenderHud(void);
void func_8211F3E4(void);
void func_8211F3EC(void);

// broll_camera.c
s32 BattleScene_AreBothParticipantModelsCompact(void);
s32 BattleScene_SkipUnavailableBRollShot(UNUSED ActivePokemon* arg0, CameraNode* arg1);
void BattleScene_BRollCameraSetupArenaOrbit(CameraNode* arg0);
void BattleScene_BRollCameraSetupRotatingArenaOverview(CameraNode* arg0);
void BattleScene_SelectNextBRollCameraShot(CameraNode* arg0);
void BattleScene_BRollCameraUpdateArenaOrbit(CameraNode* arg0);
void BattleScene_BRollCameraUpdateRotatingArenaOverview(CameraNode* arg0);
void BattleScene_BRollCameraUpdatePresetHold(CameraNode* arg0);
void BattleScene_InitializeBattlePresentation(CameraNode* arg0);
void func_8211F580(void);

// broll_camera_2.c
void BattleScene_UpdateBRollCameraSequence(CameraNode* arg0);

// scene_camera.c
f32 BattleScene_ScaleCameraDistance(ActivePokemon* arg0, f32 arg1, f32 arg2);
s32 BattleScene_AdvanceCameraSubstepCounter(s32 arg0);
s32 BattleScene_AdvanceCameraFrameCounter(s32 frame_limit);
s32 BattleScene_AdvanceCameraFrameCounterUntil(s32 arg0);
s32 BattleScene_IsCameraFrameCounterAtLeast(s32 arg0);
void BattleScene_SetActivePokemonIndex(s32 arg0);
void BattleScene_ResetCameraFrameCounter(void);
void BattleScene_ResetCameraSubstepCounter(void);
void BattleScene_SetCameraAtAndEyeFromAngles(CameraNode* camera, f32 x, f32 y, f32 z, f32 distance, s16 rotation_x, s16 rotation_y);
void BattleScene_SetCameraModeAndStep(s32 camera_mode, s32 camera_step);
void BattleScene_SetCameraClipPlanes(CameraNode* camera_node, f32 near_plane, f32 far_plane);
void BattleScene_SetCameraSubstate(s32 arg0, u16 arg1);
s32 BattleScene_IsCameraAngleSettled(s16 arg0, s16 arg1);
void BattleScene_SetCameraAtFromPosition(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeFromPosition(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeFromAt(CameraNode* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void BattleScene_SetCameraEyeAndStoreAngles(CameraNode* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeAndStoreAnglesFromAt(CameraNode* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void BattleScene_CameraHelperNop(UNUSED CameraNode* arg0);
void BattleScene_RecenterCameraOnOwner(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_ApproachCameraZoom(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraAnglesAndDistance(s16 arg0, s16 arg1, f32 arg2);
void BattleScene_SetCameraAtFromAnchor(ActivePokemon* arg0, CameraNode* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6);
void BattleScene_GetParticipantCameraAnchor(ActivePokemon* arg0, Vec3f* arg1);
void BattleScene_SetDamageShakeAmplitude(ActivePokemon* arg0);
void BattleScene_ApplyCameraShake(CameraNode* arg0);
s32 BattleScene_ApproachCameraRotationY(s32 arg0, s16 arg1, s16 arg2);
s32 BattleScene_ApproachCameraRotationYNoEyeUpdate(UNUSED CameraNode* arg0, s16 arg1, s16 arg2);
void BattleScene_ClearCameraOffsetVectors(void);
void func_821227C0(CameraNode*, ActivePokemon*);
void func_821228B0(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_ApproachCameraTarget(CameraNode* arg0, ActivePokemon* arg1);
void func_82123314(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraOwnerWideShot(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraPresetClose(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraPresetHighClose(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraPresetLowClose(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_CameraShotTargetClose(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_CameraShotTargetHigh(CameraNode* arg0, ActivePokemon* arg1);
void func_82123F44(CameraNode* arg0, ActivePokemon* arg1);
void func_82124054(CameraNode* arg0, ActivePokemon* arg1);
void func_82124194(CameraNode* arg0, ActivePokemon* arg1);
void func_82122684(s32, s16, s16, f32, f32);
M2C_UNK func_821218AC(s32, s32, f32, s32, f32, s32, s32); /* extern */
void BattleCamera_CaptureModelOrbit(ActivePokemon* arg0, CameraNode* arg1);
void func_821229AC(CameraNode* arg0, ActivePokemon* arg1);
s32 func_821217DC(s32);
s32 func_82121798(s32);
s32 func_82121820(M2C_UNK);                         /* extern */
s32 func_82122DFC(CameraNode*, ActivePokemon*);
void func_82121EB0(ActivePokemon*);
void func_82122B9C(CameraNode*, ActivePokemon*);
void func_82122A7C(CameraNode*, ActivePokemon*);
void func_821233EC(CameraNode*, ActivePokemon*);

// scene_camera_2.c
void BattleScene_SetCameraPresetCloseThunk(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraPresetHighCloseThunk(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_SetCameraPresetLowCloseThunk(CameraNode* arg0, ActivePokemon* arg1);
void BattleScene_CameraShotTargetCloseThunk(CameraNode* arg0, ActivePokemon* arg1);
void func_821247D0(CameraNode* arg0, ActivePokemon* arg1);
// Called with (CameraNode*, ActivePokemon*); the arguments pass through untouched.

void func_82124894(CameraNode* arg0, ActivePokemon* arg1);

// owner_animation.c
void BattleScene_ResetAnimationStep(void);
s32 func_82124A50(ActivePokemon* arg0);
s32 BattleScene_AdvanceOwnerAnimation98(ActivePokemon* arg0);
s32 func_82124BF8(ActivePokemon* arg0);
s32 BattleScene_AdvanceBothOwnerAnimations(void);
s32 func_82124B30(ActivePokemon*);

// turn_actions.c
void BattleScene_StartSecondAction(void);
void func_82124EF4(void);
void BattleScene_ClearPhaseFlag(void);
void BattleScene_SetPhaseFlag(void);
void BattleScene_SetPhase(UNUSED CameraNode* arg0, s32 arg1);
s32 BattleScene_TransitionToPhaseFull(s32 arg0);
s32 BattleScene_TransitionToPhase(s32 arg0);
void func_82126A1C(UNUSED CameraNode* arg0);
void BattleScene_PhaseFaint(CameraNode* arg0);
void BattleScene_FaintStepStart(CameraNode* arg0);
void BattleScene_FaintStepCollapse(CameraNode* arg0);
void BattleScene_FaintStepVanish(CameraNode* arg0);
void BattleScene_FaintStepFinishVanish(CameraNode* arg0);
void BattleScene_AdvanceSendOutFollowupCamera(CameraNode* arg0);
void BattleScene_FaintStepEnd(UNUSED CameraNode* arg0);
void func_82124E80(void);
void func_82124EB4(void);
void Battle_StartTurn(void);
void BattleScene_InitializeSwitchActions(void);
void func_821255B4(s8 *arg0);
void func_821255EC(s8 *arg0);
void func_8212562C(void);
s32 BattleScene_HandleFaintStatusCompletion(void);
void BattleScene_CompleteActionPhase(void);
void func_82125838(void);
void BattleScene_ResolveDisplayedHpCompletion(CameraNode* arg0);
void func_82125570(void);
void func_82125594(CameraNode* arg0, s32 arg1);
M2C_UNK func_821259E8();
M2C_UNK func_82125990();
s32 func_82125930(M2C_UNK);
void BattleScene_UpdateDisplayedHpAndTransition(CameraNode* arg0);
s32 BattleScene_TryEnterEffectPhaseBeforeLaunch(void);
s32 BattleScene_TryEnterEffectPhaseBeforeImpact(void);
s32 BattleScene_PrepareResidualStatusPresentation(void);
void BattleScene_UpdateActiveOwnerPointers(void);
void BattleCamera_PlayFaintShot(void* arg0, void* arg1, s32 arg2);
s32 BattleScene_ResetFaintingMonState(ActivePokemon* active_pokemon);
void func_82126D20(UNUSED CameraNode* arg0);
void func_82126E34(CameraNode* arg0);
void func_82126EE0(CameraNode* arg0);
void func_82126F70(CameraNode* arg0);
void BattleScene_PhaseCommand(CameraNode* arg0);
void func_821272C0(ActivePokemon* arg0);
M2C_UNK func_82125580();
void func_82125FD0(void);

// action_steps.c
void func_82128E34(s32 arg0);
void func_82128FBC(CameraNode* arg0);
void func_821290CC(CameraNode* arg0);
void func_821291E4(CameraNode* arg0);
void func_821292FC(CameraNode* arg0);
void func_82129414(CameraNode* arg0);
void func_8212954C(CameraNode* arg0);
void func_8212960C(CameraNode* arg0);
void func_821296E4(CameraNode* arg0);
void BattleScene_UseMoveStepConfusionSelfHit(CameraNode* arg0);
void BattleScene_ActionSetupAnimationVariantB(CameraNode* arg0);
void func_82129D10(CameraNode* arg0);
void func_82129E30(s32 arg0);
void func_82129F5C(CameraNode* arg0);
void func_8212A074(s32 arg0);
void func_82129C1C(CameraNode*);
void func_8212A190(CameraNode* arg0);
void func_8212A250(CameraNode* arg0);
void BattleScene_ActionStepIntro(CameraNode*, s32);
void BattleScene_ActionStepSetHitCount(CameraNode*, s32);
void BattleScene_ActionStepUseMove(CameraNode*, s32);

// action_steps_2.c
void BattleScene_ActionStepTravel(CameraNode* arg0, s32 arg1);
void func_8212A5AC(ActivePokemon* arg0, CameraNode* arg1);
void func_8212A67C(ActivePokemon* arg0, CameraNode* arg1);

// phases.c
void BattleAnim_RenderNop1(void);
void BattleAnim_RenderNop2(void);
void BattleScene_ReactionMultiHitEnd(CameraNode* arg0, void* arg1);
void BattleScene_ReactionSideEffect(CameraNode* arg0, void* arg1);
void BattleScene_ActionStepReaction(CameraNode* arg0, void* arg1);
void BattleScene_PhaseFirstAction(CameraNode* arg0);
void BattleScene_PhaseSecondAction(CameraNode* arg0);
void func_8212C398(s32 arg0);
void func_8212C454(s32 arg0);
void func_8212C530(s32 arg0);
void BattleCamera_PlayUserShot(s32 arg0, s32 arg1);
void BattleCamera_PlayTargetShot(ActivePokemon* arg0, CameraNode* arg1, s32 arg2);
void func_8212C78C(s32 arg0);
void BattleScene_PhaseSelfEffect(CameraNode* arg0);
void BattleScene_PhaseExplosion(CameraNode* arg0);
void BattleScene_PhaseMoveFailedMessage(CameraNode* arg0);
void BattleScene_PhaseHeal(CameraNode* arg0);
void BattleScene_PhaseTransform(CameraNode* arg0);
void BattleScene_PhaseSubstitute(CameraNode* arg0);
void BattleScene_PhaseFlyUp(CameraNode* arg0);
void BattleScene_PhaseCannotMove(CameraNode* arg0);
void func_8212E9C8(ActivePokemon* arg0);
void BattleScene_PhaseConfusionSelfHit(CameraNode* arg0);
void BattleScene_PhaseFullParalysis(CameraNode* arg0);
void func_8212EEC0(ActivePokemon* arg0, CameraNode* arg1);
void func_8212EF74(ActivePokemon*, CameraNode*);
void func_8212F044(CameraNode* arg0);
void BattleScene_PhaseEndTurn(s32 arg0);
void BattleScene_PhaseCrashDamage(CameraNode* arg0);
void BattleScene_PhaseMoveMissed(CameraNode* arg0);
void BattleScene_PhaseInflictStatus(CameraNode* arg0);
void BattleScene_PhaseLowerStat(CameraNode* arg0);
void BattleScene_PhaseDisable(CameraNode* arg0);
void func_8212F9FC(CameraNode* arg0);
void BattleScene_PhaseResidualDamageAfterMove(CameraNode* arg0);
void BattleScene_Phase10(CameraNode* arg0);
void BattleScene_PhaseBide(CameraNode* arg0);
void BattleScene_PhaseHaze(CameraNode* arg0);
void BattleScene_PhaseDigUnder(CameraNode* arg0);
void BattleScene_PhaseChargeUp(CameraNode* arg0);
void BattleScene_PhaseRecoilDamage(CameraNode* arg0);
void func_82130494(CameraNode* arg0);

// phases_2.c
void BattleScene_PhaseResidualDamageWithoutMove(CameraNode* arg0);
void func_82130D48(ActivePokemon* active_pokemon);
void BattleScene_PhaseWithdraw(CameraNode* arg0);
void BattleScene_PhaseSendOutAfterFaint(CameraNode* arg0);
void BattleScene_PhaseResidualDamageFaintCheck(CameraNode* arg0);
// Zero numbers its phases differently, so the cases call the Zero handlers by address.
void BattleScene_UpdatePhase(CameraNode* arg0);
void BattleScene_IntroStepInitOverheadCamera(CameraNode* arg0);
void BattleScene_IntroPanCamera(CameraNode* arg0);
void BattleScene_SendOutSide0(CameraNode* arg0);
void BattleScene_OpeningStepWaitSide0SendOut(CameraNode* arg0);
void BattleScene_SendOutSide1(CameraNode* arg0);
void BattleScene_OpeningStepWaitSide1SendOut(CameraNode* arg0);
void BattleScene_IntroStepSpinOverheadCamera(CameraNode* arg0);
void func_82131EC4(CameraNode* arg0);

// opening.c
void BattleScene_OpeningStepNop(UNUSED s32 arg0);
void BattleAnim_NoopUpdateHook(void);
void BattleScene_UpdateIntroSequence(CameraNode* arg0);
void BattleScene_OpeningStepWaitForAssets(s32 arg0);
void BattleScene_OpeningStepInitCamera(CameraNode* arg0);
void BattleScene_OpeningStepOrbitCamera(CameraNode* arg0);
void BattleScene_OpeningStepLowerCameraAndThrowSide0(CameraNode* arg0);

// opening_2.c
void BattleScene_RunOpeningSendOut(CameraNode* arg0);

// showcase_mode7.c
void func_821329F0(void);

// demo_mode11.c
void func_82132E20(void);
void func_821336E4(UNUSED s32 arg0);

// scene_memory.c
void BattleScene_FinalPresentationFrameActiveOwner(CameraNode* arg0);
void BattleScene_AllocateMemory(void);
void func_8213436C(void);

// scene_update.c
void BattleScene_UpdateCameraDefaultModeNoop(UNUSED CameraNode* arg0);
void BattleScene_UpdateCameraOwner0FramingModeNoop(UNUSED CameraNode* arg0);
void BattleScene_AvoidDegenerateCameraLookAt(CameraNode* arg0);
void BattleScene_TickCameraSubstateDefault(CameraNode* arg0);
void BattleScene_TickCameraSubstateStripWipe(CameraNode* arg0);
void BattleScene_TickCameraSubstate(CameraNode* arg0);
void BattleScene_Update(CameraNode* arg0);
s32 BattleScene_Dispatch(s32 arg0, CameraNode* arg1);

// anim_sound.c
void BattleAnim_PlaySoundEffect1(void);
void BattleAnim_PlaySoundEffect2(void);
void BattleAnim_PlaySoundEffect3(void);
void BattleAnim_PlayBattleSequenceById(ActivePokemon* active_pokemon, s32 sequence_id);

// participant_models.c
void BattleAnim_RunEffectInitStart(s16 arg0);
void BattleAnim_RunEffectInitEnd(s16 arg0);
void BattleAnim_RegisterEffectSlot(func_D_84390300 arg0, func_D_84390320 arg1);
void BattleAnim_RunEffectList(s32 arg0, s32 arg1, s32 arg2);
void BattleAnim_ProcessQueuedEffects(void);
void BattleAnim_SetQueuedEffectList(u8 effect_list_index);
void func_821351EC(UNUSED s32 arg0, UNUSED s32 arg1);
void func_82135100(void);
void func_82136010(void);
void func_82136018(void);

// anim_effect_queue.c
void func_82136708(s32, ActivePokemon*);
void BattleAnim_QueueEffectList(u8 arg0, s32 arg1);
s32 func_8213646C();                                /* extern */
s32 func_82136E2C(DisplayObject* arg0);
s32 func_82136AC0(s8 *);                          /* extern */
M2C_UNK func_82136D58(s32, M2C_UNK);                /* extern */
void func_821365E8(s32, ActivePokemon*);
u8 BattleAnim_GetCurrentEffectList(void);
void BattleAnim_SetQueuedResourceListId(u8 arg0);
u8 BattleAnim_GetQueuedResourceListId(void);
s16 BattleAnim_GetQueuedMoveId(void);
void BattleAnim_QueueMoveEffect(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4);
void BattleAnim_QueueMoveEffectScript(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor);
void BattleAnim_QueueMoveEffectEnd(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor);
void BattleAnim_QueueChargingMoveEffectScript(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternate_anchor);
void BattleAnim_QueueEffectList3(s32 move_id, ActivePokemon* user, ActivePokemon* user_fallback, s16 default_anchor, s16 alternative_anchor);
void BattleAnim_QueueEffectList6(s32 move_id, ActivePokemon* owner);
void BattleAnim_QueueEffectList5(s32 arg0, ActivePokemon* arg1);
void BattleAnim_QueueEffectList6Alt(s32 arg0, ActivePokemon* arg1);
void BattleAnim_QueueEffectList9(s32 arg0);
void BattleAnim_StopOwnerCategoryParticles(u8 category, ActivePokemon* owner);
void BattleAnim_RegisterAssetTable(arg1_func_80019420* arg0);
void BattleAnim_ResetAssetTable(void);
void BattleAnim_BuildResourceListForMove(s16 arg0);
void BattleAnim_LoadMoveResourceList(BattleSide* battle_session_teams, s16 move_id);
void BattleAnim_LoadModeResourceList(BattleSide* battle_session_teams, s16 mode);
void BattleAnim_RegisterAllAssetTables(void);
void BattleAnim_RegisterAssetTablesForSession(BattleSide* battle_session_teams);
void BattleAnim_ResetDisplayContexts(void);
Particle* BattleAnim_GetOwnerContextParticle(DisplayObject* arg0);
DisplayObject* BattleAnim_AllocOwnerDisplayContext(Particle* arg0);
void BattleAnim_FreeOwnerDisplayContext(DisplayObject* arg0);
DisplayObject* BattleAnim_AllocParticleDisplayContext(Particle* arg0);
void BattleAnim_FreeParticleDisplayContext(DisplayObject* arg0);
void BattleAnim_InitModelWithAnim(DisplayObject* arg0, s16 arg1, s16 arg2);
void BattleAnim_SetModelAnimFrame(DisplayObject* arg0, s16 arg1);
void BattleAnim_InitModel(DisplayObject* arg0, s16 arg1);
void BattleAnim_BindModelAnim(DisplayObject* arg0, s16 arg1);
void BattleAnim_BindModelAnimReversed(DisplayObject* arg0, s16 arg1);
s32 BattleAnim_IsModelAnimComplete(DisplayObject* arg0);
void BattleAnim_UpdateEffectCallbacks(UNUSED CameraNode* arg0);
void BattleAnim_DrawEffectCallbacks(UNUSED CameraNode* arg0);

// anim_init.c
void BattleAnim_Initialize(void);
void BattleAnim_Reset(void);

// particle_math.c
u32 ParticleMath_RandomRange(u32 arg0);                         /* extern */
M2C_UNK func_82137AB4(s8 *, M2C_UNK, M2C_UNK);    /* extern */
void ParticleMath_BitwiseOr(s32* arg0, s32 arg1);
void ParticleMath_BitwiseAndNot(s32* arg0, s32 arg1);
void ParticleMath_BitwiseXor(s32* arg0, s32 arg1);
s32 ParticleMath_HasBits(s32* arg0, s32 arg1);
s32 ParticleMath_LacksBits(s32* arg0, s32 arg1);
s32 ParticleMath_ApproachFloatUp(f32* arg0, f32 arg1, f32 arg2);
s32 ParticleMath_ApproachFloatDown(f32* arg0, f32 arg1, f32 arg2);
s32 ParticleMath_ApproachS32Up(s32* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachS32Down(s32* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachS16Up(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachU16Up(u16* arg0, u16 arg1, u16 arg2);
s32 ParticleMath_ApproachS16Down(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachU16Down(u16* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachFloatUpByPointer(f32* arg0, f32 arg1, f32* arg2);
s32 ParticleMath_ApproachFloatDownByPointer(f32* arg0, f32 arg1, f32* arg2);
s32 ParticleMath_ApproachS32UpByPointer(s32* arg0, s32 arg1, s32* arg2);
s32 ParticleMath_ApproachS32DownByPointer(s32* arg0, s32 arg1, s32* arg2);
s32 ParticleMath_ApproachS16UpByPointer(s16* arg0, s16 arg1, s16* arg2);
s32 ParticleMath_ApproachS16DownByPointer(s16* arg0, s16 arg1, s16* arg2);
s32 ParticleMath_ApproachU8(u8* arg0, u8 arg1, u8 arg2);
s32 ParticleMath_ApproachAngle(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachS32(s32* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachFloat(f32* arg0, f32 arg1, f32 arg2);
void ParticleMath_BounceFloat(f32* arg0, f32 arg1, f32 arg2, f32* arg3);
void ParticleMath_BounceS16(s16* arg0, s16 arg1, s16 arg2, s16* arg3);
void ParticleMath_CopyVec3f(Vec3f* arg0, Vec3f* arg1);
void ParticleMath_CopyVec3s(Vec3s* arg0, Vec3s* arg1);
void ParticleMath_AddVec3f(Vec3f* arg0, Vec3f* arg1);
void ParticleMath_AddVec3s(Vec3s* arg0, Vec3s* arg1);
s32 ParticleMath_IsWithinRadius2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 ParticleMath_RandomRangeOffset(s32 arg0, s32 arg1);
s32 ParticleMath_RandomSigned(s32 arg0);
s32 ParticleMath_RandomSignedOffset(s32 arg0, s32 arg1);
s32 ParticleMath_RandomSignedOffsetBySign(s32 arg0, s32 arg1);
void ParticleMath_NoopStub(UNUSED s32 arg0);
s16 ParticleMath_Atan2YZ(Vec3f arg0);
s16 ParticleMath_Atan2ZX(Vec3f arg0);
s16 ParticleMath_Atan2XY(Vec3f arg0);
void ParticleMath_Vec3ToAngles(Vec3s* arg0, Vec3f arg1);
f32 ParticleMath_Rotate2DX(f32 arg0, f32 arg1, s16 arg2);
f32 ParticleMath_Rotate2DY(f32 arg0, f32 arg1, s16 arg2);
Vec3f* ParticleMath_RotateVec3fY(Vec3f* arg0, Vec3f arg1, Vec3s arg4);
Vec3f* ParticleMath_MakeXZVectorFromAngle(Vec3f* arg0, f32 arg1, s16 arg2);
Vec3f* ParticleMath_RotateVec3fXY(Vec3f* arg0, Vec3f arg1, Vec3s arg4);
f32 ParticleMath_Distance3D(Vec3f arg0, Vec3f arg1);
Vec3f* ParticleMath_NormalizedDirection(Vec3f* arg0, Vec3f arg1, Vec3f arg2);
s32 ParticleMath_DistanceScaled(Vec3f arg0, Vec3f arg1, f32 arg2);
s32 ParticleMath_ScaleDirectionToLength(Vec3f* arg0, Vec3f arg1, Vec3f arg2, f32 arg3);
Vec3f* ParticleMath_RandomDirection(Vec3f* arg0, f32 arg1);
Vec3f* ParticleMath_ScaleVec3f(Vec3f* arg0, f32 arg1);
s16 ParticleMath_AngleXBetweenPoints(Vec3f arg0, Vec3f arg1);
s16 ParticleMath_AngleYBetweenPoints(Vec3f arg0, Vec3f arg1);
s16 ParticleMath_AngleZBetweenPoints(Vec3f arg0, Vec3f arg1);
s16 ParticleMath_ApproachAngleCoarse(s16 arg0, s16 arg1);
void ParticleGfx_NoopStub1(void);
void ParticleGfx_PushMatrix(MtxF* arg0);
void ParticleGfx_Build2DTransformMatrix(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4);
void ParticleGfx_Build2DTransformMatrixYScaled(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4);
void ParticleGfx_Push2DTransform(s16 arg0, s16 arg1, s16 arg2, f32 arg3);
void ParticleGfx_Push2DTransformYScaled(s16 arg0, s16 arg1, s16 arg2, f32 arg3);
void ParticleGfx_BuildTransformMatrix(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3);
void ParticleGfx_BuildTransformMatrixYScaled(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3);
void ParticleGfx_BuildTransformMatrixXYScaled(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3, f32 arg4);
void ParticleGfx_BuildBillboardMatrix(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3);
void ParticleGfx_BuildBillboardMatrixYScaled(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3);
void ParticleGfx_BuildBillboardRotatedMatrix(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4);
void ParticleGfx_BuildBillboardRotatedMatrixYScaled(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4);
void ParticleGfx_BuildDirectionMatrix(MtxF* arg0, Vec3f arg1, Vec3f arg2, s16 arg3, f32 arg4);
void ParticleGfx_PushTransformMatrix(Vec3f arg0, Vec3s arg1, f32 arg2);
void ParticleGfx_PushTransformMatrixYScaled(Vec3f arg0, Vec3s arg1, f32 arg2);
void ParticleGfx_PushTransformMatrixXYScaled(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3);
void ParticleGfx_PushBillboardMatrix(CameraNode* arg0, Vec3f arg1, f32 arg4);
void ParticleGfx_PushBillboardRotatedMatrix(CameraNode* arg0, Vec3f arg1, f32 arg4, s16 arg5);
void ParticleGfx_PushBillboardMatrixYScaled(CameraNode* arg0, Vec3f arg1, f32 arg4);
void ParticleGfx_PushBillboardRotatedMatrixYScaled(CameraNode* arg0, Vec3f arg1, f32 arg4, s16 arg5);
void ParticleGfx_PushTransformMatrixWithHalfTurnXY(Vec3f arg0, Vec3s arg3, f32 arg5);
void ParticleGfx_PushDirectionMatrix(Vec3f arg0, Vec3f arg3, f32 arg6);

// particle_pool.c
M2C_UNK func_8213B31C(M2C_UNK);                     /* extern */
M2C_UNK func_8213B644(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_8213B560(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_8213B464(M2C_UNK);                     /* extern */
M2C_UNK func_8213B6AC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213BC7C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213B8EC(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213B458(M2C_UNK);                     /* extern */
M2C_UNK func_8213BE70(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_8213BC00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213B720(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213C1BC(M2C_UNK);                     /* extern */
M2C_UNK func_8213B878(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_82139E5C(s8 *, M2C_UNK *, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_8213BD78(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_8213C0D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8213B794(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32); /* extern */
void BattleAnim_InitParticleSystem(void);
BattleAnimEffectSlot* BattleAnim_AllocEffectSlot(void);
void BattleAnim_FreeEffectSlot(BattleAnimEffectSlot* arg0);
void BattleAnim_InitializeParticleChain(Particle* arg0, Vec3f arg1, Vec3s arg2, s32 arg3, s32 arg4);
void BattleAnim_CloneParticleState(Particle* arg0, Particle* arg1, ParticleUpdateCallback arg2, ParticleDescriptor* arg3, s32 arg4);
void BattleAnim_EmitParticleBurst(Particle* arg0, ParticleUpdateCallback arg1, ParticleDescriptor* arg2, s16 arg3);
void BattleAnim_EmitParticleBurstWithMetadata(Particle* arg0, ParticleUpdateCallback arg1, ParticleDescriptor* arg2, s16 arg3, s16 arg4, s16 arg5);
Particle* BattleAnim_CreateProceduralParticle(s16 arg0, s16 arg1, s32 arg2, f32 arg3);
void BattleAnim_ReleaseParticleModel(Particle* arg0);
void BattleAnim_InitializeParticleAnchor(Particle* arg0);
void BattleAnim_UpdateParticleAnchor(Particle* arg0);
void BattleAnim_UpdateOrDestroyParticle(Particle* arg0);
void BattleAnim_InitializeParticleFromEffect(Particle* arg0, ActivePokemon* arg1, BattleAnimEffectSlot* arg2, s16 arg3);
void BattleAnim_SpawnStandardParticles(s8 *arg0);
void BattleAnim_SpawnBatchedParticles(s8* arg0);
void BattleAnim_SpawnSingleParticle(BattleAnimEffectSlot* arg0);
void BattleAnim_DispatchParticleEmission(BattleAnimEffectSlot* arg0);
void BattleAnim_TickEffectSlots(void);
void BattleAnim_CleanupEffectsRetainingCategories47(void);
void BattleAnim_CleanupEffectsRetainingCategory4(void);
void BattleAnim_ClearEffectCallbacks(void);
s32 BattleAnim_IsEffectSpawningEnabled(void);
void BattleAnim_EnableEffectSpawning(void);
void BattleAnim_CleanupEffects(s32 cleanup_mode);
void BattleAnim_StopParticlesForOwnerCategory(u8 arg0, ActivePokemon* arg1);
void BattleAnim_ResetSpawnDelay(void);
void BattleAnim_SetSpawnDelay(s32 arg0);
void BattleAnim_AddSpawnDelay(s32 arg0);
void BattleAnim_ResetSpawnDelayAlias(void);
BattleAnimEffectSlot* BattleAnim_CreateEffectSlot(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleDescriptor* arg4, ActivePokemon* arg5, s16 arg6, s16 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB);
BattleAnimEffectSlot* BattleAnim_CreateEffectSlotForCurrentOwner(s32 arg0, func_unk_D_8140E724 arg1, ParticleDescriptor* arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);
BattleAnimEffectSlot* BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleDescriptor* arg4, s16 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA);
BattleAnimEffectSlot* BattleAnim_SpawnGlobalTintColorFadeDetach(s32 arg0, s16 arg1, u8 arg2);
BattleAnimEffectSlot* BattleAnim_SpawnWhiteHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHold(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaFadeInHoldRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachFullAlpha(s32 arg0, s16 arg1, u8 arg2);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetach(s32 arg0, s16 arg1, u8 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25AlphaHoldDetachRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, u8 arg4, u8 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeOut(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnDescriptor25PaletteFadeIn(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRampDetach(s32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPulseDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintHoldFadeDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnBeamBoomWaterfallHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
BattleAnimEffectSlot* BattleAnim_SpawnIceBeamBlizzardHitHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintPaletteCycleVariant(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnDrainFlameHueChange(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelTintRandomPaletteCycle(s32 arg0, s16 arg1, u8 arg2);
BattleAnimEffectSlot* BattleAnim_SpawnRainbowHueChange(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnInvisibility(s32 arg0, s16 arg1, s16 arg2, s16 arg3);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeFullPreset(s32 arg0);
BattleAnimEffectSlot* BattleAnim_SpawnOwnerModelAlphaFadeZeroStartPreset(s32 arg0);
BattleAnimEffectSlot* BattleAnim_SpawnCategory17MarkerSlot(s32 arg0, u8 arg1);
BattleAnimEffectSlot* BattleAnim_SpawnCategory19MarkerSlot(s32 arg0, u8 arg1);
void Particle_ResetDefaults(Particle* arg0);
Particle* Particle_Alloc(void);
void Particle_Free(s8 *arg0);
Particle* Particle_New(void);
Particle* Particle_AllocChain(u8 arg0);
s32 Particle_CountActive(void);
s32 Particle_CountActiveAlias(void);
void Particle_DispatchDraw(Particle* arg0, CameraNode* arg1);
void Particle_UpdateFrameCounters(void);
void Particle_UpdateFrameCountersAlias(void);

// particle_fields.c
s16 Particle_GetUnkAC();                                /* extern */
s32 func_8213C494(s8 *);                          /* extern */
void func_8213C4B8(void);
void BattleAnim_SetEffectState(s32 arg0);
void BattleAnim_ClearEffectState(void);
s16 Particle_GetUnkAA(Particle* arg0);
s16 Particle_FieldAA_GetS16_0C068(Particle* arg0);
void Particle_SetFieldOffsetACIfNotSentinel(Particle* arg0, s16 arg1);
void Particle_SetFieldOffsetCFIfNotSentinel(Particle* arg0, u8 arg1);
void Particle_SetFieldOffsetA6IfNotSentinel(Particle* arg0, s16 arg1);
void Particle_SetFieldOffsetA8IfNotSentinel(Particle* arg0, s16 arg1);
void Particle_SetFieldOffsetCEIfNotSentinel(Particle* arg0, u8 arg1);
void Particle_SetFieldOffsetAAIfNotSentinel(Particle* arg0, s16 arg1);
void Particle_SetPrimAlphaIfNotSentinel(Particle* arg0, u8 arg1);

// anim_owner_bones.c
void Particle_DisableAndDetach(s8 *arg0);                      /* extern */
s32 Particle_IsRunning(s8 *arg0);                          /* extern */
void Particle_MarkInactive(s8 *arg0);                      /* extern */
s32 func_8213C4D0(M2C_UNK);                         /* extern */
s32 func_8213CA04(s8 *, M2C_UNK);                 /* extern */
void BattleAnim_DestroyParticle(Particle* arg0);
s32 BattleAnim_IsCurrentOwnerSpecies(s32 arg0);
void BattleAnim_GetOwnerBonePosition(ActivePokemon* arg0, s16 arg1, Vec3f* arg2);
void BattleAnim_GetCurrentOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetSecondaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetTertiaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetSecondaryOwnerAnchorPosition(Vec3f* arg0);
void BattleAnim_GetTertiaryOwnerBone9Position(Vec3f* arg0);
f32 BattleAnim_GetOwnerModelScale(ActivePokemon* active_pokemon);
f32 BattleAnim_GetSecondaryOwnerModelScale(void);
void BattleAnim_GetSecondaryOwnerSpeciesBaseScale(void);
f32 BattleAnim_GetTertiaryOwnerModelScale(void);
void BattleAnim_GetTertiaryOwnerSpeciesBaseScale(void);
s32 BattleAnim_GetCameraContext(void);
Particle* BattleAnim_SpawnSecondaryOwnerParticle(Vec3f arg0, u8 arg1);
void BattleAnim_SetParticlePosition(Particle* arg0, Vec3f arg1);
void BattleAnim_MarkParticleInactive(Particle* arg0);
void Particle_InitLifecycle(Particle* arg0);
s32 Particle_IsInactive(s8 *arg0);
void Particle_AdvanceLifecycle(Particle* arg0);
s32 Particle_TickDelayTimer(Particle* arg0, s16 arg1);

// particle.c
M2C_UNK func_82140228(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_82140548(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_821406B4(s8 *);                      /* extern */
M2C_UNK func_8213CB3C(s8 *);                      /* extern */
M2C_UNK func_8213E6BC(s8 *);                      /* extern */
M2C_UNK func_821402B8(s8 *);                      /* extern */
M2C_UNK func_8213CA80(s8 *, M2C_UNK);             /* extern */
void Particle_AddVelocityFromRotationTemplate1(s32 arg0);                      /* extern */
void func_8213D644(s8*, f32);
s32 func_8213CB7C(s8 *);                          /* extern */
void Particle_SetPrimAlpha(s8 *arg0, char arg1);             /* extern */
M2C_UNK func_8213EF88(s8 *, M2C_UNK, M2C_UNK);    /* extern */
void Particle_SetPosition(Particle* arg0, f32 arg1, f32 arg2, f32 arg3);
M2C_UNK func_8213DDB8(s8 *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
s32 func_8213E7A0(s8 *);                          /* extern */
M2C_UNK func_8213D238(s8 *);                      /* extern */
s32 func_8213D294(s8 *, M2C_UNK);                 /* extern */
M2C_UNK func_8213E71C(s8 *, M2C_UNK);             /* extern */
M2C_UNK func_8213E7F4(s8 *);                      /* extern */
M2C_UNK func_8213F6DC(s8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8213F940(s8 *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_8213E334(Particle* arg0, f32 arg1);
void func_8213E4B0(Particle* arg0);
void func_8213E11C(Particle* arg0, f32 arg1);
M2C_UNK func_8213E14C(s32, M2C_UNK);                /* extern */
s16 BattleAnim_GetParticleAngleYToTertiaryOwner(Particle* arg0);
s32 Particle_TickDelayAndAdvanceLifecycle(Particle* arg0, s16 arg1);
void Particle_SetFlags(Particle* arg0, s32 arg1);
void Particle_ClearFlags(Particle* arg0, s32 arg1);
void Particle_ToggleFlags(Particle* arg0, s32 arg1);
s32 Particle_HasFlags(Particle* arg0, s32 arg1);
s32 Particle_LacksFlags(Particle* arg0, s32 arg1);
void Particle_EnableRendering(Particle* arg0);
void Particle_DisableRendering(Particle* arg0);
s32 Particle_IsRenderingEnabled(Particle* arg0);
void Particle_EnableFlag40(Particle* arg0);
void Particle_DisableFlag40(Particle* arg0);
void Particle_HasFlag40(Particle* arg0);
void Particle_SetTextureFrame(Particle* arg0, s16 arg1);
s32 Particle_AnimateFramesPingPong(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesForwardAndAdvanceLifecycle(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesReverseFirstPingPong(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesReverseAndAdvanceLifecycle(Particle* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
void Particle_BeginPhase(Particle* arg0);
void Particle_ResetPhase(Particle* arg0);
s32 Particle_TickPhaseTimer(Particle* arg0, s16 arg1);
void Particle_UpdateWorldTransform(Particle* arg0);
void Particle_Field38_SetVecFromVec3fScaled_08C20(Particle* arg0, Vec3f arg1);
void Particle_SetPositionFromRotationTemplate1(Particle* arg0, f32 arg1);
void Particle_SetPositionFromRotationTemplate2(Particle* arg0, f32 arg1);
void Particle_Field38_AddVecScaledFromVec3f_08D78(Particle* arg0, Vec3f arg1);
void Particle_Field38_AddVecFromVec3f_08DD8(Particle* arg0, Vec3f arg1);
void Particle_Field38_AddVecScaled_08E18(Particle* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_AddPositionOffsetAlongRotationY(Particle* arg0, f32 arg1);
void Particle_AddPositionOffsetAlongRotationYPlus180(Particle* arg0, f32 arg1);
void Particle_AddPositionOffsetAlongRotationYPlus90(Particle* arg0, f32 arg1);
void Particle_AddPositionOffsetAlongRotationYMinus90(Particle* arg0, f32 arg1);
void Particle_AddVelocityFromDirVector(Particle* arg0, f32 arg1);
void Particle_AddPositionFromRotationTemplate1(Particle* arg0, f32 arg1);
void Particle_AddPositionFromRotationTemplate2(Particle* arg0, f32 arg1);
void Particle_AddPositionRotatedVectorByYaw(Particle* arg0, Vec3f arg1);
void Particle_SetRandomVelocityXYZ(Particle* arg0, s32 arg1, s32 arg2, s32 arg3);
void Particle_SetRandomRotatedVelocityXY(Particle* arg0, s32 arg1, s32 arg2);
void Particle_SetOrigin(Particle* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetMotionOffset(Particle* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetMotionOffsetYScaled(Particle* arg0, f32 arg1);
void Particle_SetMotionOffsetZScaled(Particle* arg0, f32 arg1);
void Particle_SetMotionTargetXScaled(Particle* arg0, f32 arg1);
void Particle_SetVelocityRandomDirection(Particle* arg0, f32 arg1);
void Particle_AddMotionOffsetYScaled(Particle* arg0, f32 arg1);
void Particle_AddMotionOffsetZScaled(Particle* arg0, f32 arg1);
void Particle_SubMotionOffsetScaled(Particle* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SubMotionOffsetYScaled(Particle* arg0, f32 arg1);
void Particle_SubMotionOffsetZScaled(Particle* arg0, f32 arg1);
s32 Particle_ApproachMotionOffsetY(Particle* arg0, f32 arg1);
s32 Particle_ApproachMotionOffsetZ(Particle* arg0, f32 arg1);
void Particle_ApplyMotionStepXY(Particle* arg0);
void Particle_ApplyMotionStepXZ(Particle* arg0);
void Particle_ApplyMotionStepY(Particle* arg0);
void Particle_ApplyMotionStepZ(Particle* arg0);
void Particle_AddVelocityXZFromRotationYViaHelpers(Particle* arg0);
void Particle_AddVelocityFromRotationTemplate2(Particle* arg0);
void Particle_AddVelocityXZFromRotationY(Particle* arg0);
void Particle_AddVelocityXZFromRotationYPlusHalfTurn(Particle* arg0);
void Particle_StepBackwardAlongRotationY(Particle* arg0, f32 arg1);
s32 Particle_FallAtStepMagnitude(Particle* arg0);
s32 Particle_AccelerateFall(Particle* arg0);
void Particle_SetVelocityTarget(Particle* arg0, f32 arg1, f32 arg2, f32 arg3);
s32 Particle_Field5C_ApproachY_0A0C4(Particle* arg0, f32 arg1, f32 arg2);
f32 ParticleMath_ScaleApproachStep(f32 arg0);
void Particle_ApproachPosition(Particle* arg0, Vec3f arg1);
void Particle_Field9A_SetVecFromVec3s_0A37C(Particle* arg0, Vec3s arg1);
void Particle_SetRotation(Particle* arg0, s16 arg1, s16 arg2, s16 arg3);
void Particle_SetRotationTargetXY(Particle* arg0, s16 arg1, s16 arg2);
void Particle_Field94_AddXFromField9A_0A4B4(Particle* arg0);
void Particle_Field94_AddVecFromVec3s_0A4F0(Particle* arg0, Vec3s arg1);
void Particle_Field94_SubVecFromVec3s_0A600(Particle* arg0, Vec3s arg1);
void Particle_Field94_SubX_0A63C(Particle* arg0, s16 arg1);
void Particle_ApproachRotationTargetXY(Particle* arg0);
void Particle_ApproachRotationTargetXYZ(Particle* arg0);
void Particle_ApproachRotationXTo(Particle* arg0, s16 arg1, s16 arg2);
s32 Particle_Field94_DecrementXTo_0A7DC(Particle* arg0, s32 arg1, s32 arg2);
void Particle_AddRotationRandomSignedXY(Particle* arg0, s32 arg1, s32 arg2);
void Particle_AddRotationRandomSignedXYWithXHalfTurn(Particle* arg0, s32 arg1, s32 arg2);
void Particle_AddRotationRandomSignedY(Particle* arg0, s32 arg1);
void Particle_AddRotationRandomSignedYWithHalfTurn(Particle* arg0, s32 arg1);
void Particle_AddRotationRandomSignedXWithFixedYQuarterTurn(Particle* arg0);
void Particle_ComputeVectorFromRotationY(Particle* arg0, f32 arg1, Vec3f* arg2);
void Particle_ComputeVectorFromRotationXY(Particle* arg0, f32 arg1, Vec3f* arg2);
void Particle_ComputeVectorFromRotationXZ(Particle* arg0, f32 arg1, Vec3f* arg2);
void Particle_ComputeVectorFromRotationXYZAlt(Particle* arg0, f32 arg1, Vec3f* arg2);
void Particle_ComputeVectorFromRotationYZVariant(Particle* arg0, f32 arg1, Vec3f* arg2);
s32 Particle_Field74_Approach_0ADBC(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_StepMagnitude_ApproachUsingMagnitudeStep(Particle* arg0, f32 arg1);
void Particle_SetMotionStep(Particle* arg0, f32 arg1, f32 arg2, f32 arg3);
s32 Particle_Field7C_IncrementXUntilAtLeast_0AF54(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_IncrementYUntilAtLeast_0AFA8(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_DecrementXUntilAtMost_0B050(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_DecrementYUntilAtMost_0B0A4(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachMotionStepY(Particle* arg0, f32 arg1, f32 arg2);
void Particle_Field7C_SetYFromField74AngleX_0B1C4(Particle* arg0);
void Particle_Field7C_SetXFromField74AngleY_0B1EC(Particle* arg0);
void Particle_SetMotionStepXZFromRotationY(Particle* arg0);
void Particle_SetMotionStepFromRotationXY(Particle* arg0);
void Particle_SetMotionStepFromRotationXZ(Particle* arg0);
void Particle_SetMotionStepFromRotationXYAlt(Particle* arg0);
void Particle_SetMotionStepFromRotationYZ(Particle* arg0);
void Particle_SetMotionStepFromRotationXYZ(Particle* arg0);
void Particle_SetMotionStepFromRotationXYZAlt(Particle* arg0);
void Particle_SetMotionStepFromRotationYZAlt(Particle* arg0);
void Particle_SetMotionStepFromRotationYZVariant(Particle* arg0);
void Particle_UpdateRotatingVelocityXZ(Particle* arg0, f32 arg1, s16 arg2);
s32 Particle_Field50_AdvanceField7CWithTimer_0B854(Particle* arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5);
void Particle_SetScaleScaled(Particle* arg0, f32 arg1);
void Particle_SetScale(Particle* arg0, f32 arg1);
void Particle_SetScaleTarget(Particle* arg0, f32 arg1);
void Particle_SetScaleStep(Particle* arg0, f32 arg1);
s32 Particle_ApproachScale(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachScaleThenAdvance(Particle* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachScaleTarget(Particle* arg0);
s32 Particle_ApproachScaleTargetThenAdvance(Particle* arg0);
s32 Particle_StepScaleTarget(Particle* arg0, f32 arg1, f32 arg2);
void Particle_SetPrimColor(Particle* arg0, u8 arg1, u8 arg2, u8 arg3);
void Particle_SetEnvColor(Particle* arg0, u8 arg1, u8 arg2, u8 arg3);
s32 Particle_ApproachPrimAlphaThenAdvance(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_FieldA6_DecrementToZero_0BD08(Particle* arg0, s16 arg1);
s32 Particle_FieldA6_DecrementToZeroAndStepState_0BD34(Particle* arg0, s16 arg1);
s32 Particle_FieldA6_DecrementToStep1_0BD80(Particle* arg0, s16 arg1);
s32 Particle_DecrementUnkA6ToZero(Particle* arg0);
s32 Particle_DecrementUnkA6ToZeroThenAdvance(Particle* arg0);
s32 Particle_DecrementUnkA8ToZero(Particle* arg0);
s32 Particle_FieldA8_DecrementToZeroStep1AndStepState_0BE8C(Particle* arg0);
s32 Particle_ApproachUnkAEThenAdvance(Particle* arg0, s16 arg1, s16 arg2);

// anim_stinger.c
void BattleAnim_InitStingerTrailColor(Particle* arg0);
void BattleAnim_UpdateNeedleBlueFadeGrow(s8 *arg0);
void BattleAnim_InitStingerTrailColorDuplicate(Particle* arg0);
void BattleAnim_UpdateSecondaryOwnerParticleBlueGrow(s8 *arg0);
void BattleAnim_InitStingerMoveParticle(Particle* arg0, u8 arg1);

// particle_textures.c
void ParticleGfx_LoadTextureCallbackIa8_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod4_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv4Mod4_32x32(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32(UNUSED Particle* arg0, u8* texture);

// particle_textures_3.c
void func_82140D50(void);
void ParticleGfx_LoadTextureCallbackI4FrameMod10_32x64(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4_64x64(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameMod8_64x64(UNUSED Particle* arg0, u8* texture);

// particle_textures_2.c
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_64x64(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4WrapST_64x64(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackIa8WrapST_64x64(UNUSED Particle* arg0, u8* texture);
void ParticleGfx_DrawBillboardPrim(Particle* arg0, CameraNode* arg1);
void ParticleGfx_DrawBillboardPrimEnv(Particle* arg0, CameraNode* arg1);
s32 ParticleGfx_DrawDoubleSidedPrimEnvTransformedQuad(Particle* arg0, UNUSED CameraNode* arg1);
void ParticleGfx_DrawBillboardDefaultQuad(Particle* arg0, CameraNode* arg1);
void ParticleGfx_DrawBillboardTextureAlphaRotatedQuad(Particle* arg0, CameraNode* arg1);
void ParticleGfx_DrawBillboardPrimEnvRotatedQuad(Particle* arg0, CameraNode* arg1);
void ParticleGfx_DrawPrimEnvTransformedQuad(Particle* arg0, CameraNode* arg1);

// anim_draw.c
void func_82142678(UNUSED ActivePokemon* active_pokemon, UNUSED s32 unused);
void BattleAnim_DrawAsset76Ia8FrameWithAsset77I4Overlay(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawFlameHit(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawFlameUse(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawSleepMoveAnimatedI4(Particle* arg0, CameraNode* arg1);
s32 BattleAnim_DrawDigRocks(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAssets27And28LayeredI4QuadVariantA(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAssets27And28LayeredI4QuadVariantB(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawMistLightest(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset87AnimatedI4Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset1AFrameI4Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset1CRgba16Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset1DRotatedI4Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset13FrameI4YScaledQuadA(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset13FrameI4YScaledQuadB(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset13FrameI4ModelQuadA(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawAsset1BI4TriangleA(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset13FrameDiv2I4Quad(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_DrawAsset18FrameI4ModelQuad(Particle* arg0, CameraNode* arg1);
void BattleAnim_DrawAssetA9I4XYScaledQuad(Particle* arg0, UNUSED CameraNode* arg1);
void ParticleEffect_Noop(UNUSED s32 arg0, UNUSED s32 arg1);

// particle_palette.c
M2C_UNK func_821437E0(s8 *, M2C_UNK, M2C_UNK);    /* extern */
void BattleAnim_SetupBackgroundRecolor(Particle* arg0);
void BattleAnim_SetupTargetHueChange(Particle* arg0);
void BattleAnim_SetupUserHueChange(Particle* arg0);
void BattleAnim_RunUserHueChange(Particle* arg0);
void BattleAnim_SetupIceBeamBlizzardHitHueChange(Particle* arg0);
void BattleAnim_RunIceBeamBlizzardHitHueChange(Particle* arg0);
void func_82143C08(void);
void ParticleGfx_CopyPaletteRgb(u8* arg0, u16 arg1);
void ParticleGfx_CopyPalettePairRgb(u8* arg0, u8* arg1, u16 arg2);
void ParticleGfx_RecolorPrimEnvFromPalettePair(Particle* arg0, u16 arg1);
void ParticleGfx_RecolorPrimFromPaletteSetA(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorEnvFromPaletteSetA(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorPrimFromPaletteSetB(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorEnvFromPaletteSetB(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorPrimEnvFromPaletteSetA(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorPrimEnvFromPaletteSetB(Particle* arg0, s16 arg1);
void ParticleGfx_RecolorPrimRandomPalette(Particle* arg0);
void ParticleGfx_RecolorEnvRandomPalette(Particle* arg0);
s32 ParticleGfx_ApproachPrimPalette(Particle* arg0, u16 arg1, u8 arg2);
s32 ParticleGfx_ApproachEnvPalette(Particle* arg0, u16 arg1, u8 arg2);
s32 ParticleGfx_ApproachPrimEnvPalettePair(Particle* arg0, u16 arg1, u8 arg2);

// anim_model_tint.c
void BattleAnim_SetupDrainFlameHueChange(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteFade(s8 *arg0);
void BattleAnim_SetupOwnerModelTintRandomPaletteCycle(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintRandomPaletteCycle(Particle* arg0);
void BattleAnim_SetupRainbowHueChange(Particle* arg0);
void BattleAnim_RunRainbowHueChange(Particle* arg0);
void BattleAnim_SetupInvisibility(Particle* arg0);
void BattleAnim_CallbackOwnerModelAlphaFade(s8 *arg0);
void BattleAnim_SetupParticleRecolorTransparent(Particle* arg0);
void BattleAnim_SetupWhiteHueChange(Particle* arg0);
void BattleAnim_RunWhiteHueChange(Particle* arg0);
void BattleAnim_SetupDescriptor25AlphaHoldFadeOut(s8 *arg0);
void BattleAnim_RunFullScreenHueChange(Particle* arg0);
void BattleAnim_SetupDescriptor25AlphaFadeInHold(Particle* arg0);
void BattleAnim_RunPokemonAndFullScreenHueChange(Particle* arg0);
void BattleAnim_CallbackDescriptor25AlphaHoldDetach(s8 *arg0);
void BattleAnim_SetupDescriptor25PaletteFadeOut(Particle* arg0);
void BattleAnim_CallbackDescriptor25PaletteFadeOut(Particle* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeIn(Particle* arg0);
void BattleAnim_CallbackDescriptor25PaletteFadeIn(Particle* arg0);

// anim_color_fade_effects.c
void BattleAnim_SetupFireBreathFlameFading(Particle* arg0, s16 arg1);
void BattleAnim_ContinueFireBreathFlameFading(Particle* arg0);
void BattleAnim_RunFireBreathFlameFading(Particle* arg0);
void BattleAnim_SetupUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0);
void BattleAnim_MotionUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0);
void BattleAnim_CallbackUnusedDescriptor4FColorCycleScaleFadeVariant(Particle* arg0);
void BattleAnim_SetupFireBreathFlameGeometry(Particle* arg0);
void BattleAnim_ContinueFireBreathFlameGeometry(Particle* arg0);
void BattleAnim_SetupFireBreathFlameColoration(Particle* arg0, s16 arg1);
void BattleAnim_ContinueFireBreathFlameColoration(Particle* arg0);
void BattleAnim_FlameRotatingFallColorCycle(Particle* arg0);
void BattleAnim_SetupExpandingHitSpark(Particle* arg0);
void BattleAnim_RunExpandingHitSpark(Particle* arg0);
void BattleAnim_RunPsybeamHitSparkDrift(Particle* arg0);
void BattleAnim_CallbackUnusedGrowFadeVariant(Particle* arg0);
void BattleAnim_SetupOscillatingFlameUnderneathPokemon(Particle* arg0);
void BattleAnim_SetupFireSpinFlame(Particle* arg0);
void BattleAnim_SetupUnusedVariant2(Particle* arg0);
void BattleAnim_CallbackUnusedVariant2(Particle* arg0);
void BattleAnim_SetupEmberProjectileAfterimages(Particle* arg0);
void BattleAnim_SetupEmberProjectile(Particle* arg0);
void BattleAnim_SetupEmberBurstEmitter(Particle* arg0);
void BattleAnim_SetupEmberUseEffect(Particle* arg0);
void BattleAnim_RunEmberUseEffect(Particle* arg0);
void BattleAnim_GetExplosionParticleColor(Particle* arg0, u8 arg1);
void BattleAnim_FirePunchEmberEggBombColorChange(Particle* arg0);
void BattleAnim_SetupBackgroundBombExplosion(Particle* arg0);
void BattleAnim_RunBackgroundBombExplosion(Particle* arg0);
void BattleAnim_SetupBoomSmallExplosion(Particle* arg0);
void BattleAnim_SetupEggBombHitEffect(Particle* arg0);
void BattleAnim_CallbackEndEffect40Descriptor48SpreadScaleAlphaFade(s8 *arg0);
void BattleAnim_SetupSecondaryBombExplosion(Particle* arg0);
void BattleAnim_SetupEmberHitFireball(Particle* arg0);
void BattleAnim_CallbackEndEffect56Descriptor46RisingScaleAlphaFade(s8 *arg0);
void BattleAnim_SetupEmberHitSmoke(Particle* arg0);
void BattleAnim_EmberSpreadScaleAlphaRise(Particle* arg0);
void BattleAnim_SetupFirePunchLingeringHitSpark(Particle* arg0);
void BattleAnim_SetupAfterImpactSmoke(Particle* arg0);
void BattleAnim_SetupFirePunchHitEffect(Particle* arg0);
void BattleAnim_SetupFlamethrowerHitRotation(Particle* arg0, s16 arg1, s16 arg2);
void BattleAnim_RunFlamethrowerHitRotation(Particle* arg0, s32 arg1);
void BattleAnim_RunFlamethrowerHitRotationWeak(Particle* arg0);
void BattleAnim_RunFlamethrowerHitRotationStrong(Particle* arg0);
void BattleAnim_SetupFireBlastHitFrontFlames(Particle* arg0);
void BattleAnim_ContinueFireBlastHitFrontFlames(Particle* arg0);
void BattleAnim_SetupDaimonji(Particle* arg0);
void BattleAnim_ContinueDaimonji(Particle* arg0);
void BattleAnim_RunDaimonji(Particle* arg0);
void BattleAnim_SetupDaimonjiColoration(Particle* arg0);
void BattleAnim_InitializeEmberHit(void);
void BattleAnim_InitializeFlamethrowerHit(void);
void BattleAnim_InitializeDragonRageHit(void);
void BattleAnim_InitializeEggBombHit(void);
void BattleAnim_InitializeFireBlastHit(void);
void func_82146674(void);
void func_821491CC(void);
void BattleAnim_DefaultStartEffect_Init(void);
void BattleAnim_DefaultEndEffect_Init(void);

// anim_water_effects.c
void BattleAnim_SetupSurfHitSpark(Particle* arg0);
void BattleAnim_SetupBubbleBubbles(Particle* arg0, s16 arg1);
void BattleAnim_RunBubbleBubbles(Particle* arg0);
void BattleAnim_SetupBubbleBeamBubblesSlow(Particle* arg0);
void BattleAnim_ContinueBubbleBeamBubblesSlow(Particle* arg0);
void BattleAnim_SetupBubbleBeamBubblesFast(Particle* arg0);
void BattleAnim_SetupUnusedRotatingSparkVariant(Particle* arg0);
void BattleAnim_MotionUnusedRotatingSparkVariant(Particle* arg0);
void BattleAnim_SetupUnusedAimedSparkVariant(Particle* arg0);
void BattleAnim_CallbackUnusedAimedSparkVariant(Particle* arg0);
void BattleAnim_SetupWaterGunAndHydroPumpEmitterFade(Particle* arg0);
void BattleAnim_RunWaterGunAndHydroPumpEmitterFade(Particle* arg0);
void BattleAnim_SetupHydroPumpBurstChild(Particle* arg0);
void BattleAnim_SetupHydroPumpMetadataBurstChild(Particle* arg0);
void BattleAnim_SetupHydroPumpBurstEmitter(Particle* arg0);
void BattleAnim_RunHydroPumpBurstEmitter(Particle* arg0);
void BattleAnim_SetupWaterGunProjectileChild(Particle* arg0);
void BattleAnim_SetupWaterGunProjectileMetadata(Particle* arg0);
void BattleAnim_SetupWaterGunProjectile(Particle* arg0);
void BattleAnim_RunWaterGunProjectile(Particle* arg0);
void BattleAnim_SetupIceBeamColdBreath(Particle* arg0);
void BattleAnim_ContinueIceBeamColdBreath(Particle* arg0);
void BattleAnim_SetupMegaKickAndPunchProjectile(Particle* arg0);
void BattleAnim_RunMegaKickAndPunchProjectile(Particle* arg0);
void BattleAnim_SetupInitialBeamEmanator(Particle* arg0);
void BattleAnim_RunInitialBeamEmanator(Particle* arg0);
void BattleAnim_SetupPulsingBeamEmanator(Particle* arg0);
void BattleAnim_SetupStrongBeamHitEffect(Particle* arg0);
void BattleAnim_RunStrongBeamHitEffect(Particle* arg0);
void BattleAnim_SetupPsybeamHitSparkFlicker(Particle* arg0);
void BattleAnim_RunPsybeamHitSparkFlicker(Particle* arg0);
void BattleAnim_SetupAuroraBeamHitSpark(Particle* arg0);
void BattleAnim_RunAuroraBeamHitSpark(Particle* arg0);
void BattleAnim_SetupStrongOutwardMovingLargeHitSpark(Particle* arg0);
void BattleAnim_SetupBlizzardHitUpwardColdAir(Particle* arg0);
void BattleAnim_SetupWaterGunHitEffect(Particle* arg0);
void BattleAnim_SetupWeakBeamHitEffect(Particle* arg0);
void BattleAnim_SetupTriAttackHitSpark(Particle* arg0);
void BattleAnim_SetupStrongOutwardMovingSmallHitSpark(Particle* arg0);
void BattleAnim_SetupUnusedIndexedFadeVariantA(Particle* arg0);
void BattleAnim_SetupUnusedIndexedFadeVariantB(Particle* arg0);
void BattleAnim_SetupBubbleBubbleBeamSharedEffect(Particle* arg0);
void BattleAnim_CallbackEndEffects34And53Descriptor45RotatingBounceFade(Particle* arg0);
void BattleAnim_SetupHydroPumpColorShiftFade(Particle* arg0);
void BattleAnim_SetupWaterGunEmitterColoration(Particle* arg0);
void BattleAnim_SetupHydroPumpWaterGunProjectileHit(Particle* arg0);
void BattleAnim_StartMegaPunchEffect(void);
void BattleAnim_InitializeBubbleHit(void);
void BattleAnim_InitializeWaterGunUse(void);
void BattleAnim_InitializeWaterGunHit(void);
void BattleAnim_InitializeHydroPumpUse(void);
void BattleAnim_InitializeBubbleBeamHit(void);
void BattleAnim_InitializeHyperBeamHit(void);
void BattleAnim_EndEffect71PaletteApproachWithExpandingScaleFades(void);
void BattleAnim_InitializeTriAttackHit(void);

// anim_electric_effects.c
void BattleAnim_SetupStrongElectricSpark(Particle* arg0);
void BattleAnim_ApplyThunderThunderboltUseRadialOffset(Particle* arg0);
void BattleAnim_SetupThunderThunderboltUseEffect(Particle* arg0);
void BattleAnim_RunThunderThunderboltUseEffect(Particle* arg0);
void BattleAnim_SetupDelayedRisingColumnFade(Particle* arg0);
void BattleAnim_RunDeterministicRotatingBoltOfLightning(Particle* arg0);
void BattleAnim_SetupDelayedRisingColumnRandomScale(Particle* arg0);
void BattleAnim_RunRandomRotatingBoltOfLightning(Particle* arg0);
void BattleAnim_SetupSharedDirectionalSprayFade(Particle* arg0);
void BattleAnim_SetupDirectionalSprayScaledFade(Particle* arg0);
void BattleAnim_SetupThunderShockOuterJolts(Particle* arg0);
void BattleAnim_SetupUnregisteredStraightDirectionalStreamFade(Particle* arg0);
void BattleAnim_SetupEndEffect28Descriptor10UpwardBurstFade(Particle* arg0);
void BattleAnim_SetupEndEffect28Descriptor10WideScatterBurstFade(Particle* arg0);
void BattleAnim_InitializeThunderThunderboltUse(void);
void BattleAnim_InitializeThunderShockUse(void);
void BattleAnim_InitializeThunderPunchUse(void);
void BattleAnim_InitializeHyperBeamHitSequence(void);

// anim_start_effects.c
void func_82150DEC(void);
void BattleAnim_InitStartEffect135Descriptor1CRisingScale(Particle* arg0);
void BattleAnim_CallbackStartEffect135Descriptor1CRisingScaleFade(Particle* arg0);
void BattleAnim_CallbackStartEffect135ExpandingFlashFade(Particle* arg0);
void BattleAnim_InitStartEffect139Descriptor42FallingScale(Particle* arg0);
void BattleAnim_CallbackStartEffect139Descriptor42FallingScaleFade(Particle* arg0);
void BattleAnim_InitStartEffect139Descriptor22SpinFade(Particle* arg0);
void BattleAnim_InitStartEffect141Descriptor1CGridRise(Particle* arg0);
void BattleAnim_CallbackStartEffect141Descriptor1CGridRiseFade(Particle* arg0);
void BattleAnim_InitExplosionOrbit(Particle* arg0);
void BattleAnim_ExplosionOrbitSwirl(Particle* arg0);
void BattleAnim_InitExplosionBurst(Particle* arg0);
void BattleAnim_ExplosionBurstEmitter(Particle* arg0);
void BattleAnim_StartEffect135ExpandingFlashAndRisingScaleFade(void);
void BattleAnim_StartEffect134ModeOrbitAndMetadataBurst(void);
void BattleAnim_StartEffect143ModeOrbitAndMetadataBurst(void);
void BattleAnim_StartEffect133ModeOrbitBurstAndEffect135Followup(void);
void BattleAnim_StartEffect122GlobalAndOwnerTintFade(void);
void func_82150DCC(void);
void func_82150D1C(void);

// anim_spin_scatter_effects.c
void BattleAnim_UnusedResetAppearanceAndAdvance(Particle* arg0);
void BattleAnim_CallbackUnusedGenericFadeApproach(Particle* arg0);
void BattleAnim_SetupOrphanDescriptor2BSpinFade(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor2BSpinFade(Particle* arg0);
void BattleAnim_SetupOrphanDescriptor2EScatterFade(Particle* arg0);
void BattleAnim_SetupPetalDanceLingeringHitEffect(Particle* arg0);
void BattleAnim_RunPetalDanceLingeringHitEffect(Particle* arg0);
void BattleAnim_SetupSlowFallingHitEffect(Particle* arg0);
void BattleAnim_RunSlowFallingHitEffect(Particle* arg0);
void BattleAnim_OrphanDescriptor2BAnd2EEmitterSequence(void);
void BattleAnim_InitializePetalDanceHit(void);
void BattleAnim_InitializeWingAttackHit(void);
void BattleAnim_DefaultStartEffect_Draw(void);

// anim_particle_models.c
void BattleAnim_SetupReflectiveCamera(void);
Gfx* BattleAnim_BuildAnimatedTileDisplayList(Gfx* arg0, u8* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                   s16 argA, s16 argB);
Gfx* BattleAnim_BuildAnimatedTileDisplayListFromStruct(Gfx* arg0, arg1_func_8434E21C* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7,
                   s16 arg8, s16 arg9, s16 argA, s16 argB);
void ParticleEffect_AllocateGfxIfNeeded(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_AllocateGfxAndDraw(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeThunderWaveUse(void);
void BattleAnim_SetupSleepMovePhaseFadeOut(Particle* arg0);
void BattleAnim_CallbackInitModelAnimWait(Particle* arg0);
void BattleAnim_InitializeParticleModel(Particle* arg0);
void BattleAnim_RunScaryEyes(Particle* arg0);
void BattleAnim_RunFillScreenOverlay(Particle* arg0);
void Gfx_SetParticlePrimEnvColors(Gfx* arg0);
void Gfx_DrawParticleTextureWithParams(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void BattleAnim_ApplyEffect1SpeciesMotion(Particle* arg0);
void BattleAnim_RunDreamEaterUseEffect(Particle* arg0);
void BattleAnim_CallbackInitModelAnimMode2(Particle* arg0);
void BattleAnim_SetupMove86EndDescriptor24(Particle* arg0);
void BattleAnim_RunThunderWaveHitEffect(Particle* arg0);
void BattleAnim_SetupMove86StartDescriptor24(Particle* arg0);
M2C_UNK func_82153D00(s8 *);                      /* extern */
void func_82153E28(s8 *arg0);
void BattleAnim_InitializeThunderWaveHit(void);
void BattleAnim_SleepMovePhaseFadeOut(Particle* arg0);
void func_821542BC(void);
M2C_UNK func_82152730(s8 *, M2C_UNK);             /* extern */
void BattleAnim_SelectParticleModelFrames(Particle* arg0, s32 arg1);

// anim_particle_models_2.c
void BattleAnim_ApplyModelSpeciesOffset(Particle* arg0);

// anim_model_effects.c
void BattleAnim_InitModelAnimationSlot(Particle* arg0, s16 arg1);
void BattleAnim_InitializeAmnesiaUse(void);
void BattleAnim_BuildReflectiveTextureDisplayList(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_AllocateReflectiveTextureDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_BuildEffect125DisplayList(Gfx* arg0, u16 arg1);
void BattleAnim_AllocateEffect125DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitEffect28Overlay(Particle* arg0);
void BattleAnim_SetupLeechSeedUseEffect1(Particle* arg0);
void BattleAnim_SetupLeechSeedUseEffect2(Particle* arg0);
void BattleAnim_InitializeLeechSeedHit(void);
void BattleAnim_InitializePayDayHit(void);
void ParticleEffect_DrawSimple(Gfx* arg0, u8* arg1);
void ParticleEffect_CreateSimpleDL(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_SetupBlizzardHitSpark(Particle* arg0);
void BattleAnim_SetupBlizzard(Particle* arg0);
void ParticleEffect_CreateNodeDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawNodeVariant(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateNodeVariantDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawSimpleOffsetTileNoCamera(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateSimpleOffsetTileNoCameraDL(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_DefaultEndEffect_Draw(void);
void BattleAnim_InitializeDizzyPunchHit(void);
void BattleAnim_InitEffect49Model(Particle* arg0);
void BattleAnim_AllocateEffect49DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterColorAnim(void);
void BattleAnim_SetupFlyUpwardMovementEffect(Particle* arg0);
void BattleAnim_InitializeTeleportUse(void);
void BattleAnim_AllocateEffect63DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_AllocateEffect75DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitRockModel(Particle* arg0);
void BattleAnim_InitEffects10And50Model(Particle* arg0);
void BattleAnim_ApplyRockSpeciesScaleOffset(Particle* arg0);
void BattleAnim_InitRockModel38(Particle* arg0);
void Particle_CreateDisplayList_Alpha(s32 arg0, arg1_func_84344CE8* arg1);
void Particle_CreateDisplayList_Texture4b(s32 arg0, arg1_func_84344CE8* arg1);
void Particle_CreateDisplayList_GreenPrim(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeRockThrowRockSlideUse(void);
void BattleAnim_InitializeRockSlideRockThrowHit(void);
void BattleAnim_InitializeStrengthUse(void);
void BattleAnim_InitializeStrengthHit(void);
void BattleAnim_InitializeEggBombUse(void);
void BattleAnim_SetupStrongWinds(Particle* arg0);
void Gfx_DrawParticleCyanEnv(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_CyanEnv(s32 arg0, arg1_func_84344CE8* arg1);
void Particle_CreateDisplayList_BluePrim(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeStrongWind(void);
void BattleAnim_InitializeRazorWindUse(void);
void BattleAnim_SetupBoomUseEffect4(Particle* arg0);
void Particle_CreateDisplayList_CustomColors(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_SetupBoomHitEffect3(Particle* arg0);
void func_821597B8(UNUSED ActivePokemon* active_pokemon, UNUSED s32 unused);
void BattleAnim_TransformNop(UNUSED ActivePokemon* owner, UNUSED ActivePokemon* animated_pokemon);
void BattleAnim_SetupBitingEffect(Particle* arg0);
void Particle_CreateDisplayList_TempColors(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeClampViceGripUse(void);
void BattleAnim_InitializeGuillotineUse(void);
void BattleAnim_InitializeBitingMoveUse(void);
void BattleAnim_InitializeBitingMoveHit(void);
void Gfx_DrawParticleDualTileDiagonal4(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_DualTileDiagonal4(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleDualTileAntiDiagonal1(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_DualTileAntiDiagonal1(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeSwordsDanceUse(void);
f32 BattleAnim_GetSpeciesScaleAdjust(Particle* arg0);
void BattleAnim_InitializeDigUse(void);
void BattleAnim_InitializeKinesisUse(void);
void BattleAnim_InitializeBonemerangUse(void);
void BattleAnim_SludgeModelAnimFinish_InitParticle(Particle* arg0);
void BattleAnim_SetupSlimePuddle(Particle* arg0);
void Gfx_DrawParticlePaletteBased(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_ParticlePaletteCallback(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_ParticlePaletteDL(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticlePaletteColorOnlyCallback(s32 arg0, arg1_func_84344CE8* arg1);
s16 BattleAnim_GetSlimeVariantIndex(void);
s16 BattleAnim_GetMoveKeyedTrailVariantParam(void);
void BattleAnim_InitializeSlimeMove(void);
void ParticleEffect_PaletteMultiBurst(void);
void Gfx_ParticleTextureTileCallback(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticleTextureTileAllocCallback(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_ParticleRedPrimAllocCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeGlareLeerUse(void);
void BattleAnim_InitializeHyperBeamUseSequence(void);
void BattleAnim_InitializeEarthquakeFissureHit(void);
void BattleAnim_InitializeEarthquakeHit(void);
void Gfx_PokemonPortraitCallback(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void Gfx_PokemonPortraitAllocCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeSpeedLines(void);
void BattleAnim_InitializeWithdrawUse(void);
void Gfx_PaletteParticleDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeDreamEaterHit(void);
void BattleAnim_InitializeMeditateUse(void);
void BattleAnim_SetupConfuseRayUseSpotlight(Particle* arg0);
void BattleAnim_SetupConfuseRayHitSpotlight(Particle* arg0);
void Gfx_WaterAnimPrimEnvDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_WaterAnimBurst(void);
void Gfx_WaterAnimDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_SetupBarrageEffect(Particle* arg0);
void BattleAnim_SetupBarrageUseEffect1(Particle* arg0);
void BattleAnim_InitializeBarrageUse(void);
void BattleAnim_SetupBarrageHitEffect(Particle* arg0);
void BattleAnim_InitializeBarrageHit(void);
void BattleAnim_SetupPsywaveEffect(Particle* arg0);
void Gfx_SimpleNodeDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializePsywaveUse(void);
void BattleAnim_InitializeBideRageUseSequence(void);
void BattleAnim_InitializeSkyAttackHit(void);
void ParticleEffect_AllocateDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitializeThunderHitSequence(void);
void BattleAnim_InitializeDrillPeckUse(void);
void BattleAnim_InitializeDrillPeckHit(void);
void BattleAnim_InitializeHornDrillUse(void);
void BattleAnim_InitializeVerticalLandingHitSpark(void);
void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade_InitParticle(Particle* arg0);
void BattleAnim_StartEffect127Descriptor39ScaleFade(void);
void BattleAnim_StartEffect128Descriptor39ScaleFade(void);
void ParticleEffect_CreateTypeX(void);
void ParticleEffect_CreateSmoke(void);
void ParticleEffect_CreateSmokeHighPriority(void);
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade_InitParticle(Particle* arg0);
void ParticleEffect_CreateDual(void);
void BattleAnim_ConfuseRayAmnesiaModelAnimWait(Particle* arg0);
void ParticleEffect_DrawNode(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_RunDizzyPunchHitEffect(Particle* arg0);
void BattleAnim_CallbackEndEffect49Model33Anim34WaitCleanup(Particle* arg0);
void BattleAnim_BuildEffect49DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void BattleAnim_RunFlyUpwardMovementEffect(Particle* arg0);
void BattleAnim_BuildEffect63DisplayList(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_BuildEffect75DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void BattleAnim_RockModelAnimWait(Particle* arg0);
void BattleAnim_RockModelFadeIn(Particle* arg0);
void Gfx_DrawParticleAlpha(Gfx* arg0, s32 arg1, u16 arg2);
void Gfx_DrawParticleTexture4b(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_DrawParticleGreenPrim(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_DrawParticleBluePrim(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_DrawParticleCustomColors(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_DrawParticleFromTempColors(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_SludgeModelAnimFinish(Particle* arg0);
void BattleAnim_RunSlimePuddle(Particle* arg0);
s16 BattleAnim_GetMoveKeyedTintRampParam(void);
void Gfx_ParticleRedPrimCallback(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void BattleAnim_RunPsychedelicOverlay(Particle* arg0);
void Gfx_PaletteParticleDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_WaterAnimPrimEnvDL(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void Gfx_WaterAnimDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void BattleAnim_CallbackStartEffect101ModelBurstEmitter(Particle* arg0);
void BattleAnim_RunPsywaveEffect(Particle* arg0);
void Gfx_SimpleNodeDL(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_DrawQuad(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade(Particle* arg0);
void BattleAnim_InitializeScreenMove(void);
void BattleAnim_ApplyEffect125ModelScaleOffset(Particle* arg0);
void BattleAnim_InitEffect125Model(Particle* arg0, UNUSED s16 arg1);
void BattleAnim_CallbackStartEffect125ModelBurstEmitter(Particle* arg0);
void func_82155084(void);
void BattleAnim_InitEffect65Overlay(Particle* arg0);
void BattleAnim_RunSporePowderMoveOverlay(Particle* arg0);
/*
 * ParticleEffect_RegisterParticleNodes
 *
 * Starts the three particle effect slots of effect 65 for the current
 * battle-animation owner: two one-shot slots (type 8) that fade in using
 * BattleAnim_RunSporePowderMoveOverlay with particle
 * descriptors 0x32 and 0x31, and one repeating slot (0, 3, 0x14) driven by
 * the animated-scale-motion callback with descriptor 0x46.
 *
 * Same three calls as ParticleEffect_RegisterParticleNodes in the Stadium 1
 * decomp.  The third descriptor is index 0x47 there; here the retail
 * address (D_8218E7B8) is index 0x46 of gBattleAnimParticleDescriptors
 * (8-byte stride from 0x8218E588), so the table differs by one entry.
 */
void ParticleEffect_RegisterParticleNodes(void);
void BattleAnim_RunGasAttack(Particle* arg0);
void BattleAnim_InitializeHazePoisonGasSmokescreenUse(void);
void BattleAnim_InitializeSmogUse(void);
void BattleAnim_InitializeMistUse(void);
M2C_UNK func_8215558C(s8 *);                      /* extern */
void BattleAnim_LeechSeedParticleUpdate(s8 *arg0);
void BattleAnim_CallbackStartEffect8ModelBurstEmitter(Particle* arg0);
void BattleAnim_InitEffect31Model(Particle* arg0);
M2C_UNK func_82155878(s8 *);                      /* extern */
void func_821558F4(s8 *arg0);
void BattleAnim_InitializeLeechSeedUse(void);
M2C_UNK func_82155CC0(s8 *);                      /* extern */
void BattleAnim_BlizzardParticleUpdate(s8 *arg0);
M2C_UNK func_82155DB8(s8 *);                      /* extern */
void BattleAnim_RunBlizzard(s8 *arg0);
void BattleAnim_InitializeBlizzardUse(void);
void BattleAnim_InitializeBlizzardHit(void);
void BattleAnim_InitMove146Model(Particle* arg0);
void func_82156654(Particle* arg0);
void BattleAnim_CallbackEndEffect21ModelAnimWait(Particle* arg0);
void BattleAnim_InitializeDrainingMoveHit(void);
void BattleAnim_InitializeFlyUse(void);
void func_82156E54(Particle* arg0);
M2C_UNK func_82156F70(s8 *);                      /* extern */
void BattleAnim_RunFallingRock(s8 *arg0);
void func_82157354(Particle* arg0);
void BattleAnim_InitializeSoftBoiledUse(void);
M2C_UNK func_82157DA0(s8 *);                      /* extern */
void func_82157E28(s8 *arg0);
void BattleAnim_RunBoomUseEffect1(Particle* arg0);
void BattleAnim_CallbackStartEffects50And82ScalePulse_InitParticle(Particle* arg0);
void BattleAnim_RunBoomUseEffect2(Particle* arg0);
void BattleAnim_SetupBoomUseEffect3(Particle* arg0);
M2C_UNK func_82158344(s8 *);                      /* extern */
void BattleAnim_RunBoomUseEffect3(s8 *arg0);
M2C_UNK func_8215856C(s8 *);                      /* extern */
void BattleAnim_RunBoomUseEffect4(s8 *arg0);
void func_821588C0(s8 *arg0);
void BattleAnim_RunBoomUseEffect6(Particle* arg0);
void BattleAnim_RunBoomHitEffect1(s8 *arg0);
void BattleAnim_SetupBoomHitEffect2(Particle* arg0);
M2C_UNK func_82158CE0(s8 *);                      /* extern */
void BattleAnim_RunBoomHitEffect2(s8 *arg0);
M2C_UNK func_82158F20(s8 *);                      /* extern */
void BattleAnim_RunBoomHitEffect3(s8 *arg0);
void BattleAnim_InitializeBoomUse(void);
void BattleAnim_InitializeBoomHit(void);
M2C_UNK func_821597D0(s8 *);                      /* extern */
void func_82159898(s8 *arg0);
void BattleAnim_InitializeGuillotineHit(void);
void BattleAnim_CallbackStartEffect69ModelPhaseWait(Particle* arg0);
void BattleAnim_InitializeDigBurrowUse(void);
void BattleAnim_InitializeDigHit(void);
void BattleAnim_InitializeBoneClubUse(void);
f32 func_8215AEA4(Particle* arg0);
void BattleAnim_InitializeEarthquakeFissureUse(void);
void BattleAnim_InitializeDefenseCurlUse(void);
void BattleAnim_InitializeSharpenUse(void);
void func_8215B5B8(void);
void BattleAnim_InitializeLickUse(void);
f32 func_8215B6A4(Particle* arg0);
void BattleAnim_InitializeLovelyKissUse(void);
void BattleAnim_InitializeLovelyKissHit(void);
void func_8215B83C(s8 *arg0);
void BattleAnim_InitializeDreamEaterUse(void);
void BattleAnim_CreateDrainingMoveOverlay(void);
void BattleAnim_InitializeNightShadeUse(void);
void BattleAnim_InitializeNightShadeHit(void);
M2C_UNK func_8215C8FC(s8 *);                      /* extern */
void func_8215C984(s8 *arg0);
M2C_UNK func_8215CA14();                            /* extern */
void BattleAnim_ConfuseRayParticleUpdate(s8 *arg0);
void func_8215CCF0(void);
void BattleAnim_InitializeConfuseRayUse(void);
void BattleAnim_InitializeConfuseRayHit(void);
void BattleAnim_InitializeWaterfallUse(void);
void BattleAnim_InitializeWaterfallHit(void);
void BattleAnim_InitializeSurfUseSpray(void);
void BattleAnim_InitializeSurfHit(void);
void BattleAnim_InitializeCrabhammerUse(void);
M2C_UNK func_8215D724(s8 *);                      /* extern */
void func_8215D76C(s8 *arg0);
M2C_UNK func_8215DA5C(s8 *);                      /* extern */
void func_8215DAEC(s8 *arg0);
void BattleAnim_InitializePsywaveHit(void);
void BattleAnim_RunConfusionPsychicHitEffect(Particle* arg0);
void BattleAnim_InitializePsychicUse(void);
void BattleAnim_InitializeConfusionUse(void);
void BattleAnim_InitializePsychicHit(void);
void BattleAnim_InitializeConfusionHit(void);
void BattleAnim_InitializeFocusEnergyUse(void);
void BattleAnim_InitializeSkyAttackUse1(void);
void BattleAnim_InitializeSkyAttackUse2(void);
void BattleAnim_InitializeSolarBeamUse2(void);
void BattleAnim_MegaHitModelFade(Particle* arg0);
void BattleAnim_InitializeLargePhysicalHitSpark(void);
void BattleAnim_InitializeHornDrillHit(void);
void BattleAnim_RunWeakSpear(Particle* arg0);
void BattleAnim_InitializeFuryAttackPeckUse(void);
void BattleAnim_InitializeHornAttackUse(void);
void func_8215F1B0(s8 *arg0);
void BattleAnim_InitializeSonicBoomUse(void);
M2C_UNK func_8215F2B8(s8 *);                      /* extern */
void func_8215F3EC(s8 *arg0);
M2C_UNK func_8215E510();                            /* extern */

// anim_contact_effects.c
void BattleAnim_SetupSlashingMoveUse(Particle* arg0);
void BattleAnim_SetupRazorWindHitEffect(Particle* arg0);
void BattleAnim_SetupPetalDanceRazorLeafHitEffect(Particle* arg0);
void BattleAnim_HeavyHitBurstChild_InitParticle(Particle* arg0);
void BattleAnim_SetupSandAttackHitEffect(Particle* arg0);
void BattleAnim_HeavyHitAnimatedRiseFade_InitParticle(Particle* arg0);
void BattleAnim_SetupIceBeamIcePunchEffect(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach_InitParticle(Particle* arg0);
void BattleAnim_SetupGroundedCircularHitSpark(Particle* arg0);
void BattleAnim_SetupUnusedGlitterVariant(Particle* arg0);
void BattleAnim_SetupPointyMoveHitSparkChild(Particle* arg0);
void BattleAnim_SetupPhysicalHitPurpleSmoke(Particle* arg0);
void BattleAnim_SetupSwiftHitEffect2(Particle* arg0);
void BattleAnim_SetupBlizzardHitEffect(Particle* arg0);
void BattleAnim_SetupThunderPunchHitEffect(Particle* arg0);
void BattleAnim_SetupDefaultHitSpark(Particle* arg0);
void BattleAnim_SetupHeavyHitSparksAndSmoke(Particle* arg0);
void BattleAnim_SetupPointyMoveHitSpark(Particle* arg0);
void BattleAnim_SetupFirePunchUseEffect1(Particle* arg0);
void BattleAnim_SetupFirePunchUseEffect2(Particle* arg0);
void BattleAnim_SetupThunderPunchUseEffect(Particle* arg0);
void BattleAnim_RecolorParticleByQueuedMoveId(Particle* arg0);
void BattleAnim_PowderCloudScaleMotion_InitParticle(Particle* arg0);
void BattleAnim_SetupAcidArmorUseEffect2(Particle* arg0);
void BattleAnim_RunRazorWindHitEffect(Particle* arg0);
void BattleAnim_RunPetalDanceRazorLeafHitEffect(Particle* arg0);
void BattleAnim_HeavyHitAnimatedRiseFade(Particle* arg0);
void BattleAnim_RunGroundedCircularHitSpark(Particle* arg0);
void BattleAnim_RunPhysicalHitPurpleSmoke(Particle* arg0);
void BattleAnim_SwiftBurstChild(Particle* arg0);
void BattleAnim_RunSwiftHitEffect2(Particle* arg0);
void BattleAnim_RunSparkleHit(Particle* arg0);
void BattleAnim_RunDefaultHitSpark(Particle* arg0);
void BattleAnim_RunHeavyHitSparksAndSmoke(Particle* arg0);
s32 BattleAnim_RunPointyMoveHitSpark(Particle* arg0);
M2C_UNK func_8215F930(s8 *);                      /* extern */
void func_8215FAA4(s8 *arg0);
void BattleAnim_SetupSlashingMoveFullScreenFlash(Particle* arg0);
void BattleAnim_RunSlashingMoveFullScreenFlash(s8 *arg0);
void BattleAnim_SetupSlashMoveWhiteFlashOverlay(Particle* arg0);
void BattleAnim_RunSlashMoveWhiteFlashOverlay(s8 *arg0);
void BattleAnim_SlashGrowFade_InitParticle(Particle* arg0);
M2C_UNK func_8216031C(s8 *);                      /* extern */
void func_821603C8(s8 *arg0);
M2C_UNK func_82160494(s8 *);                      /* extern */
void func_82160528(s8 *arg0);
void BattleAnim_SetupSmallSand(s8 *arg0);
void BattleAnim_RunSmallSand(s8 *arg0);
void BattleAnim_SetupLargeSand(s8 *arg0);
void BattleAnim_RunLargeSand(s8 *arg0);
void BattleAnim_SetupSandAttackUseEffect(Particle* arg0);
M2C_UNK func_821609F0(s8 *);                      /* extern */
void BattleAnim_SandAttackParticleUpdate(s8 *arg0);
void func_82160BB8(s8 *arg0);
void func_82160CCC(s8 *arg0);
M2C_UNK func_82160DC4(s8 *);                      /* extern */
void BattleAnim_RunSandAttackHitEffect(s8 *arg0);
M2C_UNK func_82161190(s8 *);                      /* extern */
M2C_UNK func_82161358(s8 *);                      /* extern */
void func_8216140C(s8 *arg0);
M2C_UNK func_821615F8(s8 *);                      /* extern */
void func_821616BC(s8 *arg0);
M2C_UNK func_8216177C(s8 *);                      /* extern */
void BattleAnim_RunPointyMoveHitSparkChild(s8 *arg0);
void BattleAnim_SwiftBurstChild_InitParticle(Particle* arg0);
void BattleAnim_SetupSharedScalePulseFallSetup(Particle* arg0);
void BattleAnim_RunBlizzardHitEffect(Particle* arg0);
void BattleAnim_RunThunderPunchHitEffect(Particle* arg0);
void BattleAnim_RunFirePunchUseEffect1(Particle* arg0);
M2C_UNK func_821635E4(s8 *);                      /* extern */
void BattleAnim_FirePunchParticleUpdate(s8 *arg0);
M2C_UNK func_82163884(s8 *);                      /* extern */
void func_821639EC(s8 *arg0);
M2C_UNK func_82163C28(s8 *);                      /* extern */
void BattleAnim_AcidArmorParticleUpdateB(Particle* arg0);
void BattleAnim_AcidArmorParticleUpdateA(s8 *arg0);

// anim_contact_effects_2.c
void BattleAnim_ApplySpeciesKeyedSpawnOffset(Particle* arg0);
void BattleAnim_SetupBarrageUseEffect2(Particle* arg0);
void BattleAnim_CallbackDescriptor50BurstChild_InitParticle(Particle* arg0);
void BattleAnim_EndEffect16_NoOpInit(void);
void BattleAnim_SetupSolarBeamUseEffect(Particle* arg0);
void BattleAnim_SetupQiChargeChild(Particle* arg0);
void BattleAnim_SolarbeamMimicBurstEmitter(Particle* arg0);
void BattleAnim_RunAcidArmorUseEffect2(Particle* arg0);
void BattleAnim_InitSharedVerticalFadeParticle(Particle* arg0);
M2C_UNK func_82164B9C(s8 *);                      /* extern */
void BattleAnim_RunSplashOfWater(s8 *arg0);
void BattleAnim_RunBarrageUseEffect2(Particle* arg0);
M2C_UNK func_82165100(s8 *);                      /* extern */
void func_82165224(s8 *arg0);
void BattleAnim_CallbackDescriptor50BurstEmitter_InitParticle(Particle* arg0);
void BattleAnim_CallbackDescriptor50BurstEmitter(Particle* arg0);
void func_8216547C(s8 *arg0);
void BattleAnim_RunSolarBeamUseEffect(Particle* arg0);
void BattleAnim_RunQiChargeChild(Particle* arg0);
void BattleAnim_SetupQiCharge(Particle* arg0);
void func_82165854(Particle* arg0);
void BattleAnim_CallbackDescriptor26BurstChild_InitParticle(Particle* arg0);

// anim_contact_effects_3.c
void BattleAnim_CallbackDescriptor26BurstChild(Particle* arg0);
void func_82165BC8(s32 arg0);
void BattleAnim_CallbackDescriptor26BurstEmitter(Particle* arg0);
void BattleAnim_SetupUnusedGrowingSparkVariant(Particle* arg0);

// anim_hit_sparks.c
M2C_UNK func_82166B34();                            /* extern */
M2C_UNK func_82168504();                            /* extern */
M2C_UNK func_82168844(M2C_UNK);                     /* extern */
void BattleAnim_RunStrongContactMoveHitSpark(void);
void BattleAnim_InitializeUniqueSharedHitSpark(void);
void BattleAnim_InitializeLowKickHit(void);
void BattleAnim_InitializeDefaultLimbForMove(void);
void BattleAnim_InitializeSpecialLimbForMove(void);
void BattleAnim_InitializePointyMoveHitSparks(void);
void BattleAnim_InitializePoisonStingTwineedleHit(void);
void BattleAnim_InitializeFuryAttackGustHit(void);
void BattleAnim_OrphanDescriptor34Emitter(void);
void BattleAnim_InitializeSubmissionUse(void);
void BattleAnim_InitializeStompHit(void);
void BattleAnim_InitializeGroundedCircularHitSpark(void);
void BattleAnim_InitializeSubmissionHit(void);
void BattleAnim_InitializeBitingMoveEndEffect(void);
void BattleAnim_InitializeSwiftHit(void);
void BattleAnim_StartEffect137Descriptor3FRisingFade(void);
void BattleAnim_InitializeRazorWindHit(void);
void BattleAnim_InitializePetalDanceHitSequence(void);
void BattleAnim_InitializeDoubleEdgeTakeDownUse(void);
void BattleAnim_InitializeBodySlamUse(void);
void BattleAnim_InitializeDefenseCurlSharpenUseSequence(void);
void BattleAnim_InitializeQiCharge(s32 arg0);
void BattleAnim_InitializeRecoverUse(void);
void BattleAnim_CallbackUnusedGrowingSparkVariant(Particle* arg0);
void BattleAnim_InitializeIcePunchUse(void);
void BattleAnim_InitializeIcePunchHit(void);
void BattleAnim_InitializeThunderPunchHit(void);
void BattleAnim_InitializeSwiftUse(void);
void func_82166DC4(void);
void BattleAnim_InitializeScratchSlashUse(void);
void BattleAnim_InitializeCutCrabhammerHit(void);
void BattleAnim_InitializeScratchSlashHit(void);
void BattleAnim_InitializeCutEffect(void);
void BattleAnim_InitializeVineWhipUse(void);
void BattleAnim_InitializeVineWhipHit(void);
void BattleAnim_InitializeFirePunchUse(void);
void BattleAnim_InitializeRazorLeafUse(void);
void BattleAnim_InitializeRazorLeafHit(void);
void BattleAnim_InitializePetalDanceUse(void);
void BattleAnim_InitializePowderSporeGasMoveHit(void);
void BattleAnim_InitializeSandAttackUse(void);
void BattleAnim_InitializeSandAttackHit(void);
void BattleAnim_InitializeAcidArmorUse(void);
void BattleAnim_InitializeFlashUse(void);
void BattleAnim_InitializeFlashHit(void);
void BattleAnim_InitializeBideRageUse(void);
void BattleAnim_InitializeStruggleThrashUse(void);
void BattleAnim_InitializeEarthquakeFissureHitSequence(void);
void func_82168364(void);
void BattleAnim_InitializeSubstituteTransformUse(void);
void BattleAnim_InitializeMimicConversionUse(void);
void BattleAnim_InitializeGrowthUse(void);
void BattleAnim_InitializeHardenUse(void);

// particle_gfx.c
void ParticleGfx_PipeSync(void);
void ParticleGfx_SetTextureState(void);
s32 ParticleGfx_TextureSizeLog2(s32 size);
void ParticleGfx_NoopStub2(void);
void ParticleGfx_NoopStub3(void);
void ParticleGfx_NoopStub4(void);
void ParticleGfx_LoadTextureBlock32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureTile32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureBlock16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureTile16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureBlock8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureTile8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureBlock4(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureTile4(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureMultiBlock4(u8* texture, s32 tmem, s32 rtile, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureRgba32(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileRgba32(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16Dual(u8* texture1, u8* texture2, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapS(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapT(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapSWithMask(u8* texture, s32 width, s32 height, s32 masks);
void ParticleGfx_LoadTextureTileRgba16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileIa16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileIa8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa8WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI8WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI8Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI8Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileIa4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI4Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4WrapS(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4WrapSTNoMirror(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4MultiBlockWrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4MultiBlockWrapSTWithShift(u8* texture, s32 width, s32 height, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureCi8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureCi8WrapSWithMask(u8* texture, s32 width, s32 height, s32 masks);
void ParticleGfx_LoadTextureTileCi8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureDualRgba16I8(u8* texture1, u8* texture2, s32 width, s32 height);
void ParticleGfx_DrawQuadVertices(Vtx* arg0);
void ParticleGfx_DrawTransformedQuad(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawTransformedQuadYScaled(Vec3f arg0, Vec3s arg1, f32 arg3, Vtx* arg4);
void ParticleGfx_DrawTransformedQuadXYScaled(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3, Vtx* arg4);
void ParticleGfx_DrawTransformedTriangle(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelQuad(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelQuadRotated(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void ParticleGfx_DrawModelQuadYScaled(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelQuadRotatedYScaled(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void ParticleGfx_DrawModelTriangle(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelTriangleRotated(CameraNode* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void ParticleGfx_DrawI8TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawIa16TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawIa8TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawI4TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawI4TextureAtlasTiled(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_SetPrimColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetEnvColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetFogColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetBlendColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetPrimColorTextureCombine(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetTextureAlphaCombine(u8 a);
void ParticleGfx_SetPrimEnvColorCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a);
void ParticleGfx_SetPrimEnvNoiseCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a);
void ParticleGfx_SetPrimEnvColorShadeCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b, u8 env_a);
void ParticleGfx_SetPrimEnvLodCombine(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b);
void ParticleGfx_SetPrimEnvLodTextureCombine(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b);
void ParticleGfx_SetAnimatedTileSize(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void ParticleGfx_SetAnimatedAuxTileSize(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void ParticleGfx_SetAnimatedTileSizeOnList(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetAnimatedAuxTileSizeOnList(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetPartiallyAnimatedTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetPartiallyAnimatedAuxTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

// anim_render.c
void BattleAnim_DrawFullScreenColorOverlay(u8, u8, u8, u8);
void BattleAnim_RenderEffectsFrame(CameraNode*);

// anim_stubs.c
void BattleAnim_EndEffect16_NoOpDraw(void);
void func_8216D978(void);
void func_8216D980(void);
void func_8216D988(void);

// intro_stubs.c
void BattleScene_IntroStepNop(UNUSED CameraNode* arg0);
void func_8216D9C8(UNUSED s32 arg0);
void BattleAnim_DrawStoredColorOverlay(void);
void BattleAnim_ReinitAuxiliaryEffects(void);
s32 BattleAnim_DefaultStartEffect_CompleteImmediately(void);
s32 BattleAnim_DefaultEndEffect_CompleteImmediately(void);
void func_8216D990(void);
void func_8216D998(void);
void func_8216D9A0(void);
void func_8216D9A8(void);
void func_8216D9B8(void);
void func_8216D9D0(void);
void func_8216DA30(void);
void MewtwoIntro_DrawOverlay(void);
void func_8216DA50(void);
void func_8216DA58(void);

// anim_owner_effects.c
void BattleAnim_EffectSecondaryOwnerAnchorPosition(Vec3f* arg0);
f32 BattleAnim_EffectSecondaryOwnerModelScale(void);
void BattleAnim_CalcVectorAtToDm(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void BattleAnim_ResetSharedEffectMatrix(void);
void Battle_GetTertiaryOwnerBonePositionUnused(Vec3f* arg0);
void BattleAnim_EffectTertiaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_EffectSecondaryOwnerBonePosition(Vec3f* arg0);
f32 BattleAnim_EffectTertiaryOwnerModelScale(void);
void BattleAnim_SetupStatRaiseRibbon(void);
s32 BattleAnim_RunStatRaiseRibbon(void);
void BattleAnim_DrawStatRaiseRibbon(void);
void BattleAnim_SetupStatLowerRibbon(void);
s32 BattleAnim_RunStatLowerRibbon(void);
void BattleAnim_DrawStatLowerRibbon(void);
void BattleAnim_EndEffect19RibbonMesh_Init(void);
s32 BattleAnim_EndEffect19RibbonMesh_Update(void);
void BattleAnim_EndEffect19RibbonMesh_Draw(void);
void BattleAnim_SetupHazeUseRibbonMesh(void);
s32 BattleAnim_RunHazeUseRibbonMesh(void);
void BattleAnim_DrawHazeUseRibbonMesh(void);
void BattleAnim_SetupSurfUseTerrainGrid(void);
s32 BattleAnim_RunSurfUseTerrainGrid(void);
void BattleAnim_DrawSurfUseTerrainGrid(void);

// radial_effects.c
void BattleAnim_StartEffect98Radial20_EmitVariantD(void);
s32 BattleAnim_SurfCompleteImmediately(void);
void BattleAnim_StartEffect19Radial20_EmitVariantD(void);
void BattleAnim_StartTrappingLassoMove_Init(void);
s32 BattleAnim_StartTrappingLassoMove_Update(void);
void BattleAnim_StartTrappingLassoMove_Draw(void);
void BattleAnim_EndEffect9Radial20_Init(void);
s32 BattleAnim_EndEffect9Radial20_Update(void);
void BattleAnim_EndEffect9Radial20_Draw(void);
void BattleAnim_StartEffect7TexturedRibbonSheet_Emit(void);
void BattleAnim_SetupSwiftUseRibbonSheet(void);
s32 BattleAnim_RunSwiftUseRibbonSheet(void);
void BattleAnim_DrawSwiftUseRibbonSheet(void);
void BattleAnim_StartEffect33Radial20_EmitVariantC(void);
void BattleAnim_SetupStringShotUseRadial(void);
s32 BattleAnim_RunStringShotUseRadial(void);
void BattleAnim_DrawStringShotUseRadial(void);
void BattleAnim_SetupStringShotHitRadial(void);
s32 BattleAnim_RunStringShotHitRadial(void);
void BattleAnim_DrawStringShotHitRadial(void);
s32 BattleAnim_RunDisableHitRadial(void);
void BattleAnim_DrawDisableHitRadial(void);

// anim_trails.c
void BattleAnim_SetupDisableUseRadial(void);
s32 BattleAnim_RunDisableUseRadial(void);
void BattleAnim_DrawDisableUseRadial(void);
void BattleAnim_SetupRazorLeafUseTrail(void);
s32 BattleAnim_RunRazorLeafUseTrail(void);
void BattleAnim_DrawRazorLeafUseTrail(void);
void BattleAnim_SetupPetalDanceUseTrail(void);
s32 BattleAnim_RunPetalDanceUseTrail(void);
void BattleAnim_DrawPetalDanceUseTrail(void);
void BattleAnim_SetupHypnosisScreechUseTrail(void);
s32 BattleAnim_RunHypnosisScreechUseTrail(void);
void BattleAnim_DrawHypnosisScreechUseTrail(void);
void BattleAnim_SetupSingUseTrail(void);
s32 BattleAnim_RunSingUseTrail(void);
void BattleAnim_DrawSingUseTrail(void);
void BattleAnim_SetupKinesisSupersonicUseTrail(void);
s32 BattleAnim_RunKinesisSupersonicUseTrail(void);
void BattleAnim_DrawKinesisSupersonicUseTrail(void);
void BattleAnim_SetupSonicBoomUseFourStream(void);
void BattleAnim_DrawSonicBoomUseFourStream(void);
void BattleAnim_SetupSpikeCannonUseFourStream(void);
s32 BattleAnim_RunSpikeCannonUseFourStream(void);
void BattleAnim_DrawSpikeCannonUseFourStream(void);
void BattleAnim_StingerMoves_Init(void);
s32 BattleAnim_StingerMoves_Update(void);
void BattleAnim_StingerMoves_Draw(void);
void BattleAnim_SetupTriAttackUseRadial(void);
s32 BattleAnim_RunTriAttackUseRadial(void);
void BattleAnim_DrawTriAttackUseRadial(void);
void BattleAnim_SeedAuroraBeamUseDoubleTextureTrail(void);
void BattleAnim_SetupAuroraBeamUseDoubleTextureTrail(void);
s32 BattleAnim_RunAuroraBeamUseDoubleTextureTrail(void);
void BattleAnim_DrawAuroraBeamUseDoubleTextureTrail(void);
void BattleAnim_SeedIceBeamUseSixSlotTrail(void);
void BattleAnim_SetupIceBeamUseSixSlotTrail(void);
s32 BattleAnim_RunIceBeamUseSixSlotTrail(void);
void BattleAnim_DrawIceBeamUseSixSlotTrail(void);
void BattleAnim_SeedPsybeamUseDoubleTextureTrail(void);
void BattleAnim_SetupPsybeamUseDoubleTextureTrail(void);
s32 BattleAnim_RunPsybeamUseDoubleTextureTrail(void);
void BattleAnim_DrawPsybeamUseDoubleTextureTrail(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect77DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Draw(void);
void BattleAnim_SeedSolarBeamUseDoubleTextureTrail(void);
void BattleAnim_SetupSolarBeamUseDoubleTextureTrail(void);
s32 BattleAnim_RunSolarBeamUseDoubleTextureTrail(void);
void BattleAnim_DrawSolarBeamUseDoubleTextureTrail(void);
void BattleAnim_SeedHyperBeamUseDoubleTextureTrail(void);
void BattleAnim_EmitTriAttackUseRadial(void);
s32 BattleAnim_RunSonicBoomUseFourStream(void);

// anim_trails_2.c
void BattleAnim_SeedHyperBeamUseSixSlotTrail(void);
void BattleAnim_SetupHyperBeamUseCombinedTrail(void);
s32 BattleAnim_RunHyperBeamUseCombinedTrail(void);
void BattleAnim_DrawHyperBeamUseCombinedTrail(void);

// stat_ribbon.c
void StatRibbon_Init(void);
void StatRibbon_Configure(RibbonMesh* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                   s32 arg9);
void StatRibbon_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);

// stat_ribbon_surf_grid.c
void StatRibbon_UpdateEnvAlpha(RibbonMesh* arg0);
s32 StatRibbon_Update(RibbonMesh* arg0);
s32 StatRibbon_UpdatePool(void);
Gfx* StatRibbon_Draw(Gfx* arg0, RibbonMesh* arg1);
Gfx* StatRibbon_DrawPool(Gfx* arg0);
void SurfTerrainGrid_BuildCameraBounds(unk_D_843975E8* arg0, f32 arg1);
f32 SurfTerrainGrid_SampleHeightAndSlope(f32 x, f32 z, f32* rotation_x);
s32 SurfTerrainGrid_UpdateWaves(void);
void SurfTerrainGrid_Init(s32 arg0, s16 arg1, s16 arg2);
s32 SurfTerrainGrid_Update(void);

// surf_terrain_grid.c
Gfx* SurfTerrainGrid_Draw(Gfx* arg0);

// radial_lasso.c
void LassoHit_Init(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
f32 Strip400_GetTailFadeRatio(void);
s32 LassoHit_Update(void);
Gfx* Strip400_Draw(Gfx* arg0);
void Radial20_ResetPool(void);
void TriAttackRadial_EmitVariantA(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_VariantB(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_VariantC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_VariantE(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_RotateVertexOffset(f32 arg0, UNUSED Vec3f* arg1, Vec3f* arg2, f32 arg3, UNUSED f32 arg4, UNUSED f32 arg5, UNUSED f32 arg6);
void Radial20_UpdateNode(Radial20* arg0);
s32 Radial20_IsComplete(void);
Gfx* Radial20_Draw(Gfx* arg0);

// hypnosis_screech_trail.c
void HypnosisScreechTrail_Init(s16 arg0);
void HypnosisScreechTrail_Start(s32 arg0, s32 arg1);
void HypnosisScreechTrailNode_FillVertex(Trail40Node* arg0, Vtx* arg1);
s32 HypnosisScreechTrail_IsComplete(void);
void Trail40_Reset(void);
Gfx* HypnosisScreechTrail_Draw(Gfx* arg0);

// sing_trail.c
void SingTrail_ApplyRippleAtPoint(s16 arg0, s16 arg1);
void SingTrail_InitPool(s16 arg0);
void SingTrail_UpdateNodes(s32 arg0, s32 arg1);
void SingTrail_WriteVertex(Trail40VariantNode* arg0, Vtx* arg1);
s32 SingTrail_AdvanceTimer(void);
void Trail40Variant_SetupCameraTransform(void);
Gfx* SingTrail_BuildGfx(Gfx* arg0);

// trail40_grid.c
void Trail40GridAlt_Init(s16 arg0);
void Trail40GridAlt_Start(s32 arg0, s32 arg1);
void Trail40GridAlt_FillVertex(Trail40Node* arg0, Vtx* arg1);
s32 Trail40GridAlt_IsComplete(void);
void Trail40GridAlt_Reset(void);
Gfx* Trail40GridAlt_Draw(Gfx* arg0);

// swift_ribbon.c
void SwiftRibbonSheet_Init(void);
void SwiftRibbonSheet_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, s16 argB);
void SwiftRibbonSheet_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void SwiftRibbonSheet_UpdateRecord(TexturedRibbonSheet* arg0);
s32 SwiftRibbonSheet_IsComplete(void);
Gfx* SwiftRibbonSheet_Draw(Gfx* arg0);

// thick_line.c
Gfx* Gfx_DrawThickLine(Gfx* arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);

// four_stream_trail.c
void FourStreamTrail_Init(void);
void FourStreamTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void FourStreamTrail_Update(f32 arg0, Vec3f* arg1, f32 arg2, f32 arg3);
void FourStreamTrail_UpdateNodeChain(FourStreamTrail* arg0);
s32 FourStreamTrail_IsComplete(void);
Gfx* FourStreamTrail_Draw(Gfx* arg0);

// spike_cannon_trail.c
void SpikeCannonFourStream_Init(void);
void SpikeCannonFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void SpikeCannonFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void SpikeCannonFourStream_UpdateNodeChain(OwnerLinkedFourStream* arg0);
s32 SpikeCannonFourStream_IsComplete(void);
Gfx* SpikeCannonFourStream_Draw(Gfx* arg0);

// owner_anchored_trail.c
void OwnerAnchoredFourStream_Init(void);
void OwnerAnchoredFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void OwnerAnchoredFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void OwnerAnchoredFourStream_UpdateNodeChain(OwnerAnchoredFourStream* arg0);
s32 OwnerAnchoredFourStream_IsComplete(void);
Gfx* OwnerAnchoredFourStream_Draw(Gfx* arg0);

// petal_dance_trail.c
void PetalDanceTrail_Init(void);
void PetalDanceTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void PetalDanceTrail_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void PetalDanceTrail_AdvanceNodes(Trail50Effect* arg0);
s32 PetalDanceTrail_IsComplete(void);
Gfx* PetalDanceTrail_Draw(Gfx* arg0);

// razor_leaf_trail.c
void RazorLeafTrail_Init(void);
void RazorLeafTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void RazorLeafTrail_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void RazorLeafTrail_AdvanceNodes(Trail50Effect* arg0);
s32 RazorLeafTrail_IsComplete(void);
Gfx* RazorLeafTrail_Draw(Gfx* arg0);

// double_texture_trail.c
void DoubleTextureTrail_InitPool(void);
void DoubleTextureTrail_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, s16 argB, s32 argC, s32 argD, s16 argE, s16 argF, s16 arg10, s16 arg11, s16 arg12, s16 arg13, s16 arg14, s16 arg15, unk_D_843C2C00_024* arg16, unk_D_843C2C00_024* arg17, u8 arg18, u8 arg19, u8 arg1A, u8 arg1B, u8 arg1C, u8 arg1D, u8 arg1E, u8 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, u8 arg24);
void DoubleTextureTrail_RotateVertexOffset(f32 arg0, Vec3f* arg1, f32 arg2);
void DoubleTextureTrail_Update(DoubleTextureTrail* arg0);
s32 DoubleTextureTrail_UpdateAll(void);
Gfx* WaterParticle_DrawPass(Gfx* arg0, DoubleTextureTrail* arg1, s16 arg2, s16 arg3);
Gfx* DoubleTextureTrail_LoadTextures(Gfx* arg0, DoubleTextureTrail* arg1);
Gfx* DoubleTextureTrail_DrawAll(Gfx* arg0);

// hyper_beam_ice_beam_trail.c
void HyperBeamIceBeamTrail_ResetPool(void);
void HyperBeamIceBeamTrail_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, f32 arg10, f32 arg11, f32 arg12, s16 arg13, s32 arg14, s32 arg15, s16 arg16, s16 arg17, s16 arg18, s16 arg19, s16 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, unk_D_843C2C00_024* arg1E, unk_D_843C2C00_024* arg1F);
void HyperBeamIceBeamTrail_ComputeCameraRelativeOffset(s32 arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void HyperBeamIceBeamTrail_ComputeRotatedOffset(f32 arg0, Vec3f* arg1, Vec3f* arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void HyperBeamIceBeamTrail_UpdateSlot(unk_D_843C3508* arg0);
s32 HyperBeamIceBeamTrail_UpdateAll(void);
Gfx* HyperBeamIceBeamTrail_DrawSegments(Gfx* arg0, unk_D_843C3508* arg1);
Gfx* HyperBeamIceBeamTrail_LoadTextures(Gfx* arg0, unk_D_843C3508* arg1);
Gfx* HyperBeamIceBeamTrail_DrawAll(Gfx* arg0);

// auxiliary_effect.c
void AuxiliaryEffect_Init(void);
s16 AuxiliaryEffect_Alloc(void);
void AuxiliaryEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5);
void AuxiliaryEffect_Update(s16 arg0);
Gfx* AuxiliaryEffect_DrawOne(Gfx* arg0, AuxiliaryEffectNode* arg1, MtxF* arg2);
Gfx* AuxiliaryEffect_Draw(s16 arg0, Gfx* arg1);
s32 AuxEffect_GetId(s32 arg0);

// strip_wipe.c
void BattleScene_SetStripWipeState(s32 arg0, s32 arg1);
s32 BattleScene_GetStripWipeState(void);
void BattleScene_UpdateStripWipe(void);
Gfx* BattleScene_BuildStripWipeDisplayList(Gfx* arg0, s32 arg1);
void BattleScene_DrawStripWipe(void);

// com_ai.c
s32 BattleAi_RandomPercent(void);
void func_82183D9C(void);
void func_82183DA4(void);
void func_82183DAC(void);
void func_82183DC4(void);
void func_82183E1C(void);

// com_ai_2.c
s32 BattleAi_OpponentCannotAct(ComBattler* arg0, ComBattler* arg1);
void func_821853EC(void);
void func_821853F4(void);
void func_821853FC(void);

// com_ai_move_choice.c
void BattleAi_RecordUsedMove(UNUSED s32 arg0, UNUSED s32 arg1, s32 arg2);

// functions defined in assembly
void Audio_SetChannelGroupCounts(u8, u8, u8, u8);
s32 Audio_PlaySoundEffectById(u32 sfx);
s32 Controller_CheckAccessoryEeprom(void);
s32 Diorama_LogoRotateColorCallback(s32, GraphNode*);
s32 Diorama_ScaleRotateCallbackA(s32, GraphNode*);
s32 Diorama_ScaleRotateCallbackB(s32, GraphNode*);
s32 Diorama_GroupStateCallback(s32, GraphNode*);
void BattleAnim_CallbackMove86StartDescriptor24(Particle* arg0);
void BattleAnim_CallbackMove73EndEffect31SpawnDescriptor42(Particle* arg0);
void BattleAnim_CallbackEndEffects10And50ModelAnimColorFade(Particle* arg0);
void BattleAnim_CallbackStartEffect10Model60AlphaFadeIn(Particle* arg0);
void BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle(Particle* arg0);
void BattleAnim_CallbackStartEffects21And93ModelAlphaAnchorFollow(Particle* arg0);
void BattleAnim_CallbackMove140EndEffect65EmitDescriptor4A(Particle* arg0);
void BattleAnim_CallbackEndEffect79DefaultDescriptorPaletteFade(Particle* arg0);
void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade(Particle* arg0);
M2C_UNK BattleAnim_InitializeQuickAttackHiJumpKickUse();                            /* extern */
void BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach(Particle* arg0);
void BattleAnim_CallbackSharedAnimatedVerticalFade(Particle* arg0);
void BattleAnim_InitializeCutUse(void);
void BattleScene_Init(StageContext* stage_context);
s32 BattleAnim_PollAssetLoadBusyFlags(ActivePokemon* active_pokemon);
s32 BattleAnim_IsSessionBusy(ActivePokemon* active_pokemon);
void Battle_MarkIllegalMoves(ActivePokemon* pokemon, u16 pokemon_id, SpeciesLearnsetBuffer* red_blue_learnset, SpeciesLearnsetBuffer* yellow_learnset);
void BattleScene_TryQueueIdleCueEffect(ActivePokemon* active_pokemon);
void BattleThumbnail_InitializeOwnerCameraFraming(CameraNode* side1_camera_node, ActivePokemon* side1_pokemon, CameraNode* side2_camera_node, ActivePokemon* side2_pokemon);
void BattleThumbnail_TickOwnerSlideOut(ActivePokemon* active_pokemon, s32 delta);
s32 BattleScene_GetTeamMemberTeamSize(ActivePokemon* active_pokemon);
s32 BattleScene_GetPartnerTeamSize(ActivePokemon* active_pokemon);
s32 BattleScene_GetHitCueAlternateAnchor(ActivePokemon* active_pokemon);
s16 BattleScene_GetParticipantUsedMove(ActivePokemon* active_pokemon);
void BattleAnim_GetOwnerDefaultAnchorPosition(ActivePokemon* arg0, Vec3f* arg1);
void BattleScene_GetParticipantPokeBallPosition(ActivePokemon* arg0, Vec3f* arg1);
s32 Battle_GetDisplayModelId(ActivePokemon* active_pokemon, UNUSED s32 unused);
void BattleScene_SetParticipantModelTransform(ActivePokemon* active_pokemon, s32 transform_id, s32 transform_timer);
void BattleScene_BindParticipantTeamRoster(ActivePokemon* active_pokemon, s32 team_member_index);
void BattleScene_SetParticipantTeamMember(ActivePokemon* active_pokemon, s32 team_member_index);
void BattleAnim_DigEnd(ActivePokemon* owner, ActivePokemon* animated_pokemon);
s32 BattleScene_ApplyForcedActionDelay(ActivePokemon* active_pokemon);
void BattleScene_HandlePlayerMoveSelection(ActivePokemon* active_pokemon);
s32 BattleScene_HandlePlayerMoveSelectionLocked(ActivePokemon* arg0, UNUSED Controller* arg1);
void Battle_DrawSpectatorModeBackgroundPanel(void);
void BattleScene_PhaseSendOut(CameraNode* arg0);
void BattleScene_RunFinalPresentation(CameraNode* arg0, UNUSED ActivePokemon* arg1, UNUSED ActivePokemon* arg2);
s32 BattleAnim_DispatchPresentation(s32 arg0, CameraNode* arg1);
void BattleAnim_GetOwnerSpeciesBaseScaleAlias(ActivePokemon* active_pokemon);
void BattleAnim_DrawI4AtlasYScaled(Particle* arg0, u8* arg1);
void BattleAnim_DrawAsset19I4AtlasYScaled(Particle* arg0, UNUSED CameraNode* arg1);
void BattleAnim_CallbackGlobalTintColorFadeDetach(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintRampDetach(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintHoldFadeDetach(Particle* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteApproachInactive(Particle* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor46AnimatedFade(Particle* arg0);
void BattleAnim_CallbackEndEffect40Descriptor3DSpreadRisingColorFade(Particle* arg0);
void BattleAnim_CallbackEndEffects54And56Descriptor3DRisingColorScaleFade(Particle* arg0);
void BattleAnim_CallbackEndEffects40And54Descriptor46SpreadScaleFade(Particle* arg0);
void BattleAnim_CallbackEndEffects15And22And59Descriptor3DRotatingAlphaScaleFade(Particle* arg0);
void BattleAnim_CallbackEndEffect59Descriptor4FColorScaleFade(Particle* arg0);
void BattleAnim_CallbackEndEffect16Descriptor45DelayedRotatingMotion(Particle* arg0);
void BattleAnim_CallbackStartEffect58Descriptor0ABurstChild(Particle* arg0);
void BattleAnim_CallbackStartEffect58Descriptor08MetadataBurstChild(Particle* arg0);
void BattleAnim_CallbackStartEffect6Descriptor0ABurstChild(Particle* arg0);
void BattleAnim_CallbackStartEffect6Descriptor08MetadataBurstChild(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor19AnimatedFadeMotion(Particle* arg0);
void BattleAnim_CallbackEndEffect2Descriptor19AnimatedAlphaFade(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor19RecolorAnimatedFade(Particle* arg0);
void BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor19DelayedAnimatedGrowFade(Particle* arg0);
void BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade(Particle* arg0);
void BattleAnim_CallbackEndEffects2And27Descriptor0AFallingSparkFade(Particle* arg0);
void BattleAnim_CallbackStartEffects18And73Descriptor11ScatterRiseFade(Particle* arg0);
void BattleAnim_CallbackSharedDirectionalSprayFade(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade(Particle* arg0);
void BattleAnim_CallbackStartEffect59EndEffect28DirectionalStreamFade(Particle* arg0);
void BattleAnim_InitStartEffect135ExpandingFlash(Particle* arg0);
void BattleAnim_CallbackOrphanDescriptor2EScatterFade(Particle* arg0);
void BattleAnim_CallbackStartEffects50And82Descriptor48AnimatedScaleFade(Particle* arg0);
void BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade(Particle* arg0);
void BattleAnim_CallbackStartEffects50And82CenterModelScalePaletteFade(Particle* arg0);
void BattleAnim_CallbackEndEffects81And82ModelScalePaletteFade(Particle* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor4AAnimatedColorFade(Particle* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor4FAnimatedPaletteFade(Particle* arg0);
void BattleAnim_CallbackStartEffects95To97EndEffects62And63ModelFadeIn_InitParticle(Particle* arg0);
void BattleAnim_CallbackStartEffect101EndEffect65Descriptor4ABurstChild(Particle* arg0);
void BattleAnim_CallbackSharedDescriptor29ScaleAnimFade(Particle* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorFade(Particle* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorAlphaFade(Particle* arg0);
void BattleAnim_SlashGrowFade(Particle* arg0);
void BattleAnim_HeavyHitBurstChild(Particle* arg0);
void BattleAnim_CallbackEndEffect55Descriptor49RiseGravityFade(Particle* arg0);
void BattleAnim_CallbackEndEffect67Descriptor3DAnimatedGravityFade(Particle* arg0);
void BattleAnim_CallbackEndEffects37And38Descriptor38BurstChild(Particle* arg0);
void BattleAnim_CallbackStartEffect73Descriptor15AnimatedColorImpulseFade(Particle* arg0);
void BattleAnim_PowderCloudScaleMotion(Particle* arg0);
void BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade(Particle* arg0);
void BattleAnim_CallbackDescriptor50BurstChild(Particle* arg0);
void BattleAnim_CallbackDescriptor26BurstEmitter_InitParticle(Particle* arg0);
void Radial20_VariantD(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, f32 argE, f32 argF, f32 arg10, s16 arg11);
void BattleAi_CalcDamage(BattleMonRuntime* arg0, BattleMonRuntime* arg1);
s32 Completion_LightAngleCallbackB(s32 arg0, GraphNode* arg1);
void Particle_AdvancePhase(Particle* arg0);
void Particle_Field38_SetXScaled_08C88(Particle* arg0, f32 arg1);
void Particle_Field38_SetYScaled_08CA0(Particle* arg0, f32 arg1);
void Particle_Field38_SetZScaled_08CB8(Particle* arg0, f32 arg1);
void Particle_Field38_AddYScaled_08E90(Particle* arg0, f32 arg1);
void Particle_SetRandomVelocityX(Particle* arg0, s32 arg1);
void Particle_SetRandomVelocityZ(Particle* arg0, s32 arg1);
void Particle_SetRandomVelocityYOffset(Particle* arg0, s32 arg1, s32 arg2);
void Particle_SetRandomVelocityXSymmetric(Particle* arg0, s32 arg1, s32 arg2);
void Particle_SetRandomVelocityZSymmetric(Particle* arg0, s32 arg1, s32 arg2);
void Particle_Field50_AddXYFromField7C_09C34(Particle* arg0);
void Particle_AddVelocityXZFromRotationYViaImpulse(Particle* arg0);
void Particle_AddVelocityFromRotationTemplate3(Particle* arg0);
void Particle_AddVelocityFromRotationTemplate5(Particle* arg0);
void Particle_AddVelocityFromRotationTemplate7B(Particle* arg0);
void Particle_AddVelocityYFromFieldOffset74(Particle* arg0);
void Particle_Field5C_SetYScaled_0A094(Particle* arg0, f32 arg1);
void Particle_Field94_SetX_0A2A4(Particle* arg0, s16 arg1);
void Particle_Field94_SetY_0A2B8(Particle* arg0, s16 arg1);
void Particle_Field94_SetZ_0A2CC(Particle* arg0, s16 arg1);
void Particle_Field94_AddZConstant_0A334(Particle* arg0);
void Particle_SetRotationSpeed(Particle* arg0, s16 arg1, s16 arg2, s16 arg3);
void Particle_Field9A_SetXY_0A3A0(Particle* arg0, s16 arg1, s16 arg2);
void Particle_Field9A_SetX_0A3C4(Particle* arg0, s16 arg1);
void Particle_Field9A_SetY_0A3D8(Particle* arg0, s16 arg1);
void Particle_Field9A_SetZ_0A3EC(Particle* arg0, s16 arg1);
void Particle_FieldA0_SetX_0A400(Particle* arg0, s16 arg1);
void Particle_FieldA0_SetY_0A414(Particle* arg0, s16 arg1);
void Particle_Field94_AddYFromField9A_0A4C8(Particle* arg0);
void Particle_Field94_AddVec_0A52C(Particle* arg0, s16 arg1, s16 arg2, s16 arg3);
void Particle_Field94_AddX_0A578(Particle* arg0, s16 arg1);
void Particle_Field94_AddY_0A594(Particle* arg0, s16 arg1);
void Particle_Field94_AddZ_0A5B0(Particle* arg0, s16 arg1);
void Particle_AddRotationTargetXY(Particle* arg0, s16 arg1, s16 arg2);
void Particle_ApproachRotationTargetX(Particle* arg0);
void Particle_ApproachRotationTargetY(Particle* arg0);
void Particle_ApproachRotationTargetZ(Particle* arg0);
void Particle_Field74_SetScaled_0AD8C(Particle* arg0, f32 arg1);
void Particle_Field78_SetScaled_0ADA4(Particle* arg0, f32 arg1);
void Particle_Field7C_SetYScaled_0AF24(Particle* arg0, f32 arg1);
void Particle_Field7C_ScaleVec_0B14C(Particle* arg0, f32 arg1);
s32 Particle_PrimR_Approach_0BAE4(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_PrimG_Approach_0BB14(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_PrimB_Approach_0BB44(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_EnvR_Approach_0BB90(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_EnvB_Approach_0BBC0(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_EnvG_Approach_0BBF0(Particle* arg0, u8 arg1, u8 arg2);
s32 Particle_PrimAlpha_Approach_0BC2C(Particle* arg0, u8 arg1, u8 arg2);
void Particle_FieldA6_SetS16_0BCA8(Particle* arg0, s16 arg1);
s32 Particle_FieldA6_DecrementTo_0BCC4(Particle* arg0, s16 arg1, s16 arg2);
void Particle_FieldA8_SetS16_0BE14(Particle* arg0, s16 arg1);
s32 Particle_FieldA8_DecrementTo_0BE30(Particle* arg0, s16 arg1);
void Particle_FieldCA_SetU8_0BECC(Particle* arg0, u8 arg1);
void Particle_FieldAC_SetS16_0BED8(Particle* arg0, s16 arg1);
void Particle_FieldCF_SetU8_0BEEC(Particle* arg0, u8 arg1);
void Particle_FieldCF_SetU8Alt_0BEF8(Particle* arg0, u8 arg1);
void Particle_FieldCC_SetU8_0BF04(Particle* arg0, u8 arg1);
void Particle_FieldAA_SetS16_0BF10(Particle* arg0, s16 arg1);
void Particle_FieldCE_SetS16_0BF24(Particle* arg0, s16 arg1);
void Particle_FieldCD_SetS16_0BF38(Particle* arg0, s16 arg1);
void Particle_FieldAE_SetS16_0BF4C(Particle* arg0, s16 arg1);
s32 Particle_FieldAE_Approach_0BF60(Particle* arg0, s16 arg1, s16 arg2);
void Particle_FieldB0_SetS16_0BFEC(Particle* arg0, s16 arg1);
s32 Particle_FieldB0_Approach_0C000(Particle* arg0, s16 arg1, s16 arg2);
s16 Particle_FieldAC_GetS16_0C038(Particle* arg0);
s32 Particle_FieldCE_GetS32_0C040(Particle* arg0);
u8 Particle_FieldCD_GetU8_0C048(Particle* arg0);
s16 Particle_FieldCF_GetS16_0C058(Particle* arg0);
void ParticleGfx_RecolorPrim(Particle* arg0, u16 arg1);
void ParticleGfx_RecolorEnv(Particle* arg0, u16 arg1);
BattleMon* Pokemon_CreateDefault(BattleMon* arg0, u8 arg1, s16 arg2);

#endif // FRAGMENT_BATTLE_H
