//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_ZOMBIEDATA_H
#define LEFT4DEAD_ZOMBIEDATA_H

#include "client_src/characters_src/characterData/CharacterData.h"

struct ZombieData : CharacterData {
    ZombieData() {
        health = 50;
        speed = 5;
        damage = 10;
        attackSpeed = 30;
        attackRange = 5;
    }
};


#endif //LEFT4DEAD_ZOMBIEDATA_H
