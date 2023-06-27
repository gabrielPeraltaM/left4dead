//
// Created by gabriel on 27/06/23.
//

#include "P90.h"

#define P90_HURT_RANGE 26
#define P90_AMMO 30

P90::P90(int pos_x, int pos_y, int &dead_players) : Survivor(pos_x, pos_y, P_90,
                                                             P90_HURT_RANGE,
                                                             dead_players, P90_AMMO){}
