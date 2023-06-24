//
// Created by gabriel on 30/05/23.
//

#include "Map.h"

#include <arpa/inet.h>

#include <iostream>
#include <random>

#include "Idf.h"

#define POS_X_FIRST 300
#define POS_Y_FIRST 900
#define POSX_GAP 100

#define ZOMBIE1_POS_X 800
#define ZOMBIE1_POS_Y 900
#define ZOMBIE2_POS_X 900
#define ZOMBIE2_POS_Y 900

#define CHARACTER_ATTRIBUTES_AMOUNT 7
#define ZOMBIES_AMOUNT 20
#define ZOMBIE_DEFAULT_COLLISION_RANGE 20

#define PLAYER_ZONE_LIMIT_LEFT 50
#define PLAYER_ZONE_LIMIT_RIGHT 400
#define ZONE_LIMIT_UP 920
#define ZOMBIES_ZONE_LIMIT_LEFT 1300
#define ZOMBIES_ZONE_LIMIT_RIGHT 2060
#define MAX_PLAYER_AMOUNT 10

Map::Map(int limit_y) : limit_y(limit_y), players(0), generic(0, 0, IDF) {
    initialize_zombies();
}

Map::~Map() {
    for (auto element: elements) {
        delete element.second;
    }
}

void Map::add_character(int id, int collision_range) {
    // change this
    int pos_x = 0;
    int pos_y = 0;
    calculate_position(pos_x, pos_y);
    auto *character = new Idf(pos_x, pos_y);  // change this
    characters[id] = character;
    elements[id] = character;
    ++players;
}

void Map::move_character(int id, int move_x, int move_y, bool isRunning) {
    auto *character = characters.at(id);
    if (character->is_dead()) {
        return;
    }
    if (limit_collision(character, move_x, move_y)) {
        return;
    }
    bool collision = false;
    for (auto other: characters) {
        if (other.first == id) {
            continue;
        }
        collision =
                character->collision(other.second, character->get_pos_x() + move_x,
                                     character->get_pos_y() + move_y);
    }
    if (not collision) {
        character->move(move_x, move_y);
    }
    for (auto zombie: zombies) {
        zombie.second->check_target(character);
    }
}

void Map::shoot(int player_id) {
    auto *character = characters.at(player_id);
    character->shoot(zombies);
}

void Map::reload(int player_id) {
    // auto *survivor = dynamic_cast<Survivor *>(characters.at(player_id));
    auto *character = characters.at(player_id);
    character->reload();
}

void Map::attack(int player_id) {
    auto *character = characters.at(player_id);
    character->attack(zombies);
}

std::shared_ptr<State> Map::update() {
    for (auto zombie: zombies) {
        // need to initialize the zombies in the elements
        zombie.second->interact();
    }
    std::vector<uint16_t> buf(elements.size() * CHARACTER_ATTRIBUTES_AMOUNT);
    int pos = 0;
    for (auto element: elements) {
        auto character_id = (uint16_t) element.first;
        auto *character = element.second;
        auto pos_x = (uint16_t) character->get_pos_x();
        auto pos_y = (uint16_t) character->get_pos_y();
        auto state = (uint16_t) character->get_state();
        auto life = (uint16_t) character->get_life();
        auto ammo = (uint16_t) character->get_ammo();
        auto type = (uint16_t)character->get_type();

        character_id = htons(character_id);
        pos_x = htons(pos_x);
        pos_y = htons(pos_y);
        state = htons(state);
        life = htons(life);
        ammo = htons(ammo);
        type = htons(type);
        buf[pos++] = character_id;
        buf[pos++] = pos_x;
        buf[pos++] = pos_y;
        buf[pos++] = state;
        buf[pos++] = life;
        buf[pos++] = ammo;
        buf[pos++] = type;
        character->reset_state();  // change this
    }
    return std::make_shared<State>(std::move(buf), (uint16_t) characters.size(), zombies.size());
}

bool Map::limit_collision(Character *character, int move_x, int move_y) const {
    if (character->get_pos_y() + move_y <= limit_y ||
        character->get_pos_y() + move_y >= ZONE_LIMIT_UP) {
        return true;
    }
    return false;
}

void Map::calculate_position(int &pos_x, int &pos_y) {
    pos_x = POS_X_FIRST + players * POSX_GAP;
    pos_y = POS_Y_FIRST;

    /*std::random_device rd;
    std::uniform_int_distribution<int> dist_x(PLAYER_ZONE_LIMIT_LEFT,
    PLAYER_ZONE_LIMIT_RIGHT); std::uniform_int_distribution<int> dist_y(limit_y,
    ZONE_LIMIT_UP); int tentative_pos_x; int tentative_pos_y; do { tentative_pos_x
    = dist_x(rd); tentative_pos_y = dist_y(rd); } while
    (collision(tentative_pos_x, tentative_pos_y)); pos_x = tentative_pos_x; pos_y
    = tentative_pos_y;*/
}

bool Map::collision(int pos_x, int pos_y) {
    bool collision = false;
    for (auto other: characters) {
        if (generic.collision(other.second, pos_x, pos_y)) {
            collision = true;
        }
    }
    return collision;
}

void Map::initialize_zombies() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist_x(ZOMBIES_ZONE_LIMIT_LEFT, ZOMBIES_ZONE_LIMIT_RIGHT);
    std::uniform_int_distribution<int> dist_y(limit_y, ZONE_LIMIT_UP);
    std::uniform_int_distribution<int> dist_type(INFECTED, VENOM);
    for (int i = MAX_PLAYER_AMOUNT; i < MAX_PLAYER_AMOUNT + ZOMBIES_AMOUNT; i++) {
        int pos_x = dist_x(rd);
        int pos_y = dist_y(rd);
        Type type = (Type)dist_type(rd);
        zombies[i] = new Zombie(pos_x, pos_y, ZOMBIE_DEFAULT_COLLISION_RANGE, type);
        elements[i] = zombies[i];
    }
}
