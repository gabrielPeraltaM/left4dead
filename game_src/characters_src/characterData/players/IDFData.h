//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_IDFDATA_H
#define LEFT4DEAD_IDFDATA_H


#include "game_src/characters_src/characterData/CharacterData.h"

struct IDFData : CharacterData {
    int maxAmmo = 50;
    int burst = 20;
    IDFData() {
        health = 100;
        speed = 5;
        damage = 40;
        attackSpeed = 20;
        attackRange = 50;
    }
};


#endif //LEFT4DEAD_IDFDATA_H
