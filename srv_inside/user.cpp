#include "user.hpp"

user::user()
{
    user_login = "oper4221";
    user_nickname = "operator";
    user_id = 0;
}

user::user(std::string login, std::string nickname, int id)
{
    user_login = login;
    user_nickname = nickname;
    user_id = id;
}

std::string user::get_user_login() {return (user_login);}

std::string user::get_user_nickname() {return (user_nickname);}

int user::get_user_id() {return (user_id);}