//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_GROUP_MATCH_H
#define LEFT4DEAD_GROUP_MATCH_H

#include <string>
#include <vector>
#include "Match.h"

class GroupMatch {
    const std::string name;
    ActionQueue actions;
    std::vector<StateQueue*> states;

public:
    explicit GroupMatch(std::string name);

    ~GroupMatch();

    Match add_player();
};

#endif //LEFT4DEAD_GROUP_MATCH_H
