//
// Created by gabriel on 12/06/23.
//

#ifndef LEFT4DEAD_ZOMBIE_H
#define LEFT4DEAD_ZOMBIE_H

#include "Character.h"

class Zombie : public Character {
protected:
    int moving_x;
    int moving_y;
    Character *target;
    int delay;
    int &dead_zombies;

public:
    Zombie(int pos_x, int pos_y, int collision_range, int hurt_range, Type type, int &dead_zombies);

    void update_move();

    void interact() override;

    void check_target(Character *survivor) override;

    bool collision(Character *other, int pos_x, int pos_y) override;

    void move(int move_x, int move_y) override;

    void receive_damage(int damage) override;

    void reset_state() override;

    void shoot(std::map<int, Character*> &enemies) override;

    void reload() override;

    void attack(std::map<int, Character*>& enemies) override;

    void witch_interact(int witch_pos_x, int witch_pos_y) override;

    void stop_moving() override;

protected:
    double distance_from(Character *other) const;

    bool target_collision();
};

#endif //LEFT4DEAD_ZOMBIE_H
