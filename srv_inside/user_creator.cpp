#include "user.hpp"

user_creator::user_creator(int tmp_id) {
    id = tmp_id;
    tmp_user = new user();
    std::cout   << "DBG:: called user creator CONSTR for id: "
                << id << std::endl;
}

user_creator::~user_creator() {
    std::cout   << "DBG:: called user creator DESTR for id: "
                << id << std::endl;
}

void user_creator::set_password(std::string tmp_pass) {
    password = tmp_pass;
    std::cout   << "DBG:: user with id " << id
                << "entered password" << std::endl;
}

void user_creator::set_login(std::string tmp_login) {
    login = tmp_login;
    std::cout   << "DBG:: user with id " << id
                << "entered login" << std::endl;
}

void user_creator::set_nickname(std::string tmp_nickname) {
    nickname = tmp_nickname;
    std::cout   << "DBG:: user with id " << id
                << "entered nickname" << std::endl;
}

void user_creator::set_realname(std::string tmp_realname) {
    realname = tmp_realname;
    std::cout   << "DBG:: user with id " << id
                << "entered realname" << std::endl;
}


int user_creator::pass_validation(std::string correct_pass) {
    if (password.compare(correct_pass) != 0)
    {
        std::cout   << "DBG:: user with id " << id
                    << "entered incorrect password"
                    << std::endl;
        return (INCORRPASS);
    }
    std::cout   << "DBG:: user with id " << id
                << "entered correct password"
                << std::endl;
    return (CORRPASS);
}

int user_creator::parameter_validation(std::string correct_pass) {
    if (pass_validation(correct_pass) == INCORRPASS)
        return (INCORRPASS);
    else if ()
}