//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_MAP_H
#define LEFT4DEAD_MAP_H

#include <map>
#include <memory>
#include "Character.h"
#include "Survivor.h"
#include "Zombie.h"
#include "../server_src/State.h"

class Map {
    const int limit_y;
    int players;
    std::map<int, Character*> characters;
    std::map<int, Character*> zombies;
    std::map<int, Character*> elements;
    Survivor generic;

   public:
    explicit Map(int limit_y);

    ~Map();

    void add_character(int id, int collision_range);

    void move_character(int id, int move_x, int move_y);

    void shoot(int player_id);

    void reload(int player_id);

    void attack(int player_id);

    std::shared_ptr<State> update();

   private:
    bool limit_collision(Character *character, int move_x, int move_y) const;

    void calculate_position(int &pos_x, int &pos_y);

    bool collision(int pos_x, int pos_y);
};

#endif  // LEFT4DEAD_MAP_H
