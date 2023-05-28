//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_P90DATA_H
#define LEFT4DEAD_P90DATA_H


#include "game_src/characters_src/characterData/CharacterData.h"

struct P90Data : CharacterData {
    int maxAmmo = 30;
    int burst = 10;
    P90Data() {
        health = 150;
        speed = 3;
        damage = 50;
        attackSpeed = 10;
        attackRange = 20;
    }
};


#endif //LEFT4DEAD_P90DATA_H
