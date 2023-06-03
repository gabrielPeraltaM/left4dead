//
// Created by gabriel on 01/06/23.
//

#ifndef LEFT4DEAD_STATE_MOVE_H
#define LEFT4DEAD_STATE_MOVE_H

#include "State.h"

class StateMove : public State {
    int move_x;
    int move_y;

   public:
    StateMove(int player_id, int move_x, int move_y);

    void send_state(ServerProtocol &protocol) override;
};

#endif  // LEFT4DEAD_STATE_MOVE_H
