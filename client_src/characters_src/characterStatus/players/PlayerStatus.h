//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_PLAYERSTATUS_H
#define LEFT4DEAD_PLAYERSTATUS_H

#include "client_src/characters_src/characterStatus/CharacterStatus.h"
#include "client_src/characters_src/characterData/players/IDFData.h"

struct PlayerStatus : CharacterStatus {
    int ammo;
    int killed = 0;
    int distance = 0;
    PlayerStatus(int posx, int posy) {
        IDFData data;
        health = data.health;
        ammo = data.maxAmmo;
        x = posx;
        y = posy;
    }
};

#endif  // LEFT4DEAD_PLAYERSTATUS_H
