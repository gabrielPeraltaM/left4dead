//
// Created by gabriel on 12/06/23.
//

#ifndef LEFT4DEAD_ZOMBIE_H
#define LEFT4DEAD_ZOMBIE_H

#include "Character.h"

class Zombie : public Character {
    int move_x;
    int move_y;
    Character *target;
    int life;

public:
    Zombie(int pos_x, int pos_y);

    void update_move();

    void interact() override;

    void check_target(Character *other) override;

    bool collision(Character *other, int pos_x, int pos_y) override;

    void move(int move_x, int move_y) override;

    void receive_damage(int damage) override;

    void shoot(std::map<int, Character*> &enemies) override;

private:
    double distance_from(Character *other) const;

    bool target_collision();
};

#endif //LEFT4DEAD_ZOMBIE_H
