//
// Created by Hoover Brent on 8/9/22.
//

#ifndef MY_PART_PARSER_HPP
#define MY_PART_PARSER_HPP

#include "srv_inside/CommandLine.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <algorithm>

#define COMMANDS(X) \
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

//enum representation
#define X(e) e
enum CommandEnum { COMMANDS(X), UNDEFINED };
#undef X

//string representation
#define X(s) #s
static const std::string CommandNames[] = { COMMANDS(X) };
#undef X


class Parser {
    CommandLine             _commandLine;
    CommandEnum             _type;
    std::queue<CommandLine> _tasks;

public:
    Parser(std::string input_commandLine);
    ~Parser();

    CommandLine getOneCommandLine();
    std::queue<CommandLine> getAllCommandLine();
    void    popOneCommandLine();
};


#endif //MY_PART_PARSER_HPP
