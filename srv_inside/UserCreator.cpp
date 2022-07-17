#include "User.hpp"

UserCreator::UserCreator(int tmp_id, NicknameStorage *tmp_storage, std::string server_password) {
    id = tmp_id;
    nickname_storage = tmp_storage;
    correct_password = server_password;
    std::cout   << LogIdentifier::debug("FROM_USERCREATOR_")
                << "called user creator CONSTR for id: "
                << id << std::endl;
}

UserCreator::~UserCreator() {
    std::cout   << LogIdentifier::debug("FROM_USERCREATOR_")
                << "called user creator DESTR for id: "
                << id << std::endl;
}

void UserCreator::set_password(std::string tmp_pass) {
    password = tmp_pass;
    std::cout   << LogIdentifier::info("FROM_USERCREATOR_")
                << "user with id " << id
                << " entered password" << std::endl;
}

void UserCreator::set_nickname(std::string tmp_nickname) {
    nickname = tmp_nickname;
    std::cout   << LogIdentifier::info("FROM_USERCREATOR_")
                << "user with id " << id
                << " entered nickname" << std::endl;
}

void UserCreator::set_realname(std::string tmp_realname) {
    realname = tmp_realname;
    std::cout   << LogIdentifier::info("FROM_USERCREATOR_")
                << "user with id " << id
                << " entered realname" << std::endl;
}


int UserCreator::pass_validation(std::string correct_pass) {
    if (password.compare(correct_pass) != 0)
    {
        std::cout   << LogIdentifier::error("FROM_USERCREATOR_")
                    << "user with id " << id
                    << " entered incorrect password"
                    << std::endl;
        return (INCORRPASS);
    }
    std::cout   << LogIdentifier::info("FROM_USERCREATOR_")
                << "user with id " << id
                << " entered correct password"
                << std::endl;
    return (CORRPASS);
}

int UserCreator::nickname_validation(std::string tested_nickname) {
    if (nickname_storage->
        check_size_added_nickname(tested_nickname)
        != 0){
        return (INCORRNICKNAME);
    }
    else if (nickname_storage->search_a_conflict(tested_nickname) == ERR_NICKNAMEINUSE) {
        return (ERR_NICKNAMEINUSE);
    }
    return (NICKNAMEISMAYBEGIVEN);
}

int UserCreator::parameter_validation(std::string correct_pass) {
    if (pass_validation(correct_pass) == INCORRPASS)
        return (INCORRPASS);
    else if (nickname_validation(nickname) != NICKNAMEISMAYBEGIVEN)
        return (INCORRNICKNAME);
    return (NICKNAMEISMAYBEGIVEN);
}

int UserCreator::swap_nickname(User *user, std::string new_nickname) {
    if (nickname_validation(nickname) != NICKNAMEISMAYBEGIVEN)
        return (nickname_validation(nickname));
    nickname_storage->add_nickname(new_nickname);
    nickname_storage->delete_nickname(user->get_user_nickname());
    tmp_user->set_nickname(new_nickname);
    return (NICKNAMEHASBEENGIVEN);
}

User *UserCreator::get_ready_user() {
    int result = parameter_validation(correct_password);
    if (result == NICKNAMEISMAYBEGIVEN){
        tmp_user = new User(this->nickname,
                            this->id,
                            this->realname);
        nickname_storage->add_nickname(nickname);
        std::cout << LogIdentifier::debug("FROM_USERCREATOR_")
                  << "User creator create a user with: "
                  << "\n\t\t\t-nickname: [" << nickname
                  << "]\n\t\t\t-id      : [" << id
                  << "]\n\t\t\t-realname: [" << realname
                  << "]" << std::endl;
        return (tmp_user->clone());
    }
    else if (result == INCORRNICKNAME)
            std::cout   << LogIdentifier::error("FROM_USERCREATOR_")
                        << " id " << id
                        << " need to set nickname, because nickname ["
                        << nickname << "] is incorrect";
    else if (result == INCORRPASS)
        std::cout   << LogIdentifier::error("FROM_USERCREATOR_")
                    << " id " << id
                    << " enter incorrect pass. Connect need to close"
                    << std::endl;
    return (NULL);
}
