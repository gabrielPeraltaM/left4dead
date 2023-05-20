//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_ACTION_QUEUE_H
#define LEFT4DEAD_ACTION_QUEUE_H

#include <queue>
#include "./Action.h"
#include <mutex>
#include <condition_variable>

class ActionQueue {
    std::queue<Action*> q;
    std::mutex m;
    std::condition_variable not_empty;
    bool closed = false;

public:
    bool try_push(Action *action);

    bool try_pop(Action *action);

    void push(Action *action);

    Action* pop();

    void close();
};

#endif //LEFT4DEAD_ACTION_QUEUE_H
