//
// Created by gabriel on 30/05/23.
//

#include "Map.h"

#define POS_X_ONE 200
#define POS_Y_ONE 800
#define POS_X_TWO 600
#define POS_Y_TWO 800

#define ZOMBIE1_POS_X 400
#define ZOMBIE1_POS_Y 400
#define ZOMBIE2_POS_X 400
#define ZOMBIE2_POS_Y 400


Map::Map(int limit_y) : limit_y(limit_y),
                        players(0) {
    auto *zombie1 = new Zombie(ZOMBIE1_POS_X, ZOMBIE1_POS_Y);
    auto *zombie2 = new Zombie(ZOMBIE2_POS_X, ZOMBIE2_POS_Y);
    zombies[5] = zombie1;
    zombies[6] = zombie2;
    elements[5] = zombie1;
    elements[6] = zombie2;
}

Map::~Map() {
    for (auto element : elements) {
        delete element.second;
    }
}

void Map::add_character(int id, int collision_range) {
    // change this
    int pos_x = 0;
    int pos_y = 0;
    calculate_position(pos_x, pos_y);
    auto *character = new Character(pos_x, pos_y, collision_range);
    characters[id] = character;
    elements[id] = character;
    ++players;
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
    for (auto zombie : zombies) {
        zombie.second->check_target(character);
    }
}

void Map::shoot(int player_id) {
    auto *character = characters.at(player_id);
}

std::shared_ptr<State> Map::update() {
    for (auto zombie : zombies) {
        // need to initialize the zombies in the elements
        zombie.second->interact();
    }
    return std::make_shared<State>(elements);
}

bool Map::limit_collision(Character *character, int move_x, int move_y) const {
    if (character->get_pos_y() + move_y <= limit_y || character->get_pos_y() + move_y >= 805) {
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
