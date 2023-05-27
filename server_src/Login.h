//
// Created by gabriel on 23/05/23.
//

#ifndef LOGIN_H
#define LOGIN_H

#include "./Match.h"
#include "./Matches.h"
#include <string>
#include <utility>

#define CREATE 0
#define JOIN 1
#define JOIN_FAIL (-1)

class Login {
    std::string match_name;
    const int join_code;
    int login_type;
    bool joined;

public:
    Login(std::string match_name, const int match_code) : match_name(std::move(match_name)),
                                                          join_code(match_code),
                                                          login_type(CREATE),
                                                          joined(false) {
    }

    int get_login(Matches &matches);

    void set_create();

    void set_join();

    bool is_joined() const;
};

#endif //LOGIN_H
