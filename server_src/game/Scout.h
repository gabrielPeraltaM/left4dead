//
// Created by gabriel on 22/06/23.
//

#ifndef LEFT4DEAD_SCOUT_H
#define LEFT4DEAD_SCOUT_H

#include "Survivor.h"

class Scout : public Survivor {
public:
    Scout(int pos_x, int pos_y, int &dead_players);

    //void receive_damage(int damage) override;
};

#endif //LEFT4DEAD_SCOUT_H
