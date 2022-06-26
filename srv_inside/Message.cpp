
#include "../tools/LogIdentifier.hpp"
#include "Message.hpp"

Message::Message(User *user_sender, std::string message, int iscommand) {
    sender = user_sender;
    is_command = iscommand;

    if (iscommand == 0 && message.empty())
    {
        std::cout   << LogIdentifier::debug()
                    << "user "
                    << sender->get_user_nickname()
                    << " send a empty message"
                    << std::endl;
        some_message = "[empty message]";
    }
    else if (iscommand == 1)
    {
        std::cout   << LogIdentifier::info()
                    << "user "
                    << sender->get_user_nickname()
                    << " send a command"
                    << std::endl;
    }
    else if (iscommand == 0 && !message.empty()){
        std::cout   << LogIdentifier::info()
                    << "user "
                    << sender->get_user_nickname()
                    << " send a message"
                    << std::endl;
    }
}

Message::~Message() {
    std::cout   << LogIdentifier::debug()
                << "message from user "
                << sender->get_user_nickname()
                << " has been deleted"
                << std::endl;
}

std::string Message::get_message() {
    if (!some_message.empty())
        return (some_message);
    else
        return (nullptr);
}

