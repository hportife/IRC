//
// Created by Hoover Brent on 8/9/22.
//

#ifndef MY_PART_PARSER_HPP
#define MY_PART_PARSER_HPP

#include "CommandLine.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <algorithm>
#include "Serv.hpp"

#define ERR_UNKNOWNCOMMAND 421      // "<command> :Unknown command"
#define ERR_NEEDMOREPARAMS 461      // "<command> :Not enough parameters"


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
X(PART),\
X(AWAY),\
X(WHOIS),\
X(WHOWAS),\
X(MODE),\
X(TOPIC),\
X(INVITE),\
X(NAMES),\
X(WALLOPS),\
X(ISON),\
X(USERHOST),\
X(VERSION),\
X(INFO),\
X(ADMIN),\
X(TIME),\
X(REHASH),\
X(RESTART)

//enum representation
#define X(e) e
enum CommandEnum { COMMANDS(X), UNDEFINED };
#undef X

//string representation
#define X(s) #s
static const std::string CommandNames[] = { COMMANDS(X) };
#undef X

class Serv;

class Parser {
private:
    CommandLine             _commandLine;
    CommandEnum             _type;
    std::queue<CommandLine> _tasks;
    int                     _countCommand;
    Serv                    *serv;
    int                     id_user;

    void    detect_msg(std::string *input_commandLine, std::string *msg, int *pos);

    void    detect_args_and_cmds(std::string *input_commandLine, int *pos, std::vector<std::string> *channels,
                                 std::vector<std::string> *keys_users_modes, std::vector<std::string> *command, char const **cmd);

    void    define_command(std::vector<std::string> *command);

    void    build_commandLine_with_args(const std::vector<std::string>& command, const std::vector<std::string>& channels,
                                        const std::vector<std::string>& keys_users_modes, const std::string& msg);

    void    build_commandLine_no_args(std::vector<std::string> command, const std::vector<std::string>& channels,
                                      const std::vector<std::string>& keys_users_modes, const std::string& msg);


public:
    Parser(std::string input_commandLine, int id_user, Serv *serv);
    ~Parser();

    CommandLine getOneCommandLine();
    std::queue<CommandLine> getAllCommandLine();
    void    popOneCommandLine();
    void    commandHandler();

};


#endif //MY_PART_PARSER_HPP
