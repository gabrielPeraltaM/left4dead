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
    bool dead;
    int pos_x;
    int pos_y;
    int collision_range;
    int orientation;

public:
    Character(int pos_x, int pos_y, int collision_range);

    void move(int move_x, int move_y);

    bool collision(Character *other, int move_x, int move_y) const;

    void shoot(std::map<int, Character*>& enemies);

    void receive_damage(int damage);

    bool is_dead() const;

    int get_pos_x() const;

    int get_pos_y() const;

    int get_collision_range() const;

private:
    static double distance(Character *other, int new_pos_x, int new_pos_y);

    Character *find_enemies_left(std::map<int, Character*> &enemies) const;

    Character *find_enemies_right(std::map<int, Character*> &enemies) const;
};

#endif  // LEFT4DEAD_CHARACTER_H
