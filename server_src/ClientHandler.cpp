//
// Created by gabriel on 18/05/23.
//

#include "ClientHandler.h"

void ClientHandler::run() {
    while (keep_talking) {
        std::cout << "Implement" << std::endl;
    }
    is_alive = false;
}

bool ClientHandler::is_dead() {
    return not is_alive;
}

void ClientHandler::kill() {
    keep_talking = false;
    sk.shutdown(2);
    sk.close();
}
