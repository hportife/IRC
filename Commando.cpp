#include "includes/LogIdentifier.hpp"
#include "includes/Commando.hpp"

//!!!!!!!!
#include "unistd.h"
#include <sys/socket.h>
//!!!!!!!!

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

void Commando::WrongReqMessage(const std::string& user_nickname, int eventId, const std::string& command) {
    std::string	msg = ":Amateur42_IRC ";
    std::stringstream	ss;

    ss << eventId;
    msg += ss.str() + " " + user_nickname;
    switch (eventId)
    {
//        case ERR_NOSUCHNICK:
//            msg += ' ' + command.getArgument(0) + " :No such nick/channel\n";
//            break;
        case ERR_NOSUCHSERVER:
            msg += " :No such server\n";
            break;
//        case ERR_NOSUCHCHANNEL:
//            msg += ' ' + command.getArgument(0) + " :No such channel\n";
//            break;
        case ERR_CANNOTSENDTOCHAN:
            msg += " :Cannot send to channel\n";
            break;
        case ERR_TOOMANYCHANNELS:
            msg += " :You have joined too many channels\n";
            break;
        case ERR_WASNOSUCHNICK:
            msg += " :There was no such nickname\n";
            break;
        case ERR_TOOMANYTARGETS:
            msg += " :Duplicate recipients delivered\n";
            break;
        case ERR_NOORIGIN:
            msg += " :No origin specified\n";
            break;
        case ERR_NORECIPIENT:
            msg += " :No recipient given (" + command + ")\n";
            break;
        case ERR_NOTEXTTOSEND:
            msg += " :No text to send\n";
            break;
        case ERR_NOTOPLEVEL:
            msg += " " + command + " :No toplevel domain specified\n";
            break;
        case ERR_WILDTOPLEVEL:
            msg += " " + command + " :Wildcard in toplevel domain\n";
            break;
        case ERR_UNKNOWNCOMMAND:
            msg += " " + command + " :Unknown command\n";
            break;
        case ERR_NOMOTD:
            msg += " :MOTD File is missing\n";
            break;
        case ERR_NOADMININFO:
            msg += " " + command + " :No administrative info available\n";
            break;
        case ERR_NONICKNAMEGIVEN:
            msg += " :No nickname given\n";
            break;
//        case ERR_ERRONEUSNICKNAME:
//            msg += " " + command.getArgument(0) + " :Erroneus nickname\n";
//            break;
        case ERR_NICKNAMEINUSE:
            msg += " * :Nickname is already in use.\n";
            break;
        case ERR_NICKCOLLISION:
            msg += " " + command + " :Nickname collision KILL\n";
            break;
        case ERR_USERNOTINCHANNEL:
            msg += " " + command + " :They aren't on that channel\n";
            break;
        case ERR_NOTONCHANNEL:
            msg += " " + command + " :You're not on that channel\n";
            break;
        case ERR_USERONCHANNEL:
            msg += " " + command + " :is already on channel\n";
            break;
        case ERR_NOLOGIN:
            msg += " " + command + " :User not logged in\n";
            break;
        case ERR_SUMMONDISABLED:
            msg += " :SUMMON has been disabled\n";
            break;
        case ERR_USERSDISABLED:
            msg += " :USERS has been disabled\n";
            break;
        case ERR_NOTREGISTERED:
            msg += " :You have not registered\n";
            break;
        case ERR_NEEDMOREPARAMS:
            msg += " " + command + " :Not enough parameters\n";
            break;
        case ERR_ALREADYREGISTRED:
            msg += " :You may not reregister\n";
            break;
        case ERR_NOPERMFORHOST:
            msg += " :Your host isn't among the privileged\n";
            break;
        case ERR_PASSWDMISMATCH:
            msg += " :Password incorrect\n";
            break;
        case ERR_YOUREBANNEDCREEP:
            msg += " :You are banned from this server\n";
            break;
        case ERR_KEYSET:
            msg += " " + command + " :Channel key already set\n";
            break;
        case ERR_CHANNELISFULL:
            msg += " " + command + " :Cannot join channel (+l)\n";
            break;
        case ERR_UNKNOWNMODE:
            msg += " :is unknown mode char to me\n";
            break;
        case ERR_INVITEONLYCHAN:
            msg += " " + command + " :Cannot join channel (+i)\n";
            break;
        case ERR_BANNEDFROMCHAN:
            msg += " " + command + " :Cannot join channel (+b)\n";
            break;
        case ERR_BADCHANNELKEY:
            msg += " " + command + " :Cannot join channel (+k)\n";
            break;
        case ERR_NOPRIVILEGES:
            msg += " :Permission Denied- You do not have the correct IRC Operator privileges\n";
            break;
        case ERR_CHANOPRIVSNEEDED:
            msg += " " + command + " :You're not channel operator\n";
            break;
        case ERR_CANTKILLSERVER:
            msg += " :You cant kill a server!\n";
            break;
        case ERR_NOOPERHOST:
            msg += " :No O-lines for your host\n";
            break;
        case ERR_UMODEUNKNOWNFLAG:
            msg += " :Unknown MODE flag\n";
            break;
        case ERR_USERSDONTMATCH:
            msg += " :Cant change mode for other users\n";
            break;
        default:
            msg += "UNKNOWN ERROR\n";
            break;
    }
//    logger.logUserMessage(msg, user, OUT);
    write(this->general_serv->getUserStorage()->search_by_nickname(user_nickname)->get_user_id(),
          msg.c_str(), msg.size());
}

//void    AnswerMessage(const std::string& user_nickname, int eventId,
//                      const std::string& command);

void    Commando::AnswerMessage(const std::string& user_nickname, int eventId, const std::string& command) {
    std::string	msg = ":Amateur42_IRC ";
    std::stringstream	ss;

    ss << eventId;
    msg += ss.str() + " " + user_nickname;
    switch (eventId)
    {
        case RPL_NOWAWAY:
            msg += " :You have been marked as being away\n";
            break;
        case RPL_WHOISOPERATOR:
            msg +=  + " :is an IRC operator\n";
            break;
        case RPL_ENDOFWHOWAS:
            msg +=  + " :End of WHOWAS\n";
            break;
        case RPL_LISTSTART:
            msg += "Channel :Users  Name\n";
            break;
        case RPL_NOTOPIC:
            msg +=  + " :No topic is set\n";
            break;
        case RPL_SUMMONING:
            msg +=  + " :Summoning user to IRC\n";
            break;
//        case RPL_ENDOFWHO:
//            msg += " " + command.getArgument(0) + " :End of /WHO list\n";
//            break;
        case RPL_ENDOFNAMES:
            msg +=  + " :End of /NAMES list\n";
            break;
        case RPL_ENDOFLINKS:
            msg +=  + " :End of /LINKS list\n";
            break;
        case RPL_ENDOFBANLIST:
            msg +=  + " :End of channel ban list\n";
            break;
        case RPL_ENDOFINFO:
            msg += " :End of /INFO list\n";
            break;
        case RPL_MOTDSTART:
            msg += " :- Message of the day - \n";
            break;
        case RPL_ENDOFMOTD:
            msg += " :End of /MOTD command\n";
            break;
        case RPL_YOUREOPER:
            msg += " " + command + " :You are now an IRC operator\n";
            break;
        case RPL_REHASHING:
            msg +=  + " :Rehashing\n";
            break;
        case RPL_USERSSTART:
            msg += " :UserID   Terminal  Host\n";
            break;
        case RPL_USERS:
            msg += " :%-8s %-9s %-8s\n";
            break;
        case RPL_ENDOFUSERS:
            msg += " :End of users\n";
            break;
        case RPL_NOUSERS:
            msg += " :Nobody logged in\n";
            break;
        case RPL_ENDOFSTATS:
            msg +=  + " :End of /STATS report\n";
            break;
        case RPL_STATSUPTIME:
            msg += " :Server Up %d days %d:%02d:%02d\n";
            break;
        case RPL_UMODEIS:
            msg +=  + "\n";
            break;
        case RPL_LUSEROP:
            msg +=  + " :operator(s) online\n";
            break;
        case RPL_LUSERUNKNOWN:
            msg +=  + " :unknown connection(s)\n";
            break;
        case RPL_LUSERCHANNELS:
            msg +=  + " :channels formed\n";
            break;
        case RPL_LUSERME:
            msg += " :I have clients and servers\n";
            break;
        case RPL_ADMINME:
            msg +=  + " :Administrative info\n";
            break;
        default:
            msg += "UNKNOWN REPLY\n";
            break;
    }
//    logger.logUserMessage(msg, user, OUT);
    send(this->general_serv->getUserStorage()->search_by_nickname(user_nickname)->get_user_id(),
         msg.c_str(), msg.size(), 0);
}
