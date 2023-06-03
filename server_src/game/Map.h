//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_MAP_H
#define LEFT4DEAD_MAP_H

#include <map>
#include "Character.h"
#include "../server_src/State.h"

class Map {
    const int limit_x;
    const int limit_y;
    std::map<int, Character*> characters;

   public:
    Map(int limit_x, int limit_y);

    ~Map();

    void add_character(int id, int collision_range);

    void move_character(int id, int move_x, int move_y);

   private:
    bool limit_collision(Character *character, int move_x, int move_y);
};

#endif  // LEFT4DEAD_MAP_H
