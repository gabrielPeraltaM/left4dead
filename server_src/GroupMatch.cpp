//
// Created by gabriel on 19/05/23.
//

#include "GroupMatch.h"
#include <utility>
#include <memory>

#define LIMIT_X 100
#define LIMIT_Y 100
#define PLAYER_COLLISION_RANGE 10

GroupMatch::GroupMatch(std::string name) : name(std::move(name)),
                                           game(LIMIT_X, LIMIT_Y),
                                           players(0) {}

GroupMatch::~GroupMatch() {
    for (auto *state : player_states) {
        delete state;
    }
}

void GroupMatch::run() {
    while (true) { // change this
        std::shared_ptr<Action> action;
        if (actions.try_pop(action)) {
            std::shared_ptr<State> state = game.update(action);
            for (auto *player_state: player_states) {
                player_state->push(state);
            }
        }
        std::chrono::milliseconds tic(20);
        std::this_thread::sleep_for(tic);
    }
}

Match GroupMatch::add_player() {
    auto *state = new StateQueue;
    player_states.push_back(state);
    game.add_character(++players, PLAYER_COLLISION_RANGE);
    return {actions, state};
}
