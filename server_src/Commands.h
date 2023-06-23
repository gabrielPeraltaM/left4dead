//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_COMMANDS_H
#define LEFT4DEAD_COMMANDS_H

#include "Player.h"
#include "Sender.h"
#include "Receiver.h"
#include "ServerProtocol.h"

class Commands {
    Player &match;
    Sender sender;
    Receiver receiver;

   public:
    Commands(ServerProtocol &protocol, Player &match);

    ~Commands();

    void run();
};

#endif  // LEFT4DEAD_COMMANDS_H
