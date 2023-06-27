//
// Created by gabriel on 23/05/23.
//

#include "Login.h"
#include <utility>

#define MAX_PLAYERS 5  // Hardcoded for now

Login::Login(std::string match_name, int match_code, int character_type) : match_name(std::move(match_name)),
                                                       join_code(match_code),
                                                       login_type(CREATE),
                                                       joined(false),
                                                       character_type(character_type) {}

int Login::get_login(Matches &matches) {
    if (login_type == CREATE) {
        int match_code = matches.create(std::move(match_name), MAX_PLAYERS);
        return match_code;
    } else if (login_type == JOIN) {
        if (matches.exist(join_code)) {
            joined = true;
            return join_code;
        }
    }
    return JOIN_FAIL;
}

void Login::set_create() {
    login_type = CREATE;
}

void Login::set_join() {
    login_type = JOIN;
}

bool Login::is_joined() const {
    return joined;
}

int Login::get_character_type() const { return character_type; }
