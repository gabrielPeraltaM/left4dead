//
// Created by gabriel on 30/05/23.
//

#include "GameState.h"

GameState::GameState(int limit_y) : map(limit_y) {}

void GameState::add_character(int player_id, int character_type) {
    map.add_character(player_id, character_type);
}

void GameState::receive_action(const std::shared_ptr<Action> &action) {
    action->execute(map);
}

std::shared_ptr<State> GameState::update() {
    std::shared_ptr<State> state = map.update();
    if (map.all_players_dead()) {
        state->set_loose();
        return state;
    }
    if (map.all_zombies_dead()) {
        state->set_win();
        return state;
    }
    //state->set_continue();
    return state;
}
