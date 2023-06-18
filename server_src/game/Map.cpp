//
// Created by gabriel on 30/05/23.
//

#include "Map.h"
#include "Survivor.h"
#include <arpa/inet.h>

#define POS_X_ONE 200
#define POS_Y_ONE 900
#define POS_X_TWO 350
#define POS_Y_TWO 900

#define ZOMBIE1_POS_X 800
#define ZOMBIE1_POS_Y 900
#define ZOMBIE2_POS_X 900
#define ZOMBIE2_POS_Y 900

#define CHARACTER_ATTRIBUTES_AMOUNT 5

Map::Map(int limit_y) : limit_y(limit_y),
                        players(0) {
    auto *zombie1 = new Zombie(ZOMBIE1_POS_X, ZOMBIE1_POS_Y);
    auto *zombie2 = new Zombie(ZOMBIE2_POS_X, ZOMBIE2_POS_Y);
    zombies[2] = zombie1;
    zombies[3] = zombie2;
    elements[2] = zombie1;
    elements[3] = zombie2;
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
    auto *character = new Survivor(pos_x, pos_y);
    characters[id] = character;
    elements[id] = character;
    ++players;
}

void Map::move_character(int id, int move_x, int move_y) {
    auto *character = characters.at(id);
    if (character->is_dead()) {
        return;
    }
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
    character->shoot(zombies);
}

std::shared_ptr<State> Map::update() {
    for (auto zombie : zombies) {
        // need to initialize the zombies in the elements
        zombie.second->interact();
    }
    std::vector<uint16_t> buf(elements.size() * CHARACTER_ATTRIBUTES_AMOUNT);
    int pos = 0;
    for (auto element : elements) {
        auto character_id = (uint16_t)element.first;
        auto *character = element.second;
        auto pos_x = (uint16_t)character->get_pos_x();
        auto pos_y = (uint16_t)character->get_pos_y();
        auto shooting = (uint16_t)character->get_shooting();
        auto dead = (uint16_t)character->is_dead();

        character_id = htons(character_id);
        pos_x = htons(pos_x);
        pos_y = htons(pos_y);
        shooting = htons(shooting);
        dead = htons(dead);
        buf[pos++] = character_id;
        buf[pos++] = pos_x;
        buf[pos++] = pos_y;
        buf[pos++] = shooting;
        buf[pos++] = dead;
        character->stop_shooting();
    }
    return std::make_shared<State>(std::move(buf), (uint16_t)elements.size());
}

bool Map::limit_collision(Character *character, int move_x, int move_y) const {
    if (character->get_pos_y() + move_y <= limit_y || character->get_pos_y() + move_y >= 920) {
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
