//
// Created by gabriel on 18/05/23.
//

#ifndef MATCHES_H
#define MATCHES_H

#include "./Player.h"
#include "./Groups.h"
#include <mutex>

class Matches {
    int created = 0;
    Groups groups;
    std::mutex m;

public:
    bool exist(int code);

    int create(std::string name, int max_players);

    Player join(int match_code);
};

#endif //MATCHES_H
