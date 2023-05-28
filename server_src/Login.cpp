//
// Created by gabriel on 23/05/23.
//

#include "Login.h"

int Login::get_login(Matches &matches) {
    if (login_type == CREATE) {
        int match_code = matches.create(std::move(match_name));
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
