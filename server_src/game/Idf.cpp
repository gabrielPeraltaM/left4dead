//
// Created by gabriel on 22/06/23.
//

#include "Idf.h"

#define IDF_HURT_RANGE 26
#define IDF_AMMO 50

Idf::Idf(int pos_x, int pos_y, int &dead_players) : Survivor(pos_x, pos_y,
                                                             IDF,
                                                             IDF_HURT_RANGE,
                                                             dead_players,
                                                             IDF_AMMO) {}
