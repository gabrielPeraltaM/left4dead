//
// Created by gabriel on 18/05/23.
//

#ifndef MATCH_H
#define MATCH_H

#include "./GroupMatch.h"
#include "./Player.h"
#include <atomic>

class Match {
    const GroupMatch *group;
    const Player *player;
    std::atomic<bool> finished;

public:
    Match(GroupMatch *group, Player *player) : group(group),
                                               player(player),
                                               finished(false) {
    }

    Match(Match&& other) noexcept;

    void finish();

    bool is_finished();

    Match(const Match&) = delete;
    Match& operator=(const Match&) = delete;
};

#endif //MATCH_H
