//
// Created by gabriel on 18/05/23.
//

#include "Matches.h"

bool Matches::exist(int code) {
    if (code < 0) {
        return false;
    }
    std::lock_guard<std::mutex> lock(m);
    return (this->created > code);
}

int Matches::create(std::string name) {
    std::lock_guard<std::mutex> lock(m);
    groups.create_group(created, std::move(name));
    return created++;
}

Match Matches::join(int match_code) {
    GroupMatch *group = groups.get_group(match_code);
    return group->add_player();
}
