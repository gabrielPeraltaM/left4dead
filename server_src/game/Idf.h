//
// Created by gabriel on 22/06/23.
//

#ifndef LEFT4DEAD_IDF_H
#define LEFT4DEAD_IDF_H

#include "Survivor.h"

class Idf : public Survivor {
public:
    Idf(int pos_x, int pos_y, int &dead_players);
};

#endif //LEFT4DEAD_IDF_H
