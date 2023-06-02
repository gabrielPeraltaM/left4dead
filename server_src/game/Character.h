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

    void move(int x, int y);

    bool collision(Character *other, int move_x, int move_y);

    int get_pos_x();

    int get_pos_y();

   private:
    double distance(int move_x, int move_y);
};

#endif  // LEFT4DEAD_CHARACTER_H
