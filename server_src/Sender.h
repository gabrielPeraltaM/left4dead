//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_SENDER_H
#define LEFT4DEAD_SENDER_H

#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "Match.h"

class Sender : public Thread {
    Socket &sk;
    Match &match;

   public:
    Sender(Socket &sk, Match &match);

    void run() override;
};

#endif  // LEFT4DEAD_SENDER_H
