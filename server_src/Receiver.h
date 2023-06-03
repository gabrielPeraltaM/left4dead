//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_RECEIVER_H
#define LEFT4DEAD_RECEIVER_H

#include "../common_src/thread.h"
#include "ServerProtocol.h"
#include "Match.h"

class Receiver : public Thread {
    ServerProtocol &protocol;
    Match &match;

   public:
    Receiver(ServerProtocol &protocol, Match &match);

    void run() override;
};

#endif  // LEFT4DEAD_RECEIVER_H
