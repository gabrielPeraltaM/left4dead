//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_CHARACTER_H
#define LEFT4DEAD_CHARACTER_H

#include <map>
#include <vector>

#define IDLE 0
#define RELOAD 11
#define SHOOT 9
#define ATTACK 10
#define DEAD 17

class Character {
protected:
    int pos_x;
    int pos_y;
    int collision_range;
    int state;

public:
    Character(int pos_x, int pos_y, int collision_range);

    int get_pos_x() const;

    int get_pos_y() const;

    int get_collision_range() const;

    int get_shooting() const;

    void star_shooting();

    void stop_shooting();

    virtual void receive_damage(int damage) = 0;

    virtual void interact() = 0;

    virtual void check_target(Character *other) = 0;

    virtual bool collision(Character *other, int pos_x, int pos_y) = 0;

    virtual void move(int move_x, int move_y) = 0;

    int get_state() const;

    virtual void shoot(std::map<int, Character*> &enemies) = 0;

protected:
    static double distance(Character *other, int new_pos_x, int new_pos_y);
};

#endif  // LEFT4DEAD_CHARACTER_H
