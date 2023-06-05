//
// Created by gabriel on 30/05/23.
//

#include "GameState.h"

GameState::GameState(int limit_x, int limit_y) : map(limit_x, limit_y) {}

void GameState::add_character(int id, int collision_range) {
    // change this
    map.add_character(id, collision_range);
}

std::shared_ptr<State> GameState::update(const std::shared_ptr<Action>& action) {
    return action->execute(map);
}
