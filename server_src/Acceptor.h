//
// Created by gabriel on 17/05/23.
//

#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include <atomic>
#include <list>

class Acceptor : public Thread {
    Socket sk;
    std::atomic<bool> keep;
    std::list<Thread*> clients;

public:
    explicit Acceptor(Socket sk) : sk(std::move(sk)),
                                   keep(true) {
    }

    void run() override;

    void close();

    ~Acceptor() override;

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

private:
    void reap_dead();
};

#endif //ACCEPTOR_H
