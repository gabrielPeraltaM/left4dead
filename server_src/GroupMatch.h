//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_GROUP_MATCH_H
#define LEFT4DEAD_GROUP_MATCH_H

#include <string>
#include <vector>
#include <mutex>
#include "Player.h"
#include "../common_src/thread.h"
#include "./game/GameState.h"

class GroupMatch : public Thread {
    const std::string name;
    GameState game;
    int players;
    bool finished;
    ActionQueue actions;
    std::vector<StateQueue*> player_states;
    std::mutex m;

public:
    explicit GroupMatch(std::string name);

    ~GroupMatch() override;

    void run() override;

    Player add_player();

private:
    void handle_game();
};

#endif //LEFT4DEAD_GROUP_MATCH_H
