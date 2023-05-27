//
// Created by gabriel on 18/05/23.
//

#ifndef MATCHES_H
#define MATCHES_H

#include "./Match.h"
#include "./Players.h"
#include "./Groups.h"
#include <mutex>

class Matches {
    int created = 0;
    Groups groups;
    Players players;
    std::mutex m;

public:
    bool exist(int code);

    int create(std::string name);

    Match join(int match_code);
};

#endif //MATCHES_H
