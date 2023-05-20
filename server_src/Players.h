//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_PLAYERS_H
#define LEFT4DEAD_PLAYERS_H

#include <vector>
#include "./Player.h"

class Players {
    std::vector<Player*> players;

public:
    Player* create_player();

    ~Players();
};

#endif //LEFT4DEAD_PLAYERS_H
