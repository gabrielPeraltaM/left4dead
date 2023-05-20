//
// Created by gabriel on 19/05/23.
//

#include "Players.h"

Player* Players::create_player() {
    auto *player = new Player;
    players.push_back(player);
    return player;
}

Players::~Players() {
    for (auto *player : players) {
        delete player;
    }
}
