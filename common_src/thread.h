#ifndef THREAD_H_
#define THREAD_H_

#include <thread>
#include <iostream>

class Thread {
    private:
        std::thread thread;

    public:
        Thread() = default;

        void start();

        void join();

        void main();

        virtual void run() = 0;
        virtual ~Thread() = default;

        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        Thread(Thread&& other) = delete;
        Thread& operator=(Thread&& other) = delete;
};

#endif
