//
// Created by gabriel on 30/05/23.
//

#include "Map.h"

Map::Map(int limit_x, int limit_y) : limit_x(limit_x),
                                     limit_y(limit_y) {}

Map::~Map() {
    for (auto character : characters) {
        delete character.second;
    }
}

void Map::add_character(int id, int collision_range) {
    // change this
    auto *character = new Character(0, 0, collision_range);
    characters.at(id) = character;
}

void Map::move_character(int id, int move_x, int move_y) {
    auto *character = characters.at(id);
    if (limit_collision(character, move_x, move_y)) {
      return;
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
    }
}

bool Map::limit_collision(Character *character, int move_x, int move_y) {
    if ((character->get_pos_x() + move_x) < 0 || (character->get_pos_x() + move_x) >= limit_x) {
        return true;
    }
    if ((character->get_pos_y() + move_y) < 0 || (character->get_pos_y() + move_y) >= limit_y) {
        return true;
    }
    return false;
}
