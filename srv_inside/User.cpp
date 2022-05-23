#include "User.hpp"

User::User()
{
    user_login = "oper4221";
    user_nickname = "operator";
    user_id = 0;
}

User::User(std::string login, std::string nickname, int id, std::string realname)
{
    user_login = login;
    user_nickname = nickname;
    user_id = id;
    user_realname = realname;
}

void User::set_nickname(std::string new_nickname) {
    std::cout   << LogIdentifier::debug()
                << "user with id " << user_id
                << " changed nickname ";
    if (user_nickname.empty())
        std::cout   << "on " << new_nickname << std::endl;
    else
        std::cout   << user_nickname << " on "
                    << new_nickname << std::endl;
    user_nickname = new_nickname;
}

std::string User::get_user_login() {return (user_login);}

std::string User::get_user_nickname() {return (user_nickname);}

std::string User::get_user_realname() {return (user_realname);}

int User::get_user_id() {return (user_id);}