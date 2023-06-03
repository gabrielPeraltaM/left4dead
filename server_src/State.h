//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_STATE_H
#define LEFT4DEAD_STATE_H

#include "ServerProtocol.h"

class State{
   protected:
    int player_id;

    explicit State(int player_id) : player_id(player_id) {}

   public:
    virtual void send_state(ServerProtocol &protocol) = 0;
};

#endif //LEFT4DEAD_STATE_H
