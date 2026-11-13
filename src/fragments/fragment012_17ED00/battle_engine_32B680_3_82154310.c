#include "pokemon.h"
/* Fixed-layout split; original translation-unit boundaries remain unconfirmed. */
#include "battle_engine_32B680_3.h"

/**
 * @unverified Name was previously used only by callers of this address; the definition was still func_.
 */
void BattleAnim_ApplyModelSpeciesOffset(Particle* arg0) {
    f32 offset = 0.0f;

    switch (BattleAnim_GetOwnerSpecies(arg0->pokemon)) {
        case BEEDRILL:
            offset = -13.0f;
            break;
        case FEAROW:
            offset = -15.0f;
            break;
        case PIKACHU:
            offset = -10.0f;
            break;
        case NIDOKING:
            offset = 10.0f;
            break;
        case ARCANINE:
            offset = 25.0f;
            break;
        case GOLEM:
            offset = -10.0f;
            break;
        case MAGNETON:
            offset = -8.0f;
            break;
        case CLOYSTER:
            offset = -12.0f;
            break;
        case EXEGGUTOR:
            offset = 5.0f;
            Particle_AddPositionOffsetAlongRotationY(arg0, 10.0f);
            break;
        case STARMIE:
            offset = -8.0f;
            break;
        case PINSIR:
            offset = 5.0f;
            break;
        case TAUROS:
            offset = -12.0f;
            break;
        case GYARADOS:
            offset = -10.0f;
            Particle_SetScaleScaled(arg0, 0.15f);
            break;
        case VAPOREON:
            offset = -5.0f;
            Particle_AddPositionOffsetAlongRotationYMinus90(arg0, 5.0f);
            break;
        case JOLTEON:
            offset = -15.0f;
            break;
    }
    Particle_Field38_AddYScaled_08E90(arg0, offset);
}
