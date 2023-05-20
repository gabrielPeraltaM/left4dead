//
// Created by gabriel on 17/05/23.
//

#include "server.h"
#include <string>

void Server::execute() {
    while (std::getc(stdin) != 'q') { }
}

Server::~Server() {
    acceptor.close();
    acceptor.join();
}
