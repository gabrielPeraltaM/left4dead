//
// Created by gabriel on 23/05/23.
//

#ifndef LOGIN_H
#define LOGIN_H

#include "./Player.h"
#include "./Matches.h"
#include <string>

#define CREATE 0
#define JOIN 1
#define JOIN_FAIL (-1)

class Login {
    std::string match_name;
    const int join_code;
    int login_type;
    bool joined;
    int character_type;

public:
    Login(std::string match_name, int match_code, int character_type);

    int get_login(Matches &matches);

    void set_create();

    void set_join();

    bool is_joined() const;

    int get_character_type() const;
};

#endif //LOGIN_H
