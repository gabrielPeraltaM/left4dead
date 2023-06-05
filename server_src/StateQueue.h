//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_STATE_QUEUE_H
#define LEFT4DEAD_STATE_QUEUE_H

#include <queue>
#include "./State.h"
#include <mutex>
#include <condition_variable>
#include <memory>

class StateQueue {
    std::queue<std::shared_ptr<State>> q;
    std::mutex m;
    std::condition_variable not_empty;
    bool closed = false;

public:
    bool try_push(const std::shared_ptr<State>& state);

    bool try_pop(std::shared_ptr<State>& state);

    void push(const std::shared_ptr<State>& state);

    std::shared_ptr<State> pop();

    void close();
};

#endif //LEFT4DEAD_STATE_QUEUE_H
