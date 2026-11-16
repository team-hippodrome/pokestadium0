#ifndef POKEMON_TYPES_H
#define POKEMON_TYPES_H

/*
 * Gen 1 type ids, as stored in a Pokemon's two type bytes (BattleMon.type1/type2)
 * and in move data. Values 0x09-0x13 are unused by retail data.
 * The TYPE_ prefix keeps TYPE_PSYCHIC apart from the move PSYCHIC.
 */
#define TYPE_NORMAL    0x00
#define TYPE_FIGHTING  0x01
#define TYPE_FLYING    0x02
#define TYPE_POISON    0x03
#define TYPE_GROUND    0x04
#define TYPE_ROCK      0x05
#define TYPE_BIRD      0x06 /* Leftover type id with no Pokemon or move in retail data. */
#define TYPE_BUG       0x07
#define TYPE_GHOST     0x08
#define TYPE_FIRE      0x14
#define TYPE_WATER     0x15
#define TYPE_GRASS     0x16
#define TYPE_ELECTRIC  0x17
#define TYPE_PSYCHIC   0x18
#define TYPE_ICE       0x19
#define TYPE_DRAGON    0x1A

#endif /* POKEMON_TYPES_H */
