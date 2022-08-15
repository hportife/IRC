//
// Created by Hoover Brent on 8/9/22.
//

#ifndef MY_PART_PARSER_HPP
#define MY_PART_PARSER_HPP

/*
X(PASS),\
X(USER),\
X(NICK),\
X(PONG),\
X(PRIVMSG),\
X(NOTICE),\
X(JOIN),\
X(OPER),\
X(QUIT),\
X(KILL),\
X(KICK),\
X(PING),\
X(LIST),\
X(WHO),\
X(PART)
 */

#include "srv_inside/CommandLine.hpp"
//#include "vector"

class Parser {
    CommandLine commandLine;

public:
    Parser();
    ~Parser();

    std::string getCommand();
};


#endif //MY_PART_PARSER_HPP
