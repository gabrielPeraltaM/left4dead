//
// Created by gabriel on 19/05/23.
//

#include "StateQueue.h"

bool StateQueue::try_push(State *state) {
    std::unique_lock<std::mutex> lock(m);
    if (closed) {
        return false;
    }
    if (q.empty()) {
        not_empty.notify_all();
    }
    q.push(state);
    return true;
}

bool StateQueue::try_pop(State *state) {
    std::unique_lock<std::mutex> lock(m);
    if (q.empty() || closed) {
        return false;
    }
    *state = *q.front();
    q.pop();
    return true;
}

void StateQueue::push(State *state) {
    if (closed) {
        return;
    }
    std::unique_lock<std::mutex> lock(m);
    if (q.empty()) {
        not_empty.notify_all();
    }
    q.push(state);
}

State *StateQueue::pop() {
    std::unique_lock<std::mutex> lock(m);
    while (q.empty()) {
        if (closed) {
            return nullptr;
        }
        not_empty.wait(lock);
    }
    State *state = q.front();
    q.pop();
    return state;
}

void StateQueue::close() {
    std::unique_lock<std::mutex> lck(m);
    if (closed) {
        return;
    }
    closed = true;
    not_empty.notify_all();
}
