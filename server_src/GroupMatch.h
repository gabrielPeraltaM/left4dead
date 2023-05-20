//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_GROUP_MATCH_H
#define LEFT4DEAD_GROUP_MATCH_H

#include <string>
#include <utility>
#include <vector>
#include "./Player.h"

class GroupMatch {
    const std::string name;
    std::vector<Player*> players;

public:
    explicit GroupMatch(std::string name) : name(std::move(name)) {}

    void add_player(Player *player);
};

#endif //LEFT4DEAD_GROUP_MATCH_H
