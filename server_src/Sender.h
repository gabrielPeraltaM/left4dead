//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_SENDER_H
#define LEFT4DEAD_SENDER_H

#include "../common_src/thread.h"
#include "ServerProtocol.h"
#include "Player.h"

class Sender : public Thread {
    ServerProtocol &protocol;
    Player &match;

   public:
    Sender(ServerProtocol &protocol, Player &match);

    void run() override;
};

#endif  // LEFT4DEAD_SENDER_H
