//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_ACTION_QUEUE_H
#define LEFT4DEAD_ACTION_QUEUE_H

#include <queue>
#include "./Action.h"
#include <mutex>
#include <condition_variable>
#include <memory>

class ActionQueue {
    std::queue<std::shared_ptr<Action>> q;
    std::mutex m;
    std::condition_variable not_empty;
    bool closed = false;

public:
    bool try_push(const std::shared_ptr<Action>& action);

    bool try_pop(std::shared_ptr<Action>& action);

    void push(const std::shared_ptr<Action>& action);

    std::shared_ptr<Action> pop();

    void close();
};

#endif //LEFT4DEAD_ACTION_QUEUE_H
