//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_COMMANDS_H
#define LEFT4DEAD_COMMANDS_H

#include "../common_src/socket.h"
#include "Match.h"
#include "Sender.h"
#include "Receiver.h"

class Commands {
    Match &match;
    Sender sender;
    Receiver receiver;

   public:
    Commands(Socket &sk, Match &match);

    ~Commands();

    void run();
};

#endif  // LEFT4DEAD_COMMANDS_H
