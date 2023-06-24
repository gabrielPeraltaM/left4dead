//
// Created by gabriel on 01/06/23.
//

#include "ActionMove.h"

ActionMove::ActionMove(int move_x, int move_y) : move_x(move_x),
                                                 move_y(move_y) {}

ActionMove ::ActionMove(int move_x, int move_y, bool isRunning) : move_x(move_x),
                                                                  move_y(move_y),
                                                                  isRunning(isRunning) {}

void ActionMove::execute(Map &map) {
    map.move_character(player_id, move_x, move_y, isRunning);
}
