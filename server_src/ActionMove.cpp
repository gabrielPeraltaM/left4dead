//
// Created by gabriel on 01/06/23.
//

#include "ActionMove.h"

ActionMove::ActionMove(int player_id, int move_x, int move_y) : Action(player_id),
                                                                move_x(move_x),
                                                                move_y(move_y) {}

std::shared_ptr<State> ActionMove::execute(Map &map) {
    return map.move_character(player_id, move_x, move_y);
}
