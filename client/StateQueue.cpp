//
// Created by gabriel on 27/06/23.
//

#include "StateQueue.h"

bool StateQueue::try_push(const std::vector<uint16_t>& state) {
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

bool StateQueue::try_pop(std::vector<uint16_t>& state) {
    std::unique_lock<std::mutex> lock(m);
    if (q.empty() || closed) {
        return false;
    }
    state = q.front();
    q.pop();
    return true;
}

void StateQueue::push(const std::vector<uint16_t>& state) {
    if (closed) {
        return;
    }
    std::unique_lock<std::mutex> lock(m);
    if (q.empty()) {
        not_empty.notify_all();
    }
    q.push(state);
}

std::vector<uint16_t> StateQueue::pop() {
    std::unique_lock<std::mutex> lock(m);
    while (q.empty()) {
        if (closed) {
            std::vector<uint16_t> state;
            return state;
        }
        not_empty.wait(lock);
    }
    std::vector<uint16_t> state = q.front();
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

bool StateQueue::was_closed() const { return closed; }
