#include "includes/LogIdentifier.hpp"
#include "includes/Commando.hpp"

Commando::Commando() {}

Commando::Commando(Serv *server_class) {
    this->general_serv = server_class;
    std::cout << LogIdentifier::info("COMMANDO_CLASS_")
                << "commando has run" << std::endl;
}

void Commando::UserConnect(int id) {
    this->general_serv
        ->getUserStorage()
        ->add_user(new User(id));
}

int Commando::NickCmd(std::string old_nickname,
                           std::string new_nickname) {
    //ПРОВЕРКА ВАЛИДНОСТИ НИКА
    if (nickname_validator(new_nickname) != NICKNAME_HAS_VALID)
    {
        return (nickname_validator(new_nickname));
        //ОТПРАВИТЬ
        //СООБЩЕНИЕ О НЕВАЛИДНОСТИ
    }
    //_____________________________
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
    return (NICKNAME_IS_GIVEN);//ОТПРАВИТЬ
    //СООБЩЕНИЕ ВЫДАЧЕ НОВОГО НИКА
}

int Commando::NickCmd(int id, std::string new_nickname) {
    //ПРОВЕРКА ВАЛИДНОСТИ НИКА
    if (nickname_validator(new_nickname) != NICKNAME_HAS_VALID)
        return (nickname_validator(new_nickname));//ОТПРАВИТЬ
        //СООБЩЕНИЕ О НЕВАЛИДНОСТИ
    this->general_serv
            ->getNicknameStorage()
            ->add_nickname(new_nickname);
    this->general_serv
            ->getUserStorage()
            ->search_by_id(id)
            ->set_nickname(new_nickname);
    if (!this->general_serv
            ->getUserStorage()
            ->search_by_id(id)->get_user_realname().empty())
        this->general_serv
                ->getUserStorage()
                ->search_by_id(id)
                ->setReadyness();
    return (NICKNAME_IS_GIVEN);//ОТПРАВИТЬ MOTD?
}

void Commando::AwayCmd(std::string user_nickname, std::string message) {
    this->general_serv->getUserStorage()
                        ->search_by_nickname(user_nickname)
                        ->setAwayMsg(message);
}

int Commando::UserCmd(int id, std::string clientname,
                      std::string realname){
    this->general_serv
        ->getUserStorage()
        ->search_by_id(id)
        ->setRealname(realname);
    this->general_serv
            ->getUserStorage()
            ->search_by_id(id)
            ->setClientname(clientname);
    if (!this->general_serv
            ->getUserStorage()
            ->search_by_id(id)->get_user_nickname().empty())
        this->general_serv
                ->getUserStorage()
                ->search_by_id(id)
                ->setReadyness();
    return (NEW_USER_CREATE);
}

int Commando::OperCmd(std::string nickname, std::string password) {
    if (!password.empty() && this->general_serv
        ->getPassword().compare(password) != 0){
        return (WRONGPASSWORD);
    }
    this->general_serv->getOpers()->push_back(nickname);
    return (USER_IS_OPER);
}

void Commando::OperCmd(std::string room_name, int limit) {
    this->general_serv
        ->getRoomStorage()
        ->getRoom(room_name)
        ->set_user_limit(limit);
}

void Commando::ModeOCmd(std::string room_name, std::string nickname,
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
    } //else ОТПРАВИТЬ СООБЩЕНИЕ ОБ ОТСУТСТВИИ КОМНАТЫ
}

void Commando::setUserParam(std::string nickname, std::string param,
                            bool value) {
    this->general_serv
        ->getUserStorage()
        ->search_by_nickname(nickname)
        ->setUserParamValue(param, value);
}

void Commando::setRoomParam(std::string room_name, std::string param,
                            bool value) {
    this->general_serv
        ->getRoomStorage()
        ->getRoom(room_name)
        ->setRoomParameter(param, value);
}

//-----------------------------validators-----------------------------------

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

void Commando::WrongReqMessage(std::string user_nickname, int eventId, std::string command) {
    //:My-IRC 421(eventId) nelson(user_nickname) #soskaTv(command) :Unknown command
    std::cout << LogIdentifier::error(":My-IRC " + std::to_string(eventId) +
    " " + user_nickname + " " + command + " :Unknown command") << std::endl;
}
