//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_STATE_H
#define LEFT4DEAD_STATE_H

class State{
public:
    int player_id;
    int move_x;
    int move_y;

    State(int player_id, int move_x, int move_y) : player_id(player_id),
                                                   move_x(move_x),
                                                   move_y(move_y) {}
};

#endif //LEFT4DEAD_STATE_H
