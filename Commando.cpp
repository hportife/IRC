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
    if (new_nickname.length() > 9 || new_nickname.empty()) {
        return (NICKNAME_IS_WRONG);
    }
    //ПРОВЕРКА НАЛИЧИЯ КОНФЛИКТОВ
    if (this->general_serv
            ->getNicknameStorage()
            ->search_a_conflict(new_nickname)
            == ERR_NICKNAMEINUSE) {
        return (ERR_NICKNAMEINUSE);
    }
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