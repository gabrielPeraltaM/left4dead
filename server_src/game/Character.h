//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_CHARACTER_H
#define LEFT4DEAD_CHARACTER_H

class Character {
    int pos_x;
    int pos_y;
    int collision_range;

   public:
    Character(int pos_x, int pos_y, int collision_range);

    void move(int move_x, int move_y);

    bool collision(Character *other, int move_x, int move_y);

    int get_pos_x() const;

    int get_pos_y() const;

   private:
    double distance(Character *other, int new_pos_x, int new_pos_y);
};

#endif  // LEFT4DEAD_CHARACTER_H
