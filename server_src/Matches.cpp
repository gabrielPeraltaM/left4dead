//
// Created by gabriel on 18/05/23.
//

#include "Matches.h"
#include <string>
#include <utility>

bool Matches::exist(int code) {
    if (code < 0) {
        return false;
    }
    std::lock_guard<std::mutex> lock(m);
    if (created > code) {
        GroupMatch *group = groups.get_group(code);
        if (!group->is_available()) {
            return false;
        }
        return true;
    }
    return false;
}

int Matches::create(std::string name, int max_players) {
    std::lock_guard<std::mutex> lock(m);
    groups.create_group(created, std::move(name), max_players);
    return created++;
}

Player Matches::join(int match_code) {
    std::lock_guard<std::mutex> lock(m);
    GroupMatch *group = groups.get_group(match_code);
    return group->add_player();
}
