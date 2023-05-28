//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_IDFSTATUS_H
#define LEFT4DEAD_IDFSTATUS_H

#include "game_src/characters_src/characterStatus/CharacterStatus.h"
#include "game_src/characters_src/characterData/players/IDFData.h"

struct IDFStatus : CharacterStatus {
    int ammo;
    int killed = 0;
    int distance = 0;
    IDFStatus(int posx, int posy) {
        IDFData data;
        health = data.health;
        ammo = data.maxAmmo;
        x = posx;
        y = posy;
    }
};

#endif //LEFT4DEAD_IDFSTATUS_H
