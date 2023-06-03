//
// Created by gabriel on 01/06/23.
//

#include "StateMove.h"
StateMove::StateMove(int player_id, int move_x, int move_y) : State(player_id),
                                                              move_x(move_x),
                                                              move_y(move_y) {}

void StateMove::send_state(ServerProtocol& protocol) {
}
