//
// Created by ignacio on 5/5/23.
//

#ifndef ACTIONS_PARSER_H
#define ACTIONS_PARSER_H

#include "Protocol.h"
#include <string>

class ActionsParser {
private:
    Protocol &protocol;
    bool was_closed = false;
public:
    explicit ActionsParser(Protocol &protocol);
    ~ActionsParser() = default;
    bool parseFirstAction(const std::string &message);
    bool parseNextAction(const std::string &message);
};


#endif //ACTIONS_PARSER_H
