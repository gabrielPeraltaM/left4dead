//
// Created by gabriel on 18/05/23.
//

#ifndef MATCH_H
#define MATCH_H

#include "./GroupMatch.h"
#include "./Player.h"

class Match {
    const GroupMatch *group;
    const Player *player;

public:
    Match(GroupMatch *group, Player *player) : group(group),
                                               player(player) {
    }
};

#endif //MATCH_H
