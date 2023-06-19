//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_CHARACTER_H
#define LEFT4DEAD_CHARACTER_H

#include <map>
#include <vector>

class Character {
protected:
    int life;
    int pos_x;
    int pos_y;
    int collision_range;
    bool dead;
    int shooting;

public:
    Character(int life, int pos_x, int pos_y, int collision_range);

    int get_life() const;

    int get_pos_x() const;

    int get_pos_y() const;

    int get_collision_range() const;

    int get_shooting() const;

    void start_shooting();

    void stop_shooting();

    virtual void receive_damage(int damage) = 0;

    virtual void interact() = 0;

    virtual void check_target(Character *other) = 0;

    virtual bool collision(Character *other, int pos_x, int pos_y) = 0;

    virtual void move(int move_x, int move_y) = 0;

    bool is_dead() const;

    virtual void shoot(std::map<int, Character*> &enemies) = 0;

protected:
    static double distance(Character *other, int new_pos_x, int new_pos_y);
};

#endif  // LEFT4DEAD_CHARACTER_H
