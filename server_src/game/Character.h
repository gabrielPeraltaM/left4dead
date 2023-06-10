//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_CHARACTER_H
#define LEFT4DEAD_CHARACTER_H

#include <map>
#include <vector>

class Character {
    int pos_x;
    int pos_y;
    int collision_range;
    int orientation;
    std::vector<int> zombies_ids;

   public:
    Character(int pos_x, int pos_y, int collision_range);

    void move(int move_x, int move_y);

    bool collision(Character *other, int move_x, int move_y) const;

    void shoot(std::map<int, Character*>& enemies);

    int get_pos_x() const;

    int get_pos_y() const;

   private:
    static double distance(Character *other, int new_pos_x, int new_pos_y);

    void find_enemies_left(std::map<int, Character*> &enemies);

    void find_enemies_right(std::map<int, Character*> &enemies);
};

#endif  // LEFT4DEAD_CHARACTER_H
