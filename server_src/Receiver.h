//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_RECEIVER_H
#define LEFT4DEAD_RECEIVER_H

#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "Match.h"

class Receiver : public Thread {
    Socket &sk;
    Match &match;

   public:
    Receiver(Socket &sk, Match &match);

    void run() override;
};

#endif  // LEFT4DEAD_RECEIVER_H
