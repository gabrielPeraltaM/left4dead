//
// Created by gabriel on 19/05/23.
//

#include "GroupMatch.h"
#include <utility>
#include <memory>

#define LIMIT_Y 750
#define PLAYER_COLLISION_RANGE 22

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
    std::chrono::milliseconds tic(1000/60);
    while (not finished) { // change this
        handle_game();
        std::this_thread::sleep_for(tic);
    }
}

Player GroupMatch::add_player() {
    std::lock_guard<std::mutex> lock(m);
    auto *state = new StateQueue;
    player_states.push_back(state);
    game.add_character(players, PLAYER_COLLISION_RANGE);
    bool host = false;
    if (players == 0) {
        host = true;
    }
    return {actions, state, players++, host};
}

void GroupMatch::handle_game() {
    std::lock_guard<std::mutex> lock(m);
    int missing_players = 0;
    std::shared_ptr<Action> action;
    if (actions.try_pop(action)) {
        game.receive_action(action);
    }
    std::shared_ptr<State> state = game.update();
    for (auto *player_state: player_states) {
        if (player_state->was_closed()) {
            ++missing_players;
            continue;
        }
        player_state->push(state);
    }
    if (missing_players == players) {
        finished = true;
    }
}
