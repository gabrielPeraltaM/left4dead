//
// Created by gabriel on 19/05/23.
//

#include "GroupMatch.h"
#include <utility>
#include <memory>

#define LIMIT_Y 400
#define PLAYER_COLLISION_RANGE 30

GroupMatch::GroupMatch(std::string name) : name(std::move(name)),
                                           game(LIMIT_Y),
                                           players(0),
                                           finished(false) {}

GroupMatch::~GroupMatch() {
    for (auto *state : player_states) {
        delete state;
    }
}

void GroupMatch::run() {
    while (not finished) { // change this
        handle_game();
        std::chrono::milliseconds tic(1000/60);
        std::this_thread::sleep_for(tic);
    }
}

Match GroupMatch::add_player() {
    auto *state = new StateQueue;
    player_states.push_back(state);
    game.add_character(++players, PLAYER_COLLISION_RANGE);
    return {actions, state, players};
}

void GroupMatch::handle_game() {
    int missing_players = 0;
    std::shared_ptr<Action> action;
    if (actions.try_pop(action)) {
        std::shared_ptr<State> state = game.update(action);
        for (auto *player_state: player_states) {
            // this check may be unnecessary
            if (player_state->was_closed()) {
                //++missing_players;
                continue;
            }
            player_state->push(state);
        }
    }
    // change this
    for (auto *player_state: player_states) {
        if (player_state->was_closed()) {
            ++missing_players;
        }
    }
    if (missing_players == players) {
        finished = true;
    }
}
