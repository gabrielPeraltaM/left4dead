//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_SCOUTDATA_H
#define LEFT4DEAD_SCOUTDATA_H


#include "game_src/characters_src/characterData/CharacterData.h"

class ScoutData : CharacterData {
    int maxAmmo = 20;
    int burst = 1;
    ScoutData() {
        health = 100;
        speed = 7;
        damage = 200;
        attackSpeed = 10;
        attackRange = 200;
    }
};


#endif //LEFT4DEAD_SCOUTDATA_H
