//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_STATE_QUEUE_H
#define LEFT4DEAD_STATE_QUEUE_H

#include <queue>
#include "./State.h"
#include <mutex>
#include <condition_variable>

class StateQueue {
    std::queue<State*> q;
    std::mutex m;
    std::condition_variable not_empty;
    bool closed = false;

public:
    bool try_push(State *state);

    bool try_pop(State *state);

    void push(State *state);

    State* pop();

    void close();
};

#endif //LEFT4DEAD_STATE_QUEUE_H
