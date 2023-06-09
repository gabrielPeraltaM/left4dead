//
// Created by gabriel on 30/05/23.
//

#include "Map.h"


#define POS_X_ONE 200
#define POS_Y_ONE 800
#define POS_X_TWO 600
#define POS_Y_TWO 800

Map::Map(int limit_y) : limit_y(limit_y),
                                     players(0) {}

Map::~Map() {
    for (auto character : characters) {
        delete character.second;
    }
}

void Map::add_character(int id, int collision_range) {
    // change this
    int pos_x = 0;
    int pos_y = 0;
    calculate_position(pos_x, pos_y);
    auto *character = new Character(pos_x, pos_y, collision_range);
    characters[id] = character;
    ++players;
}

std::shared_ptr<State> Map::move_character(int id, int move_x, int move_y) {
    auto *character = characters.at(id);
    if (limit_collision(character, move_x, move_y)) {
        return std::make_shared<State>(id, 0, 0);
    }
    bool collision = false;
    for (auto other : characters) {
        if (other.first == id) {
            continue;
        }
        collision = character->collision(other.second, move_x, move_y);
    }
    if (not collision) {
        character->move(move_x, move_y);
        return std::make_shared<State>(id, move_x, move_y);
    }
    return std::make_shared<State>(id, 0, 0);
}

bool Map::limit_collision(Character *character, int move_x, int move_y) const {
    if (character->get_pos_y() + move_y <= limit_y) {
        return true;
    }
    return false;
}

void Map::calculate_position(int &pos_x, int &pos_y) const {
    if (players == 0) {
        pos_x = POS_X_ONE;
        pos_y = POS_Y_ONE;
        return;
    }
    if (players == 1) {
        pos_x = POS_X_TWO;
        pos_y = POS_Y_TWO;
    }
}
