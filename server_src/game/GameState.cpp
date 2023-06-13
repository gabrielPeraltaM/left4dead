//
// Created by gabriel on 30/05/23.
//

#include "GameState.h"

GameState::GameState(int limit_y) : map(limit_y) {}

void GameState::add_character(int id, int collision_range) {
    // change this
    map.add_character(id, collision_range);
}

void GameState::receive_action(const std::shared_ptr<Action> &action) {
    action->execute(map);
}

std::shared_ptr<State> GameState::update() {
    return map.update();
}
