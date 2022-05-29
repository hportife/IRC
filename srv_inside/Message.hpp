#ifndef IRC_MESSAGE_HPP
#define IRC_MESSAGE_HPP

#define ISNOCOMMANT 2000
#define ISCOMMAND   2001

#include <iostream>
#include <vector>
#include "User.hpp"
//need to add a message counter for users
class Message{
private:
    std::string                 some_message;
    std::vector<std::string>    command_parameters;
    int                         is_command;
    User                        *sender;

public:
    Message(User *user_sender, std::string message, int iscommand);
    ~Message();

    std::string                 get_message();
    void                        set_command_parameter(std::string parameter);
    std::vector<std::string>    get_commands();
};

#endif