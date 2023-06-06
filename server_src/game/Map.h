//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_MAP_H
#define LEFT4DEAD_MAP_H

#include <map>
#include "Character.h"
#include "../server_src/State.h"
#include <memory>

class Map {
    const int limit_x;
    const int limit_y;
    int players;
    std::map<int, Character*> characters;

   public:
    Map(int limit_x, int limit_y);

    ~Map();

    void add_character(int id, int collision_range);

    std::shared_ptr<State> move_character(int id, int move_x, int move_y);

   private:
    bool limit_collision(Character *character, int move_x, int move_y) const;

    void calculate_position(int &pos_x, int &pos_y) const;
};

#endif  // LEFT4DEAD_MAP_H
