#include "tools/LogIdentifier.hpp"
#include "Commando.hpp"

Commando::Commando(Serv *server_class) {
    this->general_serv = server_class;
    std::cout << LogIdentifier::info("COMMANDO_CLASS_")
                << "commando has run" << std::endl;
}

void Commando::getNextCommandLine() {
    if (!this->general_serv->GetTasks()->empty()) {
        this->commandLine = this->general_serv->GetTasks()->front();
        this->general_serv->GetTasks()->pop();
    }
}

int Commando::swapNickname(std::string old_nickname,
                           std::string new_nickname) {
    //ПРОВЕРКА ВАЛИДНОСТИ НИКА
    if (nickname_validator(new_nickname) != NICKNAME_HAS_VALID)
        return (nickname_validator(new_nickname));
    //ВЫДАЧА НИКНЕЙМА
    this->general_serv
            ->getNicknameStorage()
            ->add_nickname(new_nickname);
    this->general_serv
            ->getUserStorage()
            ->search_by_nickname(old_nickname)
            ->set_nickname(new_nickname);
    this->general_serv
            ->getNicknameStorage()
            ->delete_nickname(old_nickname);
    return (NICKNAME_IS_GIVEN);
}

int Commando::setAwayMsg(std::string user_nickname, std::string message) {
    this->general_serv->getUserStorage()
                        ->search_by_nickname(user_nickname)
                        ->setAwayMsg(message);
}

int Commando::setAwayMsg(std::string user_nickname) {
    this->general_serv->getUserStorage()
            ->search_by_nickname(user_nickname)
            ->setAwayMsg();
}

int Commando::userCommand(std::string nickname, int id,
                          std::string realname,
                          std::string clientname){
    if (nickname_validator(nickname) != NICKNAME_HAS_VALID)
        return (nickname_validator(nickname));
    this->general_serv
        ->getNicknameStorage()
        ->add_nickname(nickname);
    User *new_user = new User(nickname, id, realname, clientname);
    this->general_serv
        ->getUserStorage()
        ->add_user(new_user->clone());
    delete new_user;
    return (NEW_USER_CREATE);
}

//-----------------------------validators---------------------------------------

int Commando::nickname_validator(std::string nickname) {
    if (nickname.length() > 9 || nickname.empty()) {
        return (NICKNAME_IS_WRONG);
    }
    if (this->general_serv
                ->getNicknameStorage()
                ->search_a_conflict(nickname)
        == ERR_NICKNAMEINUSE) {
        return (ERR_NICKNAMEINUSE);
    }
    return (NICKNAME_HAS_VALID);
}

int Commando::operLogin(std::string nickname, std::string password) {
    if (!password.empty() && this->general_serv
        ->getPassword().compare(password) != 0){
        return (WRONGPASSWORD);
    }
    this->general_serv->getOpers()->push_back(nickname);
    return (USER_IS_OPER);
}

void Commando::setRoomLimit(std::string room_name, int limit) {
    this->general_serv
        ->getRoomStorage()
        ->getRoom(room_name)
        ->set_user_limit(limit);
}

void Commando::setRoomOperRights(std::string room_name, std::string nickname,
                                 bool rights) {
    if (this->general_serv
            ->getRoomStorage()
            ->getRoom(room_name) != NULL){
        if (rights)
            this->general_serv
                ->getRoomStorage()
                ->getRoom(room_name)->set_oper(nickname);
        else
            this->general_serv
                ->getRoomStorage()
                ->getRoom(room_name)->unset_oper(nickname);
    }
}

void Commando::setUserParam(std::string nickname, std::string param,
                            bool value) {
    this->general_serv
        ->getUserStorage()
        ->search_by_nickname(nickname)
        ->setUserParamValue(param, value);
}