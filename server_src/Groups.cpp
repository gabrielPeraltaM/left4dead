//
// Created by gabriel on 19/05/23.
//

#include "Groups.h"
#include <utility>

GroupMatch *Groups::create_group(int match_code, std::string name, int max_players) {
    auto *group = new GroupMatch(std::move(name), max_players);
    groups[match_code] = group;
    group->start();
    return group;
}

Groups::~Groups() {
    for (auto group : groups) {
        group.second->join();
        delete group.second;
    }
}

GroupMatch *Groups::get_group(int code) {
    return groups.at(code);
}
