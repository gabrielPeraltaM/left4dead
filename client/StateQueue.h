//
// Created by gabriel on 27/06/23.
//

#ifndef LEFT4DEAD_STATEQUEUE_H
#define LEFT4DEAD_STATEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

class StateQueue {
    std::queue<std::vector<uint16_t>> q;
    std::mutex m;
    std::condition_variable not_empty;
    bool closed = false;

public:
    bool try_push(const std::vector<uint16_t>& state);

    bool try_pop(std::vector<uint16_t>& state);

    void push(const std::vector<uint16_t>& state);

    std::vector<uint16_t> pop();

    void close();

    bool was_closed() const;
};

#endif //LEFT4DEAD_STATEQUEUE_H
