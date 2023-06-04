//
// Created by gabriel on 19/05/23.
//

#include "GroupMatch.h"
#include <utility>

GroupMatch::GroupMatch(std::string name) : name(std::move(name)) {}

GroupMatch::~GroupMatch() {
    for (auto *state : states) {
        delete state;
    }
}

Match GroupMatch::add_player() {
    auto *state = new StateQueue;
    states.push_back(state);
    return {actions, state};
}
