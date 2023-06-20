//
// Created by gabriel on 17/05/23.
//

#include "Acceptor.h"
#include "./Matches.h"
#include "./ClientHandler.h"

void Acceptor::run() {
    Matches matches;
    while (keep) {
        try {
            Socket peer = sk.accept();
            Thread *c = new ClientHandler(std::move(peer), std::ref(matches));
            clients.push_back(c);
            c->start();
            reap_dead();
        } catch (std::exception &) {//change this
            continue;
        }
    }
}

void Acceptor::close() {
    keep = false;
    sk.shutdown(2);
    sk.close();
}

void Acceptor::reap_dead() {
    clients.remove_if([](Thread* t) {
        auto *c = dynamic_cast<ClientHandler*>(t);
        if (c->is_dead()) {
            c->join();
            return true;
        }
        return false;
    });
}

Acceptor::~Acceptor() {
    for (auto *client : clients) {
        auto *c = dynamic_cast<ClientHandler*>(client);
        c->kill();
        client->join();
        delete client;
    }
}
