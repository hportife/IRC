//
// Created by Hoover Brent on 8/9/22.
//

#include "Parser.hpp"

Parser::Parser() {
    this->commandLine = new CommandLine("dfgdfgh", 4);
}

Parser::~Parser() {

}

std::string Parser::getCommand() {
    std::string commands[] = {"PASS", "USER", "NICK", "PONG", "PRIVMSG", "NOTICE", "JOIN", "OPER", "QUIT", "KILL", "KICK", "PING", "LIST", "WHO", "PART"};

    return std::string();
}
