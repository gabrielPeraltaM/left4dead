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
    Survivor generic;
    int dead_players;
    int dead_zombies;
    std::map<int, Character*> characters;
    std::map<int, Character*> zombies;
    std::map<int, Character*> elements;

   public:
    explicit Map(int limit_y);

    ~Map();

    void add_character(int player_id, int character_type);

    void move_character(int id, int move_x, int move_y, bool isRunning);

    void shoot(int player_id);

    void reload(int player_id);

    void attack(int player_id);

    std::shared_ptr<State> update();

    bool all_players_dead() const;

    bool all_zombies_dead() const;

   private:
    bool limit_collision(Character *character, int move_x, int move_y) const;

    void calculate_position(int &pos_x, int &pos_y);

    bool collision(int pos_x, int pos_y);

    void initialize_zombies();
};

#endif  // LEFT4DEAD_MAP_H
