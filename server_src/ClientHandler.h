//
// Created by gabriel on 18/05/23.
//

#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "./Matches.h"
#include <atomic>

class ClientHandler : public Thread {
    Socket sk;
    Matches &matches;
    std::atomic<bool> is_alive;
    std::atomic<bool> keep_talking;

public:
    ClientHandler(Socket sk, Matches &matches) : sk(std::move(sk)),
                                                 matches(matches),
                                                 is_alive(true),
                                                 keep_talking(true) {
    }

    void run() override;

    bool is_dead();

    void kill();

    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;
};

#endif //CLIENT_HANDLER_H
