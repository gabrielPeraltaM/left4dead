//
// Created by gabriel on 17/05/23.
//

#ifndef SERVER_H
#define SERVER_H

#include "../common_src/socket.h"
#include "./Acceptor.h"

class Server {
    Socket sk;
    Acceptor acceptor;

public:
    explicit Server(const char *serv_name) : sk(serv_name),
                                             acceptor(std::move(sk)) {
        acceptor.start();
    }

    static void execute();

    ~Server();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
};

#endif //SERVER_H
