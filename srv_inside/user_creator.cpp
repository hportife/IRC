#include "user.hpp"

user_creator::user_creator(int tmp_id, NicknameStorage *tmp_storage, std::string server_password) {
    id = tmp_id;
    nickname_storage = tmp_storage;
    correct_password = server_password;
    tmp_user = new user();
    std::cout   << LogIdentifier::debug()
                << "called user creator CONSTR for id: "
                << id << std::endl;
}

user_creator::~user_creator() {
    std::cout   << LogIdentifier::debug()
                << "called user creator DESTR for id: "
                << id << std::endl;
}

void user_creator::set_password(std::string tmp_pass) {
    password = tmp_pass;
    std::cout   << LogIdentifier::info()
                << "user with id " << id
                << "entered password" << std::endl;
}

void user_creator::set_login(std::string tmp_login) {
    login = tmp_login;
    std::cout   << LogIdentifier::info()
                << "user with id " << id
                << "entered login" << std::endl;
}

void user_creator::set_nickname(std::string tmp_nickname) {
    nickname = tmp_nickname;
    std::cout   << LogIdentifier::info()
                << "user with id " << id
                << "entered nickname" << std::endl;
}

void user_creator::set_realname(std::string tmp_realname) {
    realname = tmp_realname;
    std::cout   << LogIdentifier::info()
                << "user with id " << id
                << "entered realname" << std::endl;
}


int user_creator::pass_validation(std::string correct_pass) {
    if (password.compare(correct_pass) != 0)
    {
        std::cout   << LogIdentifier::error()
                    << "user with id " << id
                    << "entered incorrect password"
                    << std::endl;
        return (INCORRPASS);
    }
    std::cout   << LogIdentifier::info()
                << "user with id " << id
                << "entered correct password"
                << std::endl;
    return (CORRPASS);
}

int user_creator::nickname_validation(std::string tested_nickname) {
    if (tested_nickname.size() > 9){
        std::cout   << LogIdentifier::error()
                    << "login " << tested_nickname
                    << "is too long"
                    << std::endl;
        return (ERR_NICKNAMEISTOOLONG);
    }
    else if (NicknameStorage::search_a_conflict(tested_nickname) == ERR_NICKNAMEINUSE) {
        return (ERR_NICKNAMEINUSE);
    }
        return (NICKNAMEISMAYBEGIVEN);
}

int user_creator::parameter_validation(std::string correct_pass) {
    if (pass_validation(correct_pass) == INCORRPASS)
        return (INCORRPASS);
    else if (nickname_validation(nickname) != NICKNAMEISMAYBEGIVEN)
        return (nickname_validation(nickname));
}