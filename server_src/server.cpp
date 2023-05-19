//
// Created by gabriel on 17/05/23.
//

#include "server.h"
#include <string>

void Server::execute() {
    std::string q;
    do {
        std::cin >> q;
    } while (q != "q");
}

Server::~Server() {
    acceptor.close();
    acceptor.join();
}
