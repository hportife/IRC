#include "User.hpp"

User::User(std::string nickname, int id, std::string realname)
{
    user_nickname = nickname;
    user_id = id;
    user_realname = realname;
    std::cout   << LogIdentifier::info("FROM_USERCLASS_" + this->user_nickname + "_")
                << "User: \n\t\t\t  | nick:\t["
                << nickname
                << "]\t|\n \t\t\t  | id: \t["
                << id
                << "]\t|\n \t\t\t  has been created"
                << std::endl;
}

User::~User() {
    std::cout   << LogIdentifier::info("FROM_USERCLASS_" + this->user_nickname + "_")
                << "User: \n\t\t\t  | nick:\t["
                << this->user_nickname
                << "]\t|\n\t\t\t  | id: \t["
                << this->user_id
                << "]\t|\n\t\t\t  has been deleted"
                << std::endl;
}

void User::set_nickname(std::string new_nickname) {
    std::cout   << LogIdentifier::debug("FROM_USERCLASS_" + this->user_nickname + "_")
                << "user with id " << user_id
                << " changed nickname ";
    if (user_nickname.empty())
        std::cout   << "on " << new_nickname << std::endl;
    else
        std::cout   << user_nickname << " on "
                    << new_nickname << std::endl;
    user_nickname = new_nickname;
}


std::string User::get_user_nickname() {return (user_nickname);}

std::string User::get_user_realname() {return (user_realname);}

int User::get_user_id() {return (user_id);}

User *User::clone() const{
    return (new User(this->user_nickname,
                     this->user_id,
                     this->user_realname));
}