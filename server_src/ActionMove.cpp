//
// Created by gabriel on 01/06/23.
//

#include "ActionMove.h"

ActionMove::ActionMove(int move_x, int move_y) : move_x(move_x),
                                                 move_y(move_y) {}

void ActionMove::execute(Map &map) {
    map.move_character(player_id, move_x, move_y);
}
