//
// Created by gabriel on 18/05/23.
//

#include "Matches.h"

bool Matches::exist(int code) {
    if (code < 0) {
        return false;
    }
    std::lock_guard<std::mutex> lock(m);
    return (this->created > code);
}

Match Matches::create(std::string name) {
    std::lock_guard<std::mutex> lock(m);
    GroupMatch *group = groups.create_group(created, std::move(name));
    Player *player = players.create_player();
    group->add_player(player);
    Match match(group, player);
    ++created;
    return match;
}
