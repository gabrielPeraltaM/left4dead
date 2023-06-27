//
// Created by gabriel on 13/06/23.
//

#ifndef LEFT4DEAD_SURVIVOR_H
#define LEFT4DEAD_SURVIVOR_H

#include "Character.h"

class Survivor : public Character {
    int orientation;
    int delay;
    int &dead_players;

public:
    Survivor(int pos_x, int pos_y, Type type, int hurt_range, int &dead_players, int ammo);

    void move(int move_x, int move_y) override;

    bool collision(Character *other, int pos_x, int pos_y) override;

    void shoot(std::map<int, Character*>& enemies) override;

    void reload() override;

    void attack(std::map<int, Character*>& enemies) override;

    void receive_damage(int damage) override;

    void reset_state() override;

    void interact() override;

    void check_target(Character *other) override;

    void witch_interact(int witch_pos_x, int witch_pos_y) override;

protected:
    Character *find_enemies_left(std::map<int, Character*> &enemies) const;

    Character *find_enemies_right(std::map<int, Character*> &enemies) const;
};

#endif //LEFT4DEAD_SURVIVOR_H
