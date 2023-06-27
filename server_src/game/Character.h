//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_CHARACTER_H
#define LEFT4DEAD_CHARACTER_H

#include <map>
#include <vector>

enum Type : int {
    IDF = 1,
    SCOUT,
    P_90,
    INFECTED,
    JUMPER,
    SPEAR,
    VENOM,
    WITCH
};

enum States : int {
    NOT = 4,
    SHOOTING,
    ATTACKING,
    RELOADING,
    DAMAGING,
    DEAD,
    RUNNING
};

class Character {
protected:
    int life;
    int pos_x;
    int pos_y;
    int collision_range;
    int hurt_range;
    States state;
    int ammo;
    Type type;

public:
    Character(int life, int pos_x, int pos_y, int collision_range, int hurt_range, int ammo, Type type);

    int get_life() const;

    int get_pos_x() const;

    int get_pos_y() const;

    int get_collision_range() const;

    int get_hurt_range() const;

    int get_state() const;

    int get_ammo() const;

    int get_type() const;

    void start_shooting();

    virtual void reset_state() = 0;

    virtual void receive_damage(int damage) = 0;

    virtual void interact() = 0;

    virtual void check_target(Character *other) = 0;

    virtual bool collision(Character *other, int pos_x, int pos_y) = 0;

    virtual void move(int move_x, int move_y) = 0;

    virtual void shoot(std::map<int, Character*> &enemies) = 0;

    virtual void reload() = 0;

    virtual void attack(std::map<int, Character*>& enemies) = 0;

    bool is_dead() const;

    virtual void witch_interact(int witch_pos_x, int witch_pos_y) = 0;

    virtual void stop_moving();

protected:
    static double distance(Character *other, int new_pos_x, int new_pos_y);
};

#endif  // LEFT4DEAD_CHARACTER_H
