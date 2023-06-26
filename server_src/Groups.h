//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_GROUPS_H
#define LEFT4DEAD_GROUPS_H

#include <map>
#include <string>
#include "./GroupMatch.h"

class Groups {
    std::map<int, GroupMatch*> groups;

public:
    GroupMatch *create_group(int match_code, std::string name, int max_players);

    ~Groups();

    GroupMatch *get_group(int code);
};

#endif //LEFT4DEAD_GROUPS_H
