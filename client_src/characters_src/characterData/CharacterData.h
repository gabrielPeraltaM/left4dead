//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_CHARACTERDATA_H
#define LEFT4DEAD_CHARACTERDATA_H

// Guarda los valores estaticos de cada personaje
// Especialmente útil para mantenerlos balanceados y que no haya
// uno más fuerte que el otro.
// READ - ONLY
struct CharacterData {
    int health;
    int speed;
    int damage;
    int attackSpeed;
    int attackRange;
};


#endif //LEFT4DEAD_CHARACTERDATA_H
