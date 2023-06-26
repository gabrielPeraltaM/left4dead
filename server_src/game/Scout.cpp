//
// Created by gabriel on 22/06/23.
//

#include "Scout.h"

#define SCOUT_HURT_RANGE 26

Scout::Scout(int pos_x, int pos_y, int &dead_players) : Survivor(pos_x, pos_y,
                                                                 SCOUT,
                                                                 SCOUT_HURT_RANGE,
                                                                 dead_players) {}
