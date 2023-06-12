//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_CHARACTER_H
#define LEFT4DEAD_CHARACTER_H

#include <map>
#include <vector>

class Character {
    int life;
    bool dead;
    int pos_x;
    int pos_y;
    int moving_x;
    int moving_y;
    Character *target;
    int collision_range;
    int orientation;

   public:
    Character(int pos_x, int pos_y, int collision_range);

    void move(int move_x, int move_y);

    bool collision(Character *other, int move_x, int move_y) const;

    void update_move(); // zombies

    void interact(); // zombies

    void shoot(std::map<int, Character*>& enemies);

    bool is_dead() const;

    void check_target(Character *other);

    int get_pos_x() const;

    int get_pos_y() const;

   private:
    static double distance(Character *other, int new_pos_x, int new_pos_y);

    double distance_from(Character *other) const;

    bool target_collision();

    Character *find_enemies_left(std::map<int, Character*> &enemies) const;

    Character *find_enemies_right(std::map<int, Character*> &enemies) const;
};

#endif  // LEFT4DEAD_CHARACTER_H
