//
// Created by gabriel on 19/05/23.
//

#include "Groups.h"

#include <utility>

GroupMatch *Groups::create_group(int match_code, std::string name) {
    auto *group = new GroupMatch(std::move(name));
    groups.at(match_code) = group;
    return group;
}

Groups::~Groups() {
    for (auto group : groups) {
        delete group.second;
    }
}
