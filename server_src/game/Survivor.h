//
// Created by gabriel on 13/06/23.
//

#ifndef LEFT4DEAD_SURVIVOR_H
#define LEFT4DEAD_SURVIVOR_H

#include "Character.h"

class Survivor : public Character {
    int orientation;
    int ammo;

public:
    Survivor(int pos_x, int pos_y);

    void move(int move_x, int move_y) override;

    bool collision(Character *other, int move_x, int move_y) override;

    void shoot(std::map<int, Character*>& enemies) override;

    void reload() override;

    void receive_damage(int damage) override;

    void interact() override;

    void check_target(Character *other) override;

private:
    Character *find_enemies_left(std::map<int, Character*> &enemies) const;

    Character *find_enemies_right(std::map<int, Character*> &enemies) const;
};

#endif //LEFT4DEAD_SURVIVOR_H
