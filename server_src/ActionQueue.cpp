//
// Created by gabriel on 19/05/23.
//

#include "ActionQueue.h"

bool ActionQueue::try_push(const std::shared_ptr<Action>& action) {
    std::unique_lock<std::mutex> lock(m);
    if (closed) {
        return false;
    }
    if (q.empty()) {
        not_empty.notify_all();
    }
    q.push(action);
    return true;
}

bool ActionQueue::try_pop(std::shared_ptr<Action>& action) {
    std::unique_lock<std::mutex> lock(m);
    if (q.empty() || closed) {
        return false;
    }
    action = q.front();
    q.pop();
    return true;
}

void ActionQueue::push(const std::shared_ptr<Action>& action) {
    if (closed) {
        return;
    }
    std::unique_lock<std::mutex> lock(m);
    if (q.empty()) {
        not_empty.notify_all();
    }
    q.push(action);
}

std::shared_ptr<Action> ActionQueue::pop() {
    std::unique_lock<std::mutex> lock(m);
    while (q.empty()) {
        if (closed) {
            return nullptr;
        }
        not_empty.wait(lock);
    }
    std::shared_ptr<Action> action = q.front();
    q.pop();
    return action;
}

void ActionQueue::close() {
    std::unique_lock<std::mutex> lck(m);
    if (closed) {
        return;
    }
    closed = true;
    not_empty.notify_all();
}
